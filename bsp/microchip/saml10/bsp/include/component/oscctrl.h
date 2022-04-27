/**
 * \file
 *
 * \brief Component description for OSCCTRL
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
#ifndef _SAML10_OSCCTRL_COMPONENT_H_
#define _SAML10_OSCCTRL_COMPONENT_H_
#define _SAML10_OSCCTRL_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Oscillators Control
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR OSCCTRL */
/* ========================================================================== */

#define OSCCTRL_U2119                      /**< (OSCCTRL) Module ID */
#define REV_OSCCTRL 0x400                  /**< (OSCCTRL) Module revision */

/* -------- OSCCTRL_EVCTRL : (OSCCTRL Offset: 0x00) (R/W 8) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CFDEO:1;                   /**< bit:      0  Clock Failure Detector Event Output Enable */
    uint8_t  TUNEEI:1;                  /**< bit:      1  Tune Event Input Enable                  */
    uint8_t  TUNEINV:1;                 /**< bit:      2  Tune Event Input Invert                  */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_EVCTRL_OFFSET               (0x00)                                        /**<  (OSCCTRL_EVCTRL) Event Control  Offset */
#define OSCCTRL_EVCTRL_RESETVALUE           _U_(0x00)                                     /**<  (OSCCTRL_EVCTRL) Event Control  Reset Value */

#define OSCCTRL_EVCTRL_CFDEO_Pos            0                                              /**< (OSCCTRL_EVCTRL) Clock Failure Detector Event Output Enable Position */
#define OSCCTRL_EVCTRL_CFDEO_Msk            (_U_(0x1) << OSCCTRL_EVCTRL_CFDEO_Pos)         /**< (OSCCTRL_EVCTRL) Clock Failure Detector Event Output Enable Mask */
#define OSCCTRL_EVCTRL_CFDEO                OSCCTRL_EVCTRL_CFDEO_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_EVCTRL_CFDEO_Msk instead */
#define OSCCTRL_EVCTRL_TUNEEI_Pos           1                                              /**< (OSCCTRL_EVCTRL) Tune Event Input Enable Position */
#define OSCCTRL_EVCTRL_TUNEEI_Msk           (_U_(0x1) << OSCCTRL_EVCTRL_TUNEEI_Pos)        /**< (OSCCTRL_EVCTRL) Tune Event Input Enable Mask */
#define OSCCTRL_EVCTRL_TUNEEI               OSCCTRL_EVCTRL_TUNEEI_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_EVCTRL_TUNEEI_Msk instead */
#define OSCCTRL_EVCTRL_TUNEINV_Pos          2                                              /**< (OSCCTRL_EVCTRL) Tune Event Input Invert Position */
#define OSCCTRL_EVCTRL_TUNEINV_Msk          (_U_(0x1) << OSCCTRL_EVCTRL_TUNEINV_Pos)       /**< (OSCCTRL_EVCTRL) Tune Event Input Invert Mask */
#define OSCCTRL_EVCTRL_TUNEINV              OSCCTRL_EVCTRL_TUNEINV_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_EVCTRL_TUNEINV_Msk instead */
#define OSCCTRL_EVCTRL_MASK                 _U_(0x07)                                      /**< \deprecated (OSCCTRL_EVCTRL) Register MASK  (Use OSCCTRL_EVCTRL_Msk instead)  */
#define OSCCTRL_EVCTRL_Msk                  _U_(0x07)                                      /**< (OSCCTRL_EVCTRL) Register Mask  */


/* -------- OSCCTRL_INTENCLR : (OSCCTRL Offset: 0x04) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSCRDY:1;                 /**< bit:      0  XOSC Ready Interrupt Enable              */
    uint32_t XOSCFAIL:1;                /**< bit:      1  XOSC Clock Failure Detector Interrupt Enable */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t OSC16MRDY:1;               /**< bit:      4  OSC16M Ready Interrupt Enable            */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t DFLLULPRDY:1;              /**< bit:      8  DFLLULP Ready interrupt Enable           */
    uint32_t DFLLULPLOCK:1;             /**< bit:      9  DFLLULP Lock Interrupt Enable            */
    uint32_t DFLLULPNOLOCK:1;           /**< bit:     10  DFLLULP No Lock Interrupt Enable         */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t DPLLLCKR:1;                /**< bit:     16  DPLL Lock Rise Interrupt Enable          */
    uint32_t DPLLLCKF:1;                /**< bit:     17  DPLL Lock Fall Interrupt Enable          */
    uint32_t DPLLLTO:1;                 /**< bit:     18  DPLL Lock Timeout Interrupt Enable       */
    uint32_t DPLLLDRTO:1;               /**< bit:     19  DPLL Loop Divider Ratio Update Complete Interrupt Enable */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTENCLR_OFFSET             (0x04)                                        /**<  (OSCCTRL_INTENCLR) Interrupt Enable Clear  Offset */
#define OSCCTRL_INTENCLR_RESETVALUE         _U_(0x00)                                     /**<  (OSCCTRL_INTENCLR) Interrupt Enable Clear  Reset Value */

#define OSCCTRL_INTENCLR_XOSCRDY_Pos        0                                              /**< (OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable Position */
#define OSCCTRL_INTENCLR_XOSCRDY_Msk        (_U_(0x1) << OSCCTRL_INTENCLR_XOSCRDY_Pos)     /**< (OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_XOSCRDY            OSCCTRL_INTENCLR_XOSCRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_XOSCRDY_Msk instead */
#define OSCCTRL_INTENCLR_XOSCFAIL_Pos       1                                              /**< (OSCCTRL_INTENCLR) XOSC Clock Failure Detector Interrupt Enable Position */
#define OSCCTRL_INTENCLR_XOSCFAIL_Msk       (_U_(0x1) << OSCCTRL_INTENCLR_XOSCFAIL_Pos)    /**< (OSCCTRL_INTENCLR) XOSC Clock Failure Detector Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_XOSCFAIL           OSCCTRL_INTENCLR_XOSCFAIL_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_XOSCFAIL_Msk instead */
#define OSCCTRL_INTENCLR_OSC16MRDY_Pos      4                                              /**< (OSCCTRL_INTENCLR) OSC16M Ready Interrupt Enable Position */
#define OSCCTRL_INTENCLR_OSC16MRDY_Msk      (_U_(0x1) << OSCCTRL_INTENCLR_OSC16MRDY_Pos)   /**< (OSCCTRL_INTENCLR) OSC16M Ready Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_OSC16MRDY          OSCCTRL_INTENCLR_OSC16MRDY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_OSC16MRDY_Msk instead */
#define OSCCTRL_INTENCLR_DFLLULPRDY_Pos     8                                              /**< (OSCCTRL_INTENCLR) DFLLULP Ready interrupt Enable Position */
#define OSCCTRL_INTENCLR_DFLLULPRDY_Msk     (_U_(0x1) << OSCCTRL_INTENCLR_DFLLULPRDY_Pos)  /**< (OSCCTRL_INTENCLR) DFLLULP Ready interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DFLLULPRDY         OSCCTRL_INTENCLR_DFLLULPRDY_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DFLLULPRDY_Msk instead */
#define OSCCTRL_INTENCLR_DFLLULPLOCK_Pos    9                                              /**< (OSCCTRL_INTENCLR) DFLLULP Lock Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DFLLULPLOCK_Msk    (_U_(0x1) << OSCCTRL_INTENCLR_DFLLULPLOCK_Pos)  /**< (OSCCTRL_INTENCLR) DFLLULP Lock Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DFLLULPLOCK        OSCCTRL_INTENCLR_DFLLULPLOCK_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DFLLULPLOCK_Msk instead */
#define OSCCTRL_INTENCLR_DFLLULPNOLOCK_Pos  10                                             /**< (OSCCTRL_INTENCLR) DFLLULP No Lock Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DFLLULPNOLOCK_Msk  (_U_(0x1) << OSCCTRL_INTENCLR_DFLLULPNOLOCK_Pos)  /**< (OSCCTRL_INTENCLR) DFLLULP No Lock Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DFLLULPNOLOCK      OSCCTRL_INTENCLR_DFLLULPNOLOCK_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DFLLULPNOLOCK_Msk instead */
#define OSCCTRL_INTENCLR_DPLLLCKR_Pos       16                                             /**< (OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLCKR_Msk       (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKR_Pos)    /**< (OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLCKR           OSCCTRL_INTENCLR_DPLLLCKR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DPLLLCKR_Msk instead */
#define OSCCTRL_INTENCLR_DPLLLCKF_Pos       17                                             /**< (OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLCKF_Msk       (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLCKF_Pos)    /**< (OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLCKF           OSCCTRL_INTENCLR_DPLLLCKF_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DPLLLCKF_Msk instead */
#define OSCCTRL_INTENCLR_DPLLLTO_Pos        18                                             /**< (OSCCTRL_INTENCLR) DPLL Lock Timeout Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLTO_Msk        (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLTO_Pos)     /**< (OSCCTRL_INTENCLR) DPLL Lock Timeout Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLTO            OSCCTRL_INTENCLR_DPLLLTO_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DPLLLTO_Msk instead */
#define OSCCTRL_INTENCLR_DPLLLDRTO_Pos      19                                             /**< (OSCCTRL_INTENCLR) DPLL Loop Divider Ratio Update Complete Interrupt Enable Position */
#define OSCCTRL_INTENCLR_DPLLLDRTO_Msk      (_U_(0x1) << OSCCTRL_INTENCLR_DPLLLDRTO_Pos)   /**< (OSCCTRL_INTENCLR) DPLL Loop Divider Ratio Update Complete Interrupt Enable Mask */
#define OSCCTRL_INTENCLR_DPLLLDRTO          OSCCTRL_INTENCLR_DPLLLDRTO_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENCLR_DPLLLDRTO_Msk instead */
#define OSCCTRL_INTENCLR_MASK               _U_(0xF0713)                                   /**< \deprecated (OSCCTRL_INTENCLR) Register MASK  (Use OSCCTRL_INTENCLR_Msk instead)  */
#define OSCCTRL_INTENCLR_Msk                _U_(0xF0713)                                   /**< (OSCCTRL_INTENCLR) Register Mask  */


/* -------- OSCCTRL_INTENSET : (OSCCTRL Offset: 0x08) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSCRDY:1;                 /**< bit:      0  XOSC Ready Interrupt Enable              */
    uint32_t XOSCFAIL:1;                /**< bit:      1  XOSC Clock Failure Detector Interrupt Enable */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t OSC16MRDY:1;               /**< bit:      4  OSC16M Ready Interrupt Enable            */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t DFLLULPRDY:1;              /**< bit:      8  DFLLULP Ready interrupt Enable           */
    uint32_t DFLLULPLOCK:1;             /**< bit:      9  DFLLULP Lock Interrupt Enable            */
    uint32_t DFLLULPNOLOCK:1;           /**< bit:     10  DFLLULP No Lock Interrupt Enable         */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t DPLLLCKR:1;                /**< bit:     16  DPLL Lock Rise Interrupt Enable          */
    uint32_t DPLLLCKF:1;                /**< bit:     17  DPLL Lock Fall Interrupt Enable          */
    uint32_t DPLLLTO:1;                 /**< bit:     18  DPLL Lock Timeout Interrupt Enable       */
    uint32_t DPLLLDRTO:1;               /**< bit:     19  DPLL Loop Divider Ratio Update Complete Interrupt Enable */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTENSET_OFFSET             (0x08)                                        /**<  (OSCCTRL_INTENSET) Interrupt Enable Set  Offset */
