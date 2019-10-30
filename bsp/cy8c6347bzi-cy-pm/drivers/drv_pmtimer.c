/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2017-08-01     tanek           the first version
 */

#include "board.h"
#include "project.h"
#include <rtdevice.h>
#include <drivers/pm.h>


/**
 * Handler function for the lp timer interrupt.
 */
void psoc6_lptim_interrupt_handler(void)
{
    /* Clear the MCWDT peripheral interrupt */
    MCWDT_ClearInterrupt(MCWDT_CTRS_INT_MASK);
    
    /* enter interrupt */
    rt_interrupt_enter();

    rt_pm_exit();
    
    /* leave interrupt */
    rt_interrupt_leave();
    
    /* Clear the NVIC pending interrupt for MCWDT */
    NVIC_ClearPendingIRQ(MCWDT_isr_cfg.intrSrc);
}

/**
 * This function get current count value of LPTIM
 *
 * @return the count vlaue
 */
rt_uint32_t psoc6_lptim_get_current_tick(void)
{
    return MCWDT_GetCount(CY_MCWDT_COUNTER1);
}

/**
 * This function get the max value that LPTIM can count
 *
 * @return the max count
 */
rt_uint32_t psoc6_lptim_get_tick_max(void)
{
    return (0xFFFF);
}

/**
 * This function start LPTIM with reload value
 *
 * @param reload The value that LPTIM count down from
 *
 * @return RT_EOK
 */
rt_err_t psoc6_lptim_start(rt_uint32_t reload)
{
    if(1 == MCWDT_GetEnabledStatus(CY_MCWDT_COUNTER1))
    {
        return RT_EBUSY;
    }
    cy_stc_mcwdt_config_t wdt_config = MCWDT_config;
    wdt_config.c1Match = reload;
    /* Set interrupt masks for the counters */
    MCWDT_SetInterruptMask(MCWDT_CTRS_INT_MASK);
    MCWDT_Init(&wdt_config);
    /* Enable the counters that are enabled in the customizer */
    MCWDT_Enable(MCWDT_ENABLED_CTRS_MASK, MCWDT_TWO_LF_CLK_CYCLES_DELAY);
    return (RT_EOK);
}

/**
 * This function stop LPTIM
 */
void psoc6_lptim_stop(void)
{
    MCWDT_Disable(CY_MCWDT_CTR_Msk, MCWDT_TWO_LF_CLK_CYCLES_DELAY);
    MCWDT_DeInit();
}

/**
 * This function get the count clock of LPTIM
 *
 * @return the count clock frequency in Hz
 */
rt_uint32_t psoc6_lptim_get_countfreq(void)
{
    return 32768/128;
}

/**
 * This function initialize the lptim
 */
int psoc6_hw_lptim_init(void)
{
    /* Configure ISR connected to MCWDT interrupt signal*/
    /* MCWDT_isr_cfg structure is defined by the SYSINT_PDL component based on
       parameters entered in the customizer. */
    Cy_SysInt_Init(&MCWDT_isr_cfg, &psoc6_lptim_interrupt_handler);
    /* Clear CM4 NVIC pending interrupt for MCWDT */
    NVIC_ClearPendingIRQ(MCWDT_isr_cfg.intrSrc);
    /* Enable CM4 NVIC MCWDT interrupt */
    NVIC_EnableIRQ(MCWDT_isr_cfg.intrSrc);
    
    return 0;
}
INIT_BOARD_EXPORT(psoc6_hw_lptim_init);
