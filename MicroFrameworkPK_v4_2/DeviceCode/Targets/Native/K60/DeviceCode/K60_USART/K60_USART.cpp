////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

K60_USART_Driver g_K60_USART_Driver;

BOOL CPU_USART_Initialize(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue)
{
    return K60_USART_Driver::Initialize(ComPortNum, BaudRate, Parity, DataBits, StopBits, FlowValue);
}

BOOL CPU_USART_Uninitialize(int ComPortNum)
{
    return K60_USART_Driver::Uninitialize(ComPortNum);
}

BOOL CPU_USART_TxBufferEmpty(int ComPortNum)
{
    return K60_USART_Driver::TxBufferEmpty(ComPortNum);
}

BOOL CPU_USART_TxShiftRegisterEmpty(int ComPortNum)
{
    return K60_USART_Driver::TxShiftRegisterEmpty(ComPortNum);
}

void CPU_USART_WriteCharToTxBuffer(int ComPortNum, UINT8 c)
{
    K60_USART_Driver::WriteCharToTxBuffer(ComPortNum, c);
}

void CPU_USART_TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable)
{
    K60_USART_Driver::TxBufferEmptyInterruptEnable(ComPortNum, Enable);
}

BOOL CPU_USART_TxBufferEmptyInterruptState(int ComPortNum)
{
    return K60_USART_Driver::TxBufferEmptyInterruptState(ComPortNum);
}

void CPU_USART_RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable)
{
    K60_USART_Driver::RxBufferFullInterruptEnable(ComPortNum, Enable);
}

BOOL CPU_USART_RxBufferFullInterruptState(int ComPortNum)
{
    return K60_USART_Driver::RxBufferFullInterruptState(ComPortNum);
}

BOOL CPU_USART_TxHandshakeEnabledState(int comPort)
{
    return K60_USART_Driver::TxHandshakeEnabledState(comPort);
}

void CPU_USART_ProtectPins(int ComPortNum, BOOL On)
{
    return K60_USART_Driver::ProtectPins(ComPortNum, On);
}

UINT32 CPU_USART_PortsCount()
{
    return K60_USART_Driver::c_COM_COUNT;
}

void CPU_USART_GetPins(int ComPortNum, GPIO_PIN& rxPin, GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin)
{
    return K60_USART_Driver::GetPins(ComPortNum, rxPin, txPin, ctsPin, rtsPin);
}

BOOL CPU_USART_SupportNonStandardBaudRate(int ComPortNum)
{
    return FALSE;
}

void CPU_USART_GetBaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz)
{
    return K60_USART_Driver::GetBaudrateBoundary(ComPortNum, maxBaudrateHz, minBaudrateHz);
}

BOOL CPU_USART_IsBaudrateSupported(int ComPortNum, UINT32& BaudrateHz)
{
    return K60_USART_Driver::IsBaudrateSupported(ComPortNum, BaudrateHz);
}

UART_Type* K60_USART_Driver::GetUARTFromPort(int ComPortNum)
{
    switch (ComPortNum)
    {
    case c_COM1:
        return UART0;
    case c_COM2:
        return UART1;
    case c_COM3:
        return UART2;
    case c_COM4:
        return UART3;
    default:
        ASSERT(FALSE)
        ;
        return NULL;
    }
}

void K60_USART_Driver::UARTn_IntHandler(void* param)
{
    GLOBAL_LOCK( irq);

    int ComPortNum = (int) param;

    char c;

    UART_Type* uart = GetUARTFromPort(ComPortNum);

    // get as many characters as we can from Rx FIFO
    while (RxBufferFullInterruptState(ComPortNum))
    {
        c = uart->D;

        USART_AddCharToRxBuffer(ComPortNum, c);
        Events_Set(SYSTEM_EVENT_FLAG_COM_IN);
    }

    // fill up tx FIFO will as many characters as we have
    while (TxBufferEmpty(ComPortNum))
    {
        if (USART_RemoveCharFromTxBuffer(ComPortNum, c))
        {
            // output char to USART
            WriteCharToTxBuffer(ComPortNum, c);
        }
        else
        {
            // disable transmit interrupt
            uart->C2 &= ~UART_C2_TCIE_MASK;
            break;
        }

        Events_Set(SYSTEM_EVENT_FLAG_COM_OUT);
    }
}

BOOL K60_USART_Driver::Initialize(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue)
{
    GLOBAL_LOCK( irq);

    UART_Type* uart = GetUARTFromPort(ComPortNum);

    // start the clock before we tweak the UART
    switch (ComPortNum)
    {
    case c_COM1:
        SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
        break;
    case c_COM2:
        SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
        break;
    case c_COM3:
        SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
        break;
    case c_COM4:
        SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
        break;
    default:
        ASSERT(FALSE)
        ;
    }

    // determine clock speed
    int periph_clk_hz = CPU_SystemClock() / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24) + 1);

    // Configure the UART for 8-bit mode, no parity
    uart->C1 = 0;

    // reset the control registers
    uart->C3 = 0x00U;
    uart->C5 = 0x00U;

    // setup baud
    register UINT16 ubd = (UINT16) (periph_clk_hz / (BaudRate * 16));
    UINT8 temp = uart->BDH & ~(UART_BDH_SBR(0x1F));
    uart->BDH = temp | UART_BDH_SBR(((ubd & 0x1F00) >> 8));
    uart->BDL = (UINT8) (ubd & UART_BDL_SBR_MASK);

    // improve baud
    register UINT16 brfa = (((periph_clk_hz * 3200) / (BaudRate * 16)) - (ubd * 32));
    temp = uart->C4 & ~(UART_C4_BRFA(0x1F));
    uart->C4 = temp | UART_C4_BRFA(brfa);

    // disable RTS/CTS
    uart->MODEM = 0x00U;

    // disable infrared
    uart->IR = 0x00U;

    // trigger interrupt when transmit buffer is empty
    uart->TWFIFO = 0x00U;

    // trigger interrupt when receive buffer has one character
    uart->RWFIFO = 0x01U;

    // setup Tx/Rx FIFO buffer sizes
    uart->SFIFO = UART_CFIFO_TXOFE_MASK | UART_CFIFO_RXUFE_MASK;
    uart->CFIFO = UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK;
    uart->PFIFO &= (unsigned char) ~(unsigned char) 0xEEU;

    // setup the ISR
    switch (ComPortNum)
    {
    case c_COM1:
        CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(UART0_RX_TX_IRQn), UARTn_IntHandler, (void*) ComPortNum);
        break;
    case c_COM2:
        CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(UART1_RX_TX_IRQn), UARTn_IntHandler, (void*) ComPortNum);
        break;
    case c_COM3:
        CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(UART2_RX_TX_IRQn), UARTn_IntHandler, (void*) ComPortNum);
        break;
    case c_COM4:
        CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(UART3_RX_TX_IRQn), UARTn_IntHandler, (void*) ComPortNum);
        break;
    default:
        ASSERT(FALSE)
        ;
    }

    // enable the UART register flags
    ProtectPins(ComPortNum, FALSE);

    // enable the UART
    uart->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);

    return TRUE;
}

BOOL K60_USART_Driver::Uninitialize(int ComPortNum)
{
    GLOBAL_LOCK( irq);

    UART_Type* uart = GetUARTFromPort(ComPortNum);

    // disable interrupts restore pins
    ProtectPins(ComPortNum, TRUE);

    // disable the UART
    uart->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK | UART_C2_TIE_MASK);

    // setup the ISR
    switch (ComPortNum)
    {
    case c_COM1:
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(UART0_RX_TX_IRQn));
        break;
    case c_COM2:
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(UART1_RX_TX_IRQn));
        break;
    case c_COM3:
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(UART2_RX_TX_IRQn));
        break;
    case c_COM4:
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(UART3_RX_TX_IRQn));
        break;
    default:
        ASSERT(FALSE)
        ;
    }

    return TRUE;
}

BOOL K60_USART_Driver::TxBufferEmpty(int ComPortNum)
{
    return (0 != (GetUARTFromPort(ComPortNum)->S1 & UART_S1_TDRE_MASK));
}

BOOL K60_USART_Driver::TxShiftRegisterEmpty(int ComPortNum)
{
    return (0 != (GetUARTFromPort(ComPortNum)->S1 & UART_S1_TC_MASK));
}

void K60_USART_Driver::WriteCharToTxBuffer(int ComPortNum, UINT8 c)
{
    GetUARTFromPort(ComPortNum)->D = c;
}

void K60_USART_Driver::TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable)
{
    GLOBAL_LOCK( irq);

    if (Enable)
    {
        GetUARTFromPort(ComPortNum)->C2 |= UART_C2_TCIE_MASK;
    }
    else
    {
        GetUARTFromPort(ComPortNum)->C2 &= ~UART_C2_TCIE_MASK;
    }
}

BOOL K60_USART_Driver::TxBufferEmptyInterruptState(int ComPortNum)
{
    return (0 != (GetUARTFromPort(ComPortNum)->C2 & UART_C2_TCIE_MASK));
}

void K60_USART_Driver::RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable)
{
    GetUARTFromPort(ComPortNum)->C2 |= UART_C2_RIE_MASK;
}

BOOL K60_USART_Driver::RxBufferFullInterruptState(int ComPortNum)
{
    return (0 != (GetUARTFromPort(ComPortNum)->S1 & UART_S1_RDRF_MASK));
}

BOOL K60_USART_Driver::TxHandshakeEnabledState(int comPortNum)
{
    // TODO
    return TRUE;
}

void K60_USART_Driver::ProtectPins(int ComPortNum, BOOL On)
{
    GLOBAL_LOCK( irq);

    GPIO_PIN rxPin, txPin, ctsPin, rtsPin;

    GetPins(ComPortNum, rxPin, txPin, ctsPin, rtsPin);

    if (On)
    {
        RxBufferFullInterruptEnable(ComPortNum, FALSE);
        TxBufferEmptyInterruptEnable(ComPortNum, FALSE);

        // configure the GPIO as input to save power
        CPU_GPIO_EnableInputPin(rxPin, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
        CPU_GPIO_EnableInputPin(txPin, FALSE, NULL, GPIO_INT_NONE, RESISTOR_DISABLED);
    }
    else
    {
        // configure the GPIO as UART
        CPU_GPIO_DisablePin(rxPin, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_3);
        CPU_GPIO_DisablePin(txPin, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_3);

        // enable receive ISR
        RxBufferFullInterruptEnable(ComPortNum, TRUE);
        TxBufferEmptyInterruptEnable(ComPortNum, TRUE);
    }
}

void K60_USART_Driver::GetPins(int comPort, GPIO_PIN& rxPin, GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin)
{
    // setup the GPIO as UART
    switch (comPort)
    {
    case 0:
        rxPin = (GPIO_PIN) K60_GPIO_Driver::PB16;
        txPin = (GPIO_PIN) K60_GPIO_Driver::PB17;
        ctsPin = GPIO_PIN_NONE;
        rtsPin = GPIO_PIN_NONE;
        break;

    case 1:
        rxPin = (GPIO_PIN) K60_GPIO_Driver::PC3;
        txPin = (GPIO_PIN) K60_GPIO_Driver::PC4;
        ctsPin = GPIO_PIN_NONE;
        rtsPin = GPIO_PIN_NONE;
        break;

    case 2:
        rxPin = (GPIO_PIN) K60_GPIO_Driver::PD2;
        txPin = (GPIO_PIN) K60_GPIO_Driver::PD3;
        ctsPin = GPIO_PIN_NONE;
        rtsPin = GPIO_PIN_NONE;
        break;

    case 3:
        rxPin = (GPIO_PIN) K60_GPIO_Driver::PC16;
        txPin = (GPIO_PIN) K60_GPIO_Driver::PC17;
        ctsPin = GPIO_PIN_NONE;
        rtsPin = GPIO_PIN_NONE;
        break;

    default:
        return;
    }
}

void K60_USART_Driver::GetBaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz)
{
    maxBaudrateHz = c_MAX_BAUDRATE;
    minBaudrateHz = c_MIN_BAUDRATE;
}

BOOL K60_USART_Driver::IsBaudrateSupported(int ComPortNum, UINT32 & BaudrateHz)
{
    return TRUE;
}
