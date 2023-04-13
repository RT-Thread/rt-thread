/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>
#include "interrupt.h"

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

#define GTIMER_IRQ                      (27)

static uint64_t _tickval[RT_CPUS_NR];
static uint64_t _increaseval[RT_CPUS_NR];
#define tickval _tickval[cpu_id]
#define increaseval _increaseval[cpu_id]

/**
 * This function is the gtimer isr handler.
 *
 * @param vector interrupt ID
 * @param parameter the parameter specified by rt_hw_interrupt_install
 *
 * @return none
 */
static void _hw_timer_isr(int vector, void *parameter)
{
#ifdef RT_USING_SMP
    int cpu_id = rt_hw_cpu_id();
#else
    int cpu_id = 0;
#endif
    uint64_t cntvct_el0;
    do
    {
        tickval += increaseval;
        __asm__ volatile("msr CNTV_CVAL_EL0, %0"::"r"(tickval));
        __asm__ volatile("mrs %0, CNTVCT_EL0":"=r"(cntvct_el0));
    } while (cntvct_el0 >= tickval);
    rt_tick_increase();
}

/**
 * The function will initialize the general timer used for the system tick.
 *
 * @param none
 *
 * @return none
 */
rt_weak int rt_hw_gtimer_init(void)
{
#ifdef RT_USING_SMP
    int cpu_id = rt_hw_cpu_id();
#else
    int cpu_id = 0;
#endif
    uint64_t val;

    rt_hw_interrupt_install(GTIMER_IRQ, _hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(GTIMER_IRQ);

    __asm__ volatile("mrs %0, CNTFRQ_EL0":"=r"(val));
    increaseval = val / RT_TICK_PER_SECOND;

    __asm__ volatile("msr CNTV_CTL_EL0, %0"::"r"(val));
    tickval = increaseval;
    __asm__ volatile("msr CNTV_CVAL_EL0, %0"::"r"(tickval));
    val = 1;
    __asm__ volatile("msr CNTV_CTL_EL0, %0"::"r"(val));
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_gtimer_init);
