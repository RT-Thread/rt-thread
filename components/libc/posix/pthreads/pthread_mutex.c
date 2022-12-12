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
#include "pthread.h"

#define  MUTEXATTR_SHARED_MASK 0x0010
#define  MUTEXATTR_TYPE_MASK   0x000f

const pthread_mutexattr_t pthread_default_mutexattr = PTHREAD_PROCESS_PRIVATE;

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

int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type)
{
    if (attr && type)
    {
        int  atype = (*attr & MUTEXATTR_TYPE_MASK);

        if (atype >= PTHREAD_MUTEX_NORMAL && atype <= PTHREAD_MUTEX_ERRORCHECK)
        {
            *type = atype;

            return 0;
        }
    }

    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_gettype);

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

int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = (*attr & MUTEXATTR_SHARED_MASK) ? PTHREAD_PROCESS_SHARED
                                               : PTHREAD_PROCESS_PRIVATE;
    return 0;
}
RTM_EXPORT(pthread_mutexattr_getpshared);

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    rt_err_t result;
    char name[RT_NAME_MAX];
    static rt_uint16_t pthread_mutex_number = 0;

    if (!mutex)
        return EINVAL;

    /* build mutex name */
    rt_snprintf(name, sizeof(name), "pmtx%02d", pthread_mutex_number ++);
    if (attr == RT_NULL)
        mutex->attr = pthread_default_mutexattr;
    else
        mutex->attr = *attr;

    /* init mutex lock */
    result = rt_mutex_init(&(mutex->lock), name, RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
        return EINVAL;

    /* detach the object from system object container */
    rt_object_detach(&(mutex->lock.parent.parent));
    mutex->lock.parent.parent.type = RT_Object_Class_Mutex;

    return 0;
}
RTM_EXPORT(pthread_mutex_init);

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

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int mtype;
    rt_err_t result;

    if (!mutex)
        return EINVAL;

    if (mutex->attr == -1)
    {
        /* init mutex */
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

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    rt_err_t result;

    if (!mutex)
        return EINVAL;
    if (mutex->attr == -1)
    {
        /* init mutex */
        pthread_mutex_init(mutex, RT_NULL);
    }

    if (mutex->lock.owner != rt_thread_self())
    {
        int mtype;
        mtype = mutex->attr & MUTEXATTR_TYPE_MASK;

        /* error check, return EPERM */
        if (mtype == PTHREAD_MUTEX_ERRORCHECK)
            return EPERM;

        /* no thread waiting on this mutex */
        if (mutex->lock.owner == RT_NULL)
            return 0;
    }

    result = rt_mutex_release(&(mutex->lock));
    if (result == RT_EOK)
        return 0;

    return EINVAL;
}
RTM_EXPORT(pthread_mutex_unlock);

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    rt_err_t result;
    int mtype;

    if (!mutex)
        return EINVAL;
    if (mutex->attr == -1)
    {
        /* init mutex */
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
    if (result == RT_EOK) return 0;

    return EBUSY;
}
RTM_EXPORT(pthread_mutex_trylock);

int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_getprioceiling);

int pthread_mutexattr_setprioceiling(const pthread_mutexattr_t *attr, int prioceiling)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_setprioceiling);

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_getprotocol);

int pthread_mutexattr_setprotocol(const pthread_mutexattr_t *attr, int protocol)
{
    return EINVAL;
}
RTM_EXPORT(pthread_mutexattr_setprotocol);

int pthread_mutex_getprioceiling(const pthread_mutex_t *mutex, int *prioceiling)
{
    return pthread_mutexattr_getprioceiling(&mutex->attr, prioceiling);
}
RTM_EXPORT(pthread_mutex_getprioceiling);

int pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling)
{
    *old_ceiling = pthread_mutexattr_getprioceiling(&mutex->attr, old_ceiling);
    if(*old_ceiling != 0)
    {
        return EINVAL;
    }

    return pthread_mutexattr_setprioceiling(&mutex->attr, prioceiling);
}
RTM_EXPORT(pthread_mutex_setprioceiling);
