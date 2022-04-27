/**
 * \file
 *
 * \brief Peripheral I/O description for SAML10E15A
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10E15A_PIO_H_
#define _SAML10E15A_PIO_H_

/* ========== Peripheral I/O pin numbers ========== */
#define PIN_PA00                    (  0)  /**< Pin Number for PA00 */
#define PIN_PA01                    (  1)  /**< Pin Number for PA01 */
#define PIN_PA02                    (  2)  /**< Pin Number for PA02 */
#define PIN_PA03                    (  3)  /**< Pin Number for PA03 */
#define PIN_PA04                    (  4)  /**< Pin Number for PA04 */
#define PIN_PA05                    (  5)  /**< Pin Number for PA05 */
#define PIN_PA06                    (  6)  /**< Pin Number for PA06 */
#define PIN_PA07                    (  7)  /**< Pin Number for PA07 */
#define PIN_PA08                    (  8)  /**< Pin Number for PA08 */
#define PIN_PA09                    (  9)  /**< Pin Number for PA09 */
#define PIN_PA10                    ( 10)  /**< Pin Number for PA10 */
#define PIN_PA11                    ( 11)  /**< Pin Number for PA11 */
#define PIN_PA14                    ( 14)  /**< Pin Number for PA14 */
#define PIN_PA15                    ( 15)  /**< Pin Number for PA15 */
#define PIN_PA16                    ( 16)  /**< Pin Number for PA16 */
#define PIN_PA17                    ( 17)  /**< Pin Number for PA17 */
#define PIN_PA18                    ( 18)  /**< Pin Number for PA18 */
#define PIN_PA19                    ( 19)  /**< Pin Number for PA19 */
#define PIN_PA22                    ( 22)  /**< Pin Number for PA22 */
#define PIN_PA23                    ( 23)  /**< Pin Number for PA23 */
#define PIN_PA24                    ( 24)  /**< Pin Number for PA24 */
#define PIN_PA25                    ( 25)  /**< Pin Number for PA25 */
#define PIN_PA27                    ( 27)  /**< Pin Number for PA27 */
#define PIN_PA30                    ( 30)  /**< Pin Number for PA30 */
#define PIN_PA31                    ( 31)  /**< Pin Number for PA31 */


/* ========== Peripheral I/O masks ========== */
#define PORT_PA00                   (_U_(1) << 0) /**< PORT Mask for PA00 */
#define PORT_PA01                   (_U_(1) << 1) /**< PORT Mask for PA01 */
#define PORT_PA02                   (_U_(1) << 2) /**< PORT Mask for PA02 */
#define PORT_PA03                   (_U_(1) << 3) /**< PORT Mask for PA03 */
#define PORT_PA04                   (_U_(1) << 4) /**< PORT Mask for PA04 */
#define PORT_PA05                   (_U_(1) << 5) /**< PORT Mask for PA05 */
#define PORT_PA06                   (_U_(1) << 6) /**< PORT Mask for PA06 */
#define PORT_PA07                   (_U_(1) << 7) /**< PORT Mask for PA07 */
#define PORT_PA08                   (_U_(1) << 8) /**< PORT Mask for PA08 */
#define PORT_PA09                   (_U_(1) << 9) /**< PORT Mask for PA09 */
#define PORT_PA10                   (_U_(1) << 10) /**< PORT Mask for PA10 */
#define PORT_PA11                   (_U_(1) << 11) /**< PORT Mask for PA11 */
#define PORT_PA14                   (_U_(1) << 14) /**< PORT Mask for PA14 */
#define PORT_PA15                   (_U_(1) << 15) /**< PORT Mask for PA15 */
#define PORT_PA16                   (_U_(1) << 16) /**< PORT Mask for PA16 */
#define PORT_PA17                   (_U_(1) << 17) /**< PORT Mask for PA17 */
#define PORT_PA18                   (_U_(1) << 18) /**< PORT Mask for PA18 */
#define PORT_PA19                   (_U_(1) << 19) /**< PORT Mask for PA19 */
#define PORT_PA22                   (_U_(1) << 22) /**< PORT Mask for PA22 */
#define PORT_PA23                   (_U_(1) << 23) /**< PORT Mask for PA23 */
#define PORT_PA24                   (_U_(1) << 24) /**< PORT Mask for PA24 */
#define PORT_PA25                   (_U_(1) << 25) /**< PORT Mask for PA25 */
#define PORT_PA27                   (_U_(1) << 27) /**< PORT Mask for PA27 */
#define PORT_PA30                   (_U_(1) << 30) /**< PORT Mask for PA30 */
#define PORT_PA31                   (_U_(1) << 31) /**< PORT Mask for PA31 */


/* ========== Peripheral I/O indexes ========== */
#define PORT_PA00_IDX               (  0)  /**< PORT Index Number for PA00 */
#define PORT_PA01_IDX               (  1)  /**< PORT Index Number for PA01 */
#define PORT_PA02_IDX               (  2)  /**< PORT Index Number for PA02 */
#define PORT_PA03_IDX               (  3)  /**< PORT Index Number for PA03 */
#define PORT_PA04_IDX               (  4)  /**< PORT Index Number for PA04 */
#define PORT_PA05_IDX               (  5)  /**< PORT Index Number for PA05 */
#define PORT_PA06_IDX               (  6)  /**< PORT Index Number for PA06 */
#define PORT_PA07_IDX               (  7)  /**< PORT Index Number for PA07 */
#define PORT_PA08_IDX               (  8)  /**< PORT Index Number for PA08 */
#define PORT_PA09_IDX               (  9)  /**< PORT Index Number for PA09 */
#define PORT_PA10_IDX               ( 10)  /**< PORT Index Number for PA10 */
#define PORT_PA11_IDX               ( 11)  /**< PORT Index Number for PA11 */
#define PORT_PA14_IDX               ( 14)  /**< PORT Index Number for PA14 */
#define PORT_PA15_IDX               ( 15)  /**< PORT Index Number for PA15 */
#define PORT_PA16_IDX               ( 16)  /**< PORT Index Number for PA16 */
#define PORT_PA17_IDX               ( 17)  /**< PORT Index Number for PA17 */
#define PORT_PA18_IDX               ( 18)  /**< PORT Index Number for PA18 */
#define PORT_PA19_IDX               ( 19)  /**< PORT Index Number for PA19 */
#define PORT_PA22_IDX               ( 22)  /**< PORT Index Number for PA22 */
#define PORT_PA23_IDX               ( 23)  /**< PORT Index Number for PA23 */
#define PORT_PA24_IDX               ( 24)  /**< PORT Index Number for PA24 */
#define PORT_PA25_IDX               ( 25)  /**< PORT Index Number for PA25 */
#define PORT_PA27_IDX               ( 27)  /**< PORT Index Number for PA27 */
#define PORT_PA30_IDX               ( 30)  /**< PORT Index Number for PA30 */
#define PORT_PA31_IDX               ( 31)  /**< PORT Index Number for PA31 */

/* ========== PORT definition for AC peripheral ========== */
#define PIN_PA04B_AC_AIN0                          _L_(4)       /**< AC signal: AIN0 on PA04 mux B*/
#define MUX_PA04B_AC_AIN0                          _L_(1)      
#define PINMUX_PA04B_AC_AIN0                       ((PIN_PA04B_AC_AIN0 << 16) | MUX_PA04B_AC_AIN0)
#define PORT_PA04B_AC_AIN0                         (_UL_(1) << 4)

#define PIN_PA05B_AC_AIN1                          _L_(5)       /**< AC signal: AIN1 on PA05 mux B*/
#define MUX_PA05B_AC_AIN1                          _L_(1)      
#define PINMUX_PA05B_AC_AIN1                       ((PIN_PA05B_AC_AIN1 << 16) | MUX_PA05B_AC_AIN1)
#define PORT_PA05B_AC_AIN1                         (_UL_(1) << 5)

#define PIN_PA06B_AC_AIN2                          _L_(6)       /**< AC signal: AIN2 on PA06 mux B*/
#define MUX_PA06B_AC_AIN2                          _L_(1)      
#define PINMUX_PA06B_AC_AIN2                       ((PIN_PA06B_AC_AIN2 << 16) | MUX_PA06B_AC_AIN2)
#define PORT_PA06B_AC_AIN2                         (_UL_(1) << 6)

#define PIN_PA07B_AC_AIN3                          _L_(7)       /**< AC signal: AIN3 on PA07 mux B*/
#define MUX_PA07B_AC_AIN3                          _L_(1)      
#define PINMUX_PA07B_AC_AIN3                       ((PIN_PA07B_AC_AIN3 << 16) | MUX_PA07B_AC_AIN3)
#define PORT_PA07B_AC_AIN3                         (_UL_(1) << 7)

#define PIN_PA18H_AC_CMP0                          _L_(18)      /**< AC signal: CMP0 on PA18 mux H*/
#define MUX_PA18H_AC_CMP0                          _L_(7)      
#define PINMUX_PA18H_AC_CMP0                       ((PIN_PA18H_AC_CMP0 << 16) | MUX_PA18H_AC_CMP0)
#define PORT_PA18H_AC_CMP0                         (_UL_(1) << 18)

#define PIN_PA19H_AC_CMP1                          _L_(19)      /**< AC signal: CMP1 on PA19 mux H*/
#define MUX_PA19H_AC_CMP1                          _L_(7)      
#define PINMUX_PA19H_AC_CMP1                       ((PIN_PA19H_AC_CMP1 << 16) | MUX_PA19H_AC_CMP1)
#define PORT_PA19H_AC_CMP1                         (_UL_(1) << 19)

/* ========== PORT definition for ADC peripheral ========== */
#define PIN_PA02B_ADC_AIN0                         _L_(2)       /**< ADC signal: AIN0 on PA02 mux B*/
#define MUX_PA02B_ADC_AIN0                         _L_(1)      
#define PINMUX_PA02B_ADC_AIN0                      ((PIN_PA02B_ADC_AIN0 << 16) | MUX_PA02B_ADC_AIN0)
#define PORT_PA02B_ADC_AIN0                        (_UL_(1) << 2)

#define PIN_PA03B_ADC_AIN1                         _L_(3)       /**< ADC signal: AIN1 on PA03 mux B*/
#define MUX_PA03B_ADC_AIN1                         _L_(1)      
#define PINMUX_PA03B_ADC_AIN1                      ((PIN_PA03B_ADC_AIN1 << 16) | MUX_PA03B_ADC_AIN1)
#define PORT_PA03B_ADC_AIN1                        (_UL_(1) << 3)

#define PIN_PA04B_ADC_AIN2                         _L_(4)       /**< ADC signal: AIN2 on PA04 mux B*/
#define MUX_PA04B_ADC_AIN2                         _L_(1)      
#define PINMUX_PA04B_ADC_AIN2                      ((PIN_PA04B_ADC_AIN2 << 16) | MUX_PA04B_ADC_AIN2)
#define PORT_PA04B_ADC_AIN2                        (_UL_(1) << 4)

#define PIN_PA05B_ADC_AIN3                         _L_(5)       /**< ADC signal: AIN3 on PA05 mux B*/
#define MUX_PA05B_ADC_AIN3                         _L_(1)      
#define PINMUX_PA05B_ADC_AIN3                      ((PIN_PA05B_ADC_AIN3 << 16) | MUX_PA05B_ADC_AIN3)
#define PORT_PA05B_ADC_AIN3                        (_UL_(1) << 5)

#define PIN_PA06B_ADC_AIN4                         _L_(6)       /**< ADC signal: AIN4 on PA06 mux B*/
#define MUX_PA06B_ADC_AIN4                         _L_(1)      
#define PINMUX_PA06B_ADC_AIN4                      ((PIN_PA06B_ADC_AIN4 << 16) | MUX_PA06B_ADC_AIN4)
#define PORT_PA06B_ADC_AIN4                        (_UL_(1) << 6)

#define PIN_PA07B_ADC_AIN5                         _L_(7)       /**< ADC signal: AIN5 on PA07 mux B*/
#define MUX_PA07B_ADC_AIN5                         _L_(1)      
#define PINMUX_PA07B_ADC_AIN5                      ((PIN_PA07B_ADC_AIN5 << 16) | MUX_PA07B_ADC_AIN5)
#define PORT_PA07B_ADC_AIN5                        (_UL_(1) << 7)

#define PIN_PA08B_ADC_AIN6                         _L_(8)       /**< ADC signal: AIN6 on PA08 mux B*/
#define MUX_PA08B_ADC_AIN6                         _L_(1)      
#define PINMUX_PA08B_ADC_AIN6                      ((PIN_PA08B_ADC_AIN6 << 16) | MUX_PA08B_ADC_AIN6)
#define PORT_PA08B_ADC_AIN6                        (_UL_(1) << 8)

#define PIN_PA09B_ADC_AIN7                         _L_(9)       /**< ADC signal: AIN7 on PA09 mux B*/
#define MUX_PA09B_ADC_AIN7                         _L_(1)      
#define PINMUX_PA09B_ADC_AIN7                      ((PIN_PA09B_ADC_AIN7 << 16) | MUX_PA09B_ADC_AIN7)
#define PORT_PA09B_ADC_AIN7                        (_UL_(1) << 9)

#define PIN_PA10B_ADC_AIN8                         _L_(10)      /**< ADC signal: AIN8 on PA10 mux B*/
#define MUX_PA10B_ADC_AIN8                         _L_(1)      
#define PINMUX_PA10B_ADC_AIN8                      ((PIN_PA10B_ADC_AIN8 << 16) | MUX_PA10B_ADC_AIN8)
#define PORT_PA10B_ADC_AIN8                        (_UL_(1) << 10)

#define PIN_PA11B_ADC_AIN9                         _L_(11)      /**< ADC signal: AIN9 on PA11 mux B*/
#define MUX_PA11B_ADC_AIN9                         _L_(1)      
#define PINMUX_PA11B_ADC_AIN9                      ((PIN_PA11B_ADC_AIN9 << 16) | MUX_PA11B_ADC_AIN9)
#define PORT_PA11B_ADC_AIN9                        (_UL_(1) << 11)

#define PIN_PA04B_ADC_VREFP                        _L_(4)       /**< ADC signal: VREFP on PA04 mux B*/
#define MUX_PA04B_ADC_VREFP                        _L_(1)      
#define PINMUX_PA04B_ADC_VREFP                     ((PIN_PA04B_ADC_VREFP << 16) | MUX_PA04B_ADC_VREFP)
#define PORT_PA04B_ADC_VREFP                       (_UL_(1) << 4)

/* ========== PORT definition for CCL peripheral ========== */
#define PIN_PA04I_CCL_IN0                          _L_(4)       /**< CCL signal: IN0 on PA04 mux I*/
#define MUX_PA04I_CCL_IN0                          _L_(8)      
#define PINMUX_PA04I_CCL_IN0                       ((PIN_PA04I_CCL_IN0 << 16) | MUX_PA04I_CCL_IN0)
#define PORT_PA04I_CCL_IN0                         (_UL_(1) << 4)

#define PIN_PA16I_CCL_IN0                          _L_(16)      /**< CCL signal: IN0 on PA16 mux I*/
#define MUX_PA16I_CCL_IN0                          _L_(8)      
#define PINMUX_PA16I_CCL_IN0                       ((PIN_PA16I_CCL_IN0 << 16) | MUX_PA16I_CCL_IN0)
#define PORT_PA16I_CCL_IN0                         (_UL_(1) << 16)

#define PIN_PA05I_CCL_IN1                          _L_(5)       /**< CCL signal: IN1 on PA05 mux I*/
#define MUX_PA05I_CCL_IN1                          _L_(8)      
#define PINMUX_PA05I_CCL_IN1                       ((PIN_PA05I_CCL_IN1 << 16) | MUX_PA05I_CCL_IN1)
#define PORT_PA05I_CCL_IN1                         (_UL_(1) << 5)

#define PIN_PA17I_CCL_IN1                          _L_(17)      /**< CCL signal: IN1 on PA17 mux I*/
#define MUX_PA17I_CCL_IN1                          _L_(8)      
#define PINMUX_PA17I_CCL_IN1                       ((PIN_PA17I_CCL_IN1 << 16) | MUX_PA17I_CCL_IN1)
#define PORT_PA17I_CCL_IN1                         (_UL_(1) << 17)

#define PIN_PA06I_CCL_IN2                          _L_(6)       /**< CCL signal: IN2 on PA06 mux I*/
#define MUX_PA06I_CCL_IN2                          _L_(8)      
#define PINMUX_PA06I_CCL_IN2                       ((PIN_PA06I_CCL_IN2 << 16) | MUX_PA06I_CCL_IN2)
#define PORT_PA06I_CCL_IN2                         (_UL_(1) << 6)

#define PIN_PA18I_CCL_IN2                          _L_(18)      /**< CCL signal: IN2 on PA18 mux I*/
#define MUX_PA18I_CCL_IN2                          _L_(8)      
#define PINMUX_PA18I_CCL_IN2                       ((PIN_PA18I_CCL_IN2 << 16) | MUX_PA18I_CCL_IN2)
#define PORT_PA18I_CCL_IN2                         (_UL_(1) << 18)

#define PIN_PA08I_CCL_IN3                          _L_(8)       /**< CCL signal: IN3 on PA08 mux I*/
#define MUX_PA08I_CCL_IN3                          _L_(8)      
#define PINMUX_PA08I_CCL_IN3                       ((PIN_PA08I_CCL_IN3 << 16) | MUX_PA08I_CCL_IN3)
#define PORT_PA08I_CCL_IN3                         (_UL_(1) << 8)

#define PIN_PA30I_CCL_IN3                          _L_(30)      /**< CCL signal: IN3 on PA30 mux I*/
#define MUX_PA30I_CCL_IN3                          _L_(8)      
#define PINMUX_PA30I_CCL_IN3                       ((PIN_PA30I_CCL_IN3 << 16) | MUX_PA30I_CCL_IN3)
#define PORT_PA30I_CCL_IN3                         (_UL_(1) << 30)

#define PIN_PA09I_CCL_IN4                          _L_(9)       /**< CCL signal: IN4 on PA09 mux I*/
#define MUX_PA09I_CCL_IN4                          _L_(8)      
#define PINMUX_PA09I_CCL_IN4                       ((PIN_PA09I_CCL_IN4 << 16) | MUX_PA09I_CCL_IN4)
#define PORT_PA09I_CCL_IN4                         (_UL_(1) << 9)

#define PIN_PA10I_CCL_IN5                          _L_(10)      /**< CCL signal: IN5 on PA10 mux I*/
#define MUX_PA10I_CCL_IN5                          _L_(8)      
#define PINMUX_PA10I_CCL_IN5                       ((PIN_PA10I_CCL_IN5 << 16) | MUX_PA10I_CCL_IN5)
#define PORT_PA10I_CCL_IN5                         (_UL_(1) << 10)

#define PIN_PA07I_CCL_OUT0                         _L_(7)       /**< CCL signal: OUT0 on PA07 mux I*/
#define MUX_PA07I_CCL_OUT0                         _L_(8)      
#define PINMUX_PA07I_CCL_OUT0                      ((PIN_PA07I_CCL_OUT0 << 16) | MUX_PA07I_CCL_OUT0)
#define PORT_PA07I_CCL_OUT0                        (_UL_(1) << 7)

#define PIN_PA19I_CCL_OUT0                         _L_(19)      /**< CCL signal: OUT0 on PA19 mux I*/
#define MUX_PA19I_CCL_OUT0                         _L_(8)      
#define PINMUX_PA19I_CCL_OUT0                      ((PIN_PA19I_CCL_OUT0 << 16) | MUX_PA19I_CCL_OUT0)
#define PORT_PA19I_CCL_OUT0                        (_UL_(1) << 19)

#define PIN_PA11I_CCL_OUT1                         _L_(11)      /**< CCL signal: OUT1 on PA11 mux I*/
#define MUX_PA11I_CCL_OUT1                         _L_(8)      
#define PINMUX_PA11I_CCL_OUT1                      ((PIN_PA11I_CCL_OUT1 << 16) | MUX_PA11I_CCL_OUT1)
#define PORT_PA11I_CCL_OUT1                        (_UL_(1) << 11)

#define PIN_PA31I_CCL_OUT1                         _L_(31)      /**< CCL signal: OUT1 on PA31 mux I*/
#define MUX_PA31I_CCL_OUT1                         _L_(8)      
#define PINMUX_PA31I_CCL_OUT1                      ((PIN_PA31I_CCL_OUT1 << 16) | MUX_PA31I_CCL_OUT1)
#define PORT_PA31I_CCL_OUT1                        (_UL_(1) << 31)

/* ========== PORT definition for DAC peripheral ========== */
#define PIN_PA02B_DAC_VOUT                         _L_(2)       /**< DAC signal: VOUT on PA02 mux B*/
#define MUX_PA02B_DAC_VOUT                         _L_(1)      
#define PINMUX_PA02B_DAC_VOUT                      ((PIN_PA02B_DAC_VOUT << 16) | MUX_PA02B_DAC_VOUT)
#define PORT_PA02B_DAC_VOUT                        (_UL_(1) << 2)

#define PIN_PA03B_DAC_VREFP                        _L_(3)       /**< DAC signal: VREFP on PA03 mux B*/
#define MUX_PA03B_DAC_VREFP                        _L_(1)      
#define PINMUX_PA03B_DAC_VREFP                     ((PIN_PA03B_DAC_VREFP << 16) | MUX_PA03B_DAC_VREFP)
#define PORT_PA03B_DAC_VREFP                       (_UL_(1) << 3)

/* ========== PORT definition for EIC peripheral ========== */
#define PIN_PA09A_EIC_EXTINT0                      _L_(9)       /**< EIC signal: EXTINT0 on PA09 mux A*/
#define MUX_PA09A_EIC_EXTINT0                      _L_(0)      
#define PINMUX_PA09A_EIC_EXTINT0                   ((PIN_PA09A_EIC_EXTINT0 << 16) | MUX_PA09A_EIC_EXTINT0)
#define PORT_PA09A_EIC_EXTINT0                     (_UL_(1) << 9)
#define PIN_PA09A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PA09 External Interrupt Line */

#define PIN_PA19A_EIC_EXTINT0                      _L_(19)      /**< EIC signal: EXTINT0 on PA19 mux A*/
#define MUX_PA19A_EIC_EXTINT0                      _L_(0)      
#define PINMUX_PA19A_EIC_EXTINT0                   ((PIN_PA19A_EIC_EXTINT0 << 16) | MUX_PA19A_EIC_EXTINT0)
#define PORT_PA19A_EIC_EXTINT0                     (_UL_(1) << 19)
#define PIN_PA19A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PA19 External Interrupt Line */

#define PIN_PA00A_EIC_EXTINT0                      _L_(0)       /**< EIC signal: EXTINT0 on PA00 mux A*/
#define MUX_PA00A_EIC_EXTINT0                      _L_(0)      
#define PINMUX_PA00A_EIC_EXTINT0                   ((PIN_PA00A_EIC_EXTINT0 << 16) | MUX_PA00A_EIC_EXTINT0)
#define PORT_PA00A_EIC_EXTINT0                     (_UL_(1) << 0)
#define PIN_PA00A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PA00 External Interrupt Line */

#define PIN_PA10A_EIC_EXTINT1                      _L_(10)      /**< EIC signal: EXTINT1 on PA10 mux A*/
#define MUX_PA10A_EIC_EXTINT1                      _L_(0)      
#define PINMUX_PA10A_EIC_EXTINT1                   ((PIN_PA10A_EIC_EXTINT1 << 16) | MUX_PA10A_EIC_EXTINT1)
#define PORT_PA10A_EIC_EXTINT1                     (_UL_(1) << 10)
#define PIN_PA10A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PA10 External Interrupt Line */

#define PIN_PA22A_EIC_EXTINT1                      _L_(22)      /**< EIC signal: EXTINT1 on PA22 mux A*/
#define MUX_PA22A_EIC_EXTINT1                      _L_(0)      
#define PINMUX_PA22A_EIC_EXTINT1                   ((PIN_PA22A_EIC_EXTINT1 << 16) | MUX_PA22A_EIC_EXTINT1)
#define PORT_PA22A_EIC_EXTINT1                     (_UL_(1) << 22)
#define PIN_PA22A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PA22 External Interrupt Line */

#define PIN_PA01A_EIC_EXTINT1                      _L_(1)       /**< EIC signal: EXTINT1 on PA01 mux A*/
#define MUX_PA01A_EIC_EXTINT1                      _L_(0)      
#define PINMUX_PA01A_EIC_EXTINT1                   ((PIN_PA01A_EIC_EXTINT1 << 16) | MUX_PA01A_EIC_EXTINT1)
#define PORT_PA01A_EIC_EXTINT1                     (_UL_(1) << 1)
#define PIN_PA01A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PA01 External Interrupt Line */

#define PIN_PA02A_EIC_EXTINT2                      _L_(2)       /**< EIC signal: EXTINT2 on PA02 mux A*/
#define MUX_PA02A_EIC_EXTINT2                      _L_(0)      
#define PINMUX_PA02A_EIC_EXTINT2                   ((PIN_PA02A_EIC_EXTINT2 << 16) | MUX_PA02A_EIC_EXTINT2)
#define PORT_PA02A_EIC_EXTINT2                     (_UL_(1) << 2)
#define PIN_PA02A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PA02 External Interrupt Line */

#define PIN_PA11A_EIC_EXTINT2                      _L_(11)      /**< EIC signal: EXTINT2 on PA11 mux A*/
#define MUX_PA11A_EIC_EXTINT2                      _L_(0)      
#define PINMUX_PA11A_EIC_EXTINT2                   ((PIN_PA11A_EIC_EXTINT2 << 16) | MUX_PA11A_EIC_EXTINT2)
#define PORT_PA11A_EIC_EXTINT2                     (_UL_(1) << 11)
#define PIN_PA11A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PA11 External Interrupt Line */

#define PIN_PA23A_EIC_EXTINT2                      _L_(23)      /**< EIC signal: EXTINT2 on PA23 mux A*/
#define MUX_PA23A_EIC_EXTINT2                      _L_(0)      
#define PINMUX_PA23A_EIC_EXTINT2                   ((PIN_PA23A_EIC_EXTINT2 << 16) | MUX_PA23A_EIC_EXTINT2)
#define PORT_PA23A_EIC_EXTINT2                     (_UL_(1) << 23)
#define PIN_PA23A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PA23 External Interrupt Line */

#define PIN_PA03A_EIC_EXTINT3                      _L_(3)       /**< EIC signal: EXTINT3 on PA03 mux A*/
#define MUX_PA03A_EIC_EXTINT3                      _L_(0)      
#define PINMUX_PA03A_EIC_EXTINT3                   ((PIN_PA03A_EIC_EXTINT3 << 16) | MUX_PA03A_EIC_EXTINT3)
#define PORT_PA03A_EIC_EXTINT3                     (_UL_(1) << 3)
#define PIN_PA03A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PA03 External Interrupt Line */

#define PIN_PA14A_EIC_EXTINT3                      _L_(14)      /**< EIC signal: EXTINT3 on PA14 mux A*/
#define MUX_PA14A_EIC_EXTINT3                      _L_(0)      
#define PINMUX_PA14A_EIC_EXTINT3                   ((PIN_PA14A_EIC_EXTINT3 << 16) | MUX_PA14A_EIC_EXTINT3)
#define PORT_PA14A_EIC_EXTINT3                     (_UL_(1) << 14)
#define PIN_PA14A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PA14 External Interrupt Line */

#define PIN_PA24A_EIC_EXTINT3                      _L_(24)      /**< EIC signal: EXTINT3 on PA24 mux A*/
#define MUX_PA24A_EIC_EXTINT3                      _L_(0)      
#define PINMUX_PA24A_EIC_EXTINT3                   ((PIN_PA24A_EIC_EXTINT3 << 16) | MUX_PA24A_EIC_EXTINT3)
#define PORT_PA24A_EIC_EXTINT3                     (_UL_(1) << 24)
#define PIN_PA24A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PA24 External Interrupt Line */

#define PIN_PA04A_EIC_EXTINT4                      _L_(4)       /**< EIC signal: EXTINT4 on PA04 mux A*/
#define MUX_PA04A_EIC_EXTINT4                      _L_(0)      
#define PINMUX_PA04A_EIC_EXTINT4                   ((PIN_PA04A_EIC_EXTINT4 << 16) | MUX_PA04A_EIC_EXTINT4)
#define PORT_PA04A_EIC_EXTINT4                     (_UL_(1) << 4)
#define PIN_PA04A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PA04 External Interrupt Line */

#define PIN_PA15A_EIC_EXTINT4                      _L_(15)      /**< EIC signal: EXTINT4 on PA15 mux A*/
#define MUX_PA15A_EIC_EXTINT4                      _L_(0)      
#define PINMUX_PA15A_EIC_EXTINT4                   ((PIN_PA15A_EIC_EXTINT4 << 16) | MUX_PA15A_EIC_EXTINT4)
#define PORT_PA15A_EIC_EXTINT4                     (_UL_(1) << 15)
#define PIN_PA15A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PA15 External Interrupt Line */

#define PIN_PA25A_EIC_EXTINT4                      _L_(25)      /**< EIC signal: EXTINT4 on PA25 mux A*/
#define MUX_PA25A_EIC_EXTINT4                      _L_(0)      
#define PINMUX_PA25A_EIC_EXTINT4                   ((PIN_PA25A_EIC_EXTINT4 << 16) | MUX_PA25A_EIC_EXTINT4)
#define PORT_PA25A_EIC_EXTINT4                     (_UL_(1) << 25)
#define PIN_PA25A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PA25 External Interrupt Line */

#define PIN_PA05A_EIC_EXTINT5                      _L_(5)       /**< EIC signal: EXTINT5 on PA05 mux A*/
#define MUX_PA05A_EIC_EXTINT5                      _L_(0)      
#define PINMUX_PA05A_EIC_EXTINT5                   ((PIN_PA05A_EIC_EXTINT5 << 16) | MUX_PA05A_EIC_EXTINT5)
#define PORT_PA05A_EIC_EXTINT5                     (_UL_(1) << 5)
#define PIN_PA05A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PA05 External Interrupt Line */

#define PIN_PA16A_EIC_EXTINT5                      _L_(16)      /**< EIC signal: EXTINT5 on PA16 mux A*/
#define MUX_PA16A_EIC_EXTINT5                      _L_(0)      
#define PINMUX_PA16A_EIC_EXTINT5                   ((PIN_PA16A_EIC_EXTINT5 << 16) | MUX_PA16A_EIC_EXTINT5)
#define PORT_PA16A_EIC_EXTINT5                     (_UL_(1) << 16)
#define PIN_PA16A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PA16 External Interrupt Line */

#define PIN_PA27A_EIC_EXTINT5                      _L_(27)      /**< EIC signal: EXTINT5 on PA27 mux A*/
#define MUX_PA27A_EIC_EXTINT5                      _L_(0)      
#define PINMUX_PA27A_EIC_EXTINT5                   ((PIN_PA27A_EIC_EXTINT5 << 16) | MUX_PA27A_EIC_EXTINT5)
#define PORT_PA27A_EIC_EXTINT5                     (_UL_(1) << 27)
#define PIN_PA27A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PA27 External Interrupt Line */

#define PIN_PA06A_EIC_EXTINT6                      _L_(6)       /**< EIC signal: EXTINT6 on PA06 mux A*/
#define MUX_PA06A_EIC_EXTINT6                      _L_(0)      
#define PINMUX_PA06A_EIC_EXTINT6                   ((PIN_PA06A_EIC_EXTINT6 << 16) | MUX_PA06A_EIC_EXTINT6)
#define PORT_PA06A_EIC_EXTINT6                     (_UL_(1) << 6)
#define PIN_PA06A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PA06 External Interrupt Line */

#define PIN_PA17A_EIC_EXTINT6                      _L_(17)      /**< EIC signal: EXTINT6 on PA17 mux A*/
#define MUX_PA17A_EIC_EXTINT6                      _L_(0)      
#define PINMUX_PA17A_EIC_EXTINT6                   ((PIN_PA17A_EIC_EXTINT6 << 16) | MUX_PA17A_EIC_EXTINT6)
#define PORT_PA17A_EIC_EXTINT6                     (_UL_(1) << 17)
#define PIN_PA17A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PA17 External Interrupt Line */

#define PIN_PA30A_EIC_EXTINT6                      _L_(30)      /**< EIC signal: EXTINT6 on PA30 mux A*/
#define MUX_PA30A_EIC_EXTINT6                      _L_(0)      
#define PINMUX_PA30A_EIC_EXTINT6                   ((PIN_PA30A_EIC_EXTINT6 << 16) | MUX_PA30A_EIC_EXTINT6)
#define PORT_PA30A_EIC_EXTINT6                     (_UL_(1) << 30)
#define PIN_PA30A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PA30 External Interrupt Line */

#define PIN_PA07A_EIC_EXTINT7                      _L_(7)       /**< EIC signal: EXTINT7 on PA07 mux A*/
#define MUX_PA07A_EIC_EXTINT7                      _L_(0)      
#define PINMUX_PA07A_EIC_EXTINT7                   ((PIN_PA07A_EIC_EXTINT7 << 16) | MUX_PA07A_EIC_EXTINT7)
#define PORT_PA07A_EIC_EXTINT7                     (_UL_(1) << 7)
#define PIN_PA07A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PA07 External Interrupt Line */

#define PIN_PA18A_EIC_EXTINT7                      _L_(18)      /**< EIC signal: EXTINT7 on PA18 mux A*/
#define MUX_PA18A_EIC_EXTINT7                      _L_(0)      
#define PINMUX_PA18A_EIC_EXTINT7                   ((PIN_PA18A_EIC_EXTINT7 << 16) | MUX_PA18A_EIC_EXTINT7)
#define PORT_PA18A_EIC_EXTINT7                     (_UL_(1) << 18)
#define PIN_PA18A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PA18 External Interrupt Line */

#define PIN_PA31A_EIC_EXTINT7                      _L_(31)      /**< EIC signal: EXTINT7 on PA31 mux A*/
#define MUX_PA31A_EIC_EXTINT7                      _L_(0)      
#define PINMUX_PA31A_EIC_EXTINT7                   ((PIN_PA31A_EIC_EXTINT7 << 16) | MUX_PA31A_EIC_EXTINT7)
#define PORT_PA31A_EIC_EXTINT7                     (_UL_(1) << 31)
#define PIN_PA31A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PA31 External Interrupt Line */

#define PIN_PA08A_EIC_NMI                          _L_(8)       /**< EIC signal: NMI on PA08 mux A*/
#define MUX_PA08A_EIC_NMI                          _L_(0)      
#define PINMUX_PA08A_EIC_NMI                       ((PIN_PA08A_EIC_NMI << 16) | MUX_PA08A_EIC_NMI)
#define PORT_PA08A_EIC_NMI                         (_UL_(1) << 8)

/* ========== PORT definition for GCLK peripheral ========== */
#define PIN_PA30H_GCLK_IO0                         _L_(30)      /**< GCLK signal: IO0 on PA30 mux H*/
#define MUX_PA30H_GCLK_IO0                         _L_(7)      
#define PINMUX_PA30H_GCLK_IO0                      ((PIN_PA30H_GCLK_IO0 << 16) | MUX_PA30H_GCLK_IO0)
#define PORT_PA30H_GCLK_IO0                        (_UL_(1) << 30)

#define PIN_PA14H_GCLK_IO0                         _L_(14)      /**< GCLK signal: IO0 on PA14 mux H*/
#define MUX_PA14H_GCLK_IO0                         _L_(7)      
#define PINMUX_PA14H_GCLK_IO0                      ((PIN_PA14H_GCLK_IO0 << 16) | MUX_PA14H_GCLK_IO0)
#define PORT_PA14H_GCLK_IO0                        (_UL_(1) << 14)

#define PIN_PA27H_GCLK_IO0                         _L_(27)      /**< GCLK signal: IO0 on PA27 mux H*/
#define MUX_PA27H_GCLK_IO0                         _L_(7)      
#define PINMUX_PA27H_GCLK_IO0                      ((PIN_PA27H_GCLK_IO0 << 16) | MUX_PA27H_GCLK_IO0)
#define PORT_PA27H_GCLK_IO0                        (_UL_(1) << 27)

#define PIN_PA23H_GCLK_IO1                         _L_(23)      /**< GCLK signal: IO1 on PA23 mux H*/
#define MUX_PA23H_GCLK_IO1                         _L_(7)      
#define PINMUX_PA23H_GCLK_IO1                      ((PIN_PA23H_GCLK_IO1 << 16) | MUX_PA23H_GCLK_IO1)
#define PORT_PA23H_GCLK_IO1                        (_UL_(1) << 23)

#define PIN_PA15H_GCLK_IO1                         _L_(15)      /**< GCLK signal: IO1 on PA15 mux H*/
#define MUX_PA15H_GCLK_IO1                         _L_(7)      
#define PINMUX_PA15H_GCLK_IO1                      ((PIN_PA15H_GCLK_IO1 << 16) | MUX_PA15H_GCLK_IO1)
#define PORT_PA15H_GCLK_IO1                        (_UL_(1) << 15)

#define PIN_PA16H_GCLK_IO2                         _L_(16)      /**< GCLK signal: IO2 on PA16 mux H*/
#define MUX_PA16H_GCLK_IO2                         _L_(7)      
#define PINMUX_PA16H_GCLK_IO2                      ((PIN_PA16H_GCLK_IO2 << 16) | MUX_PA16H_GCLK_IO2)
#define PORT_PA16H_GCLK_IO2                        (_UL_(1) << 16)

