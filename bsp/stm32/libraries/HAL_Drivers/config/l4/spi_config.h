/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   change to new framework
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef BSP_USING_SPI1
#define SPI1_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI1,                                \
        .bus_name = "spi1",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_rx.Instance = DMA1_Channel2,                \
        .dma_rx.request = DMA_REQUEST_1,                 \
        .dma_rx.dma_irq = DMA1_Channel2_IRQn,            \
        .dma_tx.Instance = DMA1_Channel3,                \
        .dma_tx.request = DMA_REQUEST_1,                 \
        .dma_tx.dma_irq = DMA1_Channel3_IRQn,            \
    }
#define SPI1_DMA_RX_IRQHandler           DMA1_Channel2_IRQHandler
#define SPI1_DMA_TX_IRQHandler           DMA1_Channel3_IRQHandler
#endif

#ifdef BSP_USING_SPI2
#define SPI2_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI2,                                \
        .bus_name = "spi2",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_rx.Instance = DMA1_Channel4,                \
        .dma_rx.request = DMA_REQUEST_1,                 \
        .dma_rx.dma_irq = DMA1_Channel4_IRQn,            \
        .dma_tx.Instance = DMA1_Channel5,                \
        .dma_tx.request = DMA_REQUEST_1,                 \
        .dma_tx.dma_irq = DMA1_Channel5_IRQn,            \
    }
#define SPI2_DMA_RX_IRQHandler           DMA1_Channel4_IRQHandler
#define SPI2_DMA_TX_IRQHandler           DMA1_Channel5_IRQHandler
#endif

#ifdef BSP_USING_SPI3
#define SPI3_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI3,                                \
        .bus_name = "spi3",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Channel1,                \
        .dma_rx.request = DMA_REQUEST_3,                 \
        .dma_rx.dma_irq = DMA2_Channel1_IRQn,            \
        .dma_tx.Instance = DMA2_Channel2,                \
        .dma_tx.request = DMA_REQUEST_3,                 \
        .dma_tx.dma_irq = DMA2_Channel2_IRQn,            \
    }
#define SPI3_DMA_RX_IRQHandler           DMA2_Channel1_IRQHandler
#define SPI3_DMA_TX_IRQHandler           DMA2_Channel2_IRQHandler
#endif

#endif /*__SPI_CONFIG_H__ */
