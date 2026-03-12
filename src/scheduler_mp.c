/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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
 * 2023-12-10     xqyjlj       use rt_hw_spinlock
 * 2024-01-05     Shell        Fixup of data racing in rt_critical_level
 * 2024-01-18     Shell        support rt_sched_thread of scheduling status for better mt protection
 * 2024-01-18     Shell        support rt_hw_thread_self to improve overall performance
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.scheduler"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
static struct rt_spinlock _mp_scheduler_lock;

#define SCHEDULER_LOCK_FLAG(percpu) ((percpu)->sched_lock_flag)

#define SCHEDULER_ENTER_CRITICAL(curthr)                    \
    do                                                      \
    {                                                       \
        if (curthr) RT_SCHED_CTX(curthr).critical_lock_nest++; \
    } while (0)

#define SCHEDULER_EXIT_CRITICAL(curthr)                     \
    do                                                      \
    {                                                       \
        if (curthr) RT_SCHED_CTX(curthr).critical_lock_nest--; \
    } while (0)

#define SCHEDULER_CONTEXT_LOCK(percpu)               \
    do                                               \
    {                                                \
        RT_ASSERT(SCHEDULER_LOCK_FLAG(percpu) == 0); \
        _fast_spin_lock(&_mp_scheduler_lock);        \
        SCHEDULER_LOCK_FLAG(percpu) = 1;             \
    } while (0)

#define SCHEDULER_CONTEXT_UNLOCK(percpu)             \
    do                                               \
    {                                                \
        RT_ASSERT(SCHEDULER_LOCK_FLAG(percpu) == 1); \
        SCHEDULER_LOCK_FLAG(percpu) = 0;             \
        _fast_spin_unlock(&_mp_scheduler_lock);      \
    } while (0)

#define SCHEDULER_LOCK(level)              \
    do                                     \
    {                                      \
        rt_thread_t _curthr;               \
        struct rt_cpu *_percpu;            \
        level = rt_hw_local_irq_disable(); \
        _percpu = rt_cpu_self();           \
        _curthr = _percpu->current_thread; \
        SCHEDULER_ENTER_CRITICAL(_curthr); \
        SCHEDULER_CONTEXT_LOCK(_percpu);   \
    } while (0)

#define SCHEDULER_UNLOCK(level)            \
    do                                     \
    {                                      \
        rt_thread_t _curthr;               \
        struct rt_cpu *_percpu;            \
        _percpu = rt_cpu_self();           \
        _curthr = _percpu->current_thread; \
        SCHEDULER_CONTEXT_UNLOCK(_percpu); \
        SCHEDULER_EXIT_CRITICAL(_curthr);  \
        rt_hw_local_irq_enable(level);     \
    } while (0)

#ifdef ARCH_USING_HW_THREAD_SELF
#define IS_CRITICAL_SWITCH_PEND(pcpu, curthr)  (RT_SCHED_CTX(curthr).critical_switch_flag)
#define SET_CRITICAL_SWITCH_FLAG(pcpu, curthr) (RT_SCHED_CTX(curthr).critical_switch_flag = 1)
#define CLR_CRITICAL_SWITCH_FLAG(pcpu, curthr) (RT_SCHED_CTX(curthr).critical_switch_flag = 0)

#else /* !ARCH_USING_HW_THREAD_SELF */
#define IS_CRITICAL_SWITCH_PEND(pcpu, curthr)  ((pcpu)->critical_switch_flag)
#define SET_CRITICAL_SWITCH_FLAG(pcpu, curthr) ((pcpu)->critical_switch_flag = 1)
#define CLR_CRITICAL_SWITCH_FLAG(pcpu, curthr) ((pcpu)->critical_switch_flag = 0)

#endif /* ARCH_USING_HW_THREAD_SELF */

static rt_uint32_t rt_thread_ready_priority_group;
#if RT_THREAD_PRIORITY_MAX > 32
/* Maximum priority level, 256 */
static rt_uint8_t rt_thread_ready_table[32];
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

/**
 * Used only on scheduler for optimization of control flows, where the critical
 * region is already guaranteed.
 */
rt_inline void _fast_spin_lock(struct rt_spinlock *lock)
{
    rt_hw_spin_lock(&lock->lock);

    RT_SPIN_LOCK_DEBUG(lock);
}

rt_inline void _fast_spin_unlock(struct rt_spinlock *lock)
{
    rt_base_t critical_level;
    RT_SPIN_UNLOCK_DEBUG(lock, critical_level);

    /* for the scenario of sched, we don't check critical level */
    RT_UNUSED(critical_level);

    rt_hw_spin_unlock(&lock->lock);
}

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static void (*rt_scheduler_hook)(struct rt_thread *from, struct rt_thread *to);
static void (*rt_scheduler_switch_hook)(struct rt_thread *tid);

/**
 * @addtogroup group_hook
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

/**
 * @addtogroup group_thread_management
 *
 * @cond DOXYGEN_SMP
 *
 * @{
 */

#if RT_THREAD_PRIORITY_MAX > 32

rt_inline rt_base_t _get_global_highest_ready_prio(void)
{
    rt_ubase_t number;
    rt_ubase_t highest_ready_priority;

    number = __rt_ffs(rt_thread_ready_priority_group) - 1;
    if (number != -1)
    {
        highest_ready_priority = (number << 3) + __rt_ffs(rt_thread_ready_table[number]) - 1;
    }
    else
    {
        highest_ready_priority = -1;
    }
    return highest_ready_priority;
}

rt_inline rt_base_t _get_local_highest_ready_prio(struct rt_cpu* pcpu)
{
    rt_ubase_t number;
    rt_ubase_t local_highest_ready_priority;

    number = __rt_ffs(pcpu->priority_group) - 1;
    if (number != -1)
    {
        local_highest_ready_priority = (number << 3) + __rt_ffs(pcpu->ready_table[number]) - 1;
    }
    else
    {
        local_highest_ready_priority = -1;
    }
    return local_highest_ready_priority;
}

#else /* if RT_THREAD_PRIORITY_MAX <= 32 */

rt_inline rt_base_t _get_global_highest_ready_prio(void)
{
    return __rt_ffs(rt_thread_ready_priority_group) - 1;
}

rt_inline rt_base_t _get_local_highest_ready_prio(struct rt_cpu* pcpu)
{
    return __rt_ffs(pcpu->priority_group) - 1;
}

