/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_TEMPMON_H_
#define _FSL_TEMPMON_H_

#include "fsl_common.h"

/*!
 * @addtogroup tempsensor
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_TMPSNS_DRIVER_VERSION (MAKE_VERSION(2, 0, 3)) /*!< Version 2.0.3 */
/*@}*/

/*! @brief TMPSNS interrupt status type, tmpsns_interrupt_status_enable_t. */
enum
{
    kTEMPSENSOR_HighTempInterruptStatusEnable =
        TMPSNS_CTRL1_HIGH_TEMP_IE_MASK, /*!< High temperature interrupt status enable.*/
    kTEMPSENSOR_LowTempInterruptStatusEnable =
        TMPSNS_CTRL1_LOW_TEMP_IE_MASK, /*!< High temperature interrupt status enable.*/
    kTEMPSENSOR_PanicTempInterruptStatusEnable =
        TMPSNS_CTRL1_PANIC_TEMP_IE_MASK, /*!< High temperature interrupt status enable.*/
    kTEMPSENSOR_FinishInterruptStatusEnable =
        TMPSNS_CTRL1_FINISH_IE_MASK, /*!< High temperature interrupt status enable.*/
};

/*! @brief TMPSNS measure mode, tempsensor_measure_mode. */
typedef enum
{
    kTEMPSENSOR_SingleMode     = 0U, /*!< Single measurement mode.*/
    kTEMPSENSOR_ContinuousMode = 1U, /*!< Continuous measurement mode.*/
} tmpsns_measure_mode_t;

/*! @brief TMPSNS temperature structure. */
typedef struct _tmpsns_config
{
    tmpsns_measure_mode_t measureMode; /*!< The temperature measure mode.*/
    uint16_t frequency;                /*!< The temperature measure frequency.*/
    int32_t highAlarmTemp;             /*!< The high alarm temperature.*/
    int32_t panicAlarmTemp;            /*!< The panic alarm temperature.*/
    int32_t lowAlarmTemp;              /*!< The low alarm temperature.*/
} tmpsns_config_t;

/*! @brief TMPSNS alarm mode. */
typedef enum _tmpsns_alarm_mode
{
    kTEMPMON_HighAlarmMode  = 0U, /*!< The high alarm temperature interrupt mode.*/
    kTEMPMON_PanicAlarmMode = 1U, /*!< The panic alarm temperature interrupt mode.*/
    kTEMPMON_LowAlarmMode   = 2U, /*!< The low alarm temperature interrupt mode.*/
} tmpsns_alarm_mode_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the TMPSNS module.
 *
 * @param base TMPSNS base pointer
 * @param config Pointer to configuration structure.
 */
void TMPSNS_Init(TMPSNS_Type *base, const tmpsns_config_t *config);

/*!
 * @brief Deinitializes the TMPSNS module.
 *
 * @param base TMPSNS base pointer
 */
void TMPSNS_Deinit(TMPSNS_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the TMPSNS configuration structure to a default value. The default
 * values are:
 *   tempmonConfig->frequency = 0x02U;
 *   tempmonConfig->highAlarmTemp = 44U;
 *   tempmonConfig->panicAlarmTemp = 90U;
 *   tempmonConfig->lowAlarmTemp = 39U;
 *
 * @param config Pointer to a configuration structure.
 */
void TMPSNS_GetDefaultConfig(tmpsns_config_t *config);

/*!
 * @brief start the temperature measurement process.
 *
 * @param base TMPSNS base pointer.
 */
void TMPSNS_StartMeasure(TMPSNS_Type *base);

/*!
 * @brief stop the measurement process.
 *
 * @param base TMPSNS base pointer
 */
void TMPSNS_StopMeasure(TMPSNS_Type *base);

/*!
 * @brief Get current temperature with the fused temperature calibration data.
 *
 * @param base TMPSNS base pointer
 * @return current temperature with degrees Celsius.
 */
float TMPSNS_GetCurrentTemperature(TMPSNS_Type *base);

/*!
 * @brief Set the temperature count (raw sensor output) that will generate an alarm interrupt.
 *
 * @param base TMPSNS base pointer
 * @param tempVal The alarm temperature with degrees Celsius
 * @param alarmMode The alarm mode.
 */
void TMPSNS_SetTempAlarm(TMPSNS_Type *base, int32_t tempVal, tmpsns_alarm_mode_t alarmMode);

/*!
 * @brief Enable interrupt status.
 *
 * @param base TMPSNS base pointer
 * @param mask The interrupts to enable from tmpsns_interrupt_status_enable_t.
 */
void TMPSNS_EnableInterrupt(TMPSNS_Type *base, uint32_t mask);

/*!
 * @brief Disable interrupt status.
 *
 * @param base TMPSNS base pointer
 * @param mask The interrupts to disable from tmpsns_interrupt_status_enable_t.
 */
void TMPSNS_DisableInterrupt(TMPSNS_Type *base, uint32_t mask);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_TEMPMON_H_ */
