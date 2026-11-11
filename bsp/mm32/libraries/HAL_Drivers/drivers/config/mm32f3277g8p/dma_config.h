/**
 * @file dma_config.h
 * @author 100ask development team
 * @brief
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022 Chongqing 100ASK Technology Co., LTD
 *
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel1 */
#if defined(BSP_ADC1_USING_DMA) && !defined(ADC1_DMA_INSTANCE)
#define ADC1_DMA_INSTANCE               DMA1
#define ADC1_DMA_REQ                    DMA_REQ_DMA1_ADC1
#define ADC1_DMA_IRQ                    DMA1_CH1_IRQn
#define ADC1_DMA_IRQHandler             DMA1_Channel1_IRQHandler
#define ADC1_DMA_RCC                    RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_DMA_INSTANCE              DMA1
#define UART6_RX_DMA_REQ                DMA_REQ_DMA1_UART6_RX
#define UART6_RX_DMA_IRQ                DMA1_CH1_IRQn
#define UART6_DMA_RX_IRQHandler         DMA1_Channel1_IRQHandler
#define UART6_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel2 */
#if defined(BSP_ADC2_USING_DMA) && !defined(ADC2_DMA_INSTANCE)
#define ADC2_DMA_INSTANCE               DMA1
#define ADC2_DMA_REQ                    DMA_REQ_DMA1_ADC2
#define ADC2_DMA_IRQ                    DMA1_CH2_IRQn
#define ADC2_DMA_IRQHandler             DMA1_Channel2_IRQHandler
#define ADC2_DMA_RCC                    RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_RX_DMA_INSTANCE            DMA1
#define SPI1_RX_DMA_REQ                 DMA_REQ_DMA1_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA1_CH2_IRQn
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_INSTANCE)
#define UART3_TX_DMA_INSTANCE           DMA1
#define UART3_TX_DMA_REQ                DMA_REQ_DMA1_UART3_TX
#define UART3_TX_DMA_IRQ                DMA1_CH2_IRQn
#define UART3_DMA_TX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART3_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_TX_DMA_INSTANCE            DMA1
#define SPI1_TX_DMA_REQ                 DMA_REQ_DMA1_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_CH3_IRQn
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_RX_DMA_INSTANCE           DMA1
#define UART3_RX_DMA_REQ                DMA_REQ_DMA1_UART3_RX
#define UART3_RX_DMA_IRQ                DMA1_CH3_IRQn
#define UART3_DMA_RX_IRQHandler         DMA1_Channel3_IRQHandler
#define UART3_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel4 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_RX_DMA_INSTANCE            DMA1
#define SPI2_RX_DMA_REQ                 DMA_REQ_DMA1_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_CH4_IRQn
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_RX_DMA_RCC                 RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_TX_DMA_INSTANCE           DMA1
#define UART1_TX_DMA_REQ                DMA_REQ_DMA1_UART1_TX
#define UART1_TX_DMA_IRQ                DMA1_CH4_IRQn
#define UART1_DMA_TX_IRQHandler         DMA1_Channel4_IRQHandler
#define UART1_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel5 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_TX_DMA_INSTANCE            DMA1
#define SPI2_TX_DMA_REQ                 DMA_REQ_DMA1_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA1_CH5_IRQn
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI2_TX_DMA_RCC                 RCC_AHB1_PERIPH_DMA1
#elif defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_RX_DMA_INSTANCE           DMA1
#define UART1_RX_DMA_REQ                DMA_REQ_DMA1_UART1_RX
#define UART1_RX_DMA_IRQ                DMA1_CH5_IRQn
#define UART1_DMA_RX_IRQHandler         DMA1_Channel5_IRQHandler
#define UART1_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel6 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART6_RX_DMA_INSTANCE           DMA1
#define UART6_RX_DMA_REQ                DMA_REQ_DMA1_UART6_RX
#define UART6_RX_DMA_IRQ                DMA1_CH6_IRQn
#define UART6_DMA_RX_IRQHandler         DMA1_Channel6_IRQHandler
#define UART6_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA1 channel7 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_TX_DMA_INSTANCE           DMA1
#define UART2_TX_DMA_REQ                DMA_REQ_DMA1_UART2_TX
#define UART2_TX_DMA_IRQ                DMA1_CH7_IRQn
#define UART2_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART2_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA1
#endif

