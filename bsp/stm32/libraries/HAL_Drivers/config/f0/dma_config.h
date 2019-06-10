/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-05     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1  */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler          DMA1_Channel1_IRQHandler
#define UART1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART1_RX_DMA_INSTANCE            DMA1_Channel1
#define UART1_RX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif
/* DMA1 channel2-3 DMA2 channel1-2 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel2_3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_IRQ                 DMA1_Ch2_3_DMA2_Ch1_2_IRQn
#endif
/* DMA1 channel2-3 DMA2 channel1-2 */

/* DMA1 channel4-7 DMA2 channel3-5 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler          DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHBENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE            DMA2_Channel3
#define SPI1_RX_DMA_IRQ                 DMA1_Ch4_7_DMA2_Ch3_5_IRQn
#endif
/* DMA1 channel4-7 DMA2 channel3-5 */

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
