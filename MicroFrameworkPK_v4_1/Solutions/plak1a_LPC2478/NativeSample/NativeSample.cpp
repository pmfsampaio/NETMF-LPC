////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <tinyhal.h>

void PostManagedEvent( UINT8 category, UINT8 subCategory, UINT16 data1, UINT32 data2 )
{
}

#ifdef TCPIP_LWIP 
void  Network_PostEvent(UINT32 evt, UINT32 data)
{
}
#endif

//#define TEST_DAC
//#define TIME_DAC_ISR
//#define TEST_JOYSTICK
//#define TEST_SST39WF

#if defined(TEST_DAC)
	
	#include "test_short.c"
	//#include "A.c"
	
	#if !defined(TEST_SAMPLES_NUM)
		#error	TEST_SAMPLES_NUM must be defined in test file
	#endif
	
	#define CUTOUT 1
	
	#define OUT_FREQ 8000		//8kHz output
	
	#if defined(TIME_DAC_ISR)
		extern UINT32 execStartTicks[TEST_SAMPLES_NUM];
		extern UINT32 timesRun;
		#include <math.h>
	#endif
	
	extern LPC24XX_DAC_Driver g_LPC24XX_DAC_Driver;
#endif

HAL_DECLARE_NULL_HEAP();

void resetDACISRTiming()
{
	#if defined(TIME_DAC_ISR)
	timesRun = 0;
	for(int i=0; i <TEST_SAMPLES_NUM; i++)
	{
		execStartTicks[i]=0;
	}
	#endif
}

UINT16 IRQ_INDEX_TEST[32];
UINT16 IRQ_TEST_OUTPUT[8192];
static int irq_count;

#if defined(TEST_JOYSTICK)
BOOL wait_joystick;
#endif

void hijackingISR(void* arg)
{
	UINT16* index = (UINT16*) arg;
	if(irq_count < 8192) IRQ_TEST_OUTPUT[irq_count] = *index;
	irq_count++;
}

BOOL hijackISRs()
{
	for(int irqIndex=0; irqIndex < 32; irqIndex++)
	{
		IRQ_INDEX_TEST[irqIndex] = irqIndex;
		if /*leave untouched ISRs needed for testing*/
		(
			irqIndex == LPC24XX_TIMER::getIntNo(LPC24XX_DAC::Timer)||
			irqIndex == LPC24XX_TIMER::getIntNo(LPC24XX_Driver::c_SystemTime_Timer)/*||
			irqIndex == LPC24XX_VIC::c_IRQ_INDEX_UART2 ||
			irqIndex == LPC24XX_VIC::c_IRQ_INDEX_DBG_COM_RX*/||
			irqIndex == LPC24XX_VIC::c_IRQ_INDEX_DBG_COM_TX
		)
			break;
		if(!CPU_INTC_ActivateInterrupt( irqIndex , hijackingISR, (void*)&(IRQ_INDEX_TEST[irqIndex]) )) return FALSE;
	}
	return true;
}

BOOL restoreISRs()
{
	//CPU_INTC_ActivateInterrupt(LPC24XX_VIC::c_IRQ_INDEX_EMAC, LPC24XX_EMAC_interrupt, NULL);
	//CPU_INTC_ActivateInterrupt( LPC24XX_VIC::c_IRQ_INDEX_I2C0, &LPC24XX_I2C_Driver::ISR, NULL );
	//CPU_INTC_ActivateInterrupt( LPC24XX_TIMER::getIntNo(Timer) , LPC24XX_TIMER::ISR, ISR_Param );
	//CPU_INTC_ActivateInterrupt( LPC24XX_VIC::c_IRQ_INDEX_WDT, LPC24XX_WATCHDOG_Driver::ISR, NULL );
	//CPU_INTC_ActivateInterrupt( LPC24XX_VIC::c_IRQ_INDEX_DBG_COM_TX, LPC24XX_USART_Driver::UART_IntHandler,  (void *)3);  
	return true;
}



