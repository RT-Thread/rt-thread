/**
 * \file
 *
 * \brief Component description for OSCCTRL
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

#ifndef _SAMC21_OSCCTRL_COMPONENT_
#define _SAMC21_OSCCTRL_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR OSCCTRL */
/* ========================================================================== */
/** \addtogroup SAMC21_OSCCTRL Oscillators Control */
/*@{*/

#define OSCCTRL_U2119
#define REV_OSCCTRL                 0x210

/* -------- OSCCTRL_INTENCLR : (OSCCTRL Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready Interrupt Enable        */
    uint32_t XOSCFAIL:1;       /*!< bit:      1  XOSC Clock Failure Detector Interrupt Enable */
    uint32_t :2;               /*!< bit:  2.. 3  Reserved                           */
    uint32_t OSC48MRDY:1;      /*!< bit:      4  OSC48M Ready Interrupt Enable      */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:      8  DPLL Lock Rise Interrupt Enable    */
    uint32_t DPLLLCKF:1;       /*!< bit:      9  DPLL Lock Fall Interrupt Enable    */
    uint32_t DPLLLTO:1;        /*!< bit:     10  DPLL Time Out Interrupt Enable     */
    uint32_t DPLLLDRTO:1;      /*!< bit:     11  DPLL Ratio Ready Interrupt Enable  */
    uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTENCLR_OFFSET     0x00         /**< \brief (OSCCTRL_INTENCLR offset) Interrupt Enable Clear */
#define OSCCTRL_INTENCLR_RESETVALUE _U_(0x00000000) /**< \brief (OSCCTRL_INTENCLR reset_value) Interrupt Enable Clear */

#define OSCCTRL_INTENCLR_XOSCRDY_Pos 0            /**< \brief (OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable */
#define OSCCTRL_INTENCLR_XOSCRDY    (_U_(0x1) << OSCCTRL_INTENCLR_XOSCRDY_Pos)
#define OSCCTRL_INTENCLR_XOSCFAIL_Pos 1            /**< \brief (OSCCTRL_INTENCLR) XOSC Clock Failure Detector Interrupt Enable */
#define OSCCTRL_INTENCLR_XOSCFAIL   (_U_(0x1) << OSCCTRL_INTENCLR_XOSCFAIL_Pos)
#define OSCCTRL_INTENCLR_OSC48MRDY_Pos 4            /**< \brief (OSCCTRL_INTENCLR) OSC48M Ready Interrupt Enable */
#define OSCCTRL_INTENCLR_OSC48MRDY  (_U_(0x1) << OSCCTRL_INTENCLR_OSC48MRDY_Pos)
#define OSCCTRL_INTENCLR_DPLLLCKR_Pos 8            /**< \brief (OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable */
#define OSCCTRL_INTENCLR_DPLLLCKR   (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKR_Pos)
#define OSCCTRL_INTENCLR_DPLLLCKF_Pos 9            /**< \brief (OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable */
#define OSCCTRL_INTENCLR_DPLLLCKF   (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKF_Pos)
#define OSCCTRL_INTENCLR_DPLLLTO_Pos 10           /**< \brief (OSCCTRL_INTENCLR) DPLL Time Out Interrupt Enable */
#define OSCCTRL_INTENCLR_DPLLLTO    (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLTO_Pos)
#define OSCCTRL_INTENCLR_DPLLLDRTO_Pos 11           /**< \brief (OSCCTRL_INTENCLR) DPLL Ratio Ready Interrupt Enable */
#define OSCCTRL_INTENCLR_DPLLLDRTO  (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLDRTO_Pos)
#define OSCCTRL_INTENCLR_MASK       _U_(0x00000F13) /**< \brief (OSCCTRL_INTENCLR) MASK Register */

/* -------- OSCCTRL_INTENSET : (OSCCTRL Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready Interrupt Enable        */
    uint32_t XOSCFAIL:1;       /*!< bit:      1  XOSC Clock Failure Detector Interrupt Enable */
    uint32_t :2;               /*!< bit:  2.. 3  Reserved                           */
    uint32_t OSC48MRDY:1;      /*!< bit:      4  OSC48M Ready Interrupt Enable      */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:      8  DPLL Lock Rise Interrupt Enable    */
    uint32_t DPLLLCKF:1;       /*!< bit:      9  DPLL Lock Fall Interrupt Enable    */
    uint32_t DPLLLTO:1;        /*!< bit:     10  DPLL Time Out Interrupt Enable     */
    uint32_t DPLLLDRTO:1;      /*!< bit:     11  DPLL Ratio Ready Interrupt Enable  */
    uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTENSET_OFFSET     0x04         /**< \brief (OSCCTRL_INTENSET offset) Interrupt Enable Set */
#define OSCCTRL_INTENSET_RESETVALUE _U_(0x00000000) /**< \brief (OSCCTRL_INTENSET reset_value) Interrupt Enable Set */

#define OSCCTRL_INTENSET_XOSCRDY_Pos 0            /**< \brief (OSCCTRL_INTENSET) XOSC Ready Interrupt Enable */
#define OSCCTRL_INTENSET_XOSCRDY    (_U_(0x1) << OSCCTRL_INTENSET_XOSCRDY_Pos)
#define OSCCTRL_INTENSET_XOSCFAIL_Pos 1            /**< \brief (OSCCTRL_INTENSET) XOSC Clock Failure Detector Interrupt Enable */
#define OSCCTRL_INTENSET_XOSCFAIL   (_U_(0x1) << OSCCTRL_INTENSET_XOSCFAIL_Pos)
#define OSCCTRL_INTENSET_OSC48MRDY_Pos 4            /**< \brief (OSCCTRL_INTENSET) OSC48M Ready Interrupt Enable */
#define OSCCTRL_INTENSET_OSC48MRDY  (_U_(0x1) << OSCCTRL_INTENSET_OSC48MRDY_Pos)
#define OSCCTRL_INTENSET_DPLLLCKR_Pos 8            /**< \brief (OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable */
#define OSCCTRL_INTENSET_DPLLLCKR   (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKR_Pos)
#define OSCCTRL_INTENSET_DPLLLCKF_Pos 9            /**< \brief (OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable */
#define OSCCTRL_INTENSET_DPLLLCKF   (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKF_Pos)
#define OSCCTRL_INTENSET_DPLLLTO_Pos 10           /**< \brief (OSCCTRL_INTENSET) DPLL Time Out Interrupt Enable */
#define OSCCTRL_INTENSET_DPLLLTO    (_U_(0x1) << OSCCTRL_INTENSET_DPLLLTO_Pos)
#define OSCCTRL_INTENSET_DPLLLDRTO_Pos 11           /**< \brief (OSCCTRL_INTENSET) DPLL Ratio Ready Interrupt Enable */
#define OSCCTRL_INTENSET_DPLLLDRTO  (_U_(0x1) << OSCCTRL_INTENSET_DPLLLDRTO_Pos)
#define OSCCTRL_INTENSET_MASK       _U_(0x00000F13) /**< \brief (OSCCTRL_INTENSET) MASK Register */

/* -------- OSCCTRL_INTFLAG : (OSCCTRL Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready                         */
    __I uint32_t XOSCFAIL:1;       /*!< bit:      1  XOSC Clock Failure Detector        */
    __I uint32_t :2;               /*!< bit:  2.. 3  Reserved                           */
    __I uint32_t OSC48MRDY:1;      /*!< bit:      4  OSC48M Ready                       */
    __I uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    __I uint32_t DPLLLCKR:1;       /*!< bit:      8  DPLL Lock Rise                     */
    __I uint32_t DPLLLCKF:1;       /*!< bit:      9  DPLL Lock Fall                     */
    __I uint32_t DPLLLTO:1;        /*!< bit:     10  DPLL Timeout                       */
    __I uint32_t DPLLLDRTO:1;      /*!< bit:     11  DPLL Ratio Ready                   */
    __I uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTFLAG_OFFSET      0x08         /**< \brief (OSCCTRL_INTFLAG offset) Interrupt Flag Status and Clear */
#define OSCCTRL_INTFLAG_RESETVALUE  _U_(0x00000000) /**< \brief (OSCCTRL_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define OSCCTRL_INTFLAG_XOSCRDY_Pos 0            /**< \brief (OSCCTRL_INTFLAG) XOSC Ready */
#define OSCCTRL_INTFLAG_XOSCRDY     (_U_(0x1) << OSCCTRL_INTFLAG_XOSCRDY_Pos)
#define OSCCTRL_INTFLAG_XOSCFAIL_Pos 1            /**< \brief (OSCCTRL_INTFLAG) XOSC Clock Failure Detector */
#define OSCCTRL_INTFLAG_XOSCFAIL    (_U_(0x1) << OSCCTRL_INTFLAG_XOSCFAIL_Pos)
#define OSCCTRL_INTFLAG_OSC48MRDY_Pos 4            /**< \brief (OSCCTRL_INTFLAG) OSC48M Ready */
#define OSCCTRL_INTFLAG_OSC48MRDY   (_U_(0x1) << OSCCTRL_INTFLAG_OSC48MRDY_Pos)
#define OSCCTRL_INTFLAG_DPLLLCKR_Pos 8            /**< \brief (OSCCTRL_INTFLAG) DPLL Lock Rise */
#define OSCCTRL_INTFLAG_DPLLLCKR    (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKR_Pos)
#define OSCCTRL_INTFLAG_DPLLLCKF_Pos 9            /**< \brief (OSCCTRL_INTFLAG) DPLL Lock Fall */
#define OSCCTRL_INTFLAG_DPLLLCKF    (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKF_Pos)
#define OSCCTRL_INTFLAG_DPLLLTO_Pos 10           /**< \brief (OSCCTRL_INTFLAG) DPLL Timeout */
#define OSCCTRL_INTFLAG_DPLLLTO     (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLTO_Pos)
#define OSCCTRL_INTFLAG_DPLLLDRTO_Pos 11           /**< \brief (OSCCTRL_INTFLAG) DPLL Ratio Ready */
#define OSCCTRL_INTFLAG_DPLLLDRTO   (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLDRTO_Pos)
#define OSCCTRL_INTFLAG_MASK        _U_(0x00000F13) /**< \brief (OSCCTRL_INTFLAG) MASK Register */

/* -------- OSCCTRL_STATUS : (OSCCTRL Offset: 0x0C) (R/  32) Power and Clocks Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready                         */
    uint32_t XOSCFAIL:1;       /*!< bit:      1  XOSC Clock Failure Detector        */
    uint32_t XOSCCKSW:1;       /*!< bit:      2  XOSC Clock Switch                  */
    uint32_t :1;               /*!< bit:      3  Reserved                           */
    uint32_t OSC48MRDY:1;      /*!< bit:      4  OSC48M Ready                       */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:      8  DPLL Lock Rise                     */
    uint32_t DPLLLCKF:1;       /*!< bit:      9  DPLL Lock Fall                     */
    uint32_t DPLLTO:1;         /*!< bit:     10  DPLL Timeout                       */
    uint32_t DPLLLDRTO:1;      /*!< bit:     11  DPLL Ratio Ready                   */
    uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_STATUS_OFFSET       0x0C         /**< \brief (OSCCTRL_STATUS offset) Power and Clocks Status */
