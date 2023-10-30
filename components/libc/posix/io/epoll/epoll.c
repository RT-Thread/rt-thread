/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-29   zmq810150896   first version
 */

#include <rtthread.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <dfs_file.h>
#include "sys/epoll.h"
#include "poll.h"
#include <lwp_signal.h>

#define EPOLL_MUTEX_NAME "EVENTEPOLL"

#define EFD_SHARED_EPOLL_TYPE (EPOLL_CTL_ADD | EPOLL_CTL_DEL | EPOLL_CTL_MOD)
#define EPOLLINOUT_BITS (EPOLLIN | EPOLLOUT | EPOLLRDNORM | EPOLLWRNORM)
#define EPOLLEXCLUSIVE_BITS (EPOLLINOUT_BITS | EPOLLERR | EPOLLHUP | \
                             EPOLLET | EPOLLEXCLUSIVE)

static struct rt_spinlock spinlock;

struct rt_eventpoll;

/* Monitor queue */
struct rt_fd_list
{
    rt_uint32_t revents; /* Monitored events */
    struct epoll_event epev;
    rt_pollreq_t req;
    struct rt_eventpoll *ep;
    struct rt_wqueue_node wqn;
    int fd;
    struct rt_fd_list *next;
};

struct rt_ready_list
{
    int exclusive;                /* If triggered horizontally, a check is made to see if the data has been read, and if there is any data left to read, the readability event is returned in the next epoll_wait */
    struct rt_fd_list *rdl_event; /* rdl: ready list */
    struct rt_ready_list *next;
};

struct rt_eventpoll
{
    rt_uint32_t tirggered; /* the waited thread whether triggered */
    rt_wqueue_t epoll_read;
    rt_thread_t polling_thread;
    struct rt_mutex lock;
    struct rt_fd_list *fdlist; /* Monitor list */
    int eventpoll_num;         /* Number of ready lists */
    rt_pollreq_t req;
    struct rt_ready_list *rdlist; /* ready list */
};

static int epoll_close(struct dfs_file *file);
static int epoll_poll(struct dfs_file *file, struct rt_pollreq *req);
static int epoll_get_event(struct rt_fd_list *fl, rt_pollreq_t *req);
static int epoll_do_ctl(int epfd, int op, int fd, struct epoll_event *event);

static const struct dfs_file_ops epoll_fops =
    {
        .close = epoll_close,
        .poll = epoll_poll,
};

static int epoll_close_fdlist(struct rt_fd_list *fdlist)
{
    struct rt_fd_list *fre_node, *list;

    if (fdlist != RT_NULL)
    {
        list = fdlist;
        while (list->next != RT_NULL)
        {
            fre_node = list->next;
            rt_wqueue_remove(&fre_node->wqn);
            list->next = fre_node->next;
            rt_free(fre_node);
        }

        rt_free(fdlist);
    }

    return 0;
}

static int epoll_close_rdlist(struct rt_ready_list *rdlist)
{
    struct rt_ready_list *list, *fre_node;

    list = rdlist;
    if (list)
    {
        while (list->next != RT_NULL)
        {
            fre_node = list->next;
            list->next = fre_node->next;
            rt_free(fre_node);
        }

        rt_free(rdlist);
    }

    return 0;
}

static int epoll_close(struct dfs_file *file)
{
    struct rt_eventpoll *ep;

    if (file->vnode->ref_count != 1)
        return 0;

    if (file->vnode)
    {
        if (file->vnode->data)
        {
            ep = file->vnode->data;
            if (ep)
            {
                rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
                if (ep->fdlist)
                {
                    epoll_close_fdlist(ep->fdlist);
                }

                if (ep->rdlist)
                {
                    epoll_close_rdlist(ep->rdlist);
                }

                rt_mutex_release(&ep->lock);
                rt_mutex_detach(&ep->lock);
                rt_free(ep);
            }
        }
    }

    return 0;
}

static int epoll_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct rt_eventpoll *ep;
    struct rt_fd_list *fdlist;
    int mask;
    int events = 0;

    if (file->vnode->data)
    {
        ep = file->vnode->data;
        ep->req._key = req->_key;

        rt_poll_add(&ep->epoll_read, req);

        fdlist = ep->fdlist;
        if (fdlist)
        {
            while (fdlist->next != RT_NULL)
            {
                fdlist = fdlist->next;
                mask = epoll_get_event(fdlist, &fdlist->req);

                if (mask & fdlist->revents)
                {
                    events |= mask | POLLIN | EPOLLRDNORM;
                    break;
                }
            }
        }
    }

    return events;
}

static int epoll_rdlist_add(struct rt_fd_list *fdl, rt_uint32_t revents)
{
    struct rt_ready_list *rdlist = RT_NULL;
    struct rt_eventpoll *ep;
    int isexist = 0;
    int res = -1;

    ep = fdl->ep;

    if (revents & ep->req._key)
    {
        rt_wqueue_wakeup(&ep->epoll_read, (void *)POLLIN);
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    if (ep->rdlist == RT_NULL)
    {
        ep->rdlist = (struct rt_ready_list *)rt_malloc(sizeof(struct rt_ready_list));
        if (ep->rdlist == RT_NULL)
        {
            return -1;
        }
        ep->rdlist->next = RT_NULL;
    }

    rdlist = ep->rdlist;
    while (rdlist->next != RT_NULL)
    {
        rdlist = rdlist->next;
        if (rdlist->rdl_event->fd == fdl->fd)
        {
            isexist = 1;
            res = 0;
            break;
        }
    }

    if (!isexist)
    {
        rdlist = RT_NULL;
        rdlist = (struct rt_ready_list *)rt_malloc(sizeof(struct rt_ready_list));
        if (rdlist != RT_NULL)
        {
            rdlist->rdl_event = fdl;
            rdlist->rdl_event->epev.events = fdl->revents & revents;
            rdlist->next = ep->rdlist->next;
            rdlist->exclusive = 0;
            ep->rdlist->next = rdlist;
            ep->eventpoll_num++;
            res = 0;
        }
    }

    ep->tirggered = 1;

    rt_mutex_release(&ep->lock);

    return res;
}

/**
 * @brief   Callback function for waking up the epoll wqueue.
 *
 * @param   wait    Pointer to the wait queue node.
 * @param   key     The polling key.
 *
 * @return  0 on success, -1 on failure.
 */
static int epoll_wqueue_callback(struct rt_wqueue_node *wait, void *key)
{
    struct rt_fd_list *fdlist;

    if (key && !((rt_ubase_t)key & wait->key))
        return -1;

    fdlist = rt_container_of(wait, struct rt_fd_list, wqn);

    // Check if the fdlist has any revents and add it to the rdlist
    if (fdlist->revents)
    {
        epoll_rdlist_add(fdlist, (rt_ubase_t)key);
    }

    return __wqueue_default_wake(wait, key);
}

/**
 * @brief   Add a callback to the epoll wqueue.
 *
 * @param   wq      Pointer to the wait queue.
 * @param   req     Pointer to the poll request.
 */
static void epoll_wqueue_add_callback(rt_wqueue_t *wq, rt_pollreq_t *req)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *ep;

    fdlist = rt_container_of(req, struct rt_fd_list, req);

    ep = fdlist->ep;
    fdlist->wqn.key = req->_key;

    rt_list_init(&(fdlist->wqn.list));

    // Set the polling thread and callback function for the wqueue
    fdlist->wqn.polling_thread = ep->polling_thread;
    fdlist->wqn.wakeup = epoll_wqueue_callback;
    rt_wqueue_add(wq, &fdlist->wqn);
}

