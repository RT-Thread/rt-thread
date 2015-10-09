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

#ifndef __FSL_ADC16_HAL_H__
#define __FSL_ADC16_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_ADC16_COUNT

/*!
 * @addtogroup adc16_hal
 * @{
 */

/******************************************************************************
 * Enumerations.
 *****************************************************************************/

/*!
 * @brief ADC16 status return codes.
 */
typedef enum _adc16_status
{
    kStatus_ADC16_Success         = 0U, /*!< Success. */
    kStatus_ADC16_InvalidArgument = 1U, /*!< Invalid argument. */
    kStatus_ADC16_Failed          = 2U  /*!< Execution failed. */
} adc16_status_t;

#if FSL_FEATURE_ADC16_HAS_MUX_SELECT

/*!
 * @brief Defines the type of the enumerating channel multiplexer mode for each channel.
 *
 * For some ADC16 channels, there are two selections for the channel multiplexer. For
 * example, ADC0_SE4a and ADC0_SE4b are the different channels but share the same
 * channel index.
 */
typedef enum _adc16_chn_mux_mode
{
    kAdc16ChnMuxOfA = 0U, /*!< For channel with channel mux a. @internal gui name="MUX A" */
    kAdc16ChnMuxOfB = 1U, /*!< For channel with channel mux b. @internal gui name="MUX B" */
    kAdc16ChnMuxOfDefault = kAdc16ChnMuxOfA /*!< For channel without any channel mux identifier. @internal gui name="" */
} adc16_chn_mux_mode_t;
#endif /* FSL_FEATURE_ADC16_HAS_MUX_SELECT */

/*!
 * @brief Defines the type of the enumerating divider for the converter.
 */
typedef enum _adc16_clk_divider
{
    kAdc16ClkDividerOf1 = 0U, /*!< For divider 1 from the input clock to ADC16. @internal gui name="1" */
    kAdc16ClkDividerOf2 = 1U, /*!< For divider 2 from the input clock to ADC16. @internal gui name="2" */
    kAdc16ClkDividerOf4 = 2U, /*!< For divider 4 from the input clock to ADC16. @internal gui name="4" */
    kAdc16ClkDividerOf8 = 3U  /*!< For divider 8 from the input clock to ADC16. @internal gui name="8" */
} adc16_clk_divider_t;

/*!
 *@brief Defines the type of the enumerating resolution for the converter.
 */
typedef enum _adc16_resolution
{
    kAdc16ResolutionBitOf8or9 = 0U,
        /*!< 8-bit for single end sample, or 9-bit for differential sample. @internal gui name="" */
    kAdc16ResolutionBitOfSingleEndAs8 = kAdc16ResolutionBitOf8or9, /*!< 8-bit for single end sample. @internal gui name="8 bit in single mode" */
    kAdc16ResolutionBitOfDiffModeAs9 = kAdc16ResolutionBitOf8or9, /*!< 9-bit for differential sample. @internal gui name="9 bit in differential mode" */

    kAdc16ResolutionBitOf12or13 = 1U,
        /*!< 12-bit for single end sample, or 13-bit for differential sample. @internal gui name="" */
    kAdc16ResolutionBitOfSingleEndAs12 = kAdc16ResolutionBitOf12or13, /*!< 12-bit for single end sample. @internal gui name="12 bit in single mode" */
    kAdc16ResolutionBitOfDiffModeAs13 = kAdc16ResolutionBitOf12or13, /*!< 13-bit for differential sample. @internal gui name="13 bit in differential mode" */

    kAdc16ResolutionBitOf10or11 = 2U,
        /*!< 10-bit for single end sample, or 11-bit for differential sample. @internal gui name="" */
    kAdc16ResolutionBitOfSingleEndAs10 = kAdc16ResolutionBitOf10or11, /*!< 10-bit for single end sample. @internal gui name="10 bit in single mode" */
    kAdc16ResolutionBitOfDiffModeAs11 = kAdc16ResolutionBitOf10or11 /*!< 11-bit for differential sample. @internal gui name="11 bit in differential mode" */
#if (FSL_FEATURE_ADC16_MAX_RESOLUTION >= 16U)
    , kAdc16ResolutionBitOf16 = 3U,
        /*!< 16-bit for both single end sample and differential sample. @internal gui name="16-bit" */
    kAdc16ResolutionBitOfSingleEndAs16 = kAdc16ResolutionBitOf16, /*!< 16-bit for single end sample. @internal gui name="" */
    kAdc16ResolutionBitOfDiffModeAs16 = kAdc16ResolutionBitOf16 /*!< 16-bit for differential sample. @internal gui name="" */

#endif /* FSL_FEATURE_ADC16_MAX_RESOLUTION */
} adc16_resolution_t;

