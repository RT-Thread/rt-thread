/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-27     Yi.qiu       The first version
 * 2018-02-07     Bernard      Change the 3rd parameter of open/fcntl/ioctl to '...'
 * 2022-01-19     Meco Man     add creat()
 */

#include <dfs_file.h>
#include <dfs_private.h>
#include <sys/errno.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#endif

/**
 * @addtogroup FsPosixApi
 * @{
 */

/**
 * this function is a POSIX compliant version, which will open a file and
 * return a file descriptor according specified flags.
 *
 * @param file the path name of file.
 * @param flags the file open flags. Common values include:
 *     - Access modes (mutually exclusive):
 *         - `O_RDONLY`: Open for read-only access.
 *         - `O_WRONLY`: Open for write-only access.
 *         - `O_RDWR`: Open for both reading and writing.
 *     - File status flags (can be combined with bitwise OR `|`):
 *         - `O_CREAT`: Create the file if it does not exist. Requires a `mode` argument.
 *         - `O_TRUNC`: Truncate the file to zero length if it already exists.
 *         - `O_APPEND`: Append writes to the end of the file.
 *         - `O_EXCL`: Ensure that `O_CREAT` creates the file exclusively.
 *         - Other platform-specific flags
 *
 * @return the non-negative integer on successful open, others for failed.
 */
int open(const char *file, int flags, ...)
{
    int fd, result;
    struct dfs_file *d;

    /* allocate a fd */
    fd = fd_new();
    if (fd < 0)
    {
        rt_set_errno(-ENOMEM);

        return -1;
    }
    d = fd_get(fd);

    result = dfs_file_open(d, file, flags);
    if (result < 0)
    {
        /* release the ref-count of fd */
        fd_release(fd);

        rt_set_errno(result);

        return -1;
    }

    return fd;
}
RTM_EXPORT(open);

#ifndef AT_FDCWD
#define AT_FDCWD (-100)
#endif

/**
 * @brief Opens a file relative to a directory file descriptor.
 *
 * @param dirfd The file descriptor of the directory to base the relative path on.
 * @param pathname The path to the file to be opened, relative to the directory specified by `dirfd`.
 *                 Can be an absolute path (in which case `dirfd` is ignored).
 * @param flags File access and status flags (e.g., `O_RDONLY`, `O_WRONLY`, `O_CREAT`).
 *
 * @return On success, returns a new file descriptor for the opened file.
 *         On failure, returns `-1` and sets `errno` to indicate the error.
 *
 * @note When using relative paths, ensure `dirfd` is a valid directory descriptor.
 *       When `pathname` is absolute, the `dirfd` argument is ignored.
 *
 */
int openat(int dirfd, const char *path, int flag, ...)
{
    struct dfs_file *d;
    char *fullpath;
    int fd;

    if (!path)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    fullpath = (char*)path;

    if (path[0] != '/')
    {
        if (dirfd != AT_FDCWD)
        {
            d = fd_get(dirfd);
            if (!d || !d->vnode)
            {
                rt_set_errno(-EBADF);
                return -1;
            }

            fullpath = dfs_normalize_path(d->vnode->fullpath, path);
            if (!fullpath)
            {
                rt_set_errno(-ENOMEM);
                return -1;
            }
        }
    }

    fd = open(fullpath, flag, 0);

    if (fullpath != path)
    {
        rt_free(fullpath);
    }

    return fd;
}

/**
 * this function is a POSIX compliant version,
 * which will create a new file or rewrite an existing one
 *
 * @param path the path name of file.
 * @param mode the file permission bits to be used in creating the file (not used, can be 0)
 *
 * @return the non-negative integer on successful open, others for failed.
 */
