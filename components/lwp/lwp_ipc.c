/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 * 2023-09-16     zmq810150896 Increased versatility of some features on dfs v2
 */
#include <rtthread.h>
#include <rthw.h>
#include <lwp.h>

#include "lwp_ipc.h"
#include "lwp_ipc_internal.h"

#include <dfs_file.h>
#include <poll.h>

#ifdef RT_USING_DFS_V2
#include <dfs_dentry.h>
#endif

/**
 * the IPC channel states
 */
enum
{
    RT_IPC_STAT_IDLE,   /* no suspended threads */
    RT_IPC_STAT_WAIT,   /* suspended receivers exist */
    RT_IPC_STAT_ACTIVE, /* suspended senders exist */
};

/**
 * IPC message structure.
 *
 * They are allocated and released in the similar way like 'rt_chfd'.
 */
struct rt_ipc_msg
{
    struct rt_channel_msg msg;                           /**< the payload of msg */
    rt_list_t mlist;                                     /**< the msg list */
    rt_uint8_t need_reply;                               /**< whether msg wait reply*/
};
typedef struct rt_ipc_msg *rt_ipc_msg_t;

static rt_ipc_msg_t _ipc_msg_free_list = (rt_ipc_msg_t)RT_NULL; /* released chain */
static int rt_ipc_msg_used = 0;                                 /* first unallocated entry */
static struct rt_ipc_msg ipc_msg_pool[RT_CH_MSG_MAX_NR];        /* initial message array */

/**
 * Allocate an IPC message from the statically-allocated array.
 */
static rt_ipc_msg_t _ipc_msg_alloc(void)
{
    rt_ipc_msg_t p = (rt_ipc_msg_t)RT_NULL;

    if (_ipc_msg_free_list)                         /* use the released chain first */
    {
        p = _ipc_msg_free_list;
        _ipc_msg_free_list = (rt_ipc_msg_t)p->msg.sender; /* emtry payload as a pointer */
    }
    else if (rt_ipc_msg_used < RT_CH_MSG_MAX_NR)
    {
        p = &ipc_msg_pool[rt_ipc_msg_used];
        rt_ipc_msg_used++;
    }
    return p;
}

/**
 * Put a released IPC message back to the released chain.
 */
static void _ipc_msg_free(rt_ipc_msg_t p_msg)
{
    p_msg->msg.sender = (void*)_ipc_msg_free_list;
    _ipc_msg_free_list = p_msg;
}

/**
 * Initialized the IPC message.
 */
static void rt_ipc_msg_init(rt_ipc_msg_t msg, struct rt_channel_msg *data, rt_uint8_t need_reply)
{
    RT_ASSERT(msg != RT_NULL);

    msg->need_reply = need_reply;
    msg->msg = *data;
    msg->msg.sender = (void*)rt_thread_self();
    rt_list_init(&msg->mlist);
}

/**
 * Initialized the list of the waiting receivers on the IPC channel.
 */
rt_inline rt_err_t rt_channel_object_init(struct rt_ipc_object *ipc)
{
    rt_list_init(&(ipc->suspend_thread));   /* receiver list */

    return RT_EOK;
}

/**
 * Wakeup the first suspened thread in the list.
 */
rt_inline rt_err_t rt_channel_list_resume(rt_list_t *list)
{
    struct rt_thread *thread;

    /* get the first thread entry waiting for sending */
    thread = rt_list_entry(list->next, struct rt_thread, tlist);

    rt_thread_resume(thread);

    return RT_EOK;
}

/**
 * Wakeup all the suspended threads in the list.
 */
rt_inline rt_err_t rt_channel_list_resume_all(rt_list_t *list)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;

    /* wakeup all suspended threads for sending */
    while (!rt_list_isempty(list))
    {
        temp = rt_hw_interrupt_disable();
        thread = rt_list_entry(list->next, struct rt_thread, tlist);
        thread->error = -RT_ERROR;
        rt_thread_resume(thread);
        rt_hw_interrupt_enable(temp);
    }

    return RT_EOK;
}

/**
 * Suspend the thread and chain it into the end of the list.
 */
