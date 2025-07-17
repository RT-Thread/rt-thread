/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_I2C1)
#ifndef I2C1_CONFIG
#define I2C1_CONFIG                                             \
    {                                                           \
        .name     = "i2c1",                                     \
        .Instance = CM_I2C,                                     \
        .clock    = FCG1_PERIPH_I2C,                            \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C1_CONFIG */
#endif

#if defined(BSP_I2C1_USING_DMA)
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C1_TX_DMA_INSTANCE,                 \
        .channel        = I2C1_TX_DMA_CHANNEL,                  \
        .clock          = I2C1_TX_DMA_CLOCK,                    \
        .trigger_select = I2C1_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C_TEI,                      \
        .flag           = I2C1_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C1_TX_DMA_IRQn,                     \
            .irq_prio   = I2C1_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C1_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C1_TX_DMA_CONFIG */

#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C1_RX_DMA_INSTANCE,                 \
        .channel        = I2C1_RX_DMA_CHANNEL,                  \
        .clock          = I2C1_RX_DMA_CLOCK,                    \
        .trigger_select = I2C1_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C_RXI,                      \
        .flag           = I2C1_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C1_RX_DMA_IRQn,                     \
            .irq_prio   = I2C1_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C1_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif
