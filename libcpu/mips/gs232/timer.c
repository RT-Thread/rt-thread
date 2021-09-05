/*
 * Assembly Macros For MIPS
 *
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#include <rtthread.h>
#include <rthw.h>
#include <mips.h>
#include <board.h>

/**
 * This is the timer interrupt service routine.
 */
void rt_hw_timer_handler(void)
{
    unsigned int count;

    count = read_c0_compare();
    write_c0_compare(count);
    write_c0_count(0);

    /* increase a OS tick */
    rt_tick_increase();
}

/**
 * This function will initial OS timer
 */
void rt_hw_timer_init(void)
{
    write_c0_compare(CPU_HZ/2/RT_TICK_PER_SECOND);
    write_c0_count(0);
    mips_unmask_cpu_irq(7);
}
