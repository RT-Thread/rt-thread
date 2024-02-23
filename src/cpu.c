/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     Bernard      The first version
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-12-10     xqyjlj       spinlock should lock sched
 * 2024-01-25     Shell        Using rt_exit_critical_safe
 */
#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#endif

#ifdef RT_USING_DEBUG
rt_base_t _cpus_critical_level;
#endif /* RT_USING_DEBUG */

#ifdef RT_USING_SMP
static struct rt_cpu _cpus[RT_CPUS_NR];
rt_hw_spinlock_t _cpus_lock;
#if defined(RT_DEBUGING_SPINLOCK)
void *_cpus_lock_owner = 0;
void *_cpus_lock_pc = 0;

#endif /* RT_DEBUGING_SPINLOCK */

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
 * @brief   This function will lock the spinlock, will lock the thread scheduler.
 *
 * @note    If the spinlock is locked, the current CPU will keep polling the spinlock state
 *          until the spinlock is unlocked.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_lock(struct rt_spinlock *lock)
{
    rt_enter_critical();
    rt_hw_spin_lock(&lock->lock);
    RT_SPIN_LOCK_DEBUG(lock);
}
RTM_EXPORT(rt_spin_lock)

/**
 * @brief   This function will unlock the spinlock, will unlock the thread scheduler.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_unlock(struct rt_spinlock *lock)
{
    rt_base_t critical_level;
    RT_SPIN_UNLOCK_DEBUG(lock, critical_level);
    rt_hw_spin_unlock(&lock->lock);
    rt_exit_critical_safe(critical_level);
}
RTM_EXPORT(rt_spin_unlock)

/**
 * @brief   This function will disable the local interrupt and then lock the spinlock, will lock the thread scheduler.
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
    rt_base_t level;

    level = rt_hw_local_irq_disable();
    rt_enter_critical();
    rt_hw_spin_lock(&lock->lock);
    RT_SPIN_LOCK_DEBUG(lock);
    return level;
}
RTM_EXPORT(rt_spin_lock_irqsave)

/**
 * @brief   This function will unlock the spinlock and then restore current cpu interrupt status, will unlock the thread scheduler.
 *
 * @param   lock is a pointer to the spinlock.
 *
 * @param   level is interrupt status returned by rt_spin_lock_irqsave().
 */
void rt_spin_unlock_irqrestore(struct rt_spinlock *lock, rt_base_t level)
{
    rt_base_t critical_level;

    RT_SPIN_UNLOCK_DEBUG(lock, critical_level);
    rt_hw_spin_unlock(&lock->lock);
    rt_hw_local_irq_enable(level);
    rt_exit_critical_safe(critical_level);
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
 * @param   index is the index of target cpu object.
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
        register rt_ubase_t lock_nest = rt_atomic_load(&(pcpu->current_thread->cpus_lock_nest));

        rt_atomic_add(&(pcpu->current_thread->cpus_lock_nest), 1);
        if (lock_nest == 0)
        {
            rt_enter_critical();
            rt_hw_spin_lock(&_cpus_lock);
#ifdef RT_USING_DEBUG
            _cpus_critical_level = rt_critical_level();
#endif /* RT_USING_DEBUG */

#ifdef RT_DEBUGING_SPINLOCK
            _cpus_lock_owner = pcpu->current_thread;
            _cpus_lock_pc = __GET_RETURN_ADDRESS;
#endif /* RT_DEBUGING_SPINLOCK */
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
        rt_base_t critical_level = 0;
        RT_ASSERT(rt_atomic_load(&(pcpu->current_thread->cpus_lock_nest)) > 0);
        rt_atomic_sub(&(pcpu->current_thread->cpus_lock_nest), 1);

        if (pcpu->current_thread->cpus_lock_nest == 0)
        {
#if defined(RT_DEBUGING_SPINLOCK)
            _cpus_lock_owner = __OWNER_MAGIC;
            _cpus_lock_pc = RT_NULL;
#endif /* RT_DEBUGING_SPINLOCK */
#ifdef RT_USING_DEBUG
            critical_level = _cpus_critical_level;
            _cpus_critical_level = 0;
#endif /* RT_USING_DEBUG */
            rt_hw_spin_unlock(&_cpus_lock);
            rt_exit_critical_safe(critical_level);
        }
    }
    rt_hw_local_irq_enable(level);
}
RTM_EXPORT(rt_cpus_unlock);

/**
 * This function is invoked by scheduler.
 * It will restore the lock state to whatever the thread's counter expects.
 * If target thread not locked the cpus then unlock the cpus lock.
 *
 * @param   thread is a pointer to the target thread.
 */
void rt_cpus_lock_status_restore(struct rt_thread *thread)
{
#if defined(ARCH_MM_MMU) && defined(RT_USING_SMART)
    lwp_aspace_switch(thread);
#endif
    rt_sched_post_ctx_switch(thread);
}
RTM_EXPORT(rt_cpus_lock_status_restore);
#endif /* RT_USING_SMP */
