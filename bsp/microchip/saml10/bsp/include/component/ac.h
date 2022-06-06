/**
 * \file
 *
 * \brief Component description for AC
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
#ifndef _SAML10_AC_COMPONENT_H_
#define _SAML10_AC_COMPONENT_H_
#define _SAML10_AC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Analog Comparators
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR AC */
/* ========================================================================== */

#define AC_U2245                      /**< (AC) Module ID */
#define REV_AC 0x102                  /**< (AC) Module revision */

/* -------- AC_CTRLA : (AC Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_CTRLA_OFFSET                     (0x00)                                        /**<  (AC_CTRLA) Control A  Offset */
#define AC_CTRLA_RESETVALUE                 _U_(0x00)                                     /**<  (AC_CTRLA) Control A  Reset Value */

#define AC_CTRLA_SWRST_Pos                  0                                              /**< (AC_CTRLA) Software Reset Position */
#define AC_CTRLA_SWRST_Msk                  (_U_(0x1) << AC_CTRLA_SWRST_Pos)               /**< (AC_CTRLA) Software Reset Mask */
#define AC_CTRLA_SWRST                      AC_CTRLA_SWRST_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_CTRLA_SWRST_Msk instead */
#define AC_CTRLA_ENABLE_Pos                 1                                              /**< (AC_CTRLA) Enable Position */
#define AC_CTRLA_ENABLE_Msk                 (_U_(0x1) << AC_CTRLA_ENABLE_Pos)              /**< (AC_CTRLA) Enable Mask */
#define AC_CTRLA_ENABLE                     AC_CTRLA_ENABLE_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_CTRLA_ENABLE_Msk instead */
#define AC_CTRLA_MASK                       _U_(0x03)                                      /**< \deprecated (AC_CTRLA) Register MASK  (Use AC_CTRLA_Msk instead)  */
#define AC_CTRLA_Msk                        _U_(0x03)                                      /**< (AC_CTRLA) Register Mask  */


/* -------- AC_CTRLB : (AC Offset: 0x01) (/W 8) Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  START0:1;                  /**< bit:      0  Comparator 0 Start Comparison            */
    uint8_t  START1:1;                  /**< bit:      1  Comparator 1 Start Comparison            */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  START:2;                   /**< bit:   0..1  Comparator x Start Comparison            */
    uint8_t  :6;                        /**< bit:   2..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_CTRLB_OFFSET                     (0x01)                                        /**<  (AC_CTRLB) Control B  Offset */
#define AC_CTRLB_RESETVALUE                 _U_(0x00)                                     /**<  (AC_CTRLB) Control B  Reset Value */

#define AC_CTRLB_START0_Pos                 0                                              /**< (AC_CTRLB) Comparator 0 Start Comparison Position */
#define AC_CTRLB_START0_Msk                 (_U_(0x1) << AC_CTRLB_START0_Pos)              /**< (AC_CTRLB) Comparator 0 Start Comparison Mask */
#define AC_CTRLB_START0                     AC_CTRLB_START0_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_CTRLB_START0_Msk instead */
#define AC_CTRLB_START1_Pos                 1                                              /**< (AC_CTRLB) Comparator 1 Start Comparison Position */
#define AC_CTRLB_START1_Msk                 (_U_(0x1) << AC_CTRLB_START1_Pos)              /**< (AC_CTRLB) Comparator 1 Start Comparison Mask */
#define AC_CTRLB_START1                     AC_CTRLB_START1_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_CTRLB_START1_Msk instead */
#define AC_CTRLB_MASK                       _U_(0x03)                                      /**< \deprecated (AC_CTRLB) Register MASK  (Use AC_CTRLB_Msk instead)  */
#define AC_CTRLB_Msk                        _U_(0x03)                                      /**< (AC_CTRLB) Register Mask  */

#define AC_CTRLB_START_Pos                  0                                              /**< (AC_CTRLB Position) Comparator x Start Comparison */
#define AC_CTRLB_START_Msk                  (_U_(0x3) << AC_CTRLB_START_Pos)               /**< (AC_CTRLB Mask) START */
#define AC_CTRLB_START(value)               (AC_CTRLB_START_Msk & ((value) << AC_CTRLB_START_Pos))  

/* -------- AC_EVCTRL : (AC Offset: 0x02) (R/W 16) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t COMPEO0:1;                 /**< bit:      0  Comparator 0 Event Output Enable         */
    uint16_t COMPEO1:1;                 /**< bit:      1  Comparator 1 Event Output Enable         */
    uint16_t :2;                        /**< bit:   2..3  Reserved */
    uint16_t WINEO0:1;                  /**< bit:      4  Window 0 Event Output Enable             */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t COMPEI0:1;                 /**< bit:      8  Comparator 0 Event Input Enable          */
    uint16_t COMPEI1:1;                 /**< bit:      9  Comparator 1 Event Input Enable          */
    uint16_t :2;                        /**< bit: 10..11  Reserved */
    uint16_t INVEI0:1;                  /**< bit:     12  Comparator 0 Input Event Invert Enable   */
    uint16_t INVEI1:1;                  /**< bit:     13  Comparator 1 Input Event Invert Enable   */
    uint16_t :2;                        /**< bit: 14..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t COMPEO:2;                  /**< bit:   0..1  Comparator x Event Output Enable         */
    uint16_t :2;                        /**< bit:   2..3  Reserved */
    uint16_t WINEO:1;                   /**< bit:      4  Window x Event Output Enable             */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t COMPEI:2;                  /**< bit:   8..9  Comparator x Event Input Enable          */
    uint16_t :2;                        /**< bit: 10..11  Reserved */
    uint16_t INVEI:2;                   /**< bit: 12..13  Comparator x Input Event Invert Enable   */
    uint16_t :2;                        /**< bit: 14..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} AC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_EVCTRL_OFFSET                    (0x02)                                        /**<  (AC_EVCTRL) Event Control  Offset */
#define AC_EVCTRL_RESETVALUE                _U_(0x00)                                     /**<  (AC_EVCTRL) Event Control  Reset Value */

