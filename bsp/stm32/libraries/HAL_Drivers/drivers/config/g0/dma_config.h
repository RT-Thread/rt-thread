/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

#if defined(STM32G030xx) || defined(STM32G031xx) || defined(STM32G041xx)
#define DMA_Channelx_IRQn               DMA1_Ch4_5_DMAMUX1_OVR_IRQn
#define DMA_Channelx_IRQHandler         DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler
#elif defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define DMA_Channelx_IRQn               DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn
#define DMA_Channelx_IRQHandler         DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler
#else
#define DMA_Channelx_IRQn               DMA1_Ch4_7_DMAMUX1_OVR_IRQn
#define DMA_Channelx_IRQHandler         DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
#endif

/* DMA1 channel2  */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_TX_IRQHandler       DMA1_Channel2_3_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_3_IRQn
#elif defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_TX_IRQHandler       DMA1_Channel2_3_IRQHandler
#define SPI2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_Channel2_3_IRQn
#endif

/* DMA1 channle3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_RX_TX_IRQHandler       DMA1_Channel2_3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel2_3_IRQn
#elif defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_RX_TX_IRQHandler       DMA1_Channel2_3_IRQHandler
#define SPI2_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA1_Channel2_3_IRQn
#endif

/* DMA1 channle4 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHBENR_DMA1EN
#define UART1_RX_DMA_INSTANCE           DMA1_Channel4
#define UART1_RX_DMA_REQUEST            DMA_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                DMA_Channelx_IRQn
#elif defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define SPI2_RX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE            DMA1_Channel4
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA_Channelx_IRQn
#endif

/* DMA1 channle5 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHBENR_DMA1EN
#define UART1_TX_DMA_INSTANCE           DMA1_Channel5
#define UART1_TX_DMA_REQUEST            DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                DMA_Channelx_IRQn
#elif defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define SPI2_TX_DMA_RCC                 RCC_AHBENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE            DMA1_Channel5
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA_Channelx_IRQn
#endif

#if !(defined(STM32G030xx) || defined(STM32G031xx) || defined(STM32G041xx))
/* DMA1 channle6 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define UART2_RX_DMA_RCC                RCC_AHBENR_DMA1EN
#define UART2_RX_DMA_INSTANCE           DMA1_Channel6
#define UART2_RX_DMA_REQUEST            DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                DMA_Channelx_IRQn
#endif

/* DMA1 channle7 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART_DMA_RX_TX_IRQHandler       DMA_Channelx_IRQHandler
#define UART2_TX_DMA_RCC                RCC_AHBENR_DMA1EN
#define UART2_TX_DMA_INSTANCE           DMA1_Channel7
#define UART2_TX_DMA_REQUEST            DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                DMA_Channelx_IRQn
#endif
#endif

/* DMA1 channle1 */
#if defined(BSP_LPUART1_RX_USING_DMA) && !defined(LPUART1_RX_DMA_INSTANCE)
#define LPUART1_DMA_RX_IRQHandler       DMA1_Channel1_IRQHandler
#define LPUART1_RX_DMA_RCC              RCC_AHBENR_DMA1EN
#define LPUART1_RX_DMA_INSTANCE         DMA1_Channel1
#define LPUART1_RX_DMA_REQUEST          DMA_REQUEST_LPUART1_RX
#define LPUART1_RX_DMA_IRQ              DMA1_Channel1_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
