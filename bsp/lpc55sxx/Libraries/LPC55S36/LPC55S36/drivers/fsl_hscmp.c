/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_hscmp.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.hscmp"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(HSCMP_CLOCKS)
/*!
 * @brief Get instance number for HSCMP module.
 *
 * @param base HSCMP peripheral base address
 */
static uint32_t HSCMP_GetInstance(HSCMP_Type *base);
#endif /* HSCMP_CLOCKS */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(HSCMP_CLOCKS)
/*! @brief Pointers to HSCMP bases for each instance. */
static HSCMP_Type *const s_hscmpBases[] = HSCMP_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to HSCMP clocks for each instance. */
static const clock_ip_name_t s_hscmpClocks[] = HSCMP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* HSCMP_CLOCKS */

/*******************************************************************************
 * Codes
 ******************************************************************************/
#if defined(HSCMP_CLOCKS)
static uint32_t HSCMP_GetInstance(HSCMP_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_hscmpBases); instance++)
    {
        if (s_hscmpBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_hscmpBases));

    return instance;
}
#endif /* HSCMP_CLOCKS */

/*!
 * brief Initialize the HSCMP
 *
 * This function initializes the HSCMP module. The operations included are:
 * - Enabling the clock for HSCMP module.
 * - Configuring the comparator.
 * - Enabling the HSCMP module.
 * Note: For some devices, multiple HSCMP instance share the same clock gate. In this case, to enable the clock for
 * any instance enables all the HSCMPs. Check the chip reference manual for the clock assignment of the HSCMP.
 *
 * param base HSCMP peripheral base address.
 * param config Pointer to "hscmp_config_t" structure.
 */
void HSCMP_Init(HSCMP_Type *base, const hscmp_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

#if defined(HSCMP_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_hscmpClocks[HSCMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* HSCMP_CLOCKS */

    /* Configure. */
    HSCMP_Enable(base, false);
    /* CCR0 register. */
    if (config->enableStopMode)
    {
        base->CCR0 |= HSCMP_CCR0_CMP_STOP_EN_MASK;
    }
    else
    {
        base->CCR0 &= ~HSCMP_CCR0_CMP_STOP_EN_MASK;
    }
    /* CCR1 register. */
    tmp32 = base->CCR1 & ~(HSCMP_CCR1_COUT_PEN_MASK | HSCMP_CCR1_COUT_SEL_MASK | HSCMP_CCR1_COUT_INV_MASK);
    if (config->enableOutputPin)
    {
        tmp32 |= HSCMP_CCR1_COUT_PEN_MASK;
    }
    if (config->useUnfilteredOutput)
    {
        tmp32 |= HSCMP_CCR1_COUT_SEL_MASK;
    }
    if (config->enableInvertOutput)
    {
        tmp32 |= HSCMP_CCR1_COUT_INV_MASK;
    }
    base->CCR1 = tmp32;
    /* CCR2 register. */
    tmp32 = base->CCR2 & ~(HSCMP_CCR2_HYSTCTR_MASK | HSCMP_CCR2_CMP_NPMD_MASK | HSCMP_CCR2_CMP_HPMD_MASK);
    tmp32 |= HSCMP_CCR2_HYSTCTR(config->hysteresisMode);
    tmp32 |= ((uint32_t)(config->powerMode) << HSCMP_CCR2_CMP_HPMD_SHIFT);
    base->CCR2 = tmp32;

    HSCMP_Enable(base, true); /* Enable the HSCMP module. */
}

/*!
 * brief De-initializes the HSCMP module.
 *
 * This function de-initializes the HSCMP module. The operations included are:
 * - Disabling the HSCMP module.
 * - Disabling the clock for HSCMP module.
 *
 * This function disables the clock for the HSCMP.
 * Note: For some devices, multiple HSCMP instance shares the same clock gate. In this case, before disabling the
 * clock for the HSCMP, ensure that all the HSCMP instances are not used.
 *
 * param base HSCMP peripheral base address.
 */
void HSCMP_Deinit(HSCMP_Type *base)
{
    /* Disable the HSCMP module. */
    HSCMP_Enable(base, false);
#if defined(HSCMP_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_hscmpClocks[HSCMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* HSCMP_CLOCKS */
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
 *   config->hysteresisMode      = kHSCMP_HysteresisLevel0;
 *   config->powerMode           = kHSCMP_LowSpeedPowerMode;
 * endcode
 * param config Pointer to "hscmp_config_t" structure.
 */
void HSCMP_GetDefaultConfig(hscmp_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableStopMode      = false;
    config->enableOutputPin     = false;
    config->useUnfilteredOutput = false;
    config->enableInvertOutput  = false;
    config->hysteresisMode      = kHSCMP_HysteresisLevel0;
    config->powerMode           = kHSCMP_LowSpeedPowerMode;
}

/*!
 * brief Select the input channels for HSCMP. This function determines which input
 *        is selected for the negative and positive mux.
 *
 * param base HSCMP peripheral base address.
 * param positiveChannel Positive side input channel number. Available range is 0-7.
 * param negativeChannel Negative side input channel number. Available range is 0-7.
 */
void HSCMP_SetInputChannels(HSCMP_Type *base, uint32_t positiveChannel, uint32_t negativeChannel)
{
    uint32_t tmp32;

    tmp32 = base->CCR2 & ~(HSCMP_CCR2_PSEL_MASK | HSCMP_CCR2_MSEL_MASK);
    tmp32 |= HSCMP_CCR2_PSEL(positiveChannel) | HSCMP_CCR2_MSEL(negativeChannel);
    base->CCR2 = tmp32;
}

/*!
 * brief Configures the filter.
 *
 * param base HSCMP peripheral base address.
 * param config Pointer to "hscmp_filter_config_t" structure.
 */
void HSCMP_SetFilterConfig(HSCMP_Type *base, const hscmp_filter_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

    tmp32 = base->CCR1 & ~(HSCMP_CCR1_FILT_PER_MASK | HSCMP_CCR1_FILT_CNT_MASK | HSCMP_CCR1_SAMPLE_EN_MASK);
    if (config->enableSample)
    {
        tmp32 |= HSCMP_CCR1_SAMPLE_EN_MASK;
    }
    tmp32 |= HSCMP_CCR1_FILT_PER(config->filterSamplePeriod) | HSCMP_CCR1_FILT_CNT(config->filterSampleCount);
    base->CCR1 = tmp32;
}

/*!
 * brief Configure the internal DAC module.
 *
 * param base HSCMP peripheral base address.
 * param config Pointer to "hscmp_dac_config_t" structure. If config is "NULL", disable internal DAC.
 */
void HSCMP_SetDACConfig(HSCMP_Type *base, const hscmp_dac_config_t *config)
{
    uint32_t tmp32;
    if (config == NULL)
    {
        tmp32 = 0U; /* Disable internal DAC. */
    }
    else
    {
        tmp32 = HSCMP_DCR_VRSEL(config->referenceVoltageSource) | HSCMP_DCR_DAC_DATA(config->DACValue);
        if (config->enableLowPowerMode)
        {
            tmp32 |= HSCMP_DCR_DAC_HPMD_MASK;
        }
        tmp32 |= HSCMP_DCR_DAC_EN_MASK;
    }
    base->DCR = tmp32;
}
