/**
  *********************************************************************************
  *
  * @file    ald_pis.h
  * @brief   Header file of PIS driver.
  *
  * @version V1.0
  * @date    03 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          03 Mar. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#ifndef __ALD_PIS_H__
#define __ALD_PIS_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup PIS
  * @{
  */

/**
  * @brief Producer entry
  */
/** @defgroup PIS_Public_Types PIS Public Types
  * @verbatim
      In PIS module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      TIMER0 ----> AD16C4T
      TIMER4 ----> BS16T
      TIMER5 ----> GP16C4T0
      TIMER6 ----> GP16C4T1
      TIMER7 ----> GP16C4T2
    @endverbatim
  * @{
  */
typedef enum {
    ALD_PIS_NON                 = 0x0U,     /**< No async */
    ALD_PIS_GPIO_PIN0           = 0x10U,    /**< Pin0, level,support async */
    ALD_PIS_GPIO_PIN1           = 0x11U,    /**< Pin1, level,support async */
    ALD_PIS_GPIO_PIN2           = 0x12U,    /**< Pin2, level,support async */
    ALD_PIS_GPIO_PIN3           = 0x13U,    /**< Pin3, level,support async */
    ALD_PIS_GPIO_PIN4           = 0x14U,    /**< Pin4, level,support async */
    ALD_PIS_GPIO_PIN5           = 0x15U,    /**< Pin5, level,support async */
    ALD_PIS_GPIO_PIN6           = 0x16U,    /**< Pin6, level,support async */
    ALD_PIS_GPIO_PIN7           = 0x17U,    /**< Pin7, level,support async */
    ALD_PIS_GPIO_PIN8           = 0x18U,    /**< Pin8, level,support async */
    ALD_PIS_GPIO_PIN9           = 0x19U,    /**< Pin9, level,support async */
    ALD_PIS_GPIO_PIN10          = 0x1aU,    /**< Pin10, level,support async */
    ALD_PIS_GPIO_PIN11          = 0x1bU,    /**< Pin11, level,support async */
    ALD_PIS_GPIO_PIN12          = 0x1cU,    /**< Pin12, level,support async */
    ALD_PIS_GPIO_PIN13          = 0x1dU,    /**< Pin13, level,support async */
    ALD_PIS_GPIO_PIN14          = 0x1eU,    /**< Pin14, level,support async */
    ALD_PIS_GPIO_PIN15          = 0x1fU,    /**< Pin15, level,support async */
    ALD_PIS_CLK_HSCO            = 0x20U,    /**< CLK: HSCO, level,support async */
    ALD_PIS_CLK_LSCO            = 0x21U,    /**< CLK: LSCO, level,support async */
    ALD_PIS_CLK_BUZ             = 0x22U,    /**< PCLK: BUZ, level,support async */
    ALD_PIS_ADC0_INSERT         = 0x60U,    /**< ADC0 insert, pclk2 pulse,support async */
    ALD_PIS_ADC0_NORMAL         = 0x61U,    /**< ADC0 normal, pclk2 pulse,support async */
    ALD_PIS_ADC0_AWDT           = 0x62U,    /**< ADC0 AWDT */
    ALD_PIS_LVD                 = 0x70U,    /**< LVD, level,support async */
    ALD_PIS_UART0_RESERVE0      = 0x80U,    /**< Uart0 reserve bit 0 */
    ALD_PIS_UART0_RESERVE1      = 0x81U,    /**< Uart0 reserve bit 1 */
    ALD_PIS_UART0_RESERVE2      = 0x82U,    /**< Uart0 reserve bit 2 */
    ALD_PIS_UART0_RTSOUT        = 0x83U,    /**< Uart0 rtsout, level */
    ALD_PIS_UART0_TXOUT         = 0x84U,    /**< Uart0 txout, level */
    ALD_PIS_UART0_SYN_SEND      = 0x85U,    /**< Uart0 syn send, pulse */
    ALD_PIS_UART0_SYN_RECV      = 0x86U,    /**< Uart0 syn recv, pulse */
    ALD_PIS_UART1_RESERVE0      = 0x90U,    /**< Uart1 reserve bit 0 */
    ALD_PIS_UART1_RESERVE1      = 0x91U,    /**< Uart1 reserve bit 1 */
    ALD_PIS_UART1_RESERVE2      = 0x92U,    /**< Uart1 reserve bit 2 */
    ALD_PIS_UART1_RTSOUT        = 0x93U,    /**< Uart1 rtsout, level */
    ALD_PIS_UART1_TXOUT         = 0x94U,    /**< Uart1 txout, level  */
    ALD_PIS_UART1_SYN_SEND      = 0x95U,    /**< Uart1 syn send, pulse  */
    ALD_PIS_UART1_SYN_RECV      = 0x96U,    /**< Uart1 syn recv, pulse  */
    ALD_PIS_UART2_RESERVE0      = 0xa0U,    /**< Uart2 reserve bit 0 */
    ALD_PIS_UART2_RESERVE1      = 0xa1U,    /**< Uart2 reserve bit 1 */
    ALD_PIS_UART2_RESERVE2      = 0xa2U,    /**< Uart2 reserve bit 2 */
    ALD_PIS_UART2_RTSOUT        = 0xa3U,    /**< Uart2 rtsout, level  */
    ALD_PIS_UART2_TXOUT         = 0xa4U,    /**< Uart2 txout, level  */
    ALD_PIS_UART2_SYN_SEND      = 0xa5U,    /**< Uart2 syn send, pulse  */
    ALD_PIS_UART2_SYN_RECV      = 0xa6U,    /**< Uart2 syn recv, pulse  */
    ALD_PIS_UART3_RESERVE0      = 0xb0U,    /**< Uart3 reserve bit 0 */
    ALD_PIS_UART3_RESERVE1      = 0xb1U,    /**< Uart3 reserve bit 1 */
    ALD_PIS_UART3_RESERVE2      = 0xb2U,    /**< Uart3 reserve bit 2 */
    ALD_PIS_UART3_RTSOUT        = 0xb3U,    /**< Uart3 rtsout, level  */
    ALD_PIS_UART3_TXOUT         = 0xb4U,    /**< Uart3 txout, level  */
    ALD_PIS_UART3_SYN_SEND      = 0xb5U,    /**< Uart3 syn send, pulse  */
    ALD_PIS_UART3_SYN_RECV      = 0xb6U,    /**< Uart3 syn recv, pulse  */
    ALD_PIS_UART4_RESERVE0      = 0xc0U,    /**< Uart4 reserve bit 0 */
    ALD_PIS_UART4_RESERVE1      = 0xc1U,    /**< Uart4 reserve bit 1 */
    ALD_PIS_UART4_RESERVE2      = 0xc2U,    /**< Uart4 reserve bit 2 */
    ALD_PIS_UART4_RTSOUT        = 0xc3U,    /**< Uart4 rtsout, level  */
    ALD_PIS_UART4_TXOUT         = 0xc4U,    /**< Uart4 txout, level  */
    ALD_PIS_UART4_SYN_SEND      = 0xc5U,    /**< Uart4 syn send, pulse  */
    ALD_PIS_UART4_SYN_RECV      = 0xc6U,    /**< Uart4 syn recv, pulse  */
    ALD_PIS_SPI0_RECV           = 0xe0U,    /**< Spi0 recv, plck1 pulse */
    ALD_PIS_SPI0_SEND           = 0xe1U,    /**< Spi0 send, plck1 pulse */
    ALD_PIS_SPI0_NE             = 0xe2U,    /**< Spi0 ne, plck1 level */
    ALD_PIS_SPI1_RECV           = 0xf0U,    /**< Spi1 recv, plck1 pulse */
    ALD_PIS_SPI1_SEND           = 0xf1U,    /**< Spi1 send, plck1 pulse */
    ALD_PIS_SPI1_NE             = 0xf2U,    /**< Spi1 ne, plck1 level */
    ALD_PIS_I2C0_RECV           = 0x100U,   /**< I2c0 recv, plck1 level */
    ALD_PIS_I2C0_SEND           = 0x101U,   /**< I2c0 send, plck1 level */
    ALD_PIS_I2C1_RECV           = 0x110U,   /**< I2c1 recv, plck1 level */
    ALD_PIS_I2C1_SEND           = 0x111U,   /**< I2c1 send, plck1 level */
    ALD_PIS_TIMER0_UPDATA       = 0x120U,   /**< Timer0 updata, plck1 pulse */
    ALD_PIS_TIMER0_TRIG         = 0x121U,   /**< Timer0 trig, plck1 pulse */
    ALD_PIS_TIMER0_INPUT_1      = 0x122U,   /**< Timer0 chan1 input catch, plck1 pulse */
    ALD_PIS_TIMER0_OUTPUT_1     = 0x122U,   /**< Timer0 chan1 output compare, plck1 pulse */
    ALD_PIS_TIMER0_INPUT_2      = 0x124U,   /**< Timer0 chan2 input catch, plck1 pulse */
    ALD_PIS_TIMER0_OUTPUT_2     = 0x124U,   /**< Timer0 chan2 output compare, plck1 pulse */
    ALD_PIS_TIMER0_INPUT_3      = 0x126U,   /**< Timer0 chan3 input catch, plck1 pulse */
    ALD_PIS_TIMER0_OUTPUT_3     = 0x126U,   /**< Timer0 chan3 output compare, plck1 pulse */
    ALD_PIS_TIMER0_INPUT_4      = 0x128U,   /**< Timer0 chan4 input catch, plck1 pulse */
    ALD_PIS_TIMER0_OUTPUT_4     = 0x128U,   /**< Timer0 chan4 output compare, plck1 pulse */
    ALD_PIS_TIMER5_UPDATA       = 0x1c0U,   /**< Timer5 updata, plck1 pulse */
    ALD_PIS_TIMER5_TRIG         = 0x1c1U,   /**< Timer5 trig, plck1 pulse */
    ALD_PIS_TIMER5_INPUT_1      = 0x1c2U,   /**< Timer5 chan1 input catch, plck1 pulse */
    ALD_PIS_TIMER5_OUTPUT_1     = 0x1c2U,   /**< Timer5 chan1 output compare, plck1 pulse */
    ALD_PIS_TIMER5_INPUT_2      = 0x1c4U,   /**< Timer5 chan2 input catch, plck1 pulse */
    ALD_PIS_TIMER5_OUTPUT_2     = 0x1c4U,   /**< Timer5 chan2 output compare, plck1 pulse */
    ALD_PIS_TIMER5_INPUT_3      = 0x1c6U,   /**< Timer5 chan3 input catch, plck1 pulse */
    ALD_PIS_TIMER5_OUTPUT_3     = 0x1c6U,   /**< Timer5 chan3 output compare, plck1 pulse */
    ALD_PIS_TIMER5_INPUT_4      = 0x1c8U,   /**< Timer5 chan4 input catch, plck1 pulse */
    ALD_PIS_TIMER5_OUTPUT_4     = 0x1c8U,   /**< Timer5 chan4 output compare, plck1 pulse */
    ALD_PIS_TIMER6_UPDATA       = 0x1d0U,   /**< Timer6 updata, plck1 pulse */
    ALD_PIS_TIMER6_TRIG         = 0x1d1U,   /**< Timer6 trig, plck1 pulse */
    ALD_PIS_TIMER6_INPUT_1      = 0x1d2U,   /**< Timer6 chan1 input catch, plck1 pulse */
    ALD_PIS_TIMER6_OUTPUT_1     = 0x1d2U,   /**< Timer6 chan1 output compare, plck1 pulse */
    ALD_PIS_TIMER6_INPUT_2      = 0x1d4U,   /**< Timer6 chan2 input catch, plck1 pulse */
    ALD_PIS_TIMER6_OUTPUT_2     = 0x1d4U,   /**< Timer6 chan2 output compare, plck1 pulse */
    ALD_PIS_TIMER6_INPUT_3      = 0x1d6U,   /**< Timer6 chan3 input catch, plck1 pulse */
    ALD_PIS_TIMER6_OUTPUT_3     = 0x1d6U,   /**< Timer6 chan3 output compare, plck1 pulse */
    ALD_PIS_TIMER6_INPUT_4      = 0x1d8U,   /**< Timer6 chan4 input catch, plck1 pulse */
    ALD_PIS_TIMER6_OUTPUT_4     = 0x1d8U,   /**< Timer6 chan4 output compare, plck1 pulse */
    ALD_PIS_TIMER7_UPDATA       = 0x1e0U,   /**< Timer7 updata, plck1 pulse */
    ALD_PIS_TIMER7_TRIG         = 0x1e1U,   /**< Timer7 trig, plck1 pulse */
    ALD_PIS_TIMER7_INPUT_1      = 0x1e2U,   /**< Timer7 chan1 input catch, plck1 pulse */
    ALD_PIS_TIMER7_OUTPUT_1     = 0x1e2U,   /**< Timer7 chan1 output compare, plck1 pulse */
    ALD_PIS_TIMER7_INPUT_2      = 0x1e4U,   /**< Timer7 chan2 input catch, plck1 pulse */
    ALD_PIS_TIMER7_OUTPUT_2     = 0x1e4U,   /**< Timer7 chan2 output compare, plck1 pulse */
    ALD_PIS_TIMER7_INPUT_3      = 0x1e6U,   /**< Timer7 chan3 input catch, plck1 pulse */
    ALD_PIS_TIMER7_OUTPUT_3     = 0x1e6U,   /**< Timer7 chan3 output compare, plck1 pulse */
    ALD_PIS_TIMER7_INPUT_4      = 0x1e8U,   /**< Timer7 chan4 input catch, plck1 pulse */
    ALD_PIS_TIMER7_OUTPUT_4     = 0x1e8U,   /**< Timer7 chan4 output compare, plck1 pulse */
    ALD_PIS_TIMER4_UPDATA       = 0x1b0U,   /**< Timer4 updata, plck1 pulse */
    ALD_PIS_TIMER4_TRIG         = 0x1b1U,   /**< Timer4 trig, plck1 pulse */
    ALD_PIS_DMA_CH0             = 0x190U,    /**< DMA CH0 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH1             = 0x191U,    /**< DMA CH1 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH2             = 0x192U,    /**< DMA CH2 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH3             = 0x193U,    /**< DMA CH3 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH4             = 0x194U,    /**< DMA CH4 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH5             = 0x195U,    /**< DMA CH5 complete, plck1 pulse, support async */
    ALD_PIS_DMA_CH6             = 0x196U,    /**< DMA CH6 complete, plck1 pulse, support async */
    ALD_PIS_DMA_ALL             = 0x19fU,    /**< DMA all channel complete, plck1 pulse, support async */
} ald_pis_src_t;

/**
  * @brief Consumer entry
  */
/** @defgroup PIS_Public_Types PIS Public Types
  * @verbatim
      In PIS module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      TIMER0 ----> AD16C4T
      TIMER1 ----> GP16C4T0
      TIMER2 ----> GP16C4T1
      TIMER3 ----> GP16C4T2
    @endverbatim
  * @{
  */
typedef enum {
    ALD_PIS_CH4_TIMER0_ITR0   = 0x0034U,    /** Tim0 internal input chan0 */
    ALD_PIS_CH5_TIMER0_ITR1   = 0x0035U,    /** Tim0 internal input chan1 */
    ALD_PIS_CH6_TIMER0_ITR2   = 0x0036U,    /** Tim0 internal input chan2 */
    ALD_PIS_CH7_TIMER0_ITR3   = 0x0037U,    /** Tim0 internal input chan3 */
    ALD_PIS_CH4_TIMER1_ITR0   = 0x0034U,    /** Tim1 internal input chan0 */
    ALD_PIS_CH5_TIMER1_ITR1   = 0x0035U,    /** Tim1 internal input chan1 */
    ALD_PIS_CH6_TIMER1_ITR2   = 0x0036U,    /** Tim1 internal input chan2 */
    ALD_PIS_CH7_TIMER1_ITR3   = 0x0037U,    /** Tim1 internal input chan3 */
    ALD_PIS_CH4_TIMER2_ITR0   = 0x0034U,    /** Tim2 internal input chan0 */
    ALD_PIS_CH5_TIMER2_ITR1   = 0x0035U,    /** Tim2 internal input chan1 */
    ALD_PIS_CH6_TIMER2_ITR2   = 0x0036U,    /** Tim2 internal input chan2 */
    ALD_PIS_CH7_TIMER2_ITR3   = 0x0037U,    /** Tim2 internal input chan3 */
    ALD_PIS_CH4_TIMER3_ITR0   = 0x0034U,    /** Tim3 internal input chan0 */
    ALD_PIS_CH5_TIMER3_ITR1   = 0x0035U,    /** Tim3 internal input chan1 */
    ALD_PIS_CH6_TIMER3_ITR2   = 0x0036U,    /** Tim3 internal input chan2 */
    ALD_PIS_CH7_TIMER3_ITR3   = 0x0037U,    /** Tim3 internal input chan3 */
    ALD_PIS_CH4_ADC0_NORMAL   = 0x0034U,    /** ADC0 normal transform */
    ALD_PIS_CH5_ADC0_INSERT   = 0x0035U,    /** ADC0 insert transform */
    ALD_PIS_CH7_DMA_REQUEST   = 0x0037U,    /** DMA request 7 */
    ALD_PIS_CH7_UART4_RXD     = 0x0417U,    /**< Uart4 Rx data */
    ALD_PIS_CH6_UART3_RXD     = 0x0316U,    /**< Uart3 Rx data */
    ALD_PIS_CH5_UART2_RXD     = 0x0215U,    /**< Uart2 Rx data */
    ALD_PIS_CH4_UART1_RXD     = 0x0114U,    /**< Uart1 Rx data */
    ALD_PIS_CH3_UART0_RXD     = 0x0013U,    /**< Uart0 Rx data  */
    ALD_PIS_CH4_TIMER3_CH4IN  = 0x1B04U,    /**< Tim3 input chan4 */
    ALD_PIS_CH4_TIMER2_CH4IN  = 0x1304U,    /**< Tim2 input chan4 */
    ALD_PIS_CH3_SPI1_CLK      = 0x0F13U,    /**< Spi1 clk */
    ALD_PIS_CH7_TIMER3_CH3IN  = 0x1A07U,    /**< Tim3 input chan3 */
    ALD_PIS_CH7_TIMER2_CH3IN  = 0x1207U,    /**< Tim2 input chan3 */
    ALD_PIS_CH2_SPI1_RX       = 0x0E12U,    /**< Spi1 rx */
    ALD_PIS_CH6_TIMER3_CH2IN  = 0x1906U,    /**< Tim3 input chan2 */
    ALD_PIS_CH6_TIMER2_CH2IN  = 0x1106U,    /**< Tim2 input chan2 */
    ALD_PIS_CH1_SPI0_CLK      = 0x0D11U,    /**< SPI0 CLK */
    ALD_PIS_CH5_TIMER3_CH1IN  = 0x1805U,    /**< Tim3 input chan1 */
    ALD_PIS_CH5_TIMER2_CH1IN  = 0x1005U,    /**< Tim2 input chan1 */
    ALD_PIS_CH0_SPI0_RX       = 0x0C10U,    /**< SPI0 RX */
    ALD_PIS_CH4_TIMER1_CH4IN  = 0x0B04U,    /**< Tim1 input chan4 */
    ALD_PIS_CH4_TIMER0_CH4IN  = 0x0304U,    /**< Tim0 input chan4 */
    ALD_PIS_CH3_TIMER1_CH3IN  = 0x0A03U,    /**< Tim1 input chan3 */
    ALD_PIS_CH3_TIMER0_CH3IN  = 0x0203U,    /**< Tim0 input chan3 */
    ALD_PIS_CH2_TIMER1_CH2IN  = 0x0902U,    /**< Tim1 input chan2 */
    ALD_PIS_CH2_TIMER0_CH2IN  = 0x0102U,    /**< Tim0 input chan2 */
    ALD_PIS_CH1_TIMER1_CH1IN  = 0x0801U,    /**< Tim1 input chan1 */
    ALD_PIS_CH1_TIMER0_CH1IN  = 0x0001U,    /**< Tim0 input chan1 */
    ALD_PIS_CH0_TIMER0_BRKIN  = 0x0400U,    /**< Tim0 break in */
    ALD_PIS_TRIG_RESERVE      = 0xFFFFU,    /**< Other Consumer */
} ald_pis_trig_t;

/**
  * @brief Clock select
  */
typedef enum {
    ALD_PIS_CLK_PCLK     = 0U,  /**< APB peripherals clock */
    ALD_PIS_CLK_HCLK     = 2U,  /**< AHB peripherals clock */
    ALD_PIS_CLK_RESERVE  = 3U,  /**< reserve clock */
} ald_pis_clock_t;

/**
  * @brief Level select
  */
typedef enum {
    ALD_PIS_EDGE_NONE    = 0U,  /**< None edge */
    ALD_PIS_EDGE_UP      = 1U,  /**< Up edge */
    ALD_PIS_EDGE_DOWN    = 2U,  /**< Down edge */
    ALD_PIS_EDGE_UP_DOWN = 3U,  /**< Up and down edge */
} ald_pis_edge_t;

/**
  * @brief Output style
  */
typedef enum {
    ALD_PIS_OUT_LEVEL = 0U, /**< Level */
    ALD_PIS_OUT_PULSE = 1U, /**< Pulse */
} ald_pis_output_t;
/**
  * @brief Sync select
  */
typedef enum {
    ALD_PIS_SYN_DIRECT         = 0U,    /**< Direct */
    ALD_PIS_SYN_LEVEL_ASY_APB  = 1U,    /**< Producer level signal and Consumer in APB */
    ALD_PIS_SYN_LEVEL_ASY_AHB  = 3U,    /**< Producer level signal and Consumer in AHB */
    ALD_PIS_SYN_PULSE_ASY_APB  = 4U,    /**< Producer Pulse signal and Consumer in APB */
    ALD_PIS_SYN_PULSE_ASY_AHB  = 6U,    /**< Producer Pulse signal and Consumer in AHB */
} ald_pis_syncsel_t;