void displayRunTestResults()
{
	#if defined(TIME_DAC_ISR)
	UINT16 maxSamplesUsed = TEST_SAMPLES_NUM/5;
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
}

void csvRunTestResults()
{
	#if defined(TIME_DAC_ISR)
	UINT16 maxSamplesUsed = TEST_SAMPLES_NUM;
	
	double tickTimeMicroSecs = 1000000.0/CPU_TicksPerSecond();
	debug_printf("\r\n\r\n==========================================\r\n");
	for(int i = 0; i < maxSamplesUsed; i++)
	{
		debug_printf("%f,%f\r\n",execStartTicks[i]*tickTimeMicroSecs,(execStartTicks[i+1]-execStartTicks[i])*tickTimeMicroSecs);
		//debug_printf("%f\r\n",execStartTicks[i]*tickTimeMicroSecs);
	}
	debug_printf("\r\n\r\n==========================================\r\n");
	#endif
}

void joystickISR(GPIO_PIN Pin, BOOL PinState, void* Param)
{
#if defined(TEST_JOYSTICK)
	
	debug_printf("JOYSTICK PRESSED\r\nPIN\t= %u\r\nSTATE\t= %u\r\n", Pin, PinState);
	//wait_joystick = false;
#endif
}

#if defined(TEST_TOUCH)

BOOL TSC2007_Driver_Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc) {
	CPU_GPIO_SetDebounce(3);

	if (!::CPU_GPIO_EnableInputPin2((2*32)+10/*g_TSC2007_Config.InterruptPin*/, TRUE,
			touchIsrProc, NULL, GPIO_INT_EDGE_BOTH, RESISTOR_PULLUP)) {
		return FALSE;
	}
	LPC24XX_I2C& I2C = LPC24XX::I2C();

	CPU_GPIO_DisablePin(LPC24XX_I2C::c_I2C_SDA, RESISTOR_DISABLED, 0,
			GPIO_ALT_MODE_1);
	CPU_GPIO_DisablePin(LPC24XX_I2C::c_I2C_SCL, RESISTOR_DISABLED, 0,
			GPIO_ALT_MODE_1);

	// enable the I2c module
	I2C.I2CONSET = LPC24XX_I2C::I2EN;

	I2C.I2SCLH = 26;//g_TSC2007_Config.clk;
	I2C.I2SCLL = 25;//g_TSC2007_Config.clk;

	return TRUE;
}

//#define ENABLE_I2C_AA ( I2C.I2CONSET |= (0x1 << 2))
//#define DISABLE_I2C_AA ( I2C.I2CONCLR = (0x1 << 2))
//#define I2C_BIT_RATE(rate) (I2SCLH = I2SCLL = ((unsigned int)(PERIPH_FREQ/2/rate)+10))
//#define I2C_SEND_START (I2C.I2CONSET |= (0x1 << 5))
//#define I2C_SEND_STOP (I2C.I2CONSET = (0x1 << 4))
//#define I2C_CLR_START (I2C.I2CONCLR = (0x1 << 5))
//#define I2C_CLR_SI (I2C.I2CONCLR = (0x1 << 3))

int TSC2007_Driver_Transfer(I2C_WORD *txBuffer, int txBufferLen, I2C_WORD *rxBuffer,
		int rxBufferLen) {
	unsigned char code;
	int i2c_rxcharRemaining = rxBufferLen;
	unsigned char transferComplete = 0;
	unsigned char i2c_RdnWr = 0;
	int i2c_pos = 0;
	int i2c_rxWrPos = 0;
	int i2c_charRemaining = txBufferLen;
	int i2c_rxComplete = 0;

	LPC24XX_I2C& I2C = LPC24XX::I2C();

	I2C.I2CONSET |= (0x1 << 5);
	while (!transferComplete) {
		code = I2C.I2STAT;
		switch (code) {
		/***** MASTER TX MODE *****/
		case 0x08: // First Start Transmitted
		case 0x10: // Repeated Start
			// Write address and tell if it is read or write
			I2C.I2DAT = 0x90 | i2c_RdnWr;
			I2C.I2CONCLR = (0x1 << 3); // Clear SI
			break;
		case 0x18: // Start + Wr sent, ACK received
		case 0x20: // Start + Wr sent, Not ACK received
		case 0x28: // Data unsigned char sent, ACK recieved
		case 0x30: // Data unsigned char sent, Not Ack received
			if (i2c_charRemaining > 0) {
				I2C.I2DAT = txBuffer[i2c_pos++];
				i2c_charRemaining--;
				I2C.I2CONCLR = (0x1 << 5);
			} else if (i2c_rxcharRemaining == 0) {
				I2C.I2CONSET = (0x1 << 4); // Send Stop
				I2C.I2CONCLR = (0x1 << 5);
				transferComplete = 1;
			} else { // Change from master_tx to master_rx
				i2c_RdnWr = (~i2c_RdnWr) & 0x1;
				i2c_pos = 0;
				i2c_rxWrPos = 0;
				i2c_rxComplete = 0;
				I2C.I2CONSET |= (0x1 << 5);
			}
			I2C.I2CONCLR = (0x1 << 3); // ClearTC_CR_Y SI
			break;
		case 0x38: // Arbitration Lost, try again
			I2C.I2CONSET |= (0x1 << 5);
			I2C.I2CONCLR = (0x1 << 3); // Clear SI
			break;
			/***** MASTER RX MODE *****/
		case 0x40: // SLA+R HAS BEEN SENT; ACK RECEIVED
			if (i2c_rxcharRemaining != 0)
				I2C.I2CONSET |= (0x1 << 2);
			else
				I2C.I2CONCLR = (0x1 << 2);
			I2C.I2CONCLR = (0x1 << 3) | (0x1 << 5); // Clear SI and START
			break;
		case 0x48: // SLA+R has been send; not ack received
			// Try again
			I2C.I2CONSET |= (0x1 << 5);
			I2C.I2CONCLR = (0x1 << 3);
			break;

		case 0x50: // DATA unsigned char RECEIVED, ACK RETURNED
			rxBuffer[i2c_rxWrPos] = I2C.I2DAT;
			i2c_rxWrPos++;
			i2c_rxcharRemaining--;
			if (i2c_rxcharRemaining != 0)
				I2C.I2CONSET |= (0x1 << 2);
			else
				I2C.I2CONCLR = (0x1 << 2);
			I2C.I2CONCLR = (0x1 << 3) | (0x1 << 5); // Clear SI and START
			break;
		case 0x58: // DATA unsigned char RECEIVED; NOT ACT RETURNED
			i2c_rxComplete = 1; // Done receiving all requested data
			transferComplete = 1;
			I2C.I2CONCLR = (0x1 << 5);
			I2C.I2CONSET = (0x1 << 4);
			I2C.I2CONCLR = (0x1 << 3);
			break;
		}
	}
	return 0;
}

