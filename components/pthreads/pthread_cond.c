/*
 * File      : pthread_cond.c
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
#include "pthread_internal.h"

int pthread_condattr_destroy(pthread_condattr_t *attr)
{
    if (!attr)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_condattr_destroy);

int pthread_condattr_init(pthread_condattr_t *attr)
{
    if (!attr)
        return EINVAL;
    *attr = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_condattr_init);

int pthread_condattr_getclock(const pthread_condattr_t *attr,
                              clockid_t                *clock_id)
{
    return 0;
}
RTM_EXPORT(pthread_condattr_getclock);

int pthread_condattr_setclock(pthread_condattr_t *attr,
                              clockid_t           clock_id)
{
    return 0;
}
RTM_EXPORT(pthread_condattr_setclock);

int pthread_condattr_getpshared(const pthread_condattr_t *attr, int *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_condattr_getpshared);

int pthread_condattr_setpshared(pthread_condattr_t*attr, int pshared)
{
    if ((pshared != PTHREAD_PROCESS_PRIVATE) &&
        (pshared != PTHREAD_PROCESS_SHARED))
    {
        return EINVAL;
    }

    if (pshared != PTHREAD_PROCESS_PRIVATE)
        return ENOSYS;

    return 0;
}
RTM_EXPORT(pthread_condattr_setpshared);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
    rt_err_t result;
    char cond_name[RT_NAME_MAX];
    static rt_uint16_t cond_num = 0;

    /* parameter check */
    if (cond == RT_NULL)
        return EINVAL;
    if ((attr != RT_NULL) && (*attr != PTHREAD_PROCESS_PRIVATE))
        return EINVAL;

    rt_snprintf(cond_name, sizeof(cond_name), "cond%02d", cond_num++);

	if (attr == RT_NULL) /* use default value */
		cond->attr = PTHREAD_PROCESS_PRIVATE;
	else 
	    cond->attr = *attr;

    result = rt_sem_init(&cond->sem, cond_name, 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
        return EINVAL;

    /* detach the object from system object container */
    rt_object_detach(&(cond->sem.parent.parent));

    return 0;
}
RTM_EXPORT(pthread_cond_init);

int pthread_cond_destroy(pthread_cond_t *cond)
{
    rt_err_t result;
    if (cond == RT_NULL)
        return EINVAL;
    if (cond->attr == -1)
        return 0; /* which is not initialized */

    result = rt_sem_trytake(&(cond->sem));
    if (result != RT_EOK)
        return EBUSY;

    /* clean condition */
    rt_memset(cond, 0, sizeof(pthread_cond_t));
    cond->attr = -1;

    return 0;
}
RTM_EXPORT(pthread_cond_destroy);

int pthread_cond_broadcast(pthread_cond_t *cond)
{
    rt_err_t result;
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    rt_enter_critical();
    while (1)
    {
        /* try to take condition semaphore */
        result = rt_sem_trytake(&(cond->sem));
        if (result == -RT_ETIMEOUT)
        {
            /* it's timeout, release this semaphore */
            rt_sem_release(&(cond->sem));
        }
        else if (result == RT_EOK)
        {
            /* has taken this semaphore, release it */
            rt_sem_release(&(cond->sem));
            break;
        }
        else
        {
            rt_exit_critical();

            return EINVAL;
        }
    }
    rt_exit_critical();

    return 0;
}
RTM_EXPORT(pthread_cond_broadcast);

int pthread_cond_signal(pthread_cond_t *cond)
{
    rt_err_t result;

    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    result = rt_sem_release(&(cond->sem));
    if (result == RT_EOK)
        return 0;

    return 0;
}
RTM_EXPORT(pthread_cond_signal);

rt_err_t _pthread_cond_timedwait(pthread_cond_t  *cond,
                                 pthread_mutex_t *mutex,
                                 rt_int32_t       timeout)
{
    rt_err_t result;

    if (!cond || !mutex)
        return -RT_ERROR;
    /* check whether initialized */
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    /* The mutex was not owned by the current thread at the time of the call. */
    if (mutex->lock.owner != pthread_self())
        return -RT_ERROR;
    /* unlock a mutex failed */
    if (pthread_mutex_unlock(mutex) != 0)
        return -RT_ERROR;

    result = rt_sem_take(&(cond->sem), timeout);
    /* lock mutex again */
    pthread_mutex_lock(mutex);

    return result;
}
RTM_EXPORT(_pthread_cond_timedwait);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    rt_err_t result;

    result = _pthread_cond_timedwait(cond, mutex, RT_WAITING_FOREVER);
    if (result == RT_EOK)
        return 0;

    return EINVAL;
}
RTM_EXPORT(pthread_cond_wait);

int pthread_cond_timedwait(pthread_cond_t        *cond,
                           pthread_mutex_t       *mutex,
                           const struct timespec *abstime)
{
    int timeout;
    rt_err_t result;

    timeout = clock_time_to_tick(abstime);
    result = _pthread_cond_timedwait(cond, mutex, timeout);
    if (result == RT_EOK)
        return 0;
    if (result == -RT_ETIMEOUT)
        return ETIMEDOUT;

    return EINVAL;
}
RTM_EXPORT(pthread_cond_timedwait);

