/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board_smp.h"
#include "clint.h"

#ifdef RT_USING_SMP

extern char _start[];
extern volatile rt_ubase_t secondary_boot_flag;
extern int rt_hw_tick_init(void);

#define MIE_MSIE    (1U << 3)

int rt_hw_cpu_id(void)
{
    unsigned long id;
    __asm__ volatile("csrr %0, mhartid" : "=r"(id));
    return (int)id;
}

void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    while (rt_hw_atomic_exchange((rt_atomic_t *)&lock->slock, 1) != 0)
        ;
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    rt_hw_atomic_store((rt_atomic_t *)&lock->slock, 0);
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    int idx;

    RT_UNUSED(ipi_vector);
    for (idx = 0; idx < RT_CPUS_NR; idx++)
    {
        if (cpu_mask & (1U << idx))
            v861_clint_ipi_send((unsigned int)idx);
    }
}

void rt_hw_secondary_cpu_up(void)
{
    secondary_boot_flag = 0xa55a;
    __asm__ volatile("fence iorw, iorw" ::: "memory");
    rt_hw_hart_power_on(1, (unsigned long)_start);
}

static void hart_msie_enable(void)
{
    unsigned long mie;
    __asm__ volatile("csrr %0, mie" : "=r"(mie));
    mie |= MIE_MSIE;
    __asm__ volatile("csrw mie, %0" :: "r"(mie));
}

void secondary_cpu_c_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);
    rt_hw_tick_init();
    hart_msie_enable();
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __asm__ volatile("wfi");
}

#endif /* RT_USING_SMP */
