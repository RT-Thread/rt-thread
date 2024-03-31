/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2016-12-28     Bernard           first version
 * 2018-03-09     Bernard           Add protection for pt->triggered.
 * 2023-12-04     Shell             Fix return code and error verification
 * 2023-12-14     Shell             When poll goes to sleep before the waitqueue has added a
 *                                  record and finished enumerating all the fd's, it may be
 *                                  incorrectly woken up. This is basically because the poll
 *                                  mechanism wakeup algorithm does not correctly distinguish
 *                                  the current wait state.
 * 2024-03-29     TroyMitchelle     Add all function comments and comments to structure members
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <dfs_file.h>
#include "poll.h"


enum rt_poll_status 
{
    RT_POLL_STAT_INIT,     /**< Poll operation initialization status. */
    RT_POLL_STAT_TRIG,     /**< Poll operation triggered status. */
    RT_POLL_STAT_WAITING   /**< Poll operation waiting status. */
};


struct rt_poll_table 
{
    rt_pollreq_t req;               /**< Poll request. */
    enum rt_poll_status status;     /**< Status of the poll operation. */
    rt_thread_t polling_thread;     /**< Polling thread associated with the table. */
    struct rt_poll_node *nodes;     /**< Linked list of poll nodes. */
};


struct rt_poll_node 
{
    struct rt_wqueue_node wqn;     /**< Wait queue node for the poll node. */
    struct rt_poll_table *pt;       /**< Pointer to the parent poll table. */
    struct rt_poll_node *next;      /**< Pointer to the next poll node. */
};

static RT_DEFINE_SPINLOCK(_spinlock);

/**
 * @brief   Wake-up function for the wait queue.
 *
 * This function is invoked when a node in the wait queue needs to be woken up.
 *
 * @param   wait    Pointer to the wait queue node.
 * @param   key     Key associated with the wake-up operation.
 * @return  Upon successful wake-up, returns 0; otherwise, -1 is returned.
 */
static int __wqueue_pollwake(struct rt_wqueue_node *wait, void *key)
{
    rt_ubase_t level;
    struct rt_poll_node *pn;
    int is_waiting;

    if (key && !((rt_ubase_t)key & wait->key))
        return -1;

    pn = rt_container_of(wait, struct rt_poll_node, wqn);

    level = rt_spin_lock_irqsave(&_spinlock);
    is_waiting = (pn->pt->status == RT_POLL_STAT_WAITING);

    pn->pt->status = RT_POLL_STAT_TRIG;
    rt_spin_unlock_irqrestore(&_spinlock, level);

    if (is_waiting)
        return __wqueue_default_wake(wait, key);

    return -1;
}

/**
 * @brief   Adds a poll request to the wait queue.
 *
 * This function adds a poll request to the wait queue associated with the specified
 * wait queue and poll request.
 *
 * @param   wq      Pointer to the wait queue.
 * @param   req     Pointer to the poll request.
 */
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

/**
 * @brief   Initializes a poll table.
 *
 * This function initializes a poll table with the provided poll request, status,
 * and polling thread.
 *
 * @param   pt  Pointer to the poll table to be initialized.
 */
static void poll_table_init(struct rt_poll_table *pt)
{
    pt->req._proc = _poll_add;
    pt->status = RT_POLL_STAT_INIT;
    pt->nodes = RT_NULL;
    pt->polling_thread = rt_thread_self();
}

/**
 * @brief   Waits for events on the poll table with a specified timeout.
 *
 * This function waits for events on the poll table with the specified timeout
 * in milliseconds.
 *
 * @param   pt      Pointer to the poll table.
 * @param   msec    Timeout value in milliseconds.
 * @return  Upon successful completion, returns 0. If the timeout expires, -RT_ETIMEOUT
 *          is returned. If the operation is interrupted by a signal, -RT_EINTR is
 *          returned.
 */
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

/**
 * @brief   Performs poll operation for a single file descriptor.
 *
 * This function performs a poll operation for a single file descriptor and updates
 * the revents field of the pollfd structure accordingly.
 *
 * @param   pollfd  Pointer to the pollfd structure.
 * @param   req     Pointer to the poll request.
 * @return  Upon successful completion, returns the bitmask of events that occurred.
 *          If an error occurs, -1 is returned.
 */
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

/**
 * @brief   Performs the poll operation on an array of file descriptors.
 *
 * This function performs the poll operation on an array of file descriptors and
 * waits for events with the specified timeout.
 *
 * @param   fds     Pointer to the array of pollfd structures.
 * @param   nfds    Number of file descriptors in the array.
 * @param   pt      Pointer to the poll table.
 * @param   msec    Timeout value in milliseconds.
 * @return  Upon successful completion, returns the number of file descriptors
 *          for which events were received. If the timeout expires, -RT_ETIMEOUT
 *          is returned. If the operation is interrupted by a signal, -RT_EINTR is
 *          returned.
 */
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

/**
 * @brief   Tears down the poll table.
 *
 * This function tears down the poll table by removing all poll nodes associated
 * with it.
 *
 * @param   pt  Pointer to the poll table.
 */
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

/**
 * @brief   Performs the poll operation on a set of file descriptors.
 *
 * This function performs the poll operation on a set of file descriptors and
 * waits for events with the specified timeout.
 *
 * @param   fds     Pointer to the array of pollfd structures.
 * @param   nfds    Number of file descriptors in the array.
 * @param   timeout Timeout value in milliseconds.
 * @return  Upon successful completion, returns the number of file descriptors
 *          for which events were received. If the timeout expires, 0 is returned.
 *          If an error occurs, -1 is returned.
 */
int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int num;
    struct rt_poll_table table;

    poll_table_init(&table);

    num = poll_do(fds, nfds, &table, timeout);

    poll_teardown(&table);

    return num;
}
