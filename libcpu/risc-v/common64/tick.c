/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 * 2024/07/08     Shell        Using clock_time as tick
 */

#include <rthw.h>
#include <rtthread.h>

#include <encoding.h>
#include "sbi.h"

#ifdef RT_USING_CLOCK_TIME
#include <drivers/clock_time.h>
#endif

static volatile unsigned long tick_cycles = 0;
static rt_uint64_t _clock_timer_freq = 0;

rt_weak rt_uint64_t rt_hw_get_clock_timer_freq(void)
{
    return CLOCK_TIMER_FREQ;
}

static rt_uint64_t _riscv_read_time(void)
{
    unsigned long time_elapsed;

    __asm__ __volatile__("rdtime %0" : "=r"(time_elapsed));
    return (rt_uint64_t)time_elapsed;
}

int tick_isr(void)
{
    rt_tick_increase();
    sbi_set_timer(_riscv_read_time() + tick_cycles);
    return 0;
}

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    rt_uint64_t freq = rt_hw_get_clock_timer_freq();
    RT_ASSERT(freq != 0);

    _clock_timer_freq = freq;

    /* calculate the tick cycles */
    tick_cycles = freq / RT_TICK_PER_SECOND;

    /* Clear the Supervisor-Timer bit in SIE */
    clear_csr(sie, SIP_STIP);

    /* Set timer */
    sbi_set_timer(_riscv_read_time() + tick_cycles);

#ifdef RT_USING_CLOCK_TIME
    rt_clock_time_source_init();
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
    rt_uint64_t freq;

    start_time = _riscv_read_time();
    freq = _clock_timer_freq ? _clock_timer_freq : rt_hw_get_clock_timer_freq();
    RT_ASSERT(freq != 0);
    end_time = start_time + (rt_uint64_t)us * freq / 1000000ULL;
    do
    {
        run_time = _riscv_read_time();
    } while(run_time < end_time);
}
