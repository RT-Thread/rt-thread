/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

#define DBG_TAG    "TIMERFD"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

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
    rt_atomic_t timeout_num;
    struct rt_wqueue_node wqn;
    rt_atomic_t ticks;
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

        if (tfd->wqn.wqueue)
        {
            rt_wqueue_remove(&tfd->wqn);
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

    rt_mutex_release(&tfd->lock);

    if (rt_atomic_load(&(tfd->ticks)) > 0)
    {
        events |= POLLIN;
    }

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
    int ret = 0;

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

    if ((rt_atomic_load(&(tfd->ticks)) == 0) && (file->flags & O_NONBLOCK))
    {
        rt_set_errno(EAGAIN);
        return -EAGAIN;
    }
    else
    {
        if (rt_atomic_load(&(tfd->ticks)) == 0)
        {
            tfd->wqn.polling_thread = rt_thread_self();

            if (tfd->wqn.wqueue)
            {
                rt_wqueue_remove(&tfd->wqn);
            }
            rt_wqueue_add(&tfd->timerfd_queue, &tfd->wqn);

            ret = rt_thread_suspend_with_flag(tfd->wqn.polling_thread, RT_INTERRUPTIBLE);
            if (ret == RT_EOK)
            {
                rt_schedule();
            }
            else
            {
                return ret;
            }
        }

        (*buffer) = rt_atomic_load(&(tfd->timeout_num));
        rt_atomic_store(&(tfd->timeout_num), 0);
        rt_atomic_store(&(tfd->ticks), 0);
    }

    return sizeof(buffer);
}

static int timerfd_wqueue_callback(struct rt_wqueue_node *wait, void *key)
{
    return 0;
}

static int timerfd_do_create(int clockid, int flags)
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

        tfd = (struct rt_timerfd *)rt_calloc(1, sizeof(struct rt_timerfd));

        if (tfd)
        {
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
            tfd->wqn.polling_thread = rt_thread_self();
            rt_list_init(&(tfd->wqn.list));
            tfd->wqn.wakeup = timerfd_wqueue_callback;

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

    rt_atomic_store(&(tfd->ticks), 1);
    rt_atomic_add(&(tfd->timeout_num), 1);

    rt_mutex_take(&tfd->lock, RT_WAITING_FOREVER);

    get_current_time(tfd, RT_NULL);
    if (tfd->isperiodic == OPEN_PERIODIC)
    {
        if (tfd->timer)
        {
            rt_timer_stop(tfd->timer);
            rt_timer_delete(tfd->timer);
            tfd->timer = RT_NULL;
        }
        tfd->isperiodic = ENTER_PERIODIC;
        tfd->timer = rt_timer_create(TIMERFD_MUTEX_NAME, timerfd_timeout,
                        tfd, tfd->tick_out,
                        RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

        if (tfd->timer == RT_NULL)
        {
            LOG_E("rt_timer_create fail \n");
            rt_mutex_release(&tfd->lock);
            return ;
        }
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

    if (*sec < 0 || *nsec < 0)
    {
        *sec = 0;
        *nsec = 0;
    }
}

static int timerfd_do_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
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

    rt_atomic_store(&(tfd->ticks), 0);
    rt_atomic_store(&(tfd->timeout_num), 0);

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
        if (tfd->timer != RT_NULL)
        {
            rt_timer_stop(tfd->timer);
            rt_timer_delete(tfd->timer);
            tfd->timer = RT_NULL;
        }

        if (new->it_value.tv_nsec == 0 && new->it_value.tv_sec == 0)
        {
            rt_mutex_release(&tfd->lock);
            return 0;
        }

        value_msec = (new->it_value.tv_nsec / MSEC_TO_NSEC) + (new->it_value.tv_sec * SEC_TO_MSEC);
        interval_msec = (new->it_interval.tv_nsec / MSEC_TO_NSEC) + (new->it_interval.tv_sec * SEC_TO_MSEC);

        current_time.tv_nsec = 0;
        current_time.tv_sec = 0;

        if (flags == TFD_TIMER_ABSTIME)
        {
            ret = get_current_time(tfd, &current_time);

            if (ret < 0)
            {
                rt_mutex_release(&tfd->lock);
                return ret;
            }

            cur_time = current_time.tv_sec * SEC_TO_MSEC + (current_time.tv_nsec / MSEC_TO_NSEC);
            value_msec = value_msec - cur_time;
        }

        tfd->ittimer.it_interval.tv_nsec = new->it_interval.tv_nsec;
        tfd->ittimer.it_interval.tv_sec = new->it_interval.tv_sec;
        tfd->ittimer.it_value.tv_sec = new->it_value.tv_sec - current_time.tv_sec;
        tfd->ittimer.it_value.tv_nsec = new->it_value.tv_nsec - current_time.tv_nsec;
        timerfd_time_operation(&tfd->ittimer.it_value.tv_sec, &tfd->ittimer.it_value.tv_nsec);

        if ((interval_msec > 0) && (interval_msec <= TIME_INT32_MAX))
        {
            tfd->tick_out = rt_tick_from_millisecond(interval_msec);
            if (tfd->tick_out < 0)
            {
                rt_mutex_release(&tfd->lock);
                return -EINVAL;
            }
            tfd->isperiodic = OPEN_PERIODIC;
        }

        get_current_time(tfd, RT_NULL);

        if (value_msec > 0)
        {
            if (value_msec > TIME_INT32_MAX)
            {
                rt_mutex_release(&tfd->lock);
                return -EINVAL;
            }

            tick_out = rt_tick_from_millisecond(value_msec);
            if (tick_out < 0)
            {
                rt_mutex_release(&tfd->lock);
                return -EINVAL;
            }
            tfd->timer = rt_timer_create(TIMERFD_MUTEX_NAME, timerfd_timeout,
                            tfd, tick_out,
                            RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
            if (tfd->timer == RT_NULL)
            {
                LOG_E("rt_timer_create fail \n");
                rt_mutex_release(&tfd->lock);
                return -ENOMEM;
            }
            rt_timer_start(tfd->timer);
        }
        else
        {
            timerfd_timeout(tfd);
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

static int timerfd_do_gettime(int fd, struct itimerspec *cur)
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
        timerfd_time_operation(&cur->it_value.tv_sec, &cur->it_value.tv_nsec);
    }
    else
    {
        if (rt_atomic_load(&(tfd->timeout_num)) == 1)
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

/**
 * @brief Creates a file descriptor for a timer.
 *
 * The `timerfd_create` function creates a new timer object that generates
 * timer expiration notifications via a file descriptor.
 *
 * @param clockid The clock ID that specifies the clock to be used as the
 *                timing base for the timer. Common values include:
 *                - `CLOCK_REALTIME`: A system-wide clock representing
 *                  wall-clock time.
 *                - `CLOCK_MONOTONIC`: A clock that cannot be set and
 *                  represents monotonic time since some unspecified
 *                  starting point.
 * @param flags   A bitmask that can include the following flags:
 *                - `TFD_CLOEXEC`: Close the file descriptor on `execve`.
 *                - `TFD_NONBLOCK`: Set the file descriptor to non-blocking mode.
 *
 * @return On success, returns a file descriptor for the timer. On error,
 *         returns -1 and sets `errno` appropriately.
 *
 * @note The file descriptor can be used with select, poll, or epoll to wait
 *       for timer expirations.
 *
 * @warning The timerfd interface is Linux-specific and may not be available
 *          on other operating systems.
 *
 * @see timerfd_settime, timerfd_gettime
 */
int timerfd_create(int clockid, int flags)
{
    return timerfd_do_create(clockid, flags);
}

/**
 * @brief Sets the time for a timer file descriptor.
 *
 * The `timerfd_settime` function starts or modifies the timer associated
 * with the specified timer file descriptor.
 *
 * @param fd      The file descriptor of the timer, obtained from
 *                `timerfd_create`.
 * @param flags   Flags that control the behavior of the timer. Possible
 *                values include:
 *                - `0`: Relative time is specified in `new`.
 *                - `TFD_TIMER_ABSTIME`: Use absolute time instead of
 *                  relative time.
 * @param new     A pointer to a `itimerspec` structure that specifies the
 *                new timer settings:
 *                - `it_value`: The initial expiration time. A zero value
 *                  means the timer is disabled.
 *                - `it_interval`: The interval for periodic timers. A zero
 *                  value means the timer is not periodic.
 * @param old     A pointer to a `itimerspec` structure to store the
 *                previous timer settings. Can be `NULL` if this information
 *                is not needed.
 *
 * @return On success, returns 0. On error, returns -1 and sets `errno`
 *         appropriately.
 *
 * @note The timer starts counting down immediately after this call if
 *       `it_value` is non-zero.
 *
 * @warning If the timer is set to a very short interval, high-frequency
 *          events may impact system performance.
 *
 * @see timerfd_create, timerfd_gettime
 */
int timerfd_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
    return timerfd_do_settime(fd, flags, new, old);
}

/**
 * @brief Retrieves the current value and interval of a timer.
 *
 * The `timerfd_gettime` function queries the settings of the timer associated
 * with the specified timer file descriptor.
 *
 * @param fd   The file descriptor of the timer, obtained from `timerfd_create`.
 * @param cur  A pointer to a `itimerspec` structure where the current timer
 *             settings will be stored:
 *             - `it_value`: The time remaining until the next expiration.
 *               If zero, the timer is disabled.
 *             - `it_interval`: The interval for periodic timers. Zero if the
 *               timer is not periodic.
 *
 * @return On success, returns 0. On error, returns -1 and sets `errno`
 *         appropriately.
 *
 * @note This function does not reset or modify the timer; it only retrieves
 *       the current settings.
 *
 * @see timerfd_create, timerfd_settime
 */
int timerfd_gettime(int fd, struct itimerspec *cur)
{
    return timerfd_do_gettime(fd, cur);
}
