/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

#ifndef __SDIO_CONFIG_H__
#define __SDIO_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(BSP_USING_SDIO1)
#ifndef SDIO1_BUS_CONFIG
#define SDIO1_BUS_CONFIG                                        \
    {                                                           \
        .name       = "sdio1",                                  \
        .instance   = CM_SDIOC1,                                \
        .clock      = FCG1_PERIPH_SDIOC1,                       \
        .irq_config =                                           \
        {                                                       \
            .irq_num  = BSP_SDIO1_IRQ_NUM,                      \
            .irq_prio = BSP_SDIO1_IRQ_PRIO,                     \
            .int_src  = INT_SRC_SDIOC1_SD,                      \
        },                                                      \
        .dma_rx =                                               \
        {                                                       \
            .Instance       = SDIO1_RX_DMA_INSTANCE,            \
            .channel        = SDIO1_RX_DMA_CHANNEL,             \
            .clock          = SDIO1_RX_DMA_CLOCK,               \
            .trigger_select = SDIO1_RX_DMA_TRIG_SELECT,         \
            .trigger_event  = EVT_SRC_SDIOC1_DMAR,              \
        },                                                      \
        .dma_tx =                                               \
        {                                                       \
            .Instance       = SDIO1_TX_DMA_INSTANCE,            \
            .channel        = SDIO1_TX_DMA_CHANNEL,             \
            .clock          = SDIO1_TX_DMA_CLOCK,               \
            .trigger_select = SDIO1_TX_DMA_TRIG_SELECT,         \
            .trigger_event  = EVT_SRC_SDIOC1_DMAW,              \
        },                                                      \
    }
#endif /* SDIO1_BUS_CONFIG */
#endif /* BSP_USING_SDIO1 */

#if defined(BSP_USING_SDIO2)
#ifndef SDIO2_BUS_CONFIG
#define SDIO2_BUS_CONFIG                                        \
    {                                                           \
        .name       = "sdio2",                                  \
        .instance   = CM_SDIOC2,                                \
        .clock      = FCG1_PERIPH_SDIOC2,                       \
        .irq_config =                                           \
        {                                                       \
            .irq_num  = BSP_SDIO2_IRQ_NUM,                      \
            .irq_prio = BSP_SDIO2_IRQ_PRIO,                     \
            .int_src  = INT_SRC_SDIOC2_SD,                      \
        },                                                      \
        .dma_rx =                                               \
        {                                                       \
            .Instance       = SDIO2_RX_DMA_INSTANCE,            \
            .channel        = SDIO2_RX_DMA_CHANNEL,             \
            .clock          = SDIO2_RX_DMA_CLOCK,               \
            .trigger_select = SDIO2_RX_DMA_TRIG_SELECT,         \
            .trigger_event  = EVT_SRC_SDIOC2_DMAR,              \
        },                                                      \
        .dma_tx =                                               \
        {                                                       \
            .Instance       = SDIO2_TX_DMA_INSTANCE,            \
            .channel        = SDIO2_TX_DMA_CHANNEL,             \
            .clock          = SDIO2_TX_DMA_CLOCK,               \
            .trigger_select = SDIO2_TX_DMA_TRIG_SELECT,         \
            .trigger_event  = EVT_SRC_SDIOC2_DMAW,              \
        },                                                      \
    }
#endif /* SDIO2_BUS_CONFIG */
#endif /* BSP_USING_SDIO2 */

#ifdef __cplusplus
}
#endif

#endif
