/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-02     FMD-AE       first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1  */

/* DMA1 channel2-3 DMA2 channel1-2 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler          DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#define UART1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART1_RX_DMA_INSTANCE            DMA1_Channel3
#define UART1_RX_DMA_IRQ                 DMA1_Ch2_3_DMA2_Ch1_2_IRQn
#elif defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_TX_IRQHandler       DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI1_RX_DMA_IRQ                 DMA1_Ch2_3_DMA2_Ch1_2_IRQn
#endif

#if  defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_RX_TX_IRQHandler       DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_IRQ                 DMA1_Ch2_3_DMA2_Ch1_2_IRQn
#endif
/* DMA1 channel2-3 DMA2 channel1-2 */

/* DMA1 channel4-7 DMA2 channel3-5 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Channel5
#define UART2_RX_DMA_IRQ                 DMA1_Ch4_7_DMA2_Ch3_5_IRQn
#endif
/* DMA1 channel4-7 DMA2 channel3-5 */

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
