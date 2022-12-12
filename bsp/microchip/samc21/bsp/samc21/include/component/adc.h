/**
 * \file
 *
 * \brief Component description for ADC
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_ADC_COMPONENT_
#define _SAMC21_ADC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR ADC */
/* ========================================================================== */
/** \addtogroup SAMC21_ADC Analog Digital Converter */
/*@{*/

#define ADC_U2247
#define REV_ADC                     0x220

/* -------- ADC_CTRLA : (ADC Offset: 0x00) (R/W  8) Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :3;               /*!< bit:  2.. 4  Reserved                           */
    uint8_t  SLAVEEN:1;        /*!< bit:      5  Slave Enable                       */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run During Standby                 */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLA_OFFSET            0x00         /**< \brief (ADC_CTRLA offset) Control A */
#define ADC_CTRLA_RESETVALUE        _U_(0x00)    /**< \brief (ADC_CTRLA reset_value) Control A */

#define ADC_CTRLA_SWRST_Pos         0            /**< \brief (ADC_CTRLA) Software Reset */
#define ADC_CTRLA_SWRST             (_U_(0x1) << ADC_CTRLA_SWRST_Pos)
#define ADC_CTRLA_ENABLE_Pos        1            /**< \brief (ADC_CTRLA) Enable */
#define ADC_CTRLA_ENABLE            (_U_(0x1) << ADC_CTRLA_ENABLE_Pos)
#define ADC_CTRLA_SLAVEEN_Pos       5            /**< \brief (ADC_CTRLA) Slave Enable */
#define ADC_CTRLA_SLAVEEN           (_U_(0x1) << ADC_CTRLA_SLAVEEN_Pos)
#define ADC_CTRLA_RUNSTDBY_Pos      6            /**< \brief (ADC_CTRLA) Run During Standby */
#define ADC_CTRLA_RUNSTDBY          (_U_(0x1) << ADC_CTRLA_RUNSTDBY_Pos)
#define ADC_CTRLA_ONDEMAND_Pos      7            /**< \brief (ADC_CTRLA) On Demand Control */
#define ADC_CTRLA_ONDEMAND          (_U_(0x1) << ADC_CTRLA_ONDEMAND_Pos)
#define ADC_CTRLA_MASK              _U_(0xE3)    /**< \brief (ADC_CTRLA) MASK Register */

/* -------- ADC_CTRLB : (ADC Offset: 0x01) (R/W  8) Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  PRESCALER:3;      /*!< bit:  0.. 2  Prescaler Configuration            */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLB_OFFSET            0x01         /**< \brief (ADC_CTRLB offset) Control B */
#define ADC_CTRLB_RESETVALUE        _U_(0x00)    /**< \brief (ADC_CTRLB reset_value) Control B */

#define ADC_CTRLB_PRESCALER_Pos     0            /**< \brief (ADC_CTRLB) Prescaler Configuration */
#define ADC_CTRLB_PRESCALER_Msk     (_U_(0x7) << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER(value)  (ADC_CTRLB_PRESCALER_Msk & ((value) << ADC_CTRLB_PRESCALER_Pos))
#define   ADC_CTRLB_PRESCALER_DIV2_Val    _U_(0x0)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 2 */
#define   ADC_CTRLB_PRESCALER_DIV4_Val    _U_(0x1)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 4 */
#define   ADC_CTRLB_PRESCALER_DIV8_Val    _U_(0x2)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 8 */
#define   ADC_CTRLB_PRESCALER_DIV16_Val   _U_(0x3)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 16 */
#define   ADC_CTRLB_PRESCALER_DIV32_Val   _U_(0x4)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 32 */
#define   ADC_CTRLB_PRESCALER_DIV64_Val   _U_(0x5)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 64 */
#define   ADC_CTRLB_PRESCALER_DIV128_Val  _U_(0x6)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 128 */
#define   ADC_CTRLB_PRESCALER_DIV256_Val  _U_(0x7)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 256 */
#define ADC_CTRLB_PRESCALER_DIV2    (ADC_CTRLB_PRESCALER_DIV2_Val  << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV4    (ADC_CTRLB_PRESCALER_DIV4_Val  << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV8    (ADC_CTRLB_PRESCALER_DIV8_Val  << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV16   (ADC_CTRLB_PRESCALER_DIV16_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV32   (ADC_CTRLB_PRESCALER_DIV32_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV64   (ADC_CTRLB_PRESCALER_DIV64_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV128  (ADC_CTRLB_PRESCALER_DIV128_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV256  (ADC_CTRLB_PRESCALER_DIV256_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_MASK              _U_(0x07)    /**< \brief (ADC_CTRLB) MASK Register */

/* -------- ADC_REFCTRL : (ADC Offset: 0x02) (R/W  8) Reference Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  REFSEL:4;         /*!< bit:  0.. 3  Reference Selection                */
    uint8_t  :3;               /*!< bit:  4.. 6  Reserved                           */
    uint8_t  REFCOMP:1;        /*!< bit:      7  Reference Buffer Offset Compensation Enable */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_REFCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_REFCTRL_OFFSET          0x02         /**< \brief (ADC_REFCTRL offset) Reference Control */
#define ADC_REFCTRL_RESETVALUE      _U_(0x00)    /**< \brief (ADC_REFCTRL reset_value) Reference Control */

#define ADC_REFCTRL_REFSEL_Pos      0            /**< \brief (ADC_REFCTRL) Reference Selection */
#define ADC_REFCTRL_REFSEL_Msk      (_U_(0xF) << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL(value)   (ADC_REFCTRL_REFSEL_Msk & ((value) << ADC_REFCTRL_REFSEL_Pos))
#define   ADC_REFCTRL_REFSEL_INTREF_Val   _U_(0x0)   /**< \brief (ADC_REFCTRL) Internal Bandgap Reference */
#define   ADC_REFCTRL_REFSEL_INTVCC0_Val  _U_(0x1)   /**< \brief (ADC_REFCTRL) 1/1.6 VDDANA */
#define   ADC_REFCTRL_REFSEL_INTVCC1_Val  _U_(0x2)   /**< \brief (ADC_REFCTRL) 1/2 VDDANA */
#define   ADC_REFCTRL_REFSEL_AREFA_Val    _U_(0x3)   /**< \brief (ADC_REFCTRL) External Reference */
#define   ADC_REFCTRL_REFSEL_DAC_Val      _U_(0x4)   /**< \brief (ADC_REFCTRL) DAC */
#define   ADC_REFCTRL_REFSEL_INTVCC2_Val  _U_(0x5)   /**< \brief (ADC_REFCTRL) VDDANA */
#define ADC_REFCTRL_REFSEL_INTREF   (ADC_REFCTRL_REFSEL_INTREF_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC0  (ADC_REFCTRL_REFSEL_INTVCC0_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC1  (ADC_REFCTRL_REFSEL_INTVCC1_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_AREFA    (ADC_REFCTRL_REFSEL_AREFA_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_DAC      (ADC_REFCTRL_REFSEL_DAC_Val    << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC2  (ADC_REFCTRL_REFSEL_INTVCC2_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFCOMP_Pos     7            /**< \brief (ADC_REFCTRL) Reference Buffer Offset Compensation Enable */
#define ADC_REFCTRL_REFCOMP         (_U_(0x1) << ADC_REFCTRL_REFCOMP_Pos)
#define ADC_REFCTRL_MASK            _U_(0x8F)    /**< \brief (ADC_REFCTRL) MASK Register */

