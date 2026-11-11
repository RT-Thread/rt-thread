/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-04-15     Bernard      the first version
 * 2013-05-05     Bernard      remove CRC for ramfs persistence
 * 2013-05-22     Bernard      fix the no entry issue.
 */
#include <dfs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_fs.h>
#include <rtthread.h>

#include "dfs_mnt.h"
#include "dfs_ramfs.h"

static rt_size_t dfs_ramfs_basename(const char *path, char *name, rt_size_t size)
{
    const char *start = RT_NULL;
    const char *p = path;
    rt_size_t len;

    RT_ASSERT(path != RT_NULL);
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(size > 0);

    while (*p)
    {
        while (*p == '/')
        {
            p++;
        }

        if (!*p)
        {
            break;
        }

        start = p;
        while (*p && *p != '/')
        {
            p++;
        }
    }

    if (start == RT_NULL)
    {
        name[0] = '\0';
        return 0;
    }

    len = p - start;
    if (len >= size)
    {
        rt_memcpy(name, start, size - 1);
        name[size - 1] = '\0';
    }
    else
    {
        rt_memcpy(name, start, len);
        name[len] = '\0';
    }

    return len;
}

int dfs_ramfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    struct dfs_ramfs *ramfs;

    if (data == NULL)
    {
        return -EIO;
    }

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

    buf->f_bsize = 512;
    buf->f_blocks = ramfs->memheap.pool_size / 512;
    buf->f_bfree = ramfs->memheap.available_size / 512;

    return RT_EOK;
}

int dfs_ramfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -EIO;
}

static struct ramfs_dirent *dfs_ramfs_lookup(struct dfs_ramfs *ramfs, const char *path, rt_size_t *size)
{
    char name[RAMFS_NAME_MAX];
    struct ramfs_dirent *dirent;

    if (dfs_ramfs_basename(path, name, sizeof(name)) >= sizeof(name))
    {
        return NULL;
    }

    if (name[0] == '\0') /* is root directory */
    {
        *size = 0;

        return &(ramfs->root);
    }

    for (dirent = rt_list_entry(ramfs->root.list.next, struct ramfs_dirent, list); dirent != &(ramfs->root);
         dirent = rt_list_entry(dirent->list.next, struct ramfs_dirent, list))
    {
        if (rt_strcmp(dirent->name, name) == 0)
        {
            *size = dirent->size;

            return dirent;
        }
    }

    /* not found */
    return NULL;
}

static ssize_t dfs_ramfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    ssize_t length;
    struct ramfs_dirent *dirent;

    dirent = (struct ramfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    if (*pos < 0 || *pos >= (off_t)file->vnode->size)
    {
        return 0;
    }

    if ((off_t)count < (off_t)file->vnode->size - *pos)
    {
        length = (ssize_t)count;
    }
    else
    {
        length = (ssize_t)((off_t)file->vnode->size - *pos);
    }

    if (length > 0)
    {
        rt_memcpy(buf, &(dirent->data[*pos]), length);
    }

    /* update file current position */
    *pos += length;

    return length;
}

static ssize_t dfs_ramfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    dirent = (struct ramfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    ramfs = dirent->fs;
    RT_ASSERT(ramfs != NULL);

    if (*pos < 0)
    {
        return -EINVAL;
    }

    if (*pos + (off_t)count > (off_t)file->vnode->size)
    {
        rt_uint8_t *ptr;

        ptr = rt_memheap_realloc(&(ramfs->memheap), dirent->data, (rt_size_t)(*pos + count));
        if (ptr == NULL)
        {
            rt_set_errno(-ENOMEM);

            return 0;
        }

        /* update dirent and file size */
        dirent->data = ptr;
        dirent->size = (rt_size_t)(*pos + count);
        file->vnode->size = dirent->size;
    }

    if (count > 0)
    {
        rt_memcpy(dirent->data + *pos, buf, count);
    }

    /* update file current position */
    *pos += count;

    return count;
}

static off_t dfs_ramfs_lseek(struct dfs_file *file, off_t offset, int wherece)
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

    if (offset < 0)
    {
        return -EINVAL;
    }

    if (offset <= (off_t)file->vnode->size)
    {
        return offset;
    }

    return -EIO;
}

static int dfs_ramfs_close(struct dfs_file *file)
{
    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        return 0;
    }

    file->vnode->data = NULL;

    return RT_EOK;
}

