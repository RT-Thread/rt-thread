/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     Bernard      Fix pthread_detach issue for a none-joinable
 *                             thread.
 * 2019-02-07     Bernard      Add _pthread_destroy to release pthread resource.
 * 2022-05-10     xiangxistu   Modify the recycle logic about resource of pthread.
 * 2024-04-15     atwww        Modify the recycle logic of TLS in function _pthread_data_destroy,
 *                                    make it safe for C++11's thread_local destructors.
 */

#include <rthw.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include "pthread_internal.h"

RT_DEFINE_HW_SPINLOCK(pth_lock);
_pthread_data_t *pth_table[PTHREAD_NUM_MAX] = {NULL};
static int concurrency_level;

_pthread_data_t *_pthread_get_data(pthread_t thread)
{
    _pthread_data_t *ptd;

    if (thread >= PTHREAD_NUM_MAX) return NULL;

    rt_hw_spin_lock(&pth_lock);
    ptd = pth_table[thread];
    rt_hw_spin_unlock(&pth_lock);

    if (ptd && ptd->magic == PTHREAD_MAGIC) return ptd;

    return NULL;
}

pthread_t _pthread_data_get_pth(_pthread_data_t *ptd)
{
    int index;

    rt_hw_spin_lock(&pth_lock);
    for (index = 0; index < PTHREAD_NUM_MAX; index ++)
    {
        if (pth_table[index] == ptd) break;
    }
    rt_hw_spin_unlock(&pth_lock);

    return index;
}

pthread_t _pthread_data_create(void)
{
    int index;
    _pthread_data_t *ptd = NULL;

    ptd = (_pthread_data_t*)rt_malloc(sizeof(_pthread_data_t));
    if (!ptd) return PTHREAD_NUM_MAX;

    memset(ptd, 0x0, sizeof(_pthread_data_t));
    ptd->canceled = 0;
    ptd->cancelstate = PTHREAD_CANCEL_DISABLE;
    ptd->canceltype = PTHREAD_CANCEL_DEFERRED;
    ptd->magic = PTHREAD_MAGIC;

    rt_hw_spin_lock(&pth_lock);
    for (index = 0; index < PTHREAD_NUM_MAX; index ++)
    {
        if (pth_table[index] == NULL)
        {
            pth_table[index] = ptd;
            break;
        }
    }
    rt_hw_spin_unlock(&pth_lock);

    /* full of pthreads, clean magic and release ptd */
    if (index == PTHREAD_NUM_MAX)
    {
        ptd->magic = 0x0;
        rt_free(ptd);
    }

    return index;
}

static inline void _destroy_item(int index, _pthread_data_t *ptd)
{
    extern _pthread_key_data_t _thread_keys[PTHREAD_KEY_MAX];
    void *data;

    if (_thread_keys[index].is_used)
    {
        data = ptd->tls[index];
        if (data && _thread_keys[index].destructor)
        {
            _thread_keys[index].destructor(data);
        }
    }
}

#ifdef RT_USING_CPLUSPLUS11
    #define NOT_USE_CXX_TLS -1
#endif

void _pthread_data_destroy(_pthread_data_t *ptd)
{
    pthread_t pth;

    if (ptd)
    {
        /* if this thread create the local thread data,
         * destruct thread local key
         */
        if (ptd->tls != RT_NULL)
        {
            int index;
#ifdef RT_USING_CPLUSPLUS11
            /* If C++11 is enabled and emutls is used,
             * destructors of C++ object must be called safely.
             */
            extern pthread_key_t emutls_get_pthread_key(void);
            pthread_key_t emutls_pthread_key = emutls_get_pthread_key();

            if (emutls_pthread_key != NOT_USE_CXX_TLS)
            {
                /* If execution reaches here, C++ 'thread_local' may be used.
                 * Destructors of c++ class object must be called before emutls_key_destructor.
                 */
                int start = ((emutls_pthread_key - 1 + PTHREAD_KEY_MAX) % PTHREAD_KEY_MAX);
                int i = 0;
                for (index = start; i < PTHREAD_KEY_MAX; index = (index - 1 + PTHREAD_KEY_MAX) % PTHREAD_KEY_MAX, i ++)
                {
                    _destroy_item(index, ptd);
                }
            }
            else
#endif
            {
                /* If only C TLS is used, that is, POSIX TLS or __Thread_local,
                 * just iterate the _thread_keys from index 0.
                 */
                for (index = 0; index < PTHREAD_KEY_MAX; index ++)
                {
                    _destroy_item(index, ptd);
                }
            }
            /* release tls area */
            rt_free(ptd->tls);
            ptd->tls = RT_NULL;
        }

        pth  = _pthread_data_get_pth(ptd);
        /* remove from pthread table */
        rt_hw_spin_lock(&pth_lock);
        pth_table[pth] = NULL;
        rt_hw_spin_unlock(&pth_lock);

        /* delete joinable semaphore */
        if (ptd->joinable_sem != RT_NULL)
        {
            rt_sem_delete(ptd->joinable_sem);
            ptd->joinable_sem = RT_NULL;
        }

        /* clean magic */
        ptd->magic = 0x0;

        /* clear the "ptd->tid->pthread_data" */
        ptd->tid->pthread_data = RT_NULL;

        /* free ptd */
        rt_free(ptd);
    }
}

static void _pthread_cleanup(rt_thread_t tid)
{
    /* clear cleanup function */
    tid->cleanup = RT_NULL;

    /* restore tid stack */
    rt_free(tid->stack_addr);

    /* restore tid control block */
    rt_free(tid);
}

