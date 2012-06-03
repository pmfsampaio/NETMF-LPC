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
#include "UMSH8173MD.h"
#include <LPC178X_LCDC.h>

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_UMSH8173MD_Driver"
#endif

UMSH8173MD_Driver g_UMSH8173MD_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//

BOOL UMSH8173MD_Driver::Initialize()
{
     if ( g_UMSH8173MD_Driver.m_initialized == TRUE) return TRUE;

    BOOL bRet = TRUE;


   // turn off everything first 

     // Turn off LCD (PC8)
 //   CPU_GPIO_EnableOutputPin( g_UMSH8173MD_Config.LcdConfig.LcdEnable.Pin, !g_UMSH8173MD_Config.LcdConfig.LcdEnable.ActiveState );

    LCD_Controller_Enable(FALSE);

    
    bRet = LCD_Controller_Initialize(g_UMSH8173MD_Config.ControllerConfig);


    LPC178X_LCDC_Driver::SetScreenBuffer(g_UMSH8173MD_Config.LcdConfig.ScreenBuffer);

    Clear();
	
    LCD_Controller_Enable(TRUE);


    HAL_Time_Sleep_MicroSeconds(50000);

   
   // Display_Init( g_UMSH8173MD_Config.LcdConfig );


    // Turn on LCD
    CPU_GPIO_EnableOutputPin( g_UMSH8173MD_Config.LcdConfig.LcdEnable.Pin, g_UMSH8173MD_Config.LcdConfig.LcdEnable.ActiveState );

     g_UMSH8173MD_Driver.m_initialized = TRUE;
    return bRet;
}

BOOL UMSH8173MD_Driver::Uninitialize()
{    

    if ( g_UMSH8173MD_Driver.m_initialized  == TRUE)
    {
          Clear();

          LCD_Controller_Enable(FALSE);

          // Turn off LCD (PC8)
    	   CPU_GPIO_EnableOutputPin( g_UMSH8173MD_Config.LcdConfig.LcdEnable.Pin, !g_UMSH8173MD_Config.LcdConfig.LcdEnable.ActiveState );
          g_UMSH8173MD_Driver.m_initialized  = FALSE;
         return LCD_Controller_Uninitialize();
    }
    else
    {
    	 return TRUE;
    }
	
}

void UMSH8173MD_Driver::PowerSave( BOOL On )
{
    return;
}

void UMSH8173MD_Driver::Clear()
{
    GLOBAL_LOCK(irq);
    memset( LCD_GetFrameBuffer(), 0, SizeInBytes() );

    g_UMSH8173MD_Driver.m_cursor = 0;
}


// Macro for retriving pixel value in 1-bit bitmaps
#define UMSH8173MD_GETBIT(_x,_y,_data,_widthInWords) (((_data[((_x)/32) + (_y)*(_widthInWords)])>>((_x)%32)) & 0x1)
#define LCD_BITBLT_COLOR_0  0x0000
#define LCD_BITBLT_COLOR_1  0x9E79

void UMSH8173MD_Driver::BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    // Make sure the region being redrawn is completely inside the screen
    ASSERT((x >= 0) && ((x+width)  <= g_UMSH8173MD_Config.ControllerConfig.Width));
    ASSERT((y >= 0) && ((y+height) <= g_UMSH8173MD_Config.ControllerConfig.Height));
#if 0
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
    UINT16 * StartOfLine_src = (UINT16 *)&data[0];
    UINT16 * StartOfLine_dst = (UINT16 *)LCD_GetFrameBuffer();

    StartOfLine_src += (y * g_UMSH8173MD_Config.ControllerConfig.Width) + x;
    StartOfLine_dst += (y * g_UMSH8173MD_Config.ControllerConfig.Width) + x;

    while( height-- )
    {
        UINT16 * src;
        UINT16 * dst;
        int      Xcnt;

        src = StartOfLine_src;
        dst = StartOfLine_dst;
        Xcnt = width;

        while( Xcnt-- )
        {
            *dst++ = *src++;
        }

        StartOfLine_src += g_UMSH8173MD_Config.ControllerConfig.Width;
        StartOfLine_dst += g_UMSH8173MD_Config.ControllerConfig.Width;
    }

}

void UMSH8173MD_Driver::BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    ASSERT(width  <= g_UMSH8173MD_Config.ControllerConfig.Width );
    ASSERT(height <= g_UMSH8173MD_Config.ControllerConfig.Height);

#if 0
    UINT32* ScreenBuffer = LCD_GetFrameBuffer();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x+=2)
        {
            UINT32 val = 0;
            if(UMSH8173MD_GETBIT(x  ,y,data,widthInWords)) val |=          LCD_BITBLT_COLOR_1       ;
            else                                            val |=          LCD_BITBLT_COLOR_0       ;
            if(UMSH8173MD_GETBIT(x+1,y,data,widthInWords)) val |= ((UINT32)LCD_BITBLT_COLOR_1) << 16;
            else                                            val |= ((UINT32)LCD_BITBLT_COLOR_0) << 16;

            ScreenBuffer[y*WidthInWords() + x/2] = val;
        }
    }
#endif
    BitBltEx( 0, 0, width, height, data );
}

void UMSH8173MD_Driver::WriteChar( unsigned char c, int row, int col )
{
    // convert to LCD pixel coordinates
    row *= Font_Height();
    col *= Font_Width();

    if(row > (g_UMSH8173MD_Config.ControllerConfig.Height - Font_Height())) return;
    if(col > (g_UMSH8173MD_Config.ControllerConfig.Width  - Font_Width() )) return;

    const UINT8* font = Font_GetGlyph( c );

    UINT32* ScreenBuffer = LCD_GetFrameBuffer();

    for(int y = 0; y < Font_Height(); y++)
    {
        for(int x = 0; x < Font_Width(); x+=2)
        {
            UINT32 val = 0;
            // the font data is mirrored
            if(UMSH8173MD_GETBIT(Font_Width() -  x   ,y,font,1)) val |= 0x7fff;
            if(UMSH8173MD_GETBIT(Font_Width() - (x+1),y,font,1)) val |= 0x7fff0000;

            ScreenBuffer[(row+y)*WidthInWords() + (col+x)/2] = val;
        }
    }
}


#if 0
// Macro for retriving pixel value in 1-bit bitmaps
#define UMSH8173MD_GETBIT(_x,_y,_data,_widthInWords) (((_data[((_x)/32) + (_y)*(_widthInWords)])>>((_x)%32)) & 0x1)
#define LCD_BITBLT_COLOR_0  0x0000
#define LCD_BITBLT_COLOR_1  0x9E79

void UMSH8173MD_Driver::BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ASSERT(width  <= g_UMSH8173MD_Config.ControllerConfig.Width );
    ASSERT(height <= g_UMSH8173MD_Config.ControllerConfig.Height);

    BitBltEx( 0, 0, width, height, data );

#if 0
    UINT32* ScreenBuffer = LCD_GetFrameBuffer();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x+=2)
        {
            UINT32 val = 0;
            if(UMSH8173MD_GETBIT(x  ,y,data,widthInWords)) val |=          LCD_BITBLT_COLOR_1       ;
            else                                            val |=          LCD_BITBLT_COLOR_0       ;
            if(UMSH8173MD_GETBIT(x+1,y,data,widthInWords)) val |= ((UINT32)LCD_BITBLT_COLOR_1) << 16;
            else                                            val |= ((UINT32)LCD_BITBLT_COLOR_0) << 16;

            ScreenBuffer[y*WidthInWords() + x/2] = val;
        }
    }
#endif
}

void UMSH8173MD_Driver::BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();

    ASSERT((x >= 0) && ((x+width) <= g_UMSH8173MD_Config.ControllerConfig.Width));
    ASSERT((y >= 0) && ((y+height) <= g_UMSH8173MD_Config.ControllerConfig.Height));

    UINT16 * StartOfLine_src = (UINT16 *)&data[0];
    UINT32 * StartOfLine_dst = (UINT32 *)LCD_GetFrameBuffer();

    UINT16 offset = (y * g_UMSH8173MD_Config.ControllerConfig.Width) + x;

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

        StartOfLine_src += g_UMSH8173MD_Config.ControllerConfig.Width;
        StartOfLine_dst += g_UMSH8173MD_Config.ControllerConfig.Width;
    }

#if 0
    // Make sure the region being redrawn is completely inside the screen
    ASSERT((x >= 0) && ((x+width)  <= g_UMSH8173MD_Config.ControllerConfig.Width));
    ASSERT((y >= 0) && ((y+height) <= g_UMSH8173MD_Config.ControllerConfig.Height));

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

