/**
 * \file
 *
 * \brief Component description for TRAM
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
#ifndef _SAML10_TRAM_COMPONENT_H_
#define _SAML10_TRAM_COMPONENT_H_
#define _SAML10_TRAM_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 TrustRAM
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR TRAM */
/* ========================================================================== */

#define TRAM_U2801                      /**< (TRAM) Module ID */
#define REV_TRAM 0x100                  /**< (TRAM) Module revision */

/* -------- TRAM_CTRLA : (TRAM Offset: 0x00) (R/W 8) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  TAMPERS:1;                 /**< bit:      4  Tamper Erase                             */
    uint8_t  :1;                        /**< bit:      5  Reserved */
    uint8_t  DRP:1;                     /**< bit:      6  Data Remanence Prevention                */
    uint8_t  SILACC:1;                  /**< bit:      7  Silent Access                            */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_CTRLA_OFFSET                   (0x00)                                        /**<  (TRAM_CTRLA) Control  Offset */
#define TRAM_CTRLA_RESETVALUE               _U_(0x00)                                     /**<  (TRAM_CTRLA) Control  Reset Value */

#define TRAM_CTRLA_SWRST_Pos                0                                              /**< (TRAM_CTRLA) Software Reset Position */
#define TRAM_CTRLA_SWRST_Msk                (_U_(0x1) << TRAM_CTRLA_SWRST_Pos)             /**< (TRAM_CTRLA) Software Reset Mask */
#define TRAM_CTRLA_SWRST                    TRAM_CTRLA_SWRST_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_CTRLA_SWRST_Msk instead */
#define TRAM_CTRLA_ENABLE_Pos               1                                              /**< (TRAM_CTRLA) Enable Position */
#define TRAM_CTRLA_ENABLE_Msk               (_U_(0x1) << TRAM_CTRLA_ENABLE_Pos)            /**< (TRAM_CTRLA) Enable Mask */
#define TRAM_CTRLA_ENABLE                   TRAM_CTRLA_ENABLE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_CTRLA_ENABLE_Msk instead */
#define TRAM_CTRLA_TAMPERS_Pos              4                                              /**< (TRAM_CTRLA) Tamper Erase Position */
#define TRAM_CTRLA_TAMPERS_Msk              (_U_(0x1) << TRAM_CTRLA_TAMPERS_Pos)           /**< (TRAM_CTRLA) Tamper Erase Mask */
#define TRAM_CTRLA_TAMPERS                  TRAM_CTRLA_TAMPERS_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_CTRLA_TAMPERS_Msk instead */
#define TRAM_CTRLA_DRP_Pos                  6                                              /**< (TRAM_CTRLA) Data Remanence Prevention Position */
#define TRAM_CTRLA_DRP_Msk                  (_U_(0x1) << TRAM_CTRLA_DRP_Pos)               /**< (TRAM_CTRLA) Data Remanence Prevention Mask */
#define TRAM_CTRLA_DRP                      TRAM_CTRLA_DRP_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_CTRLA_DRP_Msk instead */
#define TRAM_CTRLA_SILACC_Pos               7                                              /**< (TRAM_CTRLA) Silent Access Position */
#define TRAM_CTRLA_SILACC_Msk               (_U_(0x1) << TRAM_CTRLA_SILACC_Pos)            /**< (TRAM_CTRLA) Silent Access Mask */
#define TRAM_CTRLA_SILACC                   TRAM_CTRLA_SILACC_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_CTRLA_SILACC_Msk instead */
#define TRAM_CTRLA_MASK                     _U_(0xD3)                                      /**< \deprecated (TRAM_CTRLA) Register MASK  (Use TRAM_CTRLA_Msk instead)  */
#define TRAM_CTRLA_Msk                      _U_(0xD3)                                      /**< (TRAM_CTRLA) Register Mask  */


/* -------- TRAM_INTENCLR : (TRAM Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ERR:1;                     /**< bit:      0  TrustRAM Readout Error Interrupt Enable  */
    uint8_t  DRP:1;                     /**< bit:      1  Data Remanence Prevention Ended Interrupt Enable */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_INTENCLR_OFFSET                (0x04)                                        /**<  (TRAM_INTENCLR) Interrupt Enable Clear  Offset */
