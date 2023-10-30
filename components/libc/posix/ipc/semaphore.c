/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <rtthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "semaphore.h"

static sem_t *posix_sem_list = RT_NULL;
static struct rt_semaphore posix_sem_lock;

/**
 * @brief   Initialize the POSIX semaphore system.
 *
 * @return  0 on success, or an error code on failure.
 */
static int posix_sem_system_init(void)
{
    rt_sem_init(&posix_sem_lock, "psem", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_COMPONENT_EXPORT(posix_sem_system_init);

/**
 * @brief   Insert a POSIX semaphore into the list of semaphores.
 *
 * @param   psem    is the POSIX semaphore to be inserted.
 */
rt_inline void posix_sem_insert(sem_t *psem)
{
    psem->next = posix_sem_list;
    posix_sem_list = psem;
}

/**
 * @brief   Delete a POSIX semaphore.
 *
 * @param   psem    is the POSIX semaphore to be deleted.
 */
static void posix_sem_delete(sem_t *psem)
{
    sem_t *iter;
    if (posix_sem_list == psem)
    {
        posix_sem_list = psem->next;

        rt_sem_delete(psem->sem);

        if (psem->unamed == 0)
            rt_free(psem);

        return;
    }
    for (iter = posix_sem_list; iter->next != RT_NULL; iter = iter->next)
    {
        if (iter->next == psem)
        {
            /* Delete this semaphore */
            if (psem->next != RT_NULL)
                iter->next = psem->next;
            else
                iter->next = RT_NULL;

            /* Delete RT-Thread semaphore */
            rt_sem_delete(psem->sem);

            if (psem->unamed == 0)
                rt_free(psem);

            return;
        }
    }
}

/**
 * @brief   Find a POSIX semaphore by name.
 *
 * @param   name    is the name of the semaphore to find.
 *
 * @return  A pointer to the found semaphore, or RT_NULL if not found.
 */
static sem_t *posix_sem_find(const char *name)
{
    sem_t *iter;
    rt_object_t object;

    for (iter = posix_sem_list; iter != RT_NULL; iter = iter->next)
    {
        object = (rt_object_t)iter->sem;

        if (strncmp(object->name, name, RT_NAME_MAX) == 0)
        {
            return iter;
        }
    }

    return RT_NULL;
}

/**
 * @brief   Close a POSIX semaphore.
 *
 * @param   sem     is the POSIX semaphore to be closed.
 *
 * @return  0 on success, or -1 on failure.
 */
int sem_close(sem_t *sem)
{
    if (sem == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    /* Lock the POSIX semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    sem->refcount--;
    if (sem->refcount == 0)
    {
        /* Delete from the POSIX semaphore list */
        if (sem->unlinked)
            posix_sem_delete(sem);
        sem = RT_NULL;
    }
    rt_sem_release(&posix_sem_lock);

    return 0;
}
RTM_EXPORT(sem_close);

/**
 * @brief   Destroy an unnamed POSIX semaphore.
 *
 * @param   sem     is the POSIX semaphore to be destroyed.
 *
 * @return  0 on success, or -1 on failure.
 */
int sem_destroy(sem_t *sem)
{
    if ((!sem) || !(sem->unamed))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    /* Lock the POSIX semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    if (rt_list_len(&sem->sem->parent.suspend_thread) != 0)
    {
        rt_sem_release(&posix_sem_lock);
        rt_set_errno(EBUSY);
        return -1;
    }

    /* Destroy an unnamed POSIX semaphore */
    posix_sem_delete(sem);
    rt_sem_release(&posix_sem_lock);

    return 0;
}
RTM_EXPORT(sem_destroy);

/**
 * @brief   Unlink (remove) a named POSIX semaphore by name.
 *
 * @param   name    is the name of the semaphore to be unlinked.
 *
 * @return  0 on success, or -1 on failure.
 */
int sem_unlink(const char *name)
{
    sem_t *psem;

    /* Lock the POSIX semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    psem = posix_sem_find(name);
    if (psem != RT_NULL)
    {
        psem->unlinked = 1;
        if (psem->refcount == 0)
        {
            /* Remove this semaphore */
            posix_sem_delete(psem);
        }
        rt_sem_release(&posix_sem_lock);
        return 0;
    }
    rt_sem_release(&posix_sem_lock);

    /* No such entry */
    rt_set_errno(ENOENT);

    return -1;
}

RTM_EXPORT(sem_unlink);

/**
 * @brief   Get the value of a POSIX semaphore.
 *
 * @param   sem     is the POSIX semaphore.
 * @param   sval    is a pointer to store the value.
 *
 * @return  0 on success, or -1 on failure.
 */
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

/**
 * @brief   Initialize a POSIX semaphore.
 *
 * @param   sem     is the POSIX semaphore to be initialized.
 * @param   pshared is not used in this implementation.
 * @param   value   is the initial value of the semaphore.
 *
 * @return  0 on success, or -1 on failure.
 */
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
    if (sem->sem == RT_NULL)
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

/**
 * @brief   Open or create a POSIX semaphore by name.
 *
 * @param   name    is the name of the semaphore.
 * @param   oflag   specifies the flags for opening or creating.
 *
 * @return  A pointer to the semaphore on success, or RT_NULL on failure.
 */
sem_t *sem_open(const char *name, int oflag, ...)
{
    sem_t *sem;
    va_list arg;
    mode_t mode;
    unsigned int value;

    sem = RT_NULL;

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    if (oflag & O_CREAT)
    {
        va_start(arg, oflag);
        mode = (mode_t)va_arg(arg, unsigned int);
        mode = mode;
        value = va_arg(arg, unsigned int);
        va_end(arg);

        if (oflag & O_EXCL)
        {
            if (posix_sem_find(name) != RT_NULL)
            {
                rt_set_errno(EEXIST);
                goto __return;
            }
        }
        sem = (sem_t *)rt_malloc(sizeof(struct posix_sem));
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
            sem->refcount++; /* increase reference count */
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

/**
 * @brief   Post (unlock) a POSIX semaphore.
 *
 * @param   sem     is the POSIX semaphore to be posted.
 *
 * @return  0 on success, or -1 on failure.
 */
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

/**
 * @brief   Wait for a POSIX semaphore with a timeout.
 *
 * @param   sem             is the POSIX semaphore to wait for.
 * @param   abs_timeout      is the absolute timeout.
 *
 * @return  0 on success, or -1 on failure.
 */
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
{
    rt_err_t result;
    rt_int32_t tick;

    if (!sem || !abs_timeout)
        return EINVAL;

    /* calculate os tick */
    tick = rt_timespec_to_tick(abs_timeout);

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

/**
 * @brief   Try to wait for a POSIX semaphore without blocking.
 *
 * @param   sem     is the POSIX semaphore to wait for.
 *
 * @return  0 on success, or -1 on failure.
 */
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

/**
 * @brief   Wait for a POSIX semaphore indefinitely.
 *
 * @param   sem     is the POSIX semaphore to wait for.
 *
 * @return  0 on success, or -1 on failure.
 */
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
