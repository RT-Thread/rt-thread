/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <pthread.h>

int pthread_barrierattr_destroy(pthread_barrierattr_t *attr)
{
    if (!attr)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_destroy);

int pthread_barrierattr_init(pthread_barrierattr_t *attr)
{
    if (!attr)
        return EINVAL;
    *attr = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_init);

int pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr,
                                   int                         *pshared)
{
    if (!attr)
        return EINVAL;
    *pshared = (int)*attr;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_getpshared);

int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared)
{
    if (!attr)
        return EINVAL;
    if (pshared == PTHREAD_PROCESS_PRIVATE)
        attr = PTHREAD_PROCESS_PRIVATE;

    return EINVAL;
}
RTM_EXPORT(pthread_barrierattr_setpshared);

int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    rt_err_t result;

    if (!barrier)
        return EINVAL;

    result = pthread_cond_destroy(&(barrier->cond));

    return result;
}
RTM_EXPORT(pthread_barrier_destroy);

int pthread_barrier_init(pthread_barrier_t           *barrier,
                         const pthread_barrierattr_t *attr,
                         unsigned                     count)
{
    if (!barrier)
        return EINVAL;
    if (attr && (*attr != PTHREAD_PROCESS_PRIVATE))
        return EINVAL;

    barrier->count = count;
    pthread_cond_init(&(barrier->cond), NULL);
    pthread_mutex_init(&(barrier->mutex), NULL);

    return 0;
}
RTM_EXPORT(pthread_barrier_init);

int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    rt_err_t result;
    if (!barrier)
        return EINVAL;

    result = pthread_mutex_lock(&(barrier->mutex));
    if (result != 0)
        return EINVAL;

    if (barrier->count == 0)
        result = EINVAL;
    else
    {
        barrier->count -= 1;
        if (barrier->count == 0) /* broadcast condition */
            pthread_cond_broadcast(&(barrier->cond));
        else
            pthread_cond_wait(&(barrier->cond), &(barrier->mutex));
    }

    pthread_mutex_unlock(&(barrier->mutex));

    return result;
}
RTM_EXPORT(pthread_barrier_wait);

