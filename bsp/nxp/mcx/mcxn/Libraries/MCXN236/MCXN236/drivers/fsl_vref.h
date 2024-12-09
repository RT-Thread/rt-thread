/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_VREF_H_
#define FSL_VREF_H_

#include "fsl_common.h"

/*!
 * @addtogroup vref
 * @{
 */

/******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_VREF_DRIVER_VERSION (MAKE_VERSION(2, 2, 2)) /*!< Version 2.2.2. */
/*@}*/

/*! @brief VREF buffer modes. */
typedef enum _vref_buffer_mode
{
    kVREF_ModeBandgapOnly     = 0U, /*!< Bandgap enabled/standby. */
    kVREF_ModeLowPowerBuffer  = 1U, /*!< Low-power buffer mode enabled */
    kVREF_ModeHighPowerBuffer = 2U, /*!< High-power buffer mode enabled */
} vref_buffer_mode_t;

/*! @brief The description structure for the VREF module. */
typedef struct _vref_config
{
    vref_buffer_mode_t bufferMode;       /*!< Buffer mode selection */
    bool enableInternalVoltageRegulator; /*!< Provide additional supply noise rejection. */
    bool enableChopOscillator;           /*!< Enable Chop oscillator.*/
    bool enableHCBandgap;                /*!< Enable High-Accurate bandgap.*/
    bool enableCurvatureCompensation;    /*!< Enable second order curvature compensation. */
    bool enableLowPowerBuff;             /*!< Provides bias current for other peripherals.*/

} vref_config_t;

/******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Enables the clock gate and configures the VREF module according to the configuration structure.
 *
 * This function must be called before calling all other VREF driver functions, read/write registers, and
 * configurations with user-defined settings. The example below shows how to set up vref_config_t parameters
 * and how to call the VREF_Init function by passing in these parameters.
 * @code
 *    vref_config_t vrefConfig;
 *    VREF_GetDefaultConfig(VREF, &vrefConfig);
 *    vrefConfig.bufferMode = kVREF_ModeHighPowerBuffer;
 *    VREF_Init(VREF, &vrefConfig);
 * @endcode
 *
 * @param base VREF peripheral address.
 * @param config Pointer to the configuration structure.
 */
void VREF_Init(VREF_Type *base, const vref_config_t *config);

/*!
 * @brief Stops and disables the clock for the VREF module.
 *
 * This function should be called to shut down the module.
 * This is an example.
 * @code
 *    vref_config_t vrefUserConfig;
 *    VREF_GetDefaultConfig(VREF, &vrefUserConfig);
 *    VREF_Init(VREF, &vrefUserConfig);
 *    ...
 *    VREF_Deinit(VREF);
 * @endcode
 *
 * @param base VREF peripheral address.
 */
void VREF_Deinit(VREF_Type *base);

/*!
 * @brief Initializes the VREF configuration structure.
 *
 * This function initializes the VREF configuration structure to default values.
 * This is an example.
 * @code
 *    config->bufferMode = kVREF_ModeHighPowerBuffer;
 *    config->enableInternalVoltageRegulator = true;
 *    config->enableChopOscillator           = true;
 *    config->enableHCBandgap                = true;
 *    config->enableCurvatureCompensation    = true;
 *    config->enableLowPowerBuff             = true;
 * @endcode
 *
 * @param config Pointer to the initialization structure.
 */
void VREF_GetDefaultConfig(vref_config_t *config);

/* @} */

/*!
 * @name Trim functions
 * @{
 */

/*!
 * @brief Sets a TRIM value for the accurate 1.0V bandgap output.
 *
 * This function sets a TRIM value for the reference voltage. It will trim the accurate 1.0V bandgap by 0.5mV each step.
 *
 * @param base VREF peripheral address.
 * @param trimValue Value of the trim register to set the output reference voltage (maximum 0x3F (6-bit)).
 */
void VREF_SetVrefTrimVal(VREF_Type *base, uint8_t trimValue);

/*!
 * @brief Sets a TRIM value for the accurate buffered VREF output.
 *
 * This function sets a TRIM value for the reference voltage. If buffer mode be set to other values (Buf21
 * enabled), it will trim the VREF_OUT by 0.1V each step from 1.0V to 2.1V.
 *
 * @note When Buf21 is enabled, the value of UTRIM[TRIM2V1] should be ranged from 0b0000 to 0b1011 in order to trim the
 * output voltage from 1.0V to 2.1V, other values will make the VREF_OUT to default value, 1.0V.
 *
 * @param base VREF peripheral address.
 * @param trim21Value Value of the trim register to set the output reference voltage (maximum 0xF (4-bit)).
 */
void VREF_SetTrim21Val(VREF_Type *base, uint8_t trim21Value);

/*!
 * @brief Reads the trim value.
 *
 * This function gets the TRIM value from the UTRIM register. It reads UTRIM[VREFTRIM] (13:8)
 *
 * @param base VREF peripheral address.
 * @return 6-bit value of trim setting.
 */
uint8_t VREF_GetVrefTrimVal(VREF_Type *base);

/*!
 * @brief Reads the VREF 2.1V trim value.
 *
 * This function gets the TRIM value from the UTRIM register. It reads UTRIM[TRIM2V1] (3:0),
 *
 * @param base VREF peripheral address.
 * @return 4-bit value of trim setting.
 */
uint8_t VREF_GetTrim21Val(VREF_Type *base);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

#endif /* FSL_VREF_H_ */
