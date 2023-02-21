/**
  ******************************************************************************
  * @file    st7735.c
  * @author  MCD Application Team
  * @brief   This file includes the driver for ST7735 LCD mounted on the Adafruit
  *          1.8" TFT LCD shield (reference ID 802).
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

/* Includes ------------------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "st7735.h"

#define DRV_DEBUG
#define LOG_TAG             "st7735"
#include <drv_log.h>

#define IS_BOE_PANEL    (0)

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

/** @defgroup ST7735_Private_Types Private Types
  * @{
  */
typedef struct
{
  uint32_t        Width;
  uint32_t        Height;
  uint32_t        Orientation;
} ST7735_Ctx_t;
/**
  * @}
  */

/** @defgroup ST7735_Private_Variables Private Variables
  * @{
  */
ST7735_LCD_Drv_t   ST7735_LCD_Driver =
{
  ST7735_Init,
  ST7735_DeInit,
  ST7735_ReadID,
  ST7735_DisplayOn,
  ST7735_DisplayOff,
  ST7735_SetBrightness,
  ST7735_GetBrightness,
  ST7735_SetOrientation,
  ST7735_GetOrientation,
  ST7735_SetCursor,
  ST7735_DrawBitmap,
  ST7735_FillRGBRect,
  ST7735_DrawHLine,
  ST7735_DrawVLine,
  ST7735_FillRect,
  ST7735_GetPixel,
  ST7735_SetPixel,
  ST7735_GetXSize,
  ST7735_GetYSize,
};

/* The below table handle the different values to be set to Memory Data Access Control
   depending on the orientation and pbm image writing where the data order is inverted
*/
static uint32_t OrientationTab[4][2] =
{
  {0x48U , 0xC8U}, /* Portrait orientation choice of LCD screen               */
  {0x88U , 0x08U}, /* Portrait rotated 180° orientation choice of LCD screen  */
  {0x28U , 0x68U}, /* Landscape orientation choice of LCD screen              */
  {0xE8U , 0xA8U}  /* Landscape rotated 180° orientation choice of LCD screen */
};

static ST7735_Ctx_t ST7735Ctx;
/**
  * @}
  */

/** @defgroup ST7735_Private_FunctionsPrototypes Private Functions Prototypes
  * @{
  */
static int32_t ST7735_SetDisplayWindow(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);
static int32_t ST7735_ReadRegWrap(void *Handle, uint8_t Reg, uint8_t* pData);
static int32_t ST7735_WriteRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint32_t Length);
static int32_t ST7735_SendDataWrap(void *Handle, uint8_t *pData, uint32_t Length);
static int32_t ST7735_RecvDataWrap(void *Handle, uint8_t *pData, uint32_t Length);
static int32_t ST7735_IO_Delay(ST7735_Object_t *pObj, uint32_t Delay);
/**
* @}
*/

/** @addtogroup ST7735_Exported_Functions
  * @{
  */
/**
  * @brief  Register component IO bus
  * @param  pObj Component object pointer
  * @param  pIO  Component IO structure pointer
  * @retval Component status
  */
int32_t ST7735_RegisterBusIO (ST7735_Object_t *pObj, ST7735_IO_t *pIO)
{
  int32_t ret;

  if(pObj == NULL)
  {
    ret = ST7735_ERROR;
  }
  else
  {
    pObj->IO.Init      = pIO->Init;
    pObj->IO.DeInit    = pIO->DeInit;
    pObj->IO.Address   = pIO->Address;
    pObj->IO.WriteReg  = pIO->WriteReg;
    pObj->IO.ReadReg   = pIO->ReadReg;
    pObj->IO.SendData  = pIO->SendData;
    pObj->IO.RecvData  = pIO->RecvData;
    pObj->IO.GetTick   = pIO->GetTick;

    pObj->Ctx.ReadReg   = ST7735_ReadRegWrap;
    pObj->Ctx.WriteReg  = ST7735_WriteRegWrap;
    pObj->Ctx.SendData  = ST7735_SendDataWrap;
    pObj->Ctx.RecvData  = ST7735_RecvDataWrap;
    pObj->Ctx.handle    = pObj;

    if(pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = ST7735_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Initialize the st7735 LCD Component.
  * @param  pObj Component object
  * @param  ColorCoding RGB mode
  * @param  Orientation Display orientation
  * @retval Component status
  */
int32_t ST7735_Init(ST7735_Object_t *pObj, uint32_t ColorCoding, uint32_t Orientation)
{
  uint8_t tmp;
  int32_t ret;

  if(pObj == NULL)
  {
    ret = ST7735_ERROR;
  }
  else
  {
        /* Out of sleep mode, 0 args, delay 120ms */
    tmp = 0x00U;
    ret = st7735_write_reg(&pObj->Ctx, ST7735_SW_RESET, &tmp, 0);
        (void)ST7735_IO_Delay(pObj, 120);

    /* Out of sleep mode, 0 args, no delay */
    tmp = 0x00U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_SLEEP_OUT, &tmp, 1);

        /* Frame rate ctrl - normal mode, 3 args:Rate = fosc/(1x2+40) * (LINE+2C+2D)*/
    ret += st7735_write_reg(&pObj->Ctx, ST7735_FRAME_RATE_CTRL1, &tmp, 0);
    tmp = 0x01U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Frame rate control - idle mode, 3 args:Rate = fosc/(1x2+40) * (LINE+2C+2D) */
    tmp = 0x01U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_FRAME_RATE_CTRL2, &tmp, 1);
    tmp = 0x2CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Frame rate ctrl - partial mode, 6 args: Dot inversion mode, Line inversion mode */
    tmp = 0x01U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_FRAME_RATE_CTRL3, &tmp, 1);
    tmp = 0x2CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x01U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Display inversion ctrl, 1 arg, no delay: No inversion */
    tmp = 0x07U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_FRAME_INVERSION_CTRL, &tmp, 1);

    /* Power control, 3 args, no delay: -4.6V , AUTO mode */
    tmp = 0xA2U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PWR_CTRL1, &tmp, 1);
    tmp = 0x02U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x84U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Power control, 1 arg, no delay: VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD */
    tmp = 0xC5U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PWR_CTRL2, &tmp, 1);

    /* Power control, 2 args, no delay: Opamp current small, Boost frequency */
    tmp = 0x0AU;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PWR_CTRL3, &tmp, 1);
    tmp = 0x00U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Power control, 2 args, no delay: BCLK/2, Opamp current small & Medium low */
    tmp = 0x8AU;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PWR_CTRL4, &tmp, 1);
    tmp = 0x2AU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Power control, 2 args, no delay */
    tmp = 0x8AU;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PWR_CTRL5, &tmp, 1);
    tmp = 0xEEU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Power control, 1 arg, no delay */
    tmp = 0x0EU;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_VCOMH_VCOML_CTRL1, &tmp, 1);

#if IS_BOE_PANEL
    /* Not Invert display, no args, no delay */
    ret += st7735_write_reg(&pObj->Ctx, ST7735_DISPLAY_INVERSION_OFF, &tmp, 0);
#else
    /* Invert display, no args, no delay */
    ret += st7735_write_reg(&pObj->Ctx, ST7735_DISPLAY_INVERSION_ON, &tmp, 0);
#endif
    /* Set color mode, 1 arg, no delay */
    ret += st7735_write_reg(&pObj->Ctx, ST7735_COLOR_MODE, (uint8_t*)&ColorCoding, 1);

    /* Magical unicorn dust, 16 args, no delay */
    tmp = 0x02U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_PV_GAMMA_CTRL, &tmp, 1);
    tmp = 0x1CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x07U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x12U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x37U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x32U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x29U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x29U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x25U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2BU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x39U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x00U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x01U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x03U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x10U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Sparkles and rainbows, 16 args, no delay */
    tmp = 0x03U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_NV_GAMMA_CTRL, &tmp, 1);
    tmp = 0x1DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x07U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x06U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2EU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2CU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x29U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2DU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2EU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x2EU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x37U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x3FU;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x00U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x00U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x02U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
    tmp = 0x10U;
    ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

    /* Normal display on, no args, no delay */
    tmp  = 0x00U;
    ret += st7735_write_reg(&pObj->Ctx, ST7735_NORMAL_DISPLAY_OFF, &tmp, 1);

    /* Main screen turn on, no delay */
    ret += st7735_write_reg(&pObj->Ctx, ST7735_DISPLAY_ON, &tmp, 1);

    /* Set the display Orientation and the default display window */
    ret += ST7735_SetOrientation(pObj, Orientation);
  }

  if(ret != ST7735_OK)
  {
      LOG_E("error %d", ret);
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  De-Initialize the st7735 LCD Component.
  * @param  pObj Component object
  * @retval Component status
  */
int32_t ST7735_DeInit(ST7735_Object_t *pObj)
{
  (void)(pObj);

  return ST7735_OK;
}

/**
  * @brief  Get the st7735 ID.
  * @param  pObj Component object
  * @param  Id Component ID
  * @retval The component status
  */
int32_t ST7735_ReadID(ST7735_Object_t *pObj, uint32_t *Id)
{
  int32_t ret;
  uint8_t tmp[3];

  if(st7735_read_reg(&pObj->Ctx, ST7735_READ_ID1, &tmp[0]) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
  else if(st7735_read_reg(&pObj->Ctx, ST7735_READ_ID2, &tmp[1]) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
    else if(st7735_read_reg(&pObj->Ctx, ST7735_READ_ID3, &tmp[2]) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
  else
  {

    *Id = ((uint32_t)tmp[2])<<0| ((uint32_t)tmp[1])<<8 | ((uint32_t)tmp[0])<<16;
        //*Id = __rbit(*Id);
    ret = ST7735_OK;
  }

  return ret;
}

/**
  * @brief  Enables the Display.
  * @param  pObj Component object
  * @retval The component status
  */
int32_t ST7735_DisplayOn(ST7735_Object_t *pObj)
{
  int32_t ret;
  uint8_t tmp = 0;

  ret = st7735_write_reg(&pObj->Ctx, ST7735_NORMAL_DISPLAY_OFF, &tmp, 0);
  (void)ST7735_IO_Delay(pObj, 10);
  ret += st7735_write_reg(&pObj->Ctx, ST7735_DISPLAY_ON, &tmp, 0);
  (void)ST7735_IO_Delay(pObj, 10);
  ret += st7735_write_reg(&pObj->Ctx, ST7735_MADCTL, &tmp, 0);
  tmp = (uint8_t)OrientationTab[ST7735Ctx.Orientation][1];
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Disables the Display.
  * @param  pObj Component object
  * @retval The component status
  */
int32_t ST7735_DisplayOff(ST7735_Object_t *pObj)
{
  int32_t ret;
  uint8_t tmp = 0;

  ret = st7735_write_reg(&pObj->Ctx, ST7735_NORMAL_DISPLAY_OFF, &tmp, 0);
  (void)ST7735_IO_Delay(pObj, 10);
  ret += st7735_write_reg(&pObj->Ctx, ST7735_DISPLAY_OFF, &tmp, 0);
  (void)ST7735_IO_Delay(pObj, 10);
  ret += st7735_write_reg(&pObj->Ctx, ST7735_MADCTL, &tmp, 0);
  tmp = (uint8_t)OrientationTab[ST7735Ctx.Orientation][1];
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Set the display brightness.
  * @param  pObj Component object
  * @param  Brightness   display brightness to be set
  * @retval Component status
  */
int32_t ST7735_SetBrightness(ST7735_Object_t *pObj, uint32_t Brightness)
{
  (void)(pObj);
  (void)(Brightness);

  /* Feature not supported */
  return ST7735_ERROR;
}

/**
  * @brief  Get the display brightness.
  * @param  pObj Component object
  * @param  Brightness   display brightness to be returned
  * @retval Component status
  */
int32_t ST7735_GetBrightness(ST7735_Object_t *pObj, uint32_t *Brightness)
{
  (void)(pObj);
  (void)(Brightness);

  /* Feature not supported */
  return ST7735_ERROR;
}

/**
  * @brief  Set the Display Orientation.
  * @param  pObj Component object
  * @param  Orientation ST7735_ORIENTATION_PORTRAIT, ST7735_ORIENTATION_PORTRAIT_ROT180
  *                     ST7735_ORIENTATION_LANDSCAPE or ST7735_ORIENTATION_LANDSCAPE_ROT180
  * @retval The component status
  */
int32_t ST7735_SetOrientation(ST7735_Object_t *pObj, uint32_t Orientation)
{
  int32_t ret;
  uint8_t tmp;

  if((Orientation == ST7735_ORIENTATION_PORTRAIT) || (Orientation == ST7735_ORIENTATION_PORTRAIT_ROT180))
  {
    ST7735Ctx.Width  = ST7735_WIDTH;
    ST7735Ctx.Height = ST7735_HEIGHT;
  }
  else
  {
    ST7735Ctx.Width  = ST7735_HEIGHT;
    ST7735Ctx.Height = ST7735_WIDTH;
  }
    ST7735Ctx.Orientation = Orientation;

  ret = ST7735_SetDisplayWindow(pObj, 0U, 0U, ST7735Ctx.Width, ST7735Ctx.Height);

  tmp = (uint8_t)OrientationTab[Orientation][1];
  ret += st7735_write_reg(&pObj->Ctx, ST7735_MADCTL, &tmp, 1);



  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Set the Display Orientation.
  * @param  pObj Component object
  * @param  Orientation ST7735_ORIENTATION_PORTRAIT, ST7735_ORIENTATION_LANDSCAPE
  *                      or ST7735_ORIENTATION_LANDSCAPE_ROT180
  * @retval The component status
  */
int32_t ST7735_GetOrientation(ST7735_Object_t *pObj, uint32_t *Orientation)
{

  *Orientation = ST7735Ctx.Orientation;

  return ST7735_OK;
}

/**
  * @brief  Set Cursor position.
  * @param  pObj Component object
  * @param  Xpos specifies the X position.
  * @param  Ypos specifies the Y position.
  * @retval The component status
  */
int32_t ST7735_SetCursor(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos)
{
  int32_t ret;
  uint8_t tmp;

    /* Cursor calibration */
    if(ST7735Ctx.Orientation <= ST7735_ORIENTATION_PORTRAIT_ROT180)
    {
#if IS_BOE_PANEL
        Xpos += 24;
        Ypos += 0;
#else
        Xpos += 26;
        Ypos += 1;
#endif
    }
    else
    {
#if IS_BOE_PANEL
        Xpos += 0;
        Ypos += 24;
#else
        Xpos += 1;
        Ypos += 26;
#endif
    }

  ret = st7735_write_reg(&pObj->Ctx, ST7735_CASET, &tmp, 0);
  tmp = (uint8_t)(Xpos >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)(Xpos & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

  ret += st7735_write_reg(&pObj->Ctx, ST7735_RASET, &tmp, 0);
  tmp = (uint8_t)(Ypos >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)(Ypos & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  ret += st7735_write_reg(&pObj->Ctx, ST7735_WRITE_RAM, &tmp, 0);

  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Displays a bitmap picture.
  * @param  pObj Component object
  * @param  Xpos Bmp X position in the LCD
  * @param  Ypos Bmp Y position in the LCD
  * @param  pBmp Bmp picture address.
  * @retval The component status
  */
int32_t ST7735_DrawBitmap(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pBmp)
{
  int32_t ret = ST7735_OK;
  uint32_t index, size, width, height, y_pos;
  uint8_t pixel_val[2], tmp;
  uint8_t *pbmp;
  uint32_t counter = 0;

  /* Get bitmap data address offset */
  index = (uint32_t)pBmp[10] + ((uint32_t)pBmp[11] << 8) + ((uint32_t)pBmp[12] << 16)  + ((uint32_t)pBmp[13] << 24);

  /* Read bitmap width */
  width = (uint32_t)pBmp[18] + ((uint32_t)pBmp[19] << 8) + ((uint32_t)pBmp[20] << 16)  + ((uint32_t)pBmp[21] << 24);

  /* Read bitmap height */
  height = (uint32_t)pBmp[22] + ((uint32_t)pBmp[23] << 8) + ((uint32_t)pBmp[24] << 16)  + ((uint32_t)pBmp[25] << 24);

  /* Read bitmap size */
  size = (uint32_t)pBmp[2] + ((uint32_t)pBmp[3] << 8) + ((uint32_t)pBmp[4] << 16)  + ((uint32_t)pBmp[5] << 24);
  size = size - index;

  pbmp = pBmp + index;

  /* Remap Ypos, st7735 works with inverted X in case of bitmap */
  /* X = 0, cursor is on Top corner */
  y_pos = ST7735Ctx.Height - Ypos - height;

  if(ST7735_SetDisplayWindow(pObj, Xpos, y_pos, width, height) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
  else
  {
    /* Set GRAM write direction and BGR = 0 */
    tmp = (uint8_t)OrientationTab[ST7735Ctx.Orientation][0];

    if(st7735_write_reg(&pObj->Ctx, ST7735_MADCTL, &tmp, 1) != ST7735_OK)
    {
      ret = ST7735_ERROR;
    }/* Set Cursor */
    else if(ST7735_SetCursor(pObj, Xpos, y_pos) != ST7735_OK)
    {
      ret = ST7735_ERROR;
    }
    else
    {
      do
      {
        pixel_val[0] = *(pbmp + 1);
        pixel_val[1] = *(pbmp);
        if(st7735_send_data(&pObj->Ctx, pixel_val, 2U) != ST7735_OK)
        {
          ret = ST7735_ERROR;
          break;
        }
        counter +=2U;
        pbmp += 2;
      }while(counter < size);

      tmp = (uint8_t)OrientationTab[ST7735Ctx.Orientation][1];
      if(st7735_write_reg(&pObj->Ctx, ST7735_MADCTL, &tmp, 1) != ST7735_OK)
      {
        ret = ST7735_ERROR;
      }
      else
      {
        if(ST7735_SetDisplayWindow(pObj, 0U, 0U, ST7735Ctx.Width, ST7735Ctx.Height) != ST7735_OK)
        {
          ret = ST7735_ERROR;
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  Draws a full RGB rectangle
  * @param  pObj Component object
  * @param  Xpos   specifies the X position.
  * @param  Ypos   specifies the Y position.
  * @param  pData  pointer to RGB data
  * @param  Width  specifies the rectangle width.
  * @param  Height Specifies the rectangle height
  * @retval The component status
  */
int32_t ST7735_FillRGBRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height)
{
  int32_t ret = ST7735_OK;
  static uint8_t pdata[640];
  uint8_t *rgb_data = pData;
  uint32_t i, j;

  if(((Xpos + Width) > ST7735Ctx.Width) || ((Ypos + Height) > ST7735Ctx.Height))
  {
    ret = ST7735_ERROR;
  }/* Set Cursor */
  else
  {
    for(j = 0; j < Height; j++)
    {
      if(ST7735_SetCursor(pObj, Xpos, Ypos+j) != ST7735_OK)
      {
        ret = ST7735_ERROR;
      }
      else
      {
        for(i = 0; i < Width; i++)
        {
          pdata[2U*i] = (uint8_t)(*(rgb_data));
          pdata[(2U*i) + 1U] = (uint8_t)(*(rgb_data + 1));
          rgb_data +=2;
        }
        if(st7735_send_data(&pObj->Ctx, (uint8_t*)&pdata[0], 2U*Width) != ST7735_OK)
        {
          ret = ST7735_ERROR;
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  Draw Horizontal line.
  * @param  pObj Component object
  * @param  Xpos   specifies the X position.
  * @param  Ypos   specifies the Y position.
  * @param  Length specifies the Line length.
  * @param  Color  Specifies the RGB color in RGB565 format
  * @retval The component status
  */
int32_t ST7735_DrawHLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  uint32_t i;
  static uint8_t pdata[640];

  if((Xpos + Length) > ST7735Ctx.Width)
  {
    ret = ST7735_ERROR;
  }/* Set Cursor */
  else if(ST7735_SetCursor(pObj, Xpos, Ypos) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
  else
  {
    for(i = 0; i < Length; i++)
    {
      /* Exchange LSB and MSB to fit LCD specification */
      pdata[2U*i] = (uint8_t)(Color >> 8);
      pdata[(2U*i) + 1U] = (uint8_t)(Color);

//      pdata[(2U*i) + 1U] = (uint8_t)(Color >> 8);
//      pdata[2U*i] = (uint8_t)(Color);
    }
    if(st7735_send_data(&pObj->Ctx, (uint8_t*)&pdata[0], 2U*Length) != ST7735_OK)
    {
      ret = ST7735_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Draw vertical line.
  * @param  pObj Component object
  * @param  Color    Specifies the RGB color
  * @param  Xpos     specifies the X position.
  * @param  Ypos     specifies the Y position.
  * @param  Length   specifies the Line length.
  * @retval The component status
  */
int32_t ST7735_DrawVLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  uint32_t counter;

  if((Ypos + Length) > ST7735Ctx.Height)
  {
    ret = ST7735_ERROR;
  }
  else
  {
    for(counter = 0; counter < Length; counter++)
    {
      if(ST7735_SetPixel(pObj, Xpos, Ypos + counter, Color) != ST7735_OK)
      {
        ret = ST7735_ERROR;
        break;
      }
    }
  }

  return ret;
}

/**
  * @brief  Fill rectangle
  * @param  pObj Component object
  * @param  Xpos X position
  * @param  Ypos Y position
  * @param  Width Rectangle width
  * @param  Height Rectangle height
  * @param  Color Draw color
  * @retval Component status
  */
int32_t ST7735_FillRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  uint32_t i, y_pos = Ypos;

  for(i = 0; i < Height; i++)
  {
    if(ST7735_DrawHLine(pObj, Xpos, y_pos, Width, Color) != ST7735_OK)
    {
      ret = ST7735_ERROR;
      break;
    }
    y_pos++;
  }

  return ret;
}

/**
  * @brief  Write pixel.
  * @param  pObj Component object
  * @param  Xpos specifies the X position.
  * @param  Ypos specifies the Y position.
  * @param  Color the RGB pixel color in RGB565 format
  * @retval The component status
  */
int32_t ST7735_SetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  uint16_t color;

  /* Exchange LSB and MSB to fit LCD specification */
  color = (uint16_t)((uint16_t)Color << 8);
  color |= (uint16_t)((uint16_t)(Color >> 8));

  if((Xpos >= ST7735Ctx.Width) || (Ypos >= ST7735Ctx.Height))
  {
    ret = ST7735_ERROR;
  }/* Set Cursor */
  else if(ST7735_SetCursor(pObj, Xpos, Ypos) != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }
  else
  {
    /* Write RAM data */
    if(st7735_send_data(&pObj->Ctx, (uint8_t*)&color, 2) != ST7735_OK)
    {
      ret = ST7735_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Read pixel.
  * @param  pObj Component object
  * @param  Xpos specifies the X position.
  * @param  Ypos specifies the Y position.
  * @param  Color the RGB pixel color in RGB565 format
  * @retval The component status
  */
int32_t ST7735_GetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t *Color)
{
  int32_t ret;
  uint8_t pixel_lsb, pixel_msb;
  uint8_t tmp;


  /* Set Cursor */
  ret = ST7735_SetCursor(pObj, Xpos, Ypos);

  /* Prepare to read LCD RAM */
  ret += st7735_read_reg(&pObj->Ctx, ST7735_READ_RAM, &tmp);   /* RAM read data command */

  /* Dummy read */
  ret += st7735_recv_data(&pObj->Ctx, &tmp, 1);

  /* Read first part of the RGB888 data */
  ret += st7735_recv_data(&pObj->Ctx, &pixel_lsb, 1);
  /* Read first part of the RGB888 data */
  ret += st7735_recv_data(&pObj->Ctx, &pixel_msb, 1);

  *Color = ((uint32_t)(pixel_lsb)) + ((uint32_t)(pixel_msb) << 8);

  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Get the LCD pixel Width.
  * @param  pObj Component object
  * @retval The Lcd Pixel Width
  */
int32_t ST7735_GetXSize(ST7735_Object_t *pObj, uint32_t *XSize)
{
  (void)pObj;

  *XSize = ST7735Ctx.Width;

  return ST7735_OK;
}

/**
  * @brief  Get the LCD pixel Height.
  * @param  pObj Component object
  * @retval The Lcd Pixel Height
  */
int32_t ST7735_GetYSize(ST7735_Object_t *pObj, uint32_t *YSize)
{
  (void)pObj;

  *YSize = ST7735Ctx.Height;

  return ST7735_OK;
}

/**
  * @}
  */

/** @defgroup ST7735_Private_Functions  Private Functions
  * @{
  */
/**
  * @brief  Sets a display window
  * @param  Xpos   specifies the X bottom left position.
  * @param  Ypos   specifies the Y bottom left position.
  * @param  Height display window height.
  * @param  Width  display window width.
  * @retval Component status
  */
static int32_t ST7735_SetDisplayWindow(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
  int32_t ret;
  uint8_t tmp;

    /* Cursor calibration */
    if(ST7735Ctx.Orientation <= ST7735_ORIENTATION_PORTRAIT_ROT180)
    {
#if IS_BOE_PANEL
        Xpos += 24;
        Ypos += 0;
#else
        Xpos += 26;
        Ypos += 1;
#endif
    }
    else
    {
#if IS_BOE_PANEL
        Xpos += 0;
        Ypos += 24;
#else
        Xpos += 1;
        Ypos += 26;
#endif
    }

  /* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
  ret = st7735_write_reg(&pObj->Ctx, ST7735_CASET, &tmp, 0);
  tmp = (uint8_t)(Xpos >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)(Xpos & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)((Xpos + Width - 1U) >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)((Xpos + Width - 1U) & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

  /* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
  ret += st7735_write_reg(&pObj->Ctx, ST7735_RASET, &tmp, 0);
  tmp = (uint8_t)(Ypos >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)(Ypos & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)((Ypos + Height - 1U) >> 8U);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);
  tmp = (uint8_t)((Ypos + Height - 1U) & 0xFFU);
  ret += st7735_send_data(&pObj->Ctx, &tmp, 1);

  if(ret != ST7735_OK)
  {
    ret = ST7735_ERROR;
  }

  return ret;
}

/**
  * @brief  Wrap component ReadReg to Bus Read function
  * @param  Handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @retval Component error status
  */
static int32_t ST7735_ReadRegWrap(void *Handle, uint8_t Reg, uint8_t* pData)
{
  ST7735_Object_t *pObj = (ST7735_Object_t *)Handle;

  return pObj->IO.ReadReg(Reg, pData);
}

/**
  * @brief  Wrap component WriteReg to Bus Write function
  * @param  handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval Component error status
  */
static int32_t ST7735_WriteRegWrap(void *Handle, uint8_t Reg, uint8_t *pData, uint32_t Length)
{
  ST7735_Object_t *pObj = (ST7735_Object_t *)Handle;

  return pObj->IO.WriteReg(Reg, pData, Length);
}


/**
  * @brief  Wrap component SendData to Bus Write function
  * @param  handle  Component object handle
  * @param  pData  The target register value to be written
  * @retval Component error status
  */
static int32_t ST7735_SendDataWrap(void *Handle, uint8_t *pData, uint32_t Length)
{
  ST7735_Object_t *pObj = (ST7735_Object_t *)Handle;

  return pObj->IO.SendData(pData, Length);
}

/**
  * @brief  Wrap component SendData to Bus Write function
  * @param  handle  Component object handle
  * @param  pData  The target register value to be written
  * @retval Component error status
  */
static int32_t ST7735_RecvDataWrap(void *Handle, uint8_t *pData, uint32_t Length)
{
  ST7735_Object_t *pObj = (ST7735_Object_t *)Handle;

  return pObj->IO.RecvData(pData, Length);
}

/**
  * @brief  ST7735 delay
  * @param  Delay  Delay in ms
  * @retval Component error status
  */
static int32_t ST7735_IO_Delay(ST7735_Object_t *pObj, uint32_t Delay)
{
  rt_thread_mdelay(Delay);
  return ST7735_OK;
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

