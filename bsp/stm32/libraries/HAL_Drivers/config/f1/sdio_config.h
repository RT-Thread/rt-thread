/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
#include "stm32f1xx_hal.h"

#ifdef BSP_USING_SDIO
#define SDIO_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SDIO,                                \
        .dma_rx.dma_rcc = RCC_AHBENR_DMA2EN,             \
        .dma_tx.dma_rcc = RCC_AHBENR_DMA2EN,             \
        .dma_rx.Instance = DMA2_Channel4,                \
        .dma_rx.dma_irq = DMA2_Channel4_IRQn,            \
        .dma_tx.Instance = DMA2_Channel4,                \
        .dma_tx.dma_irq = DMA2_Channel4_IRQn,            \
    }

#define SPI1_DMA_RX_IRQHandler           DMA2_Channel4_IRQHandler    
#define SPI1_DMA_TX_IRQHandler           DMA2_Channel4_IRQHandler
#endif

#endif /*__SDIO_CONFIG_H__ */



