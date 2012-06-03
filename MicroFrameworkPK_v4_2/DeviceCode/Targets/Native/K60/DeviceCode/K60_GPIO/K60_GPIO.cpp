////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "c_Gpio_Attributes_K60"
#endif

const UINT8 __section(rodata) K60_GPIO_Driver::c_Gpio_Attributes[K60_GPIO_Driver::c_MaxPins] =
{ GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 00 Port 0
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 01
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 02
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 03
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 04
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 05
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 06
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 07
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 08
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 09
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 10
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 11
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 12
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 13
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 14
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 15
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 16
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 17
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 18
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 19
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 20
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 21
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 22
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 23
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 24
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 25
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 26
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 27
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 28
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 29
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 30
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 31

        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  32   (port 1)
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  33
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  34
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  35
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  36
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  37
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  38
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  39
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  40
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  41
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  42
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  43
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  44
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  45
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  46
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  47
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  48
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  49
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  50
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  51
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  52
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  53
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  54
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  55
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  56
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  57
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  58
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  59
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  60
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  61
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  62
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  63

        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  64   (port 2)
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  65
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  66
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  67
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  68
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  69
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  70
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  71
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  72
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  73
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  74
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  75
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  76
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  77
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  78
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  79
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  80
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  81
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  82
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  83
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  84
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  85
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  86
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  87
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  88
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  89
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  90
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  91
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  92
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  93
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  94
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  95

        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  96   (port 3)
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  97
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  98
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  99
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  100
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  101
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  102
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  103
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  104
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  105
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  106
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  107
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  108
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  109
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  110
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  111
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  112
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  113
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  114
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  115
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  116
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  117
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  118
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  119
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  120
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  121
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  122
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  123
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  124
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  125
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  126
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  127

        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  128   (port 4)
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  129
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  130
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  131
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  132
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  133
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  134
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  135
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  136
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  137
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  138
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  139
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  140
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  141
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  142
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  143
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  144
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  145
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  146
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  147
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  148
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  149
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  150
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  151
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  152
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  153
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  154
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  155
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  156
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  157
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  158
        GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  159
        };

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_K60_GPIO_Driver"
#endif

K60_GPIO_Driver g_K60_GPIO_Driver;
K60_GPIO_Driver g_K60_PINSEL_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//

BOOL CPU_GPIO_Initialize()
{
    return K60_GPIO_Driver::Initialize();
}

BOOL CPU_GPIO_Uninitialize()
{
    return K60_GPIO_Driver::Uninitialize();
}

UINT32 CPU_GPIO_Attributes(GPIO_PIN Pin)
{
    return K60_GPIO_Driver::Attributes(Pin);
}

void CPU_GPIO_DisablePin(GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction)
{
    K60_GPIO_Driver::DisablePin(Pin, ResistorState, Direction, AltFunction);
}

void CPU_GPIO_EnableOutputPin(GPIO_PIN Pin, BOOL InitialState)
{
    K60_GPIO_Driver::EnableOutputPin(Pin, InitialState);
}

BOOL CPU_GPIO_EnableInputPin(GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR,
        GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState)
{
    return K60_GPIO_Driver::EnableInputPin(Pin, GlitchFilterEnable, ISR, 0, IntEdge, ResistorState);
}

BOOL CPU_GPIO_EnableInputPin2(GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR,
        void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState)
{
    return K60_GPIO_Driver::EnableInputPin(Pin, GlitchFilterEnable, ISR, ISR_Param, IntEdge, ResistorState);
}

BOOL CPU_GPIO_GetPinState(GPIO_PIN Pin)
{
    return K60_GPIO_Driver::GetPinState(Pin);
}

void CPU_GPIO_SetPinState(GPIO_PIN Pin, BOOL PinState)
{
    K60_GPIO_Driver::SetPinState(Pin, PinState);
}

INT32 CPU_GPIO_GetPinCount()
{
    return K60_GPIO_Driver::GetPinCount();
}

void CPU_GPIO_GetPinsMap(UINT8* pins, size_t size)
{
    K60_GPIO_Driver::GetPinsMap(pins, size);
}

