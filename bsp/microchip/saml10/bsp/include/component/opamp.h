/**
 * \file
 *
 * \brief Component description for OPAMP
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
#ifndef _SAML10_OPAMP_COMPONENT_H_
#define _SAML10_OPAMP_COMPONENT_H_
#define _SAML10_OPAMP_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Operational Amplifier
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR OPAMP */
/* ========================================================================== */

#define OPAMP_U2237                      /**< (OPAMP) Module ID */
#define REV_OPAMP 0x200                  /**< (OPAMP) Module revision */

/* -------- OPAMP_CTRLA : (OPAMP Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :5;                        /**< bit:   2..6  Reserved */
    uint8_t  LPMUX:1;                   /**< bit:      7  Low-Power Mux                            */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OPAMP_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OPAMP_CTRLA_OFFSET                  (0x00)                                        /**<  (OPAMP_CTRLA) Control A  Offset */
#define OPAMP_CTRLA_RESETVALUE              _U_(0x00)                                     /**<  (OPAMP_CTRLA) Control A  Reset Value */

#define OPAMP_CTRLA_SWRST_Pos               0                                              /**< (OPAMP_CTRLA) Software Reset Position */
#define OPAMP_CTRLA_SWRST_Msk               (_U_(0x1) << OPAMP_CTRLA_SWRST_Pos)            /**< (OPAMP_CTRLA) Software Reset Mask */
#define OPAMP_CTRLA_SWRST                   OPAMP_CTRLA_SWRST_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_CTRLA_SWRST_Msk instead */
#define OPAMP_CTRLA_ENABLE_Pos              1                                              /**< (OPAMP_CTRLA) Enable Position */
#define OPAMP_CTRLA_ENABLE_Msk              (_U_(0x1) << OPAMP_CTRLA_ENABLE_Pos)           /**< (OPAMP_CTRLA) Enable Mask */
#define OPAMP_CTRLA_ENABLE                  OPAMP_CTRLA_ENABLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_CTRLA_ENABLE_Msk instead */
#define OPAMP_CTRLA_LPMUX_Pos               7                                              /**< (OPAMP_CTRLA) Low-Power Mux Position */
#define OPAMP_CTRLA_LPMUX_Msk               (_U_(0x1) << OPAMP_CTRLA_LPMUX_Pos)            /**< (OPAMP_CTRLA) Low-Power Mux Mask */
#define OPAMP_CTRLA_LPMUX                   OPAMP_CTRLA_LPMUX_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_CTRLA_LPMUX_Msk instead */
#define OPAMP_CTRLA_MASK                    _U_(0x83)                                      /**< \deprecated (OPAMP_CTRLA) Register MASK  (Use OPAMP_CTRLA_Msk instead)  */
#define OPAMP_CTRLA_Msk                     _U_(0x83)                                      /**< (OPAMP_CTRLA) Register Mask  */


/* -------- OPAMP_STATUS : (OPAMP Offset: 0x02) (R/ 8) Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  READY0:1;                  /**< bit:      0  OPAMP 0 Ready                            */
    uint8_t  READY1:1;                  /**< bit:      1  OPAMP 1 Ready                            */
    uint8_t  READY2:1;                  /**< bit:      2  OPAMP 2 Ready                            */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  READY:3;                   /**< bit:   0..2  OPAMP 2 Ready                            */
    uint8_t  :5;                        /**< bit:   3..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} OPAMP_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OPAMP_STATUS_OFFSET                 (0x02)                                        /**<  (OPAMP_STATUS) Status  Offset */
#define OPAMP_STATUS_RESETVALUE             _U_(0x00)                                     /**<  (OPAMP_STATUS) Status  Reset Value */

#define OPAMP_STATUS_READY0_Pos             0                                              /**< (OPAMP_STATUS) OPAMP 0 Ready Position */
#define OPAMP_STATUS_READY0_Msk             (_U_(0x1) << OPAMP_STATUS_READY0_Pos)          /**< (OPAMP_STATUS) OPAMP 0 Ready Mask */
#define OPAMP_STATUS_READY0                 OPAMP_STATUS_READY0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_STATUS_READY0_Msk instead */
#define OPAMP_STATUS_READY1_Pos             1                                              /**< (OPAMP_STATUS) OPAMP 1 Ready Position */
#define OPAMP_STATUS_READY1_Msk             (_U_(0x1) << OPAMP_STATUS_READY1_Pos)          /**< (OPAMP_STATUS) OPAMP 1 Ready Mask */
#define OPAMP_STATUS_READY1                 OPAMP_STATUS_READY1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_STATUS_READY1_Msk instead */
#define OPAMP_STATUS_READY2_Pos             2                                              /**< (OPAMP_STATUS) OPAMP 2 Ready Position */
#define OPAMP_STATUS_READY2_Msk             (_U_(0x1) << OPAMP_STATUS_READY2_Pos)          /**< (OPAMP_STATUS) OPAMP 2 Ready Mask */
#define OPAMP_STATUS_READY2                 OPAMP_STATUS_READY2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_STATUS_READY2_Msk instead */
#define OPAMP_STATUS_MASK                   _U_(0x07)                                      /**< \deprecated (OPAMP_STATUS) Register MASK  (Use OPAMP_STATUS_Msk instead)  */
#define OPAMP_STATUS_Msk                    _U_(0x07)                                      /**< (OPAMP_STATUS) Register Mask  */

#define OPAMP_STATUS_READY_Pos              0                                              /**< (OPAMP_STATUS Position) OPAMP 2 Ready */
#define OPAMP_STATUS_READY_Msk              (_U_(0x7) << OPAMP_STATUS_READY_Pos)           /**< (OPAMP_STATUS Mask) READY */
#define OPAMP_STATUS_READY(value)           (OPAMP_STATUS_READY_Msk & ((value) << OPAMP_STATUS_READY_Pos))  

/* -------- OPAMP_OPAMPCTRL : (OPAMP Offset: 0x04) (R/W 32) OPAMP n Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Operational Amplifier Enable             */
    uint32_t ANAOUT:1;                  /**< bit:      2  Analog Output                            */
    uint32_t BIAS:2;                    /**< bit:   3..4  Bias Selection                           */
    uint32_t RES2VCC:1;                 /**< bit:      5  Resistor ladder To VCC                   */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint32_t ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
    uint32_t RES2OUT:1;                 /**< bit:      8  Resistor ladder To Output                */
    uint32_t RES1EN:1;                  /**< bit:      9  Resistor 1 Enable                        */
    uint32_t RES1MUX:3;                 /**< bit: 10..12  Resistor 1 Mux                           */
    uint32_t POTMUX:3;                  /**< bit: 13..15  Potentiometer Selection                  */
    uint32_t MUXPOS:4;                  /**< bit: 16..19  Positive Input Mux Selection             */
    uint32_t MUXNEG:4;                  /**< bit: 20..23  Negative Input Mux Selection             */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} OPAMP_OPAMPCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OPAMP_OPAMPCTRL_OFFSET              (0x04)                                        /**<  (OPAMP_OPAMPCTRL) OPAMP n Control  Offset */
#define OPAMP_OPAMPCTRL_RESETVALUE          _U_(0x00)                                     /**<  (OPAMP_OPAMPCTRL) OPAMP n Control  Reset Value */

#define OPAMP_OPAMPCTRL_ENABLE_Pos          1                                              /**< (OPAMP_OPAMPCTRL) Operational Amplifier Enable Position */
#define OPAMP_OPAMPCTRL_ENABLE_Msk          (_U_(0x1) << OPAMP_OPAMPCTRL_ENABLE_Pos)       /**< (OPAMP_OPAMPCTRL) Operational Amplifier Enable Mask */
#define OPAMP_OPAMPCTRL_ENABLE              OPAMP_OPAMPCTRL_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_ENABLE_Msk instead */
#define OPAMP_OPAMPCTRL_ANAOUT_Pos          2                                              /**< (OPAMP_OPAMPCTRL) Analog Output Position */
#define OPAMP_OPAMPCTRL_ANAOUT_Msk          (_U_(0x1) << OPAMP_OPAMPCTRL_ANAOUT_Pos)       /**< (OPAMP_OPAMPCTRL) Analog Output Mask */
#define OPAMP_OPAMPCTRL_ANAOUT              OPAMP_OPAMPCTRL_ANAOUT_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_ANAOUT_Msk instead */
#define OPAMP_OPAMPCTRL_BIAS_Pos            3                                              /**< (OPAMP_OPAMPCTRL) Bias Selection Position */
#define OPAMP_OPAMPCTRL_BIAS_Msk            (_U_(0x3) << OPAMP_OPAMPCTRL_BIAS_Pos)         /**< (OPAMP_OPAMPCTRL) Bias Selection Mask */
#define OPAMP_OPAMPCTRL_BIAS(value)         (OPAMP_OPAMPCTRL_BIAS_Msk & ((value) << OPAMP_OPAMPCTRL_BIAS_Pos))
#define OPAMP_OPAMPCTRL_RES2VCC_Pos         5                                              /**< (OPAMP_OPAMPCTRL) Resistor ladder To VCC Position */
#define OPAMP_OPAMPCTRL_RES2VCC_Msk         (_U_(0x1) << OPAMP_OPAMPCTRL_RES2VCC_Pos)      /**< (OPAMP_OPAMPCTRL) Resistor ladder To VCC Mask */
#define OPAMP_OPAMPCTRL_RES2VCC             OPAMP_OPAMPCTRL_RES2VCC_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_RES2VCC_Msk instead */
#define OPAMP_OPAMPCTRL_RUNSTDBY_Pos        6                                              /**< (OPAMP_OPAMPCTRL) Run in Standby Position */
#define OPAMP_OPAMPCTRL_RUNSTDBY_Msk        (_U_(0x1) << OPAMP_OPAMPCTRL_RUNSTDBY_Pos)     /**< (OPAMP_OPAMPCTRL) Run in Standby Mask */
#define OPAMP_OPAMPCTRL_RUNSTDBY            OPAMP_OPAMPCTRL_RUNSTDBY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_RUNSTDBY_Msk instead */
#define OPAMP_OPAMPCTRL_ONDEMAND_Pos        7                                              /**< (OPAMP_OPAMPCTRL) On Demand Control Position */
#define OPAMP_OPAMPCTRL_ONDEMAND_Msk        (_U_(0x1) << OPAMP_OPAMPCTRL_ONDEMAND_Pos)     /**< (OPAMP_OPAMPCTRL) On Demand Control Mask */
#define OPAMP_OPAMPCTRL_ONDEMAND            OPAMP_OPAMPCTRL_ONDEMAND_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_ONDEMAND_Msk instead */
#define OPAMP_OPAMPCTRL_RES2OUT_Pos         8                                              /**< (OPAMP_OPAMPCTRL) Resistor ladder To Output Position */
#define OPAMP_OPAMPCTRL_RES2OUT_Msk         (_U_(0x1) << OPAMP_OPAMPCTRL_RES2OUT_Pos)      /**< (OPAMP_OPAMPCTRL) Resistor ladder To Output Mask */
#define OPAMP_OPAMPCTRL_RES2OUT             OPAMP_OPAMPCTRL_RES2OUT_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_RES2OUT_Msk instead */
#define OPAMP_OPAMPCTRL_RES1EN_Pos          9                                              /**< (OPAMP_OPAMPCTRL) Resistor 1 Enable Position */
#define OPAMP_OPAMPCTRL_RES1EN_Msk          (_U_(0x1) << OPAMP_OPAMPCTRL_RES1EN_Pos)       /**< (OPAMP_OPAMPCTRL) Resistor 1 Enable Mask */
#define OPAMP_OPAMPCTRL_RES1EN              OPAMP_OPAMPCTRL_RES1EN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_OPAMPCTRL_RES1EN_Msk instead */
#define OPAMP_OPAMPCTRL_RES1MUX_Pos         10                                             /**< (OPAMP_OPAMPCTRL) Resistor 1 Mux Position */
#define OPAMP_OPAMPCTRL_RES1MUX_Msk         (_U_(0x7) << OPAMP_OPAMPCTRL_RES1MUX_Pos)      /**< (OPAMP_OPAMPCTRL) Resistor 1 Mux Mask */
#define OPAMP_OPAMPCTRL_RES1MUX(value)      (OPAMP_OPAMPCTRL_RES1MUX_Msk & ((value) << OPAMP_OPAMPCTRL_RES1MUX_Pos))
#define OPAMP_OPAMPCTRL_POTMUX_Pos          13                                             /**< (OPAMP_OPAMPCTRL) Potentiometer Selection Position */
#define OPAMP_OPAMPCTRL_POTMUX_Msk          (_U_(0x7) << OPAMP_OPAMPCTRL_POTMUX_Pos)       /**< (OPAMP_OPAMPCTRL) Potentiometer Selection Mask */
#define OPAMP_OPAMPCTRL_POTMUX(value)       (OPAMP_OPAMPCTRL_POTMUX_Msk & ((value) << OPAMP_OPAMPCTRL_POTMUX_Pos))
#define OPAMP_OPAMPCTRL_MUXPOS_Pos          16                                             /**< (OPAMP_OPAMPCTRL) Positive Input Mux Selection Position */
#define OPAMP_OPAMPCTRL_MUXPOS_Msk          (_U_(0xF) << OPAMP_OPAMPCTRL_MUXPOS_Pos)       /**< (OPAMP_OPAMPCTRL) Positive Input Mux Selection Mask */
#define OPAMP_OPAMPCTRL_MUXPOS(value)       (OPAMP_OPAMPCTRL_MUXPOS_Msk & ((value) << OPAMP_OPAMPCTRL_MUXPOS_Pos))
#define OPAMP_OPAMPCTRL_MUXNEG_Pos          20                                             /**< (OPAMP_OPAMPCTRL) Negative Input Mux Selection Position */
#define OPAMP_OPAMPCTRL_MUXNEG_Msk          (_U_(0xF) << OPAMP_OPAMPCTRL_MUXNEG_Pos)       /**< (OPAMP_OPAMPCTRL) Negative Input Mux Selection Mask */
#define OPAMP_OPAMPCTRL_MUXNEG(value)       (OPAMP_OPAMPCTRL_MUXNEG_Msk & ((value) << OPAMP_OPAMPCTRL_MUXNEG_Pos))
#define OPAMP_OPAMPCTRL_MASK                _U_(0xFFFFFE)                                  /**< \deprecated (OPAMP_OPAMPCTRL) Register MASK  (Use OPAMP_OPAMPCTRL_Msk instead)  */
#define OPAMP_OPAMPCTRL_Msk                 _U_(0xFFFFFE)                                  /**< (OPAMP_OPAMPCTRL) Register Mask  */


