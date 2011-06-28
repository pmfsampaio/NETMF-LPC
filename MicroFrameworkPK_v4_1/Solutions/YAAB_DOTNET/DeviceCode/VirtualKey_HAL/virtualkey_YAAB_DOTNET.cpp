////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <..\DeviceCode\Targets\Native\LPC22XX\DeviceCode\LPC22XX.h>

GPIO_PIN VirtualKey_GetPins( UINT32 virtualKey)
{
    GPIO_PIN pin;   

    switch (virtualKey)
    {
    case VK_LEFT:
        pin = LPC22XX_GPIO::c_P1_20;     //SW0;
        break;
    case VK_UP:
        pin = LPC22XX_GPIO::c_P1_21;     //SW1;
        break;
    case VK_DOWN:
        pin = LPC22XX_GPIO::c_P1_22;     //SW2;
        break;
    case VK_SELECT:
        pin = LPC22XX_GPIO::c_P0_29;     //JS_CENTER;
        break;
    case VK_RIGHT:
        pin = LPC22XX_GPIO::c_P1_23;     //SW3;
        break;
    case VK_MENU:
    case VK_HOME:
    case VK_BACK:
    default:        
        pin = GPIO_PIN_NONE;
        break;
    }

   return pin;
}
