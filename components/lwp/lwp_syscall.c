/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-10     Bernard      first version
 * 2021-02-03     lizhirui     add limit condition for network syscall and add 64-bit arch support
 * 2021-02-06     lizhirui     fix some bugs
 * 2021-02-12     lizhirui     add 64-bit support for sys_brk
 * 2021-02-20     lizhirui     fix some warnings
 * 2023-03-13     WangXiaoyao  Format & fix syscall return value
 * 2023-07-06     Shell        adapt the signal API, and clone, fork to new implementation of lwp signal
 * 2023-07-27     Shell        Move tid_put() from lwp_free() to sys_exit()
 * 2023-11-16     xqyjlj       fix some syscalls (about sched_*, get/setpriority)
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-11-30     Shell        Fix sys_setitimer() and exit(status)
 */
#define __RT_IPC_SOURCE__
#define _GNU_SOURCE

/* RT-Thread System call */
#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#include <string.h>
#include <stdint.h>

#define DBG_TAG    "lwp.syscall"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include "syscall_generic.h"

#include "libc_musl.h"
#include "lwp_internal.h"
#ifdef ARCH_MM_MMU
#include <mm_aspace.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>
#endif

#include <fcntl.h>
#include <sys/utsname.h>

#ifdef RT_USING_DFS
#include <eventfd.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <dfs_file.h>
#ifdef RT_USING_DFS_V2
#include <dfs_dentry.h>
#endif
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */
#include <sys/timerfd.h>
#include <sys/ioctl.h>
#ifdef RT_USING_MUSLLIBC
#include <sys/signalfd.h>
#endif
#endif

#include "mqueue.h"

#ifdef RT_USING_SAL
    #include <netdev_ipaddr.h>
    #include <netdev.h>

    #include <sal_netdb.h>
    #include <sal_socket.h>
    #include <sys/socket.h>

#endif /* RT_USING_SAL */

#if (defined(RT_USING_SAL) && defined(SAL_USING_POSIX))
    #include <sys/socket.h>

    #define SYSCALL_NET(f)      f
#else
    #define SYSCALL_NET(f)      SYSCALL_SIGN(sys_notimpl)
#endif /* (defined(RT_USING_SAL) && defined(SAL_USING_POSIX)) */

#if defined(RT_USING_DFS) && defined(ARCH_MM_MMU)
    #define SYSCALL_USPACE(f)   f
#else
    #define SYSCALL_USPACE(f)   SYSCALL_SIGN(sys_notimpl)
#endif /* defined(RT_USING_DFS) && defined(ARCH_MM_MMU) */

#include "lwp_ipc_internal.h"
#include <sched.h>

#include <sys/sysinfo.h>

#ifndef GRND_NONBLOCK
#define GRND_NONBLOCK   0x0001
#endif /* GRND_NONBLOCK */

#ifndef GRND_RANDOM
#define GRND_RANDOM 0x0002
#endif /*GRND_RANDOM */

#ifndef RT_USING_POSIX_TIMER
#error "No definition RT_USING_POSIX_TIMER"
#endif /* RT_USING_POSIX_TIMER */

#ifndef RT_USING_POSIX_CLOCK
#error "No definition RT_USING_POSIX_CLOCK"
#endif /* RT_USING_POSIX_CLOCK */

void lwp_cleanup(struct rt_thread *tid);

#ifdef ARCH_MM_MMU
    #define ALLOC_KERNEL_STACK_SIZE 5120

    static void *kmem_get(size_t size)
    {
        return rt_malloc(size);
    }

    static void kmem_put(void *kptr)
    {
        rt_free(kptr);
    }
#else /* ARCH_MM_MMU */
    #define ALLOC_KERNEL_STACK_SIZE 1536
    #define ALLOC_KERNEL_STACK_SIZE_MIN 1024
    #define ALLOC_KERNEL_STACK_SIZE_MAX 4096

    extern void set_user_context(void *stack);
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SAL
    /* The same socket option is defined differently in the user interfaces and the
    * implementation. The options should be converted in the kernel. */
    #include "lwp_sys_socket.h"

    static void convert_sockopt(int *level, int *optname)
    {
        if (*level == INTF_SOL_SOCKET)
        {
            *level = IMPL_SOL_SOCKET;

            switch (*optname)
            {
                case INTF_SO_REUSEADDR:
                    *optname = IMPL_SO_REUSEADDR;
                    break;
                case INTF_SO_KEEPALIVE:
                    *optname = IMPL_SO_KEEPALIVE;
                    break;
                case INTF_SO_BROADCAST:
                    *optname = IMPL_SO_BROADCAST;
                    break;
                case INTF_SO_ACCEPTCONN:
                    *optname = IMPL_SO_ACCEPTCONN;
                    break;
                case INTF_SO_DONTROUTE:
                    *optname = IMPL_SO_DONTROUTE;
                    break;
                case INTF_SO_LINGER:
                    *optname = IMPL_SO_LINGER;
                    break;
                case INTF_SO_OOBINLINE:
                    *optname = IMPL_SO_OOBINLINE;
                    break;
                case INTF_SO_REUSEPORT:
                    *optname = IMPL_SO_REUSEPORT;
                    break;
                case INTF_SO_SNDBUF:
                    *optname = IMPL_SO_SNDBUF;
                    break;
                case INTF_SO_RCVBUF:
                    *optname = IMPL_SO_RCVBUF;
                    break;
                case INTF_SO_SNDLOWAT:
                    *optname = IMPL_SO_SNDLOWAT;
                    break;
                case INTF_SO_RCVLOWAT:
                    *optname = IMPL_SO_RCVLOWAT;
                    break;
                case INTF_SO_SNDTIMEO:
                    *optname = IMPL_SO_SNDTIMEO;
                    break;
                case INTF_SO_RCVTIMEO:
                    *optname = IMPL_SO_RCVTIMEO;
                    break;
                case INTF_SO_ERROR:
                    *optname = IMPL_SO_ERROR;
                    break;
                case INTF_SO_TYPE:
                    *optname = IMPL_SO_TYPE;
                    break;
                case INTF_SO_NO_CHECK:
                    *optname = IMPL_SO_NO_CHECK;
                    break;
                case INTF_SO_BINDTODEVICE:
                    *optname = IMPL_SO_BINDTODEVICE;
                    break;
                case INTF_SO_TIMESTAMPNS:
                    *optname = IMPL_SO_TIMESTAMPNS;
                    break;
                case INTF_SO_TIMESTAMPING:
                    *optname = IMPL_SO_TIMESTAMPING;
                    break;
                case INTF_SO_SELECT_ERR_QUEUE:
                    *optname = IMPL_SO_SELECT_ERR_QUEUE;
                    break;

                /*
                * SO_DONTLINGER (*level = ((int)(~SO_LINGER))),
                * SO_USELOOPBACK (*level = 0x0040) and
                * SO_CONTIMEO (*level = 0x1009) are not supported for now.
                */
                default:
                    *optname = 0;
                    break;
            }
            return;
        }

        if (*level == INTF_IPPROTO_IP)
        {
            *level = IMPL_IPPROTO_IP;

            switch (*optname)
            {
                case INTF_IP_TTL:
                    *optname = IMPL_IP_TTL;
                    break;
                case INTF_IP_TOS:
                    *optname = IMPL_IP_TOS;
                    break;
                case INTF_IP_MULTICAST_TTL:
                    *optname = IMPL_IP_MULTICAST_TTL;
                    break;
                case INTF_IP_MULTICAST_IF:
                    *optname = IMPL_IP_MULTICAST_IF;
                    break;
                case INTF_IP_MULTICAST_LOOP:
                    *optname = IMPL_IP_MULTICAST_LOOP;
                    break;
                case INTF_IP_ADD_MEMBERSHIP:
                    *optname = IMPL_IP_ADD_MEMBERSHIP;
                    break;
                case INTF_IP_DROP_MEMBERSHIP:
                    *optname = IMPL_IP_DROP_MEMBERSHIP;
                    break;
                default:
                    break;
            }
        }

        if (*level == INTF_IPPROTO_TCP)
        {
            *level = IMPL_IPPROTO_TCP;

            switch (*optname)
            {
                case INTF_TCP_NODELAY:
                    *optname = IMPL_TCP_NODELAY;
                    break;
                case INTF_TCP_KEEPALIVE:
                    *optname = IMPL_TCP_KEEPALIVE;
                    break;
                case INTF_TCP_KEEPIDLE:
                    *optname = IMPL_TCP_KEEPIDLE;
                    break;
                case INTF_TCP_KEEPINTVL:
                    *optname = IMPL_TCP_KEEPINTVL;
                    break;
                case INTF_TCP_KEEPCNT:
                    *optname = IMPL_TCP_KEEPCNT;
                    break;
                default:
                    break;
            }
            return;
        }

        if (*level == INTF_IPPROTO_IPV6)
        {
            *level = IMPL_IPPROTO_IPV6;

            switch (*optname)
            {
                case INTF_IPV6_V6ONLY:
                    *optname = IMPL_IPV6_V6ONLY;
                    break;
                default:
                    break;
            }
            return;
        }

    }
#endif  /* RT_USING_SAL */

#if defined(RT_USING_LWIP) || defined(SAL_USING_UNET)
    static void sockaddr_tolwip(const struct musl_sockaddr *std, struct sockaddr *lwip)
    {
        if (std && lwip)
        {
            lwip->sa_len = sizeof(*lwip);
            lwip->sa_family = (sa_family_t) std->sa_family;
            memcpy(lwip->sa_data, std->sa_data, sizeof(lwip->sa_data));
        }
    }

    static void sockaddr_tomusl(const struct sockaddr *lwip, struct musl_sockaddr *std)
    {
        if (std && lwip)
        {
            std->sa_family = (uint16_t) lwip->sa_family;
            memcpy(std->sa_data, lwip->sa_data, sizeof(std->sa_data));
        }
    }
#endif

static void _crt_thread_entry(void *parameter)
{
    rt_thread_t tid;
    rt_size_t user_stack;

    tid = rt_thread_self();

    user_stack = (rt_size_t)tid->user_stack + tid->user_stack_size;
    user_stack &= ~7; /* align 8 */

#ifdef ARCH_MM_MMU
    arch_crt_start_umode(parameter, tid->user_entry, (void *)user_stack, (char *)tid->stack_addr + tid->stack_size);
#else
    set_user_context((void*)user_stack);
    arch_start_umode(parameter, tid->user_entry, ((struct rt_lwp *)tid->lwp)->data_entry, (void*)user_stack);
#endif /* ARCH_MM_MMU */
}

/**
 * @brief Terminates all threads in the current thread group.
 *
 * This system call ends execution for all threads within the same thread group,
 * releasing resources such as memory and file descriptors. It is typically used
 * in multithreaded environments to ensure a clean exit for the entire process.
 *
 * @param value The exit code to be returned to the parent process.
 * @return sysret_t: return value of the system call execution.
 */
sysret_t sys_exit_group(int value)
{
    sysret_t rc = 0;
    lwp_status_t lwp_status;
    struct rt_lwp *lwp = lwp_self();

    if (lwp)
    {
        lwp_status = LWP_CREATE_STAT_EXIT(value);
        lwp_exit(lwp, lwp_status);
    }
    else
    {
        LOG_E("Can't find matching process of current thread");
        rc = -EINVAL;
    }

    return rc;
}

/**
 * @brief Terminates the calling thread and exits the process.
 *
 * This system call ends the execution of the calling thread and the process
 * it belongs to.
 *
 * @param status The exit code to be returned to the parent process.
 *               A value of 0 typically indicates successful execution, while
 *               non-zero values indicate an error or specific exit condition.
 * @return sysret_t: return value of the system call execution.
 *
 * @note Unlike `sys_exit_group`, which terminates all threads in a thread group,
 *       `sys_exit` only terminates the calling thread and the process.
 */
sysret_t sys_exit(int status)
{
    sysret_t rc = 0;
    rt_thread_t tid;

    tid = rt_thread_self();
    if (tid && tid->lwp)
    {
        lwp_thread_exit(tid, status);
    }
    else
    {
        LOG_E("Can't find matching process of current thread");
        rc = -EINVAL;
    }

    return rc;
}

/**
 * @brief Reads data from a file descriptor into a buffer.
 *
 * This system call reads up to `nbyte` bytes of data from the file descriptor
 * specified by `fd` into the buffer pointed to by `buf`.
 *
 * @param fd The file descriptor to read from. This should be a valid file
 *           descriptor obtained through system calls like `open()` or `socket()`.
 * @param buf A pointer to the buffer where the read data will be stored. The buffer
 *            must have enough space to accommodate up to `nbyte` bytes.
 * @param nbyte The maximum number of bytes to read. If the file contains fewer
 *              bytes than `nbyte`, only the available bytes will be read.
 * @return The number of bytes actually read, which may be less than `nbyte` if fewer
 *         bytes are available or if the end of the file is reached. Returns `0` if
 *         the end of the file is encountered. On error, returns `errno`.
 * @warning Ensure the buffer `buf` has sufficient space to hold the requested number
 *          of bytes, as failing to do so may result in undefined behavior.
 */
ssize_t sys_read(int fd, void *buf, size_t nbyte)
{
#ifdef ARCH_MM_MMU
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (!nbyte)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }

    kmem = kmem_get(nbyte);
    if (!kmem)
    {
        return -ENOMEM;
    }

    ret = read(fd, kmem, nbyte);
    if (ret > 0)
    {
        if (ret != lwp_put_to_user(buf, kmem, ret))
            return -EFAULT;
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }
    ssize_t ret = read(fd, buf, nbyte);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Writes data from a buffer to a file descriptor.
 *
 * This system call writes up to `nbyte` bytes of data from the buffer pointed
 * to by `buf` to the file descriptor specified by `fd`.
 *
 * @param fd The file descriptor to write to. This should be a valid file
 *           descriptor obtained through system calls like `open()` or `socket()`.
 * @param buf A pointer to the buffer containing the data to be written. The
 *            buffer must remain valid and accessible for the duration of the
 *            write operation.
 * @param nbyte The number of bytes to write from the buffer. If the file descriptor
 *              refers to a device or a socket, the actual number of bytes written
 *              may be less than `nbyte`.
 * @return The number of bytes actually written. This may be less than `nbyte` if
 *         the underlying resource cannot accept more data at the moment. On error,
 *         returns `errno`.
 *
 * @warning Ensure the buffer `buf` contains at least `nbyte` valid bytes to
 *          avoid undefined behavior. Additionally, verify that `fd` is writable
 *          to prevent errors.
 *
 * @see sys_read(), write()
 */
ssize_t sys_write(int fd, const void *buf, size_t nbyte)
{
#ifdef ARCH_MM_MMU
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (nbyte)
    {
        if (!lwp_user_accessable((void *)buf, nbyte))
        {
            return -EFAULT;
        }

        kmem = kmem_get(nbyte);
        if (!kmem)
        {
            return -ENOMEM;
        }

        lwp_get_from_user(kmem, (void *)buf, nbyte);
    }

    ret = write(fd, kmem, nbyte);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }
    ssize_t ret = write(fd, buf, nbyte);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Repositions the file offset of the open file descriptor.
 *
 * This system call sets the file offset for the open file descriptor `fd`
 * to a new position based on the `offset` and `whence` parameters. It is used
 * for seeking within files, enabling random access to file content.
 *
 * @param fd The file descriptor whose offset is to be modified. The descriptor
 *           must refer to a file capable of seeking (e.g., regular files, but
 *           not pipes or sockets).
 * @param offset The new offset value relative to the position specified by `whence`.
 *               Can be a positive or negative value, depending on the seek direction.
 * @param whence The reference point for the new offset. Must be one of the following:
 *               - `SEEK_SET`: Set the offset to `offset` bytes from the beginning of the file.
 *               - `SEEK_CUR`: Set the offset to its current position plus `offset`.
 *               - `SEEK_END`: Set the offset to the size of the file plus `offset`.
 * @return On success, returns the resulting offset location as measured in bytes
 *         from the beginning of the file. On failure, returns `errno`.
 *
 * @warning Ensure the file descriptor `fd` supports seeking. Using this function
 *          on non-seekable file descriptors (e.g., pipes or sockets) will result in an error.
 *
 * @see sys_read(), sys_write(), lseek()
 */
size_t sys_lseek(int fd, size_t offset, int whence)
{
    ssize_t ret = lseek(fd, offset, whence);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Opens or creates a file, returning a file descriptor.
 *
 * This system call opens the file specified by `name` with the specified
 * access mode and flags. If the file does not exist and the `O_CREAT` flag
 * is provided, it will create the file with the specified mode.
 *
 * @param name The path to the file to be opened. This can be an absolute or
 *             relative path.
 * @param flag Flags controlling how the file is opened. Common values include:
 *             - `O_RDONLY`: Open the file for read-only access.
 *             - `O_WRONLY`: Open the file for write-only access.
 *             - `O_RDWR`: Open the file for both reading and writing.
 *             - `O_CREAT`: Create the file if it does not exist (requires a mode argument).
 *             - `O_TRUNC`: Truncate the file to zero length if it exists.
 *             - `O_APPEND`: Open the file in append mode.
 * @param ... Optional. If the `O_CREAT` flag is specified, an additional
 *            `mode_t` argument must be provided, defining the file permissions
 *            (e.g., `0644` for user-read/write and group/world-read).
 * @return On success, returns the file descriptor.
 *         On failure, returns `errno`.
 *
 * @note The file descriptor returned can be used with other system calls like
 *       `sys_read()`, `sys_write()`, and `sys_close()`.
 *
 * @warning When using the `O_CREAT` flag, ensure to provide the `mode` argument
 *          to avoid undefined behavior. Additionally, verify that the process
 *          has the necessary permissions to access or create the file.
 *
 * @see sys_close(), sys_read(), sys_write(), open()
 */
sysret_t sys_open(const char *name, int flag, ...)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;
    mode_t mode = 0;

    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(name);
    if (!len)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    if ((flag & O_CREAT) || (flag & O_TMPFILE) == O_TMPFILE)
    {
        va_list ap;
        va_start(ap, flag);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return -EINVAL;
    }

    ret = open(kname, flag, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);

    return ret;
#else
    int ret;
    mode_t mode = 0;

    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }

    if ((flag & O_CREAT) || (flag & O_TMPFILE) == O_TMPFILE)
    {
        va_list ap;
        va_start(ap, flag);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    ret = open(name, flag, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Opens or creates a file relative to a directory file descriptor.
 *
 * This system call opens the file specified by `name`, relative to the directory
 * indicated by `dirfd`, with the specified flags and mode. It provides more
 * flexibility than `sys_open` for handling files in specific directory contexts.
 *
 * @param dirfd The file descriptor of the directory relative to which the file is opened.
 *              Special values include:
 *              - `AT_FDCWD`: Use the current working directory as the base.
 * @param name The path to the file to be opened. If `name` is absolute, `dirfd` is ignored.
 * @param flag Flags controlling how the file is opened. Common values include:
 *             - `O_RDONLY`: Open the file for read-only access.
 *             - `O_WRONLY`: Open the file for write-only access.
 *             - `O_RDWR`: Open the file for both reading and writing.
 *             - `O_CREAT`: Create the file if it does not exist.
 *             - `O_TRUNC`: Truncate the file to zero length if it exists.
 *             - `O_APPEND`: Open the file in append mode.
 *             - `O_EXCL`: Ensure the file is created exclusively (used with `O_CREAT`).
 * @param mode The permissions to set if the file is created (e.g., `0644` for user read/write
 *             and group/world read). This parameter is ignored unless `O_CREAT` is specified.
 * @return On success, returns the file descriptor.
 *         On failure, returns `errno`.
 *
 * @note The `sys_openat` system call is particularly useful for implementing secure
 *       directory traversal and operations, as it avoids race conditions when working
 *       with relative paths.
 *
 * @warning Ensure that `dirfd` is a valid directory file descriptor if a relative
 *          `name` is provided. Combining `O_CREAT` and `mode` requires proper handling
 *          to avoid unintended permission settings.
 *
 * @see sys_open(), sys_read(), sys_write(), sys_close()
 */
sysret_t sys_openat(int dirfd, const char *name, int flag, mode_t mode)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = openat(dirfd, kname, flag, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);

    return ret;
#else
    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }
    int ret = openat(dirfd, name, flag, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Closes a file descriptor.
 *
 * This system call closes the file descriptor specified by `fd`, releasing any
 * resources associated with it. Once closed, the file descriptor can no longer
 * be used for operations such as reading or writing, and it may be reassigned
 * by subsequent calls to functions like `sys_open()`.
 *
 * @param fd The file descriptor to be closed. This must be a valid open file descriptor.
 * @return On success, returns 0. On failure, returns `errno`.
 *
 * @note Closing a file descriptor that is already closed results in an error.
 *       Additionally, if the file descriptor refers to a file or resource shared
 *       among multiple processes or threads, only the reference count is decremented,
 *       and the resource itself is not released until all references are closed.
 *
 * @warning Always ensure `fd` is valid before calling this function. Attempting
 *          to close an invalid or already closed descriptor may lead to undefined
 *          behavior or errors.
 *
 * @see sys_open(), sys_read(), sys_write(), close()
 */
sysret_t sys_close(int fd)
{
    int ret = close(fd);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Performs control operations on a file descriptor.
 *
 * This system call allows a program to manipulate the behavior of a device or file
 * associated with the file descriptor `fd` by issuing a control command (`cmd`).
 * The function provides an interface to interact with device drivers, such as modifying
 * the settings of a device or performing custom operations.
 *
 * @param fd The file descriptor representing the device or file on which the ioctl
 *           command will be performed. This should be a valid, open file descriptor.
 * @param cmd The control command to be executed. The exact behavior depends on the
 *            device and the command. Commands are usually defined by the device driver
 *            or the kernel and can vary widely.
 * @param data A pointer to a buffer used for passing data to and from the command.
 *             The contents of the buffer depend on the specific command. For input
 *             commands, it may contain the data to be written to the device. For output
 *             commands, it may hold the data returned by the device.
 * @return On success, returns 0. On failure, returns `errno`.
 *
 * @note The actual functionality of `sys_ioctl` depends heavily on the specific `cmd`
 *       and the type of device associated with the file descriptor `fd`. Each device
 *       may have a different set of valid ioctl commands.
 *
 * @warning Ensure that `fd` refers to a valid file descriptor for a device that supports
 *          ioctl commands. Providing an invalid command or using an unsupported device
 *          may lead to undefined behavior or errors.
 *
 * @see sys_open(), sys_read(), sys_write(), ioctl()
 */
sysret_t sys_ioctl(int fd, unsigned long cmd, void* data)
{
    int ret = ioctl(fd, cmd, data);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Retrieves information about a file associated with a file descriptor.
 *
 * This system call retrieves the status information about the file referred to
 * by the file descriptor `file` and stores it in the structure pointed to by `buf`.
 * It is typically used to obtain metadata such as file size, permissions, type,
 * and timestamps.
 *
 * @param file The file descriptor referring to an open file. It must be a valid file
 *             descriptor returned by `sys_open()` or similar system calls.
 * @param buf A pointer to a `struct stat` that will be populated with the file's
 *            status information, including attributes like size, access times,
 *            permissions, and more.
 * @return On success, returns `0`. On failure, returns `errno` to indicate the error.
 *
 * @note The structure `struct stat` typically includes the following fields:
 *       - `st_size`: Size of the file in bytes.
 *       - `st_mode`: File type and permissions.
 *       - `st_mtime`: Last modification time.
 *       - `st_atime`: Last access time.
 *       - `st_ctime`: Time of last status change.
 *
 * @warning Ensure that `file` is a valid, open file descriptor. Invalid file
 *          descriptors or unsupported file types may lead to errors when using
 *          this function.
 *
 * @see sys_open(), sys_close(), stat(), fstat()
 */
sysret_t sys_fstat(int file, struct stat *buf)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }
    else
    {
        ret = fstat(file, &statbuff);

        if (ret == 0)
        {
            lwp_put_to_user(buf, &statbuff, sizeof statbuff);
        }
        else
        {
            ret = GET_ERRNO();
        }

        return ret;
    }
#else
    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }
    int ret = fstat(file, buf);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Monitors multiple file descriptors to see if they are ready for I/O.
 *
 * This system call monitors the file descriptors specified in `fds` for any
 * I/O events such as readiness for reading, writing, or exceptional conditions.
 * It waits up to the specified timeout and returns with information about which
 * file descriptors are ready for the requested operations.
 *
 * @param fds An array of `struct pollfd` structures, each specifying a file descriptor
 *            to be monitored and the events to be checked for. On return, each structure
 *            will contain the result of the poll operation for that file descriptor.
 * @param nfds The number of elements in the `fds` array.
 * @param timeout The maximum time (in milliseconds) to wait for events. If `timeout`
 *                is `-1`, the call will block indefinitely. If `timeout` is `0`,
 *                the call will return immediately.
 * @return On success, returns the number of file descriptors with events that are ready,
 *         or `0` if the timeout expired with no events. On error, returns `-1` and sets `errno`.
 *
 * @note The `pollfd` structure used for each file descriptor contains the following fields:
 *       - `fd`: The file descriptor to be monitored.
 *       - `events`: The events to monitor (e.g., `POLLIN`, `POLLOUT`).
 *       - `revents`: The events that actually occurred.
 *
 * @warning Ensure that `fds` contains valid file descriptors. Invalid descriptors or
 *          unsupported types (such as sockets) may result in errors. Also, be mindful
 *          of the timeout behavior - passing `0` will cause an immediate return, and passing
 *          `-1` will block indefinitely.
 *
 * @see sys_select(), poll(), select()
 */
sysret_t sys_poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int ret = -1;
#ifdef ARCH_MM_MMU
    struct pollfd *kfds = RT_NULL;

    if (!lwp_user_accessable((void *)fds, nfds * sizeof *fds))
    {
        return -EFAULT;
    }

    kfds = (struct pollfd *)kmem_get(nfds * sizeof *kfds);
    if (!kfds)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kfds, fds, nfds * sizeof *kfds);

    ret = poll(kfds, nfds, timeout);
    if (ret > 0)
    {
        lwp_put_to_user(fds, kfds, nfds * sizeof *kfds);
    }

    kmem_put(kfds);
    return ret;
#else
    if (!lwp_user_accessable((void *)fds, nfds * sizeof *fds))
    {
        return -EFAULT;
    }
    ret = poll(fds, nfds, timeout);
    return ret;
#endif /* ARCH_MM_MMU */
}

/**
 * @brief Monitors multiple file descriptors for readiness to perform I/O operations.
 *
 * This system call allows a program to monitor multiple file descriptors to see if
 * they are ready for reading, writing, or have exceptional conditions. It waits
 * for one or more of the file descriptors to become ready or for the specified
 * timeout to expire.
 *
 * @param nfds The highest-numbered file descriptor in any of the sets, plus one.
 *             This is the number of file descriptors to monitor.
 * @param readfds A pointer to an `fd_set` structure specifying the file descriptors
 *                to be checked for readability. If a file descriptor is ready to
 *                read, it will be set in the returned `fd_set`.
 * @param writefds A pointer to an `fd_set` structure specifying the file descriptors
 *                 to be checked for writability. If a file descriptor is ready to
 *                 write, it will be set in the returned `fd_set`.
 * @param exceptfds A pointer to an `fd_set` structure specifying the file descriptors
 *                  to be checked for exceptional conditions (e.g., out-of-band data).
 *                  If a file descriptor has exceptional conditions, it will be set in
 *                  the returned `fd_set`.
 * @param timeout A pointer to a `struct timeval` that specifies the maximum time
 *                to wait for an event. If `NULL`, the call blocks indefinitely. If
 *                `timeout` is `0`, the call will return immediately.
 * @return On success, returns the number of file descriptors that are ready for
 *         the requested operations, or `0` if the timeout expired without any events.
 *         On error, returns `-1` and sets `errno`.
 *
 * @note The `fd_set` structures should be initialized using the `FD_ZERO` macro
 *       and populated using the `FD_SET` macro. After the call, the `fd_set` structures
 *       will contain the file descriptors that are ready for the requested operations.
 *
 * @warning Ensure that the `fd_set` structures are properly initialized and that
 *          `nfds` correctly reflects the number of file descriptors to monitor.
 *          Passing invalid file descriptors or incorrect `nfds` can lead to undefined behavior.
 *
 * @see sys_poll(), sys_read(), sys_write(), poll(), select()
 */
sysret_t sys_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    fd_set *kreadfds = RT_NULL, *kwritefds = RT_NULL, *kexceptfds = RT_NULL;

    if (readfds)
    {
        if (!lwp_user_accessable((void *)readfds, sizeof *readfds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kreadfds = (fd_set *)kmem_get(sizeof *kreadfds);
        if (!kreadfds)
        {
            SET_ERRNO(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kreadfds, readfds, sizeof *kreadfds);
    }
    if (writefds)
    {
        if (!lwp_user_accessable((void *)writefds, sizeof *writefds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kwritefds = (fd_set *)kmem_get(sizeof *kwritefds);
        if (!kwritefds)
        {
            SET_ERRNO(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kwritefds, writefds, sizeof *kwritefds);
    }
    if (exceptfds)
    {
        if (!lwp_user_accessable((void *)exceptfds, sizeof *exceptfds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kexceptfds = (fd_set *)kmem_get(sizeof *kexceptfds);
        if (!kexceptfds)
        {
            SET_ERRNO(EINVAL);
            goto quit;
        }
        lwp_get_from_user(kexceptfds, exceptfds, sizeof *kexceptfds);
    }

    ret = select(nfds, kreadfds, kwritefds, kexceptfds, timeout);
    if (kreadfds)
    {
        lwp_put_to_user(readfds, kreadfds, sizeof *kreadfds);
    }
    if (kwritefds)
    {
        lwp_put_to_user(writefds, kwritefds, sizeof *kwritefds);
    }
    if (kexceptfds)
    {
        lwp_put_to_user(exceptfds, kexceptfds, sizeof *kexceptfds);
    }
quit:
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    if (kreadfds)
    {
        kmem_put(kreadfds);
    }
    if (kwritefds)
    {
        kmem_put(kwritefds);
    }
    if (kexceptfds)
    {
        kmem_put(kexceptfds);
    }
    return ret;
#else
    int ret;

    if (!lwp_user_accessable((void *)readfds, sizeof *readfds))
    {
        return -EFAULT;
    }
    if (!lwp_user_accessable((void *)writefds, sizeof *writefds))
    {
        return -EFAULT;
    }
    if (!lwp_user_accessable((void *)exceptfds, sizeof *exceptfds))
    {
        return -EFAULT;
    }
    ret = select(nfds, readfds, writefds, exceptfds, timeout);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Removes a file or symbolic link from the filesystem.
 *
 * This system call deletes the file or symbolic link specified by `pathname`.
 * After the call, the file will be unlinked from the filesystem, meaning it will
 * no longer be accessible via its pathname. If the file is still open, it will
 * remain available to processes that have it open until all file descriptors are
 * closed. If the file is a regular file and has no other hard links, it will be
 * removed from the disk once all references to it are closed.
 *
 * @param pathname The path to the file or symbolic link to be removed. It can be
 *                 an absolute or relative path.
 * @return On success, returns `0`. On failure, returns `errno` to indicate
 *         the error.
 *
 * @note If the file is currently being used by a process (i.e., the file descriptor
 *       is still open), it will not be immediately removed from the disk. The actual
 *       removal occurs once the file is no longer in use. Symbolic links are removed
 *       as soon as the call is executed.
 *
 * @warning Ensure that the file or link to be removed exists and that the `pathname`
 *          is correctly specified. The operation will fail if the file is open and
 *          in use by other processes or if the pathname does not exist.
 *
 * @see sys_open(), sys_remove(), unlink()
 */
sysret_t sys_unlink(const char *pathname)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;

    len = lwp_user_strlen(pathname);
    if (!len)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kname, (void *)pathname, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return -EINVAL;
    }
    ret = unlink(kname);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);
    return ret;
#else
    int ret = 0;
    ret = unlink(pathname);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

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
        if(ret != 0)
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
 * @brief Replaces the current process with a new process.
 *
 * This system call loads a new program into the current process's address space,
 * replacing the current program with the one specified by `filename`. It passes the
 * arguments `argv` and environment variables `envp` to the new program. If the execution
 * is successful, the current process is completely replaced, and no code after the
 * `sys_exec` call is executed. If an error occurs, the system call returns, and the
 * current process continues executing.
 *
 * @param filename The path to the executable file to be run. This can be an absolute
 *                 or relative path.
 * @param argc The number of arguments passed to the new program. This includes the
 *             executable name itself as the first argument.
 * @param argv An array of strings (character pointers), where each string is an argument
 *             passed to the new program. The first element (`argv[0]`) is conventionally
 *             the name of the executable.
 * @param envp An array of strings representing the environment variables for the new
 *             process. The array is terminated by a `NULL` pointer.
 * @return This function does not return on success, as the current process is replaced.
 *         On failure, it returns error code to indicate the error.
 *
 * @note The new process inherits most of the attributes of the current process, such
 *       as file descriptors, unless explicitly modified. It is important that `argv`
 *       and `envp` are properly formatted, and the `filename` points to a valid executable.
 *
 * @warning If `filename` is invalid or not an executable, or if the arguments or
 *          environment variables are incorrectly set, the system call will fail and
 *          return `-1`. Ensure that the executable file is accessible and that `argv`
 *          and `envp` are properly constructed.
 *
 * @see execve(), execvp(), execv(), execle()
 */
sysret_t sys_exec(char *filename, int argc, char **argv, char **envp)
{
    int ret = 0;
    int len = 0;
    char *kfilename = RT_NULL;

    len = lwp_user_strlen(filename);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kfilename = (char *)kmem_get(len + 1);
    if (!kfilename)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kfilename, (void *)filename, len + 1) != (len + 1))
    {
        kmem_put(kfilename);
        return -EFAULT;
    }

    ret = lwp_execve(kfilename, 0, argc, argv, envp);

    kmem_put(kfilename);

    return ret;
}

/**
 * @brief Sends a signal to a process or a group of processes.
 *
 * This system call sends the signal specified by `signo` to the process or process group
 * identified by `pid`. If `pid` is positive, the signal is sent to the process with the
 * specified process ID. If `pid` is `0`, the signal is sent to all processes in the
 * same process group as the caller. If `pid` is `-1`, the signal is sent to all processes
 * except for the caller. If `pid` is less than `-1`, the signal is sent to all processes
 * in the process group with the process group ID equal to `-pid`.
 *
 * @param pid The process ID or process group ID to which the signal is to be sent.
 *            - A positive value sends the signal to the process with that ID.
 *            - `0` sends the signal to all processes in the same process group as the caller.
 *            - `-1` sends the signal to all processes except the caller.
 *            - A negative value sends the signal to all processes in the process group
 *              with the process group ID equal to `-pid`.
 * @param signo The signal to send. This is an integer value that specifies the signal
 *              type. Common signal values include:
 *              - `SIGTERM` (terminate process)
 *              - `SIGKILL` (force kill process)
 *              - `SIGSTOP` (suspend process)
 *              - `SIGCONT` (resume process)
 * @return On success, returns `0`. On failure, it returns error code to indicate the error.
 *
 * @note Signals are a mechanism for inter-process communication, allowing processes
 *       to send notifications or requests to other processes. The behavior of signals
 *       depends on the signal type and how the receiving process handles them.
 *
 * @warning The `signo` value must be a valid signal number. Passing an invalid signal
 *          number or an invalid `pid` may result in an error. Additionally, some signals
 *          (e.g., `SIGKILL`) cannot be caught or ignored by processes.
 *
 * @see signal(), killpg(), raise()
 */
sysret_t sys_kill(int pid, int signo)
{
    rt_err_t kret = 0;
    sysret_t sysret;
    struct rt_lwp *lwp = RT_NULL;

    /* handling the semantics of sys_kill */
    if (pid > 0)
    {
        /**
         * Brief: Match the pid and send signal to the lwp if found
         * Note: Critical Section
         * - pid tree (READ. since the lwp is fetch from the pid tree, it must stay there)
         */
        lwp_pid_lock_take();
        lwp = lwp_from_pid_raw_locked(pid);
        if (lwp)
        {
            lwp_ref_inc(lwp);
            lwp_pid_lock_release();
        }
        else
        {
            lwp_pid_lock_release();
            kret = -RT_ENOENT;
        }

        if (lwp)
        {
            kret = lwp_signal_kill(lwp, signo, SI_USER, 0);
            lwp_ref_dec(lwp);
        }
    }
    else if (pid < -1 || pid == 0)
    {
        pid_t pgid = 0;
        rt_processgroup_t group;

        if (pid == 0)
        {
            /**
             * sig shall be sent to all processes (excluding an unspecified set
             * of system processes) whose process group ID is equal to the process
             * group ID of the sender, and for which the process has permission to
             * send a signal.
             */
            pgid = lwp_pgid_get_byprocess(lwp_self());
        }
        else
        {
            /**
             * sig shall be sent to all processes (excluding an unspecified set
             * of system processes) whose process group ID is equal to the absolute
             * value of pid, and for which the process has permission to send a signal.
             */
            pgid = -pid;
        }

        group = lwp_pgrp_find(pgid);
        if (group != RT_NULL)
        {
            PGRP_LOCK(group);
            kret = lwp_pgrp_signal_kill(group, signo, SI_USER, 0);
            PGRP_UNLOCK(group);
        }
        else
        {
            kret = -ECHILD;
        }
    }
    else if (pid == -1)
    {
        /**
         * sig shall be sent to all processes (excluding an unspecified set
         * of system processes) for which the process has permission to send
         * that signal.
         */
        kret = lwp_signal_kill_all(signo, SI_USER, 0);
    }

    switch (kret)
    {
        case -RT_ENOENT:
        case -ECHILD:
            sysret = -ESRCH;
            break;
        case -RT_EINVAL:
            sysret = -EINVAL;
            break;
        case -RT_ENOSYS:
            sysret = -ENOSYS;
            break;

        /**
         * kill() never returns ENOMEM, so return normally to caller.
         * IEEE Std 1003.1-2017 says the kill() function is successful
         * if the process has permission to send sig to any of the
         * processes specified by pid.
         */
        case -RT_ENOMEM:
        default:
            sysret = 0;
    }
    return sysret;
}

/**
 * @brief Retrieves the process ID of the calling process.
 *
 * This system call returns the process ID (PID) of the calling process. The PID is a
 * unique identifier assigned by the operating system to each running process. It can
 * be used to refer to or manipulate the process in subsequent system calls.
 *
 * @return The PID of the calling process. On failure, returns `-1` and sets `errno`
 *         to indicate the error (although this function typically does not fail).
 *
 * @note The PID returned by this function is a positive integer, and it remains
 *       unique during the lifetime of the process. This value can be used to manage
 *       the process, including sending signals or querying process information.
 *
 * @warning This function does not take any arguments and is typically used when
 *          a process needs to obtain its own PID for management or logging purposes.
 *
 * @see getppid(), getuid(), getgid()
 */
sysret_t sys_getpid(void)
{
    return lwp_getpid();
}

/**
 * @brief Retrieves the parent process ID of the calling process.
 *
 * This system call returns the process ID (PID) of the parent process of the calling process.
 * The parent process is the process that created the calling process, typically through a
 * system call like `fork()`. This information can be useful for process management and
 * for determining the hierarchy of processes.
 *
 * @return The PID of the parent process. If the calling process has no parent (for example,
 *         the init process), it typically returns `1` as the PID of the system's "root" process.
 *         On failure, returns `-1` and sets `errno` to indicate the error (although this function
 *         typically does not fail).
 *
 * @note The `getppid()` function is commonly used when a process needs to know which
 *       process is responsible for it, or for managing relationships between parent and child processes.
 *
 * @warning This function does not take any arguments and is typically used when the
 *          process requires information about its parent. It should not be confused with `getpid()`,
 *          which retrieves the PID of the calling process itself.
 *
 * @see getpid(), getuid(), getgid()
 */
sysret_t sys_getppid(void)
{
    rt_lwp_t process;

    process = lwp_self();
    if (process->parent == RT_NULL)
    {
        LOG_E("%s: process %d has no parent process", __func__, lwp_to_pid(process));
        return 0;
    }
    else
    {
        return lwp_to_pid(process->parent);
    }
}

/**
 * @brief Retrieves the priority of a process or process group.
 *
 * This system call returns the priority of a process or a process group, depending on
 * the value of the `which` argument.
 *
 * @param which The entity for which the priority is being requested. Possible values include:
 *              - `PRIO_PROCESS`: Retrieves the priority of the process specified by `who`.
 *              - `PRIO_PGRP`: Retrieves the priority of the process group specified by `who`. (Currently not supported.)
 *              - `PRIO_USER`: Retrieves the priority of the user specified by `who` (the user ID). (Currently not supported.)
 * @param who The ID of the process, process group, or user. The meaning of this parameter
 *            depends on the value of `which`:
 *            - When `which` is `PRIO_PROCESS`, `who` is the process ID (PID) of the process.
 *            - When `which` is `PRIO_PGRP`(Currently not supported.), `who` is the process group ID (PGID).
 *            - When `which` is `PRIO_USER`(Currently not supported.), `who` is the user ID (UID) of the user whose
 *              priority is being queried.
 * @return On success, returns the priority value (a negative integer indicates a lower
 *         priority).
 *
 * @warning Ensure that `which` and `who` are correctly specified to avoid errors.
 *          Invalid values for `which` or `who` may result in an error, and the function
 *          will return `-1`.
 *
 * @see setpriority(), getpid(), getppid()
 */
sysret_t sys_getpriority(int which, id_t who)
{
    long prio = 0xff;

    if (which == PRIO_PROCESS)
    {
        struct rt_lwp *lwp = RT_NULL;

        lwp_pid_lock_take();
        lwp = lwp_from_pid_locked(who);

        if (lwp)
        {
            rt_thread_t thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
            prio = RT_SCHED_PRIV(thread).current_priority;
        }

        lwp_pid_lock_release();
    }

    return prio;
}

/**
 * @brief Sets the priority of a process, process group, or user.
 *
 * This system call sets the priority of a process, process group, or user, depending
 * on the value of the `which` argument. The priority is used by the operating system
 * for scheduling processes. Lower numerical values represent higher priority in many
 * systems, and the priority range may be system-specific.
 *
 * @param which The entity for which the priority is being set. Possible values include:
 *              - `PRIO_PROCESS`: Sets the priority of the process specified by `who`.
 *              - `PRIO_PGRP`: Sets the priority of the process group specified by `who`.(Currently not supported.)
 *              - `PRIO_USER`: Sets the priority of the user specified by `who` (the user ID).(Currently not supported.)
 * @param who The ID of the process, process group, or user for which the priority is being set.
 *            The meaning of this parameter depends on the value of `which`:
 *            - When `which` is `PRIO_PROCESS`, `who` is the process ID (PID) of the process.
 *            - When `which` is `PRIO_PGRP`(Currently not supported.)  , `who` is the process group ID (PGID).
 *            - When `which` is `PRIO_USER`(Currently not supported.)  , `who` is the user ID (UID) of the user whose priority
 *              is being set.
 * @param prio The priority value to set.
 * @return On success, returns `0`. On failure, returns `-1`.
 *
 * @note This function modifies the priority of the specified process, process group, or user.
 *       The priority value is system-specific and may vary based on the system's scheduling
 *       policies. Ensure that the specified priority is within the acceptable range.
 *
 * @warning Ensure that `which`, `who`, and `prio` are valid. Invalid values for these
 *          parameters can result in errors, and the system call will return `-1`.
 *
 * @see getpriority(), getpid(), getppid()
 */
sysret_t sys_setpriority(int which, id_t who, int prio)
{
    if (which == PRIO_PROCESS)
    {
        struct rt_lwp *lwp = RT_NULL;

        lwp_pid_lock_take();
        lwp = lwp_from_pid_locked(who);

        if (lwp && prio >= 0 && prio < RT_THREAD_PRIORITY_MAX)
        {
            rt_list_t *list;
            rt_thread_t thread;
            for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
            {
                thread = rt_list_entry(list, struct rt_thread, sibling);
                rt_thread_control(thread, RT_THREAD_CTRL_CHANGE_PRIORITY, &prio);
            }
            lwp_pid_lock_release();
            return 0;
        }
        else
        {
            lwp_pid_lock_release();
        }
    }

    return -1;
}

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
    if(mutex == RT_NULL)
        return RT_NULL;

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

#ifdef ARCH_MM_MMU
/**
 * @brief Adjusts the end of the data segment (heap) of the calling process.
 *
 * This system call changes the location of the program break, which defines the end of
 * the data segment (heap) of the calling process. It provides a unified interface for adjusting
 * the heap size. The `addr` parameter specifies the new location for the program break.
 *
 * @param addr The new program break location. If `addr` is `NULL`, the current program
 *             break is returned. If a valid address is provided, the program break will
 *             be adjusted to this address. The address must be page-aligned, and changes
 *             must stay within the process's allowed address space.
 *
 * @return On success, returns the new program break.
 *
 * @note This function is typically used to manage heap space in a process. The program
 *       break adjustment can impact memory allocations and deallocations in the heap.
 *
 * @warning The `addr` must be a valid address within the process's allocated memory
 *          space. Attempting to set an invalid program break address may result in
 *          undefined behavior or memory corruption.
 *
 * @see malloc(), free(), sys_sbrk()
 */
rt_base_t sys_brk(void *addr)
{
    return lwp_brk(addr);
}

/**
 * @brief Maps a file or device into memory.
 *
 * This system call implements the `mmap2` system call, which maps a file or device into memory.
 * It provides a way for processes to access file contents directly in memory, bypassing
 * the need for explicit read or write operations. This function supports advanced memory
 * mapping options such as shared or private mappings, specific protection flags, and
 * offset alignment.
 *
 * @param addr The starting address for the memory mapping. If `NULL`, the kernel chooses
 *             the address. If not `NULL`, the address must be page-aligned and meet
 *             platform-specific alignment constraints.
 * @param length The length of the memory mapping in bytes. This value is rounded up to
 *               the nearest page size.
 * @param prot The memory protection flags. Possible values include:
 *             - `PROT_READ`: Pages can be read.
 *             - `PROT_WRITE`: Pages can be written.
 *             - `PROT_EXEC`: Pages can be executed.
 *             - `PROT_NONE`: Pages cannot be accessed.
 *             These flags can be combined using bitwise OR (`|`).
 * @param flags Flags that determine the type and behavior of the mapping. Possible values include:
 *              - `MAP_SHARED`: Updates are visible to other processes that map this file.
 *              - `MAP_PRIVATE`: Updates are not visible to other processes and are not written to the file.
 *              - `MAP_FIXED`: Use the exact address specified in `addr`.
 *              - `MAP_ANONYMOUS`: The mapping is not backed by a file and uses zero-initialized memory.
 * @param fd The file descriptor of the file to map. If `MAP_ANONYMOUS` is set in `flags`,
 *           `fd` is ignored and should be set to `-1`.
 * @param pgoffset The offset in the file where the mapping starts, specified in pages (not bytes).
 *                 This allows finer-grained control over the starting point of the mapping.
 *
 * @return On success, returns a pointer to the mapped memory region.
 *
 * @warning Ensure that the combination of `addr`, `length`, `prot`, `flags`, and `fd` is valid.
 *          Improper use may lead to undefined behavior or memory access violations.
 *
 * @see mmap(), munmap(), msync()
 */
void *sys_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, size_t pgoffset)
{
    sysret_t rc = 0;
    long offset = 0;

    /* aligned for user addr */
    if ((rt_base_t)addr & ARCH_PAGE_MASK)
    {
        if (flags & MAP_FIXED)
            rc = -EINVAL;
        else
        {
            offset = (char *)addr - (char *)RT_ALIGN_DOWN((rt_base_t)addr, ARCH_PAGE_SIZE);
            length += offset;
            addr = (void *)RT_ALIGN_DOWN((rt_base_t)addr, ARCH_PAGE_SIZE);
        }
    }

    if (rc == 0)
    {
        /* fix parameter passing (both along have same effect) */
        if (fd == -1 || flags & MAP_ANONYMOUS)
        {
            fd = -1;
            /* MAP_SHARED has no effect and treated as nothing */
            flags &= ~MAP_SHARED;
            flags |= MAP_PRIVATE | MAP_ANONYMOUS;
        }
        rc = (sysret_t)lwp_mmap2(lwp_self(), addr, length, prot, flags, fd, pgoffset);
    }

    return rc < 0 ? (char *)rc : (char *)rc + offset;
}

/**
 * @brief Unmaps a memory region previously mapped with mmap or mmap2.
 *
 * This system call implements the `munmap` system call, which removes a mapping
 * for a region of memory that was previously created using `mmap` or `mmap2`.
 *
 * @param addr The starting address of the memory region to unmap. This address
 *             must be page-aligned and refer to a region previously mapped.
 * @param length The length of the memory region to unmap, in bytes. This value
 *               is rounded up to the nearest page size internally if needed.
 *
 * @return On success, returns `0`. On failure, returns error code.
 *
 * @warning
 * - Ensure the specified memory region corresponds to a valid, active mapping.
 *   Providing invalid parameters may result in undefined behavior.
 * - Unmapping a region that is still in use by another thread or process can
 *   cause concurrency issues or data corruption.
 *
 * @see mmap(), mmap2(), msync()
 */
sysret_t sys_munmap(void *addr, size_t length)
{
    return lwp_munmap(lwp_self(), addr, length);
}

/**
 * @brief Changes the size or location of an existing memory mapping.
 *
 * This system call implements the `mremap` system call, allowing the resizing
 * or relocation of a previously created memory mapping. It is typically used
 * to dynamically adjust memory allocation for mapped regions without unmapping
 * and remapping them explicitly.
 *
 * @param old_address The starting address of the existing memory mapping to be resized
 *                    or relocated. This must be the address returned by a previous
 *                    `mmap` or `mremap` call.
 * @param old_size The current size of the memory mapping, in bytes. It must match
 *                 the size of the original mapping.
 * @param new_size The new desired size of the memory mapping, in bytes. The size will
 *                 be rounded up to the nearest page size if necessary.
 * @param flags Options to control the behavior of the remapping. Possible values include:
 *              - `MREMAP_MAYMOVE`: Allows the kernel to move the mapping to a new
 *                address if the current region cannot be resized in place.
 *              - `MREMAP_FIXED`: Requires the mapping to be relocated to the
 *                specified `new_address`. This flag must be used with caution.
 * @param new_address If `MREMAP_FIXED` is set in `flags`, this specifies the address
 *                    for the new mapping. Otherwise, it is ignored.
 *
 * @return On success, returns a pointer to the resized or relocated memory mapping.
 *
 * @warning
 * - Ensure that the `old_address` and `old_size` correspond to a valid, existing mapping.
 *
 * @see mmap(), munmap(), msync()
 */
void *sys_mremap(void *old_address, size_t old_size,
             size_t new_size, int flags, void *new_address)
{
    return lwp_mremap(lwp_self(), old_address, old_size, new_size, flags, new_address);
}

sysret_t sys_madvise(void *addr, size_t len, int behav)
{
    return -ENOSYS;
}
#endif

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
sysret_t sys_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
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
                         rt_ubase_t  value,
                         rt_int32_t   timeout)
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
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
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
sysret_t sys_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
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
        lwp_put_to_user((void *)buffer, (void *)kbuffer, ret);

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
sysret_t sys_timer_create(clockid_t clockid, struct sigevent *restrict sevp, timer_t *restrict timerid)
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
            memset(&sevp_k, 0, sizeof(sevp_k));

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
            ret = -EINVAL;
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
                           const struct itimerspec *restrict new_value,
                           struct itimerspec *restrict old_value)
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

/**
 * @brief Creates a new thread.
 *
 * This system call creates a new thread within the calling process. The newly created
 * thread starts executing the function specified by the `arg` argument, which typically
 * contains the necessary arguments or function pointer for the thread's execution.
 *
 * @param[in] arg     An array of arguments that will be passed to the function executed
 *                    by the new thread. This can include function pointers, structures,
 *                    or any necessary data the thread will need to execute its work.
 *
 * @return rt_thread_t    Returns a handle to the newly created thread. If the thread
 *                        creation fails, `NULL` is returned.
 *
 * @warning Ensure that the system has sufficient resources to create a new thread.
 *          Thread creation failures can occur if system limits are exceeded or resources
 *          are unavailable.
 */
rt_thread_t sys_thread_create(void *arg[])
{
    void *user_stack = 0;
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    int tid = 0;

    lwp = rt_thread_self()->lwp;
    lwp_ref_inc(lwp);
#ifdef ARCH_MM_MMU
    user_stack = lwp_map_user(lwp, 0, (size_t)arg[3], 0);
    if (!user_stack)
    {
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        goto fail;
    }
    thread = rt_thread_create((const char *)arg[0],
            _crt_thread_entry,
            (void *)arg[2],
            ALLOC_KERNEL_STACK_SIZE,
            (rt_uint8_t)(size_t)arg[4],
            (rt_uint32_t)(rt_size_t)arg[5]);
    if (!thread)
    {
        goto fail;
    }

#ifdef RT_USING_SMP
    RT_SCHED_CTX(thread).bind_cpu = lwp->bind_cpu;
#endif
    thread->cleanup = lwp_cleanup;
    thread->user_entry = (void (*)(void *))arg[1];
    thread->user_stack = (void *)user_stack;
    thread->user_stack_size = (rt_size_t)arg[3];
#else
    rt_uint32_t kstack_size = (rt_uint32_t)arg[7];
    if (kstack_size < ALLOC_KERNEL_STACK_SIZE_MIN)
    {
        /* When kstack size is 0, the default size of the kernel stack is used */
        kstack_size = kstack_size ? ALLOC_KERNEL_STACK_SIZE_MIN : ALLOC_KERNEL_STACK_SIZE;
    }
    else if (kstack_size > ALLOC_KERNEL_STACK_SIZE_MAX)
    {
        kstack_size = ALLOC_KERNEL_STACK_SIZE_MAX;
    }

    user_stack  = (void *)arg[3];
    if ((!user_stack) || ((rt_uint32_t)arg[6] == RT_NULL))
    {
        goto fail;
    }

    if ((tid = lwp_tid_get()) == 0)
    {
        goto fail;
    }

    thread = rt_thread_create((const char *)arg[0], _crt_thread_entry, (void *)arg[2], kstack_size, (rt_uint8_t)(size_t)arg[5], (rt_uint32_t)arg[6]);
    if (!thread)
    {
        goto fail;
    }
    thread->cleanup = lwp_cleanup;
    thread->user_entry = (void (*)(void *))arg[1];
    thread->user_stack = (void *)user_stack;
    thread->user_stack_size = (uint32_t)arg[4];
    rt_memset(thread->user_stack, '#', thread->user_stack_size);
#endif /* ARCH_MM_MMU */

    thread->lwp = (void*)lwp;
    thread->tid = tid;
    lwp_tid_set_thread(tid, thread);

    if (lwp->debug)
    {
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
    }

    LWP_LOCK(lwp);
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(lwp);

    return thread;

fail:
    lwp_tid_put(tid);
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return RT_NULL;
}

#ifdef ARCH_MM_MMU

long _sys_clone(void *arg[])
{
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self = RT_NULL;
    int tid = 0;
    rt_err_t err;

    unsigned long flags = 0;
    void *user_stack = RT_NULL;
    int *new_tid = RT_NULL;
    void *tls = RT_NULL;
    /*
       musl call flags (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND
       | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS
       | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED);
       */

    /* check args */
    if (!lwp_user_accessable(arg, sizeof(void *[SYS_CLONE_ARGS_NR])))
    {
        return -EFAULT;
    }

    flags = (unsigned long)(size_t)arg[0];
    if ((flags & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
            != (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
    {
        return -EINVAL;
    }

    user_stack = arg[1];
    new_tid = (int *)arg[2];
    tls = (void *)arg[3];

    if ((flags & CLONE_PARENT_SETTID) == CLONE_PARENT_SETTID)
    {
        if (!lwp_user_accessable(new_tid, sizeof(int)))
        {
            return -EFAULT;
        }
    }

    self = rt_thread_self();
    lwp = self->lwp;
    lwp_ref_inc(lwp);
    if (!user_stack)
    {
        SET_ERRNO(EINVAL);
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    thread = rt_thread_create(self->parent.name,
            RT_NULL,
            RT_NULL,
            self->stack_size,
            RT_SCHED_PRIV(self).init_priority,
            RT_SCHED_PRIV(self).init_tick);
    if (!thread)
    {
        goto fail;
    }

#ifdef RT_USING_SMP
    RT_SCHED_CTX(self).bind_cpu = lwp->bind_cpu;
#endif
    thread->cleanup = lwp_cleanup;
    thread->user_entry = RT_NULL;
    thread->user_stack = RT_NULL;
    thread->user_stack_size = 0;
    thread->lwp = (void *)lwp;
    thread->tid = tid;

    if ((flags & CLONE_SETTLS) == CLONE_SETTLS)
    {
        thread->thread_idr = tls;
    }
    if ((flags & CLONE_PARENT_SETTID) == CLONE_PARENT_SETTID)
    {
        *new_tid = (int)(tid);
    }
    if ((flags & CLONE_CHILD_CLEARTID) == CLONE_CHILD_CLEARTID)
    {
        thread->clear_child_tid = (int *)arg[4];
    }

    if (lwp->debug)
    {
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
    }

    LWP_LOCK(lwp);
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(lwp);

    /* copy origin stack */
    lwp_memcpy(thread->stack_addr, self->stack_addr, thread->stack_size);
    lwp_tid_set_thread(tid, thread);
    arch_set_thread_context(arch_clone_exit,
            (void *)((char *)thread->stack_addr + thread->stack_size),
            user_stack, &thread->sp);
    /* new thread never reach there */
    rt_thread_startup(thread);
    return (long)tid;
fail:
    err = GET_ERRNO();
    RT_ASSERT(err < 0);

    lwp_tid_put(tid);
    if (thread)
    {
        rt_thread_delete(thread);
    }
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return (long)err;
}

/**
 * @brief Creates a new process or thread (clone).
 *
 * This system call creates a new process or thread by duplicating the calling process.
 * The new process/thread begins execution by calling the function specified in the
 * `arg[]` array, which typically contains the necessary arguments or function pointer.
 * It is used to implement process/thread creation in the system and is often a lower-level
 * operation in process management.
 *
 * @param[in] arg   An array of arguments passed to the new process or thread. This could
 *                  include function pointers, structures, or any necessary data the
 *                  new process/thread will need to execute its work.
 *
 * @return long     Returns a status code or the process/thread ID of the newly created
 *                  process/thread. On success, it may return a positive value (such as a
 *                  thread ID). On failure, a negative value indicating the error is returned.
 *
 * @warning Be cautious when using this function as improper management of process/thread
 *          creation can lead to resource exhaustion, deadlocks, or other synchronization issues.
 */
rt_weak long sys_clone(void *arg[])
{
    return _sys_clone(arg);
}

static void lwp_struct_copy(struct rt_lwp *dst, struct rt_lwp *src)
{
#ifdef ARCH_MM_MMU
    dst->end_heap = src->end_heap;
#endif
    dst->lwp_type = src->lwp_type;
    dst->text_entry = src->text_entry;
    dst->text_size = src->text_size;
    dst->data_entry = src->data_entry;
    dst->data_size = src->data_size;
    dst->args = src->args;
    dst->background = src->background;
    dst->tty = src->tty;

    /* terminal API */
    dst->term_ctrlterm = src->term_ctrlterm;

    rt_memcpy(dst->cmd, src->cmd, RT_NAME_MAX);
    if (src->exe_file)
    {
        if (dst->exe_file)
        {
            rt_free(dst->exe_file);
        }
        dst->exe_file = strndup(src->exe_file, DFS_PATH_MAX);
    }

    rt_memcpy(&dst->signal.sig_action, &src->signal.sig_action, sizeof(dst->signal.sig_action));
    rt_memcpy(&dst->signal.sig_action_mask, &src->signal.sig_action_mask, sizeof(dst->signal.sig_action_mask));
    rt_memcpy(&dst->signal.sig_action_nodefer, &src->signal.sig_action_nodefer, sizeof(dst->signal.sig_action_nodefer));
    rt_memcpy(&dst->signal.sig_action_onstack, &src->signal.sig_action_onstack, sizeof(dst->signal.sig_action_onstack));
    rt_memcpy(&dst->signal.sig_action_restart, &dst->signal.sig_action_restart, sizeof(dst->signal.sig_action_restart));
    rt_memcpy(&dst->signal.sig_action_siginfo, &dst->signal.sig_action_siginfo, sizeof(dst->signal.sig_action_siginfo));
    rt_memcpy(&dst->signal.sig_action_nocldstop, &dst->signal.sig_action_nocldstop, sizeof(dst->signal.sig_action_nocldstop));
    rt_memcpy(&dst->signal.sig_action_nocldwait, &dst->signal.sig_action_nocldwait, sizeof(dst->signal.sig_action_nocldwait));
    rt_strcpy(dst->working_directory, src->working_directory);
}

static int lwp_copy_files(struct rt_lwp *dst, struct rt_lwp *src)
{
    struct dfs_fdtable *dst_fdt;
    struct dfs_fdtable *src_fdt;

    src_fdt = &src->fdt;
    dst_fdt = &dst->fdt;
    /* init fds */
    dst_fdt->fds = rt_calloc(src_fdt->maxfd, sizeof(void *));
    if (dst_fdt->fds)
    {
        struct dfs_file *d_s;
        int i;

        dst_fdt->maxfd = src_fdt->maxfd;

        dfs_file_lock();
        /* dup files */
        for (i = 0; i < src_fdt->maxfd; i++)
        {
            d_s = fdt_get_file(src_fdt, i);
            if (d_s)
            {
                dst_fdt->fds[i] = d_s;
                d_s->ref_count++;
            }
        }
        dfs_file_unlock();
        return 0;
    }
    return -RT_ERROR;
}

sysret_t _sys_fork(void)
{
    int tid = 0;
    sysret_t falival = 0;
    struct rt_lwp *lwp = RT_NULL;
    struct rt_lwp *self_lwp = RT_NULL;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self_thread = RT_NULL;
    void *user_stack = RT_NULL;
    rt_processgroup_t group;

    /* new lwp */
    lwp = lwp_create(LWP_CREATE_FLAG_ALLOC_PID);
    if (!lwp)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* new tid */
    if ((tid = lwp_tid_get()) == 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* user space init */
    if (lwp_user_space_init(lwp, 1) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    self_lwp = lwp_self();

    /* copy address space of process from this proc to forked one */
    if (lwp_fork_aspace(lwp, self_lwp) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* copy lwp struct data */
    lwp_struct_copy(lwp, self_lwp);

    /* copy files */
    if (lwp_copy_files(lwp, self_lwp) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* create thread */
    self_thread = rt_thread_self();

    thread = rt_thread_create(self_thread->parent.name,
            RT_NULL,
            RT_NULL,
            self_thread->stack_size,
            RT_SCHED_PRIV(self_thread).init_priority,
            RT_SCHED_PRIV(self_thread).init_tick);
    if (!thread)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    thread->cleanup = self_thread->cleanup;
    thread->user_entry = self_thread->user_entry;
    thread->user_stack = self_thread->user_stack;
    thread->user_stack_size = self_thread->user_stack_size;
    thread->signal.sigset_mask = self_thread->signal.sigset_mask;
    thread->thread_idr = self_thread->thread_idr;
    thread->clear_child_tid = self_thread->clear_child_tid;
    thread->lwp = (void *)lwp;
    thread->tid = tid;

    LWP_LOCK(self_lwp);
    /* add thread to lwp process */
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(self_lwp);

    lwp_children_register(self_lwp, lwp);

    /* set pgid and sid */
    group = lwp_pgrp_find(lwp_pgid_get_byprocess(self_lwp));
    if (group)
    {
        lwp_pgrp_insert(group, lwp);
    }
    else
    {
        LOG_W("the process group of pid: %d cannot be found", lwp_pgid_get_byprocess(self_lwp));
    }

    /* copy kernel stack context from self thread */
    lwp_memcpy(thread->stack_addr, self_thread->stack_addr, self_thread->stack_size);
    lwp_tid_set_thread(tid, thread);

    /* duplicate user objects */
    lwp_user_object_dup(lwp, self_lwp);

    user_stack = arch_get_user_sp();
    arch_set_thread_context(arch_fork_exit,
            (void *)((char *)thread->stack_addr + thread->stack_size),
            user_stack, &thread->sp);

    rt_thread_startup(thread);
    return lwp_to_pid(lwp);
fail:
    falival = GET_ERRNO();

    if (tid != 0)
    {
        lwp_tid_put(tid);
    }
    if (thread)
    {
        rt_thread_delete(thread);
    }
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return falival;
}

/* arm needs to wrap fork/clone call to preserved lr & caller saved regs */

/**
 * @brief Creates a child process by duplicating the calling process.
 *
 * This system call creates a new child process by duplicating the calling process. The
 * new child process is a copy of the parent process, except for the returned value.
 * The child process starts executing from the point of the fork, but the return value
 * differs between the parent and child: the parent receives the process ID (PID) of the
 * child, and the child receives a return value of 0.
 *
 * @return sysret_t    Returns a status code indicating the result of the operation:
 *                      - A positive value (the child's PID) is returned to the parent.
 *                      - A value of 0 is returned to the child process.
 *                      - A negative value indicates an error (e.g., resource limits exceeded).
 *
 * @note This function is commonly used in operating systems to create new processes.
 *
 * @warning Be aware that improper management of child processes (such as failing to handle
 *          process termination or excessive forking) can lead to resource exhaustion or
 *          other system issues. Ensure proper process handling in the parent and child
 *          processes to avoid leaks and inconsistencies.
 */
rt_weak sysret_t sys_fork(void)
{
    return _sys_fork();
}

rt_weak sysret_t sys_vfork(void)
{
    return sys_fork();
}

#define _swap_lwp_data(lwp_used, lwp_new, type, member) \
    do {\
        type tmp;\
        tmp = lwp_used->member;\
        lwp_used->member = lwp_new->member;\
        lwp_new->member = tmp;\
    } while (0)

/**
 * @brief Executes a program in the current process.
 *
 * This system call replaces the current process image with a new program specified by the
 * `path` argument. It loads the program located at the given `path` and passes the arguments
 * (`argv`) and environment variables (`envp`) to it. This effectively replaces the calling
 * process with a new one, and if successful, it never returns. If there is an error, the current
 * process continues to execute, and an error code is returned.
 *
 * @param[in]  path   The path to the executable file to be executed. This should be an
 *                    absolute or relative file path to the program.
 * @param[in]  argv   An array of arguments to pass to the new program. The first element
 *                    (`argv[0]`) should typically be the name of the program, and the array
 *                    should be terminated with a `NULL` pointer.
 * @param[in]  envp   An array of environment variables to pass to the new program. This is
 *                    typically in the form of `key=value` strings, with the array terminated
 *                    by a `NULL` pointer.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The program was successfully executed (this value is
 *                      never returned since the process is replaced).
 *                   - Other error codes may indicate issues with the program execution
 *
 * @note If `execve` is successful, it does not return to the calling function. The process
 *       image is replaced by the new program.
 */
sysret_t sys_execve(const char *path, char *const argv[], char *const envp[])
{
    rt_err_t error = -1;
    size_t len;
    struct rt_lwp *new_lwp = NULL;
    struct rt_lwp *lwp;
    int uni_thread;
    rt_thread_t thread;
    struct process_aux *aux;
    struct lwp_args_info args_info;
    char *kpath = RT_NULL;

    lwp = lwp_self();
    thread = rt_thread_self();
    uni_thread = 1;

    LWP_LOCK(lwp);
    if (lwp->t_grp.prev != &thread->sibling)
    {
        uni_thread = 0;
    }
    if (lwp->t_grp.next != &thread->sibling)
    {
        uni_thread = 0;
    }
    LWP_UNLOCK(lwp);

    if (!uni_thread)
    {
        return -EINVAL;
    }

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kpath = rt_malloc(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kpath, (void *)path, len) != len)
    {
        rt_free(kpath);
        return -EFAULT;
    }
    kpath[len] = '\0';

    if (access(kpath, X_OK) != 0)
    {
        error = rt_get_errno();
        rt_free(kpath);
        return (sysret_t)error;
    }

    /* setup args */
    error = lwp_args_init(&args_info);
    if (error)
    {
        rt_free(kpath);
        return -ENOMEM;
    }

    if (argv)
    {
        error = lwp_args_put_argv(&args_info, (void *)argv);
        if (error)
        {
            error = -EFAULT;
            goto quit;
        }
    }

    if (envp)
    {
        error = lwp_args_put_envp(&args_info, (void *)envp);
        if (error)
        {
            error = -EFAULT;
            goto quit;
        }
    }

    /* alloc new lwp to operation */
    new_lwp = lwp_create(LWP_CREATE_FLAG_NONE);
    if (!new_lwp)
    {
        error = -ENOMEM;
        goto quit;
    }

    error = lwp_user_space_init(new_lwp, 0);
    if (error != 0)
    {
        error = -ENOMEM;
        goto quit;
    }

    /* file is a script ? */
    path = kpath;
    while (1)
    {
        error = lwp_args_load_script(&args_info, path);
        if (error != 0)
        {
            break;
        }
        path = lwp_args_get_argv_0(&args_info);
    }

    /* now load elf */
    if ((aux = lwp_argscopy(new_lwp, &args_info)) == NULL)
    {
        error = -ENOMEM;
        goto quit;
    }
    error = lwp_load(path, new_lwp, RT_NULL, 0, aux);
    if (error == RT_EOK)
    {
        int off = 0;
        int last_backslash = 0;

        /* clear all user objects */
        lwp_user_object_clear(lwp);

        /* find last \ or / to get base name */
        while (1)
        {
            char c = path[off++];

            if (c == '\0')
            {
                break;
            }
            if (c == '\\' || c == '/')
            {
                last_backslash = off;
            }
        }

        /**
         * Set thread name and swap the data of lwp and new_lwp.
         * Since no other threads can access the lwp field, it't uneccessary to
         * take a lock here
         */
        RT_ASSERT(rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling) == thread);

        strncpy(thread->parent.name, path + last_backslash, RT_NAME_MAX - 1);
        strncpy(lwp->cmd, new_lwp->cmd, RT_NAME_MAX);
        rt_free(lwp->exe_file);
        lwp->exe_file = strndup(new_lwp->exe_file, DFS_PATH_MAX);

#ifdef ARCH_MM_MMU
        _swap_lwp_data(lwp, new_lwp, struct rt_aspace *, aspace);

        _swap_lwp_data(lwp, new_lwp, size_t, end_heap);
#endif
        _swap_lwp_data(lwp, new_lwp, uint8_t, lwp_type);
        _swap_lwp_data(lwp, new_lwp, void *, text_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, text_size);
        _swap_lwp_data(lwp, new_lwp, void *, data_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, data_size);

        _swap_lwp_data(lwp, new_lwp, void *, args);

        lwp_thread_signal_detach(&thread->signal);
        rt_memset(&thread->signal.sigset_mask, 0, sizeof(thread->signal.sigset_mask));

        lwp_signal_detach(&lwp->signal);
        lwp_signal_init(&lwp->signal);

        /* to do: clsoe files with flag CLOEXEC, recy sub-thread */

        lwp_aspace_switch(thread);

        lwp_ref_dec(new_lwp);
        arch_start_umode(lwp->args,
                lwp->text_entry,
                (void*)USER_STACK_VEND,
                (char *)thread->stack_addr + thread->stack_size);
        /* never reach here */
    }
    error = -EINVAL;
quit:
    if (kpath)
    {
        rt_free(kpath);
    }
    lwp_args_detach(&args_info);
    if (new_lwp)
    {
        lwp_ref_dec(new_lwp);
    }
    return error;
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Deletes a thread.
 *
 * This system call is used to delete an existing thread. The specified thread is terminated,
 * and its resources are released. If the thread is currently running, it will be forcefully
 * terminated. The thread identifier (`thread`) refers to the thread that is to be deleted.
 *
 * @param[in] thread   The identifier of the thread to be deleted.
 *
 * @return sysret_t    Returns a status code:
 *                      - `SYSRET_OK`: The thread was successfully deleted.
 *                     - Other error codes may indicate additional failures.
 *
 * @note This function should be used carefully, as forcefully terminating a thread may
 *       lead to resource leaks or inconsistent state if the thread is performing critical
 *       operations at the time of termination.
 *
 * @warning Ensure that the thread being deleted has completed its necessary operations
 *          and that there are no outstanding resources or critical tasks before deleting
 *          it. Otherwise, it might lead to undefined behavior or resource leaks.
 */
sysret_t sys_thread_delete(rt_thread_t thread)
{
#ifdef ARCH_MM_MMU
    return rt_thread_delete(thread);
#else
    sysret_t ret = 0;

    if(thread->parent.type != RT_Object_Class_Thread)
    {
        ret = -EINVAL;
        goto __exit;
    }

    ret = rt_thread_delete(thread);

    if (rt_thread_self() == thread)
    {
        rt_schedule();
    }

__exit:
    return ret;
#endif
}

/**
 * @brief Starts a previously created thread.
 *
 * This system call is used to start a thread that was created but has not yet started running.
 * It initiates the thread's execution, allowing it to begin performing its assigned task.
 * The `thread` parameter refers to the thread that is to be started.
 *
 * @param[in] thread   The identifier of the thread to be started.
 *
 * @return sysret_t    Returns a status code:
 *                      - `0`: The thread was successfully started.
 *                      - Other error codes may indicate additional failures.
 *
 * @warning Ensure that the thread has been correctly initialized and is in a valid state
 *          before calling this function to avoid undefined behavior. Improper initialization
 *          could lead to issues such as the thread not running as expected.
 */
sysret_t sys_thread_startup(rt_thread_t thread)
{
    return rt_thread_startup(thread);
}

/**
 * @brief Retrieves the identifier of the current thread.
 *
 * This system call returns the thread identifier of the currently executing thread. It allows
 * a thread to obtain its own identifier, which can be useful for various thread management
 * tasks such as self-identification, logging, or checking the thread's status.
 *
 * @return rt_thread_t  The identifier of the current thread.
 *                      If no thread is currently executing, a null or invalid thread ID
 *                      might be returned depending on the system's implementation.
 *
 * @note This function is typically used when a thread needs to identify itself, especially
 *       in cases where thread management is performed dynamically or the thread identifier
 *       is required for synchronization or debugging purposes.
 *
 * @warning Be aware that in environments where there is no concept of threads or if the
 *          current context is not a thread (e.g., during interrupt handling or early system
 *          initialization), the return value might be invalid.
 */
rt_thread_t sys_thread_self(void)
{
    return rt_thread_self();
}

/* sys channel */

/**
 * @brief Opens a communication channel.
 *
 * This system call is used to open a communication channel with a specified name and set of flags.
 * The channel allows for inter-process or inter-thread communication, depending on the underlying system.
 * The `name` parameter specifies the name of the channel, while the `flags` parameter allows
 * configuration of the channel's behavior (e.g., read/write permissions, blocking or non-blocking mode).
 *
 * @param[in] name   The name of the communication channel to be opened.
 * @param[in] flags  The flags to configure the behavior of the channel. These flags may
 *                   define various properties such as access mode (e.g., read-only, write-only)
 *                   or synchronization mode (e.g., blocking, non-blocking).
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The channel was successfully opened.
 *                    - Other error codes may indicate issues with the channel opening process.
 *
 * @warning Ensure that the correct flags are passed to configure the channel as required,
 *          as improper configuration might lead to access issues, data loss, or undefined behavior.
 */
sysret_t sys_channel_open(const char *name, int flags)
{
    rt_size_t ret = 0;
    char *kname = RT_NULL;
    int len = 0;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return -EFAULT;
    }

    ret = lwp_channel_open(FDT_TYPE_LWP, kname, flags);

    kmem_put(kname);

    return ret;
}

/**
 * @brief Closes an open communication channel.
 *
 * This system call is used to close an already open communication channel specified by the file descriptor `fd`.
 * After closing, the channel can no longer be used for communication, and any resources associated with
 * the channel will be released. This function is necessary for proper resource management, ensuring that
 * system resources (e.g., memory or file handles) are freed when no longer needed.
 *
 * @param[in] fd     The file descriptor of the communication channel to be closed.
 *
 * @return sysret_t  Returns a status code:
 *                    - `SYSRET_OK`: The channel was successfully closed.
 *                    - Other error codes may indicate issues with the channel closing process.
 *
 * @note This function should be called after communication is finished and the channel is no longer
 *       needed, to release any system resources associated with it.
 *
 * @warning Calling this function on an invalid or already closed file descriptor may lead to
 *          undefined behavior or errors. Ensure that the file descriptor is valid and that the
 *          channel is not already closed before attempting to close it.
 */
sysret_t sys_channel_close(int fd)
{
    return lwp_channel_close(FDT_TYPE_LWP, fd);
}

/**
 * @brief Sends a message through a communication channel.
 *
 * This system call is used to send a message through a specified communication channel identified
 * by the file descriptor `fd`. The message to be sent is provided in the `data` parameter.
 * It allows inter-process or inter-thread communication by transmitting the given message over
 * the open channel.
 *
 * @param[in] fd     The file descriptor of the communication channel to send the message to.
 * @param[in] data   The message data to be sent. This parameter is typically a structure
 *                   containing the message content and metadata.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The message was successfully sent.
 *                    - Other error codes may indicate issues with the message sending process.
 *
 * @note Ensure the channel is open and properly configured for sending messages before
 *       calling this function. Additionally, confirm that the `data` structure is valid and
 *       initialized with the appropriate content.
 *
 * @warning Failure to verify the channel's readiness or the validity of the data may lead
 *          to errors, data loss, or undefined behavior.
 */
sysret_t sys_channel_send(int fd, rt_channel_msg_t data)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
        return -ENOMEM;

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*kdata))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    ret = lwp_channel_send(FDT_TYPE_LWP, fd, kdata);

    kmem_put(kdata);

    return ret;
}

/**
 * @brief Sends a message through a communication channel and waits for a response with a timeout.
 *
 * This system call sends a message (`data`) through a specified communication channel identified by the file descriptor `fd`.
 * It then waits for a response (`data_ret`) within the specified timeout period. This is a synchronous operation
 * commonly used in request-response communication patterns between processes or threads.
 *
 * @param[in]  fd        The file descriptor of the communication channel to send the message to.
 * @param[in]  data      The message data to be sent. This is typically a structure containing
 *                       the message content and metadata.
 * @param[out] data_ret  The buffer to store the response message received from the channel.
 * @param[in]  time      The timeout period (in milliseconds) to wait for the response.
 *                       If set to a negative value, the function will wait indefinitely.
 *
 * @return sysret_t      Returns a status code:
 *                        - `0`: The message was successfully sent, and a response was received.
 *                        - Other error codes may indicate issues with the communication process.
 *
 * @note This function combines sending and receiving operations into a single atomic action.
 *       It is useful for scenarios requiring synchronous communication with a defined timeout
 *       to handle cases where a response may not be immediately available.
 *
 * @warning Ensure that the channel is open and properly configured for bidirectional communication.
 *          Verify that the `data` structure is valid and initialized, and the `data_ret` buffer is large
 *          enough to store the expected response to avoid memory issues or data corruption.
 */
sysret_t sys_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;
    rt_channel_msg_t kdata_ret = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
        return -ENOMEM;

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*kdata))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    kdata_ret = kmem_get(sizeof(*data_ret));
    if (kdata_ret == RT_NULL)
        return -ENOMEM;

    ret = lwp_channel_send_recv_timeout(FDT_TYPE_LWP, fd, kdata, kdata_ret, time);

    lwp_put_to_user(data_ret, kdata_ret, sizeof(*kdata_ret));
    kmem_put(kdata);
    kmem_put(kdata_ret);

    return ret;
}

/**
 * @brief Sends a reply message through a communication channel.
 *
 * This system call is used to send a reply (`data`) through a communication channel identified
 * by the file descriptor `fd`. It is typically called in response to a received request
 * within a request-response communication pattern. The reply is sent to the requesting entity
 * through the same channel.
 *
 * @param[in] fd     The file descriptor of the communication channel to send the reply to.
 * @param[in] data   The reply message to be sent. This is typically a structure containing
 *                   the reply content and metadata.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The reply was successfully sent.
 *                    - Other error codes may indicate issues with the reply sending process.
 *
 * @note This function is usually called in a server or responder context, where a request
 *       is received, processed, and the result is sent back to the requester. Ensure that
 *       the channel is open and configured to send replies before calling this function.
 *
 * @warning Ensure the `data` structure is valid and properly initialized before sending.
 *          Sending invalid or corrupted data may lead to unexpected behavior or communication failures.
 */
sysret_t sys_channel_reply(int fd, rt_channel_msg_t data)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
        return -ENOMEM;

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*data))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    ret = lwp_channel_reply(FDT_TYPE_LWP, fd, kdata);

    kmem_put(kdata);

    return ret;
}