int creat(const char *path, mode_t mode)
{
    return open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
RTM_EXPORT(creat);

/**
 * this function is a POSIX compliant version, which will close the open
 * file descriptor.
 *
 * @param fd the file descriptor.
 *
 * @return 0 on successful, -1 on failed.
 */
int close(int fd)
{
    int result;
    struct dfs_file *d;

    d = fd_get(fd);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_close(d);
    fd_release(fd);

    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(close);

/**
 * this function is a POSIX compliant version, which will read specified data
 * buffer length for an open file descriptor.
 *
 * @param fd the file descriptor.
 * @param buf the buffer to save the read data.
 * @param len the maximal length of data buffer
 *
 * @return the actual read data buffer length. If the returned value is 0, it
 * may be reach the end of file, please check errno.
 */
#ifdef _READ_WRITE_RETURN_TYPE
_READ_WRITE_RETURN_TYPE read(int fd, void *buf, size_t len) /* some gcc tool chains will use different data structure */
#else
ssize_t read(int fd, void *buf, size_t len)
#endif
{
    int result;
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fd);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_read(d, buf, len);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(read);

/**
 * this function is a POSIX compliant version, which will write specified data
 * buffer length for an open file descriptor.
 *
 * @param fd the file descriptor
 * @param buf the data buffer to be written.
 * @param len the data buffer length.
 *
 * @return the actual written data buffer length.
 */
#ifdef _READ_WRITE_RETURN_TYPE
_READ_WRITE_RETURN_TYPE write(int fd, const void *buf, size_t len) /* some gcc tool chains will use different data structure */
#else
ssize_t write(int fd, const void *buf, size_t len)
#endif
{
    int result;
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fd);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_write(d, buf, len);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(write);

/**
 * this function is a POSIX compliant version, which will Reposition the file offset for
 * an open file descriptor.
 *
 * The `lseek` function sets the file offset for the file descriptor `fd`
 * to a new value, determined by the `offset` and `whence` parameters.
 * It can be used to seek to specific positions in a file for reading or writing.
 *
 * @param fd the file descriptor.
 * @param offset The offset, in bytes, to set the file position.
 *               The meaning of `offset` depends on the value of `whence`.
 * @param whence the directive of seek. It can be one of:
 *               - `SEEK_SET`: Set the offset to `offset` bytes from the beginning of the file.
 *               - `SEEK_CUR`: Set the offset to its current location plus `offset` bytes.
 *               - `SEEK_END`: Set the offset to the size of the file plus `offset` bytes.
 *
 * @return the resulting read/write position in the file, or -1 on failed.
 */
off_t lseek(int fd, off_t offset, int whence)
{
    int result;
    struct dfs_file *d;

    d = fd_get(fd);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    switch (whence)
    {
    case SEEK_SET:
        break;

    case SEEK_CUR:
        offset += d->pos;
        break;

    case SEEK_END:
        offset += d->vnode->size;
        break;

    default:
        rt_set_errno(-EINVAL);

        return -1;
    }

    if (offset < 0)
    {
        rt_set_errno(-EINVAL);

        return -1;
    }
    result = dfs_file_lseek(d, offset);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return offset;
}
RTM_EXPORT(lseek);

#ifndef _WIN32
/**
 * this function is a POSIX compliant version, which will rename old file name
 * to new file name.
 *
 * @param old_file the old file name.
 * @param new_file the new file name.
 *
 * @return 0 on successful, -1 on failed.
 *
 * note: the old and new file name must be belong to a same file system.
 */
int rename(const char *old_file, const char *new_file)
{
    int result;

    result = dfs_file_rename(old_file, new_file);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(rename);
#endif

/**
 * this function is a POSIX compliant version, which will unlink (remove) a
 * specified path file from file system.
 *
 * @param pathname the specified path name to be unlinked.
 *
 * @return 0 on successful, -1 on failed.
 */
int unlink(const char *pathname)
{
    int result;

    result = dfs_file_unlink(pathname);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(unlink);

/**
 * this function is a POSIX compliant version, which will get file information.
 *
 * @param file the file name
 * @param buf the data buffer to save stat description.
 *
 * @return 0 on successful, -1 on failed.
 */
int stat(const char *file, struct stat *buf)
{
    int result;

    result = dfs_file_stat(file, buf);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(stat);

/**
 * this function is a POSIX compliant version, which will get file status.
 *
 * @param fildes the file description
 * @param buf the data buffer to save stat description.
 *
 * @return 0 on successful, -1 on failed.
 */
int fstat(int fildes, struct stat *buf)
{
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fildes);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    return stat(d->vnode->fullpath, buf);
}
RTM_EXPORT(fstat);

/**
 * this function is a POSIX compliant version, which shall request that all data
 * for the open file descriptor named by fildes is to be transferred to the storage
 * device associated with the file described by fildes.
 *
 * @param fildes the file description
 *
 * @return 0 on successful completion. Otherwise, -1 shall be returned and errno
 * set to indicate the error.
 */
int fsync(int fildes)
{
    int ret;
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fildes);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    ret = dfs_file_flush(d);

    return ret;
}
RTM_EXPORT(fsync);

/**
 * this function is a POSIX compliant version, which shall perform a variety of
 * control functions on devices.
 *
 * @param fildes the file description
 * @param cmd the specified command, Common values include:
 *     - `F_DUPFD`: Duplicate a file descriptor.
 *     - `F_GETFD`: Get the file descriptor flags.
 *     - `F_SETFD`: Set the file descriptor flags.
 *     - `F_GETFL`: Get the file status flags.
 *     - `F_SETFL`: Set the file status flags.
 * @param ... represents the additional information that is needed by this
 * specific device to perform the requested function. For example:
 *     - When `cmd` is `F_SETFL`, an additional integer argument specifies the new status flags.
 *
 * @return 0 on successful completion. Otherwise, -1 shall be returned and errno
 * set to indicate the error.
 */
int fcntl(int fildes, int cmd, ...)
{
    int ret = -1;
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fildes);
    if (d)
    {
        void *arg;
        va_list ap;

        va_start(ap, cmd);
        arg = va_arg(ap, void *);
        va_end(ap);

        ret = dfs_file_ioctl(d, cmd, arg);
    }
    else ret = -EBADF;

    if (ret < 0)
    {
        rt_set_errno(ret);
        ret = -1;
    }

    return ret;
}
RTM_EXPORT(fcntl);

/**
 * this function is a POSIX compliant version, which shall perform a variety of
 * control functions on devices.
 *
 * @param fildes the file description
 * @param cmd the specified command
 * @param ... represents the additional information that is needed by this
 * specific device to perform the requested function.
 *
 * @return 0 on successful completion. Otherwise, -1 shall be returned and errno
 * set to indicate the error.
 */
int ioctl(int fildes, int cmd, ...)
{
    void *arg;
    va_list ap;

    va_start(ap, cmd);
    arg = va_arg(ap, void *);
    va_end(ap);

    /* we use fcntl for this API. */
    return fcntl(fildes, cmd, arg);
}
RTM_EXPORT(ioctl);

/**
 *
 * this function is a POSIX compliant version, which cause the regular file
 * referenced by fd to be truncated to a size of precisely length bytes.
 * @param fd the file descriptor.
 * @param length the length to be truncated.
 *
 * @return Upon successful completion, ftruncate() shall return 0;
 * otherwise, -1 shall be returned and errno set to indicate the error.
 */
int ftruncate(int fd, off_t length)
{
    int result;
    struct dfs_file *d;

    d = fd_get(fd);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    if (length < 0)
    {
        rt_set_errno(-EINVAL);

        return -1;
    }
    result = dfs_file_ftruncate(d, length);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(ftruncate);

/**
 * this function is a POSIX compliant version, which will return the
 * information about a mounted file system.
 *
 * @param path the path which mounted file system.
 * @param buf the buffer to save the returned information.
 *
 * @return 0 on successful, others on failed.
 */
int statfs(const char *path, struct statfs *buf)
{
    int result;

    result = dfs_statfs(path, buf);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(statfs);

/**
 * this function is a POSIX compliant version, which will return the
 * information about a mounted file system.
 *
 * @param fildes the file description.
 * @param buf the buffer to save the returned information.
 *
 * @return 0 on successful, others on failed.
 */
int fstatfs(int fildes, struct statfs *buf)
{
    struct dfs_file *d;

    /* get the fd */
    d = fd_get(fildes);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    return statfs(d->vnode->fullpath, buf);
}
RTM_EXPORT(fstatfs);

/**
 * this function is a POSIX compliant version, which will make a directory
 *
 * @param path the directory path to be made.
 * @param mode The permission mode for the new directory (unused here, can be set to 0).
 *
 * @return 0 on successful, others on failed.
 */
int mkdir(const char *path, mode_t mode)
{
    int fd;
    struct dfs_file *d;
    int result;

    fd = fd_new();
    if (fd == -1)
    {
        rt_set_errno(-ENOMEM);

        return -1;
    }

    d = fd_get(fd);

    result = dfs_file_open(d, path, O_DIRECTORY | O_CREAT);

    if (result < 0)
    {
        fd_release(fd);
        rt_set_errno(result);

        return -1;
    }

    dfs_file_close(d);
    fd_release(fd);

    return 0;
}
RTM_EXPORT(mkdir);

/**
 * this function is a POSIX compliant version, which will remove a directory.
 *
 * @param pathname the path name to be removed.
 *
 * @return 0 on successful, others on failed.
 */
int rmdir(const char *pathname)
{
    int result;

    result = dfs_file_unlink(pathname);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(rmdir);

/**
 * this function is a POSIX compliant version, which will open a directory.
 *
 * @param name the path name to be open.
 *
 * @return the DIR pointer of directory, NULL on open directory failed.
 */
DIR *opendir(const char *name)
{
    struct dfs_file *d;
    int fd, result;
    DIR *t;

    t = NULL;

    /* allocate a fd */
    fd = fd_new();
    if (fd == -1)
    {
        rt_set_errno(-ENOMEM);

        return NULL;
    }
    d = fd_get(fd);

    result = dfs_file_open(d, name, O_RDONLY | O_DIRECTORY);
    if (result >= 0)
    {
        /* open successfully */
        t = (DIR *) rt_malloc(sizeof(DIR));
        if (t == NULL)
        {
            dfs_file_close(d);
            fd_release(fd);
        }
        else
        {
            rt_memset(t, 0, sizeof(DIR));

            t->fd = fd;
        }

        return t;
    }

    /* open failed */
    fd_release(fd);
    rt_set_errno(result);

    return NULL;
}
RTM_EXPORT(opendir);

/**
 * this function is a POSIX compliant version, which will return a pointer
 * to a dirent structure representing the next directory entry in the
 * directory stream.
 *
 * @param d the directory stream pointer.
 *
 * @return the next directory entry, NULL on the end of directory or failed.
 */
struct dirent *readdir(DIR *d)
{
    int result;
    struct dfs_file *fd;

    fd = fd_get(d->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);
        return NULL;
    }

    if (d->num)
    {
        struct dirent *dirent_ptr;
        dirent_ptr = (struct dirent *)&d->buf[d->cur];
        d->cur += dirent_ptr->d_reclen;
    }

    if (!d->num || d->cur >= d->num)
    {
        /* get a new entry */
        result = dfs_file_getdents(fd,
                                   (struct dirent *)d->buf,
                                   sizeof(d->buf) - 1);
        if (result <= 0)
        {
            rt_set_errno(result);

            return NULL;
        }

        d->num = result;
        d->cur = 0; /* current entry index */
    }

    return (struct dirent *)(d->buf + d->cur);
}
RTM_EXPORT(readdir);

/**
 * this function is a POSIX compliant version, which will return current
 * location in directory stream.
 *
 * @param d the directory stream pointer.
 *
 * @return the current location in directory stream.
 */
long telldir(DIR *d)
{
    struct dfs_file *fd;
    long result;

    fd = fd_get(d->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);

        return 0;
    }

    result = fd->pos - d->num + d->cur;

    return result;
}
RTM_EXPORT(telldir);

/**
 * this function is a POSIX compliant version, which will set position of
 * next directory structure in the directory stream.
 *
 * @param d the directory stream.
 * @param offset the offset in directory stream.
 */
void seekdir(DIR *d, long offset)
{
    struct dfs_file *fd;

    fd = fd_get(d->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);

        return ;
    }

    /* seek to the offset position of directory */
    if (dfs_file_lseek(fd, offset) >= 0)
        d->num = d->cur = 0;
}
RTM_EXPORT(seekdir);

/**
 * this function is a POSIX compliant version, which will reset directory
 * stream.
 *
 * @param d the directory stream.
 */
void rewinddir(DIR *d)
{
    struct dfs_file *fd;

    fd = fd_get(d->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);

        return ;
    }

    /* seek to the beginning of directory */
    if (dfs_file_lseek(fd, 0) >= 0)
        d->num = d->cur = 0;
}
RTM_EXPORT(rewinddir);

/**
 * this function is a POSIX compliant version, which will close a directory
 * stream.
 *
 * @param d the directory stream.
 *
 * @return 0 on successful, -1 on failed.
 */
int closedir(DIR *d)
{
    int result;
    struct dfs_file *fd;

    fd = fd_get(d->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_close(fd);
    fd_release(d->fd);

    rt_free(d);

    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }
    else
        return 0;
}
RTM_EXPORT(closedir);

#ifdef DFS_USING_WORKDIR
/**
 * this function is a POSIX compliant version, which will change working
 * directory.
 *
 * @param path the path name to be changed to.
 *
 * @return 0 on successful, -1 on failed.
 */
int chdir(const char *path)
{
    char *fullpath;
    DIR *d;

    if (path == NULL)
    {
        dfs_lock();
#ifdef DFS_USING_WORKDIR
        rt_kprintf("%s\n", working_directory);
#endif
        dfs_unlock();

        return 0;
    }

    if (strlen(path) > DFS_PATH_MAX)
    {
        rt_set_errno(-ENOTDIR);

        return -1;
    }

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath == NULL)
    {
        rt_set_errno(-ENOTDIR);

        return -1; /* build path failed */
    }

    dfs_lock();
    d = opendir(fullpath);
    if (d == NULL)
    {
        rt_free(fullpath);
        /* this is a not exist directory */
        dfs_unlock();

        return -1;
    }

    /* close directory stream */
    closedir(d);
#ifdef RT_USING_SMART
    /* copy full path to working directory */
    lwp_setcwd(fullpath);
#else
    rt_strncpy(working_directory, fullpath, DFS_PATH_MAX);
#endif
    /* release normalize directory path name */
    rt_free(fullpath);

    dfs_unlock();

    return 0;
}
RTM_EXPORT(chdir);

#ifdef RT_USING_FINSH
FINSH_FUNCTION_EXPORT_ALIAS(chdir, cd, change current working directory);
#endif
#endif

/**
 * this function is a POSIX compliant version, which shall check the file named
 * by the pathname pointed to by the path argument for accessibility according
 * to the bit pattern contained in amode.
 *
 * @param path the specified file/dir path.
 * @param amode the value is either the bitwise-inclusive OR of the access
 * permissions to be checked (R_OK, W_OK, X_OK) or the existence test (F_OK).
 */
int access(const char *path, int amode)
{
    struct stat sb;
    if (stat(path, &sb) < 0)
        return -1; /* already sets errno */

    /* ignore R_OK,W_OK,X_OK condition */
    return 0;
}
/**
 * this function is a POSIX compliant version, which will set current
 * working directory.
 *
 * @param buf the current directory.
 */
void setcwd(char *buf)
{
#ifdef DFS_USING_WORKDIR
    dfs_lock();
#ifdef RT_USING_SMART
    lwp_setcwd(buf);
#else
    rt_strncpy(working_directory, buf, DFS_PATH_MAX);
#endif
    dfs_unlock();
#else
    rt_kprintf(NO_WORKING_DIR);
#endif

    return ;
}
RTM_EXPORT(setcwd);

/**
 * this function is a POSIX compliant version, which will return current
 * working directory.
 *
 * @param buf the returned current directory.
 * @param size the buffer size.
 *
 * @return the returned current directory.
 */
char *getcwd(char *buf, size_t size)
{
#ifdef DFS_USING_WORKDIR
    char *dir_buf = RT_NULL;

    dfs_lock();

#ifdef RT_USING_SMART
    dir_buf = lwp_getcwd();
#else
    dir_buf = &working_directory[0];
#endif

    /* copy to buf parameter */
    if (buf)
    {
        rt_strncpy(buf, dir_buf, size);
    }

    dfs_unlock();
#else
    rt_kprintf(NO_WORKING_DIR);
#endif

    return buf;
}
RTM_EXPORT(getcwd);

/**@}*/
