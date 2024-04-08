/**********************************************************************
* $Id$      lpc_lcd.h           2011-10-14
*//**
* @file     lpc_lcd.h
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
#include "lpc_types.h"

#ifndef __LPC_LCD_H_
#define __LPC_LCD_H_

/** @defgroup LCD   LCD (Liquid Crystal Display)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

/** @defgroup LCD_Public_Macros LCD Public Macros
 * @{
 */

#define LCD_PWR_ENA_DIS_DLY  10000
#define LCD_FUNC_OK  0
#define LCD_FUNC_ERR -1

#define GET_CURSOR_IMG_SIZE(size)  ((size == 32) ? 64:256)

/**
 * @}
 */

/** @defgroup LCD_Public_Types LCD Public Types
 * @{
 */

typedef enum __LCD_TYPES
{
  LCD_STN_MONOCHROME,
  LCD_STN_COLOR,
  LCD_TFT,
  LCD_TYPE_UNKNOWN,
} LCD_TYPES;

typedef enum __LCD_BPP
{
  LCD_BPP_1 = 0x00,
  LCD_BPP_2 = 0x01,
  LCD_BPP_4 = 0x02,
  LCD_BPP_8 = 0x03,
  LCD_BPP_16 = 0x04,
  LCD_BPP_24 = 0x05,
  LCD_BPP_16_565Mode = 0x06,
  LCD_BPP_12_444Mode = 0x07,
} LCD_BPP;

typedef enum __LCD_PANEL
{
  LCD_PANEL_UPPER,
  LCD_PANEL_LOWER,
}LCD_PANEL;

/**
 * @brief A struct for Bitmap on LCD screen
 */
typedef struct _Bmp_t 
{
  uint32_t  H_Size;
  uint32_t  V_Size;
  uint32_t  BitsPP;
  uint32_t  BytesPP;
  uint8_t *pPalette;
  uint8_t *pPicStream;
  uint8_t *pPicDesc;
} Bmp_t, *pBmp_t;

/**
 * @brief A struct for Font Type on LCD screen
 */
 
typedef struct _FontType_t 
{
  uint32_t H_Size;
  uint32_t V_Size;
  uint32_t CharacterOffset;
  uint32_t CharactersNuber;
  uint8_t *pFontStream;
  uint8_t *pFontDesc;
} FontType_t, *pFontType_t;

/**
 * @brief A struct for LCD Palette
 */

typedef struct __LCD_PALETTE_Type
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
}LCD_PALETTE_Type, *pLCD_PALETTE_Type;

/**
 * @brief A struct for Horizontal configuration
 */

typedef struct __LCD_HConfig_Type
{
  uint8_t hfp;  // Horizontal front porch
  uint8_t hbp;  // Horizontal back porch
  uint8_t hsw;  // Horizontal synchronization pulse width
  uint16_t ppl;  // Number of pixels per line
}LCD_HConfig_Type;

/**
 * @brief A struct for Vertical configuration
 */

typedef struct __LCD_VConfig_Type
{
  uint8_t vfp;  // Vertical front and back porch
  uint8_t vbp;  // Vertical back porch
  uint8_t vsw;  // Vertical synchronization pulse width
  uint16_t lpp; // Number of lines per panel
}LCD_VConfig_Type;

/**
 * @brief A struct for Polarity configuration
 */

typedef struct __LCD_POLARITY_Type
{
    uint16_t cpl; // Number of pixel clocks per line 
    uint8_t  active_high; // Signal polarity, active HIGH or LOW
    uint8_t acb;  // AC bias pin frequency
    uint8_t  invert_panel_clock;   // Invert Panel clock;
    uint8_t  invert_hsync;          // Invert HSYNC
    uint8_t  invert_vsync;          // Invert VSYSNC
}LCD_POLARITY_Type;

/**
 * @brief A struct for LCD Configuration
 */

typedef struct __LCD_Config_Type
{
  LCD_HConfig_Type hConfig; // Horizontal config
  LCD_VConfig_Type vConfig; // Vertical config
  LCD_POLARITY_Type polarity; // Polarity config
  uint32_t panel_clk; // Panel clock frequency
  LCD_BPP lcd_bpp;   // Bits-per-pixel
  LCD_TYPES lcd_type; // Display type: STN monochrome, STN color, or TFT
  uint8_t   lcd_mono8; // STN 4 or 8-bit interface mode
  uint8_t   lcd_dual;  // STN dual or single panel mode
  uint8_t   big_endian_byte; // byte ordering in memory
  uint8_t   big_endian_pixel; // pixel ordering within a byte
  uint32_t  lcd_panel_upper;  // base address of frame buffer
  uint32_t  lcd_panel_lower;  // base address of frame buffer
  uint8_t*  lcd_palette;      // point to palette buffer
  Bool      lcd_bgr;          // False: RGB , TRUE: BGR
} LCD_Config_Type;

/**
 * @brief A struct for Cursor configuration
 */

typedef struct __LCD_Cursor_Config_Type
{
   uint8_t size32;              // 32x32 or 64x64
   uint8_t framesync;
   LCD_PALETTE_Type palette[2];
   uint32_t   baseaddress;
} LCD_Cursor_Config_Type;

typedef uint32_t LcdPixel_t, *pLcdPixel_t;
typedef int32_t  LCD_RET_CODE;

/**
 * @}
 */


/** @defgroup LCD_Public_Functions LCD Public Functions
 * @{
 */

LCD_RET_CODE LCD_Init (LCD_Config_Type* pConfig);
void LCD_SetBaseAddress(LCD_PANEL panel, uint32_t pAddress);
void LCD_SetPalette (const uint8_t* pPallete);
void LCD_Enable (Bool bEna);
void LCD_Cursor_Cfg(LCD_Cursor_Config_Type* pConfig);
void LCD_Cursor_Enable(int enable, int cursor);
void LCD_Move_Cursor(int x, int y);
void LCD_Cursor_SetImage (const uint32_t *pCursor, int cursor, int size);
void LCD_SetImage(LCD_PANEL panel,const uint8_t *pPain);
void LCD_FillRect (LCD_PANEL panel, uint32_t startx,uint32_t endx, 
                                        uint32_t starty, uint32_t endy,
                                        LcdPixel_t color);
void LCD_PutPixel (LCD_PANEL panel, uint32_t X_Left, uint32_t Y_Up, LcdPixel_t color);
void LCD_LoadPic (LCD_PANEL panel,uint32_t X_Left, uint32_t Y_Up, Bmp_t * pBmp, uint32_t Mask);

/**
 * @}
 */

#endif // __LPC_LCD_H_
/**
 * @}
 */

