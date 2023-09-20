/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     flybreak     the first version
 * 2023-02-01     xqyjlj       fix cannot open the same file repeatedly in 'w' mode
 * 2023-09-20     zmq810150896 adds truncate functionality and standardized unlink adaptations
 */

#include <rthw.h>
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

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

static int dfs_tmpfs_mount(struct dfs_mnt *mnt,
                           unsigned long rwflag,
                           const void *data)
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

        mnt->data = superblock;
    }
    else
    {
        return -1;
    }

    return RT_EOK;
}

static int dfs_tmpfs_unmount(struct dfs_mnt *mnt)
{
    struct tmpfs_sb *superblock;

    /* FIXME: don't unmount on busy. */
    superblock = (struct tmpfs_sb *)mnt->data;
    RT_ASSERT(superblock != NULL);

    mnt->data = NULL;
    _free_subdir(&(superblock->root));
    rt_free(superblock);

    return RT_EOK;
}

int dfs_tmpfs_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    struct tmpfs_sb *superblock;

    superblock = (struct tmpfs_sb *)mnt->data;
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

            LOG_D("tmpfile mmap ptr:%x , size:%d\n", d_file->data, mmap2->length);
            mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, d_file->data, mmap2->length, 0);
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

static ssize_t dfs_tmpfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    rt_size_t length;
    struct tmpfs_file *d_file;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    if (count < file->vnode->size - *pos)
        length = count;
    else
        length = file->vnode->size - *pos;

    if (length > 0)
        memcpy(buf, &(d_file->data[*pos]), length);

    /* update file current position */
    *pos += length;

    return length;
}

static ssize_t dfs_tmpfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    struct tmpfs_file *d_file;
    struct tmpfs_sb *superblock;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    superblock = d_file->sb;
    RT_ASSERT(superblock != NULL);

    if (count + *pos > file->vnode->size)
    {
        rt_uint8_t *ptr;
        ptr = rt_realloc(d_file->data, *pos + count);
        if (ptr == NULL)
        {
            rt_set_errno(-ENOMEM);
            return 0;
        }

        rt_spin_lock(&superblock->lock);
        superblock->df_size += (*pos - d_file->size + count);
        rt_spin_unlock(&superblock->lock);
        /* update d_file and file size */
        d_file->data = ptr;
        d_file->size = *pos + count;
        file->vnode->size = d_file->size;
        LOG_D("tmpfile ptr:%x, size:%d", ptr, d_file->size);
    }

    if (count > 0)
        memcpy(d_file->data + *pos, buf, count);

    /* update file current position */
    *pos += count;

    return count;
}

static off_t dfs_tmpfs_lseek(struct dfs_file *file, off_t offset, int wherece)
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

    if (offset <= (off_t)file->vnode->size)
    {
        return offset;
    }

    return -EIO;
}

static int dfs_tmpfs_close(struct dfs_file *file)
{
    struct tmpfs_file *d_file;

    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count != 1)
        return 0;

    d_file = (struct tmpfs_file *)file->vnode->data;

    if (d_file == NULL)
        return -ENOENT;

    if (d_file->fre_memory == RT_TRUE)
    {
        if (d_file->data != NULL)
        {
            rt_free(d_file->data);
            d_file->data = RT_NULL;
        }

        rt_free(d_file);
    }

    return RT_EOK;
}

static int dfs_tmpfs_open(struct dfs_file *file)
{
    struct tmpfs_file *d_file;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != RT_NULL);
    /* Creates a new file.
     * If the file is existing, it is truncated and overwritten.
     */
    if (file->flags & O_TRUNC)
    {
        d_file->size = 0;
        file->vnode->size = d_file->size;
        file->fpos = file->vnode->size;
        if (d_file->data != NULL)
        {
            /* ToDo: fix for rt-smart. */
            rt_free(d_file->data);
            d_file->data = NULL;
        }
    }

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

