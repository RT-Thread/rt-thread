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

#ifndef __FSL_ADC16_DRIVER_H__
#define __FSL_ADC16_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_adc16_hal.h"
#if FSL_FEATURE_SOC_ADC16_COUNT

/*!
 * @addtogroup adc16_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if FSL_FEATURE_ADC16_HAS_CALIBRATION

/*!
 * @brief Defines the structure to configure the ADC16 module calibration.
 *
 * This structure holds the configuration for the ADC16 module internal calibration.
 */
typedef struct Adc16CalibrationParam
{
    /* PG. */
    uint16_t plusSideGainValue; /*!< Plus-side gain value. */

    /* MG. */
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    uint16_t minusSideGainValue; /*!< Minus-side gain value. */
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

    /* Offset value. */
#if FSL_FEATURE_ADC16_HAS_OFFSET_CORRECTION
    uint16_t offsetValue; /*!< Offset error from correction value. */
#endif /* FSL_FEATURE_ADC16_HAS_OFFSET_CORRECTION */

} adc16_calibration_param_t;

#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

/*!
 * @brief Defines the type of event flags.
 */
typedef enum _adc16_flag_t
{
    kAdcConvActiveFlag = 0U, /*!< Indicates if a conversion or hardware averaging is in progress. */
#if FSL_FEATURE_ADC16_HAS_CALIBRATION
    kAdcCalibrationFailedFlag = 1U, /*!< Indicates if the calibration failed. */
    kAdcCalibrationActiveFlag = 2U, /*!< Indicates if the calibration is activated.*/
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
    kAdcChnConvCompleteFlag = 3U /*!< Indicates if the channel group A is ready.*/
} adc16_flag_t;

/*! @brief Table of base addresses for ADC16 instances. */
extern ADC_Type * const g_adcBase[];

/*! @brief Table to save ADC IRQ enum numbers defined in the CMSIS header file. */
extern const IRQn_Type g_adcIrqId[ADC_INSTANCE_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * API
 *****************************************************************************/

#if FSL_FEATURE_ADC16_HAS_CALIBRATION
/*!
 * @brief Gets the calibration parameters by auto calibration.
 *
 * This function executes auto calibration and fetches the calibration parameters
 * that are kept in the "adc16_calibration_param_t" type variable.
 *
 * @param instance ADC16 instance ID.
 * @param paramPtr Pointer to the parameter structure. See the "adc16_calibration_param_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_GetAutoCalibrationParam(uint32_t instance, adc16_calibration_param_t *paramPtr);

/*!
 * @brief Sets the calibration parameters.
 *
 * This function sets the calibration parameters.
 *
 * @param instance ADC16 instance ID.
 * @param paramPtr Pointer to parameter structure. See the "adc16_calibration_param_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_SetCalibrationParam(uint32_t instance, const adc16_calibration_param_t *paramPtr);

#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

/*!
 * @brief Fills the initial user configuration by default for a one-time trigger mode.
 *
 * This function fills the initial user configuration by default for a one-time
 * trigger mode. Calling the initialization function with the filled parameter
 * configures the ADC module work as one-time trigger mode. The settings are:
 * \n
 *
 * \li.lowPowerEnable = true;
 * \li.clkDividerMode = kAdc16ClkDividerOf8;
 * \li.longSampleTimeEnable = true;
 * \li.resolutionMode = kAdc16ResolutionBitOfSingleEndAs12;
 * \li.clkSrc = kAdc16ClkSrcOfAsynClk
 * \li.asyncClkEnable = true;
 * \li.highSpeedEnable = false;
 * \li.longSampleCycleMode = kAdc16LongSampleCycleOf24;
 * \li.hwTriggerEnable = false;
 * \li.refVoltSrc = kAdcRefVoltSrcOfVref;
 * \li.continuousConvEnable = false;
 * \li.dmaEnable = false;
 *
 * @param userConfigPtr Pointer to the user configuration structure. See the "adc16_converter_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_StructInitUserConfigDefault(adc16_converter_config_t *userConfigPtr);

/*!
 * @brief Initializes the ADC module converter.
 *
 * This function initializes the converter in the ADC module.
 *
 * @param instance ADC16 instance ID.
 * @param userConfigPtr Pointer to the initialization structure. See the "adc16_converter_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_Init(uint32_t instance, const adc16_converter_config_t *userConfigPtr);

/*!
 * @brief De-initializes the ADC module converter.
 *
 * This function de-initializes and gates the ADC module. When ADC is no longer used, calling
 * this API function shuts down the device to reduce the power consumption.
 *
 * @param instance ADC16 instance ID.
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_Deinit(uint32_t instance);

/*!
 * @brief Configures the hardware compare feature.
 *
 * This function configures the hardware compare feature with indicated configuration.
 *
 * @param instance ADC16 instance ID.
 * @param configPtr Pointer to configuration structure. See the "adc16_hw_cmp_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_ConfigHwCompare(uint32_t instance, const adc16_hw_cmp_config_t *configPtr);

#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE

/*!
 * @brief Configures the hardware averaging feature.
 *
 * This function configures the hardware averaging feature with an indicated configuration.
 *
 * @param instance ADC16 instance ID.
 * @param configPtr Pointer to configuration structure. See to "adc16_hw_average_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_ConfigHwAverage(uint32_t instance, const adc16_hw_average_config_t *configPtr);

#endif /* FSL_FEATURE_ADC16_HAS_HW_AVERAGE */

#if FSL_FEATURE_ADC16_HAS_PGA

/*!
 * @brief Configures the Programmable Gain Amplifier (PGA) feature.
 *
 * This function configures the PGA feature.
 *
 * @param instance ADC16 instance ID.
 * @param configPtr Pointer to configuration structure. See the "adc16_pga_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_ConfigPga(uint32_t instance, const adc16_pga_config_t *configPtr);

#endif /* FSL_FEATURE_ADC16_HAS_PGA */

#if FSL_FEATURE_ADC16_HAS_MUX_SELECT
/*!
 * @brief Switches the channel mux.
 *
 * This function switches the channel mux. For some channels share the same
 * channel index with different channel mux, like AD4a and AD4b, could be switched
 * to each group by calling this function.
 *
 * @param instance ADC16 instance ID.
 * @param chnMuxMode Setting channel mux. See the "adc16_chn_mux_mode_t".
 */
void ADC16_DRV_SetChnMux(uint32_t instance, adc16_chn_mux_mode_t chnMuxMode);
#endif /* FSL_FEATURE_ADC16_HAS_MUX_SELECT */

/*!
 * @brief Configure the conversion channel by software.
 *
 * This function configures the conversion channel. When the ADC16 module has
 * been initialized by enabling the software trigger (disable hardware trigger),
 * calling this API triggers the conversion.
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup Selection of the configuration group.
 * @param configPtr Pointer to configuration structure. See the "adc16_chn_config_t".
 * @return Execution status.
 */
adc16_status_t ADC16_DRV_ConfigConvChn(uint32_t instance, uint32_t chnGroup, const adc16_chn_config_t *configPtr);

/*!
 * @brief Waits for the latest conversion to be complete.
 *
 * This function waits for the latest conversion to be complete. When
 * triggering  the conversion by configuring the available channel, the converter is
 * launched. This API function should be called to wait for the conversion to be
 * complete when no interrupt or DMA mode is used for the ADC16 module. After the
 * waiting period, the available data from the conversion result are fetched.
 * The complete flag is not cleared until the result data is read.
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup Selection of configuration group.
 */
void ADC16_DRV_WaitConvDone(uint32_t instance, uint32_t chnGroup);

/*!
 * @brief Pauses the current conversion by software.
 *
 * This function pauses the current conversion setting by software.
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup Selection of configuration group.
 */
void ADC16_DRV_PauseConv(uint32_t instance, uint32_t chnGroup);

/*!
 * @brief Gets the latest conversion value with no format.
 *
 * This function gets the conversion value from the ADC16 module.
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup Selection of configuration group.
 * @return Unformatted conversion value.
 */
uint16_t ADC16_DRV_GetConvValueRAW(uint32_t instance, uint32_t chnGroup);

/*!
 * @brief Gets the latest conversion value with signed.
 *
 * This function gets the conversion value from the ADC16 module with signed.
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup Selection of configuration group.
 * @return Signed conversion value.
 */
int16_t ADC16_DRV_GetConvValueSigned(uint32_t instance, uint32_t chnGroup);

/*!
 * @brief Gets the event status of the ADC16 module.
 *
 * This function gets the event status of the ADC16 converter.
 * If the event is asserted, it returns "true". Otherwise, it is "false".
 *
 * @param instance ADC16 instance ID.
 * @param flag Indicated event.
 * @return Assertion of event flag.
 */
bool ADC16_DRV_GetConvFlag(uint32_t instance, adc16_flag_t flag);

/*!
 * @brief Gets the event status of each channel group.
 *
 * This function gets the event status of each channel group.
 * If the event is asserted, it returns "true". Otherwise, it is "false".
 *
 * @param instance ADC16 instance ID.
 * @param chnGroup ADC16 channel group number.
 * @param flag Indicated event.
 * @return Assertion of event flag.
 */
bool ADC16_DRV_GetChnFlag(uint32_t instance, uint32_t chnGroup, adc16_flag_t flag);

#if defined(__cplusplus)
}
#endif


/*!
 *@}
 */

#endif
#endif /* __FSL_ADC16_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

