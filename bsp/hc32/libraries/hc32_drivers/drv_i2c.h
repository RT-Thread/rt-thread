/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rtdevice.h>
#include "board_config.h"
#include "drv_irq.h"
#include "drv_dma.h"

#ifdef BSP_USING_I2C

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
struct hc32_i2c_config
{
    const char              *name;
    CM_I2C_TypeDef          *Instance;
    rt_uint32_t             clock;
    rt_uint32_t             baudrate;
    rt_uint32_t             timeout;
    struct dma_config       *i2c_tx_dma;
    struct dma_config       *i2c_rx_dma;
};

struct hc32_i2c
{
    struct hc32_i2c_config      *config;
    struct rt_i2c_bus_device    i2c_bus;
    rt_uint8_t                  i2c_dma_flag;
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define I2C_USING_TX_DMA_FLAG       (1U)
#define I2C_USING_RX_DMA_FLAG       (1U << 1)

#ifdef __cplusplus
}
#endif

#endif /* BSP_USING_I2C */

#endif /* __DRV_I2C_H__ */
