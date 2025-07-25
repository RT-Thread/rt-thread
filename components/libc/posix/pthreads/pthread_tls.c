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
#include "pthread_internal.h"

_pthread_key_data_t _thread_keys[PTHREAD_KEY_MAX];

/* initialize key area */
static int pthread_key_system_init(void)
{
    rt_memset(&_thread_keys[0], 0, sizeof(_thread_keys));
    return 0;
}
INIT_COMPONENT_EXPORT(pthread_key_system_init);

/**
 * @brief Retrieves the value associated with a thread-specific data key for the calling thread.
 *
 * This function returns the value that was previously set for the specified key
 * in the calling thread using `pthread_setspecific`. Each thread has its own independent
 * value for the same key.
 *
 * @param[in] key
 *     The thread-specific data key, created using `pthread_key_create`.
 *
 * @return
 * - The value associated with the key for the calling thread, or `NULL` if no value
 *   has been set for the key in this thread.
 *
 * @note
 * - If no value has been set for the key in the calling thread, `pthread_getspecific`
 *   returns `NULL`. This does not indicate an error unless `NULL` was explicitly set as the value.
 * - The value retrieved is specific to the calling thread and may differ for other threads.
 *
 * @attention
 * - If the key has been deleted using `pthread_key_delete`, the behavior of this
 *   function is undefined.
 *
 * @see pthread_key_create(), pthread_setspecific(), pthread_key_delete()
 */
void *pthread_getspecific(pthread_key_t key)
{
    struct _pthread_data* ptd;

    if (rt_thread_self() == NULL) return NULL;

    /* get pthread data from user data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != NULL);

    if (ptd->tls == NULL)
        return NULL;

    if ((key < PTHREAD_KEY_MAX) && (_thread_keys[key].is_used))
        return ptd->tls[key];

    return NULL;
}
RTM_EXPORT(pthread_getspecific);

/**
 * @brief Associates a value with a thread-specific data key for the calling thread.
 *
 * This function sets a thread-specific value for the given key. Each thread has its
 * own independent value associated with the same key, and this value is not shared with
 * other threads.
 *
 * @param[in] key
 *     The thread-specific data key, created using `pthread_key_create`.
 * @param[in] value
 *     The value to associate with the key for the calling thread. The value can be
 *     a pointer to any data or `NULL`.
 *
 * @return
 * - `0`: The value was successfully set.
 * - `EINVAL`: The specified key is invalid or not initialized.
 *
 * @note
 * - Setting a new value for a key in a thread overwrites any previously set value
 *   for that key in the same thread.
 * - The value set using `pthread_setspecific` is accessible via `pthread_getspecific`
 *   for the same thread.
 * - The association between the key and value is valid until the thread terminates,
 *   the key is deleted using `pthread_key_delete`, or a new value is set with this function.
 *
 * @attention
 * - The value is specific to the calling thread; other threads will not be affected
 *   and will continue to maintain their own independent values for the same key.
 *
 * @see pthread_key_create(), pthread_getspecific(), pthread_key_delete()
 */
int pthread_setspecific(pthread_key_t key, const void *value)
{
    struct _pthread_data* ptd;

    if (rt_thread_self() == NULL) return EINVAL;

    /* get pthread data from user data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != NULL);

    /* check tls area */
    if (ptd->tls == NULL)
    {
        ptd->tls = (void**)rt_calloc(PTHREAD_KEY_MAX, sizeof(void*));
    }

    if ((key < PTHREAD_KEY_MAX) && _thread_keys[key].is_used)
    {
        ptd->tls[key] = (void *)value;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_setspecific);

/**
 * @brief Creates a thread-specific data key.
 *
 * This function allocates a unique key for thread-specific data (TSD).
 * Each thread can use this key to access its own specific data associated with it.
 *
 * @param[out] key
 *     A pointer to a variable where the newly created key will be stored.
 *     On success, `*key` will hold the newly allocated key.
 * @param[in] destructor
 *     An optional destructor function pointer. This function will be called to
 *     clean up thread-specific data associated with the key when a thread terminates.
 *     Pass `NULL` if no cleanup is required.
 *
 * @return
 * - `0`: The key was successfully created.
 * - `EAGAIN`: The system has reached the maximum number of available keys, and no new key can be allocated.
 *
 * @note
 * - Each thread can use `pthread_setspecific` and `pthread_getspecific` to set and retrieve the thread-specific data associated with the key.
 * - The destructor function will be invoked automatically by the system when the thread terminates, if not explicitly called.
 *
 * @attention
 * - If the `destructor` function is invoked and it sets thread-specific data for the same key,
 *   the destructor may be called multiple times, up to a limit defined by the system
 *   (typically `PTHREAD_DESTRUCTOR_ITERATIONS`).
 *
 * @see pthread_setspecific(), pthread_getspecific(), pthread_key_delete()
 */
int pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
    rt_uint32_t index;

    rt_enter_critical();
    for (index = 0; index < PTHREAD_KEY_MAX; index ++)
    {
        if (_thread_keys[index].is_used == 0)
        {
            _thread_keys[index].is_used = 1;
            _thread_keys[index].destructor = destructor;

            *key = index;

            rt_exit_critical();

            return 0;
        }
    }

    rt_exit_critical();

    return EAGAIN;
}
RTM_EXPORT(pthread_key_create);

/**
 * @brief Deletes a thread-specific data key.
 *
 * This function deletes a previously created thread-specific data key.
 * The key will no longer be valid for use in `pthread_setspecific` or `pthread_getspecific`.
 *
 * @param[in] key
 *     The thread-specific data key to delete. The key must have been created with
 *     `pthread_key_create`.
 *
 * @return
 * - `0`: The key was successfully deleted.
 * - `EINVAL`: The specified key is invalid or has not been initialized.
 *
 * @note
 * - Deleting a key does not automatically free or clean up the thread-specific data
 *   associated with the key. It is the programmer's responsibility to ensure that
 *   associated resources are properly released, if necessary.
 * - After deletion, using the key in `pthread_setspecific` or `pthread_getspecific`
 *   will result in undefined behavior.
 *
 * @see pthread_key_create(), pthread_setspecific(), pthread_getspecific()
 */
int pthread_key_delete(pthread_key_t key)
{
    if (key >= PTHREAD_KEY_MAX)
        return EINVAL;

    rt_enter_critical();
    _thread_keys[key].is_used = 0;
    _thread_keys[key].destructor = 0;
    rt_exit_critical();

    return 0;
}
RTM_EXPORT(pthread_key_delete);

