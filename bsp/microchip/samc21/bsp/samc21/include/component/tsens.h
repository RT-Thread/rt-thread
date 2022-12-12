/**
 * \file
 *
 * \brief Component description for TSENS
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

#ifndef _SAMC21_TSENS_COMPONENT_
#define _SAMC21_TSENS_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR TSENS */
/* ========================================================================== */
/** \addtogroup SAMC21_TSENS Temperature Sensor */
/*@{*/

#define TSENS_U2261
#define REV_TSENS                   0x101

/* -------- TSENS_CTRLA : (TSENS Offset: 0x00) (R/W  8) Control A Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :4;               /*!< bit:  2.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint8_t  :1;               /*!< bit:      7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_CTRLA_OFFSET          0x00         /**< \brief (TSENS_CTRLA offset) Control A Register */
#define TSENS_CTRLA_RESETVALUE      _U_(0x00)    /**< \brief (TSENS_CTRLA reset_value) Control A Register */

#define TSENS_CTRLA_SWRST_Pos       0            /**< \brief (TSENS_CTRLA) Software Reset */
#define TSENS_CTRLA_SWRST           (_U_(0x1) << TSENS_CTRLA_SWRST_Pos)
#define TSENS_CTRLA_ENABLE_Pos      1            /**< \brief (TSENS_CTRLA) Enable */
#define TSENS_CTRLA_ENABLE          (_U_(0x1) << TSENS_CTRLA_ENABLE_Pos)
#define TSENS_CTRLA_RUNSTDBY_Pos    6            /**< \brief (TSENS_CTRLA) Run in Standby */
#define TSENS_CTRLA_RUNSTDBY        (_U_(0x1) << TSENS_CTRLA_RUNSTDBY_Pos)
#define TSENS_CTRLA_MASK            _U_(0x43)    /**< \brief (TSENS_CTRLA) MASK Register */

/* -------- TSENS_CTRLB : (TSENS Offset: 0x01) ( /W  8) Control B Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  START:1;          /*!< bit:      0  Start Measurement                  */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_CTRLB_OFFSET          0x01         /**< \brief (TSENS_CTRLB offset) Control B Register */
#define TSENS_CTRLB_RESETVALUE      _U_(0x00)    /**< \brief (TSENS_CTRLB reset_value) Control B Register */

#define TSENS_CTRLB_START_Pos       0            /**< \brief (TSENS_CTRLB) Start Measurement */
#define TSENS_CTRLB_START           (_U_(0x1) << TSENS_CTRLB_START_Pos)
#define TSENS_CTRLB_MASK            _U_(0x01)    /**< \brief (TSENS_CTRLB) MASK Register */

/* -------- TSENS_CTRLC : (TSENS Offset: 0x02) (R/W  8) Control C Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  WINMODE:3;        /*!< bit:  0.. 2  Window Monitor Mode                */
    uint8_t  :1;               /*!< bit:      3  Reserved                           */
    uint8_t  FREERUN:1;        /*!< bit:      4  Free Running Measurement           */
    uint8_t  :3;               /*!< bit:  5.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_CTRLC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_CTRLC_OFFSET          0x02         /**< \brief (TSENS_CTRLC offset) Control C Register */
#define TSENS_CTRLC_RESETVALUE      _U_(0x00)    /**< \brief (TSENS_CTRLC reset_value) Control C Register */