/*!
 * @brief Defines the type of the enumerating source of the input clock.
 */
typedef enum _adc16_clk_src_mode
{
    kAdc16ClkSrcOfBusClk  = 0U, /*!< For input as bus clock. @internal gui name="Bus clock" */
    kAdc16ClkSrcOfAltClk2 = 1U, /*!< For input as alternate clock 2 (AltClk2). @internal gui name="Alternate clock 2" */
    kAdc16ClkSrcOfAltClk  = 2U, /*!< For input as alternate clock (ALTCLK). @internal gui name="Alternate clock 1" */
    kAdc16ClkSrcOfAsynClk = 3U  /*!< For input as asynchronous clock (ADACK). @internal gui name="Asynchronous clock" */
} adc16_clk_src_mode_t;

/*!
 * @brief Defines the type of the enumerating long sample cycles.
 */
typedef enum _adc16_long_sample_cycle
{
    kAdc16LongSampleCycleOf24 = 0U, /*!< 20 extra ADCK cycles, 24 ADCK cycles total. */
    kAdc16LongSampleCycleOf16 = 1U, /*!< 12 extra ADCK cycles, 16 ADCK cycles total. */
    kAdc16LongSampleCycleOf10 = 2U, /*!< 6 extra ADCK cycles, 10 ADCK cycles total. */
    kAdc16LongSampleCycleOf6  = 3U  /*!< 2 extra ADCK cycles, 6 ADCK cycles total. */
} adc16_long_sample_cycle_t;

/*!
 * @brief Defines the type of the enumerating reference voltage source.
 */
typedef enum _adc16_ref_volt_src
{
    kAdc16RefVoltSrcOfVref = 0U, /*!< For external pins pair of VrefH and VrefL. @internal gui name="Vref pair" */
    kAdc16RefVoltSrcOfValt = 1U /*!< For alternate reference pair of ValtH and ValtL. @internal gui name="Valt pair" */
#if defined(KM34Z7_SERIES)
    ,kAdc16RefVoltSrcOfVbdg = 2U  /*!< For internal bandgap reference pair of VbdgH and VbdgL. @internal gui name="Vbdg pair" */
#endif
} adc16_ref_volt_src_t;

#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE

/*!
 * @brief Defines the type of the enumerating hardware average mode.
 */
typedef enum _adc16_hw_average_count
{
    kAdc16HwAverageCountOf4  = 0U, /*!< For hardware average with 4 samples. */
    kAdc16HwAverageCountOf8  = 1U, /*!< For hardware average with 8 samples. */
    kAdc16HwAverageCountOf16 = 2U, /*!< For hardware average with 16 samples. */
    kAdc16HwAverageCountOf32 = 3U  /*!< For hardware average with 32 samples. */
} adc16_hw_average_count_t;

#endif /* FSL_FEATURE_ADC16_HAS_HW_AVERAGE */

#if FSL_FEATURE_ADC16_HAS_PGA

/*!
 * @brief Defines the type of enumerating PGA's Gain mode.
 */
