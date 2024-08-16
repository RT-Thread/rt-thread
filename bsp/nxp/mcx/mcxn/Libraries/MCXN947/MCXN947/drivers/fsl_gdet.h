/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_GDET_H_
#define FSL_GDET_H_

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
/*! @{ */
/*! @brief Defines GDET driver version 2.0.0.
 *
 * Change log:
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_GDET_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

/*!
 * @brief GDET Core Voltage.
 *
 * These constants are used to define core voltage argument to be used with
 * GDET_ReconfigureVoltageMode().
 */

typedef uint32_t gdet_core_voltage_t;
#define kGDET_MidVoltage       ((gdet_core_voltage_t)0x0u) /*!< Mid Voltage (1.0V) */
#define kGDET_NormalVoltage    ((gdet_core_voltage_t)0x1u) /*!< Normal Voltage (1.1V) */
#define kGDET_OverDriveVoltage ((gdet_core_voltage_t)0x2u) /*!< Over Drive Voltage (1.2V) */

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
#endif   /* __cplusplus */

/*! @}*/ /* end of group gdet */

#endif   /* FSL_GDET_H_ */