#define TSENS_CTRLC_WINMODE_Pos     0            /**< \brief (TSENS_CTRLC) Window Monitor Mode */
#define TSENS_CTRLC_WINMODE_Msk     (_U_(0x7) << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE(value)  (TSENS_CTRLC_WINMODE_Msk & ((value) << TSENS_CTRLC_WINMODE_Pos))
#define   TSENS_CTRLC_WINMODE_DISABLE_Val _U_(0x0)   /**< \brief (TSENS_CTRLC) No window mode (default) */
#define   TSENS_CTRLC_WINMODE_ABOVE_Val   _U_(0x1)   /**< \brief (TSENS_CTRLC) VALUE greater than WINLT */
#define   TSENS_CTRLC_WINMODE_BELOW_Val   _U_(0x2)   /**< \brief (TSENS_CTRLC) VALUE less than WINUT */
#define   TSENS_CTRLC_WINMODE_INSIDE_Val  _U_(0x3)   /**< \brief (TSENS_CTRLC) VALUE greater than WINLT and VALUE less than WINUT */
#define   TSENS_CTRLC_WINMODE_OUTSIDE_Val _U_(0x4)   /**< \brief (TSENS_CTRLC) VALUE less than WINLT or VALUE greater than WINUT */
#define   TSENS_CTRLC_WINMODE_HYST_ABOVE_Val _U_(0x5)   /**< \brief (TSENS_CTRLC) VALUE greater than WINUT with hysteresis to WINLT */
#define   TSENS_CTRLC_WINMODE_HYST_BELOW_Val _U_(0x6)   /**< \brief (TSENS_CTRLC) VALUE less than WINLST with hysteresis to WINUT */
#define TSENS_CTRLC_WINMODE_DISABLE (TSENS_CTRLC_WINMODE_DISABLE_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_ABOVE   (TSENS_CTRLC_WINMODE_ABOVE_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_BELOW   (TSENS_CTRLC_WINMODE_BELOW_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_INSIDE  (TSENS_CTRLC_WINMODE_INSIDE_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_OUTSIDE (TSENS_CTRLC_WINMODE_OUTSIDE_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_HYST_ABOVE (TSENS_CTRLC_WINMODE_HYST_ABOVE_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_WINMODE_HYST_BELOW (TSENS_CTRLC_WINMODE_HYST_BELOW_Val << TSENS_CTRLC_WINMODE_Pos)
#define TSENS_CTRLC_FREERUN_Pos     4            /**< \brief (TSENS_CTRLC) Free Running Measurement */
#define TSENS_CTRLC_FREERUN         (_U_(0x1) << TSENS_CTRLC_FREERUN_Pos)
#define TSENS_CTRLC_MASK            _U_(0x17)    /**< \brief (TSENS_CTRLC) MASK Register */

/* -------- TSENS_EVCTRL : (TSENS Offset: 0x03) (R/W  8) Event Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  STARTEI:1;        /*!< bit:      0  Start Conversion Event Input Enable */
    uint8_t  STARTINV:1;       /*!< bit:      1  Start Conversion Event Invert Enable */
    uint8_t  WINEO:1;          /*!< bit:      2  Window Monitor Event Out           */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_EVCTRL_OFFSET         0x03         /**< \brief (TSENS_EVCTRL offset) Event Control Register */
#define TSENS_EVCTRL_RESETVALUE     _U_(0x00)    /**< \brief (TSENS_EVCTRL reset_value) Event Control Register */

#define TSENS_EVCTRL_STARTEI_Pos    0            /**< \brief (TSENS_EVCTRL) Start Conversion Event Input Enable */
#define TSENS_EVCTRL_STARTEI        (_U_(0x1) << TSENS_EVCTRL_STARTEI_Pos)
#define TSENS_EVCTRL_STARTINV_Pos   1            /**< \brief (TSENS_EVCTRL) Start Conversion Event Invert Enable */
#define TSENS_EVCTRL_STARTINV       (_U_(0x1) << TSENS_EVCTRL_STARTINV_Pos)
#define TSENS_EVCTRL_WINEO_Pos      2            /**< \brief (TSENS_EVCTRL) Window Monitor Event Out */
#define TSENS_EVCTRL_WINEO          (_U_(0x1) << TSENS_EVCTRL_WINEO_Pos)
#define TSENS_EVCTRL_MASK           _U_(0x07)    /**< \brief (TSENS_EVCTRL) MASK Register */

/* -------- TSENS_INTENCLR : (TSENS Offset: 0x04) (R/W  8) Interrupt Enable Clear Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Enable      */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Enable           */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Enable    */
    uint8_t  OVF:1;            /*!< bit:      3  Overflow Interrupt Enable          */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_INTENCLR_OFFSET       0x04         /**< \brief (TSENS_INTENCLR offset) Interrupt Enable Clear Register */
#define TSENS_INTENCLR_RESETVALUE   _U_(0x00)    /**< \brief (TSENS_INTENCLR reset_value) Interrupt Enable Clear Register */