/**
  * @brief Pis channel
  */
typedef enum {
    ALD_PIS_CH_0 = 0U,  /**< Channel 0 */
    ALD_PIS_CH_1 = 1U,  /**< Channel 1 */
    ALD_PIS_CH_2 = 2U,  /**< Channel 2 */
    ALD_PIS_CH_3 = 3U,  /**< Channel 3 */
    ALD_PIS_CH_4 = 4U,  /**< Channel 4 */
    ALD_PIS_CH_5 = 5U,  /**< Channel 5 */
    ALD_PIS_CH_6 = 6U,  /**< Channel 6 */
    ALD_PIS_CH_7 = 7U,  /**< Channel 7 */
} ald_pis_ch_t;

/**
  * @brief Pis output channel
  */
typedef enum {
    ALD_PIS_OUT_CH_0 = 0U,  /**< Channel 0 */
    ALD_PIS_OUT_CH_1 = 1U,  /**< Channel 1 */
    ALD_PIS_OUT_CH_2 = 2U,  /**< Channel 2 */
    ALD_PIS_OUT_CH_3 = 3U,  /**< Channel 3 */
    ALD_PIS_OUT_CH_4 = 4U,  /**< Channel 4 */
    ALD_PIS_OUT_CH_5 = 5U,  /**< Channel 5 */
    ALD_PIS_OUT_CH_6 = 6U,  /**< Channel 6 */
    ALD_PIS_OUT_CH_7 = 7U,  /**< Channel 7 */
} ald_pis_out_ch_t;

