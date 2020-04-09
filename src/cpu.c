/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     Bernard      The first version
 */
#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SMP
static struct rt_cpu rt_cpus[RT_CPUS_NR];
rt_hw_spinlock_t _cpus_lock;

/*
 * disable scheduler
 */
static void rt_preempt_disable(void)
{
    register rt_base_t level;
    struct rt_thread *current_thread;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    current_thread = rt_thread_self();
    if (!current_thread)
    {
        rt_hw_local_irq_enable(level);
        return;
    }

    /* lock scheduler for local cpu */
    current_thread->scheduler_lock_nest ++;

    /* enable interrupt */
    rt_hw_local_irq_enable(level);
}

/*
 * enable scheduler
 */
static void rt_preempt_enable(void)
{
    register rt_base_t level;
    struct rt_thread *current_thread;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    current_thread = rt_thread_self();
    if (!current_thread)
    {
        rt_hw_local_irq_enable(level);
        return;
    }

    /* unlock scheduler for local cpu */
    current_thread->scheduler_lock_nest --;

    rt_schedule();
    /* enable interrupt */
    rt_hw_local_irq_enable(level);
}

void rt_spin_lock_init(struct rt_spinlock *lock)
{
    rt_hw_spin_lock_init(&lock->lock);
}
RTM_EXPORT(rt_spin_lock_init)

void rt_spin_lock(struct rt_spinlock *lock)
{
    rt_preempt_disable();
    rt_hw_spin_lock(&lock->lock);
}
RTM_EXPORT(rt_spin_lock)

void rt_spin_unlock(struct rt_spinlock *lock)
{
    rt_hw_spin_unlock(&lock->lock);
    rt_preempt_enable();
}
RTM_EXPORT(rt_spin_unlock)

rt_base_t rt_spin_lock_irqsave(struct rt_spinlock *lock)
{
    unsigned long level;

    rt_preempt_disable();

    level = rt_hw_local_irq_disable();
    rt_hw_spin_lock(&lock->lock);

    return level;
}
RTM_EXPORT(rt_spin_lock_irqsave)

void rt_spin_unlock_irqrestore(struct rt_spinlock *lock, rt_base_t level)
{
    rt_hw_spin_unlock(&lock->lock);
    rt_hw_local_irq_enable(level);

    rt_preempt_enable();
}
RTM_EXPORT(rt_spin_unlock_irqrestore)

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
        register rt_ubase_t lock_nest = pcpu->current_thread->cpus_lock_nest;

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
