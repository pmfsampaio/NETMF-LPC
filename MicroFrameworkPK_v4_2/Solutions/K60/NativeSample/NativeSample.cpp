////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"

//--//

HAL_DECLARE_NULL_HEAP();

int i;

extern int Prot_Bytes;

// workaround to pull in prot bytes
volatile int ProtKeep = Prot_Bytes;

void ButtonISR (GPIO_PIN Pin, BOOL PinState, void * Param)
{
    if (PinState)     // Released, up
    {
        CPU_GPIO_SetPinState (K60_GPIO_Driver::PA29, FALSE);
    }
    else             // Pressed, down
    {
        CPU_GPIO_SetPinState (K60_GPIO_Driver::PA29, TRUE);
    }
}

void ApplicationEntryPoint()
{
    BOOL result;
        
	
		
    TimedEvents eventsTest;
    //UART        usartTest  ( 3, 115200, USART_PARITY_NONE, USART_STOP_BITS_ONE, 8, USART_FLOW_NONE );
    //GPIO        gpioTest   ( GPIOTestPin );

    do
    {    
        //result = eventsTest.Execute( STREAM__LCD );
        //result = usartTest.Execute ( STREAM__LCD );
        //result = gpioTest.Execute  ( STREAM__LCD );
		

    } while(FALSE); // run only once!	

    CPU_GPIO_EnableOutputPin(K60_GPIO_Driver::PA28, FALSE);   
    CPU_GPIO_EnableOutputPin(K60_GPIO_Driver::PA29, FALSE);   
    CPU_GPIO_EnableInputPin (K60_GPIO_Driver::PA19, FALSE, ButtonISR, GPIO_INT_EDGE_BOTH, RESISTOR_PULLDOWN);    

    while (1)
    {
        for (i = 0; i < 1000000; i++);
        CPU_GPIO_SetPinState (K60_GPIO_Driver::PA28, !CPU_GPIO_GetPinState(K60_GPIO_Driver::PA28));           
    }
}

