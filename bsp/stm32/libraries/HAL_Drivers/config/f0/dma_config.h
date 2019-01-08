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

/* dma1 channel1  */

/* dma1 channel1 */

/* dma1 channel2-3 DMA2 channel1-2 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_CHANNEL)
#define USART1_DMA_RX_IRQHandler          DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#define USART1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define USART1_RX_DMA_INSTANCE            DMA1_Channel3
#define USART1_RX_DMA_IRQ                 DMA1_Ch2_3_DMA2_Ch1_2_IRQn

#endif
/* dma1 channel2-3 DMA2 channel1-2 */

/* dma1 channel4-7 DMA2 channel3-5 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_CHANNEL)
#define USART2_DMA_RX_IRQHandler          DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler
#define USART2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define USART2_RX_DMA_INSTANCE            DMA1_Channel5
#define USART2_RX_DMA_IRQ                 DMA1_Ch4_7_DMA2_Ch3_5_IRQn

#endif
/* dma1 channel4-7 DMA2 channel3-5 */



#endif /* __DMA_CONFIG_H__ */
