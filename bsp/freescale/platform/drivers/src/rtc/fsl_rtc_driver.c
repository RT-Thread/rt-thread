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

#include <string.h>
#include "fsl_rtc_driver.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*!
 * @addtogroup rtc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! Stores state of the RTC alarm when repeated periodically */
static rtc_repeat_alarm_state_t *s_rtcRepeatAlarmState = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_Init
 * Description   : Initializes the Real Time Clock module
 * This function will initialize the Real Time Clock module.
 *
 *END**************************************************************************/

rtc_status_t RTC_DRV_Init(uint32_t instance)
{
    RTC_Type *rtcBase = g_rtcBase[instance];

    /* Enable clock gate to RTC module */
    CLOCK_SYS_EnableRtcClock(0U);

    /* Initialize the general configuration for RTC module.*/
    RTC_HAL_Init(rtcBase);

    NVIC_ClearPendingIRQ(g_rtcIrqId[instance]);
    NVIC_ClearPendingIRQ(g_rtcSecondsIrqId[instance]);
    INT_SYS_EnableIRQ(g_rtcIrqId[instance]);
    INT_SYS_EnableIRQ(g_rtcSecondsIrqId[instance]);

    return kStatusRtcSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_Deinit
 * Description   : Disable RTC module clock gate control
 * This function will disable clock gate to RTC module.
 *
 *END**************************************************************************/
void RTC_DRV_Deinit(uint32_t instance)
{
    /* Disable RTC interrupts.*/
    INT_SYS_DisableIRQ(g_rtcIrqId[instance]);
    INT_SYS_DisableIRQ(g_rtcSecondsIrqId[instance]);

    /* Disable clock gate to RTC module */
    CLOCK_SYS_DisableRtcClock(0U);
    s_rtcRepeatAlarmState = NULL;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_IsCounterEnabled
 * Description   : Checks whether the RTC is enabled.
 * The function checks the TCE bit in the RTC control register.
 *
 *END**************************************************************************/
bool RTC_DRV_IsCounterEnabled(uint32_t instance)
{
    return RTC_HAL_IsCounterEnabled(g_rtcBase[instance]);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetDatetime
 * Description   : Sets the RTC date and time according to the given time struct.
 * This function will set the RTC date and time according to the given time
 * struct, if start_after_set is true, the RTC oscillator will be enabled and
 * the counter will start.
 *
 *END**************************************************************************/
bool RTC_DRV_SetDatetime(uint32_t instance, rtc_datetime_t *datetime)
{
    assert(datetime);
    RTC_Type *rtcBase = g_rtcBase[instance];
    uint32_t srcClock = 0;
    uint32_t seconds = 0;
    uint16_t preScaler = 0;
    uint64_t tmp = 0;

    /* Return error if the time provided is not valid */
    if (!(RTC_HAL_IsDatetimeCorrectFormat(datetime)))
    {
        return false;
    }

    RTC_HAL_ConvertDatetimeToSecs(datetime, &seconds);

    if ((srcClock = CLOCK_SYS_GetRtcFreq(0U)) != 32768U)
    {
        /* As the seconds register will not increment every second, we need to adjust the value
         * programmed to the seconds register */
        tmp = (uint64_t)seconds * (uint64_t)srcClock;
        preScaler = (uint32_t)(tmp & 0x7FFFU);
        seconds = (uint32_t)(tmp >> 15U);
    }
    /* Set time in seconds */
    RTC_HAL_EnableCounter(rtcBase, false);
    /* Set seconds counter*/
    RTC_HAL_SetSecsReg(rtcBase, seconds);
    /* Set time counter*/
    RTC_HAL_SetPrescaler(rtcBase, preScaler);
     /* Enable the counter*/
    RTC_HAL_EnableCounter(rtcBase, true);
    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_GetDatetime
 * Description   : Gets the actual RTC time and stores it in the given time struct.
 * This function will get the actual RTC time and stores it in the given time
 * struct.
 *
 *END**************************************************************************/
void RTC_DRV_GetDatetime(uint32_t instance, rtc_datetime_t *datetime)
{
    assert(datetime);

    RTC_Type *rtcBase = g_rtcBase[instance];
    uint32_t seconds = 0;
    uint32_t srcClock = 0;
    uint64_t tmp = 0;

    RTC_HAL_GetDatetimeInSecs(rtcBase, &seconds);

    if ((srcClock = CLOCK_SYS_GetRtcFreq(0U)) != 32768U)
    {
        /* In case the input clock to the RTC counter is not 32KHz, the seconds register will not
         * increment every second, therefore the seconds register value needs to be adjusted.
         * to get actual seconds. We then add the prescaler register value to the seconds.
         */
        tmp = (uint64_t)seconds << 15U;
        tmp |= (uint64_t)(RTC_HAL_GetPrescaler(rtcBase) & 0x7FFFU);
        seconds = tmp / srcClock;
    }
    RTC_HAL_ConvertSecsToDatetime(&seconds, datetime);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetSecsIntCmd
 * Description   : Enables or disables the RTC seconds interrupt.
 *
 *END**************************************************************************/
void RTC_DRV_SetSecsIntCmd(uint32_t instance, bool secondsEnable)
{
    RTC_HAL_SetSecsIntCmd(g_rtcBase[instance], secondsEnable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetAlarm
 * Description   : sets the RTC alarm.
 * This function will first check if the date time has correct format. If yes,
 * convert the date time to seconds, and set the alarm in seconds.
 *
 *END**************************************************************************/
bool RTC_DRV_SetAlarm(uint32_t instance, rtc_datetime_t *alarmTime, bool enableAlarmInterrupt)
{
    assert(alarmTime);

    RTC_Type *rtcBase = g_rtcBase[instance];
    uint32_t srcClock = 0;
    uint32_t alrmSeconds = 0;
    uint32_t currSeconds = 0;
    uint64_t tmp = 0;

    /* Return error if the alarm time provided is not valid */
    if (!(RTC_HAL_IsDatetimeCorrectFormat(alarmTime)))
    {
        return false;
    }

    RTC_HAL_ConvertDatetimeToSecs(alarmTime, &alrmSeconds);

    /* Get the current time */
    currSeconds = RTC_HAL_GetSecsReg(rtcBase);

    if ((srcClock = CLOCK_SYS_GetRtcFreq(instance)) != 32768U)
    {
        /* As the seconds register will not increment every second, we need to adjust the value
         * programmed to the alarm register */
        tmp = (uint64_t)alrmSeconds * (uint64_t)srcClock;
        alrmSeconds = (uint32_t)(tmp >> 15U);
    }

    /* Make sure the alarm is for a future time */
    if (alrmSeconds < currSeconds)
    {
        return false;
    }

    /* set alarm in seconds*/
    RTC_HAL_SetAlarmReg(rtcBase, alrmSeconds);

    /* Activate or deactivate the Alarm interrupt based on user choice */
    RTC_HAL_SetAlarmIntCmd(rtcBase, enableAlarmInterrupt);

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_GetAlarm
 * Description   : returns the RTC alarm time.
 * This function will first get alarm time in seconds, then convert the seconds to
 * date time.
 *
 *END**************************************************************************/
void RTC_DRV_GetAlarm(uint32_t instance, rtc_datetime_t *date)
{
    assert(date);

    uint32_t alrmSeconds = 0;
    uint32_t srcClock = 0;

    /* Get alarm in seconds  */
    alrmSeconds = RTC_HAL_GetAlarmReg(g_rtcBase[instance]);

    if ((srcClock = CLOCK_SYS_GetRtcFreq(0U)) != 32768U)
    {
        /* Re-adjust the alarm value to match the method used to program it */
        alrmSeconds = (alrmSeconds * (32768U / srcClock));
    }

    RTC_HAL_ConvertSecsToDatetime(&alrmSeconds, date);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_InitRepeatAlarm
 * Description   : Initializes the RTC repeat alarm state structure.
 * The RTC driver uses this user-provided structure to store the alarm state
 * information.
 *
 *END**************************************************************************/
void RTC_DRV_InitRepeatAlarm(uint32_t instance, rtc_repeat_alarm_state_t *repeatAlarmState)
{
    assert(repeatAlarmState);

    /* Init driver repeat alarm struct.*/
    memset(repeatAlarmState, 0, sizeof(*repeatAlarmState));
    s_rtcRepeatAlarmState = repeatAlarmState;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetAlarmRepeat
 * Description   : Sets an alarm that is periodically repeated.
 *
 *END**************************************************************************/
bool RTC_DRV_SetAlarmRepeat(uint32_t instance, rtc_datetime_t *alarmTime, rtc_datetime_t *alarmRepInterval)
{
    assert(s_rtcRepeatAlarmState);
    assert(alarmRepInterval);

    if (!(RTC_DRV_SetAlarm(instance, alarmTime, true)))
    {
        return false;
    }

    memcpy(&s_rtcRepeatAlarmState->alarmTime, alarmTime, sizeof(*alarmTime));
    memcpy(&s_rtcRepeatAlarmState->alarmRepTime, alarmRepInterval, sizeof(*alarmRepInterval));

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_DeinitRepeatAlarm
 * Description   : De-initializes the RTC repeat alarm state structure.
 *
 *END**************************************************************************/
void RTC_DRV_DeinitRepeatAlarm(uint32_t instance)
{
    s_rtcRepeatAlarmState = NULL;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetAlarmIntCmd
 * Description   : Enables or disables the alarm interrupt.
 *
 *END**************************************************************************/
void RTC_DRV_SetAlarmIntCmd(uint32_t instance, bool alarmEnable)
{
    RTC_HAL_SetAlarmIntCmd(g_rtcBase[instance], alarmEnable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_GetAlarmIntCmd
 * Description   : Reads the alarm interrupt.
 *
 *END**************************************************************************/
bool RTC_DRV_GetAlarmIntCmd(uint32_t instance)
{
    return RTC_HAL_ReadAlarmInt(g_rtcBase[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_IsAlarmPending
 * Description   : Reads the alarm status to see if the alarm has triggered.
 *
 *END**************************************************************************/
bool RTC_DRV_IsAlarmPending(uint32_t instance)
{
    /* Return alarm time and status (triggered or not) */
    return RTC_HAL_HasAlarmOccured(g_rtcBase[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SetTimeCompensation
 * Description   : Writes the compensation value to the RTC compensation register.
 *
 *END**************************************************************************/
void RTC_DRV_SetTimeCompensation(uint32_t instance, uint32_t compensationInterval,
                                            uint32_t compensationTime)
{
    RTC_Type *rtcBase = g_rtcBase[instance];

    RTC_HAL_SetCompensationIntervalRegister(rtcBase, compensationInterval);
    RTC_HAL_SetTimeCompensationRegister(rtcBase, compensationTime);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_GetTimeCompensation
 * Description   : Reads the compensation value from the RTC compensation register.
 *
 *END**************************************************************************/
void RTC_DRV_GetTimeCompensation(uint32_t instance, uint32_t *compensationInterval,
                                            uint32_t *compensationTime)
{
    RTC_Type *rtcBase = g_rtcBase[instance];

    *compensationInterval = RTC_HAL_GetCompensationIntervalCounter(rtcBase);
    *compensationTime = RTC_HAL_GetTimeCompensationValue(rtcBase);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_AlarmIntAction
 * Description   : Action to take when an RTC alarm interrupt is triggered. To receive
 * alarms periodically, the RTC_TAR register is updated using the repeat interval.
 *
 *END**************************************************************************/
void RTC_DRV_AlarmIntAction(uint32_t instance)
{
    RTC_Type *rtcBase = g_rtcBase[instance];

    if (s_rtcRepeatAlarmState != NULL)
    {
        s_rtcRepeatAlarmState->alarmTime.year += s_rtcRepeatAlarmState->alarmRepTime.year;
        s_rtcRepeatAlarmState->alarmTime.month += s_rtcRepeatAlarmState->alarmRepTime.month;
        s_rtcRepeatAlarmState->alarmTime.day += s_rtcRepeatAlarmState->alarmRepTime.day;
        s_rtcRepeatAlarmState->alarmTime.hour += s_rtcRepeatAlarmState->alarmRepTime.hour;
        s_rtcRepeatAlarmState->alarmTime.minute += s_rtcRepeatAlarmState->alarmRepTime.minute;
        RTC_DRV_SetAlarm(instance, &s_rtcRepeatAlarmState->alarmTime, true);
    }
    else
    {
        /* Writing to the alarm register clears the TAF flag in the Status register */
        RTC_HAL_SetAlarmReg(rtcBase, 0x0);
        RTC_HAL_SetAlarmIntCmd(rtcBase, false);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_SecsIntAction
 * Description   : Action to take when an RTC seconds interrupt is triggered.
 * Disables the time seconds interrupt (TSIE) bit.
 *
 *END**************************************************************************/
void RTC_DRV_SecsIntAction(uint32_t instance)
{
    RTC_HAL_SetSecsIntCmd(g_rtcBase[instance], false);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_DRV_IncrementMonotonic
 * Description   : Increments monotonic counter by one.
 * This function will increment monotonic counter by one.
 *
 *END**************************************************************************/
bool RTC_DRV_IncrementMonotonic(uint32_t instance)
{
    return RTC_HAL_IncrementMonotonicCounter(g_rtcBase[instance]);
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

