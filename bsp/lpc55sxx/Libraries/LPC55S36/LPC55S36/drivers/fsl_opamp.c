/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_opamp.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.opamp"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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

    uint32_t tmp32;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_opampClocks[OPAMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    tmp32 = base->OPAMP_CTR;
    tmp32 &= ~(OPAMP_OPAMP_CTR_EN_MASK | OPAMP_OPAMP_CTR_MODE_MASK | OPAMP_OPAMP_CTR_BIASC_MASK |
               OPAMP_OPAMP_CTR_INTREF_MASK | OPAMP_OPAMP_CTR_ADCSW_MASK | OPAMP_OPAMP_CTR_PREF_MASK |
               OPAMP_OPAMP_CTR_PGAIN_MASK | OPAMP_OPAMP_CTR_NGAIN_MASK);
    tmp32 |= OPAMP_OPAMP_CTR_EN(config->enable) | OPAMP_OPAMP_CTR_MODE(config->mode) |
             OPAMP_OPAMP_CTR_BIASC(config->trimOption) | OPAMP_OPAMP_CTR_INTREF(config->intRefVoltage) |
             OPAMP_OPAMP_CTR_ADCSW(config->enablePosADCSw) | OPAMP_OPAMP_CTR_PREF(config->posRefVoltage) |
             OPAMP_OPAMP_CTR_PGAIN(config->posGain) | OPAMP_OPAMP_CTR_NGAIN(config->negGain);
    base->OPAMP_CTR = tmp32;
}

/*!
 * brief De-initialize OPAMP instance.
 *
 * param base OPAMP peripheral base address.
 */
void OPAMP_Deinit(OPAMP_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_opampClocks[OPAMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable OPAMP instance. */
    base->OPAMP_CTR &= ~OPAMP_OPAMP_CTR_EN_MASK;
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

    config->enablePosADCSw = false;
    config->posRefVoltage  = kOPAMP_PosRefVoltVrefh3;
    config->posGain        = kOPAMP_PosGainReserved;

    config->negGain = kOPAMP_NegGainBufferMode;
}
