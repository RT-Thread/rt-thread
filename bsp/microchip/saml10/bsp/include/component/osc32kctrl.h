/**
 * \file
 *
 * \brief Component description for OSC32KCTRL
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
#ifndef _SAML10_OSC32KCTRL_COMPONENT_H_
#define _SAML10_OSC32KCTRL_COMPONENT_H_
#define _SAML10_OSC32KCTRL_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 32k Oscillators Control
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR OSC32KCTRL */
/* ========================================================================== */

#define OSC32KCTRL_U2246                      /**< (OSC32KCTRL) Module ID */
#define REV_OSC32KCTRL 0x400                  /**< (OSC32KCTRL) Module revision */

/* -------- OSC32KCTRL_INTENCLR : (OSC32KCTRL Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSC32KRDY:1;              /**< bit:      0  XOSC32K Ready Interrupt Enable           */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t CLKFAIL:1;                 /**< bit:      2  XOSC32K Clock Failure Detector Interrupt Enable */
    uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSC32KCTRL_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_INTENCLR_OFFSET          (0x00)                                        /**<  (OSC32KCTRL_INTENCLR) Interrupt Enable Clear  Offset */
#define OSC32KCTRL_INTENCLR_RESETVALUE      _U_(0x00)                                     /**<  (OSC32KCTRL_INTENCLR) Interrupt Enable Clear  Reset Value */

#define OSC32KCTRL_INTENCLR_XOSC32KRDY_Pos  0                                              /**< (OSC32KCTRL_INTENCLR) XOSC32K Ready Interrupt Enable Position */
#define OSC32KCTRL_INTENCLR_XOSC32KRDY_Msk  (_U_(0x1) << OSC32KCTRL_INTENCLR_XOSC32KRDY_Pos)  /**< (OSC32KCTRL_INTENCLR) XOSC32K Ready Interrupt Enable Mask */
#define OSC32KCTRL_INTENCLR_XOSC32KRDY      OSC32KCTRL_INTENCLR_XOSC32KRDY_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTENCLR_XOSC32KRDY_Msk instead */
#define OSC32KCTRL_INTENCLR_CLKFAIL_Pos     2                                              /**< (OSC32KCTRL_INTENCLR) XOSC32K Clock Failure Detector Interrupt Enable Position */
#define OSC32KCTRL_INTENCLR_CLKFAIL_Msk     (_U_(0x1) << OSC32KCTRL_INTENCLR_CLKFAIL_Pos)  /**< (OSC32KCTRL_INTENCLR) XOSC32K Clock Failure Detector Interrupt Enable Mask */
#define OSC32KCTRL_INTENCLR_CLKFAIL         OSC32KCTRL_INTENCLR_CLKFAIL_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTENCLR_CLKFAIL_Msk instead */
#define OSC32KCTRL_INTENCLR_MASK            _U_(0x05)                                      /**< \deprecated (OSC32KCTRL_INTENCLR) Register MASK  (Use OSC32KCTRL_INTENCLR_Msk instead)  */
#define OSC32KCTRL_INTENCLR_Msk             _U_(0x05)                                      /**< (OSC32KCTRL_INTENCLR) Register Mask  */


/* -------- OSC32KCTRL_INTENSET : (OSC32KCTRL Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSC32KRDY:1;              /**< bit:      0  XOSC32K Ready Interrupt Enable           */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t CLKFAIL:1;                 /**< bit:      2  XOSC32K Clock Failure Detector Interrupt Enable */
    uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSC32KCTRL_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_INTENSET_OFFSET          (0x04)                                        /**<  (OSC32KCTRL_INTENSET) Interrupt Enable Set  Offset */
#define OSC32KCTRL_INTENSET_RESETVALUE      _U_(0x00)                                     /**<  (OSC32KCTRL_INTENSET) Interrupt Enable Set  Reset Value */

#define OSC32KCTRL_INTENSET_XOSC32KRDY_Pos  0                                              /**< (OSC32KCTRL_INTENSET) XOSC32K Ready Interrupt Enable Position */
#define OSC32KCTRL_INTENSET_XOSC32KRDY_Msk  (_U_(0x1) << OSC32KCTRL_INTENSET_XOSC32KRDY_Pos)  /**< (OSC32KCTRL_INTENSET) XOSC32K Ready Interrupt Enable Mask */
#define OSC32KCTRL_INTENSET_XOSC32KRDY      OSC32KCTRL_INTENSET_XOSC32KRDY_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTENSET_XOSC32KRDY_Msk instead */
#define OSC32KCTRL_INTENSET_CLKFAIL_Pos     2                                              /**< (OSC32KCTRL_INTENSET) XOSC32K Clock Failure Detector Interrupt Enable Position */
#define OSC32KCTRL_INTENSET_CLKFAIL_Msk     (_U_(0x1) << OSC32KCTRL_INTENSET_CLKFAIL_Pos)  /**< (OSC32KCTRL_INTENSET) XOSC32K Clock Failure Detector Interrupt Enable Mask */
#define OSC32KCTRL_INTENSET_CLKFAIL         OSC32KCTRL_INTENSET_CLKFAIL_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTENSET_CLKFAIL_Msk instead */
#define OSC32KCTRL_INTENSET_MASK            _U_(0x05)                                      /**< \deprecated (OSC32KCTRL_INTENSET) Register MASK  (Use OSC32KCTRL_INTENSET_Msk instead)  */
#define OSC32KCTRL_INTENSET_Msk             _U_(0x05)                                      /**< (OSC32KCTRL_INTENSET) Register Mask  */


/* -------- OSC32KCTRL_INTFLAG : (OSC32KCTRL Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t XOSC32KRDY:1;              /**< bit:      0  XOSC32K Ready                            */
    __I uint32_t :1;                        /**< bit:      1  Reserved */
    __I uint32_t CLKFAIL:1;                 /**< bit:      2  XOSC32K Clock Failure Detector           */
    __I uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSC32KCTRL_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_INTFLAG_OFFSET           (0x08)                                        /**<  (OSC32KCTRL_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define OSC32KCTRL_INTFLAG_RESETVALUE       _U_(0x00)                                     /**<  (OSC32KCTRL_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define OSC32KCTRL_INTFLAG_XOSC32KRDY_Pos   0                                              /**< (OSC32KCTRL_INTFLAG) XOSC32K Ready Position */
#define OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk   (_U_(0x1) << OSC32KCTRL_INTFLAG_XOSC32KRDY_Pos)  /**< (OSC32KCTRL_INTFLAG) XOSC32K Ready Mask */
#define OSC32KCTRL_INTFLAG_XOSC32KRDY       OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk instead */
#define OSC32KCTRL_INTFLAG_CLKFAIL_Pos      2                                              /**< (OSC32KCTRL_INTFLAG) XOSC32K Clock Failure Detector Position */
#define OSC32KCTRL_INTFLAG_CLKFAIL_Msk      (_U_(0x1) << OSC32KCTRL_INTFLAG_CLKFAIL_Pos)   /**< (OSC32KCTRL_INTFLAG) XOSC32K Clock Failure Detector Mask */
#define OSC32KCTRL_INTFLAG_CLKFAIL          OSC32KCTRL_INTFLAG_CLKFAIL_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_INTFLAG_CLKFAIL_Msk instead */
#define OSC32KCTRL_INTFLAG_MASK             _U_(0x05)                                      /**< \deprecated (OSC32KCTRL_INTFLAG) Register MASK  (Use OSC32KCTRL_INTFLAG_Msk instead)  */
#define OSC32KCTRL_INTFLAG_Msk              _U_(0x05)                                      /**< (OSC32KCTRL_INTFLAG) Register Mask  */


/* -------- OSC32KCTRL_STATUS : (OSC32KCTRL Offset: 0x0c) (R/ 32) Power and Clocks Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSC32KRDY:1;              /**< bit:      0  XOSC32K Ready                            */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t CLKFAIL:1;                 /**< bit:      2  XOSC32K Clock Failure Detector           */
    uint32_t CLKSW:1;                   /**< bit:      3  XOSC32K Clock switch                     */
    uint32_t ULP32KSW:1;                /**< bit:      4  OSCULP32K Clock Switch                   */
    uint32_t :27;                       /**< bit:  5..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSC32KCTRL_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_STATUS_OFFSET            (0x0C)                                        /**<  (OSC32KCTRL_STATUS) Power and Clocks Status  Offset */
#define OSC32KCTRL_STATUS_RESETVALUE        _U_(0x00)                                     /**<  (OSC32KCTRL_STATUS) Power and Clocks Status  Reset Value */

