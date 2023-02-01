/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dac.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dac_1"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for DAC module.
 *
 * @param base DAC peripheral base address
 */
static uint32_t DAC_GetInstance(LPDAC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to DAC bases for each instance. */
static LPDAC_Type *const s_dacBases[] = LPDAC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to DAC clocks for each instance. */
static const clock_ip_name_t s_dacClocks[] = LPDAC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DAC_GetInstance(LPDAC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dacBases); instance++)
    {
        if (s_dacBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dacBases));

    return instance;
}

/*!
 * brief Initialize the DAC module with common configuartion.
 *
 * The clock will be enabled in this function.
 *
 * param base DAC peripheral base address.
 * param config Pointer to configuration structure.
 */
void DAC_Init(LPDAC_Type *base, const dac_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32 = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dacClocks[DAC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the logic. */
    DAC_SetReset(base, kDAC_ResetLogic);
    DAC_ClearReset(base, kDAC_ResetLogic);

    /* Reset the FIFO. */
    DAC_SetReset(base, kDAC_ResetFIFO);
    DAC_ClearReset(base, kDAC_ResetFIFO);

    /* Configuration. */
    if (kDAC_FIFOTriggerBySoftwareMode == config->fifoTriggerMode)
    {
        tmp32 |= LPDAC_GCR_TRGSEL_MASK; /* Software trigger. */
    }
    switch (config->fifoWorkMode)
    {
        case kDAC_FIFOWorkAsNormalMode: /* Normal FIFO. */
            tmp32 |= LPDAC_GCR_FIFOEN_MASK;
            break;
        case kDAC_FIFOWorkAsSwingMode:
            tmp32 |= LPDAC_GCR_FIFOEN_MASK | LPDAC_GCR_SWMD_MASK; /* Enable swing mode. */
            break;
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
        case kDAC_FIFOWorkAsPeriodTriggerMode:
            tmp32 |= LPDAC_GCR_FIFOEN_MASK | LPDAC_GCR_PTGEN_MASK; /* Enable period trigger mode. */
            /* Set trigger number and width. */
            base->PCR =
                LPDAC_PCR_PTG_NUM(config->periodicTriggerNumber) | LPDAC_PCR_PTG_PERIOD(config->periodicTriggerWidth);
            break;
        case kDAC_FIFOWorkAsPeriodTriggerAndSwingMode:
            tmp32 |= LPDAC_GCR_FIFOEN_MASK | LPDAC_GCR_PTGEN_MASK | LPDAC_GCR_SWMD_MASK;
            /* Set trigger number and width. */
            base->PCR =
                LPDAC_PCR_PTG_NUM(config->periodicTriggerNumber) | LPDAC_PCR_PTG_PERIOD(config->periodicTriggerWidth);
            break;
#endif           /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
        default: /* kDAC_FIFODisabled. */
            break;
    }

#if defined(FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG) && FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG
    if (config->enableExternalTriggerSource)
    {
        tmp32 |= LPDAC_GCR_RCV_TRG_MASK; /* Use trigger source from another DAC. */
    }
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL) && FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL
    if (false == config->enableLowerLowPowerMode)
    {
        tmp32 |= LPDAC_GCR_BUF_SPD_CTRL_MASK; /* Enable low power. */
    }
#else
    if (config->enableLowPowerMode)
    {
        tmp32 |= LPDAC_GCR_LPEN_MASK; /* Enable low power. */
    }
#endif /* LPDAC_GCR_BUF_SPD_CTRL_MASK */

#if defined(FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN) && FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN
    tmp32 |= LPDAC_GCR_BUF_EN_MASK; /* Opamp is used as buffer. */
#endif                              /* FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC) && FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC
    /* Configure DAC sync cycles. */
    tmp32 |= LPDAC_GCR_LATCH_CYC(config->syncTime);
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC */
#if defined(FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT) && FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT
    tmp32 |= config->referenceCurrentSource;
#endif /* FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT */
    /* Set reference voltage source. */
    tmp32 |= LPDAC_GCR_DACRFS(config->referenceVoltageSource);

    base->GCR = tmp32;
    base->FCR = LPDAC_FCR_WML(config->fifoWatermarkLevel);

    /* Now, the DAC is disabled. It needs to be enabled in application. */
}

/*!
 * brief Get the default settings for initialization's configuration.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * code
 *   config->fifoWatermarkLevel = 0U;
 *   config->fifoTriggerMode = kDAC_FIFOTriggerByHardwareMode;
 *   config->fifoWorkMode = kDAC_FIFODisabled;
 *   config->enableLowPowerMode = false;
 *   config->referenceVoltageSource = kDAC_ReferenceVoltageSourceAlt1;
 * endcode
 *
 * param config Pointer to configuration structure.
 * param
 */
void DAC_GetDefaultConfig(dac_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->fifoWatermarkLevel = 0U;
    config->fifoTriggerMode    = kDAC_FIFOTriggerByHardwareMode;
    config->fifoWorkMode       = kDAC_FIFODisabled;

#if defined(FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG) && FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG
    config->enableExternalTriggerSource = false;
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL) && FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL
    config->enableLowerLowPowerMode = true;
#else
    config->enableLowPowerMode = false;
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL */
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
    config->periodicTriggerNumber = 0UL;
    config->periodicTriggerWidth  = 0UL;
#endif /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC) && FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC
    /* Configure DAC sync cycles. */
    config->syncTime = 1U;
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC */
#if defined(FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT) && FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT
    config->referenceCurrentSource = kDAC_ReferenceCurrentSourcePtat;
#endif /* FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT */
    config->referenceVoltageSource = kDAC_ReferenceVoltageSourceAlt1;
}

/*!
 * brief De-initialize the DAC module.
 *
 * The clock will be disabled in this function.
 *
 * param base DAC peripheral base address.
 * param
 */
void DAC_Deinit(LPDAC_Type *base)
{
    /* Disable the module. */
    DAC_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dacClocks[DAC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
