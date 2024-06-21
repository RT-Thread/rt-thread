/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_QDC_H_
#define FSL_QDC_H_

#include "fsl_common.h"

/*!
 * @addtogroup qdc
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FSL_QDC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))

/*!
 * @brief Interrupt enable/disable mask.
 */
enum _qdc_interrupt_enable
{
    kQDC_HOMETransitionInterruptEnable  = (1U << 0U), /*!< HOME interrupt enable. */
    kQDC_INDEXPulseInterruptEnable      = (1U << 1U), /*!< INDEX pulse interrupt enable. */
    kQDC_WatchdogTimeoutInterruptEnable = (1U << 2U), /*!< Watchdog timeout interrupt enable. */
    kQDC_PositionCompareInerruptEnable  = (1U << 3U), /*!< Position compare interrupt enable. */
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    kQDC_SimultBothPhaseChangeInterruptEnable =
        (1U << 4U), /*!< Simultaneous PHASEA and PHASEB change interrupt enable. */
#endif
    kQDC_PositionRollOverInterruptEnable  = (1U << 5U), /*!< Roll-over interrupt enable. */
    kQDC_PositionRollUnderInterruptEnable = (1U << 6U), /*!< Roll-under interrupt enable. */
};

/*!
 * @brief Status flag mask.
 *
 * These flags indicate the counter's events.
 */
enum _qdc_status_flags
{
    kQDC_HOMETransitionFlag  = (1U << 0U), /*!< HOME signal transition interrupt request. */
    kQDC_INDEXPulseFlag      = (1U << 1U), /*!< INDEX Pulse Interrupt Request. */
    kQDC_WatchdogTimeoutFlag = (1U << 2U), /*!< Watchdog timeout interrupt request. */
    kQDC_PositionCompareFlag = (1U << 3U), /*!< Position compare interrupt request. */
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    kQDC_SimultBothPhaseChangeFlag = (1U << 4U), /*!< Simultaneous PHASEA and PHASEB change interrupt request. */
#endif
    kQDC_PositionRollOverFlag   = (1U << 5U), /*!< Roll-over interrupt request. */
    kQDC_PositionRollUnderFlag  = (1U << 6U), /*!< Roll-under interrupt request. */
    kQDC_LastCountDirectionFlag = (1U << 7U), /*!< Last count was in the up direction, or the down direction. */
};

/*!
 * @brief Signal status flag mask.
 *
 * These flags indicate the counter's signal.
 */
enum _qdc_signal_status_flags
{
    kQDC_RawHOMEStatusFlag       = QDC_IMR_HOME_MASK,  /*!< Raw HOME input. */
    kQDC_RawINDEXStatusFlag      = QDC_IMR_INDEX_MASK, /*!< Raw INDEX input. */
    kQDC_RawPHBStatusFlag        = QDC_IMR_PHB_MASK,   /*!< Raw PHASEB input. */
    kQDC_RawPHAEXStatusFlag      = QDC_IMR_PHA_MASK,   /*!< Raw PHASEA input. */
    kQDC_FilteredHOMEStatusFlag  = QDC_IMR_FHOM_MASK,  /*!< The filtered version of HOME input. */
    kQDC_FilteredINDEXStatusFlag = QDC_IMR_FIND_MASK,  /*!< The filtered version of INDEX input. */
    kQDC_FilteredPHBStatusFlag   = QDC_IMR_FPHB_MASK,  /*!< The filtered version of PHASEB input. */
    kQDC_FilteredPHAStatusFlag   = QDC_IMR_FPHA_MASK,  /*!< The filtered version of PHASEA input. */
};

/*!
 * @brief Define HOME signal's trigger mode.
 *
 * The QDC would count the trigger from HOME signal line.
 */
typedef enum _qdc_home_trigger_mode
{
    kQDC_HOMETriggerDisabled = 0U, /*!< HOME signal's trigger is disabled. */
    kQDC_HOMETriggerOnRisingEdge,  /*!< Use positive going edge-to-trigger initialization of position counters. */
    kQDC_HOMETriggerOnFallingEdge, /*!< Use negative going edge-to-trigger initialization of position counters. */
} qdc_home_trigger_mode_t;

/*!
 * @brief Define INDEX signal's trigger mode.
 *
 * The QDC would count the trigger from INDEX signal line.
 */
typedef enum _qdc_index_trigger_mode
{
    kQDC_INDEXTriggerDisabled = 0U, /*!< INDEX signal's trigger is disabled. */
    kQDC_INDEXTriggerOnRisingEdge,  /*!< Use positive going edge-to-trigger initialization of position counters. */
    kQDC_INDEXTriggerOnFallingEdge, /*!< Use negative going edge-to-trigger initialization of position counters. */
} qdc_index_trigger_mode_t;

/*!
 * @brief Define type for decoder work mode.
 *
 * The normal work mode uses the standard quadrature decoder with PHASEA and PHASEB. When in signal phase count mode,
 * a positive transition of the PHASEA input generates a count signal while the PHASEB input and the reverse direction
 * control the counter direction. If the reverse direction is not enabled, PHASEB = 0 means counting up and PHASEB = 1
 * means counting down. Otherwise, the direction is reversed.
 */
typedef enum _qdc_decoder_work_mode
{
    kQDC_DecoderWorkAsNormalMode = 0U,      /*!< Use standard quadrature decoder with PHASEA and PHASEB. */
    kQDC_DecoderWorkAsSignalPhaseCountMode, /*!< PHASEA input generates a count signal while PHASEB input control the
                                               direction. */
} qdc_decoder_work_mode_t;

/*!
 * @brief Define type for the condition of POSMATCH pulses.
 */
typedef enum _qdc_position_match_mode
{
    kQDC_POSMATCHOnPositionCounterEqualToComapreValue = 0U, /*!< POSMATCH pulses when a match occurs between the
                                                               position counters (POS) and the compare value (COMP). */
    kQDC_POSMATCHOnReadingAnyPositionCounter, /*!< POSMATCH pulses when any position counter register is read. */
} qdc_position_match_mode_t;

/*!
 * @brief Define type for determining how the revolution counter (REV) is incremented/decremented.
 */
typedef enum _qdc_revolution_count_condition
{
    kQDC_RevolutionCountOnINDEXPulse = 0U, /*!< Use INDEX pulse to increment/decrement revolution counter. */
    kQDC_RevolutionCountOnRollOverModulus, /*!< Use modulus counting roll-over/under to increment/decrement revolution
                                              counter. */
} qdc_revolution_count_condition_t;

/*!
 * @brief Define type for direction of self test generated signal.
 */
typedef enum _qdc_self_test_direction
{
    kQDC_SelfTestDirectionPositive = 0U, /*!< Self test generates the signal in positive direction. */
    kQDC_SelfTestDirectionNegative,      /*!< Self test generates the signal in negative direction. */
} qdc_self_test_direction_t;

#if (defined(FSL_FEATURE_QDC_HAS_CTRL3) && FSL_FEATURE_QDC_HAS_CTRL3)
/*!
 * @brief Define prescaler value for clock in CTRL3.
 *
 * The clock is prescaled by a value of 2^PRSC which means that the prescaler logic
 * can divide the clock by a minimum of 1 and a maximum of 32,768.
 */
typedef enum _qdc_prescaler
{
    kQDC_ClockDiv1     = 0,
    kQDC_ClockDiv2     = 1,
    kQDC_ClockDiv4     = 2,
    kQDC_ClockDiv8     = 3,
    kQDC_ClockDiv16    = 4,
    kQDC_ClockDiv32    = 5,
    kQDC_ClockDiv64    = 6,
    kQDC_ClockDiv128   = 7,
    kQDC_ClockDiv256   = 8,
    kQDC_ClockDiv512   = 9,
    kQDC_ClockDiv1024  = 10,
    kQDC_ClockDiv2048  = 11,
    kQDC_ClockDiv4096  = 12,
    kQDC_ClockDiv8192  = 13,
    kQDC_ClockDiv16384 = 14,
    kQDC_ClockDiv32768 = 15,
} qdc_prescaler_t;
#endif

#if (defined(FSL_FEATURE_QDC_HAS_FILT_PRSC) && FSL_FEATURE_QDC_HAS_FILT_PRSC)
/*!
 * @brief Define input filter prescaler value.
 *
 * The input filter prescaler value is to prescale the IPBus clock.
 * (Frequency of FILT clock) = (Frequency of IPBus clock) / 2^FILT_PRSC.
 */
typedef enum _qdc_filter_prescaler
{
    kQDC_FilterPrescalerDiv1   = 0U, /*!< Input filter prescaler is 1. */
    kQDC_FilterPrescalerDiv2   = 1U, /*!< Input filter prescaler is 2. */
    kQDC_FilterPrescalerDiv4   = 2U, /*!< Input filter prescaler is 4. */
    kQDC_FilterPrescalerDiv8   = 3U, /*!< Input filter prescaler is 8. */
    kQDC_FilterPrescalerDiv16  = 4U, /*!< Input filter prescaler is 16. */
    kQDC_FilterPrescalerDiv32  = 5U, /*!< Input filter prescaler is 32. */
    kQDC_FilterPrescalerDiv64  = 6U, /*!< Input filter prescaler is 64. */
    kQDC_FilterPrescalerDiv128 = 7U, /*!< Input filter prescaler is 128. */
} qdc_filter_prescaler_t;
#endif

/*!
 * @brief Define user configuration structure for QDC module.
 */
typedef struct _qdc_config
{
    /* Basic counter. */
    bool enableReverseDirection;             /*!< Enable reverse direction counting. */
    qdc_decoder_work_mode_t decoderWorkMode; /*!< Enable signal phase count mode. */

    /* Signal detection. */
    qdc_home_trigger_mode_t HOMETriggerMode;   /*!< Enable HOME to initialize position counters. */
    qdc_index_trigger_mode_t INDEXTriggerMode; /*!< Enable INDEX to initialize position counters. */
    bool enableTRIGGERClearPositionCounter;    /*!< Clear POSD, REV, UPOS and LPOS on rising edge of TRIGGER, or not. */
    bool enableTRIGGERClearHoldPositionCounter; /*!< Enable update of hold registers on rising edge of TRIGGER, or not.
                                                 */

    /* Watchdog. */
    bool enableWatchdog;           /*!< Enable the watchdog to detect if the target is moving or not. */
    uint16_t watchdogTimeoutValue; /*!< Watchdog timeout count value. It stores the timeout count for the quadrature
                                        decoder module watchdog timer. This field is only available when
                                        "enableWatchdog" = true. The available value is a 16-bit unsigned number.*/

#if (defined(FSL_FEATURE_QDC_HAS_FILT_PRSC) && FSL_FEATURE_QDC_HAS_FILT_PRSC)
    qdc_filter_prescaler_t filterPrescaler; /*!< Input filter prescaler. */
#endif

    /* Filter for PHASEA, PHASEB, INDEX and HOME. */
    uint16_t filterCount; /*!< Input Filter Sample Count. This value should be chosen to reduce the probability of
                               noisy samples causing an incorrect transition to be recognized. The value represent the
                               number of consecutive samples that must agree prior to the input filter accepting an
                               input transition. A value of 0x0 represents 3 samples. A value of 0x7 represents 10
                               samples. The Available range is 0 - 7.*/
    uint16_t filterSamplePeriod; /*!< Input Filter Sample Period. This value should be set such that the sampling period
                                      is larger than the period of the expected noise. This value represents the
                                      sampling period (in IPBus clock cycles) of the decoder input signals.
                                      The available range is 0 - 255. */

    /* Position compare. */
    qdc_position_match_mode_t positionMatchMode; /*!< The condition of POSMATCH pulses. */
    uint32_t positionCompareValue;               /*!< Position compare value. The available value is a 32-bit number.*/

    /* Modulus counting. */
    qdc_revolution_count_condition_t revolutionCountCondition; /*!< Revolution Counter Modulus Enable. */
    bool enableModuloCountMode;                                /*!< Enable Modulo Counting. */
    uint32_t positionModulusValue; /*!< Position modulus value. This value would be available only when
                                        "enableModuloCountMode" = true. The available value is a 32-bit number. */
    uint32_t positionInitialValue; /*!< Position initial value. The available value is a 32-bit number. */

#if (defined(FSL_FEATURE_QDC_HAS_CTRL3) && FSL_FEATURE_QDC_HAS_CTRL3)
    /* Prescaler. */
    bool enablePeriodMeasurementFunction; /*!< Enable period measurement function. */
    qdc_prescaler_t prescalerValue;       /*!< The value of prescaler. */
#endif
} qdc_config_t;

/*!
 * @brief Define configuration structure for self test module.
 *
 * The self test module provides a quadrature test signal to the inputs of the quadrature decoder module.
 * This is a factory test feature. It is also useful to customers' software development and testing.
 */
typedef struct _qdc_self_test_config
{
    qdc_self_test_direction_t signalDirection; /*!< Direction of self test generated signal. */
    uint16_t signalCount;  /*!< Hold the number of quadrature advances to generate. The available range is 0 - 255.*/
    uint16_t signalPeriod; /*!< Hold the period of quadrature phase in IPBus clock cycles.
                                The available range is 0 - 31. */
} qdc_self_test_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and De-initialization
 * @{
 */

/*!
 * @brief Initialization for the QDC module.
 *
 * This function is to make the initialization for the QDC module. It should be called firstly before any operation to
 * the QDC with the operations like:
 *  - Enable the clock for QDC module.
 *  - Configure the QDC's working attributes.
 *
 * @param base   QDC peripheral base address.
 * @param config Pointer to configuration structure. See to "qdc_config_t".
 */
void QDC_Init(QDC_Type *base, const qdc_config_t *config);

/*!
 * @brief De-initialization for the QDC module.
 *
 * This function is to make the de-initialization for the QDC module. It could be called when QDC is no longer used with
 * the operations like:
 *  - Disable the clock for QDC module.
 *
 * @param base QDC peripheral base address.
 */
void QDC_Deinit(QDC_Type *base);

/*!
 * @brief Get an available pre-defined settings for QDC's configuration.
 *
 * This function initializes the QDC configuration structure with an available settings, the default value are:
 * @code
 *   config->enableReverseDirection                = false;
 *   config->decoderWorkMode                       = kQDC_DecoderWorkAsNormalMode;
 *   config->HOMETriggerMode                       = kQDC_HOMETriggerDisabled;
 *   config->INDEXTriggerMode                      = kQDC_INDEXTriggerDisabled;
 *   config->enableTRIGGERClearPositionCounter     = false;
 *   config->enableTRIGGERClearHoldPositionCounter = false;
 *   config->enableWatchdog                        = false;
 *   config->watchdogTimeoutValue                  = 0U;
 *   config->filterCount                           = 0U;
 *   config->filterSamplePeriod                    = 0U;
 *   config->positionMatchMode                     = kQDC_POSMATCHOnPositionCounterEqualToComapreValue;
 *   config->positionCompareValue                  = 0xFFFFFFFFU;
 *   config->revolutionCountCondition              = kQDC_RevolutionCountOnINDEXPulse;
 *   config->enableModuloCountMode                 = false;
 *   config->positionModulusValue                  = 0U;
 *   config->positionInitialValue                  = 0U;
 *   config->prescalerValue                        = kQDC_ClockDiv1;
 *   config->enablePeriodMeasurementFunction       = true;
 * @endcode
 * @param config Pointer to a variable of configuration structure. See to "qdc_config_t".
 */
void QDC_GetDefaultConfig(qdc_config_t *config);

/*!
 * @brief Load the initial position value to position counter.
 *
 * This function is to transfer the initial position value (UINIT and LINIT) contents to position counter (UPOS and
 * LPOS), so that to provide the consistent operation the position counter registers.
 *
 * @param base QDC peripheral base address.
 */
void QDC_DoSoftwareLoadInitialPositionValue(QDC_Type *base);

/*!
 * @brief Enable and configure the self test function.
 *
 * This function is to enable and configuration the self test function. It controls and sets the frequency of a
 * quadrature signal generator. It provides a quadrature test signal to the inputs of the quadrature decoder module.
 * It is a factory test feature; however, it may be useful to customers' software development and testing.
 *
 * @param base   QDC peripheral base address.
 * @param config Pointer to configuration structure. See to "qdc_self_test_config_t". Pass "NULL" to disable.
 */
void QDC_SetSelfTestConfig(QDC_Type *base, const qdc_self_test_config_t *config);

/*!
 * @brief Enable watchdog for QDC module.
 *
 * @param base QDC peripheral base address
 * @param enable Enables or disables the watchdog
 */
void QDC_EnableWatchdog(QDC_Type *base, bool enable);

/*!
 * @brief Set initial position value for QDC module.
 *
 * @param base QDC peripheral base address
 * @param value Positive initial value
 */
void QDC_SetInitialPositionValue(QDC_Type *base, uint32_t value);

/*! @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief  Get the status flags.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Mask value of status flags. For available mask, see to "_qdc_status_flags".
 */
uint32_t QDC_GetStatusFlags(QDC_Type *base);

/*!
 * @brief Clear the status flags.
 *
 * @param base QDC peripheral base address.
 * @param mask Mask value of status flags to be cleared. For available mask, see to "_qdc_status_flags".
 */
void QDC_ClearStatusFlags(QDC_Type *base, uint32_t mask);

/*!
 * @brief  Get the signals' real-time status.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Mask value of signals' real-time status. For available mask, see to "_qdc_signal_status_flags"
 */
static inline uint16_t QDC_GetSignalStatusFlags(QDC_Type *base)
{
    return base->IMR;
}
/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enable the interrupts.
 *
 * @param base QDC peripheral base address.
 * @param mask Mask value of interrupts to be enabled. For available mask, see to "_qdc_interrupt_enable".
 */
void QDC_EnableInterrupts(QDC_Type *base, uint32_t mask);

/*!
 * @brief Disable the interrupts.
 *
 * @param base QDC peripheral base address.
 * @param mask Mask value of interrupts to be disabled. For available mask, see to "_qdc_interrupt_enable".
 */
void QDC_DisableInterrupts(QDC_Type *base, uint32_t mask);

/*!
 * @brief  Get the enabled interrupts' flags.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Mask value of enabled interrupts.
 */
uint32_t QDC_GetEnabledInterrupts(QDC_Type *base);

/*! @} */

/*!
 * @name Value Operation
 * @{
 */

/*!
 * @brief  Get the current position counter's value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     Current position counter's value.
 */
uint32_t QDC_GetPositionValue(QDC_Type *base);

/*!
 * @brief  Get the hold position counter's value.
 *
 * When any of the counter registers is read, the contents of each counter register is written to the corresponding hold
 * register. Taking a snapshot of the counters' values provides a consistent view of a system position and a velocity to
 * be attained.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Hold position counter's value.
 */
uint32_t QDC_GetHoldPositionValue(QDC_Type *base);

/*!
 * @brief  Get the position difference counter's value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The position difference counter's value.
 */
static inline uint16_t QDC_GetPositionDifferenceValue(QDC_Type *base)
{
    return base->POSD;
}

/*!
 * @brief  Get the hold position difference counter's value.
 *
 * When any of the counter registers is read, the contents of each counter register is written to the corresponding hold
 * register. Taking a snapshot of the counters' values provides a consistent view of a system position and a velocity to
 * be attained.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Hold position difference counter's value.
 */
static inline uint16_t QDC_GetHoldPositionDifferenceValue(QDC_Type *base)
{
    return base->POSDH;
}

/*!
 * @brief  Get the position revolution counter's value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The position revolution counter's value.
 */
static inline uint16_t QDC_GetRevolutionValue(QDC_Type *base)
{
    return base->REV;
}

/*!
 * @brief  Get the hold position revolution counter's value.
 *
 * When any of the counter registers is read, the contents of each counter register is written to the corresponding hold
 * register. Taking a snapshot of the counters' values provides a consistent view of a system position and a velocity to
 * be attained.
 *
 * @param  base QDC peripheral base address.
 *
 * @return      Hold position revolution counter's value.
 */
static inline uint16_t QDC_GetHoldRevolutionValue(QDC_Type *base)
{
    return base->REVH;
}

#if (defined(FSL_FEATURE_QDC_HAS_LASTEDGE) && FSL_FEATURE_QDC_HAS_LASTEDGE)
/*!
 * @brief  Get the last edge time value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The last edge time hold value.
 */
static inline uint16_t QDC_GetLastEdgeTimeValue(QDC_Type *base)
{
    return base->LASTEDGE;
}

/*!
 * @brief  Get the last edge time hold value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The last edge time hold value.
 */
static inline uint16_t QDC_GetHoldLastEdgeTimeValue(QDC_Type *base)
{
    return base->LASTEDGEH;
}
#endif

#if (defined(FSL_FEATURE_QDC_HAS_POSDPER) && FSL_FEATURE_QDC_HAS_POSDPER)
/*!
 * @brief  Get the position difference period value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The position difference period hold value.
 */
static inline uint16_t QDC_GetPositionDifferencePeriodValue(QDC_Type *base)
{
    return base->POSDPER;
}

/*!
 * @brief  Get the position difference period buffer value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The position difference period hold value.
 */
static inline uint16_t QDC_GetPositionDifferencePeriodBufferValue(QDC_Type *base)
{
    return base->POSDPERBFR;
}

/*!
 * @brief  Get the position difference period hold value.
 *
 * @param  base QDC peripheral base address.
 *
 * @return     The position difference period hold value.
 */
static inline uint16_t QDC_GetHoldPositionDifferencePeriodValue(QDC_Type *base)
{
    return base->POSDPERH;
}
#endif
/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_QDC_H_ */
