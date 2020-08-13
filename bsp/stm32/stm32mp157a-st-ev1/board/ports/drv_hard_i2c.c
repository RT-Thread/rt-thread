/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-18     thread-liu        the first version
 */

#include <board.h>
#include "drv_hard_i2c.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.hardi2c"
#include <drv_log.h>

I2C_HandleTypeDef hI2c4;

int32_t BSP_I2C4_Init(void)
{
    int32_t status = RT_EOK;

    if (HAL_I2C_GetState(&hI2c4) == HAL_I2C_STATE_RESET)
    {
        if (MX_I2C4_Init(&hI2c4) != HAL_OK)
        {
            status = -RT_EBUSY;
        }
       /* Init the I2C Msp */
        if (HAL_I2C_Init(&hI2c4) != HAL_OK)
        {
            LOG_D("I2C4 Init Error!\n");
            status = -RT_EBUSY;
        } 
    }
    return status;
}

int32_t BSP_I2C4_DeInit(void)
{
    int32_t status = RT_EOK;
    
    HAL_I2C_MspDeInit(&hI2c4);  

    /* Init the I2C */  
    if (HAL_I2C_DeInit(&hI2c4) != HAL_OK)
    {
        status = -RT_EEMPTY;
    }

    return status;
}

HAL_StatusTypeDef MX_I2C4_Init(I2C_HandleTypeDef *hI2c)
{
    hI2c4.Instance              = I2C4;   
    hI2c->Init.Timing           = I2C4_TIMING;
    hI2c->Init.OwnAddress1      = STPMU1_I2C_ADDRESS;
    hI2c->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hI2c->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hI2c->Init.OwnAddress2      = 0;
    hI2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hI2c->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hI2c->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
  
    return HAL_I2C_Init(hI2c);
}

int32_t BSP_I2C4_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    return I2C4_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length);
}

int32_t BSP_I2C4_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    return I2C4_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length);
}

int32_t BSP_I2C4_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    return I2C4_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length);
}

int32_t BSP_I2C4_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
    return I2C4_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length);
}

int32_t BSP_I2C4_IsReady(uint16_t DevAddr, uint32_t Trials)
{
    int32_t status = RT_EOK;

    if(HAL_I2C_IsDeviceReady(&hI2c4, DevAddr, Trials, 1000) != HAL_OK)
    {
        status = -RT_EBUSY;
    }

    return status;
}

static int32_t I2C4_WriteReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{  
    int32_t status = -RT_EIO;

    if(HAL_I2C_Mem_Write(&hI2c4, DevAddr, Reg, MemAddSize, pData, Length, 10000) == HAL_OK)
    {
        status = RT_EOK;
    }

    return status;
}

static int32_t I2C4_ReadReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{  
    int32_t status = -RT_EIO;

    if (HAL_I2C_Mem_Read(&hI2c4, DevAddr, Reg, MemAddSize, pData, Length, 10000) == HAL_OK)
    {
        status = RT_EOK;
    }

    return status;
}