#define OSC32KCTRL_STATUS_XOSC32KRDY_Pos    0                                              /**< (OSC32KCTRL_STATUS) XOSC32K Ready Position */
#define OSC32KCTRL_STATUS_XOSC32KRDY_Msk    (_U_(0x1) << OSC32KCTRL_STATUS_XOSC32KRDY_Pos)  /**< (OSC32KCTRL_STATUS) XOSC32K Ready Mask */
#define OSC32KCTRL_STATUS_XOSC32KRDY        OSC32KCTRL_STATUS_XOSC32KRDY_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_STATUS_XOSC32KRDY_Msk instead */
#define OSC32KCTRL_STATUS_CLKFAIL_Pos       2                                              /**< (OSC32KCTRL_STATUS) XOSC32K Clock Failure Detector Position */
#define OSC32KCTRL_STATUS_CLKFAIL_Msk       (_U_(0x1) << OSC32KCTRL_STATUS_CLKFAIL_Pos)    /**< (OSC32KCTRL_STATUS) XOSC32K Clock Failure Detector Mask */
#define OSC32KCTRL_STATUS_CLKFAIL           OSC32KCTRL_STATUS_CLKFAIL_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_STATUS_CLKFAIL_Msk instead */
#define OSC32KCTRL_STATUS_CLKSW_Pos         3                                              /**< (OSC32KCTRL_STATUS) XOSC32K Clock switch Position */
#define OSC32KCTRL_STATUS_CLKSW_Msk         (_U_(0x1) << OSC32KCTRL_STATUS_CLKSW_Pos)      /**< (OSC32KCTRL_STATUS) XOSC32K Clock switch Mask */
#define OSC32KCTRL_STATUS_CLKSW             OSC32KCTRL_STATUS_CLKSW_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_STATUS_CLKSW_Msk instead */
#define OSC32KCTRL_STATUS_ULP32KSW_Pos      4                                              /**< (OSC32KCTRL_STATUS) OSCULP32K Clock Switch Position */
#define OSC32KCTRL_STATUS_ULP32KSW_Msk      (_U_(0x1) << OSC32KCTRL_STATUS_ULP32KSW_Pos)   /**< (OSC32KCTRL_STATUS) OSCULP32K Clock Switch Mask */
#define OSC32KCTRL_STATUS_ULP32KSW          OSC32KCTRL_STATUS_ULP32KSW_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_STATUS_ULP32KSW_Msk instead */
#define OSC32KCTRL_STATUS_MASK              _U_(0x1D)                                      /**< \deprecated (OSC32KCTRL_STATUS) Register MASK  (Use OSC32KCTRL_STATUS_Msk instead)  */
#define OSC32KCTRL_STATUS_Msk               _U_(0x1D)                                      /**< (OSC32KCTRL_STATUS) Register Mask  */


/* -------- OSC32KCTRL_RTCCTRL : (OSC32KCTRL Offset: 0x10) (R/W 8) RTC Clock Selection -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RTCSEL:3;                  /**< bit:   0..2  RTC Clock Selection                      */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSC32KCTRL_RTCCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_RTCCTRL_OFFSET           (0x10)                                        /**<  (OSC32KCTRL_RTCCTRL) RTC Clock Selection  Offset */
#define OSC32KCTRL_RTCCTRL_RESETVALUE       _U_(0x00)                                     /**<  (OSC32KCTRL_RTCCTRL) RTC Clock Selection  Reset Value */

#define OSC32KCTRL_RTCCTRL_RTCSEL_Pos       0                                              /**< (OSC32KCTRL_RTCCTRL) RTC Clock Selection Position */
#define OSC32KCTRL_RTCCTRL_RTCSEL_Msk       (_U_(0x7) << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)    /**< (OSC32KCTRL_RTCCTRL) RTC Clock Selection Mask */
#define OSC32KCTRL_RTCCTRL_RTCSEL(value)    (OSC32KCTRL_RTCCTRL_RTCSEL_Msk & ((value) << OSC32KCTRL_RTCCTRL_RTCSEL_Pos))
#define   OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K_Val _U_(0x0)                                       /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32kHz internal ULP oscillator  */
#define   OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K_Val _U_(0x1)                                       /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32kHz internal ULP oscillator  */
#define   OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K_Val _U_(0x2)                                       /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator  */
#define   OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K_Val _U_(0x3)                                       /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz internal oscillator  */
#define   OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val _U_(0x4)                                       /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator  */
#define   OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val _U_(0x5)                                       /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz external crystal oscillator  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K     (OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32kHz internal ULP oscillator Position  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K    (OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32kHz internal ULP oscillator Position  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K     (OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator Position  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K    (OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz internal oscillator Position  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K    (OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator Position  */
#define OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K   (OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val << OSC32KCTRL_RTCCTRL_RTCSEL_Pos)  /**< (OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz external crystal oscillator Position  */
#define OSC32KCTRL_RTCCTRL_MASK             _U_(0x07)                                      /**< \deprecated (OSC32KCTRL_RTCCTRL) Register MASK  (Use OSC32KCTRL_RTCCTRL_Msk instead)  */
#define OSC32KCTRL_RTCCTRL_Msk              _U_(0x07)                                      /**< (OSC32KCTRL_RTCCTRL) Register Mask  */


