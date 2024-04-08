/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     flybreak     the first version
 * 2023-02-01     xqyjlj       fix cannot open the same file repeatedly in 'w' mode
 */

#include <rthw.h>
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#include <lwp_user_mm.h>
#endif

#include "dfs_tmpfs.h"

#define DBG_TAG              "tmpfs"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

static int _path_separate(const char *path, char *parent_path, char *file_name)
{
    const char *path_p, *path_q;

    RT_ASSERT(path[0] == '/');

    file_name[0] = '\0';
    path_p = path_q = &path[1];
__next_dir:
    while (*path_q != '/' && *path_q != '\0')
    {
        path_q++;
    }
    if (path_q != path_p) /*sub dir*/
    {
        if (*path_q != '\0')
        {
            path_q++;
            path_p = path_q;
            goto __next_dir;
        }
        else /* Last level dir */
        {
            rt_memcpy(parent_path, path, path_p - path - 1);
            parent_path[path_p - path - 1] = '\0';
            rt_memcpy(file_name, path_p, path_q - path_p);
            file_name[path_q - path_p] = '\0';
        }
    }
    if (parent_path[0] == 0)
    {
        parent_path[0] = '/';
        parent_path[1] = '\0';
    }
    LOG_D("parent_path: %s", parent_path);
    LOG_D("file_name: %s", file_name);

    return 0;
}

static int _get_subdir(const char *path, char *name)
{
    const char *subpath = path;
    while (*subpath == '/' && *subpath)
        subpath ++;
    while (*subpath != '/' && *subpath)
    {
        *name = *subpath;
        name ++;
        subpath ++;
    }
    return 0;
}

static int _free_subdir(struct tmpfs_file *dfile)
{
    struct tmpfs_file *file;
    rt_list_t *list, *temp_list;
    struct tmpfs_sb *superblock;

    RT_ASSERT(dfile->type == TMPFS_TYPE_DIR);

    rt_list_for_each_safe(list, temp_list, &dfile->subdirs)
    {
        file = rt_list_entry(list, struct tmpfs_file, sibling);
        if (file->type == TMPFS_TYPE_DIR)
        {
            _free_subdir(file);
        }
        if (file->data != NULL)
        {
            /* TODO: fix for rt-smart */
            rt_free(file->data);
        }

        superblock = file->sb;
        RT_ASSERT(superblock != NULL);

        rt_spin_lock(&superblock->lock);
        rt_list_remove(&(file->sibling));
        rt_spin_unlock(&superblock->lock);

        rt_free(file);
    }
    return 0;
}

int dfs_tmpfs_mount(struct dfs_filesystem *fs,
                    unsigned long          rwflag,
                    const void            *data)
{
    struct tmpfs_sb *superblock;

    superblock = rt_calloc(1, sizeof(struct tmpfs_sb));
    if (superblock)
    {
        superblock->df_size = sizeof(struct tmpfs_sb);
        superblock->magic = TMPFS_MAGIC;
        rt_list_init(&superblock->sibling);

        superblock->root.name[0] = '/';
        superblock->root.sb = superblock;
        superblock->root.type = TMPFS_TYPE_DIR;
        rt_list_init(&superblock->root.sibling);
        rt_list_init(&superblock->root.subdirs);

        rt_spin_lock_init(&superblock->lock);

        fs->data = superblock;
    }
    else
    {
        return -1;
    }

    return RT_EOK;
}

int dfs_tmpfs_unmount(struct dfs_filesystem *fs)
{
    struct tmpfs_sb *superblock;

    superblock = (struct tmpfs_sb *)fs->data;
    RT_ASSERT(superblock != NULL);

    _free_subdir(&(superblock->root));
    rt_free(superblock);

    fs->data = NULL;

    return RT_EOK;
}

int dfs_tmpfs_statfs(struct dfs_filesystem *fs, struct statfs *buf)
{
    struct tmpfs_sb *superblock;

    superblock = (struct tmpfs_sb *)fs->data;
    RT_ASSERT(superblock != NULL);
    RT_ASSERT(buf != NULL);

    buf->f_bsize  = 512;
    buf->f_blocks = (superblock->df_size + 511) / 512;
    buf->f_bfree  = 1;
    buf->f_bavail = buf->f_bfree;

    return RT_EOK;
}

int dfs_tmpfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    struct tmpfs_file *d_file;
    struct tmpfs_sb *superblock;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    superblock = d_file->sb;
    RT_ASSERT(superblock != NULL);

    switch (cmd)
    {
#ifdef RT_USING_SMART
    case RT_FIOMMAP2:
    {
        struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;
        if (mmap2)
        {
            if (mmap2->length > file->vnode->size)
            {
                return -RT_ENOMEM;
            }
            else if (mmap2->lwp == RT_NULL)
                return -RT_EINVAL;

            LOG_D("tmpfile mmap ptr:%x , size:%d\n", d_file->data, mmap2->length);
            mmap2->ret = lwp_map_user_phy(mmap2->lwp, mmap2->addr, d_file->data, mmap2->length, 0);
        }
        return RT_EOK;
        break;
    }
#endif
    default:
        break;
    }
    return -EIO;
}

struct tmpfs_file *dfs_tmpfs_lookup(struct tmpfs_sb  *superblock,
                                      const char       *path,
                                      rt_size_t        *size)
{
    const char *subpath, *curpath, *filename = RT_NULL;
    char subdir_name[TMPFS_NAME_MAX];
    struct tmpfs_file *file, *curfile;
    rt_list_t *list;

    subpath = path;
    while (*subpath == '/' && *subpath)
        subpath ++;
    if (! *subpath) /* is root directory */
    {
        *size = 0;
        return &(superblock->root);
    }

    curpath = subpath;
    curfile = &superblock->root;

find_subpath:
    while (*subpath != '/' && *subpath)
        subpath ++;

    if (! *subpath) /* is last directory */
        filename = curpath;
    else
        subpath ++; /* skip '/' */

    memset(subdir_name, 0, TMPFS_NAME_MAX);
    _get_subdir(curpath, subdir_name);

    rt_spin_lock(&superblock->lock);

    rt_list_for_each(list, &curfile->subdirs)
    {
        file = rt_list_entry(list, struct tmpfs_file, sibling);
        if (filename) /* find file */
        {
            if (rt_strcmp(file->name, filename) == 0)
            {
                *size = file->size;

                rt_spin_unlock(&superblock->lock);
                return file;
            }
        }
        else if (rt_strcmp(file->name, subdir_name) == 0)
        {
            *size = file->size;
            curpath = subpath;
            curfile = file;
            rt_spin_unlock(&superblock->lock);
            goto find_subpath;
        }
    }
    rt_spin_unlock(&superblock->lock);
    /* not found */
    return NULL;
}

ssize_t dfs_tmpfs_read(struct dfs_file *file, void *buf, size_t count)
{
    rt_size_t length;
    struct tmpfs_file *d_file;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    if (count < file->vnode->size - file->pos)
        length = count;
    else
        length = file->vnode->size - file->pos;

    if (length > 0)
        memcpy(buf, &(d_file->data[file->pos]), length);

    /* update file current position */
    file->pos += length;

    return length;
}


ssize_t dfs_tmpfs_write(struct dfs_file *fd, const void *buf, size_t count)
{
    struct tmpfs_file *d_file;
    struct tmpfs_sb *superblock;

    d_file = (struct tmpfs_file *)fd->vnode->data;
    RT_ASSERT(d_file != NULL);

    superblock = d_file->sb;
    RT_ASSERT(superblock != NULL);

    if (count + fd->pos > fd->vnode->size)
    {
        rt_uint8_t *ptr;
        ptr = rt_realloc(d_file->data, fd->pos + count);
        if (ptr == NULL)
        {
            rt_set_errno(-ENOMEM);
            return 0;
        }

        superblock->df_size += (fd->pos - d_file->size + count);
        /* update d_file and file size */
        d_file->data = ptr;
        d_file->size = fd->pos + count;
        fd->vnode->size = d_file->size;
        LOG_D("tmpfile ptr:%x, size:%d", ptr, d_file->size);
    }

    if (count > 0)
        memcpy(d_file->data + fd->pos, buf, count);

    /* update file current position */
    fd->pos += count;

    return count;
}

off_t dfs_tmpfs_lseek(struct dfs_file *file, off_t offset)
{
    if (offset <= (off_t)file->vnode->size)
    {
        file->pos = offset;

        return file->pos;
    }

    return -EIO;
}

int dfs_tmpfs_close(struct dfs_file *file)
{
    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        return 0;
    }

    file->vnode->data = NULL;

    return RT_EOK;
}

int dfs_tmpfs_open(struct dfs_file *file)
{
    rt_size_t size;
    struct tmpfs_sb *superblock;
    struct tmpfs_file *d_file, *p_file;
    struct dfs_filesystem *fs;
    char parent_path[DFS_PATH_MAX],file_name[TMPFS_NAME_MAX];

    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        if (file->vnode->type == FT_DIRECTORY
                && !(file->flags & O_DIRECTORY))
        {
            return -ENOENT;
        }
        file->pos = 0;
        return 0;
    }

    fs = file->vnode->fs;

    superblock = (struct tmpfs_sb *)fs->data;
    RT_ASSERT(superblock != NULL);

    /* find file */
    d_file = dfs_tmpfs_lookup(superblock, file->vnode->path, &size);
    if (d_file == NULL && !(file->flags & O_CREAT))
        return -ENOENT;

    /* Creates a new file. */
    if (file->flags & O_CREAT)
    {
        if (d_file == NULL)
        {
            /* find parent file */
            _path_separate(file->vnode->path, parent_path, file_name);
            if (file_name[0] == '\0') /* it's root dir */
                return -ENOENT;

            /* open parent directory */
            p_file = dfs_tmpfs_lookup(superblock, parent_path, &size);
            if (p_file == NULL)
                return -ENOENT;

            /* create a file entry */
            d_file = (struct tmpfs_file *)rt_calloc(1, sizeof(struct tmpfs_file));
            if (d_file == NULL)
            {
                return -ENOMEM;
            }
            superblock->df_size += sizeof(struct tmpfs_file);

            strncpy(d_file->name, file_name, TMPFS_NAME_MAX);

            rt_list_init(&(d_file->subdirs));
            rt_list_init(&(d_file->sibling));
            d_file->data = NULL;
            d_file->size = 0;
            d_file->sb   = superblock;
            if (file->flags & O_DIRECTORY)
            {
                d_file->type = TMPFS_TYPE_DIR;
            }
            else
            {
                d_file->type = TMPFS_TYPE_FILE;
            }
            rt_spin_lock(&superblock->lock);
            rt_list_insert_after(&(p_file->subdirs), &(d_file->sibling));
            rt_spin_unlock(&superblock->lock);
        }
    }
    /* Creates a new file.
        * If the file is existing, it is truncated and overwritten.
        */
    if (file->flags & O_TRUNC)
    {
        d_file->size = 0;
        if (d_file->data != NULL)
        {
            /* ToDo: fix for rt-smart. */
            rt_free(d_file->data);
            d_file->data = NULL;
        }
    }

    /* fill file */
    if (d_file->type == TMPFS_TYPE_DIR)
    {
        if (file->flags & O_DIRECTORY)
            file->vnode->type = FT_DIRECTORY;
        else
            return -ENOMEM;
    }
    else
    {
        if (file->flags & O_DIRECTORY)
        {
            return -ENOMEM;
        }
        file->vnode->type = FT_DEVICE;
    }

    file->vnode->data = d_file;
    file->vnode->size = d_file->size;
    if (file->flags & O_APPEND)
    {
        file->pos = file->vnode->size;
    }
    else
    {
        file->pos = 0;
    }

    return 0;
}

int dfs_tmpfs_stat(struct dfs_filesystem *fs,
                   const char            *path,
                   struct stat           *st)
{
    rt_size_t size;
    struct tmpfs_file *d_file;
    struct tmpfs_sb *superblock;

    superblock = (struct tmpfs_sb *)fs->data;
    d_file = dfs_tmpfs_lookup(superblock, path, &size);

    if (d_file == NULL)
        return -ENOENT;

    st->st_dev = (rt_device_t)dfs_filesystem_lookup(fs->path);
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                  S_IWUSR | S_IWGRP | S_IWOTH;
    if (d_file->type == TMPFS_TYPE_DIR)
    {
        st->st_mode &= ~S_IFREG;
        st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    }

    st->st_size = d_file->size;
    st->st_mtime = 0;

    return RT_EOK;
}

int dfs_tmpfs_getdents(struct dfs_file *file,
                       struct dirent *dirp,
                       uint32_t    count)
{
    rt_size_t index, end;
    struct dirent *d;
    struct tmpfs_file *d_file, *n_file;
    rt_list_t *list;
    struct tmpfs_sb *superblock;

    d_file = (struct tmpfs_file *)file->vnode->data;

    superblock  = d_file->sb;
    RT_ASSERT(superblock != RT_NULL);

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
        return -EINVAL;

    end = file->pos + count;
    index = 0;
    count = 0;

    rt_list_for_each(list, &d_file->subdirs)
    {
        n_file = rt_list_entry(list, struct tmpfs_file, sibling);
        if (index >= (rt_size_t)file->pos)
        {
            d = dirp + count;
            if (d_file->type == TMPFS_TYPE_FILE)
            {
                d->d_type = DT_REG;
            }
            if (d_file->type == TMPFS_TYPE_DIR)
            {
                d->d_type = DT_DIR;
            }
            d->d_namlen = RT_NAME_MAX;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, n_file->name, TMPFS_NAME_MAX);

            count += 1;
            file->pos += 1;
        }
        index += 1;
        if (index >= end)
        {
            break;
        }
    }

    return count * sizeof(struct dirent);
}

int dfs_tmpfs_unlink(struct dfs_filesystem *fs, const char *path)
{
    rt_size_t size;
    struct tmpfs_sb *superblock;
    struct tmpfs_file *d_file;

    superblock = (struct tmpfs_sb *)fs->data;
    RT_ASSERT(superblock != NULL);

    d_file = dfs_tmpfs_lookup(superblock, path, &size);
    if (d_file == NULL)
        return -ENOENT;

    rt_spin_lock(&superblock->lock);
    rt_list_remove(&(d_file->sibling));
    rt_spin_unlock(&superblock->lock);

    if (d_file->data != NULL)
        rt_free(d_file->data);
    rt_free(d_file);

    return RT_EOK;
}

int dfs_tmpfs_rename(struct dfs_filesystem *fs,
                     const char            *oldpath,
                     const char            *newpath)
{
    struct tmpfs_file *d_file, *p_file;
    struct tmpfs_sb *superblock;
    rt_size_t size;
    char parent_path[DFS_PATH_MAX],file_name[TMPFS_NAME_MAX];

    superblock = (struct tmpfs_sb *)fs->data;
    RT_ASSERT(superblock != NULL);

    d_file = dfs_tmpfs_lookup(superblock, newpath, &size);
    if (d_file != NULL)
        return -EEXIST;

    d_file = dfs_tmpfs_lookup(superblock, oldpath, &size);
    if (d_file == NULL)
        return -ENOENT;

    /* find parent file */
    _path_separate(newpath, parent_path, file_name);
    if (file_name[0] == '\0') /* it's root dir */
        return -ENOENT;
    /* open parent directory */
    p_file = dfs_tmpfs_lookup(superblock, parent_path, &size);
    RT_ASSERT(p_file != NULL);

    rt_spin_lock(&superblock->lock);
    rt_list_remove(&(d_file->sibling));
    rt_spin_unlock(&superblock->lock);

    strncpy(d_file->name, file_name, TMPFS_NAME_MAX);

    rt_spin_lock(&superblock->lock);
    rt_list_insert_after(&(p_file->subdirs), &(d_file->sibling));
    rt_spin_unlock(&superblock->lock);

    return RT_EOK;
}

static const struct dfs_file_ops _tmp_fops =
{
    dfs_tmpfs_open,
    dfs_tmpfs_close,
    dfs_tmpfs_ioctl,
    dfs_tmpfs_read,
    dfs_tmpfs_write,
    NULL, /* flush */
    dfs_tmpfs_lseek,
    dfs_tmpfs_getdents,
};

static const struct dfs_filesystem_ops _tmpfs =
{
    "tmp",
    DFS_FS_FLAG_DEFAULT,
    &_tmp_fops,

    dfs_tmpfs_mount,
    dfs_tmpfs_unmount,
    NULL, /* mkfs */
    dfs_tmpfs_statfs,

    dfs_tmpfs_unlink,
    dfs_tmpfs_stat,
    dfs_tmpfs_rename,
};

int dfs_tmpfs_init(void)
{
    /* register tmp file system */
    dfs_register(&_tmpfs);

    return 0;
}
