/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-22     Donocean     first version
 */
 
#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

struct stm32_i2c_config
{
    I2C_TypeDef *Instance;
    char *bus_name;
    IRQn_Type irq_type;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

enum stm32_i2c_dma_flags
{
    I2C_USING_RX_DMA_FLAG = 0x01,
    I2C_USING_TX_DMA_FLAG = 0x02,
};

struct stm32_i2c
{
    I2C_HandleTypeDef handle;
    struct stm32_i2c_config *config;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_HandleTypeDef handle_rx;
        DMA_HandleTypeDef handle_tx;
    } dma;
#endif

    rt_uint8_t i2c_dma_flag; /**< @ref enum stm32_i2c_dma_flags */
    struct rt_i2c_bus_device i2c_bus; 
};

#endif /* __DRV_I2C_H__ */