static void pthread_entry_stub(void *parameter)
{
    void *value;
    _pthread_data_t *ptd;

    ptd = (_pthread_data_t *)parameter;

    /* execute pthread entry */
    value = ptd->thread_entry(ptd->thread_parameter);

    /* According to "detachstate" to whether or not to recycle resource immediately */
    if (ptd->attr.detachstate == PTHREAD_CREATE_JOINABLE)
    {
        /* set value */
        ptd->return_value = value;
        rt_sem_release(ptd->joinable_sem);
    }
    else
    {
        /* release pthread resource */
        _pthread_data_destroy(ptd);
    }
}

/**
 * @brief Creates a new thread in a POSIX-compliant system.
 *
 * The `pthread_create` function initializes a new thread in the calling process. The new thread starts execution
 * by invoking the function specified by the `start` parameter. The thread runs concurrently with the calling thread.
 *
 * @param[out] pid
 *   A pointer to a `pthread_t` object where the ID of the newly created thread will be stored.
 *   This ID can be used to refer to the thread in subsequent function calls.
 *
 * @param[in] attr
 *   A pointer to a `pthread_attr_t` object that specifies attributes for the new thread, or `NULL` for default attributes.
 *   Default attributes include:
 *   - Detached state: joinable.
 *   - Stack size: implementation-defined default.
 *
 * @param[in] start
 *   A pointer to the function that the new thread will execute. This function must have the following signature:
 *   `void *start(void *parameter)`.
 *
 * @param[in] parameter
 *   A pointer to data passed as an argument to the `start` function. The meaning and handling of this data is determined
 *   by the `start` function.
 *
 * @return
 *   Returns 0 on success. On failure, a non-zero error code is returned, indicating the error condition:
 *   - `EAGAIN`: Insufficient resources to create another thread.
 *   - `EINVAL`: Invalid attributes specified in `attr`.
 *   - `EPERM`: Insufficient permissions to set the requested attributes.
 *
 * @note
 *   It is the caller's responsibility to manage the lifetime of any resources associated with the new thread.
 *   If the thread is not detached, it must be joined using `pthread_join` to avoid resource leaks.
 *
 * @see pthread_join, pthread_exit, pthread_attr_init
 */
int pthread_create(pthread_t            *pid,
                   const pthread_attr_t *attr,
                   void *(*start)(void *), void *parameter)
{
    int ret = 0;
    void *stack;
    char name[RT_NAME_MAX];
    static rt_uint16_t pthread_number = 0;

    pthread_t pth_id;
    _pthread_data_t *ptd;

    /* pid shall be provided */
    RT_ASSERT(pid != RT_NULL);

    /* allocate posix thread data */
    pth_id = _pthread_data_create();
    if (pth_id == PTHREAD_NUM_MAX)
    {
        ret = ENOMEM;
        goto __exit;
    }
    /* get pthread data */
    ptd = _pthread_get_data(pth_id);

    RT_ASSERT(ptd != RT_NULL);

    if (attr != RT_NULL)
    {
        ptd->attr = *attr;
    }
    else
    {
        /* use default attribute */
        pthread_attr_init(&ptd->attr);
    }

    if (ptd->attr.stacksize == 0)
    {
        ret = EINVAL;
        goto __exit;
    }

    rt_snprintf(name, sizeof(name), "pth%02d", pthread_number ++);

    /* pthread is a static thread object */
    ptd->tid = (rt_thread_t) rt_malloc(sizeof(struct rt_thread));
    if (ptd->tid == RT_NULL)
    {
        ret = ENOMEM;
        goto __exit;
    }
    memset(ptd->tid, 0, sizeof(struct rt_thread));

    if (ptd->attr.detachstate == PTHREAD_CREATE_JOINABLE)
    {
        ptd->joinable_sem = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO);
        if (ptd->joinable_sem == RT_NULL)
        {
            ret = ENOMEM;
            goto __exit;
        }
    }
    else
    {
        ptd->joinable_sem = RT_NULL;
    }

    /* set parameter */
    ptd->thread_entry = start;
    ptd->thread_parameter = parameter;

    /* stack */
    if (ptd->attr.stackaddr == 0)
    {
        stack = (void *)rt_malloc(ptd->attr.stacksize);
    }
    else
    {
        stack = (void *)(ptd->attr.stackaddr);
    }

    if (stack == RT_NULL)
    {
        ret = ENOMEM;
        goto __exit;
    }

    /* initial this pthread to system */
    if (rt_thread_init(ptd->tid, name, pthread_entry_stub, ptd,
                       stack, ptd->attr.stacksize,
                       ptd->attr.schedparam.sched_priority, 20) != RT_EOK)
    {
        ret = EINVAL;
        goto __exit;
    }

    /* set pthread id */
    *pid = pth_id;

    /* set pthread cleanup function and ptd data */
    ptd->tid->cleanup = _pthread_cleanup;
    ptd->tid->pthread_data = (void *)ptd;

    /* start thread */
    if (rt_thread_startup(ptd->tid) == RT_EOK)
        return 0;

    /* start thread failed */
    rt_thread_detach(ptd->tid);
    ret = EINVAL;

__exit:
    if (pth_id != PTHREAD_NUM_MAX)
    {
        _pthread_data_destroy(ptd);
    }
    return ret;
}
RTM_EXPORT(pthread_create);

/**
 * @brief Marks a thread as detached, allowing its resources to be automatically released upon termination.
 *
 * The `pthread_detach` function separates the specified thread from the calling thread. Once a thread is detached,
 * its resources will be automatically reclaimed by the system upon the thread's termination. A detached thread cannot
 * be joined using `pthread_join`.
 *
 * @param[in] thread
 *   The thread ID of the thread to be detached. This must be a valid thread ID returned by `pthread_create`.
 *
 * @return
 *   Returns 0 on success. On failure, an error code is returned:
 *   - `EINVAL`: The specified thread is not joinable or is already detached.
 *   - `ESRCH`: No thread with the specified ID could be found.
 *
 * @note
 *   - Detaching a thread allows it to run independently. Once detached, the thread's termination status cannot
 *     be retrieved, and it cannot be joined.
 *   - Threads can be created in a detached state using attributes set with `pthread_attr_setdetachstate`.
 *
 * @see pthread_create, pthread_join, pthread_attr_setdetachstate
 */
int pthread_detach(pthread_t thread)
{
    int ret = 0;
    _pthread_data_t *ptd = _pthread_get_data(thread);
    if (ptd == RT_NULL)
    {
        /* invalid pthread id */
        ret = EINVAL;
        goto __exit;
    }

    if (ptd->attr.detachstate == PTHREAD_CREATE_DETACHED)
    {
        /* The implementation has detected that the value specified by thread does not refer
         * to a joinable thread.
         */
        ret = EINVAL;
        goto __exit;
    }

    if ((RT_SCHED_CTX(ptd->tid).stat & RT_THREAD_STAT_MASK) == RT_THREAD_CLOSE)
    {
        /* destroy this pthread */
        _pthread_data_destroy(ptd);
        goto __exit;
    }
    else
    {
        /* change to detach state */
        ptd->attr.detachstate = PTHREAD_CREATE_DETACHED;

        /* detach joinable semaphore */
        if (ptd->joinable_sem)
        {
            rt_sem_delete(ptd->joinable_sem);
            ptd->joinable_sem = RT_NULL;
        }
    }

__exit:
    return ret;
}
RTM_EXPORT(pthread_detach);

/**
 * @brief Waits for the specified thread to terminate and retrieves its exit status.
 *
 * The `pthread_join` function blocks the calling thread until the specified thread terminates.
 * If the specified thread has already terminated, it returns immediately. The exit status of
 * the terminated thread can optionally be retrieved via the `value_ptr` parameter.
 *
 * @param[in] thread
 *   The thread ID of the thread to wait for. This must be a joinable thread created with `pthread_create`.
 *
 * @param[out] value_ptr
 *   A pointer to a location where the exit status of the terminated thread will be stored.
 *   If the thread terminated by calling `pthread_exit`, the value passed to `pthread_exit`
 *   will be stored at this location. If this parameter is `NULL`, the exit status is ignored.
 *
 * @return
 *   Returns 0 on success. On failure, an error code is returned:
 *   - `ESRCH`: The specified thread does not exist.
 *   - `EINVAL`: The specified thread is not joinable.
 *   - `EDEADLK`: A deadlock was detected (e.g., a thread tries to join itself).
 *
 * @note
 *   - Threads must not be detached to use `pthread_join`.
 *   - If `pthread_join` is not called for joinable threads, their resources are not released, leading to resource leaks.
 *
 * @see pthread_create, pthread_exit, pthread_detach
 */
int pthread_join(pthread_t thread, void **value_ptr)
{
    _pthread_data_t *ptd;
    rt_err_t result;

    ptd = _pthread_get_data(thread);

    if (ptd == RT_NULL)
    {
        return EINVAL; /* invalid pthread id */
    }

    if (ptd->tid == rt_thread_self())
    {
        /* join self */
        return EDEADLK;
    }

    if (ptd->attr.detachstate == PTHREAD_CREATE_DETACHED)
    {
        return EINVAL; /* join on a detached pthread */
    }

    result = rt_sem_take(ptd->joinable_sem, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        /* get return value */
        if (value_ptr != RT_NULL)
            *value_ptr = ptd->return_value;

        /* destroy this pthread */
        _pthread_data_destroy(ptd);
    }
    else
    {
        return ESRCH;
    }

    return 0;
}
RTM_EXPORT(pthread_join);

/**
 * @brief Returns the thread ID of the calling thread.
 *
 * The `pthread_self` function returns the thread ID of the calling thread. The thread ID is unique to the
 * thread within a process and can be used to identify the calling thread in the context of multithreading.
 *
 * The value returned by `pthread_self` can be compared with the thread IDs of other threads to determine
 * if two threads are the same.
 *
 * @return
 *   The thread ID of the calling thread.
 *
 * @note
 *   - The thread ID returned by `pthread_self` is not the same as the operating system's thread ID.
 *   - This function does not affect the calling thread's state or execution.
 *   - The thread ID returned by `pthread_self` is only meaningful in the context of the current process.
 *
 * @see pthread_create, pthread_equal, pthread_join
 */
pthread_t pthread_self (void)
{
    rt_thread_t tid;
    _pthread_data_t *ptd;

    tid = rt_thread_self();
    if (tid == NULL) return PTHREAD_NUM_MAX;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    return _pthread_data_get_pth(ptd);
}
RTM_EXPORT(pthread_self);

/**
 * @brief Retrieves the clock ID for the specified thread.
 *
 * The `pthread_getcpuclockid` function retrieves the clock ID associated with the CPU time used
 * by the specified thread.
 *
 * @param[in] thread
 *   The thread whose CPU clock ID is to be retrieved. If the thread is the calling thread,
 *   the current thread's ID is used.
 *
 * @param[out] clock_id
 *   A pointer to a `clockid_t` variable that will be filled with the clock ID associated
 *   with the specified thread.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the `thread` is not a valid thread identifier.
 *   - `ESRCH` if the specified thread does not exist.
 *
 * @note
 *   The clock returned by this function is specific to the thread and is different from the
 *   system-wide clock. It measures the CPU time consumed by the specified thread, not wall-clock
 *   time. The thread's CPU time can be obtained using `clock_gettime` with the returned `clock_id`.
 *
 * @see clock_gettime, pthread_create, pthread_self
 */
int pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id)
{
    if(_pthread_get_data(thread) == NULL)
    {
        return EINVAL;
    }

    *clock_id = (clockid_t)rt_tick_get();

    return 0;
}
RTM_EXPORT(pthread_getcpuclockid);

/**
 * @brief Retrieves the current concurrency level of the program.
 *
 * The `pthread_getconcurrency` function returns the current concurrency level of the program.
 * This value represents the number of threads that can run concurrently in the program,
 * based on the current settings of the pthreads library. It is used to help tune the behavior
 * of thread scheduling in some systems.
 *
 * @return
 *   The current concurrency level of the program.
 *   - The value is an integer representing the number of threads that are permitted to run
 *     concurrently in the system, based on the library's current configuration.
 *   - A return value of `0` typically means that the system is using the default concurrency
 *     level, which may be determined automatically by the system or by thread creation behavior.
 *
 * @note
 *   - The behavior and meaning of concurrency levels can be implementation-dependent,
 *     and it may vary across different systems or environments.
 *   - The function is typically used for diagnostic purposes, and its behavior may not
 *     affect thread execution directly.
 *
 * @see pthread_setconcurrency
 */
int pthread_getconcurrency(void)
{
    return concurrency_level;
}
RTM_EXPORT(pthread_getconcurrency);

/**
 * @brief Sets the concurrency level of the program.
 *
 * The `pthread_setconcurrency` function sets the number of threads that are allowed to run concurrently.
 * The concurrency level defines the maximum number of threads that can be executed in parallel by the system.
 * This is useful for tuning thread behavior and controlling system resource usage, especially in environments
 * with limited resources (e.g., CPU cores).
 *
 * @param[in] new_level
 *   The new concurrency level to be set. This value represents the number of threads that can execute concurrently.
 *   - A value of `0` typically means that the system will automatically determine the concurrency level based on
 *     the system's configuration and available resources.
 *   - A non-zero value explicitly sets the maximum number of threads that can run concurrently.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the `new_level` is invalid or if the system does not support this functionality.
 *
 * @note
 *   - The behavior of this function is system-dependent. Some systems may ignore the concurrency setting
 *     and automatically manage the concurrency based on available resources (e.g., CPU cores).
 *   - This function may not have any effect on systems that do not support concurrency settings at the library level.
 *   - The concurrency level controls thread scheduling policies and is intended to influence how the thread library
 *     manages threads, not how the operating system schedules them at the kernel level.
 *
 * @see pthread_getconcurrency
 */
int pthread_setconcurrency(int new_level)
{
    concurrency_level = new_level;

    return 0;
}
RTM_EXPORT(pthread_setconcurrency);

/**
 * @brief Retrieves the scheduling policy and parameters of a thread.
 *
 * The `pthread_getschedparam` function retrieves the scheduling policy and the scheduling parameters
 * (such as priority) for the specified thread. This allows you to check the scheduling settings of a thread
 * and can be useful for thread management and performance tuning in a multithreaded application.
 *
 * @param[in] thread
 *   The thread whose scheduling policy and parameters are to be retrieved. This is typically a valid
 *   `pthread_t` identifier of a thread that has already been created.
 *
 * @param[out] policy
 *   A pointer to an integer where the scheduling policy of the specified thread will be stored. The
 *   value will be one of the following constants defined in `<sched.h>`:
 *   - `SCHED_FIFO`: First-in, first-out scheduling policy.
 *   - `SCHED_RR`: Round-robin scheduling policy.
 *   - `SCHED_OTHER`: Default policy, which is typically used by non-realtime threads.
 *   - `SCHED_IDLE`: For idle threads (system-level threads that do minimal work).
 *   - `SCHED_BATCH`: For threads that should be scheduled with lower priority than interactive threads.
 *   - `SCHED_DEADLINE`: A policy that allows specifying real-time deadlines (on systems that support it).
 *
 * @param[out] param
 *   A pointer to a `struct sched_param` where the scheduling parameters (e.g., priority) for the thread
 *   will be stored. The `sched_param` structure typically contains:
 *   - `sched_priority`: The priority value associated with the thread's scheduling policy.
 *
 * @return
 *   - `0` on success.
 *   - `ESRCH` if the specified thread does not exist.
 *   - `EINVAL` if an invalid argument is provided, such as an invalid thread ID or null pointers for the policy or parameters.
 *
 * @note
 *   - This function retrieves the current scheduling settings for a thread. These settings can be used
 *     to monitor or adjust thread behavior.
 *   - The scheduling policies and priorities may be platform-dependent and subject to system configuration.
 *
 * @see pthread_setschedparam, sched_getparam
 */
int pthread_getschedparam(pthread_t thread, int *policy, struct sched_param *param)
{
    _pthread_data_t *ptd;

    ptd = _pthread_get_data(thread);
    pthread_attr_getschedpolicy(&ptd->attr, policy);
    pthread_attr_getschedparam(&ptd->attr, param);

    return 0;
}
RTM_EXPORT(pthread_getschedparam);

