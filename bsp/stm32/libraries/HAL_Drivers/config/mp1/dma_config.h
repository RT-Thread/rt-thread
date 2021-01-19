/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-20     thread-liu   first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 stream0 */

/* DMA1 stream1 */

/* DMA1 stream2 */

/* DMA1 stream3 */

/* DMA1 stream4 */

/* DMA1 stream5 */

/* DMA1 stream6 */

/* DMA1 stream7 */

/* DMA2 stream0 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_RX_DMA_IRQHandler          DMA2_Stream0_IRQHandler
#define UART3_RX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART3_RX_DMA_INSTANCE            DMA2_Stream0
#define UART3_RX_DMA_CHANNEL             DMA_REQUEST_USART3_RX
#define UART3_RX_DMA_IRQ                 DMA2_Stream0_IRQn
#elif defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI5_RX_DMA_CHANNEL              DMA_REQUEST_SPI5_RX
#define SPI5_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#endif
    
/* DMA2 stream1 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(BSP_UART3_TX_USING_INSTANCE)
#define UART3_TX_DMA_IRQHandler           DMA2_Stream1_IRQHandler
#define UART3_TX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define UART3_TX_DMA_INSTANCE             DMA2_Stream1
#define UART3_TX_DMA_CHANNEL              DMA_REQUEST_USART3_TX
#define UART3_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#elif defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream1
#define SPI5_TX_DMA_CHANNEL              DMA_REQUEST_SPI5_TX
#define SPI5_TX_DMA_IRQ                  DMA2_Stream1_IRQn
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
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_DMA_RX_IRQHandler          DMA2_Stream3_IRQHandler
#define UART4_RX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART4_RX_DMA_INSTANCE            DMA2_Stream3
#define UART4_RX_DMA_CHANNEL             DMA_REQUEST_UART4_RX
#define UART4_RX_DMA_IRQ                 DMA2_Stream3_IRQn        
#endif

/* DMA2 stream4 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART4_DMA_TX_IRQHandler          DMA2_Stream4_IRQHandler
#define UART4_TX_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define UART4_TX_DMA_INSTANCE            DMA2_Stream4
#define UART4_TX_DMA_CHANNEL             DMA_REQUEST_UART4_TX
#define UART4_TX_DMA_IRQ                 DMA2_Stream4_IRQn   
#endif

/* DMA2 stream5 */
#if defined(BSP_USING_CRYP) && !defined(CRYP2_OUT_DMA_INSTANCE)
#define CRYP2_DMA_OUT_IRQHandler           DMA2_Stream5_IRQHandler
#define CRYP2_OUT_DMA_RCC                  RCC_MC_AHB2ENSETR_DMA2EN
#define CRYP2_OUT_DMA_INSTANCE             DMA2_Stream5
#define CRYP2_OUT_DMA_CHANNEL              DMA_REQUEST_CRYP2_OUT
#define CRYP2_OUT_DMA_IRQ                  DMA2_Stream5_IRQn
#endif

/* DMA2 stream6 */
#if defined(BSP_USING_CRYP) && !defined(CRYP2_IN_DMA_INSTANCE)
#define CRYP2_DMA_IN_IRQHandler          DMA2_Stream6_IRQHandler
#define CRYP2_IN_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define CRYP2_IN_DMA_INSTANCE            DMA2_Stream6
#define CRYP2_IN_DMA_CHANNEL             DMA_REQUEST_CRYP2_IN
#define CRYP2_IN_DMA_IRQ                 DMA2_Stream6_IRQn    
#endif

/* DMA2 stream7 */
#if defined(BSP_USING_HASH) && !defined(HASH2_IN_DMA_INSTANCE)
#define HASH2_DMA_IN_IRQHandler          DMA2_Stream7_IRQHandler
#define HASH2_IN_DMA_RCC                 RCC_MC_AHB2ENSETR_DMA2EN
#define HASH2_IN_DMA_INSTANCE            DMA2_Stream7
#define HASH2_IN_DMA_CHANNEL             DMA_REQUEST_HASH2_IN
#define HASH2_IN_DMA_IRQ                 DMA2_Stream7_IRQn  
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