/* -------- ADC_EVCTRL : (ADC Offset: 0x03) (R/W  8) Event Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  FLUSHEI:1;        /*!< bit:      0  Flush Event Input Enable           */
    uint8_t  STARTEI:1;        /*!< bit:      1  Start Conversion Event Input Enable */
    uint8_t  FLUSHINV:1;       /*!< bit:      2  Flush Event Invert Enable          */
    uint8_t  STARTINV:1;       /*!< bit:      3  Satrt Event Invert Enable          */
    uint8_t  RESRDYEO:1;       /*!< bit:      4  Result Ready Event Out             */
    uint8_t  WINMONEO:1;       /*!< bit:      5  Window Monitor Event Out           */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_EVCTRL_OFFSET           0x03         /**< \brief (ADC_EVCTRL offset) Event Control */
#define ADC_EVCTRL_RESETVALUE       _U_(0x00)    /**< \brief (ADC_EVCTRL reset_value) Event Control */

#define ADC_EVCTRL_FLUSHEI_Pos      0            /**< \brief (ADC_EVCTRL) Flush Event Input Enable */
#define ADC_EVCTRL_FLUSHEI          (_U_(0x1) << ADC_EVCTRL_FLUSHEI_Pos)
#define ADC_EVCTRL_STARTEI_Pos      1            /**< \brief (ADC_EVCTRL) Start Conversion Event Input Enable */
#define ADC_EVCTRL_STARTEI          (_U_(0x1) << ADC_EVCTRL_STARTEI_Pos)
#define ADC_EVCTRL_FLUSHINV_Pos     2            /**< \brief (ADC_EVCTRL) Flush Event Invert Enable */
#define ADC_EVCTRL_FLUSHINV         (_U_(0x1) << ADC_EVCTRL_FLUSHINV_Pos)
#define ADC_EVCTRL_STARTINV_Pos     3            /**< \brief (ADC_EVCTRL) Satrt Event Invert Enable */
#define ADC_EVCTRL_STARTINV         (_U_(0x1) << ADC_EVCTRL_STARTINV_Pos)
#define ADC_EVCTRL_RESRDYEO_Pos     4            /**< \brief (ADC_EVCTRL) Result Ready Event Out */
#define ADC_EVCTRL_RESRDYEO         (_U_(0x1) << ADC_EVCTRL_RESRDYEO_Pos)
#define ADC_EVCTRL_WINMONEO_Pos     5            /**< \brief (ADC_EVCTRL) Window Monitor Event Out */
#define ADC_EVCTRL_WINMONEO         (_U_(0x1) << ADC_EVCTRL_WINMONEO_Pos)
#define ADC_EVCTRL_MASK             _U_(0x3F)    /**< \brief (ADC_EVCTRL) MASK Register */

/* -------- ADC_INTENCLR : (ADC Offset: 0x04) (R/W  8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Disable     */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Disable          */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Disable   */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTENCLR_OFFSET         0x04         /**< \brief (ADC_INTENCLR offset) Interrupt Enable Clear */
#define ADC_INTENCLR_RESETVALUE     _U_(0x00)    /**< \brief (ADC_INTENCLR reset_value) Interrupt Enable Clear */

#define ADC_INTENCLR_RESRDY_Pos     0            /**< \brief (ADC_INTENCLR) Result Ready Interrupt Disable */
#define ADC_INTENCLR_RESRDY         (_U_(0x1) << ADC_INTENCLR_RESRDY_Pos)
#define ADC_INTENCLR_OVERRUN_Pos    1            /**< \brief (ADC_INTENCLR) Overrun Interrupt Disable */
#define ADC_INTENCLR_OVERRUN        (_U_(0x1) << ADC_INTENCLR_OVERRUN_Pos)
#define ADC_INTENCLR_WINMON_Pos     2            /**< \brief (ADC_INTENCLR) Window Monitor Interrupt Disable */
#define ADC_INTENCLR_WINMON         (_U_(0x1) << ADC_INTENCLR_WINMON_Pos)
#define ADC_INTENCLR_MASK           _U_(0x07)    /**< \brief (ADC_INTENCLR) MASK Register */

/* -------- ADC_INTENSET : (ADC Offset: 0x05) (R/W  8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Enable      */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Enable           */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Enable    */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTENSET_OFFSET         0x05         /**< \brief (ADC_INTENSET offset) Interrupt Enable Set */
#define ADC_INTENSET_RESETVALUE     _U_(0x00)    /**< \brief (ADC_INTENSET reset_value) Interrupt Enable Set */

#define ADC_INTENSET_RESRDY_Pos     0            /**< \brief (ADC_INTENSET) Result Ready Interrupt Enable */
#define ADC_INTENSET_RESRDY         (_U_(0x1) << ADC_INTENSET_RESRDY_Pos)
#define ADC_INTENSET_OVERRUN_Pos    1            /**< \brief (ADC_INTENSET) Overrun Interrupt Enable */
#define ADC_INTENSET_OVERRUN        (_U_(0x1) << ADC_INTENSET_OVERRUN_Pos)
#define ADC_INTENSET_WINMON_Pos     2            /**< \brief (ADC_INTENSET) Window Monitor Interrupt Enable */
#define ADC_INTENSET_WINMON         (_U_(0x1) << ADC_INTENSET_WINMON_Pos)
#define ADC_INTENSET_MASK           _U_(0x07)    /**< \brief (ADC_INTENSET) MASK Register */

/* -------- ADC_INTFLAG : (ADC Offset: 0x06) (R/W  8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Flag        */
    __I uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Flag             */
    __I uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Flag      */
    __I uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INTFLAG_OFFSET          0x06         /**< \brief (ADC_INTFLAG offset) Interrupt Flag Status and Clear */
