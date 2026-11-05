/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Creates a semaphore.
 *
 * This system call creates a new semaphore with the specified `name` and initializes
 * its value. The semaphore is used for synchronizing access to shared resources in
 * concurrent programming. The semaphore's behavior is defined by the value (`value`)
 * and any flags (`flag`) that specify additional properties or settings.
 *
 * @param name The name of the semaphore. This is a string used to identify the semaphore
 *             in the system. The name must be unique if the system requires it for reference.
 * @param value The initial value of the semaphore. The value typically represents the
 *              number of available resources or tokens. The semaphore will be initialized
 *              with this value.
 * @param flag The flag that specifies the attributes or properties of the semaphore.
 *             Flags can be used to define various characteristics of the semaphore,
 *             such as whether it is binary or counting, whether it is shared, etc.
 *
 * @return On success, returns a handle or reference to the created semaphore. On failure,
 *         returns `NULL`.
 *
 * @note Semaphores are commonly used in multithreading and multiprocessing environments
 *       to synchronize access to shared resources and ensure proper order of execution.
 *       The behavior of the semaphore depends on its type and the system's implementation.
 *
 * @warning Ensure that the `name` is unique and appropriate for your system's naming
 *          conventions. Invalid values for `value` or `flag` may lead to errors in semaphore
 *          creation.
 *
 * @see sem_wait(), sem_post(), sem_destroy()
 */
rt_sem_t sys_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    int len = 0;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    rt_sem_t sem = rt_sem_create(kname, value, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)sem) != 0)
    {
        rt_sem_delete(sem);
        sem = NULL;
    }

    kmem_put(kname);

    return sem;
}

/**
 * @brief Deletes a semaphore and releases associated resources.
 *
 * This system call deletes an existing semaphore identified by the given handle `sem`.
 * It releases any resources associated with the semaphore and ensures that it is no longer
 * available for further synchronization operations. After deletion, the semaphore handle
 * is invalid and should not be used.
 *
 * @param sem The semaphore handle to be deleted. This handle is obtained when the semaphore
 *            is created using `sys_sem_create()` or similar functions.
 *
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @note Deleting a semaphore is a critical operation that should be performed only when
 *       the semaphore is no longer needed and no tasks are currently waiting or posting
 *       to it. Deleting a semaphore while it is still in use may lead to undefined behavior.
 *
 * @warning Ensure that no tasks are using or blocking on the semaphore before deleting it.
 *          Using a deleted semaphore will result in undefined behavior and potential system errors.
 *
 * @see sys_sem_create(), sem_wait(), sem_post()
 */
sysret_t sys_sem_delete(rt_sem_t sem)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)sem);
}

/**
 * @brief Attempts to take (acquire) a semaphore.
 *
 * This system call attempts to acquire a semaphore, blocking the calling task until the
 * semaphore becomes available or the specified timeout expires. If the semaphore is already
 * available, the calling task will immediately take it and proceed. If the semaphore is not
 * available, the task will block until the semaphore becomes available or the timeout period
 * has elapsed. The `time` parameter specifies the maximum amount of time the task will block
 * waiting for the semaphore.
 *
 * @param sem The semaphore handle to be taken. This handle is obtained when the semaphore
 *            is created using `sys_sem_create()` or similar functions.
 * @param time The maximum time to wait for the semaphore to become available. If the semaphore
 *             is not acquired within this time period, the function will return with an error.
 *             A value of `0` means no waiting (non-blocking), while a negative value may indicate
 *             an infinite wait, depending on the system's implementation.
 *
 * @return On success, returns `0` if the semaphore was successfully taken. On failure, returns error code.
 *
 * @warning Ensure that the semaphore handle is valid and has been properly created before
 *          calling this function. If the semaphore is deleted or invalid, the behavior of
 *          this function is undefined.
 *
 * @see sys_sem_create(), sys_sem_delete(), sem_post()
 */
sysret_t sys_sem_take(rt_sem_t sem, rt_int32_t time)
{
    return rt_sem_take_interruptible(sem, time);
}

/**
 * @brief Releases a semaphore and wakes up any waiting tasks.
 *
 * This system call releases a semaphore, incrementing its value and allowing any tasks
 * that are blocked (waiting) on the semaphore to proceed. If there are tasks waiting for
 * the semaphore, one of them will be unblocked and allowed to take the semaphore.
 * The release operation does not block the calling task, and it will return immediately.
 *
 * @param sem The semaphore handle to be released. This handle is obtained when the semaphore
 *            is created using `sys_sem_create()` or similar functions.
 *
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @warning Ensure that the semaphore handle is valid before calling this function. If the semaphore
 *          is deleted or invalid, the behavior of this function is undefined.
 *
 * @see sys_sem_create(), sys_sem_delete(), sys_sem_take()
 */
sysret_t sys_sem_release(rt_sem_t sem)
{
    return rt_sem_release(sem);
}

/**
 * @brief Creates a mutex.
 *
 * This system call creates a new mutex with the specified `name` and initializes it
 * with the given `flag`. The mutex is used for synchronizing access to shared resources
 * between tasks. Mutexes are typically used to ensure that only one task can access
 * a critical section of code or a resource at a time. The `flag` parameter allows
 * for setting certain properties of the mutex, such as whether it is recursive or whether
 * it can be used by multiple tasks.
 *
 * @param name The name of the mutex. This is a string used to uniquely identify the mutex
 *             within the system. The name must be unique if the system requires it.
 * @param flag The flag that specifies the attributes or properties of the mutex. Flags can
 *             define various mutex behaviors, such as whether the mutex is recursive (allows
 *             the same task to lock it multiple times) or whether it can be shared across
 *             different parts of the system.
 *
 * @return On success, returns a handle to the created mutex. On failure, returns `-RT_NULL`.
 *
 * @note Mutexes are typically used to prevent race conditions and ensure mutual exclusion
 *       when multiple tasks or threads are accessing shared resources.
 *
 * @warning Ensure that the `name` is unique and appropriate according to the system's
 *          naming conventions. Invalid values for `flag` or `name` may result in errors.
 *
 * @see sys_mutex_delete(), sys_mutex_lock(), sys_mutex_unlock()
 */
rt_mutex_t sys_mutex_create(const char *name, rt_uint8_t flag)
{
    int len = 0;
    char *kname = RT_NULL;
    rt_mutex_t mutex = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    mutex = rt_mutex_create(kname, flag);
    if (mutex == RT_NULL)
    {
        return RT_NULL;
    }

    if (lwp_user_object_add(lwp_self(), (rt_object_t)mutex) != 0)
    {
        rt_mutex_delete(mutex);
        mutex = RT_NULL;
    }

    kmem_put(kname);

    return mutex;
}

/**
 * @brief Deletes a mutex and releases associated resources.
 *
 * This system call deletes an existing mutex identified by the given handle `mutex`.
 * It releases any resources associated with the mutex and ensures that it is no longer
 * available for further synchronization operations. After deletion, the mutex handle
 * becomes invalid and should not be used. This operation also ensures that no tasks
 * can block or attempt to lock the mutex after it has been deleted.
 *
 * @param mutex The mutex handle to be deleted. This handle is obtained when the mutex
 *              is created using `sys_mutex_create()` or similar functions.
 *
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @warning Ensure that the mutex handle is valid before calling this function. Deleting
 *          an already deleted or invalid mutex will result in undefined behavior.
 *
 * @see sys_mutex_create(), sys_mutex_lock(), sys_mutex_unlock()
 */
sysret_t sys_mutex_delete(rt_mutex_t mutex)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mutex);
}

/**
 * @brief Attempts to acquire (lock) a mutex.
 *
 * This system call attempts to acquire a mutex, blocking the calling task until the
 * mutex becomes available or the specified timeout expires. If the mutex is available,
 * the calling task will immediately acquire it and proceed. If the mutex is already locked
 * by another task, the calling task will block until the mutex is released or the timeout
 * period elapses. The `time` parameter specifies the maximum amount of time the task will
 * block while waiting for the mutex.
 *
 * @param mutex The mutex handle to be locked. This handle is obtained when the mutex is
 *              created using `sys_mutex_create()` or similar functions.
 * @param time The maximum time to wait for the mutex to become available. If the mutex
 *             is not acquired within this time period, the function will return an error.
 *             A value of `0` means no waiting (non-blocking), while a negative value may
 *             indicate an infinite wait.
 *
 * @return On success, returns `0` if the mutex was successfully acquired. On failure, returns error code.
 *
 * @warning Ensure that the mutex handle is valid and has been properly created before
 *          calling this function. If the mutex is deleted or invalid, the behavior of
 *          this function is undefined.
 *
 * @see sys_mutex_create(), sys_mutex_delete(), sys_mutex_unlock()
 */
sysret_t sys_mutex_take(rt_mutex_t mutex, rt_int32_t time)
{
    return rt_mutex_take_interruptible(mutex, time);
}

/**
 * @brief Releases (unlocks) a mutex.
 *
 * This system call releases a mutex that was previously acquired (locked) by the calling task.
 * If any other task is waiting for the mutex, one of them will be unblocked and allowed to
 * acquire the mutex. The release operation does not block the calling task, and it will return
 * immediately after unlocking the mutex.
 *
 * @param mutex The mutex handle to be released. This handle is obtained when the mutex is
 *              created using `sys_mutex_create()` or similar functions.
 *
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @warning Ensure that the mutex handle is valid before calling this function. Attempting
 *          to release a mutex that has not been locked or is already released can result
 *          in undefined behavior.
 *
 * @see sys_mutex_create(), sys_mutex_delete(), sys_mutex_take()
 */
sysret_t sys_mutex_release(rt_mutex_t mutex)
{
    return rt_mutex_release(mutex);
}

/**
 * @brief Creates an event object for inter-thread or inter-process communication.
 *
 * @param name A string representing the name of the event. If `NULL`, the event will
 *             be created without a name. Named events can be identified and accessed
 *             globally if supported by the system.
 * @param flag Specifies the behavior of the event. Possible values include:
 *             - `RT_IPC_FLAG_FIFO`: Events are handled in a first-in, first-out order.
 *             - `RT_IPC_FLAG_PRIO`: Events are handled in priority order.
 *
 * @return On success, returns a handle (`rt_event_t`) to the created event. On failure,
 *         returns `-RT_NULL` to indicate that the event could not be created.
 *
 * @note
 * - The event object must be explicitly deleted using `sys_event_delete` when it is
 *   no longer needed to free system resources.
 *
 * @warning
 * - Ensure that sufficient system resources (e.g., memory) are available to create
 *   the event. If resources are insufficient, the function will fail.
 * - Named events can potentially lead to naming conflicts if multiple events with
 *   the same name are created. Use unique names to avoid such issues.
 *
 * @see sys_event_delete(), sys_event_send(), sys_event_recv()
 */
rt_event_t sys_event_create(const char *name, rt_uint8_t flag)
{
    int len = 0;
    rt_event_t event = RT_NULL;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    event = rt_event_create(kname, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)event) != 0)
    {
        rt_event_delete(event);
        event = NULL;
    }

    kmem_put(kname);

    return event;
}

