/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven         first version.
 */

#ifndef LWP_SIGNAL_H__
#define LWP_SIGNAL_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

int lwp_signal_check(void);
int lwp_signal_backup(void *user_sp, void *user_pc, void* user_flag);
struct rt_user_context *lwp_signal_restore(void);
lwp_sighandler_t lwp_sighandler_get(int sig);
void lwp_sighandler_set(int sig, lwp_sighandler_t func);
#ifndef ARCH_MM_MMU
void lwp_thread_sighandler_set(int sig, lwp_sighandler_t func);
#endif
int lwp_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset);
int lwp_sigaction(int sig, const struct lwp_sigaction *act, struct lwp_sigaction * oact, size_t sigsetsize);
int lwp_thread_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset);

int lwp_kill(pid_t pid, int sig);
int lwp_thread_kill(rt_thread_t thread, int sig);

#ifdef __cplusplus
}
#endif

#endif