/**
 * @brief Receives a message from a communication channel with a timeout.
 *
 * This system call attempts to receive a message from a specified communication channel identified
 * by the file descriptor `fd`. The received message is stored in the `data` buffer. If no message
 * is available within the specified timeout period, the function returns with a timeout status.
 *
 * @param[in]  fd     The file descriptor of the communication channel to receive the message from.
 * @param[out] data   The buffer to store the received message. This parameter is typically a
 *                    structure containing the message content and metadata.
 * @param[in]  time   The timeout period (in milliseconds) to wait for a message.
 *                    A negative value indicates that the function will wait indefinitely.
 *
 * @return sysret_t   Returns a status code:
 *                     - `0`: A message was successfully received.
 *                     - `-ETIMEDOUT`: The operation timed out before a message was received.
 *                     - Other error codes may indicate issues with the message receiving process.
 *
 * @note This function is useful in scenarios where blocking indefinitely is not desirable,
 *       allowing the caller to specify a timeout for receiving messages. It is commonly
 *       used in event-driven or time-sensitive communication systems.
 *
 * @warning Ensure that the channel is open and configured for receiving messages before calling
 *          this function. The `data` buffer must be valid and large enough to store the expected
 *          message to avoid memory corruption or data loss.
 */
sysret_t sys_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
        return -ENOMEM;

    ret = lwp_channel_recv_timeout(FDT_TYPE_LWP, fd, kdata, time);

    lwp_put_to_user(data, kdata, sizeof(*kdata));
    kmem_put(kdata);

    return ret;
}

static struct rt_semaphore critical_lock;

