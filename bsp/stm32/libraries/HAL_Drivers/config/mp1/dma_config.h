/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-02     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 * 2020-06-20     thread-liu   add stm32mp1
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA2 stream0 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_RX_DMA_IRQHandler          DMA2_Stream0_IRQHandler
#define UART3_RX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART3_RX_DMA_INSTANCE            DMA2_Stream0
#define UART3_RX_DMA_CHANNEL             DMA_REQUEST_USART3_RX
#define UART3_RX_DMA_IRQ                 DMA2_Stream0_IRQn
#elif defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI4_RX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI4_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI4_RX_DMA_CHANNEL              DMA_REQUEST_SPI4_RX
#define SPI4_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#elif defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_INSTANCE)
#define UART5_DMA_RX_IRQHandler          DMA2_Stream0_IRQHandler
#define UART5_RX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART5_RX_DMA_INSTANCE            DMA2_Stream0
#define UART5_RX_DMA_CHANNEL             DMA_REQUEST_UART5_RX
#define UART5_RX_DMA_IRQ                 DMA2_Stream0_IRQn
#endif
    
/* DMA2 stream1 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(BSP_UART3_TX_USING_INSTANCE)
#define UART3_TX_DMA_IRQHandler           DMA2_Stream1_IRQHandler
#define UART3_TX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define UART3_TX_DMA_INSTANCE             DMA2_Stream1
#define UART3_TX_DMA_CHANNEL              DMA_REQUEST_USART3_TX
#define UART3_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#elif defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#define SPI4_TX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI4_TX_DMA_INSTANCE             DMA2_Stream1
#define SPI4_TX_DMA_CHANNEL              DMA_REQUEST_SPI4_TX
#define SPI4_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#endif

/* DMA2 stream2 */
#if defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler              DMA2_Stream2_IRQHandler
#define QSPI_DMA_RCC                     RCC_MC_AHB2ENSETR_DMA2EN
#define QSPI_DMA_INSTANCE                DMA2_Stream2
#define QSPI_DMA_CHANNEL                 DMA_CHANNEL_11
#define QSPI_DMA_IRQ                     DMA2_Stream2_IRQn
#endif

/* DMA2 stream3 */
#if defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream3
#define SPI5_RX_DMA_CHANNEL              DMA_REQUEST_SPI5_RX
#define SPI5_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#endif

/* DMA2 stream4 */
#if defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream4
#define SPI5_TX_DMA_CHANNEL              DMA_REQUEST_SPI5_TX
#define SPI5_TX_DMA_IRQ                  DMA2_Stream4_IRQn
#endif

/* DMA2 stream5 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART4_DMA_TX_IRQHandler          DMA2_Stream5_IRQHandler
#define UART4_TX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART4_TX_DMA_INSTANCE            DMA2_Stream5
#define UART4_TX_DMA_CHANNEL             DMA_REQUEST_UART4_TX
#define UART4_TX_DMA_IRQ                 DMA2_Stream5_IRQn    
#endif

/* DMA2 stream6 */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_DMA_RX_IRQHandler          DMA2_Stream6_IRQHandler
#define UART4_RX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART4_RX_DMA_INSTANCE            DMA2_Stream6
#define UART4_RX_DMA_CHANNEL             DMA_REQUEST_UART4_RX
#define UART4_RX_DMA_IRQ                 DMA2_Stream6_IRQn        
#endif

/* DMA2 stream7 */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART5_DMA_TX_IRQHandler          DMA2_Stream7_IRQHandler
#define UART5_TX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART5_TX_DMA_INSTANCE            DMA2_Stream7
#define UART5_TX_DMA_CHANNEL             DMA_REQUEST_UART5_TX
#define UART5_TX_DMA_IRQ                 DMA2_Stream7_IRQn
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
