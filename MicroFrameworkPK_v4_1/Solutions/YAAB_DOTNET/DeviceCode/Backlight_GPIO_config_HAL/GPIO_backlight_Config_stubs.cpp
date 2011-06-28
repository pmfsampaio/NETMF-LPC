////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Drivers\Backlight\GPIO\gpio_backlight.h>

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata = "g_BackLight_Config"
#endif

OUTPUT_GPIO_CONFIG g_BackLight_Config =
{
    { TRUE }, // HAL_DRIVER_CONFIG_HEADER Header;

    //--//
    { 
    	LPC22XX_GPIO::c_P0_21, // Output GPIO pin
        TRUE,      // Active State
    },

    0,              // Refcount
    TRUE,           // State (default on)
};

BOOL OUTPUT_GPIO_Driver::Initialize( OUTPUT_GPIO_CONFIG* Config )
{
    NATIVE_PROFILE_PAL_IO();
    if(Config)
    {
        if(Config->Header.Enable)
        {
            Config->RefCount = 0;

            if(GPIO_PIN_NONE != Config->Output_GPIO_PIN.Pin)
            {
                CPU_GPIO_EnableOutputPin( Config->Output_GPIO_PIN.Pin, Config->On ? Config->Output_GPIO_PIN.ActiveState : !Config->Output_GPIO_PIN.ActiveState );
            }
        }
    }

    return TRUE;
}


void OUTPUT_GPIO_Driver::Uninitialize( OUTPUT_GPIO_CONFIG* Config  )
{
    NATIVE_PROFILE_PAL_IO();
    if(GPIO_PIN_NONE != Config->Output_GPIO_PIN.Pin)
    {
        CPU_GPIO_EnableInputPin( Config->Output_GPIO_PIN.Pin, FALSE, NULL, GPIO_INT_NONE, RESISTOR_PULLUP );
    }
}

void OUTPUT_GPIO_Driver::Set( OUTPUT_GPIO_CONFIG* Config, BOOL On )
{
    NATIVE_PROFILE_PAL_IO();
    GLOBAL_LOCK(irq);

    Config->On = On;

    if(GPIO_PIN_NONE != Config->Output_GPIO_PIN.Pin)
    {
        BOOL Set = (Config->On) || (0 < Config->RefCount);

        CPU_GPIO_SetPinState( Config->Output_GPIO_PIN.Pin, Set ? Config->Output_GPIO_PIN.ActiveState : !Config->Output_GPIO_PIN.ActiveState );
    }
}


void OUTPUT_GPIO_Driver::RefCount( OUTPUT_GPIO_CONFIG* Config, BOOL Add )
{
    NATIVE_PROFILE_PAL_IO();
    GLOBAL_LOCK(irq);

    ASSERT(Config);
    //ASSERT(1 == Config->Enable);

    if(Add)
    {
        Config->RefCount++;
    }
    else
    {
        Config->RefCount--;
        //ASSERT(Config->RefCount >= 0);
    }

    if(GPIO_PIN_NONE != Config->Output_GPIO_PIN.Pin)
    {
        BOOL Set = (Config->On) || (0 < Config->RefCount);

        CPU_GPIO_SetPinState( Config->Output_GPIO_PIN.Pin, Set ? Config->Output_GPIO_PIN.ActiveState : !Config->Output_GPIO_PIN.ActiveState );
    }
}



#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata
#endif