#define AC_EVCTRL_COMPEO0_Pos               0                                              /**< (AC_EVCTRL) Comparator 0 Event Output Enable Position */
#define AC_EVCTRL_COMPEO0_Msk               (_U_(0x1) << AC_EVCTRL_COMPEO0_Pos)            /**< (AC_EVCTRL) Comparator 0 Event Output Enable Mask */
#define AC_EVCTRL_COMPEO0                   AC_EVCTRL_COMPEO0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_COMPEO0_Msk instead */
#define AC_EVCTRL_COMPEO1_Pos               1                                              /**< (AC_EVCTRL) Comparator 1 Event Output Enable Position */
#define AC_EVCTRL_COMPEO1_Msk               (_U_(0x1) << AC_EVCTRL_COMPEO1_Pos)            /**< (AC_EVCTRL) Comparator 1 Event Output Enable Mask */
#define AC_EVCTRL_COMPEO1                   AC_EVCTRL_COMPEO1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_COMPEO1_Msk instead */
#define AC_EVCTRL_WINEO0_Pos                4                                              /**< (AC_EVCTRL) Window 0 Event Output Enable Position */
#define AC_EVCTRL_WINEO0_Msk                (_U_(0x1) << AC_EVCTRL_WINEO0_Pos)             /**< (AC_EVCTRL) Window 0 Event Output Enable Mask */
#define AC_EVCTRL_WINEO0                    AC_EVCTRL_WINEO0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_WINEO0_Msk instead */
#define AC_EVCTRL_COMPEI0_Pos               8                                              /**< (AC_EVCTRL) Comparator 0 Event Input Enable Position */
#define AC_EVCTRL_COMPEI0_Msk               (_U_(0x1) << AC_EVCTRL_COMPEI0_Pos)            /**< (AC_EVCTRL) Comparator 0 Event Input Enable Mask */
#define AC_EVCTRL_COMPEI0                   AC_EVCTRL_COMPEI0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_COMPEI0_Msk instead */
#define AC_EVCTRL_COMPEI1_Pos               9                                              /**< (AC_EVCTRL) Comparator 1 Event Input Enable Position */
#define AC_EVCTRL_COMPEI1_Msk               (_U_(0x1) << AC_EVCTRL_COMPEI1_Pos)            /**< (AC_EVCTRL) Comparator 1 Event Input Enable Mask */
#define AC_EVCTRL_COMPEI1                   AC_EVCTRL_COMPEI1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_COMPEI1_Msk instead */
#define AC_EVCTRL_INVEI0_Pos                12                                             /**< (AC_EVCTRL) Comparator 0 Input Event Invert Enable Position */
#define AC_EVCTRL_INVEI0_Msk                (_U_(0x1) << AC_EVCTRL_INVEI0_Pos)             /**< (AC_EVCTRL) Comparator 0 Input Event Invert Enable Mask */
#define AC_EVCTRL_INVEI0                    AC_EVCTRL_INVEI0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_INVEI0_Msk instead */
#define AC_EVCTRL_INVEI1_Pos                13                                             /**< (AC_EVCTRL) Comparator 1 Input Event Invert Enable Position */
#define AC_EVCTRL_INVEI1_Msk                (_U_(0x1) << AC_EVCTRL_INVEI1_Pos)             /**< (AC_EVCTRL) Comparator 1 Input Event Invert Enable Mask */
#define AC_EVCTRL_INVEI1                    AC_EVCTRL_INVEI1_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_EVCTRL_INVEI1_Msk instead */
#define AC_EVCTRL_MASK                      _U_(0x3313)                                    /**< \deprecated (AC_EVCTRL) Register MASK  (Use AC_EVCTRL_Msk instead)  */
#define AC_EVCTRL_Msk                       _U_(0x3313)                                    /**< (AC_EVCTRL) Register Mask  */

#define AC_EVCTRL_COMPEO_Pos                0                                              /**< (AC_EVCTRL Position) Comparator x Event Output Enable */
#define AC_EVCTRL_COMPEO_Msk                (_U_(0x3) << AC_EVCTRL_COMPEO_Pos)             /**< (AC_EVCTRL Mask) COMPEO */
#define AC_EVCTRL_COMPEO(value)             (AC_EVCTRL_COMPEO_Msk & ((value) << AC_EVCTRL_COMPEO_Pos))  
#define AC_EVCTRL_WINEO_Pos                 4                                              /**< (AC_EVCTRL Position) Window x Event Output Enable */
#define AC_EVCTRL_WINEO_Msk                 (_U_(0x1) << AC_EVCTRL_WINEO_Pos)              /**< (AC_EVCTRL Mask) WINEO */
#define AC_EVCTRL_WINEO(value)              (AC_EVCTRL_WINEO_Msk & ((value) << AC_EVCTRL_WINEO_Pos))  
#define AC_EVCTRL_COMPEI_Pos                8                                              /**< (AC_EVCTRL Position) Comparator x Event Input Enable */
#define AC_EVCTRL_COMPEI_Msk                (_U_(0x3) << AC_EVCTRL_COMPEI_Pos)             /**< (AC_EVCTRL Mask) COMPEI */
#define AC_EVCTRL_COMPEI(value)             (AC_EVCTRL_COMPEI_Msk & ((value) << AC_EVCTRL_COMPEI_Pos))  
#define AC_EVCTRL_INVEI_Pos                 12                                             /**< (AC_EVCTRL Position) Comparator x Input Event Invert Enable */
#define AC_EVCTRL_INVEI_Msk                 (_U_(0x3) << AC_EVCTRL_INVEI_Pos)              /**< (AC_EVCTRL Mask) INVEI */
#define AC_EVCTRL_INVEI(value)              (AC_EVCTRL_INVEI_Msk & ((value) << AC_EVCTRL_INVEI_Pos))  

/* -------- AC_INTENCLR : (AC Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  COMP0:1;                   /**< bit:      0  Comparator 0 Interrupt Enable            */
    uint8_t  COMP1:1;                   /**< bit:      1  Comparator 1 Interrupt Enable            */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  WIN0:1;                    /**< bit:      4  Window 0 Interrupt Enable                */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  COMP:2;                    /**< bit:   0..1  Comparator x Interrupt Enable            */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  WIN:1;                     /**< bit:      4  Window x Interrupt Enable                */
    uint8_t  :3;                        /**< bit:   5..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_INTENCLR_OFFSET                  (0x04)                                        /**<  (AC_INTENCLR) Interrupt Enable Clear  Offset */
#define AC_INTENCLR_RESETVALUE              _U_(0x00)                                     /**<  (AC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define AC_INTENCLR_COMP0_Pos               0                                              /**< (AC_INTENCLR) Comparator 0 Interrupt Enable Position */
#define AC_INTENCLR_COMP0_Msk               (_U_(0x1) << AC_INTENCLR_COMP0_Pos)            /**< (AC_INTENCLR) Comparator 0 Interrupt Enable Mask */
#define AC_INTENCLR_COMP0                   AC_INTENCLR_COMP0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENCLR_COMP0_Msk instead */
#define AC_INTENCLR_COMP1_Pos               1                                              /**< (AC_INTENCLR) Comparator 1 Interrupt Enable Position */
#define AC_INTENCLR_COMP1_Msk               (_U_(0x1) << AC_INTENCLR_COMP1_Pos)            /**< (AC_INTENCLR) Comparator 1 Interrupt Enable Mask */
#define AC_INTENCLR_COMP1                   AC_INTENCLR_COMP1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENCLR_COMP1_Msk instead */
#define AC_INTENCLR_WIN0_Pos                4                                              /**< (AC_INTENCLR) Window 0 Interrupt Enable Position */
#define AC_INTENCLR_WIN0_Msk                (_U_(0x1) << AC_INTENCLR_WIN0_Pos)             /**< (AC_INTENCLR) Window 0 Interrupt Enable Mask */
#define AC_INTENCLR_WIN0                    AC_INTENCLR_WIN0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENCLR_WIN0_Msk instead */
#define AC_INTENCLR_MASK                    _U_(0x13)                                      /**< \deprecated (AC_INTENCLR) Register MASK  (Use AC_INTENCLR_Msk instead)  */
#define AC_INTENCLR_Msk                     _U_(0x13)                                      /**< (AC_INTENCLR) Register Mask  */

#define AC_INTENCLR_COMP_Pos                0                                              /**< (AC_INTENCLR Position) Comparator x Interrupt Enable */
#define AC_INTENCLR_COMP_Msk                (_U_(0x3) << AC_INTENCLR_COMP_Pos)             /**< (AC_INTENCLR Mask) COMP */
#define AC_INTENCLR_COMP(value)             (AC_INTENCLR_COMP_Msk & ((value) << AC_INTENCLR_COMP_Pos))  
#define AC_INTENCLR_WIN_Pos                 4                                              /**< (AC_INTENCLR Position) Window x Interrupt Enable */
#define AC_INTENCLR_WIN_Msk                 (_U_(0x1) << AC_INTENCLR_WIN_Pos)              /**< (AC_INTENCLR Mask) WIN */
#define AC_INTENCLR_WIN(value)              (AC_INTENCLR_WIN_Msk & ((value) << AC_INTENCLR_WIN_Pos))  

/* -------- AC_INTENSET : (AC Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  COMP0:1;                   /**< bit:      0  Comparator 0 Interrupt Enable            */
    uint8_t  COMP1:1;                   /**< bit:      1  Comparator 1 Interrupt Enable            */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  WIN0:1;                    /**< bit:      4  Window 0 Interrupt Enable                */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  COMP:2;                    /**< bit:   0..1  Comparator x Interrupt Enable            */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  WIN:1;                     /**< bit:      4  Window x Interrupt Enable                */
    uint8_t  :3;                        /**< bit:   5..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_INTENSET_OFFSET                  (0x05)                                        /**<  (AC_INTENSET) Interrupt Enable Set  Offset */
#define AC_INTENSET_RESETVALUE              _U_(0x00)                                     /**<  (AC_INTENSET) Interrupt Enable Set  Reset Value */

#define AC_INTENSET_COMP0_Pos               0                                              /**< (AC_INTENSET) Comparator 0 Interrupt Enable Position */
#define AC_INTENSET_COMP0_Msk               (_U_(0x1) << AC_INTENSET_COMP0_Pos)            /**< (AC_INTENSET) Comparator 0 Interrupt Enable Mask */
#define AC_INTENSET_COMP0                   AC_INTENSET_COMP0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENSET_COMP0_Msk instead */
#define AC_INTENSET_COMP1_Pos               1                                              /**< (AC_INTENSET) Comparator 1 Interrupt Enable Position */
#define AC_INTENSET_COMP1_Msk               (_U_(0x1) << AC_INTENSET_COMP1_Pos)            /**< (AC_INTENSET) Comparator 1 Interrupt Enable Mask */
#define AC_INTENSET_COMP1                   AC_INTENSET_COMP1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENSET_COMP1_Msk instead */
#define AC_INTENSET_WIN0_Pos                4                                              /**< (AC_INTENSET) Window 0 Interrupt Enable Position */
#define AC_INTENSET_WIN0_Msk                (_U_(0x1) << AC_INTENSET_WIN0_Pos)             /**< (AC_INTENSET) Window 0 Interrupt Enable Mask */
#define AC_INTENSET_WIN0                    AC_INTENSET_WIN0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTENSET_WIN0_Msk instead */
#define AC_INTENSET_MASK                    _U_(0x13)                                      /**< \deprecated (AC_INTENSET) Register MASK  (Use AC_INTENSET_Msk instead)  */
#define AC_INTENSET_Msk                     _U_(0x13)                                      /**< (AC_INTENSET) Register Mask  */

#define AC_INTENSET_COMP_Pos                0                                              /**< (AC_INTENSET Position) Comparator x Interrupt Enable */
#define AC_INTENSET_COMP_Msk                (_U_(0x3) << AC_INTENSET_COMP_Pos)             /**< (AC_INTENSET Mask) COMP */
#define AC_INTENSET_COMP(value)             (AC_INTENSET_COMP_Msk & ((value) << AC_INTENSET_COMP_Pos))  
#define AC_INTENSET_WIN_Pos                 4                                              /**< (AC_INTENSET Position) Window x Interrupt Enable */
#define AC_INTENSET_WIN_Msk                 (_U_(0x1) << AC_INTENSET_WIN_Pos)              /**< (AC_INTENSET Mask) WIN */
#define AC_INTENSET_WIN(value)              (AC_INTENSET_WIN_Msk & ((value) << AC_INTENSET_WIN_Pos))  

/* -------- AC_INTFLAG : (AC Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t COMP0:1;                   /**< bit:      0  Comparator 0                             */
    __I uint8_t COMP1:1;                   /**< bit:      1  Comparator 1                             */
    __I uint8_t :2;                        /**< bit:   2..3  Reserved */
    __I uint8_t WIN0:1;                    /**< bit:      4  Window 0                                 */
    __I uint8_t :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    __I uint8_t COMP:2;                    /**< bit:   0..1  Comparator x                             */
    __I uint8_t :2;                        /**< bit:   2..3  Reserved */
    __I uint8_t WIN:1;                     /**< bit:      4  Window x                                 */
    __I uint8_t :3;                        /**< bit:   5..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_INTFLAG_OFFSET                   (0x06)                                        /**<  (AC_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define AC_INTFLAG_RESETVALUE               _U_(0x00)                                     /**<  (AC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define AC_INTFLAG_COMP0_Pos                0                                              /**< (AC_INTFLAG) Comparator 0 Position */
#define AC_INTFLAG_COMP0_Msk                (_U_(0x1) << AC_INTFLAG_COMP0_Pos)             /**< (AC_INTFLAG) Comparator 0 Mask */
#define AC_INTFLAG_COMP0                    AC_INTFLAG_COMP0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTFLAG_COMP0_Msk instead */
#define AC_INTFLAG_COMP1_Pos                1                                              /**< (AC_INTFLAG) Comparator 1 Position */
#define AC_INTFLAG_COMP1_Msk                (_U_(0x1) << AC_INTFLAG_COMP1_Pos)             /**< (AC_INTFLAG) Comparator 1 Mask */
#define AC_INTFLAG_COMP1                    AC_INTFLAG_COMP1_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTFLAG_COMP1_Msk instead */
#define AC_INTFLAG_WIN0_Pos                 4                                              /**< (AC_INTFLAG) Window 0 Position */
#define AC_INTFLAG_WIN0_Msk                 (_U_(0x1) << AC_INTFLAG_WIN0_Pos)              /**< (AC_INTFLAG) Window 0 Mask */
#define AC_INTFLAG_WIN0                     AC_INTFLAG_WIN0_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_INTFLAG_WIN0_Msk instead */
#define AC_INTFLAG_MASK                     _U_(0x13)                                      /**< \deprecated (AC_INTFLAG) Register MASK  (Use AC_INTFLAG_Msk instead)  */
#define AC_INTFLAG_Msk                      _U_(0x13)                                      /**< (AC_INTFLAG) Register Mask  */

#define AC_INTFLAG_COMP_Pos                 0                                              /**< (AC_INTFLAG Position) Comparator x */
#define AC_INTFLAG_COMP_Msk                 (_U_(0x3) << AC_INTFLAG_COMP_Pos)              /**< (AC_INTFLAG Mask) COMP */
#define AC_INTFLAG_COMP(value)              (AC_INTFLAG_COMP_Msk & ((value) << AC_INTFLAG_COMP_Pos))  
#define AC_INTFLAG_WIN_Pos                  4                                              /**< (AC_INTFLAG Position) Window x */
#define AC_INTFLAG_WIN_Msk                  (_U_(0x1) << AC_INTFLAG_WIN_Pos)               /**< (AC_INTFLAG Mask) WIN */
#define AC_INTFLAG_WIN(value)               (AC_INTFLAG_WIN_Msk & ((value) << AC_INTFLAG_WIN_Pos))  

/* -------- AC_STATUSA : (AC Offset: 0x07) (R/ 8) Status A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  STATE0:1;                  /**< bit:      0  Comparator 0 Current State               */
    uint8_t  STATE1:1;                  /**< bit:      1  Comparator 1 Current State               */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  WSTATE0:2;                 /**< bit:   4..5  Window 0 Current State                   */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  STATE:2;                   /**< bit:   0..1  Comparator x Current State               */
    uint8_t  :6;                        /**< bit:   2..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_STATUSA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_STATUSA_OFFSET                   (0x07)                                        /**<  (AC_STATUSA) Status A  Offset */
#define AC_STATUSA_RESETVALUE               _U_(0x00)                                     /**<  (AC_STATUSA) Status A  Reset Value */

#define AC_STATUSA_STATE0_Pos               0                                              /**< (AC_STATUSA) Comparator 0 Current State Position */
#define AC_STATUSA_STATE0_Msk               (_U_(0x1) << AC_STATUSA_STATE0_Pos)            /**< (AC_STATUSA) Comparator 0 Current State Mask */
#define AC_STATUSA_STATE0                   AC_STATUSA_STATE0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_STATUSA_STATE0_Msk instead */
#define AC_STATUSA_STATE1_Pos               1                                              /**< (AC_STATUSA) Comparator 1 Current State Position */
#define AC_STATUSA_STATE1_Msk               (_U_(0x1) << AC_STATUSA_STATE1_Pos)            /**< (AC_STATUSA) Comparator 1 Current State Mask */
#define AC_STATUSA_STATE1                   AC_STATUSA_STATE1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_STATUSA_STATE1_Msk instead */
#define AC_STATUSA_WSTATE0_Pos              4                                              /**< (AC_STATUSA) Window 0 Current State Position */
#define AC_STATUSA_WSTATE0_Msk              (_U_(0x3) << AC_STATUSA_WSTATE0_Pos)           /**< (AC_STATUSA) Window 0 Current State Mask */
#define AC_STATUSA_WSTATE0(value)           (AC_STATUSA_WSTATE0_Msk & ((value) << AC_STATUSA_WSTATE0_Pos))
#define   AC_STATUSA_WSTATE0_ABOVE_Val      _U_(0x0)                                       /**< (AC_STATUSA) Signal is above window  */
#define   AC_STATUSA_WSTATE0_INSIDE_Val     _U_(0x1)                                       /**< (AC_STATUSA) Signal is inside window  */
#define   AC_STATUSA_WSTATE0_BELOW_Val      _U_(0x2)                                       /**< (AC_STATUSA) Signal is below window  */
#define AC_STATUSA_WSTATE0_ABOVE            (AC_STATUSA_WSTATE0_ABOVE_Val << AC_STATUSA_WSTATE0_Pos)  /**< (AC_STATUSA) Signal is above window Position  */
#define AC_STATUSA_WSTATE0_INSIDE           (AC_STATUSA_WSTATE0_INSIDE_Val << AC_STATUSA_WSTATE0_Pos)  /**< (AC_STATUSA) Signal is inside window Position  */
#define AC_STATUSA_WSTATE0_BELOW            (AC_STATUSA_WSTATE0_BELOW_Val << AC_STATUSA_WSTATE0_Pos)  /**< (AC_STATUSA) Signal is below window Position  */
#define AC_STATUSA_MASK                     _U_(0x33)                                      /**< \deprecated (AC_STATUSA) Register MASK  (Use AC_STATUSA_Msk instead)  */
#define AC_STATUSA_Msk                      _U_(0x33)                                      /**< (AC_STATUSA) Register Mask  */

#define AC_STATUSA_STATE_Pos                0                                              /**< (AC_STATUSA Position) Comparator x Current State */
#define AC_STATUSA_STATE_Msk                (_U_(0x3) << AC_STATUSA_STATE_Pos)             /**< (AC_STATUSA Mask) STATE */
#define AC_STATUSA_STATE(value)             (AC_STATUSA_STATE_Msk & ((value) << AC_STATUSA_STATE_Pos))  

/* -------- AC_STATUSB : (AC Offset: 0x08) (R/ 8) Status B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  READY0:1;                  /**< bit:      0  Comparator 0 Ready                       */
    uint8_t  READY1:1;                  /**< bit:      1  Comparator 1 Ready                       */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  READY:2;                   /**< bit:   0..1  Comparator x Ready                       */
    uint8_t  :6;                        /**< bit:   2..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_STATUSB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_STATUSB_OFFSET                   (0x08)                                        /**<  (AC_STATUSB) Status B  Offset */
#define AC_STATUSB_RESETVALUE               _U_(0x00)                                     /**<  (AC_STATUSB) Status B  Reset Value */

#define AC_STATUSB_READY0_Pos               0                                              /**< (AC_STATUSB) Comparator 0 Ready Position */
#define AC_STATUSB_READY0_Msk               (_U_(0x1) << AC_STATUSB_READY0_Pos)            /**< (AC_STATUSB) Comparator 0 Ready Mask */
#define AC_STATUSB_READY0                   AC_STATUSB_READY0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_STATUSB_READY0_Msk instead */
#define AC_STATUSB_READY1_Pos               1                                              /**< (AC_STATUSB) Comparator 1 Ready Position */
#define AC_STATUSB_READY1_Msk               (_U_(0x1) << AC_STATUSB_READY1_Pos)            /**< (AC_STATUSB) Comparator 1 Ready Mask */
#define AC_STATUSB_READY1                   AC_STATUSB_READY1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_STATUSB_READY1_Msk instead */
#define AC_STATUSB_MASK                     _U_(0x03)                                      /**< \deprecated (AC_STATUSB) Register MASK  (Use AC_STATUSB_Msk instead)  */
#define AC_STATUSB_Msk                      _U_(0x03)                                      /**< (AC_STATUSB) Register Mask  */

#define AC_STATUSB_READY_Pos                0                                              /**< (AC_STATUSB Position) Comparator x Ready */
#define AC_STATUSB_READY_Msk                (_U_(0x3) << AC_STATUSB_READY_Pos)             /**< (AC_STATUSB Mask) READY */
#define AC_STATUSB_READY(value)             (AC_STATUSB_READY_Msk & ((value) << AC_STATUSB_READY_Pos))  

/* -------- AC_DBGCTRL : (AC Offset: 0x09) (R/W 8) Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGRUN:1;                  /**< bit:      0  Debug Run                                */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_DBGCTRL_OFFSET                   (0x09)                                        /**<  (AC_DBGCTRL) Debug Control  Offset */
#define AC_DBGCTRL_RESETVALUE               _U_(0x00)                                     /**<  (AC_DBGCTRL) Debug Control  Reset Value */

#define AC_DBGCTRL_DBGRUN_Pos               0                                              /**< (AC_DBGCTRL) Debug Run Position */
#define AC_DBGCTRL_DBGRUN_Msk               (_U_(0x1) << AC_DBGCTRL_DBGRUN_Pos)            /**< (AC_DBGCTRL) Debug Run Mask */
#define AC_DBGCTRL_DBGRUN                   AC_DBGCTRL_DBGRUN_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_DBGCTRL_DBGRUN_Msk instead */
#define AC_DBGCTRL_MASK                     _U_(0x01)                                      /**< \deprecated (AC_DBGCTRL) Register MASK  (Use AC_DBGCTRL_Msk instead)  */
#define AC_DBGCTRL_Msk                      _U_(0x01)                                      /**< (AC_DBGCTRL) Register Mask  */


/* -------- AC_WINCTRL : (AC Offset: 0x0a) (R/W 8) Window Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WEN0:1;                    /**< bit:      0  Window 0 Mode Enable                     */
    uint8_t  WINTSEL0:2;                /**< bit:   1..2  Window 0 Interrupt Selection             */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  WEN:1;                     /**< bit:      0  Window x Mode Enable                     */
    uint8_t  :7;                        /**< bit:   1..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AC_WINCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_WINCTRL_OFFSET                   (0x0A)                                        /**<  (AC_WINCTRL) Window Control  Offset */
#define AC_WINCTRL_RESETVALUE               _U_(0x00)                                     /**<  (AC_WINCTRL) Window Control  Reset Value */

