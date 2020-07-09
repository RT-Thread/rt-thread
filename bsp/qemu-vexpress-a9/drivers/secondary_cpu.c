/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     Jesven       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"
#include "gic.h"
#include "drv_timer.h"

#ifdef RT_USING_SMP
#include <interrupt.h>

static void rt_hw_timer2_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    timer_clear_pending(0);
}

void rt_hw_secondary_cpu_up(void)
{
    extern void set_secondary_cpu_boot_address(void);

    set_secondary_cpu_boot_address();
    __asm__ volatile ("dsb":::"memory");
    rt_hw_ipi_send(0, 1 << 1);
}

void secondary_cpu_c_start(void)
{
    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0, REALVIEW_GIC_CPU_BASE);
    arm_gic_set_cpu(0, IRQ_PBA8_TIMER0_1, 0x2);

    timer_init(0, 10000);
    rt_hw_interrupt_install(IRQ_PBA8_TIMER0_1, rt_hw_timer2_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_PBA8_TIMER0_1);

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
     asm volatile ("wfe":::"memory", "cc");
}

#endif