#define ADC_INTFLAG_RESETVALUE      _U_(0x00)    /**< \brief (ADC_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define ADC_INTFLAG_RESRDY_Pos      0            /**< \brief (ADC_INTFLAG) Result Ready Interrupt Flag */
#define ADC_INTFLAG_RESRDY          (_U_(0x1) << ADC_INTFLAG_RESRDY_Pos)
#define ADC_INTFLAG_OVERRUN_Pos     1            /**< \brief (ADC_INTFLAG) Overrun Interrupt Flag */
#define ADC_INTFLAG_OVERRUN         (_U_(0x1) << ADC_INTFLAG_OVERRUN_Pos)
#define ADC_INTFLAG_WINMON_Pos      2            /**< \brief (ADC_INTFLAG) Window Monitor Interrupt Flag */
#define ADC_INTFLAG_WINMON          (_U_(0x1) << ADC_INTFLAG_WINMON_Pos)
#define ADC_INTFLAG_MASK            _U_(0x07)    /**< \brief (ADC_INTFLAG) MASK Register */

/* -------- ADC_SEQSTATUS : (ADC Offset: 0x07) (R/   8) Sequence Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SEQSTATE:5;       /*!< bit:  0.. 4  Sequence State                     */
    uint8_t  :2;               /*!< bit:  5.. 6  Reserved                           */
    uint8_t  SEQBUSY:1;        /*!< bit:      7  Sequence Busy                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_SEQSTATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SEQSTATUS_OFFSET        0x07         /**< \brief (ADC_SEQSTATUS offset) Sequence Status */
#define ADC_SEQSTATUS_RESETVALUE    _U_(0x00)    /**< \brief (ADC_SEQSTATUS reset_value) Sequence Status */

#define ADC_SEQSTATUS_SEQSTATE_Pos  0            /**< \brief (ADC_SEQSTATUS) Sequence State */
#define ADC_SEQSTATUS_SEQSTATE_Msk  (_U_(0x1F) << ADC_SEQSTATUS_SEQSTATE_Pos)
#define ADC_SEQSTATUS_SEQSTATE(value) (ADC_SEQSTATUS_SEQSTATE_Msk & ((value) << ADC_SEQSTATUS_SEQSTATE_Pos))
#define ADC_SEQSTATUS_SEQBUSY_Pos   7            /**< \brief (ADC_SEQSTATUS) Sequence Busy */
#define ADC_SEQSTATUS_SEQBUSY       (_U_(0x1) << ADC_SEQSTATUS_SEQBUSY_Pos)
#define ADC_SEQSTATUS_MASK          _U_(0x9F)    /**< \brief (ADC_SEQSTATUS) MASK Register */

/* -------- ADC_INPUTCTRL : (ADC Offset: 0x08) (R/W 16) Input Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t MUXPOS:5;         /*!< bit:  0.. 4  Positive Mux Input Selection       */
    uint16_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint16_t MUXNEG:5;         /*!< bit:  8..12  Negative Mux Input Selection       */
    uint16_t :3;               /*!< bit: 13..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_INPUTCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_INPUTCTRL_OFFSET        0x08         /**< \brief (ADC_INPUTCTRL offset) Input Control */
#define ADC_INPUTCTRL_RESETVALUE    _U_(0x0000)  /**< \brief (ADC_INPUTCTRL reset_value) Input Control */

#define ADC_INPUTCTRL_MUXPOS_Pos    0            /**< \brief (ADC_INPUTCTRL) Positive Mux Input Selection */
#define ADC_INPUTCTRL_MUXPOS_Msk    (_U_(0x1F) << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS(value) (ADC_INPUTCTRL_MUXPOS_Msk & ((value) << ADC_INPUTCTRL_MUXPOS_Pos))
#define   ADC_INPUTCTRL_MUXPOS_AIN0_Val   _U_(0x0)   /**< \brief (ADC_INPUTCTRL) ADC AIN0 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN1_Val   _U_(0x1)   /**< \brief (ADC_INPUTCTRL) ADC AIN1 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN2_Val   _U_(0x2)   /**< \brief (ADC_INPUTCTRL) ADC AIN2 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN3_Val   _U_(0x3)   /**< \brief (ADC_INPUTCTRL) ADC AIN3 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN4_Val   _U_(0x4)   /**< \brief (ADC_INPUTCTRL) ADC AIN4 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN5_Val   _U_(0x5)   /**< \brief (ADC_INPUTCTRL) ADC AIN5 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN6_Val   _U_(0x6)   /**< \brief (ADC_INPUTCTRL) ADC AIN6 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN7_Val   _U_(0x7)   /**< \brief (ADC_INPUTCTRL) ADC AIN7 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN8_Val   _U_(0x8)   /**< \brief (ADC_INPUTCTRL) ADC AIN8 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN9_Val   _U_(0x9)   /**< \brief (ADC_INPUTCTRL) ADC AIN9 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN10_Val  _U_(0xA)   /**< \brief (ADC_INPUTCTRL) ADC AIN10 Pin */
#define   ADC_INPUTCTRL_MUXPOS_AIN11_Val  _U_(0xB)   /**< \brief (ADC_INPUTCTRL) ADC AIN11 Pin */
#define   ADC_INPUTCTRL_MUXPOS_BANDGAP_Val _U_(0x19)   /**< \brief (ADC_INPUTCTRL) Bandgap Voltage */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val _U_(0x1A)   /**< \brief (ADC_INPUTCTRL) 1/4 Scaled Core Supply */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val _U_(0x1B)   /**< \brief (ADC_INPUTCTRL) 1/4 Scaled I/O Supply */
#define   ADC_INPUTCTRL_MUXPOS_DAC_Val    _U_(0x1C)   /**< \brief (ADC_INPUTCTRL) DAC Output */
#define ADC_INPUTCTRL_MUXPOS_AIN0   (ADC_INPUTCTRL_MUXPOS_AIN0_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN1   (ADC_INPUTCTRL_MUXPOS_AIN1_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN2   (ADC_INPUTCTRL_MUXPOS_AIN2_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN3   (ADC_INPUTCTRL_MUXPOS_AIN3_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN4   (ADC_INPUTCTRL_MUXPOS_AIN4_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN5   (ADC_INPUTCTRL_MUXPOS_AIN5_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN6   (ADC_INPUTCTRL_MUXPOS_AIN6_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN7   (ADC_INPUTCTRL_MUXPOS_AIN7_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN8   (ADC_INPUTCTRL_MUXPOS_AIN8_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN9   (ADC_INPUTCTRL_MUXPOS_AIN9_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN10  (ADC_INPUTCTRL_MUXPOS_AIN10_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_AIN11  (ADC_INPUTCTRL_MUXPOS_AIN11_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_BANDGAP (ADC_INPUTCTRL_MUXPOS_BANDGAP_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC (ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC (ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_DAC    (ADC_INPUTCTRL_MUXPOS_DAC_Val  << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXNEG_Pos    8            /**< \brief (ADC_INPUTCTRL) Negative Mux Input Selection */
#define ADC_INPUTCTRL_MUXNEG_Msk    (_U_(0x1F) << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG(value) (ADC_INPUTCTRL_MUXNEG_Msk & ((value) << ADC_INPUTCTRL_MUXNEG_Pos))
#define   ADC_INPUTCTRL_MUXNEG_AIN0_Val   _U_(0x0)   /**< \brief (ADC_INPUTCTRL) ADC AIN0 Pin */
#define   ADC_INPUTCTRL_MUXNEG_AIN1_Val   _U_(0x1)   /**< \brief (ADC_INPUTCTRL) ADC AIN1 Pin */
#define   ADC_INPUTCTRL_MUXNEG_AIN2_Val   _U_(0x2)   /**< \brief (ADC_INPUTCTRL) ADC AIN2 Pin */
#define   ADC_INPUTCTRL_MUXNEG_AIN3_Val   _U_(0x3)   /**< \brief (ADC_INPUTCTRL) ADC AIN3 Pin */
#define   ADC_INPUTCTRL_MUXNEG_AIN4_Val   _U_(0x4)   /**< \brief (ADC_INPUTCTRL) ADC AIN4 Pin */
#define   ADC_INPUTCTRL_MUXNEG_AIN5_Val   _U_(0x5)   /**< \brief (ADC_INPUTCTRL) ADC AIN5 Pin */
#define ADC_INPUTCTRL_MUXNEG_AIN0   (ADC_INPUTCTRL_MUXNEG_AIN0_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN1   (ADC_INPUTCTRL_MUXNEG_AIN1_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN2   (ADC_INPUTCTRL_MUXNEG_AIN2_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN3   (ADC_INPUTCTRL_MUXNEG_AIN3_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN4   (ADC_INPUTCTRL_MUXNEG_AIN4_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_AIN5   (ADC_INPUTCTRL_MUXNEG_AIN5_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MASK          _U_(0x1F1F)  /**< \brief (ADC_INPUTCTRL) MASK Register */

