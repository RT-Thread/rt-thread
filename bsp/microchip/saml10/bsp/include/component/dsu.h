/**
 * \file
 *
 * \brief Component description for DSU
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
#ifndef _SAML10_DSU_COMPONENT_H_
#define _SAML10_DSU_COMPONENT_H_
#define _SAML10_DSU_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Device Service Unit
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR DSU */
/* ========================================================================== */

#define DSU_U2810                      /**< (DSU) Module ID */
#define REV_DSU 0x100                  /**< (DSU) Module revision */

/* -------- DSU_CTRL : (DSU Offset: 0x00) (/W 8) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  :1;                        /**< bit:      1  Reserved */
    uint8_t  CRC:1;                     /**< bit:      2  32-bit Cyclic Redundancy Code            */
    uint8_t  MBIST:1;                   /**< bit:      3  Memory built-in self-test                */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DSU_CTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CTRL_OFFSET                     (0x00)                                        /**<  (DSU_CTRL) Control  Offset */
#define DSU_CTRL_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_CTRL) Control  Reset Value */

#define DSU_CTRL_SWRST_Pos                  0                                              /**< (DSU_CTRL) Software Reset Position */
#define DSU_CTRL_SWRST_Msk                  (_U_(0x1) << DSU_CTRL_SWRST_Pos)               /**< (DSU_CTRL) Software Reset Mask */
#define DSU_CTRL_SWRST                      DSU_CTRL_SWRST_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_CTRL_SWRST_Msk instead */
#define DSU_CTRL_CRC_Pos                    2                                              /**< (DSU_CTRL) 32-bit Cyclic Redundancy Code Position */
#define DSU_CTRL_CRC_Msk                    (_U_(0x1) << DSU_CTRL_CRC_Pos)                 /**< (DSU_CTRL) 32-bit Cyclic Redundancy Code Mask */
#define DSU_CTRL_CRC                        DSU_CTRL_CRC_Msk                               /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_CTRL_CRC_Msk instead */
#define DSU_CTRL_MBIST_Pos                  3                                              /**< (DSU_CTRL) Memory built-in self-test Position */
#define DSU_CTRL_MBIST_Msk                  (_U_(0x1) << DSU_CTRL_MBIST_Pos)               /**< (DSU_CTRL) Memory built-in self-test Mask */
#define DSU_CTRL_MBIST                      DSU_CTRL_MBIST_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_CTRL_MBIST_Msk instead */
#define DSU_CTRL_MASK                       _U_(0x0D)                                      /**< \deprecated (DSU_CTRL) Register MASK  (Use DSU_CTRL_Msk instead)  */
#define DSU_CTRL_Msk                        _U_(0x0D)                                      /**< (DSU_CTRL) Register Mask  */


/* -------- DSU_STATUSA : (DSU Offset: 0x01) (R/W 8) Status A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DONE:1;                    /**< bit:      0  Done                                     */
    uint8_t  CRSTEXT:1;                 /**< bit:      1  CPU Reset Phase Extension                */
    uint8_t  BERR:1;                    /**< bit:      2  Bus Error                                */
    uint8_t  FAIL:1;                    /**< bit:      3  Failure                                  */
    uint8_t  PERR:1;                    /**< bit:      4  Protection Error Detected by the State Machine */
    uint8_t  BREXT:1;                   /**< bit:      5  BootRom Phase Extension                  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DSU_STATUSA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_STATUSA_OFFSET                  (0x01)                                        /**<  (DSU_STATUSA) Status A  Offset */
#define DSU_STATUSA_RESETVALUE              _U_(0x00)                                     /**<  (DSU_STATUSA) Status A  Reset Value */

#define DSU_STATUSA_DONE_Pos                0                                              /**< (DSU_STATUSA) Done Position */
#define DSU_STATUSA_DONE_Msk                (_U_(0x1) << DSU_STATUSA_DONE_Pos)             /**< (DSU_STATUSA) Done Mask */
#define DSU_STATUSA_DONE                    DSU_STATUSA_DONE_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_DONE_Msk instead */
#define DSU_STATUSA_CRSTEXT_Pos             1                                              /**< (DSU_STATUSA) CPU Reset Phase Extension Position */
#define DSU_STATUSA_CRSTEXT_Msk             (_U_(0x1) << DSU_STATUSA_CRSTEXT_Pos)          /**< (DSU_STATUSA) CPU Reset Phase Extension Mask */
#define DSU_STATUSA_CRSTEXT                 DSU_STATUSA_CRSTEXT_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_CRSTEXT_Msk instead */
#define DSU_STATUSA_BERR_Pos                2                                              /**< (DSU_STATUSA) Bus Error Position */
#define DSU_STATUSA_BERR_Msk                (_U_(0x1) << DSU_STATUSA_BERR_Pos)             /**< (DSU_STATUSA) Bus Error Mask */
#define DSU_STATUSA_BERR                    DSU_STATUSA_BERR_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_BERR_Msk instead */
#define DSU_STATUSA_FAIL_Pos                3                                              /**< (DSU_STATUSA) Failure Position */
#define DSU_STATUSA_FAIL_Msk                (_U_(0x1) << DSU_STATUSA_FAIL_Pos)             /**< (DSU_STATUSA) Failure Mask */
#define DSU_STATUSA_FAIL                    DSU_STATUSA_FAIL_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_FAIL_Msk instead */
#define DSU_STATUSA_PERR_Pos                4                                              /**< (DSU_STATUSA) Protection Error Detected by the State Machine Position */
#define DSU_STATUSA_PERR_Msk                (_U_(0x1) << DSU_STATUSA_PERR_Pos)             /**< (DSU_STATUSA) Protection Error Detected by the State Machine Mask */
#define DSU_STATUSA_PERR                    DSU_STATUSA_PERR_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_PERR_Msk instead */
#define DSU_STATUSA_BREXT_Pos               5                                              /**< (DSU_STATUSA) BootRom Phase Extension Position */
#define DSU_STATUSA_BREXT_Msk               (_U_(0x1) << DSU_STATUSA_BREXT_Pos)            /**< (DSU_STATUSA) BootRom Phase Extension Mask */
#define DSU_STATUSA_BREXT                   DSU_STATUSA_BREXT_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSA_BREXT_Msk instead */
#define DSU_STATUSA_MASK                    _U_(0x3F)                                      /**< \deprecated (DSU_STATUSA) Register MASK  (Use DSU_STATUSA_Msk instead)  */
#define DSU_STATUSA_Msk                     _U_(0x3F)                                      /**< (DSU_STATUSA) Register Mask  */


/* -------- DSU_STATUSB : (DSU Offset: 0x02) (R/ 8) Status B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DAL:2;                     /**< bit:   0..1  Debugger Access Level                    */
    uint8_t  DBGPRES:1;                 /**< bit:      2  Debugger Present                         */
    uint8_t  HPE:1;                     /**< bit:      3  Hot-Plugging Enable                      */
    uint8_t  DCCD0:1;                   /**< bit:      4  Debug Communication Channel 0 Dirty      */
    uint8_t  DCCD1:1;                   /**< bit:      5  Debug Communication Channel 1 Dirty      */
    uint8_t  BCCD0:1;                   /**< bit:      6  Boot ROM Communication Channel 0 Dirty   */
    uint8_t  BCCD1:1;                   /**< bit:      7  Boot ROM Communication Channel 1 Dirty   */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  :4;                        /**< bit:   0..3  Reserved */
    uint8_t  DCCD:2;                    /**< bit:   4..5  Debug Communication Channel x Dirty      */
    uint8_t  BCCD:2;                    /**< bit:   6..7  Boot ROM Communication Channel x Dirty   */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} DSU_STATUSB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_STATUSB_OFFSET                  (0x02)                                        /**<  (DSU_STATUSB) Status B  Offset */
#define DSU_STATUSB_RESETVALUE              _U_(0x00)                                     /**<  (DSU_STATUSB) Status B  Reset Value */

#define DSU_STATUSB_DAL_Pos                 0                                              /**< (DSU_STATUSB) Debugger Access Level Position */
#define DSU_STATUSB_DAL_Msk                 (_U_(0x3) << DSU_STATUSB_DAL_Pos)              /**< (DSU_STATUSB) Debugger Access Level Mask */
#define DSU_STATUSB_DAL(value)              (DSU_STATUSB_DAL_Msk & ((value) << DSU_STATUSB_DAL_Pos))
#define   DSU_STATUSB_DAL_SECURED_Val       _U_(0x0)                                       /**< (DSU_STATUSB)   */
#define   DSU_STATUSB_DAL_NS_DEBUG_Val      _U_(0x1)                                       /**< (DSU_STATUSB)   */
#define   DSU_STATUSB_DAL_FULL_DEBUG_Val    _U_(0x2)                                       /**< (DSU_STATUSB)   */
#define DSU_STATUSB_DAL_SECURED             (DSU_STATUSB_DAL_SECURED_Val << DSU_STATUSB_DAL_Pos)  /**< (DSU_STATUSB)  Position  */
#define DSU_STATUSB_DAL_NS_DEBUG            (DSU_STATUSB_DAL_NS_DEBUG_Val << DSU_STATUSB_DAL_Pos)  /**< (DSU_STATUSB)  Position  */
#define DSU_STATUSB_DAL_FULL_DEBUG          (DSU_STATUSB_DAL_FULL_DEBUG_Val << DSU_STATUSB_DAL_Pos)  /**< (DSU_STATUSB)  Position  */
#define DSU_STATUSB_DBGPRES_Pos             2                                              /**< (DSU_STATUSB) Debugger Present Position */
#define DSU_STATUSB_DBGPRES_Msk             (_U_(0x1) << DSU_STATUSB_DBGPRES_Pos)          /**< (DSU_STATUSB) Debugger Present Mask */
#define DSU_STATUSB_DBGPRES                 DSU_STATUSB_DBGPRES_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_DBGPRES_Msk instead */
#define DSU_STATUSB_HPE_Pos                 3                                              /**< (DSU_STATUSB) Hot-Plugging Enable Position */
#define DSU_STATUSB_HPE_Msk                 (_U_(0x1) << DSU_STATUSB_HPE_Pos)              /**< (DSU_STATUSB) Hot-Plugging Enable Mask */
#define DSU_STATUSB_HPE                     DSU_STATUSB_HPE_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_HPE_Msk instead */
#define DSU_STATUSB_DCCD0_Pos               4                                              /**< (DSU_STATUSB) Debug Communication Channel 0 Dirty Position */
#define DSU_STATUSB_DCCD0_Msk               (_U_(0x1) << DSU_STATUSB_DCCD0_Pos)            /**< (DSU_STATUSB) Debug Communication Channel 0 Dirty Mask */
#define DSU_STATUSB_DCCD0                   DSU_STATUSB_DCCD0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_DCCD0_Msk instead */
#define DSU_STATUSB_DCCD1_Pos               5                                              /**< (DSU_STATUSB) Debug Communication Channel 1 Dirty Position */
#define DSU_STATUSB_DCCD1_Msk               (_U_(0x1) << DSU_STATUSB_DCCD1_Pos)            /**< (DSU_STATUSB) Debug Communication Channel 1 Dirty Mask */
#define DSU_STATUSB_DCCD1                   DSU_STATUSB_DCCD1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_DCCD1_Msk instead */
#define DSU_STATUSB_BCCD0_Pos               6                                              /**< (DSU_STATUSB) Boot ROM Communication Channel 0 Dirty Position */
#define DSU_STATUSB_BCCD0_Msk               (_U_(0x1) << DSU_STATUSB_BCCD0_Pos)            /**< (DSU_STATUSB) Boot ROM Communication Channel 0 Dirty Mask */
#define DSU_STATUSB_BCCD0                   DSU_STATUSB_BCCD0_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_BCCD0_Msk instead */
#define DSU_STATUSB_BCCD1_Pos               7                                              /**< (DSU_STATUSB) Boot ROM Communication Channel 1 Dirty Position */
#define DSU_STATUSB_BCCD1_Msk               (_U_(0x1) << DSU_STATUSB_BCCD1_Pos)            /**< (DSU_STATUSB) Boot ROM Communication Channel 1 Dirty Mask */
#define DSU_STATUSB_BCCD1                   DSU_STATUSB_BCCD1_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_STATUSB_BCCD1_Msk instead */
#define DSU_STATUSB_MASK                    _U_(0xFF)                                      /**< \deprecated (DSU_STATUSB) Register MASK  (Use DSU_STATUSB_Msk instead)  */
#define DSU_STATUSB_Msk                     _U_(0xFF)                                      /**< (DSU_STATUSB) Register Mask  */

#define DSU_STATUSB_DCCD_Pos                4                                              /**< (DSU_STATUSB Position) Debug Communication Channel x Dirty */
#define DSU_STATUSB_DCCD_Msk                (_U_(0x3) << DSU_STATUSB_DCCD_Pos)             /**< (DSU_STATUSB Mask) DCCD */
#define DSU_STATUSB_DCCD(value)             (DSU_STATUSB_DCCD_Msk & ((value) << DSU_STATUSB_DCCD_Pos))  
#define DSU_STATUSB_BCCD_Pos                6                                              /**< (DSU_STATUSB Position) Boot ROM Communication Channel x Dirty */
#define DSU_STATUSB_BCCD_Msk                (_U_(0x3) << DSU_STATUSB_BCCD_Pos)             /**< (DSU_STATUSB Mask) BCCD */
#define DSU_STATUSB_BCCD(value)             (DSU_STATUSB_BCCD_Msk & ((value) << DSU_STATUSB_BCCD_Pos))  

/* -------- DSU_STATUSC : (DSU Offset: 0x03) (R/ 8) Status C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint8_t  reg;                         /**< Type used for register access */
} DSU_STATUSC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_STATUSC_OFFSET                  (0x03)                                        /**<  (DSU_STATUSC) Status C  Offset */
#define DSU_STATUSC_RESETVALUE              _U_(0x00)                                     /**<  (DSU_STATUSC) Status C  Reset Value */

#define DSU_STATUSC_MASK                    _U_(0x00)                                      /**< \deprecated (DSU_STATUSC) Register MASK  (Use DSU_STATUSC_Msk instead)  */
#define DSU_STATUSC_Msk                     _U_(0x00)                                      /**< (DSU_STATUSC) Register Mask  */


/* -------- DSU_ADDR : (DSU Offset: 0x04) (R/W 32) Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t AMOD:2;                    /**< bit:   0..1  Access Mode                              */
    uint32_t ADDR:30;                   /**< bit:  2..31  Address                                  */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_ADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_ADDR_OFFSET                     (0x04)                                        /**<  (DSU_ADDR) Address  Offset */
#define DSU_ADDR_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_ADDR) Address  Reset Value */

#define DSU_ADDR_AMOD_Pos                   0                                              /**< (DSU_ADDR) Access Mode Position */
#define DSU_ADDR_AMOD_Msk                   (_U_(0x3) << DSU_ADDR_AMOD_Pos)                /**< (DSU_ADDR) Access Mode Mask */
#define DSU_ADDR_AMOD(value)                (DSU_ADDR_AMOD_Msk & ((value) << DSU_ADDR_AMOD_Pos))
#define DSU_ADDR_ADDR_Pos                   2                                              /**< (DSU_ADDR) Address Position */
#define DSU_ADDR_ADDR_Msk                   (_U_(0x3FFFFFFF) << DSU_ADDR_ADDR_Pos)         /**< (DSU_ADDR) Address Mask */
#define DSU_ADDR_ADDR(value)                (DSU_ADDR_ADDR_Msk & ((value) << DSU_ADDR_ADDR_Pos))
#define DSU_ADDR_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_ADDR) Register MASK  (Use DSU_ADDR_Msk instead)  */
#define DSU_ADDR_Msk                        _U_(0xFFFFFFFF)                                /**< (DSU_ADDR) Register Mask  */


/* -------- DSU_LENGTH : (DSU Offset: 0x08) (R/W 32) Length -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :2;                        /**< bit:   0..1  Reserved */
    uint32_t LENGTH:30;                 /**< bit:  2..31  Length                                   */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_LENGTH_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_LENGTH_OFFSET                   (0x08)                                        /**<  (DSU_LENGTH) Length  Offset */
#define DSU_LENGTH_RESETVALUE               _U_(0x00)                                     /**<  (DSU_LENGTH) Length  Reset Value */

#define DSU_LENGTH_LENGTH_Pos               2                                              /**< (DSU_LENGTH) Length Position */
#define DSU_LENGTH_LENGTH_Msk               (_U_(0x3FFFFFFF) << DSU_LENGTH_LENGTH_Pos)     /**< (DSU_LENGTH) Length Mask */
#define DSU_LENGTH_LENGTH(value)            (DSU_LENGTH_LENGTH_Msk & ((value) << DSU_LENGTH_LENGTH_Pos))
#define DSU_LENGTH_MASK                     _U_(0xFFFFFFFC)                                /**< \deprecated (DSU_LENGTH) Register MASK  (Use DSU_LENGTH_Msk instead)  */
#define DSU_LENGTH_Msk                      _U_(0xFFFFFFFC)                                /**< (DSU_LENGTH) Register Mask  */


/* -------- DSU_DATA : (DSU Offset: 0x0c) (R/W 32) Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:32;                   /**< bit:  0..31  Data                                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_DATA_OFFSET                     (0x0C)                                        /**<  (DSU_DATA) Data  Offset */
#define DSU_DATA_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_DATA) Data  Reset Value */

#define DSU_DATA_DATA_Pos                   0                                              /**< (DSU_DATA) Data Position */
#define DSU_DATA_DATA_Msk                   (_U_(0xFFFFFFFF) << DSU_DATA_DATA_Pos)         /**< (DSU_DATA) Data Mask */
#define DSU_DATA_DATA(value)                (DSU_DATA_DATA_Msk & ((value) << DSU_DATA_DATA_Pos))
#define DSU_DATA_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_DATA) Register MASK  (Use DSU_DATA_Msk instead)  */
#define DSU_DATA_Msk                        _U_(0xFFFFFFFF)                                /**< (DSU_DATA) Register Mask  */


/* -------- DSU_DCC : (DSU Offset: 0x10) (R/W 32) Debug Communication Channel n -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:32;                   /**< bit:  0..31  Data                                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_DCC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_DCC_OFFSET                      (0x10)                                        /**<  (DSU_DCC) Debug Communication Channel n  Offset */
#define DSU_DCC_RESETVALUE                  _U_(0x00)                                     /**<  (DSU_DCC) Debug Communication Channel n  Reset Value */

#define DSU_DCC_DATA_Pos                    0                                              /**< (DSU_DCC) Data Position */
#define DSU_DCC_DATA_Msk                    (_U_(0xFFFFFFFF) << DSU_DCC_DATA_Pos)          /**< (DSU_DCC) Data Mask */
#define DSU_DCC_DATA(value)                 (DSU_DCC_DATA_Msk & ((value) << DSU_DCC_DATA_Pos))
#define DSU_DCC_MASK                        _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_DCC) Register MASK  (Use DSU_DCC_Msk instead)  */
#define DSU_DCC_Msk                         _U_(0xFFFFFFFF)                                /**< (DSU_DCC) Register Mask  */


/* -------- DSU_DID : (DSU Offset: 0x18) (R/ 32) Device Identification -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DEVSEL:8;                  /**< bit:   0..7  Device Select                            */
    uint32_t REVISION:4;                /**< bit:  8..11  Revision Number                          */
    uint32_t DIE:4;                     /**< bit: 12..15  Die Number                               */
    uint32_t SERIES:6;                  /**< bit: 16..21  Series                                   */
    uint32_t :1;                        /**< bit:     22  Reserved */
    uint32_t FAMILY:5;                  /**< bit: 23..27  Family                                   */
    uint32_t PROCESSOR:4;               /**< bit: 28..31  Processor                                */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_DID_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_DID_OFFSET                      (0x18)                                        /**<  (DSU_DID) Device Identification  Offset */
#define DSU_DID_RESETVALUE                  _U_(0x20840000)                               /**<  (DSU_DID) Device Identification  Reset Value */

#define DSU_DID_DEVSEL_Pos                  0                                              /**< (DSU_DID) Device Select Position */
#define DSU_DID_DEVSEL_Msk                  (_U_(0xFF) << DSU_DID_DEVSEL_Pos)              /**< (DSU_DID) Device Select Mask */
#define DSU_DID_DEVSEL(value)               (DSU_DID_DEVSEL_Msk & ((value) << DSU_DID_DEVSEL_Pos))
#define DSU_DID_REVISION_Pos                8                                              /**< (DSU_DID) Revision Number Position */
#define DSU_DID_REVISION_Msk                (_U_(0xF) << DSU_DID_REVISION_Pos)             /**< (DSU_DID) Revision Number Mask */
#define DSU_DID_REVISION(value)             (DSU_DID_REVISION_Msk & ((value) << DSU_DID_REVISION_Pos))
#define DSU_DID_DIE_Pos                     12                                             /**< (DSU_DID) Die Number Position */
#define DSU_DID_DIE_Msk                     (_U_(0xF) << DSU_DID_DIE_Pos)                  /**< (DSU_DID) Die Number Mask */
#define DSU_DID_DIE(value)                  (DSU_DID_DIE_Msk & ((value) << DSU_DID_DIE_Pos))
#define DSU_DID_SERIES_Pos                  16                                             /**< (DSU_DID) Series Position */
#define DSU_DID_SERIES_Msk                  (_U_(0x3F) << DSU_DID_SERIES_Pos)              /**< (DSU_DID) Series Mask */
#define DSU_DID_SERIES(value)               (DSU_DID_SERIES_Msk & ((value) << DSU_DID_SERIES_Pos))
#define   DSU_DID_SERIES_0_Val              _U_(0x0)                                       /**< (DSU_DID) Cortex-M0+ processor, basic feature set  */
#define   DSU_DID_SERIES_1_Val              _U_(0x1)                                       /**< (DSU_DID) Cortex-M0+ processor, USB  */
#define DSU_DID_SERIES_0                    (DSU_DID_SERIES_0_Val << DSU_DID_SERIES_Pos)   /**< (DSU_DID) Cortex-M0+ processor, basic feature set Position  */
#define DSU_DID_SERIES_1                    (DSU_DID_SERIES_1_Val << DSU_DID_SERIES_Pos)   /**< (DSU_DID) Cortex-M0+ processor, USB Position  */
#define DSU_DID_FAMILY_Pos                  23                                             /**< (DSU_DID) Family Position */
#define DSU_DID_FAMILY_Msk                  (_U_(0x1F) << DSU_DID_FAMILY_Pos)              /**< (DSU_DID) Family Mask */
#define DSU_DID_FAMILY(value)               (DSU_DID_FAMILY_Msk & ((value) << DSU_DID_FAMILY_Pos))
#define   DSU_DID_FAMILY_0_Val              _U_(0x0)                                       /**< (DSU_DID) General purpose microcontroller  */
#define   DSU_DID_FAMILY_1_Val              _U_(0x1)                                       /**< (DSU_DID) PicoPower  */
#define DSU_DID_FAMILY_0                    (DSU_DID_FAMILY_0_Val << DSU_DID_FAMILY_Pos)   /**< (DSU_DID) General purpose microcontroller Position  */
#define DSU_DID_FAMILY_1                    (DSU_DID_FAMILY_1_Val << DSU_DID_FAMILY_Pos)   /**< (DSU_DID) PicoPower Position  */
#define DSU_DID_PROCESSOR_Pos               28                                             /**< (DSU_DID) Processor Position */
#define DSU_DID_PROCESSOR_Msk               (_U_(0xF) << DSU_DID_PROCESSOR_Pos)            /**< (DSU_DID) Processor Mask */
#define DSU_DID_PROCESSOR(value)            (DSU_DID_PROCESSOR_Msk & ((value) << DSU_DID_PROCESSOR_Pos))
#define   DSU_DID_PROCESSOR_CM0P_Val        _U_(0x1)                                       /**< (DSU_DID) Cortex-M0+  */
#define   DSU_DID_PROCESSOR_CM23_Val        _U_(0x2)                                       /**< (DSU_DID) Cortex-M23  */
#define   DSU_DID_PROCESSOR_CM3_Val         _U_(0x3)                                       /**< (DSU_DID) Cortex-M3  */
#define   DSU_DID_PROCESSOR_CM4_Val         _U_(0x5)                                       /**< (DSU_DID) Cortex-M4  */
#define   DSU_DID_PROCESSOR_CM4F_Val        _U_(0x6)                                       /**< (DSU_DID) Cortex-M4 with FPU  */
#define   DSU_DID_PROCESSOR_CM33_Val        _U_(0x7)                                       /**< (DSU_DID) Cortex-M33  */
#define DSU_DID_PROCESSOR_CM0P              (DSU_DID_PROCESSOR_CM0P_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M0+ Position  */
#define DSU_DID_PROCESSOR_CM23              (DSU_DID_PROCESSOR_CM23_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M23 Position  */
#define DSU_DID_PROCESSOR_CM3               (DSU_DID_PROCESSOR_CM3_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M3 Position  */
#define DSU_DID_PROCESSOR_CM4               (DSU_DID_PROCESSOR_CM4_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M4 Position  */
#define DSU_DID_PROCESSOR_CM4F              (DSU_DID_PROCESSOR_CM4F_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M4 with FPU Position  */
#define DSU_DID_PROCESSOR_CM33              (DSU_DID_PROCESSOR_CM33_Val << DSU_DID_PROCESSOR_Pos)  /**< (DSU_DID) Cortex-M33 Position  */
#define DSU_DID_MASK                        _U_(0xFFBFFFFF)                                /**< \deprecated (DSU_DID) Register MASK  (Use DSU_DID_Msk instead)  */
#define DSU_DID_Msk                         _U_(0xFFBFFFFF)                                /**< (DSU_DID) Register Mask  */


/* -------- DSU_CFG : (DSU Offset: 0x1c) (R/W 32) Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t LQOS:2;                    /**< bit:   0..1  Latency Quality Of Service               */
    uint32_t DCCDMALEVEL:2;             /**< bit:   2..3  DMA Trigger Level                        */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_CFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CFG_OFFSET                      (0x1C)                                        /**<  (DSU_CFG) Configuration  Offset */
#define DSU_CFG_RESETVALUE                  _U_(0x02)                                     /**<  (DSU_CFG) Configuration  Reset Value */

#define DSU_CFG_LQOS_Pos                    0                                              /**< (DSU_CFG) Latency Quality Of Service Position */
#define DSU_CFG_LQOS_Msk                    (_U_(0x3) << DSU_CFG_LQOS_Pos)                 /**< (DSU_CFG) Latency Quality Of Service Mask */
#define DSU_CFG_LQOS(value)                 (DSU_CFG_LQOS_Msk & ((value) << DSU_CFG_LQOS_Pos))
#define DSU_CFG_DCCDMALEVEL_Pos             2                                              /**< (DSU_CFG) DMA Trigger Level Position */
#define DSU_CFG_DCCDMALEVEL_Msk             (_U_(0x3) << DSU_CFG_DCCDMALEVEL_Pos)          /**< (DSU_CFG) DMA Trigger Level Mask */
#define DSU_CFG_DCCDMALEVEL(value)          (DSU_CFG_DCCDMALEVEL_Msk & ((value) << DSU_CFG_DCCDMALEVEL_Pos))
#define   DSU_CFG_DCCDMALEVEL_EMPTY_Val     _U_(0x0)                                       /**< (DSU_CFG) Trigger rises when DCC is empty  */
#define   DSU_CFG_DCCDMALEVEL_FULL_Val      _U_(0x1)                                       /**< (DSU_CFG) Trigger rises when DCC is full  */
#define DSU_CFG_DCCDMALEVEL_EMPTY           (DSU_CFG_DCCDMALEVEL_EMPTY_Val << DSU_CFG_DCCDMALEVEL_Pos)  /**< (DSU_CFG) Trigger rises when DCC is empty Position  */
#define DSU_CFG_DCCDMALEVEL_FULL            (DSU_CFG_DCCDMALEVEL_FULL_Val << DSU_CFG_DCCDMALEVEL_Pos)  /**< (DSU_CFG) Trigger rises when DCC is full Position  */
#define DSU_CFG_MASK                        _U_(0x0F)                                      /**< \deprecated (DSU_CFG) Register MASK  (Use DSU_CFG_Msk instead)  */
#define DSU_CFG_Msk                         _U_(0x0F)                                      /**< (DSU_CFG) Register Mask  */


