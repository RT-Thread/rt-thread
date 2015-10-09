/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_IRTC_HAL_H__)
#define __FSL_IRTC_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*!
 * @addtogroup irtc_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IRTC_BASE_YEAR    (2112U)
#define RTC_WRITE_ENABLE(base, value) (*(__IO uint8_t*)(&RTC_STATUS_REG(base)) = (value))

/*! @brief Error codes for the IRTC driver.*/
typedef enum _irtc_status
{
    kStatus_IRTC_Success = 0x00U,
    kStatus_IRTC_Fail    = 0x01U
} irtc_status_t;

/*! @brief IRTC filter clock source options. */
typedef enum _irtc_filter_clock_source {
    kIRTC32K = 0x0,  /*!< Use 32 kHz clock source for the tamper filter.*/
    kIRTC512 = 0x1,  /*!< Use 512 Hz clock source for the tamper filter.*/
    kIRTC128 = 0x2,  /*!< Use 128 Hz clock source for the tamper filter.*/
    kIRTC64  = 0x3,  /*!< Use 64 Hz clock source for the tamper filter.*/
    kIRTC16  = 0x4,  /*!< Use 16 Hz clock source for the tamper filter.*/
    kIRTC8   = 0x5,  /*!< Use 8 Hz clock source for the tamper filter.*/
    kIRTC4   = 0x6,  /*!< Use 4 Hz clock source for the tamper filter.*/
    kIRTC2   = 0x7   /*!< Use 2 Hz clock source for the tamper filter.*/
} irtc_filter_clock_source_t;

/*! @brief IRTC Tamper pins. */
typedef enum _irtc_tamper_pins {
    kIRTCTamper0   = 0x0, /*!< External Tamper 0 */
    kIRTCTamper1   = 0x1, /*!< External Tamper 1 */
    kIRTCTamper2   = 0x2, /*!< External Tamper 2 */
    kIRTCTamper3   = 0x3  /*!< Internal tamper, does not have filter configuration */
} irtc_tamper_pins_t;

/*! @brief IRTC clock output selection. */
typedef enum _irtc_clock_output {
    kIRTCNoOutputClk   = 0x0, /*!< No output clock */
    kIRTCFine1hzClk    = 0x1, /*!< Fine 1 Hz clock */
    kIRTC32khzClk      = 0x2, /*!< 32.768 kHz clock */
    kIRTCCoarse1hzClck = 0x3  /*!< Coarse 1Hz clock */
} irtc_clock_output_t;

/*! @brief IRTC alarm match selection. */
typedef enum _irtc_alarm_match {
    kIRTCSecMinHour           = 0x0, /*!< Generate alarm when sec/min/hour are matched. @internal gui name="Generate alarm when sec/min/hour are matched" */
    kIRTCSecMinHourDay        = 0x1, /*!< Generate alarm when sec/min/hour/day are matched. @internal gui name="Generate alarm when sec/min/hour/day are matched" */
    kIRTCSecMinHourDayMon     = 0x2, /*!< Generate alarm when sec/min/hour/day/month are matched. @internal gui name="Generate alarm when sec/min/hour/day/month are matched" */
    kIRTCSecMinHourDayMonYear = 0x3  /*!< Generate alarm when sec/min/hour/day/month/year are matched. @internal gui name="Generate alarm when sec/min/hour/day/month/year are matched" */
} irtc_alarm_match_t;

/*! @brief IRTC status flags. */
typedef enum _irtc_status_flag {
    kIRTCInvalidate  = RTC_STATUS_INVAL_BIT_SHIFT,
    kIRTCReadOnly    = RTC_STATUS_WRITE_PROT_EN_SHIFT,
    kIRTCLowVoltage  = RTC_STATUS_CPU_LOW_VOLT_SHIFT,
    kIRTCResetSrc    = RTC_STATUS_RST_SRC_SHIFT,
    kIRTCCmpInterval = RTC_STATUS_CMP_INT_SHIFT,
    kIRTCBusErr      = RTC_STATUS_BUS_ERR_SHIFT,
    kIRTCCmpDone     = RTC_STATUS_CMP_DONE_SHIFT
} irtc_status_flag_t;

