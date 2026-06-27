/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-04-15     Bernard      the first version
 * 2013-05-05     Bernard      remove CRC for ramfs persistence
 * 2013-05-22     Bernard      fix the no entry issue.
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

#include "dfs_ramfs.h"

int dfs_ramfs_mount(struct dfs_mnt *mnt,
                    unsigned long rwflag,
                    const void *data)
{
    struct dfs_ramfs *ramfs;

    if (data == NULL)
        return -EIO;

    ramfs = (struct dfs_ramfs *)data;
    mnt->data = ramfs;

    return RT_EOK;
}

int dfs_ramfs_unmount(struct dfs_mnt *mnt)
{
    mnt->data = NULL;

    return RT_EOK;
}

int dfs_ramfs_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    struct dfs_ramfs *ramfs;

    ramfs = (struct dfs_ramfs *)mnt->data;
    RT_ASSERT(ramfs != NULL);
    RT_ASSERT(buf != NULL);

    buf->f_bsize  = 512;
    buf->f_blocks = ramfs->memheap.pool_size / 512;
    buf->f_bfree  = ramfs->memheap.available_size / 512;

    return RT_EOK;
}

int dfs_ramfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -EIO;
}

struct ramfs_dirent *dfs_ramfs_lookup(struct dfs_ramfs *ramfs,
                                      const char       *path,
                                      rt_size_t        *size)
{
    const char *subpath;
    struct ramfs_dirent *dirent;

    subpath = path;
    while (*subpath == '/' && *subpath)
        subpath ++;
    if (! *subpath) /* is root directory */
    {
        *size = 0;

        return &(ramfs->root);
    }

    for (dirent = rt_list_entry(ramfs->root.list.next, struct ramfs_dirent, list);
         dirent != &(ramfs->root);
         dirent = rt_list_entry(dirent->list.next, struct ramfs_dirent, list))
    {
        if (rt_strcmp(dirent->name, subpath) == 0)
        {
            *size = dirent->size;

            return dirent;
        }
    }

    /* not found */
    return NULL;
}

ssize_t dfs_ramfs_read(struct dfs_file *file, void *buf, size_t count, dfs_off_t *pos)
{
    ssize_t length;
    struct ramfs_dirent *dirent;

    dirent = (struct ramfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    if ((dfs_off_t)count < file->vnode->size - *pos)
        length = count;
    else
        length = file->vnode->size - *pos;

    if (length > 0)
        rt_memcpy(buf, &(dirent->data[*pos]), length);

    /* update file current position */
    *pos += length;

    return length;
}

ssize_t dfs_ramfs_write(struct dfs_file *file, const void *buf, size_t count, dfs_off_t *pos)
{
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    dirent = (struct ramfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    ramfs = dirent->fs;
    RT_ASSERT(ramfs != NULL);

    if ((dfs_off_t)count + *pos > file->vnode->size)
    {
        rt_uint8_t *ptr;
        ptr = rt_memheap_realloc(&(ramfs->memheap), dirent->data, *pos + count);
        if (ptr == NULL)
        {
            rt_set_errno(-ENOMEM);

            return 0;
        }

        /* update dirent and file size */
        dirent->data = ptr;
        dirent->size = *pos + count;
        file->vnode->size = dirent->size;
    }

    if (count > 0)
        rt_memcpy(dirent->data + *pos, buf, count);

    /* update file current position */
    *pos += count;

    return count;
}

dfs_off_t dfs_ramfs_lseek(struct dfs_file *file, dfs_off_t offset, int wherece)
{
    switch (wherece)
    {
    case SEEK_SET:
        break;

    case SEEK_CUR:
        offset += file->fpos;
        break;

    case SEEK_END:
        offset += file->vnode->size;
        break;

    default:
        return -EINVAL;
    }

    if (offset <= (dfs_off_t)file->vnode->size)
    {
        return offset;
    }

    return -EIO;
}

int dfs_ramfs_close(struct dfs_file *file)
{
    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        return 0;
    }

    file->vnode->data = NULL;

    return RT_EOK;
}

int dfs_ramfs_open(struct dfs_file *file)
{
    rt_size_t size;
    struct dfs_ramfs *ramfs;
    struct ramfs_dirent *dirent;

    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        if (file->vnode->type == FT_DIRECTORY
                && !(file->flags & O_DIRECTORY))
        {
            return -ENOENT;
        }
        file->fpos = 0;
        return 0;
    }

    ramfs = (struct dfs_ramfs *)file->vnode->mnt->data;
    RT_ASSERT(ramfs != NULL);

    if (file->flags & O_DIRECTORY)
    {
        if (file->flags & O_CREAT)
        {
            return -ENOSPC;
        }

        /* open directory */
        dirent = dfs_ramfs_lookup(ramfs, file->dentry->pathname, &size);
        if (dirent == NULL)
            return -ENOENT;
        if (dirent == &(ramfs->root)) /* it's root directory */
        {
            if (!(file->flags & O_DIRECTORY))
            {
                return -ENOENT;
            }
        }
        file->vnode->type = FT_DIRECTORY;
    }
    else
    {
        dirent = dfs_ramfs_lookup(ramfs, file->dentry->pathname, &size);
        if (dirent == &(ramfs->root)) /* it's root directory */
        {
            return -ENOENT;
        }

        if (dirent == NULL)
        {
            if (file->flags & O_CREAT || file->flags & O_WRONLY)
            {
                char *name_ptr;

                /* create a file entry */
                dirent = (struct ramfs_dirent *)
                         rt_memheap_alloc(&(ramfs->memheap),
                                          sizeof(struct ramfs_dirent));
                if (dirent == NULL)
                {
                    return -ENOMEM;
                }

                /* remove '/' separator */
                name_ptr = file->dentry->pathname;
                while (*name_ptr == '/' && *name_ptr)
                {
                    name_ptr++;
                }
                strncpy(dirent->name, name_ptr, RAMFS_NAME_MAX);

                rt_list_init(&(dirent->list));
                dirent->data = NULL;
                dirent->size = 0;
                dirent->fs = ramfs;
                file->vnode->type = FT_DIRECTORY;

                /* add to the root directory */
                rt_list_insert_after(&(ramfs->root.list), &(dirent->list));
            }
            else
                return -ENOENT;
        }

        /* Creates a new file.
         * If the file is existing, it is truncated and overwritten.
         */
        if (file->flags & O_TRUNC)
        {
            dirent->size = 0;
            if (dirent->data != NULL)
            {
                rt_memheap_free(dirent->data);
                dirent->data = NULL;
            }
        }
    }

    file->vnode->data = dirent;
    file->vnode->size = dirent->size;
    if (file->flags & O_APPEND)
    {
        file->fpos = file->vnode->size;
    }
    else
    {
        file->fpos = 0;
    }

    return 0;
}

int dfs_ramfs_stat(struct dfs_dentry *dentry, struct dfs_stat *st)
{
    rt_size_t size;
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    ramfs = (struct dfs_ramfs *)dentry->mnt->data;
    dirent = dfs_ramfs_lookup(ramfs, dentry->pathname, &size);

    if (dirent == NULL)
        return -ENOENT;

    st->st_dev = 0;
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                  S_IWUSR | S_IWGRP | S_IWOTH;

    st->st_size = dirent->size;
    st->mtime = 0;

    return RT_EOK;
}

int dfs_ramfs_getdents(struct dfs_file *file,
                       struct dirent *dirp,
                       uint32_t    count)
{
    rt_size_t index, end;
    struct dirent *d;
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    dirent = (struct ramfs_dirent *)file->vnode->data;

    ramfs  = dirent->fs;
    RT_ASSERT(ramfs != RT_NULL);

    if (dirent != &(ramfs->root))
        return -EINVAL;

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
        return -EINVAL;

    end = file->fpos + count;
    index = 0;
    count = 0;
    for (dirent = rt_list_entry(dirent->list.next, struct ramfs_dirent, list);
         dirent != &(ramfs->root) && index < end;
         dirent = rt_list_entry(dirent->list.next, struct ramfs_dirent, list))
    {
        if (index >= (rt_size_t)file->fpos)
        {
            d = dirp + count;
            d->d_type = DT_REG;
            d->d_namlen = RT_NAME_MAX;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, dirent->name, RAMFS_NAME_MAX);

            count += 1;
            file->fpos += 1;
        }
        index += 1;
    }

    return count * sizeof(struct dirent);
}

int dfs_ramfs_unlink(struct dfs_dentry *dentry)
{
    rt_size_t size;
    struct dfs_ramfs *ramfs;
    struct ramfs_dirent *dirent;

    ramfs = (struct dfs_ramfs *)dentry->mnt->data;
    RT_ASSERT(ramfs != NULL);

    dirent = dfs_ramfs_lookup(ramfs, dentry->pathname, &size);
    if (dirent == NULL)
        return -ENOENT;

    rt_list_remove(&(dirent->list));
    if (dirent->data != NULL)
        rt_memheap_free(dirent->data);
    rt_memheap_free(dirent);

    return RT_EOK;
}

int dfs_ramfs_rename(struct dfs_dentry *old_dentry, struct dfs_dentry *new_dentry)
{
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;
    rt_size_t size;

    ramfs = (struct dfs_ramfs *)old_dentry->mnt->data;
    RT_ASSERT(ramfs != NULL);

    dirent = dfs_ramfs_lookup(ramfs, new_dentry->pathname, &size);
    if (dirent != NULL)
        return -EEXIST;

    dirent = dfs_ramfs_lookup(ramfs, old_dentry->pathname, &size);
    if (dirent == NULL)
        return -ENOENT;

    strncpy(dirent->name, new_dentry->pathname, RAMFS_NAME_MAX);

    return RT_EOK;
}

static const struct dfs_file_ops _ram_fops =
{
    .open = dfs_ramfs_open,
    .close = dfs_ramfs_close,
    .ioctl = dfs_ramfs_ioctl,
    .read = dfs_ramfs_read,
    .write = dfs_ramfs_write,
    .lseek = dfs_ramfs_lseek,
    .getdents = dfs_ramfs_getdents,
};

static const struct dfs_filesystem_ops _ramfs =
{
    .name = "ram",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_ram_fops,

    .mount = dfs_ramfs_mount,
    .umount = dfs_ramfs_unmount,
    .statfs = dfs_ramfs_statfs,

    .unlink = dfs_ramfs_unlink,
    .stat = dfs_ramfs_stat,
    .rename = dfs_ramfs_rename,
};

static struct dfs_filesystem_type _ramfs_type =
{
    .fs_ops = &_ramfs,
};

int dfs_ramfs_init(void)
{
    /* register ram file system */
    dfs_register(&_ramfs_type);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_ramfs_init);

struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size)
{
    struct dfs_ramfs *ramfs;
    rt_uint8_t *data_ptr;
    rt_err_t result;

    size  = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
    ramfs = (struct dfs_ramfs *)pool;

    data_ptr = (rt_uint8_t *)(ramfs + 1);
    size = size - sizeof(struct dfs_ramfs);
    size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);

    result = rt_memheap_init(&ramfs->memheap, "ramfs", data_ptr, size);
    if (result != RT_EOK)
        return NULL;
    /* detach this memheap object from the system */
    rt_object_detach((rt_object_t) & (ramfs->memheap));

    /* initialize ramfs object */
    ramfs->magic = RAMFS_MAGIC;
    ramfs->memheap.parent.type = RT_Object_Class_MemHeap | RT_Object_Class_Static;

    /* initialize root directory */
    rt_memset(&(ramfs->root), 0x00, sizeof(ramfs->root));
    rt_list_init(&(ramfs->root.list));
    ramfs->root.size = 0;
    strcpy(ramfs->root.name, ".");
    ramfs->root.fs = ramfs;

    return ramfs;
}

