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
#define I2C1_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c1",                   \
        .Instance        = I2C1,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C1_EV_IRQn,               \
        .erirq_type      = I2C1_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB1_PERIPHEN_M7_I2C1,  \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk4,   \
        .I2CKerClkSource = RCC_ConfigI2C1KerClkSource, \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C1_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C1_RX_DMA_IRQ,             \
        .HsInterface    = I2C1_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C1_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C1_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C1_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C1_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */
#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C1_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C1_TX_DMA_IRQ,             \
        .HsInterface    = I2C1_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C1_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C1_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C1_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C1_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c2",                   \
        .Instance        = I2C2,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C2_EV_IRQn,               \
        .erirq_type      = I2C2_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB1_PERIPHEN_M7_I2C2,  \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk4,   \
        .I2CKerClkSource = RCC_ConfigI2C2KerClkSource, \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C2_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C2_RX_DMA_IRQ,             \
        .HsInterface    = I2C2_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C2_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C2_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C2_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C2_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */
#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C2_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C2_TX_DMA_IRQ,             \
        .HsInterface    = I2C2_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C2_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C2_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C2_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C2_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c3",                   \
        .Instance        = I2C3,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C3_EV_IRQn,               \
        .erirq_type      = I2C3_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB1_PERIPHEN_M7_I2C3,  \
        .EnablePeriphClk = RCC_EnableAPB1PeriphClk4,   \
        .I2CKerClkSource = RCC_ConfigI2C3KerClkSource, \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C3 */
#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C3_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C3_RX_DMA_IRQ,             \
        .HsInterface    = I2C3_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C3_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C3_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C3_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C3_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */
#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C3_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C3_TX_DMA_IRQ,             \
        .HsInterface    = I2C3_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C3_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C3_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C3_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C3_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C4
#ifndef I2C4_BUS_CONFIG
#define I2C4_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c4",                   \
        .Instance        = I2C4,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C4_EV_IRQn,               \
        .erirq_type      = I2C4_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB2_PERIPHEN_M7_I2C4,  \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C4KerClkSource, \
    }
#endif /* I2C4_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C4 */
#ifdef BSP_I2C4_RX_USING_DMA
#ifndef I2C4_RX_DMA_CONFIG
#define I2C4_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C4_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C4_RX_DMA_IRQ,             \
        .HsInterface    = I2C4_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C4_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C4_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C4_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C4_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_RX_USING_DMA */
#ifdef BSP_I2C4_TX_USING_DMA
#ifndef I2C4_TX_DMA_CONFIG
#define I2C4_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C4_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C4_TX_DMA_IRQ,             \
        .HsInterface    = I2C4_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C4_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C4_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C4_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C4_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C4_TX_DMA_CONFIG */
#endif /* BSP_I2C4_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C5
#ifndef I2C5_BUS_CONFIG
#define I2C5_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c5",                   \
        .Instance        = I2C5,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C5_EV_IRQn,               \
        .erirq_type      = I2C5_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB2_PERIPHEN_M7_I2C5,  \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C5KerClkSource, \
    }
#endif /* I2C5_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C5 */
#ifdef BSP_I2C5_RX_USING_DMA
#ifndef I2C5_RX_DMA_CONFIG
#define I2C5_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C5_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C5_RX_DMA_IRQ,             \
        .HsInterface    = I2C5_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C5_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C5_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C5_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C5_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C5_RX_DMA_CONFIG */
#endif /* BSP_I2C5_RX_USING_DMA */
#ifdef BSP_I2C5_TX_USING_DMA
#ifndef I2C5_TX_DMA_CONFIG
#define I2C5_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C5_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C5_TX_DMA_IRQ,             \
        .HsInterface    = I2C5_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C5_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C5_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C5_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C5_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C5_TX_DMA_CONFIG */
#endif /* BSP_I2C5_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C6
#ifndef I2C6_BUS_CONFIG
#define I2C6_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c6",                   \
        .Instance        = I2C6,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C6_EV_IRQn,               \
        .erirq_type      = I2C6_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB2_PERIPHEN_M7_I2C6,  \
        .EnablePeriphClk = RCC_EnableAPB2PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C6KerClkSource, \
    }
#endif /* I2C6_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C6 */
#ifdef BSP_I2C6_RX_USING_DMA
#ifndef I2C6_RX_DMA_CONFIG
#define I2C6_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C6_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C6_RX_DMA_IRQ,             \
        .HsInterface    = I2C6_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C6_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C6_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C6_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C6_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C6_RX_DMA_CONFIG */
#endif /* BSP_I2C6_RX_USING_DMA */
#ifdef BSP_I2C6_TX_USING_DMA
#ifndef I2C6_TX_DMA_CONFIG
#define I2C6_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C6_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C6_TX_DMA_IRQ,             \
        .HsInterface    = I2C6_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C6_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C6_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C6_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C6_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C6_TX_DMA_CONFIG */
#endif /* BSP_I2C6_TX_USING_DMA */

#ifdef BSP_USING_HARD_I2C7
#ifndef I2C7_BUS_CONFIG
#define I2C7_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c7",                   \
        .Instance        = I2C7,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C7_EV_IRQn,               \
        .erirq_type      = I2C7_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB5_PERIPHEN_M7_I2C7,  \
        .EnablePeriphClk = RCC_EnableAPB5PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C7KerClkSource, \
    }
#endif /* I2C7_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C7 */
#ifdef BSP_I2C7_RX_USING_DMA
#ifndef I2C7_RX_DMA_CONFIG
#define I2C7_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C7_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C7_RX_DMA_IRQ,             \
        .HsInterface    = I2C7_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C7_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C7_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C7_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C7_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C7_RX_DMA_CONFIG */
