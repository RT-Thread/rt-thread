/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/12/23     Bernard      The first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"
#include <encoding.h>
#include <clint.h>
#include <atomic.h>

#ifdef RT_USING_SMP
extern volatile uint64_t g_wake_up[2];

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

static int k210_ipi_callback(void *ctx)
{
    /* do re-schedule */
    rt_schedule();
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    int idx;

    for (idx = 0; idx < RT_CPUS_NR; idx ++)
    {
        if (cpu_mask & (1 < idx))
        {
            clint_ipi_send(idx);
        }
    }
}

int rt_hw_ipi_init(void)
{
    clint_ipi_init();
    clint_ipi_enable();

    /* register ipi callback */
    clint_ipi_register(k210_ipi_callback, RT_NULL);

    return 0;
}

void rt_hw_secondary_cpu_up(void)
{
    mb();

    clint_ipi_send(1);
    atomic_set(&g_wake_up[1], 1);
}

void secondary_cpu_c_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);

    /* initialize interrupt controller */
    rt_hw_interrupt_init();

    /* todo: this cpu timer init */
    /* todo: this cpu timer interrupt config */

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}
#endif /*RT_USING_SMP*/
