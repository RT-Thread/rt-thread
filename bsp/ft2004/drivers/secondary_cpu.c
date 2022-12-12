/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-05-26 10:09:45
 * @LastEditTime: 2021-08-16 16:32:08
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <rtthread.h>
#include "board.h"
#include <gicv3.h>

#ifdef RT_USING_SMP
#include <interrupt.h>
#include "ft_psci.h"
#include "ft_generic_timer.h"

extern int rt_hw_timer_init(void);
extern void secondary_cpu_start(void);

void rt_hw_secondary_cpu_up(void)
{

    rt_uint32_t i;
    rt_uint32_t cpu_mask = 0;

    rt_kprintf("rt_hw_secondary_cpu_up is processing \r\n");
    for (i = 1; i < RT_CPUS_NR; i++)
    {
        if (i == 1)
        {
            /* code */
            FPsci_CpuOn(1 << i, (rt_uint32_t)secondary_cpu_start);
            cpu_mask = 2;
        }
        else if (i == 2)
        {
            FPsci_CpuOn(1 << i, (rt_uint32_t)secondary_cpu_start);
            cpu_mask = 4;
        }
        else if (i == 3)
        {
            FPsci_CpuOn(1 << i, (rt_uint32_t)secondary_cpu_start);
            cpu_mask = 8;
        }
        else
        {
            continue;
        }

        __asm__ volatile("dsb" ::
                             : "memory");
        rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
        Ft_GenericTimer_UsDelay(1000000);
    }
}

void secondary_cpu_c_start(void)
{
    rt_hw_vector_init();
    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0);
    arm_gic_redist_init(0);

    rt_hw_timer_init();

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
