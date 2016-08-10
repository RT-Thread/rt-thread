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

#ifndef __FSL_CADC_HAL_H__
#define __FSL_CADC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_CADC_COUNT

/*!
 * @addtogroup cadc_hal
 * @{
 */

/******************************************************************************
 * Enumerations.
 *****************************************************************************/

/*!
 * @brief CADC status return codes.
 */
typedef enum _cadc_status
{
    kStatus_CADC_Success         = 0U, /*!< Success. */
    kStatus_CADC_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_CADC_Failed          = 2U  /*!< Execution failed. */
} cadc_status_t;

/*!
 * @brief Defines the type of enumerating ADC differential channel pair.
 *
 * Note, "cadc_diff_chn_t" and "cadc_chn_sel_mode_t" can determine to
 * select the single ADC sample channel.
 */
typedef enum _cadc_diff_chn
{
    kCAdcDiffChnANA0_1 = 0U, /*!< ConvA's Chn 0 & 1. @internal gui name="ANA 0 & 1" */
    kCAdcDiffChnANA2_3 = 1U, /*!< ConvA's Chn 2 & 3. @internal gui name="ANA 2 & 3" */
    kCAdcDiffChnANA4_5 = 2U, /*!< ConvA's Chn 4 & 5. @internal gui name="ANA 4 & 5" */
    kCAdcDiffChnANA6_7 = 3U, /*!< ConvA's Chn 6 & 7. @internal gui name="ANA 6 & 7" */
    kCAdcDiffChnANB0_1 = 4U, /*!< ConvB's Chn 0 & 1. @internal gui name="ANB 0 & 1" */
    kCAdcDiffChnANB2_3 = 5U, /*!< ConvB's Chn 2 & 3. @internal gui name="ANB 2 & 3" */
    kCAdcDiffChnANB4_5 = 6U, /*!< ConvB's Chn 4 & 5. @internal gui name="ANB 4 & 5" */
    kCAdcDiffChnANB6_7 = 7U  /*!< ConvB's Chn 6 & 7. @internal gui name="ANB 6 & 7" */
} cadc_diff_chn_t;

/*!
 * @brief Defines the type of enumerating ADC channel in a differential pair.
 *
 * Note, "cadc_diff_chn_t" and "cadc_chn_sel_mode_t" can determine
 * selecting the single ADC sample channel.
 */
typedef enum _cadc_chn_sel_mode
{
    kCAdcChnSelN = 0U, /*!< Selects a negative side channel. @internal gui name="Negative channel side" */
    kCAdcChnSelP = 1U, /*!< Selects a positive side channel. @internal gui name="Positive channel side" */
    kCAdcChnSelBoth = 2U /*!< Selects  both channels in differential modes. @internal gui name="Both - differential mode" */
} cadc_chn_sel_mode_t;

/*!
 * @brief Defines the type of enumerating ADC converter's scan mode.
 *
 * See the ADC_CTRL1[SMODE] in the chip Reference Manual for detailed information
 * about the ADC converter scan mode.
 */
typedef enum _cadc_scan_mode
{
    kCAdcScanOnceSequential      = 0U, /*!< Once (single) sequential. @internal gui name="Once sequential" */
    kCAdcScanOnceParallel        = 1U, /*!< Once parallel. @internal gui name="Once parallel" */
    kCAdcScanLoopSequential      = 2U, /*!< Loop sequential. @internal gui name="Loop sequential" */
    kCAdcScanLoopParallel        = 3U, /*!< Loop parallel. @internal gui name="Loop parallel" */
    kCAdcScanTriggeredSequential = 4U, /*!< Triggered sequential. @internal gui name="Triggered sequential" */
    kCAdcScanTriggeredParalled   = 5U  /*!< Triggered parallel (default). @internal gui name="Triggered parallel" */
} cadc_scan_mode_t;

/*!
 * @brief Defines the type to enumerate the zero crossing detection mode for each slot.
 */
typedef enum _cadc_zero_crossing_mode
{
    kCAdcZeroCrossingDisable        = 0U, /*!< Zero crossing detection disabled. @internal gui name="Disabled" */
    kCAdcZeroCrossingAtRisingEdge   = 1U, /*!< Enable for positive to negative sign change. @internal gui name="Rising edge" */
    kCAdcZeroCrossingAtFallingEdge  = 2U, /*!< Enable for negative to positive sign change. @internal gui name="Falling edge" */
    kCAdcZeroCrossingAtBothEdge     = 3U  /*!< Enable for any sign change. @internal gui name="Both edges" */
} cadc_zero_crossing_mode_t;

/*!
 * @brief Defines the type to enumerate the amplification mode for each slot.
 */
typedef enum _cadc_gain_mode
{
    kCAdcSGainBy1 = 0U, /*!< x1 amplification. @internal gui name="1" */
    kCAdcSGainBy2 = 1U, /*!< x2 amplification. @internal gui name="2" */
    kCAdcSGainBy4 = 2U  /*!< x4 amplification. @internal gui name="4" */
} cadc_gain_mode_t;

/*!
 * @brief Defines the type to enumerate the speed mode for each converter.
 *
 * These items represent the clock speed at which the ADC converter can operate.
 * Faster conversion speeds require greater current consumption.
 */
typedef enum _cadc_conv_speed_mode
{
    kCAdcConvClkLimitBy6_25MHz  = 0U, /*!< Conversion clock frequency <= 6.25 MHz;
                                            current consumption per converter = 6 mA. @internal gui name="Max 6.25 MHz" */
    kCAdcConvClkLimitBy12_5MHz  = 1U, /*!< Conversion clock frequency <= 12.5 MHz;
                                            current consumption per converter = 10.8 mA. @internal gui name="Max 12.5 MHz" */
    kCAdcConvClkLimitBy18_75MHz = 2U, /*!< Conversion clock frequency <= 18.75 MHz;
                                            current consumption per converter = 18 mA. @internal gui name="Max 18.75 MHz" */
    kCAdcConvClkLimitBy25MHz    = 3U  /*!< Conversion clock frequency <= 25 MHz;
                                            current consumption per converter = 25.2 mA. @internal gui name="Max 25 MHz" */
} cadc_conv_speed_mode_t;

/*!
 * @brief Defines the type of DMA trigger source for each converter.
 *
 * During sequential and simultaneous parallel scan modes, it selects between
 * end of scan for ConvA's scan and RDY status as the DMA source. During
 * non-simultaneous parallel scan mode it selects between end of scan for
 * converters A and B, and the RDY status as the DMA source.
 */
typedef enum _cadc_dma_trigger_src
{
    kCAdcDmaTriggeredByEndOfScan = 0U, /*!< DMA trigger source is end of scan interrupt. @internal gui name="End of scan" */
    kCAdcDmaTriggeredByConvReady = 1U  /*!< DMA trigger source is RDY status. @internal gui name="Conversion ready status" */
} cadc_dma_trigger_src_t;

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*!
 * @brief Defines a structure to configure the CyclicADC module during initialization.
 *
 * This structure holds the configuration when initializing the CyclicADC module.
 * @internal gui name="CADC configuration" id="cadcInitCfg"
 */
typedef struct CAdcControllerConfig
{
    /* Functional control. */
    bool zeroCrossingIntEnable; /*!< Global zero crossing interrupt enable. @internal gui name="Zero crossing interrupt" */
    bool lowLimitIntEnable;     /*!< Global low limit interrupt enable. @internal gui name="Low limit interrupt"*/
    bool highLimitIntEnable;    /*!< Global high limit interrupt enable. @internal gui name="High limit interrupt" */
    cadc_scan_mode_t scanMode;  /*!< ADC scan mode control. @internal gui name="Scan mode" */
    bool parallelSimultModeEnable; /*!< Parallel scans done simultaneously enable. @internal gui name="Simultaneous parallel scans" */
    cadc_dma_trigger_src_t dmaSrc; /*!< DMA trigger source. @internal gui name="DMA trigger source" */

    /* Power control. */
    bool autoStandbyEnable;     /*!< Auto standby mode enable. @internal gui name="Auto standby mode" */
    uint16_t powerUpDelayCount; /*!< Power up delay. @internal gui name="Power up delay" range="0..63" default="26" */
    bool autoPowerDownEnable;   /*!< Auto power down mode enable. @internal gui name="Auto power down mode" */
} cadc_controller_config_t;

