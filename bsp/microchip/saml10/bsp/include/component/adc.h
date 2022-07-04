/**
 * \file
 *
 * \brief Component description for ADC
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
#ifndef _SAML10_ADC_COMPONENT_H_
#define _SAML10_ADC_COMPONENT_H_
#define _SAML10_ADC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Analog Digital Converter
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR ADC */
/* ========================================================================== */

#define ADC_U2247                      /**< (ADC) Module ID */
#define REV_ADC 0x240                  /**< (ADC) Module revision */

/* -------- ADC_CTRLA : (ADC Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :3;                        /**< bit:   2..4  Reserved */
    uint8_t  SLAVEEN:1;                 /**< bit:      5  Slave Enable                             */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run During Standby                       */
    uint8_t  ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLA_OFFSET                    (0x00)                                        /**<  (ADC_CTRLA) Control A  Offset */
#define ADC_CTRLA_RESETVALUE                _U_(0x00)                                     /**<  (ADC_CTRLA) Control A  Reset Value */

#define ADC_CTRLA_SWRST_Pos                 0                                              /**< (ADC_CTRLA) Software Reset Position */
#define ADC_CTRLA_SWRST_Msk                 (_U_(0x1) << ADC_CTRLA_SWRST_Pos)              /**< (ADC_CTRLA) Software Reset Mask */
#define ADC_CTRLA_SWRST                     ADC_CTRLA_SWRST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLA_SWRST_Msk instead */
#define ADC_CTRLA_ENABLE_Pos                1                                              /**< (ADC_CTRLA) Enable Position */
#define ADC_CTRLA_ENABLE_Msk                (_U_(0x1) << ADC_CTRLA_ENABLE_Pos)             /**< (ADC_CTRLA) Enable Mask */
#define ADC_CTRLA_ENABLE                    ADC_CTRLA_ENABLE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLA_ENABLE_Msk instead */
#define ADC_CTRLA_SLAVEEN_Pos               5                                              /**< (ADC_CTRLA) Slave Enable Position */
#define ADC_CTRLA_SLAVEEN_Msk               (_U_(0x1) << ADC_CTRLA_SLAVEEN_Pos)            /**< (ADC_CTRLA) Slave Enable Mask */
#define ADC_CTRLA_SLAVEEN                   ADC_CTRLA_SLAVEEN_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLA_SLAVEEN_Msk instead */
#define ADC_CTRLA_RUNSTDBY_Pos              6                                              /**< (ADC_CTRLA) Run During Standby Position */
#define ADC_CTRLA_RUNSTDBY_Msk              (_U_(0x1) << ADC_CTRLA_RUNSTDBY_Pos)           /**< (ADC_CTRLA) Run During Standby Mask */
#define ADC_CTRLA_RUNSTDBY                  ADC_CTRLA_RUNSTDBY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLA_RUNSTDBY_Msk instead */
#define ADC_CTRLA_ONDEMAND_Pos              7                                              /**< (ADC_CTRLA) On Demand Control Position */
#define ADC_CTRLA_ONDEMAND_Msk              (_U_(0x1) << ADC_CTRLA_ONDEMAND_Pos)           /**< (ADC_CTRLA) On Demand Control Mask */
#define ADC_CTRLA_ONDEMAND                  ADC_CTRLA_ONDEMAND_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLA_ONDEMAND_Msk instead */
#define ADC_CTRLA_MASK                      _U_(0xE3)                                      /**< \deprecated (ADC_CTRLA) Register MASK  (Use ADC_CTRLA_Msk instead)  */
#define ADC_CTRLA_Msk                       _U_(0xE3)                                      /**< (ADC_CTRLA) Register Mask  */


/* -------- ADC_CTRLB : (ADC Offset: 0x01) (R/W 8) Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PRESCALER:3;               /**< bit:   0..2  Prescaler Configuration                  */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLB_OFFSET                    (0x01)                                        /**<  (ADC_CTRLB) Control B  Offset */
#define ADC_CTRLB_RESETVALUE                _U_(0x00)                                     /**<  (ADC_CTRLB) Control B  Reset Value */

#define ADC_CTRLB_PRESCALER_Pos             0                                              /**< (ADC_CTRLB) Prescaler Configuration Position */
#define ADC_CTRLB_PRESCALER_Msk             (_U_(0x7) << ADC_CTRLB_PRESCALER_Pos)          /**< (ADC_CTRLB) Prescaler Configuration Mask */
#define ADC_CTRLB_PRESCALER(value)          (ADC_CTRLB_PRESCALER_Msk & ((value) << ADC_CTRLB_PRESCALER_Pos))
#define   ADC_CTRLB_PRESCALER_DIV2_Val      _U_(0x0)                                       /**< (ADC_CTRLB) Peripheral clock divided by 2  */
#define   ADC_CTRLB_PRESCALER_DIV4_Val      _U_(0x1)                                       /**< (ADC_CTRLB) Peripheral clock divided by 4  */
#define   ADC_CTRLB_PRESCALER_DIV8_Val      _U_(0x2)                                       /**< (ADC_CTRLB) Peripheral clock divided by 8  */
#define   ADC_CTRLB_PRESCALER_DIV16_Val     _U_(0x3)                                       /**< (ADC_CTRLB) Peripheral clock divided by 16  */
#define   ADC_CTRLB_PRESCALER_DIV32_Val     _U_(0x4)                                       /**< (ADC_CTRLB) Peripheral clock divided by 32  */
#define   ADC_CTRLB_PRESCALER_DIV64_Val     _U_(0x5)                                       /**< (ADC_CTRLB) Peripheral clock divided by 64  */
#define   ADC_CTRLB_PRESCALER_DIV128_Val    _U_(0x6)                                       /**< (ADC_CTRLB) Peripheral clock divided by 128  */
#define   ADC_CTRLB_PRESCALER_DIV256_Val    _U_(0x7)                                       /**< (ADC_CTRLB) Peripheral clock divided by 256  */
#define ADC_CTRLB_PRESCALER_DIV2            (ADC_CTRLB_PRESCALER_DIV2_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 2 Position  */
#define ADC_CTRLB_PRESCALER_DIV4            (ADC_CTRLB_PRESCALER_DIV4_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 4 Position  */
#define ADC_CTRLB_PRESCALER_DIV8            (ADC_CTRLB_PRESCALER_DIV8_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 8 Position  */
#define ADC_CTRLB_PRESCALER_DIV16           (ADC_CTRLB_PRESCALER_DIV16_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 16 Position  */
#define ADC_CTRLB_PRESCALER_DIV32           (ADC_CTRLB_PRESCALER_DIV32_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 32 Position  */
#define ADC_CTRLB_PRESCALER_DIV64           (ADC_CTRLB_PRESCALER_DIV64_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 64 Position  */
#define ADC_CTRLB_PRESCALER_DIV128          (ADC_CTRLB_PRESCALER_DIV128_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 128 Position  */
#define ADC_CTRLB_PRESCALER_DIV256          (ADC_CTRLB_PRESCALER_DIV256_Val << ADC_CTRLB_PRESCALER_Pos)  /**< (ADC_CTRLB) Peripheral clock divided by 256 Position  */
#define ADC_CTRLB_MASK                      _U_(0x07)                                      /**< \deprecated (ADC_CTRLB) Register MASK  (Use ADC_CTRLB_Msk instead)  */
#define ADC_CTRLB_Msk                       _U_(0x07)                                      /**< (ADC_CTRLB) Register Mask  */


/* -------- ADC_REFCTRL : (ADC Offset: 0x02) (R/W 8) Reference Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  REFSEL:4;                  /**< bit:   0..3  Reference Selection                      */
    uint8_t  :3;                        /**< bit:   4..6  Reserved */
    uint8_t  REFCOMP:1;                 /**< bit:      7  Reference Buffer Offset Compensation Enable */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_REFCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_REFCTRL_OFFSET                  (0x02)                                        /**<  (ADC_REFCTRL) Reference Control  Offset */
#define ADC_REFCTRL_RESETVALUE              _U_(0x00)                                     /**<  (ADC_REFCTRL) Reference Control  Reset Value */

#define ADC_REFCTRL_REFSEL_Pos              0                                              /**< (ADC_REFCTRL) Reference Selection Position */
#define ADC_REFCTRL_REFSEL_Msk              (_U_(0xF) << ADC_REFCTRL_REFSEL_Pos)           /**< (ADC_REFCTRL) Reference Selection Mask */
#define ADC_REFCTRL_REFSEL(value)           (ADC_REFCTRL_REFSEL_Msk & ((value) << ADC_REFCTRL_REFSEL_Pos))
#define   ADC_REFCTRL_REFSEL_INTREF_Val     _U_(0x0)                                       /**< (ADC_REFCTRL) Internal Bandgap Reference  */
#define   ADC_REFCTRL_REFSEL_INTVCC0_Val    _U_(0x1)                                       /**< (ADC_REFCTRL) 1/1.6 VDDANA  */
#define   ADC_REFCTRL_REFSEL_INTVCC1_Val    _U_(0x2)                                       /**< (ADC_REFCTRL) 1/2 VDDANA  */
#define   ADC_REFCTRL_REFSEL_AREFA_Val      _U_(0x3)                                       /**< (ADC_REFCTRL) External Reference  */
#define   ADC_REFCTRL_REFSEL_AREFB_Val      _U_(0x4)                                       /**< (ADC_REFCTRL) External Reference  */
#define   ADC_REFCTRL_REFSEL_INTVCC2_Val    _U_(0x5)                                       /**< (ADC_REFCTRL) VCCANA  */
#define ADC_REFCTRL_REFSEL_INTREF           (ADC_REFCTRL_REFSEL_INTREF_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) Internal Bandgap Reference Position  */
#define ADC_REFCTRL_REFSEL_INTVCC0          (ADC_REFCTRL_REFSEL_INTVCC0_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) 1/1.6 VDDANA Position  */
#define ADC_REFCTRL_REFSEL_INTVCC1          (ADC_REFCTRL_REFSEL_INTVCC1_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) 1/2 VDDANA Position  */
#define ADC_REFCTRL_REFSEL_AREFA            (ADC_REFCTRL_REFSEL_AREFA_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) External Reference Position  */
#define ADC_REFCTRL_REFSEL_AREFB            (ADC_REFCTRL_REFSEL_AREFB_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) External Reference Position  */
#define ADC_REFCTRL_REFSEL_INTVCC2          (ADC_REFCTRL_REFSEL_INTVCC2_Val << ADC_REFCTRL_REFSEL_Pos)  /**< (ADC_REFCTRL) VCCANA Position  */
#define ADC_REFCTRL_REFCOMP_Pos             7                                              /**< (ADC_REFCTRL) Reference Buffer Offset Compensation Enable Position */
#define ADC_REFCTRL_REFCOMP_Msk             (_U_(0x1) << ADC_REFCTRL_REFCOMP_Pos)          /**< (ADC_REFCTRL) Reference Buffer Offset Compensation Enable Mask */
#define ADC_REFCTRL_REFCOMP                 ADC_REFCTRL_REFCOMP_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_REFCTRL_REFCOMP_Msk instead */
#define ADC_REFCTRL_MASK                    _U_(0x8F)                                      /**< \deprecated (ADC_REFCTRL) Register MASK  (Use ADC_REFCTRL_Msk instead)  */
#define ADC_REFCTRL_Msk                     _U_(0x8F)                                      /**< (ADC_REFCTRL) Register Mask  */


/* -------- ADC_EVCTRL : (ADC Offset: 0x03) (R/W 8) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  FLUSHEI:1;                 /**< bit:      0  Flush Event Input Enable                 */
    uint8_t  STARTEI:1;                 /**< bit:      1  Start Conversion Event Input Enable      */
    uint8_t  FLUSHINV:1;                /**< bit:      2  Flush Event Invert Enable                */
    uint8_t  STARTINV:1;                /**< bit:      3  Satrt Event Invert Enable                */
    uint8_t  RESRDYEO:1;                /**< bit:      4  Result Ready Event Out                   */
    uint8_t  WINMONEO:1;                /**< bit:      5  Window Monitor Event Out                 */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_EVCTRL_OFFSET                   (0x03)                                        /**<  (ADC_EVCTRL) Event Control  Offset */
#define ADC_EVCTRL_RESETVALUE               _U_(0x00)                                     /**<  (ADC_EVCTRL) Event Control  Reset Value */

#define ADC_EVCTRL_FLUSHEI_Pos              0                                              /**< (ADC_EVCTRL) Flush Event Input Enable Position */
#define ADC_EVCTRL_FLUSHEI_Msk              (_U_(0x1) << ADC_EVCTRL_FLUSHEI_Pos)           /**< (ADC_EVCTRL) Flush Event Input Enable Mask */
#define ADC_EVCTRL_FLUSHEI                  ADC_EVCTRL_FLUSHEI_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_FLUSHEI_Msk instead */
#define ADC_EVCTRL_STARTEI_Pos              1                                              /**< (ADC_EVCTRL) Start Conversion Event Input Enable Position */
#define ADC_EVCTRL_STARTEI_Msk              (_U_(0x1) << ADC_EVCTRL_STARTEI_Pos)           /**< (ADC_EVCTRL) Start Conversion Event Input Enable Mask */
#define ADC_EVCTRL_STARTEI                  ADC_EVCTRL_STARTEI_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_STARTEI_Msk instead */
#define ADC_EVCTRL_FLUSHINV_Pos             2                                              /**< (ADC_EVCTRL) Flush Event Invert Enable Position */
#define ADC_EVCTRL_FLUSHINV_Msk             (_U_(0x1) << ADC_EVCTRL_FLUSHINV_Pos)          /**< (ADC_EVCTRL) Flush Event Invert Enable Mask */
#define ADC_EVCTRL_FLUSHINV                 ADC_EVCTRL_FLUSHINV_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_FLUSHINV_Msk instead */
#define ADC_EVCTRL_STARTINV_Pos             3                                              /**< (ADC_EVCTRL) Satrt Event Invert Enable Position */
#define ADC_EVCTRL_STARTINV_Msk             (_U_(0x1) << ADC_EVCTRL_STARTINV_Pos)          /**< (ADC_EVCTRL) Satrt Event Invert Enable Mask */
#define ADC_EVCTRL_STARTINV                 ADC_EVCTRL_STARTINV_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_STARTINV_Msk instead */
#define ADC_EVCTRL_RESRDYEO_Pos             4                                              /**< (ADC_EVCTRL) Result Ready Event Out Position */
#define ADC_EVCTRL_RESRDYEO_Msk             (_U_(0x1) << ADC_EVCTRL_RESRDYEO_Pos)          /**< (ADC_EVCTRL) Result Ready Event Out Mask */
#define ADC_EVCTRL_RESRDYEO                 ADC_EVCTRL_RESRDYEO_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_RESRDYEO_Msk instead */
#define ADC_EVCTRL_WINMONEO_Pos             5                                              /**< (ADC_EVCTRL) Window Monitor Event Out Position */
#define ADC_EVCTRL_WINMONEO_Msk             (_U_(0x1) << ADC_EVCTRL_WINMONEO_Pos)          /**< (ADC_EVCTRL) Window Monitor Event Out Mask */
#define ADC_EVCTRL_WINMONEO                 ADC_EVCTRL_WINMONEO_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_EVCTRL_WINMONEO_Msk instead */
#define ADC_EVCTRL_MASK                     _U_(0x3F)                                      /**< \deprecated (ADC_EVCTRL) Register MASK  (Use ADC_EVCTRL_Msk instead)  */
#define ADC_EVCTRL_Msk                      _U_(0x3F)                                      /**< (ADC_EVCTRL) Register Mask  */


/* -------- ADC_INTENCLR : (ADC Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RESRDY:1;                  /**< bit:      0  Result Ready Interrupt Disable           */
    uint8_t  OVERRUN:1;                 /**< bit:      1  Overrun Interrupt Disable                */
    uint8_t  WINMON:1;                  /**< bit:      2  Window Monitor Interrupt Disable         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTENCLR_OFFSET                 (0x04)                                        /**<  (ADC_INTENCLR) Interrupt Enable Clear  Offset */
#define ADC_INTENCLR_RESETVALUE             _U_(0x00)                                     /**<  (ADC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define ADC_INTENCLR_RESRDY_Pos             0                                              /**< (ADC_INTENCLR) Result Ready Interrupt Disable Position */
#define ADC_INTENCLR_RESRDY_Msk             (_U_(0x1) << ADC_INTENCLR_RESRDY_Pos)          /**< (ADC_INTENCLR) Result Ready Interrupt Disable Mask */
#define ADC_INTENCLR_RESRDY                 ADC_INTENCLR_RESRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENCLR_RESRDY_Msk instead */
#define ADC_INTENCLR_OVERRUN_Pos            1                                              /**< (ADC_INTENCLR) Overrun Interrupt Disable Position */
#define ADC_INTENCLR_OVERRUN_Msk            (_U_(0x1) << ADC_INTENCLR_OVERRUN_Pos)         /**< (ADC_INTENCLR) Overrun Interrupt Disable Mask */
#define ADC_INTENCLR_OVERRUN                ADC_INTENCLR_OVERRUN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENCLR_OVERRUN_Msk instead */
#define ADC_INTENCLR_WINMON_Pos             2                                              /**< (ADC_INTENCLR) Window Monitor Interrupt Disable Position */
#define ADC_INTENCLR_WINMON_Msk             (_U_(0x1) << ADC_INTENCLR_WINMON_Pos)          /**< (ADC_INTENCLR) Window Monitor Interrupt Disable Mask */
#define ADC_INTENCLR_WINMON                 ADC_INTENCLR_WINMON_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENCLR_WINMON_Msk instead */
#define ADC_INTENCLR_MASK                   _U_(0x07)                                      /**< \deprecated (ADC_INTENCLR) Register MASK  (Use ADC_INTENCLR_Msk instead)  */
#define ADC_INTENCLR_Msk                    _U_(0x07)                                      /**< (ADC_INTENCLR) Register Mask  */


/* -------- ADC_INTENSET : (ADC Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RESRDY:1;                  /**< bit:      0  Result Ready Interrupt Enable            */
    uint8_t  OVERRUN:1;                 /**< bit:      1  Overrun Interrupt Enable                 */
    uint8_t  WINMON:1;                  /**< bit:      2  Window Monitor Interrupt Enable          */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTENSET_OFFSET                 (0x05)                                        /**<  (ADC_INTENSET) Interrupt Enable Set  Offset */
#define ADC_INTENSET_RESETVALUE             _U_(0x00)                                     /**<  (ADC_INTENSET) Interrupt Enable Set  Reset Value */

#define ADC_INTENSET_RESRDY_Pos             0                                              /**< (ADC_INTENSET) Result Ready Interrupt Enable Position */
#define ADC_INTENSET_RESRDY_Msk             (_U_(0x1) << ADC_INTENSET_RESRDY_Pos)          /**< (ADC_INTENSET) Result Ready Interrupt Enable Mask */
#define ADC_INTENSET_RESRDY                 ADC_INTENSET_RESRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENSET_RESRDY_Msk instead */
#define ADC_INTENSET_OVERRUN_Pos            1                                              /**< (ADC_INTENSET) Overrun Interrupt Enable Position */
#define ADC_INTENSET_OVERRUN_Msk            (_U_(0x1) << ADC_INTENSET_OVERRUN_Pos)         /**< (ADC_INTENSET) Overrun Interrupt Enable Mask */
#define ADC_INTENSET_OVERRUN                ADC_INTENSET_OVERRUN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENSET_OVERRUN_Msk instead */
#define ADC_INTENSET_WINMON_Pos             2                                              /**< (ADC_INTENSET) Window Monitor Interrupt Enable Position */
#define ADC_INTENSET_WINMON_Msk             (_U_(0x1) << ADC_INTENSET_WINMON_Pos)          /**< (ADC_INTENSET) Window Monitor Interrupt Enable Mask */
#define ADC_INTENSET_WINMON                 ADC_INTENSET_WINMON_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTENSET_WINMON_Msk instead */
#define ADC_INTENSET_MASK                   _U_(0x07)                                      /**< \deprecated (ADC_INTENSET) Register MASK  (Use ADC_INTENSET_Msk instead)  */
#define ADC_INTENSET_Msk                    _U_(0x07)                                      /**< (ADC_INTENSET) Register Mask  */


/* -------- ADC_INTFLAG : (ADC Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t RESRDY:1;                  /**< bit:      0  Result Ready Interrupt Flag              */
    __I uint8_t OVERRUN:1;                 /**< bit:      1  Overrun Interrupt Flag                   */
    __I uint8_t WINMON:1;                  /**< bit:      2  Window Monitor Interrupt Flag            */
    __I uint8_t :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTFLAG_OFFSET                  (0x06)                                        /**<  (ADC_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define ADC_INTFLAG_RESETVALUE              _U_(0x00)                                     /**<  (ADC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define ADC_INTFLAG_RESRDY_Pos              0                                              /**< (ADC_INTFLAG) Result Ready Interrupt Flag Position */
#define ADC_INTFLAG_RESRDY_Msk              (_U_(0x1) << ADC_INTFLAG_RESRDY_Pos)           /**< (ADC_INTFLAG) Result Ready Interrupt Flag Mask */
#define ADC_INTFLAG_RESRDY                  ADC_INTFLAG_RESRDY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTFLAG_RESRDY_Msk instead */
#define ADC_INTFLAG_OVERRUN_Pos             1                                              /**< (ADC_INTFLAG) Overrun Interrupt Flag Position */
#define ADC_INTFLAG_OVERRUN_Msk             (_U_(0x1) << ADC_INTFLAG_OVERRUN_Pos)          /**< (ADC_INTFLAG) Overrun Interrupt Flag Mask */
#define ADC_INTFLAG_OVERRUN                 ADC_INTFLAG_OVERRUN_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTFLAG_OVERRUN_Msk instead */
#define ADC_INTFLAG_WINMON_Pos              2                                              /**< (ADC_INTFLAG) Window Monitor Interrupt Flag Position */
#define ADC_INTFLAG_WINMON_Msk              (_U_(0x1) << ADC_INTFLAG_WINMON_Pos)           /**< (ADC_INTFLAG) Window Monitor Interrupt Flag Mask */
#define ADC_INTFLAG_WINMON                  ADC_INTFLAG_WINMON_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_INTFLAG_WINMON_Msk instead */
#define ADC_INTFLAG_MASK                    _U_(0x07)                                      /**< \deprecated (ADC_INTFLAG) Register MASK  (Use ADC_INTFLAG_Msk instead)  */
#define ADC_INTFLAG_Msk                     _U_(0x07)                                      /**< (ADC_INTFLAG) Register Mask  */


/* -------- ADC_SEQSTATUS : (ADC Offset: 0x07) (R/ 8) Sequence Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SEQSTATE:5;                /**< bit:   0..4  Sequence State                           */
    uint8_t  :2;                        /**< bit:   5..6  Reserved */
    uint8_t  SEQBUSY:1;                 /**< bit:      7  Sequence Busy                            */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_SEQSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SEQSTATUS_OFFSET                (0x07)                                        /**<  (ADC_SEQSTATUS) Sequence Status  Offset */
#define ADC_SEQSTATUS_RESETVALUE            _U_(0x00)                                     /**<  (ADC_SEQSTATUS) Sequence Status  Reset Value */

#define ADC_SEQSTATUS_SEQSTATE_Pos          0                                              /**< (ADC_SEQSTATUS) Sequence State Position */
#define ADC_SEQSTATUS_SEQSTATE_Msk          (_U_(0x1F) << ADC_SEQSTATUS_SEQSTATE_Pos)      /**< (ADC_SEQSTATUS) Sequence State Mask */
#define ADC_SEQSTATUS_SEQSTATE(value)       (ADC_SEQSTATUS_SEQSTATE_Msk & ((value) << ADC_SEQSTATUS_SEQSTATE_Pos))
#define ADC_SEQSTATUS_SEQBUSY_Pos           7                                              /**< (ADC_SEQSTATUS) Sequence Busy Position */
#define ADC_SEQSTATUS_SEQBUSY_Msk           (_U_(0x1) << ADC_SEQSTATUS_SEQBUSY_Pos)        /**< (ADC_SEQSTATUS) Sequence Busy Mask */
#define ADC_SEQSTATUS_SEQBUSY               ADC_SEQSTATUS_SEQBUSY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SEQSTATUS_SEQBUSY_Msk instead */
#define ADC_SEQSTATUS_MASK                  _U_(0x9F)                                      /**< \deprecated (ADC_SEQSTATUS) Register MASK  (Use ADC_SEQSTATUS_Msk instead)  */
#define ADC_SEQSTATUS_Msk                   _U_(0x9F)                                      /**< (ADC_SEQSTATUS) Register Mask  */


/* -------- ADC_INPUTCTRL : (ADC Offset: 0x08) (R/W 16) Input Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t MUXPOS:5;                  /**< bit:   0..4  Positive Mux Input Selection             */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t MUXNEG:5;                  /**< bit:  8..12  Negative Mux Input Selection             */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_INPUTCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INPUTCTRL_OFFSET                (0x08)                                        /**<  (ADC_INPUTCTRL) Input Control  Offset */
#define ADC_INPUTCTRL_RESETVALUE            _U_(0x00)                                     /**<  (ADC_INPUTCTRL) Input Control  Reset Value */

