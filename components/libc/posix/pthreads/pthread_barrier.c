/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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
    {
        *attr = PTHREAD_PROCESS_PRIVATE;
        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_barrierattr_setpshared);

/**
 * @brief Destroys a barrier object.
 *
 * The `pthread_barrier_destroy` function releases any resources associated
 * with the specified barrier object. After a barrier has been destroyed,
 * it cannot be used again unless it is reinitialized using `pthread_barrier_init`.
 *
 * @param[in] barrier
 * A pointer to an initialized `pthread_barrier_t` object to be destroyed.
 *
 * @return
 * - `0` on success.
 * - `EINVAL` if the `barrier` is invalid or uninitialized.
 * - `EBUSY` if there are threads currently blocked on the barrier.
 *
 * @note
 * - Ensure that no threads are blocked on the barrier before calling this function.
 * - Attempting to destroy a barrier that is still in use results in undefined behavior.
 *
 * @warning
 * Destroying a barrier without ensuring it is no longer in use can lead to
 * resource leaks or undefined program behavior.
 *
 * @see pthread_barrier_init, pthread_barrier_wait
 */
int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    rt_err_t result;

    if (!barrier)
        return EINVAL;

    /* Lock the internal mutex to safely check the barrier's state*/
    result = pthread_mutex_lock(&(barrier->mutex));
    if (result != 0)
        return result;

    /* Check if any threads are currently waiting on the barrier*/
    if (barrier->count != 0)
    {
        pthread_mutex_unlock(&(barrier->mutex));
        return EBUSY; /* Threads are still waiting*/
    }

    /* Free resources associated with the barrier*/
    result = pthread_mutex_unlock(&(barrier->mutex));
    if (result != 0)
    {
        return result; /* Return mutex unlock error*/
    }

    result = pthread_mutex_destroy(&(barrier->mutex));
    if (result != 0)
    {
        return result; /* Return mutex destroy error*/
    }
    result = pthread_cond_destroy(&(barrier->cond));

    return result;
}
RTM_EXPORT(pthread_barrier_destroy);

/**
 * @brief Initializes a barrier for synchronizing threads.
 *
 * The `pthread_barrier_init` function initializes a barrier object
 * that allows a specified number of threads to synchronize at a barrier point.
 * Each thread waits at the barrier until the required number of threads have called
 * `pthread_barrier_wait`.
 *
 * @param[out] barrier
 * A pointer to the `pthread_barrier_t` object to be initialized.
 * This object must not already be initialized.
 *
 * @param[in] attr
 * A pointer to a `pthread_barrierattr_t` object that specifies
 * attributes for the barrier (e.g., process-shared or process-private).
 * If NULL, the default attributes are used.
 *
 * @param[in] count
 * The number of threads that must call `pthread_barrier_wait`
 * before any of them successfully return from the barrier.
 *
 * @return
 * - `0` on success.
 * - `EINVAL` if the `count` is zero or `barrier` is invalid.
 *
 * @note The barrier must be destroyed using `pthread_barrier_destroy`
 * when it is no longer needed.
 *
 * @warning If `count` is set to zero, the behavior is undefined.
 *
 * @see pthread_barrier_wait, pthread_barrier_destroy
 */
int pthread_barrier_init(pthread_barrier_t           *barrier,
                         const pthread_barrierattr_t *attr,
                         unsigned                     count)
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
 * @brief Synchronizes threads at a barrier.
 *
 * The `pthread_barrier_wait` function blocks the calling thread at the specified
 * barrier until the required number of threads have reached the barrier. Once
 * the required number of threads have called this function, all threads are
 * unblocked and can proceed.
 *
 * @param[in] barrier
 * A pointer to an initialized `pthread_barrier_t` object representing the barrier
 * at which threads will synchronize.
 *
 * @return
 * - `0` for all threads except one.
 * - `EINVAL` - The `barrier` is invalid or uninitialized.
 *
 * @note
 * - All threads participating in the barrier must call `pthread_barrier_wait`
 *   before any of them are released.
 *
 * @warning
 * Ensure that the number of threads specified during the barrier's initialization
 * matches the number of threads calling this function, otherwise the program
 * may hang indefinitely.
 *
 * @see pthread_barrier_init, pthread_barrier_destroy
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

