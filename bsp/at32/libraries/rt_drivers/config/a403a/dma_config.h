/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-12     shelton      first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1 */
/* DMA1 channel2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_CHANNEL)
#define SPI1_RX_DMA_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_RX_DMA_CHANNEL             DMA1_CHANNEL2
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#elif defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_CHANNEL)
#define UART3_TX_DMA_IRQHandler         DMA1_Channel2_IRQHandler
#define UART3_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART3_TX_DMA_CHANNEL            DMA1_CHANNEL2
#define UART3_TX_DMA_IRQ                DMA1_Channel2_IRQn
#elif defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_CHANNEL)
#define I2C3_TX_DMA_IRQHandler          DMA1_Channel2_IRQHandler
#define I2C3_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C3_TX_DMA_CHANNEL             DMA1_CHANNEL2
#define I2C3_TX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_CHANNEL)
#define SPI1_TX_DMA_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_TX_DMA_CHANNEL             DMA1_CHANNEL3
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#elif defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_CHANNEL)
#define UART3_RX_DMA_IRQHandler         DMA1_Channel3_IRQHandler
#define UART3_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART3_RX_DMA_CHANNEL            DMA1_CHANNEL3
#define UART3_RX_DMA_IRQ                DMA1_Channel3_IRQn
#elif defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_CHANNEL)
#define I2C3_RX_DMA_IRQHandler          DMA1_Channel3_IRQHandler
#define I2C3_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C3_RX_DMA_CHANNEL             DMA1_CHANNEL3
#define I2C3_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

/* DMA1 channel4 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_CHANNEL)
#define SPI2_RX_DMA_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_RX_DMA_CHANNEL             DMA1_CHANNEL4
#define SPI2_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_CHANNEL)
#define UART1_TX_DMA_IRQHandler         DMA1_Channel4_IRQHandler
#define UART1_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_TX_DMA_CHANNEL            DMA1_CHANNEL4
#define UART1_TX_DMA_IRQ                DMA1_Channel4_IRQn
#elif defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_CHANNEL)
#define I2C2_TX_DMA_IRQHandler          DMA1_Channel4_IRQHandler
#define I2C2_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C2_TX_DMA_CHANNEL             DMA1_CHANNEL4
#define I2C2_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 channel5 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_CHANNEL)
#define SPI2_TX_DMA_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI2_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_TX_DMA_CHANNEL             DMA1_CHANNEL5
#define SPI2_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_CHANNEL)
#define UART1_RX_DMA_IRQHandler         DMA1_Channel5_IRQHandler
#define UART1_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_RX_DMA_CHANNEL            DMA1_CHANNEL5
#define UART1_RX_DMA_IRQ                DMA1_Channel5_IRQn
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_CHANNEL)
#define I2C2_RX_DMA_IRQHandler          DMA1_Channel5_IRQHandler
#define I2C2_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C2_RX_DMA_CHANNEL             DMA1_CHANNEL5
#define I2C2_RX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

/* DMA1 channel6 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_CHANNEL)
#define UART2_RX_DMA_IRQHandler         DMA1_Channel6_IRQHandler
#define UART2_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_RX_DMA_CHANNEL            DMA1_CHANNEL6
#define UART2_RX_DMA_IRQ                DMA1_Channel6_IRQn
#elif defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_CHANNEL)
#define I2C1_TX_DMA_IRQHandler          DMA1_Channel6_IRQHandler
#define I2C1_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C1_TX_DMA_CHANNEL             DMA1_CHANNEL6
#define I2C1_TX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif

/* DMA1 channel7 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_CHANNEL)
#define UART2_TX_DMA_IRQHandler         DMA1_Channel7_IRQHandler
#define UART2_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_TX_DMA_CHANNEL            DMA1_CHANNEL7
#define UART2_TX_DMA_IRQ                DMA1_Channel7_IRQn
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_CHANNEL)
#define I2C1_RX_DMA_IRQHandler          DMA1_Channel7_IRQHandler
#define I2C1_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define I2C1_RX_DMA_CHANNEL             DMA1_CHANNEL7
#define I2C1_RX_DMA_IRQ                 DMA1_Channel7_IRQn
#endif

/* DMA2 channel1 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_CHANNEL)
#define SPI3_RX_DMA_IRQHandler          DMA2_Channel1_IRQHandler
#define SPI3_RX_DMA_CLOCK               CRM_DMA2_PERIPH_CLOCK
#define SPI3_RX_DMA_CHANNEL             DMA2_CHANNEL1
#define SPI3_RX_DMA_IRQ                 DMA2_Channel1_IRQn
#endif

/* DMA2 channel2 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_CHANNEL)
#define SPI3_TX_DMA_IRQHandler          DMA2_Channel2_IRQHandler
#define SPI3_TX_DMA_CLOCK               CRM_DMA2_PERIPH_CLOCK
#define SPI3_TX_DMA_CHANNEL             DMA2_CHANNEL2
#define SPI3_TX_DMA_IRQ                 DMA2_Channel2_IRQn
#endif

/* DMA2 channel3 */
#if defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_CHANNEL)
#define SPI4_RX_DMA_IRQHandler          DMA2_Channel3_IRQHandler
#define SPI4_RX_DMA_CLOCK               CRM_DMA2_PERIPH_CLOCK
#define SPI4_RX_DMA_CHANNEL             DMA2_CHANNEL3
#define SPI4_RX_DMA_IRQ                 DMA2_Channel3_IRQn
#elif defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_CHANNEL)
#define UART4_RX_DMA_IRQHandler         DMA2_Channel3_IRQHandler
#define UART4_RX_DMA_CLOCK              CRM_DMA2_PERIPH_CLOCK
#define UART4_RX_DMA_CHANNEL            DMA2_CHANNEL3
#define UART4_RX_DMA_IRQ                DMA2_Channel3_IRQn
#endif

/* DMA2 channel4 */
/* DMA2 channel5 */
#if defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_CHANNEL)
#define SPI4_TX_DMA_IRQHandler          DMA2_Channel4_5_IRQHandler
#define SPI4_TX_DMA_CLOCK               CRM_DMA2_PERIPH_CLOCK
#define SPI4_TX_DMA_CHANNEL             DMA2_CHANNEL5
#define SPI4_TX_DMA_IRQ                 DMA2_Channel4_5_IRQn
#elif defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_CHANNEL)
#define UART4_TX_DMA_IRQHandler         DMA2_Channel4_5_IRQHandler
#define UART4_TX_DMA_CLOCK              CRM_DMA2_PERIPH_CLOCK
#define UART4_TX_DMA_CHANNEL            DMA2_CHANNEL5
#define UART4_TX_DMA_IRQ                DMA2_Channel4_5_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
