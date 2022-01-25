/**************************************************************************//**
* @file     RTC.h
* @brief    N9H30 RTC driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_RTC_H__
#define __NU_RTC_H__


/*---------------------------------------------------------------------------------------------------------*/
/* Includes of system headers                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#include "N9H30.h"
#include "nu_sys.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_RTC_Driver RTC Driver
  @{
*/

/** @addtogroup N9H30_RTC_EXPORTED_CONSTANTS RTC Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* Define Error Code                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define E_RTC_SUCCESS                   0   /*!< success */
#define E_RTC_ERR_CALENDAR_VALUE        1   /*!< Wrong Calendar Value */
#define E_RTC_ERR_TIMESACLE_VALUE       2   /*!< Wrong Time Scale Value */
#define E_RTC_ERR_TIME_VALUE            3   /*!< Wrong Time Value */
#define E_RTC_ERR_DWR_VALUE             4   /*!< Wrong Day Value */
#define E_RTC_ERR_FCR_VALUE             5   /*!< Wrong Compenation value */
#define E_RTC_ERR_EIO                   6   /*!< Initial RTC Failed */
#define E_RTC_ERR_ENOTTY                7   /*!< Command not support, or parameter incorrect */
#define E_RTC_ERR_ENODEV                8   /*!< Interface number incorrect */

#define RTC_FCR_REFERENCE       32761   /*!< RTC Reference for frequency compensation */

#define RTC_INIT_KEY        0xa5eb1357   /*!< RTC Access Key   \hideinitializer */
#define RTC_WRITE_KEY       0xa965       /*!< RTC Access Key  \hideinitializer */

#define RTC_WAIT_COUNT      0xFFFFFFFF  /*!< Initial Time Out Value  \hideinitializer */

#define RTC_YEAR2000            2000   /*!< RTC Reference \hideinitializer */

#define RTC_LEAP_YEAR       1     /*!< RTC leap year \hideinitializer */

#define RTC_CLOCK_12            0   /*!< RTC 12 Hour  */
#define RTC_CLOCK_24            1   /*!< RTC 24 Hour  */

#define RTC_AM              1    /*!< RTC AM \hideinitializer */
#define RTC_PM              2    /*!< RTC PM \hideinitializer */

#define RTC_INIT_ACTIVE_Pos              (0)                                               /*!< RTC INIT: ACTIVE Position              */
#define RTC_INIT_ACTIVE_Msk              (0x1ul << RTC_INIT_ACTIVE_Pos)                    /*!< RTC INIT: ACTIVE Mask                  */

#define RTC_INIT_INIT_Pos                (0)                                               /*!< RTC INIT: INIT Position                */
#define RTC_INIT_INIT_Msk                (0xfffffffful << RTC_INIT_INIT_Pos)               /*!< RTC INIT: INIT Mask                    */

#define RTC_RWEN_RWENPASSWD_Pos          (0)                                               /*!< RTC RWEN: RWEN Position                */
#define RTC_RWEN_RWENPASSWD_Msk          (0xfffful << RTC_RWEN_RWEN_Pos)                   /*!< RTC RWEN: RWEN Mask                    */

#define RTC_RWEN_RWENF_Pos               (16)                                              /*!< RTC RWEN: RWENF Position               */
#define RTC_RWEN_RWENF_Msk               (0x1ul << RTC_RWEN_RWENF_Pos)                     /*!< RTC RWEN: RWENF Mask                   */

#define RTC_FREQADJ_FRACTION_Pos         (0)                                               /*!< RTC FREQADJ: FRACTION Position         */
#define RTC_FREQADJ_FRACTION_Msk         (0x3ful << RTC_FREQADJ_FRACTION_Pos)              /*!< RTC FREQADJ: FRACTION Mask             */

#define RTC_FREQADJ_INTEGER_Pos          (8)                                               /*!< RTC FREQADJ: INTEGER Position          */
#define RTC_FREQADJ_INTEGER_Msk          (0xful << RTC_FREQADJ_INTEGER_Pos)                /*!< RTC FREQADJ: INTEGER Mask              */

#define RTC_TIME_SEC_Pos                 (0)                                               /*!< RTC TIME: SEC Position                 */
#define RTC_TIME_SEC_Msk                 (0xful << RTC_TIME_SEC_Pos)                       /*!< RTC TIME: SEC Mask                     */

#define RTC_TIME_TENSEC_Pos              (4)                                               /*!< RTC TIME: TENSEC Position              */
#define RTC_TIME_TENSEC_Msk              (0x7ul << RTC_TIME_TENSEC_Pos)                    /*!< RTC TIME: TENSEC Mask                  */

#define RTC_TIME_MIN_Pos                 (8)                                               /*!< RTC TIME: MIN Position                 */
#define RTC_TIME_MIN_Msk                 (0xful << RTC_TIME_MIN_Pos)                       /*!< RTC TIME: MIN Mask                     */

#define RTC_TIME_TENMIN_Pos              (12)                                              /*!< RTC TIME: TENMIN Position              */
#define RTC_TIME_TENMIN_Msk              (0x7ul << RTC_TIME_TENMIN_Pos)                    /*!< RTC TIME: TENMIN Mask                  */

#define RTC_TIME_HR_Pos                  (16)                                              /*!< RTC TIME: HR Position                  */
#define RTC_TIME_HR_Msk                  (0xful << RTC_TIME_HR_Pos)                        /*!< RTC TIME: HR Mask                      */

#define RTC_TIME_TENHR_Pos               (20)                                              /*!< RTC TIME: TENHR Position               */
#define RTC_TIME_TENHR_Msk               (0x3ul << RTC_TIME_TENHR_Pos)                     /*!< RTC TIME: TENHR Mask                   */

#define RTC_CAL_DAY_Pos                  (0)                                               /*!< RTC CAL: DAY Position                  */
#define RTC_CAL_DAY_Msk                  (0xful << RTC_CAL_DAY_Pos)                        /*!< RTC CAL: DAY Mask                      */

#define RTC_CAL_TENDAY_Pos               (4)                                               /*!< RTC CAL: TENDAY Position               */
#define RTC_CAL_TENDAY_Msk               (0x3ul << RTC_CAL_TENDAY_Pos)                     /*!< RTC CAL: TENDAY Mask                   */

#define RTC_CAL_MON_Pos                  (8)                                               /*!< RTC CAL: MON Position                  */
#define RTC_CAL_MON_Msk                  (0xful << RTC_CAL_MON_Pos)                        /*!< RTC CAL: MON Mask                      */

#define RTC_CAL_TENMON_Pos               (12)                                              /*!< RTC CAL: TENMON Position               */
#define RTC_CAL_TENMON_Msk               (0x1ul << RTC_CAL_TENMON_Pos)                     /*!< RTC CAL: TENMON Mask                   */

#define RTC_CAL_YEAR_Pos                 (16)                                              /*!< RTC CAL: YEAR Position                 */
#define RTC_CAL_YEAR_Msk                 (0xful << RTC_CAL_YEAR_Pos)                       /*!< RTC CAL: YEAR Mask                     */

#define RTC_CAL_TENYEAR_Pos              (20)                                              /*!< RTC CAL: TENYEAR Position              */
#define RTC_CAL_TENYEAR_Msk              (0xful << RTC_CAL_TENYEAR_Pos)                    /*!< RTC CAL: TENYEAR Mask                  */

#define RTC_TIMEFMT_24HEN_Pos             (0)                                               /*!< RTC CLKFMT: 24HEN Position             */
#define RTC_TIMEFMT_24HEN_Msk             (0x1ul << RTC_CLKFMT_24HEN_Pos)                   /*!< RTC CLKFMT: 24HEN Mask                 */

#define RTC_WEEKDAY_WEEKDAY_Pos          (0)                                               /*!< RTC WEEKDAY: WEEKDAY Position          */
#define RTC_WEEKDAY_WEEKDAY_Msk          (0x7ul << RTC_WEEKDAY_WEEKDAY_Pos)                /*!< RTC WEEKDAY: WEEKDAY Mask              */

#define RTC_TALM_SEC_Pos                 (0)                                               /*!< RTC TALM: SEC Position                 */
#define RTC_TALM_SEC_Msk                 (0xful << RTC_TALM_SEC_Pos)                       /*!< RTC TALM: SEC Mask                     */

#define RTC_TALM_TENSEC_Pos              (4)                                               /*!< RTC TALM: TENSEC Position              */
#define RTC_TALM_TENSEC_Msk              (0x7ul << RTC_TALM_TENSEC_Pos)                    /*!< RTC TALM: TENSEC Mask                  */

#define RTC_TALM_MIN_Pos                 (8)                                               /*!< RTC TALM: MIN Position                 */
#define RTC_TALM_MIN_Msk                 (0xful << RTC_TALM_MIN_Pos)                       /*!< RTC TALM: MIN Mask                     */

#define RTC_TALM_TENMIN_Pos              (12)                                              /*!< RTC TALM: TENMIN Position              */
#define RTC_TALM_TENMIN_Msk              (0x7ul << RTC_TALM_TENMIN_Pos)                    /*!< RTC TALM: TENMIN Mask                  */

#define RTC_TALM_HR_Pos                  (16)                                              /*!< RTC TALM: HR Position                  */
#define RTC_TALM_HR_Msk                  (0xful << RTC_TALM_HR_Pos)                        /*!< RTC TALM: HR Mask                      */

#define RTC_TALM_TENHR_Pos               (20)                                              /*!< RTC TALM: TENHR Position               */
#define RTC_TALM_TENHR_Msk               (0x3ul << RTC_TALM_TENHR_Pos)                     /*!< RTC TALM: TENHR Mask                   */

#define RTC_CALM_DAY_Pos                 (0)                                               /*!< RTC CALM: DAY Position                 */
#define RTC_CALM_DAY_Msk                 (0xful << RTC_CALM_DAY_Pos)                       /*!< RTC CALM: DAY Mask                     */

#define RTC_CALM_TENDAY_Pos              (4)                                               /*!< RTC CALM: TENDAY Position              */
#define RTC_CALM_TENDAY_Msk              (0x3ul << RTC_CALM_TENDAY_Pos)                    /*!< RTC CALM: TENDAY Mask                  */

#define RTC_CALM_MON_Pos                 (8)                                               /*!< RTC CALM: MON Position                 */
#define RTC_CALM_MON_Msk                 (0xful << RTC_CALM_MON_Pos)                       /*!< RTC CALM: MON Mask                     */

#define RTC_CALM_TENMON_Pos              (12)                                              /*!< RTC CALM: TENMON Position              */
#define RTC_CALM_TENMON_Msk              (0x1ul << RTC_CALM_TENMON_Pos)                    /*!< RTC CALM: TENMON Mask                  */

#define RTC_CALM_YEAR_Pos                (16)                                              /*!< RTC CALM: YEAR Position                */
#define RTC_CALM_YEAR_Msk                (0xful << RTC_CALM_YEAR_Pos)                      /*!< RTC CALM: YEAR Mask                    */

#define RTC_CALM_TENYEAR_Pos             (20)                                              /*!< RTC CALM: TENYEAR Position             */
#define RTC_CALM_TENYEAR_Msk             (0xful << RTC_CALM_TENYEAR_Pos)                   /*!< RTC CALM: TENYEAR Mask                 */

#define RTC_CALM_WEEKDAY_Pos             (24)                                              /*!< RTC CALM: WEEKDAY Position             */
#define RTC_CALM_WEEKDAY_Msk             (0x7ul << RTC_CALM_WEEKDAY_Pos)                   /*!< RTC CALM: WEEKDAY Mask                 */

#define RTC_CALM_DAYALM_MSK_Pos          (28)                                              /*!< RTC CALM: DAYALM_MSK Position             */
#define RTC_CALM_DAYALM_MSK_Msk          (0x1ul << RTC_CALM_DAYALM_MSK_Pos)                /*!< RTC CALM: DAYALM_MSK Mask                 */

#define RTC_CALM_MONALM_MSK_Pos          (29)                                              /*!< RTC CALM: MONALM_MSK Position             */
#define RTC_CALM_MONALM_MSK_Msk          (0x1ul << RTC_CALM_MONALM_MSK_Pos)                /*!< RTC CALM: MONALM_MSK Mask                 */

#define RTC_CALM_YRALM_MSK_Pos           (30)                                              /*!< RTC CALM: YRALM_MSK Position             */
#define RTC_CALM_YRALM_MSK_Msk           (0x1ul << RTC_CALM_YRALM_MSK_Pos)                 /*!< RTC CALM: YRALM_MSK Mask                 */

#define RTC_CALM_WKDALM_MSK_Pos          (31)                                              /*!< RTC CALM: WKDALM_MSK Position             */
#define RTC_CALM_WKDALM_MSK_Msk          (0x1ul << RTC_CALM_WKDALM_MSK_Pos)                /*!< RTC CALM: WKDALM_MSK Mask                 */


#define RTC_LEAPYEAR_LEAPYEAR_Pos        (0)                                               /*!< RTC LEAPYEAR: LEAPYEAR Position        */
#define RTC_LEAPYEAR_LEAPYEAR_Msk        (0x1ul << RTC_LEAPYEAR_LEAPYEAR_Pos)              /*!< RTC LEAPYEAR: LEAPYEAR Mask            */

#define RTC_INTEN_ALMIEN_Pos             (0)                                               /*!< RTC INTEN: ALMIEN Position             */
#define RTC_INTEN_ALMIEN_Msk             (0x1ul << RTC_INTEN_ALMIEN_Pos)                   /*!< RTC INTEN: ALMIEN Mask                 */

#define RTC_INTEN_TICKIEN_Pos            (1)                                               /*!< RTC INTEN: TICKIEN Position            */
#define RTC_INTEN_TICKIEN_Msk            (0x1ul << RTC_INTEN_TICKIEN_Pos)                  /*!< RTC INTEN: TICKIEN Mask                */

#define RTC_INTEN_WAKEUPIEN_Pos          (2)                                               /*!< RTC INTEN: WAKEUPIEN Position            */
#define RTC_INTEN_WAKEUPIEN_Msk          (0x1ul << RTC_INTEN_WAKEUPIEN_Pos)                /*!< RTC INTEN: WAKEUPIEN Mask                */

#define RTC_INTEN_PWRSWIEN_Pos           (3)                                               /*!< RTC INTEN: PWRSWIEN Position            */
#define RTC_INTEN_PWRSWIEN_Msk           (0x1ul << RTC_INTEN_PWRSWIEN_Pos)                 /*!< RTC INTEN: PWRSWIEN Mask                */

#define RTC_INTEN_RELALMIEN_Pos          (4)                                               /*!< RTC INTEN: RELALMIEN Position            */
#define RTC_INTEN_RELALMIEN_Msk          (0x1ul << RTC_INTEN_RELALMIEN_Pos)                /*!< RTC INTEN: RELALMIEN Mask                */

#define RTC_INTEN_KEYPRESIEN_Pos         (5)                                               /*!< RTC INTEN: KEYPRESIEN Position            */
#define RTC_INTEN_KEYPRESIEN_Msk         (0x1ul << RTC_INTEN_KEYPRESIEN_Pos)               /*!< RTC INTEN: KEYPRESIEN Mask                */


#define RTC_INTSTS_ALMINT_Pos             (0)                                              /*!< RTC INTSTS: ALMINT Position             */
#define RTC_INTSTS_ALMINT_Msk             (0x1ul << RTC_INTSTS_ALMINT_Pos)                 /*!< RTC INTSTS: ALMINT Mask                 */

#define RTC_INTSTS_TICKINT_Pos            (1)                                              /*!< RTC INTSTS: TICKINT Position            */
#define RTC_INTSTS_TICKINT_Msk            (0x1ul << RTC_INTSTS_TICKINT_Pos)                /*!< RTC INTSTS: TICKINT Mask                */

#define RTC_INTSTS_WAKEUPINT_Pos          (2)                                              /*!< RTC INTSTS: WAKEUPINT Position            */
#define RTC_INTSTS_WAKEUPINT_Msk          (0x1ul << RTC_INTSTS_WAKEUPINT_Pos)              /*!< RTC INTSTS: WAKEUPINT Mask                */

#define RTC_INTSTS_PWRSWINT_Pos           (3)                                              /*!< RTC INTSTS: PWRSWINT Position            */
#define RTC_INTSTS_PWRSWINT_Msk           (0x1ul << RTC_INTSTS_PWRSWINT_Pos)               /*!< RTC INTSTS: PWRSWINT Mask                */

#define RTC_INTSTS_RELALMINT_Pos          (4)                                              /*!< RTC INTSTS: RELALMINT Position            */
#define RTC_INTSTS_RELALMINT_Msk          (0x1ul << RTC_INTSTS_RELALMINT_Pos)              /*!< RTC INTSTS: RELALMINT Mask                */

#define RTC_INTSTS_KEYPRESINT_Pos         (5)                                              /*!< RTC INTSTS: KEYPRESINT Position            */
#define RTC_INTSTS_KEYPRESINT_Msk         (0x1ul << RTC_INTSTS_KEYPRESINT_Pos)             /*!< RTC INTSTS: KEYPRESINT Mask                */

#define RTC_INTSTS_REGWRBUSY_Pos          (31)                                             /*!< RTC INTSTS: REGWRBUSY Position            */
#define RTC_INTSTS_REGWRBUSY_Msk          (0x1ul << RTC_INTSTS_REGWRBUSY_Pos)              /*!< RTC INTSTS: REGWRBUSY Mask                */


#define RTC_TICK_TTR_Pos                  (0)                                              /*!< RTC TICK: TTR Position                */
#define RTC_TICK_TTR_Msk                  (0x7ul << RTC_TICK_TTR_Pos)                      /*!< RTC TICK: TTR Mask                    */

#define RTC_PWRCTL_PWR_ON_Pos             (0)                                              /*!< RTC PWRCTL: PWR_ON Position               */
#define RTC_PWRCTL_PWR_ON_Msk             (0x1ul << RTC_PWRCTL_PWR_ON_Pos)                 /*!< RTC PWRCTL: PWR_ON Mask                   */

#define RTC_PWRCTL_SW_PCLR_Pos            (1)                                              /*!< RTC PWRCTL: SW_PCLR Position               */
#define RTC_PWRCTL_SW_PCLR_Msk            (0x1ul << RTC_PWRCTL_SW_PCLR_Pos)                /*!< RTC PWRCTL: SW_PCLR Mask                   */

#define RTC_PWRCTL_HW_PCLR_EN_Pos         (2)                                              /*!< RTC PWRCTL: HW_PCLR_EN Position               */
#define RTC_PWRCTL_HW_PCLR_EN_Msk         (0x1ul << RTC_PWRCTL_HW_PCLR_EN_Pos)             /*!< RTC PWRCTL: HW_PCLR_EN Mask                   */

#define RTC_PWRCTL_ALARM_EN_Pos           (3)                                              /*!< RTC PWRCTL: ALARM_EN Position               */
#define RTC_PWRCTL_ALARM_EN_Msk           (0x1ul << RTC_PWRCTL_ALARM_EN_Pos)               /*!< RTC PWRCTL: ALARM_EN Mask                   */

#define RTC_PWRCTL_REL_ALARM_EN_Pos       (4)                                              /*!< RTC PWRCTL: REL_ALARM_EN Position               */
#define RTC_PWRCTL_REL_ALARM_EN_Msk       (0x1ul << RTC_PWRCTL_REL_ALARM_EN_Pos)           /*!< RTC PWRCTL: REL_ALARM_EN Mask                   */

#define RTC_PWRCTL_EDGE_TRIG_Pos          (5)                                              /*!< RTC PWRCTL: EDGE_TRIG Position               */
#define RTC_PWRCTL_EDGE_TRIG_Msk          (0x1ul << RTC_PWRCTL_EDGE_TRIG_Pos)              /*!< RTC PWRCTL: EDGE_TRIG Mask                   */

#define RTC_PWRCTL_TIMEUNITL_Pos          (6)                                              /*!< RTC PWRCTL: TIMEUNITL Position               */
#define RTC_PWRCTL_TIMEUNITL_Msk          (0x1ul << RTC_PWRCTL_TIMEUNITLPos)               /*!< RTC PWRCTL: TIMEUNITL Mask                   */

#define RTC_PWRCTL_PWR_KEY_Pos            (7)                                              /*!< RTC PWRCTL: PWR_KEY Position               */
#define RTC_PWRCTL_PWR_KEY_Msk            (0x1ul << RTC_PWRCTL_PWR_KEY_Pos)                /*!< RTC PWRCTL: PWR_KEY Mask                   */

#define RTC_PWRCTL_PWRON_TIME_Pos         (8)                                              /*!< RTC PWRCTL: PWRON_TIME Position               */
#define RTC_PWRCTL_PWRON_TIME_Msk         (0xful << RTC_PWRCTL_PWRON_TIME_Pos)             /*!< RTC PWRCTL: PWRON_TIME Mask                   */

#define RTC_PWRCTL_PWROFF_TIME_Pos        (12)                                             /*!< RTC PWRCTL: PWROFF_TIME Position               */
#define RTC_PWRCTL_PWROFF_TIME_Msk        (0xful << RTC_PWRCTL_PWROFF_TIME_Pos)            /*!< RTC PWRCTL: PWROFF_TIME Mask                   */

#define RTC_PWRCTL_RELALM_TIME_Pos        (16)                                             /*!< RTC PWRCTL: RELALM_TIME Position               */
#define RTC_PWRCTL_RELALM_TIME_Msk        (0xffful << RTC_PWRCTL_RELALM_TIME_Pos)          /*!< RTC PWRCTL: RELALM_TIME Mask                   */

#define RTC_PWRCTL_ALARM_MODE_Pos         (28)                                             /*!< RTC PWRCTL: ALARM_MODE Position               */
#define RTC_PWRCTL_ALARM_MODE_Msk         (0x1ul << RTC_PWRCTL_ALARM_MODE_Pos)             /*!< RTC PWRCTL: ALARM_MODE Mask                   */


#define RTC_SPRCTL_SNPDEN_Pos            (0)                                               /*!< RTC SPRCTL: SNPDEN Position            */
#define RTC_SPRCTL_SNPDEN_Msk            (0x1ul << RTC_SPRCTL_SNPDEN_Pos)                  /*!< RTC SPRCTL: SNPDEN Mask                */

#define RTC_SPRCTL_SNPTYPE0_Pos          (1)                                               /*!< RTC SPRCTL: SNPTYPE0 Position          */
#define RTC_SPRCTL_SNPTYPE0_Msk          (0x1ul << RTC_SPRCTL_SNPTYPE0_Pos)                /*!< RTC SPRCTL: SNPTYPE0 Mask              */

#define RTC_SPRCTL_SPRRWEN_Pos           (2)                                               /*!< RTC SPRCTL: SPRRWEN Position           */
#define RTC_SPRCTL_SPRRWEN_Msk           (0x1ul << RTC_SPRCTL_SPRRWEN_Pos)                 /*!< RTC SPRCTL: SPRRWEN Mask               */

#define RTC_SPRCTL_SNPTYPE1_Pos          (3)                                               /*!< RTC SPRCTL: SNPTYPE1 Position          */
#define RTC_SPRCTL_SNPTYPE1_Msk          (0x1ul << RTC_SPRCTL_SNPTYPE1_Pos)                /*!< RTC SPRCTL: SNPTYPE1 Mask              */

#define RTC_SPRCTL_SPRCSTS_Pos           (5)                                               /*!< RTC SPRCTL: SPRCSTS Position           */
#define RTC_SPRCTL_SPRCSTS_Msk           (0x1ul << RTC_SPRCTL_SPRCSTS_Pos)                 /*!< RTC SPRCTL: SPRCSTS Mask               */

