/*
 * The Clear BSD License
 * Copyright (c) 2018, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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
#ifndef _FSL_TEMPMON_H_
#define _FSL_TEMPMON_H_

#include "fsl_common.h"

/*!
 * @addtogroup tempmon
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_TEMPMON_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0 */
/*@}*/

/*! @brief TEMPMON temperature structure. */
typedef struct _tempmon_config
{
    uint16_t frequency;      /*!< The temperature measure frequency.*/
    uint32_t highAlarmTemp;  /*!< The high alarm temperature.*/
    uint32_t panicAlarmTemp; /*!< The panic alarm temperature.*/
    uint32_t lowAlarmTemp;   /*!< The low alarm temperature.*/
} tempmon_config_t;

/*! @brief TEMPMON alarm mode. */
typedef enum _tempmon_alarm_mode
{
    kTEMPMON_HighAlarmMode = 0U,  /*!< The high alarm temperature interrupt mode.*/
    kTEMPMON_PanicAlarmMode = 1U, /*!< The panic alarm temperature interrupt mode.*/
    kTEMPMON_LowAlarmMode = 2U,   /*!< The low alarm temperature interrupt mode.*/
} tempmon_alarm_mode;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the TEMPMON module.
 *
 * @param base TEMPMON base pointer
 * @param config Pointer to configuration structure.
 */
void TEMPMON_Init(TEMPMON_Type *base, const tempmon_config_t *config);

/*!
 * @brief Deinitializes the TEMPMON module.
 *
 * @param base TEMPMON base pointer
 */
void TEMPMON_Deinit(TEMPMON_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the TEMPMON configuration structure to a default value. The default
 * values are:
 *   tempmonConfig->frequency = 0x02U;
 *   tempmonConfig->highAlarmTemp = 44U;
 *   tempmonConfig->panicAlarmTemp = 90U;
 *   tempmonConfig->lowAlarmTemp = 39U;
 *
 * @param config Pointer to a configuration structure.
 */
void TEMPMON_GetDefaultConfig(tempmon_config_t *config);

/*!
 * @brief start the temperature measurement process.
 *
 * @param base TEMPMON base pointer.
 */
static inline void TEMPMON_StartMeasure(TEMPMON_Type *base)
{
    base->TEMPSENSE0 |= TEMPMON_TEMPSENSE0_MEASURE_TEMP_MASK;
}

/*!
 * @brief stop the measurement process.
 *
 * @param base TEMPMON base pointer
 */
static inline void TEMPMON_StopMeasure(TEMPMON_Type *base)
{
    base->TEMPSENSE0 &= ~TEMPMON_TEMPSENSE0_MEASURE_TEMP_MASK;
}

/*!
 * @brief Get current temperature with the fused temperature calibration data.
 *
 * @param base TEMPMON base pointer
 * @return current temperature with degree Celsius.
 */
float TEMPMON_GetCurrentTemperature(TEMPMON_Type *base);

/*!
 * @brief Set the temperature count (raw sensor output) that will generate an alarm interrupt.
 *
 * @param base TEMPMON base pointer
 * @param tempVal The alarm temperature with degree Celsius
 * @param alarmMode The alarm mode.
 */
void TEMPMON_SetTempAlarm(TEMPMON_Type *base, uint32_t tempVal, tempmon_alarm_mode alarmMode);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_TEMPMON_H_ */
