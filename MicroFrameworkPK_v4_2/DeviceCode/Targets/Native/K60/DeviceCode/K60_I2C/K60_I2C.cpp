////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

////////////////////////////////////////////////////////////////////////////////
#undef  TRACE_ALWAYS
#define TRACE_ALWAYS               0x00000001

#undef  DEBUG_TRACE
#define DEBUG_TRACE (TRACE_ALWAYS)

////////////////////////////////////////////////////////////////////////////////

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata
#endif

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_K60_I2C_Driver"
#endif

K60_I2C_Driver g_K60_I2C_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

BOOL I2C_Internal_Initialize()
{
    return K60_I2C_Driver::Initialize();
}

BOOL I2C_Internal_Uninitialize()
{
    return K60_I2C_Driver::Uninitialize();
}

void I2C_Internal_XActionStart( I2C_HAL_XACTION* xAction, bool repeatedStart )
{
    K60_I2C_Driver::MasterXAction_Start( xAction, repeatedStart );
}

void I2C_Internal_XActionStop()
{
    K60_I2C_Driver::MasterXAction_Stop();
}

void I2C_Internal_GetClockRate( UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2)
{
    K60_I2C_Driver::GetClockRate( rateKhz, clockRate, clockRate2 );
}

void I2C_Internal_GetPins(GPIO_PIN& scl, GPIO_PIN& sda)
{
    return K60_I2C_Driver::GetPins( scl, sda);
}

//--//

UINT16 K60_I2C_Driver::s_Divider[64] =
{ 20, 22, 24, 26, 28, 30, 34, 40,
  28, 32, 38, 40, 44, 48, 56, 68,
  48, 56, 64, 72, 80, 88, 104, 128,
  80, 96, 112, 128, 144, 160, 192, 240,
  160, 192, 224, 256, 288, 320, 384, 480,
  320, 384, 448, 512, 576, 640, 768, 960,
  640, 768, 896, 1024, 1152, 1280, 1536, 1920,
  1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840 };

BOOL K60_I2C_Driver::Initialize()
{
    // reset

    if (g_K60_I2C_Driver.m_initialized == FALSE)
    {
        g_K60_I2C_Driver.m_currentXAction = NULL;
        g_K60_I2C_Driver.m_currentXActionUnit = NULL;

        // enable I2C0 clock
        SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

        CPU_GPIO_DisablePin(K60_TWI_SDA, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_2);
        CPU_GPIO_DisablePin(K60_TWI_SCL, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_2);

        // setup interrupt vector
        CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(I2C0_IRQn), &K60_I2C_Driver::ISR, NULL);

        // enable IIC
        I2C0->C1 = I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK;

        // set the Subordinate address
        I2C0->A1 = 0x7E;

        // clear arbitration lost and bus busy
        I2C0->S &= ~(I2C_S_ARBL_MASK | I2C_S_BUSY_MASK);

        g_K60_I2C_Driver.m_initialized = TRUE;
    }

    return TRUE;
}

BOOL K60_I2C_Driver::Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();

    if (g_K60_I2C_Driver.m_initialized == TRUE)
    {
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(I2C0_IRQn));

        // disable
        I2C0->C1 &= ~(I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK);

        g_K60_I2C_Driver.m_initialized = FALSE;

        CPU_GPIO_EnableInputPin(K60_TWI_SDA, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
        CPU_GPIO_EnableInputPin(K60_TWI_SCL, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
    }

    return TRUE;
}

void K60_I2C_Driver::MasterXAction_Start(I2C_HAL_XACTION* xAction, bool repeatedStart)
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();

    UINT8 control;
    UINT8 address;

    g_K60_I2C_Driver.m_currentXAction = xAction;
    g_K60_I2C_Driver.m_currentXActionUnit = xAction->m_xActionUnits[xAction->m_current];
    ++xAction->m_current;

    address = 0xFE & (xAction->m_address << 1);
    address |= g_K60_I2C_Driver.m_currentXActionUnit->IsReadXActionUnit() ? c_DirectionRead : c_DirectionWrite;

    if (!repeatedStart)
    {
        /////////////////////////////////
        // Start sequence
        I2C0->F = xAction->m_clockRate;

        control = I2C_C1_MST_MASK | I2C_C1_TX_MASK;

        // if the transaction is one byte only to read, then we must send NAK immediately
        if ((g_K60_I2C_Driver.m_currentXActionUnit->m_bytesToTransfer == 1) && (address & K60_I2C_Driver::c_DirectionRead))
        {
            control |= I2C_C1_TXAK_MASK;
        }

        I2C0->C1 |= control;
    }
    else
    {
        /////////////////////////////////
        // Repeated start sequence
        I2C0->C1 |= I2C_C1_RSTA_MASK;
        // Repeated start sequence
        /////////////////////////////////
    }

    // send device address
    I2C0->D = address;
}

