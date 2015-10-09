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
#if !defined(__FSL_RTC_DRIVER_H__)
#define __FSL_RTC_DRIVER_H__

#include <stdint.h>
#include "fsl_rtc_hal.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*!
 * @addtogroup rtc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Table of base addresses for RTC instances. */
extern RTC_Type * const g_rtcBase[RTC_INSTANCE_COUNT];

/*! @brief Table to save RTC Alarm IRQ numbers for RTC instances. */
extern const IRQn_Type g_rtcIrqId[RTC_INSTANCE_COUNT];
/*! @brief Table to save RTC Seconds IRQ numbers for RTC instances. */
extern const IRQn_Type g_rtcSecondsIrqId[RTC_INSTANCE_COUNT];

/*!
 *  @brief RTC repeated alarm information used by the RTC driver
 */
typedef struct RtcRepeatAlarmState
{
    rtc_datetime_t alarmTime; /*!< Sets the RTC alarm time. */
    rtc_datetime_t alarmRepTime;       /*!< Period for alarm to repeat, needs alarm interrupt be enabled.*/
} rtc_repeat_alarm_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Deinitialization
 * @{
 */

/*!
 * @brief  Initializes the RTC module.
 *
 * Enables the RTC clock and interrupts if requested by the user.
 *
 * @param  instance The RTC peripheral instance number.
 * @return kStatusRtcSuccess means success; Otherwise means failed.
 */
rtc_status_t RTC_DRV_Init(uint32_t instance);

/*!
 * @brief  Disables the RTC module clock gate control.
 *
 * @param  instance The RTC peripheral instance number.
 */
void RTC_DRV_Deinit(uint32_t instance);

/* @} */

/*!
 * @brief  Checks whether the RTC is enabled.
 *
 * The function checks the TCE bit in the RTC control register.
 *
 * @param  instance The RTC peripheral instance number.
 *
 * @return true: The RTC counter is enabled\n
 *         false: The RTC counter is disabled
 */
bool RTC_DRV_IsCounterEnabled(uint32_t instance);

/*!
 * @name RTC datetime set and get
 * @{
 */

/*!
 * @brief  Sets the RTC date and time according to the given time structure.
 *
 * The RTC counter is started after the time is set.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  datetime [in] pointer to structure where the date and time
 *         details to set are stored.
 *
 * @return true: success in setting the time and starting the RTC\n
 *         false: failure. An error occurs because the datetime format is incorrect.
 */
bool RTC_DRV_SetDatetime(uint32_t instance, rtc_datetime_t *datetime);

/*!
 * @brief  Gets the RTC time and stores it in the given time structure.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  datetime [out] pointer to structure where the date and time details are
 *         stored.
 */
void RTC_DRV_GetDatetime(uint32_t instance, rtc_datetime_t *datetime);
/* @} */

/*!
 * @brief  Enables or disables the RTC seconds interrupt.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  secondsEnable Takes true or false\n
 *          true: indicates seconds interrupt should be enabled\n
 *          false: indicates seconds interrupt should be disabled
 */
void RTC_DRV_SetSecsIntCmd(uint32_t instance, bool secondsEnable);

/*!
 * @name RTC alarm
 * @{
 */

/*!
 * @brief  Sets the RTC alarm time and enables the alarm interrupt.
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  alarmTime [in] pointer to structure where the alarm time is stored.
 * @param  enableAlarmInterrupt Takes true of false\n
 *          true: indicates alarm interrupt should be enabled\n
 *          false: indicates alarm interrupt should be disabled
 *
 * @return  true: success in setting the RTC alarm\n
 *          false: error in setting the RTC alarm. Error occurs because the alarm datetime format
 *                 is incorrect.
 */
bool RTC_DRV_SetAlarm(uint32_t instance, rtc_datetime_t *alarmTime, bool enableAlarmInterrupt);

/*!
 * @brief  Returns the RTC alarm time.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  date [out] pointer to structure where the alarm date and time
 *         details are stored.
 */
void RTC_DRV_GetAlarm(uint32_t instance, rtc_datetime_t *date);

/*!
 * @brief  Initializes the RTC repeat alarm state structure.
 *
 * The RTC driver uses this user-provided structure to store the alarm state
 * information.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  repeatAlarmState Pointer to structure where the alarm state is stored
 */
void RTC_DRV_InitRepeatAlarm(uint32_t instance, rtc_repeat_alarm_state_t *repeatAlarmState);

/*!
 * @brief  Sets an alarm that is periodically repeated.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  alarmTime Pointer to structure where the alarm time is provided.
 * @param  alarmRepInterval pointer to structure with the alarm repeat interval.
 *
 * @return true: success in setting the RTC alarm\n
 *         false: error in setting the RTC alarm. Error occurs because the alarm datetime format
 *                is incorrect.
 */
bool RTC_DRV_SetAlarmRepeat(uint32_t instance, rtc_datetime_t *alarmTime, rtc_datetime_t *alarmRepInterval);

/*!
 * @brief  Deinitializes the RTC repeat alarm state structure.
 *
 * @param  instance The RTC peripheral instance number.
 */
void RTC_DRV_DeinitRepeatAlarm(uint32_t instance);

/* @} */

/*!
 * @brief  Enables or disables the alarm interrupt.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  alarmEnable Takes true or false\n
 *          true: indicates alarm interrupt should be enabled\n
 *          false: indicates alarm interrupt should be disabled
 */
void RTC_DRV_SetAlarmIntCmd(uint32_t instance, bool alarmEnable);

/*!
 * @brief  Reads the alarm interrupt.
 *
 * @param  instance The RTC peripheral instance number.
 *
 * @return  true: indicates alarm interrupt is enabled\n
 *          false: indicates alarm interrupt is disabled
 */
bool RTC_DRV_GetAlarmIntCmd(uint32_t instance);

/*!
 * @brief  Reads the alarm status to see if the alarm is triggered.
 *
 * @param  instance The RTC peripheral instance number.
 *
 * @return  returns alarm status, for example, returns whether the alarm triggered\n
 *          true: indicates alarm has occurred\n
 *          false: indicates alarm has not occurred
 */
bool RTC_DRV_IsAlarmPending(uint32_t instance);

/*!
 * @brief  Writes the compensation value to the RTC compensation register.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  compensationInterval User-specified compensation interval that is written
 *                           to the CIR field in RTC Time Compensation Register (TCR)
 * @param  compensationTime User-specified compensation time that is written
 *                           to the TCR field in RTC Time Compensation Register (TCR)
 */
void RTC_DRV_SetTimeCompensation(uint32_t instance, uint32_t compensationInterval,
                                            uint32_t compensationTime);


/*!
 * @brief  Reads the compensation value from the RTC compensation register.
 *
 * @param  instance The RTC peripheral instance number.
 * @param  compensationInterval User-specified pointer to store the compensation interval counter. This value
 *                           is read from the CIC field in RTC Time Compensation Register (TCR)
 * @param  compensationTime User-specified pointer to store the compensation time value. This value
 *                           is read from the TCV field in RTC Time Compensation Register (TCR)
 */
void RTC_DRV_GetTimeCompensation(uint32_t instance, uint32_t *compensationInterval,
                                            uint32_t *compensationTime);


#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*!
 * @name Increments monotonic counter
 * @{
 */

/*!
 * @brief      Increments the monotonic counter by one.
 *
 * @param  instance The RTC peripheral instance number.
 *
 * @return     True: increment successful\n
 *             False: error invalid time found because of a tamper source enabled is detected
 *             and any write to the tamper time seconds counter is done.
 */
bool RTC_DRV_IncrementMonotonic(uint32_t instance);
/* @} */
#endif

/*!
 * @name ISR Functions
 * @{
 */

/*!
 * @brief Implements the RTC alarm handler named in the startup code.
 *
 * Handles the RTC alarm interrupt and invokes any callback related to
 * the RTC alarm.
 */
void RTC_IRQHandler(void);

/*!
 * @brief Implements the RTC seconds handler named in the startup code.
 *
 * Handles the RTC seconds interrupt and invokes any callback related to
 * the RTC second tick.
 */
void RTC_Seconds_IRQHandler(void);

/*! @}*/

/*!
 * @brief  Action to take when an RTC alarm interrupt is triggered. To receive
 *         alarms periodically, the RTC_TAR register is updated using the repeat interval.
 *
 * @param  instance The RTC peripheral instance number.
 */
void RTC_DRV_AlarmIntAction(uint32_t instance);

/*!
 * @brief  Action to take when an RTC seconds interrupt is triggered.
 *
 * Disables the time seconds interrupt (TSIE) bit.
 *
 * @param  instance The RTC peripheral instance number.
 */
void RTC_DRV_SecsIntAction(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

#endif /* __FSL_RTC_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

