/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-06     Dyyt587   first version
 * 2024-04-23     Zeidan    Add I2Cx_xx_DMA_CONFIG
 * 2024-06-23     wdfk-prog Removes timing
 */
#ifndef __I2C_HARD_CONFIG_H__
#define __I2C_HARD_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_HARD_I2C1
#ifndef I2C1_BUS_CONFIG
#define I2C1_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C1,                           \
        .timeout = 1000,                            \
        .name = "hwi2c1",                           \
        .evirq_type = I2C1_EV_IRQn,                 \
        .erirq_type = I2C1_ER_IRQn,                 \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C1 */

#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_TX_DMA_RCC,                 \
        .Instance = I2C1_TX_DMA_INSTANCE,           \
        .dma_irq = I2C1_TX_DMA_IRQ,                 \
        .channel = I2C1_TX_DMA_CHANNEL              \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_TX_DMA_RCC,                 \
        .Instance = I2C1_TX_DMA_INSTANCE,           \
        .dma_irq = I2C1_TX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C1_TX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_RX_DMA_RCC,                 \
        .Instance = I2C1_RX_DMA_INSTANCE,           \
        .dma_irq = I2C1_RX_DMA_IRQ,                 \
        .channel = I2C1_RX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C1_RX_DMA_RCC,                 \
        .Instance = I2C1_RX_DMA_INSTANCE,           \
        .dma_irq = I2C1_RX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C1_RX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C2,                           \
        .timeout = 1000,                            \
        .name = "hwi2c2",                           \
        .evirq_type = I2C2_EV_IRQn,                 \
        .erirq_type = I2C2_ER_IRQn,                 \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C2 */

#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C2_TX_DMA_RCC,                 \
        .Instance = I2C2_TX_DMA_INSTANCE,           \
        .dma_irq = I2C2_TX_DMA_IRQ,                 \
        .channel = I2C2_TX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C2_TX_DMA_RCC,                 \
        .Instance = I2C2_TX_DMA_INSTANCE,           \
        .dma_irq = I2C2_TX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C2_TX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C2_RX_DMA_RCC,                 \
        .Instance = I2C2_RX_DMA_INSTANCE,           \
        .dma_irq = I2C2_RX_DMA_IRQ,                 \
        .channel = I2C2_RX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C2_RX_DMA_RCC,                 \
        .Instance = I2C2_RX_DMA_INSTANCE,           \
        .dma_irq = I2C2_RX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C2_RX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C3,                           \
        .timeout = 1000,                            \
        .name = "hwi2c3",                           \
        .evirq_type = I2C3_EV_IRQn,                 \
        .erirq_type = I2C3_ER_IRQn,                 \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C3 */

#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C3_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_TX_DMA_RCC,                 \
        .Instance = I2C3_TX_DMA_INSTANCE,           \
        .dma_irq = I2C3_TX_DMA_IRQ,                 \
        .channel = I2C3_TX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C3_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_TX_DMA_RCC,                 \
        .Instance = I2C3_TX_DMA_INSTANCE,           \
        .dma_irq = I2C3_TX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C3_TX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */

#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C3_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_RX_DMA_RCC,                 \
        .Instance = I2C3_RX_DMA_INSTANCE,           \
        .dma_irq = I2C3_RX_DMA_IRQ,                 \
        .channel = I2C3_RX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C3_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C3_RX_DMA_RCC,                 \
        .Instance = I2C3_RX_DMA_INSTANCE,           \
        .dma_irq = I2C3_RX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C3_RX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C4
#ifndef I2C4_BUS_CONFIG
#define I2C4_BUS_CONFIG                             \
    {                                               \
        .Instance = I2C4,                           \
        .timeout = 1000,                            \
        .name = "hwi2c4",                           \
        .evirq_type = I2C4_EV_IRQn,                 \
        .erirq_type = I2C4_ER_IRQn,                 \
    }
#endif /* I2C4_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C4 */

#ifdef BSP_I2C4_TX_USING_DMA
#ifndef I2C4_TX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C4_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C4_TX_DMA_RCC,                 \
        .Instance = I2C4_TX_DMA_INSTANCE,           \
        .dma_irq = I2C4_TX_DMA_IRQ,                 \
        .channel = I2C4_TX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C4_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C4_TX_DMA_RCC,                 \
        .Instance = I2C4_TX_DMA_INSTANCE,           \
        .dma_irq = I2C4_TX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C4_TX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C4_TX_DMA_CONFIG */
#endif /* BSP_I2C4_TX_USING_DMA */

#ifdef BSP_I2C4_RX_USING_DMA
#ifndef I2C4_RX_DMA_CONFIG
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define I2C4_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C4_RX_DMA_RCC,                 \
        .Instance = I2C4_RX_DMA_INSTANCE,           \
        .dma_irq = I2C4_RX_DMA_IRQ,                 \
        .channel = I2C4_RX_DMA_CHANNEL,             \
    }
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
#define I2C4_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = I2C4_RX_DMA_RCC,                 \
        .Instance = I2C4_RX_DMA_INSTANCE,           \
        .dma_irq = I2C4_RX_DMA_IRQ,                 \
        .request = DMA_REQUEST_I2C4_RX              \
    }
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_RX_USING_DMA */


#ifdef __cplusplus
}
#endif

#endif /*__I2C_CONFIG_H__ */