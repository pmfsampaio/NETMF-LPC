////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\LPC1788_Devices.h"
#include "../../CMSIS/include/lpc177x_8x_timer.h"

#define NEW

#define SYSTEM_CLOCK_HZ                 10000000
#define SLOW_CLOCKS_PER_SECOND          10000000
#define CLOCK_COMMON_FACTOR             100000
#define SLOW_CLOCKS_TEN_MHZ_GCD         10000
#define SLOW_CLOCKS_MILLISECOND_GCD     1000

LPC178X_TIME_Driver g_LPC178X_TIME_Driver;

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

#ifdef NEW

int LED(int i)
{
	volatile int *p;

	p = (int *)0x20098080;
	*p |= (1 << 27);
	p = (i) ? (int *)0x2009809c : (int *)0x20098098;
	*p = (1 << 27);

}

volatile UINT64 SysTimeTickCnt = 0;
volatile UINT64 NextCompareTick = 0x0000FFFFFFFFFFFFull;

void SysTimeISR(void *x)
{
    static int Cnt1Sec = 0;
    static unsigned char LedState=0;

    GLOBAL_LOCK(irq);

    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

    SysTimeTickCnt++;
    Cnt1Sec++;
    if( Cnt1Sec >= 100)
    {
        Cnt1Sec = 0;
        LED(LedState);
        LedState = !LedState;
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, (LedState^=GPIO_PIN_3));
    }
    if( SysTimeTickCnt > NextCompareTick)
    {
        HAL_COMPLETION::DequeueAndExec();
    }
}
#endif


BOOL HAL_Time_Initialize()
{
#ifdef NEW
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct ;
		SysTimeTickCnt = 0;
	    NextCompareTick = 0x0000FFFFFFFFFFFFull;

//	    SysCtlPeripheralClockGating(true);
//	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//	    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
//	    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);

		TIM_Cmd(LPC_TIM0, ENABLE);
		TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;//TIM_PRESCALE_USVAL;
		TIM_ConfigStruct.PrescaleValue	= 60;//(60000000/1000)-1;//1000;
		TIM_MatchConfigStruct.MatchChannel = 0;
		TIM_MatchConfigStruct.IntOnMatch   = 1;
		TIM_MatchConfigStruct.ResetOnMatch = 1;
		TIM_MatchConfigStruct.StopOnMatch  = 0;
		TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
		TIM_MatchConfigStruct.MatchValue   = ((60000000 / 60)/ 1000)-1; // 10ms

		TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
		TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);

	    // start SysTick interrupt
	    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(TIMER0_IRQn), SysTimeISR, NULL))
	        return FALSE;

		TIM_Cmd(LPC_TIM0, ENABLE);

//	    TimerConfigure(  TIMER2_BASE,TIMER_CFG_16_BIT_PAIR | TIMER_CFG_A_ONE_SHOT | TIMER_CFG_B_PERIODIC );
//	    TimerPrescaleSet(TIMER2_BASE,TIMER_B,32);
//	    TimerLoadSet(    TIMER2_BASE,TIMER_B, SysCtlClockGet()/32/RTC_TICKS_PER_SEC);
//	    TimerIntEnable(  TIMER2_BASE,TIMER_TIMB_TIMEOUT);
//	    TimerDisable(    TIMER2_BASE, TIMER_A);
//	    TimerEnable(     TIMER2_BASE, TIMER_B);
//	    TimerIntRegister(TIMER2_BASE,TIMER_B,SysTimeISR);
//	    IntEnable(       INT_TIMER2B);

		return TRUE;
#else
    return LPC178X_TIME_Driver::Initialize();
#endif
}

BOOL HAL_Time_Uninitialize()
{
    return TRUE;// LPC178X_TIME_Driver::Uninitialize();
}

UINT64 HAL_Time_CurrentTicks()
{
    return SysTimeTickCnt * 100; //LPC178X_TIME_Driver::CounterValue();
}

INT64 HAL_Time_TicksToTime(UINT64 Ticks)
{
    return (Ticks * 100); //LPC178X_TIME_Driver::TicksToTime(Ticks);
}

INT64 HAL_Time_CurrentTime()
{
    return ( ((INT64)SysTimeTickCnt) * 100); //LPC178X_TIME_Driver::CurrentTime();
}

void HAL_Time_SetCompare(UINT64 CompareValue)
{
	NextCompareTick = (CompareValue/100);
	//LPC178X_TIME_Driver::SetCompareValue(CompareValue);
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
	UINT32 start = LPC_TIM0->TC;
	UINT32 end = (start + uSec) % (((60000000 / 60)/ 1000));
	//wait until interrupt flag occur
	while(LPC_TIM0->TC < end);
	//LPC178X_TIME_Driver::Sleep_uSec(uSec);
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled(UINT32 uSec)
{
	HAL_Time_Sleep_MicroSeconds(uSec);
	// LPC178X_TIME_Driver::Sleep_uSec_Loop(uSec);
}
