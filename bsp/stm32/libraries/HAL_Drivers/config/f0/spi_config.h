/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SPI1
#define SPI1_BUS_CONFIG                                  \
    {                                                    \
        .Instance = SPI1,                                \
        .bus_name = "spi1",                              \
        .dma_rx.dma_rcc = RCC_AHBENR_DMA1EN,             \
        .dma_tx.dma_rcc = RCC_AHBENR_DMA1EN,             \
        .dma_rx.Instance = DMA1_Channel2,                \
        .dma_rx.dma_irq = DMA1_Ch2_3_DMA2_Ch1_2_IRQn,    \
        .dma_tx.Instance = DMA1_Channel3,                \
        .dma_tx.dma_irq = DMA1_Ch2_3_DMA2_Ch1_2_IRQn,    \
    }

#define SPI1_DMA_RX_IRQHandler           DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler    
#define SPI1_DMA_TX_IRQHandler           DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#endif

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */



