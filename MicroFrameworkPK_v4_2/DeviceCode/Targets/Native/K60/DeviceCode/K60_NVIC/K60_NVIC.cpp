////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

extern int ARM_Vectors;

K60_NVIC_Driver g_K60_NVIC_Driver;

void CPU_INTC_Initialize()
{
    K60_NVIC_Driver::Initialize();
}

BOOL CPU_INTC_ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param)
{
    return K60_NVIC_Driver::ActivateInterrupt(Irq_Index, ISR, ISR_Param);
}

BOOL CPU_INTC_DeactivateInterrupt(UINT32 Irq_Index)
{
    return K60_NVIC_Driver::DeactivateInterrupt(Irq_Index);
}

BOOL CPU_INTC_InterruptEnable(UINT32 Irq_Index)
{
    return K60_NVIC_Driver::InterruptEnable(Irq_Index);
}

BOOL CPU_INTC_InterruptDisable(UINT32 Irq_Index)
{
    return K60_NVIC_Driver::InterruptDisable(Irq_Index);
}

BOOL CPU_INTC_InterruptEnableState(UINT32 Irq_Index)
{
    return K60_NVIC_Driver::InterruptEnableState(Irq_Index);
}

BOOL CPU_INTC_InterruptState(UINT32 Irq_Index)
{
    return K60_NVIC_Driver::InterruptState(Irq_Index);
}

// not the best solution - but to keep it in fitting with 
// MicroFramework - have one ISR that retrieves the parameter
// and then fires off the assigned user ISR
void GlobalNVICISR()
{
    UINT8 vector_index = (SCB->ICSR & 0xFF);

    if (g_K60_NVIC_Driver.intVector[vector_index])
    {
        g_K60_NVIC_Driver.intVector[vector_index](g_K60_NVIC_Driver.intParam[vector_index]);
    }
}

void K60_NVIC_Driver::Initialize()
{
    // clear all interrupts
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICER[1] = 0xFFFFFFFF;
    NVIC->ICER[2] = 0xFFFFFFFF;

    // relocate vector table to ram
    SCB->VTOR = (uint32_t) &ARM_Vectors;
}

BOOL K60_NVIC_Driver::ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param)
{
    GLOBAL_LOCK( irq);

    // point user vector to the request one
    g_K60_NVIC_Driver.intVector[Irq_Index] = ISR;
    g_K60_NVIC_Driver.intParam[Irq_Index] = ISR_Param;

    // setup vector	actual vector to global isr
    GET_VECTOR(Irq_Index) = (uint32_t) &GlobalNVICISR;

    // enable the interrupt
    InterruptEnable(Irq_Index);

    return TRUE;
}

BOOL K60_NVIC_Driver::DeactivateInterrupt(UINT32 Irq_Index)
{
    GLOBAL_LOCK( irq);

    // disable interrupt
    InterruptDisable(Irq_Index);

    // clear vector
    GET_VECTOR(Irq_Index) = 0;

    // clear user vector
    g_K60_NVIC_Driver.intVector[Irq_Index] = 0;
    g_K60_NVIC_Driver.intParam[Irq_Index] = 0;

    return TRUE;
}

BOOL K60_NVIC_Driver::InterruptEnable(UINT32 Irq_Index)
{
    GLOBAL_LOCK( irq);

    // we have some default priority's for different irqs
    if (INTC_TO_NVIC(Irq_Index) == SysTick_IRQn)
    {
        // set interrupt priority
        NVIC_SetPriority(INTC_TO_NVIC(Irq_Index), 0x02);

        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
    }
    else if (INTC_TO_NVIC(Irq_Index) == USB0_IRQn)
    {
        // set interrupt priority
        NVIC_SetPriority(INTC_TO_NVIC(Irq_Index), 0x01);

        // start the external interrupt
        NVIC_EnableIRQ(INTC_TO_NVIC(Irq_Index));
    }
    else if ((int) INTC_TO_NVIC(Irq_Index) >= 0)
    {
        // set interrupt priority
        NVIC_SetPriority(INTC_TO_NVIC(Irq_Index), 0x04);

        // start the external interrupt
        NVIC_EnableIRQ(INTC_TO_NVIC(Irq_Index));
    }

    return TRUE;
}

BOOL K60_NVIC_Driver::InterruptDisable(UINT32 Irq_Index)
{
    GLOBAL_LOCK( irq);

    // stop interrupt
    if (INTC_TO_NVIC(Irq_Index) == SysTick_IRQn)
    {
        SysTick->CTRL = 0;
    }
    else if ((int) INTC_TO_NVIC(Irq_Index) >= 0)
    {
        NVIC_DisableIRQ(INTC_TO_NVIC(Irq_Index));
    }

    return TRUE;
}

BOOL K60_NVIC_Driver::InterruptEnableState(UINT32 Irq_Index)
{
    if (INTC_TO_NVIC(Irq_Index) == SysTick_IRQn)
    {
        return SysTick->CTRL & SysTick_CTRL_ENABLE_Msk;
    }
    else if ((int) INTC_TO_NVIC(Irq_Index) >= 0)
    {
        return NVIC->ISER[(uint32_t) (INTC_TO_NVIC(Irq_Index)) >> 5] == (1 << ((uint32_t) (INTC_TO_NVIC(Irq_Index))
                & 0x1F));
    }
    else
    {
        ASSERT(FALSE);
        return FALSE;
    }
}

BOOL K60_NVIC_Driver::InterruptState(UINT32 Irq_Index)
{
    return GET_VECTOR(Irq_Index) != 0;
}