#define TSENS_INTENCLR_RESRDY_Pos   0            /**< \brief (TSENS_INTENCLR) Result Ready Interrupt Enable */
#define TSENS_INTENCLR_RESRDY       (_U_(0x1) << TSENS_INTENCLR_RESRDY_Pos)
#define TSENS_INTENCLR_OVERRUN_Pos  1            /**< \brief (TSENS_INTENCLR) Overrun Interrupt Enable */
#define TSENS_INTENCLR_OVERRUN      (_U_(0x1) << TSENS_INTENCLR_OVERRUN_Pos)
#define TSENS_INTENCLR_WINMON_Pos   2            /**< \brief (TSENS_INTENCLR) Window Monitor Interrupt Enable */
#define TSENS_INTENCLR_WINMON       (_U_(0x1) << TSENS_INTENCLR_WINMON_Pos)
#define TSENS_INTENCLR_OVF_Pos      3            /**< \brief (TSENS_INTENCLR) Overflow Interrupt Enable */
#define TSENS_INTENCLR_OVF          (_U_(0x1) << TSENS_INTENCLR_OVF_Pos)
#define TSENS_INTENCLR_MASK         _U_(0x0F)    /**< \brief (TSENS_INTENCLR) MASK Register */

/* -------- TSENS_INTENSET : (TSENS Offset: 0x05) (R/W  8) Interrupt Enable Set Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready Interrupt Enable      */
    uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun Interrupt Enable           */
    uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor Interrupt Enable    */
    uint8_t  OVF:1;            /*!< bit:      3  Overflow Interrupt Enable          */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_INTENSET_OFFSET       0x05         /**< \brief (TSENS_INTENSET offset) Interrupt Enable Set Register */
#define TSENS_INTENSET_RESETVALUE   _U_(0x00)    /**< \brief (TSENS_INTENSET reset_value) Interrupt Enable Set Register */

#define TSENS_INTENSET_RESRDY_Pos   0            /**< \brief (TSENS_INTENSET) Result Ready Interrupt Enable */
#define TSENS_INTENSET_RESRDY       (_U_(0x1) << TSENS_INTENSET_RESRDY_Pos)
#define TSENS_INTENSET_OVERRUN_Pos  1            /**< \brief (TSENS_INTENSET) Overrun Interrupt Enable */
#define TSENS_INTENSET_OVERRUN      (_U_(0x1) << TSENS_INTENSET_OVERRUN_Pos)
#define TSENS_INTENSET_WINMON_Pos   2            /**< \brief (TSENS_INTENSET) Window Monitor Interrupt Enable */
#define TSENS_INTENSET_WINMON       (_U_(0x1) << TSENS_INTENSET_WINMON_Pos)
#define TSENS_INTENSET_OVF_Pos      3            /**< \brief (TSENS_INTENSET) Overflow Interrupt Enable */
#define TSENS_INTENSET_OVF          (_U_(0x1) << TSENS_INTENSET_OVF_Pos)
#define TSENS_INTENSET_MASK         _U_(0x0F)    /**< \brief (TSENS_INTENSET) MASK Register */

/* -------- TSENS_INTFLAG : (TSENS Offset: 0x06) (R/W  8) Interrupt Flag Status and Clear Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  RESRDY:1;         /*!< bit:      0  Result Ready                       */
    __I uint8_t  OVERRUN:1;        /*!< bit:      1  Overrun                            */
    __I uint8_t  WINMON:1;         /*!< bit:      2  Window Monitor                     */
    __I uint8_t  OVF:1;            /*!< bit:      3  Overflow                           */
    __I uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_INTFLAG_OFFSET        0x06         /**< \brief (TSENS_INTFLAG offset) Interrupt Flag Status and Clear Register */
#define TSENS_INTFLAG_RESETVALUE    _U_(0x00)    /**< \brief (TSENS_INTFLAG reset_value) Interrupt Flag Status and Clear Register */

