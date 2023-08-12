/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-17     Bernard      the first version
 * 2006-04-28     Bernard      fix the scheduler algorthm
 * 2006-04-30     Bernard      add SCHEDULER_DEBUG
 * 2006-05-27     Bernard      fix the scheduler algorthm for same priority
 *                             thread schedule
 * 2006-06-04     Bernard      rewrite the scheduler algorithm
 * 2006-08-03     Bernard      add hook support
 * 2006-09-05     Bernard      add 32 priority level support
 * 2006-09-24     Bernard      add rt_system_scheduler_start function
 * 2009-09-16     Bernard      fix _rt_scheduler_stack_check
 * 2010-04-11     yi.qiu       add module feature
 * 2010-07-13     Bernard      fix the maximal number of rt_scheduler_lock_nest
 *                             issue found by kuronca
 * 2010-12-13     Bernard      add defunct list initialization even if not use heap.
 * 2011-05-10     Bernard      clean scheduler debug log.
 * 2013-12-21     Grissiom     add rt_critical_level
 * 2018-11-22     Jesven       remove the current task from ready queue
 *                             add per cpu ready queue
 *                             add _scheduler_get_highest_priority_thread to find highest priority task
 *                             rt_schedule_insert_thread won't insert current task to ready queue
 *                             in smp version, rt_hw_context_switch_interrupt maybe switch to
 *                             new task directly
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to scheduler.c
 * 2023-03-27     rose_man     Split into scheduler upc and scheduler_mp.c
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.scheduler"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
static RT_DEFINE_SPINLOCK(_spinlock);
rt_uint32_t rt_thread_ready_priority_group;
#if RT_THREAD_PRIORITY_MAX > 32
/* Maximum priority level, 256 */
rt_uint8_t rt_thread_ready_table[32];
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

#ifndef __on_rt_scheduler_hook
    #define __on_rt_scheduler_hook(from, to)        __ON_HOOK_ARGS(rt_scheduler_hook, (from, to))
#endif
#ifndef __on_rt_scheduler_switch_hook
    #define __on_rt_scheduler_switch_hook(tid)      __ON_HOOK_ARGS(rt_scheduler_switch_hook, (tid))
#endif

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static void (*rt_scheduler_hook)(struct rt_thread *from, struct rt_thread *to);
static void (*rt_scheduler_switch_hook)(struct rt_thread *tid);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * @brief This function will set a hook function, which will be invoked when thread
 *        switch happens.
 *
 * @param hook is the hook function.
 */
void rt_scheduler_sethook(void (*hook)(struct rt_thread *from, struct rt_thread *to))
{
    rt_scheduler_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when context
 *        switch happens.
 *
 * @param hook is the hook function.
 */
void rt_scheduler_switch_sethook(void (*hook)(struct rt_thread *tid))
{
    rt_scheduler_switch_hook = hook;
}

/**@}*/
#endif /* RT_USING_HOOK */

#ifdef RT_USING_OVERFLOW_CHECK
static void _scheduler_stack_check(struct rt_thread *thread)
{
    RT_ASSERT(thread != RT_NULL);

#ifdef RT_USING_SMART
#ifndef ARCH_MM_MMU
    struct rt_lwp *lwp = thread ? (struct rt_lwp *)thread->lwp : 0;

    /* if stack pointer locate in user data section skip stack check. */
    if (lwp && ((rt_uint32_t)thread->sp > (rt_uint32_t)lwp->data_entry &&
    (rt_uint32_t)thread->sp <= (rt_uint32_t)lwp->data_entry + (rt_uint32_t)lwp->data_size))
    {
        return;
    }
#endif /* not defined ARCH_MM_MMU */
#endif /* RT_USING_SMART */

#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    if (*((rt_uint8_t *)((rt_ubase_t)thread->stack_addr + thread->stack_size - 1)) != '#' ||
#else
    if (*((rt_uint8_t *)thread->stack_addr) != '#' ||
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
        (rt_ubase_t)thread->sp <= (rt_ubase_t)thread->stack_addr ||
        (rt_ubase_t)thread->sp >
        (rt_ubase_t)thread->stack_addr + (rt_ubase_t)thread->stack_size)
    {
        rt_base_t level;

        rt_kprintf("thread:%s stack overflow\n", thread->parent.name);

        level = rt_hw_local_irq_disable();
        rt_spin_lock(&_spinlock);
        while (level);
    }
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    else if ((rt_ubase_t)thread->sp > ((rt_ubase_t)thread->stack_addr + thread->stack_size))
    {
        rt_kprintf("warning: %s stack is close to the top of stack address.\n",
                   thread->parent.name);
    }
#else
    else if ((rt_ubase_t)thread->sp <= ((rt_ubase_t)thread->stack_addr + 32))
    {
        rt_kprintf("warning: %s stack is close to end of stack address.\n",
                   thread->parent.name);
    }
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
}
#endif /* RT_USING_OVERFLOW_CHECK */

/*
 * get the highest priority thread in ready queue
 */
static struct rt_thread* _scheduler_get_highest_priority_thread(rt_ubase_t *highest_prio)
{
    struct rt_thread *highest_priority_thread;
    rt_ubase_t highest_ready_priority, local_highest_ready_priority;
    struct rt_cpu* pcpu = rt_cpu_self();
#if RT_THREAD_PRIORITY_MAX > 32
    rt_ubase_t number;

    number = __rt_ffs(rt_thread_ready_priority_group) - 1;
    highest_ready_priority = (number << 3) + __rt_ffs(rt_thread_ready_table[number]) - 1;
    number = __rt_ffs(pcpu->priority_group) - 1;
    local_highest_ready_priority = (number << 3) + __rt_ffs(pcpu->ready_table[number]) - 1;
#else
    highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
    local_highest_ready_priority = __rt_ffs(pcpu->priority_group) - 1;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* get highest ready priority thread */
    if (highest_ready_priority < local_highest_ready_priority)
    {
        *highest_prio = highest_ready_priority;
        highest_priority_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
                                  struct rt_thread,
                                  tlist_schedule);
    }
    else
    {
        *highest_prio = local_highest_ready_priority;
        highest_priority_thread = rt_list_entry(pcpu->priority_table[local_highest_ready_priority].next,
                                  struct rt_thread,
                                  tlist_schedule);
    }

    return highest_priority_thread;
}

