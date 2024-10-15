/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/5      Bernard      the first version
 * 2018/09/17     Jesven       fix: in _signal_deliver RT_THREAD_STAT_MASK to RT_THREAD_STAT_SIGNAL_MASK
 * 2018/11/22     Jesven       in smp version rt_hw_context_switch_to add a param
 */

#include <stdint.h>
#include <string.h>

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SIGNALS

#ifndef RT_SIG_INFO_MAX
    #ifdef ARCH_CPU_64BIT
        #define RT_SIG_INFO_MAX 64
    #else
        #define RT_SIG_INFO_MAX 32
    #endif /* ARCH_CPU_64BIT */
#endif /* RT_SIG_INFO_MAX */

#define DBG_TAG     "SIGN"
#define DBG_LVL     DBG_WARNING
#include <rtdbg.h>

#define sig_mask(sig_no)    (1u << sig_no)
#define sig_valid(sig_no)   (sig_no >= 0 && sig_no < RT_SIG_MAX)

static struct rt_spinlock _thread_signal_lock = RT_SPINLOCK_INIT;

struct siginfo_node
{
    siginfo_t si;
    struct rt_slist_node list;
};

static struct rt_mempool *_siginfo_pool;
static void _signal_deliver(rt_thread_t tid);
void rt_thread_handle_sig(rt_bool_t clean_state);

static void _signal_default_handler(int signo)
{
    RT_UNUSED(signo);
    LOG_I("handled signo[%d] with default action.", signo);
    return ;
}

static void _signal_entry(void *parameter)
{
    RT_UNUSED(parameter);

    rt_thread_t tid = rt_thread_self();

    /* handle signal */
    rt_thread_handle_sig(RT_FALSE);

#ifdef RT_USING_SMP
#else
    /* return to thread */
    tid->sp = tid->sig_ret;
    tid->sig_ret = RT_NULL;
#endif /* RT_USING_SMP */

    LOG_D("switch back to: 0x%08x\n", tid->sp);
    RT_SCHED_CTX(tid).stat &= ~RT_THREAD_STAT_SIGNAL;

#ifdef RT_USING_SMP
    rt_hw_context_switch_to((rt_uintptr_t)&parameter, tid);
#else
    rt_hw_context_switch_to((rt_uintptr_t)&(tid->sp));
#endif /* RT_USING_SMP */
}

/*
 * To deliver a signal to thread, there are cases:
 * 1. When thread is suspended, function resumes thread and
 * set signal stat;
 * 2. When thread is ready:
 *   - If function delivers a signal to self thread, just handle
 *    it.
 *   - If function delivers a signal to another ready thread, OS
 *    should build a slice context to handle it.
 */
static void _signal_deliver(rt_thread_t tid)
{
    rt_base_t level;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    /* thread is not interested in pended signals */
    if (!(tid->sig_pending & tid->sig_mask))
    {
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
        return;
    }

    if ((RT_SCHED_CTX(tid).stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        /* resume thread to handle signal */
#ifdef RT_USING_SMART
        rt_thread_wakeup(tid);
#else
        rt_thread_resume(tid);
#endif
        /* add signal state */
        RT_SCHED_CTX(tid).stat |= (RT_THREAD_STAT_SIGNAL | RT_THREAD_STAT_SIGNAL_PENDING);

        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

        /* re-schedule */
        rt_schedule();
    }
    else
    {
        if (tid == rt_thread_self())
        {
            /* add signal state */
            RT_SCHED_CTX(tid).stat |= RT_THREAD_STAT_SIGNAL;

            rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

            /* do signal action in self thread context */
            if (rt_interrupt_get_nest() == 0)
            {
                rt_thread_handle_sig(RT_TRUE);
            }
        }
        else if (!((RT_SCHED_CTX(tid).stat & RT_THREAD_STAT_SIGNAL_MASK) & RT_THREAD_STAT_SIGNAL))
        {
            /* add signal state */
            RT_SCHED_CTX(tid).stat |= (RT_THREAD_STAT_SIGNAL | RT_THREAD_STAT_SIGNAL_PENDING);

#ifdef RT_USING_SMP
            {
                int cpu_id;

                cpu_id = RT_SCHED_CTX(tid).oncpu;
                if ((cpu_id != RT_CPU_DETACHED) && (cpu_id != rt_cpu_get_id()))
                {
                    rt_uint32_t cpu_mask;

                    cpu_mask = RT_CPU_MASK ^ (1 << cpu_id);
                    rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
                }
            }
#else
            /* point to the signal handle entry */
            RT_SCHED_CTX(tid).stat &= ~RT_THREAD_STAT_SIGNAL_PENDING;
            tid->sig_ret = tid->sp;
            tid->sp = rt_hw_stack_init((void *)_signal_entry, RT_NULL,
                                       (void *)((char *)tid->sig_ret - 32), RT_NULL);
#endif /* RT_USING_SMP */

            rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
            LOG_D("signal stack pointer @ 0x%08x", tid->sp);

            /* re-schedule */
            rt_schedule();
        }
        else
        {
            rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
        }
    }
}

#ifdef RT_USING_SMP
void *rt_signal_check(void* context)
{
    rt_sched_lock_level_t level;
    int cpu_id;
    struct rt_cpu* pcpu;
    struct rt_thread *current_thread;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    cpu_id = rt_cpu_get_id();
    pcpu   = rt_cpu_index(cpu_id);
    current_thread = pcpu->current_thread;

    if (pcpu->irq_nest)
    {
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
        return context;
    }

    if (current_thread->cpus_lock_nest == 1)
    {
        if (RT_SCHED_CTX(current_thread).stat & RT_THREAD_STAT_SIGNAL_PENDING)
        {
            void *sig_context;

            RT_SCHED_CTX(current_thread).stat &= ~RT_THREAD_STAT_SIGNAL_PENDING;

            rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
            sig_context = rt_hw_stack_init((void *)_signal_entry, context,
                    (void*)((char*)context - 32), RT_NULL);
            return sig_context;
        }
    }
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
    return context;
}
#endif /* RT_USING_SMP */

/**
 * @brief    This function will install a processing function to a specific
 *           signal and return the old processing function of this signal.
 *
 * @note     This function needs to be used in conjunction with the
 *           rt_signal_unmask() function to make the signal effective.
 *
 * @see      rt_signal_unmask()
 *
 * @param    signo is a specific signal value (range: 0 ~ RT_SIG_MAX).
 *
 * @param    handler is sets the processing of signal value.
 *
 * @return   Return the old processing function of this signal. ONLY When the
 *           return value is SIG_ERR, the operation is failed.
 */
rt_sighandler_t rt_signal_install(int signo, rt_sighandler_t handler)
{
    rt_base_t level;
    rt_sighandler_t old = RT_NULL;
    rt_thread_t tid = rt_thread_self();

    if (!sig_valid(signo)) return SIG_ERR;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);
    if (tid->sig_vectors == RT_NULL)
    {
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

        rt_thread_alloc_sig(tid);

        level = rt_spin_lock_irqsave(&_thread_signal_lock);
    }

    if (tid->sig_vectors)
    {
        old = tid->sig_vectors[signo];

        if (handler == SIG_IGN) tid->sig_vectors[signo] = RT_NULL;
        else if (handler == SIG_DFL) tid->sig_vectors[signo] = _signal_default_handler;
        else tid->sig_vectors[signo] = handler;
    }
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

    return old;
}

/**
 * @brief    This function will block the specified signal.
 *
 * @note     This function will block the specified signal, even if the
 *           rt_thread_kill() function is called to send this signal to
 *           the current thread, it will no longer take effect.
 *
 * @see      rt_thread_kill()
 *
 * @param    signo is a specific signal value (range: 0 ~ RT_SIG_MAX).
 */
void rt_signal_mask(int signo)
{
    rt_base_t level;
    rt_thread_t tid = rt_thread_self();

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    tid->sig_mask &= ~sig_mask(signo);

    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
}

/**
 * @brief    This function will unblock the specified signal.
 *
 * @note     This function will unblock the specified signal. After calling
 *           the rt_thread_kill() function to send this signal to the current
 *           thread, it will take effect.
 *
 * @see      rt_thread_kill()
 *
 * @param    signo is a specific signal value (range: 0 ~ RT_SIG_MAX).
 */
void rt_signal_unmask(int signo)
{
    rt_base_t level;
    rt_thread_t tid = rt_thread_self();

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    tid->sig_mask |= sig_mask(signo);

    /* let thread handle pended signals */
    if (tid->sig_mask & tid->sig_pending)
    {
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
        _signal_deliver(tid);
    }
    else
    {
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
    }
}

/**
 * @brief    This function will wait for the arrival of the set signal. If it does not wait for this signal, the thread will be
 *           suspended until it waits for this signal or the waiting time exceeds the specified timeout: timeout.
 *
 * @param    set is the set of signal values to be waited for. Use the function
 *           sigaddset() to add the signal.
 *
 * @param    si is a pointer to the received signal info. If you don't care about this value, you can use RT_NULL to set.
 *
 * @param    timeout is a timeout period (unit: an OS tick).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the signal wait failed.
 */
int rt_signal_wait(const rt_sigset_t *set, rt_siginfo_t *si, rt_int32_t timeout)
{
    int ret = RT_EOK;
    rt_base_t level;
    rt_thread_t tid = rt_thread_self();
    struct siginfo_node *si_node = RT_NULL, *si_prev = RT_NULL;

    /* current context checking */
    RT_DEBUG_IN_THREAD_CONTEXT;

    /* parameters check */
    if (set == NULL || *set == 0 || si == NULL )
    {
        ret = -RT_EINVAL;
        goto __done_return;
    }

    /* clear siginfo to avoid unknown value */
    memset(si, 0x0, sizeof(rt_siginfo_t));

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    /* already pending */
    if (tid->sig_pending & *set) goto __done;

    if (timeout == 0)
    {
        ret = -RT_ETIMEOUT;
        goto __done_int;
    }

    /* suspend self thread */
    rt_thread_suspend_with_flag(tid, RT_UNINTERRUPTIBLE);
    /* set thread stat as waiting for signal */
    RT_SCHED_CTX(tid).stat |= RT_THREAD_STAT_SIGNAL_WAIT;

    /* start timeout timer */
    if (timeout != RT_WAITING_FOREVER)
    {
        /* reset the timeout of thread timer and start it */
        rt_timer_control(&(tid->thread_timer),
                         RT_TIMER_CTRL_SET_TIME,
                         &timeout);
        rt_timer_start(&(tid->thread_timer));
    }
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

    /* do thread scheduling */
    rt_schedule();

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    /* remove signal waiting flag */
    RT_SCHED_CTX(tid).stat &= ~RT_THREAD_STAT_SIGNAL_WAIT;

    /* check errno of thread */
    if (tid->error == -RT_ETIMEOUT)
    {
        tid->error = RT_EOK;
        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

        /* timer timeout */
        ret = -RT_ETIMEOUT;
        goto __done_return;
    }

__done:
    /* to get the first matched pending signals */
    si_node = (struct siginfo_node *)tid->si_list;
    while (si_node)
    {
        int signo;

        signo = si_node->si.si_signo;
        if (sig_mask(signo) & *set)
        {
            *si  = si_node->si;

            LOG_D("sigwait: %d sig raised!", signo);
            if (si_prev) si_prev->list.next = si_node->list.next;
            else
            {
                struct siginfo_node *node_next;

                if (si_node->list.next)
                {
                    node_next = (void *)rt_slist_entry(si_node->list.next, struct siginfo_node, list);
                    tid->si_list = node_next;
                }
                else
                {
                    tid->si_list = RT_NULL;
                }
            }

            /* clear pending */
            tid->sig_pending &= ~sig_mask(signo);
            rt_mp_free(si_node);
            break;
        }

        si_prev = si_node;
        if (si_node->list.next)
        {
            si_node = (void *)rt_slist_entry(si_node->list.next, struct siginfo_node, list);
        }
        else
        {
            si_node = RT_NULL;
        }
     }

__done_int:
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

__done_return:
    return ret;
}

void rt_thread_handle_sig(rt_bool_t clean_state)
{
    rt_base_t level;

    rt_thread_t tid = rt_thread_self();
    struct siginfo_node *si_node;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);
    if (tid->sig_pending & tid->sig_mask)
    {
        /* if thread is not waiting for signal */
        if (!(RT_SCHED_CTX(tid).stat & RT_THREAD_STAT_SIGNAL_WAIT))
        {
            while (tid->sig_pending & tid->sig_mask)
            {
                int signo, error;
                rt_sighandler_t handler;

                si_node = (struct siginfo_node *)tid->si_list;
                if (!si_node) break;

                /* remove this sig info node from list */
                if (si_node->list.next == RT_NULL)
                    tid->si_list = RT_NULL;
                else
                    tid->si_list = (void *)rt_slist_entry(si_node->list.next, struct siginfo_node, list);

                signo   = si_node->si.si_signo;
                handler = tid->sig_vectors[signo];
                tid->sig_pending &= ~sig_mask(signo);
                rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

                LOG_D("handle signal: %d, handler 0x%08x", signo, handler);
                if (handler) handler(signo);

                level = rt_spin_lock_irqsave(&_thread_signal_lock);
                error = -RT_EINTR;

                rt_mp_free(si_node); /* release this siginfo node */
                /* set errno in thread tcb */
                tid->error = error;
            }

            /* whether clean signal status */
            if (clean_state == RT_TRUE)
            {
                RT_SCHED_CTX(tid).stat &= ~RT_THREAD_STAT_SIGNAL;
            }
            else
            {
                return;
            }
        }
    }
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
}

