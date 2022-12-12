/**
 * \file
 *
 * \brief Component description for SDADC
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

#ifndef _SAMC21_SDADC_COMPONENT_
#define _SAMC21_SDADC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SDADC */
/* ========================================================================== */
/** \addtogroup SAMC21_SDADC Sigma-Delta Analog Digital Converter */
/*@{*/

#define SDADC_U2260
#define REV_SDADC                   0x101

/* -------- SDADC_CTRLA : (SDADC Offset: 0x00) (R/W  8) Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :4;               /*!< bit:  2.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_CTRLA_OFFSET          0x00         /**< \brief (SDADC_CTRLA offset) Control A */
#define SDADC_CTRLA_RESETVALUE      _U_(0x00)    /**< \brief (SDADC_CTRLA reset_value) Control A */

#define SDADC_CTRLA_SWRST_Pos       0            /**< \brief (SDADC_CTRLA) Software Reset */
#define SDADC_CTRLA_SWRST           (_U_(0x1) << SDADC_CTRLA_SWRST_Pos)
#define SDADC_CTRLA_ENABLE_Pos      1            /**< \brief (SDADC_CTRLA) Enable */
#define SDADC_CTRLA_ENABLE          (_U_(0x1) << SDADC_CTRLA_ENABLE_Pos)
#define SDADC_CTRLA_RUNSTDBY_Pos    6            /**< \brief (SDADC_CTRLA) Run during Standby */
#define SDADC_CTRLA_RUNSTDBY        (_U_(0x1) << SDADC_CTRLA_RUNSTDBY_Pos)
#define SDADC_CTRLA_ONDEMAND_Pos    7            /**< \brief (SDADC_CTRLA) On Demand Control */
#define SDADC_CTRLA_ONDEMAND        (_U_(0x1) << SDADC_CTRLA_ONDEMAND_Pos)
#define SDADC_CTRLA_MASK            _U_(0xC3)    /**< \brief (SDADC_CTRLA) MASK Register */

/* -------- SDADC_REFCTRL : (SDADC Offset: 0x01) (R/W  8) Reference Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  REFSEL:2;         /*!< bit:  0.. 1  Reference Selection                */
    uint8_t  :2;               /*!< bit:  2.. 3  Reserved                           */
    uint8_t  REFRANGE:2;       /*!< bit:  4.. 5  Reference Range                    */
    uint8_t  :1;               /*!< bit:      6  Reserved                           */
    uint8_t  ONREFBUF:1;       /*!< bit:      7  Reference Buffer                   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_REFCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_REFCTRL_OFFSET        0x01         /**< \brief (SDADC_REFCTRL offset) Reference Control */
#define SDADC_REFCTRL_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_REFCTRL reset_value) Reference Control */

#define SDADC_REFCTRL_REFSEL_Pos    0            /**< \brief (SDADC_REFCTRL) Reference Selection */
#define SDADC_REFCTRL_REFSEL_Msk    (_U_(0x3) << SDADC_REFCTRL_REFSEL_Pos)
#define SDADC_REFCTRL_REFSEL(value) (SDADC_REFCTRL_REFSEL_Msk & ((value) << SDADC_REFCTRL_REFSEL_Pos))
#define   SDADC_REFCTRL_REFSEL_INTREF_Val _U_(0x0)   /**< \brief (SDADC_REFCTRL) Internal Bandgap Reference */
#define   SDADC_REFCTRL_REFSEL_AREFB_Val  _U_(0x1)   /**< \brief (SDADC_REFCTRL) External Reference */
#define   SDADC_REFCTRL_REFSEL_DAC_Val    _U_(0x2)   /**< \brief (SDADC_REFCTRL) Internal DAC Output */
#define   SDADC_REFCTRL_REFSEL_INTVCC_Val _U_(0x3)   /**< \brief (SDADC_REFCTRL) VDDANA */
#define SDADC_REFCTRL_REFSEL_INTREF (SDADC_REFCTRL_REFSEL_INTREF_Val << SDADC_REFCTRL_REFSEL_Pos)
#define SDADC_REFCTRL_REFSEL_AREFB  (SDADC_REFCTRL_REFSEL_AREFB_Val << SDADC_REFCTRL_REFSEL_Pos)
#define SDADC_REFCTRL_REFSEL_DAC    (SDADC_REFCTRL_REFSEL_DAC_Val  << SDADC_REFCTRL_REFSEL_Pos)
#define SDADC_REFCTRL_REFSEL_INTVCC (SDADC_REFCTRL_REFSEL_INTVCC_Val << SDADC_REFCTRL_REFSEL_Pos)
#define SDADC_REFCTRL_REFRANGE_Pos  4            /**< \brief (SDADC_REFCTRL) Reference Range */
#define SDADC_REFCTRL_REFRANGE_Msk  (_U_(0x3) << SDADC_REFCTRL_REFRANGE_Pos)
#define SDADC_REFCTRL_REFRANGE(value) (SDADC_REFCTRL_REFRANGE_Msk & ((value) << SDADC_REFCTRL_REFRANGE_Pos))
#define SDADC_REFCTRL_ONREFBUF_Pos  7            /**< \brief (SDADC_REFCTRL) Reference Buffer */
#define SDADC_REFCTRL_ONREFBUF      (_U_(0x1) << SDADC_REFCTRL_ONREFBUF_Pos)
#define SDADC_REFCTRL_MASK          _U_(0xB3)    /**< \brief (SDADC_REFCTRL) MASK Register */

