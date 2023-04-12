/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2011-12-08     Bernard      Merges rename patch from iamcacy.
 * 2015-05-27     Bernard      Fix the fd clear issue.
 * 2019-01-24     Bernard      Remove file repeatedly open check.
 */

#include <dfs.h>
#include <dfs_file.h>
#include <dfs_private.h>
#include <unistd.h>

#define DFS_VNODE_HASH_NR 128

struct dfs_vnode_mgr
{
    struct rt_mutex lock;
    rt_list_t head[DFS_VNODE_HASH_NR];
};

static struct dfs_vnode_mgr dfs_fm;

void dfs_fm_lock(void)
{
    rt_mutex_take(&dfs_fm.lock, RT_WAITING_FOREVER);
}

void dfs_fm_unlock(void)
{
    rt_mutex_release(&dfs_fm.lock);
}

void dfs_vnode_mgr_init(void)
{
    int i = 0;

    rt_mutex_init(&dfs_fm.lock, "dfs_mgr", RT_IPC_FLAG_PRIO);
    for (i = 0; i < DFS_VNODE_HASH_NR; i++)
    {
        rt_list_init(&dfs_fm.head[i]);
    }
}

/* BKDR Hash Function */
static unsigned int bkdr_hash(const char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash % DFS_VNODE_HASH_NR);
}

static struct dfs_vnode *dfs_vnode_find(const char *path, rt_list_t **hash_head)
{
    struct dfs_vnode *vnode = NULL;
    int hash = bkdr_hash(path);
    rt_list_t *hh;

    hh = dfs_fm.head[hash].next;

    if (hash_head)
    {
        *hash_head = &dfs_fm.head[hash];
    }

    while (hh != &dfs_fm.head[hash])
    {
        vnode = rt_container_of(hh, struct dfs_vnode, list);
        if (rt_strcmp(path, vnode->fullpath) == 0)
        {
            /* found */
            return vnode;
        }
        hh = hh->next;
    }
    return NULL;
}

/**
 * @addtogroup FileApi
 */

/*@{*/

/**
 * This function will return whether this file has been opend.
 *
 * @param pathname the file path name.
 *
 * @return 0 on file has been open successfully, -1 on open failed.
 */
int dfs_file_is_open(const char *pathname)
{
    char *fullpath = NULL;
    struct dfs_vnode *vnode = NULL;
    int ret = 0;

    fullpath = dfs_normalize_path(NULL, pathname);

    dfs_fm_lock();
    vnode = dfs_vnode_find(fullpath, NULL);
    if (vnode)
    {
        ret = 1;
    }
    dfs_fm_unlock();

    rt_free(fullpath);
    return ret;
}


/**
 * this function will open a file which specified by path with specified flags.
 *
 * @param fd the file descriptor pointer to return the corresponding result.
 * @param path the specified file path.
 * @param flags the flags for open operator.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_open(struct dfs_file *fd, const char *path, int flags)
{
    struct dfs_filesystem *fs;
    char *fullpath;
    int result;
    struct dfs_vnode *vnode = NULL;
    rt_list_t *hash_head;

    /* parameter check */
    if (fd == NULL)
        return -EINVAL;

    /* make sure we have an absolute path */
    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath == NULL)
    {
        return -ENOMEM;
    }

    LOG_D("open file:%s", fullpath);

    dfs_fm_lock();
    /* vnode find */
    vnode = dfs_vnode_find(fullpath, &hash_head);
    if (vnode)
    {
        vnode->ref_count++;
        fd->pos   = 0;
        fd->vnode = vnode;
        dfs_fm_unlock();
        rt_free(fullpath); /* release path */
    }
    else
    {
        /* find filesystem */
        fs = dfs_filesystem_lookup(fullpath);
        if (fs == NULL)
        {
            dfs_fm_unlock();
            rt_free(fullpath); /* release path */
            return -ENOENT;
        }

        vnode = rt_calloc(1, sizeof(struct dfs_vnode));
        if (!vnode)
        {
            dfs_fm_unlock();
            rt_free(fullpath); /* release path */
            return -ENOMEM;
        }
        vnode->ref_count = 1;

        LOG_D("open in filesystem:%s", fs->ops->name);
        vnode->fs    = fs;             /* set file system */
        vnode->fops  = fs->ops->fops;  /* set file ops */

        /* initialize the fd item */
        vnode->type  = FT_REGULAR;
        vnode->flags = 0;

        if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
        {
            if (dfs_subdir(fs->path, fullpath) == NULL)
                vnode->path = rt_strdup("/");
            else
                vnode->path = rt_strdup(dfs_subdir(fs->path, fullpath));
            LOG_D("Actual file path: %s", vnode->path);
        }
        else
        {
            vnode->path = fullpath;
        }
        vnode->fullpath = fullpath;

        /* specific file system open routine */
        if (vnode->fops->open == NULL)
        {
            dfs_fm_unlock();
            /* clear fd */
            if (vnode->path != vnode->fullpath)
            {
                rt_free(vnode->fullpath);
            }
            rt_free(vnode->path);
            rt_free(vnode);

            return -ENOSYS;
        }

        fd->pos   = 0;
        fd->vnode = vnode;

        /* insert vnode to hash */
        rt_list_insert_after(hash_head, &vnode->list);
    }

    fd->flags = flags;

    if ((result = vnode->fops->open(fd)) < 0)
    {
        vnode->ref_count--;
        if (vnode->ref_count == 0)
        {
            /* remove from hash */
            rt_list_remove(&vnode->list);
            /* clear fd */
            if (vnode->path != vnode->fullpath)
            {
                rt_free(vnode->fullpath);
            }
            rt_free(vnode->path);
            fd->vnode = NULL;
            rt_free(vnode);
        }

        dfs_fm_unlock();
        LOG_D("%s open failed", fullpath);

        return result;
    }

    fd->flags |= DFS_F_OPEN;
    if (flags & O_DIRECTORY)
    {
        fd->vnode->type = FT_DIRECTORY;
        fd->flags |= DFS_F_DIRECTORY;
    }
    dfs_fm_unlock();

    LOG_D("open successful");
    return 0;
}

/**
 * this function will close a file descriptor.
 *
 * @param fd the file descriptor to be closed.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_close(struct dfs_file *fd)
{
    struct dfs_vnode *vnode = NULL;
    int result = 0;

    if (fd == NULL)
    {
        return -ENXIO;
    }

    if (fd->ref_count == 1)
    {
        dfs_fm_lock();
        vnode = fd->vnode;

        if (vnode->ref_count <= 0)
        {
            dfs_fm_unlock();
            return -ENXIO;
        }

        if (vnode->fops->close != NULL)
        {
            result = vnode->fops->close(fd);
        }

        /* close fd error, return */
        if (result < 0)
        {
            dfs_fm_unlock();
            return result;
        }

        if (vnode->ref_count == 1)
        {
            /* remove from hash */
            rt_list_remove(&vnode->list);
            fd->vnode = NULL;

            if (vnode->path != vnode->fullpath)
            {
                rt_free(vnode->fullpath);
            }
            rt_free(vnode->path);
            rt_free(vnode);
        }
        dfs_fm_unlock();
    }

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
int dfs_file_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    if (fd == NULL)
    {
        return -EINVAL;
    }

    /* regular file system fd */
    if (fd->vnode->type == FT_REGULAR || fd->vnode->type == FT_DEVICE)
    {
        switch (cmd)
        {
        case F_GETFL:
            return fd->flags; /* return flags */
        case F_SETFL:
            {
                int flags = (int)(rt_base_t)args;
                int mask  = O_NONBLOCK | O_APPEND;

                flags &= mask;
                fd->flags &= ~mask;
                fd->flags |= flags;
            }
            return 0;
        }
    }

    if (fd->vnode->fops->ioctl != NULL)
    {
        return fd->vnode->fops->ioctl(fd, cmd, args);
    }

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
int dfs_file_read(struct dfs_file *fd, void *buf, size_t len)
{
    int result = 0;

    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->vnode->fops->read == NULL)
    {
        return -ENOSYS;
    }

    if ((result = fd->vnode->fops->read(fd, buf, len)) < 0)
    {
        fd->flags |= DFS_F_EOF;
    }

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
int dfs_file_getdents(struct dfs_file *fd, struct dirent *dirp, size_t nbytes)
{
    /* parameter check */
    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->vnode->type != FT_DIRECTORY)
    {
        return -EINVAL;
    }

    if (fd->vnode->fops->getdents != NULL)
    {
        return fd->vnode->fops->getdents(fd, dirp, nbytes);
    }

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

    /* Check whether file is already open */
    if (dfs_file_is_open(fullpath))
    {
        result = -EBUSY;
        goto __exit;
    }

    /* get filesystem */
    if ((fs = dfs_filesystem_lookup(fullpath)) == NULL)
    {
        result = -ENOENT;
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
int dfs_file_write(struct dfs_file *fd, const void *buf, size_t len)
{
    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->vnode->fops->write == NULL)
    {
        return -ENOSYS;
    }

    return fd->vnode->fops->write(fd, buf, len);
}

