/**
 * \file
 *
 * \brief Component description for PORT
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
#ifndef _SAML10_PORT_COMPONENT_H_
#define _SAML10_PORT_COMPONENT_H_
#define _SAML10_PORT_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Port Module
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PORT */
/* ========================================================================== */

#define PORT_U2210                      /**< (PORT) Module ID */
#define REV_PORT 0x300                  /**< (PORT) Module revision */

/* -------- PORT_DIR : (PORT Offset: 0x00) (R/W 32) Data Direction -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DIR:32;                    /**< bit:  0..31  Port Data Direction                      */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_DIR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_DIR_OFFSET                     (0x00)                                        /**<  (PORT_DIR) Data Direction  Offset */
#define PORT_DIR_RESETVALUE                 _U_(0x00)                                     /**<  (PORT_DIR) Data Direction  Reset Value */

#define PORT_DIR_DIR_Pos                    0                                              /**< (PORT_DIR) Port Data Direction Position */
#define PORT_DIR_DIR_Msk                    (_U_(0xFFFFFFFF) << PORT_DIR_DIR_Pos)          /**< (PORT_DIR) Port Data Direction Mask */
#define PORT_DIR_DIR(value)                 (PORT_DIR_DIR_Msk & ((value) << PORT_DIR_DIR_Pos))
#define PORT_DIR_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_DIR) Register MASK  (Use PORT_DIR_Msk instead)  */
#define PORT_DIR_Msk                        _U_(0xFFFFFFFF)                                /**< (PORT_DIR) Register Mask  */


/* -------- PORT_DIRCLR : (PORT Offset: 0x04) (R/W 32) Data Direction Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DIRCLR:32;                 /**< bit:  0..31  Port Data Direction Clear                */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_DIRCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_DIRCLR_OFFSET                  (0x04)                                        /**<  (PORT_DIRCLR) Data Direction Clear  Offset */
#define PORT_DIRCLR_RESETVALUE              _U_(0x00)                                     /**<  (PORT_DIRCLR) Data Direction Clear  Reset Value */

#define PORT_DIRCLR_DIRCLR_Pos              0                                              /**< (PORT_DIRCLR) Port Data Direction Clear Position */
#define PORT_DIRCLR_DIRCLR_Msk              (_U_(0xFFFFFFFF) << PORT_DIRCLR_DIRCLR_Pos)    /**< (PORT_DIRCLR) Port Data Direction Clear Mask */
#define PORT_DIRCLR_DIRCLR(value)           (PORT_DIRCLR_DIRCLR_Msk & ((value) << PORT_DIRCLR_DIRCLR_Pos))
#define PORT_DIRCLR_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_DIRCLR) Register MASK  (Use PORT_DIRCLR_Msk instead)  */
#define PORT_DIRCLR_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_DIRCLR) Register Mask  */


/* -------- PORT_DIRSET : (PORT Offset: 0x08) (R/W 32) Data Direction Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DIRSET:32;                 /**< bit:  0..31  Port Data Direction Set                  */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_DIRSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_DIRSET_OFFSET                  (0x08)                                        /**<  (PORT_DIRSET) Data Direction Set  Offset */
#define PORT_DIRSET_RESETVALUE              _U_(0x00)                                     /**<  (PORT_DIRSET) Data Direction Set  Reset Value */

#define PORT_DIRSET_DIRSET_Pos              0                                              /**< (PORT_DIRSET) Port Data Direction Set Position */
#define PORT_DIRSET_DIRSET_Msk              (_U_(0xFFFFFFFF) << PORT_DIRSET_DIRSET_Pos)    /**< (PORT_DIRSET) Port Data Direction Set Mask */
#define PORT_DIRSET_DIRSET(value)           (PORT_DIRSET_DIRSET_Msk & ((value) << PORT_DIRSET_DIRSET_Pos))
#define PORT_DIRSET_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_DIRSET) Register MASK  (Use PORT_DIRSET_Msk instead)  */
#define PORT_DIRSET_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_DIRSET) Register Mask  */


/* -------- PORT_DIRTGL : (PORT Offset: 0x0c) (R/W 32) Data Direction Toggle -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DIRTGL:32;                 /**< bit:  0..31  Port Data Direction Toggle               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_DIRTGL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_DIRTGL_OFFSET                  (0x0C)                                        /**<  (PORT_DIRTGL) Data Direction Toggle  Offset */
#define PORT_DIRTGL_RESETVALUE              _U_(0x00)                                     /**<  (PORT_DIRTGL) Data Direction Toggle  Reset Value */

#define PORT_DIRTGL_DIRTGL_Pos              0                                              /**< (PORT_DIRTGL) Port Data Direction Toggle Position */
#define PORT_DIRTGL_DIRTGL_Msk              (_U_(0xFFFFFFFF) << PORT_DIRTGL_DIRTGL_Pos)    /**< (PORT_DIRTGL) Port Data Direction Toggle Mask */
#define PORT_DIRTGL_DIRTGL(value)           (PORT_DIRTGL_DIRTGL_Msk & ((value) << PORT_DIRTGL_DIRTGL_Pos))
#define PORT_DIRTGL_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_DIRTGL) Register MASK  (Use PORT_DIRTGL_Msk instead)  */
#define PORT_DIRTGL_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_DIRTGL) Register Mask  */