/* -------- OSC32KCTRL_XOSC32K : (OSC32KCTRL Offset: 0x14) (R/W 16) 32kHz External Crystal Oscillator (XOSC32K) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :1;                        /**< bit:      0  Reserved */
    uint16_t ENABLE:1;                  /**< bit:      1  Oscillator Enable                        */
    uint16_t XTALEN:1;                  /**< bit:      2  Crystal Oscillator Enable                */
    uint16_t EN32K:1;                   /**< bit:      3  32kHz Output Enable                      */
    uint16_t EN1K:1;                    /**< bit:      4  1kHz Output Enable                       */
    uint16_t :1;                        /**< bit:      5  Reserved */
    uint16_t RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint16_t ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
    uint16_t STARTUP:3;                 /**< bit:  8..10  Oscillator Start-Up Time                 */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t WRTLOCK:1;                 /**< bit:     12  Write Lock                               */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} OSC32KCTRL_XOSC32K_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_XOSC32K_OFFSET           (0x14)                                        /**<  (OSC32KCTRL_XOSC32K) 32kHz External Crystal Oscillator (XOSC32K) Control  Offset */
#define OSC32KCTRL_XOSC32K_RESETVALUE       _U_(0x80)                                     /**<  (OSC32KCTRL_XOSC32K) 32kHz External Crystal Oscillator (XOSC32K) Control  Reset Value */