void UMSH8173MD_Driver::WriteChar( unsigned char c, int row, int col )
{
    // convert to LCD pixel coordinates
    row *= Font_Height();
    col *= Font_Width();

    if(row > (g_UMSH8173MD_Config.ControllerConfig.Height - Font_Height())) return;
    if(col > (g_UMSH8173MD_Config.ControllerConfig.Width  - Font_Width() )) return;

    const UINT8* font = Font_GetGlyph( c );

    UINT32 * ScreenBuffer = (UINT32 *)LCD_GetFrameBuffer();

#if 0
    for(int y = 0; y < Font_Height(); y++)
    {
        for(int x = 0; x < Font_Width(); x+=2)
        {
        	unsigned long long val = 0;
            // the font data is mirrored
            if(UMSH8173MD_GETBIT(Font_Width() -  x   ,y,font,1)) {
            	val |= 0xffffff;
            }
            if(UMSH8173MD_GETBIT(Font_Width() - (x+1),y,font,1)) {
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
            if(UMSH8173MD_GETBIT(Font_Width() - 1 - x  ,y,font,1))
                ScreenBuffer[(row+y)*g_UMSH8173MD_Config.ControllerConfig.Width + (col+x)] = 0xFFFFFFFF;
            else
                ScreenBuffer[(row+y)*g_UMSH8173MD_Config.ControllerConfig.Width + (col+x)] = 0x00000000;
        }
    }

}

#endif

void UMSH8173MD_Driver::WriteFormattedChar( unsigned char c )
{

     if ( g_UMSH8173MD_Driver.m_initialized == FALSE) return;

    if(c < 32)
    {
        switch(c)
        {
        case '\b':                      /* backspace, clear previous char and move cursor back */
            if((g_UMSH8173MD_Driver.m_cursor % TextColumns()) > 0)
            {
                g_UMSH8173MD_Driver.m_cursor--;
                LCD_WriteChar( ' ', g_UMSH8173MD_Driver.m_cursor / TextColumns(), g_UMSH8173MD_Driver.m_cursor % TextColumns() );
            }
            break;

        case '\f':                      /* formfeed, clear screen and home cursor */
            //LCD_Clear();
            g_UMSH8173MD_Driver.m_cursor = 0;
            break;

        case '\n':                      /* newline */
            g_UMSH8173MD_Driver.m_cursor += TextColumns();
            g_UMSH8173MD_Driver.m_cursor -= (g_UMSH8173MD_Driver.m_cursor % TextColumns());
            break;

        case '\r':                      /* carriage return */
            g_UMSH8173MD_Driver.m_cursor -= (g_UMSH8173MD_Driver.m_cursor % TextColumns());
            break;

        case '\t':                      /* horizontal tab */
            g_UMSH8173MD_Driver.m_cursor += (Font_TabWidth() - ((g_UMSH8173MD_Driver.m_cursor % TextColumns()) % Font_TabWidth()));
            // deal with line wrap scenario
            if((g_UMSH8173MD_Driver.m_cursor % TextColumns()) < Font_TabWidth())
            {
                // bring the cursor to start of line
                g_UMSH8173MD_Driver.m_cursor -= (g_UMSH8173MD_Driver.m_cursor % TextColumns());
            }
            break;

        case '\v':                      /* vertical tab */
            g_UMSH8173MD_Driver.m_cursor += TextColumns();
            break;

        default:
            debug_printf("Unrecognized control character in LCD_WriteChar");
            break;
        }
    }
    else
    {
        LCD_WriteChar( c, g_UMSH8173MD_Driver.m_cursor / TextColumns(), g_UMSH8173MD_Driver.m_cursor % TextColumns() );
        g_UMSH8173MD_Driver.m_cursor++;
    }

    if(g_UMSH8173MD_Driver.m_cursor >= (TextColumns() * TextRows()))
    {
        g_UMSH8173MD_Driver.m_cursor = 0;
    }
}

UINT32 UMSH8173MD_Driver::PixelsPerWord()
{
    return ((8*sizeof(UINT32)) / g_UMSH8173MD_Config.ControllerConfig.BitsPerPixel);
}

UINT32 UMSH8173MD_Driver::TextRows()
{
    return (g_UMSH8173MD_Config.ControllerConfig.Height / Font_Height());
}

UINT32 UMSH8173MD_Driver::TextColumns()
{
    return (g_UMSH8173MD_Config.ControllerConfig.Width / Font_Width());
}

UINT32 UMSH8173MD_Driver::WidthInWords()
{
    return ((g_UMSH8173MD_Config.ControllerConfig.Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}

UINT32 UMSH8173MD_Driver::SizeInWords()
{
    return (WidthInWords() * g_UMSH8173MD_Config.ControllerConfig.Height);
}

UINT32 UMSH8173MD_Driver::SizeInBytes()
{
    return (SizeInWords() * sizeof(UINT32));
}

void UMSH8173MD_Driver::Display_Init( UMSH8173MD_LCD_CONFIG& LcdConfig )
{
}
