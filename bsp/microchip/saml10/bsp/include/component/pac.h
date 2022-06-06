/**
 * \file
 *
 * \brief Component description for PAC
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
#ifndef _SAML10_PAC_COMPONENT_H_
#define _SAML10_PAC_COMPONENT_H_
#define _SAML10_PAC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Peripheral Access Controller
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PAC */
/* ========================================================================== */

#define PAC_U2120                      /**< (PAC) Module ID */
#define REV_PAC 0x200                  /**< (PAC) Module revision */

/* -------- PAC_WRCTRL : (PAC Offset: 0x00) (R/W 32) Write control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PERID:16;                  /**< bit:  0..15  Peripheral identifier                    */
    uint32_t KEY:8;                     /**< bit: 16..23  Peripheral access control key            */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_WRCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_WRCTRL_OFFSET                   (0x00)                                        /**<  (PAC_WRCTRL) Write control  Offset */
#define PAC_WRCTRL_RESETVALUE               _U_(0x00)                                     /**<  (PAC_WRCTRL) Write control  Reset Value */

#define PAC_WRCTRL_PERID_Pos                0                                              /**< (PAC_WRCTRL) Peripheral identifier Position */
#define PAC_WRCTRL_PERID_Msk                (_U_(0xFFFF) << PAC_WRCTRL_PERID_Pos)          /**< (PAC_WRCTRL) Peripheral identifier Mask */
#define PAC_WRCTRL_PERID(value)             (PAC_WRCTRL_PERID_Msk & ((value) << PAC_WRCTRL_PERID_Pos))
#define PAC_WRCTRL_KEY_Pos                  16                                             /**< (PAC_WRCTRL) Peripheral access control key Position */
#define PAC_WRCTRL_KEY_Msk                  (_U_(0xFF) << PAC_WRCTRL_KEY_Pos)              /**< (PAC_WRCTRL) Peripheral access control key Mask */
#define PAC_WRCTRL_KEY(value)               (PAC_WRCTRL_KEY_Msk & ((value) << PAC_WRCTRL_KEY_Pos))
#define   PAC_WRCTRL_KEY_OFF_Val            _U_(0x0)                                       /**< (PAC_WRCTRL) No action  */
#define   PAC_WRCTRL_KEY_CLR_Val            _U_(0x1)                                       /**< (PAC_WRCTRL) Clear protection  */
#define   PAC_WRCTRL_KEY_SET_Val            _U_(0x2)                                       /**< (PAC_WRCTRL) Set protection  */
#define   PAC_WRCTRL_KEY_SETLCK_Val         _U_(0x3)                                       /**< (PAC_WRCTRL) Set and lock protection  */
#define   PAC_WRCTRL_KEY_SETSEC_Val         _U_(0x4)                                       /**< (PAC_WRCTRL) Set IP secure  */
#define   PAC_WRCTRL_KEY_SETNONSEC_Val      _U_(0x5)                                       /**< (PAC_WRCTRL) Set IP non-secure  */
#define   PAC_WRCTRL_KEY_SECLOCK_Val        _U_(0x6)                                       /**< (PAC_WRCTRL) Lock IP security value  */
#define PAC_WRCTRL_KEY_OFF                  (PAC_WRCTRL_KEY_OFF_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) No action Position  */
#define PAC_WRCTRL_KEY_CLR                  (PAC_WRCTRL_KEY_CLR_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Clear protection Position  */
#define PAC_WRCTRL_KEY_SET                  (PAC_WRCTRL_KEY_SET_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Set protection Position  */
#define PAC_WRCTRL_KEY_SETLCK               (PAC_WRCTRL_KEY_SETLCK_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Set and lock protection Position  */
#define PAC_WRCTRL_KEY_SETSEC               (PAC_WRCTRL_KEY_SETSEC_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Set IP secure Position  */
#define PAC_WRCTRL_KEY_SETNONSEC            (PAC_WRCTRL_KEY_SETNONSEC_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Set IP non-secure Position  */
#define PAC_WRCTRL_KEY_SECLOCK              (PAC_WRCTRL_KEY_SECLOCK_Val << PAC_WRCTRL_KEY_Pos)  /**< (PAC_WRCTRL) Lock IP security value Position  */
#define PAC_WRCTRL_MASK                     _U_(0xFFFFFF)                                  /**< \deprecated (PAC_WRCTRL) Register MASK  (Use PAC_WRCTRL_Msk instead)  */
#define PAC_WRCTRL_Msk                      _U_(0xFFFFFF)                                  /**< (PAC_WRCTRL) Register Mask  */


/* -------- PAC_EVCTRL : (PAC Offset: 0x04) (R/W 8) Event control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ERREO:1;                   /**< bit:      0  Peripheral acess error event output      */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PAC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_EVCTRL_OFFSET                   (0x04)                                        /**<  (PAC_EVCTRL) Event control  Offset */
#define PAC_EVCTRL_RESETVALUE               _U_(0x00)                                     /**<  (PAC_EVCTRL) Event control  Reset Value */

#define PAC_EVCTRL_ERREO_Pos                0                                              /**< (PAC_EVCTRL) Peripheral acess error event output Position */
#define PAC_EVCTRL_ERREO_Msk                (_U_(0x1) << PAC_EVCTRL_ERREO_Pos)             /**< (PAC_EVCTRL) Peripheral acess error event output Mask */
#define PAC_EVCTRL_ERREO                    PAC_EVCTRL_ERREO_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_EVCTRL_ERREO_Msk instead */
#define PAC_EVCTRL_MASK                     _U_(0x01)                                      /**< \deprecated (PAC_EVCTRL) Register MASK  (Use PAC_EVCTRL_Msk instead)  */
#define PAC_EVCTRL_Msk                      _U_(0x01)                                      /**< (PAC_EVCTRL) Register Mask  */


/* -------- PAC_INTENCLR : (PAC Offset: 0x08) (R/W 8) Interrupt enable clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ERR:1;                     /**< bit:      0  Peripheral access error interrupt disable */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PAC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTENCLR_OFFSET                 (0x08)                                        /**<  (PAC_INTENCLR) Interrupt enable clear  Offset */
#define PAC_INTENCLR_RESETVALUE             _U_(0x00)                                     /**<  (PAC_INTENCLR) Interrupt enable clear  Reset Value */

#define PAC_INTENCLR_ERR_Pos                0                                              /**< (PAC_INTENCLR) Peripheral access error interrupt disable Position */
#define PAC_INTENCLR_ERR_Msk                (_U_(0x1) << PAC_INTENCLR_ERR_Pos)             /**< (PAC_INTENCLR) Peripheral access error interrupt disable Mask */
#define PAC_INTENCLR_ERR                    PAC_INTENCLR_ERR_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTENCLR_ERR_Msk instead */
#define PAC_INTENCLR_MASK                   _U_(0x01)                                      /**< \deprecated (PAC_INTENCLR) Register MASK  (Use PAC_INTENCLR_Msk instead)  */
#define PAC_INTENCLR_Msk                    _U_(0x01)                                      /**< (PAC_INTENCLR) Register Mask  */


/* -------- PAC_INTENSET : (PAC Offset: 0x09) (R/W 8) Interrupt enable set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ERR:1;                     /**< bit:      0  Peripheral access error interrupt enable */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PAC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTENSET_OFFSET                 (0x09)                                        /**<  (PAC_INTENSET) Interrupt enable set  Offset */
#define PAC_INTENSET_RESETVALUE             _U_(0x00)                                     /**<  (PAC_INTENSET) Interrupt enable set  Reset Value */

#define PAC_INTENSET_ERR_Pos                0                                              /**< (PAC_INTENSET) Peripheral access error interrupt enable Position */
#define PAC_INTENSET_ERR_Msk                (_U_(0x1) << PAC_INTENSET_ERR_Pos)             /**< (PAC_INTENSET) Peripheral access error interrupt enable Mask */
#define PAC_INTENSET_ERR                    PAC_INTENSET_ERR_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTENSET_ERR_Msk instead */
#define PAC_INTENSET_MASK                   _U_(0x01)                                      /**< \deprecated (PAC_INTENSET) Register MASK  (Use PAC_INTENSET_Msk instead)  */
#define PAC_INTENSET_Msk                    _U_(0x01)                                      /**< (PAC_INTENSET) Register Mask  */


/* -------- PAC_INTFLAGAHB : (PAC Offset: 0x10) (R/W 32) Bridge interrupt flag status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t FLASH_:1;                  /**< bit:      0  FLASH                                    */
    __I uint32_t HPB0_:1;                   /**< bit:      1  HPB0                                     */
    __I uint32_t HPB1_:1;                   /**< bit:      2  HPB1                                     */
    __I uint32_t HPB2_:1;                   /**< bit:      3  HPB2                                     */
    __I uint32_t HSRAMCPU_:1;               /**< bit:      4  HSRAMCPU                                 */
    __I uint32_t HSRAMDMAC_:1;              /**< bit:      5  HSRAMDMAC                                */
    __I uint32_t HSRAMDSU_:1;               /**< bit:      6  HSRAMDSU                                 */
    __I uint32_t :25;                       /**< bit:  7..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_INTFLAGAHB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGAHB_OFFSET               (0x10)                                        /**<  (PAC_INTFLAGAHB) Bridge interrupt flag status  Offset */
#define PAC_INTFLAGAHB_RESETVALUE           _U_(0x00)                                     /**<  (PAC_INTFLAGAHB) Bridge interrupt flag status  Reset Value */

#define PAC_INTFLAGAHB_FLASH_Pos            0                                              /**< (PAC_INTFLAGAHB) FLASH Position */
#define PAC_INTFLAGAHB_FLASH_Msk            (_U_(0x1) << PAC_INTFLAGAHB_FLASH_Pos)         /**< (PAC_INTFLAGAHB) FLASH Mask */
#define PAC_INTFLAGAHB_FLASH                PAC_INTFLAGAHB_FLASH_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_FLASH_Msk instead */
#define PAC_INTFLAGAHB_HPB0_Pos             1                                              /**< (PAC_INTFLAGAHB) HPB0 Position */
#define PAC_INTFLAGAHB_HPB0_Msk             (_U_(0x1) << PAC_INTFLAGAHB_HPB0_Pos)          /**< (PAC_INTFLAGAHB) HPB0 Mask */
#define PAC_INTFLAGAHB_HPB0                 PAC_INTFLAGAHB_HPB0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HPB0_Msk instead */
#define PAC_INTFLAGAHB_HPB1_Pos             2                                              /**< (PAC_INTFLAGAHB) HPB1 Position */
#define PAC_INTFLAGAHB_HPB1_Msk             (_U_(0x1) << PAC_INTFLAGAHB_HPB1_Pos)          /**< (PAC_INTFLAGAHB) HPB1 Mask */
#define PAC_INTFLAGAHB_HPB1                 PAC_INTFLAGAHB_HPB1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HPB1_Msk instead */
#define PAC_INTFLAGAHB_HPB2_Pos             3                                              /**< (PAC_INTFLAGAHB) HPB2 Position */
#define PAC_INTFLAGAHB_HPB2_Msk             (_U_(0x1) << PAC_INTFLAGAHB_HPB2_Pos)          /**< (PAC_INTFLAGAHB) HPB2 Mask */
#define PAC_INTFLAGAHB_HPB2                 PAC_INTFLAGAHB_HPB2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HPB2_Msk instead */
#define PAC_INTFLAGAHB_HSRAMCPU_Pos         4                                              /**< (PAC_INTFLAGAHB) HSRAMCPU Position */
#define PAC_INTFLAGAHB_HSRAMCPU_Msk         (_U_(0x1) << PAC_INTFLAGAHB_HSRAMCPU_Pos)      /**< (PAC_INTFLAGAHB) HSRAMCPU Mask */
#define PAC_INTFLAGAHB_HSRAMCPU             PAC_INTFLAGAHB_HSRAMCPU_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HSRAMCPU_Msk instead */
#define PAC_INTFLAGAHB_HSRAMDMAC_Pos        5                                              /**< (PAC_INTFLAGAHB) HSRAMDMAC Position */
#define PAC_INTFLAGAHB_HSRAMDMAC_Msk        (_U_(0x1) << PAC_INTFLAGAHB_HSRAMDMAC_Pos)     /**< (PAC_INTFLAGAHB) HSRAMDMAC Mask */
#define PAC_INTFLAGAHB_HSRAMDMAC            PAC_INTFLAGAHB_HSRAMDMAC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HSRAMDMAC_Msk instead */
#define PAC_INTFLAGAHB_HSRAMDSU_Pos         6                                              /**< (PAC_INTFLAGAHB) HSRAMDSU Position */
#define PAC_INTFLAGAHB_HSRAMDSU_Msk         (_U_(0x1) << PAC_INTFLAGAHB_HSRAMDSU_Pos)      /**< (PAC_INTFLAGAHB) HSRAMDSU Mask */
#define PAC_INTFLAGAHB_HSRAMDSU             PAC_INTFLAGAHB_HSRAMDSU_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGAHB_HSRAMDSU_Msk instead */
#define PAC_INTFLAGAHB_MASK                 _U_(0x7F)                                      /**< \deprecated (PAC_INTFLAGAHB) Register MASK  (Use PAC_INTFLAGAHB_Msk instead)  */
#define PAC_INTFLAGAHB_Msk                  _U_(0x7F)                                      /**< (PAC_INTFLAGAHB) Register Mask  */

#define PAC_INTFLAGAHB_HPB_Pos              1                                              /**< (PAC_INTFLAGAHB Position) HPBx */
#define PAC_INTFLAGAHB_HPB_Msk              (_U_(0x7) << PAC_INTFLAGAHB_HPB_Pos)           /**< (PAC_INTFLAGAHB Mask) HPB */
#define PAC_INTFLAGAHB_HPB(value)           (PAC_INTFLAGAHB_HPB_Msk & ((value) << PAC_INTFLAGAHB_HPB_Pos))  

/* -------- PAC_INTFLAGA : (PAC Offset: 0x14) (R/W 32) Peripheral interrupt flag status - Bridge A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t PAC_:1;                    /**< bit:      0  PAC                                      */
    __I uint32_t PM_:1;                     /**< bit:      1  PM                                       */
    __I uint32_t MCLK_:1;                   /**< bit:      2  MCLK                                     */
    __I uint32_t RSTC_:1;                   /**< bit:      3  RSTC                                     */
    __I uint32_t OSCCTRL_:1;                /**< bit:      4  OSCCTRL                                  */
    __I uint32_t OSC32KCTRL_:1;             /**< bit:      5  OSC32KCTRL                               */
    __I uint32_t SUPC_:1;                   /**< bit:      6  SUPC                                     */
    __I uint32_t GCLK_:1;                   /**< bit:      7  GCLK                                     */
    __I uint32_t WDT_:1;                    /**< bit:      8  WDT                                      */
    __I uint32_t RTC_:1;                    /**< bit:      9  RTC                                      */
    __I uint32_t EIC_:1;                    /**< bit:     10  EIC                                      */
    __I uint32_t FREQM_:1;                  /**< bit:     11  FREQM                                    */
    __I uint32_t PORT_:1;                   /**< bit:     12  PORT                                     */
    __I uint32_t AC_:1;                     /**< bit:     13  AC                                       */
    __I uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_INTFLAGA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGA_OFFSET                 (0x14)                                        /**<  (PAC_INTFLAGA) Peripheral interrupt flag status - Bridge A  Offset */
#define PAC_INTFLAGA_RESETVALUE             _U_(0x00)                                     /**<  (PAC_INTFLAGA) Peripheral interrupt flag status - Bridge A  Reset Value */

#define PAC_INTFLAGA_PAC_Pos                0                                              /**< (PAC_INTFLAGA) PAC Position */
#define PAC_INTFLAGA_PAC_Msk                (_U_(0x1) << PAC_INTFLAGA_PAC_Pos)             /**< (PAC_INTFLAGA) PAC Mask */
#define PAC_INTFLAGA_PAC                    PAC_INTFLAGA_PAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_PAC_Msk instead */
#define PAC_INTFLAGA_PM_Pos                 1                                              /**< (PAC_INTFLAGA) PM Position */
#define PAC_INTFLAGA_PM_Msk                 (_U_(0x1) << PAC_INTFLAGA_PM_Pos)              /**< (PAC_INTFLAGA) PM Mask */
#define PAC_INTFLAGA_PM                     PAC_INTFLAGA_PM_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_PM_Msk instead */
#define PAC_INTFLAGA_MCLK_Pos               2                                              /**< (PAC_INTFLAGA) MCLK Position */
#define PAC_INTFLAGA_MCLK_Msk               (_U_(0x1) << PAC_INTFLAGA_MCLK_Pos)            /**< (PAC_INTFLAGA) MCLK Mask */
#define PAC_INTFLAGA_MCLK                   PAC_INTFLAGA_MCLK_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_MCLK_Msk instead */
#define PAC_INTFLAGA_RSTC_Pos               3                                              /**< (PAC_INTFLAGA) RSTC Position */
#define PAC_INTFLAGA_RSTC_Msk               (_U_(0x1) << PAC_INTFLAGA_RSTC_Pos)            /**< (PAC_INTFLAGA) RSTC Mask */
#define PAC_INTFLAGA_RSTC                   PAC_INTFLAGA_RSTC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_RSTC_Msk instead */
#define PAC_INTFLAGA_OSCCTRL_Pos            4                                              /**< (PAC_INTFLAGA) OSCCTRL Position */
#define PAC_INTFLAGA_OSCCTRL_Msk            (_U_(0x1) << PAC_INTFLAGA_OSCCTRL_Pos)         /**< (PAC_INTFLAGA) OSCCTRL Mask */
#define PAC_INTFLAGA_OSCCTRL                PAC_INTFLAGA_OSCCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_OSCCTRL_Msk instead */
#define PAC_INTFLAGA_OSC32KCTRL_Pos         5                                              /**< (PAC_INTFLAGA) OSC32KCTRL Position */
#define PAC_INTFLAGA_OSC32KCTRL_Msk         (_U_(0x1) << PAC_INTFLAGA_OSC32KCTRL_Pos)      /**< (PAC_INTFLAGA) OSC32KCTRL Mask */
#define PAC_INTFLAGA_OSC32KCTRL             PAC_INTFLAGA_OSC32KCTRL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_OSC32KCTRL_Msk instead */
#define PAC_INTFLAGA_SUPC_Pos               6                                              /**< (PAC_INTFLAGA) SUPC Position */
#define PAC_INTFLAGA_SUPC_Msk               (_U_(0x1) << PAC_INTFLAGA_SUPC_Pos)            /**< (PAC_INTFLAGA) SUPC Mask */
#define PAC_INTFLAGA_SUPC                   PAC_INTFLAGA_SUPC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_SUPC_Msk instead */
#define PAC_INTFLAGA_GCLK_Pos               7                                              /**< (PAC_INTFLAGA) GCLK Position */
#define PAC_INTFLAGA_GCLK_Msk               (_U_(0x1) << PAC_INTFLAGA_GCLK_Pos)            /**< (PAC_INTFLAGA) GCLK Mask */
#define PAC_INTFLAGA_GCLK                   PAC_INTFLAGA_GCLK_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_GCLK_Msk instead */
#define PAC_INTFLAGA_WDT_Pos                8                                              /**< (PAC_INTFLAGA) WDT Position */
#define PAC_INTFLAGA_WDT_Msk                (_U_(0x1) << PAC_INTFLAGA_WDT_Pos)             /**< (PAC_INTFLAGA) WDT Mask */
#define PAC_INTFLAGA_WDT                    PAC_INTFLAGA_WDT_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_WDT_Msk instead */
#define PAC_INTFLAGA_RTC_Pos                9                                              /**< (PAC_INTFLAGA) RTC Position */
#define PAC_INTFLAGA_RTC_Msk                (_U_(0x1) << PAC_INTFLAGA_RTC_Pos)             /**< (PAC_INTFLAGA) RTC Mask */
#define PAC_INTFLAGA_RTC                    PAC_INTFLAGA_RTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_RTC_Msk instead */
#define PAC_INTFLAGA_EIC_Pos                10                                             /**< (PAC_INTFLAGA) EIC Position */
#define PAC_INTFLAGA_EIC_Msk                (_U_(0x1) << PAC_INTFLAGA_EIC_Pos)             /**< (PAC_INTFLAGA) EIC Mask */
#define PAC_INTFLAGA_EIC                    PAC_INTFLAGA_EIC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_EIC_Msk instead */
#define PAC_INTFLAGA_FREQM_Pos              11                                             /**< (PAC_INTFLAGA) FREQM Position */
#define PAC_INTFLAGA_FREQM_Msk              (_U_(0x1) << PAC_INTFLAGA_FREQM_Pos)           /**< (PAC_INTFLAGA) FREQM Mask */
#define PAC_INTFLAGA_FREQM                  PAC_INTFLAGA_FREQM_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_FREQM_Msk instead */
#define PAC_INTFLAGA_PORT_Pos               12                                             /**< (PAC_INTFLAGA) PORT Position */
#define PAC_INTFLAGA_PORT_Msk               (_U_(0x1) << PAC_INTFLAGA_PORT_Pos)            /**< (PAC_INTFLAGA) PORT Mask */
#define PAC_INTFLAGA_PORT                   PAC_INTFLAGA_PORT_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_PORT_Msk instead */
#define PAC_INTFLAGA_AC_Pos                 13                                             /**< (PAC_INTFLAGA) AC Position */
#define PAC_INTFLAGA_AC_Msk                 (_U_(0x1) << PAC_INTFLAGA_AC_Pos)              /**< (PAC_INTFLAGA) AC Mask */
#define PAC_INTFLAGA_AC                     PAC_INTFLAGA_AC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGA_AC_Msk instead */
#define PAC_INTFLAGA_MASK                   _U_(0x3FFF)                                    /**< \deprecated (PAC_INTFLAGA) Register MASK  (Use PAC_INTFLAGA_Msk instead)  */
#define PAC_INTFLAGA_Msk                    _U_(0x3FFF)                                    /**< (PAC_INTFLAGA) Register Mask  */


/* -------- PAC_INTFLAGB : (PAC Offset: 0x18) (R/W 32) Peripheral interrupt flag status - Bridge B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t IDAU_:1;                   /**< bit:      0  IDAU                                     */
    __I uint32_t DSU_:1;                    /**< bit:      1  DSU                                      */
    __I uint32_t NVMCTRL_:1;                /**< bit:      2  NVMCTRL                                  */
    __I uint32_t DMAC_:1;                   /**< bit:      3  DMAC                                     */
    __I uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_INTFLAGB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGB_OFFSET                 (0x18)                                        /**<  (PAC_INTFLAGB) Peripheral interrupt flag status - Bridge B  Offset */
#define PAC_INTFLAGB_RESETVALUE             _U_(0x00)                                     /**<  (PAC_INTFLAGB) Peripheral interrupt flag status - Bridge B  Reset Value */

#define PAC_INTFLAGB_IDAU_Pos               0                                              /**< (PAC_INTFLAGB) IDAU Position */
#define PAC_INTFLAGB_IDAU_Msk               (_U_(0x1) << PAC_INTFLAGB_IDAU_Pos)            /**< (PAC_INTFLAGB) IDAU Mask */
#define PAC_INTFLAGB_IDAU                   PAC_INTFLAGB_IDAU_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGB_IDAU_Msk instead */
#define PAC_INTFLAGB_DSU_Pos                1                                              /**< (PAC_INTFLAGB) DSU Position */
#define PAC_INTFLAGB_DSU_Msk                (_U_(0x1) << PAC_INTFLAGB_DSU_Pos)             /**< (PAC_INTFLAGB) DSU Mask */
#define PAC_INTFLAGB_DSU                    PAC_INTFLAGB_DSU_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGB_DSU_Msk instead */
#define PAC_INTFLAGB_NVMCTRL_Pos            2                                              /**< (PAC_INTFLAGB) NVMCTRL Position */
#define PAC_INTFLAGB_NVMCTRL_Msk            (_U_(0x1) << PAC_INTFLAGB_NVMCTRL_Pos)         /**< (PAC_INTFLAGB) NVMCTRL Mask */
#define PAC_INTFLAGB_NVMCTRL                PAC_INTFLAGB_NVMCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGB_NVMCTRL_Msk instead */
#define PAC_INTFLAGB_DMAC_Pos               3                                              /**< (PAC_INTFLAGB) DMAC Position */
#define PAC_INTFLAGB_DMAC_Msk               (_U_(0x1) << PAC_INTFLAGB_DMAC_Pos)            /**< (PAC_INTFLAGB) DMAC Mask */
#define PAC_INTFLAGB_DMAC                   PAC_INTFLAGB_DMAC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGB_DMAC_Msk instead */
#define PAC_INTFLAGB_MASK                   _U_(0x0F)                                      /**< \deprecated (PAC_INTFLAGB) Register MASK  (Use PAC_INTFLAGB_Msk instead)  */
#define PAC_INTFLAGB_Msk                    _U_(0x0F)                                      /**< (PAC_INTFLAGB) Register Mask  */


