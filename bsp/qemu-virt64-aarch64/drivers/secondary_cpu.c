/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rthw.h>
#include <rtthread.h>
#include <cpu.h>
#include "gic.h"
#include "interrupt.h"
#include "mmu.h"

#ifdef RT_USING_SMP

extern unsigned long MMUTable[];

void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);

    rt_hw_mmu_ktbl_set((unsigned long)MMUTable);

    // interrupt init
    rt_hw_vector_init();

    arm_gic_cpu_init(0, 0);

    // local timer init

    rt_system_scheduler_start();
}

#endif // SMP