/**
  * @brief Indirect value,no care of it.
  */
typedef enum {
    ALD_PIS_CON_0    = 0U,  /**< Con 0 */
    ALD_PIS_CON_1    = 1U,  /**< Con 1 */
    ALD_PIS_CON_NONE = 2U,  /**< None */
} ald_pis_con_t;

/**
  * @brief PIS state structures definition
  */
typedef enum {
    ALD_PIS_STATE_RESET   = 0x00U,  /**< Peripheral is not initialized */
    ALD_PIS_STATE_READY   = 0x01U,  /**< Peripheral Initialized and ready for use */
    ALD_PIS_STATE_BUSY    = 0x02U,  /**< An internal process is ongoing */
    ALD_PIS_STATE_TIMEOUT = 0x03U,  /**< Timeout state */
    ALD_PIS_STATE_ERROR   = 0x04U,  /**< Error */
} ald_pis_state_t;

/**
  * @brief PIS modulate target
  */
typedef enum {
    ALD_PIS_UART0_TX   = 0U,    /**< Modulate uart0 tx */
    ALD_PIS_UART1_TX   = 1U,    /**< Modulate uart1 tx */
    ALD_PIS_UART2_TX   = 2U,    /**< Modulate uart2 tx */
    ALD_PIS_UART3_TX   = 3U,    /**< Modulate uart3 tx */
    ALD_PIS_UART4_TX   = 4U,    /**< Modulate uart4 tx */
} ald_pis_modu_targ_t;

/**
  * @brief PIS modulate level
  */
typedef enum {
    ALD_PIS_LOW_LEVEL  = 0U,    /**< Modulate low level */
    ALD_PIS_HIGH_LEVEL = 1U,    /**< Modulate high level */
} ald_pis_modu_level_t;

/**
  * @brief PIS modulate source
  */
typedef enum {
    ALD_PIS_SRC_NONE   = 0U,    /**< Stop modulate */
    ALD_PIS_SRC_TIMER0 = 1U,    /**< Modulate source is TIMER0 */
    ALD_PIS_SRC_TIMER5 = 4U,    /**< Modulate source is TIMER5 */
    ALD_PIS_SRC_TIMER6 = 5U,    /**< Modulate source is TIMER6 */
    ALD_PIS_SRC_TIMER7 = 6U,    /**< Modulate source is TIMER7 */
    ALD_PIS_SRC_BUZ    = 8U,    /**< Modulate source is buz */
} ald_pis_modu_src_t;

/**
  * @brief PIS modulate channel
  */
typedef enum {
    ALD_PIS_TIMER_CH1 = 0U, /**< Src is TIMERx and choose channel 1 */
    ALD_PIS_TIMER_CH2 = 1U, /**< Src is TIMERx and choose channel 2 */
    ALD_PIS_TIMER_CH3 = 2U, /**< Src is TIMERx and choose channel 3 */
    ALD_PIS_TIMER_CH4 = 3U, /**< Src is TIMERx and choose channel 4 */
} ald_pis_modu_channel_t;

/**
  * @brief PIS input channel choose
  */
typedef enum {
    ALD_PIS_NONE_INPUT = 0U,    /**< Consumer input none */
    ALD_PIS_PORT_INPUT = 1U,    /**< Consumer input choose external port */
    ALD_PIS_CHAN_INPUT = 2U,    /**< Consumer input choose pis channel */
} ald_pis_input_sel_t;

/**
  * @brief PIS init structure definition
  */
typedef struct {
    ald_pis_src_t producer_src;         /**< Producer entry */
    ald_pis_output_t producer_signal;   /**< Producer signal mode */
    ald_pis_clock_t producer_clk;       /**< Producer module clock */
    ald_pis_edge_t producer_edge;       /**< Producer module pin output edge */
    ald_pis_trig_t consumer_trig;       /**< Consumer entry */
    ald_pis_clock_t consumer_clk;       /**< Consumer clock */
    ald_pis_input_sel_t input_chan;     /**< Consumer input channel */
} ald_pis_init_t;

/**
  * @brief PIS modulate config structure definition
  */
typedef struct {
    ald_pis_modu_targ_t target;     /**< Modulate target */
    ald_pis_modu_level_t level;     /**< Modulate level */
    ald_pis_modu_src_t src;         /**< Modulate src */
    ald_pis_modu_channel_t channel; /**< Modulate channel */
} ald_pis_modulate_config_t;

/**
  * @brief  PIS Handle Structure definition
  */
