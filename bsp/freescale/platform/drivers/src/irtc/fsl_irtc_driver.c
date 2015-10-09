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
#include "fsl_irtc_driver.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_DRV_Init
 * Description   : Initializes the Real Time Clock module
 * This function will initialize the Real Time Clock module.
 *
 *END**************************************************************************/
irtc_status_t IRTC_DRV_Init(uint32_t instance,
                            const irtc_datetime_t * datetime,
                            const irtc_datetime_t * alarmDatetime,
                            irtc_alarm_match_t alarmMode,
                            const irtc_daylight_time_t * daylightTime)
{
    RTC_Type *base = g_irtcBase[instance];

    /* Enable clock gate to IRTC module */
    CLOCK_SYS_EnableRtcClock(instance);

    /* Initialize the general configuration for IRTC module.*/
    IRTC_HAL_Init(base);

    /* Unlock IRTC registers. */
    IRTC_HAL_SetLockRegisterCmd(base, false);

    /* Set date and time */
    if (datetime)
    {
        IRTC_HAL_SetDatetime(base, datetime);
    }

    /* Set daylight saving time */
    if (daylightTime)
    {
        IRTC_HAL_SetDaylightTime(base, daylightTime);
    }

    /* Set alarm of date and time */
    if (alarmDatetime)
    {
        IRTC_HAL_SetAlarm(base, alarmDatetime);
        IRTC_HAL_SetAlarmMatchMode(base, alarmMode);
        /* Enable alarm interrupt */
        RTC_WR_IER(base, 0x4U);
        /* Enable RTC interrupt */
        INT_SYS_EnableIRQ(g_irtcIrqId[instance]);
    }

    /* Lock IRTC registers. */
    IRTC_HAL_SetLockRegisterCmd(RTC, true);

    return kStatus_IRTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_DRV_Deinit
 * Description   : Disable IRTC module clock gate control
 * This function will disable clock gate to IRTC module.
 *
 *END**************************************************************************/
irtc_status_t IRTC_DRV_Deinit(uint32_t instance)
{
    /* Disable IRTC interrupts.*/
    INT_SYS_DisableIRQ(g_irtcIrqId[instance]);

    /* Disable clock gate to IRTC module */
    CLOCK_SYS_DisableRtcClock(instance);

    return kStatus_IRTC_Success;
}

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