UINT8 CPU_GPIO_GetSupportedResistorModes(GPIO_PIN pin)
{
    return K60_GPIO_Driver::c_GPIO_ResistorMode;
}

UINT8 CPU_GPIO_GetSupportedInterruptModes(GPIO_PIN pin)
{
    return K60_GPIO_Driver::c_GPIO_InterruptMode;
}

BOOL CPU_GPIO_PinIsBusy(GPIO_PIN Pin)
{
    return K60_GPIO_Driver::PinIsBusy(Pin);
}

BOOL CPU_GPIO_ReservePin(GPIO_PIN Pin, BOOL fReserve)
{
    return K60_GPIO_Driver::ReservePin(Pin, fReserve);
}

UINT32 CPU_GPIO_GetDebounce()
{
    return K60_GPIO_Driver::GetDebounce();
}

BOOL CPU_GPIO_SetDebounce(INT64 debounceTimeMilliseconds)
{
    return K60_GPIO_Driver::SetDebounce(debounceTimeMilliseconds);
}

//--//

///////////////////////////////////////////////////////////////////////////////
//  Initialize
///////////////////////////////////////////////////////////////////////////////
BOOL K60_GPIO_Driver::Initialize()
{
    int i;

    // initialize the interrupt information
    {
        PIN_ISR_DESCRIPTOR* pinIsr = g_K60_GPIO_Driver.m_PinIsr;

        for (i = 0; i < c_MaxPins; i++)
        {
            pinIsr->m_pin = i;
            pinIsr->m_intEdge = GPIO_INT_NONE;
            pinIsr->m_isr = STUB_ISRVector;
            pinIsr->m_param = NULL;
            pinIsr->m_flags = 0;
            pinIsr++;
        }
    }

    for (i = 0; i < c_MaxPorts; i++)
    {
        g_K60_GPIO_Driver.m_PinReservationInfo[i] = 0;
    }

    // turn on all port clocks
    SIM->SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK
            | SIM_SCGC5_PORTE_MASK;

    // register interrupt handler for all ports
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(PORTA_IRQn), PORTn_ISR, (void*) 0))
        return FALSE;
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(PORTB_IRQn), PORTn_ISR, (void*) 1))
        return FALSE;
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(PORTC_IRQn), PORTn_ISR, (void*) 2))
        return FALSE;
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(PORTD_IRQn), PORTn_ISR, (void*) 3))
        return FALSE;
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(PORTE_IRQn), PORTn_ISR, (void*) 4))
        return FALSE;

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  Uninitialize
///////////////////////////////////////////////////////////////////////////////

BOOL K60_GPIO_Driver::Uninitialize()
{
    GLOBAL_LOCK( irq);

    // uninitialize the interrupt information
    {
        PORT_Type* portReg;
        int i;

        for (i = 0; i < c_MaxPorts; i++)
        {
            portReg = PortToPortReg(i);
            portReg->ISFR = 0xFFFFFFFF;
        }
    }

    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(PORTA_IRQn)))
        return FALSE;
    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(PORTB_IRQn)))
        return FALSE;
    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(PORTC_IRQn)))
        return FALSE;
    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(PORTD_IRQn)))
        return FALSE;
    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(PORTE_IRQn)))
        return FALSE;

    // turn off all port clocks
    SIM->SCGC5 = 0;

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  Attributes
///////////////////////////////////////////////////////////////////////////////

UINT32 K60_GPIO_Driver::Attributes(GPIO_PIN pin)
{
    ASSERT(pin < c_MaxPins);

    if (pin < c_MaxPins)
    {
        return c_Gpio_Attributes[pin];
    }

    return GPIO_ATTRIBUTE_NONE;
}

///////////////////////////////////////////////////////////////////////////////
//  DisablePin
///////////////////////////////////////////////////////////////////////////////

