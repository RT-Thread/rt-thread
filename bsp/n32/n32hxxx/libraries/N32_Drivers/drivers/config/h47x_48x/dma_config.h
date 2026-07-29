/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-04-07     ox-horse         first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA)
#define UART1_RX_DMA            DMA1
#define UART1_RX_DMA_IRQHandler DMA1_Channel1_IRQHandler
#define UART1_RX_DMA_CHType     DMA1_CH1
#define UART1_RX_DMA_IRQ        DMA1_Channel1_IRQn
#define UART1_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART1_RX_DMA_REQUEST    DMA_REMAP_USART1_RX
#define UART1_RX_DMA_CHANNEL    1U
#endif

/* DMA1 channel2 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA)
#define UART2_RX_DMA            DMA1
#define UART2_RX_DMA_IRQHandler DMA1_Channel2_IRQHandler
#define UART2_RX_DMA_CHType     DMA1_CH2
#define UART2_RX_DMA_IRQ        DMA1_Channel2_IRQn
#define UART2_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART2_RX_DMA_REQUEST    DMA_REMAP_USART2_RX
#define UART2_RX_DMA_CHANNEL    2U
#endif

/* DMA1 channel3 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA)
#define UART3_RX_DMA            DMA1
#define UART3_RX_DMA_IRQHandler DMA1_Channel3_IRQHandler
#define UART3_RX_DMA_CHType     DMA1_CH3
#define UART3_RX_DMA_IRQ        DMA1_Channel3_IRQn
#define UART3_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART3_RX_DMA_REQUEST    DMA_REMAP_USART3_RX
#define UART3_RX_DMA_CHANNEL    3U
#endif

/* DMA1 channel4 */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA)
#define UART4_RX_DMA            DMA1
#define UART4_RX_DMA_IRQHandler DMA1_Channel4_IRQHandler
#define UART4_RX_DMA_CHType     DMA1_CH4
#define UART4_RX_DMA_IRQ        DMA1_Channel4_IRQn
#define UART4_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART4_RX_DMA_REQUEST    DMA_REMAP_USART4_RX
#define UART4_RX_DMA_CHANNEL    4U
#endif

/* DMA1 channel5 */
#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA)
#define UART5_RX_DMA            DMA1
#define UART5_RX_DMA_IRQHandler DMA1_Channel5_IRQHandler
#define UART5_RX_DMA_CHType     DMA1_CH5
#define UART5_RX_DMA_IRQ        DMA1_Channel5_IRQn
#define UART5_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART5_RX_DMA_REQUEST    DMA_REMAP_UART5_RX
#define UART5_RX_DMA_CHANNEL    5U
#endif

/* DMA1 channel6 */
#if defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA)
#define UART6_RX_DMA            DMA1
#define UART6_RX_DMA_IRQHandler DMA1_Channel6_IRQHandler
#define UART6_RX_DMA_CHType     DMA1_CH6
#define UART6_RX_DMA_IRQ        DMA1_Channel6_IRQn
#define UART6_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART6_RX_DMA_REQUEST    DMA_REMAP_UART6_RX
#define UART6_RX_DMA_CHANNEL    6U
#endif

/* DMA1 channel7 */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA)
#define UART7_RX_DMA            DMA1
#define UART7_RX_DMA_IRQHandler DMA1_Channel7_IRQHandler
#define UART7_RX_DMA_CHType     DMA1_CH7
#define UART7_RX_DMA_IRQ        DMA1_Channel7_IRQn
#define UART7_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART7_RX_DMA_REQUEST    DMA_REMAP_UART7_RX
#define UART7_RX_DMA_CHANNEL    7U
#endif

/* DMA1 channel8 */
#if defined(BSP_UART8_RX_USING_DMA) && !defined(UART8_RX_DMA)
#define UART8_RX_DMA            DMA1
#define UART8_RX_DMA_IRQHandler DMA1_Channel8_IRQHandler
#define UART8_RX_DMA_CHType     DMA1_CH8
#define UART8_RX_DMA_IRQ        DMA1_Channel8_IRQn
#define UART8_RX_DMA_RCC        RCC_AHB_PERIPHEN_DMA1
#define UART8_RX_DMA_REQUEST    DMA_REMAP_UART8_RX
#define UART8_RX_DMA_CHANNEL    8U
#endif

/* DMA2 channel1 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA)
#define UART1_TX_DMA            DMA2
#define UART1_TX_DMA_IRQHandler DMA2_Channel1_IRQHandler
#define UART1_TX_DMA_CHType     DMA2_CH1
#define UART1_TX_DMA_IRQ        DMA2_Channel1_IRQn
#define UART1_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART1_TX_DMA_REQUEST    DMA_REMAP_USART1_TX
#define UART1_TX_DMA_CHANNEL    1U
#endif

/* DMA2 channel2 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA)
#define UART2_TX_DMA            DMA2
#define UART2_TX_DMA_IRQHandler DMA2_Channel2_IRQHandler
#define UART2_TX_DMA_CHType     DMA2_CH2
#define UART2_TX_DMA_IRQ        DMA2_Channel2_IRQn
#define UART2_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART2_TX_DMA_REQUEST    DMA_REMAP_USART2_TX
#define UART2_TX_DMA_CHANNEL    2U
#endif

/* DMA2 channel3 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA)
#define UART3_TX_DMA            DMA2
#define I2C10_RX_DMA_IRQHandler DMA2_Channel3_IRQHandler
#define UART3_TX_DMA_CHType     DMA2_CH3
#define UART3_TX_DMA_IRQ        DMA2_Channel3_IRQn
#define UART3_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART3_TX_DMA_REQUEST    DMA_REMAP_USART3_TX
#define UART3_TX_DMA_CHANNEL    3U
#endif

/* DMA2 channel4 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA)
#define UART4_TX_DMA            DMA2
#define UART4_TX_DMA_IRQHandler DMA2_Channel4_IRQHandler
#define UART4_TX_DMA_CHType     DMA2_CH4
#define UART4_TX_DMA_IRQ        DMA2_Channel4_IRQn
#define UART4_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART4_TX_DMA_REQUEST    DMA_REMAP_USART4_TX
#define UART4_TX_DMA_CHANNEL    4U
#endif

/* DMA2 channel5 */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA)
#define UART5_TX_DMA            DMA2
#define UART5_TX_DMA_IRQHandler DMA2_Channel5_IRQHandler
#define UART5_TX_DMA_CHType     DMA2_CH5
#define UART5_TX_DMA_IRQ        DMA2_Channel5_IRQn
#define UART5_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART5_TX_DMA_REQUEST    DMA_REMAP_UART5_TX
#define UART5_TX_DMA_CHANNEL    5U
#endif

/* DMA2 channel6 */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA)
#define UART6_TX_DMA            DMA2
#define UART6_TX_DMA_IRQHandler DMA2_Channel6_IRQHandler
#define UART6_TX_DMA_CHType     DMA2_CH6
#define UART6_TX_DMA_IRQ        DMA2_Channel6_IRQn
#define UART6_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART6_TX_DMA_REQUEST    DMA_REMAP_UART6_TX
#define UART6_TX_DMA_CHANNEL    6U
#endif

/* DMA2 channel7 */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA)
#define UART7_TX_DMA            DMA2
#define UART7_TX_DMA_IRQHandler DMA2_Channel7_IRQHandler
#define UART7_TX_DMA_CHType     DMA2_CH7
#define UART7_TX_DMA_IRQ        DMA2_Channel7_IRQn
#define UART7_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART7_TX_DMA_REQUEST    DMA_REMAP_UART7_TX
#define UART7_TX_DMA_CHANNEL    7U
#endif

/* DMA2 channel8 */
#if defined(BSP_UART8_TX_USING_DMA) && !defined(UART8_TX_DMA)
#define UART8_TX_DMA            DMA2
#define UART8_TX_DMA_IRQHandler DMA2_Channel8_IRQHandler
#define UART8_TX_DMA_CHType     DMA2_CH8
#define UART8_TX_DMA_IRQ        DMA2_Channel8_IRQn
#define UART8_TX_DMA_RCC        RCC_AHB_PERIPHEN_DMA2
#define UART8_TX_DMA_REQUEST    DMA_REMAP_UART8_TX
#define UART8_TX_DMA_CHANNEL    8U
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */

