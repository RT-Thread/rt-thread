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

/* DMA1 stream0 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_DMA_RX_IRQHandler           DMA1_Stream0_IRQHandler
#define SPI3_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_RX_DMA_INSTANCE             DMA1_Stream0
#define SPI3_RX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI3_RX_DMA_IRQ                  DMA1_Stream0_IRQn
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_INSTANCE)
#define I2C1_DMA_RX_IRQHandler          DMA1_Stream0_IRQHandler
#define I2C1_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C1_RX_DMA_INSTANCE            DMA1_Stream0
#define I2C1_RX_DMA_CHANNEL             DMA_CHANNEL_1
#define I2C1_RX_DMA_IRQ                 DMA1_Stream0_IRQn
#elif defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_INSTANCE)
#define UART5_DMA_RX_IRQHandler          DMA1_Stream0_IRQHandler
#define UART5_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART5_RX_DMA_INSTANCE            DMA1_Stream0
#define UART5_RX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART5_RX_DMA_IRQ                 DMA1_Stream0_IRQn
#elif defined(BSP_UART8_TX_USING_DMA) && !defined(UART8_TX_DMA_INSTANCE)
#define UART8_DMA_TX_IRQHandler          DMA1_Stream0_IRQHandler
#define UART8_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART8_TX_DMA_INSTANCE            DMA1_Stream0
#define UART8_TX_DMA_CHANNEL             DMA_CHANNEL_5
#define UART8_TX_DMA_IRQ                 DMA1_Stream0_IRQn
#endif

/* DMA1 stream1 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_DMA_RX_IRQHandler          DMA1_Stream1_IRQHandler
#define UART3_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART3_RX_DMA_INSTANCE            DMA1_Stream1
#define UART3_RX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART3_RX_DMA_IRQ                 DMA1_Stream1_IRQn
#elif defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_INSTANCE)
#define UART7_DMA_TX_IRQHandler          DMA1_Stream1_IRQHandler
#define UART7_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART7_TX_DMA_INSTANCE            DMA1_Stream1
#define UART7_TX_DMA_CHANNEL             DMA_CHANNEL_5
#define UART7_TX_DMA_IRQ                 DMA1_Stream1_IRQn
#endif

/* DMA1 stream2 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_DMA_RX_IRQHandler           DMA1_Stream2_IRQHandler
#define SPI3_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_RX_DMA_INSTANCE             DMA1_Stream2
#define SPI3_RX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI3_RX_DMA_IRQ                  DMA1_Stream2_IRQn
#elif defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_INSTANCE)
#define I2C3_DMA_RX_IRQHandler          DMA1_Stream2_IRQHandler
#define I2C3_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C3_RX_DMA_INSTANCE            DMA1_Stream2
#define I2C3_RX_DMA_CHANNEL             DMA_CHANNEL_3
#define I2C3_RX_DMA_IRQ                 DMA1_Stream2_IRQn
#elif defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_DMA_RX_IRQHandler          DMA1_Stream2_IRQHandler
#define UART4_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART4_RX_DMA_INSTANCE            DMA1_Stream2
#define UART4_RX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART4_RX_DMA_IRQ                 DMA1_Stream2_IRQn
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_INSTANCE)
#define I2C2_DMA_RX_IRQHandler          DMA1_Stream2_IRQHandler
#define I2C2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C2_RX_DMA_INSTANCE            DMA1_Stream2
#define I2C2_RX_DMA_CHANNEL             DMA_CHANNEL_7
#define I2C2_RX_DMA_IRQ                 DMA1_Stream2_IRQn
#endif

/* DMA1 stream3 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler
#define SPI2_RX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_RX_DMA_INSTANCE             DMA1_Stream3
#define SPI2_RX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI2_RX_DMA_IRQ                  DMA1_Stream3_IRQn
#elif defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_INSTANCE)
#define UART3_DMA_TX_IRQHandler          DMA1_Stream3_IRQHandler
#define UART3_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART3_TX_DMA_INSTANCE            DMA1_Stream3
#define UART3_TX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART3_TX_DMA_IRQ                 DMA1_Stream3_IRQn
#elif defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_INSTANCE)
#define UART7_DMA_RX_IRQHandler          DMA1_Stream3_IRQHandler
#define UART7_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART7_RX_DMA_INSTANCE            DMA1_Stream3
#define UART7_RX_DMA_CHANNEL             DMA_CHANNEL_5
#define UART7_RX_DMA_IRQ                 DMA1_Stream3_IRQn
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_INSTANCE)
#define I2C2_DMA_RX_IRQHandler          DMA1_Stream3_IRQHandler
#define I2C2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C2_RX_DMA_INSTANCE            DMA1_Stream3
#define I2C2_RX_DMA_CHANNEL             DMA_CHANNEL_7
#define I2C2_RX_DMA_IRQ                 DMA1_Stream3_IRQn
#endif

/* DMA1 stream4 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#define SPI2_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI2_TX_DMA_INSTANCE             DMA1_Stream4
#define SPI2_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI2_TX_DMA_IRQ                  DMA1_Stream4_IRQn
#elif defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_INSTANCE)
#define I2C3_DMA_TX_IRQHandler          DMA1_Stream4_IRQHandler
#define I2C3_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C3_TX_DMA_INSTANCE            DMA1_Stream4
#define I2C3_TX_DMA_CHANNEL             DMA_CHANNEL_3
#define I2C3_TX_DMA_IRQ                 DMA1_Stream4_IRQn
#elif defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_INSTANCE)
#define UART4_DMA_TX_IRQHandler          DMA1_Stream4_IRQHandler
#define UART4_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART4_TX_DMA_INSTANCE            DMA1_Stream4
#define UART4_TX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART4_TX_DMA_IRQ                 DMA1_Stream4_IRQn
#elif defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_INSTANCE)
#define UART3_DMA_TX_IRQHandler          DMA1_Stream4_IRQHandler
#define UART3_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART3_TX_DMA_INSTANCE            DMA1_Stream4
#define UART3_TX_DMA_CHANNEL             DMA_CHANNEL_7
#define UART3_TX_DMA_IRQ                 DMA1_Stream4_IRQn
#endif

/* DMA1 stream5 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream5_IRQHandler
#define SPI3_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_TX_DMA_INSTANCE             DMA1_Stream5
#define SPI3_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI3_TX_DMA_IRQ                  DMA1_Stream5_IRQn
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_INSTANCE)
#define I2C1_DMA_RX_IRQHandler          DMA1_Stream5_IRQHandler
#define I2C1_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C1_RX_DMA_INSTANCE            DMA1_Stream5
#define I2C1_RX_DMA_CHANNEL             DMA_CHANNEL_1
#define I2C1_RX_DMA_IRQ                 DMA1_Stream5_IRQn
#elif defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler          DMA1_Stream5_IRQHandler
#define UART2_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART2_RX_DMA_INSTANCE            DMA1_Stream5
#define UART2_RX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART2_RX_DMA_IRQ                 DMA1_Stream5_IRQn
#endif

/* DMA1 stream6 */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_INSTANCE)
#define I2C1_DMA_TX_IRQHandler          DMA1_Stream6_IRQHandler
#define I2C1_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C1_TX_DMA_INSTANCE            DMA1_Stream6
#define I2C1_TX_DMA_CHANNEL             DMA_CHANNEL_1
#define I2C1_TX_DMA_IRQ                 DMA1_Stream6_IRQn
#elif defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_DMA_TX_IRQHandler          DMA1_Stream6_IRQHandler
#define UART2_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART2_TX_DMA_INSTANCE            DMA1_Stream6
#define UART2_TX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART2_TX_DMA_IRQ                 DMA1_Stream6_IRQn
#elif defined(BSP_UART8_RX_USING_DMA) && !defined(UART8_RX_DMA_INSTANCE)
#define UART8_DMA_RX_IRQHandler          DMA1_Stream6_IRQHandler
#define UART8_RX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART8_RX_DMA_INSTANCE            DMA1_Stream6
#define UART8_RX_DMA_CHANNEL             DMA_CHANNEL_5
#define UART8_RX_DMA_IRQ                 DMA1_Stream6_IRQn
#endif

