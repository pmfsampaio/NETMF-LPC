//-----------------------------------------------------------------------------
// Software that is described herein is for illustrative purposes only  
// which provides customers with programming information regarding the  
// products. This software is supplied "AS IS" without any warranties.  
// NXP Semiconductors assumes no responsibility or liability for the 
// use of the software, conveys no license or title under any patent, 
// copyright, or mask work right to the product. NXP Semiconductors 
// reserves the right to make changes in the software without 
// notification. NXP Semiconductors also make no representation or 
// warranty that such application will be suitable for the specified 
// use without further testing or modification. 
//-----------------------------------------------------------------------------

#include <tinyhal.h>
#include "MTF-TQ35SP741-AV.h"
#include <LPC24XX_LCDC.h>

#include <Drivers\Display\TextFonts\Font8x8\font8x8.cpp>

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_TQ35SP741_Driver"
#endif

TQ35SP741_Driver g_TQ35SP741_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//

BOOL TQ35SP741_Driver::Initialize()
{
     if ( g_TQ35SP741_Driver.m_initialized == TRUE) return TRUE;

    BOOL bRet = TRUE;


   // turn off everything first 

     // Turn off LCD (PC8)
    CPU_GPIO_EnableOutputPin( g_TQ35SP741_Config.LcdConfig.LcdEnable.Pin, !g_TQ35SP741_Config.LcdConfig.LcdEnable.ActiveState );

    LCD_Controller_Enable(FALSE);

    
    bRet = LCD_Controller_Initialize(g_TQ35SP741_Config.ControllerConfig);


    LPC24XX_LCDC_Driver::SetScreenBuffer(g_TQ35SP741_Config.LcdConfig.ScreenBuffer);

    Clear();
	
    LCD_Controller_Enable(TRUE);


    HAL_Time_Sleep_MicroSeconds(50000);

   
    Display_Init( g_TQ35SP741_Config.LcdConfig );


    // Turn on LCD
    CPU_GPIO_EnableOutputPin( g_TQ35SP741_Config.LcdConfig.LcdEnable.Pin, g_TQ35SP741_Config.LcdConfig.LcdEnable.ActiveState );

     g_TQ35SP741_Driver.m_initialized = TRUE;
    return bRet;
}

BOOL TQ35SP741_Driver::Uninitialize()
{    

    if ( g_TQ35SP741_Driver.m_initialized  == TRUE)
    {
          Clear();

          LCD_Controller_Enable(FALSE);

          // Turn off LCD (PC8)
    	   CPU_GPIO_EnableOutputPin( g_TQ35SP741_Config.LcdConfig.LcdEnable.Pin, !g_TQ35SP741_Config.LcdConfig.LcdEnable.ActiveState );
          g_TQ35SP741_Driver.m_initialized  = FALSE;
         return LCD_Controller_Uninitialize();
    }
    else
    {
    	 return TRUE;
    }
	
}

void TQ35SP741_Driver::PowerSave( BOOL On )
{
    return;
}

void TQ35SP741_Driver::Clear()
{
    GLOBAL_LOCK(irq);
    memset( LCD_GetFrameBuffer(), 0, SizeInBytes() );

    g_TQ35SP741_Driver.m_cursor = 0;
}

// Macro for retriving pixel value in 1-bit bitmaps
#define TQ35SP741_GETBIT(_x,_y,_data,_widthInWords) (((_data[((_x)/32) + (_y)*(_widthInWords)])>>((_x)%32)) & 0x1)
#define LCD_BITBLT_COLOR_0  0x0000
#define LCD_BITBLT_COLOR_1  0x9E79

void TQ35SP741_Driver::BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ASSERT(width  <= g_TQ35SP741_Config.ControllerConfig.Width );
    ASSERT(height <= g_TQ35SP741_Config.ControllerConfig.Height);

    BitBltEx( 0, 0, width, height, data );

#if 0
    UINT32* ScreenBuffer = LCD_GetFrameBuffer();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x+=2)
        {
            UINT32 val = 0;
            if(TQ35SP741_GETBIT(x  ,y,data,widthInWords)) val |=          LCD_BITBLT_COLOR_1       ;
            else                                            val |=          LCD_BITBLT_COLOR_0       ;
            if(TQ35SP741_GETBIT(x+1,y,data,widthInWords)) val |= ((UINT32)LCD_BITBLT_COLOR_1) << 16;
            else                                            val |= ((UINT32)LCD_BITBLT_COLOR_0) << 16;

            ScreenBuffer[y*WidthInWords() + x/2] = val;
        }
    }
#endif
}

void TQ35SP741_Driver::BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();

    ASSERT((x >= 0) && ((x+width) <= g_TQ35SP741_Config.ControllerConfig.Width));
    ASSERT((y >= 0) && ((y+height) <= g_TQ35SP741_Config.ControllerConfig.Height));

    UINT16 * StartOfLine_src = (UINT16 *)&data[0];
    UINT32 * StartOfLine_dst = (UINT32 *)LCD_GetFrameBuffer();

    UINT16 offset = (y * g_TQ35SP741_Config.ControllerConfig.Width) + x;

    StartOfLine_src += offset;
    StartOfLine_dst += offset;


    while( height-- )
    {
        UINT16 * src;
        UINT32 * dst;
        int      Xcnt;

        src = StartOfLine_src;
        dst = StartOfLine_dst;
        Xcnt = width;

        while( Xcnt-- )
        {
            *dst++ = LCD_ConvertColor(*src++);
        }

        StartOfLine_src += g_TQ35SP741_Config.ControllerConfig.Width;
        StartOfLine_dst += g_TQ35SP741_Config.ControllerConfig.Width;
    }

#if 0
    // Make sure the region being redrawn is completely inside the screen
    ASSERT((x >= 0) && ((x+width)  <= g_TQ35SP741_Config.ControllerConfig.Width));
    ASSERT((y >= 0) && ((y+height) <= g_TQ35SP741_Config.ControllerConfig.Height));

    // Adjust x and width so they start out word-aligned
    UINT32  leftAdjustment = x % PixelsPerWord();
    x     -= leftAdjustment;
    width += leftAdjustment;


    // Set the starting addresses and size based on the clipping region
    UINT32  firstPixelAdj = (y * WidthInWords()) + (x / PixelsPerWord());
    UINT32* destAddr      = LCD_GetFrameBuffer() + firstPixelAdj;
    UINT32* srcAddr       = data                                  + firstPixelAdj;
    UINT32  widthInBytes  = (width + (PixelsPerWord() - 1)) / PixelsPerWord() * 4;

    // Copy away
    for(int i = 0; i < height; i++)
    {
        memcpy(destAddr, srcAddr, widthInBytes);
        destAddr += WidthInWords();
        srcAddr  += WidthInWords();
    }
#endif
}

void TQ35SP741_Driver::WriteChar( unsigned char c, int row, int col )
{
    // convert to LCD pixel coordinates
    row *= Font_Height();
    col *= Font_Width();

    if(row > (g_TQ35SP741_Config.ControllerConfig.Height - Font_Height())) return;
    if(col > (g_TQ35SP741_Config.ControllerConfig.Width  - Font_Width() )) return;

    const UINT8* font = Font_GetGlyph( c );

    UINT32 * ScreenBuffer = (UINT32 *)LCD_GetFrameBuffer();

#if 0
    for(int y = 0; y < Font_Height(); y++)
    {
        for(int x = 0; x < Font_Width(); x+=2)
        {
        	unsigned long long val = 0;
            // the font data is mirrored
            if(TQ35SP741_GETBIT(Font_Width() -  x   ,y,font,1)) {
            	val |= 0xffffff;
            }
            if(TQ35SP741_GETBIT(Font_Width() - (x+1),y,font,1)) {
            	val |= 0xffffff00000000ll;
            }

            ScreenBuffer[(row+y)*WidthInWords() + (col+x)/2] = val;
        }
    }
#endif
    for(int y = 0; y < Font_Height(); y++)
    {
        for(int x = 0; x < Font_Width(); x+=1)
        {
            // the font data is mirrored
            if(TQ35SP741_GETBIT(Font_Width() - 1 - x  ,y,font,1))
                ScreenBuffer[(row+y)*g_TQ35SP741_Config.ControllerConfig.Width + (col+x)] = 0xFFFFFFFF;
            else
                ScreenBuffer[(row+y)*g_TQ35SP741_Config.ControllerConfig.Width + (col+x)] = 0x00000000;
        }
    }

}