/* DMA2 channel1 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_RX_DMA_INSTANCE            DMA2
#define SPI3_RX_DMA_REQ                 DMA_REQ_DMA2_SPI3_RX
#define SPI3_RX_DMA_IRQ                 DMA2_CH1_IRQn
#define SPI3_DMA_RX_IRQHandler          DMA2_Channel1_IRQHandler
#define SPI3_RX_DMA_RCC                 RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_INSTANCE)
#define UART5_RX_DMA_INSTANCE           DMA2
#define UART5_RX_DMA_REQ                DMA_REQ_DMA2_UART5_RX
#define UART5_RX_DMA_IRQ                DMA2_CH1_IRQn
#define UART5_DMA_RX_IRQHandler         DMA2_Channel1_IRQHandler
#define UART5_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_INSTANCE)
#define UART7_RX_DMA_INSTANCE           DMA2
#define UART7_RX_DMA_REQ                DMA_REQ_DMA2_UART7_RX
#define UART7_RX_DMA_IRQ                DMA2_CH1_IRQn
#define UART7_DMA_RX_IRQHandler         DMA2_Channel1_IRQHandler
#define UART7_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#endif

/* DMA2 channel2 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_TX_DMA_INSTANCE            DMA2
#define SPI3_TX_DMA_REQ                 DMA_REQ_DMA2_SPI3_TX
#define SPI3_TX_DMA_IRQ                 DMA2_CH2_IRQn
#define SPI3_DMA_TX_IRQHandler          DMA2_Channel2_IRQHandler
#define SPI3_TX_DMA_RCC                 RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_INSTANCE)
#define UART5_TX_DMA_INSTANCE           DMA2
#define UART5_TX_DMA_REQ                DMA_REQ_DMA2_UART5_TX
#define UART5_TX_DMA_IRQ                DMA2_CH2_IRQn
#define UART5_DMA_TX_IRQHandler         DMA2_Channel2_IRQHandler
#define UART5_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_INSTANCE)
#define UART7_TX_DMA_INSTANCE           DMA2
#define UART7_TX_DMA_REQ                DMA_REQ_DMA2_UART7_TX
#define UART7_TX_DMA_IRQ                DMA2_CH2_IRQn
#define UART7_DMA_TX_IRQHandler         DMA2_Channel2_IRQHandler
#define UART7_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#endif

/* DMA2 channel3 */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_RX_DMA_INSTANCE           DMA2
#define UART4_RX_DMA_REQ                DMA_REQ_DMA2_UART4_RX
#define UART4_RX_DMA_IRQ                DMA2_CH3_IRQn
#define UART4_DMA_RX_IRQHandler         DMA2_Channel3_IRQHandler
#define UART4_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART8_RX_USING_DMA) && !defined(UART8_RX_DMA_INSTANCE)
#define UART8_RX_DMA_INSTANCE           DMA2
#define UART8_RX_DMA_REQ                DMA_REQ_DMA2_UART8_RX
#define UART8_RX_DMA_IRQ                DMA2_CH3_IRQn
#define UART8_DMA_RX_IRQHandler         DMA2_Channel3_IRQHandler
#define UART8_RX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#endif

/* DMA2 channel4 */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_TX_DMA_INSTANCE           DMA2
#define UART6_TX_DMA_REQ                DMA_REQ_DMA2_UART6_TX
#define UART6_TX_DMA_IRQ                DMA2_CH4_IRQn
#define UART6_DMA_TX_IRQHandler         DMA2_Channel4_IRQHandler
#define UART6_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#endif

/* DMA2 channel5 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_INSTANCE)
#define UART4_TX_DMA_INSTANCE           DMA2
#define UART4_TX_DMA_REQ                DMA_REQ_DMA2_UART4_TX
#define UART4_TX_DMA_IRQ                DMA2_CH5_IRQn
#define UART4_DMA_TX_IRQHandler         DMA2_Channel5_IRQHandler
#define UART4_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#elif defined(BSP_UART8_TX_USING_DMA) && !defined(UART8_TX_DMA_INSTANCE)
#define UART8_TX_DMA_INSTANCE           DMA2
#define UART8_TX_DMA_REQ                DMA_REQ_DMA2_UART8_TX
#define UART8_TX_DMA_IRQ                DMA2_CH5_IRQn
#define UART8_DMA_TX_IRQHandler         DMA2_Channel5_IRQHandler
#define UART8_TX_DMA_RCC                RCC_AHB1_PERIPH_DMA2
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */

