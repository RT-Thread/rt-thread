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

struct rt_eventpoll;

/* Monitor queue */
struct rt_fd_list
{
    rt_uint32_t revents;
    struct epoll_event epev;
    rt_pollreq_t req;
    struct rt_eventpoll *eventpoll;
    struct rt_wqueue_node wqn;
    struct rt_fd_list *next;
};

struct rt_rdllist
{
    int exclusive;
    struct rt_fd_list *read_event;
    struct rt_rdllist *next;
};

struct rt_eventpoll
{
    rt_uint32_t tirggered;
    rt_thread_t polling_thread;
    struct rt_mutex lock;
    struct rt_fd_list *fdlist;
    int eventfd_num;
    struct rt_rdllist *rlist;
};

static int epoll_close(struct dfs_file *file);
static int epoll_poll(struct dfs_file *file, struct rt_pollreq *req);
static int do_epoll(struct rt_fd_list *fl, rt_pollreq_t *req);
static int do_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
static int get_event(struct dfs_file *df, rt_pollreq_t *req);

static const struct dfs_file_ops epoll_fops =
{
    .close      = epoll_close,
    .poll       = epoll_poll,
};

static int free_fdlist(struct rt_fd_list *fdlist)
{
    struct rt_fd_list *fre_list, *list;

    if (fdlist != RT_NULL)
    {
        list = fdlist;
        while (list->next != RT_NULL)
        {
            fre_list = list->next;
            rt_wqueue_remove(&fre_list->wqn);
            list->next = fre_list->next;
            rt_free(fre_list);
        }

        rt_free(fdlist);
    }

    return 0;
}

static int free_rdllist(struct rt_rdllist *rlist)
{
    struct rt_rdllist *list, *fre_list;

    list = rlist;
    if (list)
    {
        while (list->next != RT_NULL)
        {
            fre_list = list->next;
            list->next = fre_list->next;
            rt_free(fre_list);
        }

        rt_free(rlist);
    }

    return 0;
}

static int epoll_close(struct dfs_file *file)
{
    struct rt_eventpoll *ep;

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
                    free_fdlist(ep->fdlist);
                }

                if (ep->rlist)
                {
                    free_rdllist(ep->rlist);
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
        fdlist = ep->fdlist;
        if (fdlist)
        {
            while (fdlist->next != RT_NULL)
            {
                fdlist = fdlist->next;
                mask = do_epoll(fdlist, &fdlist->req);

                if (mask & fdlist->epev.events)
                {
                    events |= mask | POLLIN | EPOLLRDNORM;
                    break;
                }
            }
        }
    }

    return events;
}

static int rdllist_add(struct rt_fd_list *fdl, rt_uint32_t revents)
{
    struct rt_rdllist *rlist = RT_NULL;
    struct rt_eventpoll *ep;
    int isexist = 0;
    int res = -1;

    ep = fdl->eventpoll;

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    if (ep->rlist == RT_NULL)
    {
        ep->rlist = (struct rt_rdllist *)rt_malloc(sizeof(struct rt_rdllist));
        if (ep->rlist == RT_NULL)
        {
            return -1;
        }
        ep->rlist->next = RT_NULL;
    }

    rlist = ep->rlist;
    while (rlist->next != RT_NULL)
    {
        rlist = rlist->next;
        if (rlist->read_event->epev.data.fd == fdl->epev.data.fd)
        {
            isexist = 1;
            res = 0;
            break;
        }
    }

    if (!isexist)
    {
        rlist = RT_NULL;
        rlist = (struct rt_rdllist *)rt_malloc(sizeof(struct rt_rdllist));
        if (rlist != RT_NULL)
        {
            rlist->read_event = fdl;
            rlist->read_event->epev.events = revents;
            rlist->next = ep->rlist->next;
            rlist->exclusive = 0;

            ep->rlist->next = rlist;
            ep->eventfd_num ++;
            res = 0;
            if (rlist->read_event->revents & EPOLLONESHOT)
            {
                rlist->read_event->epev.events = 0;
            }
        }
    }

    ep->tirggered = 1;

    rt_mutex_release(&ep->lock);

    return res;
}

static int __wqueue_eventpoll_wake(struct rt_wqueue_node *wait, void *key)
{
    struct rt_fd_list *fdlist;

    if (key && !((rt_ubase_t)key & wait->key))
        return -1;

    fdlist = rt_container_of(wait, struct rt_fd_list, wqn);

    if (fdlist->epev.events)
    {
        rdllist_add(fdlist, (rt_ubase_t)key);
    }

    return __wqueue_default_wake(wait, key);
}

static void __eventpoll_add(rt_wqueue_t *wq, rt_pollreq_t *req)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *ep;

    fdlist = rt_container_of(req, struct rt_fd_list, req);

    ep = fdlist->eventpoll;
    fdlist->wqn.key = req->_key;

    rt_list_init(&(fdlist->wqn.list));

    fdlist->wqn.polling_thread = ep->polling_thread;
    fdlist->wqn.wakeup = __wqueue_eventpoll_wake;
    rt_wqueue_add(wq, &fdlist->wqn);
}

static int get_event(struct dfs_file *df, rt_pollreq_t *req)
{
    int mask = 0;

    if (df)
    {
        if (df->vnode->fops->poll)
        {
            req->_key = EPOLLINOUT_BITS ;
            mask = df->vnode->fops->poll(df, req);
        }
    }

    return mask;
}

static void eventpoll_install(struct rt_fd_list *fdlist, struct rt_eventpoll *ep)
{
    struct dfs_file *df;
    rt_uint32_t mask = 0;

    fdlist->req._key = fdlist->epev.events;

    df = fd_get(fdlist->epev.data.fd);

    if (df)
    {
        mask = get_event(df, &fdlist->req);
        if (mask & fdlist->epev.events)
        {
            rdllist_add(fdlist, mask);
        }
    }
}

static void eventpoll_init(struct rt_eventpoll *ep)
{
    ep->tirggered = 0;
    ep->eventfd_num = 0;
    ep->polling_thread = rt_thread_self();
    ep->rlist = RT_NULL;
    ep->fdlist = RT_NULL;
}

static int epoll_dfs_file_init(int fd)
{
    struct dfs_file *df;
    struct rt_eventpoll *eventpoll;
    rt_err_t ret = 0;

    df = fd_get(fd);

    if (df)
    {
        eventpoll = (struct rt_eventpoll *)rt_malloc(sizeof(struct rt_eventpoll));
        if (eventpoll)
        {
            eventpoll_init(eventpoll);

            rt_mutex_init(&eventpoll->lock, EPOLL_MUTEX_NAME, RT_IPC_FLAG_FIFO);

            df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
            if (df->vnode)
            {
                eventpoll->fdlist = (struct rt_fd_list *)rt_malloc(sizeof(struct rt_fd_list));
                if (eventpoll->fdlist)
                {
                    eventpoll->fdlist->next = RT_NULL;
                    eventpoll->fdlist->epev.data.fd = fd;
                    eventpoll->fdlist->eventpoll = eventpoll;
                    dfs_vnode_init(df->vnode, FT_REGULAR, &epoll_fops);
                    df->vnode->data = eventpoll;
                }
                else
                {
                    ret = -ENOMEM;
                    rt_free(df->vnode);
                    rt_free(eventpoll);
                }
            }
            else
            {
                ret = -ENOMEM;
                rt_free(eventpoll);
            }
        }
        else
        {
            ret = -ENOMEM;
        }
    }

    return ret;
}

static int do_epoll_create(int size)
{
    rt_err_t ret = 0;
    int status;
    int fd;

    if (size < 0)
    {
        ret = -EINVAL;
    }
    else
    {
        fd = fd_new();
        if (fd >= 0)
        {
            ret = fd;
            status = epoll_dfs_file_init(fd);
            if (status < 0)
            {
                fd_release(fd);
                ret = status;
            }
        }
        else
        {
            ret = fd;
        }
    }

    return ret;
}

