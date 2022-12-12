/**
 * \file
 *
 * \brief Component description for MCLK
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
#ifndef _SAML10_MCLK_COMPONENT_H_
#define _SAML10_MCLK_COMPONENT_H_
#define _SAML10_MCLK_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Main Clock
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR MCLK */
/* ========================================================================== */

#define MCLK_U2234                      /**< (MCLK) Module ID */
#define REV_MCLK 0x300                  /**< (MCLK) Module revision */

/* -------- MCLK_CTRLA : (MCLK Offset: 0x00) (R/W 8) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :2;                        /**< bit:   0..1  Reserved */
    uint8_t  CKSEL:1;                   /**< bit:      2  Clock Select                             */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} MCLK_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_CTRLA_OFFSET                   (0x00)                                        /**<  (MCLK_CTRLA) Control  Offset */
#define MCLK_CTRLA_RESETVALUE               _U_(0x00)                                     /**<  (MCLK_CTRLA) Control  Reset Value */

#define MCLK_CTRLA_CKSEL_Pos                2                                              /**< (MCLK_CTRLA) Clock Select Position */
#define MCLK_CTRLA_CKSEL_Msk                (_U_(0x1) << MCLK_CTRLA_CKSEL_Pos)             /**< (MCLK_CTRLA) Clock Select Mask */
#define MCLK_CTRLA_CKSEL                    MCLK_CTRLA_CKSEL_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_CTRLA_CKSEL_Msk instead */
#define MCLK_CTRLA_MASK                     _U_(0x04)                                      /**< \deprecated (MCLK_CTRLA) Register MASK  (Use MCLK_CTRLA_Msk instead)  */
#define MCLK_CTRLA_Msk                      _U_(0x04)                                      /**< (MCLK_CTRLA) Register Mask  */


/* -------- MCLK_INTENCLR : (MCLK Offset: 0x01) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CKRDY:1;                   /**< bit:      0  Clock Ready Interrupt Enable             */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} MCLK_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_INTENCLR_OFFSET                (0x01)                                        /**<  (MCLK_INTENCLR) Interrupt Enable Clear  Offset */
#define MCLK_INTENCLR_RESETVALUE            _U_(0x00)                                     /**<  (MCLK_INTENCLR) Interrupt Enable Clear  Reset Value */

#define MCLK_INTENCLR_CKRDY_Pos             0                                              /**< (MCLK_INTENCLR) Clock Ready Interrupt Enable Position */
#define MCLK_INTENCLR_CKRDY_Msk             (_U_(0x1) << MCLK_INTENCLR_CKRDY_Pos)          /**< (MCLK_INTENCLR) Clock Ready Interrupt Enable Mask */
#define MCLK_INTENCLR_CKRDY                 MCLK_INTENCLR_CKRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_INTENCLR_CKRDY_Msk instead */
#define MCLK_INTENCLR_MASK                  _U_(0x01)                                      /**< \deprecated (MCLK_INTENCLR) Register MASK  (Use MCLK_INTENCLR_Msk instead)  */
#define MCLK_INTENCLR_Msk                   _U_(0x01)                                      /**< (MCLK_INTENCLR) Register Mask  */


/* -------- MCLK_INTENSET : (MCLK Offset: 0x02) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CKRDY:1;                   /**< bit:      0  Clock Ready Interrupt Enable             */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} MCLK_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_INTENSET_OFFSET                (0x02)                                        /**<  (MCLK_INTENSET) Interrupt Enable Set  Offset */
#define MCLK_INTENSET_RESETVALUE            _U_(0x00)                                     /**<  (MCLK_INTENSET) Interrupt Enable Set  Reset Value */

#define MCLK_INTENSET_CKRDY_Pos             0                                              /**< (MCLK_INTENSET) Clock Ready Interrupt Enable Position */
#define MCLK_INTENSET_CKRDY_Msk             (_U_(0x1) << MCLK_INTENSET_CKRDY_Pos)          /**< (MCLK_INTENSET) Clock Ready Interrupt Enable Mask */
#define MCLK_INTENSET_CKRDY                 MCLK_INTENSET_CKRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_INTENSET_CKRDY_Msk instead */
#define MCLK_INTENSET_MASK                  _U_(0x01)                                      /**< \deprecated (MCLK_INTENSET) Register MASK  (Use MCLK_INTENSET_Msk instead)  */
#define MCLK_INTENSET_Msk                   _U_(0x01)                                      /**< (MCLK_INTENSET) Register Mask  */


/* -------- MCLK_INTFLAG : (MCLK Offset: 0x03) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t CKRDY:1;                   /**< bit:      0  Clock Ready                              */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} MCLK_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_INTFLAG_OFFSET                 (0x03)                                        /**<  (MCLK_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define MCLK_INTFLAG_RESETVALUE             _U_(0x01)                                     /**<  (MCLK_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define MCLK_INTFLAG_CKRDY_Pos              0                                              /**< (MCLK_INTFLAG) Clock Ready Position */
#define MCLK_INTFLAG_CKRDY_Msk              (_U_(0x1) << MCLK_INTFLAG_CKRDY_Pos)           /**< (MCLK_INTFLAG) Clock Ready Mask */
#define MCLK_INTFLAG_CKRDY                  MCLK_INTFLAG_CKRDY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_INTFLAG_CKRDY_Msk instead */
#define MCLK_INTFLAG_MASK                   _U_(0x01)                                      /**< \deprecated (MCLK_INTFLAG) Register MASK  (Use MCLK_INTFLAG_Msk instead)  */
#define MCLK_INTFLAG_Msk                    _U_(0x01)                                      /**< (MCLK_INTFLAG) Register Mask  */


/* -------- MCLK_CPUDIV : (MCLK Offset: 0x04) (R/W 8) CPU Clock Division -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CPUDIV:8;                  /**< bit:   0..7  CPU Clock Division Factor                */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} MCLK_CPUDIV_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_CPUDIV_OFFSET                  (0x04)                                        /**<  (MCLK_CPUDIV) CPU Clock Division  Offset */
#define MCLK_CPUDIV_RESETVALUE              _U_(0x01)                                     /**<  (MCLK_CPUDIV) CPU Clock Division  Reset Value */

#define MCLK_CPUDIV_CPUDIV_Pos              0                                              /**< (MCLK_CPUDIV) CPU Clock Division Factor Position */
#define MCLK_CPUDIV_CPUDIV_Msk              (_U_(0xFF) << MCLK_CPUDIV_CPUDIV_Pos)          /**< (MCLK_CPUDIV) CPU Clock Division Factor Mask */
#define MCLK_CPUDIV_CPUDIV(value)           (MCLK_CPUDIV_CPUDIV_Msk & ((value) << MCLK_CPUDIV_CPUDIV_Pos))
#define   MCLK_CPUDIV_CPUDIV_DIV1_Val       _U_(0x1)                                       /**< (MCLK_CPUDIV) Divide by 1  */
#define   MCLK_CPUDIV_CPUDIV_DIV2_Val       _U_(0x2)                                       /**< (MCLK_CPUDIV) Divide by 2  */
#define   MCLK_CPUDIV_CPUDIV_DIV4_Val       _U_(0x4)                                       /**< (MCLK_CPUDIV) Divide by 4  */
#define   MCLK_CPUDIV_CPUDIV_DIV8_Val       _U_(0x8)                                       /**< (MCLK_CPUDIV) Divide by 8  */
#define   MCLK_CPUDIV_CPUDIV_DIV16_Val      _U_(0x10)                                      /**< (MCLK_CPUDIV) Divide by 16  */
#define   MCLK_CPUDIV_CPUDIV_DIV32_Val      _U_(0x20)                                      /**< (MCLK_CPUDIV) Divide by 32  */
#define   MCLK_CPUDIV_CPUDIV_DIV64_Val      _U_(0x40)                                      /**< (MCLK_CPUDIV) Divide by 64  */
#define   MCLK_CPUDIV_CPUDIV_DIV128_Val     _U_(0x80)                                      /**< (MCLK_CPUDIV) Divide by 128  */
#define MCLK_CPUDIV_CPUDIV_DIV1             (MCLK_CPUDIV_CPUDIV_DIV1_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 1 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV2             (MCLK_CPUDIV_CPUDIV_DIV2_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 2 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV4             (MCLK_CPUDIV_CPUDIV_DIV4_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 4 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV8             (MCLK_CPUDIV_CPUDIV_DIV8_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 8 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV16            (MCLK_CPUDIV_CPUDIV_DIV16_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 16 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV32            (MCLK_CPUDIV_CPUDIV_DIV32_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 32 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV64            (MCLK_CPUDIV_CPUDIV_DIV64_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 64 Position  */
#define MCLK_CPUDIV_CPUDIV_DIV128           (MCLK_CPUDIV_CPUDIV_DIV128_Val << MCLK_CPUDIV_CPUDIV_Pos)  /**< (MCLK_CPUDIV) Divide by 128 Position  */
#define MCLK_CPUDIV_MASK                    _U_(0xFF)                                      /**< \deprecated (MCLK_CPUDIV) Register MASK  (Use MCLK_CPUDIV_Msk instead)  */
#define MCLK_CPUDIV_Msk                     _U_(0xFF)                                      /**< (MCLK_CPUDIV) Register Mask  */


/* -------- MCLK_AHBMASK : (MCLK Offset: 0x10) (R/W 32) AHB Mask -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t HPB0_:1;                   /**< bit:      0  HPB0 AHB Clock Mask                      */
    uint32_t HPB1_:1;                   /**< bit:      1  HPB1 AHB Clock Mask                      */
    uint32_t HPB2_:1;                   /**< bit:      2  HPB2 AHB Clock Mask                      */
    uint32_t DMAC_:1;                   /**< bit:      3  DMAC AHB Clock Mask                      */
    uint32_t DSU_:1;                    /**< bit:      4  DSU AHB Clock Mask                       */
    uint32_t :1;                        /**< bit:      5  Reserved */
    uint32_t PAC_:1;                    /**< bit:      6  PAC AHB Clock Mask                       */
    uint32_t NVMCTRL_:1;                /**< bit:      7  NVMCTRL AHB Clock Mask                   */
    uint32_t :4;                        /**< bit:  8..11  Reserved */
    uint32_t TRAM_:1;                   /**< bit:     12  TRAM AHB Clock Mask                      */
    uint32_t :19;                       /**< bit: 13..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} MCLK_AHBMASK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_AHBMASK_OFFSET                 (0x10)                                        /**<  (MCLK_AHBMASK) AHB Mask  Offset */
#define MCLK_AHBMASK_RESETVALUE             _U_(0x1FFF)                                   /**<  (MCLK_AHBMASK) AHB Mask  Reset Value */

#define MCLK_AHBMASK_HPB0_Pos               0                                              /**< (MCLK_AHBMASK) HPB0 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB0_Msk               (_U_(0x1) << MCLK_AHBMASK_HPB0_Pos)            /**< (MCLK_AHBMASK) HPB0 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB0                   MCLK_AHBMASK_HPB0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_HPB0_Msk instead */
#define MCLK_AHBMASK_HPB1_Pos               1                                              /**< (MCLK_AHBMASK) HPB1 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB1_Msk               (_U_(0x1) << MCLK_AHBMASK_HPB1_Pos)            /**< (MCLK_AHBMASK) HPB1 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB1                   MCLK_AHBMASK_HPB1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_HPB1_Msk instead */
#define MCLK_AHBMASK_HPB2_Pos               2                                              /**< (MCLK_AHBMASK) HPB2 AHB Clock Mask Position */
#define MCLK_AHBMASK_HPB2_Msk               (_U_(0x1) << MCLK_AHBMASK_HPB2_Pos)            /**< (MCLK_AHBMASK) HPB2 AHB Clock Mask Mask */
#define MCLK_AHBMASK_HPB2                   MCLK_AHBMASK_HPB2_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_HPB2_Msk instead */
#define MCLK_AHBMASK_DMAC_Pos               3                                              /**< (MCLK_AHBMASK) DMAC AHB Clock Mask Position */
#define MCLK_AHBMASK_DMAC_Msk               (_U_(0x1) << MCLK_AHBMASK_DMAC_Pos)            /**< (MCLK_AHBMASK) DMAC AHB Clock Mask Mask */
#define MCLK_AHBMASK_DMAC                   MCLK_AHBMASK_DMAC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_DMAC_Msk instead */
#define MCLK_AHBMASK_DSU_Pos                4                                              /**< (MCLK_AHBMASK) DSU AHB Clock Mask Position */
#define MCLK_AHBMASK_DSU_Msk                (_U_(0x1) << MCLK_AHBMASK_DSU_Pos)             /**< (MCLK_AHBMASK) DSU AHB Clock Mask Mask */
#define MCLK_AHBMASK_DSU                    MCLK_AHBMASK_DSU_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_DSU_Msk instead */
#define MCLK_AHBMASK_PAC_Pos                6                                              /**< (MCLK_AHBMASK) PAC AHB Clock Mask Position */
#define MCLK_AHBMASK_PAC_Msk                (_U_(0x1) << MCLK_AHBMASK_PAC_Pos)             /**< (MCLK_AHBMASK) PAC AHB Clock Mask Mask */
#define MCLK_AHBMASK_PAC                    MCLK_AHBMASK_PAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_PAC_Msk instead */
#define MCLK_AHBMASK_NVMCTRL_Pos            7                                              /**< (MCLK_AHBMASK) NVMCTRL AHB Clock Mask Position */
#define MCLK_AHBMASK_NVMCTRL_Msk            (_U_(0x1) << MCLK_AHBMASK_NVMCTRL_Pos)         /**< (MCLK_AHBMASK) NVMCTRL AHB Clock Mask Mask */
#define MCLK_AHBMASK_NVMCTRL                MCLK_AHBMASK_NVMCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_NVMCTRL_Msk instead */
#define MCLK_AHBMASK_TRAM_Pos               12                                             /**< (MCLK_AHBMASK) TRAM AHB Clock Mask Position */
#define MCLK_AHBMASK_TRAM_Msk               (_U_(0x1) << MCLK_AHBMASK_TRAM_Pos)            /**< (MCLK_AHBMASK) TRAM AHB Clock Mask Mask */
#define MCLK_AHBMASK_TRAM                   MCLK_AHBMASK_TRAM_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_AHBMASK_TRAM_Msk instead */
#define MCLK_AHBMASK_MASK                   _U_(0x10DF)                                    /**< \deprecated (MCLK_AHBMASK) Register MASK  (Use MCLK_AHBMASK_Msk instead)  */
#define MCLK_AHBMASK_Msk                    _U_(0x10DF)                                    /**< (MCLK_AHBMASK) Register Mask  */

#define MCLK_AHBMASK_HPB_Pos                0                                              /**< (MCLK_AHBMASK Position) HPBx AHB Clock Mask */
#define MCLK_AHBMASK_HPB_Msk                (_U_(0x7) << MCLK_AHBMASK_HPB_Pos)             /**< (MCLK_AHBMASK Mask) HPB */
#define MCLK_AHBMASK_HPB(value)             (MCLK_AHBMASK_HPB_Msk & ((value) << MCLK_AHBMASK_HPB_Pos))  

/* -------- MCLK_APBAMASK : (MCLK Offset: 0x14) (R/W 32) APBA Mask -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PAC_:1;                    /**< bit:      0  PAC APB Clock Enable                     */
    uint32_t PM_:1;                     /**< bit:      1  PM APB Clock Enable                      */
    uint32_t MCLK_:1;                   /**< bit:      2  MCLK APB Clock Enable                    */
    uint32_t RSTC_:1;                   /**< bit:      3  RSTC APB Clock Enable                    */
    uint32_t OSCCTRL_:1;                /**< bit:      4  OSCCTRL APB Clock Enable                 */
    uint32_t OSC32KCTRL_:1;             /**< bit:      5  OSC32KCTRL APB Clock Enable              */
    uint32_t SUPC_:1;                   /**< bit:      6  SUPC APB Clock Enable                    */
    uint32_t GCLK_:1;                   /**< bit:      7  GCLK APB Clock Enable                    */
    uint32_t WDT_:1;                    /**< bit:      8  WDT APB Clock Enable                     */
    uint32_t RTC_:1;                    /**< bit:      9  RTC APB Clock Enable                     */
    uint32_t EIC_:1;                    /**< bit:     10  EIC APB Clock Enable                     */
    uint32_t FREQM_:1;                  /**< bit:     11  FREQM APB Clock Enable                   */
    uint32_t PORT_:1;                   /**< bit:     12  PORT APB Clock Enable                    */
    uint32_t AC_:1;                     /**< bit:     13  AC APB Clock Enable                      */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} MCLK_APBAMASK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_APBAMASK_OFFSET                (0x14)                                        /**<  (MCLK_APBAMASK) APBA Mask  Offset */
#define MCLK_APBAMASK_RESETVALUE            _U_(0x7FFF)                                   /**<  (MCLK_APBAMASK) APBA Mask  Reset Value */

