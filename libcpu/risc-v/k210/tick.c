/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 */

#include <rthw.h>
#include <rtthread.h>

#include <encoding.h>
#include <clint.h>
#include <sysctl.h>

static volatile unsigned long tick_cycles = 0;
int tick_isr(void)
{
    uint64_t core_id = current_coreid();

    clint->mtimecmp[core_id] += tick_cycles;
    rt_tick_increase();

    return 0;
}

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    /* Read core id */
    unsigned long core_id = current_coreid();
    unsigned long interval = 1000/RT_TICK_PER_SECOND;

    /* Clear the Machine-Timer bit in MIE */
    clear_csr(mie, MIP_MTIP);

    /* calculate the tick cycles */
    tick_cycles = interval * sysctl_clock_get_freq(SYSCTL_CLOCK_CPU) / CLINT_CLOCK_DIV / 1000ULL - 1;
    /* Set mtimecmp by core id */
    clint->mtimecmp[core_id] = clint->mtime + tick_cycles;

    /* Enable the Machine-Timer bit in MIE */
    set_csr(mie, MIP_MTIP);

    return 0;
}
