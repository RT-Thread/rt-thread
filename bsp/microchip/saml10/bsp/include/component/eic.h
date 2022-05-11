/**
 * \file
 *
 * \brief Component description for EIC
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
#ifndef _SAML10_EIC_COMPONENT_H_
#define _SAML10_EIC_COMPONENT_H_
#define _SAML10_EIC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 External Interrupt Controller
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR EIC */
/* ========================================================================== */

#define EIC_U2804                      /**< (EIC) Module ID */
#define REV_EIC 0x100                  /**< (EIC) Module revision */

/* -------- EIC_CTRLA : (EIC Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  CKSEL:1;                   /**< bit:      4  Clock Selection                          */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EIC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_CTRLA_OFFSET                    (0x00)                                        /**<  (EIC_CTRLA) Control A  Offset */
#define EIC_CTRLA_RESETVALUE                _U_(0x00)                                     /**<  (EIC_CTRLA) Control A  Reset Value */

#define EIC_CTRLA_SWRST_Pos                 0                                              /**< (EIC_CTRLA) Software Reset Position */
#define EIC_CTRLA_SWRST_Msk                 (_U_(0x1) << EIC_CTRLA_SWRST_Pos)              /**< (EIC_CTRLA) Software Reset Mask */
#define EIC_CTRLA_SWRST                     EIC_CTRLA_SWRST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CTRLA_SWRST_Msk instead */
#define EIC_CTRLA_ENABLE_Pos                1                                              /**< (EIC_CTRLA) Enable Position */
#define EIC_CTRLA_ENABLE_Msk                (_U_(0x1) << EIC_CTRLA_ENABLE_Pos)             /**< (EIC_CTRLA) Enable Mask */
#define EIC_CTRLA_ENABLE                    EIC_CTRLA_ENABLE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CTRLA_ENABLE_Msk instead */
#define EIC_CTRLA_CKSEL_Pos                 4                                              /**< (EIC_CTRLA) Clock Selection Position */
#define EIC_CTRLA_CKSEL_Msk                 (_U_(0x1) << EIC_CTRLA_CKSEL_Pos)              /**< (EIC_CTRLA) Clock Selection Mask */
#define EIC_CTRLA_CKSEL                     EIC_CTRLA_CKSEL_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CTRLA_CKSEL_Msk instead */
#define EIC_CTRLA_MASK                      _U_(0x13)                                      /**< \deprecated (EIC_CTRLA) Register MASK  (Use EIC_CTRLA_Msk instead)  */
#define EIC_CTRLA_Msk                       _U_(0x13)                                      /**< (EIC_CTRLA) Register Mask  */


/* -------- EIC_NMICTRL : (EIC Offset: 0x01) (R/W 8) Non-Maskable Interrupt Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  NMISENSE:3;                /**< bit:   0..2  Non-Maskable Interrupt Sense Configuration */
    uint8_t  NMIFILTEN:1;               /**< bit:      3  Non-Maskable Interrupt Filter Enable     */
    uint8_t  NMIASYNCH:1;               /**< bit:      4  Asynchronous Edge Detection Mode         */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EIC_NMICTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_NMICTRL_OFFSET                  (0x01)                                        /**<  (EIC_NMICTRL) Non-Maskable Interrupt Control  Offset */
#define EIC_NMICTRL_RESETVALUE              _U_(0x00)                                     /**<  (EIC_NMICTRL) Non-Maskable Interrupt Control  Reset Value */

#define EIC_NMICTRL_NMISENSE_Pos            0                                              /**< (EIC_NMICTRL) Non-Maskable Interrupt Sense Configuration Position */
#define EIC_NMICTRL_NMISENSE_Msk            (_U_(0x7) << EIC_NMICTRL_NMISENSE_Pos)         /**< (EIC_NMICTRL) Non-Maskable Interrupt Sense Configuration Mask */
#define EIC_NMICTRL_NMISENSE(value)         (EIC_NMICTRL_NMISENSE_Msk & ((value) << EIC_NMICTRL_NMISENSE_Pos))
#define   EIC_NMICTRL_NMISENSE_NONE_Val     _U_(0x0)                                       /**< (EIC_NMICTRL) No detection  */
#define   EIC_NMICTRL_NMISENSE_RISE_Val     _U_(0x1)                                       /**< (EIC_NMICTRL) Rising-edge detection  */
#define   EIC_NMICTRL_NMISENSE_FALL_Val     _U_(0x2)                                       /**< (EIC_NMICTRL) Falling-edge detection  */
#define   EIC_NMICTRL_NMISENSE_BOTH_Val     _U_(0x3)                                       /**< (EIC_NMICTRL) Both-edges detection  */
#define   EIC_NMICTRL_NMISENSE_HIGH_Val     _U_(0x4)                                       /**< (EIC_NMICTRL) High-level detection  */
#define   EIC_NMICTRL_NMISENSE_LOW_Val      _U_(0x5)                                       /**< (EIC_NMICTRL) Low-level detection  */
#define EIC_NMICTRL_NMISENSE_NONE           (EIC_NMICTRL_NMISENSE_NONE_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) No detection Position  */
#define EIC_NMICTRL_NMISENSE_RISE           (EIC_NMICTRL_NMISENSE_RISE_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) Rising-edge detection Position  */
#define EIC_NMICTRL_NMISENSE_FALL           (EIC_NMICTRL_NMISENSE_FALL_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) Falling-edge detection Position  */
#define EIC_NMICTRL_NMISENSE_BOTH           (EIC_NMICTRL_NMISENSE_BOTH_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) Both-edges detection Position  */
#define EIC_NMICTRL_NMISENSE_HIGH           (EIC_NMICTRL_NMISENSE_HIGH_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) High-level detection Position  */
#define EIC_NMICTRL_NMISENSE_LOW            (EIC_NMICTRL_NMISENSE_LOW_Val << EIC_NMICTRL_NMISENSE_Pos)  /**< (EIC_NMICTRL) Low-level detection Position  */
#define EIC_NMICTRL_NMIFILTEN_Pos           3                                              /**< (EIC_NMICTRL) Non-Maskable Interrupt Filter Enable Position */
#define EIC_NMICTRL_NMIFILTEN_Msk           (_U_(0x1) << EIC_NMICTRL_NMIFILTEN_Pos)        /**< (EIC_NMICTRL) Non-Maskable Interrupt Filter Enable Mask */
#define EIC_NMICTRL_NMIFILTEN               EIC_NMICTRL_NMIFILTEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_NMICTRL_NMIFILTEN_Msk instead */
#define EIC_NMICTRL_NMIASYNCH_Pos           4                                              /**< (EIC_NMICTRL) Asynchronous Edge Detection Mode Position */
#define EIC_NMICTRL_NMIASYNCH_Msk           (_U_(0x1) << EIC_NMICTRL_NMIASYNCH_Pos)        /**< (EIC_NMICTRL) Asynchronous Edge Detection Mode Mask */
#define EIC_NMICTRL_NMIASYNCH               EIC_NMICTRL_NMIASYNCH_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_NMICTRL_NMIASYNCH_Msk instead */
#define EIC_NMICTRL_MASK                    _U_(0x1F)                                      /**< \deprecated (EIC_NMICTRL) Register MASK  (Use EIC_NMICTRL_Msk instead)  */
#define EIC_NMICTRL_Msk                     _U_(0x1F)                                      /**< (EIC_NMICTRL) Register Mask  */


/* -------- EIC_NMIFLAG : (EIC Offset: 0x02) (R/W 8) Non-Maskable Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  NMI:1;                     /**< bit:      0  Non-Maskable Interrupt                   */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EIC_NMIFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_NMIFLAG_OFFSET                  (0x02)                                        /**<  (EIC_NMIFLAG) Non-Maskable Interrupt Flag Status and Clear  Offset */
#define EIC_NMIFLAG_RESETVALUE              _U_(0x00)                                     /**<  (EIC_NMIFLAG) Non-Maskable Interrupt Flag Status and Clear  Reset Value */

#define EIC_NMIFLAG_NMI_Pos                 0                                              /**< (EIC_NMIFLAG) Non-Maskable Interrupt Position */
#define EIC_NMIFLAG_NMI_Msk                 (_U_(0x1) << EIC_NMIFLAG_NMI_Pos)              /**< (EIC_NMIFLAG) Non-Maskable Interrupt Mask */
#define EIC_NMIFLAG_NMI                     EIC_NMIFLAG_NMI_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_NMIFLAG_NMI_Msk instead */
#define EIC_NMIFLAG_MASK                    _U_(0x01)                                      /**< \deprecated (EIC_NMIFLAG) Register MASK  (Use EIC_NMIFLAG_Msk instead)  */
#define EIC_NMIFLAG_Msk                     _U_(0x01)                                      /**< (EIC_NMIFLAG) Register Mask  */


/* -------- EIC_SYNCBUSY : (EIC Offset: 0x04) (R/ 32) Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy Status */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Synchronization Busy Status       */
    uint32_t :30;                       /**< bit:  2..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_SYNCBUSY_OFFSET                 (0x04)                                        /**<  (EIC_SYNCBUSY) Synchronization Busy  Offset */
#define EIC_SYNCBUSY_RESETVALUE             _U_(0x00)                                     /**<  (EIC_SYNCBUSY) Synchronization Busy  Reset Value */

#define EIC_SYNCBUSY_SWRST_Pos              0                                              /**< (EIC_SYNCBUSY) Software Reset Synchronization Busy Status Position */
#define EIC_SYNCBUSY_SWRST_Msk              (_U_(0x1) << EIC_SYNCBUSY_SWRST_Pos)           /**< (EIC_SYNCBUSY) Software Reset Synchronization Busy Status Mask */
#define EIC_SYNCBUSY_SWRST                  EIC_SYNCBUSY_SWRST_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_SYNCBUSY_SWRST_Msk instead */
#define EIC_SYNCBUSY_ENABLE_Pos             1                                              /**< (EIC_SYNCBUSY) Enable Synchronization Busy Status Position */
#define EIC_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << EIC_SYNCBUSY_ENABLE_Pos)          /**< (EIC_SYNCBUSY) Enable Synchronization Busy Status Mask */
#define EIC_SYNCBUSY_ENABLE                 EIC_SYNCBUSY_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_SYNCBUSY_ENABLE_Msk instead */
#define EIC_SYNCBUSY_MASK                   _U_(0x03)                                      /**< \deprecated (EIC_SYNCBUSY) Register MASK  (Use EIC_SYNCBUSY_Msk instead)  */
#define EIC_SYNCBUSY_Msk                    _U_(0x03)                                      /**< (EIC_SYNCBUSY) Register Mask  */


/* -------- EIC_EVCTRL : (EIC Offset: 0x08) (R/W 32) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EXTINTEO:8;                /**< bit:   0..7  External Interrupt Event Output Enable   */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_EVCTRL_OFFSET                   (0x08)                                        /**<  (EIC_EVCTRL) Event Control  Offset */
#define EIC_EVCTRL_RESETVALUE               _U_(0x00)                                     /**<  (EIC_EVCTRL) Event Control  Reset Value */

#define EIC_EVCTRL_EXTINTEO_Pos             0                                              /**< (EIC_EVCTRL) External Interrupt Event Output Enable Position */
#define EIC_EVCTRL_EXTINTEO_Msk             (_U_(0xFF) << EIC_EVCTRL_EXTINTEO_Pos)         /**< (EIC_EVCTRL) External Interrupt Event Output Enable Mask */
#define EIC_EVCTRL_EXTINTEO(value)          (EIC_EVCTRL_EXTINTEO_Msk & ((value) << EIC_EVCTRL_EXTINTEO_Pos))
#define EIC_EVCTRL_MASK                     _U_(0xFF)                                      /**< \deprecated (EIC_EVCTRL) Register MASK  (Use EIC_EVCTRL_Msk instead)  */
#define EIC_EVCTRL_Msk                      _U_(0xFF)                                      /**< (EIC_EVCTRL) Register Mask  */


/* -------- EIC_INTENCLR : (EIC Offset: 0x0c) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EXTINT:8;                  /**< bit:   0..7  External Interrupt Enable                */
    uint32_t :23;                       /**< bit:  8..30  Reserved */
    uint32_t NSCHK:1;                   /**< bit:     31  Non-secure Check Interrupt Enable        */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_INTENCLR_OFFSET                 (0x0C)                                        /**<  (EIC_INTENCLR) Interrupt Enable Clear  Offset */
#define EIC_INTENCLR_RESETVALUE             _U_(0x00)                                     /**<  (EIC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define EIC_INTENCLR_EXTINT_Pos             0                                              /**< (EIC_INTENCLR) External Interrupt Enable Position */
#define EIC_INTENCLR_EXTINT_Msk             (_U_(0xFF) << EIC_INTENCLR_EXTINT_Pos)         /**< (EIC_INTENCLR) External Interrupt Enable Mask */
#define EIC_INTENCLR_EXTINT(value)          (EIC_INTENCLR_EXTINT_Msk & ((value) << EIC_INTENCLR_EXTINT_Pos))
#define EIC_INTENCLR_NSCHK_Pos              31                                             /**< (EIC_INTENCLR) Non-secure Check Interrupt Enable Position */
#define EIC_INTENCLR_NSCHK_Msk              (_U_(0x1) << EIC_INTENCLR_NSCHK_Pos)           /**< (EIC_INTENCLR) Non-secure Check Interrupt Enable Mask */
#define EIC_INTENCLR_NSCHK                  EIC_INTENCLR_NSCHK_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_INTENCLR_NSCHK_Msk instead */
#define EIC_INTENCLR_MASK                   _U_(0x800000FF)                                /**< \deprecated (EIC_INTENCLR) Register MASK  (Use EIC_INTENCLR_Msk instead)  */
#define EIC_INTENCLR_Msk                    _U_(0x800000FF)                                /**< (EIC_INTENCLR) Register Mask  */


/* -------- EIC_INTENSET : (EIC Offset: 0x10) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EXTINT:8;                  /**< bit:   0..7  External Interrupt Enable                */
    uint32_t :23;                       /**< bit:  8..30  Reserved */
    uint32_t NSCHK:1;                   /**< bit:     31  Non-secure Check Interrupt Enable        */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_INTENSET_OFFSET                 (0x10)                                        /**<  (EIC_INTENSET) Interrupt Enable Set  Offset */
#define EIC_INTENSET_RESETVALUE             _U_(0x00)                                     /**<  (EIC_INTENSET) Interrupt Enable Set  Reset Value */

#define EIC_INTENSET_EXTINT_Pos             0                                              /**< (EIC_INTENSET) External Interrupt Enable Position */
#define EIC_INTENSET_EXTINT_Msk             (_U_(0xFF) << EIC_INTENSET_EXTINT_Pos)         /**< (EIC_INTENSET) External Interrupt Enable Mask */
#define EIC_INTENSET_EXTINT(value)          (EIC_INTENSET_EXTINT_Msk & ((value) << EIC_INTENSET_EXTINT_Pos))
#define EIC_INTENSET_NSCHK_Pos              31                                             /**< (EIC_INTENSET) Non-secure Check Interrupt Enable Position */
#define EIC_INTENSET_NSCHK_Msk              (_U_(0x1) << EIC_INTENSET_NSCHK_Pos)           /**< (EIC_INTENSET) Non-secure Check Interrupt Enable Mask */
#define EIC_INTENSET_NSCHK                  EIC_INTENSET_NSCHK_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_INTENSET_NSCHK_Msk instead */
#define EIC_INTENSET_MASK                   _U_(0x800000FF)                                /**< \deprecated (EIC_INTENSET) Register MASK  (Use EIC_INTENSET_Msk instead)  */
#define EIC_INTENSET_Msk                    _U_(0x800000FF)                                /**< (EIC_INTENSET) Register Mask  */


/* -------- EIC_INTFLAG : (EIC Offset: 0x14) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t EXTINT:8;                  /**< bit:   0..7  External Interrupt                       */
    __I uint32_t :23;                       /**< bit:  8..30  Reserved */
    __I uint32_t NSCHK:1;                   /**< bit:     31  Non-secure Check Interrupt               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_INTFLAG_OFFSET                  (0x14)                                        /**<  (EIC_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define EIC_INTFLAG_RESETVALUE              _U_(0x00)                                     /**<  (EIC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define EIC_INTFLAG_EXTINT_Pos              0                                              /**< (EIC_INTFLAG) External Interrupt Position */
#define EIC_INTFLAG_EXTINT_Msk              (_U_(0xFF) << EIC_INTFLAG_EXTINT_Pos)          /**< (EIC_INTFLAG) External Interrupt Mask */
#define EIC_INTFLAG_EXTINT(value)           (EIC_INTFLAG_EXTINT_Msk & ((value) << EIC_INTFLAG_EXTINT_Pos))
#define EIC_INTFLAG_NSCHK_Pos               31                                             /**< (EIC_INTFLAG) Non-secure Check Interrupt Position */
#define EIC_INTFLAG_NSCHK_Msk               (_U_(0x1) << EIC_INTFLAG_NSCHK_Pos)            /**< (EIC_INTFLAG) Non-secure Check Interrupt Mask */
#define EIC_INTFLAG_NSCHK                   EIC_INTFLAG_NSCHK_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_INTFLAG_NSCHK_Msk instead */
#define EIC_INTFLAG_MASK                    _U_(0x800000FF)                                /**< \deprecated (EIC_INTFLAG) Register MASK  (Use EIC_INTFLAG_Msk instead)  */
#define EIC_INTFLAG_Msk                     _U_(0x800000FF)                                /**< (EIC_INTFLAG) Register Mask  */