/**
 * @brief   Install an epoll control for the given fdlist and eventpoll.
 *
 * @param   fdlist  Pointer to the file descriptor list.
 * @param   ep      Pointer to the eventpoll.
 */
static void epoll_ctl_install(struct rt_fd_list *fdlist, struct rt_eventpoll *ep)
{
    rt_uint32_t mask = 0;

    fdlist->req._key = fdlist->revents;

    mask = epoll_get_event(fdlist, &fdlist->req);

    // Check if the mask indicates any matching events and add to the rdlist
    if (mask & fdlist->revents)
    {
        epoll_rdlist_add(fdlist, mask);
    }
}

/**
 * @brief   Initialize the members of an eventpoll structure.
 *
 * @param   ep  Pointer to the eventpoll structure.
 */
static void epoll_member_init(struct rt_eventpoll *ep)
{
    ep->tirggered = 0;
    ep->eventpoll_num = 0;
    ep->polling_thread = rt_thread_self();
    ep->rdlist = RT_NULL;
    ep->fdlist = RT_NULL;
    ep->req._key = 0;
    rt_wqueue_init(&ep->epoll_read);
    rt_spin_lock_init(&spinlock);
}

/**
 * @brief   Initialize an epoll file descriptor (epfd).
 *
 * This function initializes an epoll file descriptor (epfd) and associated data structures.
 *
 * @param   fd  The file descriptor to be initialized as an epoll file descriptor.
 *
 * @return  0 on success, a negative error code on failure.
 */
static int epoll_epf_init(int fd)
{
    struct dfs_file *df;
    struct rt_eventpoll *ep;
    rt_err_t ret = 0;

    df = fd_get(fd);

    if (df)
    {
        ep = (struct rt_eventpoll *)rt_malloc(sizeof(struct rt_eventpoll));
        if (ep)
        {
            epoll_member_init(ep);

            rt_mutex_init(&ep->lock, EPOLL_MUTEX_NAME, RT_IPC_FLAG_FIFO);

#ifdef RT_USING_DFS_V2
            df->fops = &epoll_fops;
#endif

            df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
            if (df->vnode)
            {
                ep->fdlist = (struct rt_fd_list *)rt_malloc(sizeof(struct rt_fd_list));
                if (ep->fdlist)
                {
                    ep->fdlist->next = RT_NULL;
                    ep->fdlist->fd = fd;
                    ep->fdlist->ep = ep;
                    dfs_vnode_init(df->vnode, FT_REGULAR, &epoll_fops);
                    df->vnode->data = ep;
                }
                else
                {
                    ret = -ENOMEM;
                    rt_free(df->vnode);
                    rt_free(ep);
                }
            }
            else
            {
                ret = -ENOMEM;
                rt_free(ep);
            }
        }
        else
        {
            ret = -ENOMEM;
        }
    }

    return ret;
}

/**
 * @brief   Create a new epoll file descriptor and initialize it.
 *
 * This function creates a new epoll file descriptor with the given size and initializes it.
 *
 * @param   size    The size of the epoll file descriptor.
 *
 * @return  The new epoll file descriptor (epfd) on success, or a negative error code on failure.
 */
static int epoll_do_create(int size)
{
    rt_err_t ret = -1;
    int status;
    int fd;

    if (size < 0)
    {
        rt_set_errno(EINVAL);
    }
    else
    {
        fd = fd_new();
        if (fd >= 0)
        {
            ret = fd;
            status = epoll_epf_init(fd);
            if (status < 0)
            {
                fd_release(fd);
                rt_set_errno(-status);
            }
        }
        else
        {
            rt_set_errno(-fd);
        }
    }

    return ret;
}

/**
 * @brief   Add a file descriptor to the epoll set.
 *
 * This function adds a file descriptor (fd) to the epoll set associated with the given epoll file descriptor (df).
 *
 * @param   df      The epoll file descriptor where the fd will be added.
 * @param   fd      The file descriptor to add to the epoll set.
 * @param   event   The epoll event structure that specifies the events to monitor.
 *
 * @return  0 on success, a negative error code on failure.
 */
static int epoll_ctl_add(struct dfs_file *df, int fd, struct epoll_event *event)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *ep;
    rt_err_t ret = -EINVAL;

    if (df->vnode->data)
    {
        ep = df->vnode->data;
        fdlist = ep->fdlist;
        ret = 0;

        while (fdlist->next != RT_NULL)
        {
            if (fdlist->next->fd == fd)
            {
                return 0;
            }
            fdlist = fdlist->next;
        }

        fdlist = (struct rt_fd_list *)rt_malloc(sizeof(struct rt_fd_list));
        if (fdlist)
        {
            fdlist->fd = fd;
            memcpy(&fdlist->epev.data, &event->data, sizeof(event->data));
            fdlist->epev.events = event->events;
            fdlist->ep = ep;
            fdlist->req._proc = epoll_wqueue_add_callback;
            fdlist->next = ep->fdlist->next;
            fdlist->revents = event->events;
            ep->fdlist->next = fdlist;

            epoll_ctl_install(fdlist, ep);
        }
        else
        {
            ret = -ENOMEM;
        }
    }

    return ret;
}

/**
 * @brief   Remove a file descriptor from the epoll set.
 *
 * This function removes a file descriptor (fd) from the epoll set associated with the given epoll file descriptor (df).
 *
 * @param   df  The epoll file descriptor where the fd will be removed from.
 * @param   fd  The file descriptor to remove from the epoll set.
 *
 * @return  0 on success, a negative error code on failure.
 */
static int epoll_ctl_del(struct dfs_file *df, int fd)
{
    struct rt_fd_list *fdlist, *fre_fd;
    struct rt_eventpoll *ep = RT_NULL;
    struct rt_ready_list *rdlist, *fre_rdl;
    rt_err_t ret = -EINVAL;

    if (df->vnode->data)
    {
        ep = df->vnode->data;

        fdlist = ep->fdlist;
        while (fdlist->next != RT_NULL)
        {
            if (fdlist->next->fd == fd)
            {
                fre_fd = fdlist->next;
                fdlist->next = fdlist->next->next;
                if (fre_fd->epev.events != 0)
                {
                    rt_wqueue_remove(&fre_fd->wqn);
                }
                rt_free(fre_fd);
                break;
            }
            else
            {
                fdlist = fdlist->next;
            }
        }

        if (ep->rdlist)
        {
            rdlist = ep->rdlist;
            while (rdlist->next != RT_NULL)
            {
                if (rdlist->next->rdl_event->fd == fd)
                {
                    fre_rdl = rdlist->next;
                    rdlist->next = rdlist->next->next;
                    ep->eventpoll_num--;
                    rt_free(fre_rdl);
                    break;
                }
                else
                {
                    rdlist = rdlist->next;
                }
            }
        }

        ret = 0;
    }

    return ret;
}

/**
 * @brief   Modify a file descriptor's events in the epoll set.
 *
 * This function modifies the events of a file descriptor (fd) in the epoll set associated with the given epoll file descriptor (df).
 *
 * @param   df      The epoll file descriptor where the fd is modified.
 * @param   fd      The file descriptor to modify in the epoll set.
 * @param   event   The epoll event structure specifying the modified events.
 *
 * @return  0 on success, a negative error code on failure.
 */
static int epoll_ctl_mod(struct dfs_file *df, int fd, struct epoll_event *event)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *ep = RT_NULL;
    rt_err_t ret = -EINVAL;

    if (df->vnode->data)
    {
        ep = df->vnode->data;

        fdlist = ep->fdlist;
        while (fdlist->next != RT_NULL)
        {
            if (fdlist->next->fd == fd)
            {
                memcpy(&fdlist->next->epev.data, &event->data, sizeof(event->data));
                fdlist->next->revents = event->events;
                rt_wqueue_remove(&fdlist->next->wqn);
                epoll_ctl_install(fdlist->next, ep);
                break;
            }

            fdlist = fdlist->next;
        }

        ret = 0;
    }

    return ret;
}