typedef struct ald_pis_handle_s {
    PIS_TypeDef *perh;      /**< Register base address */
    ald_pis_init_t init;        /**< PIS required parameters */
    ald_pis_ch_t consumer_ch;       /**< Indirect value, no care of it */
    ald_pis_con_t consumer_con;     /**< Indirect value, no care of it */
    uint8_t consumer_pos;           /**< Indirect value, no care of it */
    uint32_t check_info;        /**< When destroy a handle ,user need check whether is right that ready to destroy */
    lock_state_t lock;      /**< Locking object */
    ald_pis_state_t state;      /**< PIS operation state */
} ald_pis_handle_t;
/**
  * @}
  */


/** @defgroup PIS_Private_Macros PIS Private Macros
  * @{
  */
#define IS_PIS(x)       (((x) == PIS))
#define IS_PIS_SRC(x)       (((x) == ALD_PIS_NON)       || \
                 ((x) == ALD_PIS_GPIO_PIN0)     || \
                 ((x) == ALD_PIS_GPIO_PIN1)     || \
                 ((x) == ALD_PIS_GPIO_PIN2)     || \
                 ((x) == ALD_PIS_GPIO_PIN3)     || \
                 ((x) == ALD_PIS_GPIO_PIN4)     || \
                 ((x) == ALD_PIS_GPIO_PIN5)     || \
                 ((x) == ALD_PIS_GPIO_PIN6)     || \
                 ((x) == ALD_PIS_GPIO_PIN7)     || \
                 ((x) == ALD_PIS_GPIO_PIN8)     || \
                 ((x) == ALD_PIS_GPIO_PIN9)     || \
                 ((x) == ALD_PIS_GPIO_PIN10)    || \
                 ((x) == ALD_PIS_GPIO_PIN11)    || \
                 ((x) == ALD_PIS_GPIO_PIN12)    || \
                 ((x) == ALD_PIS_GPIO_PIN13)    || \
                 ((x) == ALD_PIS_GPIO_PIN14)    || \
                 ((x) == ALD_PIS_GPIO_PIN15)    || \
                 ((x) == ALD_PIS_CLK_HSCO)      || \
                 ((x) == ALD_PIS_CLK_LSCO)      || \
                 ((x) == ALD_PIS_CLK_BUZ)       || \
                 ((x) == ALD_PIS_ADC0_INSERT)       || \
                 ((x) == ALD_PIS_ADC0_NORMAL)   || \
                 ((x) == ALD_PIS_ADC0_AWDT) || \
                 ((x) == ALD_PIS_LVD)   || \
                 ((x) == ALD_PIS_UART0_RESERVE0)        || \
                 ((x) == ALD_PIS_UART0_RESERVE1)    || \
                 ((x) == ALD_PIS_UART0_RESERVE2)    || \
                 ((x) == ALD_PIS_UART0_RTSOUT)  || \
                 ((x) == ALD_PIS_UART0_TXOUT)   || \
                 ((x) == ALD_PIS_UART0_SYN_SEND)    || \
                 ((x) == ALD_PIS_UART0_SYN_RECV)    || \
                 ((x) == ALD_PIS_UART1_RESERVE0)    || \
                 ((x) == ALD_PIS_UART1_RESERVE1)    || \
                 ((x) == ALD_PIS_UART1_RESERVE2)    || \
                 ((x) == ALD_PIS_UART1_RTSOUT)      || \
                 ((x) == ALD_PIS_UART1_TXOUT)   || \
                 ((x) == ALD_PIS_UART1_SYN_SEND)    || \
                 ((x) == ALD_PIS_UART1_SYN_RECV)    || \
                 ((x) == ALD_PIS_UART2_RESERVE0)    || \
                 ((x) == ALD_PIS_UART2_RESERVE1)    || \
                 ((x) == ALD_PIS_UART2_RESERVE2)    || \
                 ((x) == ALD_PIS_UART2_RTSOUT)  || \
                 ((x) == ALD_PIS_UART2_TXOUT)       || \
                 ((x) == ALD_PIS_UART2_SYN_SEND)    || \
                 ((x) == ALD_PIS_UART2_SYN_RECV)    || \
                 ((x) == ALD_PIS_UART3_RESERVE0)    || \
                 ((x) == ALD_PIS_UART3_RESERVE1)    || \
                 ((x) == ALD_PIS_UART3_RESERVE2)    || \
                 ((x) == ALD_PIS_UART3_RTSOUT)      || \
                 ((x) == ALD_PIS_UART3_TXOUT)   || \
                 ((x) == ALD_PIS_UART3_SYN_SEND)    || \
                 ((x) == ALD_PIS_UART3_SYN_RECV)    || \
                 ((x) == ALD_PIS_UART4_RESERVE0)    || \
                 ((x) == ALD_PIS_UART4_RESERVE1)    || \
                 ((x) == ALD_PIS_UART4_RESERVE2)    || \
                 ((x) == ALD_PIS_UART4_RTSOUT)  || \
                 ((x) == ALD_PIS_UART4_TXOUT)   || \
                 ((x) == ALD_PIS_UART4_SYN_SEND)    || \
                 ((x) == ALD_PIS_UART4_SYN_RECV)        || \
                 ((x) == ALD_PIS_SPI0_RECV)     || \
                 ((x) == ALD_PIS_SPI0_SEND)     || \
                 ((x) == ALD_PIS_SPI0_NE)       || \
                 ((x) == ALD_PIS_SPI1_RECV)     || \
                 ((x) == ALD_PIS_SPI1_SEND)     || \
                 ((x) == ALD_PIS_SPI1_NE)       || \
                 ((x) == ALD_PIS_I2C0_RECV)     || \
                 ((x) == ALD_PIS_I2C0_SEND)     || \
                 ((x) == ALD_PIS_I2C1_RECV)     || \
                 ((x) == ALD_PIS_I2C1_SEND)     || \
                 ((x) == ALD_PIS_TIMER0_UPDATA) || \
                 ((x) == ALD_PIS_TIMER0_TRIG)   || \
                 ((x) == ALD_PIS_TIMER0_INPUT_1)    || \
                 ((x) == ALD_PIS_TIMER0_OUTPUT_1)   || \
                 ((x) == ALD_PIS_TIMER0_INPUT_2)    || \
                 ((x) == ALD_PIS_TIMER0_OUTPUT_2)   || \
                 ((x) == ALD_PIS_TIMER0_INPUT_3)    || \
                 ((x) == ALD_PIS_TIMER0_OUTPUT_3)   || \
                 ((x) == ALD_PIS_TIMER0_INPUT_4)    || \
                 ((x) == ALD_PIS_TIMER0_OUTPUT_4)   || \
                 ((x) == ALD_PIS_TIMER5_UPDATA) || \
                 ((x) == ALD_PIS_TIMER5_TRIG)   || \
                 ((x) == ALD_PIS_TIMER5_INPUT_1)    || \
                 ((x) == ALD_PIS_TIMER5_OUTPUT_1)   || \
                 ((x) == ALD_PIS_TIMER5_INPUT_2)    || \
                 ((x) == ALD_PIS_TIMER5_OUTPUT_2)   || \
                 ((x) == ALD_PIS_TIMER5_INPUT_3)    || \
                 ((x) == ALD_PIS_TIMER5_OUTPUT_3)   || \
                 ((x) == ALD_PIS_TIMER5_INPUT_4)    || \
                 ((x) == ALD_PIS_TIMER5_OUTPUT_4)   || \
                 ((x) == ALD_PIS_TIMER6_UPDATA) || \
                 ((x) == ALD_PIS_TIMER6_TRIG)   || \
                 ((x) == ALD_PIS_TIMER6_INPUT_1)    || \
                 ((x) == ALD_PIS_TIMER6_OUTPUT_1)   || \
                 ((x) == ALD_PIS_TIMER6_INPUT_2)    || \
                 ((x) == ALD_PIS_TIMER6_OUTPUT_2)   || \
                 ((x) == ALD_PIS_TIMER6_INPUT_3)    || \
                 ((x) == ALD_PIS_TIMER6_OUTPUT_3)   || \
                 ((x) == ALD_PIS_TIMER6_INPUT_4)    || \
                 ((x) == ALD_PIS_TIMER6_OUTPUT_4)   || \
                 ((x) == ALD_PIS_TIMER7_UPDATA)     || \
                 ((x) == ALD_PIS_TIMER7_TRIG)       || \
                 ((x) == ALD_PIS_TIMER7_INPUT_1)    || \
                 ((x) == ALD_PIS_TIMER7_OUTPUT_1)   || \
                 ((x) == ALD_PIS_TIMER7_INPUT_2)    || \
                 ((x) == ALD_PIS_TIMER7_OUTPUT_2)   || \
                 ((x) == ALD_PIS_TIMER7_INPUT_3)    || \
                 ((x) == ALD_PIS_TIMER7_OUTPUT_3)   || \
                 ((x) == ALD_PIS_TIMER7_INPUT_4)    || \
                 ((x) == ALD_PIS_TIMER7_OUTPUT_4)   || \
                 ((x) == ALD_PIS_TIMER4_UPDATA)         || \
                 ((x) == ALD_PIS_TIMER4_TRIG)         || \
                 ((x) == ALD_PIS_DMA_CH0) || \
                 ((x) == ALD_PIS_DMA_CH1) || \
                 ((x) == ALD_PIS_DMA_CH2)    || \
                 ((x) == ALD_PIS_DMA_CH3)    || \
                 ((x) == ALD_PIS_DMA_CH4)    || \
                 ((x) == ALD_PIS_DMA_CH5)    || \
                 ((x) == ALD_PIS_DMA_CH6)                 || \
                 ((x) == ALD_PIS_DMA_ALL))