#define OSCCTRL_INTENSET_RESETVALUE         _U_(0x00)                                     /**<  (OSCCTRL_INTENSET) Interrupt Enable Set  Reset Value */

#define OSCCTRL_INTENSET_XOSCRDY_Pos        0                                              /**< (OSCCTRL_INTENSET) XOSC Ready Interrupt Enable Position */
#define OSCCTRL_INTENSET_XOSCRDY_Msk        (_U_(0x1) << OSCCTRL_INTENSET_XOSCRDY_Pos)     /**< (OSCCTRL_INTENSET) XOSC Ready Interrupt Enable Mask */
#define OSCCTRL_INTENSET_XOSCRDY            OSCCTRL_INTENSET_XOSCRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_XOSCRDY_Msk instead */
#define OSCCTRL_INTENSET_XOSCFAIL_Pos       1                                              /**< (OSCCTRL_INTENSET) XOSC Clock Failure Detector Interrupt Enable Position */
#define OSCCTRL_INTENSET_XOSCFAIL_Msk       (_U_(0x1) << OSCCTRL_INTENSET_XOSCFAIL_Pos)    /**< (OSCCTRL_INTENSET) XOSC Clock Failure Detector Interrupt Enable Mask */
#define OSCCTRL_INTENSET_XOSCFAIL           OSCCTRL_INTENSET_XOSCFAIL_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_XOSCFAIL_Msk instead */
#define OSCCTRL_INTENSET_OSC16MRDY_Pos      4                                              /**< (OSCCTRL_INTENSET) OSC16M Ready Interrupt Enable Position */
#define OSCCTRL_INTENSET_OSC16MRDY_Msk      (_U_(0x1) << OSCCTRL_INTENSET_OSC16MRDY_Pos)   /**< (OSCCTRL_INTENSET) OSC16M Ready Interrupt Enable Mask */
#define OSCCTRL_INTENSET_OSC16MRDY          OSCCTRL_INTENSET_OSC16MRDY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_OSC16MRDY_Msk instead */
#define OSCCTRL_INTENSET_DFLLULPRDY_Pos     8                                              /**< (OSCCTRL_INTENSET) DFLLULP Ready interrupt Enable Position */
#define OSCCTRL_INTENSET_DFLLULPRDY_Msk     (_U_(0x1) << OSCCTRL_INTENSET_DFLLULPRDY_Pos)  /**< (OSCCTRL_INTENSET) DFLLULP Ready interrupt Enable Mask */
#define OSCCTRL_INTENSET_DFLLULPRDY         OSCCTRL_INTENSET_DFLLULPRDY_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DFLLULPRDY_Msk instead */
#define OSCCTRL_INTENSET_DFLLULPLOCK_Pos    9                                              /**< (OSCCTRL_INTENSET) DFLLULP Lock Interrupt Enable Position */
#define OSCCTRL_INTENSET_DFLLULPLOCK_Msk    (_U_(0x1) << OSCCTRL_INTENSET_DFLLULPLOCK_Pos)  /**< (OSCCTRL_INTENSET) DFLLULP Lock Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DFLLULPLOCK        OSCCTRL_INTENSET_DFLLULPLOCK_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DFLLULPLOCK_Msk instead */
#define OSCCTRL_INTENSET_DFLLULPNOLOCK_Pos  10                                             /**< (OSCCTRL_INTENSET) DFLLULP No Lock Interrupt Enable Position */
#define OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk  (_U_(0x1) << OSCCTRL_INTENSET_DFLLULPNOLOCK_Pos)  /**< (OSCCTRL_INTENSET) DFLLULP No Lock Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DFLLULPNOLOCK      OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk instead */
#define OSCCTRL_INTENSET_DPLLLCKR_Pos       16                                             /**< (OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLCKR_Msk       (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKR_Pos)    /**< (OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLCKR           OSCCTRL_INTENSET_DPLLLCKR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DPLLLCKR_Msk instead */
#define OSCCTRL_INTENSET_DPLLLCKF_Pos       17                                             /**< (OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLCKF_Msk       (_U_(0x1) << OSCCTRL_INTENSET_DPLLLCKF_Pos)    /**< (OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLCKF           OSCCTRL_INTENSET_DPLLLCKF_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DPLLLCKF_Msk instead */
#define OSCCTRL_INTENSET_DPLLLTO_Pos        18                                             /**< (OSCCTRL_INTENSET) DPLL Lock Timeout Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLTO_Msk        (_U_(0x1) << OSCCTRL_INTENSET_DPLLLTO_Pos)     /**< (OSCCTRL_INTENSET) DPLL Lock Timeout Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLTO            OSCCTRL_INTENSET_DPLLLTO_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DPLLLTO_Msk instead */
#define OSCCTRL_INTENSET_DPLLLDRTO_Pos      19                                             /**< (OSCCTRL_INTENSET) DPLL Loop Divider Ratio Update Complete Interrupt Enable Position */
#define OSCCTRL_INTENSET_DPLLLDRTO_Msk      (_U_(0x1) << OSCCTRL_INTENSET_DPLLLDRTO_Pos)   /**< (OSCCTRL_INTENSET) DPLL Loop Divider Ratio Update Complete Interrupt Enable Mask */
#define OSCCTRL_INTENSET_DPLLLDRTO          OSCCTRL_INTENSET_DPLLLDRTO_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTENSET_DPLLLDRTO_Msk instead */
#define OSCCTRL_INTENSET_MASK               _U_(0xF0713)                                   /**< \deprecated (OSCCTRL_INTENSET) Register MASK  (Use OSCCTRL_INTENSET_Msk instead)  */
#define OSCCTRL_INTENSET_Msk                _U_(0xF0713)                                   /**< (OSCCTRL_INTENSET) Register Mask  */


/* -------- OSCCTRL_INTFLAG : (OSCCTRL Offset: 0x0c) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t XOSCRDY:1;                 /**< bit:      0  XOSC Ready                               */
    __I uint32_t XOSCFAIL:1;                /**< bit:      1  XOSC Clock Failure Detector              */
    __I uint32_t :2;                        /**< bit:   2..3  Reserved */
    __I uint32_t OSC16MRDY:1;               /**< bit:      4  OSC16M Ready                             */
    __I uint32_t :3;                        /**< bit:   5..7  Reserved */
    __I uint32_t DFLLULPRDY:1;              /**< bit:      8  DFLLULP Ready                            */
    __I uint32_t DFLLULPLOCK:1;             /**< bit:      9  DFLLULP Lock                             */
    __I uint32_t DFLLULPNOLOCK:1;           /**< bit:     10  DFLLULP No Lock                          */
    __I uint32_t :5;                        /**< bit: 11..15  Reserved */
    __I uint32_t DPLLLCKR:1;                /**< bit:     16  DPLL Lock Rise                           */
    __I uint32_t DPLLLCKF:1;                /**< bit:     17  DPLL Lock Fall                           */
    __I uint32_t DPLLLTO:1;                 /**< bit:     18  DPLL Lock Timeout                        */
    __I uint32_t DPLLLDRTO:1;               /**< bit:     19  DPLL Loop Divider Ratio Update Complete  */
    __I uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_INTFLAG_OFFSET              (0x0C)                                        /**<  (OSCCTRL_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define OSCCTRL_INTFLAG_RESETVALUE          _U_(0x00)                                     /**<  (OSCCTRL_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define OSCCTRL_INTFLAG_XOSCRDY_Pos         0                                              /**< (OSCCTRL_INTFLAG) XOSC Ready Position */
#define OSCCTRL_INTFLAG_XOSCRDY_Msk         (_U_(0x1) << OSCCTRL_INTFLAG_XOSCRDY_Pos)      /**< (OSCCTRL_INTFLAG) XOSC Ready Mask */
#define OSCCTRL_INTFLAG_XOSCRDY             OSCCTRL_INTFLAG_XOSCRDY_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_XOSCRDY_Msk instead */
#define OSCCTRL_INTFLAG_XOSCFAIL_Pos        1                                              /**< (OSCCTRL_INTFLAG) XOSC Clock Failure Detector Position */
#define OSCCTRL_INTFLAG_XOSCFAIL_Msk        (_U_(0x1) << OSCCTRL_INTFLAG_XOSCFAIL_Pos)     /**< (OSCCTRL_INTFLAG) XOSC Clock Failure Detector Mask */
#define OSCCTRL_INTFLAG_XOSCFAIL            OSCCTRL_INTFLAG_XOSCFAIL_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_XOSCFAIL_Msk instead */
#define OSCCTRL_INTFLAG_OSC16MRDY_Pos       4                                              /**< (OSCCTRL_INTFLAG) OSC16M Ready Position */
#define OSCCTRL_INTFLAG_OSC16MRDY_Msk       (_U_(0x1) << OSCCTRL_INTFLAG_OSC16MRDY_Pos)    /**< (OSCCTRL_INTFLAG) OSC16M Ready Mask */
#define OSCCTRL_INTFLAG_OSC16MRDY           OSCCTRL_INTFLAG_OSC16MRDY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_OSC16MRDY_Msk instead */
#define OSCCTRL_INTFLAG_DFLLULPRDY_Pos      8                                              /**< (OSCCTRL_INTFLAG) DFLLULP Ready Position */
#define OSCCTRL_INTFLAG_DFLLULPRDY_Msk      (_U_(0x1) << OSCCTRL_INTFLAG_DFLLULPRDY_Pos)   /**< (OSCCTRL_INTFLAG) DFLLULP Ready Mask */
#define OSCCTRL_INTFLAG_DFLLULPRDY          OSCCTRL_INTFLAG_DFLLULPRDY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DFLLULPRDY_Msk instead */
#define OSCCTRL_INTFLAG_DFLLULPLOCK_Pos     9                                              /**< (OSCCTRL_INTFLAG) DFLLULP Lock Position */
#define OSCCTRL_INTFLAG_DFLLULPLOCK_Msk     (_U_(0x1) << OSCCTRL_INTFLAG_DFLLULPLOCK_Pos)  /**< (OSCCTRL_INTFLAG) DFLLULP Lock Mask */
#define OSCCTRL_INTFLAG_DFLLULPLOCK         OSCCTRL_INTFLAG_DFLLULPLOCK_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DFLLULPLOCK_Msk instead */
#define OSCCTRL_INTFLAG_DFLLULPNOLOCK_Pos   10                                             /**< (OSCCTRL_INTFLAG) DFLLULP No Lock Position */
#define OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk   (_U_(0x1) << OSCCTRL_INTFLAG_DFLLULPNOLOCK_Pos)  /**< (OSCCTRL_INTFLAG) DFLLULP No Lock Mask */
#define OSCCTRL_INTFLAG_DFLLULPNOLOCK       OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk instead */
#define OSCCTRL_INTFLAG_DPLLLCKR_Pos        16                                             /**< (OSCCTRL_INTFLAG) DPLL Lock Rise Position */
#define OSCCTRL_INTFLAG_DPLLLCKR_Msk        (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKR_Pos)     /**< (OSCCTRL_INTFLAG) DPLL Lock Rise Mask */
#define OSCCTRL_INTFLAG_DPLLLCKR            OSCCTRL_INTFLAG_DPLLLCKR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DPLLLCKR_Msk instead */
#define OSCCTRL_INTFLAG_DPLLLCKF_Pos        17                                             /**< (OSCCTRL_INTFLAG) DPLL Lock Fall Position */
#define OSCCTRL_INTFLAG_DPLLLCKF_Msk        (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLCKF_Pos)     /**< (OSCCTRL_INTFLAG) DPLL Lock Fall Mask */
#define OSCCTRL_INTFLAG_DPLLLCKF            OSCCTRL_INTFLAG_DPLLLCKF_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DPLLLCKF_Msk instead */
#define OSCCTRL_INTFLAG_DPLLLTO_Pos         18                                             /**< (OSCCTRL_INTFLAG) DPLL Lock Timeout Position */
#define OSCCTRL_INTFLAG_DPLLLTO_Msk         (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLTO_Pos)      /**< (OSCCTRL_INTFLAG) DPLL Lock Timeout Mask */
#define OSCCTRL_INTFLAG_DPLLLTO             OSCCTRL_INTFLAG_DPLLLTO_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DPLLLTO_Msk instead */
#define OSCCTRL_INTFLAG_DPLLLDRTO_Pos       19                                             /**< (OSCCTRL_INTFLAG) DPLL Loop Divider Ratio Update Complete Position */
#define OSCCTRL_INTFLAG_DPLLLDRTO_Msk       (_U_(0x1) << OSCCTRL_INTFLAG_DPLLLDRTO_Pos)    /**< (OSCCTRL_INTFLAG) DPLL Loop Divider Ratio Update Complete Mask */
#define OSCCTRL_INTFLAG_DPLLLDRTO           OSCCTRL_INTFLAG_DPLLLDRTO_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_INTFLAG_DPLLLDRTO_Msk instead */
#define OSCCTRL_INTFLAG_MASK                _U_(0xF0713)                                   /**< \deprecated (OSCCTRL_INTFLAG) Register MASK  (Use OSCCTRL_INTFLAG_Msk instead)  */
#define OSCCTRL_INTFLAG_Msk                 _U_(0xF0713)                                   /**< (OSCCTRL_INTFLAG) Register Mask  */


