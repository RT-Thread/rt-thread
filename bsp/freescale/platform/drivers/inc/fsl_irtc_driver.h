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
#if !defined(__FSL_IRTC_DRIVER_H__)
#define __FSL_IRTC_DRIVER_H__

#include <stdint.h>
#include "fsl_irtc_hal.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*!
 * @addtogroup irtc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Table of base addresses for IRTC instances. */
extern RTC_Type * const g_irtcBase[RTC_INSTANCE_COUNT];

/*! @brief Table to save IRTC Alarm IRQ numbers for IRTC instances. */
extern const IRQn_Type g_irtcIrqId[RTC_INSTANCE_COUNT];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and De-initialization
 * @{
 */

/*!
 * @brief  Initializes the IRTC module.
 *
 * Enables the IRTC clock and interrupts if requested by the user.
 *
 * @param  instance The IRTC peripheral instance number.
 * @param  datetime Date and time need to set, pass NULL to ignore.
 * @param  alarmDatetime Alarm of date and time need to set, pass NULL to ignore.
 * @param  alarmMode Alarm mode to set when will generate alarm.
 * @param  daylightTime Daylight saving time need to set, pass NULL to ignore.
 * @return Error or success returned by API.
 */
irtc_status_t IRTC_DRV_Init(uint32_t instance,
                            const irtc_datetime_t * datetime,
                            const irtc_datetime_t * alarmDatetime,
                            irtc_alarm_match_t alarmMode,
                            const irtc_daylight_time_t * daylightTime);

/*!
 * @brief  Disables the IRTC module clock gate control.
 *
 * @param  instance The IRTC peripheral instance number.
 * @return Error or success returned by API.
 */
irtc_status_t IRTC_DRV_Deinit(uint32_t instance);

/* @} */

/*!
 * @name IRTC Datetime Set and Get
 * @{
 */

/*!
 * @brief  Sets the IRTC date and time according to the given time structure.
 *
 * @param  instance The IRTC peripheral instance number.
 * @param  datetime Pointer to structure where the date and time
 *         details to set are stored.
 */
static inline void IRTC_DRV_SetDatetime(uint32_t instance, irtc_datetime_t *datetime)
{
    IRTC_HAL_SetDatetime(g_irtcBase[instance], datetime);
}

/*!
 * @brief  Gets the IRTC time and stores it in the given time structure.
 *
 * @param  instance The IRTC peripheral instance number.
 * @param  datetime Pointer to structure where the date and time details are
 *         stored.
 */
static inline void IRTC_DRV_GetDatetime(uint32_t instance, irtc_datetime_t *datetime)
{
    IRTC_HAL_GetDatetime(g_irtcBase[instance], datetime);
}

/* @} */

/*!
 * @name IRTC Alarm
 * @{
 */

/*!
 * @brief Sets the alarm match type.
 *
 * @param instance The IRTC peripheral instance number.
 * @param alarmType Alarm match selections that when an alarm will happen.
 */
static inline void IRTC_DRV_SetAlarmMatchMode(uint32_t instance, irtc_alarm_match_t alarmType)
{
    IRTC_HAL_SetAlarmMatchMode(g_irtcBase[instance], alarmType);
}

/*!
 * @brief  Sets the IRTC alarm time.
 *
 * @param  instance The IRTC peripheral instance number.
 * @param  alarmTime Pointer to structure where the alarm time is store.
 */
static inline void IRTC_DRV_SetAlarm(uint32_t instance, irtc_datetime_t *alarmTime)
{
    IRTC_HAL_SetAlarm(g_irtcBase[instance], alarmTime);
}

/*!
 * @brief  Returns the IRTC alarm time.
 *
 * @param  instance The IRTC peripheral instance number.
 * @param  date Pointer to structure where the alarm date and time
 *         details are stored.
 */
static inline void IRTC_DRV_GetAlarm(uint32_t instance, irtc_datetime_t *date)
{
    IRTC_HAL_GetAlarm(g_irtcBase[instance], date);
}
/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables or disables the related IRTC interrupt.
 *
 * @param instance The IRTC peripheral instance number.
 * @param interrupt The interrupt name, defined in type irtc_int_t.
 * @param enable Enable(ture) or disable(false) related interrupt.
 */
static inline void IRTC_DRV_SetIntCmd(uint32_t instance, irtc_int_t interrupt, bool enable)
{
    IRTC_HAL_SetIntCmd(g_irtcBase[instance], interrupt, enable);
}

/*!
 * @brief Gets whether the IRTC interrupt is enabled or not.
 *
 * @param instance The IRTC peripheral instance number.
 * @param interrupt The interrupt name, defined in type irtc_int_t.
 * @return State of the interrupt: asserted (true) or not-asserted (false).
 *         - true: related interrupt is being enabled.
 *         - false: related interrupt is not enabled.
 */
static inline bool IRTC_DRV_GetIntCmd(uint32_t instance, irtc_int_t interrupt)
{
    return IRTC_HAL_GetIntCmd(g_irtcBase[instance], interrupt);
}

/*!
 * @brief Gets the IRTC interrupt status flag state.
 *
 * @param instance The IRTC peripheral instance number.
 * @param statusFlag The status flag, defined in type irtc_int_status_flag_t.
 * @return State of the status flag: asserted (true) or not-asserted (false).
 *         - true: related status flag is being set.
 *         - false: related status flag is not set.
 */
static inline bool IRTC_DRV_GetIntStatusFlag(uint32_t instance, irtc_int_status_flag_t statusFlag)
{
    return IRTC_HAL_GetIntStatusFlag(g_irtcBase[instance], statusFlag);
}

/*!
 * @brief Clears the IRTC interrupt status flag.
 *
 * Tamper interrupt status flag is cleared when the TAMPER_SCR[TMPR_STS] is cleared.
 *
 * @param instance The IRTC peripheral instance number.
 * @param statusFlag The status flag, defined in type irtc_int_status_flag_t.
 */
static inline void IRTC_DRV_ClearIntStatusFlag(uint32_t instance, irtc_int_status_flag_t statusFlag)
{
    IRTC_HAL_ClearIntStatusFlag(g_irtcBase[instance], statusFlag);
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

#endif /* __FSL_IRTC_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