/* -------- SDADC_CTRLB : (SDADC Offset: 0x02) (R/W 16) Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t PRESCALER:8;      /*!< bit:  0.. 7  Prescaler Configuration            */
    uint16_t OSR:3;            /*!< bit:  8..10  Over Sampling Ratio                */
    uint16_t :1;               /*!< bit:     11  Reserved                           */
    uint16_t SKPCNT:4;         /*!< bit: 12..15  Skip Sample Count                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SDADC_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_CTRLB_OFFSET          0x02         /**< \brief (SDADC_CTRLB offset) Control B */
#define SDADC_CTRLB_RESETVALUE      _U_(0x2000)  /**< \brief (SDADC_CTRLB reset_value) Control B */

#define SDADC_CTRLB_PRESCALER_Pos   0            /**< \brief (SDADC_CTRLB) Prescaler Configuration */
#define SDADC_CTRLB_PRESCALER_Msk   (_U_(0xFF) << SDADC_CTRLB_PRESCALER_Pos)
#define SDADC_CTRLB_PRESCALER(value) (SDADC_CTRLB_PRESCALER_Msk & ((value) << SDADC_CTRLB_PRESCALER_Pos))
#define SDADC_CTRLB_OSR_Pos         8            /**< \brief (SDADC_CTRLB) Over Sampling Ratio */
#define SDADC_CTRLB_OSR_Msk         (_U_(0x7) << SDADC_CTRLB_OSR_Pos)
#define SDADC_CTRLB_OSR(value)      (SDADC_CTRLB_OSR_Msk & ((value) << SDADC_CTRLB_OSR_Pos))
#define SDADC_CTRLB_SKPCNT_Pos      12           /**< \brief (SDADC_CTRLB) Skip Sample Count */
#define SDADC_CTRLB_SKPCNT_Msk      (_U_(0xF) << SDADC_CTRLB_SKPCNT_Pos)
#define SDADC_CTRLB_SKPCNT(value)   (SDADC_CTRLB_SKPCNT_Msk & ((value) << SDADC_CTRLB_SKPCNT_Pos))
#define SDADC_CTRLB_MASK            _U_(0xF7FF)  /**< \brief (SDADC_CTRLB) MASK Register */

/* -------- SDADC_EVCTRL : (SDADC Offset: 0x04) (R/W  8) Event Control -------- */
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
} SDADC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_EVCTRL_OFFSET         0x04         /**< \brief (SDADC_EVCTRL offset) Event Control */
#define SDADC_EVCTRL_RESETVALUE     _U_(0x00)    /**< \brief (SDADC_EVCTRL reset_value) Event Control */

#define SDADC_EVCTRL_FLUSHEI_Pos    0            /**< \brief (SDADC_EVCTRL) Flush Event Input Enable */
#define SDADC_EVCTRL_FLUSHEI        (_U_(0x1) << SDADC_EVCTRL_FLUSHEI_Pos)
#define SDADC_EVCTRL_STARTEI_Pos    1            /**< \brief (SDADC_EVCTRL) Start Conversion Event Input Enable */
#define SDADC_EVCTRL_STARTEI        (_U_(0x1) << SDADC_EVCTRL_STARTEI_Pos)
#define SDADC_EVCTRL_FLUSHINV_Pos   2            /**< \brief (SDADC_EVCTRL) Flush Event Invert Enable */
#define SDADC_EVCTRL_FLUSHINV       (_U_(0x1) << SDADC_EVCTRL_FLUSHINV_Pos)
#define SDADC_EVCTRL_STARTINV_Pos   3            /**< \brief (SDADC_EVCTRL) Satrt Event Invert Enable */
#define SDADC_EVCTRL_STARTINV       (_U_(0x1) << SDADC_EVCTRL_STARTINV_Pos)
#define SDADC_EVCTRL_RESRDYEO_Pos   4            /**< \brief (SDADC_EVCTRL) Result Ready Event Out */
#define SDADC_EVCTRL_RESRDYEO       (_U_(0x1) << SDADC_EVCTRL_RESRDYEO_Pos)
#define SDADC_EVCTRL_WINMONEO_Pos   5            /**< \brief (SDADC_EVCTRL) Window Monitor Event Out */
#define SDADC_EVCTRL_WINMONEO       (_U_(0x1) << SDADC_EVCTRL_WINMONEO_Pos)
#define SDADC_EVCTRL_MASK           _U_(0x3F)    /**< \brief (SDADC_EVCTRL) MASK Register */

/* -------- SDADC_INTENCLR : (SDADC Offset: 0x05) (R/W  8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Disable     */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Disable          */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Disable   */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_INTENCLR_OFFSET       0x05         /**< \brief (SDADC_INTENCLR offset) Interrupt Enable Clear */
#define SDADC_INTENCLR_RESETVALUE   _U_(0x00)    /**< \brief (SDADC_INTENCLR reset_value) Interrupt Enable Clear */

#define SDADC_INTENCLR_RESRDY_Pos   0            /**< \brief (SDADC_INTENCLR) Result Ready Interrupt Disable */
#define SDADC_INTENCLR_RESRDY       (_U_(0x1) << SDADC_INTENCLR_RESRDY_Pos)
#define SDADC_INTENCLR_OVERRUN_Pos  1            /**< \brief (SDADC_INTENCLR) Overrun Interrupt Disable */
#define SDADC_INTENCLR_OVERRUN      (_U_(0x1) << SDADC_INTENCLR_OVERRUN_Pos)
#define SDADC_INTENCLR_WINMON_Pos   2            /**< \brief (SDADC_INTENCLR) Window Monitor Interrupt Disable */
#define SDADC_INTENCLR_WINMON       (_U_(0x1) << SDADC_INTENCLR_WINMON_Pos)
#define SDADC_INTENCLR_MASK         _U_(0x07)    /**< \brief (SDADC_INTENCLR) MASK Register */

/* -------- SDADC_INTENSET : (SDADC Offset: 0x06) (R/W  8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Enable      */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Enable           */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Enable    */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_INTENSET_OFFSET       0x06         /**< \brief (SDADC_INTENSET offset) Interrupt Enable Set */
#define SDADC_INTENSET_RESETVALUE   _U_(0x00)    /**< \brief (SDADC_INTENSET reset_value) Interrupt Enable Set */

#define SDADC_INTENSET_RESRDY_Pos   0            /**< \brief (SDADC_INTENSET) Result Ready Interrupt Enable */
#define SDADC_INTENSET_RESRDY       (_U_(0x1) << SDADC_INTENSET_RESRDY_Pos)
#define SDADC_INTENSET_OVERRUN_Pos  1            /**< \brief (SDADC_INTENSET) Overrun Interrupt Enable */
#define SDADC_INTENSET_OVERRUN      (_U_(0x1) << SDADC_INTENSET_OVERRUN_Pos)
#define SDADC_INTENSET_WINMON_Pos   2            /**< \brief (SDADC_INTENSET) Window Monitor Interrupt Enable */
#define SDADC_INTENSET_WINMON       (_U_(0x1) << SDADC_INTENSET_WINMON_Pos)
#define SDADC_INTENSET_MASK         _U_(0x07)    /**< \brief (SDADC_INTENSET) MASK Register */

/* -------- SDADC_INTFLAG : (SDADC Offset: 0x07) (R/W  8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Flag        */
    __I uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Flag             */
    __I uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Flag      */
    __I uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_INTFLAG_OFFSET        0x07         /**< \brief (SDADC_INTFLAG offset) Interrupt Flag Status and Clear */
#define SDADC_INTFLAG_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define SDADC_INTFLAG_RESRDY_Pos    0            /**< \brief (SDADC_INTFLAG) Result Ready Interrupt Flag */
#define SDADC_INTFLAG_RESRDY        (_U_(0x1) << SDADC_INTFLAG_RESRDY_Pos)
#define SDADC_INTFLAG_OVERRUN_Pos   1            /**< \brief (SDADC_INTFLAG) Overrun Interrupt Flag */
#define SDADC_INTFLAG_OVERRUN       (_U_(0x1) << SDADC_INTFLAG_OVERRUN_Pos)
#define SDADC_INTFLAG_WINMON_Pos    2            /**< \brief (SDADC_INTFLAG) Window Monitor Interrupt Flag */
#define SDADC_INTFLAG_WINMON        (_U_(0x1) << SDADC_INTFLAG_WINMON_Pos)
#define SDADC_INTFLAG_MASK          _U_(0x07)    /**< \brief (SDADC_INTFLAG) MASK Register */

/* -------- SDADC_SEQSTATUS : (SDADC Offset: 0x08) (R/   8) Sequence Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SEQSTATE:4;       /*!< bit:  0.. 3  Sequence State                     */
    uint8_t  :3;               /*!< bit:  4.. 6  Reserved                           */
    uint8_t  SEQBUSY:1;        /*!< bit:      7  Sequence Busy                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_SEQSTATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_SEQSTATUS_OFFSET      0x08         /**< \brief (SDADC_SEQSTATUS offset) Sequence Status */
#define SDADC_SEQSTATUS_RESETVALUE  _U_(0x00)    /**< \brief (SDADC_SEQSTATUS reset_value) Sequence Status */

#define SDADC_SEQSTATUS_SEQSTATE_Pos 0            /**< \brief (SDADC_SEQSTATUS) Sequence State */
#define SDADC_SEQSTATUS_SEQSTATE_Msk (_U_(0xF) << SDADC_SEQSTATUS_SEQSTATE_Pos)
#define SDADC_SEQSTATUS_SEQSTATE(value) (SDADC_SEQSTATUS_SEQSTATE_Msk & ((value) << SDADC_SEQSTATUS_SEQSTATE_Pos))
#define SDADC_SEQSTATUS_SEQBUSY_Pos 7            /**< \brief (SDADC_SEQSTATUS) Sequence Busy */
#define SDADC_SEQSTATUS_SEQBUSY     (_U_(0x1) << SDADC_SEQSTATUS_SEQBUSY_Pos)
#define SDADC_SEQSTATUS_MASK        _U_(0x8F)    /**< \brief (SDADC_SEQSTATUS) MASK Register */

/* -------- SDADC_INPUTCTRL : (SDADC Offset: 0x09) (R/W  8) Input Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  MUXSEL:4;         /*!< bit:  0.. 3  SDADC Input Selection              */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_INPUTCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_INPUTCTRL_OFFSET      0x09         /**< \brief (SDADC_INPUTCTRL offset) Input Control */
#define SDADC_INPUTCTRL_RESETVALUE  _U_(0x00)    /**< \brief (SDADC_INPUTCTRL reset_value) Input Control */

#define SDADC_INPUTCTRL_MUXSEL_Pos  0            /**< \brief (SDADC_INPUTCTRL) SDADC Input Selection */
#define SDADC_INPUTCTRL_MUXSEL_Msk  (_U_(0xF) << SDADC_INPUTCTRL_MUXSEL_Pos)
#define SDADC_INPUTCTRL_MUXSEL(value) (SDADC_INPUTCTRL_MUXSEL_Msk & ((value) << SDADC_INPUTCTRL_MUXSEL_Pos))
#define   SDADC_INPUTCTRL_MUXSEL_AIN0_Val _U_(0x0)   /**< \brief (SDADC_INPUTCTRL) SDADC AIN0 Pin */
#define   SDADC_INPUTCTRL_MUXSEL_AIN1_Val _U_(0x1)   /**< \brief (SDADC_INPUTCTRL) SDADC AIN1 Pin */
#define   SDADC_INPUTCTRL_MUXSEL_AIN2_Val _U_(0x2)   /**< \brief (SDADC_INPUTCTRL) SDADC AIN2 Pin */
#define SDADC_INPUTCTRL_MUXSEL_AIN0 (SDADC_INPUTCTRL_MUXSEL_AIN0_Val << SDADC_INPUTCTRL_MUXSEL_Pos)
#define SDADC_INPUTCTRL_MUXSEL_AIN1 (SDADC_INPUTCTRL_MUXSEL_AIN1_Val << SDADC_INPUTCTRL_MUXSEL_Pos)
#define SDADC_INPUTCTRL_MUXSEL_AIN2 (SDADC_INPUTCTRL_MUXSEL_AIN2_Val << SDADC_INPUTCTRL_MUXSEL_Pos)
#define SDADC_INPUTCTRL_MASK        _U_(0x0F)    /**< \brief (SDADC_INPUTCTRL) MASK Register */

/* -------- SDADC_CTRLC : (SDADC Offset: 0x0A) (R/W  8) Control C -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  FREERUN:1;        /*!< bit:      0  Free Running Mode                  */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_CTRLC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_CTRLC_OFFSET          0x0A         /**< \brief (SDADC_CTRLC offset) Control C */
#define SDADC_CTRLC_RESETVALUE      _U_(0x00)    /**< \brief (SDADC_CTRLC reset_value) Control C */

#define SDADC_CTRLC_FREERUN_Pos     0            /**< \brief (SDADC_CTRLC) Free Running Mode */
#define SDADC_CTRLC_FREERUN         (_U_(0x1) << SDADC_CTRLC_FREERUN_Pos)
#define SDADC_CTRLC_MASK            _U_(0x01)    /**< \brief (SDADC_CTRLC) MASK Register */

/* -------- SDADC_WINCTRL : (SDADC Offset: 0x0B) (R/W  8) Window Monitor Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  WINMODE:3;        /*!< bit:  0.. 2  Window Monitor Mode                */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_WINCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_WINCTRL_OFFSET        0x0B         /**< \brief (SDADC_WINCTRL offset) Window Monitor Control */
#define SDADC_WINCTRL_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_WINCTRL reset_value) Window Monitor Control */

#define SDADC_WINCTRL_WINMODE_Pos   0            /**< \brief (SDADC_WINCTRL) Window Monitor Mode */
#define SDADC_WINCTRL_WINMODE_Msk   (_U_(0x7) << SDADC_WINCTRL_WINMODE_Pos)
#define SDADC_WINCTRL_WINMODE(value) (SDADC_WINCTRL_WINMODE_Msk & ((value) << SDADC_WINCTRL_WINMODE_Pos))
#define SDADC_WINCTRL_MASK          _U_(0x07)    /**< \brief (SDADC_WINCTRL) MASK Register */

/* -------- SDADC_WINLT : (SDADC Offset: 0x0C) (R/W 32) Window Monitor Lower Threshold -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t WINLT:24;         /*!< bit:  0..23  Window Lower Threshold             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SDADC_WINLT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_WINLT_OFFSET          0x0C         /**< \brief (SDADC_WINLT offset) Window Monitor Lower Threshold */
#define SDADC_WINLT_RESETVALUE      _U_(0x00000000) /**< \brief (SDADC_WINLT reset_value) Window Monitor Lower Threshold */

#define SDADC_WINLT_WINLT_Pos       0            /**< \brief (SDADC_WINLT) Window Lower Threshold */
#define SDADC_WINLT_WINLT_Msk       (_U_(0xFFFFFF) << SDADC_WINLT_WINLT_Pos)
#define SDADC_WINLT_WINLT(value)    (SDADC_WINLT_WINLT_Msk & ((value) << SDADC_WINLT_WINLT_Pos))
#define SDADC_WINLT_MASK            _U_(0x00FFFFFF) /**< \brief (SDADC_WINLT) MASK Register */

/* -------- SDADC_WINUT : (SDADC Offset: 0x10) (R/W 32) Window Monitor Upper Threshold -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t WINUT:24;         /*!< bit:  0..23  Window Upper Threshold             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SDADC_WINUT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_WINUT_OFFSET          0x10         /**< \brief (SDADC_WINUT offset) Window Monitor Upper Threshold */
#define SDADC_WINUT_RESETVALUE      _U_(0x00000000) /**< \brief (SDADC_WINUT reset_value) Window Monitor Upper Threshold */

#define SDADC_WINUT_WINUT_Pos       0            /**< \brief (SDADC_WINUT) Window Upper Threshold */
#define SDADC_WINUT_WINUT_Msk       (_U_(0xFFFFFF) << SDADC_WINUT_WINUT_Pos)
#define SDADC_WINUT_WINUT(value)    (SDADC_WINUT_WINUT_Msk & ((value) << SDADC_WINUT_WINUT_Pos))
#define SDADC_WINUT_MASK            _U_(0x00FFFFFF) /**< \brief (SDADC_WINUT) MASK Register */

/* -------- SDADC_OFFSETCORR : (SDADC Offset: 0x14) (R/W 32) Offset Correction -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t OFFSETCORR:24;    /*!< bit:  0..23  Offset Correction Value            */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SDADC_OFFSETCORR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_OFFSETCORR_OFFSET     0x14         /**< \brief (SDADC_OFFSETCORR offset) Offset Correction */
#define SDADC_OFFSETCORR_RESETVALUE _U_(0x00000000) /**< \brief (SDADC_OFFSETCORR reset_value) Offset Correction */

#define SDADC_OFFSETCORR_OFFSETCORR_Pos 0            /**< \brief (SDADC_OFFSETCORR) Offset Correction Value */
#define SDADC_OFFSETCORR_OFFSETCORR_Msk (_U_(0xFFFFFF) << SDADC_OFFSETCORR_OFFSETCORR_Pos)
#define SDADC_OFFSETCORR_OFFSETCORR(value) (SDADC_OFFSETCORR_OFFSETCORR_Msk & ((value) << SDADC_OFFSETCORR_OFFSETCORR_Pos))
#define SDADC_OFFSETCORR_MASK       _U_(0x00FFFFFF) /**< \brief (SDADC_OFFSETCORR) MASK Register */

/* -------- SDADC_GAINCORR : (SDADC Offset: 0x18) (R/W 16) Gain Correction -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t GAINCORR:14;      /*!< bit:  0..13  Gain Correction Value              */
    uint16_t :2;               /*!< bit: 14..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SDADC_GAINCORR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_GAINCORR_OFFSET       0x18         /**< \brief (SDADC_GAINCORR offset) Gain Correction */
#define SDADC_GAINCORR_RESETVALUE   _U_(0x0001)  /**< \brief (SDADC_GAINCORR reset_value) Gain Correction */

#define SDADC_GAINCORR_GAINCORR_Pos 0            /**< \brief (SDADC_GAINCORR) Gain Correction Value */
#define SDADC_GAINCORR_GAINCORR_Msk (_U_(0x3FFF) << SDADC_GAINCORR_GAINCORR_Pos)
#define SDADC_GAINCORR_GAINCORR(value) (SDADC_GAINCORR_GAINCORR_Msk & ((value) << SDADC_GAINCORR_GAINCORR_Pos))
#define SDADC_GAINCORR_MASK         _U_(0x3FFF)  /**< \brief (SDADC_GAINCORR) MASK Register */

/* -------- SDADC_SHIFTCORR : (SDADC Offset: 0x1A) (R/W  8) Shift Correction -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SHIFTCORR:4;      /*!< bit:  0.. 3  Shift Correction Value             */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_SHIFTCORR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_SHIFTCORR_OFFSET      0x1A         /**< \brief (SDADC_SHIFTCORR offset) Shift Correction */
#define SDADC_SHIFTCORR_RESETVALUE  _U_(0x00)    /**< \brief (SDADC_SHIFTCORR reset_value) Shift Correction */

#define SDADC_SHIFTCORR_SHIFTCORR_Pos 0            /**< \brief (SDADC_SHIFTCORR) Shift Correction Value */
#define SDADC_SHIFTCORR_SHIFTCORR_Msk (_U_(0xF) << SDADC_SHIFTCORR_SHIFTCORR_Pos)
#define SDADC_SHIFTCORR_SHIFTCORR(value) (SDADC_SHIFTCORR_SHIFTCORR_Msk & ((value) << SDADC_SHIFTCORR_SHIFTCORR_Pos))
#define SDADC_SHIFTCORR_MASK        _U_(0x0F)    /**< \brief (SDADC_SHIFTCORR) MASK Register */

