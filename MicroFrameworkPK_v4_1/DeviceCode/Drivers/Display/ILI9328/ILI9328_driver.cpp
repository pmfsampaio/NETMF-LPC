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

#include <tinyhal.h>
#include "ILI9328.h"

#undef  TRACE_ALWAYS
#define TRACE_ALWAYS                       0x00000001
#undef  DEBUG_TRACE
#define DEBUG_TRACE (TRACE_ALWAYS)

ILI9328_Driver g_ILI9328_Driver;

void ILI9328_Driver::Delay_MS (UINT16 time)
{
    UINT32 i;
   
    i = 1;//31250;          // 8 ns/instruction * 4 instructions * loop_count = 1ms = 1000000 ns
    i *= time;
    while (i--);        /* loop count */
}

void ILI9328_Driver::Reg_Write (UINT16 reg_addr, UINT16 data)
{
    // memory mapping register is platform dependant
    volatile UINT16 * indexReg = (UINT16 *)g_ILI9328_Config.LcdConfig.ControlAddress;
    volatile UINT16 * dataReg  = (UINT16 *)g_ILI9328_Config.LcdConfig.DataAddress;

    *indexReg = reg_addr;   /* send the register address to the index register, to set the index register value */
    *dataReg = data;        /* send the data to write to the indexed register */
}

UINT16 ILI9328_Driver::Reg_Read (UINT16 reg_addr)
{
    volatile UINT16 * indexReg = (UINT16 *)g_ILI9328_Config.LcdConfig.ControlAddress;
    volatile UINT16 * dataReg  = (UINT16 *)g_ILI9328_Config.LcdConfig.DataAddress;
    int val;

    *indexReg = reg_addr;
	val = *dataReg & 0xffff;
	return val;
}

void ILI9328_Driver::Set_Display_On( void )
{
#if 0
    Reg_Write(DISP_CTRL_REG, 0x0001);
    Delay_MS (100);                             /* 3Frame   */
    Reg_Write(DISP_CTRL_REG, 0x0021);
    Reg_Write(DISP_CTRL_REG, 0x0023);
    Delay_MS (100);                             /* 3Frame   */  
    Reg_Write(DISP_CTRL_REG, 0x0037);      /***normaly white ***/
#endif
#if 0
    Reg_Write(ILI9325_POW_CTRL_1, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    Reg_Write(ILI9325_POW_CTRL_2, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0]  */
    Reg_Write(LI9325_POW_CTRL_3, 0x0000); /* VREG1OUT voltage  */
    Reg_Write(ILI9325_POW_CTRL_4, 0x0000); /* VDV[4:0] for VCOM amplitude  */
     Delay_MS(200); /* Dis-charge capacitor power voltage */

     Reg_Write(ILI9325_POW_CTRL_1, 0x1690); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
     Reg_Write(ILI9325_POW_CTRL_2, 0x0227); /* R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]  */
     Delay_MS(50);

     Reg_Write(ILI9325_POW_CTRL_3, 0x001D); /* External reference voltage= Vci  */
     Delay_MS(50);

     Reg_Write(ILI9325_POW_CTRL_4, 0x0800); /* R13=1D00 when R12=009D;VDV[4:0] for VCOM amplitude  */
     Reg_Write(ILI9325_POW_CTRL_7, 0x0012); /* R29=0013 when R12=009D;VCM[5:0] for VCOMH  */
     Reg_Write(ILI9325_FRM_RATE_COLOR, 0x000B); /* Frame Rate = 70Hz  */
     Delay_MS(50);
#endif
}

void ILI9328_Driver::Set_Display_Off (void)
{
#if 0
    Reg_Write(DISP_CTRL_REG, 0x0032);      /* GON = 1, DTE = 1, D1-0 = 10 */
    Delay_MS (100);                             /* 3Frame */
    Reg_Write(DISP_CTRL_REG, 0x0022);      /* GON = 1, DTE = 0, D1-0 = 10 */
    Delay_MS (100);                             /* 3Frame */
    Reg_Write(DISP_CTRL_REG, 0x0000);      /* GON = 0, DTE = 0, D1-0 = 00 */

#if 0 // JJ: this was the original code, I added more code to follow the manual */
    Reg_Write (PWR1_CTRL_REG, 0x0000);
#else
    Reg_Write(PWR1_CTRL_REG, 0x0600);      /* BT2-0 = 110 */
    Delay_MS (100);                             /* wait 100ms */    
    Reg_Write(PWR4_CTRL_REG, 0x0000);      /* PON = 0 */
    Reg_Write(PWR5_CTRL_REG, 0x0000);      /* VCOMG = 0 */
    Reg_Write(PWR1_CTRL_REG, 0x0000);      /* BT2-0 = 000, AP2-0 000 */
#endif
#endif
}


void ILI9328_Driver::Clear()
{
    register INT32 i;
    volatile UINT16 * dataReg = (UINT16 *)g_ILI9328_Config.LcdConfig.DataAddress;
    
    SetWindow(0, DISP_XMAX-1, 0, DISP_YMAX-1);
    for (i = 0; i < DISP_YMAX * DISP_XMAX; i++)
    {
        *dataReg = WHITE;
    }
}

//--//

BOOL ILI9328_Driver::Initialize()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    BOOL bRet = TRUE;
    

    //reset the cursor pos to the begining
    g_ILI9328_Driver.m_cursor = 0;
    
//    g_LPC22XX_GPIO_Driver.EnableOutputPin(LPC22XX_GPIO::c_P0_21, FALSE);
//    g_LPC22XX_GPIO_Driver.EnableOutputPin(g_ILI9328_Config.LcdConfig.Backlight.Pin, FALSE);
//    		LPC22XX_GPIO::c_P0_30, FALSE);
#if 0
	/*
	 *  0010 0000 0000 0000 0000 1100 0100 0000
	 * |    |    |    |    |    |    |    |    |
	 *                       WST2   WST1   IDLE
	 * |00xx|RWP0|----|----|wwww|wBww|www-|iiii|
	 *    |  ||||                 |
	 *    |  |||+-- BUSERR        +-- RBLE
	 *    |  ||+--- WPERR
	 *    |  |+---- WRITE PROTECT
	 *    |  +----- Burst-ROM
	 *    +-------- 00 - 8 / 01 - 16 / 10 - 32 bits
	 */
	LPC22XX::EMC().BCFG3 = 0x20000c40;
#endif
#if 1
	Reg_Write(0x00E3, 0x3008); //set the internal timing
	Reg_Write(0x00E7, 0x0012); //set the internal timing
	Reg_Write(0x00EF, 0x1231); //set the internal timing
	Reg_Write(ILI932X_START_OSC, 0x0001); //start oscillator
	Delay_MS(50);
	Reg_Write(ILI932X_DRIV_OUT_CTRL, 0x0100); //set SS, SM
	Reg_Write(ILI932X_DRIV_WAV_CTRL, 0x0700); //set 1 line inversion
	Reg_Write(ILI932X_ENTRY_MOD, GLCD_VAL_ENTRY_MOD); //set GRAM write direction, BGR=0
	Reg_Write(ILI932X_RESIZE_CTRL, 0x0000); //no resizing
	Reg_Write(ILI932X_DRIV_OUT_CTRL, 0x0100); //front & back porch periods = 2
	Reg_Write(ILI932X_DISP_CTRL3, 0x0000);
	Reg_Write(ILI932X_DISP_CTRL4, 0x0000);
	Reg_Write(ILI932X_RGB_DISP_IF_CTRL1, 0x0000); //select system interface
	Reg_Write(ILI932X_FRM_MARKER_POS, 0x0000);
	Reg_Write(ILI932X_RGB_DISP_IF_CTRL2, 0x0000);
	Reg_Write(ILI932X_POW_CTRL1, 0x0000);
	Reg_Write(ILI932X_POW_CTRL2, 0x0007);
	Reg_Write(ILI932X_POW_CTRL3, 0x0000);
	Reg_Write(ILI932X_POW_CTRL4, 0x0000);
	Delay_MS(200);
	Reg_Write(ILI932X_POW_CTRL1, 0x1690);
	Reg_Write(ILI932X_POW_CTRL2, 0x0227); // 0x137
	Delay_MS(50);
	Reg_Write(ILI932X_POW_CTRL3, 0x001A); // 0x13c
	Delay_MS(50);
	Reg_Write(ILI932X_POW_CTRL4, 0x1800); // 0x1400
	Reg_Write(ILI932X_POW_CTRL7, 0x002A); // 0x0007
	Delay_MS(50);
	Reg_Write(ILI932X_GRAM_HOR_AD, 0x0000);
	Reg_Write(ILI932X_GRAM_VER_AD, 0x0000);
	Reg_Write(ILI932X_GAMMA_CTRL1, 0x0007);
	Reg_Write(ILI932X_GAMMA_CTRL2, 0x0605);
	Reg_Write(ILI932X_GAMMA_CTRL3, 0x0106);
	Reg_Write(ILI932X_GAMMA_CTRL4, 0x0206);
	Reg_Write(ILI932X_GAMMA_CTRL5, 0x0808);
	Reg_Write(ILI932X_GAMMA_CTRL6, 0x0007);
	Reg_Write(ILI932X_GAMMA_CTRL7, 0x0201);
	Reg_Write(ILI932X_GAMMA_CTRL8, 0x0007);
	Reg_Write(ILI932X_GAMMA_CTRL9, 0x0602);
	Reg_Write(ILI932X_GAMMA_CTRL10, 0x0808);

	Reg_Write(ILI932X_HOR_START_AD, 0x0000);
	Reg_Write(ILI932X_HOR_END_AD, 0x00EF);
	Reg_Write(ILI932X_VER_START_AD, 0x0000);
	Reg_Write(ILI932X_VER_END_AD, 0x013F);

	Reg_Write(ILI932X_GATE_SCAN_CTRL1, 0xA700);
	Reg_Write(ILI932X_GATE_SCAN_CTRL2, 0x0001);
	Reg_Write(ILI932X_GATE_SCAN_CTRL3, 0x0000);

	Reg_Write(ILI932X_PART_IMG1_DISP_POS, 0x0000);
	Reg_Write(ILI932X_PART_IMG1_START_AD, 0x0000);
	Reg_Write(ILI932X_PART_IMG1_END_AD, 0x0000);

	Reg_Write(ILI932X_PART_IMG2_DISP_POS, 0x0000);
	Reg_Write(ILI932X_PART_IMG2_START_AD, 0x0000);
	Reg_Write(ILI932X_PART_IMG2_END_AD, 0x0000);

	Reg_Write(ILI932X_PANEL_IF_CTRL1, 0x0010);
	Reg_Write(ILI932X_PANEL_IF_CTRL2, 0x0000);
	Reg_Write(ILI932X_PANEL_IF_CTRL3, 0x0003);
	Reg_Write(ILI932X_PANEL_IF_CTRL4, 0x0110);
	Reg_Write(ILI932X_PANEL_IF_CTRL5, 0x0000);
	Reg_Write(ILI932X_PANEL_IF_CTRL6, 0x0000);

	Reg_Write(ILI932X_DISP_CTRL1, 0x0133);
#else
	Reg_Write(0x00E5,0x8000);// Set the Vcore voltage and this setting is must.
	Reg_Write(ILI932X_START_OSC,0x0001);// Start internal OSC.

	Reg_Write(ILI932X_DRIV_OUT_CTRL,0x0100);// set SS and SM bit
	Reg_Write(0x0002,0x0700);// set 1 line inversion
	Reg_Write(0x0003,0x1030);//0x92b0);// TRI=0, DFM=0, set GRAM write direction and BGR=1.
	Reg_Write(0x0004,0x0000);// Resize register
	Reg_Write(0x0008,0x0202);// set the back porch and front porch
	Reg_Write(0x0009,0000);// set non-display area refresh cycle ISC[3:0]
	Reg_Write(0x000A,0000);// FMARK function
	Reg_Write(0x000C,0x0000);// RGB interface setting
	Reg_Write(0x000D,0x0000);// Frame marker Position
	Reg_Write(0x000F,0x0000);// RGB interface polarity

	Reg_Write(0x0010,0x0000);// Power On sequence  //SAP, BT[3:0], AP, DSTB, SLP, STB
	Reg_Write(0x0011,0x0007);// DC1[2:0], DC0[2:0], VC[2:0]
	Reg_Write(0x0012,0x0000);// VREG1OUT voltage
	Reg_Write(0x0013,0x0000);// VDV[4:0] for VCOM amplitude
	Delay_MS(200);
	Reg_Write(0x0010,0x17B0);// SAP, BT[3:0], AP, DSTB, SLP, STB
	Reg_Write(0x0011,0x0007);// R11h=0x0001 at VCI=3.3V DC1[2:0], DC0[2:
	Delay_MS(50);
	Reg_Write(0x0012,0x013E);// R11h=0x0138 at VCI=3.3V VREG1OUT voltage
	Delay_MS(50);

	Reg_Write(0x0013,0x1F00);// R11h=0x1800 at VCI=2.8V VDV[4:0] for VCO
	Reg_Write(0x0029,0x0013);// setting VCM for VCOMH  0018-0012
	Delay_MS(50);

	Reg_Write(0x0020,0x0000);// GRAM horizontal Address
	Reg_Write(0x0021,0x0000);// GRAM Vertical Address

	Reg_Write(0x0030,0x0000);// - Adjust the Gamma Curve -//
	Reg_Write(0x0031,0x0404);
	Reg_Write(0x0032,0x0404);
	Reg_Write(0x0035,0x0004);
	Reg_Write(0x0036,0x0404);
	Reg_Write(0x0037,0x0404);
	Reg_Write(0x0038,0x0404);
	Reg_Write(0x0039,0x0707);
	Reg_Write(0x003C,0x0500);
	Reg_Write(0x003D,0x0607);// - Adjust the Gamma Curve -//

	//DelayMs(15);
	Reg_Write(0x0050,0x0000);// Horizontal GRAM Start Address
	Reg_Write(0x0051,0x00EF);// Horizontal GRAM End Address
	Reg_Write(0x0052,0x0000);// Vertical GRAM Start Address
	Reg_Write(0x0053,0x013F);// Vertical GRAM Start Address
	Reg_Write(0x0060,0x2700);// Gate Scan Line
	Reg_Write(0x0061,0x0001);// NDL,VLE, REV
	Reg_Write(0x006A,0x0000);// set scrolling line

	Reg_Write(0x0080,0x0000);//- Partial Display Control -//
	Reg_Write(0x0081,0x0000);
	Reg_Write(0x0082,0x0000);
	Reg_Write(0x0083,0x0000);
	Reg_Write(0x0084,0x0000);
	Reg_Write(0x0085,0x0000);

	Reg_Write(0x0090,0x0010);//- Panel Control -//
	Reg_Write(0x0092,0x0000);
	Reg_Write(0x0093,0x0003);
	Reg_Write(0x0095,0x0110);
	Reg_Write(0x0097,0x0000);
	Reg_Write(0x0098,0x0000);//- Panel Control -//
	Reg_Write(0x0007,0x173);//0x0133);//Display Control and display ON

	int aux = Reg_Read(ILI932X_START_OSC);

#endif
    Clear();
    Set_Display_On();    
//    g_LPC22XX_GPIO_Driver.SetPinState(LPC22XX_GPIO::c_P0_21, TRUE);
//    g_LPC22XX_GPIO_Driver.EnableOutputPin(g_ILI9328_Config.LcdConfig.Backlight.Pin, TRUE);
    return bRet;
}

BOOL ILI9328_Driver::Uninitialize()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    Clear();
#if 0
    Set_Display_Off();

    Delay_MS (1);
    Reg_Write (OSCILLATION_REG, 0x0001);
    Delay_MS (10);
    
    Reg_Write (PWR1_CTRL_REG, 0x0000);
    Reg_Write (PWR2_CTRL_REG, 0x0000);  
    Reg_Write (PWR3_CTRL_REG, 0x0000);
    Reg_Write (PWR4_CTRL_REG, 0x0F00);  /* Pon = 0 */
    Reg_Write (PWR5_CTRL_REG, 0x0E0F);  /* VCOMG=0 */
    Reg_Write (PWR1_CTRL_REG, 0x0003);  /* SLP="1",STB="1" */
#endif
    return TRUE;
}

void ILI9328_Driver::PowerSave( BOOL On )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return;
}

void ILI9328_Driver::SetWindow(UINT16 xstart,UINT16 xend,UINT16 ystart,UINT16 yend )
 {
    volatile UINT16 * indexReg = (UINT16 *)g_ILI9328_Config.LcdConfig.ControlAddress;

	Reg_Write(0x0020,xstart);    //x start command
	Reg_Write(0x0021,ystart);    //y start command

	Reg_Write(0x0050,xstart);    //x
	Reg_Write(0x0051,xend);      //x
	Reg_Write(0x0052,ystart);    //y
	Reg_Write(0x0053,yend);      //y

    *indexReg = 0x0022;
}

// Macro for retriving pixel value in 1-bit bitmaps
//#define ILI9328_GETBIT(_x,_y,_data,_widthInWords) (((_data[((_x)/32) + (_y)*(_widthInWords)])>>((_x)%32)) & 0x1)
#define ILI9328_GETBIT(_x,_y,_data,_widthInWords) ((_data[_y] >> _x)& 0x1)

void ILI9328_Driver::BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ASSERT(width  <= g_ILI9328_Config.ControllerConfig.Width );
    ASSERT(height <= g_ILI9328_Config.ControllerConfig.Height);

    BitBltEx( 0, 0, width, height, data );
}

void ILI9328_Driver::BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();

    ASSERT((x >= 0) && ((x+width) <= LCD_SCREEN_WIDTH));
    ASSERT((y >= 0) && ((y+height) <= LCD_SCREEN_HEIGHT));

    volatile UINT16 * dataReg = (UINT16 *)g_ILI9328_Config.LcdConfig.DataAddress;

    UINT16 * StartOfLine_src = (UINT16 *)&data[0];

    UINT16 offset = (y * g_ILI9328_Config.ControllerConfig.Width) + x;

    StartOfLine_src += offset;

    SetWindow(x, x+width-1,y,y+height-1);
    while( height-- )
    {
        UINT16 * src;
        UINT16 * dst;
        int      Xcnt;
        
        src = StartOfLine_src;
        Xcnt = width;

        while( Xcnt-- )
        {
        	*dataReg = *src++;
        }
        
        StartOfLine_src += g_ILI9328_Config.ControllerConfig.Width;
    }
}