/* -------- PAC_INTFLAGC : (PAC Offset: 0x1c) (R/W 32) Peripheral interrupt flag status - Bridge C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t EVSYS_:1;                  /**< bit:      0  EVSYS                                    */
    __I uint32_t SERCOM0_:1;                /**< bit:      1  SERCOM0                                  */
    __I uint32_t SERCOM1_:1;                /**< bit:      2  SERCOM1                                  */
    __I uint32_t SERCOM2_:1;                /**< bit:      3  SERCOM2                                  */
    __I uint32_t TC0_:1;                    /**< bit:      4  TC0                                      */
    __I uint32_t TC1_:1;                    /**< bit:      5  TC1                                      */
    __I uint32_t TC2_:1;                    /**< bit:      6  TC2                                      */
    __I uint32_t ADC_:1;                    /**< bit:      7  ADC                                      */
    __I uint32_t DAC_:1;                    /**< bit:      8  DAC                                      */
    __I uint32_t PTC_:1;                    /**< bit:      9  PTC                                      */
    __I uint32_t TRNG_:1;                   /**< bit:     10  TRNG                                     */
    __I uint32_t CCL_:1;                    /**< bit:     11  CCL                                      */
    __I uint32_t OPAMP_:1;                  /**< bit:     12  OPAMP                                    */
    __I uint32_t TRAM_:1;                   /**< bit:     13  TRAM                                     */
    __I uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_INTFLAGC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGC_OFFSET                 (0x1C)                                        /**<  (PAC_INTFLAGC) Peripheral interrupt flag status - Bridge C  Offset */
#define PAC_INTFLAGC_RESETVALUE             _U_(0x00)                                     /**<  (PAC_INTFLAGC) Peripheral interrupt flag status - Bridge C  Reset Value */

#define PAC_INTFLAGC_EVSYS_Pos              0                                              /**< (PAC_INTFLAGC) EVSYS Position */
#define PAC_INTFLAGC_EVSYS_Msk              (_U_(0x1) << PAC_INTFLAGC_EVSYS_Pos)           /**< (PAC_INTFLAGC) EVSYS Mask */
#define PAC_INTFLAGC_EVSYS                  PAC_INTFLAGC_EVSYS_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_EVSYS_Msk instead */
#define PAC_INTFLAGC_SERCOM0_Pos            1                                              /**< (PAC_INTFLAGC) SERCOM0 Position */
#define PAC_INTFLAGC_SERCOM0_Msk            (_U_(0x1) << PAC_INTFLAGC_SERCOM0_Pos)         /**< (PAC_INTFLAGC) SERCOM0 Mask */
#define PAC_INTFLAGC_SERCOM0                PAC_INTFLAGC_SERCOM0_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_SERCOM0_Msk instead */
#define PAC_INTFLAGC_SERCOM1_Pos            2                                              /**< (PAC_INTFLAGC) SERCOM1 Position */
#define PAC_INTFLAGC_SERCOM1_Msk            (_U_(0x1) << PAC_INTFLAGC_SERCOM1_Pos)         /**< (PAC_INTFLAGC) SERCOM1 Mask */
#define PAC_INTFLAGC_SERCOM1                PAC_INTFLAGC_SERCOM1_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_SERCOM1_Msk instead */
#define PAC_INTFLAGC_SERCOM2_Pos            3                                              /**< (PAC_INTFLAGC) SERCOM2 Position */
#define PAC_INTFLAGC_SERCOM2_Msk            (_U_(0x1) << PAC_INTFLAGC_SERCOM2_Pos)         /**< (PAC_INTFLAGC) SERCOM2 Mask */
#define PAC_INTFLAGC_SERCOM2                PAC_INTFLAGC_SERCOM2_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_SERCOM2_Msk instead */
#define PAC_INTFLAGC_TC0_Pos                4                                              /**< (PAC_INTFLAGC) TC0 Position */
#define PAC_INTFLAGC_TC0_Msk                (_U_(0x1) << PAC_INTFLAGC_TC0_Pos)             /**< (PAC_INTFLAGC) TC0 Mask */
#define PAC_INTFLAGC_TC0                    PAC_INTFLAGC_TC0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_TC0_Msk instead */
#define PAC_INTFLAGC_TC1_Pos                5                                              /**< (PAC_INTFLAGC) TC1 Position */
#define PAC_INTFLAGC_TC1_Msk                (_U_(0x1) << PAC_INTFLAGC_TC1_Pos)             /**< (PAC_INTFLAGC) TC1 Mask */
#define PAC_INTFLAGC_TC1                    PAC_INTFLAGC_TC1_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_TC1_Msk instead */
#define PAC_INTFLAGC_TC2_Pos                6                                              /**< (PAC_INTFLAGC) TC2 Position */
#define PAC_INTFLAGC_TC2_Msk                (_U_(0x1) << PAC_INTFLAGC_TC2_Pos)             /**< (PAC_INTFLAGC) TC2 Mask */
#define PAC_INTFLAGC_TC2                    PAC_INTFLAGC_TC2_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_TC2_Msk instead */
#define PAC_INTFLAGC_ADC_Pos                7                                              /**< (PAC_INTFLAGC) ADC Position */
#define PAC_INTFLAGC_ADC_Msk                (_U_(0x1) << PAC_INTFLAGC_ADC_Pos)             /**< (PAC_INTFLAGC) ADC Mask */
#define PAC_INTFLAGC_ADC                    PAC_INTFLAGC_ADC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_ADC_Msk instead */
#define PAC_INTFLAGC_DAC_Pos                8                                              /**< (PAC_INTFLAGC) DAC Position */
#define PAC_INTFLAGC_DAC_Msk                (_U_(0x1) << PAC_INTFLAGC_DAC_Pos)             /**< (PAC_INTFLAGC) DAC Mask */
#define PAC_INTFLAGC_DAC                    PAC_INTFLAGC_DAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_DAC_Msk instead */
#define PAC_INTFLAGC_PTC_Pos                9                                              /**< (PAC_INTFLAGC) PTC Position */
#define PAC_INTFLAGC_PTC_Msk                (_U_(0x1) << PAC_INTFLAGC_PTC_Pos)             /**< (PAC_INTFLAGC) PTC Mask */
#define PAC_INTFLAGC_PTC                    PAC_INTFLAGC_PTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_PTC_Msk instead */
#define PAC_INTFLAGC_TRNG_Pos               10                                             /**< (PAC_INTFLAGC) TRNG Position */
#define PAC_INTFLAGC_TRNG_Msk               (_U_(0x1) << PAC_INTFLAGC_TRNG_Pos)            /**< (PAC_INTFLAGC) TRNG Mask */
#define PAC_INTFLAGC_TRNG                   PAC_INTFLAGC_TRNG_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_TRNG_Msk instead */
#define PAC_INTFLAGC_CCL_Pos                11                                             /**< (PAC_INTFLAGC) CCL Position */
#define PAC_INTFLAGC_CCL_Msk                (_U_(0x1) << PAC_INTFLAGC_CCL_Pos)             /**< (PAC_INTFLAGC) CCL Mask */
#define PAC_INTFLAGC_CCL                    PAC_INTFLAGC_CCL_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_CCL_Msk instead */
#define PAC_INTFLAGC_OPAMP_Pos              12                                             /**< (PAC_INTFLAGC) OPAMP Position */
#define PAC_INTFLAGC_OPAMP_Msk              (_U_(0x1) << PAC_INTFLAGC_OPAMP_Pos)           /**< (PAC_INTFLAGC) OPAMP Mask */
#define PAC_INTFLAGC_OPAMP                  PAC_INTFLAGC_OPAMP_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_OPAMP_Msk instead */
#define PAC_INTFLAGC_TRAM_Pos               13                                             /**< (PAC_INTFLAGC) TRAM Position */
#define PAC_INTFLAGC_TRAM_Msk               (_U_(0x1) << PAC_INTFLAGC_TRAM_Pos)            /**< (PAC_INTFLAGC) TRAM Mask */
#define PAC_INTFLAGC_TRAM                   PAC_INTFLAGC_TRAM_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_INTFLAGC_TRAM_Msk instead */
#define PAC_INTFLAGC_MASK                   _U_(0x3FFF)                                    /**< \deprecated (PAC_INTFLAGC) Register MASK  (Use PAC_INTFLAGC_Msk instead)  */
#define PAC_INTFLAGC_Msk                    _U_(0x3FFF)                                    /**< (PAC_INTFLAGC) Register Mask  */

#define PAC_INTFLAGC_SERCOM_Pos             1                                              /**< (PAC_INTFLAGC Position) SERCOMx */
#define PAC_INTFLAGC_SERCOM_Msk             (_U_(0x7) << PAC_INTFLAGC_SERCOM_Pos)          /**< (PAC_INTFLAGC Mask) SERCOM */
#define PAC_INTFLAGC_SERCOM(value)          (PAC_INTFLAGC_SERCOM_Msk & ((value) << PAC_INTFLAGC_SERCOM_Pos))  
#define PAC_INTFLAGC_TC_Pos                 4                                              /**< (PAC_INTFLAGC Position) TCx */
#define PAC_INTFLAGC_TC_Msk                 (_U_(0x7) << PAC_INTFLAGC_TC_Pos)              /**< (PAC_INTFLAGC Mask) TC */
#define PAC_INTFLAGC_TC(value)              (PAC_INTFLAGC_TC_Msk & ((value) << PAC_INTFLAGC_TC_Pos))  

/* -------- PAC_STATUSA : (PAC Offset: 0x34) (R/ 32) Peripheral write protection status - Bridge A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PAC_:1;                    /**< bit:      0  PAC APB Protect Enable                   */
    uint32_t PM_:1;                     /**< bit:      1  PM APB Protect Enable                    */
    uint32_t MCLK_:1;                   /**< bit:      2  MCLK APB Protect Enable                  */
    uint32_t RSTC_:1;                   /**< bit:      3  RSTC APB Protect Enable                  */
    uint32_t OSCCTRL_:1;                /**< bit:      4  OSCCTRL APB Protect Enable               */
    uint32_t OSC32KCTRL_:1;             /**< bit:      5  OSC32KCTRL APB Protect Enable            */
    uint32_t SUPC_:1;                   /**< bit:      6  SUPC APB Protect Enable                  */
    uint32_t GCLK_:1;                   /**< bit:      7  GCLK APB Protect Enable                  */
    uint32_t WDT_:1;                    /**< bit:      8  WDT APB Protect Enable                   */
    uint32_t RTC_:1;                    /**< bit:      9  RTC APB Protect Enable                   */
    uint32_t EIC_:1;                    /**< bit:     10  EIC APB Protect Enable                   */
    uint32_t FREQM_:1;                  /**< bit:     11  FREQM APB Protect Enable                 */
    uint32_t PORT_:1;                   /**< bit:     12  PORT APB Protect Enable                  */
    uint32_t AC_:1;                     /**< bit:     13  AC APB Protect Enable                    */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_STATUSA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSA_OFFSET                  (0x34)                                        /**<  (PAC_STATUSA) Peripheral write protection status - Bridge A  Offset */
#define PAC_STATUSA_RESETVALUE              _U_(0xC000)                                   /**<  (PAC_STATUSA) Peripheral write protection status - Bridge A  Reset Value */