void TSC2007_Driver_GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState,
		int* pSource, int* pUnCalX, int* pUnCalY) {
	*pTipState = 0;
	*pUnCalX = 0;
	*pUnCalY = 0;
	*pSource = 0;

	static bool stylusDown = false;

	/// Apparently there's a lot of noise from the touch hardware. We will take several
	/// independent measures to compensate for them:
	/// 1. Settle down time (instead of reading right away, wait few moments) --> ReadsToIgnore
	/// 2. Read multiple samples (read a number of them, and then take average) --> ReadsPerSample.
	///

	UINT16 i = 0;
	UINT16 totalReads = 3;//g_TouchPanel_Sampling_Settings.ReadsToIgnore			+ g_TouchPanel_Sampling_Settings.ReadsPerSample;

	int x = -1;
	int y = -1;

	INT32 validReadCount = 0;

	UINT32 d1 = 0xFFFF;
	UINT32 d2 = 0;

	I2C_WORD writeBufferY[1] = { 0xc8 };
	I2C_WORD readBufferY[2] = { 0, 0 };
	I2C_WORD writeBufferX[1] = { 0xd8 };
	I2C_WORD readBufferX[2] = { 0, 0 };

	for (i = 0; i < totalReads; i++) {
		TSC2007_Driver_Transfer(writeBufferY, 1, readBufferY, 2);
		d2 = d1;

		d1 = readBufferY[0];
		d1 <<= 8;
		d1 |= readBufferY[1];
		d1 >>= 4;

		if (d1 == d2)
			break;
	}

	y = d1;

	d1 = 0xFFFF;
	d2 = 0;
	for (i = 0; i < 2/*g_TouchPanel_Sampling_Settings.ReadsPerSample*/; i++) {
		TSC2007_Driver_Transfer(writeBufferX, 1, readBufferX, 2);

		d2 = d1;

		d1 = readBufferX[0];
		d1 <<= 8;
		d1 |= readBufferX[1];
		d1 >>= 4;

		if (d1 == d2)
			break;
	}

	x = d1;

	if (x >= 3800) {
		validReadCount = 0;
	} else {
		validReadCount = 1;
	}

	if (stylusDown) {
		*pTipState |= TouchSamplePreviousDownFlag;
	}

	if (validReadCount > 0) {
		*pTipState |= TouchSampleValidFlag;
		*pUnCalX = x;
		*pUnCalY = y;
		*pTipState |= TouchSampleDownFlag;
		stylusDown = true;
	} else {
		*pUnCalX = -1;
		*pUnCalY = -1;
		stylusDown = false;
	}
}

void TouchIsrProc( GPIO_PIN pin, BOOL pinState, void* context )
{
    TOUCH_PANEL_SAMPLE_FLAGS flags;
    INT32 ux = 0; /// Uncalibrated x.
    INT32 uy = 0; /// Uncalibrated y.
    INT32 source = 0;

    if(pinState == false) //g_TouchPanel_Sampling_Settings.ActivePinStateForTouchDown)
    {
    	lcd_printf("Contact Down: ");
        TSC2007_Driver_GetPoint(&flags, &source, &ux, &uy);
        lcd_printf("%d, %d\r\n", ux, uy);
    }
    else
    {
//    	lcd_printf("Contact Up: ");
    }

}


void bottonISR(GPIO_PIN Pin, BOOL PinState, void* Param)
{
    TOUCH_PANEL_SAMPLE_FLAGS flags;
    INT32 ux = 0; /// Uncalibrated x.
    INT32 uy = 0; /// Uncalibrated y.
    INT32 source = 0;

        TSC2007_Driver_GetPoint(&flags, &source, &ux, &uy);
    	lcd_printf("\r\nPRESSED PIN = %u STATE = %u {%d,%d}\r\n", Pin, PinState, ux, uy);
}
#endif

