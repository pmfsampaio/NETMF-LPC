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

#include <tinyhal.h>
#include "..\LPC24XX.h"
	
///////////////////////////////////////////////////////////////////////////////

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_LPC24XX_ADC_Driver"
#endif
	
#pragma arm section zidata = "SectionForInternalSRAM"
LPC24XX_ADC_Driver g_LPC24XX_ADC_Driver;
#pragma arm section zidata

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif


//--//

void LPC24XX_ADC_Driver::Initialize( UINT32 SampleFrequencyHz )
{
	LPC24XX::SYSCON().PCONP |= LPC24XX_SYSCON::ENABLE_AD;
	
	//SET PINSEL1 to ADC
	CPU_GPIO_DisablePin( LPC24XX_ADC::c_ADC_IN5, RESISTOR_DISABLED, GPIO_ATTRIBUTE_NONE, GPIO_ALT_MODE_3 );
	
	LPC24XX_ADC& ADC = LPC24XX::ADC();
	UINT32 cfg = ( 1 << 5 ) | 					// CH5
			(( 72000000 / SampleFrequencyHz - 1 ) << 8 ) |  // CLKDIV = Fpclk / 1000000 - 1
			( 0 << 16 ) | 						// BURST = 0, no BURST, software controlled
			( 0 << 17 ) |  						// CLKS = 0, 11 clocks/10 bits
			( 1 << 21 ) |  						// PDN = 1, normal operation
			( 0 << 22 ) |  						// TEST1:0 = 00
			( 0 << 24 ) |  						// START = 0 A/D conversion stops
			( 0 << 27 );						/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */
	ADC.AD0CR = cfg;
}

void LPC24XX_ADC_Driver::Uninitialize()
{
	// Disable the timer in case it is running
	g_LPC24XX_ADC_Driver.Off();
}

BOOL LPC24XX_ADC_Driver::On()
{
//	LPC24XX::SYSCON().PCONP |= LPC24XX_SYSCON::ENABLE_AD;
//	g_LPC24XX_ADC_Driver.initialized = true;

#if 0
	if(g_LPC24XX_ADC_Driver.SampleTimeInCycles == 0) return FALSE;
	
	ASSERT(LPC24XX_ADC::Timer < LPC24XX_TIMER_Driver::c_MaxTimers);

    GLOBAL_LOCK(irq);

    if(g_LPC24XX_TIMER_Driver.m_configured[LPC24XX_ADC::Timer] == TRUE) return FALSE;

    //--//
	
	//rise IRQ priority to the highest one. this guarantees delay < execution time of the longest ISR in the system
	LPC24XX_VIC& VIC = LPC24XX::VIC();	
	VIC.VECTPRIORITY[LPC24XX_TIMER::getIntNo(LPC24XX_ADC::Timer)] = 0;

    if(!CPU_INTC_ActivateInterrupt( LPC24XX_TIMER::getIntNo(LPC24XX_ADC::Timer) , LPC24XX_ADC_Driver::ISR, NULL )) return FALSE;
    

    LPC24XX_TIMER& TIMER = LPC24XX::TIMER(LPC24XX_ADC::Timer);

	//Reset and Enable timer
	TIMER.TCR = 0x00000002;
    TIMER.TCR = LPC24XX_TIMER::TCR_TEN;
	
	//set prescaler to 0, we only need very short time intervals
	TIMER.PR = 0x00000000;
	
	//load MATCH REGISTER with TARGET time (expressed in cycles, since PR=0)
	TIMER.MR0 = g_LPC24XX_ADC_Driver.SampleTimeInCycles;
		
	//set MatchControlRegister to generate INTR (bit 0) on MR0 == TC and reset timer (bit 1) immediately 
	//this way the IRQ will be generated every X us, regardless of when the ISR for the last one is actually executed
	
	TIMER.MCR = 0x00000003; 
	
    //--//

    g_LPC24XX_TIMER_Driver.m_configured[LPC24XX_ADC::Timer] = TRUE;
#endif
    return TRUE;
}

BOOL LPC24XX_ADC_Driver::Off()
{
//	g_LPC24XX_ADC_Driver.initialized = false;
#if 0
	if(g_LPC24XX_ADC_Driver.SampleTimeInCycles == 0) return FALSE;
	  
	ASSERT(LPC24XX_ADC::Timer < LPC24XX_TIMER_Driver::c_MaxTimers);

    GLOBAL_LOCK(irq);

    if(g_LPC24XX_TIMER_Driver.m_configured[LPC24XX_ADC::Timer] == FALSE) return FALSE;

    //--//
	
	//reset IRQ priority
	LPC24XX_VIC& VIC = LPC24XX::VIC();	
	VIC.VECTPRIORITY[LPC24XX_TIMER::getIntNo(LPC24XX_ADC::Timer)] = 0xF;
	
    if(!CPU_INTC_DeactivateInterrupt( LPC24XX_TIMER::getIntNo(LPC24XX_ADC::Timer) )) return FALSE;

    LPC24XX_TIMER& TIMER = LPC24XX::TIMER( LPC24XX_ADC::Timer );

    //Reset timer
    TIMER.TCR = 0x2;
	//Reset Match0 and Match Control regs
	TIMER.MR0 = 0x0;
	TIMER.MCR = 0x0;
    // disable Timer
    TIMER.TCR = 0;

    //--//

    
	g_LPC24XX_TIMER_Driver.m_configured[LPC24XX_ADC::Timer] = FALSE;

	#if defined(TIME_ADC_ISR)
	
	UINT16 maxSamplesUsed = 6400;
	long double avgInterTicks = 0.0;
	long double sigmaInterTicks = 0.0;
	double tickTimeMicroSecs = 1000000.0/CPU_TicksPerSecond();
	debug_printf("Tick length = %eus\r\n",tickTimeMicroSecs);
	for(int i = 0; i < maxSamplesUsed-1; i++)
	{
		/*if(i<100)
		{
			debug_printf("execStartTicks[%u]=%u\r\n",i+1,execStartTicks[i+1]);
			debug_printf("-\r\nexecStartTicks[%u]=%u\r\n",i,execStartTicks[i]);
			debug_printf("=\r\n%u\r\n\r\n",(execStartTicks[i+1] - execStartTicks[i]));
		}*/
		avgInterTicks += (execStartTicks[i+1]-execStartTicks[i]);
		//debug_printf("avgInterTicks = %e\r\n",avgInterTicks);
	}
	avgInterTicks=avgInterTicks/(maxSamplesUsed-1);
	debug_printf("Avg Time between ISR executions = %eus\r\n",avgInterTicks*tickTimeMicroSecs);
	
	for(int i = 0; i < maxSamplesUsed; i++)
	{
		sigmaInterTicks += pow((execStartTicks[i+1] - execStartTicks[i])-avgInterTicks,2);
	}
	sigmaInterTicks = sqrt(sigmaInterTicks/maxSamplesUsed);
	debug_printf("Std Deviation in Times = %eus\r\n",sigmaInterTicks*tickTimeMicroSecs);
	
	#endif
	
	#if defined(MONITOR_BUFFER_LEVEL)
	for(bufLevelMarkCount = 0; bufLevelMarkCount<80; bufLevelMarkCount++)
		debug_printf("%u\r\n",bufferLevel[bufLevelMarkCount]);
	bufLevelMarkCount = 0;
	#endif
#endif
    return TRUE;
}

