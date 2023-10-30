/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <rtthread.h>
#include "pthread.h"

#define MUTEXATTR_SHARED_MASK 0x0010
#define MUTEXATTR_TYPE_MASK 0x000f

const pthread_mutexattr_t pthread_default_mutexattr = PTHREAD_PROCESS_PRIVATE;

/**
 * @brief   Initialize a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to be initialized.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
    if (attr)
    {
        *attr = pthread_default_mutexattr;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_init);

/**
 * @brief   Destroy a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
    if (attr)
    {
        *attr = -1;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_destroy);

/**
 * @brief   Get the type of a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to query.
 * @param   type    is the pointer to an integer where the mutex type is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type)
{
    if (attr && type)
    {
        int atype = (*attr & MUTEXATTR_TYPE_MASK);

        if (atype >= PTHREAD_MUTEX_NORMAL && atype <= PTHREAD_MUTEX_ERRORCHECK)
        {
            *type = atype;

            return 0;
        }
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_gettype);

/**
 * @brief   Set the type of a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to modify.
 * @param   type    is the new mutex type value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type)
{
    if (attr && type >= PTHREAD_MUTEX_NORMAL && type <= PTHREAD_MUTEX_ERRORCHECK)
    {
        *attr = (*attr & ~MUTEXATTR_TYPE_MASK) | type;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_settype);

/**
 * @brief   Set the process-shared attribute of a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to modify.
 * @param   pshared is the new process-shared attribute value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared)
{
    if (!attr)
        return EINVAL;

    switch (pshared)
    {
    case PTHREAD_PROCESS_PRIVATE:
        *attr &= ~MUTEXATTR_SHARED_MASK;
        return 0;

    case PTHREAD_PROCESS_SHARED:
        *attr |= MUTEXATTR_SHARED_MASK;
        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_setpshared);

/**
 * @brief   Get the process-shared attribute of a mutex attributes object.
 *
 * @param   attr    is the pointer to the mutex attributes object to query.
 * @param   pshared is the pointer to an integer where the process-shared attribute is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = (*attr & MUTEXATTR_SHARED_MASK) ? PTHREAD_PROCESS_SHARED
                                               : PTHREAD_PROCESS_PRIVATE;
    return 0;
}
RTM_EXPORT(pthread_mutexattr_getpshared);

/**
 * @brief   Initialize a mutex object.
 *
 * @param   mutex   is the pointer to the mutex object to be initialized.
 * @param   attr    is the pointer to the mutex attributes (ignored).
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    rt_err_t result;
    char name[RT_NAME_MAX];
    static rt_uint16_t pthread_mutex_number = 0;

    if (!mutex)
        return EINVAL;

    /* build mutex name */
    rt_snprintf(name, sizeof(name), "pmtx%02d", pthread_mutex_number++);
    if (attr == RT_NULL)
        mutex->attr = pthread_default_mutexattr;
    else
        mutex->attr = *attr;

    /* init mutex lock */
    result = rt_mutex_init(&(mutex->lock), name, RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
        return EINVAL;

    /* detach the object from the system object container */
    rt_object_detach(&(mutex->lock.parent.parent));
    mutex->lock.parent.parent.type = RT_Object_Class_Mutex;

    return 0;
}
RTM_EXPORT(pthread_mutex_init);

/**
 * @brief   Destroy a mutex object.
 *
 * @param   mutex   is the pointer to the mutex object to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    if (!mutex || mutex->attr == -1)
        return EINVAL;

    /* it's busy */
    if (mutex->lock.owner != RT_NULL)
        return EBUSY;

    rt_memset(mutex, 0, sizeof(pthread_mutex_t));
    mutex->attr = -1;

    return 0;
}
RTM_EXPORT(pthread_mutex_destroy);

/**
 * @brief   Lock a mutex.
 *
 * @param   mutex   is the pointer to the mutex object to be locked.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int mtype;
    rt_err_t result;

    if (!mutex)
        return EINVAL;

    if (mutex->attr == -1)
    {
        /* Initialize the mutex */
        pthread_mutex_init(mutex, RT_NULL);
    }

    mtype = mutex->attr & MUTEXATTR_TYPE_MASK;
    rt_enter_critical();
    if (mutex->lock.owner == rt_thread_self() &&
        mtype != PTHREAD_MUTEX_RECURSIVE)
    {
        rt_exit_critical();

        return EDEADLK;
    }
    rt_exit_critical();

    result = rt_mutex_take(&(mutex->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
        return 0;

    return EINVAL;
}
RTM_EXPORT(pthread_mutex_lock);

/**
 * @brief   Unlock a mutex.
 *
 * @param   mutex   is the pointer to the mutex object to be unlocked.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    rt_err_t result;

    if (!mutex)
        return EINVAL;
    if (mutex->attr == -1)
    {
        /* Initialize the mutex */
        pthread_mutex_init(mutex, RT_NULL);
    }

    if (mutex->lock.owner != rt_thread_self())
    {
        int mtype;
        mtype = mutex->attr & MUTEXATTR_TYPE_MASK;

        /* Error check, return EPERM */
        if (mtype == PTHREAD_MUTEX_ERRORCHECK)
            return EPERM;

        /* No thread waiting on this mutex */
        if (mutex->lock.owner == RT_NULL)
            return 0;
    }

    result = rt_mutex_release(&(mutex->lock));
    if (result == RT_EOK)
        return 0;

    return EINVAL;
}
RTM_EXPORT(pthread_mutex_unlock);

/**
 * @brief   Try to lock a mutex.
 *
 * @param   mutex   is the pointer to the mutex object to be locked.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    rt_err_t result;
    int mtype;

    if (!mutex)
        return EINVAL;
    if (mutex->attr == -1)
    {
        /* Initialize the mutex */
        pthread_mutex_init(mutex, RT_NULL);
    }

    mtype = mutex->attr & MUTEXATTR_TYPE_MASK;
    rt_enter_critical();
    if (mutex->lock.owner == rt_thread_self() &&
        mtype != PTHREAD_MUTEX_RECURSIVE)
    {
        rt_exit_critical();

        return EDEADLK;
    }
    rt_exit_critical();

    result = rt_mutex_take(&(mutex->lock), 0);
    if (result == RT_EOK)
        return 0;

    return EBUSY;
}
RTM_EXPORT(pthread_mutex_trylock);

/**
 * @brief   Get the priority ceiling of a mutex attributes object.
 *
 * @param   attr        is the pointer to the mutex attributes object to query.
 * @param   prioceiling is the pointer to an integer where the priority ceiling is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_getprioceiling);

/**
 * @brief   Set the priority ceiling of a mutex attributes object.
 *
 * @param   attr        is the pointer to the mutex attributes object to modify.
 * @param   prioceiling is the new priority ceiling value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_setprioceiling(const pthread_mutexattr_t *attr, int prioceiling)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_setprioceiling);

/**
 * @brief   Get the protocol attribute of a mutex attributes object.
 *
 * @param   attr        is the pointer to the mutex attributes object to query.
 * @param   protocol    is the pointer to an integer where the protocol attribute is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_getprotocol);

/**
 * @brief   Set the protocol attribute of a mutex attributes object.
 *
 * @param   attr        is the pointer to the mutex attributes object to modify.
 * @param   protocol    is the new protocol attribute value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutexattr_setprotocol(const pthread_mutexattr_t *attr, int protocol)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_setprotocol);

/**
 * @brief   Get the priority ceiling of a mutex.
 *
 * @param   mutex       is the pointer to the mutex object to query.
 * @param   prioceiling is the pointer to an integer where the priority ceiling is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_mutex_getprioceiling(const pthread_mutex_t *mutex, int *prioceiling)
{
    return pthread_mutexattr_getprioceiling(&mutex->attr, prioceiling);
}
RTM_EXPORT(pthread_mutex_getprioceiling);

/**
 * @brief   Set the priority ceiling of a mutex.
 *
 * @param   mutex       is the pointer to the mutex object to modify.
 * @param   prioceiling is the new priority ceiling value.
 * @param   old_ceiling is the pointer to an integer where the old priority ceiling is stored.
 *
 * @return  0 on success, or an error code on failure
 */
int pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling)
{
    *old_ceiling = pthread_mutexattr_getprioceiling(&mutex->attr, old_ceiling);
    if (*old_ceiling != 0)
    {
        return EINVAL;
    }

    return pthread_mutexattr_setprioceiling(&mutex->attr, prioceiling);
}
RTM_EXPORT(pthread_mutex_setprioceiling);
