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
 */

#include <dfs.h>
#include <dfs_file.h>

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
    if (fd == RT_NULL)
        return -DFS_STATUS_EINVAL;

    /* make sure we have an absolute path */
    fullpath = dfs_normalize_path(RT_NULL, path);
    if (fullpath == RT_NULL)
    {
        return -1;
    }

    dfs_log(DFS_DEBUG_INFO, ("open file:%s", fullpath));

    /* find filesystem */
    fs = dfs_filesystem_lookup(fullpath);
    if (fs == RT_NULL)
    {
        rt_free(fullpath); /* release path */

        return -DFS_STATUS_ENOENT;
    }

    dfs_log(DFS_DEBUG_INFO, ("open in filesystem:%s", fs->ops->name));
    fd->fs = fs;

    /* initialize the fd item */
    fd->type  = FT_REGULAR;
    fd->flags = flags;
    fd->size  = 0;
    fd->pos   = 0;

    if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
    {
        if (dfs_subdir(fs->path, fullpath) == RT_NULL)
            fd->path = rt_strdup("/");
        else
            fd->path = rt_strdup(dfs_subdir(fs->path, fullpath));
        rt_free(fullpath);
        dfs_log(DFS_DEBUG_INFO, ("Actual file path: %s\n", fd->path));
    }
    else
    {
        fd->path = fullpath;
    }

    /* specific file system open routine */
    if (fs->ops->open == RT_NULL)
    {
        /* clear fd */
        rt_free(fd->path);
        rt_memset(fd, 0, sizeof(*fd));

        return -DFS_STATUS_ENOSYS;
    }

    if ((result = fs->ops->open(fd)) < 0)
    {
        /* clear fd */
        rt_free(fd->path);
        rt_memset(fd, 0, sizeof(*fd));

        dfs_log(DFS_DEBUG_INFO, ("open failed"));

        return result;
    }

    fd->flags |= DFS_F_OPEN;
    if (flags & DFS_O_DIRECTORY)
    {
        fd->type = FT_DIRECTORY;
        fd->flags |= DFS_F_DIRECTORY;
    }

    dfs_log(DFS_DEBUG_INFO, ("open successful"));
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

    if (fd != RT_NULL && fd->fs->ops->close != RT_NULL)
        result = fd->fs->ops->close(fd);

    /* close fd error, return */
    if (result < 0)
        return result;

    rt_free(fd->path);
    rt_memset(fd, 0, sizeof(struct dfs_fd));

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
    struct dfs_filesystem *fs;

    if (fd == RT_NULL || fd->type != FT_REGULAR)
        return -DFS_STATUS_EINVAL;

    fs = fd->fs;
    if (fs->ops->ioctl != RT_NULL) 
        return fs->ops->ioctl(fd, cmd, args);

    return -DFS_STATUS_ENOSYS;
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
int dfs_file_read(struct dfs_fd *fd, void *buf, rt_size_t len)
{
    struct dfs_filesystem *fs;
    int result = 0;

    if (fd == RT_NULL) 
        return -DFS_STATUS_EINVAL;

    fs = (struct dfs_filesystem *)fd->fs;
    if (fs->ops->read == RT_NULL) 
        return -DFS_STATUS_ENOSYS;

    if ((result = fs->ops->read(fd, buf, len)) < 0)
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
int dfs_file_getdents(struct dfs_fd *fd, struct dirent *dirp, rt_size_t nbytes)
{
    struct dfs_filesystem *fs;

    /* parameter check */
    if (fd == RT_NULL || fd->type != FT_DIRECTORY) 
        return -DFS_STATUS_EINVAL;

    fs = (struct dfs_filesystem *)fd->fs;
    if (fs->ops->getdents != RT_NULL)
        return fs->ops->getdents(fd, dirp, nbytes);

    return -DFS_STATUS_ENOSYS;
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
    fullpath = dfs_normalize_path(RT_NULL, path);
    if (fullpath == RT_NULL)
    {
        return -DFS_STATUS_EINVAL;
    }

    /* get filesystem */
    if ((fs = dfs_filesystem_lookup(fullpath)) == RT_NULL)
    {
        result = -DFS_STATUS_ENOENT;
        goto __exit;
    }

    /* Check whether file is already open */
    if (fd_is_open(fullpath) == 0)
    {
        result = -DFS_STATUS_EBUSY;
        goto __exit;
    }

    if (fs->ops->unlink != RT_NULL)
    {
        if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
        {
            if (dfs_subdir(fs->path, fullpath) == RT_NULL)
                result = fs->ops->unlink(fs, "/");
            else
                result = fs->ops->unlink(fs, dfs_subdir(fs->path, fullpath));
        }
        else
            result = fs->ops->unlink(fs, fullpath);             
    }
    else result = -DFS_STATUS_ENOSYS;

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
int dfs_file_write(struct dfs_fd *fd, const void *buf, rt_size_t len)
{
    struct dfs_filesystem *fs;

    if (fd == RT_NULL)
        return -DFS_STATUS_EINVAL;

    fs = fd->fs;
    if (fs->ops->write == RT_NULL)
        return -DFS_STATUS_ENOSYS;

    return fs->ops->write(fd, buf, len);
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
    struct dfs_filesystem *fs;

    if (fd == RT_NULL)
        return -DFS_STATUS_EINVAL;

    fs = fd->fs;
    if (fs->ops->flush == RT_NULL)
        return -DFS_STATUS_ENOSYS;

    return fs->ops->flush(fd);
}

/**
 * this function will seek the offset for specified file descriptor.
 *
 * @param fd the file descriptor.
 * @param offset the offset to be sought.
 *
 * @return the current position after seek.
 */
int dfs_file_lseek(struct dfs_fd *fd, rt_off_t offset)
{
    int result;
    struct dfs_filesystem *fs = fd->fs;

    if (fd == RT_NULL)
        return -DFS_STATUS_EINVAL;
    if (fs->ops->lseek == RT_NULL)
        return -DFS_STATUS_ENOSYS;

    result = fs->ops->lseek(fd, offset);

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

    fullpath = dfs_normalize_path(RT_NULL, path);
    if (fullpath == RT_NULL)
    {
        return -1;
    }

    if ((fs = dfs_filesystem_lookup(fullpath)) == RT_NULL)
    {
        dfs_log(DFS_DEBUG_ERROR,
                ("can't find mounted filesystem on this path:%s", fullpath));
        rt_free(fullpath);

        return -DFS_STATUS_ENOENT;
    }

    if ((fullpath[0] == '/' && fullpath[1] == '\0') ||
        (dfs_subdir(fs->path, fullpath) == RT_NULL))
    {
        /* it's the root directory */
        buf->st_dev   = 0;

        buf->st_mode  = DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
                        DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
        buf->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;

        buf->st_size    = 0;
        buf->st_mtime   = 0;
        buf->st_blksize = 512;

        /* release full path */
        rt_free(fullpath);

        return DFS_STATUS_OK;
    }
    else
    {
        if (fs->ops->stat == RT_NULL)
        {
            rt_free(fullpath);
            dfs_log(DFS_DEBUG_ERROR,
                    ("the filesystem didn't implement this function"));

            return -DFS_STATUS_ENOSYS;
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

    result = DFS_STATUS_OK;
    newfullpath = RT_NULL;
    oldfullpath = RT_NULL;

    oldfullpath = dfs_normalize_path(RT_NULL, oldpath);
    if (oldfullpath == RT_NULL)
    {
        result = -DFS_STATUS_ENOENT;
        goto __exit;
    }

    newfullpath = dfs_normalize_path(RT_NULL, newpath);
    if (newfullpath == RT_NULL)
    {
        result = -DFS_STATUS_ENOENT;
        goto __exit;
    }

    oldfs = dfs_filesystem_lookup(oldfullpath);
    newfs = dfs_filesystem_lookup(newfullpath);

    if (oldfs == newfs)
    {
        if (oldfs->ops->rename == RT_NULL)
        {
            result = -DFS_STATUS_ENOSYS;
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
        result = -DFS_STATUS_EXDEV;
    }

__exit:
    rt_free(oldfullpath);
    rt_free(newfullpath);

    /* not at same file system, return EXDEV */
    return result;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static struct dfs_fd fd;
static struct dirent dirent;
void ls(const char *pathname)
{
    struct stat stat;
    int length;
    char *fullpath, *path;

    fullpath = RT_NULL;
    if (pathname == RT_NULL)
    {
#ifdef DFS_USING_WORKDIR
        /* open current working directory */
        path = rt_strdup(working_directory);
#else
        path = rt_strdup("/");
#endif
        if (path == RT_NULL)
            return ; /* out of memory */
    }
    else
    {
        path = (char *)pathname;
    }

    /* list directory */
    if (dfs_file_open(&fd, path, DFS_O_DIRECTORY) == 0)
    {
        rt_kprintf("Directory %s:\n", path);
        do
        {
            rt_memset(&dirent, 0, sizeof(struct dirent));
            length = dfs_file_getdents(&fd, &dirent, sizeof(struct dirent));
            if (length > 0)
            {
                rt_memset(&stat, 0, sizeof(struct stat));

                /* build full path for each file */
                fullpath = dfs_normalize_path(path, dirent.d_name);
                if (fullpath == RT_NULL) 
                    break;

                if (dfs_file_stat(fullpath, &stat) == 0)
                {
                    rt_kprintf("%-20s", dirent.d_name);
                    if ( DFS_S_ISDIR(stat.st_mode))
                    {
                        rt_kprintf("%-25s\n", "<DIR>");
                    }
                    else
                    {
                        rt_kprintf("%-25lu\n", stat.st_size);
                    }
                }
                else
                    rt_kprintf("BAD file: %s\n", dirent.d_name);
                rt_free(fullpath);
            }
        }while(length > 0);

        dfs_file_close(&fd);
    }
    else
    {
        rt_kprintf("No such directory\n");
    }
    if (pathname == RT_NULL) 
        rt_free(path);
}
FINSH_FUNCTION_EXPORT(ls, list directory contents);

void rm(const char *filename)
{
    if (dfs_file_unlink(filename) < 0)
    {
        rt_kprintf("Delete %s failed\n", filename);
    }
}
FINSH_FUNCTION_EXPORT(rm, remove files or directories);

void cat(const char* filename)
{
    rt_uint32_t length;
    char buffer[81];

    if (dfs_file_open(&fd, filename, DFS_O_RDONLY) < 0)
    {
        rt_kprintf("Open %s failed\n", filename);

        return;
    }

    do
    {
        rt_memset(buffer, 0, sizeof(buffer));
        length = dfs_file_read(&fd, buffer, sizeof(buffer)-1 );
        if (length > 0)
        {
            rt_kprintf("%s", buffer);
        }
    }while (length > 0);

    dfs_file_close(&fd);
}
FINSH_FUNCTION_EXPORT(cat, print file);

#define BUF_SZ  4096
static void copyfile(const char *src, const char *dst)
{
    struct dfs_fd src_fd;
    rt_uint8_t *block_ptr;
    rt_int32_t read_bytes;

    block_ptr = rt_malloc(BUF_SZ);
    if (block_ptr == RT_NULL)
    {
        rt_kprintf("out of memory\n");

        return;
    }

    if (dfs_file_open(&src_fd, src, DFS_O_RDONLY) < 0)
    {
        rt_free(block_ptr);
        rt_kprintf("Read %s failed\n", src);

        return;
    }
    if (dfs_file_open(&fd, dst, DFS_O_WRONLY | DFS_O_CREAT) < 0)
    {
        rt_free(block_ptr);
        dfs_file_close(&src_fd);

        rt_kprintf("Write %s failed\n", dst);

        return;
    }

    do
    {
        read_bytes = dfs_file_read(&src_fd, block_ptr, BUF_SZ);
        if (read_bytes > 0)
        {
			int length;
			
            length = dfs_file_write(&fd, block_ptr, read_bytes);
			if (length != read_bytes)
			{
				/* write failed. */
				rt_kprintf("Write file data failed, errno=%d\n", length);
				break;
			}
        }
    } while (read_bytes > 0);

    dfs_file_close(&src_fd);
    dfs_file_close(&fd);
    rt_free(block_ptr);
}

extern int mkdir(const char *path, mode_t mode);
static void copydir(const char * src, const char * dst)
{
    struct dfs_fd fd;
    struct dirent dirent;
    struct stat stat;
    int length;

    if (dfs_file_open(&fd, src, DFS_O_DIRECTORY) < 0)
    {
        rt_kprintf("open %s failed\n", src);
        return ;
    }

    do
    {
        rt_memset(&dirent, 0, sizeof(struct dirent));
        length = dfs_file_getdents(&fd, &dirent, sizeof(struct dirent));
        if (length > 0)
        {
            char * src_entry_full = RT_NULL;
            char * dst_entry_full = RT_NULL;

            if (strcmp(dirent.d_name, "..") == 0 || strcmp(dirent.d_name, ".") == 0)
                continue;

            /* build full path for each file */
            if ((src_entry_full = dfs_normalize_path(src, dirent.d_name)) == RT_NULL)
            {
                rt_kprintf("out of memory!\n");
                break;
            }
            if ((dst_entry_full = dfs_normalize_path(dst, dirent.d_name)) == RT_NULL)
            {
                rt_kprintf("out of memory!\n");
                rt_free(src_entry_full);
                break;
            }

            rt_memset(&stat, 0, sizeof(struct stat));
            if (dfs_file_stat(src_entry_full, &stat) != 0)
            {
                rt_kprintf("open file: %s failed\n", dirent.d_name);
                continue;
            }

            if (DFS_S_ISDIR(stat.st_mode))
            {
                mkdir(dst_entry_full, 0);
                copydir(src_entry_full, dst_entry_full);
            }
            else
            {
                copyfile(src_entry_full, dst_entry_full);
            }
            rt_free(src_entry_full);
            rt_free(dst_entry_full);
        }
    }while(length > 0);

    dfs_file_close(&fd);
}

static const char *_get_path_lastname(const char *path)
{
    char * ptr;
    if ((ptr = strrchr(path, '/')) == RT_NULL)
        return path;

    /* skip the '/' then return */
    return ++ptr;
}
void copy(const char *src, const char *dst)
{
#define FLAG_SRC_TYPE      0x03
#define FLAG_SRC_IS_DIR    0x01
#define FLAG_SRC_IS_FILE   0x02
#define FLAG_SRC_NON_EXSIT 0x00

#define FLAG_DST_TYPE      0x0C
#define FLAG_DST_IS_DIR    0x04
#define FLAG_DST_IS_FILE   0x08
#define FLAG_DST_NON_EXSIT 0x00

    struct stat stat;
    rt_uint32_t flag = 0;

    /* check the staus of src and dst */
    if (dfs_file_stat(src, &stat) < 0)
    {
        rt_kprintf("copy failed, bad %s\n", src);
        return;
    }
    if (DFS_S_ISDIR(stat.st_mode))
        flag |= FLAG_SRC_IS_DIR;
    else
        flag |= FLAG_SRC_IS_FILE;

    if (dfs_file_stat(dst, &stat) < 0)
    {
        flag |= FLAG_DST_NON_EXSIT;
    }
    else
    {
        if (DFS_S_ISDIR(stat.st_mode))
            flag |= FLAG_DST_IS_DIR;
        else
            flag |= FLAG_DST_IS_FILE;
    }

    //2. check status
    if ((flag & FLAG_SRC_IS_DIR) && (flag & FLAG_DST_IS_FILE))
    {
        rt_kprintf("cp faild, cp dir to file is not permitted!\n");
        return ;
    }

    //3. do copy
    if (flag & FLAG_SRC_IS_FILE)
    {
        if (flag & FLAG_DST_IS_DIR)
        {
            char * fdst;
            fdst = dfs_normalize_path(dst, _get_path_lastname(src));
            if (fdst == NULL)
            {
                rt_kprintf("out of memory\n");
                return;
            }
            copyfile(src, fdst);
            rt_free(fdst);
        }
        else
        {
            copyfile(src, dst);
        }
    }
    else //flag & FLAG_SRC_IS_DIR
    {
        if (flag & FLAG_DST_IS_DIR)
        {
            char * fdst;
            fdst = dfs_normalize_path(dst, _get_path_lastname(src));
            if (fdst == NULL)
            {
                rt_kprintf("out of memory\n");
                return;
            }
            mkdir(fdst, 0);
            copydir(src, fdst);
            rt_free(fdst);
        }
        else if ((flag & FLAG_DST_TYPE) == FLAG_DST_NON_EXSIT)
        {
            mkdir(dst, 0);
            copydir(src, dst);
        }
        else
        {
            copydir(src, dst);
        }
    }
}
FINSH_FUNCTION_EXPORT(copy, copy file or dir)

#endif
/* @} */

