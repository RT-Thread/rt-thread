/**********************************************************************
* $Id$      lpc_lcd.c           2011-10-14
*//**
* @file     lpc_lcd.c
* @brief    Contains all functions support for LCD firmware library
*           on LPC
* @version  1.0
* @date     14. October. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _LCD

#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"
#include "lpc_gpio.h"
#include "lpc_lcd.h"

uint32_t lcd_hsize = 0, lcd_vsize = 0;
uint32_t lcd_cursor_base_addr = 0;
uint32_t lcd_cursor_size = 64;
LCD_Config_Type  lcd_config;
static uint8_t bits_per_pixel[] = {  1, 2, 4, 8, 16, 32, 16, 16  };
uint32_t rect[1024];


static void LCD_SetHorizontalTiming(LCD_HConfig_Type* pConfig);
static void LCD_SetVertialTiming(LCD_VConfig_Type* pConfig);
static void LCD_SetPolarity(LCD_TYPES lcd_type, LCD_POLARITY_Type* pConfig);
static void LCD_CtrlSetup(LCD_Config_Type* pConfig);

/** @addtogroup LCD_Private_Functions LCD Private Function
 * @ingroup LCD
 * @{
 */


/*********************************************************************//**
 * @brief     Init LCD. The input clock is CClk
 *
 * @param[in] pConfig              Configuration Information
 *
 * @return    LCD_FUNC_OK   Execute successfully
 *            LCD_FUNC_ERR  Error occurred.
 *
 **********************************************************************/