/* -------- SDADC_SWTRIG : (SDADC Offset: 0x1C) (R/W  8) Software Trigger -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  FLUSH:1;          /*!< bit:      0  SDADC Flush                        */
    uint8_t  START:1;          /*!< bit:      1  Start SDADC Conversion             */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_SWTRIG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_SWTRIG_OFFSET         0x1C         /**< \brief (SDADC_SWTRIG offset) Software Trigger */
#define SDADC_SWTRIG_RESETVALUE     _U_(0x00)    /**< \brief (SDADC_SWTRIG reset_value) Software Trigger */

#define SDADC_SWTRIG_FLUSH_Pos      0            /**< \brief (SDADC_SWTRIG) SDADC Flush */
#define SDADC_SWTRIG_FLUSH          (_U_(0x1) << SDADC_SWTRIG_FLUSH_Pos)
#define SDADC_SWTRIG_START_Pos      1            /**< \brief (SDADC_SWTRIG) Start SDADC Conversion */
#define SDADC_SWTRIG_START          (_U_(0x1) << SDADC_SWTRIG_START_Pos)
#define SDADC_SWTRIG_MASK           _U_(0x03)    /**< \brief (SDADC_SWTRIG) MASK Register */

/* -------- SDADC_SYNCBUSY : (SDADC Offset: 0x20) (R/  32) Synchronization Busy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  SWRST Synchronization Busy         */
    uint32_t ENABLE:1;         /*!< bit:      1  ENABLE Synchronization Busy        */
    uint32_t CTRLC:1;          /*!< bit:      2  CTRLC Synchronization Busy         */
    uint32_t INPUTCTRL:1;      /*!< bit:      3  INPUTCTRL Synchronization Busy     */
    uint32_t WINCTRL:1;        /*!< bit:      4  WINCTRL Synchronization Busy       */
    uint32_t WINLT:1;          /*!< bit:      5  WINLT Synchronization Busy         */
    uint32_t WINUT:1;          /*!< bit:      6  WINUT Synchronization Busy         */
    uint32_t OFFSETCORR:1;     /*!< bit:      7  OFFSETCTRL Synchronization Busy    */
    uint32_t GAINCORR:1;       /*!< bit:      8  GAINCORR Synchronization Busy      */
    uint32_t SHIFTCORR:1;      /*!< bit:      9  SHIFTCORR Synchronization Busy     */
    uint32_t SWTRIG:1;         /*!< bit:     10  SWTRG Synchronization Busy         */
    uint32_t ANACTRL:1;        /*!< bit:     11  ANACTRL Synchronization Busy       */
    uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SDADC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_SYNCBUSY_OFFSET       0x20         /**< \brief (SDADC_SYNCBUSY offset) Synchronization Busy */
#define SDADC_SYNCBUSY_RESETVALUE   _U_(0x00000000) /**< \brief (SDADC_SYNCBUSY reset_value) Synchronization Busy */

#define SDADC_SYNCBUSY_SWRST_Pos    0            /**< \brief (SDADC_SYNCBUSY) SWRST Synchronization Busy */
#define SDADC_SYNCBUSY_SWRST        (_U_(0x1) << SDADC_SYNCBUSY_SWRST_Pos)
#define SDADC_SYNCBUSY_ENABLE_Pos   1            /**< \brief (SDADC_SYNCBUSY) ENABLE Synchronization Busy */
#define SDADC_SYNCBUSY_ENABLE       (_U_(0x1) << SDADC_SYNCBUSY_ENABLE_Pos)
#define SDADC_SYNCBUSY_CTRLC_Pos    2            /**< \brief (SDADC_SYNCBUSY) CTRLC Synchronization Busy */
#define SDADC_SYNCBUSY_CTRLC        (_U_(0x1) << SDADC_SYNCBUSY_CTRLC_Pos)
#define SDADC_SYNCBUSY_INPUTCTRL_Pos 3            /**< \brief (SDADC_SYNCBUSY) INPUTCTRL Synchronization Busy */
#define SDADC_SYNCBUSY_INPUTCTRL    (_U_(0x1) << SDADC_SYNCBUSY_INPUTCTRL_Pos)
#define SDADC_SYNCBUSY_WINCTRL_Pos  4            /**< \brief (SDADC_SYNCBUSY) WINCTRL Synchronization Busy */
#define SDADC_SYNCBUSY_WINCTRL      (_U_(0x1) << SDADC_SYNCBUSY_WINCTRL_Pos)
#define SDADC_SYNCBUSY_WINLT_Pos    5            /**< \brief (SDADC_SYNCBUSY) WINLT Synchronization Busy */
#define SDADC_SYNCBUSY_WINLT        (_U_(0x1) << SDADC_SYNCBUSY_WINLT_Pos)
#define SDADC_SYNCBUSY_WINUT_Pos    6            /**< \brief (SDADC_SYNCBUSY) WINUT Synchronization Busy */
#define SDADC_SYNCBUSY_WINUT        (_U_(0x1) << SDADC_SYNCBUSY_WINUT_Pos)
#define SDADC_SYNCBUSY_OFFSETCORR_Pos 7            /**< \brief (SDADC_SYNCBUSY) OFFSETCTRL Synchronization Busy */
#define SDADC_SYNCBUSY_OFFSETCORR   (_U_(0x1) << SDADC_SYNCBUSY_OFFSETCORR_Pos)
#define SDADC_SYNCBUSY_GAINCORR_Pos 8            /**< \brief (SDADC_SYNCBUSY) GAINCORR Synchronization Busy */
#define SDADC_SYNCBUSY_GAINCORR     (_U_(0x1) << SDADC_SYNCBUSY_GAINCORR_Pos)
#define SDADC_SYNCBUSY_SHIFTCORR_Pos 9            /**< \brief (SDADC_SYNCBUSY) SHIFTCORR Synchronization Busy */
#define SDADC_SYNCBUSY_SHIFTCORR    (_U_(0x1) << SDADC_SYNCBUSY_SHIFTCORR_Pos)
#define SDADC_SYNCBUSY_SWTRIG_Pos   10           /**< \brief (SDADC_SYNCBUSY) SWTRG Synchronization Busy */
#define SDADC_SYNCBUSY_SWTRIG       (_U_(0x1) << SDADC_SYNCBUSY_SWTRIG_Pos)
#define SDADC_SYNCBUSY_ANACTRL_Pos  11           /**< \brief (SDADC_SYNCBUSY) ANACTRL Synchronization Busy */
#define SDADC_SYNCBUSY_ANACTRL      (_U_(0x1) << SDADC_SYNCBUSY_ANACTRL_Pos)
#define SDADC_SYNCBUSY_MASK         _U_(0x00000FFF) /**< \brief (SDADC_SYNCBUSY) MASK Register */

