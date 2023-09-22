/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     Jesven       first version
 * 2023-02-23     Shell        Support sigtimedwait
 * 2023-07-04     Shell        Support siginfo, sigqueue
 *                             remove lwp_signal_backup/restore() to reduce architecture codes
 *                             update the generation, pending and delivery routines
 */

#define DBG_TAG    "LWP_SIGNAL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include "lwp.h"
#include "lwp_arch.h"
#include "lwp_signal.h"
#include "sys/signal.h"
#include "syscall_generic.h"

static lwp_siginfo_t siginfo_create(int signo, int code, int value)
{
    lwp_siginfo_t siginfo;
    struct rt_lwp *self_lwp;
    rt_thread_t self_thr;

    siginfo = rt_malloc(sizeof(*siginfo));
    if (siginfo)
    {
        siginfo->ksiginfo.signo = signo;
        siginfo->ksiginfo.code = code;
        siginfo->ksiginfo.value = value;

        self_lwp = lwp_self();
        self_thr = rt_thread_self();
        if (self_lwp)
        {
            siginfo->ksiginfo.from_pid = self_lwp->pid;
            siginfo->ksiginfo.from_tid = self_thr->tid;
        }
        else
        {
            siginfo->ksiginfo.from_pid = 0;
            siginfo->ksiginfo.from_tid = 0;
        }
    }

    return siginfo;
}

rt_inline void siginfo_delete(lwp_siginfo_t siginfo)
{
    rt_free(siginfo);
}

rt_inline void _sigorsets(lwp_sigset_t *dset, const lwp_sigset_t *set0, const lwp_sigset_t *set1)
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

rt_inline void _sigandsets(lwp_sigset_t *dset, const lwp_sigset_t *set0, const lwp_sigset_t *set1)
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

rt_inline void _signotsets(lwp_sigset_t *dset, const lwp_sigset_t *set)
{
    switch (_LWP_NSIG_WORDS)
    {
        case 4:
            dset->sig[3] = ~set->sig[3];
            dset->sig[2] = ~set->sig[2];
        case 2:
            dset->sig[1] = ~set->sig[1];
        case 1:
            dset->sig[0] = ~set->sig[0];
        default:
            return;
    }
}

rt_inline void _sigaddset(lwp_sigset_t *set, int _sig)
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

rt_inline void _sigdelset(lwp_sigset_t *set, int _sig)
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

rt_inline int _sigisemptyset(lwp_sigset_t *set)
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

rt_inline int _sigismember(lwp_sigset_t *set, int _sig)
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

rt_inline int _next_signal(lwp_sigset_t *pending, lwp_sigset_t *mask)
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

#define _SIGQ(tp) (&(tp)->signal.sig_queue)

rt_inline int sigqueue_isempty(lwp_sigqueue_t sigqueue)
{
    return _sigisemptyset(&sigqueue->sigset_pending);
}

rt_inline int sigqueue_ismember(lwp_sigqueue_t sigqueue, int signo)
{
    return _sigismember(&sigqueue->sigset_pending, signo);
}

rt_inline int sigqueue_peek(lwp_sigqueue_t sigqueue, lwp_sigset_t *mask)
{
    return _next_signal(&sigqueue->sigset_pending, mask);
}

rt_inline int sigqueue_examine(lwp_sigqueue_t sigqueue, lwp_sigset_t *pending)
{
    int is_empty = sigqueue_isempty(sigqueue);
    if (!is_empty)
    {
        _sigorsets(pending, &sigqueue->sigset_pending, &sigqueue->sigset_pending);
    }
    return is_empty;
}

static void sigqueue_enqueue(lwp_sigqueue_t sigqueue, lwp_siginfo_t siginfo)
{
    lwp_siginfo_t idx;
    rt_bool_t inserted = RT_FALSE;
    rt_list_for_each_entry(idx, &sigqueue->siginfo_list, node)
    {
        if (idx->ksiginfo.signo >= siginfo->ksiginfo.signo)
        {
            rt_list_insert_after(&idx->node, &siginfo->node);
            inserted = RT_TRUE;
            break;
        }
    }

    if (!inserted)
        rt_list_insert_before(&sigqueue->siginfo_list, &siginfo->node);

    _sigaddset(&sigqueue->sigset_pending, siginfo->ksiginfo.signo);
    return ;
}

/**
 * dequeue a siginfo matching the signo which is likely to be existed, and
 * test if any other siblings remains
 */
static lwp_siginfo_t sigqueue_dequeue(lwp_sigqueue_t sigqueue, int signo)
{
    lwp_siginfo_t found;
    lwp_siginfo_t candidate;
    lwp_siginfo_t next;
    rt_bool_t is_empty;

    found = RT_NULL;
    is_empty = RT_TRUE;
    rt_list_for_each_entry_safe(candidate, next, &sigqueue->siginfo_list, node)
    {
        if (candidate->ksiginfo.signo == signo)
        {
            if (found)
            {
                /* already found */
                is_empty = RT_FALSE;
                break;
            }
            else
            {
                /* found first */
                found = candidate;
                rt_list_remove(&found->node);
            }
        }
        else if (candidate->ksiginfo.signo > signo)
            break;
    }

    if (found && is_empty)
        _sigdelset(&sigqueue->sigset_pending, signo);

    return found;
}

static void sigqueue_discard(lwp_sigqueue_t sigqueue, int signo)
{
    lwp_siginfo_t queuing_si;
    while (!sigqueue_isempty(sigqueue))
    {
        queuing_si = sigqueue_dequeue(sigqueue, signo);
        siginfo_delete(queuing_si);
    }
}

/* assuming that (void *) is compatible to long at length */
RT_STATIC_ASSERT(lp_width_same, sizeof(void *) == sizeof(long));

/** translate lwp siginfo to user siginfo_t  */
rt_inline void siginfo_k2u(lwp_siginfo_t ksigi, siginfo_t *usigi)
{
    usigi->si_code = ksigi->ksiginfo.code;
    usigi->si_signo = ksigi->ksiginfo.signo;
    usigi->si_value.sival_ptr = (void *)ksigi->ksiginfo.value;
    usigi->si_pid = ksigi->ksiginfo.from_pid;

    /* deprecated field */
    usigi->si_errno = 0;
}

/* must called in locked context */
rt_inline lwp_sighandler_t _get_sighandler_locked(struct rt_lwp *lwp, int signo)
{
    return lwp->signal.sig_action[signo - 1];
}

static lwp_sigset_t *_mask_block_fn(rt_thread_t thread, const lwp_sigset_t *sigset, lwp_sigset_t *new_set)
{
    _sigorsets(new_set, &thread->signal.sigset_mask, sigset);
    return new_set;
}

static lwp_sigset_t *_mask_unblock_fn(rt_thread_t thread, const lwp_sigset_t *sigset, lwp_sigset_t *new_set)
{
    lwp_sigset_t complement;
    _signotsets(&complement, sigset);
    _sigandsets(new_set, &thread->signal.sigset_mask, &complement);
    return new_set;
}

static lwp_sigset_t *_mask_set_fn(rt_thread_t thread, const lwp_sigset_t *sigset, lwp_sigset_t *new_set)
{
    memcpy(new_set, sigset, sizeof(*sigset));
    return new_set;
}

static lwp_sigset_t *(*_sig_mask_fn[__LWP_SIG_MASK_CMD_WATERMARK])
    (rt_thread_t thread, const lwp_sigset_t *sigset, lwp_sigset_t *new_set) = {
        [LWP_SIG_MASK_CMD_BLOCK] = _mask_block_fn,
        [LWP_SIG_MASK_CMD_UNBLOCK] = _mask_unblock_fn,
        [LWP_SIG_MASK_CMD_SET_MASK] = _mask_set_fn,
    };

static void _thread_signal_mask(rt_thread_t thread, lwp_sig_mask_cmd_t how,
                                const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    lwp_sigset_t new_set;

    /**
     * @note POSIX wants this API to be capable to query the current mask
     *       by passing NULL in `sigset`
     */
    if (oset)
        memcpy(oset, &thread->signal.sigset_mask, sizeof(lwp_sigset_t));

    if (sigset)
    {
        _sig_mask_fn[how](thread, sigset, &new_set);

        /* remove un-maskable signal from set */
        _sigdelset(&new_set, SIGKILL);
        _sigdelset(&new_set, SIGSTOP);

        memcpy(&thread->signal.sigset_mask, &new_set, sizeof(lwp_sigset_t));
    }
}

void lwp_sigqueue_clear(lwp_sigqueue_t sigq)
{
    lwp_siginfo_t this, next;
    if (!sigqueue_isempty(sigq))
    {
        rt_list_for_each_entry_safe(this, next, &sigq->siginfo_list, node)
        {
            siginfo_delete(this);
        }
    }
}

static void lwp_signal_notify(rt_slist_t *list_head, lwp_siginfo_t siginfo)
{
    rt_slist_t *node;

    rt_slist_for_each(node, list_head)
    {
        struct rt_lwp_notify *n = rt_slist_entry(node, struct rt_lwp_notify, list_node);
        if (n->notify)
        {
            n->notify(n->signalfd_queue, siginfo->ksiginfo.signo);
        }
    }
}

rt_err_t lwp_signal_init(struct lwp_signal *sig)
{
    rt_err_t rc;
    rc = rt_mutex_init(&sig->sig_lock, "lwpsig", RT_IPC_FLAG_FIFO);
    if (rc == RT_EOK)
    {
        memset(&sig->sig_dispatch_thr, 0, sizeof(sig->sig_dispatch_thr));

        memset(&sig->sig_action, 0, sizeof(sig->sig_action));
        memset(&sig->sig_action_nodefer, 0, sizeof(sig->sig_action_nodefer));
        memset(&sig->sig_action_onstack, 0, sizeof(sig->sig_action_onstack));
        memset(&sig->sig_action_restart, 0, sizeof(sig->sig_action_restart));
        memset(&sig->sig_action_siginfo, 0, sizeof(sig->sig_action_siginfo));
        lwp_sigqueue_init(&sig->sig_queue);
    }
    return rc;
}

rt_err_t lwp_signal_detach(struct lwp_signal *signal)
{
    rt_err_t ret;

    lwp_sigqueue_clear(&signal->sig_queue);
    ret = rt_mutex_detach(&signal->sig_lock);

    return ret;
}

int lwp_thread_signal_suspend_check(rt_thread_t thread, int suspend_flag)
{
    struct rt_lwp *lwp = (struct rt_lwp*)thread->lwp;
    int ret = 0;

    switch (suspend_flag)
    {
        case RT_INTERRUPTIBLE:
            if (!sigqueue_isempty(_SIGQ(thread)))
            {
                break;
            }
            if (thread->lwp && !sigqueue_isempty(_SIGQ(lwp)))
            {
                break;
            }
            ret = 1;
            break;
        case RT_KILLABLE:
            if (sigqueue_ismember(_SIGQ(thread), SIGKILL))
            {
                break;
            }
            if (thread->lwp && sigqueue_ismember(_SIGQ(lwp), SIGKILL))
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

void lwp_thread_signal_catch(void *exp_frame)
{
    rt_base_t level;
    int signo = 0;
    struct rt_thread *thread;
    struct rt_lwp *lwp;
    lwp_siginfo_t siginfo = 0;
    lwp_sigqueue_t pending;
    lwp_sigset_t *sig_mask;
    lwp_sigset_t save_sig_mask;
    lwp_sigset_t new_sig_mask;
    lwp_sighandler_t handler = 0;
    siginfo_t usiginfo;
    siginfo_t *p_usi = RT_NULL;

    thread = rt_thread_self();
    lwp = (struct rt_lwp*)thread->lwp;

    RT_ASSERT(!!lwp);
    level = rt_hw_interrupt_disable();

    /* check if signal exist */
    if (!sigqueue_isempty(_SIGQ(thread)))
    {
        pending = _SIGQ(thread);
        sig_mask = &thread->signal.sigset_mask;
    }
    else if (!sigqueue_isempty(_SIGQ(lwp)))
    {
        pending = _SIGQ(lwp);
        sig_mask = &thread->signal.sigset_mask;
    }
    else
    {
        pending = RT_NULL;
    }

    if (pending)
    {
        /* peek the pending signal */
        signo = sigqueue_peek(pending, sig_mask);
        if (signo)
        {
            siginfo = sigqueue_dequeue(pending, signo);
            RT_ASSERT(siginfo != RT_NULL);
            handler = _get_sighandler_locked(lwp, signo);

            /* IGN signal will never be queued */
            RT_ASSERT(handler != LWP_SIG_ACT_IGN);

            /* copy the blocked signal mask from the registered signal action */
            memcpy(&new_sig_mask, &lwp->signal.sig_action_mask[signo - 1], sizeof(new_sig_mask));

            if (!_sigismember(&lwp->signal.sig_action_nodefer, signo))
                _sigaddset(&new_sig_mask, signo);

            _thread_signal_mask(thread, LWP_SIG_MASK_CMD_BLOCK, &new_sig_mask, &save_sig_mask);

            /* siginfo is need for signal action */
            if (_sigismember(&lwp->signal.sig_action_siginfo, signo))
            {
                siginfo_k2u(siginfo, &usiginfo);
                p_usi = &usiginfo;
            }
            else
                p_usi = RT_NULL;
        }
    }
    rt_hw_interrupt_enable(level);

    if (pending && signo)
    {
        siginfo_delete(siginfo);

        /* signal default handler */
        if (handler == LWP_SIG_ACT_DFL)
        {
            LOG_D("%s: default handler; and exit", __func__);
            sys_exit_group(0);
        }

        /**
         * enter signal action of user
         * @note that the p_usi is release before entering signal action by
         * reseting the kernel sp.
         */
        LOG_D("%s: enter signal handler(signo=%d) at %p", __func__, signo, handler);
        arch_thread_signal_enter(signo, p_usi, exp_frame, handler, &save_sig_mask);
        /* the arch_thread_signal_enter() never return */
        RT_ASSERT(0);
    }
}
static int _do_signal_wakeup(rt_thread_t thread, int sig)
{
    int need_schedule;
    if (!_sigismember(&thread->signal.sigset_mask, sig))
    {
        if ((thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK)
        {
            if ((thread->stat & RT_SIGNAL_COMMON_WAKEUP_MASK) != RT_SIGNAL_COMMON_WAKEUP_MASK)
            {
                rt_thread_wakeup(thread);
                need_schedule = 1;
            }
            else if ((sig == SIGKILL) && ((thread->stat & RT_SIGNAL_KILL_WAKEUP_MASK) != RT_SIGNAL_KILL_WAKEUP_MASK))
            {
                rt_thread_wakeup(thread);
                need_schedule = 1;
            }
            else
            {
                need_schedule = 0;
            }
        }
        else
            need_schedule = 0;
    }
    else
        need_schedule = 0;

    return need_schedule;
}

/** find a candidate to be notified of the arrival */
static rt_thread_t _signal_find_catcher(struct rt_lwp *lwp, int signo)
{
    rt_thread_t catcher = RT_NULL;
    rt_thread_t candidate;

    candidate = lwp->signal.sig_dispatch_thr[signo - 1];
    if (candidate != RT_NULL && !_sigismember(&candidate->signal.sigset_mask, signo))
    {
        catcher = candidate;
    }
    else
    {
        candidate = rt_thread_self();

        /** @note: lwp of current is a const value that can be safely read */
        if (candidate->lwp == lwp &&
            !_sigismember(&candidate->signal.sigset_mask, signo))
        {
            catcher = candidate;
        }
        else
        {
            rt_list_for_each_entry(candidate, &lwp->t_grp, sibling)
            {
                if (!_sigismember(&candidate->signal.sigset_mask, signo))
                {
                    catcher = candidate;
                    break;
                }
            }

            /* fall back to main thread */
            if (catcher == RT_NULL)
                catcher = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
        }

        /* reset the cache thread to catcher (even if catcher is main thread) */
        lwp->signal.sig_dispatch_thr[signo - 1] = catcher;
    }

    return catcher;
}

static int _siginfo_deliver_to_lwp(struct rt_lwp *lwp, lwp_siginfo_t siginfo)
{
    rt_thread_t catcher;

    catcher = _signal_find_catcher(lwp, siginfo->ksiginfo.signo);

    sigqueue_enqueue(&lwp->signal.sig_queue, siginfo);
    return _do_signal_wakeup(catcher, siginfo->ksiginfo.signo);
}

static int _siginfo_deliver_to_thread(rt_thread_t thread, lwp_siginfo_t siginfo)
{
    sigqueue_enqueue(_SIGQ(thread), siginfo);
    return _do_signal_wakeup(thread, siginfo->ksiginfo.signo);
}

rt_inline rt_bool_t _sighandler_is_ignored(struct rt_lwp *lwp, int signo)
{
    rt_bool_t is_ignored;
    lwp_sighandler_t action;
    lwp_sigset_t ign_set = lwp_sigset_init(LWP_SIG_IGNORE_SET);

    action = _get_sighandler_locked(lwp, signo);

    if (action == LWP_SIG_ACT_IGN)
        is_ignored = RT_TRUE;
    else if (action == LWP_SIG_ACT_DFL && _sigismember(&ign_set, signo))
        is_ignored = RT_TRUE;
    else
        is_ignored = RT_FALSE;

    return is_ignored;
}

rt_inline rt_bool_t _sighandler_cannot_caught(struct rt_lwp *lwp, int signo)
{
    return signo == SIGKILL || signo == SIGSTOP;
}

rt_err_t lwp_signal_kill(struct rt_lwp *lwp, long signo, long code, long value)
{
    rt_err_t ret = -1;
    rt_base_t level;
    lwp_siginfo_t siginfo;
    rt_bool_t terminated;
    rt_bool_t need_schedule;

    /** must be able to be suspended */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    if (!lwp || signo <= 0 || signo > _LWP_NSIG)
    {
        ret = -RT_EINVAL;
    }
    else
    {
        LOG_D("%s(lwp=%p \"%s\",signo=%ld,code=%ld,value=%ld)",
              __func__, lwp, lwp->cmd, signo, code, value);

        need_schedule = RT_FALSE;

        /* FIXME: acquire READ lock to lwp */
        level = rt_hw_interrupt_disable();
        terminated = lwp->terminated;

        /* short-circuit code for inactive task, ignored signals */
        if (terminated || _sighandler_is_ignored(lwp, signo))
        {
            ret = 0;
        }
        else
        {
            siginfo = siginfo_create(signo, code, value);

            if (siginfo)
            {
                need_schedule = _siginfo_deliver_to_lwp(lwp, siginfo);
                ret = 0;
                lwp_signal_notify(&lwp->signalfd_notify_head, siginfo);
            }
            else
            {
                LOG_I("%s: siginfo malloc failed", __func__);
                ret = -RT_ENOMEM;
            }
        }

        rt_hw_interrupt_enable(level);

        if (need_schedule)
            rt_schedule();
    }
    return ret;
}

static void _signal_action_flag_k2u(int signo, struct lwp_signal *signal, struct lwp_sigaction *act)
{
    long flags = 0;
    if (_sigismember(&signal->sig_action_nodefer, signo))
        flags |= SA_NODEFER;
    if (_sigismember(&signal->sig_action_onstack, signo))
        flags |= SA_ONSTACK;
    if (_sigismember(&signal->sig_action_restart, signo))
        flags |= SA_RESTART;
    if (_sigismember(&signal->sig_action_siginfo, signo))
        flags |= SA_SIGINFO;

    act->sa_flags = flags;
}

static void _signal_action_flag_u2k(int signo, struct lwp_signal *signal, const struct lwp_sigaction *act)
{
    long flags = act->sa_flags;
    if (flags & SA_NODEFER)
        _sigaddset(&signal->sig_action_nodefer, signo);
    if (flags & SA_ONSTACK)
        _sigaddset(&signal->sig_action_onstack, signo);
    if (flags & SA_RESTART)
        _sigaddset(&signal->sig_action_restart, signo);
    if (flags & SA_SIGINFO)
        _sigaddset(&signal->sig_action_siginfo, signo);
}

rt_err_t lwp_signal_action(struct rt_lwp *lwp, int signo,
                           const struct lwp_sigaction *restrict act,
                           struct lwp_sigaction *restrict oact)
{
    lwp_sighandler_t prev_handler;
    lwp_sigqueue_t thread_sigq;
    rt_list_t *thread_list;
    rt_err_t ret = RT_EOK;
    rt_base_t level;

    if (lwp)
    {
        /** acquire READ access to lwp */
        level = rt_hw_interrupt_disable();

        if (oact)
        {
            oact->sa_mask = lwp->signal.sig_action_mask[signo - 1];
            oact->__sa_handler._sa_handler = lwp->signal.sig_action[signo - 1];
            oact->sa_restorer = RT_NULL;
            _signal_action_flag_k2u(signo, &lwp->signal, oact);
        }
        if (act)
        {
            /**
             * @note POSIX.1-2017 requires calls to sigaction() that supply a NULL act
             * argument succeed, even in the case of signals that cannot be caught or ignored
             */
            if (_sighandler_cannot_caught(lwp, signo))
                ret = -RT_EINVAL;
            else
            {
                prev_handler = _get_sighandler_locked(lwp, signo);
                lwp->signal.sig_action_mask[signo - 1] = act->sa_mask;
                if (act->__sa_handler._sa_handler == SIG_IGN)
                    lwp->signal.sig_action[signo - 1] = LWP_SIG_ACT_IGN;
                else
                    lwp->signal.sig_action[signo - 1] = act->__sa_handler._sa_handler;

                _signal_action_flag_u2k(signo, &lwp->signal, act);

                /**
                 * @brief Discard the pending signal if signal action is set to SIG_IGN
                 *
                 * @note POSIX.1-2017: Setting a signal action to SIG_IGN for a signal
                 * that is pending shall cause the pending signal to be discarded,
                 * whether or not it is blocked.
                 */
                if (prev_handler != LWP_SIG_ACT_IGN &&
                    _get_sighandler_locked(lwp, signo) == LWP_SIG_ACT_IGN)
                {
                    sigqueue_discard(_SIGQ(lwp), signo);
                    for (thread_list = lwp->t_grp.next;
                         thread_list != &lwp->t_grp;
                         thread_list = thread_list->next)
                    {
                        thread_sigq = _SIGQ(rt_list_entry(thread_list, struct rt_thread, sibling));
                        sigqueue_discard(thread_sigq, signo);
                    }
                }
            }
        }

        rt_hw_interrupt_enable(level);
    }
    else
        ret = -RT_EINVAL;

    return ret;
}

rt_err_t lwp_thread_signal_kill(rt_thread_t thread, long signo, long code, long value)
{
    rt_err_t ret = -1;
    rt_base_t level;
    struct rt_lwp *lwp;
    lwp_siginfo_t siginfo;
    rt_bool_t need_schedule;

    /** must be able to be suspended */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    if (!thread || signo < 0 || signo >= _LWP_NSIG)
    {
        ret = -RT_EINVAL;
    }
    else
    {
        lwp = thread->lwp;
        need_schedule = RT_FALSE;

        RT_ASSERT(lwp);

        /* FIXME: acquire READ lock to lwp */
        level = rt_hw_interrupt_disable();

        if (!lwp)
            ret = -RT_EPERM;
        else if (lwp->terminated || _sighandler_is_ignored(lwp, signo))
            ret = 0;
        else
        {
            siginfo = siginfo_create(signo, code, value);

            if (siginfo)
            {
                need_schedule = _siginfo_deliver_to_thread(thread, siginfo);
                ret = 0;
                lwp_signal_notify(&lwp->signalfd_notify_head, siginfo);
            }
            else
            {
                LOG_I("%s: siginfo malloc failed", __func__);
                ret = -RT_ENOMEM;
            }
        }

        rt_hw_interrupt_enable(level);

        if (need_schedule)
            rt_schedule();
    }

    return ret;
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

rt_err_t lwp_thread_signal_mask(rt_thread_t thread, lwp_sig_mask_cmd_t how,
                                const lwp_sigset_t *sigset, lwp_sigset_t *oset)
{
    rt_err_t ret = -1;
    rt_base_t level;
    struct rt_lwp *lwp;

    if (thread)
    {
        /** FIXME: acquire READ access to rt_thread */
        level = rt_hw_interrupt_disable();

        lwp = (struct rt_lwp*)thread->lwp;
        if (!lwp)
        {
            ret = -RT_EPERM;
        }
        else
        {
            ret = 0;
            _thread_signal_mask(thread, how, sigset, oset);
        }

        rt_hw_interrupt_enable(level);
    }
    else
        ret = -RT_EINVAL;

    return ret;
}

static int _dequeue_signal(rt_thread_t thread, lwp_sigset_t *mask, siginfo_t *usi)
{
    int signo;
    lwp_siginfo_t si;
    struct rt_lwp *lwp;
    lwp_sigset_t *pending;
    lwp_sigqueue_t sigqueue;

    sigqueue = _SIGQ(thread);
    pending = &sigqueue->sigset_pending;
    signo = _next_signal(pending, mask);
    if (!signo)
    {
        lwp = thread->lwp;
        RT_ASSERT(lwp);
        sigqueue = _SIGQ(lwp);
        pending = &sigqueue->sigset_pending;
        signo = _next_signal(pending, mask);
    }

    if (!signo)
        return signo;

    si = sigqueue_dequeue(sigqueue, signo);
    RT_ASSERT(!!si);

    siginfo_k2u(si, usi);
    siginfo_delete(si);

    return signo;
}

rt_err_t lwp_thread_signal_timedwait(rt_thread_t thread, lwp_sigset_t *sigset,
                                     siginfo_t *usi, struct timespec *timeout)
{
    rt_base_t level;
    rt_err_t ret;
    lwp_sigset_t saved_sigset;
    lwp_sigset_t blocked_sigset;
    int sig;

    /**
     * @brief POSIX
     * If one of the signals in set is already pending for the calling thread,
     * sigwaitinfo() will return immediately
     */

    /* Create a mask of signals user dont want or cannot catch */
    _sigdelset(sigset, SIGKILL);
    _sigdelset(sigset, SIGSTOP);
    _signotsets(sigset, sigset);


    /* FIXME: acquire READ lock to lwp */
    level = rt_hw_interrupt_disable();
    sig = _dequeue_signal(thread, sigset, usi);
    rt_hw_interrupt_enable(level);
    if (sig)
        return sig;

    /**
     * @brief POSIX
     * if none of the signals specified by set are pending, sigtimedwait() shall
     * wait for the time interval specified in the timespec structure referenced
     * by timeout.
     *
     * @note If the pending signal arrives before thread suspend, the suspend
     * operation will return a failure
     */
    _sigandsets(&blocked_sigset, &thread->signal.sigset_mask, sigset);
    _thread_signal_mask(thread, LWP_SIG_MASK_CMD_SET_MASK, &blocked_sigset, &saved_sigset);
    if (timeout)
    {
        rt_uint32_t time;
        time = rt_timespec_to_tick(timeout);

        /**
         * @brief POSIX
         * If the timespec structure pointed to by timeout is zero-valued and
         * if none of the signals specified by set are pending, then
         * sigtimedwait() shall return immediately with an error
         */
        if (time == 0)
            return -EAGAIN;

        ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);
        rt_timer_control(&(thread->thread_timer),
                         RT_TIMER_CTRL_SET_TIME,
                         &timeout);
        rt_timer_start(&(thread->thread_timer));

    }
    else
    {
        /* suspend kernel forever until signal was received */
        ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);
    }

    if (ret == RT_EOK)
    {
        rt_schedule();
        /* If thread->error reliable? */
        if (thread->error == -RT_EINTR)
            ret = -EINTR;
        else
            ret = -EAGAIN;
    }
    /* else ret == -EINTR */
    _thread_signal_mask(thread, LWP_SIG_MASK_CMD_SET_MASK, &saved_sigset, RT_NULL);

    /* FIXME: acquire READ lock to lwp */
    level = rt_hw_interrupt_disable();
    sig = _dequeue_signal(thread, sigset, usi);
    rt_hw_interrupt_enable(level);

    return sig ? sig : ret;
}

void lwp_thread_signal_pending(rt_thread_t thread, lwp_sigset_t *pending)
{
    rt_base_t level;
    struct rt_lwp *lwp;
    lwp = thread->lwp;

    if (lwp)
    {
        memset(pending, 0, sizeof(*pending));

        level = rt_hw_interrupt_disable();
        sigqueue_examine(_SIGQ(thread), pending);
        sigqueue_examine(_SIGQ(lwp), pending);
        rt_hw_interrupt_enable(level);

        _sigandsets(pending, pending, &thread->signal.sigset_mask);
    }
}
