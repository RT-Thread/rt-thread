/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_HARD_I2C_H__
#define __DRV_HARD_I2C_H__

#include "drv_config.h"
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define I2C_USING_TX_DMA_FLAG       (1U)
#define I2C_USING_RX_DMA_FLAG       (1U << 1)


typedef enum
{
    I2C_RESET   = 0x00U,
    I2C_READY   = 0x01U,
    I2C_BUSY_TX = 0x02U,
    I2C_BUSY_RX = 0x03U,
} I2C_StateTypeDef;

struct n32_i2c_config
{
    const char    *name;
    I2C_Module    *Instance;
    rt_uint32_t   timing;
    rt_uint32_t   timeout;
    IRQn_Type     evirq_type;
    IRQn_Type     erirq_type;

    rt_uint32_t   scl_af_width;  /* SCL Analog Filter Width */
    rt_uint32_t   sda_af_width;  /* SDA Analog Filter Width */
    rt_uint32_t   df_width;      /* Digital Filter Width */

    uint32_t periph;
    void (*EnablePeriphClk)(uint32_t periph, FunctionalState cmd);
    void (*I2CKerClkSource)(uint32_t CLK_source);

    struct dma_config *dma_rx, *dma_tx;
};

struct hard_i2c_transfer
{
    uint8_t *pBuffPtr;           /* Pointer to I2C transfer buffer */
    uint16_t XferSize;           /* I2C transfer size */
    __IO uint16_t XferCount;     /* I2C transfer counter */
    __IO uint32_t XferOptions;   /* I2C sequantial transfer options */
    __IO I2C_StateTypeDef state; /* I2C communication state */
};


struct n32_i2c
{
    struct hard_i2c_transfer transfer;

    struct n32_i2c_config       *config;
    struct rt_i2c_bus_device    i2c_bus;
    rt_uint8_t                  i2c_dma_flag;
    struct rt_completion completion;

    void (*i2c_isr_callback)(struct n32_i2c *drv_i2c);
};



#ifdef __cplusplus
}
#endif


#if defined(RT_USING_I2C) && defined(BSP_USING_I2C)


#endif /* defined(RT_USING_I2C) && defined(BSP_USING_I2C) */


#endif /* __DRV_HARD_I2C_H__ */

