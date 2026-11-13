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
extern "C" {
#endif

#define I2C_USING_TX_DMA_FLAG (1U)
#define I2C_USING_RX_DMA_FLAG (1U << 1)


typedef enum
{
    I2C_RESET = 0x00U,
    I2C_READY = 0x01U,
    I2C_BUSY_TX = 0x02U,
    I2C_BUSY_RX = 0x03U,
} I2C_StateTypeDef;

struct n32_i2c_config
{
    const char *name;
    I2C_Module *Instance;

    /* SCL rate, in the unit the series' I2C IP takes.  As on STM32, one field
     * carries both meanings, selected by the SoC:
     *   N32H7xx                  - raw I2C_TIMINGR value
     *   N32H47x_48x / N32H49x    - bus speed in Hz; the vendor I2C_Init()
     *                              derives CLKCTRL and TMRISE from it.  The
     *                              two families diverge above 400 kHz and
     *                              neither one rejects the value: N32H49x
     *                              keeps F/S set and moves to the fast-mode+
     *                              rise time, while N32H47x_48x falls
     *                              through to the standard-mode divider with
     *                              F/S left clear.  Keep it at or below
     *                              400 kHz.
     * Never leave it 0; n32_i2c_init() substitutes DEFAULT_I2C_TIMING_VALUE.
     */
    rt_uint32_t timing;

    rt_uint32_t timeout;
    IRQn_Type evirq_type;
    IRQn_Type erirq_type;

    rt_uint32_t scl_af_width;  /* SCL Analog Filter Width */
    rt_uint32_t sda_af_width;  /* SDA Analog Filter Width */
    rt_uint32_t df_width;      /* Digital Filter Width */

    uint32_t periph;
    void (*EnablePeriphClk)(uint32_t periph, FunctionalState cmd);
#if defined(SOC_SERIES_N32H7xx)
    void (*I2CKerClkSource)(uint32_t CLK_source);
#endif

    struct dma_config *dma_rx, *dma_tx;

#if defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
    DMA_InitType dma_rx_init_str;
    DMA_InitType dma_tx_init_str;
#endif
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

    struct n32_i2c_config *config;
    struct rt_i2c_bus_device i2c_bus;
    rt_uint8_t i2c_dma_flag;
    struct rt_completion completion;

    void (*i2c_isr_callback)(struct n32_i2c *drv_i2c);
};


#ifdef __cplusplus
}
#endif


#if defined(RT_USING_I2C) && defined(BSP_USING_I2C)


#endif /* defined(RT_USING_I2C) && defined(BSP_USING_I2C) */


#endif /* __DRV_HARD_I2C_H__ */