/* -------- PORT_OUT : (PORT Offset: 0x10) (R/W 32) Data Output Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t OUT:32;                    /**< bit:  0..31  PORT Data Output Value                   */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_OUT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_OUT_OFFSET                     (0x10)                                        /**<  (PORT_OUT) Data Output Value  Offset */
#define PORT_OUT_RESETVALUE                 _U_(0x00)                                     /**<  (PORT_OUT) Data Output Value  Reset Value */

#define PORT_OUT_OUT_Pos                    0                                              /**< (PORT_OUT) PORT Data Output Value Position */
#define PORT_OUT_OUT_Msk                    (_U_(0xFFFFFFFF) << PORT_OUT_OUT_Pos)          /**< (PORT_OUT) PORT Data Output Value Mask */
#define PORT_OUT_OUT(value)                 (PORT_OUT_OUT_Msk & ((value) << PORT_OUT_OUT_Pos))
#define PORT_OUT_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_OUT) Register MASK  (Use PORT_OUT_Msk instead)  */
#define PORT_OUT_Msk                        _U_(0xFFFFFFFF)                                /**< (PORT_OUT) Register Mask  */


/* -------- PORT_OUTCLR : (PORT Offset: 0x14) (R/W 32) Data Output Value Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t OUTCLR:32;                 /**< bit:  0..31  PORT Data Output Value Clear             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_OUTCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_OUTCLR_OFFSET                  (0x14)                                        /**<  (PORT_OUTCLR) Data Output Value Clear  Offset */
#define PORT_OUTCLR_RESETVALUE              _U_(0x00)                                     /**<  (PORT_OUTCLR) Data Output Value Clear  Reset Value */

#define PORT_OUTCLR_OUTCLR_Pos              0                                              /**< (PORT_OUTCLR) PORT Data Output Value Clear Position */
#define PORT_OUTCLR_OUTCLR_Msk              (_U_(0xFFFFFFFF) << PORT_OUTCLR_OUTCLR_Pos)    /**< (PORT_OUTCLR) PORT Data Output Value Clear Mask */
#define PORT_OUTCLR_OUTCLR(value)           (PORT_OUTCLR_OUTCLR_Msk & ((value) << PORT_OUTCLR_OUTCLR_Pos))
#define PORT_OUTCLR_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_OUTCLR) Register MASK  (Use PORT_OUTCLR_Msk instead)  */
#define PORT_OUTCLR_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_OUTCLR) Register Mask  */


/* -------- PORT_OUTSET : (PORT Offset: 0x18) (R/W 32) Data Output Value Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t OUTSET:32;                 /**< bit:  0..31  PORT Data Output Value Set               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_OUTSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_OUTSET_OFFSET                  (0x18)                                        /**<  (PORT_OUTSET) Data Output Value Set  Offset */
#define PORT_OUTSET_RESETVALUE              _U_(0x00)                                     /**<  (PORT_OUTSET) Data Output Value Set  Reset Value */

#define PORT_OUTSET_OUTSET_Pos              0                                              /**< (PORT_OUTSET) PORT Data Output Value Set Position */
#define PORT_OUTSET_OUTSET_Msk              (_U_(0xFFFFFFFF) << PORT_OUTSET_OUTSET_Pos)    /**< (PORT_OUTSET) PORT Data Output Value Set Mask */
#define PORT_OUTSET_OUTSET(value)           (PORT_OUTSET_OUTSET_Msk & ((value) << PORT_OUTSET_OUTSET_Pos))
#define PORT_OUTSET_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_OUTSET) Register MASK  (Use PORT_OUTSET_Msk instead)  */
#define PORT_OUTSET_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_OUTSET) Register Mask  */


/* -------- PORT_OUTTGL : (PORT Offset: 0x1c) (R/W 32) Data Output Value Toggle -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t OUTTGL:32;                 /**< bit:  0..31  PORT Data Output Value Toggle            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_OUTTGL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_OUTTGL_OFFSET                  (0x1C)                                        /**<  (PORT_OUTTGL) Data Output Value Toggle  Offset */
#define PORT_OUTTGL_RESETVALUE              _U_(0x00)                                     /**<  (PORT_OUTTGL) Data Output Value Toggle  Reset Value */

#define PORT_OUTTGL_OUTTGL_Pos              0                                              /**< (PORT_OUTTGL) PORT Data Output Value Toggle Position */
#define PORT_OUTTGL_OUTTGL_Msk              (_U_(0xFFFFFFFF) << PORT_OUTTGL_OUTTGL_Pos)    /**< (PORT_OUTTGL) PORT Data Output Value Toggle Mask */
#define PORT_OUTTGL_OUTTGL(value)           (PORT_OUTTGL_OUTTGL_Msk & ((value) << PORT_OUTTGL_OUTTGL_Pos))
#define PORT_OUTTGL_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_OUTTGL) Register MASK  (Use PORT_OUTTGL_Msk instead)  */
#define PORT_OUTTGL_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_OUTTGL) Register Mask  */


/* -------- PORT_IN : (PORT Offset: 0x20) (R/ 32) Data Input Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IN:32;                     /**< bit:  0..31  PORT Data Input Value                    */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_IN_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_IN_OFFSET                      (0x20)                                        /**<  (PORT_IN) Data Input Value  Offset */
#define PORT_IN_RESETVALUE                  _U_(0x00)                                     /**<  (PORT_IN) Data Input Value  Reset Value */

