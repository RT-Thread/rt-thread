/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
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
        .Instance = CM_I2C1,                                    \
        .clock    = FCG1_PERIPH_I2C1,                           \
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
        .trigger_event  = EVT_SRC_I2C1_TEI,                     \
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
        .trigger_event  = EVT_SRC_I2C1_RXI,                     \
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

#if defined(BSP_USING_I2C2)
#ifndef I2C2_CONFIG
#define I2C2_CONFIG                                             \
    {                                                           \
        .name     = "i2c2",                                     \
        .Instance = CM_I2C2,                                    \
        .clock    = FCG1_PERIPH_I2C2,                           \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C2_CONFIG */

#if defined(BSP_I2C2_USING_DMA)
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C2_TX_DMA_INSTANCE,                 \
        .channel        = I2C2_TX_DMA_CHANNEL,                  \
        .clock          = I2C2_TX_DMA_CLOCK,                    \
        .trigger_select = I2C2_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C2_TEI,                     \
        .flag           = I2C2_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C2_TX_DMA_IRQn,                     \
            .irq_prio   = I2C2_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C2_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C2_TX_DMA_CONFIG */

#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C2_RX_DMA_INSTANCE,                 \
        .channel        = I2C2_RX_DMA_CHANNEL,                  \
        .clock          = I2C2_RX_DMA_CLOCK,                    \
        .trigger_select = I2C2_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C2_RXI,                     \
        .flag           = I2C2_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C2_RX_DMA_IRQn,                     \
            .irq_prio   = I2C2_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C2_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_USING_DMA */
#endif

#if defined(BSP_USING_I2C3)
#ifndef I2C3_CONFIG
#define I2C3_CONFIG                                             \
    {                                                           \
        .name     = "i2c3",                                     \
        .Instance = CM_I2C3,                                    \
        .clock    = FCG1_PERIPH_I2C3,                           \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C3_CONFIG */

#if defined(BSP_I2C3_USING_DMA)
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C3_TX_DMA_INSTANCE,                 \
        .channel        = I2C3_TX_DMA_CHANNEL,                  \
        .clock          = I2C3_TX_DMA_CLOCK,                    \
        .trigger_select = I2C3_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C3_TEI,                     \
        .flag           = I2C3_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C3_TX_DMA_IRQn,                     \
            .irq_prio   = I2C3_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C3_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C3_TX_DMA_CONFIG */

#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C3_RX_DMA_INSTANCE,                 \
        .channel        = I2C3_RX_DMA_CHANNEL,                  \
        .clock          = I2C3_RX_DMA_CLOCK,                    \
        .trigger_select = I2C3_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C3_RXI,                     \
        .flag           = I2C3_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C3_RX_DMA_IRQn,                     \
            .irq_prio   = I2C3_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C3_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_USING_DMA */
#endif

#if defined(BSP_USING_I2C4)
#ifndef I2C4_CONFIG
#define I2C4_CONFIG                                             \
    {                                                           \
        .name     = "i2c4",                                     \
        .Instance = CM_I2C4,                                    \
        .clock    = FCG1_PERIPH_I2C4,                           \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C4_CONFIG */

#if defined(BSP_I2C4_USING_DMA)
#ifndef I2C4_TX_DMA_CONFIG
#define I2C4_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C4_TX_DMA_INSTANCE,                 \
        .channel        = I2C4_TX_DMA_CHANNEL,                  \
        .clock          = I2C4_TX_DMA_CLOCK,                    \
        .trigger_select = I2C4_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C4_TEI,                     \
        .flag           = I2C4_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C4_TX_DMA_IRQn,                     \
            .irq_prio   = I2C4_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C4_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C4_TX_DMA_CONFIG */

#ifndef I2C4_RX_DMA_CONFIG
#define I2C4_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C4_RX_DMA_INSTANCE,                 \
        .channel        = I2C4_RX_DMA_CHANNEL,                  \
        .clock          = I2C4_RX_DMA_CLOCK,                    \
        .trigger_select = I2C4_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C4_RXI,                     \
        .flag           = I2C4_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C4_RX_DMA_IRQn,                     \
            .irq_prio   = I2C4_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C4_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_USING_DMA */
#endif

#if defined(BSP_USING_I2C5)
#ifndef I2C5_CONFIG
#define I2C5_CONFIG                                             \
    {                                                           \
        .name     = "i2c5",                                     \
        .Instance = CM_I2C5,                                    \
        .clock    = FCG1_PERIPH_I2C5,                           \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C5_CONFIG */

#if defined(BSP_I2C5_USING_DMA)
#ifndef I2C5_TX_DMA_CONFIG
#define I2C5_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C5_TX_DMA_INSTANCE,                 \
        .channel        = I2C5_TX_DMA_CHANNEL,                  \
        .clock          = I2C5_TX_DMA_CLOCK,                    \
        .trigger_select = I2C5_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C5_TEI,                     \
        .flag           = I2C5_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C5_TX_DMA_IRQn,                     \
            .irq_prio   = I2C5_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C5_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C5_TX_DMA_CONFIG */

#ifndef I2C5_RX_DMA_CONFIG
#define I2C5_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C5_RX_DMA_INSTANCE,                 \
        .channel        = I2C5_RX_DMA_CHANNEL,                  \
        .clock          = I2C5_RX_DMA_CLOCK,                    \
        .trigger_select = I2C5_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C5_RXI,                     \
        .flag           = I2C5_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C5_RX_DMA_IRQn,                     \
            .irq_prio   = I2C5_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C5_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C5_RX_DMA_CONFIG */
#endif /* BSP_I2C5_USING_DMA */
#endif

#if defined(BSP_USING_I2C6)
#ifndef I2C6_CONFIG
#define I2C6_CONFIG                                             \
    {                                                           \
        .name     = "i2c6",                                     \
        .Instance = CM_I2C6,                                    \
        .clock    = FCG1_PERIPH_I2C6,                           \
        .baudrate = 100000UL,                                   \
        .timeout  = 10000UL,                                    \
    }
#endif /* I2C6_CONFIG */

#if defined(BSP_I2C6_USING_DMA)
#ifndef I2C6_TX_DMA_CONFIG
#define I2C6_TX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C6_TX_DMA_INSTANCE,                 \
        .channel        = I2C6_TX_DMA_CHANNEL,                  \
        .clock          = I2C6_TX_DMA_CLOCK,                    \
        .trigger_select = I2C6_TX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C6_TEI,                     \
        .flag           = I2C6_TX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C6_TX_DMA_IRQn,                     \
            .irq_prio   = I2C6_TX_DMA_INT_PRIO,                 \
            .int_src    = I2C6_TX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C6_TX_DMA_CONFIG */

#ifndef I2C6_RX_DMA_CONFIG
#define I2C6_RX_DMA_CONFIG                                      \
    {                                                           \
        .Instance       = I2C6_RX_DMA_INSTANCE,                 \
        .channel        = I2C6_RX_DMA_CHANNEL,                  \
        .clock          = I2C6_RX_DMA_CLOCK,                    \
        .trigger_select = I2C6_RX_DMA_TRIG_SELECT,              \
        .trigger_event  = EVT_SRC_I2C6_RXI,                     \
        .flag           = I2C6_RX_DMA_TRANS_FLAG,               \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = I2C6_RX_DMA_IRQn,                     \
            .irq_prio   = I2C6_RX_DMA_INT_PRIO,                 \
            .int_src    = I2C6_RX_DMA_INT_SRC,                  \
        },                                                      \
    }
#endif /* I2C6_RX_DMA_CONFIG */
#endif /* BSP_I2C6_USING_DMA */
#endif

#ifdef __cplusplus
}
#endif

#endif
