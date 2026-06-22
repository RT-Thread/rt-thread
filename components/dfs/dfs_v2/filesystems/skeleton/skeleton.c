/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_dentry.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

#include "dfs_skt_fs.h"

int dfs_skt_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    return RT_EOK;
}

int dfs_skt_unmount(struct dfs_mnt *mnt)
{
    return RT_EOK;
}

int dfs_skt_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -RT_EIO;
}

ssize_t dfs_skt_read(struct dfs_file *file, void *buf, size_t count, dfs_off_t *pos)
{
    return count;
}

dfs_off_t dfs_skt_lseek(struct dfs_file *file, dfs_off_t offset, int wherece)
{
    return -RT_EIO;
}

int dfs_skt_close(struct dfs_file *file)
{
    return RT_EOK;
}

int dfs_skt_open(struct dfs_file *file)
{
    return RT_EOK;
}

int dfs_skt_stat(struct dfs_dentry *dentry, struct dfs_stat *st)
{
    return RT_EOK;
}

int dfs_skt_getdents(struct dfs_file *file, struct dirent *dirp, rt_uint32_t count)
{
    return count * sizeof(struct dirent);
}

static const struct dfs_file_ops _skt_fops =
{
    .open = dfs_skt_open,
    .close = dfs_skt_close,
    .ioctl = dfs_skt_ioctl,
    .read = dfs_skt_read,
    .lseek = dfs_skt_lseek,
    .getdents = dfs_skt_getdents,
};

static const struct dfs_filesystem_ops _skt_fs =
{
    .name = "skt",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_skt_fops,

    .mount = dfs_skt_mount,
    .umount = dfs_skt_unmount,

    .stat = dfs_skt_stat,
};

static struct dfs_filesystem_type _skt_type =
{
    .fs_ops = &_skt_fs,
};

int dfs_skt_init(void)
{
    /* register rom file system */
    dfs_register(&_skt_type);
    return 0;
}
INIT_COMPONENT_EXPORT(dfs_skt_init);
