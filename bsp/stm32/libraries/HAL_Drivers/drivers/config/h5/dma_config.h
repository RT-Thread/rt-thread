/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-14     Macro        first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel0 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_DMA_RX_IRQHandler         GPDMA1_Channel0_IRQHandler
#define UART3_RX_DMA_RCC                RCC_AHB1ENR_GPDMA1EN
#define UART3_RX_DMA_INSTANCE           GPDMA1_Channel0
#define UART3_RX_DMA_REQUEST            GPDMA1_REQUEST_USART3_RX
#define UART3_RX_DMA_IRQ                GPDMA1_Channel0_IRQn
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler         GPDMA1_Channel0_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHB1ENR_GPDMA1EN
#define UART1_TX_DMA_INSTANCE           GPDMA1_Channel0
#define UART1_TX_DMA_REQUEST            GPDMA1_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                GPDMA1_Channel0_IRQn
#endif

/* DMA1 channel1 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         GPDMA1_Channel1_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1ENR_GPDMA1EN
#define UART1_RX_DMA_INSTANCE           GPDMA1_Channel1
#define UART1_RX_DMA_REQUEST            GPDMA1_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                GPDMA1_Channel1_IRQn

#endif

/* DMA1 channel2 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler          GPDMA1_Channel2_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define SPI1_TX_DMA_INSTANCE            GPDMA1_Channel2
#define SPI1_TX_DMA_REQUEST             GPDMA1_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 GPDMA1_Channel2_IRQn
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler          GPDMA1_Channel3_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define SPI1_RX_DMA_INSTANCE            GPDMA1_Channel3
#define SPI1_RX_DMA_REQUEST             GPDMA1_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 GPDMA1_Channel3_IRQn
#endif


/* DMA1 channel4 */


/* DMA1 channel5 */


/* DMA1 channel6 */


/* DMA1 channel7 */


/* DMA2 channel0 */


/* DMA2 channel1 */


/* DMA2 channel2 */


/* DMA2 channel3 */


/* DMA2 channel4 */


/* DMA2 channel5 */

/* DMA2 channel6 */


/* DMA2 channel7 */


#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
