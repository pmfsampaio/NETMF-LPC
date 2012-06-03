////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// This file is part of the Microsoft .NET Micro Framework Porting Kit Code Samples and is unsupported. 
// Copyright (C) Microsoft Corporation. All rights reserved. Use of this sample source code is subject to 
// the terms of the Microsoft license agreement under which you licensed this sample source code. 
// 
// THIS SAMPLE CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// 
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *    Copyright (C) Pedro Sampaio, 2011  All rights reserved.
 */
 
#include "tinyhal.h"

#ifndef _DRIVERS_DISPLAY_ILI9328_H_
#define _DRIVERS_DISPLAY_ILI9328_H_ 1


// LCD Size Defines
#define PHYSICAL_XMAX 240
#define PHYSICAL_YMAX 320

#define DISP_XMIN   (0) 
#define DISP_XMAX   (240)
#define DISP_YMIN   (0) 
#define DISP_YMAX   (320)

#define LCD_ONELINE_OFFSET  (DISP_XMAX *2)

// Colors
#define BLUE    	(0xF800)
#define GREEN   	(0x07E0)
#define RED    		(0x001F)
#define WHITE   	(0xFFFF)
#define BLACK   	(0x0000)
#define YELLOW  	(0x07FF)
#define CYAN    	(0xFFE0)
#define MAGENTA 	(0xF81F)



//////////////////////////////////////////////////////////////////////////////
struct ILI9328_LCD_CONFIG
{
    GPIO_FLAG Backlight;
    UINT32 *ControlAddress;
    UINT32 *DataAddress;
};

struct ILI9328_CONFIG
{
    HAL_DRIVER_CONFIG_HEADER Header;

    //--//

    ILI9328_LCD_CONFIG LcdConfig;

    DISPLAY_CONTROLLER_CONFIG ControllerConfig;

    static LPCSTR GetDriverName() { return "ILI9328"; }
};

extern ILI9328_CONFIG g_ILI9328_Config;


struct ILI9328_Driver
{
    UINT32 m_cursor;

    static BOOL Initialize();
    static BOOL Uninitialize();
    static void PowerSave( BOOL On );
    static void Clear();
    static void BitBltEx( int x, int y, int width, int height, UINT32 data[] );
    static void BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta );
    static void WriteChar( unsigned char c, int row, int col );
    static void WriteFormattedChar( unsigned char c );

private:
    static void WriteRawByte( UINT8 data );
    static void WriteCmdByte( UINT8 addr, UINT8 data );
    static UINT32 PixelsPerWord();
    static UINT32 TextRows();
    static UINT32 TextColumns();
    static UINT32 WidthInWords();
    static UINT32 SizeInWords();
    static UINT32 SizeInBytes();

    static void Delay_MS (UINT16 time);
    static UINT32 Convert16To18(UINT16 val);
    static UINT32 ColorRGB666(UINT16 colorRGB565);
    static void SetWindow(UINT16 xstart,UINT16 xend,UINT16 ystart,UINT16 yend );
    static void Reg_Write (UINT16 reg_addr, UINT16 data);
    static UINT16 Reg_Read (UINT16 reg_addr);
    static void Set_Display_On( void );
    static void Set_Display_Off (void);
};

extern ILI9328_Driver g_ILI9328_Driver;

#define ILI932X_START_OSC			0x00
//data read at this instruction should be 0x0789 --> use for test connection
#define ILI932X_DRIV_OUT_CTRL		0x01
#define ILI932X_DRIV_WAV_CTRL		0x02
#define ILI932X_ENTRY_MOD			0x03
#define ILI932X_RESIZE_CTRL			0x04
#define ILI932X_DISP_CTRL1			0x07
#define ILI932X_DISP_CTRL2			0x08
#define ILI932X_DISP_CTRL3			0x09
#define ILI932X_DISP_CTRL4			0x0A
#define ILI932X_RGB_DISP_IF_CTRL1	0x0C
#define ILI932X_FRM_MARKER_POS		0x0D
#define ILI932X_RGB_DISP_IF_CTRL2	0x0F
#define ILI932X_POW_CTRL1			0x10
#define ILI932X_POW_CTRL2			0x11
#define ILI932X_POW_CTRL3			0x12
#define ILI932X_POW_CTRL4			0x13
#define ILI932X_GRAM_HOR_AD			0x20
#define ILI932X_GRAM_VER_AD			0x21
#define ILI932X_RW_GRAM				0x22
#define ILI932X_POW_CTRL7			0x29
#define ILI932X_FRM_RATE_COL_CTRL	0x2B
#define ILI932X_GAMMA_CTRL1			0x30
#define ILI932X_GAMMA_CTRL2			0x31
#define ILI932X_GAMMA_CTRL3			0x32
#define ILI932X_GAMMA_CTRL4			0x35
#define ILI932X_GAMMA_CTRL5			0x36
#define ILI932X_GAMMA_CTRL6			0x37
#define ILI932X_GAMMA_CTRL7			0x38
#define ILI932X_GAMMA_CTRL8			0x39
#define ILI932X_GAMMA_CTRL9			0x3C
#define ILI932X_GAMMA_CTRL10		0x3D
#define ILI932X_HOR_START_AD		0x50
#define ILI932X_HOR_END_AD			0x51
#define ILI932X_VER_START_AD		0x52
#define ILI932X_VER_END_AD			0x53
#define ILI932X_GATE_SCAN_CTRL1		0x60
#define ILI932X_GATE_SCAN_CTRL2		0x61
#define ILI932X_GATE_SCAN_CTRL3		0x6A
#define ILI932X_PART_IMG1_DISP_POS	0x80
#define ILI932X_PART_IMG1_START_AD	0x81
#define ILI932X_PART_IMG1_END_AD	0x82
#define ILI932X_PART_IMG2_DISP_POS	0x83
#define ILI932X_PART_IMG2_START_AD	0x84
#define ILI932X_PART_IMG2_END_AD	0x85
#define ILI932X_PANEL_IF_CTRL1		0x90
#define ILI932X_PANEL_IF_CTRL2		0x92
#define ILI932X_PANEL_IF_CTRL3		0x93
#define ILI932X_PANEL_IF_CTRL4		0x95
#define ILI932X_PANEL_IF_CTRL5		0x97
#define ILI932X_PANEL_IF_CTRL6		0x98

#define ILI932X_GRAM_ADX			ILI932X_GRAM_HOR_AD
#define ILI932X_GRAM_ADY			ILI932X_GRAM_VER_AD
#define ILI932X_START_ADX   		ILI932X_HOR_START_AD
#define ILI932X_END_ADX   			ILI932X_HOR_END_AD
#define ILI932X_START_ADY   		ILI932X_VER_START_AD
#define ILI932X_END_ADY   			ILI932X_VER_END_AD

#define GLCD_VAL_ENTRY_MOD			0x0030
#define GLCD_ORN_PORTRAIT


#endif  // _DRIVERS_DISPLAY_ILI9328_H_
