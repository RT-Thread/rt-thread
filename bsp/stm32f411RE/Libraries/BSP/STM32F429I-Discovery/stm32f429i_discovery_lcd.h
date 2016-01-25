/**
  ******************************************************************************
  * @file    stm32f429i_discovery_lcd.h
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    02-March-2015
  * @brief   This file contains all the functions prototypes for the 
  *          stm32f429i_discovery_lcd.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_LCD_H
#define __STM32F429I_DISCOVERY_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f429i_discovery.h"
/* Include SDRAM Driver */
#include "stm32f429i_discovery_sdram.h"
#include "../../../Utilities/Fonts/fonts.h"
/* Include LCD component driver */
#include "../Components/ili9341/ili9341.h"   

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */ 
    
/** @defgroup STM32F429I_DISCOVERY_LCD
  * @{
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Types
  * @{
  */
typedef enum 
{
  LCD_OK = 0,
  LCD_ERROR = 1,
  LCD_TIMEOUT = 2
}LCD_StatusTypeDef;

typedef struct 
{ 
  uint32_t  TextColor; 
  uint32_t  BackColor;  
  sFONT     *pFont;
}LCD_DrawPropTypeDef;
   
typedef struct 
{
  int16_t X;
  int16_t Y;
} Point, * pPoint;	 
	 
/** 
  * @brief  Line mode structures definition  
  */ 
typedef enum
{
  CENTER_MODE             = 0x01,    /* center mode */
  RIGHT_MODE              = 0x02,    /* right mode  */     
  LEFT_MODE               = 0x03,    /* left mode   */                                                                               
}Text_AlignModeTypdef;
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Constants
  * @{
  */ 
#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef

/** 
  * @brief  LCD status structure definition  
  */     
#define MAX_LAYER_NUMBER       2
#define LCD_FRAME_BUFFER       ((uint32_t)0xD0000000)
#define BUFFER_OFFSET          ((uint32_t)0x50000) 

/** 
  * @brief  LCD color  
  */ 
#define LCD_COLOR_BLUE          0xFF0000FF
#define LCD_COLOR_GREEN         0xFF00FF00
#define LCD_COLOR_RED           0xFFFF0000
#define LCD_COLOR_CYAN          0xFF00FFFF
#define LCD_COLOR_MAGENTA       0xFFFF00FF
#define LCD_COLOR_YELLOW        0xFFFFFF00
#define LCD_COLOR_LIGHTBLUE     0xFF8080FF
#define LCD_COLOR_LIGHTGREEN    0xFF80FF80
#define LCD_COLOR_LIGHTRED      0xFFFF8080
#define LCD_COLOR_LIGHTCYAN     0xFF80FFFF
#define LCD_COLOR_LIGHTMAGENTA  0xFFFF80FF
#define LCD_COLOR_LIGHTYELLOW   0xFFFFFF80
#define LCD_COLOR_DARKBLUE      0xFF000080
#define LCD_COLOR_DARKGREEN     0xFF008000
#define LCD_COLOR_DARKRED       0xFF800000
#define LCD_COLOR_DARKCYAN      0xFF008080
#define LCD_COLOR_DARKMAGENTA   0xFF800080
#define LCD_COLOR_DARKYELLOW    0xFF808000
#define LCD_COLOR_WHITE         0xFFFFFFFF
#define LCD_COLOR_LIGHTGRAY     0xFFD3D3D3
#define LCD_COLOR_GRAY          0xFF808080
#define LCD_COLOR_DARKGRAY      0xFF404040
#define LCD_COLOR_BLACK         0xFF000000
#define LCD_COLOR_BROWN         0xFFA52A2A
#define LCD_COLOR_ORANGE        0xFFFFA500
#define LCD_COLOR_TRANSPARENT   0xFF000000
/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font24

/** 
  * @brief  LCD Layer  
  */ 
#define LCD_BACKGROUND_LAYER     0x0000
#define LCD_FOREGROUND_LAYER     0x0001

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Macros
  * @{
  */ 
/** 
  * @brief LCD Pixel format 
  */  
#define LCD_PIXEL_FORMAT_ARGB8888         LTDC_PIXEL_FORMAT_ARGB8888
#define LCD_PIXEL_FORMAT_RGB888           LTDC_PIXEL_FORMAT_RGB888        
#define LCD_PIXEL_FORMAT_RGB565           LTDC_PIXEL_FORMAT_RGB565                
#define LCD_PIXEL_FORMAT_ARGB1555         LTDC_PIXEL_FORMAT_ARGB1555        
#define LCD_PIXEL_FORMAT_ARGB4444         LTDC_PIXEL_FORMAT_ARGB4444        
#define LCD_PIXEL_FORMAT_L8               LTDC_PIXEL_FORMAT_L8        
#define LCD_PIXEL_FORMAT_AL44             LTDC_PIXEL_FORMAT_AL44        
#define LCD_PIXEL_FORMAT_AL88             LTDC_PIXEL_FORMAT_AL88
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Functions
  * @{
  */ 
uint8_t  BSP_LCD_Init(void);
uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);

/* functions using the LTDC controller */
void     BSP_LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FrameBuffer);
void     BSP_LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency);
void     BSP_LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address);
void     BSP_LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);
void     BSP_LCD_ResetColorKeying(uint32_t LayerIndex);
void     BSP_LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_SelectLayer(uint32_t LayerIndex);
void     BSP_LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState state);

void     BSP_LCD_SetTextColor(uint32_t Color);
void     BSP_LCD_SetBackColor(uint32_t Color);
uint32_t BSP_LCD_GetTextColor(void);
uint32_t BSP_LCD_GetBackColor(void);
void     BSP_LCD_SetFont(sFONT *pFonts);
sFONT    *BSP_LCD_GetFont(void);

uint32_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);
void     BSP_LCD_Clear(uint32_t Color);
void     BSP_LCD_ClearStringLine(uint32_t Line);
void     BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_LCD_DisplayStringAt(uint16_t X, uint16_t Y, uint8_t *pText, Text_AlignModeTypdef mode);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawLine(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void     BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     BSP_LCD_DrawBitmap(uint32_t X, uint32_t Y, uint8_t *pBmp);

void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_FillTriangle(uint16_t X1, uint16_t X2, uint16_t X3, uint16_t Y1, uint16_t Y2, uint16_t Y3);
void     BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

void     BSP_LCD_DisplayOff(void);
void     BSP_LCD_DisplayOn(void);

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
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