/* DMA1 stream7 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler           DMA1_Stream7_IRQHandler
#define SPI3_TX_DMA_RCC                  RCC_AHB1ENR_DMA1EN
#define SPI3_TX_DMA_INSTANCE             DMA1_Stream7
#define SPI3_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPI3_TX_DMA_IRQ                  DMA1_Stream7_IRQn
#elif defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_INSTANCE)
#define I2C1_DMA_TX_IRQHandler          DMA1_Stream7_IRQHandler
#define I2C1_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C1_TX_DMA_INSTANCE            DMA1_Stream7
#define I2C1_TX_DMA_CHANNEL             DMA_CHANNEL_1
#define I2C1_TX_DMA_IRQ                 DMA1_Stream7_IRQn
#elif defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART5_DMA_TX_IRQHandler          DMA1_Stream7_IRQHandler
#define UART5_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define UART5_TX_DMA_INSTANCE            DMA1_Stream7
#define UART5_TX_DMA_CHANNEL             DMA_CHANNEL_4
#define UART5_TX_DMA_IRQ                 DMA1_Stream7_IRQn
#elif defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_INSTANCE)
#define I2C2_DMA_TX_IRQHandler          DMA1_Stream7_IRQHandler
#define I2C2_TX_DMA_RCC                 RCC_AHB1ENR_DMA1EN
#define I2C2_TX_DMA_INSTANCE            DMA1_Stream7
#define I2C2_TX_DMA_CHANNEL             DMA_CHANNEL_7
#define I2C2_TX_DMA_IRQ                 DMA1_Stream7_IRQn
#endif

/* DMA2 stream0 */
#if defined(BSP_ADC1_USING_DMA) && !defined(ADC1_DMA_INSTANCE)
#define ADC1_DMA_IRQHandler           DMA2_Stream0_IRQHandler
#define ADC1_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC1_DMA_INSTANCE             DMA2_Stream0
#define ADC1_DMA_CHANNEL              DMA_CHANNEL_0
#define ADC1_DMA_IRQ                  DMA2_Stream0_IRQn
#elif defined(BSP_ADC3_USING_DMA) && !defined(ADC3_DMA_INSTANCE)
#define ADC3_DMA_IRQHandler           DMA2_Stream0_IRQHandler
#define ADC3_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC3_DMA_INSTANCE             DMA2_Stream0
#define ADC3_DMA_CHANNEL              DMA_CHANNEL_2
#define ADC3_DMA_IRQ                  DMA2_Stream0_IRQn
#elif defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI1_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI1_RX_DMA_CHANNEL              DMA_CHANNEL_3
#define SPI1_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#elif defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler           DMA2_Stream0_IRQHandler
#define SPI4_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_RX_DMA_INSTANCE             DMA2_Stream0
#define SPI4_RX_DMA_CHANNEL              DMA_CHANNEL_4
#define SPI4_RX_DMA_IRQ                  DMA2_Stream0_IRQn
#elif defined(BSP_MEMTOMEM0_USING_DMA) && !defined(MEMTOMEM0_DMA_INSTANCE)
#define MEMTOMEM0_DMA_IRQHandler           DMA2_Stream0_IRQHandler
#define MEMTOMEM0_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM0_DMA_INSTANCE             DMA2_Stream0
#define MEMTOMEM0_DMA_CHANNEL              DMA_CHANNEL_7
#define MEMTOMEM0_DMA_IRQ                  DMA2_Stream0_IRQn
#endif

