/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#ifndef __FSL_TSI_HAL_H__
#define __FSL_TSI_HAL_H__

#include <assert.h>
#include <stdint.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_TSI_COUNT

// Just for right generation of documentation
#if defined(__DOXYGEN__)
  #define  FSL_FEATURE_TSI_VERSION 1
#endif



/*!
 * @addtogroup tsi_hal
 * @{
 */


/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Error codes for the TSI driver. */
typedef enum _tsi_status
{
  kStatus_TSI_Success = 0,
  kStatus_TSI_Busy,           /*!< TSI still in progress */
  kStatus_TSI_LowPower,       /*!< TSI is in low power mode */
  kStatus_TSI_Recalibration,  /*!< TSI is under recalibration process */
  kStatus_TSI_InvalidChannel, /*!< Invalid TSI channel */
  kStatus_TSI_InvalidMode,    /*!< Invalid TSI mode */
  kStatus_TSI_Initialized,    /*!< The driver is initialized and ready to measure */
  kStatus_TSI_Error           /*!< The general driver error */
} tsi_status_t;

/*!
 * @brief TSI number of scan intervals for each electrode.
 *
 * These constants define the tsi number of consecutive scans in a TSI instance for each electrode.
 */
typedef enum _tsi_n_consecutive_scans {
    kTsiConsecutiveScansNumber_1time = 0,       /*!< once per electrode */
    kTsiConsecutiveScansNumber_2time = 1,       /*!< twice per electrode */
    kTsiConsecutiveScansNumber_3time = 2,       /*!< 3 times consecutive scan */
    kTsiConsecutiveScansNumber_4time = 3,       /*!< 4 times consecutive scan */
    kTsiConsecutiveScansNumber_5time = 4,       /*!< 5 times consecutive scan */
    kTsiConsecutiveScansNumber_6time = 5,       /*!< 6 times consecutive scan */
    kTsiConsecutiveScansNumber_7time = 6,       /*!< 7 times consecutive scan */
    kTsiConsecutiveScansNumber_8time = 7,       /*!< 8 times consecutive scan */
    kTsiConsecutiveScansNumber_9time = 8,       /*!< 9 times consecutive scan */
    kTsiConsecutiveScansNumber_10time = 9,      /*!< 10 times consecutive scan */
    kTsiConsecutiveScansNumber_11time = 10,     /*!< 11 times consecutive scan */
    kTsiConsecutiveScansNumber_12time = 11,     /*!< 12 times consecutive scan */
    kTsiConsecutiveScansNumber_13time = 12,     /*!< 13 times consecutive scan */
    kTsiConsecutiveScansNumber_14time = 13,     /*!< 14 times consecutive scan */
    kTsiConsecutiveScansNumber_15time = 14,     /*!< 15 times consecutive scan */
    kTsiConsecutiveScansNumber_16time = 15,     /*!< 16 times consecutive scan */
    kTsiConsecutiveScansNumber_17time = 16,     /*!< 17 times consecutive scan */
    kTsiConsecutiveScansNumber_18time = 17,     /*!< 18 times consecutive scan */
    kTsiConsecutiveScansNumber_19time = 18,     /*!< 19 times consecutive scan */
    kTsiConsecutiveScansNumber_20time = 19,     /*!< 20 times consecutive scan */
    kTsiConsecutiveScansNumber_21time = 20,     /*!< 21 times consecutive scan */
    kTsiConsecutiveScansNumber_22time = 21,     /*!< 22 times consecutive scan */
    kTsiConsecutiveScansNumber_23time = 22,     /*!< 23 times consecutive scan */
    kTsiConsecutiveScansNumber_24time = 23,     /*!< 24 times consecutive scan */
    kTsiConsecutiveScansNumber_25time = 24,     /*!< 25 times consecutive scan */
    kTsiConsecutiveScansNumber_26time = 25,     /*!< 26 times consecutive scan */
    kTsiConsecutiveScansNumber_27time = 26,     /*!< 27 times consecutive scan */
    kTsiConsecutiveScansNumber_28time = 27,     /*!< 28 times consecutive scan */
    kTsiConsecutiveScansNumber_29time = 28,     /*!< 29 times consecutive scan */
    kTsiConsecutiveScansNumber_30time = 29,     /*!< 30 times consecutive scan */
    kTsiConsecutiveScansNumber_31time = 30,     /*!< 31 times consecutive scan */
    kTsiConsecutiveScansNumber_32time = 31,     /*!< 32 times consecutive scan */
} tsi_n_consecutive_scans_t;

/*!
 * @brief TSI low power scan intervals limits.
 *
 * These constants define the limits of the tsi number of consecutive scans in a TSI instance.
 */
typedef struct _tsi_n_consecutive_scans_limits
{
  tsi_n_consecutive_scans_t upper;              /*!< upper limit of number of consecutive scan */
  tsi_n_consecutive_scans_t lower;              /*!< lower limit of number of consecutive scan */
}tsi_n_consecutive_scans_limits_t;


/*!
 * @brief TSI electrode oscillator prescaler.
 *
 * These constants define the tsi electrode oscillator prescaler in a TSI instance.
 */
typedef enum _tsi_electrode_osc_prescaler {
    kTsiElecOscPrescaler_1div = 0,          /*!< Electrode oscillator frequency divided by 1 */
    kTsiElecOscPrescaler_2div = 1,          /*!< Electrode oscillator frequency divided by 2 */
    kTsiElecOscPrescaler_4div = 2,          /*!< Electrode oscillator frequency divided by 4 */
    kTsiElecOscPrescaler_8div = 3,          /*!< Electrode oscillator frequency divided by 8 */
    kTsiElecOscPrescaler_16div = 4,         /*!< Electrode oscillator frequency divided by 16 */
    kTsiElecOscPrescaler_32div = 5,         /*!< Electrode oscillator frequency divided by 32 */
    kTsiElecOscPrescaler_64div = 6,         /*!< Electrode oscillator frequency divided by 64 */
    kTsiElecOscPrescaler_128div = 7,        /*!< Electrode oscillator frequency divided by 128 */
} tsi_electrode_osc_prescaler_t;






#if (FSL_FEATURE_TSI_VERSION == 1) || (FSL_FEATURE_TSI_VERSION == 2)
  #include "fsl_tsi_v2_hal_specific.h"
#elif (FSL_FEATURE_TSI_VERSION == 4)
  #include "fsl_tsi_v4_hal_specific.h"
#else
  #error The TSI version is not supported
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize hardware.
 *
 * @param   base    TSI module base address.
 *
 * @return none
 *
 * @details Initialize the peripheral to default state.
 */
void TSI_HAL_Init(TSI_Type * base);

/**
 * @brief Set configuration of hardware.
 *
 * @param   base    TSI module base address.
 * @param   config      Pointer to TSI module configuration structure.
 *
 * @return none
 *
 * @details Initialize and sets prescalers, number of scans, clocks, delta voltage
 * capacitance trimmer, reference and electrode charge current and threshold.
 */
void TSI_HAL_SetConfiguration(TSI_Type * base, tsi_config_t *config);

/**
 * @brief Recalibrate TSI hardware.
 *
 * @param   base    TSI module base address.
 * @param   config      Pointer to TSI module configuration structure.
 * @param   electrodes  The map of the electrodes.
 * @param   parLimits   Pointer to TSI module parameter limits structure.
 *
 * @return  Lowest signal
 *
 * @details This function if TSI basic module is enable, than disable him and if
 * module has enabled interrupt, disable him. Then Set prescaler,
 * electrode and reference current, number of scan and voltage rails.
 * Enable module and interrupt if is not. Better if you see implimetation
 * of this function for better understanding @ref TSI_HAL_Recalibrate.
 */
uint32_t TSI_HAL_Recalibrate(TSI_Type * base, tsi_config_t *config, const uint32_t electrodes, const tsi_parameter_limits_t *parLimits);

/*!
 * @brief Enable low power for TSI module.
 *
 * @param   base TSI module base address.
 *
 * @return  none
 *
 */
void TSI_HAL_EnableLowPower(TSI_Type * base);

/*!
* @brief Disable low power for TSI module.
*
* @param    base TSI module base address.
* @return   None.
*/
void TSI_HAL_DisableLowPower(TSI_Type * base);

/*!
* @brief Get module flag enable.
*
* @param    base TSI module base address.
* @return   State of enable module flag.
*/
static inline uint32_t TSI_HAL_IsModuleEnabled(TSI_Type * base)
{
    return TSI_BRD_GENCS_TSIEN(base);
}

/*!
* @brief Get TSI scan trigger mode.
*
* @param    base    TSI module base address.
* @return   Scan trigger mode.
*/
static inline uint32_t TSI_HAL_GetScanTriggerMode(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_STM(base);
}

/*!
* @brief Get scan in progress flag.
*
* @param    base TSI module base address.
* @return   True - if scan is in progress. False - otherwise
*/
static inline uint32_t TSI_HAL_IsScanInProgress(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_SCNIP(base);
}

/*!
* @brief Get end of scan flag.
*
* @param    base TSI module base address.
* @return   Current state of end of scan flag.
*/
static inline uint32_t TSI_HAL_GetEndOfScanFlag(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_EOSF(base);
}

/*!
* @brief Get out of range flag.
*
* @param    base TSI module base address.
* @return   State of out of range flag.
*/
static inline uint32_t TSI_HAL_GetOutOfRangeFlag(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_OUTRGF(base);
}

/*!
* @brief Get prescaler.
*
* @param    base    TSI module base address.
* @return   Prescaler value.
*/
static inline tsi_electrode_osc_prescaler_t TSI_HAL_GetPrescaler(TSI_Type * base)
{
    return (tsi_electrode_osc_prescaler_t)TSI_BRD_GENCS_PS(base);
}

/*!
* @brief Get number of scans (NSCN).
*
* @param    base    TSI module base address.
* @return   Number of scans.
*/
static inline tsi_n_consecutive_scans_t TSI_HAL_GetNumberOfScans(TSI_Type * base)
{
    return (tsi_n_consecutive_scans_t)TSI_BRD_GENCS_NSCN(base);
}

#ifdef __cplusplus
}
#endif

/*! @}*/
#endif
#endif /* __FSL_TSI_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

