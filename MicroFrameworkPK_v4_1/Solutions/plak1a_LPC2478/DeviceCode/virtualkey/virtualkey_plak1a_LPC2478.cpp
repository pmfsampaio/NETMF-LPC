////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

GPIO_PIN VirtualKey_GetPins( UINT32 virtualKey)
{
	switch(virtualKey)
	{
		case VK_SELECT:
			return LPC24XX_GPIO::c_P2_21;
		case VK_RIGHT:
			return LPC24XX_GPIO::c_P0_19;
		case VK_DOWN:
			return GPIO_PIN_NONE;
		case VK_LEFT:
			return LPC24XX_GPIO::c_P0_20;
		case VK_UP:
			return GPIO_PIN_NONE;
		default:
			return GPIO_PIN_NONE; 
	}
}

