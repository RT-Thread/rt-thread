/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/1      Bernard      The first version
 */

#ifndef POSIX_SIGNAL_H__
#define POSIX_SIGNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>
#include <sys/signal.h>

enum rt_signal_value{
    SIG1 = SIGHUP,
    SIG2 = SIGINT,
    SIG3 = SIGQUIT,
    SIG4 = SIGILL,
    SIG5 = SIGTRAP,
    SIG6 = SIGABRT,
    SIG7 = SIGEMT,
    SIG8 = SIGFPE,
    SIG9 = SIGKILL,
    SIG10 = SIGBUS,
    SIG11 = SIGSEGV,
    SIG12 = SIGSYS,
    SIG13 = SIGPIPE,
    SIG14 = SIGALRM,
    SIG15 = SIGTERM,
    SIG16 = SIGURG,
    SIG17 = SIGSTOP,
    SIG18 = SIGTSTP,
    SIG19 = SIGCONT,
    SIG20 = SIGCHLD,
    SIG21 = SIGTTIN,
    SIG22 = SIGTTOU,
    SIG23 = SIGPOLL,
    SIG24 = 24, // SIGXCPU,
    SIG25 = 25, // SIGXFSZ,
    SIG26 = 26, // SIGVTALRM,
    SIG27 = 27, // SIGPROF,
    SIG28 = SIGWINCH,
    SIG29 = 29, // SIGLOST,
    SIG30 = SIGUSR1,
    SIG31 = SIGUSR2,
    SIGRT_MIN = 27, // SIGRTMIN,
    SIGRT_MAX = 31, // SIGRTMAX,
    SIGMAX = NSIG,
};

#ifdef __cplusplus
}
#endif

#endif