#define IS_PIS_TRIG(x)      (((x) == ALD_PIS_CH4_TIMER0_ITR0)  || \
                 ((x) == ALD_PIS_CH5_TIMER0_ITR1)  || \
                 ((x) == ALD_PIS_CH6_TIMER0_ITR2)  || \
                 ((x) == ALD_PIS_CH7_TIMER0_ITR3)  || \
                 ((x) == ALD_PIS_CH4_TIMER1_ITR0)  || \
                 ((x) == ALD_PIS_CH5_TIMER1_ITR1)  || \
                 ((x) == ALD_PIS_CH6_TIMER1_ITR2)  || \
                 ((x) == ALD_PIS_CH7_TIMER1_ITR3)  || \
                 ((x) == ALD_PIS_CH4_TIMER2_ITR0)  || \
                 ((x) == ALD_PIS_CH5_TIMER2_ITR1)  || \
                 ((x) == ALD_PIS_CH6_TIMER2_ITR2)  || \
                 ((x) == ALD_PIS_CH7_TIMER2_ITR3)  || \
                 ((x) == ALD_PIS_CH4_TIMER3_ITR0)  || \
                 ((x) == ALD_PIS_CH5_TIMER3_ITR1)  || \
                 ((x) == ALD_PIS_CH6_TIMER3_ITR2)  || \
                 ((x) == ALD_PIS_CH7_TIMER3_ITR3)  || \
                 ((x) == ALD_PIS_CH4_ADC0_NORMAL )  || \
                 ((x) == ALD_PIS_CH5_ADC0_INSERT)   || \
                 ((x) == ALD_PIS_CH7_DMA_REQUEST)   || \
                 ((x) == ALD_PIS_CH7_UART4_RXD)   || \
                 ((x) == ALD_PIS_CH6_UART3_RXD) || \
                 ((x) == ALD_PIS_CH5_UART2_RXD) || \
                 ((x) == ALD_PIS_CH4_UART1_RXD) || \
                 ((x) == ALD_PIS_CH3_UART0_RXD) || \
                 ((x) == ALD_PIS_CH4_TIMER3_CH4IN) || \
                 ((x) == ALD_PIS_CH4_TIMER2_CH4IN) || \
                 ((x) == ALD_PIS_CH3_SPI1_CLK) || \
                 ((x) == ALD_PIS_CH7_TIMER3_CH3IN) || \
                 ((x) == ALD_PIS_CH7_TIMER2_CH3IN)   || \
                 ((x) == ALD_PIS_CH2_SPI1_RX)  || \
                 ((x) == ALD_PIS_CH6_TIMER3_CH2IN)    || \
                 ((x) == ALD_PIS_CH6_TIMER2_CH2IN)    || \
                 ((x) == ALD_PIS_CH1_SPI0_CLK)    || \
                 ((x) == ALD_PIS_CH5_TIMER3_CH1IN)    || \
                 ((x) == ALD_PIS_CH5_TIMER2_CH1IN)    || \
                 ((x) == ALD_PIS_CH0_SPI0_RX)     || \
                 ((x) == ALD_PIS_CH4_TIMER1_CH4IN)  || \
                 ((x) == ALD_PIS_CH4_TIMER0_CH4IN)  || \
                 ((x) == ALD_PIS_CH3_TIMER1_CH3IN)      || \
                 ((x) == ALD_PIS_CH3_TIMER0_CH3IN)  || \
                 ((x) == ALD_PIS_CH2_TIMER1_CH2IN)  || \
                 ((x) == ALD_PIS_CH2_TIMER0_CH2IN)       || \
                 ((x) == ALD_PIS_CH1_TIMER1_CH1IN)  || \
                 ((x) == ALD_PIS_CH1_TIMER0_CH1IN)  || \
                 ((x) == ALD_PIS_CH0_TIMER0_BRKIN)      || \
                 ((x) == ALD_PIS_TRIG_RESERVE)      || \
                 ((x) <= 0x7U))
