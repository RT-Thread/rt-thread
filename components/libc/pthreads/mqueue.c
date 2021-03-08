/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <string.h>
#include "mqueue.h"
#include "pthread_internal.h"

static mqd_t posix_mq_list = RT_NULL;
static struct rt_semaphore posix_mq_lock;
void posix_mq_system_init()
{
    rt_sem_init(&posix_mq_lock, "pmq", 1, RT_IPC_FLAG_FIFO);
}

rt_inline void posix_mq_insert(mqd_t pmq)
{
    pmq->next = posix_mq_list;
    posix_mq_list = pmq;
}

static void posix_mq_delete(mqd_t pmq)
{
    mqd_t iter;
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

static mqd_t posix_mq_find(const char* name)
{
    mqd_t iter;
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

int mq_setattr(mqd_t                 mqdes,
               const struct mq_attr *mqstat,
               struct mq_attr       *omqstat)
{
    rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_setattr);

int mq_getattr(mqd_t mqdes, struct mq_attr *mqstat)
{
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
    mqd_t mqdes;
    va_list arg;
    mode_t mode;
    struct mq_attr *attr = RT_NULL;

    /* lock posix mqueue list */
    rt_sem_take(&posix_mq_lock, RT_WAITING_FOREVER);

    mqdes = RT_NULL;
    if (oflag & O_CREAT)
    {
        va_start(arg, oflag);
        mode = (mode_t)va_arg(arg, unsigned int);
        mode = mode;
        attr = (struct mq_attr *)va_arg(arg, struct mq_attr *);
        va_end(arg);

        if (oflag & O_EXCL)
        {
            if (posix_mq_find(name) != RT_NULL)
            {
                rt_set_errno(EEXIST);
                goto __return;
            }
        }
        mqdes = (mqd_t) rt_malloc (sizeof(struct mqdes));
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
        /* find mqueue */
        mqdes = posix_mq_find(name);
        if (mqdes != RT_NULL)
        {
            mqdes->refcount ++; /* increase reference count */
        }
        else
        {
            rt_set_errno(ENOENT);
            goto __return;
        }
    }
    rt_sem_release(&posix_mq_lock);

    return mqdes;

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
    return RT_NULL;
}
RTM_EXPORT(mq_open);

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio)
{
    rt_err_t result;

    if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_mq_recv(mqdes->mq, msg_ptr, msg_len, RT_WAITING_FOREVER);
    if (result == RT_EOK)
        return msg_len;

    rt_set_errno(EBADF);
    return -1;
}
RTM_EXPORT(mq_receive);

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
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

ssize_t mq_timedreceive(mqd_t                  mqdes,
                        char                  *msg_ptr,
                        size_t                 msg_len,
                        unsigned              *msg_prio,
                        const struct timespec *abs_timeout)
{
    int tick;
    rt_err_t result;

    /* parameters check */
    if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    tick = clock_time_to_tick(abs_timeout);

    result = rt_mq_recv(mqdes->mq, msg_ptr, msg_len, tick);
    if (result == RT_EOK)
        return msg_len;

    if (result == -RT_ETIMEOUT)
        rt_set_errno(ETIMEDOUT);
    else
        rt_set_errno(EBADMSG);

    return -1;
}
RTM_EXPORT(mq_timedreceive);

int mq_timedsend(mqd_t                  mqdes,
                 const char            *msg_ptr,
                 size_t                 msg_len,
                 unsigned               msg_prio,
                 const struct timespec *abs_timeout)
{
    /* RT-Thread does not support timed send */
    return mq_send(mqdes, msg_ptr, msg_len, msg_prio);
}
RTM_EXPORT(mq_timedsend);

int mq_notify(mqd_t mqdes, const struct sigevent *notification)
{
    rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_notify);

int mq_close(mqd_t mqdes)
{
    if (mqdes == RT_NULL)
    {
        rt_set_errno(EINVAL);

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

int mq_unlink(const char *name)
{
    mqd_t pmq;

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
