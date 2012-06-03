////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

//--//

#undef TRACE_ALWAYS

#define TRACE_ALWAYS               0x00000001

#undef DEBUG_TRACE
#define DEBUG_TRACE (TRACE_ALWAYS)

/***************************************************************************/

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_K60_SPI_Driver"
#endif 

K60_SPI_Driver g_K60_SPI_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif 

//--//

//#define DEBUG_SPI  1

#if defined(DEBUG_SPI)
#define SPI_DEBUG_PRINT(x)  hal_printf(x);
#define SPI_LOOP_BACK   1
#else 
#define SPI_DEBUG_PRINT(x)
#define SPI_LOOP_BACK   0
#endif 



BOOL CPU_SPI_Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::Initialize();
}

void CPU_SPI_Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    K60_SPI_Driver::Uninitialize();
}

BOOL CPU_SPI_nWrite16_nRead16(const SPI_CONFIGURATION& Configuration, UINT16* Write16, INT32 WriteCount, UINT16* Read16, INT32 ReadCount, INT32 ReadStartOffset)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::nWrite16_nRead16(Configuration, Write16, WriteCount, Read16, ReadCount, ReadStartOffset);
}

BOOL CPU_SPI_nWrite8_nRead8(const SPI_CONFIGURATION& Configuration, UINT8* Write8, INT32 WriteCount, UINT8* Read8, INT32 ReadCount, INT32 ReadStartOffset)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::nWrite8_nRead8(Configuration, Write8, WriteCount, Read8, ReadCount, ReadStartOffset);
}

BOOL CPU_SPI_Xaction_Start(const SPI_CONFIGURATION& Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::Xaction_Start(Configuration);
}

BOOL CPU_SPI_Xaction_Stop(const SPI_CONFIGURATION& Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::Xaction_Stop(Configuration);
}

BOOL CPU_SPI_Xaction_nWrite16_nRead16(SPI_XACTION_16& Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::Xaction_nWrite16_nRead16(Transaction);
}

BOOL CPU_SPI_Xaction_nWrite8_nRead8(SPI_XACTION_8& Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return K60_SPI_Driver::Xaction_nWrite8_nRead8(Transaction);
}

UINT32 CPU_SPI_PortsCount()
{
    return K60_SPI_Driver::c_MAX_SPI;
}

void CPU_SPI_GetPins(UINT32 spi_mod, GPIO_PIN& msk, GPIO_PIN& miso, GPIO_PIN& mosi)
{
    return K60_SPI_Driver::GetPins(spi_mod, msk, miso, mosi);
}

//---------------------------//

UINT16 K60_SPI_Driver::s_Divider[16] =
{ 2, 4, 6, 8, 16, 32, 64, 128,
  256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };

SPI_Type* K60_SPI_Driver::GetSPI(int spiNum)
{
    switch (spiNum)
    {
    case 0:
        return SPI0;
    case 1:
        return SPI1;
    case 2:
        return SPI2;
    default:
        ASSERT(0)
        ;
        return NULL;
    }
}

BOOL K60_SPI_Driver::Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    GPIO_PIN msk, miso, mosi;

    for (int i = 0; i < c_MAX_SPI; i++)
    {
        if (g_K60_SPI_Driver.m_initialized[i] == FALSE)
        {
            // reset SPI - set all pins to inputs
            GetPins(i, msk, miso, mosi);

            CPU_GPIO_EnableInputPin(msk, FALSE, NULL, GPIO_INT_NONE, RESISTOR_PULLUP);
            CPU_GPIO_EnableInputPin(miso, FALSE, NULL, GPIO_INT_NONE, RESISTOR_PULLUP);
            CPU_GPIO_EnableInputPin(mosi, FALSE, NULL, GPIO_INT_NONE, RESISTOR_PULLUP);

            g_K60_SPI_Driver.m_initialized[i] = TRUE;
        }
    }


    return TRUE;
}

