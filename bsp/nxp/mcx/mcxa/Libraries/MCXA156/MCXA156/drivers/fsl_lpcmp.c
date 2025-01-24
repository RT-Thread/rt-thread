/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpcmp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpcmp"
#endif

#if defined(LPCMP_RSTS)
#define LPCMP_RESETS_ARRAY LPCMP_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(LPCMP_CLOCKS)
/*!
 * @brief Get instance number for LPCMP module.
 *
 * @param base LPCMP peripheral base address
 */
static uint32_t LPCMP_GetInstance(LPCMP_Type *base);
#endif /* LPCMP_CLOCKS */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(LPCMP_CLOCKS)
/*! @brief Pointers to LPCMP bases for each instance. */
static LPCMP_Type *const s_lpcmpBases[] = LPCMP_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LPCMP clocks for each instance. */
static const clock_ip_name_t s_lpcmpClocks[] = LPCMP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* LPCMP_CLOCKS */

#if defined(LPCMP_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_lpcmpResets[] = LPCMP_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Codes
 ******************************************************************************/
#if defined(LPCMP_CLOCKS)
static uint32_t LPCMP_GetInstance(LPCMP_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    /*
     * $Branch Coverage Justification$
     * (instance >= ARRAY_SIZE(s_lpcmpBases)) not covered. The peripheral base
     * address is always valid and checked by assert.
     */
    for (instance = 0; instance < ARRAY_SIZE(s_lpcmpBases); instance++)
    {
        /*
         * $Branch Coverage Justification$
         * (s_lpcmpBases[instance] != base) not covered. The peripheral base
         * address is always valid and checked by assert.
         */
        if (s_lpcmpBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lpcmpBases));

    return instance;
}
#endif /* LPCMP_CLOCKS */

/*!
 * brief Initialize the LPCMP
 *
 * This function initializes the LPCMP module. The operations included are:
 * - Enabling the clock for LPCMP module.
 * - Configuring the comparator.
 * - Enabling the LPCMP module.
 * Note: For some devices, multiple LPCMP instance share the same clock gate. In this case, to enable the clock for
 * any instance enables all the LPCMPs. Check the chip reference manual for the clock assignment of the LPCMP.
 *
 * param base LPCMP peripheral base address.
 * param config Pointer to "lpcmp_config_t" structure.
 */
void LPCMP_Init(LPCMP_Type *base, const lpcmp_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

#if defined(LPCMP_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_lpcmpClocks[LPCMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* LPCMP_CLOCKS */

#if defined(LPCMP_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_lpcmpResets[LPCMP_GetInstance(base)]);
#endif

    /* Configure. */
    LPCMP_Enable(base, false);

#if !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN)
    /* CCR0 register. */
#if defined(FSL_FEATURE_LPCMP_INSTANCE_SUPPORT_CCR0_CMP_STOP_ENn)
    if (1U == FSL_FEATURE_LPCMP_INSTANCE_SUPPORT_CCR0_CMP_STOP_ENn(base))
#endif /* FSL_FEATURE_LPCMP_INSTANCE_SUPPORT_CCR0_CMP_STOP_ENn */
    {
        if (config->enableStopMode)
        {
            base->CCR0 |= LPCMP_CCR0_CMP_STOP_EN_MASK;
        }
        else
        {
            base->CCR0 &= ~LPCMP_CCR0_CMP_STOP_EN_MASK;
        }
    }
#endif /* !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) */

    /* CCR1 register. */
    tmp32 = (base->CCR1 & (~(LPCMP_CCR1_COUT_PEN_MASK | LPCMP_CCR1_COUT_SEL_MASK | LPCMP_CCR1_COUT_INV_MASK
#if defined(FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL) && FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL
                             | LPCMP_CCR1_FUNC_CLK_SEL_MASK
#endif /* FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL */
                             )));

    if (config->enableOutputPin)
    {
        tmp32 |= LPCMP_CCR1_COUT_PEN_MASK;
    }
    if (config->useUnfilteredOutput)
    {
        tmp32 |= LPCMP_CCR1_COUT_SEL_MASK;
    }
    if (config->enableInvertOutput)
    {
        tmp32 |= LPCMP_CCR1_COUT_INV_MASK;
    }
#if defined(FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL) && FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL
    tmp32 |= LPCMP_CCR1_FUNC_CLK_SEL(config->functionalSourceClock);
#endif /* FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL */
    base->CCR1 = tmp32;
    /* CCR2 register. */
    tmp32 = base->CCR2 & ~(LPCMP_CCR2_HYSTCTR_MASK | LPCMP_CCR2_CMP_NPMD_MASK | LPCMP_CCR2_CMP_HPMD_MASK);
    tmp32 |= LPCMP_CCR2_HYSTCTR(config->hysteresisMode);
    tmp32 |= ((uint32_t)(config->powerMode) << LPCMP_CCR2_CMP_HPMD_SHIFT);
    base->CCR2 = tmp32;

    LPCMP_Enable(base, true); /* Enable the LPCMP module. */
}

/*!
 * brief De-initializes the LPCMP module.
 *
 * This function de-initializes the LPCMP module. The operations included are:
 * - Disabling the LPCMP module.
 * - Disabling the clock for LPCMP module.
 *
 * This function disables the clock for the LPCMP.
 * Note: For some devices, multiple LPCMP instance shares the same clock gate. In this case, before disabling the
 * clock for the LPCMP, ensure that all the LPCMP instances are not used.
 *
 * param base LPCMP peripheral base address.
 */
void LPCMP_Deinit(LPCMP_Type *base)
{
    /* Disable the LPCMP module. */
    LPCMP_Enable(base, false);
#if defined(LPCMP_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_lpcmpClocks[LPCMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* LPCMP_CLOCKS */
}

/*!
 * brief Gets an available pre-defined settings for the comparator's configuration.
 *
 * This function initializes the comparator configuration structure to these default values:
 * code
 *   config->enableStopMode      = false;
 *   config->enableOutputPin     = false;
 *   config->useUnfilteredOutput = false;
 *   config->enableInvertOutput  = false;
 *   config->hysteresisMode      = kLPCMP_HysteresisLevel0;
 *   config->powerMode           = kLPCMP_LowSpeedPowerMode;
 *   config->functionalSourceClock = kLPCMP_FunctionalClockSource0;
 * endcode
 * param config Pointer to "lpcmp_config_t" structure.
 */
void LPCMP_GetDefaultConfig(lpcmp_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
#if !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN)
    config->enableStopMode = false;
#endif /* !(defined(FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) && FSL_FEATURE_LPCMP_HAS_NO_CCR0_CMP_STOP_EN) */
    config->enableOutputPin     = false;
    config->useUnfilteredOutput = false;
    config->enableInvertOutput  = false;
    config->hysteresisMode      = kLPCMP_HysteresisLevel0;
    config->powerMode           = kLPCMP_LowSpeedPowerMode;
#if defined(FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL) && FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL
    config->functionalSourceClock = kLPCMP_FunctionalClockSource0;
#endif /* FSL_FEATURE_LPCMP_HAS_CCR1_FUNC_CLK_SEL */
}

/*!
 * brief Select the input channels for LPCMP. This function determines which input
 *        is selected for the negative and positive mux.
 *
 * param base LPCMP peripheral base address.
 * param positiveChannel Positive side input channel number.
 * param negativeChannel Negative side input channel number.
 */
void LPCMP_SetInputChannels(LPCMP_Type *base, uint32_t positiveChannel, uint32_t negativeChannel)
{
    uint32_t tmp32;

    tmp32 = base->CCR2 & ~(LPCMP_CCR2_PSEL_MASK | LPCMP_CCR2_MSEL_MASK);
    tmp32 |= LPCMP_CCR2_PSEL(positiveChannel) | LPCMP_CCR2_MSEL(negativeChannel);
    base->CCR2 = tmp32;
}

/*!
 * brief Configures the filter.
 *
 * param base LPCMP peripheral base address.
 * param config Pointer to "lpcmp_filter_config_t" structure.
 */
void LPCMP_SetFilterConfig(LPCMP_Type *base, const lpcmp_filter_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

    tmp32 = base->CCR1 & ~(LPCMP_CCR1_FILT_PER_MASK | LPCMP_CCR1_FILT_CNT_MASK | LPCMP_CCR1_SAMPLE_EN_MASK);
    if (config->enableSample)
    {
        tmp32 |= LPCMP_CCR1_SAMPLE_EN_MASK;
    }
    tmp32 |= LPCMP_CCR1_FILT_PER(config->filterSamplePeriod) | LPCMP_CCR1_FILT_CNT(config->filterSampleCount);
    base->CCR1 = tmp32;
}

/*!
 * brief Configure the internal DAC module.
 *
 * param base LPCMP peripheral base address.
 * param config Pointer to "lpcmp_dac_config_t" structure. If config is "NULL", disable internal DAC.
 */
void LPCMP_SetDACConfig(LPCMP_Type *base, const lpcmp_dac_config_t *config)
{
    uint32_t tmp32;
    if (config == NULL)
    {
        tmp32 = 0U; /* Disable internal DAC. */
    }
    else
    {
        tmp32 = LPCMP_DCR_VRSEL(config->referenceVoltageSource) | LPCMP_DCR_DAC_DATA(config->DACValue);
        if (config->enableLowPowerMode)
        {
            tmp32 |= LPCMP_DCR_DAC_HPMD_MASK;
        }
        tmp32 |= LPCMP_DCR_DAC_EN_MASK;
    }
    base->DCR = tmp32;
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
void LPCMP_SetWindowControl(LPCMP_Type *base, const lpcmp_window_control_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32 = 0UL;

    tmp32 = (base->CCR1 & (~(LPCMP_CCR1_COUTA_CFG_MASK | LPCMP_CCR1_EVT_SEL_CFG_MASK | LPCMP_CCR1_WINDOW_INV_MASK)));

    if (config->enableInvertWindowSignal)
    {
        tmp32 |= LPCMP_CCR1_WINDOW_INV_MASK;
    }

    /* Set COUT event, which can close the active window in window mode. */
    tmp32 |= LPCMP_CCR1_EVT_SEL_CFG(config->closeWindowEvent);

    /* Set the COUTA signal value when the window is closed. */
    tmp32 |= LPCMP_CCR1_COUTA_CFG(config->COUTASignal);

    base->CCR1 = tmp32;
}
#endif /* FSL_FEATURE_LPCMP_HAS_WINDOW_CONTROL */

#if defined(FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE) && FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE
/*!
 * @brief Configure the roundrobin mode.
 *
 * @param base LPCMP peripheral base address.
 * @param config Pointer "lpcmp_roundrobin_config_t" structure.
 */
void LPCMP_SetRoundRobinConfig(LPCMP_Type *base, const lpcmp_roundrobin_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32 = 0UL;

    /* LPCMPx_RRCR0 register, Configuration options for the round-robin operation. */
    tmp32 = (base->RRCR0 &
             (~(LPCMP_RRCR0_RR_TRG_SEL_MASK | LPCMP_RRCR0_RR_NSAM_MASK | LPCMP_RRCR0_RR_CLK_SEL_MASK |
                LPCMP_RRCR0_RR_INITMOD_MASK | LPCMP_RRCR0_RR_SAMPLE_CNT_MASK | LPCMP_RRCR0_RR_SAMPLE_THRESHOLD_MASK)));

    tmp32 |=
        (LPCMP_RRCR0_RR_TRG_SEL(config->roundrobinTriggerSource) | LPCMP_RRCR0_RR_NSAM(config->sampleClockNumbers) |
         LPCMP_RRCR0_RR_CLK_SEL(config->roundrobinClockSource) | LPCMP_RRCR0_RR_INITMOD(config->initDelayModules) |
         LPCMP_RRCR0_RR_SAMPLE_CNT(config->channelSampleNumbers) |
         LPCMP_RRCR0_RR_SAMPLE_THRESHOLD(config->sampleTimeThreshhold));

    base->RRCR0 = tmp32;

    /* LPCMPx_RRCR1 register, Configure the fix port, fix channel and checker channel. */
    tmp32 =
        (base->RRCR1 & (~(LPCMP_RRCR1_FIXP_MASK | LPCMP_RRCR1_FIXCH_MASK | (0xFFUL << LPCMP_RRCR1_RR_CH0EN_SHIFT))));
    tmp32 |= (LPCMP_RRCR1_FIXP(config->fixedMuxPort) | LPCMP_RRCR1_FIXCH(config->fixedChannel) |
              ((uint32_t)(config->checkerChannelMask) << LPCMP_RRCR1_RR_CH0EN_SHIFT));

    base->RRCR1 = tmp32;
}

/*!
 * brief Configure the roundrobin internal timer reload value.
 *
 * param base LPCMP peripheral base address.
 * param value RoundRobin internal timer reload value, allowed range:0x0UL-0xFFFFFFFUL.
 */
void LPCMP_SetRoundRobinInternalTimer(LPCMP_Type *base, uint32_t value)
{
    uint32_t tmp32 = 0UL;

    tmp32 = (base->RRCR2 & (~LPCMP_RRCR2_RR_TIMER_RELOAD_MASK));
    tmp32 |= LPCMP_RRCR2_RR_TIMER_RELOAD(value);

    base->RRCR2 = tmp32;
}

#endif /* FSL_FEATURE_LPCMP_HAS_ROUNDROBIN_MODE */