/**
 * @brief Deletes a system event object.
 *
 * This system call removes the specified system event object, releasing
 * any resources associated with it. After deletion, the event object
 * should not be used.
 *
 * @param[in] event The handle to the event object to be deleted.
 *                  Must be a valid `rt_event_t` object.
 *
 * @return sysret_t Returns a status code indicating the result of the
 *                   operation:
 *                   - `0` if the operation was successful.
 *                   - An appropriate error code otherwise.
 *
 * @note Ensure that the event is no longer being accessed by any
 *       threads or tasks before calling this function.
 *
 * @warning Deleting an event that is in use or invalid may lead to
 *          undefined behavior.
 * @see sys_event_create(), sys_event_send(), sys_event_recv()
 */
sysret_t sys_event_delete(rt_event_t event)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)event);
}

/**
 * @brief Sends an event to the specified event object.
 *
 * This system call sends an event to the specified event object, setting
 * the specified bits in the event object's set. The event can be used
 * to signal other threads or tasks that a particular condition has
 * occurred.
 *
 * @param[in] event The handle to the event object to which the event
 *                  will be sent. Must be a valid `rt_event_t` object.
 * @param[in] set The bits to set in the event object's set. The bits
 *                are specified as a bitmask, where each bit represents
 *                a different event condition.
 *
 * @return sysret_t Returns a status code indicating the result of the
 *                   operation:
 *                   - `0` if the operation was successful.
 *                   - An appropriate error code otherwise.
 *
 * @note The event object must be created before sending events to it.
 *
 * @warning Ensure that the event object is valid and has been created
 *          before calling this function.
 * @see sys_event_create(), sys_event_recv()
 */
sysret_t sys_event_send(rt_event_t event, rt_uint32_t set)
{
    return rt_event_send(event, set);
}

/**
 * @brief Receives an event from the specified event object.
 *
 * This system call waits for an event to be received from the specified
 * event object. The function blocks until the specified event bits are
 * set in the event object's set or the specified timeout period has
 * elapsed. If the event is received, the function returns the set of
 * bits that were set in the event object.
 *
 * @param[in] event The handle to the event object from which the event
 *                  will be received. Must be a valid `rt_event_t` object.
 * @param[in] set The bits to wait for in the event object's set. The
 *                bits are specified as a bitmask, where each bit
 *                represents a different event condition.
 * @param[in] opt The options for receiving the event. Possible values
 *                include:
 *                - `EV_EVENT_ANY`: Wait for any of the specified bits
 *                  to be set.
 *                - `EV_EVENT_ALL`: Wait for all of the specified bits
 *                  to be set.
 * @param[in] timeout The maximum time to wait for the event to be
 *                    received, in milliseconds. A value of `0` means
 *                    no waiting (non-blocking), while a negative value
 *                    may indicate an infinite wait.
 * @param[out] recved A pointer to a variable that will receive the set
 *                    of bits that were set in the event object. If the
 *                    event is received, this variable will be updated
 *                    with the set of bits.
 *
 * @return sysret_t Returns a status code indicating the result of the
 *                   operation:
 *                   - `0` if the operation was successful.
 *                   - An appropriate error code otherwise.
 *
 * @note The event object must be created before receiving events from it.
 *
 * @warning Ensure that the event object is valid and has been created
 *          before calling this function.
 * @see sys_event_create(), sys_event_send()
 */
sysret_t sys_event_recv(rt_event_t event,
                        rt_uint32_t set,
                        rt_uint8_t opt,
                        rt_int32_t timeout,
                        rt_uint32_t *recved)
{
    int ret = 0;
    rt_uint32_t krecved;

    if ((recved != NULL) && !lwp_user_accessable((void *)recved, sizeof(rt_uint32_t *)))
    {
        return -EFAULT;
    }

    ret = rt_event_recv(event, set, opt, timeout, &krecved);
    if ((ret == RT_EOK) && recved)
    {
        lwp_put_to_user((void *)recved, &krecved, sizeof(rt_uint32_t *));
    }

    return ret;
}

/**
 * @brief Creates a mailbox for inter-thread or inter-process communication.
 *
 * This system call creates a mailbox object with the specified name and size.
 * The mailbox is used to exchange messages between threads or tasks in a
 * synchronized manner. The mailbox can be used to send and receive messages
 * of a specified size.
 *
 * @param[in] name A string representing the name of the mailbox. If `NULL`,
 *                 the mailbox will be created without a name. Named mailboxes
 *                 can be identified and accessed globally if supported by the system.
 * @param[in] size The size of the mailbox, which determines the maximum number
 *                 of messages that can be stored in the mailbox at any given time.
 * @param[in] flag The behavior of the mailbox. Possible values include:
 *                 - `RT_IPC_FLAG_FIFO`: Messages are handled in a first-in, first-out order.
 *                 - `RT_IPC_FLAG_PRIO`: Messages are handled in priority order.
 *
 * @return rt_mailbox_t Returns a handle to the created mailbox object.
 *                      On failure, returns `-RT_NULL`.
 *
 * @note
 * - The mailbox object must be explicitly deleted using `sys_mb_delete` when it is
 *   no longer needed to free system resources.
 *
 * @warning
 * - Ensure that sufficient system resources (e.g., memory) are available to create
 *   the mailbox. If resources are insufficient, the function will fail.
 * - Named mailboxes can potentially lead to naming conflicts if multiple mailboxes
 *   with the same name are created. Use unique names to avoid such issues.
 *
 * @see sys_mb_delete(), sys_mb_send(), sys_mb_recv()
 */
rt_mailbox_t sys_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    int len = 0;
    rt_mailbox_t mb = RT_NULL;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    mb = rt_mb_create(kname, size, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)mb) != 0)
    {
        rt_mb_delete(mb);
        mb = NULL;
    }

    kmem_put(kname);

    return mb;
}

/**
 * @brief Deletes a mailbox object.
 *
 * This system call deletes the specified mailbox object, releasing any resources
 * associated with it. After deletion, the mailbox object should not be used.
 *
 * @param[in] mb The handle to the mailbox object to be deleted.
 *               Must be a valid `rt_mailbox_t` object.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0` if the operation was successful.
 *                   - An appropriate error code otherwise.
 *
 * @note Ensure that the mailbox is no longer being accessed by any threads or tasks
 *       before calling this function.
 *
 * @warning Deleting a mailbox that is in use or invalid may lead to undefined behavior.
 *
 * @see sys_mb_create(), sys_mb_send(), sys_mb_recv()
 */
sysret_t sys_mb_delete(rt_mailbox_t mb)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mb);
}

/**
 * @brief Sends a message to a mailbox object.
 *
 * This system call posts a message (a single value) to the specified mailbox.
 * If the mailbox is full, the function will return an error code immediately without waiting time.
 *
 * @param[in] mb    The handle to the mailbox object where the message
 *                  will be sent. Must be a valid `rt_mailbox_t` object.
 * @param[in] value The value to be sent to the mailbox. Typically, this
 *                  is a pointer or an integral value that represents
 *                  the message content.
 *
 * @return sysret_t Returns a status code indicating the result of the
 *                   operation:
 *                   - `0` if the message was successfully sent.
 *                   - `-RT_EFULL` if the mailbox is full.
 *                   - An appropriate error code for other failures.
 *
 * @note Ensure the mailbox has been properly initialized before calling
 *       this function. Sending messages to an uninitialized or invalid
 *       mailbox may result in undefined behavior.
 *
 * @warning If the mailbox is full and the function blocks, ensure
 *          proper handling to avoid potential deadlocks.
 *
 * @see sys_mb_create(), sys_mb_recv(), sys_mb_send_wait()
 */
sysret_t sys_mb_send(rt_mailbox_t mb, rt_ubase_t value)
{
    return rt_mb_send(mb, value);
}

/**
 * @brief Sends a message to a mailbox object with a timeout.
 *
 * This system call attempts to post a message (a single value) to the specified mailbox.
 * If the mailbox is full, the function will wait for a specified timeout period
 * for space to become available. If the timeout expires before the message is sent,
 * the function returns an error.
 *
 * @param[in] mb       The handle to the mailbox object where the message
 *                     will be sent. Must be a valid `rt_mailbox_t` object.
 * @param[in] value    The value to be sent to the mailbox. Typically, this
 *                     is a pointer or an integral value representing the
 *                     message content.
 * @param[in] timeout  The maximum time to wait for space to become available
 *                     in the mailbox, in milliseconds.
 *                     - a negative value can be used to wait indefinitely.
 *                     - `0` can be used for non-blocking behavior.
 *
 * @return sysret_t Returns a status code indicating the result of the
 *                   operation:
 *                   - `0` if the message was successfully sent.
 *                   - `-RT_ETIMEOUT` if the operation timed out.
 *                   - `-RT_EFULL` if the mailbox is full and `timeout` is `0`.
 *                   - An appropriate error code for other failures.
 *
 * @note Ensure the mailbox has been properly initialized before calling this function.
 *       Passing an uninitialized or invalid mailbox handle may result in undefined behavior.
 *
 * @warning Using a negative value without appropriate logic may lead to indefinite blocking,
 *          potentially causing deadlocks.
 * @see sys_mb_send()
 */
sysret_t sys_mb_send_wait(rt_mailbox_t mb,
                          rt_ubase_t value,
                          rt_int32_t timeout)
{
    return rt_mb_send_wait(mb, value, timeout);
}

/**
 * @brief Receives a message from a mailbox with a timeout.
 *
 * This system call attempts to receive a message from the specified mailbox.
 * If the mailbox is empty, the function will wait for a specified timeout
 * period for a message to arrive. If no message is received within the timeout,
 * an error is returned.
 *
 * @param[in]  mb       The handle to the mailbox object from which the message
 *                      is to be received. Must be a valid `rt_mailbox_t` object.
 * @param[out] value    Pointer to a variable where the received message will
 *                      be stored. Must not be NULL.
 * @param[in]  timeout  The maximum time to wait for a message, in milliseconds.
 *                      - a negative value: Wait indefinitely until a message is available.
 *                      - `0`: Non-blocking mode. If no message is available, return immediately.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0`: The message was successfully received.
 *                   - `-RT_ETIMEOUT`: The operation timed out before a message was received.
 *                   - Other error codes may indicate failures.
 *
 * @note Ensure the mailbox is properly initialized and the `value` pointer
 *       is valid before calling this function. Passing an invalid mailbox
 *       or NULL `value` pointer may lead to undefined behavior.
 *
 * @warning Using a negative value without proper safeguards may cause
 *          indefinite blocking, potentially resulting in deadlocks.
 */
sysret_t sys_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    int ret = 0;
    rt_ubase_t *kvalue;

    if (!lwp_user_accessable((void *)value, sizeof(rt_ubase_t *)))
    {
        return -EFAULT;
    }

    kvalue = kmem_get(sizeof(rt_ubase_t *));
    if (kvalue == RT_NULL)
    {
        return -ENOMEM;
    }

    ret = rt_mb_recv(mb, (rt_ubase_t *)kvalue, timeout);
    if (ret == RT_EOK)
    {
        lwp_put_to_user(value, kvalue, sizeof(rt_ubase_t *));
    }

    kmem_put(kvalue);

    return ret;
}

rt_weak int syslog_ctrl(int type, char *buf, int len)
{
    return -EINVAL;
}

/**
 * @brief Sends a log message to the system log.
 *
 * This system call sends a message to the system log for recording or debugging purposes.
 *
 * @param[in] type  The type of the log message, typically representing the severity
 *                  or category (e.g., debug, info, warning, error). This should be
 *                  a valid predefined log type.
 * @param[in] buf   A pointer to a buffer containing the log message. Must be a
 *                  null-terminated string and a valid pointer.
 * @param[in] len   The length of the log message to be sent, excluding the null
 *                  terminator. If the length exceeds the system log's limit,
 *                  the message may be truncated.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0`: The log message was successfully recorded.
 *                   - Other error codes may indicate additional failures.
 *
 * @note Ensure the log type is a valid predefined value supported by the system.
 *       The buffer must remain valid and accessible during the execution of this function.
 *
 * @warning Sending excessively large or frequent log messages may impact system performance.
 */
