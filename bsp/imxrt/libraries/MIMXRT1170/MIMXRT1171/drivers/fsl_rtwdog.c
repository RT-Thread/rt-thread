/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rtwdog.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rtwdog"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Clears the RTWDOG flag.
 *
 * This function clears the RTWDOG status flag.
 *
 * Example to clear an interrupt flag:
 * code
 *   RTWDOG_ClearStatusFlags(wdog_base,kRTWDOG_InterruptFlag);
 * endcode
 * param base        RTWDOG peripheral base address.
 * param mask        The status flags to clear.
 *                    The parameter can be any combination of the following values:
 *                    arg kRTWDOG_InterruptFlag
 */
void RTWDOG_ClearStatusFlags(RTWDOG_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kRTWDOG_InterruptFlag) != 0U)
    {
        base->CS |= RTWDOG_CS_FLG_MASK;
    }
}

/*!
 * brief Initializes the RTWDOG configuration structure.
 *
 * This function initializes the RTWDOG configuration structure to default values. The default
 * values are:
 * code
 *   rtwdogConfig->enableRtwdog = true;
 *   rtwdogConfig->clockSource = kRTWDOG_ClockSource1;
 *   rtwdogConfig->prescaler = kRTWDOG_ClockPrescalerDivide1;
 *   rtwdogConfig->workMode.enableWait = true;
 *   rtwdogConfig->workMode.enableStop = false;
 *   rtwdogConfig->workMode.enableDebug = false;
 *   rtwdogConfig->testMode = kRTWDOG_TestModeDisabled;
 *   rtwdogConfig->enableUpdate = true;
 *   rtwdogConfig->enableInterrupt = false;
 *   rtwdogConfig->enableWindowMode = false;
 *   rtwdogConfig->windowValue = 0U;
 *   rtwdogConfig->timeoutValue = 0xFFFFU;
 * endcode
 *
 * param config Pointer to the RTWDOG configuration structure.
 * see rtwdog_config_t
 */
void RTWDOG_GetDefaultConfig(rtwdog_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableRtwdog         = true;
    config->clockSource          = kRTWDOG_ClockSource1;
    config->prescaler            = kRTWDOG_ClockPrescalerDivide1;
    config->workMode.enableWait  = true;
    config->workMode.enableStop  = false;
    config->workMode.enableDebug = false;
    config->testMode             = kRTWDOG_TestModeDisabled;
    config->enableUpdate         = true;
    config->enableInterrupt      = false;
    config->enableWindowMode     = false;
    config->windowValue          = 0U;
    config->timeoutValue         = 0xFFFFU;
}

/*!
 * brief Initializes the RTWDOG module.
 *
 * This function initializes the RTWDOG.
 * To reconfigure the RTWDOG without forcing a reset first, enableUpdate must be set to true
 * in the configuration.
 *
 * Example:
 * code
 *   rtwdog_config_t config;
 *   RTWDOG_GetDefaultConfig(&config);
 *   config.timeoutValue = 0x7ffU;
 *   config.enableUpdate = true;
 *   RTWDOG_Init(wdog_base,&config);
 * endcode
 *
 * param base   RTWDOG peripheral base address.
 * param config The configuration of the RTWDOG.
 */
void RTWDOG_Init(RTWDOG_Type *base, const rtwdog_config_t *config)
{
    assert(NULL != config);

    uint32_t value        = 0U;
    uint32_t primaskValue = 0U;

    /* Enable watch dog to start counting? */
    value |= ((config->enableRtwdog) ? RTWDOG_CS_EN_MASK : 0U);

    /* Enable watch dog interrupt? */
    value |= ((config->enableInterrupt) ? RTWDOG_CS_INT_MASK : 0U);

    /* Enable watch dog Window mode? */
    value |= ((config->enableWindowMode) ? RTWDOG_CS_WIN_MASK : 0U);

    /* Enable reconfigure watch dog without a reset? */
    value |= ((config->enableUpdate) ? RTWDOG_CS_UPDATE_MASK : 0U);

    /* Enable watch dog operate when the chip is in Debug mode? */
    value |= ((config->workMode.enableDebug) ? RTWDOG_CS_DBG_MASK : 0U);

    /* Enable watch dog operate when the chip is in Stop mode? */
    value |= ((config->workMode.enableStop) ? RTWDOG_CS_STOP_MASK : 0U);

    /* Enable watch dog operate when the chip is in Wait mode? */
    value |= ((config->workMode.enableWait) ? RTWDOG_CS_WAIT_MASK : 0U);

    /* Enable a fixed 256 prescaling of the watch dog counter reference clock? */
    value = (value & ~RTWDOG_CS_PRES_MASK) | RTWDOG_CS_PRES((uint32_t)config->prescaler);

    /* Select watch dog clock source. */
    value = (value & ~RTWDOG_CS_CLK_MASK) | RTWDOG_CS_CLK((uint32_t)config->clockSource);

    /* Select User mode or Test mode? */
    value = (value & ~RTWDOG_CS_TST_MASK) | RTWDOG_CS_TST((uint32_t)config->testMode);

    /* Enable support for 32-bit refresh or unlock command write words. */
    value |= RTWDOG_CS_CMD32EN(1U);

    /* Disable the global interrupts. Otherwise, an interrupt could effectively invalidate the unlock sequence
     * and the WCT may expire. After the configuration finishes, re-enable the global interrupts. */
    primaskValue = DisableGlobalIRQ();
    RTWDOG_Unlock(base);
    base->WIN   = config->windowValue;
    base->TOVAL = config->timeoutValue;
    base->CS    = value;
    while ((base->CS & RTWDOG_CS_RCS_MASK) == 0U)
    {
    }
    EnableGlobalIRQ(primaskValue);
}

/*!
 * brief De-initializes the RTWDOG module.
 *
 * This function shuts down the RTWDOG.
 * Ensure that the WDOG_CS.UPDATE is 1, which means that the register update is enabled.
 *
 * param base   RTWDOG peripheral base address.
 */
void RTWDOG_Deinit(RTWDOG_Type *base)
{
    uint32_t primaskValue = 0U;

    /* Disable the global interrupts */
    primaskValue = DisableGlobalIRQ();
    RTWDOG_Unlock(base);
    RTWDOG_Disable(base);
    while ((base->CS & RTWDOG_CS_RCS_MASK) == 0U)
    {
    }
    EnableGlobalIRQ(primaskValue);
}
