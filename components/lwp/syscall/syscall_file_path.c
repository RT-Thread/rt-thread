/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

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
            {
                ret = strlen(buf);
            }
            else
            {
                ret = -EFAULT;
            }
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
    if (ret < 0)
    {
        err = GET_ERRNO();
    }

    kmem_put(kpath);

    return (err < 0 ? err : ret);
#else
    ret = rmdir(path);
    if (ret < 0)
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
            dirp[i].d_off = i * sizeof(struct libc_dirent);
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
    int kfd[2] = { 0, 0 };

    if (!lwp_user_accessable((void *)fd, sizeof(int[2])))
    {
        return -EFAULT;
    }

    ret = pipe(kfd);

    lwp_put_to_user((void *)fd, kfd, sizeof(int[2]));

    return (ret < 0 ? GET_ERRNO() : ret);
}
