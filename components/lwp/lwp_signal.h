/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven       first version.
 * 2023-07-06     Shell        update the generation, pending and delivery API
 */

#ifndef __LWP_SIGNAL_H__
#define __LWP_SIGNAL_H__

#include "syscall_generic.h"

#include <rtthread.h>
#include <sys/signal.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _USIGNAL_SIGMASK(signo) (1u << ((signo)-1))
#define LWP_SIG_IGNORE_SET      (_USIGNAL_SIGMASK(SIGCHLD) | _USIGNAL_SIGMASK(SIGURG))
#define LWP_SIG_ACT_DFL         ((lwp_sighandler_t)0)
#define LWP_SIG_ACT_IGN         ((lwp_sighandler_t)1)
#define LWP_SIG_USER_SA_FLAGS                                               \
    (SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO | SA_ONSTACK | SA_RESTART |   \
     SA_NODEFER | SA_RESETHAND | SA_EXPOSE_TAGBITS)

typedef enum {
    LWP_SIG_MASK_CMD_BLOCK,
    LWP_SIG_MASK_CMD_UNBLOCK,
    LWP_SIG_MASK_CMD_SET_MASK,
    __LWP_SIG_MASK_CMD_WATERMARK
} lwp_sig_mask_cmd_t;

/**
 * LwP implementation of POSIX signal
 */
struct lwp_signal {
    struct lwp_sigqueue sig_queue;
    rt_thread_t sig_dispatch_thr[_LWP_NSIG];

    lwp_sighandler_t sig_action[_LWP_NSIG];
    lwp_sigset_t sig_action_mask[_LWP_NSIG];

    lwp_sigset_t sig_action_nodefer;
    lwp_sigset_t sig_action_onstack;
    lwp_sigset_t sig_action_restart;
    lwp_sigset_t sig_action_siginfo;
};

struct rt_lwp;

#ifndef ARCH_MM_MMU
void lwp_sighandler_set(int sig, lwp_sighandler_t func);
void lwp_thread_sighandler_set(int sig, lwp_sighandler_t func);
#endif

rt_inline void lwp_sigqueue_init(lwp_sigqueue_t sigq)
{
    rt_memset(&sigq->sigset_pending, 0, sizeof(lwp_sigset_t));
    rt_list_init(&sigq->siginfo_list);
}

/**
 * @brief release the signal queue
 *
 * @param sigq target signal queue
 */
void lwp_sigqueue_clear(lwp_sigqueue_t sigq);

rt_err_t lwp_signal_init(struct lwp_signal *sig);

rt_err_t lwp_signal_detach(struct lwp_signal *signal);

rt_inline void lwp_thread_signal_detach(struct lwp_thread_signal *tsig)
{
    lwp_sigqueue_clear(&tsig->sig_queue);
}

/**
 * @brief send a signal to the process
 *
 * @param lwp the process to be killed
 * @param signo the signal number
 * @param code as in siginfo
 * @param value as in siginfo
 * @return rt_err_t RT_EINVAL if the parameter is invalid, RT_EOK as successful
 *
 * @note the *signal_kill have the same definition of a successful return as
 *       kill() in IEEE Std 1003.1-2017
 */
rt_err_t lwp_signal_kill(struct rt_lwp *lwp, long signo, long code, long value);

/**
 * @brief set or examine the signal action of signo
 *
 * @param signo signal number
 * @param act the signal action
 * @param oact the old signal action
 * @return rt_err_t
 */
rt_err_t lwp_signal_action(struct rt_lwp *lwp, int signo,
                           const struct lwp_sigaction *restrict act,
                           struct lwp_sigaction *restrict oact);

/**
 * @brief send a signal to the thread
 *
 * @param thread target thread
 * @param signo the signal number
 * @param code as in siginfo
 * @param value as in siginfo
 * @return rt_err_t RT_EINVAL if the parameter is invalid, RT_EOK as successful
 */
rt_err_t lwp_thread_signal_kill(rt_thread_t thread, long signo, long code, long value);

/**
 * @brief set signal mask of target thread
 *
 * @param thread the target thread
 * @param how command
 * @param sigset operand
 * @param oset the address to old set
 * @return rt_err_t
 */
rt_err_t lwp_thread_signal_mask(rt_thread_t thread, lwp_sig_mask_cmd_t how,
                                const lwp_sigset_t *sigset, lwp_sigset_t *oset);

/**
 * @brief Catch signal if exists and no return, otherwise return with no side effect
 *
 * @param exp_frame the exception frame on kernel stack
 */
void lwp_thread_signal_catch(void *exp_frame);

/**
 * @brief Check if it's okay to suspend for current lwp thread
 *
 * @param thread target thread
 * @param suspend_flag suspend flag of target thread
 * @return int 1 if can be suspended, otherwise not
 */
int lwp_thread_signal_suspend_check(rt_thread_t thread, int suspend_flag);

/**
 * @brief Asynchronously wait for signal
 *
 * @param thread target thread
 * @param sigset the signals to be waited
 * @param info address of user siginfo
 * @param timeout timeout of waiting
 * @return rt_err_t
 */
rt_err_t lwp_thread_signal_timedwait(rt_thread_t thread, lwp_sigset_t *sigset,
                                     siginfo_t *usi, struct timespec *timeout);

/**
 * @brief Examine the set of signals that are blocked from delivery to the
 * calling thread and that are pending on the process or the calling thread
 *
 * @param thread target thread
 * @param sigset where mask of pending signals is returned
 */
void lwp_thread_signal_pending(rt_thread_t thread, lwp_sigset_t *sigset);

#ifdef __cplusplus
}
#endif

#endif /* __LWP_SIGNAL_H__ */