#define ADC_INPUTCTRL_MUXPOS_Pos            0                                              /**< (ADC_INPUTCTRL) Positive Mux Input Selection Position */
#define ADC_INPUTCTRL_MUXPOS_Msk            (_U_(0x1F) << ADC_INPUTCTRL_MUXPOS_Pos)        /**< (ADC_INPUTCTRL) Positive Mux Input Selection Mask */
#define ADC_INPUTCTRL_MUXPOS(value)         (ADC_INPUTCTRL_MUXPOS_Msk & ((value) << ADC_INPUTCTRL_MUXPOS_Pos))
#define   ADC_INPUTCTRL_MUXPOS_AIN0_Val     _U_(0x0)                                       /**< (ADC_INPUTCTRL) ADC AIN0 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN1_Val     _U_(0x1)                                       /**< (ADC_INPUTCTRL) ADC AIN1 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN2_Val     _U_(0x2)                                       /**< (ADC_INPUTCTRL) ADC AIN2 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN3_Val     _U_(0x3)                                       /**< (ADC_INPUTCTRL) ADC AIN3 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN4_Val     _U_(0x4)                                       /**< (ADC_INPUTCTRL) ADC AIN4 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN5_Val     _U_(0x5)                                       /**< (ADC_INPUTCTRL) ADC AIN5 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN6_Val     _U_(0x6)                                       /**< (ADC_INPUTCTRL) ADC AIN6 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN7_Val     _U_(0x7)                                       /**< (ADC_INPUTCTRL) ADC AIN7 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN8_Val     _U_(0x8)                                       /**< (ADC_INPUTCTRL) ADC AIN8 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN9_Val     _U_(0x9)                                       /**< (ADC_INPUTCTRL) ADC AIN9 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN10_Val    _U_(0xA)                                       /**< (ADC_INPUTCTRL) ADC AIN10 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN11_Val    _U_(0xB)                                       /**< (ADC_INPUTCTRL) ADC AIN11 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN12_Val    _U_(0xC)                                       /**< (ADC_INPUTCTRL) ADC AIN12 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN13_Val    _U_(0xD)                                       /**< (ADC_INPUTCTRL) ADC AIN13 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN14_Val    _U_(0xE)                                       /**< (ADC_INPUTCTRL) ADC AIN14 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN15_Val    _U_(0xF)                                       /**< (ADC_INPUTCTRL) ADC AIN15 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN16_Val    _U_(0x10)                                      /**< (ADC_INPUTCTRL) ADC AIN16 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN17_Val    _U_(0x11)                                      /**< (ADC_INPUTCTRL) ADC AIN17 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN18_Val    _U_(0x12)                                      /**< (ADC_INPUTCTRL) ADC AIN18 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN19_Val    _U_(0x13)                                      /**< (ADC_INPUTCTRL) ADC AIN19 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN20_Val    _U_(0x14)                                      /**< (ADC_INPUTCTRL) ADC AIN20 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN21_Val    _U_(0x15)                                      /**< (ADC_INPUTCTRL) ADC AIN21 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN22_Val    _U_(0x16)                                      /**< (ADC_INPUTCTRL) ADC AIN22 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_AIN23_Val    _U_(0x17)                                      /**< (ADC_INPUTCTRL) ADC AIN23 Pin  */
#define   ADC_INPUTCTRL_MUXPOS_TEMP_Val     _U_(0x18)                                      /**< (ADC_INPUTCTRL) Temperature Sensor  */
#define   ADC_INPUTCTRL_MUXPOS_BANDGAP_Val  _U_(0x19)                                      /**< (ADC_INPUTCTRL) Bandgap Voltage  */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val _U_(0x1A)                                      /**< (ADC_INPUTCTRL) 1/4 Scaled Core Supply  */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val _U_(0x1B)                                      /**< (ADC_INPUTCTRL) 1/4 Scaled I/O Supply  */
#define   ADC_INPUTCTRL_MUXPOS_DAC_Val      _U_(0x1C)                                      /**< (ADC_INPUTCTRL) DAC Output  */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDVBAT_Val _U_(0x1D)                                      /**< (ADC_INPUTCTRL) 1/4 Scaled VBAT Supply  */
#define   ADC_INPUTCTRL_MUXPOS_OPAMP01_Val  _U_(0x1E)                                      /**< (ADC_INPUTCTRL) OPAMP0 or OPAMP1 output  */
#define   ADC_INPUTCTRL_MUXPOS_OPAMP2_Val   _U_(0x1F)                                      /**< (ADC_INPUTCTRL) OPAMP2 output  */
#define ADC_INPUTCTRL_MUXPOS_AIN0           (ADC_INPUTCTRL_MUXPOS_AIN0_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN0 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN1           (ADC_INPUTCTRL_MUXPOS_AIN1_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN1 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN2           (ADC_INPUTCTRL_MUXPOS_AIN2_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN2 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN3           (ADC_INPUTCTRL_MUXPOS_AIN3_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN3 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN4           (ADC_INPUTCTRL_MUXPOS_AIN4_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN4 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN5           (ADC_INPUTCTRL_MUXPOS_AIN5_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN5 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN6           (ADC_INPUTCTRL_MUXPOS_AIN6_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN6 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN7           (ADC_INPUTCTRL_MUXPOS_AIN7_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN7 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN8           (ADC_INPUTCTRL_MUXPOS_AIN8_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN8 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN9           (ADC_INPUTCTRL_MUXPOS_AIN9_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN9 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN10          (ADC_INPUTCTRL_MUXPOS_AIN10_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN10 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN11          (ADC_INPUTCTRL_MUXPOS_AIN11_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN11 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN12          (ADC_INPUTCTRL_MUXPOS_AIN12_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN12 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN13          (ADC_INPUTCTRL_MUXPOS_AIN13_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN13 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN14          (ADC_INPUTCTRL_MUXPOS_AIN14_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN14 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN15          (ADC_INPUTCTRL_MUXPOS_AIN15_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN15 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN16          (ADC_INPUTCTRL_MUXPOS_AIN16_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN16 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN17          (ADC_INPUTCTRL_MUXPOS_AIN17_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN17 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN18          (ADC_INPUTCTRL_MUXPOS_AIN18_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN18 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN19          (ADC_INPUTCTRL_MUXPOS_AIN19_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN19 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN20          (ADC_INPUTCTRL_MUXPOS_AIN20_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN20 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN21          (ADC_INPUTCTRL_MUXPOS_AIN21_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN21 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN22          (ADC_INPUTCTRL_MUXPOS_AIN22_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN22 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_AIN23          (ADC_INPUTCTRL_MUXPOS_AIN23_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) ADC AIN23 Pin Position  */
#define ADC_INPUTCTRL_MUXPOS_TEMP           (ADC_INPUTCTRL_MUXPOS_TEMP_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) Temperature Sensor Position  */
#define ADC_INPUTCTRL_MUXPOS_BANDGAP        (ADC_INPUTCTRL_MUXPOS_BANDGAP_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) Bandgap Voltage Position  */
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC  (ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) 1/4 Scaled Core Supply Position  */
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC    (ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) 1/4 Scaled I/O Supply Position  */
#define ADC_INPUTCTRL_MUXPOS_DAC            (ADC_INPUTCTRL_MUXPOS_DAC_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) DAC Output Position  */
#define ADC_INPUTCTRL_MUXPOS_SCALEDVBAT     (ADC_INPUTCTRL_MUXPOS_SCALEDVBAT_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) 1/4 Scaled VBAT Supply Position  */
#define ADC_INPUTCTRL_MUXPOS_OPAMP01        (ADC_INPUTCTRL_MUXPOS_OPAMP01_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) OPAMP0 or OPAMP1 output Position  */
#define ADC_INPUTCTRL_MUXPOS_OPAMP2         (ADC_INPUTCTRL_MUXPOS_OPAMP2_Val << ADC_INPUTCTRL_MUXPOS_Pos)  /**< (ADC_INPUTCTRL) OPAMP2 output Position  */
#define ADC_INPUTCTRL_MUXNEG_Pos            8                                              /**< (ADC_INPUTCTRL) Negative Mux Input Selection Position */
#define ADC_INPUTCTRL_MUXNEG_Msk            (_U_(0x1F) << ADC_INPUTCTRL_MUXNEG_Pos)        /**< (ADC_INPUTCTRL) Negative Mux Input Selection Mask */
#define ADC_INPUTCTRL_MUXNEG(value)         (ADC_INPUTCTRL_MUXNEG_Msk & ((value) << ADC_INPUTCTRL_MUXNEG_Pos))
#define   ADC_INPUTCTRL_MUXNEG_AIN0_Val     _U_(0x0)                                       /**< (ADC_INPUTCTRL) ADC AIN0 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN1_Val     _U_(0x1)                                       /**< (ADC_INPUTCTRL) ADC AIN1 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN2_Val     _U_(0x2)                                       /**< (ADC_INPUTCTRL) ADC AIN2 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN3_Val     _U_(0x3)                                       /**< (ADC_INPUTCTRL) ADC AIN3 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN4_Val     _U_(0x4)                                       /**< (ADC_INPUTCTRL) ADC AIN4 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN5_Val     _U_(0x5)                                       /**< (ADC_INPUTCTRL) ADC AIN5 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN6_Val     _U_(0x6)                                       /**< (ADC_INPUTCTRL) ADC AIN6 Pin  */
#define   ADC_INPUTCTRL_MUXNEG_AIN7_Val     _U_(0x7)                                       /**< (ADC_INPUTCTRL) ADC AIN7 Pin  */
#define ADC_INPUTCTRL_MUXNEG_AIN0           (ADC_INPUTCTRL_MUXNEG_AIN0_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN0 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN1           (ADC_INPUTCTRL_MUXNEG_AIN1_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN1 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN2           (ADC_INPUTCTRL_MUXNEG_AIN2_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN2 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN3           (ADC_INPUTCTRL_MUXNEG_AIN3_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN3 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN4           (ADC_INPUTCTRL_MUXNEG_AIN4_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN4 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN5           (ADC_INPUTCTRL_MUXNEG_AIN5_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN5 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN6           (ADC_INPUTCTRL_MUXNEG_AIN6_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN6 Pin Position  */
#define ADC_INPUTCTRL_MUXNEG_AIN7           (ADC_INPUTCTRL_MUXNEG_AIN7_Val << ADC_INPUTCTRL_MUXNEG_Pos)  /**< (ADC_INPUTCTRL) ADC AIN7 Pin Position  */
#define ADC_INPUTCTRL_MASK                  _U_(0x1F1F)                                    /**< \deprecated (ADC_INPUTCTRL) Register MASK  (Use ADC_INPUTCTRL_Msk instead)  */
#define ADC_INPUTCTRL_Msk                   _U_(0x1F1F)                                    /**< (ADC_INPUTCTRL) Register Mask  */


/* -------- ADC_CTRLC : (ADC Offset: 0x0a) (R/W 16) Control C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DIFFMODE:1;                /**< bit:      0  Differential Mode                        */
    uint16_t LEFTADJ:1;                 /**< bit:      1  Left-Adjusted Result                     */
    uint16_t FREERUN:1;                 /**< bit:      2  Free Running Mode                        */
    uint16_t CORREN:1;                  /**< bit:      3  Digital Correction Logic Enable          */
    uint16_t RESSEL:2;                  /**< bit:   4..5  Conversion Result Resolution             */
    uint16_t :1;                        /**< bit:      6  Reserved */
    uint16_t R2R:1;                     /**< bit:      7  Rail-to-Rail mode enable                 */
    uint16_t WINMODE:3;                 /**< bit:  8..10  Window Monitor Mode                      */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t DUALSEL:2;                 /**< bit: 12..13  Dual Mode Trigger Selection              */
    uint16_t :2;                        /**< bit: 14..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_CTRLC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLC_OFFSET                    (0x0A)                                        /**<  (ADC_CTRLC) Control C  Offset */
#define ADC_CTRLC_RESETVALUE                _U_(0x00)                                     /**<  (ADC_CTRLC) Control C  Reset Value */

#define ADC_CTRLC_DIFFMODE_Pos              0                                              /**< (ADC_CTRLC) Differential Mode Position */
#define ADC_CTRLC_DIFFMODE_Msk              (_U_(0x1) << ADC_CTRLC_DIFFMODE_Pos)           /**< (ADC_CTRLC) Differential Mode Mask */
#define ADC_CTRLC_DIFFMODE                  ADC_CTRLC_DIFFMODE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLC_DIFFMODE_Msk instead */
#define ADC_CTRLC_LEFTADJ_Pos               1                                              /**< (ADC_CTRLC) Left-Adjusted Result Position */
#define ADC_CTRLC_LEFTADJ_Msk               (_U_(0x1) << ADC_CTRLC_LEFTADJ_Pos)            /**< (ADC_CTRLC) Left-Adjusted Result Mask */
#define ADC_CTRLC_LEFTADJ                   ADC_CTRLC_LEFTADJ_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLC_LEFTADJ_Msk instead */
#define ADC_CTRLC_FREERUN_Pos               2                                              /**< (ADC_CTRLC) Free Running Mode Position */
#define ADC_CTRLC_FREERUN_Msk               (_U_(0x1) << ADC_CTRLC_FREERUN_Pos)            /**< (ADC_CTRLC) Free Running Mode Mask */
#define ADC_CTRLC_FREERUN                   ADC_CTRLC_FREERUN_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLC_FREERUN_Msk instead */
#define ADC_CTRLC_CORREN_Pos                3                                              /**< (ADC_CTRLC) Digital Correction Logic Enable Position */
#define ADC_CTRLC_CORREN_Msk                (_U_(0x1) << ADC_CTRLC_CORREN_Pos)             /**< (ADC_CTRLC) Digital Correction Logic Enable Mask */
#define ADC_CTRLC_CORREN                    ADC_CTRLC_CORREN_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLC_CORREN_Msk instead */
#define ADC_CTRLC_RESSEL_Pos                4                                              /**< (ADC_CTRLC) Conversion Result Resolution Position */
#define ADC_CTRLC_RESSEL_Msk                (_U_(0x3) << ADC_CTRLC_RESSEL_Pos)             /**< (ADC_CTRLC) Conversion Result Resolution Mask */
#define ADC_CTRLC_RESSEL(value)             (ADC_CTRLC_RESSEL_Msk & ((value) << ADC_CTRLC_RESSEL_Pos))
#define   ADC_CTRLC_RESSEL_12BIT_Val        _U_(0x0)                                       /**< (ADC_CTRLC) 12-bit result  */
#define   ADC_CTRLC_RESSEL_16BIT_Val        _U_(0x1)                                       /**< (ADC_CTRLC) For averaging mode output  */
#define   ADC_CTRLC_RESSEL_10BIT_Val        _U_(0x2)                                       /**< (ADC_CTRLC) 10-bit result  */
#define   ADC_CTRLC_RESSEL_8BIT_Val         _U_(0x3)                                       /**< (ADC_CTRLC) 8-bit result  */
#define ADC_CTRLC_RESSEL_12BIT              (ADC_CTRLC_RESSEL_12BIT_Val << ADC_CTRLC_RESSEL_Pos)  /**< (ADC_CTRLC) 12-bit result Position  */
#define ADC_CTRLC_RESSEL_16BIT              (ADC_CTRLC_RESSEL_16BIT_Val << ADC_CTRLC_RESSEL_Pos)  /**< (ADC_CTRLC) For averaging mode output Position  */
#define ADC_CTRLC_RESSEL_10BIT              (ADC_CTRLC_RESSEL_10BIT_Val << ADC_CTRLC_RESSEL_Pos)  /**< (ADC_CTRLC) 10-bit result Position  */
#define ADC_CTRLC_RESSEL_8BIT               (ADC_CTRLC_RESSEL_8BIT_Val << ADC_CTRLC_RESSEL_Pos)  /**< (ADC_CTRLC) 8-bit result Position  */
#define ADC_CTRLC_R2R_Pos                   7                                              /**< (ADC_CTRLC) Rail-to-Rail mode enable Position */
#define ADC_CTRLC_R2R_Msk                   (_U_(0x1) << ADC_CTRLC_R2R_Pos)                /**< (ADC_CTRLC) Rail-to-Rail mode enable Mask */
#define ADC_CTRLC_R2R                       ADC_CTRLC_R2R_Msk                              /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_CTRLC_R2R_Msk instead */
#define ADC_CTRLC_WINMODE_Pos               8                                              /**< (ADC_CTRLC) Window Monitor Mode Position */
#define ADC_CTRLC_WINMODE_Msk               (_U_(0x7) << ADC_CTRLC_WINMODE_Pos)            /**< (ADC_CTRLC) Window Monitor Mode Mask */
#define ADC_CTRLC_WINMODE(value)            (ADC_CTRLC_WINMODE_Msk & ((value) << ADC_CTRLC_WINMODE_Pos))
#define   ADC_CTRLC_WINMODE_DISABLE_Val     _U_(0x0)                                       /**< (ADC_CTRLC) No window mode (default)  */
#define   ADC_CTRLC_WINMODE_MODE1_Val       _U_(0x1)                                       /**< (ADC_CTRLC) RESULT > WINLT  */
#define   ADC_CTRLC_WINMODE_MODE2_Val       _U_(0x2)                                       /**< (ADC_CTRLC) RESULT < WINUT  */
#define   ADC_CTRLC_WINMODE_MODE3_Val       _U_(0x3)                                       /**< (ADC_CTRLC) WINLT < RESULT < WINUT  */
#define   ADC_CTRLC_WINMODE_MODE4_Val       _U_(0x4)                                       /**< (ADC_CTRLC) !(WINLT < RESULT < WINUT)  */
#define ADC_CTRLC_WINMODE_DISABLE           (ADC_CTRLC_WINMODE_DISABLE_Val << ADC_CTRLC_WINMODE_Pos)  /**< (ADC_CTRLC) No window mode (default) Position  */
#define ADC_CTRLC_WINMODE_MODE1             (ADC_CTRLC_WINMODE_MODE1_Val << ADC_CTRLC_WINMODE_Pos)  /**< (ADC_CTRLC) RESULT > WINLT Position  */
#define ADC_CTRLC_WINMODE_MODE2             (ADC_CTRLC_WINMODE_MODE2_Val << ADC_CTRLC_WINMODE_Pos)  /**< (ADC_CTRLC) RESULT < WINUT Position  */
#define ADC_CTRLC_WINMODE_MODE3             (ADC_CTRLC_WINMODE_MODE3_Val << ADC_CTRLC_WINMODE_Pos)  /**< (ADC_CTRLC) WINLT < RESULT < WINUT Position  */
#define ADC_CTRLC_WINMODE_MODE4             (ADC_CTRLC_WINMODE_MODE4_Val << ADC_CTRLC_WINMODE_Pos)  /**< (ADC_CTRLC) !(WINLT < RESULT < WINUT) Position  */
#define ADC_CTRLC_DUALSEL_Pos               12                                             /**< (ADC_CTRLC) Dual Mode Trigger Selection Position */
#define ADC_CTRLC_DUALSEL_Msk               (_U_(0x3) << ADC_CTRLC_DUALSEL_Pos)            /**< (ADC_CTRLC) Dual Mode Trigger Selection Mask */
#define ADC_CTRLC_DUALSEL(value)            (ADC_CTRLC_DUALSEL_Msk & ((value) << ADC_CTRLC_DUALSEL_Pos))
#define   ADC_CTRLC_DUALSEL_BOTH_Val        _U_(0x0)                                       /**< (ADC_CTRLC) Start event or software trigger will start a conversion on both ADCs  */
#define   ADC_CTRLC_DUALSEL_INTERLEAVE_Val  _U_(0x1)                                       /**< (ADC_CTRLC) START event or software trigger will alternatingly start a conversion on ADC0 and ADC1  */
#define ADC_CTRLC_DUALSEL_BOTH              (ADC_CTRLC_DUALSEL_BOTH_Val << ADC_CTRLC_DUALSEL_Pos)  /**< (ADC_CTRLC) Start event or software trigger will start a conversion on both ADCs Position  */
#define ADC_CTRLC_DUALSEL_INTERLEAVE        (ADC_CTRLC_DUALSEL_INTERLEAVE_Val << ADC_CTRLC_DUALSEL_Pos)  /**< (ADC_CTRLC) START event or software trigger will alternatingly start a conversion on ADC0 and ADC1 Position  */
#define ADC_CTRLC_MASK                      _U_(0x37BF)                                    /**< \deprecated (ADC_CTRLC) Register MASK  (Use ADC_CTRLC_Msk instead)  */
#define ADC_CTRLC_Msk                       _U_(0x37BF)                                    /**< (ADC_CTRLC) Register Mask  */


/* -------- ADC_AVGCTRL : (ADC Offset: 0x0c) (R/W 8) Average Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SAMPLENUM:4;               /**< bit:   0..3  Number of Samples to be Collected        */
    uint8_t  ADJRES:3;                  /**< bit:   4..6  Adjusting Result / Division Coefficient  */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_AVGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_AVGCTRL_OFFSET                  (0x0C)                                        /**<  (ADC_AVGCTRL) Average Control  Offset */
#define ADC_AVGCTRL_RESETVALUE              _U_(0x00)                                     /**<  (ADC_AVGCTRL) Average Control  Reset Value */

#define ADC_AVGCTRL_SAMPLENUM_Pos           0                                              /**< (ADC_AVGCTRL) Number of Samples to be Collected Position */
#define ADC_AVGCTRL_SAMPLENUM_Msk           (_U_(0xF) << ADC_AVGCTRL_SAMPLENUM_Pos)        /**< (ADC_AVGCTRL) Number of Samples to be Collected Mask */
#define ADC_AVGCTRL_SAMPLENUM(value)        (ADC_AVGCTRL_SAMPLENUM_Msk & ((value) << ADC_AVGCTRL_SAMPLENUM_Pos))
#define   ADC_AVGCTRL_SAMPLENUM_1_Val       _U_(0x0)                                       /**< (ADC_AVGCTRL) 1 sample  */
#define   ADC_AVGCTRL_SAMPLENUM_2_Val       _U_(0x1)                                       /**< (ADC_AVGCTRL) 2 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_4_Val       _U_(0x2)                                       /**< (ADC_AVGCTRL) 4 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_8_Val       _U_(0x3)                                       /**< (ADC_AVGCTRL) 8 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_16_Val      _U_(0x4)                                       /**< (ADC_AVGCTRL) 16 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_32_Val      _U_(0x5)                                       /**< (ADC_AVGCTRL) 32 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_64_Val      _U_(0x6)                                       /**< (ADC_AVGCTRL) 64 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_128_Val     _U_(0x7)                                       /**< (ADC_AVGCTRL) 128 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_256_Val     _U_(0x8)                                       /**< (ADC_AVGCTRL) 256 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_512_Val     _U_(0x9)                                       /**< (ADC_AVGCTRL) 512 samples  */
#define   ADC_AVGCTRL_SAMPLENUM_1024_Val    _U_(0xA)                                       /**< (ADC_AVGCTRL) 1024 samples  */
#define ADC_AVGCTRL_SAMPLENUM_1             (ADC_AVGCTRL_SAMPLENUM_1_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 1 sample Position  */
#define ADC_AVGCTRL_SAMPLENUM_2             (ADC_AVGCTRL_SAMPLENUM_2_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 2 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_4             (ADC_AVGCTRL_SAMPLENUM_4_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 4 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_8             (ADC_AVGCTRL_SAMPLENUM_8_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 8 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_16            (ADC_AVGCTRL_SAMPLENUM_16_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 16 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_32            (ADC_AVGCTRL_SAMPLENUM_32_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 32 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_64            (ADC_AVGCTRL_SAMPLENUM_64_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 64 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_128           (ADC_AVGCTRL_SAMPLENUM_128_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 128 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_256           (ADC_AVGCTRL_SAMPLENUM_256_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 256 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_512           (ADC_AVGCTRL_SAMPLENUM_512_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 512 samples Position  */
#define ADC_AVGCTRL_SAMPLENUM_1024          (ADC_AVGCTRL_SAMPLENUM_1024_Val << ADC_AVGCTRL_SAMPLENUM_Pos)  /**< (ADC_AVGCTRL) 1024 samples Position  */
#define ADC_AVGCTRL_ADJRES_Pos              4                                              /**< (ADC_AVGCTRL) Adjusting Result / Division Coefficient Position */
#define ADC_AVGCTRL_ADJRES_Msk              (_U_(0x7) << ADC_AVGCTRL_ADJRES_Pos)           /**< (ADC_AVGCTRL) Adjusting Result / Division Coefficient Mask */
#define ADC_AVGCTRL_ADJRES(value)           (ADC_AVGCTRL_ADJRES_Msk & ((value) << ADC_AVGCTRL_ADJRES_Pos))
#define ADC_AVGCTRL_MASK                    _U_(0x7F)                                      /**< \deprecated (ADC_AVGCTRL) Register MASK  (Use ADC_AVGCTRL_Msk instead)  */
#define ADC_AVGCTRL_Msk                     _U_(0x7F)                                      /**< (ADC_AVGCTRL) Register Mask  */


/* -------- ADC_SAMPCTRL : (ADC Offset: 0x0d) (R/W 8) Sample Time Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SAMPLEN:6;                 /**< bit:   0..5  Sampling Time Length                     */
    uint8_t  :1;                        /**< bit:      6  Reserved */
    uint8_t  OFFCOMP:1;                 /**< bit:      7  Comparator Offset Compensation Enable    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_SAMPCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SAMPCTRL_OFFSET                 (0x0D)                                        /**<  (ADC_SAMPCTRL) Sample Time Control  Offset */
#define ADC_SAMPCTRL_RESETVALUE             _U_(0x00)                                     /**<  (ADC_SAMPCTRL) Sample Time Control  Reset Value */

#define ADC_SAMPCTRL_SAMPLEN_Pos            0                                              /**< (ADC_SAMPCTRL) Sampling Time Length Position */
#define ADC_SAMPCTRL_SAMPLEN_Msk            (_U_(0x3F) << ADC_SAMPCTRL_SAMPLEN_Pos)        /**< (ADC_SAMPCTRL) Sampling Time Length Mask */
#define ADC_SAMPCTRL_SAMPLEN(value)         (ADC_SAMPCTRL_SAMPLEN_Msk & ((value) << ADC_SAMPCTRL_SAMPLEN_Pos))
#define ADC_SAMPCTRL_OFFCOMP_Pos            7                                              /**< (ADC_SAMPCTRL) Comparator Offset Compensation Enable Position */
#define ADC_SAMPCTRL_OFFCOMP_Msk            (_U_(0x1) << ADC_SAMPCTRL_OFFCOMP_Pos)         /**< (ADC_SAMPCTRL) Comparator Offset Compensation Enable Mask */
#define ADC_SAMPCTRL_OFFCOMP                ADC_SAMPCTRL_OFFCOMP_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SAMPCTRL_OFFCOMP_Msk instead */
#define ADC_SAMPCTRL_MASK                   _U_(0xBF)                                      /**< \deprecated (ADC_SAMPCTRL) Register MASK  (Use ADC_SAMPCTRL_Msk instead)  */
#define ADC_SAMPCTRL_Msk                    _U_(0xBF)                                      /**< (ADC_SAMPCTRL) Register Mask  */


/* -------- ADC_WINLT : (ADC Offset: 0x0e) (R/W 16) Window Monitor Lower Threshold -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t WINLT:16;                  /**< bit:  0..15  Window Lower Threshold                   */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_WINLT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_WINLT_OFFSET                    (0x0E)                                        /**<  (ADC_WINLT) Window Monitor Lower Threshold  Offset */
#define ADC_WINLT_RESETVALUE                _U_(0x00)                                     /**<  (ADC_WINLT) Window Monitor Lower Threshold  Reset Value */

#define ADC_WINLT_WINLT_Pos                 0                                              /**< (ADC_WINLT) Window Lower Threshold Position */
#define ADC_WINLT_WINLT_Msk                 (_U_(0xFFFF) << ADC_WINLT_WINLT_Pos)           /**< (ADC_WINLT) Window Lower Threshold Mask */
#define ADC_WINLT_WINLT(value)              (ADC_WINLT_WINLT_Msk & ((value) << ADC_WINLT_WINLT_Pos))
#define ADC_WINLT_MASK                      _U_(0xFFFF)                                    /**< \deprecated (ADC_WINLT) Register MASK  (Use ADC_WINLT_Msk instead)  */
#define ADC_WINLT_Msk                       _U_(0xFFFF)                                    /**< (ADC_WINLT) Register Mask  */


/* -------- ADC_WINUT : (ADC Offset: 0x10) (R/W 16) Window Monitor Upper Threshold -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t WINUT:16;                  /**< bit:  0..15  Window Upper Threshold                   */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_WINUT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_WINUT_OFFSET                    (0x10)                                        /**<  (ADC_WINUT) Window Monitor Upper Threshold  Offset */
#define ADC_WINUT_RESETVALUE                _U_(0x00)                                     /**<  (ADC_WINUT) Window Monitor Upper Threshold  Reset Value */

#define ADC_WINUT_WINUT_Pos                 0                                              /**< (ADC_WINUT) Window Upper Threshold Position */
#define ADC_WINUT_WINUT_Msk                 (_U_(0xFFFF) << ADC_WINUT_WINUT_Pos)           /**< (ADC_WINUT) Window Upper Threshold Mask */
#define ADC_WINUT_WINUT(value)              (ADC_WINUT_WINUT_Msk & ((value) << ADC_WINUT_WINUT_Pos))
#define ADC_WINUT_MASK                      _U_(0xFFFF)                                    /**< \deprecated (ADC_WINUT) Register MASK  (Use ADC_WINUT_Msk instead)  */
#define ADC_WINUT_Msk                       _U_(0xFFFF)                                    /**< (ADC_WINUT) Register Mask  */


/* -------- ADC_GAINCORR : (ADC Offset: 0x12) (R/W 16) Gain Correction -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GAINCORR:12;               /**< bit:  0..11  Gain Correction Value                    */
    uint16_t :4;                        /**< bit: 12..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_GAINCORR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_GAINCORR_OFFSET                 (0x12)                                        /**<  (ADC_GAINCORR) Gain Correction  Offset */
#define ADC_GAINCORR_RESETVALUE             _U_(0x00)                                     /**<  (ADC_GAINCORR) Gain Correction  Reset Value */

#define ADC_GAINCORR_GAINCORR_Pos           0                                              /**< (ADC_GAINCORR) Gain Correction Value Position */
#define ADC_GAINCORR_GAINCORR_Msk           (_U_(0xFFF) << ADC_GAINCORR_GAINCORR_Pos)      /**< (ADC_GAINCORR) Gain Correction Value Mask */
#define ADC_GAINCORR_GAINCORR(value)        (ADC_GAINCORR_GAINCORR_Msk & ((value) << ADC_GAINCORR_GAINCORR_Pos))
#define ADC_GAINCORR_MASK                   _U_(0xFFF)                                     /**< \deprecated (ADC_GAINCORR) Register MASK  (Use ADC_GAINCORR_Msk instead)  */
#define ADC_GAINCORR_Msk                    _U_(0xFFF)                                     /**< (ADC_GAINCORR) Register Mask  */


/* -------- ADC_OFFSETCORR : (ADC Offset: 0x14) (R/W 16) Offset Correction -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t OFFSETCORR:12;             /**< bit:  0..11  Offset Correction Value                  */
    uint16_t :4;                        /**< bit: 12..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_OFFSETCORR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_OFFSETCORR_OFFSET               (0x14)                                        /**<  (ADC_OFFSETCORR) Offset Correction  Offset */
#define ADC_OFFSETCORR_RESETVALUE           _U_(0x00)                                     /**<  (ADC_OFFSETCORR) Offset Correction  Reset Value */