/**
 * @brief Sets the scheduling policy and parameters for a thread.
 *
 * The `pthread_setschedparam` function sets the scheduling policy and scheduling parameters (such as priority)
 * for the specified thread. This allows you to control how the thread is scheduled by the operating system.
 * It is useful for adjusting thread behavior, especially for real-time or performance-sensitive applications.
 *
 * @param[in] thread
 *   The thread whose scheduling policy and parameters are to be set. This is a valid `pthread_t` identifier.
 *
 * @param[in] policy
 *   The scheduling policy to be set for the thread. This can be one of the following values:
 *   - `SCHED_FIFO`: First-in, first-out scheduling policy, where threads are scheduled based on their arrival time.
 *   - `SCHED_RR`: Round-robin scheduling policy, where each thread is allocated a fixed time slice and scheduled cyclically.
 *   - `SCHED_OTHER`: Default policy for non-realtime threads.
 *   - `SCHED_IDLE`: For threads intended to run only when no other threads are runnable.
 *   - `SCHED_BATCH`: For threads that should run with lower priority than interactive threads.
 *   - `SCHED_DEADLINE`: For real-time threads that have a specified deadline (if supported).
 *
 * @param[in] param
 *   A pointer to a `struct sched_param`, which contains the scheduling parameters, typically the thread's priority.
 *   The `sched_priority` field is the most commonly used parameter, and it controls the thread's priority within
 *   the specified scheduling policy.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if an invalid policy or parameter is provided.
 *   - `ESRCH` if the specified thread does not exist.
 *   - `EPERM` if the caller does not have permission to modify the thread's scheduling attributes.
 *
 * @note
 *   - The `sched_param` structure's `sched_priority` field specifies the priority of the thread. The priority
 *     range depends on the policy used. For example, for `SCHED_FIFO` and `SCHED_RR`, higher priority values
 *     correspond to higher priority threads, while for `SCHED_OTHER`, priorities are not as strictly enforced.
 *   - Changing a thread's scheduling parameters may affect its execution behavior, including how it competes with
 *     other threads for CPU time.
 *   - The system may not allow you to modify scheduling parameters for all threads, depending on system configuration
 *     and privileges.
 *
 * @see pthread_getschedparam
 */
int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param)
{
    _pthread_data_t *ptd;

    ptd = _pthread_get_data(thread);
    pthread_attr_setschedpolicy(&ptd->attr, policy);
    pthread_attr_setschedparam(&ptd->attr, param);

    return 0;
}
RTM_EXPORT(pthread_setschedparam);

/**
 * @brief Sets the scheduling priority for a thread.
 *
 * The `pthread_setschedprio` function adjusts the priority of the specified thread while leaving its
 * scheduling policy unchanged. This is useful for fine-tuning thread behavior in multithreaded applications.
 *
 * @param[in] thread
 *   The thread whose scheduling priority is to be changed. This must be a valid `pthread_t` identifier.
 *
 * @param[in] prio
 *   The new scheduling priority for the thread. The priority must fall within the valid range for the
 *   thread's current scheduling policy, as defined by `sched_get_priority_min` and `sched_get_priority_max`.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the specified priority is invalid for the thread's current scheduling policy.
 *   - `ESRCH` if the specified thread does not exist.
 *   - `EPERM` if the calling process lacks the necessary privileges to set the thread's priority.
 *
 * @note
 *   - Changing a thread's priority may require elevated privileges (e.g., root) on certain systems, especially
 *     for real-time priorities.
 *   - The priority range and behavior depend on the thread's current scheduling policy. For example:
 *     - `SCHED_FIFO` and `SCHED_RR`: Priorities are used for strict scheduling.
 *     - `SCHED_OTHER`: Priorities may have minimal or no effect.
 *   - The behavior of this function is platform-dependent and may vary between different operating systems.
 *
 * @see pthread_setschedparam, pthread_getschedparam
 */
int pthread_setschedprio(pthread_t thread, int prio)
{
    _pthread_data_t *ptd;
    struct sched_param param;

    ptd = _pthread_get_data(thread);
    param.sched_priority = prio;
    pthread_attr_setschedparam(&ptd->attr, &param);

    return 0;
}
RTM_EXPORT(pthread_setschedprio);

/**
 * @brief Terminates the calling thread and optionally returns a value.
 *
 * The `pthread_exit` function terminates the calling thread. It can optionally provide an exit status that can be
 * retrieved by other threads that join the calling thread using `pthread_join`. If the thread is detached, the
 * exit status is ignored and the system automatically reclaims resources once the thread terminates.
 *
 * @param[in] value
 *   A pointer to a value that will be returned to any thread that calls `pthread_join` on this thread.
 *   If `NULL`, no value is returned.
 *
 * @note
 *   - This function does not terminate the process. It only terminates the calling thread.
 *   - If the calling thread is the main thread, `pthread_exit` allows other threads to continue execution.
 *   - If a thread terminates without calling `pthread_exit`, it returns control to the system when the thread's function ends.
 *
 * @see pthread_join, pthread_create
 */
void pthread_exit(void *value)
{
    _pthread_data_t *ptd;
    _pthread_cleanup_t *cleanup;
    rt_thread_t tid;

    if (rt_thread_self() == RT_NULL)
    {
        return;
    }

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;

    rt_enter_critical();
    /* disable cancel */
    ptd->cancelstate = PTHREAD_CANCEL_DISABLE;
    /* set return value */
    ptd->return_value = value;
    rt_exit_critical();

    /*
    * When use pthread_exit to exit.
    * invoke pushed cleanup
    */
    while (ptd->cleanup != RT_NULL)
    {
        cleanup = ptd->cleanup;
        ptd->cleanup = cleanup->next;

        cleanup->cleanup_func(cleanup->parameter);
        /* release this cleanup function */
        rt_free(cleanup);
    }

    /* get the info aboult "tid" early */
    tid = ptd->tid;

    /* According to "detachstate" to whether or not to recycle resource immediately */
    if (ptd->attr.detachstate == PTHREAD_CREATE_JOINABLE)
    {
        /* set value */
        rt_sem_release(ptd->joinable_sem);
    }
    else
    {
        /* release pthread resource */
        _pthread_data_destroy(ptd);
    }

    /*
        * second: detach thread.
        * this thread will be removed from scheduler list
        * and because there is a cleanup function in the
        * thread (pthread_cleanup), it will move to defunct
        * thread list and wait for handling in idle thread.
        */
    rt_thread_detach(tid);

    /* reschedule thread */
    rt_schedule();
}
RTM_EXPORT(pthread_exit);

