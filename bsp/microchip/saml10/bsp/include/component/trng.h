/**
 * \file
 *
 * \brief Component description for TRNG
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
#ifndef _SAML10_TRNG_COMPONENT_H_
#define _SAML10_TRNG_COMPONENT_H_
#define _SAML10_TRNG_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 True Random Generator
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR TRNG */
/* ========================================================================== */

#define TRNG_U2242                      /**< (TRNG) Module ID */
#define REV_TRNG 0x120                  /**< (TRNG) Module revision */

/* -------- TRNG_CTRLA : (TRNG Offset: 0x00) (R/W 8) Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :4;                        /**< bit:   2..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Run in Standby                           */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRNG_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_CTRLA_OFFSET                   (0x00)                                        /**<  (TRNG_CTRLA) Control A  Offset */
#define TRNG_CTRLA_RESETVALUE               _U_(0x00)                                     /**<  (TRNG_CTRLA) Control A  Reset Value */

#define TRNG_CTRLA_ENABLE_Pos               1                                              /**< (TRNG_CTRLA) Enable Position */
#define TRNG_CTRLA_ENABLE_Msk               (_U_(0x1) << TRNG_CTRLA_ENABLE_Pos)            /**< (TRNG_CTRLA) Enable Mask */
#define TRNG_CTRLA_ENABLE                   TRNG_CTRLA_ENABLE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_CTRLA_ENABLE_Msk instead */
#define TRNG_CTRLA_RUNSTDBY_Pos             6                                              /**< (TRNG_CTRLA) Run in Standby Position */
#define TRNG_CTRLA_RUNSTDBY_Msk             (_U_(0x1) << TRNG_CTRLA_RUNSTDBY_Pos)          /**< (TRNG_CTRLA) Run in Standby Mask */
#define TRNG_CTRLA_RUNSTDBY                 TRNG_CTRLA_RUNSTDBY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_CTRLA_RUNSTDBY_Msk instead */
#define TRNG_CTRLA_MASK                     _U_(0x42)                                      /**< \deprecated (TRNG_CTRLA) Register MASK  (Use TRNG_CTRLA_Msk instead)  */
#define TRNG_CTRLA_Msk                      _U_(0x42)                                      /**< (TRNG_CTRLA) Register Mask  */


/* -------- TRNG_EVCTRL : (TRNG Offset: 0x04) (R/W 8) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATARDYEO:1;               /**< bit:      0  Data Ready Event Output                  */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRNG_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_EVCTRL_OFFSET                  (0x04)                                        /**<  (TRNG_EVCTRL) Event Control  Offset */
#define TRNG_EVCTRL_RESETVALUE              _U_(0x00)                                     /**<  (TRNG_EVCTRL) Event Control  Reset Value */

#define TRNG_EVCTRL_DATARDYEO_Pos           0                                              /**< (TRNG_EVCTRL) Data Ready Event Output Position */
#define TRNG_EVCTRL_DATARDYEO_Msk           (_U_(0x1) << TRNG_EVCTRL_DATARDYEO_Pos)        /**< (TRNG_EVCTRL) Data Ready Event Output Mask */
#define TRNG_EVCTRL_DATARDYEO               TRNG_EVCTRL_DATARDYEO_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_EVCTRL_DATARDYEO_Msk instead */
#define TRNG_EVCTRL_MASK                    _U_(0x01)                                      /**< \deprecated (TRNG_EVCTRL) Register MASK  (Use TRNG_EVCTRL_Msk instead)  */
#define TRNG_EVCTRL_Msk                     _U_(0x01)                                      /**< (TRNG_EVCTRL) Register Mask  */


/* -------- TRNG_INTENCLR : (TRNG Offset: 0x08) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATARDY:1;                 /**< bit:      0  Data Ready Interrupt Enable              */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRNG_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_INTENCLR_OFFSET                (0x08)                                        /**<  (TRNG_INTENCLR) Interrupt Enable Clear  Offset */
#define TRNG_INTENCLR_RESETVALUE            _U_(0x00)                                     /**<  (TRNG_INTENCLR) Interrupt Enable Clear  Reset Value */

#define TRNG_INTENCLR_DATARDY_Pos           0                                              /**< (TRNG_INTENCLR) Data Ready Interrupt Enable Position */
#define TRNG_INTENCLR_DATARDY_Msk           (_U_(0x1) << TRNG_INTENCLR_DATARDY_Pos)        /**< (TRNG_INTENCLR) Data Ready Interrupt Enable Mask */
#define TRNG_INTENCLR_DATARDY               TRNG_INTENCLR_DATARDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_INTENCLR_DATARDY_Msk instead */
#define TRNG_INTENCLR_MASK                  _U_(0x01)                                      /**< \deprecated (TRNG_INTENCLR) Register MASK  (Use TRNG_INTENCLR_Msk instead)  */
#define TRNG_INTENCLR_Msk                   _U_(0x01)                                      /**< (TRNG_INTENCLR) Register Mask  */


/* -------- TRNG_INTENSET : (TRNG Offset: 0x09) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATARDY:1;                 /**< bit:      0  Data Ready Interrupt Enable              */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRNG_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_INTENSET_OFFSET                (0x09)                                        /**<  (TRNG_INTENSET) Interrupt Enable Set  Offset */
#define TRNG_INTENSET_RESETVALUE            _U_(0x00)                                     /**<  (TRNG_INTENSET) Interrupt Enable Set  Reset Value */

#define TRNG_INTENSET_DATARDY_Pos           0                                              /**< (TRNG_INTENSET) Data Ready Interrupt Enable Position */
#define TRNG_INTENSET_DATARDY_Msk           (_U_(0x1) << TRNG_INTENSET_DATARDY_Pos)        /**< (TRNG_INTENSET) Data Ready Interrupt Enable Mask */
#define TRNG_INTENSET_DATARDY               TRNG_INTENSET_DATARDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_INTENSET_DATARDY_Msk instead */
#define TRNG_INTENSET_MASK                  _U_(0x01)                                      /**< \deprecated (TRNG_INTENSET) Register MASK  (Use TRNG_INTENSET_Msk instead)  */
#define TRNG_INTENSET_Msk                   _U_(0x01)                                      /**< (TRNG_INTENSET) Register Mask  */


/* -------- TRNG_INTFLAG : (TRNG Offset: 0x0a) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t DATARDY:1;                 /**< bit:      0  Data Ready Interrupt Flag                */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRNG_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_INTFLAG_OFFSET                 (0x0A)                                        /**<  (TRNG_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define TRNG_INTFLAG_RESETVALUE             _U_(0x00)                                     /**<  (TRNG_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define TRNG_INTFLAG_DATARDY_Pos            0                                              /**< (TRNG_INTFLAG) Data Ready Interrupt Flag Position */
#define TRNG_INTFLAG_DATARDY_Msk            (_U_(0x1) << TRNG_INTFLAG_DATARDY_Pos)         /**< (TRNG_INTFLAG) Data Ready Interrupt Flag Mask */
#define TRNG_INTFLAG_DATARDY                TRNG_INTFLAG_DATARDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRNG_INTFLAG_DATARDY_Msk instead */
#define TRNG_INTFLAG_MASK                   _U_(0x01)                                      /**< \deprecated (TRNG_INTFLAG) Register MASK  (Use TRNG_INTFLAG_Msk instead)  */
#define TRNG_INTFLAG_Msk                    _U_(0x01)                                      /**< (TRNG_INTFLAG) Register Mask  */


/* -------- TRNG_DATA : (TRNG Offset: 0x20) (R/ 32) Output Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:32;                   /**< bit:  0..31  Output Data                              */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} TRNG_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRNG_DATA_OFFSET                    (0x20)                                        /**<  (TRNG_DATA) Output Data  Offset */
#define TRNG_DATA_RESETVALUE                _U_(0x00)                                     /**<  (TRNG_DATA) Output Data  Reset Value */

#define TRNG_DATA_DATA_Pos                  0                                              /**< (TRNG_DATA) Output Data Position */
#define TRNG_DATA_DATA_Msk                  (_U_(0xFFFFFFFF) << TRNG_DATA_DATA_Pos)        /**< (TRNG_DATA) Output Data Mask */
#define TRNG_DATA_DATA(value)               (TRNG_DATA_DATA_Msk & ((value) << TRNG_DATA_DATA_Pos))
#define TRNG_DATA_MASK                      _U_(0xFFFFFFFF)                                /**< \deprecated (TRNG_DATA) Register MASK  (Use TRNG_DATA_Msk instead)  */
#define TRNG_DATA_Msk                       _U_(0xFFFFFFFF)                                /**< (TRNG_DATA) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief TRNG hardware registers */
typedef struct {  /* True Random Generator */
  __IO TRNG_CTRLA_Type                CTRLA;          /**< Offset: 0x00 (R/W   8) Control A */
  __I  uint8_t                        Reserved1[3];
  __IO TRNG_EVCTRL_Type               EVCTRL;         /**< Offset: 0x04 (R/W   8) Event Control */
  __I  uint8_t                        Reserved2[3];
  __IO TRNG_INTENCLR_Type             INTENCLR;       /**< Offset: 0x08 (R/W   8) Interrupt Enable Clear */
  __IO TRNG_INTENSET_Type             INTENSET;       /**< Offset: 0x09 (R/W   8) Interrupt Enable Set */
  __IO TRNG_INTFLAG_Type              INTFLAG;        /**< Offset: 0x0A (R/W   8) Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved3[21];
  __I  TRNG_DATA_Type                 DATA;           /**< Offset: 0x20 (R/   32) Output Data */
} Trng;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of True Random Generator */

#endif /* _SAML10_TRNG_COMPONENT_H_ */
