/**
 * \file
 *
 * \brief Component description for SUPC
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
#ifndef _SAML10_SUPC_COMPONENT_H_
#define _SAML10_SUPC_COMPONENT_H_
#define _SAML10_SUPC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Supply Controller
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SUPC */
/* ========================================================================== */

#define SUPC_U2117                      /**< (SUPC) Module ID */
#define REV_SUPC 0x400                  /**< (SUPC) Module revision */

/* -------- SUPC_INTENCLR : (SUPC Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BOD33RDY:1;                /**< bit:      0  BOD33 Ready                              */
    uint32_t BOD33DET:1;                /**< bit:      1  BOD33 Detection                          */
    uint32_t B33SRDY:1;                 /**< bit:      2  BOD33 Synchronization Ready              */
    uint32_t BOD12RDY:1;                /**< bit:      3  BOD12 Ready                              */
    uint32_t BOD12DET:1;                /**< bit:      4  BOD12 Detection                          */
    uint32_t B12SRDY:1;                 /**< bit:      5  BOD12 Synchronization Ready              */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t VREGRDY:1;                 /**< bit:      8  Voltage Regulator Ready                  */
    uint32_t :1;                        /**< bit:      9  Reserved */
    uint32_t VCORERDY:1;                /**< bit:     10  VDDCORE Ready                            */
    uint32_t ULPVREFRDY:1;              /**< bit:     11  ULPVREF Voltage Reference Ready          */
    uint32_t :20;                       /**< bit: 12..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTENCLR_OFFSET                (0x00)                                        /**<  (SUPC_INTENCLR) Interrupt Enable Clear  Offset */
#define SUPC_INTENCLR_RESETVALUE            _U_(0x00)                                     /**<  (SUPC_INTENCLR) Interrupt Enable Clear  Reset Value */

#define SUPC_INTENCLR_BOD33RDY_Pos          0                                              /**< (SUPC_INTENCLR) BOD33 Ready Position */
#define SUPC_INTENCLR_BOD33RDY_Msk          (_U_(0x1) << SUPC_INTENCLR_BOD33RDY_Pos)       /**< (SUPC_INTENCLR) BOD33 Ready Mask */
#define SUPC_INTENCLR_BOD33RDY              SUPC_INTENCLR_BOD33RDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_BOD33RDY_Msk instead */
#define SUPC_INTENCLR_BOD33DET_Pos          1                                              /**< (SUPC_INTENCLR) BOD33 Detection Position */
#define SUPC_INTENCLR_BOD33DET_Msk          (_U_(0x1) << SUPC_INTENCLR_BOD33DET_Pos)       /**< (SUPC_INTENCLR) BOD33 Detection Mask */
#define SUPC_INTENCLR_BOD33DET              SUPC_INTENCLR_BOD33DET_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_BOD33DET_Msk instead */
#define SUPC_INTENCLR_B33SRDY_Pos           2                                              /**< (SUPC_INTENCLR) BOD33 Synchronization Ready Position */
#define SUPC_INTENCLR_B33SRDY_Msk           (_U_(0x1) << SUPC_INTENCLR_B33SRDY_Pos)        /**< (SUPC_INTENCLR) BOD33 Synchronization Ready Mask */
#define SUPC_INTENCLR_B33SRDY               SUPC_INTENCLR_B33SRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_B33SRDY_Msk instead */
#define SUPC_INTENCLR_BOD12RDY_Pos          3                                              /**< (SUPC_INTENCLR) BOD12 Ready Position */
#define SUPC_INTENCLR_BOD12RDY_Msk          (_U_(0x1) << SUPC_INTENCLR_BOD12RDY_Pos)       /**< (SUPC_INTENCLR) BOD12 Ready Mask */
#define SUPC_INTENCLR_BOD12RDY              SUPC_INTENCLR_BOD12RDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_BOD12RDY_Msk instead */
#define SUPC_INTENCLR_BOD12DET_Pos          4                                              /**< (SUPC_INTENCLR) BOD12 Detection Position */
#define SUPC_INTENCLR_BOD12DET_Msk          (_U_(0x1) << SUPC_INTENCLR_BOD12DET_Pos)       /**< (SUPC_INTENCLR) BOD12 Detection Mask */
#define SUPC_INTENCLR_BOD12DET              SUPC_INTENCLR_BOD12DET_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_BOD12DET_Msk instead */
#define SUPC_INTENCLR_B12SRDY_Pos           5                                              /**< (SUPC_INTENCLR) BOD12 Synchronization Ready Position */
#define SUPC_INTENCLR_B12SRDY_Msk           (_U_(0x1) << SUPC_INTENCLR_B12SRDY_Pos)        /**< (SUPC_INTENCLR) BOD12 Synchronization Ready Mask */
#define SUPC_INTENCLR_B12SRDY               SUPC_INTENCLR_B12SRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_B12SRDY_Msk instead */
#define SUPC_INTENCLR_VREGRDY_Pos           8                                              /**< (SUPC_INTENCLR) Voltage Regulator Ready Position */
#define SUPC_INTENCLR_VREGRDY_Msk           (_U_(0x1) << SUPC_INTENCLR_VREGRDY_Pos)        /**< (SUPC_INTENCLR) Voltage Regulator Ready Mask */
#define SUPC_INTENCLR_VREGRDY               SUPC_INTENCLR_VREGRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_VREGRDY_Msk instead */
#define SUPC_INTENCLR_VCORERDY_Pos          10                                             /**< (SUPC_INTENCLR) VDDCORE Ready Position */
#define SUPC_INTENCLR_VCORERDY_Msk          (_U_(0x1) << SUPC_INTENCLR_VCORERDY_Pos)       /**< (SUPC_INTENCLR) VDDCORE Ready Mask */
#define SUPC_INTENCLR_VCORERDY              SUPC_INTENCLR_VCORERDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_VCORERDY_Msk instead */
#define SUPC_INTENCLR_ULPVREFRDY_Pos        11                                             /**< (SUPC_INTENCLR) ULPVREF Voltage Reference Ready Position */
#define SUPC_INTENCLR_ULPVREFRDY_Msk        (_U_(0x1) << SUPC_INTENCLR_ULPVREFRDY_Pos)     /**< (SUPC_INTENCLR) ULPVREF Voltage Reference Ready Mask */
#define SUPC_INTENCLR_ULPVREFRDY            SUPC_INTENCLR_ULPVREFRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENCLR_ULPVREFRDY_Msk instead */
#define SUPC_INTENCLR_MASK                  _U_(0xD3F)                                     /**< \deprecated (SUPC_INTENCLR) Register MASK  (Use SUPC_INTENCLR_Msk instead)  */
#define SUPC_INTENCLR_Msk                   _U_(0xD3F)                                     /**< (SUPC_INTENCLR) Register Mask  */


/* -------- SUPC_INTENSET : (SUPC Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BOD33RDY:1;                /**< bit:      0  BOD33 Ready                              */
    uint32_t BOD33DET:1;                /**< bit:      1  BOD33 Detection                          */
    uint32_t B33SRDY:1;                 /**< bit:      2  BOD33 Synchronization Ready              */
    uint32_t BOD12RDY:1;                /**< bit:      3  BOD12 Ready                              */
    uint32_t BOD12DET:1;                /**< bit:      4  BOD12 Detection                          */
    uint32_t B12SRDY:1;                 /**< bit:      5  BOD12 Synchronization Ready              */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t VREGRDY:1;                 /**< bit:      8  Voltage Regulator Ready                  */
    uint32_t :1;                        /**< bit:      9  Reserved */
    uint32_t VCORERDY:1;                /**< bit:     10  VDDCORE Ready                            */
    uint32_t ULPVREFRDY:1;              /**< bit:     11  ULPVREF Voltage Reference Ready          */
    uint32_t :20;                       /**< bit: 12..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTENSET_OFFSET                (0x04)                                        /**<  (SUPC_INTENSET) Interrupt Enable Set  Offset */
#define SUPC_INTENSET_RESETVALUE            _U_(0x00)                                     /**<  (SUPC_INTENSET) Interrupt Enable Set  Reset Value */

#define SUPC_INTENSET_BOD33RDY_Pos          0                                              /**< (SUPC_INTENSET) BOD33 Ready Position */
#define SUPC_INTENSET_BOD33RDY_Msk          (_U_(0x1) << SUPC_INTENSET_BOD33RDY_Pos)       /**< (SUPC_INTENSET) BOD33 Ready Mask */
#define SUPC_INTENSET_BOD33RDY              SUPC_INTENSET_BOD33RDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_BOD33RDY_Msk instead */
#define SUPC_INTENSET_BOD33DET_Pos          1                                              /**< (SUPC_INTENSET) BOD33 Detection Position */
#define SUPC_INTENSET_BOD33DET_Msk          (_U_(0x1) << SUPC_INTENSET_BOD33DET_Pos)       /**< (SUPC_INTENSET) BOD33 Detection Mask */
#define SUPC_INTENSET_BOD33DET              SUPC_INTENSET_BOD33DET_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_BOD33DET_Msk instead */
#define SUPC_INTENSET_B33SRDY_Pos           2                                              /**< (SUPC_INTENSET) BOD33 Synchronization Ready Position */
#define SUPC_INTENSET_B33SRDY_Msk           (_U_(0x1) << SUPC_INTENSET_B33SRDY_Pos)        /**< (SUPC_INTENSET) BOD33 Synchronization Ready Mask */
#define SUPC_INTENSET_B33SRDY               SUPC_INTENSET_B33SRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_B33SRDY_Msk instead */
#define SUPC_INTENSET_BOD12RDY_Pos          3                                              /**< (SUPC_INTENSET) BOD12 Ready Position */
#define SUPC_INTENSET_BOD12RDY_Msk          (_U_(0x1) << SUPC_INTENSET_BOD12RDY_Pos)       /**< (SUPC_INTENSET) BOD12 Ready Mask */
#define SUPC_INTENSET_BOD12RDY              SUPC_INTENSET_BOD12RDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_BOD12RDY_Msk instead */
#define SUPC_INTENSET_BOD12DET_Pos          4                                              /**< (SUPC_INTENSET) BOD12 Detection Position */
#define SUPC_INTENSET_BOD12DET_Msk          (_U_(0x1) << SUPC_INTENSET_BOD12DET_Pos)       /**< (SUPC_INTENSET) BOD12 Detection Mask */
#define SUPC_INTENSET_BOD12DET              SUPC_INTENSET_BOD12DET_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_BOD12DET_Msk instead */
#define SUPC_INTENSET_B12SRDY_Pos           5                                              /**< (SUPC_INTENSET) BOD12 Synchronization Ready Position */
#define SUPC_INTENSET_B12SRDY_Msk           (_U_(0x1) << SUPC_INTENSET_B12SRDY_Pos)        /**< (SUPC_INTENSET) BOD12 Synchronization Ready Mask */
#define SUPC_INTENSET_B12SRDY               SUPC_INTENSET_B12SRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_B12SRDY_Msk instead */
#define SUPC_INTENSET_VREGRDY_Pos           8                                              /**< (SUPC_INTENSET) Voltage Regulator Ready Position */
#define SUPC_INTENSET_VREGRDY_Msk           (_U_(0x1) << SUPC_INTENSET_VREGRDY_Pos)        /**< (SUPC_INTENSET) Voltage Regulator Ready Mask */
#define SUPC_INTENSET_VREGRDY               SUPC_INTENSET_VREGRDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_VREGRDY_Msk instead */
#define SUPC_INTENSET_VCORERDY_Pos          10                                             /**< (SUPC_INTENSET) VDDCORE Ready Position */
#define SUPC_INTENSET_VCORERDY_Msk          (_U_(0x1) << SUPC_INTENSET_VCORERDY_Pos)       /**< (SUPC_INTENSET) VDDCORE Ready Mask */
#define SUPC_INTENSET_VCORERDY              SUPC_INTENSET_VCORERDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_VCORERDY_Msk instead */
#define SUPC_INTENSET_ULPVREFRDY_Pos        11                                             /**< (SUPC_INTENSET) ULPVREF Voltage Reference Ready Position */
#define SUPC_INTENSET_ULPVREFRDY_Msk        (_U_(0x1) << SUPC_INTENSET_ULPVREFRDY_Pos)     /**< (SUPC_INTENSET) ULPVREF Voltage Reference Ready Mask */
#define SUPC_INTENSET_ULPVREFRDY            SUPC_INTENSET_ULPVREFRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTENSET_ULPVREFRDY_Msk instead */
#define SUPC_INTENSET_MASK                  _U_(0xD3F)                                     /**< \deprecated (SUPC_INTENSET) Register MASK  (Use SUPC_INTENSET_Msk instead)  */
#define SUPC_INTENSET_Msk                   _U_(0xD3F)                                     /**< (SUPC_INTENSET) Register Mask  */


/* -------- SUPC_INTFLAG : (SUPC Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t BOD33RDY:1;                /**< bit:      0  BOD33 Ready                              */
    __I uint32_t BOD33DET:1;                /**< bit:      1  BOD33 Detection                          */
    __I uint32_t B33SRDY:1;                 /**< bit:      2  BOD33 Synchronization Ready              */
    __I uint32_t BOD12RDY:1;                /**< bit:      3  BOD12 Ready                              */
    __I uint32_t BOD12DET:1;                /**< bit:      4  BOD12 Detection                          */
    __I uint32_t B12SRDY:1;                 /**< bit:      5  BOD12 Synchronization Ready              */
    __I uint32_t :2;                        /**< bit:   6..7  Reserved */
    __I uint32_t VREGRDY:1;                 /**< bit:      8  Voltage Regulator Ready                  */
    __I uint32_t :1;                        /**< bit:      9  Reserved */
    __I uint32_t VCORERDY:1;                /**< bit:     10  VDDCORE Ready                            */
    __I uint32_t ULPVREFRDY:1;              /**< bit:     11  ULPVREF Voltage Reference Ready          */
    __I uint32_t :20;                       /**< bit: 12..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTFLAG_OFFSET                 (0x08)                                        /**<  (SUPC_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define SUPC_INTFLAG_RESETVALUE             _U_(0x00)                                     /**<  (SUPC_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define SUPC_INTFLAG_BOD33RDY_Pos           0                                              /**< (SUPC_INTFLAG) BOD33 Ready Position */
#define SUPC_INTFLAG_BOD33RDY_Msk           (_U_(0x1) << SUPC_INTFLAG_BOD33RDY_Pos)        /**< (SUPC_INTFLAG) BOD33 Ready Mask */
#define SUPC_INTFLAG_BOD33RDY               SUPC_INTFLAG_BOD33RDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_BOD33RDY_Msk instead */
#define SUPC_INTFLAG_BOD33DET_Pos           1                                              /**< (SUPC_INTFLAG) BOD33 Detection Position */
#define SUPC_INTFLAG_BOD33DET_Msk           (_U_(0x1) << SUPC_INTFLAG_BOD33DET_Pos)        /**< (SUPC_INTFLAG) BOD33 Detection Mask */
#define SUPC_INTFLAG_BOD33DET               SUPC_INTFLAG_BOD33DET_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_BOD33DET_Msk instead */
#define SUPC_INTFLAG_B33SRDY_Pos            2                                              /**< (SUPC_INTFLAG) BOD33 Synchronization Ready Position */
#define SUPC_INTFLAG_B33SRDY_Msk            (_U_(0x1) << SUPC_INTFLAG_B33SRDY_Pos)         /**< (SUPC_INTFLAG) BOD33 Synchronization Ready Mask */
#define SUPC_INTFLAG_B33SRDY                SUPC_INTFLAG_B33SRDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_B33SRDY_Msk instead */
#define SUPC_INTFLAG_BOD12RDY_Pos           3                                              /**< (SUPC_INTFLAG) BOD12 Ready Position */
#define SUPC_INTFLAG_BOD12RDY_Msk           (_U_(0x1) << SUPC_INTFLAG_BOD12RDY_Pos)        /**< (SUPC_INTFLAG) BOD12 Ready Mask */
#define SUPC_INTFLAG_BOD12RDY               SUPC_INTFLAG_BOD12RDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_BOD12RDY_Msk instead */
#define SUPC_INTFLAG_BOD12DET_Pos           4                                              /**< (SUPC_INTFLAG) BOD12 Detection Position */
#define SUPC_INTFLAG_BOD12DET_Msk           (_U_(0x1) << SUPC_INTFLAG_BOD12DET_Pos)        /**< (SUPC_INTFLAG) BOD12 Detection Mask */
#define SUPC_INTFLAG_BOD12DET               SUPC_INTFLAG_BOD12DET_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_BOD12DET_Msk instead */
#define SUPC_INTFLAG_B12SRDY_Pos            5                                              /**< (SUPC_INTFLAG) BOD12 Synchronization Ready Position */
#define SUPC_INTFLAG_B12SRDY_Msk            (_U_(0x1) << SUPC_INTFLAG_B12SRDY_Pos)         /**< (SUPC_INTFLAG) BOD12 Synchronization Ready Mask */
#define SUPC_INTFLAG_B12SRDY                SUPC_INTFLAG_B12SRDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_B12SRDY_Msk instead */
#define SUPC_INTFLAG_VREGRDY_Pos            8                                              /**< (SUPC_INTFLAG) Voltage Regulator Ready Position */
#define SUPC_INTFLAG_VREGRDY_Msk            (_U_(0x1) << SUPC_INTFLAG_VREGRDY_Pos)         /**< (SUPC_INTFLAG) Voltage Regulator Ready Mask */
#define SUPC_INTFLAG_VREGRDY                SUPC_INTFLAG_VREGRDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_VREGRDY_Msk instead */
#define SUPC_INTFLAG_VCORERDY_Pos           10                                             /**< (SUPC_INTFLAG) VDDCORE Ready Position */
#define SUPC_INTFLAG_VCORERDY_Msk           (_U_(0x1) << SUPC_INTFLAG_VCORERDY_Pos)        /**< (SUPC_INTFLAG) VDDCORE Ready Mask */
#define SUPC_INTFLAG_VCORERDY               SUPC_INTFLAG_VCORERDY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_VCORERDY_Msk instead */
#define SUPC_INTFLAG_ULPVREFRDY_Pos         11                                             /**< (SUPC_INTFLAG) ULPVREF Voltage Reference Ready Position */
#define SUPC_INTFLAG_ULPVREFRDY_Msk         (_U_(0x1) << SUPC_INTFLAG_ULPVREFRDY_Pos)      /**< (SUPC_INTFLAG) ULPVREF Voltage Reference Ready Mask */
#define SUPC_INTFLAG_ULPVREFRDY             SUPC_INTFLAG_ULPVREFRDY_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_INTFLAG_ULPVREFRDY_Msk instead */
#define SUPC_INTFLAG_MASK                   _U_(0xD3F)                                     /**< \deprecated (SUPC_INTFLAG) Register MASK  (Use SUPC_INTFLAG_Msk instead)  */
#define SUPC_INTFLAG_Msk                    _U_(0xD3F)                                     /**< (SUPC_INTFLAG) Register Mask  */


/* -------- SUPC_STATUS : (SUPC Offset: 0x0c) (R/ 32) Power and Clocks Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BOD33RDY:1;                /**< bit:      0  BOD33 Ready                              */
    uint32_t BOD33DET:1;                /**< bit:      1  BOD33 Detection                          */
    uint32_t B33SRDY:1;                 /**< bit:      2  BOD33 Synchronization Ready              */
    uint32_t BOD12RDY:1;                /**< bit:      3  BOD12 Ready                              */
    uint32_t BOD12DET:1;                /**< bit:      4  BOD12 Detection                          */
    uint32_t B12SRDY:1;                 /**< bit:      5  BOD12 Synchronization Ready              */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t VREGRDY:1;                 /**< bit:      8  Voltage Regulator Ready                  */
    uint32_t :1;                        /**< bit:      9  Reserved */
    uint32_t VCORERDY:1;                /**< bit:     10  VDDCORE Ready                            */
    uint32_t :1;                        /**< bit:     11  Reserved */
    uint32_t ULPVREFRDY:1;              /**< bit:     12  Low Power Voltage Reference Ready        */
    uint32_t ULPBIASRDY:1;              /**< bit:     13  Low Power Voltage Bias Ready             */
    uint32_t :18;                       /**< bit: 14..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_STATUS_OFFSET                  (0x0C)                                        /**<  (SUPC_STATUS) Power and Clocks Status  Offset */
#define SUPC_STATUS_RESETVALUE              _U_(0x00)                                     /**<  (SUPC_STATUS) Power and Clocks Status  Reset Value */

#define SUPC_STATUS_BOD33RDY_Pos            0                                              /**< (SUPC_STATUS) BOD33 Ready Position */
#define SUPC_STATUS_BOD33RDY_Msk            (_U_(0x1) << SUPC_STATUS_BOD33RDY_Pos)         /**< (SUPC_STATUS) BOD33 Ready Mask */
#define SUPC_STATUS_BOD33RDY                SUPC_STATUS_BOD33RDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_BOD33RDY_Msk instead */
#define SUPC_STATUS_BOD33DET_Pos            1                                              /**< (SUPC_STATUS) BOD33 Detection Position */
#define SUPC_STATUS_BOD33DET_Msk            (_U_(0x1) << SUPC_STATUS_BOD33DET_Pos)         /**< (SUPC_STATUS) BOD33 Detection Mask */
#define SUPC_STATUS_BOD33DET                SUPC_STATUS_BOD33DET_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_BOD33DET_Msk instead */
#define SUPC_STATUS_B33SRDY_Pos             2                                              /**< (SUPC_STATUS) BOD33 Synchronization Ready Position */
#define SUPC_STATUS_B33SRDY_Msk             (_U_(0x1) << SUPC_STATUS_B33SRDY_Pos)          /**< (SUPC_STATUS) BOD33 Synchronization Ready Mask */
#define SUPC_STATUS_B33SRDY                 SUPC_STATUS_B33SRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_B33SRDY_Msk instead */
#define SUPC_STATUS_BOD12RDY_Pos            3                                              /**< (SUPC_STATUS) BOD12 Ready Position */
#define SUPC_STATUS_BOD12RDY_Msk            (_U_(0x1) << SUPC_STATUS_BOD12RDY_Pos)         /**< (SUPC_STATUS) BOD12 Ready Mask */
#define SUPC_STATUS_BOD12RDY                SUPC_STATUS_BOD12RDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_BOD12RDY_Msk instead */
#define SUPC_STATUS_BOD12DET_Pos            4                                              /**< (SUPC_STATUS) BOD12 Detection Position */
#define SUPC_STATUS_BOD12DET_Msk            (_U_(0x1) << SUPC_STATUS_BOD12DET_Pos)         /**< (SUPC_STATUS) BOD12 Detection Mask */
#define SUPC_STATUS_BOD12DET                SUPC_STATUS_BOD12DET_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_BOD12DET_Msk instead */
#define SUPC_STATUS_B12SRDY_Pos             5                                              /**< (SUPC_STATUS) BOD12 Synchronization Ready Position */
#define SUPC_STATUS_B12SRDY_Msk             (_U_(0x1) << SUPC_STATUS_B12SRDY_Pos)          /**< (SUPC_STATUS) BOD12 Synchronization Ready Mask */
#define SUPC_STATUS_B12SRDY                 SUPC_STATUS_B12SRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_B12SRDY_Msk instead */
#define SUPC_STATUS_VREGRDY_Pos             8                                              /**< (SUPC_STATUS) Voltage Regulator Ready Position */
#define SUPC_STATUS_VREGRDY_Msk             (_U_(0x1) << SUPC_STATUS_VREGRDY_Pos)          /**< (SUPC_STATUS) Voltage Regulator Ready Mask */
#define SUPC_STATUS_VREGRDY                 SUPC_STATUS_VREGRDY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_VREGRDY_Msk instead */
#define SUPC_STATUS_VCORERDY_Pos            10                                             /**< (SUPC_STATUS) VDDCORE Ready Position */
#define SUPC_STATUS_VCORERDY_Msk            (_U_(0x1) << SUPC_STATUS_VCORERDY_Pos)         /**< (SUPC_STATUS) VDDCORE Ready Mask */
#define SUPC_STATUS_VCORERDY                SUPC_STATUS_VCORERDY_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_VCORERDY_Msk instead */
#define SUPC_STATUS_ULPVREFRDY_Pos          12                                             /**< (SUPC_STATUS) Low Power Voltage Reference Ready Position */
#define SUPC_STATUS_ULPVREFRDY_Msk          (_U_(0x1) << SUPC_STATUS_ULPVREFRDY_Pos)       /**< (SUPC_STATUS) Low Power Voltage Reference Ready Mask */
#define SUPC_STATUS_ULPVREFRDY              SUPC_STATUS_ULPVREFRDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_ULPVREFRDY_Msk instead */
#define SUPC_STATUS_ULPBIASRDY_Pos          13                                             /**< (SUPC_STATUS) Low Power Voltage Bias Ready Position */
#define SUPC_STATUS_ULPBIASRDY_Msk          (_U_(0x1) << SUPC_STATUS_ULPBIASRDY_Pos)       /**< (SUPC_STATUS) Low Power Voltage Bias Ready Mask */
#define SUPC_STATUS_ULPBIASRDY              SUPC_STATUS_ULPBIASRDY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_STATUS_ULPBIASRDY_Msk instead */
#define SUPC_STATUS_MASK                    _U_(0x353F)                                    /**< \deprecated (SUPC_STATUS) Register MASK  (Use SUPC_STATUS_Msk instead)  */
#define SUPC_STATUS_Msk                     _U_(0x353F)                                    /**< (SUPC_STATUS) Register Mask  */


/* -------- SUPC_BOD33 : (SUPC Offset: 0x10) (R/W 32) BOD33 Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t HYST:1;                    /**< bit:      2  Hysteresis Enable                        */
    uint32_t ACTION:2;                  /**< bit:   3..4  Action when Threshold Crossed            */
    uint32_t STDBYCFG:1;                /**< bit:      5  Configuration in Standby mode            */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run during Standby                       */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t ACTCFG:1;                  /**< bit:      8  Configuration in Active mode             */
    uint32_t :2;                        /**< bit:  9..10  Reserved */
    uint32_t REFSEL:1;                  /**< bit:     11  BOD33 Voltage Reference Selection        */
    uint32_t PSEL:4;                    /**< bit: 12..15  Prescaler Select                         */
    uint32_t LEVEL:6;                   /**< bit: 16..21  Threshold Level for VDD                  */
    uint32_t :10;                       /**< bit: 22..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_BOD33_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_BOD33_OFFSET                   (0x10)                                        /**<  (SUPC_BOD33) BOD33 Control  Offset */
#define SUPC_BOD33_RESETVALUE               _U_(0x00)                                     /**<  (SUPC_BOD33) BOD33 Control  Reset Value */

#define SUPC_BOD33_ENABLE_Pos               1                                              /**< (SUPC_BOD33) Enable Position */
#define SUPC_BOD33_ENABLE_Msk               (_U_(0x1) << SUPC_BOD33_ENABLE_Pos)            /**< (SUPC_BOD33) Enable Mask */
#define SUPC_BOD33_ENABLE                   SUPC_BOD33_ENABLE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_ENABLE_Msk instead */
#define SUPC_BOD33_HYST_Pos                 2                                              /**< (SUPC_BOD33) Hysteresis Enable Position */
#define SUPC_BOD33_HYST_Msk                 (_U_(0x1) << SUPC_BOD33_HYST_Pos)              /**< (SUPC_BOD33) Hysteresis Enable Mask */
#define SUPC_BOD33_HYST                     SUPC_BOD33_HYST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_HYST_Msk instead */
#define SUPC_BOD33_ACTION_Pos               3                                              /**< (SUPC_BOD33) Action when Threshold Crossed Position */
#define SUPC_BOD33_ACTION_Msk               (_U_(0x3) << SUPC_BOD33_ACTION_Pos)            /**< (SUPC_BOD33) Action when Threshold Crossed Mask */
#define SUPC_BOD33_ACTION(value)            (SUPC_BOD33_ACTION_Msk & ((value) << SUPC_BOD33_ACTION_Pos))
#define   SUPC_BOD33_ACTION_NONE_Val        _U_(0x0)                                       /**< (SUPC_BOD33) No action  */
#define   SUPC_BOD33_ACTION_RESET_Val       _U_(0x1)                                       /**< (SUPC_BOD33) The BOD33 generates a reset  */
#define   SUPC_BOD33_ACTION_INT_Val         _U_(0x2)                                       /**< (SUPC_BOD33) The BOD33 generates an interrupt  */
#define   SUPC_BOD33_ACTION_BKUP_Val        _U_(0x3)                                       /**< (SUPC_BOD33) The BOD33 puts the device in backup sleep mode if VMON=0  */
#define SUPC_BOD33_ACTION_NONE              (SUPC_BOD33_ACTION_NONE_Val << SUPC_BOD33_ACTION_Pos)  /**< (SUPC_BOD33) No action Position  */
#define SUPC_BOD33_ACTION_RESET             (SUPC_BOD33_ACTION_RESET_Val << SUPC_BOD33_ACTION_Pos)  /**< (SUPC_BOD33) The BOD33 generates a reset Position  */
#define SUPC_BOD33_ACTION_INT               (SUPC_BOD33_ACTION_INT_Val << SUPC_BOD33_ACTION_Pos)  /**< (SUPC_BOD33) The BOD33 generates an interrupt Position  */
#define SUPC_BOD33_ACTION_BKUP              (SUPC_BOD33_ACTION_BKUP_Val << SUPC_BOD33_ACTION_Pos)  /**< (SUPC_BOD33) The BOD33 puts the device in backup sleep mode if VMON=0 Position  */
#define SUPC_BOD33_STDBYCFG_Pos             5                                              /**< (SUPC_BOD33) Configuration in Standby mode Position */
#define SUPC_BOD33_STDBYCFG_Msk             (_U_(0x1) << SUPC_BOD33_STDBYCFG_Pos)          /**< (SUPC_BOD33) Configuration in Standby mode Mask */
#define SUPC_BOD33_STDBYCFG                 SUPC_BOD33_STDBYCFG_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_STDBYCFG_Msk instead */
#define SUPC_BOD33_RUNSTDBY_Pos             6                                              /**< (SUPC_BOD33) Run during Standby Position */
#define SUPC_BOD33_RUNSTDBY_Msk             (_U_(0x1) << SUPC_BOD33_RUNSTDBY_Pos)          /**< (SUPC_BOD33) Run during Standby Mask */
#define SUPC_BOD33_RUNSTDBY                 SUPC_BOD33_RUNSTDBY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_RUNSTDBY_Msk instead */
#define SUPC_BOD33_ACTCFG_Pos               8                                              /**< (SUPC_BOD33) Configuration in Active mode Position */
#define SUPC_BOD33_ACTCFG_Msk               (_U_(0x1) << SUPC_BOD33_ACTCFG_Pos)            /**< (SUPC_BOD33) Configuration in Active mode Mask */
#define SUPC_BOD33_ACTCFG                   SUPC_BOD33_ACTCFG_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_ACTCFG_Msk instead */
#define SUPC_BOD33_REFSEL_Pos               11                                             /**< (SUPC_BOD33) BOD33 Voltage Reference Selection Position */
#define SUPC_BOD33_REFSEL_Msk               (_U_(0x1) << SUPC_BOD33_REFSEL_Pos)            /**< (SUPC_BOD33) BOD33 Voltage Reference Selection Mask */
#define SUPC_BOD33_REFSEL                   SUPC_BOD33_REFSEL_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD33_REFSEL_Msk instead */
#define   SUPC_BOD33_REFSEL_SEL_VREFDETREF_Val _U_(0x0)                                       /**< (SUPC_BOD33) Selects VREFDETREF for the BOD33  */
#define   SUPC_BOD33_REFSEL_SEL_ULPVREF_Val _U_(0x1)                                       /**< (SUPC_BOD33) Selects ULPVREF for the BOD33  */
#define SUPC_BOD33_REFSEL_SEL_VREFDETREF    (SUPC_BOD33_REFSEL_SEL_VREFDETREF_Val << SUPC_BOD33_REFSEL_Pos)  /**< (SUPC_BOD33) Selects VREFDETREF for the BOD33 Position  */
#define SUPC_BOD33_REFSEL_SEL_ULPVREF       (SUPC_BOD33_REFSEL_SEL_ULPVREF_Val << SUPC_BOD33_REFSEL_Pos)  /**< (SUPC_BOD33) Selects ULPVREF for the BOD33 Position  */
#define SUPC_BOD33_PSEL_Pos                 12                                             /**< (SUPC_BOD33) Prescaler Select Position */
#define SUPC_BOD33_PSEL_Msk                 (_U_(0xF) << SUPC_BOD33_PSEL_Pos)              /**< (SUPC_BOD33) Prescaler Select Mask */
#define SUPC_BOD33_PSEL(value)              (SUPC_BOD33_PSEL_Msk & ((value) << SUPC_BOD33_PSEL_Pos))
#define   SUPC_BOD33_PSEL_DIV2_Val          _U_(0x0)                                       /**< (SUPC_BOD33) Divide clock by 2  */
#define   SUPC_BOD33_PSEL_DIV4_Val          _U_(0x1)                                       /**< (SUPC_BOD33) Divide clock by 4  */
#define   SUPC_BOD33_PSEL_DIV8_Val          _U_(0x2)                                       /**< (SUPC_BOD33) Divide clock by 8  */
#define   SUPC_BOD33_PSEL_DIV16_Val         _U_(0x3)                                       /**< (SUPC_BOD33) Divide clock by 16  */
#define   SUPC_BOD33_PSEL_DIV32_Val         _U_(0x4)                                       /**< (SUPC_BOD33) Divide clock by 32  */
#define   SUPC_BOD33_PSEL_DIV64_Val         _U_(0x5)                                       /**< (SUPC_BOD33) Divide clock by 64  */
#define   SUPC_BOD33_PSEL_DIV128_Val        _U_(0x6)                                       /**< (SUPC_BOD33) Divide clock by 128  */
#define   SUPC_BOD33_PSEL_DIV256_Val        _U_(0x7)                                       /**< (SUPC_BOD33) Divide clock by 256  */
#define   SUPC_BOD33_PSEL_DIV512_Val        _U_(0x8)                                       /**< (SUPC_BOD33) Divide clock by 512  */
#define   SUPC_BOD33_PSEL_DIV1024_Val       _U_(0x9)                                       /**< (SUPC_BOD33) Divide clock by 1024  */
#define   SUPC_BOD33_PSEL_DIV2048_Val       _U_(0xA)                                       /**< (SUPC_BOD33) Divide clock by 2048  */
#define   SUPC_BOD33_PSEL_DIV4096_Val       _U_(0xB)                                       /**< (SUPC_BOD33) Divide clock by 4096  */
#define   SUPC_BOD33_PSEL_DIV8192_Val       _U_(0xC)                                       /**< (SUPC_BOD33) Divide clock by 8192  */
#define   SUPC_BOD33_PSEL_DIV16384_Val      _U_(0xD)                                       /**< (SUPC_BOD33) Divide clock by 16384  */
#define   SUPC_BOD33_PSEL_DIV32768_Val      _U_(0xE)                                       /**< (SUPC_BOD33) Divide clock by 32768  */
#define   SUPC_BOD33_PSEL_DIV65536_Val      _U_(0xF)                                       /**< (SUPC_BOD33) Divide clock by 65536  */
#define SUPC_BOD33_PSEL_DIV2                (SUPC_BOD33_PSEL_DIV2_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 2 Position  */
#define SUPC_BOD33_PSEL_DIV4                (SUPC_BOD33_PSEL_DIV4_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 4 Position  */
#define SUPC_BOD33_PSEL_DIV8                (SUPC_BOD33_PSEL_DIV8_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 8 Position  */
#define SUPC_BOD33_PSEL_DIV16               (SUPC_BOD33_PSEL_DIV16_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 16 Position  */
#define SUPC_BOD33_PSEL_DIV32               (SUPC_BOD33_PSEL_DIV32_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 32 Position  */
#define SUPC_BOD33_PSEL_DIV64               (SUPC_BOD33_PSEL_DIV64_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 64 Position  */
#define SUPC_BOD33_PSEL_DIV128              (SUPC_BOD33_PSEL_DIV128_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 128 Position  */
#define SUPC_BOD33_PSEL_DIV256              (SUPC_BOD33_PSEL_DIV256_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 256 Position  */
#define SUPC_BOD33_PSEL_DIV512              (SUPC_BOD33_PSEL_DIV512_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 512 Position  */
#define SUPC_BOD33_PSEL_DIV1024             (SUPC_BOD33_PSEL_DIV1024_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 1024 Position  */
#define SUPC_BOD33_PSEL_DIV2048             (SUPC_BOD33_PSEL_DIV2048_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 2048 Position  */
#define SUPC_BOD33_PSEL_DIV4096             (SUPC_BOD33_PSEL_DIV4096_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 4096 Position  */
#define SUPC_BOD33_PSEL_DIV8192             (SUPC_BOD33_PSEL_DIV8192_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 8192 Position  */
#define SUPC_BOD33_PSEL_DIV16384            (SUPC_BOD33_PSEL_DIV16384_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 16384 Position  */
#define SUPC_BOD33_PSEL_DIV32768            (SUPC_BOD33_PSEL_DIV32768_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 32768 Position  */
#define SUPC_BOD33_PSEL_DIV65536            (SUPC_BOD33_PSEL_DIV65536_Val << SUPC_BOD33_PSEL_Pos)  /**< (SUPC_BOD33) Divide clock by 65536 Position  */
#define SUPC_BOD33_LEVEL_Pos                16                                             /**< (SUPC_BOD33) Threshold Level for VDD Position */
#define SUPC_BOD33_LEVEL_Msk                (_U_(0x3F) << SUPC_BOD33_LEVEL_Pos)            /**< (SUPC_BOD33) Threshold Level for VDD Mask */
#define SUPC_BOD33_LEVEL(value)             (SUPC_BOD33_LEVEL_Msk & ((value) << SUPC_BOD33_LEVEL_Pos))
#define SUPC_BOD33_MASK                     _U_(0x3FF97E)                                  /**< \deprecated (SUPC_BOD33) Register MASK  (Use SUPC_BOD33_Msk instead)  */
#define SUPC_BOD33_Msk                      _U_(0x3FF97E)                                  /**< (SUPC_BOD33) Register Mask  */


/* -------- SUPC_BOD12 : (SUPC Offset: 0x14) (R/W 32) BOD12 Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t HYST:1;                    /**< bit:      2  Hysteresis Enable                        */
    uint32_t ACTION:2;                  /**< bit:   3..4  Action when Threshold Crossed            */
    uint32_t STDBYCFG:1;                /**< bit:      5  Configuration in Standby mode            */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run during Standby                       */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t ACTCFG:1;                  /**< bit:      8  Configuration in Active mode             */
    uint32_t :3;                        /**< bit:  9..11  Reserved */
    uint32_t PSEL:4;                    /**< bit: 12..15  Prescaler Select                         */
    uint32_t LEVEL:6;                   /**< bit: 16..21  Threshold Level                          */
    uint32_t :10;                       /**< bit: 22..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_BOD12_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_BOD12_OFFSET                   (0x14)                                        /**<  (SUPC_BOD12) BOD12 Control  Offset */
#define SUPC_BOD12_RESETVALUE               _U_(0x00)                                     /**<  (SUPC_BOD12) BOD12 Control  Reset Value */

#define SUPC_BOD12_ENABLE_Pos               1                                              /**< (SUPC_BOD12) Enable Position */
#define SUPC_BOD12_ENABLE_Msk               (_U_(0x1) << SUPC_BOD12_ENABLE_Pos)            /**< (SUPC_BOD12) Enable Mask */
#define SUPC_BOD12_ENABLE                   SUPC_BOD12_ENABLE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD12_ENABLE_Msk instead */
#define SUPC_BOD12_HYST_Pos                 2                                              /**< (SUPC_BOD12) Hysteresis Enable Position */
#define SUPC_BOD12_HYST_Msk                 (_U_(0x1) << SUPC_BOD12_HYST_Pos)              /**< (SUPC_BOD12) Hysteresis Enable Mask */
#define SUPC_BOD12_HYST                     SUPC_BOD12_HYST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD12_HYST_Msk instead */
#define SUPC_BOD12_ACTION_Pos               3                                              /**< (SUPC_BOD12) Action when Threshold Crossed Position */
#define SUPC_BOD12_ACTION_Msk               (_U_(0x3) << SUPC_BOD12_ACTION_Pos)            /**< (SUPC_BOD12) Action when Threshold Crossed Mask */
#define SUPC_BOD12_ACTION(value)            (SUPC_BOD12_ACTION_Msk & ((value) << SUPC_BOD12_ACTION_Pos))
#define   SUPC_BOD12_ACTION_NONE_Val        _U_(0x0)                                       /**< (SUPC_BOD12) No action  */
#define   SUPC_BOD12_ACTION_RESET_Val       _U_(0x1)                                       /**< (SUPC_BOD12) The BOD12 generates a reset  */
#define   SUPC_BOD12_ACTION_INT_Val         _U_(0x2)                                       /**< (SUPC_BOD12) The BOD12 generates an interrupt  */
#define SUPC_BOD12_ACTION_NONE              (SUPC_BOD12_ACTION_NONE_Val << SUPC_BOD12_ACTION_Pos)  /**< (SUPC_BOD12) No action Position  */
#define SUPC_BOD12_ACTION_RESET             (SUPC_BOD12_ACTION_RESET_Val << SUPC_BOD12_ACTION_Pos)  /**< (SUPC_BOD12) The BOD12 generates a reset Position  */
#define SUPC_BOD12_ACTION_INT               (SUPC_BOD12_ACTION_INT_Val << SUPC_BOD12_ACTION_Pos)  /**< (SUPC_BOD12) The BOD12 generates an interrupt Position  */
#define SUPC_BOD12_STDBYCFG_Pos             5                                              /**< (SUPC_BOD12) Configuration in Standby mode Position */
#define SUPC_BOD12_STDBYCFG_Msk             (_U_(0x1) << SUPC_BOD12_STDBYCFG_Pos)          /**< (SUPC_BOD12) Configuration in Standby mode Mask */
#define SUPC_BOD12_STDBYCFG                 SUPC_BOD12_STDBYCFG_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD12_STDBYCFG_Msk instead */
#define SUPC_BOD12_RUNSTDBY_Pos             6                                              /**< (SUPC_BOD12) Run during Standby Position */
#define SUPC_BOD12_RUNSTDBY_Msk             (_U_(0x1) << SUPC_BOD12_RUNSTDBY_Pos)          /**< (SUPC_BOD12) Run during Standby Mask */
#define SUPC_BOD12_RUNSTDBY                 SUPC_BOD12_RUNSTDBY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD12_RUNSTDBY_Msk instead */
#define SUPC_BOD12_ACTCFG_Pos               8                                              /**< (SUPC_BOD12) Configuration in Active mode Position */
#define SUPC_BOD12_ACTCFG_Msk               (_U_(0x1) << SUPC_BOD12_ACTCFG_Pos)            /**< (SUPC_BOD12) Configuration in Active mode Mask */
#define SUPC_BOD12_ACTCFG                   SUPC_BOD12_ACTCFG_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_BOD12_ACTCFG_Msk instead */
#define SUPC_BOD12_PSEL_Pos                 12                                             /**< (SUPC_BOD12) Prescaler Select Position */
#define SUPC_BOD12_PSEL_Msk                 (_U_(0xF) << SUPC_BOD12_PSEL_Pos)              /**< (SUPC_BOD12) Prescaler Select Mask */
#define SUPC_BOD12_PSEL(value)              (SUPC_BOD12_PSEL_Msk & ((value) << SUPC_BOD12_PSEL_Pos))
#define   SUPC_BOD12_PSEL_DIV2_Val          _U_(0x0)                                       /**< (SUPC_BOD12) Divide clock by 2  */
#define   SUPC_BOD12_PSEL_DIV4_Val          _U_(0x1)                                       /**< (SUPC_BOD12) Divide clock by 4  */
#define   SUPC_BOD12_PSEL_DIV8_Val          _U_(0x2)                                       /**< (SUPC_BOD12) Divide clock by 8  */
#define   SUPC_BOD12_PSEL_DIV16_Val         _U_(0x3)                                       /**< (SUPC_BOD12) Divide clock by 16  */
#define   SUPC_BOD12_PSEL_DIV32_Val         _U_(0x4)                                       /**< (SUPC_BOD12) Divide clock by 32  */
#define   SUPC_BOD12_PSEL_DIV64_Val         _U_(0x5)                                       /**< (SUPC_BOD12) Divide clock by 64  */
#define   SUPC_BOD12_PSEL_DIV128_Val        _U_(0x6)                                       /**< (SUPC_BOD12) Divide clock by 128  */
#define   SUPC_BOD12_PSEL_DIV256_Val        _U_(0x7)                                       /**< (SUPC_BOD12) Divide clock by 256  */
#define   SUPC_BOD12_PSEL_DIV512_Val        _U_(0x8)                                       /**< (SUPC_BOD12) Divide clock by 512  */
#define   SUPC_BOD12_PSEL_DIV1024_Val       _U_(0x9)                                       /**< (SUPC_BOD12) Divide clock by 1024  */
#define   SUPC_BOD12_PSEL_DIV2048_Val       _U_(0xA)                                       /**< (SUPC_BOD12) Divide clock by 2048  */
#define   SUPC_BOD12_PSEL_DIV4096_Val       _U_(0xB)                                       /**< (SUPC_BOD12) Divide clock by 4096  */
#define   SUPC_BOD12_PSEL_DIV8192_Val       _U_(0xC)                                       /**< (SUPC_BOD12) Divide clock by 8192  */
#define   SUPC_BOD12_PSEL_DIV16384_Val      _U_(0xD)                                       /**< (SUPC_BOD12) Divide clock by 16384  */
#define   SUPC_BOD12_PSEL_DIV32768_Val      _U_(0xE)                                       /**< (SUPC_BOD12) Divide clock by 32768  */
#define   SUPC_BOD12_PSEL_DIV65536_Val      _U_(0xF)                                       /**< (SUPC_BOD12) Divide clock by 65536  */
#define SUPC_BOD12_PSEL_DIV2                (SUPC_BOD12_PSEL_DIV2_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 2 Position  */
#define SUPC_BOD12_PSEL_DIV4                (SUPC_BOD12_PSEL_DIV4_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 4 Position  */
#define SUPC_BOD12_PSEL_DIV8                (SUPC_BOD12_PSEL_DIV8_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 8 Position  */
#define SUPC_BOD12_PSEL_DIV16               (SUPC_BOD12_PSEL_DIV16_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 16 Position  */
#define SUPC_BOD12_PSEL_DIV32               (SUPC_BOD12_PSEL_DIV32_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 32 Position  */
#define SUPC_BOD12_PSEL_DIV64               (SUPC_BOD12_PSEL_DIV64_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 64 Position  */
#define SUPC_BOD12_PSEL_DIV128              (SUPC_BOD12_PSEL_DIV128_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 128 Position  */
#define SUPC_BOD12_PSEL_DIV256              (SUPC_BOD12_PSEL_DIV256_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 256 Position  */
#define SUPC_BOD12_PSEL_DIV512              (SUPC_BOD12_PSEL_DIV512_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 512 Position  */
#define SUPC_BOD12_PSEL_DIV1024             (SUPC_BOD12_PSEL_DIV1024_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 1024 Position  */
#define SUPC_BOD12_PSEL_DIV2048             (SUPC_BOD12_PSEL_DIV2048_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 2048 Position  */
#define SUPC_BOD12_PSEL_DIV4096             (SUPC_BOD12_PSEL_DIV4096_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 4096 Position  */
#define SUPC_BOD12_PSEL_DIV8192             (SUPC_BOD12_PSEL_DIV8192_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 8192 Position  */
#define SUPC_BOD12_PSEL_DIV16384            (SUPC_BOD12_PSEL_DIV16384_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 16384 Position  */
#define SUPC_BOD12_PSEL_DIV32768            (SUPC_BOD12_PSEL_DIV32768_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 32768 Position  */
#define SUPC_BOD12_PSEL_DIV65536            (SUPC_BOD12_PSEL_DIV65536_Val << SUPC_BOD12_PSEL_Pos)  /**< (SUPC_BOD12) Divide clock by 65536 Position  */
#define SUPC_BOD12_LEVEL_Pos                16                                             /**< (SUPC_BOD12) Threshold Level Position */
#define SUPC_BOD12_LEVEL_Msk                (_U_(0x3F) << SUPC_BOD12_LEVEL_Pos)            /**< (SUPC_BOD12) Threshold Level Mask */
#define SUPC_BOD12_LEVEL(value)             (SUPC_BOD12_LEVEL_Msk & ((value) << SUPC_BOD12_LEVEL_Pos))
#define SUPC_BOD12_MASK                     _U_(0x3FF17E)                                  /**< \deprecated (SUPC_BOD12) Register MASK  (Use SUPC_BOD12_Msk instead)  */
#define SUPC_BOD12_Msk                      _U_(0x3FF17E)                                  /**< (SUPC_BOD12) Register Mask  */


