/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     Jesven       first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "lwp.h"

int lwp_signal_check(void)
{
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    uint32_t signal = 0;

    level = rt_hw_interrupt_disable();

    thread = rt_thread_self();

    if (thread->signal_in_process)
    {
        goto out;
    }

    lwp = thread->lwp;

    if (lwp->signal_in_process)
    {
        goto out;
    }

    signal = thread->signal;
    if (signal)
    {
        thread->signal_in_process = 1;
        goto out;
    }
    signal = lwp->signal;
    if (signal)
    {
        lwp->signal_in_process = 1;
    }
out:
    rt_hw_interrupt_enable(level);
    return signal;
}

uint32_t lwp_signal_backup(void *user_sp, void *user_pc, void* user_flag)
{
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    uint32_t signal, sig_bit;

    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
    if (thread->signal_in_process)
    {
        thread->user_ctx.sp = user_sp;
        thread->user_ctx.pc = user_pc;
        thread->user_ctx.flag = user_flag;
        signal = thread->signal;
        sig_bit = __builtin_ffs(signal);
        sig_bit--;
        thread->signal_mask |= (1 << sig_bit);
        thread->signal_mask_bak = (1 << sig_bit);
        thread->signal &= ~(1 << sig_bit);
    }
    else
    {
        lwp = thread->lwp;
        lwp->user_ctx.sp = user_sp;
        lwp->user_ctx.pc = user_pc;
        lwp->user_ctx.flag = user_flag;
        signal = lwp->signal;
        sig_bit = __builtin_ffs(signal);
        sig_bit--;
        lwp->signal_mask |= (1 << sig_bit);
        lwp->signal_mask_bak = (1 << sig_bit);
        lwp->signal &= ~(1 << sig_bit);
    }
    rt_hw_interrupt_enable(level);
    return sig_bit;
}

struct rt_user_context *lwp_signal_restore(void)
{
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    struct rt_user_context *ctx;

    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
    if (thread->signal_in_process)
    {
        ctx = &thread->user_ctx;
        thread->signal_in_process = 0;
        thread->signal_mask &= ~thread->signal_mask_bak;
        thread->signal_mask_bak = 0;
    }
    else
    {
        lwp = thread->lwp;
        ctx = &lwp->user_ctx;
        RT_ASSERT(lwp->signal_in_process != 0);
        lwp->signal_in_process = 0;
        lwp->signal_mask &= ~lwp->signal_mask_bak;
        lwp->signal_mask_bak = 0;
    }
    rt_hw_interrupt_enable(level);
    return ctx;
}

void sys_exit(int value);
lwp_sighandler_t lwp_sighandler_get(int sig)
{
    lwp_sighandler_t func;
    struct rt_lwp *lwp;
    rt_thread_t thread;
    rt_thread_t main_thread;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
    if (thread->signal_in_process)
    {
        func = rt_thread_self()->signal_handler[sig];
        if (!func)
        {
            lwp = (struct rt_lwp*)thread->lwp;
            main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
            if (thread == main_thread)
            {
                rt_thread_t sub_thread;
                rt_list_t *s_list = lwp->t_grp.next;
                rt_list_t *m_list = lwp->t_grp.prev;

                while (s_list != m_list)
                {
                    sub_thread = rt_list_entry(s_list, struct rt_thread, sibling);
                    /* kill all sub threads */
                    s_list = sub_thread->sibling.next;
                    lwp_thread_kill(sub_thread, 0);
                }
            }
            sys_exit(0);
        }
    }
    else
    {
        lwp = (struct rt_lwp*)thread->lwp;
        func = lwp->signal_handler[sig];
        if (!func)
        {
            main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
            lwp_thread_kill(main_thread, 0);
        }
    }
    rt_hw_interrupt_enable(level);
    return func;
}

void lwp_sighandler_set(int sig, lwp_sighandler_t func)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ((struct rt_lwp*)rt_thread_self()->lwp)->signal_handler[sig] = func;
    rt_hw_interrupt_enable(level);
}

void lwp_thread_sighandler_set(int sig, lwp_sighandler_t func)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (sig) /* sig 0 is default behavior */
    {
        rt_thread_self()->signal_handler[sig] = func;
    }
    rt_hw_interrupt_enable(level);
}

int lwp_sigprocmask(const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    int ret = -1;
    rt_base_t level;
    struct rt_lwp *lwp;
    struct rt_thread *thread;

    level = rt_hw_interrupt_disable();

    thread = rt_thread_self();
    lwp = thread->lwp;
    if (!lwp)
    {
        goto out;
    }
    *oset = lwp->signal_mask;
    lwp->signal_mask = *sigset;
    lwp->signal_mask_bak &= ~*sigset;
    ret = 0;

out:
    rt_hw_interrupt_enable(level);
    return ret;
}

int lwp_thread_sigprocmask(const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    rt_base_t level;
    struct rt_thread *thread;
    uint32_t value = *sigset;

    value &= ~(1 << 0); /* thread sig 0 must not be masked */
    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
    *oset = thread->signal_mask;
    thread->signal_mask = value;
    thread->signal_mask_bak &= ~value;
    rt_hw_interrupt_enable(level);
    return 0;
}

int lwp_kill(pid_t pid, int sig)
{
    rt_base_t level;
    struct rt_lwp *lwp;
    int ret = -RT_EINVAL;
    uint32_t signal;
    rt_thread_t thread;

    level = rt_hw_interrupt_disable();
    lwp = lwp_from_pid(pid);
    if (!lwp)
    {
        goto out;
    }

    /* check main thread */
    thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if ((lwp->signal_mask & (1 << sig)) != 0)
    {
        goto out;
    }

    signal = (1 << sig);
    signal &= ~lwp->signal_mask;
    lwp->signal |= signal;
    if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        rt_thread_wakeup(thread);

        /* do schedule */
        rt_schedule();
    }
    ret = 0;
out:
    rt_hw_interrupt_enable(level);
    return ret;
}

int lwp_thread_kill(rt_thread_t thread, int sig)
{
    rt_base_t level;
    int ret = -RT_EINVAL;
    uint32_t signal;

    if (!thread) return ret;

    level = rt_hw_interrupt_disable();
    if ((thread->signal_mask & (1 << sig)) != 0)
    {
        goto out;
    }

    signal = (1 << sig);
    signal &= ~thread->signal_mask;
    thread->signal |= signal;
    if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        rt_thread_wakeup(thread);

        /* do schedule */
        rt_schedule();
    }
    ret = 0;

out:
    rt_hw_interrupt_enable(level);
    return ret;
}