#endif /* RT_THREAD_PRIORITY_MAX > 32 */

/*
 * get the highest priority thread in ready queue
 */
static struct rt_thread* _scheduler_get_highest_priority_thread(rt_ubase_t *highest_prio)
{
    struct rt_thread *highest_priority_thread;
    rt_ubase_t highest_ready_priority, local_highest_ready_priority;
    struct rt_cpu* pcpu = rt_cpu_self();

    highest_ready_priority = _get_global_highest_ready_prio();
    local_highest_ready_priority = _get_local_highest_ready_prio(pcpu);

    /* get highest ready priority thread */
    if (highest_ready_priority < local_highest_ready_priority)
    {
        *highest_prio = highest_ready_priority;

        highest_priority_thread = RT_THREAD_LIST_NODE_ENTRY(
            rt_thread_priority_table[highest_ready_priority].next);
    }
    else
    {
        *highest_prio = local_highest_ready_priority;
        if (local_highest_ready_priority != -1)
        {
            highest_priority_thread = RT_THREAD_LIST_NODE_ENTRY(
                pcpu->priority_table[local_highest_ready_priority].next);
        }
        else
        {
            highest_priority_thread = RT_NULL;
        }
    }

    RT_ASSERT(!highest_priority_thread ||
              rt_object_get_type(&highest_priority_thread->parent) == RT_Object_Class_Thread);
    return highest_priority_thread;
}

/**
 * @brief   set READY and insert thread to ready queue
 *
 * @note    caller must holding the `_mp_scheduler_lock` lock
 */
static void _sched_insert_thread_locked(struct rt_thread *thread)
{
    int cpu_id;
    int bind_cpu;
    rt_uint32_t cpu_mask;

    if ((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_READY)
    {
        /* already in ready queue */
        return ;
    }
    else if (RT_SCHED_CTX(thread).oncpu != RT_CPU_DETACHED)
    {
        /**
         * only YIELD -> READY, SUSPEND -> READY is allowed by this API. However,
         * this is a RUNNING thread. So here we reset it's status and let it go.
         */
        RT_SCHED_CTX(thread).stat = RT_THREAD_RUNNING | (RT_SCHED_CTX(thread).stat & ~RT_THREAD_STAT_MASK);
        return ;
    }

    /* READY thread, insert to ready queue */
    RT_SCHED_CTX(thread).stat = RT_THREAD_READY | (RT_SCHED_CTX(thread).stat & ~RT_THREAD_STAT_MASK);

    cpu_id   = rt_hw_cpu_id();
    bind_cpu = RT_SCHED_CTX(thread).bind_cpu;

    /* insert thread to ready list */
    if (bind_cpu == RT_CPUS_NR)
    {
#if RT_THREAD_PRIORITY_MAX > 32
        rt_thread_ready_table[RT_SCHED_PRIV(thread).number] |= RT_SCHED_PRIV(thread).high_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        rt_thread_ready_priority_group |= RT_SCHED_PRIV(thread).number_mask;

        /* there is no time slices left(YIELD), inserting thread before ready list*/
        if((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_YIELD_MASK) != 0)
        {
            rt_list_insert_before(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority]),
                                  &RT_THREAD_LIST_NODE(thread));
        }
        /* there are some time slices left, inserting thread after ready list to schedule it firstly at next time*/
        else
        {
            rt_list_insert_after(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority]),
                                 &RT_THREAD_LIST_NODE(thread));
        }

        cpu_mask = RT_CPU_MASK ^ (1 << cpu_id);
        rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
    }
    else
    {
        struct rt_cpu *pcpu = rt_cpu_index(bind_cpu);

#if RT_THREAD_PRIORITY_MAX > 32
        pcpu->ready_table[RT_SCHED_PRIV(thread).number] |= RT_SCHED_PRIV(thread).high_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        pcpu->priority_group |= RT_SCHED_PRIV(thread).number_mask;

        /* there is no time slices left(YIELD), inserting thread before ready list*/
        if((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_YIELD_MASK) != 0)
        {
            rt_list_insert_before(&(rt_cpu_index(bind_cpu)->priority_table[RT_SCHED_PRIV(thread).current_priority]),
                                  &RT_THREAD_LIST_NODE(thread));
        }
        /* there are some time slices left, inserting thread after ready list to schedule it firstly at next time*/
        else
        {
            rt_list_insert_after(&(rt_cpu_index(bind_cpu)->priority_table[RT_SCHED_PRIV(thread).current_priority]),
                                 &RT_THREAD_LIST_NODE(thread));
        }

        if (cpu_id != bind_cpu)
        {
            cpu_mask = 1 << bind_cpu;
            rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
        }
    }

    LOG_D("insert thread[%.*s], the priority: %d",
          RT_NAME_MAX, thread->parent.name, RT_SCHED_PRIV(thread).current_priority);
}

/* remove thread from ready queue */
static void _sched_remove_thread_locked(struct rt_thread *thread)
{
    LOG_D("%s [%.*s], the priority: %d", __func__,
          RT_NAME_MAX, thread->parent.name,
          RT_SCHED_PRIV(thread).current_priority);

    /* remove thread from ready list */
    rt_list_remove(&RT_THREAD_LIST_NODE(thread));

    if (RT_SCHED_CTX(thread).bind_cpu == RT_CPUS_NR)
    {
        if (rt_list_isempty(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority])))
        {
#if RT_THREAD_PRIORITY_MAX > 32
            rt_thread_ready_table[RT_SCHED_PRIV(thread).number] &= ~RT_SCHED_PRIV(thread).high_mask;
            if (rt_thread_ready_table[RT_SCHED_PRIV(thread).number] == 0)
            {
                rt_thread_ready_priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
            }
#else
            rt_thread_ready_priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        }
    }
    else
    {
        struct rt_cpu *pcpu = rt_cpu_index(RT_SCHED_CTX(thread).bind_cpu);

        if (rt_list_isempty(&(pcpu->priority_table[RT_SCHED_PRIV(thread).current_priority])))
        {
#if RT_THREAD_PRIORITY_MAX > 32
            pcpu->ready_table[RT_SCHED_PRIV(thread).number] &= ~RT_SCHED_PRIV(thread).high_mask;
            if (pcpu->ready_table[RT_SCHED_PRIV(thread).number] == 0)
            {
                pcpu->priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
            }
#else
            pcpu->priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        }
    }
}

