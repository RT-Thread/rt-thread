/**
 * \file
 *
 * \brief Component description for DAC
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
#ifndef _SAML10_DAC_COMPONENT_H_
#define _SAML10_DAC_COMPONENT_H_
#define _SAML10_DAC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Digital Analog Converter
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR DAC */
/* ========================================================================== */

#define DAC_U2214                      /**< (DAC) Module ID */
#define REV_DAC 0x210                  /**< (DAC) Module revision */

/* -------- DAC_CTRLA : (DAC Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :4;                        /**< bit:   2..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_CTRLA_OFFSET                    (0x00)                                        /**<  (DAC_CTRLA) Control A  Offset */
#define DAC_CTRLA_RESETVALUE                _U_(0x00)                                     /**<  (DAC_CTRLA) Control A  Reset Value */

#define DAC_CTRLA_SWRST_Pos                 0                                              /**< (DAC_CTRLA) Software Reset Position */
#define DAC_CTRLA_SWRST_Msk                 (_U_(0x1) << DAC_CTRLA_SWRST_Pos)              /**< (DAC_CTRLA) Software Reset Mask */
#define DAC_CTRLA_SWRST                     DAC_CTRLA_SWRST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLA_SWRST_Msk instead */
#define DAC_CTRLA_ENABLE_Pos                1                                              /**< (DAC_CTRLA) Enable Position */
#define DAC_CTRLA_ENABLE_Msk                (_U_(0x1) << DAC_CTRLA_ENABLE_Pos)             /**< (DAC_CTRLA) Enable Mask */
#define DAC_CTRLA_ENABLE                    DAC_CTRLA_ENABLE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLA_ENABLE_Msk instead */
#define DAC_CTRLA_RUNSTDBY_Pos              6                                              /**< (DAC_CTRLA) Run in Standby Position */
#define DAC_CTRLA_RUNSTDBY_Msk              (_U_(0x1) << DAC_CTRLA_RUNSTDBY_Pos)           /**< (DAC_CTRLA) Run in Standby Mask */
#define DAC_CTRLA_RUNSTDBY                  DAC_CTRLA_RUNSTDBY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLA_RUNSTDBY_Msk instead */
#define DAC_CTRLA_MASK                      _U_(0x43)                                      /**< \deprecated (DAC_CTRLA) Register MASK  (Use DAC_CTRLA_Msk instead)  */
#define DAC_CTRLA_Msk                       _U_(0x43)                                      /**< (DAC_CTRLA) Register Mask  */


/* -------- DAC_CTRLB : (DAC Offset: 0x01) (R/W 8) Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  EOEN:1;                    /**< bit:      0  External Output Enable                   */
    uint8_t  IOEN:1;                    /**< bit:      1  Internal Output Enable                   */
    uint8_t  LEFTADJ:1;                 /**< bit:      2  Left Adjusted Data                       */
    uint8_t  VPD:1;                     /**< bit:      3  Voltage Pump Disable                     */
    uint8_t  :1;                        /**< bit:      4  Reserved */
    uint8_t  DITHER:1;                  /**< bit:      5  Dither Enable                            */
    uint8_t  REFSEL:2;                  /**< bit:   6..7  Reference Selection                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_CTRLB_OFFSET                    (0x01)                                        /**<  (DAC_CTRLB) Control B  Offset */
#define DAC_CTRLB_RESETVALUE                _U_(0x00)                                     /**<  (DAC_CTRLB) Control B  Reset Value */

#define DAC_CTRLB_EOEN_Pos                  0                                              /**< (DAC_CTRLB) External Output Enable Position */
#define DAC_CTRLB_EOEN_Msk                  (_U_(0x1) << DAC_CTRLB_EOEN_Pos)               /**< (DAC_CTRLB) External Output Enable Mask */
#define DAC_CTRLB_EOEN                      DAC_CTRLB_EOEN_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLB_EOEN_Msk instead */
#define DAC_CTRLB_IOEN_Pos                  1                                              /**< (DAC_CTRLB) Internal Output Enable Position */
#define DAC_CTRLB_IOEN_Msk                  (_U_(0x1) << DAC_CTRLB_IOEN_Pos)               /**< (DAC_CTRLB) Internal Output Enable Mask */
#define DAC_CTRLB_IOEN                      DAC_CTRLB_IOEN_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLB_IOEN_Msk instead */
#define DAC_CTRLB_LEFTADJ_Pos               2                                              /**< (DAC_CTRLB) Left Adjusted Data Position */
#define DAC_CTRLB_LEFTADJ_Msk               (_U_(0x1) << DAC_CTRLB_LEFTADJ_Pos)            /**< (DAC_CTRLB) Left Adjusted Data Mask */
#define DAC_CTRLB_LEFTADJ                   DAC_CTRLB_LEFTADJ_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLB_LEFTADJ_Msk instead */
#define DAC_CTRLB_VPD_Pos                   3                                              /**< (DAC_CTRLB) Voltage Pump Disable Position */
#define DAC_CTRLB_VPD_Msk                   (_U_(0x1) << DAC_CTRLB_VPD_Pos)                /**< (DAC_CTRLB) Voltage Pump Disable Mask */
#define DAC_CTRLB_VPD                       DAC_CTRLB_VPD_Msk                              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLB_VPD_Msk instead */
#define DAC_CTRLB_DITHER_Pos                5                                              /**< (DAC_CTRLB) Dither Enable Position */
#define DAC_CTRLB_DITHER_Msk                (_U_(0x1) << DAC_CTRLB_DITHER_Pos)             /**< (DAC_CTRLB) Dither Enable Mask */
#define DAC_CTRLB_DITHER                    DAC_CTRLB_DITHER_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_CTRLB_DITHER_Msk instead */
#define DAC_CTRLB_REFSEL_Pos                6                                              /**< (DAC_CTRLB) Reference Selection Position */
#define DAC_CTRLB_REFSEL_Msk                (_U_(0x3) << DAC_CTRLB_REFSEL_Pos)             /**< (DAC_CTRLB) Reference Selection Mask */
#define DAC_CTRLB_REFSEL(value)             (DAC_CTRLB_REFSEL_Msk & ((value) << DAC_CTRLB_REFSEL_Pos))
#define   DAC_CTRLB_REFSEL_INT1V_Val        _U_(0x0)                                       /**< (DAC_CTRLB) Internal 1.0V reference  */
#define   DAC_CTRLB_REFSEL_AVCC_Val         _U_(0x1)                                       /**< (DAC_CTRLB) AVCC  */
#define   DAC_CTRLB_REFSEL_VREFP_Val        _U_(0x2)                                       /**< (DAC_CTRLB) External reference  */
#define DAC_CTRLB_REFSEL_INT1V              (DAC_CTRLB_REFSEL_INT1V_Val << DAC_CTRLB_REFSEL_Pos)  /**< (DAC_CTRLB) Internal 1.0V reference Position  */
#define DAC_CTRLB_REFSEL_AVCC               (DAC_CTRLB_REFSEL_AVCC_Val << DAC_CTRLB_REFSEL_Pos)  /**< (DAC_CTRLB) AVCC Position  */
#define DAC_CTRLB_REFSEL_VREFP              (DAC_CTRLB_REFSEL_VREFP_Val << DAC_CTRLB_REFSEL_Pos)  /**< (DAC_CTRLB) External reference Position  */
#define DAC_CTRLB_MASK                      _U_(0xEF)                                      /**< \deprecated (DAC_CTRLB) Register MASK  (Use DAC_CTRLB_Msk instead)  */
#define DAC_CTRLB_Msk                       _U_(0xEF)                                      /**< (DAC_CTRLB) Register Mask  */


/* -------- DAC_EVCTRL : (DAC Offset: 0x02) (R/W 8) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  STARTEI:1;                 /**< bit:      0  Start Conversion Event Input             */
    uint8_t  EMPTYEO:1;                 /**< bit:      1  Data Buffer Empty Event Output           */
    uint8_t  INVEI:1;                   /**< bit:      2  Invert Event Input                       */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_EVCTRL_OFFSET                   (0x02)                                        /**<  (DAC_EVCTRL) Event Control  Offset */
#define DAC_EVCTRL_RESETVALUE               _U_(0x00)                                     /**<  (DAC_EVCTRL) Event Control  Reset Value */

#define DAC_EVCTRL_STARTEI_Pos              0                                              /**< (DAC_EVCTRL) Start Conversion Event Input Position */
#define DAC_EVCTRL_STARTEI_Msk              (_U_(0x1) << DAC_EVCTRL_STARTEI_Pos)           /**< (DAC_EVCTRL) Start Conversion Event Input Mask */
#define DAC_EVCTRL_STARTEI                  DAC_EVCTRL_STARTEI_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_EVCTRL_STARTEI_Msk instead */
#define DAC_EVCTRL_EMPTYEO_Pos              1                                              /**< (DAC_EVCTRL) Data Buffer Empty Event Output Position */
#define DAC_EVCTRL_EMPTYEO_Msk              (_U_(0x1) << DAC_EVCTRL_EMPTYEO_Pos)           /**< (DAC_EVCTRL) Data Buffer Empty Event Output Mask */
#define DAC_EVCTRL_EMPTYEO                  DAC_EVCTRL_EMPTYEO_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_EVCTRL_EMPTYEO_Msk instead */
#define DAC_EVCTRL_INVEI_Pos                2                                              /**< (DAC_EVCTRL) Invert Event Input Position */
#define DAC_EVCTRL_INVEI_Msk                (_U_(0x1) << DAC_EVCTRL_INVEI_Pos)             /**< (DAC_EVCTRL) Invert Event Input Mask */
#define DAC_EVCTRL_INVEI                    DAC_EVCTRL_INVEI_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_EVCTRL_INVEI_Msk instead */
#define DAC_EVCTRL_MASK                     _U_(0x07)                                      /**< \deprecated (DAC_EVCTRL) Register MASK  (Use DAC_EVCTRL_Msk instead)  */
#define DAC_EVCTRL_Msk                      _U_(0x07)                                      /**< (DAC_EVCTRL) Register Mask  */


/* -------- DAC_INTENCLR : (DAC Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  UNDERRUN:1;                /**< bit:      0  Underrun Interrupt Enable                */
    uint8_t  EMPTY:1;                   /**< bit:      1  Data Buffer Empty Interrupt Enable       */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_INTENCLR_OFFSET                 (0x04)                                        /**<  (DAC_INTENCLR) Interrupt Enable Clear  Offset */
#define DAC_INTENCLR_RESETVALUE             _U_(0x00)                                     /**<  (DAC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define DAC_INTENCLR_UNDERRUN_Pos           0                                              /**< (DAC_INTENCLR) Underrun Interrupt Enable Position */
#define DAC_INTENCLR_UNDERRUN_Msk           (_U_(0x1) << DAC_INTENCLR_UNDERRUN_Pos)        /**< (DAC_INTENCLR) Underrun Interrupt Enable Mask */
#define DAC_INTENCLR_UNDERRUN               DAC_INTENCLR_UNDERRUN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTENCLR_UNDERRUN_Msk instead */
#define DAC_INTENCLR_EMPTY_Pos              1                                              /**< (DAC_INTENCLR) Data Buffer Empty Interrupt Enable Position */
#define DAC_INTENCLR_EMPTY_Msk              (_U_(0x1) << DAC_INTENCLR_EMPTY_Pos)           /**< (DAC_INTENCLR) Data Buffer Empty Interrupt Enable Mask */
#define DAC_INTENCLR_EMPTY                  DAC_INTENCLR_EMPTY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTENCLR_EMPTY_Msk instead */
#define DAC_INTENCLR_MASK                   _U_(0x03)                                      /**< \deprecated (DAC_INTENCLR) Register MASK  (Use DAC_INTENCLR_Msk instead)  */
#define DAC_INTENCLR_Msk                    _U_(0x03)                                      /**< (DAC_INTENCLR) Register Mask  */


/* -------- DAC_INTENSET : (DAC Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  UNDERRUN:1;                /**< bit:      0  Underrun Interrupt Enable                */
    uint8_t  EMPTY:1;                   /**< bit:      1  Data Buffer Empty Interrupt Enable       */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_INTENSET_OFFSET                 (0x05)                                        /**<  (DAC_INTENSET) Interrupt Enable Set  Offset */
#define DAC_INTENSET_RESETVALUE             _U_(0x00)                                     /**<  (DAC_INTENSET) Interrupt Enable Set  Reset Value */

#define DAC_INTENSET_UNDERRUN_Pos           0                                              /**< (DAC_INTENSET) Underrun Interrupt Enable Position */
#define DAC_INTENSET_UNDERRUN_Msk           (_U_(0x1) << DAC_INTENSET_UNDERRUN_Pos)        /**< (DAC_INTENSET) Underrun Interrupt Enable Mask */
#define DAC_INTENSET_UNDERRUN               DAC_INTENSET_UNDERRUN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTENSET_UNDERRUN_Msk instead */
#define DAC_INTENSET_EMPTY_Pos              1                                              /**< (DAC_INTENSET) Data Buffer Empty Interrupt Enable Position */
#define DAC_INTENSET_EMPTY_Msk              (_U_(0x1) << DAC_INTENSET_EMPTY_Pos)           /**< (DAC_INTENSET) Data Buffer Empty Interrupt Enable Mask */
#define DAC_INTENSET_EMPTY                  DAC_INTENSET_EMPTY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTENSET_EMPTY_Msk instead */
#define DAC_INTENSET_MASK                   _U_(0x03)                                      /**< \deprecated (DAC_INTENSET) Register MASK  (Use DAC_INTENSET_Msk instead)  */
#define DAC_INTENSET_Msk                    _U_(0x03)                                      /**< (DAC_INTENSET) Register Mask  */


/* -------- DAC_INTFLAG : (DAC Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t UNDERRUN:1;                /**< bit:      0  Underrun                                 */
    __I uint8_t EMPTY:1;                   /**< bit:      1  Data Buffer Empty                        */
    __I uint8_t :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_INTFLAG_OFFSET                  (0x06)                                        /**<  (DAC_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define DAC_INTFLAG_RESETVALUE              _U_(0x00)                                     /**<  (DAC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define DAC_INTFLAG_UNDERRUN_Pos            0                                              /**< (DAC_INTFLAG) Underrun Position */
#define DAC_INTFLAG_UNDERRUN_Msk            (_U_(0x1) << DAC_INTFLAG_UNDERRUN_Pos)         /**< (DAC_INTFLAG) Underrun Mask */
#define DAC_INTFLAG_UNDERRUN                DAC_INTFLAG_UNDERRUN_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTFLAG_UNDERRUN_Msk instead */
#define DAC_INTFLAG_EMPTY_Pos               1                                              /**< (DAC_INTFLAG) Data Buffer Empty Position */
#define DAC_INTFLAG_EMPTY_Msk               (_U_(0x1) << DAC_INTFLAG_EMPTY_Pos)            /**< (DAC_INTFLAG) Data Buffer Empty Mask */
#define DAC_INTFLAG_EMPTY                   DAC_INTFLAG_EMPTY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_INTFLAG_EMPTY_Msk instead */
#define DAC_INTFLAG_MASK                    _U_(0x03)                                      /**< \deprecated (DAC_INTFLAG) Register MASK  (Use DAC_INTFLAG_Msk instead)  */
#define DAC_INTFLAG_Msk                     _U_(0x03)                                      /**< (DAC_INTFLAG) Register Mask  */


/* -------- DAC_STATUS : (DAC Offset: 0x07) (R/ 8) Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  READY:1;                   /**< bit:      0  Ready                                    */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_STATUS_OFFSET                   (0x07)                                        /**<  (DAC_STATUS) Status  Offset */
#define DAC_STATUS_RESETVALUE               _U_(0x00)                                     /**<  (DAC_STATUS) Status  Reset Value */

#define DAC_STATUS_READY_Pos                0                                              /**< (DAC_STATUS) Ready Position */
#define DAC_STATUS_READY_Msk                (_U_(0x1) << DAC_STATUS_READY_Pos)             /**< (DAC_STATUS) Ready Mask */
#define DAC_STATUS_READY                    DAC_STATUS_READY_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_STATUS_READY_Msk instead */
#define DAC_STATUS_MASK                     _U_(0x01)                                      /**< \deprecated (DAC_STATUS) Register MASK  (Use DAC_STATUS_Msk instead)  */
#define DAC_STATUS_Msk                      _U_(0x01)                                      /**< (DAC_STATUS) Register Mask  */


/* -------- DAC_DATA : (DAC Offset: 0x08) (/W 16) Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DATA:16;                   /**< bit:  0..15  Data value to be converted               */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DAC_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_DATA_OFFSET                     (0x08)                                        /**<  (DAC_DATA) Data  Offset */
#define DAC_DATA_RESETVALUE                 _U_(0x00)                                     /**<  (DAC_DATA) Data  Reset Value */

#define DAC_DATA_DATA_Pos                   0                                              /**< (DAC_DATA) Data value to be converted Position */
#define DAC_DATA_DATA_Msk                   (_U_(0xFFFF) << DAC_DATA_DATA_Pos)             /**< (DAC_DATA) Data value to be converted Mask */
#define DAC_DATA_DATA(value)                (DAC_DATA_DATA_Msk & ((value) << DAC_DATA_DATA_Pos))
#define DAC_DATA_MASK                       _U_(0xFFFF)                                    /**< \deprecated (DAC_DATA) Register MASK  (Use DAC_DATA_Msk instead)  */
#define DAC_DATA_Msk                        _U_(0xFFFF)                                    /**< (DAC_DATA) Register Mask  */


/* -------- DAC_DATABUF : (DAC Offset: 0x0c) (/W 16) Data Buffer -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DATABUF:16;                /**< bit:  0..15  Data Buffer                              */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DAC_DATABUF_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_DATABUF_OFFSET                  (0x0C)                                        /**<  (DAC_DATABUF) Data Buffer  Offset */
#define DAC_DATABUF_RESETVALUE              _U_(0x00)                                     /**<  (DAC_DATABUF) Data Buffer  Reset Value */

#define DAC_DATABUF_DATABUF_Pos             0                                              /**< (DAC_DATABUF) Data Buffer Position */
#define DAC_DATABUF_DATABUF_Msk             (_U_(0xFFFF) << DAC_DATABUF_DATABUF_Pos)       /**< (DAC_DATABUF) Data Buffer Mask */
#define DAC_DATABUF_DATABUF(value)          (DAC_DATABUF_DATABUF_Msk & ((value) << DAC_DATABUF_DATABUF_Pos))
#define DAC_DATABUF_MASK                    _U_(0xFFFF)                                    /**< \deprecated (DAC_DATABUF) Register MASK  (Use DAC_DATABUF_Msk instead)  */
#define DAC_DATABUF_Msk                     _U_(0xFFFF)                                    /**< (DAC_DATABUF) Register Mask  */


/* -------- DAC_SYNCBUSY : (DAC Offset: 0x10) (R/ 32) Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t DATA:1;                    /**< bit:      2  Data                                     */
    uint32_t DATABUF:1;                 /**< bit:      3  Data Buffer                              */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DAC_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_SYNCBUSY_OFFSET                 (0x10)                                        /**<  (DAC_SYNCBUSY) Synchronization Busy  Offset */
#define DAC_SYNCBUSY_RESETVALUE             _U_(0x00)                                     /**<  (DAC_SYNCBUSY) Synchronization Busy  Reset Value */

#define DAC_SYNCBUSY_SWRST_Pos              0                                              /**< (DAC_SYNCBUSY) Software Reset Position */
#define DAC_SYNCBUSY_SWRST_Msk              (_U_(0x1) << DAC_SYNCBUSY_SWRST_Pos)           /**< (DAC_SYNCBUSY) Software Reset Mask */
#define DAC_SYNCBUSY_SWRST                  DAC_SYNCBUSY_SWRST_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_SYNCBUSY_SWRST_Msk instead */
#define DAC_SYNCBUSY_ENABLE_Pos             1                                              /**< (DAC_SYNCBUSY) Enable Position */
#define DAC_SYNCBUSY_ENABLE_Msk             (_U_(0x1) << DAC_SYNCBUSY_ENABLE_Pos)          /**< (DAC_SYNCBUSY) Enable Mask */
#define DAC_SYNCBUSY_ENABLE                 DAC_SYNCBUSY_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_SYNCBUSY_ENABLE_Msk instead */
#define DAC_SYNCBUSY_DATA_Pos               2                                              /**< (DAC_SYNCBUSY) Data Position */
#define DAC_SYNCBUSY_DATA_Msk               (_U_(0x1) << DAC_SYNCBUSY_DATA_Pos)            /**< (DAC_SYNCBUSY) Data Mask */
#define DAC_SYNCBUSY_DATA                   DAC_SYNCBUSY_DATA_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_SYNCBUSY_DATA_Msk instead */
#define DAC_SYNCBUSY_DATABUF_Pos            3                                              /**< (DAC_SYNCBUSY) Data Buffer Position */
#define DAC_SYNCBUSY_DATABUF_Msk            (_U_(0x1) << DAC_SYNCBUSY_DATABUF_Pos)         /**< (DAC_SYNCBUSY) Data Buffer Mask */
#define DAC_SYNCBUSY_DATABUF                DAC_SYNCBUSY_DATABUF_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_SYNCBUSY_DATABUF_Msk instead */
#define DAC_SYNCBUSY_MASK                   _U_(0x0F)                                      /**< \deprecated (DAC_SYNCBUSY) Register MASK  (Use DAC_SYNCBUSY_Msk instead)  */
#define DAC_SYNCBUSY_Msk                    _U_(0x0F)                                      /**< (DAC_SYNCBUSY) Register Mask  */


/* -------- DAC_DBGCTRL : (DAC Offset: 0x14) (R/W 8) Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGRUN:1;                  /**< bit:      0  Debug Run                                */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DAC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DAC_DBGCTRL_OFFSET                  (0x14)                                        /**<  (DAC_DBGCTRL) Debug Control  Offset */
#define DAC_DBGCTRL_RESETVALUE              _U_(0x00)                                     /**<  (DAC_DBGCTRL) Debug Control  Reset Value */

#define DAC_DBGCTRL_DBGRUN_Pos              0                                              /**< (DAC_DBGCTRL) Debug Run Position */
#define DAC_DBGCTRL_DBGRUN_Msk              (_U_(0x1) << DAC_DBGCTRL_DBGRUN_Pos)           /**< (DAC_DBGCTRL) Debug Run Mask */
#define DAC_DBGCTRL_DBGRUN                  DAC_DBGCTRL_DBGRUN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DAC_DBGCTRL_DBGRUN_Msk instead */
#define DAC_DBGCTRL_MASK                    _U_(0x01)                                      /**< \deprecated (DAC_DBGCTRL) Register MASK  (Use DAC_DBGCTRL_Msk instead)  */
#define DAC_DBGCTRL_Msk                     _U_(0x01)                                      /**< (DAC_DBGCTRL) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief DAC hardware registers */
typedef struct {  /* Digital Analog Converter */
  __IO DAC_CTRLA_Type                 CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __IO DAC_CTRLB_Type                 CTRLB;          /**< Offset: 0x01 (R/W   8) Control B */
  __IO DAC_EVCTRL_Type                EVCTRL;         /**< Offset: 0x02 (R/W   8) Event Control */
  __I  uint8_t                        Reserved1[1];
  __IO DAC_INTENCLR_Type              INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO DAC_INTENSET_Type              INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO DAC_INTFLAG_Type               INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  DAC_STATUS_Type                STATUS;         /**< Offset: 0x07 (R/    8) Status */
  __O  DAC_DATA_Type                  DATA;           /**< Offset: 0x08 ( /W  16) Data */
  __I  uint8_t                        Reserved2[2];
  __O  DAC_DATABUF_Type               DATABUF;        /**< Offset: 0x0C ( /W  16) Data Buffer */
  __I  uint8_t                        Reserved3[2];
  __I  DAC_SYNCBUSY_Type              SYNCBUSY;       /**< Offset: 0x10 (R/   32) Synchronization Busy */
  __IO DAC_DBGCTRL_Type               DBGCTRL;        /**< Offset: 0x14 (R/W   8) Debug Control */
} Dac;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Digital Analog Converter */

#endif /* _SAML10_DAC_COMPONENT_H_ */
