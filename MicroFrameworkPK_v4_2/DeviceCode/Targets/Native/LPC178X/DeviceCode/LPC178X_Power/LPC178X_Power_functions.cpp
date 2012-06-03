////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for LPC178X: Copyright (c) Oberon microsystems, Inc.
//
//  *** CPU Power States ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\LPC1788_Devices.h"



BOOL CPU_Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_POWER();
    CPU_INTC_Initialize();
    return TRUE;
}

void CPU_ChangePowerLevel(POWER_LEVEL level)
{
    switch(level)
    {
        case POWER_LEVEL__MID_POWER:
            break;

        case POWER_LEVEL__LOW_POWER:
            break;

        case POWER_LEVEL__HIGH_POWER:
        default:
            break;
    }
}

void CPU_Sleep( SLEEP_LEVEL level, UINT64 wakeEvents )
{
    NATIVE_PROFILE_HAL_PROCESSOR_POWER();
#if 0
    PWR->CR &= ~(PWR_CR_LPDS | PWR_CR_PDDS); // reset deepsleep bits
    
    switch(level)
    {
        
        case SLEEP_LEVEL__DEEP_SLEEP: // stop
            SCB->SCR |= SCB_SCR_SLEEPDEEP;
            PWR->CR |= PWR_CR_CWUF | PWR_CR_LPDS; // low power deepsleep
            break;
        case SLEEP_LEVEL__OFF: // standby
            SCB->SCR |= SCB_SCR_SLEEPDEEP;
            PWR->CR |= PWR_CR_CWUF | PWR_CR_PDDS; // power down deepsleep
            break;            
        default: // sleep
            SCB->SCR &= ~SCB_SCR_SLEEPDEEP;       // no deepsleep
            PWR->CR |= PWR_CR_CWUF;
            break;
    }
#endif
    __WFI(); // sleep and wait for interrupt
}

void CPU_Halt()  // unrecoverable error
{
    NATIVE_PROFILE_HAL_PROCESSOR_POWER();
    while(1);
}

void CPU_Reset()
{
    NATIVE_PROFILE_HAL_PROCESSOR_POWER();
#if 0
    SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos)  // unlock key
               | (1 << SCB_AIRCR_SYSRESETREQ_Pos); // reset request
#endif

//    	unsigned long *paircr = (unsigned long *) CM3_AIRCR;
//    	asm volatile ("dsb");
//    	SCB->AIRCR = (SCB->AIRCR & (7 << 8)) | 1 << 2 | 0x5FA << 16
    	//*paircr = (*paircr & (7 << 8)) | 1 << 2 | 0x5FA << 16;
//    	asm volatile ("dsb");
    asm volatile("b EntryPoint");
    while(1); // wait for reset
}

BOOL CPU_IsSoftRebootSupported ()
{
    NATIVE_PROFILE_HAL_PROCESSOR_POWER();
    return TRUE;
}

// PS
#if 0
__asm void HAL_AssertEx()
{
    BKPT     #0
L1  B        L1
    BX       lr
}
#endif
void HAL_AssertEx()
{
	while(1);
}

//--//

