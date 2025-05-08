/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_posix.h>
#include <dfs_mnt.h>
#include <dfs_dentry.h>

#include "proc.h"
#include "procfs.h"

#define PROC_DEBUG(...) //rt_kprintf

static int dfs_procfs_open(struct dfs_file *file)
{
    rt_err_t ret = RT_EOK;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;


    RT_ASSERT(file->ref_count > 0);

    // this file is opened and in an fdtable
    if (file->ref_count > 1)
    {
        file->fpos = 0;
        return ret;
    }

    if (entry->fops && entry->fops->open)
    {
        ret = entry->fops->open(file);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_close(struct dfs_file *file)
{
    rt_err_t ret = RT_EOK;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    RT_ASSERT(file->vnode->ref_count > 0);
    if (file->vnode->ref_count > 1)
    {
        return ret;
    }

    if (entry && entry->fops && entry->fops->close)
    {
        ret = entry->fops->close(file);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static ssize_t dfs_procfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    ssize_t ret = -RT_ERROR;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry && entry->fops && entry->fops->read)
    {
        ret = entry->fops->read(file, buf, count, pos);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static ssize_t dfs_procfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    ssize_t ret = -RT_ERROR;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry && entry->fops && entry->fops->write)
    {
        ret = entry->fops->write(file, buf, count, pos);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    int ret = -RT_ERROR;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry && entry->fops && entry->fops->ioctl)
    {
        ret = entry->fops->ioctl(file, cmd, args);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    int ret = 0;
    rt_uint32_t index = 0;
    struct dirent *d;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry)
    {
        struct proc_dentry *iter = RT_NULL, *tmp;

        /* make integer count */
        count = (count / sizeof(struct dirent));
        if (count == 0)
        {
            return -EINVAL;
        }

        dfs_vfs_for_each_subnode(iter, tmp, entry, node)
        {
            if (iter == RT_NULL)
            {
                break;
            }

            if (index >= file->fpos)
            {
                d = dirp + index - file->fpos;

                if (S_ISDIR(entry->mode))
                {
                    d->d_type = DT_DIR;
                }
                else if (S_ISLNK(entry->mode))
                {
                    d->d_type = DT_SYMLINK;
                }
                else
                {
                    d->d_type = DT_REG;
                }

                d->d_namlen = rt_strlen(iter->name);
                d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
                rt_strncpy(d->d_name, iter->name, rt_strlen(iter->name) + 1);

                ret ++;
            }

            index++;
            if (index - file->fpos >= count)
            {
                break;
            }
        }

        if (ret > 0)
        {
            file->fpos = index;
        }

        if (entry->fops && entry->fops->getdents && ret < count)
        {
            int r;

            file->fpos -= index;

            r = entry->fops->getdents(file, dirp + ret, (count - ret) * sizeof(struct dirent));

            ret = ret * sizeof(struct dirent);

            if (r > 0)
            {
                ret += r;
            }

            file->fpos += index;
        }
        else
        {
            ret = ret * sizeof(struct dirent);
        }
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int ret = -RT_ERROR;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry && entry->fops && entry->fops->poll)
    {
        ret = entry->fops->poll(file, req);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_flush(struct dfs_file *file)
{
    int ret = -RT_ERROR;
    struct proc_dentry *entry = (struct proc_dentry *)file->vnode->data;

    if (entry && entry->fops && entry->fops->flush)
    {
        ret = entry->fops->flush(file);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, file->dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    RT_ASSERT(mnt != RT_NULL);

    return RT_EOK;
}

static int dfs_procfs_umount(struct dfs_mnt *mnt)
{
    RT_ASSERT(mnt != RT_NULL);

    return RT_EOK;
}

static int dfs_procfs_readlink(struct dfs_dentry *dentry, char *buf, int len)
{
    int ret = 0;
    struct proc_dentry *entry = dfs_proc_find(dentry->pathname);

    if (entry)
    {
        if (S_ISLNK(entry->mode) && entry->data)
        {
            if (entry->ops && entry->ops->readlink)
            {
                ret = entry->ops->readlink(entry, buf, len);
            }
            else
            {
                rt_strncpy(buf, (const char *)entry->data, len);
                buf[len - 1] = '\0';
                ret = rt_strlen(buf);
            }
        }

        proc_release(entry);
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_unlink(struct dfs_dentry *dentry)
{
    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, dentry->pathname, -1);
    return -RT_ERROR;
}

static int dfs_procfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    int ret = RT_EOK;
    struct dfs_vnode *vnode;

    if (dentry && dentry->vnode)
    {
        vnode = dentry->vnode;

        st->st_dev = (dev_t)(dentry->mnt->dev_id);
        st->st_ino = (ino_t)dfs_dentry_full_path_crc32(dentry);

        st->st_gid = vnode->gid;
        st->st_uid = vnode->uid;
        st->st_mode = vnode->mode;
        st->st_nlink = vnode->nlink;
        st->st_size = vnode->size;
        st->st_mtim.tv_nsec = vnode->mtime.tv_nsec;
        st->st_mtim.tv_sec = vnode->mtime.tv_sec;
        st->st_ctim.tv_nsec = vnode->ctime.tv_nsec;
        st->st_ctim.tv_sec = vnode->ctime.tv_sec;
        st->st_atim.tv_nsec = vnode->atime.tv_nsec;
        st->st_atim.tv_sec = vnode->atime.tv_sec;
    }

    PROC_DEBUG(" %s %d >> %s ret: %d\n", __func__, __LINE__, dentry->pathname, ret);

    return ret;
}

static int dfs_procfs_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    if (mnt && buf)
    {
        buf->f_bsize = 512;
        buf->f_blocks = 2048 * 64; // 64M
        buf->f_bfree = buf->f_blocks;
        buf->f_bavail = buf->f_bfree;
    }

    PROC_DEBUG(" %s %d\n", __func__, __LINE__);

    return RT_EOK;
}

static struct dfs_vnode *dfs_procfs_lookup(struct dfs_dentry *dentry)
{
    struct dfs_vnode *vnode = RT_NULL;
    struct proc_dentry *entry = dfs_proc_find(dentry->pathname);

    if (entry)
    {
        vnode = dfs_vnode_create();
        if (vnode)
        {
            vnode->nlink = 1;
            vnode->size = 0;
            if (S_ISDIR(entry->mode))
            {
                vnode->mode = entry->mode;
                vnode->type = FT_DIRECTORY;
            }
            else if (S_ISLNK(entry->mode))
            {
                vnode->mode = entry->mode;
                vnode->type = FT_SYMLINK;
            }
            else
            {
                vnode->mode = entry->mode;
                vnode->type = FT_REGULAR;
            }

            vnode->data = entry;
            vnode->mnt = dentry->mnt;
        }

        proc_release(entry);
    }

    PROC_DEBUG(" %s %d >> %s\n", __func__, __LINE__, dentry->pathname);

    return vnode;
}

static struct dfs_vnode *dfs_procfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
    return RT_NULL;
}

static int dfs_procfs_free_vnode(struct dfs_vnode *vnode)
{
    return 0;
}

static const struct dfs_file_ops _procfs_fops =
{
    .open = dfs_procfs_open,
    .close = dfs_procfs_close,
    .lseek = generic_dfs_lseek,
    .read = dfs_procfs_read,
    .write = dfs_procfs_write,
    .ioctl = dfs_procfs_ioctl,
    .getdents = dfs_procfs_getdents,
    .poll = dfs_procfs_poll,
    .flush = dfs_procfs_flush,
};

static const struct dfs_filesystem_ops _procfs_ops =
{
    .name = "procfs",

    .default_fops = &_procfs_fops,

    .mount = dfs_procfs_mount,
    .umount = dfs_procfs_umount,
    .readlink   = dfs_procfs_readlink,
    .unlink = dfs_procfs_unlink,
    .stat = dfs_procfs_stat,
    .statfs = dfs_procfs_statfs,
    .lookup = dfs_procfs_lookup,
    .create_vnode = dfs_procfs_create_vnode,
    .free_vnode = dfs_procfs_free_vnode,
};

static struct dfs_filesystem_type _procfs =
{
    .fs_ops = &_procfs_ops,
};

int dfs_procfs_init(void)
{
    /* register procfs file system */
    dfs_register(&_procfs);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_procfs_init);

int proc_read_data(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    if (file->fpos >= file->vnode->size)
    {
        return 0;
    }

    if (file->data)
    {
        count = file->vnode->size - file->fpos >= count ? count : file->vnode->size - file->fpos;
        rt_strncpy(buf, file->data + file->fpos, count);

        file->fpos += count;
        *pos = file->fpos;
    }
    else
    {
        return 0;
    }

    return count;
}
