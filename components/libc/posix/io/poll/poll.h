/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-11     Meco Man     First version
 */

#ifndef __POLL_H__
#define __POLL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_MUSLLIBC
#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN     0x001
#define POLLPRI    0x002
#define POLLOUT    0x004
#define POLLERR    0x008
#define POLLHUP    0x010
#define POLLNVAL   0x020
#define POLLRDNORM 0x040
#define POLLRDBAND 0x080
#define POLLWRNORM 0x100
#define POLLWRBAND 0x200
typedef unsigned int nfds_t;
struct pollfd
{
    int fd;
    short events;
    short revents;
};
#endif
#else
#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN     0x1
#define POLLOUT    0x2
#define POLLERR    0x4
#define POLLNVAL   0x8
/* Below values are unimplemented */
#define POLLRDNORM 0x10
#define POLLRDBAND 0x20
#define POLLPRI    0x40
#define POLLWRNORM 0x80
#define POLLWRBAND 0x100
#define POLLHUP    0x200
typedef unsigned int nfds_t;
struct pollfd
{
    int fd;
    short events;
    short revents;
};
#endif
#endif /* !defined(POLLIN) && !defined(POLLOUT) */

#define POLLMASK_DEFAULT (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
}
#endif

#endif /* __POLL_H__ */
