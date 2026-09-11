/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     BalanceTWK   first version
 */

#ifndef __SDIO_CONFIG_H__
#define __SDIO_CONFIG_H__

#include <rtthread.h>
#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SDIO
#define SDIO_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SDMMC1,                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Stream3,                 \
        .dma_rx.channel = DMA_CHANNEL_4,                 \
        .dma_rx.dma_irq = DMA2_Stream3_IRQn,             \
        .dma_tx.Instance = DMA2_Stream6,                 \
        .dma_tx.channel = DMA_CHANNEL_4,                 \
        .dma_tx.dma_irq = DMA2_Stream6_IRQn,             \
    }

#endif

#ifdef __cplusplus
}
#endif

#endif /*__SDIO_CONFIG_H__ */



