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
#ifdef RT_USING_PAGECACHE
#include "dfs_pcache.h"
#endif

#ifdef RT_USING_PAGECACHE
static ssize_t dfs_tmp_page_read(struct dfs_file *file, struct dfs_page *page);
static ssize_t dfs_tmp_page_write(struct dfs_page *page);

static struct dfs_aspace_ops dfs_tmp_aspace_ops =
{
    .read = dfs_tmp_page_read,
    .write = dfs_tmp_page_write,
};
#endif

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
    struct tmpfs_file *file = RT_NULL, *tmp;
    struct tmpfs_sb *superblock;

    RT_ASSERT(dfile->type == TMPFS_TYPE_DIR);

    dfs_vfs_for_each_subnode(file, tmp, dfile, node)
    {
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
        dfs_vfs_remove_node(&file->node);
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

        superblock->root.name[0] = '/';
        superblock->root.sb = superblock;
        superblock->root.type = TMPFS_TYPE_DIR;
        dfs_vfs_init_node(&superblock->root.node);

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
    RT_UNUSED(superblock);

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
    struct tmpfs_file *file, *curfile, *tmp;

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

    dfs_vfs_for_each_subnode(file, tmp, curfile, node)
    {
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
    ssize_t length;
    struct tmpfs_file *d_file;
    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    rt_mutex_take(&file->vnode->lock, RT_WAITING_FOREVER);
    ssize_t size = (ssize_t)file->vnode->size;
    if ((ssize_t)count < size - *pos)
        length = count;
    else
        length = size - *pos;

    if (length > 0)
        memcpy(buf, &(d_file->data[*pos]), length);

    /* update file current position */
    *pos += length;

    rt_mutex_release(&file->vnode->lock);

    return length;
}

static ssize_t _dfs_tmpfs_write(struct tmpfs_file *d_file, const void *buf, size_t count, off_t *pos)
{
    struct tmpfs_sb *superblock;

    RT_ASSERT(d_file != NULL);

    superblock = d_file->sb;
    RT_ASSERT(superblock != NULL);

    if (count + *pos > d_file->size)
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
        LOG_D("tmpfile ptr:%x, size:%d", ptr, d_file->size);
    }

    if (count > 0)
        memcpy(d_file->data + *pos, buf, count);

    /* update file current position */
    *pos += count;

    return count;
}

