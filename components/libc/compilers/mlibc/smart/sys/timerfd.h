/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/8/8   0Bitbiscuits the first version
 */
#ifndef MLIBC_SYS_TIMERFD_H__
#define MLIBC_SYS_TIMERFD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <fcntl.h>

#define TFD_NONBLOCK            O_NONBLOCK
#define TFD_CLOEXEC             O_CLOEXEC

#define TFD_TIMER_ABSTIME       1
#define TFD_TIMER_CANCEL_ON_SET (1 << 1)

int timerfd_create(int, int);
int timerfd_settime(int, int, const struct itimerspec *, struct itimerspec *);
int timerfd_gettime(int, struct itimerspec *);

#ifdef __cplusplus
}
#endif

#endif /* MLIBC_SYS_TIMERFD_H__ */
