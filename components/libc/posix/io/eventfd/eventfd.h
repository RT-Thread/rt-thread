/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-20    zmq810150896  First version
 */

#ifndef __EVENTFD_H__
#define __EVENTFD_H__

#include <rtthread.h>
#include <rthw.h>
#include <dfs_file.h>

#define EFD_SEMAPHORE (1 << 0)
#define EFD_CLOEXEC O_CLOEXEC
#define EFD_NONBLOCK O_NONBLOCK

#define EFD_SHARED_FCNTL_FLAGS (O_CLOEXEC | O_NONBLOCK)
#define EFD_FLAGS_SET (EFD_SHARED_FCNTL_FLAGS | EFD_SEMAPHORE)

#define ULLONG_MAX  (~0ULL)

#define EVENTFD_MUTEX_NAME "eventfd"

struct eventfd_ctx {
    rt_wqueue_t reader_queue;
    rt_wqueue_t writer_queue;
    rt_uint64_t count;
    unsigned int flags;
    struct rt_mutex lock;
    rt_thread_t id;
};

int eventfd(unsigned int count);
int eventfd2(unsigned int count, int flags);

#endif /* __EVENTFD_H__ */