void TQ35SP741_Driver::WriteFormattedChar( unsigned char c )
{

     if ( g_TQ35SP741_Driver.m_initialized == FALSE) return;

    if(c < 32)
    {
        switch(c)
        {
        case '\b':                      /* backspace, clear previous char and move cursor back */
            if((g_TQ35SP741_Driver.m_cursor % TextColumns()) > 0)
            {
                g_TQ35SP741_Driver.m_cursor--;
                LCD_WriteChar( ' ', g_TQ35SP741_Driver.m_cursor / TextColumns(), g_TQ35SP741_Driver.m_cursor % TextColumns() );
            }
            break;

        case '\f':                      /* formfeed, clear screen and home cursor */
            //LCD_Clear();
            g_TQ35SP741_Driver.m_cursor = 0;
            break;

        case '\n':                      /* newline */
            g_TQ35SP741_Driver.m_cursor += TextColumns();
            g_TQ35SP741_Driver.m_cursor -= (g_TQ35SP741_Driver.m_cursor % TextColumns());
            break;

        case '\r':                      /* carriage return */
            g_TQ35SP741_Driver.m_cursor -= (g_TQ35SP741_Driver.m_cursor % TextColumns());
            break;

        case '\t':                      /* horizontal tab */
            g_TQ35SP741_Driver.m_cursor += (Font_TabWidth() - ((g_TQ35SP741_Driver.m_cursor % TextColumns()) % Font_TabWidth()));
            // deal with line wrap scenario
            if((g_TQ35SP741_Driver.m_cursor % TextColumns()) < Font_TabWidth())
            {
                // bring the cursor to start of line
                g_TQ35SP741_Driver.m_cursor -= (g_TQ35SP741_Driver.m_cursor % TextColumns());
            }
            break;

        case '\v':                      /* vertical tab */
            g_TQ35SP741_Driver.m_cursor += TextColumns();
            break;

        default:
            debug_printf("Unrecognized control character in LCD_WriteChar");
            break;
        }
    }
    else
    {
        LCD_WriteChar( c, g_TQ35SP741_Driver.m_cursor / TextColumns(), g_TQ35SP741_Driver.m_cursor % TextColumns() );
        g_TQ35SP741_Driver.m_cursor++;
    }

    if(g_TQ35SP741_Driver.m_cursor >= (TextColumns() * TextRows()))
    {
        g_TQ35SP741_Driver.m_cursor = 0;
    }
}

UINT32 TQ35SP741_Driver::PixelsPerWord()
{
    return ((8*sizeof(UINT32)) / g_TQ35SP741_Config.ControllerConfig.BitsPerPixel);
}

UINT32 TQ35SP741_Driver::TextRows()
{
    return (g_TQ35SP741_Config.ControllerConfig.Height / Font_Height());
}

UINT32 TQ35SP741_Driver::TextColumns()
{
    return (g_TQ35SP741_Config.ControllerConfig.Width / Font_Width());
}

UINT32 TQ35SP741_Driver::WidthInWords()
{
    return ((g_TQ35SP741_Config.ControllerConfig.Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}

UINT32 TQ35SP741_Driver::SizeInWords()
{
    return (WidthInWords() * g_TQ35SP741_Config.ControllerConfig.Height);
}

UINT32 TQ35SP741_Driver::SizeInBytes()
{
    return (SizeInWords() * sizeof(UINT32));
}

void TQ35SP741_Driver::Display_Init( TQ35SP741_LCD_CONFIG& LcdConfig )
{
#if 0
    Write_SPI(LcdConfig, 0x00, 0x0001);
    HAL_Time_Sleep_MicroSeconds(20000);

    Write_SPI(LcdConfig, 0x03, 0xA2A4);
    Write_SPI(LcdConfig, 0x0C, 0x0004);
    Write_SPI(LcdConfig, 0x0D, 0x0308);
    Write_SPI(LcdConfig, 0x0E, 0x3000);
    HAL_Time_Sleep_MicroSeconds(50000);

    Write_SPI(LcdConfig, 0x1E, 0x00AF);

    Write_SPI(LcdConfig, 0x01, 0x693f);

    Write_SPI(LcdConfig, 0x02, 0x0600);
    Write_SPI(LcdConfig, 0x10, 0x0000);
    Write_SPI(LcdConfig, 0x07, 0x0233);
    Write_SPI(LcdConfig, 0x0B, 0x0039);
    Write_SPI(LcdConfig, 0x0F, 0x0000);
    HAL_Time_Sleep_MicroSeconds(50000);
    
    Write_SPI(LcdConfig, 0x30, 0x0707);
    Write_SPI(LcdConfig, 0x31, 0x0204);
    Write_SPI(LcdConfig, 0x32, 0x0204);
    Write_SPI(LcdConfig, 0x33, 0x0502);
    Write_SPI(LcdConfig, 0x34, 0x0507);
    Write_SPI(LcdConfig, 0x35, 0x0204);
    Write_SPI(LcdConfig, 0x36, 0x0204);
    Write_SPI(LcdConfig, 0x37, 0x0502);
    Write_SPI(LcdConfig, 0x3A, 0x0302);
    Write_SPI(LcdConfig, 0x3B, 0x0302);
    Write_SPI(LcdConfig, 0x23, 0x0000);
    Write_SPI(LcdConfig, 0x24, 0x0000);
    Write_SPI(LcdConfig, 0x48, 0x0000);
    Write_SPI(LcdConfig, 0x49, 0x013F);
    Write_SPI(LcdConfig, 0x4A, 0x0000);
    Write_SPI(LcdConfig, 0x4B, 0x0000);
    Write_SPI(LcdConfig, 0x41, 0x0000);
    Write_SPI(LcdConfig, 0x42, 0x0000);
    Write_SPI(LcdConfig, 0x44, 0xEF00);
    Write_SPI(LcdConfig, 0x45, 0x0000);
    Write_SPI(LcdConfig, 0x46, 0x013F);
    HAL_Time_Sleep_MicroSeconds(50000);
  
    Write_SPI(LcdConfig, 0x44, 0xEF00);
    Write_SPI(LcdConfig, 0x45, 0x0000);
    Write_SPI(LcdConfig, 0x4E, 0x0000);
    Write_SPI(LcdConfig, 0x4F, 0x0000);
    Write_SPI(LcdConfig, 0x46, 0x013F);
#endif
    Write_SPI(LcdConfig, 0x01, 0x633f);
    Write_SPI(LcdConfig, 0x0A, 0x4008);
    HAL_Time_Sleep_MicroSeconds(50000);
}
  
void TQ35SP741_Driver::Write_SPI ( TQ35SP741_LCD_CONFIG& LcdConfig, UINT16 addr, UINT16 data )
{
    UINT8 SPIData[3];

    SPIData[0] = 0x70;
    SPIData[1] = 0;
    SPIData[2] = addr & 0xff;
    CPU_SPI_nWrite8_nRead8 (LcdConfig.SPI_Config, SPIData, 3, 0, 0, 0);

    SPIData[0] = 0x72;
    SPIData[1] = (data >> 8) & 0xff;
    SPIData[2] = data & 0xff;
    CPU_SPI_nWrite8_nRead8 (LcdConfig.SPI_Config, SPIData, 3, 0, 0, 0);
}
