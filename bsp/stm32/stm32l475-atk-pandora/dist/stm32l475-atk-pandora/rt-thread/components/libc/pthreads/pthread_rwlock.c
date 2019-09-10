/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <pthread.h>

int pthread_rwlockattr_init(pthread_rwlockattr_t *attr)
{
    if (!attr)
        return EINVAL;
    *attr = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_rwlockattr_init);

int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr)
{
    if (!attr)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_rwlockattr_destroy);

int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *attr,
                                  int                        *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_rwlockattr_getpshared);

int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared)
{
    if (!attr || pshared != PTHREAD_PROCESS_PRIVATE)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_rwlockattr_setpshared);

int pthread_rwlock_init(pthread_rwlock_t           *rwlock,
                        const pthread_rwlockattr_t *attr)
{
    if (!rwlock)
        return EINVAL;

    rwlock->attr = PTHREAD_PROCESS_PRIVATE;
    pthread_mutex_init(&(rwlock->rw_mutex), NULL);
    pthread_cond_init(&(rwlock->rw_condreaders), NULL);
    pthread_cond_init(&(rwlock->rw_condwriters), NULL);
    
    rwlock->rw_nwaitwriters = 0;
    rwlock->rw_nwaitreaders = 0;
    rwlock->rw_refcount = 0;

    return 0;
}
RTM_EXPORT(pthread_rwlock_init);

int pthread_rwlock_destroy (pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        return 0; /* rwlock is not initialized */

    if ( (result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    if (rwlock->rw_refcount != 0 ||
        rwlock->rw_nwaitreaders != 0 ||
        rwlock->rw_nwaitwriters != 0)
    {
        result = EBUSY;

        return result;
    }
    else
    {
        /* check whether busy */
        result = rt_sem_trytake(&(rwlock->rw_condreaders.sem));
        if (result == RT_EOK)
        {
            result = rt_sem_trytake(&(rwlock->rw_condwriters.sem));
            if (result == RT_EOK)
            {
                rt_sem_release(&(rwlock->rw_condreaders.sem));
                rt_sem_release(&(rwlock->rw_condwriters.sem));

                pthread_cond_destroy(&rwlock->rw_condreaders);
                pthread_cond_destroy(&rwlock->rw_condwriters);
            }
            else
            {
                rt_sem_release(&(rwlock->rw_condreaders.sem));
                result = EBUSY;
            }
        }
        else
            result = EBUSY;
    }

    pthread_mutex_unlock(&rwlock->rw_mutex);
    if (result == 0)
        pthread_mutex_destroy(&rwlock->rw_mutex);
    
    return result;
}
RTM_EXPORT(pthread_rwlock_destroy);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ((result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    /* give preference to waiting writers */
    while (rwlock->rw_refcount < 0 || rwlock->rw_nwaitwriters > 0)
    {
        rwlock->rw_nwaitreaders++;
        /* rw_mutex will be released when waiting for rw_condreaders */
        result = pthread_cond_wait(&rwlock->rw_condreaders, &rwlock->rw_mutex);
        /* rw_mutex should have been taken again when returned from waiting */
        rwlock->rw_nwaitreaders--;
        if (result != 0) /* wait error */
            break;
    }

    /* another reader has a read lock */
    if (result == 0)
        rwlock->rw_refcount++;

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return (result);
}
RTM_EXPORT(pthread_rwlock_rdlock);

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ((result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    if (rwlock->rw_refcount < 0 || rwlock->rw_nwaitwriters > 0)
        result = EBUSY;                 /* held by a writer or waiting writers */
    else
        rwlock->rw_refcount++;          /* increment count of reader locks */

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return(result);
}
RTM_EXPORT(pthread_rwlock_tryrdlock);

int pthread_rwlock_timedrdlock(pthread_rwlock_t      *rwlock,
                               const struct timespec *abstime)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ( (result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    /* give preference to waiting writers */
    while (rwlock->rw_refcount < 0 || rwlock->rw_nwaitwriters > 0)
    {
        rwlock->rw_nwaitreaders++;
        /* rw_mutex will be released when waiting for rw_condreaders */
        result = pthread_cond_timedwait(&rwlock->rw_condreaders, &rwlock->rw_mutex, abstime);
        /* rw_mutex should have been taken again when returned from waiting */
        rwlock->rw_nwaitreaders--;
        if (result != 0)
            break;
    }

    /* another reader has a read lock */
    if (result == 0)
        rwlock->rw_refcount++;

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return (result);
}
RTM_EXPORT(pthread_rwlock_timedrdlock);

int pthread_rwlock_timedwrlock(pthread_rwlock_t      *rwlock,
                               const struct timespec *abstime)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ((result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    while (rwlock->rw_refcount != 0)
    {
        rwlock->rw_nwaitwriters++;
        /* rw_mutex will be released when waiting for rw_condwriters */
        result = pthread_cond_timedwait(&rwlock->rw_condwriters, &rwlock->rw_mutex, abstime);
        /* rw_mutex should have been taken again when returned from waiting */
        rwlock->rw_nwaitwriters--;
        
        if (result != 0)
            break;
    }

    if (result == 0)
        rwlock->rw_refcount = -1;

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return(result);
}
RTM_EXPORT(pthread_rwlock_timedwrlock);

int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ((result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    if (rwlock->rw_refcount != 0)
        result = EBUSY;                 /* held by either writer or reader(s) */
    else
        rwlock->rw_refcount = -1;       /* available, indicate a writer has it */

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return(result);
}
RTM_EXPORT(pthread_rwlock_trywrlock);

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ( (result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    if (rwlock->rw_refcount > 0)
        rwlock->rw_refcount--;              /* releasing a reader */
    else if (rwlock->rw_refcount == -1)
        rwlock->rw_refcount = 0;            /* releasing a writer */

    /* give preference to waiting writers over waiting readers */
    if (rwlock->rw_nwaitwriters > 0)
    {
        if (rwlock->rw_refcount == 0)
            result = pthread_cond_signal(&rwlock->rw_condwriters);
    }
    else if (rwlock->rw_nwaitreaders > 0)
    {
        result = pthread_cond_broadcast(&rwlock->rw_condreaders);
    }

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return(result);
}
RTM_EXPORT(pthread_rwlock_unlock);

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    int result;

    if (!rwlock)
        return EINVAL;
    if (rwlock->attr == -1)
        pthread_rwlock_init(rwlock, NULL);

    if ((result = pthread_mutex_lock(&rwlock->rw_mutex)) != 0)
        return(result);

    while (rwlock->rw_refcount != 0)
    {
        rwlock->rw_nwaitwriters++;
        /* rw_mutex will be released when waiting for rw_condwriters */
        result = pthread_cond_wait(&rwlock->rw_condwriters, &rwlock->rw_mutex);
        /* rw_mutex should have been taken again when returned from waiting */
        rwlock->rw_nwaitwriters--;
        
        if (result != 0)
            break;
    }

    if (result == 0)
        rwlock->rw_refcount = -1;

    pthread_mutex_unlock(&rwlock->rw_mutex);

    return(result);
}
RTM_EXPORT(pthread_rwlock_wrlock);

