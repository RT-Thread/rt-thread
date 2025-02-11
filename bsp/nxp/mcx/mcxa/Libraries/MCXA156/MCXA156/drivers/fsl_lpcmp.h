/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2023-2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LPCMP_H_
#define FSL_LPCMP_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpcmp
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief LPCMP driver version 2.1.3. */
#define FSL_LPCMP_DRIVER_VERSION (MAKE_VERSION(2, 1, 3))
/*! @} */

#define LPCMP_CCR1_COUTA_CFG_MASK  (LPCMP_CCR1_COUTA_OWEN_MASK | LPCMP_CCR1_COUTA_OW_MASK)
#define LPCMP_CCR1_COUTA_CFG_SHIFT LPCMP_CCR1_COUTA_OWEN_SHIFT
#define LPCMP_CCR1_COUTA_CFG(x) \
    (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUTA_CFG_SHIFT)) & LPCMP_CCR1_COUTA_CFG_MASK)

#define LPCMP_CCR1_EVT_SEL_CFG_MASK  (LPCMP_CCR1_EVT_SEL_MASK | LPCMP_CCR1_WINDOW_CLS_MASK)
#define LPCMP_CCR1_EVT_SEL_CFG_SHIFT LPCMP_CCR1_WINDOW_CLS_SHIFT
#define LPCMP_CCR1_EVT_SEL_CFG(x) \
    (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_EVT_SEL_CFG_SHIFT)) & LPCMP_CCR1_EVT_SEL_CFG_MASK)

/*!
 * @brief LPCMP status falgs mask.
 */
enum _lpcmp_status_flags
{
    kLPCMP_OutputRisingEventFlag  = LPCMP_CSR_CFR_MASK,    /*!< Rising-edge on the comparison output has occurred. */
    kLPCMP_OutputFallingEventFlag = LPCMP_CSR_CFF_MASK,    /*!< Falling-edge on the comparison output has occurred. */
#if defined(FSL_FEATURE_LPCMP_HAS_CSR_RRF) && FSL_FEATURE_LPCMP_HAS_CSR_RRF
    kLPCMP_OutputRoundRobinEventFlag = LPCMP_CSR_RRF_MASK, /*!< Detects when any channel's last comparison result is
                                                                different from the pre-set value in trigger mode. */
#endif                                                     /* FSL_FEATURE_LPCMP_HAS_CSR_RRF */
    kLPCMP_OutputAssertEventFlag = LPCMP_CSR_COUT_MASK, /*!< Return the current value of the analog comparator output.
                                                             The flag does not support W1C. */
};

/*!
 * @brief LPCMP interrupt enable/disable mask.
 */
enum _lpcmp_interrupt_enable
{
    kLPCMP_OutputRisingInterruptEnable  = LPCMP_IER_CFR_IE_MASK, /*!< Comparator interrupt enable rising. */
    kLPCMP_OutputFallingInterruptEnable = LPCMP_IER_CFF_IE_MASK, /*!< Comparator interrupt enable falling. */
#if defined(FSL_FEATURE_LPCMP_HAS_IER_RRF_IE) && FSL_FEATURE_LPCMP_HAS_IER_RRF_IE
    kLPCMP_RoundRobinInterruptEnable = LPCMP_IER_RRF_IE_MASK,    /*!< Comparator round robin mode interrupt
                                       occurred when the comparison result changes for a given channel. */
#endif                                                           /* FSL_FEATURE_LPCMP_HAS_IER_RRF_IE */
};

/*!
 * @brief LPCMP hysteresis mode. See chip data sheet to get the actual hystersis
 *        value with each level
 */
typedef enum _lpcmp_hysteresis_mode
{
    kLPCMP_HysteresisLevel0 = 0U, /*!< The hard block output has level 0 hysteresis internally. */
    kLPCMP_HysteresisLevel1 = 1U, /*!< The hard block output has level 1 hysteresis internally. */
    kLPCMP_HysteresisLevel2 = 2U, /*!< The hard block output has level 2 hysteresis internally. */
    kLPCMP_HysteresisLevel3 = 3U, /*!< The hard block output has level 3 hysteresis internally. */
} lpcmp_hysteresis_mode_t;

/*!
 * @brief LPCMP nano mode.
 */
typedef enum _lpcmp_power_mode
{
    kLPCMP_LowSpeedPowerMode  = 0U, /*!< Low speed comparison mode is selected. */
    kLPCMP_HighSpeedPowerMode = 1U, /*!< High speed comparison mode is selected. */
    kLPCMP_NanoPowerMode      = 2U, /*!< Nano power comparator is enabled. */
} lpcmp_power_mode_t;

/*!
 * @brief Internal DAC reference voltage source.
 */
typedef enum _lpcmp_dac_reference_voltage_source
{
    kLPCMP_VrefSourceVin1 = 0U, /*!< vrefh_int is selected as resistor ladder network supply reference Vin. */
    kLPCMP_VrefSourceVin2 = 1U, /*!< vrefh_ext is selected as resistor ladder network supply reference Vin. */
} lpcmp_dac_reference_voltage_source_t;

#if defined(FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL) && FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL
/*!
 * @brief LPCMP functional mode clock source selection.
 *
 * Note: In different devices, the functional mode clock source selection is different,
 * please refer to specific device Reference Manual for details.
 */
typedef enum _lpcmp_functional_source_clock
{
    kLPCMP_FunctionalClockSource0 = 0U, /*!< Select functional mode clock source0. */
    kLPCMP_FunctionalClockSource1 = 1U, /*!< Select functional mode clock source1. */
    kLPCMP_FunctionalClockSource2 = 2U, /*!< Select functional mode clock source2. */
    kLPCMP_FunctionalClockSource3 = 3U, /*!< Select functional mode clock source3. */
} lpcmp_functional_source_clock_t;
#endif                                  /* FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL */

#if defined(FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL) && FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL
/*!
 * @brief Set the COUTA signal value when the window is closed.
 */
typedef enum _lpcmp_couta_signal
{
    kLPCMP_COUTASignalNoSet = 0U, /*!< NO set the COUTA signal value when the window is closed. */
    kLPCMP_COUTASignalLow   = 1U, /*!< Set COUTA signal low(0) when the window is closed. */
    kLPCMP_COUTASignalHigh  = 3U, /*!< Set COUTA signal high(1) when the window is closed. */
} lpcmp_couta_signal_t;

/*!
 * @brief Set COUT event, which can close the active window in window mode.
 */
typedef enum _lpcmp_close_window_event
{
    kLPCMP_CLoseWindowEventNoSet      = 0U, /*!< No Set COUT event, which can close the active window in window mode. */
    kLPCMP_CloseWindowEventRisingEdge = 1U, /*!< Set rising edge COUT signal as COUT event. */
    kLPCMP_CloseWindowEventFallingEdge = 3U, /*!< Set falling edge COUT signal as COUT event. */
    kLPCMP_CLoseWindowEventBothEdge    = 5U, /*!< Set both rising and falling edge COUT signal as COUT event. */
} lpcmp_close_window_event_t;
#endif                                       /* FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL */

#if defined(FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE) && FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE
/*!
 * @brief LPCMP round robin mode fixed mux port.
 */
typedef enum _lpcmp_roundrobin_fixedmuxport
{
    kLPCMP_FixedPlusMuxPort  = 0U, /*!< Fixed plus mux port. */
    kLPCMP_FixedMinusMuxPort = 1U, /*!< Fixed minus mux port. */
} lpcmp_roundrobin_fixedmuxport_t;

/*!
 * @brief LPCMP round robin mode clock source selection.
 *
 * Note: In different devices,the round robin mode clock source selection is different,
 * please refer to the specific device Reference Manual for details.
 */
typedef enum _lpcmp_roundrobin_clock_source
{
    kLPCMP_RoundRobinClockSource0 = 0U, /*!< Select roundrobin mode clock source0. */
    kLPCMP_RoundRobinClockSource1 = 1U, /*!< Select roundrobin mode clock source1. */
    kLPCMP_RoundRobinClockSource2 = 2U, /*!< Select roundrobin mode clock source2. */
    kLPCMP_RoundRobinClockSource3 = 3U, /*!< Select roundrobin mode clock source3. */
} lpcmp_roundrobin_clock_source_t;

/*!
 * @brief LPCMP round robin mode trigger source.
 */
typedef enum _lpcmp_roundrobin_trigger_source
{
    kLPCMP_TriggerSourceExternally = 0U, /*!< Select external trigger source. */
    kLPCMP_TriggerSourceInternally = 1U, /*!< Select internal trigger source. */
} lpcmp_roundrobin_trigger_source_t;
#endif                                   /* FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE */

/*!
 * @brief Configure the filter.
 */
typedef struct _lpcmp_filter_config
{
    bool enableSample;          /*!< Decide whether to use the external SAMPLE as a sampling clock input. */
    uint8_t filterSampleCount;  /*!< Filter Sample Count. Available range is 1-7; 0 disables the filter. */
    uint8_t filterSamplePeriod; /*!< Filter Sample Period. The divider to the bus clock. Available range is 0-255. The
                            sampling clock must be at least 4 times slower than the system clock to the comparator.
                            So if enableSample is "false", filterSamplePeriod should be set greater than 4.*/
} lpcmp_filter_config_t;

/*!
 * @brief configure the internal DAC.
 */
typedef struct _lpcmp_dac_config
{
    bool enableLowPowerMode;                                     /*!< Decide whether to enable DAC low power mode. */
    lpcmp_dac_reference_voltage_source_t referenceVoltageSource; /*!< Internal DAC supply voltage reference source. */
    uint8_t DACValue; /*!< Value for the DAC Output Voltage. Different devices has different available range,
                           for specific values, please refer to the reference manual.*/
} lpcmp_dac_config_t;

/*!
 * @brief Configures the comparator.
 */
typedef struct _lpcmp_config
{
#if !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN)
    bool enableStopMode; /*!< Decide whether to enable the comparator when in STOP modes. */
#endif /* !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) */

    bool enableOutputPin;     /*!< Decide whether to enable the comparator is available in selected pin. */
    bool useUnfilteredOutput; /*!< Decide whether to use unfiltered output. */
    bool enableInvertOutput;  /*!< Decide whether to inverts the comparator output. */
    lpcmp_hysteresis_mode_t hysteresisMode;                /*!< LPCMP hysteresis mode. */
    lpcmp_power_mode_t powerMode;                          /*!< LPCMP power mode. */
#if defined(FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL) && FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL
    lpcmp_functional_source_clock_t functionalSourceClock; /*!< Select LPCMP functional mode clock source. */
#endif                                                     /* FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL */
} lpcmp_config_t;

#if defined(FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL) && FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL
/*!
 * @brief Configure the window mode control.
 */
typedef struct _lpcmp_window_control_config
{
    bool enableInvertWindowSignal;    /*!< True: enable invert window signal, False: disable invert window signal. */
    lpcmp_couta_signal_t COUTASignal; /*!< Decide whether to define the COUTA signal value when the window is closed. */
    lpcmp_close_window_event_t closeWindowEvent; /*!< Decide whether to select COUT event signal edge defines
                                                      a COUT event to close window. */
} lpcmp_window_control_config_t;
#endif                                           /* FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL */

#if defined(FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE) && FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE
/*!
 * @brief Configure the round robin mode.
 */