/* -------- EIC_ASYNCH : (EIC Offset: 0x18) (R/W 32) External Interrupt Asynchronous Mode -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ASYNCH:8;                  /**< bit:   0..7  Asynchronous Edge Detection Mode         */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_ASYNCH_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_ASYNCH_OFFSET                   (0x18)                                        /**<  (EIC_ASYNCH) External Interrupt Asynchronous Mode  Offset */
#define EIC_ASYNCH_RESETVALUE               _U_(0x00)                                     /**<  (EIC_ASYNCH) External Interrupt Asynchronous Mode  Reset Value */

#define EIC_ASYNCH_ASYNCH_Pos               0                                              /**< (EIC_ASYNCH) Asynchronous Edge Detection Mode Position */
#define EIC_ASYNCH_ASYNCH_Msk               (_U_(0xFF) << EIC_ASYNCH_ASYNCH_Pos)           /**< (EIC_ASYNCH) Asynchronous Edge Detection Mode Mask */
#define EIC_ASYNCH_ASYNCH(value)            (EIC_ASYNCH_ASYNCH_Msk & ((value) << EIC_ASYNCH_ASYNCH_Pos))
#define EIC_ASYNCH_MASK                     _U_(0xFF)                                      /**< \deprecated (EIC_ASYNCH) Register MASK  (Use EIC_ASYNCH_Msk instead)  */
#define EIC_ASYNCH_Msk                      _U_(0xFF)                                      /**< (EIC_ASYNCH) Register Mask  */


/* -------- EIC_CONFIG : (EIC Offset: 0x1c) (R/W 32) External Interrupt Sense Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SENSE0:3;                  /**< bit:   0..2  Input Sense Configuration 0              */
    uint32_t FILTEN0:1;                 /**< bit:      3  Filter Enable 0                          */
    uint32_t SENSE1:3;                  /**< bit:   4..6  Input Sense Configuration 1              */
    uint32_t FILTEN1:1;                 /**< bit:      7  Filter Enable 1                          */
    uint32_t SENSE2:3;                  /**< bit:  8..10  Input Sense Configuration 2              */
    uint32_t FILTEN2:1;                 /**< bit:     11  Filter Enable 2                          */
    uint32_t SENSE3:3;                  /**< bit: 12..14  Input Sense Configuration 3              */
    uint32_t FILTEN3:1;                 /**< bit:     15  Filter Enable 3                          */
    uint32_t SENSE4:3;                  /**< bit: 16..18  Input Sense Configuration 4              */
    uint32_t FILTEN4:1;                 /**< bit:     19  Filter Enable 4                          */
    uint32_t SENSE5:3;                  /**< bit: 20..22  Input Sense Configuration 5              */
    uint32_t FILTEN5:1;                 /**< bit:     23  Filter Enable 5                          */
    uint32_t SENSE6:3;                  /**< bit: 24..26  Input Sense Configuration 6              */
    uint32_t FILTEN6:1;                 /**< bit:     27  Filter Enable 6                          */
    uint32_t SENSE7:3;                  /**< bit: 28..30  Input Sense Configuration 7              */
    uint32_t FILTEN7:1;                 /**< bit:     31  Filter Enable 7                          */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_CONFIG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_CONFIG_OFFSET                   (0x1C)                                        /**<  (EIC_CONFIG) External Interrupt Sense Configuration  Offset */
#define EIC_CONFIG_RESETVALUE               _U_(0x00)                                     /**<  (EIC_CONFIG) External Interrupt Sense Configuration  Reset Value */

