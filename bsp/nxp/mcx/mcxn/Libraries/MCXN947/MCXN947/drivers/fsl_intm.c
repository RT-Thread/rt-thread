/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_intm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.intm"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief  Fill in the INTM config struct with the default settings
 *
 * The default values are:
 * code
 *     config[0].irqnumber = NotAvail_IRQn;
 *     config[0].maxtimer = 1000U;
 *     config[1].irqnumber = NotAvail_IRQn;
 *     config[1].maxtimer = 1000U;
 *     config[2].irqnumber = NotAvail_IRQn;
 *     config[2].maxtimer = 1000U;
 *     config[3].irqnumber = NotAvail_IRQn;
 *     config[3].maxtimer = 1000U;
 *     config->enable = false;
 * endcode
 * param config Pointer to user's INTM config structure.
 */
void INTM_GetDefaultConfig(intm_config_t *config)
{
    assert(config);

    for (uint32_t i = 0; i < (uint32_t)FSL_FEATURE_INTM_MONITOR_COUNT; i++)
    {
        config->intm[i].irqnumber = NotAvail_IRQn;
        config->intm[i].maxtimer  = 1000U;
    }

    /* INTM cycle count timer mode disable*/
    config->enable = false;
}

/*!
 * brief Ungates the INTM clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the INTM driver.
 *
 * param base      INTM peripheral base address
 * param config    Pointer to user's INTM config structure.
 */
void INTM_Init(INTM_Type *base, const intm_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Intm);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    for (uint32_t i = 0U; i < (uint32_t)FSL_FEATURE_INTM_MONITOR_COUNT; i++)
    {
        base->MON[i].INTM_IRQSEL  = INTM_MON_INTM_IRQSEL_IRQ(config->intm[i].irqnumber);
        base->MON[i].INTM_LATENCY = INTM_MON_INTM_LATENCY_LAT(config->intm[i].maxtimer);
    }

    INTM_EnableCycleCount(base, config->enable);
}

/*!
 * brief Disables the INTM module.
 *
 * param base INTM peripheral base address
 */
void INTM_Deinit(INTM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the INTM clock*/
    CLOCK_DisableClock(kCLOCK_Intm);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