#define TRAM_INTENCLR_RESETVALUE            _U_(0x00)                                     /**<  (TRAM_INTENCLR) Interrupt Enable Clear  Reset Value */

#define TRAM_INTENCLR_ERR_Pos               0                                              /**< (TRAM_INTENCLR) TrustRAM Readout Error Interrupt Enable Position */
#define TRAM_INTENCLR_ERR_Msk               (_U_(0x1) << TRAM_INTENCLR_ERR_Pos)            /**< (TRAM_INTENCLR) TrustRAM Readout Error Interrupt Enable Mask */
#define TRAM_INTENCLR_ERR                   TRAM_INTENCLR_ERR_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTENCLR_ERR_Msk instead */
#define TRAM_INTENCLR_DRP_Pos               1                                              /**< (TRAM_INTENCLR) Data Remanence Prevention Ended Interrupt Enable Position */
#define TRAM_INTENCLR_DRP_Msk               (_U_(0x1) << TRAM_INTENCLR_DRP_Pos)            /**< (TRAM_INTENCLR) Data Remanence Prevention Ended Interrupt Enable Mask */
#define TRAM_INTENCLR_DRP                   TRAM_INTENCLR_DRP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTENCLR_DRP_Msk instead */
#define TRAM_INTENCLR_MASK                  _U_(0x03)                                      /**< \deprecated (TRAM_INTENCLR) Register MASK  (Use TRAM_INTENCLR_Msk instead)  */
#define TRAM_INTENCLR_Msk                   _U_(0x03)                                      /**< (TRAM_INTENCLR) Register Mask  */


/* -------- TRAM_INTENSET : (TRAM Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ERR:1;                     /**< bit:      0  TrustRAM Readout Error Interrupt Enable  */
    uint8_t  DRP:1;                     /**< bit:      1  Data Remanence Prevention Ended Interrupt Enable */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_INTENSET_OFFSET                (0x05)                                        /**<  (TRAM_INTENSET) Interrupt Enable Set  Offset */
#define TRAM_INTENSET_RESETVALUE            _U_(0x00)                                     /**<  (TRAM_INTENSET) Interrupt Enable Set  Reset Value */

#define TRAM_INTENSET_ERR_Pos               0                                              /**< (TRAM_INTENSET) TrustRAM Readout Error Interrupt Enable Position */
#define TRAM_INTENSET_ERR_Msk               (_U_(0x1) << TRAM_INTENSET_ERR_Pos)            /**< (TRAM_INTENSET) TrustRAM Readout Error Interrupt Enable Mask */
#define TRAM_INTENSET_ERR                   TRAM_INTENSET_ERR_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTENSET_ERR_Msk instead */
#define TRAM_INTENSET_DRP_Pos               1                                              /**< (TRAM_INTENSET) Data Remanence Prevention Ended Interrupt Enable Position */
#define TRAM_INTENSET_DRP_Msk               (_U_(0x1) << TRAM_INTENSET_DRP_Pos)            /**< (TRAM_INTENSET) Data Remanence Prevention Ended Interrupt Enable Mask */
#define TRAM_INTENSET_DRP                   TRAM_INTENSET_DRP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTENSET_DRP_Msk instead */
#define TRAM_INTENSET_MASK                  _U_(0x03)                                      /**< \deprecated (TRAM_INTENSET) Register MASK  (Use TRAM_INTENSET_Msk instead)  */
#define TRAM_INTENSET_Msk                   _U_(0x03)                                      /**< (TRAM_INTENSET) Register Mask  */


/* -------- TRAM_INTFLAG : (TRAM Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t ERR:1;                     /**< bit:      0  TrustRAM Readout Error                   */
    __I uint8_t DRP:1;                     /**< bit:      1  Data Remanence Prevention Ended          */
    __I uint8_t :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_INTFLAG_OFFSET                 (0x06)                                        /**<  (TRAM_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define TRAM_INTFLAG_RESETVALUE             _U_(0x00)                                     /**<  (TRAM_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define TRAM_INTFLAG_ERR_Pos                0                                              /**< (TRAM_INTFLAG) TrustRAM Readout Error Position */
#define TRAM_INTFLAG_ERR_Msk                (_U_(0x1) << TRAM_INTFLAG_ERR_Pos)             /**< (TRAM_INTFLAG) TrustRAM Readout Error Mask */
#define TRAM_INTFLAG_ERR                    TRAM_INTFLAG_ERR_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTFLAG_ERR_Msk instead */
#define TRAM_INTFLAG_DRP_Pos                1                                              /**< (TRAM_INTFLAG) Data Remanence Prevention Ended Position */
#define TRAM_INTFLAG_DRP_Msk                (_U_(0x1) << TRAM_INTFLAG_DRP_Pos)             /**< (TRAM_INTFLAG) Data Remanence Prevention Ended Mask */
#define TRAM_INTFLAG_DRP                    TRAM_INTFLAG_DRP_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_INTFLAG_DRP_Msk instead */
#define TRAM_INTFLAG_MASK                   _U_(0x03)                                      /**< \deprecated (TRAM_INTFLAG) Register MASK  (Use TRAM_INTFLAG_Msk instead)  */
#define TRAM_INTFLAG_Msk                    _U_(0x03)                                      /**< (TRAM_INTFLAG) Register Mask  */


/* -------- TRAM_STATUS : (TRAM Offset: 0x07) (R/ 8) Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RAMINV:1;                  /**< bit:      0  RAM Inversion Bit                        */
    uint8_t  DRP:1;                     /**< bit:      1  Data Remanence Prevention Ongoing        */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_STATUS_OFFSET                  (0x07)                                        /**<  (TRAM_STATUS) Status  Offset */
#define TRAM_STATUS_RESETVALUE              _U_(0x00)                                     /**<  (TRAM_STATUS) Status  Reset Value */

#define TRAM_STATUS_RAMINV_Pos              0                                              /**< (TRAM_STATUS) RAM Inversion Bit Position */
#define TRAM_STATUS_RAMINV_Msk              (_U_(0x1) << TRAM_STATUS_RAMINV_Pos)           /**< (TRAM_STATUS) RAM Inversion Bit Mask */
#define TRAM_STATUS_RAMINV                  TRAM_STATUS_RAMINV_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_STATUS_RAMINV_Msk instead */
#define TRAM_STATUS_DRP_Pos                 1                                              /**< (TRAM_STATUS) Data Remanence Prevention Ongoing Position */
#define TRAM_STATUS_DRP_Msk                 (_U_(0x1) << TRAM_STATUS_DRP_Pos)              /**< (TRAM_STATUS) Data Remanence Prevention Ongoing Mask */
#define TRAM_STATUS_DRP                     TRAM_STATUS_DRP_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_STATUS_DRP_Msk instead */
#define TRAM_STATUS_MASK                    _U_(0x03)                                      /**< \deprecated (TRAM_STATUS) Register MASK  (Use TRAM_STATUS_Msk instead)  */
#define TRAM_STATUS_Msk                     _U_(0x03)                                      /**< (TRAM_STATUS) Register Mask  */


/* -------- TRAM_SYNCBUSY : (TRAM Offset: 0x08) (R/ 32) Synchronization Busy Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Busy                      */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Busy                              */
    uint32_t :30;                       /**< bit:  2..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} TRAM_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_SYNCBUSY_OFFSET                (0x08)                                        /**<  (TRAM_SYNCBUSY) Synchronization Busy Status  Offset */
#define TRAM_SYNCBUSY_RESETVALUE            _U_(0x00)                                     /**<  (TRAM_SYNCBUSY) Synchronization Busy Status  Reset Value */

#define TRAM_SYNCBUSY_SWRST_Pos             0                                              /**< (TRAM_SYNCBUSY) Software Reset Busy Position */
#define TRAM_SYNCBUSY_SWRST_Msk             (_U_(0x1) << TRAM_SYNCBUSY_SWRST_Pos)          /**< (TRAM_SYNCBUSY) Software Reset Busy Mask */
#define TRAM_SYNCBUSY_SWRST                 TRAM_SYNCBUSY_SWRST_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_SYNCBUSY_SWRST_Msk instead */
#define TRAM_SYNCBUSY_ENABLE_Pos            1                                              /**< (TRAM_SYNCBUSY) Enable Busy Position */
#define TRAM_SYNCBUSY_ENABLE_Msk            (_U_(0x1) << TRAM_SYNCBUSY_ENABLE_Pos)         /**< (TRAM_SYNCBUSY) Enable Busy Mask */
#define TRAM_SYNCBUSY_ENABLE                TRAM_SYNCBUSY_ENABLE_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_SYNCBUSY_ENABLE_Msk instead */
#define TRAM_SYNCBUSY_MASK                  _U_(0x03)                                      /**< \deprecated (TRAM_SYNCBUSY) Register MASK  (Use TRAM_SYNCBUSY_Msk instead)  */
#define TRAM_SYNCBUSY_Msk                   _U_(0x03)                                      /**< (TRAM_SYNCBUSY) Register Mask  */


/* -------- TRAM_DSCC : (TRAM Offset: 0x0c) (/W 32) Data Scramble Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DSCKEY:30;                 /**< bit:  0..29  Data Scramble Key                        */
    uint32_t :1;                        /**< bit:     30  Reserved */
    uint32_t DSCEN:1;                   /**< bit:     31  Data Scramble Enable                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} TRAM_DSCC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_DSCC_OFFSET                    (0x0C)                                        /**<  (TRAM_DSCC) Data Scramble Control  Offset */
#define TRAM_DSCC_RESETVALUE                _U_(0x00)                                     /**<  (TRAM_DSCC) Data Scramble Control  Reset Value */

#define TRAM_DSCC_DSCKEY_Pos                0                                              /**< (TRAM_DSCC) Data Scramble Key Position */
#define TRAM_DSCC_DSCKEY_Msk                (_U_(0x3FFFFFFF) << TRAM_DSCC_DSCKEY_Pos)      /**< (TRAM_DSCC) Data Scramble Key Mask */
#define TRAM_DSCC_DSCKEY(value)             (TRAM_DSCC_DSCKEY_Msk & ((value) << TRAM_DSCC_DSCKEY_Pos))
#define TRAM_DSCC_DSCEN_Pos                 31                                             /**< (TRAM_DSCC) Data Scramble Enable Position */
#define TRAM_DSCC_DSCEN_Msk                 (_U_(0x1) << TRAM_DSCC_DSCEN_Pos)              /**< (TRAM_DSCC) Data Scramble Enable Mask */
#define TRAM_DSCC_DSCEN                     TRAM_DSCC_DSCEN_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use TRAM_DSCC_DSCEN_Msk instead */
#define TRAM_DSCC_MASK                      _U_(0xBFFFFFFF)                                /**< \deprecated (TRAM_DSCC) Register MASK  (Use TRAM_DSCC_Msk instead)  */
#define TRAM_DSCC_Msk                       _U_(0xBFFFFFFF)                                /**< (TRAM_DSCC) Register Mask  */


/* -------- TRAM_PERMW : (TRAM Offset: 0x10) (/W 8) Permutation Write -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATA:3;                    /**< bit:   0..2  Permutation Scrambler Data Input         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_PERMW_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_PERMW_OFFSET                   (0x10)                                        /**<  (TRAM_PERMW) Permutation Write  Offset */
#define TRAM_PERMW_RESETVALUE               _U_(0x00)                                     /**<  (TRAM_PERMW) Permutation Write  Reset Value */

#define TRAM_PERMW_DATA_Pos                 0                                              /**< (TRAM_PERMW) Permutation Scrambler Data Input Position */
#define TRAM_PERMW_DATA_Msk                 (_U_(0x7) << TRAM_PERMW_DATA_Pos)              /**< (TRAM_PERMW) Permutation Scrambler Data Input Mask */
#define TRAM_PERMW_DATA(value)              (TRAM_PERMW_DATA_Msk & ((value) << TRAM_PERMW_DATA_Pos))
#define TRAM_PERMW_MASK                     _U_(0x07)                                      /**< \deprecated (TRAM_PERMW) Register MASK  (Use TRAM_PERMW_Msk instead)  */
#define TRAM_PERMW_Msk                      _U_(0x07)                                      /**< (TRAM_PERMW) Register Mask  */


/* -------- TRAM_PERMR : (TRAM Offset: 0x11) (R/ 8) Permutation Read -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATA:3;                    /**< bit:   0..2  Permutation Scrambler Data Output        */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} TRAM_PERMR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_PERMR_OFFSET                   (0x11)                                        /**<  (TRAM_PERMR) Permutation Read  Offset */
#define TRAM_PERMR_RESETVALUE               _U_(0x00)                                     /**<  (TRAM_PERMR) Permutation Read  Reset Value */

#define TRAM_PERMR_DATA_Pos                 0                                              /**< (TRAM_PERMR) Permutation Scrambler Data Output Position */
#define TRAM_PERMR_DATA_Msk                 (_U_(0x7) << TRAM_PERMR_DATA_Pos)              /**< (TRAM_PERMR) Permutation Scrambler Data Output Mask */
#define TRAM_PERMR_DATA(value)              (TRAM_PERMR_DATA_Msk & ((value) << TRAM_PERMR_DATA_Pos))
#define TRAM_PERMR_MASK                     _U_(0x07)                                      /**< \deprecated (TRAM_PERMR) Register MASK  (Use TRAM_PERMR_Msk instead)  */
#define TRAM_PERMR_Msk                      _U_(0x07)                                      /**< (TRAM_PERMR) Register Mask  */


/* -------- TRAM_RAM : (TRAM Offset: 0x100) (R/W 32) TrustRAM -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:32;                   /**< bit:  0..31  Trust RAM Data                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} TRAM_RAM_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TRAM_RAM_OFFSET                     (0x100)                                       /**<  (TRAM_RAM) TrustRAM  Offset */
#define TRAM_RAM_RESETVALUE                 _U_(0x00)                                     /**<  (TRAM_RAM) TrustRAM  Reset Value */

#define TRAM_RAM_DATA_Pos                   0                                              /**< (TRAM_RAM) Trust RAM Data Position */
#define TRAM_RAM_DATA_Msk                   (_U_(0xFFFFFFFF) << TRAM_RAM_DATA_Pos)         /**< (TRAM_RAM) Trust RAM Data Mask */
#define TRAM_RAM_DATA(value)                (TRAM_RAM_DATA_Msk & ((value) << TRAM_RAM_DATA_Pos))
#define TRAM_RAM_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (TRAM_RAM) Register MASK  (Use TRAM_RAM_Msk instead)  */
#define TRAM_RAM_Msk                        _U_(0xFFFFFFFF)                                /**< (TRAM_RAM) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief TRAM hardware registers */
typedef struct {  /* TrustRAM */
  __IO TRAM_CTRLA_Type                CTRLA;          /**< Offset: 0x00 (R/W   8) Control */
  __I  uint8_t                        Reserved1[3];
  __IO TRAM_INTENCLR_Type             INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO TRAM_INTENSET_Type             INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO TRAM_INTFLAG_Type              INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  TRAM_STATUS_Type               STATUS;         /**< Offset: 0x07 (R/    8) Status */
  __I  TRAM_SYNCBUSY_Type             SYNCBUSY;       /**< Offset: 0x08 (R/   32) Synchronization Busy Status */
  __O  TRAM_DSCC_Type                 DSCC;           /**< Offset: 0x0C ( /W  32) Data Scramble Control */
  __O  TRAM_PERMW_Type                PERMW;          /**< Offset: 0x10 ( /W   8) Permutation Write */
  __I  TRAM_PERMR_Type                PERMR;          /**< Offset: 0x11 (R/    8) Permutation Read */
  __I  uint8_t                        Reserved2[238];
  __IO TRAM_RAM_Type                  RAM[64];        /**< Offset: 0x100 (R/W  32) TrustRAM */
} Tram;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of TrustRAM */

#endif /* _SAML10_TRAM_COMPONENT_H_ */
