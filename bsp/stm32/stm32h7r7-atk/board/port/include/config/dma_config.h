/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-02     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GPDMA1_Channel2 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler          GPDMA1_Channel2_IRQHandler
#define UART1_RX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define UART1_RX_DMA_INSTANCE            GPDMA1_Channel2
#define UART1_RX_DMA_REQUEST             GPDMA1_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                 GPDMA1_Channel2_IRQn
#endif

/* GPDMA1_Channel */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler          GPDMA1_Channel3_IRQHandler
#define UART1_TX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define UART1_TX_DMA_INSTANCE            GPDMA1_Channel3
#define UART1_TX_DMA_REQUEST             GPDMA1_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                 GPDMA1_Channel3_IRQn
#endif

/* GPDMA1_Channel0 */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_INSTANCE)
#define UART7_DMA_TX_IRQHandler          GPDMA1_Channel0_IRQHandler
#define UART7_TX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define UART7_TX_DMA_INSTANCE            GPDMA1_Channel0
#define UART7_TX_DMA_REQUEST             GPDMA1_REQUEST_UART7_TX
// #define UART7_TX_DMA_CHANNEL             GPDMA1_Channel0
#define UART7_TX_DMA_IRQ                 GPDMA1_Channel0_IRQn
#endif

/* GPDMA1_Channel1 */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_INSTANCE)
#define UART7_DMA_RX_IRQHandler          GPDMA1_Channel1_IRQHandler
#define UART7_RX_DMA_RCC                 RCC_AHB1ENR_GPDMA1EN
#define UART7_RX_DMA_INSTANCE            GPDMA1_Channel1
#define UART7_RX_DMA_REQUEST             GPDMA1_REQUEST_UART7_RX
// #define UART7_RX_DMA_CHANNEL             GPDMA1_Channel11
#define UART7_RX_DMA_IRQ                 GPDMA1_Channel1_IRQn
#endif

/* DMA1 stream3 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler
#define SPI2_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE             DMA1_Stream3
#define SPI2_RX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI2_RX_DMA_IRQ                  DMA1_Stream3_IRQn
#endif

/* DMA1 stream4 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#define SPI2_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE             DMA1_Stream4
#define SPI2_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI2_TX_DMA_IRQ                  DMA1_Stream4_IRQn
#endif


/* DMA1 stream5 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Stream5_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Stream5
#define UART2_RX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART2_RX_DMA_IRQ                 DMA1_Stream5_IRQn
#endif

/* DMA1 stream6 */

/* DMA1 stream7 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream7_IRQHandler
#define SPI3_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_TX_DMA_INSTANCE             DMA1_Stream7
#define SPI3_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI3_TX_DMA_IRQ                  DMA1_Stream7_IRQn
#endif

/* DMA2 stream0 */
#if defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI4_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI4_RX_DMA_CHANNEL              DMA_CHANNEL_4
#define SPI4_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#endif

/* DMA2 stream1 */
#if defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#define SPI4_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_TX_DMA_INSTANCE             DMA2_Stream1
#define SPI4_TX_DMA_CHANNEL              DMA_CHANNEL_4
#define SPI4_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#endif

/* DMA2 stream2 */
#if defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler              DMA2_Stream2_IRQHandler
#define QSPI_DMA_RCC                     RCC_AHB1ENR_DMA2EN
#define QSPI_DMA_INSTANCE                DMA2_Stream2
#define QSPI_DMA_CHANNEL                 DMA_CHANNEL_11
#define QSPI_DMA_IRQ                     DMA2_Stream2_IRQn
#endif

/* DMA2 stream3 */
#if defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI4_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_RX_DMA_INSTANCE             DMA2_Stream3
#define SPI4_RX_DMA_CHANNEL              DMA_CHANNEL_5
#define SPI4_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#endif

/* DMA2 stream4 */
#if defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream4
#define SPI5_TX_DMA_CHANNEL              DMA_CHANNEL_2
#define SPI5_TX_DMA_IRQ                  DMA2_Stream4_IRQn
#endif

/* DMA2 stream5 */
#if defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream5_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream5
#define SPI5_RX_DMA_CHANNEL              DMA_CHANNEL_7
#define SPI5_RX_DMA_IRQ                  DMA2_Stream5_IRQn
#endif

/* DMA2 stream6 */
#if defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream6_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream6
#define SPI5_TX_DMA_CHANNEL              DMA_CHANNEL_7
#define SPI5_TX_DMA_IRQ                  DMA2_Stream6_IRQn
#endif

/* DMA2 stream7 */
#if defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler              DMA2_Stream7_IRQHandler
#define QSPI_DMA_RCC                     RCC_AHB1ENR_DMA2EN
#define QSPI_DMA_INSTANCE                DMA2_Stream7
#define QSPI_DMA_CHANNEL                 DMA_CHANNEL_3
#define QSPI_DMA_IRQ                     DMA2_Stream7_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
