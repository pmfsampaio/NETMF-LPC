////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "MTF-TQ35SP741-AV.h"

//--//


BOOL LCD_Initialize()
{
    return TQ35SP741_Driver::Initialize();
}

BOOL LCD_Uninitialize()
{
    return TQ35SP741_Driver::Uninitialize();
}

void LCD_PowerSave( BOOL On )
{
    TQ35SP741_Driver::PowerSave( On );
}

void LCD_Clear()
{
    TQ35SP741_Driver::Clear();
}

void LCD_BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    TQ35SP741_Driver::BitBlt( width, height, widthInWords, data, fUseDelta );
}

void LCD_BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    TQ35SP741_Driver::BitBltEx( x, y, width, height, data );
}

void LCD_WriteChar( unsigned char c, int row, int col )
{
    TQ35SP741_Driver::WriteChar( c, row, col );
}

void LCD_WriteFormattedChar( unsigned char c )
{
    TQ35SP741_Driver::WriteFormattedChar( c );
}

INT32 LCD_GetWidth()
{
    return g_TQ35SP741_Config.ControllerConfig.Width;
}

INT32 LCD_GetHeight()
{
    return g_TQ35SP741_Config.ControllerConfig.Height;
}

INT32 LCD_GetBitsPerPixel()
{
    return g_TQ35SP741_Config.ControllerConfig.BitsPerPixel;
}

UINT32 LCD_GetPixelClockDivider()
{
    return g_TQ35SP741_Config.ControllerConfig.PixelClockDivider;
}

INT32 LCD_GetOrientation()
{
    return g_TQ35SP741_Config.ControllerConfig.Orientation;
}

#define RGB_UNPACK_RED(_c)		((((_c) >> 8) & 0xF8) | ((_c) >> 13))
#define RGB_UNPACK_GREEN(_c)	((((_c) >> 3) & 0xFC) | ((_c) >> 9) & 0x03)
#define RGB_UNPACK_BLUE(_c)		((((_c) << 3) & 0xF8) | ((_c) >> 2) & 0x07)

UINT32 LCD_ConvertColor(UINT32 color)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();

    return ( RGB_UNPACK_RED(color) << 16 ) |
    		( RGB_UNPACK_GREEN(color) << 8 ) |
    		( RGB_UNPACK_BLUE(color) );
}

//--//