#define TSENS_INTFLAG_RESRDY_Pos    0            /**< \brief (TSENS_INTFLAG) Result Ready */
#define TSENS_INTFLAG_RESRDY        (_U_(0x1) << TSENS_INTFLAG_RESRDY_Pos)
#define TSENS_INTFLAG_OVERRUN_Pos   1            /**< \brief (TSENS_INTFLAG) Overrun */
#define TSENS_INTFLAG_OVERRUN       (_U_(0x1) << TSENS_INTFLAG_OVERRUN_Pos)
#define TSENS_INTFLAG_WINMON_Pos    2            /**< \brief (TSENS_INTFLAG) Window Monitor */
#define TSENS_INTFLAG_WINMON        (_U_(0x1) << TSENS_INTFLAG_WINMON_Pos)
#define TSENS_INTFLAG_OVF_Pos       3            /**< \brief (TSENS_INTFLAG) Overflow */
#define TSENS_INTFLAG_OVF           (_U_(0x1) << TSENS_INTFLAG_OVF_Pos)
#define TSENS_INTFLAG_MASK          _U_(0x0F)    /**< \brief (TSENS_INTFLAG) MASK Register */

/* -------- TSENS_STATUS : (TSENS Offset: 0x07) (R/   8) Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  OVF:1;            /*!< bit:      0  Result Overflow                    */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_STATUS_OFFSET         0x07         /**< \brief (TSENS_STATUS offset) Status Register */
#define TSENS_STATUS_RESETVALUE     _U_(0x00)    /**< \brief (TSENS_STATUS reset_value) Status Register */

#define TSENS_STATUS_OVF_Pos        0            /**< \brief (TSENS_STATUS) Result Overflow */
#define TSENS_STATUS_OVF            (_U_(0x1) << TSENS_STATUS_OVF_Pos)
#define TSENS_STATUS_MASK           _U_(0x01)    /**< \brief (TSENS_STATUS) MASK Register */

/* -------- TSENS_SYNCBUSY : (TSENS Offset: 0x08) (R/  32) Synchronization Busy Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Busy                */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable Busy                        */
    uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_SYNCBUSY_OFFSET       0x08         /**< \brief (TSENS_SYNCBUSY offset) Synchronization Busy Register */
#define TSENS_SYNCBUSY_RESETVALUE   _U_(0x00000000) /**< \brief (TSENS_SYNCBUSY reset_value) Synchronization Busy Register */

#define TSENS_SYNCBUSY_SWRST_Pos    0            /**< \brief (TSENS_SYNCBUSY) Software Reset Busy */
#define TSENS_SYNCBUSY_SWRST        (_U_(0x1) << TSENS_SYNCBUSY_SWRST_Pos)
#define TSENS_SYNCBUSY_ENABLE_Pos   1            /**< \brief (TSENS_SYNCBUSY) Enable Busy */
#define TSENS_SYNCBUSY_ENABLE       (_U_(0x1) << TSENS_SYNCBUSY_ENABLE_Pos)
#define TSENS_SYNCBUSY_MASK         _U_(0x00000003) /**< \brief (TSENS_SYNCBUSY) MASK Register */

/* -------- TSENS_VALUE : (TSENS Offset: 0x0C) (R/  32) Value Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t VALUE:24;         /*!< bit:  0..23  Measurement Value                  */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_VALUE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_VALUE_OFFSET          0x0C         /**< \brief (TSENS_VALUE offset) Value Register */
#define TSENS_VALUE_RESETVALUE      _U_(0x00000000) /**< \brief (TSENS_VALUE reset_value) Value Register */

#define TSENS_VALUE_VALUE_Pos       0            /**< \brief (TSENS_VALUE) Measurement Value */
#define TSENS_VALUE_VALUE_Msk       (_U_(0xFFFFFF) << TSENS_VALUE_VALUE_Pos)
#define TSENS_VALUE_VALUE(value)    (TSENS_VALUE_VALUE_Msk & ((value) << TSENS_VALUE_VALUE_Pos))
#define TSENS_VALUE_MASK            _U_(0x00FFFFFF) /**< \brief (TSENS_VALUE) MASK Register */

/* -------- TSENS_WINLT : (TSENS Offset: 0x10) (R/W 32) Window Monitor Lower Threshold Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t WINLT:24;         /*!< bit:  0..23  Window Lower Threshold             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_WINLT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_WINLT_OFFSET          0x10         /**< \brief (TSENS_WINLT offset) Window Monitor Lower Threshold Register */
#define TSENS_WINLT_RESETVALUE      _U_(0x00000000) /**< \brief (TSENS_WINLT reset_value) Window Monitor Lower Threshold Register */

#define TSENS_WINLT_WINLT_Pos       0            /**< \brief (TSENS_WINLT) Window Lower Threshold */
#define TSENS_WINLT_WINLT_Msk       (_U_(0xFFFFFF) << TSENS_WINLT_WINLT_Pos)
#define TSENS_WINLT_WINLT(value)    (TSENS_WINLT_WINLT_Msk & ((value) << TSENS_WINLT_WINLT_Pos))
#define TSENS_WINLT_MASK            _U_(0x00FFFFFF) /**< \brief (TSENS_WINLT) MASK Register */

/* -------- TSENS_WINUT : (TSENS Offset: 0x14) (R/W 32) Window Monitor Upper Threshold Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t WINUT:24;         /*!< bit:  0..23  Window Upper Threshold             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_WINUT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_WINUT_OFFSET          0x14         /**< \brief (TSENS_WINUT offset) Window Monitor Upper Threshold Register */
#define TSENS_WINUT_RESETVALUE      _U_(0x00000000) /**< \brief (TSENS_WINUT reset_value) Window Monitor Upper Threshold Register */

#define TSENS_WINUT_WINUT_Pos       0            /**< \brief (TSENS_WINUT) Window Upper Threshold */
#define TSENS_WINUT_WINUT_Msk       (_U_(0xFFFFFF) << TSENS_WINUT_WINUT_Pos)
#define TSENS_WINUT_WINUT(value)    (TSENS_WINUT_WINUT_Msk & ((value) << TSENS_WINUT_WINUT_Pos))
#define TSENS_WINUT_MASK            _U_(0x00FFFFFF) /**< \brief (TSENS_WINUT) MASK Register */

/* -------- TSENS_GAIN : (TSENS Offset: 0x18) (R/W 32) Gain Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t GAIN:24;          /*!< bit:  0..23  Time Amplifier Gain                */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_GAIN_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_GAIN_OFFSET           0x18         /**< \brief (TSENS_GAIN offset) Gain Register */
#define TSENS_GAIN_RESETVALUE       _U_(0x00000000) /**< \brief (TSENS_GAIN reset_value) Gain Register */

#define TSENS_GAIN_GAIN_Pos         0            /**< \brief (TSENS_GAIN) Time Amplifier Gain */
#define TSENS_GAIN_GAIN_Msk         (_U_(0xFFFFFF) << TSENS_GAIN_GAIN_Pos)
#define TSENS_GAIN_GAIN(value)      (TSENS_GAIN_GAIN_Msk & ((value) << TSENS_GAIN_GAIN_Pos))
#define TSENS_GAIN_MASK             _U_(0x00FFFFFF) /**< \brief (TSENS_GAIN) MASK Register */

/* -------- TSENS_OFFSET : (TSENS Offset: 0x1C) (R/W 32) Offset Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t OFFSETC:24;       /*!< bit:  0..23  Offset Correction                  */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_OFFSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_OFFSET_OFFSET         0x1C         /**< \brief (TSENS_OFFSET offset) Offset Register */
#define TSENS_OFFSET_RESETVALUE     _U_(0x00000000) /**< \brief (TSENS_OFFSET reset_value) Offset Register */

#define TSENS_OFFSET_OFFSETC_Pos    0            /**< \brief (TSENS_OFFSET) Offset Correction */
#define TSENS_OFFSET_OFFSETC_Msk    (_U_(0xFFFFFF) << TSENS_OFFSET_OFFSETC_Pos)
#define TSENS_OFFSET_OFFSETC(value) (TSENS_OFFSET_OFFSETC_Msk & ((value) << TSENS_OFFSET_OFFSETC_Pos))
#define TSENS_OFFSET_MASK           _U_(0x00FFFFFF) /**< \brief (TSENS_OFFSET) MASK Register */

/* -------- TSENS_CAL : (TSENS Offset: 0x20) (R/W 32) Calibration Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t FCAL:6;           /*!< bit:  0.. 5  Frequency Calibration              */
    uint32_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint32_t TCAL:6;           /*!< bit:  8..13  Temperature Calibration            */
    uint32_t :18;              /*!< bit: 14..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TSENS_CAL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_CAL_OFFSET            0x20         /**< \brief (TSENS_CAL offset) Calibration Register */
#define TSENS_CAL_RESETVALUE        _U_(0x00000000) /**< \brief (TSENS_CAL reset_value) Calibration Register */

#define TSENS_CAL_FCAL_Pos          0            /**< \brief (TSENS_CAL) Frequency Calibration */
#define TSENS_CAL_FCAL_Msk          (_U_(0x3F) << TSENS_CAL_FCAL_Pos)
#define TSENS_CAL_FCAL(value)       (TSENS_CAL_FCAL_Msk & ((value) << TSENS_CAL_FCAL_Pos))
#define TSENS_CAL_TCAL_Pos          8            /**< \brief (TSENS_CAL) Temperature Calibration */
#define TSENS_CAL_TCAL_Msk          (_U_(0x3F) << TSENS_CAL_TCAL_Pos)
#define TSENS_CAL_TCAL(value)       (TSENS_CAL_TCAL_Msk & ((value) << TSENS_CAL_TCAL_Pos))
#define TSENS_CAL_MASK              _U_(0x00003F3F) /**< \brief (TSENS_CAL) MASK Register */

/* -------- TSENS_DBGCTRL : (TSENS Offset: 0x24) (R/W  8) Debug Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGRUN:1;         /*!< bit:      0  Debug Run                          */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TSENS_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TSENS_DBGCTRL_OFFSET        0x24         /**< \brief (TSENS_DBGCTRL offset) Debug Control Register */
#define TSENS_DBGCTRL_RESETVALUE    _U_(0x00)    /**< \brief (TSENS_DBGCTRL reset_value) Debug Control Register */

#define TSENS_DBGCTRL_DBGRUN_Pos    0            /**< \brief (TSENS_DBGCTRL) Debug Run */
#define TSENS_DBGCTRL_DBGRUN        (_U_(0x1) << TSENS_DBGCTRL_DBGRUN_Pos)
#define TSENS_DBGCTRL_MASK          _U_(0x01)    /**< \brief (TSENS_DBGCTRL) MASK Register */

/** \brief TSENS hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO TSENS_CTRLA_Type          CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A Register */
  __O  TSENS_CTRLB_Type          CTRLB;       /**< \brief Offset: 0x01 ( /W  8) Control B Register */
  __IO TSENS_CTRLC_Type          CTRLC;       /**< \brief Offset: 0x02 (R/W  8) Control C Register */
  __IO TSENS_EVCTRL_Type         EVCTRL;      /**< \brief Offset: 0x03 (R/W  8) Event Control Register */
  __IO TSENS_INTENCLR_Type       INTENCLR;    /**< \brief Offset: 0x04 (R/W  8) Interrupt Enable Clear Register */
  __IO TSENS_INTENSET_Type       INTENSET;    /**< \brief Offset: 0x05 (R/W  8) Interrupt Enable Set Register */
  __IO TSENS_INTFLAG_Type        INTFLAG;     /**< \brief Offset: 0x06 (R/W  8) Interrupt Flag Status and Clear Register */
  __I  TSENS_STATUS_Type         STATUS;      /**< \brief Offset: 0x07 (R/   8) Status Register */
  __I  TSENS_SYNCBUSY_Type       SYNCBUSY;    /**< \brief Offset: 0x08 (R/  32) Synchronization Busy Register */
  __I  TSENS_VALUE_Type          VALUE;       /**< \brief Offset: 0x0C (R/  32) Value Register */
  __IO TSENS_WINLT_Type          WINLT;       /**< \brief Offset: 0x10 (R/W 32) Window Monitor Lower Threshold Register */
  __IO TSENS_WINUT_Type          WINUT;       /**< \brief Offset: 0x14 (R/W 32) Window Monitor Upper Threshold Register */
  __IO TSENS_GAIN_Type           GAIN;        /**< \brief Offset: 0x18 (R/W 32) Gain Register */
  __IO TSENS_OFFSET_Type         OFFSET;      /**< \brief Offset: 0x1C (R/W 32) Offset Register */
  __IO TSENS_CAL_Type            CAL;         /**< \brief Offset: 0x20 (R/W 32) Calibration Register */
  __IO TSENS_DBGCTRL_Type        DBGCTRL;     /**< \brief Offset: 0x24 (R/W  8) Debug Control Register */
} Tsens;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_TSENS_COMPONENT_ */
