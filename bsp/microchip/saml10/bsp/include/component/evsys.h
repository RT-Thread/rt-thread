/**
 * \file
 *
 * \brief Component description for EVSYS
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
#ifndef _SAML10_EVSYS_COMPONENT_H_
#define _SAML10_EVSYS_COMPONENT_H_
#define _SAML10_EVSYS_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Event System Interface
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR EVSYS */
/* ========================================================================== */

#define EVSYS_U2504                      /**< (EVSYS) Module ID */
#define REV_EVSYS 0x200                  /**< (EVSYS) Module revision */

/* -------- EVSYS_CHANNEL : (EVSYS Offset: 0x00) (R/W 32) Channel n Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EVGEN:6;                   /**< bit:   0..5  Event Generator Selection                */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t PATH:2;                    /**< bit:   8..9  Path Selection                           */
    uint32_t EDGSEL:2;                  /**< bit: 10..11  Edge Detection Selection                 */
    uint32_t :2;                        /**< bit: 12..13  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:     14  Run in standby                           */
    uint32_t ONDEMAND:1;                /**< bit:     15  Generic Clock On Demand                  */
    uint32_t :16;                       /**< bit: 16..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_CHANNEL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CHANNEL_OFFSET                (0x00)                                        /**<  (EVSYS_CHANNEL) Channel n Control  Offset */
#define EVSYS_CHANNEL_RESETVALUE            _U_(0x8000)                                   /**<  (EVSYS_CHANNEL) Channel n Control  Reset Value */

#define EVSYS_CHANNEL_EVGEN_Pos             0                                              /**< (EVSYS_CHANNEL) Event Generator Selection Position */
#define EVSYS_CHANNEL_EVGEN_Msk             (_U_(0x3F) << EVSYS_CHANNEL_EVGEN_Pos)         /**< (EVSYS_CHANNEL) Event Generator Selection Mask */
#define EVSYS_CHANNEL_EVGEN(value)          (EVSYS_CHANNEL_EVGEN_Msk & ((value) << EVSYS_CHANNEL_EVGEN_Pos))
#define EVSYS_CHANNEL_PATH_Pos              8                                              /**< (EVSYS_CHANNEL) Path Selection Position */
#define EVSYS_CHANNEL_PATH_Msk              (_U_(0x3) << EVSYS_CHANNEL_PATH_Pos)           /**< (EVSYS_CHANNEL) Path Selection Mask */
#define EVSYS_CHANNEL_PATH(value)           (EVSYS_CHANNEL_PATH_Msk & ((value) << EVSYS_CHANNEL_PATH_Pos))
#define   EVSYS_CHANNEL_PATH_SYNCHRONOUS_Val _U_(0x0)                                       /**< (EVSYS_CHANNEL) Synchronous path  */
#define   EVSYS_CHANNEL_PATH_RESYNCHRONIZED_Val _U_(0x1)                                       /**< (EVSYS_CHANNEL) Resynchronized path  */
#define   EVSYS_CHANNEL_PATH_ASYNCHRONOUS_Val _U_(0x2)                                       /**< (EVSYS_CHANNEL) Asynchronous path  */
#define EVSYS_CHANNEL_PATH_SYNCHRONOUS      (EVSYS_CHANNEL_PATH_SYNCHRONOUS_Val << EVSYS_CHANNEL_PATH_Pos)  /**< (EVSYS_CHANNEL) Synchronous path Position  */
#define EVSYS_CHANNEL_PATH_RESYNCHRONIZED   (EVSYS_CHANNEL_PATH_RESYNCHRONIZED_Val << EVSYS_CHANNEL_PATH_Pos)  /**< (EVSYS_CHANNEL) Resynchronized path Position  */
#define EVSYS_CHANNEL_PATH_ASYNCHRONOUS     (EVSYS_CHANNEL_PATH_ASYNCHRONOUS_Val << EVSYS_CHANNEL_PATH_Pos)  /**< (EVSYS_CHANNEL) Asynchronous path Position  */
#define EVSYS_CHANNEL_EDGSEL_Pos            10                                             /**< (EVSYS_CHANNEL) Edge Detection Selection Position */
#define EVSYS_CHANNEL_EDGSEL_Msk            (_U_(0x3) << EVSYS_CHANNEL_EDGSEL_Pos)         /**< (EVSYS_CHANNEL) Edge Detection Selection Mask */
#define EVSYS_CHANNEL_EDGSEL(value)         (EVSYS_CHANNEL_EDGSEL_Msk & ((value) << EVSYS_CHANNEL_EDGSEL_Pos))
#define   EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT_Val _U_(0x0)                                       /**< (EVSYS_CHANNEL) No event output when using the resynchronized or synchronous path  */
#define   EVSYS_CHANNEL_EDGSEL_RISING_EDGE_Val _U_(0x1)                                       /**< (EVSYS_CHANNEL) Event detection only on the rising edge of the signal from the event generator when using the resynchronized or synchronous path  */
#define   EVSYS_CHANNEL_EDGSEL_FALLING_EDGE_Val _U_(0x2)                                       /**< (EVSYS_CHANNEL) Event detection only on the falling edge of the signal from the event generator when using the resynchronized or synchronous path  */
#define   EVSYS_CHANNEL_EDGSEL_BOTH_EDGES_Val _U_(0x3)                                       /**< (EVSYS_CHANNEL) Event detection on rising and falling edges of the signal from the event generator when using the resynchronized or synchronous path  */
#define EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT  (EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT_Val << EVSYS_CHANNEL_EDGSEL_Pos)  /**< (EVSYS_CHANNEL) No event output when using the resynchronized or synchronous path Position  */
#define EVSYS_CHANNEL_EDGSEL_RISING_EDGE    (EVSYS_CHANNEL_EDGSEL_RISING_EDGE_Val << EVSYS_CHANNEL_EDGSEL_Pos)  /**< (EVSYS_CHANNEL) Event detection only on the rising edge of the signal from the event generator when using the resynchronized or synchronous path Position  */
#define EVSYS_CHANNEL_EDGSEL_FALLING_EDGE   (EVSYS_CHANNEL_EDGSEL_FALLING_EDGE_Val << EVSYS_CHANNEL_EDGSEL_Pos)  /**< (EVSYS_CHANNEL) Event detection only on the falling edge of the signal from the event generator when using the resynchronized or synchronous path Position  */
#define EVSYS_CHANNEL_EDGSEL_BOTH_EDGES     (EVSYS_CHANNEL_EDGSEL_BOTH_EDGES_Val << EVSYS_CHANNEL_EDGSEL_Pos)  /**< (EVSYS_CHANNEL) Event detection on rising and falling edges of the signal from the event generator when using the resynchronized or synchronous path Position  */
#define EVSYS_CHANNEL_RUNSTDBY_Pos          14                                             /**< (EVSYS_CHANNEL) Run in standby Position */
#define EVSYS_CHANNEL_RUNSTDBY_Msk          (_U_(0x1) << EVSYS_CHANNEL_RUNSTDBY_Pos)       /**< (EVSYS_CHANNEL) Run in standby Mask */
#define EVSYS_CHANNEL_RUNSTDBY              EVSYS_CHANNEL_RUNSTDBY_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHANNEL_RUNSTDBY_Msk instead */
#define EVSYS_CHANNEL_ONDEMAND_Pos          15                                             /**< (EVSYS_CHANNEL) Generic Clock On Demand Position */
#define EVSYS_CHANNEL_ONDEMAND_Msk          (_U_(0x1) << EVSYS_CHANNEL_ONDEMAND_Pos)       /**< (EVSYS_CHANNEL) Generic Clock On Demand Mask */
#define EVSYS_CHANNEL_ONDEMAND              EVSYS_CHANNEL_ONDEMAND_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHANNEL_ONDEMAND_Msk instead */
#define EVSYS_CHANNEL_MASK                  _U_(0xCF3F)                                    /**< \deprecated (EVSYS_CHANNEL) Register MASK  (Use EVSYS_CHANNEL_Msk instead)  */
#define EVSYS_CHANNEL_Msk                   _U_(0xCF3F)                                    /**< (EVSYS_CHANNEL) Register Mask  */


/* -------- EVSYS_CHINTENCLR : (EVSYS Offset: 0x04) (R/W 8) Channel n Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  OVR:1;                     /**< bit:      0  Channel Overrun Interrupt Disable        */
    uint8_t  EVD:1;                     /**< bit:      1  Channel Event Detected Interrupt Disable */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_CHINTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CHINTENCLR_OFFSET             (0x04)                                        /**<  (EVSYS_CHINTENCLR) Channel n Interrupt Enable Clear  Offset */
#define EVSYS_CHINTENCLR_RESETVALUE         _U_(0x00)                                     /**<  (EVSYS_CHINTENCLR) Channel n Interrupt Enable Clear  Reset Value */

#define EVSYS_CHINTENCLR_OVR_Pos            0                                              /**< (EVSYS_CHINTENCLR) Channel Overrun Interrupt Disable Position */
#define EVSYS_CHINTENCLR_OVR_Msk            (_U_(0x1) << EVSYS_CHINTENCLR_OVR_Pos)         /**< (EVSYS_CHINTENCLR) Channel Overrun Interrupt Disable Mask */
#define EVSYS_CHINTENCLR_OVR                EVSYS_CHINTENCLR_OVR_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTENCLR_OVR_Msk instead */
#define EVSYS_CHINTENCLR_EVD_Pos            1                                              /**< (EVSYS_CHINTENCLR) Channel Event Detected Interrupt Disable Position */
#define EVSYS_CHINTENCLR_EVD_Msk            (_U_(0x1) << EVSYS_CHINTENCLR_EVD_Pos)         /**< (EVSYS_CHINTENCLR) Channel Event Detected Interrupt Disable Mask */
#define EVSYS_CHINTENCLR_EVD                EVSYS_CHINTENCLR_EVD_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTENCLR_EVD_Msk instead */
#define EVSYS_CHINTENCLR_MASK               _U_(0x03)                                      /**< \deprecated (EVSYS_CHINTENCLR) Register MASK  (Use EVSYS_CHINTENCLR_Msk instead)  */
#define EVSYS_CHINTENCLR_Msk                _U_(0x03)                                      /**< (EVSYS_CHINTENCLR) Register Mask  */


/* -------- EVSYS_CHINTENSET : (EVSYS Offset: 0x05) (R/W 8) Channel n Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  OVR:1;                     /**< bit:      0  Channel Overrun Interrupt Enable         */
    uint8_t  EVD:1;                     /**< bit:      1  Channel Event Detected Interrupt Enable  */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_CHINTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CHINTENSET_OFFSET             (0x05)                                        /**<  (EVSYS_CHINTENSET) Channel n Interrupt Enable Set  Offset */
#define EVSYS_CHINTENSET_RESETVALUE         _U_(0x00)                                     /**<  (EVSYS_CHINTENSET) Channel n Interrupt Enable Set  Reset Value */

#define EVSYS_CHINTENSET_OVR_Pos            0                                              /**< (EVSYS_CHINTENSET) Channel Overrun Interrupt Enable Position */
#define EVSYS_CHINTENSET_OVR_Msk            (_U_(0x1) << EVSYS_CHINTENSET_OVR_Pos)         /**< (EVSYS_CHINTENSET) Channel Overrun Interrupt Enable Mask */
#define EVSYS_CHINTENSET_OVR                EVSYS_CHINTENSET_OVR_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTENSET_OVR_Msk instead */
#define EVSYS_CHINTENSET_EVD_Pos            1                                              /**< (EVSYS_CHINTENSET) Channel Event Detected Interrupt Enable Position */
#define EVSYS_CHINTENSET_EVD_Msk            (_U_(0x1) << EVSYS_CHINTENSET_EVD_Pos)         /**< (EVSYS_CHINTENSET) Channel Event Detected Interrupt Enable Mask */
#define EVSYS_CHINTENSET_EVD                EVSYS_CHINTENSET_EVD_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTENSET_EVD_Msk instead */
#define EVSYS_CHINTENSET_MASK               _U_(0x03)                                      /**< \deprecated (EVSYS_CHINTENSET) Register MASK  (Use EVSYS_CHINTENSET_Msk instead)  */
#define EVSYS_CHINTENSET_Msk                _U_(0x03)                                      /**< (EVSYS_CHINTENSET) Register Mask  */


/* -------- EVSYS_CHINTFLAG : (EVSYS Offset: 0x06) (R/W 8) Channel n Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t OVR:1;                     /**< bit:      0  Channel Overrun                          */
    __I uint8_t EVD:1;                     /**< bit:      1  Channel Event Detected                   */
    __I uint8_t :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_CHINTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CHINTFLAG_OFFSET              (0x06)                                        /**<  (EVSYS_CHINTFLAG) Channel n Interrupt Flag Status and Clear  Offset */
#define EVSYS_CHINTFLAG_RESETVALUE          _U_(0x00)                                     /**<  (EVSYS_CHINTFLAG) Channel n Interrupt Flag Status and Clear  Reset Value */

#define EVSYS_CHINTFLAG_OVR_Pos             0                                              /**< (EVSYS_CHINTFLAG) Channel Overrun Position */
#define EVSYS_CHINTFLAG_OVR_Msk             (_U_(0x1) << EVSYS_CHINTFLAG_OVR_Pos)          /**< (EVSYS_CHINTFLAG) Channel Overrun Mask */
#define EVSYS_CHINTFLAG_OVR                 EVSYS_CHINTFLAG_OVR_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTFLAG_OVR_Msk instead */
#define EVSYS_CHINTFLAG_EVD_Pos             1                                              /**< (EVSYS_CHINTFLAG) Channel Event Detected Position */
#define EVSYS_CHINTFLAG_EVD_Msk             (_U_(0x1) << EVSYS_CHINTFLAG_EVD_Pos)          /**< (EVSYS_CHINTFLAG) Channel Event Detected Mask */
#define EVSYS_CHINTFLAG_EVD                 EVSYS_CHINTFLAG_EVD_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHINTFLAG_EVD_Msk instead */
#define EVSYS_CHINTFLAG_MASK                _U_(0x03)                                      /**< \deprecated (EVSYS_CHINTFLAG) Register MASK  (Use EVSYS_CHINTFLAG_Msk instead)  */
#define EVSYS_CHINTFLAG_Msk                 _U_(0x03)                                      /**< (EVSYS_CHINTFLAG) Register Mask  */


/* -------- EVSYS_CHSTATUS : (EVSYS Offset: 0x07) (R/ 8) Channel n Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RDYUSR:1;                  /**< bit:      0  Ready User                               */
    uint8_t  BUSYCH:1;                  /**< bit:      1  Busy Channel                             */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_CHSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CHSTATUS_OFFSET               (0x07)                                        /**<  (EVSYS_CHSTATUS) Channel n Status  Offset */
#define EVSYS_CHSTATUS_RESETVALUE           _U_(0x01)                                     /**<  (EVSYS_CHSTATUS) Channel n Status  Reset Value */

#define EVSYS_CHSTATUS_RDYUSR_Pos           0                                              /**< (EVSYS_CHSTATUS) Ready User Position */
#define EVSYS_CHSTATUS_RDYUSR_Msk           (_U_(0x1) << EVSYS_CHSTATUS_RDYUSR_Pos)        /**< (EVSYS_CHSTATUS) Ready User Mask */
#define EVSYS_CHSTATUS_RDYUSR               EVSYS_CHSTATUS_RDYUSR_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHSTATUS_RDYUSR_Msk instead */
#define EVSYS_CHSTATUS_BUSYCH_Pos           1                                              /**< (EVSYS_CHSTATUS) Busy Channel Position */
#define EVSYS_CHSTATUS_BUSYCH_Msk           (_U_(0x1) << EVSYS_CHSTATUS_BUSYCH_Pos)        /**< (EVSYS_CHSTATUS) Busy Channel Mask */
#define EVSYS_CHSTATUS_BUSYCH               EVSYS_CHSTATUS_BUSYCH_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CHSTATUS_BUSYCH_Msk instead */
#define EVSYS_CHSTATUS_MASK                 _U_(0x03)                                      /**< \deprecated (EVSYS_CHSTATUS) Register MASK  (Use EVSYS_CHSTATUS_Msk instead)  */
#define EVSYS_CHSTATUS_Msk                  _U_(0x03)                                      /**< (EVSYS_CHSTATUS) Register Mask  */


/* -------- EVSYS_CTRLA : (EVSYS Offset: 0x00) (/W 8) Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_CTRLA_OFFSET                  (0x00)                                        /**<  (EVSYS_CTRLA) Control  Offset */
#define EVSYS_CTRLA_RESETVALUE              _U_(0x00)                                     /**<  (EVSYS_CTRLA) Control  Reset Value */

#define EVSYS_CTRLA_SWRST_Pos               0                                              /**< (EVSYS_CTRLA) Software Reset Position */
#define EVSYS_CTRLA_SWRST_Msk               (_U_(0x1) << EVSYS_CTRLA_SWRST_Pos)            /**< (EVSYS_CTRLA) Software Reset Mask */
#define EVSYS_CTRLA_SWRST                   EVSYS_CTRLA_SWRST_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_CTRLA_SWRST_Msk instead */
#define EVSYS_CTRLA_MASK                    _U_(0x01)                                      /**< \deprecated (EVSYS_CTRLA) Register MASK  (Use EVSYS_CTRLA_Msk instead)  */
#define EVSYS_CTRLA_Msk                     _U_(0x01)                                      /**< (EVSYS_CTRLA) Register Mask  */


/* -------- EVSYS_SWEVT : (EVSYS Offset: 0x04) (/W 32) Software Event -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHANNEL0:1;                /**< bit:      0  Channel 0 Software Selection             */
    uint32_t CHANNEL1:1;                /**< bit:      1  Channel 1 Software Selection             */
    uint32_t CHANNEL2:1;                /**< bit:      2  Channel 2 Software Selection             */
    uint32_t CHANNEL3:1;                /**< bit:      3  Channel 3 Software Selection             */
    uint32_t CHANNEL4:1;                /**< bit:      4  Channel 4 Software Selection             */
    uint32_t CHANNEL5:1;                /**< bit:      5  Channel 5 Software Selection             */
    uint32_t CHANNEL6:1;                /**< bit:      6  Channel 6 Software Selection             */
    uint32_t CHANNEL7:1;                /**< bit:      7  Channel 7 Software Selection             */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t CHANNEL:8;                 /**< bit:   0..7  Channel 7 Software Selection             */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_SWEVT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_SWEVT_OFFSET                  (0x04)                                        /**<  (EVSYS_SWEVT) Software Event  Offset */
#define EVSYS_SWEVT_RESETVALUE              _U_(0x00)                                     /**<  (EVSYS_SWEVT) Software Event  Reset Value */

#define EVSYS_SWEVT_CHANNEL0_Pos            0                                              /**< (EVSYS_SWEVT) Channel 0 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL0_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL0_Pos)         /**< (EVSYS_SWEVT) Channel 0 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL0                EVSYS_SWEVT_CHANNEL0_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL0_Msk instead */
#define EVSYS_SWEVT_CHANNEL1_Pos            1                                              /**< (EVSYS_SWEVT) Channel 1 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL1_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL1_Pos)         /**< (EVSYS_SWEVT) Channel 1 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL1                EVSYS_SWEVT_CHANNEL1_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL1_Msk instead */
#define EVSYS_SWEVT_CHANNEL2_Pos            2                                              /**< (EVSYS_SWEVT) Channel 2 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL2_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL2_Pos)         /**< (EVSYS_SWEVT) Channel 2 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL2                EVSYS_SWEVT_CHANNEL2_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL2_Msk instead */
#define EVSYS_SWEVT_CHANNEL3_Pos            3                                              /**< (EVSYS_SWEVT) Channel 3 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL3_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL3_Pos)         /**< (EVSYS_SWEVT) Channel 3 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL3                EVSYS_SWEVT_CHANNEL3_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL3_Msk instead */
#define EVSYS_SWEVT_CHANNEL4_Pos            4                                              /**< (EVSYS_SWEVT) Channel 4 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL4_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL4_Pos)         /**< (EVSYS_SWEVT) Channel 4 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL4                EVSYS_SWEVT_CHANNEL4_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL4_Msk instead */
#define EVSYS_SWEVT_CHANNEL5_Pos            5                                              /**< (EVSYS_SWEVT) Channel 5 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL5_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL5_Pos)         /**< (EVSYS_SWEVT) Channel 5 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL5                EVSYS_SWEVT_CHANNEL5_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL5_Msk instead */
#define EVSYS_SWEVT_CHANNEL6_Pos            6                                              /**< (EVSYS_SWEVT) Channel 6 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL6_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL6_Pos)         /**< (EVSYS_SWEVT) Channel 6 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL6                EVSYS_SWEVT_CHANNEL6_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL6_Msk instead */
#define EVSYS_SWEVT_CHANNEL7_Pos            7                                              /**< (EVSYS_SWEVT) Channel 7 Software Selection Position */
#define EVSYS_SWEVT_CHANNEL7_Msk            (_U_(0x1) << EVSYS_SWEVT_CHANNEL7_Pos)         /**< (EVSYS_SWEVT) Channel 7 Software Selection Mask */
#define EVSYS_SWEVT_CHANNEL7                EVSYS_SWEVT_CHANNEL7_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_SWEVT_CHANNEL7_Msk instead */
#define EVSYS_SWEVT_MASK                    _U_(0xFF)                                      /**< \deprecated (EVSYS_SWEVT) Register MASK  (Use EVSYS_SWEVT_Msk instead)  */
#define EVSYS_SWEVT_Msk                     _U_(0xFF)                                      /**< (EVSYS_SWEVT) Register Mask  */

#define EVSYS_SWEVT_CHANNEL_Pos             0                                              /**< (EVSYS_SWEVT Position) Channel 7 Software Selection */
#define EVSYS_SWEVT_CHANNEL_Msk             (_U_(0xFF) << EVSYS_SWEVT_CHANNEL_Pos)         /**< (EVSYS_SWEVT Mask) CHANNEL */
#define EVSYS_SWEVT_CHANNEL(value)          (EVSYS_SWEVT_CHANNEL_Msk & ((value) << EVSYS_SWEVT_CHANNEL_Pos))  

/* -------- EVSYS_PRICTRL : (EVSYS Offset: 0x08) (R/W 8) Priority Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PRI:2;                     /**< bit:   0..1  Channel Priority Number                  */
    uint8_t  :5;                        /**< bit:   2..6  Reserved */
    uint8_t  RREN:1;                    /**< bit:      7  Round-Robin Scheduling Enable            */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_PRICTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_PRICTRL_OFFSET                (0x08)                                        /**<  (EVSYS_PRICTRL) Priority Control  Offset */
#define EVSYS_PRICTRL_RESETVALUE            _U_(0x00)                                     /**<  (EVSYS_PRICTRL) Priority Control  Reset Value */

#define EVSYS_PRICTRL_PRI_Pos               0                                              /**< (EVSYS_PRICTRL) Channel Priority Number Position */
#define EVSYS_PRICTRL_PRI_Msk               (_U_(0x3) << EVSYS_PRICTRL_PRI_Pos)            /**< (EVSYS_PRICTRL) Channel Priority Number Mask */
#define EVSYS_PRICTRL_PRI(value)            (EVSYS_PRICTRL_PRI_Msk & ((value) << EVSYS_PRICTRL_PRI_Pos))
#define EVSYS_PRICTRL_RREN_Pos              7                                              /**< (EVSYS_PRICTRL) Round-Robin Scheduling Enable Position */
#define EVSYS_PRICTRL_RREN_Msk              (_U_(0x1) << EVSYS_PRICTRL_RREN_Pos)           /**< (EVSYS_PRICTRL) Round-Robin Scheduling Enable Mask */
#define EVSYS_PRICTRL_RREN                  EVSYS_PRICTRL_RREN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_PRICTRL_RREN_Msk instead */
#define EVSYS_PRICTRL_MASK                  _U_(0x83)                                      /**< \deprecated (EVSYS_PRICTRL) Register MASK  (Use EVSYS_PRICTRL_Msk instead)  */
#define EVSYS_PRICTRL_Msk                   _U_(0x83)                                      /**< (EVSYS_PRICTRL) Register Mask  */


/* -------- EVSYS_INTPEND : (EVSYS Offset: 0x10) (R/W 16) Channel Pending Interrupt -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t ID:2;                      /**< bit:   0..1  Channel ID                               */
    uint16_t :6;                        /**< bit:   2..7  Reserved */
    uint16_t OVR:1;                     /**< bit:      8  Channel Overrun                          */
    uint16_t EVD:1;                     /**< bit:      9  Channel Event Detected                   */
    uint16_t :4;                        /**< bit: 10..13  Reserved */
    uint16_t READY:1;                   /**< bit:     14  Ready                                    */
    uint16_t BUSY:1;                    /**< bit:     15  Busy                                     */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} EVSYS_INTPEND_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_INTPEND_OFFSET                (0x10)                                        /**<  (EVSYS_INTPEND) Channel Pending Interrupt  Offset */
#define EVSYS_INTPEND_RESETVALUE            _U_(0x4000)                                   /**<  (EVSYS_INTPEND) Channel Pending Interrupt  Reset Value */

#define EVSYS_INTPEND_ID_Pos                0                                              /**< (EVSYS_INTPEND) Channel ID Position */
#define EVSYS_INTPEND_ID_Msk                (_U_(0x3) << EVSYS_INTPEND_ID_Pos)             /**< (EVSYS_INTPEND) Channel ID Mask */
#define EVSYS_INTPEND_ID(value)             (EVSYS_INTPEND_ID_Msk & ((value) << EVSYS_INTPEND_ID_Pos))
#define EVSYS_INTPEND_OVR_Pos               8                                              /**< (EVSYS_INTPEND) Channel Overrun Position */
#define EVSYS_INTPEND_OVR_Msk               (_U_(0x1) << EVSYS_INTPEND_OVR_Pos)            /**< (EVSYS_INTPEND) Channel Overrun Mask */
#define EVSYS_INTPEND_OVR                   EVSYS_INTPEND_OVR_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTPEND_OVR_Msk instead */
#define EVSYS_INTPEND_EVD_Pos               9                                              /**< (EVSYS_INTPEND) Channel Event Detected Position */
#define EVSYS_INTPEND_EVD_Msk               (_U_(0x1) << EVSYS_INTPEND_EVD_Pos)            /**< (EVSYS_INTPEND) Channel Event Detected Mask */
#define EVSYS_INTPEND_EVD                   EVSYS_INTPEND_EVD_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTPEND_EVD_Msk instead */
#define EVSYS_INTPEND_READY_Pos             14                                             /**< (EVSYS_INTPEND) Ready Position */
#define EVSYS_INTPEND_READY_Msk             (_U_(0x1) << EVSYS_INTPEND_READY_Pos)          /**< (EVSYS_INTPEND) Ready Mask */
#define EVSYS_INTPEND_READY                 EVSYS_INTPEND_READY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTPEND_READY_Msk instead */
#define EVSYS_INTPEND_BUSY_Pos              15                                             /**< (EVSYS_INTPEND) Busy Position */
#define EVSYS_INTPEND_BUSY_Msk              (_U_(0x1) << EVSYS_INTPEND_BUSY_Pos)           /**< (EVSYS_INTPEND) Busy Mask */
#define EVSYS_INTPEND_BUSY                  EVSYS_INTPEND_BUSY_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTPEND_BUSY_Msk instead */
#define EVSYS_INTPEND_MASK                  _U_(0xC303)                                    /**< \deprecated (EVSYS_INTPEND) Register MASK  (Use EVSYS_INTPEND_Msk instead)  */
#define EVSYS_INTPEND_Msk                   _U_(0xC303)                                    /**< (EVSYS_INTPEND) Register Mask  */


/* -------- EVSYS_INTSTATUS : (EVSYS Offset: 0x14) (R/ 32) Interrupt Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHINT0:1;                  /**< bit:      0  Channel 0 Pending Interrupt              */
    uint32_t CHINT1:1;                  /**< bit:      1  Channel 1 Pending Interrupt              */
    uint32_t CHINT2:1;                  /**< bit:      2  Channel 2 Pending Interrupt              */
    uint32_t CHINT3:1;                  /**< bit:      3  Channel 3 Pending Interrupt              */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t CHINT:4;                   /**< bit:   0..3  Channel 3 Pending Interrupt              */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_INTSTATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_INTSTATUS_OFFSET              (0x14)                                        /**<  (EVSYS_INTSTATUS) Interrupt Status  Offset */
#define EVSYS_INTSTATUS_RESETVALUE          _U_(0x00)                                     /**<  (EVSYS_INTSTATUS) Interrupt Status  Reset Value */