static ssize_t dfs_tmpfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    struct tmpfs_file *d_file;

    d_file = (struct tmpfs_file *)file->vnode->data;
    RT_ASSERT(d_file != NULL);

    rt_mutex_take(&file->vnode->lock, RT_WAITING_FOREVER);

    count = _dfs_tmpfs_write(d_file, buf, count, pos);

    rt_mutex_release(&file->vnode->lock);

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

    rt_mutex_detach(&file->vnode->lock);

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

    RT_ASSERT(file->vnode->ref_count > 0);
    if(file->vnode->ref_count == 1)
    {
        rt_mutex_init(&file->vnode->lock, file->dentry->pathname, RT_IPC_FLAG_PRIO);
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

    if (d_file->type == TMPFS_TYPE_DIR)
    {
        st->st_mode = S_IFDIR | (S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    else
    {
        st->st_mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
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
    struct tmpfs_file *d_file, *n_file, *tmp;
    struct tmpfs_sb *superblock;

    d_file = (struct tmpfs_file *)file->vnode->data;

    rt_mutex_take(&file->vnode->lock, RT_WAITING_FOREVER);

    superblock  = d_file->sb;
    RT_ASSERT(superblock != RT_NULL);
    RT_UNUSED(superblock);

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
    {
        rt_mutex_release(&file->vnode->lock);
        return -EINVAL;
    }

    end = file->fpos + count;
    index = 0;
    count = 0;

    dfs_vfs_for_each_subnode(n_file, tmp, d_file, node)
    {
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
    rt_mutex_release(&file->vnode->lock);

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
    dfs_vfs_remove_node(&d_file->node);
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
    char *parent_path;
    char file_name[TMPFS_NAME_MAX];

    superblock = (struct tmpfs_sb *)old_dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    d_file = dfs_tmpfs_lookup(superblock, new_dentry->pathname, &size);
    if (d_file != NULL)
        return -EEXIST;

    d_file = dfs_tmpfs_lookup(superblock, old_dentry->pathname, &size);
    if (d_file == NULL)
        return -ENOENT;

    parent_path = rt_malloc(DFS_PATH_MAX);
    if (!parent_path)
    {
        return -ENOMEM;
    }

    /* find parent file */
    _path_separate(new_dentry->pathname, parent_path, file_name);
    if (file_name[0] == '\0') /* it's root dir */
    {
        rt_free(parent_path);
        return -ENOENT;
    }
    /* open parent directory */
    p_file = dfs_tmpfs_lookup(superblock, parent_path, &size);
    RT_ASSERT(p_file != NULL);

    rt_spin_lock(&superblock->lock);
    dfs_vfs_remove_node(&d_file->node);
    rt_spin_unlock(&superblock->lock);

    strncpy(d_file->name, file_name, TMPFS_NAME_MAX);

    rt_spin_lock(&superblock->lock);
    dfs_vfs_append_node(&p_file->node, &d_file->node);
    rt_spin_unlock(&superblock->lock);

    rt_free(parent_path);

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
                vnode->mode = S_IFDIR | (S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
                vnode->type = FT_DIRECTORY;
            }
            else
            {
                vnode->mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
                vnode->type = FT_REGULAR;
#ifdef RT_USING_PAGECACHE
                vnode->aspace = dfs_aspace_create(dentry, vnode, &dfs_tmp_aspace_ops);
#endif
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
    char *parent_path;
    char file_name[TMPFS_NAME_MAX];

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct tmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    parent_path = rt_malloc(DFS_PATH_MAX);
    if (!parent_path)
    {
        return NULL;
    }

    vnode = dfs_vnode_create();
    if (vnode)
    {
        /* find parent file */
        _path_separate(dentry->pathname, parent_path, file_name);
        if (file_name[0] == '\0') /* it's root dir */
        {
            rt_free(parent_path);
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* open parent directory */
        p_file = dfs_tmpfs_lookup(superblock, parent_path, &size);
        if (p_file == NULL)
        {
            rt_free(parent_path);
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* create a file entry */
        d_file = (struct tmpfs_file *)rt_calloc(1, sizeof(struct tmpfs_file));
        if (d_file == NULL)
        {
            rt_free(parent_path);
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        superblock->df_size += sizeof(struct tmpfs_file);

        strncpy(d_file->name, file_name, TMPFS_NAME_MAX);

        dfs_vfs_init_node(&d_file->node);
        d_file->data = NULL;
        d_file->size = 0;
        d_file->sb = superblock;
        d_file->fre_memory = RT_FALSE;
        if (type == FT_DIRECTORY)
        {
            d_file->type = TMPFS_TYPE_DIR;
            vnode->mode = S_IFDIR | (S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            d_file->type = TMPFS_TYPE_FILE;
            vnode->mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
            vnode->type = FT_REGULAR;
#ifdef RT_USING_PAGECACHE
            vnode->aspace = dfs_aspace_create(dentry, vnode, &dfs_tmp_aspace_ops);
#endif
        }
        rt_spin_lock(&superblock->lock);
        dfs_vfs_append_node(&p_file->node, &d_file->node);
        rt_spin_unlock(&superblock->lock);

        vnode->mnt = dentry->mnt;
        vnode->data = d_file;
        vnode->size = d_file->size;
    }

    rt_free(parent_path);

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

#ifdef RT_USING_PAGECACHE
static ssize_t dfs_tmp_page_read(struct dfs_file *file, struct dfs_page *page)
{
    int ret = -EINVAL;

    if (page->page)
    {
        off_t fpos = page->fpos;
        ret = dfs_tmpfs_read(file, page->page, page->size, &fpos);
    }

    return ret;
}

ssize_t dfs_tmp_page_write(struct dfs_page *page)
{
    off_t pos;
    size_t count = 0;
    struct tmpfs_file *d_file;

    if (page->aspace->vnode->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    d_file = (struct tmpfs_file *)(page->aspace->vnode->data);
    RT_ASSERT(d_file != RT_NULL);

    rt_mutex_take(&page->aspace->vnode->lock, RT_WAITING_FOREVER);
    if (page->len > 0)
    {
        pos = page->fpos;
        count = _dfs_tmpfs_write(d_file, page->page, page->len, &pos);
    }
    rt_mutex_release(&page->aspace->vnode->lock);

    return count;
}
#endif

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
