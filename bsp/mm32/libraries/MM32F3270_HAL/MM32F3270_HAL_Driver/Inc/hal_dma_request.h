/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __HAL_DMA_REQUESET_H__
#define __HAL_DMA_REQUESET_H__

#if 0

#define DMA_REQ_GET_DMA_INSTANCE(code) (uint32_t)((code) >> 8u)
#define DMA_REQ_GET_DMA_CHANNEL(code)  (uint32_t)((code) & 0xFF)
#define DMA_REQ_DMA_INSTANCE(dmax)     (uint32_t)((dmax) << 8u)
#define DMA_REQ_DMA_CHANNEL(channel)   (uint32_t)((channel) & 0xFF)


#define DMA_REQ_DMA1_ADC1        0u
#define DMA_REQ_DMA1_UART6_RX    0u
#define DMA_REQ_DMA1_TIM2_CC3    0u
#define DMA_REQ_DMA1_TIM4_CC1    0u
#define DMA_REQ_DMA1_ADC2        1u
#define DMA_REQ_DMA1_SPI1_RX     1u
#define DMA_REQ_DMA1_UART3_TX    1u
#define DMA_REQ_DMA1_TIM1_CC1    1u
#define DMA_REQ_DMA1_TIM2_UP     1u
#define DMA_REQ_DMA1_TIM3_CC3    1u
#define DMA_REQ_DMA1_SPI1_TX     2u
#define DMA_REQ_DMA1_UART3_RX    2u
#define DMA_REQ_DMA1_TIM1_CC2    2u
#define DMA_REQ_DMA1_TIM3_CC4    2u
#define DMA_REQ_DMA1_TIM2_UP     2u
#define DMA_REQ_DMA1_SPI2_RX     3u
#define DMA_REQ_DMA1_UART1_TX    3u
#define DMA_REQ_DMA1_I2C2_TX     3u
#define DMA_REQ_DMA1_TIM1_CC4    3u
#define DMA_REQ_DMA1_TIM1_TRIG   3u
#define DMA_REQ_DMA1_TIM1_COM    3u
#define DMA_REQ_DMA1_TIM4_CC2    3u
#define DMA_REQ_DMA1_SPI2_TX     4u
#define DMA_REQ_DMA1_UART1_RX    4u
#define DMA_REQ_DMA1_I2C2_RX     4u
#define DMA_REQ_DMA1_TIM1_UP     4u
#define DMA_REQ_DMA1_TIM2_CC1    4u
#define DMA_REQ_DMA1_TIM4_CC3    4u
#define DMA_REQ_DMA1_UART2_RX    5u
#define DMA_REQ_DMA1_I2C1_TX     5u
#define DMA_REQ_DMA1_TIM1_CC3    5u
#define DMA_REQ_DMA1_TIM3_CC1    5u
#define DMA_REQ_DMA1_TIM3_TRIG   5u
#define DMA_REQ_DMA1_UART2_TX    6u
#define DMA_REQ_DMA1_I2C1_RX     6u
#define DMA_REQ_DMA1_TIM2_CC2    6u
#define DMA_REQ_DMA1_TIM2_CC4    6u
#define DMA_REQ_DMA1_TIM4_UP     6u

#define DMA_REQ_DMA2_SPI3_RX     0u
#define DMA_REQ_DMA2_UART5_RX    0u
#define DMA_REQ_DMA2_UART7_RX    0u
#define DMA_REQ_DMA2_TIM5_CC4    0u
#define DMA_REQ_DMA2_TIM5_TRIG   0u
#define DMA_REQ_DMA2_TIM8_CC3    0u
#define DMA_REQ_DMA2_TIM8_UP     0u
#define DMA_REQ_DMA2_SPI3_TX     1u
#define DMA_REQ_DMA2_UART5_TX    1u
#define DMA_REQ_DMA2_UART7_TX    1u
#define DMA_REQ_DMA2_TIM5_CC3    1u
#define DMA_REQ_DMA2_TIM5_UP     1u
#define DMA_REQ_DMA2_TIM8_CC4    1u
#define DMA_REQ_DMA2_TIM8_TRIG   1u
#define DMA_REQ_DMA2_TIM8_COM    1u
#define DMA_REQ_DMA2_UART4_RX    2u
#define DMA_REQ_DMA2_UART8_RX    2u
#define DMA_REQ_DMA2_TIM6_UP     2u
#define DMA_REQ_DMA2_DAC_CH1     2u
#define DMA_REQ_DMA2_TIM8_CC1    2u
#define DMA_REQ_DMA2_UART6_TX    3u
#define DMA_REQ_DMA2_SDIO        3u
#define DMA_REQ_DMA2_TIM5_CC2    3u
#define DMA_REQ_DMA2_TIM6_UP     3u
#define DMA_REQ_DMA2_DAC_CH2     3u
#define DMA_REQ_DMA2_ADC3        4u
#define DMA_REQ_DMA2_UART4_TX    4u
#define DMA_REQ_DMA2_UART8_TX    4u
#define DMA_REQ_DMA2_TIM5_CC1    4u
#define DMA_REQ_DMA2_TIM8_CC2    4u
#endif

/* ADC. */
#define DMA_REQ_DMA1_ADC1        0u
#define DMA_REQ_DMA1_ADC2        1u
#define DMA_REQ_DMA2_ADC3        4u

/* DAC. */
#define DMA_REQ_DMA2_DAC_CH1     2u
#define DMA_REQ_DMA2_DAC_CH2     3u

/* UART. */
#define DMA_REQ_DMA1_UART1_TX    3u
#define DMA_REQ_DMA1_UART1_RX    4u
#define DMA_REQ_DMA1_UART2_RX    5u
#define DMA_REQ_DMA1_UART2_TX    6u
#define DMA_REQ_DMA1_UART3_RX    2u
#define DMA_REQ_DMA1_UART3_TX    1u
#define DMA_REQ_DMA2_UART4_RX    2u
#define DMA_REQ_DMA2_UART4_TX    4u
#define DMA_REQ_DMA2_UART5_RX    0u
#define DMA_REQ_DMA2_UART5_TX    1u
#define DMA_REQ_DMA1_UART6_RX    0u
#define DMA_REQ_DMA2_UART6_TX    3u
#define DMA_REQ_DMA2_UART7_RX    0u
#define DMA_REQ_DMA2_UART7_TX    1u
#define DMA_REQ_DMA2_UART8_RX    2u
#define DMA_REQ_DMA2_UART8_TX    4u

/* SPI. */
#define DMA_REQ_DMA1_SPI1_RX     1u
#define DMA_REQ_DMA1_SPI1_TX     2u
#define DMA_REQ_DMA1_SPI2_RX     3u
#define DMA_REQ_DMA1_SPI2_TX     4u
#define DMA_REQ_DMA2_SPI3_RX     0u
#define DMA_REQ_DMA2_SPI3_TX     1u

/* I2C. */
#define DMA_REQ_DMA1_I2C1_RX     6u
#define DMA_REQ_DMA1_I2C1_TX     5u
#define DMA_REQ_DMA1_I2C2_RX     4u
#define DMA_REQ_DMA1_I2C2_TX     3u

/* TIM1. */
#define DMA_REQ_DMA1_TIM1_CC1    1u
#define DMA_REQ_DMA1_TIM1_CC2    2u
#define DMA_REQ_DMA1_TIM1_CC3    5u
#define DMA_REQ_DMA1_TIM1_CC4    3u
#define DMA_REQ_DMA1_TIM1_TRIG   3u
#define DMA_REQ_DMA1_TIM1_COM    3u
#define DMA_REQ_DMA1_TIM1_UP     4u

/* TIM2. */
#define DMA_REQ_DMA1_TIM2_CC1    4u
#define DMA_REQ_DMA1_TIM2_CC2    6u
#define DMA_REQ_DMA1_TIM2_CC3    0u
#define DMA_REQ_DMA1_TIM2_CC4    6u
#define DMA_REQ_DMA1_TIM2_UP     1u

/* TIM3. */
#define DMA_REQ_DMA1_TIM3_CC1    5u
#define DMA_REQ_DMA1_TIM3_CC3    1u
#define DMA_REQ_DMA1_TIM3_CC4    2u
#define DMA_REQ_DMA1_TIM3_UP     2u
#define DMA_REQ_DMA1_TIM3_TRIG   5u

/* TIM4. */
#define DMA_REQ_DMA1_TIM4_CC1    0u
#define DMA_REQ_DMA1_TIM4_CC2    3u
#define DMA_REQ_DMA1_TIM4_CC3    4u
#define DMA_REQ_DMA1_TIM4_UP     6u

/* TIM5. */
#define DMA_REQ_DMA2_TIM5_CC1    4u
#define DMA_REQ_DMA2_TIM5_CC2    3u
#define DMA_REQ_DMA2_TIM5_CC3    1u
#define DMA_REQ_DMA2_TIM5_CC4    0u
#define DMA_REQ_DMA2_TIM5_TRIG   0u
#define DMA_REQ_DMA2_TIM5_UP     1u

/* TIM6. */
#define DMA_REQ_DMA2_TIM6_UP     2u

/* TIM7. */
#define DMA_REQ_DMA2_TIM7_UP     3u /* DMA_REQ_DMA2_TIM7_UP */

/* TIM8. */
#define DMA_REQ_DMA2_TIM8_CC1    2u
#define DMA_REQ_DMA2_TIM8_CC2    4u
#define DMA_REQ_DMA2_TIM8_CC3    0u
#define DMA_REQ_DMA2_TIM8_CC4    1u
#define DMA_REQ_DMA2_TIM8_UP     0u
#define DMA_REQ_DMA2_TIM8_COM    1u
#define DMA_REQ_DMA2_TIM8_TRIG   1u

/* SDIO. */
#define DMA_REQ_DMA2_SDIO        3u

#endif /* __HAL_DMA_REQUESET_H__ */