static int dfs_tmpfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    rt_size_t size;
    struct tmpfs_file *d_file;
    struct tmpfs_sb *superblock;

    superblock = (struct tmpfs_sb *)dentry->mnt->data;
    d_file = dfs_tmpfs_lookup(superblock, dentry->pathname, &size);

    if (d_file == NULL)
        return -ENOENT;

    st->st_dev = (dev_t)(size_t)(dentry->mnt->dev_id);
    st->st_ino = (ino_t)dfs_dentry_full_path_crc32(dentry);

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

static int dfs_tmpfs_getdents(struct dfs_file *file,
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

    end = file->fpos + count;
    index = 0;
    count = 0;

    rt_list_for_each(list, &d_file->subdirs)
    {
        n_file = rt_list_entry(list, struct tmpfs_file, sibling);
        if (index >= (rt_size_t)file->fpos)
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
            file->fpos += 1;
        }
        index += 1;
        if (index >= end)
        {
            break;
        }
    }

    return count * sizeof(struct dirent);
}

static int dfs_tmpfs_unlink(struct dfs_dentry *dentry)
{
    rt_size_t size;
    struct tmpfs_sb *superblock;
    struct tmpfs_file *d_file;

    superblock = (struct tmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    d_file = dfs_tmpfs_lookup(superblock, dentry->pathname, &size);
    if (d_file == NULL)
        return -ENOENT;

    rt_spin_lock(&superblock->lock);
    rt_list_remove(&(d_file->sibling));
    rt_spin_unlock(&superblock->lock);

    if (rt_atomic_load(&(dentry->ref_count)) == 1)
    {
        if (d_file->data != NULL)
        {
            rt_free(d_file->data);
            d_file->data = RT_NULL;
        }

        rt_free(d_file);
    }
    else
    {
        d_file->fre_memory = RT_TRUE;
    }

    return RT_EOK;
}

static int dfs_tmpfs_rename(struct dfs_dentry *old_dentry, struct dfs_dentry *new_dentry)
{
    struct tmpfs_file *d_file, *p_file;
    struct tmpfs_sb *superblock;
    rt_size_t size;
    char parent_path[DFS_PATH_MAX], file_name[TMPFS_NAME_MAX];

    superblock = (struct tmpfs_sb *)old_dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    d_file = dfs_tmpfs_lookup(superblock, new_dentry->pathname, &size);
    if (d_file != NULL)
        return -EEXIST;

    d_file = dfs_tmpfs_lookup(superblock, old_dentry->pathname, &size);
    if (d_file == NULL)
        return -ENOENT;

    /* find parent file */
    _path_separate(new_dentry->pathname, parent_path, file_name);
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

static struct dfs_vnode *_dfs_tmpfs_lookup(struct dfs_dentry *dentry)
{
    struct dfs_vnode *vnode = RT_NULL;
    rt_size_t size;
    struct tmpfs_sb *superblock;
    struct tmpfs_file *d_file;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct tmpfs_sb *)dentry->mnt->data;

    d_file = dfs_tmpfs_lookup(superblock, dentry->pathname, &size);
    if (d_file)
    {
        vnode = dfs_vnode_create();
        if (vnode)
        {
            if (d_file->type == TMPFS_TYPE_DIR)
            {
                vnode->mode = S_IFDIR | S_IRUSR | S_IWUSR | S_IXUSR;
                vnode->type = FT_DIRECTORY;
            }
            else
            {
                vnode->mode = S_IFREG | S_IRUSR | S_IWUSR | S_IXUSR;
                vnode->type = FT_REGULAR;
            }

            vnode->mnt = dentry->mnt;
            vnode->data = d_file;
            vnode->size = d_file->size;
        }
    }

    return vnode;
}

static struct dfs_vnode *dfs_tmpfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
    struct dfs_vnode *vnode = RT_NULL;
    rt_size_t size;
    struct tmpfs_sb *superblock;
    struct tmpfs_file *d_file, *p_file;
    char parent_path[DFS_PATH_MAX], file_name[TMPFS_NAME_MAX];

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct tmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    vnode = dfs_vnode_create();
    if (vnode)
    {
        /* find parent file */
        _path_separate(dentry->pathname, parent_path, file_name);
        if (file_name[0] == '\0') /* it's root dir */
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* open parent directory */
        p_file = dfs_tmpfs_lookup(superblock, parent_path, &size);
        if (p_file == NULL)
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* create a file entry */
        d_file = (struct tmpfs_file *)rt_calloc(1, sizeof(struct tmpfs_file));
        if (d_file == NULL)
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        superblock->df_size += sizeof(struct tmpfs_file);

        strncpy(d_file->name, file_name, TMPFS_NAME_MAX);

        rt_list_init(&(d_file->subdirs));
        rt_list_init(&(d_file->sibling));
        d_file->data = NULL;
        d_file->size = 0;
        d_file->sb = superblock;
        d_file->fre_memory = RT_FALSE;
        if (type == FT_DIRECTORY)
        {
            d_file->type = TMPFS_TYPE_DIR;
            vnode->mode = S_IFDIR | mode;
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            d_file->type = TMPFS_TYPE_FILE;
            vnode->mode = S_IFREG | mode;
            vnode->type = FT_REGULAR;
        }
        rt_spin_lock(&superblock->lock);
        rt_list_insert_after(&(p_file->subdirs), &(d_file->sibling));
        rt_spin_unlock(&superblock->lock);

        vnode->mnt = dentry->mnt;
        vnode->data = d_file;
        vnode->size = d_file->size;
    }

    return vnode;
}