#define PORT_IN_IN_Pos                      0                                              /**< (PORT_IN) PORT Data Input Value Position */
#define PORT_IN_IN_Msk                      (_U_(0xFFFFFFFF) << PORT_IN_IN_Pos)            /**< (PORT_IN) PORT Data Input Value Mask */
#define PORT_IN_IN(value)                   (PORT_IN_IN_Msk & ((value) << PORT_IN_IN_Pos))
#define PORT_IN_MASK                        _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_IN) Register MASK  (Use PORT_IN_Msk instead)  */
#define PORT_IN_Msk                         _U_(0xFFFFFFFF)                                /**< (PORT_IN) Register Mask  */


/* -------- PORT_CTRL : (PORT Offset: 0x24) (R/W 32) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SAMPLING:32;               /**< bit:  0..31  Input Sampling Mode                      */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_CTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_CTRL_OFFSET                    (0x24)                                        /**<  (PORT_CTRL) Control  Offset */
#define PORT_CTRL_RESETVALUE                _U_(0x00)                                     /**<  (PORT_CTRL) Control  Reset Value */

#define PORT_CTRL_SAMPLING_Pos              0                                              /**< (PORT_CTRL) Input Sampling Mode Position */
#define PORT_CTRL_SAMPLING_Msk              (_U_(0xFFFFFFFF) << PORT_CTRL_SAMPLING_Pos)    /**< (PORT_CTRL) Input Sampling Mode Mask */
#define PORT_CTRL_SAMPLING(value)           (PORT_CTRL_SAMPLING_Msk & ((value) << PORT_CTRL_SAMPLING_Pos))
#define PORT_CTRL_MASK                      _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_CTRL) Register MASK  (Use PORT_CTRL_Msk instead)  */
#define PORT_CTRL_Msk                       _U_(0xFFFFFFFF)                                /**< (PORT_CTRL) Register Mask  */


/* -------- PORT_WRCONFIG : (PORT Offset: 0x28) (/W 32) Write Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PINMASK:16;                /**< bit:  0..15  Pin Mask for Multiple Pin Configuration  */
    uint32_t PMUXEN:1;                  /**< bit:     16  Peripheral Multiplexer Enable            */
    uint32_t INEN:1;                    /**< bit:     17  Input Enable                             */
    uint32_t PULLEN:1;                  /**< bit:     18  Pull Enable                              */
    uint32_t :3;                        /**< bit: 19..21  Reserved */
    uint32_t DRVSTR:1;                  /**< bit:     22  Output Driver Strength Selection         */
    uint32_t :1;                        /**< bit:     23  Reserved */
    uint32_t PMUX:4;                    /**< bit: 24..27  Peripheral Multiplexing                  */
    uint32_t WRPMUX:1;                  /**< bit:     28  Write PMUX                               */
    uint32_t :1;                        /**< bit:     29  Reserved */
    uint32_t WRPINCFG:1;                /**< bit:     30  Write PINCFG                             */
    uint32_t HWSEL:1;                   /**< bit:     31  Half-Word Select                         */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_WRCONFIG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_WRCONFIG_OFFSET                (0x28)                                        /**<  (PORT_WRCONFIG) Write Configuration  Offset */
#define PORT_WRCONFIG_RESETVALUE            _U_(0x00)                                     /**<  (PORT_WRCONFIG) Write Configuration  Reset Value */