#define EVSYS_INTSTATUS_CHINT0_Pos          0                                              /**< (EVSYS_INTSTATUS) Channel 0 Pending Interrupt Position */
#define EVSYS_INTSTATUS_CHINT0_Msk          (_U_(0x1) << EVSYS_INTSTATUS_CHINT0_Pos)       /**< (EVSYS_INTSTATUS) Channel 0 Pending Interrupt Mask */
#define EVSYS_INTSTATUS_CHINT0              EVSYS_INTSTATUS_CHINT0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTSTATUS_CHINT0_Msk instead */
#define EVSYS_INTSTATUS_CHINT1_Pos          1                                              /**< (EVSYS_INTSTATUS) Channel 1 Pending Interrupt Position */
#define EVSYS_INTSTATUS_CHINT1_Msk          (_U_(0x1) << EVSYS_INTSTATUS_CHINT1_Pos)       /**< (EVSYS_INTSTATUS) Channel 1 Pending Interrupt Mask */
#define EVSYS_INTSTATUS_CHINT1              EVSYS_INTSTATUS_CHINT1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTSTATUS_CHINT1_Msk instead */
#define EVSYS_INTSTATUS_CHINT2_Pos          2                                              /**< (EVSYS_INTSTATUS) Channel 2 Pending Interrupt Position */
#define EVSYS_INTSTATUS_CHINT2_Msk          (_U_(0x1) << EVSYS_INTSTATUS_CHINT2_Pos)       /**< (EVSYS_INTSTATUS) Channel 2 Pending Interrupt Mask */
#define EVSYS_INTSTATUS_CHINT2              EVSYS_INTSTATUS_CHINT2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTSTATUS_CHINT2_Msk instead */
#define EVSYS_INTSTATUS_CHINT3_Pos          3                                              /**< (EVSYS_INTSTATUS) Channel 3 Pending Interrupt Position */
#define EVSYS_INTSTATUS_CHINT3_Msk          (_U_(0x1) << EVSYS_INTSTATUS_CHINT3_Pos)       /**< (EVSYS_INTSTATUS) Channel 3 Pending Interrupt Mask */
#define EVSYS_INTSTATUS_CHINT3              EVSYS_INTSTATUS_CHINT3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTSTATUS_CHINT3_Msk instead */
#define EVSYS_INTSTATUS_MASK                _U_(0x0F)                                      /**< \deprecated (EVSYS_INTSTATUS) Register MASK  (Use EVSYS_INTSTATUS_Msk instead)  */
#define EVSYS_INTSTATUS_Msk                 _U_(0x0F)                                      /**< (EVSYS_INTSTATUS) Register Mask  */

#define EVSYS_INTSTATUS_CHINT_Pos           0                                              /**< (EVSYS_INTSTATUS Position) Channel 3 Pending Interrupt */
#define EVSYS_INTSTATUS_CHINT_Msk           (_U_(0xF) << EVSYS_INTSTATUS_CHINT_Pos)        /**< (EVSYS_INTSTATUS Mask) CHINT */
#define EVSYS_INTSTATUS_CHINT(value)        (EVSYS_INTSTATUS_CHINT_Msk & ((value) << EVSYS_INTSTATUS_CHINT_Pos))  

/* -------- EVSYS_BUSYCH : (EVSYS Offset: 0x18) (R/ 32) Busy Channels -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUSYCH0:1;                 /**< bit:      0  Busy Channel 0                           */
    uint32_t BUSYCH1:1;                 /**< bit:      1  Busy Channel 1                           */
    uint32_t BUSYCH2:1;                 /**< bit:      2  Busy Channel 2                           */
    uint32_t BUSYCH3:1;                 /**< bit:      3  Busy Channel 3                           */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t BUSYCH:4;                  /**< bit:   0..3  Busy Channel 3                           */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_BUSYCH_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_BUSYCH_OFFSET                 (0x18)                                        /**<  (EVSYS_BUSYCH) Busy Channels  Offset */
#define EVSYS_BUSYCH_RESETVALUE             _U_(0x00)                                     /**<  (EVSYS_BUSYCH) Busy Channels  Reset Value */

#define EVSYS_BUSYCH_BUSYCH0_Pos            0                                              /**< (EVSYS_BUSYCH) Busy Channel 0 Position */
#define EVSYS_BUSYCH_BUSYCH0_Msk            (_U_(0x1) << EVSYS_BUSYCH_BUSYCH0_Pos)         /**< (EVSYS_BUSYCH) Busy Channel 0 Mask */
#define EVSYS_BUSYCH_BUSYCH0                EVSYS_BUSYCH_BUSYCH0_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_BUSYCH_BUSYCH0_Msk instead */
#define EVSYS_BUSYCH_BUSYCH1_Pos            1                                              /**< (EVSYS_BUSYCH) Busy Channel 1 Position */
#define EVSYS_BUSYCH_BUSYCH1_Msk            (_U_(0x1) << EVSYS_BUSYCH_BUSYCH1_Pos)         /**< (EVSYS_BUSYCH) Busy Channel 1 Mask */
#define EVSYS_BUSYCH_BUSYCH1                EVSYS_BUSYCH_BUSYCH1_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_BUSYCH_BUSYCH1_Msk instead */
#define EVSYS_BUSYCH_BUSYCH2_Pos            2                                              /**< (EVSYS_BUSYCH) Busy Channel 2 Position */
#define EVSYS_BUSYCH_BUSYCH2_Msk            (_U_(0x1) << EVSYS_BUSYCH_BUSYCH2_Pos)         /**< (EVSYS_BUSYCH) Busy Channel 2 Mask */
#define EVSYS_BUSYCH_BUSYCH2                EVSYS_BUSYCH_BUSYCH2_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_BUSYCH_BUSYCH2_Msk instead */
#define EVSYS_BUSYCH_BUSYCH3_Pos            3                                              /**< (EVSYS_BUSYCH) Busy Channel 3 Position */
#define EVSYS_BUSYCH_BUSYCH3_Msk            (_U_(0x1) << EVSYS_BUSYCH_BUSYCH3_Pos)         /**< (EVSYS_BUSYCH) Busy Channel 3 Mask */
#define EVSYS_BUSYCH_BUSYCH3                EVSYS_BUSYCH_BUSYCH3_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_BUSYCH_BUSYCH3_Msk instead */
#define EVSYS_BUSYCH_MASK                   _U_(0x0F)                                      /**< \deprecated (EVSYS_BUSYCH) Register MASK  (Use EVSYS_BUSYCH_Msk instead)  */
#define EVSYS_BUSYCH_Msk                    _U_(0x0F)                                      /**< (EVSYS_BUSYCH) Register Mask  */

#define EVSYS_BUSYCH_BUSYCH_Pos             0                                              /**< (EVSYS_BUSYCH Position) Busy Channel 3 */
#define EVSYS_BUSYCH_BUSYCH_Msk             (_U_(0xF) << EVSYS_BUSYCH_BUSYCH_Pos)          /**< (EVSYS_BUSYCH Mask) BUSYCH */
#define EVSYS_BUSYCH_BUSYCH(value)          (EVSYS_BUSYCH_BUSYCH_Msk & ((value) << EVSYS_BUSYCH_BUSYCH_Pos))  

/* -------- EVSYS_READYUSR : (EVSYS Offset: 0x1c) (R/ 32) Ready Users -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t READYUSR0:1;               /**< bit:      0  Ready User for Channel 0                 */
    uint32_t READYUSR1:1;               /**< bit:      1  Ready User for Channel 1                 */
    uint32_t READYUSR2:1;               /**< bit:      2  Ready User for Channel 2                 */
    uint32_t READYUSR3:1;               /**< bit:      3  Ready User for Channel 3                 */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t READYUSR:4;                /**< bit:   0..3  Ready User for Channel 3                 */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_READYUSR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_READYUSR_OFFSET               (0x1C)                                        /**<  (EVSYS_READYUSR) Ready Users  Offset */
#define EVSYS_READYUSR_RESETVALUE           _U_(0xFFFFFFFF)                               /**<  (EVSYS_READYUSR) Ready Users  Reset Value */

#define EVSYS_READYUSR_READYUSR0_Pos        0                                              /**< (EVSYS_READYUSR) Ready User for Channel 0 Position */
#define EVSYS_READYUSR_READYUSR0_Msk        (_U_(0x1) << EVSYS_READYUSR_READYUSR0_Pos)     /**< (EVSYS_READYUSR) Ready User for Channel 0 Mask */
#define EVSYS_READYUSR_READYUSR0            EVSYS_READYUSR_READYUSR0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_READYUSR_READYUSR0_Msk instead */
#define EVSYS_READYUSR_READYUSR1_Pos        1                                              /**< (EVSYS_READYUSR) Ready User for Channel 1 Position */
#define EVSYS_READYUSR_READYUSR1_Msk        (_U_(0x1) << EVSYS_READYUSR_READYUSR1_Pos)     /**< (EVSYS_READYUSR) Ready User for Channel 1 Mask */
#define EVSYS_READYUSR_READYUSR1            EVSYS_READYUSR_READYUSR1_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_READYUSR_READYUSR1_Msk instead */
#define EVSYS_READYUSR_READYUSR2_Pos        2                                              /**< (EVSYS_READYUSR) Ready User for Channel 2 Position */
#define EVSYS_READYUSR_READYUSR2_Msk        (_U_(0x1) << EVSYS_READYUSR_READYUSR2_Pos)     /**< (EVSYS_READYUSR) Ready User for Channel 2 Mask */
#define EVSYS_READYUSR_READYUSR2            EVSYS_READYUSR_READYUSR2_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_READYUSR_READYUSR2_Msk instead */
#define EVSYS_READYUSR_READYUSR3_Pos        3                                              /**< (EVSYS_READYUSR) Ready User for Channel 3 Position */
#define EVSYS_READYUSR_READYUSR3_Msk        (_U_(0x1) << EVSYS_READYUSR_READYUSR3_Pos)     /**< (EVSYS_READYUSR) Ready User for Channel 3 Mask */
#define EVSYS_READYUSR_READYUSR3            EVSYS_READYUSR_READYUSR3_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_READYUSR_READYUSR3_Msk instead */
#define EVSYS_READYUSR_MASK                 _U_(0x0F)                                      /**< \deprecated (EVSYS_READYUSR) Register MASK  (Use EVSYS_READYUSR_Msk instead)  */
#define EVSYS_READYUSR_Msk                  _U_(0x0F)                                      /**< (EVSYS_READYUSR) Register Mask  */

#define EVSYS_READYUSR_READYUSR_Pos         0                                              /**< (EVSYS_READYUSR Position) Ready User for Channel 3 */
#define EVSYS_READYUSR_READYUSR_Msk         (_U_(0xF) << EVSYS_READYUSR_READYUSR_Pos)      /**< (EVSYS_READYUSR Mask) READYUSR */
#define EVSYS_READYUSR_READYUSR(value)      (EVSYS_READYUSR_READYUSR_Msk & ((value) << EVSYS_READYUSR_READYUSR_Pos))  

/* -------- EVSYS_USER : (EVSYS Offset: 0x120) (R/W 8) User Multiplexer n -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CHANNEL:4;                 /**< bit:   0..3  Channel Event Selection                  */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_USER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_USER_OFFSET                   (0x120)                                       /**<  (EVSYS_USER) User Multiplexer n  Offset */
#define EVSYS_USER_RESETVALUE               _U_(0x00)                                     /**<  (EVSYS_USER) User Multiplexer n  Reset Value */

