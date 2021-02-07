/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

#define DFS_FNODE_HASH_NR 128

struct dfs_fnode_mgr
{
    struct rt_mutex lock;
    rt_list_t head[DFS_FNODE_HASH_NR];
};

static struct dfs_fnode_mgr dfs_fm;

void dfs_fnode_mgr_init(void)
{
    int i = 0;

    rt_mutex_init(&dfs_fm.lock, "dfs_mgr", RT_IPC_FLAG_PRIO);
    for (i = 0; i < DFS_FNODE_HASH_NR; i++)
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

    return (hash % DFS_FNODE_HASH_NR);
}

static struct dfs_fnode *dfs_fnode_find(const char *path, rt_list_t **hash_head)
{
    struct dfs_fnode *fnode = NULL;
    int hash = bkdr_hash(path);
    rt_list_t *hh;

    hh = dfs_fm.head[hash].next;

    if (hash_head)
    {
        *hash_head = &dfs_fm.head[hash];
    }

    while (hh != &dfs_fm.head[hash])
    {
        fnode = rt_container_of(hh, struct dfs_fnode, list);
        if (rt_strcmp(path, fnode->fullpath) == 0)
        {
            /* found */
            return fnode;
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
    struct dfs_fnode *fnode = NULL;
    int ret = 0;

    fullpath = dfs_normalize_path(NULL, pathname);

    rt_mutex_take(&dfs_fm.lock, RT_WAITING_FOREVER);
    fnode = dfs_fnode_find(fullpath, NULL);
    if (fnode)
    {
        ret = 1;
    }
    rt_mutex_release(&dfs_fm.lock);

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
int dfs_file_open(struct dfs_fd *fd, const char *path, int flags)
{
    struct dfs_filesystem *fs;
    char *fullpath;
    int result;
    struct dfs_fnode *fnode = NULL;
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

    rt_mutex_take(&dfs_fm.lock, RT_WAITING_FOREVER);
    /* fnode find */
    fnode = dfs_fnode_find(fullpath, &hash_head);
    if (fnode)
    {
        fnode->ref_count++;
        fd->pos   = 0;
        fd->fnode = fnode;
        rt_mutex_release(&dfs_fm.lock);
    }
    else
    {
        /* find filesystem */
        fs = dfs_filesystem_lookup(fullpath);
        if (fs == NULL)
        {
            rt_mutex_release(&dfs_fm.lock);
            rt_free(fullpath); /* release path */
            return -ENOENT;
        }

        fnode = rt_calloc(1, sizeof(struct dfs_fnode));
        if (!fnode)
        {
            rt_mutex_release(&dfs_fm.lock);
            rt_free(fullpath); /* release path */
            return -ENOMEM;
        }
        fnode->ref_count = 1;

        LOG_D("open in filesystem:%s", fs->ops->name);
        fnode->fs    = fs;             /* set file system */
        fnode->fops  = fs->ops->fops;  /* set file ops */

        /* initialize the fd item */
        fnode->type  = FT_REGULAR;
        fnode->flags = flags;

        if (!(fs->ops->flags & DFS_FS_FLAG_FULLPATH))
        {
            if (dfs_subdir(fs->path, fullpath) == NULL)
                fnode->path = rt_strdup("/");
            else
                fnode->path = rt_strdup(dfs_subdir(fs->path, fullpath));
            LOG_D("Actual file path: %s", fnode->path);
        }
        else
        {
            fnode->path = fullpath;
        }
        fnode->fullpath = fullpath;

        /* specific file system open routine */
        if (fnode->fops->open == NULL)
        {
            rt_mutex_release(&dfs_fm.lock);
            /* clear fd */
            if (fnode->path != fnode->fullpath)
            {
                rt_free(fnode->fullpath);
            }
            rt_free(fnode->path);
            rt_free(fnode);

            return -ENOSYS;
        }

        fd->pos   = 0;
        fd->fnode = fnode;

        /* insert fnode to hash */
        rt_list_insert_after(hash_head, &fnode->list);
    }

    if ((result = fnode->fops->open(fd)) < 0)
    {
        fnode->ref_count--;
        if (fnode->ref_count == 0)
        {
            /* remove from hash */
            rt_list_remove(&fnode->list);
            /* clear fd */
            if (fnode->path != fnode->fullpath)
            {
                rt_free(fnode->fullpath);
            }
            rt_free(fnode->path);
            fd->fnode = NULL;
            rt_free(fnode);
            rt_mutex_release(&dfs_fm.lock);
        }

        LOG_D("%s open failed", fullpath);

        return result;
    }

    fnode->flags |= DFS_F_OPEN;
    if (flags & O_DIRECTORY)
    {
        fnode->type = FT_DIRECTORY;
        fnode->flags |= DFS_F_DIRECTORY;
    }
    rt_mutex_release(&dfs_fm.lock);

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
int dfs_file_close(struct dfs_fd *fd)
{
    struct dfs_fnode *fnode = NULL;
    int result = 0;

    if (fd == NULL)
    {
        return -ENXIO;
    }

    if (fd->ref_count == 1)
    {
        rt_mutex_take(&dfs_fm.lock, RT_WAITING_FOREVER);
        fnode = fd->fnode;

        if (fnode->ref_count <= 0)
        {
            rt_mutex_release(&dfs_fm.lock);
            return -ENXIO;
        }

        if (fnode->fops->close != NULL)
        {
            result = fnode->fops->close(fd);
        }

        /* close fd error, return */
        if (result < 0)
        {
            rt_mutex_release(&dfs_fm.lock);
            return result;
        }

        if (fnode->ref_count == 1)
        {
            /* remove from hash */
            rt_list_remove(&fnode->list);
            fd->fnode = NULL;

            if (fnode->path != fnode->fullpath)
            {
                rt_free(fnode->fullpath);
            }
            rt_free(fnode->path);
            rt_free(fnode);
            rt_mutex_release(&dfs_fm.lock);
        }
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
int dfs_file_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    if (fd == NULL)
    {
        return -EINVAL;
    }

    /* regular file system fd */
    if (fd->fnode->type == FT_REGULAR || fd->fnode->type == FT_DEVICE)
    {
        switch (cmd)
        {
        case F_GETFL:
            return fd->fnode->flags; /* return flags */
        case F_SETFL:
            {
                int flags = (int)(rt_base_t)args;
                int mask  = O_NONBLOCK | O_APPEND;

                flags &= mask;
                fd->fnode->flags &= ~mask;
                fd->fnode->flags |= flags;
            }
            return 0;
        }
    }

    if (fd->fnode->fops->ioctl != NULL)
    {
        return fd->fnode->fops->ioctl(fd, cmd, args);
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
int dfs_file_read(struct dfs_fd *fd, void *buf, size_t len)
{
    int result = 0;

    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->fnode->fops->read == NULL)
    {
        return -ENOSYS;
    }

    if ((result = fd->fnode->fops->read(fd, buf, len)) < 0)
    {
        fd->fnode->flags |= DFS_F_EOF;
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
int dfs_file_getdents(struct dfs_fd *fd, struct dirent *dirp, size_t nbytes)
{
    /* parameter check */
    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->fnode->type != FT_DIRECTORY)
    {
        return -EINVAL;
    }

    if (fd->fnode->fops->getdents != NULL)
    {
        return fd->fnode->fops->getdents(fd, dirp, nbytes);
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
int dfs_file_write(struct dfs_fd *fd, const void *buf, size_t len)
{
    if (fd == NULL)
    {
        return -EINVAL;
    }

    if (fd->fnode->fops->write == NULL)
    {
        return -ENOSYS;
    }

    return fd->fnode->fops->write(fd, buf, len);
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

    if (fd->fnode->fops->flush == NULL)
        return -ENOSYS;

    return fd->fnode->fops->flush(fd);
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

    if (fd->fnode->fops->lseek == NULL)
        return -ENOSYS;

    result = fd->fnode->fops->lseek(fd, offset);

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
int dfs_file_ftruncate(struct dfs_fd *fd, off_t length)
{
    int result;

    /* fd is null or not a regular file system fd, or length is invalid */
    if (fd == NULL || fd->fnode->type != FT_REGULAR || length < 0)
        return -EINVAL;

    if (fd->fnode->fops->ioctl == NULL)
        return -ENOSYS;

    result = fd->fnode->fops->ioctl(fd, RT_FIOFTRUNCATE, (void*)&length);

    /* update current size */
    if (result == 0)
        fd->fnode->size = length;

    return result;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

void ls(const char *pathname)
{
    struct dfs_fd fd;
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
            memset(&dirent, 0, sizeof(struct dirent));
            length = dfs_file_getdents(&fd, &dirent, sizeof(struct dirent));
            if (length > 0)
            {
                memset(&stat, 0, sizeof(struct stat));

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
    struct dfs_fd fd;
    uint32_t length = 0;
    char buffer[81];

    fd_init(&fd);
    if (dfs_file_open(&fd, filename, O_RDONLY) < 0)
    {
        rt_kprintf("Open %s failed\n", filename);

        return;
    }

    do
    {
        length = dfs_file_read(&fd, buffer, sizeof(buffer) - 1);
        if (length > 0)
        {
            buffer[length] = '\0';
            rt_kprintf("%s", buffer);
        }
    }
    while (length > 0);

    dfs_file_close(&fd);
}
FINSH_FUNCTION_EXPORT(cat, print file);

#define BUF_SZ  4096
static void copyfile(const char *src, const char *dst)
{
    struct dfs_fd fd;
    struct dfs_fd src_fd;
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
    struct dfs_fd cpfd;
    if (dfs_file_open(&cpfd, src, O_DIRECTORY) < 0)
    {
        rt_kprintf("open %s failed\n", src);
        return ;
    }

    do
    {
        memset(&dirent, 0, sizeof(struct dirent));

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

            memset(&stat, 0, sizeof(struct stat));
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

#endif
/* @} */

