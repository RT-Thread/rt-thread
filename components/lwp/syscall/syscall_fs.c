/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

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
    struct statfs statfsbuff = { 0 };

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char *)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void *)path, len);
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
    struct statfs statfsbuff = { 0 };

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

    copy_path = (char *)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void *)path, len);
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
    struct statfs statfsbuff = { 0 };

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
    struct statfs statfsbuff = { 0 };

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
    struct stat buf = { 0 };
    char *dev_fullpath = RT_NULL;

    len_source = source ? lwp_user_strlen(source) : 0;
    if (len_source < 0)
    {
        return -EINVAL;
    }

    len_target = target ? lwp_user_strlen(target) : 0;
    if (len_target <= 0)
    {
        return -EINVAL;
    }

    len_fs = filesystemtype ? lwp_user_strlen(filesystemtype) : 0;
    if (len_fs < 0)
    {
        return -EINVAL;
    }

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

    copy_special_file = (char *)rt_malloc(len_special_file + 1);
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
    if (ret < 0)
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
    int err = 0;
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
    if (ret < 0)
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
        {
            return -EFAULT;
        }

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
    {
        return -EFAULT;
    }

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
    {
        kmem_put(ksigs);
    }

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
    struct dfs_attr attr = { 0 };
    int ret = 0;

    len_file = lwp_user_strlen(pathname);
    if (len_file <= 0)
    {
        return -EFAULT;
    }

    copy_file = (char *)rt_malloc(len_file + 1);
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
 * @brief Changes the permissions of an open file descriptor.
 *
 * @param[in] fd The open file descriptor.
 * @param[in] mode The new file permission bits.
 * @return sysret_t Zero on success, otherwise a negative error code.
 */
sysret_t sys_fchmod(int fd, mode_t mode)
{
    int ret;

    ret = fchmod(fd, mode);
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
    struct dfs_attr attr = { 0 };
    int ret = 0;

    len_file = lwp_user_strlen(pathname);
    if (len_file <= 0)
    {
        return -EFAULT;
    }

    copy_file = (char *)rt_malloc(len_file + 1);
    if (!copy_file)
    {
        return -ENOMEM;
    }

    copy_len_file = lwp_get_from_user(copy_file, (void *)pathname, len_file);

    if (owner >= 0)
    {
        attr.st_uid = owner;
        attr.ia_valid |= ATTR_UID_SET;
    }

    if (group >= 0)
    {
        attr.st_gid = group;
        attr.ia_valid |= ATTR_GID_SET;
    }

    copy_file[copy_len_file] = '\0';
    ret = dfs_file_setattr(copy_file, &attr);
    rt_free(copy_file);

    return (ret < 0 ? GET_ERRNO() : ret);
}
