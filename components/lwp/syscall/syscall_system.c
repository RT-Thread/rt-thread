/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Get system information.
 *
 * This function retrieves information about the current system, such as the system name,
 * version, release, architecture, and other details. The information is stored in the
 * `utsname` structure pointed to by the `uts` parameter.
 *
 * @param[out] uts  A pointer to a `utsname` structure where the system information will
 *                  be stored. The structure includes fields such as:
 *                  - `sysname`: Operating system name.
 *                  - `nodename`: Network node hostname.
 *                  - `release`: Operating system release version.
 *                  - `version`: Operating system version.
 *                  - `machine`: Hardware identifier (architecture).
 *
 * @return sysret_t Returns `SYSRET_OK` (0) on success. On failure, returns a negative error code.
 *
 * @note This function provides details about the system environment, which may be useful
 *       for applications needing to adapt to different system configurations.
 *
 * @see sys_gethostname, sys_uname
 */
sysret_t sys_uname(struct utsname *uts)
{
    struct utsname utsbuff = { 0 };
    int ret = 0;
    const char *machine;

    if (!lwp_user_accessable((void *)uts, sizeof(struct utsname)))
    {
        return -EFAULT;
    }
    rt_strncpy(utsbuff.sysname, "RT-Thread", sizeof(utsbuff.sysname));
    utsbuff.nodename[0] = '\0';
    ret = rt_snprintf(utsbuff.release, sizeof(utsbuff.release), "%u.%u.%u",
                      RT_VERSION_MAJOR, RT_VERSION_MINOR, RT_VERSION_PATCH);
    if (ret < 0)
    {
        return -EIO;
    }
    ret = rt_snprintf(utsbuff.version, sizeof(utsbuff.version), "RT-Thread %u.%u.%u %s %s",
                      RT_VERSION_MAJOR, RT_VERSION_MINOR, RT_VERSION_PATCH, __DATE__, __TIME__);
    if (ret < 0)
    {
        return -EIO;
    }

    machine = rt_hw_cpu_arch();
    rt_strncpy(utsbuff.machine, machine, sizeof(utsbuff.machine));

    utsbuff.domainname[0] = '\0';
    lwp_put_to_user(uts, &utsbuff, sizeof utsbuff);
    return 0;
}

#ifndef LWP_USING_RUNTIME
sysret_t lwp_teardown(struct rt_lwp *lwp, void (*cb)(void))
{
    /* if no LWP_USING_RUNTIME configured */
    return -ENOSYS;
}
#endif

/**
 * @brief Reboot the system.
 *
 * This function initiates a system reboot with a specific reboot type and optional arguments.
 * The reboot process is performed by passing `magic` and `magic2` as security keys to validate the
 * reboot request, along with the desired reboot type (`type`) and optional argument (`arg`) that
 * may contain additional parameters depending on the reboot type.
 *
 * @param[in] magic   A magic number for security validation, typically used to verify that the caller
 *                    has sufficient privileges (e.g., root).
 * @param[in] magic2  A second magic number for additional security verification, used in combination
 *                    with `magic` to validate the reboot request.
 * @param[in] type    The type of reboot to perform, such as `RB_AUTOBOOT`, `RB_HALT`, `RB_RESTART`,
 *                    etc. The exact values may depend on the platform.
 * @param[in] arg     An optional argument for the reboot process. This can provide additional data,
 *                    such as a specific shutdown procedure, depending on the type of reboot.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note This operation is typically available to the system administrator (root) and should be used
 *       with caution as it can cause the system to restart or shut down.
 */
sysret_t sys_reboot(int magic, int magic2, int type, void *arg)
{
    sysret_t rc;
    switch (type)
    {
        /* Hardware reset */
    case RB_AUTOBOOT:
        rc = lwp_teardown(lwp_self(), rt_hw_cpu_reset);
        break;

        /* Stop system and switch power off */
    case RB_POWER_OFF:
        rc = lwp_teardown(lwp_self(), rt_hw_cpu_shutdown);
        break;
    default:
        rc = -ENOSYS;
    }

    return rc;
}

/**
 * @brief Read data from a file descriptor at a specific offset.
 *
 * This function reads data from a file descriptor `fd` into the buffer `buf`, starting from the
 * specified byte `offset`. Unlike a regular `read` call, `sys_pread64` allows the file pointer to
 * remain unchanged after the read, as the operation directly accesses the file at the provided
 * offset.
 *
 * @param[in] fd      The file descriptor from which to read. It must be a valid open file descriptor.
 * @param[out] buf    A pointer to the buffer where the read data will be stored.
 * @param[in] size    The number of bytes to read from the file.
 * @param[in] offset  The offset in bytes from the beginning of the file to start reading from.
 *
 * @return ssize_t On success, returns the number of bytes read (which may be less than `size` if
 *                  the end of the file is reached). On error, returns a negative error code.
 *
 * @note This function is particularly useful for random access to files, allowing for efficient
 *       reads from arbitrary positions without affecting the current file pointer.
 */
ssize_t sys_pread64(int fd, void *buf, int size, size_t offset)
#ifdef RT_USING_DFS_V2
{
    ssize_t pread(int fd, void *buf, size_t len, size_t offset);
#ifdef ARCH_MM_MMU
    ssize_t ret = -1;
    void *kmem = RT_NULL;

    if (!size)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)buf, size))
    {
        return -EFAULT;
    }
    kmem = kmem_get(size);
    if (!kmem)
    {
        return -ENOMEM;
    }

    ret = pread(fd, kmem, size, offset);
    if (ret > 0)
    {
        lwp_put_to_user(buf, kmem, ret);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, size))
    {
        return -EFAULT;
    }

    ssize_t ret = pread(fd, kmem, size, offset);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}
#else
{
    ssize_t ret = -ENOSYS;
    return (ret < 0 ? GET_ERRNO() : ret);
}
#endif

/**
 * @brief Write data to a file descriptor at a specific offset.
 *
 * This function writes data from the buffer `buf` to the file descriptor `fd`, starting at the
 * specified byte `offset`. Unlike a regular `write` call, `sys_pwrite64` allows the file pointer to
 * remain unchanged after the write, as the operation directly writes the data to the file at the
 * provided offset.
 *
 * @param[in] fd      The file descriptor to which the data will be written. It must be a valid open
 *                    file descriptor.
 * @param[in] buf     A pointer to the buffer containing the data to be written.
 * @param[in] size    The number of bytes to write to the file.
 * @param[in] offset  The offset in bytes from the beginning of the file to start writing to.
 *
 * @return ssize_t On success, returns the number of bytes written (which may be less than `size` if
 *                  the write operation is partial). On error, returns a negative error code.
 *
 * @note This function is particularly useful for random access to files, allowing for efficient
 *       writes to arbitrary positions without affecting the current file pointer.
 */
ssize_t sys_pwrite64(int fd, void *buf, int size, size_t offset)
#ifdef RT_USING_DFS_V2
{
    ssize_t pwrite(int fd, const void *buf, size_t len, size_t offset);
#ifdef ARCH_MM_MMU
    ssize_t ret = -1;
    void *kmem = RT_NULL;

    if (!size)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)buf, size))
    {
        return -EFAULT;
    }
    kmem = kmem_get(size);
    if (!kmem)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kmem, (void *)buf, size);

    ret = pwrite(fd, kmem, size, offset);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, size))
    {
        return -EFAULT;
    }

    ssize_t ret = pwrite(fd, kmem, size, offset);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}
#else
{
    ssize_t ret = -ENOSYS;
    return (ret < 0 ? GET_ERRNO() : ret);
}
#endif

/**
 * @brief Create a timer file descriptor.
 *
 * This function creates a timer that can be used to notify a process after a specified
 * amount of time has passed. The timer is represented by a file descriptor, which can be
 * used with functions such as `read` and `poll` to monitor and retrieve notifications
 * about timer expirations.
 *
 * @param[in] clockid The clock to use for the timer. Possible values include:
 *                    - `CLOCK_REALTIME`: The system's real-time clock.
 *                    - `CLOCK_MONOTONIC`: A clock that cannot be set and is not affected by
 *                      changes in the system time.
 * @param[in] flags   Flags that modify the behavior of the timer. The commonly used values are:
 *                    - `TFD_CLOEXEC`: Set the close-on-exec flag for the file descriptor.
 *                    - `TFD_NONBLOCK`: Set the non-blocking flag for the file descriptor.
 *
 * @return sysret_t On success, returns a non-negative file descriptor that refers to the timer.
 *                   On failure, returns a negative error code.
 *
 * @note The timer created by this function can be used to create periodic or one-shot timers.
 *       The timer can be configured using `timerfd_settime` and notifications can be retrieved
 *       by reading from the returned file descriptor.
 */
sysret_t sys_timerfd_create(int clockid, int flags)
{
    int ret;

    ret = timerfd_create(clockid, flags);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Set or modify the expiration time for a timer.
 *
 * This function is used to arm or re-arm a timer associated with a file descriptor created
 * by `sys_timerfd_create`. It allows setting a new expiration time and can also return
 * the previous timer configuration.
 *
 * @param[in] fd     The file descriptor referring to the timer, which was created using
 *                   `sys_timerfd_create`.
 * @param[in] flags  Flags that modify the behavior of the timer. The commonly used values are:
 *                   - `TFD_TIMER_ABSTIME`: If set, the `new` expiration time is an absolute time.
 *                   - `TFD_TIMER_RELATIVE`: The default behavior, where `new` expiration time is
 *                     a relative time from now.
 * @param[in] new    A pointer to a `struct itimerspec` specifying the new expiration time.
 *                   It contains two fields:
 *                   - `it_value`: The initial expiration time of the timer.
 *                   - `it_interval`: The period of periodic timers (if zero, the timer is one-shot).
 * @param[out] old   A pointer to a `struct itimerspec` where the previous timer configuration
 *                   will be stored. This can be `NULL` if the previous configuration is not needed.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note This function allows for both one-shot and periodic timers. If the timer is periodic,
 *       it will continue triggering at intervals specified in `it_interval` until canceled or modified.
 *       When a timer expires, the associated file descriptor becomes readable, and the application
 *       can retrieve the expiration event by reading from the file descriptor.
 */
sysret_t sys_timerfd_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
    int ret = -1;
    struct itimerspec *knew = RT_NULL;
    struct itimerspec *kold = RT_NULL;

    if (new == RT_NULL)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)new, sizeof(struct itimerspec)))
    {
        return -EFAULT;
    }

    knew = kmem_get(sizeof(struct itimerspec));

    if (knew)
    {
        lwp_get_from_user(knew, (void *)new, sizeof(struct itimerspec));

        if (old)
        {
            if (!lwp_user_accessable((void *)old, sizeof(struct itimerspec)))
            {
                kmem_put(knew);
                return -EFAULT;
            }

            kold = kmem_get(sizeof(struct itimerspec));
            if (kold == RT_NULL)
            {
                kmem_put(knew);
                return -ENOMEM;
            }
        }

        ret = timerfd_settime(fd, flags, knew, kold);

        if (old)
        {
            lwp_put_to_user(old, kold, sizeof(*kold));
            kmem_put(kold);
        }

        kmem_put(knew);
    }

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Retrieve the current configuration of a timer.
 *
 * This function is used to obtain the current expiration time and interval of a timer associated
 * with a file descriptor created by `sys_timerfd_create`. It allows querying the current state
 * of the timer, including the time remaining until the next expiration and the period (for periodic timers).
 *
 * @param[in] fd    The file descriptor referring to the timer, which was created using
 *                  `sys_timerfd_create`.
 * @param[out] cur  A pointer to a `struct itimerspec` where the current timer configuration will
 *                  be stored. This structure contains:
 *                  - `it_value`: The time remaining until the timer expires.
 *                  - `it_interval`: The period for periodic timers (zero for one-shot timers).
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The timer's `it_value` field will contain the time remaining until the next expiration.
 *       If the timer is periodic, the `it_interval` field will contain the period for the next expiration.
 *       If the timer has expired and there is no further interval (for one-shot timers), `it_value` will
 *       contain a value of `0`.
 */
sysret_t sys_timerfd_gettime(int fd, struct itimerspec *cur)
{
    int ret = -1;
    struct itimerspec *kcur;

    if (cur == RT_NULL)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)cur, sizeof(struct itimerspec)))
    {
        return -EFAULT;
    }

    kcur = kmem_get(sizeof(struct itimerspec));

    if (kcur)
    {
        lwp_get_from_user(kcur, cur, sizeof(struct itimerspec));
        ret = timerfd_gettime(fd, kcur);
        lwp_put_to_user(cur, kcur, sizeof(struct itimerspec));
        kmem_put(kcur);
    }

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Create a file descriptor for receiving signals.
 *
 * This function creates a file descriptor that can be used to receive signals, similar to how a
 * regular file descriptor is used. The signals specified in the provided signal mask are blocked
 * for the calling thread, and any matching signals will be reported through the file descriptor.
 * This allows signals to be handled in a more controlled, non-interrupt-driven way by using
 * standard I/O operations (e.g., `read()` or `select()`) on the file descriptor.
 *
 * @param[in] fd    A file descriptor associated with the process, typically obtained from
 *                  `sys_signalfd()` or a similar mechanism. If `fd` is `-1`, a new file descriptor
 *                  will be created.
 * @param[in] mask  A pointer to the signal mask (`sigset_t`) that specifies the signals that
 *                  should be received by the file descriptor. Only signals in the mask will be
 *                  reported.
 * @param[in] flags Additional flags to control the behavior of the signalfd. Common flags
 *                  include `O_NONBLOCK` for non-blocking operation.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The caller must call `read()` on the resulting file descriptor to actually receive signals.
 *       Each read returns a `struct signalfd_siginfo` containing the signal number, and additional
 *       information, such as the signal source and sender.
 *
 * @see sys_read(), sigprocmask(), sigaction(), sigsuspend().
 */
sysret_t sys_signalfd(int fd, const sigset_t *mask, int flags)
{
    int ret = 0;
    sigset_t *kmask = RT_NULL;

#ifdef RT_USING_MUSLLIBC
    if (mask == RT_NULL)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)mask, sizeof(struct itimerspec)))
    {
        return -EFAULT;
    }

    kmask = kmem_get(sizeof(struct itimerspec));

    if (kmask)
    {
        if (lwp_get_from_user(kmask, (void *)mask, sizeof(struct itimerspec)) != sizeof(struct itimerspec))
        {
            kmem_put(kmask);
            return -EFAULT;
        }

        ret = signalfd(fd, mask, flags);
        kmem_put(kmask);
    }
#endif

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Creates an anonymous memory-backed file descriptor.
 *
 * This implementation currently returns success without creating a descriptor
 * for compatibility with callers that only probe this interface.
 *
 * @return sysret_t Zero on success.
 */
sysret_t sys_memfd_create()
{
    return 0;
}

/**
 * @brief Set the value of an interval timer.
 *
 * This function is used to set the value of a specified timer that generates periodic signals
 * after the specified intervals. The timer can be configured to generate a signal when it expires,
 * and it can be used for tasks like scheduling periodic events.
 *
 * @param[in] which Specifies which timer to set. Possible values include:
 *                  - `ITIMER_REAL`: Timer that decrements in real time and sends `SIGALRM` when expired.
 *                  - `ITIMER_VIRTUAL`: Timer that decrements only while the process is executing.
 *                  - `ITIMER_PROF`: Timer that decrements while the process is executing or when it is
 *                    executing in the kernel.
 * @param[in] new A pointer to a `struct itimerspec` containing the new value for the timer.
 *                The `itimerspec` structure contains two `timespec` fields: `it_value` for the initial
 *                expiration time and `it_interval` for the interval between successive expirations.
 * @param[out] old A pointer to a `struct itimerspec` where the previous timer values (before the
 *                 timer is set) will be stored.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note If the specified timer is already active, it will be updated with the new values. The timer
 *       will start at the `it_value` time and will repeat at the interval specified in `it_interval`.
 *       If `it_interval` is set to `0`, the timer will not repeat and will only expire once.
 *
 * @see sys_getitimer(), sigaction(), alarm(), setitimer().
 */
sysret_t sys_setitimer(int which, const struct itimerspec * restrict new, struct itimerspec * restrict old)
{
    sysret_t rc = 0;
    rt_lwp_t lwp = lwp_self();
    struct itimerspec new_value_k;
    struct itimerspec old_value_k;

    if (lwp_get_from_user(&new_value_k, (void *)new, sizeof(*new)) != sizeof(*new))
    {
        return -EFAULT;
    }

    rc = lwp_signal_setitimer(lwp, which, &new_value_k, &old_value_k);
    if (old && lwp_put_to_user(old, (void *)&old_value_k, sizeof old_value_k) != sizeof old_value_k)
    {
        return -EFAULT;
    }

    return rc;
}

/**
 * @brief Set the robust list for the current thread.
 *
 * The `sys_set_robust_list` function sets the robust list for the calling thread. The robust list is
 * a list of `struct robust_list_head` elements that contain information about mutexes or other
 * resources that need to be cleaned up if the thread dies unexpectedly.
 *
 * This function is typically used for thread safety in multi-threaded programs, where robust mutexes
 * can be used to avoid leaving resources in an inconsistent state when a thread is terminated
 * without properly unlocking locks or releasing resources.
 *
 * @param[in] head A pointer to the robust list to be set. This list contains `struct robust_list_head`
 *                 entries which are used by the kernel to maintain information about robust mutexes.
 * @param[in] len The length of the robust list (the number of entries in the list). This should correspond
 *                to the size of the list in memory, generally expressed in bytes.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The robust list should be set during the initialization of a thread or task, and it may be
 *       used by the kernel to track which mutexes need to be cleaned up in case of failure.
 *       The list may be manipulated using related functions such as `sys_get_robust_list`.
 *
 * @see sys_get_robust_list(), robust_mutex, pthread_mutex, set_robust_list.
 */
sysret_t sys_set_robust_list(struct robust_list_head *head, size_t len)
{
    if (len != sizeof(*head))
    {
        return -EINVAL;
    }

    rt_thread_self()->robust_list = head;
    return 0;
}

/**
 * @brief Get the robust list for the specified thread.
 *
 * The `sys_get_robust_list` function retrieves the robust list associated with the given thread.
 * The robust list contains `struct robust_list_head` entries used by the kernel to manage
 * robust mutexes and other resources that need to be cleaned up if the thread terminates unexpectedly.
 *
 * This function is primarily used to retrieve the robust list for a specific thread, so that
 * the caller can inspect or manipulate the robust list to handle clean-up operations in case
 * the thread exits while holding resources.
 *
 * @param[in] tid The thread ID of the thread whose robust list is to be retrieved.
 *
 * @param[out] head_ptr A pointer to a pointer to `struct robust_list_head`. On success,
 *                      this will point to the robust list for the specified thread.
 *
 * @param[out] len_ptr A pointer to a variable that will hold the length of the robust list
 *                     (i.e., the number of entries in the list).
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The robust list is used to track mutexes and other resources that need to be cleaned up
 *       if a thread terminates without releasing the resources properly. It is typically used by
 *       the kernel for thread safety and resource management in multi-threaded programs.
 *
 * @see sys_set_robust_list(), robust_mutex, pthread_mutex, get_robust_list.
 */
sysret_t sys_get_robust_list(int tid, struct robust_list_head **head_ptr, size_t *len_ptr)
{
    rt_thread_t thread;
    size_t len;
    struct robust_list_head *head;

    if (!lwp_user_accessable((void *)head_ptr, sizeof(struct robust_list_head *)))
    {
        return -EFAULT;
    }
    if (!lwp_user_accessable((void *)len_ptr, sizeof(size_t)))
    {
        return -EFAULT;
    }

    if (tid == 0)
    {
        thread = rt_thread_self();
        head = thread->robust_list;
    }
    else
    {
        thread = lwp_tid_get_thread_and_inc_ref(tid);
        if (thread)
        {
            head = thread->robust_list;
            lwp_tid_dec_ref(thread);
        }
        else
        {
            return -ESRCH;
        }
    }

    len = sizeof(*(head));

    if (!lwp_put_to_user(len_ptr, &len, sizeof(size_t)))
    {
        return -EFAULT;
    }
    if (!lwp_put_to_user(head_ptr, &head, sizeof(struct robust_list_head *)))
    {
        return -EFAULT;
    }

    return 0;
}
