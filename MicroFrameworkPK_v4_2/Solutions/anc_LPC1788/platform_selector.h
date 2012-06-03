////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for anc_LPC1788 board (LPC178X): Copyright (c) Oberon microsystems, Inc.
//
//  anc_LPC1788-specific definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_anc_LPC1788_SELECTOR_H_
#define _PLATFORM_anc_LPC1788_SELECTOR_H_ 1


/////////////////////////////////////////////////////////
//
// processor and features
//

#if defined(PLATFORM_ARM_anc_LPC1788)
#define HAL_SYSTEM_NAME                     "anc_LPC1788"


//#define USB_ALLOW_CONFIGURATION_OVERRIDE  1


//
// processor and features
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// constants
//

#define SYSTEM_CLOCK_HZ                 96000000
#define SLOW_CLOCKS_PER_SECOND          48000000

//#define CLOCK_COMMON_FACTOR             200000 // old value:  1000000
//#define SLOW_CLOCKS_TEN_MHZ_GCD         400000 // old value: 10000000

#define CLOCK_COMMON_FACTOR             1000000
#define SLOW_CLOCKS_TEN_MHZ_GCD         2000000

//#define CLOCK_COMMON_FACTOR             1000000
//#define SLOW_CLOCKS_TEN_MHZ_GCD         10000000
#define SLOW_CLOCKS_MILLISECOND_GCD     1000

#define SYSTEM_CYCLE_CLOCK_HZ           SYSTEM_CLOCK_HZ


#define FLASH_MEMORY_Base               0x80000000
#define FLASH_MEMORY_Size               0x00400000
#define SRAM1_MEMORY_Base               0xA0000000
#define SRAM1_MEMORY_Size               0x04000000

#define TXPROTECTRESISTOR               RESISTOR_DISABLED
#define RXPROTECTRESISTOR               RESISTOR_DISABLED
#define CTSPROTECTRESISTOR              RESISTOR_DISABLED
#define RTSPROTECTRESISTOR              RESISTOR_DISABLED

#define INSTRUMENTATION_H_GPIO_PIN      GPIO_PIN_NONE

#define TOTAL_USART_PORT                3
#define USART_DEFAULT_PORT              COM3
#define USART_DEFAULT_BAUDRATE          115200

#define DEBUG_TEXT_PORT                 COM3
#define STDIO                           COM3
#define DEBUGGER_PORT                   COM3
#define MESSAGING_PORT                  COM3

//#define LPC178X_USB_Attach_Pin_Direct     (16 + 5) // B5


#define DRIVER_PAL_BUTTON_MAPPING               \
    { GPIO_PIN_NONE, BUTTON_B0 }, /* Up */      \
    { GPIO_PIN_NONE, BUTTON_B1 }, /* Down */    \
    { GPIO_PIN_NONE, BUTTON_B2 }, /* Left */    \
    { GPIO_PIN_NONE, BUTTON_B3 }, /* Right */   \
    { GPIO_PIN_NONE, BUTTON_B4 }, /* Enter */   \
    { GPIO_PIN_NONE, BUTTON_B5 }, /* User */

//
// constants
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// macros
//

#define GLOBAL_LOCK(x)             SmartPtr_IRQ x
#define DISABLE_INTERRUPTS()       SmartPtr_IRQ::ForceDisabled()
#define ENABLE_INTERRUPTS()        SmartPtr_IRQ::ForceEnabled()
#define INTERRUPTS_ENABLED_STATE() SmartPtr_IRQ::GetState()
#define GLOBAL_LOCK_SOCKETS(x)     SmartPtr_IRQ x

#if defined(_DEBUG)
#define ASSERT_IRQ_MUST_BE_OFF()   ASSERT(!SmartPtr_IRQ::GetState())
#define ASSERT_IRQ_MUST_BE_ON()    ASSERT( SmartPtr_IRQ::GetState())
#else
#define ASSERT_IRQ_MUST_BE_OFF()
#define ASSERT_IRQ_MUST_BE_ON()
#endif


//
// macros
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// global functions
//

//
// global functions
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// communicaiton facilities
//

// Port definitions
#define COM1                   ConvertCOM_ComHandle(0)
#define COM2                   ConvertCOM_ComHandle(1)
#define COM3                   ConvertCOM_ComHandle(2)

#define TOTAL_USB_CONTROLLER   1
#define USB1                   ConvertCOM_UsbHandle(0)

#define USB_MAX_QUEUES         7  // 7 endpoints (EP0 + 6)

#define TOTAL_SOCK_PORT        0

#define TOTAL_DEBUG_PORT       1
#define COM_DEBUG              ConvertCOM_DebugHandle(0)

#define COM_MESSAGING          ConvertCOM_MessagingHandle(0)

#define USB_IRQ_INDEX          20  // NVIC USB low priority index

#define USART_TX_IRQ_INDEX(x)           ( LPC178X_USART::getIntNo(x) )

#define PLATFORM_DEPENDENT_TX_USART_BUFFER_SIZE    2048  // there is one TX for each usart port
#define PLATFORM_DEPENDENT_RX_USART_BUFFER_SIZE    4096  // there is one RX for each usart port
#define PLATFORM_DEPENDENT_USB_QUEUE_PACKET_COUNT  8    // there is one queue for each pipe of each endpoint and the size of a single packet is sizeof(USB_PACKET64) == 68 bytes

//
// communicaiton facilities
/////////////////////////////////////////////////////////


#include <processor_selector.h>

#endif // PLATFORM_ARM_anc_LPC1788
//
// drivers
/////////////////////////////////////////////////////////

#endif // _PLATFORM_anc_LPC1788_SELECTOR_H_
