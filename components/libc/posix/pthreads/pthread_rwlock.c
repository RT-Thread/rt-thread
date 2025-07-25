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

/**
 * @brief Initializes a read-write lock.
 *
 * This function initializes the read-write lock object pointed to by `rwlock` with the
 * attributes specified by `attr`. If `attr` is `NULL`, the default attributes are used.
 * A read-write lock allows multiple threads to read or a single thread to write, but not both simultaneously.
 *
 * @param rwlock A pointer to the read-write lock object to be initialized.
 *               Must point to valid memory.
 * @param attr A pointer to the attributes for the read-write lock.
 *             If `NULL`, default attributes are applied.
 *
 * @return
 * - `0` on success.
 * - A non-zero error code on failure, including:
 *   - `EINVAL`: Invalid attributes.
 *
 * @note
 * - The read-write lock must be destroyed using `pthread_rwlock_destroy()` when it is no longer needed.
 * - 'rw_mutex' is used for protecting rwlock data.
 *   'rw_condreaders' is a condition variable for controlling readers.
 *   'rw_condwriters' is a condition variable for controlling writers.
 *
 * @see pthread_rwlock_destroy, pthread_rwlock_rdlock, pthread_rwlock_wrlock, pthread_rwlock_unlock
 */
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

/**
 * @brief Destroys a read-write lock.
 *
 * This function destroys the read-write lock object pointed to by `rwlock`. After
 * the lock is destroyed, it cannot be used until it is reinitialized with
 * `pthread_rwlock_init`. Any threads currently blocked on the lock are affected by the destruction.
 *
 * @param rwlock A pointer to the read-write lock object to be destroyed.
 *               Must point to a valid, initialized read-write lock.
 *
 * @return
 * - `0` on success.
 * - A non-zero error code on failure, including:
 *   - `EINVAL`: The `rwlock` is invalid or uninitialized.
 *   - `EBUSY`: The lock is currently in use by a thread, and cannot be destroyed.
 *
 * @note
 * - The read-write lock must not be in use (i.e., no threads should be blocked on it)
 *   when `pthread_rwlock_destroy` is called.
 * - Calling this function on an uninitialized or destroyed lock will result in undefined behavior.
 * - Ensure that all threads have unlocked the lock before attempting to destroy it.
 *
 * @see pthread_rwlock_init, pthread_rwlock_rdlock, pthread_rwlock_wrlock, pthread_rwlock_unlock
 */
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

/**
 * @brief Acquire a read lock on a read-write lock.
 *
 * This function locks the specified read-write lock for reading. If the lock
 * is already held by one or more threads for reading, the calling thread
 * can acquire the lock as well (shared access). However, if the lock is
 * held by another writer thread, or other writer thread has been waiting
 * for the lock, the calling thread will block until the write lock is released.
 *
 * @param rwlock A pointer to the read-write lock to be locked.
 *
 * @return - 0 on success.
 *         - EINVAL if the rwlock is invalid.
 *         - EDEADLK if a deadlock condition is detected (optional; implementation-dependent).
 *
 * @note A thread that has acquired a read lock must eventually release it
 *       using `pthread_rwlock_unlock`. Multiple read locks can be held
 *       simultaneously, but a write lock excludes all other locks.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_wrlock
 * @see pthread_rwlock_tryrdlock
 */
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

/**
 * @brief Try to acquire a read lock on a read-write lock without blocking.
 *
 * This function attempts to acquire a read lock on the specified read-write lock.
 * If the lock is already held for writing, the function will return immediately
 * without blocking the calling thread. If the lock is available for reading,
 * it will be acquired successfully.
 *
 * @param rwlock A pointer to the read-write lock to attempt to lock.
 *
 * @return - 0 on success, indicating the read lock was acquired.
 *         - EBUSY if the lock is currently held for writing by another thread.
 *         - EINVAL if the rwlock is invalid.
 *
 * @note This function is non-blocking and returns immediately if the lock
 *       cannot be acquired. After successfully acquiring the read lock,
 *       the thread must release it using `pthread_rwlock_unlock`.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_rdlock
 * @see pthread_rwlock_trywrlock
 */
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

/**
 * @brief Acquire a read lock on a read-write lock with a timeout.
 *
 * This function attempts to lock the specified read-write lock for reading,
 * blocking until the lock becomes available or the specified timeout expires.
 * If the lock is held for writing by another thread, the calling thread will
 * block, but only up to the time specified by `abstime`.
 *
 * @param rwlock A pointer to the read-write lock to be locked.
 * @param abstime A pointer to a `timespec` structure specifying the
 *                    absolute timeout (in seconds and nanoseconds since the
 *                    Epoch, 1970-01-01 00:00:00 UTC).
 *
 * @return - 0 on success, indicating the read lock was acquired.
 *         - ETIMEDOUT if the timeout expired before the lock could be acquired.
 *         - EINVAL if the `rwlock` is invalid or `abstime` contains invalid values.
 *         - EDEADLK if a deadlock condition is detected (optional; implementation-dependent).
 *
 * @note The timeout is specified as an absolute time (not relative). After
 *       acquiring the read lock, the thread must release it using
 *       `pthread_rwlock_unlock`.
 *
 * @warning If the system clock is changed (e.g., via manual adjustment or
 *          NTP synchronization), the timeout behavior may be affected.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_rdlock
 * @see pthread_rwlock_tryrdlock
 */
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

/**
 * @brief Acquire a write lock on a read-write lock with a timeout.
 *
 * This function attempts to acquire a write lock on the specified read-write lock,
 * blocking until the lock becomes available or the specified timeout expires.
 * If the lock is already held for reading or writing by another thread, the
 * calling thread will block, but only up to the time specified by `abstime`.
 *
 * @param rwlock A pointer to the read-write lock to be locked.
 * @param abstime A pointer to a `timespec` structure specifying the
 *                    absolute timeout (in seconds and nanoseconds since the
 *                    Epoch, 1970-01-01 00:00:00 UTC).
 *
 * @return
 * - 0 on success, indicating the write lock was acquired.
 * - EINVAL if the `rwlock` is invalid or `abstime` contains invalid values.
 * - EDEADLK if a deadlock condition is detected (optional; implementation-dependent).
 *
 * @note The timeout is specified as an absolute time (not relative). After
 *       acquiring the write lock, the thread must release it using
 *       `pthread_rwlock_unlock`.
 *
 * @warning If the system clock is adjusted (e.g., manually or via NTP synchronization),
 *          the timeout behavior may be affected.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_wrlock
 * @see pthread_rwlock_trywrlock
 */
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

/**
 * @brief Try to acquire a write lock on a read-write lock without blocking.
 *
 * This function attempts to acquire a write lock on the specified read-write lock.
 * If the lock is already held for reading or writing by another thread, the function
 * will return immediately without blocking the calling thread. If the lock is
 * available, it will be acquired successfully.
 *
 * @param rwlock A pointer to the read-write lock to attempt to lock.
 *
 * @return
 * - 0 on success, indicating the write lock was acquired.
 * - EBUSY if the lock is currently held by another thread (read or write lock).
 * - EINVAL if the `rwlock` is invalid.
 *
 * @note This function is non-blocking and returns immediately if the lock cannot
 *       be acquired. After successfully acquiring the write lock, the thread must
 *       release it using `pthread_rwlock_unlock`.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_wrlock
 * @see pthread_rwlock_timedwrlock
 */
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

/**
 * @brief Release a read or write lock on a read-write lock.
 *
 * This function unlocks the specified read-write lock, releasing either a read
 * lock or a write lock held by the calling thread. If the calling thread does
 * not hold the lock, the behavior is undefined.
 *
 * @param rwlock A pointer to the read-write lock to be unlocked.
 *
 * @return
 * - 0 on success.
 * - EINVAL if the `rwlock` is invalid.
 *
 * @note
 * - This function must only be called by the thread that successfully acquired
 *   the lock.
 *
 * @see pthread_rwlock_rdlock
 * @see pthread_rwlock_wrlock
 * @see pthread_rwlock_tryrdlock
 * @see pthread_rwlock_trywrlock
 */
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

/**
 * @brief Acquire a write lock on a read-write lock.
 *
 * This function locks the specified read-write lock for writing. If the lock
 * is already held by another thread for reading or writing, the calling thread
 * blocks until the lock becomes available.
 *
 * @param rwlock A pointer to the read-write lock to be locked.
 *
 * @return
 * - 0 on success, indicating the write lock was acquired.
 * - EINVAL if the `rwlock` is invalid.
 * - EDEADLK if a deadlock condition is detected (optional; implementation-dependent).
 *
 * @note
 * - A write lock is exclusive, meaning no other thread can acquire a read or
 *   write lock while a write lock is held.
 * - The thread that successfully acquires the write lock must release it using
 *   `pthread_rwlock_unlock`.
 *
 * @see pthread_rwlock_unlock
 * @see pthread_rwlock_trywrlock
 * @see pthread_rwlock_timedwrlock
 * @see pthread_rwlock_rdlock
 */
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