#define MCLK_APBAMASK_PAC_Pos               0                                              /**< (MCLK_APBAMASK) PAC APB Clock Enable Position */
#define MCLK_APBAMASK_PAC_Msk               (_U_(0x1) << MCLK_APBAMASK_PAC_Pos)            /**< (MCLK_APBAMASK) PAC APB Clock Enable Mask */
#define MCLK_APBAMASK_PAC                   MCLK_APBAMASK_PAC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_PAC_Msk instead */
#define MCLK_APBAMASK_PM_Pos                1                                              /**< (MCLK_APBAMASK) PM APB Clock Enable Position */
#define MCLK_APBAMASK_PM_Msk                (_U_(0x1) << MCLK_APBAMASK_PM_Pos)             /**< (MCLK_APBAMASK) PM APB Clock Enable Mask */
#define MCLK_APBAMASK_PM                    MCLK_APBAMASK_PM_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_PM_Msk instead */
#define MCLK_APBAMASK_MCLK_Pos              2                                              /**< (MCLK_APBAMASK) MCLK APB Clock Enable Position */
#define MCLK_APBAMASK_MCLK_Msk              (_U_(0x1) << MCLK_APBAMASK_MCLK_Pos)           /**< (MCLK_APBAMASK) MCLK APB Clock Enable Mask */
#define MCLK_APBAMASK_MCLK                  MCLK_APBAMASK_MCLK_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_MCLK_Msk instead */
#define MCLK_APBAMASK_RSTC_Pos              3                                              /**< (MCLK_APBAMASK) RSTC APB Clock Enable Position */
#define MCLK_APBAMASK_RSTC_Msk              (_U_(0x1) << MCLK_APBAMASK_RSTC_Pos)           /**< (MCLK_APBAMASK) RSTC APB Clock Enable Mask */
#define MCLK_APBAMASK_RSTC                  MCLK_APBAMASK_RSTC_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_RSTC_Msk instead */
#define MCLK_APBAMASK_OSCCTRL_Pos           4                                              /**< (MCLK_APBAMASK) OSCCTRL APB Clock Enable Position */
#define MCLK_APBAMASK_OSCCTRL_Msk           (_U_(0x1) << MCLK_APBAMASK_OSCCTRL_Pos)        /**< (MCLK_APBAMASK) OSCCTRL APB Clock Enable Mask */
#define MCLK_APBAMASK_OSCCTRL               MCLK_APBAMASK_OSCCTRL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_OSCCTRL_Msk instead */
#define MCLK_APBAMASK_OSC32KCTRL_Pos        5                                              /**< (MCLK_APBAMASK) OSC32KCTRL APB Clock Enable Position */
#define MCLK_APBAMASK_OSC32KCTRL_Msk        (_U_(0x1) << MCLK_APBAMASK_OSC32KCTRL_Pos)     /**< (MCLK_APBAMASK) OSC32KCTRL APB Clock Enable Mask */
#define MCLK_APBAMASK_OSC32KCTRL            MCLK_APBAMASK_OSC32KCTRL_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_OSC32KCTRL_Msk instead */
#define MCLK_APBAMASK_SUPC_Pos              6                                              /**< (MCLK_APBAMASK) SUPC APB Clock Enable Position */
#define MCLK_APBAMASK_SUPC_Msk              (_U_(0x1) << MCLK_APBAMASK_SUPC_Pos)           /**< (MCLK_APBAMASK) SUPC APB Clock Enable Mask */
#define MCLK_APBAMASK_SUPC                  MCLK_APBAMASK_SUPC_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_SUPC_Msk instead */
#define MCLK_APBAMASK_GCLK_Pos              7                                              /**< (MCLK_APBAMASK) GCLK APB Clock Enable Position */
#define MCLK_APBAMASK_GCLK_Msk              (_U_(0x1) << MCLK_APBAMASK_GCLK_Pos)           /**< (MCLK_APBAMASK) GCLK APB Clock Enable Mask */
#define MCLK_APBAMASK_GCLK                  MCLK_APBAMASK_GCLK_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_GCLK_Msk instead */
#define MCLK_APBAMASK_WDT_Pos               8                                              /**< (MCLK_APBAMASK) WDT APB Clock Enable Position */
#define MCLK_APBAMASK_WDT_Msk               (_U_(0x1) << MCLK_APBAMASK_WDT_Pos)            /**< (MCLK_APBAMASK) WDT APB Clock Enable Mask */
#define MCLK_APBAMASK_WDT                   MCLK_APBAMASK_WDT_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_WDT_Msk instead */
#define MCLK_APBAMASK_RTC_Pos               9                                              /**< (MCLK_APBAMASK) RTC APB Clock Enable Position */
#define MCLK_APBAMASK_RTC_Msk               (_U_(0x1) << MCLK_APBAMASK_RTC_Pos)            /**< (MCLK_APBAMASK) RTC APB Clock Enable Mask */
#define MCLK_APBAMASK_RTC                   MCLK_APBAMASK_RTC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_RTC_Msk instead */
#define MCLK_APBAMASK_EIC_Pos               10                                             /**< (MCLK_APBAMASK) EIC APB Clock Enable Position */
#define MCLK_APBAMASK_EIC_Msk               (_U_(0x1) << MCLK_APBAMASK_EIC_Pos)            /**< (MCLK_APBAMASK) EIC APB Clock Enable Mask */
#define MCLK_APBAMASK_EIC                   MCLK_APBAMASK_EIC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_EIC_Msk instead */
#define MCLK_APBAMASK_FREQM_Pos             11                                             /**< (MCLK_APBAMASK) FREQM APB Clock Enable Position */
#define MCLK_APBAMASK_FREQM_Msk             (_U_(0x1) << MCLK_APBAMASK_FREQM_Pos)          /**< (MCLK_APBAMASK) FREQM APB Clock Enable Mask */
#define MCLK_APBAMASK_FREQM                 MCLK_APBAMASK_FREQM_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_FREQM_Msk instead */
#define MCLK_APBAMASK_PORT_Pos              12                                             /**< (MCLK_APBAMASK) PORT APB Clock Enable Position */
#define MCLK_APBAMASK_PORT_Msk              (_U_(0x1) << MCLK_APBAMASK_PORT_Pos)           /**< (MCLK_APBAMASK) PORT APB Clock Enable Mask */
#define MCLK_APBAMASK_PORT                  MCLK_APBAMASK_PORT_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_PORT_Msk instead */
#define MCLK_APBAMASK_AC_Pos                13                                             /**< (MCLK_APBAMASK) AC APB Clock Enable Position */
#define MCLK_APBAMASK_AC_Msk                (_U_(0x1) << MCLK_APBAMASK_AC_Pos)             /**< (MCLK_APBAMASK) AC APB Clock Enable Mask */
#define MCLK_APBAMASK_AC                    MCLK_APBAMASK_AC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBAMASK_AC_Msk instead */
#define MCLK_APBAMASK_MASK                  _U_(0x3FFF)                                    /**< \deprecated (MCLK_APBAMASK) Register MASK  (Use MCLK_APBAMASK_Msk instead)  */
#define MCLK_APBAMASK_Msk                   _U_(0x3FFF)                                    /**< (MCLK_APBAMASK) Register Mask  */


/* -------- MCLK_APBBMASK : (MCLK Offset: 0x18) (R/W 32) APBB Mask -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IDAU_:1;                   /**< bit:      0  IDAU APB Clock Enable                    */
    uint32_t DSU_:1;                    /**< bit:      1  DSU APB Clock Enable                     */
    uint32_t NVMCTRL_:1;                /**< bit:      2  NVMCTRL APB Clock Enable                 */
    uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} MCLK_APBBMASK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_APBBMASK_OFFSET                (0x18)                                        /**<  (MCLK_APBBMASK) APBB Mask  Offset */
#define MCLK_APBBMASK_RESETVALUE            _U_(0x17)                                     /**<  (MCLK_APBBMASK) APBB Mask  Reset Value */

#define MCLK_APBBMASK_IDAU_Pos              0                                              /**< (MCLK_APBBMASK) IDAU APB Clock Enable Position */
#define MCLK_APBBMASK_IDAU_Msk              (_U_(0x1) << MCLK_APBBMASK_IDAU_Pos)           /**< (MCLK_APBBMASK) IDAU APB Clock Enable Mask */
#define MCLK_APBBMASK_IDAU                  MCLK_APBBMASK_IDAU_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBBMASK_IDAU_Msk instead */
#define MCLK_APBBMASK_DSU_Pos               1                                              /**< (MCLK_APBBMASK) DSU APB Clock Enable Position */
#define MCLK_APBBMASK_DSU_Msk               (_U_(0x1) << MCLK_APBBMASK_DSU_Pos)            /**< (MCLK_APBBMASK) DSU APB Clock Enable Mask */
#define MCLK_APBBMASK_DSU                   MCLK_APBBMASK_DSU_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBBMASK_DSU_Msk instead */
#define MCLK_APBBMASK_NVMCTRL_Pos           2                                              /**< (MCLK_APBBMASK) NVMCTRL APB Clock Enable Position */
#define MCLK_APBBMASK_NVMCTRL_Msk           (_U_(0x1) << MCLK_APBBMASK_NVMCTRL_Pos)        /**< (MCLK_APBBMASK) NVMCTRL APB Clock Enable Mask */
#define MCLK_APBBMASK_NVMCTRL               MCLK_APBBMASK_NVMCTRL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBBMASK_NVMCTRL_Msk instead */
#define MCLK_APBBMASK_MASK                  _U_(0x07)                                      /**< \deprecated (MCLK_APBBMASK) Register MASK  (Use MCLK_APBBMASK_Msk instead)  */
#define MCLK_APBBMASK_Msk                   _U_(0x07)                                      /**< (MCLK_APBBMASK) Register Mask  */


/* -------- MCLK_APBCMASK : (MCLK Offset: 0x1c) (R/W 32) APBC Mask -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVSYS_:1;                  /**< bit:      0  EVSYS APB Clock Enable                   */
    uint32_t SERCOM0_:1;                /**< bit:      1  SERCOM0 APB Clock Enable                 */
    uint32_t SERCOM1_:1;                /**< bit:      2  SERCOM1 APB Clock Enable                 */
    uint32_t SERCOM2_:1;                /**< bit:      3  SERCOM2 APB Clock Enable                 */
    uint32_t TC0_:1;                    /**< bit:      4  TC0 APB Clock Enable                     */
    uint32_t TC1_:1;                    /**< bit:      5  TC1 APB Clock Enable                     */
    uint32_t TC2_:1;                    /**< bit:      6  TC2 APB Clock Enable                     */
    uint32_t ADC_:1;                    /**< bit:      7  ADC APB Clock Enable                     */
    uint32_t DAC_:1;                    /**< bit:      8  DAC APB Clock Enable                     */
    uint32_t PTC_:1;                    /**< bit:      9  PTC APB Clock Enable                     */
    uint32_t TRNG_:1;                   /**< bit:     10  TRNG APB Clock Enable                    */
    uint32_t CCL_:1;                    /**< bit:     11  CCL APB Clock Enable                     */
    uint32_t OPAMP_:1;                  /**< bit:     12  OPAMP APB Clock Enable                   */
    uint32_t :19;                       /**< bit: 13..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} MCLK_APBCMASK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define MCLK_APBCMASK_OFFSET                (0x1C)                                        /**<  (MCLK_APBCMASK) APBC Mask  Offset */
