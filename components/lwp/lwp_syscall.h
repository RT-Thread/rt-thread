/*
 * File      : lwp_syscall.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2006-03-18     Bernard      the first version
 * 2006-04-25     Bernard      add rt_hw_context_switch_interrupt declaration
 * 2006-09-24     Bernard      add rt_hw_context_switch_to declaration
 * 2012-12-29     Bernard      add rt_hw_exception_install declaration
 * 2017-10-17     Hichard      add some micros
 */

#ifndef __LWP_SYSCALL_H__
#define __LWP_SYSCALL_H__

#include <stdint.h>
#include <rtthread.h>
#include <dfs_posix.h>
#include <sys/time.h>
#include <sys/types.h>

typedef long suseconds_t;       /* microseconds (signed) */
typedef long key_t;             /* IPC key (for Sys V IPC) */
typedef uint32_t id_t;          /* may contain pid, uid or gid */

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	    (-20)
#define	PRIO_MAX	    20

#define	PRIO_PROCESS	0       /* only support lwp process */
#define	PRIO_PGRP	    1
#define	PRIO_USER	    2

#define TIMEVAL_TO_TIMESPEC(tv, ts) {                   \
    (ts)->tv_sec = (tv)->tv_sec;                        \
    (ts)->tv_nsec = (tv)->tv_usec * 1000;               \
}
#define TIMESPEC_TO_TIMEVAL(tv, ts) {                   \
    (tv)->tv_sec = (ts)->tv_sec;                        \
    (tv)->tv_usec = (ts)->tv_nsec / 1000;               \
}

void sys_exit(int value);
ssize_t sys_read(int fd, void *buf, size_t nbyte);
ssize_t sys_write(int fd, const void *buf, size_t nbyte);
off_t sys_lseek(int fd, off_t offset, int whence);
int sys_open(const char *name, int mode, ...);
int sys_close(int fd);
int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int sys_getpriority(int which, id_t who);
int sys_setpriority(int which, id_t who, int prio);
int sys_gettimeofday(struct timeval *tp, struct timezone *tzp);
int sys_settimeofday(const struct timeval *tv, const struct timezone *tzp);
int sys_msgget(key_t key, int msgflg);
int sys_msgsend(int msqid, const void *msgp, size_t msgsz, int msgflg);
int sys_msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

int sys_log(const char* log, int size);

#endif
