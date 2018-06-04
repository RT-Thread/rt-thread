/*
 * File      : dfs_file.c
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2011-12-08     Bernard      Merges rename patch from iamcacy.
 * 2015-05-27     Bernard      Fix the fd clear issue.
 */

#include <dfs.h>
#include <dfs_file.h>
#include <dfs_private.h>

/**
 * @addtogroup FileApi
 */

/*@{*/

/**
 * this function will open a file which specified by path with specified flags.
 *
 * @param fd the file descriptor pointer to return the corresponding result.
 * @param path the specified file path.
 * @param flags the flags for open operator.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_open(struct dfs_fd *fd, const char *path, int flags)
{
    struct dfs_filesystem *fs;
    char *fullpath;
    int result;

    /* parameter check */
    if (fd == NULL)
        return -EINVAL;

    /* make sure we have an absolute path */
    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath == NULL)
    {
        return -ENOMEM;
    }

    dbg_log(DBG_LOG, "open file:%s\n", fullpath);

    /* Check whether file is already open */
    if (fd_is_open(fullpath) == 0)
    {
        rt_free(fullpath); /* release path */

        return -EBUSY;
    }

    /* find filesystem */
    fs = dfs_filesystem_lookup(fullpath);
    if (fs == NULL)
    {
        rt_free(fullpath); /* release path */

        return -ENOENT;
    }

    dbg_log(DBG_LOG, "open in filesystem:%s\n", fs->ops->name);
    fd->fops  = fs->ops->fops; /* set file ops */

    /* initialize the fd item */
    fd->type  = FT_REGULAR;
    fd->flags = flags;
    fd->size  = 0;
    fd->pos   = 0;
    fd->data  = fs;

    if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
    {
        if (dfs_subdir(fs->path, fullpath) == NULL)
            fd->path = rt_strdup("/");
        else
            fd->path = rt_strdup(dfs_subdir(fs->path, fullpath));
        rt_free(fullpath);
        dbg_log(DBG_LOG, "Actual file path: %s\n", fd->path);
    }
    else
    {
        fd->path = fullpath;
    }

    /* specific file system open routine */
    if (fd->fops->open == NULL)
    {
        /* clear fd */
        rt_free(fd->path);
        fd->path = NULL;

        return -ENOSYS;
    }

    if ((result = fd->fops->open(fd)) < 0)
    {
        /* clear fd */
        rt_free(fd->path);
        fd->path = NULL;

        dbg_log(DBG_ERROR, "open failed\n");

        return result;
    }

    fd->flags |= DFS_F_OPEN;
    if (flags & O_DIRECTORY)
    {
        fd->type = FT_DIRECTORY;
        fd->flags |= DFS_F_DIRECTORY;
    }

    dbg_log(DBG_INFO, "open successful\n");
    return 0;
}

/**
 * this function will close a file descriptor.
 *
 * @param fd the file descriptor to be closed.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_close(struct dfs_fd *fd)
{
    int result = 0;

    if (fd == NULL)
        return -ENXIO;

    if (fd->fops->close != NULL)
        result = fd->fops->close(fd);

    /* close fd error, return */
    if (result < 0)
        return result;

    rt_free(fd->path);
    fd->path = NULL;

    return result;
}

/**
 * this function will perform a io control on a file descriptor.
 *
 * @param fd the file descriptor.
 * @param cmd the command to send to file descriptor.
 * @param args the argument to send to file descriptor.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    if (fd == NULL)
        return -EINVAL;

    /* regular file system fd */
    if (fd->type == FT_REGULAR)
    {
        switch (cmd)
        {
        case F_GETFL:
            return fd->flags; /* return flags */
        case F_SETFL:
            {
                int flags = (int)args;
                int mask  = O_NONBLOCK | O_APPEND;

                flags &= mask;
                fd->flags &= mask;
                fd->flags |= flags;
            }
            return 0;
        }
    }

    if (fd->fops->ioctl != NULL)
        return fd->fops->ioctl(fd, cmd, args);

    return -ENOSYS;
}

/**
 * this function will read specified length data from a file descriptor to a
 * buffer.
 *
 * @param fd the file descriptor.
 * @param buf the buffer to save the read data.
 * @param len the length of data buffer to be read.
 *
 * @return the actual read data bytes or 0 on end of file or failed.
 */
int dfs_file_read(struct dfs_fd *fd, void *buf, size_t len)
{
    int result = 0;

    if (fd == NULL)
        return -EINVAL;

    if (fd->fops->read == NULL)
        return -ENOSYS;

    if ((result = fd->fops->read(fd, buf, len)) < 0)
        fd->flags |= DFS_F_EOF;

    return result;
}

/**
 * this function will fetch directory entries from a directory descriptor.
 *
 * @param fd the directory descriptor.
 * @param dirp the dirent buffer to save result.
 * @param nbytes the available room in the buffer.
 *
 * @return the read dirent, others on failed.
 */
int dfs_file_getdents(struct dfs_fd *fd, struct dirent *dirp, size_t nbytes)
{
    /* parameter check */
    if (fd == NULL || fd->type != FT_DIRECTORY)
        return -EINVAL;

    if (fd->fops->getdents != NULL)
        return fd->fops->getdents(fd, dirp, nbytes);

    return -ENOSYS;
}

/**
 * this function will unlink (remove) a specified path file from file system.
 *
 * @param path the specified path file to be unlinked.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_unlink(const char *path)
{
    int result;
    char *fullpath;
    struct dfs_filesystem *fs;

    /* Make sure we have an absolute path */
    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath == NULL)
    {
        return -EINVAL;
    }

    /* get filesystem */
    if ((fs = dfs_filesystem_lookup(fullpath)) == NULL)
    {
        result = -ENOENT;
        goto __exit;
    }

    /* Check whether file is already open */
    if (fd_is_open(fullpath) == 0)
    {
        result = -EBUSY;
        goto __exit;
    }

    if (fs->ops->unlink != NULL)
    {
        if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
        {
            if (dfs_subdir(fs->path, fullpath) == NULL)
                result = fs->ops->unlink(fs, "/");
            else
                result = fs->ops->unlink(fs, dfs_subdir(fs->path, fullpath));
        }
        else
            result = fs->ops->unlink(fs, fullpath);
    }
    else result = -ENOSYS;

__exit:
    rt_free(fullpath);
    return result;
}

/**
 * this function will write some specified length data to file system.
 *
 * @param fd the file descriptor.
 * @param buf the data buffer to be written.
 * @param len the data buffer length
 *
 * @return the actual written data length.
 */
int dfs_file_write(struct dfs_fd *fd, const void *buf, size_t len)
{
    if (fd == NULL)
        return -EINVAL;

    if (fd->fops->write == NULL)
        return -ENOSYS;

    return fd->fops->write(fd, buf, len);
}

/**
 * this function will flush buffer on a file descriptor.
 *
 * @param fd the file descriptor.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_flush(struct dfs_fd *fd)
{
    if (fd == NULL)
        return -EINVAL;

    if (fd->fops->flush == NULL)
        return -ENOSYS;

    return fd->fops->flush(fd);
}

/**
 * this function will seek the offset for specified file descriptor.
 *
 * @param fd the file descriptor.
 * @param offset the offset to be sought.
 *
 * @return the current position after seek.
 */
int dfs_file_lseek(struct dfs_fd *fd, off_t offset)
{
    int result;

    if (fd == NULL)
        return -EINVAL;

    if (fd->fops->lseek == NULL)
        return -ENOSYS;

    result = fd->fops->lseek(fd, offset);

    /* update current position */
    if (result >= 0)
        fd->pos = result;

    return result;
}

/**
 * this function will get file information.
 *
 * @param path the file path.
 * @param buf the data buffer to save stat description.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_stat(const char *path, struct stat *buf)
{
    int result;
    char *fullpath;
    struct dfs_filesystem *fs;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath == NULL)
    {
        return -1;
    }

    if ((fs = dfs_filesystem_lookup(fullpath)) == NULL)
    {
        dbg_log(DBG_ERROR,
                "can't find mounted filesystem on this path:%s\n", fullpath);
        rt_free(fullpath);

        return -ENOENT;
    }

    if ((fullpath[0] == '/' && fullpath[1] == '\0') ||
        (dfs_subdir(fs->path, fullpath) == NULL))
    {
        /* it's the root directory */
        buf->st_dev   = 0;

        buf->st_mode  = S_IRUSR | S_IRGRP | S_IROTH |
                        S_IWUSR | S_IWGRP | S_IWOTH;
        buf->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;

        buf->st_size    = 0;
        buf->st_mtime   = 0;

        /* release full path */
        rt_free(fullpath);

        return RT_EOK;
    }
    else
    {
        if (fs->ops->stat == NULL)
        {
            rt_free(fullpath);
            dbg_log(DBG_ERROR,
                    "the filesystem didn't implement this function\n");

            return -ENOSYS;
        }

        /* get the real file path and get file stat */
        if (fs->ops->flags & DFS_FS_FLAG_FULLPATH)
            result = fs->ops->stat(fs, fullpath, buf);
        else
            result = fs->ops->stat(fs, dfs_subdir(fs->path, fullpath), buf);
    }

    rt_free(fullpath);

    return result;
}

/**
 * this function will rename an old path name to a new path name.
 *
 * @param oldpath the old path name.
 * @param newpath the new path name.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_rename(const char *oldpath, const char *newpath)
{
    int result;
    struct dfs_filesystem *oldfs, *newfs;
    char *oldfullpath, *newfullpath;

    result = RT_EOK;
    newfullpath = NULL;
    oldfullpath = NULL;

    oldfullpath = dfs_normalize_path(NULL, oldpath);
    if (oldfullpath == NULL)
    {
        result = -ENOENT;
        goto __exit;
    }

    newfullpath = dfs_normalize_path(NULL, newpath);
    if (newfullpath == NULL)
    {
        result = -ENOENT;
        goto __exit;
    }

    oldfs = dfs_filesystem_lookup(oldfullpath);
    newfs = dfs_filesystem_lookup(newfullpath);

    if (oldfs == newfs)
    {
        if (oldfs->ops->rename == NULL)
        {
            result = -ENOSYS;
        }
        else
        {
            if (oldfs->ops->flags & DFS_FS_FLAG_FULLPATH)
                result = oldfs->ops->rename(oldfs, oldfullpath, newfullpath);
            else
                /* use sub directory to rename in file system */
                result = oldfs->ops->rename(oldfs,
                                            dfs_subdir(oldfs->path, oldfullpath),
                                            dfs_subdir(newfs->path, newfullpath));
        }
    }
    else
    {
        result = -EXDEV;
    }

__exit:
    rt_free(oldfullpath);
    rt_free(newfullpath);

    /* not at same file system, return EXDEV */
    return result;
}

/* @} */
