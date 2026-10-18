/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Suspends execution for a specified amount of time.
 *
 * This system call suspends the execution of the calling thread for the duration
 * specified by the `rqtp` argument. The `rqtp` argument is a pointer to a `struct timespec`
 * that defines the sleep time in seconds and nanoseconds. If the sleep is interrupted by a signal,
 * the function may return early with the remaining time in `rmtp`, which is an optional argument.
 *
 * @param rqtp A pointer to a `struct timespec` that specifies the requested sleep time.
 *             The structure contains two fields: `tv_sec` (seconds) and `tv_nsec` (nanoseconds).
 * @param rmtp A pointer to a `struct timespec` where the remaining time will be stored if the
 *             sleep is interrupted by a signal. This can be `NULL` if the remaining time is not needed.
 * @return On success, returns `0`. On failure, returns `errno` to indicate the error.
 *
 * @note The `timespec` structure has two fields:
 *       - `tv_sec`: The number of whole seconds to sleep.
 *       - `tv_nsec`: The number of nanoseconds to sleep after the seconds. This value should be
 *         in the range [0, 1,000,000,000) nanoseconds.
 *
 * @warning Ensure that the values in `rqtp` are within valid ranges. A `tv_nsec` value greater than
 *          or equal to 1,000,000,000 will result in an error. If `rmtp` is provided, the caller
 *          must ensure the buffer is large enough to store the remaining time.
 *
 * @see sys_sleep(), clock_nanosleep(), nanosleep()
 */
sysret_t sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret = 0;
    LOG_D("sys_nanosleep\n");
    if (!lwp_user_accessable((void *)rqtp, sizeof *rqtp))
        return -EFAULT;

#ifdef ARCH_MM_MMU
    struct timespec rqtp_k;
    struct timespec rmtp_k;

    lwp_get_from_user(&rqtp_k, (void *)rqtp, sizeof rqtp_k);
    ret = nanosleep(&rqtp_k, &rmtp_k);
    if ((ret != -1 || rt_get_errno() == EINTR) && rmtp && lwp_user_accessable((void *)rmtp, sizeof *rmtp))
    {
        lwp_put_to_user(rmtp, (void *)&rmtp_k, sizeof rmtp_k);
        if (ret != 0)
            return -EINTR;
    }
#else
    if (rmtp)
    {
        if (!lwp_user_accessable((void *)rmtp, sizeof *rmtp))
            return -EFAULT;
        ret = nanosleep(rqtp, rmtp);
    }
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Retrieves the current time and timezone information.
 *
 * This system call retrieves the current time in seconds and microseconds since
 * the Unix epoch (1970-01-01 00:00:00 UTC) and stores it in the `tp` argument.
 * It also retrieves the timezone information, if requested, and stores it in the
 * `tzp` argument. The time returned is the local time of the system unless
 * UTC is specified.
 *
 * @param tp A pointer to a `struct timeval` where the current time will be stored.
 *           The `struct timeval` contains two fields:
 *           - `tv_sec`: The number of seconds since the Unix epoch.
 *           - `tv_usec`: The number of microseconds past `tv_sec`.
 * @param tzp A pointer to a `struct timezone` where the timezone information will
 *            be stored. This structure contains two fields:
 *            - `tz_minuteswest`: The number of minutes west of UTC.
 *            - `tz_dsttime`: A flag indicating the type of daylight saving time (DST) adjustment.
 *            If `tzp` is `NULL`, timezone information is not provided.
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @note The `struct timeval` represents the current time in seconds and microseconds,
 *       while `struct timezone` provides information on the timezone relative to UTC
 *       and any daylight saving adjustments.
 *
 * @warning Ensure that `tp` and `tzp` are valid pointers before calling the function.
 *          If you don't need timezone information, you can pass `NULL` for `tzp`.
 *
 * @see sys_time(), time(), gettimeofday()
 */
sysret_t sys_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
#ifdef ARCH_MM_MMU
    struct timeval t_k;

    if (tp)
    {
        if (!lwp_user_accessable((void *)tp, sizeof *tp))
        {
            return -EFAULT;
        }

        t_k.tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        t_k.tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);

        lwp_put_to_user(tp, (void *)&t_k, sizeof t_k);
    }
#else
    if (tp)
    {
        if (!lwp_user_accessable((void *)tp, sizeof *tp))
        {
            return -EFAULT;
        }
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }
#endif

    return 0;
}

/**
 * @brief Sets the system's current time and timezone information.
 *
 * @param tv A pointer to a `struct timeval` that contains the new system time to set.
 *           The `struct timeval` consists of:
 *           - `tv_sec`: The number of seconds since the Unix epoch (1970-01-01 00:00:00 UTC).
 *           - `tv_usec`: The number of microseconds past `tv_sec`.
 * @param tzp A pointer to a `struct timezone` that contains the new timezone settings.
 *            The `struct timezone` consists of:
 *            - `tz_minuteswest`: The number of minutes west of UTC.
 *            - `tz_dsttime`: The type of daylight saving time adjustment.
 *            If `tzp` is `NULL`, the timezone information is not changed.
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @note haven't supported now.
 *
 * @see sys_gettimeofday(), settimeofday(), time()
 */
sysret_t sys_settimeofday(const struct timeval *tv, const struct timezone *tzp)
{
    return 0;
}

/**
 * @brief Sets the time of a specified clock.
 *
 * This function sets the time of the specified clock (identified by `clk`) to the given value. The time is provided
 * as a `struct timespec` containing seconds and nanoseconds. This function can be used to set the system clock or
 * other specific clocks, such as monotonic or real-time clocks.
 *
 * @param[in] clk  The clock ID for which to set the time. The clock can be one of the following:
 *                 - `CLOCK_REALTIME`: Set the system's real-time clock.
 *                 - `CLOCK_MONOTONIC`: Set the monotonic clock, which measures time since some unspecified starting point.
 *                 - `CLOCK_PROCESS_CPUTIME_ID`: Set the CPU time used by the process.
 *                 - `CLOCK_THREAD_CPUTIME_ID`: Set the CPU time used by the current thread.
 *
 * @param[in] ts   A pointer to a `struct timespec` containing the new time to set for the specified clock.
 *                 - `ts->tv_sec`: Seconds since the epoch (for `CLOCK_REALTIME`) or since some unspecified start point (for other clocks).
 *                 - `ts->tv_nsec`: Nanoseconds within the current second.
 *
 * @return sysret_t  Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function requires appropriate permissions for setting the system's clock. In some systems, only privileged users
 *       may change the `CLOCK_REALTIME` clock.
 *
 * @see sys_clock_gettime(), sys_clock_getres()
 */
sysret_t sys_clock_settime(clockid_t clk, const struct timespec *ts)
{
    int ret = 0;

#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    kts = kmem_get(size);
    if (!kts)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kts, (void *)ts, size);
    ret = clock_settime(clk, kts);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kts);

    return ret;
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_settime(clk, ts);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Retrieves the current time of a specified clock.
 *
 * This function retrieves the current time of the specified clock (identified by `clk`) and stores it in the
 * `struct timespec` pointed to by `ts`. The time is expressed in seconds and nanoseconds. The clock can be
 * one of several types, such as real-time, monotonic, or process-specific clocks.
 *
 * @param[in] clk  The clock ID for which to get the time. The clock can be one of the following:
 *                 - `CLOCK_REALTIME`: Get the system's real-time clock.
 *                 - `CLOCK_MONOTONIC`: Get the monotonic clock, which measures time since some unspecified starting point.
 *                 - `CLOCK_PROCESS_CPUTIME_ID`: Get the CPU time used by the process.
 *                 - `CLOCK_THREAD_CPUTIME_ID`: Get the CPU time used by the current thread.
 *
 * @param[out] ts  A pointer to a `struct timespec` where the current time for the specified clock will be stored.
 *                 - `ts->tv_sec`: Seconds since the epoch (for `CLOCK_REALTIME`) or since some unspecified start point (for other clocks).
 *                 - `ts->tv_nsec`: Nanoseconds within the current second.
 *
 * @return sysret_t  Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function requires appropriate permissions for retrieving certain clocks (e.g., `CLOCK_REALTIME`).
 *
 * @see sys_clock_settime(), sys_clock_getres()
 */
sysret_t sys_clock_gettime(clockid_t clk, struct timespec *ts)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    kts = kmem_get(size);
    if (!kts)
    {
        return -ENOMEM;
    }

    ret = clock_gettime(clk, kts);
    if (ret != -1)
        lwp_put_to_user(ts, kts, size);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kts);

    return ret;
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_gettime(clk, ts);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Suspends the execution of the calling thread for the specified time duration.
 *
 * This function causes the calling thread to sleep for the specified time duration, which is provided as a
 * `struct timespec` containing seconds and nanoseconds. The sleep is done based on the specified clock (identified by `clk`).
 * If the `flags` parameter is set to `TIMER_ABSTIME`, the specified time represents an absolute time, otherwise,
 * it represents a relative time interval.
 *
 * @param[in] clk   The clock ID for which to perform the sleep. The clock can be one of the following:
 *                  - `CLOCK_REALTIME`: Use the system's real-time clock.
 *                  - `CLOCK_MONOTONIC`: Use the monotonic clock, which measures time since some unspecified starting point.
 *                  - `CLOCK_PROCESS_CPUTIME_ID`: Use the CPU time used by the process.
 *                  - `CLOCK_THREAD_CPUTIME_ID`: Use the CPU time used by the current thread.
 *
 * @param[in] flags The sleep behavior flags. The possible flags are:
 *                  - `0`: The sleep duration is relative to the current time.
 *                  - `TIMER_ABSTIME`: The sleep duration is absolute (measured from the specified clock).
 *
 * @param[in] rqtp  A pointer to a `struct timespec` containing the requested sleep time.
 *                  - `rqtp->tv_sec`: Seconds to sleep.
 *                  - `rqtp->tv_nsec`: Nanoseconds to sleep (0 Ã¢â€°Â¤ `rqtp->tv_nsec` < 1 billion).
 *
 * @param[out] rmtp A pointer to a `struct timespec` where the remaining time will be stored if the sleep is interrupted.
 *                  If the sleep completes successfully, `rmtp` will not be modified.
 *                  - `rmtp->tv_sec`: Remaining seconds.
 *                  - `rmtp->tv_nsec`: Remaining nanoseconds.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function can be interrupted by signals. In that case, the remaining time is returned in `rmtp`.
 *       If the sleep is not interrupted, the function returns `SYSRET_OK` when the requested time has passed.
 *
 * @see sys_clock_gettime(), sys_clock_settime(), sys_nanosleep()
 */
sysret_t sys_clock_nanosleep(clockid_t clk, int flags, const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret = 0;
    LOG_D("sys_nanosleep\n");
    if (!lwp_user_accessable((void *)rqtp, sizeof *rqtp))
        return -EFAULT;

#ifdef ARCH_MM_MMU
    struct timespec rqtp_k;
    struct timespec rmtp_k;

    lwp_get_from_user(&rqtp_k, (void *)rqtp, sizeof rqtp_k);
    ret = clock_nanosleep(clk, flags, &rqtp_k, &rmtp_k);
    if ((ret != -1 || rt_get_errno() == EINTR) && rmtp && lwp_user_accessable((void *)rmtp, sizeof *rmtp))
    {
        lwp_put_to_user(rmtp, (void *)&rmtp_k, sizeof rmtp_k);
        if (ret != 0)
            return -EINTR;
    }
#else
    if (rmtp)
    {
        if (!lwp_user_accessable((void *)rmtp, sizeof *rmtp))
            return -EFAULT;
        ret = clock_nanosleep(clk, flags, rqtp, rmtp);
    }
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Get the resolution of the specified clock.
 *
 * This function retrieves the resolution of the specified clock, which is the smallest time interval that the clock can measure.
 * The resolution is returned in a `struct timespec` which contains seconds and nanoseconds.
 *
 * @param[in] clk   The clock ID for which to get the resolution. The clock can be one of the following:
 *                  - `CLOCK_REALTIME`: System's real-time clock.
 *                  - `CLOCK_MONOTONIC`: Monotonic clock (measures time since an unspecified point).
 *                  - `CLOCK_PROCESS_CPUTIME_ID`: CPU time consumed by the current process.
 *                  - `CLOCK_THREAD_CPUTIME_ID`: CPU time consumed by the current thread.
 *
 * @param[out] ts   A pointer to a `struct timespec` where the clock's resolution will be stored.
 *                  - `ts->tv_sec`: The number of seconds in the resolution.
 *                  - `ts->tv_nsec`: The number of nanoseconds in the resolution (0 â‰¤ `ts->tv_nsec` < 1 billion).
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The resolution may be zero for some clocks, depending on the system's configuration.
 *       A clock's resolution determines the smallest unit of time the clock can measure.
 *
 * @see sys_clock_gettime(), sys_clock_settime(), sys_clock_nanosleep()
 */
sysret_t sys_clock_getres(clockid_t clk, struct timespec *ts)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct timespec kts;
    size_t size = sizeof(struct timespec);

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    ret = clock_getres(clk, &kts);

    if (ret != -1)
        lwp_put_to_user(ts, &kts, size);
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_getres(clk, ts);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Rename or move a file or directory.
 *
 * This function renames or moves a file or directory from `oldpath` to `newpath`.
 * If the `newpath` exists, it may be overwritten depending on the system's file system behavior and
 * the permissions of the files involved.
 *
 * @param[in] oldpath  The current path of the file or directory to rename or move.
 * @param[in] newpath  The new path or name to which the file or directory should be renamed or moved.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note If `oldpath` and `newpath` refer to different file systems, the behavior may vary,
 *       as the operation might involve copying and removing files instead of simply renaming them.
 *       The success of the operation also depends on the permissions of the source and destination.
 *
 * @see sys_unlink(), sys_mkdir(), sys_access()
 */
sysret_t sys_rename(const char *oldpath, const char *newpath)
{
    int ret = -1;
#ifdef ARCH_MM_MMU
    int err;

    err = lwp_user_strlen(oldpath);
    if (err <= 0)
    {
        return -EFAULT;
    }

    err = lwp_user_strlen(newpath);
    if (err <= 0)
    {
        return -EFAULT;
    }
#endif
    ret = rename(oldpath, newpath);
    return (ret < 0 ? GET_ERRNO() : ret);
}

typedef unsigned long long rlim_t;

struct rlimit
{
    rlim_t rlim_cur;
    rlim_t rlim_max;
};

#define RLIMIT_CPU     0
#define RLIMIT_FSIZE   1
#define RLIMIT_DATA    2
#define RLIMIT_STACK   3
#define RLIMIT_CORE    4
#define RLIMIT_RSS     5
#define RLIMIT_NPROC   6
#define RLIMIT_NOFILE  7
#define RLIMIT_MEMLOCK 8
#define RLIMIT_AS      9

/**
 * @brief Sets or gets process resource limits.
 *
 * This implementation is currently unsupported and returns `-ENOSYS`.
 *
 * @param[in] pid The target process ID.
 * @param[in] resource The resource limit identifier.
 * @param[in] new_rlim The new limit, or `NULL`.
 * @param[out] old_rlim Receives the current limit, or `NULL`.
 * @return sysret_t Always returns `-ENOSYS`.
 */
sysret_t sys_prlimit64(pid_t pid,
                       unsigned int resource,
                       const struct rlimit *new_rlim,
                       struct rlimit *old_rlim)
{
    return -ENOSYS;
}

/**
 * @brief Get resource limits.
 *
 * This function retrieves the current resource limits for the specified resource type.
 * The resource limit specifies the maximum value for a particular resource that a process or thread can use.
 * The limits are returned in an array `rlim` where:
 * - `rlim[0]` represents the soft limit (the current value).
 * - `rlim[1]` represents the hard limit (the maximum allowable value).
 *
 * @param[in] resource  The resource for which to get the limits. It can be one of the following:
 *                      - `RLIMIT_NOFILE`: Maximum number of file descriptors.
 *
 * @param[out] rlim    An array to store the resource limits. The array should have at least 2 elements:
 *                     - `rlim[0]`: The soft limit for the resource.
 *                     - `rlim[1]`: The hard limit for the resource.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The limits returned by `sys_getrlimit` are subject to system constraints and may vary across different systems.
 *
 * @see sys_setrlimit(), sys_getrlimit64(), sys_getrusage()
 */
sysret_t sys_getrlimit(unsigned int resource, unsigned long rlim[2])
{
    int ret = -1;
    unsigned long krlim[2] = { 0, 0 };

    if (!lwp_user_accessable((void *)rlim, sizeof(unsigned long[2])))
    {
        return -EFAULT;
    }

    if (lwp_get_from_user(krlim, rlim, sizeof(unsigned long[2])) != sizeof(unsigned long[2]))
    {
        return -EINVAL;
    }

    switch (resource)
    {
    case RLIMIT_NOFILE:
    {
        struct dfs_fdtable *fdt = dfs_fdtable_get();

        dfs_file_lock();
        krlim[0] = fdt->maxfd;
        dfs_file_unlock();
        krlim[1] = DFS_FD_MAX;
        ret = 0;
    }
    break;
    default:
        return -EINVAL;
        break;
    }

    lwp_put_to_user((void *)rlim, krlim, sizeof(unsigned long[2]));

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Sets a process resource limit.
 *
 * This implementation is currently unsupported and returns `-ENOSYS`.
 *
 * @param[in] resource The resource limit identifier.
 * @param[in] rlim The new resource limit.
 * @return sysret_t Always returns `-ENOSYS`.
 */
sysret_t sys_setrlimit(unsigned int resource, struct rlimit *rlim)
{
    return -ENOSYS;
}

/**
 * @brief Get random data from the kernel's random number generator.
 *
 * This function retrieves cryptographically secure random data from the kernel's random number generator
 * and stores it in the buffer provided by the user. The data can be used for cryptographic operations or
 * other applications requiring randomization.
 *
 * @param[out] buf     A pointer to the buffer where the random data will be stored. The buffer must be large
 *                     enough to hold the requested amount of random data.
 * @param[in]  buflen  The number of bytes of random data to retrieve. This value must be a positive integer.
 * @param[in]  flags   Optional flags to modify the behavior of the random data retrieval. Possible values may include:
 *                     - `GRND_RANDOM`: Requests random data from the system's non-blocking random source.
 *                     - `GRND_NONBLOCK`: Instructs the function to return immediately even if insufficient entropy is available.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note
 * - If the `GRND_NONBLOCK` flag is not set and there is insufficient entropy in the system's random pool,
 *   this function may block until enough entropy is available.
 * - The function returns cryptographically secure random data, suitable for use in secure applications.
 *
 * @see sys_random(), sys_getentropy()
 */
sysret_t sys_getrandom(void *buf, size_t buflen, unsigned int flags)
{
    int ret = -1;
    int count = 0;
    void *kmem = RT_NULL;
    rt_device_t rd_dev = RT_NULL;

    if (flags & GRND_RANDOM)
        rd_dev = rt_device_find("random");
    else
        rd_dev = rt_device_find("urandom");

    if (rd_dev == RT_NULL)
    {
        return -EFAULT;
    }

    if (rt_device_open(rd_dev, RT_DEVICE_OFLAG_RDONLY) != RT_EOK)
    {
        return -EFAULT;
    }

    if (!lwp_user_accessable(buf, buflen))
    {
        rt_device_close(rd_dev);
        return -EFAULT;
    }

#ifdef ARCH_MM_MMU
    kmem = kmem_get(buflen);
    if (!kmem)
    {
        rt_device_close(rd_dev);
        return -ENOMEM;
    }

    while (count < buflen)
    {
        ret = rt_device_read(rd_dev, count, (char *)kmem + count, buflen - count);
        if (ret <= 0)
            break;
        count += ret;
    }
    rt_device_close(rd_dev);

    ret = count;
    if (count > 0)
    {
        ret = lwp_put_to_user(buf, kmem, count);
    }
    kmem_put(kmem);
#else
    while (count < buflen)
    {
        ret = rt_device_read(rd_dev, count, (char *)kmem + count, buflen - count);
        if (ret <= 0)
            break;
        count += ret;
    }
    rt_device_close(rd_dev);

    ret = count;
#endif
    return ret;
}

/**
 * @brief Read the value of a symbolic link.
 *
 * This function reads the value of a symbolic link and stores it in the provided buffer. The value is the
 * path to which the symbolic link points. If the symbolic link is too long to fit in the provided buffer,
 * the function returns the number of bytes needed to store the entire path (not including the terminating null byte).
 *
 * @param[in]  path   The path of the symbolic link to read.
 * @param[out] buf    A buffer where the symbolic link's target will be stored. The buffer must be large enough
 *                    to hold the path of the symbolic link.
 * @param[in]  bufsz  The size of the buffer `buf`. It specifies the maximum number of bytes to read.
 *
 * @return ssize_t The number of bytes written to `buf` (excluding the terminating null byte) on success.
 *                 On failure, it returns a negative error code:
 *                 - `-EINVAL`: Invalid path.
 *                 - `-ENOMEM`: Insufficient memory to read the link.
 *                 - `-EFAULT`: Invalid address for the `buf`.
 *
 * @note It will (silently) truncate the contents(to a length of bufsiz characters),
 *       in case the buffer is too small to hold all of the contents.
 *
 * @see sys_symlink(), sys_lstat()
 */
ssize_t sys_readlink(char *path, char *buf, size_t bufsz)
{
    size_t len, copy_len;
    int err, rtn;
    char *copy_path;

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    if (!lwp_user_accessable(buf, bufsz))
    {
        return -EINVAL;
    }

    copy_path = (char *)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, path, len);
    copy_path[copy_len] = '\0';

    char *link_fn = (char *)rt_malloc(DFS_PATH_MAX);
    if (link_fn)
    {
        err = dfs_file_readlink(copy_path, link_fn, DFS_PATH_MAX);
        if (err > 0)
        {
            buf[bufsz > err ? err : bufsz] = '\0';
            rtn = lwp_put_to_user(buf, link_fn, bufsz > err ? err : bufsz);
        }
        else
        {
            rtn = -EIO;
        }
        rt_free(link_fn);
    }
    else
    {
        rtn = -ENOMEM;
    }

    rt_free(copy_path);
    return rtn;
}

/**
 * @brief Set the CPU affinity mask of a process.
 *
 * This function sets the CPU affinity mask for a specified process. The affinity mask determines which CPUs the
 * process is allowed to execute on. The process will be restricted to the CPUs specified in the mask.
 *
 * @param[in] pid     The process ID of the process whose CPU affinity is to be set. If the `pid` is `0`, the
 *                    affinity of the calling process will be modified.
 * @param[in] size    The size (in bytes) of the CPU set, typically `sizeof(cpu_set_t)`.
 * @param[in] set     A pointer to the CPU set. The CPU set is a bitmask representing which CPUs the process
 *                    is allowed to run on. The bitmask must have enough bits to cover the number of CPUs on the system.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The CPU set is represented as a bitmask where each bit corresponds to a CPU. If the bit is set, the process
 *       can execute on that CPU. The number of CPUs is platform-dependent, and the size of `set` must be large enough
 *       to hold a bit for each CPU.
 *
 * @see sys_sched_getaffinity(), sys_setcpu()
 */
sysret_t sys_sched_setaffinity(pid_t pid, size_t size, void *set)
{
    void *kset = RT_NULL;

    if (size <= 0 || size > sizeof(cpu_set_t))
    {
        return -EINVAL;
    }
    if (!lwp_user_accessable((void *)set, size))
        return -EFAULT;

    kset = kmem_get(size);
    if (kset == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kset, set, size) != size)
    {
        kmem_put(kset);
        return -EINVAL;
    }

    for (int i = 0; i < size * 8; i++)
    {
        if (CPU_ISSET_S(i, size, kset))
        {
            kmem_put(kset);

            /**
             * yes it's tricky.
             * But when we talk about 'pid' from GNU libc, it's the 'task-id'
             * aka 'thread->tid' known in kernel.
             */
            return lwp_setaffinity(pid, i);
        }
    }

    kmem_put(kset);

    return -1;
}

/**
 * @brief Get the CPU affinity mask of a process.
 *
 * This function retrieves the CPU affinity mask for a specified process. The affinity mask indicates which CPUs the
 * process is allowed to execute on. The process can run on any of the CPUs represented by the bits set in the mask.
 *
 * @param[in]  pid    The process ID of the process whose CPU affinity is to be retrieved. If `pid` is `0`, the
 *                    affinity mask of the calling process will be retrieved.
 * @param[in]  size   The size (in bytes) of the CPU set, typically `sizeof(cpu_set_t)`.
 * @param[out] set    A pointer to a buffer where the CPU affinity mask will be stored. The mask is represented
 *                    as a bitmask, where each bit corresponds to a CPU. The bit is set if the process can run on that CPU.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The CPU set is represented as a bitmask where each bit corresponds to a CPU. If the bit is set, the process
 *       can execute on that CPU. The number of CPUs is platform-dependent, and the size of `set` must be large enough
 *       to hold a bit for each CPU.
 *
 * @see sys_sched_setaffinity(), sys_getcpu()
 */
sysret_t sys_sched_getaffinity(const pid_t pid, size_t size, void *set)
{
#ifdef ARCH_MM_MMU
    LWP_DEF_RETURN_CODE(rc);
    void *mask;
    struct rt_lwp *lwp;

    if (size <= 0 || size > sizeof(cpu_set_t))
    {
        return -EINVAL;
    }
    if (!lwp_user_accessable(set, size))
    {
        return -EFAULT;
    }
    mask = kmem_get(size);
    if (!mask)
    {
        return -ENOMEM;
    }

    CPU_ZERO_S(size, mask);

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(pid);

    if (!lwp)
    {
        rc = -ESRCH;
    }
    else
    {
#ifdef RT_USING_SMP
        if (lwp->bind_cpu == RT_CPUS_NR)    /* not bind */
        {
            for (int i = 0; i < RT_CPUS_NR; i++)
            {
                CPU_SET_S(i, size, mask);
            }
        }
        else /* set bind cpu */
        {
            /* TODO: only single-core bindings are now supported of rt-smart */
            CPU_SET_S(lwp->bind_cpu, size, mask);
        }
#else
        CPU_SET_S(0, size, mask);
#endif

        if (lwp_put_to_user(set, mask, size) != size)
            rc = -EFAULT;
        else
            rc = size;
    }

    lwp_pid_lock_release();

    kmem_put(mask);

    LWP_RETURN(rc);
#else
    return -1;
#endif
}

/**
 * @brief Retrieve system information.
 *
 * This function provides details about the current state of the system, such as uptime, memory usage,
 * load average, and other key statistics. The information is stored in a structure pointed to by `info`.
 *
 * @param[out] info A pointer to a buffer where system information will be stored. The structure should
 *                  be compatible with the format expected by the system, typically `struct sysinfo`.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The structure of `info` must be predefined and consistent with the system's expectations.
 *       This function does not allocate memory for `info`; the caller must provide sufficient
 *       memory for the structure.
 */
sysret_t sys_sysinfo(void *info)
{
#ifdef ARCH_MM_MMU
    struct sysinfo kinfo = { 0 };
    rt_size_t total_pages = 0, free_pages = 0;

    if (!lwp_user_accessable(info, sizeof(struct sysinfo)))
    {
        return -EFAULT;
    }

    kinfo.uptime = rt_tick_get_millisecond() / 1000;
    /* TODO: 1, 5, and 15 minute load averages */
    kinfo.loads[0] = kinfo.loads[1] = kinfo.loads[2] = rt_object_get_length(RT_Object_Class_Thread);
    rt_page_get_info(&total_pages, &free_pages);
    kinfo.totalram = total_pages;
    kinfo.freeram = free_pages;

    /* TODO: implementation procfs, here is counter the lwp number */
    struct lwp_avl_struct *pids = lwp_get_pid_ary();
    for (int index = 0; index < RT_LWP_MAX_NR; index++)
    {
        struct rt_lwp *lwp = (struct rt_lwp *)pids[index].data;

        if (lwp)
        {
            kinfo.procs++;
        }
    }

    rt_page_high_get_info(&total_pages, &free_pages);
    kinfo.totalhigh = total_pages;
    kinfo.freehigh = free_pages;
    kinfo.mem_unit = ARCH_PAGE_SIZE;

    if (lwp_put_to_user(info, &kinfo, sizeof(struct sysinfo)) != sizeof(struct sysinfo))
    {
        return -EFAULT;
    }

    return 0;
#else
    return -1;
#endif
}

static rt_bool_t _sys_sched_priority_is_valid(int priority);

/**
 * @brief Set scheduling parameters for a specific thread.
 *
 * This function allows setting the scheduling parameters for a thread identified by its thread ID (`tid`).
 * The parameters are provided via the `param` argument, which should be a structure compatible with the
 * system's scheduling policies.
 *
 * @param[in] tid The thread ID of the target thread for which the scheduling parameters are to be set.
 * @param[in] param A pointer to a structure containing the new scheduling parameters. The structure
 *                  typically includes fields like priority and policy.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The caller must have appropriate permissions to change the scheduling parameters of the specified thread.
 *       The exact structure and fields of `param` depend on the system's implementation and scheduling policies.
 */
sysret_t sys_sched_setparam(pid_t tid, void *param)
{
    struct sched_param *sched_param = RT_NULL;
    rt_thread_t thread;
    int ret = -1;

    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }

    sched_param = kmem_get(sizeof(struct sched_param));
    if (sched_param == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(sched_param, param, sizeof(struct sched_param)) != sizeof(struct sched_param))
    {
        kmem_put(sched_param);
        return -EINVAL;
    }

    if (!_sys_sched_priority_is_valid(sched_param->sched_priority))
    {
        kmem_put(sched_param);
        return -EINVAL;
    }

    thread = lwp_tid_get_thread_and_inc_ref(tid);

    if (thread)
    {
        ret = rt_thread_control(thread, RT_THREAD_CTRL_RESET_PRIORITY, (void *)&sched_param->sched_priority);
    }

    lwp_tid_dec_ref(thread);

    kmem_put(sched_param);

    return ret;
}

/**
 * @brief Relinquish the processor voluntarily.
 *
 * This function causes the calling thread to yield the processor, allowing other threads
 * that are ready to run to execute. The thread will be placed back into the scheduler's
 * ready queue and may be rescheduled according to its priority and the system's scheduling policy.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is typically used in cooperative multitasking scenarios or when a thread
 *       explicitly determines it no longer needs the processor at the moment.
 */
sysret_t sys_sched_yield(void)
{
    rt_thread_yield();
    return 0;
}

/**
 * @brief Retrieve the scheduling parameters of a specific thread.
 *
 * This function retrieves the scheduling parameters of the thread identified by the thread ID (`tid`).
 * The retrieved parameters are stored in the structure pointed to by the `param` argument.
 *
 * @param[in]  tid   The thread ID of the target thread whose scheduling parameters are to be retrieved.
 * @param[out] param A pointer to a structure where the scheduling parameters will be stored. The structure
 *                   typically includes fields like priority and policy.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The caller must have appropriate permissions to query the scheduling parameters of the specified thread.
 *       The exact structure and fields of `param` depend on the system's implementation and scheduling policies.
 */
sysret_t sys_sched_getparam(const pid_t tid, void *param)
{
    struct sched_param *sched_param = RT_NULL;
    rt_thread_t thread;
    int ret = -1;

    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }

    sched_param = kmem_get(sizeof(struct sched_param));
    if (sched_param == RT_NULL)
    {
        return -ENOMEM;
    }

    thread = lwp_tid_get_thread_and_inc_ref(tid);

    if (thread)
    {
        sched_param->sched_priority = RT_SCHED_PRIV(thread).current_priority;
        ret = 0;
    }

    lwp_tid_dec_ref(thread);

    lwp_put_to_user((void *)param, sched_param, sizeof(struct sched_param));
    kmem_put(sched_param);

    return ret;
}

/**
 * @brief Get the maximum priority for a given scheduling policy.
 *
 * This function retrieves the maximum priority value that can be used with the specified
 * scheduling policy.
 *
 * @param[in] policy The scheduling policy for which to retrieve the maximum priority.
 *
 * @return sysret_t Returns the maximum priority value on success. On failure, returns a
 *                  negative error code.
 *
 * @note The valid priority range depends on the system's configuration and the selected
 *       scheduling policy. The returned value represents the highest priority that can
 *       be assigned to a thread using the given policy.
 */
sysret_t sys_sched_get_priority_max(int policy)
{
    if (policy < 0)
    {
        SET_ERRNO(EINVAL);
        return -rt_get_errno();
    }
    return RT_THREAD_PRIORITY_MAX;
}

/**
 * @brief Get the minimum priority for a given scheduling policy.
 *
 * This function retrieves the minimum priority value that can be used with the specified
 * scheduling policy.
 *
 * @param[in] policy The scheduling policy for which to retrieve the minimum priority.
 *
 * @return sysret_t Returns the minimum priority value on success. On failure, returns a
 *                  negative error code.
 *
 * @note The valid priority range depends on the system's configuration and the selected
 *       scheduling policy. The returned value represents the lowest priority that can
 *       be assigned to a thread using the given policy.
 */
sysret_t sys_sched_get_priority_min(int policy)
{
    if (policy < 0)
    {
        SET_ERRNO(EINVAL);
        return -rt_get_errno();
    }
    return 0;
}

static rt_bool_t _sys_sched_priority_is_valid(int priority)
{
    return (priority >= 0) && (priority < RT_THREAD_PRIORITY_MAX);
}

#if defined(RT_USING_UTESTCASES) && defined(RT_USING_SMART)
rt_bool_t rt_utest_sys_sched_priority_is_valid(int priority)
{
    return _sys_sched_priority_is_valid(priority);
}
#endif

/**
 * @brief Set the scheduling policy and parameters for a thread.
 *
 * This function sets the scheduling policy and associated parameters for the specified thread.
 * It allows controlling the scheduling behavior of threads.
 *
 * @param[in] tid    The thread ID of the target thread.
 * @param[in] policy The scheduling policy to be applied. Common values include:
 *                   - `SCHED_FIFO`: First-in, first-out scheduling.
 *                   - `SCHED_RR`: Round-robin scheduling.
 *                   - `SCHED_OTHER`: Default or standard scheduling.
 * @param[in] param  Pointer to a structure containing scheduling parameters, such as priority.
 *                   The structure type depends on the system implementation.
 *
 * @return sysret_t Returns 0 on success. On failure, returns a negative error code.
 *
 * @note This function requires appropriate permissions to modify the scheduling settings
 *       of another thread. For most systems, elevated privileges may be required.
 *       Ensure the `param` structure is properly initialized for the given `policy`.
 */
sysret_t sys_sched_setscheduler(int tid, int policy, void *param)
{
    sysret_t ret;
    struct sched_param *sched_param = RT_NULL;
    rt_thread_t thread = RT_NULL;

    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }

    sched_param = kmem_get(sizeof(struct sched_param));
    if (sched_param == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(sched_param, param, sizeof(struct sched_param)) != sizeof(struct sched_param))
    {
        kmem_put(sched_param);
        return -EINVAL;
    }

    if (!_sys_sched_priority_is_valid(sched_param->sched_priority))
    {
        kmem_put(sched_param);
        return -EINVAL;
    }

    thread = lwp_tid_get_thread_and_inc_ref(tid);
    ret = rt_thread_control(thread, RT_THREAD_CTRL_RESET_PRIORITY, (void *)&sched_param->sched_priority);
    lwp_tid_dec_ref(thread);

    kmem_put(sched_param);

    return ret;
}

/**
 * @brief Get the scheduling policy of a thread.
 *
 * This function retrieves the current scheduling policy of the specified thread.
 *
 * @param[in] tid The thread ID of the target thread.
 *
 * @return sysret_t Returns the scheduling policy of the thread on success. On failure,
 *                  returns a negative error code.
 *
 * @note The caller must have appropriate permissions to query the scheduling policy
 *       of the specified thread.
 */
sysret_t sys_sched_getscheduler(int tid)
{
    rt_thread_t thread = RT_NULL;
    int rtn;

    thread = lwp_tid_get_thread_and_inc_ref(tid);
    lwp_tid_dec_ref(thread);

    if (thread)
    {
        rtn = SCHED_RR;
    }
    else
    {
        rtn = -ESRCH;
    }

    return rtn;
}

/**
 * @brief Flush the file descriptors' data to disk.
 *
 * This function flushes all modified data of the file associated with the specified
 * file descriptor to disk, ensuring that any changes made to the file are committed
 * to permanent storage.
 *
 * @param[in] fd The file descriptor associated with the file to be flushed. It should
 *               refer to an open file.
 *
 * @return sysret_t Returns `0` (0) on success. On failure, returns a negative
 *                  error code.
 *
 * @note The `fsync` function ensures that all data written to the file is physically
 *       stored on disk, but it does not guarantee that all file metadata is flushed.
 *       To flush both data and metadata, `fdatasync` can be used.
 */
sysret_t sys_fsync(int fd)
{
    int res = fsync(fd);
    if (res < 0)
        res = rt_get_errno();
    return res;
}