#define OSCCTRL_STATUS_RESETVALUE   _U_(0x00000000) /**< \brief (OSCCTRL_STATUS reset_value) Power and Clocks Status */

#define OSCCTRL_STATUS_XOSCRDY_Pos  0            /**< \brief (OSCCTRL_STATUS) XOSC Ready */
#define OSCCTRL_STATUS_XOSCRDY      (_U_(0x1) << OSCCTRL_STATUS_XOSCRDY_Pos)
#define OSCCTRL_STATUS_XOSCFAIL_Pos 1            /**< \brief (OSCCTRL_STATUS) XOSC Clock Failure Detector */
#define OSCCTRL_STATUS_XOSCFAIL     (_U_(0x1) << OSCCTRL_STATUS_XOSCFAIL_Pos)
#define OSCCTRL_STATUS_XOSCCKSW_Pos 2            /**< \brief (OSCCTRL_STATUS) XOSC Clock Switch */
#define OSCCTRL_STATUS_XOSCCKSW     (_U_(0x1) << OSCCTRL_STATUS_XOSCCKSW_Pos)
#define OSCCTRL_STATUS_OSC48MRDY_Pos 4            /**< \brief (OSCCTRL_STATUS) OSC48M Ready */
#define OSCCTRL_STATUS_OSC48MRDY    (_U_(0x1) << OSCCTRL_STATUS_OSC48MRDY_Pos)
#define OSCCTRL_STATUS_DPLLLCKR_Pos 8            /**< \brief (OSCCTRL_STATUS) DPLL Lock Rise */
#define OSCCTRL_STATUS_DPLLLCKR     (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKR_Pos)
#define OSCCTRL_STATUS_DPLLLCKF_Pos 9            /**< \brief (OSCCTRL_STATUS) DPLL Lock Fall */
#define OSCCTRL_STATUS_DPLLLCKF     (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKF_Pos)
#define OSCCTRL_STATUS_DPLLTO_Pos   10           /**< \brief (OSCCTRL_STATUS) DPLL Timeout */
#define OSCCTRL_STATUS_DPLLTO       (_U_(0x1) << OSCCTRL_STATUS_DPLLTO_Pos)
#define OSCCTRL_STATUS_DPLLLDRTO_Pos 11           /**< \brief (OSCCTRL_STATUS) DPLL Ratio Ready */
#define OSCCTRL_STATUS_DPLLLDRTO    (_U_(0x1) << OSCCTRL_STATUS_DPLLLDRTO_Pos)
#define OSCCTRL_STATUS_MASK         _U_(0x00000F17) /**< \brief (OSCCTRL_STATUS) MASK Register */

/* -------- OSCCTRL_XOSCCTRL : (OSCCTRL Offset: 0x10) (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t :1;               /*!< bit:      0  Reserved                           */
    uint16_t ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint16_t XTALEN:1;         /*!< bit:      2  Crystal Oscillator Enable          */
    uint16_t CFDEN:1;          /*!< bit:      3  Xosc Clock Failure Detecteor Enable */
    uint16_t SWBEN:1;          /*!< bit:      4  Xosc Clock Switch Enable           */
    uint16_t :1;               /*!< bit:      5  Reserved                           */
    uint16_t RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint16_t ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
    uint16_t GAIN:3;           /*!< bit:  8..10  Oscillator Gain                    */
    uint16_t AMPGC:1;          /*!< bit:     11  Automatic Amplitude Gain Control   */
    uint16_t STARTUP:4;        /*!< bit: 12..15  Start-Up Time                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} OSCCTRL_XOSCCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_XOSCCTRL_OFFSET     0x10         /**< \brief (OSCCTRL_XOSCCTRL offset) External Multipurpose Crystal Oscillator (XOSC) Control */
#define OSCCTRL_XOSCCTRL_RESETVALUE _U_(0x0080)  /**< \brief (OSCCTRL_XOSCCTRL reset_value) External Multipurpose Crystal Oscillator (XOSC) Control */

#define OSCCTRL_XOSCCTRL_ENABLE_Pos 1            /**< \brief (OSCCTRL_XOSCCTRL) Oscillator Enable */
#define OSCCTRL_XOSCCTRL_ENABLE     (_U_(0x1) << OSCCTRL_XOSCCTRL_ENABLE_Pos)
#define OSCCTRL_XOSCCTRL_XTALEN_Pos 2            /**< \brief (OSCCTRL_XOSCCTRL) Crystal Oscillator Enable */
#define OSCCTRL_XOSCCTRL_XTALEN     (_U_(0x1) << OSCCTRL_XOSCCTRL_XTALEN_Pos)
#define OSCCTRL_XOSCCTRL_CFDEN_Pos  3            /**< \brief (OSCCTRL_XOSCCTRL) Xosc Clock Failure Detecteor Enable */
#define OSCCTRL_XOSCCTRL_CFDEN      (_U_(0x1) << OSCCTRL_XOSCCTRL_CFDEN_Pos)
#define OSCCTRL_XOSCCTRL_SWBEN_Pos  4            /**< \brief (OSCCTRL_XOSCCTRL) Xosc Clock Switch Enable */
#define OSCCTRL_XOSCCTRL_SWBEN      (_U_(0x1) << OSCCTRL_XOSCCTRL_SWBEN_Pos)
#define OSCCTRL_XOSCCTRL_RUNSTDBY_Pos 6            /**< \brief (OSCCTRL_XOSCCTRL) Run in Standby */
#define OSCCTRL_XOSCCTRL_RUNSTDBY   (_U_(0x1) << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos)
#define OSCCTRL_XOSCCTRL_ONDEMAND_Pos 7            /**< \brief (OSCCTRL_XOSCCTRL) On Demand Control */
#define OSCCTRL_XOSCCTRL_ONDEMAND   (_U_(0x1) << OSCCTRL_XOSCCTRL_ONDEMAND_Pos)
#define OSCCTRL_XOSCCTRL_GAIN_Pos   8            /**< \brief (OSCCTRL_XOSCCTRL) Oscillator Gain */
#define OSCCTRL_XOSCCTRL_GAIN_Msk   (_U_(0x7) << OSCCTRL_XOSCCTRL_GAIN_Pos)
#define OSCCTRL_XOSCCTRL_GAIN(value) (OSCCTRL_XOSCCTRL_GAIN_Msk & ((value) << OSCCTRL_XOSCCTRL_GAIN_Pos))
#define OSCCTRL_XOSCCTRL_AMPGC_Pos  11           /**< \brief (OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control */
#define OSCCTRL_XOSCCTRL_AMPGC      (_U_(0x1) << OSCCTRL_XOSCCTRL_AMPGC_Pos)
#define OSCCTRL_XOSCCTRL_STARTUP_Pos 12           /**< \brief (OSCCTRL_XOSCCTRL) Start-Up Time */
#define OSCCTRL_XOSCCTRL_STARTUP_Msk (_U_(0xF) << OSCCTRL_XOSCCTRL_STARTUP_Pos)
#define OSCCTRL_XOSCCTRL_STARTUP(value) (OSCCTRL_XOSCCTRL_STARTUP_Msk & ((value) << OSCCTRL_XOSCCTRL_STARTUP_Pos))
#define OSCCTRL_XOSCCTRL_MASK       _U_(0xFFDE)  /**< \brief (OSCCTRL_XOSCCTRL) MASK Register */

/* -------- OSCCTRL_CFDPRESC : (OSCCTRL Offset: 0x12) (R/W  8) Clock Failure Detector Prescaler -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CFDPRESC:3;       /*!< bit:  0.. 2  Clock Failure Detector Prescaler   */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_CFDPRESC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_CFDPRESC_OFFSET     0x12         /**< \brief (OSCCTRL_CFDPRESC offset) Clock Failure Detector Prescaler */
#define OSCCTRL_CFDPRESC_RESETVALUE _U_(0x00)    /**< \brief (OSCCTRL_CFDPRESC reset_value) Clock Failure Detector Prescaler */

#define OSCCTRL_CFDPRESC_CFDPRESC_Pos 0            /**< \brief (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler */
#define OSCCTRL_CFDPRESC_CFDPRESC_Msk (_U_(0x7) << OSCCTRL_CFDPRESC_CFDPRESC_Pos)
#define OSCCTRL_CFDPRESC_CFDPRESC(value) (OSCCTRL_CFDPRESC_CFDPRESC_Msk & ((value) << OSCCTRL_CFDPRESC_CFDPRESC_Pos))
#define OSCCTRL_CFDPRESC_MASK       _U_(0x07)    /**< \brief (OSCCTRL_CFDPRESC) MASK Register */

/* -------- OSCCTRL_EVCTRL : (OSCCTRL Offset: 0x13) (R/W  8) Event Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CFDEO:1;          /*!< bit:      0  Clock Failure Detector Event Output Enable */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_EVCTRL_OFFSET       0x13         /**< \brief (OSCCTRL_EVCTRL offset) Event Control */
#define OSCCTRL_EVCTRL_RESETVALUE   _U_(0x00)    /**< \brief (OSCCTRL_EVCTRL reset_value) Event Control */

#define OSCCTRL_EVCTRL_CFDEO_Pos    0            /**< \brief (OSCCTRL_EVCTRL) Clock Failure Detector Event Output Enable */
#define OSCCTRL_EVCTRL_CFDEO        (_U_(0x1) << OSCCTRL_EVCTRL_CFDEO_Pos)
#define OSCCTRL_EVCTRL_MASK         _U_(0x01)    /**< \brief (OSCCTRL_EVCTRL) MASK Register */

/* -------- OSCCTRL_OSC48MCTRL : (OSCCTRL Offset: 0x14) (R/W  8) 48MHz Internal Oscillator (OSC48M) Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint8_t  :4;               /*!< bit:  2.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_OSC48MCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_OSC48MCTRL_OFFSET   0x14         /**< \brief (OSCCTRL_OSC48MCTRL offset) 48MHz Internal Oscillator (OSC48M) Control */
#define OSCCTRL_OSC48MCTRL_RESETVALUE _U_(0x82)    /**< \brief (OSCCTRL_OSC48MCTRL reset_value) 48MHz Internal Oscillator (OSC48M) Control */

#define OSCCTRL_OSC48MCTRL_ENABLE_Pos 1            /**< \brief (OSCCTRL_OSC48MCTRL) Oscillator Enable */
#define OSCCTRL_OSC48MCTRL_ENABLE   (_U_(0x1) << OSCCTRL_OSC48MCTRL_ENABLE_Pos)
#define OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos 6            /**< \brief (OSCCTRL_OSC48MCTRL) Run in Standby */
#define OSCCTRL_OSC48MCTRL_RUNSTDBY (_U_(0x1) << OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos)
#define OSCCTRL_OSC48MCTRL_ONDEMAND_Pos 7            /**< \brief (OSCCTRL_OSC48MCTRL) On Demand Control */
#define OSCCTRL_OSC48MCTRL_ONDEMAND (_U_(0x1) << OSCCTRL_OSC48MCTRL_ONDEMAND_Pos)
#define OSCCTRL_OSC48MCTRL_MASK     _U_(0xC2)    /**< \brief (OSCCTRL_OSC48MCTRL) MASK Register */