#define PORT_WRCONFIG_PINMASK_Pos           0                                              /**< (PORT_WRCONFIG) Pin Mask for Multiple Pin Configuration Position */
#define PORT_WRCONFIG_PINMASK_Msk           (_U_(0xFFFF) << PORT_WRCONFIG_PINMASK_Pos)     /**< (PORT_WRCONFIG) Pin Mask for Multiple Pin Configuration Mask */
#define PORT_WRCONFIG_PINMASK(value)        (PORT_WRCONFIG_PINMASK_Msk & ((value) << PORT_WRCONFIG_PINMASK_Pos))
#define PORT_WRCONFIG_PMUXEN_Pos            16                                             /**< (PORT_WRCONFIG) Peripheral Multiplexer Enable Position */
#define PORT_WRCONFIG_PMUXEN_Msk            (_U_(0x1) << PORT_WRCONFIG_PMUXEN_Pos)         /**< (PORT_WRCONFIG) Peripheral Multiplexer Enable Mask */
#define PORT_WRCONFIG_PMUXEN                PORT_WRCONFIG_PMUXEN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_PMUXEN_Msk instead */
#define PORT_WRCONFIG_INEN_Pos              17                                             /**< (PORT_WRCONFIG) Input Enable Position */
#define PORT_WRCONFIG_INEN_Msk              (_U_(0x1) << PORT_WRCONFIG_INEN_Pos)           /**< (PORT_WRCONFIG) Input Enable Mask */
#define PORT_WRCONFIG_INEN                  PORT_WRCONFIG_INEN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_INEN_Msk instead */
#define PORT_WRCONFIG_PULLEN_Pos            18                                             /**< (PORT_WRCONFIG) Pull Enable Position */
#define PORT_WRCONFIG_PULLEN_Msk            (_U_(0x1) << PORT_WRCONFIG_PULLEN_Pos)         /**< (PORT_WRCONFIG) Pull Enable Mask */
#define PORT_WRCONFIG_PULLEN                PORT_WRCONFIG_PULLEN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_PULLEN_Msk instead */
#define PORT_WRCONFIG_DRVSTR_Pos            22                                             /**< (PORT_WRCONFIG) Output Driver Strength Selection Position */
#define PORT_WRCONFIG_DRVSTR_Msk            (_U_(0x1) << PORT_WRCONFIG_DRVSTR_Pos)         /**< (PORT_WRCONFIG) Output Driver Strength Selection Mask */
#define PORT_WRCONFIG_DRVSTR                PORT_WRCONFIG_DRVSTR_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_DRVSTR_Msk instead */
#define PORT_WRCONFIG_PMUX_Pos              24                                             /**< (PORT_WRCONFIG) Peripheral Multiplexing Position */
#define PORT_WRCONFIG_PMUX_Msk              (_U_(0xF) << PORT_WRCONFIG_PMUX_Pos)           /**< (PORT_WRCONFIG) Peripheral Multiplexing Mask */
#define PORT_WRCONFIG_PMUX(value)           (PORT_WRCONFIG_PMUX_Msk & ((value) << PORT_WRCONFIG_PMUX_Pos))
#define PORT_WRCONFIG_WRPMUX_Pos            28                                             /**< (PORT_WRCONFIG) Write PMUX Position */
#define PORT_WRCONFIG_WRPMUX_Msk            (_U_(0x1) << PORT_WRCONFIG_WRPMUX_Pos)         /**< (PORT_WRCONFIG) Write PMUX Mask */
#define PORT_WRCONFIG_WRPMUX                PORT_WRCONFIG_WRPMUX_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_WRPMUX_Msk instead */
#define PORT_WRCONFIG_WRPINCFG_Pos          30                                             /**< (PORT_WRCONFIG) Write PINCFG Position */
#define PORT_WRCONFIG_WRPINCFG_Msk          (_U_(0x1) << PORT_WRCONFIG_WRPINCFG_Pos)       /**< (PORT_WRCONFIG) Write PINCFG Mask */
#define PORT_WRCONFIG_WRPINCFG              PORT_WRCONFIG_WRPINCFG_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_WRPINCFG_Msk instead */
#define PORT_WRCONFIG_HWSEL_Pos             31                                             /**< (PORT_WRCONFIG) Half-Word Select Position */
#define PORT_WRCONFIG_HWSEL_Msk             (_U_(0x1) << PORT_WRCONFIG_HWSEL_Pos)          /**< (PORT_WRCONFIG) Half-Word Select Mask */
#define PORT_WRCONFIG_HWSEL                 PORT_WRCONFIG_HWSEL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_WRCONFIG_HWSEL_Msk instead */
#define PORT_WRCONFIG_Msk                   _U_(0xDF47FFFF)                                /**< (PORT_WRCONFIG) Register Mask  */


/* -------- PORT_EVCTRL : (PORT Offset: 0x2c) (R/W 32) Event Input Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PID0:5;                    /**< bit:   0..4  PORT Event Pin Identifier 0              */
    uint32_t EVACT0:2;                  /**< bit:   5..6  PORT Event Action 0                      */
    uint32_t PORTEI0:1;                 /**< bit:      7  PORT Event Input Enable 0                */
    uint32_t PID1:5;                    /**< bit:  8..12  PORT Event Pin Identifier 1              */
    uint32_t EVACT1:2;                  /**< bit: 13..14  PORT Event Action 1                      */
    uint32_t PORTEI1:1;                 /**< bit:     15  PORT Event Input Enable 1                */
    uint32_t PID2:5;                    /**< bit: 16..20  PORT Event Pin Identifier 2              */
    uint32_t EVACT2:2;                  /**< bit: 21..22  PORT Event Action 2                      */
    uint32_t PORTEI2:1;                 /**< bit:     23  PORT Event Input Enable 2                */
    uint32_t PID3:5;                    /**< bit: 24..28  PORT Event Pin Identifier 3              */
    uint32_t EVACT3:2;                  /**< bit: 29..30  PORT Event Action 3                      */
    uint32_t PORTEI3:1;                 /**< bit:     31  PORT Event Input Enable 3                */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_EVCTRL_OFFSET                  (0x2C)                                        /**<  (PORT_EVCTRL) Event Input Control  Offset */
#define PORT_EVCTRL_RESETVALUE              _U_(0x00)                                     /**<  (PORT_EVCTRL) Event Input Control  Reset Value */

#define PORT_EVCTRL_PID0_Pos                0                                              /**< (PORT_EVCTRL) PORT Event Pin Identifier 0 Position */
#define PORT_EVCTRL_PID0_Msk                (_U_(0x1F) << PORT_EVCTRL_PID0_Pos)            /**< (PORT_EVCTRL) PORT Event Pin Identifier 0 Mask */
#define PORT_EVCTRL_PID0(value)             (PORT_EVCTRL_PID0_Msk & ((value) << PORT_EVCTRL_PID0_Pos))
#define PORT_EVCTRL_EVACT0_Pos              5                                              /**< (PORT_EVCTRL) PORT Event Action 0 Position */
#define PORT_EVCTRL_EVACT0_Msk              (_U_(0x3) << PORT_EVCTRL_EVACT0_Pos)           /**< (PORT_EVCTRL) PORT Event Action 0 Mask */
#define PORT_EVCTRL_EVACT0(value)           (PORT_EVCTRL_EVACT0_Msk & ((value) << PORT_EVCTRL_EVACT0_Pos))
#define   PORT_EVCTRL_EVACT0_OUT_Val        _U_(0x0)                                       /**< (PORT_EVCTRL) Event output to pin  */
#define   PORT_EVCTRL_EVACT0_SET_Val        _U_(0x1)                                       /**< (PORT_EVCTRL) Set output register of pin on event  */
#define   PORT_EVCTRL_EVACT0_CLR_Val        _U_(0x2)                                       /**< (PORT_EVCTRL) Clear output register of pin on event  */
#define   PORT_EVCTRL_EVACT0_TGL_Val        _U_(0x3)                                       /**< (PORT_EVCTRL) Toggle output register of pin on event  */
#define PORT_EVCTRL_EVACT0_OUT              (PORT_EVCTRL_EVACT0_OUT_Val << PORT_EVCTRL_EVACT0_Pos)  /**< (PORT_EVCTRL) Event output to pin Position  */
#define PORT_EVCTRL_EVACT0_SET              (PORT_EVCTRL_EVACT0_SET_Val << PORT_EVCTRL_EVACT0_Pos)  /**< (PORT_EVCTRL) Set output register of pin on event Position  */
#define PORT_EVCTRL_EVACT0_CLR              (PORT_EVCTRL_EVACT0_CLR_Val << PORT_EVCTRL_EVACT0_Pos)  /**< (PORT_EVCTRL) Clear output register of pin on event Position  */
#define PORT_EVCTRL_EVACT0_TGL              (PORT_EVCTRL_EVACT0_TGL_Val << PORT_EVCTRL_EVACT0_Pos)  /**< (PORT_EVCTRL) Toggle output register of pin on event Position  */
#define PORT_EVCTRL_PORTEI0_Pos             7                                              /**< (PORT_EVCTRL) PORT Event Input Enable 0 Position */
#define PORT_EVCTRL_PORTEI0_Msk             (_U_(0x1) << PORT_EVCTRL_PORTEI0_Pos)          /**< (PORT_EVCTRL) PORT Event Input Enable 0 Mask */
#define PORT_EVCTRL_PORTEI0                 PORT_EVCTRL_PORTEI0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_EVCTRL_PORTEI0_Msk instead */
#define PORT_EVCTRL_PID1_Pos                8                                              /**< (PORT_EVCTRL) PORT Event Pin Identifier 1 Position */
#define PORT_EVCTRL_PID1_Msk                (_U_(0x1F) << PORT_EVCTRL_PID1_Pos)            /**< (PORT_EVCTRL) PORT Event Pin Identifier 1 Mask */
#define PORT_EVCTRL_PID1(value)             (PORT_EVCTRL_PID1_Msk & ((value) << PORT_EVCTRL_PID1_Pos))
#define PORT_EVCTRL_EVACT1_Pos              13                                             /**< (PORT_EVCTRL) PORT Event Action 1 Position */
#define PORT_EVCTRL_EVACT1_Msk              (_U_(0x3) << PORT_EVCTRL_EVACT1_Pos)           /**< (PORT_EVCTRL) PORT Event Action 1 Mask */
#define PORT_EVCTRL_EVACT1(value)           (PORT_EVCTRL_EVACT1_Msk & ((value) << PORT_EVCTRL_EVACT1_Pos))
#define PORT_EVCTRL_PORTEI1_Pos             15                                             /**< (PORT_EVCTRL) PORT Event Input Enable 1 Position */
#define PORT_EVCTRL_PORTEI1_Msk             (_U_(0x1) << PORT_EVCTRL_PORTEI1_Pos)          /**< (PORT_EVCTRL) PORT Event Input Enable 1 Mask */
#define PORT_EVCTRL_PORTEI1                 PORT_EVCTRL_PORTEI1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_EVCTRL_PORTEI1_Msk instead */
#define PORT_EVCTRL_PID2_Pos                16                                             /**< (PORT_EVCTRL) PORT Event Pin Identifier 2 Position */
#define PORT_EVCTRL_PID2_Msk                (_U_(0x1F) << PORT_EVCTRL_PID2_Pos)            /**< (PORT_EVCTRL) PORT Event Pin Identifier 2 Mask */
#define PORT_EVCTRL_PID2(value)             (PORT_EVCTRL_PID2_Msk & ((value) << PORT_EVCTRL_PID2_Pos))
#define PORT_EVCTRL_EVACT2_Pos              21                                             /**< (PORT_EVCTRL) PORT Event Action 2 Position */
#define PORT_EVCTRL_EVACT2_Msk              (_U_(0x3) << PORT_EVCTRL_EVACT2_Pos)           /**< (PORT_EVCTRL) PORT Event Action 2 Mask */
#define PORT_EVCTRL_EVACT2(value)           (PORT_EVCTRL_EVACT2_Msk & ((value) << PORT_EVCTRL_EVACT2_Pos))
#define PORT_EVCTRL_PORTEI2_Pos             23                                             /**< (PORT_EVCTRL) PORT Event Input Enable 2 Position */
#define PORT_EVCTRL_PORTEI2_Msk             (_U_(0x1) << PORT_EVCTRL_PORTEI2_Pos)          /**< (PORT_EVCTRL) PORT Event Input Enable 2 Mask */
#define PORT_EVCTRL_PORTEI2                 PORT_EVCTRL_PORTEI2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_EVCTRL_PORTEI2_Msk instead */
#define PORT_EVCTRL_PID3_Pos                24                                             /**< (PORT_EVCTRL) PORT Event Pin Identifier 3 Position */
#define PORT_EVCTRL_PID3_Msk                (_U_(0x1F) << PORT_EVCTRL_PID3_Pos)            /**< (PORT_EVCTRL) PORT Event Pin Identifier 3 Mask */
#define PORT_EVCTRL_PID3(value)             (PORT_EVCTRL_PID3_Msk & ((value) << PORT_EVCTRL_PID3_Pos))
#define PORT_EVCTRL_EVACT3_Pos              29                                             /**< (PORT_EVCTRL) PORT Event Action 3 Position */
#define PORT_EVCTRL_EVACT3_Msk              (_U_(0x3) << PORT_EVCTRL_EVACT3_Pos)           /**< (PORT_EVCTRL) PORT Event Action 3 Mask */
#define PORT_EVCTRL_EVACT3(value)           (PORT_EVCTRL_EVACT3_Msk & ((value) << PORT_EVCTRL_EVACT3_Pos))
#define PORT_EVCTRL_PORTEI3_Pos             31                                             /**< (PORT_EVCTRL) PORT Event Input Enable 3 Position */
#define PORT_EVCTRL_PORTEI3_Msk             (_U_(0x1) << PORT_EVCTRL_PORTEI3_Pos)          /**< (PORT_EVCTRL) PORT Event Input Enable 3 Mask */
#define PORT_EVCTRL_PORTEI3                 PORT_EVCTRL_PORTEI3_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_EVCTRL_PORTEI3_Msk instead */
#define PORT_EVCTRL_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_EVCTRL) Register MASK  (Use PORT_EVCTRL_Msk instead)  */
#define PORT_EVCTRL_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_EVCTRL) Register Mask  */


/* -------- PORT_PMUX : (PORT Offset: 0x30) (R/W 8) Peripheral Multiplexing -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PMUXE:4;                   /**< bit:   0..3  Peripheral Multiplexing for Even-Numbered Pin */
    uint8_t  PMUXO:4;                   /**< bit:   4..7  Peripheral Multiplexing for Odd-Numbered Pin */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PORT_PMUX_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_PMUX_OFFSET                    (0x30)                                        /**<  (PORT_PMUX) Peripheral Multiplexing  Offset */
#define PORT_PMUX_RESETVALUE                _U_(0x00)                                     /**<  (PORT_PMUX) Peripheral Multiplexing  Reset Value */

#define PORT_PMUX_PMUXE_Pos                 0                                              /**< (PORT_PMUX) Peripheral Multiplexing for Even-Numbered Pin Position */
#define PORT_PMUX_PMUXE_Msk                 (_U_(0xF) << PORT_PMUX_PMUXE_Pos)              /**< (PORT_PMUX) Peripheral Multiplexing for Even-Numbered Pin Mask */
#define PORT_PMUX_PMUXE(value)              (PORT_PMUX_PMUXE_Msk & ((value) << PORT_PMUX_PMUXE_Pos))
#define PORT_PMUX_PMUXO_Pos                 4                                              /**< (PORT_PMUX) Peripheral Multiplexing for Odd-Numbered Pin Position */
#define PORT_PMUX_PMUXO_Msk                 (_U_(0xF) << PORT_PMUX_PMUXO_Pos)              /**< (PORT_PMUX) Peripheral Multiplexing for Odd-Numbered Pin Mask */
#define PORT_PMUX_PMUXO(value)              (PORT_PMUX_PMUXO_Msk & ((value) << PORT_PMUX_PMUXO_Pos))
#define PORT_PMUX_MASK                      _U_(0xFF)                                      /**< \deprecated (PORT_PMUX) Register MASK  (Use PORT_PMUX_Msk instead)  */
#define PORT_PMUX_Msk                       _U_(0xFF)                                      /**< (PORT_PMUX) Register Mask  */


/* -------- PORT_PINCFG : (PORT Offset: 0x40) (R/W 8) Pin Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PMUXEN:1;                  /**< bit:      0  Peripheral Multiplexer Enable            */
    uint8_t  INEN:1;                    /**< bit:      1  Input Enable                             */
    uint8_t  PULLEN:1;                  /**< bit:      2  Pull Enable                              */
    uint8_t  :3;                        /**< bit:   3..5  Reserved */
    uint8_t  DRVSTR:1;                  /**< bit:      6  Output Driver Strength Selection         */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PORT_PINCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_PINCFG_OFFSET                  (0x40)                                        /**<  (PORT_PINCFG) Pin Configuration  Offset */
#define PORT_PINCFG_RESETVALUE              _U_(0x00)                                     /**<  (PORT_PINCFG) Pin Configuration  Reset Value */

