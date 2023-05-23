/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <string.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <rtthread.h>
#include <limits.h>
#include "mqueue.h"

static mqdes_t posix_mq_list = RT_NULL;
static struct rt_semaphore posix_mq_lock;

/* initialize posix mqueue */
static int posix_mq_system_init(void)
{
    rt_sem_init(&posix_mq_lock, "pmq", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_COMPONENT_EXPORT(posix_mq_system_init);

rt_inline void posix_mq_insert(mqdes_t pmq)
{
    if (posix_mq_list == RT_NULL)
        pmq->mq_id = 1;
    else
        pmq->mq_id = posix_mq_list->mq_id + 1;
    pmq->next = posix_mq_list;
    posix_mq_list = pmq;
}

static void posix_mq_delete(mqdes_t pmq)
{
    mqdes_t iter;
    if (posix_mq_list == pmq)
    {
        posix_mq_list = pmq->next;

        rt_mq_delete(pmq->mq);
        rt_free(pmq);

        return;
    }
    for (iter = posix_mq_list; iter->next != RT_NULL; iter = iter->next)
    {
        if (iter->next == pmq)
        {
            /* delete this mq */
            if (pmq->next != RT_NULL)
                iter->next = pmq->next;
            else
                iter->next = RT_NULL;

            /* delete RT-Thread mqueue */
            rt_mq_delete(pmq->mq);
            rt_free(pmq);

            return ;
        }
    }
}

static mqdes_t posix_mq_find(const char *name)
{
    mqdes_t iter;
    rt_object_t object;

    for (iter = posix_mq_list; iter != RT_NULL; iter = iter->next)
    {
        object = (rt_object_t)(iter->mq);

        if (strncmp(object->name, name, RT_NAME_MAX) == 0)
        {
            return iter;
        }
    }

    return RT_NULL;
}

static mqdes_t posix_mq_id_find(mqd_t id)
{
    for (mqdes_t iter = posix_mq_list; iter != RT_NULL; iter = iter->next)
        if (iter->mq_id == id)
            return iter;
    return RT_NULL;
}

int mq_setattr(mqd_t                 id,
               const struct mq_attr *mqstat,
               struct mq_attr       *omqstat)
{
    if (mqstat == RT_NULL)
        return mq_getattr(id, omqstat);
    else
        rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_setattr);

int mq_getattr(mqd_t id, struct mq_attr *mqstat)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    if ((mqdes == RT_NULL) || mqstat == RT_NULL)
    {
        rt_set_errno(EBADF);

        return -1;
    }

    mqstat->mq_maxmsg = mqdes->mq->max_msgs;
    mqstat->mq_msgsize = mqdes->mq->msg_size;
    mqstat->mq_curmsgs = 0;
    mqstat->mq_flags = 0;

    return 0;
}
RTM_EXPORT(mq_getattr);

mqd_t mq_open(const char *name, int oflag, ...)
{
    va_list arg;
    mode_t mode;
    mqdes_t mqdes = RT_NULL;
    struct mq_attr *attr = RT_NULL;

    /* lock posix mqueue list */
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    int len = rt_strlen(name);
    if (len > RT_NAME_MAX)
    {
        rt_set_errno(ENAMETOOLONG);
        goto __return;
    }

    mqdes = posix_mq_find(name);
    if (mqdes != RT_NULL)
    {
        if (oflag & O_CREAT && oflag & O_EXCL)
        {
            rt_set_errno(EEXIST);
            rt_sem_release(&posix_mq_lock);
            return (mqd_t)(-1);
        }
        mqdes->refcount++; /* increase reference count */
    }
    else if (oflag & O_CREAT)
    {
        va_start(arg, oflag);
        mode = (mode_t)va_arg(arg, unsigned int);
        mode = (mode_t)mode; /* self-assignment avoids compiler optimization */
        attr = (struct mq_attr *)va_arg(arg, struct mq_attr *);
        attr = (struct mq_attr *)attr; /* self-assignment avoids compiler optimization */
        va_end(arg);

        if (attr->mq_maxmsg <= 0)
        {
            rt_set_errno(EINVAL);
            goto __return;
        }

        mqdes = (mqdes_t) rt_malloc (sizeof(struct mqdes));
        if (mqdes == RT_NULL)
        {
            rt_set_errno(ENFILE);
            goto __return;
        }

        /* create RT-Thread message queue */
        mqdes->mq = rt_mq_create(name, attr->mq_msgsize, attr->mq_maxmsg, RT_IPC_FLAG_FIFO);
        if (mqdes->mq == RT_NULL) /* create failed */
        {
            rt_set_errno(ENFILE);
            goto __return;
        }
        /* initialize reference count */
        mqdes->refcount = 1;
        mqdes->unlinked = 0;

        /* insert mq to posix mq list */
        posix_mq_insert(mqdes);
    }
    else
    {
        rt_set_errno(ENOENT);
        goto __return;
    }
    rt_sem_release(&posix_mq_lock);

    return (mqd_t)(mqdes->mq_id);

__return:
    /* release lock */
    rt_sem_release(&posix_mq_lock);

    /* release allocated memory */
    if (mqdes != RT_NULL)
    {
        if (mqdes->mq != RT_NULL)
        {
            /* delete RT-Thread message queue */
            rt_mq_delete(mqdes->mq);
        }
        rt_free(mqdes);
    }
    return (mqd_t)(-1);
}
RTM_EXPORT(mq_open);

ssize_t mq_receive(mqd_t id, char *msg_ptr, size_t msg_len, unsigned *msg_prio)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    rt_err_t result;

    if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_mq_recv(mqdes->mq, msg_ptr, msg_len, RT_WAITING_FOREVER);
    if (result == RT_EOK)
        return rt_strlen(msg_ptr);

    rt_set_errno(EBADF);
    return -1;
}
RTM_EXPORT(mq_receive);

int mq_send(mqd_t id, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    rt_err_t result;

    if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_mq_send(mqdes->mq, (void*)msg_ptr, msg_len);
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EBADF);

    return -1;
}
RTM_EXPORT(mq_send);

ssize_t mq_timedreceive(mqd_t                  id,
                        char                  *msg_ptr,
                        size_t                 msg_len,
                        unsigned              *msg_prio,
                        const struct timespec *abs_timeout)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    int tick = 0;
    rt_err_t result;

    /* parameters check */
    if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);

        return -1;
    }
    if (abs_timeout != RT_NULL)
        tick = rt_timespec_to_tick(abs_timeout);

    result = rt_mq_recv(mqdes->mq, msg_ptr, msg_len, tick);
    if (result == RT_EOK)
        return rt_strlen(msg_ptr);

    if (result == -RT_ETIMEOUT)
        rt_set_errno(ETIMEDOUT);
    else if (result == -RT_ERROR)
        rt_set_errno(EMSGSIZE);
    else
        rt_set_errno(EBADMSG);

    return -1;
}
RTM_EXPORT(mq_timedreceive);

int mq_timedsend(mqd_t                  id,
                 const char            *msg_ptr,
                 size_t                 msg_len,
                 unsigned               msg_prio,
                 const struct timespec *abs_timeout)
{
    /* RT-Thread does not support timed send */
    return mq_send(id, msg_ptr, msg_len, msg_prio);
}
RTM_EXPORT(mq_timedsend);

int mq_notify(mqd_t id, const struct sigevent *notification)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    if (mqdes == RT_NULL || mqdes->refcount == 0)
    {
        rt_set_errno(EBADF);
        return -1;
    }
    rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_notify);

int mq_close(mqd_t id)
{
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes_t mqdes = posix_mq_id_find(id);
    rt_sem_release(&posix_mq_lock);
    if (mqdes == RT_NULL)
    {
        rt_set_errno(EBADF);
        return -1;
    }

    /* lock posix mqueue list */
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    mqdes->refcount --;
    if (mqdes->refcount == 0)
    {
        /* delete from posix mqueue list */
        if (mqdes->unlinked)
            posix_mq_delete(mqdes);
    }
    rt_sem_release(&posix_mq_lock);

    return 0;
}
RTM_EXPORT(mq_close);

/**
 * @brief    This function will remove a message queue (REALTIME).
 *
 * @note    The mq_unlink() function shall remove the message queue named by the string name. 
 *          If one or more processes have the message queue open when mq_unlink() is called, 
 *          destruction of the message queue shall be postponed until all references to the message queue have been closed. 
 *          However, the mq_unlink() call need not block until all references have been closed; it may return immediately.
 * 
 *          After a successful call to mq_unlink(), reuse of the name shall subsequently cause mq_open() to behave as if 
 *          no message queue of this name exists (that is, mq_open() will fail if O_CREAT is not set, 
 *          or will create a new message queue if O_CREAT is set).
 * 
 * @param    name  is the name of the message queue.
 *
 * @return   Upon successful completion, the function shall return a value of zero. 
 *           Otherwise, the named message queue shall be unchanged by this function call, 
 *           and the function shall return a value of -1 and set errno to indicate the error.
 *
 * @warning  This function can ONLY be called in the thread context, you can use RT_DEBUG_IN_THREAD_CONTEXT to
 *           check the context.
 *           The mq_unlink() function shall fail if:
 *              [EACCES]
 *              Permission is denied to unlink the named message queue.
 *              [EINTR]
 *              The call to mq_unlink() blocked waiting for all references to the named message queue to be closed and a signal interrupted the call.
 *              [ENOENT]
 *              The named message queue does not exist.
 *           The mq_unlink() function may fail if:
 *              [ENAMETOOLONG]
 *              The length of the name argument exceeds {_POSIX_PATH_MAX} on systems that do not support the XSI option 
 *              or exceeds {_XOPEN_PATH_MAX} on XSI systems,or has a pathname component that is longer than {_POSIX_NAME_MAX} on systems that do 
 *              not support the XSI option or longer than {_XOPEN_NAME_MAX} on XSI systems.A call to mq_unlink() with a name argument that contains 
 *              the same message queue name as was previously used in a successful mq_open() call shall not give an [ENAMETOOLONG] error.
 */
int mq_unlink(const char *name)
{
    mqdes_t pmq;

    /* lock posix mqueue list */
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);
    pmq = posix_mq_find(name);
    if (pmq != RT_NULL)
    {
        pmq->unlinked = 1;
        if (pmq->refcount == 0)
        {
            /* remove this mqueue */
            posix_mq_delete(pmq);
        }
        rt_sem_release(&posix_mq_lock);

        return 0;
    }
    rt_sem_release(&posix_mq_lock);

    /* no this entry */
    rt_set_errno(ENOENT);

    return -1;
}
RTM_EXPORT(mq_unlink);
