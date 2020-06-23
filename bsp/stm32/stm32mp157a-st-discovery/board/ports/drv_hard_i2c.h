/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-18     thread-liu        the first version
 */

#ifndef __DRV_HARD_I2C_H__
#define __DRV_HARD_I2C_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STPMU1_I2C_ADDRESS               ((0x33 & 0x7F) << 1)

#ifndef I2C_SPEED
#define I2C_SPEED                        ((uint32_t)100000)
#endif /* I2C_SPEED */

#ifndef I2C4_TIMING
#define I2C4_TIMING                      ((uint32_t)0x10805E89)
#endif

static int32_t I2C4_WriteReg(uint16_t DevAddr, uint16_t MemAddSize, uint16_t Reg, uint8_t *pData, uint16_t Length);
static int32_t I2C4_ReadReg(uint16_t DevAddr, uint16_t MemAddSize, uint16_t Reg, uint8_t *pData, uint16_t Length);

int32_t BSP_I2C4_Init(void);
int32_t BSP_I2C4_DeInit(void);
int32_t BSP_I2C4_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_IsReady(uint16_t DevAddr, uint32_t Trials);

HAL_StatusTypeDef MX_I2C4_Init(I2C_HandleTypeDef *hI2c);

#ifdef __cplusplus
}
#endif

#endif
