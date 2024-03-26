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

#include <sys/signal.h>

enum rt_signal_value{
    SIG1  = SIGHUP,  // Hangup detected on controlling terminal or death of controlling process
    SIG2  = SIGINT,  // Interrupt from keyboard
    SIG3  = SIGQUIT, // Quit from keyboard
    SIG4  = SIGILL,  // Illegal instruction
    SIG5  = SIGTRAP, // Trace trap
    SIG6  = SIGABRT, // Abort signal from abort(3)
    SIG7  = SIGEMT,  // Emulator trap
    SIG8  = SIGFPE,  // Floating-point exception
    SIG9  = SIGKILL, // Kill signal
    SIG10 = SIGBUS,  // Bus error
    SIG11 = SIGSEGV, // Segmentation fault
    SIG12 = SIGSYS,  // Bad system call
    SIG13 = SIGPIPE, // Broken pipe
    SIG14 = SIGALRM, // Timer signal from alarm(2)
    SIG15 = SIGTERM, // Termination signal
    SIG16 = SIGURG,  // Urgent condition on socket
    SIG17 = SIGSTOP, // Stop executing (cannot be caught or ignored)
    SIG18 = SIGTSTP, // Stop signal from keyboard to suspend execution
    SIG19 = SIGCONT, // Continue if stopped
    SIG20 = SIGCHLD, // Child status has changed
    SIG21 = SIGTTIN, // Background read from control terminal attempted by background process
    SIG22 = SIGTTOU, // Background write to control terminal attempted by background process
    SIG23 = SIGPOLL, // Pollable event
    SIG24 = 24,      // SIGXCPU: CPU time limit exceeded
    SIG25 = 25,      // SIGXFSZ: File size limit exceeded
    SIG26 = 26,      // SIGVTALRM: Virtual timer expired
    SIG27 = 27,      // SIGPROF: Profiling timer expired
    SIG28 = SIGWINCH,// Window size changed
    SIG29 = 29,      // SIGLOST
    SIG30 = SIGUSR1, // User-defined signal 1
    SIG31 = SIGUSR2, // User-defined signal 2
    SIGRT_MIN = 27, // SIGRTMIN: Minimum real-time signal number
    SIGRT_MAX = 31, // SIGRTMAX: Maximum real-time signal number
    SIGMAX    = NSIG // Number of signals (total)
};

#ifdef __cplusplus
}
#endif

#endif