rt_inline rt_err_t rt_channel_list_suspend(rt_list_t *list, struct rt_thread *thread)
{
    /* suspend thread */
    rt_err_t ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);

    if (ret == RT_EOK)
    {
        rt_list_insert_before(list, &(thread->tlist));  /* list end */
    }

    return ret;
}


static void _rt_channel_check_wq_wakup(rt_channel_t ch)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (rt_list_isempty(&ch->wait_msg))
    {
        rt_hw_interrupt_enable(level);
        return;
    }

    rt_wqueue_wakeup(&ch->reader_queue, 0);
    rt_hw_interrupt_enable(level);
}

/**
 * Create a new or open an existing IPC channel.
 */
rt_channel_t rt_raw_channel_open(const char *name, int flags)
{
    register rt_ubase_t temp = 0;
    rt_channel_t ch = RT_NULL;

    struct rt_object *object;
    struct rt_list_node *node;
    struct rt_object_information *information;

    temp = rt_hw_interrupt_disable();
    information = rt_object_get_information(RT_Object_Class_Channel);
    RT_ASSERT(information != RT_NULL);

    /* retrieve the existing IPC channels */
    for (node  = information->object_list.next;
            node != &(information->object_list);
            node  = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);
        if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
        {
            if ((flags & O_CREAT) && (flags & O_EXCL))
            {
                goto quit;
            }
            /* find the IPC channel with the specific name */
            ch = (rt_channel_t)object;
            ch->ref++;      /* increase the reference count */
            break;
        }
    }
    if (!ch) /* create a new IPC channel */
    {
        if (flags & O_CREAT)
        {
            RT_DEBUG_NOT_IN_INTERRUPT;

            /* allocate a real IPC channel structure */
            ch = (rt_channel_t)rt_object_allocate(RT_Object_Class_Channel, name);
        }

        if (!ch)
        {
            goto quit;
        }

        rt_channel_object_init(&ch->parent);    /* suspended receivers */
        rt_list_init(&ch->wait_msg);            /* unhandled messages */
        rt_list_init(&ch->wait_thread);         /* suspended senders */
        rt_wqueue_init(&ch->reader_queue);      /* reader poll queue */
        ch->reply = RT_NULL;
        ch->stat = RT_IPC_STAT_IDLE;            /* no suspended threads */
        ch->ref = 1;
    }
quit:
    rt_hw_interrupt_enable(temp);
    return ch;
}

/**
 * Close an existiong IPC channel, release the resources.
 */
rt_err_t rt_raw_channel_close(rt_channel_t ch)
{
    register rt_ubase_t temp;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (ch == RT_NULL)
    {
        return -RT_EIO;
    }

    temp = rt_hw_interrupt_disable();
    if (rt_object_get_type(&ch->parent.parent) != RT_Object_Class_Channel)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }
    if (rt_object_is_systemobject(&ch->parent.parent) != RT_FALSE)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }

    if (ch->ref == 0)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }
    ch->ref--;
    if (ch->ref == 0)
    {
        /* wakeup all the suspended receivers and senders */
        rt_channel_list_resume_all(&ch->parent.suspend_thread);
        rt_channel_list_resume_all(&ch->wait_thread);

        /* all ipc msg will lost */
        rt_list_init(&ch->wait_msg);

        rt_object_delete(&ch->parent.parent);   /* release the IPC channel structure */
    }
    rt_hw_interrupt_enable(temp);
    return RT_EOK;
}

static rt_err_t wakeup_sender_wait_recv(void *object, struct rt_thread *thread)
{
    rt_channel_t ch;

    ch = (rt_channel_t)object;
    if (ch->stat == RT_IPC_STAT_ACTIVE && ch->reply == thread)
    {
        ch->stat = RT_IPC_STAT_IDLE;
        ch->reply = RT_NULL;
    }
    else
    {
        rt_ipc_msg_t msg;
        rt_list_t *l;

        l = ch->wait_msg.next;
        while (l != &ch->wait_msg)
        {
            msg = rt_list_entry(l, struct rt_ipc_msg, mlist);
            if (msg->need_reply && msg->msg.sender == thread)
            {
                rt_list_remove(&msg->mlist);  /* remove the msg from the channel */
                _ipc_msg_free(msg);
                break;
            }
            l = l->next;
        }
    }
    thread->error = -RT_EINTR;
    return rt_thread_resume(thread);       /* wake up the sender */
}

static rt_err_t wakeup_sender_wait_reply(void *object, struct rt_thread *thread)
{
    rt_channel_t ch;

    ch = (rt_channel_t)object;
    RT_ASSERT(ch->stat == RT_IPC_STAT_ACTIVE && ch->reply == thread);
    ch->stat = RT_IPC_STAT_IDLE;
    ch->reply = RT_NULL;
    thread->error = -RT_EINTR;
    return rt_thread_resume(thread);       /* wake up the sender */
}

static void sender_timeout(void *parameter)
{
    struct rt_thread *thread = (struct rt_thread*)parameter;
    rt_channel_t ch;

    ch = (rt_channel_t)(thread->wakeup.user_data);
    if (ch->stat == RT_IPC_STAT_ACTIVE && ch->reply == thread)
    {
        ch->stat = RT_IPC_STAT_IDLE;
        ch->reply = RT_NULL;
    }
    else
    {
        rt_ipc_msg_t msg;
        rt_list_t *l;

        l = ch->wait_msg.next;
        while (l != &ch->wait_msg)
        {
            msg = rt_list_entry(l, struct rt_ipc_msg, mlist);
            if (msg->need_reply && msg->msg.sender == thread)
            {
                rt_list_remove(&msg->mlist);  /* remove the msg from the channel */
                _ipc_msg_free(msg);
                break;
            }
            l = l->next;
        }
    }
    thread->error = -RT_ETIMEOUT;
    thread->wakeup.func = RT_NULL;

    rt_list_remove(&(thread->tlist));
    /* insert to schedule ready list */
    rt_schedule_insert_thread(thread);
    /* do schedule */
    rt_schedule();
}

/**
 * Get file vnode from fd.
 */
static void *_ipc_msg_get_file(int fd)
{
    struct dfs_file *d;

    d = fd_get(fd);
    if (d == RT_NULL)
        return RT_NULL;

    if (!d->vnode)
        return RT_NULL;

    return (void *)d;
}

/**
 * Get fd from file vnode.
 */
static int _ipc_msg_fd_new(void *file)
{
    int fd;
    struct dfs_file *d;
    struct dfs_file *df = RT_NULL;

    if (file == RT_NULL)
    {
        return -1;
    }

    df = (struct dfs_file *)file;

    fd = fd_new();
    if (fd < 0)
    {
        return -1;
    }

    d = fd_get(fd);
    if (!d)
    {
        fd_release(fd);
        return -1;
    }

#ifdef RT_USING_DFS_V2
    d->fops = df->fops;
    d->mode = df->mode;
    d->dentry = df->dentry;
    d->dentry->ref_count ++;
#endif

    d->vnode = df->vnode;
    d->flags = df->flags;
    d->data = df->data;
    d->magic = df->magic;

    d->vnode->ref_count ++;

    return fd;
}

/**
 * Send data through an IPC channel, wait for the reply or not.
 */
static rt_err_t _rt_raw_channel_send_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, int need_reply, rt_channel_msg_t data_ret, rt_int32_t time)
{
    rt_ipc_msg_t msg;
    struct rt_thread *thread_recv, *thread_send = 0;
    register rt_base_t temp;
    rt_err_t ret;
    void (*old_timeout_func)(void *) = 0;

    if (need_reply)
    {
        RT_DEBUG_NOT_IN_INTERRUPT;
    }

    if (ch == RT_NULL)
    {
        return -RT_EIO;
    }

    temp = rt_hw_interrupt_disable();

    if (rt_object_get_type(&ch->parent.parent) != RT_Object_Class_Channel)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }
    if (need_reply && time == 0)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ETIMEOUT;
    }

    /* allocate an IPC message */
    msg = _ipc_msg_alloc();
    if (!msg)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ENOMEM;
    }

    /* IPC message : file descriptor */
    if (data->type == RT_CHANNEL_FD)
    {
        data->u.fd.file = _ipc_msg_get_file(data->u.fd.fd);
    }

    rt_ipc_msg_init(msg, data, need_reply);

    if (need_reply)
    {
        thread_send = rt_thread_self();
        thread_send->error = RT_EOK;
    }

    switch (ch->stat)
    {
        case RT_IPC_STAT_IDLE:
        case RT_IPC_STAT_ACTIVE:
            if (need_reply)
            {
                ret = rt_channel_list_suspend(&ch->wait_thread, thread_send);
                if (ret != RT_EOK)
                {
                    _ipc_msg_free(msg);
                    rt_hw_interrupt_enable(temp);
                    return ret;
                }
                rt_thread_wakeup_set(thread_send, wakeup_sender_wait_recv, (void*)ch);
                if (time > 0)
                {
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_GET_FUNC,
                            &old_timeout_func);
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_SET_FUNC,
                            sender_timeout);
                    /* reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_SET_TIME,
                            &time);
                    rt_timer_start(&(thread_send->thread_timer));
                }
            }
            /*
             * If there is no thread waiting for messages, chain the message
             * into the list.
             */
            rt_list_insert_before(&ch->wait_msg, &msg->mlist);
            break;
        case RT_IPC_STAT_WAIT:
            /*
             * If there are suspended receivers on the IPC channel, transfer the
             * pointer of the message to the first receiver directly and wake it
             * up.
             */
            RT_ASSERT(ch->parent.suspend_thread.next != &ch->parent.suspend_thread);

            if (need_reply)
            {
                ret = rt_channel_list_suspend(&ch->wait_thread, thread_send);
                if (ret != RT_EOK)
                {
                    _ipc_msg_free(msg);
                    rt_hw_interrupt_enable(temp);
                    return ret;
                }
                ch->reply = thread_send;    /* record the current waiting sender */
                ch->stat = RT_IPC_STAT_ACTIVE;
                rt_thread_wakeup_set(thread_send, wakeup_sender_wait_reply, (void*)ch);
                if (time > 0)
                {
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_GET_FUNC,
                            &old_timeout_func);
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_SET_FUNC,
                            sender_timeout);
                    /* reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread_send->thread_timer),
                            RT_TIMER_CTRL_SET_TIME,
                            &time);
                    rt_timer_start(&(thread_send->thread_timer));
                }
            }
            else
            {
                ch->stat = RT_IPC_STAT_IDLE;
            }
            thread_recv = rt_list_entry(ch->parent.suspend_thread.next, struct rt_thread, tlist);
            thread_recv->msg_ret = msg;     /* to the first suspended receiver */
            thread_recv->error = RT_EOK;
            rt_channel_list_resume(&ch->parent.suspend_thread);
            break;
        default:
            break;
    }

    if ( ch->stat == RT_IPC_STAT_IDLE)
    {
        _rt_channel_check_wq_wakup(ch);
    }
    rt_hw_interrupt_enable(temp);

    /* reschedule in order to let the potential receivers run */
    rt_schedule();

    if (need_reply)
    {
        temp = rt_hw_interrupt_disable();
        if (old_timeout_func)
        {
            rt_timer_control(&(thread_send->thread_timer),
                    RT_TIMER_CTRL_SET_FUNC,
                    old_timeout_func);
        }
        ret = thread_send->error;
        rt_hw_interrupt_enable(temp);

        if (ret != RT_EOK)
        {
            return ret;
        }

        /* If the sender gets the chance to run, the requested reply must be valid. */
        RT_ASSERT(data_ret != RT_NULL);
        *data_ret = ((rt_ipc_msg_t)(thread_send->msg_ret))->msg;   /* extract data */
        temp = rt_hw_interrupt_disable();
        _ipc_msg_free(thread_send->msg_ret);    /* put back the message to kernel */
        rt_hw_interrupt_enable(temp);
        thread_send->msg_ret = RT_NULL;
    }

    return RT_EOK;
}

/**
 * Send data through an IPC channel with no reply.
 */
rt_err_t rt_raw_channel_send(rt_channel_t ch, rt_channel_msg_t data)
{
    return _rt_raw_channel_send_recv_timeout(ch, data, 0, 0, RT_WAITING_FOREVER);
}

/**
 * Send data through an IPC channel and wait for the relpy.
 */
rt_err_t rt_raw_channel_send_recv(rt_channel_t ch, rt_channel_msg_t data, rt_channel_msg_t data_ret)
{
    return _rt_raw_channel_send_recv_timeout(ch, data, 1, data_ret, RT_WAITING_FOREVER);
}

/**
 * Send data through an IPC channel and wait for the relpy.
 */
rt_err_t rt_raw_channel_send_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    return _rt_raw_channel_send_recv_timeout(ch, data, 1, data_ret, time);
}

/**
 * Reply to the waiting sender and wake it up.
 */
rt_err_t rt_raw_channel_reply(rt_channel_t ch, rt_channel_msg_t data)
{
    rt_ipc_msg_t msg;
    struct rt_thread *thread;
    register rt_base_t temp;

    if (ch == RT_NULL)
    {
        return -RT_EIO;
    }

    temp = rt_hw_interrupt_disable();

    if (rt_object_get_type(&ch->parent.parent) != RT_Object_Class_Channel)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }

    if (ch->stat != RT_IPC_STAT_ACTIVE)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ERROR;
    }

    if (ch->reply == RT_NULL)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ERROR;
    }

    /* allocate an IPC message */
    msg = _ipc_msg_alloc();
    if (!msg)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ENOMEM;
    }

    rt_ipc_msg_init(msg, data, 0);

    thread = ch->reply;
    thread->msg_ret = msg;          /* transfer the reply to the sender */
    rt_thread_resume(thread);       /* wake up the sender */
    ch->stat = RT_IPC_STAT_IDLE;
    ch->reply = RT_NULL;

    _rt_channel_check_wq_wakup(ch);
    rt_hw_interrupt_enable(temp);
    rt_schedule();

    return RT_EOK;
}

static rt_err_t wakeup_receiver(void *object, struct rt_thread *thread)
{
    rt_channel_t ch;
    rt_err_t ret;

    ch = (rt_channel_t)object;
    ch->stat = RT_IPC_STAT_IDLE;
    thread->error = -RT_EINTR;
    ret = rt_channel_list_resume(&ch->parent.suspend_thread);
    _rt_channel_check_wq_wakup(ch);
    return ret;
}

static void receiver_timeout(void *parameter)
{
    struct rt_thread *thread = (struct rt_thread*)parameter;
    rt_channel_t ch;

    ch = (rt_channel_t)(thread->wakeup.user_data);

    ch->stat = RT_IPC_STAT_IDLE;
    thread->error = -RT_ETIMEOUT;
    thread->wakeup.func = RT_NULL;

    rt_list_remove(&(thread->tlist));
    /* insert to schedule ready list */
    rt_schedule_insert_thread(thread);

    _rt_channel_check_wq_wakup(ch);
    /* do schedule */
    rt_schedule();
}

/**
 * Fetch a message from the specified IPC channel.
 */
static rt_err_t _rt_raw_channel_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, rt_int32_t time)
{
    struct rt_thread *thread;
    rt_ipc_msg_t msg_ret;
    register rt_base_t temp;
    rt_err_t ret;
    void (*old_timeout_func)(void *) = 0;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (ch == RT_NULL)
    {
        return -RT_EIO;
    }

    temp = rt_hw_interrupt_disable();

    if (rt_object_get_type(&ch->parent.parent) != RT_Object_Class_Channel)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_EIO;
    }
    if (ch->stat != RT_IPC_STAT_IDLE)
    {
        rt_hw_interrupt_enable(temp);
        return -RT_ERROR;
    }

    if (ch->wait_msg.next != &ch->wait_msg) /* there exist unhandled messages */
    {
        msg_ret = rt_list_entry(ch->wait_msg.next, struct rt_ipc_msg, mlist);
        rt_list_remove(ch->wait_msg.next);  /* remove the message from the channel */
        if (msg_ret->need_reply)
        {
            RT_ASSERT(ch->wait_thread.next != &ch->wait_thread);

            thread = rt_list_entry(ch->wait_thread.next, struct rt_thread, tlist);
            rt_list_remove(ch->wait_thread.next);
            ch->reply = thread;             /* record the waiting sender */
            ch->stat = RT_IPC_STAT_ACTIVE;  /* no valid suspened receivers */
        }
        *data = msg_ret->msg;      /* extract the transferred data */
        if (data->type == RT_CHANNEL_FD)
        {
            data->u.fd.fd = _ipc_msg_fd_new(data->u.fd.file);
        }
        _ipc_msg_free(msg_ret);     /* put back the message to kernel */
    }
    else
    {
        if (time == 0)
        {
            rt_hw_interrupt_enable(temp);
            return -RT_ETIMEOUT;
        }
        /* no valid message, we must wait */
        thread = rt_thread_self();

        ret = rt_channel_list_suspend(&ch->parent.suspend_thread, thread);
        if (ret != RT_EOK)
        {
            rt_hw_interrupt_enable(temp);
            return ret;
        }
        rt_thread_wakeup_set(thread, wakeup_receiver, (void*)ch);
        ch->stat = RT_IPC_STAT_WAIT;/* no valid suspended senders */
        thread->error = RT_EOK;
        if (time > 0)
        {
            rt_timer_control(&(thread->thread_timer),
                    RT_TIMER_CTRL_GET_FUNC,
                    &old_timeout_func);
            rt_timer_control(&(thread->thread_timer),
                    RT_TIMER_CTRL_SET_FUNC,
                    receiver_timeout);
            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                    RT_TIMER_CTRL_SET_TIME,
                    &time);
            rt_timer_start(&(thread->thread_timer));
        }
        rt_hw_interrupt_enable(temp);

        rt_schedule();              /* let the senders run */

        temp = rt_hw_interrupt_disable();
        if (old_timeout_func)
        {
            rt_timer_control(&(thread->thread_timer),
                    RT_TIMER_CTRL_SET_FUNC,
                    old_timeout_func);
        }
        ret = thread->error;
        if ( ret != RT_EOK)
        {
            rt_hw_interrupt_enable(temp);
            return ret;
        }
        /* If waked up, the received message has been store into the thread. */
        *data = ((rt_ipc_msg_t)(thread->msg_ret))->msg;    /* extract data */
        if (data->type == RT_CHANNEL_FD)
        {
            data->u.fd.fd = _ipc_msg_fd_new(data->u.fd.file);
        }
        _ipc_msg_free(thread->msg_ret);     /* put back the message to kernel */
        thread->msg_ret = RT_NULL;
    }

    rt_hw_interrupt_enable(temp);

    return RT_EOK;
}

rt_err_t rt_raw_channel_recv(rt_channel_t ch, rt_channel_msg_t data)
{
    return _rt_raw_channel_recv_timeout(ch, data, RT_WAITING_FOREVER);
}

rt_err_t rt_raw_channel_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, rt_int32_t time)
{
    return _rt_raw_channel_recv_timeout(ch, data, time);
}
/**
 * Peek a message from the specified IPC channel.
 */
rt_err_t rt_raw_channel_peek(rt_channel_t ch, rt_channel_msg_t data)
{
    return _rt_raw_channel_recv_timeout(ch, data, 0);
}

/* for API */

static int lwp_fd_new(int fdt_type)
{
    struct dfs_fdtable *fdt;

    if (fdt_type)
    {
        fdt = dfs_fdtable_get_global();
    }
    else
    {
        fdt = dfs_fdtable_get();
    }
    return fdt_fd_new(fdt);
}

static struct dfs_file *lwp_fd_get(int fdt_type, int fd)
{
    struct dfs_fdtable *fdt;

    if (fdt_type)
    {
        fdt = dfs_fdtable_get_global();
    }
    else
    {
        fdt = dfs_fdtable_get();
    }
    return fdt_fd_get(fdt, fd);
}

static void lwp_fd_release(int fdt_type, int fd)
{
    struct dfs_fdtable *fdt;

    if (fdt_type)
    {
        fdt = dfs_fdtable_get_global();
    }
    else
    {
        fdt = dfs_fdtable_get();
    }
    fdt_fd_release(fdt, fd);
}

static int _chfd_alloc(int fdt_type)
{
    /* create a BSD socket */
    int fd;

    /* allocate a fd */
    fd = lwp_fd_new(fdt_type);

    if (fd < 0)
    {
        return -1;
    }
    return fd;
}

static void _chfd_free(int fd, int fdt_type)
{
    struct dfs_file *d;

    d = lwp_fd_get(fdt_type, fd);
    if (d == RT_NULL)
    {
        return;
    }
    lwp_fd_release(fdt_type, fd);
}

/* for fops */
static int channel_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = POLLOUT;
    rt_channel_t ch;

    ch = (rt_channel_t)file->vnode->data;
    rt_poll_add(&(ch->reader_queue), req);
    if (ch->stat != RT_IPC_STAT_IDLE)
    {
        return mask;
    }
    if (!rt_list_isempty(&ch->wait_msg))
    {
        mask |= POLLIN;
    }
    return mask;
}

static int channel_fops_close(struct dfs_file *file)
{
    rt_channel_t ch;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ch = (rt_channel_t)file->vnode->data;
    if (file->vnode->ref_count == 1)
    {
        ch->ref--;
        if (ch->ref == 0)
        {
            /* wakeup all the suspended receivers and senders */
            rt_channel_list_resume_all(&ch->parent.suspend_thread);
            rt_channel_list_resume_all(&ch->wait_thread);

            /* all ipc msg will lost */
            rt_list_init(&ch->wait_msg);

            rt_object_delete(&ch->parent.parent);   /* release the IPC channel structure */
        }
    }
    rt_hw_interrupt_enable(level);
    return 0;
}

static const struct dfs_file_ops channel_fops =
{
    .close = channel_fops_close,    /* close */
    .poll = channel_fops_poll,      /* poll */
};

int lwp_channel_open(int fdt_type, const char *name, int flags)
{
    int fd;
    rt_channel_t ch = RT_NULL;
    struct dfs_file *d;

    fd = _chfd_alloc(fdt_type);     /* allocate an IPC channel descriptor */
    if (fd == -1)
    {
        goto quit;
    }
    d = lwp_fd_get(fdt_type, fd);
    d->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
    if (!d->vnode)
    {
        _chfd_free(fd, fdt_type);
        fd = -1;
        goto quit;
    }

    ch = rt_raw_channel_open(name, flags);
    if (ch)
    {
        /* initialize vnode */
        dfs_vnode_init(d->vnode, FT_USER, &channel_fops);
        d->flags = O_RDWR; /* set flags as read and write */

        /* set socket to the data of dfs_file */
        d->vnode->data = (void *)ch;
    }
    else
    {
        rt_free(d->vnode);
        d->vnode = RT_NULL;
        _chfd_free(fd, fdt_type);
        fd = -1;
    }
quit:
    return fd;
}

static rt_channel_t fd_2_channel(int fdt_type, int fd)
{
    struct dfs_file *d;

    d = lwp_fd_get(fdt_type, fd);
    if (d)
    {
        rt_channel_t ch;

        ch = (rt_channel_t)d->vnode->data;
        if (ch)
        {
            return ch;
        }
    }
    return RT_NULL;
}

rt_err_t lwp_channel_close(int fdt_type, int fd)
{
    rt_channel_t ch;
    struct dfs_file *d;
    struct dfs_vnode *vnode;

    d = lwp_fd_get(fdt_type, fd);
    if (!d)
    {
        return -RT_EIO;
    }

    vnode = d->vnode;
    if (!vnode)
    {
        return -RT_EIO;
    }

    ch = fd_2_channel(fdt_type, fd);
    if (!ch)
    {
        return -RT_EIO;
    }
    _chfd_free(fd, fdt_type);
    if (vnode->ref_count == 1)
    {
        rt_free(vnode);
        return rt_raw_channel_close(ch);
    }

    return 0;
}

rt_err_t lwp_channel_send(int fdt_type, int fd, rt_channel_msg_t data)
{
    rt_channel_t ch;
    ch = fd_2_channel(fdt_type, fd);
    if (ch)
    {
        return rt_raw_channel_send(ch, data);
    }
    return -RT_EIO;
}

rt_err_t lwp_channel_send_recv_timeout(int fdt_type, int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    rt_channel_t ch;
    ch = fd_2_channel(fdt_type, fd);
    if (ch)
    {
        return rt_raw_channel_send_recv_timeout(ch, data, data_ret, time);
    }
    return -RT_EIO;
}

rt_err_t lwp_channel_reply(int fdt_type, int fd, rt_channel_msg_t data)
{
    rt_channel_t ch;
    ch = fd_2_channel(fdt_type, fd);
    if (ch)
    {
        return rt_raw_channel_reply(ch, data);
    }
    return -RT_EIO;
}

rt_err_t lwp_channel_recv_timeout(int fdt_type, int fd, rt_channel_msg_t data, rt_int32_t time)
{
    rt_channel_t ch;
    ch = fd_2_channel(fdt_type, fd);
    if (ch)
    {
        return rt_raw_channel_recv_timeout(ch, data, time);
    }
    return -RT_EIO;
}

int rt_channel_open(const char *name, int flags)
{
    return lwp_channel_open(FDT_TYPE_KERNEL, name, flags);
}

rt_err_t rt_channel_close(int fd)
{
    return lwp_channel_close(FDT_TYPE_KERNEL, fd);
}

rt_err_t rt_channel_send(int fd, rt_channel_msg_t data)
{
    return lwp_channel_send(FDT_TYPE_KERNEL, fd, data);
}

rt_err_t rt_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    return lwp_channel_send_recv_timeout(FDT_TYPE_KERNEL, fd, data, data_ret, time);
}

rt_err_t rt_channel_send_recv(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret)
{
    return lwp_channel_send_recv_timeout(FDT_TYPE_KERNEL, fd, data, data_ret, RT_WAITING_FOREVER);
}

rt_err_t rt_channel_reply(int fd, rt_channel_msg_t data)
{
    return lwp_channel_reply(FDT_TYPE_KERNEL, fd, data);
}

rt_err_t rt_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    return lwp_channel_recv_timeout(FDT_TYPE_KERNEL, fd, data, time);
}

rt_err_t rt_channel_recv(int fd, rt_channel_msg_t data)
{
    return lwp_channel_recv_timeout(FDT_TYPE_KERNEL, fd, data, RT_WAITING_FOREVER);
}

rt_err_t rt_channel_peek(int fd, rt_channel_msg_t data)
{
    return lwp_channel_recv_timeout(FDT_TYPE_KERNEL, fd, data, 0);
}

#ifdef RT_USING_FINSH
static int list_channel(void)
{
    rt_base_t level;
    rt_channel_t *channels;
    rt_ubase_t index, count;
    struct rt_object *object;
    struct rt_list_node *node;
    struct rt_object_information *information;

    const char* stat_strs[] = {"idle", "wait", "active"};

    information = rt_object_get_information(RT_Object_Class_Channel);
    RT_ASSERT(information != RT_NULL);

    count = 0;
    level = rt_hw_interrupt_disable();
    /* get the count of IPC channels */
    for (node  = information->object_list.next;
            node != &(information->object_list);
            node  = node->next)
    {
        count ++;
    }
    rt_hw_interrupt_enable(level);

    if (count == 0) return 0;

    channels = (rt_channel_t *) rt_calloc(count, sizeof(rt_channel_t));
    if (channels == RT_NULL) return 0; /* out of memory */

    index = 0;
    level = rt_hw_interrupt_disable();
    /* retrieve pointer of IPC channels */
    for (node  = information->object_list.next;
            node != &(information->object_list);
            node  = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);

        channels[index] = (rt_channel_t)object;
        index ++;
    }
    rt_hw_interrupt_enable(level);

    rt_kprintf(" channel state\n");
    rt_kprintf("-------- -------\n");
    for (index = 0; index < count; index ++)
    {
        if (channels[index] != RT_NULL)
        {
            rt_kprintf("%-*.s", RT_NAME_MAX, channels[index]->parent.parent.name);
            if (channels[index]->stat < 3)
                rt_kprintf(" %s\n", stat_strs[channels[index]->stat]);
        }
    }

    rt_free(channels);

    return 0;
}
MSH_CMD_EXPORT(list_channel, list IPC channel information);
#endif