#define AC_WINCTRL_WEN0_Pos                 0                                              /**< (AC_WINCTRL) Window 0 Mode Enable Position */
#define AC_WINCTRL_WEN0_Msk                 (_U_(0x1) << AC_WINCTRL_WEN0_Pos)              /**< (AC_WINCTRL) Window 0 Mode Enable Mask */
#define AC_WINCTRL_WEN0                     AC_WINCTRL_WEN0_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_WINCTRL_WEN0_Msk instead */
#define AC_WINCTRL_WINTSEL0_Pos             1                                              /**< (AC_WINCTRL) Window 0 Interrupt Selection Position */
#define AC_WINCTRL_WINTSEL0_Msk             (_U_(0x3) << AC_WINCTRL_WINTSEL0_Pos)          /**< (AC_WINCTRL) Window 0 Interrupt Selection Mask */
#define AC_WINCTRL_WINTSEL0(value)          (AC_WINCTRL_WINTSEL0_Msk & ((value) << AC_WINCTRL_WINTSEL0_Pos))
#define   AC_WINCTRL_WINTSEL0_ABOVE_Val     _U_(0x0)                                       /**< (AC_WINCTRL) Interrupt on signal above window  */
#define   AC_WINCTRL_WINTSEL0_INSIDE_Val    _U_(0x1)                                       /**< (AC_WINCTRL) Interrupt on signal inside window  */
#define   AC_WINCTRL_WINTSEL0_BELOW_Val     _U_(0x2)                                       /**< (AC_WINCTRL) Interrupt on signal below window  */
#define   AC_WINCTRL_WINTSEL0_OUTSIDE_Val   _U_(0x3)                                       /**< (AC_WINCTRL) Interrupt on signal outside window  */
#define AC_WINCTRL_WINTSEL0_ABOVE           (AC_WINCTRL_WINTSEL0_ABOVE_Val << AC_WINCTRL_WINTSEL0_Pos)  /**< (AC_WINCTRL) Interrupt on signal above window Position  */
#define AC_WINCTRL_WINTSEL0_INSIDE          (AC_WINCTRL_WINTSEL0_INSIDE_Val << AC_WINCTRL_WINTSEL0_Pos)  /**< (AC_WINCTRL) Interrupt on signal inside window Position  */
#define AC_WINCTRL_WINTSEL0_BELOW           (AC_WINCTRL_WINTSEL0_BELOW_Val << AC_WINCTRL_WINTSEL0_Pos)  /**< (AC_WINCTRL) Interrupt on signal below window Position  */
#define AC_WINCTRL_WINTSEL0_OUTSIDE         (AC_WINCTRL_WINTSEL0_OUTSIDE_Val << AC_WINCTRL_WINTSEL0_Pos)  /**< (AC_WINCTRL) Interrupt on signal outside window Position  */
#define AC_WINCTRL_MASK                     _U_(0x07)                                      /**< \deprecated (AC_WINCTRL) Register MASK  (Use AC_WINCTRL_Msk instead)  */
#define AC_WINCTRL_Msk                      _U_(0x07)                                      /**< (AC_WINCTRL) Register Mask  */

#define AC_WINCTRL_WEN_Pos                  0                                              /**< (AC_WINCTRL Position) Window x Mode Enable */
#define AC_WINCTRL_WEN_Msk                  (_U_(0x1) << AC_WINCTRL_WEN_Pos)               /**< (AC_WINCTRL Mask) WEN */
#define AC_WINCTRL_WEN(value)               (AC_WINCTRL_WEN_Msk & ((value) << AC_WINCTRL_WEN_Pos))  

/* -------- AC_SCALER : (AC Offset: 0x0c) (R/W 8) Scaler n -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  VALUE:6;                   /**< bit:   0..5  Scaler Value                             */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AC_SCALER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_SCALER_OFFSET                    (0x0C)                                        /**<  (AC_SCALER) Scaler n  Offset */
#define AC_SCALER_RESETVALUE                _U_(0x00)                                     /**<  (AC_SCALER) Scaler n  Reset Value */

#define AC_SCALER_VALUE_Pos                 0                                              /**< (AC_SCALER) Scaler Value Position */
#define AC_SCALER_VALUE_Msk                 (_U_(0x3F) << AC_SCALER_VALUE_Pos)             /**< (AC_SCALER) Scaler Value Mask */
#define AC_SCALER_VALUE(value)              (AC_SCALER_VALUE_Msk & ((value) << AC_SCALER_VALUE_Pos))
#define AC_SCALER_MASK                      _U_(0x3F)                                      /**< \deprecated (AC_SCALER) Register MASK  (Use AC_SCALER_Msk instead)  */
#define AC_SCALER_Msk                       _U_(0x3F)                                      /**< (AC_SCALER) Register Mask  */


/* -------- AC_COMPCTRL : (AC Offset: 0x10) (R/W 32) Comparator Control n -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t SINGLE:1;                  /**< bit:      2  Single-Shot Mode                         */
    uint32_t INTSEL:2;                  /**< bit:   3..4  Interrupt Selection                      */
    uint32_t :1;                        /**< bit:      5  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t MUXNEG:3;                  /**< bit:  8..10  Negative Input Mux Selection             */
    uint32_t :1;                        /**< bit:     11  Reserved */
    uint32_t MUXPOS:3;                  /**< bit: 12..14  Positive Input Mux Selection             */
    uint32_t SWAP:1;                    /**< bit:     15  Swap Inputs and Invert                   */
    uint32_t SPEED:2;                   /**< bit: 16..17  Speed Selection                          */
    uint32_t :1;                        /**< bit:     18  Reserved */
    uint32_t HYSTEN:1;                  /**< bit:     19  Hysteresis Enable                        */
    uint32_t HYST:2;                    /**< bit: 20..21  Hysteresis Level                         */
    uint32_t :2;                        /**< bit: 22..23  Reserved */
    uint32_t FLEN:3;                    /**< bit: 24..26  Filter Length                            */
    uint32_t :1;                        /**< bit:     27  Reserved */
    uint32_t OUT:2;                     /**< bit: 28..29  Output                                   */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AC_COMPCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_COMPCTRL_OFFSET                  (0x10)                                        /**<  (AC_COMPCTRL) Comparator Control n  Offset */
#define AC_COMPCTRL_RESETVALUE              _U_(0x00)                                     /**<  (AC_COMPCTRL) Comparator Control n  Reset Value */

#define AC_COMPCTRL_ENABLE_Pos              1                                              /**< (AC_COMPCTRL) Enable Position */
#define AC_COMPCTRL_ENABLE_Msk              (_U_(0x1) << AC_COMPCTRL_ENABLE_Pos)           /**< (AC_COMPCTRL) Enable Mask */
#define AC_COMPCTRL_ENABLE                  AC_COMPCTRL_ENABLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_COMPCTRL_ENABLE_Msk instead */
#define AC_COMPCTRL_SINGLE_Pos              2                                              /**< (AC_COMPCTRL) Single-Shot Mode Position */
#define AC_COMPCTRL_SINGLE_Msk              (_U_(0x1) << AC_COMPCTRL_SINGLE_Pos)           /**< (AC_COMPCTRL) Single-Shot Mode Mask */
#define AC_COMPCTRL_SINGLE                  AC_COMPCTRL_SINGLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_COMPCTRL_SINGLE_Msk instead */
#define AC_COMPCTRL_INTSEL_Pos              3                                              /**< (AC_COMPCTRL) Interrupt Selection Position */
#define AC_COMPCTRL_INTSEL_Msk              (_U_(0x3) << AC_COMPCTRL_INTSEL_Pos)           /**< (AC_COMPCTRL) Interrupt Selection Mask */
#define AC_COMPCTRL_INTSEL(value)           (AC_COMPCTRL_INTSEL_Msk & ((value) << AC_COMPCTRL_INTSEL_Pos))
#define   AC_COMPCTRL_INTSEL_TOGGLE_Val     _U_(0x0)                                       /**< (AC_COMPCTRL) Interrupt on comparator output toggle  */
#define   AC_COMPCTRL_INTSEL_RISING_Val     _U_(0x1)                                       /**< (AC_COMPCTRL) Interrupt on comparator output rising  */
#define   AC_COMPCTRL_INTSEL_FALLING_Val    _U_(0x2)                                       /**< (AC_COMPCTRL) Interrupt on comparator output falling  */
#define   AC_COMPCTRL_INTSEL_EOC_Val        _U_(0x3)                                       /**< (AC_COMPCTRL) Interrupt on end of comparison (single-shot mode only)  */
#define AC_COMPCTRL_INTSEL_TOGGLE           (AC_COMPCTRL_INTSEL_TOGGLE_Val << AC_COMPCTRL_INTSEL_Pos)  /**< (AC_COMPCTRL) Interrupt on comparator output toggle Position  */
#define AC_COMPCTRL_INTSEL_RISING           (AC_COMPCTRL_INTSEL_RISING_Val << AC_COMPCTRL_INTSEL_Pos)  /**< (AC_COMPCTRL) Interrupt on comparator output rising Position  */
#define AC_COMPCTRL_INTSEL_FALLING          (AC_COMPCTRL_INTSEL_FALLING_Val << AC_COMPCTRL_INTSEL_Pos)  /**< (AC_COMPCTRL) Interrupt on comparator output falling Position  */
#define AC_COMPCTRL_INTSEL_EOC              (AC_COMPCTRL_INTSEL_EOC_Val << AC_COMPCTRL_INTSEL_Pos)  /**< (AC_COMPCTRL) Interrupt on end of comparison (single-shot mode only) Position  */
#define AC_COMPCTRL_RUNSTDBY_Pos            6                                              /**< (AC_COMPCTRL) Run in Standby Position */
#define AC_COMPCTRL_RUNSTDBY_Msk            (_U_(0x1) << AC_COMPCTRL_RUNSTDBY_Pos)         /**< (AC_COMPCTRL) Run in Standby Mask */
#define AC_COMPCTRL_RUNSTDBY                AC_COMPCTRL_RUNSTDBY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_COMPCTRL_RUNSTDBY_Msk instead */
#define AC_COMPCTRL_MUXNEG_Pos              8                                              /**< (AC_COMPCTRL) Negative Input Mux Selection Position */
#define AC_COMPCTRL_MUXNEG_Msk              (_U_(0x7) << AC_COMPCTRL_MUXNEG_Pos)           /**< (AC_COMPCTRL) Negative Input Mux Selection Mask */
#define AC_COMPCTRL_MUXNEG(value)           (AC_COMPCTRL_MUXNEG_Msk & ((value) << AC_COMPCTRL_MUXNEG_Pos))
#define   AC_COMPCTRL_MUXNEG_PIN0_Val       _U_(0x0)                                       /**< (AC_COMPCTRL) I/O pin 0  */
#define   AC_COMPCTRL_MUXNEG_PIN1_Val       _U_(0x1)                                       /**< (AC_COMPCTRL) I/O pin 1  */
#define   AC_COMPCTRL_MUXNEG_PIN2_Val       _U_(0x2)                                       /**< (AC_COMPCTRL) I/O pin 2  */
#define   AC_COMPCTRL_MUXNEG_PIN3_Val       _U_(0x3)                                       /**< (AC_COMPCTRL) I/O pin 3  */
#define   AC_COMPCTRL_MUXNEG_GND_Val        _U_(0x4)                                       /**< (AC_COMPCTRL) Ground  */
#define   AC_COMPCTRL_MUXNEG_VSCALE_Val     _U_(0x5)                                       /**< (AC_COMPCTRL) VDD scaler  */
#define   AC_COMPCTRL_MUXNEG_BANDGAP_Val    _U_(0x6)                                       /**< (AC_COMPCTRL) Internal bandgap voltage  */
#define   AC_COMPCTRL_MUXNEG_OPAMP_Val      _U_(0x7)                                       /**< (AC_COMPCTRL) OPAMP output (on AC1)  */
#define   AC_COMPCTRL_MUXNEG_DAC_Val        _U_(0x7)                                       /**< (AC_COMPCTRL) DAC output (on AC0)  */
#define AC_COMPCTRL_MUXNEG_PIN0             (AC_COMPCTRL_MUXNEG_PIN0_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) I/O pin 0 Position  */
#define AC_COMPCTRL_MUXNEG_PIN1             (AC_COMPCTRL_MUXNEG_PIN1_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) I/O pin 1 Position  */
#define AC_COMPCTRL_MUXNEG_PIN2             (AC_COMPCTRL_MUXNEG_PIN2_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) I/O pin 2 Position  */
#define AC_COMPCTRL_MUXNEG_PIN3             (AC_COMPCTRL_MUXNEG_PIN3_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) I/O pin 3 Position  */
#define AC_COMPCTRL_MUXNEG_GND              (AC_COMPCTRL_MUXNEG_GND_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) Ground Position  */
#define AC_COMPCTRL_MUXNEG_VSCALE           (AC_COMPCTRL_MUXNEG_VSCALE_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) VDD scaler Position  */
#define AC_COMPCTRL_MUXNEG_BANDGAP          (AC_COMPCTRL_MUXNEG_BANDGAP_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) Internal bandgap voltage Position  */
#define AC_COMPCTRL_MUXNEG_OPAMP            (AC_COMPCTRL_MUXNEG_OPAMP_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) OPAMP output (on AC1) Position  */
#define AC_COMPCTRL_MUXNEG_DAC              (AC_COMPCTRL_MUXNEG_DAC_Val << AC_COMPCTRL_MUXNEG_Pos)  /**< (AC_COMPCTRL) DAC output (on AC0) Position  */
#define AC_COMPCTRL_MUXPOS_Pos              12                                             /**< (AC_COMPCTRL) Positive Input Mux Selection Position */
#define AC_COMPCTRL_MUXPOS_Msk              (_U_(0x7) << AC_COMPCTRL_MUXPOS_Pos)           /**< (AC_COMPCTRL) Positive Input Mux Selection Mask */
#define AC_COMPCTRL_MUXPOS(value)           (AC_COMPCTRL_MUXPOS_Msk & ((value) << AC_COMPCTRL_MUXPOS_Pos))
#define   AC_COMPCTRL_MUXPOS_PIN0_Val       _U_(0x0)                                       /**< (AC_COMPCTRL) I/O pin 0  */
#define   AC_COMPCTRL_MUXPOS_PIN1_Val       _U_(0x1)                                       /**< (AC_COMPCTRL) I/O pin 1  */
#define   AC_COMPCTRL_MUXPOS_PIN2_Val       _U_(0x2)                                       /**< (AC_COMPCTRL) I/O pin 2  */
#define   AC_COMPCTRL_MUXPOS_PIN3_Val       _U_(0x3)                                       /**< (AC_COMPCTRL) I/O pin 3  */
#define   AC_COMPCTRL_MUXPOS_VSCALE_Val     _U_(0x4)                                       /**< (AC_COMPCTRL) VDD Scaler  */
#define AC_COMPCTRL_MUXPOS_PIN0             (AC_COMPCTRL_MUXPOS_PIN0_Val << AC_COMPCTRL_MUXPOS_Pos)  /**< (AC_COMPCTRL) I/O pin 0 Position  */
#define AC_COMPCTRL_MUXPOS_PIN1             (AC_COMPCTRL_MUXPOS_PIN1_Val << AC_COMPCTRL_MUXPOS_Pos)  /**< (AC_COMPCTRL) I/O pin 1 Position  */
#define AC_COMPCTRL_MUXPOS_PIN2             (AC_COMPCTRL_MUXPOS_PIN2_Val << AC_COMPCTRL_MUXPOS_Pos)  /**< (AC_COMPCTRL) I/O pin 2 Position  */
#define AC_COMPCTRL_MUXPOS_PIN3             (AC_COMPCTRL_MUXPOS_PIN3_Val << AC_COMPCTRL_MUXPOS_Pos)  /**< (AC_COMPCTRL) I/O pin 3 Position  */
#define AC_COMPCTRL_MUXPOS_VSCALE           (AC_COMPCTRL_MUXPOS_VSCALE_Val << AC_COMPCTRL_MUXPOS_Pos)  /**< (AC_COMPCTRL) VDD Scaler Position  */
#define AC_COMPCTRL_SWAP_Pos                15                                             /**< (AC_COMPCTRL) Swap Inputs and Invert Position */
#define AC_COMPCTRL_SWAP_Msk                (_U_(0x1) << AC_COMPCTRL_SWAP_Pos)             /**< (AC_COMPCTRL) Swap Inputs and Invert Mask */
#define AC_COMPCTRL_SWAP                    AC_COMPCTRL_SWAP_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_COMPCTRL_SWAP_Msk instead */
#define AC_COMPCTRL_SPEED_Pos               16                                             /**< (AC_COMPCTRL) Speed Selection Position */
#define AC_COMPCTRL_SPEED_Msk               (_U_(0x3) << AC_COMPCTRL_SPEED_Pos)            /**< (AC_COMPCTRL) Speed Selection Mask */
#define AC_COMPCTRL_SPEED(value)            (AC_COMPCTRL_SPEED_Msk & ((value) << AC_COMPCTRL_SPEED_Pos))
#define   AC_COMPCTRL_SPEED_LOW_Val         _U_(0x0)                                       /**< (AC_COMPCTRL) Low speed  */
#define   AC_COMPCTRL_SPEED_MEDLOW_Val      _U_(0x1)                                       /**< (AC_COMPCTRL) Medium low speed  */
#define   AC_COMPCTRL_SPEED_MEDHIGH_Val     _U_(0x2)                                       /**< (AC_COMPCTRL) Medium high speed  */
#define   AC_COMPCTRL_SPEED_HIGH_Val        _U_(0x3)                                       /**< (AC_COMPCTRL) High speed  */
#define AC_COMPCTRL_SPEED_LOW               (AC_COMPCTRL_SPEED_LOW_Val << AC_COMPCTRL_SPEED_Pos)  /**< (AC_COMPCTRL) Low speed Position  */
#define AC_COMPCTRL_SPEED_MEDLOW            (AC_COMPCTRL_SPEED_MEDLOW_Val << AC_COMPCTRL_SPEED_Pos)  /**< (AC_COMPCTRL) Medium low speed Position  */
#define AC_COMPCTRL_SPEED_MEDHIGH           (AC_COMPCTRL_SPEED_MEDHIGH_Val << AC_COMPCTRL_SPEED_Pos)  /**< (AC_COMPCTRL) Medium high speed Position  */
#define AC_COMPCTRL_SPEED_HIGH              (AC_COMPCTRL_SPEED_HIGH_Val << AC_COMPCTRL_SPEED_Pos)  /**< (AC_COMPCTRL) High speed Position  */
#define AC_COMPCTRL_HYSTEN_Pos              19                                             /**< (AC_COMPCTRL) Hysteresis Enable Position */
#define AC_COMPCTRL_HYSTEN_Msk              (_U_(0x1) << AC_COMPCTRL_HYSTEN_Pos)           /**< (AC_COMPCTRL) Hysteresis Enable Mask */
#define AC_COMPCTRL_HYSTEN                  AC_COMPCTRL_HYSTEN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_COMPCTRL_HYSTEN_Msk instead */
#define AC_COMPCTRL_HYST_Pos                20                                             /**< (AC_COMPCTRL) Hysteresis Level Position */
#define AC_COMPCTRL_HYST_Msk                (_U_(0x3) << AC_COMPCTRL_HYST_Pos)             /**< (AC_COMPCTRL) Hysteresis Level Mask */
#define AC_COMPCTRL_HYST(value)             (AC_COMPCTRL_HYST_Msk & ((value) << AC_COMPCTRL_HYST_Pos))
#define   AC_COMPCTRL_HYST_HYST50_Val       _U_(0x0)                                       /**< (AC_COMPCTRL) 50mV  */
#define   AC_COMPCTRL_HYST_HYST70_Val       _U_(0x1)                                       /**< (AC_COMPCTRL) 70mV  */
#define   AC_COMPCTRL_HYST_HYST90_Val       _U_(0x2)                                       /**< (AC_COMPCTRL) 90mV  */
#define   AC_COMPCTRL_HYST_HYST110_Val      _U_(0x3)                                       /**< (AC_COMPCTRL) 110mV  */
#define AC_COMPCTRL_HYST_HYST50             (AC_COMPCTRL_HYST_HYST50_Val << AC_COMPCTRL_HYST_Pos)  /**< (AC_COMPCTRL) 50mV Position  */
#define AC_COMPCTRL_HYST_HYST70             (AC_COMPCTRL_HYST_HYST70_Val << AC_COMPCTRL_HYST_Pos)  /**< (AC_COMPCTRL) 70mV Position  */
#define AC_COMPCTRL_HYST_HYST90             (AC_COMPCTRL_HYST_HYST90_Val << AC_COMPCTRL_HYST_Pos)  /**< (AC_COMPCTRL) 90mV Position  */
#define AC_COMPCTRL_HYST_HYST110            (AC_COMPCTRL_HYST_HYST110_Val << AC_COMPCTRL_HYST_Pos)  /**< (AC_COMPCTRL) 110mV Position  */
#define AC_COMPCTRL_FLEN_Pos                24                                             /**< (AC_COMPCTRL) Filter Length Position */
#define AC_COMPCTRL_FLEN_Msk                (_U_(0x7) << AC_COMPCTRL_FLEN_Pos)             /**< (AC_COMPCTRL) Filter Length Mask */
#define AC_COMPCTRL_FLEN(value)             (AC_COMPCTRL_FLEN_Msk & ((value) << AC_COMPCTRL_FLEN_Pos))
#define   AC_COMPCTRL_FLEN_OFF_Val          _U_(0x0)                                       /**< (AC_COMPCTRL) No filtering  */
#define   AC_COMPCTRL_FLEN_MAJ3_Val         _U_(0x1)                                       /**< (AC_COMPCTRL) 3-bit majority function (2 of 3)  */
#define   AC_COMPCTRL_FLEN_MAJ5_Val         _U_(0x2)                                       /**< (AC_COMPCTRL) 5-bit majority function (3 of 5)  */
#define AC_COMPCTRL_FLEN_OFF                (AC_COMPCTRL_FLEN_OFF_Val << AC_COMPCTRL_FLEN_Pos)  /**< (AC_COMPCTRL) No filtering Position  */
#define AC_COMPCTRL_FLEN_MAJ3               (AC_COMPCTRL_FLEN_MAJ3_Val << AC_COMPCTRL_FLEN_Pos)  /**< (AC_COMPCTRL) 3-bit majority function (2 of 3) Position  */
#define AC_COMPCTRL_FLEN_MAJ5               (AC_COMPCTRL_FLEN_MAJ5_Val << AC_COMPCTRL_FLEN_Pos)  /**< (AC_COMPCTRL) 5-bit majority function (3 of 5) Position  */
#define AC_COMPCTRL_OUT_Pos                 28                                             /**< (AC_COMPCTRL) Output Position */
#define AC_COMPCTRL_OUT_Msk                 (_U_(0x3) << AC_COMPCTRL_OUT_Pos)              /**< (AC_COMPCTRL) Output Mask */
#define AC_COMPCTRL_OUT(value)              (AC_COMPCTRL_OUT_Msk & ((value) << AC_COMPCTRL_OUT_Pos))
#define   AC_COMPCTRL_OUT_OFF_Val           _U_(0x0)                                       /**< (AC_COMPCTRL) The output of COMPn is not routed to the COMPn I/O port  */
#define   AC_COMPCTRL_OUT_ASYNC_Val         _U_(0x1)                                       /**< (AC_COMPCTRL) The asynchronous output of COMPn is routed to the COMPn I/O port  */
#define   AC_COMPCTRL_OUT_SYNC_Val          _U_(0x2)                                       /**< (AC_COMPCTRL) The synchronous output (including filtering) of COMPn is routed to the COMPn I/O port  */
#define AC_COMPCTRL_OUT_OFF                 (AC_COMPCTRL_OUT_OFF_Val << AC_COMPCTRL_OUT_Pos)  /**< (AC_COMPCTRL) The output of COMPn is not routed to the COMPn I/O port Position  */
#define AC_COMPCTRL_OUT_ASYNC               (AC_COMPCTRL_OUT_ASYNC_Val << AC_COMPCTRL_OUT_Pos)  /**< (AC_COMPCTRL) The asynchronous output of COMPn is routed to the COMPn I/O port Position  */
#define AC_COMPCTRL_OUT_SYNC                (AC_COMPCTRL_OUT_SYNC_Val << AC_COMPCTRL_OUT_Pos)  /**< (AC_COMPCTRL) The synchronous output (including filtering) of COMPn is routed to the COMPn I/O port Position  */
#define AC_COMPCTRL_MASK                    _U_(0x373BF75E)                                /**< \deprecated (AC_COMPCTRL) Register MASK  (Use AC_COMPCTRL_Msk instead)  */
#define AC_COMPCTRL_Msk                     _U_(0x373BF75E)                                /**< (AC_COMPCTRL) Register Mask  */


