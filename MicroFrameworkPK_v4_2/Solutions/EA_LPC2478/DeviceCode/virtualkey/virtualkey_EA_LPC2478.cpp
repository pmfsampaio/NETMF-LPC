////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

GPIO_PIN VirtualKey_GetPins( UINT32 virtualKey)
{
	switch(virtualKey)
	{
		case VK_SELECT:
			return LPC24XX_GPIO::c_P2_22;
		case VK_RIGHT:
			return LPC24XX_GPIO::c_P2_23;
		case VK_DOWN:
			return LPC24XX_GPIO::c_P2_25;
		case VK_LEFT:
			return LPC24XX_GPIO::c_P2_26;
		case VK_UP:
			return LPC24XX_GPIO::c_P2_27;
		default:
			return GPIO_PIN_NONE; 
	}
}