/* -------- OSCCTRL_STATUS : (OSCCTRL Offset: 0x10) (R/ 32) Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t XOSCRDY:1;                 /**< bit:      0  XOSC Ready                               */
    uint32_t XOSCFAIL:1;                /**< bit:      1  XOSC Clock Failure Detector              */
    uint32_t XOSCCKSW:1;                /**< bit:      2  XOSC Clock Switch                        */
    uint32_t :1;                        /**< bit:      3  Reserved */
    uint32_t OSC16MRDY:1;               /**< bit:      4  OSC16M Ready                             */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t DFLLULPRDY:1;              /**< bit:      8  DFLLULP Ready                            */
    uint32_t DFLLULPLOCK:1;             /**< bit:      9  DFLLULP Lock                             */
    uint32_t DFLLULPNOLOCK:1;           /**< bit:     10  DFLLULP No Lock                          */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t DPLLLCKR:1;                /**< bit:     16  DPLL Lock Rise                           */
    uint32_t DPLLLCKF:1;                /**< bit:     17  DPLL Lock Fall                           */
    uint32_t DPLLTO:1;                  /**< bit:     18  DPLL Lock Timeout                        */
    uint32_t DPLLLDRTO:1;               /**< bit:     19  DPLL Loop Divider Ratio Update Complete  */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_STATUS_OFFSET               (0x10)                                        /**<  (OSCCTRL_STATUS) Status  Offset */
#define OSCCTRL_STATUS_RESETVALUE           _U_(0x00)                                     /**<  (OSCCTRL_STATUS) Status  Reset Value */

#define OSCCTRL_STATUS_XOSCRDY_Pos          0                                              /**< (OSCCTRL_STATUS) XOSC Ready Position */
#define OSCCTRL_STATUS_XOSCRDY_Msk          (_U_(0x1) << OSCCTRL_STATUS_XOSCRDY_Pos)       /**< (OSCCTRL_STATUS) XOSC Ready Mask */
#define OSCCTRL_STATUS_XOSCRDY              OSCCTRL_STATUS_XOSCRDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_XOSCRDY_Msk instead */
#define OSCCTRL_STATUS_XOSCFAIL_Pos         1                                              /**< (OSCCTRL_STATUS) XOSC Clock Failure Detector Position */
#define OSCCTRL_STATUS_XOSCFAIL_Msk         (_U_(0x1) << OSCCTRL_STATUS_XOSCFAIL_Pos)      /**< (OSCCTRL_STATUS) XOSC Clock Failure Detector Mask */
#define OSCCTRL_STATUS_XOSCFAIL             OSCCTRL_STATUS_XOSCFAIL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_XOSCFAIL_Msk instead */
#define OSCCTRL_STATUS_XOSCCKSW_Pos         2                                              /**< (OSCCTRL_STATUS) XOSC Clock Switch Position */
#define OSCCTRL_STATUS_XOSCCKSW_Msk         (_U_(0x1) << OSCCTRL_STATUS_XOSCCKSW_Pos)      /**< (OSCCTRL_STATUS) XOSC Clock Switch Mask */
#define OSCCTRL_STATUS_XOSCCKSW             OSCCTRL_STATUS_XOSCCKSW_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_XOSCCKSW_Msk instead */
#define OSCCTRL_STATUS_OSC16MRDY_Pos        4                                              /**< (OSCCTRL_STATUS) OSC16M Ready Position */
#define OSCCTRL_STATUS_OSC16MRDY_Msk        (_U_(0x1) << OSCCTRL_STATUS_OSC16MRDY_Pos)     /**< (OSCCTRL_STATUS) OSC16M Ready Mask */
#define OSCCTRL_STATUS_OSC16MRDY            OSCCTRL_STATUS_OSC16MRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_OSC16MRDY_Msk instead */
#define OSCCTRL_STATUS_DFLLULPRDY_Pos       8                                              /**< (OSCCTRL_STATUS) DFLLULP Ready Position */
#define OSCCTRL_STATUS_DFLLULPRDY_Msk       (_U_(0x1) << OSCCTRL_STATUS_DFLLULPRDY_Pos)    /**< (OSCCTRL_STATUS) DFLLULP Ready Mask */
#define OSCCTRL_STATUS_DFLLULPRDY           OSCCTRL_STATUS_DFLLULPRDY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DFLLULPRDY_Msk instead */
#define OSCCTRL_STATUS_DFLLULPLOCK_Pos      9                                              /**< (OSCCTRL_STATUS) DFLLULP Lock Position */
#define OSCCTRL_STATUS_DFLLULPLOCK_Msk      (_U_(0x1) << OSCCTRL_STATUS_DFLLULPLOCK_Pos)   /**< (OSCCTRL_STATUS) DFLLULP Lock Mask */
#define OSCCTRL_STATUS_DFLLULPLOCK          OSCCTRL_STATUS_DFLLULPLOCK_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DFLLULPLOCK_Msk instead */
#define OSCCTRL_STATUS_DFLLULPNOLOCK_Pos    10                                             /**< (OSCCTRL_STATUS) DFLLULP No Lock Position */
#define OSCCTRL_STATUS_DFLLULPNOLOCK_Msk    (_U_(0x1) << OSCCTRL_STATUS_DFLLULPNOLOCK_Pos)  /**< (OSCCTRL_STATUS) DFLLULP No Lock Mask */
#define OSCCTRL_STATUS_DFLLULPNOLOCK        OSCCTRL_STATUS_DFLLULPNOLOCK_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DFLLULPNOLOCK_Msk instead */
#define OSCCTRL_STATUS_DPLLLCKR_Pos         16                                             /**< (OSCCTRL_STATUS) DPLL Lock Rise Position */
#define OSCCTRL_STATUS_DPLLLCKR_Msk         (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKR_Pos)      /**< (OSCCTRL_STATUS) DPLL Lock Rise Mask */
#define OSCCTRL_STATUS_DPLLLCKR             OSCCTRL_STATUS_DPLLLCKR_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DPLLLCKR_Msk instead */
#define OSCCTRL_STATUS_DPLLLCKF_Pos         17                                             /**< (OSCCTRL_STATUS) DPLL Lock Fall Position */
#define OSCCTRL_STATUS_DPLLLCKF_Msk         (_U_(0x1) << OSCCTRL_STATUS_DPLLLCKF_Pos)      /**< (OSCCTRL_STATUS) DPLL Lock Fall Mask */
#define OSCCTRL_STATUS_DPLLLCKF             OSCCTRL_STATUS_DPLLLCKF_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DPLLLCKF_Msk instead */
#define OSCCTRL_STATUS_DPLLTO_Pos           18                                             /**< (OSCCTRL_STATUS) DPLL Lock Timeout Position */
#define OSCCTRL_STATUS_DPLLTO_Msk           (_U_(0x1) << OSCCTRL_STATUS_DPLLTO_Pos)        /**< (OSCCTRL_STATUS) DPLL Lock Timeout Mask */
#define OSCCTRL_STATUS_DPLLTO               OSCCTRL_STATUS_DPLLTO_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DPLLTO_Msk instead */
#define OSCCTRL_STATUS_DPLLLDRTO_Pos        19                                             /**< (OSCCTRL_STATUS) DPLL Loop Divider Ratio Update Complete Position */
#define OSCCTRL_STATUS_DPLLLDRTO_Msk        (_U_(0x1) << OSCCTRL_STATUS_DPLLLDRTO_Pos)     /**< (OSCCTRL_STATUS) DPLL Loop Divider Ratio Update Complete Mask */
#define OSCCTRL_STATUS_DPLLLDRTO            OSCCTRL_STATUS_DPLLLDRTO_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_STATUS_DPLLLDRTO_Msk instead */
#define OSCCTRL_STATUS_MASK                 _U_(0xF0717)                                   /**< \deprecated (OSCCTRL_STATUS) Register MASK  (Use OSCCTRL_STATUS_Msk instead)  */
#define OSCCTRL_STATUS_Msk                  _U_(0xF0717)                                   /**< (OSCCTRL_STATUS) Register Mask  */


/* -------- OSCCTRL_XOSCCTRL : (OSCCTRL Offset: 0x14) (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :1;                        /**< bit:      0  Reserved */
    uint16_t ENABLE:1;                  /**< bit:      1  Oscillator Enable                        */
    uint16_t XTALEN:1;                  /**< bit:      2  Crystal Oscillator Enable                */
    uint16_t CFDEN:1;                   /**< bit:      3  Clock Failure Detector Enable            */
    uint16_t SWBEN:1;                   /**< bit:      4  Xosc Clock Switch Enable                 */
    uint16_t :1;                        /**< bit:      5  Reserved */
    uint16_t RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint16_t ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
    uint16_t GAIN:3;                    /**< bit:  8..10  Oscillator Gain                          */
    uint16_t AMPGC:1;                   /**< bit:     11  Automatic Amplitude Gain Control         */
    uint16_t STARTUP:4;                 /**< bit: 12..15  Start-Up Time                            */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} OSCCTRL_XOSCCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_XOSCCTRL_OFFSET             (0x14)                                        /**<  (OSCCTRL_XOSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control  Offset */
#define OSCCTRL_XOSCCTRL_RESETVALUE         _U_(0x80)                                     /**<  (OSCCTRL_XOSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control  Reset Value */

#define OSCCTRL_XOSCCTRL_ENABLE_Pos         1                                              /**< (OSCCTRL_XOSCCTRL) Oscillator Enable Position */
#define OSCCTRL_XOSCCTRL_ENABLE_Msk         (_U_(0x1) << OSCCTRL_XOSCCTRL_ENABLE_Pos)      /**< (OSCCTRL_XOSCCTRL) Oscillator Enable Mask */
#define OSCCTRL_XOSCCTRL_ENABLE             OSCCTRL_XOSCCTRL_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_ENABLE_Msk instead */
#define OSCCTRL_XOSCCTRL_XTALEN_Pos         2                                              /**< (OSCCTRL_XOSCCTRL) Crystal Oscillator Enable Position */
#define OSCCTRL_XOSCCTRL_XTALEN_Msk         (_U_(0x1) << OSCCTRL_XOSCCTRL_XTALEN_Pos)      /**< (OSCCTRL_XOSCCTRL) Crystal Oscillator Enable Mask */
#define OSCCTRL_XOSCCTRL_XTALEN             OSCCTRL_XOSCCTRL_XTALEN_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_XTALEN_Msk instead */
#define OSCCTRL_XOSCCTRL_CFDEN_Pos          3                                              /**< (OSCCTRL_XOSCCTRL) Clock Failure Detector Enable Position */
#define OSCCTRL_XOSCCTRL_CFDEN_Msk          (_U_(0x1) << OSCCTRL_XOSCCTRL_CFDEN_Pos)       /**< (OSCCTRL_XOSCCTRL) Clock Failure Detector Enable Mask */
#define OSCCTRL_XOSCCTRL_CFDEN              OSCCTRL_XOSCCTRL_CFDEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_CFDEN_Msk instead */
#define OSCCTRL_XOSCCTRL_SWBEN_Pos          4                                              /**< (OSCCTRL_XOSCCTRL) Xosc Clock Switch Enable Position */
#define OSCCTRL_XOSCCTRL_SWBEN_Msk          (_U_(0x1) << OSCCTRL_XOSCCTRL_SWBEN_Pos)       /**< (OSCCTRL_XOSCCTRL) Xosc Clock Switch Enable Mask */
#define OSCCTRL_XOSCCTRL_SWBEN              OSCCTRL_XOSCCTRL_SWBEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_SWBEN_Msk instead */
#define OSCCTRL_XOSCCTRL_RUNSTDBY_Pos       6                                              /**< (OSCCTRL_XOSCCTRL) Run in Standby Position */
#define OSCCTRL_XOSCCTRL_RUNSTDBY_Msk       (_U_(0x1) << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos)    /**< (OSCCTRL_XOSCCTRL) Run in Standby Mask */
#define OSCCTRL_XOSCCTRL_RUNSTDBY           OSCCTRL_XOSCCTRL_RUNSTDBY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_RUNSTDBY_Msk instead */
#define OSCCTRL_XOSCCTRL_ONDEMAND_Pos       7                                              /**< (OSCCTRL_XOSCCTRL) On Demand Control Position */
#define OSCCTRL_XOSCCTRL_ONDEMAND_Msk       (_U_(0x1) << OSCCTRL_XOSCCTRL_ONDEMAND_Pos)    /**< (OSCCTRL_XOSCCTRL) On Demand Control Mask */
#define OSCCTRL_XOSCCTRL_ONDEMAND           OSCCTRL_XOSCCTRL_ONDEMAND_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_ONDEMAND_Msk instead */
#define OSCCTRL_XOSCCTRL_GAIN_Pos           8                                              /**< (OSCCTRL_XOSCCTRL) Oscillator Gain Position */
#define OSCCTRL_XOSCCTRL_GAIN_Msk           (_U_(0x7) << OSCCTRL_XOSCCTRL_GAIN_Pos)        /**< (OSCCTRL_XOSCCTRL) Oscillator Gain Mask */
#define OSCCTRL_XOSCCTRL_GAIN(value)        (OSCCTRL_XOSCCTRL_GAIN_Msk & ((value) << OSCCTRL_XOSCCTRL_GAIN_Pos))
#define OSCCTRL_XOSCCTRL_AMPGC_Pos          11                                             /**< (OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control Position */
#define OSCCTRL_XOSCCTRL_AMPGC_Msk          (_U_(0x1) << OSCCTRL_XOSCCTRL_AMPGC_Pos)       /**< (OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control Mask */
#define OSCCTRL_XOSCCTRL_AMPGC              OSCCTRL_XOSCCTRL_AMPGC_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_XOSCCTRL_AMPGC_Msk instead */
#define OSCCTRL_XOSCCTRL_STARTUP_Pos        12                                             /**< (OSCCTRL_XOSCCTRL) Start-Up Time Position */
#define OSCCTRL_XOSCCTRL_STARTUP_Msk        (_U_(0xF) << OSCCTRL_XOSCCTRL_STARTUP_Pos)     /**< (OSCCTRL_XOSCCTRL) Start-Up Time Mask */
#define OSCCTRL_XOSCCTRL_STARTUP(value)     (OSCCTRL_XOSCCTRL_STARTUP_Msk & ((value) << OSCCTRL_XOSCCTRL_STARTUP_Pos))
#define OSCCTRL_XOSCCTRL_MASK               _U_(0xFFDE)                                    /**< \deprecated (OSCCTRL_XOSCCTRL) Register MASK  (Use OSCCTRL_XOSCCTRL_Msk instead)  */
#define OSCCTRL_XOSCCTRL_Msk                _U_(0xFFDE)                                    /**< (OSCCTRL_XOSCCTRL) Register Mask  */


/* -------- OSCCTRL_CFDPRESC : (OSCCTRL Offset: 0x16) (R/W 8) Clock Failure Detector Prescaler -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CFDPRESC:3;                /**< bit:   0..2  Clock Failure Detector Prescaler         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_CFDPRESC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_CFDPRESC_OFFSET             (0x16)                                        /**<  (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler  Offset */
#define OSCCTRL_CFDPRESC_RESETVALUE         _U_(0x00)                                     /**<  (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler  Reset Value */

#define OSCCTRL_CFDPRESC_CFDPRESC_Pos       0                                              /**< (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler Position */
#define OSCCTRL_CFDPRESC_CFDPRESC_Msk       (_U_(0x7) << OSCCTRL_CFDPRESC_CFDPRESC_Pos)    /**< (OSCCTRL_CFDPRESC) Clock Failure Detector Prescaler Mask */
#define OSCCTRL_CFDPRESC_CFDPRESC(value)    (OSCCTRL_CFDPRESC_CFDPRESC_Msk & ((value) << OSCCTRL_CFDPRESC_CFDPRESC_Pos))
#define OSCCTRL_CFDPRESC_MASK               _U_(0x07)                                      /**< \deprecated (OSCCTRL_CFDPRESC) Register MASK  (Use OSCCTRL_CFDPRESC_Msk instead)  */
#define OSCCTRL_CFDPRESC_Msk                _U_(0x07)                                      /**< (OSCCTRL_CFDPRESC) Register Mask  */


/* -------- OSCCTRL_OSC16MCTRL : (OSCCTRL Offset: 0x18) (R/W 8) 16MHz Internal Oscillator (OSC16M) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  ENABLE:1;                  /**< bit:      1  Oscillator Enable                        */
    uint8_t  FSEL:2;                    /**< bit:   2..3  Oscillator Frequency Selection           */
    uint8_t  :2;                        /**< bit:   4..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint8_t  ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_OSC16MCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_OSC16MCTRL_OFFSET           (0x18)                                        /**<  (OSCCTRL_OSC16MCTRL) 16MHz Internal Oscillator (OSC16M) Control  Offset */
#define OSCCTRL_OSC16MCTRL_RESETVALUE       _U_(0x82)                                     /**<  (OSCCTRL_OSC16MCTRL) 16MHz Internal Oscillator (OSC16M) Control  Reset Value */

#define OSCCTRL_OSC16MCTRL_ENABLE_Pos       1                                              /**< (OSCCTRL_OSC16MCTRL) Oscillator Enable Position */
#define OSCCTRL_OSC16MCTRL_ENABLE_Msk       (_U_(0x1) << OSCCTRL_OSC16MCTRL_ENABLE_Pos)    /**< (OSCCTRL_OSC16MCTRL) Oscillator Enable Mask */
#define OSCCTRL_OSC16MCTRL_ENABLE           OSCCTRL_OSC16MCTRL_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_OSC16MCTRL_ENABLE_Msk instead */
#define OSCCTRL_OSC16MCTRL_FSEL_Pos         2                                              /**< (OSCCTRL_OSC16MCTRL) Oscillator Frequency Selection Position */
#define OSCCTRL_OSC16MCTRL_FSEL_Msk         (_U_(0x3) << OSCCTRL_OSC16MCTRL_FSEL_Pos)      /**< (OSCCTRL_OSC16MCTRL) Oscillator Frequency Selection Mask */
#define OSCCTRL_OSC16MCTRL_FSEL(value)      (OSCCTRL_OSC16MCTRL_FSEL_Msk & ((value) << OSCCTRL_OSC16MCTRL_FSEL_Pos))
#define   OSCCTRL_OSC16MCTRL_FSEL_4_Val     _U_(0x0)                                       /**< (OSCCTRL_OSC16MCTRL) 4MHz  */
#define   OSCCTRL_OSC16MCTRL_FSEL_8_Val     _U_(0x1)                                       /**< (OSCCTRL_OSC16MCTRL) 8MHz  */
#define   OSCCTRL_OSC16MCTRL_FSEL_12_Val    _U_(0x2)                                       /**< (OSCCTRL_OSC16MCTRL) 12MHz  */
#define   OSCCTRL_OSC16MCTRL_FSEL_16_Val    _U_(0x3)                                       /**< (OSCCTRL_OSC16MCTRL) 16MHz  */
#define OSCCTRL_OSC16MCTRL_FSEL_4           (OSCCTRL_OSC16MCTRL_FSEL_4_Val << OSCCTRL_OSC16MCTRL_FSEL_Pos)  /**< (OSCCTRL_OSC16MCTRL) 4MHz Position  */
#define OSCCTRL_OSC16MCTRL_FSEL_8           (OSCCTRL_OSC16MCTRL_FSEL_8_Val << OSCCTRL_OSC16MCTRL_FSEL_Pos)  /**< (OSCCTRL_OSC16MCTRL) 8MHz Position  */
#define OSCCTRL_OSC16MCTRL_FSEL_12          (OSCCTRL_OSC16MCTRL_FSEL_12_Val << OSCCTRL_OSC16MCTRL_FSEL_Pos)  /**< (OSCCTRL_OSC16MCTRL) 12MHz Position  */
#define OSCCTRL_OSC16MCTRL_FSEL_16          (OSCCTRL_OSC16MCTRL_FSEL_16_Val << OSCCTRL_OSC16MCTRL_FSEL_Pos)  /**< (OSCCTRL_OSC16MCTRL) 16MHz Position  */
#define OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos     6                                              /**< (OSCCTRL_OSC16MCTRL) Run in Standby Position */
#define OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk     (_U_(0x1) << OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos)  /**< (OSCCTRL_OSC16MCTRL) Run in Standby Mask */
#define OSCCTRL_OSC16MCTRL_RUNSTDBY         OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk instead */
#define OSCCTRL_OSC16MCTRL_ONDEMAND_Pos     7                                              /**< (OSCCTRL_OSC16MCTRL) On Demand Control Position */
#define OSCCTRL_OSC16MCTRL_ONDEMAND_Msk     (_U_(0x1) << OSCCTRL_OSC16MCTRL_ONDEMAND_Pos)  /**< (OSCCTRL_OSC16MCTRL) On Demand Control Mask */
#define OSCCTRL_OSC16MCTRL_ONDEMAND         OSCCTRL_OSC16MCTRL_ONDEMAND_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_OSC16MCTRL_ONDEMAND_Msk instead */
#define OSCCTRL_OSC16MCTRL_MASK             _U_(0xCE)                                      /**< \deprecated (OSCCTRL_OSC16MCTRL) Register MASK  (Use OSCCTRL_OSC16MCTRL_Msk instead)  */
#define OSCCTRL_OSC16MCTRL_Msk              _U_(0xCE)                                      /**< (OSCCTRL_OSC16MCTRL) Register Mask  */


/* -------- OSCCTRL_DFLLULPCTRL : (OSCCTRL Offset: 0x1c) (R/W 16) DFLLULP Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :1;                        /**< bit:      0  Reserved */
    uint16_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint16_t :1;                        /**< bit:      2  Reserved */
    uint16_t BINSE:1;                   /**< bit:      3  Binary Search Enable                     */
    uint16_t SAFE:1;                    /**< bit:      4  Tuner Safe Mode                          */
    uint16_t DITHER:1;                  /**< bit:      5  Tuner Dither Mode                        */
    uint16_t RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint16_t ONDEMAND:1;                /**< bit:      7  On Demand                                */
    uint16_t DIV:3;                     /**< bit:  8..10  Division Factor                          */
    uint16_t :5;                        /**< bit: 11..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPCTRL_OFFSET          (0x1C)                                        /**<  (OSCCTRL_DFLLULPCTRL) DFLLULP Control  Offset */
#define OSCCTRL_DFLLULPCTRL_RESETVALUE      _U_(0x504)                                    /**<  (OSCCTRL_DFLLULPCTRL) DFLLULP Control  Reset Value */

#define OSCCTRL_DFLLULPCTRL_ENABLE_Pos      1                                              /**< (OSCCTRL_DFLLULPCTRL) Enable Position */
#define OSCCTRL_DFLLULPCTRL_ENABLE_Msk      (_U_(0x1) << OSCCTRL_DFLLULPCTRL_ENABLE_Pos)   /**< (OSCCTRL_DFLLULPCTRL) Enable Mask */
#define OSCCTRL_DFLLULPCTRL_ENABLE          OSCCTRL_DFLLULPCTRL_ENABLE_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_ENABLE_Msk instead */
#define OSCCTRL_DFLLULPCTRL_BINSE_Pos       3                                              /**< (OSCCTRL_DFLLULPCTRL) Binary Search Enable Position */
#define OSCCTRL_DFLLULPCTRL_BINSE_Msk       (_U_(0x1) << OSCCTRL_DFLLULPCTRL_BINSE_Pos)    /**< (OSCCTRL_DFLLULPCTRL) Binary Search Enable Mask */
#define OSCCTRL_DFLLULPCTRL_BINSE           OSCCTRL_DFLLULPCTRL_BINSE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_BINSE_Msk instead */
#define OSCCTRL_DFLLULPCTRL_SAFE_Pos        4                                              /**< (OSCCTRL_DFLLULPCTRL) Tuner Safe Mode Position */
#define OSCCTRL_DFLLULPCTRL_SAFE_Msk        (_U_(0x1) << OSCCTRL_DFLLULPCTRL_SAFE_Pos)     /**< (OSCCTRL_DFLLULPCTRL) Tuner Safe Mode Mask */
#define OSCCTRL_DFLLULPCTRL_SAFE            OSCCTRL_DFLLULPCTRL_SAFE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_SAFE_Msk instead */
#define OSCCTRL_DFLLULPCTRL_DITHER_Pos      5                                              /**< (OSCCTRL_DFLLULPCTRL) Tuner Dither Mode Position */
#define OSCCTRL_DFLLULPCTRL_DITHER_Msk      (_U_(0x1) << OSCCTRL_DFLLULPCTRL_DITHER_Pos)   /**< (OSCCTRL_DFLLULPCTRL) Tuner Dither Mode Mask */
#define OSCCTRL_DFLLULPCTRL_DITHER          OSCCTRL_DFLLULPCTRL_DITHER_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_DITHER_Msk instead */
#define OSCCTRL_DFLLULPCTRL_RUNSTDBY_Pos    6                                              /**< (OSCCTRL_DFLLULPCTRL) Run in Standby Position */
#define OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk    (_U_(0x1) << OSCCTRL_DFLLULPCTRL_RUNSTDBY_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Run in Standby Mask */
#define OSCCTRL_DFLLULPCTRL_RUNSTDBY        OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk instead */
#define OSCCTRL_DFLLULPCTRL_ONDEMAND_Pos    7                                              /**< (OSCCTRL_DFLLULPCTRL) On Demand Position */
#define OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk    (_U_(0x1) << OSCCTRL_DFLLULPCTRL_ONDEMAND_Pos)  /**< (OSCCTRL_DFLLULPCTRL) On Demand Mask */
#define OSCCTRL_DFLLULPCTRL_ONDEMAND        OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk instead */
#define OSCCTRL_DFLLULPCTRL_DIV_Pos         8                                              /**< (OSCCTRL_DFLLULPCTRL) Division Factor Position */
#define OSCCTRL_DFLLULPCTRL_DIV_Msk         (_U_(0x7) << OSCCTRL_DFLLULPCTRL_DIV_Pos)      /**< (OSCCTRL_DFLLULPCTRL) Division Factor Mask */
#define OSCCTRL_DFLLULPCTRL_DIV(value)      (OSCCTRL_DFLLULPCTRL_DIV_Msk & ((value) << OSCCTRL_DFLLULPCTRL_DIV_Pos))
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV1_Val  _U_(0x0)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 1  */
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV2_Val  _U_(0x1)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 2  */
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV4_Val  _U_(0x2)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 4  */
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV8_Val  _U_(0x3)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 8  */
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV16_Val _U_(0x4)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 16  */
#define   OSCCTRL_DFLLULPCTRL_DIV_DIV32_Val _U_(0x5)                                       /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 32  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV1        (OSCCTRL_DFLLULPCTRL_DIV_DIV1_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 1 Position  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV2        (OSCCTRL_DFLLULPCTRL_DIV_DIV2_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 2 Position  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV4        (OSCCTRL_DFLLULPCTRL_DIV_DIV4_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 4 Position  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV8        (OSCCTRL_DFLLULPCTRL_DIV_DIV8_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 8 Position  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV16       (OSCCTRL_DFLLULPCTRL_DIV_DIV16_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 16 Position  */
#define OSCCTRL_DFLLULPCTRL_DIV_DIV32       (OSCCTRL_DFLLULPCTRL_DIV_DIV32_Val << OSCCTRL_DFLLULPCTRL_DIV_Pos)  /**< (OSCCTRL_DFLLULPCTRL) Frequency Divided by 32 Position  */
#define OSCCTRL_DFLLULPCTRL_MASK            _U_(0x7FA)                                     /**< \deprecated (OSCCTRL_DFLLULPCTRL) Register MASK  (Use OSCCTRL_DFLLULPCTRL_Msk instead)  */
#define OSCCTRL_DFLLULPCTRL_Msk             _U_(0x7FA)                                     /**< (OSCCTRL_DFLLULPCTRL) Register Mask  */


/* -------- OSCCTRL_DFLLULPDITHER : (OSCCTRL Offset: 0x1e) (R/W 8) DFLLULP Dither Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  STEP:3;                    /**< bit:   0..2  Dither Step                              */
    uint8_t  :1;                        /**< bit:      3  Reserved */
    uint8_t  PER:3;                     /**< bit:   4..6  Dither Period                            */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPDITHER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPDITHER_OFFSET        (0x1E)                                        /**<  (OSCCTRL_DFLLULPDITHER) DFLLULP Dither Control  Offset */
#define OSCCTRL_DFLLULPDITHER_RESETVALUE    _U_(0x00)                                     /**<  (OSCCTRL_DFLLULPDITHER) DFLLULP Dither Control  Reset Value */

#define OSCCTRL_DFLLULPDITHER_STEP_Pos      0                                              /**< (OSCCTRL_DFLLULPDITHER) Dither Step Position */
#define OSCCTRL_DFLLULPDITHER_STEP_Msk      (_U_(0x7) << OSCCTRL_DFLLULPDITHER_STEP_Pos)   /**< (OSCCTRL_DFLLULPDITHER) Dither Step Mask */
#define OSCCTRL_DFLLULPDITHER_STEP(value)   (OSCCTRL_DFLLULPDITHER_STEP_Msk & ((value) << OSCCTRL_DFLLULPDITHER_STEP_Pos))
#define   OSCCTRL_DFLLULPDITHER_STEP_STEP1_Val _U_(0x0)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 1  */
#define   OSCCTRL_DFLLULPDITHER_STEP_STEP2_Val _U_(0x1)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 2  */
#define   OSCCTRL_DFLLULPDITHER_STEP_STEP4_Val _U_(0x2)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 4  */
#define   OSCCTRL_DFLLULPDITHER_STEP_STEP8_Val _U_(0x3)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 8  */
#define OSCCTRL_DFLLULPDITHER_STEP_STEP1    (OSCCTRL_DFLLULPDITHER_STEP_STEP1_Val << OSCCTRL_DFLLULPDITHER_STEP_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 1 Position  */
#define OSCCTRL_DFLLULPDITHER_STEP_STEP2    (OSCCTRL_DFLLULPDITHER_STEP_STEP2_Val << OSCCTRL_DFLLULPDITHER_STEP_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 2 Position  */
#define OSCCTRL_DFLLULPDITHER_STEP_STEP4    (OSCCTRL_DFLLULPDITHER_STEP_STEP4_Val << OSCCTRL_DFLLULPDITHER_STEP_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 4 Position  */
#define OSCCTRL_DFLLULPDITHER_STEP_STEP8    (OSCCTRL_DFLLULPDITHER_STEP_STEP8_Val << OSCCTRL_DFLLULPDITHER_STEP_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Step = 8 Position  */
#define OSCCTRL_DFLLULPDITHER_PER_Pos       4                                              /**< (OSCCTRL_DFLLULPDITHER) Dither Period Position */
#define OSCCTRL_DFLLULPDITHER_PER_Msk       (_U_(0x7) << OSCCTRL_DFLLULPDITHER_PER_Pos)    /**< (OSCCTRL_DFLLULPDITHER) Dither Period Mask */
#define OSCCTRL_DFLLULPDITHER_PER(value)    (OSCCTRL_DFLLULPDITHER_PER_Msk & ((value) << OSCCTRL_DFLLULPDITHER_PER_Pos))
#define   OSCCTRL_DFLLULPDITHER_PER_PER1_Val _U_(0x0)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 1 Reference Clock Period  */
#define   OSCCTRL_DFLLULPDITHER_PER_PER2_Val _U_(0x1)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 2 Reference Clock Period  */
#define   OSCCTRL_DFLLULPDITHER_PER_PER4_Val _U_(0x2)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 4 Reference Clock Period  */
#define   OSCCTRL_DFLLULPDITHER_PER_PER8_Val _U_(0x3)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 8 Reference Clock Period  */
#define   OSCCTRL_DFLLULPDITHER_PER_PER16_Val _U_(0x4)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 16 Reference Clock Period  */
#define   OSCCTRL_DFLLULPDITHER_PER_PER32_Val _U_(0x5)                                       /**< (OSCCTRL_DFLLULPDITHER) Dither Over 32 Reference Clock Period  */
#define OSCCTRL_DFLLULPDITHER_PER_PER1      (OSCCTRL_DFLLULPDITHER_PER_PER1_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 1 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_PER_PER2      (OSCCTRL_DFLLULPDITHER_PER_PER2_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 2 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_PER_PER4      (OSCCTRL_DFLLULPDITHER_PER_PER4_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 4 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_PER_PER8      (OSCCTRL_DFLLULPDITHER_PER_PER8_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 8 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_PER_PER16     (OSCCTRL_DFLLULPDITHER_PER_PER16_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 16 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_PER_PER32     (OSCCTRL_DFLLULPDITHER_PER_PER32_Val << OSCCTRL_DFLLULPDITHER_PER_Pos)  /**< (OSCCTRL_DFLLULPDITHER) Dither Over 32 Reference Clock Period Position  */
#define OSCCTRL_DFLLULPDITHER_MASK          _U_(0x77)                                      /**< \deprecated (OSCCTRL_DFLLULPDITHER) Register MASK  (Use OSCCTRL_DFLLULPDITHER_Msk instead)  */
#define OSCCTRL_DFLLULPDITHER_Msk           _U_(0x77)                                      /**< (OSCCTRL_DFLLULPDITHER) Register Mask  */


