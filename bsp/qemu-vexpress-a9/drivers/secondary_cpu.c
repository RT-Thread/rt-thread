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

#ifdef RT_USING_USERSPACE
#include <mmu.h>
#endif

static void rt_hw_timer2_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    timer_clear_pending(0);
}

#ifdef RT_USING_USERSPACE
extern void set_secondary_cpu_boot_address(uint32_t pv_off, void *second_boot_reg);
#else
extern void set_secondary_cpu_boot_address(void);
#endif

void rt_hw_secondary_cpu_up(void)
{
#ifdef RT_USING_USERSPACE
    void *plat_boot_reg;

    plat_boot_reg = rt_hw_mmu_map(&mmu_info, 0, (void*)0x10000034, 0x1000, MMU_MAP_K_RW);
    set_secondary_cpu_boot_address(PV_OFFSET, plat_boot_reg);
#else
    extern void set_secondary_cpu_boot_address(void);
#endif
    __asm__ volatile ("dsb":::"memory");
    rt_hw_ipi_send(0, 1 << 1);
}

void secondary_cpu_c_start(void)
{
    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);

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
