/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
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
        .name = "hwi2c1",                           \
        .Instance = I2C1,                           \
        .timeout = 0x1000,                          \
        .evirq_type = I2C1_EV_IRQn,                 \
        .erirq_type = I2C1_ER_IRQn,                 \
        .scl_af_width = 0,                          \
        .sda_af_width = 0,                          \
        .df_width = 0,                              \
        .periph = RCC_APB1_PERIPH_I2C1,             \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C1_RX_DMA,            \
        .DMAChx = I2C1_RX_DMA_CHType,   \
        .dma_irq = I2C1_RX_DMA_IRQ,     \
        .dma_rcc = I2C1_RX_DMA_RCC,     \
        .request = I2C1_RX_DMA_REQUEST, \
        .channel = I2C1_RX_DMA_CHANNEL, \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */
#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C1_TX_DMA,            \
        .DMAChx = I2C1_TX_DMA_CHType,   \
        .dma_irq = I2C1_TX_DMA_IRQ,     \
        .dma_rcc = I2C1_TX_DMA_RCC,     \
        .request = I2C1_TX_DMA_REQUEST, \
        .channel = I2C1_TX_DMA_CHANNEL, \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                             \
    {                                               \
        .name = "hwi2c2",                           \
        .Instance = I2C2,                           \
        .timeout = 0x1000,                          \
        .evirq_type = I2C2_EV_IRQn,                 \
        .erirq_type = I2C2_ER_IRQn,                 \
        .scl_af_width = 0,                          \
        .sda_af_width = 0,                          \
        .df_width = 0,                              \
        .periph = RCC_APB1_PERIPH_I2C2,             \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C2_RX_DMA,            \
        .DMAChx = I2C2_RX_DMA_CHType,   \
        .dma_irq = I2C2_RX_DMA_IRQ,     \
        .dma_rcc = I2C2_RX_DMA_RCC,     \
        .request = I2C2_RX_DMA_REQUEST, \
        .channel = I2C2_RX_DMA_CHANNEL, \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */
#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C2_TX_DMA,            \
        .DMAChx = I2C2_TX_DMA_CHType,   \
        .dma_irq = I2C2_TX_DMA_IRQ,     \
        .dma_rcc = I2C2_TX_DMA_RCC,     \
        .request = I2C2_TX_DMA_REQUEST, \
        .channel = I2C2_TX_DMA_CHANNEL, \
    }
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG                             \
    {                                               \
        .name = "hwi2c3",                           \
        .Instance = I2C3,                           \
        .timeout = 0x1000,                          \
        .evirq_type = I2C3_EV_IRQn,                 \
        .erirq_type = I2C3_ER_IRQn,                 \
        .scl_af_width = 0,                          \
        .sda_af_width = 0,                          \
        .df_width = 0,                              \
        .periph = RCC_APB1_PERIPH_I2C3,             \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C3 */
#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C3_RX_DMA,            \
        .DMAChx = I2C3_RX_DMA_CHType,   \
        .dma_irq = I2C3_RX_DMA_IRQ,     \
        .dma_rcc = I2C3_RX_DMA_RCC,     \
        .request = I2C3_RX_DMA_REQUEST, \
        .channel = I2C3_RX_DMA_CHANNEL, \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */
#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C3_TX_DMA,            \
        .DMAChx = I2C3_TX_DMA_CHType,   \
        .dma_irq = I2C3_TX_DMA_IRQ,     \
        .dma_rcc = I2C3_TX_DMA_RCC,     \
        .request = I2C3_TX_DMA_REQUEST, \
        .channel = I2C3_TX_DMA_CHANNEL, \
    }
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C4
#ifndef I2C4_BUS_CONFIG
#define I2C4_BUS_CONFIG                             \
    {                                               \
        .name = "hwi2c4",                           \
        .Instance = I2C4,                           \
        .timeout = 0x1000,                          \
        .evirq_type = I2C4_EV_IRQn,                 \
        .erirq_type = I2C4_ER_IRQn,                 \
        .scl_af_width = 0,                          \
        .sda_af_width = 0,                          \
        .df_width = 0,                              \
        .periph = RCC_APB1_PERIPH_I2C4,             \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk, \
    }
#endif /* I2C4_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C4 */
#ifdef BSP_I2C4_RX_USING_DMA
#ifndef I2C4_RX_DMA_CONFIG
#define I2C4_RX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C4_RX_DMA,            \
        .DMAChx = I2C4_RX_DMA_CHType,   \
        .dma_irq = I2C4_RX_DMA_IRQ,     \
        .dma_rcc = I2C4_RX_DMA_RCC,     \
        .request = I2C4_RX_DMA_REQUEST, \
        .channel = I2C4_RX_DMA_CHANNEL, \
    }
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_RX_USING_DMA */
#ifdef BSP_I2C4_TX_USING_DMA
#ifndef I2C4_TX_DMA_CONFIG
#define I2C4_TX_DMA_CONFIG              \
    {                                   \
        .DMAy = I2C4_TX_DMA,            \
        .DMAChx = I2C4_TX_DMA_CHType,   \
        .dma_irq = I2C4_TX_DMA_IRQ,     \
        .dma_rcc = I2C4_TX_DMA_RCC,     \
        .request = I2C4_TX_DMA_REQUEST, \
        .channel = I2C4_TX_DMA_CHANNEL, \
    }
#endif /* I2C4_TX_DMA_CONFIG */
#endif /* BSP_I2C4_TX_USING_DMA */

#ifdef __cplusplus
}

#endif

#endif /*__I2C_HARD_CONFIG_H__ */
