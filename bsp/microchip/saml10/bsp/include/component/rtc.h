/**
 * \file
 *
 * \brief Component description for RTC
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
#ifndef _SAML10_RTC_COMPONENT_H_
#define _SAML10_RTC_COMPONENT_H_
#define _SAML10_RTC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Real-Time Counter
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR RTC */
/* ========================================================================== */

#define RTC_U2250                      /**< (RTC) Module ID */
#define REV_RTC 0x300                  /**< (RTC) Module revision */

/* -------- RTC_MODE2_ALARM : (RTC Offset: 0x00) (R/W 32) MODE2_ALARM Alarm n Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SECOND:6;                  /**< bit:   0..5  Second                                   */
    uint32_t MINUTE:6;                  /**< bit:  6..11  Minute                                   */
    uint32_t HOUR:5;                    /**< bit: 12..16  Hour                                     */
    uint32_t DAY:5;                     /**< bit: 17..21  Day                                      */
    uint32_t MONTH:4;                   /**< bit: 22..25  Month                                    */
    uint32_t YEAR:6;                    /**< bit: 26..31  Year                                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE2_ALARM_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_ALARM_OFFSET              (0x00)                                        /**<  (RTC_MODE2_ALARM) MODE2_ALARM Alarm n Value  Offset */
#define RTC_MODE2_ALARM_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE2_ALARM) MODE2_ALARM Alarm n Value  Reset Value */

#define RTC_MODE2_ALARM_SECOND_Pos          0                                              /**< (RTC_MODE2_ALARM) Second Position */
#define RTC_MODE2_ALARM_SECOND_Msk          (_U_(0x3F) << RTC_MODE2_ALARM_SECOND_Pos)      /**< (RTC_MODE2_ALARM) Second Mask */
#define RTC_MODE2_ALARM_SECOND(value)       (RTC_MODE2_ALARM_SECOND_Msk & ((value) << RTC_MODE2_ALARM_SECOND_Pos))
#define RTC_MODE2_ALARM_MINUTE_Pos          6                                              /**< (RTC_MODE2_ALARM) Minute Position */
#define RTC_MODE2_ALARM_MINUTE_Msk          (_U_(0x3F) << RTC_MODE2_ALARM_MINUTE_Pos)      /**< (RTC_MODE2_ALARM) Minute Mask */
#define RTC_MODE2_ALARM_MINUTE(value)       (RTC_MODE2_ALARM_MINUTE_Msk & ((value) << RTC_MODE2_ALARM_MINUTE_Pos))
#define RTC_MODE2_ALARM_HOUR_Pos            12                                             /**< (RTC_MODE2_ALARM) Hour Position */
#define RTC_MODE2_ALARM_HOUR_Msk            (_U_(0x1F) << RTC_MODE2_ALARM_HOUR_Pos)        /**< (RTC_MODE2_ALARM) Hour Mask */
#define RTC_MODE2_ALARM_HOUR(value)         (RTC_MODE2_ALARM_HOUR_Msk & ((value) << RTC_MODE2_ALARM_HOUR_Pos))
#define   RTC_MODE2_ALARM_HOUR_AM_Val       _U_(0x0)                                       /**< (RTC_MODE2_ALARM) Morning hour  */
#define   RTC_MODE2_ALARM_HOUR_PM_Val       _U_(0x10)                                      /**< (RTC_MODE2_ALARM) Afternoon hour  */
#define RTC_MODE2_ALARM_HOUR_AM             (RTC_MODE2_ALARM_HOUR_AM_Val << RTC_MODE2_ALARM_HOUR_Pos)  /**< (RTC_MODE2_ALARM) Morning hour Position  */
#define RTC_MODE2_ALARM_HOUR_PM             (RTC_MODE2_ALARM_HOUR_PM_Val << RTC_MODE2_ALARM_HOUR_Pos)  /**< (RTC_MODE2_ALARM) Afternoon hour Position  */
#define RTC_MODE2_ALARM_DAY_Pos             17                                             /**< (RTC_MODE2_ALARM) Day Position */
#define RTC_MODE2_ALARM_DAY_Msk             (_U_(0x1F) << RTC_MODE2_ALARM_DAY_Pos)         /**< (RTC_MODE2_ALARM) Day Mask */
#define RTC_MODE2_ALARM_DAY(value)          (RTC_MODE2_ALARM_DAY_Msk & ((value) << RTC_MODE2_ALARM_DAY_Pos))
#define RTC_MODE2_ALARM_MONTH_Pos           22                                             /**< (RTC_MODE2_ALARM) Month Position */
#define RTC_MODE2_ALARM_MONTH_Msk           (_U_(0xF) << RTC_MODE2_ALARM_MONTH_Pos)        /**< (RTC_MODE2_ALARM) Month Mask */
#define RTC_MODE2_ALARM_MONTH(value)        (RTC_MODE2_ALARM_MONTH_Msk & ((value) << RTC_MODE2_ALARM_MONTH_Pos))
#define RTC_MODE2_ALARM_YEAR_Pos            26                                             /**< (RTC_MODE2_ALARM) Year Position */
#define RTC_MODE2_ALARM_YEAR_Msk            (_U_(0x3F) << RTC_MODE2_ALARM_YEAR_Pos)        /**< (RTC_MODE2_ALARM) Year Mask */
#define RTC_MODE2_ALARM_YEAR(value)         (RTC_MODE2_ALARM_YEAR_Msk & ((value) << RTC_MODE2_ALARM_YEAR_Pos))
#define RTC_MODE2_ALARM_MASK                _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE2_ALARM) Register MASK  (Use RTC_MODE2_ALARM_Msk instead)  */
#define RTC_MODE2_ALARM_Msk                 _U_(0xFFFFFFFF)                                /**< (RTC_MODE2_ALARM) Register Mask  */


/* -------- RTC_MODE2_MASK : (RTC Offset: 0x04) (R/W 8) MODE2_ALARM Alarm n Mask -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SEL:3;                     /**< bit:   0..2  Alarm Mask Selection                     */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} RTC_MODE2_MASK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_MASK_OFFSET               (0x04)                                        /**<  (RTC_MODE2_MASK) MODE2_ALARM Alarm n Mask  Offset */
#define RTC_MODE2_MASK_RESETVALUE           _U_(0x00)                                     /**<  (RTC_MODE2_MASK) MODE2_ALARM Alarm n Mask  Reset Value */

#define RTC_MODE2_MASK_SEL_Pos              0                                              /**< (RTC_MODE2_MASK) Alarm Mask Selection Position */
#define RTC_MODE2_MASK_SEL_Msk              (_U_(0x7) << RTC_MODE2_MASK_SEL_Pos)           /**< (RTC_MODE2_MASK) Alarm Mask Selection Mask */
#define RTC_MODE2_MASK_SEL(value)           (RTC_MODE2_MASK_SEL_Msk & ((value) << RTC_MODE2_MASK_SEL_Pos))
#define   RTC_MODE2_MASK_SEL_OFF_Val        _U_(0x0)                                       /**< (RTC_MODE2_MASK) Alarm Disabled  */
#define   RTC_MODE2_MASK_SEL_SS_Val         _U_(0x1)                                       /**< (RTC_MODE2_MASK) Match seconds only  */
#define   RTC_MODE2_MASK_SEL_MMSS_Val       _U_(0x2)                                       /**< (RTC_MODE2_MASK) Match seconds and minutes only  */
#define   RTC_MODE2_MASK_SEL_HHMMSS_Val     _U_(0x3)                                       /**< (RTC_MODE2_MASK) Match seconds, minutes, and hours only  */
#define   RTC_MODE2_MASK_SEL_DDHHMMSS_Val   _U_(0x4)                                       /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, and days only  */
#define   RTC_MODE2_MASK_SEL_MMDDHHMMSS_Val _U_(0x5)                                       /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, days, and months only  */
#define   RTC_MODE2_MASK_SEL_YYMMDDHHMMSS_Val _U_(0x6)                                       /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, days, months, and years  */
#define RTC_MODE2_MASK_SEL_OFF              (RTC_MODE2_MASK_SEL_OFF_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Alarm Disabled Position  */
#define RTC_MODE2_MASK_SEL_SS               (RTC_MODE2_MASK_SEL_SS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds only Position  */
#define RTC_MODE2_MASK_SEL_MMSS             (RTC_MODE2_MASK_SEL_MMSS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds and minutes only Position  */
#define RTC_MODE2_MASK_SEL_HHMMSS           (RTC_MODE2_MASK_SEL_HHMMSS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds, minutes, and hours only Position  */
#define RTC_MODE2_MASK_SEL_DDHHMMSS         (RTC_MODE2_MASK_SEL_DDHHMMSS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, and days only Position  */
#define RTC_MODE2_MASK_SEL_MMDDHHMMSS       (RTC_MODE2_MASK_SEL_MMDDHHMMSS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, days, and months only Position  */
#define RTC_MODE2_MASK_SEL_YYMMDDHHMMSS     (RTC_MODE2_MASK_SEL_YYMMDDHHMMSS_Val << RTC_MODE2_MASK_SEL_Pos)  /**< (RTC_MODE2_MASK) Match seconds, minutes, hours, days, months, and years Position  */
#define RTC_MODE2_MASK_MASK                 _U_(0x07)                                      /**< \deprecated (RTC_MODE2_MASK) Register MASK  (Use RTC_MODE2_MASK_Msk instead)  */
#define RTC_MODE2_MASK_Msk                  _U_(0x07)                                      /**< (RTC_MODE2_MASK) Register Mask  */


/* -------- RTC_MODE0_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE0 Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint16_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint16_t MODE:2;                    /**< bit:   2..3  Operating Mode                           */
    uint16_t :3;                        /**< bit:   4..6  Reserved */
    uint16_t MATCHCLR:1;                /**< bit:      7  Clear on Match                           */
    uint16_t PRESCALER:4;               /**< bit:  8..11  Prescaler                                */
    uint16_t :2;                        /**< bit: 12..13  Reserved */
    uint16_t GPTRST:1;                  /**< bit:     14  GP Registers Reset On Tamper Enable      */
    uint16_t COUNTSYNC:1;               /**< bit:     15  Count Read Synchronization Enable        */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE0_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_CTRLA_OFFSET              (0x00)                                        /**<  (RTC_MODE0_CTRLA) MODE0 Control A  Offset */
#define RTC_MODE0_CTRLA_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE0_CTRLA) MODE0 Control A  Reset Value */

#define RTC_MODE0_CTRLA_SWRST_Pos           0                                              /**< (RTC_MODE0_CTRLA) Software Reset Position */
#define RTC_MODE0_CTRLA_SWRST_Msk           (_U_(0x1) << RTC_MODE0_CTRLA_SWRST_Pos)        /**< (RTC_MODE0_CTRLA) Software Reset Mask */
#define RTC_MODE0_CTRLA_SWRST               RTC_MODE0_CTRLA_SWRST_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLA_SWRST_Msk instead */
#define RTC_MODE0_CTRLA_ENABLE_Pos          1                                              /**< (RTC_MODE0_CTRLA) Enable Position */
#define RTC_MODE0_CTRLA_ENABLE_Msk          (_U_(0x1) << RTC_MODE0_CTRLA_ENABLE_Pos)       /**< (RTC_MODE0_CTRLA) Enable Mask */
#define RTC_MODE0_CTRLA_ENABLE              RTC_MODE0_CTRLA_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLA_ENABLE_Msk instead */
#define RTC_MODE0_CTRLA_MODE_Pos            2                                              /**< (RTC_MODE0_CTRLA) Operating Mode Position */
#define RTC_MODE0_CTRLA_MODE_Msk            (_U_(0x3) << RTC_MODE0_CTRLA_MODE_Pos)         /**< (RTC_MODE0_CTRLA) Operating Mode Mask */
#define RTC_MODE0_CTRLA_MODE(value)         (RTC_MODE0_CTRLA_MODE_Msk & ((value) << RTC_MODE0_CTRLA_MODE_Pos))
#define   RTC_MODE0_CTRLA_MODE_COUNT32_Val  _U_(0x0)                                       /**< (RTC_MODE0_CTRLA) Mode 0: 32-bit Counter  */
#define   RTC_MODE0_CTRLA_MODE_COUNT16_Val  _U_(0x1)                                       /**< (RTC_MODE0_CTRLA) Mode 1: 16-bit Counter  */
#define   RTC_MODE0_CTRLA_MODE_CLOCK_Val    _U_(0x2)                                       /**< (RTC_MODE0_CTRLA) Mode 2: Clock/Calendar  */
#define RTC_MODE0_CTRLA_MODE_COUNT32        (RTC_MODE0_CTRLA_MODE_COUNT32_Val << RTC_MODE0_CTRLA_MODE_Pos)  /**< (RTC_MODE0_CTRLA) Mode 0: 32-bit Counter Position  */
#define RTC_MODE0_CTRLA_MODE_COUNT16        (RTC_MODE0_CTRLA_MODE_COUNT16_Val << RTC_MODE0_CTRLA_MODE_Pos)  /**< (RTC_MODE0_CTRLA) Mode 1: 16-bit Counter Position  */
#define RTC_MODE0_CTRLA_MODE_CLOCK          (RTC_MODE0_CTRLA_MODE_CLOCK_Val << RTC_MODE0_CTRLA_MODE_Pos)  /**< (RTC_MODE0_CTRLA) Mode 2: Clock/Calendar Position  */
#define RTC_MODE0_CTRLA_MATCHCLR_Pos        7                                              /**< (RTC_MODE0_CTRLA) Clear on Match Position */
#define RTC_MODE0_CTRLA_MATCHCLR_Msk        (_U_(0x1) << RTC_MODE0_CTRLA_MATCHCLR_Pos)     /**< (RTC_MODE0_CTRLA) Clear on Match Mask */
#define RTC_MODE0_CTRLA_MATCHCLR            RTC_MODE0_CTRLA_MATCHCLR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLA_MATCHCLR_Msk instead */
#define RTC_MODE0_CTRLA_PRESCALER_Pos       8                                              /**< (RTC_MODE0_CTRLA) Prescaler Position */
#define RTC_MODE0_CTRLA_PRESCALER_Msk       (_U_(0xF) << RTC_MODE0_CTRLA_PRESCALER_Pos)    /**< (RTC_MODE0_CTRLA) Prescaler Mask */
#define RTC_MODE0_CTRLA_PRESCALER(value)    (RTC_MODE0_CTRLA_PRESCALER_Msk & ((value) << RTC_MODE0_CTRLA_PRESCALER_Pos))
#define   RTC_MODE0_CTRLA_PRESCALER_OFF_Val _U_(0x0)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV1_Val _U_(0x1)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV2_Val _U_(0x2)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/2  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV4_Val _U_(0x3)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/4  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV8_Val _U_(0x4)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/8  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV16_Val _U_(0x5)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/16  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV32_Val _U_(0x6)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/32  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV64_Val _U_(0x7)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/64  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV128_Val _U_(0x8)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/128  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV256_Val _U_(0x9)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/256  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV512_Val _U_(0xA)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/512  */
#define   RTC_MODE0_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)                                       /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024  */
#define RTC_MODE0_CTRLA_PRESCALER_OFF       (RTC_MODE0_CTRLA_PRESCALER_OFF_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV1      (RTC_MODE0_CTRLA_PRESCALER_DIV1_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV2      (RTC_MODE0_CTRLA_PRESCALER_DIV2_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/2 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV4      (RTC_MODE0_CTRLA_PRESCALER_DIV4_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/4 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV8      (RTC_MODE0_CTRLA_PRESCALER_DIV8_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/8 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV16     (RTC_MODE0_CTRLA_PRESCALER_DIV16_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/16 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV32     (RTC_MODE0_CTRLA_PRESCALER_DIV32_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/32 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV64     (RTC_MODE0_CTRLA_PRESCALER_DIV64_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/64 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV128    (RTC_MODE0_CTRLA_PRESCALER_DIV128_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/128 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV256    (RTC_MODE0_CTRLA_PRESCALER_DIV256_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/256 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV512    (RTC_MODE0_CTRLA_PRESCALER_DIV512_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/512 Position  */
#define RTC_MODE0_CTRLA_PRESCALER_DIV1024   (RTC_MODE0_CTRLA_PRESCALER_DIV1024_Val << RTC_MODE0_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE0_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024 Position  */
#define RTC_MODE0_CTRLA_GPTRST_Pos          14                                             /**< (RTC_MODE0_CTRLA) GP Registers Reset On Tamper Enable Position */
#define RTC_MODE0_CTRLA_GPTRST_Msk          (_U_(0x1) << RTC_MODE0_CTRLA_GPTRST_Pos)       /**< (RTC_MODE0_CTRLA) GP Registers Reset On Tamper Enable Mask */
#define RTC_MODE0_CTRLA_GPTRST              RTC_MODE0_CTRLA_GPTRST_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLA_GPTRST_Msk instead */
#define RTC_MODE0_CTRLA_COUNTSYNC_Pos       15                                             /**< (RTC_MODE0_CTRLA) Count Read Synchronization Enable Position */
#define RTC_MODE0_CTRLA_COUNTSYNC_Msk       (_U_(0x1) << RTC_MODE0_CTRLA_COUNTSYNC_Pos)    /**< (RTC_MODE0_CTRLA) Count Read Synchronization Enable Mask */
#define RTC_MODE0_CTRLA_COUNTSYNC           RTC_MODE0_CTRLA_COUNTSYNC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLA_COUNTSYNC_Msk instead */
#define RTC_MODE0_CTRLA_MASK                _U_(0xCF8F)                                    /**< \deprecated (RTC_MODE0_CTRLA) Register MASK  (Use RTC_MODE0_CTRLA_Msk instead)  */
#define RTC_MODE0_CTRLA_Msk                 _U_(0xCF8F)                                    /**< (RTC_MODE0_CTRLA) Register Mask  */


/* -------- RTC_MODE1_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE1 Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint16_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint16_t MODE:2;                    /**< bit:   2..3  Operating Mode                           */
    uint16_t :4;                        /**< bit:   4..7  Reserved */
    uint16_t PRESCALER:4;               /**< bit:  8..11  Prescaler                                */
    uint16_t :2;                        /**< bit: 12..13  Reserved */
    uint16_t GPTRST:1;                  /**< bit:     14  GP Registers Reset On Tamper Enable      */
    uint16_t COUNTSYNC:1;               /**< bit:     15  Count Read Synchronization Enable        */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_CTRLA_OFFSET              (0x00)                                        /**<  (RTC_MODE1_CTRLA) MODE1 Control A  Offset */
#define RTC_MODE1_CTRLA_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE1_CTRLA) MODE1 Control A  Reset Value */

#define RTC_MODE1_CTRLA_SWRST_Pos           0                                              /**< (RTC_MODE1_CTRLA) Software Reset Position */
#define RTC_MODE1_CTRLA_SWRST_Msk           (_U_(0x1) << RTC_MODE1_CTRLA_SWRST_Pos)        /**< (RTC_MODE1_CTRLA) Software Reset Mask */
#define RTC_MODE1_CTRLA_SWRST               RTC_MODE1_CTRLA_SWRST_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLA_SWRST_Msk instead */
#define RTC_MODE1_CTRLA_ENABLE_Pos          1                                              /**< (RTC_MODE1_CTRLA) Enable Position */
#define RTC_MODE1_CTRLA_ENABLE_Msk          (_U_(0x1) << RTC_MODE1_CTRLA_ENABLE_Pos)       /**< (RTC_MODE1_CTRLA) Enable Mask */
#define RTC_MODE1_CTRLA_ENABLE              RTC_MODE1_CTRLA_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLA_ENABLE_Msk instead */
#define RTC_MODE1_CTRLA_MODE_Pos            2                                              /**< (RTC_MODE1_CTRLA) Operating Mode Position */
#define RTC_MODE1_CTRLA_MODE_Msk            (_U_(0x3) << RTC_MODE1_CTRLA_MODE_Pos)         /**< (RTC_MODE1_CTRLA) Operating Mode Mask */
#define RTC_MODE1_CTRLA_MODE(value)         (RTC_MODE1_CTRLA_MODE_Msk & ((value) << RTC_MODE1_CTRLA_MODE_Pos))
#define   RTC_MODE1_CTRLA_MODE_COUNT32_Val  _U_(0x0)                                       /**< (RTC_MODE1_CTRLA) Mode 0: 32-bit Counter  */
#define   RTC_MODE1_CTRLA_MODE_COUNT16_Val  _U_(0x1)                                       /**< (RTC_MODE1_CTRLA) Mode 1: 16-bit Counter  */
#define   RTC_MODE1_CTRLA_MODE_CLOCK_Val    _U_(0x2)                                       /**< (RTC_MODE1_CTRLA) Mode 2: Clock/Calendar  */
#define RTC_MODE1_CTRLA_MODE_COUNT32        (RTC_MODE1_CTRLA_MODE_COUNT32_Val << RTC_MODE1_CTRLA_MODE_Pos)  /**< (RTC_MODE1_CTRLA) Mode 0: 32-bit Counter Position  */
#define RTC_MODE1_CTRLA_MODE_COUNT16        (RTC_MODE1_CTRLA_MODE_COUNT16_Val << RTC_MODE1_CTRLA_MODE_Pos)  /**< (RTC_MODE1_CTRLA) Mode 1: 16-bit Counter Position  */
#define RTC_MODE1_CTRLA_MODE_CLOCK          (RTC_MODE1_CTRLA_MODE_CLOCK_Val << RTC_MODE1_CTRLA_MODE_Pos)  /**< (RTC_MODE1_CTRLA) Mode 2: Clock/Calendar Position  */
#define RTC_MODE1_CTRLA_PRESCALER_Pos       8                                              /**< (RTC_MODE1_CTRLA) Prescaler Position */
#define RTC_MODE1_CTRLA_PRESCALER_Msk       (_U_(0xF) << RTC_MODE1_CTRLA_PRESCALER_Pos)    /**< (RTC_MODE1_CTRLA) Prescaler Mask */
#define RTC_MODE1_CTRLA_PRESCALER(value)    (RTC_MODE1_CTRLA_PRESCALER_Msk & ((value) << RTC_MODE1_CTRLA_PRESCALER_Pos))
#define   RTC_MODE1_CTRLA_PRESCALER_OFF_Val _U_(0x0)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV1_Val _U_(0x1)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV2_Val _U_(0x2)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/2  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV4_Val _U_(0x3)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/4  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV8_Val _U_(0x4)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/8  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV16_Val _U_(0x5)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/16  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV32_Val _U_(0x6)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/32  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV64_Val _U_(0x7)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/64  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV128_Val _U_(0x8)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/128  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV256_Val _U_(0x9)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/256  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV512_Val _U_(0xA)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/512  */
#define   RTC_MODE1_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)                                       /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024  */
#define RTC_MODE1_CTRLA_PRESCALER_OFF       (RTC_MODE1_CTRLA_PRESCALER_OFF_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV1      (RTC_MODE1_CTRLA_PRESCALER_DIV1_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV2      (RTC_MODE1_CTRLA_PRESCALER_DIV2_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/2 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV4      (RTC_MODE1_CTRLA_PRESCALER_DIV4_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/4 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV8      (RTC_MODE1_CTRLA_PRESCALER_DIV8_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/8 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV16     (RTC_MODE1_CTRLA_PRESCALER_DIV16_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/16 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV32     (RTC_MODE1_CTRLA_PRESCALER_DIV32_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/32 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV64     (RTC_MODE1_CTRLA_PRESCALER_DIV64_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/64 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV128    (RTC_MODE1_CTRLA_PRESCALER_DIV128_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/128 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV256    (RTC_MODE1_CTRLA_PRESCALER_DIV256_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/256 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV512    (RTC_MODE1_CTRLA_PRESCALER_DIV512_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/512 Position  */
#define RTC_MODE1_CTRLA_PRESCALER_DIV1024   (RTC_MODE1_CTRLA_PRESCALER_DIV1024_Val << RTC_MODE1_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE1_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024 Position  */
#define RTC_MODE1_CTRLA_GPTRST_Pos          14                                             /**< (RTC_MODE1_CTRLA) GP Registers Reset On Tamper Enable Position */
#define RTC_MODE1_CTRLA_GPTRST_Msk          (_U_(0x1) << RTC_MODE1_CTRLA_GPTRST_Pos)       /**< (RTC_MODE1_CTRLA) GP Registers Reset On Tamper Enable Mask */
#define RTC_MODE1_CTRLA_GPTRST              RTC_MODE1_CTRLA_GPTRST_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLA_GPTRST_Msk instead */
#define RTC_MODE1_CTRLA_COUNTSYNC_Pos       15                                             /**< (RTC_MODE1_CTRLA) Count Read Synchronization Enable Position */
#define RTC_MODE1_CTRLA_COUNTSYNC_Msk       (_U_(0x1) << RTC_MODE1_CTRLA_COUNTSYNC_Pos)    /**< (RTC_MODE1_CTRLA) Count Read Synchronization Enable Mask */
#define RTC_MODE1_CTRLA_COUNTSYNC           RTC_MODE1_CTRLA_COUNTSYNC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLA_COUNTSYNC_Msk instead */
#define RTC_MODE1_CTRLA_MASK                _U_(0xCF0F)                                    /**< \deprecated (RTC_MODE1_CTRLA) Register MASK  (Use RTC_MODE1_CTRLA_Msk instead)  */
#define RTC_MODE1_CTRLA_Msk                 _U_(0xCF0F)                                    /**< (RTC_MODE1_CTRLA) Register Mask  */


/* -------- RTC_MODE2_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE2 Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint16_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint16_t MODE:2;                    /**< bit:   2..3  Operating Mode                           */
    uint16_t :2;                        /**< bit:   4..5  Reserved */
    uint16_t CLKREP:1;                  /**< bit:      6  Clock Representation                     */
    uint16_t MATCHCLR:1;                /**< bit:      7  Clear on Match                           */
    uint16_t PRESCALER:4;               /**< bit:  8..11  Prescaler                                */
    uint16_t :2;                        /**< bit: 12..13  Reserved */
    uint16_t GPTRST:1;                  /**< bit:     14  GP Registers Reset On Tamper Enable      */
    uint16_t CLOCKSYNC:1;               /**< bit:     15  Clock Read Synchronization Enable        */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE2_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_CTRLA_OFFSET              (0x00)                                        /**<  (RTC_MODE2_CTRLA) MODE2 Control A  Offset */
#define RTC_MODE2_CTRLA_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE2_CTRLA) MODE2 Control A  Reset Value */

#define RTC_MODE2_CTRLA_SWRST_Pos           0                                              /**< (RTC_MODE2_CTRLA) Software Reset Position */
#define RTC_MODE2_CTRLA_SWRST_Msk           (_U_(0x1) << RTC_MODE2_CTRLA_SWRST_Pos)        /**< (RTC_MODE2_CTRLA) Software Reset Mask */
#define RTC_MODE2_CTRLA_SWRST               RTC_MODE2_CTRLA_SWRST_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_SWRST_Msk instead */
#define RTC_MODE2_CTRLA_ENABLE_Pos          1                                              /**< (RTC_MODE2_CTRLA) Enable Position */
#define RTC_MODE2_CTRLA_ENABLE_Msk          (_U_(0x1) << RTC_MODE2_CTRLA_ENABLE_Pos)       /**< (RTC_MODE2_CTRLA) Enable Mask */
#define RTC_MODE2_CTRLA_ENABLE              RTC_MODE2_CTRLA_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_ENABLE_Msk instead */
#define RTC_MODE2_CTRLA_MODE_Pos            2                                              /**< (RTC_MODE2_CTRLA) Operating Mode Position */
#define RTC_MODE2_CTRLA_MODE_Msk            (_U_(0x3) << RTC_MODE2_CTRLA_MODE_Pos)         /**< (RTC_MODE2_CTRLA) Operating Mode Mask */
#define RTC_MODE2_CTRLA_MODE(value)         (RTC_MODE2_CTRLA_MODE_Msk & ((value) << RTC_MODE2_CTRLA_MODE_Pos))
#define   RTC_MODE2_CTRLA_MODE_COUNT32_Val  _U_(0x0)                                       /**< (RTC_MODE2_CTRLA) Mode 0: 32-bit Counter  */
#define   RTC_MODE2_CTRLA_MODE_COUNT16_Val  _U_(0x1)                                       /**< (RTC_MODE2_CTRLA) Mode 1: 16-bit Counter  */
#define   RTC_MODE2_CTRLA_MODE_CLOCK_Val    _U_(0x2)                                       /**< (RTC_MODE2_CTRLA) Mode 2: Clock/Calendar  */
#define RTC_MODE2_CTRLA_MODE_COUNT32        (RTC_MODE2_CTRLA_MODE_COUNT32_Val << RTC_MODE2_CTRLA_MODE_Pos)  /**< (RTC_MODE2_CTRLA) Mode 0: 32-bit Counter Position  */
#define RTC_MODE2_CTRLA_MODE_COUNT16        (RTC_MODE2_CTRLA_MODE_COUNT16_Val << RTC_MODE2_CTRLA_MODE_Pos)  /**< (RTC_MODE2_CTRLA) Mode 1: 16-bit Counter Position  */
#define RTC_MODE2_CTRLA_MODE_CLOCK          (RTC_MODE2_CTRLA_MODE_CLOCK_Val << RTC_MODE2_CTRLA_MODE_Pos)  /**< (RTC_MODE2_CTRLA) Mode 2: Clock/Calendar Position  */
#define RTC_MODE2_CTRLA_CLKREP_Pos          6                                              /**< (RTC_MODE2_CTRLA) Clock Representation Position */
#define RTC_MODE2_CTRLA_CLKREP_Msk          (_U_(0x1) << RTC_MODE2_CTRLA_CLKREP_Pos)       /**< (RTC_MODE2_CTRLA) Clock Representation Mask */
#define RTC_MODE2_CTRLA_CLKREP              RTC_MODE2_CTRLA_CLKREP_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_CLKREP_Msk instead */
#define RTC_MODE2_CTRLA_MATCHCLR_Pos        7                                              /**< (RTC_MODE2_CTRLA) Clear on Match Position */
#define RTC_MODE2_CTRLA_MATCHCLR_Msk        (_U_(0x1) << RTC_MODE2_CTRLA_MATCHCLR_Pos)     /**< (RTC_MODE2_CTRLA) Clear on Match Mask */
#define RTC_MODE2_CTRLA_MATCHCLR            RTC_MODE2_CTRLA_MATCHCLR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_MATCHCLR_Msk instead */
#define RTC_MODE2_CTRLA_PRESCALER_Pos       8                                              /**< (RTC_MODE2_CTRLA) Prescaler Position */
#define RTC_MODE2_CTRLA_PRESCALER_Msk       (_U_(0xF) << RTC_MODE2_CTRLA_PRESCALER_Pos)    /**< (RTC_MODE2_CTRLA) Prescaler Mask */
#define RTC_MODE2_CTRLA_PRESCALER(value)    (RTC_MODE2_CTRLA_PRESCALER_Msk & ((value) << RTC_MODE2_CTRLA_PRESCALER_Pos))
#define   RTC_MODE2_CTRLA_PRESCALER_OFF_Val _U_(0x0)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV1_Val _U_(0x1)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV2_Val _U_(0x2)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/2  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV4_Val _U_(0x3)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/4  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV8_Val _U_(0x4)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/8  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV16_Val _U_(0x5)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/16  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV32_Val _U_(0x6)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/32  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV64_Val _U_(0x7)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/64  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV128_Val _U_(0x8)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/128  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV256_Val _U_(0x9)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/256  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV512_Val _U_(0xA)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/512  */
#define   RTC_MODE2_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)                                       /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024  */
#define RTC_MODE2_CTRLA_PRESCALER_OFF       (RTC_MODE2_CTRLA_PRESCALER_OFF_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV1      (RTC_MODE2_CTRLA_PRESCALER_DIV1_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV2      (RTC_MODE2_CTRLA_PRESCALER_DIV2_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/2 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV4      (RTC_MODE2_CTRLA_PRESCALER_DIV4_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/4 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV8      (RTC_MODE2_CTRLA_PRESCALER_DIV8_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/8 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV16     (RTC_MODE2_CTRLA_PRESCALER_DIV16_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/16 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV32     (RTC_MODE2_CTRLA_PRESCALER_DIV32_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/32 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV64     (RTC_MODE2_CTRLA_PRESCALER_DIV64_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/64 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV128    (RTC_MODE2_CTRLA_PRESCALER_DIV128_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/128 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV256    (RTC_MODE2_CTRLA_PRESCALER_DIV256_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/256 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV512    (RTC_MODE2_CTRLA_PRESCALER_DIV512_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/512 Position  */
#define RTC_MODE2_CTRLA_PRESCALER_DIV1024   (RTC_MODE2_CTRLA_PRESCALER_DIV1024_Val << RTC_MODE2_CTRLA_PRESCALER_Pos)  /**< (RTC_MODE2_CTRLA) CLK_RTC_CNT = GCLK_RTC/1024 Position  */
#define RTC_MODE2_CTRLA_GPTRST_Pos          14                                             /**< (RTC_MODE2_CTRLA) GP Registers Reset On Tamper Enable Position */
#define RTC_MODE2_CTRLA_GPTRST_Msk          (_U_(0x1) << RTC_MODE2_CTRLA_GPTRST_Pos)       /**< (RTC_MODE2_CTRLA) GP Registers Reset On Tamper Enable Mask */
#define RTC_MODE2_CTRLA_GPTRST              RTC_MODE2_CTRLA_GPTRST_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_GPTRST_Msk instead */
#define RTC_MODE2_CTRLA_CLOCKSYNC_Pos       15                                             /**< (RTC_MODE2_CTRLA) Clock Read Synchronization Enable Position */
#define RTC_MODE2_CTRLA_CLOCKSYNC_Msk       (_U_(0x1) << RTC_MODE2_CTRLA_CLOCKSYNC_Pos)    /**< (RTC_MODE2_CTRLA) Clock Read Synchronization Enable Mask */
#define RTC_MODE2_CTRLA_CLOCKSYNC           RTC_MODE2_CTRLA_CLOCKSYNC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLA_CLOCKSYNC_Msk instead */
#define RTC_MODE2_CTRLA_MASK                _U_(0xCFCF)                                    /**< \deprecated (RTC_MODE2_CTRLA) Register MASK  (Use RTC_MODE2_CTRLA_Msk instead)  */
#define RTC_MODE2_CTRLA_Msk                 _U_(0xCFCF)                                    /**< (RTC_MODE2_CTRLA) Register Mask  */


/* -------- RTC_MODE0_CTRLB : (RTC Offset: 0x02) (R/W 16) MODE0 Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GP0EN:1;                   /**< bit:      0  General Purpose 0 Enable                 */
    uint16_t :3;                        /**< bit:   1..3  Reserved */
    uint16_t DEBMAJ:1;                  /**< bit:      4  Debouncer Majority Enable                */
    uint16_t DEBASYNC:1;                /**< bit:      5  Debouncer Asynchronous Enable            */
    uint16_t RTCOUT:1;                  /**< bit:      6  RTC Output Enable                        */
    uint16_t DMAEN:1;                   /**< bit:      7  DMA Enable                               */
    uint16_t DEBF:3;                    /**< bit:  8..10  Debounce Frequency                       */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t ACTF:3;                    /**< bit: 12..14  Active Layer Frequency                   */
    uint16_t SEPTO:1;                   /**< bit:     15  Separate Tamper Outputs                  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE0_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_CTRLB_OFFSET              (0x02)                                        /**<  (RTC_MODE0_CTRLB) MODE0 Control B  Offset */
#define RTC_MODE0_CTRLB_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE0_CTRLB) MODE0 Control B  Reset Value */

#define RTC_MODE0_CTRLB_GP0EN_Pos           0                                              /**< (RTC_MODE0_CTRLB) General Purpose 0 Enable Position */
#define RTC_MODE0_CTRLB_GP0EN_Msk           (_U_(0x1) << RTC_MODE0_CTRLB_GP0EN_Pos)        /**< (RTC_MODE0_CTRLB) General Purpose 0 Enable Mask */
#define RTC_MODE0_CTRLB_GP0EN               RTC_MODE0_CTRLB_GP0EN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_GP0EN_Msk instead */
#define RTC_MODE0_CTRLB_DEBMAJ_Pos          4                                              /**< (RTC_MODE0_CTRLB) Debouncer Majority Enable Position */
#define RTC_MODE0_CTRLB_DEBMAJ_Msk          (_U_(0x1) << RTC_MODE0_CTRLB_DEBMAJ_Pos)       /**< (RTC_MODE0_CTRLB) Debouncer Majority Enable Mask */
#define RTC_MODE0_CTRLB_DEBMAJ              RTC_MODE0_CTRLB_DEBMAJ_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_DEBMAJ_Msk instead */
#define RTC_MODE0_CTRLB_DEBASYNC_Pos        5                                              /**< (RTC_MODE0_CTRLB) Debouncer Asynchronous Enable Position */
#define RTC_MODE0_CTRLB_DEBASYNC_Msk        (_U_(0x1) << RTC_MODE0_CTRLB_DEBASYNC_Pos)     /**< (RTC_MODE0_CTRLB) Debouncer Asynchronous Enable Mask */
#define RTC_MODE0_CTRLB_DEBASYNC            RTC_MODE0_CTRLB_DEBASYNC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_DEBASYNC_Msk instead */
#define RTC_MODE0_CTRLB_RTCOUT_Pos          6                                              /**< (RTC_MODE0_CTRLB) RTC Output Enable Position */
#define RTC_MODE0_CTRLB_RTCOUT_Msk          (_U_(0x1) << RTC_MODE0_CTRLB_RTCOUT_Pos)       /**< (RTC_MODE0_CTRLB) RTC Output Enable Mask */
#define RTC_MODE0_CTRLB_RTCOUT              RTC_MODE0_CTRLB_RTCOUT_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_RTCOUT_Msk instead */
#define RTC_MODE0_CTRLB_DMAEN_Pos           7                                              /**< (RTC_MODE0_CTRLB) DMA Enable Position */
#define RTC_MODE0_CTRLB_DMAEN_Msk           (_U_(0x1) << RTC_MODE0_CTRLB_DMAEN_Pos)        /**< (RTC_MODE0_CTRLB) DMA Enable Mask */
#define RTC_MODE0_CTRLB_DMAEN               RTC_MODE0_CTRLB_DMAEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_DMAEN_Msk instead */
#define RTC_MODE0_CTRLB_DEBF_Pos            8                                              /**< (RTC_MODE0_CTRLB) Debounce Frequency Position */
#define RTC_MODE0_CTRLB_DEBF_Msk            (_U_(0x7) << RTC_MODE0_CTRLB_DEBF_Pos)         /**< (RTC_MODE0_CTRLB) Debounce Frequency Mask */
#define RTC_MODE0_CTRLB_DEBF(value)         (RTC_MODE0_CTRLB_DEBF_Msk & ((value) << RTC_MODE0_CTRLB_DEBF_Pos))
#define   RTC_MODE0_CTRLB_DEBF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/2  */
#define   RTC_MODE0_CTRLB_DEBF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/4  */
#define   RTC_MODE0_CTRLB_DEBF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/8  */
#define   RTC_MODE0_CTRLB_DEBF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/16  */
#define   RTC_MODE0_CTRLB_DEBF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/32  */
#define   RTC_MODE0_CTRLB_DEBF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/64  */
#define   RTC_MODE0_CTRLB_DEBF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/128  */
#define   RTC_MODE0_CTRLB_DEBF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/256  */
#define RTC_MODE0_CTRLB_DEBF_DIV2           (RTC_MODE0_CTRLB_DEBF_DIV2_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/2 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV4           (RTC_MODE0_CTRLB_DEBF_DIV4_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/4 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV8           (RTC_MODE0_CTRLB_DEBF_DIV8_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/8 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV16          (RTC_MODE0_CTRLB_DEBF_DIV16_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/16 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV32          (RTC_MODE0_CTRLB_DEBF_DIV32_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/32 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV64          (RTC_MODE0_CTRLB_DEBF_DIV64_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/64 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV128         (RTC_MODE0_CTRLB_DEBF_DIV128_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/128 Position  */
#define RTC_MODE0_CTRLB_DEBF_DIV256         (RTC_MODE0_CTRLB_DEBF_DIV256_Val << RTC_MODE0_CTRLB_DEBF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_DEB = CLK_RTC/256 Position  */
#define RTC_MODE0_CTRLB_ACTF_Pos            12                                             /**< (RTC_MODE0_CTRLB) Active Layer Frequency Position */
#define RTC_MODE0_CTRLB_ACTF_Msk            (_U_(0x7) << RTC_MODE0_CTRLB_ACTF_Pos)         /**< (RTC_MODE0_CTRLB) Active Layer Frequency Mask */
#define RTC_MODE0_CTRLB_ACTF(value)         (RTC_MODE0_CTRLB_ACTF_Msk & ((value) << RTC_MODE0_CTRLB_ACTF_Pos))
#define   RTC_MODE0_CTRLB_ACTF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/2  */
#define   RTC_MODE0_CTRLB_ACTF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/4  */
#define   RTC_MODE0_CTRLB_ACTF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/8  */
#define   RTC_MODE0_CTRLB_ACTF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/16  */
#define   RTC_MODE0_CTRLB_ACTF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/32  */
#define   RTC_MODE0_CTRLB_ACTF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/64  */
#define   RTC_MODE0_CTRLB_ACTF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/128  */
#define   RTC_MODE0_CTRLB_ACTF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/256  */
#define RTC_MODE0_CTRLB_ACTF_DIV2           (RTC_MODE0_CTRLB_ACTF_DIV2_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/2 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV4           (RTC_MODE0_CTRLB_ACTF_DIV4_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/4 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV8           (RTC_MODE0_CTRLB_ACTF_DIV8_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/8 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV16          (RTC_MODE0_CTRLB_ACTF_DIV16_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/16 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV32          (RTC_MODE0_CTRLB_ACTF_DIV32_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/32 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV64          (RTC_MODE0_CTRLB_ACTF_DIV64_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/64 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV128         (RTC_MODE0_CTRLB_ACTF_DIV128_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/128 Position  */
#define RTC_MODE0_CTRLB_ACTF_DIV256         (RTC_MODE0_CTRLB_ACTF_DIV256_Val << RTC_MODE0_CTRLB_ACTF_Pos)  /**< (RTC_MODE0_CTRLB) CLK_RTC_OUT = CLK_RTC/256 Position  */
#define RTC_MODE0_CTRLB_SEPTO_Pos           15                                             /**< (RTC_MODE0_CTRLB) Separate Tamper Outputs Position */
#define RTC_MODE0_CTRLB_SEPTO_Msk           (_U_(0x1) << RTC_MODE0_CTRLB_SEPTO_Pos)        /**< (RTC_MODE0_CTRLB) Separate Tamper Outputs Mask */
#define RTC_MODE0_CTRLB_SEPTO               RTC_MODE0_CTRLB_SEPTO_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_CTRLB_SEPTO_Msk instead */
#define RTC_MODE0_CTRLB_MASK                _U_(0xF7F1)                                    /**< \deprecated (RTC_MODE0_CTRLB) Register MASK  (Use RTC_MODE0_CTRLB_Msk instead)  */
#define RTC_MODE0_CTRLB_Msk                 _U_(0xF7F1)                                    /**< (RTC_MODE0_CTRLB) Register Mask  */


/* -------- RTC_MODE1_CTRLB : (RTC Offset: 0x02) (R/W 16) MODE1 Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GP0EN:1;                   /**< bit:      0  General Purpose 0 Enable                 */
    uint16_t :3;                        /**< bit:   1..3  Reserved */
    uint16_t DEBMAJ:1;                  /**< bit:      4  Debouncer Majority Enable                */
    uint16_t DEBASYNC:1;                /**< bit:      5  Debouncer Asynchronous Enable            */
    uint16_t RTCOUT:1;                  /**< bit:      6  RTC Output Enable                        */
    uint16_t DMAEN:1;                   /**< bit:      7  DMA Enable                               */
    uint16_t DEBF:3;                    /**< bit:  8..10  Debounce Frequency                       */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t ACTF:3;                    /**< bit: 12..14  Active Layer Frequency                   */
    uint16_t SEPTO:1;                   /**< bit:     15  Separate Tamper Outputs                  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_CTRLB_OFFSET              (0x02)                                        /**<  (RTC_MODE1_CTRLB) MODE1 Control B  Offset */
#define RTC_MODE1_CTRLB_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE1_CTRLB) MODE1 Control B  Reset Value */

#define RTC_MODE1_CTRLB_GP0EN_Pos           0                                              /**< (RTC_MODE1_CTRLB) General Purpose 0 Enable Position */
#define RTC_MODE1_CTRLB_GP0EN_Msk           (_U_(0x1) << RTC_MODE1_CTRLB_GP0EN_Pos)        /**< (RTC_MODE1_CTRLB) General Purpose 0 Enable Mask */
#define RTC_MODE1_CTRLB_GP0EN               RTC_MODE1_CTRLB_GP0EN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_GP0EN_Msk instead */
#define RTC_MODE1_CTRLB_DEBMAJ_Pos          4                                              /**< (RTC_MODE1_CTRLB) Debouncer Majority Enable Position */
#define RTC_MODE1_CTRLB_DEBMAJ_Msk          (_U_(0x1) << RTC_MODE1_CTRLB_DEBMAJ_Pos)       /**< (RTC_MODE1_CTRLB) Debouncer Majority Enable Mask */
#define RTC_MODE1_CTRLB_DEBMAJ              RTC_MODE1_CTRLB_DEBMAJ_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_DEBMAJ_Msk instead */
#define RTC_MODE1_CTRLB_DEBASYNC_Pos        5                                              /**< (RTC_MODE1_CTRLB) Debouncer Asynchronous Enable Position */
#define RTC_MODE1_CTRLB_DEBASYNC_Msk        (_U_(0x1) << RTC_MODE1_CTRLB_DEBASYNC_Pos)     /**< (RTC_MODE1_CTRLB) Debouncer Asynchronous Enable Mask */
#define RTC_MODE1_CTRLB_DEBASYNC            RTC_MODE1_CTRLB_DEBASYNC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_DEBASYNC_Msk instead */
#define RTC_MODE1_CTRLB_RTCOUT_Pos          6                                              /**< (RTC_MODE1_CTRLB) RTC Output Enable Position */
#define RTC_MODE1_CTRLB_RTCOUT_Msk          (_U_(0x1) << RTC_MODE1_CTRLB_RTCOUT_Pos)       /**< (RTC_MODE1_CTRLB) RTC Output Enable Mask */
#define RTC_MODE1_CTRLB_RTCOUT              RTC_MODE1_CTRLB_RTCOUT_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_RTCOUT_Msk instead */
#define RTC_MODE1_CTRLB_DMAEN_Pos           7                                              /**< (RTC_MODE1_CTRLB) DMA Enable Position */
#define RTC_MODE1_CTRLB_DMAEN_Msk           (_U_(0x1) << RTC_MODE1_CTRLB_DMAEN_Pos)        /**< (RTC_MODE1_CTRLB) DMA Enable Mask */
#define RTC_MODE1_CTRLB_DMAEN               RTC_MODE1_CTRLB_DMAEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_DMAEN_Msk instead */
#define RTC_MODE1_CTRLB_DEBF_Pos            8                                              /**< (RTC_MODE1_CTRLB) Debounce Frequency Position */
#define RTC_MODE1_CTRLB_DEBF_Msk            (_U_(0x7) << RTC_MODE1_CTRLB_DEBF_Pos)         /**< (RTC_MODE1_CTRLB) Debounce Frequency Mask */
#define RTC_MODE1_CTRLB_DEBF(value)         (RTC_MODE1_CTRLB_DEBF_Msk & ((value) << RTC_MODE1_CTRLB_DEBF_Pos))
#define   RTC_MODE1_CTRLB_DEBF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/2  */
#define   RTC_MODE1_CTRLB_DEBF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/4  */
#define   RTC_MODE1_CTRLB_DEBF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/8  */
#define   RTC_MODE1_CTRLB_DEBF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/16  */
#define   RTC_MODE1_CTRLB_DEBF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/32  */
#define   RTC_MODE1_CTRLB_DEBF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/64  */
#define   RTC_MODE1_CTRLB_DEBF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/128  */
#define   RTC_MODE1_CTRLB_DEBF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/256  */
#define RTC_MODE1_CTRLB_DEBF_DIV2           (RTC_MODE1_CTRLB_DEBF_DIV2_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/2 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV4           (RTC_MODE1_CTRLB_DEBF_DIV4_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/4 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV8           (RTC_MODE1_CTRLB_DEBF_DIV8_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/8 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV16          (RTC_MODE1_CTRLB_DEBF_DIV16_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/16 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV32          (RTC_MODE1_CTRLB_DEBF_DIV32_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/32 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV64          (RTC_MODE1_CTRLB_DEBF_DIV64_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/64 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV128         (RTC_MODE1_CTRLB_DEBF_DIV128_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/128 Position  */
#define RTC_MODE1_CTRLB_DEBF_DIV256         (RTC_MODE1_CTRLB_DEBF_DIV256_Val << RTC_MODE1_CTRLB_DEBF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_DEB = CLK_RTC/256 Position  */
#define RTC_MODE1_CTRLB_ACTF_Pos            12                                             /**< (RTC_MODE1_CTRLB) Active Layer Frequency Position */
#define RTC_MODE1_CTRLB_ACTF_Msk            (_U_(0x7) << RTC_MODE1_CTRLB_ACTF_Pos)         /**< (RTC_MODE1_CTRLB) Active Layer Frequency Mask */
#define RTC_MODE1_CTRLB_ACTF(value)         (RTC_MODE1_CTRLB_ACTF_Msk & ((value) << RTC_MODE1_CTRLB_ACTF_Pos))
#define   RTC_MODE1_CTRLB_ACTF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/2  */
#define   RTC_MODE1_CTRLB_ACTF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/4  */
#define   RTC_MODE1_CTRLB_ACTF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/8  */
#define   RTC_MODE1_CTRLB_ACTF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/16  */
#define   RTC_MODE1_CTRLB_ACTF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/32  */
#define   RTC_MODE1_CTRLB_ACTF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/64  */
#define   RTC_MODE1_CTRLB_ACTF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/128  */
#define   RTC_MODE1_CTRLB_ACTF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/256  */
#define RTC_MODE1_CTRLB_ACTF_DIV2           (RTC_MODE1_CTRLB_ACTF_DIV2_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/2 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV4           (RTC_MODE1_CTRLB_ACTF_DIV4_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/4 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV8           (RTC_MODE1_CTRLB_ACTF_DIV8_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/8 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV16          (RTC_MODE1_CTRLB_ACTF_DIV16_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/16 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV32          (RTC_MODE1_CTRLB_ACTF_DIV32_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/32 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV64          (RTC_MODE1_CTRLB_ACTF_DIV64_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/64 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV128         (RTC_MODE1_CTRLB_ACTF_DIV128_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/128 Position  */
#define RTC_MODE1_CTRLB_ACTF_DIV256         (RTC_MODE1_CTRLB_ACTF_DIV256_Val << RTC_MODE1_CTRLB_ACTF_Pos)  /**< (RTC_MODE1_CTRLB) CLK_RTC_OUT = CLK_RTC/256 Position  */
#define RTC_MODE1_CTRLB_SEPTO_Pos           15                                             /**< (RTC_MODE1_CTRLB) Separate Tamper Outputs Position */
#define RTC_MODE1_CTRLB_SEPTO_Msk           (_U_(0x1) << RTC_MODE1_CTRLB_SEPTO_Pos)        /**< (RTC_MODE1_CTRLB) Separate Tamper Outputs Mask */
#define RTC_MODE1_CTRLB_SEPTO               RTC_MODE1_CTRLB_SEPTO_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_CTRLB_SEPTO_Msk instead */
#define RTC_MODE1_CTRLB_MASK                _U_(0xF7F1)                                    /**< \deprecated (RTC_MODE1_CTRLB) Register MASK  (Use RTC_MODE1_CTRLB_Msk instead)  */
#define RTC_MODE1_CTRLB_Msk                 _U_(0xF7F1)                                    /**< (RTC_MODE1_CTRLB) Register Mask  */


/* -------- RTC_MODE2_CTRLB : (RTC Offset: 0x02) (R/W 16) MODE2 Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GP0EN:1;                   /**< bit:      0  General Purpose 0 Enable                 */
    uint16_t :3;                        /**< bit:   1..3  Reserved */
    uint16_t DEBMAJ:1;                  /**< bit:      4  Debouncer Majority Enable                */
    uint16_t DEBASYNC:1;                /**< bit:      5  Debouncer Asynchronous Enable            */
    uint16_t RTCOUT:1;                  /**< bit:      6  RTC Output Enable                        */
    uint16_t DMAEN:1;                   /**< bit:      7  DMA Enable                               */
    uint16_t DEBF:3;                    /**< bit:  8..10  Debounce Frequency                       */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t ACTF:3;                    /**< bit: 12..14  Active Layer Frequency                   */
    uint16_t SEPTO:1;                   /**< bit:     15  Separate Tamper Outputs                  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE2_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_CTRLB_OFFSET              (0x02)                                        /**<  (RTC_MODE2_CTRLB) MODE2 Control B  Offset */
#define RTC_MODE2_CTRLB_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE2_CTRLB) MODE2 Control B  Reset Value */

#define RTC_MODE2_CTRLB_GP0EN_Pos           0                                              /**< (RTC_MODE2_CTRLB) General Purpose 0 Enable Position */
#define RTC_MODE2_CTRLB_GP0EN_Msk           (_U_(0x1) << RTC_MODE2_CTRLB_GP0EN_Pos)        /**< (RTC_MODE2_CTRLB) General Purpose 0 Enable Mask */
#define RTC_MODE2_CTRLB_GP0EN               RTC_MODE2_CTRLB_GP0EN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_GP0EN_Msk instead */
#define RTC_MODE2_CTRLB_DEBMAJ_Pos          4                                              /**< (RTC_MODE2_CTRLB) Debouncer Majority Enable Position */
#define RTC_MODE2_CTRLB_DEBMAJ_Msk          (_U_(0x1) << RTC_MODE2_CTRLB_DEBMAJ_Pos)       /**< (RTC_MODE2_CTRLB) Debouncer Majority Enable Mask */
#define RTC_MODE2_CTRLB_DEBMAJ              RTC_MODE2_CTRLB_DEBMAJ_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_DEBMAJ_Msk instead */
#define RTC_MODE2_CTRLB_DEBASYNC_Pos        5                                              /**< (RTC_MODE2_CTRLB) Debouncer Asynchronous Enable Position */
#define RTC_MODE2_CTRLB_DEBASYNC_Msk        (_U_(0x1) << RTC_MODE2_CTRLB_DEBASYNC_Pos)     /**< (RTC_MODE2_CTRLB) Debouncer Asynchronous Enable Mask */
#define RTC_MODE2_CTRLB_DEBASYNC            RTC_MODE2_CTRLB_DEBASYNC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_DEBASYNC_Msk instead */
#define RTC_MODE2_CTRLB_RTCOUT_Pos          6                                              /**< (RTC_MODE2_CTRLB) RTC Output Enable Position */
#define RTC_MODE2_CTRLB_RTCOUT_Msk          (_U_(0x1) << RTC_MODE2_CTRLB_RTCOUT_Pos)       /**< (RTC_MODE2_CTRLB) RTC Output Enable Mask */
#define RTC_MODE2_CTRLB_RTCOUT              RTC_MODE2_CTRLB_RTCOUT_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_RTCOUT_Msk instead */
#define RTC_MODE2_CTRLB_DMAEN_Pos           7                                              /**< (RTC_MODE2_CTRLB) DMA Enable Position */
#define RTC_MODE2_CTRLB_DMAEN_Msk           (_U_(0x1) << RTC_MODE2_CTRLB_DMAEN_Pos)        /**< (RTC_MODE2_CTRLB) DMA Enable Mask */
#define RTC_MODE2_CTRLB_DMAEN               RTC_MODE2_CTRLB_DMAEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_DMAEN_Msk instead */
#define RTC_MODE2_CTRLB_DEBF_Pos            8                                              /**< (RTC_MODE2_CTRLB) Debounce Frequency Position */
#define RTC_MODE2_CTRLB_DEBF_Msk            (_U_(0x7) << RTC_MODE2_CTRLB_DEBF_Pos)         /**< (RTC_MODE2_CTRLB) Debounce Frequency Mask */
#define RTC_MODE2_CTRLB_DEBF(value)         (RTC_MODE2_CTRLB_DEBF_Msk & ((value) << RTC_MODE2_CTRLB_DEBF_Pos))
#define   RTC_MODE2_CTRLB_DEBF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/2  */
#define   RTC_MODE2_CTRLB_DEBF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/4  */
#define   RTC_MODE2_CTRLB_DEBF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/8  */
#define   RTC_MODE2_CTRLB_DEBF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/16  */
#define   RTC_MODE2_CTRLB_DEBF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/32  */
#define   RTC_MODE2_CTRLB_DEBF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/64  */
#define   RTC_MODE2_CTRLB_DEBF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/128  */
#define   RTC_MODE2_CTRLB_DEBF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/256  */
#define RTC_MODE2_CTRLB_DEBF_DIV2           (RTC_MODE2_CTRLB_DEBF_DIV2_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/2 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV4           (RTC_MODE2_CTRLB_DEBF_DIV4_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/4 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV8           (RTC_MODE2_CTRLB_DEBF_DIV8_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/8 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV16          (RTC_MODE2_CTRLB_DEBF_DIV16_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/16 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV32          (RTC_MODE2_CTRLB_DEBF_DIV32_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/32 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV64          (RTC_MODE2_CTRLB_DEBF_DIV64_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/64 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV128         (RTC_MODE2_CTRLB_DEBF_DIV128_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/128 Position  */
#define RTC_MODE2_CTRLB_DEBF_DIV256         (RTC_MODE2_CTRLB_DEBF_DIV256_Val << RTC_MODE2_CTRLB_DEBF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_DEB = CLK_RTC/256 Position  */
#define RTC_MODE2_CTRLB_ACTF_Pos            12                                             /**< (RTC_MODE2_CTRLB) Active Layer Frequency Position */
#define RTC_MODE2_CTRLB_ACTF_Msk            (_U_(0x7) << RTC_MODE2_CTRLB_ACTF_Pos)         /**< (RTC_MODE2_CTRLB) Active Layer Frequency Mask */
#define RTC_MODE2_CTRLB_ACTF(value)         (RTC_MODE2_CTRLB_ACTF_Msk & ((value) << RTC_MODE2_CTRLB_ACTF_Pos))
#define   RTC_MODE2_CTRLB_ACTF_DIV2_Val     _U_(0x0)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/2  */
#define   RTC_MODE2_CTRLB_ACTF_DIV4_Val     _U_(0x1)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/4  */
#define   RTC_MODE2_CTRLB_ACTF_DIV8_Val     _U_(0x2)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/8  */
#define   RTC_MODE2_CTRLB_ACTF_DIV16_Val    _U_(0x3)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/16  */
#define   RTC_MODE2_CTRLB_ACTF_DIV32_Val    _U_(0x4)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/32  */
#define   RTC_MODE2_CTRLB_ACTF_DIV64_Val    _U_(0x5)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/64  */
#define   RTC_MODE2_CTRLB_ACTF_DIV128_Val   _U_(0x6)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/128  */
#define   RTC_MODE2_CTRLB_ACTF_DIV256_Val   _U_(0x7)                                       /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/256  */
#define RTC_MODE2_CTRLB_ACTF_DIV2           (RTC_MODE2_CTRLB_ACTF_DIV2_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/2 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV4           (RTC_MODE2_CTRLB_ACTF_DIV4_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/4 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV8           (RTC_MODE2_CTRLB_ACTF_DIV8_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/8 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV16          (RTC_MODE2_CTRLB_ACTF_DIV16_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/16 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV32          (RTC_MODE2_CTRLB_ACTF_DIV32_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/32 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV64          (RTC_MODE2_CTRLB_ACTF_DIV64_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/64 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV128         (RTC_MODE2_CTRLB_ACTF_DIV128_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/128 Position  */
#define RTC_MODE2_CTRLB_ACTF_DIV256         (RTC_MODE2_CTRLB_ACTF_DIV256_Val << RTC_MODE2_CTRLB_ACTF_Pos)  /**< (RTC_MODE2_CTRLB) CLK_RTC_OUT = CLK_RTC/256 Position  */
#define RTC_MODE2_CTRLB_SEPTO_Pos           15                                             /**< (RTC_MODE2_CTRLB) Separate Tamper Outputs Position */
#define RTC_MODE2_CTRLB_SEPTO_Msk           (_U_(0x1) << RTC_MODE2_CTRLB_SEPTO_Pos)        /**< (RTC_MODE2_CTRLB) Separate Tamper Outputs Mask */
#define RTC_MODE2_CTRLB_SEPTO               RTC_MODE2_CTRLB_SEPTO_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_CTRLB_SEPTO_Msk instead */
#define RTC_MODE2_CTRLB_MASK                _U_(0xF7F1)                                    /**< \deprecated (RTC_MODE2_CTRLB) Register MASK  (Use RTC_MODE2_CTRLB_Msk instead)  */
#define RTC_MODE2_CTRLB_Msk                 _U_(0xF7F1)                                    /**< (RTC_MODE2_CTRLB) Register Mask  */


/* -------- RTC_MODE0_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE0 Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PEREO0:1;                  /**< bit:      0  Periodic Interval 0 Event Output Enable  */
    uint32_t PEREO1:1;                  /**< bit:      1  Periodic Interval 1 Event Output Enable  */
    uint32_t PEREO2:1;                  /**< bit:      2  Periodic Interval 2 Event Output Enable  */
    uint32_t PEREO3:1;                  /**< bit:      3  Periodic Interval 3 Event Output Enable  */
    uint32_t PEREO4:1;                  /**< bit:      4  Periodic Interval 4 Event Output Enable  */
    uint32_t PEREO5:1;                  /**< bit:      5  Periodic Interval 5 Event Output Enable  */
    uint32_t PEREO6:1;                  /**< bit:      6  Periodic Interval 6 Event Output Enable  */
    uint32_t PEREO7:1;                  /**< bit:      7  Periodic Interval 7 Event Output Enable  */
    uint32_t CMPEO0:1;                  /**< bit:      8  Compare 0 Event Output Enable            */
    uint32_t :5;                        /**< bit:  9..13  Reserved */
    uint32_t TAMPEREO:1;                /**< bit:     14  Tamper Event Output Enable               */
    uint32_t OVFEO:1;                   /**< bit:     15  Overflow Event Output Enable             */
    uint32_t TAMPEVEI:1;                /**< bit:     16  Tamper Event Input Enable                */
    uint32_t :7;                        /**< bit: 17..23  Reserved */
    uint32_t PERDEO:1;                  /**< bit:     24  Periodic Interval Daily Event Output Enable */
    uint32_t :7;                        /**< bit: 25..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t PEREO:8;                   /**< bit:   0..7  Periodic Interval x Event Output Enable  */
    uint32_t CMPEO:1;                   /**< bit:      8  Compare x Event Output Enable            */
    uint32_t :23;                       /**< bit:  9..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE0_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_EVCTRL_OFFSET             (0x04)                                        /**<  (RTC_MODE0_EVCTRL) MODE0 Event Control  Offset */
#define RTC_MODE0_EVCTRL_RESETVALUE         _U_(0x00)                                     /**<  (RTC_MODE0_EVCTRL) MODE0 Event Control  Reset Value */

#define RTC_MODE0_EVCTRL_PEREO0_Pos         0                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 0 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO0_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO0_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 0 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO0             RTC_MODE0_EVCTRL_PEREO0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO0_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO1_Pos         1                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 1 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO1_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO1_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 1 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO1             RTC_MODE0_EVCTRL_PEREO1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO1_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO2_Pos         2                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 2 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO2_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO2_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 2 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO2             RTC_MODE0_EVCTRL_PEREO2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO2_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO3_Pos         3                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 3 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO3_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO3_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 3 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO3             RTC_MODE0_EVCTRL_PEREO3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO3_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO4_Pos         4                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 4 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO4_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO4_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 4 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO4             RTC_MODE0_EVCTRL_PEREO4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO4_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO5_Pos         5                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 5 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO5_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO5_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 5 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO5             RTC_MODE0_EVCTRL_PEREO5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO5_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO6_Pos         6                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 6 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO6_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO6_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 6 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO6             RTC_MODE0_EVCTRL_PEREO6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO6_Msk instead */
#define RTC_MODE0_EVCTRL_PEREO7_Pos         7                                              /**< (RTC_MODE0_EVCTRL) Periodic Interval 7 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PEREO7_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PEREO7_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval 7 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PEREO7             RTC_MODE0_EVCTRL_PEREO7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PEREO7_Msk instead */
#define RTC_MODE0_EVCTRL_CMPEO0_Pos         8                                              /**< (RTC_MODE0_EVCTRL) Compare 0 Event Output Enable Position */
#define RTC_MODE0_EVCTRL_CMPEO0_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_CMPEO0_Pos)      /**< (RTC_MODE0_EVCTRL) Compare 0 Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_CMPEO0             RTC_MODE0_EVCTRL_CMPEO0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_CMPEO0_Msk instead */
#define RTC_MODE0_EVCTRL_TAMPEREO_Pos       14                                             /**< (RTC_MODE0_EVCTRL) Tamper Event Output Enable Position */
#define RTC_MODE0_EVCTRL_TAMPEREO_Msk       (_U_(0x1) << RTC_MODE0_EVCTRL_TAMPEREO_Pos)    /**< (RTC_MODE0_EVCTRL) Tamper Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_TAMPEREO           RTC_MODE0_EVCTRL_TAMPEREO_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_TAMPEREO_Msk instead */
#define RTC_MODE0_EVCTRL_OVFEO_Pos          15                                             /**< (RTC_MODE0_EVCTRL) Overflow Event Output Enable Position */
#define RTC_MODE0_EVCTRL_OVFEO_Msk          (_U_(0x1) << RTC_MODE0_EVCTRL_OVFEO_Pos)       /**< (RTC_MODE0_EVCTRL) Overflow Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_OVFEO              RTC_MODE0_EVCTRL_OVFEO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_OVFEO_Msk instead */
#define RTC_MODE0_EVCTRL_TAMPEVEI_Pos       16                                             /**< (RTC_MODE0_EVCTRL) Tamper Event Input Enable Position */
#define RTC_MODE0_EVCTRL_TAMPEVEI_Msk       (_U_(0x1) << RTC_MODE0_EVCTRL_TAMPEVEI_Pos)    /**< (RTC_MODE0_EVCTRL) Tamper Event Input Enable Mask */
#define RTC_MODE0_EVCTRL_TAMPEVEI           RTC_MODE0_EVCTRL_TAMPEVEI_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_TAMPEVEI_Msk instead */
#define RTC_MODE0_EVCTRL_PERDEO_Pos         24                                             /**< (RTC_MODE0_EVCTRL) Periodic Interval Daily Event Output Enable Position */
#define RTC_MODE0_EVCTRL_PERDEO_Msk         (_U_(0x1) << RTC_MODE0_EVCTRL_PERDEO_Pos)      /**< (RTC_MODE0_EVCTRL) Periodic Interval Daily Event Output Enable Mask */
#define RTC_MODE0_EVCTRL_PERDEO             RTC_MODE0_EVCTRL_PERDEO_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_EVCTRL_PERDEO_Msk instead */
#define RTC_MODE0_EVCTRL_MASK               _U_(0x101C1FF)                                 /**< \deprecated (RTC_MODE0_EVCTRL) Register MASK  (Use RTC_MODE0_EVCTRL_Msk instead)  */
#define RTC_MODE0_EVCTRL_Msk                _U_(0x101C1FF)                                 /**< (RTC_MODE0_EVCTRL) Register Mask  */

#define RTC_MODE0_EVCTRL_PEREO_Pos          0                                              /**< (RTC_MODE0_EVCTRL Position) Periodic Interval x Event Output Enable */
#define RTC_MODE0_EVCTRL_PEREO_Msk          (_U_(0xFF) << RTC_MODE0_EVCTRL_PEREO_Pos)      /**< (RTC_MODE0_EVCTRL Mask) PEREO */
#define RTC_MODE0_EVCTRL_PEREO(value)       (RTC_MODE0_EVCTRL_PEREO_Msk & ((value) << RTC_MODE0_EVCTRL_PEREO_Pos))  
#define RTC_MODE0_EVCTRL_CMPEO_Pos          8                                              /**< (RTC_MODE0_EVCTRL Position) Compare x Event Output Enable */
#define RTC_MODE0_EVCTRL_CMPEO_Msk          (_U_(0x1) << RTC_MODE0_EVCTRL_CMPEO_Pos)       /**< (RTC_MODE0_EVCTRL Mask) CMPEO */
#define RTC_MODE0_EVCTRL_CMPEO(value)       (RTC_MODE0_EVCTRL_CMPEO_Msk & ((value) << RTC_MODE0_EVCTRL_CMPEO_Pos))  

/* -------- RTC_MODE1_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE1 Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PEREO0:1;                  /**< bit:      0  Periodic Interval 0 Event Output Enable  */
    uint32_t PEREO1:1;                  /**< bit:      1  Periodic Interval 1 Event Output Enable  */
    uint32_t PEREO2:1;                  /**< bit:      2  Periodic Interval 2 Event Output Enable  */
    uint32_t PEREO3:1;                  /**< bit:      3  Periodic Interval 3 Event Output Enable  */
    uint32_t PEREO4:1;                  /**< bit:      4  Periodic Interval 4 Event Output Enable  */
    uint32_t PEREO5:1;                  /**< bit:      5  Periodic Interval 5 Event Output Enable  */
    uint32_t PEREO6:1;                  /**< bit:      6  Periodic Interval 6 Event Output Enable  */
    uint32_t PEREO7:1;                  /**< bit:      7  Periodic Interval 7 Event Output Enable  */
    uint32_t CMPEO0:1;                  /**< bit:      8  Compare 0 Event Output Enable            */
    uint32_t CMPEO1:1;                  /**< bit:      9  Compare 1 Event Output Enable            */
    uint32_t :4;                        /**< bit: 10..13  Reserved */
    uint32_t TAMPEREO:1;                /**< bit:     14  Tamper Event Output Enable               */
    uint32_t OVFEO:1;                   /**< bit:     15  Overflow Event Output Enable             */
    uint32_t TAMPEVEI:1;                /**< bit:     16  Tamper Event Input Enable                */
    uint32_t :7;                        /**< bit: 17..23  Reserved */
    uint32_t PERDEO:1;                  /**< bit:     24  Periodic Interval Daily Event Output Enable */
    uint32_t :7;                        /**< bit: 25..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t PEREO:8;                   /**< bit:   0..7  Periodic Interval x Event Output Enable  */
    uint32_t CMPEO:2;                   /**< bit:   8..9  Compare x Event Output Enable            */
    uint32_t :22;                       /**< bit: 10..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE1_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_EVCTRL_OFFSET             (0x04)                                        /**<  (RTC_MODE1_EVCTRL) MODE1 Event Control  Offset */
#define RTC_MODE1_EVCTRL_RESETVALUE         _U_(0x00)                                     /**<  (RTC_MODE1_EVCTRL) MODE1 Event Control  Reset Value */

#define RTC_MODE1_EVCTRL_PEREO0_Pos         0                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 0 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO0_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO0_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 0 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO0             RTC_MODE1_EVCTRL_PEREO0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO0_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO1_Pos         1                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 1 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO1_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO1_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 1 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO1             RTC_MODE1_EVCTRL_PEREO1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO1_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO2_Pos         2                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 2 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO2_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO2_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 2 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO2             RTC_MODE1_EVCTRL_PEREO2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO2_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO3_Pos         3                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 3 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO3_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO3_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 3 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO3             RTC_MODE1_EVCTRL_PEREO3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO3_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO4_Pos         4                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 4 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO4_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO4_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 4 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO4             RTC_MODE1_EVCTRL_PEREO4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO4_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO5_Pos         5                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 5 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO5_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO5_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 5 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO5             RTC_MODE1_EVCTRL_PEREO5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO5_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO6_Pos         6                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 6 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO6_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO6_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 6 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO6             RTC_MODE1_EVCTRL_PEREO6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO6_Msk instead */
#define RTC_MODE1_EVCTRL_PEREO7_Pos         7                                              /**< (RTC_MODE1_EVCTRL) Periodic Interval 7 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PEREO7_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PEREO7_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval 7 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PEREO7             RTC_MODE1_EVCTRL_PEREO7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PEREO7_Msk instead */
#define RTC_MODE1_EVCTRL_CMPEO0_Pos         8                                              /**< (RTC_MODE1_EVCTRL) Compare 0 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_CMPEO0_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_CMPEO0_Pos)      /**< (RTC_MODE1_EVCTRL) Compare 0 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_CMPEO0             RTC_MODE1_EVCTRL_CMPEO0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_CMPEO0_Msk instead */
#define RTC_MODE1_EVCTRL_CMPEO1_Pos         9                                              /**< (RTC_MODE1_EVCTRL) Compare 1 Event Output Enable Position */
#define RTC_MODE1_EVCTRL_CMPEO1_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_CMPEO1_Pos)      /**< (RTC_MODE1_EVCTRL) Compare 1 Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_CMPEO1             RTC_MODE1_EVCTRL_CMPEO1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_CMPEO1_Msk instead */
#define RTC_MODE1_EVCTRL_TAMPEREO_Pos       14                                             /**< (RTC_MODE1_EVCTRL) Tamper Event Output Enable Position */
#define RTC_MODE1_EVCTRL_TAMPEREO_Msk       (_U_(0x1) << RTC_MODE1_EVCTRL_TAMPEREO_Pos)    /**< (RTC_MODE1_EVCTRL) Tamper Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_TAMPEREO           RTC_MODE1_EVCTRL_TAMPEREO_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_TAMPEREO_Msk instead */
#define RTC_MODE1_EVCTRL_OVFEO_Pos          15                                             /**< (RTC_MODE1_EVCTRL) Overflow Event Output Enable Position */
#define RTC_MODE1_EVCTRL_OVFEO_Msk          (_U_(0x1) << RTC_MODE1_EVCTRL_OVFEO_Pos)       /**< (RTC_MODE1_EVCTRL) Overflow Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_OVFEO              RTC_MODE1_EVCTRL_OVFEO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_OVFEO_Msk instead */
#define RTC_MODE1_EVCTRL_TAMPEVEI_Pos       16                                             /**< (RTC_MODE1_EVCTRL) Tamper Event Input Enable Position */
#define RTC_MODE1_EVCTRL_TAMPEVEI_Msk       (_U_(0x1) << RTC_MODE1_EVCTRL_TAMPEVEI_Pos)    /**< (RTC_MODE1_EVCTRL) Tamper Event Input Enable Mask */
#define RTC_MODE1_EVCTRL_TAMPEVEI           RTC_MODE1_EVCTRL_TAMPEVEI_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_TAMPEVEI_Msk instead */
#define RTC_MODE1_EVCTRL_PERDEO_Pos         24                                             /**< (RTC_MODE1_EVCTRL) Periodic Interval Daily Event Output Enable Position */
#define RTC_MODE1_EVCTRL_PERDEO_Msk         (_U_(0x1) << RTC_MODE1_EVCTRL_PERDEO_Pos)      /**< (RTC_MODE1_EVCTRL) Periodic Interval Daily Event Output Enable Mask */
#define RTC_MODE1_EVCTRL_PERDEO             RTC_MODE1_EVCTRL_PERDEO_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_EVCTRL_PERDEO_Msk instead */
#define RTC_MODE1_EVCTRL_MASK               _U_(0x101C3FF)                                 /**< \deprecated (RTC_MODE1_EVCTRL) Register MASK  (Use RTC_MODE1_EVCTRL_Msk instead)  */
#define RTC_MODE1_EVCTRL_Msk                _U_(0x101C3FF)                                 /**< (RTC_MODE1_EVCTRL) Register Mask  */

#define RTC_MODE1_EVCTRL_PEREO_Pos          0                                              /**< (RTC_MODE1_EVCTRL Position) Periodic Interval x Event Output Enable */
#define RTC_MODE1_EVCTRL_PEREO_Msk          (_U_(0xFF) << RTC_MODE1_EVCTRL_PEREO_Pos)      /**< (RTC_MODE1_EVCTRL Mask) PEREO */
#define RTC_MODE1_EVCTRL_PEREO(value)       (RTC_MODE1_EVCTRL_PEREO_Msk & ((value) << RTC_MODE1_EVCTRL_PEREO_Pos))  
#define RTC_MODE1_EVCTRL_CMPEO_Pos          8                                              /**< (RTC_MODE1_EVCTRL Position) Compare x Event Output Enable */
#define RTC_MODE1_EVCTRL_CMPEO_Msk          (_U_(0x3) << RTC_MODE1_EVCTRL_CMPEO_Pos)       /**< (RTC_MODE1_EVCTRL Mask) CMPEO */
#define RTC_MODE1_EVCTRL_CMPEO(value)       (RTC_MODE1_EVCTRL_CMPEO_Msk & ((value) << RTC_MODE1_EVCTRL_CMPEO_Pos))  

/* -------- RTC_MODE2_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE2 Event Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PEREO0:1;                  /**< bit:      0  Periodic Interval 0 Event Output Enable  */
    uint32_t PEREO1:1;                  /**< bit:      1  Periodic Interval 1 Event Output Enable  */
    uint32_t PEREO2:1;                  /**< bit:      2  Periodic Interval 2 Event Output Enable  */
    uint32_t PEREO3:1;                  /**< bit:      3  Periodic Interval 3 Event Output Enable  */
    uint32_t PEREO4:1;                  /**< bit:      4  Periodic Interval 4 Event Output Enable  */
    uint32_t PEREO5:1;                  /**< bit:      5  Periodic Interval 5 Event Output Enable  */
    uint32_t PEREO6:1;                  /**< bit:      6  Periodic Interval 6 Event Output Enable  */
    uint32_t PEREO7:1;                  /**< bit:      7  Periodic Interval 7 Event Output Enable  */
    uint32_t ALARMEO0:1;                /**< bit:      8  Alarm 0 Event Output Enable              */
    uint32_t :5;                        /**< bit:  9..13  Reserved */
    uint32_t TAMPEREO:1;                /**< bit:     14  Tamper Event Output Enable               */
    uint32_t OVFEO:1;                   /**< bit:     15  Overflow Event Output Enable             */
    uint32_t TAMPEVEI:1;                /**< bit:     16  Tamper Event Input Enable                */
    uint32_t :7;                        /**< bit: 17..23  Reserved */
    uint32_t PERDEO:1;                  /**< bit:     24  Periodic Interval Daily Event Output Enable */
    uint32_t :7;                        /**< bit: 25..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t PEREO:8;                   /**< bit:   0..7  Periodic Interval x Event Output Enable  */
    uint32_t ALARMEO:1;                 /**< bit:      8  Alarm x Event Output Enable              */
    uint32_t :23;                       /**< bit:  9..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE2_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_EVCTRL_OFFSET             (0x04)                                        /**<  (RTC_MODE2_EVCTRL) MODE2 Event Control  Offset */
#define RTC_MODE2_EVCTRL_RESETVALUE         _U_(0x00)                                     /**<  (RTC_MODE2_EVCTRL) MODE2 Event Control  Reset Value */

#define RTC_MODE2_EVCTRL_PEREO0_Pos         0                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 0 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO0_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO0_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 0 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO0             RTC_MODE2_EVCTRL_PEREO0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO0_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO1_Pos         1                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 1 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO1_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO1_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 1 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO1             RTC_MODE2_EVCTRL_PEREO1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO1_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO2_Pos         2                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 2 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO2_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO2_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 2 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO2             RTC_MODE2_EVCTRL_PEREO2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO2_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO3_Pos         3                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 3 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO3_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO3_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 3 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO3             RTC_MODE2_EVCTRL_PEREO3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO3_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO4_Pos         4                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 4 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO4_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO4_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 4 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO4             RTC_MODE2_EVCTRL_PEREO4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO4_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO5_Pos         5                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 5 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO5_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO5_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 5 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO5             RTC_MODE2_EVCTRL_PEREO5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO5_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO6_Pos         6                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 6 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO6_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO6_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 6 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO6             RTC_MODE2_EVCTRL_PEREO6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO6_Msk instead */
#define RTC_MODE2_EVCTRL_PEREO7_Pos         7                                              /**< (RTC_MODE2_EVCTRL) Periodic Interval 7 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PEREO7_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PEREO7_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval 7 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PEREO7             RTC_MODE2_EVCTRL_PEREO7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PEREO7_Msk instead */
#define RTC_MODE2_EVCTRL_ALARMEO0_Pos       8                                              /**< (RTC_MODE2_EVCTRL) Alarm 0 Event Output Enable Position */
#define RTC_MODE2_EVCTRL_ALARMEO0_Msk       (_U_(0x1) << RTC_MODE2_EVCTRL_ALARMEO0_Pos)    /**< (RTC_MODE2_EVCTRL) Alarm 0 Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_ALARMEO0           RTC_MODE2_EVCTRL_ALARMEO0_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_ALARMEO0_Msk instead */
#define RTC_MODE2_EVCTRL_TAMPEREO_Pos       14                                             /**< (RTC_MODE2_EVCTRL) Tamper Event Output Enable Position */
#define RTC_MODE2_EVCTRL_TAMPEREO_Msk       (_U_(0x1) << RTC_MODE2_EVCTRL_TAMPEREO_Pos)    /**< (RTC_MODE2_EVCTRL) Tamper Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_TAMPEREO           RTC_MODE2_EVCTRL_TAMPEREO_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_TAMPEREO_Msk instead */
#define RTC_MODE2_EVCTRL_OVFEO_Pos          15                                             /**< (RTC_MODE2_EVCTRL) Overflow Event Output Enable Position */
#define RTC_MODE2_EVCTRL_OVFEO_Msk          (_U_(0x1) << RTC_MODE2_EVCTRL_OVFEO_Pos)       /**< (RTC_MODE2_EVCTRL) Overflow Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_OVFEO              RTC_MODE2_EVCTRL_OVFEO_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_OVFEO_Msk instead */
#define RTC_MODE2_EVCTRL_TAMPEVEI_Pos       16                                             /**< (RTC_MODE2_EVCTRL) Tamper Event Input Enable Position */
#define RTC_MODE2_EVCTRL_TAMPEVEI_Msk       (_U_(0x1) << RTC_MODE2_EVCTRL_TAMPEVEI_Pos)    /**< (RTC_MODE2_EVCTRL) Tamper Event Input Enable Mask */
#define RTC_MODE2_EVCTRL_TAMPEVEI           RTC_MODE2_EVCTRL_TAMPEVEI_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_TAMPEVEI_Msk instead */
#define RTC_MODE2_EVCTRL_PERDEO_Pos         24                                             /**< (RTC_MODE2_EVCTRL) Periodic Interval Daily Event Output Enable Position */
#define RTC_MODE2_EVCTRL_PERDEO_Msk         (_U_(0x1) << RTC_MODE2_EVCTRL_PERDEO_Pos)      /**< (RTC_MODE2_EVCTRL) Periodic Interval Daily Event Output Enable Mask */
#define RTC_MODE2_EVCTRL_PERDEO             RTC_MODE2_EVCTRL_PERDEO_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_EVCTRL_PERDEO_Msk instead */
#define RTC_MODE2_EVCTRL_MASK               _U_(0x101C1FF)                                 /**< \deprecated (RTC_MODE2_EVCTRL) Register MASK  (Use RTC_MODE2_EVCTRL_Msk instead)  */
#define RTC_MODE2_EVCTRL_Msk                _U_(0x101C1FF)                                 /**< (RTC_MODE2_EVCTRL) Register Mask  */