void K60_SPI_Driver::Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    GPIO_PIN msk, miso, mosi;

    for (int i = 0; i < c_MAX_SPI; i++)
    {
        if (g_K60_SPI_Driver.m_initialized[i] == TRUE)
        {
            // set pins to inputs
            GetPins(i, msk, miso, mosi);

            CPU_GPIO_EnableInputPin(msk, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
            CPU_GPIO_EnableInputPin(miso, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
            CPU_GPIO_EnableInputPin(mosi, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);

            g_K60_SPI_Driver.m_initialized[i] = FALSE;
        }
    }

    // disable all the SPI clocks
    SIM->SCGC6 &= ~SIM_SCGC6_DSPI0_MASK;
    SIM->SCGC6 &= ~SIM_SCGC6_SPI1_MASK;
    SIM->SCGC3 &= ~SIM_SCGC3_SPI2_MASK;
}

/***************************************************************************/

void K60_SPI_Driver::ISR(void *Param)
{

    debug_printf("error ISR\r\n");
    ASSERT(0);
}

BOOL K60_SPI_Driver::nWrite16_nRead16(const SPI_CONFIGURATION &Configuration, UINT16 *Write16, INT32 WriteCount, UINT16 *Read16, INT32 ReadCount,
        INT32 ReadStartOffset)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    if (g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod])
    {
        HARD_BREAKPOINT();
        return FALSE;
    }

    if (Configuration.SPI_mod > c_MAX_SPI)
    {
        HARD_BREAKPOINT();
        return FALSE;
    }

    if (!Xaction_Start(Configuration))
        return FALSE;
    {
        SPI_XACTION_16 Transaction;

        Transaction.Read16 = Read16;
        Transaction.ReadCount = ReadCount;
        Transaction.ReadStartOffset = ReadStartOffset;
        Transaction.Write16 = Write16;
        Transaction.WriteCount = WriteCount;
        Transaction.SPI_mod = Configuration.SPI_mod;
        Transaction.BusyPin.Pin = GPIO_PIN_NONE;

        if (!Xaction_nWrite16_nRead16(Transaction))
            return FALSE;
    }

    return Xaction_Stop(Configuration);
}

BOOL K60_SPI_Driver::nWrite8_nRead8(const SPI_CONFIGURATION &Configuration, UINT8 *Write8, INT32 WriteCount, UINT8 *Read8, INT32 ReadCount,
        INT32 ReadStartOffset)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    if (g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod])
    {
        return FALSE;
    }

    if (Configuration.SPI_mod > c_MAX_SPI)
    {
        HARD_BREAKPOINT();
        return FALSE;
    }

    if (!Xaction_Start(Configuration))
        return FALSE;

    {
        SPI_XACTION_8 Transaction;

        Transaction.Read8 = Read8;
        Transaction.ReadCount = ReadCount;
        Transaction.ReadStartOffset = ReadStartOffset;
        Transaction.Write8 = Write8;
        Transaction.WriteCount = WriteCount;
        Transaction.SPI_mod = Configuration.SPI_mod;
        Transaction.BusyPin.Pin = GPIO_PIN_NONE;

        if (!Xaction_nWrite8_nRead8(Transaction))
            return FALSE;
    }

    return Xaction_Stop(Configuration);
}

//--//