/**
 * @brief Executes a routine once in a multithreaded environment.
 *
 * The `pthread_once` function ensures that the specified initialization routine is executed exactly once,
 * even if multiple threads attempt to execute it simultaneously. It is typically used for one-time
 * initialization tasks in a multithreaded program.
 *
 * @param[in] once_control
 *   A pointer to a `pthread_once_t` control variable. The init_routine can only be excuted
 *   when (*once_control) is zero.
 *
 * @param[in] init_routine
 *   A pointer to the initialization routine to be executed. This routine takes no arguments and
 *   returns no value. It is guaranteed to be executed exactly once.
 *
 * @return
 *   - `0` on success.
 *
 * @note
 *   - The `pthread_once` function is thread-safe and guarantees that the `init_routine` is called only once.
 *   - The `once_control` variable must remain valid and should not be modified by the application after
 *     initialization.
 *   - If the initialization routine fails or encounters an error, it is the responsibility of the routine
 *     to handle it appropriately.
 *
 * @see pthread_mutex_lock, pthread_mutex_unlock
 */
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
{
    RT_ASSERT(once_control != RT_NULL);
    RT_ASSERT(init_routine != RT_NULL);

    rt_enter_critical();
    if (!(*once_control))
    {
        /* call routine once */
        *once_control = 1;
        rt_exit_critical();

        init_routine();
    }
    rt_exit_critical();

    return 0;
}
RTM_EXPORT(pthread_once);

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_atfork);

/**
 * @brief Sends a signal to a specific thread.
 *
 * The `pthread_kill` function sends the specified signal to the target thread. This allows fine-grained
 * control over signal handling in multithreaded applications.
 *
 * @param[in] thread
 *   The target thread to which the signal is sent. This is a valid `pthread_t` identifier.
 *
 * @param[in] sig
 *   The signal to be sent. This can be any valid signal, such as those defined in `<signal.h>`. For example:
 *   - `SIGTERM`: Request thread termination.
 *   - `SIGUSR1` or `SIGUSR2`: User-defined signals.
 *   - `0`: Used to check if the thread is still valid without sending a signal.
 *
 * @return
 *   - `0` on success.
 *   - `ESRCH` if the specified thread does not exist or is invalid.
 *   - `EINVAL` if the signal number `sig` is invalid.
 *
 * @note
 *   - The signal is delivered to the specified thread only if the thread has the appropriate signal handlers
 *     set up. Unhandled signals might result in the default action for that signal.
 *   - If `sig` is `0`, no signal is sent, but the function checks if the thread is valid and exists.
 *   - Signal handling behavior is shared across threads in a process. For example, blocking or ignoring a signal
 *     in one thread affects the entire process.
 *
 * @see pthread_sigmask, sigaction
 */
int pthread_kill(pthread_t thread, int sig)
{
#ifdef RT_USING_SIGNALS
    _pthread_data_t *ptd;
    int ret;

    ptd = _pthread_get_data(thread);
    if (ptd)
    {
        ret = rt_thread_kill(ptd->tid, sig);
        if (ret == -RT_EINVAL)
        {
            return EINVAL;
        }

        return ret;
    }

    return ESRCH;
#else
    return ENOSYS;
#endif
}
RTM_EXPORT(pthread_kill);

#ifdef RT_USING_SIGNALS
/**
 * @brief Modifies or retrieves the signal mask of the calling thread.
 *
 * The `pthread_sigmask` function allows a thread to block, unblock, or examine the signals in its signal mask.
 * Signals that are blocked are not delivered to the thread until they are unblocked.
 *
 * @param[in] how
 *   Specifies how the signal mask is modified. Possible values:
 *   - `SIG_BLOCK`: Add the signals in `set` to the current signal mask.
 *   - `SIG_UNBLOCK`: Remove the signals in `set` from the current signal mask.
 *   - `SIG_SETMASK`: Replace the current signal mask with the signals in `set`.
 *
 * @param[in] set
 *   A pointer to a `sigset_t` containing the signals to be modified in the mask. Can be `NULL` if no change is needed.
 *
 * @param[out] oset
 *   A pointer to a `sigset_t` where the previous signal mask will be stored. Can be `NULL` if the previous mask is not required.
 *
 * @return
 *   - `0` on success.
 *
 * @note
 *   - Signal masks are thread-specific in a multithreaded program.
 *   - The `pthread_sigmask` function is designed for multithreaded programs, whereas `sigprocmask` should not be used.
 *   - Blocking a signal prevents it from being delivered to the thread until unblocked.
 *
 * @see sigprocmask, sigaction, pthread_kill
 */
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oset)
{
    return sigprocmask(how, set, oset);
}
#endif

/**
 * @brief Unregisters a cleanup handler and optionally executes it.
 *
 * The `pthread_cleanup_pop` function unregisters a cleanup handler that was previously registered
 * using `pthread_cleanup_push`. If the `execute` parameter is non-zero, the cleanup handler is executed
 * at the point where the thread terminates or is canceled.
 *
 * If `execute` is zero, the handler is unregistered without being executed. This allows the handler
 * to be removed from the cleanup stack without performing any actions.
 *
 * @param[in] execute
 *   If non-zero, the cleanup handler is executed when the thread terminates or is canceled.
 *   If zero, the handler is simply removed from the stack without executing it.
 *
 * @note
 *   - Cleanup handlers are executed in the reverse order of their registration (i.e., last-in, first-out).
 *   - It is important to use `pthread_cleanup_push` to register cleanup handlers and `pthread_cleanup_pop`
 *     to ensure they are properly unregistered and executed if needed.
 *   - This function should be paired with `pthread_cleanup_push` to manage cleanup handlers effectively.
 *
 * @see pthread_cleanup_push, pthread_exit, pthread_cancel
 */
void pthread_cleanup_pop(int execute)
{
    _pthread_data_t *ptd;
    _pthread_cleanup_t *cleanup;

    if (rt_thread_self() == NULL) return;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    if (execute)
    {
        rt_enter_critical();
        cleanup = ptd->cleanup;
        if (cleanup)
            ptd->cleanup = cleanup->next;
        rt_exit_critical();

        if (cleanup)
        {
            cleanup->cleanup_func(cleanup->parameter);

            rt_free(cleanup);
        }
    }
}
RTM_EXPORT(pthread_cleanup_pop);

/**
 * @brief Registers a cleanup handler to be executed when the calling thread terminates.
 *
 * The `pthread_cleanup_push` function registers a cleanup handler that is executed when the calling thread
 * is canceled or exits (either normally or via `pthread_exit`). The cleanup handler will be executed
 * in the reverse order of their registration.
 *
 * The cleanup handler can be used to release resources such as memory or file descriptors when the thread
 * is terminated, whether it terminates normally or is canceled.
 *
 * @param[in] routine
 *   A pointer to the cleanup handler function. The function must have the following signature:
 *   `void routine(void* arg);`. It is invoked when the thread terminates or is canceled.
 *
 * @param[in] arg
 *   A pointer to the argument that will be passed to the cleanup handler (`routine`).
 *   This allows the handler to perform actions with the passed argument.
 *
 * @note
 *   - The cleanup handler is automatically invoked when a thread terminates or is canceled.
 *   - The cleanup handlers are executed in the reverse order of their registration, similar to how
 *     destructors are executed in a stack-based fashion.
 *   - `pthread_cleanup_pop` must be called to unregister the cleanup handler. It ensures that the handler
 *     is only invoked during the thread's termination process.
 *
 * @see pthread_cleanup_pop, pthread_cancel, pthread_exit
 */
void pthread_cleanup_push(void (*routine)(void *), void *arg)
{
    _pthread_data_t *ptd;
    _pthread_cleanup_t *cleanup;

    if (rt_thread_self() == NULL) return;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    cleanup = (_pthread_cleanup_t *)rt_malloc(sizeof(_pthread_cleanup_t));
    if (cleanup != RT_NULL)
    {
        cleanup->cleanup_func = routine;
        cleanup->parameter = arg;

        rt_enter_critical();
        cleanup->next = ptd->cleanup;
        ptd->cleanup = cleanup;
        rt_exit_critical();
    }
}
RTM_EXPORT(pthread_cleanup_push);

/*
 * According to IEEE Std 1003.1, 2004 Edition , following pthreads
 * interface support cancellation point:
 * mq_receive()
 * mq_send()
 * mq_timedreceive()
 * mq_timedsend()
 * msgrcv()
 * msgsnd()
 * msync()
 * pthread_cond_timedwait()
 * pthread_cond_wait()
 * pthread_join()
 * pthread_testcancel()
 * sem_timedwait()
 * sem_wait()
 *
 * A cancellation point may also occur when a thread is
 * executing the following functions:
 * pthread_rwlock_rdlock()
 * pthread_rwlock_timedrdlock()
 * pthread_rwlock_timedwrlock()
 * pthread_rwlock_wrlock()
 *
 * The pthread_cancel(), pthread_setcancelstate(), and pthread_setcanceltype()
 * functions are defined to be async-cancel safe.
 */

/**
 * @brief Sets the cancelability state of the calling thread.
 *
 * The `pthread_setcancelstate` function allows a thread to enable or disable its ability to be canceled
 * by another thread. Cancelability determines if and when a thread responds to a cancellation request.
 *
 * @param[in] state
 *   The new cancelability state for the calling thread. Possible values:
 *   - `PTHREAD_CANCEL_ENABLE`: The thread can be canceled.
 *   - `PTHREAD_CANCEL_DISABLE`: The thread cannot be canceled.
 *
 * @param[out] oldstate
 *   A pointer to an integer where the previous cancelability state will be stored. Can be `NULL` if
 *   the previous state is not needed.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the `state` is not a valid cancelability state.
 *
 * @note
 *   - The cancelability state affects how the thread responds to cancellation requests:
 *     - In the `PTHREAD_CANCEL_DISABLE` state, cancellation requests are held pending until the state is changed to `PTHREAD_CANCEL_ENABLE`.
 *   - Cancelability is distinct from the cancelability type, which controls the timing of cancellation (deferred or asynchronous).
 *   - By default, threads are created with `PTHREAD_CANCEL_ENABLE`.
 *
 * @see pthread_cancel, pthread_setcanceltype
 */
