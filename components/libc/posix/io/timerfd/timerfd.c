/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-20   zmq810150896   first version
 */

#include <rtthread.h>
#include <dfs_file.h>
#include <stdint.h>
#include <poll.h>
#include <sys/timerfd.h>

#define INIT_PERIODIC 0
#define OPEN_PERIODIC 1
#define ENTER_PERIODIC 2

#define SEC_TO_MSEC 1000
#define MSEC_TO_NSEC 1000000
#define SEC_TO_NSEC 1000000000

#define TIME_INT32_MAX   0x7FFFFFFF

#define TIMERFD_MUTEX_NAME "TIMERFD"

#define TFD_SHARED_FCNTL_FLAGS (TFD_CLOEXEC | TFD_NONBLOCK)

struct rt_timerfd
{
    rt_wqueue_t timerfd_queue;
    struct itimerspec ittimer;
    rt_timer_t timer;
    struct rt_mutex lock;
    struct timespec pre_time;
    rt_uint64_t timeout_num;
    int ticks;
    int clockid;
    int isperiodic;
    int tick_out;
};

static int timerfd_close(struct dfs_file *file);
static int timerfd_poll(struct dfs_file *file, struct rt_pollreq *req);
#ifndef RT_USING_DFS_V2
static ssize_t timerfd_read(struct dfs_file *file, void *buf, size_t count);
#else
static ssize_t timerfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
#endif

static const struct dfs_file_ops timerfd_fops =
{
    .close      = timerfd_close,
    .poll       = timerfd_poll,
    .read       = timerfd_read,
};

static int timerfd_close(struct dfs_file *file)
{
    struct rt_timerfd *tfd;

    if (file->vnode->ref_count != 1)
        return 0;

    tfd = file->vnode->data;

    if (tfd)
    {
        if (tfd->timer != RT_NULL)
        {
            rt_timer_stop(tfd->timer);
            rt_timer_delete(tfd->timer);
            tfd->timer = RT_NULL;
        }

        rt_mutex_detach(&tfd->lock);
        rt_free(tfd);
    }

    return 0;
}

static int timerfd_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct rt_timerfd *tfd;
    int events = 0;

    tfd = file->vnode->data;

    rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);

    rt_poll_add(&tfd->timerfd_queue, req);

    if (tfd->ticks)
        events |= POLLIN;

    rt_mutex_release(&tfd->lock);

    return events;
}

#ifndef RT_USING_DFS_V2
static ssize_t timerfd_read(struct dfs_file *file, void *buf, size_t count)
#else
static ssize_t timerfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
#endif
{
    struct rt_timerfd *tfd;
    rt_uint64_t *buffer;

    buffer = (rt_uint64_t *)buf;

    if (sizeof(buffer) > count)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    tfd = file->vnode->data;

    if (!tfd)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if ((tfd->ticks == 0) && (file->flags & O_NONBLOCK))
    {
        rt_set_errno(EAGAIN);
        return -EAGAIN;
    }
    else
    {
        if (tfd->ticks == 0)
        {
            rt_wqueue_wait(&tfd->timerfd_queue, 0, RT_WAITING_FOREVER);
        }

        rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);
        (*buffer) = tfd->timeout_num;
        rt_mutex_release(&tfd->lock);
    }

    tfd->ticks = 0;

    return sizeof(buffer);
}

static int timerfd_create_do(int clockid, int flags)
{
    struct rt_timerfd *tfd = RT_NULL;
    struct dfs_file *df;
    rt_err_t ret = -1;
    int fd = -1;

    if ((flags & ~TFD_SHARED_FCNTL_FLAGS) ||
        (clockid != CLOCK_MONOTONIC &&
         clockid != CLOCK_REALTIME &&
         clockid != CLOCK_REALTIME_ALARM &&
         clockid != CLOCK_BOOTTIME &&
         clockid != CLOCK_BOOTTIME_ALARM))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if ((clockid == CLOCK_REALTIME_ALARM ||
         clockid == CLOCK_BOOTTIME_ALARM))
    {
        rt_set_errno(EPERM);
        return -1;
    }

    fd = fd_new();
    if (fd < 0)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    ret = fd;
    df = fd_get(fd);

    if (df)
    {
        df->flags |= flags;

        tfd = (struct rt_timerfd *)rt_malloc(sizeof(struct rt_timerfd));

        rt_mutex_init(&tfd->lock, TIMERFD_MUTEX_NAME, RT_IPC_FLAG_FIFO);
        rt_wqueue_init(&tfd->timerfd_queue);

        tfd->isperiodic = INIT_PERIODIC;
        tfd->ticks = 0;
        tfd->timeout_num = 0;
        tfd->tick_out = 0;
        tfd->clockid = clockid;
        tfd->timer = RT_NULL;
        tfd->pre_time.tv_sec = 0;
        tfd->pre_time.tv_nsec = 0;

        if (tfd)
        {
            df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
            if (df->vnode)
            {
                dfs_vnode_init(df->vnode, FT_REGULAR, &timerfd_fops);
                df->vnode->data = tfd;

                #ifdef RT_USING_DFS_V2
                df->fops = &timerfd_fops;
                #endif
            }
            else
            {
                rt_free(tfd);
                fd_release(fd);
                rt_set_errno(ENOMEM);
                ret = -1;
            }
        }
        else
        {
            fd_release(fd);
            rt_set_errno(ENOMEM);
            ret = -1;
        }
    }
    else
    {
        fd_release(fd);
        ret = -1;
    }

    return ret;
}

static int get_current_time(struct rt_timerfd *tfd, struct timespec *time)
{
    int ret = 0;
    struct timespec *cur_time = RT_NULL;

    if (time == RT_NULL)
    {
        cur_time = &tfd->pre_time;
    }
    else
    {
        cur_time = time;
    }

    if (tfd->clockid >= 0)
    {
        ret = clock_gettime(tfd->clockid, cur_time);
    }
    else
    {
        ret = clock_gettime(CLOCK_MONOTONIC, cur_time);
    }

    return ret;
}

static void timerfd_timeout(void *parameter)
{
    struct rt_timerfd *tfd = RT_NULL;

    tfd = (struct rt_timerfd *)parameter;

    if (tfd == RT_NULL)
    {
        return ;
    }

    rt_wqueue_wakeup(&tfd->timerfd_queue, (void *)POLLIN);

    rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);

    tfd->ticks = 1;
    tfd->timeout_num ++;

    get_current_time(tfd, RT_NULL);
    if (tfd->isperiodic == OPEN_PERIODIC)
    {
        rt_timer_stop(tfd->timer);
        rt_timer_delete(tfd->timer);
        tfd->timer = RT_NULL;
        tfd->isperiodic = ENTER_PERIODIC;
        tfd->timer = rt_timer_create(TIMERFD_MUTEX_NAME, timerfd_timeout,
                        tfd, tfd->tick_out,
                        RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
        rt_timer_start(tfd->timer);
    }

    rt_mutex_release(&tfd->lock);
}

static void timerfd_time_operation(time_t *sec, long *nsec)
{
    if (*nsec < 0)
    {
        if (*sec > 0)
        {
            *sec -= 1;
            *nsec = 1 * SEC_TO_NSEC + *nsec;
        }
    }
}

static int timerfd_settime_do(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
    int ret = 0;
    struct rt_timerfd *tfd;
    struct dfs_file *df;
    struct timespec current_time;
    int tick_out;
    rt_int64_t value_msec;
    rt_int64_t interval_msec;
    rt_int64_t cur_time = 0;

    if (fd < 0)
    {
        rt_set_errno(EINVAL);
        return -EINVAL;
    }

    df = fd_get(fd);
    if (!df)
        return -EINVAL;

    tfd = df->vnode->data;
    tfd->timeout_num = 0;

    rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);
    tfd->isperiodic = INIT_PERIODIC;

    if (old)
    {
        old->it_interval.tv_nsec = tfd->ittimer.it_interval.tv_nsec;
        old->it_interval.tv_sec = tfd->ittimer.it_interval.tv_sec;
        old->it_value.tv_nsec = tfd->ittimer.it_value.tv_nsec;
        old->it_value.tv_sec = tfd->ittimer.it_value.tv_sec;
    }

    if (new)
    {
        value_msec = (new->it_value.tv_nsec / MSEC_TO_NSEC) + (new->it_value.tv_sec * SEC_TO_MSEC);
        interval_msec = (new->it_interval.tv_nsec / MSEC_TO_NSEC) + (new->it_interval.tv_sec * SEC_TO_MSEC);

        current_time.tv_nsec = 0;
        current_time.tv_sec = 0;

        if (flags == TFD_TIMER_ABSTIME)
        {
            ret = get_current_time(tfd, &current_time);

            if (ret < 0)
                return ret;

            cur_time = current_time.tv_sec * SEC_TO_MSEC + (current_time.tv_nsec / MSEC_TO_NSEC);
            value_msec = value_msec - cur_time;
        }

        tfd->ittimer.it_interval.tv_nsec = new->it_interval.tv_nsec;
        tfd->ittimer.it_interval.tv_sec = new->it_interval.tv_sec;
        tfd->ittimer.it_value.tv_sec = new->it_value.tv_sec - current_time.tv_sec;
        tfd->ittimer.it_value.tv_nsec = new->it_value.tv_nsec - current_time.tv_nsec;
        timerfd_time_operation(&tfd->ittimer.it_value.tv_sec, &tfd->ittimer.it_value.tv_nsec);

        if (tfd->timer != RT_NULL)
        {
            rt_timer_stop(tfd->timer);
            rt_timer_delete(tfd->timer);
            tfd->timer = RT_NULL;
        }

        if (value_msec > 0)
        {
            if (value_msec > TIME_INT32_MAX)
                return -EINVAL;

            tick_out = rt_tick_from_millisecond(value_msec);
            if (tick_out < 0)
                return -EINVAL;

            if ((interval_msec > 0) && (interval_msec <= TIME_INT32_MAX))
            {
                tfd->tick_out = rt_tick_from_millisecond(interval_msec);
                if (tfd->tick_out < 0)
                    return -EINVAL;
                tfd->isperiodic = OPEN_PERIODIC;
            }

            get_current_time(tfd, RT_NULL);
            tfd->timer = rt_timer_create(TIMERFD_MUTEX_NAME, timerfd_timeout,
                            tfd, tick_out,
                            RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
             rt_timer_start(tfd->timer);
        }
    }
    else
    {
        rt_set_errno(EINVAL);
        ret = -1;
    }

    rt_mutex_release(&tfd->lock);

    return ret;
}

static int timerfd_gettime_do(int fd, struct itimerspec *cur)
{
    struct rt_timerfd *tfd;
    struct dfs_file *df = RT_NULL;
    struct timespec cur_time;
    rt_int64_t tv_sec = 0;
    rt_int64_t tv_nsec = 0;

    df = fd_get(fd);

    if (df == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    tfd = df->vnode->data;

    get_current_time(tfd, &cur_time);

    rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);

    tv_sec = cur_time.tv_sec - tfd->pre_time.tv_sec;
    tv_nsec = cur_time.tv_nsec - tfd->pre_time.tv_nsec;
    timerfd_time_operation(&tv_sec, &tv_nsec);
    cur->it_interval.tv_nsec = tfd->ittimer.it_interval.tv_nsec;
    cur->it_interval.tv_sec = tfd->ittimer.it_interval.tv_sec;

    if (tfd->isperiodic == ENTER_PERIODIC)
    {
        cur->it_value.tv_nsec = tfd->ittimer.it_interval.tv_nsec - tv_nsec;
        cur->it_value.tv_sec = tfd->ittimer.it_interval.tv_sec - tv_sec;
    }
    else
    {
        if (tfd->timeout_num == 1)
        {
            cur->it_value.tv_nsec = 0;
            cur->it_value.tv_sec = 0;
        }
        else
        {
            cur->it_value.tv_nsec = tfd->ittimer.it_value.tv_nsec - tv_nsec;
            cur->it_value.tv_sec = tfd->ittimer.it_value.tv_sec - tv_sec;
            timerfd_time_operation(&cur->it_value.tv_sec, &cur->it_value.tv_nsec);
        }
    }

    rt_mutex_release(&tfd->lock);

    return 0;
}

int timerfd_create(int clockid, int flags)
{
    return timerfd_create_do(clockid, flags);
}

int timerfd_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
    return timerfd_settime_do(fd, flags, new, old);
}

int timerfd_gettime(int fd, struct itimerspec *cur)
{
    return timerfd_gettime_do(fd, cur);
}
