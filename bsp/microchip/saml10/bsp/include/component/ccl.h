/**
 * \file
 *
 * \brief Component description for CCL
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
#ifndef _SAML10_CCL_COMPONENT_H_
#define _SAML10_CCL_COMPONENT_H_
#define _SAML10_CCL_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Configurable Custom Logic
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR CCL */
/* ========================================================================== */

#define CCL_U2225                      /**< (CCL) Module ID */
#define REV_CCL 0x200                  /**< (CCL) Module revision */

/* -------- CCL_CTRL : (CCL Offset: 0x00) (R/W 8) Control -------- */
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
} CCL_CTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define CCL_CTRL_OFFSET                     (0x00)                                        /**<  (CCL_CTRL) Control  Offset */
#define CCL_CTRL_RESETVALUE                 _U_(0x00)                                     /**<  (CCL_CTRL) Control  Reset Value */

#define CCL_CTRL_SWRST_Pos                  0                                              /**< (CCL_CTRL) Software Reset Position */
#define CCL_CTRL_SWRST_Msk                  (_U_(0x1) << CCL_CTRL_SWRST_Pos)               /**< (CCL_CTRL) Software Reset Mask */
#define CCL_CTRL_SWRST                      CCL_CTRL_SWRST_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_CTRL_SWRST_Msk instead */
#define CCL_CTRL_ENABLE_Pos                 1                                              /**< (CCL_CTRL) Enable Position */
#define CCL_CTRL_ENABLE_Msk                 (_U_(0x1) << CCL_CTRL_ENABLE_Pos)              /**< (CCL_CTRL) Enable Mask */
#define CCL_CTRL_ENABLE                     CCL_CTRL_ENABLE_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_CTRL_ENABLE_Msk instead */
#define CCL_CTRL_RUNSTDBY_Pos               6                                              /**< (CCL_CTRL) Run in Standby Position */
#define CCL_CTRL_RUNSTDBY_Msk               (_U_(0x1) << CCL_CTRL_RUNSTDBY_Pos)            /**< (CCL_CTRL) Run in Standby Mask */
#define CCL_CTRL_RUNSTDBY                   CCL_CTRL_RUNSTDBY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_CTRL_RUNSTDBY_Msk instead */
#define CCL_CTRL_MASK                       _U_(0x43)                                      /**< \deprecated (CCL_CTRL) Register MASK  (Use CCL_CTRL_Msk instead)  */
#define CCL_CTRL_Msk                        _U_(0x43)                                      /**< (CCL_CTRL) Register Mask  */


/* -------- CCL_SEQCTRL : (CCL Offset: 0x04) (R/W 8) SEQ Control x -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SEQSEL:4;                  /**< bit:   0..3  Sequential Selection                     */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} CCL_SEQCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define CCL_SEQCTRL_OFFSET                  (0x04)                                        /**<  (CCL_SEQCTRL) SEQ Control x  Offset */
#define CCL_SEQCTRL_RESETVALUE              _U_(0x00)                                     /**<  (CCL_SEQCTRL) SEQ Control x  Reset Value */

#define CCL_SEQCTRL_SEQSEL_Pos              0                                              /**< (CCL_SEQCTRL) Sequential Selection Position */
#define CCL_SEQCTRL_SEQSEL_Msk              (_U_(0xF) << CCL_SEQCTRL_SEQSEL_Pos)           /**< (CCL_SEQCTRL) Sequential Selection Mask */
#define CCL_SEQCTRL_SEQSEL(value)           (CCL_SEQCTRL_SEQSEL_Msk & ((value) << CCL_SEQCTRL_SEQSEL_Pos))
#define   CCL_SEQCTRL_SEQSEL_DISABLE_Val    _U_(0x0)                                       /**< (CCL_SEQCTRL) Sequential logic is disabled  */
#define   CCL_SEQCTRL_SEQSEL_DFF_Val        _U_(0x1)                                       /**< (CCL_SEQCTRL) D flip flop  */
#define   CCL_SEQCTRL_SEQSEL_JK_Val         _U_(0x2)                                       /**< (CCL_SEQCTRL) JK flip flop  */
#define   CCL_SEQCTRL_SEQSEL_LATCH_Val      _U_(0x3)                                       /**< (CCL_SEQCTRL) D latch  */
#define   CCL_SEQCTRL_SEQSEL_RS_Val         _U_(0x4)                                       /**< (CCL_SEQCTRL) RS latch  */
#define CCL_SEQCTRL_SEQSEL_DISABLE          (CCL_SEQCTRL_SEQSEL_DISABLE_Val << CCL_SEQCTRL_SEQSEL_Pos)  /**< (CCL_SEQCTRL) Sequential logic is disabled Position  */
#define CCL_SEQCTRL_SEQSEL_DFF              (CCL_SEQCTRL_SEQSEL_DFF_Val << CCL_SEQCTRL_SEQSEL_Pos)  /**< (CCL_SEQCTRL) D flip flop Position  */
#define CCL_SEQCTRL_SEQSEL_JK               (CCL_SEQCTRL_SEQSEL_JK_Val << CCL_SEQCTRL_SEQSEL_Pos)  /**< (CCL_SEQCTRL) JK flip flop Position  */
#define CCL_SEQCTRL_SEQSEL_LATCH            (CCL_SEQCTRL_SEQSEL_LATCH_Val << CCL_SEQCTRL_SEQSEL_Pos)  /**< (CCL_SEQCTRL) D latch Position  */
#define CCL_SEQCTRL_SEQSEL_RS               (CCL_SEQCTRL_SEQSEL_RS_Val << CCL_SEQCTRL_SEQSEL_Pos)  /**< (CCL_SEQCTRL) RS latch Position  */
#define CCL_SEQCTRL_MASK                    _U_(0x0F)                                      /**< \deprecated (CCL_SEQCTRL) Register MASK  (Use CCL_SEQCTRL_Msk instead)  */
#define CCL_SEQCTRL_Msk                     _U_(0x0F)                                      /**< (CCL_SEQCTRL) Register Mask  */


/* -------- CCL_LUTCTRL : (CCL Offset: 0x08) (R/W 32) LUT Control x -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t ENABLE:1;                  /**< bit:      1  LUT Enable                               */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t FILTSEL:2;                 /**< bit:   4..5  Filter Selection                         */
    uint32_t :1;                        /**< bit:      6  Reserved */
    uint32_t EDGESEL:1;                 /**< bit:      7  Edge Selection                           */
    uint32_t INSEL0:4;                  /**< bit:  8..11  Input Selection 0                        */
    uint32_t INSEL1:4;                  /**< bit: 12..15  Input Selection 1                        */
    uint32_t INSEL2:4;                  /**< bit: 16..19  Input Selection 2                        */
    uint32_t INVEI:1;                   /**< bit:     20  Inverted Event Input Enable              */
    uint32_t LUTEI:1;                   /**< bit:     21  LUT Event Input Enable                   */
    uint32_t LUTEO:1;                   /**< bit:     22  LUT Event Output Enable                  */
    uint32_t :1;                        /**< bit:     23  Reserved */
    uint32_t TRUTH:8;                   /**< bit: 24..31  Truth Value                              */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} CCL_LUTCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define CCL_LUTCTRL_OFFSET                  (0x08)                                        /**<  (CCL_LUTCTRL) LUT Control x  Offset */
#define CCL_LUTCTRL_RESETVALUE              _U_(0x00)                                     /**<  (CCL_LUTCTRL) LUT Control x  Reset Value */

#define CCL_LUTCTRL_ENABLE_Pos              1                                              /**< (CCL_LUTCTRL) LUT Enable Position */
#define CCL_LUTCTRL_ENABLE_Msk              (_U_(0x1) << CCL_LUTCTRL_ENABLE_Pos)           /**< (CCL_LUTCTRL) LUT Enable Mask */
#define CCL_LUTCTRL_ENABLE                  CCL_LUTCTRL_ENABLE_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_LUTCTRL_ENABLE_Msk instead */
#define CCL_LUTCTRL_FILTSEL_Pos             4                                              /**< (CCL_LUTCTRL) Filter Selection Position */
#define CCL_LUTCTRL_FILTSEL_Msk             (_U_(0x3) << CCL_LUTCTRL_FILTSEL_Pos)          /**< (CCL_LUTCTRL) Filter Selection Mask */
#define CCL_LUTCTRL_FILTSEL(value)          (CCL_LUTCTRL_FILTSEL_Msk & ((value) << CCL_LUTCTRL_FILTSEL_Pos))
#define   CCL_LUTCTRL_FILTSEL_DISABLE_Val   _U_(0x0)                                       /**< (CCL_LUTCTRL) Filter disabled  */
#define   CCL_LUTCTRL_FILTSEL_SYNCH_Val     _U_(0x1)                                       /**< (CCL_LUTCTRL) Synchronizer enabled  */
#define   CCL_LUTCTRL_FILTSEL_FILTER_Val    _U_(0x2)                                       /**< (CCL_LUTCTRL) Filter enabled  */
#define CCL_LUTCTRL_FILTSEL_DISABLE         (CCL_LUTCTRL_FILTSEL_DISABLE_Val << CCL_LUTCTRL_FILTSEL_Pos)  /**< (CCL_LUTCTRL) Filter disabled Position  */
#define CCL_LUTCTRL_FILTSEL_SYNCH           (CCL_LUTCTRL_FILTSEL_SYNCH_Val << CCL_LUTCTRL_FILTSEL_Pos)  /**< (CCL_LUTCTRL) Synchronizer enabled Position  */
#define CCL_LUTCTRL_FILTSEL_FILTER          (CCL_LUTCTRL_FILTSEL_FILTER_Val << CCL_LUTCTRL_FILTSEL_Pos)  /**< (CCL_LUTCTRL) Filter enabled Position  */
#define CCL_LUTCTRL_EDGESEL_Pos             7                                              /**< (CCL_LUTCTRL) Edge Selection Position */
#define CCL_LUTCTRL_EDGESEL_Msk             (_U_(0x1) << CCL_LUTCTRL_EDGESEL_Pos)          /**< (CCL_LUTCTRL) Edge Selection Mask */
#define CCL_LUTCTRL_EDGESEL                 CCL_LUTCTRL_EDGESEL_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_LUTCTRL_EDGESEL_Msk instead */
#define CCL_LUTCTRL_INSEL0_Pos              8                                              /**< (CCL_LUTCTRL) Input Selection 0 Position */
#define CCL_LUTCTRL_INSEL0_Msk              (_U_(0xF) << CCL_LUTCTRL_INSEL0_Pos)           /**< (CCL_LUTCTRL) Input Selection 0 Mask */
#define CCL_LUTCTRL_INSEL0(value)           (CCL_LUTCTRL_INSEL0_Msk & ((value) << CCL_LUTCTRL_INSEL0_Pos))
#define   CCL_LUTCTRL_INSEL0_MASK_Val       _U_(0x0)                                       /**< (CCL_LUTCTRL) Masked input  */
#define   CCL_LUTCTRL_INSEL0_FEEDBACK_Val   _U_(0x1)                                       /**< (CCL_LUTCTRL) Feedback input source  */
#define   CCL_LUTCTRL_INSEL0_LINK_Val       _U_(0x2)                                       /**< (CCL_LUTCTRL) Linked LUT input source  */
#define   CCL_LUTCTRL_INSEL0_EVENT_Val      _U_(0x3)                                       /**< (CCL_LUTCTRL) Event input source  */
#define   CCL_LUTCTRL_INSEL0_IO_Val         _U_(0x4)                                       /**< (CCL_LUTCTRL) I/O pin input source  */
#define   CCL_LUTCTRL_INSEL0_AC_Val         _U_(0x5)                                       /**< (CCL_LUTCTRL) AC input source  */
#define   CCL_LUTCTRL_INSEL0_TC_Val         _U_(0x6)                                       /**< (CCL_LUTCTRL) TC input source  */
#define   CCL_LUTCTRL_INSEL0_ALTTC_Val      _U_(0x7)                                       /**< (CCL_LUTCTRL) Alternate TC input source  */
#define   CCL_LUTCTRL_INSEL0_TCC_Val        _U_(0x8)                                       /**< (CCL_LUTCTRL) TCC input source  */
#define   CCL_LUTCTRL_INSEL0_SERCOM_Val     _U_(0x9)                                       /**< (CCL_LUTCTRL) SERCOM input source  */
#define   CCL_LUTCTRL_INSEL0_ALT2TC_Val     _U_(0xA)                                       /**< (CCL_LUTCTRL) Alternate 2 TC input source  */
#define   CCL_LUTCTRL_INSEL0_ASYNCEVENT_Val _U_(0xB)                                       /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic.  */
#define CCL_LUTCTRL_INSEL0_MASK             (CCL_LUTCTRL_INSEL0_MASK_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Masked input Position  */
#define CCL_LUTCTRL_INSEL0_FEEDBACK         (CCL_LUTCTRL_INSEL0_FEEDBACK_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Feedback input source Position  */
#define CCL_LUTCTRL_INSEL0_LINK             (CCL_LUTCTRL_INSEL0_LINK_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Linked LUT input source Position  */
#define CCL_LUTCTRL_INSEL0_EVENT            (CCL_LUTCTRL_INSEL0_EVENT_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Event input source Position  */
#define CCL_LUTCTRL_INSEL0_IO               (CCL_LUTCTRL_INSEL0_IO_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) I/O pin input source Position  */
#define CCL_LUTCTRL_INSEL0_AC               (CCL_LUTCTRL_INSEL0_AC_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) AC input source Position  */
#define CCL_LUTCTRL_INSEL0_TC               (CCL_LUTCTRL_INSEL0_TC_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) TC input source Position  */
#define CCL_LUTCTRL_INSEL0_ALTTC            (CCL_LUTCTRL_INSEL0_ALTTC_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Alternate TC input source Position  */
#define CCL_LUTCTRL_INSEL0_TCC              (CCL_LUTCTRL_INSEL0_TCC_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) TCC input source Position  */
#define CCL_LUTCTRL_INSEL0_SERCOM           (CCL_LUTCTRL_INSEL0_SERCOM_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) SERCOM input source Position  */
#define CCL_LUTCTRL_INSEL0_ALT2TC           (CCL_LUTCTRL_INSEL0_ALT2TC_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Alternate 2 TC input source Position  */
#define CCL_LUTCTRL_INSEL0_ASYNCEVENT       (CCL_LUTCTRL_INSEL0_ASYNCEVENT_Val << CCL_LUTCTRL_INSEL0_Pos)  /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic. Position  */
#define CCL_LUTCTRL_INSEL1_Pos              12                                             /**< (CCL_LUTCTRL) Input Selection 1 Position */
#define CCL_LUTCTRL_INSEL1_Msk              (_U_(0xF) << CCL_LUTCTRL_INSEL1_Pos)           /**< (CCL_LUTCTRL) Input Selection 1 Mask */
#define CCL_LUTCTRL_INSEL1(value)           (CCL_LUTCTRL_INSEL1_Msk & ((value) << CCL_LUTCTRL_INSEL1_Pos))
#define   CCL_LUTCTRL_INSEL1_MASK_Val       _U_(0x0)                                       /**< (CCL_LUTCTRL) Masked input  */
#define   CCL_LUTCTRL_INSEL1_FEEDBACK_Val   _U_(0x1)                                       /**< (CCL_LUTCTRL) Feedback input source  */
#define   CCL_LUTCTRL_INSEL1_LINK_Val       _U_(0x2)                                       /**< (CCL_LUTCTRL) Linked LUT input source  */
#define   CCL_LUTCTRL_INSEL1_EVENT_Val      _U_(0x3)                                       /**< (CCL_LUTCTRL) Event input source  */
#define   CCL_LUTCTRL_INSEL1_IO_Val         _U_(0x4)                                       /**< (CCL_LUTCTRL) I/O pin input source  */
#define   CCL_LUTCTRL_INSEL1_AC_Val         _U_(0x5)                                       /**< (CCL_LUTCTRL) AC input source  */
#define   CCL_LUTCTRL_INSEL1_TC_Val         _U_(0x6)                                       /**< (CCL_LUTCTRL) TC input source  */
#define   CCL_LUTCTRL_INSEL1_ALTTC_Val      _U_(0x7)                                       /**< (CCL_LUTCTRL) Alternate TC input source  */
#define   CCL_LUTCTRL_INSEL1_TCC_Val        _U_(0x8)                                       /**< (CCL_LUTCTRL) TCC input source  */
#define   CCL_LUTCTRL_INSEL1_SERCOM_Val     _U_(0x9)                                       /**< (CCL_LUTCTRL) SERCOM input source  */
#define   CCL_LUTCTRL_INSEL1_ALT2TC_Val     _U_(0xA)                                       /**< (CCL_LUTCTRL) Alternate 2 TC input source  */
#define   CCL_LUTCTRL_INSEL1_ASYNCEVENT_Val _U_(0xB)                                       /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic.  */
#define CCL_LUTCTRL_INSEL1_MASK             (CCL_LUTCTRL_INSEL1_MASK_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Masked input Position  */
#define CCL_LUTCTRL_INSEL1_FEEDBACK         (CCL_LUTCTRL_INSEL1_FEEDBACK_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Feedback input source Position  */
#define CCL_LUTCTRL_INSEL1_LINK             (CCL_LUTCTRL_INSEL1_LINK_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Linked LUT input source Position  */
#define CCL_LUTCTRL_INSEL1_EVENT            (CCL_LUTCTRL_INSEL1_EVENT_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Event input source Position  */
#define CCL_LUTCTRL_INSEL1_IO               (CCL_LUTCTRL_INSEL1_IO_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) I/O pin input source Position  */
#define CCL_LUTCTRL_INSEL1_AC               (CCL_LUTCTRL_INSEL1_AC_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) AC input source Position  */
#define CCL_LUTCTRL_INSEL1_TC               (CCL_LUTCTRL_INSEL1_TC_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) TC input source Position  */
#define CCL_LUTCTRL_INSEL1_ALTTC            (CCL_LUTCTRL_INSEL1_ALTTC_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Alternate TC input source Position  */
#define CCL_LUTCTRL_INSEL1_TCC              (CCL_LUTCTRL_INSEL1_TCC_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) TCC input source Position  */
#define CCL_LUTCTRL_INSEL1_SERCOM           (CCL_LUTCTRL_INSEL1_SERCOM_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) SERCOM input source Position  */
#define CCL_LUTCTRL_INSEL1_ALT2TC           (CCL_LUTCTRL_INSEL1_ALT2TC_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Alternate 2 TC input source Position  */
#define CCL_LUTCTRL_INSEL1_ASYNCEVENT       (CCL_LUTCTRL_INSEL1_ASYNCEVENT_Val << CCL_LUTCTRL_INSEL1_Pos)  /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic. Position  */
#define CCL_LUTCTRL_INSEL2_Pos              16                                             /**< (CCL_LUTCTRL) Input Selection 2 Position */
#define CCL_LUTCTRL_INSEL2_Msk              (_U_(0xF) << CCL_LUTCTRL_INSEL2_Pos)           /**< (CCL_LUTCTRL) Input Selection 2 Mask */
#define CCL_LUTCTRL_INSEL2(value)           (CCL_LUTCTRL_INSEL2_Msk & ((value) << CCL_LUTCTRL_INSEL2_Pos))
#define   CCL_LUTCTRL_INSEL2_MASK_Val       _U_(0x0)                                       /**< (CCL_LUTCTRL) Masked input  */
#define   CCL_LUTCTRL_INSEL2_FEEDBACK_Val   _U_(0x1)                                       /**< (CCL_LUTCTRL) Feedback input source  */
#define   CCL_LUTCTRL_INSEL2_LINK_Val       _U_(0x2)                                       /**< (CCL_LUTCTRL) Linked LUT input source  */
#define   CCL_LUTCTRL_INSEL2_EVENT_Val      _U_(0x3)                                       /**< (CCL_LUTCTRL) Event input source  */
#define   CCL_LUTCTRL_INSEL2_IO_Val         _U_(0x4)                                       /**< (CCL_LUTCTRL) I/O pin input source  */
#define   CCL_LUTCTRL_INSEL2_AC_Val         _U_(0x5)                                       /**< (CCL_LUTCTRL) AC input source  */
#define   CCL_LUTCTRL_INSEL2_TC_Val         _U_(0x6)                                       /**< (CCL_LUTCTRL) TC input source  */
#define   CCL_LUTCTRL_INSEL2_ALTTC_Val      _U_(0x7)                                       /**< (CCL_LUTCTRL) Alternate TC input source  */
#define   CCL_LUTCTRL_INSEL2_TCC_Val        _U_(0x8)                                       /**< (CCL_LUTCTRL) TCC input source  */
#define   CCL_LUTCTRL_INSEL2_SERCOM_Val     _U_(0x9)                                       /**< (CCL_LUTCTRL) SERCOM input source  */
#define   CCL_LUTCTRL_INSEL2_ALT2TC_Val     _U_(0xA)                                       /**< (CCL_LUTCTRL) Alternate 2 TC input source  */
#define   CCL_LUTCTRL_INSEL2_ASYNCEVENT_Val _U_(0xB)                                       /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic.  */
#define CCL_LUTCTRL_INSEL2_MASK             (CCL_LUTCTRL_INSEL2_MASK_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Masked input Position  */
#define CCL_LUTCTRL_INSEL2_FEEDBACK         (CCL_LUTCTRL_INSEL2_FEEDBACK_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Feedback input source Position  */
#define CCL_LUTCTRL_INSEL2_LINK             (CCL_LUTCTRL_INSEL2_LINK_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Linked LUT input source Position  */
#define CCL_LUTCTRL_INSEL2_EVENT            (CCL_LUTCTRL_INSEL2_EVENT_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Event input source Position  */
#define CCL_LUTCTRL_INSEL2_IO               (CCL_LUTCTRL_INSEL2_IO_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) I/O pin input source Position  */
#define CCL_LUTCTRL_INSEL2_AC               (CCL_LUTCTRL_INSEL2_AC_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) AC input source Position  */
#define CCL_LUTCTRL_INSEL2_TC               (CCL_LUTCTRL_INSEL2_TC_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) TC input source Position  */
#define CCL_LUTCTRL_INSEL2_ALTTC            (CCL_LUTCTRL_INSEL2_ALTTC_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Alternate TC input source Position  */
#define CCL_LUTCTRL_INSEL2_TCC              (CCL_LUTCTRL_INSEL2_TCC_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) TCC input source Position  */
#define CCL_LUTCTRL_INSEL2_SERCOM           (CCL_LUTCTRL_INSEL2_SERCOM_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) SERCOM input source Position  */
#define CCL_LUTCTRL_INSEL2_ALT2TC           (CCL_LUTCTRL_INSEL2_ALT2TC_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Alternate 2 TC input source Position  */
#define CCL_LUTCTRL_INSEL2_ASYNCEVENT       (CCL_LUTCTRL_INSEL2_ASYNCEVENT_Val << CCL_LUTCTRL_INSEL2_Pos)  /**< (CCL_LUTCTRL) Asynchronous event input source. The EVENT input will bypass edge detection logic. Position  */
#define CCL_LUTCTRL_INVEI_Pos               20                                             /**< (CCL_LUTCTRL) Inverted Event Input Enable Position */
#define CCL_LUTCTRL_INVEI_Msk               (_U_(0x1) << CCL_LUTCTRL_INVEI_Pos)            /**< (CCL_LUTCTRL) Inverted Event Input Enable Mask */
#define CCL_LUTCTRL_INVEI                   CCL_LUTCTRL_INVEI_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_LUTCTRL_INVEI_Msk instead */
#define CCL_LUTCTRL_LUTEI_Pos               21                                             /**< (CCL_LUTCTRL) LUT Event Input Enable Position */
#define CCL_LUTCTRL_LUTEI_Msk               (_U_(0x1) << CCL_LUTCTRL_LUTEI_Pos)            /**< (CCL_LUTCTRL) LUT Event Input Enable Mask */
#define CCL_LUTCTRL_LUTEI                   CCL_LUTCTRL_LUTEI_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_LUTCTRL_LUTEI_Msk instead */
#define CCL_LUTCTRL_LUTEO_Pos               22                                             /**< (CCL_LUTCTRL) LUT Event Output Enable Position */
#define CCL_LUTCTRL_LUTEO_Msk               (_U_(0x1) << CCL_LUTCTRL_LUTEO_Pos)            /**< (CCL_LUTCTRL) LUT Event Output Enable Mask */
#define CCL_LUTCTRL_LUTEO                   CCL_LUTCTRL_LUTEO_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use CCL_LUTCTRL_LUTEO_Msk instead */
#define CCL_LUTCTRL_TRUTH_Pos               24                                             /**< (CCL_LUTCTRL) Truth Value Position */
#define CCL_LUTCTRL_TRUTH_Msk               (_U_(0xFF) << CCL_LUTCTRL_TRUTH_Pos)           /**< (CCL_LUTCTRL) Truth Value Mask */
#define CCL_LUTCTRL_TRUTH(value)            (CCL_LUTCTRL_TRUTH_Msk & ((value) << CCL_LUTCTRL_TRUTH_Pos))
#define CCL_LUTCTRL_MASK                    _U_(0xFF7FFFB2)                                /**< \deprecated (CCL_LUTCTRL) Register MASK  (Use CCL_LUTCTRL_Msk instead)  */
#define CCL_LUTCTRL_Msk                     _U_(0xFF7FFFB2)                                /**< (CCL_LUTCTRL) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief CCL hardware registers */
typedef struct {  /* Configurable Custom Logic */
  __IO CCL_CTRL_Type                  CTRL;           /**< Offset: 0x00 (R/W   8) Control */
  __I  uint8_t                        Reserved1[3];
  __IO CCL_SEQCTRL_Type               SEQCTRL[1];     /**< Offset: 0x04 (R/W   8) SEQ Control x */
  __I  uint8_t                        Reserved2[3];
  __IO CCL_LUTCTRL_Type               LUTCTRL[2];     /**< Offset: 0x08 (R/W  32) LUT Control x */
} Ccl;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Configurable Custom Logic */

#endif /* _SAML10_CCL_COMPONENT_H_ */