#define IS_PIS_CLOCK(x)     (((x) == ALD_PIS_CLK_PCLK)  || \
                 ((x) == ALD_PIS_CLK_HCLK)  || \
                 ((x) == ALD_PIS_CLK_RESERVE))
#define IS_PIS_SIGNAL_MODE(x)   (((x) == ALD_PIS_OUT_LEVEL)  || \
                 ((x) == ALD_PIS_OUT_PULSE))
#define IS_PIS_EDGE(x)      (((x) == ALD_PIS_EDGE_NONE) || \
                 ((x) == ALD_PIS_EDGE_UP)   || \
                 ((x) == ALD_PIS_EDGE_DOWN) || \
                 ((x) == ALD_PIS_EDGE_UP_DOWN))
#define IS_PIS_OUTPUT(x)    (((x) == ALD_PIS_OUT_LEVEL) || \
                 ((x) == ALD_PIS_OUT_PULSE))
#define IS_PIS_OUPUT_CH(x)  (((x) == ALD_PIS_OUT_CH_0) || \
                 ((x) == ALD_PIS_OUT_CH_1) || \
                 ((x) == ALD_PIS_OUT_CH_2) || \
                 ((x) == ALD_PIS_OUT_CH_3) || \
                 ((x) == ALD_PIS_OUT_CH_4) || \
                 ((x) == ALD_PIS_OUT_CH_5) || \
                 ((x) == ALD_PIS_OUT_CH_6) || \
                 ((x) == ALD_PIS_OUT_CH_7))
#define IS_PIS_MODU_TARGET(x)   (((x) == ALD_PIS_UART0_TX) || \
                 ((x) == ALD_PIS_UART1_TX) || \
                 ((x) == ALD_PIS_UART2_TX) || \
                 ((x) == ALD_PIS_UART3_TX) || \
                 ((x) == ALD_PIS_UART4_TX))
#define IS_PIS_MODU_LEVEL(x)    (((x) == ALD_PIS_LOW_LEVEL) || \
                 ((x) == ALD_PIS_HIGH_LEVEL))
#define IS_PIS_MODU_SRC(x)  (((x) == ALD_PIS_SRC_NONE)     || \
                 ((x) == ALD_PIS_SRC_TIMER0)   || \
                 ((x) == ALD_PIS_SRC_TIMER5)   || \
                 ((x) == ALD_PIS_SRC_TIMER6)   || \
                 ((x) == ALD_PIS_SRC_TIMER7)   || \
                 ((x) == ALD_PIS_SRC_BUZ))
#define IS_PIS_MODU_CHANNEL(x)  (((x) == ALD_PIS_TIMER_CH1) || \
                 ((x) == ALD_PIS_TIMER_CH2) || \
                 ((x) == ALD_PIS_TIMER_CH3) || \
                 ((x) == ALD_PIS_TIMER_CH4))
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions
  * @{
  */

/** @addtogroup PIS_Public_Functions_Group1
  * @{
  */
ald_status_t ald_pis_create(ald_pis_handle_t *hperh);
ald_status_t ald_pis_destroy(ald_pis_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group2
  * @{
  */
ald_status_t ald_pis_output_start(ald_pis_handle_t *hperh, ald_pis_out_ch_t ch);
ald_status_t ald_pis_output_stop(ald_pis_handle_t *hperh, ald_pis_out_ch_t ch);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group3
  * @{
  */
ald_pis_state_t ald_pis_get_state(ald_pis_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group4
  * @{
  */
ald_status_t ald_pis_modu_config(ald_pis_handle_t *hperh, ald_pis_modulate_config_t *config);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ALD_PIS_H__ */