void K60_GPIO_Driver::DisablePin(GPIO_PIN pin, GPIO_RESISTOR resistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction)
{
    // Configure the pin to its alternate function.
    GLOBAL_LOCK( irq);

    UINT32 bit = PinToBit(pin);
    UINT32 port = PinToPort(pin);
    PORT_Type* portReg = PortToPortReg(port);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    portReg->PCR[bit] = PORT_PCR_MUX(AltFunction) | PORT_PCR_DSE_MASK;

    switch (resistorState)
    {
    case RESISTOR_DISABLED:
        portReg->PCR[bit] &= ~PORT_PCR_PE_MASK;
        break;
    case RESISTOR_PULLUP:
        portReg->PCR[bit] |= PORT_PCR_PS_MASK;
        portReg->PCR[bit] |= PORT_PCR_PE_MASK;
        break;
    case RESISTOR_PULLDOWN:
        portReg->PCR[bit] &= ~PORT_PCR_PS_MASK;
        portReg->PCR[bit] |= PORT_PCR_PE_MASK;
        break;
    }

    PIN_ISR_DESCRIPTOR& pinIsr = g_K60_GPIO_Driver.m_PinIsr[pin];

    pinIsr.m_intEdge = GPIO_INT_NONE;
    pinIsr.m_isr = STUB_ISRVector;
    pinIsr.m_param = NULL;

}

///////////////////////////////////////////////////////////////////////////////
//  EnableOutputPin
///////////////////////////////////////////////////////////////////////////////

void K60_GPIO_Driver::EnableOutputPin(GPIO_PIN pin, BOOL initialState)
{
    ASSERT(pin < c_MaxPins);

    GLOBAL_LOCK( irq);

    UINT32 bit = PinToBit(pin);
    UINT32 port = PinToPort(pin);
    PORT_Type* portReg = PortToPortReg(port);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    portReg->PCR[bit] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;

    if (initialState)
        gpioReg->PDOR &= ~GPIO_PDOR_PDO(GPIO_PIN_BIT(bit));
    else
        gpioReg->PDOR |= GPIO_PDOR_PDO(GPIO_PIN_BIT(bit));

    gpioReg->PDDR |= GPIO_PDDR_PDD(GPIO_PIN_BIT(bit));
}

///////////////////////////////////////////////////////////////////////////////
//  EnableInputPin
///////////////////////////////////////////////////////////////////////////////
BOOL K60_GPIO_Driver::EnableInputPin(GPIO_PIN pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR,
        void* Param, GPIO_INT_EDGE intEdge, GPIO_RESISTOR resistorState)
{
    ASSERT(pin < c_MaxPins);

    GLOBAL_LOCK( irq);

    UINT32 bit = PinToBit(pin);
    UINT32 port = PinToPort(pin);
    PORT_Type* portReg = PortToPortReg(port);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    switch (resistorState)
    {
    case RESISTOR_DISABLED:
        portReg->PCR[bit] &= ~PORT_PCR_PE_MASK;
        break;
    case RESISTOR_PULLUP:
        portReg->PCR[bit] |= PORT_PCR_PS_MASK;
        portReg->PCR[bit] |= PORT_PCR_PE_MASK;
        break;
    case RESISTOR_PULLDOWN:
        portReg->PCR[bit] &= ~PORT_PCR_PS_MASK;
        portReg->PCR[bit] |= PORT_PCR_PE_MASK;
        break;
    }

    portReg->PCR[bit] = PORT_PCR_MUX(1);
    gpioReg->PDDR &= GPIO_PDDR_PDD(~GPIO_PIN_BIT(bit));

    PIN_ISR_DESCRIPTOR& pinIsr = g_K60_GPIO_Driver.m_PinIsr[pin];

    pinIsr.m_intEdge = intEdge;
    pinIsr.m_isr = (ISR != NULL) ? ISR : STUB_ISRVector;
    pinIsr.m_param = Param;
    pinIsr.m_flags = (GlitchFilterEnable == TRUE) ? PIN_ISR_DESCRIPTOR::c_Flags_Debounce : 0;
    pinIsr.m_status = 0;

    if (ISR)
    {
        switch (intEdge)
        {
        case GPIO_INT_NONE:
            break;
        case GPIO_INT_EDGE_LOW:
            portReg->PCR[bit] |= PORT_PCR_IRQC(0xA);
            break;
        case GPIO_INT_LEVEL_LOW:
            portReg->PCR[bit] |= PORT_PCR_IRQC(0x8);
            break;
        case GPIO_INT_EDGE_HIGH:
            portReg->PCR[bit] |= PORT_PCR_IRQC(0x9);
            break;
        case GPIO_INT_LEVEL_HIGH:
            portReg->PCR[bit] |= PORT_PCR_IRQC(0x6);
            break;
        case GPIO_INT_EDGE_BOTH:
            portReg->PCR[bit] |= PORT_PCR_IRQC(0x9 | 0xA);
            break;
        default:
            ASSERT (0)
            ;
            return FALSE;
        }
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  GetPinState
///////////////////////////////////////////////////////////////////////////////

BOOL K60_GPIO_Driver::GetPinState(GPIO_PIN pin)
{
    ASSERT(pin < c_MaxPins);

    UINT32 bit = PinToBit(pin);
    UINT32 port = PinToPort(pin);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    return (0 == (gpioReg->PDIR & GPIO_PDIR_PDI(GPIO_PIN_BIT(bit))));
}

///////////////////////////////////////////////////////////////////////////////
//  SetPinState
///////////////////////////////////////////////////////////////////////////////
void K60_GPIO_Driver::SetPinState(GPIO_PIN pin, BOOL pinState)
{
    ASSERT(pin < c_MaxPins);

    UINT32 bit = PinToBit(pin);
    UINT32 port = PinToPort(pin);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    if (pinState)
        gpioReg->PDOR &= ~GPIO_PDOR_PDO(GPIO_PIN_BIT(bit));
    else
        gpioReg->PDOR |= GPIO_PDOR_PDO(GPIO_PIN_BIT(bit));
}

///////////////////////////////////////////////////////////////////////////////
//  PinIsBusy
///////////////////////////////////////////////////////////////////////////////
BOOL K60_GPIO_Driver::PinIsBusy(GPIO_PIN pin)
{
    UINT32 port = PinToPort(pin);
    UINT32 bit = PinToBit(pin);
    UINT32& res = g_K60_GPIO_Driver.m_PinReservationInfo[port];

    return (res & GPIO_PIN_BIT(bit)) != 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//  ReservePin
///////////////////////////////////////////////////////////////////////////////
BOOL K60_GPIO_Driver::ReservePin(GPIO_PIN pin, BOOL fReserve)
{
    GLOBAL_LOCK( irq);

    UINT32 port = PinToPort(pin);
    UINT32 bit = PinToBit(pin);
    UINT32& res = g_K60_GPIO_Driver.m_PinReservationInfo[port];
    UINT32 mask = (fReserve ? 1u : 0u) << bit;

    if ((res & (1u << bit)) == mask)
        return FALSE;

    if (fReserve)
    {
        res |= (1u << bit);
    }
    else
    {
        res &= ~(1u << bit);
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  GetDebounce
///////////////////////////////////////////////////////////////////////////////
UINT32 K60_GPIO_Driver::GetDebounce()
{
    return CPU_TicksToTime(g_K60_GPIO_Driver.m_DebounceTicks) / 10000;
}

///////////////////////////////////////////////////////////////////////////////
//  SetDebounce
///////////////////////////////////////////////////////////////////////////////
BOOL K60_GPIO_Driver::SetDebounce(INT64 debounceTimeMilliseconds)
{
    if (debounceTimeMilliseconds < c_MinDebounceTimeMs || c_MaxDebounceTimeMs < debounceTimeMilliseconds)
    {
        return FALSE;
    }

    g_K60_GPIO_Driver.m_DebounceTicks = CPU_MillisecondsToTicks((UINT32) debounceTimeMilliseconds);

    return TRUE;
}

INT32 K60_GPIO_Driver::GetPinCount()
{
    return c_MaxPins;
}

void K60_GPIO_Driver::GetPinsMap(UINT8* pins, size_t size)
{
    const UINT8* src = c_Gpio_Attributes;
    UINT8* dst = pins;
    UINT32 maxpin = c_MaxPins;

    if (size == 0)
        return;
    while ((size--) && (maxpin--))
    {
        *dst = *src;
        ++dst;
        ++src;
    }
}

void K60_GPIO_Driver::PIN_ISR_DESCRIPTOR::Fire(void* arg)
{
    PIN_ISR_DESCRIPTOR* desc = (PIN_ISR_DESCRIPTOR*) arg;

    desc->m_isr(desc->m_pin, (desc->m_status & c_Status_AllowHighEdge) != 0, desc->m_param);

    if (desc->m_intEdge == GPIO_INT_EDGE_BOTH)
    {
        desc->m_status ^= PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge | PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;
    }
}

void K60_GPIO_Driver::PIN_ISR_DESCRIPTOR::HandleDebounce(BOOL edge)
{
    ASSERT_IRQ_MUST_BE_OFF();

    UINT32 count = c_DebounceCount;

    // we implement debouce by reading the pin a finite number of times
    while (--count > 0)
    {
        if (GetPinState(m_pin) != edge)
        {
            // it was a glitch
            return;
        }
    }

    // debounce test passed
    Fire(this);
}

void K60_GPIO_Driver::STUB_ISRVector(GPIO_PIN Pin, BOOL PinState, void* Param)
{
}

void K60_GPIO_Driver::PORTn_ISR(void* param)
{
    int port = (int) param;

    // fire off each change, one at a time
    UINT32 bitMask = 0x00000001;
    UINT32 bitIndex = 0;

    PORT_Type* portReg = PortToPortReg(port);
    GPIO_Type* gpioReg = PortToGPIOReg(port);

    UINT32 interruptsActive = portReg->ISFR;

    while (interruptsActive)
    {
        while ((interruptsActive & bitMask) == 0)
        {
            bitMask <<= 1;
            ++bitIndex;
        }

        //--//

        GPIO_PIN pin = BitToPin(bitIndex, port);

        PIN_ISR_DESCRIPTOR& pinIsr = g_K60_GPIO_Driver.m_PinIsr[pin];

        if (pinIsr.m_intEdge != GPIO_INT_NONE)
        {
            BOOL negativeEdge;

            if (pinIsr.m_intEdge == GPIO_INT_EDGE_BOTH)
            {
                // which edge are we interrupting on?
                if (pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge)
                {
                    // is pin not set ( == 1 )
                    if (!(0 == (gpioReg->PDIR & GPIO_PDIR_PDI(bitMask))))
                        negativeEdge = TRUE;
                    else
                        return; // A pair of falling edge and rising edge may have been lost, exit without any handling
                }
                else if (pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge)
                {
                    // is pin set ( == 0 )
                    if ((0 == (gpioReg->PDIR & GPIO_PDIR_PDI(bitMask))))
                        negativeEdge = FALSE;
                    else
                        return; // A pair of rising edge and falling edge may have been lost, exit without any handling
                }
            }
            else
            {
                if (pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge)
                {
                    // is pin not set ( == 1 )                     
                    if (!(0 == (gpioReg->PDIR & GPIO_PDIR_PDI(bitMask))))
                    {
                        negativeEdge = TRUE;
                    }
                    else
                    {
                        return; // throw out the unexpected falling edge
                    }
                }
                else if (pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge)
                {
                    // is pin set ( == 0 )
                    if ((0 == (gpioReg->PDIR & GPIO_PDIR_PDI(bitMask))))
                    {
                        negativeEdge = FALSE;
                    }
                    else
                    {
                        return; // throw out the unexpected rising edge
                    }
                }
            }

            // send the interrupted state to the higher level
            if (pinIsr.m_flags & PIN_ISR_DESCRIPTOR::c_Flags_Debounce)
            {
                pinIsr.HandleDebounce(!negativeEdge);
            }
            else
            {
                pinIsr.Fire((void*) &pinIsr);
            }
        }

        // remove the pin from the local check
        interruptsActive ^= bitMask;
    }

    // clear interrupts
    portReg->ISFR = 0xFFFFFFFF;
}