typedef enum _adc16_pga_gain
{
    kAdc16PgaGainValueOf1  = 0U, /*!< For amplifier gain of 1. @internal gui name="1" */
    kAdc16PgaGainValueOf2  = 1U, /*!< For amplifier gain of 2. @internal gui name="2" */
    kAdc16PgaGainValueOf4  = 2U, /*!< For amplifier gain of 4. @internal gui name="4" */
    kAdc16PgaGainValueOf8  = 3U, /*!< For amplifier gain of 8. @internal gui name="8" */
    kAdc16PgaGainValueOf16 = 4U, /*!< For amplifier gain of 16. @internal gui name="16" */
    kAdc16PgaGainValueOf32 = 5U, /*!< For amplifier gain of 32. @internal gui name="32" */
    kAdc16PgaGainValueOf64 = 6U  /*!< For amplifier gain of 64. @internal gui name="64" */
} adc16_pga_gain_t;

#endif /* FSL_FEATURE_ADC16_HAS_PGA */

/*!
 * @brief Defines the type of enumerating ADC16's channel index.
 */
typedef enum _adc16_chn
{
    kAdc16Chn0  = 0U,  /*!< AD0. */
    kAdc16Chn1  = 1U,  /*!< AD1. */
    kAdc16Chn2  = 2U,  /*!< AD2. */
    kAdc16Chn3  = 3U,  /*!< AD3. */
    kAdc16Chn4  = 4U,  /*!< AD4. */
    kAdc16Chn5  = 5U,  /*!< AD5. */
    kAdc16Chn6  = 6U,  /*!< AD6. */
    kAdc16Chn7  = 7U,  /*!< AD6. */
    kAdc16Chn8  = 8U,  /*!< AD8.  */
    kAdc16Chn9  = 9U,  /*!< AD9.  */
    kAdc16Chn10 = 10U, /*!< AD10. */
    kAdc16Chn11 = 11U, /*!< AD11. */
    kAdc16Chn12 = 12U, /*!< AD12. */
    kAdc16Chn13 = 13U, /*!< AD13. */
    kAdc16Chn14 = 14U, /*!< AD14. */
    kAdc16Chn15 = 15U, /*!< AD15. */
    kAdc16Chn16 = 16U, /*!< AD16. */
    kAdc16Chn17 = 17U, /*!< AD17. */
    kAdc16Chn18 = 18U, /*!< AD18. */
    kAdc16Chn19 = 19U, /*!< AD19. */
    kAdc16Chn20 = 20U, /*!< AD20. */
    kAdc16Chn21 = 21U, /*!< AD21. */
    kAdc16Chn22 = 22U, /*!< AD22. */
    kAdc16Chn23 = 23U, /*!< AD23. */
    kAdc16Chn24 = 24U, /*!< AD24. */
    kAdc16Chn25 = 25U, /*!< AD25. */
    kAdc16Chn26 = 26U, /*!< AD26. */
    kAdc16Chn27 = 27U, /*!< AD27. */
    kAdc16Chn28 = 28U, /*!< AD28. */
    kAdc16Chn29 = 29U, /*!< AD29. */
    kAdc16Chn30 = 30U, /*!< AD30. */
    kAdc16Chn31 = 31U,  /*!< AD31. */

    kAdc16Chn0d = kAdc16Chn0,  /*!< DAD0. */
    kAdc16Chn1d = kAdc16Chn1,  /*!< DAD1. */
    kAdc16Chn2d = kAdc16Chn2,  /*!< DAD2. */
    kAdc16Chn3d = kAdc16Chn3,  /*!< DAD3. */
    kAdc16Chn4a = kAdc16Chn4,  /*!< AD4a. */
    kAdc16Chn5a = kAdc16Chn5,  /*!< AD5a. */
    kAdc16Chn6a = kAdc16Chn6,  /*!< AD6a. */
    kAdc16Chn7a = kAdc16Chn7,  /*!< AD7a. */
    kAdc16Chn4b = kAdc16Chn4,  /*!< AD4b. */
    kAdc16Chn5b = kAdc16Chn5,  /*!< AD5b. */
    kAdc16Chn6b = kAdc16Chn6,  /*!< AD6b. */
    kAdc16Chn7b = kAdc16Chn7   /*!< AD7b. */

} adc16_chn_t;

/******************************************************************************
 * Definitions.
 *****************************************************************************/