/* -------- OSCCTRL_DFLLULPRREQ : (OSCCTRL Offset: 0x1f) (R/W 8) DFLLULP Read Request -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :7;                        /**< bit:   0..6  Reserved */
    uint8_t  RREQ:1;                    /**< bit:      7  Read Request                             */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPRREQ_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPRREQ_OFFSET          (0x1F)                                        /**<  (OSCCTRL_DFLLULPRREQ) DFLLULP Read Request  Offset */
#define OSCCTRL_DFLLULPRREQ_RESETVALUE      _U_(0x00)                                     /**<  (OSCCTRL_DFLLULPRREQ) DFLLULP Read Request  Reset Value */

#define OSCCTRL_DFLLULPRREQ_RREQ_Pos        7                                              /**< (OSCCTRL_DFLLULPRREQ) Read Request Position */
#define OSCCTRL_DFLLULPRREQ_RREQ_Msk        (_U_(0x1) << OSCCTRL_DFLLULPRREQ_RREQ_Pos)     /**< (OSCCTRL_DFLLULPRREQ) Read Request Mask */
#define OSCCTRL_DFLLULPRREQ_RREQ            OSCCTRL_DFLLULPRREQ_RREQ_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPRREQ_RREQ_Msk instead */
#define OSCCTRL_DFLLULPRREQ_MASK            _U_(0x80)                                      /**< \deprecated (OSCCTRL_DFLLULPRREQ) Register MASK  (Use OSCCTRL_DFLLULPRREQ_Msk instead)  */
#define OSCCTRL_DFLLULPRREQ_Msk             _U_(0x80)                                      /**< (OSCCTRL_DFLLULPRREQ) Register Mask  */


/* -------- OSCCTRL_DFLLULPDLY : (OSCCTRL Offset: 0x20) (R/W 32) DFLLULP Delay Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DELAY:8;                   /**< bit:   0..7  Delay Value                              */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPDLY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPDLY_OFFSET           (0x20)                                        /**<  (OSCCTRL_DFLLULPDLY) DFLLULP Delay Value  Offset */
#define OSCCTRL_DFLLULPDLY_RESETVALUE       _U_(0x80)                                     /**<  (OSCCTRL_DFLLULPDLY) DFLLULP Delay Value  Reset Value */

#define OSCCTRL_DFLLULPDLY_DELAY_Pos        0                                              /**< (OSCCTRL_DFLLULPDLY) Delay Value Position */
#define OSCCTRL_DFLLULPDLY_DELAY_Msk        (_U_(0xFF) << OSCCTRL_DFLLULPDLY_DELAY_Pos)    /**< (OSCCTRL_DFLLULPDLY) Delay Value Mask */
#define OSCCTRL_DFLLULPDLY_DELAY(value)     (OSCCTRL_DFLLULPDLY_DELAY_Msk & ((value) << OSCCTRL_DFLLULPDLY_DELAY_Pos))
#define OSCCTRL_DFLLULPDLY_MASK             _U_(0xFF)                                      /**< \deprecated (OSCCTRL_DFLLULPDLY) Register MASK  (Use OSCCTRL_DFLLULPDLY_Msk instead)  */
#define OSCCTRL_DFLLULPDLY_Msk              _U_(0xFF)                                      /**< (OSCCTRL_DFLLULPDLY) Register Mask  */


/* -------- OSCCTRL_DFLLULPRATIO : (OSCCTRL Offset: 0x24) (R/W 32) DFLLULP Target Ratio -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RATIO:11;                  /**< bit:  0..10  Target Tuner Ratio                       */
    uint32_t :21;                       /**< bit: 11..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPRATIO_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPRATIO_OFFSET         (0x24)                                        /**<  (OSCCTRL_DFLLULPRATIO) DFLLULP Target Ratio  Offset */
#define OSCCTRL_DFLLULPRATIO_RESETVALUE     _U_(0x00)                                     /**<  (OSCCTRL_DFLLULPRATIO) DFLLULP Target Ratio  Reset Value */

#define OSCCTRL_DFLLULPRATIO_RATIO_Pos      0                                              /**< (OSCCTRL_DFLLULPRATIO) Target Tuner Ratio Position */
#define OSCCTRL_DFLLULPRATIO_RATIO_Msk      (_U_(0x7FF) << OSCCTRL_DFLLULPRATIO_RATIO_Pos)  /**< (OSCCTRL_DFLLULPRATIO) Target Tuner Ratio Mask */
#define OSCCTRL_DFLLULPRATIO_RATIO(value)   (OSCCTRL_DFLLULPRATIO_RATIO_Msk & ((value) << OSCCTRL_DFLLULPRATIO_RATIO_Pos))
#define OSCCTRL_DFLLULPRATIO_MASK           _U_(0x7FF)                                     /**< \deprecated (OSCCTRL_DFLLULPRATIO) Register MASK  (Use OSCCTRL_DFLLULPRATIO_Msk instead)  */
#define OSCCTRL_DFLLULPRATIO_Msk            _U_(0x7FF)                                     /**< (OSCCTRL_DFLLULPRATIO) Register Mask  */


/* -------- OSCCTRL_DFLLULPSYNCBUSY : (OSCCTRL Offset: 0x28) (R/ 32) DFLLULP Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Bit Synchronization Busy          */
    uint32_t TUNE:1;                    /**< bit:      2  Tune Bit Synchronization Busy            */
    uint32_t DELAY:1;                   /**< bit:      3  Delay Register Synchronization Busy      */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_DFLLULPSYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DFLLULPSYNCBUSY_OFFSET      (0x28)                                        /**<  (OSCCTRL_DFLLULPSYNCBUSY) DFLLULP Synchronization Busy  Offset */
#define OSCCTRL_DFLLULPSYNCBUSY_RESETVALUE  _U_(0x00)                                     /**<  (OSCCTRL_DFLLULPSYNCBUSY) DFLLULP Synchronization Busy  Reset Value */

#define OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Pos  1                                              /**< (OSCCTRL_DFLLULPSYNCBUSY) Enable Bit Synchronization Busy Position */
#define OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Msk  (_U_(0x1) << OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Pos)  /**< (OSCCTRL_DFLLULPSYNCBUSY) Enable Bit Synchronization Busy Mask */
#define OSCCTRL_DFLLULPSYNCBUSY_ENABLE      OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Msk instead */
#define OSCCTRL_DFLLULPSYNCBUSY_TUNE_Pos    2                                              /**< (OSCCTRL_DFLLULPSYNCBUSY) Tune Bit Synchronization Busy Position */
#define OSCCTRL_DFLLULPSYNCBUSY_TUNE_Msk    (_U_(0x1) << OSCCTRL_DFLLULPSYNCBUSY_TUNE_Pos)  /**< (OSCCTRL_DFLLULPSYNCBUSY) Tune Bit Synchronization Busy Mask */
#define OSCCTRL_DFLLULPSYNCBUSY_TUNE        OSCCTRL_DFLLULPSYNCBUSY_TUNE_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPSYNCBUSY_TUNE_Msk instead */
#define OSCCTRL_DFLLULPSYNCBUSY_DELAY_Pos   3                                              /**< (OSCCTRL_DFLLULPSYNCBUSY) Delay Register Synchronization Busy Position */
#define OSCCTRL_DFLLULPSYNCBUSY_DELAY_Msk   (_U_(0x1) << OSCCTRL_DFLLULPSYNCBUSY_DELAY_Pos)  /**< (OSCCTRL_DFLLULPSYNCBUSY) Delay Register Synchronization Busy Mask */
#define OSCCTRL_DFLLULPSYNCBUSY_DELAY       OSCCTRL_DFLLULPSYNCBUSY_DELAY_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DFLLULPSYNCBUSY_DELAY_Msk instead */
#define OSCCTRL_DFLLULPSYNCBUSY_MASK        _U_(0x0E)                                      /**< \deprecated (OSCCTRL_DFLLULPSYNCBUSY) Register MASK  (Use OSCCTRL_DFLLULPSYNCBUSY_Msk instead)  */
#define OSCCTRL_DFLLULPSYNCBUSY_Msk         _U_(0x0E)                                      /**< (OSCCTRL_DFLLULPSYNCBUSY) Register Mask  */


/* -------- OSCCTRL_DPLLCTRLA : (OSCCTRL Offset: 0x2c) (R/W 8) DPLL Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  ENABLE:1;                  /**< bit:      1  DPLL Enable                              */
    uint8_t  :4;                        /**< bit:   2..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint8_t  ONDEMAND:1;                /**< bit:      7  On Demand Clock Activation               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DPLLCTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLCTRLA_OFFSET            (0x2C)                                        /**<  (OSCCTRL_DPLLCTRLA) DPLL Control A  Offset */
#define OSCCTRL_DPLLCTRLA_RESETVALUE        _U_(0x80)                                     /**<  (OSCCTRL_DPLLCTRLA) DPLL Control A  Reset Value */

#define OSCCTRL_DPLLCTRLA_ENABLE_Pos        1                                              /**< (OSCCTRL_DPLLCTRLA) DPLL Enable Position */
#define OSCCTRL_DPLLCTRLA_ENABLE_Msk        (_U_(0x1) << OSCCTRL_DPLLCTRLA_ENABLE_Pos)     /**< (OSCCTRL_DPLLCTRLA) DPLL Enable Mask */
#define OSCCTRL_DPLLCTRLA_ENABLE            OSCCTRL_DPLLCTRLA_ENABLE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLA_ENABLE_Msk instead */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos      6                                              /**< (OSCCTRL_DPLLCTRLA) Run in Standby Position */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk      (_U_(0x1) << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos)   /**< (OSCCTRL_DPLLCTRLA) Run in Standby Mask */
#define OSCCTRL_DPLLCTRLA_RUNSTDBY          OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk instead */
#define OSCCTRL_DPLLCTRLA_ONDEMAND_Pos      7                                              /**< (OSCCTRL_DPLLCTRLA) On Demand Clock Activation Position */
#define OSCCTRL_DPLLCTRLA_ONDEMAND_Msk      (_U_(0x1) << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos)   /**< (OSCCTRL_DPLLCTRLA) On Demand Clock Activation Mask */
#define OSCCTRL_DPLLCTRLA_ONDEMAND          OSCCTRL_DPLLCTRLA_ONDEMAND_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLA_ONDEMAND_Msk instead */
#define OSCCTRL_DPLLCTRLA_MASK              _U_(0xC2)                                      /**< \deprecated (OSCCTRL_DPLLCTRLA) Register MASK  (Use OSCCTRL_DPLLCTRLA_Msk instead)  */
#define OSCCTRL_DPLLCTRLA_Msk               _U_(0xC2)                                      /**< (OSCCTRL_DPLLCTRLA) Register Mask  */


/* -------- OSCCTRL_DPLLRATIO : (OSCCTRL Offset: 0x30) (R/W 32) DPLL Ratio Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t LDR:12;                    /**< bit:  0..11  Loop Divider Ratio                       */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t LDRFRAC:4;                 /**< bit: 16..19  Loop Divider Ratio Fractional Part       */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_DPLLRATIO_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLRATIO_OFFSET            (0x30)                                        /**<  (OSCCTRL_DPLLRATIO) DPLL Ratio Control  Offset */
#define OSCCTRL_DPLLRATIO_RESETVALUE        _U_(0x00)                                     /**<  (OSCCTRL_DPLLRATIO) DPLL Ratio Control  Reset Value */

#define OSCCTRL_DPLLRATIO_LDR_Pos           0                                              /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Position */
#define OSCCTRL_DPLLRATIO_LDR_Msk           (_U_(0xFFF) << OSCCTRL_DPLLRATIO_LDR_Pos)      /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Mask */
#define OSCCTRL_DPLLRATIO_LDR(value)        (OSCCTRL_DPLLRATIO_LDR_Msk & ((value) << OSCCTRL_DPLLRATIO_LDR_Pos))
#define OSCCTRL_DPLLRATIO_LDRFRAC_Pos       16                                             /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part Position */
#define OSCCTRL_DPLLRATIO_LDRFRAC_Msk       (_U_(0xF) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos)    /**< (OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part Mask */
#define OSCCTRL_DPLLRATIO_LDRFRAC(value)    (OSCCTRL_DPLLRATIO_LDRFRAC_Msk & ((value) << OSCCTRL_DPLLRATIO_LDRFRAC_Pos))
#define OSCCTRL_DPLLRATIO_MASK              _U_(0xF0FFF)                                   /**< \deprecated (OSCCTRL_DPLLRATIO) Register MASK  (Use OSCCTRL_DPLLRATIO_Msk instead)  */
#define OSCCTRL_DPLLRATIO_Msk               _U_(0xF0FFF)                                   /**< (OSCCTRL_DPLLRATIO) Register Mask  */


/* -------- OSCCTRL_DPLLCTRLB : (OSCCTRL Offset: 0x34) (R/W 32) DPLL Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FILTER:2;                  /**< bit:   0..1  Proportional Integral Filter Selection   */
    uint32_t LPEN:1;                    /**< bit:      2  Low-Power Enable                         */
    uint32_t WUF:1;                     /**< bit:      3  Wake Up Fast                             */
    uint32_t REFCLK:2;                  /**< bit:   4..5  Reference Clock Selection                */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t LTIME:3;                   /**< bit:  8..10  Lock Time                                */
    uint32_t :1;                        /**< bit:     11  Reserved */
    uint32_t LBYPASS:1;                 /**< bit:     12  Lock Bypass                              */
    uint32_t :3;                        /**< bit: 13..15  Reserved */
    uint32_t DIV:11;                    /**< bit: 16..26  Clock Divider                            */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OSCCTRL_DPLLCTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLCTRLB_OFFSET            (0x34)                                        /**<  (OSCCTRL_DPLLCTRLB) DPLL Control B  Offset */
#define OSCCTRL_DPLLCTRLB_RESETVALUE        _U_(0x00)                                     /**<  (OSCCTRL_DPLLCTRLB) DPLL Control B  Reset Value */

#define OSCCTRL_DPLLCTRLB_FILTER_Pos        0                                              /**< (OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection Position */
#define OSCCTRL_DPLLCTRLB_FILTER_Msk        (_U_(0x3) << OSCCTRL_DPLLCTRLB_FILTER_Pos)     /**< (OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection Mask */
#define OSCCTRL_DPLLCTRLB_FILTER(value)     (OSCCTRL_DPLLCTRLB_FILTER_Msk & ((value) << OSCCTRL_DPLLCTRLB_FILTER_Pos))
#define   OSCCTRL_DPLLCTRLB_FILTER_Default_Val _U_(0x0)                                       /**< (OSCCTRL_DPLLCTRLB) Default Filter Mode  */
#define   OSCCTRL_DPLLCTRLB_FILTER_LBFILT_Val _U_(0x1)                                       /**< (OSCCTRL_DPLLCTRLB) Low Bandwidth Filter  */
#define   OSCCTRL_DPLLCTRLB_FILTER_HBFILT_Val _U_(0x2)                                       /**< (OSCCTRL_DPLLCTRLB) High Bandwidth Filter  */
#define   OSCCTRL_DPLLCTRLB_FILTER_HDFILT_Val _U_(0x3)                                       /**< (OSCCTRL_DPLLCTRLB) High Damping Filter  */
#define OSCCTRL_DPLLCTRLB_FILTER_Default    (OSCCTRL_DPLLCTRLB_FILTER_Default_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos)  /**< (OSCCTRL_DPLLCTRLB) Default Filter Mode Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_LBFILT     (OSCCTRL_DPLLCTRLB_FILTER_LBFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos)  /**< (OSCCTRL_DPLLCTRLB) Low Bandwidth Filter Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_HBFILT     (OSCCTRL_DPLLCTRLB_FILTER_HBFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos)  /**< (OSCCTRL_DPLLCTRLB) High Bandwidth Filter Position  */
#define OSCCTRL_DPLLCTRLB_FILTER_HDFILT     (OSCCTRL_DPLLCTRLB_FILTER_HDFILT_Val << OSCCTRL_DPLLCTRLB_FILTER_Pos)  /**< (OSCCTRL_DPLLCTRLB) High Damping Filter Position  */
#define OSCCTRL_DPLLCTRLB_LPEN_Pos          2                                              /**< (OSCCTRL_DPLLCTRLB) Low-Power Enable Position */
#define OSCCTRL_DPLLCTRLB_LPEN_Msk          (_U_(0x1) << OSCCTRL_DPLLCTRLB_LPEN_Pos)       /**< (OSCCTRL_DPLLCTRLB) Low-Power Enable Mask */
#define OSCCTRL_DPLLCTRLB_LPEN              OSCCTRL_DPLLCTRLB_LPEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLB_LPEN_Msk instead */
#define OSCCTRL_DPLLCTRLB_WUF_Pos           3                                              /**< (OSCCTRL_DPLLCTRLB) Wake Up Fast Position */
#define OSCCTRL_DPLLCTRLB_WUF_Msk           (_U_(0x1) << OSCCTRL_DPLLCTRLB_WUF_Pos)        /**< (OSCCTRL_DPLLCTRLB) Wake Up Fast Mask */
#define OSCCTRL_DPLLCTRLB_WUF               OSCCTRL_DPLLCTRLB_WUF_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLB_WUF_Msk instead */
#define OSCCTRL_DPLLCTRLB_REFCLK_Pos        4                                              /**< (OSCCTRL_DPLLCTRLB) Reference Clock Selection Position */
#define OSCCTRL_DPLLCTRLB_REFCLK_Msk        (_U_(0x3) << OSCCTRL_DPLLCTRLB_REFCLK_Pos)     /**< (OSCCTRL_DPLLCTRLB) Reference Clock Selection Mask */
#define OSCCTRL_DPLLCTRLB_REFCLK(value)     (OSCCTRL_DPLLCTRLB_REFCLK_Msk & ((value) << OSCCTRL_DPLLCTRLB_REFCLK_Pos))
#define   OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K_Val _U_(0x0)                                       /**< (OSCCTRL_DPLLCTRLB) XOSC32K Clock Reference  */
#define   OSCCTRL_DPLLCTRLB_REFCLK_XOSC_Val _U_(0x1)                                       /**< (OSCCTRL_DPLLCTRLB) XOSC Clock Reference  */
#define   OSCCTRL_DPLLCTRLB_REFCLK_GCLK_Val _U_(0x2)                                       /**< (OSCCTRL_DPLLCTRLB) GCLK Clock Reference  */
#define OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K    (OSCCTRL_DPLLCTRLB_REFCLK_XOSC32K_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos)  /**< (OSCCTRL_DPLLCTRLB) XOSC32K Clock Reference Position  */
#define OSCCTRL_DPLLCTRLB_REFCLK_XOSC       (OSCCTRL_DPLLCTRLB_REFCLK_XOSC_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos)  /**< (OSCCTRL_DPLLCTRLB) XOSC Clock Reference Position  */
#define OSCCTRL_DPLLCTRLB_REFCLK_GCLK       (OSCCTRL_DPLLCTRLB_REFCLK_GCLK_Val << OSCCTRL_DPLLCTRLB_REFCLK_Pos)  /**< (OSCCTRL_DPLLCTRLB) GCLK Clock Reference Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_Pos         8                                              /**< (OSCCTRL_DPLLCTRLB) Lock Time Position */
#define OSCCTRL_DPLLCTRLB_LTIME_Msk         (_U_(0x7) << OSCCTRL_DPLLCTRLB_LTIME_Pos)      /**< (OSCCTRL_DPLLCTRLB) Lock Time Mask */
#define OSCCTRL_DPLLCTRLB_LTIME(value)      (OSCCTRL_DPLLCTRLB_LTIME_Msk & ((value) << OSCCTRL_DPLLCTRLB_LTIME_Pos))
#define   OSCCTRL_DPLLCTRLB_LTIME_Default_Val _U_(0x0)                                       /**< (OSCCTRL_DPLLCTRLB) No time-out. Automatic lock  */
#define   OSCCTRL_DPLLCTRLB_LTIME_8MS_Val   _U_(0x4)                                       /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 8 ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_9MS_Val   _U_(0x5)                                       /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 9 ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_10MS_Val  _U_(0x6)                                       /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 10 ms  */
#define   OSCCTRL_DPLLCTRLB_LTIME_11MS_Val  _U_(0x7)                                       /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 11 ms  */
#define OSCCTRL_DPLLCTRLB_LTIME_Default     (OSCCTRL_DPLLCTRLB_LTIME_Default_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos)  /**< (OSCCTRL_DPLLCTRLB) No time-out. Automatic lock Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_8MS         (OSCCTRL_DPLLCTRLB_LTIME_8MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos)  /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 8 ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_9MS         (OSCCTRL_DPLLCTRLB_LTIME_9MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos)  /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 9 ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_10MS        (OSCCTRL_DPLLCTRLB_LTIME_10MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos)  /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 10 ms Position  */
#define OSCCTRL_DPLLCTRLB_LTIME_11MS        (OSCCTRL_DPLLCTRLB_LTIME_11MS_Val << OSCCTRL_DPLLCTRLB_LTIME_Pos)  /**< (OSCCTRL_DPLLCTRLB) Time-out if no lock within 11 ms Position  */
#define OSCCTRL_DPLLCTRLB_LBYPASS_Pos       12                                             /**< (OSCCTRL_DPLLCTRLB) Lock Bypass Position */
#define OSCCTRL_DPLLCTRLB_LBYPASS_Msk       (_U_(0x1) << OSCCTRL_DPLLCTRLB_LBYPASS_Pos)    /**< (OSCCTRL_DPLLCTRLB) Lock Bypass Mask */
#define OSCCTRL_DPLLCTRLB_LBYPASS           OSCCTRL_DPLLCTRLB_LBYPASS_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLCTRLB_LBYPASS_Msk instead */
#define OSCCTRL_DPLLCTRLB_DIV_Pos           16                                             /**< (OSCCTRL_DPLLCTRLB) Clock Divider Position */
#define OSCCTRL_DPLLCTRLB_DIV_Msk           (_U_(0x7FF) << OSCCTRL_DPLLCTRLB_DIV_Pos)      /**< (OSCCTRL_DPLLCTRLB) Clock Divider Mask */
#define OSCCTRL_DPLLCTRLB_DIV(value)        (OSCCTRL_DPLLCTRLB_DIV_Msk & ((value) << OSCCTRL_DPLLCTRLB_DIV_Pos))
#define OSCCTRL_DPLLCTRLB_MASK              _U_(0x7FF173F)                                 /**< \deprecated (OSCCTRL_DPLLCTRLB) Register MASK  (Use OSCCTRL_DPLLCTRLB_Msk instead)  */
#define OSCCTRL_DPLLCTRLB_Msk               _U_(0x7FF173F)                                 /**< (OSCCTRL_DPLLCTRLB) Register Mask  */


/* -------- OSCCTRL_DPLLPRESC : (OSCCTRL Offset: 0x38) (R/W 8) DPLL Prescaler -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PRESC:2;                   /**< bit:   0..1  Output Clock Prescaler                   */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DPLLPRESC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLPRESC_OFFSET            (0x38)                                        /**<  (OSCCTRL_DPLLPRESC) DPLL Prescaler  Offset */
#define OSCCTRL_DPLLPRESC_RESETVALUE        _U_(0x00)                                     /**<  (OSCCTRL_DPLLPRESC) DPLL Prescaler  Reset Value */

#define OSCCTRL_DPLLPRESC_PRESC_Pos         0                                              /**< (OSCCTRL_DPLLPRESC) Output Clock Prescaler Position */
#define OSCCTRL_DPLLPRESC_PRESC_Msk         (_U_(0x3) << OSCCTRL_DPLLPRESC_PRESC_Pos)      /**< (OSCCTRL_DPLLPRESC) Output Clock Prescaler Mask */
#define OSCCTRL_DPLLPRESC_PRESC(value)      (OSCCTRL_DPLLPRESC_PRESC_Msk & ((value) << OSCCTRL_DPLLPRESC_PRESC_Pos))
#define   OSCCTRL_DPLLPRESC_PRESC_DIV1_Val  _U_(0x0)                                       /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 1  */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV2_Val  _U_(0x1)                                       /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 2  */
#define   OSCCTRL_DPLLPRESC_PRESC_DIV4_Val  _U_(0x2)                                       /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 4  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV1        (OSCCTRL_DPLLPRESC_PRESC_DIV1_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)  /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 1 Position  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV2        (OSCCTRL_DPLLPRESC_PRESC_DIV2_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)  /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 2 Position  */
#define OSCCTRL_DPLLPRESC_PRESC_DIV4        (OSCCTRL_DPLLPRESC_PRESC_DIV4_Val << OSCCTRL_DPLLPRESC_PRESC_Pos)  /**< (OSCCTRL_DPLLPRESC) DPLL output is divided by 4 Position  */
#define OSCCTRL_DPLLPRESC_MASK              _U_(0x03)                                      /**< \deprecated (OSCCTRL_DPLLPRESC) Register MASK  (Use OSCCTRL_DPLLPRESC_Msk instead)  */
#define OSCCTRL_DPLLPRESC_Msk               _U_(0x03)                                      /**< (OSCCTRL_DPLLPRESC) Register Mask  */


/* -------- OSCCTRL_DPLLSYNCBUSY : (OSCCTRL Offset: 0x3c) (R/ 8) DPLL Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  ENABLE:1;                  /**< bit:      1  DPLL Enable Synchronization Status       */
    uint8_t  DPLLRATIO:1;               /**< bit:      2  DPLL Loop Divider Ratio Synchronization Status */
    uint8_t  DPLLPRESC:1;               /**< bit:      3  DPLL Prescaler Synchronization Status    */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DPLLSYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLSYNCBUSY_OFFSET         (0x3C)                                        /**<  (OSCCTRL_DPLLSYNCBUSY) DPLL Synchronization Busy  Offset */
#define OSCCTRL_DPLLSYNCBUSY_RESETVALUE     _U_(0x00)                                     /**<  (OSCCTRL_DPLLSYNCBUSY) DPLL Synchronization Busy  Reset Value */

#define OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos     1                                              /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk     (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos)  /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_ENABLE         OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk instead */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos  2                                              /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Loop Divider Ratio Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk  (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos)  /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Loop Divider Ratio Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_DPLLRATIO      OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk instead */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos  3                                              /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status Position */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk  (_U_(0x1) << OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos)  /**< (OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status Mask */
#define OSCCTRL_DPLLSYNCBUSY_DPLLPRESC      OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk instead */
#define OSCCTRL_DPLLSYNCBUSY_MASK           _U_(0x0E)                                      /**< \deprecated (OSCCTRL_DPLLSYNCBUSY) Register MASK  (Use OSCCTRL_DPLLSYNCBUSY_Msk instead)  */
#define OSCCTRL_DPLLSYNCBUSY_Msk            _U_(0x0E)                                      /**< (OSCCTRL_DPLLSYNCBUSY) Register Mask  */


/* -------- OSCCTRL_DPLLSTATUS : (OSCCTRL Offset: 0x40) (R/ 8) DPLL Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  LOCK:1;                    /**< bit:      0  DPLL Lock                                */
    uint8_t  CLKRDY:1;                  /**< bit:      1  DPLL Clock Ready                         */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OSCCTRL_DPLLSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OSCCTRL_DPLLSTATUS_OFFSET           (0x40)                                        /**<  (OSCCTRL_DPLLSTATUS) DPLL Status  Offset */
#define OSCCTRL_DPLLSTATUS_RESETVALUE       _U_(0x00)                                     /**<  (OSCCTRL_DPLLSTATUS) DPLL Status  Reset Value */

#define OSCCTRL_DPLLSTATUS_LOCK_Pos         0                                              /**< (OSCCTRL_DPLLSTATUS) DPLL Lock Position */
#define OSCCTRL_DPLLSTATUS_LOCK_Msk         (_U_(0x1) << OSCCTRL_DPLLSTATUS_LOCK_Pos)      /**< (OSCCTRL_DPLLSTATUS) DPLL Lock Mask */
#define OSCCTRL_DPLLSTATUS_LOCK             OSCCTRL_DPLLSTATUS_LOCK_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLSTATUS_LOCK_Msk instead */
#define OSCCTRL_DPLLSTATUS_CLKRDY_Pos       1                                              /**< (OSCCTRL_DPLLSTATUS) DPLL Clock Ready Position */
#define OSCCTRL_DPLLSTATUS_CLKRDY_Msk       (_U_(0x1) << OSCCTRL_DPLLSTATUS_CLKRDY_Pos)    /**< (OSCCTRL_DPLLSTATUS) DPLL Clock Ready Mask */
#define OSCCTRL_DPLLSTATUS_CLKRDY           OSCCTRL_DPLLSTATUS_CLKRDY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use OSCCTRL_DPLLSTATUS_CLKRDY_Msk instead */
#define OSCCTRL_DPLLSTATUS_MASK             _U_(0x03)                                      /**< \deprecated (OSCCTRL_DPLLSTATUS) Register MASK  (Use OSCCTRL_DPLLSTATUS_Msk instead)  */
#define OSCCTRL_DPLLSTATUS_Msk              _U_(0x03)                                      /**< (OSCCTRL_DPLLSTATUS) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief OSCCTRL hardware registers */
typedef struct {  /* Oscillators Control */
  __IO OSCCTRL_EVCTRL_Type            EVCTRL;         /**< Offset: 0x00 (R/W   8) Event Control */
  __I  uint8_t                        Reserved1[3];
  __IO OSCCTRL_INTENCLR_Type          INTENCLR;       /**< Offset: 0x04 (R/W  32) Interrupt Enable Clear */
  __IO OSCCTRL_INTENSET_Type          INTENSET;       /**< Offset: 0x08 (R/W  32) Interrupt Enable Set */
  __IO OSCCTRL_INTFLAG_Type           INTFLAG;        /**< Offset: 0x0C (R/W  32) Interrupt Flag Status and Clear */
  __I  OSCCTRL_STATUS_Type            STATUS;         /**< Offset: 0x10 (R/   32) Status */
  __IO OSCCTRL_XOSCCTRL_Type          XOSCCTRL;       /**< Offset: 0x14 (R/W  16) External Multipurpose Crystal Oscillator (XOSC) Control */
  __IO OSCCTRL_CFDPRESC_Type          CFDPRESC;       /**< Offset: 0x16 (R/W   8) Clock Failure Detector Prescaler */
  __I  uint8_t                        Reserved2[1];
  __IO OSCCTRL_OSC16MCTRL_Type        OSC16MCTRL;     /**< Offset: 0x18 (R/W   8) 16MHz Internal Oscillator (OSC16M) Control */
  __I  uint8_t                        Reserved3[3];
  __IO OSCCTRL_DFLLULPCTRL_Type       DFLLULPCTRL;    /**< Offset: 0x1C (R/W  16) DFLLULP Control */
  __IO OSCCTRL_DFLLULPDITHER_Type     DFLLULPDITHER;  /**< Offset: 0x1E (R/W   8) DFLLULP Dither Control */
  __IO OSCCTRL_DFLLULPRREQ_Type       DFLLULPRREQ;    /**< Offset: 0x1F (R/W   8) DFLLULP Read Request */
  __IO OSCCTRL_DFLLULPDLY_Type        DFLLULPDLY;     /**< Offset: 0x20 (R/W  32) DFLLULP Delay Value */
  __IO OSCCTRL_DFLLULPRATIO_Type      DFLLULPRATIO;   /**< Offset: 0x24 (R/W  32) DFLLULP Target Ratio */
  __I  OSCCTRL_DFLLULPSYNCBUSY_Type   DFLLULPSYNCBUSY; /**< Offset: 0x28 (R/   32) DFLLULP Synchronization Busy */
  __IO OSCCTRL_DPLLCTRLA_Type         DPLLCTRLA;      /**< Offset: 0x2C (R/W   8) DPLL Control A */
  __I  uint8_t                        Reserved4[3];
  __IO OSCCTRL_DPLLRATIO_Type         DPLLRATIO;      /**< Offset: 0x30 (R/W  32) DPLL Ratio Control */
  __IO OSCCTRL_DPLLCTRLB_Type         DPLLCTRLB;      /**< Offset: 0x34 (R/W  32) DPLL Control B */
  __IO OSCCTRL_DPLLPRESC_Type         DPLLPRESC;      /**< Offset: 0x38 (R/W   8) DPLL Prescaler */
  __I  uint8_t                        Reserved5[3];
  __I  OSCCTRL_DPLLSYNCBUSY_Type      DPLLSYNCBUSY;   /**< Offset: 0x3C (R/    8) DPLL Synchronization Busy */
  __I  uint8_t                        Reserved6[3];
  __I  OSCCTRL_DPLLSTATUS_Type        DPLLSTATUS;     /**< Offset: 0x40 (R/    8) DPLL Status */
} Oscctrl;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Oscillators Control */

#endif /* _SAML10_OSCCTRL_COMPONENT_H_ */