/**
 * @brief This function will initialize the system scheduler.
 */
void rt_system_scheduler_init(void)
{
    int cpu;
    rt_base_t offset;

    LOG_D("start scheduler: max priority 0x%02x",
          RT_THREAD_PRIORITY_MAX);

    for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset ++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);
    }

    for (cpu = 0; cpu < RT_CPUS_NR; cpu++)
    {
        struct rt_cpu *pcpu =  rt_cpu_index(cpu);
        for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset ++)
        {
            rt_list_init(&pcpu->priority_table[offset]);
        }

        pcpu->irq_switch_flag = 0;
        pcpu->current_priority = RT_THREAD_PRIORITY_MAX - 1;
        pcpu->current_thread = RT_NULL;
        pcpu->priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
        rt_memset(pcpu->ready_table, 0, sizeof(pcpu->ready_table));
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

        rt_spin_lock_init(&(pcpu->spinlock));
    }

    /* initialize ready priority group */
    rt_thread_ready_priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
    /* initialize ready table */
    rt_memset(rt_thread_ready_table, 0, sizeof(rt_thread_ready_table));
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
}

/**
 * @addtogroup Thread
 * @cond
 */

/**@{*/

/**
 * @brief This function will handle IPI interrupt and do a scheduling in system.
 *
 * @param vector is the number of IPI interrupt for system scheduling.
 *
 * @param param is not used, and can be set to RT_NULL.
 *
 * @note this function should be invoke or register as ISR in BSP.
 */
void rt_scheduler_ipi_handler(int vector, void *param)
{
    rt_schedule();
}

static void _rt_schedule_insert_thread(struct rt_thread *thread, rt_bool_t is_lock)
{
    int cpu_id;
    int bind_cpu;
    rt_uint32_t cpu_mask;

    RT_ASSERT(thread != RT_NULL);

    /* disable interrupt */
    if(is_lock)
    {
        rt_spin_lock(&(thread->spinlock));
    }

    if ((thread->stat & RT_THREAD_STAT_MASK) == RT_THREAD_READY)
    {
        if(is_lock)
        {
            rt_spin_unlock(&(thread->spinlock));
        }
        return;
    }

    /* it should be RUNNING thread */
    if (thread->oncpu != RT_CPU_DETACHED)
    {
        thread->stat = RT_THREAD_RUNNING | (thread->stat & ~RT_THREAD_STAT_MASK);
        if(is_lock)
        {
            rt_spin_unlock(&(thread->spinlock));
        }
        return;
    }

    /* READY thread, insert to ready queue */
    thread->stat = RT_THREAD_READY | (thread->stat & ~RT_THREAD_STAT_MASK);

    cpu_id   = rt_hw_cpu_id();
    bind_cpu = thread->bind_cpu ;

    /* insert thread to ready list */
    if (bind_cpu == RT_CPUS_NR)
    {
#if RT_THREAD_PRIORITY_MAX > 32
        rt_thread_ready_table[thread->number] |= thread->high_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        rt_thread_ready_priority_group |= thread->number_mask;

        /* there is no time slices left(YIELD), inserting thread before ready list*/
        if((thread->stat & RT_THREAD_STAT_YIELD_MASK) != 0)
        {
            rt_list_insert_before(&(rt_thread_priority_table[thread->current_priority]),
                                &(thread->tlist_schedule));
        }
        /* there are some time slices left, inserting thread after ready list to schedule it firstly at next time*/
        else
        {
            rt_list_insert_after(&(rt_thread_priority_table[thread->current_priority]),
                                &(thread->tlist_schedule));
        }
        if(is_lock)
        {
            rt_spin_unlock(&(thread->spinlock));
        }

        cpu_mask = RT_CPU_MASK ^ (1 << cpu_id);
        rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
    }
    else
    {
        struct rt_cpu *pcpu = rt_cpu_index(bind_cpu);

        if(is_lock)
        {
            rt_spin_lock(&(pcpu->spinlock));
        }
#if RT_THREAD_PRIORITY_MAX > 32
        pcpu->ready_table[thread->number] |= thread->high_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        pcpu->priority_group |= thread->number_mask;

        /* there is no time slices left(YIELD), inserting thread before ready list*/
        if((thread->stat & RT_THREAD_STAT_YIELD_MASK) != 0)
        {
            rt_list_insert_before(&(rt_cpu_index(bind_cpu)->priority_table[thread->current_priority]),
                                &(thread->tlist_schedule));
        }
        /* there are some time slices left, inserting thread after ready list to schedule it firstly at next time*/
        else
        {
            rt_list_insert_after(&(rt_cpu_index(bind_cpu)->priority_table[thread->current_priority]),
                                &(thread->tlist_schedule));
        }

        if(is_lock)
        {
            rt_spin_unlock(&(pcpu->spinlock));
            rt_spin_unlock(&(thread->spinlock));
        }

        if (cpu_id != bind_cpu)
        {
            cpu_mask = 1 << bind_cpu;
            rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
        }
    }

    LOG_D("insert thread[%.*s], the priority: %d",
          RT_NAME_MAX, thread->parent.name, thread->current_priority);
}

static void _rt_schedule_remove_thread(struct rt_thread *thread, rt_bool_t is_lock)
{

    RT_ASSERT(thread != RT_NULL);

    LOG_D("remove thread[%.*s], the priority: %d",
          RT_NAME_MAX, thread->parent.name,
          thread->current_priority);

    /* remove thread from ready list */
    rt_list_remove(&(thread->tlist_schedule));
    if (thread->bind_cpu == RT_CPUS_NR)
    {
        if (rt_list_isempty(&(rt_thread_priority_table[thread->current_priority])))
        {
#if RT_THREAD_PRIORITY_MAX > 32
            rt_thread_ready_table[thread->number] &= ~thread->high_mask;
            if (rt_thread_ready_table[thread->number] == 0)
            {
                rt_thread_ready_priority_group &= ~thread->number_mask;
            }
#else
            rt_thread_ready_priority_group &= ~thread->number_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        }
    }
    else
    {
        struct rt_cpu *pcpu = rt_cpu_index(thread->bind_cpu);
        if(is_lock)
        {
            rt_spin_lock(&(pcpu->spinlock));
        }
        if (rt_list_isempty(&(pcpu->priority_table[thread->current_priority])))
        {
#if RT_THREAD_PRIORITY_MAX > 32
            pcpu->ready_table[thread->number] &= ~thread->high_mask;
            if (pcpu->ready_table[thread->number] == 0)
            {
                pcpu->priority_group &= ~thread->number_mask;
            }
#else
            pcpu->priority_group &= ~thread->number_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        }
        if(is_lock)
        {
            rt_spin_unlock(&(pcpu->spinlock));
        }
    }
}

/**
 * @brief This function will startup the scheduler. It will select one thread
 *        with the highest priority level, then switch to it.
 */
void rt_system_scheduler_start(void)
{
    struct rt_thread *to_thread;
    rt_ubase_t highest_ready_priority;

    rt_hw_local_irq_disable();
    rt_spin_lock(&_spinlock);

    to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);
    rt_spin_lock(&to_thread->spinlock);
    to_thread->oncpu = rt_hw_cpu_id();

    _rt_schedule_remove_thread(to_thread, RT_TRUE);
    to_thread->stat = RT_THREAD_RUNNING;

    rt_spin_unlock(&to_thread->spinlock);
    rt_spin_unlock(&_spinlock);

    rt_hw_spin_unlock(&_cpus_lock);

    /* switch to new thread */
    rt_hw_context_switch_to((rt_ubase_t)&to_thread->sp, to_thread);

    /* never come back */
}

/**
 * @brief This function will perform one scheduling. It will select one thread
 *        with the highest priority level in global ready queue or local ready queue,
 *        then switch to it.
 */
void rt_schedule(void)
{
    rt_base_t        level;
    struct rt_thread *to_thread;
    struct rt_thread *current_thread;
    struct rt_cpu    *pcpu;
    int              cpu_id;
    rt_bool_t        need_unlock = RT_TRUE;

    /* disable interrupt */
    level  = rt_hw_local_irq_disable();

    rt_spin_lock(&_spinlock);

    cpu_id = rt_hw_cpu_id();
    pcpu   = rt_cpu_index(cpu_id);
    rt_spin_lock(&pcpu->spinlock);
    current_thread = pcpu->current_thread;

    /* whether do switch in interrupt */
    if (rt_atomic_load(&(pcpu->irq_nest)))
    {
        pcpu->irq_switch_flag = 1;
        rt_spin_unlock(&pcpu->spinlock);
        rt_spin_unlock(&_spinlock);
        rt_hw_local_irq_enable(level);
        goto __exit;
    }

#ifdef RT_USING_SIGNALS
    if ((current_thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        /* if current_thread signal is in pending */

        if ((current_thread->stat & RT_THREAD_STAT_SIGNAL_MASK) & RT_THREAD_STAT_SIGNAL_PENDING)
        {
#ifdef RT_USING_SMART
            rt_thread_wakeup(current_thread);
#else
            rt_thread_resume(current_thread);
#endif
        }
    }
#endif /* RT_USING_SIGNALS */

    rt_spin_lock(&(current_thread->spinlock));
    if (rt_atomic_load(&(current_thread->critical_lock_nest)) == 0) /* whether lock scheduler */
    {
        rt_ubase_t highest_ready_priority;

        if (rt_thread_ready_priority_group != 0 || pcpu->priority_group != 0)
        {
            to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);
            current_thread->oncpu = RT_CPU_DETACHED;
            if ((current_thread->stat & RT_THREAD_STAT_MASK) == RT_THREAD_RUNNING)
            {
                if (current_thread->bind_cpu == RT_CPUS_NR || current_thread->bind_cpu == cpu_id)
                {
                    if (current_thread->current_priority < highest_ready_priority)
                    {
                        to_thread = current_thread;
                    }
                    else if (current_thread->current_priority == highest_ready_priority && (current_thread->stat & RT_THREAD_STAT_YIELD_MASK) == 0)
                    {
                        to_thread = current_thread;
                    }
                    else
                    {
                        _rt_schedule_insert_thread(current_thread, RT_FALSE);
                    }
                }
                else
                {
                    _rt_schedule_insert_thread(current_thread, RT_FALSE);
                }
                current_thread->stat &= ~RT_THREAD_STAT_YIELD_MASK;
            }

            if (to_thread != current_thread)
            {
                rt_spin_lock(&(to_thread->spinlock));
            }
            to_thread->oncpu = cpu_id;
            if (to_thread != current_thread)
            {
                /* if the destination thread is not the same as current thread */
                pcpu->current_priority = (rt_uint8_t)highest_ready_priority;

                RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (current_thread, to_thread));

                _rt_schedule_remove_thread(to_thread, RT_FALSE);
                to_thread->stat = RT_THREAD_RUNNING | (to_thread->stat & ~RT_THREAD_STAT_MASK);

                /* switch to new thread */
                LOG_D("[%d]switch to priority#%d "
                         "thread:%.*s(sp:0x%08x), "
                         "from thread:%.*s(sp: 0x%08x)",
                         rt_atomic_load(&(pcpu->irq_nest)), highest_ready_priority,
                         RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
                         RT_NAME_MAX, current_thread->parent.name, current_thread->sp);

#ifdef RT_USING_OVERFLOW_CHECK
                _scheduler_stack_check(to_thread);
#endif /* RT_USING_OVERFLOW_CHECK */

                RT_OBJECT_HOOK_CALL(rt_scheduler_switch_hook, (current_thread));

                rt_spin_unlock(&(to_thread->spinlock));
                rt_spin_unlock(&pcpu->spinlock);
                rt_spin_unlock(&_spinlock);

                need_unlock = RT_FALSE;
                rt_hw_context_switch((rt_ubase_t)&current_thread->sp,
                        (rt_ubase_t)&to_thread->sp, to_thread);
            }
        }
    }

    if(need_unlock)
    {
        rt_spin_unlock(&(current_thread->spinlock));
        rt_spin_unlock(&pcpu->spinlock);
        rt_spin_unlock(&_spinlock);
    }
    rt_hw_local_irq_enable(level);

