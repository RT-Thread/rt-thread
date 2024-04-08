/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                             \
    {                                               \
        .Instance = SPI1,                           \
        .bus_name = "spi1",                         \
        .irq_type = SPI1_IRQn,                      \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI1_TX_DMA_RCC,                 \
        .Instance = SPI1_TX_DMA_INSTANCE,           \
        .request = SPI1_TX_DMA_CHANNEL,             \
        .dma_irq = SPI1_TX_DMA_IRQ,                 \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI1_RX_DMA_RCC,                 \
        .Instance = SPI1_RX_DMA_INSTANCE,           \
        .request = SPI1_RX_DMA_CHANNEL,             \
        .dma_irq = SPI1_RX_DMA_IRQ,                 \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                             \
    {                                               \
        .Instance = SPI2,                           \
        .bus_name = "spi2",                         \
        .irq_type = SPI2_IRQn,                      \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI2_TX_DMA_RCC,                 \
        .Instance = SPI2_TX_DMA_INSTANCE,           \
        .request = SPI2_TX_DMA_CHANNEL,             \
        .dma_irq = SPI2_TX_DMA_IRQ,                 \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI2_RX_DMA_RCC,                 \
        .Instance = SPI2_RX_DMA_INSTANCE,           \
        .request = SPI2_RX_DMA_CHANNEL,             \
        .dma_irq = SPI2_RX_DMA_IRQ,                 \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                             \
    {                                               \
        .Instance = SPI3,                           \
        .bus_name = "spi3",                         \
        .irq_type = SPI3_IRQn,                      \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_SPI3_TX_USING_DMA
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI3_TX_DMA_RCC,                 \
        .Instance = SPI3_TX_DMA_INSTANCE,           \
        .request = SPI3_TX_DMA_CHANNEL,             \
        .dma_irq = SPI3_TX_DMA_IRQ,                 \
    }
#endif /* SPI3_TX_DMA_CONFIG */
#endif /* BSP_SPI3_TX_USING_DMA */

#ifdef BSP_SPI3_RX_USING_DMA
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI3_RX_DMA_RCC,                 \
        .Instance = SPI3_RX_DMA_INSTANCE,           \
        .request = SPI3_RX_DMA_CHANNEL,             \
        .dma_irq = SPI3_RX_DMA_IRQ,                 \
    }
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_RX_USING_DMA */

#ifdef BSP_USING_SPI4
#ifndef SPI4_BUS_CONFIG
#define SPI4_BUS_CONFIG                             \
    {                                               \
        .Instance = SPI4,                           \
        .bus_name = "spi4",                         \
        .irq_type = SPI4_IRQn,                      \
    }
#endif /* SPI4_BUS_CONFIG */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_SPI4_TX_USING_DMA
#ifndef SPI4_TX_DMA_CONFIG
#define SPI4_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI4_TX_DMA_RCC,                 \
        .Instance = SPI4_TX_DMA_INSTANCE,           \
        .request = SPI4_TX_DMA_CHANNEL,             \
        .dma_irq = SPI4_TX_DMA_IRQ,                 \
    }
#endif /* SPI4_TX_DMA_CONFIG */
#endif /* BSP_SPI4_TX_USING_DMA */

#ifdef BSP_SPI4_RX_USING_DMA
#ifndef SPI4_RX_DMA_CONFIG
#define SPI4_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI4_RX_DMA_RCC,                 \
        .Instance = SPI4_RX_DMA_INSTANCE,           \
        .request = SPI4_RX_DMA_CHANNEL,             \
        .dma_irq = SPI4_RX_DMA_IRQ,                 \
    }
#endif /* SPI4_RX_DMA_CONFIG */
#endif /* BSP_SPI4_RX_USING_DMA */

#ifdef BSP_USING_SPI5
#ifndef SPI5_BUS_CONFIG
#define SPI5_BUS_CONFIG                             \
    {                                               \
        .Instance = SPI5,                           \
        .bus_name = "spi5",                         \
        .irq_type = SPI5_IRQn,                      \
    }
#endif /* SPI5_BUS_CONFIG */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_SPI5_TX_USING_DMA
#ifndef SPI5_TX_DMA_CONFIG
#define SPI5_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI5_TX_DMA_RCC,                 \
        .Instance = SPI5_TX_DMA_INSTANCE,           \
        .request = SPI5_TX_DMA_CHANNEL,             \
        .dma_irq = SPI5_TX_DMA_IRQ,                 \
    }
#endif /* SPI5_TX_DMA_CONFIG */
#endif /* BSP_SPI5_TX_USING_DMA */

#ifdef BSP_SPI5_RX_USING_DMA
#ifndef SPI5_RX_DMA_CONFIG
#define SPI5_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI5_RX_DMA_RCC,                 \
        .Instance = SPI5_RX_DMA_INSTANCE,           \
        .request = SPI5_RX_DMA_CHANNEL,             \
        .dma_irq = SPI5_RX_DMA_IRQ,                 \
    }
#endif /* SPI5_RX_DMA_CONFIG */
#endif /* BSP_SPI5_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */
