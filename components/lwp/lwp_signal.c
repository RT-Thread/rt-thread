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
#include "lwp_arch.h"
#include "sys/signal.h"

rt_inline void lwp_sigaddset(lwp_sigset_t *set, int _sig)
{
    unsigned long sig = _sig - 1;

    if (_LWP_NSIG_WORDS == 1)
    {
        set->sig[0] |= 1UL << sig;
    }
    else
    {
        set->sig[sig / _LWP_NSIG_BPW] |= 1UL << (sig % _LWP_NSIG_BPW);
    }
}

rt_inline void lwp_sigdelset(lwp_sigset_t *set, int _sig)
{
    unsigned long sig = _sig - 1;

    if (_LWP_NSIG_WORDS == 1)
    {
        set->sig[0] &= ~(1UL << sig);
    }
    else
    {
        set->sig[sig / _LWP_NSIG_BPW] &= ~(1UL << (sig % _LWP_NSIG_BPW));
    }
}

rt_inline int lwp_sigisemptyset(lwp_sigset_t *set)
{
    switch (_LWP_NSIG_WORDS)
    {
        case 4:
            return (set->sig[3] | set->sig[2] |
                    set->sig[1] | set->sig[0]) == 0;
        case 2:
            return (set->sig[1] | set->sig[0]) == 0;
        case 1:
            return set->sig[0] == 0;
        default:
            return 1;
    }
}

rt_inline int lwp_sigismember(lwp_sigset_t *set, int _sig)
{
    unsigned long sig = _sig - 1;

    if (_LWP_NSIG_WORDS == 1)
    {
        return 1 & (set->sig[0] >> sig);
    }
    else
    {
        return 1 & (set->sig[sig / _LWP_NSIG_BPW] >> (sig % _LWP_NSIG_BPW));
    }
}

rt_inline int next_signal(lwp_sigset_t *pending, lwp_sigset_t *mask)
{
    unsigned long i, *s, *m, x;
    int sig = 0;

    s = pending->sig;
    m = mask->sig;

    x = *s & ~*m;
    if (x)
    {
        sig = rt_hw_ffz(~x) + 1;
        return sig;
    }

    switch (_LWP_NSIG_WORDS)
    {
        default:
            for (i = 1; i < _LWP_NSIG_WORDS; ++i)
            {
                x = *++s &~ *++m;
                if (!x)
                    continue;
                sig = rt_hw_ffz(~x) + i*_LWP_NSIG_BPW + 1;
                break;
            }
            break;

        case 2:
            x = s[1] &~ m[1];
            if (!x)
                break;
            sig = rt_hw_ffz(~x) + _LWP_NSIG_BPW + 1;
            break;

        case 1:
            /* Nothing to do */
            break;
    }

    return sig;
}

int lwp_suspend_sigcheck(rt_thread_t thread, int suspend_flag)
{
    struct rt_lwp *lwp = (struct rt_lwp*)thread->lwp;
    int ret = 0;

    switch (suspend_flag)
    {
        case RT_INTERRUPTIBLE:
            if (!lwp_sigisemptyset(&thread->signal))
            {
                break;
            }
            if (thread->lwp && !lwp_sigisemptyset(&lwp->signal))
            {
                break;
            }
            ret = 1;
            break;
        case RT_KILLABLE:
            if (lwp_sigismember(&thread->signal, SIGKILL))
            {
                break;
            }
            if (thread->lwp && lwp_sigismember(&lwp->signal, SIGKILL))
            {
                break;
            }
            ret = 1;
            break;
        case RT_UNINTERRUPTIBLE:
            ret = 1;
            break;
        default:
            RT_ASSERT(0);
            break;
    }
    return ret;
}

int lwp_signal_check(void)
{
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    uint32_t have_signal = 0;

    level = rt_hw_interrupt_disable();

    thread = rt_thread_self();

    if (thread->signal_in_process)
    {
        goto out;
    }

    lwp = (struct rt_lwp*)thread->lwp;

    if (lwp->signal_in_process)
    {
        goto out;
    }

    have_signal = !lwp_sigisemptyset(&thread->signal);
    if (have_signal)
    {
        thread->signal_in_process = 1;
        goto out;
    }
    have_signal = !lwp_sigisemptyset(&lwp->signal);
    if (have_signal)
    {
        lwp->signal_in_process = 1;
    }
out:
    rt_hw_interrupt_enable(level);
    return have_signal;
}

int lwp_signal_backup(void *user_sp, void *user_pc, void* user_flag)
{
    rt_base_t level;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    int signal;

    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
    if (thread->signal_in_process)
    {
        thread->user_ctx.sp = user_sp;
        thread->user_ctx.pc = user_pc;
        thread->user_ctx.flag = user_flag;

        signal = next_signal(&thread->signal, &thread->signal_mask);
        RT_ASSERT(signal != 0);
        lwp_sigaddset(&thread->signal_mask, signal);
        thread->signal_mask_bak = signal;
        lwp_sigdelset(&thread->signal, signal);
    }
    else
    {
        lwp = (struct rt_lwp*)thread->lwp;
        lwp->user_ctx.sp = user_sp;
        lwp->user_ctx.pc = user_pc;
        lwp->user_ctx.flag = user_flag;

        signal = next_signal(&lwp->signal, &lwp->signal_mask);
        RT_ASSERT(signal != 0);
        lwp_sigaddset(&lwp->signal_mask, signal);
        lwp->signal_mask_bak = signal;
        lwp_sigdelset(&lwp->signal, signal);
    }
    rt_hw_interrupt_enable(level);
    return signal;
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

        lwp_sigdelset(&thread->signal_mask, thread->signal_mask_bak);
        thread->signal_mask_bak = 0;
    }
    else
    {
        lwp = (struct rt_lwp*)thread->lwp;
        ctx = &lwp->user_ctx;
        RT_ASSERT(lwp->signal_in_process != 0);
        lwp->signal_in_process = 0;

        lwp_sigdelset(&lwp->signal_mask, lwp->signal_mask_bak);
        lwp->signal_mask_bak = 0;
    }
    rt_hw_interrupt_enable(level);
    return ctx;
}

rt_inline int _lwp_check_ignore(int sig)
{
    if (sig == SIGCHLD || sig == SIGCONT)
    {
        return 1;
    }
    return 0;
}

void sys_exit(int value);
lwp_sighandler_t lwp_sighandler_get(int sig)
{
    lwp_sighandler_t func = RT_NULL;
    struct rt_lwp *lwp;
    rt_thread_t thread;
    rt_base_t level;

    if (sig == 0 || sig > _LWP_NSIG)
    {
        return func;
    }
    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();
#ifndef ARCH_MM_MMU
    if (thread->signal_in_process)
    {
        func = thread->signal_handler[sig - 1];
        goto out;
    }
#endif
    lwp = (struct rt_lwp*)thread->lwp;

    func = lwp->signal_handler[sig - 1];
    if (!func)
    {
        if (_lwp_check_ignore(sig))
        {
            goto out;
        }
        if (lwp->signal_in_process)
        {
            lwp_terminate(lwp);
        }
        sys_exit(0);
    }
out:
    rt_hw_interrupt_enable(level);

    if (func == (lwp_sighandler_t)SIG_IGN)
    {
        func = RT_NULL;
    }
    return func;
}

void lwp_sighandler_set(int sig, lwp_sighandler_t func)
{
    rt_base_t level;

    if (sig == 0 || sig > _LWP_NSIG)
        return;
    if (sig == SIGKILL || sig == SIGSTOP)
        return;
    level = rt_hw_interrupt_disable();
    ((struct rt_lwp*)rt_thread_self()->lwp)->signal_handler[sig - 1] = func;
    rt_hw_interrupt_enable(level);
}

#ifndef ARCH_MM_MMU
void lwp_thread_sighandler_set(int sig, lwp_sighandler_t func)
{
    rt_base_t level;

    if (sig == 0 || sig > _LWP_NSIG)
        return;
    level = rt_hw_interrupt_disable();
    rt_thread_self()->signal_handler[sig - 1] = func;
    rt_hw_interrupt_enable(level);
}
#endif

int lwp_sigaction(int sig, const struct lwp_sigaction *act,
             struct lwp_sigaction *oact, size_t sigsetsize)
{
    rt_base_t level;
    struct rt_lwp *lwp;
    int ret = -RT_EINVAL;
    lwp_sigset_t newset;

    level = rt_hw_interrupt_disable();
    lwp = (struct rt_lwp*)rt_thread_self()->lwp;
    if (!lwp)
    {
        goto out;
    }
    if (sigsetsize != sizeof(lwp_sigset_t))
    {
        goto out;
    }
    if (!act && !oact)
    {
        goto out;
    }
    if (oact)
    {
        oact->sa_flags = lwp->sa_flags;
        oact->sa_mask = lwp->signal_mask;
        oact->sa_restorer = RT_NULL;
        oact->__sa_handler._sa_handler = lwp->signal_handler[sig - 1];
    }
    if (act)
    {
        lwp->sa_flags = act->sa_flags;
        newset = act->sa_mask;
        lwp_sigdelset(&newset, SIGKILL);
        lwp_sigdelset(&newset, SIGSTOP);
        lwp->signal_mask = newset;
        lwp_sighandler_set(sig, act->__sa_handler._sa_handler);
    }
    ret = 0;
out:
    rt_hw_interrupt_enable(level);
    return ret;
}

rt_inline void sigorsets(lwp_sigset_t *dset, const lwp_sigset_t *set0, const lwp_sigset_t *set1)
{
    switch (_LWP_NSIG_WORDS)
    {
        case 4:
            dset->sig[3] = set0->sig[3] | set1->sig[3];
            dset->sig[2] = set0->sig[2] | set1->sig[2];
        case 2:
            dset->sig[1] = set0->sig[1] | set1->sig[1];
        case 1:
            dset->sig[0] = set0->sig[0] | set1->sig[0];
        default:
            return;
    }
}

rt_inline void sigandsets(lwp_sigset_t *dset, const lwp_sigset_t *set0, const lwp_sigset_t *set1)
{
    switch (_LWP_NSIG_WORDS)
    {
        case 4:
            dset->sig[3] = set0->sig[3] & set1->sig[3];
            dset->sig[2] = set0->sig[2] & set1->sig[2];
        case 2:
            dset->sig[1] = set0->sig[1] & set1->sig[1];
        case 1:
            dset->sig[0] = set0->sig[0] & set1->sig[0];
        default:
            return;
    }
}

int lwp_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    int ret = -1;
    rt_base_t level;
    struct rt_lwp *lwp;
    struct rt_thread *thread;
    lwp_sigset_t newset;

    level = rt_hw_interrupt_disable();

    thread = rt_thread_self();
    lwp = (struct rt_lwp*)thread->lwp;
    if (!lwp)
    {
        goto out;
    }
    if (oset)
    {
        rt_memcpy(oset, &lwp->signal_mask, sizeof(lwp_sigset_t));
    }

    if (sigset)
    {
        switch (how)
        {
            case SIG_BLOCK:
                sigorsets(&newset, &lwp->signal_mask, sigset);
                break;
            case SIG_UNBLOCK:
                sigandsets(&newset, &lwp->signal_mask, sigset);
                break;
            case SIG_SETMASK:
                newset = *sigset;
                break;
            default:
                ret = -RT_EINVAL;
                goto out;
        }

        lwp_sigdelset(&newset, SIGKILL);
        lwp_sigdelset(&newset, SIGSTOP);

        lwp->signal_mask = newset;
    }
    ret = 0;
out:
    rt_hw_interrupt_enable(level);
    return ret;
}

int lwp_thread_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    rt_base_t level;
    struct rt_thread *thread;
    lwp_sigset_t newset;

    level = rt_hw_interrupt_disable();
    thread = rt_thread_self();

    if (oset)
    {
        rt_memcpy(oset, &thread->signal_mask, sizeof(lwp_sigset_t));
    }

    if (sigset)
    {
        switch (how)
        {
            case SIG_BLOCK:
                sigorsets(&newset, &thread->signal_mask, sigset);
                break;
            case SIG_UNBLOCK:
                sigandsets(&newset, &thread->signal_mask, sigset);
                break;
            case SIG_SETMASK:
                newset = *sigset;
                break;
            default:
                goto out;
        }

        lwp_sigdelset(&newset, SIGKILL);
        lwp_sigdelset(&newset, SIGSTOP);

        thread->signal_mask = newset;
    }
out:
    rt_hw_interrupt_enable(level);
    return 0;
}

static void _do_signal_wakeup(rt_thread_t thread, int sig)
{
    if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
    {
        int need_schedule = 1;

        if ((thread->stat & RT_SIGNAL_COMMON_WAKEUP_MASK) != RT_SIGNAL_COMMON_WAKEUP_MASK)
        {
            rt_thread_wakeup(thread);
        }
        else if ((sig == SIGKILL) && ((thread->stat & RT_SIGNAL_KILL_WAKEUP_MASK) != RT_SIGNAL_KILL_WAKEUP_MASK))
        {
            rt_thread_wakeup(thread);
        }
        else
        {
            need_schedule = 0;
        }

        /* do schedule */
        if (need_schedule)
        {
            rt_schedule();
        }
    }
}

int lwp_kill(pid_t pid, int sig)
{
    rt_base_t level;
    struct rt_lwp *lwp;
    int ret = -1;
    rt_thread_t thread;

    if (sig < 0 || sig >= _LWP_NSIG)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    level = rt_hw_interrupt_disable();
    lwp = lwp_from_pid(pid);
    if (!lwp || lwp->finish)
    {
        rt_set_errno(ESRCH);
        goto out;
    }
    if (sig)
    {
        /* check main thread */
        thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
        if (!lwp_sigismember(&lwp->signal_mask, sig)) /* if signal masked */
        {
            lwp_sigaddset(&lwp->signal, sig);
            _do_signal_wakeup(thread, sig);
        }
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

    if (!thread)
    {
        rt_set_errno(ESRCH);
        return ret;
    }
    if (sig < 0 || sig >= _LWP_NSIG)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    level = rt_hw_interrupt_disable();
    if (!thread->lwp)
    {
        rt_set_errno(EPERM);
        goto out;
    }
    if (!lwp_sigismember(&thread->signal_mask, sig)) /* if signal masked */
    {
        lwp_sigaddset(&thread->signal, sig);
        _do_signal_wakeup(thread, sig);
    }
    ret = 0;
out:
    rt_hw_interrupt_enable(level);
    return ret;
}