#define OSC32KCTRL_XOSC32K_ENABLE_Pos       1                                              /**< (OSC32KCTRL_XOSC32K) Oscillator Enable Position */
#define OSC32KCTRL_XOSC32K_ENABLE_Msk       (_U_(0x1) << OSC32KCTRL_XOSC32K_ENABLE_Pos)    /**< (OSC32KCTRL_XOSC32K) Oscillator Enable Mask */
#define OSC32KCTRL_XOSC32K_ENABLE           OSC32KCTRL_XOSC32K_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_ENABLE_Msk instead */
#define OSC32KCTRL_XOSC32K_XTALEN_Pos       2                                              /**< (OSC32KCTRL_XOSC32K) Crystal Oscillator Enable Position */
#define OSC32KCTRL_XOSC32K_XTALEN_Msk       (_U_(0x1) << OSC32KCTRL_XOSC32K_XTALEN_Pos)    /**< (OSC32KCTRL_XOSC32K) Crystal Oscillator Enable Mask */
#define OSC32KCTRL_XOSC32K_XTALEN           OSC32KCTRL_XOSC32K_XTALEN_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_XTALEN_Msk instead */
#define OSC32KCTRL_XOSC32K_EN32K_Pos        3                                              /**< (OSC32KCTRL_XOSC32K) 32kHz Output Enable Position */
#define OSC32KCTRL_XOSC32K_EN32K_Msk        (_U_(0x1) << OSC32KCTRL_XOSC32K_EN32K_Pos)     /**< (OSC32KCTRL_XOSC32K) 32kHz Output Enable Mask */
#define OSC32KCTRL_XOSC32K_EN32K            OSC32KCTRL_XOSC32K_EN32K_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_EN32K_Msk instead */
#define OSC32KCTRL_XOSC32K_EN1K_Pos         4                                              /**< (OSC32KCTRL_XOSC32K) 1kHz Output Enable Position */
#define OSC32KCTRL_XOSC32K_EN1K_Msk         (_U_(0x1) << OSC32KCTRL_XOSC32K_EN1K_Pos)      /**< (OSC32KCTRL_XOSC32K) 1kHz Output Enable Mask */
#define OSC32KCTRL_XOSC32K_EN1K             OSC32KCTRL_XOSC32K_EN1K_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_EN1K_Msk instead */
#define OSC32KCTRL_XOSC32K_RUNSTDBY_Pos     6                                              /**< (OSC32KCTRL_XOSC32K) Run in Standby Position */
#define OSC32KCTRL_XOSC32K_RUNSTDBY_Msk     (_U_(0x1) << OSC32KCTRL_XOSC32K_RUNSTDBY_Pos)  /**< (OSC32KCTRL_XOSC32K) Run in Standby Mask */
#define OSC32KCTRL_XOSC32K_RUNSTDBY         OSC32KCTRL_XOSC32K_RUNSTDBY_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_RUNSTDBY_Msk instead */
#define OSC32KCTRL_XOSC32K_ONDEMAND_Pos     7                                              /**< (OSC32KCTRL_XOSC32K) On Demand Control Position */
#define OSC32KCTRL_XOSC32K_ONDEMAND_Msk     (_U_(0x1) << OSC32KCTRL_XOSC32K_ONDEMAND_Pos)  /**< (OSC32KCTRL_XOSC32K) On Demand Control Mask */
#define OSC32KCTRL_XOSC32K_ONDEMAND         OSC32KCTRL_XOSC32K_ONDEMAND_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_ONDEMAND_Msk instead */
#define OSC32KCTRL_XOSC32K_STARTUP_Pos      8                                              /**< (OSC32KCTRL_XOSC32K) Oscillator Start-Up Time Position */
#define OSC32KCTRL_XOSC32K_STARTUP_Msk      (_U_(0x7) << OSC32KCTRL_XOSC32K_STARTUP_Pos)   /**< (OSC32KCTRL_XOSC32K) Oscillator Start-Up Time Mask */
#define OSC32KCTRL_XOSC32K_STARTUP(value)   (OSC32KCTRL_XOSC32K_STARTUP_Msk & ((value) << OSC32KCTRL_XOSC32K_STARTUP_Pos))
#define OSC32KCTRL_XOSC32K_WRTLOCK_Pos      12                                             /**< (OSC32KCTRL_XOSC32K) Write Lock Position */
#define OSC32KCTRL_XOSC32K_WRTLOCK_Msk      (_U_(0x1) << OSC32KCTRL_XOSC32K_WRTLOCK_Pos)   /**< (OSC32KCTRL_XOSC32K) Write Lock Mask */
#define OSC32KCTRL_XOSC32K_WRTLOCK          OSC32KCTRL_XOSC32K_WRTLOCK_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_XOSC32K_WRTLOCK_Msk instead */
#define OSC32KCTRL_XOSC32K_MASK             _U_(0x17DE)                                    /**< \deprecated (OSC32KCTRL_XOSC32K) Register MASK  (Use OSC32KCTRL_XOSC32K_Msk instead)  */
#define OSC32KCTRL_XOSC32K_Msk              _U_(0x17DE)                                    /**< (OSC32KCTRL_XOSC32K) Register Mask  */


/* -------- OSC32KCTRL_CFDCTRL : (OSC32KCTRL Offset: 0x16) (R/W 8) Clock Failure Detector Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CFDEN:1;                   /**< bit:      0  Clock Failure Detector Enable            */
    uint8_t  SWBACK:1;                  /**< bit:      1  Clock Switch Back                        */
    uint8_t  CFDPRESC:1;                /**< bit:      2  Clock Failure Detector Prescaler         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSC32KCTRL_CFDCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_CFDCTRL_OFFSET           (0x16)                                        /**<  (OSC32KCTRL_CFDCTRL) Clock Failure Detector Control  Offset */
#define OSC32KCTRL_CFDCTRL_RESETVALUE       _U_(0x00)                                     /**<  (OSC32KCTRL_CFDCTRL) Clock Failure Detector Control  Reset Value */