/* -------- SDADC_RESULT : (SDADC Offset: 0x24) (R/  32) Result -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t RESULT:24;        /*!< bit:  0..23  Result Value                       */
    uint32_t RESERVED:8;       /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SDADC_RESULT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_RESULT_OFFSET         0x24         /**< \brief (SDADC_RESULT offset) Result */
#define SDADC_RESULT_RESETVALUE     _U_(0x00000000) /**< \brief (SDADC_RESULT reset_value) Result */

#define SDADC_RESULT_RESULT_Pos     0            /**< \brief (SDADC_RESULT) Result Value */
#define SDADC_RESULT_RESULT_Msk     (_U_(0xFFFFFF) << SDADC_RESULT_RESULT_Pos)
#define SDADC_RESULT_RESULT(value)  (SDADC_RESULT_RESULT_Msk & ((value) << SDADC_RESULT_RESULT_Pos))
#define SDADC_RESULT_RESERVED_Pos   24           /**< \brief (SDADC_RESULT) Reserved */
#define SDADC_RESULT_RESERVED_Msk   (_U_(0xFF) << SDADC_RESULT_RESERVED_Pos)
#define SDADC_RESULT_RESERVED(value) (SDADC_RESULT_RESERVED_Msk & ((value) << SDADC_RESULT_RESERVED_Pos))
#define SDADC_RESULT_MASK           _U_(0xFFFFFFFF) /**< \brief (SDADC_RESULT) MASK Register */

/* -------- SDADC_SEQCTRL : (SDADC Offset: 0x28) (R/W  8) Sequence Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SEQEN:3;          /*!< bit:  0.. 2  Enable Positive Input in the Sequence */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_SEQCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_SEQCTRL_OFFSET        0x28         /**< \brief (SDADC_SEQCTRL offset) Sequence Control */
#define SDADC_SEQCTRL_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_SEQCTRL reset_value) Sequence Control */

#define SDADC_SEQCTRL_SEQEN_Pos     0            /**< \brief (SDADC_SEQCTRL) Enable Positive Input in the Sequence */
#define SDADC_SEQCTRL_SEQEN_Msk     (_U_(0x7) << SDADC_SEQCTRL_SEQEN_Pos)
#define SDADC_SEQCTRL_SEQEN(value)  (SDADC_SEQCTRL_SEQEN_Msk & ((value) << SDADC_SEQCTRL_SEQEN_Pos))
#define SDADC_SEQCTRL_MASK          _U_(0x07)    /**< \brief (SDADC_SEQCTRL) MASK Register */

/* -------- SDADC_ANACTRL : (SDADC Offset: 0x2C) (R/W  8) Analog Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CTRSDADC:6;       /*!< bit:  0.. 5  SDADC Control                      */
    uint8_t  ONCHOP:1;         /*!< bit:      6  Chopper                            */
    uint8_t  BUFTEST:1;        /*!< bit:      7  BUFTEST                            */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_ANACTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_ANACTRL_OFFSET        0x2C         /**< \brief (SDADC_ANACTRL offset) Analog Control */
#define SDADC_ANACTRL_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_ANACTRL reset_value) Analog Control */

