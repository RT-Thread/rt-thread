/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-02     SummerGift   first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

/* DMA1 channel1 */
/* DMA1 channel2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_CHANNEL)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_CHANNEL)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_IRQn

#elif defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_CHANNEL)
#define USART3_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler
#define USART3_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define USART3_RX_DMA_INSTANCE            DMA1_Channel3
#define USART3_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

/* DMA1 channel4 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_CHANNEL)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE            DMA1_Channel4
#define SPI2_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 channel5 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_CHANNEL)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI2_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE            DMA1_Channel5
#define SPI2_TX_DMA_IRQ                 DMA1_Channel5_IRQn

#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_CHANNEL)
#define USART1_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler
#define USART1_RX_DMA_RCC                RCC_AHBENR_DMA1EN
#define USART1_RX_DMA_INSTANCE           DMA1_Channel5
#define USART1_RX_DMA_IRQ                DMA1_Channel5_IRQn
#endif

/* DMA1 channel6 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_CHANNEL)
#define USART2_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define USART2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define USART2_RX_DMA_INSTANCE            DMA1_Channel6
#define USART2_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif


/* DMA1 channel7 */

/* DMA2 channel1 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_CHANNEL)
#define SPI3_DMA_RX_IRQHandler          DMA2_Channel1_IRQHandler
#define SPI3_RX_DMA_RCC                 RCC_AHBENR_DMA2EN
#define SPI3_RX_DMA_INSTANCE            DMA2_Channel1
#define SPI3_RX_DMA_IRQ                 DMA2_Channel1_IRQn
#endif

/* DMA2 channel2 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_CHANNEL)
#define SPI3_DMA_TX_IRQHandler          DMA2_Channel2_IRQHandler
#define SPI3_TX_DMA_RCC                 RCC_AHBENR_DMA2EN
#define SPI3_TX_DMA_INSTANCE            DMA2_Channel2
#define SPI3_TX_DMA_IRQ                 DMA2_Channel2_IRQn
/* DMA1 channel4 */
#endif

/* DMA2 channel3 */
/* DMA2 channel4 */
/* DMA2 channel5 */


#endif /* __DMA_CONFIG_H__ */