#define OSC32KCTRL_CFDCTRL_CFDEN_Pos        0                                              /**< (OSC32KCTRL_CFDCTRL) Clock Failure Detector Enable Position */
#define OSC32KCTRL_CFDCTRL_CFDEN_Msk        (_U_(0x1) << OSC32KCTRL_CFDCTRL_CFDEN_Pos)     /**< (OSC32KCTRL_CFDCTRL) Clock Failure Detector Enable Mask */
#define OSC32KCTRL_CFDCTRL_CFDEN            OSC32KCTRL_CFDCTRL_CFDEN_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_CFDCTRL_CFDEN_Msk instead */
#define OSC32KCTRL_CFDCTRL_SWBACK_Pos       1                                              /**< (OSC32KCTRL_CFDCTRL) Clock Switch Back Position */
#define OSC32KCTRL_CFDCTRL_SWBACK_Msk       (_U_(0x1) << OSC32KCTRL_CFDCTRL_SWBACK_Pos)    /**< (OSC32KCTRL_CFDCTRL) Clock Switch Back Mask */
#define OSC32KCTRL_CFDCTRL_SWBACK           OSC32KCTRL_CFDCTRL_SWBACK_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_CFDCTRL_SWBACK_Msk instead */
#define OSC32KCTRL_CFDCTRL_CFDPRESC_Pos     2                                              /**< (OSC32KCTRL_CFDCTRL) Clock Failure Detector Prescaler Position */
#define OSC32KCTRL_CFDCTRL_CFDPRESC_Msk     (_U_(0x1) << OSC32KCTRL_CFDCTRL_CFDPRESC_Pos)  /**< (OSC32KCTRL_CFDCTRL) Clock Failure Detector Prescaler Mask */
#define OSC32KCTRL_CFDCTRL_CFDPRESC         OSC32KCTRL_CFDCTRL_CFDPRESC_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_CFDCTRL_CFDPRESC_Msk instead */
#define OSC32KCTRL_CFDCTRL_MASK             _U_(0x07)                                      /**< \deprecated (OSC32KCTRL_CFDCTRL) Register MASK  (Use OSC32KCTRL_CFDCTRL_Msk instead)  */
#define OSC32KCTRL_CFDCTRL_Msk              _U_(0x07)                                      /**< (OSC32KCTRL_CFDCTRL) Register Mask  */


/* -------- OSC32KCTRL_EVCTRL : (OSC32KCTRL Offset: 0x17) (R/W 8) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CFDEO:1;                   /**< bit:      0  Clock Failure Detector Event Output Enable */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSC32KCTRL_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_EVCTRL_OFFSET            (0x17)                                        /**<  (OSC32KCTRL_EVCTRL) Event Control  Offset */
#define OSC32KCTRL_EVCTRL_RESETVALUE        _U_(0x00)                                     /**<  (OSC32KCTRL_EVCTRL) Event Control  Reset Value */

#define OSC32KCTRL_EVCTRL_CFDEO_Pos         0                                              /**< (OSC32KCTRL_EVCTRL) Clock Failure Detector Event Output Enable Position */
#define OSC32KCTRL_EVCTRL_CFDEO_Msk         (_U_(0x1) << OSC32KCTRL_EVCTRL_CFDEO_Pos)      /**< (OSC32KCTRL_EVCTRL) Clock Failure Detector Event Output Enable Mask */
#define OSC32KCTRL_EVCTRL_CFDEO             OSC32KCTRL_EVCTRL_CFDEO_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_EVCTRL_CFDEO_Msk instead */
#define OSC32KCTRL_EVCTRL_MASK              _U_(0x01)                                      /**< \deprecated (OSC32KCTRL_EVCTRL) Register MASK  (Use OSC32KCTRL_EVCTRL_Msk instead)  */
#define OSC32KCTRL_EVCTRL_Msk               _U_(0x01)                                      /**< (OSC32KCTRL_EVCTRL) Register Mask  */


/* -------- OSC32KCTRL_OSCULP32K : (OSC32KCTRL Offset: 0x1c) (R/W 32) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :5;                        /**< bit:   0..4  Reserved */
    uint32_t ULP32KSW:1;                /**< bit:      5  OSCULP32K Clock Switch Enable            */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t CALIB:5;                   /**< bit:  8..12  Oscillator Calibration                   */
    uint32_t :2;                        /**< bit: 13..14  Reserved */
    uint32_t WRTLOCK:1;                 /**< bit:     15  Write Lock                               */
    uint32_t :16;                       /**< bit: 16..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSC32KCTRL_OSCULP32K_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSC32KCTRL_OSCULP32K_OFFSET         (0x1C)                                        /**<  (OSC32KCTRL_OSCULP32K) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control  Offset */