#define RTC_MODE2_EVCTRL_PEREO_Pos          0                                              /**< (RTC_MODE2_EVCTRL Position) Periodic Interval x Event Output Enable */
#define RTC_MODE2_EVCTRL_PEREO_Msk          (_U_(0xFF) << RTC_MODE2_EVCTRL_PEREO_Pos)      /**< (RTC_MODE2_EVCTRL Mask) PEREO */
#define RTC_MODE2_EVCTRL_PEREO(value)       (RTC_MODE2_EVCTRL_PEREO_Msk & ((value) << RTC_MODE2_EVCTRL_PEREO_Pos))  
#define RTC_MODE2_EVCTRL_ALARMEO_Pos        8                                              /**< (RTC_MODE2_EVCTRL Position) Alarm x Event Output Enable */
#define RTC_MODE2_EVCTRL_ALARMEO_Msk        (_U_(0x1) << RTC_MODE2_EVCTRL_ALARMEO_Pos)     /**< (RTC_MODE2_EVCTRL Mask) ALARMEO */
#define RTC_MODE2_EVCTRL_ALARMEO(value)     (RTC_MODE2_EVCTRL_ALARMEO_Msk & ((value) << RTC_MODE2_EVCTRL_ALARMEO_Pos))  

/* -------- RTC_MODE0_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE0 Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Interrupt Enable     */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Interrupt Enable     */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Interrupt Enable     */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Interrupt Enable     */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Interrupt Enable     */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Interrupt Enable     */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Interrupt Enable     */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Interrupt Enable     */
    uint16_t CMP0:1;                    /**< bit:      8  Compare 0 Interrupt Enable               */
    uint16_t :5;                        /**< bit:  9..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Interrupt Enable     */
    uint16_t CMP:1;                     /**< bit:      8  Compare x Interrupt Enable               */
    uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE0_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_INTENCLR_OFFSET           (0x08)                                        /**<  (RTC_MODE0_INTENCLR) MODE0 Interrupt Enable Clear  Offset */
#define RTC_MODE0_INTENCLR_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE0_INTENCLR) MODE0 Interrupt Enable Clear  Reset Value */

#define RTC_MODE0_INTENCLR_PER0_Pos         0                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 0 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER0_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER0_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 0 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER0             RTC_MODE0_INTENCLR_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER0_Msk instead */
#define RTC_MODE0_INTENCLR_PER1_Pos         1                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 1 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER1_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER1_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 1 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER1             RTC_MODE0_INTENCLR_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER1_Msk instead */
#define RTC_MODE0_INTENCLR_PER2_Pos         2                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 2 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER2_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER2_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 2 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER2             RTC_MODE0_INTENCLR_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER2_Msk instead */
#define RTC_MODE0_INTENCLR_PER3_Pos         3                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 3 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER3_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER3_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 3 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER3             RTC_MODE0_INTENCLR_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER3_Msk instead */
#define RTC_MODE0_INTENCLR_PER4_Pos         4                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 4 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER4_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER4_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 4 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER4             RTC_MODE0_INTENCLR_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER4_Msk instead */
#define RTC_MODE0_INTENCLR_PER5_Pos         5                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 5 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER5_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER5_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 5 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER5             RTC_MODE0_INTENCLR_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER5_Msk instead */
#define RTC_MODE0_INTENCLR_PER6_Pos         6                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 6 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER6_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER6_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 6 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER6             RTC_MODE0_INTENCLR_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER6_Msk instead */
#define RTC_MODE0_INTENCLR_PER7_Pos         7                                              /**< (RTC_MODE0_INTENCLR) Periodic Interval 7 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_PER7_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_PER7_Pos)      /**< (RTC_MODE0_INTENCLR) Periodic Interval 7 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_PER7             RTC_MODE0_INTENCLR_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_PER7_Msk instead */
#define RTC_MODE0_INTENCLR_CMP0_Pos         8                                              /**< (RTC_MODE0_INTENCLR) Compare 0 Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_CMP0_Msk         (_U_(0x1) << RTC_MODE0_INTENCLR_CMP0_Pos)      /**< (RTC_MODE0_INTENCLR) Compare 0 Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_CMP0             RTC_MODE0_INTENCLR_CMP0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_CMP0_Msk instead */
#define RTC_MODE0_INTENCLR_TAMPER_Pos       14                                             /**< (RTC_MODE0_INTENCLR) Tamper Enable Position */
#define RTC_MODE0_INTENCLR_TAMPER_Msk       (_U_(0x1) << RTC_MODE0_INTENCLR_TAMPER_Pos)    /**< (RTC_MODE0_INTENCLR) Tamper Enable Mask */
#define RTC_MODE0_INTENCLR_TAMPER           RTC_MODE0_INTENCLR_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_TAMPER_Msk instead */
#define RTC_MODE0_INTENCLR_OVF_Pos          15                                             /**< (RTC_MODE0_INTENCLR) Overflow Interrupt Enable Position */
#define RTC_MODE0_INTENCLR_OVF_Msk          (_U_(0x1) << RTC_MODE0_INTENCLR_OVF_Pos)       /**< (RTC_MODE0_INTENCLR) Overflow Interrupt Enable Mask */
#define RTC_MODE0_INTENCLR_OVF              RTC_MODE0_INTENCLR_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENCLR_OVF_Msk instead */
#define RTC_MODE0_INTENCLR_MASK             _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE0_INTENCLR) Register MASK  (Use RTC_MODE0_INTENCLR_Msk instead)  */
#define RTC_MODE0_INTENCLR_Msk              _U_(0xC1FF)                                    /**< (RTC_MODE0_INTENCLR) Register Mask  */

#define RTC_MODE0_INTENCLR_PER_Pos          0                                              /**< (RTC_MODE0_INTENCLR Position) Periodic Interval x Interrupt Enable */
#define RTC_MODE0_INTENCLR_PER_Msk          (_U_(0xFF) << RTC_MODE0_INTENCLR_PER_Pos)      /**< (RTC_MODE0_INTENCLR Mask) PER */
#define RTC_MODE0_INTENCLR_PER(value)       (RTC_MODE0_INTENCLR_PER_Msk & ((value) << RTC_MODE0_INTENCLR_PER_Pos))  
#define RTC_MODE0_INTENCLR_CMP_Pos          8                                              /**< (RTC_MODE0_INTENCLR Position) Compare x Interrupt Enable */
#define RTC_MODE0_INTENCLR_CMP_Msk          (_U_(0x1) << RTC_MODE0_INTENCLR_CMP_Pos)       /**< (RTC_MODE0_INTENCLR Mask) CMP */
#define RTC_MODE0_INTENCLR_CMP(value)       (RTC_MODE0_INTENCLR_CMP_Msk & ((value) << RTC_MODE0_INTENCLR_CMP_Pos))  

/* -------- RTC_MODE1_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE1 Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Interrupt Enable     */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Interrupt Enable     */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Interrupt Enable     */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Interrupt Enable     */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Interrupt Enable     */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Interrupt Enable     */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Interrupt Enable     */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Interrupt Enable     */
    uint16_t CMP0:1;                    /**< bit:      8  Compare 0 Interrupt Enable               */
    uint16_t CMP1:1;                    /**< bit:      9  Compare 1 Interrupt Enable               */
    uint16_t :4;                        /**< bit: 10..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Interrupt Enable     */
    uint16_t CMP:2;                     /**< bit:   8..9  Compare x Interrupt Enable               */
    uint16_t :6;                        /**< bit: 10..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_INTENCLR_OFFSET           (0x08)                                        /**<  (RTC_MODE1_INTENCLR) MODE1 Interrupt Enable Clear  Offset */
#define RTC_MODE1_INTENCLR_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE1_INTENCLR) MODE1 Interrupt Enable Clear  Reset Value */

#define RTC_MODE1_INTENCLR_PER0_Pos         0                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 0 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER0_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER0_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 0 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER0             RTC_MODE1_INTENCLR_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER0_Msk instead */
#define RTC_MODE1_INTENCLR_PER1_Pos         1                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 1 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER1_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER1_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 1 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER1             RTC_MODE1_INTENCLR_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER1_Msk instead */
#define RTC_MODE1_INTENCLR_PER2_Pos         2                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 2 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER2_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER2_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 2 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER2             RTC_MODE1_INTENCLR_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER2_Msk instead */
#define RTC_MODE1_INTENCLR_PER3_Pos         3                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 3 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER3_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER3_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 3 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER3             RTC_MODE1_INTENCLR_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER3_Msk instead */
#define RTC_MODE1_INTENCLR_PER4_Pos         4                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 4 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER4_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER4_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 4 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER4             RTC_MODE1_INTENCLR_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER4_Msk instead */
#define RTC_MODE1_INTENCLR_PER5_Pos         5                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 5 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER5_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER5_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 5 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER5             RTC_MODE1_INTENCLR_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER5_Msk instead */
#define RTC_MODE1_INTENCLR_PER6_Pos         6                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 6 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER6_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER6_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 6 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER6             RTC_MODE1_INTENCLR_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER6_Msk instead */
#define RTC_MODE1_INTENCLR_PER7_Pos         7                                              /**< (RTC_MODE1_INTENCLR) Periodic Interval 7 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_PER7_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_PER7_Pos)      /**< (RTC_MODE1_INTENCLR) Periodic Interval 7 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_PER7             RTC_MODE1_INTENCLR_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_PER7_Msk instead */
#define RTC_MODE1_INTENCLR_CMP0_Pos         8                                              /**< (RTC_MODE1_INTENCLR) Compare 0 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_CMP0_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_CMP0_Pos)      /**< (RTC_MODE1_INTENCLR) Compare 0 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_CMP0             RTC_MODE1_INTENCLR_CMP0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_CMP0_Msk instead */
#define RTC_MODE1_INTENCLR_CMP1_Pos         9                                              /**< (RTC_MODE1_INTENCLR) Compare 1 Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_CMP1_Msk         (_U_(0x1) << RTC_MODE1_INTENCLR_CMP1_Pos)      /**< (RTC_MODE1_INTENCLR) Compare 1 Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_CMP1             RTC_MODE1_INTENCLR_CMP1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_CMP1_Msk instead */
#define RTC_MODE1_INTENCLR_TAMPER_Pos       14                                             /**< (RTC_MODE1_INTENCLR) Tamper Enable Position */
#define RTC_MODE1_INTENCLR_TAMPER_Msk       (_U_(0x1) << RTC_MODE1_INTENCLR_TAMPER_Pos)    /**< (RTC_MODE1_INTENCLR) Tamper Enable Mask */
#define RTC_MODE1_INTENCLR_TAMPER           RTC_MODE1_INTENCLR_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_TAMPER_Msk instead */
#define RTC_MODE1_INTENCLR_OVF_Pos          15                                             /**< (RTC_MODE1_INTENCLR) Overflow Interrupt Enable Position */
#define RTC_MODE1_INTENCLR_OVF_Msk          (_U_(0x1) << RTC_MODE1_INTENCLR_OVF_Pos)       /**< (RTC_MODE1_INTENCLR) Overflow Interrupt Enable Mask */
#define RTC_MODE1_INTENCLR_OVF              RTC_MODE1_INTENCLR_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENCLR_OVF_Msk instead */
#define RTC_MODE1_INTENCLR_MASK             _U_(0xC3FF)                                    /**< \deprecated (RTC_MODE1_INTENCLR) Register MASK  (Use RTC_MODE1_INTENCLR_Msk instead)  */
#define RTC_MODE1_INTENCLR_Msk              _U_(0xC3FF)                                    /**< (RTC_MODE1_INTENCLR) Register Mask  */

#define RTC_MODE1_INTENCLR_PER_Pos          0                                              /**< (RTC_MODE1_INTENCLR Position) Periodic Interval x Interrupt Enable */
#define RTC_MODE1_INTENCLR_PER_Msk          (_U_(0xFF) << RTC_MODE1_INTENCLR_PER_Pos)      /**< (RTC_MODE1_INTENCLR Mask) PER */
#define RTC_MODE1_INTENCLR_PER(value)       (RTC_MODE1_INTENCLR_PER_Msk & ((value) << RTC_MODE1_INTENCLR_PER_Pos))  
#define RTC_MODE1_INTENCLR_CMP_Pos          8                                              /**< (RTC_MODE1_INTENCLR Position) Compare x Interrupt Enable */
#define RTC_MODE1_INTENCLR_CMP_Msk          (_U_(0x3) << RTC_MODE1_INTENCLR_CMP_Pos)       /**< (RTC_MODE1_INTENCLR Mask) CMP */
#define RTC_MODE1_INTENCLR_CMP(value)       (RTC_MODE1_INTENCLR_CMP_Msk & ((value) << RTC_MODE1_INTENCLR_CMP_Pos))  

/* -------- RTC_MODE2_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE2 Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Interrupt Enable     */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Interrupt Enable     */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Interrupt Enable     */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Interrupt Enable     */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Interrupt Enable     */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Interrupt Enable     */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Interrupt Enable     */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Interrupt Enable     */
    uint16_t ALARM0:1;                  /**< bit:      8  Alarm 0 Interrupt Enable                 */
    uint16_t :5;                        /**< bit:  9..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Interrupt Enable     */
    uint16_t ALARM:1;                   /**< bit:      8  Alarm x Interrupt Enable                 */
    uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE2_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_INTENCLR_OFFSET           (0x08)                                        /**<  (RTC_MODE2_INTENCLR) MODE2 Interrupt Enable Clear  Offset */
#define RTC_MODE2_INTENCLR_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE2_INTENCLR) MODE2 Interrupt Enable Clear  Reset Value */

#define RTC_MODE2_INTENCLR_PER0_Pos         0                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 0 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER0_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER0_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 0 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER0             RTC_MODE2_INTENCLR_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER0_Msk instead */
#define RTC_MODE2_INTENCLR_PER1_Pos         1                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 1 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER1_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER1_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 1 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER1             RTC_MODE2_INTENCLR_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER1_Msk instead */
#define RTC_MODE2_INTENCLR_PER2_Pos         2                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 2 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER2_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER2_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 2 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER2             RTC_MODE2_INTENCLR_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER2_Msk instead */
#define RTC_MODE2_INTENCLR_PER3_Pos         3                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 3 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER3_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER3_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 3 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER3             RTC_MODE2_INTENCLR_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER3_Msk instead */
#define RTC_MODE2_INTENCLR_PER4_Pos         4                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 4 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER4_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER4_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 4 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER4             RTC_MODE2_INTENCLR_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER4_Msk instead */
#define RTC_MODE2_INTENCLR_PER5_Pos         5                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 5 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER5_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER5_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 5 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER5             RTC_MODE2_INTENCLR_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER5_Msk instead */
#define RTC_MODE2_INTENCLR_PER6_Pos         6                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 6 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER6_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER6_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 6 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER6             RTC_MODE2_INTENCLR_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER6_Msk instead */
#define RTC_MODE2_INTENCLR_PER7_Pos         7                                              /**< (RTC_MODE2_INTENCLR) Periodic Interval 7 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_PER7_Msk         (_U_(0x1) << RTC_MODE2_INTENCLR_PER7_Pos)      /**< (RTC_MODE2_INTENCLR) Periodic Interval 7 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_PER7             RTC_MODE2_INTENCLR_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_PER7_Msk instead */
#define RTC_MODE2_INTENCLR_ALARM0_Pos       8                                              /**< (RTC_MODE2_INTENCLR) Alarm 0 Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_ALARM0_Msk       (_U_(0x1) << RTC_MODE2_INTENCLR_ALARM0_Pos)    /**< (RTC_MODE2_INTENCLR) Alarm 0 Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_ALARM0           RTC_MODE2_INTENCLR_ALARM0_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_ALARM0_Msk instead */
#define RTC_MODE2_INTENCLR_TAMPER_Pos       14                                             /**< (RTC_MODE2_INTENCLR) Tamper Enable Position */
#define RTC_MODE2_INTENCLR_TAMPER_Msk       (_U_(0x1) << RTC_MODE2_INTENCLR_TAMPER_Pos)    /**< (RTC_MODE2_INTENCLR) Tamper Enable Mask */
#define RTC_MODE2_INTENCLR_TAMPER           RTC_MODE2_INTENCLR_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_TAMPER_Msk instead */
#define RTC_MODE2_INTENCLR_OVF_Pos          15                                             /**< (RTC_MODE2_INTENCLR) Overflow Interrupt Enable Position */
#define RTC_MODE2_INTENCLR_OVF_Msk          (_U_(0x1) << RTC_MODE2_INTENCLR_OVF_Pos)       /**< (RTC_MODE2_INTENCLR) Overflow Interrupt Enable Mask */
#define RTC_MODE2_INTENCLR_OVF              RTC_MODE2_INTENCLR_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENCLR_OVF_Msk instead */
#define RTC_MODE2_INTENCLR_MASK             _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE2_INTENCLR) Register MASK  (Use RTC_MODE2_INTENCLR_Msk instead)  */
#define RTC_MODE2_INTENCLR_Msk              _U_(0xC1FF)                                    /**< (RTC_MODE2_INTENCLR) Register Mask  */

#define RTC_MODE2_INTENCLR_PER_Pos          0                                              /**< (RTC_MODE2_INTENCLR Position) Periodic Interval x Interrupt Enable */
#define RTC_MODE2_INTENCLR_PER_Msk          (_U_(0xFF) << RTC_MODE2_INTENCLR_PER_Pos)      /**< (RTC_MODE2_INTENCLR Mask) PER */
#define RTC_MODE2_INTENCLR_PER(value)       (RTC_MODE2_INTENCLR_PER_Msk & ((value) << RTC_MODE2_INTENCLR_PER_Pos))  
#define RTC_MODE2_INTENCLR_ALARM_Pos        8                                              /**< (RTC_MODE2_INTENCLR Position) Alarm x Interrupt Enable */
#define RTC_MODE2_INTENCLR_ALARM_Msk        (_U_(0x1) << RTC_MODE2_INTENCLR_ALARM_Pos)     /**< (RTC_MODE2_INTENCLR Mask) ALARM */
#define RTC_MODE2_INTENCLR_ALARM(value)     (RTC_MODE2_INTENCLR_ALARM_Msk & ((value) << RTC_MODE2_INTENCLR_ALARM_Pos))  

/* -------- RTC_MODE0_INTENSET : (RTC Offset: 0x0a) (R/W 16) MODE0 Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Interrupt Enable     */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Interrupt Enable     */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Interrupt Enable     */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Interrupt Enable     */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Interrupt Enable     */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Interrupt Enable     */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Interrupt Enable     */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Interrupt Enable     */
    uint16_t CMP0:1;                    /**< bit:      8  Compare 0 Interrupt Enable               */
    uint16_t :5;                        /**< bit:  9..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Interrupt Enable     */
    uint16_t CMP:1;                     /**< bit:      8  Compare x Interrupt Enable               */
    uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE0_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_INTENSET_OFFSET           (0x0A)                                        /**<  (RTC_MODE0_INTENSET) MODE0 Interrupt Enable Set  Offset */
#define RTC_MODE0_INTENSET_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE0_INTENSET) MODE0 Interrupt Enable Set  Reset Value */

#define RTC_MODE0_INTENSET_PER0_Pos         0                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 0 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER0_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER0_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 0 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER0             RTC_MODE0_INTENSET_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER0_Msk instead */
#define RTC_MODE0_INTENSET_PER1_Pos         1                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 1 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER1_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER1_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 1 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER1             RTC_MODE0_INTENSET_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER1_Msk instead */
#define RTC_MODE0_INTENSET_PER2_Pos         2                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 2 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER2_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER2_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 2 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER2             RTC_MODE0_INTENSET_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER2_Msk instead */
#define RTC_MODE0_INTENSET_PER3_Pos         3                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 3 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER3_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER3_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 3 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER3             RTC_MODE0_INTENSET_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER3_Msk instead */
#define RTC_MODE0_INTENSET_PER4_Pos         4                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 4 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER4_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER4_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 4 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER4             RTC_MODE0_INTENSET_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER4_Msk instead */
#define RTC_MODE0_INTENSET_PER5_Pos         5                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 5 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER5_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER5_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 5 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER5             RTC_MODE0_INTENSET_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER5_Msk instead */
#define RTC_MODE0_INTENSET_PER6_Pos         6                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 6 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER6_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER6_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 6 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER6             RTC_MODE0_INTENSET_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER6_Msk instead */
#define RTC_MODE0_INTENSET_PER7_Pos         7                                              /**< (RTC_MODE0_INTENSET) Periodic Interval 7 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_PER7_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_PER7_Pos)      /**< (RTC_MODE0_INTENSET) Periodic Interval 7 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_PER7             RTC_MODE0_INTENSET_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_PER7_Msk instead */
#define RTC_MODE0_INTENSET_CMP0_Pos         8                                              /**< (RTC_MODE0_INTENSET) Compare 0 Interrupt Enable Position */
#define RTC_MODE0_INTENSET_CMP0_Msk         (_U_(0x1) << RTC_MODE0_INTENSET_CMP0_Pos)      /**< (RTC_MODE0_INTENSET) Compare 0 Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_CMP0             RTC_MODE0_INTENSET_CMP0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_CMP0_Msk instead */
#define RTC_MODE0_INTENSET_TAMPER_Pos       14                                             /**< (RTC_MODE0_INTENSET) Tamper Enable Position */
#define RTC_MODE0_INTENSET_TAMPER_Msk       (_U_(0x1) << RTC_MODE0_INTENSET_TAMPER_Pos)    /**< (RTC_MODE0_INTENSET) Tamper Enable Mask */
#define RTC_MODE0_INTENSET_TAMPER           RTC_MODE0_INTENSET_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_TAMPER_Msk instead */
#define RTC_MODE0_INTENSET_OVF_Pos          15                                             /**< (RTC_MODE0_INTENSET) Overflow Interrupt Enable Position */
#define RTC_MODE0_INTENSET_OVF_Msk          (_U_(0x1) << RTC_MODE0_INTENSET_OVF_Pos)       /**< (RTC_MODE0_INTENSET) Overflow Interrupt Enable Mask */
#define RTC_MODE0_INTENSET_OVF              RTC_MODE0_INTENSET_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTENSET_OVF_Msk instead */
#define RTC_MODE0_INTENSET_MASK             _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE0_INTENSET) Register MASK  (Use RTC_MODE0_INTENSET_Msk instead)  */
#define RTC_MODE0_INTENSET_Msk              _U_(0xC1FF)                                    /**< (RTC_MODE0_INTENSET) Register Mask  */

#define RTC_MODE0_INTENSET_PER_Pos          0                                              /**< (RTC_MODE0_INTENSET Position) Periodic Interval x Interrupt Enable */
#define RTC_MODE0_INTENSET_PER_Msk          (_U_(0xFF) << RTC_MODE0_INTENSET_PER_Pos)      /**< (RTC_MODE0_INTENSET Mask) PER */
#define RTC_MODE0_INTENSET_PER(value)       (RTC_MODE0_INTENSET_PER_Msk & ((value) << RTC_MODE0_INTENSET_PER_Pos))  
#define RTC_MODE0_INTENSET_CMP_Pos          8                                              /**< (RTC_MODE0_INTENSET Position) Compare x Interrupt Enable */
#define RTC_MODE0_INTENSET_CMP_Msk          (_U_(0x1) << RTC_MODE0_INTENSET_CMP_Pos)       /**< (RTC_MODE0_INTENSET Mask) CMP */
#define RTC_MODE0_INTENSET_CMP(value)       (RTC_MODE0_INTENSET_CMP_Msk & ((value) << RTC_MODE0_INTENSET_CMP_Pos))  

/* -------- RTC_MODE1_INTENSET : (RTC Offset: 0x0a) (R/W 16) MODE1 Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Interrupt Enable     */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Interrupt Enable     */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Interrupt Enable     */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Interrupt Enable     */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Interrupt Enable     */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Interrupt Enable     */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Interrupt Enable     */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Interrupt Enable     */
    uint16_t CMP0:1;                    /**< bit:      8  Compare 0 Interrupt Enable               */
    uint16_t CMP1:1;                    /**< bit:      9  Compare 1 Interrupt Enable               */
    uint16_t :4;                        /**< bit: 10..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Interrupt Enable     */
    uint16_t CMP:2;                     /**< bit:   8..9  Compare x Interrupt Enable               */
    uint16_t :6;                        /**< bit: 10..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_INTENSET_OFFSET           (0x0A)                                        /**<  (RTC_MODE1_INTENSET) MODE1 Interrupt Enable Set  Offset */
#define RTC_MODE1_INTENSET_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE1_INTENSET) MODE1 Interrupt Enable Set  Reset Value */

#define RTC_MODE1_INTENSET_PER0_Pos         0                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 0 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER0_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER0_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 0 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER0             RTC_MODE1_INTENSET_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER0_Msk instead */
#define RTC_MODE1_INTENSET_PER1_Pos         1                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 1 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER1_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER1_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 1 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER1             RTC_MODE1_INTENSET_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER1_Msk instead */
#define RTC_MODE1_INTENSET_PER2_Pos         2                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 2 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER2_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER2_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 2 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER2             RTC_MODE1_INTENSET_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER2_Msk instead */
#define RTC_MODE1_INTENSET_PER3_Pos         3                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 3 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER3_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER3_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 3 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER3             RTC_MODE1_INTENSET_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER3_Msk instead */
#define RTC_MODE1_INTENSET_PER4_Pos         4                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 4 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER4_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER4_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 4 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER4             RTC_MODE1_INTENSET_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER4_Msk instead */
#define RTC_MODE1_INTENSET_PER5_Pos         5                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 5 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER5_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER5_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 5 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER5             RTC_MODE1_INTENSET_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER5_Msk instead */
#define RTC_MODE1_INTENSET_PER6_Pos         6                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 6 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER6_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER6_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 6 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER6             RTC_MODE1_INTENSET_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER6_Msk instead */
#define RTC_MODE1_INTENSET_PER7_Pos         7                                              /**< (RTC_MODE1_INTENSET) Periodic Interval 7 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_PER7_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_PER7_Pos)      /**< (RTC_MODE1_INTENSET) Periodic Interval 7 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_PER7             RTC_MODE1_INTENSET_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_PER7_Msk instead */
#define RTC_MODE1_INTENSET_CMP0_Pos         8                                              /**< (RTC_MODE1_INTENSET) Compare 0 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_CMP0_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_CMP0_Pos)      /**< (RTC_MODE1_INTENSET) Compare 0 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_CMP0             RTC_MODE1_INTENSET_CMP0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_CMP0_Msk instead */
#define RTC_MODE1_INTENSET_CMP1_Pos         9                                              /**< (RTC_MODE1_INTENSET) Compare 1 Interrupt Enable Position */
#define RTC_MODE1_INTENSET_CMP1_Msk         (_U_(0x1) << RTC_MODE1_INTENSET_CMP1_Pos)      /**< (RTC_MODE1_INTENSET) Compare 1 Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_CMP1             RTC_MODE1_INTENSET_CMP1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_CMP1_Msk instead */
#define RTC_MODE1_INTENSET_TAMPER_Pos       14                                             /**< (RTC_MODE1_INTENSET) Tamper Enable Position */
#define RTC_MODE1_INTENSET_TAMPER_Msk       (_U_(0x1) << RTC_MODE1_INTENSET_TAMPER_Pos)    /**< (RTC_MODE1_INTENSET) Tamper Enable Mask */
#define RTC_MODE1_INTENSET_TAMPER           RTC_MODE1_INTENSET_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_TAMPER_Msk instead */
#define RTC_MODE1_INTENSET_OVF_Pos          15                                             /**< (RTC_MODE1_INTENSET) Overflow Interrupt Enable Position */
#define RTC_MODE1_INTENSET_OVF_Msk          (_U_(0x1) << RTC_MODE1_INTENSET_OVF_Pos)       /**< (RTC_MODE1_INTENSET) Overflow Interrupt Enable Mask */
#define RTC_MODE1_INTENSET_OVF              RTC_MODE1_INTENSET_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTENSET_OVF_Msk instead */
#define RTC_MODE1_INTENSET_MASK             _U_(0xC3FF)                                    /**< \deprecated (RTC_MODE1_INTENSET) Register MASK  (Use RTC_MODE1_INTENSET_Msk instead)  */
#define RTC_MODE1_INTENSET_Msk              _U_(0xC3FF)                                    /**< (RTC_MODE1_INTENSET) Register Mask  */

#define RTC_MODE1_INTENSET_PER_Pos          0                                              /**< (RTC_MODE1_INTENSET Position) Periodic Interval x Interrupt Enable */
#define RTC_MODE1_INTENSET_PER_Msk          (_U_(0xFF) << RTC_MODE1_INTENSET_PER_Pos)      /**< (RTC_MODE1_INTENSET Mask) PER */
#define RTC_MODE1_INTENSET_PER(value)       (RTC_MODE1_INTENSET_PER_Msk & ((value) << RTC_MODE1_INTENSET_PER_Pos))  
#define RTC_MODE1_INTENSET_CMP_Pos          8                                              /**< (RTC_MODE1_INTENSET Position) Compare x Interrupt Enable */
#define RTC_MODE1_INTENSET_CMP_Msk          (_U_(0x3) << RTC_MODE1_INTENSET_CMP_Pos)       /**< (RTC_MODE1_INTENSET Mask) CMP */
#define RTC_MODE1_INTENSET_CMP(value)       (RTC_MODE1_INTENSET_CMP_Msk & ((value) << RTC_MODE1_INTENSET_CMP_Pos))  

/* -------- RTC_MODE2_INTENSET : (RTC Offset: 0x0a) (R/W 16) MODE2 Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0 Enable               */
    uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1 Enable               */
    uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2 Enable               */
    uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3 Enable               */
    uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4 Enable               */
    uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5 Enable               */
    uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6 Enable               */
    uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7 Enable               */
    uint16_t ALARM0:1;                  /**< bit:      8  Alarm 0 Interrupt Enable                 */
    uint16_t :5;                        /**< bit:  9..13  Reserved */
    uint16_t TAMPER:1;                  /**< bit:     14  Tamper Enable                            */
    uint16_t OVF:1;                     /**< bit:     15  Overflow Interrupt Enable                */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x Enable               */
    uint16_t ALARM:1;                   /**< bit:      8  Alarm x Interrupt Enable                 */
    uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE2_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_INTENSET_OFFSET           (0x0A)                                        /**<  (RTC_MODE2_INTENSET) MODE2 Interrupt Enable Set  Offset */
#define RTC_MODE2_INTENSET_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE2_INTENSET) MODE2 Interrupt Enable Set  Reset Value */

#define RTC_MODE2_INTENSET_PER0_Pos         0                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 0 Enable Position */
#define RTC_MODE2_INTENSET_PER0_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER0_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 0 Enable Mask */
#define RTC_MODE2_INTENSET_PER0             RTC_MODE2_INTENSET_PER0_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER0_Msk instead */
#define RTC_MODE2_INTENSET_PER1_Pos         1                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 1 Enable Position */
#define RTC_MODE2_INTENSET_PER1_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER1_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 1 Enable Mask */
#define RTC_MODE2_INTENSET_PER1             RTC_MODE2_INTENSET_PER1_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER1_Msk instead */
#define RTC_MODE2_INTENSET_PER2_Pos         2                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 2 Enable Position */
#define RTC_MODE2_INTENSET_PER2_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER2_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 2 Enable Mask */
#define RTC_MODE2_INTENSET_PER2             RTC_MODE2_INTENSET_PER2_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER2_Msk instead */
#define RTC_MODE2_INTENSET_PER3_Pos         3                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 3 Enable Position */
#define RTC_MODE2_INTENSET_PER3_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER3_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 3 Enable Mask */
#define RTC_MODE2_INTENSET_PER3             RTC_MODE2_INTENSET_PER3_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER3_Msk instead */
#define RTC_MODE2_INTENSET_PER4_Pos         4                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 4 Enable Position */
#define RTC_MODE2_INTENSET_PER4_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER4_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 4 Enable Mask */
#define RTC_MODE2_INTENSET_PER4             RTC_MODE2_INTENSET_PER4_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER4_Msk instead */
#define RTC_MODE2_INTENSET_PER5_Pos         5                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 5 Enable Position */
#define RTC_MODE2_INTENSET_PER5_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER5_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 5 Enable Mask */
#define RTC_MODE2_INTENSET_PER5             RTC_MODE2_INTENSET_PER5_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER5_Msk instead */
#define RTC_MODE2_INTENSET_PER6_Pos         6                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 6 Enable Position */
#define RTC_MODE2_INTENSET_PER6_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER6_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 6 Enable Mask */
#define RTC_MODE2_INTENSET_PER6             RTC_MODE2_INTENSET_PER6_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER6_Msk instead */
#define RTC_MODE2_INTENSET_PER7_Pos         7                                              /**< (RTC_MODE2_INTENSET) Periodic Interval 7 Enable Position */
#define RTC_MODE2_INTENSET_PER7_Msk         (_U_(0x1) << RTC_MODE2_INTENSET_PER7_Pos)      /**< (RTC_MODE2_INTENSET) Periodic Interval 7 Enable Mask */
#define RTC_MODE2_INTENSET_PER7             RTC_MODE2_INTENSET_PER7_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_PER7_Msk instead */
#define RTC_MODE2_INTENSET_ALARM0_Pos       8                                              /**< (RTC_MODE2_INTENSET) Alarm 0 Interrupt Enable Position */
#define RTC_MODE2_INTENSET_ALARM0_Msk       (_U_(0x1) << RTC_MODE2_INTENSET_ALARM0_Pos)    /**< (RTC_MODE2_INTENSET) Alarm 0 Interrupt Enable Mask */
#define RTC_MODE2_INTENSET_ALARM0           RTC_MODE2_INTENSET_ALARM0_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_ALARM0_Msk instead */
#define RTC_MODE2_INTENSET_TAMPER_Pos       14                                             /**< (RTC_MODE2_INTENSET) Tamper Enable Position */
#define RTC_MODE2_INTENSET_TAMPER_Msk       (_U_(0x1) << RTC_MODE2_INTENSET_TAMPER_Pos)    /**< (RTC_MODE2_INTENSET) Tamper Enable Mask */
#define RTC_MODE2_INTENSET_TAMPER           RTC_MODE2_INTENSET_TAMPER_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_TAMPER_Msk instead */
#define RTC_MODE2_INTENSET_OVF_Pos          15                                             /**< (RTC_MODE2_INTENSET) Overflow Interrupt Enable Position */
#define RTC_MODE2_INTENSET_OVF_Msk          (_U_(0x1) << RTC_MODE2_INTENSET_OVF_Pos)       /**< (RTC_MODE2_INTENSET) Overflow Interrupt Enable Mask */
#define RTC_MODE2_INTENSET_OVF              RTC_MODE2_INTENSET_OVF_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTENSET_OVF_Msk instead */
#define RTC_MODE2_INTENSET_MASK             _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE2_INTENSET) Register MASK  (Use RTC_MODE2_INTENSET_Msk instead)  */
#define RTC_MODE2_INTENSET_Msk              _U_(0xC1FF)                                    /**< (RTC_MODE2_INTENSET) Register Mask  */

#define RTC_MODE2_INTENSET_PER_Pos          0                                              /**< (RTC_MODE2_INTENSET Position) Periodic Interval x Enable */
#define RTC_MODE2_INTENSET_PER_Msk          (_U_(0xFF) << RTC_MODE2_INTENSET_PER_Pos)      /**< (RTC_MODE2_INTENSET Mask) PER */
#define RTC_MODE2_INTENSET_PER(value)       (RTC_MODE2_INTENSET_PER_Msk & ((value) << RTC_MODE2_INTENSET_PER_Pos))  
#define RTC_MODE2_INTENSET_ALARM_Pos        8                                              /**< (RTC_MODE2_INTENSET Position) Alarm x Interrupt Enable */
#define RTC_MODE2_INTENSET_ALARM_Msk        (_U_(0x1) << RTC_MODE2_INTENSET_ALARM_Pos)     /**< (RTC_MODE2_INTENSET Mask) ALARM */
#define RTC_MODE2_INTENSET_ALARM(value)     (RTC_MODE2_INTENSET_ALARM_Msk & ((value) << RTC_MODE2_INTENSET_ALARM_Pos))  

/* -------- RTC_MODE0_INTFLAG : (RTC Offset: 0x0c) (R/W 16) MODE0 Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0                      */
    __I uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1                      */
    __I uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2                      */
    __I uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3                      */
    __I uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4                      */
    __I uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5                      */
    __I uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6                      */
    __I uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7                      */
    __I uint16_t CMP0:1;                    /**< bit:      8  Compare 0                                */
    __I uint16_t :5;                        /**< bit:  9..13  Reserved */
    __I uint16_t TAMPER:1;                  /**< bit:     14  Tamper                                   */
    __I uint16_t OVF:1;                     /**< bit:     15  Overflow                                 */
  } bit;                                /**< Structure used for bit  access */
  struct {
    __I uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x                      */
    __I uint16_t CMP:1;                     /**< bit:      8  Compare x                                */
    __I uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE0_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_INTFLAG_OFFSET            (0x0C)                                        /**<  (RTC_MODE0_INTFLAG) MODE0 Interrupt Flag Status and Clear  Offset */
#define RTC_MODE0_INTFLAG_RESETVALUE        _U_(0x00)                                     /**<  (RTC_MODE0_INTFLAG) MODE0 Interrupt Flag Status and Clear  Reset Value */

#define RTC_MODE0_INTFLAG_PER0_Pos          0                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 0 Position */
#define RTC_MODE0_INTFLAG_PER0_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER0_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 0 Mask */
#define RTC_MODE0_INTFLAG_PER0              RTC_MODE0_INTFLAG_PER0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER0_Msk instead */
#define RTC_MODE0_INTFLAG_PER1_Pos          1                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 1 Position */
#define RTC_MODE0_INTFLAG_PER1_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER1_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 1 Mask */
#define RTC_MODE0_INTFLAG_PER1              RTC_MODE0_INTFLAG_PER1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER1_Msk instead */
#define RTC_MODE0_INTFLAG_PER2_Pos          2                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 2 Position */
#define RTC_MODE0_INTFLAG_PER2_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER2_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 2 Mask */
#define RTC_MODE0_INTFLAG_PER2              RTC_MODE0_INTFLAG_PER2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER2_Msk instead */
#define RTC_MODE0_INTFLAG_PER3_Pos          3                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 3 Position */
#define RTC_MODE0_INTFLAG_PER3_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER3_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 3 Mask */
#define RTC_MODE0_INTFLAG_PER3              RTC_MODE0_INTFLAG_PER3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER3_Msk instead */
#define RTC_MODE0_INTFLAG_PER4_Pos          4                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 4 Position */
#define RTC_MODE0_INTFLAG_PER4_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER4_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 4 Mask */
#define RTC_MODE0_INTFLAG_PER4              RTC_MODE0_INTFLAG_PER4_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER4_Msk instead */
#define RTC_MODE0_INTFLAG_PER5_Pos          5                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 5 Position */
#define RTC_MODE0_INTFLAG_PER5_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER5_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 5 Mask */
#define RTC_MODE0_INTFLAG_PER5              RTC_MODE0_INTFLAG_PER5_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER5_Msk instead */
#define RTC_MODE0_INTFLAG_PER6_Pos          6                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 6 Position */
#define RTC_MODE0_INTFLAG_PER6_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER6_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 6 Mask */
#define RTC_MODE0_INTFLAG_PER6              RTC_MODE0_INTFLAG_PER6_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER6_Msk instead */
#define RTC_MODE0_INTFLAG_PER7_Pos          7                                              /**< (RTC_MODE0_INTFLAG) Periodic Interval 7 Position */
#define RTC_MODE0_INTFLAG_PER7_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_PER7_Pos)       /**< (RTC_MODE0_INTFLAG) Periodic Interval 7 Mask */
#define RTC_MODE0_INTFLAG_PER7              RTC_MODE0_INTFLAG_PER7_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_PER7_Msk instead */
#define RTC_MODE0_INTFLAG_CMP0_Pos          8                                              /**< (RTC_MODE0_INTFLAG) Compare 0 Position */
#define RTC_MODE0_INTFLAG_CMP0_Msk          (_U_(0x1) << RTC_MODE0_INTFLAG_CMP0_Pos)       /**< (RTC_MODE0_INTFLAG) Compare 0 Mask */
#define RTC_MODE0_INTFLAG_CMP0              RTC_MODE0_INTFLAG_CMP0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_CMP0_Msk instead */
#define RTC_MODE0_INTFLAG_TAMPER_Pos        14                                             /**< (RTC_MODE0_INTFLAG) Tamper Position */
#define RTC_MODE0_INTFLAG_TAMPER_Msk        (_U_(0x1) << RTC_MODE0_INTFLAG_TAMPER_Pos)     /**< (RTC_MODE0_INTFLAG) Tamper Mask */
#define RTC_MODE0_INTFLAG_TAMPER            RTC_MODE0_INTFLAG_TAMPER_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_TAMPER_Msk instead */
#define RTC_MODE0_INTFLAG_OVF_Pos           15                                             /**< (RTC_MODE0_INTFLAG) Overflow Position */
#define RTC_MODE0_INTFLAG_OVF_Msk           (_U_(0x1) << RTC_MODE0_INTFLAG_OVF_Pos)        /**< (RTC_MODE0_INTFLAG) Overflow Mask */
#define RTC_MODE0_INTFLAG_OVF               RTC_MODE0_INTFLAG_OVF_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_INTFLAG_OVF_Msk instead */
#define RTC_MODE0_INTFLAG_MASK              _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE0_INTFLAG) Register MASK  (Use RTC_MODE0_INTFLAG_Msk instead)  */
#define RTC_MODE0_INTFLAG_Msk               _U_(0xC1FF)                                    /**< (RTC_MODE0_INTFLAG) Register Mask  */

#define RTC_MODE0_INTFLAG_PER_Pos           0                                              /**< (RTC_MODE0_INTFLAG Position) Periodic Interval x */
#define RTC_MODE0_INTFLAG_PER_Msk           (_U_(0xFF) << RTC_MODE0_INTFLAG_PER_Pos)       /**< (RTC_MODE0_INTFLAG Mask) PER */
#define RTC_MODE0_INTFLAG_PER(value)        (RTC_MODE0_INTFLAG_PER_Msk & ((value) << RTC_MODE0_INTFLAG_PER_Pos))  
#define RTC_MODE0_INTFLAG_CMP_Pos           8                                              /**< (RTC_MODE0_INTFLAG Position) Compare x */
#define RTC_MODE0_INTFLAG_CMP_Msk           (_U_(0x1) << RTC_MODE0_INTFLAG_CMP_Pos)        /**< (RTC_MODE0_INTFLAG Mask) CMP */
#define RTC_MODE0_INTFLAG_CMP(value)        (RTC_MODE0_INTFLAG_CMP_Msk & ((value) << RTC_MODE0_INTFLAG_CMP_Pos))  

/* -------- RTC_MODE1_INTFLAG : (RTC Offset: 0x0c) (R/W 16) MODE1 Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0                      */
    __I uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1                      */
    __I uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2                      */
    __I uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3                      */
    __I uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4                      */
    __I uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5                      */
    __I uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6                      */
    __I uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7                      */
    __I uint16_t CMP0:1;                    /**< bit:      8  Compare 0                                */
    __I uint16_t CMP1:1;                    /**< bit:      9  Compare 1                                */
    __I uint16_t :4;                        /**< bit: 10..13  Reserved */
    __I uint16_t TAMPER:1;                  /**< bit:     14  Tamper                                   */
    __I uint16_t OVF:1;                     /**< bit:     15  Overflow                                 */
  } bit;                                /**< Structure used for bit  access */
  struct {
    __I uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x                      */
    __I uint16_t CMP:2;                     /**< bit:   8..9  Compare x                                */
    __I uint16_t :6;                        /**< bit: 10..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_INTFLAG_OFFSET            (0x0C)                                        /**<  (RTC_MODE1_INTFLAG) MODE1 Interrupt Flag Status and Clear  Offset */
#define RTC_MODE1_INTFLAG_RESETVALUE        _U_(0x00)                                     /**<  (RTC_MODE1_INTFLAG) MODE1 Interrupt Flag Status and Clear  Reset Value */

#define RTC_MODE1_INTFLAG_PER0_Pos          0                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 0 Position */
#define RTC_MODE1_INTFLAG_PER0_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER0_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 0 Mask */
#define RTC_MODE1_INTFLAG_PER0              RTC_MODE1_INTFLAG_PER0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER0_Msk instead */
#define RTC_MODE1_INTFLAG_PER1_Pos          1                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 1 Position */
#define RTC_MODE1_INTFLAG_PER1_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER1_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 1 Mask */
#define RTC_MODE1_INTFLAG_PER1              RTC_MODE1_INTFLAG_PER1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER1_Msk instead */
#define RTC_MODE1_INTFLAG_PER2_Pos          2                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 2 Position */
#define RTC_MODE1_INTFLAG_PER2_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER2_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 2 Mask */
#define RTC_MODE1_INTFLAG_PER2              RTC_MODE1_INTFLAG_PER2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER2_Msk instead */
#define RTC_MODE1_INTFLAG_PER3_Pos          3                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 3 Position */
#define RTC_MODE1_INTFLAG_PER3_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER3_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 3 Mask */
#define RTC_MODE1_INTFLAG_PER3              RTC_MODE1_INTFLAG_PER3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER3_Msk instead */
#define RTC_MODE1_INTFLAG_PER4_Pos          4                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 4 Position */
#define RTC_MODE1_INTFLAG_PER4_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER4_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 4 Mask */
#define RTC_MODE1_INTFLAG_PER4              RTC_MODE1_INTFLAG_PER4_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER4_Msk instead */
#define RTC_MODE1_INTFLAG_PER5_Pos          5                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 5 Position */
#define RTC_MODE1_INTFLAG_PER5_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER5_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 5 Mask */
#define RTC_MODE1_INTFLAG_PER5              RTC_MODE1_INTFLAG_PER5_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER5_Msk instead */
#define RTC_MODE1_INTFLAG_PER6_Pos          6                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 6 Position */
#define RTC_MODE1_INTFLAG_PER6_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER6_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 6 Mask */
#define RTC_MODE1_INTFLAG_PER6              RTC_MODE1_INTFLAG_PER6_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER6_Msk instead */
#define RTC_MODE1_INTFLAG_PER7_Pos          7                                              /**< (RTC_MODE1_INTFLAG) Periodic Interval 7 Position */
#define RTC_MODE1_INTFLAG_PER7_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_PER7_Pos)       /**< (RTC_MODE1_INTFLAG) Periodic Interval 7 Mask */
#define RTC_MODE1_INTFLAG_PER7              RTC_MODE1_INTFLAG_PER7_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_PER7_Msk instead */
#define RTC_MODE1_INTFLAG_CMP0_Pos          8                                              /**< (RTC_MODE1_INTFLAG) Compare 0 Position */
#define RTC_MODE1_INTFLAG_CMP0_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_CMP0_Pos)       /**< (RTC_MODE1_INTFLAG) Compare 0 Mask */
#define RTC_MODE1_INTFLAG_CMP0              RTC_MODE1_INTFLAG_CMP0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_CMP0_Msk instead */
#define RTC_MODE1_INTFLAG_CMP1_Pos          9                                              /**< (RTC_MODE1_INTFLAG) Compare 1 Position */
#define RTC_MODE1_INTFLAG_CMP1_Msk          (_U_(0x1) << RTC_MODE1_INTFLAG_CMP1_Pos)       /**< (RTC_MODE1_INTFLAG) Compare 1 Mask */
#define RTC_MODE1_INTFLAG_CMP1              RTC_MODE1_INTFLAG_CMP1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_CMP1_Msk instead */
#define RTC_MODE1_INTFLAG_TAMPER_Pos        14                                             /**< (RTC_MODE1_INTFLAG) Tamper Position */
#define RTC_MODE1_INTFLAG_TAMPER_Msk        (_U_(0x1) << RTC_MODE1_INTFLAG_TAMPER_Pos)     /**< (RTC_MODE1_INTFLAG) Tamper Mask */
#define RTC_MODE1_INTFLAG_TAMPER            RTC_MODE1_INTFLAG_TAMPER_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_TAMPER_Msk instead */
#define RTC_MODE1_INTFLAG_OVF_Pos           15                                             /**< (RTC_MODE1_INTFLAG) Overflow Position */
#define RTC_MODE1_INTFLAG_OVF_Msk           (_U_(0x1) << RTC_MODE1_INTFLAG_OVF_Pos)        /**< (RTC_MODE1_INTFLAG) Overflow Mask */
#define RTC_MODE1_INTFLAG_OVF               RTC_MODE1_INTFLAG_OVF_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_INTFLAG_OVF_Msk instead */
#define RTC_MODE1_INTFLAG_MASK              _U_(0xC3FF)                                    /**< \deprecated (RTC_MODE1_INTFLAG) Register MASK  (Use RTC_MODE1_INTFLAG_Msk instead)  */
#define RTC_MODE1_INTFLAG_Msk               _U_(0xC3FF)                                    /**< (RTC_MODE1_INTFLAG) Register Mask  */

#define RTC_MODE1_INTFLAG_PER_Pos           0                                              /**< (RTC_MODE1_INTFLAG Position) Periodic Interval x */
#define RTC_MODE1_INTFLAG_PER_Msk           (_U_(0xFF) << RTC_MODE1_INTFLAG_PER_Pos)       /**< (RTC_MODE1_INTFLAG Mask) PER */
#define RTC_MODE1_INTFLAG_PER(value)        (RTC_MODE1_INTFLAG_PER_Msk & ((value) << RTC_MODE1_INTFLAG_PER_Pos))  
#define RTC_MODE1_INTFLAG_CMP_Pos           8                                              /**< (RTC_MODE1_INTFLAG Position) Compare x */
#define RTC_MODE1_INTFLAG_CMP_Msk           (_U_(0x3) << RTC_MODE1_INTFLAG_CMP_Pos)        /**< (RTC_MODE1_INTFLAG Mask) CMP */
#define RTC_MODE1_INTFLAG_CMP(value)        (RTC_MODE1_INTFLAG_CMP_Msk & ((value) << RTC_MODE1_INTFLAG_CMP_Pos))  

/* -------- RTC_MODE2_INTFLAG : (RTC Offset: 0x0c) (R/W 16) MODE2 Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;                    /**< bit:      0  Periodic Interval 0                      */
    __I uint16_t PER1:1;                    /**< bit:      1  Periodic Interval 1                      */
    __I uint16_t PER2:1;                    /**< bit:      2  Periodic Interval 2                      */
    __I uint16_t PER3:1;                    /**< bit:      3  Periodic Interval 3                      */
    __I uint16_t PER4:1;                    /**< bit:      4  Periodic Interval 4                      */
    __I uint16_t PER5:1;                    /**< bit:      5  Periodic Interval 5                      */
    __I uint16_t PER6:1;                    /**< bit:      6  Periodic Interval 6                      */
    __I uint16_t PER7:1;                    /**< bit:      7  Periodic Interval 7                      */
    __I uint16_t ALARM0:1;                  /**< bit:      8  Alarm 0                                  */
    __I uint16_t :5;                        /**< bit:  9..13  Reserved */
    __I uint16_t TAMPER:1;                  /**< bit:     14  Tamper                                   */
    __I uint16_t OVF:1;                     /**< bit:     15  Overflow                                 */
  } bit;                                /**< Structure used for bit  access */
  struct {
    __I uint16_t PER:8;                     /**< bit:   0..7  Periodic Interval x                      */
    __I uint16_t ALARM:1;                   /**< bit:      8  Alarm x                                  */
    __I uint16_t :7;                        /**< bit:  9..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE2_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_INTFLAG_OFFSET            (0x0C)                                        /**<  (RTC_MODE2_INTFLAG) MODE2 Interrupt Flag Status and Clear  Offset */
#define RTC_MODE2_INTFLAG_RESETVALUE        _U_(0x00)                                     /**<  (RTC_MODE2_INTFLAG) MODE2 Interrupt Flag Status and Clear  Reset Value */

#define RTC_MODE2_INTFLAG_PER0_Pos          0                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 0 Position */
#define RTC_MODE2_INTFLAG_PER0_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER0_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 0 Mask */
#define RTC_MODE2_INTFLAG_PER0              RTC_MODE2_INTFLAG_PER0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER0_Msk instead */
#define RTC_MODE2_INTFLAG_PER1_Pos          1                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 1 Position */
#define RTC_MODE2_INTFLAG_PER1_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER1_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 1 Mask */
#define RTC_MODE2_INTFLAG_PER1              RTC_MODE2_INTFLAG_PER1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER1_Msk instead */
#define RTC_MODE2_INTFLAG_PER2_Pos          2                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 2 Position */
#define RTC_MODE2_INTFLAG_PER2_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER2_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 2 Mask */
#define RTC_MODE2_INTFLAG_PER2              RTC_MODE2_INTFLAG_PER2_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER2_Msk instead */
#define RTC_MODE2_INTFLAG_PER3_Pos          3                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 3 Position */
#define RTC_MODE2_INTFLAG_PER3_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER3_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 3 Mask */
#define RTC_MODE2_INTFLAG_PER3              RTC_MODE2_INTFLAG_PER3_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER3_Msk instead */
#define RTC_MODE2_INTFLAG_PER4_Pos          4                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 4 Position */
#define RTC_MODE2_INTFLAG_PER4_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER4_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 4 Mask */
#define RTC_MODE2_INTFLAG_PER4              RTC_MODE2_INTFLAG_PER4_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER4_Msk instead */
#define RTC_MODE2_INTFLAG_PER5_Pos          5                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 5 Position */
#define RTC_MODE2_INTFLAG_PER5_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER5_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 5 Mask */
#define RTC_MODE2_INTFLAG_PER5              RTC_MODE2_INTFLAG_PER5_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER5_Msk instead */
#define RTC_MODE2_INTFLAG_PER6_Pos          6                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 6 Position */
#define RTC_MODE2_INTFLAG_PER6_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER6_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 6 Mask */
#define RTC_MODE2_INTFLAG_PER6              RTC_MODE2_INTFLAG_PER6_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER6_Msk instead */
#define RTC_MODE2_INTFLAG_PER7_Pos          7                                              /**< (RTC_MODE2_INTFLAG) Periodic Interval 7 Position */
#define RTC_MODE2_INTFLAG_PER7_Msk          (_U_(0x1) << RTC_MODE2_INTFLAG_PER7_Pos)       /**< (RTC_MODE2_INTFLAG) Periodic Interval 7 Mask */
#define RTC_MODE2_INTFLAG_PER7              RTC_MODE2_INTFLAG_PER7_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_PER7_Msk instead */
#define RTC_MODE2_INTFLAG_ALARM0_Pos        8                                              /**< (RTC_MODE2_INTFLAG) Alarm 0 Position */
#define RTC_MODE2_INTFLAG_ALARM0_Msk        (_U_(0x1) << RTC_MODE2_INTFLAG_ALARM0_Pos)     /**< (RTC_MODE2_INTFLAG) Alarm 0 Mask */
#define RTC_MODE2_INTFLAG_ALARM0            RTC_MODE2_INTFLAG_ALARM0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_ALARM0_Msk instead */
#define RTC_MODE2_INTFLAG_TAMPER_Pos        14                                             /**< (RTC_MODE2_INTFLAG) Tamper Position */
#define RTC_MODE2_INTFLAG_TAMPER_Msk        (_U_(0x1) << RTC_MODE2_INTFLAG_TAMPER_Pos)     /**< (RTC_MODE2_INTFLAG) Tamper Mask */
#define RTC_MODE2_INTFLAG_TAMPER            RTC_MODE2_INTFLAG_TAMPER_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_TAMPER_Msk instead */
#define RTC_MODE2_INTFLAG_OVF_Pos           15                                             /**< (RTC_MODE2_INTFLAG) Overflow Position */
#define RTC_MODE2_INTFLAG_OVF_Msk           (_U_(0x1) << RTC_MODE2_INTFLAG_OVF_Pos)        /**< (RTC_MODE2_INTFLAG) Overflow Mask */
#define RTC_MODE2_INTFLAG_OVF               RTC_MODE2_INTFLAG_OVF_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_INTFLAG_OVF_Msk instead */
#define RTC_MODE2_INTFLAG_MASK              _U_(0xC1FF)                                    /**< \deprecated (RTC_MODE2_INTFLAG) Register MASK  (Use RTC_MODE2_INTFLAG_Msk instead)  */
#define RTC_MODE2_INTFLAG_Msk               _U_(0xC1FF)                                    /**< (RTC_MODE2_INTFLAG) Register Mask  */

#define RTC_MODE2_INTFLAG_PER_Pos           0                                              /**< (RTC_MODE2_INTFLAG Position) Periodic Interval x */
#define RTC_MODE2_INTFLAG_PER_Msk           (_U_(0xFF) << RTC_MODE2_INTFLAG_PER_Pos)       /**< (RTC_MODE2_INTFLAG Mask) PER */
#define RTC_MODE2_INTFLAG_PER(value)        (RTC_MODE2_INTFLAG_PER_Msk & ((value) << RTC_MODE2_INTFLAG_PER_Pos))  
#define RTC_MODE2_INTFLAG_ALARM_Pos         8                                              /**< (RTC_MODE2_INTFLAG Position) Alarm x */
#define RTC_MODE2_INTFLAG_ALARM_Msk         (_U_(0x1) << RTC_MODE2_INTFLAG_ALARM_Pos)      /**< (RTC_MODE2_INTFLAG Mask) ALARM */
#define RTC_MODE2_INTFLAG_ALARM(value)      (RTC_MODE2_INTFLAG_ALARM_Msk & ((value) << RTC_MODE2_INTFLAG_ALARM_Pos))  

/* -------- RTC_DBGCTRL : (RTC Offset: 0x0e) (R/W 8) Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGRUN:1;                  /**< bit:      0  Run During Debug                         */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} RTC_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_DBGCTRL_OFFSET                  (0x0E)                                        /**<  (RTC_DBGCTRL) Debug Control  Offset */
#define RTC_DBGCTRL_RESETVALUE              _U_(0x00)                                     /**<  (RTC_DBGCTRL) Debug Control  Reset Value */