/**
 * @brief   Perform an epoll control operation (EPOLL_CTL_ADD/EPOLL_CTL_DEL/EPOLL_CTL_MOD).
 *
 * This function performs an epoll control operation, which can be EPOLL_CTL_ADD, EPOLL_CTL_DEL, or EPOLL_CTL_MOD.
 *
 * @param   epfd    The epoll file descriptor to operate on.
 * @param   op      The operation to perform (EPOLL_CTL_ADD, EPOLL_CTL_DEL, or EPOLL_CTL_MOD).
 * @param   fd      The file descriptor to add, remove, or modify.
 * @param   event   The epoll event structure specifying the events to monitor or modify.
 *
 * @return  0 on success, a negative error code on failure.
 */
static int epoll_do_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    struct dfs_file *epdf;
    struct rt_eventpoll *ep;
    rt_err_t ret = 0;

    if (op & ~EFD_SHARED_EPOLL_TYPE)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if ((epfd == fd) || (epfd < 0))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!(event->events & EPOLLEXCLUSIVE_BITS))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!fd_get(fd))
    {
        rt_set_errno(EBADF);
        return -1;
    }

    epdf = fd_get(epfd);

    if (epdf->vnode->data)
    {
        ep = epdf->vnode->data;
        event->events |= EPOLLERR | EPOLLHUP;
        rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

        switch (op)
        {
        case EPOLL_CTL_ADD:
            ret = epoll_ctl_add(epdf, fd, event);
            break;
        case EPOLL_CTL_DEL:
            ret = epoll_ctl_del(epdf, fd);
            break;
        case EPOLL_CTL_MOD:
            ret = epoll_ctl_mod(epdf, fd, event);
            break;
        default:
            rt_set_errno(EINVAL);
            break;
        }

        if (ret < 0)
        {
            rt_set_errno(-ret);
            ret = -1;
        }
        else
        {
            ep->polling_thread = rt_thread_self();
        }

        rt_mutex_release(&ep->lock);
    }

    return ret;
}

/**
 * @brief   Wait for events on an epoll file descriptor with a timeout.
 *
 * This function waits for events on an epoll file descriptor (epfd) with a specified timeout.
 *
 * @param   ep      The epoll file descriptor to wait for events on.
 * @param   msec    The timeout duration in milliseconds.
 *
 * @return  0 if events occurred within the timeout, 1 if no events occurred within the timeout.
 */
static int epoll_wait_timeout(struct rt_eventpoll *ep, int msec)
{
    rt_int32_t timeout;
    struct rt_thread *thread;
    rt_base_t level;
    int ret = 0;

    thread = ep->polling_thread;

    timeout = rt_tick_from_millisecond(msec);

    level = rt_spin_lock_irqsave(&spinlock);

    if (timeout != 0 && !ep->tirggered)
    {
        if (rt_thread_suspend_with_flag(thread, RT_KILLABLE) == RT_EOK)
        {
            if (timeout > 0)
            {
                rt_timer_control(&(thread->thread_timer),
                                 RT_TIMER_CTRL_SET_TIME,
                                 &timeout);
                rt_timer_start(&(thread->thread_timer));
            }

            rt_spin_unlock_irqrestore(&spinlock, level);

            rt_schedule();

            level = rt_spin_lock_irqsave(&spinlock);
        }
    }

    ret = !ep->tirggered;
    rt_spin_unlock_irqrestore(&spinlock, level);

    return ret;
}

/**
 * @brief   Get the events for a file descriptor in the epoll set.
 *
 * This function retrieves the events for a file descriptor (fd) in the epoll set and stores them in the poll request structure (req).
 *
 * @param   fl  The file descriptor list structure.
 * @param   req The poll request structure to store the events.
 *
 * @return  The retrieved events for the file descriptor or a negative error code on failure.
 */