#define PIN_PA22H_GCLK_IO2                         _L_(22)      /**< GCLK signal: IO2 on PA22 mux H*/
#define MUX_PA22H_GCLK_IO2                         _L_(7)      
#define PINMUX_PA22H_GCLK_IO2                      ((PIN_PA22H_GCLK_IO2 << 16) | MUX_PA22H_GCLK_IO2)
#define PORT_PA22H_GCLK_IO2                        (_UL_(1) << 22)

#define PIN_PA11H_GCLK_IO3                         _L_(11)      /**< GCLK signal: IO3 on PA11 mux H*/
#define MUX_PA11H_GCLK_IO3                         _L_(7)      
#define PINMUX_PA11H_GCLK_IO3                      ((PIN_PA11H_GCLK_IO3 << 16) | MUX_PA11H_GCLK_IO3)
#define PORT_PA11H_GCLK_IO3                        (_UL_(1) << 11)

#define PIN_PA17H_GCLK_IO3                         _L_(17)      /**< GCLK signal: IO3 on PA17 mux H*/
#define MUX_PA17H_GCLK_IO3                         _L_(7)      
#define PINMUX_PA17H_GCLK_IO3                      ((PIN_PA17H_GCLK_IO3 << 16) | MUX_PA17H_GCLK_IO3)
#define PORT_PA17H_GCLK_IO3                        (_UL_(1) << 17)

#define PIN_PA10H_GCLK_IO4                         _L_(10)      /**< GCLK signal: IO4 on PA10 mux H*/
#define MUX_PA10H_GCLK_IO4                         _L_(7)      
#define PINMUX_PA10H_GCLK_IO4                      ((PIN_PA10H_GCLK_IO4 << 16) | MUX_PA10H_GCLK_IO4)
#define PORT_PA10H_GCLK_IO4                        (_UL_(1) << 10)

/* ========== PORT definition for OPAMP peripheral ========== */
#define PIN_PA02B_OPAMP_OANEG0                     _L_(2)       /**< OPAMP signal: OANEG0 on PA02 mux B*/
#define MUX_PA02B_OPAMP_OANEG0                     _L_(1)      
#define PINMUX_PA02B_OPAMP_OANEG0                  ((PIN_PA02B_OPAMP_OANEG0 << 16) | MUX_PA02B_OPAMP_OANEG0)
#define PORT_PA02B_OPAMP_OANEG0                    (_UL_(1) << 2)

#define PIN_PA00B_OPAMP_OANEG1                     _L_(0)       /**< OPAMP signal: OANEG1 on PA00 mux B*/
#define MUX_PA00B_OPAMP_OANEG1                     _L_(1)      
#define PINMUX_PA00B_OPAMP_OANEG1                  ((PIN_PA00B_OPAMP_OANEG1 << 16) | MUX_PA00B_OPAMP_OANEG1)
#define PORT_PA00B_OPAMP_OANEG1                    (_UL_(1) << 0)

#define PIN_PA03B_OPAMP_OANEG2                     _L_(3)       /**< OPAMP signal: OANEG2 on PA03 mux B*/
#define MUX_PA03B_OPAMP_OANEG2                     _L_(1)      
#define PINMUX_PA03B_OPAMP_OANEG2                  ((PIN_PA03B_OPAMP_OANEG2 << 16) | MUX_PA03B_OPAMP_OANEG2)
#define PORT_PA03B_OPAMP_OANEG2                    (_UL_(1) << 3)

#define PIN_PA07B_OPAMP_OAOUT0                     _L_(7)       /**< OPAMP signal: OAOUT0 on PA07 mux B*/
#define MUX_PA07B_OPAMP_OAOUT0                     _L_(1)      
#define PINMUX_PA07B_OPAMP_OAOUT0                  ((PIN_PA07B_OPAMP_OAOUT0 << 16) | MUX_PA07B_OPAMP_OAOUT0)
#define PORT_PA07B_OPAMP_OAOUT0                    (_UL_(1) << 7)

#define PIN_PA04B_OPAMP_OAOUT2                     _L_(4)       /**< OPAMP signal: OAOUT2 on PA04 mux B*/
#define MUX_PA04B_OPAMP_OAOUT2                     _L_(1)      
#define PINMUX_PA04B_OPAMP_OAOUT2                  ((PIN_PA04B_OPAMP_OAOUT2 << 16) | MUX_PA04B_OPAMP_OAOUT2)
#define PORT_PA04B_OPAMP_OAOUT2                    (_UL_(1) << 4)

#define PIN_PA06B_OPAMP_OAPOS0                     _L_(6)       /**< OPAMP signal: OAPOS0 on PA06 mux B*/
#define MUX_PA06B_OPAMP_OAPOS0                     _L_(1)      
#define PINMUX_PA06B_OPAMP_OAPOS0                  ((PIN_PA06B_OPAMP_OAPOS0 << 16) | MUX_PA06B_OPAMP_OAPOS0)
#define PORT_PA06B_OPAMP_OAPOS0                    (_UL_(1) << 6)

#define PIN_PA01B_OPAMP_OAPOS1                     _L_(1)       /**< OPAMP signal: OAPOS1 on PA01 mux B*/
#define MUX_PA01B_OPAMP_OAPOS1                     _L_(1)      
#define PINMUX_PA01B_OPAMP_OAPOS1                  ((PIN_PA01B_OPAMP_OAPOS1 << 16) | MUX_PA01B_OPAMP_OAPOS1)
#define PORT_PA01B_OPAMP_OAPOS1                    (_UL_(1) << 1)

#define PIN_PA05B_OPAMP_OAPOS2                     _L_(5)       /**< OPAMP signal: OAPOS2 on PA05 mux B*/
#define MUX_PA05B_OPAMP_OAPOS2                     _L_(1)      
#define PINMUX_PA05B_OPAMP_OAPOS2                  ((PIN_PA05B_OPAMP_OAPOS2 << 16) | MUX_PA05B_OPAMP_OAPOS2)
#define PORT_PA05B_OPAMP_OAPOS2                    (_UL_(1) << 5)

/* ========== PORT definition for PTC peripheral ========== */
#define PIN_PA00F_PTC_DRV0                         _L_(0)       /**< PTC signal: DRV0 on PA00 mux F*/
#define MUX_PA00F_PTC_DRV0                         _L_(5)      
#define PINMUX_PA00F_PTC_DRV0                      ((PIN_PA00F_PTC_DRV0 << 16) | MUX_PA00F_PTC_DRV0)
#define PORT_PA00F_PTC_DRV0                        (_UL_(1) << 0)

#define PIN_PA01F_PTC_DRV1                         _L_(1)       /**< PTC signal: DRV1 on PA01 mux F*/
#define MUX_PA01F_PTC_DRV1                         _L_(5)      
#define PINMUX_PA01F_PTC_DRV1                      ((PIN_PA01F_PTC_DRV1 << 16) | MUX_PA01F_PTC_DRV1)
#define PORT_PA01F_PTC_DRV1                        (_UL_(1) << 1)

#define PIN_PA02F_PTC_DRV2                         _L_(2)       /**< PTC signal: DRV2 on PA02 mux F*/
#define MUX_PA02F_PTC_DRV2                         _L_(5)      
#define PINMUX_PA02F_PTC_DRV2                      ((PIN_PA02F_PTC_DRV2 << 16) | MUX_PA02F_PTC_DRV2)
#define PORT_PA02F_PTC_DRV2                        (_UL_(1) << 2)

#define PIN_PA03F_PTC_DRV3                         _L_(3)       /**< PTC signal: DRV3 on PA03 mux F*/
#define MUX_PA03F_PTC_DRV3                         _L_(5)      
#define PINMUX_PA03F_PTC_DRV3                      ((PIN_PA03F_PTC_DRV3 << 16) | MUX_PA03F_PTC_DRV3)
#define PORT_PA03F_PTC_DRV3                        (_UL_(1) << 3)

#define PIN_PA05F_PTC_DRV4                         _L_(5)       /**< PTC signal: DRV4 on PA05 mux F*/
#define MUX_PA05F_PTC_DRV4                         _L_(5)      
#define PINMUX_PA05F_PTC_DRV4                      ((PIN_PA05F_PTC_DRV4 << 16) | MUX_PA05F_PTC_DRV4)
#define PORT_PA05F_PTC_DRV4                        (_UL_(1) << 5)

#define PIN_PA06F_PTC_DRV5                         _L_(6)       /**< PTC signal: DRV5 on PA06 mux F*/
#define MUX_PA06F_PTC_DRV5                         _L_(5)      
#define PINMUX_PA06F_PTC_DRV5                      ((PIN_PA06F_PTC_DRV5 << 16) | MUX_PA06F_PTC_DRV5)
#define PORT_PA06F_PTC_DRV5                        (_UL_(1) << 6)

#define PIN_PA08F_PTC_DRV6                         _L_(8)       /**< PTC signal: DRV6 on PA08 mux F*/
#define MUX_PA08F_PTC_DRV6                         _L_(5)      
#define PINMUX_PA08F_PTC_DRV6                      ((PIN_PA08F_PTC_DRV6 << 16) | MUX_PA08F_PTC_DRV6)
#define PORT_PA08F_PTC_DRV6                        (_UL_(1) << 8)

#define PIN_PA09F_PTC_DRV7                         _L_(9)       /**< PTC signal: DRV7 on PA09 mux F*/
#define MUX_PA09F_PTC_DRV7                         _L_(5)      
#define PINMUX_PA09F_PTC_DRV7                      ((PIN_PA09F_PTC_DRV7 << 16) | MUX_PA09F_PTC_DRV7)
#define PORT_PA09F_PTC_DRV7                        (_UL_(1) << 9)

#define PIN_PA10F_PTC_DRV8                         _L_(10)      /**< PTC signal: DRV8 on PA10 mux F*/
#define MUX_PA10F_PTC_DRV8                         _L_(5)      
#define PINMUX_PA10F_PTC_DRV8                      ((PIN_PA10F_PTC_DRV8 << 16) | MUX_PA10F_PTC_DRV8)
#define PORT_PA10F_PTC_DRV8                        (_UL_(1) << 10)

#define PIN_PA11F_PTC_DRV9                         _L_(11)      /**< PTC signal: DRV9 on PA11 mux F*/
#define MUX_PA11F_PTC_DRV9                         _L_(5)      
#define PINMUX_PA11F_PTC_DRV9                      ((PIN_PA11F_PTC_DRV9 << 16) | MUX_PA11F_PTC_DRV9)
#define PORT_PA11F_PTC_DRV9                        (_UL_(1) << 11)

#define PIN_PA14F_PTC_DRV10                        _L_(14)      /**< PTC signal: DRV10 on PA14 mux F*/
#define MUX_PA14F_PTC_DRV10                        _L_(5)      
#define PINMUX_PA14F_PTC_DRV10                     ((PIN_PA14F_PTC_DRV10 << 16) | MUX_PA14F_PTC_DRV10)
#define PORT_PA14F_PTC_DRV10                       (_UL_(1) << 14)

#define PIN_PA15F_PTC_DRV11                        _L_(15)      /**< PTC signal: DRV11 on PA15 mux F*/
#define MUX_PA15F_PTC_DRV11                        _L_(5)      
#define PINMUX_PA15F_PTC_DRV11                     ((PIN_PA15F_PTC_DRV11 << 16) | MUX_PA15F_PTC_DRV11)
#define PORT_PA15F_PTC_DRV11                       (_UL_(1) << 15)

#define PIN_PA16F_PTC_DRV12                        _L_(16)      /**< PTC signal: DRV12 on PA16 mux F*/
#define MUX_PA16F_PTC_DRV12                        _L_(5)      
#define PINMUX_PA16F_PTC_DRV12                     ((PIN_PA16F_PTC_DRV12 << 16) | MUX_PA16F_PTC_DRV12)
#define PORT_PA16F_PTC_DRV12                       (_UL_(1) << 16)

#define PIN_PA17F_PTC_DRV13                        _L_(17)      /**< PTC signal: DRV13 on PA17 mux F*/
#define MUX_PA17F_PTC_DRV13                        _L_(5)      
#define PINMUX_PA17F_PTC_DRV13                     ((PIN_PA17F_PTC_DRV13 << 16) | MUX_PA17F_PTC_DRV13)
#define PORT_PA17F_PTC_DRV13                       (_UL_(1) << 17)

#define PIN_PA18F_PTC_DRV14                        _L_(18)      /**< PTC signal: DRV14 on PA18 mux F*/
#define MUX_PA18F_PTC_DRV14                        _L_(5)      
#define PINMUX_PA18F_PTC_DRV14                     ((PIN_PA18F_PTC_DRV14 << 16) | MUX_PA18F_PTC_DRV14)
#define PORT_PA18F_PTC_DRV14                       (_UL_(1) << 18)

#define PIN_PA19F_PTC_DRV15                        _L_(19)      /**< PTC signal: DRV15 on PA19 mux F*/
#define MUX_PA19F_PTC_DRV15                        _L_(5)      
#define PINMUX_PA19F_PTC_DRV15                     ((PIN_PA19F_PTC_DRV15 << 16) | MUX_PA19F_PTC_DRV15)
#define PORT_PA19F_PTC_DRV15                       (_UL_(1) << 19)

#define PIN_PA22F_PTC_DRV16                        _L_(22)      /**< PTC signal: DRV16 on PA22 mux F*/
#define MUX_PA22F_PTC_DRV16                        _L_(5)      
#define PINMUX_PA22F_PTC_DRV16                     ((PIN_PA22F_PTC_DRV16 << 16) | MUX_PA22F_PTC_DRV16)
#define PORT_PA22F_PTC_DRV16                       (_UL_(1) << 22)

#define PIN_PA23F_PTC_DRV17                        _L_(23)      /**< PTC signal: DRV17 on PA23 mux F*/
#define MUX_PA23F_PTC_DRV17                        _L_(5)      
#define PINMUX_PA23F_PTC_DRV17                     ((PIN_PA23F_PTC_DRV17 << 16) | MUX_PA23F_PTC_DRV17)
#define PORT_PA23F_PTC_DRV17                       (_UL_(1) << 23)

#define PIN_PA30F_PTC_DRV18                        _L_(30)      /**< PTC signal: DRV18 on PA30 mux F*/
#define MUX_PA30F_PTC_DRV18                        _L_(5)      
#define PINMUX_PA30F_PTC_DRV18                     ((PIN_PA30F_PTC_DRV18 << 16) | MUX_PA30F_PTC_DRV18)
#define PORT_PA30F_PTC_DRV18                       (_UL_(1) << 30)

#define PIN_PA31F_PTC_DRV19                        _L_(31)      /**< PTC signal: DRV19 on PA31 mux F*/
#define MUX_PA31F_PTC_DRV19                        _L_(5)      
#define PINMUX_PA31F_PTC_DRV19                     ((PIN_PA31F_PTC_DRV19 << 16) | MUX_PA31F_PTC_DRV19)
#define PORT_PA31F_PTC_DRV19                       (_UL_(1) << 31)

#define PIN_PA03B_PTC_ECI0                         _L_(3)       /**< PTC signal: ECI0 on PA03 mux B*/
#define MUX_PA03B_PTC_ECI0                         _L_(1)      
#define PINMUX_PA03B_PTC_ECI0                      ((PIN_PA03B_PTC_ECI0 << 16) | MUX_PA03B_PTC_ECI0)
#define PORT_PA03B_PTC_ECI0                        (_UL_(1) << 3)

#define PIN_PA04B_PTC_ECI1                         _L_(4)       /**< PTC signal: ECI1 on PA04 mux B*/
#define MUX_PA04B_PTC_ECI1                         _L_(1)      
#define PINMUX_PA04B_PTC_ECI1                      ((PIN_PA04B_PTC_ECI1 << 16) | MUX_PA04B_PTC_ECI1)
#define PORT_PA04B_PTC_ECI1                        (_UL_(1) << 4)

#define PIN_PA05B_PTC_ECI2                         _L_(5)       /**< PTC signal: ECI2 on PA05 mux B*/
#define MUX_PA05B_PTC_ECI2                         _L_(1)      
#define PINMUX_PA05B_PTC_ECI2                      ((PIN_PA05B_PTC_ECI2 << 16) | MUX_PA05B_PTC_ECI2)
#define PORT_PA05B_PTC_ECI2                        (_UL_(1) << 5)

#define PIN_PA06B_PTC_ECI3                         _L_(6)       /**< PTC signal: ECI3 on PA06 mux B*/
#define MUX_PA06B_PTC_ECI3                         _L_(1)      
#define PINMUX_PA06B_PTC_ECI3                      ((PIN_PA06B_PTC_ECI3 << 16) | MUX_PA06B_PTC_ECI3)
#define PORT_PA06B_PTC_ECI3                        (_UL_(1) << 6)

#define PIN_PA00B_PTC_X0                           _L_(0)       /**< PTC signal: X0 on PA00 mux B*/
#define MUX_PA00B_PTC_X0                           _L_(1)      
#define PINMUX_PA00B_PTC_X0                        ((PIN_PA00B_PTC_X0 << 16) | MUX_PA00B_PTC_X0)
#define PORT_PA00B_PTC_X0                          (_UL_(1) << 0)

#define PIN_PA00B_PTC_Y0                           _L_(0)       /**< PTC signal: Y0 on PA00 mux B*/
#define MUX_PA00B_PTC_Y0                           _L_(1)      
#define PINMUX_PA00B_PTC_Y0                        ((PIN_PA00B_PTC_Y0 << 16) | MUX_PA00B_PTC_Y0)
#define PORT_PA00B_PTC_Y0                          (_UL_(1) << 0)

#define PIN_PA01B_PTC_X1                           _L_(1)       /**< PTC signal: X1 on PA01 mux B*/
#define MUX_PA01B_PTC_X1                           _L_(1)      
#define PINMUX_PA01B_PTC_X1                        ((PIN_PA01B_PTC_X1 << 16) | MUX_PA01B_PTC_X1)
#define PORT_PA01B_PTC_X1                          (_UL_(1) << 1)

#define PIN_PA01B_PTC_Y1                           _L_(1)       /**< PTC signal: Y1 on PA01 mux B*/
#define MUX_PA01B_PTC_Y1                           _L_(1)      
#define PINMUX_PA01B_PTC_Y1                        ((PIN_PA01B_PTC_Y1 << 16) | MUX_PA01B_PTC_Y1)
#define PORT_PA01B_PTC_Y1                          (_UL_(1) << 1)

#define PIN_PA02B_PTC_X2                           _L_(2)       /**< PTC signal: X2 on PA02 mux B*/
#define MUX_PA02B_PTC_X2                           _L_(1)      
#define PINMUX_PA02B_PTC_X2                        ((PIN_PA02B_PTC_X2 << 16) | MUX_PA02B_PTC_X2)
#define PORT_PA02B_PTC_X2                          (_UL_(1) << 2)

#define PIN_PA02B_PTC_Y2                           _L_(2)       /**< PTC signal: Y2 on PA02 mux B*/
#define MUX_PA02B_PTC_Y2                           _L_(1)      
#define PINMUX_PA02B_PTC_Y2                        ((PIN_PA02B_PTC_Y2 << 16) | MUX_PA02B_PTC_Y2)
#define PORT_PA02B_PTC_Y2                          (_UL_(1) << 2)

#define PIN_PA03B_PTC_X3                           _L_(3)       /**< PTC signal: X3 on PA03 mux B*/
#define MUX_PA03B_PTC_X3                           _L_(1)      
#define PINMUX_PA03B_PTC_X3                        ((PIN_PA03B_PTC_X3 << 16) | MUX_PA03B_PTC_X3)
#define PORT_PA03B_PTC_X3                          (_UL_(1) << 3)

#define PIN_PA03B_PTC_Y3                           _L_(3)       /**< PTC signal: Y3 on PA03 mux B*/
#define MUX_PA03B_PTC_Y3                           _L_(1)      
#define PINMUX_PA03B_PTC_Y3                        ((PIN_PA03B_PTC_Y3 << 16) | MUX_PA03B_PTC_Y3)
#define PORT_PA03B_PTC_Y3                          (_UL_(1) << 3)

#define PIN_PA05B_PTC_X4                           _L_(5)       /**< PTC signal: X4 on PA05 mux B*/
#define MUX_PA05B_PTC_X4                           _L_(1)      
#define PINMUX_PA05B_PTC_X4                        ((PIN_PA05B_PTC_X4 << 16) | MUX_PA05B_PTC_X4)
#define PORT_PA05B_PTC_X4                          (_UL_(1) << 5)

#define PIN_PA05B_PTC_Y4                           _L_(5)       /**< PTC signal: Y4 on PA05 mux B*/
#define MUX_PA05B_PTC_Y4                           _L_(1)      
#define PINMUX_PA05B_PTC_Y4                        ((PIN_PA05B_PTC_Y4 << 16) | MUX_PA05B_PTC_Y4)
#define PORT_PA05B_PTC_Y4                          (_UL_(1) << 5)

#define PIN_PA06B_PTC_X5                           _L_(6)       /**< PTC signal: X5 on PA06 mux B*/
#define MUX_PA06B_PTC_X5                           _L_(1)      
#define PINMUX_PA06B_PTC_X5                        ((PIN_PA06B_PTC_X5 << 16) | MUX_PA06B_PTC_X5)
#define PORT_PA06B_PTC_X5                          (_UL_(1) << 6)

#define PIN_PA06B_PTC_Y5                           _L_(6)       /**< PTC signal: Y5 on PA06 mux B*/
#define MUX_PA06B_PTC_Y5                           _L_(1)      
#define PINMUX_PA06B_PTC_Y5                        ((PIN_PA06B_PTC_Y5 << 16) | MUX_PA06B_PTC_Y5)
#define PORT_PA06B_PTC_Y5                          (_UL_(1) << 6)

#define PIN_PA08B_PTC_X6                           _L_(8)       /**< PTC signal: X6 on PA08 mux B*/
#define MUX_PA08B_PTC_X6                           _L_(1)      
#define PINMUX_PA08B_PTC_X6                        ((PIN_PA08B_PTC_X6 << 16) | MUX_PA08B_PTC_X6)
#define PORT_PA08B_PTC_X6                          (_UL_(1) << 8)

#define PIN_PA08B_PTC_Y6                           _L_(8)       /**< PTC signal: Y6 on PA08 mux B*/
#define MUX_PA08B_PTC_Y6                           _L_(1)      
#define PINMUX_PA08B_PTC_Y6                        ((PIN_PA08B_PTC_Y6 << 16) | MUX_PA08B_PTC_Y6)
#define PORT_PA08B_PTC_Y6                          (_UL_(1) << 8)

#define PIN_PA09B_PTC_X7                           _L_(9)       /**< PTC signal: X7 on PA09 mux B*/
#define MUX_PA09B_PTC_X7                           _L_(1)      
#define PINMUX_PA09B_PTC_X7                        ((PIN_PA09B_PTC_X7 << 16) | MUX_PA09B_PTC_X7)
#define PORT_PA09B_PTC_X7                          (_UL_(1) << 9)

#define PIN_PA09B_PTC_Y7                           _L_(9)       /**< PTC signal: Y7 on PA09 mux B*/
#define MUX_PA09B_PTC_Y7                           _L_(1)      
#define PINMUX_PA09B_PTC_Y7                        ((PIN_PA09B_PTC_Y7 << 16) | MUX_PA09B_PTC_Y7)
#define PORT_PA09B_PTC_Y7                          (_UL_(1) << 9)

#define PIN_PA10B_PTC_X8                           _L_(10)      /**< PTC signal: X8 on PA10 mux B*/
#define MUX_PA10B_PTC_X8                           _L_(1)      
#define PINMUX_PA10B_PTC_X8                        ((PIN_PA10B_PTC_X8 << 16) | MUX_PA10B_PTC_X8)
#define PORT_PA10B_PTC_X8                          (_UL_(1) << 10)

#define PIN_PA10B_PTC_Y8                           _L_(10)      /**< PTC signal: Y8 on PA10 mux B*/
#define MUX_PA10B_PTC_Y8                           _L_(1)      
#define PINMUX_PA10B_PTC_Y8                        ((PIN_PA10B_PTC_Y8 << 16) | MUX_PA10B_PTC_Y8)
#define PORT_PA10B_PTC_Y8                          (_UL_(1) << 10)

#define PIN_PA11B_PTC_X9                           _L_(11)      /**< PTC signal: X9 on PA11 mux B*/
#define MUX_PA11B_PTC_X9                           _L_(1)      
#define PINMUX_PA11B_PTC_X9                        ((PIN_PA11B_PTC_X9 << 16) | MUX_PA11B_PTC_X9)
#define PORT_PA11B_PTC_X9                          (_UL_(1) << 11)

#define PIN_PA11B_PTC_Y9                           _L_(11)      /**< PTC signal: Y9 on PA11 mux B*/
#define MUX_PA11B_PTC_Y9                           _L_(1)      
#define PINMUX_PA11B_PTC_Y9                        ((PIN_PA11B_PTC_Y9 << 16) | MUX_PA11B_PTC_Y9)
#define PORT_PA11B_PTC_Y9                          (_UL_(1) << 11)

#define PIN_PA14B_PTC_X10                          _L_(14)      /**< PTC signal: X10 on PA14 mux B*/
#define MUX_PA14B_PTC_X10                          _L_(1)      
#define PINMUX_PA14B_PTC_X10                       ((PIN_PA14B_PTC_X10 << 16) | MUX_PA14B_PTC_X10)
#define PORT_PA14B_PTC_X10                         (_UL_(1) << 14)

#define PIN_PA14B_PTC_Y10                          _L_(14)      /**< PTC signal: Y10 on PA14 mux B*/
#define MUX_PA14B_PTC_Y10                          _L_(1)      
#define PINMUX_PA14B_PTC_Y10                       ((PIN_PA14B_PTC_Y10 << 16) | MUX_PA14B_PTC_Y10)
#define PORT_PA14B_PTC_Y10                         (_UL_(1) << 14)

#define PIN_PA15B_PTC_X11                          _L_(15)      /**< PTC signal: X11 on PA15 mux B*/
#define MUX_PA15B_PTC_X11                          _L_(1)      
#define PINMUX_PA15B_PTC_X11                       ((PIN_PA15B_PTC_X11 << 16) | MUX_PA15B_PTC_X11)
#define PORT_PA15B_PTC_X11                         (_UL_(1) << 15)

#define PIN_PA15B_PTC_Y11                          _L_(15)      /**< PTC signal: Y11 on PA15 mux B*/
#define MUX_PA15B_PTC_Y11                          _L_(1)      
#define PINMUX_PA15B_PTC_Y11                       ((PIN_PA15B_PTC_Y11 << 16) | MUX_PA15B_PTC_Y11)
#define PORT_PA15B_PTC_Y11                         (_UL_(1) << 15)

#define PIN_PA16B_PTC_X12                          _L_(16)      /**< PTC signal: X12 on PA16 mux B*/
#define MUX_PA16B_PTC_X12                          _L_(1)      
#define PINMUX_PA16B_PTC_X12                       ((PIN_PA16B_PTC_X12 << 16) | MUX_PA16B_PTC_X12)
#define PORT_PA16B_PTC_X12                         (_UL_(1) << 16)

#define PIN_PA16B_PTC_Y12                          _L_(16)      /**< PTC signal: Y12 on PA16 mux B*/
#define MUX_PA16B_PTC_Y12                          _L_(1)      
#define PINMUX_PA16B_PTC_Y12                       ((PIN_PA16B_PTC_Y12 << 16) | MUX_PA16B_PTC_Y12)
#define PORT_PA16B_PTC_Y12                         (_UL_(1) << 16)

#define PIN_PA17B_PTC_X13                          _L_(17)      /**< PTC signal: X13 on PA17 mux B*/
#define MUX_PA17B_PTC_X13                          _L_(1)      
#define PINMUX_PA17B_PTC_X13                       ((PIN_PA17B_PTC_X13 << 16) | MUX_PA17B_PTC_X13)
#define PORT_PA17B_PTC_X13                         (_UL_(1) << 17)

#define PIN_PA17B_PTC_Y13                          _L_(17)      /**< PTC signal: Y13 on PA17 mux B*/
#define MUX_PA17B_PTC_Y13                          _L_(1)      
#define PINMUX_PA17B_PTC_Y13                       ((PIN_PA17B_PTC_Y13 << 16) | MUX_PA17B_PTC_Y13)
#define PORT_PA17B_PTC_Y13                         (_UL_(1) << 17)

#define PIN_PA18B_PTC_X14                          _L_(18)      /**< PTC signal: X14 on PA18 mux B*/
#define MUX_PA18B_PTC_X14                          _L_(1)      
#define PINMUX_PA18B_PTC_X14                       ((PIN_PA18B_PTC_X14 << 16) | MUX_PA18B_PTC_X14)
#define PORT_PA18B_PTC_X14                         (_UL_(1) << 18)

#define PIN_PA18B_PTC_Y14                          _L_(18)      /**< PTC signal: Y14 on PA18 mux B*/
#define MUX_PA18B_PTC_Y14                          _L_(1)      
#define PINMUX_PA18B_PTC_Y14                       ((PIN_PA18B_PTC_Y14 << 16) | MUX_PA18B_PTC_Y14)
#define PORT_PA18B_PTC_Y14                         (_UL_(1) << 18)

#define PIN_PA19B_PTC_X15                          _L_(19)      /**< PTC signal: X15 on PA19 mux B*/
#define MUX_PA19B_PTC_X15                          _L_(1)      
#define PINMUX_PA19B_PTC_X15                       ((PIN_PA19B_PTC_X15 << 16) | MUX_PA19B_PTC_X15)
#define PORT_PA19B_PTC_X15                         (_UL_(1) << 19)

#define PIN_PA19B_PTC_Y15                          _L_(19)      /**< PTC signal: Y15 on PA19 mux B*/
#define MUX_PA19B_PTC_Y15                          _L_(1)      
#define PINMUX_PA19B_PTC_Y15                       ((PIN_PA19B_PTC_Y15 << 16) | MUX_PA19B_PTC_Y15)
#define PORT_PA19B_PTC_Y15                         (_UL_(1) << 19)

#define PIN_PA22B_PTC_X16                          _L_(22)      /**< PTC signal: X16 on PA22 mux B*/
#define MUX_PA22B_PTC_X16                          _L_(1)      
#define PINMUX_PA22B_PTC_X16                       ((PIN_PA22B_PTC_X16 << 16) | MUX_PA22B_PTC_X16)
#define PORT_PA22B_PTC_X16                         (_UL_(1) << 22)

#define PIN_PA22B_PTC_Y16                          _L_(22)      /**< PTC signal: Y16 on PA22 mux B*/
#define MUX_PA22B_PTC_Y16                          _L_(1)      
#define PINMUX_PA22B_PTC_Y16                       ((PIN_PA22B_PTC_Y16 << 16) | MUX_PA22B_PTC_Y16)
#define PORT_PA22B_PTC_Y16                         (_UL_(1) << 22)

#define PIN_PA23B_PTC_X17                          _L_(23)      /**< PTC signal: X17 on PA23 mux B*/
#define MUX_PA23B_PTC_X17                          _L_(1)      
#define PINMUX_PA23B_PTC_X17                       ((PIN_PA23B_PTC_X17 << 16) | MUX_PA23B_PTC_X17)
#define PORT_PA23B_PTC_X17                         (_UL_(1) << 23)

#define PIN_PA23B_PTC_Y17                          _L_(23)      /**< PTC signal: Y17 on PA23 mux B*/
#define MUX_PA23B_PTC_Y17                          _L_(1)      
#define PINMUX_PA23B_PTC_Y17                       ((PIN_PA23B_PTC_Y17 << 16) | MUX_PA23B_PTC_Y17)
#define PORT_PA23B_PTC_Y17                         (_UL_(1) << 23)

#define PIN_PA30B_PTC_X18                          _L_(30)      /**< PTC signal: X18 on PA30 mux B*/
#define MUX_PA30B_PTC_X18                          _L_(1)      
#define PINMUX_PA30B_PTC_X18                       ((PIN_PA30B_PTC_X18 << 16) | MUX_PA30B_PTC_X18)
#define PORT_PA30B_PTC_X18                         (_UL_(1) << 30)

#define PIN_PA30B_PTC_Y18                          _L_(30)      /**< PTC signal: Y18 on PA30 mux B*/
#define MUX_PA30B_PTC_Y18                          _L_(1)      
#define PINMUX_PA30B_PTC_Y18                       ((PIN_PA30B_PTC_Y18 << 16) | MUX_PA30B_PTC_Y18)
#define PORT_PA30B_PTC_Y18                         (_UL_(1) << 30)

#define PIN_PA31B_PTC_X19                          _L_(31)      /**< PTC signal: X19 on PA31 mux B*/
#define MUX_PA31B_PTC_X19                          _L_(1)      
#define PINMUX_PA31B_PTC_X19                       ((PIN_PA31B_PTC_X19 << 16) | MUX_PA31B_PTC_X19)
#define PORT_PA31B_PTC_X19                         (_UL_(1) << 31)

#define PIN_PA31B_PTC_Y19                          _L_(31)      /**< PTC signal: Y19 on PA31 mux B*/
#define MUX_PA31B_PTC_Y19                          _L_(1)      
#define PINMUX_PA31B_PTC_Y19                       ((PIN_PA31B_PTC_Y19 << 16) | MUX_PA31B_PTC_Y19)
#define PORT_PA31B_PTC_Y19                         (_UL_(1) << 31)

/* ========== PORT definition for RTC peripheral ========== */
#define PIN_PA08G_RTC_IN0                          _L_(8)       /**< RTC signal: IN0 on PA08 mux G*/
#define MUX_PA08G_RTC_IN0                          _L_(6)      
#define PINMUX_PA08G_RTC_IN0                       ((PIN_PA08G_RTC_IN0 << 16) | MUX_PA08G_RTC_IN0)
#define PORT_PA08G_RTC_IN0                         (_UL_(1) << 8)

#define PIN_PA09G_RTC_IN1                          _L_(9)       /**< RTC signal: IN1 on PA09 mux G*/
#define MUX_PA09G_RTC_IN1                          _L_(6)      
#define PINMUX_PA09G_RTC_IN1                       ((PIN_PA09G_RTC_IN1 << 16) | MUX_PA09G_RTC_IN1)
#define PORT_PA09G_RTC_IN1                         (_UL_(1) << 9)

#define PIN_PA16G_RTC_IN2                          _L_(16)      /**< RTC signal: IN2 on PA16 mux G*/
#define MUX_PA16G_RTC_IN2                          _L_(6)      
#define PINMUX_PA16G_RTC_IN2                       ((PIN_PA16G_RTC_IN2 << 16) | MUX_PA16G_RTC_IN2)
#define PORT_PA16G_RTC_IN2                         (_UL_(1) << 16)

#define PIN_PA17G_RTC_IN3                          _L_(17)      /**< RTC signal: IN3 on PA17 mux G*/
#define MUX_PA17G_RTC_IN3                          _L_(6)      
#define PINMUX_PA17G_RTC_IN3                       ((PIN_PA17G_RTC_IN3 << 16) | MUX_PA17G_RTC_IN3)
#define PORT_PA17G_RTC_IN3                         (_UL_(1) << 17)

#define PIN_PA18G_RTC_OUT0                         _L_(18)      /**< RTC signal: OUT0 on PA18 mux G*/
#define MUX_PA18G_RTC_OUT0                         _L_(6)      
#define PINMUX_PA18G_RTC_OUT0                      ((PIN_PA18G_RTC_OUT0 << 16) | MUX_PA18G_RTC_OUT0)
#define PORT_PA18G_RTC_OUT0                        (_UL_(1) << 18)

#define PIN_PA19G_RTC_OUT1                         _L_(19)      /**< RTC signal: OUT1 on PA19 mux G*/
#define MUX_PA19G_RTC_OUT1                         _L_(6)      
#define PINMUX_PA19G_RTC_OUT1                      ((PIN_PA19G_RTC_OUT1 << 16) | MUX_PA19G_RTC_OUT1)
#define PORT_PA19G_RTC_OUT1                        (_UL_(1) << 19)

#define PIN_PA22G_RTC_OUT2                         _L_(22)      /**< RTC signal: OUT2 on PA22 mux G*/
#define MUX_PA22G_RTC_OUT2                         _L_(6)      
#define PINMUX_PA22G_RTC_OUT2                      ((PIN_PA22G_RTC_OUT2 << 16) | MUX_PA22G_RTC_OUT2)
#define PORT_PA22G_RTC_OUT2                        (_UL_(1) << 22)

#define PIN_PA23G_RTC_OUT3                         _L_(23)      /**< RTC signal: OUT3 on PA23 mux G*/
#define MUX_PA23G_RTC_OUT3                         _L_(6)      
#define PINMUX_PA23G_RTC_OUT3                      ((PIN_PA23G_RTC_OUT3 << 16) | MUX_PA23G_RTC_OUT3)
#define PORT_PA23G_RTC_OUT3                        (_UL_(1) << 23)

/* ========== PORT definition for SERCOM0 peripheral ========== */
#define PIN_PA04D_SERCOM0_PAD0                     _L_(4)       /**< SERCOM0 signal: PAD0 on PA04 mux D*/
#define MUX_PA04D_SERCOM0_PAD0                     _L_(3)      
#define PINMUX_PA04D_SERCOM0_PAD0                  ((PIN_PA04D_SERCOM0_PAD0 << 16) | MUX_PA04D_SERCOM0_PAD0)
#define PORT_PA04D_SERCOM0_PAD0                    (_UL_(1) << 4)

#define PIN_PA16D_SERCOM0_PAD0                     _L_(16)      /**< SERCOM0 signal: PAD0 on PA16 mux D*/
#define MUX_PA16D_SERCOM0_PAD0                     _L_(3)      
#define PINMUX_PA16D_SERCOM0_PAD0                  ((PIN_PA16D_SERCOM0_PAD0 << 16) | MUX_PA16D_SERCOM0_PAD0)
#define PORT_PA16D_SERCOM0_PAD0                    (_UL_(1) << 16)

