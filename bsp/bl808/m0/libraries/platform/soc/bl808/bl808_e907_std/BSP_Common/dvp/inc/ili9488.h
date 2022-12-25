/**
  ******************************************************************************
  * @file    ili9488.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __ILI9488_H__
#define __ILI9488_H__

#include "bflb_bsp_driver_glue.h"

/** @addtogroup  ILI9488_Driver
 *  @{
 */

/** @addtogroup  ILI9488
 *  @{
 */

/** @defgroup  ILI9488_Public_Types
 *  @{
 */

/*@} end of group ILI9488_Public_Types */

/** @defgroup  ILI9488_Public_Constants
 *  @{
 */

/*@} end of group ILI9488_Public_Constants */

/** @defgroup  ILI9488_Public_Macros
 *  @{
 */
#define LCD_W 320                     /* LCD width */
#define LCD_H 480                     /* LCD height */
/* 24-bit RGB color */
#define RGB(r,g,b)                    (b<<16|g<<8|r)
/* RGB565 to RGB888 */
#define RGB565_888(value)             ((value<<19&0xf80000)|(value<<5&0xfc00)|(value>>8&0xf8))
/* Calculate 32-bit or 16-bit absolute value */
#define ABS32(value)                  ((value^(value>>31))-(value>>31))
#define ABS16(value)                  ((value^(value>>15))-(value>>15))

/*@} end of group ILI9488_Public_Macros */

/** @defgroup  ILI9488_Public_Functions
 *  @{
 */

/**
 *  @brief Tft_lcd Functions
 */
void LCD_Init(void);
void LCD_DPI_Init(void);
void LCD_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_Clear(uint32_t color);
void LCD_DMA_Clear(uint32_t sourceAddr);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color);
void LCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color);
void LCD_DrawCircle(uint16_t x,uint16_t y,uint16_t r,uint32_t color);
void LCD_DrawArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color);
void LCD_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t* picture);
void LCD_DMA_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t* picture);
void LCD_DrawChinese(uint16_t x,uint16_t y,uint8_t* character,uint32_t bColor,uint32_t cColor);

/*@} end of group ILI9488_Public_Functions */

/*@} end of group ILI9488 */

/*@} end of group ILI9488_Driver */

#endif /* __ILI9488_H__ */
