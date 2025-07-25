/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI,                                 \
        .bus_name = "spi1",                                 \
        .clock    = FCG1_PERIPH_SPI,                        \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI1_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI1_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI_SPEI,                 \
        },                                                  \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI1_TX_DMA_INSTANCE,             \
        .channel        = SPI1_TX_DMA_CHANNEL,              \
        .clock          = SPI1_TX_DMA_CLOCK,                \
        .trigger_select = SPI1_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI_SPTI,                 \
        .flag           = SPI1_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI1_TX_DMA_IRQn,                 \
            .irq_prio   = SPI1_TX_DMA_INT_PRIO,             \
            .int_src    = SPI1_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI1_RX_DMA_INSTANCE,             \
        .channel        = SPI1_RX_DMA_CHANNEL,              \
        .clock          = SPI1_RX_DMA_CLOCK,                \
        .trigger_select = SPI1_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI_SPRI,                 \
        .flag           = SPI1_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI1_RX_DMA_IRQn,                 \
            .irq_prio   = SPI1_RX_DMA_INT_PRIO,             \
            .int_src    = SPI1_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */
