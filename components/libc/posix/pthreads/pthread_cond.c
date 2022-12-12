/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 * 2022-06-27     xiangxistu   use atomic operation to protect pthread conditional variable
 */

#include <rthw.h>
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
                              clockid_t *clock_id)
{
    return 0;
}
RTM_EXPORT(pthread_condattr_getclock);

int pthread_condattr_setclock(pthread_condattr_t *attr,
                              clockid_t clock_id)
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

int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared)
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

    /* use default value */
    if (attr == RT_NULL)
    {
        cond->attr = PTHREAD_PROCESS_PRIVATE;
    }
    else
    {
        cond->attr = *attr;
    }

    result = rt_sem_init(&cond->sem, cond_name, 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        return EINVAL;
    }

    /* detach the object from system object container */
    rt_object_detach(&(cond->sem.parent.parent));
    cond->sem.parent.parent.type = RT_Object_Class_Semaphore;

    return 0;
}
RTM_EXPORT(pthread_cond_init);

int pthread_cond_destroy(pthread_cond_t *cond)
{
    rt_err_t result;
    if (cond == RT_NULL)
    {
        return EINVAL;
    }
    /* which is not initialized */
    if (cond->attr == -1)
    {
        return 0;
    }

    if (!rt_list_isempty(&cond->sem.parent.suspend_thread))
    {
        return EBUSY;
    }
__retry:
    result = rt_sem_trytake(&(cond->sem));
    if (result == EBUSY)
    {
        pthread_cond_broadcast(cond);
        goto __retry;
    }

    /* clean condition */
    rt_memset(cond, 0, sizeof(pthread_cond_t));
    cond->attr = -1;

    return 0;
}
RTM_EXPORT(pthread_cond_destroy);

int pthread_cond_broadcast(pthread_cond_t *cond)
{
    rt_err_t result;

    if (cond == RT_NULL)
        return EINVAL;
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

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
            return EINVAL;
        }
    }

    return 0;
}
RTM_EXPORT(pthread_cond_broadcast);

int pthread_cond_signal(pthread_cond_t *cond)
{
    rt_base_t temp;
    rt_err_t result;

    if (cond == RT_NULL)
        return EINVAL;
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    /* disable interrupt */
    temp = rt_hw_interrupt_disable();
    if (rt_list_isempty(&cond->sem.parent.suspend_thread))
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
        return 0;
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
        result = rt_sem_release(&(cond->sem));
        if (result == RT_EOK)
        {
            return 0;
        }

        return 0;
    }
}
RTM_EXPORT(pthread_cond_signal);

rt_err_t _pthread_cond_timedwait(pthread_cond_t *cond,
                                 pthread_mutex_t *mutex,
                                 rt_int32_t timeout)
{
    rt_err_t result = RT_EOK;
    rt_sem_t sem;
    rt_int32_t time;

    sem = &(cond->sem);
    if (sem == RT_NULL)
    {
        return -RT_ERROR;
    }
    time = timeout;

    if (!cond || !mutex)
    {
        return -RT_ERROR;
    }
    /* check whether initialized */
    if (cond->attr == -1)
    {
        pthread_cond_init(cond, RT_NULL);
    }

    /* The mutex was not owned by the current thread at the time of the call. */
    if (mutex->lock.owner != rt_thread_self())
    {
        return -RT_ERROR;
    }

    {
        register rt_base_t temp;
        struct rt_thread *thread;

        /* parameter check */
        RT_ASSERT(sem != RT_NULL);
        RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);

        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        if (sem->value > 0)
        {
            /* semaphore is available */
            sem->value--;

            /* enable interrupt */
            rt_hw_interrupt_enable(temp);
        }
        else
        {
            /* no waiting, return with timeout */
            if (time == 0)
            {
                rt_hw_interrupt_enable(temp);

                return -RT_ETIMEOUT;
            }
            else
            {
                /* current context checking */
                RT_DEBUG_IN_THREAD_CONTEXT;

                /* semaphore is unavailable, push to suspend list */
                /* get current thread */
                thread = rt_thread_self();

                /* reset thread error number */
                thread->error = RT_EOK;

                /* suspend thread */
                rt_thread_suspend(thread);

                /* Only support FIFO */
                rt_list_insert_before(&(sem->parent.suspend_thread), &(thread->tlist));

                /**
                rt_ipc_list_suspend(&(sem->parent.suspend_thread),
                                    thread,
                                    sem->parent.parent.flag);
                */

                /* has waiting time, start thread timer */
                if (time > 0)
                {
                    /* reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread->thread_timer),
                                     RT_TIMER_CTRL_SET_TIME,
                                     &time);
                    rt_timer_start(&(thread->thread_timer));
                }

                /* to avoid the lost of singal< cond->sem > */
                if (pthread_mutex_unlock(mutex) != 0)
                {
                    return -RT_ERROR;
                }

                /* enable interrupt */
                rt_hw_interrupt_enable(temp);

                /* do schedule */
                rt_schedule();

                result = thread->error;

                /* lock mutex again */
                pthread_mutex_lock(mutex);
            }
        }
    }

    return result;
}
RTM_EXPORT(_pthread_cond_timedwait);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    rt_err_t result;

__retry:
    result = _pthread_cond_timedwait(cond, mutex, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        return 0;
    }
    else if (result == -RT_EINTR)
    {
        /* https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_wait.html
         * These functions shall not return an error code of [EINTR].
         */
        goto __retry;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_cond_wait);

int pthread_cond_timedwait(pthread_cond_t *cond,
                           pthread_mutex_t *mutex,
                           const struct timespec *abstime)
{
    int timeout;
    rt_err_t result;

    timeout = rt_timespec_to_tick(abstime);
    result = _pthread_cond_timedwait(cond, mutex, timeout);
    if (result == RT_EOK)
    {
        return 0;
    }
    if (result == -RT_ETIMEOUT)
    {
        return ETIMEDOUT;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_cond_timedwait);
