/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_opamp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.opamp"
#endif

#if defined(OPAMP_RSTS)
#define OPAMP_RESETS_ARRAY OPAMP_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t OPAMP_GetInstance(OPAMP_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static OPAMP_Type *const s_opampBases[] = OPAMP_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to OPAMP clocks for each instance. */
static const clock_ip_name_t s_opampClocks[] = OPAMP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(OPAMP_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_opampResets[] = OPAMP_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t OPAMP_GetInstance(OPAMP_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0UL; instance < ARRAY_SIZE(s_opampBases); instance++)
    {
        if (s_opampBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_opampBases));

    return instance;
}

/*!
 * brief Initialize OPAMP instance.
 *
 * param base OPAMP peripheral base address.
 * param config The pointer to opamp_config_t.
 */
void OPAMP_Init(OPAMP_Type *base, const opamp_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32 = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_opampClocks[OPAMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(OPAMP_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_opampResets[OPAMP_GetInstance(base)]);
#endif

    tmp32 = OPAMP_OPAMP_CTR_EN(config->enable) | OPAMP_OPAMP_CTR_MODE(config->mode) |
            OPAMP_OPAMP_CTR_BIASC(config->trimOption) | OPAMP_OPAMP_CTR_INTREF(config->intRefVoltage) |
            OPAMP_OPAMP_CTR_PREF(config->posRefVoltage) |
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW
            OPAMP_OPAMP_CTR_OUTSW(config->enableOutputSwitch) |
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1
            OPAMP_OPAMP_CTR_ADCSW1(config->enablePosADCSw1) |
#else
            OPAMP_OPAMP_CTR_ADCSW(config->enablePosADCSw) |
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2
            OPAMP_OPAMP_CTR_ADCSW2(config->enablePosADCSw2) |
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL
            OPAMP_OPAMP_CTR_INPSEL(config->PosInputChannelSelection) |
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD
            OPAMP_OPAMP_CTR_TRIGMD(config->enableTriggerMode) |
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD */
            OPAMP_OPAMP_CTR_NGAIN(config->negGain);
    base->OPAMP_CTR = tmp32;
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN
    if (config->enableRefBuffer)
    {
        assert((uint32_t)(config->posGain) <= 7UL);
        base->OPAMP_CTR |= OPAMP_OPAMP_CTR_PGAIN(config->posGain) | OPAMP_OPAMP_CTR_BUFEN_MASK;
    }
    else
    {
        if ((uint32_t)(config->posGain) > 7UL)
        {
            base->OPAMP_CTR |= OPAMP_OPAMP_CTR_PGAIN((uint32_t)(config->posGain) - 7UL);
        }
        else
        {
            assert((uint32_t)(config->posGain) == 0UL);
            base->OPAMP_CTR |= OPAMP_OPAMP_CTR_PGAIN(config->posGain);
        }
    }
#else
    base->OPAMP_CTR |= OPAMP_OPAMP_CTR_PGAIN(config->posGain);
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD */
}

/*!
 * brief De-initialize OPAMP instance.
 *
 * param base OPAMP peripheral base address.
 */
void OPAMP_Deinit(OPAMP_Type *base)
{
    /* Disable OPAMP instance. */
    base->OPAMP_CTR &= ~OPAMP_OPAMP_CTR_EN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_opampClocks[OPAMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get default configuration of OPAMP.
 *
 * code
 *     config->enable        = false;
 *     config->mode          = kOPAMP_LowNoiseMode;
 *     config->trimOption    = kOPAMP_TrimOptionDefault;
 *     config->intRefVoltage = kOPAMP_IntRefVoltVddaDiv2;
 *     config->enablePosADCSw = false;
 *     config->posRefVoltage = kOPAMP_PosRefVoltVrefh3;
 *     config->posGain       = kOPAMP_PosGainReserved;
 *     config->negGain       = kOPAMP_NegGainBufferMode;
 * endcode
 *
 * param config The pointer to opamp_config_t.
 */
void OPAMP_GetDefaultConfig(opamp_config_t *config)
{
    assert(config != NULL);

    config->enable        = false;
    config->mode          = kOPAMP_LowNoiseMode;
    config->trimOption    = kOPAMP_TrimOptionDefault;
    config->intRefVoltage = kOPAMP_IntRefVoltVddaDiv2;
    config->posRefVoltage = kOPAMP_PosRefVoltVrefh3;
    config->posGain       = kOPAMP_PosGainReserved;
    config->negGain       = kOPAMP_NegGainBufferMode;
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW
    config->enableOutputSwitch = true;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1
    config->enablePosADCSw1 = false;
#else
    config->enablePosADCSw = false;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2
    config->enablePosADCSw2 = false;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN
    config->enableRefBuffer = false;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL
    config->PosInputChannelSelection = kOPAMP_PosInputChannel0;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD
    config->enableTriggerMode = false;
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD */
}