void rt_thread_alloc_sig(rt_thread_t tid)
{
    int index;
    rt_bool_t need_free = RT_FALSE;
    rt_base_t level;
    rt_sighandler_t *vectors;

    vectors = (rt_sighandler_t *)RT_KERNEL_MALLOC(sizeof(rt_sighandler_t) * RT_SIG_MAX);
    RT_ASSERT(vectors != RT_NULL);

    for (index = 0; index < RT_SIG_MAX; index ++)
    {
        vectors[index] = _signal_default_handler;
    }

    level = rt_spin_lock_irqsave(&_thread_signal_lock);

    if (tid->sig_vectors == RT_NULL)
    {
        tid->sig_vectors = vectors;
    }
    else
    {
        need_free = RT_TRUE;
    }

    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

    if (need_free)
    {
        rt_free(vectors);
    }
}

void rt_thread_free_sig(rt_thread_t tid)
{
    rt_base_t level;
    struct siginfo_node *si_node;
    rt_sighandler_t *sig_vectors;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);
    si_node = (struct siginfo_node *)tid->si_list;
    tid->si_list = RT_NULL;

    sig_vectors = tid->sig_vectors;
    tid->sig_vectors = RT_NULL;
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

    if (si_node)
    {
        struct rt_slist_node *node;
        struct rt_slist_node *node_to_free;

        LOG_D("free signal info list");
        node = &(si_node->list);
        do
        {
            node_to_free = node;
            node = node->next;
            si_node = rt_slist_entry(node_to_free, struct siginfo_node, list);
            rt_mp_free(si_node);
        } while (node);
    }

    if (sig_vectors)
    {
        RT_KERNEL_FREE(sig_vectors);
    }
}

/**
 * @brief    This function can be used to send any signal to any thread.
 *
 * @param    tid is a pointer to the thread that receives the signal.
 *
 * @param    sig is a specific signal value (range: 0 ~ RT_SIG_MAX).
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it means that the signal send failed.
 */
int rt_thread_kill(rt_thread_t tid, int sig)
{
    siginfo_t si;
    rt_base_t level;
    struct siginfo_node *si_node;

    RT_ASSERT(tid != RT_NULL);
    if (!sig_valid(sig)) return -RT_EINVAL;

    LOG_I("send signal: %d", sig);
    si.si_signo = sig;
    si.si_code  = SI_USER;
    si.si_value.sival_ptr = RT_NULL;

    level = rt_spin_lock_irqsave(&_thread_signal_lock);
    if (tid->sig_pending & sig_mask(sig))
    {
        /* whether already emits this signal? */
        struct rt_slist_node *node;
        struct siginfo_node  *entry;

        si_node = (struct siginfo_node *)tid->si_list;
        if (si_node)
            node = (struct rt_slist_node *)&si_node->list;
        else
            node = RT_NULL;

        /* update sig info */
        for (; (node) != RT_NULL; node = node->next)
        {
            entry = rt_slist_entry(node, struct siginfo_node, list);
            if (entry->si.si_signo == sig)
            {
                memcpy(&(entry->si), &si, sizeof(siginfo_t));
                rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
                return 0;
            }
        }
    }
    rt_spin_unlock_irqrestore(&_thread_signal_lock, level);

    si_node = (struct siginfo_node *) rt_mp_alloc(_siginfo_pool, 0);
    if (si_node)
    {
        rt_slist_init(&(si_node->list));
        memcpy(&(si_node->si), &si, sizeof(siginfo_t));

        level = rt_spin_lock_irqsave(&_thread_signal_lock);

        if (tid->si_list)
        {
            struct siginfo_node *si_list;

            si_list = (struct siginfo_node *)tid->si_list;
            rt_slist_append(&(si_list->list), &(si_node->list));
        }
        else
        {
            tid->si_list = si_node;
        }

        /* a new signal */
        tid->sig_pending |= sig_mask(sig);

        rt_spin_unlock_irqrestore(&_thread_signal_lock, level);
    }
    else
    {
        LOG_E("The allocation of signal info node failed.");
        return -RT_EEMPTY;
    }

    /* deliver signal to this thread */
    _signal_deliver(tid);

    return RT_EOK;
}

int rt_system_signal_init(void)
{
    _siginfo_pool = rt_mp_create("signal", RT_SIG_INFO_MAX, sizeof(struct siginfo_node));
    if (_siginfo_pool == RT_NULL)
    {
        LOG_E("create memory pool for signal info failed.");
        RT_ASSERT(0);
    }

    return 0;
}

#endif /* RT_USING_SIGNALS */
