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

#include "fsl_rtc_hal.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SECONDS_IN_A_DAY     (86400U)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of month length (in days) for the Un-leap-year*/
static const uint8_t ULY[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

/* Table of month length (in days) for the Leap-year*/
static const uint8_t LY[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

/* Number of days from begin of the non Leap-year*/
static const uint16_t MONTH_DAYS[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U,
    212U, 243U, 273U, 304U, 334U};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_ConvertSecsToDatetime
 * Description   : converts time data from seconds to a datetime structure.
 * This function will convert time data from seconds to a datetime structure.
 *
 *END**************************************************************************/
void RTC_HAL_ConvertSecsToDatetime(const uint32_t * seconds, rtc_datetime_t * datetime)
{
    uint32_t x;
    uint32_t Seconds, Days, Days_in_year;
    const uint8_t *Days_in_month;

    /* Start from 1970-01-01*/
    Seconds = *seconds;
    /* days, we add 1 for the current day which is represented in the hours and seconds field */
    Days = Seconds / SECONDS_IN_A_DAY + 1;
    /* seconds left*/
    Seconds = Seconds % SECONDS_IN_A_DAY;
    /* hours*/
    datetime->hour = Seconds / SECONDS_IN_A_HOUR;
    /* seconds left*/
    Seconds = Seconds % SECONDS_IN_A_HOUR;
    /* minutes*/
    datetime->minute = Seconds / SECONDS_IN_A_MIN;
    /* seconds*/
    datetime->second = Seconds % SECONDS_IN_A_MIN;
    /* year*/
    datetime->year = YEAR_RANGE_START;
    Days_in_year = DAYS_IN_A_YEAR;

    while (Days > Days_in_year)
    {
        Days -= Days_in_year;
        datetime->year++;
        if  (datetime->year & 3U)
        {
            Days_in_year = DAYS_IN_A_YEAR;
        }
        else
        {
            Days_in_year = DAYS_IN_A_LEAP_YEAR;
        }
    }

    if (datetime->year & 3U)
    {
        Days_in_month = ULY;
    }
    else
    {
        Days_in_month = LY;
    }

    for (x = 1U; x <= 12U; x++)
    {
        if (Days <= (*(Days_in_month + x)))
        {
            datetime->month = x;
            break;
        }
        else
        {
            Days -= (*(Days_in_month + x));
        }
    }

    datetime->day = Days;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_IsDatetimeCorrectFormat
 * Description   : checks if the datetime is in correct format.
 * This function will check if the given datetime is in the correct format.
 *
 *END**************************************************************************/
bool RTC_HAL_IsDatetimeCorrectFormat(const rtc_datetime_t * datetime)
{
    bool result = false;

    /* Test correctness of given parameters*/
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) ||
        (datetime->month > 12U) || (datetime->month < 1U) ||
        (datetime->day > 31U) || (datetime->day < 1U) ||
        (datetime->hour >= HOURS_IN_A_DAY) || (datetime->minute >= MINS_IN_A_HOUR) ||
        (datetime->second >= SECONDS_IN_A_MIN))
    {
        /* If not correct then error*/
        result = false;
    }
    else
    {
        result = true;
    }

    /* Is given year un-leap-one?*/
    /* Leap year calculation only looks for years divisible by 4 as acceptable years is limited */
    if ( result && (datetime->year & 3U))
    {
        /* Does the obtained number of days exceed number of days in the appropriate month & year?*/
        if (ULY[datetime->month] < datetime->day)
        {
            /* If yes (incorrect datetime inserted) then error*/
            result = false;
        }
    }
    else /* Is given year leap-one?*/
    {
        /* Does the obtained number of days exceed number of days in the appropriate month & year?*/
        if (result && (LY[datetime->month] < datetime->day))
        {
            /* if yes (incorrect date inserted) then error*/
            result = false;
        }
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_ConvertDatetimeToSecs
 * Description   : converts time data from datetime to seconds.
 * This function will convert time data from datetime to seconds.
 *
 *END**************************************************************************/
void RTC_HAL_ConvertDatetimeToSecs(const rtc_datetime_t * datetime, uint32_t * seconds)
{
    /* Compute number of days from 1970 till given year*/
    *seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    *seconds += ((datetime->year / 4) - (1970U / 4));
    /* Add number of days till given month*/
    *seconds += MONTH_DAYS[datetime->month];
    /* Add days in given month. We take away seconds for the current day as it is
     * represented in the hours and seconds field*/
    *seconds += (datetime->day - 1);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
    {
        (*seconds)--;
    }

    *seconds = ((*seconds) * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
               (datetime->minute * SECONDS_IN_A_MIN) + datetime->second;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_Init
 * Description   : This function will clear all interrupts and resets the RTC
 * module if the time invalid flag is set.
 *
 *END**************************************************************************/
void RTC_HAL_Init(RTC_Type *base)
{
    if(RTC_BRD_SR_TIF(base))
    {
        /* Resets the RTC registers except for the SWR bit */
        RTC_HAL_SoftwareReset(base);
        RTC_HAL_SoftwareResetFlagClear(base);

        /* Set TSR register to 0x1 to avoid the TIF bit being set in the SR register */
        RTC_HAL_SetSecsReg(base, 1U);
    }
    /* Clear the interrupt enable register */
    RTC_HAL_SetSecsIntCmd(base, false);
    RTC_HAL_SetAlarmIntCmd(base, false);
    RTC_HAL_SetTimeOverflowIntCmd(base, false);
    RTC_HAL_SetTimeInvalidIntCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_SetDatetime
 * Description   : Sets the RTC date and time according to the given time structure.
 * The function converts the data from the time structure to seconds and writes the seconds
 * value to the RTC register. The RTC counter is started after setting the time.
 *
 *END**************************************************************************/
void RTC_HAL_SetDatetime(RTC_Type *base, const rtc_datetime_t * datetime)
{
    uint32_t seconds;

    /* Protect against null pointers*/
    assert(datetime);

    RTC_HAL_ConvertDatetimeToSecs(datetime, &seconds);
    /* Set time in seconds */
    RTC_HAL_SetDatetimeInsecs(base, seconds);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_SetDatetimeInsecs
 * Description   : Sets the RTC date and time according to the given time
 * provided in seconds. The RTC counter is started after setting the time.
 *
 *END**************************************************************************/
void RTC_HAL_SetDatetimeInsecs(RTC_Type *base, const uint32_t seconds)
{
    /* Disable counter*/
    RTC_HAL_EnableCounter(base, false);
    /* Set seconds counter*/
    RTC_HAL_SetSecsReg(base, seconds);
    /* Enable the counter*/
    RTC_HAL_EnableCounter(base, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_GetDatetime
 * Description   : Gets the RTC time and stores it in the given time structure.
 * The function reads the value in seconds from the RTC register. It then converts to the
 * time structure which provides the time in date, hour, minutes and seconds.
 *
 *END**************************************************************************/
void RTC_HAL_GetDatetime(RTC_Type *base, rtc_datetime_t * datetime)
{
    uint32_t seconds = 0;

    /* Protect against null pointers*/
    assert(datetime);

    RTC_HAL_GetDatetimeInSecs(base, &seconds);

    RTC_HAL_ConvertSecsToDatetime(&seconds, datetime);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_GetDatetimeInSecs
 * Description   : Gets the RTC time and returns it in seconds.
 *
 *END**************************************************************************/
void RTC_HAL_GetDatetimeInSecs(RTC_Type *base, uint32_t * seconds)
{
    /* Protect against null pointers*/
    assert(seconds);
    *seconds = RTC_HAL_GetSecsReg(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_SetAlarm
 * Description   : Sets the RTC alarm time and enables the alarm interrupt.
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 *END**************************************************************************/
bool RTC_HAL_SetAlarm(RTC_Type *base, const rtc_datetime_t * date)
{
    uint32_t alrm_seconds, curr_seconds;

    /* Protect against null pointers*/
    assert(date);

    RTC_HAL_ConvertDatetimeToSecs(date, &alrm_seconds);

    /* Get the current time */
    curr_seconds = RTC_HAL_GetSecsReg(base);

    /* Make sure the alarm is for a future time */
    if (alrm_seconds <= curr_seconds)
    {
        return false;
    }

    /* set alarm in seconds*/
    RTC_HAL_SetAlarmReg(base, alrm_seconds);

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_GetAlarm
 * Description   : Reads the value of the time alarm.
 *
 *END**************************************************************************/
void RTC_HAL_GetAlarm(RTC_Type *base, rtc_datetime_t * date)
{
    uint32_t seconds = 0;

    /* Protect against null pointers*/
    assert(date);

    /* Get alarm in seconds  */
    seconds = RTC_HAL_GetAlarmReg(base);

    RTC_HAL_ConvertSecsToDatetime(&seconds, date);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_GetMonotonicCounter
 * Description   : Reads the values of the Monotonic Counter High and Monotonic
 * Counter Low and returns them as a single value.
 *
 *END**************************************************************************/
void RTC_HAL_GetMonotonicCounter(RTC_Type *base, uint64_t * counter)
{
    uint32_t tmpCountHigh = 0;
    uint32_t tmpCountLow = 0;

    tmpCountHigh = RTC_HAL_GetMonotonicCounterHigh(base);
    tmpCountLow = RTC_HAL_GetMonotonicCounterLow(base);

    *counter = (((uint64_t)(tmpCountHigh) << 32) | ((uint64_t)tmpCountLow));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_SetMonotonicCounter
 * Description   : Writes values Monotonic Counter High and Monotonic
 * Counter Low by decomposing the given single value.
 *
 *END**************************************************************************/
void RTC_HAL_SetMonotonicCounter(RTC_Type *base, const uint64_t * counter)
{
    uint32_t tmpCountHigh = 0;
    uint32_t tmpCountLow = 0;

    tmpCountHigh = (uint32_t)((*counter) >> 32);
    RTC_HAL_SetMonotonicCounterHigh(base, tmpCountHigh);
    tmpCountLow = (uint32_t)(*counter);
    RTC_HAL_SetMonotonicCounterLow(base, tmpCountLow);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_IncrementMonotonicCounter
 * Description   : Increments the Monotonic Counter by one.
 * Increments the Monotonic Counter (registers RTC_MCLR and RTC_MCHR accordingly) by setting
 * the monotonic counter enable (MER[MCE]) and then writing to the RTC_MCLR register. A write to the
 * monotonic counter low that causes it to overflow also increments the monotonic counter high.
 *
 *END**************************************************************************/
bool RTC_HAL_IncrementMonotonicCounter(RTC_Type *base)
{
    bool result = false;

    if((!(RTC_HAL_IsMonotonicCounterOverflow(base))) && (!(RTC_HAL_IsTimeInvalid(base))))
    {
        /* prepare for incrementing after write*/
        RTC_HAL_SetMonotonicEnableCmd(base, true);

        /* write anything so the counter increments*/
        RTC_WR_MCLR(base, 1U);

        result = true;
    }

    return result;
}

#endif

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

