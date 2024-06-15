/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-05     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1 */

/* DMA1 channel2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI1_RX_DMA_INSTANCE            DMA1_Channel2
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_1
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI1_TX_DMA_INSTANCE            DMA1_Channel3
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_1
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#elif defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_DMA_RX_IRQHandler         DMA1_Channel3_IRQHandler
#define UART3_RX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define UART3_RX_DMA_INSTANCE           DMA1_Channel3
#define UART3_RX_DMA_REQUEST            DMA_REQUEST_2
#define UART3_RX_DMA_IRQ                DMA1_Channel3_IRQn
#endif

/* DMA1 channel4 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler         DMA1_Channel4_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define UART1_TX_DMA_INSTANCE           DMA1_Channel4
#define UART1_TX_DMA_REQUEST            DMA_REQUEST_2
#define UART1_TX_DMA_IRQ                DMA1_Channel4_IRQn
#elif defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE            DMA1_Channel4
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_1
#define SPI2_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 channel5 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         DMA1_Channel5_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define UART1_RX_DMA_INSTANCE           DMA1_Channel5
#define UART1_RX_DMA_REQUEST            DMA_REQUEST_USART1_RX//DMA_REQUEST_2
#define UART1_RX_DMA_IRQ                DMA1_Channel5_IRQn
#elif defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler             DMA1_Channel5_IRQHandler
#define QSPI_DMA_RCC                    RCC_AHB1ENR_DMA1EN
#define QSPI_DMA_INSTANCE               DMA1_Channel5
#define QSPI_DMA_REQUEST                DMA_REQUEST_5
#define QSPI_DMA_IRQ                    DMA1_Channel5_IRQn
#elif defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI2_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE            DMA1_Channel5
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_1
#define SPI2_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

/* DMA1 channel6 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler         DMA1_Channel6_IRQHandler
#define UART2_RX_DMA_RCC                RCC_AHB1ENR_DMA1EN
#define UART2_RX_DMA_INSTANCE           DMA1_Channel6
#define UART2_RX_DMA_REQUEST            DMA_REQUEST_USART2_RX//DMA_REQUEST_2
#define UART2_RX_DMA_IRQ                DMA1_Channel6_IRQn
#endif

/* DMA1 channel7 */

/* DMA2 channel1 */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART5_DMA_TX_IRQHandler         DMA2_Channel1_IRQHandler
#define UART5_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART5_TX_DMA_INSTANCE           DMA2_Channel1
#define UART5_TX_DMA_REQUEST            DMA_REQUEST_2
#define UART5_TX_DMA_IRQ                DMA2_Channel1_IRQn
#endif

/* DMA2 channel2 */
#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_INSTANCE)
#define UART5_DMA_RX_IRQHandler         DMA2_Channel2_IRQHandler
#define UART5_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART5_RX_DMA_INSTANCE           DMA2_Channel2
#define UART5_RX_DMA_REQUEST            DMA_REQUEST_2
#define UART5_RX_DMA_IRQ                DMA2_Channel2_IRQn
#endif

/* DMA2 channel3 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler          DMA2_Channel3_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE            DMA2_Channel3
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_4
#define SPI1_RX_DMA_IRQ                 DMA2_Channel3_IRQn
#endif

/* DMA2 channel4 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler          DMA2_Channel4_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1ENR_DMA2EN
#define SPI1_TX_DMA_INSTANCE            DMA2_Channel4
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_4
#define SPI1_TX_DMA_IRQ                 DMA2_Channel4_IRQn
#endif

/* DMA2 channel5 */

/* DMA2 channel6 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler         DMA2_Channel6_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART1_TX_DMA_INSTANCE           DMA2_Channel6
#define UART1_TX_DMA_REQUEST            DMA_REQUEST_2
#define UART1_TX_DMA_IRQ                DMA2_Channel6_IRQn
#endif

/* DMA2 channel7 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         DMA2_Channel7_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART1_RX_DMA_INSTANCE           DMA2_Channel7
#define UART1_RX_DMA_REQUEST            DMA_REQUEST_2
#define UART1_RX_DMA_IRQ                DMA2_Channel7_IRQn
#elif defined(BSP_QSPI_USING_DMA) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_IRQHandler             DMA2_Channel7_IRQHandler
#define QSPI_DMA_RCC                    RCC_AHB1ENR_DMA2EN
#define QSPI_DMA_INSTANCE               DMA2_Channel7
#define QSPI_DMA_REQUEST                DMA_REQUEST_3
#define QSPI_DMA_IRQ                    DMA2_Channel7_IRQn
#elif defined(BSP_LPUART1_RX_USING_DMA) && !defined(LPUART1_RX_DMA_INSTANCE)
#define LPUART1_DMA_RX_IRQHandler       DMA2_Channel7_IRQHandler
#define LPUART1_RX_DMA_RCC              RCC_AHB1ENR_DMA2EN
#define LPUART1_RX_DMA_INSTANCE         DMA2_Channel7
#define LPUART1_RX_DMA_REQUEST          DMA_REQUEST_LPUART1_RX
#define LPUART1_RX_DMA_IRQ              DMA2_Channel7_IRQn
#endif

/* DMA2 channel6 */
#if defined(BSP_LPUART1_TX_USING_DMA) && !defined(LPUART1_TX_DMA_INSTANCE)
#define LPUART1_DMA_TX_IRQHandler         DMA2_Channel6_IRQHandler
#define LPUART1_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define LPUART1_TX_DMA_INSTANCE           DMA2_Channel6
#define LPUART1_TX_DMA_REQUEST            DMA_REQUEST_LPUART1_TX
#define LPUART1_TX_DMA_IRQ                DMA2_Channel6_IRQn
#endif


#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
