/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_GDET_H_
#define _FSL_GDET_H_

#include "fsl_common.h"

/*!
 * @addtogroup GDET
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines GDET driver version 2.0.0.
 *
 * Change log:
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_GDET_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!
 * @brief GDET Core Voltage.
 *
 * These constants are used to define core voltage argument to be used with
 * GDET_ReconfigureVoltageMode().
 */
typedef enum _gdet_core_voltage
{
    kGDET_MidVoltage       = 0U, /*!< Mid Voltage (1.0V) */
    kGDET_NormalVoltage    = 1U, /*!< Normal Voltage (1.1V) */
    kGDET_OverDriveVoltage = 2U, /*!< Over Drive Voltage (1.2V) */
} gdet_core_voltage_t;
/*******************************************************************************
 * API
 *******************************************************************************/

extern void GDET_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name GDET Functional Operation
 * @{
 */

/*!
 * @brief Initialize GDET
 *
 * This function initializes GDET block and setting.
 *
 * @param base GDET peripheral base address
 * @return Status of the init operation
 */
status_t GDET_Init(GDET_Type *base);

/*!
 * @brief Deinitialize GDET
 *
 * This function deinitializes GDET secure counter.
 *
 * @param base GDET peripheral base address
 */
void GDET_Deinit(GDET_Type *base);
/*!
 * @brief Turn on GDET isolation
 *
 * This function turns on isolation of GDET peripheral
 *
 * @param base GDET peripheral base address
 */
status_t GDET_IsolateOn(GDET_Type *base);

/*!
 * @brief Turn off GDET isolation
 *
 * This function turns off isolation of GDET peripheral
 *
 * @param base GDET peripheral base address
 */
status_t GDET_IsolateOff(GDET_Type *base);

/*!
 * @brief Change expected core voltage
 *
 * This function changes core voltage which Glitch detector expect.
 *
 * @param base GDET peripheral base address
 * @param voltage Expected core voltage
 * @return Status of the GDET reconfiguration operation
 */
status_t GDET_ReconfigureVoltageMode(GDET_Type *base, gdet_core_voltage_t voltage);

/*! @}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/ /* end of group gdet */

#endif /* _FSL_GDET_H_ */
