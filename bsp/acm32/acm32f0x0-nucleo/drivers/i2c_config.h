/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-03     AisinoChip   the first version
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtconfig.h>
#include "board.h"


#ifdef __cplusplus
extern "C" {
#endif

#if defined(RT_USING_I2C)

#if defined(BSP_USING_I2C1)

#if defined(BSP_I2C1_RX_USING_DMA)
#ifndef I2C1_DMA_RX_CONFIG
#define I2C1_DMA_RX_CONFIG                                         \
    {                                                              \
        .Instance = I2C1_RX_DMA_INSTANCE,                          \
        .dma_rcc  = I2C1_RX_DMA_RCC,                               \
        .dma_irq  = I2C1_RX_DMA_IRQ,                               \
        .channel  = I2C1_RX_DMA_CHANNEL,                           \
        .request  = I2C1_RX_DMA_REQUEST,                           \
    }
#endif /* I2C1_DMA_RX_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#if defined(BSP_I2C1_TX_USING_DMA)
#ifndef I2C1_DMA_TX_CONFIG
#define I2C1_DMA_TX_CONFIG                                         \
    {                                                              \
        .Instance = I2C1_TX_DMA_INSTANCE,                          \
        .dma_rcc  = I2C1_TX_DMA_RCC,                               \
        .dma_irq  = I2C1_TX_DMA_IRQ,                               \
        .channel  = I2C1_TX_DMA_CHANNEL,                           \
        .request  = I2C1_TX_DMA_REQUEST,                           \
    }
#endif /* I2C1_DMA_TX_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifndef I2C1_CONFIG
#define I2C1_CONFIG                                                \
    {                                                              \
        .name = "i2c1",                                            \
        .Instance = I2C1,                                          \
        .clock_speed = CLOCK_SPEED_STANDARD,                       \
        .irq_type = I2C1_IRQn,                                     \
        .enable_id = EN_I2C1,                                      \
        .scl_port  = I2C1_SCL_PORT,                                \
        .scl_pin  = I2C1_SCL_PIN,                                  \
        .scl_alternate  = I2C1_SCL_ALTERNATE,                      \
        .sda_port  = I2C1_SDA_PORT,                                \
        .sda_pin  = I2C1_SDA_PIN,                                  \
        .sda_alternate  = I2C1_SDA_ALTERNATE,                      \
    }
#endif /* I2C1_CONFIG */
#endif /* BSP_USING_I2C1 */

#if defined(BSP_USING_I2C2)

#if defined(BSP_I2C2_RX_USING_DMA)
#ifndef I2C2_DMA_RX_CONFIG
#define I2C2_DMA_RX_CONFIG                                         \
    {                                                              \
        .Instance = I2C2_RX_DMA_INSTANCE,                          \
        .dma_rcc  = I2C2_RX_DMA_RCC,                               \
        .dma_irq  = I2C2_RX_DMA_IRQ,                               \
        .channel  = I2C2_RX_DMA_CHANNEL,                           \
        .request  = I2C2_RX_DMA_REQUEST,                           \
    }
#endif /* I2C2_DMA_RX_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

#if defined(BSP_I2C2_TX_USING_DMA)
#ifndef I2C2_DMA_TX_CONFIG
#define I2C2_DMA_TX_CONFIG                                         \
    {                                                              \
        .Instance = I2C2_TX_DMA_INSTANCE,                          \
        .dma_rcc  = I2C2_TX_DMA_RCC,                               \
        .dma_irq  = I2C2_TX_DMA_IRQ,                               \
        .channel  = I2C2_TX_DMA_CHANNEL,                           \
        .request  = I2C2_TX_DMA_REQUEST,                           \
    }
#endif /* I2C2_DMA_TX_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

#ifndef I2C2_CONFIG
#define I2C2_CONFIG                                                \
    {                                                              \
        .name = "i2c2",                                            \
        .Instance = I2C2,                                          \
        .clock_speed = CLOCK_SPEED_STANDARD,                       \
        .irq_type = I2C2_IRQn,                                     \
        .enable_id = EN_I2C2,                                      \
        .scl_port  = I2C2_SCL_PORT,                                \
        .scl_pin  = I2C2_SCL_PIN,                                  \
        .scl_alternate  = I2C2_SCL_ALTERNATE,                      \
        .sda_port  = I2C2_SDA_PORT,                                \
        .sda_pin  = I2C2_SDA_PIN,                                  \
        .sda_alternate  = I2C2_SDA_ALTERNATE,                      \
    }
#endif /* I2C2_CONFIG */
#endif /* BSP_USING_I2C2 */

#ifdef __cplusplus
}
#endif

#endif /* RT_USING_I2C */

#endif /* __I2C_CONFIG_H__ */