#define ADC_OFFSETCORR_OFFSETCORR_Pos       0                                              /**< (ADC_OFFSETCORR) Offset Correction Value Position */
#define ADC_OFFSETCORR_OFFSETCORR_Msk       (_U_(0xFFF) << ADC_OFFSETCORR_OFFSETCORR_Pos)  /**< (ADC_OFFSETCORR) Offset Correction Value Mask */
#define ADC_OFFSETCORR_OFFSETCORR(value)    (ADC_OFFSETCORR_OFFSETCORR_Msk & ((value) << ADC_OFFSETCORR_OFFSETCORR_Pos))
#define ADC_OFFSETCORR_MASK                 _U_(0xFFF)                                     /**< \deprecated (ADC_OFFSETCORR) Register MASK  (Use ADC_OFFSETCORR_Msk instead)  */
#define ADC_OFFSETCORR_Msk                  _U_(0xFFF)                                     /**< (ADC_OFFSETCORR) Register Mask  */


/* -------- ADC_SWTRIG : (ADC Offset: 0x18) (R/W 8) Software Trigger -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  FLUSH:1;                   /**< bit:      0  ADC Flush                                */
    uint8_t  START:1;                   /**< bit:      1  Start ADC Conversion                     */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_SWTRIG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SWTRIG_OFFSET                   (0x18)                                        /**<  (ADC_SWTRIG) Software Trigger  Offset */
#define ADC_SWTRIG_RESETVALUE               _U_(0x00)                                     /**<  (ADC_SWTRIG) Software Trigger  Reset Value */

#define ADC_SWTRIG_FLUSH_Pos                0                                              /**< (ADC_SWTRIG) ADC Flush Position */
#define ADC_SWTRIG_FLUSH_Msk                (_U_(0x1) << ADC_SWTRIG_FLUSH_Pos)             /**< (ADC_SWTRIG) ADC Flush Mask */
#define ADC_SWTRIG_FLUSH                    ADC_SWTRIG_FLUSH_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SWTRIG_FLUSH_Msk instead */
#define ADC_SWTRIG_START_Pos                1                                              /**< (ADC_SWTRIG) Start ADC Conversion Position */
#define ADC_SWTRIG_START_Msk                (_U_(0x1) << ADC_SWTRIG_START_Pos)             /**< (ADC_SWTRIG) Start ADC Conversion Mask */
#define ADC_SWTRIG_START                    ADC_SWTRIG_START_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SWTRIG_START_Msk instead */
#define ADC_SWTRIG_MASK                     _U_(0x03)                                      /**< \deprecated (ADC_SWTRIG) Register MASK  (Use ADC_SWTRIG_Msk instead)  */
#define ADC_SWTRIG_Msk                      _U_(0x03)                                      /**< (ADC_SWTRIG) Register Mask  */


/* -------- ADC_DBGCTRL : (ADC Offset: 0x1c) (R/W 8) Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGRUN:1;                  /**< bit:      0  Debug Run                                */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ADC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_DBGCTRL_OFFSET                  (0x1C)                                        /**<  (ADC_DBGCTRL) Debug Control  Offset */
#define ADC_DBGCTRL_RESETVALUE              _U_(0x00)                                     /**<  (ADC_DBGCTRL) Debug Control  Reset Value */

#define ADC_DBGCTRL_DBGRUN_Pos              0                                              /**< (ADC_DBGCTRL) Debug Run Position */
#define ADC_DBGCTRL_DBGRUN_Msk              (_U_(0x1) << ADC_DBGCTRL_DBGRUN_Pos)           /**< (ADC_DBGCTRL) Debug Run Mask */
#define ADC_DBGCTRL_DBGRUN                  ADC_DBGCTRL_DBGRUN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_DBGCTRL_DBGRUN_Msk instead */
#define ADC_DBGCTRL_MASK                    _U_(0x01)                                      /**< \deprecated (ADC_DBGCTRL) Register MASK  (Use ADC_DBGCTRL_Msk instead)  */
#define ADC_DBGCTRL_Msk                     _U_(0x01)                                      /**< (ADC_DBGCTRL) Register Mask  */


/* -------- ADC_SYNCBUSY : (ADC Offset: 0x20) (R/ 16) Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SWRST:1;                   /**< bit:      0  SWRST Synchronization Busy               */
    uint16_t ENABLE:1;                  /**< bit:      1  ENABLE Synchronization Busy              */
    uint16_t INPUTCTRL:1;               /**< bit:      2  INPUTCTRL Synchronization Busy           */
    uint16_t CTRLC:1;                   /**< bit:      3  CTRLC Synchronization Busy               */
    uint16_t AVGCTRL:1;                 /**< bit:      4  AVGCTRL Synchronization Busy             */
    uint16_t SAMPCTRL:1;                /**< bit:      5  SAMPCTRL Synchronization Busy            */
    uint16_t WINLT:1;                   /**< bit:      6  WINLT Synchronization Busy               */
    uint16_t WINUT:1;                   /**< bit:      7  WINUT Synchronization Busy               */
    uint16_t GAINCORR:1;                /**< bit:      8  GAINCORR Synchronization Busy            */
    uint16_t OFFSETCORR:1;              /**< bit:      9  OFFSETCTRL Synchronization Busy          */
    uint16_t SWTRIG:1;                  /**< bit:     10  SWTRG Synchronization Busy               */
    uint16_t :5;                        /**< bit: 11..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SYNCBUSY_OFFSET                 (0x20)                                        /**<  (ADC_SYNCBUSY) Synchronization Busy  Offset */
#define ADC_SYNCBUSY_RESETVALUE             _U_(0x00)                                     /**<  (ADC_SYNCBUSY) Synchronization Busy  Reset Value */

#define ADC_SYNCBUSY_SWRST_Pos              0                                              /**< (ADC_SYNCBUSY) SWRST Synchronization Busy Position */
#define ADC_SYNCBUSY_SWRST_Msk              (_U_(0x1) << ADC_SYNCBUSY_SWRST_Pos)           /**< (ADC_SYNCBUSY) SWRST Synchronization Busy Mask */
#define ADC_SYNCBUSY_SWRST                  ADC_SYNCBUSY_SWRST_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_SWRST_Msk instead */
#define ADC_SYNCBUSY_ENABLE_Pos             1                                              /**< (ADC_SYNCBUSY) ENABLE Synchronization Busy Position */
#define ADC_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << ADC_SYNCBUSY_ENABLE_Pos)          /**< (ADC_SYNCBUSY) ENABLE Synchronization Busy Mask */
#define ADC_SYNCBUSY_ENABLE                 ADC_SYNCBUSY_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_ENABLE_Msk instead */
#define ADC_SYNCBUSY_INPUTCTRL_Pos          2                                              /**< (ADC_SYNCBUSY) INPUTCTRL Synchronization Busy Position */
#define ADC_SYNCBUSY_INPUTCTRL_Msk          (_U_(0x1) << ADC_SYNCBUSY_INPUTCTRL_Pos)       /**< (ADC_SYNCBUSY) INPUTCTRL Synchronization Busy Mask */
#define ADC_SYNCBUSY_INPUTCTRL              ADC_SYNCBUSY_INPUTCTRL_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_INPUTCTRL_Msk instead */
#define ADC_SYNCBUSY_CTRLC_Pos              3                                              /**< (ADC_SYNCBUSY) CTRLC Synchronization Busy Position */
#define ADC_SYNCBUSY_CTRLC_Msk              (_U_(0x1) << ADC_SYNCBUSY_CTRLC_Pos)           /**< (ADC_SYNCBUSY) CTRLC Synchronization Busy Mask */
#define ADC_SYNCBUSY_CTRLC                  ADC_SYNCBUSY_CTRLC_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_CTRLC_Msk instead */
#define ADC_SYNCBUSY_AVGCTRL_Pos            4                                              /**< (ADC_SYNCBUSY) AVGCTRL Synchronization Busy Position */
#define ADC_SYNCBUSY_AVGCTRL_Msk            (_U_(0x1) << ADC_SYNCBUSY_AVGCTRL_Pos)         /**< (ADC_SYNCBUSY) AVGCTRL Synchronization Busy Mask */
#define ADC_SYNCBUSY_AVGCTRL                ADC_SYNCBUSY_AVGCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_AVGCTRL_Msk instead */
#define ADC_SYNCBUSY_SAMPCTRL_Pos           5                                              /**< (ADC_SYNCBUSY) SAMPCTRL Synchronization Busy Position */
#define ADC_SYNCBUSY_SAMPCTRL_Msk           (_U_(0x1) << ADC_SYNCBUSY_SAMPCTRL_Pos)        /**< (ADC_SYNCBUSY) SAMPCTRL Synchronization Busy Mask */
#define ADC_SYNCBUSY_SAMPCTRL               ADC_SYNCBUSY_SAMPCTRL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_SAMPCTRL_Msk instead */
#define ADC_SYNCBUSY_WINLT_Pos              6                                              /**< (ADC_SYNCBUSY) WINLT Synchronization Busy Position */
#define ADC_SYNCBUSY_WINLT_Msk              (_U_(0x1) << ADC_SYNCBUSY_WINLT_Pos)           /**< (ADC_SYNCBUSY) WINLT Synchronization Busy Mask */
#define ADC_SYNCBUSY_WINLT                  ADC_SYNCBUSY_WINLT_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_WINLT_Msk instead */
#define ADC_SYNCBUSY_WINUT_Pos              7                                              /**< (ADC_SYNCBUSY) WINUT Synchronization Busy Position */
#define ADC_SYNCBUSY_WINUT_Msk              (_U_(0x1) << ADC_SYNCBUSY_WINUT_Pos)           /**< (ADC_SYNCBUSY) WINUT Synchronization Busy Mask */
#define ADC_SYNCBUSY_WINUT                  ADC_SYNCBUSY_WINUT_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_WINUT_Msk instead */
#define ADC_SYNCBUSY_GAINCORR_Pos           8                                              /**< (ADC_SYNCBUSY) GAINCORR Synchronization Busy Position */
#define ADC_SYNCBUSY_GAINCORR_Msk           (_U_(0x1) << ADC_SYNCBUSY_GAINCORR_Pos)        /**< (ADC_SYNCBUSY) GAINCORR Synchronization Busy Mask */
#define ADC_SYNCBUSY_GAINCORR               ADC_SYNCBUSY_GAINCORR_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_GAINCORR_Msk instead */
#define ADC_SYNCBUSY_OFFSETCORR_Pos         9                                              /**< (ADC_SYNCBUSY) OFFSETCTRL Synchronization Busy Position */
#define ADC_SYNCBUSY_OFFSETCORR_Msk         (_U_(0x1) << ADC_SYNCBUSY_OFFSETCORR_Pos)      /**< (ADC_SYNCBUSY) OFFSETCTRL Synchronization Busy Mask */
#define ADC_SYNCBUSY_OFFSETCORR             ADC_SYNCBUSY_OFFSETCORR_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_OFFSETCORR_Msk instead */
#define ADC_SYNCBUSY_SWTRIG_Pos             10                                             /**< (ADC_SYNCBUSY) SWTRG Synchronization Busy Position */
#define ADC_SYNCBUSY_SWTRIG_Msk             (_U_(0x1) << ADC_SYNCBUSY_SWTRIG_Pos)          /**< (ADC_SYNCBUSY) SWTRG Synchronization Busy Mask */
#define ADC_SYNCBUSY_SWTRIG                 ADC_SYNCBUSY_SWTRIG_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ADC_SYNCBUSY_SWTRIG_Msk instead */
#define ADC_SYNCBUSY_MASK                   _U_(0x7FF)                                     /**< \deprecated (ADC_SYNCBUSY) Register MASK  (Use ADC_SYNCBUSY_Msk instead)  */
#define ADC_SYNCBUSY_Msk                    _U_(0x7FF)                                     /**< (ADC_SYNCBUSY) Register Mask  */