#define RTC_DBGCTRL_DBGRUN_Pos              0                                              /**< (RTC_DBGCTRL) Run During Debug Position */
#define RTC_DBGCTRL_DBGRUN_Msk              (_U_(0x1) << RTC_DBGCTRL_DBGRUN_Pos)           /**< (RTC_DBGCTRL) Run During Debug Mask */
#define RTC_DBGCTRL_DBGRUN                  RTC_DBGCTRL_DBGRUN_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_DBGCTRL_DBGRUN_Msk instead */
#define RTC_DBGCTRL_MASK                    _U_(0x01)                                      /**< \deprecated (RTC_DBGCTRL) Register MASK  (Use RTC_DBGCTRL_Msk instead)  */
#define RTC_DBGCTRL_Msk                     _U_(0x01)                                      /**< (RTC_DBGCTRL) Register Mask  */


/* -------- RTC_MODE0_SYNCBUSY : (RTC Offset: 0x10) (R/ 32) MODE0 Synchronization Busy Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Busy                      */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Bit Busy                          */
    uint32_t FREQCORR:1;                /**< bit:      2  FREQCORR Register Busy                   */
    uint32_t COUNT:1;                   /**< bit:      3  COUNT Register Busy                      */
    uint32_t :1;                        /**< bit:      4  Reserved */
    uint32_t COMP0:1;                   /**< bit:      5  COMP 0 Register Busy                     */
    uint32_t :9;                        /**< bit:  6..14  Reserved */
    uint32_t COUNTSYNC:1;               /**< bit:     15  Count Synchronization Enable Bit Busy    */
    uint32_t GP0:1;                     /**< bit:     16  General Purpose 0 Register Busy          */
    uint32_t GP1:1;                     /**< bit:     17  General Purpose 1 Register Busy          */
    uint32_t :14;                       /**< bit: 18..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :5;                        /**< bit:   0..4  Reserved */
    uint32_t COMP:1;                    /**< bit:      5  COMP x Register Busy                     */
    uint32_t :10;                       /**< bit:  6..15  Reserved */
    uint32_t GP:2;                      /**< bit: 16..17  General Purpose x Register Busy          */
    uint32_t :14;                       /**< bit: 18..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE0_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_SYNCBUSY_OFFSET           (0x10)                                        /**<  (RTC_MODE0_SYNCBUSY) MODE0 Synchronization Busy Status  Offset */
#define RTC_MODE0_SYNCBUSY_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE0_SYNCBUSY) MODE0 Synchronization Busy Status  Reset Value */

#define RTC_MODE0_SYNCBUSY_SWRST_Pos        0                                              /**< (RTC_MODE0_SYNCBUSY) Software Reset Busy Position */
#define RTC_MODE0_SYNCBUSY_SWRST_Msk        (_U_(0x1) << RTC_MODE0_SYNCBUSY_SWRST_Pos)     /**< (RTC_MODE0_SYNCBUSY) Software Reset Busy Mask */
#define RTC_MODE0_SYNCBUSY_SWRST            RTC_MODE0_SYNCBUSY_SWRST_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_SWRST_Msk instead */
#define RTC_MODE0_SYNCBUSY_ENABLE_Pos       1                                              /**< (RTC_MODE0_SYNCBUSY) Enable Bit Busy Position */
#define RTC_MODE0_SYNCBUSY_ENABLE_Msk       (_U_(0x1) << RTC_MODE0_SYNCBUSY_ENABLE_Pos)    /**< (RTC_MODE0_SYNCBUSY) Enable Bit Busy Mask */
#define RTC_MODE0_SYNCBUSY_ENABLE           RTC_MODE0_SYNCBUSY_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_ENABLE_Msk instead */
#define RTC_MODE0_SYNCBUSY_FREQCORR_Pos     2                                              /**< (RTC_MODE0_SYNCBUSY) FREQCORR Register Busy Position */
#define RTC_MODE0_SYNCBUSY_FREQCORR_Msk     (_U_(0x1) << RTC_MODE0_SYNCBUSY_FREQCORR_Pos)  /**< (RTC_MODE0_SYNCBUSY) FREQCORR Register Busy Mask */
#define RTC_MODE0_SYNCBUSY_FREQCORR         RTC_MODE0_SYNCBUSY_FREQCORR_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_FREQCORR_Msk instead */
#define RTC_MODE0_SYNCBUSY_COUNT_Pos        3                                              /**< (RTC_MODE0_SYNCBUSY) COUNT Register Busy Position */
#define RTC_MODE0_SYNCBUSY_COUNT_Msk        (_U_(0x1) << RTC_MODE0_SYNCBUSY_COUNT_Pos)     /**< (RTC_MODE0_SYNCBUSY) COUNT Register Busy Mask */
#define RTC_MODE0_SYNCBUSY_COUNT            RTC_MODE0_SYNCBUSY_COUNT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_COUNT_Msk instead */
#define RTC_MODE0_SYNCBUSY_COMP0_Pos        5                                              /**< (RTC_MODE0_SYNCBUSY) COMP 0 Register Busy Position */
#define RTC_MODE0_SYNCBUSY_COMP0_Msk        (_U_(0x1) << RTC_MODE0_SYNCBUSY_COMP0_Pos)     /**< (RTC_MODE0_SYNCBUSY) COMP 0 Register Busy Mask */
#define RTC_MODE0_SYNCBUSY_COMP0            RTC_MODE0_SYNCBUSY_COMP0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_COMP0_Msk instead */
#define RTC_MODE0_SYNCBUSY_COUNTSYNC_Pos    15                                             /**< (RTC_MODE0_SYNCBUSY) Count Synchronization Enable Bit Busy Position */
#define RTC_MODE0_SYNCBUSY_COUNTSYNC_Msk    (_U_(0x1) << RTC_MODE0_SYNCBUSY_COUNTSYNC_Pos)  /**< (RTC_MODE0_SYNCBUSY) Count Synchronization Enable Bit Busy Mask */
#define RTC_MODE0_SYNCBUSY_COUNTSYNC        RTC_MODE0_SYNCBUSY_COUNTSYNC_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_COUNTSYNC_Msk instead */
#define RTC_MODE0_SYNCBUSY_GP0_Pos          16                                             /**< (RTC_MODE0_SYNCBUSY) General Purpose 0 Register Busy Position */
#define RTC_MODE0_SYNCBUSY_GP0_Msk          (_U_(0x1) << RTC_MODE0_SYNCBUSY_GP0_Pos)       /**< (RTC_MODE0_SYNCBUSY) General Purpose 0 Register Busy Mask */
#define RTC_MODE0_SYNCBUSY_GP0              RTC_MODE0_SYNCBUSY_GP0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_GP0_Msk instead */
#define RTC_MODE0_SYNCBUSY_GP1_Pos          17                                             /**< (RTC_MODE0_SYNCBUSY) General Purpose 1 Register Busy Position */
#define RTC_MODE0_SYNCBUSY_GP1_Msk          (_U_(0x1) << RTC_MODE0_SYNCBUSY_GP1_Pos)       /**< (RTC_MODE0_SYNCBUSY) General Purpose 1 Register Busy Mask */
#define RTC_MODE0_SYNCBUSY_GP1              RTC_MODE0_SYNCBUSY_GP1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE0_SYNCBUSY_GP1_Msk instead */
#define RTC_MODE0_SYNCBUSY_MASK             _U_(0x3802F)                                   /**< \deprecated (RTC_MODE0_SYNCBUSY) Register MASK  (Use RTC_MODE0_SYNCBUSY_Msk instead)  */
#define RTC_MODE0_SYNCBUSY_Msk              _U_(0x3802F)                                   /**< (RTC_MODE0_SYNCBUSY) Register Mask  */

#define RTC_MODE0_SYNCBUSY_COMP_Pos         5                                              /**< (RTC_MODE0_SYNCBUSY Position) COMP x Register Busy */
#define RTC_MODE0_SYNCBUSY_COMP_Msk         (_U_(0x1) << RTC_MODE0_SYNCBUSY_COMP_Pos)      /**< (RTC_MODE0_SYNCBUSY Mask) COMP */
#define RTC_MODE0_SYNCBUSY_COMP(value)      (RTC_MODE0_SYNCBUSY_COMP_Msk & ((value) << RTC_MODE0_SYNCBUSY_COMP_Pos))  
#define RTC_MODE0_SYNCBUSY_GP_Pos           16                                             /**< (RTC_MODE0_SYNCBUSY Position) General Purpose x Register Busy */
#define RTC_MODE0_SYNCBUSY_GP_Msk           (_U_(0x3) << RTC_MODE0_SYNCBUSY_GP_Pos)        /**< (RTC_MODE0_SYNCBUSY Mask) GP */
#define RTC_MODE0_SYNCBUSY_GP(value)        (RTC_MODE0_SYNCBUSY_GP_Msk & ((value) << RTC_MODE0_SYNCBUSY_GP_Pos))  

/* -------- RTC_MODE1_SYNCBUSY : (RTC Offset: 0x10) (R/ 32) MODE1 Synchronization Busy Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Bit Busy                  */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Bit Busy                          */
    uint32_t FREQCORR:1;                /**< bit:      2  FREQCORR Register Busy                   */
    uint32_t COUNT:1;                   /**< bit:      3  COUNT Register Busy                      */
    uint32_t PER:1;                     /**< bit:      4  PER Register Busy                        */
    uint32_t COMP0:1;                   /**< bit:      5  COMP 0 Register Busy                     */
    uint32_t COMP1:1;                   /**< bit:      6  COMP 1 Register Busy                     */
    uint32_t :8;                        /**< bit:  7..14  Reserved */
    uint32_t COUNTSYNC:1;               /**< bit:     15  Count Synchronization Enable Bit Busy    */
    uint32_t GP0:1;                     /**< bit:     16  General Purpose 0 Register Busy          */
    uint32_t GP1:1;                     /**< bit:     17  General Purpose 1 Register Busy          */
    uint32_t :14;                       /**< bit: 18..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :5;                        /**< bit:   0..4  Reserved */
    uint32_t COMP:2;                    /**< bit:   5..6  COMP x Register Busy                     */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t GP:2;                      /**< bit: 16..17  General Purpose x Register Busy          */
    uint32_t :14;                       /**< bit: 18..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE1_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_SYNCBUSY_OFFSET           (0x10)                                        /**<  (RTC_MODE1_SYNCBUSY) MODE1 Synchronization Busy Status  Offset */
#define RTC_MODE1_SYNCBUSY_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE1_SYNCBUSY) MODE1 Synchronization Busy Status  Reset Value */

#define RTC_MODE1_SYNCBUSY_SWRST_Pos        0                                              /**< (RTC_MODE1_SYNCBUSY) Software Reset Bit Busy Position */
#define RTC_MODE1_SYNCBUSY_SWRST_Msk        (_U_(0x1) << RTC_MODE1_SYNCBUSY_SWRST_Pos)     /**< (RTC_MODE1_SYNCBUSY) Software Reset Bit Busy Mask */
#define RTC_MODE1_SYNCBUSY_SWRST            RTC_MODE1_SYNCBUSY_SWRST_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_SWRST_Msk instead */
#define RTC_MODE1_SYNCBUSY_ENABLE_Pos       1                                              /**< (RTC_MODE1_SYNCBUSY) Enable Bit Busy Position */
#define RTC_MODE1_SYNCBUSY_ENABLE_Msk       (_U_(0x1) << RTC_MODE1_SYNCBUSY_ENABLE_Pos)    /**< (RTC_MODE1_SYNCBUSY) Enable Bit Busy Mask */
#define RTC_MODE1_SYNCBUSY_ENABLE           RTC_MODE1_SYNCBUSY_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_ENABLE_Msk instead */
#define RTC_MODE1_SYNCBUSY_FREQCORR_Pos     2                                              /**< (RTC_MODE1_SYNCBUSY) FREQCORR Register Busy Position */
#define RTC_MODE1_SYNCBUSY_FREQCORR_Msk     (_U_(0x1) << RTC_MODE1_SYNCBUSY_FREQCORR_Pos)  /**< (RTC_MODE1_SYNCBUSY) FREQCORR Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_FREQCORR         RTC_MODE1_SYNCBUSY_FREQCORR_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_FREQCORR_Msk instead */
#define RTC_MODE1_SYNCBUSY_COUNT_Pos        3                                              /**< (RTC_MODE1_SYNCBUSY) COUNT Register Busy Position */
#define RTC_MODE1_SYNCBUSY_COUNT_Msk        (_U_(0x1) << RTC_MODE1_SYNCBUSY_COUNT_Pos)     /**< (RTC_MODE1_SYNCBUSY) COUNT Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_COUNT            RTC_MODE1_SYNCBUSY_COUNT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_COUNT_Msk instead */
#define RTC_MODE1_SYNCBUSY_PER_Pos          4                                              /**< (RTC_MODE1_SYNCBUSY) PER Register Busy Position */
#define RTC_MODE1_SYNCBUSY_PER_Msk          (_U_(0x1) << RTC_MODE1_SYNCBUSY_PER_Pos)       /**< (RTC_MODE1_SYNCBUSY) PER Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_PER              RTC_MODE1_SYNCBUSY_PER_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_PER_Msk instead */
#define RTC_MODE1_SYNCBUSY_COMP0_Pos        5                                              /**< (RTC_MODE1_SYNCBUSY) COMP 0 Register Busy Position */
#define RTC_MODE1_SYNCBUSY_COMP0_Msk        (_U_(0x1) << RTC_MODE1_SYNCBUSY_COMP0_Pos)     /**< (RTC_MODE1_SYNCBUSY) COMP 0 Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_COMP0            RTC_MODE1_SYNCBUSY_COMP0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_COMP0_Msk instead */
#define RTC_MODE1_SYNCBUSY_COMP1_Pos        6                                              /**< (RTC_MODE1_SYNCBUSY) COMP 1 Register Busy Position */
#define RTC_MODE1_SYNCBUSY_COMP1_Msk        (_U_(0x1) << RTC_MODE1_SYNCBUSY_COMP1_Pos)     /**< (RTC_MODE1_SYNCBUSY) COMP 1 Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_COMP1            RTC_MODE1_SYNCBUSY_COMP1_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_COMP1_Msk instead */
#define RTC_MODE1_SYNCBUSY_COUNTSYNC_Pos    15                                             /**< (RTC_MODE1_SYNCBUSY) Count Synchronization Enable Bit Busy Position */
#define RTC_MODE1_SYNCBUSY_COUNTSYNC_Msk    (_U_(0x1) << RTC_MODE1_SYNCBUSY_COUNTSYNC_Pos)  /**< (RTC_MODE1_SYNCBUSY) Count Synchronization Enable Bit Busy Mask */
#define RTC_MODE1_SYNCBUSY_COUNTSYNC        RTC_MODE1_SYNCBUSY_COUNTSYNC_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_COUNTSYNC_Msk instead */
#define RTC_MODE1_SYNCBUSY_GP0_Pos          16                                             /**< (RTC_MODE1_SYNCBUSY) General Purpose 0 Register Busy Position */
#define RTC_MODE1_SYNCBUSY_GP0_Msk          (_U_(0x1) << RTC_MODE1_SYNCBUSY_GP0_Pos)       /**< (RTC_MODE1_SYNCBUSY) General Purpose 0 Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_GP0              RTC_MODE1_SYNCBUSY_GP0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_GP0_Msk instead */
#define RTC_MODE1_SYNCBUSY_GP1_Pos          17                                             /**< (RTC_MODE1_SYNCBUSY) General Purpose 1 Register Busy Position */
#define RTC_MODE1_SYNCBUSY_GP1_Msk          (_U_(0x1) << RTC_MODE1_SYNCBUSY_GP1_Pos)       /**< (RTC_MODE1_SYNCBUSY) General Purpose 1 Register Busy Mask */
#define RTC_MODE1_SYNCBUSY_GP1              RTC_MODE1_SYNCBUSY_GP1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE1_SYNCBUSY_GP1_Msk instead */
#define RTC_MODE1_SYNCBUSY_MASK             _U_(0x3807F)                                   /**< \deprecated (RTC_MODE1_SYNCBUSY) Register MASK  (Use RTC_MODE1_SYNCBUSY_Msk instead)  */
#define RTC_MODE1_SYNCBUSY_Msk              _U_(0x3807F)                                   /**< (RTC_MODE1_SYNCBUSY) Register Mask  */

#define RTC_MODE1_SYNCBUSY_COMP_Pos         5                                              /**< (RTC_MODE1_SYNCBUSY Position) COMP x Register Busy */
#define RTC_MODE1_SYNCBUSY_COMP_Msk         (_U_(0x3) << RTC_MODE1_SYNCBUSY_COMP_Pos)      /**< (RTC_MODE1_SYNCBUSY Mask) COMP */
#define RTC_MODE1_SYNCBUSY_COMP(value)      (RTC_MODE1_SYNCBUSY_COMP_Msk & ((value) << RTC_MODE1_SYNCBUSY_COMP_Pos))  
#define RTC_MODE1_SYNCBUSY_GP_Pos           16                                             /**< (RTC_MODE1_SYNCBUSY Position) General Purpose x Register Busy */
#define RTC_MODE1_SYNCBUSY_GP_Msk           (_U_(0x3) << RTC_MODE1_SYNCBUSY_GP_Pos)        /**< (RTC_MODE1_SYNCBUSY Mask) GP */
#define RTC_MODE1_SYNCBUSY_GP(value)        (RTC_MODE1_SYNCBUSY_GP_Msk & ((value) << RTC_MODE1_SYNCBUSY_GP_Pos))  

/* -------- RTC_MODE2_SYNCBUSY : (RTC Offset: 0x10) (R/ 32) MODE2 Synchronization Busy Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Bit Busy                  */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable Bit Busy                          */
    uint32_t FREQCORR:1;                /**< bit:      2  FREQCORR Register Busy                   */
    uint32_t CLOCK:1;                   /**< bit:      3  CLOCK Register Busy                      */
    uint32_t :1;                        /**< bit:      4  Reserved */
    uint32_t ALARM0:1;                  /**< bit:      5  ALARM 0 Register Busy                    */
    uint32_t :5;                        /**< bit:  6..10  Reserved */
    uint32_t MASK0:1;                   /**< bit:     11  MASK 0 Register Busy                     */
    uint32_t :3;                        /**< bit: 12..14  Reserved */
    uint32_t CLOCKSYNC:1;               /**< bit:     15  Clock Synchronization Enable Bit Busy    */
    uint32_t GP0:1;                     /**< bit:     16  General Purpose 0 Register Busy          */
    uint32_t GP1:1;                     /**< bit:     17  General Purpose 1 Register Busy          */
    uint32_t :14;                       /**< bit: 18..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :5;                        /**< bit:   0..4  Reserved */
    uint32_t ALARM:1;                   /**< bit:      5  ALARM x Register Busy                    */
    uint32_t :5;                        /**< bit:  6..10  Reserved */
    uint32_t MASK:1;                    /**< bit:     11  MASK x Register Busy                     */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t GP:2;                      /**< bit: 16..17  General Purpose x Register Busy          */
    uint32_t :14;                       /**< bit: 18..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE2_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_SYNCBUSY_OFFSET           (0x10)                                        /**<  (RTC_MODE2_SYNCBUSY) MODE2 Synchronization Busy Status  Offset */
#define RTC_MODE2_SYNCBUSY_RESETVALUE       _U_(0x00)                                     /**<  (RTC_MODE2_SYNCBUSY) MODE2 Synchronization Busy Status  Reset Value */

#define RTC_MODE2_SYNCBUSY_SWRST_Pos        0                                              /**< (RTC_MODE2_SYNCBUSY) Software Reset Bit Busy Position */
#define RTC_MODE2_SYNCBUSY_SWRST_Msk        (_U_(0x1) << RTC_MODE2_SYNCBUSY_SWRST_Pos)     /**< (RTC_MODE2_SYNCBUSY) Software Reset Bit Busy Mask */
#define RTC_MODE2_SYNCBUSY_SWRST            RTC_MODE2_SYNCBUSY_SWRST_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_SWRST_Msk instead */
#define RTC_MODE2_SYNCBUSY_ENABLE_Pos       1                                              /**< (RTC_MODE2_SYNCBUSY) Enable Bit Busy Position */
#define RTC_MODE2_SYNCBUSY_ENABLE_Msk       (_U_(0x1) << RTC_MODE2_SYNCBUSY_ENABLE_Pos)    /**< (RTC_MODE2_SYNCBUSY) Enable Bit Busy Mask */
#define RTC_MODE2_SYNCBUSY_ENABLE           RTC_MODE2_SYNCBUSY_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_ENABLE_Msk instead */
#define RTC_MODE2_SYNCBUSY_FREQCORR_Pos     2                                              /**< (RTC_MODE2_SYNCBUSY) FREQCORR Register Busy Position */
#define RTC_MODE2_SYNCBUSY_FREQCORR_Msk     (_U_(0x1) << RTC_MODE2_SYNCBUSY_FREQCORR_Pos)  /**< (RTC_MODE2_SYNCBUSY) FREQCORR Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_FREQCORR         RTC_MODE2_SYNCBUSY_FREQCORR_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_FREQCORR_Msk instead */
#define RTC_MODE2_SYNCBUSY_CLOCK_Pos        3                                              /**< (RTC_MODE2_SYNCBUSY) CLOCK Register Busy Position */
#define RTC_MODE2_SYNCBUSY_CLOCK_Msk        (_U_(0x1) << RTC_MODE2_SYNCBUSY_CLOCK_Pos)     /**< (RTC_MODE2_SYNCBUSY) CLOCK Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_CLOCK            RTC_MODE2_SYNCBUSY_CLOCK_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_CLOCK_Msk instead */
#define RTC_MODE2_SYNCBUSY_ALARM0_Pos       5                                              /**< (RTC_MODE2_SYNCBUSY) ALARM 0 Register Busy Position */
#define RTC_MODE2_SYNCBUSY_ALARM0_Msk       (_U_(0x1) << RTC_MODE2_SYNCBUSY_ALARM0_Pos)    /**< (RTC_MODE2_SYNCBUSY) ALARM 0 Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_ALARM0           RTC_MODE2_SYNCBUSY_ALARM0_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_ALARM0_Msk instead */
#define RTC_MODE2_SYNCBUSY_MASK0_Pos        11                                             /**< (RTC_MODE2_SYNCBUSY) MASK 0 Register Busy Position */
#define RTC_MODE2_SYNCBUSY_MASK0_Msk        (_U_(0x1) << RTC_MODE2_SYNCBUSY_MASK0_Pos)     /**< (RTC_MODE2_SYNCBUSY) MASK 0 Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_MASK0            RTC_MODE2_SYNCBUSY_MASK0_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_MASK0_Msk instead */
#define RTC_MODE2_SYNCBUSY_CLOCKSYNC_Pos    15                                             /**< (RTC_MODE2_SYNCBUSY) Clock Synchronization Enable Bit Busy Position */
#define RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk    (_U_(0x1) << RTC_MODE2_SYNCBUSY_CLOCKSYNC_Pos)  /**< (RTC_MODE2_SYNCBUSY) Clock Synchronization Enable Bit Busy Mask */
#define RTC_MODE2_SYNCBUSY_CLOCKSYNC        RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk instead */
#define RTC_MODE2_SYNCBUSY_GP0_Pos          16                                             /**< (RTC_MODE2_SYNCBUSY) General Purpose 0 Register Busy Position */
#define RTC_MODE2_SYNCBUSY_GP0_Msk          (_U_(0x1) << RTC_MODE2_SYNCBUSY_GP0_Pos)       /**< (RTC_MODE2_SYNCBUSY) General Purpose 0 Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_GP0              RTC_MODE2_SYNCBUSY_GP0_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_GP0_Msk instead */
#define RTC_MODE2_SYNCBUSY_GP1_Pos          17                                             /**< (RTC_MODE2_SYNCBUSY) General Purpose 1 Register Busy Position */
#define RTC_MODE2_SYNCBUSY_GP1_Msk          (_U_(0x1) << RTC_MODE2_SYNCBUSY_GP1_Pos)       /**< (RTC_MODE2_SYNCBUSY) General Purpose 1 Register Busy Mask */
#define RTC_MODE2_SYNCBUSY_GP1              RTC_MODE2_SYNCBUSY_GP1_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_MODE2_SYNCBUSY_GP1_Msk instead */
#define RTC_MODE2_SYNCBUSY_Msk              _U_(0x3882F)                                   /**< (RTC_MODE2_SYNCBUSY) Register Mask  */

#define RTC_MODE2_SYNCBUSY_ALARM_Pos        5                                              /**< (RTC_MODE2_SYNCBUSY Position) ALARM x Register Busy */
#define RTC_MODE2_SYNCBUSY_ALARM_Msk        (_U_(0x1) << RTC_MODE2_SYNCBUSY_ALARM_Pos)     /**< (RTC_MODE2_SYNCBUSY Mask) ALARM */
#define RTC_MODE2_SYNCBUSY_ALARM(value)     (RTC_MODE2_SYNCBUSY_ALARM_Msk & ((value) << RTC_MODE2_SYNCBUSY_ALARM_Pos))  
#define RTC_MODE2_SYNCBUSY_MASK_Pos         11                                             /**< (RTC_MODE2_SYNCBUSY Position) MASK x Register Busy */
#define RTC_MODE2_SYNCBUSY_MASK_Msk         (_U_(0x1) << RTC_MODE2_SYNCBUSY_MASK_Pos)      /**< (RTC_MODE2_SYNCBUSY Mask) MASK */
#define RTC_MODE2_SYNCBUSY_MASK(value)      (RTC_MODE2_SYNCBUSY_MASK_Msk & ((value) << RTC_MODE2_SYNCBUSY_MASK_Pos))  
#define RTC_MODE2_SYNCBUSY_GP_Pos           16                                             /**< (RTC_MODE2_SYNCBUSY Position) General Purpose x Register Busy */
#define RTC_MODE2_SYNCBUSY_GP_Msk           (_U_(0x3) << RTC_MODE2_SYNCBUSY_GP_Pos)        /**< (RTC_MODE2_SYNCBUSY Mask) GP */
#define RTC_MODE2_SYNCBUSY_GP(value)        (RTC_MODE2_SYNCBUSY_GP_Msk & ((value) << RTC_MODE2_SYNCBUSY_GP_Pos))  

/* -------- RTC_FREQCORR : (RTC Offset: 0x14) (R/W 8) Frequency Correction -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  VALUE:7;                   /**< bit:   0..6  Correction Value                         */
    uint8_t  SIGN:1;                    /**< bit:      7  Correction Sign                          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} RTC_FREQCORR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_FREQCORR_OFFSET                 (0x14)                                        /**<  (RTC_FREQCORR) Frequency Correction  Offset */
#define RTC_FREQCORR_RESETVALUE             _U_(0x00)                                     /**<  (RTC_FREQCORR) Frequency Correction  Reset Value */

#define RTC_FREQCORR_VALUE_Pos              0                                              /**< (RTC_FREQCORR) Correction Value Position */
#define RTC_FREQCORR_VALUE_Msk              (_U_(0x7F) << RTC_FREQCORR_VALUE_Pos)          /**< (RTC_FREQCORR) Correction Value Mask */
#define RTC_FREQCORR_VALUE(value)           (RTC_FREQCORR_VALUE_Msk & ((value) << RTC_FREQCORR_VALUE_Pos))
#define RTC_FREQCORR_SIGN_Pos               7                                              /**< (RTC_FREQCORR) Correction Sign Position */
#define RTC_FREQCORR_SIGN_Msk               (_U_(0x1) << RTC_FREQCORR_SIGN_Pos)            /**< (RTC_FREQCORR) Correction Sign Mask */
#define RTC_FREQCORR_SIGN                   RTC_FREQCORR_SIGN_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_FREQCORR_SIGN_Msk instead */
#define RTC_FREQCORR_MASK                   _U_(0xFF)                                      /**< \deprecated (RTC_FREQCORR) Register MASK  (Use RTC_FREQCORR_Msk instead)  */
#define RTC_FREQCORR_Msk                    _U_(0xFF)                                      /**< (RTC_FREQCORR) Register Mask  */


/* -------- RTC_MODE0_COUNT : (RTC Offset: 0x18) (R/W 32) MODE0 Counter Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COUNT:32;                  /**< bit:  0..31  Counter Value                            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE0_COUNT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_COUNT_OFFSET              (0x18)                                        /**<  (RTC_MODE0_COUNT) MODE0 Counter Value  Offset */
#define RTC_MODE0_COUNT_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE0_COUNT) MODE0 Counter Value  Reset Value */

#define RTC_MODE0_COUNT_COUNT_Pos           0                                              /**< (RTC_MODE0_COUNT) Counter Value Position */
#define RTC_MODE0_COUNT_COUNT_Msk           (_U_(0xFFFFFFFF) << RTC_MODE0_COUNT_COUNT_Pos)  /**< (RTC_MODE0_COUNT) Counter Value Mask */
#define RTC_MODE0_COUNT_COUNT(value)        (RTC_MODE0_COUNT_COUNT_Msk & ((value) << RTC_MODE0_COUNT_COUNT_Pos))
#define RTC_MODE0_COUNT_MASK                _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE0_COUNT) Register MASK  (Use RTC_MODE0_COUNT_Msk instead)  */
#define RTC_MODE0_COUNT_Msk                 _U_(0xFFFFFFFF)                                /**< (RTC_MODE0_COUNT) Register Mask  */


/* -------- RTC_MODE1_COUNT : (RTC Offset: 0x18) (R/W 16) MODE1 Counter Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t COUNT:16;                  /**< bit:  0..15  Counter Value                            */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_COUNT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_COUNT_OFFSET              (0x18)                                        /**<  (RTC_MODE1_COUNT) MODE1 Counter Value  Offset */
#define RTC_MODE1_COUNT_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE1_COUNT) MODE1 Counter Value  Reset Value */

#define RTC_MODE1_COUNT_COUNT_Pos           0                                              /**< (RTC_MODE1_COUNT) Counter Value Position */
#define RTC_MODE1_COUNT_COUNT_Msk           (_U_(0xFFFF) << RTC_MODE1_COUNT_COUNT_Pos)     /**< (RTC_MODE1_COUNT) Counter Value Mask */
#define RTC_MODE1_COUNT_COUNT(value)        (RTC_MODE1_COUNT_COUNT_Msk & ((value) << RTC_MODE1_COUNT_COUNT_Pos))
#define RTC_MODE1_COUNT_MASK                _U_(0xFFFF)                                    /**< \deprecated (RTC_MODE1_COUNT) Register MASK  (Use RTC_MODE1_COUNT_Msk instead)  */
#define RTC_MODE1_COUNT_Msk                 _U_(0xFFFF)                                    /**< (RTC_MODE1_COUNT) Register Mask  */


/* -------- RTC_MODE2_CLOCK : (RTC Offset: 0x18) (R/W 32) MODE2 Clock Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SECOND:6;                  /**< bit:   0..5  Second                                   */
    uint32_t MINUTE:6;                  /**< bit:  6..11  Minute                                   */
    uint32_t HOUR:5;                    /**< bit: 12..16  Hour                                     */
    uint32_t DAY:5;                     /**< bit: 17..21  Day                                      */
    uint32_t MONTH:4;                   /**< bit: 22..25  Month                                    */
    uint32_t YEAR:6;                    /**< bit: 26..31  Year                                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE2_CLOCK_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_CLOCK_OFFSET              (0x18)                                        /**<  (RTC_MODE2_CLOCK) MODE2 Clock Value  Offset */
#define RTC_MODE2_CLOCK_RESETVALUE          _U_(0x00)                                     /**<  (RTC_MODE2_CLOCK) MODE2 Clock Value  Reset Value */

#define RTC_MODE2_CLOCK_SECOND_Pos          0                                              /**< (RTC_MODE2_CLOCK) Second Position */
#define RTC_MODE2_CLOCK_SECOND_Msk          (_U_(0x3F) << RTC_MODE2_CLOCK_SECOND_Pos)      /**< (RTC_MODE2_CLOCK) Second Mask */
#define RTC_MODE2_CLOCK_SECOND(value)       (RTC_MODE2_CLOCK_SECOND_Msk & ((value) << RTC_MODE2_CLOCK_SECOND_Pos))
#define RTC_MODE2_CLOCK_MINUTE_Pos          6                                              /**< (RTC_MODE2_CLOCK) Minute Position */
#define RTC_MODE2_CLOCK_MINUTE_Msk          (_U_(0x3F) << RTC_MODE2_CLOCK_MINUTE_Pos)      /**< (RTC_MODE2_CLOCK) Minute Mask */
#define RTC_MODE2_CLOCK_MINUTE(value)       (RTC_MODE2_CLOCK_MINUTE_Msk & ((value) << RTC_MODE2_CLOCK_MINUTE_Pos))
#define RTC_MODE2_CLOCK_HOUR_Pos            12                                             /**< (RTC_MODE2_CLOCK) Hour Position */
#define RTC_MODE2_CLOCK_HOUR_Msk            (_U_(0x1F) << RTC_MODE2_CLOCK_HOUR_Pos)        /**< (RTC_MODE2_CLOCK) Hour Mask */
#define RTC_MODE2_CLOCK_HOUR(value)         (RTC_MODE2_CLOCK_HOUR_Msk & ((value) << RTC_MODE2_CLOCK_HOUR_Pos))
#define RTC_MODE2_CLOCK_DAY_Pos             17                                             /**< (RTC_MODE2_CLOCK) Day Position */
#define RTC_MODE2_CLOCK_DAY_Msk             (_U_(0x1F) << RTC_MODE2_CLOCK_DAY_Pos)         /**< (RTC_MODE2_CLOCK) Day Mask */
#define RTC_MODE2_CLOCK_DAY(value)          (RTC_MODE2_CLOCK_DAY_Msk & ((value) << RTC_MODE2_CLOCK_DAY_Pos))
#define RTC_MODE2_CLOCK_MONTH_Pos           22                                             /**< (RTC_MODE2_CLOCK) Month Position */
#define RTC_MODE2_CLOCK_MONTH_Msk           (_U_(0xF) << RTC_MODE2_CLOCK_MONTH_Pos)        /**< (RTC_MODE2_CLOCK) Month Mask */
#define RTC_MODE2_CLOCK_MONTH(value)        (RTC_MODE2_CLOCK_MONTH_Msk & ((value) << RTC_MODE2_CLOCK_MONTH_Pos))
#define RTC_MODE2_CLOCK_YEAR_Pos            26                                             /**< (RTC_MODE2_CLOCK) Year Position */
#define RTC_MODE2_CLOCK_YEAR_Msk            (_U_(0x3F) << RTC_MODE2_CLOCK_YEAR_Pos)        /**< (RTC_MODE2_CLOCK) Year Mask */
#define RTC_MODE2_CLOCK_YEAR(value)         (RTC_MODE2_CLOCK_YEAR_Msk & ((value) << RTC_MODE2_CLOCK_YEAR_Pos))
#define RTC_MODE2_CLOCK_MASK                _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE2_CLOCK) Register MASK  (Use RTC_MODE2_CLOCK_Msk instead)  */
#define RTC_MODE2_CLOCK_Msk                 _U_(0xFFFFFFFF)                                /**< (RTC_MODE2_CLOCK) Register Mask  */


/* -------- RTC_MODE1_PER : (RTC Offset: 0x1c) (R/W 16) MODE1 Counter Period -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PER:16;                    /**< bit:  0..15  Counter Period                           */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_PER_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_PER_OFFSET                (0x1C)                                        /**<  (RTC_MODE1_PER) MODE1 Counter Period  Offset */
#define RTC_MODE1_PER_RESETVALUE            _U_(0x00)                                     /**<  (RTC_MODE1_PER) MODE1 Counter Period  Reset Value */

#define RTC_MODE1_PER_PER_Pos               0                                              /**< (RTC_MODE1_PER) Counter Period Position */
#define RTC_MODE1_PER_PER_Msk               (_U_(0xFFFF) << RTC_MODE1_PER_PER_Pos)         /**< (RTC_MODE1_PER) Counter Period Mask */
#define RTC_MODE1_PER_PER(value)            (RTC_MODE1_PER_PER_Msk & ((value) << RTC_MODE1_PER_PER_Pos))
#define RTC_MODE1_PER_MASK                  _U_(0xFFFF)                                    /**< \deprecated (RTC_MODE1_PER) Register MASK  (Use RTC_MODE1_PER_Msk instead)  */
#define RTC_MODE1_PER_Msk                   _U_(0xFFFF)                                    /**< (RTC_MODE1_PER) Register Mask  */


/* -------- RTC_MODE0_COMP : (RTC Offset: 0x20) (R/W 32) MODE0 Compare n Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COMP:32;                   /**< bit:  0..31  Compare Value                            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE0_COMP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_COMP_OFFSET               (0x20)                                        /**<  (RTC_MODE0_COMP) MODE0 Compare n Value  Offset */
#define RTC_MODE0_COMP_RESETVALUE           _U_(0x00)                                     /**<  (RTC_MODE0_COMP) MODE0 Compare n Value  Reset Value */

#define RTC_MODE0_COMP_COMP_Pos             0                                              /**< (RTC_MODE0_COMP) Compare Value Position */
#define RTC_MODE0_COMP_COMP_Msk             (_U_(0xFFFFFFFF) << RTC_MODE0_COMP_COMP_Pos)   /**< (RTC_MODE0_COMP) Compare Value Mask */
#define RTC_MODE0_COMP_COMP(value)          (RTC_MODE0_COMP_COMP_Msk & ((value) << RTC_MODE0_COMP_COMP_Pos))
#define RTC_MODE0_COMP_MASK                 _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE0_COMP) Register MASK  (Use RTC_MODE0_COMP_Msk instead)  */
#define RTC_MODE0_COMP_Msk                  _U_(0xFFFFFFFF)                                /**< (RTC_MODE0_COMP) Register Mask  */


/* -------- RTC_MODE1_COMP : (RTC Offset: 0x20) (R/W 16) MODE1 Compare n Value -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t COMP:16;                   /**< bit:  0..15  Compare Value                            */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} RTC_MODE1_COMP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_COMP_OFFSET               (0x20)                                        /**<  (RTC_MODE1_COMP) MODE1 Compare n Value  Offset */
#define RTC_MODE1_COMP_RESETVALUE           _U_(0x00)                                     /**<  (RTC_MODE1_COMP) MODE1 Compare n Value  Reset Value */

#define RTC_MODE1_COMP_COMP_Pos             0                                              /**< (RTC_MODE1_COMP) Compare Value Position */
#define RTC_MODE1_COMP_COMP_Msk             (_U_(0xFFFF) << RTC_MODE1_COMP_COMP_Pos)       /**< (RTC_MODE1_COMP) Compare Value Mask */
#define RTC_MODE1_COMP_COMP(value)          (RTC_MODE1_COMP_COMP_Msk & ((value) << RTC_MODE1_COMP_COMP_Pos))
#define RTC_MODE1_COMP_MASK                 _U_(0xFFFF)                                    /**< \deprecated (RTC_MODE1_COMP) Register MASK  (Use RTC_MODE1_COMP_Msk instead)  */
#define RTC_MODE1_COMP_Msk                  _U_(0xFFFF)                                    /**< (RTC_MODE1_COMP) Register Mask  */


/* -------- RTC_GP : (RTC Offset: 0x40) (R/W 32) General Purpose -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t GP:32;                     /**< bit:  0..31  General Purpose                          */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_GP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_GP_OFFSET                       (0x40)                                        /**<  (RTC_GP) General Purpose  Offset */
#define RTC_GP_RESETVALUE                   _U_(0x00)                                     /**<  (RTC_GP) General Purpose  Reset Value */

#define RTC_GP_GP_Pos                       0                                              /**< (RTC_GP) General Purpose Position */
#define RTC_GP_GP_Msk                       (_U_(0xFFFFFFFF) << RTC_GP_GP_Pos)             /**< (RTC_GP) General Purpose Mask */
#define RTC_GP_GP(value)                    (RTC_GP_GP_Msk & ((value) << RTC_GP_GP_Pos)) 
#define RTC_GP_MASK                         _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_GP) Register MASK  (Use RTC_GP_Msk instead)  */
#define RTC_GP_Msk                          _U_(0xFFFFFFFF)                                /**< (RTC_GP) Register Mask  */


/* -------- RTC_TAMPCTRL : (RTC Offset: 0x60) (R/W 32) Tamper Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t IN0ACT:2;                  /**< bit:   0..1  Tamper Input 0 Action                    */
    uint32_t IN1ACT:2;                  /**< bit:   2..3  Tamper Input 1 Action                    */
    uint32_t IN2ACT:2;                  /**< bit:   4..5  Tamper Input 2 Action                    */
    uint32_t IN3ACT:2;                  /**< bit:   6..7  Tamper Input 3 Action                    */
    uint32_t :8;                        /**< bit:  8..15  Reserved */
    uint32_t TAMLVL0:1;                 /**< bit:     16  Tamper Level Select 0                    */
    uint32_t TAMLVL1:1;                 /**< bit:     17  Tamper Level Select 1                    */
    uint32_t TAMLVL2:1;                 /**< bit:     18  Tamper Level Select 2                    */
    uint32_t TAMLVL3:1;                 /**< bit:     19  Tamper Level Select 3                    */
    uint32_t :4;                        /**< bit: 20..23  Reserved */
    uint32_t DEBNC0:1;                  /**< bit:     24  Debouncer Enable 0                       */
    uint32_t DEBNC1:1;                  /**< bit:     25  Debouncer Enable 1                       */
    uint32_t DEBNC2:1;                  /**< bit:     26  Debouncer Enable 2                       */
    uint32_t DEBNC3:1;                  /**< bit:     27  Debouncer Enable 3                       */
    uint32_t :4;                        /**< bit: 28..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t :16;                       /**< bit:  0..15  Reserved */
    uint32_t TAMLVL:4;                  /**< bit: 16..19  Tamper Level Select x                    */
    uint32_t :4;                        /**< bit: 20..23  Reserved */
    uint32_t DEBNC:4;                   /**< bit: 24..27  Debouncer Enable 3                       */
    uint32_t :4;                        /**< bit: 28..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_TAMPCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_TAMPCTRL_OFFSET                 (0x60)                                        /**<  (RTC_TAMPCTRL) Tamper Control  Offset */
#define RTC_TAMPCTRL_RESETVALUE             _U_(0x00)                                     /**<  (RTC_TAMPCTRL) Tamper Control  Reset Value */

#define RTC_TAMPCTRL_IN0ACT_Pos             0                                              /**< (RTC_TAMPCTRL) Tamper Input 0 Action Position */
#define RTC_TAMPCTRL_IN0ACT_Msk             (_U_(0x3) << RTC_TAMPCTRL_IN0ACT_Pos)          /**< (RTC_TAMPCTRL) Tamper Input 0 Action Mask */
#define RTC_TAMPCTRL_IN0ACT(value)          (RTC_TAMPCTRL_IN0ACT_Msk & ((value) << RTC_TAMPCTRL_IN0ACT_Pos))
#define   RTC_TAMPCTRL_IN0ACT_OFF_Val       _U_(0x0)                                       /**< (RTC_TAMPCTRL) Off (Disabled)  */
#define   RTC_TAMPCTRL_IN0ACT_WAKE_Val      _U_(0x1)                                       /**< (RTC_TAMPCTRL) Wake and set Tamper flag  */
#define   RTC_TAMPCTRL_IN0ACT_CAPTURE_Val   _U_(0x2)                                       /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag  */
#define   RTC_TAMPCTRL_IN0ACT_ACTL_Val      _U_(0x3)                                       /**< (RTC_TAMPCTRL) Compare IN0 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag  */
#define RTC_TAMPCTRL_IN0ACT_OFF             (RTC_TAMPCTRL_IN0ACT_OFF_Val << RTC_TAMPCTRL_IN0ACT_Pos)  /**< (RTC_TAMPCTRL) Off (Disabled) Position  */
#define RTC_TAMPCTRL_IN0ACT_WAKE            (RTC_TAMPCTRL_IN0ACT_WAKE_Val << RTC_TAMPCTRL_IN0ACT_Pos)  /**< (RTC_TAMPCTRL) Wake and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN0ACT_CAPTURE         (RTC_TAMPCTRL_IN0ACT_CAPTURE_Val << RTC_TAMPCTRL_IN0ACT_Pos)  /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN0ACT_ACTL            (RTC_TAMPCTRL_IN0ACT_ACTL_Val << RTC_TAMPCTRL_IN0ACT_Pos)  /**< (RTC_TAMPCTRL) Compare IN0 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN1ACT_Pos             2                                              /**< (RTC_TAMPCTRL) Tamper Input 1 Action Position */
#define RTC_TAMPCTRL_IN1ACT_Msk             (_U_(0x3) << RTC_TAMPCTRL_IN1ACT_Pos)          /**< (RTC_TAMPCTRL) Tamper Input 1 Action Mask */
#define RTC_TAMPCTRL_IN1ACT(value)          (RTC_TAMPCTRL_IN1ACT_Msk & ((value) << RTC_TAMPCTRL_IN1ACT_Pos))
#define   RTC_TAMPCTRL_IN1ACT_OFF_Val       _U_(0x0)                                       /**< (RTC_TAMPCTRL) Off (Disabled)  */
#define   RTC_TAMPCTRL_IN1ACT_WAKE_Val      _U_(0x1)                                       /**< (RTC_TAMPCTRL) Wake and set Tamper flag  */
#define   RTC_TAMPCTRL_IN1ACT_CAPTURE_Val   _U_(0x2)                                       /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag  */
#define   RTC_TAMPCTRL_IN1ACT_ACTL_Val      _U_(0x3)                                       /**< (RTC_TAMPCTRL) Compare IN1 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag  */
#define RTC_TAMPCTRL_IN1ACT_OFF             (RTC_TAMPCTRL_IN1ACT_OFF_Val << RTC_TAMPCTRL_IN1ACT_Pos)  /**< (RTC_TAMPCTRL) Off (Disabled) Position  */
#define RTC_TAMPCTRL_IN1ACT_WAKE            (RTC_TAMPCTRL_IN1ACT_WAKE_Val << RTC_TAMPCTRL_IN1ACT_Pos)  /**< (RTC_TAMPCTRL) Wake and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN1ACT_CAPTURE         (RTC_TAMPCTRL_IN1ACT_CAPTURE_Val << RTC_TAMPCTRL_IN1ACT_Pos)  /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN1ACT_ACTL            (RTC_TAMPCTRL_IN1ACT_ACTL_Val << RTC_TAMPCTRL_IN1ACT_Pos)  /**< (RTC_TAMPCTRL) Compare IN1 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN2ACT_Pos             4                                              /**< (RTC_TAMPCTRL) Tamper Input 2 Action Position */
#define RTC_TAMPCTRL_IN2ACT_Msk             (_U_(0x3) << RTC_TAMPCTRL_IN2ACT_Pos)          /**< (RTC_TAMPCTRL) Tamper Input 2 Action Mask */
#define RTC_TAMPCTRL_IN2ACT(value)          (RTC_TAMPCTRL_IN2ACT_Msk & ((value) << RTC_TAMPCTRL_IN2ACT_Pos))
#define   RTC_TAMPCTRL_IN2ACT_OFF_Val       _U_(0x0)                                       /**< (RTC_TAMPCTRL) Off (Disabled)  */
#define   RTC_TAMPCTRL_IN2ACT_WAKE_Val      _U_(0x1)                                       /**< (RTC_TAMPCTRL) Wake and set Tamper flag  */
#define   RTC_TAMPCTRL_IN2ACT_CAPTURE_Val   _U_(0x2)                                       /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag  */
#define   RTC_TAMPCTRL_IN2ACT_ACTL_Val      _U_(0x3)                                       /**< (RTC_TAMPCTRL) Compare IN2 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag  */
#define RTC_TAMPCTRL_IN2ACT_OFF             (RTC_TAMPCTRL_IN2ACT_OFF_Val << RTC_TAMPCTRL_IN2ACT_Pos)  /**< (RTC_TAMPCTRL) Off (Disabled) Position  */
#define RTC_TAMPCTRL_IN2ACT_WAKE            (RTC_TAMPCTRL_IN2ACT_WAKE_Val << RTC_TAMPCTRL_IN2ACT_Pos)  /**< (RTC_TAMPCTRL) Wake and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN2ACT_CAPTURE         (RTC_TAMPCTRL_IN2ACT_CAPTURE_Val << RTC_TAMPCTRL_IN2ACT_Pos)  /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN2ACT_ACTL            (RTC_TAMPCTRL_IN2ACT_ACTL_Val << RTC_TAMPCTRL_IN2ACT_Pos)  /**< (RTC_TAMPCTRL) Compare IN2 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN3ACT_Pos             6                                              /**< (RTC_TAMPCTRL) Tamper Input 3 Action Position */
#define RTC_TAMPCTRL_IN3ACT_Msk             (_U_(0x3) << RTC_TAMPCTRL_IN3ACT_Pos)          /**< (RTC_TAMPCTRL) Tamper Input 3 Action Mask */
#define RTC_TAMPCTRL_IN3ACT(value)          (RTC_TAMPCTRL_IN3ACT_Msk & ((value) << RTC_TAMPCTRL_IN3ACT_Pos))
#define   RTC_TAMPCTRL_IN3ACT_OFF_Val       _U_(0x0)                                       /**< (RTC_TAMPCTRL) Off (Disabled)  */
#define   RTC_TAMPCTRL_IN3ACT_WAKE_Val      _U_(0x1)                                       /**< (RTC_TAMPCTRL) Wake and set Tamper flag  */
#define   RTC_TAMPCTRL_IN3ACT_CAPTURE_Val   _U_(0x2)                                       /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag  */
#define   RTC_TAMPCTRL_IN3ACT_ACTL_Val      _U_(0x3)                                       /**< (RTC_TAMPCTRL) Compare IN3 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag  */
#define RTC_TAMPCTRL_IN3ACT_OFF             (RTC_TAMPCTRL_IN3ACT_OFF_Val << RTC_TAMPCTRL_IN3ACT_Pos)  /**< (RTC_TAMPCTRL) Off (Disabled) Position  */
#define RTC_TAMPCTRL_IN3ACT_WAKE            (RTC_TAMPCTRL_IN3ACT_WAKE_Val << RTC_TAMPCTRL_IN3ACT_Pos)  /**< (RTC_TAMPCTRL) Wake and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN3ACT_CAPTURE         (RTC_TAMPCTRL_IN3ACT_CAPTURE_Val << RTC_TAMPCTRL_IN3ACT_Pos)  /**< (RTC_TAMPCTRL) Capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_IN3ACT_ACTL            (RTC_TAMPCTRL_IN3ACT_ACTL_Val << RTC_TAMPCTRL_IN3ACT_Pos)  /**< (RTC_TAMPCTRL) Compare IN3 to OUT. When a mismatch occurs, capture timestamp and set Tamper flag Position  */
#define RTC_TAMPCTRL_TAMLVL0_Pos            16                                             /**< (RTC_TAMPCTRL) Tamper Level Select 0 Position */
#define RTC_TAMPCTRL_TAMLVL0_Msk            (_U_(0x1) << RTC_TAMPCTRL_TAMLVL0_Pos)         /**< (RTC_TAMPCTRL) Tamper Level Select 0 Mask */
#define RTC_TAMPCTRL_TAMLVL0                RTC_TAMPCTRL_TAMLVL0_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_TAMLVL0_Msk instead */
#define RTC_TAMPCTRL_TAMLVL1_Pos            17                                             /**< (RTC_TAMPCTRL) Tamper Level Select 1 Position */
#define RTC_TAMPCTRL_TAMLVL1_Msk            (_U_(0x1) << RTC_TAMPCTRL_TAMLVL1_Pos)         /**< (RTC_TAMPCTRL) Tamper Level Select 1 Mask */
#define RTC_TAMPCTRL_TAMLVL1                RTC_TAMPCTRL_TAMLVL1_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_TAMLVL1_Msk instead */
#define RTC_TAMPCTRL_TAMLVL2_Pos            18                                             /**< (RTC_TAMPCTRL) Tamper Level Select 2 Position */
#define RTC_TAMPCTRL_TAMLVL2_Msk            (_U_(0x1) << RTC_TAMPCTRL_TAMLVL2_Pos)         /**< (RTC_TAMPCTRL) Tamper Level Select 2 Mask */
#define RTC_TAMPCTRL_TAMLVL2                RTC_TAMPCTRL_TAMLVL2_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_TAMLVL2_Msk instead */
#define RTC_TAMPCTRL_TAMLVL3_Pos            19                                             /**< (RTC_TAMPCTRL) Tamper Level Select 3 Position */
#define RTC_TAMPCTRL_TAMLVL3_Msk            (_U_(0x1) << RTC_TAMPCTRL_TAMLVL3_Pos)         /**< (RTC_TAMPCTRL) Tamper Level Select 3 Mask */
#define RTC_TAMPCTRL_TAMLVL3                RTC_TAMPCTRL_TAMLVL3_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_TAMLVL3_Msk instead */
#define RTC_TAMPCTRL_DEBNC0_Pos             24                                             /**< (RTC_TAMPCTRL) Debouncer Enable 0 Position */
#define RTC_TAMPCTRL_DEBNC0_Msk             (_U_(0x1) << RTC_TAMPCTRL_DEBNC0_Pos)          /**< (RTC_TAMPCTRL) Debouncer Enable 0 Mask */
#define RTC_TAMPCTRL_DEBNC0                 RTC_TAMPCTRL_DEBNC0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_DEBNC0_Msk instead */
#define RTC_TAMPCTRL_DEBNC1_Pos             25                                             /**< (RTC_TAMPCTRL) Debouncer Enable 1 Position */
#define RTC_TAMPCTRL_DEBNC1_Msk             (_U_(0x1) << RTC_TAMPCTRL_DEBNC1_Pos)          /**< (RTC_TAMPCTRL) Debouncer Enable 1 Mask */
#define RTC_TAMPCTRL_DEBNC1                 RTC_TAMPCTRL_DEBNC1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_DEBNC1_Msk instead */
#define RTC_TAMPCTRL_DEBNC2_Pos             26                                             /**< (RTC_TAMPCTRL) Debouncer Enable 2 Position */
#define RTC_TAMPCTRL_DEBNC2_Msk             (_U_(0x1) << RTC_TAMPCTRL_DEBNC2_Pos)          /**< (RTC_TAMPCTRL) Debouncer Enable 2 Mask */
#define RTC_TAMPCTRL_DEBNC2                 RTC_TAMPCTRL_DEBNC2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_DEBNC2_Msk instead */
#define RTC_TAMPCTRL_DEBNC3_Pos             27                                             /**< (RTC_TAMPCTRL) Debouncer Enable 3 Position */
#define RTC_TAMPCTRL_DEBNC3_Msk             (_U_(0x1) << RTC_TAMPCTRL_DEBNC3_Pos)          /**< (RTC_TAMPCTRL) Debouncer Enable 3 Mask */
#define RTC_TAMPCTRL_DEBNC3                 RTC_TAMPCTRL_DEBNC3_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRL_DEBNC3_Msk instead */
#define RTC_TAMPCTRL_MASK                   _U_(0xF0F00FF)                                 /**< \deprecated (RTC_TAMPCTRL) Register MASK  (Use RTC_TAMPCTRL_Msk instead)  */
#define RTC_TAMPCTRL_Msk                    _U_(0xF0F00FF)                                 /**< (RTC_TAMPCTRL) Register Mask  */

#define RTC_TAMPCTRL_TAMLVL_Pos             16                                             /**< (RTC_TAMPCTRL Position) Tamper Level Select x */
#define RTC_TAMPCTRL_TAMLVL_Msk             (_U_(0xF) << RTC_TAMPCTRL_TAMLVL_Pos)          /**< (RTC_TAMPCTRL Mask) TAMLVL */
#define RTC_TAMPCTRL_TAMLVL(value)          (RTC_TAMPCTRL_TAMLVL_Msk & ((value) << RTC_TAMPCTRL_TAMLVL_Pos))  
#define RTC_TAMPCTRL_DEBNC_Pos              24                                             /**< (RTC_TAMPCTRL Position) Debouncer Enable 3 */
#define RTC_TAMPCTRL_DEBNC_Msk              (_U_(0xF) << RTC_TAMPCTRL_DEBNC_Pos)           /**< (RTC_TAMPCTRL Mask) DEBNC */
#define RTC_TAMPCTRL_DEBNC(value)           (RTC_TAMPCTRL_DEBNC_Msk & ((value) << RTC_TAMPCTRL_DEBNC_Pos))  

/* -------- RTC_MODE0_TIMESTAMP : (RTC Offset: 0x64) (R/ 32) MODE0 Timestamp -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COUNT:32;                  /**< bit:  0..31  Count Timestamp Value                    */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE0_TIMESTAMP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE0_TIMESTAMP_OFFSET          (0x64)                                        /**<  (RTC_MODE0_TIMESTAMP) MODE0 Timestamp  Offset */
#define RTC_MODE0_TIMESTAMP_RESETVALUE      _U_(0x00)                                     /**<  (RTC_MODE0_TIMESTAMP) MODE0 Timestamp  Reset Value */

#define RTC_MODE0_TIMESTAMP_COUNT_Pos       0                                              /**< (RTC_MODE0_TIMESTAMP) Count Timestamp Value Position */
#define RTC_MODE0_TIMESTAMP_COUNT_Msk       (_U_(0xFFFFFFFF) << RTC_MODE0_TIMESTAMP_COUNT_Pos)  /**< (RTC_MODE0_TIMESTAMP) Count Timestamp Value Mask */
#define RTC_MODE0_TIMESTAMP_COUNT(value)    (RTC_MODE0_TIMESTAMP_COUNT_Msk & ((value) << RTC_MODE0_TIMESTAMP_COUNT_Pos))
#define RTC_MODE0_TIMESTAMP_MASK            _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE0_TIMESTAMP) Register MASK  (Use RTC_MODE0_TIMESTAMP_Msk instead)  */
#define RTC_MODE0_TIMESTAMP_Msk             _U_(0xFFFFFFFF)                                /**< (RTC_MODE0_TIMESTAMP) Register Mask  */


/* -------- RTC_MODE1_TIMESTAMP : (RTC Offset: 0x64) (R/ 32) MODE1 Timestamp -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COUNT:16;                  /**< bit:  0..15  Count Timestamp Value                    */
    uint32_t :16;                       /**< bit: 16..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE1_TIMESTAMP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE1_TIMESTAMP_OFFSET          (0x64)                                        /**<  (RTC_MODE1_TIMESTAMP) MODE1 Timestamp  Offset */
#define RTC_MODE1_TIMESTAMP_RESETVALUE      _U_(0x00)                                     /**<  (RTC_MODE1_TIMESTAMP) MODE1 Timestamp  Reset Value */

#define RTC_MODE1_TIMESTAMP_COUNT_Pos       0                                              /**< (RTC_MODE1_TIMESTAMP) Count Timestamp Value Position */
#define RTC_MODE1_TIMESTAMP_COUNT_Msk       (_U_(0xFFFF) << RTC_MODE1_TIMESTAMP_COUNT_Pos)  /**< (RTC_MODE1_TIMESTAMP) Count Timestamp Value Mask */
#define RTC_MODE1_TIMESTAMP_COUNT(value)    (RTC_MODE1_TIMESTAMP_COUNT_Msk & ((value) << RTC_MODE1_TIMESTAMP_COUNT_Pos))
#define RTC_MODE1_TIMESTAMP_MASK            _U_(0xFFFF)                                    /**< \deprecated (RTC_MODE1_TIMESTAMP) Register MASK  (Use RTC_MODE1_TIMESTAMP_Msk instead)  */
#define RTC_MODE1_TIMESTAMP_Msk             _U_(0xFFFF)                                    /**< (RTC_MODE1_TIMESTAMP) Register Mask  */


/* -------- RTC_MODE2_TIMESTAMP : (RTC Offset: 0x64) (R/ 32) MODE2 Timestamp -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SECOND:6;                  /**< bit:   0..5  Second Timestamp Value                   */
    uint32_t MINUTE:6;                  /**< bit:  6..11  Minute Timestamp Value                   */
    uint32_t HOUR:5;                    /**< bit: 12..16  Hour Timestamp Value                     */
    uint32_t DAY:5;                     /**< bit: 17..21  Day Timestamp Value                      */
    uint32_t MONTH:4;                   /**< bit: 22..25  Month Timestamp Value                    */
    uint32_t YEAR:6;                    /**< bit: 26..31  Year Timestamp Value                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} RTC_MODE2_TIMESTAMP_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_MODE2_TIMESTAMP_OFFSET          (0x64)                                        /**<  (RTC_MODE2_TIMESTAMP) MODE2 Timestamp  Offset */
#define RTC_MODE2_TIMESTAMP_RESETVALUE      _U_(0x00)                                     /**<  (RTC_MODE2_TIMESTAMP) MODE2 Timestamp  Reset Value */

#define RTC_MODE2_TIMESTAMP_SECOND_Pos      0                                              /**< (RTC_MODE2_TIMESTAMP) Second Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_SECOND_Msk      (_U_(0x3F) << RTC_MODE2_TIMESTAMP_SECOND_Pos)  /**< (RTC_MODE2_TIMESTAMP) Second Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_SECOND(value)   (RTC_MODE2_TIMESTAMP_SECOND_Msk & ((value) << RTC_MODE2_TIMESTAMP_SECOND_Pos))
#define RTC_MODE2_TIMESTAMP_MINUTE_Pos      6                                              /**< (RTC_MODE2_TIMESTAMP) Minute Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_MINUTE_Msk      (_U_(0x3F) << RTC_MODE2_TIMESTAMP_MINUTE_Pos)  /**< (RTC_MODE2_TIMESTAMP) Minute Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_MINUTE(value)   (RTC_MODE2_TIMESTAMP_MINUTE_Msk & ((value) << RTC_MODE2_TIMESTAMP_MINUTE_Pos))
#define RTC_MODE2_TIMESTAMP_HOUR_Pos        12                                             /**< (RTC_MODE2_TIMESTAMP) Hour Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_HOUR_Msk        (_U_(0x1F) << RTC_MODE2_TIMESTAMP_HOUR_Pos)    /**< (RTC_MODE2_TIMESTAMP) Hour Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_HOUR(value)     (RTC_MODE2_TIMESTAMP_HOUR_Msk & ((value) << RTC_MODE2_TIMESTAMP_HOUR_Pos))
#define RTC_MODE2_TIMESTAMP_DAY_Pos         17                                             /**< (RTC_MODE2_TIMESTAMP) Day Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_DAY_Msk         (_U_(0x1F) << RTC_MODE2_TIMESTAMP_DAY_Pos)     /**< (RTC_MODE2_TIMESTAMP) Day Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_DAY(value)      (RTC_MODE2_TIMESTAMP_DAY_Msk & ((value) << RTC_MODE2_TIMESTAMP_DAY_Pos))
#define RTC_MODE2_TIMESTAMP_MONTH_Pos       22                                             /**< (RTC_MODE2_TIMESTAMP) Month Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_MONTH_Msk       (_U_(0xF) << RTC_MODE2_TIMESTAMP_MONTH_Pos)    /**< (RTC_MODE2_TIMESTAMP) Month Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_MONTH(value)    (RTC_MODE2_TIMESTAMP_MONTH_Msk & ((value) << RTC_MODE2_TIMESTAMP_MONTH_Pos))
#define RTC_MODE2_TIMESTAMP_YEAR_Pos        26                                             /**< (RTC_MODE2_TIMESTAMP) Year Timestamp Value Position */
#define RTC_MODE2_TIMESTAMP_YEAR_Msk        (_U_(0x3F) << RTC_MODE2_TIMESTAMP_YEAR_Pos)    /**< (RTC_MODE2_TIMESTAMP) Year Timestamp Value Mask */
#define RTC_MODE2_TIMESTAMP_YEAR(value)     (RTC_MODE2_TIMESTAMP_YEAR_Msk & ((value) << RTC_MODE2_TIMESTAMP_YEAR_Pos))
#define RTC_MODE2_TIMESTAMP_MASK            _U_(0xFFFFFFFF)                                /**< \deprecated (RTC_MODE2_TIMESTAMP) Register MASK  (Use RTC_MODE2_TIMESTAMP_Msk instead)  */
#define RTC_MODE2_TIMESTAMP_Msk             _U_(0xFFFFFFFF)                                /**< (RTC_MODE2_TIMESTAMP) Register Mask  */


/* -------- RTC_TAMPID : (RTC Offset: 0x68) (R/W 32) Tamper ID -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TAMPID0:1;                 /**< bit:      0  Tamper Input 0 Detected                  */
    uint32_t TAMPID1:1;                 /**< bit:      1  Tamper Input 1 Detected                  */
    uint32_t TAMPID2:1;                 /**< bit:      2  Tamper Input 2 Detected                  */
    uint32_t TAMPID3:1;                 /**< bit:      3  Tamper Input 3 Detected                  */
    uint32_t :27;                       /**< bit:  4..30  Reserved */
    uint32_t TAMPEVT:1;                 /**< bit:     31  Tamper Event Detected                    */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t TAMPID:4;                  /**< bit:   0..3  Tamper Input x Detected                  */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_TAMPID_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_TAMPID_OFFSET                   (0x68)                                        /**<  (RTC_TAMPID) Tamper ID  Offset */
#define RTC_TAMPID_RESETVALUE               _U_(0x00)                                     /**<  (RTC_TAMPID) Tamper ID  Reset Value */

#define RTC_TAMPID_TAMPID0_Pos              0                                              /**< (RTC_TAMPID) Tamper Input 0 Detected Position */
#define RTC_TAMPID_TAMPID0_Msk              (_U_(0x1) << RTC_TAMPID_TAMPID0_Pos)           /**< (RTC_TAMPID) Tamper Input 0 Detected Mask */
#define RTC_TAMPID_TAMPID0                  RTC_TAMPID_TAMPID0_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPID_TAMPID0_Msk instead */
#define RTC_TAMPID_TAMPID1_Pos              1                                              /**< (RTC_TAMPID) Tamper Input 1 Detected Position */
#define RTC_TAMPID_TAMPID1_Msk              (_U_(0x1) << RTC_TAMPID_TAMPID1_Pos)           /**< (RTC_TAMPID) Tamper Input 1 Detected Mask */
#define RTC_TAMPID_TAMPID1                  RTC_TAMPID_TAMPID1_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPID_TAMPID1_Msk instead */
#define RTC_TAMPID_TAMPID2_Pos              2                                              /**< (RTC_TAMPID) Tamper Input 2 Detected Position */
#define RTC_TAMPID_TAMPID2_Msk              (_U_(0x1) << RTC_TAMPID_TAMPID2_Pos)           /**< (RTC_TAMPID) Tamper Input 2 Detected Mask */
#define RTC_TAMPID_TAMPID2                  RTC_TAMPID_TAMPID2_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPID_TAMPID2_Msk instead */
#define RTC_TAMPID_TAMPID3_Pos              3                                              /**< (RTC_TAMPID) Tamper Input 3 Detected Position */
#define RTC_TAMPID_TAMPID3_Msk              (_U_(0x1) << RTC_TAMPID_TAMPID3_Pos)           /**< (RTC_TAMPID) Tamper Input 3 Detected Mask */
#define RTC_TAMPID_TAMPID3                  RTC_TAMPID_TAMPID3_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPID_TAMPID3_Msk instead */
#define RTC_TAMPID_TAMPEVT_Pos              31                                             /**< (RTC_TAMPID) Tamper Event Detected Position */
#define RTC_TAMPID_TAMPEVT_Msk              (_U_(0x1) << RTC_TAMPID_TAMPEVT_Pos)           /**< (RTC_TAMPID) Tamper Event Detected Mask */
#define RTC_TAMPID_TAMPEVT                  RTC_TAMPID_TAMPEVT_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPID_TAMPEVT_Msk instead */
#define RTC_TAMPID_MASK                     _U_(0x8000000F)                                /**< \deprecated (RTC_TAMPID) Register MASK  (Use RTC_TAMPID_Msk instead)  */
#define RTC_TAMPID_Msk                      _U_(0x8000000F)                                /**< (RTC_TAMPID) Register Mask  */

#define RTC_TAMPID_TAMPID_Pos               0                                              /**< (RTC_TAMPID Position) Tamper Input x Detected */
#define RTC_TAMPID_TAMPID_Msk               (_U_(0xF) << RTC_TAMPID_TAMPID_Pos)            /**< (RTC_TAMPID Mask) TAMPID */
#define RTC_TAMPID_TAMPID(value)            (RTC_TAMPID_TAMPID_Msk & ((value) << RTC_TAMPID_TAMPID_Pos))  

/* -------- RTC_TAMPCTRLB : (RTC Offset: 0x6c) (R/W 32) Tamper Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ALSI0:1;                   /**< bit:      0  Active Layer Select Internal 0           */
    uint32_t ALSI1:1;                   /**< bit:      1  Active Layer Select Internal 1           */
    uint32_t ALSI2:1;                   /**< bit:      2  Active Layer Select Internal 2           */
    uint32_t ALSI3:1;                   /**< bit:      3  Active Layer Select Internal 3           */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint32_t ALSI:4;                    /**< bit:   0..3  Active Layer Select Internal 3           */
    uint32_t :28;                       /**< bit:  4..31 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint32_t reg;                         /**< Type used for register access */
} RTC_TAMPCTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RTC_TAMPCTRLB_OFFSET                (0x6C)                                        /**<  (RTC_TAMPCTRLB) Tamper Control B  Offset */
#define RTC_TAMPCTRLB_RESETVALUE            _U_(0x00)                                     /**<  (RTC_TAMPCTRLB) Tamper Control B  Reset Value */

#define RTC_TAMPCTRLB_ALSI0_Pos             0                                              /**< (RTC_TAMPCTRLB) Active Layer Select Internal 0 Position */
#define RTC_TAMPCTRLB_ALSI0_Msk             (_U_(0x1) << RTC_TAMPCTRLB_ALSI0_Pos)          /**< (RTC_TAMPCTRLB) Active Layer Select Internal 0 Mask */
#define RTC_TAMPCTRLB_ALSI0                 RTC_TAMPCTRLB_ALSI0_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRLB_ALSI0_Msk instead */
#define RTC_TAMPCTRLB_ALSI1_Pos             1                                              /**< (RTC_TAMPCTRLB) Active Layer Select Internal 1 Position */
#define RTC_TAMPCTRLB_ALSI1_Msk             (_U_(0x1) << RTC_TAMPCTRLB_ALSI1_Pos)          /**< (RTC_TAMPCTRLB) Active Layer Select Internal 1 Mask */
#define RTC_TAMPCTRLB_ALSI1                 RTC_TAMPCTRLB_ALSI1_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRLB_ALSI1_Msk instead */
#define RTC_TAMPCTRLB_ALSI2_Pos             2                                              /**< (RTC_TAMPCTRLB) Active Layer Select Internal 2 Position */
#define RTC_TAMPCTRLB_ALSI2_Msk             (_U_(0x1) << RTC_TAMPCTRLB_ALSI2_Pos)          /**< (RTC_TAMPCTRLB) Active Layer Select Internal 2 Mask */
#define RTC_TAMPCTRLB_ALSI2                 RTC_TAMPCTRLB_ALSI2_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRLB_ALSI2_Msk instead */
#define RTC_TAMPCTRLB_ALSI3_Pos             3                                              /**< (RTC_TAMPCTRLB) Active Layer Select Internal 3 Position */
#define RTC_TAMPCTRLB_ALSI3_Msk             (_U_(0x1) << RTC_TAMPCTRLB_ALSI3_Pos)          /**< (RTC_TAMPCTRLB) Active Layer Select Internal 3 Mask */
#define RTC_TAMPCTRLB_ALSI3                 RTC_TAMPCTRLB_ALSI3_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RTC_TAMPCTRLB_ALSI3_Msk instead */
#define RTC_TAMPCTRLB_MASK                  _U_(0x0F)                                      /**< \deprecated (RTC_TAMPCTRLB) Register MASK  (Use RTC_TAMPCTRLB_Msk instead)  */
#define RTC_TAMPCTRLB_Msk                   _U_(0x0F)                                      /**< (RTC_TAMPCTRLB) Register Mask  */

#define RTC_TAMPCTRLB_ALSI_Pos              0                                              /**< (RTC_TAMPCTRLB Position) Active Layer Select Internal 3 */
#define RTC_TAMPCTRLB_ALSI_Msk              (_U_(0xF) << RTC_TAMPCTRLB_ALSI_Pos)           /**< (RTC_TAMPCTRLB Mask) ALSI */
#define RTC_TAMPCTRLB_ALSI(value)           (RTC_TAMPCTRLB_ALSI_Msk & ((value) << RTC_TAMPCTRLB_ALSI_Pos))  

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MODE2_ALARM hardware registers */
typedef struct {  
  __IO RTC_MODE2_ALARM_Type           ALARM;          /**< Offset: 0x00 (R/W  32) MODE2_ALARM Alarm n Value */
  __IO RTC_MODE2_MASK_Type            MASK;           /**< Offset: 0x04 (R/W   8) MODE2_ALARM Alarm n Mask */
  __I  uint8_t                        Reserved1[3];
} RtcMode2Alarm;

/** \brief RTC hardware registers */
typedef struct {  /* Real-Time Counter */
  __IO RTC_MODE0_CTRLA_Type           CTRLA;          /**< Offset: 0x00 (R/W  16) MODE0 Control A */
  __IO RTC_MODE0_CTRLB_Type           CTRLB;          /**< Offset: 0x02 (R/W  16) MODE0 Control B */
  __IO RTC_MODE0_EVCTRL_Type          EVCTRL;         /**< Offset: 0x04 (R/W  32) MODE0 Event Control */
  __IO RTC_MODE0_INTENCLR_Type        INTENCLR;       /**< Offset: 0x08 (R/W  16) MODE0 Interrupt Enable Clear */
  __IO RTC_MODE0_INTENSET_Type        INTENSET;       /**< Offset: 0x0A (R/W  16) MODE0 Interrupt Enable Set */
  __IO RTC_MODE0_INTFLAG_Type         INTFLAG;        /**< Offset: 0x0C (R/W  16) MODE0 Interrupt Flag Status and Clear */
  __IO RTC_DBGCTRL_Type               DBGCTRL;        /**< Offset: 0x0E (R/W   8) Debug Control */
  __I  uint8_t                        Reserved1[1];
  __I  RTC_MODE0_SYNCBUSY_Type        SYNCBUSY;       /**< Offset: 0x10 (R/   32) MODE0 Synchronization Busy Status */
  __IO RTC_FREQCORR_Type              FREQCORR;       /**< Offset: 0x14 (R/W   8) Frequency Correction */
  __I  uint8_t                        Reserved2[3];
  __IO RTC_MODE0_COUNT_Type           COUNT;          /**< Offset: 0x18 (R/W  32) MODE0 Counter Value */
  __I  uint8_t                        Reserved3[4];
  __IO RTC_MODE0_COMP_Type            COMP[1];        /**< Offset: 0x20 (R/W  32) MODE0 Compare n Value */
  __I  uint8_t                        Reserved4[28];
  __IO RTC_GP_Type                    GP[2];          /**< Offset: 0x40 (R/W  32) General Purpose */
  __I  uint8_t                        Reserved5[24];
  __IO RTC_TAMPCTRL_Type              TAMPCTRL;       /**< Offset: 0x60 (R/W  32) Tamper Control */
  __I  RTC_MODE0_TIMESTAMP_Type       TIMESTAMP;      /**< Offset: 0x64 (R/   32) MODE0 Timestamp */
  __IO RTC_TAMPID_Type                TAMPID;         /**< Offset: 0x68 (R/W  32) Tamper ID */
  __IO RTC_TAMPCTRLB_Type             TAMPCTRLB;      /**< Offset: 0x6C (R/W  32) Tamper Control B */
} RtcMode0;

/** \brief RTC hardware registers */
typedef struct {  /* Real-Time Counter */
  __IO RTC_MODE1_CTRLA_Type           CTRLA;          /**< Offset: 0x00 (R/W  16) MODE1 Control A */
  __IO RTC_MODE1_CTRLB_Type           CTRLB;          /**< Offset: 0x02 (R/W  16) MODE1 Control B */
  __IO RTC_MODE1_EVCTRL_Type          EVCTRL;         /**< Offset: 0x04 (R/W  32) MODE1 Event Control */
  __IO RTC_MODE1_INTENCLR_Type        INTENCLR;       /**< Offset: 0x08 (R/W  16) MODE1 Interrupt Enable Clear */
  __IO RTC_MODE1_INTENSET_Type        INTENSET;       /**< Offset: 0x0A (R/W  16) MODE1 Interrupt Enable Set */
  __IO RTC_MODE1_INTFLAG_Type         INTFLAG;        /**< Offset: 0x0C (R/W  16) MODE1 Interrupt Flag Status and Clear */
  __IO RTC_DBGCTRL_Type               DBGCTRL;        /**< Offset: 0x0E (R/W   8) Debug Control */
  __I  uint8_t                        Reserved1[1];
  __I  RTC_MODE1_SYNCBUSY_Type        SYNCBUSY;       /**< Offset: 0x10 (R/   32) MODE1 Synchronization Busy Status */
  __IO RTC_FREQCORR_Type              FREQCORR;       /**< Offset: 0x14 (R/W   8) Frequency Correction */
  __I  uint8_t                        Reserved2[3];
  __IO RTC_MODE1_COUNT_Type           COUNT;          /**< Offset: 0x18 (R/W  16) MODE1 Counter Value */
  __I  uint8_t                        Reserved3[2];
  __IO RTC_MODE1_PER_Type             PER;            /**< Offset: 0x1C (R/W  16) MODE1 Counter Period */
  __I  uint8_t                        Reserved4[2];
  __IO RTC_MODE1_COMP_Type            COMP[2];        /**< Offset: 0x20 (R/W  16) MODE1 Compare n Value */
  __I  uint8_t                        Reserved5[28];
  __IO RTC_GP_Type                    GP[2];          /**< Offset: 0x40 (R/W  32) General Purpose */
  __I  uint8_t                        Reserved6[24];
  __IO RTC_TAMPCTRL_Type              TAMPCTRL;       /**< Offset: 0x60 (R/W  32) Tamper Control */
  __I  RTC_MODE1_TIMESTAMP_Type       TIMESTAMP;      /**< Offset: 0x64 (R/   32) MODE1 Timestamp */
  __IO RTC_TAMPID_Type                TAMPID;         /**< Offset: 0x68 (R/W  32) Tamper ID */
  __IO RTC_TAMPCTRLB_Type             TAMPCTRLB;      /**< Offset: 0x6C (R/W  32) Tamper Control B */
} RtcMode1;

/** \brief RTC hardware registers */
typedef struct {  /* Real-Time Counter */
  __IO RTC_MODE2_CTRLA_Type           CTRLA;          /**< Offset: 0x00 (R/W  16) MODE2 Control A */
  __IO RTC_MODE2_CTRLB_Type           CTRLB;          /**< Offset: 0x02 (R/W  16) MODE2 Control B */
  __IO RTC_MODE2_EVCTRL_Type          EVCTRL;         /**< Offset: 0x04 (R/W  32) MODE2 Event Control */
  __IO RTC_MODE2_INTENCLR_Type        INTENCLR;       /**< Offset: 0x08 (R/W  16) MODE2 Interrupt Enable Clear */
  __IO RTC_MODE2_INTENSET_Type        INTENSET;       /**< Offset: 0x0A (R/W  16) MODE2 Interrupt Enable Set */
  __IO RTC_MODE2_INTFLAG_Type         INTFLAG;        /**< Offset: 0x0C (R/W  16) MODE2 Interrupt Flag Status and Clear */
  __IO RTC_DBGCTRL_Type               DBGCTRL;        /**< Offset: 0x0E (R/W   8) Debug Control */
  __I  uint8_t                        Reserved1[1];
  __I  RTC_MODE2_SYNCBUSY_Type        SYNCBUSY;       /**< Offset: 0x10 (R/   32) MODE2 Synchronization Busy Status */
  __IO RTC_FREQCORR_Type              FREQCORR;       /**< Offset: 0x14 (R/W   8) Frequency Correction */
  __I  uint8_t                        Reserved2[3];
  __IO RTC_MODE2_CLOCK_Type           CLOCK;          /**< Offset: 0x18 (R/W  32) MODE2 Clock Value */
  __I  uint8_t                        Reserved3[4];
       RtcMode2Alarm                  Mode2Alarm[1];  /**< Offset: 0x20  */
  __I  uint8_t                        Reserved4[24];
  __IO RTC_GP_Type                    GP[2];          /**< Offset: 0x40 (R/W  32) General Purpose */
  __I  uint8_t                        Reserved5[24];
  __IO RTC_TAMPCTRL_Type              TAMPCTRL;       /**< Offset: 0x60 (R/W  32) Tamper Control */
  __I  RTC_MODE2_TIMESTAMP_Type       TIMESTAMP;      /**< Offset: 0x64 (R/   32) MODE2 Timestamp */
  __IO RTC_TAMPID_Type                TAMPID;         /**< Offset: 0x68 (R/W  32) Tamper ID */
  __IO RTC_TAMPCTRLB_Type             TAMPCTRLB;      /**< Offset: 0x6C (R/W  32) Tamper Control B */
} RtcMode2;

/** \brief RTC hardware registers */
typedef union {  /* Real-Time Counter */
       RtcMode0                       MODE0;          /**< 32-bit Counter with Single 32-bit Compare */
       RtcMode1                       MODE1;          /**< 16-bit Counter with Two 16-bit Compares */
       RtcMode2                       MODE2;          /**< Clock/Calendar with Alarm */
} Rtc;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Real-Time Counter */

#endif /* _SAML10_RTC_COMPONENT_H_ */
