/**
 * \file
 *
 * \brief Component description for DMAC
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
#ifndef _SAML10_DMAC_COMPONENT_H_
#define _SAML10_DMAC_COMPONENT_H_
#define _SAML10_DMAC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Direct Memory Access Controller
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR DMAC */
/* ========================================================================== */

#define DMAC_U2223                      /**< (DMAC) Module ID */
#define REV_DMAC 0x240                  /**< (DMAC) Module revision */

/* -------- DMAC_BTCTRL : (DMAC Offset: 0x00) (R/W 16) Block Transfer Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALID:1;                   /**< bit:      0  Descriptor Valid                         */
    uint16_t EVOSEL:2;                  /**< bit:   1..2  Event Output Selection                   */
    uint16_t BLOCKACT:2;                /**< bit:   3..4  Block Action                             */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t BEATSIZE:2;                /**< bit:   8..9  Beat Size                                */
    uint16_t SRCINC:1;                  /**< bit:     10  Source Address Increment Enable          */
    uint16_t DSTINC:1;                  /**< bit:     11  Destination Address Increment Enable     */
    uint16_t STEPSEL:1;                 /**< bit:     12  Step Selection                           */
    uint16_t STEPSIZE:3;                /**< bit: 13..15  Address Increment Step Size              */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DMAC_BTCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_BTCTRL_OFFSET                  (0x00)                                        /**<  (DMAC_BTCTRL) Block Transfer Control  Offset */
#define DMAC_BTCTRL_RESETVALUE              _U_(0x00)                                     /**<  (DMAC_BTCTRL) Block Transfer Control  Reset Value */

#define DMAC_BTCTRL_VALID_Pos               0                                              /**< (DMAC_BTCTRL) Descriptor Valid Position */
#define DMAC_BTCTRL_VALID_Msk               (_U_(0x1) << DMAC_BTCTRL_VALID_Pos)            /**< (DMAC_BTCTRL) Descriptor Valid Mask */
#define DMAC_BTCTRL_VALID                   DMAC_BTCTRL_VALID_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BTCTRL_VALID_Msk instead */
#define DMAC_BTCTRL_EVOSEL_Pos              1                                              /**< (DMAC_BTCTRL) Event Output Selection Position */
#define DMAC_BTCTRL_EVOSEL_Msk              (_U_(0x3) << DMAC_BTCTRL_EVOSEL_Pos)           /**< (DMAC_BTCTRL) Event Output Selection Mask */
#define DMAC_BTCTRL_EVOSEL(value)           (DMAC_BTCTRL_EVOSEL_Msk & ((value) << DMAC_BTCTRL_EVOSEL_Pos))
#define   DMAC_BTCTRL_EVOSEL_DISABLE_Val    _U_(0x0)                                       /**< (DMAC_BTCTRL) Event generation disabled  */
#define   DMAC_BTCTRL_EVOSEL_BLOCK_Val      _U_(0x1)                                       /**< (DMAC_BTCTRL) Event strobe when block transfer complete  */
#define   DMAC_BTCTRL_EVOSEL_BEAT_Val       _U_(0x3)                                       /**< (DMAC_BTCTRL) Event strobe when beat transfer complete  */
#define DMAC_BTCTRL_EVOSEL_DISABLE          (DMAC_BTCTRL_EVOSEL_DISABLE_Val << DMAC_BTCTRL_EVOSEL_Pos)  /**< (DMAC_BTCTRL) Event generation disabled Position  */
#define DMAC_BTCTRL_EVOSEL_BLOCK            (DMAC_BTCTRL_EVOSEL_BLOCK_Val << DMAC_BTCTRL_EVOSEL_Pos)  /**< (DMAC_BTCTRL) Event strobe when block transfer complete Position  */
#define DMAC_BTCTRL_EVOSEL_BEAT             (DMAC_BTCTRL_EVOSEL_BEAT_Val << DMAC_BTCTRL_EVOSEL_Pos)  /**< (DMAC_BTCTRL) Event strobe when beat transfer complete Position  */
#define DMAC_BTCTRL_BLOCKACT_Pos            3                                              /**< (DMAC_BTCTRL) Block Action Position */
#define DMAC_BTCTRL_BLOCKACT_Msk            (_U_(0x3) << DMAC_BTCTRL_BLOCKACT_Pos)         /**< (DMAC_BTCTRL) Block Action Mask */
#define DMAC_BTCTRL_BLOCKACT(value)         (DMAC_BTCTRL_BLOCKACT_Msk & ((value) << DMAC_BTCTRL_BLOCKACT_Pos))
#define   DMAC_BTCTRL_BLOCKACT_NOACT_Val    _U_(0x0)                                       /**< (DMAC_BTCTRL) Channel will be disabled if it is the last block transfer in the transaction  */
#define   DMAC_BTCTRL_BLOCKACT_INT_Val      _U_(0x1)                                       /**< (DMAC_BTCTRL) Channel will be disabled if it is the last block transfer in the transaction and block interrupt  */
#define   DMAC_BTCTRL_BLOCKACT_SUSPEND_Val  _U_(0x2)                                       /**< (DMAC_BTCTRL) Channel suspend operation is completed  */
#define   DMAC_BTCTRL_BLOCKACT_BOTH_Val     _U_(0x3)                                       /**< (DMAC_BTCTRL) Both channel suspend operation and block interrupt  */
#define DMAC_BTCTRL_BLOCKACT_NOACT          (DMAC_BTCTRL_BLOCKACT_NOACT_Val << DMAC_BTCTRL_BLOCKACT_Pos)  /**< (DMAC_BTCTRL) Channel will be disabled if it is the last block transfer in the transaction Position  */
#define DMAC_BTCTRL_BLOCKACT_INT            (DMAC_BTCTRL_BLOCKACT_INT_Val << DMAC_BTCTRL_BLOCKACT_Pos)  /**< (DMAC_BTCTRL) Channel will be disabled if it is the last block transfer in the transaction and block interrupt Position  */
#define DMAC_BTCTRL_BLOCKACT_SUSPEND        (DMAC_BTCTRL_BLOCKACT_SUSPEND_Val << DMAC_BTCTRL_BLOCKACT_Pos)  /**< (DMAC_BTCTRL) Channel suspend operation is completed Position  */
#define DMAC_BTCTRL_BLOCKACT_BOTH           (DMAC_BTCTRL_BLOCKACT_BOTH_Val << DMAC_BTCTRL_BLOCKACT_Pos)  /**< (DMAC_BTCTRL) Both channel suspend operation and block interrupt Position  */
#define DMAC_BTCTRL_BEATSIZE_Pos            8                                              /**< (DMAC_BTCTRL) Beat Size Position */
#define DMAC_BTCTRL_BEATSIZE_Msk            (_U_(0x3) << DMAC_BTCTRL_BEATSIZE_Pos)         /**< (DMAC_BTCTRL) Beat Size Mask */
#define DMAC_BTCTRL_BEATSIZE(value)         (DMAC_BTCTRL_BEATSIZE_Msk & ((value) << DMAC_BTCTRL_BEATSIZE_Pos))
#define   DMAC_BTCTRL_BEATSIZE_BYTE_Val     _U_(0x0)                                       /**< (DMAC_BTCTRL) 8-bit bus transfer  */
#define   DMAC_BTCTRL_BEATSIZE_HWORD_Val    _U_(0x1)                                       /**< (DMAC_BTCTRL) 16-bit bus transfer  */
#define   DMAC_BTCTRL_BEATSIZE_WORD_Val     _U_(0x2)                                       /**< (DMAC_BTCTRL) 32-bit bus transfer  */
#define DMAC_BTCTRL_BEATSIZE_BYTE           (DMAC_BTCTRL_BEATSIZE_BYTE_Val << DMAC_BTCTRL_BEATSIZE_Pos)  /**< (DMAC_BTCTRL) 8-bit bus transfer Position  */
#define DMAC_BTCTRL_BEATSIZE_HWORD          (DMAC_BTCTRL_BEATSIZE_HWORD_Val << DMAC_BTCTRL_BEATSIZE_Pos)  /**< (DMAC_BTCTRL) 16-bit bus transfer Position  */
#define DMAC_BTCTRL_BEATSIZE_WORD           (DMAC_BTCTRL_BEATSIZE_WORD_Val << DMAC_BTCTRL_BEATSIZE_Pos)  /**< (DMAC_BTCTRL) 32-bit bus transfer Position  */
#define DMAC_BTCTRL_SRCINC_Pos              10                                             /**< (DMAC_BTCTRL) Source Address Increment Enable Position */
#define DMAC_BTCTRL_SRCINC_Msk              (_U_(0x1) << DMAC_BTCTRL_SRCINC_Pos)           /**< (DMAC_BTCTRL) Source Address Increment Enable Mask */
#define DMAC_BTCTRL_SRCINC                  DMAC_BTCTRL_SRCINC_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BTCTRL_SRCINC_Msk instead */
#define DMAC_BTCTRL_DSTINC_Pos              11                                             /**< (DMAC_BTCTRL) Destination Address Increment Enable Position */
#define DMAC_BTCTRL_DSTINC_Msk              (_U_(0x1) << DMAC_BTCTRL_DSTINC_Pos)           /**< (DMAC_BTCTRL) Destination Address Increment Enable Mask */
#define DMAC_BTCTRL_DSTINC                  DMAC_BTCTRL_DSTINC_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BTCTRL_DSTINC_Msk instead */
#define DMAC_BTCTRL_STEPSEL_Pos             12                                             /**< (DMAC_BTCTRL) Step Selection Position */
#define DMAC_BTCTRL_STEPSEL_Msk             (_U_(0x1) << DMAC_BTCTRL_STEPSEL_Pos)          /**< (DMAC_BTCTRL) Step Selection Mask */
#define DMAC_BTCTRL_STEPSEL                 DMAC_BTCTRL_STEPSEL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BTCTRL_STEPSEL_Msk instead */
#define   DMAC_BTCTRL_STEPSEL_DST_Val       _U_(0x0)                                       /**< (DMAC_BTCTRL) Step size settings apply to the destination address  */
#define   DMAC_BTCTRL_STEPSEL_SRC_Val       _U_(0x1)                                       /**< (DMAC_BTCTRL) Step size settings apply to the source address  */
#define DMAC_BTCTRL_STEPSEL_DST             (DMAC_BTCTRL_STEPSEL_DST_Val << DMAC_BTCTRL_STEPSEL_Pos)  /**< (DMAC_BTCTRL) Step size settings apply to the destination address Position  */
#define DMAC_BTCTRL_STEPSEL_SRC             (DMAC_BTCTRL_STEPSEL_SRC_Val << DMAC_BTCTRL_STEPSEL_Pos)  /**< (DMAC_BTCTRL) Step size settings apply to the source address Position  */
#define DMAC_BTCTRL_STEPSIZE_Pos            13                                             /**< (DMAC_BTCTRL) Address Increment Step Size Position */
#define DMAC_BTCTRL_STEPSIZE_Msk            (_U_(0x7) << DMAC_BTCTRL_STEPSIZE_Pos)         /**< (DMAC_BTCTRL) Address Increment Step Size Mask */
#define DMAC_BTCTRL_STEPSIZE(value)         (DMAC_BTCTRL_STEPSIZE_Msk & ((value) << DMAC_BTCTRL_STEPSIZE_Pos))
#define   DMAC_BTCTRL_STEPSIZE_X1_Val       _U_(0x0)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 1  */
#define   DMAC_BTCTRL_STEPSIZE_X2_Val       _U_(0x1)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 2  */
#define   DMAC_BTCTRL_STEPSIZE_X4_Val       _U_(0x2)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 4  */
#define   DMAC_BTCTRL_STEPSIZE_X8_Val       _U_(0x3)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 8  */
#define   DMAC_BTCTRL_STEPSIZE_X16_Val      _U_(0x4)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 16  */
#define   DMAC_BTCTRL_STEPSIZE_X32_Val      _U_(0x5)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 32  */
#define   DMAC_BTCTRL_STEPSIZE_X64_Val      _U_(0x6)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 64  */
#define   DMAC_BTCTRL_STEPSIZE_X128_Val     _U_(0x7)                                       /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 128  */
#define DMAC_BTCTRL_STEPSIZE_X1             (DMAC_BTCTRL_STEPSIZE_X1_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 1 Position  */
#define DMAC_BTCTRL_STEPSIZE_X2             (DMAC_BTCTRL_STEPSIZE_X2_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 2 Position  */
#define DMAC_BTCTRL_STEPSIZE_X4             (DMAC_BTCTRL_STEPSIZE_X4_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 4 Position  */
#define DMAC_BTCTRL_STEPSIZE_X8             (DMAC_BTCTRL_STEPSIZE_X8_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 8 Position  */
#define DMAC_BTCTRL_STEPSIZE_X16            (DMAC_BTCTRL_STEPSIZE_X16_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 16 Position  */
#define DMAC_BTCTRL_STEPSIZE_X32            (DMAC_BTCTRL_STEPSIZE_X32_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 32 Position  */
#define DMAC_BTCTRL_STEPSIZE_X64            (DMAC_BTCTRL_STEPSIZE_X64_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 64 Position  */
#define DMAC_BTCTRL_STEPSIZE_X128           (DMAC_BTCTRL_STEPSIZE_X128_Val << DMAC_BTCTRL_STEPSIZE_Pos)  /**< (DMAC_BTCTRL) Next ADDR = ADDR + (BEATSIZE+1) * 128 Position  */
#define DMAC_BTCTRL_MASK                    _U_(0xFF1F)                                    /**< \deprecated (DMAC_BTCTRL) Register MASK  (Use DMAC_BTCTRL_Msk instead)  */
#define DMAC_BTCTRL_Msk                     _U_(0xFF1F)                                    /**< (DMAC_BTCTRL) Register Mask  */


/* -------- DMAC_BTCNT : (DMAC Offset: 0x02) (R/W 16) Block Transfer Count -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BTCNT:16;                  /**< bit:  0..15  Block Transfer Count                     */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DMAC_BTCNT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_BTCNT_OFFSET                   (0x02)                                        /**<  (DMAC_BTCNT) Block Transfer Count  Offset */

#define DMAC_BTCNT_BTCNT_Pos                0                                              /**< (DMAC_BTCNT) Block Transfer Count Position */
#define DMAC_BTCNT_BTCNT_Msk                (_U_(0xFFFF) << DMAC_BTCNT_BTCNT_Pos)          /**< (DMAC_BTCNT) Block Transfer Count Mask */
#define DMAC_BTCNT_BTCNT(value)             (DMAC_BTCNT_BTCNT_Msk & ((value) << DMAC_BTCNT_BTCNT_Pos))
#define DMAC_BTCNT_MASK                     _U_(0xFFFF)                                    /**< \deprecated (DMAC_BTCNT) Register MASK  (Use DMAC_BTCNT_Msk instead)  */
#define DMAC_BTCNT_Msk                      _U_(0xFFFF)                                    /**< (DMAC_BTCNT) Register Mask  */


/* -------- DMAC_SRCADDR : (DMAC Offset: 0x04) (R/W 32) Block Transfer Source Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SRCADDR:32;                /**< bit:  0..31  Transfer Source Address                  */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_SRCADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_SRCADDR_OFFSET                 (0x04)                                        /**<  (DMAC_SRCADDR) Block Transfer Source Address  Offset */

#define DMAC_SRCADDR_SRCADDR_Pos            0                                              /**< (DMAC_SRCADDR) Transfer Source Address Position */
#define DMAC_SRCADDR_SRCADDR_Msk            (_U_(0xFFFFFFFF) << DMAC_SRCADDR_SRCADDR_Pos)  /**< (DMAC_SRCADDR) Transfer Source Address Mask */
#define DMAC_SRCADDR_SRCADDR(value)         (DMAC_SRCADDR_SRCADDR_Msk & ((value) << DMAC_SRCADDR_SRCADDR_Pos))
#define DMAC_SRCADDR_MASK                   _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_SRCADDR) Register MASK  (Use DMAC_SRCADDR_Msk instead)  */
#define DMAC_SRCADDR_Msk                    _U_(0xFFFFFFFF)                                /**< (DMAC_SRCADDR) Register Mask  */


/* -------- DMAC_DSTADDR : (DMAC Offset: 0x08) (R/W 32) Block Transfer Destination Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DSTADDR:32;                /**< bit:  0..31  Transfer Destination Address             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_DSTADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_DSTADDR_OFFSET                 (0x08)                                        /**<  (DMAC_DSTADDR) Block Transfer Destination Address  Offset */

#define DMAC_DSTADDR_DSTADDR_Pos            0                                              /**< (DMAC_DSTADDR) Transfer Destination Address Position */
#define DMAC_DSTADDR_DSTADDR_Msk            (_U_(0xFFFFFFFF) << DMAC_DSTADDR_DSTADDR_Pos)  /**< (DMAC_DSTADDR) Transfer Destination Address Mask */
#define DMAC_DSTADDR_DSTADDR(value)         (DMAC_DSTADDR_DSTADDR_Msk & ((value) << DMAC_DSTADDR_DSTADDR_Pos))
#define DMAC_DSTADDR_MASK                   _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_DSTADDR) Register MASK  (Use DMAC_DSTADDR_Msk instead)  */
#define DMAC_DSTADDR_Msk                    _U_(0xFFFFFFFF)                                /**< (DMAC_DSTADDR) Register Mask  */


/* -------- DMAC_DESCADDR : (DMAC Offset: 0x0c) (R/W 32) Next Descriptor Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DESCADDR:32;               /**< bit:  0..31  Next Descriptor Address                  */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_DESCADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_DESCADDR_OFFSET                (0x0C)                                        /**<  (DMAC_DESCADDR) Next Descriptor Address  Offset */

#define DMAC_DESCADDR_DESCADDR_Pos          0                                              /**< (DMAC_DESCADDR) Next Descriptor Address Position */
#define DMAC_DESCADDR_DESCADDR_Msk          (_U_(0xFFFFFFFF) << DMAC_DESCADDR_DESCADDR_Pos)  /**< (DMAC_DESCADDR) Next Descriptor Address Mask */
#define DMAC_DESCADDR_DESCADDR(value)       (DMAC_DESCADDR_DESCADDR_Msk & ((value) << DMAC_DESCADDR_DESCADDR_Pos))
#define DMAC_DESCADDR_MASK                  _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_DESCADDR) Register MASK  (Use DMAC_DESCADDR_Msk instead)  */
#define DMAC_DESCADDR_Msk                   _U_(0xFFFFFFFF)                                /**< (DMAC_DESCADDR) Register Mask  */


/* -------- DMAC_CTRL : (DMAC Offset: 0x00) (R/W 16) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint16_t DMAENABLE:1;               /**< bit:      1  DMA Enable                               */
    uint16_t CRCENABLE:1;               /**< bit:      2  CRC Enable                               */
    uint16_t :5;                        /**< bit:   3..7  Reserved */
    uint16_t LVLEN0:1;                  /**< bit:      8  Priority Level 0 Enable                  */
    uint16_t LVLEN1:1;                  /**< bit:      9  Priority Level 1 Enable                  */
    uint16_t LVLEN2:1;                  /**< bit:     10  Priority Level 2 Enable                  */
    uint16_t LVLEN3:1;                  /**< bit:     11  Priority Level 3 Enable                  */
    uint16_t :4;                        /**< bit: 12..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t :8;                        /**< bit:   0..7  Reserved */
    uint16_t LVLEN:4;                   /**< bit:  8..11  Priority Level 3 Enable                  */
    uint16_t :4;                        /**< bit: 12..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} DMAC_CTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CTRL_OFFSET                    (0x00)                                        /**<  (DMAC_CTRL) Control  Offset */
#define DMAC_CTRL_RESETVALUE                _U_(0x00)                                     /**<  (DMAC_CTRL) Control  Reset Value */

#define DMAC_CTRL_SWRST_Pos                 0                                              /**< (DMAC_CTRL) Software Reset Position */
#define DMAC_CTRL_SWRST_Msk                 (_U_(0x1) << DMAC_CTRL_SWRST_Pos)              /**< (DMAC_CTRL) Software Reset Mask */
#define DMAC_CTRL_SWRST                     DMAC_CTRL_SWRST_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_SWRST_Msk instead */
#define DMAC_CTRL_DMAENABLE_Pos             1                                              /**< (DMAC_CTRL) DMA Enable Position */
#define DMAC_CTRL_DMAENABLE_Msk             (_U_(0x1) << DMAC_CTRL_DMAENABLE_Pos)          /**< (DMAC_CTRL) DMA Enable Mask */
#define DMAC_CTRL_DMAENABLE                 DMAC_CTRL_DMAENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_DMAENABLE_Msk instead */
#define DMAC_CTRL_CRCENABLE_Pos             2                                              /**< (DMAC_CTRL) CRC Enable Position */
#define DMAC_CTRL_CRCENABLE_Msk             (_U_(0x1) << DMAC_CTRL_CRCENABLE_Pos)          /**< (DMAC_CTRL) CRC Enable Mask */
#define DMAC_CTRL_CRCENABLE                 DMAC_CTRL_CRCENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_CRCENABLE_Msk instead */
#define DMAC_CTRL_LVLEN0_Pos                8                                              /**< (DMAC_CTRL) Priority Level 0 Enable Position */
#define DMAC_CTRL_LVLEN0_Msk                (_U_(0x1) << DMAC_CTRL_LVLEN0_Pos)             /**< (DMAC_CTRL) Priority Level 0 Enable Mask */
#define DMAC_CTRL_LVLEN0                    DMAC_CTRL_LVLEN0_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_LVLEN0_Msk instead */
#define DMAC_CTRL_LVLEN1_Pos                9                                              /**< (DMAC_CTRL) Priority Level 1 Enable Position */
#define DMAC_CTRL_LVLEN1_Msk                (_U_(0x1) << DMAC_CTRL_LVLEN1_Pos)             /**< (DMAC_CTRL) Priority Level 1 Enable Mask */
#define DMAC_CTRL_LVLEN1                    DMAC_CTRL_LVLEN1_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_LVLEN1_Msk instead */
#define DMAC_CTRL_LVLEN2_Pos                10                                             /**< (DMAC_CTRL) Priority Level 2 Enable Position */
#define DMAC_CTRL_LVLEN2_Msk                (_U_(0x1) << DMAC_CTRL_LVLEN2_Pos)             /**< (DMAC_CTRL) Priority Level 2 Enable Mask */
#define DMAC_CTRL_LVLEN2                    DMAC_CTRL_LVLEN2_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_LVLEN2_Msk instead */
#define DMAC_CTRL_LVLEN3_Pos                11                                             /**< (DMAC_CTRL) Priority Level 3 Enable Position */
#define DMAC_CTRL_LVLEN3_Msk                (_U_(0x1) << DMAC_CTRL_LVLEN3_Pos)             /**< (DMAC_CTRL) Priority Level 3 Enable Mask */
#define DMAC_CTRL_LVLEN3                    DMAC_CTRL_LVLEN3_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CTRL_LVLEN3_Msk instead */
#define DMAC_CTRL_MASK                      _U_(0xF07)                                     /**< \deprecated (DMAC_CTRL) Register MASK  (Use DMAC_CTRL_Msk instead)  */
#define DMAC_CTRL_Msk                       _U_(0xF07)                                     /**< (DMAC_CTRL) Register Mask  */

#define DMAC_CTRL_LVLEN_Pos                 8                                              /**< (DMAC_CTRL Position) Priority Level 3 Enable */
#define DMAC_CTRL_LVLEN_Msk                 (_U_(0xF) << DMAC_CTRL_LVLEN_Pos)              /**< (DMAC_CTRL Mask) LVLEN */
#define DMAC_CTRL_LVLEN(value)              (DMAC_CTRL_LVLEN_Msk & ((value) << DMAC_CTRL_LVLEN_Pos))  

/* -------- DMAC_CRCCTRL : (DMAC Offset: 0x02) (R/W 16) CRC Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t CRCBEATSIZE:2;             /**< bit:   0..1  CRC Beat Size                            */
    uint16_t CRCPOLY:2;                 /**< bit:   2..3  CRC Polynomial Type                      */
    uint16_t :4;                        /**< bit:   4..7  Reserved */
    uint16_t CRCSRC:6;                  /**< bit:  8..13  CRC Input Source                         */
    uint16_t :2;                        /**< bit: 14..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DMAC_CRCCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CRCCTRL_OFFSET                 (0x02)                                        /**<  (DMAC_CRCCTRL) CRC Control  Offset */
#define DMAC_CRCCTRL_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_CRCCTRL) CRC Control  Reset Value */

#define DMAC_CRCCTRL_CRCBEATSIZE_Pos        0                                              /**< (DMAC_CRCCTRL) CRC Beat Size Position */
#define DMAC_CRCCTRL_CRCBEATSIZE_Msk        (_U_(0x3) << DMAC_CRCCTRL_CRCBEATSIZE_Pos)     /**< (DMAC_CRCCTRL) CRC Beat Size Mask */
#define DMAC_CRCCTRL_CRCBEATSIZE(value)     (DMAC_CRCCTRL_CRCBEATSIZE_Msk & ((value) << DMAC_CRCCTRL_CRCBEATSIZE_Pos))
#define   DMAC_CRCCTRL_CRCBEATSIZE_BYTE_Val _U_(0x0)                                       /**< (DMAC_CRCCTRL) 8-bit bus transfer  */
#define   DMAC_CRCCTRL_CRCBEATSIZE_HWORD_Val _U_(0x1)                                       /**< (DMAC_CRCCTRL) 16-bit bus transfer  */
#define   DMAC_CRCCTRL_CRCBEATSIZE_WORD_Val _U_(0x2)                                       /**< (DMAC_CRCCTRL) 32-bit bus transfer  */
#define DMAC_CRCCTRL_CRCBEATSIZE_BYTE       (DMAC_CRCCTRL_CRCBEATSIZE_BYTE_Val << DMAC_CRCCTRL_CRCBEATSIZE_Pos)  /**< (DMAC_CRCCTRL) 8-bit bus transfer Position  */
#define DMAC_CRCCTRL_CRCBEATSIZE_HWORD      (DMAC_CRCCTRL_CRCBEATSIZE_HWORD_Val << DMAC_CRCCTRL_CRCBEATSIZE_Pos)  /**< (DMAC_CRCCTRL) 16-bit bus transfer Position  */
#define DMAC_CRCCTRL_CRCBEATSIZE_WORD       (DMAC_CRCCTRL_CRCBEATSIZE_WORD_Val << DMAC_CRCCTRL_CRCBEATSIZE_Pos)  /**< (DMAC_CRCCTRL) 32-bit bus transfer Position  */
#define DMAC_CRCCTRL_CRCPOLY_Pos            2                                              /**< (DMAC_CRCCTRL) CRC Polynomial Type Position */
#define DMAC_CRCCTRL_CRCPOLY_Msk            (_U_(0x3) << DMAC_CRCCTRL_CRCPOLY_Pos)         /**< (DMAC_CRCCTRL) CRC Polynomial Type Mask */
#define DMAC_CRCCTRL_CRCPOLY(value)         (DMAC_CRCCTRL_CRCPOLY_Msk & ((value) << DMAC_CRCCTRL_CRCPOLY_Pos))
#define   DMAC_CRCCTRL_CRCPOLY_CRC16_Val    _U_(0x0)                                       /**< (DMAC_CRCCTRL) CRC-16 (CRC-CCITT)  */
#define   DMAC_CRCCTRL_CRCPOLY_CRC32_Val    _U_(0x1)                                       /**< (DMAC_CRCCTRL) CRC32 (IEEE 802.3)  */
#define DMAC_CRCCTRL_CRCPOLY_CRC16          (DMAC_CRCCTRL_CRCPOLY_CRC16_Val << DMAC_CRCCTRL_CRCPOLY_Pos)  /**< (DMAC_CRCCTRL) CRC-16 (CRC-CCITT) Position  */
#define DMAC_CRCCTRL_CRCPOLY_CRC32          (DMAC_CRCCTRL_CRCPOLY_CRC32_Val << DMAC_CRCCTRL_CRCPOLY_Pos)  /**< (DMAC_CRCCTRL) CRC32 (IEEE 802.3) Position  */
#define DMAC_CRCCTRL_CRCSRC_Pos             8                                              /**< (DMAC_CRCCTRL) CRC Input Source Position */
#define DMAC_CRCCTRL_CRCSRC_Msk             (_U_(0x3F) << DMAC_CRCCTRL_CRCSRC_Pos)         /**< (DMAC_CRCCTRL) CRC Input Source Mask */
#define DMAC_CRCCTRL_CRCSRC(value)          (DMAC_CRCCTRL_CRCSRC_Msk & ((value) << DMAC_CRCCTRL_CRCSRC_Pos))
#define   DMAC_CRCCTRL_CRCSRC_NOACT_Val     _U_(0x0)                                       /**< (DMAC_CRCCTRL) No action  */
#define   DMAC_CRCCTRL_CRCSRC_IO_Val        _U_(0x1)                                       /**< (DMAC_CRCCTRL) I/O interface  */
#define DMAC_CRCCTRL_CRCSRC_NOACT           (DMAC_CRCCTRL_CRCSRC_NOACT_Val << DMAC_CRCCTRL_CRCSRC_Pos)  /**< (DMAC_CRCCTRL) No action Position  */
#define DMAC_CRCCTRL_CRCSRC_IO              (DMAC_CRCCTRL_CRCSRC_IO_Val << DMAC_CRCCTRL_CRCSRC_Pos)  /**< (DMAC_CRCCTRL) I/O interface Position  */
#define DMAC_CRCCTRL_MASK                   _U_(0x3F0F)                                    /**< \deprecated (DMAC_CRCCTRL) Register MASK  (Use DMAC_CRCCTRL_Msk instead)  */
#define DMAC_CRCCTRL_Msk                    _U_(0x3F0F)                                    /**< (DMAC_CRCCTRL) Register Mask  */


/* -------- DMAC_CRCDATAIN : (DMAC Offset: 0x04) (R/W 32) CRC Data Input -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CRCDATAIN:32;              /**< bit:  0..31  CRC Data Input                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_CRCDATAIN_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CRCDATAIN_OFFSET               (0x04)                                        /**<  (DMAC_CRCDATAIN) CRC Data Input  Offset */
#define DMAC_CRCDATAIN_RESETVALUE           _U_(0x00)                                     /**<  (DMAC_CRCDATAIN) CRC Data Input  Reset Value */

#define DMAC_CRCDATAIN_CRCDATAIN_Pos        0                                              /**< (DMAC_CRCDATAIN) CRC Data Input Position */
#define DMAC_CRCDATAIN_CRCDATAIN_Msk        (_U_(0xFFFFFFFF) << DMAC_CRCDATAIN_CRCDATAIN_Pos)  /**< (DMAC_CRCDATAIN) CRC Data Input Mask */
#define DMAC_CRCDATAIN_CRCDATAIN(value)     (DMAC_CRCDATAIN_CRCDATAIN_Msk & ((value) << DMAC_CRCDATAIN_CRCDATAIN_Pos))
#define DMAC_CRCDATAIN_MASK                 _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_CRCDATAIN) Register MASK  (Use DMAC_CRCDATAIN_Msk instead)  */
#define DMAC_CRCDATAIN_Msk                  _U_(0xFFFFFFFF)                                /**< (DMAC_CRCDATAIN) Register Mask  */


/* -------- DMAC_CRCCHKSUM : (DMAC Offset: 0x08) (R/W 32) CRC Checksum -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CRCCHKSUM:32;              /**< bit:  0..31  CRC Checksum                             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_CRCCHKSUM_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CRCCHKSUM_OFFSET               (0x08)                                        /**<  (DMAC_CRCCHKSUM) CRC Checksum  Offset */
#define DMAC_CRCCHKSUM_RESETVALUE           _U_(0x00)                                     /**<  (DMAC_CRCCHKSUM) CRC Checksum  Reset Value */

#define DMAC_CRCCHKSUM_CRCCHKSUM_Pos        0                                              /**< (DMAC_CRCCHKSUM) CRC Checksum Position */
#define DMAC_CRCCHKSUM_CRCCHKSUM_Msk        (_U_(0xFFFFFFFF) << DMAC_CRCCHKSUM_CRCCHKSUM_Pos)  /**< (DMAC_CRCCHKSUM) CRC Checksum Mask */
#define DMAC_CRCCHKSUM_CRCCHKSUM(value)     (DMAC_CRCCHKSUM_CRCCHKSUM_Msk & ((value) << DMAC_CRCCHKSUM_CRCCHKSUM_Pos))
#define DMAC_CRCCHKSUM_MASK                 _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_CRCCHKSUM) Register MASK  (Use DMAC_CRCCHKSUM_Msk instead)  */
#define DMAC_CRCCHKSUM_Msk                  _U_(0xFFFFFFFF)                                /**< (DMAC_CRCCHKSUM) Register Mask  */


/* -------- DMAC_CRCSTATUS : (DMAC Offset: 0x0c) (R/W 8) CRC Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CRCBUSY:1;                 /**< bit:      0  CRC Module Busy                          */
    uint8_t  CRCZERO:1;                 /**< bit:      1  CRC Zero                                 */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CRCSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CRCSTATUS_OFFSET               (0x0C)                                        /**<  (DMAC_CRCSTATUS) CRC Status  Offset */
#define DMAC_CRCSTATUS_RESETVALUE           _U_(0x00)                                     /**<  (DMAC_CRCSTATUS) CRC Status  Reset Value */

#define DMAC_CRCSTATUS_CRCBUSY_Pos          0                                              /**< (DMAC_CRCSTATUS) CRC Module Busy Position */
#define DMAC_CRCSTATUS_CRCBUSY_Msk          (_U_(0x1) << DMAC_CRCSTATUS_CRCBUSY_Pos)       /**< (DMAC_CRCSTATUS) CRC Module Busy Mask */
#define DMAC_CRCSTATUS_CRCBUSY              DMAC_CRCSTATUS_CRCBUSY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CRCSTATUS_CRCBUSY_Msk instead */
#define DMAC_CRCSTATUS_CRCZERO_Pos          1                                              /**< (DMAC_CRCSTATUS) CRC Zero Position */
#define DMAC_CRCSTATUS_CRCZERO_Msk          (_U_(0x1) << DMAC_CRCSTATUS_CRCZERO_Pos)       /**< (DMAC_CRCSTATUS) CRC Zero Mask */
#define DMAC_CRCSTATUS_CRCZERO              DMAC_CRCSTATUS_CRCZERO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CRCSTATUS_CRCZERO_Msk instead */
#define DMAC_CRCSTATUS_MASK                 _U_(0x03)                                      /**< \deprecated (DMAC_CRCSTATUS) Register MASK  (Use DMAC_CRCSTATUS_Msk instead)  */
#define DMAC_CRCSTATUS_Msk                  _U_(0x03)                                      /**< (DMAC_CRCSTATUS) Register Mask  */


/* -------- DMAC_DBGCTRL : (DMAC Offset: 0x0d) (R/W 8) Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGRUN:1;                  /**< bit:      0  Debug Run                                */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_DBGCTRL_OFFSET                 (0x0D)                                        /**<  (DMAC_DBGCTRL) Debug Control  Offset */
#define DMAC_DBGCTRL_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_DBGCTRL) Debug Control  Reset Value */

#define DMAC_DBGCTRL_DBGRUN_Pos             0                                              /**< (DMAC_DBGCTRL) Debug Run Position */
#define DMAC_DBGCTRL_DBGRUN_Msk             (_U_(0x1) << DMAC_DBGCTRL_DBGRUN_Pos)          /**< (DMAC_DBGCTRL) Debug Run Mask */
#define DMAC_DBGCTRL_DBGRUN                 DMAC_DBGCTRL_DBGRUN_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_DBGCTRL_DBGRUN_Msk instead */
#define DMAC_DBGCTRL_MASK                   _U_(0x01)                                      /**< \deprecated (DMAC_DBGCTRL) Register MASK  (Use DMAC_DBGCTRL_Msk instead)  */
#define DMAC_DBGCTRL_Msk                    _U_(0x01)                                      /**< (DMAC_DBGCTRL) Register Mask  */


/* -------- DMAC_QOSCTRL : (DMAC Offset: 0x0e) (R/W 8) QOS Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WRBQOS:2;                  /**< bit:   0..1  Write-Back Quality of Service            */
    uint8_t  FQOS:2;                    /**< bit:   2..3  Fetch Quality of Service                 */
    uint8_t  DQOS:2;                    /**< bit:   4..5  Data Transfer Quality of Service         */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_QOSCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_QOSCTRL_OFFSET                 (0x0E)                                        /**<  (DMAC_QOSCTRL) QOS Control  Offset */
#define DMAC_QOSCTRL_RESETVALUE             _U_(0x2A)                                     /**<  (DMAC_QOSCTRL) QOS Control  Reset Value */

#define DMAC_QOSCTRL_WRBQOS_Pos             0                                              /**< (DMAC_QOSCTRL) Write-Back Quality of Service Position */
#define DMAC_QOSCTRL_WRBQOS_Msk             (_U_(0x3) << DMAC_QOSCTRL_WRBQOS_Pos)          /**< (DMAC_QOSCTRL) Write-Back Quality of Service Mask */
#define DMAC_QOSCTRL_WRBQOS(value)          (DMAC_QOSCTRL_WRBQOS_Msk & ((value) << DMAC_QOSCTRL_WRBQOS_Pos))
#define   DMAC_QOSCTRL_WRBQOS_DISABLE_Val   _U_(0x0)                                       /**< (DMAC_QOSCTRL) Background (no sensitive operation)  */
#define   DMAC_QOSCTRL_WRBQOS_LOW_Val       _U_(0x1)                                       /**< (DMAC_QOSCTRL) Sensitive Bandwidth  */
#define   DMAC_QOSCTRL_WRBQOS_MEDIUM_Val    _U_(0x2)                                       /**< (DMAC_QOSCTRL) Sensitive Latency  */
#define   DMAC_QOSCTRL_WRBQOS_HIGH_Val      _U_(0x3)                                       /**< (DMAC_QOSCTRL) Critical Latency  */
#define DMAC_QOSCTRL_WRBQOS_DISABLE         (DMAC_QOSCTRL_WRBQOS_DISABLE_Val << DMAC_QOSCTRL_WRBQOS_Pos)  /**< (DMAC_QOSCTRL) Background (no sensitive operation) Position  */
#define DMAC_QOSCTRL_WRBQOS_LOW             (DMAC_QOSCTRL_WRBQOS_LOW_Val << DMAC_QOSCTRL_WRBQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Bandwidth Position  */
#define DMAC_QOSCTRL_WRBQOS_MEDIUM          (DMAC_QOSCTRL_WRBQOS_MEDIUM_Val << DMAC_QOSCTRL_WRBQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Latency Position  */
#define DMAC_QOSCTRL_WRBQOS_HIGH            (DMAC_QOSCTRL_WRBQOS_HIGH_Val << DMAC_QOSCTRL_WRBQOS_Pos)  /**< (DMAC_QOSCTRL) Critical Latency Position  */
#define DMAC_QOSCTRL_FQOS_Pos               2                                              /**< (DMAC_QOSCTRL) Fetch Quality of Service Position */
#define DMAC_QOSCTRL_FQOS_Msk               (_U_(0x3) << DMAC_QOSCTRL_FQOS_Pos)            /**< (DMAC_QOSCTRL) Fetch Quality of Service Mask */
#define DMAC_QOSCTRL_FQOS(value)            (DMAC_QOSCTRL_FQOS_Msk & ((value) << DMAC_QOSCTRL_FQOS_Pos))
#define   DMAC_QOSCTRL_FQOS_DISABLE_Val     _U_(0x0)                                       /**< (DMAC_QOSCTRL) Background (no sensitive operation)  */
#define   DMAC_QOSCTRL_FQOS_LOW_Val         _U_(0x1)                                       /**< (DMAC_QOSCTRL) Sensitive Bandwidth  */
#define   DMAC_QOSCTRL_FQOS_MEDIUM_Val      _U_(0x2)                                       /**< (DMAC_QOSCTRL) Sensitive Latency  */
#define   DMAC_QOSCTRL_FQOS_HIGH_Val        _U_(0x3)                                       /**< (DMAC_QOSCTRL) Critical Latency  */
#define DMAC_QOSCTRL_FQOS_DISABLE           (DMAC_QOSCTRL_FQOS_DISABLE_Val << DMAC_QOSCTRL_FQOS_Pos)  /**< (DMAC_QOSCTRL) Background (no sensitive operation) Position  */
#define DMAC_QOSCTRL_FQOS_LOW               (DMAC_QOSCTRL_FQOS_LOW_Val << DMAC_QOSCTRL_FQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Bandwidth Position  */
#define DMAC_QOSCTRL_FQOS_MEDIUM            (DMAC_QOSCTRL_FQOS_MEDIUM_Val << DMAC_QOSCTRL_FQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Latency Position  */
#define DMAC_QOSCTRL_FQOS_HIGH              (DMAC_QOSCTRL_FQOS_HIGH_Val << DMAC_QOSCTRL_FQOS_Pos)  /**< (DMAC_QOSCTRL) Critical Latency Position  */
#define DMAC_QOSCTRL_DQOS_Pos               4                                              /**< (DMAC_QOSCTRL) Data Transfer Quality of Service Position */
#define DMAC_QOSCTRL_DQOS_Msk               (_U_(0x3) << DMAC_QOSCTRL_DQOS_Pos)            /**< (DMAC_QOSCTRL) Data Transfer Quality of Service Mask */
#define DMAC_QOSCTRL_DQOS(value)            (DMAC_QOSCTRL_DQOS_Msk & ((value) << DMAC_QOSCTRL_DQOS_Pos))
#define   DMAC_QOSCTRL_DQOS_DISABLE_Val     _U_(0x0)                                       /**< (DMAC_QOSCTRL) Background (no sensitive operation)  */
#define   DMAC_QOSCTRL_DQOS_LOW_Val         _U_(0x1)                                       /**< (DMAC_QOSCTRL) Sensitive Bandwidth  */
#define   DMAC_QOSCTRL_DQOS_MEDIUM_Val      _U_(0x2)                                       /**< (DMAC_QOSCTRL) Sensitive Latency  */
#define   DMAC_QOSCTRL_DQOS_HIGH_Val        _U_(0x3)                                       /**< (DMAC_QOSCTRL) Critical Latency  */
#define DMAC_QOSCTRL_DQOS_DISABLE           (DMAC_QOSCTRL_DQOS_DISABLE_Val << DMAC_QOSCTRL_DQOS_Pos)  /**< (DMAC_QOSCTRL) Background (no sensitive operation) Position  */
#define DMAC_QOSCTRL_DQOS_LOW               (DMAC_QOSCTRL_DQOS_LOW_Val << DMAC_QOSCTRL_DQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Bandwidth Position  */
#define DMAC_QOSCTRL_DQOS_MEDIUM            (DMAC_QOSCTRL_DQOS_MEDIUM_Val << DMAC_QOSCTRL_DQOS_Pos)  /**< (DMAC_QOSCTRL) Sensitive Latency Position  */
#define DMAC_QOSCTRL_DQOS_HIGH              (DMAC_QOSCTRL_DQOS_HIGH_Val << DMAC_QOSCTRL_DQOS_Pos)  /**< (DMAC_QOSCTRL) Critical Latency Position  */
#define DMAC_QOSCTRL_MASK                   _U_(0x3F)                                      /**< \deprecated (DMAC_QOSCTRL) Register MASK  (Use DMAC_QOSCTRL_Msk instead)  */
#define DMAC_QOSCTRL_Msk                    _U_(0x3F)                                      /**< (DMAC_QOSCTRL) Register Mask  */


/* -------- DMAC_SWTRIGCTRL : (DMAC Offset: 0x10) (R/W 32) Software Trigger Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWTRIG0:1;                 /**< bit:      0  Channel 0 Software Trigger               */
    uint32_t SWTRIG1:1;                 /**< bit:      1  Channel 1 Software Trigger               */
    uint32_t SWTRIG2:1;                 /**< bit:      2  Channel 2 Software Trigger               */
    uint32_t SWTRIG3:1;                 /**< bit:      3  Channel 3 Software Trigger               */
    uint32_t SWTRIG4:1;                 /**< bit:      4  Channel 4 Software Trigger               */
    uint32_t SWTRIG5:1;                 /**< bit:      5  Channel 5 Software Trigger               */
    uint32_t SWTRIG6:1;                 /**< bit:      6  Channel 6 Software Trigger               */
    uint32_t SWTRIG7:1;                 /**< bit:      7  Channel 7 Software Trigger               */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t SWTRIG:8;                  /**< bit:   0..7  Channel 7 Software Trigger               */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_SWTRIGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_SWTRIGCTRL_OFFSET              (0x10)                                        /**<  (DMAC_SWTRIGCTRL) Software Trigger Control  Offset */
#define DMAC_SWTRIGCTRL_RESETVALUE          _U_(0x00)                                     /**<  (DMAC_SWTRIGCTRL) Software Trigger Control  Reset Value */

#define DMAC_SWTRIGCTRL_SWTRIG0_Pos         0                                              /**< (DMAC_SWTRIGCTRL) Channel 0 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG0_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG0_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 0 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG0             DMAC_SWTRIGCTRL_SWTRIG0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG0_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG1_Pos         1                                              /**< (DMAC_SWTRIGCTRL) Channel 1 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG1_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG1_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 1 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG1             DMAC_SWTRIGCTRL_SWTRIG1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG1_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG2_Pos         2                                              /**< (DMAC_SWTRIGCTRL) Channel 2 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG2_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG2_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 2 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG2             DMAC_SWTRIGCTRL_SWTRIG2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG2_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG3_Pos         3                                              /**< (DMAC_SWTRIGCTRL) Channel 3 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG3_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG3_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 3 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG3             DMAC_SWTRIGCTRL_SWTRIG3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG3_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG4_Pos         4                                              /**< (DMAC_SWTRIGCTRL) Channel 4 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG4_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG4_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 4 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG4             DMAC_SWTRIGCTRL_SWTRIG4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG4_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG5_Pos         5                                              /**< (DMAC_SWTRIGCTRL) Channel 5 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG5_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG5_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 5 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG5             DMAC_SWTRIGCTRL_SWTRIG5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG5_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG6_Pos         6                                              /**< (DMAC_SWTRIGCTRL) Channel 6 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG6_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG6_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 6 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG6             DMAC_SWTRIGCTRL_SWTRIG6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG6_Msk instead */
#define DMAC_SWTRIGCTRL_SWTRIG7_Pos         7                                              /**< (DMAC_SWTRIGCTRL) Channel 7 Software Trigger Position */
#define DMAC_SWTRIGCTRL_SWTRIG7_Msk         (_U_(0x1) << DMAC_SWTRIGCTRL_SWTRIG7_Pos)      /**< (DMAC_SWTRIGCTRL) Channel 7 Software Trigger Mask */
#define DMAC_SWTRIGCTRL_SWTRIG7             DMAC_SWTRIGCTRL_SWTRIG7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_SWTRIGCTRL_SWTRIG7_Msk instead */
#define DMAC_SWTRIGCTRL_MASK                _U_(0xFF)                                      /**< \deprecated (DMAC_SWTRIGCTRL) Register MASK  (Use DMAC_SWTRIGCTRL_Msk instead)  */
#define DMAC_SWTRIGCTRL_Msk                 _U_(0xFF)                                      /**< (DMAC_SWTRIGCTRL) Register Mask  */

#define DMAC_SWTRIGCTRL_SWTRIG_Pos          0                                              /**< (DMAC_SWTRIGCTRL Position) Channel 7 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG_Msk          (_U_(0xFF) << DMAC_SWTRIGCTRL_SWTRIG_Pos)      /**< (DMAC_SWTRIGCTRL Mask) SWTRIG */
#define DMAC_SWTRIGCTRL_SWTRIG(value)       (DMAC_SWTRIGCTRL_SWTRIG_Msk & ((value) << DMAC_SWTRIGCTRL_SWTRIG_Pos))  

/* -------- DMAC_PRICTRL0 : (DMAC Offset: 0x14) (R/W 32) Priority Control 0 -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t LVLPRI0:3;                 /**< bit:   0..2  Level 0 Channel Priority Number          */
    uint32_t :4;                        /**< bit:   3..6  Reserved */
    uint32_t RRLVLEN0:1;                /**< bit:      7  Level 0 Round-Robin Scheduling Enable    */
    uint32_t LVLPRI1:3;                 /**< bit:  8..10  Level 1 Channel Priority Number          */
    uint32_t :4;                        /**< bit: 11..14  Reserved */
    uint32_t RRLVLEN1:1;                /**< bit:     15  Level 1 Round-Robin Scheduling Enable    */
    uint32_t LVLPRI2:3;                 /**< bit: 16..18  Level 2 Channel Priority Number          */
    uint32_t :4;                        /**< bit: 19..22  Reserved */
    uint32_t RRLVLEN2:1;                /**< bit:     23  Level 2 Round-Robin Scheduling Enable    */
    uint32_t LVLPRI3:3;                 /**< bit: 24..26  Level 3 Channel Priority Number          */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t RRLVLEN3:1;                /**< bit:     31  Level 3 Round-Robin Scheduling Enable    */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_PRICTRL0_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_PRICTRL0_OFFSET                (0x14)                                        /**<  (DMAC_PRICTRL0) Priority Control 0  Offset */
#define DMAC_PRICTRL0_RESETVALUE            _U_(0x00)                                     /**<  (DMAC_PRICTRL0) Priority Control 0  Reset Value */

#define DMAC_PRICTRL0_LVLPRI0_Pos           0                                              /**< (DMAC_PRICTRL0) Level 0 Channel Priority Number Position */
#define DMAC_PRICTRL0_LVLPRI0_Msk           (_U_(0x7) << DMAC_PRICTRL0_LVLPRI0_Pos)        /**< (DMAC_PRICTRL0) Level 0 Channel Priority Number Mask */
#define DMAC_PRICTRL0_LVLPRI0(value)        (DMAC_PRICTRL0_LVLPRI0_Msk & ((value) << DMAC_PRICTRL0_LVLPRI0_Pos))
#define DMAC_PRICTRL0_RRLVLEN0_Pos          7                                              /**< (DMAC_PRICTRL0) Level 0 Round-Robin Scheduling Enable Position */
#define DMAC_PRICTRL0_RRLVLEN0_Msk          (_U_(0x1) << DMAC_PRICTRL0_RRLVLEN0_Pos)       /**< (DMAC_PRICTRL0) Level 0 Round-Robin Scheduling Enable Mask */
#define DMAC_PRICTRL0_RRLVLEN0              DMAC_PRICTRL0_RRLVLEN0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PRICTRL0_RRLVLEN0_Msk instead */
#define DMAC_PRICTRL0_LVLPRI1_Pos           8                                              /**< (DMAC_PRICTRL0) Level 1 Channel Priority Number Position */
#define DMAC_PRICTRL0_LVLPRI1_Msk           (_U_(0x7) << DMAC_PRICTRL0_LVLPRI1_Pos)        /**< (DMAC_PRICTRL0) Level 1 Channel Priority Number Mask */
#define DMAC_PRICTRL0_LVLPRI1(value)        (DMAC_PRICTRL0_LVLPRI1_Msk & ((value) << DMAC_PRICTRL0_LVLPRI1_Pos))
#define DMAC_PRICTRL0_RRLVLEN1_Pos          15                                             /**< (DMAC_PRICTRL0) Level 1 Round-Robin Scheduling Enable Position */
#define DMAC_PRICTRL0_RRLVLEN1_Msk          (_U_(0x1) << DMAC_PRICTRL0_RRLVLEN1_Pos)       /**< (DMAC_PRICTRL0) Level 1 Round-Robin Scheduling Enable Mask */
#define DMAC_PRICTRL0_RRLVLEN1              DMAC_PRICTRL0_RRLVLEN1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PRICTRL0_RRLVLEN1_Msk instead */
#define DMAC_PRICTRL0_LVLPRI2_Pos           16                                             /**< (DMAC_PRICTRL0) Level 2 Channel Priority Number Position */
#define DMAC_PRICTRL0_LVLPRI2_Msk           (_U_(0x7) << DMAC_PRICTRL0_LVLPRI2_Pos)        /**< (DMAC_PRICTRL0) Level 2 Channel Priority Number Mask */
#define DMAC_PRICTRL0_LVLPRI2(value)        (DMAC_PRICTRL0_LVLPRI2_Msk & ((value) << DMAC_PRICTRL0_LVLPRI2_Pos))
#define DMAC_PRICTRL0_RRLVLEN2_Pos          23                                             /**< (DMAC_PRICTRL0) Level 2 Round-Robin Scheduling Enable Position */
#define DMAC_PRICTRL0_RRLVLEN2_Msk          (_U_(0x1) << DMAC_PRICTRL0_RRLVLEN2_Pos)       /**< (DMAC_PRICTRL0) Level 2 Round-Robin Scheduling Enable Mask */
#define DMAC_PRICTRL0_RRLVLEN2              DMAC_PRICTRL0_RRLVLEN2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PRICTRL0_RRLVLEN2_Msk instead */
#define DMAC_PRICTRL0_LVLPRI3_Pos           24                                             /**< (DMAC_PRICTRL0) Level 3 Channel Priority Number Position */
#define DMAC_PRICTRL0_LVLPRI3_Msk           (_U_(0x7) << DMAC_PRICTRL0_LVLPRI3_Pos)        /**< (DMAC_PRICTRL0) Level 3 Channel Priority Number Mask */
#define DMAC_PRICTRL0_LVLPRI3(value)        (DMAC_PRICTRL0_LVLPRI3_Msk & ((value) << DMAC_PRICTRL0_LVLPRI3_Pos))
#define DMAC_PRICTRL0_RRLVLEN3_Pos          31                                             /**< (DMAC_PRICTRL0) Level 3 Round-Robin Scheduling Enable Position */
#define DMAC_PRICTRL0_RRLVLEN3_Msk          (_U_(0x1) << DMAC_PRICTRL0_RRLVLEN3_Pos)       /**< (DMAC_PRICTRL0) Level 3 Round-Robin Scheduling Enable Mask */
#define DMAC_PRICTRL0_RRLVLEN3              DMAC_PRICTRL0_RRLVLEN3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PRICTRL0_RRLVLEN3_Msk instead */
#define DMAC_PRICTRL0_MASK                  _U_(0x87878787)                                /**< \deprecated (DMAC_PRICTRL0) Register MASK  (Use DMAC_PRICTRL0_Msk instead)  */
#define DMAC_PRICTRL0_Msk                   _U_(0x87878787)                                /**< (DMAC_PRICTRL0) Register Mask  */


/* -------- DMAC_INTPEND : (DMAC Offset: 0x20) (R/W 16) Interrupt Pending -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t ID:3;                      /**< bit:   0..2  Channel ID                               */
    uint16_t :5;                        /**< bit:   3..7  Reserved */
    uint16_t TERR:1;                    /**< bit:      8  Transfer Error                           */
    uint16_t TCMPL:1;                   /**< bit:      9  Transfer Complete                        */
    uint16_t SUSP:1;                    /**< bit:     10  Channel Suspend                          */
    uint16_t :2;                        /**< bit: 11..12  Reserved */
    uint16_t FERR:1;                    /**< bit:     13  Fetch Error                              */
    uint16_t BUSY:1;                    /**< bit:     14  Busy                                     */
    uint16_t PEND:1;                    /**< bit:     15  Pending                                  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} DMAC_INTPEND_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_INTPEND_OFFSET                 (0x20)                                        /**<  (DMAC_INTPEND) Interrupt Pending  Offset */
#define DMAC_INTPEND_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_INTPEND) Interrupt Pending  Reset Value */

#define DMAC_INTPEND_ID_Pos                 0                                              /**< (DMAC_INTPEND) Channel ID Position */
#define DMAC_INTPEND_ID_Msk                 (_U_(0x7) << DMAC_INTPEND_ID_Pos)              /**< (DMAC_INTPEND) Channel ID Mask */
#define DMAC_INTPEND_ID(value)              (DMAC_INTPEND_ID_Msk & ((value) << DMAC_INTPEND_ID_Pos))
#define DMAC_INTPEND_TERR_Pos               8                                              /**< (DMAC_INTPEND) Transfer Error Position */
#define DMAC_INTPEND_TERR_Msk               (_U_(0x1) << DMAC_INTPEND_TERR_Pos)            /**< (DMAC_INTPEND) Transfer Error Mask */
#define DMAC_INTPEND_TERR                   DMAC_INTPEND_TERR_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_TERR_Msk instead */
#define DMAC_INTPEND_TCMPL_Pos              9                                              /**< (DMAC_INTPEND) Transfer Complete Position */
#define DMAC_INTPEND_TCMPL_Msk              (_U_(0x1) << DMAC_INTPEND_TCMPL_Pos)           /**< (DMAC_INTPEND) Transfer Complete Mask */
#define DMAC_INTPEND_TCMPL                  DMAC_INTPEND_TCMPL_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_TCMPL_Msk instead */
#define DMAC_INTPEND_SUSP_Pos               10                                             /**< (DMAC_INTPEND) Channel Suspend Position */
#define DMAC_INTPEND_SUSP_Msk               (_U_(0x1) << DMAC_INTPEND_SUSP_Pos)            /**< (DMAC_INTPEND) Channel Suspend Mask */
#define DMAC_INTPEND_SUSP                   DMAC_INTPEND_SUSP_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_SUSP_Msk instead */
#define DMAC_INTPEND_FERR_Pos               13                                             /**< (DMAC_INTPEND) Fetch Error Position */
#define DMAC_INTPEND_FERR_Msk               (_U_(0x1) << DMAC_INTPEND_FERR_Pos)            /**< (DMAC_INTPEND) Fetch Error Mask */
#define DMAC_INTPEND_FERR                   DMAC_INTPEND_FERR_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_FERR_Msk instead */
#define DMAC_INTPEND_BUSY_Pos               14                                             /**< (DMAC_INTPEND) Busy Position */
#define DMAC_INTPEND_BUSY_Msk               (_U_(0x1) << DMAC_INTPEND_BUSY_Pos)            /**< (DMAC_INTPEND) Busy Mask */
#define DMAC_INTPEND_BUSY                   DMAC_INTPEND_BUSY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_BUSY_Msk instead */
#define DMAC_INTPEND_PEND_Pos               15                                             /**< (DMAC_INTPEND) Pending Position */
#define DMAC_INTPEND_PEND_Msk               (_U_(0x1) << DMAC_INTPEND_PEND_Pos)            /**< (DMAC_INTPEND) Pending Mask */
#define DMAC_INTPEND_PEND                   DMAC_INTPEND_PEND_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTPEND_PEND_Msk instead */
#define DMAC_INTPEND_MASK                   _U_(0xE707)                                    /**< \deprecated (DMAC_INTPEND) Register MASK  (Use DMAC_INTPEND_Msk instead)  */
#define DMAC_INTPEND_Msk                    _U_(0xE707)                                    /**< (DMAC_INTPEND) Register Mask  */


/* -------- DMAC_INTSTATUS : (DMAC Offset: 0x24) (R/ 32) Interrupt Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHINT0:1;                  /**< bit:      0  Channel 0 Pending Interrupt              */
    uint32_t CHINT1:1;                  /**< bit:      1  Channel 1 Pending Interrupt              */
    uint32_t CHINT2:1;                  /**< bit:      2  Channel 2 Pending Interrupt              */
    uint32_t CHINT3:1;                  /**< bit:      3  Channel 3 Pending Interrupt              */
    uint32_t CHINT4:1;                  /**< bit:      4  Channel 4 Pending Interrupt              */
    uint32_t CHINT5:1;                  /**< bit:      5  Channel 5 Pending Interrupt              */
    uint32_t CHINT6:1;                  /**< bit:      6  Channel 6 Pending Interrupt              */
    uint32_t CHINT7:1;                  /**< bit:      7  Channel 7 Pending Interrupt              */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t CHINT:8;                   /**< bit:   0..7  Channel 7 Pending Interrupt              */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_INTSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_INTSTATUS_OFFSET               (0x24)                                        /**<  (DMAC_INTSTATUS) Interrupt Status  Offset */
#define DMAC_INTSTATUS_RESETVALUE           _U_(0x00)                                     /**<  (DMAC_INTSTATUS) Interrupt Status  Reset Value */

#define DMAC_INTSTATUS_CHINT0_Pos           0                                              /**< (DMAC_INTSTATUS) Channel 0 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT0_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT0_Pos)        /**< (DMAC_INTSTATUS) Channel 0 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT0               DMAC_INTSTATUS_CHINT0_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT0_Msk instead */
#define DMAC_INTSTATUS_CHINT1_Pos           1                                              /**< (DMAC_INTSTATUS) Channel 1 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT1_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT1_Pos)        /**< (DMAC_INTSTATUS) Channel 1 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT1               DMAC_INTSTATUS_CHINT1_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT1_Msk instead */
#define DMAC_INTSTATUS_CHINT2_Pos           2                                              /**< (DMAC_INTSTATUS) Channel 2 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT2_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT2_Pos)        /**< (DMAC_INTSTATUS) Channel 2 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT2               DMAC_INTSTATUS_CHINT2_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT2_Msk instead */
#define DMAC_INTSTATUS_CHINT3_Pos           3                                              /**< (DMAC_INTSTATUS) Channel 3 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT3_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT3_Pos)        /**< (DMAC_INTSTATUS) Channel 3 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT3               DMAC_INTSTATUS_CHINT3_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT3_Msk instead */
#define DMAC_INTSTATUS_CHINT4_Pos           4                                              /**< (DMAC_INTSTATUS) Channel 4 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT4_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT4_Pos)        /**< (DMAC_INTSTATUS) Channel 4 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT4               DMAC_INTSTATUS_CHINT4_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT4_Msk instead */
#define DMAC_INTSTATUS_CHINT5_Pos           5                                              /**< (DMAC_INTSTATUS) Channel 5 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT5_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT5_Pos)        /**< (DMAC_INTSTATUS) Channel 5 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT5               DMAC_INTSTATUS_CHINT5_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT5_Msk instead */
#define DMAC_INTSTATUS_CHINT6_Pos           6                                              /**< (DMAC_INTSTATUS) Channel 6 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT6_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT6_Pos)        /**< (DMAC_INTSTATUS) Channel 6 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT6               DMAC_INTSTATUS_CHINT6_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT6_Msk instead */
#define DMAC_INTSTATUS_CHINT7_Pos           7                                              /**< (DMAC_INTSTATUS) Channel 7 Pending Interrupt Position */
#define DMAC_INTSTATUS_CHINT7_Msk           (_U_(0x1) << DMAC_INTSTATUS_CHINT7_Pos)        /**< (DMAC_INTSTATUS) Channel 7 Pending Interrupt Mask */
#define DMAC_INTSTATUS_CHINT7               DMAC_INTSTATUS_CHINT7_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_INTSTATUS_CHINT7_Msk instead */
#define DMAC_INTSTATUS_MASK                 _U_(0xFF)                                      /**< \deprecated (DMAC_INTSTATUS) Register MASK  (Use DMAC_INTSTATUS_Msk instead)  */
#define DMAC_INTSTATUS_Msk                  _U_(0xFF)                                      /**< (DMAC_INTSTATUS) Register Mask  */

#define DMAC_INTSTATUS_CHINT_Pos            0                                              /**< (DMAC_INTSTATUS Position) Channel 7 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT_Msk            (_U_(0xFF) << DMAC_INTSTATUS_CHINT_Pos)        /**< (DMAC_INTSTATUS Mask) CHINT */
#define DMAC_INTSTATUS_CHINT(value)         (DMAC_INTSTATUS_CHINT_Msk & ((value) << DMAC_INTSTATUS_CHINT_Pos))  

/* -------- DMAC_BUSYCH : (DMAC Offset: 0x28) (R/ 32) Busy Channels -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUSYCH0:1;                 /**< bit:      0  Busy Channel 0                           */
    uint32_t BUSYCH1:1;                 /**< bit:      1  Busy Channel 1                           */
    uint32_t BUSYCH2:1;                 /**< bit:      2  Busy Channel 2                           */
    uint32_t BUSYCH3:1;                 /**< bit:      3  Busy Channel 3                           */
    uint32_t BUSYCH4:1;                 /**< bit:      4  Busy Channel 4                           */
    uint32_t BUSYCH5:1;                 /**< bit:      5  Busy Channel 5                           */
    uint32_t BUSYCH6:1;                 /**< bit:      6  Busy Channel 6                           */
    uint32_t BUSYCH7:1;                 /**< bit:      7  Busy Channel 7                           */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t BUSYCH:8;                  /**< bit:   0..7  Busy Channel 7                           */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_BUSYCH_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_BUSYCH_OFFSET                  (0x28)                                        /**<  (DMAC_BUSYCH) Busy Channels  Offset */
#define DMAC_BUSYCH_RESETVALUE              _U_(0x00)                                     /**<  (DMAC_BUSYCH) Busy Channels  Reset Value */

#define DMAC_BUSYCH_BUSYCH0_Pos             0                                              /**< (DMAC_BUSYCH) Busy Channel 0 Position */
#define DMAC_BUSYCH_BUSYCH0_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH0_Pos)          /**< (DMAC_BUSYCH) Busy Channel 0 Mask */
#define DMAC_BUSYCH_BUSYCH0                 DMAC_BUSYCH_BUSYCH0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH0_Msk instead */
#define DMAC_BUSYCH_BUSYCH1_Pos             1                                              /**< (DMAC_BUSYCH) Busy Channel 1 Position */
#define DMAC_BUSYCH_BUSYCH1_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH1_Pos)          /**< (DMAC_BUSYCH) Busy Channel 1 Mask */
#define DMAC_BUSYCH_BUSYCH1                 DMAC_BUSYCH_BUSYCH1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH1_Msk instead */
#define DMAC_BUSYCH_BUSYCH2_Pos             2                                              /**< (DMAC_BUSYCH) Busy Channel 2 Position */
#define DMAC_BUSYCH_BUSYCH2_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH2_Pos)          /**< (DMAC_BUSYCH) Busy Channel 2 Mask */
#define DMAC_BUSYCH_BUSYCH2                 DMAC_BUSYCH_BUSYCH2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH2_Msk instead */
#define DMAC_BUSYCH_BUSYCH3_Pos             3                                              /**< (DMAC_BUSYCH) Busy Channel 3 Position */
#define DMAC_BUSYCH_BUSYCH3_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH3_Pos)          /**< (DMAC_BUSYCH) Busy Channel 3 Mask */
#define DMAC_BUSYCH_BUSYCH3                 DMAC_BUSYCH_BUSYCH3_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH3_Msk instead */
#define DMAC_BUSYCH_BUSYCH4_Pos             4                                              /**< (DMAC_BUSYCH) Busy Channel 4 Position */
#define DMAC_BUSYCH_BUSYCH4_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH4_Pos)          /**< (DMAC_BUSYCH) Busy Channel 4 Mask */
#define DMAC_BUSYCH_BUSYCH4                 DMAC_BUSYCH_BUSYCH4_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH4_Msk instead */
#define DMAC_BUSYCH_BUSYCH5_Pos             5                                              /**< (DMAC_BUSYCH) Busy Channel 5 Position */
#define DMAC_BUSYCH_BUSYCH5_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH5_Pos)          /**< (DMAC_BUSYCH) Busy Channel 5 Mask */
#define DMAC_BUSYCH_BUSYCH5                 DMAC_BUSYCH_BUSYCH5_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH5_Msk instead */
#define DMAC_BUSYCH_BUSYCH6_Pos             6                                              /**< (DMAC_BUSYCH) Busy Channel 6 Position */
#define DMAC_BUSYCH_BUSYCH6_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH6_Pos)          /**< (DMAC_BUSYCH) Busy Channel 6 Mask */
#define DMAC_BUSYCH_BUSYCH6                 DMAC_BUSYCH_BUSYCH6_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH6_Msk instead */
#define DMAC_BUSYCH_BUSYCH7_Pos             7                                              /**< (DMAC_BUSYCH) Busy Channel 7 Position */
#define DMAC_BUSYCH_BUSYCH7_Msk             (_U_(0x1) << DMAC_BUSYCH_BUSYCH7_Pos)          /**< (DMAC_BUSYCH) Busy Channel 7 Mask */
#define DMAC_BUSYCH_BUSYCH7                 DMAC_BUSYCH_BUSYCH7_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_BUSYCH_BUSYCH7_Msk instead */
#define DMAC_BUSYCH_MASK                    _U_(0xFF)                                      /**< \deprecated (DMAC_BUSYCH) Register MASK  (Use DMAC_BUSYCH_Msk instead)  */
#define DMAC_BUSYCH_Msk                     _U_(0xFF)                                      /**< (DMAC_BUSYCH) Register Mask  */

#define DMAC_BUSYCH_BUSYCH_Pos              0                                              /**< (DMAC_BUSYCH Position) Busy Channel 7 */
#define DMAC_BUSYCH_BUSYCH_Msk              (_U_(0xFF) << DMAC_BUSYCH_BUSYCH_Pos)          /**< (DMAC_BUSYCH Mask) BUSYCH */
#define DMAC_BUSYCH_BUSYCH(value)           (DMAC_BUSYCH_BUSYCH_Msk & ((value) << DMAC_BUSYCH_BUSYCH_Pos))  

/* -------- DMAC_PENDCH : (DMAC Offset: 0x2c) (R/ 32) Pending Channels -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PENDCH0:1;                 /**< bit:      0  Pending Channel 0                        */
    uint32_t PENDCH1:1;                 /**< bit:      1  Pending Channel 1                        */
    uint32_t PENDCH2:1;                 /**< bit:      2  Pending Channel 2                        */
    uint32_t PENDCH3:1;                 /**< bit:      3  Pending Channel 3                        */
    uint32_t PENDCH4:1;                 /**< bit:      4  Pending Channel 4                        */
    uint32_t PENDCH5:1;                 /**< bit:      5  Pending Channel 5                        */
    uint32_t PENDCH6:1;                 /**< bit:      6  Pending Channel 6                        */
    uint32_t PENDCH7:1;                 /**< bit:      7  Pending Channel 7                        */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t PENDCH:8;                  /**< bit:   0..7  Pending Channel 7                        */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_PENDCH_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_PENDCH_OFFSET                  (0x2C)                                        /**<  (DMAC_PENDCH) Pending Channels  Offset */
#define DMAC_PENDCH_RESETVALUE              _U_(0x00)                                     /**<  (DMAC_PENDCH) Pending Channels  Reset Value */