/* -------- OSCCTRL_OSC48MDIV : (OSCCTRL Offset: 0x15) (R/W  8) OSC48M Divider -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DIV:4;            /*!< bit:  0.. 3  OSC48M Division Factor             */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_OSC48MDIV_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_OSC48MDIV_OFFSET    0x15         /**< \brief (OSCCTRL_OSC48MDIV offset) OSC48M Divider */
#define OSCCTRL_OSC48MDIV_RESETVALUE _U_(0x0B)    /**< \brief (OSCCTRL_OSC48MDIV reset_value) OSC48M Divider */

#define OSCCTRL_OSC48MDIV_DIV_Pos   0            /**< \brief (OSCCTRL_OSC48MDIV) OSC48M Division Factor */
#define OSCCTRL_OSC48MDIV_DIV_Msk   (_U_(0xF) << OSCCTRL_OSC48MDIV_DIV_Pos)
#define OSCCTRL_OSC48MDIV_DIV(value) (OSCCTRL_OSC48MDIV_DIV_Msk & ((value) << OSCCTRL_OSC48MDIV_DIV_Pos))
#define OSCCTRL_OSC48MDIV_MASK      _U_(0x0F)    /**< \brief (OSCCTRL_OSC48MDIV) MASK Register */

/* -------- OSCCTRL_OSC48MSTUP : (OSCCTRL Offset: 0x16) (R/W  8) OSC48M Startup Time -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  STARTUP:3;        /*!< bit:  0.. 2  Startup Time                       */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_OSC48MSTUP_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_OSC48MSTUP_OFFSET   0x16         /**< \brief (OSCCTRL_OSC48MSTUP offset) OSC48M Startup Time */
#define OSCCTRL_OSC48MSTUP_RESETVALUE _U_(0x07)    /**< \brief (OSCCTRL_OSC48MSTUP reset_value) OSC48M Startup Time */

#define OSCCTRL_OSC48MSTUP_STARTUP_Pos 0            /**< \brief (OSCCTRL_OSC48MSTUP) Startup Time */
#define OSCCTRL_OSC48MSTUP_STARTUP_Msk (_U_(0x7) << OSCCTRL_OSC48MSTUP_STARTUP_Pos)
#define OSCCTRL_OSC48MSTUP_STARTUP(value) (OSCCTRL_OSC48MSTUP_STARTUP_Msk & ((value) << OSCCTRL_OSC48MSTUP_STARTUP_Pos))
#define OSCCTRL_OSC48MSTUP_MASK     _U_(0x07)    /**< \brief (OSCCTRL_OSC48MSTUP) MASK Register */

/* -------- OSCCTRL_OSC48MSYNCBUSY : (OSCCTRL Offset: 0x18) (R/  32) OSC48M Synchronization Busy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :2;               /*!< bit:  0.. 1  Reserved                           */
    uint32_t OSC48MDIV:1;      /*!< bit:      2  OSC48MDIV Synchronization Status   */
    uint32_t :29;              /*!< bit:  3..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_OSC48MSYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_OSC48MSYNCBUSY_OFFSET 0x18         /**< \brief (OSCCTRL_OSC48MSYNCBUSY offset) OSC48M Synchronization Busy */
#define OSCCTRL_OSC48MSYNCBUSY_RESETVALUE _U_(0x00000000) /**< \brief (OSCCTRL_OSC48MSYNCBUSY reset_value) OSC48M Synchronization Busy */

#define OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos 2            /**< \brief (OSCCTRL_OSC48MSYNCBUSY) OSC48MDIV Synchronization Status */
#define OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV (_U_(0x1) << OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos)
#define OSCCTRL_OSC48MSYNCBUSY_MASK _U_(0x00000004) /**< \brief (OSCCTRL_OSC48MSYNCBUSY) MASK Register */

/* -------- OSCCTRL_DPLLCTRLA : (OSCCTRL Offset: 0x1C) (R/W  8) DPLL Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :4;               /*!< bit:  2.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand                          */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_DPLLCTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLCTRLA_OFFSET    0x1C         /**< \brief (OSCCTRL_DPLLCTRLA offset) DPLL Control */
#define OSCCTRL_DPLLCTRLA_RESETVALUE _U_(0x80)    /**< \brief (OSCCTRL_DPLLCTRLA reset_value) DPLL Control */

#define OSCCTRL_DPLLCTRLA_ENABLE_Pos 1            /**< \brief (OSCCTRL_DPLLCTRLA) Enable */
#define OSCCTRL_DPLLCTRLA_ENABLE    (_U_(0x1) << OSCCTRL_DPLLCTRLA_ENABLE_Pos)
#define OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos 6            /**< \brief (OSCCTRL_DPLLCTRLA) Run in Standby */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY  (_U_(0x1) << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos)
#define OSCCTRL_DPLLCTRLA_ONDEMAND_Pos 7            /**< \brief (OSCCTRL_DPLLCTRLA) On Demand */
#define OSCCTRL_DPLLCTRLA_ONDEMAND  (_U_(0x1) << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos)
#define OSCCTRL_DPLLCTRLA_MASK      _U_(0xC2)    /**< \brief (OSCCTRL_DPLLCTRLA) MASK Register */

/* -------- OSCCTRL_DPLLRATIO : (OSCCTRL Offset: 0x20) (R/W 32) DPLL Ratio Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t LDR:12;           /*!< bit:  0..11  Loop Divider Ratio                 */
    uint32_t :4;               /*!< bit: 12..15  Reserved                           */
    uint32_t LDRFRAC:4;        /*!< bit: 16..19  Loop Divider Ratio Fractional Part */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_DPLLRATIO_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLRATIO_OFFSET    0x20         /**< \brief (OSCCTRL_DPLLRATIO offset) DPLL Ratio Control */
#define OSCCTRL_DPLLRATIO_RESETVALUE _U_(0x00000000) /**< \brief (OSCCTRL_DPLLRATIO reset_value) DPLL Ratio Control */

#define OSCCTRL_DPLLRATIO_LDR_Pos   0            /**< \brief (OSCCTRL_DPLLRATIO) Loop Divider Ratio */
#define OSCCTRL_DPLLRATIO_LDR_Msk   (_U_(0xFFF) << OSCCTRL_DPLLRATIO_LDR_Pos)
#define OSCCTRL_DPLLRATIO_LDR(value) (OSCCTRL_DPLLRATIO_LDR_Msk & ((value) << OSCCTRL_DPLLRATIO_LDR_Pos))
#define OSCCTRL_DPLLRATIO_LDRFRAC_Pos 16           /**< \brief (OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part */
#define OSCCTRL_DPLLRATIO_LDRFRAC_Msk (_U_(0xF) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos)
#define OSCCTRL_DPLLRATIO_LDRFRAC(value) (OSCCTRL_DPLLRATIO_LDRFRAC_Msk & ((value) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos))
#define OSCCTRL_DPLLRATIO_MASK      _U_(0x000F0FFF) /**< \brief (OSCCTRL_DPLLRATIO) MASK Register */

/* -------- OSCCTRL_DPLLCTRLB : (OSCCTRL Offset: 0x24) (R/W 32) Digital Core Configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t FILTER:2;         /*!< bit:  0.. 1  Proportional Integral Filter Selection */
    uint32_t LPEN:1;           /*!< bit:      2  Low-Power Enable                   */
    uint32_t WUF:1;            /*!< bit:      3  Wake Up Fast                       */
    uint32_t REFCLK:2;         /*!< bit:  4.. 5  Reference Clock Selection          */
    uint32_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint32_t LTIME:3;          /*!< bit:  8..10  Lock Time                          */
    uint32_t :1;               /*!< bit:     11  Reserved                           */
    uint32_t LBYPASS:1;        /*!< bit:     12  Lock Bypass                        */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t DIV:11;           /*!< bit: 16..26  Clock Divider                      */
    uint32_t :5;               /*!< bit: 27..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_DPLLCTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLCTRLB_OFFSET    0x24         /**< \brief (OSCCTRL_DPLLCTRLB offset) Digital Core Configuration */
#define OSCCTRL_DPLLCTRLB_RESETVALUE _U_(0x00000000) /**< \brief (OSCCTRL_DPLLCTRLB reset_value) Digital Core Configuration */

#define OSCCTRL_DPLLCTRLB_FILTER_Pos 0            /**< \brief (OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection */
#define OSCCTRL_DPLLCTRLB_FILTER_Msk (_U_(0x3) << OSCCTRL_DPLLCTRLB_FILTER_Pos)
#define OSCCTRL_DPLLCTRLB_FILTER(value) (OSCCTRL_DPLLCTRLB_FILTER_Msk & ((value) << OSCCTRL_DPLLCTRLB_FILTER_Pos))
#define OSCCTRL_DPLLCTRLB_LPEN_Pos  2            /**< \brief (OSCCTRL_DPLLCTRLB) Low-Power Enable */
#define OSCCTRL_DPLLCTRLB_LPEN      (_U_(0x1) << OSCCTRL_DPLLCTRLB_LPEN_Pos)
#define OSCCTRL_DPLLCTRLB_WUF_Pos   3            /**< \brief (OSCCTRL_DPLLCTRLB) Wake Up Fast */
#define OSCCTRL_DPLLCTRLB_WUF       (_U_(0x1) << OSCCTRL_DPLLCTRLB_WUF_Pos)
#define OSCCTRL_DPLLCTRLB_REFCLK_Pos 4            /**< \brief (OSCCTRL_DPLLCTRLB) Reference Clock Selection */
#define OSCCTRL_DPLLCTRLB_REFCLK_Msk (_U_(0x3) << OSCCTRL_DPLLCTRLB_REFCLK_Pos)
#define OSCCTRL_DPLLCTRLB_REFCLK(value) (OSCCTRL_DPLLCTRLB_REFCLK_Msk & ((value) << OSCCTRL_DPLLCTRLB_REFCLK_Pos))
#define OSCCTRL_DPLLCTRLB_LTIME_Pos 8            /**< \brief (OSCCTRL_DPLLCTRLB) Lock Time */
#define OSCCTRL_DPLLCTRLB_LTIME_Msk (_U_(0x7) << OSCCTRL_DPLLCTRLB_LTIME_Pos)
#define OSCCTRL_DPLLCTRLB_LTIME(value) (OSCCTRL_DPLLCTRLB_LTIME_Msk & ((value) << OSCCTRL_DPLLCTRLB_LTIME_Pos))
#define OSCCTRL_DPLLCTRLB_LBYPASS_Pos 12           /**< \brief (OSCCTRL_DPLLCTRLB) Lock Bypass */
#define OSCCTRL_DPLLCTRLB_LBYPASS   (_U_(0x1) << OSCCTRL_DPLLCTRLB_LBYPASS_Pos)
#define OSCCTRL_DPLLCTRLB_DIV_Pos   16           /**< \brief (OSCCTRL_DPLLCTRLB) Clock Divider */
#define OSCCTRL_DPLLCTRLB_DIV_Msk   (_U_(0x7FF) << OSCCTRL_DPLLCTRLB_DIV_Pos)
#define OSCCTRL_DPLLCTRLB_DIV(value) (OSCCTRL_DPLLCTRLB_DIV_Msk & ((value) << OSCCTRL_DPLLCTRLB_DIV_Pos))
#define OSCCTRL_DPLLCTRLB_MASK      _U_(0x07FF173F) /**< \brief (OSCCTRL_DPLLCTRLB) MASK Register */

/* -------- OSCCTRL_DPLLPRESC : (OSCCTRL Offset: 0x28) (R/W  8) DPLL Prescaler -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  PRESC:2;          /*!< bit:  0.. 1  Output Clock Prescaler             */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_DPLLPRESC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLPRESC_OFFSET    0x28         /**< \brief (OSCCTRL_DPLLPRESC offset) DPLL Prescaler */
#define OSCCTRL_DPLLPRESC_RESETVALUE _U_(0x00)    /**< \brief (OSCCTRL_DPLLPRESC reset_value) DPLL Prescaler */

#define OSCCTRL_DPLLPRESC_PRESC_Pos 0            /**< \brief (OSCCTRL_DPLLPRESC) Output Clock Prescaler */
#define OSCCTRL_DPLLPRESC_PRESC_Msk (_U_(0x3) << OSCCTRL_DPLLPRESC_PRESC_Pos)
#define OSCCTRL_DPLLPRESC_PRESC(value) (OSCCTRL_DPLLPRESC_PRESC_Msk & ((value) << OSCCTRL_DPLLPRESC_PRESC_Pos))
#define   OSCCTRL_DPLLPRESC_PRESC_DIV1_Val _U_(0x0)   /**< \brief (OSCCTRL_DPLLPRESC) DPLL output is divided by 1 */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV2_Val _U_(0x1)   /**< \brief (OSCCTRL_DPLLPRESC) DPLL output is divided by 2 */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV4_Val _U_(0x2)   /**< \brief (OSCCTRL_DPLLPRESC) DPLL output is divided by 4 */
#define OSCCTRL_DPLLPRESC_PRESC_DIV1 (OSCCTRL_DPLLPRESC_PRESC_DIV1_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)
#define OSCCTRL_DPLLPRESC_PRESC_DIV2 (OSCCTRL_DPLLPRESC_PRESC_DIV2_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)
#define OSCCTRL_DPLLPRESC_PRESC_DIV4 (OSCCTRL_DPLLPRESC_PRESC_DIV4_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)
#define OSCCTRL_DPLLPRESC_MASK      _U_(0x03)    /**< \brief (OSCCTRL_DPLLPRESC) MASK Register */

/* -------- OSCCTRL_DPLLSYNCBUSY : (OSCCTRL Offset: 0x2C) (R/   8) DPLL Synchronization Busy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  DPLL Enable Synchronization Status */
    uint8_t  DPLLRATIO:1;      /*!< bit:      2  DPLL Ratio Synchronization Status  */
    uint8_t  DPLLPRESC:1;      /*!< bit:      3  DPLL Prescaler Synchronization Status */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_DPLLSYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLSYNCBUSY_OFFSET 0x2C         /**< \brief (OSCCTRL_DPLLSYNCBUSY offset) DPLL Synchronization Busy */
#define OSCCTRL_DPLLSYNCBUSY_RESETVALUE _U_(0x00)    /**< \brief (OSCCTRL_DPLLSYNCBUSY reset_value) DPLL Synchronization Busy */

#define OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos 1            /**< \brief (OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status */
#define OSCCTRL_DPLLSYNCBUSY_ENABLE (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos)
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos 2            /**< \brief (OSCCTRL_DPLLSYNCBUSY) DPLL Ratio Synchronization Status */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos)
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos 3            /**< \brief (OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos)
#define OSCCTRL_DPLLSYNCBUSY_MASK   _U_(0x0E)    /**< \brief (OSCCTRL_DPLLSYNCBUSY) MASK Register */

/* -------- OSCCTRL_DPLLSTATUS : (OSCCTRL Offset: 0x30) (R/   8) DPLL Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  LOCK:1;           /*!< bit:      0  DPLL Lock Status                   */
    uint8_t  CLKRDY:1;         /*!< bit:      1  DPLL Clock Ready                   */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} OSCCTRL_DPLLSTATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLSTATUS_OFFSET   0x30         /**< \brief (OSCCTRL_DPLLSTATUS offset) DPLL Status */
#define OSCCTRL_DPLLSTATUS_RESETVALUE _U_(0x00)    /**< \brief (OSCCTRL_DPLLSTATUS reset_value) DPLL Status */

#define OSCCTRL_DPLLSTATUS_LOCK_Pos 0            /**< \brief (OSCCTRL_DPLLSTATUS) DPLL Lock Status */
#define OSCCTRL_DPLLSTATUS_LOCK     (_U_(0x1) << OSCCTRL_DPLLSTATUS_LOCK_Pos)
#define OSCCTRL_DPLLSTATUS_CLKRDY_Pos 1            /**< \brief (OSCCTRL_DPLLSTATUS) DPLL Clock Ready */
#define OSCCTRL_DPLLSTATUS_CLKRDY   (_U_(0x1) << OSCCTRL_DPLLSTATUS_CLKRDY_Pos)
#define OSCCTRL_DPLLSTATUS_MASK     _U_(0x03)    /**< \brief (OSCCTRL_DPLLSTATUS) MASK Register */

