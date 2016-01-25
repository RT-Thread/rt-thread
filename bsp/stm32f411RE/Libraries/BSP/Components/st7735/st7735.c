/**
  ******************************************************************************
  * @file    st7735.c
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    24-November-2014
  * @brief   This file includes the driver for ST7735 LCD mounted on the Adafruit
  *          1.8" TFT LCD shield (reference ID 802).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
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

/* Includes ------------------------------------------------------------------*/
#include "st7735.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup ST7735
  * @brief      This file provides a set of functions needed to drive the
  *             ST7735 LCD.
  * @{
  */

/** @defgroup ST7735_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ST7735_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ST7735_Private_Macros
  * @{
  */

/**
  * @}
  */  

/** @defgroup ST7735_Private_Variables
  * @{
  */ 


LCD_DrvTypeDef   st7735_drv = 
{
  st7735_Init,
  0,
  st7735_DisplayOn,
  st7735_DisplayOff,
  st7735_SetCursor,
  st7735_WritePixel,
  0,
  st7735_SetDisplayWindow,
  st7735_DrawHLine,
  st7735_DrawVLine,
  st7735_GetLcdPixelWidth,
  st7735_GetLcdPixelHeight,
  st7735_DrawBitmap,
};

static uint16_t ArrayRGB[320] = {0};

/**
* @}
*/ 

/** @defgroup ST7735_Private_FunctionPrototypes
  * @{
  */

/**
* @}
*/ 

/** @defgroup ST7735_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the ST7735 LCD Component.
  * @param  None
  * @retval None
  */
void st7735_Init(void)
{    
  uint8_t data = 0;
  
  /* Initialize ST7735 low level bus layer -----------------------------------*/
  LCD_IO_Init();
  /* Out of sleep mode, 0 args, no delay */
  st7735_WriteReg(LCD_REG_17, 0x00); 
  /* Frame rate ctrl - normal mode, 3 args:Rate = fosc/(1x2+40) * (LINE+2C+2D)*/
  LCD_IO_WriteReg(LCD_REG_177);
  data = 0x01;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x2C;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x2D;
  LCD_IO_WriteMultipleData(&data, 1);
  /* Frame rate control - idle mode, 3 args:Rate = fosc/(1x2+40) * (LINE+2C+2D) */    
  st7735_WriteReg(LCD_REG_178, 0x01);
  st7735_WriteReg(LCD_REG_178, 0x2C);
  st7735_WriteReg(LCD_REG_178, 0x2D);
  /* Frame rate ctrl - partial mode, 6 args: Dot inversion mode, Line inversion mode */ 
  st7735_WriteReg(LCD_REG_179, 0x01);
  st7735_WriteReg(LCD_REG_179, 0x2C);
  st7735_WriteReg(LCD_REG_179, 0x2D);
  st7735_WriteReg(LCD_REG_179, 0x01);
  st7735_WriteReg(LCD_REG_179, 0x2C);
  st7735_WriteReg(LCD_REG_179, 0x2D);
  /* Display inversion ctrl, 1 arg, no delay: No inversion */
  st7735_WriteReg(LCD_REG_180, 0x07);
  /* Power control, 3 args, no delay: -4.6V , AUTO mode */
  st7735_WriteReg(LCD_REG_192, 0xA2);
  st7735_WriteReg(LCD_REG_192, 0x02);
  st7735_WriteReg(LCD_REG_192, 0x84);
  /* Power control, 1 arg, no delay: VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD */
  st7735_WriteReg(LCD_REG_193, 0xC5);
  /* Power control, 2 args, no delay: Opamp current small, Boost frequency */ 
  st7735_WriteReg(LCD_REG_194, 0x0A);
  st7735_WriteReg(LCD_REG_194, 0x00);
  /* Power control, 2 args, no delay: BCLK/2, Opamp current small & Medium low */  
  st7735_WriteReg(LCD_REG_195, 0x8A);
  st7735_WriteReg(LCD_REG_195, 0x2A);
  /* Power control, 2 args, no delay */
  st7735_WriteReg(LCD_REG_196, 0x8A);
  st7735_WriteReg(LCD_REG_196, 0xEE);
  /* Power control, 1 arg, no delay */
  st7735_WriteReg(LCD_REG_197, 0x0E);
  /* Don't invert display, no args, no delay */
  LCD_IO_WriteReg(LCD_REG_32);
  /* Set color mode, 1 arg, no delay: 16-bit color */
  st7735_WriteReg(LCD_REG_58, 0x05);
  /* Column addr set, 4 args, no delay: XSTART = 0, XEND = 127 */
  LCD_IO_WriteReg(LCD_REG_42);
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x7F;
  LCD_IO_WriteMultipleData(&data, 1);
  /* Row addr set, 4 args, no delay: YSTART = 0, YEND = 159 */
  LCD_IO_WriteReg(LCD_REG_43);
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x9F;
  LCD_IO_WriteMultipleData(&data, 1);
  /* Magical unicorn dust, 16 args, no delay */
  st7735_WriteReg(LCD_REG_224, 0x02); 
  st7735_WriteReg(LCD_REG_224, 0x1c);  
  st7735_WriteReg(LCD_REG_224, 0x07); 
  st7735_WriteReg(LCD_REG_224, 0x12);
  st7735_WriteReg(LCD_REG_224, 0x37);  
  st7735_WriteReg(LCD_REG_224, 0x32);  
  st7735_WriteReg(LCD_REG_224, 0x29);  
  st7735_WriteReg(LCD_REG_224, 0x2d);
  st7735_WriteReg(LCD_REG_224, 0x29);  
  st7735_WriteReg(LCD_REG_224, 0x25);  
  st7735_WriteReg(LCD_REG_224, 0x2B);  
  st7735_WriteReg(LCD_REG_224, 0x39);  
  st7735_WriteReg(LCD_REG_224, 0x00);  
  st7735_WriteReg(LCD_REG_224, 0x01);  
  st7735_WriteReg(LCD_REG_224, 0x03);  
  st7735_WriteReg(LCD_REG_224, 0x10);
  /* Sparkles and rainbows, 16 args, no delay */
  st7735_WriteReg(LCD_REG_225, 0x03);
  st7735_WriteReg(LCD_REG_225, 0x1d);  
  st7735_WriteReg(LCD_REG_225, 0x07);  
  st7735_WriteReg(LCD_REG_225, 0x06);
  st7735_WriteReg(LCD_REG_225, 0x2E);  
  st7735_WriteReg(LCD_REG_225, 0x2C);  
  st7735_WriteReg(LCD_REG_225, 0x29);  
  st7735_WriteReg(LCD_REG_225, 0x2D);
  st7735_WriteReg(LCD_REG_225, 0x2E);  
  st7735_WriteReg(LCD_REG_225, 0x2E);  
  st7735_WriteReg(LCD_REG_225, 0x37);  
  st7735_WriteReg(LCD_REG_225, 0x3F);  
  st7735_WriteReg(LCD_REG_225, 0x00);  
  st7735_WriteReg(LCD_REG_225, 0x00);  
  st7735_WriteReg(LCD_REG_225, 0x02);  
  st7735_WriteReg(LCD_REG_225, 0x10);
  /* Normal display on, no args, no delay */
  st7735_WriteReg(LCD_REG_19, 0x00);
  /* Main screen turn on, no delay */
  st7735_WriteReg(LCD_REG_41, 0x00);
  /* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
  st7735_WriteReg(LCD_REG_54, 0xC0);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void st7735_DisplayOn(void)
{
  uint8_t data = 0;
  LCD_IO_WriteReg(LCD_REG_19);
  LCD_Delay(10);
  LCD_IO_WriteReg(LCD_REG_41);
  LCD_Delay(10);
  LCD_IO_WriteReg(LCD_REG_54);
  data = 0xC0;
  LCD_IO_WriteMultipleData(&data, 1);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void st7735_DisplayOff(void)
{
  uint8_t data = 0;
  LCD_IO_WriteReg(LCD_REG_19);
  LCD_Delay(10);
  LCD_IO_WriteReg(LCD_REG_40);
  LCD_Delay(10);
  LCD_IO_WriteReg(LCD_REG_54);
  data = 0xC0;
  LCD_IO_WriteMultipleData(&data, 1);
}

/**
  * @brief  Sets Cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void st7735_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
  uint8_t data = 0;
  LCD_IO_WriteReg(LCD_REG_42);
  data = (Xpos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteReg(LCD_REG_43); 
  data = (Ypos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteReg(LCD_REG_44);
}

/**
  * @brief  Writes pixel.   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  RGBCode: the RGB pixel color
  * @retval None
  */
void st7735_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
  uint8_t data = 0;
  if((Xpos >= ST7735_LCD_PIXEL_WIDTH) || (Ypos >= ST7735_LCD_PIXEL_HEIGHT)) 
  {
    return;
  }
  
  /* Set Cursor */
  st7735_SetCursor(Xpos, Ypos);
  
  data = RGBCode >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = RGBCode;
  LCD_IO_WriteMultipleData(&data, 1);
}  


/**
  * @brief  Writes to the selected LCD register.
  * @param  LCDReg: Address of the selected register.
  * @param  LCDRegValue: value to write to the selected register.
  * @retval None
  */
void st7735_WriteReg(uint8_t LCDReg, uint8_t LCDRegValue)
{
  LCD_IO_WriteReg(LCDReg);
  LCD_IO_WriteMultipleData(&LCDRegValue, 1);
}

/**
  * @brief  Sets a display window
  * @param  Xpos:   specifies the X bottom left position.
  * @param  Ypos:   specifies the Y bottom left position.
  * @param  Height: display window height.
  * @param  Width:  display window width.
  * @retval None
  */
void st7735_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  uint8_t data = 0;
  /* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
  LCD_IO_WriteReg(LCD_REG_42);
  data = (Xpos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  /* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
  LCD_IO_WriteReg(LCD_REG_43);
  data = (Ypos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
}

/**
  * @brief  Draws horizontal line.
  * @param  RGBCode: Specifies the RGB color   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Length: specifies the line length.  
  * @retval None
  */
void st7735_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint8_t counter = 0;
  
  if(Xpos + Length > ST7735_LCD_PIXEL_WIDTH) return;
  
  /* Set Cursor */
  st7735_SetCursor(Xpos, Ypos);
  
  for(counter = 0; counter < Length; counter++)
  {
    ArrayRGB[counter] = RGBCode;
  }
  LCD_IO_WriteMultipleData((uint8_t*)&ArrayRGB[0], Length * 2);
}

/**
  * @brief  Draws vertical line.
  * @param  RGBCode: Specifies the RGB color   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Length: specifies the line length.  
  * @retval None
  */
void st7735_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint8_t counter = 0;
  
  if(Ypos + Length > ST7735_LCD_PIXEL_HEIGHT) return;
  for(counter = 0; counter < Length; counter++)
  {
    st7735_WritePixel(Xpos, Ypos + counter, RGBCode);
  }   
}

/**
  * @brief  Gets the LCD pixel Width.
  * @param  None
  * @retval The Lcd Pixel Width
  */
uint16_t st7735_GetLcdPixelWidth(void)
{
  return ST7735_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Gets the LCD pixel Height.
  * @param  None
  * @retval The Lcd Pixel Height
  */
uint16_t st7735_GetLcdPixelHeight(void)
{                          
  return ST7735_LCD_PIXEL_HEIGHT;
}

/**
  * @brief  Displays a bitmap picture loaded in the internal Flash.
  * @param  BmpAddress: Bmp picture address in the internal Flash.
  * @retval None
  */
void st7735_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
  uint32_t index = 0, size = 0;
  
  /* Read bitmap size */
  size = *(volatile uint16_t *) (pbmp + 2);
  size |= (*(volatile uint16_t *) (pbmp + 4)) << 16;
  /* Get bitmap data address offset */
  index = *(volatile uint16_t *) (pbmp + 10);
  index |= (*(volatile uint16_t *) (pbmp + 12)) << 16;
  size = (size - index)/2;
  pbmp += index;
  
  /* Set GRAM write direction and BGR = 0 */
  /* Memory access control: MY = 0, MX = 1, MV = 0, ML = 0 */
  st7735_WriteReg(LCD_REG_54, 0x40);

  /* Set Cursor */
  st7735_SetCursor(Xpos, Ypos);  
 
  LCD_IO_WriteMultipleData((uint8_t*)pbmp, size*2);
 
  /* Set GRAM write direction and BGR = 0 */
  /* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
  st7735_WriteReg(LCD_REG_54, 0xC0);
}

/**
* @}
*/ 

/**
* @}
*/ 

/**
* @}
*/ 

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

