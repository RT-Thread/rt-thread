/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "drv_timer.h"
#include "interrupt.h"
#include "common.h"

#include <rthw.h>
#include <rtthread.h>

/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_systick_isr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * The function initial system timer interrupt.
 */
void rt_hw_system_timer_init(void)
{
    // initial system timer interrupt, map local timer interrupt to INT14
    gp_cgem_regs->INTMUX3 = (CSL_GEM_TINTLN << CSL_CGEM_INTMUX3_INTSEL14_SHIFT);
    // enable CPU INT14
    rt_hw_interrupt_umask(1 << 14);

    return ;
}

/**
 * The function initial system timer.
 * Use local timer (== DNUM of a core) to generate a clock on TIMO0,interrupts are generated as well
 *
 */
void rt_hw_system_timer_start(void)
{
    Timer64_Config tmrCfg;

    // select output on TIMO0 from local timer.
    gp_bootcfg_regs->TOUTSEL = (DNUM*2) << CSL_BOOTCFG_TOUTSEL_TOUTSEL0_SHIFT;

    // configure the timer to generate clocks and interrupts
    tmrCfg.timer_num = DNUM;
    tmrCfg.timerMode = TIMER_PERIODIC_CLOCK;
    tmrCfg.period = (unsigned long long) RT_TICK_PER_SECOND * DSP_CORE_SPEED_HZ / 6000;
    tmrCfg.reload_period = 0;

    // initial timer
    timer64_init(&tmrCfg);
}