static int critical_init(void)
{
    rt_sem_init(&critical_lock, "ct_lock", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_DEVICE_EXPORT(critical_init);

/**
 * @brief Enters a critical section to prevent context switching or interrupts.
 *
 * @note Critical sections are typically used to protect shared resources or perform
 *       non-interruptible operations. Ensure to exit the critical section as soon as
 *       possible by calling `sys_exit_critical` to avoid system performance degradation
 *       or deadlocks.
 *
 * @warning Failure to exit a critical section (e.g., due to an exception or missing
 *          `sys_exit_critical` call) may lead to system instability or a complete halt.
 */
void sys_enter_critical(void)
{
    rt_sem_take(&critical_lock, RT_WAITING_FOREVER);
}

/**
 * @brief Exits a critical section and restores the system's previous state.
 *
 * @note Exiting the critical section as soon as the protected operation is completed
 *       is essential to avoid performance degradation or system deadlocks. Ensure
 *       that every call to `sys_enter_critical` is matched with a corresponding
 *       `sys_exit_critical` call.
 *
 * @warning Calling this function without a prior `sys_enter_critical` may result
 *          in undefined behavior or system instability. Use carefully in nested
 *          critical sections and ensure proper tracking of critical section depth
 *          if required.
 */
void sys_exit_critical(void)
{
    rt_sem_release(&critical_lock);
}

/* syscall: "sys_log" ret: "int" args: "const char*" "size" */
static int __sys_log_enable = 0;
static int sys_log_enable(int argc, char** argv)
{
    if (argc == 1)
    {
        rt_kprintf("sys_log = %d\n", __sys_log_enable);
        return 0;
    }
    else
    {
        __sys_log_enable = atoi(argv[1]);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(sys_log_enable, sys_log, sys_log 1(enable)/0(disable));

/**
 * @brief Logs a message to the system logging mechanism.
 *
 * This system call writes a log message to the system log for diagnostic or informational purposes.
 * The message is specified by the `log` parameter, and its size is given by the `size` parameter.
 * The logging mechanism is typically used for tracking system events, debugging, or reporting errors.
 *
 * @param[in] log   A pointer to the message to be logged. The message should be a valid character
 *                  array or string.
 * @param[in] size  The size of the log message in bytes. This specifies the number of bytes to write
 *                  from the `log` buffer.
 *
 * @return sysret_t Returns a status code:
 *                   - `0`: The log message was successfully written.
 *                   - Other error codes may indicate issues with the logging process.
 *
 * @note Ensure that the `log` pointer is valid and points to a properly initialized memory buffer.
 *       Truncation may occur if the logging system has a size limitation. Logging should not be used
 *       in performance-critical paths as it may introduce latency.
 *
 * @warning Passing a `NULL` pointer or an invalid `size` may lead to undefined behavior. Ensure the
 *          logging system is properly initialized before invoking this function.
 */
sysret_t sys_log(const char* log, int size)
{
    char *klog = RT_NULL;
    rt_device_t console = RT_NULL;

    if (!lwp_user_accessable((void *)log, size))
        return -EFAULT;

    klog = kmem_get(size);
    if (klog == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user((void *)klog, (void *)log, size) != size)
    {
        kmem_put(klog);
        return -EINVAL;
    }

    console = rt_console_get_device();

    if (console && __sys_log_enable)
    {
        rt_device_write(console, -1, klog, size);
    }

    kmem_put(klog);

    return 0;
}

/**
 * @brief Retrieves information about a file or directory.
 *
 * This system call obtains metadata about the specified file or directory and stores it in
 * the `buf` structure. The metadata includes attributes such as file size, permissions,
 * ownership, and timestamps.
 *
 * @param[in]  file  A pointer to the path of the file or directory to be queried.
 *                   The path should be a null-terminated string.
 * @param[out] buf   A pointer to a `struct stat` structure where the file's metadata
 *                   will be stored. This structure must be allocated by the caller.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The operation completed successfully, and the metadata
 *                      has been written to `buf`.
 *                    - Other error codes may indicate issues with the file path.
 *
 * @note The `file` path must be valid and accessible by the calling process. Ensure that
 *       the `buf` pointer points to a properly allocated memory region.
 *
 * @warning Passing a `NULL` pointer for `file` or `buf` may result in undefined behavior.
 *          Check all inputs before invoking this function to avoid potential issues.
 */
sysret_t sys_stat(const char *file, struct stat *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(stat(copy_path, &statbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}

/**
 * @brief Retrieves metadata about a file or symbolic link.
 *
 * This system call obtains metadata for the specified file or symbolic link and stores
 * it in the `buf` structure. Unlike `sys_stat`, if the specified path refers to a
 * symbolic link, this function retrieves information about the link itself, not the
 * target it points to.
 *
 * @param[in]  file  A pointer to the path of the file or symbolic link to be queried.
 *                   The path must be a null-terminated string.
 * @param[out] buf   A pointer to a `struct stat` structure where the metadata will be
 *                   stored. This structure must be allocated by the caller.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The operation completed successfully, and the metadata
 *                      has been written to `buf`.
 *                   - Other error codes may indicate issues with the file path.
 *
 * @note This function is particularly useful for handling symbolic links when you want
 *       to get information about the link itself rather than the target file or directory.
 *       The `file` path must be valid and accessible by the calling process.
 *
 * @warning Passing a `NULL` pointer for `file` or `buf` may result in undefined behavior.
 *          Always check inputs for validity before invoking this function.
 */
sysret_t sys_lstat(const char *file, struct stat *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';
#ifdef RT_USING_DFS_V2
    ret = _SYS_WRAP(dfs_file_lstat(copy_path, &statbuff));
#else
    ret = _SYS_WRAP(stat(copy_path, &statbuff));
#endif
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}

sysret_t sys_notimpl(void)
{
    return -ENOSYS;
}

uint32_t sys_hw_interrupt_disable(void)
{
    return rt_hw_interrupt_disable();
}

void sys_hw_interrupt_enable(uint32_t level)
{
    rt_hw_interrupt_enable(level);
}

#ifdef ARCH_MM_MMU
/**
 * @brief Allocates or retrieves a shared memory segment.
 *
 * This system call allocates a new shared memory segment or retrieves an existing one
 * based on the specified `key`. Shared memory allows processes to communicate by
 * sharing a region of memory.
 *
 * @param[in] key     A unique identifier for the shared memory segment. If `key` matches
 *                    an existing segment, it will be retrieved. If `create` is set and the
 *                    segment does not exist, a new one will be created.
 * @param[in] size    The size (in bytes) of the shared memory segment. If creating a new
 *                    segment, this specifies its size. If retrieving an existing segment,
 *                    `size` is ignored.
 * @param[in] create  A flag indicating whether to create the segment if it does not exist:
 *                    - `1`: Create the shared memory segment if it does not exist.
 *                    - `0`: Only retrieve an existing segment.
 *
 * @return sysret_t   Returns a status code:
 *                    - `0`: The shared memory segment was successfully created or
 *                      retrieved.
 *                    - Other error codes may indicate issues with the shared memory
 *
 * @note Shared memory segments identified by the same `key` are accessible across
 *       processes. Ensure proper synchronization mechanisms (e.g., semaphores) are in
 *       place to manage access to the shared memory.
 *
 * @warning Using a `NULL` or invalid `key` may result in undefined behavior. When creating
 *          a new segment, ensure that `size` is non-zero and meaningful.
 */
sysret_t sys_shmget(size_t key, size_t size, int create)
{
    return lwp_shmget(key, size, create);
}

/**
 * @brief Removes a shared memory segment.
 *
 * This system call removes the specified shared memory segment identified by its `id`.
 * Once removed, the segment will no longer be accessible, and any memory associated
 * with it will be freed. It is typically used to clean up shared memory resources
 * when they are no longer needed.
 *
 * @param[in] id  The identifier of the shared memory segment to be removed. This identifier
 *                was obtained when the segment was created or retrieved using `sys_shmget`.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The shared memory segment was successfully removed.
 *                    - Other error codes may indicate issues with the shared memory removal.
 *
 * @note This function should be called only when all processes that were using the shared
 *       memory segment have finished accessing it. Removing the segment while it is in use
 *       by another process may result in undefined behavior or memory corruption.
 *
 * @warning Ensure that the shared memory segment is no longer needed by any process before
 *          calling this function to avoid premature removal and potential data loss.
 */
sysret_t sys_shmrm(int id)
{
    return lwp_shmrm(id);
}

/**
 * @brief Attaches a shared memory segment to the calling process's address space.
 *
 * This system call maps a shared memory segment identified by `id` into the calling
 * process's address space. The segment can then be accessed using the returned virtual
 * address. If the segment was previously detached or created, it will be made available
 * for reading and writing.
 *
 * @param[in] id         The identifier of the shared memory segment to be attached.
 *                       This identifier was obtained when the segment was created
 *                       or retrieved using `sys_shmget`.
 * @param[in] shm_vaddr  A pointer to the desired virtual address where the shared
 *                       memory segment should be mapped. If `NULL`, the system will
 *                       choose an appropriate address.
 *
 * @return void*        Returns the virtual address where the shared memory segment
 *                      is mapped. On success, this will be the address in the
 *                      calling process's address space. If the attachment fails,
 *                      `NULL` is returned.
 *
 * @note Once the shared memory segment is attached, it can be accessed like any
 *       regular memory, but it should be used with caution, especially in multi-process
 *       environments. Ensure that proper synchronization mechanisms (e.g., semaphores)
 *       are used to manage concurrent access.
 *
 * @warning Ensure that the shared memory segment is properly allocated and not in use
 *          by other processes before attaching it. Passing invalid `id` or an inaccessible
 *          segment may result in undefined behavior.
 */
void* sys_shmat(int id, void* shm_vaddr)
{
    return lwp_shmat(id, shm_vaddr);
}

/**
 * @brief Detaches a shared memory segment from the calling process's address space.
 *
 * This system call detaches the shared memory segment previously attached to the calling
 * process's address space using `sys_shmat`. After calling this function, the shared
 * memory will no longer be accessible via the returned address.
 *
 * @param[in] shm_vaddr  A pointer to the virtual address where the shared memory
 *                       segment was previously mapped. This address was returned
 *                       by the `sys_shmat` function.
 *
 * @return sysret_t      Returns a status code:
 *                       - `0`: The shared memory segment was successfully detached.
 *                       - Other error codes may indicate issues with the detachment process.
 *
 * @note It is important to ensure that no processes are using the shared memory segment
 *       before detaching it. Detaching the segment while it is still being accessed
 *       may lead to undefined behavior.
 *
 * @warning Ensure that `shm_vaddr` corresponds to a valid attached address returned
 *          by `sys_shmat`. Passing an incorrect or uninitialized address may result
 *          in undefined behavior.
 */
sysret_t sys_shmdt(void* shm_vaddr)
{
    return lwp_shmdt(shm_vaddr);
}
#elif defined RT_LWP_USING_SHM

/**
 * @brief Allocates a new shared memory segment.
 *
 * This system call allocates a new shared memory segment of the specified size and
 * returns a pointer to the allocated memory. The allocated segment can be used for
 * inter-process communication or shared memory access. The segment is typically
 * managed by the system, and it can be accessed by other processes with appropriate
 * synchronization.
 *
 * @param[in] size  The size (in bytes) of the shared memory segment to be allocated.
 *
 * @return void*    Returns a pointer to the allocated shared memory segment.
 *                  If the allocation fails, `RT_NULL` is returned.
 *
 * @note The allocated shared memory segment can be used like regular memory,
 *       but it should be accessed with proper synchronization mechanisms (e.g.,
 *       semaphores or mutexes) to avoid race conditions or data corruption in
 *       multi-process environments.
 *
 * @warning Ensure that the `size` parameter is a valid, non-zero value, and that
 *          there is enough system memory to allocate the requested size.
 *          Failure to do so may result in errors or resource exhaustion.
 */
void *sys_shm_alloc(int size)
{
    if (size < 0)
    {
        return RT_NULL;
    }
    return lwp_shm_alloc((rt_size_t)size);
}

/**
 * @brief Retains an existing shared memory segment.
 *
 * This system call retains an existing shared memory segment that was previously
 * allocated or attached, ensuring it remains available for further use. It is
 * typically used to increment the reference count or to ensure the segment is
 * not removed or deallocated while it is still being used.
 *
 * @param[in] mem  A pointer to the shared memory segment to retain. This should be
 *                 the address previously returned by a memory allocation or
 *                 attachment function such as `sys_shmat` or `sys_shm_alloc`.
 *
 * @return void*   Returns the original pointer `mem` if the retention is successful.
 *                  If the operation fails, `NULL` is returned.
 *
 * @note This function does not affect the actual content of the shared memory segment,
 *       but ensures the segment is not removed or deallocated while still in use.
 *       It is generally used in conjunction with `sys_shmdt` or `sys_shmrm` to ensure
 *       proper resource management.
 *
 * @warning Ensure that the provided pointer `mem` corresponds to a valid shared
 *          memory segment that is currently allocated or attached. Passing an
 *          invalid or uninitialized pointer may result in undefined behavior.
 */
void *sys_shm_retain(void *mem)
{
    if (!lwp_user_accessable(mem, sizeof (void *)))
    {
        return RT_NULL;
    }
    return lwp_shm_retain(mem);
}

/**
 * @brief Frees a previously allocated shared memory segment.
 *
 * This system call frees a shared memory segment that was previously allocated or
 * retained using functions like `sys_shm_alloc` or `sys_shm_retain`. It ensures
 * that the shared memory is properly deallocated, making it available for future
 * allocations or for removal from the system.
 *
 * @param[in] mem  A pointer to the shared memory segment to be freed. This should be
 *                 the address returned by a memory allocation or retention function.
 *
 * @return sysret_t  Returns a status code:
 *                   - `0`: The shared memory segment was successfully freed.
 *                   - Other error codes may indicate issues with the memory deallocation.
 *
 * @note After calling this function, the memory will be deallocated, and any subsequent
 *       access to the freed memory will result in undefined behavior. Ensure that no
 *       processes are using the shared memory before calling this function.
 *
 * @warning Ensure that `mem` corresponds to a valid shared memory segment that was
 *          previously allocated or retained. Passing an invalid or already freed
 *          pointer may result in undefined behavior.
 */
sysret_t sys_shm_free(void *mem)
{
    if (!lwp_user_accessable(mem, sizeof (void *)))
    {
        return -EFAULT;
    }
    lwp_shm_free(mem);
    return 0;
}
#endif

/* device interfaces */

/**
 * @brief Initializes a device.
 *
 * This system call initializes the specified device, preparing it for use. Device initialization
 * typically involves setting up necessary hardware configurations, registering device drivers,
 * and ensuring that the device is in a ready state for further operations. This function should
 * be called before interacting with the device.
 *
 * @param[in] dev  A pointer to the device structure that represents the device to be initialized.
 *                 This structure contains device-specific configuration and state information.
 *
 * @return sysret_t  Returns a status code:
 *                   - `0`: The device was successfully initialized.
 *                   - Other error codes may indicate issues with the device initialization process.
 *
 * @note This function is typically called once during system startup or when a device is
 *       first accessed. It ensures that all necessary setup steps are completed before
 *       the device can be used.
 *
 * @warning Ensure that the device passed to this function is valid and properly configured
 *          before initialization. Initializing an invalid or improperly configured device
 *          may result in unpredictable behavior.
 */
sysret_t sys_device_init(rt_device_t dev)
{
    return rt_device_init(dev);
}

/**
 * @brief Registers a device with the system.
 *
 * This system call registers a device with the system, making it available for interaction
 * by the operating system or other components. Registration typically involves associating
 * the device with a name and setting up the necessary flags for the device's behavior.
 *
 * @param[in] dev     A pointer to the device structure that represents the device to be registered.
 *                    This structure contains the device's configuration, capabilities, and state.
 * @param[in] name    A string representing the name by which the device will be identified in the system.
 *                    This name is used for device lookup and reference.
 * @param[in] flags   A set of flags that configure the behavior of the device, such as enabling
 *                    or disabling certain features, or specifying the device's mode of operation.
 *
 * @return sysret_t   Returns a status code:
 *                    - `0`: The device was successfully registered.
 *                    - Other error codes may indicate issues with the device registration process.
 *
 * @note This function should be called after the device has been initialized (via `sys_device_init`)
 *       and before the device is used by the system or other components.
 *
 * @warning Ensure that the `name` provided is unique and not already in use by another device in the system.
 *          Passing invalid `dev` or `flags` may result in unexpected behavior or failure of device registration.
 */
sysret_t sys_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
    return rt_device_register(dev, name, flags);
}

/**
 * @brief Controls a device by sending a command.
 *
 * This system call sends a control command to the specified device, allowing the system or other
 * components to modify the device's behavior or state. The command is specified by the `cmd`
 * parameter, and the arguments for the command are passed via the `arg` parameter.
 *
 * @param[in] dev   A pointer to the device structure representing the device to be controlled.
 *                  The device must have been previously registered and initialized.
 * @param[in] cmd   The control command to be sent to the device. The meaning and behavior of the
 *                  command are device-specific and depend on the device type.
 * @param[in] arg   A pointer to the arguments required by the command. The type and content of
 *                  the arguments are determined by the command. Some commands may not require
 *                  arguments, in which case `arg` can be `NULL`.
 *
 * @return sysret_t Returns a status code:
 *                   - `0`: The command was successfully executed on the device.
 *                   - Other error codes may indicate issues with the command execution or device control.
 *
 * @note The set of available commands (`cmd`) and the expected argument types (`arg`) are specific
 *       to each device. Refer to the device documentation for the supported commands and argument
 *       formats.
 *
 * @warning Ensure that the `dev` pointer is valid and points to a correctly initialized device.
 *          Providing an invalid device or incorrect command may result in undefined behavior.
 */
sysret_t sys_device_control(rt_device_t dev, int cmd, void *arg)
{
    return rt_device_control(dev, cmd, arg);
}

/**
 * @brief Finds a device by its name.
 *
 * This system call searches for a device that has been registered with the system using the
 * specified name. If the device exists, a pointer to the device structure is returned,
 * allowing further interaction with the device. If no device with the specified name is found,
 * a `NULL` pointer is returned.
 *
 * @param[in] name  The name of the device to search for. This name must match the name used
 *                  during device registration (e.g., via `sys_device_register`).
 *
 * @return rt_device_t  Returns a pointer to the device structure if the device is found.
 *                      Returns `NULL` if no device with the specified name exists.
 *
 * @note The device must have been previously registered with the system using `sys_device_register`.
 *
 * @warning Ensure that the provided `name` is a valid string and corresponds to a registered device.
 *          Passing an invalid or non-registered name will result in `NULL` being returned.
 */
rt_device_t sys_device_find(const char* name)
{
    return rt_device_find(name);
}

/**
 * @brief Opens a device for use.
 *
 * This system call opens the specified device, making it ready for interaction with the system
 * or other components. The device must have been previously registered and initialized.
 * The `oflag` parameter specifies the open mode, which may determine how the device is accessed
 * (e.g., read, write, or exclusive access).
 *
 * @param[in] dev    A pointer to the device structure representing the device to be opened.
 *                   The device must be registered and initialized before being opened.
 * @param[in] oflag  The open flags that determine the mode of access to the device. These flags
 *                   may specify read, write, or other modes of operation, depending on the device's capabilities.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The device was successfully opened.
 *                    - Other error codes may indicate issues with the device opening process.
 *
 * @note The open flags (`oflag`) should be set according to the device's capabilities. For example,
 *       some devices may support read or write operations, while others may only support one of them.
 *       Check the device documentation for supported flags.
 *
 * @warning Ensure that the device pointer (`dev`) is valid and that the device has been initialized
 *          properly. Incorrect flags or attempting to open a device that is already in use may result
 *          in errors or undefined behavior.
 */
sysret_t sys_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return rt_device_open(dev, oflag);
}

/**
 * @brief Closes an open device.
 *
 * This system call closes an open device, releasing any resources or locks associated with it
 * and making it unavailable for further interaction until it is opened again. The device must
 * have been previously opened using `sys_device_open`. After calling this function, any further
 * attempts to interact with the device will result in an error unless the device is opened again.
 *
 * @param[in] dev  A pointer to the device structure representing the device to be closed.
 *                 The device must be open before it can be closed.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The device was successfully closed.
 *                    - Other error codes may indicate issues with the device closing process.
 *
 * @note This function should be called when the device is no longer needed or before shutting
 *       down the system to release device resources properly.
 *
 * @warning Ensure that the device has been opened before calling this function. Calling this function
 *          on an uninitialized or already closed device may result in undefined behavior or errors.
 */
sysret_t sys_device_close(rt_device_t dev)
{
    return rt_device_close(dev);
}

/**
 * @brief Reads data from an open device.
 *
 * This system call reads data from the specified device, starting at the given position and
 * storing the data in the provided buffer. The device must be open before this function can be called.
 * The amount of data to read is determined by the `size` parameter.
 *
 * @param[in]  dev     A pointer to the device structure representing the device to read from.
 *                     The device must be open and ready for reading.
 * @param[in]  pos     The position within the device from which to begin reading. For devices that
 *                     support seeking, this value is used to specify the starting point.
 * @param[out] buffer  A pointer to the buffer where the read data will be stored. This buffer should
 *                     be large enough to hold the specified amount of data.
 * @param[in]  size    The number of bytes to read from the device. This value determines how much
 *                     data is read into the buffer.
 *
 * @return rt_ssize_t  Returns the number of bytes actually read from the device:
 *                      - On success: The number of bytes read, which may be less than `size` if
 *                        the end of the device is reached or other factors limit the read.
 *                      - On failure: A negative error code.
 *
 * @note The device must be open and in a readable state before calling this function.
 *       The `pos` parameter allows seeking within the device if it supports such operations.
 *
 * @warning Ensure that the buffer provided is large enough to hold the data being read.
 *          Providing an insufficient buffer may result in undefined behavior.
 */
rt_ssize_t sys_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return rt_device_read(dev, pos, buffer, size);
}

/**
 * @brief Writes data to an open device.
 *
 * This system call writes data to the specified device, starting at the given position and using
 * the provided buffer. The device must be open and ready for writing. The amount of data to write
 * is determined by the `size` parameter.
 *
 * @param[in]  dev     A pointer to the device structure representing the device to write to.
 *                     The device must be open and ready for writing.
 * @param[in]  pos     The position within the device where the writing should start. For devices
 *                     that support seeking, this value specifies the location to begin writing.
 * @param[in]  buffer  A pointer to the buffer containing the data to be written to the device.
 *                     This buffer should contain the data to be written and should be large enough
 *                     to accommodate the specified size.
 * @param[in]  size    The number of bytes to write to the device. This value indicates how much
 *                     data should be written from the buffer to the device.
 *
 * @return rt_ssize_t  Returns the number of bytes actually written to the device:
 *                      - On success: The number of bytes written, which may be less than `size`
 *                        if there is an issue with the device or the data was truncated.
 *                      - On failure: A negative error code.
 *
 * @note The device must be open and in a writable state before calling this function.
 *       The `pos` parameter allows seeking within the device if it supports such operations.
 *
 * @warning Ensure that the buffer provided contains valid data and that it is large enough
 *          to fit the amount of data specified by `size`. Providing an insufficient buffer
 *          or invalid data may lead to undefined behavior.
 */
rt_ssize_t sys_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return rt_device_write(dev, pos, buffer, size);
}

#ifdef RT_USING_SAL
/* network interfaces */

/**
 * @brief Accepts a connection on a socket.
 *
 * This system call is used to accept a pending connection request on a socket. It extracts the
 * first connection request from the incoming queue, creates a new socket for the connection,
 * and stores the address information of the remote peer in the provided address structure.
 * The original socket must be a listening socket that has been previously bound and set to listen
 * for incoming connections.
 *
 * @param[in]  socket    The listening socket file descriptor that is waiting for incoming connections.
 *                       This socket must be in a listening state, created using `sys_socket` and
 *                       bound to an address using `sys_bind`.
 * @param[out] addr      A pointer to a `musl_sockaddr` structure where the address of the connecting
 *                       client will be stored. The structure is populated with information such as
 *                       the client's IP address and port number.
 * @param[in,out] addrlen A pointer to a socklen_t variable that specifies the size of the `addr`
 *                        structure on input. On output, it will contain the actual size of the
 *                        address returned in `addr`.
 *
 * @return sysret_t      Returns a socket descriptor for the new connection on success, or
 *                        `SYSRET_ERROR` on failure:
 *                        - On success: A new socket descriptor that can be used for further
 *                          communication with the connected peer.
 *                        - On failure: A negative error code indicating the reason for the failure.
 *
 * @note The socket passed as `socket` must be in a listening state and ready to accept incoming
 *       connections. The `addr` structure is populated with the client's address details, which can
 *       be used for further operations, such as identifying the client.
 *
 * @warning Ensure that the `addr` structure is sufficiently large to hold the address information.
 *          The `addrlen` parameter must be set to the size of the `musl_sockaddr` structure before
 *          calling this function. Calling the function with an incorrectly sized `addrlen` may lead
 *          to buffer overflows or undefined behavior.
 */
sysret_t sys_accept(int socket, struct musl_sockaddr *addr, socklen_t *addrlen)
{
    int ret = -1;
    struct sockaddr ksa;
    struct musl_sockaddr kmusladdr;
    socklen_t uaddrlen;
    socklen_t kaddrlen;

    if (addr)
    {
        if (!lwp_user_accessable(addrlen, sizeof(socklen_t)))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&uaddrlen, addrlen, sizeof(socklen_t));
        if (!uaddrlen)
        {
            return -EINVAL;
        }

        if (!lwp_user_accessable(addr, uaddrlen))
        {
            return -EFAULT;
        }
    }

    kaddrlen = sizeof(struct sockaddr);
    ret = accept(socket, &ksa, &kaddrlen);
    if (ret >= 0)
    {
        if (addr)
        {
            sockaddr_tomusl(&ksa, &kmusladdr);
            if (uaddrlen > sizeof(struct musl_sockaddr))
            {
                uaddrlen = sizeof(struct musl_sockaddr);
            }
            lwp_put_to_user(addr, &kmusladdr, uaddrlen);
            lwp_put_to_user(addrlen, &uaddrlen, sizeof(socklen_t));
        }
    }
    return ret;
}

/**
 * @brief Binds a socket to a local address.
 *
 * This system call binds a socket to a specific local address and port. The socket must be created
 * using `sys_socket` before it can be bound. The `bind` operation allows the application to associate
 * a socket with a specific address, such as an IP address and port number, which can then be used
 * for sending or receiving data.
 *
 * @param[in]  socket  The socket descriptor to which the address will be bound. This socket must
 *                     be created using `sys_socket` and should not already be bound to another address.
 * @param[in]  name    A pointer to a `musl_sockaddr` structure that contains the address to which
 *                     the socket will be bound. This can represent an IP address and port number.
 * @param[in]  namelen The size of the `musl_sockaddr` structure in bytes. This value should be set
 *                     to the actual size of the `name` structure before calling this function.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code on failure.
 *
 * @note The `socket` must be created before calling this function, and the address provided in `name`
 *       should be a valid local address for the socket. This operation is typically used for server-side
 *       sockets that listen for incoming connections or for any socket that needs to specify its local
 *       address before communication.
 *
 * @warning If the specified address is already in use by another socket or if the socket type is incompatible
 *          with the address, the function will return an error. Ensure that the address is not in use and is
 *          valid for the socket type.
 */
sysret_t sys_bind(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    rt_err_t ret = 0;
    struct sockaddr sa;
    struct sockaddr_un un_addr;
    struct musl_sockaddr kname;
    rt_uint16_t family = 0;

    if (!lwp_user_accessable((void *)name, namelen))
    {
        return -EFAULT;
    }

    lwp_get_from_user(&family, (void *)name, 2);
    if (family == AF_UNIX)
    {
        lwp_get_from_user(&un_addr, (void *)name, sizeof(struct sockaddr_un));
        ret = bind(socket, (struct sockaddr *)&un_addr, namelen);
    }
    else if (family == AF_NETLINK)
    {
        lwp_get_from_user(&sa, (void *)name, namelen);
        ret = bind(socket, &sa, namelen);
    }
    else
    {
        lwp_get_from_user(&kname, (void *)name, namelen);
        sockaddr_tolwip(&kname, &sa);
        ret = bind(socket, &sa, namelen);
    }

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Shuts down part of a full-duplex connection.
 *
 * This system call disables further send or receive operations on a socket. The `how` parameter
 * specifies which part of the connection should be shut down. This operation is typically used
 * when the application no longer needs to send or receive data, but wants to keep the connection open
 * for other purposes (e.g., receiving shutdown acknowledgment).
 *
 * @param[in]  socket  The socket descriptor to be shut down. This socket must be an open socket that
 *                     has been created using `sys_socket`.
 * @param[in]  how     The shutdown behavior:
 *                     - `SHUT_RD`: Disables further receives on the socket. The application can no longer
 *                       receive data from this socket.
 *                     - `SHUT_WR`: Disables further sends on the socket. The application can no longer
 *                       send data through this socket.
 *                     - `SHUT_RDWR`: Disables both sends and receives on the socket. The socket is
 *                       fully shut down for communication.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code (e.g., `SYSRET_ERROR`) on failure.
 *
 * @note The `socket` should be open and in a connected state when calling this function. The `how`
 *       parameter determines which part of the connection is to be shut down, allowing for finer control
 *       over communication termination.
 *
 * @warning Once a socket is shut down with `SHUT_RD`, no further data can be received on it. Similarly,
 *          after `SHUT_WR`, no more data can be sent. Calling `sys_shutdown` with incompatible `how` values
 *          or on an invalid socket may result in errors.
 */
sysret_t sys_shutdown(int socket, int how)
{
    return shutdown(socket, how);
}

/**
 * @brief Retrieves the address of the peer connected to a socket.
 *
 * This system call retrieves the address of the peer (remote endpoint) that is connected to the specified
 * socket. The socket must be connected (i.e., for stream-oriented protocols such as TCP). The address
 * of the peer is stored in the `name` structure, and the size of the structure is updated in `namelen`.
 *
 * @param[in]  socket    The socket descriptor of the connected socket. This socket must be in a connected
 *                       state (e.g., after a successful `sys_connect` or `sys_accept` call).
 * @param[out] name      A pointer to a `musl_sockaddr` structure where the address of the peer will be
 *                       stored. This structure will be populated with the peer's IP address and port number.
 * @param[in,out] namelen A pointer to a `socklen_t` variable that specifies the size of the `name` structure
 *                        on input. On output, it will contain the actual size of the address returned in `name`.
 *
 * @return sysret_t      Returns `SYSRET_OK` on success, or a negative error code on failure.
 *
 * @note The `socket` must be in a connected state when calling this function. The `name` structure will
 *       contain the peer's address information, which can be used for logging, debugging, or further
 *       communication.
 *
 * @warning Ensure that the `name` structure is sufficiently large to hold the peer's address information.
 *          The `namelen` parameter must be set to the size of the `name` structure before calling this function.
 *          Failing to provide a correctly sized `namelen` could result in buffer overflows or undefined behavior.
 */
sysret_t sys_getpeername(int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof(socklen_t)))
    {
        return -EFAULT;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof(socklen_t));
    if (!unamelen)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        return -EFAULT;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getpeername(socket, &sa, &knamelen);

    if (ret == 0)
    {
        sockaddr_tomusl(&sa, &kname);
        if (unamelen > sizeof(struct musl_sockaddr))
        {
            unamelen = sizeof(struct musl_sockaddr);
        }
        lwp_put_to_user(name, &kname, unamelen);
        lwp_put_to_user(namelen, &unamelen, sizeof(socklen_t));
    }
    else
    {
        ret = GET_ERRNO();
    }

    return ret;
}

/**
 * @brief Retrieves the local address of the socket.
 *
 * This system call retrieves the local address (local endpoint) that is bound to the specified socket.
 * The socket must be created and, if necessary, bound to a local address using `sys_bind`. The address
 * of the local endpoint is stored in the `name` structure, and the size of the structure is updated in `namelen`.
 *
 * @param[in]  socket    The socket descriptor of the socket. This socket must be created and, if required,
 *                       bound to a local address.
 * @param[out] name      A pointer to a `musl_sockaddr` structure where the local address of the socket will
 *                       be stored. This structure will be populated with the local IP address and port number.
 * @param[in,out] namelen A pointer to a `socklen_t` variable that specifies the size of the `name` structure
 *                        on input. On output, it will contain the actual size of the address returned in `name`.
 *
 * @return sysret_t      Returns `0` on success, or a negative error code on failure.
 *
 * @note The `socket` must be created and, if needed, bound to a local address using `sys_bind`.
 *       The `name` structure will contain the local address of the socket, which can be used for logging,
 *       debugging, or further communication.
 *
 * @warning Ensure that the `name` structure is sufficiently large to hold the local address information.
 *          The `namelen` parameter must be set to the size of the `name` structure before calling this function.
 *          Failing to provide a correctly sized `namelen` could result in buffer overflows or undefined behavior.
 */
sysret_t sys_getsockname(int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof (socklen_t)))
    {
        return -EFAULT;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof (socklen_t));
    if (!unamelen)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        return -EFAULT;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getsockname(socket, &sa, &knamelen);
    if (ret == 0)
    {
        sockaddr_tomusl(&sa, &kname);
        if (unamelen > sizeof(struct musl_sockaddr))
        {
            unamelen = sizeof(struct musl_sockaddr);
        }
        lwp_put_to_user(name, &kname, unamelen);
        lwp_put_to_user(namelen, &unamelen, sizeof(socklen_t));
    }
    else
    {
        ret = GET_ERRNO();
    }
    return ret;
}

/**
 * @brief Retrieves the value of a socket option.
 *
 * This system call retrieves the current value of a socket option for the specified socket. The socket
 * options allow fine-grained control over various aspects of socket behavior, such as timeouts, buffering,
 * and connection settings. The option value is stored in the `optval` buffer, and the size of the buffer
 * is specified by the `optlen` parameter.
 *
 * @param[in]  socket    The socket descriptor for which the option value is being retrieved. The socket
 *                       must be valid and open.
 * @param[in]  level     The level at which the option is defined. Typically, this is `SOL_SOCKET` for general
 *                       socket options, or a protocol-specific level (e.g., `IPPROTO_TCP` for TCP options).
 * @param[in]  optname   The option name. This specifies which socket option to retrieve (e.g., `SO_RCVBUF`
 *                       for receive buffer size or `SO_RCVBUF` for send buffer size).
 * @param[out] optval    A pointer to a buffer where the option value will be stored. The buffer's type depends
 *                       on the option being retrieved.
 * @param[in,out] optlen A pointer to a `socklen_t` variable that specifies the size of the `optval` buffer on
 *                       input. On output, it will contain the actual size of the option value retrieved.
 *
 * @return sysret_t      Returns `0` on success, or a negative error code on failure.
 *
 * @note The `socket` must be valid and open when calling this function. The `level` and `optname` parameters
 *       define the specific option to be retrieved. The `optval` buffer will contain the option value after
 *       the function call, and `optlen` will be updated to reflect the size of the retrieved value.
 *
 * @warning Ensure that the `optval` buffer is large enough to hold the value for the specified option.
 *          The `optlen` parameter must be set to the correct size of the buffer before calling this function.
 *          Failing to provide a correctly sized buffer could result in undefined behavior or buffer overflows.
 */
sysret_t sys_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    int ret = 0;
    socklen_t koptlen = 0;
    void *koptval = RT_NULL;

    if (!lwp_user_accessable((void *)optlen, sizeof(uint32_t)))
        return -EFAULT;

    if (lwp_get_from_user(&koptlen, optlen, sizeof(uint32_t)) != sizeof(uint32_t))
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)optval, koptlen))
        return -EFAULT;

    koptval = kmem_get(koptlen);
    if (koptval == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(koptval, optval, koptlen) != koptlen)
    {
        kmem_put(koptval);
        return -EINVAL;
    }

    convert_sockopt(&level, &optname);
    ret = getsockopt(socket, level, optname, koptval, &koptlen);

    lwp_put_to_user((void *)optval, koptval, koptlen);
    lwp_put_to_user((void *)optlen, &koptlen, sizeof(uint32_t));

    kmem_put(koptval);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Sets the value of a socket option.
 *
 * This system call sets a socket option for the specified socket. Socket options control various aspects
 * of socket behavior, such as timeouts, buffer sizes, or connection parameters. The option value is
 * provided in the `optval` buffer, and its length is specified by the `optlen` parameter.
 *
 * @param[in]  socket    The socket descriptor for which the option is being set. The socket must be valid and open.
 * @param[in]  level     The level at which the option is defined. This can be `SOL_SOCKET` for general socket options,
 *                       or a protocol-specific level (e.g., `IPPROTO_TCP` for TCP options).
 * @param[in]  optname   The option name. This specifies which socket option to set (e.g., `SO_RCVBUF` for receive buffer size).
 * @param[in]  optval    A pointer to the buffer that contains the option value to set. The format of this buffer depends
 *                       on the option being set.
 * @param[in]  optlen    The size of the `optval` buffer. This specifies the length of the data to be used when setting
 *                       the option value.
 *
 * @return sysret_t      Returns `0` on success, or a negative error code on failure:
 *
 * @note The `socket` must be valid and open. The `level` and `optname` parameters define the specific option to be set,
 *       and the `optval` buffer should contain the appropriate value for that option. The `optlen` parameter must
 *       match the size of the `optval` buffer.
 *
 * @warning Ensure that the `optval` buffer contains valid data for the specified option. The `optlen` parameter must be
 *          set to the correct size of the `optval` buffer before calling this function. Failing to provide a correctly
 *          sized buffer could result in undefined behavior or errors.
 */
sysret_t sys_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    int ret;
    void *koptval = RT_NULL;

    if (!lwp_user_accessable((void *)optval, optlen))
        return -EFAULT;

    koptval = kmem_get(optlen);
    if (koptval == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(koptval, (void *)optval, optlen) != optlen)
    {
        kmem_put(koptval);
        return -EINVAL;
    }

    convert_sockopt(&level, &optname);
    ret = setsockopt(socket, level, optname, koptval, optlen);

    kmem_put(koptval);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Establishes a connection to a remote socket.
 *
 * This system call attempts to establish a connection to a remote socket specified by the `name` parameter.
 * It is typically used for client-side socket operations to connect to a server. The connection is established
 * by using the specified socket descriptor and the address of the remote server.
 *
 * @param[in]  socket   The socket descriptor for the connection attempt. The socket must be valid and in a
 *                      `SOCK_STREAM` or `SOCK_DGRAM` state, depending on the protocol.
 * @param[in]  name     A pointer to a `sockaddr` structure containing the address of the remote host. This address
 *                      must include the correct IP address and port number for the connection.
 * @param[in]  namelen  The size of the `sockaddr` structure pointed to by `name`. This should match the size
 *                      of the address structure (e.g., `sizeof(struct sockaddr_in)` for IPv4).
 *
 * @return sysret_t     Returns `0` on success, or a negative error code on failure:
 *
 * @note This function may block if the connection is being established, depending on the socket's configuration.
 *       For non-blocking sockets, it will return immediately, even if the connection has not been established.
 *
 * @warning The `socket` must be of a valid type (e.g., `SOCK_STREAM` for TCP or `SOCK_DGRAM` for UDP).
 *          The `name` parameter must point to a valid `sockaddr` structure that contains a correctly formatted address.
 */
sysret_t sys_connect(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    int ret = 0;
    rt_uint16_t family = 0;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    struct sockaddr_un addr_un;

    if (!lwp_user_accessable((void *)name, namelen))
    {
        return -EFAULT;
    }

    lwp_get_from_user(&family, (void *)name, 2);
    if (family == AF_UNIX)
    {
        if (!lwp_user_accessable((void *)name, sizeof(struct sockaddr_un)))
        {
            return -EFAULT;
        }

        lwp_get_from_user(&addr_un, (void *)name, sizeof(struct sockaddr_un));
        ret = connect(socket, (struct sockaddr *)(&addr_un), namelen);
    }
    else
    {
        lwp_get_from_user(&kname, (void *)name, namelen);
        sockaddr_tolwip(&kname, &sa);
        ret = connect(socket, &sa, namelen);
    }

    return ret;
}

/**
 * @brief Prepares a socket to accept incoming connection requests.
 *
 * This system call marks a socket as a passive socket, indicating that it will be used to accept
 * incoming connection requests. It is typically used on server-side sockets after binding a
 * local address and port using `sys_bind()`.
 *
 * @param[in]  socket   The socket descriptor to be set up for listening. The socket must be valid
 *                      and of type `SOCK_STREAM` (for TCP connections).
 * @param[in]  backlog  The maximum number of pending connections that can be queued. This value
 *                      is system-dependent and may be limited to a lower maximum.
 *
 * @return sysret_t     Returns `0` on success, or a negative error code on failure.
 *
 * @note Before calling this function, the socket must be bound to a local address and port using
 *       `sys_bind()`. Only sockets of type `SOCK_STREAM` can be used for listening. The actual
 *       maximum queue length may be less than the specified `backlog` value, depending on system limits.
 *
 * @warning Ensure that the socket is properly initialized, bound, and of the correct type before calling this function.
 *          Failure to do so will result in undefined behavior or errors.
 */
sysret_t sys_listen(int socket, int backlog)
{
    return listen(socket, backlog);
}

#define MUSLC_MSG_OOB       0x0001
#define MUSLC_MSG_PEEK      0x0002
#define MUSLC_MSG_DONTWAIT  0x0040
#define MUSLC_MSG_WAITALL   0x0100
#define MUSLC_MSG_MORE      0x8000

static int netflags_muslc_2_lwip(int flags)
{
    int flgs = 0;

    if (flags & MUSLC_MSG_PEEK)
    {
        flgs |= MSG_PEEK;
    }
    if (flags & MUSLC_MSG_WAITALL)
    {
        flgs |= MSG_WAITALL;
    }
    if (flags & MUSLC_MSG_OOB)
    {
        flgs |= MSG_OOB;
    }
    if (flags & MUSLC_MSG_DONTWAIT)
    {
        flgs |= MSG_DONTWAIT;
    }
    if (flags & MUSLC_MSG_MORE)
    {
        flgs |= MSG_MORE;
    }
    if (flags & MSG_ERRQUEUE)
    {
        flgs |= MSG_ERRQUEUE;
    }

    return flgs;
}

#ifdef ARCH_MM_MMU
static int copy_msghdr_from_user(struct msghdr *kmsg, struct msghdr *umsg,
        struct iovec **out_iov, void **out_msg_control)
{
    size_t iovs_size;
    struct iovec *uiov, *kiov;
    size_t iovs_buffer_size = 0;
    void *iovs_buffer;

    if (!lwp_user_accessable(umsg, sizeof(*umsg)))
    {
        return -EFAULT;
    }

    lwp_get_from_user(kmsg, umsg, sizeof(*kmsg));

    iovs_size = sizeof(*kmsg->msg_iov) * kmsg->msg_iovlen;
    if (!lwp_user_accessable(kmsg->msg_iov, iovs_size))
    {
        return -EFAULT;
    }

    /* user and kernel */
    kiov = kmem_get(iovs_size * 2);
    if (!kiov)
    {
        return -ENOMEM;
    }

    uiov = (void *)kiov + iovs_size;
    lwp_get_from_user(uiov, kmsg->msg_iov, iovs_size);

    if (out_iov)
    {
        *out_iov = uiov;
    }
    kmsg->msg_iov = kiov;

    for (int i = 0; i < kmsg->msg_iovlen; ++i)
    {
        /*
         * We MUST check we can copy data to user after socket done in uiov
         * otherwise we will be lost the messages from the network!
         */
        if (!lwp_user_accessable(uiov->iov_base, uiov->iov_len))
        {
            kmem_put(kmsg->msg_iov);

            return -EPERM;
        }

        iovs_buffer_size += uiov->iov_len;
        kiov->iov_len = uiov->iov_len;

        ++kiov;
        ++uiov;
    }

    /* msg_iov and msg_control */
    iovs_buffer = kmem_get(iovs_buffer_size + kmsg->msg_controllen);

    if (!iovs_buffer)
    {
        kmem_put(kmsg->msg_iov);

        return -ENOMEM;
    }

