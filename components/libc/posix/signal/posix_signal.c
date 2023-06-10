/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/1      Bernard      The first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <sys/time.h>
#include <sys/errno.h>

#include "posix_signal.h"

#define sig_valid(sig_no)   (sig_no >= 0 && sig_no < RT_SIG_MAX)

void (*signal(int sig, void (*func)(int))) (int)
{
    return rt_signal_install(sig, func);
}

/**
 * @brief    This function will examines, changes, or examines and changes the signal mask of the calling thread.
 *
 * @param    how indicates the way in which the existing set of blocked signals should be changed.
 *           The following are the possible values for option:
 *
 *              SIG_BLOCK       The set of blocked signals is the union of the current set and the set argument.
 *
 *              SIG_UNBLOCK     The signals in set are removed from the current set of blocked signals.
 *                              It is permissible to attempt to unblock a signal which is not blocked.
 *
 *              SIG_SETMASK     The set of blocked signals is set to the argument set.
 *
 * @param    set is a pointer to a sigset_t object that specifies the new set of blocked signals.
 *           If set is NULL, then the signal mask is unchanged (i.e., how is ignored)
 *
 * @param    oset is a pointer to a sigset_t object that is used to return the previous set of blocked signals.
 *           If oset is non-NULL, the previous value of the signal mask is stored in it.
 *
 * @return   Returns 0 on success.
 */
int sigprocmask (int how, const sigset_t *set, sigset_t *oset)
{
    rt_base_t level;
    rt_thread_t tid;

    tid = rt_thread_self();

    level = rt_hw_interrupt_disable();
    if (oset) *oset = tid->sig_mask;

    if (set)
    {
        switch(how)
        {
        case SIG_BLOCK:
            tid->sig_mask |= *set;
            break;
        case SIG_UNBLOCK:
            tid->sig_mask &= ~*set;
            break;
        case SIG_SETMASK:
            tid->sig_mask =  *set;
            break;
        default:
            break;
        }
    }
    rt_hw_interrupt_enable(level);

    return 0;
}

/**
 * @brief    This function will examines the signal mask of the calling thread.
 *
 * @param    set is a pointer to a sigset_t object that is used to return the previous set of blocked signals.
 *           If set is non-NULL, the previous value of the signal mask is stored in it.
 *
 * @return   Returns 0 on success.
 */
int sigpending (sigset_t *set)
{
    sigprocmask(SIG_SETMASK, RT_NULL, set);
    return 0;
}
/**
 * @brief    This function will temporarily replace the signal mask of the calling thread
 *           with the mask given and then suspends the thread until delivery of an expected signal
 *           or a signal whose action is to terminate a process.
 *
 * @param    set is a pointer of a sigset_t object that is used to replace the original mask of the calling thread.
 *
 * @return   Returns 0 on success.
 *           If the return value is any other values, it means that the signal wait failed.
 */
int sigsuspend (const sigset_t *set)
{
    int ret  = 0;
    sigset_t origin_set;
    sigset_t suspend_set;
    siginfo_t info;            /* unless paremeter */

    /* get the origin signal information */
    sigpending(&origin_set);

    /* set the new signal information */
    sigprocmask(SIG_BLOCK, set, RT_NULL);
    sigpending(&suspend_set);

    ret = rt_signal_wait(&suspend_set, &info, RT_WAITING_FOREVER);

    /* restore the original sigprocmask */
    sigprocmask(SIG_UNBLOCK, (sigset_t *)0xffffUL, RT_NULL);
    sigprocmask(SIG_BLOCK, &origin_set, RT_NULL);

    return ret;
}

/**
 * @brief    This function will install or confirm action for specified signal.
 *
 * @param    signum is the signal to be handled.
 *
 * @param    act is the new signal action, or NULL to restore default action.
 *
 * @param    oldact returns the previous signal action, or NULL if not required.
 *
 * @return   Returns 0 on success or -1 on failure.
 */
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
    rt_sighandler_t old = RT_NULL;

    if (!sig_valid(signum)) return -RT_ERROR;

    if (act)
        old = rt_signal_install(signum, act->sa_handler);
    else
    {
        old = rt_signal_install(signum, RT_NULL);
        rt_signal_install(signum, old);
    }

    if (oldact)
        oldact->sa_handler = old;

    return 0;
}
/**
 * @brief    This function will suspends execution of the calling thread until one of
 *           the signals in the given set is pending. If none of the signals specified
 *           are pending, it will wait for the specified time interval.
 *
 * @param    set is the set of signal values to be waited for.
 *
 * @param    info is a pointer to the received signal info.
 *
 * @param    timeout is a pointer to a timespec structure that specifys the waiting time.
 *
 * @return   Return 0 on success. Otherwise, return -1 and set errno to indicate the error.
 */
int sigtimedwait(const sigset_t *set, siginfo_t *info, const struct timespec *timeout)
{
    int ret  = 0;
    int tick = RT_WAITING_FOREVER;

    if (timeout)
    {
        tick = rt_timespec_to_tick(timeout);
    }

    ret = rt_signal_wait(set, info, tick);
    if (ret == 0) return 0;

    errno = ret;
    return -1;
}
/**
 * @brief    This function will suspend execution of the calling thread until one of
 *           the specified signal becomes pending and return the signal number.
 *
 * @param    set is the set of signal values to be waited for.
 *
 * @param    sig is a pointer to the received signal number.
 *
 * @return   Return 0 on success or -1 on failure.
 */
int sigwait(const sigset_t *set, int *sig)
{
    siginfo_t si;
    if (sigtimedwait(set, &si, 0) < 0)
        return -1;

    *sig = si.si_signo;
    return 0;
}
/**
 * @brief    This function will suspend execution of the calling thread until one of
 *           the specified signal is pending.
 *
 * @param    set is the set of signal values to be waited for.
 *
 * @param    info is a pointer to the received signal info.
 *
 * @return   Return 0 on success or -1 on failure.
 */
int sigwaitinfo(const sigset_t *set, siginfo_t *info)
{
    return sigtimedwait(set, info, NULL);
}

/**
 * @brief    This function willsend a signal to the caller
 *
 * @param    sig is the signal that is to be sent.
 *
 * @return   Returns 0 on success.
 */
int raise(int sig)
{
    rt_thread_kill(rt_thread_self(), sig);
    return 0;
}

#include <sys/types.h>
int sigqueue (pid_t pid, int signo, const union sigval value)
{
    /* no support, signal queue */

    return -1;
}