/* -------- SUPC_VREG : (SUPC Offset: 0x18) (R/W 32) VREG Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t SEL:2;                     /**< bit:   2..3  Voltage Regulator Selection in active mode */
    uint32_t :1;                        /**< bit:      4  Reserved */
    uint32_t STDBYPL0:1;                /**< bit:      5  Standby in PL0                           */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run during Standby                       */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t LPEFF:1;                   /**< bit:      8  Low Power efficiency                     */
    uint32_t VREFSEL:1;                 /**< bit:      9  Voltage Regulator Voltage Reference Selection */
    uint32_t :6;                        /**< bit: 10..15  Reserved */
    uint32_t VSVSTEP:4;                 /**< bit: 16..19  Voltage Scaling Voltage Step             */
    uint32_t :4;                        /**< bit: 20..23  Reserved */
    uint32_t VSPER:8;                   /**< bit: 24..31  Voltage Scaling Period                   */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :5;                        /**< bit:   0..4  Reserved */
    uint32_t STDBYPL:1;                 /**< bit:      5  Standby in PLx                           */
    uint32_t :26;                       /**< bit:  6..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_VREG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_VREG_OFFSET                    (0x18)                                        /**<  (SUPC_VREG) VREG Control  Offset */
#define SUPC_VREG_RESETVALUE                _U_(0x02)                                     /**<  (SUPC_VREG) VREG Control  Reset Value */

#define SUPC_VREG_ENABLE_Pos                1                                              /**< (SUPC_VREG) Enable Position */
#define SUPC_VREG_ENABLE_Msk                (_U_(0x1) << SUPC_VREG_ENABLE_Pos)             /**< (SUPC_VREG) Enable Mask */
#define SUPC_VREG_ENABLE                    SUPC_VREG_ENABLE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREG_ENABLE_Msk instead */
#define SUPC_VREG_SEL_Pos                   2                                              /**< (SUPC_VREG) Voltage Regulator Selection in active mode Position */
#define SUPC_VREG_SEL_Msk                   (_U_(0x3) << SUPC_VREG_SEL_Pos)                /**< (SUPC_VREG) Voltage Regulator Selection in active mode Mask */
#define SUPC_VREG_SEL(value)                (SUPC_VREG_SEL_Msk & ((value) << SUPC_VREG_SEL_Pos))
#define   SUPC_VREG_SEL_LDO_Val             _U_(0x0)                                       /**< (SUPC_VREG) LDO selection  */
#define   SUPC_VREG_SEL_BUCK_Val            _U_(0x1)                                       /**< (SUPC_VREG) Buck selection  */
#define SUPC_VREG_SEL_LDO                   (SUPC_VREG_SEL_LDO_Val << SUPC_VREG_SEL_Pos)   /**< (SUPC_VREG) LDO selection Position  */
#define SUPC_VREG_SEL_BUCK                  (SUPC_VREG_SEL_BUCK_Val << SUPC_VREG_SEL_Pos)  /**< (SUPC_VREG) Buck selection Position  */
#define SUPC_VREG_STDBYPL0_Pos              5                                              /**< (SUPC_VREG) Standby in PL0 Position */
#define SUPC_VREG_STDBYPL0_Msk              (_U_(0x1) << SUPC_VREG_STDBYPL0_Pos)           /**< (SUPC_VREG) Standby in PL0 Mask */
#define SUPC_VREG_STDBYPL0                  SUPC_VREG_STDBYPL0_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREG_STDBYPL0_Msk instead */
#define SUPC_VREG_RUNSTDBY_Pos              6                                              /**< (SUPC_VREG) Run during Standby Position */
#define SUPC_VREG_RUNSTDBY_Msk              (_U_(0x1) << SUPC_VREG_RUNSTDBY_Pos)           /**< (SUPC_VREG) Run during Standby Mask */
#define SUPC_VREG_RUNSTDBY                  SUPC_VREG_RUNSTDBY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREG_RUNSTDBY_Msk instead */
#define SUPC_VREG_LPEFF_Pos                 8                                              /**< (SUPC_VREG) Low Power efficiency Position */
#define SUPC_VREG_LPEFF_Msk                 (_U_(0x1) << SUPC_VREG_LPEFF_Pos)              /**< (SUPC_VREG) Low Power efficiency Mask */
#define SUPC_VREG_LPEFF                     SUPC_VREG_LPEFF_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREG_LPEFF_Msk instead */
#define SUPC_VREG_VREFSEL_Pos               9                                              /**< (SUPC_VREG) Voltage Regulator Voltage Reference Selection Position */
#define SUPC_VREG_VREFSEL_Msk               (_U_(0x1) << SUPC_VREG_VREFSEL_Pos)            /**< (SUPC_VREG) Voltage Regulator Voltage Reference Selection Mask */
#define SUPC_VREG_VREFSEL                   SUPC_VREG_VREFSEL_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREG_VREFSEL_Msk instead */
#define SUPC_VREG_VSVSTEP_Pos               16                                             /**< (SUPC_VREG) Voltage Scaling Voltage Step Position */
#define SUPC_VREG_VSVSTEP_Msk               (_U_(0xF) << SUPC_VREG_VSVSTEP_Pos)            /**< (SUPC_VREG) Voltage Scaling Voltage Step Mask */
#define SUPC_VREG_VSVSTEP(value)            (SUPC_VREG_VSVSTEP_Msk & ((value) << SUPC_VREG_VSVSTEP_Pos))
#define SUPC_VREG_VSPER_Pos                 24                                             /**< (SUPC_VREG) Voltage Scaling Period Position */
#define SUPC_VREG_VSPER_Msk                 (_U_(0xFF) << SUPC_VREG_VSPER_Pos)             /**< (SUPC_VREG) Voltage Scaling Period Mask */
#define SUPC_VREG_VSPER(value)              (SUPC_VREG_VSPER_Msk & ((value) << SUPC_VREG_VSPER_Pos))
#define SUPC_VREG_MASK                      _U_(0xFF0F036E)                                /**< \deprecated (SUPC_VREG) Register MASK  (Use SUPC_VREG_Msk instead)  */
#define SUPC_VREG_Msk                       _U_(0xFF0F036E)                                /**< (SUPC_VREG) Register Mask  */

#define SUPC_VREG_STDBYPL_Pos               5                                              /**< (SUPC_VREG Position) Standby in PLx */
#define SUPC_VREG_STDBYPL_Msk               (_U_(0x1) << SUPC_VREG_STDBYPL_Pos)            /**< (SUPC_VREG Mask) STDBYPL */
#define SUPC_VREG_STDBYPL(value)            (SUPC_VREG_STDBYPL_Msk & ((value) << SUPC_VREG_STDBYPL_Pos))  

/* -------- SUPC_VREF : (SUPC Offset: 0x1c) (R/W 32) VREF Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t TSEN:1;                    /**< bit:      1  Temperature Sensor Output Enable         */
    uint32_t VREFOE:1;                  /**< bit:      2  Voltage Reference Output Enable          */
    uint32_t TSSEL:1;                   /**< bit:      3  Temperature Sensor Selection             */
    uint32_t :2;                        /**< bit:   4..5  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      6  Run during Standby                       */
    uint32_t ONDEMAND:1;                /**< bit:      7  On Demand Control                        */
    uint32_t :8;                        /**< bit:  8..15  Reserved */
    uint32_t SEL:4;                     /**< bit: 16..19  Voltage Reference Selection              */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_VREF_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_VREF_OFFSET                    (0x1C)                                        /**<  (SUPC_VREF) VREF Control  Offset */
#define SUPC_VREF_RESETVALUE                _U_(0x00)                                     /**<  (SUPC_VREF) VREF Control  Reset Value */