#define PORT_PINCFG_PMUXEN_Pos              0                                              /**< (PORT_PINCFG) Peripheral Multiplexer Enable Position */
#define PORT_PINCFG_PMUXEN_Msk              (_U_(0x1) << PORT_PINCFG_PMUXEN_Pos)           /**< (PORT_PINCFG) Peripheral Multiplexer Enable Mask */
#define PORT_PINCFG_PMUXEN                  PORT_PINCFG_PMUXEN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_PINCFG_PMUXEN_Msk instead */
#define PORT_PINCFG_INEN_Pos                1                                              /**< (PORT_PINCFG) Input Enable Position */
#define PORT_PINCFG_INEN_Msk                (_U_(0x1) << PORT_PINCFG_INEN_Pos)             /**< (PORT_PINCFG) Input Enable Mask */
#define PORT_PINCFG_INEN                    PORT_PINCFG_INEN_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_PINCFG_INEN_Msk instead */
#define PORT_PINCFG_PULLEN_Pos              2                                              /**< (PORT_PINCFG) Pull Enable Position */
#define PORT_PINCFG_PULLEN_Msk              (_U_(0x1) << PORT_PINCFG_PULLEN_Pos)           /**< (PORT_PINCFG) Pull Enable Mask */
#define PORT_PINCFG_PULLEN                  PORT_PINCFG_PULLEN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_PINCFG_PULLEN_Msk instead */
#define PORT_PINCFG_DRVSTR_Pos              6                                              /**< (PORT_PINCFG) Output Driver Strength Selection Position */
#define PORT_PINCFG_DRVSTR_Msk              (_U_(0x1) << PORT_PINCFG_DRVSTR_Pos)           /**< (PORT_PINCFG) Output Driver Strength Selection Mask */
#define PORT_PINCFG_DRVSTR                  PORT_PINCFG_DRVSTR_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_PINCFG_DRVSTR_Msk instead */
#define PORT_PINCFG_MASK                    _U_(0x47)                                      /**< \deprecated (PORT_PINCFG) Register MASK  (Use PORT_PINCFG_Msk instead)  */
#define PORT_PINCFG_Msk                     _U_(0x47)                                      /**< (PORT_PINCFG) Register Mask  */


/* -------- PORT_INTENCLR : (PORT Offset: 0x60) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t NSCHK:1;                   /**< bit:      0  Non-Secure Check Interrupt Enable        */
    uint32_t :31;                       /**< bit:  1..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_INTENCLR_OFFSET                (0x60)                                        /**<  (PORT_INTENCLR) Interrupt Enable Clear  Offset */
#define PORT_INTENCLR_RESETVALUE            _U_(0x00)                                     /**<  (PORT_INTENCLR) Interrupt Enable Clear  Reset Value */

#define PORT_INTENCLR_NSCHK_Pos             0                                              /**< (PORT_INTENCLR) Non-Secure Check Interrupt Enable Position */
#define PORT_INTENCLR_NSCHK_Msk             (_U_(0x1) << PORT_INTENCLR_NSCHK_Pos)          /**< (PORT_INTENCLR) Non-Secure Check Interrupt Enable Mask */
#define PORT_INTENCLR_NSCHK                 PORT_INTENCLR_NSCHK_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_INTENCLR_NSCHK_Msk instead */
#define PORT_INTENCLR_MASK                  _U_(0x01)                                      /**< \deprecated (PORT_INTENCLR) Register MASK  (Use PORT_INTENCLR_Msk instead)  */
#define PORT_INTENCLR_Msk                   _U_(0x01)                                      /**< (PORT_INTENCLR) Register Mask  */


/* -------- PORT_INTENSET : (PORT Offset: 0x64) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t NSCHK:1;                   /**< bit:      0  Non-Secure Check Interrupt Enable        */
    uint32_t :31;                       /**< bit:  1..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_INTENSET_OFFSET                (0x64)                                        /**<  (PORT_INTENSET) Interrupt Enable Set  Offset */
#define PORT_INTENSET_RESETVALUE            _U_(0x00)                                     /**<  (PORT_INTENSET) Interrupt Enable Set  Reset Value */

#define PORT_INTENSET_NSCHK_Pos             0                                              /**< (PORT_INTENSET) Non-Secure Check Interrupt Enable Position */
#define PORT_INTENSET_NSCHK_Msk             (_U_(0x1) << PORT_INTENSET_NSCHK_Pos)          /**< (PORT_INTENSET) Non-Secure Check Interrupt Enable Mask */
#define PORT_INTENSET_NSCHK                 PORT_INTENSET_NSCHK_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_INTENSET_NSCHK_Msk instead */
#define PORT_INTENSET_MASK                  _U_(0x01)                                      /**< \deprecated (PORT_INTENSET) Register MASK  (Use PORT_INTENSET_Msk instead)  */
#define PORT_INTENSET_Msk                   _U_(0x01)                                      /**< (PORT_INTENSET) Register Mask  */


/* -------- PORT_INTFLAG : (PORT Offset: 0x68) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t NSCHK:1;                   /**< bit:      0  Non-Secure Check                         */
    __I uint32_t :31;                       /**< bit:  1..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_INTFLAG_OFFSET                 (0x68)                                        /**<  (PORT_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define PORT_INTFLAG_RESETVALUE             _U_(0x00)                                     /**<  (PORT_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define PORT_INTFLAG_NSCHK_Pos              0                                              /**< (PORT_INTFLAG) Non-Secure Check Position */
#define PORT_INTFLAG_NSCHK_Msk              (_U_(0x1) << PORT_INTFLAG_NSCHK_Pos)           /**< (PORT_INTFLAG) Non-Secure Check Mask */
#define PORT_INTFLAG_NSCHK                  PORT_INTFLAG_NSCHK_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PORT_INTFLAG_NSCHK_Msk instead */
#define PORT_INTFLAG_MASK                   _U_(0x01)                                      /**< \deprecated (PORT_INTFLAG) Register MASK  (Use PORT_INTFLAG_Msk instead)  */
#define PORT_INTFLAG_Msk                    _U_(0x01)                                      /**< (PORT_INTFLAG) Register Mask  */


/* -------- PORT_NONSEC : (PORT Offset: 0x6c) (R/W 32) Security Attribution -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t NONSEC:32;                 /**< bit:  0..31  Port Security Attribution                */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_NONSEC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_NONSEC_OFFSET                  (0x6C)                                        /**<  (PORT_NONSEC) Security Attribution  Offset */
#define PORT_NONSEC_RESETVALUE              _U_(0x00)                                     /**<  (PORT_NONSEC) Security Attribution  Reset Value */

#define PORT_NONSEC_NONSEC_Pos              0                                              /**< (PORT_NONSEC) Port Security Attribution Position */
#define PORT_NONSEC_NONSEC_Msk              (_U_(0xFFFFFFFF) << PORT_NONSEC_NONSEC_Pos)    /**< (PORT_NONSEC) Port Security Attribution Mask */
#define PORT_NONSEC_NONSEC(value)           (PORT_NONSEC_NONSEC_Msk & ((value) << PORT_NONSEC_NONSEC_Pos))
#define PORT_NONSEC_MASK                    _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_NONSEC) Register MASK  (Use PORT_NONSEC_Msk instead)  */
#define PORT_NONSEC_Msk                     _U_(0xFFFFFFFF)                                /**< (PORT_NONSEC) Register Mask  */


/* -------- PORT_NSCHK : (PORT Offset: 0x70) (R/W 32) Security Attribution Check -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t NSCHK:32;                  /**< bit:  0..31  Port Security Attribution Check          */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PORT_NSCHK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PORT_NSCHK_OFFSET                   (0x70)                                        /**<  (PORT_NSCHK) Security Attribution Check  Offset */
#define PORT_NSCHK_RESETVALUE               _U_(0x00)                                     /**<  (PORT_NSCHK) Security Attribution Check  Reset Value */

#define PORT_NSCHK_NSCHK_Pos                0                                              /**< (PORT_NSCHK) Port Security Attribution Check Position */
#define PORT_NSCHK_NSCHK_Msk                (_U_(0xFFFFFFFF) << PORT_NSCHK_NSCHK_Pos)      /**< (PORT_NSCHK) Port Security Attribution Check Mask */
#define PORT_NSCHK_NSCHK(value)             (PORT_NSCHK_NSCHK_Msk & ((value) << PORT_NSCHK_NSCHK_Pos))
#define PORT_NSCHK_MASK                     _U_(0xFFFFFFFF)                                /**< \deprecated (PORT_NSCHK) Register MASK  (Use PORT_NSCHK_Msk instead)  */
#define PORT_NSCHK_Msk                      _U_(0xFFFFFFFF)                                /**< (PORT_NSCHK) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief GROUP hardware registers */
typedef struct {  
  __IO PORT_DIR_Type                  DIR;            /**< Offset: 0x00 (R/W  32) Data Direction */
  __IO PORT_DIRCLR_Type               DIRCLR;         /**< Offset: 0x04 (R/W  32) Data Direction Clear */
  __IO PORT_DIRSET_Type               DIRSET;         /**< Offset: 0x08 (R/W  32) Data Direction Set */
  __IO PORT_DIRTGL_Type               DIRTGL;         /**< Offset: 0x0C (R/W  32) Data Direction Toggle */
  __IO PORT_OUT_Type                  OUT;            /**< Offset: 0x10 (R/W  32) Data Output Value */
  __IO PORT_OUTCLR_Type               OUTCLR;         /**< Offset: 0x14 (R/W  32) Data Output Value Clear */
  __IO PORT_OUTSET_Type               OUTSET;         /**< Offset: 0x18 (R/W  32) Data Output Value Set */
  __IO PORT_OUTTGL_Type               OUTTGL;         /**< Offset: 0x1C (R/W  32) Data Output Value Toggle */
  __I  PORT_IN_Type                   IN;             /**< Offset: 0x20 (R/   32) Data Input Value */
  __IO PORT_CTRL_Type                 CTRL;           /**< Offset: 0x24 (R/W  32) Control */
  __O  PORT_WRCONFIG_Type             WRCONFIG;       /**< Offset: 0x28 ( /W  32) Write Configuration */
  __IO PORT_EVCTRL_Type               EVCTRL;         /**< Offset: 0x2C (R/W  32) Event Input Control */
  __IO PORT_PMUX_Type                 PMUX[16];       /**< Offset: 0x30 (R/W   8) Peripheral Multiplexing */
  __IO PORT_PINCFG_Type               PINCFG[32];     /**< Offset: 0x40 (R/W   8) Pin Configuration */
  __IO PORT_INTENCLR_Type             INTENCLR;       /**< Offset: 0x60 (R/W  32) Interrupt Enable Clear */
  __IO PORT_INTENSET_Type             INTENSET;       /**< Offset: 0x64 (R/W  32) Interrupt Enable Set */
  __IO PORT_INTFLAG_Type              INTFLAG;        /**< Offset: 0x68 (R/W  32) Interrupt Flag Status and Clear */
  __IO PORT_NONSEC_Type               NONSEC;         /**< Offset: 0x6C (R/W  32) Security Attribution */
  __IO PORT_NSCHK_Type                NSCHK;          /**< Offset: 0x70 (R/W  32) Security Attribution Check */
  __I  uint8_t                        Reserved1[12];
} PortGroup;

/** \brief PORT hardware registers */
typedef struct {  /* Port Module */
       PortGroup                      Group[1];       /**< Offset: 0x00  */
} Port;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Port Module */

#endif /* _SAML10_PORT_COMPONENT_H_ */
