/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-12-28     Bernard      first version
 * 2018-03-09     Bernard      Add protection for pt->triggered.
 * 2023-12-04     Shell        Fix return code and error verification
 * 2023-12-14     Shell        When poll goes to sleep before the waitqueue has added a
 *                             record and finished enumerating all the fd's, it may be
 *                             incorrectly woken up. This is basically because the poll
 *                             mechanism wakeup algorithm does not correctly distinguish
 *                             the current wait state.
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <dfs_file.h>
#include "poll.h"

struct rt_poll_node;
enum rt_poll_status {
    RT_POLL_STAT_INIT,
    RT_POLL_STAT_TRIG,
    RT_POLL_STAT_WAITING,
};

struct rt_poll_table
{
    rt_pollreq_t req;
    enum rt_poll_status status; /* the waited thread whether triggered */
    rt_thread_t polling_thread;
    struct rt_poll_node *nodes;
};

struct rt_poll_node
{
    struct rt_wqueue_node wqn;
    struct rt_poll_table *pt;
    struct rt_poll_node *next;
};

static RT_DEFINE_SPINLOCK(_spinlock);

static int __wqueue_pollwake(struct rt_wqueue_node *wait, void *key)
{
    rt_ubase_t level;
    struct rt_poll_node *pn;
    int is_waiting = 0;

    if (key && !((rt_ubase_t)key & wait->key))
        return -1;

    pn = rt_container_of(wait, struct rt_poll_node, wqn);

    level = rt_spin_lock_irqsave(&_spinlock);
    if (pn->pt->status == RT_POLL_STAT_WAITING)
        is_waiting = 1;

    pn->pt->status = RT_POLL_STAT_TRIG;
    rt_spin_unlock_irqrestore(&_spinlock, level);

    if (is_waiting)
        return __wqueue_default_wake(wait, key);

    return -1;
}

static void _poll_add(rt_wqueue_t *wq, rt_pollreq_t *req)
{
    struct rt_poll_table *pt;
    struct rt_poll_node *node;

    node = (struct rt_poll_node *)rt_malloc(sizeof(struct rt_poll_node));
    if (node == RT_NULL)
        return;

    pt = rt_container_of(req, struct rt_poll_table, req);

    node->wqn.key = req->_key;
    rt_list_init(&(node->wqn.list));
    node->wqn.polling_thread = pt->polling_thread;
    node->wqn.wakeup = __wqueue_pollwake;
    node->next = pt->nodes;
    node->pt = pt;
    pt->nodes = node;
    rt_wqueue_add(wq, &node->wqn);
}

static void poll_table_init(struct rt_poll_table *pt)
{
    pt->req._proc = _poll_add;
    pt->status = RT_POLL_STAT_INIT;
    pt->nodes = RT_NULL;
    pt->polling_thread = rt_thread_self();
}

static int poll_wait_timeout(struct rt_poll_table *pt, int msec)
{
    rt_int32_t timeout;
    int ret = 0;
    struct rt_thread *thread;
    rt_base_t level;

    thread = pt->polling_thread;

    timeout = rt_tick_from_millisecond(msec);

    level = rt_spin_lock_irqsave(&_spinlock);

    if (timeout != 0 && pt->status != RT_POLL_STAT_TRIG)
    {
        if (rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE) == RT_EOK)
        {
            if (timeout > 0)
            {
                rt_timer_control(&(thread->thread_timer),
                        RT_TIMER_CTRL_SET_TIME,
                        &timeout);
                rt_timer_start(&(thread->thread_timer));
                rt_set_errno(RT_ETIMEOUT);
            }
            else
            {
                rt_set_errno(0);
            }
            pt->status = RT_POLL_STAT_WAITING;
            rt_spin_unlock_irqrestore(&_spinlock, level);

            rt_schedule();

            level = rt_spin_lock_irqsave(&_spinlock);
            if (pt->status == RT_POLL_STAT_WAITING)
                pt->status = RT_POLL_STAT_INIT;
        }
    }

    ret = rt_get_errno();
    if (ret == RT_EINTR)
        ret = -RT_EINTR;
    else if (pt->status == RT_POLL_STAT_TRIG)
        ret = RT_EOK;
    else
        ret = -RT_ETIMEOUT;

    rt_spin_unlock_irqrestore(&_spinlock, level);

    return ret;
}

static int do_pollfd(struct pollfd *pollfd, rt_pollreq_t *req)
{
    int mask = 0;
    int fd;

    fd = pollfd->fd;

    if (fd >= 0)
    {
        struct dfs_file *f = fd_get(fd);
        mask = POLLNVAL;

        if (f)
        {
            mask = POLLMASK_DEFAULT;
            if (f->vnode->fops->poll)
            {
                req->_key = pollfd->events | POLLERR | POLLHUP;

                mask = f->vnode->fops->poll(f, req);

                /* dealwith the device return error -1*/
                if (mask < 0)
                {
                    pollfd->revents = 0;
                    return mask;
                }
            }
            /* Mask out unneeded events. */
            mask &= pollfd->events | POLLERR | POLLHUP;
        }
    }
    pollfd->revents = mask;

    return mask;
}

static int poll_do(struct pollfd *fds, nfds_t nfds, struct rt_poll_table *pt, int msec)
{
    int num;
    int istimeout = 0;
    nfds_t n;
    struct pollfd *pf;
    int  ret = 0;

    if (msec == 0)
    {
        pt->req._proc = RT_NULL;
        istimeout = 1;
    }

    while (1)
    {
        pf = fds;
        num = 0;
        pt->status = RT_POLL_STAT_INIT;

        for (n = 0; n < nfds; n ++)
        {
            ret = do_pollfd(pf, &pt->req);
            if(ret < 0)
            {
                /*dealwith the device return error -1  */
                pt->req._proc = RT_NULL;
                return ret;
            }
            else if(ret > 0)
            {
                num ++;
                pt->req._proc = RT_NULL;
            }
            pf ++;
        }

        pt->req._proc = RT_NULL;

        if (num || istimeout)
            break;

        ret = poll_wait_timeout(pt, msec);
        if (ret == -RT_EINTR)
            return -EINTR;
        else if (ret == -RT_ETIMEOUT)
            istimeout = 1;
        else
            istimeout = 0;
    }

    return num;
}

static void poll_teardown(struct rt_poll_table *pt)
{
    struct rt_poll_node *node, *next;

    next = pt->nodes;
    while (next)
    {
        node = next;
        rt_wqueue_remove(&node->wqn);
        next = node->next;
        rt_free(node);
    }
}

int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int num;
    struct rt_poll_table table;

    poll_table_init(&table);

    num = poll_do(fds, nfds, &table, timeout);

    poll_teardown(&table);

    return num;
}