#define EIC_CONFIG_SENSE0_Pos               0                                              /**< (EIC_CONFIG) Input Sense Configuration 0 Position */
#define EIC_CONFIG_SENSE0_Msk               (_U_(0x7) << EIC_CONFIG_SENSE0_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 0 Mask */
#define EIC_CONFIG_SENSE0(value)            (EIC_CONFIG_SENSE0_Msk & ((value) << EIC_CONFIG_SENSE0_Pos))
#define   EIC_CONFIG_SENSE0_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE0_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE0_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE0_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE0_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE0_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE0_NONE              (EIC_CONFIG_SENSE0_NONE_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE0_RISE              (EIC_CONFIG_SENSE0_RISE_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE0_FALL              (EIC_CONFIG_SENSE0_FALL_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE0_BOTH              (EIC_CONFIG_SENSE0_BOTH_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE0_HIGH              (EIC_CONFIG_SENSE0_HIGH_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE0_LOW               (EIC_CONFIG_SENSE0_LOW_Val << EIC_CONFIG_SENSE0_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN0_Pos              3                                              /**< (EIC_CONFIG) Filter Enable 0 Position */
#define EIC_CONFIG_FILTEN0_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN0_Pos)           /**< (EIC_CONFIG) Filter Enable 0 Mask */
#define EIC_CONFIG_FILTEN0                  EIC_CONFIG_FILTEN0_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN0_Msk instead */
#define EIC_CONFIG_SENSE1_Pos               4                                              /**< (EIC_CONFIG) Input Sense Configuration 1 Position */
#define EIC_CONFIG_SENSE1_Msk               (_U_(0x7) << EIC_CONFIG_SENSE1_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 1 Mask */
#define EIC_CONFIG_SENSE1(value)            (EIC_CONFIG_SENSE1_Msk & ((value) << EIC_CONFIG_SENSE1_Pos))
#define   EIC_CONFIG_SENSE1_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE1_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE1_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE1_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE1_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE1_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE1_NONE              (EIC_CONFIG_SENSE1_NONE_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE1_RISE              (EIC_CONFIG_SENSE1_RISE_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE1_FALL              (EIC_CONFIG_SENSE1_FALL_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE1_BOTH              (EIC_CONFIG_SENSE1_BOTH_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE1_HIGH              (EIC_CONFIG_SENSE1_HIGH_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE1_LOW               (EIC_CONFIG_SENSE1_LOW_Val << EIC_CONFIG_SENSE1_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN1_Pos              7                                              /**< (EIC_CONFIG) Filter Enable 1 Position */
#define EIC_CONFIG_FILTEN1_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN1_Pos)           /**< (EIC_CONFIG) Filter Enable 1 Mask */
#define EIC_CONFIG_FILTEN1                  EIC_CONFIG_FILTEN1_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN1_Msk instead */
#define EIC_CONFIG_SENSE2_Pos               8                                              /**< (EIC_CONFIG) Input Sense Configuration 2 Position */
#define EIC_CONFIG_SENSE2_Msk               (_U_(0x7) << EIC_CONFIG_SENSE2_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 2 Mask */
#define EIC_CONFIG_SENSE2(value)            (EIC_CONFIG_SENSE2_Msk & ((value) << EIC_CONFIG_SENSE2_Pos))
#define   EIC_CONFIG_SENSE2_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE2_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE2_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE2_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE2_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE2_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE2_NONE              (EIC_CONFIG_SENSE2_NONE_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE2_RISE              (EIC_CONFIG_SENSE2_RISE_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE2_FALL              (EIC_CONFIG_SENSE2_FALL_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE2_BOTH              (EIC_CONFIG_SENSE2_BOTH_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE2_HIGH              (EIC_CONFIG_SENSE2_HIGH_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE2_LOW               (EIC_CONFIG_SENSE2_LOW_Val << EIC_CONFIG_SENSE2_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN2_Pos              11                                             /**< (EIC_CONFIG) Filter Enable 2 Position */
#define EIC_CONFIG_FILTEN2_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN2_Pos)           /**< (EIC_CONFIG) Filter Enable 2 Mask */
#define EIC_CONFIG_FILTEN2                  EIC_CONFIG_FILTEN2_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN2_Msk instead */
#define EIC_CONFIG_SENSE3_Pos               12                                             /**< (EIC_CONFIG) Input Sense Configuration 3 Position */
#define EIC_CONFIG_SENSE3_Msk               (_U_(0x7) << EIC_CONFIG_SENSE3_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 3 Mask */
#define EIC_CONFIG_SENSE3(value)            (EIC_CONFIG_SENSE3_Msk & ((value) << EIC_CONFIG_SENSE3_Pos))
#define   EIC_CONFIG_SENSE3_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE3_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE3_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE3_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE3_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE3_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE3_NONE              (EIC_CONFIG_SENSE3_NONE_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE3_RISE              (EIC_CONFIG_SENSE3_RISE_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE3_FALL              (EIC_CONFIG_SENSE3_FALL_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE3_BOTH              (EIC_CONFIG_SENSE3_BOTH_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE3_HIGH              (EIC_CONFIG_SENSE3_HIGH_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE3_LOW               (EIC_CONFIG_SENSE3_LOW_Val << EIC_CONFIG_SENSE3_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN3_Pos              15                                             /**< (EIC_CONFIG) Filter Enable 3 Position */
#define EIC_CONFIG_FILTEN3_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN3_Pos)           /**< (EIC_CONFIG) Filter Enable 3 Mask */
#define EIC_CONFIG_FILTEN3                  EIC_CONFIG_FILTEN3_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN3_Msk instead */
#define EIC_CONFIG_SENSE4_Pos               16                                             /**< (EIC_CONFIG) Input Sense Configuration 4 Position */
#define EIC_CONFIG_SENSE4_Msk               (_U_(0x7) << EIC_CONFIG_SENSE4_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 4 Mask */
#define EIC_CONFIG_SENSE4(value)            (EIC_CONFIG_SENSE4_Msk & ((value) << EIC_CONFIG_SENSE4_Pos))
#define   EIC_CONFIG_SENSE4_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE4_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE4_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE4_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE4_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE4_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE4_NONE              (EIC_CONFIG_SENSE4_NONE_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE4_RISE              (EIC_CONFIG_SENSE4_RISE_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE4_FALL              (EIC_CONFIG_SENSE4_FALL_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE4_BOTH              (EIC_CONFIG_SENSE4_BOTH_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE4_HIGH              (EIC_CONFIG_SENSE4_HIGH_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE4_LOW               (EIC_CONFIG_SENSE4_LOW_Val << EIC_CONFIG_SENSE4_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN4_Pos              19                                             /**< (EIC_CONFIG) Filter Enable 4 Position */
#define EIC_CONFIG_FILTEN4_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN4_Pos)           /**< (EIC_CONFIG) Filter Enable 4 Mask */
#define EIC_CONFIG_FILTEN4                  EIC_CONFIG_FILTEN4_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN4_Msk instead */
#define EIC_CONFIG_SENSE5_Pos               20                                             /**< (EIC_CONFIG) Input Sense Configuration 5 Position */
#define EIC_CONFIG_SENSE5_Msk               (_U_(0x7) << EIC_CONFIG_SENSE5_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 5 Mask */
#define EIC_CONFIG_SENSE5(value)            (EIC_CONFIG_SENSE5_Msk & ((value) << EIC_CONFIG_SENSE5_Pos))
#define   EIC_CONFIG_SENSE5_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE5_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE5_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE5_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE5_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE5_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE5_NONE              (EIC_CONFIG_SENSE5_NONE_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE5_RISE              (EIC_CONFIG_SENSE5_RISE_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE5_FALL              (EIC_CONFIG_SENSE5_FALL_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE5_BOTH              (EIC_CONFIG_SENSE5_BOTH_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE5_HIGH              (EIC_CONFIG_SENSE5_HIGH_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE5_LOW               (EIC_CONFIG_SENSE5_LOW_Val << EIC_CONFIG_SENSE5_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN5_Pos              23                                             /**< (EIC_CONFIG) Filter Enable 5 Position */
#define EIC_CONFIG_FILTEN5_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN5_Pos)           /**< (EIC_CONFIG) Filter Enable 5 Mask */
#define EIC_CONFIG_FILTEN5                  EIC_CONFIG_FILTEN5_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN5_Msk instead */
#define EIC_CONFIG_SENSE6_Pos               24                                             /**< (EIC_CONFIG) Input Sense Configuration 6 Position */
#define EIC_CONFIG_SENSE6_Msk               (_U_(0x7) << EIC_CONFIG_SENSE6_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 6 Mask */
#define EIC_CONFIG_SENSE6(value)            (EIC_CONFIG_SENSE6_Msk & ((value) << EIC_CONFIG_SENSE6_Pos))
#define   EIC_CONFIG_SENSE6_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE6_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE6_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE6_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE6_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE6_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE6_NONE              (EIC_CONFIG_SENSE6_NONE_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE6_RISE              (EIC_CONFIG_SENSE6_RISE_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE6_FALL              (EIC_CONFIG_SENSE6_FALL_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE6_BOTH              (EIC_CONFIG_SENSE6_BOTH_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE6_HIGH              (EIC_CONFIG_SENSE6_HIGH_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE6_LOW               (EIC_CONFIG_SENSE6_LOW_Val << EIC_CONFIG_SENSE6_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN6_Pos              27                                             /**< (EIC_CONFIG) Filter Enable 6 Position */
#define EIC_CONFIG_FILTEN6_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN6_Pos)           /**< (EIC_CONFIG) Filter Enable 6 Mask */
#define EIC_CONFIG_FILTEN6                  EIC_CONFIG_FILTEN6_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN6_Msk instead */
#define EIC_CONFIG_SENSE7_Pos               28                                             /**< (EIC_CONFIG) Input Sense Configuration 7 Position */
#define EIC_CONFIG_SENSE7_Msk               (_U_(0x7) << EIC_CONFIG_SENSE7_Pos)            /**< (EIC_CONFIG) Input Sense Configuration 7 Mask */
#define EIC_CONFIG_SENSE7(value)            (EIC_CONFIG_SENSE7_Msk & ((value) << EIC_CONFIG_SENSE7_Pos))
#define   EIC_CONFIG_SENSE7_NONE_Val        _U_(0x0)                                       /**< (EIC_CONFIG) No detection  */
#define   EIC_CONFIG_SENSE7_RISE_Val        _U_(0x1)                                       /**< (EIC_CONFIG) Rising edge detection  */
#define   EIC_CONFIG_SENSE7_FALL_Val        _U_(0x2)                                       /**< (EIC_CONFIG) Falling edge detection  */
#define   EIC_CONFIG_SENSE7_BOTH_Val        _U_(0x3)                                       /**< (EIC_CONFIG) Both edges detection  */
#define   EIC_CONFIG_SENSE7_HIGH_Val        _U_(0x4)                                       /**< (EIC_CONFIG) High level detection  */
#define   EIC_CONFIG_SENSE7_LOW_Val         _U_(0x5)                                       /**< (EIC_CONFIG) Low level detection  */
#define EIC_CONFIG_SENSE7_NONE              (EIC_CONFIG_SENSE7_NONE_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) No detection Position  */
#define EIC_CONFIG_SENSE7_RISE              (EIC_CONFIG_SENSE7_RISE_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) Rising edge detection Position  */
#define EIC_CONFIG_SENSE7_FALL              (EIC_CONFIG_SENSE7_FALL_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) Falling edge detection Position  */
#define EIC_CONFIG_SENSE7_BOTH              (EIC_CONFIG_SENSE7_BOTH_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) Both edges detection Position  */
#define EIC_CONFIG_SENSE7_HIGH              (EIC_CONFIG_SENSE7_HIGH_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) High level detection Position  */
#define EIC_CONFIG_SENSE7_LOW               (EIC_CONFIG_SENSE7_LOW_Val << EIC_CONFIG_SENSE7_Pos)  /**< (EIC_CONFIG) Low level detection Position  */
#define EIC_CONFIG_FILTEN7_Pos              31                                             /**< (EIC_CONFIG) Filter Enable 7 Position */
#define EIC_CONFIG_FILTEN7_Msk              (_U_(0x1) << EIC_CONFIG_FILTEN7_Pos)           /**< (EIC_CONFIG) Filter Enable 7 Mask */
#define EIC_CONFIG_FILTEN7                  EIC_CONFIG_FILTEN7_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_CONFIG_FILTEN7_Msk instead */
#define EIC_CONFIG_MASK                     _U_(0xFFFFFFFF)                                /**< \deprecated (EIC_CONFIG) Register MASK  (Use EIC_CONFIG_Msk instead)  */
#define EIC_CONFIG_Msk                      _U_(0xFFFFFFFF)                                /**< (EIC_CONFIG) Register Mask  */


/* -------- EIC_DEBOUNCEN : (EIC Offset: 0x30) (R/W 32) Debouncer Enable -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DEBOUNCEN:8;               /**< bit:   0..7  Debouncer Enable                         */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_DEBOUNCEN_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_DEBOUNCEN_OFFSET                (0x30)                                        /**<  (EIC_DEBOUNCEN) Debouncer Enable  Offset */
#define EIC_DEBOUNCEN_RESETVALUE            _U_(0x00)                                     /**<  (EIC_DEBOUNCEN) Debouncer Enable  Reset Value */

#define EIC_DEBOUNCEN_DEBOUNCEN_Pos         0                                              /**< (EIC_DEBOUNCEN) Debouncer Enable Position */
#define EIC_DEBOUNCEN_DEBOUNCEN_Msk         (_U_(0xFF) << EIC_DEBOUNCEN_DEBOUNCEN_Pos)     /**< (EIC_DEBOUNCEN) Debouncer Enable Mask */
#define EIC_DEBOUNCEN_DEBOUNCEN(value)      (EIC_DEBOUNCEN_DEBOUNCEN_Msk & ((value) << EIC_DEBOUNCEN_DEBOUNCEN_Pos))
#define EIC_DEBOUNCEN_MASK                  _U_(0xFF)                                      /**< \deprecated (EIC_DEBOUNCEN) Register MASK  (Use EIC_DEBOUNCEN_Msk instead)  */
#define EIC_DEBOUNCEN_Msk                   _U_(0xFF)                                      /**< (EIC_DEBOUNCEN) Register Mask  */


