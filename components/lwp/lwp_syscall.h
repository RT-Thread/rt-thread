/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Jesven       fix complie error in iar and keil
 */

#ifndef __LWP_SYSCALL_H__
#define __LWP_SYSCALL_H__

#include <stdint.h>
#include <rtthread.h>
#include <dfs_file.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>

typedef long suseconds_t;       /* microseconds (signed) */
typedef uint32_t id_t;          /* may contain pid, uid or gid */

/*
 * Process priority specifications to get/setpriority.
 */
#define PRIO_MIN        (-20)
#define PRIO_MAX        20

#define PRIO_PROCESS    0       /* only support lwp process */
#define PRIO_PGRP       1
#define PRIO_USER       2

#ifndef TIMEVAL_TO_TIMESPEC
#define TIMEVAL_TO_TIMESPEC(tv, ts) {                   \
    (ts)->tv_sec = (tv)->tv_sec;                        \
    (ts)->tv_nsec = (tv)->tv_usec * 1000;               \
}
#endif

#ifndef TIMESPEC_TO_TIMEVAL
#define TIMESPEC_TO_TIMEVAL(tv, ts) {                   \
    (tv)->tv_sec = (ts)->tv_sec;                        \
    (tv)->tv_usec = (ts)->tv_nsec / 1000;               \
}
#endif

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
