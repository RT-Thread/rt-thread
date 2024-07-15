/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 * 2024/07/08     Shell        Using CPUTIME as tick
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/cputime.h>
#include <encoding.h>
#include "sbi.h"

#ifdef RT_USING_KTIME
#include <ktime.h>
#endif

static volatile unsigned long tick_cycles = 0;

int tick_isr(void)
{
    rt_tick_increase();
    sbi_set_timer(clock_cpu_gettime() + tick_cycles);
    return 0;
}

/* BSP should config clockbase frequency */
RT_STATIC_ASSERT(defined_clockbase_freq, CPUTIME_TIMER_FREQ != 0);

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    /* calculate the tick cycles */
    tick_cycles = CPUTIME_TIMER_FREQ / RT_TICK_PER_SECOND;

    /* Clear the Supervisor-Timer bit in SIE */
    clear_csr(sie, SIP_STIP);

    /* Init riscv timer */
    riscv_cputime_init();

    /* Set timer */
    sbi_set_timer(clock_cpu_gettime() + tick_cycles);

#ifdef RT_USING_KTIME
    rt_ktime_cputimer_init();
#endif
    /* Enable the Supervisor-Timer bit in SIE */
    set_csr(sie, SIP_STIP);

    return 0;
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    unsigned long start_time;
    unsigned long end_time;
    unsigned long run_time;

    start_time = clock_cpu_gettime();
    end_time = start_time + us * (CPUTIME_TIMER_FREQ / 1000000);
    do
    {
        run_time = clock_cpu_gettime();
    } while(run_time < end_time);
}
