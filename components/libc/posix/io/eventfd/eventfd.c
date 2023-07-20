/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-20   zmq810150896   first version
 */

#include <rtthread.h>
#include <fcntl.h>
#include <rtdevice.h>
#include <dfs_file.h>
#include <resource_id.h>
#include <stdint.h>
#include <unistd.h>
#include "poll.h"
#include "eventfd.h"

#ifndef RT_USING_DFS_V2
static int eventfd_close(struct dfs_file *file);
static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req);
static int eventfd_read(struct dfs_file *file, void *buf, size_t count);
static int eventfd_write(struct dfs_file *file, const void *buf, size_t count);
static int noop_lseek(struct dfs_file *file, off_t offset);
#else
static int eventfd_close(struct dfs_file *file);
static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req);
static int eventfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
static int eventfd_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos);
static int noop_lseek(struct dfs_file *file, off_t offset, int wherece);
#endif

struct check_rt_unamed_event_number
{
    char _check[RT_NAME_MAX - 4 - 1 - BITS(RT_UNAMED_PIPE_NUMBER)];
};

static void *resoure_id[RT_UNAMED_PIPE_NUMBER];
static resource_id_t id_mgr = RESOURCE_ID_INIT(RT_UNAMED_PIPE_NUMBER, resoure_id);

static const struct dfs_file_ops eventfd_fops =
{
    .close      = eventfd_close,
    .poll       = eventfd_poll,
    .read       = eventfd_read,
    .write      = eventfd_write,
    .lseek      = noop_lseek,
};

void eventfd_ctx_do_read(struct eventfd_ctx *ctx, rt_u64 *cnt)
{
    *cnt = (ctx->flags & EFD_SEMAPHORE) ? 1 : ctx->count;
    ctx->count -= *cnt;
}

static int eventfd_close(struct dfs_file *file)
{
    struct eventfd_ctx *ctx = file->data;
    free(ctx);
    return 0;
}

static int eventfd_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    rt_poll_add(&ctx->reader_queue, req);
    rt_poll_add(&ctx->writer_queue, req);

    int events = 0;
    rt_u64 count;
    count = ctx->count;

    if (count > 0)
        events |= POLLIN;

    if (count == ULLONG_MAX)
        events |= POLLERR;

    if (ULLONG_MAX -1 > count)
        events |= POLLOUT;

    return events;
}

#ifndef RT_USING_DFS_V2
static int eventfd_read(struct dfs_file *file, void *buf, size_t count)
#else
static int eventfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
#endif
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    rt_u64 ucnt = 0;

    rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);

    if(ctx->count == 0)
    {
        if (file->flags & O_NONBLOCK)
        {
            rt_mutex_release(&ctx->lock);
            return -EAGAIN;
        }
        rt_mutex_release(&ctx->lock);
        rt_wqueue_wakeup(&ctx->writer_queue, (void*)POLLOUT);
        rt_wqueue_wait(&ctx->reader_queue, 0, RT_WAITING_FOREVER);
        rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);
    }

    eventfd_ctx_do_read(ctx, &ucnt);
    rt_mutex_release(&ctx->lock);

    return sizeof(ucnt);
}

#ifndef RT_USING_DFS_V2
static int eventfd_write(struct dfs_file *file, const void *buf, size_t count)
#else
static int eventfd_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
#endif
{
    struct eventfd_ctx *ctx = (struct eventfd_ctx *)file->vnode->data;
    rt_ssize_t res;
    rt_u64 ucnt = *(rt_u64 *)buf;

    if (count < sizeof(ucnt))
        return -EINVAL;

    if (ucnt == ULLONG_MAX)
        return -EINVAL;

    res = -EAGAIN;
    rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);
    if ((ULLONG_MAX - ctx->count) > ucnt)
        res = sizeof(ucnt);
    else if (!(file->flags & O_NONBLOCK))
    {

        for (res = 0;;)
        {
            // status fun
            if ((ULLONG_MAX - ctx->count) >= ucnt)
            {
                res = sizeof(ucnt);
                break;
            }
            rt_mutex_release(&ctx->lock);
            rt_wqueue_wait(&ctx->writer_queue, 0, RT_WAITING_FOREVER);
            rt_wqueue_wakeup(&ctx->reader_queue, (void *)POLLIN);
            rt_mutex_take(&ctx->lock, RT_WAITING_FOREVER);
        }
    }

    if (res > 0)
    {
        rt_kprintf("%u \n", ucnt);
        ctx->count += ucnt;
        rt_wqueue_wakeup(&ctx->reader_queue, (void *)POLLIN);
    }

    rt_mutex_release(&ctx->lock);

    return res;
}

#ifndef RT_USING_DFS_V2
static int noop_lseek(struct dfs_file *file, off_t offset)
#else
static int noop_lseek(struct dfs_file *file, off_t offset, int wherece)
#endif
{
    #ifndef RT_USING_DFS_V2
    return file->pos;
    #else
    return file->fpos;
    #endif
}

static int rt_eventfd_create(struct dfs_file *df,const char *name, unsigned int count, int flags)
{
    struct eventfd_ctx *ctx = RT_NULL;

    ctx = (struct eventfd_ctx *)rt_malloc(sizeof(struct eventfd_ctx));
    if (ctx == RT_NULL)
        return -ENOMEM;

    ctx->count = count;
    ctx->flags = flags;
    ctx->id = rt_thread_self();
    flags &= EFD_SHARED_FCNTL_FLAGS;
    flags |= O_RDWR;

    rt_mutex_init(&ctx->lock, name, RT_IPC_FLAG_FIFO);
    rt_wqueue_init(&ctx->reader_queue);
    rt_wqueue_init(&ctx->writer_queue);

    df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
    if (!df->vnode)
    {
        free(ctx);
        return -ENOMEM;
    }

    dfs_vnode_init(df->vnode, FT_REGULAR, &eventfd_fops);
    df->vnode->data = ctx;

    df->flags = flags;

    return 0;
}

static int do_eventfd(unsigned int count, int flags)
{
    struct dfs_file *file;
    char dname[8];
    int fd;
    int eventno = 0;
    int status;

    if (flags & ~EFD_FLAGS_SET)
        return -RT_EINVAL;

    fd = fd_new();
    if (fd < 0)
    {
        return fd;
    }

    file = fd_get(fd);

    eventno = resource_id_get(&id_mgr);
    rt_snprintf(dname, sizeof(dname), "eventfd%d", eventno);

    status = rt_eventfd_create(file, dname, count, flags);
    if (status < 0)
    {
        fd_release(fd);
        return status;
    }

    return fd;
}

int eventfd(unsigned int count)
{
    return do_eventfd(count, 0);
}

int eventfd2(unsigned int count, int flags)
{
    return do_eventfd(count, flags);
}