/* -------- ADC_CTRLC : (ADC Offset: 0x0A) (R/W 16) Control C -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t DIFFMODE:1;       /*!< bit:      0  Differential Mode                  */
    uint16_t LEFTADJ:1;        /*!< bit:      1  Left-Adjusted Result               */
    uint16_t FREERUN:1;        /*!< bit:      2  Free Running Mode                  */
    uint16_t CORREN:1;         /*!< bit:      3  Digital Correction Logic Enable    */
    uint16_t RESSEL:2;         /*!< bit:  4.. 5  Conversion Result Resolution       */
    uint16_t :1;               /*!< bit:      6  Reserved                           */
    uint16_t R2R:1;            /*!< bit:      7  Rail-to-Rail mode enable           */
    uint16_t WINMODE:3;        /*!< bit:  8..10  Window Monitor Mode                */
    uint16_t :1;               /*!< bit:     11  Reserved                           */
    uint16_t DUALSEL:2;        /*!< bit: 12..13  Dual Mode Trigger Selection        */
    uint16_t :2;               /*!< bit: 14..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_CTRLC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CTRLC_OFFSET            0x0A         /**< \brief (ADC_CTRLC offset) Control C */
#define ADC_CTRLC_RESETVALUE        _U_(0x0000)  /**< \brief (ADC_CTRLC reset_value) Control C */

#define ADC_CTRLC_DIFFMODE_Pos      0            /**< \brief (ADC_CTRLC) Differential Mode */
#define ADC_CTRLC_DIFFMODE          (_U_(0x1) << ADC_CTRLC_DIFFMODE_Pos)
#define ADC_CTRLC_LEFTADJ_Pos       1            /**< \brief (ADC_CTRLC) Left-Adjusted Result */
#define ADC_CTRLC_LEFTADJ           (_U_(0x1) << ADC_CTRLC_LEFTADJ_Pos)
#define ADC_CTRLC_FREERUN_Pos       2            /**< \brief (ADC_CTRLC) Free Running Mode */
#define ADC_CTRLC_FREERUN           (_U_(0x1) << ADC_CTRLC_FREERUN_Pos)
#define ADC_CTRLC_CORREN_Pos        3            /**< \brief (ADC_CTRLC) Digital Correction Logic Enable */
#define ADC_CTRLC_CORREN            (_U_(0x1) << ADC_CTRLC_CORREN_Pos)
#define ADC_CTRLC_RESSEL_Pos        4            /**< \brief (ADC_CTRLC) Conversion Result Resolution */
#define ADC_CTRLC_RESSEL_Msk        (_U_(0x3) << ADC_CTRLC_RESSEL_Pos)
#define ADC_CTRLC_RESSEL(value)     (ADC_CTRLC_RESSEL_Msk & ((value) << ADC_CTRLC_RESSEL_Pos))
#define   ADC_CTRLC_RESSEL_12BIT_Val      _U_(0x0)   /**< \brief (ADC_CTRLC) 12-bit result */
#define   ADC_CTRLC_RESSEL_16BIT_Val      _U_(0x1)   /**< \brief (ADC_CTRLC) For averaging mode output */
#define   ADC_CTRLC_RESSEL_10BIT_Val      _U_(0x2)   /**< \brief (ADC_CTRLC) 10-bit result */
#define   ADC_CTRLC_RESSEL_8BIT_Val       _U_(0x3)   /**< \brief (ADC_CTRLC) 8-bit result */
#define ADC_CTRLC_RESSEL_12BIT      (ADC_CTRLC_RESSEL_12BIT_Val    << ADC_CTRLC_RESSEL_Pos)
#define ADC_CTRLC_RESSEL_16BIT      (ADC_CTRLC_RESSEL_16BIT_Val    << ADC_CTRLC_RESSEL_Pos)
#define ADC_CTRLC_RESSEL_10BIT      (ADC_CTRLC_RESSEL_10BIT_Val    << ADC_CTRLC_RESSEL_Pos)
#define ADC_CTRLC_RESSEL_8BIT       (ADC_CTRLC_RESSEL_8BIT_Val     << ADC_CTRLC_RESSEL_Pos)
#define ADC_CTRLC_R2R_Pos           7            /**< \brief (ADC_CTRLC) Rail-to-Rail mode enable */
#define ADC_CTRLC_R2R               (_U_(0x1) << ADC_CTRLC_R2R_Pos)
#define ADC_CTRLC_WINMODE_Pos       8            /**< \brief (ADC_CTRLC) Window Monitor Mode */
#define ADC_CTRLC_WINMODE_Msk       (_U_(0x7) << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_WINMODE(value)    (ADC_CTRLC_WINMODE_Msk & ((value) << ADC_CTRLC_WINMODE_Pos))
#define   ADC_CTRLC_WINMODE_DISABLE_Val   _U_(0x0)   /**< \brief (ADC_CTRLC) No window mode (default) */
#define   ADC_CTRLC_WINMODE_MODE1_Val     _U_(0x1)   /**< \brief (ADC_CTRLC) RESULT > WINLT */
#define   ADC_CTRLC_WINMODE_MODE2_Val     _U_(0x2)   /**< \brief (ADC_CTRLC) RESULT < WINUT */
#define   ADC_CTRLC_WINMODE_MODE3_Val     _U_(0x3)   /**< \brief (ADC_CTRLC) WINLT < RESULT < WINUT */
#define   ADC_CTRLC_WINMODE_MODE4_Val     _U_(0x4)   /**< \brief (ADC_CTRLC) !(WINLT < RESULT < WINUT) */
#define ADC_CTRLC_WINMODE_DISABLE   (ADC_CTRLC_WINMODE_DISABLE_Val << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_WINMODE_MODE1     (ADC_CTRLC_WINMODE_MODE1_Val   << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_WINMODE_MODE2     (ADC_CTRLC_WINMODE_MODE2_Val   << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_WINMODE_MODE3     (ADC_CTRLC_WINMODE_MODE3_Val   << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_WINMODE_MODE4     (ADC_CTRLC_WINMODE_MODE4_Val   << ADC_CTRLC_WINMODE_Pos)
#define ADC_CTRLC_DUALSEL_Pos       12           /**< \brief (ADC_CTRLC) Dual Mode Trigger Selection */
#define ADC_CTRLC_DUALSEL_Msk       (_U_(0x3) << ADC_CTRLC_DUALSEL_Pos)
#define ADC_CTRLC_DUALSEL(value)    (ADC_CTRLC_DUALSEL_Msk & ((value) << ADC_CTRLC_DUALSEL_Pos))
#define   ADC_CTRLC_DUALSEL_BOTH_Val      _U_(0x0)   /**< \brief (ADC_CTRLC) Start event or software trigger will start a conversion on both ADCs */
#define   ADC_CTRLC_DUALSEL_INTERLEAVE_Val _U_(0x1)   /**< \brief (ADC_CTRLC) START event or software trigger will alternatingly start a conversion on ADC0 and ADC1 */
#define ADC_CTRLC_DUALSEL_BOTH      (ADC_CTRLC_DUALSEL_BOTH_Val    << ADC_CTRLC_DUALSEL_Pos)
#define ADC_CTRLC_DUALSEL_INTERLEAVE (ADC_CTRLC_DUALSEL_INTERLEAVE_Val << ADC_CTRLC_DUALSEL_Pos)
#define ADC_CTRLC_MASK              _U_(0x37BF)  /**< \brief (ADC_CTRLC) MASK Register */

/* -------- ADC_AVGCTRL : (ADC Offset: 0x0C) (R/W  8) Average Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SAMPLENUM:4;      /*!< bit:  0.. 3  Number of Samples to be Collected  */
    uint8_t  ADJRES:3;         /*!< bit:  4.. 6  Adjusting Result / Division Coefficient */
    uint8_t  :1;               /*!< bit:      7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_AVGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_AVGCTRL_OFFSET          0x0C         /**< \brief (ADC_AVGCTRL offset) Average Control */
#define ADC_AVGCTRL_RESETVALUE      _U_(0x00)    /**< \brief (ADC_AVGCTRL reset_value) Average Control */

#define ADC_AVGCTRL_SAMPLENUM_Pos   0            /**< \brief (ADC_AVGCTRL) Number of Samples to be Collected */
#define ADC_AVGCTRL_SAMPLENUM_Msk   (_U_(0xF) << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM(value) (ADC_AVGCTRL_SAMPLENUM_Msk & ((value) << ADC_AVGCTRL_SAMPLENUM_Pos))
#define   ADC_AVGCTRL_SAMPLENUM_1_Val     _U_(0x0)   /**< \brief (ADC_AVGCTRL) 1 sample */
#define   ADC_AVGCTRL_SAMPLENUM_2_Val     _U_(0x1)   /**< \brief (ADC_AVGCTRL) 2 samples */
#define   ADC_AVGCTRL_SAMPLENUM_4_Val     _U_(0x2)   /**< \brief (ADC_AVGCTRL) 4 samples */
#define   ADC_AVGCTRL_SAMPLENUM_8_Val     _U_(0x3)   /**< \brief (ADC_AVGCTRL) 8 samples */
#define   ADC_AVGCTRL_SAMPLENUM_16_Val    _U_(0x4)   /**< \brief (ADC_AVGCTRL) 16 samples */
#define   ADC_AVGCTRL_SAMPLENUM_32_Val    _U_(0x5)   /**< \brief (ADC_AVGCTRL) 32 samples */
#define   ADC_AVGCTRL_SAMPLENUM_64_Val    _U_(0x6)   /**< \brief (ADC_AVGCTRL) 64 samples */
#define   ADC_AVGCTRL_SAMPLENUM_128_Val   _U_(0x7)   /**< \brief (ADC_AVGCTRL) 128 samples */
#define   ADC_AVGCTRL_SAMPLENUM_256_Val   _U_(0x8)   /**< \brief (ADC_AVGCTRL) 256 samples */
#define   ADC_AVGCTRL_SAMPLENUM_512_Val   _U_(0x9)   /**< \brief (ADC_AVGCTRL) 512 samples */
#define   ADC_AVGCTRL_SAMPLENUM_1024_Val  _U_(0xA)   /**< \brief (ADC_AVGCTRL) 1024 samples */
#define ADC_AVGCTRL_SAMPLENUM_1     (ADC_AVGCTRL_SAMPLENUM_1_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_2     (ADC_AVGCTRL_SAMPLENUM_2_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_4     (ADC_AVGCTRL_SAMPLENUM_4_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_8     (ADC_AVGCTRL_SAMPLENUM_8_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_16    (ADC_AVGCTRL_SAMPLENUM_16_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_32    (ADC_AVGCTRL_SAMPLENUM_32_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_64    (ADC_AVGCTRL_SAMPLENUM_64_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_128   (ADC_AVGCTRL_SAMPLENUM_128_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_256   (ADC_AVGCTRL_SAMPLENUM_256_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_512   (ADC_AVGCTRL_SAMPLENUM_512_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_1024  (ADC_AVGCTRL_SAMPLENUM_1024_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_ADJRES_Pos      4            /**< \brief (ADC_AVGCTRL) Adjusting Result / Division Coefficient */
#define ADC_AVGCTRL_ADJRES_Msk      (_U_(0x7) << ADC_AVGCTRL_ADJRES_Pos)
#define ADC_AVGCTRL_ADJRES(value)   (ADC_AVGCTRL_ADJRES_Msk & ((value) << ADC_AVGCTRL_ADJRES_Pos))
#define ADC_AVGCTRL_MASK            _U_(0x7F)    /**< \brief (ADC_AVGCTRL) MASK Register */

