/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/12/23     Bernard      The first version
 * 2018/12/27     Jesven       Add secondary cpu boot
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"
#include <encoding.h>
#include <clint.h>
#include <atomic.h>

#ifdef RT_USING_SMP

int rt_hw_cpu_id(void)
{
    return read_csr(mhartid);
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    spinlock_lock((spinlock_t *)lock);
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    spinlock_unlock((spinlock_t *)lock);
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    int idx;

    for (idx = 0; idx < RT_CPUS_NR; idx ++)
    {
        if (cpu_mask & (1 << idx))
        {
            clint_ipi_send(idx);
        }
    }
}

extern rt_base_t secondary_boot_flag;
void rt_hw_secondary_cpu_up(void)
{
    mb();
    secondary_boot_flag = 0xa55a;
}

extern void rt_hw_scondary_interrupt_init(void);
extern int rt_hw_tick_init(void);
extern int rt_hw_clint_ipi_enable(void);

void secondary_cpu_c_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);

    /* initialize interrupt controller */
    rt_hw_scondary_interrupt_init();

    rt_hw_tick_init();

    rt_hw_clint_ipi_enable();

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}
#endif /*RT_USING_SMP*/