/* -------- ADC_RESULT : (ADC Offset: 0x24) (R/ 16) Result -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RESULT:16;                 /**< bit:  0..15  Result Value                             */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_RESULT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_RESULT_OFFSET                   (0x24)                                        /**<  (ADC_RESULT) Result  Offset */
#define ADC_RESULT_RESETVALUE               _U_(0x00)                                     /**<  (ADC_RESULT) Result  Reset Value */

#define ADC_RESULT_RESULT_Pos               0                                              /**< (ADC_RESULT) Result Value Position */
#define ADC_RESULT_RESULT_Msk               (_U_(0xFFFF) << ADC_RESULT_RESULT_Pos)         /**< (ADC_RESULT) Result Value Mask */
#define ADC_RESULT_RESULT(value)            (ADC_RESULT_RESULT_Msk & ((value) << ADC_RESULT_RESULT_Pos))
#define ADC_RESULT_MASK                     _U_(0xFFFF)                                    /**< \deprecated (ADC_RESULT) Register MASK  (Use ADC_RESULT_Msk instead)  */
#define ADC_RESULT_Msk                      _U_(0xFFFF)                                    /**< (ADC_RESULT) Register Mask  */


/* -------- ADC_SEQCTRL : (ADC Offset: 0x28) (R/W 32) Sequence Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SEQEN:32;                  /**< bit:  0..31  Enable Positive Input in the Sequence    */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ADC_SEQCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SEQCTRL_OFFSET                  (0x28)                                        /**<  (ADC_SEQCTRL) Sequence Control  Offset */
#define ADC_SEQCTRL_RESETVALUE              _U_(0x00)                                     /**<  (ADC_SEQCTRL) Sequence Control  Reset Value */

#define ADC_SEQCTRL_SEQEN_Pos               0                                              /**< (ADC_SEQCTRL) Enable Positive Input in the Sequence Position */
#define ADC_SEQCTRL_SEQEN_Msk               (_U_(0xFFFFFFFF) << ADC_SEQCTRL_SEQEN_Pos)     /**< (ADC_SEQCTRL) Enable Positive Input in the Sequence Mask */
#define ADC_SEQCTRL_SEQEN(value)            (ADC_SEQCTRL_SEQEN_Msk & ((value) << ADC_SEQCTRL_SEQEN_Pos))
#define ADC_SEQCTRL_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (ADC_SEQCTRL) Register MASK  (Use ADC_SEQCTRL_Msk instead)  */
#define ADC_SEQCTRL_Msk                     _U_(0xFFFFFFFF)                                /**< (ADC_SEQCTRL) Register Mask  */


/* -------- ADC_CALIB : (ADC Offset: 0x2c) (R/W 16) Calibration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BIASCOMP:3;                /**< bit:   0..2  Bias Comparator Scaling                  */
    uint16_t :5;                        /**< bit:   3..7  Reserved */
    uint16_t BIASREFBUF:3;              /**< bit:  8..10  Bias  Reference Buffer Scaling           */
    uint16_t :5;                        /**< bit: 11..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} ADC_CALIB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CALIB_OFFSET                    (0x2C)                                        /**<  (ADC_CALIB) Calibration  Offset */
#define ADC_CALIB_RESETVALUE                _U_(0x00)                                     /**<  (ADC_CALIB) Calibration  Reset Value */

#define ADC_CALIB_BIASCOMP_Pos              0                                              /**< (ADC_CALIB) Bias Comparator Scaling Position */
#define ADC_CALIB_BIASCOMP_Msk              (_U_(0x7) << ADC_CALIB_BIASCOMP_Pos)           /**< (ADC_CALIB) Bias Comparator Scaling Mask */
#define ADC_CALIB_BIASCOMP(value)           (ADC_CALIB_BIASCOMP_Msk & ((value) << ADC_CALIB_BIASCOMP_Pos))
#define ADC_CALIB_BIASREFBUF_Pos            8                                              /**< (ADC_CALIB) Bias  Reference Buffer Scaling Position */
#define ADC_CALIB_BIASREFBUF_Msk            (_U_(0x7) << ADC_CALIB_BIASREFBUF_Pos)         /**< (ADC_CALIB) Bias  Reference Buffer Scaling Mask */
#define ADC_CALIB_BIASREFBUF(value)         (ADC_CALIB_BIASREFBUF_Msk & ((value) << ADC_CALIB_BIASREFBUF_Pos))
#define ADC_CALIB_MASK                      _U_(0x707)                                     /**< \deprecated (ADC_CALIB) Register MASK  (Use ADC_CALIB_Msk instead)  */
#define ADC_CALIB_Msk                       _U_(0x707)                                     /**< (ADC_CALIB) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief ADC hardware registers */
typedef struct {  /* Analog Digital Converter */
  __IO ADC_CTRLA_Type                 CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __IO ADC_CTRLB_Type                 CTRLB;          /**< Offset: 0x01 (R/W   8) Control B */
  __IO ADC_REFCTRL_Type               REFCTRL;        /**< Offset: 0x02 (R/W   8) Reference Control */
  __IO ADC_EVCTRL_Type                EVCTRL;         /**< Offset: 0x03 (R/W   8) Event Control */
  __IO ADC_INTENCLR_Type              INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO ADC_INTENSET_Type              INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO ADC_INTFLAG_Type               INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  ADC_SEQSTATUS_Type             SEQSTATUS;      /**< Offset: 0x07 (R/    8) Sequence Status */
  __IO ADC_INPUTCTRL_Type             INPUTCTRL;      /**< Offset: 0x08 (R/W  16) Input Control */
  __IO ADC_CTRLC_Type                 CTRLC;          /**< Offset: 0x0A (R/W  16) Control C */
  __IO ADC_AVGCTRL_Type               AVGCTRL;        /**< Offset: 0x0C (R/W   8) Average Control */
  __IO ADC_SAMPCTRL_Type              SAMPCTRL;       /**< Offset: 0x0D (R/W   8) Sample Time Control */
  __IO ADC_WINLT_Type                 WINLT;          /**< Offset: 0x0E (R/W  16) Window Monitor Lower Threshold */
  __IO ADC_WINUT_Type                 WINUT;          /**< Offset: 0x10 (R/W  16) Window Monitor Upper Threshold */
  __IO ADC_GAINCORR_Type              GAINCORR;       /**< Offset: 0x12 (R/W  16) Gain Correction */
  __IO ADC_OFFSETCORR_Type            OFFSETCORR;     /**< Offset: 0x14 (R/W  16) Offset Correction */
  __I  uint8_t                        Reserved1[2];
  __IO ADC_SWTRIG_Type                SWTRIG;         /**< Offset: 0x18 (R/W   8) Software Trigger */
  __I  uint8_t                        Reserved2[3];
  __IO ADC_DBGCTRL_Type               DBGCTRL;        /**< Offset: 0x1C (R/W   8) Debug Control */
  __I  uint8_t                        Reserved3[3];
  __I  ADC_SYNCBUSY_Type              SYNCBUSY;       /**< Offset: 0x20 (R/   16) Synchronization Busy */
  __I  uint8_t                        Reserved4[2];
  __I  ADC_RESULT_Type                RESULT;         /**< Offset: 0x24 (R/   16) Result */
  __I  uint8_t                        Reserved5[2];
  __IO ADC_SEQCTRL_Type               SEQCTRL;        /**< Offset: 0x28 (R/W  32) Sequence Control */
  __IO ADC_CALIB_Type                 CALIB;          /**< Offset: 0x2C (R/W  16) Calibration */
} Adc;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Analog Digital Converter */

#endif /* _SAML10_ADC_COMPONENT_H_ */
