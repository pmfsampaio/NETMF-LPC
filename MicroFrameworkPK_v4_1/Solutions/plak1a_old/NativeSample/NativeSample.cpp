////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"

//--//

HAL_DECLARE_NULL_HEAP();

void ApplicationEntryPoint()
{
#if 1
    // PS - BEGIN
	debug_printf("TEST LED...\r\n");
    lcd_printf( "\n\n\n\n\n\n\n\n   TESTING!!!!\n" );
    lcd_printf("E agora um texto muito muito muito muito longo\n");
	g_LPC22XX_GPIO_Driver.EnableOutputPin(LPC22XX_GPIO::c_P0_22, TRUE);
    for (int i = 500; i; i--) {
    	g_LPC22XX_GPIO_Driver.SetPinState(LPC22XX_GPIO::c_P0_22, FALSE);
    	Events_WaitForEvents(0, 100);
    	g_LPC22XX_GPIO_Driver.SetPinState(LPC22XX_GPIO::c_P0_22, TRUE);
    	Events_WaitForEvents(0, 100);
    }
#endif

#if 0
    BOOL result;

    TimedEvents eventsTest;
    UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
    GPIO        gpioTest   ( GPIOTestPin );
    Timers      timersTest ( DisplayInterval, TimerDuration );

    debug_printf("TEST LED...\r\n");
    do
    {    
        result = eventsTest.Execute( STREAM__LCD );
        result = usartTest.Execute ( STREAM__LCD );
        result = gpioTest.Execute  ( STREAM__LCD );
        result = timersTest.Execute( STREAM__LCD );

    } while(FALSE); // run only once!
#endif
    while(TRUE);
}

