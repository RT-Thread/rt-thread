/**
 * \file
 *
 * \brief Component description for FREQM
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
#ifndef _SAML10_FREQM_COMPONENT_H_
#define _SAML10_FREQM_COMPONENT_H_
#define _SAML10_FREQM_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Frequency Meter
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR FREQM */
/* ========================================================================== */

#define FREQM_U2257                      /**< (FREQM) Module ID */
#define REV_FREQM 0x210                  /**< (FREQM) Module revision */

/* -------- FREQM_CTRLA : (FREQM Offset: 0x00) (R/W 8) Control A Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_CTRLA_OFFSET                  (0x00)                                        /**<  (FREQM_CTRLA) Control A Register  Offset */
#define FREQM_CTRLA_RESETVALUE              _U_(0x00)                                     /**<  (FREQM_CTRLA) Control A Register  Reset Value */

#define FREQM_CTRLA_SWRST_Pos               0                                              /**< (FREQM_CTRLA) Software Reset Position */
#define FREQM_CTRLA_SWRST_Msk               (_U_(0x1) << FREQM_CTRLA_SWRST_Pos)            /**< (FREQM_CTRLA) Software Reset Mask */
#define FREQM_CTRLA_SWRST                   FREQM_CTRLA_SWRST_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_CTRLA_SWRST_Msk instead */
#define FREQM_CTRLA_ENABLE_Pos              1                                              /**< (FREQM_CTRLA) Enable Position */
#define FREQM_CTRLA_ENABLE_Msk              (_U_(0x1) << FREQM_CTRLA_ENABLE_Pos)           /**< (FREQM_CTRLA) Enable Mask */
#define FREQM_CTRLA_ENABLE                  FREQM_CTRLA_ENABLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_CTRLA_ENABLE_Msk instead */
#define FREQM_CTRLA_MASK                    _U_(0x03)                                      /**< \deprecated (FREQM_CTRLA) Register MASK  (Use FREQM_CTRLA_Msk instead)  */
#define FREQM_CTRLA_Msk                     _U_(0x03)                                      /**< (FREQM_CTRLA) Register Mask  */


/* -------- FREQM_CTRLB : (FREQM Offset: 0x01) (/W 8) Control B Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  START:1;                   /**< bit:      0  Start Measurement                        */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_CTRLB_OFFSET                  (0x01)                                        /**<  (FREQM_CTRLB) Control B Register  Offset */
#define FREQM_CTRLB_RESETVALUE              _U_(0x00)                                     /**<  (FREQM_CTRLB) Control B Register  Reset Value */

#define FREQM_CTRLB_START_Pos               0                                              /**< (FREQM_CTRLB) Start Measurement Position */
#define FREQM_CTRLB_START_Msk               (_U_(0x1) << FREQM_CTRLB_START_Pos)            /**< (FREQM_CTRLB) Start Measurement Mask */
#define FREQM_CTRLB_START                   FREQM_CTRLB_START_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_CTRLB_START_Msk instead */
#define FREQM_CTRLB_MASK                    _U_(0x01)                                      /**< \deprecated (FREQM_CTRLB) Register MASK  (Use FREQM_CTRLB_Msk instead)  */
#define FREQM_CTRLB_Msk                     _U_(0x01)                                      /**< (FREQM_CTRLB) Register Mask  */


/* -------- FREQM_CFGA : (FREQM Offset: 0x02) (R/W 16) Config A register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t REFNUM:8;                  /**< bit:   0..7  Number of Reference Clock Cycles         */
    uint16_t :7;                        /**< bit:  8..14  Reserved */
    uint16_t DIVREF:1;                  /**< bit:     15  Divide Reference Clock                   */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} FREQM_CFGA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_CFGA_OFFSET                   (0x02)                                        /**<  (FREQM_CFGA) Config A register  Offset */
#define FREQM_CFGA_RESETVALUE               _U_(0x00)                                     /**<  (FREQM_CFGA) Config A register  Reset Value */

#define FREQM_CFGA_REFNUM_Pos               0                                              /**< (FREQM_CFGA) Number of Reference Clock Cycles Position */
#define FREQM_CFGA_REFNUM_Msk               (_U_(0xFF) << FREQM_CFGA_REFNUM_Pos)           /**< (FREQM_CFGA) Number of Reference Clock Cycles Mask */
#define FREQM_CFGA_REFNUM(value)            (FREQM_CFGA_REFNUM_Msk & ((value) << FREQM_CFGA_REFNUM_Pos))
#define FREQM_CFGA_DIVREF_Pos               15                                             /**< (FREQM_CFGA) Divide Reference Clock Position */
#define FREQM_CFGA_DIVREF_Msk               (_U_(0x1) << FREQM_CFGA_DIVREF_Pos)            /**< (FREQM_CFGA) Divide Reference Clock Mask */
#define FREQM_CFGA_DIVREF                   FREQM_CFGA_DIVREF_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_CFGA_DIVREF_Msk instead */
#define FREQM_CFGA_MASK                     _U_(0x80FF)                                    /**< \deprecated (FREQM_CFGA) Register MASK  (Use FREQM_CFGA_Msk instead)  */
#define FREQM_CFGA_Msk                      _U_(0x80FF)                                    /**< (FREQM_CFGA) Register Mask  */


/* -------- FREQM_INTENCLR : (FREQM Offset: 0x08) (R/W 8) Interrupt Enable Clear Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DONE:1;                    /**< bit:      0  Measurement Done Interrupt Enable        */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_INTENCLR_OFFSET               (0x08)                                        /**<  (FREQM_INTENCLR) Interrupt Enable Clear Register  Offset */
#define FREQM_INTENCLR_RESETVALUE           _U_(0x00)                                     /**<  (FREQM_INTENCLR) Interrupt Enable Clear Register  Reset Value */

#define FREQM_INTENCLR_DONE_Pos             0                                              /**< (FREQM_INTENCLR) Measurement Done Interrupt Enable Position */
#define FREQM_INTENCLR_DONE_Msk             (_U_(0x1) << FREQM_INTENCLR_DONE_Pos)          /**< (FREQM_INTENCLR) Measurement Done Interrupt Enable Mask */
#define FREQM_INTENCLR_DONE                 FREQM_INTENCLR_DONE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_INTENCLR_DONE_Msk instead */
#define FREQM_INTENCLR_MASK                 _U_(0x01)                                      /**< \deprecated (FREQM_INTENCLR) Register MASK  (Use FREQM_INTENCLR_Msk instead)  */
#define FREQM_INTENCLR_Msk                  _U_(0x01)                                      /**< (FREQM_INTENCLR) Register Mask  */


/* -------- FREQM_INTENSET : (FREQM Offset: 0x09) (R/W 8) Interrupt Enable Set Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DONE:1;                    /**< bit:      0  Measurement Done Interrupt Enable        */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_INTENSET_OFFSET               (0x09)                                        /**<  (FREQM_INTENSET) Interrupt Enable Set Register  Offset */
#define FREQM_INTENSET_RESETVALUE           _U_(0x00)                                     /**<  (FREQM_INTENSET) Interrupt Enable Set Register  Reset Value */

#define FREQM_INTENSET_DONE_Pos             0                                              /**< (FREQM_INTENSET) Measurement Done Interrupt Enable Position */
#define FREQM_INTENSET_DONE_Msk             (_U_(0x1) << FREQM_INTENSET_DONE_Pos)          /**< (FREQM_INTENSET) Measurement Done Interrupt Enable Mask */
#define FREQM_INTENSET_DONE                 FREQM_INTENSET_DONE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_INTENSET_DONE_Msk instead */
#define FREQM_INTENSET_MASK                 _U_(0x01)                                      /**< \deprecated (FREQM_INTENSET) Register MASK  (Use FREQM_INTENSET_Msk instead)  */
#define FREQM_INTENSET_Msk                  _U_(0x01)                                      /**< (FREQM_INTENSET) Register Mask  */


/* -------- FREQM_INTFLAG : (FREQM Offset: 0x0a) (R/W 8) Interrupt Flag Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t DONE:1;                    /**< bit:      0  Measurement Done                         */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_INTFLAG_OFFSET                (0x0A)                                        /**<  (FREQM_INTFLAG) Interrupt Flag Register  Offset */
#define FREQM_INTFLAG_RESETVALUE            _U_(0x00)                                     /**<  (FREQM_INTFLAG) Interrupt Flag Register  Reset Value */

#define FREQM_INTFLAG_DONE_Pos              0                                              /**< (FREQM_INTFLAG) Measurement Done Position */
#define FREQM_INTFLAG_DONE_Msk              (_U_(0x1) << FREQM_INTFLAG_DONE_Pos)           /**< (FREQM_INTFLAG) Measurement Done Mask */
#define FREQM_INTFLAG_DONE                  FREQM_INTFLAG_DONE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_INTFLAG_DONE_Msk instead */
#define FREQM_INTFLAG_MASK                  _U_(0x01)                                      /**< \deprecated (FREQM_INTFLAG) Register MASK  (Use FREQM_INTFLAG_Msk instead)  */
#define FREQM_INTFLAG_Msk                   _U_(0x01)                                      /**< (FREQM_INTFLAG) Register Mask  */


/* -------- FREQM_STATUS : (FREQM Offset: 0x0b) (R/W 8) Status Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BUSY:1;                    /**< bit:      0  FREQM Status                             */
    uint8_t  OVF:1;                     /**< bit:      1  Sticky Count Value Overflow              */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} FREQM_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_STATUS_OFFSET                 (0x0B)                                        /**<  (FREQM_STATUS) Status Register  Offset */
#define FREQM_STATUS_RESETVALUE             _U_(0x00)                                     /**<  (FREQM_STATUS) Status Register  Reset Value */

#define FREQM_STATUS_BUSY_Pos               0                                              /**< (FREQM_STATUS) FREQM Status Position */
#define FREQM_STATUS_BUSY_Msk               (_U_(0x1) << FREQM_STATUS_BUSY_Pos)            /**< (FREQM_STATUS) FREQM Status Mask */
#define FREQM_STATUS_BUSY                   FREQM_STATUS_BUSY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_STATUS_BUSY_Msk instead */
#define FREQM_STATUS_OVF_Pos                1                                              /**< (FREQM_STATUS) Sticky Count Value Overflow Position */
#define FREQM_STATUS_OVF_Msk                (_U_(0x1) << FREQM_STATUS_OVF_Pos)             /**< (FREQM_STATUS) Sticky Count Value Overflow Mask */
#define FREQM_STATUS_OVF                    FREQM_STATUS_OVF_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_STATUS_OVF_Msk instead */
#define FREQM_STATUS_MASK                   _U_(0x03)                                      /**< \deprecated (FREQM_STATUS) Register MASK  (Use FREQM_STATUS_Msk instead)  */
#define FREQM_STATUS_Msk                    _U_(0x03)                                      /**< (FREQM_STATUS) Register Mask  */


/* -------- FREQM_SYNCBUSY : (FREQM Offset: 0x0c) (R/ 32) Synchronization Busy Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t :30;                       /**< bit:  2..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} FREQM_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_SYNCBUSY_OFFSET               (0x0C)                                        /**<  (FREQM_SYNCBUSY) Synchronization Busy Register  Offset */
#define FREQM_SYNCBUSY_RESETVALUE           _U_(0x00)                                     /**<  (FREQM_SYNCBUSY) Synchronization Busy Register  Reset Value */

#define FREQM_SYNCBUSY_SWRST_Pos            0                                              /**< (FREQM_SYNCBUSY) Software Reset Position */
#define FREQM_SYNCBUSY_SWRST_Msk            (_U_(0x1) << FREQM_SYNCBUSY_SWRST_Pos)         /**< (FREQM_SYNCBUSY) Software Reset Mask */
#define FREQM_SYNCBUSY_SWRST                FREQM_SYNCBUSY_SWRST_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_SYNCBUSY_SWRST_Msk instead */
#define FREQM_SYNCBUSY_ENABLE_Pos           1                                              /**< (FREQM_SYNCBUSY) Enable Position */
#define FREQM_SYNCBUSY_ENABLE_Msk           (_U_(0x1) << FREQM_SYNCBUSY_ENABLE_Pos)        /**< (FREQM_SYNCBUSY) Enable Mask */
#define FREQM_SYNCBUSY_ENABLE               FREQM_SYNCBUSY_ENABLE_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use FREQM_SYNCBUSY_ENABLE_Msk instead */
#define FREQM_SYNCBUSY_MASK                 _U_(0x03)                                      /**< \deprecated (FREQM_SYNCBUSY) Register MASK  (Use FREQM_SYNCBUSY_Msk instead)  */
#define FREQM_SYNCBUSY_Msk                  _U_(0x03)                                      /**< (FREQM_SYNCBUSY) Register Mask  */


/* -------- FREQM_VALUE : (FREQM Offset: 0x10) (R/ 32) Count Value Register -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t VALUE:24;                  /**< bit:  0..23  Measurement Value                        */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} FREQM_VALUE_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define FREQM_VALUE_OFFSET                  (0x10)                                        /**<  (FREQM_VALUE) Count Value Register  Offset */
#define FREQM_VALUE_RESETVALUE              _U_(0x00)                                     /**<  (FREQM_VALUE) Count Value Register  Reset Value */

#define FREQM_VALUE_VALUE_Pos               0                                              /**< (FREQM_VALUE) Measurement Value Position */
#define FREQM_VALUE_VALUE_Msk               (_U_(0xFFFFFF) << FREQM_VALUE_VALUE_Pos)       /**< (FREQM_VALUE) Measurement Value Mask */
#define FREQM_VALUE_VALUE(value)            (FREQM_VALUE_VALUE_Msk & ((value) << FREQM_VALUE_VALUE_Pos))
#define FREQM_VALUE_MASK                    _U_(0xFFFFFF)                                  /**< \deprecated (FREQM_VALUE) Register MASK  (Use FREQM_VALUE_Msk instead)  */
#define FREQM_VALUE_Msk                     _U_(0xFFFFFF)                                  /**< (FREQM_VALUE) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief FREQM hardware registers */
typedef struct {  /* Frequency Meter */
  __IO FREQM_CTRLA_Type               CTRLA;          /**< Offset: 0x00 (R/W   8) Control A Register */
  __O  FREQM_CTRLB_Type               CTRLB;          /**< Offset: 0x01 ( /W   8) Control B Register */
  __IO FREQM_CFGA_Type                CFGA;           /**< Offset: 0x02 (R/W  16) Config A register */
  __I  uint8_t                        Reserved1[4];
  __IO FREQM_INTENCLR_Type            INTENCLR;       /**< Offset: 0x08 (R/W   8) Interrupt Enable Clear Register */
  __IO FREQM_INTENSET_Type            INTENSET;       /**< Offset: 0x09 (R/W   8) Interrupt Enable Set Register */
  __IO FREQM_INTFLAG_Type             INTFLAG;        /**< Offset: 0x0A (R/W   8) Interrupt Flag Register */
  __IO FREQM_STATUS_Type              STATUS;         /**< Offset: 0x0B (R/W   8) Status Register */
  __I  FREQM_SYNCBUSY_Type            SYNCBUSY;       /**< Offset: 0x0C (R/   32) Synchronization Busy Register */
  __I  FREQM_VALUE_Type               VALUE;          /**< Offset: 0x10 (R/   32) Count Value Register */
} Freqm;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Frequency Meter */

#endif /* _SAML10_FREQM_COMPONENT_H_ */