static int dfs_ramfs_open(struct dfs_file *file)
{
    rt_size_t size;
    struct dfs_ramfs *ramfs;
    struct ramfs_dirent *dirent;

    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        if (file->vnode->type == FT_DIRECTORY && !(file->flags & O_DIRECTORY))
        {
            return -ENOENT;
        }

        file->fpos = (file->flags & O_APPEND) ? file->vnode->size : 0;

        return 0;
    }

    ramfs = (struct dfs_ramfs *)file->dentry->mnt->data;
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
        {
            return -ENOENT;
        }
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
                rt_size_t name_len;

                /* create a file entry */
                dirent = (struct ramfs_dirent *)rt_memheap_alloc(&(ramfs->memheap), sizeof(struct ramfs_dirent));
                if (dirent == NULL)
                {
                    return -ENOMEM;
                }

                name_len = dfs_ramfs_basename(file->dentry->pathname, dirent->name, sizeof(dirent->name));
                if (name_len == 0 || name_len >= sizeof(dirent->name))
                {
                    rt_memheap_free(dirent);
                    return name_len == 0 ? -ENOENT : -ENAMETOOLONG;
                }

                dirent->mode = (file->vnode->mode & 0777) ? (file->vnode->mode & 0777) : 0644;
                file->vnode->mode = S_IFREG | dirent->mode;

                rt_list_init(&(dirent->list));
                dirent->data = NULL;
                dirent->size = 0;
                dirent->fs = ramfs;
                file->vnode->type = FT_REGULAR;

                /* add to the root directory */
                rt_list_insert_after(&(ramfs->root.list), &(dirent->list));
            }
            else
            {
                return -ENOENT;
            }
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

static int dfs_ramfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    rt_size_t size;
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    ramfs = (struct dfs_ramfs *)dentry->mnt->data;
    dirent = dfs_ramfs_lookup(ramfs, dentry->pathname, &size);

    if (dirent == NULL)
    {
        return -ENOENT;
    }

    st->st_dev = 0;
    if (dirent == &(ramfs->root))
    {
        st->st_mode = S_IFDIR | (dirent->mode & 0777);
    }
    else
    {
        st->st_mode = S_IFREG | (dirent->mode & 0777);
    }

    st->st_size = dirent->size;
    st->st_mtime = 0;

    return RT_EOK;
}

static int dfs_ramfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    rt_size_t index, end;
    struct dirent *d;
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    dirent = (struct ramfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    ramfs = dirent->fs;
    RT_ASSERT(ramfs != NULL);

    if (dirent != &(ramfs->root))
    {
        return -EINVAL;
    }

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
    {
        return -EINVAL;
    }

    end = file->fpos + count;
    index = 0;
    count = 0;
    for (dirent = rt_list_entry(dirent->list.next, struct ramfs_dirent, list); dirent != &(ramfs->root) && index < end;
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

static int dfs_ramfs_unlink(struct dfs_dentry *dentry)
{
    rt_size_t size;
    struct dfs_ramfs *ramfs;
    struct ramfs_dirent *dirent;

    ramfs = (struct dfs_ramfs *)dentry->mnt->data;
    RT_ASSERT(ramfs != NULL);

    dirent = dfs_ramfs_lookup(ramfs, dentry->pathname, &size);
    if (dirent == NULL)
    {
        return -ENOENT;
    }
    if (dirent == &(ramfs->root))
    {
        return -EBUSY;
    }

    rt_list_remove(&(dirent->list));
    if (dirent->data != NULL)
    {
        rt_memheap_free(dirent->data);
    }
    rt_memheap_free(dirent);

    return RT_EOK;
}

static int dfs_ramfs_rename(struct dfs_dentry *old_dentry, struct dfs_dentry *new_dentry)
{
    char name[RAMFS_NAME_MAX];
    rt_size_t size, name_len;
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;

    ramfs = (struct dfs_ramfs *)old_dentry->mnt->data;
    RT_ASSERT(ramfs != NULL);

    dirent = dfs_ramfs_lookup(ramfs, new_dentry->pathname, &size);
    if (dirent != NULL)
    {
        return -EEXIST;
    }

    dirent = dfs_ramfs_lookup(ramfs, old_dentry->pathname, &size);
    if (dirent == NULL)
    {
        return -ENOENT;
    }
    if (dirent == &(ramfs->root))
    {
        return -EBUSY;
    }

    name_len = dfs_ramfs_basename(new_dentry->pathname, name, sizeof(name));
    if (name_len == 0)
    {
        return -ENOENT;
    }
    if (name_len >= sizeof(name))
    {
        return -ENAMETOOLONG;
    }

    rt_strncpy(dirent->name, name, sizeof(dirent->name));

    return RT_EOK;
}

static struct dfs_vnode *dfs_ramfs_lookup_vnode(struct dfs_dentry *dentry)
{
    struct ramfs_dirent *dirent;
    struct dfs_ramfs *ramfs;
    rt_size_t size;
    struct dfs_vnode *vnode = NULL;

    ramfs = (struct dfs_ramfs *)dentry->mnt->data;
    dirent = dfs_ramfs_lookup(ramfs, dentry->pathname, &size);
    if (dirent == NULL)
    {
        return NULL;
    }

    vnode = dfs_vnode_create();
    if (vnode)
    {
        if (dirent == &(ramfs->root))
        {
            vnode->mode = S_IFDIR | (dirent->mode & 0777);
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            vnode->mode = S_IFREG | (dirent->mode & 0777);
            vnode->type = FT_REGULAR;
        }
        vnode->mnt = dentry->mnt;
        vnode->size = size;
    }

    return vnode;
}

static struct dfs_vnode *dfs_ramfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
    struct dfs_vnode *vnode = RT_NULL;

    if (type == FT_DIRECTORY)
    {
        return NULL;
    }

    vnode = dfs_vnode_create();
    if (vnode)
    {
        vnode->mnt = dentry->mnt;
        vnode->mode = S_IFREG | ((mode & 0777) ? (mode & 0777) : 0644);
        vnode->type = FT_REGULAR;
    }

    return vnode;
}

static int dfs_ramfs_free_vnode(struct dfs_vnode *vnode)
{
    if (vnode && vnode->ref_count <= 1)
    {
        vnode->data = NULL;
    }

    return 0;
}

static const struct dfs_file_ops _ram_fops = {
    .open = dfs_ramfs_open,
    .close = dfs_ramfs_close,
    .ioctl = dfs_ramfs_ioctl,
    .read = dfs_ramfs_read,
    .write = dfs_ramfs_write,
    .flush = NULL, /* flush */
    .lseek = dfs_ramfs_lseek,
    .getdents = dfs_ramfs_getdents,
};

static const struct dfs_filesystem_ops _ramfs = {
    "ram",
    DFS_FS_FLAG_DEFAULT,
    &_ram_fops,

    .mount = dfs_ramfs_mount,
    .umount = dfs_ramfs_unmount,
    .mkfs = NULL, /* mkfs */
    .statfs = dfs_ramfs_statfs,

    .unlink = dfs_ramfs_unlink,
    .stat = dfs_ramfs_stat,
    .rename = dfs_ramfs_rename,
    .lookup = dfs_ramfs_lookup_vnode,

    .create_vnode = dfs_ramfs_create_vnode,
    .free_vnode = dfs_ramfs_free_vnode,
};

static struct dfs_filesystem_type ramfs_type = {
    .fs_ops = &_ramfs,
};

int dfs_ramfs_init(void)
{
    /* register ram file system */
    dfs_register(&ramfs_type);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_ramfs_init);

struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size)
{
    struct dfs_ramfs *ramfs;
    rt_uint8_t *data_ptr;
    rt_err_t result;

    size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
    ramfs = (struct dfs_ramfs *)pool;

    data_ptr = (rt_uint8_t *)(ramfs + 1);
    size = size - sizeof(struct dfs_ramfs);
    size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);

    result = rt_memheap_init(&ramfs->memheap, "ramfs", data_ptr, size);
    if (result != RT_EOK)
    {
        return NULL;
    }
    /* detach this memheap object from the system */
    rt_object_detach((rt_object_t) & (ramfs->memheap));

    /* initialize ramfs object */
    ramfs->magic = RAMFS_MAGIC;
    ramfs->memheap.parent.type = RT_Object_Class_MemHeap | RT_Object_Class_Static;

    /* initialize root directory */
    rt_memset(&(ramfs->root), 0x00, sizeof(ramfs->root));
    rt_list_init(&(ramfs->root.list));
    ramfs->root.size = 0;
    ramfs->root.mode = 0755;
    strcpy(ramfs->root.name, ".");
    ramfs->root.fs = ramfs;

    return ramfs;
}