/* -------- EIC_DPRESCALER : (EIC Offset: 0x34) (R/W 32) Debouncer Prescaler -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PRESCALER0:3;              /**< bit:   0..2  Debouncer Prescaler                      */
    uint32_t STATES0:1;                 /**< bit:      3  Debouncer number of states               */
    uint32_t :12;                       /**< bit:  4..15  Reserved */
    uint32_t TICKON:1;                  /**< bit:     16  Pin Sampler frequency selection          */
    uint32_t :15;                       /**< bit: 17..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :3;                        /**< bit:   0..2  Reserved */
    uint32_t STATES:1;                  /**< bit:      3  Debouncer number of states               */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EIC_DPRESCALER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_DPRESCALER_OFFSET               (0x34)                                        /**<  (EIC_DPRESCALER) Debouncer Prescaler  Offset */
#define EIC_DPRESCALER_RESETVALUE           _U_(0x00)                                     /**<  (EIC_DPRESCALER) Debouncer Prescaler  Reset Value */

#define EIC_DPRESCALER_PRESCALER0_Pos       0                                              /**< (EIC_DPRESCALER) Debouncer Prescaler Position */
#define EIC_DPRESCALER_PRESCALER0_Msk       (_U_(0x7) << EIC_DPRESCALER_PRESCALER0_Pos)    /**< (EIC_DPRESCALER) Debouncer Prescaler Mask */
#define EIC_DPRESCALER_PRESCALER0(value)    (EIC_DPRESCALER_PRESCALER0_Msk & ((value) << EIC_DPRESCALER_PRESCALER0_Pos))
#define EIC_DPRESCALER_STATES0_Pos          3                                              /**< (EIC_DPRESCALER) Debouncer number of states Position */
#define EIC_DPRESCALER_STATES0_Msk          (_U_(0x1) << EIC_DPRESCALER_STATES0_Pos)       /**< (EIC_DPRESCALER) Debouncer number of states Mask */
#define EIC_DPRESCALER_STATES0              EIC_DPRESCALER_STATES0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_DPRESCALER_STATES0_Msk instead */
#define EIC_DPRESCALER_TICKON_Pos           16                                             /**< (EIC_DPRESCALER) Pin Sampler frequency selection Position */
#define EIC_DPRESCALER_TICKON_Msk           (_U_(0x1) << EIC_DPRESCALER_TICKON_Pos)        /**< (EIC_DPRESCALER) Pin Sampler frequency selection Mask */
#define EIC_DPRESCALER_TICKON               EIC_DPRESCALER_TICKON_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_DPRESCALER_TICKON_Msk instead */
#define EIC_DPRESCALER_MASK                 _U_(0x1000F)                                   /**< \deprecated (EIC_DPRESCALER) Register MASK  (Use EIC_DPRESCALER_Msk instead)  */
#define EIC_DPRESCALER_Msk                  _U_(0x1000F)                                   /**< (EIC_DPRESCALER) Register Mask  */

#define EIC_DPRESCALER_STATES_Pos           3                                              /**< (EIC_DPRESCALER Position) Debouncer number of states */
#define EIC_DPRESCALER_STATES_Msk           (_U_(0x1) << EIC_DPRESCALER_STATES_Pos)        /**< (EIC_DPRESCALER Mask) STATES */
#define EIC_DPRESCALER_STATES(value)        (EIC_DPRESCALER_STATES_Msk & ((value) << EIC_DPRESCALER_STATES_Pos))  

/* -------- EIC_PINSTATE : (EIC Offset: 0x38) (R/ 32) Pin State -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PINSTATE:8;                /**< bit:   0..7  Pin State                                */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_PINSTATE_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_PINSTATE_OFFSET                 (0x38)                                        /**<  (EIC_PINSTATE) Pin State  Offset */
#define EIC_PINSTATE_RESETVALUE             _U_(0x00)                                     /**<  (EIC_PINSTATE) Pin State  Reset Value */

#define EIC_PINSTATE_PINSTATE_Pos           0                                              /**< (EIC_PINSTATE) Pin State Position */
#define EIC_PINSTATE_PINSTATE_Msk           (_U_(0xFF) << EIC_PINSTATE_PINSTATE_Pos)       /**< (EIC_PINSTATE) Pin State Mask */
#define EIC_PINSTATE_PINSTATE(value)        (EIC_PINSTATE_PINSTATE_Msk & ((value) << EIC_PINSTATE_PINSTATE_Pos))
#define EIC_PINSTATE_MASK                   _U_(0xFF)                                      /**< \deprecated (EIC_PINSTATE) Register MASK  (Use EIC_PINSTATE_Msk instead)  */
#define EIC_PINSTATE_Msk                    _U_(0xFF)                                      /**< (EIC_PINSTATE) Register Mask  */


/* -------- EIC_NSCHK : (EIC Offset: 0x3c) (R/W 32) Non-secure Interrupt Check Enable -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EXTINT:8;                  /**< bit:   0..7  External Interrupt Nonsecure Check Enable */
    uint32_t :23;                       /**< bit:  8..30  Reserved */
    uint32_t NMI:1;                     /**< bit:     31  Non-Maskable External Interrupt Nonsecure Check Enable */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_NSCHK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_NSCHK_OFFSET                    (0x3C)                                        /**<  (EIC_NSCHK) Non-secure Interrupt Check Enable  Offset */
