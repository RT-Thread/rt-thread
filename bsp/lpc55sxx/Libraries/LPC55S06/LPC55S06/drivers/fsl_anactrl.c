/*
 * Copyright 2018-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_anactrl.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.anactrl"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for ANACTRL module.
 *
 * @param base ANACTRL peripheral base address
 */
static uint32_t ANACTRL_GetInstance(ANACTRL_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to ANACTRL bases for each instance. */
static ANACTRL_Type *const s_anactrlBases[] = ANACTRL_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to ANACTRL clocks for each instance. */
static const clock_ip_name_t s_anactrlClocks[] = ANALOGCTRL_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Get the ANACTRL instance from peripheral base address.
 *
 * param base ANACTRL peripheral base address.
 * return ANACTRL instance.
 */
static uint32_t ANACTRL_GetInstance(ANACTRL_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_anactrlBases); instance++)
    {
        if (s_anactrlBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_anactrlBases));

    return instance;
}

/*!
 * brief Initializes the ANACTRL mode, the module's clock will be enabled by invoking this function.
 *
 * param base ANACTRL peripheral base address.
 */
void ANACTRL_Init(ANACTRL_Type *base)
{
    assert(NULL != base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock for ANACTRL instance. */
    CLOCK_EnableClock(s_anactrlClocks[ANACTRL_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes ANACTRL module, the module's clock will be disabled by invoking this function.
 *
 * param base ANACTRL peripheral base address.
 */
void ANACTRL_Deinit(ANACTRL_Type *base)
{
    assert(NULL != base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock for ANACTRL instance. */
    CLOCK_DisableClock(s_anactrlClocks[ANACTRL_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Configs the on-chip high-speed Free Running Oscillator(FRO192M), such as enabling/disabling 12 MHZ clock output
 * and enable/disable 96MHZ clock output.
 *
 * param base ANACTRL peripheral base address.
 * param config Pointer to FRO192M configuration structure. Refer to anactrl_fro192M_config_t structure.
 */
void ANACTRL_SetFro192M(ANACTRL_Type *base, const anactrl_fro192M_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32 = base->FRO192M_CTRL;

    tmp32 &= ~(ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK | ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK);

    if (config->enable12MHzClk)
    {
        tmp32 |= ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK;
    }
    if (config->enable96MHzClk)
    {
        tmp32 |= ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK;
    }

    base->FRO192M_CTRL |= tmp32;
}

/*!
 * brief Gets the default configuration of FRO192M.
 * The default values are:
 * code
    config->enable12MHzClk = true;
    config->enable96MHzClk = false;
    endcode
 * param config Pointer to FRO192M configuration structure. Refer to anactrl_fro192M_config_t structure.
 */
void ANACTRL_GetDefaultFro192MConfig(anactrl_fro192M_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enable12MHzClk = true;
    config->enable96MHzClk = false;
}

/*!
 * brief Configs the 32 MHz Crystal oscillator(High-speed crystal oscillator), such as enable/disable output to CPU
 * system, and so on.
 *
 * param base ANACTRL peripheral base address.
 * param config Pointer to XO32M configuration structure. Refer to anactrl_xo32M_config_t structure.
 */
void ANACTRL_SetXo32M(ANACTRL_Type *base, const anactrl_xo32M_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32 = base->XO32M_CTRL;

    tmp32 &= ~(ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK | ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK);

    /* Set XO32M CTRL. */
#if !(defined(FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD) && \
      FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD)
    tmp32 &= ~ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_MASK;
    if (config->enablePllUsbOutput)
    {
        tmp32 |= ANACTRL_XO32M_CTRL_ENABLE_PLL_USB_OUT_MASK;
    }
#endif /* FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD */

    if (config->enableACBufferBypass)
    {
        tmp32 |= ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK;
    }

    if (config->enableSysCLkOutput)
    {
        tmp32 |= ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK;
    }
    base->XO32M_CTRL = tmp32;

#if (defined(FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD) && \
     FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD)
    if (config->enableADCOutput)
    {
        base->DUMMY_CTRL |= ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_MASK;
    }
    else
    {
        base->DUMMY_CTRL &= ~ANACTRL_DUMMY_CTRL_XO32M_ADC_CLK_MODE_MASK;
    }
#endif /* FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD */
}

/*!
 * brief Gets the default configuration of XO32M.
 * The default values are:
 * code
    config->enableSysCLkOutput = false;
    config->enableACBufferBypass = false;
    endcode
 * param config Pointer to XO32M configuration structure. Refer to anactrl_xo32M_config_t structure.
 */
void ANACTRL_GetDefaultXo32MConfig(anactrl_xo32M_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

#if !(defined(FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD) && \
      FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD)
    config->enablePllUsbOutput = false;
#endif /* FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD */
    config->enableSysCLkOutput   = false;
    config->enableACBufferBypass = false;
#if (defined(FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD) && \
     FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD)
    config->enableADCOutput = true;
#endif /* FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD */
}

#if !(defined(FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL) && FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL)
/*!
 * brief Measures the frequency of the target clock source.
 *
 * This function measures target frequency according to a accurate reference frequency.The formula is:
 * Ftarget = (CAPVAL * Freference) / ((1<<SCALE)-1)
 *
 * note Both tartget and reference clocks are selectable by programming the target clock select FREQMEAS_TARGET register
 * in INPUTMUX and reference clock select FREQMEAS_REF register in INPUTMUX.
 *
 * param base ANACTRL peripheral base address.
 * param scale Define the power of 2 count that ref counter counts to during measurement, ranges from 2 to 31.
 * param refClkFreq frequency of the reference clock.
 *
 * return frequency of the target clock.
 */
uint32_t ANACTRL_MeasureFrequency(ANACTRL_Type *base, uint8_t scale, uint32_t refClkFreq)
{
    assert(scale >= 2U);

    uint32_t targetClkFreq = 0U;
    uint32_t capval        = 0U;

    /* Init a measurement cycle. */
    base->FREQ_ME_CTRL = ANACTRL_FREQ_ME_CTRL_PROG_MASK + ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE(scale);
    while (ANACTRL_FREQ_ME_CTRL_PROG_MASK == (base->FREQ_ME_CTRL & ANACTRL_FREQ_ME_CTRL_PROG_MASK))
    {
    }

    /* Calculate the target clock frequency. */
    capval        = (base->FREQ_ME_CTRL & ANACTRL_FREQ_ME_CTRL_CAPVAL_SCALE_MASK);
    targetClkFreq = (capval * refClkFreq) / ((1UL << scale) - 1UL);

    return targetClkFreq;
}
#endif /* FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL */
