/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <encoding.h>
#include "tick.h"

static volatile rt_uint64_t time_elapsed = 0;
static volatile unsigned long tick_cycles = 0;

#define CLINT_BASE (BSP_PLIC_PHY_ADDR + 0x4000000UL)

static volatile rt_uint32_t *mtimecmp_l = (volatile rt_uint32_t *)(CLINT_BASE + 0x4000UL);
static volatile rt_uint32_t *mtimecmp_h = (volatile rt_uint32_t *)(CLINT_BASE + 0x4004UL);

rt_inline void set_ticks(rt_uint64_t value)
{
    *mtimecmp_l = 0xFFFFFFFF;
    *mtimecmp_h = (rt_uint32_t)(value >> 32);
    *mtimecmp_l = (rt_uint32_t)(value & 0xFFFFFFFF);
}

static rt_uint64_t get_ticks(void)
{
    __asm__ __volatile__(
        "rdtime %0"
        : "=r"(time_elapsed));
    return time_elapsed;
}

int rt_hw_tick_isr(void)
{
    rt_tick_increase();
    set_ticks(get_ticks() + tick_cycles);
    return 0;
}

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    /* Clear the Machine-Timer bit in MIE */
    clear_csr(mie, MIP_MTIP);

    tick_cycles = BSP_TIMER_CLK_FREQ / RT_TICK_PER_SECOND;

    set_ticks(get_ticks() + tick_cycles);

    rt_kprintf("[rt_hw_tick_init] time_elapsed: %d tick_cycles:%d\n", time_elapsed, tick_cycles);

    /* Enable the Machine-Timer bit in MIE */
    set_csr(mie, MIP_MTIP);

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

    start_time = get_ticks();
    end_time = start_time + us * (BSP_TIMER_CLK_FREQ / 1000000);
    do{
        run_time = get_ticks();
    } while(run_time < end_time);
}