/* -------- DSU_BCC : (DSU Offset: 0x20) (R/W 32) Boot ROM Communication Channel n -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:32;                   /**< bit:  0..31  Data                                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_BCC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_BCC_OFFSET                      (0x20)                                        /**<  (DSU_BCC) Boot ROM Communication Channel n  Offset */
#define DSU_BCC_RESETVALUE                  _U_(0x00)                                     /**<  (DSU_BCC) Boot ROM Communication Channel n  Reset Value */

#define DSU_BCC_DATA_Pos                    0                                              /**< (DSU_BCC) Data Position */
#define DSU_BCC_DATA_Msk                    (_U_(0xFFFFFFFF) << DSU_BCC_DATA_Pos)          /**< (DSU_BCC) Data Mask */
#define DSU_BCC_DATA(value)                 (DSU_BCC_DATA_Msk & ((value) << DSU_BCC_DATA_Pos))
#define DSU_BCC_MASK                        _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_BCC) Register MASK  (Use DSU_BCC_Msk instead)  */
#define DSU_BCC_Msk                         _U_(0xFFFFFFFF)                                /**< (DSU_BCC) Register Mask  */


/* -------- DSU_DCFG : (DSU Offset: 0xf0) (R/W 32) Device Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DCFG:32;                   /**< bit:  0..31  Device Configuration                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_DCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_DCFG_OFFSET                     (0xF0)                                        /**<  (DSU_DCFG) Device Configuration  Offset */
#define DSU_DCFG_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_DCFG) Device Configuration  Reset Value */

#define DSU_DCFG_DCFG_Pos                   0                                              /**< (DSU_DCFG) Device Configuration Position */
#define DSU_DCFG_DCFG_Msk                   (_U_(0xFFFFFFFF) << DSU_DCFG_DCFG_Pos)         /**< (DSU_DCFG) Device Configuration Mask */
#define DSU_DCFG_DCFG(value)                (DSU_DCFG_DCFG_Msk & ((value) << DSU_DCFG_DCFG_Pos))
#define DSU_DCFG_MASK                       _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_DCFG) Register MASK  (Use DSU_DCFG_Msk instead)  */
#define DSU_DCFG_Msk                        _U_(0xFFFFFFFF)                                /**< (DSU_DCFG) Register Mask  */


/* -------- DSU_ENTRY0 : (DSU Offset: 0x1000) (R/ 32) CoreSight ROM Table Entry 0 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EPRES:1;                   /**< bit:      0  Entry Present                            */
    uint32_t FMT:1;                     /**< bit:      1  Format                                   */
    uint32_t :10;                       /**< bit:  2..11  Reserved */
    uint32_t ADDOFF:20;                 /**< bit: 12..31  Address Offset                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_ENTRY0_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_ENTRY0_OFFSET                   (0x1000)                                      /**<  (DSU_ENTRY0) CoreSight ROM Table Entry 0  Offset */
#define DSU_ENTRY0_RESETVALUE               _U_(0x9F0FC002)                               /**<  (DSU_ENTRY0) CoreSight ROM Table Entry 0  Reset Value */

#define DSU_ENTRY0_EPRES_Pos                0                                              /**< (DSU_ENTRY0) Entry Present Position */
#define DSU_ENTRY0_EPRES_Msk                (_U_(0x1) << DSU_ENTRY0_EPRES_Pos)             /**< (DSU_ENTRY0) Entry Present Mask */
#define DSU_ENTRY0_EPRES                    DSU_ENTRY0_EPRES_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_ENTRY0_EPRES_Msk instead */
#define DSU_ENTRY0_FMT_Pos                  1                                              /**< (DSU_ENTRY0) Format Position */
#define DSU_ENTRY0_FMT_Msk                  (_U_(0x1) << DSU_ENTRY0_FMT_Pos)               /**< (DSU_ENTRY0) Format Mask */
#define DSU_ENTRY0_FMT                      DSU_ENTRY0_FMT_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_ENTRY0_FMT_Msk instead */
#define DSU_ENTRY0_ADDOFF_Pos               12                                             /**< (DSU_ENTRY0) Address Offset Position */
#define DSU_ENTRY0_ADDOFF_Msk               (_U_(0xFFFFF) << DSU_ENTRY0_ADDOFF_Pos)        /**< (DSU_ENTRY0) Address Offset Mask */
#define DSU_ENTRY0_ADDOFF(value)            (DSU_ENTRY0_ADDOFF_Msk & ((value) << DSU_ENTRY0_ADDOFF_Pos))
#define DSU_ENTRY0_MASK                     _U_(0xFFFFF003)                                /**< \deprecated (DSU_ENTRY0) Register MASK  (Use DSU_ENTRY0_Msk instead)  */
#define DSU_ENTRY0_Msk                      _U_(0xFFFFF003)                                /**< (DSU_ENTRY0) Register Mask  */


/* -------- DSU_ENTRY1 : (DSU Offset: 0x1004) (R/ 32) CoreSight ROM Table Entry 1 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint32_t reg;                         /**< Type used for register access */
} DSU_ENTRY1_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_ENTRY1_OFFSET                   (0x1004)                                      /**<  (DSU_ENTRY1) CoreSight ROM Table Entry 1  Offset */
#define DSU_ENTRY1_RESETVALUE               _U_(0x00)                                     /**<  (DSU_ENTRY1) CoreSight ROM Table Entry 1  Reset Value */

#define DSU_ENTRY1_MASK                     _U_(0x00)                                      /**< \deprecated (DSU_ENTRY1) Register MASK  (Use DSU_ENTRY1_Msk instead)  */
#define DSU_ENTRY1_Msk                      _U_(0x00)                                      /**< (DSU_ENTRY1) Register Mask  */


/* -------- DSU_END : (DSU Offset: 0x1008) (R/ 32) CoreSight ROM Table End -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t END:32;                    /**< bit:  0..31  End Marker                               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_END_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_END_OFFSET                      (0x1008)                                      /**<  (DSU_END) CoreSight ROM Table End  Offset */
#define DSU_END_RESETVALUE                  _U_(0x00)                                     /**<  (DSU_END) CoreSight ROM Table End  Reset Value */

#define DSU_END_END_Pos                     0                                              /**< (DSU_END) End Marker Position */
#define DSU_END_END_Msk                     (_U_(0xFFFFFFFF) << DSU_END_END_Pos)           /**< (DSU_END) End Marker Mask */
#define DSU_END_END(value)                  (DSU_END_END_Msk & ((value) << DSU_END_END_Pos))
#define DSU_END_MASK                        _U_(0xFFFFFFFF)                                /**< \deprecated (DSU_END) Register MASK  (Use DSU_END_Msk instead)  */
#define DSU_END_Msk                         _U_(0xFFFFFFFF)                                /**< (DSU_END) Register Mask  */


/* -------- DSU_MEMTYPE : (DSU Offset: 0x1fcc) (R/ 32) CoreSight ROM Table Memory Type -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SMEMP:1;                   /**< bit:      0  System Memory Present                    */
    uint32_t :31;                       /**< bit:  1..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_MEMTYPE_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_MEMTYPE_OFFSET                  (0x1FCC)                                      /**<  (DSU_MEMTYPE) CoreSight ROM Table Memory Type  Offset */
#define DSU_MEMTYPE_RESETVALUE              _U_(0x00)                                     /**<  (DSU_MEMTYPE) CoreSight ROM Table Memory Type  Reset Value */

#define DSU_MEMTYPE_SMEMP_Pos               0                                              /**< (DSU_MEMTYPE) System Memory Present Position */
#define DSU_MEMTYPE_SMEMP_Msk               (_U_(0x1) << DSU_MEMTYPE_SMEMP_Pos)            /**< (DSU_MEMTYPE) System Memory Present Mask */
#define DSU_MEMTYPE_SMEMP                   DSU_MEMTYPE_SMEMP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_MEMTYPE_SMEMP_Msk instead */
#define DSU_MEMTYPE_MASK                    _U_(0x01)                                      /**< \deprecated (DSU_MEMTYPE) Register MASK  (Use DSU_MEMTYPE_Msk instead)  */
#define DSU_MEMTYPE_Msk                     _U_(0x01)                                      /**< (DSU_MEMTYPE) Register Mask  */


/* -------- DSU_PID4 : (DSU Offset: 0x1fd0) (R/ 32) Peripheral Identification 4 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t JEPCC:4;                   /**< bit:   0..3  JEP-106 Continuation Code                */
    uint32_t FKBC:4;                    /**< bit:   4..7  4KB count                                */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID4_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID4_OFFSET                     (0x1FD0)                                      /**<  (DSU_PID4) Peripheral Identification 4  Offset */
#define DSU_PID4_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_PID4) Peripheral Identification 4  Reset Value */

#define DSU_PID4_JEPCC_Pos                  0                                              /**< (DSU_PID4) JEP-106 Continuation Code Position */
#define DSU_PID4_JEPCC_Msk                  (_U_(0xF) << DSU_PID4_JEPCC_Pos)               /**< (DSU_PID4) JEP-106 Continuation Code Mask */
#define DSU_PID4_JEPCC(value)               (DSU_PID4_JEPCC_Msk & ((value) << DSU_PID4_JEPCC_Pos))
#define DSU_PID4_FKBC_Pos                   4                                              /**< (DSU_PID4) 4KB count Position */
#define DSU_PID4_FKBC_Msk                   (_U_(0xF) << DSU_PID4_FKBC_Pos)                /**< (DSU_PID4) 4KB count Mask */
#define DSU_PID4_FKBC(value)                (DSU_PID4_FKBC_Msk & ((value) << DSU_PID4_FKBC_Pos))
#define DSU_PID4_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_PID4) Register MASK  (Use DSU_PID4_Msk instead)  */
#define DSU_PID4_Msk                        _U_(0xFF)                                      /**< (DSU_PID4) Register Mask  */


/* -------- DSU_PID5 : (DSU Offset: 0x1fd4) (R/ 32) Peripheral Identification 5 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID5_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID5_OFFSET                     (0x1FD4)                                      /**<  (DSU_PID5) Peripheral Identification 5  Offset */
#define DSU_PID5_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_PID5) Peripheral Identification 5  Reset Value */

#define DSU_PID5_MASK                       _U_(0x00)                                      /**< \deprecated (DSU_PID5) Register MASK  (Use DSU_PID5_Msk instead)  */
#define DSU_PID5_Msk                        _U_(0x00)                                      /**< (DSU_PID5) Register Mask  */


/* -------- DSU_PID6 : (DSU Offset: 0x1fd8) (R/ 32) Peripheral Identification 6 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID6_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID6_OFFSET                     (0x1FD8)                                      /**<  (DSU_PID6) Peripheral Identification 6  Offset */
#define DSU_PID6_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_PID6) Peripheral Identification 6  Reset Value */

#define DSU_PID6_MASK                       _U_(0x00)                                      /**< \deprecated (DSU_PID6) Register MASK  (Use DSU_PID6_Msk instead)  */
#define DSU_PID6_Msk                        _U_(0x00)                                      /**< (DSU_PID6) Register Mask  */


/* -------- DSU_PID7 : (DSU Offset: 0x1fdc) (R/ 32) Peripheral Identification 7 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID7_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID7_OFFSET                     (0x1FDC)                                      /**<  (DSU_PID7) Peripheral Identification 7  Offset */
#define DSU_PID7_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_PID7) Peripheral Identification 7  Reset Value */

#define DSU_PID7_MASK                       _U_(0x00)                                      /**< \deprecated (DSU_PID7) Register MASK  (Use DSU_PID7_Msk instead)  */
#define DSU_PID7_Msk                        _U_(0x00)                                      /**< (DSU_PID7) Register Mask  */


/* -------- DSU_PID0 : (DSU Offset: 0x1fe0) (R/ 32) Peripheral Identification 0 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PARTNBL:8;                 /**< bit:   0..7  Part Number Low                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID0_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID0_OFFSET                     (0x1FE0)                                      /**<  (DSU_PID0) Peripheral Identification 0  Offset */
#define DSU_PID0_RESETVALUE                 _U_(0xD0)                                     /**<  (DSU_PID0) Peripheral Identification 0  Reset Value */

#define DSU_PID0_PARTNBL_Pos                0                                              /**< (DSU_PID0) Part Number Low Position */
#define DSU_PID0_PARTNBL_Msk                (_U_(0xFF) << DSU_PID0_PARTNBL_Pos)            /**< (DSU_PID0) Part Number Low Mask */
#define DSU_PID0_PARTNBL(value)             (DSU_PID0_PARTNBL_Msk & ((value) << DSU_PID0_PARTNBL_Pos))
#define DSU_PID0_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_PID0) Register MASK  (Use DSU_PID0_Msk instead)  */
#define DSU_PID0_Msk                        _U_(0xFF)                                      /**< (DSU_PID0) Register Mask  */


/* -------- DSU_PID1 : (DSU Offset: 0x1fe4) (R/ 32) Peripheral Identification 1 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PARTNBH:4;                 /**< bit:   0..3  Part Number High                         */
    uint32_t JEPIDCL:4;                 /**< bit:   4..7  Low part of the JEP-106 Identity Code    */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID1_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID1_OFFSET                     (0x1FE4)                                      /**<  (DSU_PID1) Peripheral Identification 1  Offset */
#define DSU_PID1_RESETVALUE                 _U_(0xFC)                                     /**<  (DSU_PID1) Peripheral Identification 1  Reset Value */

