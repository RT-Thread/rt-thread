/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2021-06-17     Wayne        the first version
 */

#include <rtthread.h>
#include "board.h"
#include "gic.h"
#include "cp15.h"

#ifdef RT_USING_SMP
#include "interrupt.h"

extern int rt_hw_timer_init(void);
extern void secondary_cpu_start(void);

/*
   For core-1, core-2 and core-3.
*/
void rt_hw_secondary_cpu_up(void)
{
    rt_uint32_t cpu_mask = 2;
    rt_int32_t i;

    rt_cpu_dcache_clean_flush();
    rt_cpu_icache_flush();

    rt_kprintf("rt_hw_secondary_cpu_up is processing \r\n");
    for (i = 1; i < RT_CPUS_NR, i != 4; i++)
    {
        rt_kprintf("Boot Core-%d\n", i);
        //FPsci_CpuOn(1 << i, (rt_uint32_t)secondary_cpu_start);
        cpu_mask <<= 1;
        __SEV();
        __DSB();
        __ISB();

        __DSB();
        rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
    }
}

void secondary_cpu_c_start(void)
{
    uint32_t id = rt_hw_cpu_id();
    rt_kprintf("cpu = 0x%08x\n", id);

    rt_hw_timer_init();

    /* initialize vector table */
    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);

    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile("wfe" ::
                 : "memory", "cc");
}

#endif
