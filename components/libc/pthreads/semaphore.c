/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <rtthread.h>
#include <string.h>
#include "semaphore.h"
#include "pthread_internal.h"

static sem_t *posix_sem_list = RT_NULL;
static struct rt_semaphore posix_sem_lock;
void posix_sem_system_init()
{
    rt_sem_init(&posix_sem_lock, "psem", 1, RT_IPC_FLAG_FIFO);
}

rt_inline void posix_sem_insert(sem_t *psem)
{
    psem->next = posix_sem_list;
    posix_sem_list = psem;
}

static void posix_sem_delete(sem_t *psem)
{
    sem_t *iter;
    if (posix_sem_list == psem)
    {
        posix_sem_list = psem->next;

        rt_sem_delete(psem->sem);
        rt_free(psem);

        return;
    }
    for (iter = posix_sem_list; iter->next != RT_NULL; iter = iter->next)
    {
        if (iter->next == psem)
        {
            /* delete this mq */
            if (psem->next != RT_NULL)
                iter->next = psem->next;
            else
                iter->next = RT_NULL;

            /* delete RT-Thread mqueue */
            rt_sem_delete(psem->sem);
            rt_free(psem);

            return ;
        }
    }
}

static sem_t *posix_sem_find(const char* name)
{
    sem_t *iter;
    rt_object_t object;

    for (iter = posix_sem_list; iter != RT_NULL; iter = iter->next)
    {
        object = (rt_object_t)&(iter->sem);

        if (strncmp(object->name, name, RT_NAME_MAX) == 0)
        {
            return iter;
        }
    }

    return RT_NULL;
}

int sem_close(sem_t *sem)
{
    if (sem == RT_NULL)
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    sem->refcount --;
    if (sem->refcount == 0)
    {
        /* delete from posix semaphore list */
        if (sem->unlinked)
            posix_sem_delete(sem);
        sem = RT_NULL;
    }
    rt_sem_release(&posix_sem_lock);

    return 0;
}
RTM_EXPORT(sem_close);

int sem_destroy(sem_t *sem)
{
    rt_err_t result;

    if ((!sem) || !(sem->unamed))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    result = rt_sem_trytake(sem->sem);
    if (result != RT_EOK)
    {
        rt_sem_release(&posix_sem_lock);
        rt_set_errno(EBUSY);

        return -1;
    }

    /* destroy an unamed posix semaphore */
    posix_sem_delete(sem);
    rt_sem_release(&posix_sem_lock);

    return 0;
}
RTM_EXPORT(sem_destroy);

int sem_unlink(const char *name)
{
    sem_t *psem;

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    psem = posix_sem_find(name);
    if (psem != RT_NULL)
    {
        psem->unlinked = 1;
        if (psem->refcount == 0)
        {
            /* remove this semaphore */
            posix_sem_delete(psem);
        }
        rt_sem_release(&posix_sem_lock);

        return 0;
    }
    rt_sem_release(&posix_sem_lock);

    /* no this entry */
    rt_set_errno(ENOENT);

    return -1;
}
RTM_EXPORT(sem_unlink);

int sem_getvalue(sem_t *sem, int *sval)
{
    if (!sem || !sval)
    {
        rt_set_errno(EINVAL);

        return -1;
    }
    *sval = sem->sem->value;

    return 0;
}
RTM_EXPORT(sem_getvalue);

int sem_init(sem_t *sem, int pshared, unsigned int value)
{
    char name[RT_NAME_MAX];
    static rt_uint16_t psem_number = 0;

    if (sem == RT_NULL)
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    rt_snprintf(name, sizeof(name), "psem%02d", psem_number++);
    sem->sem = rt_sem_create(name, value, RT_IPC_FLAG_FIFO);
    if (sem == RT_NULL)
    {
        rt_set_errno(ENOMEM);

        return -1;
    }

    /* initialize posix semaphore */
    sem->refcount = 1;
    sem->unlinked = 0;
    sem->unamed = 1;
    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    posix_sem_insert(sem);
    rt_sem_release(&posix_sem_lock);

    return 0;
}
RTM_EXPORT(sem_init);

sem_t *sem_open(const char *name, int oflag, ...)
{
    sem_t* sem;
    va_list arg;
    mode_t mode;
    unsigned int value;

    sem = RT_NULL;

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    if (oflag & O_CREAT)
    {
        va_start(arg, oflag);
        mode = (mode_t) va_arg( arg, unsigned int); mode = mode;
        value = va_arg( arg, unsigned int);
        va_end(arg);

        if (oflag & O_EXCL)
        {
            if (posix_sem_find(name) != RT_NULL)
            {
                rt_set_errno(EEXIST);
                goto __return;
            }
        }
        sem = (sem_t*) rt_malloc (sizeof(struct posix_sem));
        if (sem == RT_NULL)
        {
            rt_set_errno(ENFILE);
            goto __return;
        }

        /* create RT-Thread semaphore */
        sem->sem = rt_sem_create(name, value, RT_IPC_FLAG_FIFO);
        if (sem->sem == RT_NULL) /* create failed */
        {
            rt_set_errno(ENFILE);
            goto __return;
        }
        /* initialize reference count */
        sem->refcount = 1;
        sem->unlinked = 0;
        sem->unamed = 0;

        /* insert semaphore to posix semaphore list */
        posix_sem_insert(sem);
    }
    else
    {
        /* find semaphore */
        sem = posix_sem_find(name);
        if (sem != RT_NULL)
        {
            sem->refcount ++; /* increase reference count */
        }
        else
        {
            rt_set_errno(ENOENT);
            goto __return;
        }
    }
    rt_sem_release(&posix_sem_lock);

    return sem;

__return:
    /* release lock */
    rt_sem_release(&posix_sem_lock);

    /* release allocated memory */
    if (sem != RT_NULL)
    {
        /* delete RT-Thread semaphore */
        if (sem->sem != RT_NULL)
            rt_sem_delete(sem->sem);
        rt_free(sem);
    }

    return RT_NULL;
}
RTM_EXPORT(sem_open);

int sem_post(sem_t *sem)
{
    rt_err_t result;

    if (!sem)
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_sem_release(sem->sem);
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EINVAL);

    return -1;
}
RTM_EXPORT(sem_post);

int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
{
    rt_err_t result;
    rt_int32_t tick;

    if (!sem || !abs_timeout)
        return EINVAL;

    /* calculate os tick */
    tick = clock_time_to_tick(abs_timeout);

    result = rt_sem_take(sem->sem, tick);
    if (result == -RT_ETIMEOUT)
    {
        rt_set_errno(ETIMEDOUT);

        return -1;
    }
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EINTR);

    return -1;
}
RTM_EXPORT(sem_timedwait);

int sem_trywait(sem_t *sem)
{
    rt_err_t result;

    if (!sem)
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_sem_take(sem->sem, 0);
    if (result == -RT_ETIMEOUT)
    {
        rt_set_errno(EAGAIN);

        return -1;
    }
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EINTR);

    return -1;
}
RTM_EXPORT(sem_trywait);

int sem_wait(sem_t *sem)
{
    rt_err_t result;

    if (!sem)
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    result = rt_sem_take(sem->sem, RT_WAITING_FOREVER);
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EINTR);

    return -1;
}
RTM_EXPORT(sem_wait);

