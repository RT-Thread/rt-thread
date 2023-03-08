/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-31     shelton      first version
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
#define SPI1_TX_RX_DMA_IRQHandler       DMA1_Channel3_2_IRQHandler
#define SPI1_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_RX_DMA_CHANNEL             DMA1_CHANNEL2
#define SPI1_RX_DMA_IRQ                 DMA1_Channel3_2_IRQn
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_CHANNEL)
#define UART1_TX_RX_DMA_IRQHandler      DMA1_Channel3_2_IRQHandler
#define UART1_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_TX_DMA_CHANNEL            DMA1_CHANNEL2
#define UART1_TX_DMA_IRQ                DMA1_Channel3_2_IRQn
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_CHANNEL)
#define SPI1_TX_RX_DMA_IRQHandler       DMA1_Channel3_2_IRQHandler
#define SPI1_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI1_TX_DMA_CHANNEL             DMA1_CHANNEL3
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_2_IRQn
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_CHANNEL)
#define UART1_TX_RX_DMA_IRQHandler      DMA1_Channel3_2_IRQHandler
#define UART1_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART1_RX_DMA_CHANNEL            DMA1_CHANNEL3
#define UART1_RX_DMA_IRQ                DMA1_Channel3_2_IRQn
#endif

/* DMA1 channel4 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_CHANNEL)
#define SPI2_TX_RX_DMA_IRQHandler       DMA1_Channel5_4_IRQHandler
#define SPI2_RX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_RX_DMA_CHANNEL             DMA1_CHANNEL4
#define SPI2_RX_DMA_IRQ                 DMA1_Channel5_4_IRQn
#elif defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_CHANNEL)
#define UART2_TX_RX_DMA_IRQHandler      DMA1_Channel5_4_IRQHandler
#define UART2_TX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_TX_DMA_CHANNEL            DMA1_CHANNEL4
#define UART2_TX_DMA_IRQ                DMA1_Channel5_4_IRQn
#endif

/* DMA1 channel5 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_CHANNEL)
#define SPI2_TX_RX_DMA_IRQHandler       DMA1_Channel5_4_IRQHandler
#define SPI2_TX_DMA_CLOCK               CRM_DMA1_PERIPH_CLOCK
#define SPI2_TX_DMA_CHANNEL             DMA1_CHANNEL5
#define SPI2_TX_DMA_IRQ                 DMA1_Channel5_4_IRQn
#elif defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_CHANNEL)
#define UART2_TX_RX_DMA_IRQHandler      DMA1_Channel5_4_IRQHandler
#define UART2_RX_DMA_CLOCK              CRM_DMA1_PERIPH_CLOCK
#define UART2_RX_DMA_CHANNEL            DMA1_CHANNEL5
#define UART2_RX_DMA_IRQ                DMA1_Channel5_4_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
