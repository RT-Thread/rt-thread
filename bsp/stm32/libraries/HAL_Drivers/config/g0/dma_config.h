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

/* DMA1 channel2-3 DMA2 channel1-2 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler          DMA1_Channel2_3_IRQHandler
#define UART1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART1_RX_DMA_INSTANCE            DMA1_Channel3
#define UART1_RX_DMA_IRQ                 DMA1_Channel2_3_IRQn
#endif
/* DMA1 channel2-3 DMA2 channel1-2 */

/* DMA1 channel4-7 DMA2 channel3-5 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Channel5
#define UART2_RX_DMA_IRQ                 DMA1_Ch4_7_DMAMUX1_OVR_IRQn
#endif
/* DMA1 channel4-7 DMA2 channel3-5 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_DMA_RX_IRQHandler          DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
#define UART3_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART3_RX_DMA_INSTANCE            DMA1_Channel4
#define UART3_RX_DMA_IRQ                 DMA1_Ch4_7_DMAMUX1_OVR_IRQn
#endif
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_DMA_RX_IRQHandler          DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
#define UART4_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART4_RX_DMA_INSTANCE            DMA1_Channel6
#define UART4_RX_DMA_IRQ                 DMA1_Ch4_7_DMAMUX1_OVR_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
