////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"

//--//

HAL_DECLARE_NULL_HEAP();

void ISRGpio(GPIO_PIN pin, BOOL state, void *param)
{
	debug_printf("Aqui!\r\n");
}
void ApplicationEntryPoint()
{
    BOOL result;
    char    buffer[10];
#if 0
    TimedEvents eventsTest;
    UART        usartTest  ( COMTestPort, 115200, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
    GPIO        gpioTest   ( GPIOTestPin );
    Timers      timersTest ( DisplayInterval, TimerDuration );


    USART_Initialize( 0, 115200, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
    USART_Write(0, "Teste USART\r\n", 13);
    do {
    	Events_WaitForEvents(0, 100);
    	int res = USART_Read(0, buffer, 10 );
    	if (res == 0) continue;
        if(!USART_Write(0, buffer, res)) break;
    } while (1);
#endif

#if 0
    do
    {    
        result = eventsTest.Execute( STREAM__LCD );
        result = usartTest.Execute ( STREAM__LCD );
        result = gpioTest.Execute  ( STREAM__LCD );
        result = timersTest.Execute( STREAM__LCD );

    } while(FALSE); // run only once!
#endif

    lcd_printf( "\n\n\n\n\n\n\n\n   TESTING!!!!\n" );

#if 1
    // PS - BEGIN
	debug_printf("TEST LED...\r\n");
	g_LPC22XX_GPIO_Driver.EnableOutputPin(LPC22XX_GPIO::c_P1_16, TRUE);
    for (int i = 500; i; i--) {
    	g_LPC22XX_GPIO_Driver.SetPinState(LPC22XX_GPIO::c_P1_16, FALSE);
    	Events_WaitForEvents(0, 100);
    	g_LPC22XX_GPIO_Driver.SetPinState(LPC22XX_GPIO::c_P1_16, TRUE);
    	Events_WaitForEvents(0, 100);
    }
#endif
#if defined(TEST_BUTTON)
    bool enterBooterMode = false;
    GPIO_BUTTON_CONFIG * ButtonConfig = &g_GPIO_BUTTON_Config;

    if ((ButtonConfig->Mapping[BUTTON_B4_BITIDX].m_HW != GPIO_PIN_NONE))
    {
    	while (1) {
			debug_printf("Test Button...\r\n");
			while (!CPU_GPIO_GetPinState(LPC22XX_GPIO::c_P1_20))
			{
				debug_printf("Get zero\r\n");
			}
			while (CPU_GPIO_GetPinState(LPC22XX_GPIO::c_P1_20))
			{
				debug_printf("Get ONE\r\n");
			}
    	}
    }

#endif

#if	defined(TEST_FLASH)

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

        Events_WaitForEvents( 0, 2000 );
    }
#endif		//TEST_FLASH

    // PS - END

    while(TRUE);
}