static int epoll_get_event(struct rt_fd_list *fl, rt_pollreq_t *req)
{
    struct dfs_file *df;
    int mask = 0;
    int fd = 0;

    fd = fl->fd;
    if (fd >= 0)
    {
        df = fd_get(fd);
        if (df)
        {
            if (df->vnode->fops->poll)
            {
                req->_key = fl->revents | POLLERR | POLLHUP;
                mask = df->vnode->fops->poll(df, req);
                if (mask < 0)
                    return mask;
            }

            mask &= fl->revents | EPOLLOUT | POLLERR;
        }
    }

    return mask;
}

/**
 * @brief   Wait for events on an epoll file descriptor.
 *
 * This function waits for events on an epoll file descriptor (ep) and stores the events in the events array.
 *
 * @param   ep          The epoll file descriptor to wait for events on.
 * @param   events      The array to store the retrieved epoll events.
 * @param   maxevents   The maximum number of events to retrieve.
 * @param   timeout     The timeout duration in milliseconds.
 *
 * @return  The number of events retrieved, or 0 if the timeout expired, or a negative error code on failure.
 */
static int epoll_do(struct rt_eventpoll *ep, struct epoll_event *events, int maxevents, int timeout)
{
    struct rt_ready_list *rdlist, *pre_rdlist;
    int event_num = 0;
    int istimeout = 0;
    int isn_add = 0;
    int isfree = 0;
    int mask = 0;

    while (1)
    {
        rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
        if (ep->eventpoll_num > 0)
        {
            rdlist = ep->rdlist;
            while (rdlist->next != RT_NULL)
            {
                isfree = 0;
                isn_add = 0;
                pre_rdlist = rdlist;
                rdlist = rdlist->next;
                if (event_num < maxevents)
                {
                    rt_wqueue_remove(&rdlist->rdl_event->wqn);
                    mask = epoll_get_event(rdlist->rdl_event, &rdlist->rdl_event->req);

                    if (mask & rdlist->rdl_event->revents)
                    {
                        rdlist->rdl_event->epev.events = mask & rdlist->rdl_event->revents;
                    }
                    else
                    {
                        isfree = 1;
                        isn_add = 1;
                    }

                    if (rdlist->rdl_event->revents & EPOLLONESHOT)
                    {
                        rdlist->rdl_event->revents = 0;
                        isfree = 1;
                        rt_wqueue_remove(&rdlist->rdl_event->wqn);
                    }
                    else
                    {
                        if (rdlist->rdl_event->revents & EPOLLET)
                        {
                            isfree = 1;
                        }
                        else
                        {
                            if (rdlist->exclusive != 1)
                            {
                                rdlist->exclusive = 1;
                            }
                        }
                    }

                    if (!isn_add)
                    {
                        memcpy(&events[event_num], &rdlist->rdl_event->epev, sizeof(rdlist->rdl_event->epev));
                        event_num++;
                    }

                    if (isfree)
                    {
                        pre_rdlist->next = rdlist->next;
                        rt_free(rdlist);
                        ep->eventpoll_num--;
                        rdlist = pre_rdlist;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        rt_mutex_release(&ep->lock);

        if (event_num || istimeout)
        {
            ep->tirggered = 0;
            break;
        }

        if (epoll_wait_timeout(ep, timeout))
        {
            istimeout = 1;
        }
    }

    return event_num;
}

/**
 * @brief   Wait for events on an epoll file descriptor with timeout and signal mask.
 *
 * This function waits for events on an epoll file descriptor (epfd) with a specified timeout and signal mask.
 *
 * @param   epfd        The epoll file descriptor to wait for events on.
 * @param   events      The array to store the retrieved epoll events.
 * @param   maxevents   The maximum number of events to retrieve.
 * @param   timeout     The timeout duration in milliseconds.
 * @param   ss          The signal mask for the waiting thread (can be NULL).
 *
 * @return  The number of events retrieved, or 0 if the timeout expired, or a negative error code on failure.
 */
static int epoll_do_wait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    struct rt_eventpoll *ep;
    struct dfs_file *df;
    lwp_sigset_t old_sig, new_sig;
    rt_err_t ret = 0;

    if (ss)
    {
        memcpy(&new_sig, ss, sizeof(lwp_sigset_t));
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_BLOCK, &new_sig, &old_sig);
    }

    if ((maxevents > 0) && (epfd >= 0))
    {
        df = fd_get(epfd);
        if (df && df->vnode)
        {
            ep = (struct rt_eventpoll *)df->vnode->data;
            if (ep)
            {
                ret = epoll_do(ep, events, maxevents, timeout);
            }
        }
    }

    if (ss)
    {
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_SET_MASK, &old_sig, RT_NULL);
    }

    if (ret < 0)
    {
        rt_set_errno(-ret);
        ret = -1;
    }

    return ret;
}

/**
 * @brief   Create an epoll instance.
 *
 * This function creates an epoll instance and returns a file descriptor for it.
 *
 * @param   size The size parameter is ignored in this implementation.
 *
 * @return  A file descriptor for the epoll instance, or a negative error code on failure.
 */
int epoll_create(int size)
{
    return epoll_do_create(size);
}

/**
 * @brief   Control an epoll instance.
 *
 * This function allows adding, modifying, or deleting file descriptors from an epoll instance.
 *
 * @param   epfd    The file descriptor of the epoll instance.
 * @param   op      The operation to be performed (EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL).
 * @param   fd      The file descriptor to be added, modified, or deleted.
 * @param   event   The event structure specifying the events to monitor.
 *
 * @return  0 on success, or a negative error code on failure.
 */
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    return epoll_do_ctl(epfd, op, fd, event);
}

/**
 * @brief   Wait for events on an epoll instance.
 *
 * This function waits for events on an epoll instance and stores the events in the events array.
 *
 * @param   epfd        The file descriptor of the epoll instance to wait on.
 * @param   events      The array to store the retrieved epoll events.
 * @param   maxevents   The maximum number of events to retrieve.
 * @param   timeout     The timeout duration in milliseconds.
 *
 * @return  The number of events retrieved, or 0 if the timeout expired, or a negative error code on failure.
 */
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
{
    return epoll_do_wait(epfd, events, maxevents, timeout, RT_NULL);
}

/**
 * @brief   Wait for events on an epoll instance with signal mask.
 *
 * This function waits for events on an epoll instance with a specified signal mask and stores the events in the events array.
 *
 * @param   epfd        The file descriptor of the epoll instance to wait on.
 * @param   events      The array to store the retrieved epoll events.
 * @param   maxevents   The maximum number of events to retrieve.
 * @param   timeout     The timeout duration in milliseconds.
 * @param   ss          The signal mask for the waiting thread.
 *
 * @return  The number of events retrieved, or 0 if the timeout expired, or a negative error code on failure.
 */
int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    return epoll_do_wait(epfd, events, maxevents, timeout, ss);
}

/**
 * @brief   Wait for events on an epoll instance with signal mask.
 *
 * This function is equivalent to epoll_pwait and provides compatibility with some systems that use this name.
 *
 * @param   epfd        The file descriptor of the epoll instance to wait on.
 * @param   events      The array to store the retrieved epoll events.
 * @param   maxevents   The maximum number of events to retrieve.
 * @param   timeout     The timeout duration in milliseconds.
 * @param   ss          The signal mask for the waiting thread.
 *
 * @return  The number of events retrieved, or 0 if the timeout expired, or a negative error code on failure.
 */
int epoll_pwait2(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    return epoll_do_wait(epfd, events, maxevents, timeout, ss);
}