    kiov = kmsg->msg_iov;

    for (int i = 0; i < kmsg->msg_iovlen; ++i)
    {
        kiov->iov_base = iovs_buffer;
        iovs_buffer += kiov->iov_len;
        ++kiov;
    }

    *out_msg_control = kmsg->msg_control;
    /* msg_control is the end of the iovs_buffer */
    kmsg->msg_control = iovs_buffer;

    return 0;
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Receives a message from a socket using a message header structure.
 *
 * This system call is used to receive data and associated metadata from a socket.
 * It supports both stream-oriented and message-oriented sockets and allows control
 * over the behavior of the receiving operation via the `flags` parameter.
 *
 * @param[in]  socket   The socket descriptor from which the message will be received.
 *                      The socket must be in a valid and connected state for stream-oriented
 *                      sockets or bound for message-oriented sockets.
 * @param[out] msg      A pointer to an `msghdr` structure that specifies message buffers and
 *                      will receive the incoming data. The structure also stores ancillary
 *                      data for advanced socket operations.
 * @param[in]  flags    Modifiers that control the behavior of the receive operation. Common
 *                      flags include:
 *                       - `MSG_PEEK`: Peek at the incoming data without removing it from the queue.
 *                       - `MSG_WAITALL`: Wait for the full request to be satisfied before returning.
 *                       - `MSG_DONTWAIT`: Perform a non-blocking receive operation.
 *
 * @return sysret_t     Returns `0` on success, or a negative error code on failure.
 *
 * @note The `msghdr` structure should be initialized properly, including setting up buffers for
 *       receiving the data. The function can return fewer bytes than expected depending on socket
 *       type and flags. For stream-oriented sockets, partial data may be received.
 *
 * @warning The `socket` must be valid and in an appropriate state. If the socket is non-blocking
 *          and no data is available, the function will return immediately.
 *
 * @see sys_sendmsg()
 */
sysret_t sys_recvmsg(int socket, struct msghdr *msg, int flags)
{
    int flgs, ret = -1;
    struct msghdr kmsg;
#ifdef ARCH_MM_MMU
    void *msg_control;
    struct iovec *uiov, *kiov;
#endif

    if (!msg)
    {
        return -EPERM;
    }

    flgs = netflags_muslc_2_lwip(flags);

#ifdef ARCH_MM_MMU
    ret = copy_msghdr_from_user(&kmsg, msg, &uiov, &msg_control);

    if (!ret)
    {
        ret = recvmsg(socket, &kmsg, flgs);

        if (ret < 0)
        {
            goto _free_res;
        }

        kiov = kmsg.msg_iov;

        for (int i = 0; i < kmsg.msg_iovlen; ++i)
        {
            lwp_put_to_user(uiov->iov_base, kiov->iov_base, kiov->iov_len);

            ++kiov;
            ++uiov;
        }

        lwp_put_to_user(msg_control, kmsg.msg_control, kmsg.msg_controllen);
        lwp_put_to_user(&msg->msg_flags, &kmsg.msg_flags, sizeof(kmsg.msg_flags));

    _free_res:
        kmem_put(kmsg.msg_iov->iov_base);
        kmem_put(kmsg.msg_iov);
    }
#else
    rt_memcpy(&kmsg, msg, sizeof(kmsg));

    ret = recvmsg(socket, &kmsg, flgs);

    if (!ret)
    {
        msg->msg_flags = kmsg.msg_flags;
    }
#endif /* ARCH_MM_MMU */

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Receives data from a socket, optionally capturing the source address.
 *
 * This system call is used to receive data from a socket. For connectionless sockets, it also
 * retrieves the address of the sender. It supports both blocking and non-blocking operations
 * depending on the socket configuration and the specified flags.
 *
 * @param[in]  socket   The socket descriptor from which the data will be received. The socket
 *                      must be valid and appropriately configured (e.g., connected or bound).
 * @param[out] mem      A pointer to the buffer where the received data will be stored.
 * @param[in]  len      The maximum number of bytes to receive. This defines the size of the `mem` buffer.
 * @param[in]  flags    Modifiers that control the behavior of the receive operation. Common
 *                      flags include:
 *                       - `MSG_PEEK`: Peek at the incoming data without removing it from the queue.
 *                       - `MSG_WAITALL`: Wait for the full request to be satisfied before returning.
 *                       - `MSG_DONTWAIT`: Perform a non-blocking receive operation.
 * @param[out] from     A pointer to a `musl_sockaddr` structure that will hold the address of
 *                      the sender. This parameter can be `NULL` if the sender's address is not needed.
 * @param[in,out] fromlen A pointer to a `socklen_t` variable indicating the size of the `from` buffer.
 *                        On return, it will be updated with the actual size of the sender's address.
 *                        This parameter is ignored if `from` is `NULL`.
 *
 * @return sysret_t     Returns `0` on success, or a negative error code on failure:
 *
 * @note For stream-oriented sockets, this function behaves like `sys_recv()`, and the `from` and
 *       `fromlen` parameters are ignored. For datagram-oriented sockets, the function fills `from`
 *       with the address of the sender.
 *
 * @warning The `socket` must be valid and configured for receiving data. If the `mem` buffer is
 *          smaller than the received data, excess data may be discarded. In non-blocking mode,
 *          if no data is available, the function returns immediately.
 *
 * @see sys_sendto(), sys_recv()
 */
sysret_t sys_recvfrom(int socket, void *mem, size_t len, int flags,
      struct musl_sockaddr *from, socklen_t *fromlen)
{
    int flgs = 0;
#ifdef ARCH_MM_MMU
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef ARCH_MM_MMU
    if (!len)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)mem, len))
    {
        return -EFAULT;
    }

    kmem = kmem_get(len);
    if (!kmem)
    {
        return -ENOMEM;
    }

    if (flags == 0x2)
    {
        flags = 0x1;
    }

    if (from)
    {
        struct sockaddr sa;

        ret = recvfrom(socket, kmem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
    }
    else
    {
        ret = recvfrom(socket, kmem, len, flgs, NULL, NULL);
    }

    if (ret > 0)
    {
        lwp_put_to_user(mem, kmem, len);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    int ret = -1;
    if (from)
    {
        struct sockaddr sa = {0};

        ret = recvfrom(socket, mem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
    }
    else
    {
        ret = recvfrom(socket, mem, len, flags, NULL, NULL);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Receives data from a connected socket.
 *
 * This system call is used to receive data from a socket that is in a connected state.
 * It supports various flags to modify the behavior of the receive operation.
 *
 * @param[in]  socket   The socket descriptor from which the data will be received.
 *                      The socket must be in a valid and connected state.
 * @param[out] mem      A pointer to the buffer where the received data will be stored.
 * @param[in]  len      The maximum number of bytes to receive. This defines the size of the `mem` buffer.
 * @param[in]  flags    Modifiers that control the behavior of the receive operation. Common flags include:
 *                       - `MSG_PEEK`: Peek at the incoming data without removing it from the queue.
 *                       - `MSG_WAITALL`: Wait for the full request to be satisfied before returning.
 *                       - `MSG_DONTWAIT`: Perform a non-blocking receive operation.
 *
 * @return sysret_t     Returns `0` on success, or a negative error code on failure.
 *
 * @note The function is designed for connected sockets, such as stream-oriented sockets (e.g., TCP).
 *       For datagram-oriented sockets (e.g., UDP), use `sys_recvfrom()` to capture the sender's address if needed.
 *
 * @warning The `socket` must be valid and in a connected state. If the `mem` buffer is smaller than the
 *          received data, excess data may be discarded. For non-blocking sockets, the function returns
 *          immediately if no data is available.
 *
 * @see sys_send(), sys_recvfrom()
 */
sysret_t sys_recv(int socket, void *mem, size_t len, int flags)
{
    int flgs = 0;
    int ret;
    void *kmem = RT_NULL;

    if (!lwp_user_accessable((void *)mem, len))
        return -EFAULT;

    kmem = kmem_get(sizeof(*kmem));
    if (kmem == RT_NULL)
    {
        return -ENOMEM;
    }

    flgs = netflags_muslc_2_lwip(flags);
    ret = recvfrom(socket, kmem, len, flgs, NULL, NULL);

    lwp_put_to_user((void *)mem, kmem, len);
    kmem_put(kmem);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Sends a message from a socket using scatter-gather I/O.
 *
 * This system call sends data from multiple buffers specified in the `msghdr` structure. It is particularly
 * useful for advanced socket operations requiring ancillary data or scatter-gather I/O.
 *
 * @param[in] socket   The socket descriptor through which the data will be sent. The socket must be
 *                     valid and, for connection-oriented sockets, in a connected state.
 * @param[in] msg      A pointer to a `msghdr` structure that specifies the message to be sent. This structure includes:
 *                      - `msg_name`: Optional address of the target (used for connectionless sockets like UDP).
 *                      - `msg_namelen`: Length of the address in `msg_name`.
 *                      - `msg_iov`: An array of `iovec` structures pointing to the data buffers.
 *                      - `msg_iovlen`: The number of elements in the `msg_iov` array.
 *                      - `msg_control`: Optional ancillary data (e.g., file descriptors).
 *                      - `msg_controllen`: Length of the ancillary data.
 *                      - `msg_flags`: Flags for the message (e.g., end-of-record markers).
 * @param[in] flags    Flags that modify the behavior of the send operation. Common flags include:
 *                      - `MSG_DONTWAIT`: Perform a non-blocking send operation.
 *                      - `MSG_EOR`: Indicates the end of a record.
 *                      - `MSG_NOSIGNAL`: Prevent the function from raising `SIGPIPE` on errors.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code on failure.
 *
 * @note This function is versatile and supports both connection-oriented (e.g., TCP) and
 *       connectionless (e.g., UDP) sockets. For simpler use cases, consider using `sys_send()` or `sys_sendto()`.
 *
 * @warning The `socket` must be configured correctly for the intended communication. For non-blocking sockets,
 *          the function may return immediately if the send buffer is full. Ancillary data in `msg_control`
 *          must be formatted correctly to avoid undefined behavior.
 *
 * @see sys_send(), sys_sendto(), sys_recvmsg()
 */
sysret_t sys_sendmsg(int socket, const struct msghdr *msg, int flags)
{
    int flgs, ret = -1;
    struct msghdr kmsg;
#ifdef ARCH_MM_MMU
    void *msg_control;
    struct iovec *uiov, *kiov;
#endif
    if (!msg)
    {
        return -EPERM;
    }

    flgs = netflags_muslc_2_lwip(flags);

#ifdef ARCH_MM_MMU
    ret = copy_msghdr_from_user(&kmsg, (struct msghdr *)msg, &uiov, &msg_control);

    if (!ret)
    {
        kiov = kmsg.msg_iov;

        for (int i = 0; i < kmsg.msg_iovlen; ++i)
        {
            lwp_get_from_user(kiov->iov_base, uiov->iov_base, kiov->iov_len);

            ++kiov;
            ++uiov;
        }

        lwp_get_from_user(kmsg.msg_control, msg_control, kmsg.msg_controllen);

        ret = sendmsg(socket, &kmsg, flgs);

        kmem_put(kmsg.msg_iov->iov_base);
        kmem_put(kmsg.msg_iov);
    }
#else
    rt_memcpy(&kmsg, msg, sizeof(kmsg));

    ret = sendmsg(socket, &kmsg, flgs);

    if (!ret)
    {
        msg->msg_flags = kmsg.msg_flags;
    }
#endif /* ARCH_MM_MMU */

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Sends data to a specific address using a socket.
 *
 * This system call is used to send data from a socket to a specified address. It is commonly
 * used with connectionless sockets (e.g., UDP) but can also be used with connection-oriented
 * sockets if the destination address needs to be overridden.
 *
 * @param[in] socket   The socket descriptor used for sending data. It must be valid and
 *                     properly configured for communication.
 * @param[in] dataptr  A pointer to the buffer containing the data to be sent.
 * @param[in] size     The size, in bytes, of the data to be sent.
 * @param[in] flags    Flags that modify the behavior of the send operation. Common flags include:
 *                      - `MSG_DONTWAIT`: Perform a non-blocking send operation.
 *                      - `MSG_NOSIGNAL`: Prevent the function from raising `SIGPIPE` on errors.
 * @param[in] to       A pointer to a `musl_sockaddr` structure that specifies the destination address.
 *                     This parameter can be `NULL` if the socket is connection-oriented.
 * @param[in] tolen    The length of the address structure pointed to by `to`.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code on failure.
 *
 * @note For connectionless sockets (e.g., UDP), `to` and `tolen` must specify a valid destination address.
 *       For connection-oriented sockets (e.g., TCP), these parameters can be ignored if the connection
 *       is already established.
 *
 * @warning Ensure that the buffer size (`size`) matches the expected size for the data protocol in use.
 *          For non-blocking sockets, this function may return immediately if the send buffer is full.
 *
 * @see sys_send(), sys_sendmsg(), sys_recvfrom()
 */
sysret_t sys_sendto(int socket, const void *dataptr, size_t size, int flags,
    const struct musl_sockaddr *to, socklen_t tolen)
{
    int flgs = 0;
#ifdef ARCH_MM_MMU
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef ARCH_MM_MMU
    if (!size)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)dataptr, size))
    {
        return -EFAULT;
    }

    kmem = kmem_get(size);
    if (!kmem)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kmem, (void *)dataptr, size);

    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        ret = sendto(socket, kmem, size, flgs, &sa, tolen);
    }
    else
    {
        ret = sendto(socket, kmem, size, flgs, NULL, tolen);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    int ret;
    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        ret = sendto(socket, dataptr, size, flgs, &sa, tolen);
    }
    else
    {
        ret = sendto(socket, dataptr, size, flgs, NULL, tolen);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Sends data over a connected socket.
 *
 * This system call sends data from the specified buffer through a connected socket. It is typically
 * used with connection-oriented sockets (e.g., TCP) but can also work with connectionless sockets
 * (e.g., UDP) if a connection is established using `sys_connect()`.
 *
 * @param[in] socket   The socket descriptor used for sending data. It must be a valid socket
 *                     and, for connection-oriented sockets, in a connected state.
 * @param[in] dataptr  A pointer to the buffer containing the data to be sent.
 * @param[in] size     The size, in bytes, of the data to be sent.
 * @param[in] flags    Flags that modify the behavior of the send operation. Common flags include:
 *                      - `MSG_DONTWAIT`: Perform a non-blocking send operation.
 *                      - `MSG_NOSIGNAL`: Prevent the function from raising `SIGPIPE` on errors.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code on failure.
 *
 * @note For connection-oriented sockets, the socket must already be connected using `sys_connect()` or
 *       `sys_accept()`. For connectionless sockets, use `sys_sendto()` to specify the destination address.
 *
 * @warning If the socket is in non-blocking mode and the send buffer is full, this function may return
 *          immediately with an error. Ensure that the size of the data (`size`) matches the protocol's
 *          expectations to avoid truncation or overflow issues.
 *
 * @see sys_sendto(), sys_sendmsg(), sys_recv()
 */
sysret_t sys_send(int socket, const void *dataptr, size_t size, int flags)
{
    int flgs = 0;
    int ret = 0;
    void *kdataptr = RT_NULL;

    if (!lwp_user_accessable((void *)dataptr, size))
        return -EFAULT;

    kdataptr = kmem_get(size);
    if (kdataptr == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kdataptr, (void *)dataptr, size) != size)
    {
        kmem_put(kdataptr);
        return -EINVAL;
    }

    flgs = netflags_muslc_2_lwip(flags);
    ret = sendto(socket, kdataptr, size, flgs, NULL, 0);

    kmem_put(kdataptr);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Creates a new socket for communication.
 *
 * This system call creates a new socket endpoint for communication and returns a file descriptor
 * that can be used for subsequent socket operations, such as binding, connecting, or data transfer.
 *
 * @param[in] domain   Specifies the protocol family to be used for the socket. Common values include:
 *                      - `AF_INET`: IPv4 Internet protocols.
 *                      - `AF_INET6`: IPv6 Internet protocols.
 *                      - `AF_UNIX`: Local communication using UNIX domain sockets.
 * @param[in] type     Specifies the type of socket to be created. Common values include:
 *                      - `SOCK_STREAM`: Provides sequenced, reliable, two-way, connection-based byte streams.
 *                      - `SOCK_DGRAM`: Supports datagrams (connectionless, unreliable messages of fixed maximum length).
 *                      - `SOCK_RAW`: Provides raw network protocol access.
 * @param[in] protocol Specifies the specific protocol to be used. Typically set to `0` to use the default
 *                     protocol for the specified domain and type.
 *
 * @return sysret_t    Returns the socket file descriptor on success, or a negative error code on failure.
 *
 * @note The returned socket descriptor must be closed using `sys_close()` to release system resources.
 *
 * @warning Ensure the combination of `domain`, `type`, and `protocol` is valid. Invalid combinations
 *          may result in errors. For example, specifying `AF_INET` with `SOCK_DGRAM` is valid for UDP,
 *          but with `SOCK_STREAM` it is used for TCP.
 *
 * @see sys_bind(), sys_connect(), sys_accept(), sys_close()
 */
sysret_t sys_socket(int domain, int type, int protocol)
{
    int fd = -1;
    int nonblock = 0;
    /* not support SOCK_CLOEXEC type */
    if (type & SOCK_CLOEXEC)
    {
        type &= ~SOCK_CLOEXEC;
    }
    if (type & SOCK_NONBLOCK)
    {
        nonblock = 1;
        type &= ~SOCK_NONBLOCK;
    }

    fd = socket(domain, type, protocol);
    if (fd < 0)
    {
        goto out;
    }
    if (nonblock)
    {
        fcntl(fd, F_SETFL, O_NONBLOCK);
    }

out:
    return (fd < 0 ? GET_ERRNO() : fd);
}

/**
 * @brief Creates a pair of connected sockets.
 *
 * This system call creates two connected sockets that can be used for bidirectional communication
 * between processes or threads. The sockets are returned as file descriptors in the `fd` array.
 *
 * @param[in] domain   Specifies the protocol family to be used for the sockets. Common values include:
 *                      - `AF_UNIX`: Local communication using UNIX domain sockets.
 * @param[in] type     Specifies the type of socket to be created. Common values include:
 *                      - `SOCK_STREAM`: Provides sequenced, reliable, two-way, connection-based byte streams.
 *                      - `SOCK_DGRAM`: Supports datagrams (connectionless, unreliable messages of fixed maximum length).
 * @param[in] protocol Specifies the specific protocol to be used. Typically set to `0` to use the default
 *                     protocol for the specified domain and type.
 * @param[out] fd      An array of two integers where the connected socket descriptors will be stored.
 *                     After a successful call:
 *                      - `fd[0]`: The first socket descriptor.
 *                      - `fd[1]`: The second socket descriptor.
 *
 * @return sysret_t    Returns `0` on success, or a negative error code on failure.
 *
 * @note The sockets in the pair are connected and can be used for inter-process communication
 *       (IPC) or between threads in the same process.
 *
 * @warning Ensure the `domain`, `type`, and `protocol` combination is valid. This function is typically
 *          supported only for `AF_UNIX` domain.
 *
 * @see sys_socket(), sys_close()
 */
sysret_t sys_socketpair(int domain, int type, int protocol, int fd[2])
{
#ifdef RT_USING_SAL
    int ret = 0;
    int k_fd[2];

    if (!lwp_user_accessable((void *)fd, sizeof(int [2])))
    {
        return -EFAULT;
    }

    ret = socketpair(domain, type, protocol, k_fd);

    if (ret == 0)
    {
        lwp_put_to_user(fd, k_fd, sizeof(int [2]));
    }

    return ret;
#else
    return -ELIBACC;
#endif
}

/**
 * @brief Closes an open socket.
 *
 * This system call is used to close a previously opened socket. Once the socket is closed, it is no longer
 * valid for any further operations, such as sending, receiving, or other socket-related functions.
 *
 * @param[in] socket  The socket descriptor to be closed. This descriptor must be a valid socket that was
 *                    previously created with `sys_socket()` or related functions.
 *
 * @return sysret_t   Returns `0` on success, or a negative error code on failure.
 *
 * @note Once a socket is closed, any attempts to use the socket for communication will result in an error.
 *       The system will release any resources associated with the socket.
 *
 * @warning Make sure that no data is being transferred or pending on the socket before closing it.
 *          Closing an active socket might lead to data loss.
 *
 * @see sys_socket(), sys_shutdown()
 */
sysret_t sys_closesocket(int socket)
{
    return closesocket(socket);
}

#endif

/**
 * @brief Finds a thread by its name.
 *
 * This system call is used to search for a thread based on its name. It returns a reference to the
 * thread if found, otherwise it returns `RT_NULL`. The name comparison is case-sensitive.
 *
 * @param[in] name    The name of the thread to search for. This should be a valid string that
 *                    uniquely identifies the thread within the system.
 *
 * @return rt_thread_t   The thread object corresponding to the given name, or `RT_NULL` if no
 *                        matching thread was found.
 *
 * @note The thread name is typically assigned when the thread is created, and it can be used to
 *       identify threads in the system.
 *
 * @warning Ensure that the `name` string is correctly set and unique within the system to avoid
 *          unexpected behavior.
 *
 * @see sys_thread_create(), sys_thread_delete()
 */
rt_thread_t sys_thread_find(char *name)
{
    int len = 0;
    char *kname = RT_NULL;
    rt_thread_t thread;

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

    thread = rt_thread_find(name);

    kmem_put(kname);

    return thread;
}

/**
 * @brief Gets the current system tick count.
 *
 * This system call returns the current value of the system tick counter, which is typically incremented
 * at a fixed interval (e.g., every millisecond or microsecond). The tick count can be used for timing
 * purposes, such as measuring the elapsed time or triggering time-based events.
 *
 * @return rt_tick_t    The current value of the system tick counter.
 *
 * @note The system tick counter typically wraps around after reaching its maximum value, so the
 *       returned tick value may reset after a certain period of time, depending on the configuration
 *       of the system tick timer.
 *
 * @warning Be cautious when using the tick value for time-based calculations, as the counter may
 *          overflow and wrap around. Ensure that the code handling the tick count properly accounts
 *          for potential overflow.
 *
 * @see sys_tick_init(), sys_tick_delay()
 */
rt_tick_t sys_tick_get(void)
{
    return rt_tick_get();
}

/**
 * @brief Delays the current thread for a specified number of milliseconds.
 *
 * This system call puts the calling thread to sleep for a given number of milliseconds. It is a blocking
 * call, meaning the thread will not execute any further instructions until the specified delay has
 * passed. The delay is achieved by the system's timer mechanism.
 *
 * @param[in] ms   The number of milliseconds to delay. The value must be a positive integer.
 *
 * @return sysret_t   Returns `0` on success, or a negative error code on failure.
 *
 * @note This function is useful for introducing a fixed delay in time-sensitive applications or when
 *       the thread needs to be paused before continuing execution.
 *
 * @warning Be cautious when using this function in real-time or time-critical applications, as
 *          excessive delays may affect overall system performance or responsiveness.
 *
 * @see sys_thread_delay(), sys_thread_sleep()
 */
sysret_t sys_thread_mdelay(rt_int32_t ms)
{
    return rt_thread_mdelay(ms);
}

struct k_sigaction {
    void (*handler)(int);
    unsigned long flags;
    void (*restorer)(void);
    unsigned mask[2];
};

/**
 * @brief Changes the action taken by the system on receiving a signal.
 *
 * This system call allows a process to specify how signals should be handled. It allows you to set a
 * new action for a specific signal, retrieve the old action, and define the signal mask that should
 * be applied during the execution of the signal handler.
 *
 * @param[in] sig         The signal number for which the action is to be set or retrieved.
 *                        Signal numbers are typically defined as constants (e.g., `SIGINT`, `SIGTERM`).
 * @param[in] act         A pointer to a `k_sigaction` structure that specifies the new action for the signal.
 *                        If `act` is `NULL`, the signal's action is not changed.
 * @param[out] oact       A pointer to a `k_sigaction` structure where the old action will be stored.
 *                        If `oact` is `NULL`, the old action is not retrieved.
 * @param[in] sigsetsize  The size of the `sigset_t` structure used in `k_sigaction`. This is to ensure the
 *                        compatibility with the signal mask size.
 *
 * @return sysret_t      Returns `0` on success or a negative error code on failure.
 *
 * @note The `k_sigaction` structure allows you to specify the signal handler, signal mask, and flags for
 *       the signal action. It is important to correctly configure the handler to prevent unexpected
 *       behavior in the signal handling process.
 *
 * @warning Be cautious when modifying signal handling behavior, as incorrect configuration may result
 *          in unhandled signals or undefined behavior. Signal handlers should be designed to perform
 *          minimal, safe operations.
 *
 * @see sys_signal(), sys_sigprocmask()
 */
sysret_t sys_sigaction(int sig, const struct k_sigaction *act,
                       struct k_sigaction *oact, size_t sigsetsize)
{
    int ret = -RT_EINVAL;
    struct rt_lwp *lwp;
    struct lwp_sigaction kact, *pkact = RT_NULL;
    struct lwp_sigaction koact, *pkoact = RT_NULL;

    if (!sigsetsize)
    {
        SET_ERRNO(EINVAL);
        goto out;
    }
    if (sigsetsize > sizeof(lwp_sigset_t))
    {
        sigsetsize = sizeof(lwp_sigset_t);
    }
    if (!act && !oact)
    {
        SET_ERRNO(EINVAL);
        goto out;
    }
    if (oact)
    {
        if (!lwp_user_accessable((void *)oact, sizeof(*oact)))
        {
            SET_ERRNO(EFAULT);
            goto out;
        }
        pkoact = &koact;
    }
    if (act)
    {
        if (!lwp_user_accessable((void *)act, sizeof(*act)))
        {
            SET_ERRNO(EFAULT);
            goto out;
        }
        kact.sa_flags = act->flags;
        kact.__sa_handler._sa_handler = act->handler;
        lwp_memcpy(&kact.sa_mask, &act->mask, sigsetsize);
        kact.sa_restorer = act->restorer;
        pkact = &kact;
    }

    lwp = lwp_self();
    RT_ASSERT(lwp);
    ret = lwp_signal_action(lwp, sig, pkact, pkoact);
#ifdef ARCH_MM_MMU
    if (ret == 0 && oact)
    {
        lwp_put_to_user(&oact->handler, &pkoact->__sa_handler._sa_handler, sizeof(void (*)(int)));
        lwp_put_to_user(&oact->mask, &pkoact->sa_mask, sigsetsize);
        lwp_put_to_user(&oact->flags, &pkoact->sa_flags, sizeof(int));
        lwp_put_to_user(&oact->restorer, &pkoact->sa_restorer, sizeof(void (*)(void)));
    }
#endif /* ARCH_MM_MMU */
out:
    return (ret < 0 ? GET_ERRNO() : ret);
}

static int mask_command_u2k[] = {
    [SIG_BLOCK] = LWP_SIG_MASK_CMD_BLOCK,
    [SIG_UNBLOCK] = LWP_SIG_MASK_CMD_UNBLOCK,
    [SIG_SETMASK] = LWP_SIG_MASK_CMD_SET_MASK,
};

/**
 * @brief Sets or retrieves the signal mask for the calling process.
 *
 * This system call allows the caller to block or unblock signals by modifying the signal mask. The signal
 * mask determines which signals are blocked and which signals can be delivered to the process. The
 * function can also be used to retrieve the current signal mask.
 *
 * @param[in] how      The action to be taken on the signal mask. It can be one of the following values:
 *                     - `SIG_BLOCK`: Add the signals in `sigset` to the current mask.
 *                     - `SIG_UNBLOCK`: Remove the signals in `sigset` from the current mask.
 *                     - `SIG_SETMASK`: Set the signal mask to the value in `sigset`, replacing the current mask.
 * @param[in] sigset   A pointer to a `sigset_t` structure that specifies the signals to be blocked or unblocked.
 *                     This parameter is ignored when `how` is `SIG_SETMASK`, in which case `sigset` is used
 *                     as the new signal mask.
 * @param[out] oset    A pointer to a `sigset_t` structure where the previous signal mask will be stored.
 *                     If `oset` is `NULL`, the previous signal mask will not be returned.
 * @param[in] size     The size of the `sigset_t` structure, ensuring compatibility with the signal mask.
 *
 * @return sysret_t   Returns `0` on success or a negative error code on failure.
 *
 * @note Modifying the signal mask prevents signals from being delivered to the process while they are blocked.
 *       Once the signals are unblocked, they will be delivered to the process if they are pending.
 *
 * @warning Be careful when blocking signals, especially critical ones like `SIGKILL`, as it may interfere
 *          with the normal operation of the system. Ensure that signal masks are managed carefully to avoid
 *          missing important signals.
 *
 * @see sys_sigaction(), sys_sigpending()
 */
sysret_t sys_sigprocmask(int how, const sigset_t *sigset, sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t *pnewset = RT_NULL, *poldset = RT_NULL;
#ifdef ARCH_MM_MMU
    lwp_sigset_t newset, oldset;
#endif /* ARCH_MM_MMU*/

    if (!size)
    {
        return -EINVAL;
    }
    if (!oset && !sigset)
    {
        return -EINVAL;
    }
    if (size > sizeof(lwp_sigset_t))
    {
        size = sizeof(lwp_sigset_t);
    }
    if (oset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = &oldset;
#else
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = (lwp_sigset_t *)oset;
#endif
    }
    if (sigset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&newset, (void *)sigset, size);
        pnewset = &newset;
#else
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        pnewset = (lwp_sigset_t *)sigset;
#endif /* ARCH_MM_MMU */
    }
    ret = lwp_thread_signal_mask(rt_thread_self(), mask_command_u2k[how], pnewset, poldset);
#ifdef ARCH_MM_MMU
    if (ret < 0)
    {
        return ret;
    }
    if (oset)
    {
        lwp_put_to_user(oset, poldset, size);
    }
#endif /* ARCH_MM_MMU */
    return (ret < 0 ? -EFAULT: ret);
}

/**
 * @brief Retrieves the set of signals that are pending for delivery to the calling process.
 *
 * This system call allows a process to query the set of signals that are pending, i.e., signals that have
 * been sent to the process but have not yet been delivered because the process is blocking those signals
 * or has not yet handled them. The function returns the set of signals that are waiting to be delivered.
 *
 * @param[out] sigset   A pointer to a `sigset_t` structure where the set of pending signals will be stored.
 *                      The `sigset_t` structure will contain the signals that are pending for delivery.
 * @param[in] sigsize   The size of the `sigset_t` structure, used to ensure compatibility with the signal set.
 *
 * @return sysret_t    Returns `0` on success or a negative error code on failure.
 *
 * @note The returned signal set will contain the signals that have been sent to the process but are blocked,
 *       or that are waiting to be handled. These signals will be delivered once they are unblocked or the
 *       process handles them.
 *
 * @warning Be cautious when querying pending signals, as unblocking too many signals at once may lead
 *          to unexpected behavior or a flood of signal deliveries. It's recommended to carefully manage
 *          the signals the process can accept at any given time.
 *
 * @see sys_sigaction(), sys_sigprocmask()
 */
sysret_t sys_sigpending(sigset_t *sigset, size_t sigsize)
{
    sysret_t ret = 0;
    lwp_sigset_t lwpset;

    /* Verify and Get sigset, timeout */
    if (!sigset || !lwp_user_accessable((void *)sigset, sigsize))
    {
        ret = -EFAULT;
    }
    else
    {
        /* Fit sigset size to lwp set */
        if (sizeof(lwpset) < sigsize)
        {
            LOG_I("%s: sigsize (%lx) extends lwp sigset chunk\n", __func__, sigsize);
            sigsize = sizeof(lwpset);
        }

        lwp_thread_signal_pending(rt_thread_self(), &lwpset);

        if (!lwp_put_to_user(sigset, &lwpset, sigsize))
            RT_ASSERT(0);   /* should never happened */
    }

    return ret;
}

/**
 * @brief Waits for a signal to be delivered, with a timeout.
 *
 * This system call allows a process to wait for one of the signals specified in the `sigset` to be delivered.
 * The process will block until a signal in the set is received or the specified timeout period expires.
 * If the signal is received before the timeout, information about the signal will be returned in the `siginfo_t` structure.
 * If the timeout expires without any signal being delivered, the function will return with an appropriate error code.
 *
 * @param[in] sigset   A pointer to a `sigset_t` structure that specifies the set of signals to wait for.
 *                     The function will block until a signal in this set is received, or the timeout expires.
 * @param[out] info    A pointer to a `siginfo_t` structure where information about the delivered signal will be stored.
 *                     If no signal is received before the timeout, this structure will not be filled.
 * @param[in] timeout  A pointer to a `timespec` structure that specifies the maximum amount of time to wait
 *                     for a signal to be delivered. If this value is `NULL`, the function will wait indefinitely.
 * @param[in] sigsize  The size of the `sigset_t` structure, ensuring compatibility with the signal set.
 *
 * @return sysret_t   Returns `0` on success or a negative error code on failure.
 *
 * @note If the `timeout` is `NULL`, the function will block indefinitely until a signal is delivered.
 *       If a signal is received, the corresponding information is returned in the `siginfo_t` structure.
 *       The `sigset` should contain only the signals you are interested in.
 *
 * @warning If the timeout expires, no signal will be delivered, and the function will return a timeout error.
 *          Make sure to handle the timeout case correctly to prevent any unexpected behavior.
 *
 * @see sys_sigaction(), sys_sigtimedwait()
 */
sysret_t sys_sigtimedwait(const sigset_t *sigset, siginfo_t *info, const struct timespec *timeout, size_t sigsize)
{
    int sig;
    size_t ret;
    lwp_sigset_t lwpset;
    siginfo_t kinfo;
    struct timespec ktimeout;
    struct timespec *ptimeout;

    /* for RT_ASSERT */
    RT_UNUSED(ret);

    /* Fit sigset size to lwp set */
    if (sizeof(lwpset) < sigsize)
    {
        LOG_I("%s: sigsize (%lx) extends lwp sigset chunk\n", __func__, sigsize);
        sigsize = sizeof(lwpset);
    }
    else
    {
        /* if sigset of user is smaller, clear extra space */
        memset(&lwpset, 0, sizeof(lwpset));
    }

    /* Verify and Get sigset, timeout */
    if (!sigset || !lwp_user_accessable((void *)sigset, sigsize))
    {
        return -EFAULT;
    }
    else
    {
        ret = lwp_get_from_user(&lwpset, (void *)sigset, sigsize);
        RT_ASSERT(ret == sigsize);
    }

    if (timeout)
    {
        if (!lwp_user_accessable((void *)timeout, sizeof(*timeout)))
            return -EFAULT;
        else
        {
            ret = lwp_get_from_user(&ktimeout, (void *)timeout, sizeof(*timeout));
            ptimeout = &ktimeout;
            RT_ASSERT(ret == sizeof(*timeout));
        }
    }
    else
    {
        ptimeout = RT_NULL;
    }

    sig = lwp_thread_signal_timedwait(rt_thread_self(), &lwpset, &kinfo, ptimeout);

    if (sig > 0 && info)
    {
        if (!lwp_user_accessable((void *)info, sizeof(*info)))
            return -EFAULT;
        else
        {
            ret = lwp_put_to_user(info, &kinfo, sizeof(*info));
            RT_ASSERT(ret == sizeof(*info));
        }
    }

    return sig;
}

/**
 * @brief Sends a signal to a specific thread.
 *
 * This system call allows a process to send a signal to a specific thread within the same process.
 * The signal specified by the `sig` parameter will be delivered to the thread with the ID `tid`.
 * This function is similar to `kill()`, but it targets a specific thread rather than a process.
 *
 * @param[in] tid   The thread ID to which the signal will be sent. This ID identifies the target thread within the same process.
 * @param[in] sig   The signal number to be sent to the specified thread. The signal can be any valid signal number.
 *
 * @return sysret_t Returns `0` on success or a negative error code on failure.
 *
 * @note The `sig` parameter must be a valid signal number. It can range from `1` to `31`, or be one of the predefined signal constants like `SIGKILL`, `SIGTERM`, etc.
 *       If the target thread does not exist or is not eligible to receive the signal, the function will fail.
 *
 * @warning If an invalid signal number is provided or the target thread does not exist, an error will be returned.
 *          Be careful when sending signals, as some signals (e.g., `SIGKILL`) can immediately terminate the target thread.
 *
 * @see sys_kill(), sys_sigaction()
 */
sysret_t sys_tkill(int tid, int sig)
{
#ifdef ARCH_MM_MMU
    rt_thread_t thread;
    sysret_t ret;

    /**
     * Brief: Match a tid and do the kill
     *
     * Note: Critical Section
     * - the thread (READ. may be released at the meantime; protected by locked)
     */
    thread = lwp_tid_get_thread_and_inc_ref(tid);
    ret = lwp_thread_signal_kill(thread, sig, SI_USER, 0);
    lwp_tid_dec_ref(thread);

    return ret;
#else
    return lwp_thread_kill((rt_thread_t)tid, sig);
#endif
}

/**
 * @brief Manipulates the signal mask for the current thread.
 *
 * This function allows a thread to modify its signal mask, which controls which signals are blocked (prevented from delivery).
 * The signal mask can be modified by adding, removing, or setting the signal set as a whole, depending on the `how` parameter.
 * The `sigset` specifies the signals to be manipulated, and the current signal mask before modification can be retrieved in `oset`.
 *
 * @param[in] how     The operation to perform on the signal mask. It can be one of the following values:
 *                    - `SIG_BLOCK`: Add the signals in `sigset` to the current mask (block those signals).
 *                    - `SIG_UNBLOCK`: Remove the signals in `sigset` from the current mask (unblock those signals).
 *                    - `SIG_SETMASK`: Set the signal mask to the signals specified in `sigset` (replace the current mask).
 * @param[in] sigset  A pointer to an `lwp_sigset_t` structure that specifies the set of signals to be manipulated.
 *                    Signals in this set will be added, removed, or set in the current thread's signal mask based on the `how` parameter.
 * @param[out] oset   A pointer to an `lwp_sigset_t` structure where the previous signal mask will be stored.
 *                    This allows the caller to restore the previous mask if needed.
 * @param[in] size    The size of the `lwp_sigset_t` structure. This ensures that the correct structure size is used during signal mask manipulation.
 *
 * @return sysret_t   Returns `0` on success or a negative error code on failure.
 *
 * @note The `sigset` structure should contain only valid signal numbers. If `how` is `SIG_SETMASK`, the entire signal mask will be replaced by the contents of `sigset`.
 *       If `how` is `SIG_BLOCK` or `SIG_UNBLOCK`, the signals in `sigset` will be added or removed from the current mask, respectively.
 *
 * @warning Be cautious when modifying the signal mask, as blocking signals can cause the thread to miss important signals.
 *          If a signal is blocked, it will not be delivered to the thread until it is unblocked, or the thread is explicitly made to handle it.
 *
 * @see sys_sigaction(), sys_thread_sigpending()
 */
sysret_t sys_thread_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t *pnewset = RT_NULL, *poldset = RT_NULL;
#ifdef ARCH_MM_MMU
    lwp_sigset_t newset, oldset;
#endif /* ARCH_MM_MMU */

    if (!size)
    {
        return -EINVAL;
    }
    if (!oset && !sigset)
    {
        return -EINVAL;
    }
    if (size != sizeof(lwp_sigset_t))
    {
        return -EINVAL;
    }
    if (oset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = &oldset;
#else
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = oset;
#endif
    }
    if (sigset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&newset, (void *)sigset, sizeof(lwp_sigset_t));
        pnewset = &newset;
#else
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        pnewset = (lwp_sigset_t *)sigset;
#endif
    }
    ret = lwp_thread_signal_mask(rt_thread_self(), mask_command_u2k[how], pnewset, poldset);
    if (ret < 0)
    {
        return ret;
    }
#ifdef ARCH_MM_MMU
    if (oset)
    {
        lwp_put_to_user(oset, poldset, sizeof(lwp_sigset_t));
    }
#endif
    return (ret < 0 ? -EFAULT: ret);
}

#ifndef ARCH_MM_MMU

/**
 * @brief Sets the signal handler for a specific signal in the current thread.
 *
 * This function allows a thread to set a custom signal handler for a specific signal.
 * When the specified signal is received, the corresponding handler function (`func`) will be invoked.
 * The handler will be executed in the context of the current thread, allowing it to handle signals as needed.
 *
 * @param[in] sig    The signal number for which the handler is being set. This should be a valid signal number.
 * @param[in] func   The signal handler function to be set. This function will be called when the specified signal is received.
 *                   The signature of `func` should match the expected format for signal handlers.
 *
 * @return sysret_t  Returns `0` on success or a negative error code on failure.
 *
 * @note The `func` parameter must be a valid function pointer. It will be called when the signal specified by `sig` is received by the thread.
 *       The handler function typically has the signature: `void handler(int sig)`, where `sig` is the signal number.
 *
 * @warning Setting a custom signal handler may override any default actions for that signal.
 *          It is important to ensure that the handler function is properly designed to handle the signal appropriately.
 *          For example, some signals may require special handling (e.g., `SIGKILL` cannot be caught).
 *
 * @see sys_signal(), sys_lwp_sigaction()
 */
sysret_t sys_lwp_sighandler_set(int sig, lwp_sighandler_t func)
{
    if (!lwp_user_accessable((void *)func, sizeof(lwp_sighandler_t)))
    {
        return -EFAULT;
    }

    lwp_sighandler_set(sig, func);
    return 0;
}

/**
 * @brief Sets the signal handler for a specific signal in the target thread.
 *
 * This function allows setting a custom signal handler for a specific signal within a particular thread.
 * When the specified signal is delivered to the thread, the corresponding handler function (`func`) will be invoked.
 * The handler is executed in the context of the thread that receives the signal.
 *
 * @param[in] sig    The signal number for which the handler is being set. This should be a valid signal number.
 * @param[in] func   The signal handler function to be set. This function will be called when the specified signal is delivered to the target thread.
 *                   The handler function should have the signature `void func(int sig)`.
 *
 * @return sysret_t  Returns `0` on success or a negative error code on failure.
 *
 * @note The `func` parameter must be a valid function pointer, and it will be invoked when the signal specified by `sig` is delivered to the target thread.
 *       The handler function typically has the signature: `void handler(int sig)`, where `sig` is the signal number.
 *
 * @warning Setting a custom signal handler may override any default actions for that signal.
 *          It is important to ensure that the handler function is properly designed to handle the signal appropriately.
 *          For example, some signals may require special handling (e.g., `SIGKILL` cannot be caught).
 *
 * @see sys_thread_sigprocmask(), sys_thread_sigaction(), sys_signal()
 */
sysret_t sys_thread_sighandler_set(int sig, lwp_sighandler_t func)
{
    if (!lwp_user_accessable((void *)func, sizeof(lwp_sighandler_t)))
    {
        return -EFAULT;
    }

    lwp_thread_sighandler_set(sig, func);
    return 0;
}
#endif /* not defined ARCH_MM_MMU */

/**
 * @brief Waits for the termination of a child process.
 *
 * This function makes the calling process wait until one of its child processes terminates or until a
 * specified condition is met. The function retrieves information about the terminated child process,
 * including its exit status, and can also handle other process-related events, such as stopping or
 * continuing execution.
 *
 * @param[in] pid     The process ID of the child process to wait for. If `pid` is:
 *                    - `-1`: Wait for any child process.
 *                    - `0`: Wait for any child process in the same process group.
 *                    - > 0: Wait for the child process with the specified process ID.
 * @param[out] status A pointer to an integer where the exit status of the terminated child process will be stored.
 *                    This value provides information about the child's termination status, such as normal exit,
 *                    signal termination, etc.
 * @param[in] options A bitmask of options that control the behavior of the function. It can include:
 *                    - `WNOHANG`: Return immediately if no child has exited.
 *                    - `WUNTRACED`: Report status of stopped child processes.
 *                    - Other flags can be defined depending on the implementation.
 *
 * @return sysret_t  Returns the process ID of the child process that terminated on success, or a negative error code on failure.
 *
 * @note The `status` argument provides detailed information about the termination of the child process. To interpret this
 *       status, macros such as `WIFEXITED()`, `WIFSIGNALED()`, and `WEXITSTATUS()` are commonly used.
 *
 * @warning This function should be used carefully when managing child processes, as not properly handling child processes
 *          may lead to zombie processes.
 *
 * @see sys_wait(), sys_waitid()
 */
sysret_t sys_waitpid(int32_t pid, int *status, int options)
{
    int ret = -1;
#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)status, sizeof(int)))
    {
        return -EFAULT;
    }
    else
    {
        ret = lwp_waitpid(pid, status, options, RT_NULL);
    }
#else
    if (!lwp_user_accessable((void *)status, sizeof(int)))
    {
        return -EFAULT;
    }
    ret = waitpid(pid, status, options);
#endif
    return ret;
}

#if defined(RT_USING_SAL) && defined(SAL_USING_POSIX)
struct musl_addrinfo
{
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;

    struct musl_sockaddr *ai_addr;
    char *ai_canonname;

    struct musl_addrinfo *ai_next;
};

/**
 * @brief Resolves network addresses and service names into a list of address structures.
 *
 * This function provides a mechanism for resolving a host name and service name (or port number)
 * into a list of address structures suitable for use with socket-based communication. The function
 * can handle both IPv4 and IPv6 addresses and provides a flexible way to specify different types
 * of address and service resolution options.
 *
 * @param[in] nodename  The host name to be resolved. This can be a DNS name or an IP address in string format.
 *                      If `nodename` is `NULL`, the function will resolve the local host.
 * @param[in] servname  The service name (e.g., "http") or port number to be resolved. If `servname` is `NULL`,
 *                      the function will resolve the port number or address without any service association.
 * @param[in] hints     A pointer to a `struct musl_addrinfo` that provides hints for the address resolution.
 *                      It can be used to specify criteria such as the desired address family (IPv4 or IPv6),
 *                      socket type, protocol, and flags for resolution.
 * @param[out] res      A pointer to a `struct musl_addrinfo` that will be filled with the resolved address
 *                      information. The resulting linked list will contain one or more `struct musl_sockaddr`
 *                      structures, each representing a different address that can be used for communication.
 *
 * @return sysret_t     Returns `0` on success, indicating that the address resolution was successful.
 *                       On failure, returns a negative error code.
 *
 * @note The `res` parameter points to a linked list of resolved address structures. Each node in the list
 *       contains a different resolved address and can be used for socket connection purposes.
 *       It is important to free the memory allocated for the list after it is no longer needed, using `freeaddrinfo()`.
 *
 * @warning The `hints` structure allows you to specify various options for the resolution. However, incorrect
 *          hints may lead to unexpected or incorrect results. For example, if you request IPv6 addresses but
 *          the host only supports IPv4, the function may not return the expected results.
 *
 * @see freeaddrinfo(), sys_socket(), sys_connect(), sys_gethostbyname(), sys_gethostbyaddr()
 */
sysret_t sys_getaddrinfo(const char *nodename,
        const char *servname,
        const struct musl_addrinfo *hints,
        struct musl_addrinfo *res)
{
    int ret = -1;
    struct addrinfo *k_res = NULL;
    char *k_nodename = NULL;
    char *k_servname = NULL;
    struct addrinfo *k_hints = NULL;
#ifdef ARCH_MM_MMU
    int len = 0;
#endif

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)res, sizeof(*res)))
    {
        SET_ERRNO(EFAULT);
        goto exit;
    }
#endif
    if (nodename)
    {
#ifdef ARCH_MM_MMU
        len = lwp_user_strlen(nodename);
        if (len <= 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }

        k_nodename = (char *)kmem_get(len + 1);
        if (!k_nodename)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        if (lwp_get_from_user(k_nodename, (void *)nodename, len + 1) != len + 1)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#else
        k_nodename = rt_strdup(nodename);
        if (!k_nodename)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
#endif
    }
    if (servname)
    {
#ifdef ARCH_MM_MMU
        len = lwp_user_strlen(servname);
        if (len <= 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }

        k_servname = (char *)kmem_get(len + 1);
        if (!k_servname)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        if (lwp_get_from_user(k_servname, (void *)servname, len + 1) < 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#else
        k_servname = rt_strdup(servname);
        if (!k_servname)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
#endif
    }

    if (hints)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)hints, sizeof(*hints)))
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#endif
        k_hints = (struct addrinfo *) rt_malloc(sizeof *hints);
        if (!k_hints)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        rt_memset(k_hints, 0x0, sizeof(struct addrinfo));
        k_hints->ai_flags    = hints->ai_flags;
        k_hints->ai_family   = hints->ai_family;
        k_hints->ai_socktype = hints->ai_socktype;
        k_hints->ai_protocol = hints->ai_protocol;
        k_hints->ai_addrlen  = hints->ai_addrlen;
    }

    ret = sal_getaddrinfo(k_nodename, k_servname, k_hints, &k_res);
    if (ret == 0)
    {
        /* set sockaddr */
        sockaddr_tomusl(k_res->ai_addr, res->ai_addr);
        res->ai_addrlen = k_res->ai_addrlen;

        /* set up addrinfo */
        res->ai_family = k_res->ai_family;
        res->ai_flags  = k_res->ai_flags;
        res->ai_next = NULL;

        if (hints != NULL)
        {
            /* copy socktype & protocol from hints if specified */
            res->ai_socktype = hints->ai_socktype;
            res->ai_protocol = hints->ai_protocol;
        }

        sal_freeaddrinfo(k_res);
        k_res = NULL;
    }

exit:
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }
#ifdef ARCH_MM_MMU
    if (k_nodename)
    {
        kmem_put(k_nodename);
    }
#else
    if (k_nodename)
    {
        rt_free(k_nodename);
    }
#endif
#ifdef ARCH_MM_MMU
    if (k_servname)
    {
        kmem_put(k_servname);
    }
#else
    if (k_servname)
    {
        rt_free(k_servname);
    }
#endif
    if (k_hints)
    {
        rt_free(k_hints);
    }

    return ret;
}

#define HOSTENT_BUFSZ   512

/**
 * @brief Resolves a host name to an address, with support for specifying the address family.
 *
 * This function performs a lookup of the specified host name, and resolves it to an address,
 * while allowing the caller to specify the desired address family (e.g., IPv4 or IPv6). It is
 * a reentrant version of `gethostbyname2`, meaning it is safe for use in multi-threaded applications.
 * The results are returned in a user-provided buffer to avoid memory allocation overhead.
 *
 * @param[in] name      The host name to be resolved. This can be a DNS name or an IP address in string format.
 * @param[in] af        The address family to use for the resolution. Common values are:
 *                      - `AF_INET` for IPv4 addresses.
 *                      - `AF_INET6` for IPv6 addresses.
 * @param[out] ret      A pointer to a `struct hostent` where the resolved host information will be stored.
 *                      This includes the host name, alias names, address type, and the address itself.
 * @param[in] buf       A buffer to store additional information required for the `struct hostent` structure.
 *                      This is needed to ensure the reentrant behavior and avoid memory allocation.
 * @param[in] buflen    The size of the buffer provided.
 * @param[out] result   A pointer to a `struct hostent*` that will point to the resolved host entry.
 *                      This will be set to the value of `ret` upon success.
 * @param[out] err      A pointer to an integer where error codes will be stored. If the function fails,
 *                      `err` will contain a non-zero value corresponding to the error.
 *
 * @return sysret_t     Returns `0` on success, indicating the resolution was successful.
 *                       On failure, returns a negative error code that indicates the failure reason.
 *
 * @note This function is reentrant and thread-safe, meaning it does not use static memory or global state.
 *       It relies on the buffers provided by the caller to store the resolved data.
 *
 * @see gethostbyname2(), sys_gethostbyname(), sys_socket(), sys_connect(), sys_getaddrinfo()
 */
sysret_t sys_gethostbyname2_r(const char *name, int af, struct hostent *ret,
        char *buf, size_t buflen,
        struct hostent **result, int *err)
{
    int ret_val = -1;
    int sal_ret = -1 , sal_err = -1;
    struct hostent sal_he, sal_tmp;
    struct hostent *sal_result = NULL;
    char *sal_buf = NULL;
    char *k_name  = NULL;
    int len = 0;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)err, sizeof(*err)))
    {
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    if (!lwp_user_accessable((void *)result, sizeof(*result))
    || !lwp_user_accessable((void *)ret, sizeof(*ret))
    || !lwp_user_accessable((void *)buf, buflen))
    {
        /* not all arguments given */
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    k_name = (char *)kmem_get(len + 1);
    if (!k_name)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    if (lwp_get_from_user(k_name, (void *)name, len + 1) < 0)
    {
        SET_ERRNO(EFAULT);
        goto __exit;
    }
#else
    k_name = rt_strdup(name);
    if (k_name == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }
#endif

    *result = ret;
    sal_buf = (char *)malloc(HOSTENT_BUFSZ);
    if (sal_buf == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    /* get host by name in SAL */
    sal_ret = sal_gethostbyname_r(k_name, &sal_he, sal_buf, HOSTENT_BUFSZ, &sal_result, &sal_err);
    if (sal_ret == 0)
    {
        int index = 0, cnt = 0;
        char *ptr = buf;

        /* get counter */
        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            index++;
        }
        cnt = index + 1;

#ifdef ARCH_MM_MMU
        /* update user space hostent */
        lwp_put_to_user(buf, k_name, buflen - (ptr - buf));
        lwp_memcpy(&sal_tmp, &sal_he, sizeof(sal_he));
        sal_tmp.h_name = ptr;
        ptr += rt_strlen(k_name);

        sal_tmp.h_addr_list = (char**)ptr;
        ptr += cnt * sizeof(char *);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            sal_tmp.h_addr_list[index] = ptr;
            lwp_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index++;
        }
        sal_tmp.h_addr_list[index] = NULL;
        lwp_put_to_user(ret, &sal_tmp, sizeof(sal_tmp));
#else
        /* update user space hostent */
        ret->h_addrtype = sal_he.h_addrtype;
        ret->h_length   = sal_he.h_length;

        rt_strncpy(ptr, k_name, buflen - (ptr - buf));
        ret->h_name = ptr;
        ptr += strlen(k_name);

        ret->h_addr_list = (char**)ptr;
        ptr += cnt * sizeof(char *);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            ret->h_addr_list[index] = ptr;
            lwp_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index++;
        }
        ret->h_addr_list[index] = NULL;
#endif
        ret_val = 0;
    }
    else
    {
        SET_ERRNO(EINVAL);
    }

__exit:
    if (ret_val < 0)
    {
        ret_val = GET_ERRNO();
    }

    /* release buffer */
    if (sal_buf)
    {
        free(sal_buf);
    }
#ifdef ARCH_MM_MMU
    if (k_name)
    {
        kmem_put(k_name);
    }
#else
    if (k_name)
    {
        free(k_name);
    }
#endif

    return ret_val;
}
#endif

/**
 * @brief Gets the current working directory.
 *
 * This function retrieves the absolute pathname of the current working directory
 * and stores it in the provided buffer. The buffer must be large enough to hold
 * the directory path, including the null-terminator. If the buffer is too small,
 * the function will return an error.
 *
 * @param[out] buf     A pointer to a buffer where the current working directory
 *                     path will be stored. The buffer should be large enough
 *                     to hold the path, including the null-terminator.
 * @param[in] size     The size of the buffer in bytes. The buffer must be large enough
 *                     to accommodate the full path.
 *
 * @return long        On success, returns the number of bytes written to the buffer
 *                     (not including the null-terminator). If the buffer is not large
 *                     enough, returns a negative error code.
 *
 * @note The maximum path length depends on the system's configuration.
 *       Ensure the buffer size is sufficient to hold the entire path.
 *
 * @see sys_chdir(), sys_getcwd_r(), sys_realpath()
 */
long sys_getcwd(char *buf, size_t size)
{
    char *tmp = RT_NULL;
    long ret = -1;

    if (!lwp_user_accessable((void *)buf, size))
    {
        return ret;
    }

    tmp = (char *)rt_malloc(size);
    if (!tmp)
    {
        return ret;
    }

    if (getcwd(tmp, size) != RT_NULL)
    {
        if (lwp_put_to_user(buf, tmp, size) > 0)
        {
            if (buf != RT_NULL)
                ret = strlen(buf);
            else
                ret = -EFAULT;
        }
    }

    rt_free(tmp);

    return ret;
}

/**
 * @brief Changes the current working directory.
 *
 * This function changes the current working directory of the calling process
 * to the directory specified by the given path. The path can be absolute or
 * relative. If the specified path does not exist or the process does not have
 * sufficient permissions, the function will return an error.
 *
 * @param[in] path     The path to the new working directory. This can be either
 *                     an absolute or a relative path.
 *
 * @return sysret_t    Returns `0` on success, indicating that the working
 *                     directory was successfully changed. On failure, returns a
 *                     negative error code indicating the reason for failure.
 *
 * @note If the specified path is a relative path, it is interpreted relative
 *       to the current working directory.
 *
 * @see sys_getcwd(), sys_chdir() for changing directories, sys_opendir(), sys_stat()
 */
sysret_t sys_chdir(const char *path)
{
#ifdef ARCH_MM_MMU
    int err = 0;
    int len = 0;
    int errcode;
    char *kpath = RT_NULL;

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kpath = (char *)kmem_get(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kpath, (void *)path, len + 1) != (len + 1))
    {
        kmem_put(kpath);
        return -EINVAL;
    }

    err = chdir(kpath);
    errcode = err != 0 ? GET_ERRNO() : 0;

    kmem_put(kpath);

    return errcode;
#else
    int ret = chdir(path);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Changes the current working directory to the one associated with the specified file descriptor.
 *
 * This function changes the current working directory of the calling process
 * to the directory associated with the file descriptor `fd`. The file descriptor
 * should refer to an open directory. If the file descriptor does not refer to a
 * directory, or if the process lacks the necessary permissions, the function will
 * return an error.
 *
 * @param[in] fd   The file descriptor referring to the directory to which the current
 *                 working directory should be changed.
 *
 * @return sysret_t    Returns `0` on success, indicating the current working directory
 *                     was successfully changed. On failure, returns a negative error code.
 *
 * @note The file descriptor must refer to a directory. If it refers to a file or other
 *       non-directory object, the operation will fail.
 *
 * @see sys_chdir(), sys_getcwd(), sys_opendir(), sys_open()
 */
sysret_t sys_fchdir(int fd)
{
    int errcode = -ENOSYS;
#ifdef ARCH_MM_MMU
#ifdef RT_USING_DFS_V2
    int err = -1;
    struct dfs_file *d;
    char *kpath;

    d = fd_get(fd);
    if (!d || !d->vnode)
    {
        return -EBADF;
    }
    kpath = dfs_dentry_full_path(d->dentry);
    if (!kpath)
    {
        return -EACCES;
    }

    err = chdir(kpath);
    errcode = err != 0 ? GET_ERRNO() : 0;

    kmem_put(kpath);
#endif
#endif
    return errcode;
}

/**
 * @brief Creates a new directory with the specified path and mode.
 *
 * This function creates a new directory with the specified path and mode.
 * The directory is created with the permissions specified by the `mode` parameter.
 * If the directory already exists, the function will return an error.
 *
 * @param[in] path     The path of the directory to be created. This can be an absolute
 *                     or relative path. If the directory does not exist, it will be created.
 * @param[in] mode     The permissions to be set for the new directory. This parameter
 *                     specifies the access permissions for the directory owner, group, and others.
 *
 * @return sysret_t    Returns `0` on success, indicating that the directory was successfully
 *                     created. On failure, returns a negative error code indicating the reason for failure.
 *
 * @note The `mode` parameter specifies the permissions for the new directory. The permissions
 *       are typically specified using the `S_IRWXU`, `S_IRWXG`, and `S_IRWXO` macros, which
 *       define the read, write, and execute permissions for the owner, group, and others.
 *
 * @see sys_rmdir(), sys_chdir(), sys_mkdirat()
 */
sysret_t sys_mkdir(const char *path, mode_t mode)
{
#ifdef ARCH_MM_MMU
    int err = 0;
    int len = 0;
    char *kpath = RT_NULL;

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kpath = (char *)kmem_get(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kpath, (void *)path, len + 1) != (len + 1))
    {
        kmem_put(kpath);
        return -EINVAL;
    }

    err = _SYS_WRAP(mkdir(kpath, mode));

    kmem_put(kpath);

    return err;
#else
    int ret = mkdir(path, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Removes the specified directory.
 *
 * This function removes the directory specified by the given path. The directory
 * must be empty for the operation to succeed. If the directory is not empty, the
 * function will return an error. If the directory does not exist or the process
 * lacks the necessary permissions, the function will also return an error.
 *
 * @param[in] path     The path of the directory to be removed. This can be an absolute
 *                     or relative path. The directory must be empty for the operation to succeed.
 *
 * @return sysret_t    Returns `0` on success, indicating that the directory was successfully
 *                     removed. On failure, returns a negative error code indicating the reason for failure.
 *
 * @note The directory must be empty for the operation to succeed. If the directory contains
 *       files or subdirectories, the operation will fail. To remove a non-empty directory,
 *       the contents must be deleted first.
 *
 * @see sys_mkdir(), sys_chdir(), sys_rmdirat()
 */
sysret_t sys_rmdir(const char *path)
{
    int err = 0;
    int ret = 0;
#ifdef ARCH_MM_MMU
    int len = 0;
    char *kpath = RT_NULL;

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kpath = (char *)kmem_get(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kpath, (void *)path, len + 1) != (len + 1))
    {
        kmem_put(kpath);
        return -EINVAL;
    }

    ret = rmdir(kpath);
    if(ret < 0)
    {
        err = GET_ERRNO();
    }

    kmem_put(kpath);

    return (err < 0 ? err : ret);
#else
    ret = rmdir(path);
    if(ret < 0)
    {
        err = GET_ERRNO();
    }
    return (err < 0 ? err : ret);
#endif
}

/**
 * @brief Reads directory entries.
 *
 * This function reads the directory entries from the directory stream specified by the file descriptor `fd`.
 * It stores the directory entries in the buffer pointed to by `dirp`, up to the specified number of bytes (`nbytes`).
 * The entries are returned in a format compatible with the `struct libc_dirent` structure.
 *
 * @param[in] fd      The file descriptor referring to an open directory. This descriptor must be obtained
 *                    from a call to `sys_open()` with the appropriate flags for directory reading.
 * @param[out] dirp   A pointer to a buffer where the directory entries will be stored.
 *                    The buffer must be large enough to hold at least `nbytes` bytes of directory entries.
 * @param[in] nbytes  The size of the buffer (`dirp`) in bytes. It limits the number of directory entries
 *                    that can be read in a single call. The function will return as many entries as possible
 *                    that fit within the buffer size.
 *
 * @return sysret_t   Returns the number of bytes read on success, which may be less than `nbytes` if there
 *                     are fewer entries in the directory or if the buffer is too small.
 *                     On failure, returns a negative error code.
 *
 * @note If the function returns 0, it indicates the end of the directory stream. A negative return value
 *       indicates an error. The caller can use the returned number of bytes to process the entries in `dirp`.
 *
 * @see sys_open(), sys_close(), sys_readdir(), sys_stat()
 */