void ApplicationEntryPoint()
{
	
#if defined(TEST_DAC)
	UINT32 FramesNum = g_LPC24XX_DAC_Driver.GetBufferFrameCapacity();
	if (DAC_FRAME_BUFFERS_NUM!=FramesNum)
	{
		debug_printf( "Error, BufferFrameCapacity != DAC_FRAME_BUFFERS_NUM: %d != %d.\r\n", FramesNum, DAC_FRAME_BUFFERS_NUM );
	}
		
	UINT32 nextInFrameOffset=0;
	UINT16 frameLength = MAX_DECODED_FRAME_SIZE/2;
	short* frameSignedStart = NULL;

	
	LPC24XX_VIC& VIC = LPC24XX::VIC();
	
	/*debug_printf("VIC INTRSEL = 0x%08x\r\n", VIC.INTRSEL);
	VIC.INTRSEL |= 1 << LPC24XX_TIMER::getIntNo(LPC24XX_DAC::Timer);
	debug_printf("new VIC INTRSEL = 0x%08x\r\n", VIC.INTRSEL);*/
	
	VIC.VECTPRIORITY[LPC24XX_TIMER::getIntNo(LPC24XX_DAC::Timer)] = 0;
		
	for(int i= 0; i< 32; i++)
	{
		debug_printf("PRIO INTR%02d = %d \r\n", i,VIC.VECTPRIORITY[i]);
	}
	
		
	debug_printf( "Init DAC, 8kHz output.\r\n" );
	g_LPC24XX_DAC_Driver.Initialize(OUT_FREQ); 
	


	
	debug_printf( "BUFFER PRE-FILL TEST.\r\n" );
	debug_printf( "Adding frames to the DAC driver buffer: " );


	debug_printf("total frames to be added = %d\r\n", TEST_SAMPLES_NUM/MAX_DECODED_FRAME_SIZE-CUTOUT);
	debug_printf("DAC frame buffers available = %d\r\n", DAC_FRAME_BUFFERS_NUM);
	if(DAC_FRAME_BUFFERS_NUM<(TEST_SAMPLES_NUM/MAX_DECODED_FRAME_SIZE-CUTOUT))
		debug_printf("ONLY THE FIRST %d FRAMES OF THE SAMPLE WILL BE PLAYED.\r\n", DAC_FRAME_BUFFERS_NUM);
	
	while(nextInFrameOffset+(MAX_DECODED_FRAME_SIZE*CUTOUT) < TEST_SAMPLES_NUM)
	{
		//if(i%(1024*256)) continue;
		
			
		frameSignedStart = (short*)(bin_data+nextInFrameOffset);
			
		if(g_LPC24XX_DAC_Driver.AddFrame(frameSignedStart, frameLength))
		{
			debug_printf( "     done.\r\n" );
			nextInFrameOffset+=MAX_DECODED_FRAME_SIZE;
		}
		else
		{
			debug_printf( "Buffer full, starting playout.\r\n");
			break;
		}
	}

	resetDACISRTiming();
	
		
	debug_printf( "DAC.On() in 2 seconds\r\n");
	Events_WaitForEvents( 0, 2000 );
	
	if(!hijackISRs())
		return;
	
	if(g_LPC24XX_DAC_Driver.On())
	{
		//debug_printf( "Done. 2sec wait.\r\n" ); don't output to avoid adding serial activity during the test
	}
	else
	{
		debug_printf( "FAILED.\r\n" );
	}
	
	while(g_LPC24XX_DAC_Driver.GetBufferLevel()>0)
	{
		//debug_printf("Samples left: %d\r\n", g_LPC24XX_DAC_Driver.GetBufferLevel());
		//debug_printf("Frames left:  %d\r\n", g_LPC24XX_DAC_Driver.GetFramesLeft());
	}
	
	//stop logging interrupts before starting to output again
	
	int finalIrqCount = irq_count;
	irq_count = 8192;
	
	Events_WaitForEvents( 0, 5000 );
	
	if(!restoreISRs())
		return;
	
	debug_printf("%d frames left.\r\n", g_LPC24XX_DAC_Driver.GetFramesLeft());
	debug_printf("Final IRQ count = %u\r\n", finalIrqCount);
	debug_printf( "BUFFER PRE-FILL TEST OVER.\r\n");
	
	displayRunTestResults();
	debug_printf("CSV DATA OUTPUT FOLLOWS\r\n");
	//csvRunTestResults();
	
	
	
	debug_printf("\r\nPARALLEL BUFFER FILL TEST\r\n" );
	
	
	Events_WaitForEvents( 0, 3000 );
	
	debug_printf( "DAC.Off()\r\n");
	if(g_LPC24XX_DAC_Driver.Off())
	{
		debug_printf( "Done.\r\n" );
	}
	else
	{
		debug_printf( "FAILED.\r\n" );
	}
	
	debug_printf( "Uninit DAC\r\n");
	g_LPC24XX_DAC_Driver.Uninitialize();
	debug_printf( "Done.\r\n");
	
	debug_printf( "Init DAC, 8kHz output.\r\n" );
	g_LPC24XX_DAC_Driver.Initialize(OUT_FREQ); 
	
	resetDACISRTiming();
	
	debug_printf( "DAC.On() in 2 seconds\r\n");
	Events_WaitForEvents( 0, 2000 );
	if(g_LPC24XX_DAC_Driver.On())
	{
		//debug_printf( "Done.\r\n" );
	}
	else
	{
		debug_printf( "FAILED.\r\n" );
	}
	
	debug_printf( "Adding frames to the DAC driver buffer: " );

	nextInFrameOffset=0;
	
	debug_printf("total frames to be added = %d\r\n", TEST_SAMPLES_NUM/MAX_DECODED_FRAME_SIZE-CUTOUT);
	
	//FILL JUST ONCE 
	while(nextInFrameOffset+(MAX_DECODED_FRAME_SIZE*CUTOUT) < TEST_SAMPLES_NUM)
	{
		//if(i%(1024*256)) continue;
		
			
		frameSignedStart = (short*)(bin_data+nextInFrameOffset);
			
		if(g_LPC24XX_DAC_Driver.AddFrame(frameSignedStart, frameLength))
		{
			debug_printf( "     done.\r\n" );
			nextInFrameOffset+=MAX_DECODED_FRAME_SIZE;
		}
		else
		{
			//debug_printf( "FAIL.\r\n");
		}
	}	
	
	while(g_LPC24XX_DAC_Driver.GetBufferLevel()>0)
	{
		//debug_printf("Samples left: %d\r\n", g_LPC24XX_DAC_Driver.GetBufferLevel());
		//debug_printf("Frames left:  %d\r\n", g_LPC24XX_DAC_Driver.GetFramesLeft());
	}
	
	Events_WaitForEvents( 0, 3000 );
	
	displayRunTestResults();
	
	debug_printf("CSV DATA OUTPUT FOLLOWS\r\n");
	csvRunTestResults();
	
	/*CONTINUOUS REFILL with samples
	while(true)
	{
		//if(i%(1024*256)) continue;
		
			
		frameSignedStart = (short*)(bin_data+nextInFrameOffset);
			
		if(g_LPC24XX_DAC_Driver.AddFrame(frameSignedStart, frameLength))
		{
			//debug_printf( "     done.\r\n" );
			nextInFrameOffset+=MAX_DECODED_FRAME_SIZE;
			if(nextInFrameOffset+(MAX_DECODED_FRAME_SIZE*CUTOUT)>=TEST_SAMPLES_NUM)
				nextInFrameOffset = 0;
		}
		else
		{
			//debug_printf( "FAIL.\r\n");
		}
		debug_printf("Samples left: %d\r\n", g_LPC24XX_DAC_Driver.GetBufferLevel());
		debug_printf("Frames left:  %d\r\n", g_LPC24XX_DAC_Driver.GetFramesLeft());
	}*///end continuous refill

		
	debug_printf("%d frames left.\r\n", g_LPC24XX_DAC_Driver.GetFramesLeft());
	debug_printf( "PARALLEL BUFFER FILL TEST OVER.\r\n\r\n" );
	
	
	//Events_WaitForEvents( 0, 10000 );
		
	debug_printf( "DAC.Off()\r\n");
	if(g_LPC24XX_DAC_Driver.Off())
	{
		debug_printf( "Done.\r\n" );
	}
	else
	{
		debug_printf( "FAILED.\r\n" );
	}
	
	debug_printf( "Uninit DAC()\r\n");
	g_LPC24XX_DAC_Driver.Uninitialize();
	debug_printf( "Done.\r\n");
	
#endif


#if defined(TEST_JOYSTICK)
	extern LPC24XX_GPIO_Driver g_LPC24XX_GPIO_Driver;
	
	wait_joystick = true;
	
	for(UINT32 pin = LPC24XX_GPIO::c_P2_22; pin < LPC24XX_GPIO::c_P2_28; pin++)
	{
		if(pin == LPC24XX_GPIO::c_P2_24)
			continue;
		if(!g_LPC24XX_GPIO_Driver.EnableInputPin( pin, false,  joystickISR, NULL, GPIO_INT_EDGE_HIGH, (GPIO_RESISTOR)2 ))
		{
			debug_printf("Cannot enable pin %u as INPUT pin.\r\n", pin);
			exit(1);
		}
		debug_printf("Enabled pin %u as INPUT pin.\r\n", pin);
	}
	
	while(wait_joystick){};
	
#endif
	
#if	0 //TEST FLASH
    while(1)
    {
       lcd_printf("Test FLASH\r\n");
       debug_printf( "Test FLASH\r\n" );
		if(BlockStorageList::GetNumDevices() != 1)
		{
			debug_printf( "%d Block Devices present!\r\n", BlockStorageList::GetNumDevices() );
			break;
		}

		BlockStorageDevice* ATM = BlockStorageList::GetFirstDevice();
		if(ATM == NULL)
		{
			debug_printf( "GetFirstDevice failed.\r\n" );
			break;
		}

		const BlockDeviceInfo* ATMInfo = ATM->GetDeviceInfo();
		if(ATMInfo == NULL)
		{
			debug_printf( "GetDeviceInfo failed.\r\n" );
			break;
		}

		debug_printf( "NumRegions in BSDevice: %d\r\n", ATMInfo->NumRegions);

		ByteAddress PhyAddress = (ByteAddress) 0xC0FFEEEE;

//		SectorAddress SectAddress = 0xC0FFEEEE;
		UINT32 RangeIndex;
		UINT32 RegionIndex;

		const BlockRegionInfo *pBlockRegionInfo;
		BOOL result = ATM->FindForBlockUsage(	/*UINT32*/ BlockUsage::DEPLOYMENT ,
								  PhyAddress , RegionIndex, RangeIndex );
		if(!result)
		{
			debug_printf( "FindForBlockUsage failed.\r\n" );
			break;
		}

		debug_printf( "Block founded at physical address: 0x%08x\r\n", PhyAddress);

		BYTE pSectorBuf[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};

		BYTE pVerBuf[17];

		//ERASE before writing!
		if(!ATM->IsBlockErased(PhyAddress, 0x1000))
		{
			debug_printf( "Erasing block " );
			if(!ATM->EraseBlock(PhyAddress))
			{
				debug_printf( "failed.\r\n" );
				break;
			}
			debug_printf( "successful.\r\n" );
		}

		if(ATM->Write(/*UINT32*/ PhyAddress, /*UINT32 NumOfBytes*/ 16, /*BYTE* */ pSectorBuf, /*SectorMetadata* */ FALSE))
			debug_printf( "Correctly written 16 bytes to address 0x%08x\r\n", PhyAddress);

		memset(pVerBuf, 0, 16);
		ATM->Read(PhyAddress, 16, pVerBuf);
		memset(pVerBuf, 0, 16);
		ATM->Read(PhyAddress, 16, pVerBuf);
		if (memcmp(pVerBuf, pSectorBuf, 16) == 0) {
			debug_printf( "Verify OK\r\n");
		}
		else {
			debug_printf( "Verify ERROR\r\n");
		}
        Events_WaitForEvents( 0, 2000 );
    }

#endif		//TEST FLASH

#if 0
    // PS - BEGIN
	debug_printf("TEST LED...\r\n");
	g_LPC24XX_GPIO_Driver.EnableOutputPin(LPC24XX_GPIO::c_P4_26, TRUE);
    for (int i = 50; i; i--) {
    	g_LPC24XX_GPIO_Driver.SetPinState(LPC24XX_GPIO::c_P4_26, FALSE);
    	Events_WaitForEvents(0, 100);
    	g_LPC24XX_GPIO_Driver.SetPinState(LPC24XX_GPIO::c_P4_26, TRUE);
    	Events_WaitForEvents(0, 100);
    }
#endif

#if 0
    // PS - BEGIN
	debug_printf("TEST JOYSTICK...\r\n");
	g_LPC24XX_ADC_Driver.Initialize(10000);
	g_LPC24XX_ADC_Driver.On();
    for (int i = 50; i; i--) {
    	int v = g_LPC24XX_ADC_Driver.GetSample();
    	Events_WaitForEvents(0, 100);
    }
#endif

#if 0
	I2C_Initialize();

    static I2C_WORD writeBufferY[1] = {0xcc};
    static I2C_WORD readBufferY[2] =  {0, 0};
    static I2C_WORD writeBufferX[1] = {0xdc};
    static I2C_WORD readBufferX[2] =  {0, 0};
    I2C_USER_CONFIGURATION cfg = { 0x48, 100};
    I2C_HAL_XACTION xaction;
    I2C_HAL_XACTION_UNIT xunit, *pxunit;

    I2C_Initialize();
    while(1) {
    	pxunit = &xunit;

    	I2C_InitializeTransactionUnit(&xunit, writeBufferY, readBufferY, 1, false);
    	I2C_InitializeTransaction(&xaction, cfg, &pxunit, 1);
    	I2C_Enqueue(&xaction);
    	while (!I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Completed | I2C_HAL_XACTION::c_Status_Aborted));

    	if (I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Aborted)) continue;
    	I2C_InitializeTransactionUnit(&xunit, writeBufferY, readBufferY, 2, true);
    	I2C_InitializeTransaction(&xaction, cfg, &pxunit, 1);
    	I2C_Enqueue(&xaction);
    	while (!I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Completed | I2C_HAL_XACTION::c_Status_Aborted));

    	int d1 = readBufferY[0];
    	d1 <<= 8;
    	d1 |=  readBufferY[1];
    	d1 >>= 4;

    	I2C_InitializeTransactionUnit(&xunit, writeBufferX, readBufferX, 1, false);
    	I2C_InitializeTransaction(&xaction, cfg, &pxunit, 1);
    	I2C_Enqueue(&xaction);
    	while (!I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Completed | I2C_HAL_XACTION::c_Status_Aborted));

    	if (I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Aborted)) continue;
    	I2C_InitializeTransactionUnit(&xunit, writeBufferX, readBufferX, 2, true);
    	I2C_InitializeTransaction(&xaction, cfg, &pxunit, 1);
    	I2C_Enqueue(&xaction);
    	while (!I2C_XAction_CheckState(&xaction, I2C_HAL_XACTION::c_Status_Completed | I2C_HAL_XACTION::c_Status_Aborted));

    	int d2 = readBufferX[0];
    	d2 <<= 8;
    	d2 |=  readBufferX[1];
    	d2 >>= 4;


    	debug_printf("TS: X = %d, Y = %d\n\r", d2, d1);
    	Events_WaitForEvents( 0, 1000 );

    }