/* -------- AC_SYNCBUSY : (AC Offset: 0x20) (R/ 32) Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy      */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Synchronization Busy              */
    uint32_t WINCTRL:1;                 /**< bit:      2  WINCTRL Synchronization Busy             */
    uint32_t COMPCTRL0:1;               /**< bit:      3  COMPCTRL 0 Synchronization Busy          */
    uint32_t COMPCTRL1:1;               /**< bit:      4  COMPCTRL 1 Synchronization Busy          */
    uint32_t :27;                       /**< bit:  5..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :3;                        /**< bit:   0..2  Reserved */
    uint32_t COMPCTRL:2;                /**< bit:   3..4  COMPCTRL x Synchronization Busy          */
    uint32_t :27;                       /**< bit:  5..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} AC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AC_SYNCBUSY_OFFSET                  (0x20)                                        /**<  (AC_SYNCBUSY) Synchronization Busy  Offset */
#define AC_SYNCBUSY_RESETVALUE              _U_(0x00)                                     /**<  (AC_SYNCBUSY) Synchronization Busy  Reset Value */

#define AC_SYNCBUSY_SWRST_Pos               0                                              /**< (AC_SYNCBUSY) Software Reset Synchronization Busy Position */
#define AC_SYNCBUSY_SWRST_Msk               (_U_(0x1) << AC_SYNCBUSY_SWRST_Pos)            /**< (AC_SYNCBUSY) Software Reset Synchronization Busy Mask */
#define AC_SYNCBUSY_SWRST                   AC_SYNCBUSY_SWRST_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_SYNCBUSY_SWRST_Msk instead */
#define AC_SYNCBUSY_ENABLE_Pos              1                                              /**< (AC_SYNCBUSY) Enable Synchronization Busy Position */
#define AC_SYNCBUSY_ENABLE_Msk              (_U_(0x1) << AC_SYNCBUSY_ENABLE_Pos)           /**< (AC_SYNCBUSY) Enable Synchronization Busy Mask */
#define AC_SYNCBUSY_ENABLE                  AC_SYNCBUSY_ENABLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_SYNCBUSY_ENABLE_Msk instead */
#define AC_SYNCBUSY_WINCTRL_Pos             2                                              /**< (AC_SYNCBUSY) WINCTRL Synchronization Busy Position */
#define AC_SYNCBUSY_WINCTRL_Msk             (_U_(0x1) << AC_SYNCBUSY_WINCTRL_Pos)          /**< (AC_SYNCBUSY) WINCTRL Synchronization Busy Mask */
#define AC_SYNCBUSY_WINCTRL                 AC_SYNCBUSY_WINCTRL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_SYNCBUSY_WINCTRL_Msk instead */
#define AC_SYNCBUSY_COMPCTRL0_Pos           3                                              /**< (AC_SYNCBUSY) COMPCTRL 0 Synchronization Busy Position */
#define AC_SYNCBUSY_COMPCTRL0_Msk           (_U_(0x1) << AC_SYNCBUSY_COMPCTRL0_Pos)        /**< (AC_SYNCBUSY) COMPCTRL 0 Synchronization Busy Mask */
#define AC_SYNCBUSY_COMPCTRL0               AC_SYNCBUSY_COMPCTRL0_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_SYNCBUSY_COMPCTRL0_Msk instead */
#define AC_SYNCBUSY_COMPCTRL1_Pos           4                                              /**< (AC_SYNCBUSY) COMPCTRL 1 Synchronization Busy Position */
#define AC_SYNCBUSY_COMPCTRL1_Msk           (_U_(0x1) << AC_SYNCBUSY_COMPCTRL1_Pos)        /**< (AC_SYNCBUSY) COMPCTRL 1 Synchronization Busy Mask */
#define AC_SYNCBUSY_COMPCTRL1               AC_SYNCBUSY_COMPCTRL1_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AC_SYNCBUSY_COMPCTRL1_Msk instead */
#define AC_SYNCBUSY_MASK                    _U_(0x1F)                                      /**< \deprecated (AC_SYNCBUSY) Register MASK  (Use AC_SYNCBUSY_Msk instead)  */
#define AC_SYNCBUSY_Msk                     _U_(0x1F)                                      /**< (AC_SYNCBUSY) Register Mask  */