#define PIN_PA22C_SERCOM0_PAD0                     _L_(22)      /**< SERCOM0 signal: PAD0 on PA22 mux C*/
#define MUX_PA22C_SERCOM0_PAD0                     _L_(2)      
#define PINMUX_PA22C_SERCOM0_PAD0                  ((PIN_PA22C_SERCOM0_PAD0 << 16) | MUX_PA22C_SERCOM0_PAD0)
#define PORT_PA22C_SERCOM0_PAD0                    (_UL_(1) << 22)

#define PIN_PA05D_SERCOM0_PAD1                     _L_(5)       /**< SERCOM0 signal: PAD1 on PA05 mux D*/
#define MUX_PA05D_SERCOM0_PAD1                     _L_(3)      
#define PINMUX_PA05D_SERCOM0_PAD1                  ((PIN_PA05D_SERCOM0_PAD1 << 16) | MUX_PA05D_SERCOM0_PAD1)
#define PORT_PA05D_SERCOM0_PAD1                    (_UL_(1) << 5)

#define PIN_PA17D_SERCOM0_PAD1                     _L_(17)      /**< SERCOM0 signal: PAD1 on PA17 mux D*/
#define MUX_PA17D_SERCOM0_PAD1                     _L_(3)      
#define PINMUX_PA17D_SERCOM0_PAD1                  ((PIN_PA17D_SERCOM0_PAD1 << 16) | MUX_PA17D_SERCOM0_PAD1)
#define PORT_PA17D_SERCOM0_PAD1                    (_UL_(1) << 17)

#define PIN_PA23C_SERCOM0_PAD1                     _L_(23)      /**< SERCOM0 signal: PAD1 on PA23 mux C*/
#define MUX_PA23C_SERCOM0_PAD1                     _L_(2)      
#define PINMUX_PA23C_SERCOM0_PAD1                  ((PIN_PA23C_SERCOM0_PAD1 << 16) | MUX_PA23C_SERCOM0_PAD1)
#define PORT_PA23C_SERCOM0_PAD1                    (_UL_(1) << 23)

#define PIN_PA06D_SERCOM0_PAD2                     _L_(6)       /**< SERCOM0 signal: PAD2 on PA06 mux D*/
#define MUX_PA06D_SERCOM0_PAD2                     _L_(3)      
#define PINMUX_PA06D_SERCOM0_PAD2                  ((PIN_PA06D_SERCOM0_PAD2 << 16) | MUX_PA06D_SERCOM0_PAD2)
#define PORT_PA06D_SERCOM0_PAD2                    (_UL_(1) << 6)

#define PIN_PA14D_SERCOM0_PAD2                     _L_(14)      /**< SERCOM0 signal: PAD2 on PA14 mux D*/
#define MUX_PA14D_SERCOM0_PAD2                     _L_(3)      
#define PINMUX_PA14D_SERCOM0_PAD2                  ((PIN_PA14D_SERCOM0_PAD2 << 16) | MUX_PA14D_SERCOM0_PAD2)
#define PORT_PA14D_SERCOM0_PAD2                    (_UL_(1) << 14)

#define PIN_PA18D_SERCOM0_PAD2                     _L_(18)      /**< SERCOM0 signal: PAD2 on PA18 mux D*/
#define MUX_PA18D_SERCOM0_PAD2                     _L_(3)      
#define PINMUX_PA18D_SERCOM0_PAD2                  ((PIN_PA18D_SERCOM0_PAD2 << 16) | MUX_PA18D_SERCOM0_PAD2)
#define PORT_PA18D_SERCOM0_PAD2                    (_UL_(1) << 18)

#define PIN_PA24C_SERCOM0_PAD2                     _L_(24)      /**< SERCOM0 signal: PAD2 on PA24 mux C*/
#define MUX_PA24C_SERCOM0_PAD2                     _L_(2)      
#define PINMUX_PA24C_SERCOM0_PAD2                  ((PIN_PA24C_SERCOM0_PAD2 << 16) | MUX_PA24C_SERCOM0_PAD2)
#define PORT_PA24C_SERCOM0_PAD2                    (_UL_(1) << 24)

#define PIN_PA02D_SERCOM0_PAD2                     _L_(2)       /**< SERCOM0 signal: PAD2 on PA02 mux D*/
#define MUX_PA02D_SERCOM0_PAD2                     _L_(3)      
#define PINMUX_PA02D_SERCOM0_PAD2                  ((PIN_PA02D_SERCOM0_PAD2 << 16) | MUX_PA02D_SERCOM0_PAD2)
#define PORT_PA02D_SERCOM0_PAD2                    (_UL_(1) << 2)

#define PIN_PA07D_SERCOM0_PAD3                     _L_(7)       /**< SERCOM0 signal: PAD3 on PA07 mux D*/
#define MUX_PA07D_SERCOM0_PAD3                     _L_(3)      
#define PINMUX_PA07D_SERCOM0_PAD3                  ((PIN_PA07D_SERCOM0_PAD3 << 16) | MUX_PA07D_SERCOM0_PAD3)
#define PORT_PA07D_SERCOM0_PAD3                    (_UL_(1) << 7)

#define PIN_PA15D_SERCOM0_PAD3                     _L_(15)      /**< SERCOM0 signal: PAD3 on PA15 mux D*/
#define MUX_PA15D_SERCOM0_PAD3                     _L_(3)      
#define PINMUX_PA15D_SERCOM0_PAD3                  ((PIN_PA15D_SERCOM0_PAD3 << 16) | MUX_PA15D_SERCOM0_PAD3)
#define PORT_PA15D_SERCOM0_PAD3                    (_UL_(1) << 15)

#define PIN_PA19D_SERCOM0_PAD3                     _L_(19)      /**< SERCOM0 signal: PAD3 on PA19 mux D*/
#define MUX_PA19D_SERCOM0_PAD3                     _L_(3)      
#define PINMUX_PA19D_SERCOM0_PAD3                  ((PIN_PA19D_SERCOM0_PAD3 << 16) | MUX_PA19D_SERCOM0_PAD3)
#define PORT_PA19D_SERCOM0_PAD3                    (_UL_(1) << 19)

#define PIN_PA25C_SERCOM0_PAD3                     _L_(25)      /**< SERCOM0 signal: PAD3 on PA25 mux C*/
#define MUX_PA25C_SERCOM0_PAD3                     _L_(2)      
#define PINMUX_PA25C_SERCOM0_PAD3                  ((PIN_PA25C_SERCOM0_PAD3 << 16) | MUX_PA25C_SERCOM0_PAD3)
#define PORT_PA25C_SERCOM0_PAD3                    (_UL_(1) << 25)

#define PIN_PA03D_SERCOM0_PAD3                     _L_(3)       /**< SERCOM0 signal: PAD3 on PA03 mux D*/
#define MUX_PA03D_SERCOM0_PAD3                     _L_(3)      
#define PINMUX_PA03D_SERCOM0_PAD3                  ((PIN_PA03D_SERCOM0_PAD3 << 16) | MUX_PA03D_SERCOM0_PAD3)
#define PORT_PA03D_SERCOM0_PAD3                    (_UL_(1) << 3)

/* ========== PORT definition for SERCOM1 peripheral ========== */
#define PIN_PA16C_SERCOM1_PAD0                     _L_(16)      /**< SERCOM1 signal: PAD0 on PA16 mux C*/
#define MUX_PA16C_SERCOM1_PAD0                     _L_(2)      
#define PINMUX_PA16C_SERCOM1_PAD0                  ((PIN_PA16C_SERCOM1_PAD0 << 16) | MUX_PA16C_SERCOM1_PAD0)
#define PORT_PA16C_SERCOM1_PAD0                    (_UL_(1) << 16)

#define PIN_PA08C_SERCOM1_PAD0                     _L_(8)       /**< SERCOM1 signal: PAD0 on PA08 mux C*/
#define MUX_PA08C_SERCOM1_PAD0                     _L_(2)      
#define PINMUX_PA08C_SERCOM1_PAD0                  ((PIN_PA08C_SERCOM1_PAD0 << 16) | MUX_PA08C_SERCOM1_PAD0)
#define PORT_PA08C_SERCOM1_PAD0                    (_UL_(1) << 8)

#define PIN_PA00D_SERCOM1_PAD0                     _L_(0)       /**< SERCOM1 signal: PAD0 on PA00 mux D*/
#define MUX_PA00D_SERCOM1_PAD0                     _L_(3)      
#define PINMUX_PA00D_SERCOM1_PAD0                  ((PIN_PA00D_SERCOM1_PAD0 << 16) | MUX_PA00D_SERCOM1_PAD0)
#define PORT_PA00D_SERCOM1_PAD0                    (_UL_(1) << 0)

#define PIN_PA17C_SERCOM1_PAD1                     _L_(17)      /**< SERCOM1 signal: PAD1 on PA17 mux C*/
#define MUX_PA17C_SERCOM1_PAD1                     _L_(2)      
#define PINMUX_PA17C_SERCOM1_PAD1                  ((PIN_PA17C_SERCOM1_PAD1 << 16) | MUX_PA17C_SERCOM1_PAD1)
#define PORT_PA17C_SERCOM1_PAD1                    (_UL_(1) << 17)

#define PIN_PA09C_SERCOM1_PAD1                     _L_(9)       /**< SERCOM1 signal: PAD1 on PA09 mux C*/
#define MUX_PA09C_SERCOM1_PAD1                     _L_(2)      
#define PINMUX_PA09C_SERCOM1_PAD1                  ((PIN_PA09C_SERCOM1_PAD1 << 16) | MUX_PA09C_SERCOM1_PAD1)
#define PORT_PA09C_SERCOM1_PAD1                    (_UL_(1) << 9)

#define PIN_PA01D_SERCOM1_PAD1                     _L_(1)       /**< SERCOM1 signal: PAD1 on PA01 mux D*/
#define MUX_PA01D_SERCOM1_PAD1                     _L_(3)      
#define PINMUX_PA01D_SERCOM1_PAD1                  ((PIN_PA01D_SERCOM1_PAD1 << 16) | MUX_PA01D_SERCOM1_PAD1)
#define PORT_PA01D_SERCOM1_PAD1                    (_UL_(1) << 1)

#define PIN_PA18C_SERCOM1_PAD2                     _L_(18)      /**< SERCOM1 signal: PAD2 on PA18 mux C*/
#define MUX_PA18C_SERCOM1_PAD2                     _L_(2)      
#define PINMUX_PA18C_SERCOM1_PAD2                  ((PIN_PA18C_SERCOM1_PAD2 << 16) | MUX_PA18C_SERCOM1_PAD2)
#define PORT_PA18C_SERCOM1_PAD2                    (_UL_(1) << 18)

#define PIN_PA10C_SERCOM1_PAD2                     _L_(10)      /**< SERCOM1 signal: PAD2 on PA10 mux C*/
#define MUX_PA10C_SERCOM1_PAD2                     _L_(2)      
#define PINMUX_PA10C_SERCOM1_PAD2                  ((PIN_PA10C_SERCOM1_PAD2 << 16) | MUX_PA10C_SERCOM1_PAD2)
#define PORT_PA10C_SERCOM1_PAD2                    (_UL_(1) << 10)

#define PIN_PA30D_SERCOM1_PAD2                     _L_(30)      /**< SERCOM1 signal: PAD2 on PA30 mux D*/
#define MUX_PA30D_SERCOM1_PAD2                     _L_(3)      
#define PINMUX_PA30D_SERCOM1_PAD2                  ((PIN_PA30D_SERCOM1_PAD2 << 16) | MUX_PA30D_SERCOM1_PAD2)
#define PORT_PA30D_SERCOM1_PAD2                    (_UL_(1) << 30)

#define PIN_PA19C_SERCOM1_PAD3                     _L_(19)      /**< SERCOM1 signal: PAD3 on PA19 mux C*/
#define MUX_PA19C_SERCOM1_PAD3                     _L_(2)      
#define PINMUX_PA19C_SERCOM1_PAD3                  ((PIN_PA19C_SERCOM1_PAD3 << 16) | MUX_PA19C_SERCOM1_PAD3)
#define PORT_PA19C_SERCOM1_PAD3                    (_UL_(1) << 19)

#define PIN_PA11C_SERCOM1_PAD3                     _L_(11)      /**< SERCOM1 signal: PAD3 on PA11 mux C*/
#define MUX_PA11C_SERCOM1_PAD3                     _L_(2)      
#define PINMUX_PA11C_SERCOM1_PAD3                  ((PIN_PA11C_SERCOM1_PAD3 << 16) | MUX_PA11C_SERCOM1_PAD3)
#define PORT_PA11C_SERCOM1_PAD3                    (_UL_(1) << 11)

#define PIN_PA31D_SERCOM1_PAD3                     _L_(31)      /**< SERCOM1 signal: PAD3 on PA31 mux D*/
#define MUX_PA31D_SERCOM1_PAD3                     _L_(3)      
#define PINMUX_PA31D_SERCOM1_PAD3                  ((PIN_PA31D_SERCOM1_PAD3 << 16) | MUX_PA31D_SERCOM1_PAD3)
#define PORT_PA31D_SERCOM1_PAD3                    (_UL_(1) << 31)

/* ========== PORT definition for SERCOM2 peripheral ========== */
#define PIN_PA08D_SERCOM2_PAD0                     _L_(8)       /**< SERCOM2 signal: PAD0 on PA08 mux D*/
#define MUX_PA08D_SERCOM2_PAD0                     _L_(3)      
#define PINMUX_PA08D_SERCOM2_PAD0                  ((PIN_PA08D_SERCOM2_PAD0 << 16) | MUX_PA08D_SERCOM2_PAD0)
#define PORT_PA08D_SERCOM2_PAD0                    (_UL_(1) << 8)

#define PIN_PA22D_SERCOM2_PAD0                     _L_(22)      /**< SERCOM2 signal: PAD0 on PA22 mux D*/
#define MUX_PA22D_SERCOM2_PAD0                     _L_(3)      
#define PINMUX_PA22D_SERCOM2_PAD0                  ((PIN_PA22D_SERCOM2_PAD0 << 16) | MUX_PA22D_SERCOM2_PAD0)
#define PORT_PA22D_SERCOM2_PAD0                    (_UL_(1) << 22)

#define PIN_PA09D_SERCOM2_PAD1                     _L_(9)       /**< SERCOM2 signal: PAD1 on PA09 mux D*/
#define MUX_PA09D_SERCOM2_PAD1                     _L_(3)      
#define PINMUX_PA09D_SERCOM2_PAD1                  ((PIN_PA09D_SERCOM2_PAD1 << 16) | MUX_PA09D_SERCOM2_PAD1)
#define PORT_PA09D_SERCOM2_PAD1                    (_UL_(1) << 9)

#define PIN_PA23D_SERCOM2_PAD1                     _L_(23)      /**< SERCOM2 signal: PAD1 on PA23 mux D*/
#define MUX_PA23D_SERCOM2_PAD1                     _L_(3)      
#define PINMUX_PA23D_SERCOM2_PAD1                  ((PIN_PA23D_SERCOM2_PAD1 << 16) | MUX_PA23D_SERCOM2_PAD1)
#define PORT_PA23D_SERCOM2_PAD1                    (_UL_(1) << 23)

#define PIN_PA10D_SERCOM2_PAD2                     _L_(10)      /**< SERCOM2 signal: PAD2 on PA10 mux D*/
#define MUX_PA10D_SERCOM2_PAD2                     _L_(3)      
#define PINMUX_PA10D_SERCOM2_PAD2                  ((PIN_PA10D_SERCOM2_PAD2 << 16) | MUX_PA10D_SERCOM2_PAD2)
#define PORT_PA10D_SERCOM2_PAD2                    (_UL_(1) << 10)

#define PIN_PA24D_SERCOM2_PAD2                     _L_(24)      /**< SERCOM2 signal: PAD2 on PA24 mux D*/
#define MUX_PA24D_SERCOM2_PAD2                     _L_(3)      
#define PINMUX_PA24D_SERCOM2_PAD2                  ((PIN_PA24D_SERCOM2_PAD2 << 16) | MUX_PA24D_SERCOM2_PAD2)
#define PORT_PA24D_SERCOM2_PAD2                    (_UL_(1) << 24)

#define PIN_PA14C_SERCOM2_PAD2                     _L_(14)      /**< SERCOM2 signal: PAD2 on PA14 mux C*/
#define MUX_PA14C_SERCOM2_PAD2                     _L_(2)      
#define PINMUX_PA14C_SERCOM2_PAD2                  ((PIN_PA14C_SERCOM2_PAD2 << 16) | MUX_PA14C_SERCOM2_PAD2)
#define PORT_PA14C_SERCOM2_PAD2                    (_UL_(1) << 14)

#define PIN_PA11D_SERCOM2_PAD3                     _L_(11)      /**< SERCOM2 signal: PAD3 on PA11 mux D*/
#define MUX_PA11D_SERCOM2_PAD3                     _L_(3)      
#define PINMUX_PA11D_SERCOM2_PAD3                  ((PIN_PA11D_SERCOM2_PAD3 << 16) | MUX_PA11D_SERCOM2_PAD3)
#define PORT_PA11D_SERCOM2_PAD3                    (_UL_(1) << 11)

#define PIN_PA25D_SERCOM2_PAD3                     _L_(25)      /**< SERCOM2 signal: PAD3 on PA25 mux D*/
#define MUX_PA25D_SERCOM2_PAD3                     _L_(3)      
#define PINMUX_PA25D_SERCOM2_PAD3                  ((PIN_PA25D_SERCOM2_PAD3 << 16) | MUX_PA25D_SERCOM2_PAD3)
#define PORT_PA25D_SERCOM2_PAD3                    (_UL_(1) << 25)

#define PIN_PA15C_SERCOM2_PAD3                     _L_(15)      /**< SERCOM2 signal: PAD3 on PA15 mux C*/
#define MUX_PA15C_SERCOM2_PAD3                     _L_(2)      
#define PINMUX_PA15C_SERCOM2_PAD3                  ((PIN_PA15C_SERCOM2_PAD3 << 16) | MUX_PA15C_SERCOM2_PAD3)
#define PORT_PA15C_SERCOM2_PAD3                    (_UL_(1) << 15)

/* ========== PORT definition for TC0 peripheral ========== */
#define PIN_PA04E_TC0_WO0                          _L_(4)       /**< TC0 signal: WO0 on PA04 mux E*/
#define MUX_PA04E_TC0_WO0                          _L_(4)      
#define PINMUX_PA04E_TC0_WO0                       ((PIN_PA04E_TC0_WO0 << 16) | MUX_PA04E_TC0_WO0)
#define PORT_PA04E_TC0_WO0                         (_UL_(1) << 4)

#define PIN_PA14E_TC0_WO0                          _L_(14)      /**< TC0 signal: WO0 on PA14 mux E*/
#define MUX_PA14E_TC0_WO0                          _L_(4)      
#define PINMUX_PA14E_TC0_WO0                       ((PIN_PA14E_TC0_WO0 << 16) | MUX_PA14E_TC0_WO0)
#define PORT_PA14E_TC0_WO0                         (_UL_(1) << 14)

#define PIN_PA22E_TC0_WO0                          _L_(22)      /**< TC0 signal: WO0 on PA22 mux E*/
#define MUX_PA22E_TC0_WO0                          _L_(4)      
#define PINMUX_PA22E_TC0_WO0                       ((PIN_PA22E_TC0_WO0 << 16) | MUX_PA22E_TC0_WO0)
#define PORT_PA22E_TC0_WO0                         (_UL_(1) << 22)

#define PIN_PA05E_TC0_WO1                          _L_(5)       /**< TC0 signal: WO1 on PA05 mux E*/
#define MUX_PA05E_TC0_WO1                          _L_(4)      
#define PINMUX_PA05E_TC0_WO1                       ((PIN_PA05E_TC0_WO1 << 16) | MUX_PA05E_TC0_WO1)
#define PORT_PA05E_TC0_WO1                         (_UL_(1) << 5)

#define PIN_PA15E_TC0_WO1                          _L_(15)      /**< TC0 signal: WO1 on PA15 mux E*/
#define MUX_PA15E_TC0_WO1                          _L_(4)      
#define PINMUX_PA15E_TC0_WO1                       ((PIN_PA15E_TC0_WO1 << 16) | MUX_PA15E_TC0_WO1)
#define PORT_PA15E_TC0_WO1                         (_UL_(1) << 15)

#define PIN_PA23E_TC0_WO1                          _L_(23)      /**< TC0 signal: WO1 on PA23 mux E*/
#define MUX_PA23E_TC0_WO1                          _L_(4)      
#define PINMUX_PA23E_TC0_WO1                       ((PIN_PA23E_TC0_WO1 << 16) | MUX_PA23E_TC0_WO1)
#define PORT_PA23E_TC0_WO1                         (_UL_(1) << 23)

/* ========== PORT definition for TC1 peripheral ========== */
#define PIN_PA06E_TC1_WO0                          _L_(6)       /**< TC1 signal: WO0 on PA06 mux E*/
#define MUX_PA06E_TC1_WO0                          _L_(4)      
#define PINMUX_PA06E_TC1_WO0                       ((PIN_PA06E_TC1_WO0 << 16) | MUX_PA06E_TC1_WO0)
#define PORT_PA06E_TC1_WO0                         (_UL_(1) << 6)

#define PIN_PA24E_TC1_WO0                          _L_(24)      /**< TC1 signal: WO0 on PA24 mux E*/
#define MUX_PA24E_TC1_WO0                          _L_(4)      
#define PINMUX_PA24E_TC1_WO0                       ((PIN_PA24E_TC1_WO0 << 16) | MUX_PA24E_TC1_WO0)
#define PORT_PA24E_TC1_WO0                         (_UL_(1) << 24)

#define PIN_PA30E_TC1_WO0                          _L_(30)      /**< TC1 signal: WO0 on PA30 mux E*/
#define MUX_PA30E_TC1_WO0                          _L_(4)      
#define PINMUX_PA30E_TC1_WO0                       ((PIN_PA30E_TC1_WO0 << 16) | MUX_PA30E_TC1_WO0)
#define PORT_PA30E_TC1_WO0                         (_UL_(1) << 30)

#define PIN_PA07E_TC1_WO1                          _L_(7)       /**< TC1 signal: WO1 on PA07 mux E*/
#define MUX_PA07E_TC1_WO1                          _L_(4)      
#define PINMUX_PA07E_TC1_WO1                       ((PIN_PA07E_TC1_WO1 << 16) | MUX_PA07E_TC1_WO1)
#define PORT_PA07E_TC1_WO1                         (_UL_(1) << 7)

#define PIN_PA25E_TC1_WO1                          _L_(25)      /**< TC1 signal: WO1 on PA25 mux E*/
#define MUX_PA25E_TC1_WO1                          _L_(4)      
#define PINMUX_PA25E_TC1_WO1                       ((PIN_PA25E_TC1_WO1 << 16) | MUX_PA25E_TC1_WO1)
#define PORT_PA25E_TC1_WO1                         (_UL_(1) << 25)

#define PIN_PA31E_TC1_WO1                          _L_(31)      /**< TC1 signal: WO1 on PA31 mux E*/
#define MUX_PA31E_TC1_WO1                          _L_(4)      
#define PINMUX_PA31E_TC1_WO1                       ((PIN_PA31E_TC1_WO1 << 16) | MUX_PA31E_TC1_WO1)
#define PORT_PA31E_TC1_WO1                         (_UL_(1) << 31)

/* ========== PORT definition for TC2 peripheral ========== */
#define PIN_PA00E_TC2_WO0                          _L_(0)       /**< TC2 signal: WO0 on PA00 mux E*/
#define MUX_PA00E_TC2_WO0                          _L_(4)      
#define PINMUX_PA00E_TC2_WO0                       ((PIN_PA00E_TC2_WO0 << 16) | MUX_PA00E_TC2_WO0)
#define PORT_PA00E_TC2_WO0                         (_UL_(1) << 0)

#define PIN_PA18E_TC2_WO0                          _L_(18)      /**< TC2 signal: WO0 on PA18 mux E*/
#define MUX_PA18E_TC2_WO0                          _L_(4)      
#define PINMUX_PA18E_TC2_WO0                       ((PIN_PA18E_TC2_WO0 << 16) | MUX_PA18E_TC2_WO0)
#define PORT_PA18E_TC2_WO0                         (_UL_(1) << 18)

#define PIN_PA01E_TC2_WO1                          _L_(1)       /**< TC2 signal: WO1 on PA01 mux E*/
#define MUX_PA01E_TC2_WO1                          _L_(4)      
#define PINMUX_PA01E_TC2_WO1                       ((PIN_PA01E_TC2_WO1 << 16) | MUX_PA01E_TC2_WO1)
#define PORT_PA01E_TC2_WO1                         (_UL_(1) << 1)

#define PIN_PA19E_TC2_WO1                          _L_(19)      /**< TC2 signal: WO1 on PA19 mux E*/
#define MUX_PA19E_TC2_WO1                          _L_(4)      
#define PINMUX_PA19E_TC2_WO1                       ((PIN_PA19E_TC2_WO1 << 16) | MUX_PA19E_TC2_WO1)
#define PORT_PA19E_TC2_WO1                         (_UL_(1) << 19)


#endif /* _SAML10E15A_PIO_H_ */
