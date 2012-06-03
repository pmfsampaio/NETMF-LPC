////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

//--//

void HAL_AssertEx()
{
    // cause an abort and let the abort handler take over
    *((char*)0xFFFFFFFF) = 'a';
}

//--//

BOOL CPU_Initialize()
{
    CPU_INTC_Initialize();

    return TRUE;
}

void CPU_Reset()
{
    NVIC_SystemReset();

    while (1)
    {
    }
}

void CPU_Sleep(SLEEP_LEVEL level, UINT64 wakeEvents)
{
    // TODO
}

void CPU_ChangePowerLevel(POWER_LEVEL level)
{
    // TODO
}

BOOL CPU_IsSoftRebootSupported()
{
    return TRUE;
}

void CPU_Halt()
{
    while (1)
    {
    }
}

