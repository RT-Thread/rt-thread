/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

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
sysret_t sys_ioctl(int fd, unsigned long cmd, void *data)
{
#ifdef ARCH_MM_MMU
    if (cmd == F_GETLK || cmd == F_SETLK || cmd == F_SETLKW)
    {
        struct flock lock;
        int ret;

        if (data == RT_NULL ||
            !lwp_user_accessable(data, sizeof(lock)) ||
            lwp_get_from_user(&lock, data, sizeof(lock)) != sizeof(lock))
        {
            return -EFAULT;
        }

        ret = ioctl(fd, cmd, &lock);
        if (ret >= 0 && cmd == F_GETLK &&
            lwp_put_to_user(data, &lock, sizeof(lock)) != sizeof(lock))
        {
            return -EFAULT;
        }
        return ret < 0 ? GET_ERRNO() : ret;
    }
#endif
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
    struct stat statbuff = { 0 };

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
    struct timeval ktimeout, *ptimeout = RT_NULL;

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
    if (timeout)
    {
        if (!lwp_user_accessable((void *)timeout, sizeof *timeout))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        lwp_get_from_user(&ktimeout, timeout, sizeof ktimeout);
        ptimeout = &ktimeout;
    }

    ret = select(nfds, kreadfds, kwritefds, kexceptfds, ptimeout);
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
