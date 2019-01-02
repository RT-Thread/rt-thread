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
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Stream2,                 \
        .dma_rx.channel = DMA_CHANNEL_3,                 \
        .dma_rx.dma_irq = DMA2_Stream2_IRQn,             \
        .dma_tx.Instance = DMA2_Stream3,                 \
        .dma_tx.channel = DMA_CHANNEL_3,                 \
        .dma_tx.dma_irq = DMA2_Stream3_IRQn,             \
    }

#define SPI1_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler    
#define SPI1_DMA_TX_IRQHandler           DMA2_Stream3_IRQHandler
#endif

#ifdef BSP_USING_SPI2
#define SPI2_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI2,                                \
        .bus_name = "spi2",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_rx.Instance = DMA1_Stream3,                 \
        .dma_rx.channel = DMA_CHANNEL_0,                 \
        .dma_rx.dma_irq = DMA1_Stream3_IRQn,             \
        .dma_tx.Instance = DMA1_Stream4,                 \
        .dma_tx.channel = DMA_CHANNEL_0,                 \
        .dma_tx.dma_irq = DMA1_Stream4_IRQn,             \
    }

#define SPI2_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler    
#define SPI2_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#endif

#ifdef BSP_USING_SPI3
#define SPI3_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI3,                                \
        .bus_name = "spi3",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA1EN,            \
        .dma_rx.Instance = DMA1_Stream0,                 \
        .dma_rx.channel = DMA_CHANNEL_0,                 \
        .dma_rx.dma_irq = DMA1_Stream0_IRQn,             \
        .dma_tx.Instance = DMA1_Stream7,                 \
        .dma_tx.channel = DMA_CHANNEL_0,                 \
        .dma_tx.dma_irq = DMA1_Stream7_IRQn,             \
    }

#define SPI3_DMA_RX_IRQHandler           DMA1_Stream0_IRQHandler    
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream7_IRQHandler
#endif

#ifdef BSP_USING_SPI4
#define SPI4_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI4,                                \
        .bus_name = "spi4",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Stream0,                 \
        .dma_rx.channel = DMA_CHANNEL_4,                 \
        .dma_rx.dma_irq = DMA2_Stream0_IRQn,             \
        .dma_tx.Instance = DMA2_Stream1,                 \
        .dma_tx.channel = DMA_CHANNEL_4,                 \
        .dma_tx.dma_irq = DMA2_Stream1_IRQn,             \
    }

#define SPI4_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler    
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#endif

#ifdef BSP_USING_SPI5
#define SPI5_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI5,                                \
        .bus_name = "spi5",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Stream3,                 \
        .dma_rx.channel = DMA_CHANNEL_2,                 \
        .dma_rx.dma_irq = DMA2_Stream3_IRQn,             \
        .dma_tx.Instance = DMA2_Stream4,                 \
        .dma_tx.channel = DMA_CHANNEL_2,                 \
        .dma_tx.dma_irq = DMA2_Stream4_IRQn,             \
    }

#define SPI5_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler    
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#endif

#ifdef BSP_USING_SPI6
#define SPI5_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI6,                                \
        .bus_name = "spi6",                              \
        .dma_rx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_tx.dma_rcc = RCC_AHB1ENR_DMA2EN,            \
        .dma_rx.Instance = DMA2_Stream6,                 \
        .dma_rx.channel = DMA_CHANNEL_1,                 \
        .dma_rx.dma_irq = DMA2_Stream6_IRQn,             \
        .dma_tx.Instance = DMA2_Stream5,                 \
        .dma_tx.channel = DMA_CHANNEL_1,                 \
        .dma_tx.dma_irq = DMA2_Stream5_IRQn,             \
    }

#define SPI6_DMA_RX_IRQHandler           DMA2_Stream6_IRQHandler    
#define SPI6_DMA_TX_IRQHandler           DMA2_Stream5_IRQHandler
#endif

#endif /*__SPI_CONFIG_H__ */