sysret_t sys_syslog(int type, char *buf, int len)
{
    char *tmp;
    int ret = -1;

    if (!lwp_user_accessable((void *)buf, len))
    {
        return -EFAULT;
    }

    tmp = (char *)rt_malloc(len);
    if (!tmp)
    {
        return -ENOMEM;
    }

    ret = syslog_ctrl(type, tmp, len);
    lwp_put_to_user(buf, tmp, len);
    rt_free(tmp);

    return ret;
}

/**
 * @brief Creates a message queue.
 *
 * This system call creates a new message queue with a specified name, message size,
 * maximum number of messages, and associated flags. The message queue allows
 * messages of a given size to be sent and received between tasks or threads.
 *
 * @param[in]  name      The name of the message queue. It should be a unique
 *                       identifier and a null-terminated string.
 * @param[in]  msg_size  The size of each message in the queue. This defines
 *                       the maximum size for individual messages that can
 *                       be sent or received.
 * @param[in]  max_msgs  The maximum number of messages the queue can hold.
 *                       If the queue is full, further send operations may
 *                       block or return an error depending on the flags.
 * @param[in]  flag      Flags that control the behavior of the message queue.
 *                       This can specify whether the queue is blocking,
 *                       non-blocking, or has other specific attributes.
 *
 * @return rt_mq_t  Returns the handle to the created message queue, or `NULL`
 *                  if the creation failed (e.g., due to invalid parameters
 *                  or insufficient resources).
 *
 * @note Ensure that the message queue name is unique. The size of the messages
 *       and the number of messages should be chosen based on the application
 *       requirements.
 *
 * @warning Creating too many message queues or setting an overly large
 *          `max_msgs` may lead to resource exhaustion.
 */
rt_mq_t sys_mq_create(const char *name,
                      rt_size_t msg_size,
                      rt_size_t max_msgs,
                      rt_uint8_t flag)
{
    rt_mq_t mq = RT_NULL;

    int len = 0;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    mq = rt_mq_create(kname, msg_size, max_msgs, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)mq) != 0)
    {
        rt_mq_delete(mq);
        mq = NULL;
    }

    kmem_put(kname);

    return mq;
}

/**
 * @brief Deletes a message queue.
 *
 * This system call deletes the specified message queue and releases any resources
 * associated with it. After calling this function, the message queue handle
 * becomes invalid and should not be used.
 *
 * @param[in] mq  The handle to the message queue to be deleted.
 *               Must be a valid `rt_mq_t` object.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0`: The message queue was successfully deleted.
 *                   - An appropriate error code for other failures.
 *
 * @note Ensure that no tasks or threads are using the message queue before
 *       deleting it to avoid undefined behavior or data loss.
 *
 * @warning Deleting an active message queue that is being used by tasks or
 *          threads may lead to resource leaks or corruption. Ensure proper
 *          synchronization before deletion.
 */
sysret_t sys_mq_delete(rt_mq_t mq)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mq);
}

/**
 * @brief Sends a message to a message queue.
 *
 * This system call sends a message to the specified message queue. The message
 * is copied into the queue's buffer. If the queue is full, the behavior will
 * depend on the flags set during queue creation (e.g., whether it is blocking
 * or non-blocking).
 *
 * @param[in] mq     The handle to the message queue where the message will be sent.
 *                   Must be a valid `rt_mq_t` object.
 * @param[in] buffer A pointer to the message data to be sent. This must not be NULL.
 * @param[in] size   The size of the message to be sent, in bytes. This should be
 *                   less than or equal to the maximum message size defined when
 *                   the queue was created.
 *
 * @return sysret_t  Returns a status code indicating the result of the operation:
 *                    - `0`: The message was successfully sent to the queue.
 *                    - An appropriate error code for other failures.
 *
 * @note Ensure that the message size does not exceed the maximum allowed message
 *       size when the queue was created. Passing an invalid queue handle or buffer
 *       may result in undefined behavior.
 *
 * @warning Sending messages to a full queue in blocking mode may cause the calling
 *          task or thread to block indefinitely if not properly handled.
 */
sysret_t sys_mq_send(rt_mq_t mq, void *buffer, rt_size_t size)
{
    int ret = 0;
    void *kbuffer = RT_NULL;

    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }

    kbuffer = kmem_get(size);
    if (kbuffer == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kbuffer, buffer, size) != size)
    {
        kmem_put(kbuffer);
        return -EINVAL;
    }

    ret = rt_mq_send(mq, kbuffer, size);

    kmem_put(kbuffer);

    return ret;
}

/**
 * @brief Sends an urgent message to a message queue.
 *
 * This system call sends a message to the specified message queue with higher priority,
 * meaning it will be placed at the front of the queue, bypassing normal message
 * order. The message is copied into the queue's buffer. If the queue is full,
 * the behavior will depend on the flags set during queue creation (e.g., whether
 * it is blocking or non-blocking).
 *
 * @param[in] mq     The handle to the message queue where the message will be sent.
 *                   Must be a valid `rt_mq_t` object.
 * @param[in] buffer A pointer to the message data to be sent. This must not be NULL.
 * @param[in] size   The size of the message to be sent, in bytes. This should be
 *                   less than or equal to the maximum message size defined when
 *                   the queue was created.
 *
 * @return sysret_t  Returns a status code indicating the result of the operation:
 *                    - `0`: The urgent message was successfully sent to the queue.
 *                    - `-RT_EFULL`: The queue is full and the message could not be sent.
 *                    - An appropriate error code for other failures.
 *
 * @note Ensure that the message size does not exceed the maximum allowed message
 *       size when the queue was created. The urgent message will be processed before
 *       other normal messages in the queue.
 *
 * @warning Sending urgent messages to a full queue in blocking mode may cause the
 *          calling task or thread to block indefinitely if not properly handled.
 */
