/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

/**
 * @brief Initializes a mutex attributes object.
 *
 * This function initializes a mutex attributes object pointed to by `attr` with
 * default attribute values. Once initialized, the attributes object can be used
 * to customize the behavior of mutexes created using it.
 *
 * @param[out] attr Pointer to the mutex attributes object to be initialized.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure.
 *
 * @note
 * After initialization, the mutex attributes object must be destroyed with
 * `pthread_mutexattr_destroy()` when it is no longer needed.
 *
 * @warning
 * Using an uninitialized mutex attributes object may result in undefined behavior.
 *
 * @see pthread_mutexattr_destroy, pthread_mutex_init
 */
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

/**
 * @brief Destroys a mutex attributes object.
 *
 * This function releases any resources associated with the mutex attributes object
 * pointed to by `attr`. After the attributes object is destroyed, it should not
 * be used unless it is re-initialized with `pthread_mutexattr_init()`.
 *
 * @param[in,out] attr Pointer to the mutex attributes object to be destroyed.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: The attributes object is invalid or uninitialized.
 *
 * @note
 * Destroying an uninitialized or already destroyed attributes object results in undefined behavior.
 *
 * @warning
 * Ensure that no mutexes are being initialized or created using this attributes object
 * at the time of its destruction.
 *
 * @see pthread_mutexattr_init, pthread_mutex_init
 */
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

/**
 * @brief Retrieves the type attribute of a mutex attributes object.
 *
 * This function retrieves the mutex type attribute from the attributes object
 * pointed to by `attr` and stores it in the integer pointed to by `type`.
 *
 * @param[in] attr Pointer to the mutex attributes object.
 * @param[out] type Pointer to an integer where the mutex type will be stored.
 *                  Possible values include:
 *                  - `PTHREAD_MUTEX_NORMAL`: Default mutex type.
 *                  - `PTHREAD_MUTEX_ERRORCHECK`: Mutex with error-checking.
 *                  - `PTHREAD_MUTEX_RECURSIVE`: Recursive mutex.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: The attributes object or the `type` pointer is invalid.
 *
 * @note
 * Use this function to check the type of a mutex attributes object that has
 * already been initialized or configured.
 *
 * @see pthread_mutexattr_settype, pthread_mutexattr_init
 */
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

/**
 * @brief Sets the type attribute of a mutex attributes object.
 *
 * This function sets the type of the mutex to be initialized using the
 * attributes object pointed to by `attr`. The `type` can be one of the
 * following values:
 * - `PTHREAD_MUTEX_NORMAL`: Default mutex type. The mutex does not allow
 *   a thread to unlock it if it was not locked by that thread (this results
 *   in undefined behavior).
 * - `PTHREAD_MUTEX_ERRORCHECK`: Error-checking mutex type. A thread trying to
 *   lock a mutex it already holds will return an error.
 * - `PTHREAD_MUTEX_RECURSIVE`: Recursive mutex type. The same thread can lock
 *   the mutex multiple times without causing a deadlock, but it must unlock it
 *   the same number of times.
 *
 * @param[in,out] attr Pointer to the mutex attributes object.
 * @param[in] type The type to set for the mutex. One of the following:
 *                 - `PTHREAD_MUTEX_NORMAL`
 *                 - `PTHREAD_MUTEX_ERRORCHECK`
 *                 - `PTHREAD_MUTEX_RECURSIVE`
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: The specified type is invalid.
 *
 * @note
 * The type must be set before the mutex attributes object is used to
 * initialize a mutex with `pthread_mutex_init()`.
 *
 * @warning
 * Attempting to set an invalid mutex type will result in an error.
 *
 * @see pthread_mutexattr_gettype, pthread_mutexattr_init, pthread_mutex_init
 */
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

/**
 * @brief Sets the shared attribute of a mutex attributes object.
 *
 * This function sets the `pshared` attribute of the mutex attributes object
 * pointed to by `attr`. The `pshared` attribute determines whether the mutex
 * is shared between threads of the same process or can be shared between
 * threads of different processes.
 *
 * @param[in,out] attr Pointer to the mutex attributes object.
 * @param[in] pshared The sharing behavior of the mutex. This can be one of the following:
 *                   - `PTHREAD_PROCESS_PRIVATE`: The mutex is only shared between threads
 *                     of the same process (this is the default behavior).
 *                   - `PTHREAD_PROCESS_SHARED`: The mutex can be shared between threads
 *                     of different processes (requires the mutex to be allocated in
 *                     shared memory).
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: Invalid `pshared` value or invalid attributes object.
 *
 * @note
 * The `pshared` attribute must be set before the mutex attributes object is
 * used to initialize a mutex with `pthread_mutex_init()`. For shared mutexes
 * (`PTHREAD_PROCESS_SHARED`), the mutex object must be allocated in shared memory.
 *
 * @warning
 * Attempting to set an invalid `pshared` value will result in an error.
 *
 * @see pthread_mutexattr_getpshared, pthread_mutexattr_init, pthread_mutex_init
 */
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