typedef struct _lpcmp_roundrobin_config
{
    uint8_t initDelayModules;   /*!< Comparator and DAC initialization delay modulus, See Reference Manual and DataSheet
                                     for specific value. */
    uint8_t sampleClockNumbers; /*!< Specify the number of the round robin clock cycles(0~3) to wait after scanning the
                                     active channel before sampling the channel's comparison result. */
    uint8_t channelSampleNumbers; /*!< Specify the number of samples for one channel, note that channelSampleNumbers
                                       must not smaller than sampleTimeThreshhold. */
    uint8_t sampleTimeThreshhold; /*!< Specify that for one channel, when (sampleTimeThreshhold + 1) sample results are
                                       "1",the final result is "1", otherwise the final result is "0", note that the
                                       sampleTimeThreshhold must not be larger than channelSampleNumbers. */
    lpcmp_roundrobin_clock_source_t roundrobinClockSource;     /*!< Decide which clock source to
                                                        choose in round robin mode. */
    lpcmp_roundrobin_trigger_source_t roundrobinTriggerSource; /*!< Decide which trigger source to
                                                        choose in round robin mode. */
    lpcmp_roundrobin_fixedmuxport_t fixedMuxPort;              /*!< Decide which mux port to choose as
                                                        fixed channel in round robin mode. */
    uint8_t fixedChannel;       /*!< Indicate which channel of the fixed mux port is used in round robin mode. */
    uint8_t checkerChannelMask; /*!< Indicate which channel of the non-fixed mux port to check its voltage value in
                                     round robin mode, for example, if checkerChannelMask set to 0x11U means select
                                     channel 0 and channel 4 as checker channel.*/
} lpcmp_roundrobin_config_t;
#endif                          /* FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and configuration
 * @{
 */

/*!
 * @brief Initialize the LPCMP
 *
 * This function initializes the LPCMP module. The operations included are:
 * - Enabling the clock for LPCMP module.
 * - Configuring the comparator.
 * - Enabling the LPCMP module.
 * Note: For some devices, multiple LPCMP instance share the same clock gate. In this case, to enable the clock for
 * any instance enables all the LPCMPs. Check the chip reference manual for the clock assignment of the LPCMP.
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer to "lpcmp_config_t" structure.
 */
void LPCMP_Init(LPCMP_Type *base, const lpcmp_config_t *config);

/*!
 * @brief De-initializes the LPCMP module.
 *
 * This function de-initializes the LPCMP module. The operations included are:
 * - Disabling the LPCMP module.
 * - Disabling the clock for LPCMP module.
 *
 * This function disables the clock for the LPCMP.
 * Note: For some devices, multiple LPCMP instance shares the same clock gate. In this case, before disabling the
 * clock for the LPCMP, ensure that all the LPCMP instances are not used.
 *
 * @param base LPCMP peripheral base address.
 */
void LPCMP_Deinit(LPCMP_Type *base);

/*!
 * @brief Gets an available pre-defined settings for the comparator's configuration.
 *
 * This function initializes the comparator configuration structure to these default values:
 * @code
 *   config->enableStopMode      = false;
 *   config->enableOutputPin     = false;
 *   config->useUnfilteredOutput = false;
 *   config->enableInvertOutput  = false;
 *   config->hysteresisMode      = kLPCMP_HysteresisLevel0;
 *   config->powerMode           = kLPCMP_LowSpeedPowerMode;
 *   config->functionalSourceClock = kLPCMP_FunctionalClockSource0;
 * @endcode
 * @param config Pointer to "lpcmp_config_t" structure.
 */
void LPCMP_GetDefaultConfig(lpcmp_config_t *config);

/*!
 * @brief Enable/Disable LPCMP module.
 *
 * @param base LPCMP peripheral base address.
 * @param enable "true" means enable the module, and "false" means disable the module.
 */
static inline void LPCMP_Enable(LPCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR0 |= LPCMP_CCR0_CMP_EN_MASK;
    }
    else
    {
        base->CCR0 &= ~LPCMP_CCR0_CMP_EN_MASK;
    }
}

/*!
 * @brief Select the input channels for LPCMP. This function determines which input
 *        is selected for the negative and positive mux.
 *
 * @param base LPCMP peripheral base address.
 * @param positiveChannel Positive side input channel number. Available range is 0-7.
 * @param negativeChannel Negative side input channel number. Available range is 0-7.
 */
void LPCMP_SetInputChannels(LPCMP_Type *base, uint32_t positiveChannel, uint32_t negativeChannel);

/*!
 * @brief Enables/disables the DMA request for rising/falling events.
 *        Normally, the LPCMP generates a CPU interrupt if there is a rising/falling event. When
 *        DMA support is enabled and the rising/falling interrupt is enabled , the rising/falling
 *        event forces a DMA transfer request rather than a CPU interrupt instead.
 *
 * @param base LPCMP peripheral base address.
 * @param enable "true" means enable DMA support, and "false" means disable DMA support.
 */
static inline void LPCMP_EnableDMA(LPCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR1 |= LPCMP_CCR1_DMA_EN_MASK;
    }
    else
    {
        base->CCR1 &= ~LPCMP_CCR1_DMA_EN_MASK;
    }
}

/*!
 * @brief Configures the filter.
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer to "lpcmp_filter_config_t" structure.
 */
void LPCMP_SetFilterConfig(LPCMP_Type *base, const lpcmp_filter_config_t *config);

/*!
 * @brief Configure the internal DAC module.
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer to "lpcmp_dac_config_t" structure. If config is "NULL", disable internal DAC.
 */
void LPCMP_SetDACConfig(LPCMP_Type *base, const lpcmp_dac_config_t *config);

/*!
 * @brief Enable the interrupts.
 *
 * @param base LPCMP peripheral base address.
 * @param mask Mask value for interrupts. See "_lpcmp_interrupt_enable".
 */
static inline void LPCMP_EnableInterrupts(LPCMP_Type *base, uint32_t mask)
{
    base->IER |= mask;
}

/*!
 * @brief Disable the interrupts.
 *
 * @param base LPCMP peripheral base address.
 * @param mask Mask value for interrupts. See "_lpcmp_interrupt_enable".
 */
static inline void LPCMP_DisableInterrupts(LPCMP_Type *base, uint32_t mask)
{
    base->IER &= ~mask;
}

/*!
 * @brief Get the LPCMP status flags.
 *
 * @param base LPCMP peripheral base address.
 *
 * @return Mask value for the asserted flags. See "_lpcmp_status_flags".
 */
static inline uint32_t LPCMP_GetStatusFlags(LPCMP_Type *base)
{
    return base->CSR;
}

/*!
 * @brief Clear the LPCMP status flags
 *
 * @param base LPCMP peripheral base address.
 * @param mask Mask value for the flags. See "_lpcmp_status_flags".
 */
static inline void LPCMP_ClearStatusFlags(LPCMP_Type *base, uint32_t mask)
{
    base->CSR = mask;
}

/*! @} */

/*!
 * @name Window mode
 * @{
 */

/*!
 * @brief Enable/Disable window mode.When any windowed mode is active, COUTA is clocked by
 *        the bus clock whenever WINDOW = 1. The last latched value is held when WINDOW = 0.
 *        The optionally inverted comparator output COUT_RAW is sampled on every bus clock
 *        when WINDOW=1 to generate COUTA.
 *
 * @param base LPCMP peripheral base address.
 * @param enable "true" means enable window mode, and "false" means disable window mode.
 */
static inline void LPCMP_EnableWindowMode(LPCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR1 |= LPCMP_CCR1_WINDOW_EN_MASK;
    }
    else
    {
        base->CCR1 &= ~LPCMP_CCR1_WINDOW_EN_MASK;
    }
}

#if defined(FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL) && FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL
/*!
 * @brief Configure the window control, users can use this API to implement operations on the window,
 * such as inverting the window signal, setting the window closing event(only valid in windowing mode),
 * and setting the COUTA signal after the window is closed(only valid in windowing mode).
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer "lpcmp_window_control_config_t" structure.
 */
void LPCMP_SetWindowControl(LPCMP_Type *base, const lpcmp_window_control_config_t *config);
#endif /* FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL */

/*! @} */

#if defined(FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE) && FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE
/*!
 * @name RoundRobin mode
 * @{
 */

/*!
 * @brief Configure the roundrobin mode.
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer "lpcmp_roundrobin_config_t" structure.
 */
void LPCMP_SetRoundRobinConfig(LPCMP_Type *base, const lpcmp_roundrobin_config_t *config);

/*!
 * brief Configure the roundrobin internal timer reload value.
 *
 * param base LPCMP peripheral base address.
 * param value RoundRobin internal timer reload value, allowed range:0x0UL-0xFFFFFFFUL.
 */
void LPCMP_SetRoundRobinInternalTimer(LPCMP_Type *base, uint32_t value);

/*!
 * @brief Enable/Disable roundrobin mode.
 *
 * @param base LPCMP peripheral base address.
 * @param enable "true" means enable roundrobin mode, and "false" means disable roundrobin mode.
 */
static inline void LPCMP_EnableRoundRobinMode(LPCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->RRCR0 |= LPCMP_RRCR0_RR_EN_MASK;
    }
    else
    {
        base->RRCR0 &= ~LPCMP_RRCR0_RR_EN_MASK;
    }
}

/*!
 * @brief Enable/Disable roundrobin internal timer, note that this function is only valid
 * when using the internal trigger source.
 *
 * @param base LPCMP peripheral base address.
 * @param enable "true" means enable roundrobin internal timer, and "false" means disable roundrobin internal timer.
 */
static inline void LPCMP_EnableRoundRobinInternalTimer(LPCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->RRCR2 |= LPCMP_RRCR2_RR_TIMER_EN_MASK;
    }
    else
    {
        base->RRCR2 &= ~LPCMP_RRCR2_RR_TIMER_EN_MASK;
    }
}

/*!
 * @brief Set preset value for all channels, users can set all channels' preset vaule through this API,
 * for example, if the mask set to 0x03U means channel0 and channel2's preset value set to 1U and other
 * channels' preset value set to 0U.
 *
 * @param base LPCMP peripheral base address.
 * @param mask Mask of channel index.
 */
static inline void LPCMP_SetPreSetValue(LPCMP_Type *base, uint8_t mask)
{
    base->RRCSR = (uint32_t)mask;
}

/*!
 * @brief Get comparison results for all channels, users can get all channels' comparison
 * results through this API.
 *
 * @param base LPCMP peripheral base address.
 * @return return All channels' comparison result.
 */
static inline uint8_t LPCMP_GetComparisonResult(LPCMP_Type *base)
{
    return (uint8_t)base->RRCSR;
}

/*!
 * @brief Clear input changed flags for single channel or multiple channels, users can clear
 * input changed flag of a single channel or multiple channels through this API, for example,
 * if the mask set to 0x03U means clear channel0 and channel2's input changed flags.
 *
 * @param base LPCMP peripheral base address.
 * @param mask Mask of channel index.
 */
static inline void LPCMP_ClearInputChangedFlags(LPCMP_Type *base, uint8_t mask)
{
    base->RRSR = (uint32_t)mask;
}

/*!
 * @brief Get input changed flags for all channels, Users can get all channels' input changed
 * flags through this API.
 *
 * @param base LPCMP peripheral base address.
 * @return return All channels' changed flag.
 */
static inline uint8_t LPCMP_GetInputChangedFlags(LPCMP_Type *base)
{
    return (uint8_t)base->RRSR;
}

/*! @} */

#endif /* FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_LPCMP_H_ */
