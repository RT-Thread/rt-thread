/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_FREQME_H_
#define FSL_FREQME_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpc_freqme
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief FREQME driver version 2.1.2. */
#define FSL_FREQME_DRIVER_VERSION (MAKE_VERSION(2, 1, 2))
/*! @} */

/*!
 * @brief The enumeration of interrupt status flags.
 * @anchor _freqme_interrupt_status_flags
 */
enum _freqme_interrupt_status_flags
{
    kFREQME_UnderflowInterruptStatusFlag = FREQME_CTRLSTAT_LT_MIN_STAT_MASK,   /*!< Indicate the measurement is
                                                                                     just done and the result is less
                                                                                     than minimun value. */
    kFREQME_OverflowInterruptStatusFlag = FREQME_CTRLSTAT_GT_MAX_STAT_MASK,    /*!< Indicate the measurement is
                                                                                     just done and the result is greater
                                                                                     than maximum value. */
    kFREQME_ReadyInterruptStatusFlag = FREQME_CTRLSTAT_RESULT_READY_STAT_MASK, /*!< Indicate the measurement is
                                                                                 just done and the result is ready to
                                                                                 read. */
    kFREQME_AllInterruptStatusFlags = FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_GT_MAX_STAT_MASK |
                                      FREQME_CTRLSTAT_RESULT_READY_STAT_MASK, /*!< All interrupt
                                                                                        status flags. */
};

/*!
 * @brief The enumeration of interrupts, including underflow interrupt, overflow interrupt,
 * and result ready interrupt.
 * @anchor _freqme_interrupt_enable
 */
enum _freqme_interrupt_enable
{
    kFREQME_UnderflowInterruptEnable = FREQME_CTRL_W_LT_MIN_INT_EN_MASK, /*!< Enable interrupt when the result is
                                                                                   less than minimum value. */
    kFREQME_OverflowInterruptEnable = FREQME_CTRL_W_GT_MAX_INT_EN_MASK,  /*!< Enable interrupt when the result is
                                                                                   greater than maximum value. */
    kFREQME_ReadyInterruptEnable = FREQME_CTRL_W_RESULT_READY_INT_EN_MASK, /*!< Enable interrupt when a
                                                                                 measurement completes and the result
                                                                                 is ready. */
};

/*!
 * @brief FREQME module operate mode enumeration, including frequency measurement mode
 * and pulse width measurement mode.
 */
typedef enum _freqme_operate_mode
{
    kFREQME_FreqMeasurementMode = 0U,  /*!< The module works in the frequency measurement mode. */
    kFREOME_PulseWidthMeasurementMode, /*!< The module works in the pulse width measurement mode. */
} freqme_operate_mode_t;

/*!
 * @brief The enumeration of pulse polarity.
 */
typedef enum _freqme_pulse_polarity
{
    kFREQME_PulseHighPeriod = 0U, /*!< Select high period of the reference clock. */
    kFREQME_PulseLowPeriod,       /*!< Select low period of the reference clock. */
} freqme_pulse_polarity_t;

/*!
 * @brief The union of operate mode attribute.
 * @note If the operate mode is selected as frequency measurement mode the member \b refClkScaleFactor should be used,
 * if the operate mode is selected as pulse width measurement mode the member \b pulsePolarity should be used.
 */
typedef union _freqme_mode_attribute
{
    uint8_t refClkScaleFactor;             /*!< Only useful in frequency measurement operate mode,
                                               used to set the reference clock counter scaling factor. */
    freqme_pulse_polarity_t pulsePolarity; /*!< Only Useful in pulse width measurement operate mode,
                                               used to set period polarity. */
} freqme_mode_attribute_t;

/*!
 * @brief The structure of freqme module basic configuration,
 * including operate mode, operate mode attribute and so on.
 */
typedef struct _freq_measure_config
{
    freqme_operate_mode_t operateMode; /*!< Select operate mode, please refer to @ref freqme_operate_mode_t. */
    freqme_mode_attribute_t operateModeAttribute; /*!< Used to set the attribute of the selected operate mode, if
                                                the operate mode is selected as @ref kFREQME_FreqMeasurementMode
                                                set freqme_mode_attribute_t::refClkScaleFactor, if operate mode is
                                                selected as @ref kFREOME_PulseWidthMeasurementMode, please set
                                                freqme_mode_attribute_t::pulsePolarity.  */

    bool enableContinuousMode; /*!< Enable/disable continuous mode, if continuous mode is enable,
                                  the measurement is performed continuously and the result for the
                                  last completed measurement is available in the result register. */
    bool startMeasurement;
} freq_measure_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Basic Control APIs
 * @{
 */
/*!
 * @brief Initialize freqme module, set operate mode, operate mode attribute and initialize measurement cycle.
 *
 * @param base FREQME peripheral base address.
 * @param config The pointer to module basic configuration, please refer to @ref freq_measure_config_t.
 */
void FREQME_Init(FREQME_Type *base, const freq_measure_config_t *config);

/*!
 * @brief Get default configuration.
 *
 * @code
 *      config->operateMode = kFREQME_FreqMeasurementMode;
 *      config->operateModeAttribute.refClkScaleFactor = 0U;
 *      config->enableContinuousMode                   = false;
 *      config->startMeasurement                       = false;
 * @endcode
 *
 * @param config The pointer to module basic configuration, please refer to @ref freq_measure_config_t.
 */
void FREQME_GetDefaultConfig(freq_measure_config_t *config);

/*!
 * @brief Start frequency or pulse width measurement process.
 *
 * @param base FREQME peripheral base address.
 */
static inline void FREQME_StartMeasurementCycle(FREQME_Type *base)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_MEASURE_IN_PROGRESS_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);
    tmp32 |= FREQME_CTRL_W_MEASURE_IN_PROGRESS_MASK;
    base->CTRL_W = tmp32;
}

/*!
 * @brief Force the termination of any measurement cycle currently in progress and resets RESULT or just reset
 * RESULT if the module in idle state.
 *
 * @param base FREQME peripheral base address.
 */
static inline void FREQME_TerminateMeasurementCycle(FREQME_Type *base)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_MEASURE_IN_PROGRESS_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);
    base->CTRL_W = tmp32;
}

/*!
 * @brief Enable/disable Continuous mode.
 *
 * @param base FREQME peripheral base address.
 * @param enable Used to enable/disable continuous mode,
 *              - \b true Enable Continuous mode.
 *              - \b false Disable Continuous mode.
 */
static inline void FREQME_EnableContinuousMode(FREQME_Type *base, bool enable)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_CONTINUOUS_MODE_EN_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);
    if (enable)
    {
        tmp32 |= FREQME_CTRL_W_CONTINUOUS_MODE_EN_MASK;
    }

    base->CTRL_W = tmp32;
}

/*!
 * @brief Check whether continuous mode is enabled.
 *
 * @param base FREQME peripheral base address.
 * @retval True Continuous mode is enabled, the measurement is performed continuously.
 * @retval False Continuous mode is disabled.
 */
static inline bool FREQME_CheckContinuousMode(FREQME_Type *base)
{
    return (bool)((base->CTRLSTAT & FREQME_CTRLSTAT_CONTINUOUS_MODE_EN_MASK) != 0UL);
}

/*!
 * @brief Set operate mode of freqme module.
 *
 * @param base FREQME peripheral base address.
 * @param operateMode The operate mode to be set, please refer to @ref freqme_operate_mode_t.
 */
static inline void FREQME_SetOperateMode(FREQME_Type *base, freqme_operate_mode_t operateMode)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_PULSE_MODE_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);
    if (operateMode == kFREOME_PulseWidthMeasurementMode)
    {
        tmp32 |= FREQME_CTRL_W_PULSE_MODE_MASK;
    }

    base->CTRL_W = tmp32;
}

/*!
 * @brief Check module's operate mode.
 *
 * @param base FREQME peripheral base address.
 * @retval True Pulse width measurement mode.
 * @retval False Frequency measurement mode.
 */
static inline bool FREQME_CheckOperateMode(FREQME_Type *base)
{
    return (bool)((base->CTRLSTAT & FREQME_CTRLSTAT_PULSE_MODE_MASK) != 0UL);

}

/*!
 * @brief Set the minimum expected value for the measurement result.
 *
 * @param base FREQME peripheral base address.
 * @param minValue The minimum value to set, please note that this value is 31 bits width.
 */
static inline void FREQME_SetMinExpectedValue(FREQME_Type *base, uint32_t minValue)
{
    base->MIN = minValue;
}

/*!
 * @brief Set the maximum expected value for the measurement result.
 *
 * @param base FREQME peripheral base address.
 * @param maxValue The maximum value to set, please note that this value is 31 bits width.
 */
static inline void FREQME_SetMaxExpectedValue(FREQME_Type *base, uint32_t maxValue)
{
    base->MAX = maxValue;
}

/*! @} */

/*!
 * @name Frequency Measurement Mode Control APIs
 * @{
 */

/*!
 * @brief Calculate the frequency of selected target clock。
 *
 * @note The formula: Ftarget = (RESULT - 2) * Freference / 2 ^ REF_SCALE.
 *
 * @note This function only useful when the operate mode is selected as frequency measurement mode.
 *
 * @param base FREQME peripheral base address.
 * @param refClkFrequency The frequency of reference clock.
 * @return The frequency of target clock the unit is Hz, if the output result is 0, please check the module's
 *         operate mode.
 */
uint32_t FREQME_CalculateTargetClkFreq(FREQME_Type *base, uint32_t refClkFrequency);

/*!
 * @brief Get reference clock scaling factor.
 *
 * @param base FREQME peripheral base address.
 * @return Reference clock scaling factor, the reference count cycle is 2 ^ ref_scale.
 */
static inline uint8_t FREQME_GetReferenceClkScaleValue(FREQME_Type *base)
{
    return (uint8_t)(base->CTRLSTAT & FREQME_CTRLSTAT_REF_SCALE_MASK);
}

/*! @} */

/*!
 * @name Pulse Width Measurement Mode Control APIs
 * @{
 */

/*!
 * @brief Set pulse polarity when operate mode is selected as Pulse Width Measurement mode.
 *
 * @param base FREQME peripheral base address.
 * @param pulsePolarity The pulse polarity to be set, please refer to @ref freqme_pulse_polarity_t.
 */
static inline void FREQME_SetPulsePolarity(FREQME_Type *base, freqme_pulse_polarity_t pulsePolarity)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_PULSE_POL_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);

    if (pulsePolarity != kFREQME_PulseHighPeriod)
    {
        tmp32 |= FREQME_CTRL_W_PULSE_POL_MASK;
    }

    base->CTRL_W = tmp32;
}

/*!
 * @brief Check pulse polarity when the operate mode is selected as pulse width measurement mode.
 *
 * @param base FREQME peripheral base address.
 * @retval True Low period.
 * @retval False High period.
 */
static inline bool FREQME_CheckPulsePolarity(FREQME_Type *base)
{
    return (bool)((base->CTRLSTAT & FREQME_CTRLSTAT_PULSE_POL_MASK) != 0UL);
}

/*!
 * @brief Get measurement result, if operate mode is selected as pulse width measurement mode this function can
 * be used to calculate pulse width.
 *
 * @note Pulse width = counter result / Frequency of target clock.
 *
 * @param base FREQME peripheral base address.
 * @return Measurement result.
 */
static inline uint32_t FREQME_GetMeasurementResult(FREQME_Type *base)
{
    return base->CTRL_R & FREQME_CTRL_R_RESULT_MASK;
}

/*! @} */

/*!
 * @name Status Control APIs
 * @{
 */

/*!
 * @brief Get interrupt status flags, such as overflow interrupt status flag,
 * underflow interrupt status flag, and so on.
 *
 * @param base FREQME peripheral base address.
 * @return Current interrupt status flags, should be the OR'ed value of @ref _freqme_interrupt_status_flags.
 */
static inline uint32_t FREQME_GetInterruptStatusFlags(FREQME_Type *base)
{
    return (base->CTRLSTAT & (uint32_t)kFREQME_AllInterruptStatusFlags);
}

/*!
 * @brief Clear interrupt status flags.
 *
 * @param base FREQME peripheral base address.
 * @param statusFlags The combination of interrupt status flags to clear,
 *                    should be the OR'ed value of @ref _freqme_interrupt_status_flags.
 */
static inline void FREQME_ClearInterruptStatusFlags(FREQME_Type *base, uint32_t statusFlags)
{
    base->CTRLSTAT |= statusFlags;
}

/*! @} */

/*!
 * @name Interrupt Control APIs
 * @{
 */

/*!
 * @brief Enable interrupts, such as result ready interrupt, overflow interrupt and so on.
 *
 * @param base FREQME peripheral base address.
 * @param masks The mask of interrupts to enable, should be the OR'ed value of @ref _freqme_interrupt_enable.
 */
static inline void FREQME_EnableInterrupts(FREQME_Type *base, uint32_t masks)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_LT_MIN_INT_EN_MASK |
               FREQME_CTRLSTAT_GT_MAX_STAT_MASK | FREQME_CTRLSTAT_GT_MAX_INT_EN_MASK |
               FREQME_CTRLSTAT_RESULT_READY_INT_EN_MASK | FREQME_CTRLSTAT_RESULT_READY_STAT_MASK);

    tmp32 |= masks;
    base->CTRL_W = tmp32;
}

/*!
 * @brief Disable interrupts, such as result ready interrupt, overflow interrupt and so on.
 *
 * @param base FREQME peripheral base address.
 * @param masks The mask of interrupts to disable, should be the OR'ed value of @ref _freqme_interrupt_enable.
 */
static inline void FREQME_DisableInterrupts(FREQME_Type *base, uint32_t masks)
{
    uint32_t tmp32;

    tmp32 = base->CTRLSTAT;
    tmp32 &= ~(FREQME_CTRLSTAT_LT_MIN_STAT_MASK | FREQME_CTRLSTAT_GT_MAX_STAT_MASK |
               FREQME_CTRLSTAT_RESULT_READY_STAT_MASK | masks);

    base->CTRL_W = tmp32;
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_FREQME_H_ */