#endif /* BSP_I2C7_RX_USING_DMA */
#ifdef BSP_I2C7_TX_USING_DMA
#ifndef I2C7_TX_DMA_CONFIG
#define I2C7_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C7_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C7_TX_DMA_IRQ,             \
        .HsInterface    = I2C7_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C7_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C7_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C7_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C7_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C7_TX_DMA_CONFIG */
#endif /* BSP_I2C7_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C8
#ifndef I2C8_BUS_CONFIG
#define I2C8_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c8",                   \
        .Instance        = I2C8,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C8_EV_IRQn,               \
        .erirq_type      = I2C8_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB5_PERIPHEN_M7_I2C8,  \
        .EnablePeriphClk = RCC_EnableAPB5PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C8KerClkSource, \
    }
#endif /* I2C8_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C8 */
#ifdef BSP_I2C8_RX_USING_DMA
#ifndef I2C8_RX_DMA_CONFIG
#define I2C8_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C8_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C8_RX_DMA_IRQ,             \
        .HsInterface    = I2C8_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C8_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C8_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C8_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C8_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C8_RX_DMA_CONFIG */
#endif /* BSP_I2C8_RX_USING_DMA */
#ifdef BSP_I2C8_TX_USING_DMA
#ifndef I2C8_TX_DMA_CONFIG
#define I2C8_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C8_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C8_TX_DMA_IRQ,             \
        .HsInterface    = I2C8_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C8_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C8_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C8_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C8_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C8_TX_DMA_CONFIG */
#endif /* BSP_I2C8_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C9
#ifndef I2C9_BUS_CONFIG
#define I2C9_BUS_CONFIG                                \
    {                                                  \
        .name            = "hwi2c9",                   \
        .Instance        = I2C9,                       \
        .timing          = 0x50012526,                 \
        .timeout         = 0x1000,                     \
        .evirq_type      = I2C9_EV_IRQn,               \
        .erirq_type      = I2C9_ER_IRQn,               \
        .scl_af_width    = 0,                          \
        .sda_af_width    = 0,                          \
        .df_width        = 0,                          \
        .periph          = RCC_APB5_PERIPHEN_M7_I2C9,  \
        .EnablePeriphClk = RCC_EnableAPB5PeriphClk2,   \
        .I2CKerClkSource = RCC_ConfigI2C9KerClkSource, \
    }
#endif /* I2C9_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C9 */
#ifdef BSP_I2C9_RX_USING_DMA
#ifndef I2C9_RX_DMA_CONFIG
#define I2C9_RX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C9_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C9_RX_DMA_IRQ,             \
        .HsInterface    = I2C9_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C9_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C9_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C9_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C9_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C9_RX_DMA_CONFIG */
#endif /* BSP_I2C9_RX_USING_DMA */
#ifdef BSP_I2C9_TX_USING_DMA
#ifndef I2C9_TX_DMA_CONFIG
#define I2C9_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C9_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C9_TX_DMA_IRQ,             \
        .HsInterface    = I2C9_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C9_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C9_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C9_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C9_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C9_TX_DMA_CONFIG */
#endif /* BSP_I2C9_TX_USING_DMA */


#ifdef BSP_USING_HARD_I2C10
#ifndef I2C10_BUS_CONFIG
#define I2C10_BUS_CONFIG                                \
    {                                                   \
        .name            = "hwi2c10",                   \
        .Instance        = I2C10,                       \
        .timing          = 0x50012526,                  \
        .timeout         = 0x1000,                      \
        .evirq_type      = I2C10_EV_IRQn,               \
        .erirq_type      = I2C10_ER_IRQn,               \
        .scl_af_width    = 0,                           \
        .sda_af_width    = 0,                           \
        .df_width        = 0,                           \
        .periph          = RCC_APB5_PERIPHEN_M7_I2C10,  \
        .EnablePeriphClk = RCC_EnableAPB5PeriphClk2,    \
        .I2CKerClkSource = RCC_ConfigI2C10KerClkSource, \
    }
#endif /* I2C10_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C10 */
#ifdef BSP_I2C10_RX_USING_DMA
#ifndef I2C10_RX_DMA_CONFIG
#define I2C10_RX_DMA_CONFIG                             \
    {                                                   \
        .Instance       = I2C10_RX_DMA_INSTANCE,        \
        .dma_irq        = I2C10_RX_DMA_IRQ,             \
        .HsInterface    = I2C10_RX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C10_RX_DMA_DMA_RCC,         \
        .dma_channel    = I2C10_RX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C10_RX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C10_RX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C10_RX_DMA_CONFIG */
#endif /* BSP_I2C10_RX_USING_DMA */
#ifdef BSP_I2C10_TX_USING_DMA
#ifndef I2C10_TX_DMA_CONFIG
#define I2C10_TX_DMA_CONFIG                             \
    {                                                  \
        .Instance       = I2C10_TX_DMA_INSTANCE,        \
        .dma_irq        = I2C10_TX_DMA_IRQ,             \
        .HsInterface    = I2C10_TX_DMA_HANDSHAK,        \
        .dma_rcc        = I2C10_TX_DMA_DMA_RCC,         \
        .dma_channel    = I2C10_TX_DMA_DMA_CHANNEL,     \
        .dmamux_channel = I2C10_TX_DMA_DMAMUX_CHANNEL,  \
        .dmamux_request = I2C10_TX_DMA_DMAMUX_REQUEST,  \
    }
#endif /* I2C10_TX_DMA_CONFIG */
#endif /* BSP_I2C10_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__I2C_HARD_CONFIG_H__ */
