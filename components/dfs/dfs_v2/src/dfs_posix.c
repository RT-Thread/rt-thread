/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-27     Yi.qiu       The first version
 * 2018-02-07     Bernard      Change the 3rd parameter of open/fcntl/ioctl to '...'
 * 2021-08-26     linzhenxing  add setcwd and modify getcwd\chdir
 */

#include <dfs.h>
#include <unistd.h>

#include <dfs_dentry.h>
#include <dfs_mnt.h>
#include "dfs_private.h"

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
 * @param flags the file open flags.
 *
 * @return the non-negative integer on successful open, others for failed.
 */
int open(const char *file, int flags, ...)
{
    int fd, result;
    struct dfs_file *df = RT_NULL;
    mode_t mode = 0;

    if (file == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE)
    {
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    fd = fd_new();
    if (fd >= 0)
    {
        df = fd_get(fd);
    }
    else
    {
        rt_set_errno(-RT_ERROR);
        return RT_NULL;
    }

    result = dfs_file_open(df, file, flags, mode);
    if (result < 0)
    {
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

            fullpath = dfs_dentry_full_path(d->dentry);
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
    struct dfs_file *file;

    file = fd_get(fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_close(file);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    fd_release(fd);

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
#if defined(RT_USING_NEWLIB) && defined(_EXFUN)
_READ_WRITE_RETURN_TYPE _EXFUN(read, (int fd, void *buf, size_t len))
#else
ssize_t read(int fd, void *buf, size_t len)
#endif
{
    ssize_t result;
    struct dfs_file *file;

    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    file = fd_get(fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_read(file, buf, len);
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
#if defined(RT_USING_NEWLIB) && defined(_EXFUN)
_READ_WRITE_RETURN_TYPE _EXFUN(write, (int fd, const void *buf, size_t len))
#else
ssize_t write(int fd, const void *buf, size_t len)
#endif
{
    ssize_t result;
    struct dfs_file *file;

    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    file = fd_get(fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_write(file, buf, len);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(write);

/**
 * this function is a POSIX compliant version, which will seek the offset for
 * an open file descriptor.
 *
 * @param fd the file descriptor.
 * @param offset the offset to be seeked.
 * @param whence the directory of seek.
 *
 * @return the current read/write position in the file, or -1 on failed.
 */
off_t lseek(int fd, off_t offset, int whence)
{
    off_t result;
    struct dfs_file *file;

    file = fd_get(fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    result = dfs_file_lseek(file, offset, whence);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return result;
}
RTM_EXPORT(lseek);

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

    if (old_file == NULL || new_file == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    result = dfs_file_rename(old_file, new_file);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(rename);

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
    struct stat stat;

    if (pathname == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    result = dfs_file_lstat(pathname, &stat);
    if (result == 0 && S_ISDIR(stat.st_mode))
    {
        rt_set_errno(-RT_ERROR);

        return -1;
    }

    result = dfs_file_unlink(pathname);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    return 0;
}
RTM_EXPORT(unlink);

#ifndef _WIN32 /* we can not implement these functions */
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

    if (file == NULL || buf == NULL)
    {
        rt_set_errno(EBADF);
        return -1;
    }

    result = dfs_file_stat(file, buf);
    if (result < 0)
    {
        rt_set_errno(-result);
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
    int ret = 0;
    struct dfs_file *file;

    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    /* get the fd */
    file = fd_get(fildes);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    ret = file->dentry->mnt->fs_ops->stat(file->dentry, buf);

    return ret;
}
RTM_EXPORT(fstat);
#endif

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
    struct dfs_file *file;

    file = fd_get(fildes);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    ret = dfs_file_fsync(file);

    return ret;
}
RTM_EXPORT(fsync);

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
int fcntl(int fildes, int cmd, ...)
{
    int ret = -1;
    struct dfs_file *file;

    file = fd_get(fildes);
    if (file)
    {
        void *arg;
        va_list ap;

        va_start(ap, cmd);
        arg = va_arg(ap, void *);
        va_end(ap);

        ret = dfs_file_ioctl(file, cmd, arg);
        if (ret < 0)
        {
            ret = dfs_file_fcntl(fildes, cmd, (unsigned long)arg);
        }
    }
    else
    {
        ret = -EBADF;
    }

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
    struct dfs_file *file;

    file = fd_get(fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    if (length < 0)
    {
        rt_set_errno(-EINVAL);

        return -1;
    }

    result = dfs_file_ftruncate(file, length);
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

    if (path == NULL || buf == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

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
    int ret = 0;
    struct dfs_file *file;

    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    /* get the fd */
    file = fd_get(fildes);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    ret = file->dentry->mnt->fs_ops->statfs(file->dentry->mnt, buf);

    return ret;
}
RTM_EXPORT(fstatfs);

/**
 * this function is a POSIX compliant version, which will make a directory
 *
 * @param path the directory path to be made.
 * @param mode
 *
 * @return 0 on successful, others on failed.
 */
int mkdir(const char *path, mode_t mode)
{
    int result;
    struct stat stat;
    struct dfs_file file;

    if (path == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (path && dfs_file_lstat(path, &stat) == 0)
    {
        rt_set_errno(-RT_ERROR);
        return -1;
    }

    dfs_file_init(&file);

    result = dfs_file_open(&file, path, O_DIRECTORY | O_CREAT, mode);
    if (result >= 0)
    {
        dfs_file_close(&file);
        result = 0;
    }
    else
    {
        rt_set_errno(result);
        result = -1;
    }

    dfs_file_deinit(&file);

    return result;
}
RTM_EXPORT(mkdir);

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(mkdir, create a directory);
#endif

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
    DIR *dir = RT_NULL;
    struct stat stat;

    if (!pathname)
    {
        rt_set_errno(-RT_ERROR);
        return -1;
    }

    dir = opendir(pathname);
    if (dir)
    {
        struct dirent *dirent;

        while (1)
        {
            dirent = readdir(dir);
            if (dirent == RT_NULL)
                break;
            if (rt_strcmp(".", dirent->d_name) != 0 &&
                rt_strcmp("..", dirent->d_name) != 0)
            {
                break;
            }
        }

        closedir(dir);

        if (dirent)
        {
            rt_set_errno(-RT_ERROR);
            return -1;
        }
    }

    if (dfs_file_lstat(pathname, &stat) == 0)
    {
        if (S_ISLNK(stat.st_mode))
        {
            rt_set_errno(-RT_ERROR);
            return -1;
        }
    }

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
    DIR *t = RT_NULL;
    int fd, result;
    struct dfs_file *file = RT_NULL;

    if (!name || dfs_file_isdir(name) != 0)
    {
        rt_set_errno(-RT_ERROR);
        return RT_NULL;
    }

    fd = fd_new();
    if (fd >= 0)
    {
        file = fd_get(fd);
    }
    else
    {
        rt_set_errno(-RT_ERROR);
        return RT_NULL;
    }

    result = dfs_file_open(file, name, O_RDONLY | O_DIRECTORY, 0);
    if (result >= 0)
    {
        /* open successfully */
        t = (DIR *) rt_malloc(sizeof(DIR));
        if (t == NULL)
        {
            dfs_file_close(file);
            fd_release(fd);
        }
        else
        {
            rt_memset(t, 0, sizeof(DIR));

            t->fd = fd;
        }

        return t;
    }

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
    struct dirent *dirent = NULL;

    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return NULL;
    }

    do
    {
        if (d->num)
        {
            struct dirent *dirent_ptr;
            dirent_ptr = (struct dirent *)&d->buf[d->cur];
            d->cur += dirent_ptr->d_reclen;
        }

        if (!d->num || d->cur >= d->num)
        {
            /* get a new entry */
            result = dfs_file_getdents(fd_get(d->fd),
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

        dirent = (struct dirent *)(d->buf + d->cur);
        if (rt_strcmp(".", dirent->d_name) != 0 &&
            rt_strcmp("..", dirent->d_name) != 0)
        {
            break;
        }
    } while (dirent);

    return dirent;
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
    struct dfs_file *file;
    long result;

    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    file = fd_get(d->fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return 0;
    }

    result = file->fpos - d->num + d->cur;

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
    struct dfs_file *file;

    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return;
    }

    file = fd_get(d->fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);

        return;
    }

    if (d && d->fd > 0)
    {
        if (file->fpos > offset)
        {
            /* seek to the offset position of directory */
            if (dfs_file_lseek(fd_get(d->fd), 0, SEEK_SET) >= 0)
                d->num = d->cur = 0;
        }

        while(file->fpos < offset)
        {
            if (!readdir(d))
            {
                break;
            }
        }
    }
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
    if (d && d->fd > 0)
    {
        /* seek to the beginning of directory */
        if (dfs_file_lseek(fd_get(d->fd), 0, SEEK_SET) >= 0)
            d->num = d->cur = 0;
    }
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
    struct dfs_file *file;

    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    file = fd_get(d->fd);
    if (file == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    result = dfs_file_close(file);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }
    else
    {
        fd_release(d->fd);
        rt_free(d);
    }

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

        rt_set_errno(-ENOTDIR);
        return -1;
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
    int fd, ret = -1, flags = 0;
    struct stat sb;

    if (path == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (amode == F_OK)
    {
        if (stat(path, &sb) < 0)
            return -1; /* already sets errno */
        else
            return 0;
    }

    /* ignore R_OK,W_OK,X_OK condition */
    if (dfs_file_isdir(path) == 0)
    {
        flags |= O_DIRECTORY;
    }

    if (amode & R_OK)
    {
        flags |= O_RDONLY;
    }

    if (amode & W_OK)
    {
        flags |= O_WRONLY;
    }

    if (amode & X_OK)
    {
        flags |= O_EXEC;
    }

    fd = open(path, flags, 0);
    if (fd >= 0)
    {
        ret = 0;
        close(fd);
    }

    return ret;
}
/**
 * this function is a POSIX compliant version, which will set current
 * working directory.
 *
 * @param buf the current directory.
 */
void setcwd(char *buf)
{
    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return;
    }

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
    if (buf == NULL)
    {
        rt_set_errno(-EBADF);
        return NULL;
    }

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