#endif

#if defined(TEST_TOUCH)
    TSC2007_Driver_Enable(TouchIsrProc);
 //   	bool res = g_LPC24XX_GPIO_Driver.EnableInputPin( (2*32)+10, false,  bottonISR, NULL, GPIO_INT_EDGE_BOTH, RESISTOR_PULLUP );
#endif
    TOUCH_PANEL_Initialize();
    TOUCH_PANEL_ResetCalibration();

    UINT32 flags;
    UINT16 source;
    UINT16 x;
    UINT16 y;
    INT64 time;

    debug_printf("Start Test\r\n");
    while(1)
    {
//        lcd_printf  ( "Hello, world!\r\n" );
  //      hal_printf  ( "Hello, world!\r\n" );

        TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time);
        debug_printf( "F=%d S=%d (%d,%d) t=%d\r\n", (flags >> 16),source, x, y, time );
        if ((flags >> 16) == 2)
        	lcd_printf( "(%03d,%03d) t=%06d\r", x, y, time );
        Events_WaitForEvents( 0, 100 );
    }

    while(1)
    {
        lcd_printf  ( "Hello, world!\r\n" );
        hal_printf  ( "Hello, world!\r\n" );
        debug_printf( "Hello, world!\r\n" );
        Events_WaitForEvents( 0, 2000 );
    }

}
