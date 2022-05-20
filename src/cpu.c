/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
static struct rt_cpu _cpus[RT_CPUS_NR];
rt_hw_spinlock_t _cpus_lock;

/*
 * disable scheduler
 */
static void _cpu_preempt_disable(void)
{
    rt_base_t level;
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
static void _cpu_preempt_enable(void)
{
    rt_base_t level;
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

/**
 * @brief   Initialize a static spinlock object.
 *
 * @param   lock is a pointer to the spinlock to initialize.
 */
void rt_spin_lock_init(struct rt_spinlock *lock)
{
    rt_hw_spin_lock_init(&lock->lock);
}
RTM_EXPORT(rt_spin_lock_init)

/**
 * @brief   This function will lock the spinlock.
 *
 * @note    If the spinlock is locked, the current CPU will keep polling the spinlock state
 *          until the spinlock is unlocked.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_lock(struct rt_spinlock *lock)
{
    _cpu_preempt_disable();
    rt_hw_spin_lock(&lock->lock);
}
RTM_EXPORT(rt_spin_lock)

/**
 * @brief   This function will unlock the spinlock.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_unlock(struct rt_spinlock *lock)
{
    rt_hw_spin_unlock(&lock->lock);
    _cpu_preempt_enable();
}
RTM_EXPORT(rt_spin_unlock)

/**
 * @brief   This function will disable the local interrupt and then lock the spinlock.
 *
 * @note    If the spinlock is locked, the current CPU will keep polling the spinlock state
 *          until the spinlock is unlocked.
 *
 * @param   lock is a pointer to the spinlock.
 *
 * @return  Return current cpu interrupt status.
 */
rt_base_t rt_spin_lock_irqsave(struct rt_spinlock *lock)
{
    unsigned long level;

    _cpu_preempt_disable();

    level = rt_hw_local_irq_disable();
    rt_hw_spin_lock(&lock->lock);

    return level;
}
RTM_EXPORT(rt_spin_lock_irqsave)

/**
 * @brief   This function will unlock the spinlock and then restore current cpu interrupt status.
 *
 * @param   lock is a pointer to the spinlock.
 *
 * @param   level is interrupt status returned by rt_spin_lock_irqsave().
 */
void rt_spin_unlock_irqrestore(struct rt_spinlock *lock, rt_base_t level)
{
    rt_hw_spin_unlock(&lock->lock);
    rt_hw_local_irq_enable(level);

    _cpu_preempt_enable();
}
RTM_EXPORT(rt_spin_unlock_irqrestore)

/**
 * @brief   This fucntion will return current cpu object.
 *
 * @return  Return a pointer to the current cpu object.
 */
struct rt_cpu *rt_cpu_self(void)
{
    return &_cpus[rt_hw_cpu_id()];
}

/**
 * @brief   This fucntion will return the cpu object corresponding to index.
 *
 * @return  Return a pointer to the cpu object corresponding to index.
 */
struct rt_cpu *rt_cpu_index(int index)
{
    return &_cpus[index];
}

/**
 * @brief   This function will lock all cpus's scheduler and disable local irq.
 *
 * @return  Return current cpu interrupt status.
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
 * @brief   This function will restore all cpus's scheduler and restore local irq.
 *
 * @param   level is interrupt status returned by rt_cpus_lock().
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

#endif /* RT_USING_SMP */