#define SDADC_ANACTRL_CTRSDADC_Pos  0            /**< \brief (SDADC_ANACTRL) SDADC Control */
#define SDADC_ANACTRL_CTRSDADC_Msk  (_U_(0x3F) << SDADC_ANACTRL_CTRSDADC_Pos)
#define SDADC_ANACTRL_CTRSDADC(value) (SDADC_ANACTRL_CTRSDADC_Msk & ((value) << SDADC_ANACTRL_CTRSDADC_Pos))
#define SDADC_ANACTRL_ONCHOP_Pos    6            /**< \brief (SDADC_ANACTRL) Chopper */
#define SDADC_ANACTRL_ONCHOP        (_U_(0x1) << SDADC_ANACTRL_ONCHOP_Pos)
#define SDADC_ANACTRL_BUFTEST_Pos   7            /**< \brief (SDADC_ANACTRL) BUFTEST */
#define SDADC_ANACTRL_BUFTEST       (_U_(0x1) << SDADC_ANACTRL_BUFTEST_Pos)
#define SDADC_ANACTRL_MASK          _U_(0xFF)    /**< \brief (SDADC_ANACTRL) MASK Register */

/* -------- SDADC_DBGCTRL : (SDADC Offset: 0x2E) (R/W  8) Debug Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGRUN:1;         /*!< bit:      0  Debug Run                          */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SDADC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SDADC_DBGCTRL_OFFSET        0x2E         /**< \brief (SDADC_DBGCTRL offset) Debug Control */
#define SDADC_DBGCTRL_RESETVALUE    _U_(0x00)    /**< \brief (SDADC_DBGCTRL reset_value) Debug Control */

#define SDADC_DBGCTRL_DBGRUN_Pos    0            /**< \brief (SDADC_DBGCTRL) Debug Run */
#define SDADC_DBGCTRL_DBGRUN        (_U_(0x1) << SDADC_DBGCTRL_DBGRUN_Pos)
#define SDADC_DBGCTRL_MASK          _U_(0x01)    /**< \brief (SDADC_DBGCTRL) MASK Register */

/** \brief SDADC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO SDADC_CTRLA_Type          CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A */
  __IO SDADC_REFCTRL_Type        REFCTRL;     /**< \brief Offset: 0x01 (R/W  8) Reference Control */
  __IO SDADC_CTRLB_Type          CTRLB;       /**< \brief Offset: 0x02 (R/W 16) Control B */
  __IO SDADC_EVCTRL_Type         EVCTRL;      /**< \brief Offset: 0x04 (R/W  8) Event Control */
  __IO SDADC_INTENCLR_Type       INTENCLR;    /**< \brief Offset: 0x05 (R/W  8) Interrupt Enable Clear */
  __IO SDADC_INTENSET_Type       INTENSET;    /**< \brief Offset: 0x06 (R/W  8) Interrupt Enable Set */
  __IO SDADC_INTFLAG_Type        INTFLAG;     /**< \brief Offset: 0x07 (R/W  8) Interrupt Flag Status and Clear */
  __I  SDADC_SEQSTATUS_Type      SEQSTATUS;   /**< \brief Offset: 0x08 (R/   8) Sequence Status */
  __IO SDADC_INPUTCTRL_Type      INPUTCTRL;   /**< \brief Offset: 0x09 (R/W  8) Input Control */
  __IO SDADC_CTRLC_Type          CTRLC;       /**< \brief Offset: 0x0A (R/W  8) Control C */
  __IO SDADC_WINCTRL_Type        WINCTRL;     /**< \brief Offset: 0x0B (R/W  8) Window Monitor Control */
  __IO SDADC_WINLT_Type          WINLT;       /**< \brief Offset: 0x0C (R/W 32) Window Monitor Lower Threshold */
  __IO SDADC_WINUT_Type          WINUT;       /**< \brief Offset: 0x10 (R/W 32) Window Monitor Upper Threshold */
  __IO SDADC_OFFSETCORR_Type     OFFSETCORR;  /**< \brief Offset: 0x14 (R/W 32) Offset Correction */
  __IO SDADC_GAINCORR_Type       GAINCORR;    /**< \brief Offset: 0x18 (R/W 16) Gain Correction */
  __IO SDADC_SHIFTCORR_Type      SHIFTCORR;   /**< \brief Offset: 0x1A (R/W  8) Shift Correction */
       RoReg8                    Reserved1[0x1];
  __IO SDADC_SWTRIG_Type         SWTRIG;      /**< \brief Offset: 0x1C (R/W  8) Software Trigger */
       RoReg8                    Reserved2[0x3];
  __I  SDADC_SYNCBUSY_Type       SYNCBUSY;    /**< \brief Offset: 0x20 (R/  32) Synchronization Busy */
  __I  SDADC_RESULT_Type         RESULT;      /**< \brief Offset: 0x24 (R/  32) Result */
  __IO SDADC_SEQCTRL_Type        SEQCTRL;     /**< \brief Offset: 0x28 (R/W  8) Sequence Control */
       RoReg8                    Reserved3[0x3];
  __IO SDADC_ANACTRL_Type        ANACTRL;     /**< \brief Offset: 0x2C (R/W  8) Analog Control */
       RoReg8                    Reserved4[0x1];
  __IO SDADC_DBGCTRL_Type        DBGCTRL;     /**< \brief Offset: 0x2E (R/W  8) Debug Control */
} Sdadc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_SDADC_COMPONENT_ */
