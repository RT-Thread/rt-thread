/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     shelton      first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPI1_IRQHandler      SPI1_IRQHandler
#define SPI2_IRQHandler      SPI2_IRQHandler

#ifdef BSP_USING_SPI1
#define SPI1_CONFIG                                 \
    {                                               \
        .spi_x = SPI1,                              \
        .spi_name = "spi1",                         \
        .irqn = SPI1_IRQn,                          \
    }
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_RX_USING_DMA
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = SPI1_RX_DMA_CHANNEL,         \
        .dma_clock = SPI1_RX_DMA_CLOCK,             \
        .dma_irqn = SPI1_RX_DMA_IRQ,                \
        .dmamux_channel = SPI1_RX_DMA_MUX_CHANNEL,  \
        .request_id = SPI1_RX_DMA_REQ_ID,           \
    }
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_SPI1_TX_USING_DMA
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = SPI1_TX_DMA_CHANNEL,         \
        .dma_clock = SPI1_TX_DMA_CLOCK,             \
        .dma_irqn = SPI1_TX_DMA_IRQ,                \
        .dmamux_channel = SPI1_TX_DMA_MUX_CHANNEL,  \
        .request_id = SPI1_TX_DMA_REQ_ID,           \
    }
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_USING_SPI2
#define SPI2_CONFIG                                 \
    {                                               \
        .spi_x = SPI2,                              \
        .spi_name = "spi2",                         \
        .irqn = SPI2_IRQn,                          \
    }
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_RX_USING_DMA
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = SPI2_RX_DMA_CHANNEL,         \
        .dma_clock = SPI2_RX_DMA_CLOCK,             \
        .dma_irqn = SPI2_RX_DMA_IRQ,                \
        .dmamux_channel = SPI2_RX_DMA_MUX_CHANNEL,  \
        .request_id = SPI2_RX_DMA_REQ_ID,           \
    }
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_SPI2_TX_USING_DMA
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = SPI2_TX_DMA_CHANNEL,         \
        .dma_clock = SPI2_TX_DMA_CLOCK,             \
        .dma_irqn = SPI2_TX_DMA_IRQ,                \
        .dmamux_channel = SPI2_TX_DMA_MUX_CHANNEL,  \
        .request_id = SPI2_TX_DMA_REQ_ID,           \
    }
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */



