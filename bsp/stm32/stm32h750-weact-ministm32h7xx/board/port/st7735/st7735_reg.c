/**
  ******************************************************************************
  * @file    st7735_reg.c
  * @author  MCD Application Team
  * @brief   This file includes the LCD driver for st7735 LCD.
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
#include "st7735_reg.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ST7735_REG
  * @{
  */
 
/** @addtogroup ST7735_REG_Exported_Functions
  * @{
  */   

/**
  * @brief  Read ST7735 register
  * @param  ctx   Component context
  * @param  reg   Register to read
  * @param  pdata data to read from the register
  * @retval Component status
  */
int32_t st7735_read_reg(st7735_ctx_t *ctx, uint8_t reg, uint8_t *pdata)
{
  return ctx->ReadReg(ctx->handle, reg, pdata);
}

/**
  * @brief  Write ST7735 register
  * @param  ctx    Component context
  * @param  reg    Register to write
  * @param  pdata  data to write to the register
  * @param  length length of data to write to the register
  * @retval Component status
  */
int32_t st7735_write_reg(st7735_ctx_t *ctx, uint8_t reg, uint8_t *pdata, uint32_t length)
{
  return ctx->WriteReg(ctx->handle, reg, pdata, length);
}

/**
  * @brief  Send data
  * @param  ctx    Component context
  * @param  pdata  data to write
  * @param  length length of data to write
  * @retval Component status
  */
int32_t st7735_send_data(st7735_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->SendData(ctx->handle, pdata, length);
}

/**
  * @brief  Recieve data
  * @param  ctx    Component context
  * @param  pdata  data to read
  * @param  length length of data to read
  * @retval Component status
  */
int32_t st7735_recv_data(st7735_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->RecvData(ctx->handle, pdata, length);
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