#define RTC_SPRCTL_SPRRWRDY_Pos          (7)                                               /*!< RTC SPRCTL: SPRRWRDY Position          */
#define RTC_SPRCTL_SPRRWRDY_Msk          (0x1ul << RTC_SPRCTL_SPRRWRDY_Pos)                /*!< RTC SPRCTL: SPRRWRDY Mask              */

#define RTC_SPR0_SPARE_Pos               (0)                                               /*!< RTC SPR0: SPARE Position               */
#define RTC_SPR0_SPARE_Msk               (0xfffffffful << RTC_SPR0_SPARE_Pos)              /*!< RTC SPR0: SPARE Mask                   */

#define RTC_SPR1_SPARE_Pos               (0)                                               /*!< RTC SPR1: SPARE Position               */
#define RTC_SPR1_SPARE_Msk               (0xfffffffful << RTC_SPR1_SPARE_Pos)              /*!< RTC SPR1: SPARE Mask                   */

#define RTC_SPR2_SPARE_Pos               (0)                                               /*!< RTC SPR2: SPARE Position               */
#define RTC_SPR2_SPARE_Msk               (0xfffffffful << RTC_SPR2_SPARE_Pos)              /*!< RTC SPR2: SPARE Mask                   */

#define RTC_SPR3_SPARE_Pos               (0)                                               /*!< RTC SPR3: SPARE Position               */
#define RTC_SPR3_SPARE_Msk               (0xfffffffful << RTC_SPR3_SPARE_Pos)              /*!< RTC SPR3: SPARE Mask                   */

#define RTC_SPR4_SPARE_Pos               (0)                                               /*!< RTC SPR4: SPARE Position               */
#define RTC_SPR4_SPARE_Msk               (0xfffffffful << RTC_SPR4_SPARE_Pos)              /*!< RTC SPR4: SPARE Mask                   */

#define RTC_SPR5_SPARE_Pos               (0)                                               /*!< RTC SPR5: SPARE Position               */
#define RTC_SPR5_SPARE_Msk               (0xfffffffful << RTC_SPR5_SPARE_Pos)              /*!< RTC SPR5: SPARE Mask                   */

#define RTC_SPR6_SPARE_Pos               (0)                                               /*!< RTC SPR6: SPARE Position               */
#define RTC_SPR6_SPARE_Msk               (0xfffffffful << RTC_SPR6_SPARE_Pos)              /*!< RTC SPR6: SPARE Mask                   */

#define RTC_SPR7_SPARE_Pos               (0)                                               /*!< RTC SPR7: SPARE Position               */
#define RTC_SPR7_SPARE_Msk               (0xfffffffful << RTC_SPR7_SPARE_Pos)              /*!< RTC SPR7: SPARE Mask                   */

#define RTC_SPR8_SPARE_Pos               (0)                                               /*!< RTC SPR8: SPARE Position               */
#define RTC_SPR8_SPARE_Msk               (0xfffffffful << RTC_SPR8_SPARE_Pos)              /*!< RTC SPR8: SPARE Mask                   */

#define RTC_SPR9_SPARE_Pos               (0)                                               /*!< RTC SPR9: SPARE Position               */
#define RTC_SPR9_SPARE_Msk               (0xfffffffful << RTC_SPR9_SPARE_Pos)              /*!< RTC SPR9: SPARE Mask                   */

#define RTC_SPR10_SPARE_Pos              (0)                                               /*!< RTC SPR10: SPARE Position              */
#define RTC_SPR10_SPARE_Msk              (0xfffffffful << RTC_SPR10_SPARE_Pos)             /*!< RTC SPR10: SPARE Mask                  */

#define RTC_SPR11_SPARE_Pos              (0)                                               /*!< RTC SPR11: SPARE Position              */
#define RTC_SPR11_SPARE_Msk              (0xfffffffful << RTC_SPR11_SPARE_Pos)             /*!< RTC SPR11: SPARE Mask                  */

#define RTC_SPR12_SPARE_Pos              (0)                                               /*!< RTC SPR12: SPARE Position              */
#define RTC_SPR12_SPARE_Msk              (0xfffffffful << RTC_SPR12_SPARE_Pos)             /*!< RTC SPR12: SPARE Mask                  */

#define RTC_SPR13_SPARE_Pos              (0)                                               /*!< RTC SPR13: SPARE Position              */
#define RTC_SPR13_SPARE_Msk              (0xfffffffful << RTC_SPR13_SPARE_Pos)             /*!< RTC SPR13: SPARE Mask                  */

#define RTC_SPR14_SPARE_Pos              (0)                                               /*!< RTC SPR14: SPARE Position              */
#define RTC_SPR14_SPARE_Msk              (0xfffffffful << RTC_SPR14_SPARE_Pos)             /*!< RTC SPR14: SPARE Mask                  */

#define RTC_SPR15_SPARE_Pos              (0)                                               /*!< RTC SPR15: SPARE Position              */
#define RTC_SPR15_SPARE_Msk              (0xfffffffful << RTC_SPR15_SPARE_Pos)             /*!< RTC SPR15: SPARE Mask                  */

#define RTC_SPR16_SPARE_Pos              (0)                                               /*!< RTC SPR16: SPARE Position              */
#define RTC_SPR16_SPARE_Msk              (0xfffffffful << RTC_SPR16_SPARE_Pos)             /*!< RTC SPR16: SPARE Mask                  */

#define RTC_SPR17_SPARE_Pos              (0)                                               /*!< RTC SPR17: SPARE Position              */
#define RTC_SPR17_SPARE_Msk              (0xfffffffful << RTC_SPR17_SPARE_Pos)             /*!< RTC SPR17: SPARE Mask                  */

#define RTC_SPR18_SPARE_Pos              (0)                                               /*!< RTC SPR18: SPARE Position              */
#define RTC_SPR18_SPARE_Msk              (0xfffffffful << RTC_SPR18_SPARE_Pos)             /*!< RTC SPR18: SPARE Mask                  */

#define RTC_SPR19_SPARE_Pos              (0)                                               /*!< RTC SPR19: SPARE Position              */
#define RTC_SPR19_SPARE_Msk              (0xfffffffful << RTC_SPR19_SPARE_Pos)             /*!< RTC SPR19: SPARE Mask                  */

/**
  * @brief  RTC define interrupt source
  */
typedef enum
{
    RTC_ALARM_INT           = 0x01, /*!< Alarm interrupt */
    RTC_TICK_INT            = 0x02, /*!< Tick interrupt */
    RTC_WAKEUP_INT          = 0x04, /*!< Wake-up interrupt */
    RTC_PSWI_INT            = 0x08, /*!< Power switch interrupt */
    RTC_RELATIVE_ALARM_INT  = 0x10, /*!< Releative Alarm interrupt */
    RTC_KEY_PRESS_INT       = 0x20, /*!< Power Key press interrupt */
    RTC_ALL_INT             = 0x3F  /*!< All interrupt */
} RTC_INT_SOURCE;

/**
  * @brief  Define Ioctl commands
  */
typedef enum
{
    RTC_IOC_IDENTIFY_LEAP_YEAR      =  0,    /*!< Identify leap year */
    RTC_IOC_SET_TICK_MODE           =  1,    /*!< Set tick mode */
    RTC_IOC_GET_TICK                =  2,    /*!< Get tick count */
    RTC_IOC_RESTORE_TICK            =  3,    /*!< Reset tick count */
    RTC_IOC_ENABLE_INT              =  4,    /*!< Enable RTC interrupt */
    RTC_IOC_DISABLE_INT             =  5,    /*!< Disable RTC interrupt */
    RTC_IOC_SET_CURRENT_TIME        =  6,    /*!< Set current time */
    RTC_IOC_SET_ALAMRM_TIME         =  7,    /*!< set alarm time */
    RTC_IOC_SET_FREQUENCY           =  8,    /*!< Set frequency compensation value */
    RTC_IOC_SET_POWER_ON            =  9,    /*!< Set Power on */
    RTC_IOC_SET_POWER_OFF           =  10,    /*!< Set Power off*/
    RTC_IOC_SET_POWER_OFF_PERIOD    =  11,    /*!< Set Power off period */
    RTC_IOC_ENABLE_HW_POWEROFF      =  12,    /*!< Enable H/W Power off */
    RTC_IOC_DISABLE_HW_POWEROFF     =  13,    /*!< Disable H/W Power off */
    RTC_IOC_GET_POWERKEY_STATUS     =  14,    /*!< Get Power key status */
    RTC_IOC_SET_PSWI_CALLBACK       =  15,    /*!< Set Power switch isr call back function */
    //RTC_IOC_GET_SW_STATUS         =  16,
    //RTC_IOC_SET_SW_STATUS         =  17,
    RTC_IOC_SET_RELEATIVE_ALARM     =  18,    /*!< Set releative alarm */
    //RTC_IOC_SET_POWER_KEY_DELAY   =  19,
    //RTC_IOC_SET_CLOCK_SOURCE      =  20,
    //RTC_IOC_GET_CLOCK_SOURCE      =  21
} E_RTC_CMD;

/**
  * @brief  RTC define Tick mode
  */
typedef enum
{
    RTC_TICK_1_SEC       =         0,      /*!< Time tick is 1 second     */
    RTC_TICK_1_2_SEC     =         1,      /*!< Time tick is 1/2 second   */
    RTC_TICK_1_4_SEC     =         2,      /*!< Time tick is 1/4 second   */
    RTC_TICK_1_8_SEC     =         3,      /*!< Time tick is 1/8 second   */
    RTC_TICK_1_16_SEC    =         4,      /*!< Time tick is 1/16 second  */
    RTC_TICK_1_32_SEC    =         5,      /*!< Time tick is 1/32 second  */
    RTC_TICK_1_64_SEC    =         6,      /*!< Time tick is 1/64 second  */
    RTC_TICK_1_128_SEC   =         7       /*!< Time tick is 1/128 second */
} RTC_TICK;

typedef void (PFN_RTC_CALLBACK)(void);  /*!< Call back function \hideinitializer */

/**
  * @brief  RTC current/alarm time select
  */
typedef enum
{
    RTC_CURRENT_TIME    =    0,   /*!< Select current time */
    RTC_ALARM_TIME      =    1    /*!< Select alarm time */
} E_RTC_TIME_SELECT;

/**
  * @brief  RTC define Day of week parameter
  */
typedef enum
{
    RTC_SUNDAY         =   0,   /*!< Sunday    */
    RTC_MONDAY         =   1,   /*!< Monday    */
    RTC_TUESDAY        =   2,   /*!< Tuesday   */
    RTC_WEDNESDAY      =   3,   /*!< Wednesday */
    RTC_THURSDAY       =   4,   /*!< Thursday  */
    RTC_FRIDAY         =   5,   /*!< Friday    */
    RTC_SATURDAY       =   6    /*!< Saturday  */
} E_RTC_DWR_PARAMETER;


/**
  * @brief  RTC define Time Data Struct
  */
typedef struct
{
    UINT8 u8cClockDisplay;            /*!<  12-Hour, 24-Hour */
    UINT8 u8cAmPm;                    /*!<  Time Scale select 12-hr/24-hr */
    UINT32 u32cSecond;                /*!<  Second value */
    UINT32 u32cMinute;                /*!<  Minute value */
    UINT32 u32cHour;                  /*!<  Hour value */
    UINT32 u32cDayOfWeek;             /*!<  Day of week value */
    UINT32 u32cDay;                   /*!<  Day value */
    UINT32 u32cMonth;                 /*!<  Month value */
    UINT32 u32Year;                   /*!<  Year value */
    UINT32 u32AlarmMaskSecond;        /*!<  Alarm mask second */
    UINT32 u32AlarmMaskMinute;        /*!<  Alarm mask minute */
    UINT32 u32AlarmMaskHour;          /*!<  Alarm mask hour */
    PFN_RTC_CALLBACK *pfnAlarmCallBack;    /*!< Alarm ISR call back function */
} S_RTC_TIME_DATA_T;


/**
  * @brief  RTC define Tick Struct
  */
typedef struct
{
    UINT8 ucMode;                           /*!< Tick Mode  */
    PFN_RTC_CALLBACK *pfnTickCallBack;      /*!< Tick ISR call back function  */
} RTC_TICK_T;

/*@}*/ /* end of group N9H30_RTC_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/

UINT32 RTC_Init(void);
UINT32 RTC_Open(S_RTC_TIME_DATA_T *sPt);
UINT32 RTC_Ioctl(INT32 i32Num, E_RTC_CMD eCmd, UINT32 u32Arg0, UINT32 u32Arg1);
UINT32 RTC_Read(E_RTC_TIME_SELECT eTime, S_RTC_TIME_DATA_T *sPt);
UINT32 RTC_Write(E_RTC_TIME_SELECT eTime, S_RTC_TIME_DATA_T *sPt);
UINT32 RTC_DoFrequencyCompensation(INT32 i32FrequencyX100);
UINT32 RTC_WriteEnable(BOOL bEnable);
UINT32 RTC_Close(void);
void RTC_EnableClock(BOOL bEnable);
VOID RTC_Check(void);

#define RTC_DisableInt(u32IntFlag) RTC_Ioctl(0, RTC_IOC_DISABLE_INT, u32IntFlag, 0)
#define RTC_EnableInt(u32IntFlag)  RTC_Ioctl(0, RTC_IOC_ENABLE_INT, u32IntFlag, 0)
#define RTC_GET_TICK_INT_FLAG()    (inp32(REG_RTC_INTSTS)&RTC_TICK_INT)
#define RTC_GET_ALARM_INT_FLAG()   (inp32(REG_RTC_INTSTS)&RTC_ALARM_INT)

static __inline void RTC_CLEAR_TICK_INT_FLAG(void)
{
    RTC_WriteEnable(1);
    outp32(REG_RTC_INTSTS, RTC_TICK_INT);
    RTC_Check();
}

static __inline void RTC_CLEAR_ALARM_INT_FLAG(void)
{
    RTC_WriteEnable(1);
    outp32(REG_RTC_INTSTS, RTC_ALARM_INT);
    RTC_Check();
}


/*@}*/ /* end of group N9H30_RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_RTC_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef  __cplusplus
}
#endif

#endif /* __NU_RTC_H__ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/