#define SUPC_VREF_TSEN_Pos                  1                                              /**< (SUPC_VREF) Temperature Sensor Output Enable Position */
#define SUPC_VREF_TSEN_Msk                  (_U_(0x1) << SUPC_VREF_TSEN_Pos)               /**< (SUPC_VREF) Temperature Sensor Output Enable Mask */
#define SUPC_VREF_TSEN                      SUPC_VREF_TSEN_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREF_TSEN_Msk instead */
#define SUPC_VREF_VREFOE_Pos                2                                              /**< (SUPC_VREF) Voltage Reference Output Enable Position */
#define SUPC_VREF_VREFOE_Msk                (_U_(0x1) << SUPC_VREF_VREFOE_Pos)             /**< (SUPC_VREF) Voltage Reference Output Enable Mask */
#define SUPC_VREF_VREFOE                    SUPC_VREF_VREFOE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREF_VREFOE_Msk instead */
#define SUPC_VREF_TSSEL_Pos                 3                                              /**< (SUPC_VREF) Temperature Sensor Selection Position */
#define SUPC_VREF_TSSEL_Msk                 (_U_(0x1) << SUPC_VREF_TSSEL_Pos)              /**< (SUPC_VREF) Temperature Sensor Selection Mask */
#define SUPC_VREF_TSSEL                     SUPC_VREF_TSSEL_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREF_TSSEL_Msk instead */
#define SUPC_VREF_RUNSTDBY_Pos              6                                              /**< (SUPC_VREF) Run during Standby Position */
#define SUPC_VREF_RUNSTDBY_Msk              (_U_(0x1) << SUPC_VREF_RUNSTDBY_Pos)           /**< (SUPC_VREF) Run during Standby Mask */
#define SUPC_VREF_RUNSTDBY                  SUPC_VREF_RUNSTDBY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREF_RUNSTDBY_Msk instead */
#define SUPC_VREF_ONDEMAND_Pos              7                                              /**< (SUPC_VREF) On Demand Control Position */
#define SUPC_VREF_ONDEMAND_Msk              (_U_(0x1) << SUPC_VREF_ONDEMAND_Pos)           /**< (SUPC_VREF) On Demand Control Mask */
#define SUPC_VREF_ONDEMAND                  SUPC_VREF_ONDEMAND_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREF_ONDEMAND_Msk instead */
#define SUPC_VREF_SEL_Pos                   16                                             /**< (SUPC_VREF) Voltage Reference Selection Position */
#define SUPC_VREF_SEL_Msk                   (_U_(0xF) << SUPC_VREF_SEL_Pos)                /**< (SUPC_VREF) Voltage Reference Selection Mask */
#define SUPC_VREF_SEL(value)                (SUPC_VREF_SEL_Msk & ((value) << SUPC_VREF_SEL_Pos))
#define   SUPC_VREF_SEL_1V0_Val             _U_(0x0)                                       /**< (SUPC_VREF) 1.0V voltage reference typical value  */
#define   SUPC_VREF_SEL_1V1_Val             _U_(0x1)                                       /**< (SUPC_VREF) 1.1V voltage reference typical value  */
#define   SUPC_VREF_SEL_1V2_Val             _U_(0x2)                                       /**< (SUPC_VREF) 1.2V voltage reference typical value  */
#define   SUPC_VREF_SEL_1V25_Val            _U_(0x3)                                       /**< (SUPC_VREF) 1.25V voltage reference typical value  */
#define   SUPC_VREF_SEL_2V0_Val             _U_(0x4)                                       /**< (SUPC_VREF) 2.0V voltage reference typical value  */
#define   SUPC_VREF_SEL_2V2_Val             _U_(0x5)                                       /**< (SUPC_VREF) 2.2V voltage reference typical value  */
#define   SUPC_VREF_SEL_2V4_Val             _U_(0x6)                                       /**< (SUPC_VREF) 2.4V voltage reference typical value  */
#define   SUPC_VREF_SEL_2V5_Val             _U_(0x7)                                       /**< (SUPC_VREF) 2.5V voltage reference typical value  */
#define SUPC_VREF_SEL_1V0                   (SUPC_VREF_SEL_1V0_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 1.0V voltage reference typical value Position  */
#define SUPC_VREF_SEL_1V1                   (SUPC_VREF_SEL_1V1_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 1.1V voltage reference typical value Position  */
#define SUPC_VREF_SEL_1V2                   (SUPC_VREF_SEL_1V2_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 1.2V voltage reference typical value Position  */
#define SUPC_VREF_SEL_1V25                  (SUPC_VREF_SEL_1V25_Val << SUPC_VREF_SEL_Pos)  /**< (SUPC_VREF) 1.25V voltage reference typical value Position  */
#define SUPC_VREF_SEL_2V0                   (SUPC_VREF_SEL_2V0_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 2.0V voltage reference typical value Position  */
#define SUPC_VREF_SEL_2V2                   (SUPC_VREF_SEL_2V2_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 2.2V voltage reference typical value Position  */
#define SUPC_VREF_SEL_2V4                   (SUPC_VREF_SEL_2V4_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 2.4V voltage reference typical value Position  */
#define SUPC_VREF_SEL_2V5                   (SUPC_VREF_SEL_2V5_Val << SUPC_VREF_SEL_Pos)   /**< (SUPC_VREF) 2.5V voltage reference typical value Position  */
#define SUPC_VREF_MASK                      _U_(0xF00CE)                                   /**< \deprecated (SUPC_VREF) Register MASK  (Use SUPC_VREF_Msk instead)  */
#define SUPC_VREF_Msk                       _U_(0xF00CE)                                   /**< (SUPC_VREF) Register Mask  */


/* -------- SUPC_EVCTRL : (SUPC Offset: 0x2c) (R/W 32) Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t BOD33DETEO:1;              /**< bit:      1  BOD33 Detection Event Output Enable      */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t BOD12DETEO:1;              /**< bit:      4  BOD12 Detection Event Output Enable      */
    uint32_t :27;                       /**< bit:  5..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_EVCTRL_OFFSET                  (0x2C)                                        /**<  (SUPC_EVCTRL) Event Control  Offset */
#define SUPC_EVCTRL_RESETVALUE              _U_(0x00)                                     /**<  (SUPC_EVCTRL) Event Control  Reset Value */

#define SUPC_EVCTRL_BOD33DETEO_Pos          1                                              /**< (SUPC_EVCTRL) BOD33 Detection Event Output Enable Position */
#define SUPC_EVCTRL_BOD33DETEO_Msk          (_U_(0x1) << SUPC_EVCTRL_BOD33DETEO_Pos)       /**< (SUPC_EVCTRL) BOD33 Detection Event Output Enable Mask */
#define SUPC_EVCTRL_BOD33DETEO              SUPC_EVCTRL_BOD33DETEO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_EVCTRL_BOD33DETEO_Msk instead */
#define SUPC_EVCTRL_BOD12DETEO_Pos          4                                              /**< (SUPC_EVCTRL) BOD12 Detection Event Output Enable Position */
#define SUPC_EVCTRL_BOD12DETEO_Msk          (_U_(0x1) << SUPC_EVCTRL_BOD12DETEO_Pos)       /**< (SUPC_EVCTRL) BOD12 Detection Event Output Enable Mask */
#define SUPC_EVCTRL_BOD12DETEO              SUPC_EVCTRL_BOD12DETEO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_EVCTRL_BOD12DETEO_Msk instead */
#define SUPC_EVCTRL_MASK                    _U_(0x12)                                      /**< \deprecated (SUPC_EVCTRL) Register MASK  (Use SUPC_EVCTRL_Msk instead)  */
#define SUPC_EVCTRL_Msk                     _U_(0x12)                                      /**< (SUPC_EVCTRL) Register Mask  */


/* -------- SUPC_VREGSUSP : (SUPC Offset: 0x30) (R/W 32) VREG Suspend Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t VREGSEN:1;                 /**< bit:      0  Enable Voltage Regulator Suspend         */
    uint32_t :31;                       /**< bit:  1..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SUPC_VREGSUSP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_VREGSUSP_OFFSET                (0x30)                                        /**<  (SUPC_VREGSUSP) VREG Suspend Control  Offset */
#define SUPC_VREGSUSP_RESETVALUE            _U_(0x00)                                     /**<  (SUPC_VREGSUSP) VREG Suspend Control  Reset Value */

#define SUPC_VREGSUSP_VREGSEN_Pos           0                                              /**< (SUPC_VREGSUSP) Enable Voltage Regulator Suspend Position */
#define SUPC_VREGSUSP_VREGSEN_Msk           (_U_(0x1) << SUPC_VREGSUSP_VREGSEN_Pos)        /**< (SUPC_VREGSUSP) Enable Voltage Regulator Suspend Mask */
#define SUPC_VREGSUSP_VREGSEN               SUPC_VREGSUSP_VREGSEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SUPC_VREGSUSP_VREGSEN_Msk instead */
#define SUPC_VREGSUSP_MASK                  _U_(0x01)                                      /**< \deprecated (SUPC_VREGSUSP) Register MASK  (Use SUPC_VREGSUSP_Msk instead)  */
#define SUPC_VREGSUSP_Msk                   _U_(0x01)                                      /**< (SUPC_VREGSUSP) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SUPC hardware registers */
typedef struct {  /* Supply Controller */
  __IO SUPC_INTENCLR_Type             INTENCLR;       /**< Offset: 0x00 (R/W  32) Interrupt Enable Clear */
  __IO SUPC_INTENSET_Type             INTENSET;       /**< Offset: 0x04 (R/W  32) Interrupt Enable Set */
  __IO SUPC_INTFLAG_Type              INTFLAG;        /**< Offset: 0x08 (R/W  32) Interrupt Flag Status and Clear */
  __I  SUPC_STATUS_Type               STATUS;         /**< Offset: 0x0C (R/   32) Power and Clocks Status */
  __IO SUPC_BOD33_Type                BOD33;          /**< Offset: 0x10 (R/W  32) BOD33 Control */
  __IO SUPC_BOD12_Type                BOD12;          /**< Offset: 0x14 (R/W  32) BOD12 Control */
  __IO SUPC_VREG_Type                 VREG;           /**< Offset: 0x18 (R/W  32) VREG Control */
  __IO SUPC_VREF_Type                 VREF;           /**< Offset: 0x1C (R/W  32) VREF Control */
  __I  uint8_t                        Reserved1[12];
  __IO SUPC_EVCTRL_Type               EVCTRL;         /**< Offset: 0x2C (R/W  32) Event Control */
  __IO SUPC_VREGSUSP_Type             VREGSUSP;       /**< Offset: 0x30 (R/W  32) VREG Suspend Control */
} Supc;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Supply Controller */

#endif /* _SAML10_SUPC_COMPONENT_H_ */
