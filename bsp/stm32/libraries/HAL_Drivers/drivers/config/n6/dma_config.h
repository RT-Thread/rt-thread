/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-02     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 * 2020-05-02     whj4674672   support stm32h7 dma1 and dma2
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* N6 provides one GPDMA1 controller with 16 independent channels. Keep the
 * legacy endpoint table below source-compatible while assigning each legacy
 * stream a unique GPDMA channel. */
#define DMA1_Stream0                 GPDMA1_Channel0
#define DMA1_Stream1                 GPDMA1_Channel1
#define DMA1_Stream2                 GPDMA1_Channel2
#define DMA1_Stream3                 GPDMA1_Channel3
#define DMA1_Stream4                 GPDMA1_Channel4
#define DMA1_Stream5                 GPDMA1_Channel5
#define DMA1_Stream6                 GPDMA1_Channel6
#define DMA1_Stream7                 GPDMA1_Channel7
#define DMA2_Stream0                 GPDMA1_Channel8
#define DMA2_Stream1                 GPDMA1_Channel9
#define DMA2_Stream2                 GPDMA1_Channel10
#define DMA2_Stream3                 GPDMA1_Channel11
#define DMA2_Stream4                 GPDMA1_Channel12
#define DMA2_Stream5                 GPDMA1_Channel13
#define DMA2_Stream6                 GPDMA1_Channel14
#define DMA2_Stream7                 GPDMA1_Channel15
#define DMA1_Stream0_IRQn            GPDMA1_Channel0_IRQn
#define DMA1_Stream1_IRQn            GPDMA1_Channel1_IRQn
#define DMA1_Stream2_IRQn            GPDMA1_Channel2_IRQn
#define DMA1_Stream3_IRQn            GPDMA1_Channel3_IRQn
#define DMA1_Stream4_IRQn            GPDMA1_Channel4_IRQn
#define DMA1_Stream5_IRQn            GPDMA1_Channel5_IRQn
#define DMA1_Stream6_IRQn            GPDMA1_Channel6_IRQn
#define DMA1_Stream7_IRQn            GPDMA1_Channel7_IRQn
#define DMA2_Stream0_IRQn            GPDMA1_Channel8_IRQn
#define DMA2_Stream1_IRQn            GPDMA1_Channel9_IRQn
#define DMA2_Stream2_IRQn            GPDMA1_Channel10_IRQn
#define DMA2_Stream3_IRQn            GPDMA1_Channel11_IRQn
#define DMA2_Stream4_IRQn            GPDMA1_Channel12_IRQn
#define DMA2_Stream5_IRQn            GPDMA1_Channel13_IRQn
#define DMA2_Stream6_IRQn            GPDMA1_Channel14_IRQn
#define DMA2_Stream7_IRQn            GPDMA1_Channel15_IRQn
#define RCC_AHB1ENR_DMA1EN          RCC_AHB1ENR_GPDMA1EN
#define RCC_AHB1ENR_DMA2EN          RCC_AHB1ENR_GPDMA1EN
#define SPI1_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI1_RX
#define SPI1_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI1_TX
#define SPI2_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI2_RX
#define SPI2_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI2_TX
#define SPI3_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI3_RX
#define SPI3_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI3_TX
#define SPI4_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI4_RX
#define SPI4_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI4_TX
#define SPI5_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI5_RX
#define SPI5_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI5_TX
#define SPI6_RX_DMA_REQUEST         GPDMA1_REQUEST_SPI6_RX
#define SPI6_TX_DMA_REQUEST         GPDMA1_REQUEST_SPI6_TX
#define DMA_REQUEST_USART2_RX       GPDMA1_REQUEST_USART2_RX
#define DMA_REQUEST_USART2_TX       GPDMA1_REQUEST_USART2_TX

/* DMA1 stream0 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Stream0_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Stream0
#define UART2_RX_DMA_REQUEST             DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                 DMA1_Stream0_IRQn
#endif

/* DMA1 stream1 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_DMA_TX_IRQHandler          DMA1_Stream1_IRQHandler
#define UART2_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART2_TX_DMA_INSTANCE            DMA1_Stream1
#define UART2_TX_DMA_REQUEST             DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                 DMA1_Stream1_IRQn
#endif

/* DMA1 stream2 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_DMA_RX_IRQHandler           DMA1_Stream2_IRQHandler
#define SPI3_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_RX_DMA_INSTANCE             DMA1_Stream2
#define SPI3_RX_DMA_IRQ                  DMA1_Stream2_IRQn
#endif

/* DMA1 stream3 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler
#define SPI2_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE             DMA1_Stream3
#define SPI2_RX_DMA_IRQ                  DMA1_Stream3_IRQn
#endif

/* DMA1 stream4 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#define SPI2_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE             DMA1_Stream4
#define SPI2_TX_DMA_IRQ                  DMA1_Stream4_IRQn
#endif


/* DMA1 stream5 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream5_IRQHandler
#define SPI3_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_TX_DMA_INSTANCE             DMA1_Stream5
#define SPI3_TX_DMA_IRQ                  DMA1_Stream5_IRQn
#endif

/* DMA1 stream6 */

/* DMA1 stream7 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream7_IRQHandler
#define SPI3_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_TX_DMA_INSTANCE             DMA1_Stream7
#define SPI3_TX_DMA_IRQ                  DMA1_Stream7_IRQn
#endif

/* DMA1 stream6/7 are available for SPI6 when SPI3 TX uses stream5. */
#if defined(BSP_SPI6_RX_USING_DMA) && !defined(SPI6_RX_DMA_INSTANCE)
#define SPI6_DMA_RX_IRQHandler           DMA1_Stream6_IRQHandler
#define SPI6_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI6_RX_DMA_INSTANCE             DMA1_Stream6
#define SPI6_RX_DMA_IRQ                  DMA1_Stream6_IRQn
#endif

#if defined(BSP_SPI6_TX_USING_DMA) && !defined(SPI6_TX_DMA_INSTANCE)
#define SPI6_DMA_TX_IRQHandler           DMA1_Stream7_IRQHandler
#define SPI6_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI6_TX_DMA_INSTANCE             DMA1_Stream7
#define SPI6_TX_DMA_IRQ                  DMA1_Stream7_IRQn
#endif

/* DMA2 stream0 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI1_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI1_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#endif

/* DMA2 stream1 */
#if defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#define SPI4_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_TX_DMA_INSTANCE             DMA2_Stream1
#define SPI4_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#endif

/* DMA2 stream2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler
#define SPI1_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE             DMA2_Stream2
#define SPI1_RX_DMA_IRQ                  DMA2_Stream2_IRQn
#endif

/* DMA2 stream3 */
#if defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream3
#define SPI5_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#endif

/* DMA2 stream4 */
#if defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream4
#define SPI5_TX_DMA_IRQ                  DMA2_Stream4_IRQn
#endif

/* DMA2 stream5 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler           DMA2_Stream5_IRQHandler
#define SPI1_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_TX_DMA_INSTANCE             DMA2_Stream5
#define SPI1_TX_DMA_IRQ                  DMA2_Stream5_IRQn
#endif

/* DMA2 stream6 */
#if defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream6_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream6
#define SPI5_TX_DMA_IRQ                  DMA2_Stream6_IRQn
#endif

/* DMA2 stream7 */
#if defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler              DMA2_Stream7_IRQHandler
#define QSPI_DMA_RCC                     RCC_AHB1ENR_DMA2EN
#define QSPI_DMA_INSTANCE                DMA2_Stream7
#define QSPI_DMA_IRQ                     DMA2_Stream7_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