sysret_t sys_getdents(int fd, struct libc_dirent *dirp, size_t nbytes)
{
    int ret = -1;
    struct dfs_file *file;
    size_t cnt = (nbytes / sizeof(struct libc_dirent));
    size_t rtt_nbytes = 0;
    struct dirent *rtt_dirp;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)dirp, sizeof(struct libc_dirent)))
    {
        return -EFAULT;
    }
#endif

    if (cnt == 0)
    {
        return -EINVAL;
    }
    rtt_nbytes = cnt * sizeof(struct dirent);
    rtt_dirp = (struct dirent *)rt_malloc(rtt_nbytes);
    if (!rtt_dirp)
    {
        return -ENOMEM;
    }
    file = fd_get(fd);
    ret = dfs_file_getdents(file, rtt_dirp, rtt_nbytes);
    if (ret > 0)
    {
        size_t i = 0;
        cnt = ret / sizeof(struct dirent);
        for (i = 0; i < cnt; i++)
        {
            dirp[i].d_ino = 0;
            dirp[i].d_off = i*sizeof(struct libc_dirent);
            dirp[i].d_type = rtt_dirp[i].d_type;
            dirp[i].d_reclen = sizeof(struct libc_dirent);
            strcpy(dirp[i].d_name, rtt_dirp[i].d_name);
        }
        ret = cnt * sizeof(struct libc_dirent);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    rt_free(rtt_dirp);

    return ret;
}

/**
 * @brief Retrieves the current value of the error code.
 *
 * This function returns the most recent error code set by a system call. The error code is typically set
 * when a system call fails. This function allows users to retrieve the last error that occurred, helping to
 * diagnose issues or handle errors in a more controlled manner.
 *
 * @return sysret_t  The current error code. A value of `0` indicates no error, while a non-zero value
 *                   represents the most recent error. The error codes are system-specific and can
 *                   represent various failure conditions (e.g., `EINVAL`, `ENOMEM`, `EIO`).
 *
 * @note The error code returned is specific to the current thread or process and is typically updated
 *       each time a system call fails. The error code is persistent until it is overwritten by the next
 *       failed system call or explicitly reset.
 *
 * @see sys_set_errno(), sys_perror(), sys_strerror()
 */
sysret_t sys_get_errno(void)
{
    return rt_get_errno();
}

#ifdef ARCH_MM_MMU

/**
 * @brief Sets the thread-specific data area.
 *
 * This function is used to associate a specific area of memory with the current thread. The area pointed to
 * by `p` is set as the thread's local storage. Thread-specific data is used to store data that is unique to
 * each thread, allowing different threads to maintain independent state information.
 *
 * @param[in] p  A pointer to the memory area that is to be set as the thread's local storage. This area
 *               will be used by the thread to store its specific data. The structure and size of the data
 *               area depend on the implementation and use case.
 *
 * @return sysret_t   Returns `0` on success. On failure, it returns a negative error code.
 *
 * @note This function is typically used to set up thread-specific storage for managing data that should
 *       not be shared between threads. The data area is accessible only by the thread that set it, ensuring
 *       thread safety for the stored information.
 *
 * @see sys_get_thread_area(), sys_thread_create(), sys_thread_self()
 */
sysret_t sys_set_thread_area(void *p)
{
    rt_thread_t thread;

    thread = rt_thread_self();
    thread->thread_idr = p;
    arch_set_thread_area(p);

    return 0;
}

/**
 * @brief Sets the address at which the thread ID is stored.
 *
 * This function sets the address of a variable that will store the thread ID for the calling thread.
 * The specified address `tidptr` will hold the thread's unique identifier. This can be useful for
 * managing thread-specific state or for synchronization mechanisms where the thread's ID needs to be
 * shared or checked by other parts of the system.
 *
 * @param[in] tidptr  A pointer to an integer where the thread ID will be stored. This value will
 *                    hold the calling thread's ID, and it can be accessed to identify the thread
 *                    later. The value of the thread ID can be used in various thread management
 *                    operations.
 *
 * @return sysret_t   Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is typically used in systems that require associating a specific address with the
 *       thread ID, often in real-time or embedded systems where managing and accessing thread IDs is
 *       crucial for scheduling or resource allocation.
 *
 * @see sys_get_tid(), sys_thread_self(), sys_thread_create()
 */
sysret_t sys_set_tid_address(int *tidptr)
{
    rt_thread_t thread;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)tidptr, sizeof(int)))
    {
        return -EFAULT;
    }
#endif
    thread = rt_thread_self();
    thread->clear_child_tid = tidptr;
    return thread->tid;
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Gets the thread ID of the calling thread.
 *
 * This function returns the unique thread identifier (thread ID) for the calling thread. The thread ID
 * can be used to uniquely identify the thread within the system and is typically used for debugging,
 * thread management, or scheduling purposes.
 *
 * @return sysret_t   The thread ID of the calling thread. The value is typically a positive integer
 *                     representing the unique ID assigned to the thread. In case of failure, an error code
 *                     may be returned.
 *
 * @note The thread ID returned by this function is unique within the system, and it may be used to
 *       reference or manipulate the specific thread associated with the ID.
 *
 * @see sys_set_tid_address(), sys_thread_self(), sys_thread_create()
 */
sysret_t sys_gettid(void)
{
    return rt_thread_self()->tid;
}

/**
 * @brief Checks the accessibility of a file or directory.
 *
 * This function checks whether the calling process has the specified access rights for the given file or directory.
 * The check is performed based on the provided `mode`, which can indicate whether read, write, or execute permissions
 * are required.
 *
 * @param[in] filename  The path to the file or directory whose accessibility is being checked.
 * @param[in] mode      The access mode to check for. This can be a combination of the following:
 *                      - `R_OK`: Check for read permission.
 *                      - `W_OK`: Check for write permission.
 *                      - `X_OK`: Check for execute permission.
 *                      - `F_OK`: Check if the file exists.
 *
 * @return sysret_t     Returns `0` if the specified access is allowed. On failure, returns a negative error code.
 *
 * @note This function does not modify the file or directory, it only checks if the specified access rights are granted.
 *
 * @see sys_open(), sys_stat(), sys_fstat(), sys_chmod(), sys_chown()
 */
sysret_t sys_access(const char *filename, int mode)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    rt_size_t len = 0;
    char *kfilename = RT_NULL;

    len = lwp_user_strlen(filename);
    if (len <= 0)
    {
        return -EINVAL;
    }

    kfilename = (char *)kmem_get(len + 1);
    if (!kfilename)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kfilename, (void *)filename, len + 1) != (len + 1))
    {
        kmem_put(kfilename);
        return -EFAULT;
    }

    ret = access(kfilename, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kfilename);
    return ret;
#else
    ret = access(filename, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Creates a pipe, a unidirectional data channel.
 *
 * This function creates a pipe, which is a unidirectional data channel used for inter-process communication.
 * The pipe consists of two file descriptors: one for reading from the pipe and one for writing to the pipe.
 * The pipe is used for passing data between processes or threads, typically in a producer-consumer scenario.
 *
 * @param[out] fd  An array of two integers where the file descriptors for the read and write ends of the pipe will be stored.
 *                 - `fd[0]`: The file descriptor for reading from the pipe.
 *                 - `fd[1]`: The file descriptor for writing to the pipe.
 *
 * @return sysret_t   Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The pipe created by this function is typically used for simple communication between processes or threads.
 *       The data written to `fd[1]` can be read from `fd[0]`. After usage, both file descriptors should be closed.
 *
 * @see sys_read(), sys_write(), sys_close(), sys_fork(), sys_execve()
 */
sysret_t sys_pipe(int fd[2])
{
    int ret;
    int kfd[2] = {0, 0};

    if (!lwp_user_accessable((void *)fd, sizeof(int[2])))
    {
        return -EFAULT;
    }

    ret = pipe(kfd);

    lwp_put_to_user((void *)fd, kfd, sizeof(int[2]));

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Waits for a process to change state.
 *
 * This function suspends the execution of the calling process until one of its child processes terminates
 * or a specified process (identified by `pid`) changes its state. The function returns the process ID of the child
 * process that terminated, and provides information about its exit status and resource usage.
 *
 * @param[in]  pid      The process ID of the child process to wait for. The behavior of this parameter can be one of the following:
 *                      - `pid > 0`: Wait for the child process with the specified PID.
 *                      - `pid == 0`: Wait for any child process in the same process group.
 *                      - `pid == -1`: Wait for any child process (default behavior).
 *                      - `pid < -1`: Wait for any child process in the specified process group.
 *
 * @param[out] status   A pointer to an integer where the exit status of the terminated child process will be stored.
 *                      This status can be interpreted using macros such as `WIFEXITED` or `WIFSIGNALED`.
 *
 * @param[in]  options  Options for the wait operation, which can include:
 *                      - `WNOHANG`: Return immediately if no child has exited.
 *                      - `WUNTRACED`: Return if a child has stopped, but not yet terminated.
 *
 * @param[out] ru       A pointer to a `struct rusage` where resource usage information of the child process will be stored.
 *                      This includes information such as CPU time consumed by the child process.
 *
 * @return sysret_t     Returns the process ID of the terminated child on success. In case of failure, a negative error code is returned.
 *
 * @note This function is useful for monitoring and cleaning up child processes in parent-child relationships.
 *       The `status` value can be further analyzed to determine if the child process terminated normally or due to a signal.
 *
 * @see sys_waitpid(), sys_fork(), sys_exit()
 */
sysret_t sys_wait4(pid_t pid, int *status, int options, struct rusage *ru)
{
    return lwp_waitpid(pid, status, options, ru);
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
                if(ret != 0)
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

struct rlimit {
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
    unsigned long krlim[2] = {0, 0};

    if (!lwp_user_accessable((void *)rlim, sizeof(unsigned long [2])))
    {
        return -EFAULT;
    }

    if (lwp_get_from_user(krlim, rlim, sizeof(unsigned long [2])) != sizeof(unsigned long [2]))
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

    lwp_put_to_user((void *)rlim, krlim, sizeof(unsigned long [2]));

    return (ret < 0 ? GET_ERRNO() : ret);
}

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
ssize_t sys_readlink(char* path, char *buf, size_t bufsz)
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

    copy_path = (char*)rt_malloc(len + 1);
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

    for (int i = 0;i < size * 8; i++)
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
            for(int i = 0; i < RT_CPUS_NR; i++)
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
    struct sysinfo kinfo = {0};
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

    thread = lwp_tid_get_thread_and_inc_ref(tid);

    if (thread)
    {
        ret = rt_thread_control(thread, RT_THREAD_CTRL_CHANGE_PRIORITY, (void *)&sched_param->sched_priority);
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
    if(policy < 0)
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
    if(policy < 0)
    {
        SET_ERRNO(EINVAL);
        return -rt_get_errno();
    }
    return 0;
}

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

    thread = lwp_tid_get_thread_and_inc_ref(tid);
    ret = rt_thread_control(thread, RT_THREAD_CTRL_CHANGE_PRIORITY, (void *)&sched_param->sched_priority);
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

/**
 * @brief Open a message queue.
 *
 * This function opens a message queue for communication between processes.
 * It can create a new message queue or open an existing one, depending on the specified
 * flags.
 *
 * @param[in] name  The name of the message queue. The name should be a null-terminated
 *                  string and is subject to system-specific naming conventions.
 * @param[in] flags Flags that control the behavior of the message queue. Common flags include:
 *                  - `O_CREAT`: Create the message queue if it does not exist.
 *                  - `O_EXCL`: Fail if the message queue already exists.
 *                  - `O_RDONLY`: Open the queue for reading.
 *                  - `O_WRONLY`: Open the queue for writing.
 *                  - `O_RDWR`: Open the queue for both reading and writing.
 * @param[in] mode  The mode to be applied when creating the message queue, which defines
 *                  the permissions for the message queue (e.g., read, write).
 * @param[in] attr  A pointer to a `struct mq_attr` that defines the attributes of the
 *                  message queue, such as the maximum number of messages and the size of
 *                  each message. If `NULL`, default values are used.
 *
 * @return mqd_t Returns a non-negative file descriptor for the message queue on success.
 *               On failure, returns `-1` and sets `errno` to indicate the error.
 *
 * @note If the message queue is created, its attributes (such as the maximum number of
 *       messages and message size) must be defined in the `mq_attr` structure. If the
 *       `O_CREAT` flag is not specified and the queue does not exist, the function will
 *       return `-1`.
 */
mqd_t sys_mq_open(const char *name, int flags, mode_t mode, struct mq_attr *attr)
{
    mqd_t mqdes;
    sysret_t ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    rt_size_t len = 0;
    struct mq_attr attr_k;

    len = lwp_user_strlen(name);
    if (!len)
        return (mqd_t)-EINVAL;

    kname = (char *)kmem_get(len + 1);
    if (!kname)
        return (mqd_t)-ENOMEM;

    if (attr == NULL)
    {
        attr_k.mq_maxmsg = 10;
        attr_k.mq_msgsize = 8192;
        attr_k.mq_flags = 0;
        attr = &attr_k;
    }
    else
    {
        if (!lwp_get_from_user(&attr_k, (void *)attr, sizeof(struct mq_attr)))
            return -EINVAL;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    mqdes = mq_open(kname, flags, mode, &attr_k);
    if (mqdes == -1)
    {
        ret = GET_ERRNO();
    }
    lwp_put_to_user(attr, &attr_k, sizeof(struct mq_attr));
    kmem_put(kname);
#else
    mqdes = mq_open(name, flags, mode, attr);
#endif
    if (mqdes == -1)
        return (mqd_t)ret;
    else
        return mqdes;
}

/**
 * @brief Remove a message queue.
 *
 * This function removes a message queue identified by its name. If the message queue
 * is open by any process, it will be removed only when all the processes close their
 * file descriptors associated with the message queue.
 *
 * @param[in] name The name of the message queue to be removed. It should be a null-terminated
 *                 string that conforms to system-specific naming conventions.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative
 *                  error code.
 *
 * @note After a successful call, the message queue is removed from the system. However,
 *       the removal will not take effect until all processes close their file descriptors
 *       associated with the queue. The function will fail if the message queue is still
 *       open by other processes.
 */
sysret_t sys_mq_unlink(const char *name)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    rt_size_t len = 0;

    len = lwp_user_strlen(name);
    if (!len)
        return -EINVAL;
    kname = (char *)kmem_get(len + 1);
    if (!kname)
        return -ENOMEM;

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = mq_unlink(kname);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }
    kmem_put(kname);
    return ret;
#else
    ret = mq_unlink(name);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Send a message to a message queue with a timeout.
 *
 * This function sends a message to the specified message queue, but it allows the sender
 * to specify a timeout. If the message queue is full, the function will block until either
 * space becomes available or the specified timeout expires. If the timeout expires without
 * space being available, the function returns an error.
 *
 * @param[in] mqd   The message queue descriptor returned by `sys_mq_open`.
 * @param[in] msg   A pointer to the message to be sent.
 * @param[in] len   The length of the message to send.
 * @param[in] prio  The priority of the message (higher values indicate higher priority).
 * @param[in] at    A pointer to a `timespec` structure that specifies the absolute timeout.
 *                  If the timeout expires before the message can be sent, the function returns
 *                  an error.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error
 *                  code.
 *
 * @note The function uses the `timespec` structure to specify the absolute timeout. The
 *       `at` parameter should indicate the time at which the operation should time out.
 *       If the timeout is `NULL`, the function will not apply any timeout (it will block
 *       indefinitely until the message is sent).
 *
 * @see sys_mq_send
 */
sysret_t sys_mq_timedsend(mqd_t mqd, const char *msg, size_t len, unsigned prio, const struct timespec *at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kmsg = RT_NULL;
    struct timespec at_k;

    kmsg = (char *)kmem_get(len + 1);
    if (!kmsg)
        return -ENOMEM;

    lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec));
    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    ret = mq_timedsend(mqd, kmsg, len, prio, &at_k);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedsend(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Receive a message from a message queue with a timeout.
 *
 * This function attempts to receive a message from the specified message queue, but it
 * allows the receiver to specify a timeout. If the queue is empty, the function will block
 * until either a message becomes available or the specified timeout expires. If the timeout
 * expires without receiving a message, the function returns an error.
 *
 * @param[in] mqd    The message queue descriptor returned by `sys_mq_open`.
 * @param[out] msg   A pointer to the buffer where the received message will be stored.
 * @param[in] len    The maximum length of the buffer to store the received message.
 * @param[out] prio  A pointer to an unsigned integer that will be set to the priority
 *                   of the received message.
 * @param[in] at     A pointer to a `timespec` structure that specifies the absolute timeout.
 *                   If the timeout expires before a message is received, the function will
 *                   return an error.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The function uses the `timespec` structure to specify the absolute timeout. The
 *       `at` parameter should indicate the time at which the operation should time out.
 *       If the timeout is `NULL`, the function will block indefinitely until a message is
 *       received.
 *
 * @see sys_mq_receive
 */
sysret_t sys_mq_timedreceive(mqd_t mqd, char *restrict msg, size_t len, unsigned *restrict prio, const struct timespec *restrict at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *restrict kmsg = RT_NULL;

    struct timespec at_k;

    kmsg = (char *restrict)kmem_get(len + 1);
    if (!kmsg)
        return -ENOMEM;

    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    if (at == RT_NULL)
    {
        ret = mq_timedreceive(mqd, kmsg, len, prio, RT_NULL);
    }
    else
    {
        if (!lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec)))
            return -EINVAL;
        ret = mq_timedreceive(mqd, kmsg, len, prio, &at_k);
    }

    if (ret > 0)
        lwp_put_to_user(msg, kmsg, len + 1);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedreceive(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Set up asynchronous notification for a message queue.
 *
 * This function configures asynchronous notification for a message queue. When a message
 * is available in the queue, the system can notify the calling process through a signal
 * or another method specified in the `sigevent` structure. This is typically used to allow
 * a process to be notified when a message arrives without having to block in the receive call.
 *
 * @param[in] mqd  The message queue descriptor returned by `sys_mq_open`.
 * @param[in] sev  A pointer to a `sigevent` structure that specifies the notification
 *                 mechanism to be used when a message is received. It could include
 *                 signals or other notification types such as event flags or message passing.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function enables asynchronous notification, but the specific behavior depends
 *       on the configuration specified in the `sev` parameter, which could involve signals
 *       or other forms of notification.
 *
 * @see sys_mq_send, sys_mq_timedreceive
 */
sysret_t sys_mq_notify(mqd_t mqd, const struct sigevent *sev)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct sigevent sev_k;
    lwp_get_from_user(&sev_k, (void *)sev, sizeof(struct timespec));
    ret = mq_notify(mqd, &sev_k);
#else
    ret = mq_notify(mqd, sev);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Get or set attributes of a message queue.
 *
 * This function allows you to get or set the attributes of an existing message queue.
 * If the `new` attribute structure is non-NULL, it updates the message queue with the new
 * attributes. Otherwise, If the `old` attribute structure is non-NULL, it will return the current
 * attributes of the message queue.
 *
 * @param[in] mqd  The message queue descriptor returned by `sys_mq_open`.
 * @param[in] new  A pointer to a `mq_attr` structure containing the new attributes to set.
 *                 If `NULL`, the function will not modify the message queue attributes.
 * @param[out] old A pointer to a `mq_attr` structure where the current message queue
 *                 attributes will be returned. If `NULL`, the current attributes will not
 *                 be returned.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The `mq_attr` structure contains parameters like the maximum number of messages,
 *       the maximum message size, and other attributes that control the behavior of the
 *       message queue.
 *
 * @see sys_mq_open, sys_mq_notify
 */
sysret_t sys_mq_getsetattr(mqd_t mqd, const struct mq_attr *restrict new, struct mq_attr *restrict old)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct mq_attr);
    struct mq_attr *restrict knew = NULL;
    struct mq_attr *restrict kold = NULL;

    if (new != RT_NULL)
    {
        if (!lwp_user_accessable((void *)new, size))
            return -EFAULT;
        knew = kmem_get(size);
        if (!knew)
            return -ENOMEM;
        lwp_get_from_user(knew, (void *)new, size);
    }

    if (!lwp_user_accessable((void *)old, size))
        return -EFAULT;
    kold = kmem_get(size);
    if (!kold)
        return -ENOMEM;

    lwp_get_from_user(kold, (void *)old, size);
    ret = mq_setattr(mqd, knew, kold);
    if (ret != -1)
        lwp_put_to_user(old, kold, size);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kold);
    if (new != RT_NULL)
        kmem_put(knew);

    return ret;
#else
    ret = mq_setattr(mqd, new, old);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Close a message queue descriptor.
 *
 * This function closes a message queue descriptor. After calling this function, the
 * descriptor can no longer be used to interact with the message queue. Any resources
 * associated with the descriptor are released. If the message queue was opened with the
 * `O_CLOEXEC` flag, it will be automatically closed when the calling process executes
 * an `exec` system call.
 *
 * @param[in] mqd  The message queue descriptor to be closed. It was previously returned
 *                 by `sys_mq_open`.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @see sys_mq_open, sys_mq_unlink
 */
sysret_t sys_mq_close(mqd_t mqd)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    ret = mq_close(mqd);
#else
    ret = mq_close(mqd);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

#define ICACHE (1<<0)
#define DCACHE (1<<1)
#define BCACHE (ICACHE|DCACHE)

/**
 * @brief Flush the cache for a specified memory region.
 *
 * This function flushes the cache for a specified memory region. It is commonly used
 * to ensure that the contents of a memory region are written back to the main memory
 * or that stale cache entries are invalidated. The cache operation can be controlled
 * by the `cache` parameter to determine whether to clean or invalidate the cache.
 *
 * @param[in] addr   The starting address of the memory region to flush.
 * @param[in] size   The size of the memory region to flush, in bytes.
 * @param[in] cache  A flag to specify the cache operation:
 *                   - `CACHE_CLEAN`: Clean the cache (write back to memory).
 *                   - `CACHE_INVALIDATE`: Invalidate the cache (discard cached data).
 *                   - `CACHE_FLUSH`: Both clean and invalidate the cache.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is typically used in low-level operations or in systems where
 *       cache coherence between memory and cache is critical.
 */
rt_weak sysret_t sys_cacheflush(void *addr, int size, int cache)
{
    if (!lwp_user_accessable(addr, size))
        return -EFAULT;

    if (((size_t)addr < (size_t)addr + size) &&
        ((size_t)addr >= USER_VADDR_START) &&
        ((size_t)addr + size < USER_VADDR_TOP))
    {
        if ((cache & DCACHE))
        {
            rt_hw_cpu_dcache_clean_and_invalidate(addr, size);
        }

        if ((cache & ICACHE))
        {
            rt_hw_cpu_icache_invalidate(addr, size);
        }

        return 0;
    }
    return -EFAULT;
}

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
    struct utsname utsbuff = {0};
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

/**
 * @brief Get filesystem statistics.
 *
 * This function retrieves statistics about the filesystem at the specified path,
 * storing the results in the provided `statfs` structure. It can be used to obtain
 * information such as the total number of blocks, free blocks, available inodes, etc.
 *
 * @param[in]  path  The path to the filesystem to query. If the path is the root directory
 *                   (`"/"`), it returns statistics for the root filesystem.
 * @param[out] buf   A pointer to a `statfs` structure where the filesystem statistics will
 *                   be stored. This structure includes information such as:
 *                   - `f_type`: The type of the filesystem.
 *                   - `f_bsize`: The optimal block size for I/O operations.
 *                   - `f_blocks`: Total number of blocks in the filesystem.
 *                   - `f_bfree`: Number of free blocks.
 *                   - `f_bavail`: Number of free blocks available to non-superuser.
 *                   - `f_files`: Total number of file nodes (inodes).
 *                   - `f_ffree`: Number of free inodes.
 *                   - `f_favail`: Number of inodes available to non-superuser.
 *                   - `f_flag`: Flags describing the filesystem.
 *                   - `f_namelen`: Maximum length of a filename.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is useful for determining the available space and file system
 *       characteristics of a mounted filesystem.
 *
 * @see sys_fstatfs
 */
sysret_t sys_statfs(const char *path, struct statfs *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)path, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(statfs(copy_path, &statfsbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

/**
 * @brief Get extended filesystem statistics (64-bit).
 *
 * This function retrieves extended statistics about the filesystem at the specified path,
 * using 64-bit values for larger filesystems or filesystems with a large number of blocks or inodes.
 * The information is stored in the provided `statfs` structure, which includes details such as total
 * blocks, free blocks, available inodes, etc.
 *
 * @param[in]  path  The path to the filesystem to query. Typically, this would be the root directory
 *                   (`"/"`) for the root filesystem, or any other directory on the filesystem.
 * @param[in]  sz    The size of the `statfs` structure. This parameter allows for future extensions
 *                   of the `statfs` structure without breaking compatibility with older applications.
 * @param[out] buf   A pointer to a `statfs` structure where the extended filesystem statistics
 *                   will be stored. This structure includes information such as:
 *                   - `f_bsize`: The optimal block size for I/O operations.
 *                   - `f_blocks`: Total number of blocks in the filesystem.
 *                   - `f_bfree`: Number of free blocks.
 *                   - `f_bavail`: Number of free blocks available to non-superuser.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is particularly useful for querying large filesystems or filesystems with
 *       64-bit addresses or data values, and is an extended version of the standard `sys_statfs`.
 *
 * @see sys_statfs
 */
sysret_t sys_statfs64(const char *path, size_t sz, struct statfs *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    if (sz != sizeof(struct statfs))
    {
        return -EINVAL;
    }

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)path, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(statfs(copy_path, &statfsbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

/**
 * @brief Get filesystem statistics for a file descriptor.
 *
 * This function retrieves statistics about the filesystem containing the file referred to by the
 * file descriptor `fd`. The information is stored in the provided `statfs` structure, which includes
 * details such as total blocks, free blocks, available inodes, etc.
 *
 * @param[in]  fd    The file descriptor referring to an open file. The file descriptor must be
 *                   valid and represent a file on a mounted filesystem.
 * @param[out] buf   A pointer to a `statfs` structure where the filesystem statistics will be
 *                   stored. This structure includes information such as:
 *                   - `f_bsize`: The optimal block size for I/O operations.
 *                   - `f_blocks`: Total number of blocks in the filesystem.
 *                   - `f_bfree`: Number of free blocks.
 *                   - `f_bavail`: Number of free blocks available to non-superuser.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is useful for obtaining filesystem information about a specific file
 *       represented by its file descriptor, rather than querying the filesystem associated with
 *       a specific path.
 *
 * @see sys_statfs
 */
sysret_t sys_fstatfs(int fd, struct statfs *buf)
{
    int ret = 0;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    ret = _SYS_WRAP(fstatfs(fd, &statfsbuff));

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

/**
 * @brief Get 64-bit filesystem statistics for a file descriptor.
 *
 * This function retrieves 64-bit statistics about the filesystem containing the file referred to by
 * the file descriptor `fd`. The statistics are stored in the provided `statfs` structure, which
 * includes details such as total blocks, free blocks, available inodes, etc. The function differs
 * from `sys_fstatfs` in that it supports 64-bit values for filesystem sizes and counts.
 *
 * @param[in]  fd    The file descriptor referring to an open file. The file descriptor must be
 *                   valid and represent a file on a mounted filesystem.
 * @param[in]  sz    The size of the `statfs` structure (typically used to ensure compatibility with
 *                   different versions of the structure).
 * @param[out] buf   A pointer to a `statfs` structure where the filesystem statistics will be
 *                   stored. This structure includes information such as:
 *                   - `f_bsize`: The optimal block size for I/O operations.
 *                   - `f_blocks`: Total number of blocks in the filesystem (64-bit).
 *                   - `f_bfree`: Number of free blocks (64-bit).
 *                   - `f_bavail`: Number of free blocks available to non-superuser (64-bit).
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 * @note This function is particularly useful for systems supporting 64-bit filesystem statistics.
 *       It provides extended accuracy for large filesystems, including those with very large
 *       numbers of blocks or inodes.
 *
 * @see sys_fstatfs
 */
sysret_t sys_fstatfs64(int fd, size_t sz, struct statfs *buf)
{
    int ret = 0;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    if (sz != sizeof(struct statfs))
    {
        return -EINVAL;
    }

    ret = _SYS_WRAP(fstatfs(fd, &statfsbuff));

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

static char *_cp_from_usr_string(char *dst, char *src, size_t length)
{
    char *rc;
    size_t copied_bytes;
    if (length)
    {
        copied_bytes = lwp_get_from_user(dst, src, length);
        dst[copied_bytes] = '\0';
        rc = dst;
    }
    else
    {
        rc = RT_NULL;
    }
    return rc;
}

/**
 * @brief Mount a filesystem.
 *
 * This function mounts a filesystem onto a specified directory. It allows for mounting various
 * types of filesystems, including but not limited to `ext4`, `nfs`, and `tmpfs`. The function
 * allows the specification of the source device, the target mount point, and additional parameters
 * such as filesystem type, mount flags, and extra data.
 *
 * @param[in]  source        The source of the filesystem, which can be a device (e.g., `/dev/sda1`)
 *                           or a network resource (e.g., a NFS share). For certain filesystems like
 *                           `tmpfs`, this can be `NULL`.
 * @param[in]  target        The target directory where the filesystem will be mounted.
 *                           This should be an existing empty directory.
 * @param[in]  filesystemtype The type of filesystem to mount, e.g., `ext4`, `tmpfs`, `nfs`, etc.
 * @param[in]  mountflags    Flags that control the mount operation, such as `MS_RDONLY` for read-only
 *                           mounts or `MS_NODEV` to prevent device files from being created.
 * @param[in]  data          Optional data that is passed to the filesystem's mount handler. This
 *                           may be used for setting up specific parameters for the filesystem type.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note Mounting a filesystem on an existing mount point can replace the existing filesystem at that
 *       location. Make sure the target directory is empty before mounting to avoid any conflicts.
 */
sysret_t sys_mount(char *source, char *target, char *filesystemtype,
                   unsigned long mountflags, void *data)
{
    char *kbuffer, *ksource, *ktarget, *kfs;
    size_t len_source, len_target, len_fs;
    char *tmp = NULL;
    int ret = 0;
    struct stat buf = {0};
    char *dev_fullpath = RT_NULL;

    len_source = source ? lwp_user_strlen(source) : 0;
    if (len_source < 0)
        return -EINVAL;

    len_target = target ? lwp_user_strlen(target) : 0;
    if (len_target <= 0)
        return -EINVAL;

    len_fs = filesystemtype ? lwp_user_strlen(filesystemtype) : 0;
    if (len_fs < 0)
        return -EINVAL;

    kbuffer = (char *)rt_malloc(len_source + 1 + len_target + 1 + len_fs + 1);
    if (!kbuffer)
    {
        return -ENOMEM;
    }

    /* get parameters from user space */
    ksource = kbuffer;
    ktarget = ksource + len_source + 1;
    kfs = ktarget + len_target + 1;
    ksource = _cp_from_usr_string(ksource, source, len_source);
    ktarget = _cp_from_usr_string(ktarget, target, len_target);
    kfs = _cp_from_usr_string(kfs, filesystemtype, len_fs);

    if (mountflags & MS_REMOUNT)
    {
        ret = dfs_remount(ktarget, mountflags, data);
    }
    else
    {
        if (strcmp(kfs, "nfs") == 0)
        {
            tmp = ksource;
            ksource = NULL;
        }
        if (strcmp(kfs, "tmp") == 0)
        {
            ksource = NULL;
        }

        if (ksource && !dfs_file_stat(ksource, &buf) && S_ISBLK(buf.st_mode))
        {
            dev_fullpath = dfs_normalize_path(RT_NULL, ksource);
            RT_ASSERT(rt_strncmp(dev_fullpath, "/dev/", sizeof("/dev/") - 1) == 0);
            ret = dfs_mount(dev_fullpath + sizeof("/dev/") - 1, ktarget, kfs, 0, tmp);
        }
        else
        {
            ret = dfs_mount(ksource, ktarget, kfs, 0, tmp);
        }

        if (ret < 0)
        {
            ret = -rt_get_errno();
        }
    }

    rt_free(kbuffer);
    rt_free(dev_fullpath);
    return ret;
}

/**
 * @brief Unmount a filesystem.
 *
 * This function unmounts a previously mounted filesystem from a specified target directory or file.
 * It removes the filesystem from the system, making the resources associated with it available for
 * other uses. It can also support additional flags to control the unmounting behavior.
 *
 * @param[in]  __special_file The target directory or mount point from which the filesystem is to be
 *                            unmounted. This should be a valid mount point that was previously mounted.
 * @param[in]  __flags        Flags that control the unmounting behavior. Common flags include:
 *                            - `MNT_FORCE`: Forces the unmount even if the filesystem is busy.
 *                            - `MNT_DETACH`: Detaches the filesystem, allowing it to be unmounted
 *                              asynchronously.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The `MNT_FORCE` flag should be used with caution, as it may result in data loss or corruption
 *       if there are pending writes or active processes using the filesystem.
 *
 * @see sys_mount
 */
sysret_t sys_umount2(char *__special_file, int __flags)
{
    char *copy_special_file;
    size_t len_special_file, copy_len_special_file;
    int ret = 0;

    len_special_file = lwp_user_strlen(__special_file);
    if (len_special_file <= 0)
    {
        return -EFAULT;
    }

    copy_special_file = (char*)rt_malloc(len_special_file + 1);
    if (!copy_special_file)
    {
        return -ENOMEM;
    }

    copy_len_special_file = lwp_get_from_user(copy_special_file, __special_file, len_special_file);
    copy_special_file[copy_len_special_file] = '\0';

    ret = dfs_unmount(copy_special_file);
    rt_free(copy_special_file);

    return ret;
}

/**
 * @brief Create a new hard link to an existing file.
 *
 * This function creates a new hard link to an existing file, making the file accessible from
 * multiple filenames. The new link points to the same inode as the existing file, meaning
 * both names refer to the same underlying data. The link count for the file is incremented.
 *
 * @param[in]  existing The path to the existing file. It must be an absolute or relative path
 *                      to a file that already exists.
 * @param[in]  new      The path to the new link to be created. This can be a new filename or
 *                      an existing directory where the link will be placed.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note Hard links share the same inode number, meaning changes to the data of the file via one
 *       link will be reflected in all hard links. Deleting any of the links will not remove the
 *       file data until all links are deleted.
 */
sysret_t sys_link(const char *existing, const char *new)
{
    int ret = -1;
    int err = 0;
#ifdef RT_USING_DFS_V2
#ifdef ARCH_MM_MMU
    int len = 0;
    char *kexisting = RT_NULL;
    char *knew = RT_NULL;

    len = lwp_user_strlen(existing);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kexisting = (char *)kmem_get(len + 1);
    if (!kexisting)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kexisting, (void *)existing, len + 1) != (len + 1))
    {
        kmem_put(kexisting);
        return -EINVAL;
    }

    len = lwp_user_strlen(new);
    if (len <= 0)
    {
        kmem_put(kexisting);
        return -EFAULT;
    }

    knew = (char *)kmem_get(len + 1);
    if (!knew)
    {
        kmem_put(kexisting);
        return -ENOMEM;
    }

    if (lwp_get_from_user(knew, (void *)new, len + 1) != (len + 1))
    {
        kmem_put(knew);
        kmem_put(kexisting);
        return -EINVAL;
    }

    ret = dfs_file_link(kexisting, knew);
    if(ret  < 0)
    {
        err = GET_ERRNO();
    }

    kmem_put(knew);
    kmem_put(kexisting);
#else
    ret = dfs_file_link(existing, new);
#endif
#else
    SET_ERRNO(EFAULT);
    err = GET_ERRNO();
#endif

    return (err < 0 ? err : ret);
}

/**
 * @brief Create a symbolic link to an existing file or directory.
 *
 * This function creates a new symbolic link, which is a special file that contains a reference
 * to another file or directory. The symbolic link allows for easy redirection or aliasing of
 * file paths. Unlike a hard link, a symbolic link can point to a file or directory across
 * different file systems.
 *
 * @param[in]  existing The path to the existing file or directory that the symbolic link
 *                      will refer to. It must be an absolute or relative path.
 * @param[in]  new      The path to the new symbolic link to be created. This must be a valid
 *                      path where the link will be placed.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note A symbolic link is distinct from a hard link in that it points to the path of the target
 *       file or directory, rather than directly to the inode. If the target file or directory is
 *       removed or moved, the symbolic link will become "broken" and will not resolve to a valid
 *       location.
 */
sysret_t sys_symlink(const char *existing, const char *new)
{
    int ret = -1;
    int err = 0 ;
#ifdef ARCH_MM_MMU

    ret = lwp_user_strlen(existing);
    if (ret <= 0)
    {
        return -EFAULT;
    }

    ret = lwp_user_strlen(new);
    if (ret <= 0)
    {
        return -EFAULT;
    }
#endif
#ifdef RT_USING_DFS_V2
    ret = dfs_file_symlink(existing, new);
    if(ret < 0)
    {
        err = GET_ERRNO();
    }
#else
    SET_ERRNO(EFAULT);
#endif
    return (err < 0 ? err : ret);
}

/**
 * @brief Create an event file descriptor.
 *
 * This function creates an eventfd, which is a file descriptor used for event notification.
 * Eventfd is a simple mechanism to notify threads or processes about certain events using
 * an integer counter. It is typically used for inter-process communication (IPC) or
 * synchronization purposes, where one thread or process increments the counter to signal
 * another thread or process.
 *
 * @param[in] count  Initial value for the eventfd counter. It can be set to a non-zero
 *                   value to initialize the counter to that value.
 * @param[in] flags  Flags that control the behavior of the eventfd. Valid flags include:
 *                   - `EFD_CLOEXEC`: Set the close-on-exec flag for the eventfd.
 *                   - `EFD_NONBLOCK`: Set the non-blocking flag for the eventfd.
 *
 * @return sysret_t On success, returns a valid file descriptor referring to the eventfd. On
 *                  failure, returns a negative error code.
 *
 * @note Eventfd can be used for both counting and signaling purposes. It provides
 *       efficient signaling between threads or processes.
 */
sysret_t sys_eventfd2(unsigned int count, int flags)
{
    int ret;

    ret = eventfd(count, flags);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Create an epoll instance.
 *
 * This function creates an epoll instance, which is used for monitoring multiple file descriptors
 * to see if I/O is possible on them. It allows a program to efficiently wait for events such as
 * data being available for reading or space becoming available for writing. Epoll provides a scalable
 * mechanism for managing large numbers of file descriptors.
 *
 * @param[in] flags  Flags that control the behavior of the epoll instance. The valid flags include:
 *                   - `EPOLL_CLOEXEC`: Set the close-on-exec flag for the epoll instance.
 *                   - `EPOLL_NONBLOCK`: Set the non-blocking flag for the epoll instance.
 *
 * @return sysret_t On success, returns a file descriptor for the epoll instance. On failure,
 *                  returns a negative error code.
 *
 * @note The `sys_epoll_create1` function is similar to `sys_epoll_create`, but it allows for
 *       additional control over the epoll instance creation via flags.
 */
sysret_t sys_epoll_create1(int flags)
{
    int ret;

    ret = epoll_create(flags);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Control an epoll instance.
 *
 * This function performs control operations on an epoll instance, such as adding, modifying,
 * or removing file descriptors from the epoll instance's interest list.
 *
 * @param[in] fd    The file descriptor of the epoll instance created using `sys_epoll_create` or `sys_epoll_create1`.
 * @param[in] op    The operation to perform on the epoll instance. It can be one of the following:
 *                  - `EPOLL_CTL_ADD`: Add the specified file descriptor to the epoll interest list.
 *                  - `EPOLL_CTL_MOD`: Modify the event mask of an existing file descriptor in the epoll interest list.
 *                  - `EPOLL_CTL_DEL`: Remove the specified file descriptor from the epoll interest list.
 * @param[in] fd2   The file descriptor to be added, modified, or removed from the epoll interest list.
 * @param[in] ev    A pointer to an `epoll_event` structure that describes the event to be associated with `fd2`.
 *                  This parameter is required for `EPOLL_CTL_ADD` and `EPOLL_CTL_MOD`, but not for `EPOLL_CTL_DEL`.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note This function is typically used to manage the set of file descriptors monitored by an epoll instance.
 */
sysret_t sys_epoll_ctl(int fd, int op, int fd2, struct epoll_event *ev)
{
    int ret = 0;
    struct epoll_event *kev = RT_NULL;

    if (ev)
    {
        if (!lwp_user_accessable((void *)ev, sizeof(struct epoll_event)))
        return -EFAULT;

        kev = kmem_get(sizeof(struct epoll_event));
        if (kev == RT_NULL)
        {
            return -ENOMEM;
        }

        if (lwp_get_from_user(kev, ev, sizeof(struct epoll_event)) != sizeof(struct epoll_event))
        {
            kmem_put(kev);
            return -EINVAL;
        }

        ret = epoll_ctl(fd, op, fd2, kev);

        kmem_put(kev);
    }
    else
    {
         ret = epoll_ctl(fd, op, fd2, RT_NULL);
    }

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Wait for events on an epoll file descriptor, with the ability to block for specific signals.
 *
 * This function waits for events on an epoll file descriptor. It blocks until one or more events
 * are available or a timeout occurs. In addition to waiting for events, it can also block for specific signals
 * as specified by the `sigs` argument.
 *
 * @param[in] fd          The file descriptor of the epoll instance, created using `sys_epoll_create` or `sys_epoll_create1`.
 * @param[out] ev         A pointer to an array of `epoll_event` structures that will receive the events that have occurred.
 * @param[in] cnt         The maximum number of events to return. This specifies the size of the `ev` array.
 * @param[in] to          The timeout in milliseconds. A negative value means no timeout, and `0` means non-blocking.
 * @param[in] sigs        A pointer to a signal set (`sigset_t`) that specifies the signals to block during the wait.
 *                        If `NULL`, no signals are blocked.
 * @param[in] sigsetsize  The size of the signal set (`sigs`) in bytes. This should be the size of `sigset_t` if `sigs` is not `NULL`.
 *
 * @return sysret_t On success, returns the number of events returned (may be `0` if the timeout expires with no events).
 *                  On failure, returns a negative error code.
 *
 * @note This function is similar to `sys_epoll_wait`, but it also allows for signal handling, blocking the calling thread
 *       from receiving signals specified in the `sigs` set while waiting for events.
 */
sysret_t sys_epoll_pwait(int fd,
        struct epoll_event *ev,
        int cnt,
        int to,
        const sigset_t *sigs,
        unsigned long sigsetsize)
{
    int ret = 0;
    struct epoll_event *kev = RT_NULL;
    sigset_t *ksigs = RT_NULL;

    if (!lwp_user_accessable((void *)ev, cnt * sizeof(struct epoll_event)))
        return -EFAULT;

    kev = kmem_get(cnt * sizeof(struct epoll_event));
    if (kev == RT_NULL)
    {
        return -ENOMEM;
    }

    if (sigs != RT_NULL)
    {
        if (!lwp_user_accessable((void *)sigs, sizeof(sigset_t)))
        {
            kmem_put(kev);
            return -EFAULT;
        }

        ksigs = kmem_get(sizeof(sigset_t));
        if (ksigs == RT_NULL)
        {
            kmem_put(kev);
            return -ENOMEM;
        }

        if (lwp_get_from_user(ksigs, (void *)sigs, sizeof(sigset_t)) != sizeof(sigset_t))
        {
            kmem_put(kev);
            kmem_put(ksigs);
            return -EINVAL;
        }
    }

    ret = epoll_pwait(fd, kev, cnt, to, ksigs);

    if (ret > 0)
    {
        lwp_put_to_user((void *)ev, kev, ret * sizeof(struct epoll_event));
    }

    if (sigs != RT_NULL)
        kmem_put(ksigs);

    kmem_put(kev);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Truncate a file to a specified length.
 *
 * This function resizes the file associated with the given file descriptor `fd` to the specified length.
 * If the current size of the file is greater than the specified length, the file is truncated. If the file is smaller,
 * it is extended, and the new space is initialized to zero.
 *
 * @param[in] fd       The file descriptor referring to the file to truncate. This must be a valid open file descriptor.
 * @param[in] length   The new length of the file. The file will be truncated or extended to this size.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The file descriptor `fd` must be opened with write permissions for this operation to succeed.
 */
sysret_t sys_ftruncate(int fd, size_t length)
{
    int ret;

    ret = ftruncate(fd, length);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Set file access and modification times.
 *
 * This function updates the access and modification times of a file or directory referenced by `__fd` or `__path`.
 * If `__fd` is a valid file descriptor, the times will be applied to the file or directory it refers to.
 * If `__fd` is `AT_FDCWD`, the times will be applied to the file or directory specified by `__path`.
 * The `__times` argument consists of two `timespec` values: the first represents the access time,
 * and the second represents the modification time. If `__times` is `NULL`, the current time is used.
 *
 * @param[in] __fd       The file descriptor of the file or directory to modify, or `AT_FDCWD` to modify using `__path`.
 * @param[in] __path     The path to the file or directory to modify. Ignored if `__fd` is not `AT_FDCWD`.
 * @param[in] __times    An array of two `timespec` structures. The first element is the access time, and the second is the modification time.
 *                       If `__times` is `NULL`, the current time is used for both access and modification times.
 * @param[in] __flags    Flags to modify behavior. Supported flags include:
 *                       - `AT_SYMLINK_NOFOLLOW`: Do not follow symbolic links.
 *                       - `AT_NO_AUTOMOUNT`: Do not trigger automounting.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note This function modifies both access and modification times of files, and may affect file system timestamps.
 */
sysret_t sys_utimensat(int __fd, const char *__path, const struct timespec __times[2], int __flags)
{
#ifdef RT_USING_DFS_V2
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kpath = RT_NULL;

    len = lwp_user_strlen(__path);
    if (len <= 0)
    {
        return -EINVAL;
    }

    kpath = (char *)kmem_get(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kpath, (void *)__path, len + 1);
    ret = utimensat(__fd, kpath, __times, __flags);

    kmem_put(kpath);

    return ret;
#else
    if (!lwp_user_accessable((void *)__path, 1))
    {
        return -EFAULT;
    }
    int ret = utimensat(__fd, __path, __times, __flags);
    return ret;
#endif
#else
    return -1;
#endif
}

/**
 * @brief Change file permissions.
 *
 * This function changes the permissions of a file or directory specified by the `pathname`.
 * The new permissions are specified using the `mode` argument, which is a bitwise OR of permission bits.
 * The permissions apply to the file owner, group, and others, depending on the value of `mode`.
 *
 * @param[in] pathname  The path to the file or directory whose permissions are to be changed.
 * @param[in] mode      The new permissions to set, represented as a bitwise OR of permission flags.
 *                      For example, `S_IRUSR`, `S_IWUSR`, `S_IRGRP`, etc.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note If the file or directory is a symbolic link, this function will modify the permissions of the symbolic link itself,
 *       not the target file or directory.
 */
sysret_t sys_chmod(const char *pathname, mode_t mode)
{
    char *copy_file;
    size_t len_file, copy_len_file;
    struct dfs_attr attr = {0};
    int ret = 0;

    len_file = lwp_user_strlen(pathname);
    if (len_file <= 0)
    {
        return -EFAULT;
    }

    copy_file = (char*)rt_malloc(len_file + 1);
    if (!copy_file)
    {
        return -ENOMEM;
    }

    copy_len_file = lwp_get_from_user(copy_file, (void *)pathname, len_file);

    attr.st_mode = mode;
    attr.ia_valid |= ATTR_MODE_SET;

    copy_file[copy_len_file] = '\0';
    ret = dfs_file_setattr(copy_file, &attr);
    rt_free(copy_file);

    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Change the ownership of a file or directory.
 *
 * This function changes the owner and/or group of the file or directory specified by `pathname`.
 * The `owner` and `group` parameters represent the new owner and group IDs, respectively. If either
 * parameter is set to `-1`, that aspect (owner or group) will remain unchanged.
 *
 * @param[in] pathname  The path to the file or directory whose ownership is to be changed.
 * @param[in] owner     The new owner ID. If set to `-1`, the owner's ID is not changed.
 * @param[in] group     The new group ID. If set to `-1`, the group's ID is not changed.
 *
 * @return sysret_t On success, returns `0`. On failure, returns a negative error code.
 *
 * @note The caller must have the appropriate permissions (i.e., be the superuser or the file owner)
 *       to change the ownership of a file or directory.
 */
sysret_t sys_chown(const char *pathname, uid_t owner, gid_t group)
{
    char *copy_file;
    size_t len_file, copy_len_file;
    struct dfs_attr attr = {0};
    int ret = 0;

    len_file = lwp_user_strlen(pathname);
    if (len_file <= 0)
    {
        return -EFAULT;
    }

    copy_file = (char*)rt_malloc(len_file + 1);
    if (!copy_file)
    {
        return -ENOMEM;
    }

    copy_len_file = lwp_get_from_user(copy_file, (void *)pathname, len_file);

    if(owner >= 0)
    {
        attr.st_uid = owner;
        attr.ia_valid |= ATTR_UID_SET;
    }

    if(group >= 0)
    {
        attr.st_gid = group;
        attr.ia_valid |= ATTR_GID_SET;
    }

    copy_file[copy_len_file] = '\0';
    ret = dfs_file_setattr(copy_file, &attr);
    rt_free(copy_file);

    return (ret < 0 ? GET_ERRNO() : ret);
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
        return -EINVAL;

    if (!lwp_user_accessable((void *)new, sizeof(struct itimerspec)))
    {
        return -EFAULT;
    }

    knew = kmem_get(sizeof(struct itimerspec));

    if (knew)
    {
        lwp_get_from_user(knew, (void*)new, sizeof(struct itimerspec));

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
        return -EINVAL;

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
        return -EINVAL;

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
sysret_t sys_setitimer(int which, const struct itimerspec *restrict new, struct itimerspec *restrict old)
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
        return -EFAULT;

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
        return -EINVAL;

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
        return -EFAULT;
    if (!lwp_put_to_user(head_ptr, &head, sizeof(struct robust_list_head *)))
        return -EFAULT;

    return 0;
}

const static struct rt_syscall_def func_table[] =
{
    SYSCALL_SIGN(sys_exit),            /* 01 */
    SYSCALL_SIGN(sys_read),
    SYSCALL_SIGN(sys_write),
    SYSCALL_SIGN(sys_lseek),
    SYSCALL_SIGN(sys_open),            /* 05 */
    SYSCALL_SIGN(sys_close),
    SYSCALL_SIGN(sys_ioctl),
    SYSCALL_SIGN(sys_fstat),
    SYSCALL_SIGN(sys_poll),
    SYSCALL_SIGN(sys_nanosleep),       /* 10 */
    SYSCALL_SIGN(sys_gettimeofday),
    SYSCALL_SIGN(sys_settimeofday),
    SYSCALL_SIGN(sys_exec),
    SYSCALL_SIGN(sys_kill),
    SYSCALL_SIGN(sys_getpid),          /* 15 */
    SYSCALL_SIGN(sys_getpriority),
    SYSCALL_SIGN(sys_setpriority),
    SYSCALL_SIGN(sys_sem_create),
    SYSCALL_SIGN(sys_sem_delete),
    SYSCALL_SIGN(sys_sem_take),        /* 20 */
    SYSCALL_SIGN(sys_sem_release),
    SYSCALL_SIGN(sys_mutex_create),
    SYSCALL_SIGN(sys_mutex_delete),
    SYSCALL_SIGN(sys_mutex_take),
    SYSCALL_SIGN(sys_mutex_release),   /* 25 */
    SYSCALL_SIGN(sys_event_create),
    SYSCALL_SIGN(sys_event_delete),
    SYSCALL_SIGN(sys_event_send),
    SYSCALL_SIGN(sys_event_recv),
    SYSCALL_SIGN(sys_mb_create),       /* 30 */
    SYSCALL_SIGN(sys_mb_delete),
    SYSCALL_SIGN(sys_mb_send),
    SYSCALL_SIGN(sys_mb_send_wait),
    SYSCALL_SIGN(sys_mb_recv),
    SYSCALL_SIGN(sys_mq_create),       /* 35 */
    SYSCALL_SIGN(sys_mq_delete),
    SYSCALL_SIGN(sys_mq_send),
    SYSCALL_SIGN(sys_mq_urgent),
    SYSCALL_SIGN(sys_mq_recv),
    SYSCALL_SIGN(sys_thread_create),   /* 40 */
    SYSCALL_SIGN(sys_thread_delete),
    SYSCALL_SIGN(sys_thread_startup),
    SYSCALL_SIGN(sys_thread_self),
    SYSCALL_SIGN(sys_channel_open),
    SYSCALL_SIGN(sys_channel_close),   /* 45 */
    SYSCALL_SIGN(sys_channel_send),
    SYSCALL_SIGN(sys_channel_send_recv_timeout),
    SYSCALL_SIGN(sys_channel_reply),
    SYSCALL_SIGN(sys_channel_recv_timeout),
    SYSCALL_SIGN(sys_enter_critical),  /* 50 */
    SYSCALL_SIGN(sys_exit_critical),

    SYSCALL_USPACE(SYSCALL_SIGN(sys_brk)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_mmap2)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_munmap)),
#ifdef ARCH_MM_MMU
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmget)), /* 55 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmrm)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmat)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmdt)),
#else
#ifdef RT_LWP_USING_SHM
    SYSCALL_SIGN(sys_shm_alloc),      /* 55 */
    SYSCALL_SIGN(sys_shm_free),
    SYSCALL_SIGN(sys_shm_retain),
    SYSCALL_SIGN(sys_notimpl),
#else
    SYSCALL_SIGN(sys_notimpl),      /* 55 */
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#endif /* RT_LWP_USING_SHM */
#endif /* ARCH_MM_MMU */
    SYSCALL_SIGN(sys_device_init),
    SYSCALL_SIGN(sys_device_register), /* 60 */
    SYSCALL_SIGN(sys_device_control),
    SYSCALL_SIGN(sys_device_find),
    SYSCALL_SIGN(sys_device_open),
    SYSCALL_SIGN(sys_device_close),
    SYSCALL_SIGN(sys_device_read),    /* 65 */
    SYSCALL_SIGN(sys_device_write),

    SYSCALL_SIGN(sys_stat),
    SYSCALL_SIGN(sys_thread_find),

    SYSCALL_NET(SYSCALL_SIGN(sys_accept)),
    SYSCALL_NET(SYSCALL_SIGN(sys_bind)),      /* 70 */
    SYSCALL_NET(SYSCALL_SIGN(sys_shutdown)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getpeername)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getsockname)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getsockopt)),
    SYSCALL_NET(SYSCALL_SIGN(sys_setsockopt)), /* 75 */
    SYSCALL_NET(SYSCALL_SIGN(sys_connect)),
    SYSCALL_NET(SYSCALL_SIGN(sys_listen)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recv)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recvfrom)),
    SYSCALL_NET(SYSCALL_SIGN(sys_send)),      /* 80 */
    SYSCALL_NET(SYSCALL_SIGN(sys_sendto)),
    SYSCALL_NET(SYSCALL_SIGN(sys_socket)),

    SYSCALL_NET(SYSCALL_SIGN(sys_closesocket)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getaddrinfo)),
    SYSCALL_NET(SYSCALL_SIGN(sys_gethostbyname2_r)), /* 85 */

    SYSCALL_NET(SYSCALL_SIGN(sys_sendmsg)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recvmsg)),
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network, 90 */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */

#ifdef RT_USING_DFS
    SYSCALL_SIGN(sys_select),
#else
    SYSCALL_SIGN(sys_notimpl),
#endif

    SYSCALL_SIGN(sys_notimpl),    /* SYSCALL_SIGN(sys_hw_interrupt_disable), 95 */
    SYSCALL_SIGN(sys_notimpl),    /* SYSCALL_SIGN(sys_hw_interrupt_enable) */

    SYSCALL_SIGN(sys_tick_get),
    SYSCALL_SIGN(sys_exit_group),

    SYSCALL_SIGN(sys_notimpl),    /* rt_delayed_work_init */
    SYSCALL_SIGN(sys_notimpl),    /* rt_work_submit, 100 */
    SYSCALL_SIGN(sys_notimpl),    /* rt_wqueue_wakeup */
    SYSCALL_SIGN(sys_thread_mdelay),
    SYSCALL_SIGN(sys_sigaction),
    SYSCALL_SIGN(sys_sigprocmask),
    SYSCALL_SIGN(sys_tkill),             /* 105 */
    SYSCALL_SIGN(sys_thread_sigprocmask),
#ifdef ARCH_MM_MMU
    SYSCALL_SIGN(sys_cacheflush),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_lwp_sighandler_set),
    SYSCALL_SIGN(sys_thread_sighandler_set),
#endif
    SYSCALL_SIGN(sys_waitpid),          /* 110 */

    SYSCALL_SIGN(sys_rt_timer_create),
    SYSCALL_SIGN(sys_rt_timer_delete),
    SYSCALL_SIGN(sys_rt_timer_start),
    SYSCALL_SIGN(sys_rt_timer_stop),
    SYSCALL_SIGN(sys_rt_timer_control),  /* 115 */
    SYSCALL_SIGN(sys_getcwd),
    SYSCALL_SIGN(sys_chdir),
    SYSCALL_SIGN(sys_unlink),
    SYSCALL_SIGN(sys_mkdir),
    SYSCALL_SIGN(sys_rmdir),          /* 120 */
    SYSCALL_SIGN(sys_getdents),
    SYSCALL_SIGN(sys_get_errno),
#ifdef ARCH_MM_MMU
    SYSCALL_SIGN(sys_set_thread_area),
    SYSCALL_SIGN(sys_set_tid_address),
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#endif
    SYSCALL_SIGN(sys_access),         /* 125 */
    SYSCALL_SIGN(sys_pipe),
    SYSCALL_SIGN(sys_clock_settime),
    SYSCALL_SIGN(sys_clock_gettime),
    SYSCALL_SIGN(sys_clock_getres),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_clone)),            /* 130 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_futex)),
    SYSCALL_SIGN(sys_notimpl),                          /* discarded: sys_pmutex */
    SYSCALL_SIGN(sys_dup),
    SYSCALL_SIGN(sys_dup2),
    SYSCALL_SIGN(sys_rename),                           /* 135 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_fork)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_execve)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_vfork)),
    SYSCALL_SIGN(sys_gettid),
    SYSCALL_SIGN(sys_prlimit64),                        /* 140 */
    SYSCALL_SIGN(sys_getrlimit),
    SYSCALL_SIGN(sys_setrlimit),
    SYSCALL_SIGN(sys_setsid),
    SYSCALL_SIGN(sys_getrandom),
    SYSCALL_SIGN(sys_readlink),                         /* 145 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_mremap)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_madvise)),
    SYSCALL_SIGN(sys_sched_setparam),
    SYSCALL_SIGN(sys_sched_getparam),
    SYSCALL_SIGN(sys_sched_get_priority_max),           /* 150 */
    SYSCALL_SIGN(sys_sched_get_priority_min),
    SYSCALL_SIGN(sys_sched_setscheduler),
    SYSCALL_SIGN(sys_sched_getscheduler),
    SYSCALL_SIGN(sys_sched_setaffinity),
    SYSCALL_SIGN(sys_fsync),                            /* 155 */
    SYSCALL_SIGN(sys_clock_nanosleep),
    SYSCALL_SIGN(sys_timer_create),
    SYSCALL_SIGN(sys_timer_delete),
    SYSCALL_SIGN(sys_timer_settime),
    SYSCALL_SIGN(sys_timer_gettime),                    /* 160 */
    SYSCALL_SIGN(sys_timer_getoverrun),
    SYSCALL_SIGN(sys_mq_open),
    SYSCALL_SIGN(sys_mq_unlink),
    SYSCALL_SIGN(sys_mq_timedsend),
    SYSCALL_SIGN(sys_mq_timedreceive),                  /* 165 */
    SYSCALL_SIGN(sys_mq_notify),
    SYSCALL_SIGN(sys_mq_getsetattr),
    SYSCALL_SIGN(sys_mq_close),
    SYSCALL_SIGN(sys_lstat),
    SYSCALL_SIGN(sys_uname),                            /* 170 */
    SYSCALL_SIGN(sys_statfs),
    SYSCALL_SIGN(sys_statfs64),
    SYSCALL_SIGN(sys_fstatfs),
    SYSCALL_SIGN(sys_fstatfs64),
    SYSCALL_SIGN(sys_openat),                           /* 175 */
    SYSCALL_SIGN(sys_mount),
    SYSCALL_SIGN(sys_umount2),
    SYSCALL_SIGN(sys_link),
    SYSCALL_SIGN(sys_symlink),
    SYSCALL_SIGN(sys_sched_getaffinity),                /* 180 */
    SYSCALL_SIGN(sys_sysinfo),
    SYSCALL_SIGN(sys_chmod),
    SYSCALL_SIGN(sys_reboot),
    SYSCALL_SIGN(sys_sched_yield),
    SYSCALL_SIGN(sys_pread64),                          /* 185 */
    SYSCALL_SIGN(sys_pwrite64),
    SYSCALL_SIGN(sys_sigpending),
    SYSCALL_SIGN(sys_sigtimedwait),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),                          /* 190 */
    SYSCALL_SIGN(sys_eventfd2),
    SYSCALL_SIGN(sys_epoll_create1),
    SYSCALL_SIGN(sys_epoll_ctl),
    SYSCALL_SIGN(sys_epoll_pwait),
    SYSCALL_SIGN(sys_notimpl),                          /* 195 */
    SYSCALL_SIGN(sys_timerfd_create),
    SYSCALL_SIGN(sys_timerfd_settime),
    SYSCALL_SIGN(sys_timerfd_gettime),
    SYSCALL_SIGN(sys_signalfd),
    SYSCALL_SIGN(sys_memfd_create),                     /* 200 */
    SYSCALL_SIGN(sys_ftruncate),
    SYSCALL_SIGN(sys_setitimer),
    SYSCALL_SIGN(sys_utimensat),
#ifdef RT_USING_POSIX_SOCKET
    SYSCALL_SIGN(sys_syslog),
    SYSCALL_SIGN(sys_socketpair),                             /* 205 */
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),                          /* 205 */
#endif
    SYSCALL_SIGN(sys_wait4),
    SYSCALL_SIGN(sys_set_robust_list),
    SYSCALL_SIGN(sys_get_robust_list),
    SYSCALL_SIGN(sys_setpgid),
    SYSCALL_SIGN(sys_getpgid),                          /* 210 */
    SYSCALL_SIGN(sys_getsid),
    SYSCALL_SIGN(sys_getppid),
    SYSCALL_SIGN(sys_fchdir),
    SYSCALL_SIGN(sys_chown),
};

const void *lwp_get_sys_api(rt_uint32_t number)
{
    const void *func = (const void *)sys_notimpl;

    if (number == 0xff)
    {
        func = (void *)sys_log;
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table) / sizeof(func_table[0]))
        {
            func = func_table[number].func;
        }
        else
        {
            if (__sys_log_enable)
            {
                LOG_I("Unimplement syscall %d", number);
            }
        }
    }

    return func;
}

const char *lwp_get_syscall_name(rt_uint32_t number)
{
    const char *name = "sys_notimpl";

    if (number == 0xff)
    {
        name = "sys_log";
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table) / sizeof(func_table[0]))
        {
            name = (char*)func_table[number].name;
        }
        else
        {
            if (__sys_log_enable)
            {
                LOG_I("Unimplement syscall %d", number);
            }
        }
    }

    /* skip sys_ */
    return name;
}