#define PAC_STATUSA_PAC_Pos                 0                                              /**< (PAC_STATUSA) PAC APB Protect Enable Position */
#define PAC_STATUSA_PAC_Msk                 (_U_(0x1) << PAC_STATUSA_PAC_Pos)              /**< (PAC_STATUSA) PAC APB Protect Enable Mask */
#define PAC_STATUSA_PAC                     PAC_STATUSA_PAC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_PAC_Msk instead */
#define PAC_STATUSA_PM_Pos                  1                                              /**< (PAC_STATUSA) PM APB Protect Enable Position */
#define PAC_STATUSA_PM_Msk                  (_U_(0x1) << PAC_STATUSA_PM_Pos)               /**< (PAC_STATUSA) PM APB Protect Enable Mask */
#define PAC_STATUSA_PM                      PAC_STATUSA_PM_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_PM_Msk instead */
#define PAC_STATUSA_MCLK_Pos                2                                              /**< (PAC_STATUSA) MCLK APB Protect Enable Position */
#define PAC_STATUSA_MCLK_Msk                (_U_(0x1) << PAC_STATUSA_MCLK_Pos)             /**< (PAC_STATUSA) MCLK APB Protect Enable Mask */
#define PAC_STATUSA_MCLK                    PAC_STATUSA_MCLK_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_MCLK_Msk instead */
#define PAC_STATUSA_RSTC_Pos                3                                              /**< (PAC_STATUSA) RSTC APB Protect Enable Position */
#define PAC_STATUSA_RSTC_Msk                (_U_(0x1) << PAC_STATUSA_RSTC_Pos)             /**< (PAC_STATUSA) RSTC APB Protect Enable Mask */
#define PAC_STATUSA_RSTC                    PAC_STATUSA_RSTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_RSTC_Msk instead */
#define PAC_STATUSA_OSCCTRL_Pos             4                                              /**< (PAC_STATUSA) OSCCTRL APB Protect Enable Position */
#define PAC_STATUSA_OSCCTRL_Msk             (_U_(0x1) << PAC_STATUSA_OSCCTRL_Pos)          /**< (PAC_STATUSA) OSCCTRL APB Protect Enable Mask */
#define PAC_STATUSA_OSCCTRL                 PAC_STATUSA_OSCCTRL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_OSCCTRL_Msk instead */
#define PAC_STATUSA_OSC32KCTRL_Pos          5                                              /**< (PAC_STATUSA) OSC32KCTRL APB Protect Enable Position */
#define PAC_STATUSA_OSC32KCTRL_Msk          (_U_(0x1) << PAC_STATUSA_OSC32KCTRL_Pos)       /**< (PAC_STATUSA) OSC32KCTRL APB Protect Enable Mask */
#define PAC_STATUSA_OSC32KCTRL              PAC_STATUSA_OSC32KCTRL_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_OSC32KCTRL_Msk instead */
#define PAC_STATUSA_SUPC_Pos                6                                              /**< (PAC_STATUSA) SUPC APB Protect Enable Position */
#define PAC_STATUSA_SUPC_Msk                (_U_(0x1) << PAC_STATUSA_SUPC_Pos)             /**< (PAC_STATUSA) SUPC APB Protect Enable Mask */
#define PAC_STATUSA_SUPC                    PAC_STATUSA_SUPC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_SUPC_Msk instead */
#define PAC_STATUSA_GCLK_Pos                7                                              /**< (PAC_STATUSA) GCLK APB Protect Enable Position */
#define PAC_STATUSA_GCLK_Msk                (_U_(0x1) << PAC_STATUSA_GCLK_Pos)             /**< (PAC_STATUSA) GCLK APB Protect Enable Mask */
#define PAC_STATUSA_GCLK                    PAC_STATUSA_GCLK_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_GCLK_Msk instead */
#define PAC_STATUSA_WDT_Pos                 8                                              /**< (PAC_STATUSA) WDT APB Protect Enable Position */
#define PAC_STATUSA_WDT_Msk                 (_U_(0x1) << PAC_STATUSA_WDT_Pos)              /**< (PAC_STATUSA) WDT APB Protect Enable Mask */
#define PAC_STATUSA_WDT                     PAC_STATUSA_WDT_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_WDT_Msk instead */
#define PAC_STATUSA_RTC_Pos                 9                                              /**< (PAC_STATUSA) RTC APB Protect Enable Position */
#define PAC_STATUSA_RTC_Msk                 (_U_(0x1) << PAC_STATUSA_RTC_Pos)              /**< (PAC_STATUSA) RTC APB Protect Enable Mask */
#define PAC_STATUSA_RTC                     PAC_STATUSA_RTC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_RTC_Msk instead */
#define PAC_STATUSA_EIC_Pos                 10                                             /**< (PAC_STATUSA) EIC APB Protect Enable Position */
#define PAC_STATUSA_EIC_Msk                 (_U_(0x1) << PAC_STATUSA_EIC_Pos)              /**< (PAC_STATUSA) EIC APB Protect Enable Mask */
#define PAC_STATUSA_EIC                     PAC_STATUSA_EIC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_EIC_Msk instead */
#define PAC_STATUSA_FREQM_Pos               11                                             /**< (PAC_STATUSA) FREQM APB Protect Enable Position */
#define PAC_STATUSA_FREQM_Msk               (_U_(0x1) << PAC_STATUSA_FREQM_Pos)            /**< (PAC_STATUSA) FREQM APB Protect Enable Mask */
#define PAC_STATUSA_FREQM                   PAC_STATUSA_FREQM_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_FREQM_Msk instead */
#define PAC_STATUSA_PORT_Pos                12                                             /**< (PAC_STATUSA) PORT APB Protect Enable Position */
#define PAC_STATUSA_PORT_Msk                (_U_(0x1) << PAC_STATUSA_PORT_Pos)             /**< (PAC_STATUSA) PORT APB Protect Enable Mask */
#define PAC_STATUSA_PORT                    PAC_STATUSA_PORT_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_PORT_Msk instead */
#define PAC_STATUSA_AC_Pos                  13                                             /**< (PAC_STATUSA) AC APB Protect Enable Position */
#define PAC_STATUSA_AC_Msk                  (_U_(0x1) << PAC_STATUSA_AC_Pos)               /**< (PAC_STATUSA) AC APB Protect Enable Mask */
#define PAC_STATUSA_AC                      PAC_STATUSA_AC_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSA_AC_Msk instead */
#define PAC_STATUSA_MASK                    _U_(0x3FFF)                                    /**< \deprecated (PAC_STATUSA) Register MASK  (Use PAC_STATUSA_Msk instead)  */
#define PAC_STATUSA_Msk                     _U_(0x3FFF)                                    /**< (PAC_STATUSA) Register Mask  */


/* -------- PAC_STATUSB : (PAC Offset: 0x38) (R/ 32) Peripheral write protection status - Bridge B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IDAU_:1;                   /**< bit:      0  IDAU APB Protect Enable                  */
    uint32_t DSU_:1;                    /**< bit:      1  DSU APB Protect Enable                   */
    uint32_t NVMCTRL_:1;                /**< bit:      2  NVMCTRL APB Protect Enable               */
    uint32_t DMAC_:1;                   /**< bit:      3  DMAC APB Protect Enable                  */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_STATUSB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSB_OFFSET                  (0x38)                                        /**<  (PAC_STATUSB) Peripheral write protection status - Bridge B  Offset */
#define PAC_STATUSB_RESETVALUE              _U_(0x02)                                     /**<  (PAC_STATUSB) Peripheral write protection status - Bridge B  Reset Value */

#define PAC_STATUSB_IDAU_Pos                0                                              /**< (PAC_STATUSB) IDAU APB Protect Enable Position */
#define PAC_STATUSB_IDAU_Msk                (_U_(0x1) << PAC_STATUSB_IDAU_Pos)             /**< (PAC_STATUSB) IDAU APB Protect Enable Mask */
#define PAC_STATUSB_IDAU                    PAC_STATUSB_IDAU_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSB_IDAU_Msk instead */
#define PAC_STATUSB_DSU_Pos                 1                                              /**< (PAC_STATUSB) DSU APB Protect Enable Position */
#define PAC_STATUSB_DSU_Msk                 (_U_(0x1) << PAC_STATUSB_DSU_Pos)              /**< (PAC_STATUSB) DSU APB Protect Enable Mask */
#define PAC_STATUSB_DSU                     PAC_STATUSB_DSU_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSB_DSU_Msk instead */
#define PAC_STATUSB_NVMCTRL_Pos             2                                              /**< (PAC_STATUSB) NVMCTRL APB Protect Enable Position */
#define PAC_STATUSB_NVMCTRL_Msk             (_U_(0x1) << PAC_STATUSB_NVMCTRL_Pos)          /**< (PAC_STATUSB) NVMCTRL APB Protect Enable Mask */
#define PAC_STATUSB_NVMCTRL                 PAC_STATUSB_NVMCTRL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSB_NVMCTRL_Msk instead */
#define PAC_STATUSB_DMAC_Pos                3                                              /**< (PAC_STATUSB) DMAC APB Protect Enable Position */
#define PAC_STATUSB_DMAC_Msk                (_U_(0x1) << PAC_STATUSB_DMAC_Pos)             /**< (PAC_STATUSB) DMAC APB Protect Enable Mask */
#define PAC_STATUSB_DMAC                    PAC_STATUSB_DMAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSB_DMAC_Msk instead */
#define PAC_STATUSB_MASK                    _U_(0x0F)                                      /**< \deprecated (PAC_STATUSB) Register MASK  (Use PAC_STATUSB_Msk instead)  */
#define PAC_STATUSB_Msk                     _U_(0x0F)                                      /**< (PAC_STATUSB) Register Mask  */


/* -------- PAC_STATUSC : (PAC Offset: 0x3c) (R/ 32) Peripheral write protection status - Bridge C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVSYS_:1;                  /**< bit:      0  EVSYS APB Protect Enable                 */
    uint32_t SERCOM0_:1;                /**< bit:      1  SERCOM0 APB Protect Enable               */
    uint32_t SERCOM1_:1;                /**< bit:      2  SERCOM1 APB Protect Enable               */
    uint32_t SERCOM2_:1;                /**< bit:      3  SERCOM2 APB Protect Enable               */
    uint32_t TC0_:1;                    /**< bit:      4  TC0 APB Protect Enable                   */
    uint32_t TC1_:1;                    /**< bit:      5  TC1 APB Protect Enable                   */
    uint32_t TC2_:1;                    /**< bit:      6  TC2 APB Protect Enable                   */
    uint32_t ADC_:1;                    /**< bit:      7  ADC APB Protect Enable                   */
    uint32_t DAC_:1;                    /**< bit:      8  DAC APB Protect Enable                   */
    uint32_t PTC_:1;                    /**< bit:      9  PTC APB Protect Enable                   */
    uint32_t TRNG_:1;                   /**< bit:     10  TRNG APB Protect Enable                  */
    uint32_t CCL_:1;                    /**< bit:     11  CCL APB Protect Enable                   */
    uint32_t OPAMP_:1;                  /**< bit:     12  OPAMP APB Protect Enable                 */
    uint32_t TRAM_:1;                   /**< bit:     13  TRAM APB Protect Enable                  */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_STATUSC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSC_OFFSET                  (0x3C)                                        /**<  (PAC_STATUSC) Peripheral write protection status - Bridge C  Offset */
#define PAC_STATUSC_RESETVALUE              _U_(0x00)                                     /**<  (PAC_STATUSC) Peripheral write protection status - Bridge C  Reset Value */

