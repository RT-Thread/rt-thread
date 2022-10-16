/**
  ******************************************************************************
  * @file    st7735.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the st7735.c
  *          driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ST7735_H
#define ST7735_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "st7735_reg.h"
#include <stddef.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @defgroup ST7735 ST7735
  * @{
  */

/** @defgroup ST7735_Exported_Types Exported Types
  * @{
  */
typedef int32_t (*ST7735_Init_Func)     (void);
typedef int32_t (*ST7735_DeInit_Func)   (void);
typedef int32_t (*ST7735_GetTick_Func)  (void);
typedef int32_t (*ST7735_Delay_Func)    (uint32_t);
typedef int32_t (*ST7735_WriteReg_Func) (uint8_t, uint8_t*, uint32_t);
typedef int32_t (*ST7735_ReadReg_Func)  (uint8_t, uint8_t*);
typedef int32_t (*ST7735_SendData_Func) (uint8_t*, uint32_t);
typedef int32_t (*ST7735_RecvData_Func) (uint8_t*, uint32_t);

typedef struct
{
  ST7735_Init_Func          Init;
  ST7735_DeInit_Func        DeInit;
  uint16_t                  Address;
  ST7735_WriteReg_Func      WriteReg;
  ST7735_ReadReg_Func       ReadReg;
  ST7735_SendData_Func      SendData;
  ST7735_RecvData_Func      RecvData;
  ST7735_GetTick_Func       GetTick;
} ST7735_IO_t;


typedef struct
{
  ST7735_IO_t         IO;
  st7735_ctx_t        Ctx;
  uint8_t             IsInitialized;
} ST7735_Object_t;

typedef struct
{
  /* Control functions */
  int32_t (*Init             )(ST7735_Object_t*, uint32_t, uint32_t);
  int32_t (*DeInit           )(ST7735_Object_t*);
  int32_t (*ReadID           )(ST7735_Object_t*, uint32_t*);
  int32_t (*DisplayOn        )(ST7735_Object_t*);
  int32_t (*DisplayOff       )(ST7735_Object_t*);
  int32_t (*SetBrightness    )(ST7735_Object_t*, uint32_t);
  int32_t (*GetBrightness    )(ST7735_Object_t*, uint32_t*);
  int32_t (*SetOrientation   )(ST7735_Object_t*, uint32_t);
  int32_t (*GetOrientation   )(ST7735_Object_t*, uint32_t*);

  /* Drawing functions*/
  int32_t ( *SetCursor       ) (ST7735_Object_t*, uint32_t, uint32_t);
  int32_t ( *DrawBitmap      ) (ST7735_Object_t*, uint32_t, uint32_t, uint8_t *);
  int32_t ( *FillRGBRect     ) (ST7735_Object_t*, uint32_t, uint32_t, uint8_t*, uint32_t, uint32_t);
  int32_t ( *DrawHLine       ) (ST7735_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *DrawVLine       ) (ST7735_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *FillRect        ) (ST7735_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetPixel        ) (ST7735_Object_t*, uint32_t, uint32_t, uint32_t*);
  int32_t ( *SetPixel        ) (ST7735_Object_t*, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetXSize        ) (ST7735_Object_t*, uint32_t *);
  int32_t ( *GetYSize        ) (ST7735_Object_t*, uint32_t *);

}ST7735_LCD_Drv_t;

/**
  * @}
  */

/** @defgroup ST7735_Exported_Constants Exported Constants
  * @{
  */

/**
  * @brief  ST7735 Size
  */
#define ST7735_OK                (0)
#define ST7735_ERROR             (-1)

/**
  * @brief  ST7735 ID
  */
#define  ST7735_ID              0x5CU

/**
  * @brief  ST7735 Size
  */
#define  ST7735_WIDTH           80U
#define  ST7735_HEIGHT          160U

/**
 *  @brief LCD_OrientationTypeDef
 *  Possible values of Display Orientation
 */
#define ST7735_ORIENTATION_PORTRAIT         0x00U /* Portrait orientation choice of LCD screen               */
#define ST7735_ORIENTATION_PORTRAIT_ROT180  0x01U /* Portrait rotated 180° orientation choice of LCD screen  */
#define ST7735_ORIENTATION_LANDSCAPE        0x02U /* Landscape orientation choice of LCD screen              */
#define ST7735_ORIENTATION_LANDSCAPE_ROT180 0x03U /* Landscape rotated 180° orientation choice of LCD screen */

/**
 *  @brief  Possible values of pixel data format (ie color coding)
 */
#define ST7735_FORMAT_RBG444                0x03U /* Pixel format chosen is RGB444 : 12 bpp */
#define ST7735_FORMAT_RBG565                0x05U /* Pixel format chosen is RGB565 : 16 bpp */
#define ST7735_FORMAT_RBG666                0x06U /* Pixel format chosen is RGB666 : 18 bpp */
#define ST7735_FORMAT_DEFAULT               ST7735_FORMAT_RBG565
/**
  * @}
  */

/** @defgroup ST7735_Exported_Functions Exported Functions
  * @{
  */
int32_t ST7735_RegisterBusIO (ST7735_Object_t *pObj, ST7735_IO_t *pIO);
int32_t ST7735_Init(ST7735_Object_t *pObj, uint32_t ColorCoding, uint32_t Orientation);
int32_t ST7735_DeInit(ST7735_Object_t *pObj);
int32_t ST7735_ReadID(ST7735_Object_t *pObj, uint32_t *Id);
int32_t ST7735_DisplayOn(ST7735_Object_t *pObj);
int32_t ST7735_DisplayOff(ST7735_Object_t *pObj);
int32_t ST7735_SetBrightness(ST7735_Object_t *pObj, uint32_t Brightness);
int32_t ST7735_GetBrightness(ST7735_Object_t *pObj, uint32_t *Brightness);
int32_t ST7735_SetOrientation(ST7735_Object_t *pObj, uint32_t Orientation);
int32_t ST7735_GetOrientation(ST7735_Object_t *pObj, uint32_t *Orientation);

int32_t ST7735_SetCursor(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos);
int32_t ST7735_DrawBitmap(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pBmp);
int32_t ST7735_FillRGBRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height);
int32_t ST7735_DrawHLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color);
int32_t ST7735_DrawVLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color);
int32_t ST7735_FillRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color);
int32_t ST7735_SetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Color);
int32_t ST7735_GetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t *Color);
int32_t ST7735_GetXSize(ST7735_Object_t *pObj, uint32_t *XSize);
int32_t ST7735_GetYSize(ST7735_Object_t *pObj, uint32_t *YSize);

extern ST7735_LCD_Drv_t   ST7735_LCD_Driver;

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* ST7735_H */

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