/**
 * @brief Retrieves the shared attribute of a mutex attributes object.
 *
 * This function retrieves the `pshared` attribute from the mutex attributes
 * object pointed to by `attr` and stores it in the integer pointed to by `pshared`.
 * The `pshared` attribute indicates whether the mutex can be shared between threads
 * of different processes or only within the same process.
 *
 * @param[in] attr Pointer to the mutex attributes object.
 * @param[out] pshared Pointer to an integer where the shared attribute will be stored.
 *                    Possible values are:
 *                    - `PTHREAD_PROCESS_PRIVATE`: Mutex is shared only within the same process.
 *                    - `PTHREAD_PROCESS_SHARED`: Mutex can be shared between threads of different processes.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: Invalid attributes object or the `pshared` pointer is NULL.
 *
 * @note
 * Use this function to check the shared attribute of an already initialized
 * mutex attributes object.
 *
 * @warning
 * Attempting to get the `pshared` attribute of an uninitialized or invalid
 * attributes object will result in an error.
 *
 * @see pthread_mutexattr_setpshared, pthread_mutexattr_init, pthread_mutex_init
 */
int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared)
{
    if (!attr || !pshared)
        return EINVAL;

    *pshared = (*attr & MUTEXATTR_SHARED_MASK) ? PTHREAD_PROCESS_SHARED
                                               : PTHREAD_PROCESS_PRIVATE;
    return 0;
}
RTM_EXPORT(pthread_mutexattr_getpshared);

/**
 * @brief Initializes a mutex with optional attributes.
 *
 * This function initializes a mutex object pointed to by `mutex`. The mutex
 * can optionally be initialized with attributes specified by `attr`. If
 * `attr` is `NULL`, default attributes are used.
 *
 * @param[in,out] mutex Pointer to the mutex to be initialized.
 * @param[in] attr Pointer to the mutex attributes object. Pass `NULL` to use
 *                 default attributes.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EINVAL`: Invalid parameters or result.
 *
 * @note
 * The mutex object must be destroyed using `pthread_mutex_destroy()` after it
 * is no longer needed to free associated resources.
 *
 * @warning
 * A mutex should not be re-initialized while it is already in use.
 *
 * @see pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
 */
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

/**
 * @brief Destroys a mutex object.
 *
 * This function releases any resources associated with the mutex object
 * pointed to by `mutex`. After the mutex has been destroyed, it cannot
 * be used unless it is re-initialized with `pthread_mutex_init()`.
 *
 * @param[in,out] mutex Pointer to the mutex to be destroyed.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EBUSY`: The mutex is currently locked or being used by another thread.
 *   - `EINVAL`: The mutex is invalid or has not been initialized.
 *
 * @note
 * Before calling this function, ensure that the mutex is not locked or in use
 * by any thread. Destroying a locked mutex results in undefined behavior.
 *
 * @warning
 * Attempting to destroy a mutex that is still in use can cause resource leaks
 * or undefined behavior.
 *
 * @see pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock
 */
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

/**
 * @brief Locks a mutex.
 *
 * This function locks the mutex object pointed to by `mutex`. If the mutex is
 * already locked by another thread, the calling thread will block until the
 * mutex becomes available.
 *
 * @param[in,out] mutex Pointer to the mutex to be locked.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EDEADLK`: A deadlock condition was detected (e.g., the current thread
 *     already holds the mutex in a recursive locking scenario).
 *   - `EINVAL`: The mutex is invalid or uninitialized.
 *
 * @note
 * If the mutex is initialized with the `PTHREAD_MUTEX_RECURSIVE` attribute,
 * the same thread can lock the mutex multiple times without causing a deadlock.
 * However, the mutex must be unlocked an equal number of times before it
 * becomes available to other threads.
 *
 * @warning
 * Attempting to lock an uninitialized or already destroyed mutex results in
 * undefined behavior.
 *
 * @see pthread_mutex_unlock, pthread_mutex_trylock, pthread_mutex_init
 */
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

/**
 * @brief Unlocks a mutex.
 *
 * This function unlocks the mutex object pointed to by `mutex`. If other threads
 * are blocked waiting for the mutex, one of them will acquire the lock once it is
 * released. The calling thread must hold the lock on the mutex before calling
 * this function.
 *
 * @param[in,out] mutex Pointer to the mutex to be unlocked.
 *
 * @return
 * - 0 on success.
 * - Non-zero error code on failure, including:
 *   - `EPERM`: The current thread does not hold the lock on the mutex.
 *   - `EINVAL`: The mutex is invalid or uninitialized.
 *
 * @note
 * If the mutex was initialized with the `PTHREAD_MUTEX_RECURSIVE` attribute,
 * the mutex will only be unlocked after the calling thread unlocks it as many
 * times as it was locked.
 *
 * @warning
 * Attempting to unlock an uninitialized, destroyed, or unlocked mutex results
 * in undefined behavior.
 *
 * @see pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_init
 */
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

/**
 * @brief Attempts to lock a mutex without blocking.
 *
 * This function attempts to lock the mutex object pointed to by `mutex`. If the mutex
 * is already locked by another thread, the function returns immediately with an error
 * code instead of blocking.
 *
 * @param[in,out] mutex Pointer to the mutex to be locked.
 *
 * @return
 * - 0 on success (the mutex was successfully locked).
 * - Non-zero error code on failure, including:
 *   - `EBUSY`: The mutex is already locked by another thread.
 *   - `EINVAL`: The mutex is invalid or uninitialized.
 *
 * @note
 * This function is useful for implementing non-blocking mutex acquisition. If the mutex
 * was initialized with the `PTHREAD_MUTEX_RECURSIVE` attribute, the calling thread can
 * lock it multiple times, but must unlock it the same number of times.
 *
 * @warning
 * Attempting to trylock an uninitialized or destroyed mutex results in undefined behavior.
 *
 * @see pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_init
 */
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
