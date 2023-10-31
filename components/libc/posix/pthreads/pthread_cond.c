/**
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

/**
 * @brief   Destroy a condition variable attributes object.
 *
 * @param   attr    is the pointer to the condition variable attributes object to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_destroy(pthread_condattr_t *attr)
{
    if (!attr)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_condattr_destroy);

/**
 * @brief   Initialize a condition variable attributes object.
 *
 * @param   attr    is the pointer to the condition variable attributes object to be initialized.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_init(pthread_condattr_t *attr)
{
    if (!attr)
        return EINVAL;
    *attr = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_condattr_init);

/**
 * @brief   Get the clock ID associated with a condition variable attributes object.
 *
 * @param   attr        is the pointer to the condition variable attributes object to query.
 * @param   clock_id    is the pointer to a variable where the clock ID is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_getclock(const pthread_condattr_t *attr,
                              clockid_t *clock_id)
{
    return 0;
}
RTM_EXPORT(pthread_condattr_getclock);

/**
 * @brief   Set the clock ID associated with a condition variable attributes object.
 *
 * @param   attr        is the pointer to the condition variable attributes object to modify.
 * @param   clock_id    is the new clock ID value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_setclock(pthread_condattr_t *attr,
                              clockid_t clock_id)
{
    return 0;
}
RTM_EXPORT(pthread_condattr_setclock);

/**
 * @brief   Get the process-shared attribute of a condition variable attributes object.
 *
 * @param   attr    is the pointer to the condition variable attributes object to query.
 * @param   pshared is the pointer to an integer where the process-shared attribute is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_getpshared(const pthread_condattr_t *attr, int *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_condattr_getpshared);

/**
 * @brief   Set the process-shared attribute of a condition variable attributes object.
 *
 * @param   attr    is the pointer to the condition variable attributes object to modify.
 * @param   pshared is the new process-shared attribute value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared)
{
    if ((pshared != PTHREAD_PROCESS_PRIVATE) && (pshared != PTHREAD_PROCESS_SHARED))
    {
        return EINVAL;
    }

    if (pshared != PTHREAD_PROCESS_PRIVATE)
        return ENOSYS;

    return 0;
}
RTM_EXPORT(pthread_condattr_setpshared);

/**
 * @brief   Initialize a condition variable.
 *
 * @param   cond    is the pointer to the condition variable to be initialized.
 * @param   attr    is the pointer to condition variable attributes (ignored).
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
    rt_err_t result;
    char cond_name[RT_NAME_MAX];
    static rt_uint16_t cond_num = 0;

    /* Parameter check */
    if (cond == RT_NULL)
        return EINVAL;
    if ((attr != RT_NULL) && (*attr != PTHREAD_PROCESS_PRIVATE))
        return EINVAL;

    rt_snprintf(cond_name, sizeof(cond_name), "cond%02d", cond_num++);

    /* Use default value */
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

    /* Detach the object from the system object container */
    rt_object_detach(&(cond->sem.parent.parent));
    cond->sem.parent.parent.type = RT_Object_Class_Semaphore;

    return 0;
}
RTM_EXPORT(pthread_cond_init);

/**
 * @brief   Destroy a condition variable.
 *
 * @param   cond    is the pointer to the condition variable to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_cond_destroy(pthread_cond_t *cond)
{
    rt_err_t result;
    if (cond == RT_NULL)
    {
        return EINVAL;
    }
    /* Which is not initialized */
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

    /* Clean the condition */
    rt_memset(cond, 0, sizeof(pthread_cond_t));
    cond->attr = -1;

    return 0;
}
RTM_EXPORT(pthread_cond_destroy);

/**
 * @brief   Wake up all threads waiting on a condition variable.
 *
 * @param   cond    is the pointer to the condition variable.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_cond_broadcast(pthread_cond_t *cond)
{
    rt_err_t result;

    if (cond == RT_NULL)
        return EINVAL;
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    while (1)
    {
        /* Try to take the condition semaphore */
        result = rt_sem_trytake(&(cond->sem));
        if (result == -RT_ETIMEOUT)
        {
            /* It's timeout, release this semaphore */
            rt_sem_release(&(cond->sem));
        }
        else if (result == RT_EOK)
        {
            /* Has taken this semaphore, release it */
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

/**
 * @brief   Wake up one thread waiting on a condition variable.
 *
 * @param   cond    is the pointer to the condition variable.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_cond_signal(pthread_cond_t *cond)
{
    rt_base_t temp;
    rt_err_t result;

    if (cond == RT_NULL)
        return EINVAL;
    if (cond->attr == -1)
        pthread_cond_init(cond, RT_NULL);

    /* Disable interrupts */
    temp = rt_hw_interrupt_disable();
    if (rt_list_isempty(&cond->sem.parent.suspend_thread))
    {
        /* Enable interrupts */
        rt_hw_interrupt_enable(temp);
        return 0;
    }
    else
    {
        /* Enable interrupts */
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

/**
 * @brief   Wait on a condition variable with a timeout.
 *
 * @param   cond    is the pointer to the condition variable.
 * @param   mutex   is the pointer to the associated mutex.
 * @param   timeout is the timeout value in ticks.
 *
 * @return  0 on success, or an error code on failure.
 */
rt_err_t _pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, rt_int32_t timeout)
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
    /* Check whether initialized */
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

        /* Parameter check */
        RT_ASSERT(sem != RT_NULL);
        RT_ASSERT(rt_object_get_type(&sem->parent.parent) == RT_Object_Class_Semaphore);

        /* Disable interrupts */
        temp = rt_hw_interrupt_disable();

        if (sem->value > 0)
        {
            /* Semaphore is available */
            sem->value--;

            /* Enable interrupts */
            rt_hw_interrupt_enable(temp);
        }
        else
        {
            /* No waiting, return with timeout */
            if (time == 0)
            {
                rt_hw_interrupt_enable(temp);

                return -RT_ETIMEOUT;
            }
            else
            {
                /* Current context checking */
                RT_DEBUG_IN_THREAD_CONTEXT;

                /* Semaphore is unavailable, push to suspend list */
                /* Get current thread */
                thread = rt_thread_self();

                /* Reset thread error number */
                thread->error = RT_EOK;

                /* Suspend thread */
                rt_thread_suspend(thread);

                /* Only support FIFO */
                rt_list_insert_before(&(sem->parent.suspend_thread), &(thread->tlist));

                /* Has waiting time, start thread timer */
                if (time > 0)
                {
                    /* Reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread->thread_timer), RT_TIMER_CTRL_SET_TIME, &time);
                    rt_timer_start(&(thread->thread_timer));
                }

                /* To avoid the loss of signal< cond->sem > */
                if (pthread_mutex_unlock(mutex) != 0)
                {
                    return -RT_ERROR;
                }

                /* Enable interrupts */
                rt_hw_interrupt_enable(temp);

                /* Do schedule */
                rt_schedule();

                result = thread->error;

                /* Lock the mutex again */
                pthread_mutex_lock(mutex);
            }
        }
    }

    return result;
}
RTM_EXPORT(_pthread_cond_timedwait);

/**
 * @brief   Wait on a condition variable.
 *
 * @param   cond    is the pointer to the condition variable.
 * @param   mutex   is the pointer to the associated mutex.
 *
 * @return  0 on success, or an error code on failure.
 */
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
        /* These functions shall not return an error code of [EINTR]. */
        goto __retry;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_cond_wait);

/**
 * @brief   Wait on a condition variable with an absolute timeout.
 *
 * @param   cond    is the pointer to the condition variable.
 * @param   mutex   is the pointer to the associated mutex.
 * @param   abstime is the absolute timeout value.
 *
 * @return  0 on success, or an error code on failure.
 */

int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime)
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
