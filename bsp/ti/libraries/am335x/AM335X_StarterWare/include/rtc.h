
/**
 * \file   rtc.h
 *
 * \brief  Header file for RTC driver module. This file contains the 
 *         prototypes of the APIs of RTC module and some related macros.
 */

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


#ifndef __RTC_H__
#define __RTC_H__

#include "hw_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Either of these macros are returned by the RTCEnableStatus() API.*/   

/* Used to disable RTC instance.*/
#define RTC_DISABLED              RTC_CTRL_RTCDISABLE

/* Used to indicate that RTC is enabled and functional.*/
#define RTC_ENABLED               RTC_CTRL_RUN_SHIFT
/*****************************************************************************/
/* Either of these macros are used as a parameter to RTCHourModeSet() API.*/

/* Used to enable 12 hour mode for hours.*/
#define RTC_12HOUR_MODE           (1 << RTC_CTRL_HOURMODE_SHIFT)

/* Used to enable 24 hour mode for hours.*/
#define RTC_24HOUR_MODE           (0 << RTC_CTRL_HOURMODE_SHIFT)
/*****************************************************************************/
/*
** One among the following  macros are passed as a parameter to 
** RTCIntTimerEnable() API.
*/

/* Used to enable interrupt generation on every second.*/
#define RTC_INT_EVERY_SECOND      RTC_INTERRUPTS_EVERY_SECOND

/* Used to enable interrupt generation on every minute.*/
#define RTC_INT_EVERY_MINUTE      RTC_INTERRUPTS_EVERY_MINUTE

/* Used to enable interrupt generation on every hour.*/
#define RTC_INT_EVERY_HOUR        RTC_INTERRUPTS_EVERY_HOUR

/* Used to enable interrupt generation on every day.*/
#define RTC_INT_EVERY_DAY         RTC_INTERRUPTS_EVERY_DAY

/****************************************************************************/
/* Either of these macros are returned by the RTCAlarmIntStatusGet() API. */

/* Used to indicate that a new alarm interrupt has been generated. */
#define RTC_NEW_ALARM_INTERRUPT           RTC_STATUS_ALARM

/* Used to indicate that no new alarm interrupt has been generated.*/
#define RTC_NO_NEW_ALARM_INTERRUPT        0x0
/****************************************************************************/
/* Either of these macros are returned by the RTCAlarm2IntStatusGet() API. */

/* Used to indicate that a new alarm interrupt has been generated. */
#define RTC_NEW_ALARM2_INTERRUPT          RTC_STATUS_ALARM2

/* Used to indicate that no new alarm interrupt has been generated.*/
#define RTC_NO_NEW_ALARM2_INTERRUPT       0x0
/****************************************************************************/

/*
** Any one of the following macros or a combination of the same are returned
** by the RTCEventUpdateGet() API.
*/
/*
** Used to indicate that DAY register was incremented in the latest 
** time update.
*/
#define RTC_DAY_EVENT                RTC_STATUS_DAYEVT

/*
** Used to indicate that HOUR register was incremented in the latest 
** time update.
*/
#define RTC_HOUR_EVENT               RTC_STATUS_HREVT

/*
** Used to indicate that MINUTE register was incremented in the latest
** time update.
*/
#define RTC_MINUTE_EVENT             RTC_STATUS_MINEVT

/*
** Used to indicate that SECOND register was incremented in the latest
** time update.
*/
#define RTC_SECOND_EVENT             RTC_STATUS_SECEVT
/****************************************************************************/
/* These macros are returned by the RTCBusyStatusGet() API. */

/* Used to indicate that RTC is busy in updating its registers.*/
#define RTC_BUSY                     RTC_STATUS_BUSY

/*
** Used to indicate that RTC is free and is currently not updating its 
** registers.
*/
#define RTC_FREE                     RTC_STATUS_BUSY_SHIFT
/****************************************************************************/
/* These macros are returned by the function RTCRunStatusGet() API. */

/* Used to indicate that RTC is in running state.*/
#define RTC_STATUS_RUNNING           RTC_STATUS_RUN

/* Used to indicate that RTC is in stopped state.*/
#define RTC_STATUS_STOPPED           RTC_STATUS_BUSY_SHIFT

/*****************************************************************************/
/*
** Either of following macros are passed as a parameter to
** RTCAlarmHourMeridiemSet() and RTCMeridiemSet() APIs. Similarly either of 
** these are returned by RTCAlarmHourMeridiemGet() and RTCMeridiemGet() APIs.
*/

/* Used to set the meridiem as post-meridiem(PM).*/
#define RTC_POST_MERIDIEM            (1 << RTC_HOUR_MERIDIEM_SHIFT)

/* Used to set the meridiem as ante-meridiem(AM).*/
#define RTC_ANTE_MERIDIEM            (0 << RTC_HOUR_MERIDIEM_SHIFT)
/*****************************************************************************/
/*
** One among the following  macros are passed as a parameter to 
** RTCDayOfTheWeekSet() API. Similarly one of these macros are returned by the
** RTCDayOfTheWeekGet() API.
*/

/* Used to indicate the days of the week. */
#define RTC_DOTW_SUN                 RTC_DOTW_DOTW_SUN
#define RTC_DOTW_MON                 RTC_DOTW_DOTW_MON
#define RTC_DOTW_TUE                 RTC_DOTW_DOTW_TUE
#define RTC_DOTW_WED                 RTC_DOTW_DOTW_WED
#define RTC_DOTW_THU                 RTC_DOTW_DOTW_THU
#define RTC_DOTW_FRI                 RTC_DOTW_DOTW_FRI
#define RTC_DOTW_SAT                 RTC_DOTW_DOTW_SAT

/*****************************************************************************/

/* Definitions specific to RTC IP in AM335X. */

/*
** RTC Idle Mode Options.
*/

#define RTC_IDLEMODE_FORCE_IDLE        (RTC_SYSCONFIG_IDLEMODE_FORCE_IDLE_MODE)
#define RTC_IDLEMODE_NO_IDLE           (RTC_SYSCONFIG_IDLEMODE_NO_IDLE_MODE)
#define RTC_IDLEMODE_SMART_IDLE        (RTC_SYSCONFIG_IDLEMODE_SMART_IDLE_MODE)
#define RTC_IDLEMODE_SMART_IDLE_WAKEUP (RTC_SYSCONFIG_IDLEMODE_SMART_IDLE_WAKEUP_CAPABLE_MODE)

/*
** Values are used to enable/disable Wakeup generation on Alarm event.
*/

#define RTC_ALARM_WAKEUP_ENABLE        (RTC_IRQ_WAKEEN_ALARM_WAKEEN_WAKEUP_ENABLED <<  \
                                        RTC_IRQ_WAKEEN_ALARM_WAKEEN_SHIFT)
#define RTC_ALARM_WAKEUP_DISABLE       (RTC_IRQ_WAKEEN_ALARM_WAKEEN_WAKEUP_DISABLED << \
                                        RTC_IRQ_WAKEEN_ALARM_WAKEEN_SHIFT)

/*
** Values are used to enable/disable Wakeup generation on Timer event.
*/

#define RTC_TIMER_WAKEUP_ENABLE        (RTC_IRQ_WAKEEN_TIMER_WAKEEN_WAKEUP_ENABLED << \
                                        RTC_IRQ_WAKEEN_TIMER_WAKEEN_SHIFT)
#define RTC_TIMER_WAKEUP_DISABLE       (RTC_IRQ_WAKEEN_TIMER_WAKEEN_WAKEUP_DISABLED << \
                                        RTC_IRQ_WAKEEN_TIMER_WAKEEN_SHIFT)

/* Values used to enable/disable Test Mode. */
#define RTC_FUNCTIONAL_MODE_ENABLE     (RTC_CTRL_TEST_MODE_FUNCTIONAL_MODE << \
                                        RTC_CTRL_TEST_MODE_SHIFT)
#define RTC_TEST_MODE_ENABLE           (RTC_CTRL_TEST_MODE_TEST_MODE << \
                                        RTC_CTRL_TEST_MODE_SHIFT)

/* Values used to select the clock source to the RTC. */
#define RTC_INTERNAL_CLK_SRC_SELECT    (RTC_OSC_32KCLK_SEL_SELECT_INTERNAL_CLK_SOURCE << \
                                        RTC_OSC_32KCLK_SEL_SHIFT)
#define RTC_EXTERNAL_CLK_SRC_SELECT    (RTC_OSC_32KCLK_SEL_SELECT_EXTERNAL_CLK_SOURCE << \
                                        RTC_OSC_32KCLK_SEL_SHIFT)

/* Values used to enable/disable the RTC to receive clock inputs from the selected source. */
#define RTC_32KCLK_ENABLE              (RTC_OSC_32KCLK_EN_ENABLE << \
                                        RTC_OSC_32KCLK_EN_SHIFT)
#define RTC_32KCLK_DISABLE             (RTC_OSC_32KCLK_EN_DISABLE << \
                                        RTC_OSC_32KCLK_EN_SHIFT)

/* Values used to enable/disable the Oscillator. */
#define RTC_32KOSC_ENABLE              (RTC_OSC_OSC32K_GZ_ENABLE << \
                                        RTC_OSC_OSC32K_GZ_SHIFT)
#define RTC_32KOSC_DISABLE             (RTC_OSC_OSC32K_GZ_DISABLE << \
                                        RTC_OSC_OSC32K_GZ_SHIFT)

/* Values used to select the mode of the Oscillator Feedback resistor. */
#define RTC_INTERNAL_FEEDBACK_RES_SEL  (RTC_OSC_RES_SELECT_INTERNAL << \
                                        RTC_OSC_RES_SELECT_SHIFT)
#define RTC_EXTERNAL_FEEDBACK_RES_SEL  (RTC_OSC_RES_SELECT_EXTERNAL << \
                                        RTC_OSC_RES_SELECT_SHIFT)

/* Values used to enable/disable PMIC Power. Passed as parameters to the API
   RTCConfigPmicPowerEnable().  */
#define RTC_PMIC_PWR_ENABLE            (RTC_PMIC_PWR_ENABLE_EN)
#define RTC_PMIC_PWR_DISABLE           (RTC_PMIC_PWR_ENABLE_EN_DISABLE)

/* Values used to configure polarity of external wake pin. Passed as
   parameters to the API RTCConfigPmicExtWakePolarity().  */
#define RTC_EXT_WAKEUP_POL_ACTIVE_HIGH (RTC_PMIC_EXT_WAKEUP_POL_ACTIVE_HIGH)
#define RTC_EXT_WAKEUP_POL_ACTIVE_LOW  (RTC_PMIC_EXT_WAKEUP_POL_ACTIVE_LOW)

/* Values used to configure polarity of external wake pin. Passed as
   parameters to the API RTCConfigPmicExtWakePolarity().  */
#define RTC_EXT_WAKEUP_ENABLE       (RTC_PMIC_EXT_WAKEUP_EN_EXT_WALEUP_ENABLE)
#define RTC_EXT_WAKEUP_DISABLE      (RTC_PMIC_EXT_WAKEUP_EN_EXT_WAKEUP_DISABLED)

/* Values used to configure polarity of external wake pin. Passed as
   parameters to the API RTCConfigPmicExtWakePolarity().  */
#define RTC_EXT_WAKEUP_DB_ENABLE       (RTC_PMIC_EXT_WAKEUP_DB_EN_ENABLE)
#define RTC_EXT_WAKEUP_DB_DISABLE      (RTC_PMIC_EXT_WAKEUP_DB_EN_DISABLE)

/*****************************************************************************/

/******************************************************************************
**            DRIVER API FUNCTIONS PROTOTYPES                              
******************************************************************************/
/******************************************************************************
**         APIs common to the RTC IPs of both AM1808 and AM335x.
******************************************************************************/
extern void RTCRun(unsigned int baseAddr);
extern void RTCStop(unsigned int baseAddr);
extern void RTCMinRoundingEnable(unsigned int baseAddr);
extern void RTCMinRoundingDisable(unsigned int baseAddr);
extern void RTCAutoCompEnable(unsigned int baseAddr);
extern void RTCAutoCompDisable(unsigned int baseAddr);
extern void RTCHourModeSet(unsigned int baseAddr, unsigned int hourType);
extern unsigned int RTCHourModeGet(unsigned int baseAddr);
extern void RTCSet32CounterEnable(unsigned int baseAddr);
extern void RTCSet32CounterDisable(unsigned int baseAddr);

extern unsigned int RTCEnableStatus(unsigned int baseAddr);
extern void RTCDisable(unsigned int baseAddr);
extern void RTCEnable(unsigned int baseAddr);
extern void RTCSplitPwrEnable(unsigned int baseAddr);
extern void RTCSplitPwrDisable(unsigned int baseAddr);
extern void RTCWriteProtectEnable(unsigned int baseAddr);
extern void RTCWriteProtectDisable(unsigned int baseAddr);
extern void RTCIntAlarmEnable(unsigned int baseAddr);
extern void RTCIntAlarmDisable(unsigned int baseAddr);
extern void RTCIntTimerEnable(unsigned int baseAddr, unsigned int timerPeriod);

extern void RTCIntTimerDisable(unsigned int baseAddr);
extern unsigned int RTCBusyStatusGet(unsigned int baseAddr);
extern unsigned int RTCRunStatusGet(unsigned int baseAddr);
extern unsigned int RTCAlarmIntStatusGet(unsigned int baseAddr);
extern void RTCAlarmIntStatusClear(unsigned int baseAddr);
extern unsigned int RTCEventUpdateGet(unsigned int baseAddr);
extern void RTCSecondSet(unsigned int baseAddr, unsigned int secValue);
extern unsigned int RTCSecondGet(unsigned int baseAddr);
extern void RTCMinuteSet(unsigned int baseAddr, unsigned int minValue);
extern unsigned int RTCMinuteGet(unsigned int baseAddr);

extern void RTCHourSet(unsigned int baseAddr, unsigned int hourValue);
extern unsigned int RTCHourGet(unsigned int baseAddr);
extern void RTCMeridiemSet(unsigned int baseAddr, unsigned int meridiemType);
extern unsigned int RTCMeridiemGet(unsigned int baseAddr);
extern void RTCDayOfMonthSet(unsigned int baseAddr, unsigned int dayValue);
extern unsigned int RTCDayOfMonthGet(unsigned int baseAddr);
extern void RTCMonthSet(unsigned int baseAddr, unsigned int monthValue);
extern unsigned int RTCMonthGet(unsigned int baseAddr);
extern void RTCYearSet(unsigned int baseAddr, unsigned int yearValue);
extern unsigned int RTCYearGet(unsigned int baseAddr);

extern void RTCDayOfTheWeekSet(unsigned int baseAddr, unsigned int dotwValue);
extern unsigned int RTCDayOfTheWeekGet(unsigned int baseAddr);
extern void RTCTimeSet(unsigned int baseAddr, unsigned int time);
extern unsigned int RTCTimeGet(unsigned int baseAddr);
extern void RTCCalendarSet(unsigned int baseAddr, unsigned int calendar);
extern unsigned int RTCCalendarGet(unsigned int baseAddr);
extern void RTCAlarmSecondSet(unsigned int baseAddr, unsigned int alarmSecValue);
extern unsigned int RTCAlarmSecondGet(unsigned int baseAddr);
extern void RTCAlarmMinuteSet(unsigned int baseAddr, unsigned int alrmMinValue);
extern unsigned int RTCAlarmMinuteGet(unsigned int baseAddr);

extern void RTCAlarmHourSet(unsigned int baseAddr, unsigned int alrmHourVal);
extern unsigned int RTCAlarmHourGet(unsigned int baseAddr);
extern void RTCAlarmHourMeridiemSet(unsigned int baseAddr, unsigned int meridiemType);
extern unsigned int RTCAlarmHourMeridiemGet(unsigned int baseAddr);
extern void RTCAlarmTimeSet(unsigned int baseAddr, unsigned int alarmTime);
extern unsigned int RTCAlarmTimeGet(unsigned int baseAddr);
extern void RTCAlarmDayOfMonthSet(unsigned int baseAddr, unsigned int alarmDayValue);
extern unsigned int RTCAlarmDayOfMonthGet(unsigned int baseAddr);
extern void RTCAlarmMonthSet(unsigned int baseAddr, unsigned int alrmMnthVal);
extern unsigned int RTCAlarmMonthGet(unsigned int baseAddr);

extern void RTCAlarmYearSet(unsigned int baseAddr, unsigned int alrmYrVal);
extern unsigned int RTCAlarmYearGet(unsigned int baseAddr);
extern void RTCAlarmCalendarSet(unsigned int baseAddr, unsigned int calVal);
extern unsigned int RTCAlarmCalendarGet(unsigned int baseAddr);
extern void RTCCompensationSet(unsigned int baseAddr, unsigned int compVal);
extern unsigned int RTCCompensationGet(unsigned int baseAddr);
extern void RTCScratchPadSet(unsigned int baseAddr, unsigned int regNumber,
                      unsigned int scratchValue);
extern unsigned int RTCScratchPadGet(unsigned int baseAddr, unsigned int regNumber);

/*****************************************************************************
**  APIs specific to RTC IP of AM1808 and not applicable for that in AM335x.
*****************************************************************************/
extern void RTCSoftwareReset(unsigned int baseAddr);

/*****************************************************************************
**  APIs specific to RTC IP of AM335x and not applicable for that in AM1808.
*****************************************************************************/
extern void RTCIdleModeConfigure(unsigned int baseAdd, unsigned int modeFlag);
extern void RTCWakeUpAlarmEventControl(unsigned int baseAdd, unsigned int controlFlag);
extern void RTCWakeUpTimerEventControl(unsigned int baseAdd, unsigned int controlFlag);
extern void RTCTestModeControl(unsigned int baseAdd, unsigned int controlFlag);
extern void RTC32KClkSourceSelect(unsigned int baseAdd, unsigned int clkSrcFlag);
extern void RTC32KClkClockControl(unsigned int baseAdd, unsigned int controlFlag);
extern void RTCOscillatorStateControl(unsigned int baseAdd, unsigned int controlFlag);
extern void RTCFeedbackResistanceSelect(unsigned int baseAdd, unsigned int selectFlag);
extern void RTCConfigPmicPowerEnable(unsigned int baseAdd, unsigned int selectFlag);
extern void RTCConfigPmicExtWakePolarity(unsigned int baseAdd,
                                         unsigned int extInput,
                                         unsigned int selectFlag);
extern void RTCConfigPmicExtWake(unsigned int baseAdd, unsigned int extInput,
                                 unsigned int selectFlag);
extern void RTCConfigPmicExtWakeDebounce(unsigned int baseAdd,
                                         unsigned int extInput,
                                         unsigned int selectFlag);
extern void RTCPmicExtWakeStatusClear(unsigned int baseAdd,
                                      unsigned int extInput);
extern void RTCIntAlarm2Enable(unsigned int baseAddr);
extern void RTCAlarm2IntStatusClear(unsigned int baseAddr);
extern void RTCAlarm2TimeSet(unsigned int baseAddr, unsigned int alarmTime);
extern void RTCAlarm2CalendarSet(unsigned int baseAddr, unsigned int calVal);
extern unsigned int RTCAlarm2IntStatusGet(unsigned int baseAdd);

/*****************************************************************************
**              Prototypes of Miscellaneous and related functions
*****************************************************************************/

/* Function which helps determine the SoC(Platform) in use. */
extern unsigned int RtcVersionGet(void);


#ifdef __cplusplus
}
#endif
#endif