int pthread_setcancelstate(int state, int *oldstate)
{
    _pthread_data_t *ptd;

    if (rt_thread_self() == NULL) return EINVAL;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    if ((state == PTHREAD_CANCEL_ENABLE) || (state == PTHREAD_CANCEL_DISABLE))
    {
        if (oldstate)
            *oldstate = ptd->cancelstate;
        ptd->cancelstate = state;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_setcancelstate);

/**
 * @brief Sets the cancellation type of the calling thread.
 *
 * The `pthread_setcanceltype` function allows a thread to specify when it should respond to
 * a cancellation request. The cancellation type can be set to deferred or asynchronous.
 *
 * @param[in] type
 *   The new cancellation type for the calling thread. Possible values:
 *   - `PTHREAD_CANCEL_DEFERRED`: Cancellation occurs at cancellation points (default behavior).
 *   - `PTHREAD_CANCEL_ASYNCHRONOUS`: Cancellation occurs immediately when a request is received.
 *
 * @param[out] oldtype
 *   A pointer to an integer where the previous cancellation type will be stored. Can be `NULL`
 *   if the previous type is not required.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the `type` is not a valid cancellation type.
 *
 * @note
 *   - The cancellation type determines when a thread processes a cancellation request:
 *     - **Deferred**: The thread responds to cancellation only at well-defined cancellation points.
 *     - **Asynchronous**: The thread can be canceled immediately, which may lead to resource inconsistencies.
 *   - By default, threads use `PTHREAD_CANCEL_DEFERRED`.
 *   - Asynchronous cancellation should be used cautiously as it can interrupt a thread at any point.
 *
 * @see pthread_cancel, pthread_setcancelstate, pthread_testcancel
 */
int pthread_setcanceltype(int type, int *oldtype)
{
    _pthread_data_t *ptd;

    if (rt_thread_self() == NULL) return EINVAL;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    if ((type != PTHREAD_CANCEL_DEFERRED) && (type != PTHREAD_CANCEL_ASYNCHRONOUS))
        return EINVAL;

    if (oldtype)
        *oldtype = ptd->canceltype;
    ptd->canceltype = type;

    return 0;
}
RTM_EXPORT(pthread_setcanceltype);

/**
 * @brief Explicitly checks for pending cancellation requests in the calling thread.
 *
 * The `pthread_testcancel` function allows a thread to determine if it has a pending
 * cancellation request. If a cancellation request is pending and the thread's cancelability
 * state is set to `PTHREAD_CANCEL_ENABLE`, the thread will terminate immediately.
 *
 * @note
 *   - This function is a cancellation point, meaning it checks for cancellation and responds if applicable.
 *   - If the thread's cancelability state is `PTHREAD_CANCEL_DISABLE`, the function has no effect.
 *   - The thread will invoke any cleanup handlers registered with `pthread_cleanup_push` before termination.
 *
 * @return
 *   This function does not return if a cancellation is performed. Otherwise, it returns normally.
 *
 * @see pthread_setcancelstate, pthread_setcanceltype, pthread_cancel
 */
void pthread_testcancel(void)
{
    int cancel = 0;
    _pthread_data_t *ptd;

    if (rt_thread_self() == NULL) return;

    /* get pthread data from pthread_data of thread */
    ptd = (_pthread_data_t *)rt_thread_self()->pthread_data;
    RT_ASSERT(ptd != RT_NULL);

    if (ptd->cancelstate == PTHREAD_CANCEL_ENABLE)
        cancel = ptd->canceled;
    if (cancel)
        pthread_exit((void *)PTHREAD_CANCELED);
}
RTM_EXPORT(pthread_testcancel);

/**
 * @brief Sends a cancellation request to a specified thread.
 *
 * The `pthread_cancel` function requests the cancellation of the thread identified by `thread`.
 * The actual response to the request depends on the target thread's cancelability state and type.
 *
 * @param[in] thread
 *   The identifier of the thread to be canceled.
 *
 * @return
 *   - `0` on success.
 *   - `EINVAL` if the specified thread does not exist.
 *
 * @note
 *   - Cancellation is an asynchronous mechanism. The thread may not terminate immediately or at all
 *     if its cancelability state is set to `PTHREAD_CANCEL_DISABLE`.
 *   - If the thread is cancelable and terminates, it invokes cleanup handlers registered with
 *     `pthread_cleanup_push` before termination.
 *   - The thread's cancellation type determines when it processes the cancellation request:
 *     - `PTHREAD_CANCEL_DEFERRED` (default): At specific cancellation points.
 *     - `PTHREAD_CANCEL_ASYNCHRONOUS`: Immediately upon receipt of the request.
 *
 * @see pthread_setcancelstate, pthread_setcanceltype, pthread_testcancel
 */
int pthread_cancel(pthread_t thread)
{
    _pthread_data_t *ptd;
    _pthread_cleanup_t *cleanup;
    rt_thread_t tid;

    /* get posix thread data */
    ptd = _pthread_get_data(thread);
    if (ptd == RT_NULL)
    {
        return EINVAL;
    }
    tid = ptd->tid;

    /* cancel self */
    if (ptd->tid == rt_thread_self())
        return 0;

    /* set canceled */
    if (ptd->cancelstate == PTHREAD_CANCEL_ENABLE)
    {
        ptd->canceled = 1;
        if (ptd->canceltype == PTHREAD_CANCEL_ASYNCHRONOUS)
        {
            /*
             * When use pthread_cancel to exit.
             * invoke pushed cleanup
             */
            while (ptd->cleanup != RT_NULL)
            {
                cleanup = ptd->cleanup;
                ptd->cleanup = cleanup->next;

                cleanup->cleanup_func(cleanup->parameter);
                /* release this cleanup function */
                rt_free(cleanup);
            }

            /* According to "detachstate" to whether or not to recycle resource immediately */
            if (ptd->attr.detachstate == PTHREAD_CREATE_JOINABLE)
            {
                /* set value */
                rt_sem_release(ptd->joinable_sem);
            }
            else
            {
                /* release pthread resource */
                _pthread_data_destroy(ptd);
            }

            /*
             * second: detach thread.
             * this thread will be removed from scheduler list
             * and because there is a cleanup function in the
             * thread (pthread_cleanup), it will move to defunct
             * thread list and wait for handling in idle thread.
             */
            rt_thread_detach(tid);
        }
    }

    return 0;
}
RTM_EXPORT(pthread_cancel);

