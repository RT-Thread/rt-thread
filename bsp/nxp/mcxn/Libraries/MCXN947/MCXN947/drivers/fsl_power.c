/*
 * Copyright 2022, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Codes
 ******************************************************************************/

/*******************************************************************************
 * LOCAL FUNCTIONS PROTOTYPES
 ******************************************************************************/

/**
 * brief    PMC Sleep function call
 * return   nothing
 */
void POWER_EnterSleep(void)
{
    uint32_t pmsk;
    pmsk = __get_PRIMASK();
    __disable_irq();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
    __set_PRIMASK(pmsk);
}

/**
 * brief    PMC Deep Sleep function call
 * return   nothing
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t hardware_wake_ctrl)
{
}

/**
 * brief    PMC power Down function call
 * return   nothing
 */
void POWER_EnterPowerDown(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t cpu_retention_ctrl)
{
}

/**
 * brief    PMC Deep Sleep Power Down function call
 * return   nothing
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd,
                              uint32_t sram_retention_ctrl,
                              uint64_t wakeup_interrupts,
                              uint32_t wakeup_io_ctrl)
{
}

/**
 * @brief             Described in fsl_common.h
 * @param
 * @return
 */
void POWER_SetVoltageForFreq(uint32_t system_freq_hz)
{
}
