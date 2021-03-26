/**************************************************************************//**
 * @file     rtc.h
 * @version  V3.00
 * @brief    NUC980 series RTC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_RTC_H__
#define __NU_RTC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nuc980.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @addtogroup RTC_EXPORTED_CONSTANTS RTC Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Initial Keyword Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_INIT_KEY            0xA5EB1357UL    /*!< RTC Initiation Key to make RTC leaving reset state \hideinitializer */
#define RTC_WRITE_KEY           0x0000A965UL    /*!< RTC Register Access Enable Key to enable RTC read/write accessible and kept 1024 RTC clock \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Time Attribute Constant Definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_CLOCK_12            0UL               /*!< RTC as 12-hour time scale with AM and PM indication \hideinitializer */
#define RTC_CLOCK_24            1UL               /*!< RTC as 24-hour time scale \hideinitializer */
#define RTC_AM                  1UL               /*!< RTC as AM indication \hideinitializer */
#define RTC_PM                  2UL               /*!< RTC as PM indication \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Tick Period Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_TICK_1_SEC          0x0UL           /*!< RTC time tick period is 1 second \hideinitializer */
#define RTC_TICK_1_2_SEC        0x1UL           /*!< RTC time tick period is 1/2 second \hideinitializer */
#define RTC_TICK_1_4_SEC        0x2UL           /*!< RTC time tick period is 1/4 second \hideinitializer */
#define RTC_TICK_1_8_SEC        0x3UL           /*!< RTC time tick period is 1/8 second \hideinitializer */
#define RTC_TICK_1_16_SEC       0x4UL           /*!< RTC time tick period is 1/16 second \hideinitializer */
#define RTC_TICK_1_32_SEC       0x5UL           /*!< RTC time tick period is 1/32 second \hideinitializer */
#define RTC_TICK_1_64_SEC       0x6UL           /*!< RTC time tick period is 1/64 second \hideinitializer */
#define RTC_TICK_1_128_SEC      0x7UL           /*!< RTC time tick period is 1/128 second \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Day of Week Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_SUNDAY              0x0UL           /*!< Day of the Week is Sunday \hideinitializer */
#define RTC_MONDAY              0x1UL           /*!< Day of the Week is Monday \hideinitializer */
#define RTC_TUESDAY             0x2UL           /*!< Day of the Week is Tuesday \hideinitializer */
#define RTC_WEDNESDAY           0x3UL           /*!< Day of the Week is Wednesday \hideinitializer */
#define RTC_THURSDAY            0x4UL           /*!< Day of the Week is Thursday \hideinitializer */
#define RTC_FRIDAY              0x5UL           /*!< Day of the Week is Friday \hideinitializer */
#define RTC_SATURDAY            0x6UL           /*!< Day of the Week is Saturday \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Miscellaneous Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_WAIT_COUNT          0xFFFFFFFFUL      /*!< Initial Time-out Value \hideinitializer */
#define RTC_YEAR2000            2000UL            /*!< RTC Reference for compute year data \hideinitializer */
#define RTC_FCR_REFERENCE       32761UL           /*!< RTC Reference for frequency compensation \hideinitializer */

#define RTC_2POW10_CLK  (0x0 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 RTC clock cycles \hideinitializer */
#define RTC_2POW11_CLK  (0x1 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 2 RTC clock cycles \hideinitializer */
#define RTC_2POW12_CLK  (0x2 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 4 RTC clock cycles \hideinitializer */
#define RTC_2POW13_CLK  (0x3 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 6 RTC clock cycles \hideinitializer */
#define RTC_2POW14_CLK  (0x4 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 8 RTC clock cycles \hideinitializer */
#define RTC_2POW15_CLK  (0x5 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 16 RTC clock cycles \hideinitializer */
#define RTC_2POW16_CLK  (0x6 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 32 RTC clock cycles \hideinitializer */
#define RTC_2POW17_CLK  (0x7 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 64 RTC clock cycles \hideinitializer */

#define REF_RANDOM_PATTERN    0x0 /*!< The new reference pattern is generated by random number generator when the reference pattern run out \hideinitializer */
#define REF_PREVIOUS_PATTERN  0x1 /*!< The new reference pattern is repeated previous random value when the reference pattern run out \hideinitializer */
#define REF_SEED              0x3 /*!< The new reference pattern is repeated from SEED (RTC_TAMPSEED[31:0]) when the reference pattern run out \hideinitializer */

/*@}*/ /* end of group RTC_EXPORTED_CONSTANTS */


/** @addtogroup RTC_EXPORTED_STRUCTS RTC Exported Structs
  @{
*/
/**
  * @details    RTC define Time Data Struct
  */
typedef struct
{
    uint32_t u32Year;           /*!< Year value */
    uint32_t u32Month;          /*!< Month value */
    uint32_t u32Day;            /*!< Day value */
    uint32_t u32DayOfWeek;      /*!< Day of week value */
    uint32_t u32Hour;           /*!< Hour value */
    uint32_t u32Minute;         /*!< Minute value */
    uint32_t u32Second;         /*!< Second value */
    uint32_t u32TimeScale;      /*!< 12-Hour, 24-Hour */
    uint32_t u32AmPm;           /*!< Only Time Scale select 12-hr used */
} S_RTC_TIME_DATA_T;

/*@}*/ /* end of group RTC_EXPORTED_STRUCTS */


typedef struct
{
    __IO uint32_t INIT;                  /*!< [0x0000] RTC Initiation Register                                          */
    __IO uint32_t RWEN;                  /*!< [0x0004] RTC Access Enable Register                                       */
    __IO uint32_t FREQADJ;               /*!< [0x0008] RTC Frequency Compensation Register                              */
    __IO uint32_t TIME;                  /*!< [0x000c] RTC Time Loading Register                                        */
    __IO uint32_t CAL;                   /*!< [0x0010] RTC Calendar Loading Register                                    */
    __IO uint32_t CLKFMT;                /*!< [0x0014] RTC Time Scale Selection Register                                */
    __IO uint32_t WEEKDAY;               /*!< [0x0018] RTC Day of the Week Register                                     */
    __IO uint32_t TALM;                  /*!< [0x001c] RTC Time Alarm Register                                          */
    __IO uint32_t CALM;                  /*!< [0x0020] RTC Calendar Alarm Register                                      */
    __I uint32_t LEAPYEAR;              /*!< [0x0024] RTC Leap Year Indicator Register                                 */
    __IO uint32_t INTEN;                 /*!< [0x0028] RTC Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x002c] RTC Interrupt Status Register                                    */
    __IO uint32_t TICK;                  /*!< [0x0030] RTC Time Tick Register                                           */
    __IO uint32_t PWRCTL;                 /*!< [0x0034] RTC Power Control Register                                     */
    __IO uint32_t PWRCNT;                 /*!< [0x0038] RTC Power Control Counter Register                                 */
    __IO uint32_t RESERVE0;                /*!< [0x003c] RTC Spare Functional Control Register                            */
    __I uint32_t SPR[16];               /*!< [0x0040] ~ [0x007c] RTC Spare Register 0 ~ 15                             */
} RTC_T;

#define RTC_INIT_ACTIVE_Pos         (0)                                               /*!< RTC_T::INIT: INIT_ACTIVE Position      */
#define RTC_INIT_ACTIVE_Msk         (0x1ul << RTC_INIT_ACTIVE_Pos)               /*!< RTC_T::INIT: INIT_ACTIVE Mask          */

#define RTC_INIT_INIT_Pos                (1)                                               /*!< RTC_T::INIT: INIT Position             */
#define RTC_INIT_INIT_Msk                (0x7ffffffful << RTC_INIT_INIT_Pos)               /*!< RTC_T::INIT: INIT Mask                 */

#define RTC_RWEN_RWENF_Pos               (16)                                              /*!< RTC_T::RWEN: RWENF Position            */
#define RTC_RWEN_RWENF_Msk               (0x1ul << RTC_RWEN_RWENF_Pos)                     /*!< RTC_T::RWEN: RWENF Mask                */

#define RTC_RWEN_RTCBUSY_Pos             (24)                                              /*!< RTC_T::RWEN: RTCBUSY Position          */
#define RTC_RWEN_RTCBUSY_Msk             (0x1ul << RTC_RWEN_RTCBUSY_Pos)                   /*!< RTC_T::RWEN: RTCBUSY Mask              */

#define RTC_FREQADJ_FRACTION_Pos          (0)                                              /*!< RTC_T::FRACTION: FRACTION Position       */
#define RTC_FREQADJ_FRACTION_Msk          (0x3ful << RTC_FREQADJ_FRACTION_Pos)             /*!< RTC_T::FRACTION: FRACTION Mask           */

#define RTC_INTEGER_FRACTION_Pos          (8)                                              /*!< RTC_T::INTEGER: INTEGER Position       */
#define RTC_INTEGER_FRACTION_Msk          (0xful << RTC_FREQADJ_INTEGER_Pos)               /*!< RTC_T::INTEGER: INTEGER Mask           */

#define RTC_TIME_SEC_Pos                 (0)                                               /*!< RTC_T::TIME: SEC Position              */
#define RTC_TIME_SEC_Msk                 (0xful << RTC_TIME_SEC_Pos)                       /*!< RTC_T::TIME: SEC Mask                  */

#define RTC_TIME_TENSEC_Pos              (4)                                               /*!< RTC_T::TIME: TENSEC Position           */
#define RTC_TIME_TENSEC_Msk              (0x7ul << RTC_TIME_TENSEC_Pos)                    /*!< RTC_T::TIME: TENSEC Mask               */

#define RTC_TIME_MIN_Pos                 (8)                                               /*!< RTC_T::TIME: MIN Position              */
#define RTC_TIME_MIN_Msk                 (0xful << RTC_TIME_MIN_Pos)                       /*!< RTC_T::TIME: MIN Mask                  */

#define RTC_TIME_TENMIN_Pos              (12)                                              /*!< RTC_T::TIME: TENMIN Position           */
#define RTC_TIME_TENMIN_Msk              (0x7ul << RTC_TIME_TENMIN_Pos)                    /*!< RTC_T::TIME: TENMIN Mask               */

#define RTC_TIME_HR_Pos                  (16)                                              /*!< RTC_T::TIME: HR Position               */
#define RTC_TIME_HR_Msk                  (0xful << RTC_TIME_HR_Pos)                        /*!< RTC_T::TIME: HR Mask                   */

#define RTC_TIME_TENHR_Pos               (20)                                              /*!< RTC_T::TIME: TENHR Position            */
#define RTC_TIME_TENHR_Msk               (0x3ul << RTC_TIME_TENHR_Pos)                     /*!< RTC_T::TIME: TENHR Mask                */

#define RTC_CAL_DAY_Pos                  (0)                                               /*!< RTC_T::CAL: DAY Position               */
#define RTC_CAL_DAY_Msk                  (0xful << RTC_CAL_DAY_Pos)                        /*!< RTC_T::CAL: DAY Mask                   */

#define RTC_CAL_TENDAY_Pos               (4)                                               /*!< RTC_T::CAL: TENDAY Position            */
#define RTC_CAL_TENDAY_Msk               (0x3ul << RTC_CAL_TENDAY_Pos)                     /*!< RTC_T::CAL: TENDAY Mask                */

#define RTC_CAL_MON_Pos                  (8)                                               /*!< RTC_T::CAL: MON Position               */
#define RTC_CAL_MON_Msk                  (0xful << RTC_CAL_MON_Pos)                        /*!< RTC_T::CAL: MON Mask                   */

#define RTC_CAL_TENMON_Pos               (12)                                              /*!< RTC_T::CAL: TENMON Position            */
#define RTC_CAL_TENMON_Msk               (0x1ul << RTC_CAL_TENMON_Pos)                     /*!< RTC_T::CAL: TENMON Mask                */

#define RTC_CAL_YEAR_Pos                 (16)                                              /*!< RTC_T::CAL: YEAR Position              */
#define RTC_CAL_YEAR_Msk                 (0xful << RTC_CAL_YEAR_Pos)                       /*!< RTC_T::CAL: YEAR Mask                  */

#define RTC_CAL_TENYEAR_Pos              (20)                                              /*!< RTC_T::CAL: TENYEAR Position           */
#define RTC_CAL_TENYEAR_Msk              (0xful << RTC_CAL_TENYEAR_Pos)                    /*!< RTC_T::CAL: TENYEAR Mask               */

#define RTC_CLKFMT_24HEN_Pos             (0)                                               /*!< RTC_T::CLKFMT: 24HEN Position          */
#define RTC_CLKFMT_24HEN_Msk             (0x1ul << RTC_CLKFMT_24HEN_Pos)                   /*!< RTC_T::CLKFMT: 24HEN Mask              */

#define RTC_WEEKDAY_WEEKDAY_Pos          (0)                                               /*!< RTC_T::WEEKDAY: WEEKDAY Position       */
#define RTC_WEEKDAY_WEEKDAY_Msk          (0x7ul << RTC_WEEKDAY_WEEKDAY_Pos)                /*!< RTC_T::WEEKDAY: WEEKDAY Mask           */

#define RTC_TALM_SEC_Pos                 (0)                                               /*!< RTC_T::TALM: SEC Position              */
#define RTC_TALM_SEC_Msk                 (0xful << RTC_TALM_SEC_Pos)                       /*!< RTC_T::TALM: SEC Mask                  */

#define RTC_TALM_TENSEC_Pos              (4)                                               /*!< RTC_T::TALM: TENSEC Position           */
#define RTC_TALM_TENSEC_Msk              (0x7ul << RTC_TALM_TENSEC_Pos)                    /*!< RTC_T::TALM: TENSEC Mask               */

#define RTC_TALM_MIN_Pos                 (8)                                               /*!< RTC_T::TALM: MIN Position              */
#define RTC_TALM_MIN_Msk                 (0xful << RTC_TALM_MIN_Pos)                       /*!< RTC_T::TALM: MIN Mask                  */

#define RTC_TALM_TENMIN_Pos              (12)                                              /*!< RTC_T::TALM: TENMIN Position           */
#define RTC_TALM_TENMIN_Msk              (0x7ul << RTC_TALM_TENMIN_Pos)                    /*!< RTC_T::TALM: TENMIN Mask               */

#define RTC_TALM_HR_Pos                  (16)                                              /*!< RTC_T::TALM: HR Position               */
#define RTC_TALM_HR_Msk                  (0xful << RTC_TALM_HR_Pos)                        /*!< RTC_T::TALM: HR Mask                   */

#define RTC_TALM_TENHR_Pos               (20)                                              /*!< RTC_T::TALM: TENHR Position            */
#define RTC_TALM_TENHR_Msk               (0x3ul << RTC_TALM_TENHR_Pos)                     /*!< RTC_T::TALM: TENHR Mask                */

#define RTC_CALM_DAY_Pos                 (0)                                               /*!< RTC_T::CALM: DAY Position              */
#define RTC_CALM_DAY_Msk                 (0xful << RTC_CALM_DAY_Pos)                       /*!< RTC_T::CALM: DAY Mask                  */

#define RTC_CALM_TENDAY_Pos              (4)                                               /*!< RTC_T::CALM: TENDAY Position           */
#define RTC_CALM_TENDAY_Msk              (0x3ul << RTC_CALM_TENDAY_Pos)                    /*!< RTC_T::CALM: TENDAY Mask               */

#define RTC_CALM_MON_Pos                 (8)                                               /*!< RTC_T::CALM: MON Position              */
#define RTC_CALM_MON_Msk                 (0xful << RTC_CALM_MON_Pos)                       /*!< RTC_T::CALM: MON Mask                  */

#define RTC_CALM_TENMON_Pos              (12)                                              /*!< RTC_T::CALM: TENMON Position           */
#define RTC_CALM_TENMON_Msk              (0x1ul << RTC_CALM_TENMON_Pos)                    /*!< RTC_T::CALM: TENMON Mask               */

#define RTC_CALM_YEAR_Pos                (16)                                              /*!< RTC_T::CALM: YEAR Position             */
#define RTC_CALM_YEAR_Msk                (0xful << RTC_CALM_YEAR_Pos)                      /*!< RTC_T::CALM: YEAR Mask                 */

#define RTC_CALM_TENYEAR_Pos             (20)                                              /*!< RTC_T::CALM: TENYEAR Position          */
#define RTC_CALM_TENYEAR_Msk             (0xful << RTC_CALM_TENYEAR_Pos)                   /*!< RTC_T::CALM: TENYEAR Mask              */

#define RTC_LEAPYEAR_LEAPYEAR_Pos        (0)                                               /*!< RTC_T::LEAPYEAR: LEAPYEAR Position     */
#define RTC_LEAPYEAR_LEAPYEAR_Msk        (0x1ul << RTC_LEAPYEAR_LEAPYEAR_Pos)              /*!< RTC_T::LEAPYEAR: LEAPYEAR Mask         */

#define RTC_INTEN_ALMIEN_Pos             (0)                                               /*!< RTC_T::INTEN: ALMIEN Position          */
#define RTC_INTEN_ALMIEN_Msk             (0x1ul << RTC_INTEN_ALMIEN_Pos)                   /*!< RTC_T::INTEN: ALMIEN Mask              */

#define RTC_INTEN_TICKIEN_Pos            (1)                                               /*!< RTC_T::INTEN: TICKIEN Position         */
#define RTC_INTEN_TICKIEN_Msk            (0x1ul << RTC_INTEN_TICKIEN_Pos)                  /*!< RTC_T::INTEN: TICKIEN Mask             */

#define RTC_INTEN_WAKEUPIEN_Pos          (2)                                               /*!< RTC INTEN: WAKEUPIEN Position            */
#define RTC_INTEN_WAKEUPIEN_Msk          (0x1ul << RTC_INTEN_WAKEUPIEN_Pos)                /*!< RTC INTEN: WAKEUPIEN Mask                */

#define RTC_INTEN_RELALMIEN_Pos          (4)                                               /*!< RTC INTEN: RELALMIEN Position            */
#define RTC_INTEN_RELALMIEN_Msk          (0x1ul << RTC_INTEN_RELALMIEN_Pos)                /*!< RTC INTEN: RELALMIEN Mask                */

#define RTC_INTSTS_ALMIF_Pos             (0)                                               /*!< RTC_T::INTSTS: ALMIF Position          */
#define RTC_INTSTS_ALMIF_Msk             (0x1ul << RTC_INTSTS_ALMIF_Pos)                   /*!< RTC_T::INTSTS: ALMIF Mask              */

#define RTC_INTSTS_TICKIF_Pos            (1)                                               /*!< RTC_T::INTSTS: TICKIF Position         */
#define RTC_INTSTS_TICKIF_Msk            (0x1ul << RTC_INTSTS_TICKIF_Pos)                  /*!< RTC_T::INTSTS: TICKIF Mask             */

#define RTC_INTSTS_WAKEUPINT_Pos          (2)                                              /*!< RTC INTSTS: WAKEUPINT Position            */
#define RTC_INTSTS_WAKEUPINT_Msk          (0x1ul << RTC_INTSTS_WAKEUPINT_Pos)              /*!< RTC INTSTS: WAKEUPINT Mask                */

#define RTC_INTSTS_REGWRBUSY_Pos          (31)                                             /*!< RTC INTSTS: REGWRBUSY Position            */
#define RTC_INTSTS_REGWRBUSY_Msk          (0x1ul << RTC_INTSTS_REGWRBUSY_Pos)              /*!< RTC INTSTS: REGWRBUSY Mask                */

#define RTC_TICK_TICK_Pos                (0)                                               /*!< RTC_T::TICK: TICK Position             */
#define RTC_TICK_TICK_Msk                (0x7ul << RTC_TICK_TICK_Pos)                      /*!< RTC_T::TICK: TICK Mask                 */

#define RTC_PWRCTL_ALARM_EN_Pos          (3)
#define RTC_PWRCTL_ALARM_EN_Msk          (0x1ul << RTC_PWRCTL_ALARM_EN_Pos)

#define RTC_PWRCTL_REL_ALARM_EN_Pos      (4)
#define RTC_PWRCTL_REL_ALARM_EN_Msk      (0x1ul << RTC_PWRCTL_REL_ALARM_EN_Pos)

#define RTC_PWRCTL_RELALM_TIME_Pos       (16)
#define RTC_PWRCTL_RELALM_TIME_Msk       (0xffful << RTC_PWRCTL_RELALM_TIME_Pos)

#define RTC_SPR0_SPARE_Pos               (0)                                               /*!< RTC_T::SPR0: SPARE Position            */
#define RTC_SPR0_SPARE_Msk               (0xfffffffful << RTC_SPR0_SPARE_Pos)              /*!< RTC_T::SPR0: SPARE Mask                */

#define RTC_SPR1_SPARE_Pos               (0)                                               /*!< RTC_T::SPR1: SPARE Position            */
#define RTC_SPR1_SPARE_Msk               (0xfffffffful << RTC_SPR1_SPARE_Pos)              /*!< RTC_T::SPR1: SPARE Mask                */

#define RTC_SPR2_SPARE_Pos               (0)                                               /*!< RTC_T::SPR2: SPARE Position            */
#define RTC_SPR2_SPARE_Msk               (0xfffffffful << RTC_SPR2_SPARE_Pos)              /*!< RTC_T::SPR2: SPARE Mask                */

#define RTC_SPR3_SPARE_Pos               (0)                                               /*!< RTC_T::SPR3: SPARE Position            */
#define RTC_SPR3_SPARE_Msk               (0xfffffffful << RTC_SPR3_SPARE_Pos)              /*!< RTC_T::SPR3: SPARE Mask                */

#define RTC_SPR4_SPARE_Pos               (0)                                               /*!< RTC_T::SPR4: SPARE Position            */
#define RTC_SPR4_SPARE_Msk               (0xfffffffful << RTC_SPR4_SPARE_Pos)              /*!< RTC_T::SPR4: SPARE Mask                */

#define RTC_SPR5_SPARE_Pos               (0)                                               /*!< RTC_T::SPR5: SPARE Position            */
#define RTC_SPR5_SPARE_Msk               (0xfffffffful << RTC_SPR5_SPARE_Pos)              /*!< RTC_T::SPR5: SPARE Mask                */

#define RTC_SPR6_SPARE_Pos               (0)                                               /*!< RTC_T::SPR6: SPARE Position            */
#define RTC_SPR6_SPARE_Msk               (0xfffffffful << RTC_SPR6_SPARE_Pos)              /*!< RTC_T::SPR6: SPARE Mask                */

#define RTC_SPR7_SPARE_Pos               (0)                                               /*!< RTC_T::SPR7: SPARE Position            */
#define RTC_SPR7_SPARE_Msk               (0xfffffffful << RTC_SPR7_SPARE_Pos)              /*!< RTC_T::SPR7: SPARE Mask                */

#define RTC_SPR8_SPARE_Pos               (0)                                               /*!< RTC_T::SPR8: SPARE Position            */
#define RTC_SPR8_SPARE_Msk               (0xfffffffful << RTC_SPR8_SPARE_Pos)              /*!< RTC_T::SPR8: SPARE Mask                */

#define RTC_SPR9_SPARE_Pos               (0)                                               /*!< RTC_T::SPR9: SPARE Position            */
#define RTC_SPR9_SPARE_Msk               (0xfffffffful << RTC_SPR9_SPARE_Pos)              /*!< RTC_T::SPR9: SPARE Mask                */

#define RTC_SPR10_SPARE_Pos              (0)                                               /*!< RTC_T::SPR10: SPARE Position           */
#define RTC_SPR10_SPARE_Msk              (0xfffffffful << RTC_SPR10_SPARE_Pos)             /*!< RTC_T::SPR10: SPARE Mask               */

#define RTC_SPR11_SPARE_Pos              (0)                                               /*!< RTC_T::SPR11: SPARE Position           */
#define RTC_SPR11_SPARE_Msk              (0xfffffffful << RTC_SPR11_SPARE_Pos)             /*!< RTC_T::SPR11: SPARE Mask               */

#define RTC_SPR12_SPARE_Pos              (0)                                               /*!< RTC_T::SPR12: SPARE Position           */
#define RTC_SPR12_SPARE_Msk              (0xfffffffful << RTC_SPR12_SPARE_Pos)             /*!< RTC_T::SPR12: SPARE Mask               */

#define RTC_SPR13_SPARE_Pos              (0)                                               /*!< RTC_T::SPR13: SPARE Position           */
#define RTC_SPR13_SPARE_Msk              (0xfffffffful << RTC_SPR13_SPARE_Pos)             /*!< RTC_T::SPR13: SPARE Mask               */

#define RTC_SPR14_SPARE_Pos              (0)                                               /*!< RTC_T::SPR14: SPARE Position           */
#define RTC_SPR14_SPARE_Msk              (0xfffffffful << RTC_SPR14_SPARE_Pos)             /*!< RTC_T::SPR14: SPARE Mask               */

#define RTC_SPR15_SPARE_Pos              (0)                                               /*!< RTC_T::SPR15: SPARE Position           */
#define RTC_SPR15_SPARE_Msk              (0xfffffffful << RTC_SPR15_SPARE_Pos)             /*!< RTC_T::SPR15: SPARE Mask               */


#define RTC                 ((RTC_T *)   RTC_BA)

/** @addtogroup RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/

/**
  * @brief      Indicate is Leap Year or not
  *
  * @param      None
  *
  * @retval     0   This year is not a leap year
  * @retval     1   This year is a leap year
  *
  * @details    According to current date, return this year is leap year or not.
  * \hideinitializer
  */
#define RTC_IS_LEAP_YEAR()              (RTC->LEAPYEAR & RTC_LEAPYEAR_LEAPYEAR_Msk ? 1:0)

/**
  * @brief      Clear RTC Alarm Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear RTC alarm interrupt flag.
  * \hideinitializer
  */
#define RTC_CLEAR_ALARM_INT_FLAG()      (RTC->INTSTS = RTC_INTSTS_ALMIF_Msk)

/**
  * @brief      Clear RTC Tick Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear RTC tick interrupt flag.
  * \hideinitializer
  */
#define RTC_CLEAR_TICK_INT_FLAG()       (RTC->INTSTS = RTC_INTSTS_TICKIF_Msk)

/**
  * @brief      Get RTC Alarm Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   RTC alarm interrupt did not occur
  * @retval     1   RTC alarm interrupt occurred
  *
  * @details    This macro indicates RTC alarm interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_ALARM_INT_FLAG()        ((RTC->INTSTS & RTC_INTSTS_ALMIF_Msk)? 1:0)

/**
  * @brief      Get RTC Time Tick Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   RTC time tick interrupt did not occur
  * @retval     1   RTC time tick interrupt occurred
  *
  * @details    This macro indicates RTC time tick interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_TICK_INT_FLAG()         ((RTC->INTSTS & RTC_INTSTS_TICKIF_Msk)? 1:0)

/**
  * @brief      Read Spare Register
  *
  * @param[in]  u32RegNum   The spare register number, 0~19.
  *
  * @return     Spare register content
  *
  * @details    Read the specify spare register content.
  * @note       The returned value is valid only when SPRRDY(SPRCTL[7] SPR Register Ready) bit is set. \n
  *             And its controlled by RTC Access Enable Register.
  * \hideinitializer
  */
#define RTC_READ_SPARE_REGISTER(u32RegNum)                  (RTC->SPR[(u32RegNum)])

/**
  * @brief      Write Spare Register
  *
  * @param[in]  u32RegNum    The spare register number, 0~19.
  * @param[in]  u32RegValue  The spare register value.
  *
  * @return     None
  *
  * @details    Write specify data to spare register.
  * @note       This macro is effect only when SPRRDY(SPRCTL[7] SPR Register Ready) bit is set. \n
  *             And its controlled by RTC Access Enable Register(RTC_RWEN).
  * \hideinitializer
  */
#define RTC_WRITE_SPARE_REGISTER(u32RegNum, u32RegValue)    (RTC->SPR[(u32RegNum)] = (u32RegValue))

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
void RTC_WaitAccessEnable(void);
void RTC_Check(void);

void RTC_Open(S_RTC_TIME_DATA_T *sPt);
void RTC_Close(void);
void RTC_32KCalibration(int32_t i32FrequencyX100);
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_SetDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek);
void RTC_SetTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm);
void RTC_SetAlarmDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek);
void RTC_SetAlarmTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm);
uint32_t RTC_GetDayOfWeek(void);
void RTC_SetTickPeriod(uint32_t u32TickSelection);
void RTC_EnableInt(uint32_t u32IntFlagMask);
void RTC_DisableInt(uint32_t u32IntFlagMask);
void RTC_EnableSpareAccess(void);
void RTC_DisableSpareRegister(void);

/*@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group RTC_Driver */

/*@}*/ /* end of group Standard_Driver */


#endif /* __NU_RTC_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