/*!
 * @brief Defines a structure to configure each converter in the CyclicADC module.
 *
 * This structure holds the configuration for each converter in the CyclicADC module.
 * Normally, there are two converters, ConvA and ConvB in the cyclic ADC
 * module. However, each converter can be configured separately for some features.
 * @internal gui name="CADC Converter configuration" id="cadcConvCfg"
 */
typedef struct CAdcConverterConfig
{
    bool dmaEnable;     /*!< DMA enable. @internal gui name="DMA" */

    /*
    * When this bit is asserted, the current scan is stopped and no further
    * scans can start.  Any further SYNC input pulses or software trigger are
    * ignored until this bit has been cleared. After the ADC is in stop mode,
    * the results registers can be modified by the processor. Any changes to
    * the result registers in stop mode are treated as if the analog core
    * supplied the data. Therefore, limit checking, zero crossing, and
    * associated interrupts can occur when authorized.
    */
    bool stopEnable;    /*!< Stop mode enable. @internal gui name="Stop mode" */

    bool syncEnable;    /*!< Enable external sync input to trigger conversion. @internal gui name="External synchronization" */
    bool endOfScanIntEnable; /*!< End of scan interrupt enable. @internal gui name="End of scan interrupt" */

    /*
    * For Clock Divisor Select:
    * The divider circuit generates the ADC clock by dividing the system clock:
    *  - When the value is set to 0, the divisor is 2.
    *  - For all other setting values, the divisor is 1 more than the decimal
    *     value of the setting value.
    * A divider value must be chosen to prevent the ADC clock from exceeding the
    * maximum frequency.
    */
    uint16_t clkDivValue;    /*!< ADC clock divider from the bus clock. @internal gui name="Clock divider" range="0..63" */

    bool useChnInputAsVrefH; /*!< Use input channel as high reference voltage, such as AN2. @internal gui name="Input channel as high voltage reference" */
    bool useChnInputAsVrefL; /*!< Use input channel as low reference voltage, such as AN3. @internal gui name="Input channel as low voltage reference" */
    cadc_conv_speed_mode_t speedMode; /*!< ADC speed control mode. @internal gui name="Speed mode" */

    /*
    * For ConvA:
    * During sequential and parallel simultaneous scan modes, the
    * "sampleWindowCount" controls the sampling time of the first sample after
    * a scan is initiated on both converters A and B.
    * In parallel non-simultaneous mode, this field affects ConvA only.
    * In sequential scan mode, this field setting is ignored whenever
    * the channel selected for the next sample is on the other converter. In
    * other words, during a sequential scan, if a sample converts a ConvA
    * channel (ANA0-ANA7) and the next sample converts a ConvB channel
    * (ANB0-ANB7) or vice versa, this field is ignored and uses the
    * default sampling time (value 0) for the next sample.
    *
    * For ConvB:
    * During parallel non-simultaneous scan mode, the "sampleWindowCount" for
    * ConvB is used to control the sampling time of the first sample after
    * a scan is initiated. During sequential and parallel simultaneous scan
    * modes, "sampleWindowCount" is ignored and the sampling window for both
    * converters is controlled by the "sampleWindowCount" for ConvA.
    *
    * To set the value:
    * The value 0 corresponds to a sampling time of 2 ADC clocks. Each increment
    * of "sampleWindowCount" corresponds to an additional ADC clock cycle of
    * sampling time with a maximum sampling time of 9 ADC clocks.
    */
    uint16_t sampleWindowCount; /*!< Sample window count. @internal gui name="Sample window count" range="0..7" */
} cadc_converter_config_t;

/*!
 * @brief Defines a structure to configure each input channel.
 *
 * This structure holds the configuration for each input channel. In CylicADC
 * module, the input channels are handled by a differential sample.
 * However, the user can still configure the function for each channel when
 * set to operate as a single end sample.
 * @internal gui name="Channel configuration" id="cadcChnCfg"
 */
typedef struct CAdcChnConfig
{
    cadc_diff_chn_t diffChns; /*!< Select the differential channel pair. @internal gui name="Channel" */
    cadc_chn_sel_mode_t diffSelMode; /*!< Select which channel is indicated in a pair. @internal gui name="Differential mode" */
    cadc_gain_mode_t gainMode; /*!< Gain mode for each channel. @internal gui name="Gain" */
} cadc_chn_config_t;

/*!
 * @brief Defines a structure to configure each slot.
 *
 * This structure holds the configuration for each slot in a conversion sequence.
 * @internal gui name="Slot configuration" id="cadcSlotCfg"
 */
typedef struct CAdcSlotConfig
{
    bool slotDisable; /*!< Keep the slot unavailable. @internal gui name="Slot" */
    bool syncPointEnable; /*!< Sample waits for an enabled SYNC input to occur. @internal gui name="Synchronization point" */
    bool syncIntEnable; /*!< Scan interrupt enable. @internal gui name="Scan interrupt" */

    /* Select the input channel for slot. */
    cadc_diff_chn_t diffChns;  /*!< Select the differential pair. @internal gui name="Channel pair" id="diffSlotChns" */
    cadc_chn_sel_mode_t  diffSel;   /*!< Positive or negative channel in differential pair. @internal gui name="Channel select" */

    /* Event detection mode. */
    cadc_zero_crossing_mode_t zeroCrossingMode; /*!< Select zero crossing detection mode. @internal gui name="Zero cross mode" */
    uint16_t lowLimitValue; /*!< Select low limit for hardware compare. @internal gui name="Low limit compare value" range="0..32760" */
    uint16_t highLimitValue;/*!< Select high limit for hardware compare. @internal gui name="High limit compare value" range="0..32760" */
    uint16_t offsetValue;   /*!< Select sign change limit for hardware compare. @internal gui name="Offset value" range="0..32760" */
} cadc_slot_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes all ADC registers to a known state.
 *
 * The initial states of ADC registers are set as specified in the chip Reference Manual.
 *
 * @param base Register base address for the module.
 */
void CADC_HAL_Init(ADC_Type * base);

/*!
 * @brief Configures the common features in cyclic ADC module.
 *
 * This function configures the common features in cyclic ADC module. For
 * detailed items, see the "cadc_controller_config_t".
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void CADC_HAL_ConfigController(ADC_Type * base, const cadc_controller_config_t *configPtr);

/*!
 * @brief Configures the features for the converter A.
 *
 * This function configures the features for the converter A. For detailed items,
 * see the "cadc_converter_config_t".
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void CADC_HAL_ConfigConvA(ADC_Type * base, const cadc_converter_config_t *configPtr);

/*!
 * @brief Configures the features for the conversion B.
 *
 * This function configures the features for the conversion B. For detailed items,
 * see the "cadc_converter_config_t".
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void CADC_HAL_ConfigConvB(ADC_Type * base, const cadc_converter_config_t *configPtr);

/*!
 * @brief Configures the feature for the sample channel.
 *
 * This function configures the features for the sample channel. For detailed
 * items, see the "cadc_chn_config_t".
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure.
 */
void CADC_HAL_ConfigChn(ADC_Type * base, const cadc_chn_config_t *configPtr);

/*!
 * @brief Configures the features for the sample sequence slot.
 *
 * This function configures the features for the sample sequence slot. For detailed
 * items, see the "cadc_slot_config_t".
 *
 * @param base Register base address for the module.
 * @param slotIdx Sample slot index.
 * @param configPtr Pointer to configuration structure.
 */
void CADC_HAL_ConfigSeqSlot(ADC_Type * base, uint32_t slotIdx, const cadc_slot_config_t *configPtr);

/* Command. */
/*!
 * @brief Executes the command that starts conversion of the converter A.
 *
 * This function executes the command that start the conversion of the converter A
 * when using the software trigger.
 *
 * @param base Register base address for the module.
 */
static inline void CADC_HAL_SetConvAStartCmd(ADC_Type * base)
{
    ADC_BWR_CTRL1_START0(base, 1U);
}

/*!
 * @brief Executes the command that start conversion of the converter B.
 *
 * This function executes the command that start the conversion of the converter B
 * when using the software trigger.
 *
 * @param base Register base address for the module.
 */
static inline void CADC_HAL_SetConvBStartCmd(ADC_Type * base)
{
    ADC_BWR_CTRL2_START1(base, 1U);
}

/* Power switcher for converters. */
/*!
 * @brief Shuts down the conversion power manually for the converter A.
 *
 * This function shuts down the conversion power manually for the conversion A.
 * The conversion stops immediately after calling this function.
 *
 * @param base Register base address for the module.
 * @param enable Switcher to enable the feature or not.
 */
static inline void CADC_HAL_SetConvAPowerDownCmd(ADC_Type * base, bool enable)
{
    ADC_BWR_PWR_PD0(base, (uint16_t)enable);
}

/*!
 * @brief Shuts down the conversion power manually for the converter B.
 *
 * This function shots downs the conversion power manually for the conversion B.
 * The conversion stops immediately after calling this function.
 *
 * @param base Register base address for the module.
 * @param enable Switcher to enable the feature or not.
 */
static inline void CADC_HAL_SetConvBPowerDownCmd(ADC_Type * base, bool enable)
{
    ADC_BWR_PWR_PD1(base, (uint16_t)enable);
}

/* Flags. */
/* Conversion in progress. */
/*!
 * @brief Gets the flag whether the converter A is in process.
 *
 * This function gets the flag whether the converter A is in process.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvAInProgressFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_CIP0(base);
}

/*!
 * @brief Gets the flag whether the converter B is in process.
 *
 * This function gets the flag whether the converter B is in process.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvBInProgressFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_CIP1(base);
}

/* End of scan interrupt flag. */
/*!
 * @brief Gets the flag whether the converter A has finished the conversion.
 *
 * This function gets the flag whether the converter A has finished the conversion.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvAEndOfScanIntFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_EOSI0(base);
}

/*!
 * @brief Gets the flag whether the converter B has finished the conversion.
 *
 * This function gets the flag whether the converter B has finished the conversion.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvBEndOfScanIntFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_EOSI1(base);
}

/*!
 * @brief Clears the flag that finishes the conversion of the converter A.
 *
 * This function clears the flag that finishes the conversion of the converter A.
 *
 * @param base Register base address for the module.
 */
static inline void CADC_HAL_ClearConvAEndOfScanIntFlag(ADC_Type * base)
{
    ADC_BWR_STAT_EOSI0(base, 1U);
}

/*!
 * @brief Clears the flag that finishes the conversion of the converter B.
 *
 * This function clears the flag that finishes the conversion of the converter B.
 *
 * @param base Register base address for the module.
 */
static inline void CADC_HAL_ClearConvBEndOfScanIntFlag(ADC_Type * base)
{
    ADC_BWR_STAT_EOSI1(base, 1U);
}

/* Zero-crossing interrupt flag. */
/*!
 * @brief Gets the flag whether a sample zero-crossing event has happened.
 *
 * This function gets the flag whether any sample zero-crossing event has
 * happened.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetZeroCrossingIntFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_ZCI(base);
}

/*!
 * @brief Gets the flag whether a sample zero-crossing event has happened.
 *
 * This function gets the flags whether a sample zero-crossing event has
 * happened.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 * @return flags whether the event are happened for indicated slots.
 */
static inline uint16_t CADC_HAL_GetSlotZeroCrossingFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    return ( slotIdxMask & ADC_RD_ZXSTAT(base) );
}

/*!
 * @brief Clears the flags of a sample zero-crossing events.
 *
 * This function clears the flags of the sample zero-crossing events.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 */
static inline void CADC_HAL_ClearSlotZeroCrossingFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    ADC_WR_ZXSTAT(base, slotIdxMask);
}

/* Low limit interrupt flag. */
/*!
 * @brief Gets the flag whether any sample value is lower than the low limit value.
 *
 * This function gets the flag whether any sample value is lower than the low
 * limit value.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetLowLimitIntFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_LLMTI(base);
}

/*!
 * @brief Gets the flags whether a sample value is lower than the low limit value.
 *
 * This function gets the flags whether a samples value is lower than the low
 * limit value.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 * @return flags whether the event are happened for indicated slots.
 */
static inline uint16_t CADC_HAL_GetSlotLowLimitFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    return (slotIdxMask & ADC_RD_LOLIMSTAT(base));
}

/*!
 * @brief Clears the flags of the sample low limit event.
 *
 * This function clears the flags of the sample low limit event.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 */
static inline void CADC_HAL_ClearSlotLowLimitFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    ADC_WR_LOLIMSTAT(base, slotIdxMask);
}

/* High limit interrupt flag. */
/*!
 * @brief Gets the flag whether any sample value is higher than the high limit value.
 *
 * This function gets the flag whether any sample value is higher than the high
 * limit value.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetHighLimitIntFlag(ADC_Type * base)
{
    return ADC_BRD_STAT_HLMTI(base);
}

/*!
 * @brief Gets the flags whether a sample value is higher than the high limit value.
 *
 * This function gets the flags whether a sample value is higher than the
 * high limit value.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 * @return flags whether the event are happened for indicated slots.
 */
static inline uint16_t CADC_HAL_GetSlotHighLimitFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    return (slotIdxMask & ADC_RD_HILIMSTAT(base) );
}

/*!
 * @brief Clears the flags of the sample high limit event.
 *
 * This function clears the flags of the sample high limit event.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 */
static inline void CADC_HAL_ClearSlotHighLimitFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    ADC_WR_HILIMSTAT(base, slotIdxMask );
}

/*!
 * @brief Gets the flags whether a sample value is ready.
 *
 * This function gets the flags whether a sample value is ready.
 *
 * @param base Register base address for the module.
 * @param slotIdxMask Mask for indicated slots.
 * @return flags whether the event are happened for indicated slots.
 */
static inline uint16_t CADC_HAL_GetSlotReadyFlag(ADC_Type * base, uint16_t slotIdxMask)
{
    return (slotIdxMask & ADC_RD_RDY(base) );
}

/* ADC Converter's power status. */
/*!
 * @brief Gets the flag whether the converter A is powered down.
 *
 * This function gets the flag whether the converter A is powered down.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvAPowerDownFlag(ADC_Type * base)
{
    return ADC_BRD_PWR_PSTS0(base);
}

/*!
 * @brief Gets the flag whether the converter B is powered down.
 *
 * This function gets the flag whether the converter B is powered down.
 *
 * @param base Register base address for the module.
 * @return The event is asserted or not.
 */
static inline bool CADC_HAL_GetConvBPowerDownFlag(ADC_Type * base)
{
    return ADC_BRD_PWR_PSTS1(base);
}

/* Value. */
/*!
 * @brief Gets the sample value.
 *
 * This function gets the sample value. Note that the 3 LSBs are not available.
 * When the differential conversion is executed, the MSB is the sign bit.
 *
 * @param base Register base address for the module.
 * @param slotIdx Index of slot in conversion sequence.
 * @return sample value with sign bit in MSB.
 */
static inline uint16_t CADC_HAL_GetSampleValue(ADC_Type * base, uint16_t slotIdx)
{
    return ADC_RD_RSLT(base, slotIdx);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_CADC_HAL_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