void K60_I2C_Driver::MasterXAction_Stop()
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();

    I2C0->C1 &= ~(I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_TXAK_MASK | I2C_C1_RSTA_MASK);

    g_K60_I2C_Driver.m_currentXAction = NULL;
    g_K60_I2C_Driver.m_currentXActionUnit = NULL;
}

void K60_I2C_Driver::GetClockRate(UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2)
{
    int periph_clk_hz = CPU_SystemClock() / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24) + 1);
    int divider = periph_clk_hz / (rateKhz * 1000);

    ASSERT(s_Divider[0x3F] == 3840);

    UINT16* entry = s_Divider;
    UINT8 best = 0x3F;

    for (UINT8 i = 0; i < ARRAYSIZE(s_Divider); ++i)
    {
        if (*entry >= divider)
        {
            if (s_Divider[best] > *entry)
            {
                best = i;
            }
        }

        ++entry;
    }

    clockRate = best;
    clockRate2 = 0;
}

void K60_I2C_Driver::WriteToSubordinate(I2C_HAL_XACTION_UNIT* unit)
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();
    UINT8* queueData;

    queueData = unit->m_dataQueue.Pop();

    I2C0->D = *queueData;

    ++unit->m_bytesTransferred;
    --unit->m_bytesToTransfer;

}

void K60_I2C_Driver::ReadFromSubordinate(I2C_HAL_XACTION_UNIT* unit)
{
    UINT8* queueData;

    queueData = unit->m_dataQueue.Push();

    ASSERT(queueData);

    UINT8 data = I2C0->D;

    *queueData = data;
    ++unit->m_bytesTransferred;
    --unit->m_bytesToTransfer;

}

void K60_I2C_Driver::ISR(void* arg)
{
    GLOBAL_LOCK(irq);

    // read control and status
    UINT8 status = I2C0->S;
    UINT8 ctrl = I2C0->C1;

    I2C_HAL_XACTION* xAction = g_K60_I2C_Driver.m_currentXAction;
    I2C_HAL_XACTION_UNIT* unit = g_K60_I2C_Driver.m_currentXActionUnit;

    ASSERT(xAction);
    ASSERT(unit);

    // master mode
    if (ctrl & I2C_C1_MST_MASK)
    {
        // tx
        if (ctrl & I2C_C1_TX_MASK)
        {
            // transaction completed
            if (unit->m_bytesToTransfer == 0)
            {
                if (xAction->ProcessingLastUnit())
                {
                    xAction->Signal(I2C_HAL_XACTION::c_Status_Completed);
                }
                else
                {
                    MasterXAction_Start(xAction, true);
                }
            }
            // NAK received from Subordinate
            else if (status & I2C_S_RXAK_MASK)
            {
                xAction->Signal(I2C_HAL_XACTION::c_Status_Aborted);
            }
            else
            {
                // end of address cycle
                if (unit->IsReadXActionUnit())
                {
                    I2C0->C1 &= ~I2C_C1_TX_MASK;
                    I2C0->C1 |= I2C_C1_TXAK_MASK;

                    UINT8 dummy = I2C0->D;
                }
                // write next byte
                else
                {
                    WriteToSubordinate(unit);
                }
            }
        }
        // rx
        else
        {
            bool lastUnit = xAction->ProcessingLastUnit();

            // prepare for nak
            if (unit->m_bytesToTransfer == 2)
            {
                I2C0->C1 |= I2C_C1_TXAK_MASK;

            }

            if (unit->m_bytesToTransfer == 1)
            {
                if (lastUnit)
                {
                    // send transaction stop
                    xAction->Signal(I2C_HAL_XACTION::c_Status_Completed);
                }
            }

            // read next byte
            ReadFromSubordinate(unit);

            if (!lastUnit)
            {
                // start next
                MasterXAction_Start(xAction, true);
            }
        }
    }
    // Subordinate mode
    else
    {
        debug_printf("[K60_I2C_Driver::ISR] arbitration lost\r\n");

        I2C0->S &= ~I2C_S_ARBL_MASK;

        if (I2C0->S & I2C_S_IAAS_MASK)
        {
            debug_printf("[K60_I2C_Driver::ISR] addressed as Subordinate\r\n");
        }

        xAction->Signal(I2C_HAL_XACTION::c_Status_Aborted);
    }

    // clear interrupt flag
    I2C0->S |= I2C_S_IICIF_MASK;
}

void K60_I2C_Driver::GetPins(GPIO_PIN& scl, GPIO_PIN& sda)
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();

    scl = K60_TWI_SCL;
    sda = K60_TWI_SDA;
}

