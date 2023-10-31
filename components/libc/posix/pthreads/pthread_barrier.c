/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <pthread.h>

/**
 * @brief   Destroy a barrier attributes object.
 *
 * @param   attr    is the pointer to the barrier attributes object to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrierattr_destroy(pthread_barrierattr_t *attr)
{
    if (!attr)
        return EINVAL;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_destroy);

/**
 * @brief   Initialize a barrier attributes object.
 *
 * @param   attr    is the pointer to the barrier attributes object to be initialized.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrierattr_init(pthread_barrierattr_t *attr)
{
    if (!attr)
        return EINVAL;
    *attr = PTHREAD_PROCESS_PRIVATE;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_init);

/**
 * @brief   Get the process-shared attribute of a barrier attributes object.
 *
 * @param   attr        is the pointer to the barrier attributes object to query.
 * @param   pshared     is the pointer to an integer where the process-shared attribute is stored.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr,
                                   int *pshared)
{
    if (!attr)
        return EINVAL;
    *pshared = (int)*attr;

    return 0;
}
RTM_EXPORT(pthread_barrierattr_getpshared);

/**
 * @brief   Set the process-shared attribute of a barrier attributes object.
 *
 * @param   attr    is the pointer to the barrier attributes object to modify.
 * @param   pshared is the new process-shared attribute value.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared)
{
    if (!attr)
        return EINVAL;
    if (pshared == PTHREAD_PROCESS_PRIVATE)
        attr = PTHREAD_PROCESS_PRIVATE;

    return EINVAL;
}
RTM_EXPORT(pthread_barrierattr_setpshared);

/**
 * @brief   Destroy a barrier object.
 *
 * @param   barrier is the pointer to the barrier object to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    rt_err_t result;

    if (!barrier)
        return EINVAL;

    result = pthread_cond_destroy(&(barrier->cond));

    return result;
}
RTM_EXPORT(pthread_barrier_destroy);

/**
 * @brief   Initialize a barrier object.
 *
 * @param   barrier is the pointer to the barrier object to be initialized.
 * @param   attr    is the pointer to barrier attributes (ignored).
 * @param   count   is the count of threads required to trigger the barrier.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_barrier_init(pthread_barrier_t *barrier,
                         const pthread_barrierattr_t *attr,
                         unsigned count)
{
    if (!barrier)
        return EINVAL;
    if (attr && (*attr != PTHREAD_PROCESS_PRIVATE))
        return EINVAL;
    if (count == 0)
        return EINVAL;

    barrier->count = count;
    pthread_cond_init(&(barrier->cond), NULL);
    pthread_mutex_init(&(barrier->mutex), NULL);

    return 0;
}
RTM_EXPORT(pthread_barrier_init);

/**
 * @brief   Wait on a barrier.
 *
 * @param   barrier is the pointer to the barrier object to wait on.
 *
 * @return  0 on success, or an error code on failure.
 */
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
