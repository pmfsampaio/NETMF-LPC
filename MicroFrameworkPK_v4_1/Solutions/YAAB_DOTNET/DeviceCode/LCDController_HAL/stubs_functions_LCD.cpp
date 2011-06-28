////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Drivers\Display\ILI9328\ILI9328.h>
#include <Drivers\Backlight\GPIO\gpio_backlight.h>

#include <Drivers\Display\TextFonts\Font8x8\font8x8.cpp>

//////////////////////////////////////////////////////////////////////////////

#define ILI9328_SCREEN_WIDTH           (240)
#define ILI9328_SCREEN_HEIGHT          (320)
#define ILI9328_BITS_PER_PIXEL         16
#define ILI9328_ORIENTATION            0

#define ILI9328_TIME_POWER_STABLE      0
#define ILI9328_TIME_SDA_SETUP         0          // Time after presenting data until rising clock edge.
#define ILI9328_TIME_SDA_HOLD          0          // Time after rising clock edge to data change.
#define ILI9328_TIME_MIN_CMD_HOLD_OFF  0          // Minimum spacing between commands on serial bus.
#define ILI9328_TIME_LOAD_SETUP        0          // Time between asserting LOAD and first bit.
#define ILI9328_TIME_LOAD_HOLD         0          // Time after last bit and unasserting LOAD.

#define ILI9328_ENABLE_TFT             TRUE
#define ILI9328_ENABLE_COLOR           TRUE
#define ILI9328_PIXEL_POLARITY         TRUE
#define ILI9328_FIRST_LINE_POLARITY    FALSE
#define ILI9328_LINE_PULSE_POLARITY    FALSE
#define ILI9328_SHIFT_CLK_POLARITY     FALSE
#define ILI9328_OUTPUT_ENABLE_POLARITY TRUE
#define ILI9328_CLK_IDLE_ENABLE        FALSE
#define ILI9328_CLK_SELECT_ENABLE      FALSE

#define ILI9328_PIXELCLOCKDIVIDER      0//(29 - 1)    // Div by 19 (96/19 = 5.05 Mhz)
#define ILI9328_BUS_WIDTH              16
#define ILI9328_HWIDTH                 0//7
#define ILI9328_HWAIT1                 0//43
#define ILI9328_HWAIT2                 0//9
#define ILI9328_VWIDTH                 0//2
#define ILI9328_VWAIT1                 0//3
#define ILI9328_VWAIT2                 0//5

//////////////////////////////////////////////////////////////////////////////

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata = "g_ILI9328_Config"
#endif



// ILI9328 Register Definitions
#define PA_LCD_INSTR			( 0x82000000 )
#define PA_LCD_DATA				( 0x82000000 | (1 << 22) )

ILI9328_CONFIG g_ILI9328_Config =
{
	    { TRUE }, // HAL_DRIVER_CONFIG_HEADER Header;
	    {
	    		{ LPC22XX_GPIO::c_P0_21, FALSE},
	    		(UINT32 *)PA_LCD_INSTR,
	    		(UINT32 *)PA_LCD_DATA,
	    },
	    {
    ILI9328_SCREEN_WIDTH,              // UINT32 Width;
    ILI9328_SCREEN_HEIGHT,             // UINT32 Height;
    ILI9328_ENABLE_TFT,                // BOOL EnableTFT;
    ILI9328_ENABLE_COLOR,              // BOOL EnableColor;
    ILI9328_PIXEL_POLARITY,            // BOOL PixelPolarity;           (TRUE == high)
    ILI9328_FIRST_LINE_POLARITY,       // BOOL FirstLineMarkerPolarity; (FALSE == low)
    ILI9328_LINE_PULSE_POLARITY,       // BOOL LinePulsePolarity;
    ILI9328_SHIFT_CLK_POLARITY,        // BOOL ShiftClockPolarity;
    ILI9328_OUTPUT_ENABLE_POLARITY,    // BOOL OutputEnablePolarity;
    ILI9328_CLK_IDLE_ENABLE,           // BOOL ClockIdleEnable;
    ILI9328_CLK_SELECT_ENABLE,         // BOOL ClockSelectEnable;

    ILI9328_PIXELCLOCKDIVIDER,         // UINT32 PixelClockDivider;
    ILI9328_BUS_WIDTH,                 // UINT32 BusWidth;
    ILI9328_BITS_PER_PIXEL,            // UINT32 BitsPerPixel;
    ILI9328_ORIENTATION,               // UINT8 Orientation;

    ILI9328_HWIDTH,                    // UINT32 HorizontalSyncPulseWidth;
    ILI9328_HWAIT1,                    // UINT32 HorizontalSyncWait1;
    ILI9328_HWAIT2,                    // UINT32 HorizontalSyncWait2;
    ILI9328_VWIDTH,                    // UINT32 VerticalSyncPulseWidth;
    ILI9328_VWAIT1,                    // UINT32 VerticalSyncWait1;
    ILI9328_VWAIT2,                    // UINT32 VerticalSyncWait2;
	    }
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata
#endif


//--//

BOOL LCD_Controller_Initialize( DISPLAY_CONTROLLER_CONFIG& config )
{
    return FALSE;
}

BOOL LCD_Controller_Uninitialize()
{
    return TRUE;
}

BOOL LCD_Controller_Enable( BOOL fEnable )
{
    return TRUE;
}