/* DMA2 stream1 */
#if defined(BSP_ADC3_USING_DMA) && !defined(ADC3_DMA_INSTANCE)
#define ADC3_DMA_IRQHandler           DMA2_Stream1_IRQHandler
#define ADC3_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC3_DMA_INSTANCE             DMA2_Stream1
#define ADC3_DMA_CHANNEL              DMA_CHANNEL_2
#define ADC3_DMA_IRQ                  DMA2_Stream1_IRQn
#elif defined(BSP_MEMTOMEM1_USING_DMA) && !defined(MEMTOMEM1_DMA_INSTANCE)
#define MEMTOMEM1_DMA_IRQHandler           DMA2_Stream1_IRQHandler
#define MEMTOMEM1_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM1_DMA_INSTANCE             DMA2_Stream1
#define MEMTOMEM1_DMA_CHANNEL              DMA_CHANNEL_3
#define MEMTOMEM1_DMA_IRQ                  DMA2_Stream1_IRQn
#elif defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream1_IRQHandler
#define SPI4_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_TX_DMA_INSTANCE             DMA2_Stream1
#define SPI4_TX_DMA_CHANNEL              DMA_CHANNEL_4
#define SPI4_TX_DMA_IRQ                  DMA2_Stream1_IRQn
#elif defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_DMA_RX_IRQHandler          DMA2_Stream1_IRQHandler
#define UART6_RX_DMA_RCC                 RCC_AHB1ENR_DMA2EN
#define UART6_RX_DMA_INSTANCE            DMA2_Stream1
#define UART6_RX_DMA_CHANNEL             DMA_CHANNEL_5
#define UART6_RX_DMA_IRQ                 DMA2_Stream1_IRQn
#endif

