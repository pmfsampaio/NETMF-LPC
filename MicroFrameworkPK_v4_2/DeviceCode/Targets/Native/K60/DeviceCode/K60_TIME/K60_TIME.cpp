////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <cores\arm\include\cpu.h>
#include "../K60.h"

K60_TIME_Driver g_K60_TIME_Driver;

UINT32 CPU_SystemClock()
{
    return SYSTEM_CLOCK_HZ;
}

UINT32 CPU_TicksPerSecond()
{
    return SLOW_CLOCKS_PER_SECOND;
}

//--//

UINT64 CPU_TicksToTime(UINT64 Ticks)
{
    Ticks *= (TEN_MHZ / SLOW_CLOCKS_TEN_MHZ_GCD);
    Ticks /= (SLOW_CLOCKS_PER_SECOND / SLOW_CLOCKS_TEN_MHZ_GCD);

    return Ticks;
}

UINT64 CPU_TicksToTime(UINT32 Ticks32)
{
    UINT64 Ticks;

    Ticks = (UINT64) Ticks32 * (TEN_MHZ / SLOW_CLOCKS_TEN_MHZ_GCD);
    Ticks /= (SLOW_CLOCKS_PER_SECOND / SLOW_CLOCKS_TEN_MHZ_GCD);

    return Ticks;
}

//--//

UINT64 CPU_MillisecondsToTicks(UINT64 Ticks)
{
    Ticks *= (SLOW_CLOCKS_PER_SECOND / SLOW_CLOCKS_MILLISECOND_GCD);
    Ticks /= (1000 / SLOW_CLOCKS_MILLISECOND_GCD);

    return Ticks;
}

UINT64 CPU_MillisecondsToTicks(UINT32 Ticks32)
{
    UINT64 Ticks;

    Ticks = (UINT64) Ticks32 * (SLOW_CLOCKS_PER_SECOND / SLOW_CLOCKS_MILLISECOND_GCD);
    Ticks /= (1000 / SLOW_CLOCKS_MILLISECOND_GCD);

    return Ticks;
}

//--//

UINT64 CPU_MicrosecondsToTicks(UINT64 uSec)
{
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

UINT32 CPU_MicrosecondsToTicks(UINT32 uSec)
{
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

//--//

#pragma arm section code = "SectionForFlashOperations"

UINT32 __section(SectionForFlashOperations) CPU_MicrosecondsToSystemClocks(UINT32 uSec)
{
    uSec *= (SYSTEM_CLOCK_HZ / CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ / CLOCK_COMMON_FACTOR);

    return uSec;
}

int __section(SectionForFlashOperations) CPU_MicrosecondsToSystemClocks(int uSec)
{
    uSec *= (SYSTEM_CLOCK_HZ / CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ / CLOCK_COMMON_FACTOR);

    return uSec;
}

#pragma arm section code

//--//

int CPU_SystemClocksToMicroseconds(int Ticks)
{
    Ticks *= (ONE_MHZ / CLOCK_COMMON_FACTOR);
    Ticks /= (SYSTEM_CLOCK_HZ / CLOCK_COMMON_FACTOR);

    return Ticks;
}
// -- //


BOOL HAL_Time_Initialize()
{
    return K60_TIME_Driver::Initialize();
}

BOOL HAL_Time_Uninitialize()
{
    return K60_TIME_Driver::Uninitialize();
}

UINT64 HAL_Time_CurrentTicks()
{
    return K60_TIME_Driver::CounterValue();
}

INT64 HAL_Time_TicksToTime(UINT64 Ticks)
{
    return K60_TIME_Driver::TicksToTime(Ticks);
}

INT64 HAL_Time_CurrentTime()
{
    return K60_TIME_Driver::CurrentTime();
}

void HAL_Time_SetCompare(UINT64 CompareValue)
{
    K60_TIME_Driver::SetCompareValue(CompareValue);
}

void HAL_Time_GetDriftParameters(INT32* a, INT32* b, INT64* c)
{
    *a = 1;
    *b = 1;
    *c = 0;
}

UINT64 Time_CurrentTicks()
{
    return HAL_Time_CurrentTicks();
}

#pragma arm section code = "SectionForFlashOperations"

void __section(SectionForFlashOperations) HAL_Time_Sleep_MicroSeconds(UINT32 uSec)
{
    K60_TIME_Driver::Sleep_uSec(uSec);
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled(UINT32 uSec)
{
    K60_TIME_Driver::Sleep_uSec_Loop(uSec);
}

#pragma arm section code

//--//

BOOL K60_TIME_Driver::Initialize()
{
    g_K60_TIME_Driver.m_Tick = 0;
    g_K60_TIME_Driver.m_nextCompare = c_MaxTimerValue;

    // load the SysTick timer
    SysTick->LOAD = c_MaxTimerValue;
    SysTick->VAL = 0;

    // start SysTick interrupt
    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(SysTick_IRQn), ISR, NULL))
        return FALSE;

    return TRUE;
}

BOOL K60_TIME_Driver::Uninitialize()
{
    if (!CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(SysTick_IRQn)))
        return FALSE;

    return TRUE;
}

UINT64 K60_TIME_Driver::CounterValue()
{
    GLOBAL_LOCK ( irq);
    UINT32 value = (SysTick->LOAD - SysTick->VAL);

    if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
    {
        g_K60_TIME_Driver.m_Tick += SysTick->LOAD;
    }

    return g_K60_TIME_Driver.m_Tick + value;
}

void K60_TIME_Driver::SetCompareValue(UINT64 CompareValue)
{
    g_K60_TIME_Driver.m_nextCompare = CompareValue;

    UINT64 cntr = CounterValue();

    if (cntr > CompareValue)
    {
        // reset SysTick interrupt
        SCB->ICSR |= (1 << SCB_ICSR_PENDSTSET_Pos);
    }
    else
    {
        UINT64 diff = CompareValue - cntr;

        if (diff > c_MaxTimerValue)
        {
            diff = c_MaxTimerValue;
        }

        g_K60_TIME_Driver.m_Tick = CounterValue();

        SysTick->LOAD = diff;
        SysTick->VAL = 0;

        if (CounterValue() > CompareValue)
        {
            // reset SysTick interrupt
            SCB->ICSR |= (1 << SCB_ICSR_PENDSTSET_Pos);
        }
    }
}

//--//

void K60_TIME_Driver::ISR(void* param)
{
    if (CounterValue() >= g_K60_TIME_Driver.m_nextCompare)
    {
        // this also schedules the next one, if there is one
        HAL_COMPLETION::DequeueAndExec();
    }
    else
    {
        SetCompareValue(g_K60_TIME_Driver.m_nextCompare);
    }
}

//--//

INT64 K60_TIME_Driver::TicksToTime(UINT64 Ticks)
{
    return CPU_TicksToTime(Ticks);
}

INT64 K60_TIME_Driver::CurrentTime()
{
    return CPU_TicksToTime(CounterValue());
}

//--//

//
// Since this is probably calibrated for RAM execution and it's used by the FLASH routines,
// make sure to have this function in RAM...
//
#pragma arm section code = "SectionForFlashOperations"

//
// To calibrate this constant, uncomment #define CALIBRATE_SLEEP_USEC in TinyHAL.c
//
#define K60_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS 4

void __section(SectionForFlashOperations) K60_TIME_Driver::Sleep_uSec(UINT32 uSec)
{
    GLOBAL_LOCK( irq);

    UINT32 maxDiff = CPU_MicrosecondsToTicks(uSec); // Number of ticks per microsecond
    SysTick->LOAD = maxDiff & 0xFFFFFF;

    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
        ;
}

// This routine is not designed for very accurate time delays.  It is designed to insure a minimum
// delay.  It is implemented using a simple timing loop that assumes the best of conditions - that
// is to say: turbo mode, cache, and branch prediction enabled, no cache misses and no interrupts
// while it is executing.  Since this cannot be guaranteed, it is possible and even likely that
// this routine will take a bit longer to return than the requested time - but it will not return
// in less time.

void __section(SectionForFlashOperations) K60_TIME_Driver::Sleep_uSec_Loop(UINT32 uSec)
{
    // Iterations must be signed so that negative iterations will result in the minimum delay
    uSec *= (SYSTEM_CYCLE_CLOCK_HZ / CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ / CLOCK_COMMON_FACTOR);

    // Iterations is equal to the number of CPU instruction cycles in the required time minus
    // Overhead cycles required to call this subroutine.
    int iterations = (int) uSec - 14; // Subtract off call & calculation overhead

    CYCLE_DELAY_LOOP2 (iterations);
}

#pragma arm section code