#define DMAC_PENDCH_PENDCH0_Pos             0                                              /**< (DMAC_PENDCH) Pending Channel 0 Position */
#define DMAC_PENDCH_PENDCH0_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH0_Pos)          /**< (DMAC_PENDCH) Pending Channel 0 Mask */
#define DMAC_PENDCH_PENDCH0                 DMAC_PENDCH_PENDCH0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH0_Msk instead */
#define DMAC_PENDCH_PENDCH1_Pos             1                                              /**< (DMAC_PENDCH) Pending Channel 1 Position */
#define DMAC_PENDCH_PENDCH1_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH1_Pos)          /**< (DMAC_PENDCH) Pending Channel 1 Mask */
#define DMAC_PENDCH_PENDCH1                 DMAC_PENDCH_PENDCH1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH1_Msk instead */
#define DMAC_PENDCH_PENDCH2_Pos             2                                              /**< (DMAC_PENDCH) Pending Channel 2 Position */
#define DMAC_PENDCH_PENDCH2_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH2_Pos)          /**< (DMAC_PENDCH) Pending Channel 2 Mask */
#define DMAC_PENDCH_PENDCH2                 DMAC_PENDCH_PENDCH2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH2_Msk instead */
#define DMAC_PENDCH_PENDCH3_Pos             3                                              /**< (DMAC_PENDCH) Pending Channel 3 Position */
#define DMAC_PENDCH_PENDCH3_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH3_Pos)          /**< (DMAC_PENDCH) Pending Channel 3 Mask */
#define DMAC_PENDCH_PENDCH3                 DMAC_PENDCH_PENDCH3_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH3_Msk instead */
#define DMAC_PENDCH_PENDCH4_Pos             4                                              /**< (DMAC_PENDCH) Pending Channel 4 Position */
#define DMAC_PENDCH_PENDCH4_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH4_Pos)          /**< (DMAC_PENDCH) Pending Channel 4 Mask */
#define DMAC_PENDCH_PENDCH4                 DMAC_PENDCH_PENDCH4_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH4_Msk instead */
#define DMAC_PENDCH_PENDCH5_Pos             5                                              /**< (DMAC_PENDCH) Pending Channel 5 Position */
#define DMAC_PENDCH_PENDCH5_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH5_Pos)          /**< (DMAC_PENDCH) Pending Channel 5 Mask */
#define DMAC_PENDCH_PENDCH5                 DMAC_PENDCH_PENDCH5_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH5_Msk instead */
#define DMAC_PENDCH_PENDCH6_Pos             6                                              /**< (DMAC_PENDCH) Pending Channel 6 Position */
#define DMAC_PENDCH_PENDCH6_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH6_Pos)          /**< (DMAC_PENDCH) Pending Channel 6 Mask */
#define DMAC_PENDCH_PENDCH6                 DMAC_PENDCH_PENDCH6_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH6_Msk instead */
#define DMAC_PENDCH_PENDCH7_Pos             7                                              /**< (DMAC_PENDCH) Pending Channel 7 Position */
#define DMAC_PENDCH_PENDCH7_Msk             (_U_(0x1) << DMAC_PENDCH_PENDCH7_Pos)          /**< (DMAC_PENDCH) Pending Channel 7 Mask */
#define DMAC_PENDCH_PENDCH7                 DMAC_PENDCH_PENDCH7_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_PENDCH_PENDCH7_Msk instead */
#define DMAC_PENDCH_MASK                    _U_(0xFF)                                      /**< \deprecated (DMAC_PENDCH) Register MASK  (Use DMAC_PENDCH_Msk instead)  */
#define DMAC_PENDCH_Msk                     _U_(0xFF)                                      /**< (DMAC_PENDCH) Register Mask  */

#define DMAC_PENDCH_PENDCH_Pos              0                                              /**< (DMAC_PENDCH Position) Pending Channel 7 */
#define DMAC_PENDCH_PENDCH_Msk              (_U_(0xFF) << DMAC_PENDCH_PENDCH_Pos)          /**< (DMAC_PENDCH Mask) PENDCH */
#define DMAC_PENDCH_PENDCH(value)           (DMAC_PENDCH_PENDCH_Msk & ((value) << DMAC_PENDCH_PENDCH_Pos))  

/* -------- DMAC_ACTIVE : (DMAC Offset: 0x30) (R/ 32) Active Channel and Levels -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t LVLEX0:1;                  /**< bit:      0  Level 0 Channel Trigger Request Executing */
    uint32_t LVLEX1:1;                  /**< bit:      1  Level 1 Channel Trigger Request Executing */
    uint32_t LVLEX2:1;                  /**< bit:      2  Level 2 Channel Trigger Request Executing */
    uint32_t LVLEX3:1;                  /**< bit:      3  Level 3 Channel Trigger Request Executing */
    uint32_t :4;                        /**< bit:   4..7  Reserved */
    uint32_t ID:5;                      /**< bit:  8..12  Active Channel ID                        */
    uint32_t :2;                        /**< bit: 13..14  Reserved */
    uint32_t ABUSY:1;                   /**< bit:     15  Active Channel Busy                      */
    uint32_t BTCNT:16;                  /**< bit: 16..31  Active Channel Block Transfer Count      */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t LVLEX:4;                   /**< bit:   0..3  Level x Channel Trigger Request Executing */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_ACTIVE_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_ACTIVE_OFFSET                  (0x30)                                        /**<  (DMAC_ACTIVE) Active Channel and Levels  Offset */
#define DMAC_ACTIVE_RESETVALUE              _U_(0x00)                                     /**<  (DMAC_ACTIVE) Active Channel and Levels  Reset Value */

#define DMAC_ACTIVE_LVLEX0_Pos              0                                              /**< (DMAC_ACTIVE) Level 0 Channel Trigger Request Executing Position */
#define DMAC_ACTIVE_LVLEX0_Msk              (_U_(0x1) << DMAC_ACTIVE_LVLEX0_Pos)           /**< (DMAC_ACTIVE) Level 0 Channel Trigger Request Executing Mask */
#define DMAC_ACTIVE_LVLEX0                  DMAC_ACTIVE_LVLEX0_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_ACTIVE_LVLEX0_Msk instead */
#define DMAC_ACTIVE_LVLEX1_Pos              1                                              /**< (DMAC_ACTIVE) Level 1 Channel Trigger Request Executing Position */
#define DMAC_ACTIVE_LVLEX1_Msk              (_U_(0x1) << DMAC_ACTIVE_LVLEX1_Pos)           /**< (DMAC_ACTIVE) Level 1 Channel Trigger Request Executing Mask */
#define DMAC_ACTIVE_LVLEX1                  DMAC_ACTIVE_LVLEX1_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_ACTIVE_LVLEX1_Msk instead */
#define DMAC_ACTIVE_LVLEX2_Pos              2                                              /**< (DMAC_ACTIVE) Level 2 Channel Trigger Request Executing Position */
#define DMAC_ACTIVE_LVLEX2_Msk              (_U_(0x1) << DMAC_ACTIVE_LVLEX2_Pos)           /**< (DMAC_ACTIVE) Level 2 Channel Trigger Request Executing Mask */
#define DMAC_ACTIVE_LVLEX2                  DMAC_ACTIVE_LVLEX2_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_ACTIVE_LVLEX2_Msk instead */
#define DMAC_ACTIVE_LVLEX3_Pos              3                                              /**< (DMAC_ACTIVE) Level 3 Channel Trigger Request Executing Position */
#define DMAC_ACTIVE_LVLEX3_Msk              (_U_(0x1) << DMAC_ACTIVE_LVLEX3_Pos)           /**< (DMAC_ACTIVE) Level 3 Channel Trigger Request Executing Mask */
#define DMAC_ACTIVE_LVLEX3                  DMAC_ACTIVE_LVLEX3_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_ACTIVE_LVLEX3_Msk instead */
#define DMAC_ACTIVE_ID_Pos                  8                                              /**< (DMAC_ACTIVE) Active Channel ID Position */
#define DMAC_ACTIVE_ID_Msk                  (_U_(0x1F) << DMAC_ACTIVE_ID_Pos)              /**< (DMAC_ACTIVE) Active Channel ID Mask */
#define DMAC_ACTIVE_ID(value)               (DMAC_ACTIVE_ID_Msk & ((value) << DMAC_ACTIVE_ID_Pos))
#define DMAC_ACTIVE_ABUSY_Pos               15                                             /**< (DMAC_ACTIVE) Active Channel Busy Position */
#define DMAC_ACTIVE_ABUSY_Msk               (_U_(0x1) << DMAC_ACTIVE_ABUSY_Pos)            /**< (DMAC_ACTIVE) Active Channel Busy Mask */
#define DMAC_ACTIVE_ABUSY                   DMAC_ACTIVE_ABUSY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_ACTIVE_ABUSY_Msk instead */
#define DMAC_ACTIVE_BTCNT_Pos               16                                             /**< (DMAC_ACTIVE) Active Channel Block Transfer Count Position */
#define DMAC_ACTIVE_BTCNT_Msk               (_U_(0xFFFF) << DMAC_ACTIVE_BTCNT_Pos)         /**< (DMAC_ACTIVE) Active Channel Block Transfer Count Mask */
#define DMAC_ACTIVE_BTCNT(value)            (DMAC_ACTIVE_BTCNT_Msk & ((value) << DMAC_ACTIVE_BTCNT_Pos))
#define DMAC_ACTIVE_MASK                    _U_(0xFFFF9F0F)                                /**< \deprecated (DMAC_ACTIVE) Register MASK  (Use DMAC_ACTIVE_Msk instead)  */
#define DMAC_ACTIVE_Msk                     _U_(0xFFFF9F0F)                                /**< (DMAC_ACTIVE) Register Mask  */

#define DMAC_ACTIVE_LVLEX_Pos               0                                              /**< (DMAC_ACTIVE Position) Level x Channel Trigger Request Executing */
#define DMAC_ACTIVE_LVLEX_Msk               (_U_(0xF) << DMAC_ACTIVE_LVLEX_Pos)            /**< (DMAC_ACTIVE Mask) LVLEX */
#define DMAC_ACTIVE_LVLEX(value)            (DMAC_ACTIVE_LVLEX_Msk & ((value) << DMAC_ACTIVE_LVLEX_Pos))  

/* -------- DMAC_BASEADDR : (DMAC Offset: 0x34) (R/W 32) Descriptor Memory Section Base Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BASEADDR:32;               /**< bit:  0..31  Descriptor Memory Base Address           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_BASEADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_BASEADDR_OFFSET                (0x34)                                        /**<  (DMAC_BASEADDR) Descriptor Memory Section Base Address  Offset */
#define DMAC_BASEADDR_RESETVALUE            _U_(0x00)                                     /**<  (DMAC_BASEADDR) Descriptor Memory Section Base Address  Reset Value */

#define DMAC_BASEADDR_BASEADDR_Pos          0                                              /**< (DMAC_BASEADDR) Descriptor Memory Base Address Position */
#define DMAC_BASEADDR_BASEADDR_Msk          (_U_(0xFFFFFFFF) << DMAC_BASEADDR_BASEADDR_Pos)  /**< (DMAC_BASEADDR) Descriptor Memory Base Address Mask */
#define DMAC_BASEADDR_BASEADDR(value)       (DMAC_BASEADDR_BASEADDR_Msk & ((value) << DMAC_BASEADDR_BASEADDR_Pos))
#define DMAC_BASEADDR_MASK                  _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_BASEADDR) Register MASK  (Use DMAC_BASEADDR_Msk instead)  */
#define DMAC_BASEADDR_Msk                   _U_(0xFFFFFFFF)                                /**< (DMAC_BASEADDR) Register Mask  */


/* -------- DMAC_WRBADDR : (DMAC Offset: 0x38) (R/W 32) Write-Back Memory Section Base Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WRBADDR:32;                /**< bit:  0..31  Write-Back Memory Base Address           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_WRBADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_WRBADDR_OFFSET                 (0x38)                                        /**<  (DMAC_WRBADDR) Write-Back Memory Section Base Address  Offset */
#define DMAC_WRBADDR_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_WRBADDR) Write-Back Memory Section Base Address  Reset Value */

#define DMAC_WRBADDR_WRBADDR_Pos            0                                              /**< (DMAC_WRBADDR) Write-Back Memory Base Address Position */
#define DMAC_WRBADDR_WRBADDR_Msk            (_U_(0xFFFFFFFF) << DMAC_WRBADDR_WRBADDR_Pos)  /**< (DMAC_WRBADDR) Write-Back Memory Base Address Mask */
#define DMAC_WRBADDR_WRBADDR(value)         (DMAC_WRBADDR_WRBADDR_Msk & ((value) << DMAC_WRBADDR_WRBADDR_Pos))
#define DMAC_WRBADDR_MASK                   _U_(0xFFFFFFFF)                                /**< \deprecated (DMAC_WRBADDR) Register MASK  (Use DMAC_WRBADDR_Msk instead)  */
#define DMAC_WRBADDR_Msk                    _U_(0xFFFFFFFF)                                /**< (DMAC_WRBADDR) Register Mask  */


/* -------- DMAC_CHID : (DMAC Offset: 0x3f) (R/W 8) Channel ID -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ID:3;                      /**< bit:   0..2  Channel ID                               */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHID_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHID_OFFSET                    (0x3F)                                        /**<  (DMAC_CHID) Channel ID  Offset */
#define DMAC_CHID_RESETVALUE                _U_(0x00)                                     /**<  (DMAC_CHID) Channel ID  Reset Value */

#define DMAC_CHID_ID_Pos                    0                                              /**< (DMAC_CHID) Channel ID Position */
#define DMAC_CHID_ID_Msk                    (_U_(0x7) << DMAC_CHID_ID_Pos)                 /**< (DMAC_CHID) Channel ID Mask */
#define DMAC_CHID_ID(value)                 (DMAC_CHID_ID_Msk & ((value) << DMAC_CHID_ID_Pos))
#define DMAC_CHID_MASK                      _U_(0x07)                                      /**< \deprecated (DMAC_CHID) Register MASK  (Use DMAC_CHID_Msk instead)  */
#define DMAC_CHID_Msk                       _U_(0x07)                                      /**< (DMAC_CHID) Register Mask  */


/* -------- DMAC_CHCTRLA : (DMAC Offset: 0x40) (R/W 8) Channel Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Channel Software Reset                   */
    uint8_t  ENABLE:1;                  /**< bit:      1  Channel Enable                           */
    uint8_t  :4;                        /**< bit:   2..5  Reserved */
    uint8_t  RUNSTDBY:1;                /**< bit:      6  Channel run in standby                   */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHCTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHCTRLA_OFFSET                 (0x40)                                        /**<  (DMAC_CHCTRLA) Channel Control A  Offset */
#define DMAC_CHCTRLA_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_CHCTRLA) Channel Control A  Reset Value */

#define DMAC_CHCTRLA_SWRST_Pos              0                                              /**< (DMAC_CHCTRLA) Channel Software Reset Position */
#define DMAC_CHCTRLA_SWRST_Msk              (_U_(0x1) << DMAC_CHCTRLA_SWRST_Pos)           /**< (DMAC_CHCTRLA) Channel Software Reset Mask */
#define DMAC_CHCTRLA_SWRST                  DMAC_CHCTRLA_SWRST_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHCTRLA_SWRST_Msk instead */
#define DMAC_CHCTRLA_ENABLE_Pos             1                                              /**< (DMAC_CHCTRLA) Channel Enable Position */
#define DMAC_CHCTRLA_ENABLE_Msk             (_U_(0x1) << DMAC_CHCTRLA_ENABLE_Pos)          /**< (DMAC_CHCTRLA) Channel Enable Mask */
#define DMAC_CHCTRLA_ENABLE                 DMAC_CHCTRLA_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHCTRLA_ENABLE_Msk instead */
#define DMAC_CHCTRLA_RUNSTDBY_Pos           6                                              /**< (DMAC_CHCTRLA) Channel run in standby Position */
#define DMAC_CHCTRLA_RUNSTDBY_Msk           (_U_(0x1) << DMAC_CHCTRLA_RUNSTDBY_Pos)        /**< (DMAC_CHCTRLA) Channel run in standby Mask */
#define DMAC_CHCTRLA_RUNSTDBY               DMAC_CHCTRLA_RUNSTDBY_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHCTRLA_RUNSTDBY_Msk instead */
#define DMAC_CHCTRLA_MASK                   _U_(0x43)                                      /**< \deprecated (DMAC_CHCTRLA) Register MASK  (Use DMAC_CHCTRLA_Msk instead)  */
#define DMAC_CHCTRLA_Msk                    _U_(0x43)                                      /**< (DMAC_CHCTRLA) Register Mask  */


/* -------- DMAC_CHCTRLB : (DMAC Offset: 0x44) (R/W 32) Channel Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVACT:3;                   /**< bit:   0..2  Event Input Action                       */
    uint32_t EVIE:1;                    /**< bit:      3  Channel Event Input Enable               */
    uint32_t EVOE:1;                    /**< bit:      4  Channel Event Output Enable              */
    uint32_t LVL:2;                     /**< bit:   5..6  Channel Arbitration Level                */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t TRIGSRC:5;                 /**< bit:  8..12  Trigger Source                           */
    uint32_t :9;                        /**< bit: 13..21  Reserved */
    uint32_t TRIGACT:2;                 /**< bit: 22..23  Trigger Action                           */
    uint32_t CMD:2;                     /**< bit: 24..25  Software Command                         */
    uint32_t :6;                        /**< bit: 26..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DMAC_CHCTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHCTRLB_OFFSET                 (0x44)                                        /**<  (DMAC_CHCTRLB) Channel Control B  Offset */
#define DMAC_CHCTRLB_RESETVALUE             _U_(0x00)                                     /**<  (DMAC_CHCTRLB) Channel Control B  Reset Value */

#define DMAC_CHCTRLB_EVACT_Pos              0                                              /**< (DMAC_CHCTRLB) Event Input Action Position */
#define DMAC_CHCTRLB_EVACT_Msk              (_U_(0x7) << DMAC_CHCTRLB_EVACT_Pos)           /**< (DMAC_CHCTRLB) Event Input Action Mask */
#define DMAC_CHCTRLB_EVACT(value)           (DMAC_CHCTRLB_EVACT_Msk & ((value) << DMAC_CHCTRLB_EVACT_Pos))
#define   DMAC_CHCTRLB_EVACT_NOACT_Val      _U_(0x0)                                       /**< (DMAC_CHCTRLB) No action  */
#define   DMAC_CHCTRLB_EVACT_TRIG_Val       _U_(0x1)                                       /**< (DMAC_CHCTRLB) Transfer and periodic transfer trigger  */
#define   DMAC_CHCTRLB_EVACT_CTRIG_Val      _U_(0x2)                                       /**< (DMAC_CHCTRLB) Conditional transfer trigger  */
#define   DMAC_CHCTRLB_EVACT_CBLOCK_Val     _U_(0x3)                                       /**< (DMAC_CHCTRLB) Conditional block transfer  */
#define   DMAC_CHCTRLB_EVACT_SUSPEND_Val    _U_(0x4)                                       /**< (DMAC_CHCTRLB) Channel suspend operation  */
#define   DMAC_CHCTRLB_EVACT_RESUME_Val     _U_(0x5)                                       /**< (DMAC_CHCTRLB) Channel resume operation  */
#define   DMAC_CHCTRLB_EVACT_SSKIP_Val      _U_(0x6)                                       /**< (DMAC_CHCTRLB) Skip next block suspend action  */
#define DMAC_CHCTRLB_EVACT_NOACT            (DMAC_CHCTRLB_EVACT_NOACT_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) No action Position  */
#define DMAC_CHCTRLB_EVACT_TRIG             (DMAC_CHCTRLB_EVACT_TRIG_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Transfer and periodic transfer trigger Position  */
#define DMAC_CHCTRLB_EVACT_CTRIG            (DMAC_CHCTRLB_EVACT_CTRIG_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Conditional transfer trigger Position  */
#define DMAC_CHCTRLB_EVACT_CBLOCK           (DMAC_CHCTRLB_EVACT_CBLOCK_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Conditional block transfer Position  */
#define DMAC_CHCTRLB_EVACT_SUSPEND          (DMAC_CHCTRLB_EVACT_SUSPEND_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Channel suspend operation Position  */
#define DMAC_CHCTRLB_EVACT_RESUME           (DMAC_CHCTRLB_EVACT_RESUME_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Channel resume operation Position  */
#define DMAC_CHCTRLB_EVACT_SSKIP            (DMAC_CHCTRLB_EVACT_SSKIP_Val << DMAC_CHCTRLB_EVACT_Pos)  /**< (DMAC_CHCTRLB) Skip next block suspend action Position  */
#define DMAC_CHCTRLB_EVIE_Pos               3                                              /**< (DMAC_CHCTRLB) Channel Event Input Enable Position */
#define DMAC_CHCTRLB_EVIE_Msk               (_U_(0x1) << DMAC_CHCTRLB_EVIE_Pos)            /**< (DMAC_CHCTRLB) Channel Event Input Enable Mask */
#define DMAC_CHCTRLB_EVIE                   DMAC_CHCTRLB_EVIE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHCTRLB_EVIE_Msk instead */
#define DMAC_CHCTRLB_EVOE_Pos               4                                              /**< (DMAC_CHCTRLB) Channel Event Output Enable Position */
#define DMAC_CHCTRLB_EVOE_Msk               (_U_(0x1) << DMAC_CHCTRLB_EVOE_Pos)            /**< (DMAC_CHCTRLB) Channel Event Output Enable Mask */
#define DMAC_CHCTRLB_EVOE                   DMAC_CHCTRLB_EVOE_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHCTRLB_EVOE_Msk instead */
#define DMAC_CHCTRLB_LVL_Pos                5                                              /**< (DMAC_CHCTRLB) Channel Arbitration Level Position */
#define DMAC_CHCTRLB_LVL_Msk                (_U_(0x3) << DMAC_CHCTRLB_LVL_Pos)             /**< (DMAC_CHCTRLB) Channel Arbitration Level Mask */
#define DMAC_CHCTRLB_LVL(value)             (DMAC_CHCTRLB_LVL_Msk & ((value) << DMAC_CHCTRLB_LVL_Pos))
#define DMAC_CHCTRLB_TRIGSRC_Pos            8                                              /**< (DMAC_CHCTRLB) Trigger Source Position */
#define DMAC_CHCTRLB_TRIGSRC_Msk            (_U_(0x1F) << DMAC_CHCTRLB_TRIGSRC_Pos)        /**< (DMAC_CHCTRLB) Trigger Source Mask */
#define DMAC_CHCTRLB_TRIGSRC(value)         (DMAC_CHCTRLB_TRIGSRC_Msk & ((value) << DMAC_CHCTRLB_TRIGSRC_Pos))
#define   DMAC_CHCTRLB_TRIGSRC_DISABLE_Val  _U_(0x0)                                       /**< (DMAC_CHCTRLB) Only software/event triggers  */
#define DMAC_CHCTRLB_TRIGSRC_DISABLE        (DMAC_CHCTRLB_TRIGSRC_DISABLE_Val << DMAC_CHCTRLB_TRIGSRC_Pos)  /**< (DMAC_CHCTRLB) Only software/event triggers Position  */
#define DMAC_CHCTRLB_TRIGACT_Pos            22                                             /**< (DMAC_CHCTRLB) Trigger Action Position */
#define DMAC_CHCTRLB_TRIGACT_Msk            (_U_(0x3) << DMAC_CHCTRLB_TRIGACT_Pos)         /**< (DMAC_CHCTRLB) Trigger Action Mask */
#define DMAC_CHCTRLB_TRIGACT(value)         (DMAC_CHCTRLB_TRIGACT_Msk & ((value) << DMAC_CHCTRLB_TRIGACT_Pos))
#define   DMAC_CHCTRLB_TRIGACT_BLOCK_Val    _U_(0x0)                                       /**< (DMAC_CHCTRLB) One trigger required for each block transfer  */
#define   DMAC_CHCTRLB_TRIGACT_BEAT_Val     _U_(0x2)                                       /**< (DMAC_CHCTRLB) One trigger required for each beat transfer  */
#define   DMAC_CHCTRLB_TRIGACT_TRANSACTION_Val _U_(0x3)                                       /**< (DMAC_CHCTRLB) One trigger required for each transaction  */
#define DMAC_CHCTRLB_TRIGACT_BLOCK          (DMAC_CHCTRLB_TRIGACT_BLOCK_Val << DMAC_CHCTRLB_TRIGACT_Pos)  /**< (DMAC_CHCTRLB) One trigger required for each block transfer Position  */
#define DMAC_CHCTRLB_TRIGACT_BEAT           (DMAC_CHCTRLB_TRIGACT_BEAT_Val << DMAC_CHCTRLB_TRIGACT_Pos)  /**< (DMAC_CHCTRLB) One trigger required for each beat transfer Position  */
#define DMAC_CHCTRLB_TRIGACT_TRANSACTION    (DMAC_CHCTRLB_TRIGACT_TRANSACTION_Val << DMAC_CHCTRLB_TRIGACT_Pos)  /**< (DMAC_CHCTRLB) One trigger required for each transaction Position  */
#define DMAC_CHCTRLB_CMD_Pos                24                                             /**< (DMAC_CHCTRLB) Software Command Position */
#define DMAC_CHCTRLB_CMD_Msk                (_U_(0x3) << DMAC_CHCTRLB_CMD_Pos)             /**< (DMAC_CHCTRLB) Software Command Mask */
#define DMAC_CHCTRLB_CMD(value)             (DMAC_CHCTRLB_CMD_Msk & ((value) << DMAC_CHCTRLB_CMD_Pos))
#define   DMAC_CHCTRLB_CMD_NOACT_Val        _U_(0x0)                                       /**< (DMAC_CHCTRLB) No action  */
#define   DMAC_CHCTRLB_CMD_SUSPEND_Val      _U_(0x1)                                       /**< (DMAC_CHCTRLB) Channel suspend operation  */
#define   DMAC_CHCTRLB_CMD_RESUME_Val       _U_(0x2)                                       /**< (DMAC_CHCTRLB) Channel resume operation  */
#define DMAC_CHCTRLB_CMD_NOACT              (DMAC_CHCTRLB_CMD_NOACT_Val << DMAC_CHCTRLB_CMD_Pos)  /**< (DMAC_CHCTRLB) No action Position  */
#define DMAC_CHCTRLB_CMD_SUSPEND            (DMAC_CHCTRLB_CMD_SUSPEND_Val << DMAC_CHCTRLB_CMD_Pos)  /**< (DMAC_CHCTRLB) Channel suspend operation Position  */
#define DMAC_CHCTRLB_CMD_RESUME             (DMAC_CHCTRLB_CMD_RESUME_Val << DMAC_CHCTRLB_CMD_Pos)  /**< (DMAC_CHCTRLB) Channel resume operation Position  */
#define DMAC_CHCTRLB_MASK                   _U_(0x3C01F7F)                                 /**< \deprecated (DMAC_CHCTRLB) Register MASK  (Use DMAC_CHCTRLB_Msk instead)  */
#define DMAC_CHCTRLB_Msk                    _U_(0x3C01F7F)                                 /**< (DMAC_CHCTRLB) Register Mask  */


/* -------- DMAC_CHINTENCLR : (DMAC Offset: 0x4c) (R/W 8) Channel Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TERR:1;                    /**< bit:      0  Channel Transfer Error Interrupt Enable  */
    uint8_t  TCMPL:1;                   /**< bit:      1  Channel Transfer Complete Interrupt Enable */
    uint8_t  SUSP:1;                    /**< bit:      2  Channel Suspend Interrupt Enable         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHINTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHINTENCLR_OFFSET              (0x4C)                                        /**<  (DMAC_CHINTENCLR) Channel Interrupt Enable Clear  Offset */
#define DMAC_CHINTENCLR_RESETVALUE          _U_(0x00)                                     /**<  (DMAC_CHINTENCLR) Channel Interrupt Enable Clear  Reset Value */

#define DMAC_CHINTENCLR_TERR_Pos            0                                              /**< (DMAC_CHINTENCLR) Channel Transfer Error Interrupt Enable Position */
#define DMAC_CHINTENCLR_TERR_Msk            (_U_(0x1) << DMAC_CHINTENCLR_TERR_Pos)         /**< (DMAC_CHINTENCLR) Channel Transfer Error Interrupt Enable Mask */
#define DMAC_CHINTENCLR_TERR                DMAC_CHINTENCLR_TERR_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENCLR_TERR_Msk instead */
#define DMAC_CHINTENCLR_TCMPL_Pos           1                                              /**< (DMAC_CHINTENCLR) Channel Transfer Complete Interrupt Enable Position */
#define DMAC_CHINTENCLR_TCMPL_Msk           (_U_(0x1) << DMAC_CHINTENCLR_TCMPL_Pos)        /**< (DMAC_CHINTENCLR) Channel Transfer Complete Interrupt Enable Mask */
#define DMAC_CHINTENCLR_TCMPL               DMAC_CHINTENCLR_TCMPL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENCLR_TCMPL_Msk instead */
#define DMAC_CHINTENCLR_SUSP_Pos            2                                              /**< (DMAC_CHINTENCLR) Channel Suspend Interrupt Enable Position */
#define DMAC_CHINTENCLR_SUSP_Msk            (_U_(0x1) << DMAC_CHINTENCLR_SUSP_Pos)         /**< (DMAC_CHINTENCLR) Channel Suspend Interrupt Enable Mask */
#define DMAC_CHINTENCLR_SUSP                DMAC_CHINTENCLR_SUSP_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENCLR_SUSP_Msk instead */
#define DMAC_CHINTENCLR_MASK                _U_(0x07)                                      /**< \deprecated (DMAC_CHINTENCLR) Register MASK  (Use DMAC_CHINTENCLR_Msk instead)  */
#define DMAC_CHINTENCLR_Msk                 _U_(0x07)                                      /**< (DMAC_CHINTENCLR) Register Mask  */


/* -------- DMAC_CHINTENSET : (DMAC Offset: 0x4d) (R/W 8) Channel Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TERR:1;                    /**< bit:      0  Channel Transfer Error Interrupt Enable  */
    uint8_t  TCMPL:1;                   /**< bit:      1  Channel Transfer Complete Interrupt Enable */
    uint8_t  SUSP:1;                    /**< bit:      2  Channel Suspend Interrupt Enable         */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHINTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHINTENSET_OFFSET              (0x4D)                                        /**<  (DMAC_CHINTENSET) Channel Interrupt Enable Set  Offset */
#define DMAC_CHINTENSET_RESETVALUE          _U_(0x00)                                     /**<  (DMAC_CHINTENSET) Channel Interrupt Enable Set  Reset Value */

#define DMAC_CHINTENSET_TERR_Pos            0                                              /**< (DMAC_CHINTENSET) Channel Transfer Error Interrupt Enable Position */
#define DMAC_CHINTENSET_TERR_Msk            (_U_(0x1) << DMAC_CHINTENSET_TERR_Pos)         /**< (DMAC_CHINTENSET) Channel Transfer Error Interrupt Enable Mask */
#define DMAC_CHINTENSET_TERR                DMAC_CHINTENSET_TERR_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENSET_TERR_Msk instead */
#define DMAC_CHINTENSET_TCMPL_Pos           1                                              /**< (DMAC_CHINTENSET) Channel Transfer Complete Interrupt Enable Position */
#define DMAC_CHINTENSET_TCMPL_Msk           (_U_(0x1) << DMAC_CHINTENSET_TCMPL_Pos)        /**< (DMAC_CHINTENSET) Channel Transfer Complete Interrupt Enable Mask */
#define DMAC_CHINTENSET_TCMPL               DMAC_CHINTENSET_TCMPL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENSET_TCMPL_Msk instead */
#define DMAC_CHINTENSET_SUSP_Pos            2                                              /**< (DMAC_CHINTENSET) Channel Suspend Interrupt Enable Position */
#define DMAC_CHINTENSET_SUSP_Msk            (_U_(0x1) << DMAC_CHINTENSET_SUSP_Pos)         /**< (DMAC_CHINTENSET) Channel Suspend Interrupt Enable Mask */
#define DMAC_CHINTENSET_SUSP                DMAC_CHINTENSET_SUSP_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTENSET_SUSP_Msk instead */
#define DMAC_CHINTENSET_MASK                _U_(0x07)                                      /**< \deprecated (DMAC_CHINTENSET) Register MASK  (Use DMAC_CHINTENSET_Msk instead)  */
#define DMAC_CHINTENSET_Msk                 _U_(0x07)                                      /**< (DMAC_CHINTENSET) Register Mask  */


/* -------- DMAC_CHINTFLAG : (DMAC Offset: 0x4e) (R/W 8) Channel Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t TERR:1;                    /**< bit:      0  Channel Transfer Error                   */
    __I uint8_t TCMPL:1;                   /**< bit:      1  Channel Transfer Complete                */
    __I uint8_t SUSP:1;                    /**< bit:      2  Channel Suspend                          */
    __I uint8_t :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHINTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHINTFLAG_OFFSET               (0x4E)                                        /**<  (DMAC_CHINTFLAG) Channel Interrupt Flag Status and Clear  Offset */
#define DMAC_CHINTFLAG_RESETVALUE           _U_(0x00)                                     /**<  (DMAC_CHINTFLAG) Channel Interrupt Flag Status and Clear  Reset Value */

#define DMAC_CHINTFLAG_TERR_Pos             0                                              /**< (DMAC_CHINTFLAG) Channel Transfer Error Position */
#define DMAC_CHINTFLAG_TERR_Msk             (_U_(0x1) << DMAC_CHINTFLAG_TERR_Pos)          /**< (DMAC_CHINTFLAG) Channel Transfer Error Mask */
#define DMAC_CHINTFLAG_TERR                 DMAC_CHINTFLAG_TERR_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTFLAG_TERR_Msk instead */
#define DMAC_CHINTFLAG_TCMPL_Pos            1                                              /**< (DMAC_CHINTFLAG) Channel Transfer Complete Position */
#define DMAC_CHINTFLAG_TCMPL_Msk            (_U_(0x1) << DMAC_CHINTFLAG_TCMPL_Pos)         /**< (DMAC_CHINTFLAG) Channel Transfer Complete Mask */
#define DMAC_CHINTFLAG_TCMPL                DMAC_CHINTFLAG_TCMPL_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTFLAG_TCMPL_Msk instead */
#define DMAC_CHINTFLAG_SUSP_Pos             2                                              /**< (DMAC_CHINTFLAG) Channel Suspend Position */
#define DMAC_CHINTFLAG_SUSP_Msk             (_U_(0x1) << DMAC_CHINTFLAG_SUSP_Pos)          /**< (DMAC_CHINTFLAG) Channel Suspend Mask */
#define DMAC_CHINTFLAG_SUSP                 DMAC_CHINTFLAG_SUSP_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHINTFLAG_SUSP_Msk instead */
#define DMAC_CHINTFLAG_MASK                 _U_(0x07)                                      /**< \deprecated (DMAC_CHINTFLAG) Register MASK  (Use DMAC_CHINTFLAG_Msk instead)  */
#define DMAC_CHINTFLAG_Msk                  _U_(0x07)                                      /**< (DMAC_CHINTFLAG) Register Mask  */


/* -------- DMAC_CHSTATUS : (DMAC Offset: 0x4f) (R/ 8) Channel Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PEND:1;                    /**< bit:      0  Channel Pending                          */
    uint8_t  BUSY:1;                    /**< bit:      1  Channel Busy                             */
    uint8_t  FERR:1;                    /**< bit:      2  Channel Fetch Error                      */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DMAC_CHSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DMAC_CHSTATUS_OFFSET                (0x4F)                                        /**<  (DMAC_CHSTATUS) Channel Status  Offset */
#define DMAC_CHSTATUS_RESETVALUE            _U_(0x00)                                     /**<  (DMAC_CHSTATUS) Channel Status  Reset Value */

#define DMAC_CHSTATUS_PEND_Pos              0                                              /**< (DMAC_CHSTATUS) Channel Pending Position */
#define DMAC_CHSTATUS_PEND_Msk              (_U_(0x1) << DMAC_CHSTATUS_PEND_Pos)           /**< (DMAC_CHSTATUS) Channel Pending Mask */
#define DMAC_CHSTATUS_PEND                  DMAC_CHSTATUS_PEND_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHSTATUS_PEND_Msk instead */
#define DMAC_CHSTATUS_BUSY_Pos              1                                              /**< (DMAC_CHSTATUS) Channel Busy Position */
#define DMAC_CHSTATUS_BUSY_Msk              (_U_(0x1) << DMAC_CHSTATUS_BUSY_Pos)           /**< (DMAC_CHSTATUS) Channel Busy Mask */
#define DMAC_CHSTATUS_BUSY                  DMAC_CHSTATUS_BUSY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHSTATUS_BUSY_Msk instead */
#define DMAC_CHSTATUS_FERR_Pos              2                                              /**< (DMAC_CHSTATUS) Channel Fetch Error Position */
#define DMAC_CHSTATUS_FERR_Msk              (_U_(0x1) << DMAC_CHSTATUS_FERR_Pos)           /**< (DMAC_CHSTATUS) Channel Fetch Error Mask */
#define DMAC_CHSTATUS_FERR                  DMAC_CHSTATUS_FERR_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DMAC_CHSTATUS_FERR_Msk instead */
#define DMAC_CHSTATUS_MASK                  _U_(0x07)                                      /**< \deprecated (DMAC_CHSTATUS) Register MASK  (Use DMAC_CHSTATUS_Msk instead)  */
#define DMAC_CHSTATUS_Msk                   _U_(0x07)                                      /**< (DMAC_CHSTATUS) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief DMAC_DESCRIPTOR hardware registers */
typedef struct {  /* Direct Memory Access Controller */
  __IO DMAC_BTCTRL_Type               BTCTRL;         /**< Offset: 0x00 (R/W  16) Block Transfer Control */
  __IO DMAC_BTCNT_Type                BTCNT;          /**< Offset: 0x02 (R/W  16) Block Transfer Count */
  __IO DMAC_SRCADDR_Type              SRCADDR;        /**< Offset: 0x04 (R/W  32) Block Transfer Source Address */
  __IO DMAC_DSTADDR_Type              DSTADDR;        /**< Offset: 0x08 (R/W  32) Block Transfer Destination Address */
  __IO DMAC_DESCADDR_Type             DESCADDR;       /**< Offset: 0x0C (R/W  32) Next Descriptor Address */
} DmacDescriptor
#ifdef __GNUC__
  __attribute__ ((aligned (8)))
#endif
;

/** \brief DMAC hardware registers */
typedef struct {  /* Direct Memory Access Controller */
  __IO DMAC_CTRL_Type                 CTRL;           /**< Offset: 0x00 (R/W  16) Control */
  __IO DMAC_CRCCTRL_Type              CRCCTRL;        /**< Offset: 0x02 (R/W  16) CRC Control */
  __IO DMAC_CRCDATAIN_Type            CRCDATAIN;      /**< Offset: 0x04 (R/W  32) CRC Data Input */
  __IO DMAC_CRCCHKSUM_Type            CRCCHKSUM;      /**< Offset: 0x08 (R/W  32) CRC Checksum */
  __IO DMAC_CRCSTATUS_Type            CRCSTATUS;      /**< Offset: 0x0C (R/W   8) CRC Status */
  __IO DMAC_DBGCTRL_Type              DBGCTRL;        /**< Offset: 0x0D (R/W   8) Debug Control */
  __IO DMAC_QOSCTRL_Type              QOSCTRL;        /**< Offset: 0x0E (R/W   8) QOS Control */
  __I  uint8_t                        Reserved1[1];
  __IO DMAC_SWTRIGCTRL_Type           SWTRIGCTRL;     /**< Offset: 0x10 (R/W  32) Software Trigger Control */
  __IO DMAC_PRICTRL0_Type             PRICTRL0;       /**< Offset: 0x14 (R/W  32) Priority Control 0 */
  __I  uint8_t                        Reserved2[8];
  __IO DMAC_INTPEND_Type              INTPEND;        /**< Offset: 0x20 (R/W  16) Interrupt Pending */
  __I  uint8_t                        Reserved3[2];
  __I  DMAC_INTSTATUS_Type            INTSTATUS;      /**< Offset: 0x24 (R/   32) Interrupt Status */
  __I  DMAC_BUSYCH_Type               BUSYCH;         /**< Offset: 0x28 (R/   32) Busy Channels */
  __I  DMAC_PENDCH_Type               PENDCH;         /**< Offset: 0x2C (R/   32) Pending Channels */
  __I  DMAC_ACTIVE_Type               ACTIVE;         /**< Offset: 0x30 (R/   32) Active Channel and Levels */
  __IO DMAC_BASEADDR_Type             BASEADDR;       /**< Offset: 0x34 (R/W  32) Descriptor Memory Section Base Address */
  __IO DMAC_WRBADDR_Type              WRBADDR;        /**< Offset: 0x38 (R/W  32) Write-Back Memory Section Base Address */
  __I  uint8_t                        Reserved4[3];
  __IO DMAC_CHID_Type                 CHID;           /**< Offset: 0x3F (R/W   8) Channel ID */
  __IO DMAC_CHCTRLA_Type              CHCTRLA;        /**< Offset: 0x40 (R/W   8) Channel Control A */
  __I  uint8_t                        Reserved5[3];
  __IO DMAC_CHCTRLB_Type              CHCTRLB;        /**< Offset: 0x44 (R/W  32) Channel Control B */
  __I  uint8_t                        Reserved6[4];
  __IO DMAC_CHINTENCLR_Type           CHINTENCLR;     /**< Offset: 0x4C (R/W   8) Channel Interrupt Enable Clear */
  __IO DMAC_CHINTENSET_Type           CHINTENSET;     /**< Offset: 0x4D (R/W   8) Channel Interrupt Enable Set */
  __IO DMAC_CHINTFLAG_Type            CHINTFLAG;      /**< Offset: 0x4E (R/W   8) Channel Interrupt Flag Status and Clear */
  __I  DMAC_CHSTATUS_Type             CHSTATUS;       /**< Offset: 0x4F (R/    8) Channel Status */
} Dmac;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** \brief DMAC_DESCRIPTOR memory section attribute */
#define SECTION_DMAC_DESCRIPTOR

/** @}  end of Direct Memory Access Controller */

#endif /* _SAML10_DMAC_COMPONENT_H_ */
