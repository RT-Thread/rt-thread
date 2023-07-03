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

#ifdef RT_USING_SMP
#include <stdint.h>

#include "board.h"
#include "gicv3.h"
#include <mmu.h>
#include <cpu.h>
#include <interrupt.h>
#include <gtimer.h>

extern volatile unsigned long MMUTable[];
extern void rt_hw_cpu_id_set();
void rt_hw_mmu_ktbl_set(unsigned long tbl);

/* Interface */
void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);

    rt_hw_mmu_ktbl_set((unsigned long) MMUTable);

    rt_hw_cpu_id_set();

    rt_hw_vector_init();

    arm_gic_cpu_init(0, 0);

    arm_gic_redist_init(0, 0);

    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);

    rt_hw_gtimer_init();

    rt_kprintf("rt_hw_secondary_cpu_bsp_start  cpu %d\n", rt_hw_cpu_id());

    rt_system_scheduler_start();
}

#endif
