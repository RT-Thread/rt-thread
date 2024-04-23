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

/* initialize posix semaphore */
static int posix_sem_system_init(void)
{
    rt_sem_init(&posix_sem_lock, "psem", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_COMPONENT_EXPORT(posix_sem_system_init);

/**
 * @brief   Inserts a semaphore into the linked list of semaphores.
 * @param   psem Pointer to the semaphore structure to be inserted.
 *
 * @note    This function inserts the specified semaphore into a linked list of semaphores.
 *          The newly inserted semaphore becomes the head of the list.
 *          It updates the 'next' pointer of the semaphore structure to link it to the
 *          current head of the list and then sets the head of the list to point to the
 *          newly inserted semaphore.
 */
rt_inline void posix_sem_insert(sem_t *psem)
{
    psem->next = posix_sem_list;
    posix_sem_list = psem;
}

/**
 * @brief   Deletes a semaphore from the linked list of semaphores.
 * @param   psem Pointer to the semaphore structure to be deleted.
 *
 * @note    This function deletes the specified semaphore from a linked list of semaphores.
 *          If the semaphore to be deleted is the head of the list, it updates the head of the list
 *          to point to the next semaphore. Otherwise, it traverses the list to find the semaphore
 *          to be deleted and updates the 'next' pointer of the preceding semaphore to skip over
 *          the semaphore to be deleted.
 *          After deleting the semaphore, it also deletes the underlying RT-Thread semaphore if it exists
 *          and frees the memory associated with the semaphore structure if it's not unnamed.
 */
static void posix_sem_delete(sem_t *psem)
{
    sem_t *iter;
    if (posix_sem_list == psem)
    {
        posix_sem_list = psem->next;

        rt_sem_delete(psem->sem);

        if(psem->unamed == 0)
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

            if(psem->unamed == 0)
                rt_free(psem);

            return ;
        }
    }
}

/**
 * @brief   Finds a semaphore by name in the linked list of semaphores.
 * @param   name Pointer to the name of the semaphore to be found.
 * @return  Pointer to the semaphore structure if found; otherwise, RT_NULL.
 *
 * @note    This function searches for a semaphore with the specified name in the linked list of semaphores.
 *          It iterates through the list and compares the name of each semaphore with the given name.
 *          If a semaphore with a matching name is found, a pointer to its structure is returned.
 *          Otherwise, RT_NULL is returned to indicate that no semaphore with the given name was found.
 */
static sem_t *posix_sem_find(const char* name)
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
 * @brief   Closes a POSIX semaphore.
 * @param   sem Pointer to the semaphore to be closed.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function decreases the reference count of the specified semaphore.
 *          If the reference count reaches zero, the semaphore is removed from the list
 *          of POSIX semaphores if it was unlinked. The memory associated with the semaphore
 *          is not immediately freed; instead, it will be freed when the last reference to
 *          the semaphore is released.
 */
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

/**
 * @brief   Destroys a POSIX semaphore.
 * @param   sem Pointer to the semaphore to be destroyed.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function destroys an unnamed POSIX semaphore.
 *          It first checks if the semaphore pointer is valid and if the semaphore is unnamed.
 *          If the semaphore is still in use (i.e., there are threads waiting on it),
 *          the function returns with an error code (EBUSY) without destroying the semaphore.
 *          Otherwise, it removes the semaphore from the list of POSIX semaphores and frees
 *          the memory associated with the semaphore structure.
 */
int sem_destroy(sem_t *sem)
{
    if ((!sem) || !(sem->unamed))
    {
        rt_set_errno(EINVAL);

        return -1;
    }

    /* lock posix semaphore list */
    rt_sem_take(&posix_sem_lock, RT_WAITING_FOREVER);
    if(rt_list_len(&sem->sem->parent.suspend_thread) != 0)
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

/**
 * @brief   Unlinks a named POSIX semaphore.
 * @param   name Pointer to the name of the semaphore to be unlinked.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function unlinks a named POSIX semaphore identified by the given name.
 *          It first searches for the semaphore with the specified name in the list of
 *          POSIX semaphores. If the semaphore is found, it marks the semaphore as unlinked.
 *          If the reference count of the semaphore is zero, indicating that no threads are
 *          currently using the semaphore, it removes the semaphore from the list and frees
 *          the associated memory. Otherwise, the semaphore is not immediately removed; it
 *          will be removed when its reference count reaches zero.
 */
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

/**
 * @brief   Retrieves the value of a POSIX semaphore.
 * @param   sem Pointer to the semaphore.
 * @param   sval Pointer to an integer where the semaphore value will be stored.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function retrieves the current value of the specified POSIX semaphore.
 *          It copies the semaphore value into the memory location pointed to by sval.
 *          If either sem or sval is a null pointer, the function sets errno to EINVAL
 *          to indicate an invalid argument and returns -1.
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
 * @brief   Initializes a POSIX semaphore.
 * @param   sem Pointer to the semaphore structure to be initialized.
 * @param   pshared Flag indicating whether the semaphore is to be shared between processes.
 * @param   value Initial value of the semaphore.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function initializes a POSIX semaphore with the specified initial value.
 *          If sem is a null pointer, the function sets errno to EINVAL to indicate an invalid argument and returns -1.
 *          The pshared parameter is not used in this implementation, as all semaphores are created as local (unshared).
 *          The value parameter specifies the initial value of the semaphore.
 *          The semaphore is given a unique name using a static counter, and it is created using the RT-Thread semaphore
 *          creation function rt_sem_create(). If memory allocation fails during semaphore creation, errno is set to ENOMEM.
 *          After successful initialization, the semaphore structure is inserted into the linked list of POSIX semaphores.
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
 * @brief   Opens or creates a POSIX semaphore.
 * @param   name Pointer to the name of the semaphore.
 * @param   oflag Bitwise OR of flags indicating the operation mode.
 * @param   ... Additional arguments (optional).
 * @return  Upon successful completion, returns a pointer to the semaphore;
 *          otherwise, returns RT_NULL and sets errno to indicate the error.
 *
 * @note    This function opens or creates a POSIX semaphore specified by the name argument.
 *          If the oflag argument includes O_CREAT, the semaphore is created if it does not already exist.
 *          Additional arguments may include the mode (not used in this implementation) and the initial value of the semaphore.
 *          If the oflag argument includes O_EXCL along with O_CREAT, the function fails if the semaphore already exists.
 *          If memory allocation fails during semaphore creation, errno is set to ENFILE.
 *          After successful creation or opening, the semaphore's reference count is incremented, and it is inserted into
 *          the linked list of POSIX semaphores. If the semaphore already exists and is successfully opened, its reference
 *          count is incremented. If the semaphore cannot be opened or created for any reason, errno is set to indicate the error,
 *          and the function returns RT_NULL.
 */
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

/**
 * @brief   Posts (increments) a POSIX semaphore.
 * @param   sem Pointer to the semaphore.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function increments the value of the specified POSIX semaphore by one.
 *          If sem is a null pointer, errno is set to EINVAL to indicate an invalid argument, and the function returns -1.
 *          The semaphore is released using the RT-Thread semaphore release function rt_sem_release().
 *          If the semaphore release operation succeeds, the function returns 0; otherwise, errno is set to EINVAL,
 *          indicating an error, and the function returns -1.
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
 * @brief   Waits for a POSIX semaphore with a timeout.
 * @param   sem Pointer to the semaphore.
 * @param   abs_timeout Pointer to the absolute timeout value.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function waits for the specified POSIX semaphore to become available within the specified timeout.
 *          If either sem or abs_timeout is a null pointer, the function returns EINVAL, indicating an invalid argument.
 *          The abs_timeout parameter specifies an absolute timeout value based on the CLOCK_REALTIME clock.
 *          The timeout is converted to RT-Thread ticks using the rt_timespec_to_tick() function.
 *          The semaphore is waited upon using the RT-Thread semaphore take function rt_sem_take().
 *          If the semaphore is successfully acquired within the specified timeout, the function returns 0.
 *          If the timeout expires before the semaphore becomes available, errno is set to ETIMEDOUT,
 *          and the function returns -1. If the semaphore wait operation is interrupted by a signal,
 *          errno is set to EINTR, and the function returns -1.
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
 * @brief   Attempts to wait for a POSIX semaphore without blocking.
 * @param   sem Pointer to the semaphore.
 * @return  Upon successful completion, returns 0 if the semaphore was acquired;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function attempts to acquire the specified POSIX semaphore without blocking.
 *          If sem is a null pointer, errno is set to EINVAL to indicate an invalid argument, and the function returns -1.
 *          The semaphore is waited upon using the RT-Thread semaphore take function rt_sem_take() with a timeout of 0,
 *          meaning that the function does not block if the semaphore is not available.
 *          If the semaphore is successfully acquired, the function returns 0. If the semaphore is not available,
 *          errno is set to EAGAIN to indicate that the operation would result in blocking, and the function returns -1.
 *          If the semaphore wait operation is interrupted by a signal, errno is set to EINTR, and the function returns -1.
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
 * @brief   Waits indefinitely for a POSIX semaphore to become available.
 * @param   sem Pointer to the semaphore.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function waits indefinitely for the specified POSIX semaphore to become available.
 *          If sem is a null pointer, errno is set to EINVAL to indicate an invalid argument, and the function returns -1.
 *          The semaphore is waited upon using the RT-Thread semaphore take function rt_sem_take() with a timeout
 *          value of RT_WAITING_FOREVER, indicating an infinite wait time.
 *          If the semaphore is successfully acquired, the function returns 0. If the semaphore wait operation is interrupted
 *          by a signal, errno is set to EINTR, and the function returns -1.
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