/* -------- OSCCTRL_CAL48M : (OSCCTRL Offset: 0x38) (R/W 32) 48MHz Oscillator Calibration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t FCAL:6;           /*!< bit:  0.. 5  Frequency Calibration (48MHz)      */
    uint32_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint32_t FRANGE:2;         /*!< bit:  8.. 9  Frequency Range (48MHz)            */
    uint32_t :6;               /*!< bit: 10..15  Reserved                           */
    uint32_t TCAL:6;           /*!< bit: 16..21  Temperature Calibration (48MHz)    */
    uint32_t :10;              /*!< bit: 22..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} OSCCTRL_CAL48M_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_CAL48M_OFFSET       0x38         /**< \brief (OSCCTRL_CAL48M offset) 48MHz Oscillator Calibration */
#define OSCCTRL_CAL48M_RESETVALUE   _U_(0x00000000) /**< \brief (OSCCTRL_CAL48M reset_value) 48MHz Oscillator Calibration */

#define OSCCTRL_CAL48M_FCAL_Pos     0            /**< \brief (OSCCTRL_CAL48M) Frequency Calibration (48MHz) */
#define OSCCTRL_CAL48M_FCAL_Msk     (_U_(0x3F) << OSCCTRL_CAL48M_FCAL_Pos)
#define OSCCTRL_CAL48M_FCAL(value)  (OSCCTRL_CAL48M_FCAL_Msk & ((value) << OSCCTRL_CAL48M_FCAL_Pos))
#define OSCCTRL_CAL48M_FRANGE_Pos   8            /**< \brief (OSCCTRL_CAL48M) Frequency Range (48MHz) */
#define OSCCTRL_CAL48M_FRANGE_Msk   (_U_(0x3) << OSCCTRL_CAL48M_FRANGE_Pos)
#define OSCCTRL_CAL48M_FRANGE(value) (OSCCTRL_CAL48M_FRANGE_Msk & ((value) << OSCCTRL_CAL48M_FRANGE_Pos))
#define OSCCTRL_CAL48M_TCAL_Pos     16           /**< \brief (OSCCTRL_CAL48M) Temperature Calibration (48MHz) */
#define OSCCTRL_CAL48M_TCAL_Msk     (_U_(0x3F) << OSCCTRL_CAL48M_TCAL_Pos)
#define OSCCTRL_CAL48M_TCAL(value)  (OSCCTRL_CAL48M_TCAL_Msk & ((value) << OSCCTRL_CAL48M_TCAL_Pos))
#define OSCCTRL_CAL48M_MASK         _U_(0x003F033F) /**< \brief (OSCCTRL_CAL48M) MASK Register */

/** \brief OSCCTRL hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO OSCCTRL_INTENCLR_Type     INTENCLR;    /**< \brief Offset: 0x00 (R/W 32) Interrupt Enable Clear */
  __IO OSCCTRL_INTENSET_Type     INTENSET;    /**< \brief Offset: 0x04 (R/W 32) Interrupt Enable Set */
  __IO OSCCTRL_INTFLAG_Type      INTFLAG;     /**< \brief Offset: 0x08 (R/W 32) Interrupt Flag Status and Clear */
  __I  OSCCTRL_STATUS_Type       STATUS;      /**< \brief Offset: 0x0C (R/  32) Power and Clocks Status */
  __IO OSCCTRL_XOSCCTRL_Type     XOSCCTRL;    /**< \brief Offset: 0x10 (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control */
  __IO OSCCTRL_CFDPRESC_Type     CFDPRESC;    /**< \brief Offset: 0x12 (R/W  8) Clock Failure Detector Prescaler */
  __IO OSCCTRL_EVCTRL_Type       EVCTRL;      /**< \brief Offset: 0x13 (R/W  8) Event Control */
  __IO OSCCTRL_OSC48MCTRL_Type   OSC48MCTRL;  /**< \brief Offset: 0x14 (R/W  8) 48MHz Internal Oscillator (OSC48M) Control */
  __IO OSCCTRL_OSC48MDIV_Type    OSC48MDIV;   /**< \brief Offset: 0x15 (R/W  8) OSC48M Divider */
  __IO OSCCTRL_OSC48MSTUP_Type   OSC48MSTUP;  /**< \brief Offset: 0x16 (R/W  8) OSC48M Startup Time */
       RoReg8                    Reserved1[0x1];
  __I  OSCCTRL_OSC48MSYNCBUSY_Type OSC48MSYNCBUSY; /**< \brief Offset: 0x18 (R/  32) OSC48M Synchronization Busy */
  __IO OSCCTRL_DPLLCTRLA_Type    DPLLCTRLA;   /**< \brief Offset: 0x1C (R/W  8) DPLL Control */
       RoReg8                    Reserved2[0x3];
  __IO OSCCTRL_DPLLRATIO_Type    DPLLRATIO;   /**< \brief Offset: 0x20 (R/W 32) DPLL Ratio Control */
  __IO OSCCTRL_DPLLCTRLB_Type    DPLLCTRLB;   /**< \brief Offset: 0x24 (R/W 32) Digital Core Configuration */
  __IO OSCCTRL_DPLLPRESC_Type    DPLLPRESC;   /**< \brief Offset: 0x28 (R/W  8) DPLL Prescaler */
       RoReg8                    Reserved3[0x3];
  __I  OSCCTRL_DPLLSYNCBUSY_Type DPLLSYNCBUSY; /**< \brief Offset: 0x2C (R/   8) DPLL Synchronization Busy */
       RoReg8                    Reserved4[0x3];
  __I  OSCCTRL_DPLLSTATUS_Type   DPLLSTATUS;  /**< \brief Offset: 0x30 (R/   8) DPLL Status */
       RoReg8                    Reserved5[0x7];
  __IO OSCCTRL_CAL48M_Type       CAL48M;      /**< \brief Offset: 0x38 (R/W 32) 48MHz Oscillator Calibration */
} Oscctrl;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_OSCCTRL_COMPONENT_ */
