/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-20   zmq810150896   first version
 * 2024-03-28   TroyMitchell   Add comments for all functions
 */

#include <rtthread.h>
#include <fcntl.h>
#include <rtdevice.h>
#include <stdint.h>
#include <unistd.h>
#include <dfs_file.h>
#include <dfs.h>
#include "poll.h"
#include "eventfd.h"

#define EFD_SEMAPHORE (1 << 0)
#define EFD_CLOEXEC O_CLOEXEC
#define EFD_NONBLOCK O_NONBLOCK

#define EFD_SHARED_FCNTL_FLAGS (O_CLOEXEC | O_NONBLOCK)
#define EFD_FLAGS_SET (EFD_SHARED_FCNTL_FLAGS | EFD_SEMAPHORE)

#define EFD_ULLONG_MAX  (~0ULL)

#define EVENTFD_MUTEX_NAME "eventfd"

struct eventfd_ctx
{
    rt_wqueue_t reader_queue;
    rt_wqueue_t writer_queue;
    rt_uint64_t count;
    unsigned int flags;
    struct rt_mutex lock;
};

#ifndef RT_USING_DFS_V2
static int eventfd_close(struct dfs_file *file);
static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req);
static ssize_t eventfd_read(struct dfs_file *file, void *buf, size_t count);
static ssize_t eventfd_write(struct dfs_file *file, const void *buf, size_t count);
#else
static int eventfd_close(struct dfs_file *file);
static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req);
static ssize_t eventfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
static ssize_t eventfd_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos);
#endif

static const struct dfs_file_ops eventfd_fops =
{
    .close      = eventfd_close,
    .poll       = eventfd_poll,
    .read       = eventfd_read,
    .write      = eventfd_write,
};

/**
 * @brief   Closes an event file descriptor.
 * @param   file Pointer to the file descriptor structure.
 * @return  0 on success, otherwise an error code.
 */
static int eventfd_close(struct dfs_file *file)
{
    struct eventfd_ctx *ctx = file->vnode->data;

    if (file->vnode->ref_count == 1)
    {
        rt_mutex_detach(&ctx->lock);
        rt_free(ctx);
    }

    return 0;
}

/**
 * @brief   Polls an event file descriptor for events.
 * @param   file Pointer to the file descriptor structure.
 * @param   req Pointer to the poll request structure.
 * @return  Events that occurred on the file descriptor.
 */
static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    int events = 0;
    rt_uint64_t count;

    count = ctx->count;

    rt_poll_add(&ctx->reader_queue, req);

    if (count > 0)
        events |= POLLIN;

    if (count == EFD_ULLONG_MAX)
        events |= POLLERR;

    if ((EFD_ULLONG_MAX - 1) > count)
        events |= POLLOUT;

    return events;
}

#ifndef RT_USING_DFS_V2
/**
 * @brief   Reads data from an event file descriptor.
 * @param   file Pointer to the file descriptor structure.
 * @param   buf Pointer to the buffer to read data into.
 * @param   count Maximum number of bytes to read.
 * @return  Number of bytes read on success, otherwise an error code.
 */
static ssize_t eventfd_read(struct dfs_file *file, void *buf, size_t count)
#else
/**
 * @brief   Reads data from an event file descriptor.
 * @param   file Pointer to the file descriptor structure.
 * @param   buf Pointer to the buffer to read data into.
 * @param   count Maximum number of bytes to read.
 * @param   pos Pointer to the file position (not used).
 * @return  Number of bytes read on success, otherwise an error code.
 */
static ssize_t eventfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
#endif
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    rt_uint64_t counter_num = 0;
    rt_uint64_t *buffer;

    if (count < sizeof(counter_num))
        return -EINVAL;

    buffer = (rt_uint64_t *)buf;

    rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);

    if (ctx->count <= 0)
    {
        if (file->flags & O_NONBLOCK)
        {
            rt_wqueue_wakeup(&ctx->writer_queue, (void*)POLLOUT);
            rt_mutex_release(&ctx->lock);
            return -EAGAIN;
        }
        else
        {
            /* In this case, when the data is read in blocked mode, when ctx->count is 0, the mutex needs to be released and wait for writing */
            rt_mutex_release(&ctx->lock);
            rt_wqueue_wakeup(&ctx->writer_queue, (void*)POLLOUT);
            rt_wqueue_wait(&ctx->reader_queue, 0, RT_WAITING_FOREVER);
            rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);
        }
    }

    if (ctx->flags & EFD_SEMAPHORE)
    {
        counter_num = 1;
    }
    else
    {
        counter_num = ctx->count;
    }

    ctx->count -= counter_num;
    (*buffer) = counter_num;

    rt_mutex_release(&ctx->lock);

    return sizeof(counter_num);
}

#ifndef RT_USING_DFS_V2
/**
 * @brief   Writes data to an event file descriptor.
 * @param   file Pointer to the file descriptor structure.
 * @param   buf Pointer to the buffer containing data to write.
 * @param   count Number of bytes to write.
 * @return  Number of bytes written on success, otherwise an error code.
 */
static ssize_t eventfd_write(struct dfs_file *file, const void *buf, size_t count)
#else
/**
 * @brief   Writes data to an event file descriptor.
 * @param   file Pointer to the file descriptor structure.
 * @param   buf Pointer to the buffer containing data to write.
 * @param   count Number of bytes to write.
 * @param   pos Pointer to the file position (not used).
 * @return  Number of bytes written on success, otherwise an error code.
 */
static ssize_t eventfd_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
#endif
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    rt_ssize_t ret = 0;

    rt_uint64_t counter_num;

    if (count < sizeof(counter_num))
        return -EINVAL;

    counter_num = *(rt_uint64_t *)buf;

    if (counter_num == EFD_ULLONG_MAX)
        return -EINVAL;

    ret = -EAGAIN;

    rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);

    if ((EFD_ULLONG_MAX - ctx->count) > counter_num)
    {
        ret = sizeof(counter_num);
    }
    else if (!(file->flags & O_NONBLOCK))
    {
        for (;;)
        {
            if ((EFD_ULLONG_MAX - ctx->count) >= counter_num)
            {
                ret = sizeof(counter_num);
                break;
            }
            /* Release the mutex to avoid a deadlock */
            rt_mutex_release(&ctx->lock);
            rt_wqueue_wait(&ctx->writer_queue, 0, RT_WAITING_FOREVER);
            rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);
        }
    }

    if (ret > 0)
    {
        ctx->count += counter_num;
        rt_wqueue_wakeup(&ctx->reader_queue, (void *)POLLIN);
    }

    rt_mutex_release(&ctx->lock);

    return ret;
}
/**
 * @brief   Creates an event file descriptor.
 * @param   df Pointer to the file descriptor structure.
 * @param   count Initial value of the event counter.
 * @param   flags Flags for the event file descriptor.
 * @return  0 on success, otherwise an error code.
 */
static int rt_eventfd_create(struct dfs_file *df, unsigned int count, int flags)
{
    struct eventfd_ctx *ctx = RT_NULL;
    rt_err_t ret = 0;

    ctx = (struct eventfd_ctx *)rt_malloc(sizeof(struct eventfd_ctx));
    if (ctx == RT_NULL)
    {
        ret = -ENOMEM;
    }
    else
    {
        ctx->count = count;
        ctx->flags = flags;
        flags &= EFD_SHARED_FCNTL_FLAGS;
        flags |= O_RDWR;

        rt_mutex_init(&ctx->lock, EVENTFD_MUTEX_NAME, RT_IPC_FLAG_FIFO);
        rt_wqueue_init(&ctx->reader_queue);
        rt_wqueue_init(&ctx->writer_queue);

        df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
        if (df->vnode)
        {
            dfs_vnode_init(df->vnode, FT_NONLOCK, &eventfd_fops);
            df->vnode->data = ctx;
            df->flags = flags;
        }
        else
        {
            rt_mutex_detach(&ctx->lock);
            rt_free(ctx);
            ret = -ENOMEM;
        }

        #ifdef RT_USING_DFS_V2
        df->fops = &eventfd_fops;
        #endif

    }

    return ret;
}

/**
 * @brief   Internal function to create an event file descriptor.
 * @param   count Initial value of the event counter.
 * @param   flags Flags for the event file descriptor.
 * @return  File descriptor on success, otherwise an error code.
 */
static int do_eventfd(unsigned int count, int flags)
{
    struct dfs_file *file;
    int fd;
    int status;
    rt_ssize_t ret = 0;

    if (flags & ~EFD_FLAGS_SET)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    fd = fd_new();
    if (fd >= 0)
    {
        ret = fd;
        file = fd_get(fd);

        status = rt_eventfd_create(file, count, flags);
        if (status < 0)
        {
            fd_release(fd);
            rt_set_errno(-status);
            ret = -1;
        }
    }
    else
    {
        rt_set_errno(-fd);
        ret = -1;
    }

    return ret;
}

/**
 * @brief   Creates an event file descriptor with the specified count and flags.
 * @param   count Initial value of the event counter.
 * @param   flags Flags for the event file descriptor.
 * @return  File descriptor on success, otherwise an error code.
 */
int eventfd(unsigned int count, int flags)
{
    return do_eventfd(count, flags);
}