/* -------- OPAMP_RESCTRL : (OPAMP Offset: 0x10) (R/W 8) Resister Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RES2OUT:1;                 /**< bit:      0  Resistor ladder To Output                */
    uint8_t  RES1EN:1;                  /**< bit:      1  Resistor 1 Enable                        */
    uint8_t  RES1MUX:1;                 /**< bit:      2  Resistor 1 Mux                           */
    uint8_t  POTMUX:3;                  /**< bit:   3..5  Potentiometer Selection                  */
    uint8_t  REFBUFLEVEL:2;             /**< bit:   6..7  Reference output voltage level select    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} OPAMP_RESCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define OPAMP_RESCTRL_OFFSET                (0x10)                                        /**<  (OPAMP_RESCTRL) Resister Control  Offset */
#define OPAMP_RESCTRL_RESETVALUE            _U_(0x00)                                     /**<  (OPAMP_RESCTRL) Resister Control  Reset Value */

#define OPAMP_RESCTRL_RES2OUT_Pos           0                                              /**< (OPAMP_RESCTRL) Resistor ladder To Output Position */
#define OPAMP_RESCTRL_RES2OUT_Msk           (_U_(0x1) << OPAMP_RESCTRL_RES2OUT_Pos)        /**< (OPAMP_RESCTRL) Resistor ladder To Output Mask */
#define OPAMP_RESCTRL_RES2OUT               OPAMP_RESCTRL_RES2OUT_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_RESCTRL_RES2OUT_Msk instead */
#define OPAMP_RESCTRL_RES1EN_Pos            1                                              /**< (OPAMP_RESCTRL) Resistor 1 Enable Position */
#define OPAMP_RESCTRL_RES1EN_Msk            (_U_(0x1) << OPAMP_RESCTRL_RES1EN_Pos)         /**< (OPAMP_RESCTRL) Resistor 1 Enable Mask */
#define OPAMP_RESCTRL_RES1EN                OPAMP_RESCTRL_RES1EN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_RESCTRL_RES1EN_Msk instead */
#define OPAMP_RESCTRL_RES1MUX_Pos           2                                              /**< (OPAMP_RESCTRL) Resistor 1 Mux Position */
#define OPAMP_RESCTRL_RES1MUX_Msk           (_U_(0x1) << OPAMP_RESCTRL_RES1MUX_Pos)        /**< (OPAMP_RESCTRL) Resistor 1 Mux Mask */
#define OPAMP_RESCTRL_RES1MUX               OPAMP_RESCTRL_RES1MUX_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use OPAMP_RESCTRL_RES1MUX_Msk instead */
#define OPAMP_RESCTRL_POTMUX_Pos            3                                              /**< (OPAMP_RESCTRL) Potentiometer Selection Position */
#define OPAMP_RESCTRL_POTMUX_Msk            (_U_(0x7) << OPAMP_RESCTRL_POTMUX_Pos)         /**< (OPAMP_RESCTRL) Potentiometer Selection Mask */
#define OPAMP_RESCTRL_POTMUX(value)         (OPAMP_RESCTRL_POTMUX_Msk & ((value) << OPAMP_RESCTRL_POTMUX_Pos))
#define OPAMP_RESCTRL_REFBUFLEVEL_Pos       6                                              /**< (OPAMP_RESCTRL) Reference output voltage level select Position */
#define OPAMP_RESCTRL_REFBUFLEVEL_Msk       (_U_(0x3) << OPAMP_RESCTRL_REFBUFLEVEL_Pos)    /**< (OPAMP_RESCTRL) Reference output voltage level select Mask */
#define OPAMP_RESCTRL_REFBUFLEVEL(value)    (OPAMP_RESCTRL_REFBUFLEVEL_Msk & ((value) << OPAMP_RESCTRL_REFBUFLEVEL_Pos))
#define OPAMP_RESCTRL_MASK                  _U_(0xFF)                                      /**< \deprecated (OPAMP_RESCTRL) Register MASK  (Use OPAMP_RESCTRL_Msk instead)  */
#define OPAMP_RESCTRL_Msk                   _U_(0xFF)                                      /**< (OPAMP_RESCTRL) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief OPAMP hardware registers */
typedef struct {  /* Operational Amplifier */
  __IO OPAMP_CTRLA_Type               CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __I  uint8_t                        Reserved1[1];
  __I  OPAMP_STATUS_Type              STATUS;         /**< Offset: 0x02 (R/    8) Status */
  __I  uint8_t                        Reserved2[1];
  __IO OPAMP_OPAMPCTRL_Type           OPAMPCTRL[3];   /**< Offset: 0x04 (R/W  32) OPAMP n Control */
  __IO OPAMP_RESCTRL_Type             RESCTRL;        /**< Offset: 0x10 (R/W   8) Resister Control */
} Opamp;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Operational Amplifier */

#endif /* _SAML10_OPAMP_COMPONENT_H_ */