sysret_t sys_mq_urgent(rt_mq_t mq, void *buffer, rt_size_t size)
{
    int ret = 0;
    void *kbuffer = RT_NULL;

    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }

    kbuffer = kmem_get(size);
    if (kbuffer == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kbuffer, buffer, size) != size)
    {
        kmem_put(kbuffer);
        return -EINVAL;
    }

    ret = rt_mq_urgent(mq, kbuffer, size);

    kmem_put(kbuffer);

    return ret;
}

/**
 * @brief Receives a message from a message queue.
 *
 * This system call attempts to receive a message from the specified message queue.
 * The message is copied into the provided buffer. If no message is available
 * in the queue, the function will block for a specified timeout period before
 * returning. If the timeout expires without receiving a message, an error is returned.
 *
 * @param[in]  mq       The handle to the message queue from which the message
 *                      will be received. Must be a valid `rt_mq_t` object.
 * @param[out] buffer   A pointer to the buffer where the received message will
 *                      be stored. Must not be NULL and large enough to hold the
 *                      message.
 * @param[in]  size     The size of the buffer, in bytes. This should be at least
 *                      the size of a message in the queue.
 * @param[in]  timeout  The maximum time to wait for a message, in milliseconds.
 *                      - a negative value: Wait indefinitely until a message is available.
 *                      - `0`: Non-blocking mode. If no message is available, return immediately.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0`: The message was successfully received.
 *                   - `-RT_ETIMEOUT`: The operation timed out before a message was received.
 *                   - Other error codes may indicate additional failures.
 *
 * @note Ensure the buffer is large enough to store the message received from the queue.
 *       If the buffer is too small, the function may fail or behave unexpectedly.
 *
 * @warning Using a negative value without proper safeguards may cause indefinite
 *          blocking, potentially resulting in deadlocks if no message is received.
 */
sysret_t sys_mq_recv(rt_mq_t mq,
                     void *buffer,
                     rt_size_t size,
                     rt_int32_t timeout)
{
    int ret = 0;
    void *kbuffer = RT_NULL;

    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }

    kbuffer = kmem_get(size);
    if (kbuffer == RT_NULL)
    {
        return -ENOMEM;
    }

    ret = rt_mq_recv(mq, kbuffer, size, timeout);
    if (ret > 0)
    {
        lwp_put_to_user((void *)buffer, (void *)kbuffer, ret);
    }

    kmem_put(kbuffer);

    return ret;
}

static void timer_timeout_callback(void *parameter)
{
    rt_sem_t sem = (rt_sem_t)parameter;
    rt_sem_release(sem);
}

/**
 * @brief Creates a timer.
 *
 * This system call creates a timer that can be used to trigger events or
 * actions after a specified timeout or interval. The timer will operate in a
 * real-time manner and can be configured to trigger once or repeatedly. The
 * created timer can be started, stopped, or deleted as required.
 *
 * @param[in]  name   The name of the timer. It should be a unique string identifier.
 *                    The name is used for debugging and logging purposes.
 * @param[in]  data   A pointer to user-defined data that will be passed to the timer's
 *                    callback function when it is triggered. This may be used to carry
 *                    context or other necessary information for the callback.
 * @param[in]  period The timer period in milliseconds. The timer will trigger every
 *                    `period` milliseconds, or after the specified timeout.
 * @param[in]  flag   Flags that control the behavior of the timer. These can specify
 *                    whether the timer is one-shot (triggers once) or periodic
 *                    (triggers repeatedly).
 *
 * @return rt_timer_t Returns the handle to the created timer, or `NULL` if the creation failed.
 *
 * @note The timer callback function must be implemented to handle the event triggered
 *       by the timer. Ensure that the `data` parameter, if used, is properly handled
 *       in the callback.
 *
 * @warning Ensure the timer's period and flags are configured correctly to avoid
 *          undesired behavior, especially if the timer is periodic.
 */
rt_timer_t sys_rt_timer_create(const char *name,
                               void *data,
                               rt_tick_t time,
                               rt_uint8_t flag)
{
    int len = 0;
    char *kname = RT_NULL;
    rt_timer_t timer = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    timer = rt_timer_create(kname, timer_timeout_callback, (void *)data, time, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)timer) != 0)
    {
        rt_timer_delete(timer);
        timer = NULL;
    }

    kmem_put(kname);

    return timer;
}

/**
 * @brief Deletes a timer.
 *
 * This system call deletes the specified timer and releases any resources
 * associated with it. Once the timer is deleted, its handle becomes invalid,
 * and any further operations on the timer should be avoided.
 *
 * @param[in] timer  The handle to the timer to be deleted. Must be a valid `rt_timer_t` object.
 *
 * @return sysret_t Returns a status code indicating the result of the operation:
 *                   - `0`: The timer was successfully deleted.
 *                   - Other error codes may indicate additional failures.
 *
 * @note Ensure that the timer is not active or being used before deleting it to avoid
 *       any unexpected behavior or resource leaks.
 *
 * @warning Deleting an active timer may lead to undefined behavior, especially
 *          if the timer is in the middle of triggering or executing its callback.
 */
sysret_t sys_rt_timer_delete(rt_timer_t timer)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)timer);
}

/**
 * @brief Starts a timer.
 *
 * This system call starts the specified timer, causing it to begin counting down
 * based on its configured period. Once the timer reaches the set period, it triggers the
 * associated callback function. The behavior depends on whether the timer is configured
 * as one-shot or periodic.
 *
 * @param[in] timer  The handle to the timer to be started. Must be a valid `rt_timer_t` object.
 *
 * @return sysret_t  Returns a status code indicating the result of the operation:
 *                    - `0`: The timer was successfully started.
 *                    - Other error codes may indicate additional failures.
 *
 * @note Ensure that the timer has been created and is in a valid state before attempting to start it.
 *
 * @warning Starting a timer that is already running may lead to undefined behavior. Ensure that the
 *          timer is stopped or not in use before starting it.
 */
sysret_t sys_rt_timer_start(rt_timer_t timer)
{
    return rt_timer_start(timer);
}

/**
 * @brief Stops a timer.
 *
 * This system call stops the specified timer, halting its countdown and
 * preventing it from triggering further callbacks. If the timer is periodic,
 * stopping it will prevent further periodic triggers until it is started again.
 *
 * @param[in] timer  The handle to the timer to be stopped. Must be a valid `rt_timer_t` object.
 *
 * @return sysret_t  Returns a status code indicating the result of the operation:
 *                    - `0`: The timer was successfully stopped.
 *                    - Other error codes may indicate additional failures.
 *
 * @note Ensure that the timer is in a valid state before attempting to stop it.
 *       Stopping an inactive or already stopped timer may not have any effect.
 *
 * @warning Stopping a timer that is actively triggering or in use may disrupt its expected
 *          behavior. Ensure proper synchronization or state management when stopping
 *          the timer during active use.
 */
sysret_t sys_rt_timer_stop(rt_timer_t timer)
{
    return rt_timer_stop(timer);
}

/**
 * @brief Controls various properties of a timer.
 *
 * This system call provides control over various aspects of a timer, such as
 * modifying its configuration, querying its status, or changing its behavior.
 * The specific behavior is determined by the command (`cmd`) and any associated arguments (`arg`).
 *
 * @param[in]  timer  The handle to the timer to be controlled. Must be a valid `rt_timer_t` object.
 * @param[in]  cmd    The command to execute. The meaning of this parameter depends on the command value.
 *                    Common commands might include modifying the timer period, changing its callback,
 *                    or querying its current state.
 * @param[in]  arg    A pointer to any additional arguments needed for the command. The type and content
 *                    of this argument depend on the specific command being executed.
 *
 * @return sysret_t  Returns a status code indicating the result of the operation:
 *                    - `0`: The timer control operation was successful.
 *                    - Other error codes may indicate additional failures.
 *
 * @note Ensure that the provided command (`cmd`) is valid for the specific timer implementation.
 *       Incorrect commands or arguments may lead to unexpected behavior or errors.
 *
 * @warning Using invalid or unsupported commands may cause undefined behavior or crashes.
 */
sysret_t sys_rt_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    return rt_timer_control(timer, cmd, arg);
}

/* MUSL compatible */
struct ksigevent
{
    union sigval sigev_value;
    int sigev_signo;
    int sigev_notify;
    int sigev_tid;
};

/* to protect unsafe implementation in current rt-smart toolchain */
RT_STATIC_ASSERT(sigevent_compatible, offsetof(struct ksigevent, sigev_tid) == offsetof(struct sigevent, sigev_notify_function));

/**
 * @brief Creates a per-process timer.
 *
 * This system call creates a new timer associated with the specified clock, and
 * initializes the timer with the provided event notification attributes.
 * Once created, the timer can be started, stopped, or controlled as needed.
 * The timer will trigger when the specified expiration time or interval is reached.
 *
 * @param[in]  clockid   The clock to be used for the timer. Common clock values include:
 *                       - `CLOCK_REALTIME`: System real-time clock.
 *                       - `CLOCK_MONOTONIC`: Monotonic clock that cannot be set and is not affected by system time changes.
 *                       - Other clock IDs can be used depending on the platform and requirements.
 * @param[in]  sevp      A pointer to a `sigevent` structure that specifies how the process
 *                       should be notified when the timer expires. This can include notification
 *                       types such as signal delivery, thread notification, or posting to a queue.
 * @param[out] timerid   A pointer to a `timer_t` variable where the created timer's ID will be stored.
 *                       The timer ID will be used for subsequent timer operations (e.g., starting, stopping).
 *
 * @return sysret_t      Returns a status code indicating the result of the operation:
 *                       - `0`: The timer was successfully created.
 *                       - Other error codes may indicate additional failures.
 *
 * @warning Ensure that the provided `sigevent` structure is properly configured, as invalid or
 *          unsupported notification types may result in unexpected behavior.
 */
sysret_t sys_timer_create(clockid_t clockid, struct sigevent * restrict sevp, timer_t * restrict timerid)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct sigevent sevp_k;
    timer_t timerid_k;
    int utimer;

    if (sevp == NULL)
    {
        sevp_k.sigev_notify = SIGEV_SIGNAL;
        sevp_k.sigev_signo = SIGALRM;
        sevp = &sevp_k;
    }
    else
    {
        /* clear extra bytes if any */
        if (sizeof(struct ksigevent) < sizeof(struct sigevent))
        {
            memset(&sevp_k, 0, sizeof(sevp_k));
        }

        /* musl passes `struct ksigevent` to kernel, we shoule only get size of that bytes */
        if (!lwp_get_from_user(&sevp_k, (void *)sevp, sizeof(struct ksigevent)))
        {
            return -EINVAL;
        }
    }

    ret = _SYS_WRAP(timer_create(clockid, &sevp_k, &timerid_k));

    if (ret != -RT_ERROR)
    {
        utimer = (rt_ubase_t)timerid_k;
        if (!lwp_put_to_user(sevp, (void *)&sevp_k, sizeof(struct ksigevent)) ||
            !lwp_put_to_user(timerid, (void *)&utimer, sizeof(utimer)))
        {
            ret = -EINVAL;
        }
    }
