/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-31     AisinoChip   first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtconfig.h>

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
        .enable_id=EN_SPI1,                         \
        .cs_port = SPI1_CS_PORT,                    \
        .cs_pin = SPI1_CS_PIN,                      \
        .cs_alternate = SPI1_CS_ALTERNATE,          \
        .sck_port = SPI1_SCK_PORT,                  \
        .sck_pin = SPI1_SCK_PIN,                    \
        .sck_alternate = SPI1_SCK_ALTERNATE,        \
        .mosi_port = SPI1_MOSI_PORT,                \
        .mosi_pin = SPI1_MOSI_PIN,                  \
        .mosi_alternate = SPI1_MOSI_ALTERNATE,      \
        .miso_port = SPI1_MISO_PORT,                \
        .miso_pin = SPI1_MISO_PIN,                  \
        .miso_alternate = SPI1_MISO_ALTERNATE,      \
        .wp_port = SPI1_WP_PORT,                    \
        .wp_pin = SPI1_WP_PIN,                      \
        .wp_alternate = SPI1_WP_ALTERNATE,          \
        .hold_port = SPI1_HOLD_PORT,                \
        .hold_pin = SPI1_HOLD_PIN,                  \
        .hold_alternate = SPI1_HOLD_ALTERNATE,      \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI1_TX_DMA_RCC,                 \
        .Instance = SPI1_TX_DMA_INSTANCE,           \
        .dma_irq = SPI1_TX_DMA_IRQ,                 \
        .channel = SPI1_TX_DMA_CHANNEL,             \
        .request = SPI1_TX_DMA_REQUEST,             \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc = SPI1_RX_DMA_RCC,                 \
        .Instance = SPI1_RX_DMA_INSTANCE,           \
        .dma_irq = SPI1_RX_DMA_IRQ,                 \
        .channel = SPI1_RX_DMA_CHANNEL,             \
        .request = SPI1_RX_DMA_REQUEST,             \
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
        .enable_id=EN_SPI2,                         \
        .cs_port = SPI2_CS_PORT,                    \
        .cs_pin = SPI2_CS_PIN,                      \
        .cs_alternate = SPI2_CS_ALTERNATE,          \
        .sck_port = SPI2_SCK_PORT,                  \
        .sck_pin = SPI2_SCK_PIN,                    \
        .sck_alternate = SPI2_SCK_ALTERNATE,        \
        .mosi_port = SPI2_MOSI_PORT,                \
        .mosi_pin = SPI2_MOSI_PIN,                  \
        .mosi_alternate = SPI2_MOSI_ALTERNATE,      \
        .miso_port = SPI2_MISO_PORT,                \
        .miso_pin = SPI2_MISO_PIN,                  \
        .miso_alternate = SPI2_MISO_ALTERNATE,      \
        .wp_port = SPI2_WP_PORT,                    \
        .wp_pin = SPI2_WP_PIN,                      \
        .wp_alternate = SPI2_WP_ALTERNATE,          \
        .hold_port = SPI2_HOLD_PORT,                \
        .hold_pin = SPI2_HOLD_PIN,                  \
        .hold_alternate = SPI2_HOLD_ALTERNATE,      \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc  = SPI2_TX_DMA_RCC,                \
        .Instance = SPI2_TX_DMA_INSTANCE,           \
        .dma_irq  = SPI2_TX_DMA_IRQ,                \
        .channel = SPI2_TX_DMA_CHANNEL,             \
        .request = SPI2_TX_DMA_REQUEST,             \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .dma_rcc  = SPI2_RX_DMA_RCC,                \
        .Instance = SPI2_RX_DMA_INSTANCE,           \
        .dma_irq  = SPI2_RX_DMA_IRQ,                \
        .channel = SPI2_RX_DMA_CHANNEL,             \
        .request = SPI2_RX_DMA_REQUEST,             \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */


