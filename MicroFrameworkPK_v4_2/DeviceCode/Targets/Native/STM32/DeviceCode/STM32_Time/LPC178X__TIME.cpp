//-----------------------------------------------------------------------------
// Software that is described herein is for illustrative purposes only  
// which provides customers with programming information regarding the  
// products. This software is supplied "AS IS" without any warranties.  
// NXP Semiconductors assumes no responsibility or liability for the 
// use of the software, conveys no license or title under any patent, 
// copyright, or mask work right to the product. NXP Semiconductors 
// reserves the right to make changes in the software without 
// notification. NXP Semiconductors also make no representation or 
// warranty that such application will be suitable for the specified 
// use without further testing or modification. 
//-----------------------------------------------------------------------------
#if 1
#include <tinyhal.h>
#include "..\LPC1788_Devices.h"
//--//

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_LPC178X_TIME_Driver"
#endif

LPC178X_TIME_Driver g_LPC178X_TIME_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//


void HAL_Time_SetCompare( UINT64 CompareValue )
{
    LPC178X_TIME_Driver::SetCompareValue( CompareValue );
}

void HAL_Time_Sleep_MicroSeconds( UINT32 uSec )
{
    LPC178X_TIME_Driver::Sleep_uSec( uSec );
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled( UINT32 uSec )
{
    LPC178X_TIME_Driver::Sleep_uSec_Loop( uSec );
}

BOOL HAL_Time_Initialize()
{
    return LPC178X_TIME_Driver::Initialize();
}

BOOL HAL_Time_Uninitialize()
{
    return LPC178X_TIME_Driver::Uninitialize();
}

UINT64 HAL_Time_CurrentTicks()
{
    return LPC178X_TIME_Driver::CounterValue();
}

/// Remove this method once dependency on this are gone.
UINT64 Time_CurrentTicks()
{
    return HAL_Time_CurrentTicks();
}

INT64 HAL_Time_TicksToTime( UINT64 Ticks )
{
    return LPC178X_TIME_Driver::TicksToTime( Ticks );
}

INT64 HAL_Time_CurrentTime()
{
    return LPC178X_TIME_Driver::CurrentTime();
}


void HAL_Time_GetDriftParameters  ( INT32* a, INT32* b, INT64* c )
{
    *a = 1;
    *b = 1;
    *c = 0;
}


//--//

UINT32 CPU_SystemClock()
{
    return SYSTEM_CLOCK_HZ;
}

UINT32 CPU_TicksPerSecond()
{
    return SLOW_CLOCKS_PER_SECOND;
}

//--//

UINT64 CPU_TicksToTime( UINT64 Ticks )
{
    Ticks *= (TEN_MHZ               /SLOW_CLOCKS_TEN_MHZ_GCD);
    Ticks /= (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_TEN_MHZ_GCD);

    return Ticks;
}

UINT64 CPU_TicksToTime( UINT32 Ticks32 )
{
    UINT64 Ticks;

    Ticks  = (UINT64)Ticks32 * (TEN_MHZ               /SLOW_CLOCKS_TEN_MHZ_GCD);
    Ticks /=                   (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_TEN_MHZ_GCD);

    return Ticks;
}

//--//

UINT64 CPU_MillisecondsToTicks( UINT64 Ticks )
{
    Ticks *= (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_MILLISECOND_GCD);
    Ticks /= (1000                  /SLOW_CLOCKS_MILLISECOND_GCD);

    return Ticks;
}

UINT64 CPU_MillisecondsToTicks( UINT32 Ticks32 )
{
    UINT64 Ticks;

    Ticks  = (UINT64)Ticks32 * (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_MILLISECOND_GCD);
    Ticks /=                   (1000                  /SLOW_CLOCKS_MILLISECOND_GCD);

    return Ticks;
}

//--//



#pragma arm section code = "SectionForFlashOperations"

UINT64 __section(SectionForFlashOperations) CPU_MicrosecondsToTicks( UINT64 uSec )
{
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

UINT32 __section(SectionForFlashOperations) CPU_MicrosecondsToTicks( UINT32 uSec )
{
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

#pragma arm section code


//--//

UINT32 CPU_MicrosecondsToSystemClocks( UINT32 uSec )
{
    uSec *= (SYSTEM_CLOCK_HZ/CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ        /CLOCK_COMMON_FACTOR);

    return uSec;
}

int CPU_MicrosecondsToSystemClocks( int uSec )
{
    uSec *= (SYSTEM_CLOCK_HZ/CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ        /CLOCK_COMMON_FACTOR);

    return uSec;
}

int CPU_SystemClocksToMicroseconds( int Ticks )
{
    Ticks *= (ONE_MHZ        /CLOCK_COMMON_FACTOR);
    Ticks /= (SYSTEM_CLOCK_HZ/CLOCK_COMMON_FACTOR);

    return Ticks;
}




//--//

BOOL LPC178X_TIME_Driver::Initialize()
{
    g_LPC178X_TIME_Driver.m_lastRead    = 0;
    g_LPC178X_TIME_Driver.m_nextCompare = 0x0000FFFFFFFFFFFFull;


    if(!LPC178X_TIMER_Driver::Initialize( LPC178X_Driver::c_SystemTime_Timer, ISR, NULL )) return FALSE;

    //
    // This bootstraps the overflow mechanism.
    //
    LPC178X_TIMER_Driver::SetCompare( LPC178X_Driver::c_SystemTime_Timer, g_LPC178X_TIME_Driver.m_nextCompare );

    LPC178X_TIMER_Driver::EnableCompareInterrupt( LPC178X_Driver::c_SystemTime_Timer );

    return TRUE;
}

BOOL LPC178X_TIME_Driver::Uninitialize()
{
    if(!LPC178X_TIMER_Driver::Uninitialize( LPC178X_Driver::c_SystemTime_Timer )) return FALSE;

    return TRUE;
}

UINT64 LPC178X_TIME_Driver::CounterValue()
{
    UINT64 lastValue = g_LPC178X_TIME_Driver.m_lastRead;
    UINT32 resHigh = (UINT32)(lastValue >> 32);
    UINT32 resLow  = (UINT32)(lastValue & 0xFFFFFFFF);

    UINT32 value = LPC178X_TIMER_Driver::ReadCounter( LPC178X_Driver::c_SystemTime_Timer );

    //DEBUG_TRACE2(TRACE_COUNTER_READS,"CounterValue_Inner: %08x%08x ", resHigh, resLow);

    if(value <= resLow)
    {
        resHigh += 1;
    }
    
    g_LPC178X_TIME_Driver.m_lastRead = (UINT64)resHigh << 32 | value;

    return g_LPC178X_TIME_Driver.m_lastRead;
}

void LPC178X_TIME_Driver::SetCompareValue( UINT64 CompareValue )
{
    GLOBAL_LOCK(irq);

    g_LPC178X_TIME_Driver.m_nextCompare = CompareValue;

    UINT64 currValue = g_LPC178X_TIME_Driver.CounterValue();

    bool fForceInterrupt = false;

    if(CompareValue < currValue)
    {
        fForceInterrupt = true; //DEBUG_TRACE1(TRACE_SETCOMPARE,"ForceInterrupt: %d\r\n", __LINE__);
    }
    else
    {
            INT64 diff = CompareValue - currValue;
            INT32 nextComp;

            if(diff > 0xFFFFFFFFull)
            {
                nextComp = (UINT32)(currValue - 0xFFF); // leave some time so we don't miss the timer overlap
            }
            else
            {
                nextComp = (UINT32)currValue + (UINT32)diff; // don't worry about overflow.
            }

            LPC178X_TIMER_Driver::SetCompare( LPC178X_Driver::c_SystemTime_Timer, nextComp );

            currValue = g_LPC178X_TIME_Driver.CounterValue();

            if(CompareValue < currValue)
            {
                //
                // We missed it, make sure we process an interrupt anyway.
                //
                fForceInterrupt = true; //DEBUG_TRACE4(TRACE_SETCOMPARE,"ForceInterrupt: %d %d %08x %08x\r\n", __LINE__, diff, nextComp, lowReadNew);
            }
    }

    if(fForceInterrupt)
    {
        // Force interrupt to process this.
        LPC178X_TIMER_Driver::ForceInterrupt( LPC178X_Driver::c_SystemTime_Timer );
    }
}

//--//

int LED(int i)
{
	volatile int *p;

	p = (int *)0x20098080;
	*p |= (1 << 27);
	p = (i) ? (int *)0x2009809c : (int *)0x20098098;
	*p = (1 << 27);

}

static unsigned char LedState=0;

void LPC178X_TIME_Driver::ISR( void* Param )
{
    //DEBUG_TRACE0(TRACE_SETCOMPARE,"LPC178X_TIME_Driver::ISR\r\n");

    GLOBAL_LOCK(irq);

   // LED(LedState);
   // LedState = !LedState;

    if(LPC178X_TIMER_Driver::DidCompareHit( LPC178X_Driver::c_SystemTime_Timer ))
    {
        LPC178X_TIMER_Driver::ResetCompareHit( LPC178X_Driver::c_SystemTime_Timer );
    }

    UINT64 value = CounterValue();

    if(value >= g_LPC178X_TIME_Driver.m_nextCompare)
    {
        // this also schedules the next one, if there is one
        HAL_COMPLETION::DequeueAndExec();
    }
    else
    {
        //
        // Because we are limited in the resolution of timer,
        // resetting the compare will properly configure the next interrupt.
        //
        SetCompareValue( g_LPC178X_TIME_Driver.m_nextCompare );
    }
}

//--//

INT64 LPC178X_TIME_Driver::TicksToTime( UINT64 Ticks )
{
    return CPU_TicksToTime( Ticks );
}


INT64 LPC178X_TIME_Driver::CurrentTime()
{
    //return Time_TicksToTime(Time_CurrentTicks());
    // we collapse the above to improve perf on a high hit function

    INT64 Time = CPU_TicksToTime( CounterValue() );

#if defined(HAL_TIMEWARP)
    return s_timewarp_compensate + Time;
#else
    return Time;
#endif
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
#define LPC178X_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS 3

void __section(SectionForFlashOperations) LPC178X_TIME_Driver::Sleep_uSec( UINT32 uSec )
{
    GLOBAL_LOCK(irq);

    UINT32 value   = LPC178X_TIMER_Driver::ReadCounter( LPC178X_Driver::c_SystemTime_Timer );
    UINT32 maxDiff = CPU_MicrosecondsToTicks( uSec ) - LPC178X_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS;

    if(maxDiff <= LPC178X_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS) maxDiff  = LPC178X_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS;
    else                                                      maxDiff -= LPC178X_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS;

    while(((INT32)(LPC178X_TIMER_Driver::ReadCounter( LPC178X_Driver::c_SystemTime_Timer ) - value)) <= maxDiff);
}


// This routine is not designed for very accurate time delays.  It is designed to insure a minimum
// delay.  It is implemented using a simple timing loop that assumes the best of conditions - that
// is to say: no cache misses and no interrupts while it is executing.  Since this cannot be guaranteed,
// it is possible and even likely that this routine will take a bit longer to return than the
// requested time - but it will not return in less time.

void __section(SectionForFlashOperations) LPC178X_TIME_Driver::Sleep_uSec_Loop( UINT32 uSec )
{
    // iterations must be signed so that negative iterations will result in the minimum delay

    uSec *= (SYSTEM_CYCLE_CLOCK_HZ / CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ               / CLOCK_COMMON_FACTOR);

    // iterations is equal to the number of CPU instruction cycles in the required time minus
    // overhead cycles required to call this subroutine.
    int iterations = (int)uSec - 12;      // Subtract off call & calculation overhead

    CYCLE_DELAY_LOOP(iterations);
}

#pragma arm section code

#else

#include <tinyhal.h>
#include "..\LPC1788_Devices.h"
#include "../../CMSIS/include/lpc177x_8x_timer.h"

#define PERPH_CLOCK			48000000ul
#define RTC_TICKS_PER_SEC       1000ul
#define CLR_TICKS_PER_SEC   10000000ul
#define RTC_TICK_TO_CLR_TICK (CLR_TICKS_PER_SEC/RTC_TICKS_PER_SEC)

//--//

volatile UINT64 SysTimeTickCnt = 0;
volatile UINT64 NextCompareTick = 0x0000FFFFFFFFFFFFull;

LPC178X_TIME_Driver g_LPC178X_TIME_Driver;

int LED(int i)
{
	volatile int *p;

	p = (int *)0x20098080;
	*p |= (1 << 27);
	p = (i) ? (int *)0x2009809c : (int *)0x20098098;
	*p = (1 << 27);

}

void SysTimeISR(void *x)
{
    static int Cnt1Sec = 0;
    static unsigned char LedState=0;

    GLOBAL_LOCK(irq);

    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

    SysTimeTickCnt++;
#if 0
    Cnt1Sec++;
    if( Cnt1Sec >= (RTC_TICKS_PER_SEC))
    {
        Cnt1Sec = 0;
        LED(LedState);
        LedState = !LedState;
    }
#endif
    if( SysTimeTickCnt >= NextCompareTick)
    {
        HAL_COMPLETION::DequeueAndExec();
    }
}


BOOL HAL_Time_Initialize()
{
		TIM_TIMERCFG_Type TIM_ConfigStruct;
		TIM_MATCHCFG_Type TIM_MatchConfigStruct;

		SysTimeTickCnt = 0;
	    NextCompareTick = 0x0000FFFFFFFFFFFFull;

		TIM_Cmd(LPC_TIM0, ENABLE);
		TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;//TIM_PRESCALE_USVAL;
		TIM_ConfigStruct.PrescaleValue	= 1;
		TIM_MatchConfigStruct.MatchChannel = 0;
		TIM_MatchConfigStruct.IntOnMatch   = 1;
		TIM_MatchConfigStruct.ResetOnMatch = 1;
		TIM_MatchConfigStruct.StopOnMatch  = 0;
		TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
		TIM_MatchConfigStruct.MatchValue   = ((PERPH_CLOCK)/ RTC_TICKS_PER_SEC)-1;

		TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
		TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);

	    // start SysTick interrupt
	    if (!CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(TIMER0_IRQn), SysTimeISR, NULL))
	        return FALSE;

		TIM_Cmd(LPC_TIM0, ENABLE);

		return TRUE;
}

BOOL HAL_Time_Uninitialize()
{
    return TRUE;// LPC178X_TIME_Driver::Uninitialize();
}


UINT64 HAL_Time_CurrentTicks()
{
    return SysTimeTickCnt;
}

INT64 HAL_Time_TicksToTime(UINT64 Ticks)
{
    return (Ticks * RTC_TICK_TO_CLR_TICK);
}

INT64 HAL_Time_CurrentTime()
{
    return ( ((INT64)SysTimeTickCnt) * RTC_TICK_TO_CLR_TICK);
}

void HAL_Time_SetCompare(UINT64 CompareValue)
{
	NextCompareTick = (CompareValue*RTC_TICK_TO_CLR_TICK);
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





UINT32 CPU_SystemClock()
{
    return PERPH_CLOCK;
}

UINT32 CPU_TicksPerSecond()
{
    return RTC_TICKS_PER_SEC;
}

//--//

UINT64 CPU_MillisecondsToTicks( UINT64 Ticks )
{
    return ((Ticks * RTC_TICKS_PER_SEC)/1000);
}

UINT64 CPU_MillisecondsToTicks( UINT32 Ticks32 )
{
    return ((Ticks32 * RTC_TICKS_PER_SEC)/1000);
}

UINT64 CPU_MicrosecondsToTicks( UINT64 uSec )
{
    return ((uSec * RTC_TICKS_PER_SEC)/1000000ul);
}

UINT32 CPU_MicrosecondsToTicks( UINT32 uSec )
{
    return ((uSec * RTC_TICKS_PER_SEC)/1000000ul);
}

UINT32 CPU_MicrosecondsToSystemClocks( UINT32 uSec )
{
    return ( (PERPH_CLOCK/1000000ul) * uSec );
}

UINT64 CPU_TicksToTime( UINT64 Ticks )
{
    return (Ticks * RTC_TICK_TO_CLR_TICK );
}

UINT64 CPU_TicksToTime( UINT32 Ticks32 )
{
    return (Ticks32 * RTC_TICK_TO_CLR_TICK );
}
// -- //



#pragma arm section code = "SectionForFlashOperations"

void __section(SectionForFlashOperations) HAL_Time_Sleep_MicroSeconds(UINT32 uSec)
{
	UINT32 start = LPC_TIM0->TC;
	UINT32 end = (start + uSec) % (((PERPH_CLOCK)/ RTC_TICKS_PER_SEC));
	//wait until interrupt flag occur
	while(LPC_TIM0->TC < end);
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled(UINT32 uSec)
{
	HAL_Time_Sleep_MicroSeconds(uSec);
}

#endif
