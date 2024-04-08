/*
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_freqme.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_freqme"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t FREQME_GetInstance(FREQME_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array to map freqme instance number to base address. */
static FREQME_Type *const s_freqmeBases[] = FREQME_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to FREQME clocks for each instance. */
static const clock_ip_name_t s_freqmeClocks[] = FREQME_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t FREQME_GetInstance(FREQME_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_freqmeBases); instance++)
    {
        if (s_freqmeBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_freqmeBases));

    return instance;
}

/*!
 * brief Initialize freqme module, set operate mode, operate mode attribute and initialize measurement cycle.
 *
 * param base FREQME peripheral base address.
 * param config The pointer to module basic configuration, please refer to freq_measure_config_t.
 */
void FREQME_Init(FREQME_Type *base, const freq_measure_config_t *config)
{
    assert(config);

    uint32_t tmp32 = 0UL;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable FREQME clock. */
    CLOCK_EnableClock(s_freqmeClocks[FREQME_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    if (config->startMeasurement)
    {
        tmp32 |= FREQME_FREQMECTRL_W_MEASURE_IN_PROGRESS_MASK;
    }
    tmp32 |= FREQME_FREQMECTRL_W_CONTINUOUS_MODE_EN(config->enableContinuousMode) |
             FREQME_FREQMECTRL_W_PULSE_MODE(config->operateMode);
    if (config->operateMode == kFREQME_FreqMeasurementMode)
    {
        tmp32 |= FREQME_FREQMECTRL_W_REF_SCALE(config->operateModeAttribute.refClkScaleFactor);
    }
    else
    {
        tmp32 |= FREQME_FREQMECTRL_W_PULSE_POL(config->operateModeAttribute.pulsePolarity);
    }

    base->FREQMECTRL_W = tmp32;
}

/*!
 * brief Get default configuration.
 *
 * code
 *      config->operateMode = kFREQME_FreqMeasurementMode;
 *      config->operateModeAttribute.refClkScaleFactor = 0U;
 *      config->enableContinuousMode                   = false;
 *      config->startMeasurement                       = false;
 * endcode
 *
 * param config The pointer to module basic configuration, please refer to freq_measure_config_t.
 */
void FREQME_GetDefaultConfig(freq_measure_config_t *config)
{
    assert(config);

    (void)memset(config, 0, sizeof(*config));

    config->operateMode                            = kFREQME_FreqMeasurementMode;
    config->operateModeAttribute.refClkScaleFactor = 0U;
    config->enableContinuousMode                   = false;
    config->startMeasurement                       = false;
}

/*!
 * brief Calculate the frequency of selected target clock.
 *
 * note The formula: Ftarget = (RESULT - 2) * Freference / 2 ^ REF_SCALE.
 *
 * note This function only useful when the operate mode is selected as frequency measurement mode.
 *
 * param base FREQME peripheral base address.
 * param refClkFrequency The frequency of reference clock.
 * return The frequency of target clock, if the output result is 0, please check the module's operate mode.
 */
uint32_t FREQME_CalculateTargetClkFreq(FREQME_Type *base, uint32_t refClkFrequency)
{
    uint64_t measureResult = 0ULL;
    uint32_t targetFreq    = 0ULL;
    uint64_t tmp64         = 0ULL;

    while ((base->FREQMECTRL_R & FREQME_FREQMECTRL_R_MEASURE_IN_PROGRESS_MASK) != 0UL)
    {
    }

    if (!FREQME_CheckOperateMode(base))
    {
        measureResult = (uint64_t)(base->FREQMECTRL_R & FREQME_FREQMECTRL_R_RESULT_MASK);
        tmp64         = (measureResult - 2ULL) * (uint64_t)refClkFrequency;
        targetFreq    = (uint32_t)(tmp64 / (1UL << (uint32_t)FREQME_GetReferenceClkScaleValue(base)));
    }

    return targetFreq;
}