#ifdef RT_USING_SIGNALS
    /* check stat of thread for signal */
    rt_spin_lock(&(current_thread->spinlock));
    if (current_thread->stat & RT_THREAD_STAT_SIGNAL_PENDING)
    {
        extern void rt_thread_handle_sig(rt_bool_t clean_state);

        current_thread->stat &= ~RT_THREAD_STAT_SIGNAL_PENDING;

        rt_spin_unlock(&(current_thread->spinlock));

        /* check signal status */
        rt_thread_handle_sig(RT_TRUE);
    }
    else
    {
        rt_spin_unlock(&(current_thread->spinlock));
    }
#endif /* RT_USING_SIGNALS */

__exit:
    return ;
}

/**
 * @brief This function checks whether a scheduling is needed after an IRQ context switching. If yes,
 *        it will select one thread with the highest priority level, and then switch
 *        to it.
 */
void rt_scheduler_do_irq_switch(void *context)
{
    int              cpu_id;
    rt_base_t        level;
    struct rt_cpu    *pcpu;
    struct rt_thread *to_thread;
    struct rt_thread *current_thread;
    rt_bool_t        need_unlock = RT_TRUE;

    level  = rt_hw_local_irq_disable();
    rt_spin_lock(&_spinlock);
    cpu_id = rt_hw_cpu_id();
    pcpu   = rt_cpu_index(cpu_id);
    rt_spin_lock(&pcpu->spinlock);
    current_thread = pcpu->current_thread;

#ifdef RT_USING_SIGNALS
    if ((current_thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        /* if current_thread signal is in pending */

        if ((current_thread->stat & RT_THREAD_STAT_SIGNAL_MASK) & RT_THREAD_STAT_SIGNAL_PENDING)
        {
#ifdef RT_USING_SMART
            rt_thread_wakeup(current_thread);
#else
            rt_thread_resume(current_thread);
#endif
        }
    }
#endif /* RT_USING_SIGNALS */

    if (pcpu->irq_switch_flag == 0)
    {
        rt_spin_unlock(&pcpu->spinlock);
        rt_spin_unlock(&_spinlock);
        rt_hw_local_irq_enable(level);
        return;
    }
    rt_spin_lock(&(current_thread->spinlock));
    if (rt_atomic_load(&(current_thread->critical_lock_nest)) == 0 &&
        rt_atomic_load(&(pcpu->irq_nest)) == 0)
    {
        rt_ubase_t highest_ready_priority;

        /* clear irq switch flag */
        pcpu->irq_switch_flag = 0;

        if (rt_thread_ready_priority_group != 0 || pcpu->priority_group != 0)
        {
            to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);
            current_thread->oncpu = RT_CPU_DETACHED;
            if ((current_thread->stat & RT_THREAD_STAT_MASK) == RT_THREAD_RUNNING)
            {
                if (current_thread->bind_cpu == RT_CPUS_NR || current_thread->bind_cpu == cpu_id)
                {
                    if (current_thread->current_priority < highest_ready_priority)
                    {
                        to_thread = current_thread;
                    }
                    else if (current_thread->current_priority == highest_ready_priority && (current_thread->stat & RT_THREAD_STAT_YIELD_MASK) == 0)
                    {
                        to_thread = current_thread;
                    }
                    else
                    {
                        _rt_schedule_insert_thread(current_thread, RT_FALSE);
                    }
                }
                else
                {
                    _rt_schedule_insert_thread(current_thread, RT_FALSE);
                }
                current_thread->stat &= ~RT_THREAD_STAT_YIELD_MASK;
            }

            if (to_thread != current_thread)
            {
                rt_spin_lock(&(to_thread->spinlock));
            }
            to_thread->oncpu = cpu_id;
            if (to_thread != current_thread)
            {
                /* if the destination thread is not the same as current thread */

                pcpu->current_priority = (rt_uint8_t)highest_ready_priority;

                RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (current_thread, to_thread));

                _rt_schedule_remove_thread(to_thread, RT_FALSE);
                to_thread->stat = RT_THREAD_RUNNING | (to_thread->stat & ~RT_THREAD_STAT_MASK);

#ifdef RT_USING_OVERFLOW_CHECK
                _scheduler_stack_check(to_thread);
#endif /* RT_USING_OVERFLOW_CHECK */
                LOG_D("switch in interrupt");

                RT_OBJECT_HOOK_CALL(rt_scheduler_switch_hook, (current_thread));

                rt_spin_unlock(&(to_thread->spinlock));
                rt_spin_unlock(&pcpu->spinlock);
                rt_spin_unlock(&_spinlock);

                need_unlock = RT_FALSE;
                rt_hw_context_switch_interrupt(context, (rt_ubase_t)&current_thread->sp,
                        (rt_ubase_t)&to_thread->sp, to_thread);
            }
        }
    }

    if(need_unlock)
    {
        rt_spin_unlock(&(current_thread->spinlock));
        rt_spin_unlock(&pcpu->spinlock);
        rt_spin_unlock(&_spinlock);
    }

    rt_hw_local_irq_enable(level);
}

/**
 * @brief This function will insert a thread to the system ready queue. The state of
 *        thread will be set as READY and the thread will be removed from suspend queue.
 *
 * @param thread is the thread to be inserted.
 *
 * @note  Please do not invoke this function in user application.
 */
void rt_schedule_insert_thread(struct rt_thread *thread)
{
    rt_base_t level;
    level = rt_spin_lock_irqsave(&_spinlock);
    _rt_schedule_insert_thread(thread, RT_TRUE);
    rt_spin_unlock_irqrestore(&_spinlock, level);
}

/**
 * @brief This function will remove a thread from system ready queue.
 *
 * @param thread is the thread to be removed.
 *
 * @note  Please do not invoke this function in user application.
 */
void rt_schedule_remove_thread(struct rt_thread *thread)
{
    rt_base_t level;
    level = rt_spin_lock_irqsave(&_spinlock);
    rt_spin_lock(&thread->spinlock);
    _rt_schedule_remove_thread(thread, RT_TRUE);
    rt_spin_unlock(&thread->spinlock);
    rt_spin_unlock_irqrestore(&_spinlock, level);
}

/**
 * @brief This function will lock the thread scheduler.
 */
void rt_enter_critical(void)
{
    rt_base_t level;
    struct rt_thread *current_thread;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    current_thread = rt_cpu_self()->current_thread;
    if (!current_thread)
    {
        rt_hw_local_irq_enable(level);
        return;
    }

    /* critical for local cpu */
    rt_atomic_add(&(current_thread->critical_lock_nest), 1);

    /* enable interrupt */
    rt_hw_local_irq_enable(level);
}
RTM_EXPORT(rt_enter_critical);

/**
 * @brief This function will unlock the thread scheduler.
 */
void rt_exit_critical(void)
{
    rt_base_t level;
    struct rt_thread *current_thread;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    current_thread = rt_cpu_self()->current_thread;
    if (!current_thread)
    {
        rt_hw_local_irq_enable(level);
        return;
    }

    rt_atomic_sub(&(current_thread->critical_lock_nest), 1);

    if (rt_atomic_load(&(current_thread->critical_lock_nest)) <= 0)
    {
        rt_atomic_store(&(current_thread->critical_lock_nest), 0);
        /* enable interrupt */
        rt_hw_local_irq_enable(level);

        rt_schedule();
    }
    else
    {
        /* enable interrupt */
        rt_hw_local_irq_enable(level);
    }
}
RTM_EXPORT(rt_exit_critical);

/**
 * @brief Get the scheduler lock level.
 *
 * @return the level of the scheduler lock. 0 means unlocked.
 */
rt_uint16_t rt_critical_level(void)
{
    struct rt_thread *current_thread = rt_cpu_self()->current_thread;
    return rt_atomic_load(&(current_thread->critical_lock_nest));
}
RTM_EXPORT(rt_critical_level);

/**@}*/
/**@endcond*/
