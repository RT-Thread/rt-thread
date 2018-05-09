/*
 * File      : signals.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