#define PAC_STATUSC_EVSYS_Pos               0                                              /**< (PAC_STATUSC) EVSYS APB Protect Enable Position */
#define PAC_STATUSC_EVSYS_Msk               (_U_(0x1) << PAC_STATUSC_EVSYS_Pos)            /**< (PAC_STATUSC) EVSYS APB Protect Enable Mask */
#define PAC_STATUSC_EVSYS                   PAC_STATUSC_EVSYS_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_EVSYS_Msk instead */
#define PAC_STATUSC_SERCOM0_Pos             1                                              /**< (PAC_STATUSC) SERCOM0 APB Protect Enable Position */
#define PAC_STATUSC_SERCOM0_Msk             (_U_(0x1) << PAC_STATUSC_SERCOM0_Pos)          /**< (PAC_STATUSC) SERCOM0 APB Protect Enable Mask */
#define PAC_STATUSC_SERCOM0                 PAC_STATUSC_SERCOM0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_SERCOM0_Msk instead */
#define PAC_STATUSC_SERCOM1_Pos             2                                              /**< (PAC_STATUSC) SERCOM1 APB Protect Enable Position */
#define PAC_STATUSC_SERCOM1_Msk             (_U_(0x1) << PAC_STATUSC_SERCOM1_Pos)          /**< (PAC_STATUSC) SERCOM1 APB Protect Enable Mask */
#define PAC_STATUSC_SERCOM1                 PAC_STATUSC_SERCOM1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_SERCOM1_Msk instead */
#define PAC_STATUSC_SERCOM2_Pos             3                                              /**< (PAC_STATUSC) SERCOM2 APB Protect Enable Position */
#define PAC_STATUSC_SERCOM2_Msk             (_U_(0x1) << PAC_STATUSC_SERCOM2_Pos)          /**< (PAC_STATUSC) SERCOM2 APB Protect Enable Mask */
#define PAC_STATUSC_SERCOM2                 PAC_STATUSC_SERCOM2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_SERCOM2_Msk instead */
#define PAC_STATUSC_TC0_Pos                 4                                              /**< (PAC_STATUSC) TC0 APB Protect Enable Position */
#define PAC_STATUSC_TC0_Msk                 (_U_(0x1) << PAC_STATUSC_TC0_Pos)              /**< (PAC_STATUSC) TC0 APB Protect Enable Mask */
#define PAC_STATUSC_TC0                     PAC_STATUSC_TC0_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_TC0_Msk instead */
#define PAC_STATUSC_TC1_Pos                 5                                              /**< (PAC_STATUSC) TC1 APB Protect Enable Position */
#define PAC_STATUSC_TC1_Msk                 (_U_(0x1) << PAC_STATUSC_TC1_Pos)              /**< (PAC_STATUSC) TC1 APB Protect Enable Mask */
#define PAC_STATUSC_TC1                     PAC_STATUSC_TC1_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_TC1_Msk instead */
#define PAC_STATUSC_TC2_Pos                 6                                              /**< (PAC_STATUSC) TC2 APB Protect Enable Position */
#define PAC_STATUSC_TC2_Msk                 (_U_(0x1) << PAC_STATUSC_TC2_Pos)              /**< (PAC_STATUSC) TC2 APB Protect Enable Mask */
#define PAC_STATUSC_TC2                     PAC_STATUSC_TC2_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_TC2_Msk instead */
#define PAC_STATUSC_ADC_Pos                 7                                              /**< (PAC_STATUSC) ADC APB Protect Enable Position */
#define PAC_STATUSC_ADC_Msk                 (_U_(0x1) << PAC_STATUSC_ADC_Pos)              /**< (PAC_STATUSC) ADC APB Protect Enable Mask */
#define PAC_STATUSC_ADC                     PAC_STATUSC_ADC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_ADC_Msk instead */
#define PAC_STATUSC_DAC_Pos                 8                                              /**< (PAC_STATUSC) DAC APB Protect Enable Position */
#define PAC_STATUSC_DAC_Msk                 (_U_(0x1) << PAC_STATUSC_DAC_Pos)              /**< (PAC_STATUSC) DAC APB Protect Enable Mask */
#define PAC_STATUSC_DAC                     PAC_STATUSC_DAC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_DAC_Msk instead */
#define PAC_STATUSC_PTC_Pos                 9                                              /**< (PAC_STATUSC) PTC APB Protect Enable Position */
#define PAC_STATUSC_PTC_Msk                 (_U_(0x1) << PAC_STATUSC_PTC_Pos)              /**< (PAC_STATUSC) PTC APB Protect Enable Mask */
#define PAC_STATUSC_PTC                     PAC_STATUSC_PTC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_PTC_Msk instead */
#define PAC_STATUSC_TRNG_Pos                10                                             /**< (PAC_STATUSC) TRNG APB Protect Enable Position */
#define PAC_STATUSC_TRNG_Msk                (_U_(0x1) << PAC_STATUSC_TRNG_Pos)             /**< (PAC_STATUSC) TRNG APB Protect Enable Mask */
#define PAC_STATUSC_TRNG                    PAC_STATUSC_TRNG_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_TRNG_Msk instead */
#define PAC_STATUSC_CCL_Pos                 11                                             /**< (PAC_STATUSC) CCL APB Protect Enable Position */
#define PAC_STATUSC_CCL_Msk                 (_U_(0x1) << PAC_STATUSC_CCL_Pos)              /**< (PAC_STATUSC) CCL APB Protect Enable Mask */
#define PAC_STATUSC_CCL                     PAC_STATUSC_CCL_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_CCL_Msk instead */
#define PAC_STATUSC_OPAMP_Pos               12                                             /**< (PAC_STATUSC) OPAMP APB Protect Enable Position */
#define PAC_STATUSC_OPAMP_Msk               (_U_(0x1) << PAC_STATUSC_OPAMP_Pos)            /**< (PAC_STATUSC) OPAMP APB Protect Enable Mask */
#define PAC_STATUSC_OPAMP                   PAC_STATUSC_OPAMP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_OPAMP_Msk instead */
#define PAC_STATUSC_TRAM_Pos                13                                             /**< (PAC_STATUSC) TRAM APB Protect Enable Position */
#define PAC_STATUSC_TRAM_Msk                (_U_(0x1) << PAC_STATUSC_TRAM_Pos)             /**< (PAC_STATUSC) TRAM APB Protect Enable Mask */
#define PAC_STATUSC_TRAM                    PAC_STATUSC_TRAM_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_STATUSC_TRAM_Msk instead */
#define PAC_STATUSC_MASK                    _U_(0x3FFF)                                    /**< \deprecated (PAC_STATUSC) Register MASK  (Use PAC_STATUSC_Msk instead)  */
#define PAC_STATUSC_Msk                     _U_(0x3FFF)                                    /**< (PAC_STATUSC) Register Mask  */

#define PAC_STATUSC_SERCOM_Pos              1                                              /**< (PAC_STATUSC Position) SERCOMx APB Protect Enable */
#define PAC_STATUSC_SERCOM_Msk              (_U_(0x7) << PAC_STATUSC_SERCOM_Pos)           /**< (PAC_STATUSC Mask) SERCOM */
#define PAC_STATUSC_SERCOM(value)           (PAC_STATUSC_SERCOM_Msk & ((value) << PAC_STATUSC_SERCOM_Pos))  
#define PAC_STATUSC_TC_Pos                  4                                              /**< (PAC_STATUSC Position) TCx APB Protect Enable */
#define PAC_STATUSC_TC_Msk                  (_U_(0x7) << PAC_STATUSC_TC_Pos)               /**< (PAC_STATUSC Mask) TC */
#define PAC_STATUSC_TC(value)               (PAC_STATUSC_TC_Msk & ((value) << PAC_STATUSC_TC_Pos))  

/* -------- PAC_NONSECA : (PAC Offset: 0x54) (R/ 32) Peripheral non-secure status - Bridge A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PAC_:1;                    /**< bit:      0  PAC Non-Secure                           */
    uint32_t PM_:1;                     /**< bit:      1  PM Non-Secure                            */
    uint32_t MCLK_:1;                   /**< bit:      2  MCLK Non-Secure                          */
    uint32_t RSTC_:1;                   /**< bit:      3  RSTC Non-Secure                          */
    uint32_t OSCCTRL_:1;                /**< bit:      4  OSCCTRL Non-Secure                       */
    uint32_t OSC32KCTRL_:1;             /**< bit:      5  OSC32KCTRL Non-Secure                    */
    uint32_t SUPC_:1;                   /**< bit:      6  SUPC Non-Secure                          */
    uint32_t GCLK_:1;                   /**< bit:      7  GCLK Non-Secure                          */
    uint32_t WDT_:1;                    /**< bit:      8  WDT Non-Secure                           */
    uint32_t RTC_:1;                    /**< bit:      9  RTC Non-Secure                           */
    uint32_t EIC_:1;                    /**< bit:     10  EIC Non-Secure                           */
    uint32_t FREQM_:1;                  /**< bit:     11  FREQM Non-Secure                         */
    uint32_t PORT_:1;                   /**< bit:     12  PORT Non-Secure                          */
    uint32_t AC_:1;                     /**< bit:     13  AC Non-Secure                            */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_NONSECA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_NONSECA_OFFSET                  (0x54)                                        /**<  (PAC_NONSECA) Peripheral non-secure status - Bridge A  Offset */
#define PAC_NONSECA_RESETVALUE              _U_(0x00)                                     /**<  (PAC_NONSECA) Peripheral non-secure status - Bridge A  Reset Value */

#define PAC_NONSECA_PAC_Pos                 0                                              /**< (PAC_NONSECA) PAC Non-Secure Position */
#define PAC_NONSECA_PAC_Msk                 (_U_(0x1) << PAC_NONSECA_PAC_Pos)              /**< (PAC_NONSECA) PAC Non-Secure Mask */
#define PAC_NONSECA_PAC                     PAC_NONSECA_PAC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_PAC_Msk instead */
#define PAC_NONSECA_PM_Pos                  1                                              /**< (PAC_NONSECA) PM Non-Secure Position */
#define PAC_NONSECA_PM_Msk                  (_U_(0x1) << PAC_NONSECA_PM_Pos)               /**< (PAC_NONSECA) PM Non-Secure Mask */
#define PAC_NONSECA_PM                      PAC_NONSECA_PM_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_PM_Msk instead */
#define PAC_NONSECA_MCLK_Pos                2                                              /**< (PAC_NONSECA) MCLK Non-Secure Position */
#define PAC_NONSECA_MCLK_Msk                (_U_(0x1) << PAC_NONSECA_MCLK_Pos)             /**< (PAC_NONSECA) MCLK Non-Secure Mask */
#define PAC_NONSECA_MCLK                    PAC_NONSECA_MCLK_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_MCLK_Msk instead */
#define PAC_NONSECA_RSTC_Pos                3                                              /**< (PAC_NONSECA) RSTC Non-Secure Position */
#define PAC_NONSECA_RSTC_Msk                (_U_(0x1) << PAC_NONSECA_RSTC_Pos)             /**< (PAC_NONSECA) RSTC Non-Secure Mask */
#define PAC_NONSECA_RSTC                    PAC_NONSECA_RSTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_RSTC_Msk instead */
#define PAC_NONSECA_OSCCTRL_Pos             4                                              /**< (PAC_NONSECA) OSCCTRL Non-Secure Position */
#define PAC_NONSECA_OSCCTRL_Msk             (_U_(0x1) << PAC_NONSECA_OSCCTRL_Pos)          /**< (PAC_NONSECA) OSCCTRL Non-Secure Mask */
#define PAC_NONSECA_OSCCTRL                 PAC_NONSECA_OSCCTRL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_OSCCTRL_Msk instead */
#define PAC_NONSECA_OSC32KCTRL_Pos          5                                              /**< (PAC_NONSECA) OSC32KCTRL Non-Secure Position */
#define PAC_NONSECA_OSC32KCTRL_Msk          (_U_(0x1) << PAC_NONSECA_OSC32KCTRL_Pos)       /**< (PAC_NONSECA) OSC32KCTRL Non-Secure Mask */
#define PAC_NONSECA_OSC32KCTRL              PAC_NONSECA_OSC32KCTRL_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_OSC32KCTRL_Msk instead */
#define PAC_NONSECA_SUPC_Pos                6                                              /**< (PAC_NONSECA) SUPC Non-Secure Position */
#define PAC_NONSECA_SUPC_Msk                (_U_(0x1) << PAC_NONSECA_SUPC_Pos)             /**< (PAC_NONSECA) SUPC Non-Secure Mask */
#define PAC_NONSECA_SUPC                    PAC_NONSECA_SUPC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_SUPC_Msk instead */
#define PAC_NONSECA_GCLK_Pos                7                                              /**< (PAC_NONSECA) GCLK Non-Secure Position */
#define PAC_NONSECA_GCLK_Msk                (_U_(0x1) << PAC_NONSECA_GCLK_Pos)             /**< (PAC_NONSECA) GCLK Non-Secure Mask */
#define PAC_NONSECA_GCLK                    PAC_NONSECA_GCLK_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_GCLK_Msk instead */
#define PAC_NONSECA_WDT_Pos                 8                                              /**< (PAC_NONSECA) WDT Non-Secure Position */
#define PAC_NONSECA_WDT_Msk                 (_U_(0x1) << PAC_NONSECA_WDT_Pos)              /**< (PAC_NONSECA) WDT Non-Secure Mask */
#define PAC_NONSECA_WDT                     PAC_NONSECA_WDT_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_WDT_Msk instead */
#define PAC_NONSECA_RTC_Pos                 9                                              /**< (PAC_NONSECA) RTC Non-Secure Position */
#define PAC_NONSECA_RTC_Msk                 (_U_(0x1) << PAC_NONSECA_RTC_Pos)              /**< (PAC_NONSECA) RTC Non-Secure Mask */
#define PAC_NONSECA_RTC                     PAC_NONSECA_RTC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_RTC_Msk instead */
#define PAC_NONSECA_EIC_Pos                 10                                             /**< (PAC_NONSECA) EIC Non-Secure Position */
#define PAC_NONSECA_EIC_Msk                 (_U_(0x1) << PAC_NONSECA_EIC_Pos)              /**< (PAC_NONSECA) EIC Non-Secure Mask */
#define PAC_NONSECA_EIC                     PAC_NONSECA_EIC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_EIC_Msk instead */
#define PAC_NONSECA_FREQM_Pos               11                                             /**< (PAC_NONSECA) FREQM Non-Secure Position */
#define PAC_NONSECA_FREQM_Msk               (_U_(0x1) << PAC_NONSECA_FREQM_Pos)            /**< (PAC_NONSECA) FREQM Non-Secure Mask */
#define PAC_NONSECA_FREQM                   PAC_NONSECA_FREQM_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_FREQM_Msk instead */
#define PAC_NONSECA_PORT_Pos                12                                             /**< (PAC_NONSECA) PORT Non-Secure Position */
#define PAC_NONSECA_PORT_Msk                (_U_(0x1) << PAC_NONSECA_PORT_Pos)             /**< (PAC_NONSECA) PORT Non-Secure Mask */
#define PAC_NONSECA_PORT                    PAC_NONSECA_PORT_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_PORT_Msk instead */
#define PAC_NONSECA_AC_Pos                  13                                             /**< (PAC_NONSECA) AC Non-Secure Position */
#define PAC_NONSECA_AC_Msk                  (_U_(0x1) << PAC_NONSECA_AC_Pos)               /**< (PAC_NONSECA) AC Non-Secure Mask */
#define PAC_NONSECA_AC                      PAC_NONSECA_AC_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECA_AC_Msk instead */
#define PAC_NONSECA_MASK                    _U_(0x3FFF)                                    /**< \deprecated (PAC_NONSECA) Register MASK  (Use PAC_NONSECA_Msk instead)  */
#define PAC_NONSECA_Msk                     _U_(0x3FFF)                                    /**< (PAC_NONSECA) Register Mask  */


