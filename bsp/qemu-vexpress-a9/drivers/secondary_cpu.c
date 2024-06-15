/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#ifdef RT_USING_SMART
#include <mmu.h>
#endif

static void rt_hw_timer2_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    timer_clear_pending(0);
}

void rt_hw_secondary_cpu_up(void)
{
    volatile void **plat_boot_reg = (volatile void **)0x10000034;
    char *entry = (char *)rt_secondary_cpu_entry;

#ifdef RT_USING_SMART
    plat_boot_reg = (volatile void **)rt_ioremap_nocache((void *)plat_boot_reg, 0x1000);
    if (!plat_boot_reg)
    {
        /* failed */
        return;
    }
    entry += PV_OFFSET;
#endif
    *plat_boot_reg-- = (void *)(size_t)-1;
    *plat_boot_reg = (void *)entry;
    rt_hw_dsb();
    rt_hw_ipi_send(0, RT_CPU_MASK ^ (1 << rt_hw_cpu_id()));
}
extern size_t MMUTable[];
/* Interface */
void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);
    rt_uint32_t mmutable_p;
    mmutable_p = (rt_uint32_t)MMUTable + (rt_uint32_t)PV_OFFSET ;
    rt_hw_mmu_switch((void*)mmutable_p) ;
    arm_gic_cpu_init(0, 0);
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
