/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-22     Donocean     first version
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_I2C1
#ifndef I2C1_BUS_CONFIG
#define I2C1_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C1,                           \
        .bus_name = "i2c1",                         \
        .irq_type = I2C1_EV_IRQn,                   \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_I2C1 */

#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_TX_DMA_RCC,                 \
        .Instance = I2C1_TX_DMA_INSTANCE,           \
        .channel = I2C1_TX_DMA_CHANNEL,             \
        .dma_irq = I2C1_TX_DMA_IRQ,                 \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_RX_DMA_RCC,                 \
        .Instance = I2C1_RX_DMA_INSTANCE,           \
        .channel = I2C1_RX_DMA_CHANNEL,             \
        .dma_irq = I2C1_RX_DMA_IRQ,                 \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef BSP_USING_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C2,                           \
        .bus_name = "i2c2",                         \
        .irq_type = I2C2_EV_IRQn,                   \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_I2C2 */

#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C2_TX_DMA_RCC,                 \
        .Instance = I2C2_TX_DMA_INSTANCE,           \
        .channel = I2C2_TX_DMA_CHANNEL,             \
        .dma_irq = I2C2_TX_DMA_IRQ,                 \
    }
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI2_RX_DMA_RCC,                 \
        .Instance = SPI2_RX_DMA_INSTANCE,           \
        .channel = SPI2_RX_DMA_CHANNEL,             \
        .dma_irq = SPI2_RX_DMA_IRQ,                 \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

#ifdef BSP_USING_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C3,                           \
        .bus_name = "i2c3",                         \
        .irq_type = I2C3_EV_IRQn,                   \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_I2C3 */

#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_TX_DMA_RCC,                 \
        .Instance = I2C3_TX_DMA_INSTANCE,           \
        .channel = I2C3_TX_DMA_CHANNEL,             \
        .dma_irq = I2C3_TX_DMA_IRQ,                 \
    }
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */

#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_RX_DMA_RCC,                 \
        .Instance = I2C3_RX_DMA_INSTANCE,           \
        .channel = I2C3_RX_DMA_CHANNEL,             \
        .dma_irq = I2C3_RX_DMA_IRQ,                 \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */
