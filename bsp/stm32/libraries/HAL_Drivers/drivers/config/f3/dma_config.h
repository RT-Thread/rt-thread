/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Channel5
#define UART2_RX_DMA_CHANNEL             DMA1_Channel5_BASE
#define UART2_RX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_DMA_TX_IRQHandler          DMA1_Channel6_IRQHandler
#define UART2_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define UART2_TX_DMA_INSTANCE            DMA1_Channel6
#define UART2_TX_DMA_CHANNEL             DMA1_Channel6_BASE
#define UART2_TX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