#define MCLK_APBCMASK_RESETVALUE            _U_(0x1FFF)                                   /**<  (MCLK_APBCMASK) APBC Mask  Reset Value */

#define MCLK_APBCMASK_EVSYS_Pos             0                                              /**< (MCLK_APBCMASK) EVSYS APB Clock Enable Position */
#define MCLK_APBCMASK_EVSYS_Msk             (_U_(0x1) << MCLK_APBCMASK_EVSYS_Pos)          /**< (MCLK_APBCMASK) EVSYS APB Clock Enable Mask */
#define MCLK_APBCMASK_EVSYS                 MCLK_APBCMASK_EVSYS_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_EVSYS_Msk instead */
#define MCLK_APBCMASK_SERCOM0_Pos           1                                              /**< (MCLK_APBCMASK) SERCOM0 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM0_Msk           (_U_(0x1) << MCLK_APBCMASK_SERCOM0_Pos)        /**< (MCLK_APBCMASK) SERCOM0 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM0               MCLK_APBCMASK_SERCOM0_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_SERCOM0_Msk instead */
#define MCLK_APBCMASK_SERCOM1_Pos           2                                              /**< (MCLK_APBCMASK) SERCOM1 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM1_Msk           (_U_(0x1) << MCLK_APBCMASK_SERCOM1_Pos)        /**< (MCLK_APBCMASK) SERCOM1 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM1               MCLK_APBCMASK_SERCOM1_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_SERCOM1_Msk instead */
#define MCLK_APBCMASK_SERCOM2_Pos           3                                              /**< (MCLK_APBCMASK) SERCOM2 APB Clock Enable Position */
#define MCLK_APBCMASK_SERCOM2_Msk           (_U_(0x1) << MCLK_APBCMASK_SERCOM2_Pos)        /**< (MCLK_APBCMASK) SERCOM2 APB Clock Enable Mask */
#define MCLK_APBCMASK_SERCOM2               MCLK_APBCMASK_SERCOM2_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_SERCOM2_Msk instead */
#define MCLK_APBCMASK_TC0_Pos               4                                              /**< (MCLK_APBCMASK) TC0 APB Clock Enable Position */
#define MCLK_APBCMASK_TC0_Msk               (_U_(0x1) << MCLK_APBCMASK_TC0_Pos)            /**< (MCLK_APBCMASK) TC0 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC0                   MCLK_APBCMASK_TC0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_TC0_Msk instead */
#define MCLK_APBCMASK_TC1_Pos               5                                              /**< (MCLK_APBCMASK) TC1 APB Clock Enable Position */
#define MCLK_APBCMASK_TC1_Msk               (_U_(0x1) << MCLK_APBCMASK_TC1_Pos)            /**< (MCLK_APBCMASK) TC1 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC1                   MCLK_APBCMASK_TC1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_TC1_Msk instead */
#define MCLK_APBCMASK_TC2_Pos               6                                              /**< (MCLK_APBCMASK) TC2 APB Clock Enable Position */
#define MCLK_APBCMASK_TC2_Msk               (_U_(0x1) << MCLK_APBCMASK_TC2_Pos)            /**< (MCLK_APBCMASK) TC2 APB Clock Enable Mask */
#define MCLK_APBCMASK_TC2                   MCLK_APBCMASK_TC2_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_TC2_Msk instead */
#define MCLK_APBCMASK_ADC_Pos               7                                              /**< (MCLK_APBCMASK) ADC APB Clock Enable Position */
#define MCLK_APBCMASK_ADC_Msk               (_U_(0x1) << MCLK_APBCMASK_ADC_Pos)            /**< (MCLK_APBCMASK) ADC APB Clock Enable Mask */
#define MCLK_APBCMASK_ADC                   MCLK_APBCMASK_ADC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_ADC_Msk instead */
#define MCLK_APBCMASK_DAC_Pos               8                                              /**< (MCLK_APBCMASK) DAC APB Clock Enable Position */
#define MCLK_APBCMASK_DAC_Msk               (_U_(0x1) << MCLK_APBCMASK_DAC_Pos)            /**< (MCLK_APBCMASK) DAC APB Clock Enable Mask */
#define MCLK_APBCMASK_DAC                   MCLK_APBCMASK_DAC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_DAC_Msk instead */
#define MCLK_APBCMASK_PTC_Pos               9                                              /**< (MCLK_APBCMASK) PTC APB Clock Enable Position */
#define MCLK_APBCMASK_PTC_Msk               (_U_(0x1) << MCLK_APBCMASK_PTC_Pos)            /**< (MCLK_APBCMASK) PTC APB Clock Enable Mask */
#define MCLK_APBCMASK_PTC                   MCLK_APBCMASK_PTC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_PTC_Msk instead */
#define MCLK_APBCMASK_TRNG_Pos              10                                             /**< (MCLK_APBCMASK) TRNG APB Clock Enable Position */
#define MCLK_APBCMASK_TRNG_Msk              (_U_(0x1) << MCLK_APBCMASK_TRNG_Pos)           /**< (MCLK_APBCMASK) TRNG APB Clock Enable Mask */
#define MCLK_APBCMASK_TRNG                  MCLK_APBCMASK_TRNG_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_TRNG_Msk instead */
#define MCLK_APBCMASK_CCL_Pos               11                                             /**< (MCLK_APBCMASK) CCL APB Clock Enable Position */
#define MCLK_APBCMASK_CCL_Msk               (_U_(0x1) << MCLK_APBCMASK_CCL_Pos)            /**< (MCLK_APBCMASK) CCL APB Clock Enable Mask */
#define MCLK_APBCMASK_CCL                   MCLK_APBCMASK_CCL_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_CCL_Msk instead */
#define MCLK_APBCMASK_OPAMP_Pos             12                                             /**< (MCLK_APBCMASK) OPAMP APB Clock Enable Position */
#define MCLK_APBCMASK_OPAMP_Msk             (_U_(0x1) << MCLK_APBCMASK_OPAMP_Pos)          /**< (MCLK_APBCMASK) OPAMP APB Clock Enable Mask */
#define MCLK_APBCMASK_OPAMP                 MCLK_APBCMASK_OPAMP_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use MCLK_APBCMASK_OPAMP_Msk instead */
#define MCLK_APBCMASK_MASK                  _U_(0x1FFF)                                    /**< \deprecated (MCLK_APBCMASK) Register MASK  (Use MCLK_APBCMASK_Msk instead)  */
#define MCLK_APBCMASK_Msk                   _U_(0x1FFF)                                    /**< (MCLK_APBCMASK) Register Mask  */