/* -------- PAC_NONSECB : (PAC Offset: 0x58) (R/ 32) Peripheral non-secure status - Bridge B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IDAU_:1;                   /**< bit:      0  IDAU Non-Secure                          */
    uint32_t DSU_:1;                    /**< bit:      1  DSU Non-Secure                           */
    uint32_t NVMCTRL_:1;                /**< bit:      2  NVMCTRL Non-Secure                       */
    uint32_t DMAC_:1;                   /**< bit:      3  DMAC Non-Secure                          */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_NONSECB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_NONSECB_OFFSET                  (0x58)                                        /**<  (PAC_NONSECB) Peripheral non-secure status - Bridge B  Offset */
#define PAC_NONSECB_RESETVALUE              _U_(0x02)                                     /**<  (PAC_NONSECB) Peripheral non-secure status - Bridge B  Reset Value */

#define PAC_NONSECB_IDAU_Pos                0                                              /**< (PAC_NONSECB) IDAU Non-Secure Position */
#define PAC_NONSECB_IDAU_Msk                (_U_(0x1) << PAC_NONSECB_IDAU_Pos)             /**< (PAC_NONSECB) IDAU Non-Secure Mask */
#define PAC_NONSECB_IDAU                    PAC_NONSECB_IDAU_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECB_IDAU_Msk instead */
#define PAC_NONSECB_DSU_Pos                 1                                              /**< (PAC_NONSECB) DSU Non-Secure Position */
#define PAC_NONSECB_DSU_Msk                 (_U_(0x1) << PAC_NONSECB_DSU_Pos)              /**< (PAC_NONSECB) DSU Non-Secure Mask */
#define PAC_NONSECB_DSU                     PAC_NONSECB_DSU_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECB_DSU_Msk instead */
#define PAC_NONSECB_NVMCTRL_Pos             2                                              /**< (PAC_NONSECB) NVMCTRL Non-Secure Position */
#define PAC_NONSECB_NVMCTRL_Msk             (_U_(0x1) << PAC_NONSECB_NVMCTRL_Pos)          /**< (PAC_NONSECB) NVMCTRL Non-Secure Mask */
#define PAC_NONSECB_NVMCTRL                 PAC_NONSECB_NVMCTRL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECB_NVMCTRL_Msk instead */
#define PAC_NONSECB_DMAC_Pos                3                                              /**< (PAC_NONSECB) DMAC Non-Secure Position */
#define PAC_NONSECB_DMAC_Msk                (_U_(0x1) << PAC_NONSECB_DMAC_Pos)             /**< (PAC_NONSECB) DMAC Non-Secure Mask */
#define PAC_NONSECB_DMAC                    PAC_NONSECB_DMAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECB_DMAC_Msk instead */
#define PAC_NONSECB_MASK                    _U_(0x0F)                                      /**< \deprecated (PAC_NONSECB) Register MASK  (Use PAC_NONSECB_Msk instead)  */
#define PAC_NONSECB_Msk                     _U_(0x0F)                                      /**< (PAC_NONSECB) Register Mask  */


/* -------- PAC_NONSECC : (PAC Offset: 0x5c) (R/ 32) Peripheral non-secure status - Bridge C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVSYS_:1;                  /**< bit:      0  EVSYS Non-Secure                         */
    uint32_t SERCOM0_:1;                /**< bit:      1  SERCOM0 Non-Secure                       */
    uint32_t SERCOM1_:1;                /**< bit:      2  SERCOM1 Non-Secure                       */
    uint32_t SERCOM2_:1;                /**< bit:      3  SERCOM2 Non-Secure                       */
    uint32_t TC0_:1;                    /**< bit:      4  TC0 Non-Secure                           */
    uint32_t TC1_:1;                    /**< bit:      5  TC1 Non-Secure                           */
    uint32_t TC2_:1;                    /**< bit:      6  TC2 Non-Secure                           */
    uint32_t ADC_:1;                    /**< bit:      7  ADC Non-Secure                           */
    uint32_t DAC_:1;                    /**< bit:      8  DAC Non-Secure                           */
    uint32_t PTC_:1;                    /**< bit:      9  PTC Non-Secure                           */
    uint32_t TRNG_:1;                   /**< bit:     10  TRNG Non-Secure                          */
    uint32_t CCL_:1;                    /**< bit:     11  CCL Non-Secure                           */
    uint32_t OPAMP_:1;                  /**< bit:     12  OPAMP Non-Secure                         */
    uint32_t TRAM_:1;                   /**< bit:     13  TRAM Non-Secure                          */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_NONSECC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_NONSECC_OFFSET                  (0x5C)                                        /**<  (PAC_NONSECC) Peripheral non-secure status - Bridge C  Offset */
#define PAC_NONSECC_RESETVALUE              _U_(0x00)                                     /**<  (PAC_NONSECC) Peripheral non-secure status - Bridge C  Reset Value */

#define PAC_NONSECC_EVSYS_Pos               0                                              /**< (PAC_NONSECC) EVSYS Non-Secure Position */
#define PAC_NONSECC_EVSYS_Msk               (_U_(0x1) << PAC_NONSECC_EVSYS_Pos)            /**< (PAC_NONSECC) EVSYS Non-Secure Mask */
#define PAC_NONSECC_EVSYS                   PAC_NONSECC_EVSYS_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_EVSYS_Msk instead */
#define PAC_NONSECC_SERCOM0_Pos             1                                              /**< (PAC_NONSECC) SERCOM0 Non-Secure Position */
#define PAC_NONSECC_SERCOM0_Msk             (_U_(0x1) << PAC_NONSECC_SERCOM0_Pos)          /**< (PAC_NONSECC) SERCOM0 Non-Secure Mask */
#define PAC_NONSECC_SERCOM0                 PAC_NONSECC_SERCOM0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_SERCOM0_Msk instead */
#define PAC_NONSECC_SERCOM1_Pos             2                                              /**< (PAC_NONSECC) SERCOM1 Non-Secure Position */
#define PAC_NONSECC_SERCOM1_Msk             (_U_(0x1) << PAC_NONSECC_SERCOM1_Pos)          /**< (PAC_NONSECC) SERCOM1 Non-Secure Mask */
#define PAC_NONSECC_SERCOM1                 PAC_NONSECC_SERCOM1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_SERCOM1_Msk instead */
#define PAC_NONSECC_SERCOM2_Pos             3                                              /**< (PAC_NONSECC) SERCOM2 Non-Secure Position */
#define PAC_NONSECC_SERCOM2_Msk             (_U_(0x1) << PAC_NONSECC_SERCOM2_Pos)          /**< (PAC_NONSECC) SERCOM2 Non-Secure Mask */
#define PAC_NONSECC_SERCOM2                 PAC_NONSECC_SERCOM2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_SERCOM2_Msk instead */
#define PAC_NONSECC_TC0_Pos                 4                                              /**< (PAC_NONSECC) TC0 Non-Secure Position */
#define PAC_NONSECC_TC0_Msk                 (_U_(0x1) << PAC_NONSECC_TC0_Pos)              /**< (PAC_NONSECC) TC0 Non-Secure Mask */
#define PAC_NONSECC_TC0                     PAC_NONSECC_TC0_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_TC0_Msk instead */
#define PAC_NONSECC_TC1_Pos                 5                                              /**< (PAC_NONSECC) TC1 Non-Secure Position */
#define PAC_NONSECC_TC1_Msk                 (_U_(0x1) << PAC_NONSECC_TC1_Pos)              /**< (PAC_NONSECC) TC1 Non-Secure Mask */
#define PAC_NONSECC_TC1                     PAC_NONSECC_TC1_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_TC1_Msk instead */
#define PAC_NONSECC_TC2_Pos                 6                                              /**< (PAC_NONSECC) TC2 Non-Secure Position */
#define PAC_NONSECC_TC2_Msk                 (_U_(0x1) << PAC_NONSECC_TC2_Pos)              /**< (PAC_NONSECC) TC2 Non-Secure Mask */
#define PAC_NONSECC_TC2                     PAC_NONSECC_TC2_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_TC2_Msk instead */
#define PAC_NONSECC_ADC_Pos                 7                                              /**< (PAC_NONSECC) ADC Non-Secure Position */
#define PAC_NONSECC_ADC_Msk                 (_U_(0x1) << PAC_NONSECC_ADC_Pos)              /**< (PAC_NONSECC) ADC Non-Secure Mask */
#define PAC_NONSECC_ADC                     PAC_NONSECC_ADC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_ADC_Msk instead */
#define PAC_NONSECC_DAC_Pos                 8                                              /**< (PAC_NONSECC) DAC Non-Secure Position */
#define PAC_NONSECC_DAC_Msk                 (_U_(0x1) << PAC_NONSECC_DAC_Pos)              /**< (PAC_NONSECC) DAC Non-Secure Mask */
#define PAC_NONSECC_DAC                     PAC_NONSECC_DAC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_DAC_Msk instead */
#define PAC_NONSECC_PTC_Pos                 9                                              /**< (PAC_NONSECC) PTC Non-Secure Position */
#define PAC_NONSECC_PTC_Msk                 (_U_(0x1) << PAC_NONSECC_PTC_Pos)              /**< (PAC_NONSECC) PTC Non-Secure Mask */
#define PAC_NONSECC_PTC                     PAC_NONSECC_PTC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_PTC_Msk instead */
#define PAC_NONSECC_TRNG_Pos                10                                             /**< (PAC_NONSECC) TRNG Non-Secure Position */
#define PAC_NONSECC_TRNG_Msk                (_U_(0x1) << PAC_NONSECC_TRNG_Pos)             /**< (PAC_NONSECC) TRNG Non-Secure Mask */
#define PAC_NONSECC_TRNG                    PAC_NONSECC_TRNG_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_TRNG_Msk instead */
#define PAC_NONSECC_CCL_Pos                 11                                             /**< (PAC_NONSECC) CCL Non-Secure Position */
#define PAC_NONSECC_CCL_Msk                 (_U_(0x1) << PAC_NONSECC_CCL_Pos)              /**< (PAC_NONSECC) CCL Non-Secure Mask */
#define PAC_NONSECC_CCL                     PAC_NONSECC_CCL_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_CCL_Msk instead */
#define PAC_NONSECC_OPAMP_Pos               12                                             /**< (PAC_NONSECC) OPAMP Non-Secure Position */
#define PAC_NONSECC_OPAMP_Msk               (_U_(0x1) << PAC_NONSECC_OPAMP_Pos)            /**< (PAC_NONSECC) OPAMP Non-Secure Mask */
#define PAC_NONSECC_OPAMP                   PAC_NONSECC_OPAMP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_OPAMP_Msk instead */
#define PAC_NONSECC_TRAM_Pos                13                                             /**< (PAC_NONSECC) TRAM Non-Secure Position */
#define PAC_NONSECC_TRAM_Msk                (_U_(0x1) << PAC_NONSECC_TRAM_Pos)             /**< (PAC_NONSECC) TRAM Non-Secure Mask */
#define PAC_NONSECC_TRAM                    PAC_NONSECC_TRAM_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_NONSECC_TRAM_Msk instead */
#define PAC_NONSECC_MASK                    _U_(0x3FFF)                                    /**< \deprecated (PAC_NONSECC) Register MASK  (Use PAC_NONSECC_Msk instead)  */
#define PAC_NONSECC_Msk                     _U_(0x3FFF)                                    /**< (PAC_NONSECC) Register Mask  */

#define PAC_NONSECC_SERCOM_Pos              1                                              /**< (PAC_NONSECC Position) SERCOMx Non-Secure */
#define PAC_NONSECC_SERCOM_Msk              (_U_(0x7) << PAC_NONSECC_SERCOM_Pos)           /**< (PAC_NONSECC Mask) SERCOM */
#define PAC_NONSECC_SERCOM(value)           (PAC_NONSECC_SERCOM_Msk & ((value) << PAC_NONSECC_SERCOM_Pos))  
#define PAC_NONSECC_TC_Pos                  4                                              /**< (PAC_NONSECC Position) TCx Non-Secure */
#define PAC_NONSECC_TC_Msk                  (_U_(0x7) << PAC_NONSECC_TC_Pos)               /**< (PAC_NONSECC Mask) TC */
#define PAC_NONSECC_TC(value)               (PAC_NONSECC_TC_Msk & ((value) << PAC_NONSECC_TC_Pos))  