LCD_RET_CODE LCD_Init (LCD_Config_Type* pConfig)
{
    uint8_t clkdiv;

    if(pConfig == NULL)
        return LCD_FUNC_ERR;

    if(pConfig->big_endian_byte & !pConfig->big_endian_pixel)
      return LCD_FUNC_ERR;
    
    lcd_config = *pConfig;
    
    // Assign pins
    PINSEL_ConfigPin(0,4,7);
    PINSEL_ConfigPin(0,5,7);
    PINSEL_ConfigPin(0,6,7);
    PINSEL_ConfigPin(0,7,7);
    PINSEL_ConfigPin(0,8,7);
    PINSEL_ConfigPin(0,9,7);
    PINSEL_ConfigPin(1,20,7);
    PINSEL_ConfigPin(1,21,7);
    PINSEL_ConfigPin(1,22,7);
    PINSEL_ConfigPin(1,23,7);
    PINSEL_ConfigPin(1,24,7);
    PINSEL_ConfigPin(1,25,7);
    PINSEL_ConfigPin(1,26,7);
    PINSEL_ConfigPin(1,27,7);
    PINSEL_ConfigPin(1,28,7);
    PINSEL_ConfigPin(1,29,7);
    PINSEL_ConfigPin(2,0,7);
    PINSEL_ConfigPin(2,1,7);
    PINSEL_ConfigPin(2,2,7);
    PINSEL_ConfigPin(2,3,7);
    PINSEL_ConfigPin(2,4,7);
    PINSEL_ConfigPin(2,5,7);
    PINSEL_ConfigPin(2,6,7);
#ifdef CORE_M4
    PINSEL_ConfigPin(0,10,7);
#else
    PINSEL_ConfigPin(2,7,7);
#endif    
    PINSEL_ConfigPin(2,8,7);
    PINSEL_ConfigPin(2,9,7);
    PINSEL_ConfigPin(2,11,7);
    PINSEL_ConfigPin(2,12,7);
    PINSEL_ConfigPin(2,13,7);
    PINSEL_ConfigPin(4,28,7);
    PINSEL_ConfigPin(4,29,7);
    
    //Turn on LCD clock
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCLCD, ENABLE);

    // Set clock    
    LPC_LCD->POL &= ~(0x01 << 5);
    if( pConfig->panel_clk > 0) {
        clkdiv = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU) / pConfig->panel_clk - 1;
        LPC_SC->LCD_CFG = clkdiv & 0x1F;
        LPC_LCD->POL |=(1<<26);
    }

    // init Horizontal Timing
    LCD_SetHorizontalTiming(&pConfig->hConfig);

    // Init Vertical Timing
    LCD_SetVertialTiming(&pConfig->vConfig);

    // Set Polarity
    LCD_SetPolarity(pConfig->lcd_type, &pConfig->polarity);

    if(NULL != pConfig->lcd_palette)
    {
        LCD_SetPalette(pConfig->lcd_palette);
    }

    // Set Base address
    LCD_SetBaseAddress(LCD_PANEL_UPPER, pConfig->lcd_panel_upper);
    LCD_SetBaseAddress(LCD_PANEL_LOWER, pConfig->lcd_panel_lower);

        // Setup
    LCD_CtrlSetup(pConfig);
    
    return LCD_FUNC_OK;

    
}
/*********************************************************************//**
 * @brief     Horizontal Timing Setting
 *
 * @param[in] pConfig              Configuration Information
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetHorizontalTiming(LCD_HConfig_Type* pConfig)
{
    LPC_LCD->TIMH = 0; //reset TIMH before set value
    LPC_LCD->TIMH |= ((pConfig->hbp - 1)& 0xFF)<<24;
    LPC_LCD->TIMH |= ((pConfig->hfp - 1)& 0xFF)<<16;
    LPC_LCD->TIMH |= ((pConfig->hsw - 1)& 0xFF)<<8;
    LPC_LCD->TIMH |= ((pConfig->ppl/16 - 1)& 0x3F)<<2;
    lcd_hsize =  pConfig->ppl;
}

/*********************************************************************//**
 * @brief     Vertical Timing Setting
 *
 * @param[in] pConfig              Configuration Information
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetVertialTiming(LCD_VConfig_Type* pConfig)
{
    LPC_LCD->TIMV = 0;  //reset TIMV value before setting
    LPC_LCD->TIMV |= ((pConfig->vbp)& 0xFF)<<24;
    LPC_LCD->TIMV |= ((pConfig->vfp)& 0xFF)<<16;
    LPC_LCD->TIMV |= ((pConfig->vsw - 1)& 0x3F)<<10;
    LPC_LCD->TIMV |= ((pConfig->lpp - 1)& 0x03FF)<<0;
    lcd_vsize =   pConfig->lpp;
}

/*********************************************************************//**
 * @brief     Polarity Setting
 *
 * @param[in] pConfig              Configuration Information
 * @param[in] lcd_type            It can be:
 *                                                - LCD_STN_MONOCHROME
 *                                                - LCD_STN_COLOR
 *                                                - LCD_TFT
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetPolarity(LCD_TYPES lcd_type, LCD_POLARITY_Type* pConfig)
{
    // LCDFP pin is active LOW and inactive HIGH
    if(pConfig->invert_vsync)
        LPC_LCD->POL |= (1<<11);
    else
        LPC_LCD->POL &= ~(1<<11);        
    // LCDLP pin is active LOW and inactive HIGH
    if(pConfig->invert_hsync)
        LPC_LCD->POL |= (1<<12);
    else
        LPC_LCD->POL &= ~(1<<12);
    // data is driven out into the LCD on the falling edge
    if(pConfig->invert_panel_clock)
        LPC_LCD->POL |= (1<<13);
    else
        LPC_LCD->POL &= ~(1<<13);
    
    // active high
    if(pConfig->active_high) {
      LPC_LCD->POL &= ~(1<<14);
    }
    else
    {
      LPC_LCD->POL |= (1<<14);
    }

    LPC_LCD->POL &= ~(0x3FF <<16);
    LPC_LCD->POL |= (pConfig->cpl - 1)<<16;

    if(lcd_type == LCD_STN_COLOR || lcd_type == LCD_STN_MONOCHROME)
    LPC_LCD->POL |= (pConfig->acb & 0x1F) << 6;
    }

/*********************************************************************//**
 * @brief     Set base address of frame buffer
 *
 * @param[in] panel           identify which panel is.
 * @param[in] pAddress          base address of the inputted panel.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetBaseAddress(LCD_PANEL panel, uint32_t pAddress)
{
    // Frame Base Address doubleword aligned
    if(panel == LCD_PANEL_UPPER)
        LPC_LCD->UPBASE = pAddress & ~7UL ;
    else
        LPC_LCD->LPBASE = pAddress & ~7UL ;
}

/*********************************************************************//**
 * @brief     LCD Setup.
 *
 * @param[in] pConfig             Configuration information.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_CtrlSetup(LCD_Config_Type* pConfig)
{
    // disable LCD controller   
    LPC_LCD->CTRL = 0;
    
    //  bpp
    LPC_LCD->CTRL &= ~(0x07 <<1);
    LPC_LCD->CTRL |=((pConfig->lcd_bpp & 0x07)<<1);

    if(pConfig->lcd_type == LCD_TFT) {
        LPC_LCD->CTRL |=  (0x01 << 5);  // TFT
    }
    else {
        // Color/Mono
        if(pConfig->lcd_type == LCD_STN_COLOR) {
            LPC_LCD->CTRL &= ~ (0x01 << 4);  // Color
        }
        else if (pConfig->lcd_type == LCD_STN_MONOCHROME) {
            LPC_LCD->CTRL |=  (0x01 << 4);   // Mono
         }

        // STN/TFT
        LPC_LCD->CTRL &= ~ (0x01 << 5);  // STN

        // Mono4/8
        if(pConfig->lcd_mono8)
            LPC_LCD->CTRL |= (0x01 << 6);
        else
            LPC_LCD->CTRL &= ~(0x01 << 6);

        // Single/dual
        if(pConfig->lcd_dual)
            LPC_LCD->CTRL |= (0x01 << 7);
        else
            LPC_LCD->CTRL &= ~(0x01 << 7);
    }
    
    // notmal output
    if(pConfig->lcd_bgr)
        LPC_LCD->CTRL |= (1<<8);    // BGR
    else
        LPC_LCD->CTRL &= ~(1<<8);   // RGB

        // Byte order
    if(pConfig->big_endian_byte)
      LPC_LCD->CTRL |= (1<<9);
    else
      LPC_LCD->CTRL &= ~(1<<9);

    // Pixel order
    if(pConfig->big_endian_pixel)
      LPC_LCD->CTRL |= (1<<10);
    else
      LPC_LCD->CTRL &= ~(1<<10);
    
    // disable power
    LPC_LCD->CTRL &= ~(1<<11);
}

/*********************************************************************//**
 * @brief     Enable/disable LCD Display.
 *
 * @param[in] bEna           0: disable, 1: enable.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_Enable (Bool bEna)
{
  volatile uint32_t i;
  if (bEna)
  {
    LPC_LCD->CTRL |= (1<<0);
    for(i = LCD_PWR_ENA_DIS_DLY; i; i--);
    LPC_LCD->CTRL |= (1<<11);
  }
  else
  {
    LPC_LCD->CTRL &= ~(1<<11);
    for(i = LCD_PWR_ENA_DIS_DLY; i; i--);
    LPC_LCD->CTRL &= ~(1<<0);
  }
}


/*********************************************************************//**
 * @brief     Set palette.
 *
 * @param[in] bEna           0: disable, 1: enable.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetPalette (const uint8_t* pPallete)
{
    uint32_t i;
    uint32_t size = (0x01 << bits_per_pixel[lcd_config.lcd_bpp])/2 ;
    uint32_t * pDst = (uint32_t *)LPC_LCD->PAL;
    uint32_t * pInput = (uint32_t*) pPallete;

    for (i = 0; i < size; i++)
    {
      *pDst = *pInput;
      pDst++;
      pInput++;
    }
}
/*********************************************************************//**
 * @brief     Get word offset for the given pixel
 *
 * @param[in] x      x position of input pixel
 * @param[in] y      y position of input pixel
 *
 * @return    Offset
 *
 **********************************************************************/
uint32_t LCD_GetWordOffset(uint32_t x, uint32_t y)
{
  uint32_t pixel_num = x + y*lcd_hsize;

  return (pixel_num * bits_per_pixel[lcd_config.lcd_bpp])/32;
}
/*********************************************************************//**
 * @brief     Get bit offset for the given pixel
 *
 * @param[in] x      x position of input pixel
 * @param[in] y      y position of input pixel
 *
 * @return    Offset
 *
 **********************************************************************/
uint32_t LCD_GetBitOffset(uint32_t x, uint32_t y)
{
  uint32_t pixel_num;
  uint32_t ofs;
  pixel_num = x + y*lcd_hsize;
  
  ofs = (pixel_num * bits_per_pixel[lcd_config.lcd_bpp])%32;
  
  if(lcd_config.big_endian_pixel & lcd_config.big_endian_byte)
  {
     ofs = 32 - bits_per_pixel[lcd_config.lcd_bpp] - ofs;
  }
  else if (lcd_config.big_endian_pixel & !lcd_config.big_endian_byte)
  {
     if(bits_per_pixel[lcd_config.lcd_bpp] < 8)
     {
        ofs = (ofs/8)*8 + (8 - (ofs%8)-bits_per_pixel[lcd_config.lcd_bpp]);
     }
  }
  return ofs;
}