/*!
 * @brief Defines the structure to configure the ADC16 channel.
 *
 * This type of variable is treated as the command to be set in ADC
 * control register, which may execute the ADC's conversion.
 */
typedef struct Adc16ChnConfig
{
    adc16_chn_t chnIdx;          /*!< Select the sample channel index. */
    bool convCompletedIntEnable; /*!< Enable the conversion complete interrupt. */
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    bool diffConvEnable;         /*!< Enable the differential conversion. */
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
} adc16_chn_config_t;

/*!
 * @brief Defines the structure to configure the ADC16's converter.
 *
 * This type of variable is treated as a group of configurations.
 * Most of the time, these configurations are a one-time
 * setting for converter sampling condition. Usually, they are set before
 * executing the ADC16 job.
 * @internal gui name="ADC configuration" id="adcCfg"
 */
typedef struct Adc16ConverterConfig
{
    bool                    lowPowerEnable; /*!< Enables low power. @internal gui name="Low power mode" id="LowPowerMode" */
    adc16_clk_divider_t     clkDividerMode; /*!< Selects the divider of input clock source. @internal gui name="Clock divider" id="ClockDivider" */
    bool                    longSampleTimeEnable; /*!< Enables the long sample time. @internal gui name="Long sample time" id="LongSampleTime" */
    adc16_resolution_t      resolution; /*!< Selects the sample resolution mode. @internal gui name="Resolution" id="Resolution" */
    adc16_clk_src_mode_t    clkSrc; /*!< Selects the input clock source to converter. @internal gui name="Clock source" id="ClockSource" */
    bool                    asyncClkEnable; /*!< Enables the asynchronous clock inside the ADC. @internal gui name="Internal async. clock" id="InternalAsyncClock" */
    bool                    highSpeedEnable; /*!< Enables the high-speed mode. @internal gui name="High speed mode" id="HighSpeed" */
    adc16_long_sample_cycle_t longSampleCycleMode; /*!< Selects the long sample mode. @internal gui name="Long sample mode" id="LongSampleMode" */
    bool                    hwTriggerEnable; /*!< Enables the hardware trigger function. @internal gui name="Hardware trigger" id="HwTrigger" */
    adc16_ref_volt_src_t    refVoltSrc; /*!< Selects the reference voltage source. @internal gui name="Voltage reference" id="ReferenceVoltage" */
    bool                    continuousConvEnable; /*!< Enables continuous conversion mode. @internal gui name="Continuous mode" id="ContinuousMode" */
#if FSL_FEATURE_ADC16_HAS_DMA
    bool                    dmaEnable; /*!< Enables the DMA for ADC converter. @internal gui name="DMA mode" id="DMASupport" */
#endif /* FSL_FEATURE_ADC16_HAS_DMA */
} adc16_converter_config_t;

/*!
 * @brief Defines the structure to configure the ADC16 internal comparator.
 * @internal gui name="HW compare configuration" id="adcHwCfg"
 */
typedef struct Adc16HwCmpConfig
{
    bool hwCmpEnable; /*!< Enables the hardware compare function. @internal gui name="Hardware compare" */
    bool hwCmpGreaterThanEnable; /*!< Configures the compare function. @internal gui name="Compare function greater than" */
    /*
     false - Configures less than the threshold. The outside and inside range are not inclusive.
             The functionality is based on the values
             placed in CV1 and CV2.
     true  - Configures greater than or equal to the threshold. The outside and inside
             ranges are inclusive. The functionality is based on the values placed in
             CV1 and CV2.
     */
    bool hwCmpRangeEnable; /*!< Configures the comparator function. @internal gui name="Compare function range" */
    /*
     Configures the comparator function to check if the conversion result of the
     input being monitored is either between or outside the range formed by
     CV1 and CV2 and determined by the value of hwCmpGreaterThanEnable.

     false - Range function disabled. Only CV1 is compared.
     true  - Range function enabled. Both CV1 and CV2 are compared.
    */
    uint16_t cmpValue1; /*!< Setting value for CV1. @internal gui name="Compare value 1" */
    uint16_t cmpValue2; /*!< Setting value for CV2. @internal gui name="Compare value 2" */
} adc16_hw_cmp_config_t;

#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE
/*!
 * @brief Defines the structure to configure the ADC16 internal accumulator.
 */
typedef struct Adc16HwAverageConfig
{
    bool hwAverageEnable; /*!< Enable the hardware average function. */
    adc16_hw_average_count_t hwAverageCountMode; /*!< Select the count of conversion result for accumulator. */
} adc16_hw_average_config_t;

#endif /* FSL_FEATURE_ADC16_HAS_HW_AVERAGE */


#if FSL_FEATURE_ADC16_HAS_PGA
/*!
 * @brief Defines the structure to configure the ADC16 programmable gain amplifier.
 * @internal gui name="ADC PGA configuration" id="adcPgaCfg"
 */
typedef struct Adc16PgaConfig
{
    bool pgaEnable; /*!< Enables the PGA's function. @internal gui name="PGA module" */
    bool runInNormalModeEnable; /*!< Enables PGA working in normal mode or low power mode by default. @internal gui name="Low power mode run" */
    adc16_pga_gain_t pgaGainMode; /*!< Selects the PGA Gain factor. @internal gui name="Gain" */

#if FSL_FEATURE_ADC16_HAS_PGA_CHOPPING
    bool pgaChoppingDisable; /*!< Disables the PGA chopping function. @internal gui name="Chopping control" */
    /*
     The PGA employs chopping to remove/reduce offset and 1/f noise and offers an
     offset measurement configuration that aids the offset calibration.
    */
#endif /* FSL_FEATURE_ADC16_HAS_PGA_CHOPPING */
#if FSL_FEATURE_ADC16_HAS_PGA_OFFSET_MEASUREMENT
    bool runInOffsetMeasurementEnable; /*!< Enables the PGA working in offset measurement mode. @internal gui name="Offset measurement mode" */
    /*
     When this feature is enabled, the PGA disconnects itself from the external
     inputs and auto-configures into offset measurement mode. With this bit set,
     run the ADC in the recommended settings and enable the maximum hardware
     averaging to get the PGA offset number. The output is the
     (PGA offset * (64+1)) for the given PGA setting.
    */
#endif /* FSL_FEATURE_ADC16_HAS_PGA_OFFSET_MEASUREMENT */
} adc16_pga_config_t;

#endif /* FSL_FEATURE_ADC16_HAS_PGA */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*! 
 * @name ADC16 HAL.
 * @{
 */
 
 
/*!
 * @brief Resets all registers into a known state for the ADC16 module.
 *
 * This function resets all registers into a known state for the ADC
 * module. This known state is the reset value indicated by the Reference
 * manual. It is strongly recommended to call this API before any other operation
 * when initializing the ADC16 module.
 *
 * @param base Register base address for the module.
 */
void ADC16_HAL_Init(ADC_Type * base);

/*!
 * @brief Configures the conversion channel for the ADC16 module.
 *
 * This function configures the channel for the ADC16 module. At any point,
 * only one of the configuration groups takes effect. The other channel group of
 * the first group (group A, 0) is only for the hardware trigger. Both software and
 * hardware trigger can be used to the first group. When in software trigger
 * mode, after the available channel is set, the conversion begins to execute.
 *
 * @param base Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @param configPtr Pointer to configuration structure.
 */
void ADC16_HAL_ConfigChn(ADC_Type * base, uint32_t chnGroup, const adc16_chn_config_t *configPtr);

/*!
 * @brief Checks whether the channel conversion is completed.
 *
 * This function checks whether the channel conversion for the ADC
 * module is completed.
 *
 * @param base Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @return Assertion of completed conversion mode.
 */
static inline bool ADC16_HAL_GetChnConvCompletedFlag(ADC_Type * base, uint32_t chnGroup)
{
    assert(chnGroup < FSL_FEATURE_ADC16_CONVERSION_CONTROL_COUNT);
    return (1U == ADC_BRD_SC1_COCO(base, chnGroup) );
}

/*!
 * @brief Configures the sampling converter for the ADC16.
 *
 * This function configures the sampling converter for the ADC16.
 * Most of the time, the configurations are a one-time setting for the
 * converter sampling condition. Usually, it is called before
 * executing the ADC16 job.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void ADC16_HAL_ConfigConverter(ADC_Type *base, const adc16_converter_config_t *configPtr);

/*!
 * @brief Configures the hardware comparator function for the ADC16.
 *
 * This function configures the hardware comparator function for the ADC16.
 * These are the settings  for the ADC16 comparator.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void ADC16_HAL_ConfigHwCompare(ADC_Type * base, const adc16_hw_cmp_config_t *configPtr);

#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE
/*!
 * @brief Configures the hardware average function for the ADC16.
 *
 * This function configures the hardware average function for the ADC16.
 * These are the settings  for the accumulator inside the ADC16.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void ADC16_HAL_ConfigHwAverage(ADC_Type * base, const adc16_hw_average_config_t *configPtr);
#endif /* FSL_FEATURE_ADC16_HAS_HW_AVERAGE */

/*!
 * @brief Gets the raw result data of channel conversion for the ADC16 module.
 *
 * This function gets the conversion result data for the ADC16 module.
 * The return value is the raw data that is not processed.
 *
 * @param base Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @return Conversion value of RAW.
 */
static inline uint16_t ADC16_HAL_GetChnConvValue(ADC_Type * base, uint32_t chnGroup )
{
    assert(chnGroup < FSL_FEATURE_ADC16_CONVERSION_CONTROL_COUNT);
    return (uint16_t)(ADC_BRD_R_D(base, chnGroup) );
}

/*!
 * @brief Checks whether the converter is active for the ADC16 module.
 *
 * This function checks  whether the converter is active for the ADC16
 * module.
 *
 * @param base Register base address for the module.
 * @return Assertion of that the converter is active.
 */
static inline bool ADC16_HAL_GetConvActiveFlag(ADC_Type * base)
{
    return (1U == ADC_BRD_SC2_ADACT(base) );
}

#if FSL_FEATURE_ADC16_HAS_MUX_SELECT
/*!
 * @brief Selects the channel mux mode for the ADC16 module.
 *
 * This function selects the channel mux mode for the ADC16 module.
 *
 * @param base Register base address for the module.
 * @param mode Selection of mode enumeration. See to "adc16_chn_mux_mode_t".
 */
static inline void ADC16_HAL_SetChnMuxMode(ADC_Type * base, adc16_chn_mux_mode_t mode)
{
    ADC_BWR_CFG2_MUXSEL(base, ((kAdc16ChnMuxOfA == mode) ? 0U : 1U) );
}
#endif /* FSL_FEATURE_ADC16_HAS_MUX_SELECT */

#if FSL_FEATURE_ADC16_HAS_CALIBRATION
/*!
 * @brief Switches to enable the hardware calibration for the ADC16 module.
 *
 * This function launches the hardware calibration for the ADC16 module.
 *
 * @param base Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC16_HAL_SetAutoCalibrationCmd(ADC_Type * base, bool enable)
{
    ADC_BWR_SC3_CAL(base, (enable ? 1U : 0U) );
}

/*!
 * @brief Gets the hardware calibration status for the ADC16 module.
 *
 * This function gets the status whether the hardware calibration is active
 * for the ADC16 module. The return value holds on as asserted during the hardware
 * calibration. Then, it is cleared and dis-asserted after the
 * calibration.
 *
 * @param base Register base address for the module.
 * @return Whether the hardware calibration is active or not.
 */
static inline bool ADC16_HAL_GetAutoCalibrationActiveFlag(ADC_Type * base)
{
    return (1U == ADC_BRD_SC3_CAL(base) );
}

/*!
 * @brief Gets the hardware calibration status for the ADC16 module.
 *
 * This function gets the status whether the hardware calibration has failed
 * for the ADC16 module. The return value  is asserted if there is anything wrong
 * with the hardware calibration.
 *
 * @param base Register base address for the module.
 * @return Whether the hardware calibration has failed or not.
 */
static inline bool ADC16_HAL_GetAutoCalibrationFailedFlag(ADC_Type * base)
{
    return (1U == ADC_BRD_SC3_CALF(base) );
}

/*!
 * @brief Gets and calculates the plus side calibration parameter from the auto calibration.
 *
 * This function  gets the values of CLP0 - CLP4 and CLPS internally,
 * accumulates them, and returns the value that can be used to be set in the PG
 * register directly. Note that this API should be called after the process of
 * auto calibration is complete.
 *
 * @param base Register base address for the module.
 * @return value that can be set into PG directly.
 */
uint16_t ADC16_HAL_GetAutoPlusSideGainValue(ADC_Type * base);

/*!
 * @brief Sets the plus side gain calibration value  for the ADC16 module.
 *
 * This function  sets the plus side gain calibration value  for the ADC16 module.
 *
 * @param base Register base address for the module.
 * @param value Setting value for plus side gain.
 */
static inline void ADC16_HAL_SetPlusSideGainValue(ADC_Type * base, uint16_t value)
{
    ADC_BWR_PG_PG(base, value);
}

#if FSL_FEATURE_ADC16_HAS_DIFF_MODE

/*!
 * @brief Gets and calculates the minus side calibration parameter from the auto calibration.
 *
 * This function gets the values of CLM0 - CLM4 and CLMS internally,
 * accumulates them, and returns the value that can be used to be set in the MG
 * register directly. Note that this API should be called after the process of
 * auto calibration is complete.
 *
 * @param base Register base address for the module.
 * @return value that can be set into MG directly.
 */
uint16_t ADC16_HAL_GetAutoMinusSideGainValue(ADC_Type * base);

/*!
 * @brief Sets the minus side gain calibration  value for the ADC16 module.
 *
 * This function sets the minus side gain calibration value for the ADC16 module.
 *
 * @param base Register base address for the module.
 * @param value Setting value for minus side gain.
 */
static inline void ADC16_HAL_SetMinusSideGainValue(ADC_Type * base, uint16_t value)
{
    ADC_BWR_MG_MG(base, value);
}

#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

#if FSL_FEATURE_ADC16_HAS_OFFSET_CORRECTION

/*!
 * @brief Gets the offset correction value for the ADC16 module.
 *
 * This function gets the offset correction value for the ADC16 module.
 * When auto calibration is executed, the OFS register holds the new value
 * generated by the calibration. It can be left as default or modified
 * according to the use case.
 *
 * @param base Register base address for the module.
 * @return current value for OFS.
 */
static inline uint16_t ADC16_HAL_GetOffsetValue(ADC_Type * base)
{
    return (uint16_t)(ADC_BRD_OFS_OFS(base) );
}

/*!
 * @brief Sets the offset correction value for the ADC16 module.
 *
 * This function sets the offset correction value for the ADC16 module. The ADC
 * offset correction register (OFS) contains the user-selected or calibration-generated
 * offset error correction value. The value in the offset correction
 * registers (OFS) is subtracted from the conversion and the result is
 * transferred into the result registers (Rn). If the result is above the
 * maximum or below the minimum result value, it is forced to the appropriate
 * limit for the current mode of operation.
 *
 * @param base Register base address for the module.
 * @param value Setting value for OFS.
 */
static inline void ADC16_HAL_SetOffsetValue(ADC_Type * base, uint16_t value)
{
    ADC_BWR_OFS_OFS(base, value);
}

#endif /* FSL_FEATURE_ADC16_HAS_OFFSET_CORRECTION */

#if FSL_FEATURE_ADC16_HAS_PGA

/*!
 * @brief Configures the PGA function for ADC16.
 *
 * This function configures the PGA function for ADC16.
 * The settings are mainly for the Programmable Gain Amplifier inside
 * the ADC16.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void ADC16_HAL_ConfigPga(ADC_Type * base, const adc16_pga_config_t *configPtr);

/*@}*/

#endif /* FSL_FEATURE_ADC16_HAS_PGA */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif

#endif /* __FSL_ADC16_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