/**
 * @brief Initialize the system scheduler.
 *
 * @note This function must be called before any thread scheduling can occur.
 *       It prepares the scheduler data structures for multi-core operation.
 *
 * @note This function has both MP version and UP version.
 */
/*
 * Don't include below in doxygen document due to they are MP version only.
 * @details This function performs the following initialization tasks:
 *          - Initializes the global scheduler spinlock for multi-core synchronization.
 *          - Initializes the global priority table for saving ready threads of all priority levels.
 *          - For each CPU core:
 *            * Initializes per-CPU priority tables
 *            * Sets initial CPU state (irq_switch_flag, current_priority, etc.)
 *            * Initializes per-CPU ready tables (if priority > 32)
 *            * Initializes per-CPU spinlock (if RT_USING_SMART is defined)
 *          - Initializes the global ready priority group and tables (if priority > 32) as bitmaps for all priorities.
 */
void rt_system_scheduler_init(void)
{
    int cpu;
    rt_base_t offset;

    LOG_D("start scheduler: max priority 0x%02x",
          RT_THREAD_PRIORITY_MAX);

    rt_spin_lock_init(&_mp_scheduler_lock);

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

#ifdef RT_USING_SMART
        rt_spin_lock_init(&(pcpu->spinlock));
#endif
    }

    /* initialize ready priority group */
    rt_thread_ready_priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
    /* initialize ready table */
    rt_memset(rt_thread_ready_table, 0, sizeof(rt_thread_ready_table));
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
}

/**
 * @brief Start the system scheduler and switch to the highest priority thread.
 *
 * @note This function will not return after successful execution.
 *       It performs the initial thread switch during system startup.
 *       The scheduler must be initialized before calling this function.
 *
 * @note This function has both MP version and UP version.
 */
/*
 * Don't include below in doxygen document due to they are MP version only.
 * @details This function performs the following operations:
 *          - Releases legacy CPU lock (if any)
 *          - Disables interrupts to ensure atomic operation
 *          - Acquires scheduler lock for thread safety
 *          - Selects the highest priority thread from ready queue
 *          - Removes the selected thread from ready queue
 *          - Assigns current CPU core to the selected thread
 *          - Performs context switch to the selected thread
 */
void rt_system_scheduler_start(void)
{
    struct rt_thread *to_thread;
    rt_ubase_t highest_ready_priority;

    /*
     * legacy rt_cpus_lock. some bsp codes still use it as for it's critical
     * region. Since scheduler is never touching this, here we just release it
     * on the entry.
     */
    rt_hw_spin_unlock(&_cpus_lock);

    /* ISR will corrupt the coherency of running frame */
    rt_hw_local_irq_disable();

    /*
     * for the accessing of the scheduler context. Noted that we don't have
     * current_thread at this point
     */
    _fast_spin_lock(&_mp_scheduler_lock);

    /* get the thread scheduling to */
    to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);
    RT_ASSERT(to_thread);

    /* to_thread is picked to running on current core, so remove it from ready queue */
    _sched_remove_thread_locked(to_thread);

    /* dedigate current core to `to_thread` */
    RT_SCHED_CTX(to_thread).oncpu = rt_hw_cpu_id();
    RT_SCHED_CTX(to_thread).stat = RT_THREAD_RUNNING;

    LOG_D("[cpu#%d] switch to priority#%d thread:%.*s(sp:0x%08x)",
          rt_hw_cpu_id(), RT_SCHED_PRIV(to_thread).current_priority,
          RT_NAME_MAX, to_thread->parent.name, to_thread->sp);

    _fast_spin_unlock(&_mp_scheduler_lock);

    /* switch to new thread */
    rt_hw_context_switch_to((rt_ubase_t)&to_thread->sp, to_thread);

    /* never come back */
}

/**
 * @brief This function will handle IPI interrupt and do a scheduling in system.
 *
 * This function should be invoke or register as ISR in BSP.
 *
 * @param vector The number of IPI interrupt for system scheduling.
 *
 * @param param Not used, and can be set to RT_NULL.
 *
 * @note This function only has MP version.
 */
void rt_scheduler_ipi_handler(int vector, void *param)
{
    rt_schedule();
}

/**
 * @brief Lock the system scheduler
 *
 * @param plvl Pointer to the object where lock level stores to
 *
 * @return rt_err_t
 *         - RT_EOK on success
 *         - -RT_EINVAL if plvl is NULL
 *
 * @note This function has both MP version and UP version.
 */
rt_err_t rt_sched_lock(rt_sched_lock_level_t *plvl)
{
    rt_base_t level;
    if (!plvl)
        return -RT_EINVAL;

    SCHEDULER_LOCK(level);
    *plvl = level;

    return RT_EOK;
}

/**
 * @brief Unlock the scheduler and restore the interrupt level
 *
 * @param level The interrupt level to restore (previously saved by rt_sched_lock)
 *
 * @return rt_err_t Always returns RT_EOK
 *
 * @note This function has both MP version and UP version.
 */
rt_err_t rt_sched_unlock(rt_sched_lock_level_t level)
{
    SCHEDULER_UNLOCK(level);

    return RT_EOK;
}

/**
 * @brief Check if the scheduler is currently locked
 *
 * This function checks the scheduler lock status in a thread-safe manner
 * by temporarily disabling interrupts to get consistent state.
 *
 * @return rt_bool_t Returns RT_TRUE if scheduler is locked, RT_FALSE otherwise
 *
 * @note This function only has MP version.
 */
rt_bool_t rt_sched_is_locked(void)
{
    rt_bool_t rc;
    rt_base_t level;
    struct rt_cpu *pcpu;

    level = rt_hw_local_irq_disable();
    pcpu = rt_cpu_self();

    /* get lock stat which is a boolean value */
    rc = pcpu->sched_lock_flag;

    rt_hw_local_irq_enable(level);
    return rc;
}

/**
 * @brief Pick the highest runnable thread, and pass the control to it
 *
 * @note caller should hold the scheduler context lock. lock will be released
 *       before return from this routine
 */
static rt_thread_t _prepare_context_switch_locked(int cpu_id,
                                                  struct rt_cpu *pcpu,
                                                  rt_thread_t current_thread)
{
    rt_thread_t to_thread = RT_NULL;
    rt_ubase_t highest_ready_priority;

    /* quickly check if any other ready threads queuing */
    if (rt_thread_ready_priority_group != 0 || pcpu->priority_group != 0)
    {
        /* pick the highest ready thread */
        to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);

        /* detach current thread from percpu scheduling context */
        RT_SCHED_CTX(current_thread).oncpu = RT_CPU_DETACHED;

        /* check if current thread should be put to ready queue, or scheduling again */
        if ((RT_SCHED_CTX(current_thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_RUNNING)
        {
            /* check if current thread can be running on current core again */
            if (RT_SCHED_CTX(current_thread).bind_cpu == RT_CPUS_NR
                || RT_SCHED_CTX(current_thread).bind_cpu == cpu_id)
            {
                /* if current_thread is the highest runnable thread */
                if (RT_SCHED_PRIV(current_thread).current_priority < highest_ready_priority)
                {
                    to_thread = current_thread;
                }
                /* or no higher-priority thread existed and it has remaining ticks */
                else if (RT_SCHED_PRIV(current_thread).current_priority == highest_ready_priority &&
                         (RT_SCHED_CTX(current_thread).stat & RT_THREAD_STAT_YIELD_MASK) == 0)
                {
                    to_thread = current_thread;
                }
                /* otherwise give out the core */
                else
                {
                    _sched_insert_thread_locked(current_thread);
                }
            }
            else
            {
                /* put current_thread to ready queue of another core */
                _sched_insert_thread_locked(current_thread);
            }

            /* consume the yield flags after scheduling */
            RT_SCHED_CTX(current_thread).stat &= ~RT_THREAD_STAT_YIELD_MASK;
        }

        /**
         * Now destination thread is determined, core is passed to it. Though
         * the percpu scheduling context is not updated here, since the cpu
         * is locked contiguously before all the scheduling works are done, it's
         * safe to observe that current thread as the running thread on this
         * core for any observers if they properly do the synchronization
         * (take the SCHEDULER_LOCK).
         */
        RT_SCHED_CTX(to_thread).oncpu = cpu_id;

        /* check if context switch is required */
        if (to_thread != current_thread)
        {
            pcpu->current_priority = (rt_uint8_t)highest_ready_priority;

            RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (current_thread, to_thread));

            /* remove to_thread from ready queue and update its status to RUNNING */
            _sched_remove_thread_locked(to_thread);
            RT_SCHED_CTX(to_thread).stat = RT_THREAD_RUNNING | (RT_SCHED_CTX(to_thread).stat & ~RT_THREAD_STAT_MASK);

            RT_SCHEDULER_STACK_CHECK(to_thread);

            RT_OBJECT_HOOK_CALL(rt_scheduler_switch_hook, (current_thread));
        }
        else
        {
            /* current thread is still the best runnable thread */
            to_thread = RT_NULL;
        }
    }
    else
    {
        /* no ready threads */
        to_thread = RT_NULL;
    }

    return to_thread;
}

#ifdef RT_USING_SIGNALS
/**
 * @brief Preprocess pending signals for a suspended thread
 *
 * @param current_thread The thread to check for pending signals
 *
 * @details This function checks if the specified thread is suspended and has pending signals.
 *          If both conditions are met, it will wake up/resume the thread to process the signals.
 */
static void _sched_thread_preprocess_signal(struct rt_thread *current_thread)
{
    /* should process signal? */
    if (rt_sched_thread_is_suspended(current_thread))
    {
        /* if current_thread signal is in pending */
        if ((RT_SCHED_CTX(current_thread).stat & RT_THREAD_STAT_SIGNAL_MASK) & RT_THREAD_STAT_SIGNAL_PENDING)
        {
#ifdef RT_USING_SMART
            rt_thread_wakeup(current_thread);
#else
            rt_thread_resume(current_thread);
#endif
        }
    }
}

/**
 * @brief Process pending signals for the current thread
 *
 * @param current_thread The thread to process signals for
 *
 * @details This function:
 *          - Locks the scheduler to ensure thread safety
 *          - Checks if the thread has pending signals
 *          - If signals are pending:
 *            * Clears the pending flag
 *            * Unlocks the scheduler
 *            * Calls signal handler to process the signals
 *          - If no signals pending, simply unlocks the scheduler
 */
static void _sched_thread_process_signal(struct rt_thread *current_thread)
{
    rt_base_t level;
    SCHEDULER_LOCK(level);

    /* check stat of thread for signal */
    if (RT_SCHED_CTX(current_thread).stat & RT_THREAD_STAT_SIGNAL_PENDING)
    {
        extern void rt_thread_handle_sig(rt_bool_t clean_state);

        RT_SCHED_CTX(current_thread).stat &= ~RT_THREAD_STAT_SIGNAL_PENDING;

        SCHEDULER_UNLOCK(level);

        /* check signal status */
        rt_thread_handle_sig(RT_TRUE);
    }
    else
    {
        SCHEDULER_UNLOCK(level);
    }

    /* lock is released above */
}

#define SCHED_THREAD_PREPROCESS_SIGNAL(pcpu, curthr)    \
    do                                            \
    {                                             \
        SCHEDULER_CONTEXT_LOCK(pcpu);   \
        _sched_thread_preprocess_signal(curthr);  \
        SCHEDULER_CONTEXT_UNLOCK(pcpu); \
    } while (0)
#define SCHED_THREAD_PREPROCESS_SIGNAL_LOCKED(curthr) \
    _sched_thread_preprocess_signal(curthr)
#define SCHED_THREAD_PROCESS_SIGNAL(curthr) _sched_thread_process_signal(curthr)

#else /* ! RT_USING_SIGNALS */

#define SCHED_THREAD_PREPROCESS_SIGNAL(pcpu, curthr)
#define SCHED_THREAD_PREPROCESS_SIGNAL_LOCKED(curthr)
#define SCHED_THREAD_PROCESS_SIGNAL(curthr)
#endif /* RT_USING_SIGNALS */

/**
 * @brief Unlock scheduler and perform rescheduling if needed
 *
 * @param level The scheduler lock level obtained from rt_sched_lock()
 *
 * @return rt_err_t
 *   - RT_EOK: Success
 *   - -RT_EBUSY: Scheduler not available
 *   - -RT_ESCHEDISR: Called in interrupt context
 *   - -RT_ESCHEDLOCKED: Scheduler still locked by others
 *
 * @details This function:
 *   - Releases scheduler lock at specified level
 *   - Checks if rescheduling is needed
 *   - If needed, finds highest priority thread and switches to it
 *   - Processes pending signals for current thread
 *   - Handles various error conditions
 *
 * @note Must be called in pair with rt_sched_lock()
 *       May trigger context switch if conditions met
 *
 * @note This function has both MP version and UP version.
 */
rt_err_t rt_sched_unlock_n_resched(rt_sched_lock_level_t level)
{
    struct rt_thread *to_thread;
    struct rt_thread *current_thread;
    struct rt_cpu    *pcpu;
    int              cpu_id;
    rt_err_t         error = RT_EOK;

    cpu_id = rt_hw_cpu_id();
    pcpu   = rt_cpu_index(cpu_id);
    current_thread = pcpu->current_thread;

    if (!current_thread)
    {
        /* scheduler is unavailable yet */
        SCHEDULER_CONTEXT_UNLOCK(pcpu);
        SCHEDULER_EXIT_CRITICAL(current_thread);
        rt_hw_local_irq_enable(level);
        return -RT_EBUSY;
    }

    /* whether do switch in interrupt */
    if (rt_atomic_load(&(pcpu->irq_nest)))
    {
        pcpu->irq_switch_flag = 1;
        SCHEDULER_CONTEXT_UNLOCK(pcpu);
        SCHEDULER_EXIT_CRITICAL(current_thread);
        rt_hw_local_irq_enable(level);
        return -RT_ESCHEDISR;
    }

    /* prepare current_thread for processing if signals existed */
    SCHED_THREAD_PREPROCESS_SIGNAL_LOCKED(current_thread);

    /* whether caller had locked the local scheduler already */
    if (RT_SCHED_CTX(current_thread).critical_lock_nest > 1)
    {
        /* leaving critical region of global context since we can't schedule */
        SCHEDULER_CONTEXT_UNLOCK(pcpu);

        SET_CRITICAL_SWITCH_FLAG(pcpu, current_thread);
        error = -RT_ESCHEDLOCKED;

        SCHEDULER_EXIT_CRITICAL(current_thread);
    }
    else
    {
        /* flush critical switch flag since a scheduling is done */
        CLR_CRITICAL_SWITCH_FLAG(pcpu, current_thread);

        /* pick the highest runnable thread, and pass the control to it */
        to_thread = _prepare_context_switch_locked(cpu_id, pcpu, current_thread);
        if (to_thread)
        {
            /* switch to new thread */
            LOG_D("[cpu#%d] UNLOCK switch to priority#%d "
                  "thread:%.*s(sp:0x%08x), "
                  "from thread:%.*s(sp: 0x%08x)",
                  cpu_id, RT_SCHED_PRIV(to_thread).current_priority,
                  RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
                  RT_NAME_MAX, current_thread->parent.name, current_thread->sp);

            rt_hw_context_switch((rt_ubase_t)&current_thread->sp,
                                 (rt_ubase_t)&to_thread->sp, to_thread);
        }
        else
        {
            SCHEDULER_CONTEXT_UNLOCK(pcpu);
            SCHEDULER_EXIT_CRITICAL(current_thread);
        }
    }

    /* leaving critical region of percpu scheduling context */
    rt_hw_local_irq_enable(level);

    /* process signals on thread if any existed */
    SCHED_THREAD_PROCESS_SIGNAL(current_thread);

    return error;
}

/**
 * @brief This function will perform one scheduling. It will select one thread
 *        with the highest priority level in global ready queue or local ready queue,
 *        then switch to it.
 *
 * @note This function has both MP version and UP version.
 */

/*
 * NOTE: not in doxygen due to these info. are special for MP version
 * @details This function performs the following operations:
 *   - Disables interrupts to enter critical section
 *   - Gets current CPU and thread context
 *   - Checks if called from interrupt context
 *   - Finds highest priority ready thread
 *   - Performs context switch if needed
 *   - Processes pending signals
 *   - Restores interrupt state
 */
void rt_schedule(void)
{
    rt_base_t level;
    struct rt_thread *to_thread;
    struct rt_thread *current_thread;
    struct rt_cpu    *pcpu;
    int              cpu_id;

    /* enter ciritical region of percpu scheduling context */
    level = rt_hw_local_irq_disable();

    /* get percpu scheduling context */
    cpu_id = rt_hw_cpu_id();
    pcpu   = rt_cpu_index(cpu_id);
    current_thread = pcpu->current_thread;

    /* whether do switch in interrupt */
    if (rt_atomic_load(&(pcpu->irq_nest)))
    {
        pcpu->irq_switch_flag = 1;
        rt_hw_local_irq_enable(level);
        return ; /* -RT_ESCHEDISR */
    }

    /* forbid any recursive entries of schedule() */
    SCHEDULER_ENTER_CRITICAL(current_thread);

    /* prepare current_thread for processing if signals existed */
    SCHED_THREAD_PREPROCESS_SIGNAL(pcpu, current_thread);

    /* whether caller had locked the local scheduler already */
    if (RT_SCHED_CTX(current_thread).critical_lock_nest > 1)
    {
        SET_CRITICAL_SWITCH_FLAG(pcpu, current_thread);

        SCHEDULER_EXIT_CRITICAL(current_thread);

        /* -RT_ESCHEDLOCKED */
    }
    else
    {
        /* flush critical switch flag since a scheduling is done */
        CLR_CRITICAL_SWITCH_FLAG(pcpu, current_thread);
        pcpu->irq_switch_flag = 0;

        /*
         * take the context lock before we do the real scheduling works. Context
         * lock will be released before returning from this _schedule_locked()
         */
        SCHEDULER_CONTEXT_LOCK(pcpu);

        /* pick the highest runnable thread, and pass the control to it */
        to_thread = _prepare_context_switch_locked(cpu_id, pcpu, current_thread);

        if (to_thread)
        {
            LOG_D("[cpu#%d] switch to priority#%d "
                  "thread:%.*s(sp:0x%08x), "
                  "from thread:%.*s(sp: 0x%08x)",
                  cpu_id, RT_SCHED_PRIV(to_thread).current_priority,
                  RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
                  RT_NAME_MAX, current_thread->parent.name, current_thread->sp);

            rt_hw_context_switch((rt_ubase_t)&current_thread->sp,
                                 (rt_ubase_t)&to_thread->sp, to_thread);
        }
        else
        {
            /* current thread continue to take the core */
            SCHEDULER_CONTEXT_UNLOCK(pcpu);
            SCHEDULER_EXIT_CRITICAL(current_thread);
        }
    }

    /* leaving critical region of percpu scheduling context */
    rt_hw_local_irq_enable(level);

    /* process signals on thread if any existed */
    SCHED_THREAD_PROCESS_SIGNAL(current_thread);
}

/**
 * @brief Perform thread scheduling after an interrupt context switch
 *
 * @param context The interrupt context pointer
 *
 * @details This function handles scheduling when returning from interrupt context:
 *   - Checks if scheduling is needed (irq_switch_flag set)
 *   - If needed, finds highest priority ready thread
 *   - Performs context switch to new thread if available
 *   - Handles cases where scheduler is locked or still in interrupt context
 *   - Processes pending signals before scheduling
 *
 * @note This function only has MP version.
 */
void rt_scheduler_do_irq_switch(void *context)
{
    int              cpu_id;
    rt_base_t        level;
    struct rt_cpu    *pcpu;
    struct rt_thread *to_thread;
    struct rt_thread *current_thread;

    level = rt_hw_local_irq_disable();

    cpu_id = rt_hw_cpu_id();
    pcpu   = rt_cpu_index(cpu_id);
    current_thread = pcpu->current_thread;

    /* forbid any recursive entries of schedule() */
    SCHEDULER_ENTER_CRITICAL(current_thread);

    SCHED_THREAD_PREPROCESS_SIGNAL(pcpu, current_thread);

    /* any pending scheduling existed? */
    if (pcpu->irq_switch_flag == 0)
    {
        /* if no, just continue execution of current_thread */
        SCHEDULER_EXIT_CRITICAL(current_thread);
        rt_hw_local_irq_enable(level);
        return;
    }

    /* whether caller had locked the local scheduler already */
    if (RT_SCHED_CTX(current_thread).critical_lock_nest > 1)
    {
        SET_CRITICAL_SWITCH_FLAG(pcpu, current_thread);
        SCHEDULER_EXIT_CRITICAL(current_thread);
    }
    else if (rt_atomic_load(&(pcpu->irq_nest)) == 0)
    {
        /* flush critical & irq switch flag since a scheduling is done */
        CLR_CRITICAL_SWITCH_FLAG(pcpu, current_thread);
        pcpu->irq_switch_flag = 0;

        SCHEDULER_CONTEXT_LOCK(pcpu);

        /* pick the highest runnable thread, and pass the control to it */
        to_thread = _prepare_context_switch_locked(cpu_id, pcpu, current_thread);
        if (to_thread)
        {
            LOG_D("[cpu#%d] IRQ switch to priority#%d "
                  "thread:%.*s(sp:0x%08x), "
                  "from thread:%.*s(sp: 0x%08x)",
                  cpu_id, RT_SCHED_PRIV(to_thread).current_priority,
                  RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
                  RT_NAME_MAX, current_thread->parent.name, current_thread->sp);

            rt_hw_context_switch_interrupt(context, (rt_ubase_t)&current_thread->sp,
                                           (rt_ubase_t)&to_thread->sp, to_thread);
        }
        else
        {
            /* current thread continue to take the core */
            SCHEDULER_CONTEXT_UNLOCK(pcpu);
            SCHEDULER_EXIT_CRITICAL(current_thread);
        }
    }
    else
    {
        SCHEDULER_EXIT_CRITICAL(current_thread);
    }

    /* leaving critical region of percpu scheduling context */
    rt_hw_local_irq_enable(level);
}

/**
 * @brief This function will insert a thread to the system ready queue. The state of
 *        thread will be set as READY and the thread will be removed from suspend queue.
 *
 * @param thread The thread to be inserted.
 *
 * @note  Please do not invoke this function in user application.
 *        Caller must hold the scheduler lock
 *
 * @note This function has both MP version and UP version.
 */
void rt_sched_insert_thread(struct rt_thread *thread)
{
    RT_ASSERT(thread != RT_NULL);
    RT_SCHED_DEBUG_IS_LOCKED;

    /* set READY and insert thread to ready queue */
    _sched_insert_thread_locked(thread);
}

/**
 * @brief This function will remove a thread from system ready queue.
 *
 * @param thread The thread to be removed.
 *
 * @note  Please do not invoke this function in user application.
 *
 * @note This function has both MP version and UP version.
 */
void rt_sched_remove_thread(struct rt_thread *thread)
{
    RT_ASSERT(thread != RT_NULL);
    RT_SCHED_DEBUG_IS_LOCKED;

    /* remove thread from scheduler ready list  */
    _sched_remove_thread_locked(thread);

    RT_SCHED_CTX(thread).stat = RT_THREAD_SUSPEND_UNINTERRUPTIBLE;
}

/**
 * @brief Initialize thread's scheduling private data
 *
 * @param thread The thread to be initialized
 * @param tick Initial time slice value for the thread
 * @param priority Initial priority of the thread
 *
 * @details This function performs the following initialization:
 *   - Initializes thread's ready list node
 *   - Sets initial and current priority (must be < RT_THREAD_PRIORITY_MAX)
 *   - Initializes priority bitmasks (handles >32 priorities if needed)
 *   - Sets initial time slice values
 *   - For SMP systems, initializes critical section nesting counter
 *
 * @note This function has both MP version and UP version.
 */
void rt_sched_thread_init_priv(struct rt_thread *thread, rt_uint32_t tick, rt_uint8_t priority)
{
    rt_list_init(&RT_THREAD_LIST_NODE(thread));

    /* priority init */
    RT_ASSERT(priority < RT_THREAD_PRIORITY_MAX);
    RT_SCHED_PRIV(thread).init_priority    = priority;
    RT_SCHED_PRIV(thread).current_priority = priority;

    /* don't add to scheduler queue as init thread */
    RT_SCHED_PRIV(thread).number_mask = 0;
#if RT_THREAD_PRIORITY_MAX > 32
    RT_SCHED_PRIV(thread).number = 0;
    RT_SCHED_PRIV(thread).high_mask = 0;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* tick init */
    RT_SCHED_PRIV(thread).init_tick = tick;
    RT_SCHED_PRIV(thread).remaining_tick = tick;

#ifdef RT_USING_SMP

    /* lock init */
    RT_SCHED_CTX(thread).critical_lock_nest = 0;
#endif /* RT_USING_SMP */

}

/**
 * @brief Initialize thread scheduling attributes for startup
 *
 * @param thread The thread to be initialized
 *
 * @details This function:
 *   - For systems with >32 priorities:
 *     * Sets priority number (5 bits)
 *     * Initializes number_mask and high_mask (3 bits)
 *   - For systems with <=32 priorities:
 *     * Initializes number_mask
 *   - Sets thread state to SUSPEND
 *
 * @note This is a lockless operation as it's called during thread creation
 *       when no concurrent access is possible
 *
 * @note This function has both MP version and UP version.
 */
void rt_sched_thread_startup(struct rt_thread *thread)
{
#if RT_THREAD_PRIORITY_MAX > 32
    RT_SCHED_PRIV(thread).number = RT_SCHED_PRIV(thread).current_priority >> 3;            /* 5bit */
    RT_SCHED_PRIV(thread).number_mask = 1L << RT_SCHED_PRIV(thread).number;
    RT_SCHED_PRIV(thread).high_mask = 1L << (RT_SCHED_PRIV(thread).current_priority & 0x07);  /* 3bit */
#else
    RT_SCHED_PRIV(thread).number_mask = 1L << RT_SCHED_PRIV(thread).current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* change thread stat, so we can resume it */
    RT_SCHED_CTX(thread).stat = RT_THREAD_SUSPEND;
}

/**
 * @brief Update thread scheduling status after context switch
 *
 * @param thread The thread that will be running after the context switch
 *
 * @details This function performs critical post-context-switch operations:
 *   - Verifies interrupts are disabled (RT_ASSERT)
 *   - Releases scheduler lock from previous thread if exists
 *   - Updates current thread pointer for the CPU
 *   - Must be called with interrupts disabled
 *
 * @note this operation is taken as an atomic operation of the update of SP.
 *       Since the local irq is disabled, it's okay to assume that the stack
 *       will not be modified meanwhile.
 *
 * @note This function only has MP version.
 */
void rt_sched_post_ctx_switch(struct rt_thread *thread)
{
    struct rt_cpu* pcpu = rt_cpu_self();
    rt_thread_t from_thread = pcpu->current_thread;

    RT_ASSERT(rt_hw_interrupt_is_disabled());

    if (from_thread)
    {
        RT_ASSERT(RT_SCHED_CTX(from_thread).critical_lock_nest == 1);

        /* release the scheduler lock since we are done with critical region */
        RT_SCHED_CTX(from_thread).critical_lock_nest = 0;
        SCHEDULER_CONTEXT_UNLOCK(pcpu);
    }
    /* safe to access since irq is masked out */
    pcpu->current_thread = thread;
}

#ifdef RT_DEBUGING_CRITICAL

static volatile int _critical_error_occurred = 0;

/**
 * @brief Safely exit critical section with level checking
 *
 * @param critical_level The expected critical level to match
 *
 * @details This function provides a safe way to exit critical sections by:
 *   - Verifying the current critical level matches the expected level
 *   - If mismatch detected (debug build only):
 *     * Prints error message with current and expected levels
 *     * Triggers backtrace for debugging
 *     * Enters infinite loop to halt execution
 *   - Always calls rt_exit_critical() to ensure critical section is exited
 *
 * @note This is primarily used for debugging critical section mismatches.
 *
 * @note This function has both MP version and UP version.
 */
void rt_exit_critical_safe(rt_base_t critical_level)
{
    struct rt_cpu *pcpu = rt_cpu_self();
    rt_thread_t current_thread = pcpu->current_thread;
    if (current_thread && !_critical_error_occurred)
    {
        if (critical_level != RT_SCHED_CTX(current_thread).critical_lock_nest)
        {
            int dummy = 1;
            _critical_error_occurred = 1;

            rt_kprintf("%s: un-compatible critical level\n" \
                       "\tCurrent %d\n\tCaller %d\n",
                       __func__, RT_SCHED_CTX(current_thread).critical_lock_nest,
                       critical_level);
            rt_backtrace();

            while (dummy) ;
        }
    }
    rt_exit_critical();
}

#else /* !RT_DEBUGING_CRITICAL */

/**
 * @brief Safely exit critical section (non-debug version)
 *
 * @param critical_level The expected critical level (unused in non-debug build)
 *
 * @details This is the non-debug version that simply calls rt_exit_critical().
 *          The critical_level parameter is ignored in this implementation.
 *
 * @note This function has both MP version and UP version.
 */
void rt_exit_critical_safe(rt_base_t critical_level)
{
    RT_UNUSED(critical_level);
    return rt_exit_critical();
}

#endif /* RT_DEBUGING_CRITICAL */
RTM_EXPORT(rt_exit_critical_safe);

#ifdef ARCH_USING_HW_THREAD_SELF
#define FREE_THREAD_SELF(lvl)

#else /* !ARCH_USING_HW_THREAD_SELF */
#define FREE_THREAD_SELF(lvl)        \
    do                               \
    {                                \
        rt_hw_local_irq_enable(lvl); \
    } while (0)

#endif /* ARCH_USING_HW_THREAD_SELF */

/**
 * @brief Enter a critical section and lock the scheduler
 *
 * @return The critical level after entering (nesting count)
 *         Returns -RT_EINVAL if scheduler is unavailable
 *
 * @details This function:
 *   - Disables interrupts to ensure atomic operation
 *   - Gets current thread context
 *   - Increments critical section nesting counter
 *   - Returns the new nesting level
 *   - Handles both hardware-assisted and software thread context cases
 *
 * @note Must be paired with rt_exit_critical()
 *       Can be nested, each call must have matching exit call
 *
 * @note This function has both MP version and UP version.
 */
rt_base_t rt_enter_critical(void)
{
    rt_base_t critical_level;
    struct rt_thread *current_thread;

#ifndef ARCH_USING_HW_THREAD_SELF
    rt_base_t level;
    struct rt_cpu *pcpu;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    pcpu = rt_cpu_self();
    current_thread = pcpu->current_thread;

#else /* !ARCH_USING_HW_THREAD_SELF */
    current_thread = rt_hw_thread_self();

#endif /* ARCH_USING_HW_THREAD_SELF */

    if (!current_thread)
    {
        FREE_THREAD_SELF(level);
        /* scheduler unavailable */
        return -RT_EINVAL;
    }

    /* critical for local cpu */
    RT_SCHED_CTX(current_thread).critical_lock_nest++;
    critical_level = RT_SCHED_CTX(current_thread).critical_lock_nest;

    FREE_THREAD_SELF(level);

    return critical_level;
}
RTM_EXPORT(rt_enter_critical);

/**
 * @brief Exit a critical section and unlock the scheduler
 *
 * @details This function performs the following operations:
 *   - Gets current thread context (using hardware-assisted or software method)
 *   - Decrements critical section nesting counter
 *   - If nesting level reaches 0:
 *     * Checks if rescheduling is needed
 *     * Clears critical switch flag
 *     * Performs rescheduling if needed
 *   - Verifies critical section nesting is valid (debug assertion)
 *   - Restores interrupt state
 *
 * @note Must be called in pair with rt_enter_critical()
 *       Handles both hardware-assisted and software thread context cases
 *       May trigger rescheduling if conditions met
 *
 * @note This function has both MP version and UP version.
 */
void rt_exit_critical(void)
{
    struct rt_thread *current_thread;
    rt_bool_t need_resched;

#ifndef ARCH_USING_HW_THREAD_SELF
    rt_base_t level;
    struct rt_cpu *pcpu;

    /* disable interrupt */
    level = rt_hw_local_irq_disable();

    pcpu = rt_cpu_self();
    current_thread = pcpu->current_thread;

#else /* !ARCH_USING_HW_THREAD_SELF */
    current_thread = rt_hw_thread_self();

#endif /* ARCH_USING_HW_THREAD_SELF */

    if (!current_thread)
    {
        FREE_THREAD_SELF(level);
        return;
    }

    /* the necessary memory barrier is done on irq_(dis|en)able */
    RT_SCHED_CTX(current_thread).critical_lock_nest--;

    /* may need a rescheduling */
    if (RT_SCHED_CTX(current_thread).critical_lock_nest == 0)
    {
        /* is there any scheduling request unfinished? */
        need_resched = IS_CRITICAL_SWITCH_PEND(pcpu, current_thread);
        CLR_CRITICAL_SWITCH_FLAG(pcpu, current_thread);

        FREE_THREAD_SELF(level);

        if (need_resched)
            rt_schedule();
    }
    else
    {
        /* each exit_critical is strictly corresponding to an enter_critical */
        RT_ASSERT(RT_SCHED_CTX(current_thread).critical_lock_nest > 0);

        FREE_THREAD_SELF(level);
    }
}
RTM_EXPORT(rt_exit_critical);

/**
 * @brief Get the scheduler lock level.
 *
 * @return The level of the scheduler lock. 0 means unlocked.
 *
 * @note This function has both MP version and UP version.
 */
rt_uint16_t rt_critical_level(void)
{
    rt_base_t level;
    rt_uint16_t critical_lvl;
    struct rt_thread *current_thread;

    level = rt_hw_local_irq_disable();

    current_thread = rt_cpu_self()->current_thread;

    if (current_thread)
    {
        /* the necessary memory barrier is done on irq_(dis|en)able */
        critical_lvl = RT_SCHED_CTX(current_thread).critical_lock_nest;
    }
    else
    {
        critical_lvl = 0;
    }

    rt_hw_local_irq_enable(level);
    return critical_lvl;
}
RTM_EXPORT(rt_critical_level);

/**
 * @brief Bind a thread to a specific CPU core
 *
 * @param thread The thread to be bound
 * @param cpu The target CPU core index (RT_CPUS_NR for no binding)
 *
 * @return rt_err_t
 *   - RT_EOK: Operation successful
 *
 * @details This function handles thread-CPU binding with the following logic:
 *   - If thread is READY:
 *     * Removes from current ready queue
 *     * Updates bind CPU information
 *     * Inserts to new ready queue
 *     * Triggers rescheduling if needed
 *   - If thread is RUNNING:
 *     * Updates bind CPU information
 *     * Sends IPI to target CPU if binding changed
 *     * Triggers rescheduling if needed
 *   - For other states, just updates bind CPU info
 *
 * @note Caller must ensure scheduler is not locked before calling
 *       This function will acquire scheduler lock internally
 *
 * @note This function has both MP version and UP version, but UP version does
 *       nothing and always returns -RT_EINVAL.
 */
rt_err_t rt_sched_thread_bind_cpu(struct rt_thread *thread, int cpu)
{
    rt_sched_lock_level_t slvl;
    rt_uint8_t thread_stat;

    RT_SCHED_DEBUG_IS_UNLOCKED;

    if (cpu >= RT_CPUS_NR)
    {
        cpu = RT_CPUS_NR;
    }

    rt_sched_lock(&slvl);

    thread_stat = rt_sched_thread_get_stat(thread);

    if (thread_stat == RT_THREAD_READY)
    {
        /* unbind */
        /* remove from old ready queue */
        rt_sched_remove_thread(thread);
        /* change thread bind cpu */
        RT_SCHED_CTX(thread).bind_cpu = cpu;
        /* add to new ready queue */
        rt_sched_insert_thread(thread);

        if (rt_thread_self() != RT_NULL)
        {
            rt_sched_unlock_n_resched(slvl);
        }
        else
        {
            rt_sched_unlock(slvl);
        }
    }
    else
    {
        RT_SCHED_CTX(thread).bind_cpu = cpu;
        if (thread_stat == RT_THREAD_RUNNING)
        {
            /* thread is running on a cpu */
            int current_cpu = rt_hw_cpu_id();

            if (cpu != RT_CPUS_NR)
            {
                if (RT_SCHED_CTX(thread).oncpu == current_cpu)
                {
                    /* current thread on current cpu */
                    if (cpu != current_cpu)
                    {
                        /* bind to other cpu */
                        rt_hw_ipi_send(RT_SCHEDULE_IPI, 1U << cpu);
                        /* self cpu need reschedule */
                        rt_sched_unlock_n_resched(slvl);
                    }
                    else
                    {
                        /* else do nothing */
                        rt_sched_unlock(slvl);
                    }
                }
                else
                {
                    /* no running on self cpu, but dest cpu can be itself */
                    rt_hw_ipi_send(RT_SCHEDULE_IPI, 1U << RT_SCHED_CTX(thread).oncpu);
                    rt_sched_unlock(slvl);
                }
            }
            else
            {
                /* else do nothing */
                rt_sched_unlock(slvl);
            }
        }
        else
        {
            rt_sched_unlock(slvl);
        }
    }

    return RT_EOK;
}

/**
 * @} group_thread_management
 *
 * @endcond
 */