/* DMA2 stream2 */
#if defined(BSP_ADC2_USING_DMA) && !defined(ADC2_DMA_INSTANCE)
#define ADC2_DMA_IRQHandler           DMA2_Stream2_IRQHandler
#define ADC2_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC2_DMA_INSTANCE             DMA2_Stream2
#define ADC2_DMA_CHANNEL              DMA_CHANNEL_1
#define ADC2_DMA_IRQ                  DMA2_Stream2_IRQn
#elif defined(BSP_MEMTOMEM2_USING_DMA) && !defined(MEMTOMEM2_DMA_INSTANCE)
#define MEMTOMEM2_DMA_IRQHandler           DMA2_Stream2_IRQHandler
#define MEMTOMEM2_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM2_DMA_INSTANCE             DMA2_Stream2
#define MEMTOMEM2_DMA_CHANNEL              DMA_CHANNEL_2
#define MEMTOMEM2_DMA_IRQ                  DMA2_Stream2_IRQn
#elif defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler
#define SPI1_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_RX_DMA_INSTANCE             DMA2_Stream2
#define SPI1_RX_DMA_CHANNEL              DMA_CHANNEL_3
#define SPI1_RX_DMA_IRQ                  DMA2_Stream2_IRQn
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         DMA2_Stream2_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART1_RX_DMA_INSTANCE           DMA2_Stream2
#define UART1_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define UART1_RX_DMA_IRQ                DMA2_Stream2_IRQn
#elif defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_DMA_RX_IRQHandler         DMA2_Stream2_IRQHandler
#define UART6_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART6_RX_DMA_INSTANCE           DMA2_Stream2
#define UART6_RX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART6_RX_DMA_IRQ                DMA2_Stream2_IRQn
#endif

/* DMA2 stream3 */
#if defined(BSP_MEMTOMEM3_USING_DMA) && !defined(MEMTOMEM3_DMA_INSTANCE)
#define MEMTOMEM3_DMA_IRQHandler           DMA2_Stream3_IRQHandler
#define MEMTOMEM3_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM3_DMA_INSTANCE             DMA2_Stream3
#define MEMTOMEM3_DMA_CHANNEL              DMA_CHANNEL_0
#define MEMTOMEM3_DMA_IRQ                  DMA2_Stream3_IRQn
#elif defined(BSP_ADC2_USING_DMA) && !defined(ADC2_DMA_INSTANCE)
#define ADC2_DMA_IRQHandler           DMA2_Stream3_IRQHandler
#define ADC2_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC2_DMA_INSTANCE             DMA2_Stream3
#define ADC2_DMA_CHANNEL              DMA_CHANNEL_1
#define ADC2_DMA_IRQ                  DMA2_Stream3_IRQn
#elif defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream3
#define SPI5_RX_DMA_CHANNEL              DMA_CHANNEL_2
#define SPI5_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#elif defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI1_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_TX_DMA_INSTANCE             DMA2_Stream3
#define SPI1_TX_DMA_CHANNEL              DMA_CHANNEL_3
#define SPI1_TX_DMA_IRQ                  DMA2_Stream3_IRQn
#elif defined(BSP_SDIO_RX_USING_DMA) && !defined(SDIO_RX_DMA_INSTANCE)
#define SDIO_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SDIO_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SDIO_RX_DMA_INSTANCE             DMA2_Stream3
#define SDIO_RX_DMA_CHANNEL              DMA_CHANNEL_4
#define SDIO_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#elif defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI4_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_RX_DMA_INSTANCE             DMA2_Stream3
#define SPI4_RX_DMA_CHANNEL              DMA_CHANNEL_5
#define SPI4_RX_DMA_IRQ                  DMA2_Stream3_IRQn
#endif

/* DMA2 stream4 */
#if defined(BSP_ADC1_USING_DMA) && !defined(ADC1_DMA_INSTANCE)
#define ADC1_DMA_IRQHandler           DMA2_Stream4_IRQHandler
#define ADC1_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define ADC1_DMA_INSTANCE             DMA2_Stream4
#define ADC1_DMA_CHANNEL              DMA_CHANNEL_0
#define ADC1_DMA_IRQ                  DMA2_Stream4_IRQn
#elif defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream4
#define SPI5_TX_DMA_CHANNEL              DMA_CHANNEL_2
#define SPI5_TX_DMA_IRQ                  DMA2_Stream4_IRQn
#elif defined(BSP_MEMTOMEM4_USING_DMA) && !defined(MEMTOMEM4_DMA_INSTANCE)
#define MEMTOMEM4_DMA_IRQHandler           DMA2_Stream4_IRQHandler
#define MEMTOMEM4_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM4_DMA_INSTANCE             DMA2_Stream4
#define MEMTOMEM4_DMA_CHANNEL              DMA_CHANNEL_4
#define MEMTOMEM4_DMA_IRQ                  DMA2_Stream4_IRQn
#elif defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler           DMA2_Stream4_IRQHandler
#define SPI4_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI4_TX_DMA_INSTANCE             DMA2_Stream4
#define SPI4_TX_DMA_CHANNEL              DMA_CHANNEL_5
#define SPI4_TX_DMA_IRQ                  DMA2_Stream4_IRQn
#endif

/* DMA2 stream5 */
#if defined(BSP_SPI6_TX_USING_DMA) && !defined(SPI6_TX_DMA_INSTANCE)
#define SPI6_DMA_TX_IRQHandler           DMA2_Stream5_IRQHandler
#define SPI6_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI6_TX_DMA_INSTANCE             DMA2_Stream5
#define SPI6_TX_DMA_CHANNEL              DMA_CHANNEL_1
#define SPI6_TX_DMA_IRQ                  DMA2_Stream5_IRQn
#elif defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler           DMA2_Stream5_IRQHandler
#define SPI1_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI1_TX_DMA_INSTANCE             DMA2_Stream5
#define SPI1_TX_DMA_CHANNEL              DMA_CHANNEL_3
#define SPI1_TX_DMA_IRQ                  DMA2_Stream5_IRQn
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         DMA2_Stream5_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART1_RX_DMA_INSTANCE           DMA2_Stream5
#define UART1_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define UART1_RX_DMA_IRQ                DMA2_Stream5_IRQn
#elif defined(BSP_MEMTOMEM5_USING_DMA) && !defined(MEMTOMEM5_DMA_INSTANCE)
#define MEMTOMEM5_DMA_IRQHandler           DMA2_Stream5_IRQHandler
#define MEMTOMEM5_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define MEMTOMEM5_DMA_INSTANCE             DMA2_Stream5
#define MEMTOMEM5_DMA_CHANNEL              DMA_CHANNEL_5
#define MEMTOMEM5_DMA_IRQ                  DMA2_Stream5_IRQn
#elif defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler           DMA2_Stream5_IRQHandler
#define SPI5_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_RX_DMA_INSTANCE             DMA2_Stream5
#define SPI5_RX_DMA_CHANNEL              DMA_CHANNEL_7
#define SPI5_RX_DMA_IRQ                  DMA2_Stream5_IRQn
#endif

