/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef DFS_POLL_H__
#define DFS_POLL_H__

#include <rtthread.h>

#ifdef RT_USING_POSIX
#include <sys/time.h> /* for struct timeval */

#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN          (0x01)
#define POLLRDNORM      (0x01)
#define POLLRDBAND      (0x01)
#define POLLPRI         (0x01)

#define POLLOUT         (0x02)
#define POLLWRNORM      (0x02)
#define POLLWRBAND      (0x02)

#define POLLERR         (0x04)
#define POLLHUP         (0x08)
#define POLLNVAL        (0x10)

typedef unsigned int nfds_t;

struct pollfd
{
    int fd;
    short events;
    short revents;
};
#endif /* !defined(POLLIN) && !defined(POLLOUT) */

#define POLLMASK_DEFAULT (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
#endif /* RT_USING_POSIX */

#endif /* DFS_POLL_H__ */