#define EVSYS_USER_CHANNEL_Pos              0                                              /**< (EVSYS_USER) Channel Event Selection Position */
#define EVSYS_USER_CHANNEL_Msk              (_U_(0xF) << EVSYS_USER_CHANNEL_Pos)           /**< (EVSYS_USER) Channel Event Selection Mask */
#define EVSYS_USER_CHANNEL(value)           (EVSYS_USER_CHANNEL_Msk & ((value) << EVSYS_USER_CHANNEL_Pos))
#define EVSYS_USER_MASK                     _U_(0x0F)                                      /**< \deprecated (EVSYS_USER) Register MASK  (Use EVSYS_USER_Msk instead)  */
#define EVSYS_USER_Msk                      _U_(0x0F)                                      /**< (EVSYS_USER) Register Mask  */


/* -------- EVSYS_INTENCLR : (EVSYS Offset: 0x1d4) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  NSCHK:1;                   /**< bit:      0  Non-Secure Check Interrupt Enable        */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_INTENCLR_OFFSET               (0x1D4)                                       /**<  (EVSYS_INTENCLR) Interrupt Enable Clear  Offset */
#define EVSYS_INTENCLR_RESETVALUE           _U_(0x00)                                     /**<  (EVSYS_INTENCLR) Interrupt Enable Clear  Reset Value */

#define EVSYS_INTENCLR_NSCHK_Pos            0                                              /**< (EVSYS_INTENCLR) Non-Secure Check Interrupt Enable Position */
#define EVSYS_INTENCLR_NSCHK_Msk            (_U_(0x1) << EVSYS_INTENCLR_NSCHK_Pos)         /**< (EVSYS_INTENCLR) Non-Secure Check Interrupt Enable Mask */
#define EVSYS_INTENCLR_NSCHK                EVSYS_INTENCLR_NSCHK_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTENCLR_NSCHK_Msk instead */
#define EVSYS_INTENCLR_MASK                 _U_(0x01)                                      /**< \deprecated (EVSYS_INTENCLR) Register MASK  (Use EVSYS_INTENCLR_Msk instead)  */
#define EVSYS_INTENCLR_Msk                  _U_(0x01)                                      /**< (EVSYS_INTENCLR) Register Mask  */


/* -------- EVSYS_INTENSET : (EVSYS Offset: 0x1d5) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  NSCHK:1;                   /**< bit:      0  Non-Secure Check Interrupt Enable        */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_INTENSET_OFFSET               (0x1D5)                                       /**<  (EVSYS_INTENSET) Interrupt Enable Set  Offset */
#define EVSYS_INTENSET_RESETVALUE           _U_(0x00)                                     /**<  (EVSYS_INTENSET) Interrupt Enable Set  Reset Value */

#define EVSYS_INTENSET_NSCHK_Pos            0                                              /**< (EVSYS_INTENSET) Non-Secure Check Interrupt Enable Position */
#define EVSYS_INTENSET_NSCHK_Msk            (_U_(0x1) << EVSYS_INTENSET_NSCHK_Pos)         /**< (EVSYS_INTENSET) Non-Secure Check Interrupt Enable Mask */
#define EVSYS_INTENSET_NSCHK                EVSYS_INTENSET_NSCHK_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTENSET_NSCHK_Msk instead */
#define EVSYS_INTENSET_MASK                 _U_(0x01)                                      /**< \deprecated (EVSYS_INTENSET) Register MASK  (Use EVSYS_INTENSET_Msk instead)  */
#define EVSYS_INTENSET_Msk                  _U_(0x01)                                      /**< (EVSYS_INTENSET) Register Mask  */


/* -------- EVSYS_INTFLAG : (EVSYS Offset: 0x1d6) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t NSCHK:1;                   /**< bit:      0  Non-Secure Check                         */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EVSYS_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_INTFLAG_OFFSET                (0x1D6)                                       /**<  (EVSYS_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define EVSYS_INTFLAG_RESETVALUE            _U_(0x00)                                     /**<  (EVSYS_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define EVSYS_INTFLAG_NSCHK_Pos             0                                              /**< (EVSYS_INTFLAG) Non-Secure Check Position */
#define EVSYS_INTFLAG_NSCHK_Msk             (_U_(0x1) << EVSYS_INTFLAG_NSCHK_Pos)          /**< (EVSYS_INTFLAG) Non-Secure Check Mask */
#define EVSYS_INTFLAG_NSCHK                 EVSYS_INTFLAG_NSCHK_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_INTFLAG_NSCHK_Msk instead */
#define EVSYS_INTFLAG_MASK                  _U_(0x01)                                      /**< \deprecated (EVSYS_INTFLAG) Register MASK  (Use EVSYS_INTFLAG_Msk instead)  */
#define EVSYS_INTFLAG_Msk                   _U_(0x01)                                      /**< (EVSYS_INTFLAG) Register Mask  */


/* -------- EVSYS_NONSECCHAN : (EVSYS Offset: 0x1d8) (R/W 32) Channels Security Attribution -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHANNEL0:1;                /**< bit:      0  Non-Secure for Channel 0                 */
    uint32_t CHANNEL1:1;                /**< bit:      1  Non-Secure for Channel 1                 */
    uint32_t CHANNEL2:1;                /**< bit:      2  Non-Secure for Channel 2                 */
    uint32_t CHANNEL3:1;                /**< bit:      3  Non-Secure for Channel 3                 */
    uint32_t CHANNEL4:1;                /**< bit:      4  Non-Secure for Channel 4                 */
    uint32_t CHANNEL5:1;                /**< bit:      5  Non-Secure for Channel 5                 */
    uint32_t CHANNEL6:1;                /**< bit:      6  Non-Secure for Channel 6                 */
    uint32_t CHANNEL7:1;                /**< bit:      7  Non-Secure for Channel 7                 */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t CHANNEL:8;                 /**< bit:   0..7  Non-Secure for Channel 7                 */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_NONSECCHAN_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_NONSECCHAN_OFFSET             (0x1D8)                                       /**<  (EVSYS_NONSECCHAN) Channels Security Attribution  Offset */
#define EVSYS_NONSECCHAN_RESETVALUE         _U_(0x00)                                     /**<  (EVSYS_NONSECCHAN) Channels Security Attribution  Reset Value */

#define EVSYS_NONSECCHAN_CHANNEL0_Pos       0                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 0 Position */
#define EVSYS_NONSECCHAN_CHANNEL0_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL0_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 0 Mask */
#define EVSYS_NONSECCHAN_CHANNEL0           EVSYS_NONSECCHAN_CHANNEL0_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL0_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL1_Pos       1                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 1 Position */
#define EVSYS_NONSECCHAN_CHANNEL1_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL1_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 1 Mask */
#define EVSYS_NONSECCHAN_CHANNEL1           EVSYS_NONSECCHAN_CHANNEL1_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL1_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL2_Pos       2                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 2 Position */
#define EVSYS_NONSECCHAN_CHANNEL2_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL2_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 2 Mask */
#define EVSYS_NONSECCHAN_CHANNEL2           EVSYS_NONSECCHAN_CHANNEL2_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL2_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL3_Pos       3                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 3 Position */
#define EVSYS_NONSECCHAN_CHANNEL3_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL3_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 3 Mask */
#define EVSYS_NONSECCHAN_CHANNEL3           EVSYS_NONSECCHAN_CHANNEL3_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL3_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL4_Pos       4                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 4 Position */
#define EVSYS_NONSECCHAN_CHANNEL4_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL4_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 4 Mask */
#define EVSYS_NONSECCHAN_CHANNEL4           EVSYS_NONSECCHAN_CHANNEL4_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL4_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL5_Pos       5                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 5 Position */
#define EVSYS_NONSECCHAN_CHANNEL5_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL5_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 5 Mask */
#define EVSYS_NONSECCHAN_CHANNEL5           EVSYS_NONSECCHAN_CHANNEL5_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL5_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL6_Pos       6                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 6 Position */
#define EVSYS_NONSECCHAN_CHANNEL6_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL6_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 6 Mask */
#define EVSYS_NONSECCHAN_CHANNEL6           EVSYS_NONSECCHAN_CHANNEL6_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL6_Msk instead */
#define EVSYS_NONSECCHAN_CHANNEL7_Pos       7                                              /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 7 Position */
#define EVSYS_NONSECCHAN_CHANNEL7_Msk       (_U_(0x1) << EVSYS_NONSECCHAN_CHANNEL7_Pos)    /**< (EVSYS_NONSECCHAN) Non-Secure for Channel 7 Mask */
#define EVSYS_NONSECCHAN_CHANNEL7           EVSYS_NONSECCHAN_CHANNEL7_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECCHAN_CHANNEL7_Msk instead */
#define EVSYS_NONSECCHAN_MASK               _U_(0xFF)                                      /**< \deprecated (EVSYS_NONSECCHAN) Register MASK  (Use EVSYS_NONSECCHAN_Msk instead)  */
#define EVSYS_NONSECCHAN_Msk                _U_(0xFF)                                      /**< (EVSYS_NONSECCHAN) Register Mask  */

#define EVSYS_NONSECCHAN_CHANNEL_Pos        0                                              /**< (EVSYS_NONSECCHAN Position) Non-Secure for Channel 7 */
#define EVSYS_NONSECCHAN_CHANNEL_Msk        (_U_(0xFF) << EVSYS_NONSECCHAN_CHANNEL_Pos)    /**< (EVSYS_NONSECCHAN Mask) CHANNEL */
#define EVSYS_NONSECCHAN_CHANNEL(value)     (EVSYS_NONSECCHAN_CHANNEL_Msk & ((value) << EVSYS_NONSECCHAN_CHANNEL_Pos))  

/* -------- EVSYS_NSCHKCHAN : (EVSYS Offset: 0x1dc) (R/W 32) Non-Secure Channels Check -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHANNEL0:1;                /**< bit:      0  Channel 0 to be checked as non-secured   */
    uint32_t CHANNEL1:1;                /**< bit:      1  Channel 1 to be checked as non-secured   */
    uint32_t CHANNEL2:1;                /**< bit:      2  Channel 2 to be checked as non-secured   */
    uint32_t CHANNEL3:1;                /**< bit:      3  Channel 3 to be checked as non-secured   */
    uint32_t CHANNEL4:1;                /**< bit:      4  Channel 4 to be checked as non-secured   */
    uint32_t CHANNEL5:1;                /**< bit:      5  Channel 5 to be checked as non-secured   */
    uint32_t CHANNEL6:1;                /**< bit:      6  Channel 6 to be checked as non-secured   */
    uint32_t CHANNEL7:1;                /**< bit:      7  Channel 7 to be checked as non-secured   */
    uint32_t :24;                       /**< bit:  8..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t CHANNEL:8;                 /**< bit:   0..7  Channel 7 to be checked as non-secured   */
    uint32_t :24;                       /**< bit:  8..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_NSCHKCHAN_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_NSCHKCHAN_OFFSET              (0x1DC)                                       /**<  (EVSYS_NSCHKCHAN) Non-Secure Channels Check  Offset */
#define EVSYS_NSCHKCHAN_RESETVALUE          _U_(0x00)                                     /**<  (EVSYS_NSCHKCHAN) Non-Secure Channels Check  Reset Value */

#define EVSYS_NSCHKCHAN_CHANNEL0_Pos        0                                              /**< (EVSYS_NSCHKCHAN) Channel 0 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL0_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL0_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 0 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL0            EVSYS_NSCHKCHAN_CHANNEL0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL0_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL1_Pos        1                                              /**< (EVSYS_NSCHKCHAN) Channel 1 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL1_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL1_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 1 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL1            EVSYS_NSCHKCHAN_CHANNEL1_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL1_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL2_Pos        2                                              /**< (EVSYS_NSCHKCHAN) Channel 2 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL2_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL2_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 2 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL2            EVSYS_NSCHKCHAN_CHANNEL2_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL2_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL3_Pos        3                                              /**< (EVSYS_NSCHKCHAN) Channel 3 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL3_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL3_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 3 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL3            EVSYS_NSCHKCHAN_CHANNEL3_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL3_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL4_Pos        4                                              /**< (EVSYS_NSCHKCHAN) Channel 4 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL4_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL4_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 4 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL4            EVSYS_NSCHKCHAN_CHANNEL4_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL4_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL5_Pos        5                                              /**< (EVSYS_NSCHKCHAN) Channel 5 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL5_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL5_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 5 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL5            EVSYS_NSCHKCHAN_CHANNEL5_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL5_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL6_Pos        6                                              /**< (EVSYS_NSCHKCHAN) Channel 6 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL6_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL6_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 6 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL6            EVSYS_NSCHKCHAN_CHANNEL6_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL6_Msk instead */
#define EVSYS_NSCHKCHAN_CHANNEL7_Pos        7                                              /**< (EVSYS_NSCHKCHAN) Channel 7 to be checked as non-secured Position */
#define EVSYS_NSCHKCHAN_CHANNEL7_Msk        (_U_(0x1) << EVSYS_NSCHKCHAN_CHANNEL7_Pos)     /**< (EVSYS_NSCHKCHAN) Channel 7 to be checked as non-secured Mask */
#define EVSYS_NSCHKCHAN_CHANNEL7            EVSYS_NSCHKCHAN_CHANNEL7_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKCHAN_CHANNEL7_Msk instead */
#define EVSYS_NSCHKCHAN_MASK                _U_(0xFF)                                      /**< \deprecated (EVSYS_NSCHKCHAN) Register MASK  (Use EVSYS_NSCHKCHAN_Msk instead)  */
#define EVSYS_NSCHKCHAN_Msk                 _U_(0xFF)                                      /**< (EVSYS_NSCHKCHAN) Register Mask  */

#define EVSYS_NSCHKCHAN_CHANNEL_Pos         0                                              /**< (EVSYS_NSCHKCHAN Position) Channel 7 to be checked as non-secured */
#define EVSYS_NSCHKCHAN_CHANNEL_Msk         (_U_(0xFF) << EVSYS_NSCHKCHAN_CHANNEL_Pos)     /**< (EVSYS_NSCHKCHAN Mask) CHANNEL */
#define EVSYS_NSCHKCHAN_CHANNEL(value)      (EVSYS_NSCHKCHAN_CHANNEL_Msk & ((value) << EVSYS_NSCHKCHAN_CHANNEL_Pos))  

/* -------- EVSYS_NONSECUSER : (EVSYS Offset: 0x1e0) (R/W 32) Users Security Attribution -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t USER0:1;                   /**< bit:      0  Non-Secure for User 0                    */
    uint32_t USER1:1;                   /**< bit:      1  Non-Secure for User 1                    */
    uint32_t USER2:1;                   /**< bit:      2  Non-Secure for User 2                    */
    uint32_t USER3:1;                   /**< bit:      3  Non-Secure for User 3                    */
    uint32_t USER4:1;                   /**< bit:      4  Non-Secure for User 4                    */
    uint32_t USER5:1;                   /**< bit:      5  Non-Secure for User 5                    */
    uint32_t USER6:1;                   /**< bit:      6  Non-Secure for User 6                    */
    uint32_t USER7:1;                   /**< bit:      7  Non-Secure for User 7                    */
    uint32_t USER8:1;                   /**< bit:      8  Non-Secure for User 8                    */
    uint32_t USER9:1;                   /**< bit:      9  Non-Secure for User 9                    */
    uint32_t USER10:1;                  /**< bit:     10  Non-Secure for User 10                   */
    uint32_t USER11:1;                  /**< bit:     11  Non-Secure for User 11                   */
    uint32_t USER12:1;                  /**< bit:     12  Non-Secure for User 12                   */
    uint32_t USER13:1;                  /**< bit:     13  Non-Secure for User 13                   */
    uint32_t USER14:1;                  /**< bit:     14  Non-Secure for User 14                   */
    uint32_t USER15:1;                  /**< bit:     15  Non-Secure for User 15                   */
    uint32_t USER16:1;                  /**< bit:     16  Non-Secure for User 16                   */
    uint32_t USER17:1;                  /**< bit:     17  Non-Secure for User 17                   */
    uint32_t USER18:1;                  /**< bit:     18  Non-Secure for User 18                   */
    uint32_t USER19:1;                  /**< bit:     19  Non-Secure for User 19                   */
    uint32_t USER20:1;                  /**< bit:     20  Non-Secure for User 20                   */
    uint32_t USER21:1;                  /**< bit:     21  Non-Secure for User 21                   */
    uint32_t USER22:1;                  /**< bit:     22  Non-Secure for User 22                   */
    uint32_t :9;                        /**< bit: 23..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t USER:23;                   /**< bit:  0..22  Non-Secure for User 22                   */
    uint32_t :9;                        /**< bit: 23..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_NONSECUSER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_NONSECUSER_OFFSET             (0x1E0)                                       /**<  (EVSYS_NONSECUSER) Users Security Attribution  Offset */
#define EVSYS_NONSECUSER_RESETVALUE         _U_(0x00)                                     /**<  (EVSYS_NONSECUSER) Users Security Attribution  Reset Value */

#define EVSYS_NONSECUSER_USER0_Pos          0                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 0 Position */
#define EVSYS_NONSECUSER_USER0_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER0_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 0 Mask */
#define EVSYS_NONSECUSER_USER0              EVSYS_NONSECUSER_USER0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER0_Msk instead */
#define EVSYS_NONSECUSER_USER1_Pos          1                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 1 Position */
#define EVSYS_NONSECUSER_USER1_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER1_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 1 Mask */
#define EVSYS_NONSECUSER_USER1              EVSYS_NONSECUSER_USER1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER1_Msk instead */
#define EVSYS_NONSECUSER_USER2_Pos          2                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 2 Position */
#define EVSYS_NONSECUSER_USER2_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER2_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 2 Mask */
#define EVSYS_NONSECUSER_USER2              EVSYS_NONSECUSER_USER2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER2_Msk instead */
#define EVSYS_NONSECUSER_USER3_Pos          3                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 3 Position */
#define EVSYS_NONSECUSER_USER3_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER3_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 3 Mask */
#define EVSYS_NONSECUSER_USER3              EVSYS_NONSECUSER_USER3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER3_Msk instead */
#define EVSYS_NONSECUSER_USER4_Pos          4                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 4 Position */
#define EVSYS_NONSECUSER_USER4_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER4_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 4 Mask */
#define EVSYS_NONSECUSER_USER4              EVSYS_NONSECUSER_USER4_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER4_Msk instead */
#define EVSYS_NONSECUSER_USER5_Pos          5                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 5 Position */
#define EVSYS_NONSECUSER_USER5_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER5_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 5 Mask */
#define EVSYS_NONSECUSER_USER5              EVSYS_NONSECUSER_USER5_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER5_Msk instead */
#define EVSYS_NONSECUSER_USER6_Pos          6                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 6 Position */
#define EVSYS_NONSECUSER_USER6_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER6_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 6 Mask */
#define EVSYS_NONSECUSER_USER6              EVSYS_NONSECUSER_USER6_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER6_Msk instead */
#define EVSYS_NONSECUSER_USER7_Pos          7                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 7 Position */
#define EVSYS_NONSECUSER_USER7_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER7_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 7 Mask */
#define EVSYS_NONSECUSER_USER7              EVSYS_NONSECUSER_USER7_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER7_Msk instead */
#define EVSYS_NONSECUSER_USER8_Pos          8                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 8 Position */
#define EVSYS_NONSECUSER_USER8_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER8_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 8 Mask */
#define EVSYS_NONSECUSER_USER8              EVSYS_NONSECUSER_USER8_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER8_Msk instead */
#define EVSYS_NONSECUSER_USER9_Pos          9                                              /**< (EVSYS_NONSECUSER) Non-Secure for User 9 Position */
#define EVSYS_NONSECUSER_USER9_Msk          (_U_(0x1) << EVSYS_NONSECUSER_USER9_Pos)       /**< (EVSYS_NONSECUSER) Non-Secure for User 9 Mask */
#define EVSYS_NONSECUSER_USER9              EVSYS_NONSECUSER_USER9_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER9_Msk instead */
#define EVSYS_NONSECUSER_USER10_Pos         10                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 10 Position */
#define EVSYS_NONSECUSER_USER10_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER10_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 10 Mask */
#define EVSYS_NONSECUSER_USER10             EVSYS_NONSECUSER_USER10_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER10_Msk instead */
#define EVSYS_NONSECUSER_USER11_Pos         11                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 11 Position */
#define EVSYS_NONSECUSER_USER11_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER11_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 11 Mask */
#define EVSYS_NONSECUSER_USER11             EVSYS_NONSECUSER_USER11_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER11_Msk instead */
#define EVSYS_NONSECUSER_USER12_Pos         12                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 12 Position */
#define EVSYS_NONSECUSER_USER12_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER12_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 12 Mask */
#define EVSYS_NONSECUSER_USER12             EVSYS_NONSECUSER_USER12_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER12_Msk instead */
#define EVSYS_NONSECUSER_USER13_Pos         13                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 13 Position */
#define EVSYS_NONSECUSER_USER13_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER13_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 13 Mask */
#define EVSYS_NONSECUSER_USER13             EVSYS_NONSECUSER_USER13_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER13_Msk instead */
#define EVSYS_NONSECUSER_USER14_Pos         14                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 14 Position */
#define EVSYS_NONSECUSER_USER14_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER14_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 14 Mask */
#define EVSYS_NONSECUSER_USER14             EVSYS_NONSECUSER_USER14_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER14_Msk instead */
#define EVSYS_NONSECUSER_USER15_Pos         15                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 15 Position */
#define EVSYS_NONSECUSER_USER15_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER15_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 15 Mask */
#define EVSYS_NONSECUSER_USER15             EVSYS_NONSECUSER_USER15_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER15_Msk instead */
#define EVSYS_NONSECUSER_USER16_Pos         16                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 16 Position */
#define EVSYS_NONSECUSER_USER16_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER16_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 16 Mask */
#define EVSYS_NONSECUSER_USER16             EVSYS_NONSECUSER_USER16_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER16_Msk instead */
#define EVSYS_NONSECUSER_USER17_Pos         17                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 17 Position */
#define EVSYS_NONSECUSER_USER17_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER17_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 17 Mask */
#define EVSYS_NONSECUSER_USER17             EVSYS_NONSECUSER_USER17_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER17_Msk instead */
#define EVSYS_NONSECUSER_USER18_Pos         18                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 18 Position */
#define EVSYS_NONSECUSER_USER18_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER18_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 18 Mask */
#define EVSYS_NONSECUSER_USER18             EVSYS_NONSECUSER_USER18_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER18_Msk instead */
#define EVSYS_NONSECUSER_USER19_Pos         19                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 19 Position */
#define EVSYS_NONSECUSER_USER19_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER19_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 19 Mask */
#define EVSYS_NONSECUSER_USER19             EVSYS_NONSECUSER_USER19_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER19_Msk instead */
#define EVSYS_NONSECUSER_USER20_Pos         20                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 20 Position */
#define EVSYS_NONSECUSER_USER20_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER20_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 20 Mask */
#define EVSYS_NONSECUSER_USER20             EVSYS_NONSECUSER_USER20_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER20_Msk instead */
#define EVSYS_NONSECUSER_USER21_Pos         21                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 21 Position */
#define EVSYS_NONSECUSER_USER21_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER21_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 21 Mask */
#define EVSYS_NONSECUSER_USER21             EVSYS_NONSECUSER_USER21_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER21_Msk instead */
#define EVSYS_NONSECUSER_USER22_Pos         22                                             /**< (EVSYS_NONSECUSER) Non-Secure for User 22 Position */
#define EVSYS_NONSECUSER_USER22_Msk         (_U_(0x1) << EVSYS_NONSECUSER_USER22_Pos)      /**< (EVSYS_NONSECUSER) Non-Secure for User 22 Mask */
#define EVSYS_NONSECUSER_USER22             EVSYS_NONSECUSER_USER22_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NONSECUSER_USER22_Msk instead */
#define EVSYS_NONSECUSER_MASK               _U_(0x7FFFFF)                                  /**< \deprecated (EVSYS_NONSECUSER) Register MASK  (Use EVSYS_NONSECUSER_Msk instead)  */
#define EVSYS_NONSECUSER_Msk                _U_(0x7FFFFF)                                  /**< (EVSYS_NONSECUSER) Register Mask  */

#define EVSYS_NONSECUSER_USER_Pos           0                                              /**< (EVSYS_NONSECUSER Position) Non-Secure for User 22 */
#define EVSYS_NONSECUSER_USER_Msk           (_U_(0x7FFFFF) << EVSYS_NONSECUSER_USER_Pos)   /**< (EVSYS_NONSECUSER Mask) USER */
#define EVSYS_NONSECUSER_USER(value)        (EVSYS_NONSECUSER_USER_Msk & ((value) << EVSYS_NONSECUSER_USER_Pos))  

/* -------- EVSYS_NSCHKUSER : (EVSYS Offset: 0x1f0) (R/W 32) Non-Secure Users Check -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t USER0:1;                   /**< bit:      0  User 0 to be checked as non-secured      */
    uint32_t USER1:1;                   /**< bit:      1  User 1 to be checked as non-secured      */
    uint32_t USER2:1;                   /**< bit:      2  User 2 to be checked as non-secured      */
    uint32_t USER3:1;                   /**< bit:      3  User 3 to be checked as non-secured      */
    uint32_t USER4:1;                   /**< bit:      4  User 4 to be checked as non-secured      */
    uint32_t USER5:1;                   /**< bit:      5  User 5 to be checked as non-secured      */
    uint32_t USER6:1;                   /**< bit:      6  User 6 to be checked as non-secured      */
    uint32_t USER7:1;                   /**< bit:      7  User 7 to be checked as non-secured      */
    uint32_t USER8:1;                   /**< bit:      8  User 8 to be checked as non-secured      */
    uint32_t USER9:1;                   /**< bit:      9  User 9 to be checked as non-secured      */
    uint32_t USER10:1;                  /**< bit:     10  User 10 to be checked as non-secured     */
    uint32_t USER11:1;                  /**< bit:     11  User 11 to be checked as non-secured     */
    uint32_t USER12:1;                  /**< bit:     12  User 12 to be checked as non-secured     */
    uint32_t USER13:1;                  /**< bit:     13  User 13 to be checked as non-secured     */
    uint32_t USER14:1;                  /**< bit:     14  User 14 to be checked as non-secured     */
    uint32_t USER15:1;                  /**< bit:     15  User 15 to be checked as non-secured     */
    uint32_t USER16:1;                  /**< bit:     16  User 16 to be checked as non-secured     */
    uint32_t USER17:1;                  /**< bit:     17  User 17 to be checked as non-secured     */
    uint32_t USER18:1;                  /**< bit:     18  User 18 to be checked as non-secured     */
    uint32_t USER19:1;                  /**< bit:     19  User 19 to be checked as non-secured     */
    uint32_t USER20:1;                  /**< bit:     20  User 20 to be checked as non-secured     */
    uint32_t USER21:1;                  /**< bit:     21  User 21 to be checked as non-secured     */
    uint32_t USER22:1;                  /**< bit:     22  User 22 to be checked as non-secured     */
    uint32_t :9;                        /**< bit: 23..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t USER:23;                   /**< bit:  0..22  User 22 to be checked as non-secured     */
    uint32_t :9;                        /**< bit: 23..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} EVSYS_NSCHKUSER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EVSYS_NSCHKUSER_OFFSET              (0x1F0)                                       /**<  (EVSYS_NSCHKUSER) Non-Secure Users Check  Offset */
#define EVSYS_NSCHKUSER_RESETVALUE          _U_(0x00)                                     /**<  (EVSYS_NSCHKUSER) Non-Secure Users Check  Reset Value */

#define EVSYS_NSCHKUSER_USER0_Pos           0                                              /**< (EVSYS_NSCHKUSER) User 0 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER0_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER0_Pos)        /**< (EVSYS_NSCHKUSER) User 0 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER0               EVSYS_NSCHKUSER_USER0_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER0_Msk instead */
#define EVSYS_NSCHKUSER_USER1_Pos           1                                              /**< (EVSYS_NSCHKUSER) User 1 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER1_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER1_Pos)        /**< (EVSYS_NSCHKUSER) User 1 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER1               EVSYS_NSCHKUSER_USER1_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER1_Msk instead */
#define EVSYS_NSCHKUSER_USER2_Pos           2                                              /**< (EVSYS_NSCHKUSER) User 2 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER2_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER2_Pos)        /**< (EVSYS_NSCHKUSER) User 2 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER2               EVSYS_NSCHKUSER_USER2_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER2_Msk instead */
#define EVSYS_NSCHKUSER_USER3_Pos           3                                              /**< (EVSYS_NSCHKUSER) User 3 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER3_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER3_Pos)        /**< (EVSYS_NSCHKUSER) User 3 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER3               EVSYS_NSCHKUSER_USER3_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER3_Msk instead */
#define EVSYS_NSCHKUSER_USER4_Pos           4                                              /**< (EVSYS_NSCHKUSER) User 4 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER4_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER4_Pos)        /**< (EVSYS_NSCHKUSER) User 4 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER4               EVSYS_NSCHKUSER_USER4_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER4_Msk instead */
#define EVSYS_NSCHKUSER_USER5_Pos           5                                              /**< (EVSYS_NSCHKUSER) User 5 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER5_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER5_Pos)        /**< (EVSYS_NSCHKUSER) User 5 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER5               EVSYS_NSCHKUSER_USER5_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER5_Msk instead */
#define EVSYS_NSCHKUSER_USER6_Pos           6                                              /**< (EVSYS_NSCHKUSER) User 6 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER6_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER6_Pos)        /**< (EVSYS_NSCHKUSER) User 6 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER6               EVSYS_NSCHKUSER_USER6_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER6_Msk instead */
#define EVSYS_NSCHKUSER_USER7_Pos           7                                              /**< (EVSYS_NSCHKUSER) User 7 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER7_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER7_Pos)        /**< (EVSYS_NSCHKUSER) User 7 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER7               EVSYS_NSCHKUSER_USER7_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER7_Msk instead */
#define EVSYS_NSCHKUSER_USER8_Pos           8                                              /**< (EVSYS_NSCHKUSER) User 8 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER8_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER8_Pos)        /**< (EVSYS_NSCHKUSER) User 8 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER8               EVSYS_NSCHKUSER_USER8_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER8_Msk instead */
#define EVSYS_NSCHKUSER_USER9_Pos           9                                              /**< (EVSYS_NSCHKUSER) User 9 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER9_Msk           (_U_(0x1) << EVSYS_NSCHKUSER_USER9_Pos)        /**< (EVSYS_NSCHKUSER) User 9 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER9               EVSYS_NSCHKUSER_USER9_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER9_Msk instead */
#define EVSYS_NSCHKUSER_USER10_Pos          10                                             /**< (EVSYS_NSCHKUSER) User 10 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER10_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER10_Pos)       /**< (EVSYS_NSCHKUSER) User 10 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER10              EVSYS_NSCHKUSER_USER10_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER10_Msk instead */
#define EVSYS_NSCHKUSER_USER11_Pos          11                                             /**< (EVSYS_NSCHKUSER) User 11 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER11_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER11_Pos)       /**< (EVSYS_NSCHKUSER) User 11 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER11              EVSYS_NSCHKUSER_USER11_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER11_Msk instead */
#define EVSYS_NSCHKUSER_USER12_Pos          12                                             /**< (EVSYS_NSCHKUSER) User 12 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER12_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER12_Pos)       /**< (EVSYS_NSCHKUSER) User 12 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER12              EVSYS_NSCHKUSER_USER12_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER12_Msk instead */
#define EVSYS_NSCHKUSER_USER13_Pos          13                                             /**< (EVSYS_NSCHKUSER) User 13 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER13_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER13_Pos)       /**< (EVSYS_NSCHKUSER) User 13 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER13              EVSYS_NSCHKUSER_USER13_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER13_Msk instead */
#define EVSYS_NSCHKUSER_USER14_Pos          14                                             /**< (EVSYS_NSCHKUSER) User 14 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER14_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER14_Pos)       /**< (EVSYS_NSCHKUSER) User 14 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER14              EVSYS_NSCHKUSER_USER14_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER14_Msk instead */
#define EVSYS_NSCHKUSER_USER15_Pos          15                                             /**< (EVSYS_NSCHKUSER) User 15 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER15_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER15_Pos)       /**< (EVSYS_NSCHKUSER) User 15 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER15              EVSYS_NSCHKUSER_USER15_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER15_Msk instead */
#define EVSYS_NSCHKUSER_USER16_Pos          16                                             /**< (EVSYS_NSCHKUSER) User 16 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER16_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER16_Pos)       /**< (EVSYS_NSCHKUSER) User 16 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER16              EVSYS_NSCHKUSER_USER16_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER16_Msk instead */
#define EVSYS_NSCHKUSER_USER17_Pos          17                                             /**< (EVSYS_NSCHKUSER) User 17 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER17_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER17_Pos)       /**< (EVSYS_NSCHKUSER) User 17 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER17              EVSYS_NSCHKUSER_USER17_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER17_Msk instead */
#define EVSYS_NSCHKUSER_USER18_Pos          18                                             /**< (EVSYS_NSCHKUSER) User 18 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER18_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER18_Pos)       /**< (EVSYS_NSCHKUSER) User 18 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER18              EVSYS_NSCHKUSER_USER18_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER18_Msk instead */
#define EVSYS_NSCHKUSER_USER19_Pos          19                                             /**< (EVSYS_NSCHKUSER) User 19 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER19_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER19_Pos)       /**< (EVSYS_NSCHKUSER) User 19 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER19              EVSYS_NSCHKUSER_USER19_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER19_Msk instead */
#define EVSYS_NSCHKUSER_USER20_Pos          20                                             /**< (EVSYS_NSCHKUSER) User 20 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER20_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER20_Pos)       /**< (EVSYS_NSCHKUSER) User 20 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER20              EVSYS_NSCHKUSER_USER20_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER20_Msk instead */
#define EVSYS_NSCHKUSER_USER21_Pos          21                                             /**< (EVSYS_NSCHKUSER) User 21 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER21_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER21_Pos)       /**< (EVSYS_NSCHKUSER) User 21 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER21              EVSYS_NSCHKUSER_USER21_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER21_Msk instead */
#define EVSYS_NSCHKUSER_USER22_Pos          22                                             /**< (EVSYS_NSCHKUSER) User 22 to be checked as non-secured Position */
#define EVSYS_NSCHKUSER_USER22_Msk          (_U_(0x1) << EVSYS_NSCHKUSER_USER22_Pos)       /**< (EVSYS_NSCHKUSER) User 22 to be checked as non-secured Mask */
#define EVSYS_NSCHKUSER_USER22              EVSYS_NSCHKUSER_USER22_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use EVSYS_NSCHKUSER_USER22_Msk instead */
#define EVSYS_NSCHKUSER_MASK                _U_(0x7FFFFF)                                  /**< \deprecated (EVSYS_NSCHKUSER) Register MASK  (Use EVSYS_NSCHKUSER_Msk instead)  */
#define EVSYS_NSCHKUSER_Msk                 _U_(0x7FFFFF)                                  /**< (EVSYS_NSCHKUSER) Register Mask  */

#define EVSYS_NSCHKUSER_USER_Pos            0                                              /**< (EVSYS_NSCHKUSER Position) User 22 to be checked as non-secured */
#define EVSYS_NSCHKUSER_USER_Msk            (_U_(0x7FFFFF) << EVSYS_NSCHKUSER_USER_Pos)    /**< (EVSYS_NSCHKUSER Mask) USER */
#define EVSYS_NSCHKUSER_USER(value)         (EVSYS_NSCHKUSER_USER_Msk & ((value) << EVSYS_NSCHKUSER_USER_Pos))  

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief CHANNEL hardware registers */
typedef struct {  
  __IO EVSYS_CHANNEL_Type             CHANNEL;        /**< Offset: 0x00 (R/W  32) Channel n Control */
  __IO EVSYS_CHINTENCLR_Type          CHINTENCLR;     /**< Offset: 0x04 (R/W   8) Channel n Interrupt Enable Clear */
  __IO EVSYS_CHINTENSET_Type          CHINTENSET;     /**< Offset: 0x05 (R/W   8) Channel n Interrupt Enable Set */
  __IO EVSYS_CHINTFLAG_Type           CHINTFLAG;      /**< Offset: 0x06 (R/W   8) Channel n Interrupt Flag Status and Clear */
  __I  EVSYS_CHSTATUS_Type            CHSTATUS;       /**< Offset: 0x07 (R/    8) Channel n Status */
} EvsysChannel;

/** \brief EVSYS hardware registers */
typedef struct {  /* Event System Interface */
  __O  EVSYS_CTRLA_Type               CTRLA;          /**< Offset: 0x00 ( /W   8) Control */
  __I  uint8_t                        Reserved1[3];
  __O  EVSYS_SWEVT_Type               SWEVT;          /**< Offset: 0x04 ( /W  32) Software Event */
  __IO EVSYS_PRICTRL_Type             PRICTRL;        /**< Offset: 0x08 (R/W   8) Priority Control */
  __I  uint8_t                        Reserved2[7];
  __IO EVSYS_INTPEND_Type             INTPEND;        /**< Offset: 0x10 (R/W  16) Channel Pending Interrupt */
  __I  uint8_t                        Reserved3[2];
  __I  EVSYS_INTSTATUS_Type           INTSTATUS;      /**< Offset: 0x14 (R/   32) Interrupt Status */
  __I  EVSYS_BUSYCH_Type              BUSYCH;         /**< Offset: 0x18 (R/   32) Busy Channels */
  __I  EVSYS_READYUSR_Type            READYUSR;       /**< Offset: 0x1C (R/   32) Ready Users */
       EvsysChannel                   Channel[8];     /**< Offset: 0x20  */
  __I  uint8_t                        Reserved4[192];
  __IO EVSYS_USER_Type                USER[23];       /**< Offset: 0x120 (R/W   8) User Multiplexer n */
  __I  uint8_t                        Reserved5[157];
  __IO EVSYS_INTENCLR_Type            INTENCLR;       /**< Offset: 0x1D4 (R/W   8) Interrupt Enable Clear */
  __IO EVSYS_INTENSET_Type            INTENSET;       /**< Offset: 0x1D5 (R/W   8) Interrupt Enable Set */
  __IO EVSYS_INTFLAG_Type             INTFLAG;        /**< Offset: 0x1D6 (R/W   8) Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved6[1];
  __IO EVSYS_NONSECCHAN_Type          NONSECCHAN;     /**< Offset: 0x1D8 (R/W  32) Channels Security Attribution */
  __IO EVSYS_NSCHKCHAN_Type           NSCHKCHAN;      /**< Offset: 0x1DC (R/W  32) Non-Secure Channels Check */
  __IO EVSYS_NONSECUSER_Type          NONSECUSER[1];  /**< Offset: 0x1E0 (R/W  32) Users Security Attribution */
  __I  uint8_t                        Reserved7[12];
  __IO EVSYS_NSCHKUSER_Type           NSCHKUSER[1];   /**< Offset: 0x1F0 (R/W  32) Non-Secure Users Check */
} Evsys;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Event System Interface */

#endif /* _SAML10_EVSYS_COMPONENT_H_ */
