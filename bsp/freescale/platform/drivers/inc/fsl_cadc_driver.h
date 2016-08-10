/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#ifndef __FSL_CADC_DRIVER_H__
#define __FSL_CADC_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_cadc_hal.h"
#if FSL_FEATURE_SOC_CADC_COUNT

/*!
 * @addtogroup cadc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Defines the type of enumerating ADC converter ID.
 */
typedef enum _cadc_conv_id
{
    kCAdcConvA = 0U,/*!< ID for ADC converter A. */
    kCAdcConvB = 1U /*!< ID for ADC converter B. */
} cadc_conv_id_t;

/*!
 * @brief Defines types for an enumerating event.
 */
typedef enum _cadc_flag
{
    /* Converter events. */
    kCAdcConvInProgress = 0U,   /*!< Conversion in progress for each converter. */
    kCAdcConvEndOfScanInt = 1U, /*!< End of scan interrupt. */
    kCAdcConvPowerDown = 2U,      /*!< The converter is powered Down. */

    /* Global events. */
    kCAdcZeroCrossingInt = 3U,  /*!< Zero crossing interrupt. */
    kCAdcLowLimitInt = 4U,      /*!< Low limit interrupt. */
    kCAdcHighLimitInt = 5U,     /*!< High limit interrupt. */

    /* Slot events. */
    kCAdcSlotReady = 6U,            /*!< Sample is ready to be read. */
    kCAdcSlotLowLimitEvent = 7U,    /*!< Low limit event for each slot. */
    kCAdcSlotHighLimitEvent = 8U,   /*!< High limit event for each slot. */
    kCAdcSlotCrossingEvent = 9U     /*!< Zero crossing event for each slot. */
} cadc_flag_t;

/*! @brief Table of base addresses for ADC instances. */
extern ADC_Type * g_cadcBaseAddr[];

/*! @brief Table to save ADC IRQ enumeration numbers defined in the CMSIS header file. */
extern IRQn_Type g_cadcErrIrqId[ADC_INSTANCE_COUNT];
extern IRQn_Type g_cadcConvAIrqId[ADC_INSTANCE_COUNT];
extern IRQn_Type g_cadcConvBIrqId[ADC_INSTANCE_COUNT];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name CADC Driver
 * @{
 */

/*!
 * @brief Populates the user configuration structure for the CyclicADC common settings.
 *
 * This function populates the cadc_user_config_t structure with
 * default settings, which are used in polling mode for ADC conversion.
 * These settings are:
 *
 * .zeroCrossingIntEnable = false;
 * .lowLimitIntEnable = false;
 * .highLimitIntEnable = false;
 * .scanMode = kCAdcScanOnceSequential;
 * .parallelSimultModeEnable = false;
 * .dmaSrc = kCAdcDmaTriggeredByEndOfScan;
 * .autoStandbyEnable = false;
 * .powerUpDelayCount = 0x2AU;
 * .autoPowerDownEnable = false;
 *
 * @param userConfigPtr Pointer to structure of "cadc_controller_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_StructInitUserConfigDefault(cadc_controller_config_t *userConfigPtr);

/*!
 * @brief Initializes the CyclicADC module for a global configuration.
 *
 * This function configures the CyclicADC module for the global configuration
 * which is shared by all converters.
 *
 * @param instance Instance ID number.
 * @param userConfigPtr Pointer to structure of "cadc_controller_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_Init(uint32_t instance, const cadc_controller_config_t *userConfigPtr);

/*!
 * @brief De-initializes the CyclicADC module.
 *
 * This function shuts down the CyclicADC module and disables related IRQs.
 *
 * @param instance Instance ID number.
 * @return Execution status.
 */
cadc_status_t CADC_DRV_Deinit(uint32_t instance);

/*!
 * @brief Populates the user configuration structure for each converter.
 *
 * This function populates the cadc_conv_config_t structure with
 * default settings, which are used in polling mode for ADC conversion.
 * These settings are:
 *
 * .dmaEnable = false;
 * .stopEnable = false;
 * .syncEnable = false;
 * .endOfScanIntEnable = false;
 * .clkDivValue = 0x3FU;
 * .useChnInputAsVrefH = false;
 * .useChnInputAsVrefL = false;
 * .speedMode = kCAdcConvClkLimitBy25MHz;
 * .sampleWindowCount = 0U;
 *
 * @param configPtr Pointer to structure of "cadc_converter_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_StructInitConvConfigDefault(cadc_converter_config_t *configPtr);

/*!
 * @brief Configures each converter in the CyclicADC module.
 *
 * This function configures each converter in the CyclicADC module. However, when
 * the multiple converters are operating simultaneously, the converter settings
 * are interrelated. For more information, see the appropriate device
 * reference manual.
 *
 * @param instance Instance ID number.
 * @param convId Converter ID. See "cadc_conv_id_t".
 * @param configPtr Pointer to configure structure. See "cadc_converter_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_ConfigConverter(
    uint32_t instance, cadc_conv_id_t convId, const cadc_converter_config_t *configPtr);

/*!
 * @brief Configures the input channel for ADC conversion.
 *
 * This function configures the input channel for ADC conversion. The CyclicADC
 * module input channels are organized in pairs. The configuration can
 * be set for each channel in the pair.
 *
 * @param instance Instance ID number.
 * @param configPtr Pointer to configure structure. See "cadc_chn_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_ConfigSampleChn(uint32_t instance, const cadc_chn_config_t *configPtr);

/*!
 * @brief Configures each slot for the ADC conversion sequence.
 *
 * This function configures each slot in the ADC conversion sequence. ADC conversion
 * sequence is the basic execution unit in the CyclicADC module. However, the
 * sequence should be configured slot-by-slot. The end of the sequence is a
 * slot that is configured as disabled.
 *
 * @param instance Instance ID number.
 * @param slotIdx Indicated slot number, available in range of 0 - 15.
 * @param configPtr Pointer to configure structure. See "cadc_slot_config_t".
 * @return Execution status.
 */
cadc_status_t CADC_DRV_ConfigSeqSlot(
    uint32_t instance, uint32_t slotIdx, const cadc_slot_config_t *configPtr);

/*!
 * @brief Triggers the ADC conversion sequence by software.
 *
 * This function triggers the ADC conversion by executing a software command. It
 * starts the conversion if no other SYNC input (hardware trigger) is needed.
 *
 * @param instance Instance ID number.
 * @param convId Indicated converter. See "cadc_conv_id_t".
 */
void CADC_DRV_SoftTriggerConv(uint32_t instance, cadc_conv_id_t convId);

/*!
 * @brief Reads the conversion value and returns an absolute value.
 *
 * This function reads the conversion value from each slot in a conversion sequence.
 * The return value is the absolute value without being signed.
 *
 * @param instance Instance ID number.
 * @param slotIdx Indicated slot number, available in range of 0 - 15.
 * @return The conversion value.
 */
uint16_t CADC_DRV_GetSeqSlotConvValue(uint32_t instance, uint32_t slotIdx);

/*!
 * @brief Gets the global event flag.
 *
 * This function gets the global flag of the CyclicADC module.
 *
 * @param instance Instance ID number.
 * @param flag Indicated event. See "cadc_flag_t".
 * @return Assertion of indicated event.
 */
bool CADC_DRV_GetFlag(uint32_t instance, cadc_flag_t flag);

/*!
 * @brief Clears the global event flag.
 *
 * This function clears the global event flag of the CyclicADC module.
 *
 * @param instance Instance ID number.
 * @param flag Indicated event. See "cadc_flag_t".
 */
void CADC_DRV_ClearFlag(uint32_t instance, cadc_flag_t flag);

/*!
 * @brief Gets the flag for each converter event.
 *
 * This function gets the flag for each converter event.
 *
 * @param instance Instance ID number.
 * @param convId Indicated converter.
 * @param flag Indicated event. See "cadc_flag_t".
 * @return Assertion of indicated event.
 */
bool CADC_DRV_GetConvFlag(uint32_t instance, cadc_conv_id_t convId, cadc_flag_t flag);

/*!
 * @brief Clears the flag for each converter event.
 *
 * This function clears the flag for each converter event.
 *
 * @param instance Instance ID number.
 * @param convId Indicated converter.
 * @param flag Indicated event. See  "cadc_flag_t".
 */
void CADC_DRV_ClearConvFlag(uint32_t instance, cadc_conv_id_t convId, cadc_flag_t flag);

/*!
 * @brief Gets the flag for each slot event.
 *
 * This function gets the flag for each slot event in the conversion in
 * sequence.
 *
 * @param instance Instance ID number.
 * @param slotIdxMask Indicated slot number's mask.
 * @param flag Indicated event. See "cadc_flag_t".
 * @return Assertion of indicated event.
 */
uint16_t CADC_DRV_GetSlotFlag(uint32_t instance, uint16_t slotIdxMask, cadc_flag_t flag);

/*!
 * @brief Clears the flag for each slot event.
 *
 * This function clears the flag for each slot event in the conversion in
 * sequence.
 *
 * @param instance Instance ID number.
 * @param slotIdxMask Indicated slot number's mask.
 * @param flag Indicated event. See "cadc_flag_t".
 */
void CADC_DRV_ClearSlotFlag(uint32_t instance, uint16_t slotIdxMask, cadc_flag_t flag);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_CADC_DRIVER_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

