/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-20     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <gtimer.h>
#include <cpuport.h>

#ifdef RT_USING_KTIME
#include <ktime.h>
#endif

#define EL1_PHY_TIMER_IRQ_NUM 30

static volatile rt_uint64_t timer_step;

static void rt_hw_timer_isr(int vector, void *parameter)
{
    rt_hw_set_gtimer_val(timer_step);
    rt_tick_increase();
}

void rt_hw_gtimer_init(void)
{
    rt_hw_interrupt_install(EL1_PHY_TIMER_IRQ_NUM, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_isb();
    timer_step = rt_hw_get_gtimer_frq();
    rt_hw_dsb();
    timer_step /= RT_TICK_PER_SECOND;
    rt_hw_gtimer_local_enable();
}

void rt_hw_gtimer_local_enable(void)
{
    rt_hw_gtimer_disable();
    rt_hw_set_gtimer_val(timer_step);
    rt_hw_interrupt_umask(EL1_PHY_TIMER_IRQ_NUM);
#ifdef RT_USING_KTIME
    rt_ktime_cputimer_init();
#endif
    rt_hw_gtimer_enable();
}

void rt_hw_gtimer_local_disable(void)
{
    rt_hw_gtimer_disable();
    rt_hw_interrupt_mask(EL1_PHY_TIMER_IRQ_NUM);
}