/*********************************************************************//**
 * @brief     Copy pixel values from image buffer to frame buffer.
 *
 * @param[in] panel          It can be:
 *                                             - LCD_PANEL_UPPER
 *                                             - LCD_PANEL_LOWER
 * @param[in] pPain         point to image buffer.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_SetImage(LCD_PANEL panel, const uint8_t *pPain)
{
    volatile uint32_t i;
    uint32_t * pWordDst = NULL;
    uint8_t* pByteDst = NULL;
    uint32_t bytes_num;

    if(panel == LCD_PANEL_UPPER)
        pWordDst = (uint32_t*) LPC_LCD->UPBASE;
    else
        pWordDst = (uint32_t*) LPC_LCD->LPBASE;

    pByteDst = (uint8_t*) pWordDst;
    bytes_num =  ((lcd_hsize * lcd_vsize) * bits_per_pixel[lcd_config.lcd_bpp]) /8;

    if (NULL == pPain)
    {
        // clear display memory
        for( i = 0; bytes_num > i; i++)
        {
             *pByteDst++ = 0;
        }
    }
    else
    {
        // set display memory
        for(i = 0; bytes_num > i; i++)
        {
            *pByteDst++ = *pPain++;
        }
    }

    for(i = LCD_PWR_ENA_DIS_DLY; i; i--);
}
/*********************************************************************//**
 * @brief     Draw a pixel on the given panel.
 *
 * @param[in] panel          It can be:
 *                                             - LCD_PANEL_UPPER
 *                                             - LCD_PANEL_LOWER
 * @param[in] X_Left        X position.
 * @param[in] Y_Up          Y position.
 * @param[in] color         Color which is placed to the given pixel.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_PutPixel (LCD_PANEL panel, uint32_t X_Left, uint32_t Y_Up, LcdPixel_t color)
{
    uint32_t k;
    uint32_t * pWordData = NULL;
    uint8_t*   pByteData = NULL;
    uint32_t  bitOffset;
    uint8_t*   pByteSrc = (uint8_t*)&color;
    uint8_t  bpp = bits_per_pixel[lcd_config.lcd_bpp];
    uint8_t  bytes_per_pixel = bpp/8;
    uint32_t start_bit;
  
    if((X_Left >= lcd_hsize)||(Y_Up >= lcd_vsize))
        return;

    if(panel == LCD_PANEL_UPPER)
    pWordData = (uint32_t*) LPC_LCD->UPBASE + LCD_GetWordOffset(X_Left,Y_Up);
    else
    pWordData = (uint32_t*) LPC_LCD->LPBASE + LCD_GetWordOffset(X_Left,Y_Up);
    
    bitOffset = LCD_GetBitOffset(X_Left,Y_Up);
    pByteData = (uint8_t*) pWordData;
    pByteData += bitOffset/8;
    
    start_bit =  bitOffset%8;

    if(bpp < 8)
    {
      uint8_t bit_pos = start_bit;
      uint8_t bit_ofs = 0;
      for(bit_ofs = 0;bit_ofs <bpp; bit_ofs++,bit_pos++)
      {
          *pByteData &= ~ (0x01 << bit_pos);
          *pByteData |= ((*pByteSrc >> (k+bit_ofs)) & 0x01) << bit_pos; 
      }
    }
    else
    {
         for(k = 0; k < bytes_per_pixel; k++)
        {
           *(pByteData+ k) = *pByteSrc++;
        }
    }
}
/*********************************************************************//**
 * @brief     Place given image to given position.
 *
 * @param[in] panel          It can be:
 *                                             - LCD_PANEL_UPPER
 *                                             - LCD_PANEL_LOWER
 * @param[in] X_Left        Start X position.
 * @param[in] Y_Up          Start Y position.
 * @param[in] pBmp          Image information. 
 * @param[in] Mask          Mask on pixel values.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_LoadPic (LCD_PANEL panel, uint32_t X_Left, uint32_t Y_Up, 
                        Bmp_t * pBmp, uint32_t Mask)
{
  uint32_t i, j, k, inc;
  uint32_t * pWordData = NULL;
  uint8_t*   pByteData = NULL;
  uint32_t  bitOffset;
  uint8_t*   pByteSrc = (uint8_t*) pBmp->pPicStream;
  uint32_t X_LeftHold = X_Left;
  uint8_t  bpp = bits_per_pixel[lcd_config.lcd_bpp];
  uint8_t  bytes_per_pixel = bpp/8;
  uint8_t  pixels_per_byte = 8/bpp;
  uint32_t hsize, vsize;
  uint32_t start_bit;

  if(pBmp->BytesPP == 0)
    pBmp->BytesPP = bytes_per_pixel;
         
  hsize = pBmp->H_Size;
  vsize = pBmp->V_Size;
  inc = (pixels_per_byte > 0) ? pixels_per_byte:1;
   
  for(i = 0; i < vsize; i++)
  {
    if(panel == LCD_PANEL_UPPER)
    pWordData = (uint32_t*) LPC_LCD->UPBASE + LCD_GetWordOffset(X_Left,Y_Up);
    else
    pWordData = (uint32_t*) LPC_LCD->LPBASE + LCD_GetWordOffset(X_Left,Y_Up);

    bitOffset = LCD_GetBitOffset(X_Left,Y_Up);
    pByteData = (uint8_t*) pWordData;
    pByteData += bitOffset/8;
    
    start_bit =  bitOffset%8;
  
    if(pBmp->BytesPP > 0)
    pByteSrc = (uint8_t*) pBmp->pPicStream + i*hsize*pBmp->BytesPP; // storage of each line must be word alignment
    else
    pByteSrc = (uint8_t*) pBmp->pPicStream + (i*hsize*pBmp->BitsPP + 7)/8; // storage of each line must be word alignment
    
    X_LeftHold = X_Left;

    for(j = 0; j <= hsize; j+= inc)
    {
         if((X_LeftHold  >= lcd_hsize) || (X_LeftHold - X_Left  >= hsize))
            break;
         if(bpp < 8)
         {
          uint8_t bit_pos = start_bit;
          uint8_t bit_ofs = 0;
          for(k = 0; k < 8; k+= bpp)
          {
              for(bit_ofs = 0;bit_ofs <bpp; bit_ofs++,bit_pos++)
              {
                 *pByteData &= ~ (0x01 << bit_pos);
                 *pByteData |= ((*pByteSrc >> (k+bit_ofs)) & 0x01) << bit_pos; 
              }
              if(lcd_config.big_endian_byte && lcd_config.big_endian_pixel)
              {
                if(bit_pos >= bpp*2)
                    bit_pos -= bpp*2;
                else
                {
                   bit_pos = 8-bpp;
                   if((((uint32_t)pByteData)%4) == 0)
                     pByteData += 7; // change to next word
                   else
                     pByteData--;  // change to previous byte
                }   
             }
             else if( !lcd_config.big_endian_byte && lcd_config.big_endian_pixel)
              {
                if(bit_pos >= bpp*2)
                    bit_pos -= bpp*2;
                else
                {
                   bit_pos = 8-bpp;
                   pByteData++;  // change to next byte
                }
               }
               else
               {
                 if(bit_pos >= 8)
                 {
                    bit_pos = 0;
                    pByteData++; // change to next byte
                 }
                   
               }
               X_LeftHold++;
               if((X_LeftHold  >= lcd_hsize) || 
                   (X_LeftHold - X_Left  >= hsize))
                    break;
          } 
          pByteSrc++;
          continue;
        }
        else
        {
            for(k = 0; k < pBmp->BytesPP; k++)
            {
               *(pByteData+ k) = *pByteSrc++ ^ Mask;
            }
            if(lcd_config.big_endian_byte)
            {
              if((uint32_t)pByteData %4 > 0)
                pByteData -= bytes_per_pixel;
              else
                pByteData += 8 - bytes_per_pixel;
            }
            else
              pByteData+= bytes_per_pixel;
            X_LeftHold++;
        }
    }
    if(Y_Up++ >= lcd_vsize)
    {
    break;
    }
  }
}

/*********************************************************************//**
 * @brief     Fill a rectangle.
 *
 * @param[in] panel          It can be:
 *                                             - LCD_PANEL_UPPER
 *                                             - LCD_PANEL_LOWER
 * @param[in] startx            Start X position.
 * @param[in] endy             End X position.
 * @param[in] starty            Start Y position.
 * @param[in] endy           End Y position.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_FillRect (LCD_PANEL panel, uint32_t startx,uint32_t endx, 
                                        uint32_t starty, uint32_t endy,
                                        LcdPixel_t color)
{
   uint32_t x, xs, xe, ys, ye;
   uint8_t  bpp,  pixels_per_word;
   uint32_t word_val, mask;
   uint32_t max_vsize = 0;
   Bmp_t  bitmap;
   uint32_t hsize, vsize;

   bpp = bits_per_pixel[lcd_config.lcd_bpp];
   pixels_per_word = 32/bpp;

   mask = 0;
   for( x = 0; x < bpp; x++)
     mask |= 0x01 << x;
   
   color &= mask;

   word_val = 0;
   for(x = 0; x < pixels_per_word; x++)
      word_val |= color << (x*bpp);
      
   ys = (starty > endy) ? endy : starty;
   ye = (starty > endy) ? starty : endy;

   xs = (startx > endx) ? endx : startx;
   xe = (startx > endx) ? startx : endx;

   bitmap.BitsPP = bpp;
   bitmap.BytesPP = bpp/8;
   hsize = xe - xs + 1;
   bitmap.H_Size = hsize;
   vsize = ye - ys + 1;
   bitmap.pPicStream = (uint8_t*)rect;

   max_vsize = ((1024 * 32)/(hsize*bpp));

   for( x = 0; x < 1024; x++)
   {
     rect[x] = word_val;
   }
   
   while(1)
    {
      if(max_vsize >= vsize)
      {
         bitmap.V_Size = vsize;
         LCD_LoadPic(panel,xs,ys, &bitmap, 0);
         break;
      }
      else {
        bitmap.V_Size = max_vsize;
        vsize -= bitmap.V_Size;
        LCD_LoadPic(panel,xs,ys, &bitmap, 0);
        ys += max_vsize;
      }
    } 

   
}

/*********************************************************************//**
 * @brief     Configure display of cursor.
 *
 * @param[in] pConfig            Configuration information.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_Cursor_Cfg(LCD_Cursor_Config_Type* pConfig)
{
  if(pConfig->size32) {
    LPC_LCD->CRSR_CFG &= ~(0x01 << 0);
    lcd_cursor_size = 32;
  }
  else {
    LPC_LCD->CRSR_CFG |= (0x01 << 0);
    lcd_cursor_size = 64;
  }

  if(pConfig->framesync)
    LPC_LCD->CRSR_CFG &= ~(0x01 << 1);
  else
    LPC_LCD->CRSR_CFG |= (0x01 << 1);

  lcd_cursor_base_addr = pConfig->baseaddress;
  
  LPC_LCD->CRSR_PAL0 = pConfig->palette[0].Red |
                       pConfig->palette[0].Green << 8 |
                       pConfig->palette[0].Blue << 16;
  LPC_LCD->CRSR_PAL1 = pConfig->palette[1].Red |
                       pConfig->palette[1].Green << 8 |
                       pConfig->palette[1].Blue << 16;

}
/*********************************************************************//**
 * @brief     Enable/disable cursor display.
 *
 * @param[in] enable             0: disable, 1: enable.
 * @param[in] cursor             identify which cursor image is used.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_Cursor_Enable(int enable, int cursor)
{
  if(enable) {
    LPC_LCD->CRSR_CTRL |= (1<<0);
    LPC_LCD->CRSR_CTRL |= (cursor<<4);
  }
  else {
    LPC_LCD->CRSR_CTRL &= ~(1<<0);
  }
}


/*********************************************************************//**
 * @brief     move the cursor to the inputted position.
 *
 * @param[in] x          Position in x-direction.
 * @param[in] y          Position in y-direction.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_Move_Cursor(int x, int y)
{
  LPC_LCD->CRSR_CLIP = 0;
  LPC_LCD->CRSR_XY = 0;
  if(0 <= x)
  {//no clipping
    LPC_LCD->CRSR_XY |= (x & 0x3FF);
  }
  else
  {//clip x
    LPC_LCD->CRSR_CLIP |= -x;
  }

  if(0 <= y)
  {//no clipping

    LPC_LCD->CRSR_XY |= (y << 16);
  }
  else
  {//clip y
    LPC_LCD->CRSR_CLIP |= (-y << 8);
  }
}

/*********************************************************************//**
 * @brief     Set the cursor image.
 *
 * @param[in] pCursor      point to cursor image.
 * @param[in] cursor       cursor image number. It has no meaning when cursor size is 64x64
 * @param[in] cursor       cursor size in words.
 *
 * @return    None.
 *
 **********************************************************************/
void LCD_Cursor_SetImage (const uint32_t *pCursor, int cursor, int size)
{
    uint32_t i ;
    uint32_t * pDst = (uint32_t *)lcd_cursor_base_addr;

    if(lcd_cursor_size == 32) 
        pDst += cursor*GET_CURSOR_IMG_SIZE(lcd_cursor_size);
        

    for(i = 0; i < size ; i++) 
    {
    *pDst = *pCursor;
    pDst++;
    pCursor++;
    }
}

/**
 * @}
 */
 
#endif /*_LCD*/



