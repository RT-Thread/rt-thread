/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-31     shelton      first version
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HWI2C_OWN_ADDRESS        0x0

#define I2C1_EVT_IRQHandler      I2C1_EVT_IRQHandler
#define I2C1_ERR_IRQHandler      I2C1_ERR_IRQHandler
#define I2C2_EVT_IRQHandler      I2C2_EVT_IRQHandler
#define I2C2_ERR_IRQHandler      I2C2_ERR_IRQHandler

#ifdef BSP_USING_HARD_I2C1
#define I2C1_CONFIG                                 \
    {                                               \
        .i2c_x = I2C1,                              \
        .i2c_name = "hwi2c1",                       \
        .timing = 0x80E02E2E,                       \
        .ev_irqn = I2C1_EVT_IRQn,                   \
        .er_irqn = I2C1_ERR_IRQn,                   \
    }
#endif /* BSP_USING_HARD_I2C1 */

#ifdef BSP_I2C1_RX_USING_DMA
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = I2C1_RX_DMA_CHANNEL,         \
        .dma_clock = I2C1_RX_DMA_CLOCK,             \
        .dma_irqn = I2C1_RX_DMA_IRQ,                \
        .flex_channel = I2C1_RX_DMA_FLEX_CHANNEL,   \
        .request_id = I2C1_RX_DMA_REQ_ID,           \
    }
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef BSP_I2C1_TX_USING_DMA
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = I2C1_TX_DMA_CHANNEL,         \
        .dma_clock = I2C1_TX_DMA_CLOCK,             \
        .dma_irqn = I2C1_TX_DMA_IRQ,                \
        .flex_channel = I2C1_TX_DMA_FLEX_CHANNEL,   \
        .request_id = I2C1_TX_DMA_REQ_ID,           \
    }
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_USING_HARD_I2C2
#define I2C2_CONFIG                                 \
    {                                               \
        .i2c_x = I2C2,                              \
        .i2c_name = "hwi2c2",                       \
        .timing = 0x80E02E2E,                       \
        .ev_irqn = I2C2_EVT_IRQn,                   \
        .er_irqn = I2C2_ERR_IRQn,                   \
    }
#endif /* BSP_USING_HARD_I2C2 */

#ifdef BSP_I2C2_RX_USING_DMA
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = I2C2_RX_DMA_CHANNEL,         \
        .dma_clock = I2C2_RX_DMA_CLOCK,             \
        .dma_irqn = I2C2_RX_DMA_IRQ,                \
        .flex_channel = I2C2_RX_DMA_FLEX_CHANNEL,   \
        .request_id = I2C2_RX_DMA_REQ_ID,           \
    }
#endif /* BSP_I2C2_RX_USING_DMA */

#ifdef BSP_I2C2_TX_USING_DMA
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_channel = I2C2_TX_DMA_CHANNEL,         \
        .dma_clock = I2C2_TX_DMA_CLOCK,             \
        .dma_irqn = I2C2_TX_DMA_IRQ,                \
        .flex_channel = I2C2_TX_DMA_FLEX_CHANNEL,   \
        .request_id = I2C2_TX_DMA_REQ_ID,           \
    }
#endif /* BSP_I2C2_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__I2C_CONFIG_H__ */