//return whether the ADC is converting or not
BOOL LPC24XX_ADC_Driver::IsEnabled()
{
	return g_LPC24XX_ADC_Driver.initialized;
}

//Samples in the buffer
UINT32 LPC24XX_ADC_Driver::GetSample()
{
	LPC24XX_ADC& ADC = LPC24XX::ADC();

	/* Clear all SEL bits */
    ADC.AD0CR &= 0xFFFFFF00;
	/* switch channel, start A/D convert */
    ADC.AD0CR |= (1 << 24) | (1 << 5);

    UINT32 val;
    while (1) {
    	val = ADC.AD0ADR5;
    	if (val & (1 << 31)) break;
    }

    ADC.AD0CR &= 0xF8FFFFFF;
    if (val & (1 << 30)) return 0;

	return val >> 6 & 0x3FF;
}

#if 0
#pragma arm section code = "SectionForInternalFLASH"
//Output one sample when the timer goes off.
void LPC24XX_ADC_Driver::ISR(void* Param)
{	
#if defined(TIME_ADC_ISR)
	if(timesRun<TEST_SAMPLES_NUM)
	{
		execStartTicks[timesRun] = /*(UINT32)*/Time_CurrentTicks();
		timesRun++;
	}
#endif

#if defined(MONITOR_BUFFER_LEVEL)
	bufferMonitorSampleCount++;
	if(!(bufferMonitorSampleCount%2000)) /*mark the buf lvl 4 times a sec @ 8kHz*/
	{
		bufferLevel[bufLevelMarkCount] =(g_LPC24XX_ADC_Driver.FrameCount*100)/ADC_FRAME_BUFFERS_NUM;
		if(++bufLevelMarkCount==80)
			bufLevelMarkCount=0;
	}
#endif

	
	LPC24XX_TIMER& TIMER = LPC24XX::TIMER(LPC24XX_ADC::Timer);
		
	//Reset match interrupt
	TIMER.IR = LPC24XX_TIMER::MR0_RESET;
	
	LPC24XX_ADC& ADC = LPC24XX::ADC();
	
	if(g_LPC24XX_ADC_Driver.SampleCount>0)
	{
		if((g_LPC24XX_ADC_Driver.nextSampleRead>=g_LPC24XX_ADC_Driver.SamplesInFrame[g_LPC24XX_ADC_Driver.nextFrameRead])
			||(g_LPC24XX_ADC_Driver.nextSampleRead>=ADC_FRAME_BUFFER_SIZE_SAMPLES))	//if we reached the end of frame buffer
		{
			g_LPC24XX_ADC_Driver.nextSampleRead = 0;
			g_LPC24XX_ADC_Driver.nextFrameRead++;												//jump to the next frame
			g_LPC24XX_ADC_Driver.FrameCount--;
			if(g_LPC24XX_ADC_Driver.nextFrameRead>=ADC_FRAME_BUFFERS_NUM)							//if we reached the last frame
				g_LPC24XX_ADC_Driver.nextFrameRead = 0;												//jump back to the first one
			//debug_printf("\r\nFrame %u:\r\n", (g_LPC24XX_ADC_Driver.nextFrameRead>=ADC_FRAME_BUFFERS_NUM)?0:g_LPC24XX_ADC_Driver.nextFrameRead);
		}
		
		
			
		// switch to unsigned
		// zero out the reserved bits
		// add the bias bit 
		// write to ADCR
		unsigned short sample = 0x7FFF+(signed long)g_LPC24XX_ADC_Driver.SamplesBuffer[g_LPC24XX_ADC_Driver.nextFrameRead*ADC_FRAME_BUFFER_SIZE_SAMPLES+g_LPC24XX_ADC_Driver.nextSampleRead];
		ADC.ADCR = ADC.TRADE_SPEED_FOR_POWER | (ADC.VALUE_MASK & (sample));
		
		g_LPC24XX_ADC_Driver.SampleCount--;
		g_LPC24XX_ADC_Driver.nextSampleRead++;
	}
	else
	{
		//buffer empty, zero out the output
		ADC.ADCR = 0x7FC0;
	}
}
#pragma arm section code

#endif
