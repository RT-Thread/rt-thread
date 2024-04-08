/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dac12.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dac12"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for DAC12 module.
 *
 * @param base DAC12 peripheral base address
 */
static uint32_t DAC12_GetInstance(DAC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to DAC bases for each instance. */
static DAC_Type *const s_dac12Bases[] = DAC_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to DAC clocks for each instance. */
static const clock_ip_name_t s_dac12Clocks[] = DAC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t DAC12_GetInstance(DAC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dac12Bases); instance++)
    {
        if (s_dac12Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dac12Bases));

    return instance;
}

/*!
 * brief Get hardware information about this module.
 *
 * param base DAC12 peripheral base address.
 * param info Pointer to info structure, see to #dac12_hardware_info_t.
 */
void DAC12_GetHardwareInfo(DAC_Type *base, dac12_hardware_info_t *info)
{
    assert(NULL != info);

    info->fifoSizeInfo =
        (dac12_fifo_size_info_t)(uint32_t)((DAC_PARAM_FIFOSZ_MASK & base->PARAM) >> DAC_PARAM_FIFOSZ_SHIFT);
}

/*!
 * brief Initialize the DAC12 module.
 *
 * param base DAC12 peripheral base address.
 * param config Pointer to configuration structure, see to #dac12_config_t.
 */
void DAC12_Init(DAC_Type *base, const dac12_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dac12Clocks[DAC12_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    tmp32 = DAC_CR_WML(config->fifoWatermarkLevel); /* FIFO watermark level. */
    switch (config->fifoWorkMode)                   /* FIFO work mode. */
    {
        case kDAC12_FIFOWorkAsNormalMode:
            tmp32 |= DAC_CR_FIFOEN_MASK;
            break;
        case kDAC12_FIFOWorkAsSwingMode:
            tmp32 |= DAC_CR_FIFOEN_MASK | DAC_CR_SWMD_MASK;
            break;
        default: /* kDAC12_FIFODisabled. */
            break;
    }

    tmp32 |= DAC_CR_DACRFS(config->referenceVoltageSource) /* Reference voltage source. */
             | DAC_CR_TRGSEL(config->fifoTriggerMode);     /* Trigger mode. */

    base->CR = tmp32;

    /* DACx_CR2. */
    tmp32 = 0U;
    /* Reference voltage current. */
    switch (config->referenceCurrentSource)
    {
        case kDAC12_ReferenceCurrentSourceAlt0:
            tmp32 |= DAC_CR2_IREF_MASK;
            break;
        case kDAC12_ReferenceCurrentSourceAlt1:
            tmp32 |= DAC_CR2_IREF1_MASK;
            break;
        case kDAC12_ReferenceCurrentSourceAlt2:
            tmp32 |= DAC_CR2_IREF2_MASK;
            break;
        default: /* kDAC12_ReferenceCurrentSourceDisabled */
            break;
    }

    /* Speed mode. */
    switch (config->speedMode)
    {
        case kDAC12_SpeedMiddleMode:
            tmp32 |= DAC_CR2_BFMS_MASK;
            break;
        case kDAC12_SpeedHighMode:
            tmp32 |= DAC_CR2_BFHS_MASK;
            break;
        default: /* kDAC12_SpeedLowMode */
            break;
    }

    /* DAC buffered mode needs OPAMP enabled. DAC unbuffered mode needs OPAMP disabled. */
    if (config->enableAnalogBuffer)
    {
        tmp32 |= DAC_CR2_BFEN_MASK; /* OPAMP is used as buffer. */
    }
    else
    {
        tmp32 |= DAC_CR2_OEN_MASK; /* Output buffer is bypassed. */
    }
    base->CR2 = tmp32;

#if !(defined(FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER) && FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER)
    base->ITRM = DAC_ITRM_TRIM(config->currentReferenceInternalTrimValue);
#endif /* FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER */
}

/*!
 * brief De-initialize the DAC12 module.
 *
 * param base DAC12 peripheral base address.
 */
void DAC12_Deinit(DAC_Type *base)
{
    DAC12_Enable(base, false);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_dac12Clocks[DAC12_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initializes the DAC12 user configuration structure.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * code
 *   config->fifoWatermarkLevel = 0U;
 *   config->fifoWorkMode = kDAC12_FIFODisabled;
 *   config->referenceVoltageSource = kDAC12_ReferenceVoltageSourceAlt1;
 *   config->fifoTriggerMode = kDAC12_FIFOTriggerByHardwareMode;
 *   config->referenceCurrentSource = kDAC12_ReferenceCurrentSourceAlt0;
 *   config->speedMode = kDAC12_SpeedLowMode;
 *   config->speedMode = false;
 *   config->currentReferenceInternalTrimValue = 0x4;
 * endcode
 * param config Pointer to the configuration structure. See "dac12_config_t".
 */
void DAC12_GetDefaultConfig(dac12_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->fifoWatermarkLevel     = 0U;
    config->fifoWorkMode           = kDAC12_FIFODisabled;
    config->referenceVoltageSource = kDAC12_ReferenceVoltageSourceAlt1;
    config->fifoTriggerMode        = kDAC12_FIFOTriggerByHardwareMode;
    config->referenceCurrentSource = kDAC12_ReferenceCurrentSourceAlt0;
    config->speedMode              = kDAC12_SpeedLowMode;
    config->enableAnalogBuffer     = false;
#if !(defined(FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER) && FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER)
    config->currentReferenceInternalTrimValue = 0x4;
#endif /* FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER */
}
