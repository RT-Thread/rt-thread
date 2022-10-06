
/**
 *  @Component:   RTC
 *
 *  @Filename:    hw_rtc.h
 *
 ============================================================================ */
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _HW_RTC_H_
#define _HW_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define RTC_SECOND               (0x0)
#define RTC_MINUTE               (0x4)
#define RTC_HOUR                 (0x8)
#define RTC_DAY                  (0xC)
#define RTC_MONTH                (0x10)
#define RTC_YEAR                 (0x14)
#define RTC_DOTW                 (0x18)
#define RTC_ALARMSECOND          (0x20)
#define RTC_ALARMMINUTE          (0x24)
#define RTC_ALARMHOUR            (0x28)
#define RTC_ALARMDAY             (0x2C)
#define RTC_ALARMMONTH           (0x30)
#define RTC_ALARMYEAR            (0x34)
#define RTC_CTRL                 (0x40)
#define RTC_STATUS               (0x44)
#define RTC_INTERRUPT            (0x48)
#define RTC_COMPLSB              (0x4C)
#define RTC_COMPMSB              (0x50)
#define RTC_OSC                  (0x54)
#define RTC_SCRATCH0             (0x60)
#define RTC_SCRATCH1             (0x64)
#define RTC_SCRATCH2             (0x68)
#define RTC_KICK0                (0x6C)
#define RTC_KICK1                (0x70)

/*------Definitions specific to RTC IP in AM335x -------- */
#define RTC_REVISION             (0x74)
#define RTC_SYSCONFIG            (0x78)
#define RTC_IRQWAKEEN            (0x7C)
#define RTC_ALARM2_SECONDS       (0x80)
#define RTC_ALARM2_MINUTES       (0x84)
#define RTC_ALARM2_HOURS         (0x88)
#define RTC_ALARM2_DAYS          (0x8C)
#define RTC_ALARM2_MONTHS        (0x90)
#define RTC_ALARM2_YEARS         (0x94)
#define RTC_PMIC                 (0x98)
#define RTC_DEBOUNCE             (0x9C)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* SECOND */


#define RTC_SECOND_SEC1         (0x00000070u)
#define RTC_SECOND_SEC1_SHIFT        (0x00000004u)

#define RTC_SECOND_SEC0         (0x0000000Fu)
#define RTC_SECOND_SEC0_SHIFT        (0x00000000u)


/* MINUTE */


#define RTC_MINUTE_MIN1         (0x00000070u)
#define RTC_MINUTE_MIN1_SHIFT        (0x00000004u)

#define RTC_MINUTE_MIN0         (0x0000000Fu)
#define RTC_MINUTE_MIN0_SHIFT        (0x00000000u)


/* HOUR */


#define RTC_HOUR_MERIDIEM       (0x00000080u)
#define RTC_HOUR_MERIDIEM_SHIFT      (0x00000007u)

#define RTC_HOUR_HOUR1          (0x00000030u)
#define RTC_HOUR_HOUR1_SHIFT         (0x00000004u)

#define RTC_HOUR_HOUR0          (0x0000000Fu)
#define RTC_HOUR_HOUR0_SHIFT         (0x00000000u)


/* DAY */


#define RTC_DAY_DAY1            (0x00000030u)
#define RTC_DAY_DAY1_SHIFT           (0x00000004u)

#define RTC_DAY_DAY0            (0x0000000Fu)
#define RTC_DAY_DAY0_SHIFT           (0x00000000u)


/* MONTH */


#define RTC_MONTH_MONTH1        (0x00000010u)
#define RTC_MONTH_MONTH1_SHIFT       (0x00000004u)

#define RTC_MONTH_MONTH0        (0x0000000Fu)
#define RTC_MONTH_MONTH0_SHIFT       (0x00000000u)


/* YEAR */


#define RTC_YEAR_YEAR1          (0x000000F0u)
#define RTC_YEAR_YEAR1_SHIFT         (0x00000004u)

#define RTC_YEAR_YEAR0          (0x0000000Fu)
#define RTC_YEAR_YEAR0_SHIFT         (0x00000000u)


/* DOTW */


#define RTC_DOTW_DOTW                (0x00000007u)
#define RTC_DOTW_DOTW_SHIFT          (0x00000000u)
#define RTC_DOTW_DOTW_SUN            (0x00000000u)
#define RTC_DOTW_DOTW_MON            (0x00000001u)
#define RTC_DOTW_DOTW_TUE            (0x00000002u)
#define RTC_DOTW_DOTW_WED            (0x00000003u)
#define RTC_DOTW_DOTW_THU            (0x00000004u)
#define RTC_DOTW_DOTW_FRI            (0x00000005u)
#define RTC_DOTW_DOTW_SAT            (0x00000006u)


/* ALARMSECOND */


#define RTC_ALARMSECOND_SEC1    (0x00000070u)
#define RTC_ALARMSECOND_SEC1_SHIFT   (0x00000004u)

#define RTC_ALARMSECOND_SEC0    (0x0000000Fu)
#define RTC_ALARMSECOND_SEC0_SHIFT   (0x00000000u)


/* ALARMMINUTE */


#define RTC_ALARMMINUTE_MIN1    (0x00000070u)
#define RTC_ALARMMINUTE_MIN1_SHIFT   (0x00000004u)

#define RTC_ALARMMINUTE_MIN0    (0x0000000Fu)
#define RTC_ALARMMINUTE_MIN0_SHIFT   (0x00000000u)


/* ALARMHOUR */


#define RTC_ALARMHOUR_MERIDIEM  (0x00000080u)
#define RTC_ALARMHOUR_MERIDIEM_SHIFT (0x00000007u)

#define RTC_ALARMHOUR_HOUR1     (0x00000030u)
#define RTC_ALARMHOUR_HOUR1_SHIFT    (0x00000004u)

#define RTC_ALARMHOUR_HOUR0     (0x0000000Fu)
#define RTC_ALARMHOUR_HOUR0_SHIFT    (0x00000000u)


/* ALARMDAY */


#define RTC_ALARMDAY_DAY1       (0x00000030u)
#define RTC_ALARMDAY_DAY1_SHIFT      (0x00000004u)

#define RTC_ALARMDAY_DAY0       (0x0000000Fu)
#define RTC_ALARMDAY_DAY0_SHIFT      (0x00000000u)


/* ALARMMONTH */


#define RTC_ALARMMONTH_MONTH1   (0x00000010u)
#define RTC_ALARMMONTH_MONTH1_SHIFT  (0x00000004u)

#define RTC_ALARMMONTH_MONTH0   (0x0000000Fu)
#define RTC_ALARMMONTH_MONTH0_SHIFT  (0x00000000u)


/* ALARMYEAR */


#define RTC_ALARMYEAR_YEAR1     (0x000000F0u)
#define RTC_ALARMYEAR_YEAR1_SHIFT    (0x00000004u)

#define RTC_ALARMYEAR_YEAR0     (0x0000000Fu)
#define RTC_ALARMYEAR_YEAR0_SHIFT    (0x00000000u)

/* CTRL */

/*----- Definition specific to RTC IP in AM1808 ----------*/
#define RTC_CTRL_SPLITPOWER     (0x00000080u)
#define RTC_CTRL_SPLITPOWER_SHIFT    (0x00000007u)
/*--------------------------------------------------------*/

#define RTC_CTRL_RTCDISABLE     (0x00000040u)
#define RTC_CTRL_RTCDISABLE_SHIFT    (0x00000006u)

#define RTC_CTRL_SET32COUNTER   (0x00000020u)
#define RTC_CTRL_SET32COUNTER_SHIFT  (0x00000005u)


/*-------- Definition specific to RTC IP in AM335x -------*/
#define RTC_CTRL_TEST_MODE      (0x00000010u)
#define RTC_CTRL_TEST_MODE_SHIFT      (0x00000004u)
#define RTC_CTRL_TEST_MODE_FUNCTIONAL_MODE    (0x0u)
#define RTC_CTRL_TEST_MODE_TEST_MODE    (0x1u)
/*--------------------------------------------------------*/

#define RTC_CTRL_HOURMODE       (0x00000008u)
#define RTC_CTRL_HOURMODE_SHIFT      (0x00000003u)

#define RTC_CTRL_AUTOCOMP       (0x00000004u)
#define RTC_CTRL_AUTOCOMP_SHIFT      (0x00000002u)

#define RTC_CTRL_ROUNDMIN       (0x00000002u)
#define RTC_CTRL_ROUNDMIN_SHIFT      (0x00000001u)

#define RTC_CTRL_RUN            (0x00000001u)
#define RTC_CTRL_RUN_SHIFT           (0x00000000u)


/* STATUS */

#define RTC_STATUS_ALARM2        (0x00000080u)
#define RTC_STATUS_ALARM2_SHIFT       (0x00000007u)

#define RTC_STATUS_ALARM        (0x00000040u)
#define RTC_STATUS_ALARM_SHIFT       (0x00000006u)

#define RTC_STATUS_DAYEVT       (0x00000020u)
#define RTC_STATUS_DAYEVT_SHIFT      (0x00000005u)

#define RTC_STATUS_HREVT        (0x00000010u)
#define RTC_STATUS_HREVT_SHIFT       (0x00000004u)

#define RTC_STATUS_MINEVT       (0x00000008u)
#define RTC_STATUS_MINEVT_SHIFT      (0x00000003u)

#define RTC_STATUS_SECEVT       (0x00000004u)
#define RTC_STATUS_SECEVT_SHIFT      (0x00000002u)

#define RTC_STATUS_RUN          (0x00000002u)
#define RTC_STATUS_RUN_SHIFT         (0x00000001u)

#define RTC_STATUS_BUSY         (0x00000001u)
#define RTC_STATUS_BUSY_SHIFT        (0x00000000u)

/* INTERRUPTS */

#define RTC_INTERRUPTS_ALARM2    (0x00000010u)
#define RTC_INTERRUPTS_ALARM2_SHIFT   (0x00000004u)

#define RTC_INTERRUPTS_ALARM    (0x00000008u)
#define RTC_INTERRUPTS_ALARM_SHIFT   (0x00000003u)

#define RTC_INTERRUPTS_TIMER    (0x00000004u)
#define RTC_INTERRUPTS_TIMER_SHIFT   (0x00000002u)

#define RTC_INTERRUPTS_EVERY    (0x00000003u)
#define RTC_INTERRUPTS_EVERY_SHIFT   (0x00000000u)
#define RTC_INTERRUPTS_EVERY_SECOND  (0x00000000u)
#define RTC_INTERRUPTS_EVERY_MINUTE  (0x00000001u)
#define RTC_INTERRUPTS_EVERY_HOUR    (0x00000002u)
#define RTC_INTERRUPTS_EVERY_DAY     (0x00000003u)

/* COMPLSB */

#define RTC_COMPLSB_COMPLSB     (0x000000FFu)
#define RTC_COMPLSB_COMPLSB_SHIFT    (0x00000000u)


/* COMPMSB */

#define RTC_COMPMSB_COMPMSB     (0x000000FFu)
#define RTC_COMPMSB_COMPMSB_SHIFT    (0x00000000u)

/* OSC */

/*----- Definition specific to RTC IP in AM1808 ----------*/
#define RTC_OSC_SWRESET         (0x00000020u)
#define RTC_OSC_SWRESET_SHIFT        (0x00000005u)
/*--------------------------------------------------------*/

/*----- Definitions specific to RTC IP in AM335x ---------*/
#define RTC_OSC_32KCLK_EN   (0x00000040u)
#define RTC_OSC_32KCLK_EN_SHIFT   (0x00000006u)
#define RTC_OSC_32KCLK_EN_DISABLE   (0x0)
#define RTC_OSC_32KCLK_EN_ENABLE   (0x1)

#define RTC_OSC_OSC32K_GZ   (0x00000010u)
#define RTC_OSC_OSC32K_GZ_SHIFT   (0x00000004u)
#define RTC_OSC_OSC32K_GZ_DISABLE   (0x1u)
#define RTC_OSC_OSC32K_GZ_ENABLE   (0x0u)

#define RTC_OSC_32KCLK_SEL   (0x00000008u)
#define RTC_OSC_32KCLK_SEL_SHIFT   (0x00000003u)
#define RTC_OSC_32KCLK_SEL_SELECT_EXTERNAL_CLK_SOURCE   (0x1u)
#define RTC_OSC_32KCLK_SEL_SELECT_INTERNAL_CLK_SOURCE   (0x0u)

#define RTC_OSC_RES_SELECT   (0x00000004u)
#define RTC_OSC_RES_SELECT_SHIFT   (0x00000002u)
#define RTC_OSC_RES_SELECT_EXTERNAL   (0x1u)
#define RTC_OSC_RES_SELECT_INTERNAL   (0x0u)
/*--------------------------------------------------------*/

/* SCRATCH0 */

#define RTC_SCRATCH0_SCRATCH0   (0xFFFFFFFFu)
#define RTC_SCRATCH0_SCRATCH0_SHIFT  (0x00000000u)


/* SCRATCH1 */

#define RTC_SCRATCH1_SCRATCH1   (0xFFFFFFFFu)
#define RTC_SCRATCH1_SCRATCH1_SHIFT  (0x00000000u)


/* SCRATCH2 */

#define RTC_SCRATCH2_SCRATCH2   (0xFFFFFFFFu)
#define RTC_SCRATCH2_SCRATCH2_SHIFT  (0x00000000u)

/* KICK0 */

#define RTC_KICK0_KICK0         (0xFFFFFFFFu)
#define RTC_KICK0_KICK0_SHIFT        (0x00000000u)

/* KICK1 */

#define RTC_KICK1_KICK1         (0xFFFFFFFFu)
#define RTC_KICK1_KICK1_SHIFT        (0x00000000u)

/*----- Definitions specific to RTC IP in AM335x ---------*/

/* REVISION */

#define RTC_REVISION_SCHEME      (0xC0000000u)
#define RTC_REVISION_SCHEME_SHIFT  (0x0000001Eu)

#define RTC_REVISION_FUNC        (0x0FFF0000u)
#define RTC_REVISION_FUNC_SHIFT    (0x00000010u)

#define RTC_REVISION_R_RTL       (0x0000F800u)
#define RTC_REVISION_R_RTL_SHIFT   (0x0000000Bu)

#define RTC_REVISION_X_MAJOR     (0x00000700u)
#define RTC_REVISION_X_MAJOR_SHIFT   (0x00000008u)

#define RTC_REVISION_CUSTOM      (0x000000C0u)
#define RTC_REVISION_CUSTOM_SHIFT    (0x00000006u)

#define RTC_REVISION_Y_MINOR     (0x0000003Fu)
#define RTC_REVISION_Y_MINOR_SHIFT   (0x00000000u)

/* SYSCONFIG */

#define RTC_SYSCONFIG_IDLEMODE   (0x00000003u)
#define RTC_SYSCONFIG_IDLEMODE_SHIFT   (0x00000000u)
#define RTC_SYSCONFIG_IDLEMODE_FORCE_IDLE_MODE   (0x0u)
#define RTC_SYSCONFIG_IDLEMODE_NO_IDLE_MODE   (0x1u)
#define RTC_SYSCONFIG_IDLEMODE_SMART_IDLE_MODE   (0x2u)
#define RTC_SYSCONFIG_IDLEMODE_SMART_IDLE_WAKEUP_CAPABLE_MODE   (0x3u)

/* IRQWAKEEN */

#define RTC_IRQ_WAKEEN_ALARM_WAKEEN   (0x00000002u)
#define RTC_IRQ_WAKEEN_ALARM_WAKEEN_SHIFT   (0x00000001u)
#define RTC_IRQ_WAKEEN_ALARM_WAKEEN_WAKEUP_DISABLED   (0x0u)
#define RTC_IRQ_WAKEEN_ALARM_WAKEEN_WAKEUP_ENABLED   (0x1u)

#define RTC_IRQ_WAKEEN_TIMER_WAKEEN   (0x00000001u)
#define RTC_IRQ_WAKEEN_TIMER_WAKEEN_SHIFT   (0x00000000u)
#define RTC_IRQ_WAKEEN_TIMER_WAKEEN_WAKEUP_DISABLED   (0x0u)
#define RTC_IRQ_WAKEEN_TIMER_WAKEEN_WAKEUP_ENABLED   (0x1u)

/* ALARM2_SECONDS_REG */
#define RTC_ALARM2_SECONDS_ALARM2_SEC0   (0x0000000Fu)
#define RTC_ALARM2_SECONDS_ALARM2_SEC0_SHIFT   (0x00000000u)

#define RTC_ALARM2_SECONDS_ALARM2_SEC1   (0x00000070u)
#define RTC_ALARM2_SECONDS_ALARM2_SEC1_SHIFT   (0x00000004u)

/* ALARM2_MINUTES_REG */
#define RTC_ALARM2_MINUTES_ALARM2_MIN0   (0x0000000Fu)
#define RTC_ALARM2_MINUTES_ALARM2_MIN0_SHIFT   (0x00000000u)

#define RTC_ALARM2_MINUTES_ALARM2_MIN1   (0x00000070u)
#define RTC_ALARM2_MINUTES_ALARM2_MIN1_SHIFT   (0x00000004u)

/* ALARM2_HOURS_REG */
#define RTC_ALARM2_HOURS_ALARM2_HOUR0   (0x0000000Fu)
#define RTC_ALARM2_HOURS_ALARM2_HOUR0_SHIFT   (0x00000000u)

#define RTC_ALARM2_HOURS_ALARM2_HOUR1   (0x00000030u)
#define RTC_ALARM2_HOURS_ALARM2_HOUR1_SHIFT   (0x00000004u)

#define RTC_ALARM2_HOURS_ALARM2_PM_NAM   (0x00000080u)
#define RTC_ALARM2_HOURS_ALARM2_PM_NAM_SHIFT   (0x00000007u)
#define RTC_ALARM2_HOURS_ALARM2_PM_NAM_AM   (0x0u)
#define RTC_ALARM2_HOURS_ALARM2_PM_NAM_PM   (0x1u)

/* ALARM2_DAYS_REG */
#define RTC_ALARM2_DAYS_ALARM2_DAY0   (0x0000000Fu)
#define RTC_ALARM2_DAYS_ALARM2_DAY0_SHIFT   (0x00000000u)

#define RTC_ALARM2_DAYS_ALARM2_DAY1   (0x00000030u)
#define RTC_ALARM2_DAYS_ALARM2_DAY1_SHIFT   (0x00000004u)

/* ALARM2_MONTHS_REG */
#define RTC_ALARM2_MONTHS_ALARM2_MONTH0   (0x0000000Fu)
#define RTC_ALARM2_MONTHS_ALARM2_MONTH0_SHIFT   (0x00000000u)

#define RTC_ALARM2_MONTHS_ALARM2_MONTH1   (0x00000010u)
#define RTC_ALARM2_MONTHS_ALARM2_MONTH1_SHIFT   (0x00000004u)

/* ALARM2_YEARS_REG */
#define RTC_ALARM2_YEARS_ALARM2_YEAR0   (0x0000000Fu)
#define RTC_ALARM2_YEARS_ALARM2_YEAR0_SHIFT   (0x00000000u)

#define RTC_ALARM2_YEARS_ALARM2_YEAR1   (0x000000F0u)
#define RTC_ALARM2_YEARS_ALARM2_YEAR1_SHIFT   (0x00000004u)

/* RTC_PMIC_REG */
#define RTC_PMIC_EXT_WAKEUP_DB_EN   (0x00000F00u)
#define RTC_PMIC_EXT_WAKEUP_DB_EN_SHIFT   (0x00000008u)
#define RTC_PMIC_EXT_WAKEUP_DB_EN_DISABLE   (0x0u)
#define RTC_PMIC_EXT_WAKEUP_DB_EN_ENABLE   (0x1u)

#define RTC_PMIC_EXT_WAKEUP_EN   (0x0000000Fu)
#define RTC_PMIC_EXT_WAKEUP_EN_SHIFT   (0x00000000u)
#define RTC_PMIC_EXT_WAKEUP_EN_EXT_WAKEUP_DISABLED   (0x0u)
#define RTC_PMIC_EXT_WAKEUP_EN_EXT_WALEUP_ENABLE   (0x1u)

#define RTC_PMIC_EXT_WAKEUP_POL   (0x000000F0u)
#define RTC_PMIC_EXT_WAKEUP_POL_SHIFT   (0x00000004u)
#define RTC_PMIC_EXT_WAKEUP_POL_ACTIVE_HIGH   (0x0u)
#define RTC_PMIC_EXT_WAKEUP_POL_ACTIVE_LOW   (0x1u)

#define RTC_PMIC_EXT_WAKEUP_STATUS   (0x0000F000u)
#define RTC_PMIC_EXT_WAKEUP_STATUS_SHIFT   (0x0000000Cu)
#define RTC_PMIC_EXT_WAKEUP_STATUS_NOT_OCCURED   (0x0u)
#define RTC_PMIC_EXT_WAKEUP_STATUS_OCCURRED   (0x1u)

#define RTC_PMIC_PWR_ENABLE_EN   (0x00010000u)
#define RTC_PMIC_PWR_ENABLE_EN_SHIFT   (0x00000010u)
#define RTC_PMIC_PWR_ENABLE_EN_DISABLE   (0x0u)
#define RTC_PMIC_PWR_ENABLE_EN_ENABLE   (0x1u)

#define RTC_PMIC_PWR_ENABLE_SM   (0x00060000u)
#define RTC_PMIC_PWR_ENABLE_SM_SHIFT   (0x00000011u)
#define RTC_PMIC_PWR_ENABLE_SM_EXTERNAL_EVENT_BASED_WAKEUP   (0x3u)
#define RTC_PMIC_PWR_ENABLE_SM_IDLE   (0x0u)
#define RTC_PMIC_PWR_ENABLE_SM_SHUTDOWN   (0x1u)
#define RTC_PMIC_PWR_ENABLE_SM_TIME_BASED_WAKEUP   (0x2u)

/* RTC_DEBOUNCE_REG */
#define RTC_DEBOUNCE_DEBOUNCE_REG   (0x000000FFu)
#define RTC_DEBOUNCE_DEBOUNCE_SHIFT   (0x00000000u)

/*-------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif
