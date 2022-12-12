/**
 * \file
 *
 * \brief Component description for WDT
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
#ifndef _SAML10_WDT_COMPONENT_H_
#define _SAML10_WDT_COMPONENT_H_
#define _SAML10_WDT_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Watchdog Timer
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR WDT */
/* ========================================================================== */

#define WDT_U2251                      /**< (WDT) Module ID */
#define REV_WDT 0x200                  /**< (WDT) Module revision */

/* -------- WDT_CTRLA : (WDT Offset: 0x00) (R/W 8) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  WEN:1;                     /**< bit:      2  Watchdog Timer Window Mode Enable        */
    uint8_t  :3;                        /**< bit:   3..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run During Standby                       */
    uint8_t  ALWAYSON:1;                /**< bit:      7  Always-On                                */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_CTRLA_OFFSET                    (0x00)                                        /**<  (WDT_CTRLA) Control  Offset */
#define WDT_CTRLA_RESETVALUE                _U_(0x00)                                     /**<  (WDT_CTRLA) Control  Reset Value */

#define WDT_CTRLA_ENABLE_Pos                1                                              /**< (WDT_CTRLA) Enable Position */
#define WDT_CTRLA_ENABLE_Msk                (_U_(0x1) << WDT_CTRLA_ENABLE_Pos)             /**< (WDT_CTRLA) Enable Mask */
#define WDT_CTRLA_ENABLE                    WDT_CTRLA_ENABLE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_CTRLA_ENABLE_Msk instead */
#define WDT_CTRLA_WEN_Pos                   2                                              /**< (WDT_CTRLA) Watchdog Timer Window Mode Enable Position */
#define WDT_CTRLA_WEN_Msk                   (_U_(0x1) << WDT_CTRLA_WEN_Pos)                /**< (WDT_CTRLA) Watchdog Timer Window Mode Enable Mask */
#define WDT_CTRLA_WEN                       WDT_CTRLA_WEN_Msk                              /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_CTRLA_WEN_Msk instead */
#define WDT_CTRLA_RUNSTDBY_Pos              6                                              /**< (WDT_CTRLA) Run During Standby Position */
#define WDT_CTRLA_RUNSTDBY_Msk              (_U_(0x1) << WDT_CTRLA_RUNSTDBY_Pos)           /**< (WDT_CTRLA) Run During Standby Mask */
#define WDT_CTRLA_RUNSTDBY                  WDT_CTRLA_RUNSTDBY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_CTRLA_RUNSTDBY_Msk instead */
#define WDT_CTRLA_ALWAYSON_Pos              7                                              /**< (WDT_CTRLA) Always-On Position */
#define WDT_CTRLA_ALWAYSON_Msk              (_U_(0x1) << WDT_CTRLA_ALWAYSON_Pos)           /**< (WDT_CTRLA) Always-On Mask */
#define WDT_CTRLA_ALWAYSON                  WDT_CTRLA_ALWAYSON_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_CTRLA_ALWAYSON_Msk instead */
#define WDT_CTRLA_MASK                      _U_(0xC6)                                      /**< \deprecated (WDT_CTRLA) Register MASK  (Use WDT_CTRLA_Msk instead)  */
#define WDT_CTRLA_Msk                       _U_(0xC6)                                      /**< (WDT_CTRLA) Register Mask  */


/* -------- WDT_CONFIG : (WDT Offset: 0x01) (R/W 8) Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PER:4;                     /**< bit:   0..3  Time-Out Period                          */
    uint8_t  WINDOW:4;                  /**< bit:   4..7  Window Mode Time-Out Period              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_CONFIG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_CONFIG_OFFSET                   (0x01)                                        /**<  (WDT_CONFIG) Configuration  Offset */
#define WDT_CONFIG_RESETVALUE               _U_(0xBB)                                     /**<  (WDT_CONFIG) Configuration  Reset Value */

#define WDT_CONFIG_PER_Pos                  0                                              /**< (WDT_CONFIG) Time-Out Period Position */
#define WDT_CONFIG_PER_Msk                  (_U_(0xF) << WDT_CONFIG_PER_Pos)               /**< (WDT_CONFIG) Time-Out Period Mask */
#define WDT_CONFIG_PER(value)               (WDT_CONFIG_PER_Msk & ((value) << WDT_CONFIG_PER_Pos))
#define   WDT_CONFIG_PER_CYC8_Val           _U_(0x0)                                       /**< (WDT_CONFIG) 8 clock cycles  */
#define   WDT_CONFIG_PER_CYC16_Val          _U_(0x1)                                       /**< (WDT_CONFIG) 16 clock cycles  */
#define   WDT_CONFIG_PER_CYC32_Val          _U_(0x2)                                       /**< (WDT_CONFIG) 32 clock cycles  */
#define   WDT_CONFIG_PER_CYC64_Val          _U_(0x3)                                       /**< (WDT_CONFIG) 64 clock cycles  */
#define   WDT_CONFIG_PER_CYC128_Val         _U_(0x4)                                       /**< (WDT_CONFIG) 128 clock cycles  */
#define   WDT_CONFIG_PER_CYC256_Val         _U_(0x5)                                       /**< (WDT_CONFIG) 256 clock cycles  */
#define   WDT_CONFIG_PER_CYC512_Val         _U_(0x6)                                       /**< (WDT_CONFIG) 512 clock cycles  */
#define   WDT_CONFIG_PER_CYC1024_Val        _U_(0x7)                                       /**< (WDT_CONFIG) 1024 clock cycles  */
#define   WDT_CONFIG_PER_CYC2048_Val        _U_(0x8)                                       /**< (WDT_CONFIG) 2048 clock cycles  */
#define   WDT_CONFIG_PER_CYC4096_Val        _U_(0x9)                                       /**< (WDT_CONFIG) 4096 clock cycles  */
#define   WDT_CONFIG_PER_CYC8192_Val        _U_(0xA)                                       /**< (WDT_CONFIG) 8192 clock cycles  */
#define   WDT_CONFIG_PER_CYC16384_Val       _U_(0xB)                                       /**< (WDT_CONFIG) 16384 clock cycles  */
#define WDT_CONFIG_PER_CYC8                 (WDT_CONFIG_PER_CYC8_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 8 clock cycles Position  */
#define WDT_CONFIG_PER_CYC16                (WDT_CONFIG_PER_CYC16_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 16 clock cycles Position  */
#define WDT_CONFIG_PER_CYC32                (WDT_CONFIG_PER_CYC32_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 32 clock cycles Position  */
#define WDT_CONFIG_PER_CYC64                (WDT_CONFIG_PER_CYC64_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 64 clock cycles Position  */
#define WDT_CONFIG_PER_CYC128               (WDT_CONFIG_PER_CYC128_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 128 clock cycles Position  */
#define WDT_CONFIG_PER_CYC256               (WDT_CONFIG_PER_CYC256_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 256 clock cycles Position  */
#define WDT_CONFIG_PER_CYC512               (WDT_CONFIG_PER_CYC512_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 512 clock cycles Position  */
#define WDT_CONFIG_PER_CYC1024              (WDT_CONFIG_PER_CYC1024_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 1024 clock cycles Position  */
#define WDT_CONFIG_PER_CYC2048              (WDT_CONFIG_PER_CYC2048_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 2048 clock cycles Position  */
#define WDT_CONFIG_PER_CYC4096              (WDT_CONFIG_PER_CYC4096_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 4096 clock cycles Position  */
#define WDT_CONFIG_PER_CYC8192              (WDT_CONFIG_PER_CYC8192_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 8192 clock cycles Position  */
#define WDT_CONFIG_PER_CYC16384             (WDT_CONFIG_PER_CYC16384_Val << WDT_CONFIG_PER_Pos)  /**< (WDT_CONFIG) 16384 clock cycles Position  */
#define WDT_CONFIG_WINDOW_Pos               4                                              /**< (WDT_CONFIG) Window Mode Time-Out Period Position */
#define WDT_CONFIG_WINDOW_Msk               (_U_(0xF) << WDT_CONFIG_WINDOW_Pos)            /**< (WDT_CONFIG) Window Mode Time-Out Period Mask */
#define WDT_CONFIG_WINDOW(value)            (WDT_CONFIG_WINDOW_Msk & ((value) << WDT_CONFIG_WINDOW_Pos))
#define   WDT_CONFIG_WINDOW_CYC8_Val        _U_(0x0)                                       /**< (WDT_CONFIG) 8 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC16_Val       _U_(0x1)                                       /**< (WDT_CONFIG) 16 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC32_Val       _U_(0x2)                                       /**< (WDT_CONFIG) 32 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC64_Val       _U_(0x3)                                       /**< (WDT_CONFIG) 64 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC128_Val      _U_(0x4)                                       /**< (WDT_CONFIG) 128 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC256_Val      _U_(0x5)                                       /**< (WDT_CONFIG) 256 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC512_Val      _U_(0x6)                                       /**< (WDT_CONFIG) 512 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC1024_Val     _U_(0x7)                                       /**< (WDT_CONFIG) 1024 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC2048_Val     _U_(0x8)                                       /**< (WDT_CONFIG) 2048 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC4096_Val     _U_(0x9)                                       /**< (WDT_CONFIG) 4096 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC8192_Val     _U_(0xA)                                       /**< (WDT_CONFIG) 8192 clock cycles  */
#define   WDT_CONFIG_WINDOW_CYC16384_Val    _U_(0xB)                                       /**< (WDT_CONFIG) 16384 clock cycles  */
#define WDT_CONFIG_WINDOW_CYC8              (WDT_CONFIG_WINDOW_CYC8_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 8 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC16             (WDT_CONFIG_WINDOW_CYC16_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 16 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC32             (WDT_CONFIG_WINDOW_CYC32_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 32 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC64             (WDT_CONFIG_WINDOW_CYC64_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 64 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC128            (WDT_CONFIG_WINDOW_CYC128_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 128 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC256            (WDT_CONFIG_WINDOW_CYC256_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 256 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC512            (WDT_CONFIG_WINDOW_CYC512_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 512 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC1024           (WDT_CONFIG_WINDOW_CYC1024_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 1024 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC2048           (WDT_CONFIG_WINDOW_CYC2048_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 2048 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC4096           (WDT_CONFIG_WINDOW_CYC4096_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 4096 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC8192           (WDT_CONFIG_WINDOW_CYC8192_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 8192 clock cycles Position  */
#define WDT_CONFIG_WINDOW_CYC16384          (WDT_CONFIG_WINDOW_CYC16384_Val << WDT_CONFIG_WINDOW_Pos)  /**< (WDT_CONFIG) 16384 clock cycles Position  */
#define WDT_CONFIG_MASK                     _U_(0xFF)                                      /**< \deprecated (WDT_CONFIG) Register MASK  (Use WDT_CONFIG_Msk instead)  */
#define WDT_CONFIG_Msk                      _U_(0xFF)                                      /**< (WDT_CONFIG) Register Mask  */


/* -------- WDT_EWCTRL : (WDT Offset: 0x02) (R/W 8) Early Warning Interrupt Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  EWOFFSET:4;                /**< bit:   0..3  Early Warning Interrupt Time Offset      */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_EWCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_EWCTRL_OFFSET                   (0x02)                                        /**<  (WDT_EWCTRL) Early Warning Interrupt Control  Offset */
#define WDT_EWCTRL_RESETVALUE               _U_(0x0B)                                     /**<  (WDT_EWCTRL) Early Warning Interrupt Control  Reset Value */

#define WDT_EWCTRL_EWOFFSET_Pos             0                                              /**< (WDT_EWCTRL) Early Warning Interrupt Time Offset Position */
#define WDT_EWCTRL_EWOFFSET_Msk             (_U_(0xF) << WDT_EWCTRL_EWOFFSET_Pos)          /**< (WDT_EWCTRL) Early Warning Interrupt Time Offset Mask */
#define WDT_EWCTRL_EWOFFSET(value)          (WDT_EWCTRL_EWOFFSET_Msk & ((value) << WDT_EWCTRL_EWOFFSET_Pos))
#define   WDT_EWCTRL_EWOFFSET_CYC8_Val      _U_(0x0)                                       /**< (WDT_EWCTRL) 8 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC16_Val     _U_(0x1)                                       /**< (WDT_EWCTRL) 16 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC32_Val     _U_(0x2)                                       /**< (WDT_EWCTRL) 32 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC64_Val     _U_(0x3)                                       /**< (WDT_EWCTRL) 64 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC128_Val    _U_(0x4)                                       /**< (WDT_EWCTRL) 128 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC256_Val    _U_(0x5)                                       /**< (WDT_EWCTRL) 256 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC512_Val    _U_(0x6)                                       /**< (WDT_EWCTRL) 512 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC1024_Val   _U_(0x7)                                       /**< (WDT_EWCTRL) 1024 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC2048_Val   _U_(0x8)                                       /**< (WDT_EWCTRL) 2048 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC4096_Val   _U_(0x9)                                       /**< (WDT_EWCTRL) 4096 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC8192_Val   _U_(0xA)                                       /**< (WDT_EWCTRL) 8192 clock cycles  */
#define   WDT_EWCTRL_EWOFFSET_CYC16384_Val  _U_(0xB)                                       /**< (WDT_EWCTRL) 16384 clock cycles  */
#define WDT_EWCTRL_EWOFFSET_CYC8            (WDT_EWCTRL_EWOFFSET_CYC8_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 8 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC16           (WDT_EWCTRL_EWOFFSET_CYC16_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 16 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC32           (WDT_EWCTRL_EWOFFSET_CYC32_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 32 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC64           (WDT_EWCTRL_EWOFFSET_CYC64_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 64 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC128          (WDT_EWCTRL_EWOFFSET_CYC128_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 128 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC256          (WDT_EWCTRL_EWOFFSET_CYC256_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 256 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC512          (WDT_EWCTRL_EWOFFSET_CYC512_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 512 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC1024         (WDT_EWCTRL_EWOFFSET_CYC1024_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 1024 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC2048         (WDT_EWCTRL_EWOFFSET_CYC2048_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 2048 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC4096         (WDT_EWCTRL_EWOFFSET_CYC4096_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 4096 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC8192         (WDT_EWCTRL_EWOFFSET_CYC8192_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 8192 clock cycles Position  */
#define WDT_EWCTRL_EWOFFSET_CYC16384        (WDT_EWCTRL_EWOFFSET_CYC16384_Val << WDT_EWCTRL_EWOFFSET_Pos)  /**< (WDT_EWCTRL) 16384 clock cycles Position  */
#define WDT_EWCTRL_MASK                     _U_(0x0F)                                      /**< \deprecated (WDT_EWCTRL) Register MASK  (Use WDT_EWCTRL_Msk instead)  */
#define WDT_EWCTRL_Msk                      _U_(0x0F)                                      /**< (WDT_EWCTRL) Register Mask  */


/* -------- WDT_INTENCLR : (WDT Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  EW:1;                      /**< bit:      0  Early Warning Interrupt Enable           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_INTENCLR_OFFSET                 (0x04)                                        /**<  (WDT_INTENCLR) Interrupt Enable Clear  Offset */
#define WDT_INTENCLR_RESETVALUE             _U_(0x00)                                     /**<  (WDT_INTENCLR) Interrupt Enable Clear  Reset Value */

#define WDT_INTENCLR_EW_Pos                 0                                              /**< (WDT_INTENCLR) Early Warning Interrupt Enable Position */
#define WDT_INTENCLR_EW_Msk                 (_U_(0x1) << WDT_INTENCLR_EW_Pos)              /**< (WDT_INTENCLR) Early Warning Interrupt Enable Mask */
#define WDT_INTENCLR_EW                     WDT_INTENCLR_EW_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_INTENCLR_EW_Msk instead */
#define WDT_INTENCLR_MASK                   _U_(0x01)                                      /**< \deprecated (WDT_INTENCLR) Register MASK  (Use WDT_INTENCLR_Msk instead)  */
#define WDT_INTENCLR_Msk                    _U_(0x01)                                      /**< (WDT_INTENCLR) Register Mask  */


/* -------- WDT_INTENSET : (WDT Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  EW:1;                      /**< bit:      0  Early Warning Interrupt Enable           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_INTENSET_OFFSET                 (0x05)                                        /**<  (WDT_INTENSET) Interrupt Enable Set  Offset */
#define WDT_INTENSET_RESETVALUE             _U_(0x00)                                     /**<  (WDT_INTENSET) Interrupt Enable Set  Reset Value */

#define WDT_INTENSET_EW_Pos                 0                                              /**< (WDT_INTENSET) Early Warning Interrupt Enable Position */
#define WDT_INTENSET_EW_Msk                 (_U_(0x1) << WDT_INTENSET_EW_Pos)              /**< (WDT_INTENSET) Early Warning Interrupt Enable Mask */
#define WDT_INTENSET_EW                     WDT_INTENSET_EW_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_INTENSET_EW_Msk instead */
#define WDT_INTENSET_MASK                   _U_(0x01)                                      /**< \deprecated (WDT_INTENSET) Register MASK  (Use WDT_INTENSET_Msk instead)  */
#define WDT_INTENSET_Msk                    _U_(0x01)                                      /**< (WDT_INTENSET) Register Mask  */


/* -------- WDT_INTFLAG : (WDT Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t EW:1;                      /**< bit:      0  Early Warning                            */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_INTFLAG_OFFSET                  (0x06)                                        /**<  (WDT_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define WDT_INTFLAG_RESETVALUE              _U_(0x00)                                     /**<  (WDT_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define WDT_INTFLAG_EW_Pos                  0                                              /**< (WDT_INTFLAG) Early Warning Position */
#define WDT_INTFLAG_EW_Msk                  (_U_(0x1) << WDT_INTFLAG_EW_Pos)               /**< (WDT_INTFLAG) Early Warning Mask */
#define WDT_INTFLAG_EW                      WDT_INTFLAG_EW_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_INTFLAG_EW_Msk instead */
#define WDT_INTFLAG_MASK                    _U_(0x01)                                      /**< \deprecated (WDT_INTFLAG) Register MASK  (Use WDT_INTFLAG_Msk instead)  */
#define WDT_INTFLAG_Msk                     _U_(0x01)                                      /**< (WDT_INTFLAG) Register Mask  */


/* -------- WDT_SYNCBUSY : (WDT Offset: 0x08) (R/ 32) Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Synchronization Busy              */
    uint32_t WEN:1;                     /**< bit:      2  Window Enable Synchronization Busy       */
    uint32_t RUNSTDBY:1;                /**< bit:      3  Run During Standby Synchronization Busy  */
    uint32_t ALWAYSON:1;                /**< bit:      4  Always-On Synchronization Busy           */
    uint32_t CLEAR:1;                   /**< bit:      5  Clear Synchronization Busy               */
    uint32_t :26;                       /**< bit:  6..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} WDT_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_SYNCBUSY_OFFSET                 (0x08)                                        /**<  (WDT_SYNCBUSY) Synchronization Busy  Offset */
#define WDT_SYNCBUSY_RESETVALUE             _U_(0x00)                                     /**<  (WDT_SYNCBUSY) Synchronization Busy  Reset Value */

#define WDT_SYNCBUSY_ENABLE_Pos             1                                              /**< (WDT_SYNCBUSY) Enable Synchronization Busy Position */
#define WDT_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << WDT_SYNCBUSY_ENABLE_Pos)          /**< (WDT_SYNCBUSY) Enable Synchronization Busy Mask */
#define WDT_SYNCBUSY_ENABLE                 WDT_SYNCBUSY_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_SYNCBUSY_ENABLE_Msk instead */
#define WDT_SYNCBUSY_WEN_Pos                2                                              /**< (WDT_SYNCBUSY) Window Enable Synchronization Busy Position */
#define WDT_SYNCBUSY_WEN_Msk                (_U_(0x1) << WDT_SYNCBUSY_WEN_Pos)             /**< (WDT_SYNCBUSY) Window Enable Synchronization Busy Mask */
#define WDT_SYNCBUSY_WEN                    WDT_SYNCBUSY_WEN_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_SYNCBUSY_WEN_Msk instead */
#define WDT_SYNCBUSY_RUNSTDBY_Pos           3                                              /**< (WDT_SYNCBUSY) Run During Standby Synchronization Busy Position */
#define WDT_SYNCBUSY_RUNSTDBY_Msk           (_U_(0x1) << WDT_SYNCBUSY_RUNSTDBY_Pos)        /**< (WDT_SYNCBUSY) Run During Standby Synchronization Busy Mask */
#define WDT_SYNCBUSY_RUNSTDBY               WDT_SYNCBUSY_RUNSTDBY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_SYNCBUSY_RUNSTDBY_Msk instead */
#define WDT_SYNCBUSY_ALWAYSON_Pos           4                                              /**< (WDT_SYNCBUSY) Always-On Synchronization Busy Position */
#define WDT_SYNCBUSY_ALWAYSON_Msk           (_U_(0x1) << WDT_SYNCBUSY_ALWAYSON_Pos)        /**< (WDT_SYNCBUSY) Always-On Synchronization Busy Mask */
#define WDT_SYNCBUSY_ALWAYSON               WDT_SYNCBUSY_ALWAYSON_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_SYNCBUSY_ALWAYSON_Msk instead */
#define WDT_SYNCBUSY_CLEAR_Pos              5                                              /**< (WDT_SYNCBUSY) Clear Synchronization Busy Position */
#define WDT_SYNCBUSY_CLEAR_Msk              (_U_(0x1) << WDT_SYNCBUSY_CLEAR_Pos)           /**< (WDT_SYNCBUSY) Clear Synchronization Busy Mask */
#define WDT_SYNCBUSY_CLEAR                  WDT_SYNCBUSY_CLEAR_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_SYNCBUSY_CLEAR_Msk instead */
#define WDT_SYNCBUSY_MASK                   _U_(0x3E)                                      /**< \deprecated (WDT_SYNCBUSY) Register MASK  (Use WDT_SYNCBUSY_Msk instead)  */
#define WDT_SYNCBUSY_Msk                    _U_(0x3E)                                      /**< (WDT_SYNCBUSY) Register Mask  */


/* -------- WDT_CLEAR : (WDT Offset: 0x0c) (/W 8) Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CLEAR:8;                   /**< bit:   0..7  Watchdog Clear                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_CLEAR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_CLEAR_OFFSET                    (0x0C)                                        /**<  (WDT_CLEAR) Clear  Offset */
#define WDT_CLEAR_RESETVALUE                _U_(0x00)                                     /**<  (WDT_CLEAR) Clear  Reset Value */

#define WDT_CLEAR_CLEAR_Pos                 0                                              /**< (WDT_CLEAR) Watchdog Clear Position */
#define WDT_CLEAR_CLEAR_Msk                 (_U_(0xFF) << WDT_CLEAR_CLEAR_Pos)             /**< (WDT_CLEAR) Watchdog Clear Mask */
#define WDT_CLEAR_CLEAR(value)              (WDT_CLEAR_CLEAR_Msk & ((value) << WDT_CLEAR_CLEAR_Pos))
#define   WDT_CLEAR_CLEAR_KEY_Val           _U_(0xA5)                                      /**< (WDT_CLEAR) Clear Key  */
#define WDT_CLEAR_CLEAR_KEY                 (WDT_CLEAR_CLEAR_KEY_Val << WDT_CLEAR_CLEAR_Pos)  /**< (WDT_CLEAR) Clear Key Position  */
#define WDT_CLEAR_MASK                      _U_(0xFF)                                      /**< \deprecated (WDT_CLEAR) Register MASK  (Use WDT_CLEAR_Msk instead)  */
#define WDT_CLEAR_Msk                       _U_(0xFF)                                      /**< (WDT_CLEAR) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief WDT hardware registers */
typedef struct {  /* Watchdog Timer */
  __IO WDT_CTRLA_Type                 CTRLA;          /**< Offset: 0x00 (R/W   8) Control */
  __IO WDT_CONFIG_Type                CONFIG;         /**< Offset: 0x01 (R/W   8) Configuration */
  __IO WDT_EWCTRL_Type                EWCTRL;         /**< Offset: 0x02 (R/W   8) Early Warning Interrupt Control */
  __I  uint8_t                        Reserved1[1];
  __IO WDT_INTENCLR_Type              INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO WDT_INTENSET_Type              INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO WDT_INTFLAG_Type               INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved2[1];
  __I  WDT_SYNCBUSY_Type              SYNCBUSY;       /**< Offset: 0x08 (R/   32) Synchronization Busy */
  __O  WDT_CLEAR_Type                 CLEAR;          /**< Offset: 0x0C ( /W   8) Clear */
} Wdt;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Watchdog Timer */

#endif /* _SAML10_WDT_COMPONENT_H_ */