#define EIC_NSCHK_RESETVALUE                _U_(0x00)                                     /**<  (EIC_NSCHK) Non-secure Interrupt Check Enable  Reset Value */

#define EIC_NSCHK_EXTINT_Pos                0                                              /**< (EIC_NSCHK) External Interrupt Nonsecure Check Enable Position */
#define EIC_NSCHK_EXTINT_Msk                (_U_(0xFF) << EIC_NSCHK_EXTINT_Pos)            /**< (EIC_NSCHK) External Interrupt Nonsecure Check Enable Mask */
#define EIC_NSCHK_EXTINT(value)             (EIC_NSCHK_EXTINT_Msk & ((value) << EIC_NSCHK_EXTINT_Pos))
#define EIC_NSCHK_NMI_Pos                   31                                             /**< (EIC_NSCHK) Non-Maskable External Interrupt Nonsecure Check Enable Position */
#define EIC_NSCHK_NMI_Msk                   (_U_(0x1) << EIC_NSCHK_NMI_Pos)                /**< (EIC_NSCHK) Non-Maskable External Interrupt Nonsecure Check Enable Mask */
#define EIC_NSCHK_NMI                       EIC_NSCHK_NMI_Msk                              /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_NSCHK_NMI_Msk instead */
#define EIC_NSCHK_MASK                      _U_(0x800000FF)                                /**< \deprecated (EIC_NSCHK) Register MASK  (Use EIC_NSCHK_Msk instead)  */
#define EIC_NSCHK_Msk                       _U_(0x800000FF)                                /**< (EIC_NSCHK) Register Mask  */


/* -------- EIC_NONSEC : (EIC Offset: 0x40) (R/W 32) Non-secure Interrupt -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EXTINT:8;                  /**< bit:   0..7  External Interrupt Nonsecure Enable      */
    uint32_t :23;                       /**< bit:  8..30  Reserved */
    uint32_t NMI:1;                     /**< bit:     31  Non-Maskable Interrupt Nonsecure Enable  */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EIC_NONSEC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EIC_NONSEC_OFFSET                   (0x40)                                        /**<  (EIC_NONSEC) Non-secure Interrupt  Offset */
#define EIC_NONSEC_RESETVALUE               _U_(0x00)                                     /**<  (EIC_NONSEC) Non-secure Interrupt  Reset Value */

#define EIC_NONSEC_EXTINT_Pos               0                                              /**< (EIC_NONSEC) External Interrupt Nonsecure Enable Position */
#define EIC_NONSEC_EXTINT_Msk               (_U_(0xFF) << EIC_NONSEC_EXTINT_Pos)           /**< (EIC_NONSEC) External Interrupt Nonsecure Enable Mask */
#define EIC_NONSEC_EXTINT(value)            (EIC_NONSEC_EXTINT_Msk & ((value) << EIC_NONSEC_EXTINT_Pos))
#define EIC_NONSEC_NMI_Pos                  31                                             /**< (EIC_NONSEC) Non-Maskable Interrupt Nonsecure Enable Position */
#define EIC_NONSEC_NMI_Msk                  (_U_(0x1) << EIC_NONSEC_NMI_Pos)               /**< (EIC_NONSEC) Non-Maskable Interrupt Nonsecure Enable Mask */
#define EIC_NONSEC_NMI                      EIC_NONSEC_NMI_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use EIC_NONSEC_NMI_Msk instead */
#define EIC_NONSEC_MASK                     _U_(0x800000FF)                                /**< \deprecated (EIC_NONSEC) Register MASK  (Use EIC_NONSEC_Msk instead)  */
#define EIC_NONSEC_Msk                      _U_(0x800000FF)                                /**< (EIC_NONSEC) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief EIC hardware registers */
typedef struct {  /* External Interrupt Controller */
  __IO EIC_CTRLA_Type                 CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __IO EIC_NMICTRL_Type               NMICTRL;        /**< Offset: 0x01 (R/W   8) Non-Maskable Interrupt Control */
  __IO EIC_NMIFLAG_Type               NMIFLAG;        /**< Offset: 0x02 (R/W   8) Non-Maskable Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved1[1];
  __I  EIC_SYNCBUSY_Type              SYNCBUSY;       /**< Offset: 0x04 (R/   32) Synchronization Busy */
  __IO EIC_EVCTRL_Type                EVCTRL;         /**< Offset: 0x08 (R/W  32) Event Control */
  __IO EIC_INTENCLR_Type              INTENCLR;       /**< Offset: 0x0C (R/W  32) Interrupt Enable Clear */
  __IO EIC_INTENSET_Type              INTENSET;       /**< Offset: 0x10 (R/W  32) Interrupt Enable Set */
  __IO EIC_INTFLAG_Type               INTFLAG;        /**< Offset: 0x14 (R/W  32) Interrupt Flag Status and Clear */
  __IO EIC_ASYNCH_Type                ASYNCH;         /**< Offset: 0x18 (R/W  32) External Interrupt Asynchronous Mode */
  __IO EIC_CONFIG_Type                CONFIG[1];      /**< Offset: 0x1C (R/W  32) External Interrupt Sense Configuration */
  __I  uint8_t                        Reserved2[16];
  __IO EIC_DEBOUNCEN_Type             DEBOUNCEN;      /**< Offset: 0x30 (R/W  32) Debouncer Enable */
  __IO EIC_DPRESCALER_Type            DPRESCALER;     /**< Offset: 0x34 (R/W  32) Debouncer Prescaler */
  __I  EIC_PINSTATE_Type              PINSTATE;       /**< Offset: 0x38 (R/   32) Pin State */
  __IO EIC_NSCHK_Type                 NSCHK;          /**< Offset: 0x3C (R/W  32) Non-secure Interrupt Check Enable */
  __IO EIC_NONSEC_Type                NONSEC;         /**< Offset: 0x40 (R/W  32) Non-secure Interrupt */
} Eic;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of External Interrupt Controller */

#endif /* _SAML10_EIC_COMPONENT_H_ */
