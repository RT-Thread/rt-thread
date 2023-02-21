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
#include "sbi.h"

static volatile uint64_t time_elapsed = 0;
static volatile unsigned long tick_cycles = 0;

static uint64_t get_ticks()
{
    __asm__ __volatile__(
        "rdtime %0"
        : "=r"(time_elapsed));
    return time_elapsed;
}

int tick_isr(void)
{
    // uint64_t core_id = current_coreid();
    int tick_cycles = 40000;
    // clint->mtimecmp[core_id] += tick_cycles;
    rt_tick_increase();
    sbi_set_timer(get_ticks() + tick_cycles);

    return 0;
}

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    /* Read core id */
    // unsigned long core_id = current_coreid();
    unsigned long interval = 1000/RT_TICK_PER_SECOND;

    /* Clear the Supervisor-Timer bit in SIE */
    clear_csr(sie, SIP_STIP);

    /* calculate the tick cycles */
    // tick_cycles = interval * sysctl_clock_get_freq(SYSCTL_CLOCK_CPU) / CLINT_CLOCK_DIV / 1000ULL - 1;
    tick_cycles = 40000;
    /* Set timer */
    sbi_set_timer(get_ticks() + tick_cycles);

    /* Enable the Supervisor-Timer bit in SIE */
    set_csr(sie, SIP_STIP);

    return 0;
}
