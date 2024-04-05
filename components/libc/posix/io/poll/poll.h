/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-11     Meco Man          First version
 * 2024-03-29     TroyMitchelle     Add all macro comments and comments to structure members
 */

#ifndef __POLL_H__
#define __POLL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_MUSLLIBC
#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN     0x001   /**< There is data to read. */
#define POLLPRI    0x002   /**< There is urgent data to read. */
#define POLLOUT    0x004   /**< Writing is now possible. */
#define POLLERR    0x008   /**< Error condition. */
#define POLLHUP    0x010   /**< Hang up. */
#define POLLNVAL   0x020   /**< Invalid polling request. */
#define POLLRDNORM 0x040   /**< Normal data may be read. */
#define POLLRDBAND 0x080   /**< Priority data may be read. */
#define POLLWRNORM 0x100   /**< Writing normal data is possible. */
#define POLLWRBAND 0x200   /**< Writing priority data is possible. */
typedef unsigned int nfds_t;
struct pollfd
{
    int fd;             /**< File descriptor. */
    short events;       /**< Requested events. */
    short revents;      /**< Returned events. */
};
#endif
#else
#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN     0x1     /**< There is data to read. */
#define POLLOUT    0x2     /**< Writing is now possible. */
#define POLLERR    0x4     /**< Error condition. */
#define POLLNVAL   0x8     /**< Invalid polling request. */
/* Below values are unimplemented */
#define POLLRDNORM 0x10    /**< Normal data may be read. */
#define POLLRDBAND 0x20    /**< Priority data may be read. */
#define POLLPRI    0x40    /**< There is urgent data to read. */
#define POLLWRNORM 0x80    /**< Writing normal data is possible. */
#define POLLWRBAND 0x100   /**< Writing priority data is possible. */
#define POLLHUP    0x200   /**< Hang up. */
typedef unsigned int nfds_t;
struct pollfd
{
    int fd;             /**< File descriptor. */
    short events;       /**< Requested events. */
    short revents;      /**< Returned events. */
};
#endif
#endif /* !defined(POLLIN) && !defined(POLLOUT) */

#define POLLMASK_DEFAULT (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
}
#endif

#endif /* __POLL_H__ */