/* -------- PAC_SECLOCKA : (PAC Offset: 0x74) (R/ 32) Peripheral secure status locked - Bridge A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PAC_:1;                    /**< bit:      0  PAC Secure Status Locked                 */
    uint32_t PM_:1;                     /**< bit:      1  PM Secure Status Locked                  */
    uint32_t MCLK_:1;                   /**< bit:      2  MCLK Secure Status Locked                */
    uint32_t RSTC_:1;                   /**< bit:      3  RSTC Secure Status Locked                */
    uint32_t OSCCTRL_:1;                /**< bit:      4  OSCCTRL Secure Status Locked             */
    uint32_t OSC32KCTRL_:1;             /**< bit:      5  OSC32KCTRL Secure Status Locked          */
    uint32_t SUPC_:1;                   /**< bit:      6  SUPC Secure Status Locked                */
    uint32_t GCLK_:1;                   /**< bit:      7  GCLK Secure Status Locked                */
    uint32_t WDT_:1;                    /**< bit:      8  WDT Secure Status Locked                 */
    uint32_t RTC_:1;                    /**< bit:      9  RTC Secure Status Locked                 */
    uint32_t EIC_:1;                    /**< bit:     10  EIC Secure Status Locked                 */
    uint32_t FREQM_:1;                  /**< bit:     11  FREQM Secure Status Locked               */
    uint32_t PORT_:1;                   /**< bit:     12  PORT Secure Status Locked                */
    uint32_t AC_:1;                     /**< bit:     13  AC Secure Status Locked                  */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_SECLOCKA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_SECLOCKA_OFFSET                 (0x74)                                        /**<  (PAC_SECLOCKA) Peripheral secure status locked - Bridge A  Offset */
#define PAC_SECLOCKA_RESETVALUE             _U_(0x00)                                     /**<  (PAC_SECLOCKA) Peripheral secure status locked - Bridge A  Reset Value */

#define PAC_SECLOCKA_PAC_Pos                0                                              /**< (PAC_SECLOCKA) PAC Secure Status Locked Position */
#define PAC_SECLOCKA_PAC_Msk                (_U_(0x1) << PAC_SECLOCKA_PAC_Pos)             /**< (PAC_SECLOCKA) PAC Secure Status Locked Mask */
#define PAC_SECLOCKA_PAC                    PAC_SECLOCKA_PAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_PAC_Msk instead */
#define PAC_SECLOCKA_PM_Pos                 1                                              /**< (PAC_SECLOCKA) PM Secure Status Locked Position */
#define PAC_SECLOCKA_PM_Msk                 (_U_(0x1) << PAC_SECLOCKA_PM_Pos)              /**< (PAC_SECLOCKA) PM Secure Status Locked Mask */
#define PAC_SECLOCKA_PM                     PAC_SECLOCKA_PM_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_PM_Msk instead */
#define PAC_SECLOCKA_MCLK_Pos               2                                              /**< (PAC_SECLOCKA) MCLK Secure Status Locked Position */
#define PAC_SECLOCKA_MCLK_Msk               (_U_(0x1) << PAC_SECLOCKA_MCLK_Pos)            /**< (PAC_SECLOCKA) MCLK Secure Status Locked Mask */
#define PAC_SECLOCKA_MCLK                   PAC_SECLOCKA_MCLK_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_MCLK_Msk instead */
#define PAC_SECLOCKA_RSTC_Pos               3                                              /**< (PAC_SECLOCKA) RSTC Secure Status Locked Position */
#define PAC_SECLOCKA_RSTC_Msk               (_U_(0x1) << PAC_SECLOCKA_RSTC_Pos)            /**< (PAC_SECLOCKA) RSTC Secure Status Locked Mask */
#define PAC_SECLOCKA_RSTC                   PAC_SECLOCKA_RSTC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_RSTC_Msk instead */
#define PAC_SECLOCKA_OSCCTRL_Pos            4                                              /**< (PAC_SECLOCKA) OSCCTRL Secure Status Locked Position */
#define PAC_SECLOCKA_OSCCTRL_Msk            (_U_(0x1) << PAC_SECLOCKA_OSCCTRL_Pos)         /**< (PAC_SECLOCKA) OSCCTRL Secure Status Locked Mask */
#define PAC_SECLOCKA_OSCCTRL                PAC_SECLOCKA_OSCCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_OSCCTRL_Msk instead */
#define PAC_SECLOCKA_OSC32KCTRL_Pos         5                                              /**< (PAC_SECLOCKA) OSC32KCTRL Secure Status Locked Position */
#define PAC_SECLOCKA_OSC32KCTRL_Msk         (_U_(0x1) << PAC_SECLOCKA_OSC32KCTRL_Pos)      /**< (PAC_SECLOCKA) OSC32KCTRL Secure Status Locked Mask */
#define PAC_SECLOCKA_OSC32KCTRL             PAC_SECLOCKA_OSC32KCTRL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_OSC32KCTRL_Msk instead */
#define PAC_SECLOCKA_SUPC_Pos               6                                              /**< (PAC_SECLOCKA) SUPC Secure Status Locked Position */
#define PAC_SECLOCKA_SUPC_Msk               (_U_(0x1) << PAC_SECLOCKA_SUPC_Pos)            /**< (PAC_SECLOCKA) SUPC Secure Status Locked Mask */
#define PAC_SECLOCKA_SUPC                   PAC_SECLOCKA_SUPC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_SUPC_Msk instead */
#define PAC_SECLOCKA_GCLK_Pos               7                                              /**< (PAC_SECLOCKA) GCLK Secure Status Locked Position */
#define PAC_SECLOCKA_GCLK_Msk               (_U_(0x1) << PAC_SECLOCKA_GCLK_Pos)            /**< (PAC_SECLOCKA) GCLK Secure Status Locked Mask */
#define PAC_SECLOCKA_GCLK                   PAC_SECLOCKA_GCLK_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_GCLK_Msk instead */
#define PAC_SECLOCKA_WDT_Pos                8                                              /**< (PAC_SECLOCKA) WDT Secure Status Locked Position */
#define PAC_SECLOCKA_WDT_Msk                (_U_(0x1) << PAC_SECLOCKA_WDT_Pos)             /**< (PAC_SECLOCKA) WDT Secure Status Locked Mask */
#define PAC_SECLOCKA_WDT                    PAC_SECLOCKA_WDT_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_WDT_Msk instead */
#define PAC_SECLOCKA_RTC_Pos                9                                              /**< (PAC_SECLOCKA) RTC Secure Status Locked Position */
#define PAC_SECLOCKA_RTC_Msk                (_U_(0x1) << PAC_SECLOCKA_RTC_Pos)             /**< (PAC_SECLOCKA) RTC Secure Status Locked Mask */
#define PAC_SECLOCKA_RTC                    PAC_SECLOCKA_RTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_RTC_Msk instead */
#define PAC_SECLOCKA_EIC_Pos                10                                             /**< (PAC_SECLOCKA) EIC Secure Status Locked Position */
#define PAC_SECLOCKA_EIC_Msk                (_U_(0x1) << PAC_SECLOCKA_EIC_Pos)             /**< (PAC_SECLOCKA) EIC Secure Status Locked Mask */
#define PAC_SECLOCKA_EIC                    PAC_SECLOCKA_EIC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_EIC_Msk instead */
#define PAC_SECLOCKA_FREQM_Pos              11                                             /**< (PAC_SECLOCKA) FREQM Secure Status Locked Position */
#define PAC_SECLOCKA_FREQM_Msk              (_U_(0x1) << PAC_SECLOCKA_FREQM_Pos)           /**< (PAC_SECLOCKA) FREQM Secure Status Locked Mask */
#define PAC_SECLOCKA_FREQM                  PAC_SECLOCKA_FREQM_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_FREQM_Msk instead */
#define PAC_SECLOCKA_PORT_Pos               12                                             /**< (PAC_SECLOCKA) PORT Secure Status Locked Position */
#define PAC_SECLOCKA_PORT_Msk               (_U_(0x1) << PAC_SECLOCKA_PORT_Pos)            /**< (PAC_SECLOCKA) PORT Secure Status Locked Mask */
#define PAC_SECLOCKA_PORT                   PAC_SECLOCKA_PORT_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_PORT_Msk instead */
#define PAC_SECLOCKA_AC_Pos                 13                                             /**< (PAC_SECLOCKA) AC Secure Status Locked Position */
#define PAC_SECLOCKA_AC_Msk                 (_U_(0x1) << PAC_SECLOCKA_AC_Pos)              /**< (PAC_SECLOCKA) AC Secure Status Locked Mask */
#define PAC_SECLOCKA_AC                     PAC_SECLOCKA_AC_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKA_AC_Msk instead */
#define PAC_SECLOCKA_MASK                   _U_(0x3FFF)                                    /**< \deprecated (PAC_SECLOCKA) Register MASK  (Use PAC_SECLOCKA_Msk instead)  */
#define PAC_SECLOCKA_Msk                    _U_(0x3FFF)                                    /**< (PAC_SECLOCKA) Register Mask  */


/* -------- PAC_SECLOCKB : (PAC Offset: 0x78) (R/ 32) Peripheral secure status locked - Bridge B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IDAU_:1;                   /**< bit:      0  IDAU Secure Status Locked                */
    uint32_t DSU_:1;                    /**< bit:      1  DSU Secure Status Locked                 */
    uint32_t NVMCTRL_:1;                /**< bit:      2  NVMCTRL Secure Status Locked             */
    uint32_t DMAC_:1;                   /**< bit:      3  DMAC Secure Status Locked                */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_SECLOCKB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_SECLOCKB_OFFSET                 (0x78)                                        /**<  (PAC_SECLOCKB) Peripheral secure status locked - Bridge B  Offset */
#define PAC_SECLOCKB_RESETVALUE             _U_(0x03)                                     /**<  (PAC_SECLOCKB) Peripheral secure status locked - Bridge B  Reset Value */

#define PAC_SECLOCKB_IDAU_Pos               0                                              /**< (PAC_SECLOCKB) IDAU Secure Status Locked Position */
#define PAC_SECLOCKB_IDAU_Msk               (_U_(0x1) << PAC_SECLOCKB_IDAU_Pos)            /**< (PAC_SECLOCKB) IDAU Secure Status Locked Mask */
#define PAC_SECLOCKB_IDAU                   PAC_SECLOCKB_IDAU_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKB_IDAU_Msk instead */
#define PAC_SECLOCKB_DSU_Pos                1                                              /**< (PAC_SECLOCKB) DSU Secure Status Locked Position */
#define PAC_SECLOCKB_DSU_Msk                (_U_(0x1) << PAC_SECLOCKB_DSU_Pos)             /**< (PAC_SECLOCKB) DSU Secure Status Locked Mask */
#define PAC_SECLOCKB_DSU                    PAC_SECLOCKB_DSU_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKB_DSU_Msk instead */
#define PAC_SECLOCKB_NVMCTRL_Pos            2                                              /**< (PAC_SECLOCKB) NVMCTRL Secure Status Locked Position */
#define PAC_SECLOCKB_NVMCTRL_Msk            (_U_(0x1) << PAC_SECLOCKB_NVMCTRL_Pos)         /**< (PAC_SECLOCKB) NVMCTRL Secure Status Locked Mask */
#define PAC_SECLOCKB_NVMCTRL                PAC_SECLOCKB_NVMCTRL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKB_NVMCTRL_Msk instead */
#define PAC_SECLOCKB_DMAC_Pos               3                                              /**< (PAC_SECLOCKB) DMAC Secure Status Locked Position */
#define PAC_SECLOCKB_DMAC_Msk               (_U_(0x1) << PAC_SECLOCKB_DMAC_Pos)            /**< (PAC_SECLOCKB) DMAC Secure Status Locked Mask */
#define PAC_SECLOCKB_DMAC                   PAC_SECLOCKB_DMAC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKB_DMAC_Msk instead */
#define PAC_SECLOCKB_MASK                   _U_(0x0F)                                      /**< \deprecated (PAC_SECLOCKB) Register MASK  (Use PAC_SECLOCKB_Msk instead)  */
#define PAC_SECLOCKB_Msk                    _U_(0x0F)                                      /**< (PAC_SECLOCKB) Register Mask  */


/* -------- PAC_SECLOCKC : (PAC Offset: 0x7c) (R/ 32) Peripheral secure status locked - Bridge C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVSYS_:1;                  /**< bit:      0  EVSYS Secure Status Locked               */
    uint32_t SERCOM0_:1;                /**< bit:      1  SERCOM0 Secure Status Locked             */
    uint32_t SERCOM1_:1;                /**< bit:      2  SERCOM1 Secure Status Locked             */
    uint32_t SERCOM2_:1;                /**< bit:      3  SERCOM2 Secure Status Locked             */
    uint32_t TC0_:1;                    /**< bit:      4  TC0 Secure Status Locked                 */
    uint32_t TC1_:1;                    /**< bit:      5  TC1 Secure Status Locked                 */
    uint32_t TC2_:1;                    /**< bit:      6  TC2 Secure Status Locked                 */
    uint32_t ADC_:1;                    /**< bit:      7  ADC Secure Status Locked                 */
    uint32_t DAC_:1;                    /**< bit:      8  DAC Secure Status Locked                 */
    uint32_t PTC_:1;                    /**< bit:      9  PTC Secure Status Locked                 */
    uint32_t TRNG_:1;                   /**< bit:     10  TRNG Secure Status Locked                */
    uint32_t CCL_:1;                    /**< bit:     11  CCL Secure Status Locked                 */
    uint32_t OPAMP_:1;                  /**< bit:     12  OPAMP Secure Status Locked               */
    uint32_t TRAM_:1;                   /**< bit:     13  TRAM Secure Status Locked                */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PAC_SECLOCKC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_SECLOCKC_OFFSET                 (0x7C)                                        /**<  (PAC_SECLOCKC) Peripheral secure status locked - Bridge C  Offset */
#define PAC_SECLOCKC_RESETVALUE             _U_(0x00)                                     /**<  (PAC_SECLOCKC) Peripheral secure status locked - Bridge C  Reset Value */

#define PAC_SECLOCKC_EVSYS_Pos              0                                              /**< (PAC_SECLOCKC) EVSYS Secure Status Locked Position */
#define PAC_SECLOCKC_EVSYS_Msk              (_U_(0x1) << PAC_SECLOCKC_EVSYS_Pos)           /**< (PAC_SECLOCKC) EVSYS Secure Status Locked Mask */
#define PAC_SECLOCKC_EVSYS                  PAC_SECLOCKC_EVSYS_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_EVSYS_Msk instead */
#define PAC_SECLOCKC_SERCOM0_Pos            1                                              /**< (PAC_SECLOCKC) SERCOM0 Secure Status Locked Position */
#define PAC_SECLOCKC_SERCOM0_Msk            (_U_(0x1) << PAC_SECLOCKC_SERCOM0_Pos)         /**< (PAC_SECLOCKC) SERCOM0 Secure Status Locked Mask */
#define PAC_SECLOCKC_SERCOM0                PAC_SECLOCKC_SERCOM0_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_SERCOM0_Msk instead */
#define PAC_SECLOCKC_SERCOM1_Pos            2                                              /**< (PAC_SECLOCKC) SERCOM1 Secure Status Locked Position */
#define PAC_SECLOCKC_SERCOM1_Msk            (_U_(0x1) << PAC_SECLOCKC_SERCOM1_Pos)         /**< (PAC_SECLOCKC) SERCOM1 Secure Status Locked Mask */
#define PAC_SECLOCKC_SERCOM1                PAC_SECLOCKC_SERCOM1_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_SERCOM1_Msk instead */
#define PAC_SECLOCKC_SERCOM2_Pos            3                                              /**< (PAC_SECLOCKC) SERCOM2 Secure Status Locked Position */
#define PAC_SECLOCKC_SERCOM2_Msk            (_U_(0x1) << PAC_SECLOCKC_SERCOM2_Pos)         /**< (PAC_SECLOCKC) SERCOM2 Secure Status Locked Mask */
#define PAC_SECLOCKC_SERCOM2                PAC_SECLOCKC_SERCOM2_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_SERCOM2_Msk instead */
#define PAC_SECLOCKC_TC0_Pos                4                                              /**< (PAC_SECLOCKC) TC0 Secure Status Locked Position */
#define PAC_SECLOCKC_TC0_Msk                (_U_(0x1) << PAC_SECLOCKC_TC0_Pos)             /**< (PAC_SECLOCKC) TC0 Secure Status Locked Mask */
#define PAC_SECLOCKC_TC0                    PAC_SECLOCKC_TC0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_TC0_Msk instead */
#define PAC_SECLOCKC_TC1_Pos                5                                              /**< (PAC_SECLOCKC) TC1 Secure Status Locked Position */
#define PAC_SECLOCKC_TC1_Msk                (_U_(0x1) << PAC_SECLOCKC_TC1_Pos)             /**< (PAC_SECLOCKC) TC1 Secure Status Locked Mask */
#define PAC_SECLOCKC_TC1                    PAC_SECLOCKC_TC1_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_TC1_Msk instead */
#define PAC_SECLOCKC_TC2_Pos                6                                              /**< (PAC_SECLOCKC) TC2 Secure Status Locked Position */
#define PAC_SECLOCKC_TC2_Msk                (_U_(0x1) << PAC_SECLOCKC_TC2_Pos)             /**< (PAC_SECLOCKC) TC2 Secure Status Locked Mask */
#define PAC_SECLOCKC_TC2                    PAC_SECLOCKC_TC2_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_TC2_Msk instead */
#define PAC_SECLOCKC_ADC_Pos                7                                              /**< (PAC_SECLOCKC) ADC Secure Status Locked Position */
#define PAC_SECLOCKC_ADC_Msk                (_U_(0x1) << PAC_SECLOCKC_ADC_Pos)             /**< (PAC_SECLOCKC) ADC Secure Status Locked Mask */
#define PAC_SECLOCKC_ADC                    PAC_SECLOCKC_ADC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_ADC_Msk instead */
#define PAC_SECLOCKC_DAC_Pos                8                                              /**< (PAC_SECLOCKC) DAC Secure Status Locked Position */
#define PAC_SECLOCKC_DAC_Msk                (_U_(0x1) << PAC_SECLOCKC_DAC_Pos)             /**< (PAC_SECLOCKC) DAC Secure Status Locked Mask */
#define PAC_SECLOCKC_DAC                    PAC_SECLOCKC_DAC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_DAC_Msk instead */
#define PAC_SECLOCKC_PTC_Pos                9                                              /**< (PAC_SECLOCKC) PTC Secure Status Locked Position */
#define PAC_SECLOCKC_PTC_Msk                (_U_(0x1) << PAC_SECLOCKC_PTC_Pos)             /**< (PAC_SECLOCKC) PTC Secure Status Locked Mask */
#define PAC_SECLOCKC_PTC                    PAC_SECLOCKC_PTC_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_PTC_Msk instead */
#define PAC_SECLOCKC_TRNG_Pos               10                                             /**< (PAC_SECLOCKC) TRNG Secure Status Locked Position */
#define PAC_SECLOCKC_TRNG_Msk               (_U_(0x1) << PAC_SECLOCKC_TRNG_Pos)            /**< (PAC_SECLOCKC) TRNG Secure Status Locked Mask */
#define PAC_SECLOCKC_TRNG                   PAC_SECLOCKC_TRNG_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_TRNG_Msk instead */
#define PAC_SECLOCKC_CCL_Pos                11                                             /**< (PAC_SECLOCKC) CCL Secure Status Locked Position */
#define PAC_SECLOCKC_CCL_Msk                (_U_(0x1) << PAC_SECLOCKC_CCL_Pos)             /**< (PAC_SECLOCKC) CCL Secure Status Locked Mask */
#define PAC_SECLOCKC_CCL                    PAC_SECLOCKC_CCL_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_CCL_Msk instead */
#define PAC_SECLOCKC_OPAMP_Pos              12                                             /**< (PAC_SECLOCKC) OPAMP Secure Status Locked Position */
#define PAC_SECLOCKC_OPAMP_Msk              (_U_(0x1) << PAC_SECLOCKC_OPAMP_Pos)           /**< (PAC_SECLOCKC) OPAMP Secure Status Locked Mask */
#define PAC_SECLOCKC_OPAMP                  PAC_SECLOCKC_OPAMP_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_OPAMP_Msk instead */
#define PAC_SECLOCKC_TRAM_Pos               13                                             /**< (PAC_SECLOCKC) TRAM Secure Status Locked Position */
#define PAC_SECLOCKC_TRAM_Msk               (_U_(0x1) << PAC_SECLOCKC_TRAM_Pos)            /**< (PAC_SECLOCKC) TRAM Secure Status Locked Mask */
#define PAC_SECLOCKC_TRAM                   PAC_SECLOCKC_TRAM_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PAC_SECLOCKC_TRAM_Msk instead */
#define PAC_SECLOCKC_MASK                   _U_(0x3FFF)                                    /**< \deprecated (PAC_SECLOCKC) Register MASK  (Use PAC_SECLOCKC_Msk instead)  */
#define PAC_SECLOCKC_Msk                    _U_(0x3FFF)                                    /**< (PAC_SECLOCKC) Register Mask  */

#define PAC_SECLOCKC_SERCOM_Pos             1                                              /**< (PAC_SECLOCKC Position) SERCOMx Secure Status Locked */
#define PAC_SECLOCKC_SERCOM_Msk             (_U_(0x7) << PAC_SECLOCKC_SERCOM_Pos)          /**< (PAC_SECLOCKC Mask) SERCOM */
#define PAC_SECLOCKC_SERCOM(value)          (PAC_SECLOCKC_SERCOM_Msk & ((value) << PAC_SECLOCKC_SERCOM_Pos))  
#define PAC_SECLOCKC_TC_Pos                 4                                              /**< (PAC_SECLOCKC Position) TCx Secure Status Locked */
#define PAC_SECLOCKC_TC_Msk                 (_U_(0x7) << PAC_SECLOCKC_TC_Pos)              /**< (PAC_SECLOCKC Mask) TC */
#define PAC_SECLOCKC_TC(value)              (PAC_SECLOCKC_TC_Msk & ((value) << PAC_SECLOCKC_TC_Pos))  

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief PAC hardware registers */
typedef struct {  /* Peripheral Access Controller */
  __IO PAC_WRCTRL_Type                WRCTRL;         /**< Offset: 0x00 (R/W  32) Write control */
  __IO PAC_EVCTRL_Type                EVCTRL;         /**< Offset: 0x04 (R/W   8) Event control */
  __I  uint8_t                        Reserved1[3];
  __IO PAC_INTENCLR_Type              INTENCLR;       /**< Offset: 0x08 (R/W   8) Interrupt enable clear */
  __IO PAC_INTENSET_Type              INTENSET;       /**< Offset: 0x09 (R/W   8) Interrupt enable set */
  __I  uint8_t                        Reserved2[6];
  __IO PAC_INTFLAGAHB_Type            INTFLAGAHB;     /**< Offset: 0x10 (R/W  32) Bridge interrupt flag status */
  __IO PAC_INTFLAGA_Type              INTFLAGA;       /**< Offset: 0x14 (R/W  32) Peripheral interrupt flag status - Bridge A */
  __IO PAC_INTFLAGB_Type              INTFLAGB;       /**< Offset: 0x18 (R/W  32) Peripheral interrupt flag status - Bridge B */
  __IO PAC_INTFLAGC_Type              INTFLAGC;       /**< Offset: 0x1C (R/W  32) Peripheral interrupt flag status - Bridge C */
  __I  uint8_t                        Reserved3[20];
  __I  PAC_STATUSA_Type               STATUSA;        /**< Offset: 0x34 (R/   32) Peripheral write protection status - Bridge A */
  __I  PAC_STATUSB_Type               STATUSB;        /**< Offset: 0x38 (R/   32) Peripheral write protection status - Bridge B */
  __I  PAC_STATUSC_Type               STATUSC;        /**< Offset: 0x3C (R/   32) Peripheral write protection status - Bridge C */
  __I  uint8_t                        Reserved4[20];
  __I  PAC_NONSECA_Type               NONSECA;        /**< Offset: 0x54 (R/   32) Peripheral non-secure status - Bridge A */
  __I  PAC_NONSECB_Type               NONSECB;        /**< Offset: 0x58 (R/   32) Peripheral non-secure status - Bridge B */
  __I  PAC_NONSECC_Type               NONSECC;        /**< Offset: 0x5C (R/   32) Peripheral non-secure status - Bridge C */
  __I  uint8_t                        Reserved5[20];
  __I  PAC_SECLOCKA_Type              SECLOCKA;       /**< Offset: 0x74 (R/   32) Peripheral secure status locked - Bridge A */
  __I  PAC_SECLOCKB_Type              SECLOCKB;       /**< Offset: 0x78 (R/   32) Peripheral secure status locked - Bridge B */
  __I  PAC_SECLOCKC_Type              SECLOCKC;       /**< Offset: 0x7C (R/   32) Peripheral secure status locked - Bridge C */
} Pac;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Peripheral Access Controller */

#endif /* _SAML10_PAC_COMPONENT_H_ */
