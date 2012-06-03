////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "UMSH8173MD.h"

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata = "g_UMSH8173MD_Config"
#endif

#define UMSH8173MD_WIDTH   800
#define UMSH8173MD_HEIGHT  480
#define UMSH8173MD_BPP     16



// Screen buffer for EA_LPC2378 LCD controller, has to be double word aligned, requirement for the LPC24xx core.
// for GNU, we used section and at scatterfile to put the screenbuffer to be aligned, instead of using the "attribute" to save some dummy memory.

#if defined(__GNUC__)

UINT8 __attribute__ ((aligned (16))) ScreenBuffer[(UMSH8173MD_WIDTH*UMSH8173MD_HEIGHT*UMSH8173MD_BPP)/8];

#else

__align(16) UINT8 ScreenBuffer[(UMSH8173MD_WIDTH*UMSH8173MD_HEIGHT*UMSH8173MD_BPP)/8];

#endif


UMSH8173MD_CONFIG g_UMSH8173MD_Config =
{
    { TRUE },                      // HAL_DRIVER_CONFIG_HEADER Header;
    {
        (UINT32 *)ScreenBuffer, // Screen Buffer
        {                          // GPIO_FLAG LcdEnable
             LPC178X_GPIO::c_P2_01,
            TRUE,
        },
    },
    {
        UMSH8173MD_WIDTH,      // UINT32 Width;
        UMSH8173MD_HEIGHT,     // UINT32 Height;
        TRUE,     // BOOL EnableTFT;
        TRUE,     // BOOL EnableColor;
        FALSE,    // Not applicable BOOL PixelPolarity; (TRUE == high)
        FALSE,    // BOOL FirstLineMarkerPolarity;      (FALSE == low)
        FALSE,    // BOOL LinePulsePolarity; Hsync
        TRUE,    // BOOL ShiftClockPolarity; Vsync
        FALSE,     // BOOL OutputEnablePolarity;
        FALSE,    // Not applicable BOOL ClockIdleEnable;
        FALSE,    // Not applicable BOOL ClockSelectEnable;

        128,       // UINT32 PixelClockDivider;
        16,       // UINT32 BusWidth;
        UMSH8173MD_BPP,       // UINT32 BitsPerPixel;
        0,        // UINT8 Orientation;

        150,        // UINT32 HorizontalSyncPulseWidth;
        25,       // UINT32 HorizontalSyncWait1;
        25,       // UINT32 HorizontalSyncWait2;
        6,        // UINT32 VerticalSyncPulseWidth;
        2,        // UINT32 VerticalSyncWait1;
        2,        // UINT32 VerticalSyncWait2;
    },
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata
#endif

//--//