#define AC_SYNCBUSY_COMPCTRL_Pos            3                                              /**< (AC_SYNCBUSY Position) COMPCTRL x Synchronization Busy */
#define AC_SYNCBUSY_COMPCTRL_Msk            (_U_(0x3) << AC_SYNCBUSY_COMPCTRL_Pos)         /**< (AC_SYNCBUSY Mask) COMPCTRL */
#define AC_SYNCBUSY_COMPCTRL(value)         (AC_SYNCBUSY_COMPCTRL_Msk & ((value) << AC_SYNCBUSY_COMPCTRL_Pos))  

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief AC hardware registers */
typedef struct {  /* Analog Comparators */
  __IO AC_CTRLA_Type                  CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __O  AC_CTRLB_Type                  CTRLB;          /**< Offset: 0x01 ( /W   8) Control B */
  __IO AC_EVCTRL_Type                 EVCTRL;         /**< Offset: 0x02 (R/W  16) Event Control */
  __IO AC_INTENCLR_Type               INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO AC_INTENSET_Type               INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO AC_INTFLAG_Type                INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  AC_STATUSA_Type                STATUSA;        /**< Offset: 0x07 (R/    8) Status A */
  __I  AC_STATUSB_Type                STATUSB;        /**< Offset: 0x08 (R/    8) Status B */
  __IO AC_DBGCTRL_Type                DBGCTRL;        /**< Offset: 0x09 (R/W   8) Debug Control */
  __IO AC_WINCTRL_Type                WINCTRL;        /**< Offset: 0x0A (R/W   8) Window Control */
  __I  uint8_t                        Reserved1[1];
  __IO AC_SCALER_Type                 SCALER[2];      /**< Offset: 0x0C (R/W   8) Scaler n */
  __I  uint8_t                        Reserved2[2];
  __IO AC_COMPCTRL_Type               COMPCTRL[2];    /**< Offset: 0x10 (R/W  32) Comparator Control n */
  __I  uint8_t                        Reserved3[8];
  __I  AC_SYNCBUSY_Type               SYNCBUSY;       /**< Offset: 0x20 (R/   32) Synchronization Busy */
} Ac;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Analog Comparators */

#endif /* _SAML10_AC_COMPONENT_H_ */