/*! @brief IRTC interrupt status flags. */
typedef enum _irtc_int_status_flag {
    kIRTCTamperIntFlag = RTC_ISR_TAMPER_IS_SHIFT,
    kIRTCAlarmIntFlag  = RTC_ISR_ALM_IS_SHIFT,
    kIRTCDayIntFlag    = RTC_ISR_DAY_IS_SHIFT,
    kIRTCHourIntFlag   = RTC_ISR_HOUR_IS_SHIFT,
    kIRTCMinIntFlag    = RTC_ISR_MIN_IS_SHIFT,
    kIRTC1hzIntFlag    = RTC_ISR_IS_1HZ_SHIFT,
    kIRTC2hzIntFlag    = RTC_ISR_IS_2HZ_SHIFT,
    kIRTC4hzIntFlag    = RTC_ISR_IS_4HZ_SHIFT,
    kIRTC8hzIntFlag    = RTC_ISR_IS_8HZ_SHIFT,
    kIRTC16hzIntFlag   = RTC_ISR_IS_16HZ_SHIFT,
    kIRTC32hzIntFlag   = RTC_ISR_IS_32HZ_SHIFT,
    kIRTC64hzIntFlag   = RTC_ISR_IS_64HZ_SHIFT,
    kIRTC128hzIntFlag  = RTC_ISR_IS_128HZ_SHIFT,
    kIRTC256hzIntFlag  = RTC_ISR_IS_256HZ_SHIFT,
    kIRTC512hzIntFlag  = RTC_ISR_IS_512HZ_SHIFT
} irtc_int_status_flag_t;

/*! @brief IRTC interrupts. */
typedef enum _irtc_int {
    kIRTCTamperInt = RTC_IER_TAMPER_IE_SHIFT,
    kIRTCAlarmInt  = RTC_IER_ALM_IE_SHIFT,
    kIRTCDayInt    = RTC_IER_DAY_IE_SHIFT,
    kIRTCHourInt   = RTC_IER_HOUR_IE_SHIFT,
    kIRTCMinInt    = RTC_IER_MIN_IE_SHIFT,
    kIRTC1hzInt    = RTC_IER_IE_1HZ_SHIFT,
    kIRTC2hzInt    = RTC_IER_IE_2HZ_SHIFT,
    kIRTC4hzInt    = RTC_IER_IE_4HZ_SHIFT,
    kIRTC8hzInt    = RTC_IER_IE_8HZ_SHIFT,
    kIRTC16hzInt   = RTC_IER_IE_16HZ_SHIFT,
    kIRTC32hzInt   = RTC_IER_IE_32HZ_SHIFT,
    kIRTC64hzInt   = RTC_IER_IE_64HZ_SHIFT,
    kIRTC128hzInt  = RTC_IER_IE_128HZ_SHIFT,
    kIRTC256hzInt  = RTC_IER_IE_256HZ_SHIFT,
    kIRTC512hzInt  = RTC_IER_IE_512HZ_SHIFT
} irtc_int_t;

/*!
 * @brief Structure is used to hold the time in a simple "date" format.
 * @internal gui name="Date and Time configuration" id="IrtcDateTimeCfg"
 */
typedef struct IrtcDatetime
{
   uint16_t year;    /*!< Range from 1984 to 2239. @internal gui name="Year" id="IrtcYear" range="1984..2239" default default="2015"*/
   uint16_t month;   /*!< Range from 1 to 12. @internal gui name="Month" id="IrtcMonth" range="1..12" default="1"*/
   uint16_t day;     /*!< Range from 1 to 31 (depending on month). @internal gui name="Day" id="IrtcDay" range="1..31" default="1"*/
   uint16_t weekDay; /*!< Range from 0(Sunday) to 6(Saturday). @internal gui name="Weekday" id="IrtcWeekday" range="0..6" default="0"*/
   uint16_t hour;    /*!< Range from 0 to 23. @internal gui name="Hour" id="IrtcHour" range="0..23" default="0"*/
   uint16_t minute;  /*!< Range from 0 to 59. @internal gui name="Minute" id="IrtcMinute" range="0..59" default="0"*/
   uint16_t second;   /*!< Range from 0 to 59. @internal gui name="Second" id="IrtcSecond" range="0..59" default="0"*/
} irtc_datetime_t;

/*!
 * @brief Structure is used to hold the daylight saving time.
 * @internal gui name="Daylight time configuration" id="IrtcDaylightTimeCfg"
 */
typedef struct IrtcDaylightTime
{
   uint16_t startMonth; /*!< Range from 1 to 12. @internal gui name="Start month" id="IrtcStartMonth" range="1..12" default="1"*/
   uint16_t endMonth;   /*!< Range from 1 to 12. @internal gui name="End month" id="IrtcEndMonth" range="1..12" default="1"*/
   uint16_t startDay;   /*!< Range from 1 to 31 (depending on month). @internal gui name="Start day" id="IrtcStartDay" range="1..31" default="1"*/
   uint16_t endDay;     /*!< Range from 1 to 31 (depending on month). @internal gui name="End day" id="IrtcEndDay" range="1..31" default="1"*/
   uint16_t startHour;  /*!< Range from 0 to 23. @internal gui name="Start Hour" id="IrtcStartHour" range="0..23" default="0"*/
   uint16_t endHour;    /*!< Range from 0 to 23. @internal gui name="End Hour" id="IrtcEndHour" range="0..23" default="0"*/
} irtc_daylight_time_t;

/*! @brief Structure is used to define the parameters to configure a RTC tamper event. */
typedef struct IrtcTamperConfig
{
#if FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION
    bool activePassive; /*!< true: configure tamper as active; false: passive tamper */
    bool direction;     /*!< true: configure tamper direction as output; false: configure as input;
                             this is only used if a tamper pin is defined as active */
#endif
    bool pinPolarity;   /*!< true: tamper has active low polarity; false: active high polarity */
    irtc_filter_clock_source_t filterClk;  /*!< Clock source for the tamper filter */
    uint8_t filterDuration;  /*!< Tamper filter duration.*/
} irtc_tamper_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief  Resets the IRTC module.
 *
 * This function initiates a soft-reset of the IRTC module to reset
 * the IRTC registers.
 *
 * @param  base The IRTC base address pointer.
 */
void IRTC_HAL_Init(RTC_Type *base);

/*!
 * @brief Locks or unlocks IRTC registers for write access.
 *
 * @note When the registers are unlocked, they remain in unlocked state for
 * 2 seconds, after which they are locked automatically. After
 * power-on-reset, the registers come out unlocked and they are locked
 * automatically 15 seconds after power on.
 *
 * @param  base The IRTC base address pointer.
 * @param  lock Lock(true) or unlock(false) IRTC registers.
 */
void IRTC_HAL_SetLockRegisterCmd(RTC_Type *base, bool lock);

/*@}*/

/*!
 * @name Date and Time Setting
 *
 * @note All Date and Time settings APIs except the IRTC_HAL_SetDatetime and the IRTC_HAL_GetDatetime settings,
 * should first determine the state of the INVAL bit in the STATUS(bit 0) to
 * determine that the counters are stable before their value can be read or
 * changed (this be done by calling IRTC_HAL_GetStatusFlag(base, kIRTCInvalidate)).
 * The assertion of INVAL bit ensures that no operation is done at the boundary
 * of a second when counters change value.
 *
 * @{
 */

/*!
 * @brief Sets the IRTC year and month.
 *
 * @param base The IRTC base address pointer
 * @param year Year number from 1984 to 2239.
 * @param month Month number from 1 to 12.
 */
void IRTC_HAL_SetYearMonth(RTC_Type * base, uint16_t year, uint16_t month);

/*!
 * @brief Gets the IRTC current year and month.
 *
 * @param base The IRTC base address pointer
 * @param year Current year number from 1984 to 2239.
 * @param month Current month number from 1 to 12.
 */
void IRTC_HAL_GetYearMonth(RTC_Type * base, uint16_t * year, uint16_t * month);

/*!
 * @brief Sets the IRTC day and day of week.
 *
 * @param base The IRTC base address pointer
 * @param day Day number from 1 to 31.
 * @param weekDay Day of week number from 0(Sunday) to 6(Saturday).
 */
static inline void IRTC_HAL_SetDayWeek(RTC_Type * base, uint16_t day, uint16_t weekDay)
{
    RTC_WR_DAYS(base, RTC_DAYS_DOW(weekDay) | RTC_DAYS_DAY_CNT(day));
}

/*!
 * @brief Gets the IRTC current day and day of week.
 *
 * @param base The IRTC base address pointer
 * @param day Current day number from 1 to 31.
 * @param weekDay Current day of week number from 0(Sunday) to 6(Saturday).
 */
void IRTC_HAL_GetDayWeek(RTC_Type * base, uint16_t * day, uint16_t * weekDay);

/*!
 * @brief Sets the IRTC hours and minutes.
 *
 * @param base The IRTC base address pointer
 * @param hour Hour number from 0 to 23.
 * @param min Min number from 0 to 59.
 */
static inline void IRTC_HAL_SetHourMin(RTC_Type * base, uint16_t hour, uint16_t min)
{
    RTC_WR_HOURMIN(base, RTC_HOURMIN_HOUR_CNT(hour) | RTC_HOURMIN_MIN_CNT(min));
}

/*!
 * @brief Gets the IRTC current hours and minutes.
 *
 * @param base The IRTC base address pointer
 * @param hour Current hour number from 0 to 23.
 * @param min Current minute number from 0 to 59.
 */
void IRTC_HAL_GetHourMin(RTC_Type * base, uint16_t * hour, uint16_t * min);

/*!
 * @brief Sets the IRTC second counter.
 *
 * @param base The IRTC base address pointer
 * @param sec Second number from 0 to 59.
 */
static inline void IRTC_HAL_SetSec(RTC_Type * base, uint16_t sec)
{
    RTC_WR_SECONDS(base, sec);
}

/*!
 * @brief Gets the IRTC current second counter.
 *
 * @param base The IRTC base address pointer
 * @param sec Current second number from 0 to 59.
 */
static inline void IRTC_HAL_GetSec(RTC_Type * base, uint16_t * sec)
{
    *sec = RTC_RD_SECONDS(base);
}

/*!
 * @brief Sets the IRTC date and time according to the given time structure.
 *
 * @param  base The IRTC base address pointer
 * @param  datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_HAL_SetDatetime(RTC_Type *base, const irtc_datetime_t * datetime);

/*!
 * @brief  Gets the IRTC time and stores it in the given time structure.
 *
 * @param  base The IRTC base address pointer
 * @param  datetime Pointer to a structure where the date and time details are
 *         stored.
 */
void IRTC_HAL_GetDatetime(RTC_Type *base, irtc_datetime_t * datetime);

/*@}*/

/*!
 * @name Alarm Time Setting
 * @{
 */

/*!
 * @brief Sets the alarm match type.
 *
 * @param base The IRTC base address pointer
 * @param alarmType Alarm match selections that when an alarm happens.
 */
static inline void IRTC_HAL_SetAlarmMatchMode(RTC_Type * base, irtc_alarm_match_t alarmType)
{
    RTC_BWR_CTRL_ALM_MATCH(base, alarmType);
}

/*!
 * @brief  Sets the IRTC alarm time and enables the alarm interrupt.
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * @param  base The IRTC base address pointer.
 * @param  datetime Pointer to structure where the alarm date and time
 *         details will be stored at.
 */
void IRTC_HAL_SetAlarm(RTC_Type *base, const irtc_datetime_t * datetime);

/*!
 * @brief  Reads the value of the time alarm.
 *
 * @param  base The IRTC base address pointer
 * @param  datetime Pointer to a variable where the alarm date and time
 *         details are stored.
 */
void IRTC_HAL_GetAlarm(RTC_Type *base, irtc_datetime_t * datetime);

/*@}*/

/*!
 * @name Daylight Saving Time Setting
 * @{
 */

/*!
 * @brief Sets IRTC daylight savings start month and end month.
 *
 * @param base The IRTC base address pointer
 * @param startMonth Daylight saving start month number from 1 to 12.
 * @param endMonth Daylight saving end month number from 1 to 12.
 */
static inline void IRTC_HAL_SetDaylightMonth(RTC_Type * base, uint16_t startMonth, uint16_t endMonth)
{
    RTC_WR_DST_MONTH(base, RTC_DST_MONTH_DST_START_MONTH(startMonth) |
                           RTC_DST_MONTH_DST_END_MONTH(endMonth));
}

/*!
 * @brief Gets the IRTC current daylight savings start and end month.
 *
 * @param base The IRTC base address pointer
 * @param startMonth Current daylight saving start month number from 1 to 12.
 * @param endMonth Current daylight saving end month number from 1 to 12.
 */
void IRTC_HAL_GetDaylightMonth(RTC_Type * base, uint16_t * startMonth, uint16_t * endMonth);

/*!
 * @brief Sets the IRTC daylight savings start and end day.
 *
 * @param base The IRTC base address pointer
 * @param startDay Daylight saving day start value number from 1 to 31.
 * @param endDay Daylight saving day end value number from 1 to 31.
 */
static inline void IRTC_HAL_SetDaylightDay(RTC_Type * base, uint16_t startDay, uint16_t endDay)
{
    RTC_WR_DST_DAY(base, RTC_DST_DAY_DST_START_DAY(startDay) |
                         RTC_DST_DAY_DST_END_DAY(endDay));
}

/*!
 * @brief Gets the IRTC current daylight savings start and end day.
 *
 * @param base The IRTC base address pointer
 * @param startDay Current daylight saving day start value number from 1 to 31.
 * @param endDay Current daylight saving day end value number from 1 to 31.
 */
void IRTC_HAL_GetDaylightDay(RTC_Type * base, uint16_t * startDay, uint16_t * endDay);

/*!
 * @brief Sets the IRTC current daylight savings start and end hour.
 *
 * @param base The IRTC base address pointer
 * @param startHour Daylight saving hour start value.
 * @param endHour Daylight saving hour end value.
 */
static inline void IRTC_HAL_SetDaylightHour(RTC_Type * base, uint16_t startHour, uint16_t endHour)
{
    RTC_WR_DST_HOUR(base, RTC_DST_HOUR_DST_START_HOUR(startHour) |
                         RTC_DST_HOUR_DST_END_HOUR(endHour));
}

/*!
 * @brief Gets the IRTC current daylight savings start and end hour.
 *
 * @param base The IRTC base address pointer
 * @param startHour Current daylight saving hour start value.
 * @param endHour Current daylight saving hour end value.
 */
void IRTC_HAL_GetDaylightHour(RTC_Type * base, uint16_t * startHour, uint16_t * endHour);

/*!
 * @brief Sets the IRTC daylight savings date and time.
 *
 * @param  base The IRTC base address pointer
 * @param  datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_HAL_SetDaylightTime(RTC_Type *base, const irtc_daylight_time_t * datetime);

/*!
 * @brief  Gets the IRTC daylight savings time and stores it in the given time structure.
 *
 * @param  base The IRTC base address pointer
 * @param  datetime Pointer to a structure where the date and time details are
 *         stored.
 */