#define MCLK_APBCMASK_SERCOM_Pos            1                                              /**< (MCLK_APBCMASK Position) SERCOMx APB Clock Enable */
#define MCLK_APBCMASK_SERCOM_Msk            (_U_(0x7) << MCLK_APBCMASK_SERCOM_Pos)         /**< (MCLK_APBCMASK Mask) SERCOM */
#define MCLK_APBCMASK_SERCOM(value)         (MCLK_APBCMASK_SERCOM_Msk & ((value) << MCLK_APBCMASK_SERCOM_Pos))  
#define MCLK_APBCMASK_TC_Pos                4                                              /**< (MCLK_APBCMASK Position) TCx APB Clock Enable */
#define MCLK_APBCMASK_TC_Msk                (_U_(0x7) << MCLK_APBCMASK_TC_Pos)             /**< (MCLK_APBCMASK Mask) TC */
#define MCLK_APBCMASK_TC(value)             (MCLK_APBCMASK_TC_Msk & ((value) << MCLK_APBCMASK_TC_Pos))  

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MCLK hardware registers */
typedef struct {  /* Main Clock */
  __IO MCLK_CTRLA_Type                CTRLA;          /**< Offset: 0x00 (R/W   8) Control */
  __IO MCLK_INTENCLR_Type             INTENCLR;       /**< Offset: 0x01 (R/W   8) Interrupt Enable Clear */
  __IO MCLK_INTENSET_Type             INTENSET;       /**< Offset: 0x02 (R/W   8) Interrupt Enable Set */
  __IO MCLK_INTFLAG_Type              INTFLAG;        /**< Offset: 0x03 (R/W   8) Interrupt Flag Status and Clear */
  __IO MCLK_CPUDIV_Type               CPUDIV;         /**< Offset: 0x04 (R/W   8) CPU Clock Division */
  __I  uint8_t                        Reserved1[11];
  __IO MCLK_AHBMASK_Type              AHBMASK;        /**< Offset: 0x10 (R/W  32) AHB Mask */
  __IO MCLK_APBAMASK_Type             APBAMASK;       /**< Offset: 0x14 (R/W  32) APBA Mask */
  __IO MCLK_APBBMASK_Type             APBBMASK;       /**< Offset: 0x18 (R/W  32) APBB Mask */
  __IO MCLK_APBCMASK_Type             APBCMASK;       /**< Offset: 0x1C (R/W  32) APBC Mask */
} Mclk;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Main Clock */

#endif /* _SAML10_MCLK_COMPONENT_H_ */
