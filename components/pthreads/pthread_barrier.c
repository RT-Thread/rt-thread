/*
 * File      : pthread_barrier.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