BOOL K60_SPI_Driver::Xaction_Start(const SPI_CONFIGURATION &Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    if (!g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod])
    {
        g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod] = TRUE;

        // start the clock
        switch (Configuration.SPI_mod)
        {
        case 0:
            SIM->SCGC6 |= SIM_SCGC6_DSPI0_MASK;
            break;
        case 1:
            SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
            break;
        case 2:
            SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK;
            break;
        default:
            ASSERT(FALSE)
            ;
        }

        GPIO_PIN msk, miso, mosi;
        GetPins(Configuration.SPI_mod, msk, miso, mosi);

        // all three SPIs use alt_mode_2
        CPU_GPIO_DisablePin(msk, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_2);
        CPU_GPIO_DisablePin(miso, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_2);
        CPU_GPIO_DisablePin(mosi, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_2);

        SPI_Type* spi = GetSPI(Configuration.SPI_mod);

        // halt and clear FIFOs
        spi->MCR = SPI_MCR_HALT_MASK | SPI_MCR_CLR_TXF_MASK | SPI_MCR_CLR_RXF_MASK;

        // setup transfer size (16 or 8)
        if (Configuration.MD_16bits)
            spi->CTAR[0] = SPI_CTAR_FMSZ(15);
        else
            spi->CTAR[0] = SPI_CTAR_FMSZ(7);

        // manual says SPI is based off system clock - but in fact it is using peripheral clock
        int periph_clk_khz = (CPU_SystemClock() / 1000) / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24) + 1);
        int target_rate_khz = Configuration.Clock_RateKHz;

        // enable the baud rate doubler?
        if (target_rate_khz > (periph_clk_khz / 2))
        {
            spi->CTAR[0] |= SPI_CTAR_DBR_MASK;
            target_rate_khz /= 2;
        }

        // peripheral clock speed divided by 2 due to PBR being set to 0
        int divider = (periph_clk_khz / 2) / target_rate_khz;

        UINT16* entry = s_Divider;
        UINT8 best = 0x0F;

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

        // setup baud rate
        spi->CTAR[0] |= SPI_CTAR_BR(best);

        // disable interrupts
        spi->RSER  = 0x00;

        // master mode
        spi->MCR |= SPI_MCR_MSTR_MASK;

        // enable the SPI
        spi->MCR &= ~SPI_MCR_HALT_MASK;

        // first set CS active as soon as clock and data pins are in proper initial state
        if (Configuration.DeviceCS != GPIO_PIN_NONE)
        {
            CPU_GPIO_EnableOutputPin(Configuration.DeviceCS, Configuration.CS_Active);
        }

        if (Configuration.CS_Setup_uSecs)
        {
            HAL_Time_Sleep_MicroSeconds_InterruptEnabled(Configuration.CS_Setup_uSecs);
        }
    }
    else
    {
        //  HARD_BREAKPOINT();
        return FALSE;
    }

    return TRUE;
}

