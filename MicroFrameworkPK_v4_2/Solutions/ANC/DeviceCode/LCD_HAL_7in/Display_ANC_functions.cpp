////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "UMSH8173MD.h"

//--//


BOOL LCD_Initialize()
{
    return UMSH8173MD_Driver::Initialize();
}

BOOL LCD_Uninitialize()
{
    return UMSH8173MD_Driver::Uninitialize();
}

void LCD_PowerSave( BOOL On )
{
    UMSH8173MD_Driver::PowerSave( On );
}

void LCD_Clear()
{
    UMSH8173MD_Driver::Clear();
}

void LCD_BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    UMSH8173MD_Driver::BitBlt( width, height, widthInWords, data, fUseDelta );
}

void LCD_BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    UMSH8173MD_Driver::BitBltEx( x, y, width, height, data );
}

void LCD_WriteChar( unsigned char c, int row, int col )
{
    UMSH8173MD_Driver::WriteChar( c, row, col );
}

void LCD_WriteFormattedChar( unsigned char c )
{
    UMSH8173MD_Driver::WriteFormattedChar( c );
}

INT32 LCD_GetWidth()
{
    return g_UMSH8173MD_Config.ControllerConfig.Width;
}

INT32 LCD_GetHeight()
{
    return g_UMSH8173MD_Config.ControllerConfig.Height;
}

INT32 LCD_GetBitsPerPixel()
{
    return g_UMSH8173MD_Config.ControllerConfig.BitsPerPixel;
}

UINT32 LCD_GetPixelClockDivider()
{
    return g_UMSH8173MD_Config.ControllerConfig.PixelClockDivider;
}

INT32 LCD_GetOrientation()
{
    return g_UMSH8173MD_Config.ControllerConfig.Orientation;
}

UINT32 LCD_ConvertColor(UINT32 color)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();

    return color;
}

//--//


