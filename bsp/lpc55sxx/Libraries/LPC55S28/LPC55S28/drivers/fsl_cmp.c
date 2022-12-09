/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cmp.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cmp_1"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief CMP initialization.
 *
 * This function enables the CMP module and do necessary settings.
 *
 * @param config Pointer to the configuration structure.
 */
void CMP_Init(const cmp_config_t *config)
{
    assert(NULL != config);

    uint32_t tmpReg = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(kCLOCK_Comp);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_CMP_HAS_NO_RESET) && FSL_TEATURE_CMP_HAS_NO_RESET)
    /* Reset the CMP module. */
    RESET_PeripheralReset(kCMP_RST_SHIFT_RSTn);
#endif /* FSL_FEATURE_CMP_HAS_NO_RESET */

    tmpReg = (PMC->COMP & ~(PMC_COMP_LOWPOWER_MASK | PMC_COMP_HYST_MASK | PMC_COMP_FILTERCGF_CLKDIV_MASK |
                            PMC_COMP_FILTERCGF_SAMPLEMODE_MASK));

    if (true == config->enableLowPower)
    {
        tmpReg |= PMC_COMP_LOWPOWER_MASK;
    }
    else
    {
        tmpReg &= ~PMC_COMP_LOWPOWER_MASK;
    }

    if (true == config->enableHysteresis)
    {
        tmpReg |= PMC_COMP_HYST_MASK;
    }
    else
    {
        tmpReg &= ~PMC_COMP_HYST_MASK;
    }

    tmpReg |= (PMC_COMP_FILTERCGF_CLKDIV(config->filterClockDivider) |
               PMC_COMP_FILTERCGF_SAMPLEMODE(config->filterSampleMode));

    PMC->COMP = tmpReg;
}

/*!
 * @brief CMP deinitialization.
 *
 * This function gates the clock for CMP module.
 */
void CMP_Deinit(void)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(kCLOCK_Comp);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * @brief Initializes the CMP user configuration structure.
 *
 * This function initializes the user configuration structure to these default values.
 * @code
 *   config->enableHysteresis    = true;
 *   config->enableLowPower      = true;
 *   config->filterClockDivider  = kCMP_FilterClockDivide1;
 *   config->filterSampleMode    = kCMP_FilterSampleMode0;
 * @endcode
 * @param config Pointer to the configuration structure.
 */
void CMP_GetDefaultConfig(cmp_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableHysteresis   = true;
    config->enableLowPower     = true;
    config->filterClockDivider = kCMP_FilterClockDivide1;
    config->filterSampleMode   = kCMP_FilterSampleMode0;
}

/*!
 * @brief Configures the VREFINPUT.
 *
 * @param config Pointer to the configuration structure.
 */
void CMP_SetVREF(const cmp_vref_config_t *config)
{
    assert(NULL != config);
    assert(config->vrefValue < 32U);

    uint32_t tmpReg = PMC->COMP & ~(PMC_COMP_VREF_MASK | PMC_COMP_VREFINPUT_MASK);

    tmpReg |= PMC_COMP_VREFINPUT(config->vrefSource) | PMC_COMP_VREF(config->vrefValue);

    PMC->COMP = tmpReg;
}