#define DSU_PID1_PARTNBH_Pos                0                                              /**< (DSU_PID1) Part Number High Position */
#define DSU_PID1_PARTNBH_Msk                (_U_(0xF) << DSU_PID1_PARTNBH_Pos)             /**< (DSU_PID1) Part Number High Mask */
#define DSU_PID1_PARTNBH(value)             (DSU_PID1_PARTNBH_Msk & ((value) << DSU_PID1_PARTNBH_Pos))
#define DSU_PID1_JEPIDCL_Pos                4                                              /**< (DSU_PID1) Low part of the JEP-106 Identity Code Position */
#define DSU_PID1_JEPIDCL_Msk                (_U_(0xF) << DSU_PID1_JEPIDCL_Pos)             /**< (DSU_PID1) Low part of the JEP-106 Identity Code Mask */
#define DSU_PID1_JEPIDCL(value)             (DSU_PID1_JEPIDCL_Msk & ((value) << DSU_PID1_JEPIDCL_Pos))
#define DSU_PID1_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_PID1) Register MASK  (Use DSU_PID1_Msk instead)  */
#define DSU_PID1_Msk                        _U_(0xFF)                                      /**< (DSU_PID1) Register Mask  */


/* -------- DSU_PID2 : (DSU Offset: 0x1fe8) (R/ 32) Peripheral Identification 2 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t JEPIDCH:3;                 /**< bit:   0..2  JEP-106 Identity Code High               */
    uint32_t JEPU:1;                    /**< bit:      3  JEP-106 Identity Code is used            */
    uint32_t REVISION:4;                /**< bit:   4..7  Revision Number                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID2_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID2_OFFSET                     (0x1FE8)                                      /**<  (DSU_PID2) Peripheral Identification 2  Offset */
#define DSU_PID2_RESETVALUE                 _U_(0x09)                                     /**<  (DSU_PID2) Peripheral Identification 2  Reset Value */

#define DSU_PID2_JEPIDCH_Pos                0                                              /**< (DSU_PID2) JEP-106 Identity Code High Position */
#define DSU_PID2_JEPIDCH_Msk                (_U_(0x7) << DSU_PID2_JEPIDCH_Pos)             /**< (DSU_PID2) JEP-106 Identity Code High Mask */
#define DSU_PID2_JEPIDCH(value)             (DSU_PID2_JEPIDCH_Msk & ((value) << DSU_PID2_JEPIDCH_Pos))
#define DSU_PID2_JEPU_Pos                   3                                              /**< (DSU_PID2) JEP-106 Identity Code is used Position */
#define DSU_PID2_JEPU_Msk                   (_U_(0x1) << DSU_PID2_JEPU_Pos)                /**< (DSU_PID2) JEP-106 Identity Code is used Mask */
#define DSU_PID2_JEPU                       DSU_PID2_JEPU_Msk                              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DSU_PID2_JEPU_Msk instead */
#define DSU_PID2_REVISION_Pos               4                                              /**< (DSU_PID2) Revision Number Position */
#define DSU_PID2_REVISION_Msk               (_U_(0xF) << DSU_PID2_REVISION_Pos)            /**< (DSU_PID2) Revision Number Mask */
#define DSU_PID2_REVISION(value)            (DSU_PID2_REVISION_Msk & ((value) << DSU_PID2_REVISION_Pos))
#define DSU_PID2_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_PID2) Register MASK  (Use DSU_PID2_Msk instead)  */
#define DSU_PID2_Msk                        _U_(0xFF)                                      /**< (DSU_PID2) Register Mask  */


/* -------- DSU_PID3 : (DSU Offset: 0x1fec) (R/ 32) Peripheral Identification 3 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CUSMOD:4;                  /**< bit:   0..3  ARM CUSMOD                               */
    uint32_t REVAND:4;                  /**< bit:   4..7  Revision Number                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_PID3_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_PID3_OFFSET                     (0x1FEC)                                      /**<  (DSU_PID3) Peripheral Identification 3  Offset */
#define DSU_PID3_RESETVALUE                 _U_(0x00)                                     /**<  (DSU_PID3) Peripheral Identification 3  Reset Value */

#define DSU_PID3_CUSMOD_Pos                 0                                              /**< (DSU_PID3) ARM CUSMOD Position */
#define DSU_PID3_CUSMOD_Msk                 (_U_(0xF) << DSU_PID3_CUSMOD_Pos)              /**< (DSU_PID3) ARM CUSMOD Mask */
#define DSU_PID3_CUSMOD(value)              (DSU_PID3_CUSMOD_Msk & ((value) << DSU_PID3_CUSMOD_Pos))
#define DSU_PID3_REVAND_Pos                 4                                              /**< (DSU_PID3) Revision Number Position */
#define DSU_PID3_REVAND_Msk                 (_U_(0xF) << DSU_PID3_REVAND_Pos)              /**< (DSU_PID3) Revision Number Mask */
#define DSU_PID3_REVAND(value)              (DSU_PID3_REVAND_Msk & ((value) << DSU_PID3_REVAND_Pos))
#define DSU_PID3_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_PID3) Register MASK  (Use DSU_PID3_Msk instead)  */
#define DSU_PID3_Msk                        _U_(0xFF)                                      /**< (DSU_PID3) Register Mask  */


/* -------- DSU_CID0 : (DSU Offset: 0x1ff0) (R/ 32) Component Identification 0 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PREAMBLEB0:8;              /**< bit:   0..7  Preamble Byte 0                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_CID0_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CID0_OFFSET                     (0x1FF0)                                      /**<  (DSU_CID0) Component Identification 0  Offset */
#define DSU_CID0_RESETVALUE                 _U_(0x0D)                                     /**<  (DSU_CID0) Component Identification 0  Reset Value */

#define DSU_CID0_PREAMBLEB0_Pos             0                                              /**< (DSU_CID0) Preamble Byte 0 Position */
#define DSU_CID0_PREAMBLEB0_Msk             (_U_(0xFF) << DSU_CID0_PREAMBLEB0_Pos)         /**< (DSU_CID0) Preamble Byte 0 Mask */
#define DSU_CID0_PREAMBLEB0(value)          (DSU_CID0_PREAMBLEB0_Msk & ((value) << DSU_CID0_PREAMBLEB0_Pos))
#define DSU_CID0_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_CID0) Register MASK  (Use DSU_CID0_Msk instead)  */
#define DSU_CID0_Msk                        _U_(0xFF)                                      /**< (DSU_CID0) Register Mask  */


/* -------- DSU_CID1 : (DSU Offset: 0x1ff4) (R/ 32) Component Identification 1 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PREAMBLE:4;                /**< bit:   0..3  Preamble                                 */
    uint32_t CCLASS:4;                  /**< bit:   4..7  Component Class                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_CID1_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CID1_OFFSET                     (0x1FF4)                                      /**<  (DSU_CID1) Component Identification 1  Offset */
#define DSU_CID1_RESETVALUE                 _U_(0x10)                                     /**<  (DSU_CID1) Component Identification 1  Reset Value */

#define DSU_CID1_PREAMBLE_Pos               0                                              /**< (DSU_CID1) Preamble Position */
#define DSU_CID1_PREAMBLE_Msk               (_U_(0xF) << DSU_CID1_PREAMBLE_Pos)            /**< (DSU_CID1) Preamble Mask */
#define DSU_CID1_PREAMBLE(value)            (DSU_CID1_PREAMBLE_Msk & ((value) << DSU_CID1_PREAMBLE_Pos))
#define DSU_CID1_CCLASS_Pos                 4                                              /**< (DSU_CID1) Component Class Position */
#define DSU_CID1_CCLASS_Msk                 (_U_(0xF) << DSU_CID1_CCLASS_Pos)              /**< (DSU_CID1) Component Class Mask */
#define DSU_CID1_CCLASS(value)              (DSU_CID1_CCLASS_Msk & ((value) << DSU_CID1_CCLASS_Pos))
#define DSU_CID1_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_CID1) Register MASK  (Use DSU_CID1_Msk instead)  */
#define DSU_CID1_Msk                        _U_(0xFF)                                      /**< (DSU_CID1) Register Mask  */


/* -------- DSU_CID2 : (DSU Offset: 0x1ff8) (R/ 32) Component Identification 2 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PREAMBLEB2:8;              /**< bit:   0..7  Preamble Byte 2                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_CID2_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CID2_OFFSET                     (0x1FF8)                                      /**<  (DSU_CID2) Component Identification 2  Offset */
#define DSU_CID2_RESETVALUE                 _U_(0x05)                                     /**<  (DSU_CID2) Component Identification 2  Reset Value */

#define DSU_CID2_PREAMBLEB2_Pos             0                                              /**< (DSU_CID2) Preamble Byte 2 Position */
#define DSU_CID2_PREAMBLEB2_Msk             (_U_(0xFF) << DSU_CID2_PREAMBLEB2_Pos)         /**< (DSU_CID2) Preamble Byte 2 Mask */
#define DSU_CID2_PREAMBLEB2(value)          (DSU_CID2_PREAMBLEB2_Msk & ((value) << DSU_CID2_PREAMBLEB2_Pos))
#define DSU_CID2_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_CID2) Register MASK  (Use DSU_CID2_Msk instead)  */
#define DSU_CID2_Msk                        _U_(0xFF)                                      /**< (DSU_CID2) Register Mask  */


/* -------- DSU_CID3 : (DSU Offset: 0x1ffc) (R/ 32) Component Identification 3 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PREAMBLEB3:8;              /**< bit:   0..7  Preamble Byte 3                          */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DSU_CID3_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DSU_CID3_OFFSET                     (0x1FFC)                                      /**<  (DSU_CID3) Component Identification 3  Offset */
#define DSU_CID3_RESETVALUE                 _U_(0xB1)                                     /**<  (DSU_CID3) Component Identification 3  Reset Value */

#define DSU_CID3_PREAMBLEB3_Pos             0                                              /**< (DSU_CID3) Preamble Byte 3 Position */
#define DSU_CID3_PREAMBLEB3_Msk             (_U_(0xFF) << DSU_CID3_PREAMBLEB3_Pos)         /**< (DSU_CID3) Preamble Byte 3 Mask */
#define DSU_CID3_PREAMBLEB3(value)          (DSU_CID3_PREAMBLEB3_Msk & ((value) << DSU_CID3_PREAMBLEB3_Pos))
#define DSU_CID3_MASK                       _U_(0xFF)                                      /**< \deprecated (DSU_CID3) Register MASK  (Use DSU_CID3_Msk instead)  */
#define DSU_CID3_Msk                        _U_(0xFF)                                      /**< (DSU_CID3) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief DSU hardware registers */
typedef struct {  /* Device Service Unit */
  __O  DSU_CTRL_Type                  CTRL;           /**< Offset: 0x00 ( /W   8) Control */
  __IO DSU_STATUSA_Type               STATUSA;        /**< Offset: 0x01 (R/W   8) Status A */
  __I  DSU_STATUSB_Type               STATUSB;        /**< Offset: 0x02 (R/    8) Status B */
  __I  DSU_STATUSC_Type               STATUSC;        /**< Offset: 0x03 (R/    8) Status C */
  __IO DSU_ADDR_Type                  ADDR;           /**< Offset: 0x04 (R/W  32) Address */
  __IO DSU_LENGTH_Type                LENGTH;         /**< Offset: 0x08 (R/W  32) Length */
  __IO DSU_DATA_Type                  DATA;           /**< Offset: 0x0C (R/W  32) Data */
  __IO DSU_DCC_Type                   DCC[2];         /**< Offset: 0x10 (R/W  32) Debug Communication Channel n */
  __I  DSU_DID_Type                   DID;            /**< Offset: 0x18 (R/   32) Device Identification */
  __IO DSU_CFG_Type                   CFG;            /**< Offset: 0x1C (R/W  32) Configuration */
  __IO DSU_BCC_Type                   BCC[2];         /**< Offset: 0x20 (R/W  32) Boot ROM Communication Channel n */
  __I  uint8_t                        Reserved1[200];
  __IO DSU_DCFG_Type                  DCFG[2];        /**< Offset: 0xF0 (R/W  32) Device Configuration */
  __I  uint8_t                        Reserved2[3848];
  __I  DSU_ENTRY0_Type                ENTRY0;         /**< Offset: 0x1000 (R/   32) CoreSight ROM Table Entry 0 */
  __I  DSU_ENTRY1_Type                ENTRY1;         /**< Offset: 0x1004 (R/   32) CoreSight ROM Table Entry 1 */
  __I  DSU_END_Type                   END;            /**< Offset: 0x1008 (R/   32) CoreSight ROM Table End */
  __I  uint8_t                        Reserved3[4032];
  __I  DSU_MEMTYPE_Type               MEMTYPE;        /**< Offset: 0x1FCC (R/   32) CoreSight ROM Table Memory Type */
  __I  DSU_PID4_Type                  PID4;           /**< Offset: 0x1FD0 (R/   32) Peripheral Identification 4 */
  __I  DSU_PID5_Type                  PID5;           /**< Offset: 0x1FD4 (R/   32) Peripheral Identification 5 */
  __I  DSU_PID6_Type                  PID6;           /**< Offset: 0x1FD8 (R/   32) Peripheral Identification 6 */
  __I  DSU_PID7_Type                  PID7;           /**< Offset: 0x1FDC (R/   32) Peripheral Identification 7 */
  __I  DSU_PID0_Type                  PID0;           /**< Offset: 0x1FE0 (R/   32) Peripheral Identification 0 */
  __I  DSU_PID1_Type                  PID1;           /**< Offset: 0x1FE4 (R/   32) Peripheral Identification 1 */
  __I  DSU_PID2_Type                  PID2;           /**< Offset: 0x1FE8 (R/   32) Peripheral Identification 2 */
  __I  DSU_PID3_Type                  PID3;           /**< Offset: 0x1FEC (R/   32) Peripheral Identification 3 */
  __I  DSU_CID0_Type                  CID0;           /**< Offset: 0x1FF0 (R/   32) Component Identification 0 */
  __I  DSU_CID1_Type                  CID1;           /**< Offset: 0x1FF4 (R/   32) Component Identification 1 */
  __I  DSU_CID2_Type                  CID2;           /**< Offset: 0x1FF8 (R/   32) Component Identification 2 */
  __I  DSU_CID3_Type                  CID3;           /**< Offset: 0x1FFC (R/   32) Component Identification 3 */
} Dsu;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Device Service Unit */

#endif /* _SAML10_DSU_COMPONENT_H_ */