/* DMA2 stream6 */
#if defined(BSP_SPI6_RX_USING_DMA) && !defined(SPI6_RX_DMA_INSTANCE)
#define SPI6_DMA_RX_IRQHandler           DMA2_Stream6_IRQHandler
#define SPI6_RX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI6_RX_DMA_INSTANCE             DMA2_Stream6
#define SPI6_RX_DMA_CHANNEL              DMA_CHANNEL_1
#define SPI6_RX_DMA_IRQ                  DMA2_Stream6_IRQn
#elif defined(BSP_MEMTOMEM6_USING_DMA) && !defined(MEMTOMEM6_DMA_INSTANCE)
#define MEMTOMEM6_DMA_IRQHandler         DMA2_Stream6_IRQHandler
#define MEMTOMEM6_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define MEMTOMEM6_DMA_INSTANCE           DMA2_Stream6
#define MEMTOMEM6_DMA_CHANNEL            DMA_CHANNEL_3
#define MEMTOMEM6_DMA_IRQ                DMA2_Stream6_IRQn
#elif defined(BSP_SDIO_TX_USING_DMA) && !defined(SDIO_TX_DMA_INSTANCE)
#define SDIO_DMA_TX_IRQHandler         DMA2_Stream6_IRQHandler
#define SDIO_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define SDIO_TX_DMA_INSTANCE           DMA2_Stream6
#define SDIO_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define SDIO_TX_DMA_IRQ                DMA2_Stream6_IRQn
#elif defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_DMA_TX_IRQHandler         DMA2_Stream6_IRQHandler
#define UART6_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART6_TX_DMA_INSTANCE           DMA2_Stream6
#define UART6_TX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART6_TX_DMA_IRQ                DMA2_Stream6_IRQn
#elif defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler           DMA2_Stream6_IRQHandler
#define SPI5_TX_DMA_RCC                  RCC_AHB1ENR_DMA2EN
#define SPI5_TX_DMA_INSTANCE             DMA2_Stream6
#define SPI5_TX_DMA_CHANNEL              DMA_CHANNEL_7
#define SPI5_TX_DMA_IRQ                  DMA2_Stream6_IRQn
#endif

/* DMA2 stream7 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler         DMA2_Stream7_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART1_TX_DMA_INSTANCE           DMA2_Stream7
#define UART1_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define UART1_TX_DMA_IRQ                DMA2_Stream7_IRQn
#elif defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_DMA_TX_IRQHandler         DMA2_Stream7_IRQHandler
#define UART6_TX_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define UART6_TX_DMA_INSTANCE           DMA2_Stream7
#define UART6_TX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART6_TX_DMA_IRQ                DMA2_Stream7_IRQn
#elif defined(BSP_MEMTOMEM7_USING_DMA) && !defined(MEMTOMEM7_DMA_INSTANCE)
#define MEMTOMEM7_DMA_IRQHandler         DMA2_Stream7_IRQHandler
#define MEMTOMEM7_DMA_RCC                RCC_AHB1ENR_DMA2EN
#define MEMTOMEM7_DMA_INSTANCE           DMA2_Stream7
#define MEMTOMEM7_DMA_CHANNEL            DMA_CHANNEL_6
#define MEMTOMEM7_DMA_IRQ                DMA2_Stream7_IRQn
#endif

#ifdef __cplusplus
}
#endif


#endif /* __DMA_CONFIG_H__ */
