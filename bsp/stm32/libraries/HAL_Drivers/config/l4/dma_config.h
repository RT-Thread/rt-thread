/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-05     zylx         first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

/* dma1 channel1 */



/* dma1 channel1 */

/* dma1 channel2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_REQUEST)

#define SPI1_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI1_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_1
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_IRQn

#endif
/* dma1 channel2 */

/* dma1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_REQUEST)

#define SPI1_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_1
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_IRQn

#endif
/* dma1 channel3 */

/* dma1 channel4 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(USART1_TX_DMA_REQUEST)

#define USART1_DMA_TX_IRQHandler         DMA1_Channel4_IRQHandler
#define USART1_TX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define USART1_TX_DMA_INSTANCE           DMA1_Channel4
#define USART1_TX_DMA_REQUEST            DMA_REQUEST_2
#define USART1_TX_DMA_IRQ                DMA1_Channel4_IRQn

#endif
/* dma1 channel4 */

/* dma1 channel5 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(USART1_RX_DMA_REQUEST)

#define USART1_DMA_RX_IRQHandler         DMA1_Channel5_IRQHandler
#define USART1_RX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define USART1_RX_DMA_INSTANCE           DMA1_Channel5
#define USART1_RX_DMA_REQUEST            DMA_REQUEST_2
#define USART1_RX_DMA_IRQ                DMA1_Channel5_IRQn

#elif defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_CHANNEL)

#define QSPI_DMA_IRQHandler             DMA1_Channel5_IRQHandler
#define QSPI_DMA_RCC                    RCC_AHB1ENR_DMA1EN
#define QSPI_DMA_INSTANCE               DMA1_Channel5
#define QSPI_DMA_CHANNEL                DMA_REQUEST_5
#define QSPI_DMA_IRQ                    DMA1_Channel5_IRQn

#endif
/* dma1 channel5 */

/* dma1 channel6 */
/* dma1 channel6 */

/* dma1 channel7 */



/* dma1 channel7 */

/* dma2 channel1 */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_REQUEST)

#define UART5_DMA_TX_IRQHandler         DMA2_Channel1_IRQHandler
#define UART5_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART5_TX_DMA_INSTANCE           DMA2_Channel1
#define UART5_TX_DMA_REQUEST            DMA_REQUEST_2
#define UART5_TX_DMA_IRQ                DMA2_Channel1_IRQn

#endif
/* dma2 channel1 */

/* dma2 channel2 */
#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_REQUEST)

#define UART5_DMA_RX_IRQHandler         DMA2_Channel2_IRQHandler
#define UART5_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART5_RX_DMA_INSTANCE           DMA2_Channel2
#define UART5_RX_DMA_REQUEST            DMA_REQUEST_2
#define UART5_RX_DMA_IRQ                DMA2_Channel2_IRQn

#endif
/* dma2 channel2 */

/* dma2 channel3 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_REQUEST)

#define SPI1_DMA_RX_IRQHandler          DMA2_Channel3_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE            DMA2_Channel3
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_4
#define SPI1_RX_DMA_IRQ                 DMA2_Channel3_IRQn

#endif
/* dma2 channel3 */

/* dma2 channel4 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_REQUEST)

#define SPI1_DMA_TX_IRQHandler          DMA2_Channel4_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1ENR_DMA2EN
#define SPI1_TX_DMA_INSTANCE            DMA2_Channel4
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_4
#define SPI1_TX_DMA_IRQ                 DMA2_Channel4_IRQn

#endif
/* dma2 channel4 */

/* dma2 channel5 */



/* dma2 channel5 */

/* dma2 channel6 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(USART1_TX_DMA_REQUEST)

#define USART1_DMA_TX_IRQHandler         DMA2_Channel6_IRQHandler
#define USART1_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define USART1_TX_DMA_INSTANCE           DMA2_Channel6
#define USART1_TX_DMA_REQUEST            DMA_REQUEST_2
#define USART1_TX_DMA_IRQ                DMA2_Channel6_IRQn

#endif
/* dma2 channel6 */

/* dma2 channel7 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(USART1_RX_DMA_REQUEST)

#define USART1_DMA_RX_IRQHandler         DMA2_Channel7_IRQHandler
#define USART1_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define USART1_RX_DMA_INSTANCE           DMA2_Channel7
#define USART1_RX_DMA_REQUEST            DMA_REQUEST_2
#define USART1_RX_DMA_IRQ                DMA2_Channel7_IRQn

#elif defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_CHANNEL)

#define QSPI_DMA_IRQHandler             DMA2_Channel7_IRQHandler
#define QSPI_DMA_RCC                    RCC_AHB1ENR_DMA2EN
#define QSPI_DMA_INSTANCE               DMA2_Channel7
#define QSPI_DMA_CHANNEL                DMA_REQUEST_3
#define QSPI_DMA_IRQ                    DMA2_Channel7_IRQn

#endif
/* dma2 channel7 */

#endif /* __DMA_CONFIG_H__ */
