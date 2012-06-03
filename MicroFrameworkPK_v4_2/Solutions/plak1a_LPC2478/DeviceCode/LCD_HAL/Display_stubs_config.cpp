////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "MTF-TQ35SP741-AV.h"

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata = "g_TQ35SP741_Config"
#endif

#define TQ35SP741_WIDTH   320//240
#define TQ35SP741_HEIGHT  240//320
#define TQ35SP741_BPP     32



// Screen buffer for EA_LPC2378 LCD controller, has to be double word aligned, requirement for the LPC24xx core.
// for GNU, we used section and at scatterfile to put the screenbuffer to be aligned, instead of using the "attribute" to save some dummy memory.

#if defined(__GNUC__)

UINT8 __attribute__ ((aligned (16))) ScreenBuffer[(TQ35SP741_WIDTH*TQ35SP741_HEIGHT*TQ35SP741_BPP)/8];

#else

__align(16) UINT8 ScreenBuffer[(TQ35SP741_WIDTH*TQ35SP741_HEIGHT*TQ35SP741_BPP)/8];

#endif


TQ35SP741_CONFIG g_TQ35SP741_Config =
{
    { TRUE },                      // HAL_DRIVER_CONFIG_HEADER Header;
    {
        (UINT32 *)ScreenBuffer, // Screen Buffer
        {                          // GPIO_FLAG LcdEnable
             LPC24XX_GPIO::c_P2_01,
            TRUE,
        },
        {                          // SPI_CONFIGURATION SPI_Config
            LPC24XX_GPIO::c_P0_16, // Chip select
            FALSE,                 // Chip Select polarity
            TRUE,                  // MSK_IDLE
            TRUE,                  // MSK_SAMPLE_EDGE
            FALSE,                 // 16-bit mode
            900,                   // SPI Clock Rate KHz
            1,                     // CS setup time us
            1,                     // CS hold time us
            LPC24XX_SPI::c_SPI0,   // SPI Module
        },
    },
    {
        TQ35SP741_WIDTH,      // UINT32 Width;
        TQ35SP741_HEIGHT,     // UINT32 Height;
        TRUE,     // BOOL EnableTFT;
        TRUE,     // BOOL EnableColor;
        FALSE,    // Not applicable BOOL PixelPolarity; (TRUE == high)
        FALSE,    // BOOL FirstLineMarkerPolarity;      (FALSE == low)
        FALSE,    // BOOL LinePulsePolarity; Hsync
        FALSE,    // BOOL ShiftClockPolarity; Vsync
        FALSE,     // BOOL OutputEnablePolarity;
        FALSE,    // Not applicable BOOL ClockIdleEnable;
        FALSE,    // Not applicable BOOL ClockSelectEnable;

        1, //4,       // UINT32 PixelClockDivider;
        32,//16,       // UINT32 BusWidth;
        TQ35SP741_BPP,       // UINT32 BitsPerPixel;
        0,        // UINT8 Orientation;

        30, //2,        // UINT32 HorizontalSyncPulseWidth;
        20, //60, //20 10,       // UINT32 HorizontalSyncWait1;
        38, //68, //38 30,       // UINT32 HorizontalSyncWait2;
        3, //2,        // UINT32 VerticalSyncPulseWidth;
        5, //4, //5 2,        // UINT32 VerticalSyncWait1;
        15, //18, //15 4,        // UINT32 VerticalSyncWait2;
    },
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata
#endif

//--//

