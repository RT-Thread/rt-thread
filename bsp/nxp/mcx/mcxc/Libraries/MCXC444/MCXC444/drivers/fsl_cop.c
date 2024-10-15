/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cop.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cop"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Initializes the COP configuration structure.
 *
 * This function initializes the COP configuration structure to default values. The default
 * values are:
 * code
 *   copConfig->enableWindowMode = false;
 *   copConfig->timeoutMode = kCOP_LongTimeoutMode;
 *   copConfig->enableStop = false;
 *   copConfig->enableDebug = false;
 *   copConfig->clockSource = kCOP_LpoClock;
 *   copConfig->timeoutCycles = kCOP_2Power10CyclesOr2Power18Cycles;
 * endcode
 *
 * param config Pointer to the COP configuration structure.
 * see cop_config_t
 */
void COP_GetDefaultConfig(cop_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableWindowMode = false;
#if defined(FSL_FEATURE_COP_HAS_LONGTIME_MODE) && FSL_FEATURE_COP_HAS_LONGTIME_MODE
    config->timeoutMode = kCOP_LongTimeoutMode;
    config->enableStop  = false;
    config->enableDebug = false;
#endif /* FSL_FEATURE_COP_HAS_LONGTIME_MODE */
    config->clockSource   = kCOP_LpoClock;
    config->timeoutCycles = kCOP_2Power10CyclesOr2Power18Cycles;
}

/*!
 * brief Initializes the COP module.
 *
 * This function configures the COP. After it is called, the COP
 * starts running according to the configuration.
 * Because all COP control registers are write-once only, the COP_Init function
 * and the COP_Disable function can be called only once. A second call has no effect.
 *
 * Example:
 * code
 *  cop_config_t config;
 *  COP_GetDefaultConfig(&config);
 *  config.timeoutCycles = kCOP_2Power8CyclesOr2Power16Cycles;
 *  COP_Init(sim_base,&config);
 * endcode
 *
 * param base   SIM peripheral base address.
 * param config The configuration of COP.
 */
void COP_Init(SIM_Type *base, const cop_config_t *config)
{
    assert(NULL != config);

    uint32_t value = 0U;

#if defined(FSL_FEATURE_COP_HAS_LONGTIME_MODE) && FSL_FEATURE_COP_HAS_LONGTIME_MODE
    value = SIM_COPC_COPW(config->enableWindowMode) | SIM_COPC_COPCLKS(config->timeoutMode) |
            SIM_COPC_COPT(config->timeoutCycles) | SIM_COPC_COPSTPEN(config->enableStop) |
            SIM_COPC_COPDBGEN(config->enableDebug) | SIM_COPC_COPCLKSEL(config->clockSource);
#else
    value = SIM_COPC_COPW(config->enableWindowMode) | SIM_COPC_COPCLKS(config->clockSource) |
            SIM_COPC_COPT(config->timeoutCycles);
#endif /* FSL_FEATURE_COP_HAS_LONGTIME_MODE */
    base->COPC = value;
}

/*!
 * brief Refreshes the COP timer
 *
 * This function feeds the COP.
 *
 * param base  SIM peripheral base address.
 */
void COP_Refresh(SIM_Type *base)
{
    uint32_t primaskValue = 0U;

    /* Disable the global interrupt to protect refresh sequence */
    primaskValue = DisableGlobalIRQ();
    base->SRVCOP = COP_FIRST_BYTE_OF_REFRESH;
    base->SRVCOP = COP_SECOND_BYTE_OF_REFRESH;
    EnableGlobalIRQ(primaskValue);
}