void IRTC_HAL_GetDaylightTime(RTC_Type *base, irtc_daylight_time_t * datetime);

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the IRTC status flag state.
 *
 * @param base The IRTC peripheral base pointer.
 * @param statusFlag The status flag, defined in type irtc_status_flag_t.
 * @return State of the status flag: asserted (true) or not-asserted (false).
 *         - true: related status flag is being set.
 *         - false: related status flag is not set.
 */
static inline bool IRTC_HAL_GetStatusFlag(RTC_Type *base, irtc_status_flag_t statusFlag)
{
    return (bool)((RTC_RD_STATUS(base) >> statusFlag) & 0x1U);
}

/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables or disables the related IRTC interrupt.
 *
 * @param base The IRTC peripheral base pointer.
 * @param interrupt The interrupt name, defined in type irtc_int_t.
 * @param enable Enable (true) or disable (false) related interrupt.
 */
static inline void IRTC_HAL_SetIntCmd(RTC_Type * base, irtc_int_t interrupt, bool enable)
{
    uint16_t temp = 1U << (uint16_t)interrupt;
    enable ? RTC_SET_IER(base, temp) : RTC_CLR_IER(base, temp);
}

/*!
 * @brief Indicates whether the IRTC interrupt is enabled or not.
 *
 * @param base The IRTC peripheral base pointer.
 * @param interrupt The interrupt name, defined in type irtc_int_t.
 * @return State of the interrupt: asserted (true) or not-asserted (false).
 *         - true: related interrupt is being enabled.
 *         - false: related interrupt is not enabled.
 */
static inline bool IRTC_HAL_GetIntCmd(RTC_Type * base, irtc_int_t interrupt)
{
    return (bool)((RTC_RD_IER(base) >> interrupt) & 0x1U);
}

/*!
 * @brief Gets the IRTC interrupt status flag state.
 *
 * @param base The IRTC peripheral base pointer.
 * @param statusFlag The status flag, defined in type irtc_int_status_flag_t.
 * @return State of the status flag: asserted (true) or not-asserted (false).
 *         - true: related status flag is being set.
 *         - false: related status flag is not set.
 */
static inline bool IRTC_HAL_GetIntStatusFlag(RTC_Type * base, irtc_int_status_flag_t statusFlag)
{
    return (bool)((RTC_RD_ISR(base) >> statusFlag) & 0x1U);
}

/*!
 * @brief Clears the IRTC interrupt status flag.
 *
 * Tamper interrupt status flag is cleared when the TAMPER_SCR[TMPR_STS] is cleared.
 *
 * @param base The IRTC peripheral base pointer.
 * @param statusFlag The status flag, defined in type irtc_int_status_flag_t.
 */
static inline void IRTC_HAL_ClearIntStatusFlag(RTC_Type * base, irtc_int_status_flag_t statusFlag)
{
    IRTC_HAL_SetLockRegisterCmd(base, false);
    RTC_WR_ISR(base, 1U << (uint16_t)statusFlag);
    IRTC_HAL_SetLockRegisterCmd(base, true);
}

/*@}*/

/*!
 * @name IRTC Time Compensation
 * @{
 */

/*!
 * @brief  Enables the coarse compensation and sets the value to the IRTC compensation register.
 *
 * @param  base The IRTC base address pointer
 * @param  compVal Compensation value is a 2's complement value.
 * @param  compInterval Compensation interval.
 */
void IRTC_HAL_SetCoarseCompensation(RTC_Type *base, uint8_t compVal, uint8_t compInterval);

/*!
 * @brief  Enables the fine compensation and sets the value to the IRTC compensation register.
 *
 * @param  base The IRTC base address pointer
 * @param  integralVal Compensation integral value is a twos complement value of the integer part.
 * @param  fracVal Compensation fraction value expressed as number of clock cycles of a fixed
 *         4.194304Mhz clock that have to be added.
 * @param  accumulateFrac Flag indicating if we want to add to previous fractional part;
 *         true: accumulate fractional part, false: start afresh and overwrite current value
 */
void IRTC_HAL_SetFineCompensation(RTC_Type *base, uint8_t integralVal, uint8_t fracVal,
                                           bool accumulateFrac);

/*@}*/

/*!
 * @name IRTC Control
 * @{
 */

/*!
 * @brief  Selects which clock to output from the SoC for use outside the RTC.
 *
 * @param  base The IRTC base address pointer.
 * @param  clock OUtput clock selection from list of irtc_clock_output_t.
 */
static inline void IRTC_HAL_SetClockOutMode(RTC_Type *base, irtc_clock_output_t clock)
{
    RTC_BWR_CTRL_CLKOUT(base, clock);
}

/*!
 * @brief  Performs a software reset on the IRTC module.
 *
 * This clears the contents of alarm, interrupt (status and enable except tamper
 * interrupt enable bit) registers, STATUS[CMP_DONE], and STATUS[BUS_ERR] and
 * has no effect on DST, calendaring, standby time, and tamper detect registers.
 *
 * @param  base The IRTC base address pointer
 */
static inline void IRTC_HAL_SoftwareReset(RTC_Type *base)
{
    RTC_BWR_CTRL_SWR(base, 0x1U);
}

/*@}*/

/*!
 * @name IRTC Tamper
 * @{
 */

/*!
 * @brief  This function allows configuring the four tamper inputs.
 *
 * The function configures the filter properties for the three external tampers i.e., 0, 1, and 2.
 * It also sets up active/passive and direction of the tamper bits, which are not available
 * on all platforms.
 * NOTE: This function programs the tamper filter parameters. The user must
 * gate the 32 K clock to the RTC before calling this function. It is assumed that the time and date
 * are set after this and the tamper parameters do not require to be changed again later.
 *
 * @param  base The IRTC base address pointer
 * @param  tamperNum The IRTC tamper input to configure
 * @param  tamperConfig The IRTC tamper properties
 */
void IRTC_HAL_ConfigTamperParams(RTC_Type *base, irtc_tamper_pins_t tamperNum,
                                           irtc_tamper_config_t * tamperConfig);

/*!
 * @brief Enables the tamper feature.
 *
 * The function should be called after all required tamper features have been configured
 * by calling the IRTC_HAL_ConfigTamperParams functions.
 *
 * @param  base The IRTC base address pointer
 */
static inline void IRTC_HAL_EnableTamper(RTC_Type *base)
{
    RTC_BWR_CTRL2_TAMP_CFG_OVER(base, 0x1U);
}

/*!
 * @brief Disables the tamper feature.
 *
 * @param  base The IRTC base address pointer
 */
static inline void IRTC_HAL_DisableTamper(RTC_Type *base)
{
    RTC_BWR_CTRL2_TAMP_CFG_OVER(base, 0x0U);
}

#if FSL_FEATURE_RTC_HAS_TAMPER_QUEUE

/*!
 * @brief  This function reads the tamper timestamp and returns the associated tamper pin.
 *
 * The tamper timestamp has month, day, hour, minutes, and seconds. Ignore the year field as this
 * information is not available in the tamper queue. The user should look at the RTC_YEARMON register
 * for this because the expectation is that the queue is read at least once a year.
 * Return the tamper pin number associated with the timestamp.
 *
 * @param  base The IRTC base address pointer
 * @param  tamperTimestamp The tamper timestamp
 *
 * @return The tamper pin number
 */
uint8_t IRTC_HAL_ReadTamperQueue(RTC_Type *base, irtc_datetime_t * tamperTimestamp);

#endif

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

#endif /* __FSL_IRTC_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