BOOL K60_SPI_Driver::Xaction_Stop(const SPI_CONFIGURATION &Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    if (g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod])
    {
        UINT32 index = Configuration.SPI_mod;

        if (Configuration.CS_Hold_uSecs)
        {
            HAL_Time_Sleep_MicroSeconds_InterruptEnabled(Configuration.CS_Hold_uSecs);
        }

        GPIO_PIN msk, miso, mosi;
        GetPins(index, msk, miso, mosi);

        // next, bring the CS to the proper inactive state
        if (Configuration.DeviceCS != GPIO_PIN_NONE)
        {
            CPU_GPIO_SetPinState(Configuration.DeviceCS, !Configuration.CS_Active);
        }

        // switch off SPI module
        GetSPI(index)->MCR |= SPI_MCR_HALT_MASK;

        // disable pins
        CPU_GPIO_EnableInputPin(msk, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
        CPU_GPIO_EnableInputPin(miso, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
        CPU_GPIO_EnableInputPin(mosi, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);

        g_K60_SPI_Driver.m_Enabled[Configuration.SPI_mod] = FALSE;
    }
    else
    {
        HARD_BREAKPOINT();
        return FALSE;
    }
    return TRUE;
}

BOOL K60_SPI_Driver::Xaction_nWrite16_nRead16(SPI_XACTION_16 &Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    UINT16 Data16;

    if (!g_K60_SPI_Driver.m_Enabled[Transaction.SPI_mod])
    {
        ASSERT(FALSE);
        return FALSE;
    }

    UINT16 *Write16 = Transaction.Write16;
    INT32 WriteCount = Transaction.WriteCount;
    UINT16 *Read16 = Transaction.Read16;
    INT32 ReadCount = Transaction.ReadCount;
    INT32 ReadStartOffset = Transaction.ReadStartOffset;
    INT32 ReadTotal = 0;

    // as master, we must always write something before reading or not
    if (WriteCount <= 0)
    {
        ASSERT(FALSE);
        return FALSE;
    }
    if (Write16 == NULL)
    {
        ASSERT(FALSE);
        return FALSE;
    }
    if ((ReadCount > 0) && (Read16 == NULL))
    {
        ASSERT(FALSE);
        return FALSE;
    }

    if (ReadCount)
    {
        ReadTotal = ReadCount + ReadStartOffset; // we need to read as many bytes as the buffer is long, plus the offset at which we start
    }

    INT32 loopCnt = ReadTotal;

    // take the max of Read+offset or WrCnt
    if (loopCnt < WriteCount)
        loopCnt = WriteCount;

    // we will use WriteCount to move in the Write16 array
    // so we do no want to go past the end when we will check for 
    // WriteCount to be bigger than zero
    WriteCount -= 1;

    while (loopCnt--)
    {
        SPI_Type* spi = GetSPI(Transaction.SPI_mod);

        // write the 16bit value
        spi->PUSHR = SPI_PUSHR_TXDATA(Write16[0]);

        // wait till data is shifted out
        while (!(spi->SR & SPI_SR_TCF_MASK))
        {
        };

        // read the value
        Data16 = spi->POPR;

        // clear transmit complete flag
        spi->SR |= SPI_SR_TCF_MASK;

        // repeat last write word for all subsequent reads
        if (WriteCount)
        {
            WriteCount--;
            Write16++;
        }

        // only save data once we have reached ReadCount-1 portion of words
        ReadTotal--;
        if ((ReadTotal >= 0) && (ReadTotal < ReadCount))
        {
            Read16[0] = Data16;
            Read16++;
        }

    }

    return TRUE;
}

BOOL K60_SPI_Driver::Xaction_nWrite8_nRead8(SPI_XACTION_8 &Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    UINT8 Data8;

    if (!g_K60_SPI_Driver.m_Enabled[Transaction.SPI_mod])
    {
        ASSERT(FALSE);
        return FALSE;
    }

    UINT8 *Write8 = Transaction.Write8;
    INT32 WriteCount = Transaction.WriteCount;
    UINT8 *Read8 = Transaction.Read8;
    INT32 ReadCount = Transaction.ReadCount;
    INT32 ReadStartOffset = Transaction.ReadStartOffset;
    INT32 ReadTotal = 0;

    // as master, we must always write something before reading or not
    if (WriteCount <= 0)
    {
        ASSERT(FALSE);
        return FALSE;
    }
    if (Write8 == NULL)
    {
        ASSERT(FALSE);
        return FALSE;
    }
    if ((ReadCount > 0) && (Read8 == NULL))
    {
        ASSERT(FALSE);
        return FALSE;
    }

    if (ReadCount)
    {
        ReadTotal = ReadCount + ReadStartOffset; // we need to read as many bytes as the buffer is long, plus the offset at which we start
    }

    INT32 loopCnt = ReadTotal;

    // take the max of Read+offset or WrCnt
    if (loopCnt < WriteCount)
        loopCnt = WriteCount;

    // we will use WriteCount to move in the Write8 array
    // so we do no want to go past the end when we will check for 
    // WriteCount to be bigger than zero
    WriteCount -= 1;

    // Start transmission 
    while (loopCnt--)
    {
        SPI_Type* spi = GetSPI(Transaction.SPI_mod);

        // write the 16bit value
        spi->PUSHR = SPI_PUSHR_TXDATA(Write8[0]);

        // wait till data is shifted out
        while (!(spi->SR & SPI_SR_TCF_MASK))
        {
        };

        // read the value
        Data8 = spi->POPR;

        // repeat last write word for all subsequent reads
        if (WriteCount)
        {
            WriteCount--;
            Write8++;
        }

        // only save data once we have reached ReadCount-1 portion of words
        ReadTotal--;
        if ((ReadTotal >= 0) && (ReadTotal < ReadCount))
        {
            Read8[0] = Data8;
            Read8++;
        }
    }

    return TRUE;
}

void K60_SPI_Driver::GetPins(UINT32 spi_mod, GPIO_PIN &msk, GPIO_PIN &miso, GPIO_PIN &mosi)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    switch (spi_mod)
    {
    case 0:
        msk = (GPIO_PIN) K60_GPIO_Driver::PA15;
        miso = (GPIO_PIN) K60_GPIO_Driver::PA14;
        mosi = (GPIO_PIN) K60_GPIO_Driver::PA16;
        break;
    case 1:
        msk = (GPIO_PIN) K60_GPIO_Driver::PE2;
        miso = (GPIO_PIN) K60_GPIO_Driver::PE3;
        mosi = (GPIO_PIN) K60_GPIO_Driver::PE1;
        break;
    case 2:
        msk = (GPIO_PIN) K60_GPIO_Driver::PD12;
        miso = (GPIO_PIN) K60_GPIO_Driver::PD14;
        mosi = (GPIO_PIN) K60_GPIO_Driver::PD13;
        break;
    default:
        break;
    }

}
/***************************************************************************/
