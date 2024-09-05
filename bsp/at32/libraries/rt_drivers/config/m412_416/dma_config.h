/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     shelton      first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_CHANNEL)
#define SPI1_RX_DMA_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI1_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_RX_DMA_CHANNEL             DMA1_CHANNEL1
#define SPI1_RX_DMA_IRQ                 DMA1_Channel1_IRQn
#define SPI1_RX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL1
#define SPI1_RX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_SPI1_RX
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_CHANNEL)
#define UART1_RX_DMA_IRQHandler         DMA1_Channel1_IRQHandler
#define UART1_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_RX_DMA_CHANNEL            DMA1_CHANNEL1
#define UART1_RX_DMA_IRQ                DMA1_Channel1_IRQn
#define UART1_RX_DMA_MUX_CHANNEL        DMA1MUX_CHANNEL1
#define UART1_RX_DMA_REQ_ID             DMAMUX_DMAREQ_ID_USART1_RX
#endif

/* DMA1 channel2 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_CHANNEL)
#define SPI1_TX_DMA_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_TX_DMA_CHANNEL             DMA1_CHANNEL2
#define SPI1_TX_DMA_IRQ                 DMA1_Channel2_IRQn
#define SPI1_TX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL2
#define SPI1_TX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_SPI1_TX
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_CHANNEL)
#define UART1_TX_DMA_IRQHandler         DMA1_Channel2_IRQHandler
#define UART1_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_TX_DMA_CHANNEL            DMA1_CHANNEL2
#define UART1_TX_DMA_IRQ                DMA1_Channel2_IRQn
#define UART1_TX_DMA_MUX_CHANNEL        DMA1MUX_CHANNEL2
#define UART1_TX_DMA_REQ_ID             DMAMUX_DMAREQ_ID_USART1_TX
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_CHANNEL)
#define SPI2_RX_DMA_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI2_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_RX_DMA_CHANNEL             DMA1_CHANNEL3
#define SPI2_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#define SPI2_RX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL3
#define SPI2_RX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_SPI2_RX
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_CHANNEL)
#define I2C1_RX_DMA_IRQHandler          DMA1_Channel3_IRQHandler
#define I2C1_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C1_RX_DMA_CHANNEL             DMA1_CHANNEL3
#define I2C1_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#define I2C1_RX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL1
#define I2C1_RX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_I2C1_RX
#endif

/* DMA1 channel4 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_CHANNEL)
#define SPI2_TX_DMA_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_TX_DMA_CHANNEL             DMA1_CHANNEL4
#define SPI2_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#define SPI2_TX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL4
#define SPI2_TX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_SPI2_TX
#elif defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_CHANNEL)
#define I2C1_TX_DMA_IRQHandler          DMA1_Channel4_IRQHandler
#define I2C1_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C1_TX_DMA_CHANNEL             DMA1_CHANNEL4
#define I2C1_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#define I2C1_TX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL2
#define I2C1_TX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_I2C1_TX
#endif

/* DMA1 channel5 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_CHANNEL)
#define UART2_RX_DMA_IRQHandler         DMA1_Channel5_IRQHandler
#define UART2_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_RX_DMA_CHANNEL            DMA1_CHANNEL5
#define UART2_RX_DMA_IRQ                DMA1_Channel5_IRQn
#define UART2_RX_DMA_MUX_CHANNEL        DMA1MUX_CHANNEL5
#define UART2_RX_DMA_REQ_ID             DMAMUX_DMAREQ_ID_USART2_RX
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_CHANNEL)
#define I2C2_RX_DMA_IRQHandler          DMA1_Channel5_IRQHandler
#define I2C2_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C2_RX_DMA_CHANNEL             DMA1_CHANNEL5
#define I2C2_RX_DMA_IRQ                 DMA1_Channel5_IRQn
#define I2C2_RX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL5
#define I2C2_RX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_I2C2_RX
#endif

/* DMA1 channel6 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_CHANNEL)
#define UART2_TX_DMA_IRQHandler         DMA1_Channel6_IRQHandler
#define UART2_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_TX_DMA_CHANNEL            DMA1_CHANNEL6
#define UART2_TX_DMA_IRQ                DMA1_Channel6_IRQn
#define UART2_TX_DMA_MUX_CHANNEL        DMA1MUX_CHANNEL6
#define UART2_TX_DMA_REQ_ID             DMAMUX_DMAREQ_ID_USART2_TX
#elif defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_CHANNEL)
#define I2C2_TX_DMA_IRQHandler          DMA1_Channel6_IRQHandler
#define I2C2_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C2_TX_DMA_CHANNEL             DMA1_CHANNEL6
#define I2C2_TX_DMA_IRQ                 DMA1_Channel6_IRQn
#define I2C2_TX_DMA_MUX_CHANNEL         DMA1MUX_CHANNEL6
#define I2C2_TX_DMA_REQ_ID              DMAMUX_DMAREQ_ID_I2C2_TX
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
