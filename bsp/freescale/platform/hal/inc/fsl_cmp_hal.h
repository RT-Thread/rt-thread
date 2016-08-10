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

#ifndef __FSL_CMP_HAL_H__
#define __FSL_CMP_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_CMP_COUNT

/*!
 * @addtogroup cmp_hal
 * @{
 */

/******************************************************************************
 * Enumerations
 *****************************************************************************/

/*!
 * @brief CMP status return codes.
 */
typedef enum _cmp_status 
{
    kStatus_CMP_Success         = 0U, /*!< Success */
    kStatus_CMP_InvalidArgument = 1U, /*!< Invalid argument existed */
    kStatus_CMP_Failed          = 2U  /*!< Execution failed */
} cmp_status_t;

/*!
 * @brief Defines the selections of the hard block hysteresis control level.
 * 
 * The hysteresis control level indicates the smallest window between the two
 * inputs when asserting the change of output. See the chip
 * Data Sheet for detailed electrical characteristics. Generally, the lower level
 * represents the smaller window.
 */
typedef enum _cmp_hystersis_mode
{
    kCmpHystersisOfLevel0 = 0U, /*!< Level 0 */
    kCmpHystersisOfLevel1 = 1U, /*!< Level 1 */
    kCmpHystersisOfLevel2 = 2U, /*!< Level 2 */
    kCmpHystersisOfLevel3 = 3U  /*!< Level 3 */
} cmp_hystersis_mode_t;

/*!
 * @brief Defines the selections of the filter sample counter.
 * 
 * The selection item represents the number of consecutive samples that must
 * agree prior to the comparator output filter accepting a new output state.
 */
typedef enum _cmp_filter_counter_mode_t
{
    kCmpFilterCountSampleOf0 = 0U, /*!< Disable the filter */
    kCmpFilterCountSampleOf1 = 1U, /*!< One sample must agree */
    kCmpFilterCountSampleOf2 = 2U, /*!< 2 consecutive samples must agree */
    kCmpFilterCountSampleOf3 = 3U, /*!< 3 consecutive samples must agree */
    kCmpFilterCountSampleOf4 = 4U, /*!< 4 consecutive samples must agree */
    kCmpFilterCountSampleOf5 = 5U, /*!< 5 consecutive samples must agree */
    kCmpFilterCountSampleOf6 = 6U, /*!< 6 consecutive samples must agree */
    kCmpFilterCountSampleOf7 = 7U  /*!< 7 consecutive samples must agree */ 
} cmp_filter_counter_mode_t;

/*!
 * @brief Defines the selections of reference voltage source for the internal DAC.
 */
typedef enum _cmp_dac_ref_volt_src_mode_t
{
    kCmpDacRefVoltSrcOf1 = 0U, /*!< Vin1 - Vref_out */
    kCmpDacRefVoltSrcOf2 = 1U  /*!< Vin2 - Vdd */
} cmp_dac_ref_volt_src_mode_t;

/*!
 * @brief Define the selection of the CMP channel mux.
 */
typedef enum _cmp_chn_mux_mode_t
{
    kCmpInputChn0 = 0U, /*!< Comparator input channel 0. @internal gui name="Input 0" */
    kCmpInputChn1 = 1U, /*!< Comparator input channel 1. @internal gui name="Input 1" */
    kCmpInputChn2 = 2U, /*!< Comparator input channel 2. @internal gui name="Input 2" */
    kCmpInputChn3 = 3U, /*!< Comparator input channel 3. @internal gui name="Input 3" */
    kCmpInputChn4 = 4U, /*!< Comparator input channel 4. @internal gui name="Input 4" */
    kCmpInputChn5 = 5U, /*!< Comparator input channel 5. @internal gui name="Input 5" */
    kCmpInputChn6 = 6U, /*!< Comparator input channel 6. @internal gui name="Input 6" */
    kCmpInputChn7 = 7U, /*!< Comparator input channel 7. @internal gui name="Input 7" */
    kCmpInputChnDac = kCmpInputChn7 /*!< Comparator input channel 7. @internal gui name="DAC output" */
} cmp_chn_mux_mode_t;

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*!
 * @brief Defines a structure for configuring the comparator in the CMP module.
 *
 * This structure holds the configuration for the comparator
 * inside the CMP module. With the configuration, the CMP can be set as a
 * basic comparator without additional features. 
 * @internal gui name="Basic configuration" id="cmpCfg"
 */
typedef struct CmpComparatorConfig
{
    cmp_hystersis_mode_t hystersisMode; /*!< Set the hysteresis level. @internal gui name="Hysteresis level" id="HysteresisLevel" */
    bool pinoutEnable; /*!< Enable outputting the CMPO to pin. @internal gui name="Out pin" id="OutPin" */
    bool pinoutUnfilteredEnable; /*!< Enable outputting unfiltered result to CMPO. @internal gui name="Unfiltered output pin" id="UnfilteredOutPinEnable" */
    bool invertEnable; /*!< Enable inverting the comparator's result. @internal gui name="Output inversion" id="InvertLogic" */
    bool highSpeedEnable; /*!< Enable working in speed mode. @internal gui name="High speed" id="HighSpeed" */
#if FSL_FEATURE_CMP_HAS_DMA
    bool dmaEnable; /*!< Enable using DMA. @internal gui name="DMA" id="DMA" */
#endif /* FSL_FEATURE_CMP_HAS_DMA */
    bool risingIntEnable; /*!< Enable using CMPO rising interrupt. @internal gui name="Rising interrupt" id="RisingInt" */
    bool fallingIntEnable; /*!< Enable using CMPO falling interrupt. @internal gui name="Falling interrupt" id="FallingInt" */
    cmp_chn_mux_mode_t plusChnMux; /*!< Set the Plus side input to comparator. @internal gui name="Positive channel" id="PositiveChannel" default="0" */
    cmp_chn_mux_mode_t minusChnMux; /*!< Set the Minus side input to comparator. @internal gui name="Negative channel" id="NegativeChannel" default="1" */
#if FSL_FEATURE_CMP_HAS_TRIGGER_MODE
    bool triggerEnable; /*!< Enable triggering mode. @internal gui name="Trigger mode" id="TriggerMode" */
#endif /* FSL_FEATURE_CMP_HAS_TRIGGER_MODE */
    
} cmp_comparator_config_t;

/*!
* @brief Definition selections of the sample and filter modes in the CMP module.
*
* Comparator sample/filter is available in several modes. Use the enumeration
* to identify the comparator's status:
*
* kCmpContinuousMode - Continuous Mode:
        Both window control and filter blocks are completely bypassed. The
        comparator output is updated continuously. 
* kCmpSampleWithNoFilteredMode - Sample, Non-Filtered Mode:
        Window control is completely bypassed. The comparator output  is
        sampled whenever a rising-edge is detected on the filter block clock
        input. The filter clock prescaler can be configured as a
        divider from the bus clock.
* kCmpSampleWithFilteredMode - Sample, Filtered Mode:
        Similar to "Sample, Non-Filtered Mode", but the filter is active in
        this mode. The filter counter value also becomes
        configurable.
* kCmpWindowedMode - Windowed Mode:
        In Windowed Mode, only output of analog comparator is passed when
        the WINDOW signal is high. The last latched value is held when the WINDOW
        signal is low.
* kCmpWindowedFilteredMode - Window/Filtered Mode:
        This is a complex mode because it uses both window and filtering
        features. It also has the highest latency of all modes. This can be 
        approximated to up to 1 bus clock synchronization in the window function
        + ( ( filter counter * filter prescaler ) + 1) bus clock for the
        filter function.
*/
typedef enum _cmp_sample_filter_mode
{
    kCmpContinuousMode = 0U, /*!< Continuous Mode */
    kCmpSampleWithNoFilteredMode = 1U, /*!< Sample, Non-Filtered Mode */
    kCmpSampleWithFilteredMode = 2U, /*!< Sample, Filtered Mode */
    kCmpWindowedMode = 3U, /*!< Window Mode */
    kCmpWindowedFilteredMode = 4U /*!< Window/Filtered Mode */
} cmp_sample_filter_mode_t;

/*!
* @brief Defines a structure to configure the window/filter in CMP module.
*
* This structure holds the configuration for the window/filter inside
* the CMP module. With the configuration, the CMP module can operate in 
* advanced mode.
* @internal gui name="Filter configuration" id="filterCfg"
*/
typedef struct CmpSampleFilterConfig
{
    cmp_sample_filter_mode_t workMode; /*!< Sample/Filter's work mode. @internal gui name="Work mode" id="WorkMode" */
    bool useExtSampleOrWindow; /*!< Switcher to use external WINDOW/SAMPLE signal. @internal gui name="External sample/window signal" id="ExtSampleWinSignal" */
    uint8_t filterClkDiv; /*!< Filter's prescaler which divides from the bus clock. @internal gui name="Filter divider" id="FiltClkDiv" */
    cmp_filter_counter_mode_t filterCount; /*!< Sample count for filter. See "cmp_filter_counter_mode_t". @internal gui name="Filter sample count" id="FiltCnt" */
} cmp_sample_filter_config_t;

/*!
 * @brief Defines a structure to configure the internal DAC in the CMP module.
 *
 * This structure holds the configuration for the DAC
 * inside the CMP module. With the configuration, the internal DAC
 * provides a reference voltage level and is chosen as the CMP input.
 * @internal gui name="DAC configuration" id="dacCfg"
 */
typedef struct CmpDacConfig
{
    bool dacEnable; /*!< Enable the internal 6-bit DAC. @internal gui name="D/A converter" id="DacEnable" */
    cmp_dac_ref_volt_src_mode_t refVoltSrcMode; /*!< Select the reference voltage source for internal DAC. @internal gui name="Input reference" id="Reference" */
    uint8_t dacValue; /*!< Set the value for internal DAC. @internal gui name="Output level value" id="DacValue" range="0..63" */
} cmp_dac_config_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Resets the CMP registers to a known state.
 *
 * This function resets the CMP registers to a known state. This state is
 * defined in the chip Reference Manual, which is power on reset value.
 *
 * @param base Register base address for the module.
 */
void CMP_HAL_Init(CMP_Type * base);

/*!
 * @brief Configures the CMP comparator function.
 *
 * This function configures the CMP comparator function.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure. See to "cmp_comparator_config_t".
 */
void CMP_HAL_ConfigComparator(CMP_Type * base, const cmp_comparator_config_t *configPtr);

/*!
 * @brief Configures the CMP DAC function.
 *
 * This function configures the CMP DAC function.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure. See to "cmp_dac_config_t".
 */
void CMP_HAL_ConfigDacChn(CMP_Type * base, const cmp_dac_config_t *configPtr);

/*!
 * @brief Configures the CMP sample or the filter function.
 *
 * This function configures the CMP sample or filter function.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure. See to "cmp_sample_filter_config_t".
 */
void CMP_HAL_ConfigSampleFilter(CMP_Type * base, const cmp_sample_filter_config_t *configPtr);

/*!
 * @brief Enables the comparator in the CMP module.
 *
 * This function enables the comparator in the CMP module. The analog 
 * comparator is the core component in the CMP module. Only when it is enabled, all
 * other functions for advanced features are meaningful.
 *
 * @param base Register base address for the module.
 */
static inline void CMP_HAL_Enable(CMP_Type * base)
{
    CMP_BWR_CR1_EN(base, 1U);
}

/*!
 * @brief Disables the comparator in the CMP module.
 *
 * This function disables the comparator in the CMP module. The analog 
 * comparator is the core component in the CMP module. When it is disabled, it
 * remains in the off state and consumes no power. 
 *
 * @param base Register base address for the module.
 */
static inline void CMP_HAL_Disable(CMP_Type * base)
{
    CMP_BWR_CR1_EN(base, 0U);
}

/*!
 * @brief Gets the comparator logic output in the CMP module.
 *
 * This function gets the comparator logic output in the CMP module.
 * It returns the current value of the analog comparator output. The value
 * is reset to 0 and read as de-asserted value when the CMP module is
 * disabled. When setting to invert mode, the comparator logic output is
 * inverted as well.
 *
 * @param base Register base address for the module.
 * @return The logic output is assert or not.
 */
static inline bool CMP_HAL_GetOutputLogic(CMP_Type * base)
{
    return ( 1U == CMP_BRD_SCR_COUT(base) );
}

/*!
 * @brief Gets the logic output falling edge event in the CMP module.
 *
 * This function gets the logic output falling edge event in the CMP module.
 * It detects a falling-edge on COUT and returns the asserted state when the
 * falling-edge on COUT has occurred.
 *
 * @param base Register base address for the module.
 * @return The falling-edge on COUT has occurred or not.
 */
static inline bool CMP_HAL_GetOutputFallingFlag(CMP_Type * base)
{
    return ( 1U == CMP_BRD_SCR_CFF(base) );
}

/*!
 * @brief Clears the logic output falling edge event in the CMP module.
 *
 * This function clears the logic output falling edge event in the CMP module.
 *
 * @param base Register base address for the module.
 */
static inline void CMP_HAL_ClearOutputFallingFlag(CMP_Type * base)
{
    CMP_BWR_SCR_CFF(base, 1U);
}

/*!
 * @brief Gets the logic output rising edge event in the CMP module.
 *
 * This function gets the logic output rising edge event in the CMP module.
 * It detects a rising-edge on COUT and returns the asserted state when the
 * rising-edge on COUT has occurred.
 *
 * @param base Register base address for the module.
 * @return The rising-edge on COUT has occurred or not.
 */
static inline bool CMP_HAL_GetOutputRisingFlag(CMP_Type * base)
{
    return ( 1U == CMP_BRD_SCR_CFR(base) );
}

/*!
 * @brief Clears the logic output rising edge event in the CMP module.
 *
 * This function clears the logic output rising edge event in the CMP module.
 *
 * @param base Register base address for the module.
 */
static inline void CMP_HAL_ClearOutputRisingFlag(CMP_Type * base)
{
    CMP_BWR_SCR_CFR(base, 1U);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_CMP_HAL_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