/**
 * this function will flush buffer on a file descriptor.
 *
 * @param fd the file descriptor.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_file_flush(struct dfs_file *fd)
{
    if (fd == NULL)
        return -EINVAL;

    if (fd->vnode->fops->flush == NULL)
        return -ENOSYS;

    return fd->vnode->fops->flush(fd);
}

/**
 * this function will seek the offset for specified file descriptor.
 *
 * @param fd the file descriptor.
 * @param offset the offset to be sought.
 *
 * @return the current position after seek.
 */
int dfs_file_lseek(struct dfs_file *fd, off_t offset)
{
    int result;

    if (fd == NULL)
        return -EINVAL;

    if (fd->vnode->fops->lseek == NULL)
        return -ENOSYS;

    result = fd->vnode->fops->lseek(fd, offset);

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
        LOG_E("can't find mounted filesystem on this path:%s", fullpath);
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
            LOG_E("the filesystem didn't implement this function");

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
    int result = RT_EOK;
    struct dfs_filesystem *oldfs = NULL, *newfs = NULL;
    char *oldfullpath = NULL, *newfullpath = NULL;

    newfullpath = NULL;
    oldfullpath = NULL;

    oldfullpath = dfs_normalize_path(NULL, oldpath);
    if (oldfullpath == NULL)
    {
        result = -ENOENT;
        goto __exit;
    }

    if (dfs_file_is_open((const char *)oldfullpath))
    {
        result = -EBUSY;
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
    if (oldfullpath)
    {
        rt_free(oldfullpath);
    }
    if (newfullpath)
    {
        rt_free(newfullpath);
    }

    /* not at same file system, return EXDEV */
    return result;
}

/**
 * this function is will cause the regular file referenced by fd
 * to be truncated to a size of precisely length bytes.
 *
 * @param fd the file descriptor.
 * @param length the length to be truncated.
 *
 * @return the status of truncated.
 */
int dfs_file_ftruncate(struct dfs_file *fd, off_t length)
{
    int result;

    /* fd is null or not a regular file system fd, or length is invalid */
    if (fd == NULL || fd->vnode->type != FT_REGULAR || length < 0)
        return -EINVAL;

    if (fd->vnode->fops->ioctl == NULL)
        return -ENOSYS;

    result = fd->vnode->fops->ioctl(fd, RT_FIOFTRUNCATE, (void*)&length);

    /* update current size */
    if (result == 0)
        fd->vnode->size = length;

    return result;
}

int dfs_file_mmap2(struct dfs_file *fd, struct dfs_mmap2_args *mmap2)
{
    int ret = 0;

    if (fd && mmap2)
    {
        if (fd->vnode->type != FT_DEVICE || !fd->vnode->fops->ioctl)
        {
            rt_set_errno(EINVAL);
        }
        else if (fd->vnode->type == FT_DEVICE && fd->vnode->fops->ioctl)
        {
            ret = fd->vnode->fops->ioctl(fd, RT_FIOMMAP2, mmap2);
            if (ret != 0)
            {
                ret = ret > 0? ret : -ret;
                rt_set_errno(ret);
            }
        }
    }

    return ret;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

void ls(const char *pathname)
{
    struct dfs_file fd;
    struct dirent dirent;
    struct stat stat;
    int length;
    char *fullpath, *path;

    fullpath = NULL;
    if (pathname == NULL)
    {
#ifdef DFS_USING_WORKDIR
        /* open current working directory */
        path = rt_strdup(working_directory);
#else
        path = rt_strdup("/");
#endif
        if (path == NULL)
            return ; /* out of memory */
    }
    else
    {
        path = (char *)pathname;
    }

    fd_init(&fd);
    /* list directory */
    if (dfs_file_open(&fd, path, O_DIRECTORY) == 0)
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
                if (fullpath == NULL)
                    break;

                if (dfs_file_stat(fullpath, &stat) == 0)
                {
                    rt_kprintf("%-20s", dirent.d_name);
                    if (S_ISDIR(stat.st_mode))
                    {
                        rt_kprintf("%-25s\n", "<DIR>");
                    }
                    else
                    {
                        rt_kprintf("%-25lu\n", (unsigned long)stat.st_size);
                    }
                }
                else
                    rt_kprintf("BAD file: %s\n", dirent.d_name);
                rt_free(fullpath);
            }
        }
        while (length > 0);

        dfs_file_close(&fd);
    }
    else
    {
        rt_kprintf("No such directory\n");
    }
    if (pathname == NULL)
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

void cat(const char *filename)
{
    struct dfs_file fd;
    int length = 0;
    char buffer[81];

    fd_init(&fd);
    if (dfs_file_open(&fd, filename, O_RDONLY) < 0)
    {
        rt_kprintf("Open %s failed\n", filename);

        return;
    }

    do
    {
        rt_memset(buffer, 0x0, sizeof(buffer));
        length = dfs_file_read(&fd, (void *)buffer, sizeof(buffer) - 1);
        if (length > 0)
        {
            buffer[length] = '\0';
            rt_device_t out_device = rt_console_get_device();
            rt_device_write(out_device, 0, (void *)buffer, sizeof(buffer));
        }
    } while (length > 0);
    rt_kprintf("\n");

    dfs_file_close(&fd);
}
FINSH_FUNCTION_EXPORT(cat, print file);

#ifdef DFS_USING_POSIX
#define BUF_SZ  4096
static void copyfile(const char *src, const char *dst)
{
    struct dfs_file fd;
    struct dfs_file src_fd;
    rt_uint8_t *block_ptr;
    rt_int32_t read_bytes;

    block_ptr = (rt_uint8_t *)rt_malloc(BUF_SZ);
    if (block_ptr == NULL)
    {
        rt_kprintf("out of memory\n");

        return;
    }

    fd_init(&src_fd);
    if (dfs_file_open(&src_fd, src, O_RDONLY) < 0)
    {
        rt_free(block_ptr);
        rt_kprintf("Read %s failed\n", src);

        return;
    }
    fd_init(&fd);
    if (dfs_file_open(&fd, dst, O_WRONLY | O_CREAT) < 0)
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
    }
    while (read_bytes > 0);

    dfs_file_close(&src_fd);
    dfs_file_close(&fd);
    rt_free(block_ptr);
}

extern int mkdir(const char *path, mode_t mode);
static void copydir(const char *src, const char *dst)
{
    struct dirent dirent;
    struct stat stat;
    int length;
    struct dfs_file cpfd;
    if (dfs_file_open(&cpfd, src, O_DIRECTORY) < 0)
    {
        rt_kprintf("open %s failed\n", src);
        return ;
    }

    do
    {
        rt_memset(&dirent, 0, sizeof(struct dirent));

        length = dfs_file_getdents(&cpfd, &dirent, sizeof(struct dirent));
        if (length > 0)
        {
            char *src_entry_full = NULL;
            char *dst_entry_full = NULL;

            if (strcmp(dirent.d_name, "..") == 0 || strcmp(dirent.d_name, ".") == 0)
                continue;

            /* build full path for each file */
            if ((src_entry_full = dfs_normalize_path(src, dirent.d_name)) == NULL)
            {
                rt_kprintf("out of memory!\n");
                break;
            }
            if ((dst_entry_full = dfs_normalize_path(dst, dirent.d_name)) == NULL)
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

            if (S_ISDIR(stat.st_mode))
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
    }
    while (length > 0);

    dfs_file_close(&cpfd);
}

static const char *_get_path_lastname(const char *path)
{
    char *ptr;
    if ((ptr = (char *)strrchr(path, '/')) == NULL)
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
    uint32_t flag = 0;

    /* check the staus of src and dst */
    if (dfs_file_stat(src, &stat) < 0)
    {
        rt_kprintf("copy failed, bad %s\n", src);
        return;
    }
    if (S_ISDIR(stat.st_mode))
        flag |= FLAG_SRC_IS_DIR;
    else
        flag |= FLAG_SRC_IS_FILE;

    if (dfs_file_stat(dst, &stat) < 0)
    {
        flag |= FLAG_DST_NON_EXSIT;
    }
    else
    {
        if (S_ISDIR(stat.st_mode))
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
            char *fdst;
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
            char *fdst;
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
#endif /* DFS_USING_POSIX */

#endif /* RT_USING_FINSH */
/* @} */