/* -------- ADC_SAMPCTRL : (ADC Offset: 0x0D) (R/W  8) Sample Time Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SAMPLEN:6;        /*!< bit:  0.. 5  Sampling Time Length               */
    uint8_t  :1;               /*!< bit:      6  Reserved                           */
    uint8_t  OFFCOMP:1;        /*!< bit:      7  Comparator Offset Compensation Enable */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_SAMPCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SAMPCTRL_OFFSET         0x0D         /**< \brief (ADC_SAMPCTRL offset) Sample Time Control */
#define ADC_SAMPCTRL_RESETVALUE     _U_(0x00)    /**< \brief (ADC_SAMPCTRL reset_value) Sample Time Control */

#define ADC_SAMPCTRL_SAMPLEN_Pos    0            /**< \brief (ADC_SAMPCTRL) Sampling Time Length */
#define ADC_SAMPCTRL_SAMPLEN_Msk    (_U_(0x3F) << ADC_SAMPCTRL_SAMPLEN_Pos)
#define ADC_SAMPCTRL_SAMPLEN(value) (ADC_SAMPCTRL_SAMPLEN_Msk & ((value) << ADC_SAMPCTRL_SAMPLEN_Pos))
#define ADC_SAMPCTRL_OFFCOMP_Pos    7            /**< \brief (ADC_SAMPCTRL) Comparator Offset Compensation Enable */
#define ADC_SAMPCTRL_OFFCOMP        (_U_(0x1) << ADC_SAMPCTRL_OFFCOMP_Pos)
#define ADC_SAMPCTRL_MASK           _U_(0xBF)    /**< \brief (ADC_SAMPCTRL) MASK Register */

/* -------- ADC_WINLT : (ADC Offset: 0x0E) (R/W 16) Window Monitor Lower Threshold -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t WINLT:16;         /*!< bit:  0..15  Window Lower Threshold             */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_WINLT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_WINLT_OFFSET            0x0E         /**< \brief (ADC_WINLT offset) Window Monitor Lower Threshold */
#define ADC_WINLT_RESETVALUE        _U_(0x0000)  /**< \brief (ADC_WINLT reset_value) Window Monitor Lower Threshold */

#define ADC_WINLT_WINLT_Pos         0            /**< \brief (ADC_WINLT) Window Lower Threshold */
#define ADC_WINLT_WINLT_Msk         (_U_(0xFFFF) << ADC_WINLT_WINLT_Pos)
#define ADC_WINLT_WINLT(value)      (ADC_WINLT_WINLT_Msk & ((value) << ADC_WINLT_WINLT_Pos))
#define ADC_WINLT_MASK              _U_(0xFFFF)  /**< \brief (ADC_WINLT) MASK Register */

/* -------- ADC_WINUT : (ADC Offset: 0x10) (R/W 16) Window Monitor Upper Threshold -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t WINUT:16;         /*!< bit:  0..15  Window Upper Threshold             */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_WINUT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_WINUT_OFFSET            0x10         /**< \brief (ADC_WINUT offset) Window Monitor Upper Threshold */
#define ADC_WINUT_RESETVALUE        _U_(0x0000)  /**< \brief (ADC_WINUT reset_value) Window Monitor Upper Threshold */

#define ADC_WINUT_WINUT_Pos         0            /**< \brief (ADC_WINUT) Window Upper Threshold */
#define ADC_WINUT_WINUT_Msk         (_U_(0xFFFF) << ADC_WINUT_WINUT_Pos)
#define ADC_WINUT_WINUT(value)      (ADC_WINUT_WINUT_Msk & ((value) << ADC_WINUT_WINUT_Pos))
#define ADC_WINUT_MASK              _U_(0xFFFF)  /**< \brief (ADC_WINUT) MASK Register */

/* -------- ADC_GAINCORR : (ADC Offset: 0x12) (R/W 16) Gain Correction -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t GAINCORR:12;      /*!< bit:  0..11  Gain Correction Value              */
    uint16_t :4;               /*!< bit: 12..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_GAINCORR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_GAINCORR_OFFSET         0x12         /**< \brief (ADC_GAINCORR offset) Gain Correction */
#define ADC_GAINCORR_RESETVALUE     _U_(0x0000)  /**< \brief (ADC_GAINCORR reset_value) Gain Correction */

#define ADC_GAINCORR_GAINCORR_Pos   0            /**< \brief (ADC_GAINCORR) Gain Correction Value */
#define ADC_GAINCORR_GAINCORR_Msk   (_U_(0xFFF) << ADC_GAINCORR_GAINCORR_Pos)
#define ADC_GAINCORR_GAINCORR(value) (ADC_GAINCORR_GAINCORR_Msk & ((value) << ADC_GAINCORR_GAINCORR_Pos))
#define ADC_GAINCORR_MASK           _U_(0x0FFF)  /**< \brief (ADC_GAINCORR) MASK Register */

/* -------- ADC_OFFSETCORR : (ADC Offset: 0x14) (R/W 16) Offset Correction -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t OFFSETCORR:12;    /*!< bit:  0..11  Offset Correction Value            */
    uint16_t :4;               /*!< bit: 12..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_OFFSETCORR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_OFFSETCORR_OFFSET       0x14         /**< \brief (ADC_OFFSETCORR offset) Offset Correction */
#define ADC_OFFSETCORR_RESETVALUE   _U_(0x0000)  /**< \brief (ADC_OFFSETCORR reset_value) Offset Correction */

#define ADC_OFFSETCORR_OFFSETCORR_Pos 0            /**< \brief (ADC_OFFSETCORR) Offset Correction Value */
#define ADC_OFFSETCORR_OFFSETCORR_Msk (_U_(0xFFF) << ADC_OFFSETCORR_OFFSETCORR_Pos)
#define ADC_OFFSETCORR_OFFSETCORR(value) (ADC_OFFSETCORR_OFFSETCORR_Msk & ((value) << ADC_OFFSETCORR_OFFSETCORR_Pos))
#define ADC_OFFSETCORR_MASK         _U_(0x0FFF)  /**< \brief (ADC_OFFSETCORR) MASK Register */

/* -------- ADC_SWTRIG : (ADC Offset: 0x18) (R/W  8) Software Trigger -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  FLUSH:1;          /*!< bit:      0  ADC Flush                          */
    uint8_t  START:1;          /*!< bit:      1  Start ADC Conversion               */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_SWTRIG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SWTRIG_OFFSET           0x18         /**< \brief (ADC_SWTRIG offset) Software Trigger */
#define ADC_SWTRIG_RESETVALUE       _U_(0x00)    /**< \brief (ADC_SWTRIG reset_value) Software Trigger */

#define ADC_SWTRIG_FLUSH_Pos        0            /**< \brief (ADC_SWTRIG) ADC Flush */
#define ADC_SWTRIG_FLUSH            (_U_(0x1) << ADC_SWTRIG_FLUSH_Pos)
#define ADC_SWTRIG_START_Pos        1            /**< \brief (ADC_SWTRIG) Start ADC Conversion */
#define ADC_SWTRIG_START            (_U_(0x1) << ADC_SWTRIG_START_Pos)
#define ADC_SWTRIG_MASK             _U_(0x03)    /**< \brief (ADC_SWTRIG) MASK Register */

/* -------- ADC_DBGCTRL : (ADC Offset: 0x1C) (R/W  8) Debug Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGRUN:1;         /*!< bit:      0  Debug Run                          */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} ADC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_DBGCTRL_OFFSET          0x1C         /**< \brief (ADC_DBGCTRL offset) Debug Control */
#define ADC_DBGCTRL_RESETVALUE      _U_(0x00)    /**< \brief (ADC_DBGCTRL reset_value) Debug Control */

#define ADC_DBGCTRL_DBGRUN_Pos      0            /**< \brief (ADC_DBGCTRL) Debug Run */
#define ADC_DBGCTRL_DBGRUN          (_U_(0x1) << ADC_DBGCTRL_DBGRUN_Pos)
#define ADC_DBGCTRL_MASK            _U_(0x01)    /**< \brief (ADC_DBGCTRL) MASK Register */

/* -------- ADC_SYNCBUSY : (ADC Offset: 0x20) (R/  16) Synchronization Busy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t SWRST:1;          /*!< bit:      0  SWRST Synchronization Busy         */
    uint16_t ENABLE:1;         /*!< bit:      1  ENABLE Synchronization Busy        */
    uint16_t INPUTCTRL:1;      /*!< bit:      2  INPUTCTRL Synchronization Busy     */
    uint16_t CTRLC:1;          /*!< bit:      3  CTRLC Synchronization Busy         */
    uint16_t AVGCTRL:1;        /*!< bit:      4  AVGCTRL Synchronization Busy       */
    uint16_t SAMPCTRL:1;       /*!< bit:      5  SAMPCTRL Synchronization Busy      */
    uint16_t WINLT:1;          /*!< bit:      6  WINLT Synchronization Busy         */
    uint16_t WINUT:1;          /*!< bit:      7  WINUT Synchronization Busy         */
    uint16_t GAINCORR:1;       /*!< bit:      8  GAINCORR Synchronization Busy      */
    uint16_t OFFSETCORR:1;     /*!< bit:      9  OFFSETCTRL Synchronization Busy    */
    uint16_t SWTRIG:1;         /*!< bit:     10  SWTRG Synchronization Busy         */
    uint16_t :5;               /*!< bit: 11..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SYNCBUSY_OFFSET         0x20         /**< \brief (ADC_SYNCBUSY offset) Synchronization Busy */
#define ADC_SYNCBUSY_RESETVALUE     _U_(0x0000)  /**< \brief (ADC_SYNCBUSY reset_value) Synchronization Busy */

#define ADC_SYNCBUSY_SWRST_Pos      0            /**< \brief (ADC_SYNCBUSY) SWRST Synchronization Busy */
#define ADC_SYNCBUSY_SWRST          (_U_(0x1) << ADC_SYNCBUSY_SWRST_Pos)
#define ADC_SYNCBUSY_ENABLE_Pos     1            /**< \brief (ADC_SYNCBUSY) ENABLE Synchronization Busy */
#define ADC_SYNCBUSY_ENABLE         (_U_(0x1) << ADC_SYNCBUSY_ENABLE_Pos)
#define ADC_SYNCBUSY_INPUTCTRL_Pos  2            /**< \brief (ADC_SYNCBUSY) INPUTCTRL Synchronization Busy */
#define ADC_SYNCBUSY_INPUTCTRL      (_U_(0x1) << ADC_SYNCBUSY_INPUTCTRL_Pos)
#define ADC_SYNCBUSY_CTRLC_Pos      3            /**< \brief (ADC_SYNCBUSY) CTRLC Synchronization Busy */
#define ADC_SYNCBUSY_CTRLC          (_U_(0x1) << ADC_SYNCBUSY_CTRLC_Pos)
#define ADC_SYNCBUSY_AVGCTRL_Pos    4            /**< \brief (ADC_SYNCBUSY) AVGCTRL Synchronization Busy */
#define ADC_SYNCBUSY_AVGCTRL        (_U_(0x1) << ADC_SYNCBUSY_AVGCTRL_Pos)
#define ADC_SYNCBUSY_SAMPCTRL_Pos   5            /**< \brief (ADC_SYNCBUSY) SAMPCTRL Synchronization Busy */
#define ADC_SYNCBUSY_SAMPCTRL       (_U_(0x1) << ADC_SYNCBUSY_SAMPCTRL_Pos)
#define ADC_SYNCBUSY_WINLT_Pos      6            /**< \brief (ADC_SYNCBUSY) WINLT Synchronization Busy */
#define ADC_SYNCBUSY_WINLT          (_U_(0x1) << ADC_SYNCBUSY_WINLT_Pos)
#define ADC_SYNCBUSY_WINUT_Pos      7            /**< \brief (ADC_SYNCBUSY) WINUT Synchronization Busy */
#define ADC_SYNCBUSY_WINUT          (_U_(0x1) << ADC_SYNCBUSY_WINUT_Pos)
#define ADC_SYNCBUSY_GAINCORR_Pos   8            /**< \brief (ADC_SYNCBUSY) GAINCORR Synchronization Busy */
#define ADC_SYNCBUSY_GAINCORR       (_U_(0x1) << ADC_SYNCBUSY_GAINCORR_Pos)
#define ADC_SYNCBUSY_OFFSETCORR_Pos 9            /**< \brief (ADC_SYNCBUSY) OFFSETCTRL Synchronization Busy */
#define ADC_SYNCBUSY_OFFSETCORR     (_U_(0x1) << ADC_SYNCBUSY_OFFSETCORR_Pos)
#define ADC_SYNCBUSY_SWTRIG_Pos     10           /**< \brief (ADC_SYNCBUSY) SWTRG Synchronization Busy */
#define ADC_SYNCBUSY_SWTRIG         (_U_(0x1) << ADC_SYNCBUSY_SWTRIG_Pos)
#define ADC_SYNCBUSY_MASK           _U_(0x07FF)  /**< \brief (ADC_SYNCBUSY) MASK Register */

/* -------- ADC_RESULT : (ADC Offset: 0x24) (R/  16) Result -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t RESULT:16;        /*!< bit:  0..15  Result Value                       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_RESULT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_RESULT_OFFSET           0x24         /**< \brief (ADC_RESULT offset) Result */
#define ADC_RESULT_RESETVALUE       _U_(0x0000)  /**< \brief (ADC_RESULT reset_value) Result */

#define ADC_RESULT_RESULT_Pos       0            /**< \brief (ADC_RESULT) Result Value */
#define ADC_RESULT_RESULT_Msk       (_U_(0xFFFF) << ADC_RESULT_RESULT_Pos)
#define ADC_RESULT_RESULT(value)    (ADC_RESULT_RESULT_Msk & ((value) << ADC_RESULT_RESULT_Pos))
#define ADC_RESULT_MASK             _U_(0xFFFF)  /**< \brief (ADC_RESULT) MASK Register */

/* -------- ADC_SEQCTRL : (ADC Offset: 0x28) (R/W 32) Sequence Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SEQEN:32;         /*!< bit:  0..31  Enable Positive Input in the Sequence */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} ADC_SEQCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_SEQCTRL_OFFSET          0x28         /**< \brief (ADC_SEQCTRL offset) Sequence Control */
#define ADC_SEQCTRL_RESETVALUE      _U_(0x00000000) /**< \brief (ADC_SEQCTRL reset_value) Sequence Control */

#define ADC_SEQCTRL_SEQEN_Pos       0            /**< \brief (ADC_SEQCTRL) Enable Positive Input in the Sequence */
#define ADC_SEQCTRL_SEQEN_Msk       (_U_(0xFFFFFFFF) << ADC_SEQCTRL_SEQEN_Pos)
#define ADC_SEQCTRL_SEQEN(value)    (ADC_SEQCTRL_SEQEN_Msk & ((value) << ADC_SEQCTRL_SEQEN_Pos))
#define ADC_SEQCTRL_MASK            _U_(0xFFFFFFFF) /**< \brief (ADC_SEQCTRL) MASK Register */

/* -------- ADC_CALIB : (ADC Offset: 0x2C) (R/W 16) Calibration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t BIASCOMP:3;       /*!< bit:  0.. 2  Bias Comparator Scaling            */
    uint16_t :5;               /*!< bit:  3.. 7  Reserved                           */
    uint16_t BIASREFBUF:3;     /*!< bit:  8..10  Bias  Reference Buffer Scaling     */
    uint16_t :5;               /*!< bit: 11..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} ADC_CALIB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ADC_CALIB_OFFSET            0x2C         /**< \brief (ADC_CALIB offset) Calibration */
#define ADC_CALIB_RESETVALUE        _U_(0x0000)  /**< \brief (ADC_CALIB reset_value) Calibration */

#define ADC_CALIB_BIASCOMP_Pos      0            /**< \brief (ADC_CALIB) Bias Comparator Scaling */
#define ADC_CALIB_BIASCOMP_Msk      (_U_(0x7) << ADC_CALIB_BIASCOMP_Pos)
#define ADC_CALIB_BIASCOMP(value)   (ADC_CALIB_BIASCOMP_Msk & ((value) << ADC_CALIB_BIASCOMP_Pos))
#define ADC_CALIB_BIASREFBUF_Pos    8            /**< \brief (ADC_CALIB) Bias  Reference Buffer Scaling */
#define ADC_CALIB_BIASREFBUF_Msk    (_U_(0x7) << ADC_CALIB_BIASREFBUF_Pos)
#define ADC_CALIB_BIASREFBUF(value) (ADC_CALIB_BIASREFBUF_Msk & ((value) << ADC_CALIB_BIASREFBUF_Pos))
#define ADC_CALIB_MASK              _U_(0x0707)  /**< \brief (ADC_CALIB) MASK Register */

/** \brief ADC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO ADC_CTRLA_Type            CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A */
  __IO ADC_CTRLB_Type            CTRLB;       /**< \brief Offset: 0x01 (R/W  8) Control B */
  __IO ADC_REFCTRL_Type          REFCTRL;     /**< \brief Offset: 0x02 (R/W  8) Reference Control */
  __IO ADC_EVCTRL_Type           EVCTRL;      /**< \brief Offset: 0x03 (R/W  8) Event Control */
  __IO ADC_INTENCLR_Type         INTENCLR;    /**< \brief Offset: 0x04 (R/W  8) Interrupt Enable Clear */
  __IO ADC_INTENSET_Type         INTENSET;    /**< \brief Offset: 0x05 (R/W  8) Interrupt Enable Set */
  __IO ADC_INTFLAG_Type          INTFLAG;     /**< \brief Offset: 0x06 (R/W  8) Interrupt Flag Status and Clear */
  __I  ADC_SEQSTATUS_Type        SEQSTATUS;   /**< \brief Offset: 0x07 (R/   8) Sequence Status */
  __IO ADC_INPUTCTRL_Type        INPUTCTRL;   /**< \brief Offset: 0x08 (R/W 16) Input Control */
  __IO ADC_CTRLC_Type            CTRLC;       /**< \brief Offset: 0x0A (R/W 16) Control C */
  __IO ADC_AVGCTRL_Type          AVGCTRL;     /**< \brief Offset: 0x0C (R/W  8) Average Control */
  __IO ADC_SAMPCTRL_Type         SAMPCTRL;    /**< \brief Offset: 0x0D (R/W  8) Sample Time Control */
  __IO ADC_WINLT_Type            WINLT;       /**< \brief Offset: 0x0E (R/W 16) Window Monitor Lower Threshold */
  __IO ADC_WINUT_Type            WINUT;       /**< \brief Offset: 0x10 (R/W 16) Window Monitor Upper Threshold */
  __IO ADC_GAINCORR_Type         GAINCORR;    /**< \brief Offset: 0x12 (R/W 16) Gain Correction */
  __IO ADC_OFFSETCORR_Type       OFFSETCORR;  /**< \brief Offset: 0x14 (R/W 16) Offset Correction */
       RoReg8                    Reserved1[0x2];
  __IO ADC_SWTRIG_Type           SWTRIG;      /**< \brief Offset: 0x18 (R/W  8) Software Trigger */
       RoReg8                    Reserved2[0x3];
  __IO ADC_DBGCTRL_Type          DBGCTRL;     /**< \brief Offset: 0x1C (R/W  8) Debug Control */
       RoReg8                    Reserved3[0x3];
  __I  ADC_SYNCBUSY_Type         SYNCBUSY;    /**< \brief Offset: 0x20 (R/  16) Synchronization Busy */
       RoReg8                    Reserved4[0x2];
  __I  ADC_RESULT_Type           RESULT;      /**< \brief Offset: 0x24 (R/  16) Result */
       RoReg8                    Reserved5[0x2];
  __IO ADC_SEQCTRL_Type          SEQCTRL;     /**< \brief Offset: 0x28 (R/W 32) Sequence Control */
  __IO ADC_CALIB_Type            CALIB;       /**< \brief Offset: 0x2C (R/W 16) Calibration */
} Adc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_ADC_COMPONENT_ */
