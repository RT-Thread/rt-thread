/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-11-01     wangyq          first version
 */

#include <board.h>
#include <drv_lptim.h>
#include <ald_lptim.h>

static lptim_handle_t h_lptim;

void LPTIM0_SPI2_Handler(void)
{
    /* LPTIM Intetrupt */
    if (ald_lptim_get_it_status(&h_lptim, LPTIM_IT_ARRMAT) &&
            ald_lptim_get_flag_status(&h_lptim, LPTIM_FLAG_ARRMAT))
    {
        /* enter interrupt */
        rt_interrupt_enter();

        ald_lptim_clear_flag_status(&h_lptim, LPTIM_FLAG_ARRMAT);

        /* leave interrupt */
        rt_interrupt_leave();
    }
}

/**
 * This function get current count value of LPTIM
 *
 * @return the count vlaue
 */
rt_uint32_t es32f0_lptim_get_current_tick(void)
{
    return READ_REG(h_lptim.perh->CNT);
}

/**
 * This function get the max value that LPTIM can count
 *
 * @return the max count
 */
rt_uint32_t es32f0_lptim_get_tick_max(void)
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
rt_err_t es32f0_lptim_start(rt_uint32_t reload)
{
    h_lptim.init.arr = reload;
    ald_lptim_toggle_start_by_it(&h_lptim);

    return (RT_EOK);
}

/**
 * This function stop LPTIM
 */
void es32f0_lptim_stop(void)
{
    ald_lptim_toggle_stop_by_it(&h_lptim);
}

/**
 * This function get the count clock of LPTIM
 *
 * @return the count clock frequency in Hz
 */
rt_uint32_t es32f0_lptim_get_countfreq(void)
{
    return 1000000;
}

/**
 * This function initialize the lptim
 */
int es32f0_hw_lptim_init(void)
{
    lptim_clock_source_init_t clock_config;
    lptim_trigger_init_t trigger_config;

    /* Enable LPTIM clock */
    ald_cmu_perh_clock_config(CMU_PERH_LPTIM0, ENABLE);

    /* LPTIM Configuration */
    h_lptim.perh       = LPTIM0;
    h_lptim.init.psc   = LPTIM_PRESC_1;           // can not select other premeter
    h_lptim.init.arr   = 0x0FFF;
    h_lptim.init.clock = CMU_LP_PERH_CLOCK_SEL_HRC_1M;
    h_lptim.init.mode  = LPTIM_MODE_SINGLE;

    ald_lptim_toggle_init(&h_lptim);

    /* Initialize clock source */
    clock_config.sel      = LPTIM_CKSEL_INTERNAL;
    clock_config.polarity = LPTIM_CKPOL_RISING;
    ald_lptim_clock_source_config(&h_lptim, &clock_config);

    /* Initialize toggle */
    trigger_config.mode = LPTIM_TRIGEN_SW;
    ald_lptim_trigger_config(&h_lptim, &trigger_config);

    ald_lptim_interrupt_config(&h_lptim, LPTIM_IT_ARRMAT, ENABLE);

    NVIC_ClearPendingIRQ(LPTIM0_SPI2_IRQn);
    NVIC_SetPriority(LPTIM0_SPI2_IRQn, 0);
    NVIC_EnableIRQ(LPTIM0_SPI2_IRQn);

    return 0;
}

INIT_DEVICE_EXPORT(es32f0_hw_lptim_init);