static int epoll_ctl_add(struct dfs_file *df ,struct epoll_event *event)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *eventpoll;
    rt_err_t ret = 0;

    if (df->vnode->data)
    {
        eventpoll = df->vnode->data;
    }
    else
    {
        return -1;
    }

    fdlist = eventpoll->fdlist;
    while (fdlist->next != RT_NULL)
    {
        if (fdlist->next->epev.data.fd == event->data.fd)
        {
            return 0;
        }
        fdlist = fdlist->next;
    }

    fdlist = (struct rt_fd_list *)rt_malloc(sizeof(struct rt_fd_list));
    if (fdlist)
    {
        fdlist->epev.data.fd = event->data.fd;
        fdlist->epev.events = event->events;
        fdlist->eventpoll = eventpoll;
        fdlist->req._proc = __eventpoll_add;
        fdlist->next = eventpoll->fdlist->next;
        fdlist->revents = event->events;
        eventpoll->fdlist->next = fdlist;

        eventpoll_install(fdlist, eventpoll);
    }
    else
    {
        ret = -ENOMEM;
    }

    return ret;
}

static int epoll_ctl_del(struct dfs_file *df ,struct epoll_event *event)
{
    struct rt_fd_list *fdlist, *fre_fd;
    struct rt_eventpoll *eventpoll = RT_NULL;
    struct rt_rdllist *rdllist, *fre_rdl;
    rt_err_t ret = 0;

    if (df->vnode->data)
    {
        eventpoll = df->vnode->data;
    }
    else
    {
        return 0;
    }

    fdlist = eventpoll->fdlist;
    while (fdlist->next != RT_NULL)
    {
        if (fdlist->next->epev.data.fd == event->data.fd)
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

    if (eventpoll->rlist)
    {
        rdllist = eventpoll->rlist;
        while (rdllist->next != RT_NULL)
        {
            if (rdllist->next->read_event->epev.data.fd == event->data.fd)
            {
                fre_rdl = rdllist->next;
                rdllist->next = rdllist->next->next;
                eventpoll->eventfd_num --;
                rt_free(fre_rdl);
                break;
            }
            else
            {
                rdllist = rdllist->next;
            }
        }
    }

    return ret;
}

static int epoll_ctl_mod(struct dfs_file *df ,struct epoll_event *event)
{
    struct rt_fd_list *fdlist;
    struct rt_eventpoll *eventpoll = RT_NULL;
    rt_err_t ret = 0;

    if (df->vnode->data)
    {
        eventpoll = df->vnode->data;
    }
    else
    {
        return -1;
    }

    fdlist = eventpoll->fdlist;
    while (fdlist->next != RT_NULL)
    {
        if (fdlist->next->epev.data.fd == event->data.fd)
        {
            fdlist->next->epev.events = event->events;
            fdlist->next->revents = event->events;
            rt_wqueue_remove(&fdlist->wqn);
            eventpoll_install(fdlist, eventpoll);
            break;
        }

        fdlist = fdlist->next;
    }

    return ret;
}

static int do_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    struct dfs_file *epdf;
    struct rt_eventpoll *ep;
    rt_err_t ret = 0;

    if (op & ~EFD_SHARED_EPOLL_TYPE)
        return -EINVAL;

    if ((epfd == fd) || (epfd < 0) || (fd < 0) || (event->data.fd != fd))
        return -EINVAL;

    if (!(event->events & EPOLLEXCLUSIVE_BITS))
        return -EINVAL;

    epdf = fd_get(epfd);

    if (epdf->vnode->data)
    {
        ep = epdf->vnode->data;
    }
    else
    {
        return -1;
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    if (epdf)
    {
        switch (op)
        {
        case EPOLL_CTL_ADD:
            ret = epoll_ctl_add(epdf, event);
            break;
        case EPOLL_CTL_DEL:
            ret = epoll_ctl_del(epdf, event);
            break;
        case EPOLL_CTL_MOD:
            ret = epoll_ctl_mod(epdf, event);
            break;
        default:
            ret = -EINVAL;
            break;
        }
    }
    else
    {
        ret = -EINVAL;
    }

    rt_mutex_release(&ep->lock);

    return ret;
}

static int epoll_wait_timeout(struct rt_eventpoll *ep, int msec)
{
    rt_int32_t timeout;
    struct rt_thread *thread;
    rt_base_t level;
    int ret = 0;

    thread = ep->polling_thread;

    timeout = rt_tick_from_millisecond(msec);

    level = rt_hw_interrupt_disable();

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

            rt_hw_interrupt_enable(level);

            rt_schedule();

            level = rt_hw_interrupt_disable();
        }
    }

    ret = !ep->tirggered;
    rt_hw_interrupt_enable(level);

    return ret;
}

static int do_epoll(struct rt_fd_list *fl, rt_pollreq_t *req)
{
    struct dfs_file *df;
    int mask = 0;
    int fd = 0;

    fd = fl->epev.data.fd;
    if (fd >= 0)
    {
        df = fd_get(fd);
        if (df)
        {
            if (df->vnode->fops->poll)
            {
                req->_key = fl->epev.events | EPOLLINOUT_BITS;
                mask = df->vnode->fops->poll(df, req);
            }
        }

        if (mask >= 0)
        {
            mask &= fl->epev.events;
        }
    }

    return mask;
}

static int epoll_do(struct rt_eventpoll *ep, struct epoll_event *events, int maxevents, int timeout)
{
    struct rt_rdllist *rdllist, *pre_rdllist;
    int event_num = 0;
    int istimeout = 0;
    int isn_add = 0;
    int isfree = 0;
    int mask = 0;

    while (1)
    {
        rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

        if (ep->eventfd_num > 0)
        {
            rdllist = ep->rlist;
            while (rdllist->next != RT_NULL)
            {
                isfree = 0;
                isn_add = 0;
                pre_rdllist = rdllist;
                rdllist = rdllist->next;
                if (event_num < maxevents)
                {
                    if (rdllist->read_event->epev.events == 0)
                    {
                        isfree = 1;
                        rt_wqueue_remove(&rdllist->read_event->wqn);
                    }
                    else
                    {
                        if (rdllist->read_event->revents & EPOLLET)
                        {
                            isfree = 1;
                        }
                        else
                        {
                            if (rdllist->exclusive)
                            {
                                rt_wqueue_remove(&rdllist->read_event->wqn);
                                mask = get_event(fd_get(rdllist->read_event->epev.data.fd), &rdllist->read_event->req);
                                if (mask & rdllist->read_event->revents)
                                {
                                    rdllist->read_event->epev.events = mask;
                                }
                                else
                                {
                                    isfree = 1;
                                    isn_add = 1;
                                }
                            }
                            else
                            {
                                rdllist->exclusive = 1;
                            }
                        }
                    }

                    if (!isn_add)
                    {
                        events[event_num].data.fd = rdllist->read_event->epev.data.fd;
                        events[event_num].events = rdllist->read_event->revents;
                        event_num ++;
                    }

                    if (isfree)
                    {
                        pre_rdllist->next = rdllist->next;
                        rt_free(rdllist);
                        ep->eventfd_num --;
                        rdllist = pre_rdllist;
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

static int do_epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    struct rt_eventpoll *ep;
    struct dfs_file *df;
    lwp_sigset_t old_sig, new_sig;
    rt_err_t ret = -EINVAL;

    if (ss)
    {
        memcpy(&new_sig, ss, sizeof(lwp_sigset_t));
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_BLOCK, &new_sig, &old_sig);
    }

    if ((maxevents > 0) && (epfd >=0))
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

    return ret;
}

int epoll_create(int size)
{
    return do_epoll_create(size);
}

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    return do_epoll_ctl(epfd, op, fd, event);
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
{
    return do_epoll_wait(epfd, events, maxevents, timeout, RT_NULL);
}

int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    return do_epoll_wait(epfd, events, maxevents, timeout, ss);
}

int epoll_pwait2(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *ss)
{
    return do_epoll_wait(epfd, events, maxevents, timeout, ss);
}