#define OSC32KCTRL_OSCULP32K_RESETVALUE     _U_(0x00)                                     /**<  (OSC32KCTRL_OSCULP32K) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control  Reset Value */

#define OSC32KCTRL_OSCULP32K_ULP32KSW_Pos   5                                              /**< (OSC32KCTRL_OSCULP32K) OSCULP32K Clock Switch Enable Position */
#define OSC32KCTRL_OSCULP32K_ULP32KSW_Msk   (_U_(0x1) << OSC32KCTRL_OSCULP32K_ULP32KSW_Pos)  /**< (OSC32KCTRL_OSCULP32K) OSCULP32K Clock Switch Enable Mask */
#define OSC32KCTRL_OSCULP32K_ULP32KSW       OSC32KCTRL_OSCULP32K_ULP32KSW_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_OSCULP32K_ULP32KSW_Msk instead */
#define OSC32KCTRL_OSCULP32K_CALIB_Pos      8                                              /**< (OSC32KCTRL_OSCULP32K) Oscillator Calibration Position */
#define OSC32KCTRL_OSCULP32K_CALIB_Msk      (_U_(0x1F) << OSC32KCTRL_OSCULP32K_CALIB_Pos)  /**< (OSC32KCTRL_OSCULP32K) Oscillator Calibration Mask */
#define OSC32KCTRL_OSCULP32K_CALIB(value)   (OSC32KCTRL_OSCULP32K_CALIB_Msk & ((value) << OSC32KCTRL_OSCULP32K_CALIB_Pos))
#define OSC32KCTRL_OSCULP32K_WRTLOCK_Pos    15                                             /**< (OSC32KCTRL_OSCULP32K) Write Lock Position */
#define OSC32KCTRL_OSCULP32K_WRTLOCK_Msk    (_U_(0x1) << OSC32KCTRL_OSCULP32K_WRTLOCK_Pos)  /**< (OSC32KCTRL_OSCULP32K) Write Lock Mask */
#define OSC32KCTRL_OSCULP32K_WRTLOCK        OSC32KCTRL_OSCULP32K_WRTLOCK_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSC32KCTRL_OSCULP32K_WRTLOCK_Msk instead */
#define OSC32KCTRL_OSCULP32K_MASK           _U_(0x9F20)                                    /**< \deprecated (OSC32KCTRL_OSCULP32K) Register MASK  (Use OSC32KCTRL_OSCULP32K_Msk instead)  */
#define OSC32KCTRL_OSCULP32K_Msk            _U_(0x9F20)                                    /**< (OSC32KCTRL_OSCULP32K) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief OSC32KCTRL hardware registers */
typedef struct {  /* 32k Oscillators Control */
  __IO OSC32KCTRL_INTENCLR_Type       INTENCLR;       /**< Offset: 0x00 (R/W  32) Interrupt Enable Clear */
  __IO OSC32KCTRL_INTENSET_Type       INTENSET;       /**< Offset: 0x04 (R/W  32) Interrupt Enable Set */
  __IO OSC32KCTRL_INTFLAG_Type        INTFLAG;        /**< Offset: 0x08 (R/W  32) Interrupt Flag Status and Clear */
  __I  OSC32KCTRL_STATUS_Type         STATUS;         /**< Offset: 0x0C (R/   32) Power and Clocks Status */
  __IO OSC32KCTRL_RTCCTRL_Type        RTCCTRL;        /**< Offset: 0x10 (R/W   8) RTC Clock Selection */
  __I  uint8_t                        Reserved1[3];
  __IO OSC32KCTRL_XOSC32K_Type        XOSC32K;        /**< Offset: 0x14 (R/W  16) 32kHz External Crystal Oscillator (XOSC32K) Control */
  __IO OSC32KCTRL_CFDCTRL_Type        CFDCTRL;        /**< Offset: 0x16 (R/W   8) Clock Failure Detector Control */
  __IO OSC32KCTRL_EVCTRL_Type         EVCTRL;         /**< Offset: 0x17 (R/W   8) Event Control */
  __I  uint8_t                        Reserved2[4];
  __IO OSC32KCTRL_OSCULP32K_Type      OSCULP32K;      /**< Offset: 0x1C (R/W  32) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */
} Osc32kctrl;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of 32k Oscillators Control */

#endif /* _SAML10_OSC32KCTRL_COMPONENT_H_ */