static int dfs_tmpfs_free_vnode(struct dfs_vnode *vnode)
{
    /* nothing to be freed */
    if (vnode && vnode->ref_count <= 1)
    {
        vnode->data = NULL;
    }

    return 0;
}

static int dfs_tmpfs_truncate(struct dfs_file *file, off_t offset)
{
    struct tmpfs_file *d_file = RT_NULL;
    struct tmpfs_sb *superblock = RT_NULL;
    rt_uint8_t *ptr = RT_NULL;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != RT_NULL);

    superblock = d_file->sb;
    RT_ASSERT(superblock != RT_NULL);

    ptr = rt_realloc(d_file->data, offset);
    if (ptr == RT_NULL)
    {
        rt_set_errno(-ENOMEM);
        return 0;
    }

    rt_spin_lock(&superblock->lock);
    superblock->df_size = offset;
    rt_spin_unlock(&superblock->lock);

    /* update d_file and file size */
    d_file->data = ptr;
    d_file->size = offset;
    file->vnode->size = d_file->size;
    LOG_D("tmpfile ptr:%x, size:%d", ptr, d_file->size);

    return 0;
}

static const struct dfs_file_ops _tmp_fops =
{
    .open = dfs_tmpfs_open,
    .close = dfs_tmpfs_close,
    .ioctl = dfs_tmpfs_ioctl,
    .read = dfs_tmpfs_read,
    .write = dfs_tmpfs_write,
    .lseek = dfs_tmpfs_lseek,
    .getdents = dfs_tmpfs_getdents,
    .truncate = dfs_tmpfs_truncate,
};

static const struct dfs_filesystem_ops _tmpfs_ops =
{
    .name = "tmp",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_tmp_fops,

    .mount = dfs_tmpfs_mount,
    .umount = dfs_tmpfs_unmount,
    .statfs = dfs_tmpfs_statfs,

    .unlink = dfs_tmpfs_unlink,
    .stat = dfs_tmpfs_stat,
    .rename = dfs_tmpfs_rename,
    .lookup = _dfs_tmpfs_lookup,
    .create_vnode = dfs_tmpfs_create_vnode,
    .free_vnode = dfs_tmpfs_free_vnode
};

static struct dfs_filesystem_type _tmpfs =
{
    .fs_ops = &_tmpfs_ops,
};

int dfs_tmpfs_init(void)
{
    /* register tmp file system */
    dfs_register(&_tmpfs);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_tmpfs_init);