#else
    ret = _SYS_WRAP(timer_create(clockid, sevp, timerid));
#endif
    return ret;
}

/**
 * @brief Deletes a timer.
 *
 * This system call deletes the specified timer and releases any resources associated
 * with it. Once the timer is deleted, it can no longer be used, and any further
 * operations on the timer (such as starting or stopping) will result in an error.
 *
 * @param[in] timerid  The ID of the timer to be deleted. This is the timer handle
 *                     returned by `sys_timer_create`.
 *
 * @return sysret_t    Returns a status code indicating the result of the operation:
 *                     - `0`: The timer was successfully deleted.
 *                     - Other error codes may indicate additional failures.
 *
 * @note After calling this function, the timer ID becomes invalid, and it should
 *       not be used in any further operations.
 *
 * @warning Make sure the timer is not active or in use when attempting to delete it,
 *          as deleting an active timer may cause unexpected behavior or resource leaks.
 */
sysret_t sys_timer_delete(timer_t timerid)
{
    int ret = timer_delete(timerid);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Changes the time or interval of an existing timer.
 *
 * This system call modifies the expiration time or interval of a previously created
 * timer. It can either set a new expiration time for the timer or update the
 * interval for periodic timers. The timer can be started or modified based on
 * the flags provided. The current (old) timer settings can be retrieved if
 * requested.
 *
 * @param[in]  timerid      The ID of the timer to modify. This is the timer handle
 *                          returned by `sys_timer_create`.
 * @param[in]  flags        Flags that control the behavior of the operation. Common
 *                          values include:
 *                          - `TIMER_ABSTIME`: Specifies that `new_value` contains
 *                            an absolute time. Otherwise, it is treated as relative.
 * @param[in]  new_value    A pointer to the `itimerspec` structure specifying
 *                          the new time settings for the timer. The structure includes:
 *                          - `it_value`: The initial expiration time (relative or absolute).
 *                          - `it_interval`: The period for periodic timers.
 * @param[out] old_value    A pointer to an `itimerspec` structure where the previous
 *                          timer settings will be stored. If NULL, the old value is ignored.
 *
 * @return sysret_t         Returns a status code indicating the result of the operation:
 *                          - `0`: The timer time/interval was successfully updated.
 *                          - Other error codes may indicate additional failures.
 *
 * @warning Modifying a timer that is currently active can cause timing-related issues
 *          if not handled correctly. Make sure the timer is in an appropriate state
 *          before making changes.
 */
sysret_t sys_timer_settime(timer_t timerid, int flags,
                           const struct itimerspec * restrict new_value,
                           struct itimerspec * restrict old_value)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct itimerspec new_value_k;
    struct itimerspec old_value_k;

    if (!lwp_get_from_user(&new_value_k, (void *)new_value, sizeof(*new_value)) ||
        (old_value && !lwp_get_from_user(&old_value_k, (void *)old_value, sizeof(*old_value))))
    {
        return -EFAULT;
    }

    ret = timer_settime(timerid, flags, &new_value_k, &old_value_k);
    lwp_put_to_user(old_value, (void *)&old_value_k, sizeof old_value_k);

#else
    ret = timer_settime(timerid, flags, new_value, old_value);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Retrieves the current time and interval of a timer.
 *
 * This system call fetches the current expiration time (`it_value`) and interval (`it_interval`)
 * of a previously created timer. It allows the caller to determine the current state of the timer,
 * whether it is one-shot or periodic, and the remaining time before expiration.
 *
 * @param[in]  timerid      The ID of the timer to query. This is the timer handle
 *                          returned by `sys_timer_create`.
 * @param[out] curr_value   A pointer to an `itimerspec` structure where the current timer values
 *                          will be stored. This structure includes:
 *                          - `it_value`: The remaining time until the timer expires.
 *                          - `it_interval`: The interval between subsequent expirations (for periodic timers).
 *
 * @return sysret_t         Returns a status code indicating the result of the operation:
 *                          - `0`: The current time/interval was successfully retrieved.
 *                          - Other error codes may indicate additional failures.
 *
 * @warning Ensure that the timer ID is valid before calling this function, as invalid timer IDs
 *          will result in errors.
 */
sysret_t sys_timer_gettime(timer_t timerid, struct itimerspec *curr_value)
{
    int ret = 0;
#ifdef ARCH_MM_MMU

    struct itimerspec curr_value_k;
    lwp_get_from_user(&curr_value_k, (void *)curr_value, sizeof curr_value_k);
    ret = timer_gettime(timerid, &curr_value_k);
    lwp_put_to_user(curr_value, (void *)&curr_value_k, sizeof curr_value_k);
#else
    ret = timer_gettime(timerid, curr_value);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Retrieves the overrun count for a periodic timer.
 *
 * This system call retrieves the number of times a periodic timer has "overrun." An overrun occurs
 * when a timer expires before the previous expiration has been acknowledged or handled. For periodic
 * timers, this indicates how many times the timer's expiration has been missed due to delayed processing
 * or handling.
 *
 * @param[in]  timerid      The ID of the timer to query. This is the timer handle
 *                          returned by `sys_timer_create`.
 *
 * @return sysret_t         Returns a status code indicating the result of the operation:
 *                          - `0`: The overrun count was successfully retrieved.
 *                         - Other error codes may indicate additional failures.
 *
 * @warning Ensure that the timer ID is valid before calling this function, as invalid timer IDs
 *          will result in errors.
 */
sysret_t sys_timer_getoverrun(timer_t timerid)
{
    int ret = 0;
    ret = timer_getoverrun(timerid);
    return (ret < 0 ? GET_ERRNO() : ret);
}