void ILI9328_Driver::WriteChar( unsigned char c, int row, int col )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();    
    // convert to LCD pixel coordinates
    
    row *= Font_Height();
    col *= Font_Width();

 
    if(row > (g_ILI9328_Config.ControllerConfig.Height - Font_Height())) return;
    if(col > (g_ILI9328_Config.ControllerConfig.Width  - Font_Width() )) return;

    const UINT8* font = Font_GetGlyph( c );

    volatile UINT16 * dataReg = (UINT16 *)g_ILI9328_Config.LcdConfig.DataAddress;

    SetWindow(col, col+Font_Width()-1, row, row+Font_Height()-1);

    for(int y = 0; y < Font_Height(); y++)
    {
        for(int x = 0; x < Font_Width(); x+=1)
        {
            // the font data is mirrored
            if(ILI9328_GETBIT(Font_Width() - 1 - x  ,y,font,1))
                *dataReg = BLACK;
            else
                *dataReg = WHITE;
        }
    }    
}

void ILI9328_Driver::WriteFormattedChar( unsigned char c )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    
           
    if(c < 32)
    {        
        switch(c)
        {        
        case '\b':                      /* backspace, clear previous char and move cursor back */
            if((g_ILI9328_Driver.m_cursor % TextColumns()) > 0)
            {
                g_ILI9328_Driver.m_cursor--;
                LCD_WriteChar( ' ', g_ILI9328_Driver.m_cursor / TextColumns(), g_ILI9328_Driver.m_cursor % TextColumns() );
            }
            break;

        case '\f':                      /* formfeed, clear screen and home cursor */
            //LCD_Clear();
            g_ILI9328_Driver.m_cursor = 0;
            break;

        case '\n':                      /* newline */
            g_ILI9328_Driver.m_cursor += TextColumns();
            g_ILI9328_Driver.m_cursor -= (g_ILI9328_Driver.m_cursor % TextColumns());
            break;

        case '\r':                      /* carriage return */
            g_ILI9328_Driver.m_cursor -= (g_ILI9328_Driver.m_cursor % TextColumns());
            break;

        case '\t':                      /* horizontal tab */
            g_ILI9328_Driver.m_cursor += (Font_TabWidth() - ((g_ILI9328_Driver.m_cursor % TextColumns()) % Font_TabWidth()));
            // deal with line wrap scenario
            if((g_ILI9328_Driver.m_cursor % TextColumns()) < Font_TabWidth())
            {
                // bring the cursor to start of line
                g_ILI9328_Driver.m_cursor -= (g_ILI9328_Driver.m_cursor % TextColumns());
            }
            break;

        case '\v':                      /* vertical tab */
            g_ILI9328_Driver.m_cursor += TextColumns();
            break;

        default:
            DEBUG_TRACE2(TRACE_ALWAYS, "Unrecognized control character in LCD_WriteChar: %2u (0x%02x)\r\n", (unsigned int) c, (unsigned int) c);
            break;
        }
    }
    else
    {        
        LCD_WriteChar( c, g_ILI9328_Driver.m_cursor / TextColumns(), g_ILI9328_Driver.m_cursor % TextColumns() );
        g_ILI9328_Driver.m_cursor++;
    }

    if(g_ILI9328_Driver.m_cursor >= (TextColumns() * TextRows()))
    {
        g_ILI9328_Driver.m_cursor = 0;
    }
}

UINT32 ILI9328_Driver::PixelsPerWord()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return ((8*sizeof(UINT32)) / g_ILI9328_Config.ControllerConfig.BitsPerPixel);
}

UINT32 ILI9328_Driver::TextRows()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return (g_ILI9328_Config.ControllerConfig.Height / Font_Height());
}

UINT32 ILI9328_Driver::TextColumns()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();    
    return (g_ILI9328_Config.ControllerConfig.Width / Font_Width());
}

UINT32 ILI9328_Driver::WidthInWords()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return ((g_ILI9328_Config.ControllerConfig.Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}

UINT32 ILI9328_Driver::SizeInWords()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return (WidthInWords() * g_ILI9328_Config.ControllerConfig.Height);
}

UINT32 ILI9328_Driver::SizeInBytes()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return (SizeInWords() * sizeof(UINT32));
}
