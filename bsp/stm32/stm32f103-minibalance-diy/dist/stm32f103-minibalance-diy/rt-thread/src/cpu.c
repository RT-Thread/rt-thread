/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     Bernard      The first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_SMP

static struct rt_cpu rt_cpus[RT_CPUS_NR];
rt_hw_spinlock_t _cpus_lock;

/**
 * This fucntion will return current cpu.
 */
struct rt_cpu *rt_cpu_self(void)
{
    return &rt_cpus[rt_hw_cpu_id()];
}

struct rt_cpu *rt_cpu_index(int index)
{
    return &rt_cpus[index];
}

/**
 * This function will lock all cpus's scheduler and disable local irq.
 */
rt_base_t rt_cpus_lock(void)
{
    rt_base_t level;
    struct rt_cpu* pcpu;

    level = rt_hw_local_irq_disable();

    pcpu = rt_cpu_self();
    if (pcpu->current_thread != RT_NULL)
    {
        register rt_uint16_t lock_nest = pcpu->current_thread->cpus_lock_nest;

        pcpu->current_thread->cpus_lock_nest++;
        if (lock_nest == 0)
        {
            pcpu->current_thread->scheduler_lock_nest++;
            rt_hw_spin_lock(&_cpus_lock);
        }
    }

    return level;
}
RTM_EXPORT(rt_cpus_lock);

/**
 * This function will restore all cpus's scheduler and restore local irq.
 */
void rt_cpus_unlock(rt_base_t level)
{
    struct rt_cpu* pcpu = rt_cpu_self();

    if (pcpu->current_thread != RT_NULL)
    {
        pcpu->current_thread->cpus_lock_nest--;

        if (pcpu->current_thread->cpus_lock_nest == 0)
        {
            pcpu->current_thread->scheduler_lock_nest--;
            rt_hw_spin_unlock(&_cpus_lock);
        }
    }
    rt_hw_local_irq_enable(level);
}
RTM_EXPORT(rt_cpus_unlock);

/**
 * This function is invoked by scheduler.
 * It will restore the lock state to whatever the thread's counter expects.
 * If target thread not locked the cpus then unlock the cpus lock.
 */
void rt_cpus_lock_status_restore(struct rt_thread *thread)
{
    struct rt_cpu* pcpu = rt_cpu_self();

    pcpu->current_thread = thread;
    if (!thread->cpus_lock_nest)
    {
        rt_hw_spin_unlock(&_cpus_lock);
    }
}
RTM_EXPORT(rt_cpus_lock_status_restore);

#endif
