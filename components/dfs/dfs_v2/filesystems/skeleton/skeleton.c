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
#include <dfs_fs.h>
#include <dfs_file.h>

#include "dfs_skt_fs.h"

int dfs_skt_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    return RT_EOK;
}

int dfs_skt_unmount(struct dfs_filesystem *fs)
{
    return RT_EOK;
}

int dfs_skt_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -RT_EIO;
}

int dfs_skt_read(struct dfs_file *file, void *buf, rt_size_t count)
{
    return count;
}

int dfs_skt_lseek(struct dfs_file *file, rt_off_t offset)
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

int dfs_skt_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    return RT_EOK;
}

int dfs_skt_getdents(struct dfs_file *file, struct dirent *dirp, rt_uint32_t count)
{
    return count * sizeof(struct dirent);
}

static const struct dfs_file_ops _skt_fops =
{
    dfs_skt_open,
    dfs_skt_close,
    dfs_skt_ioctl,
    dfs_skt_read,
    NULL, /* write */
    NULL, /* flush */
    dfs_skt_lseek,
    dfs_skt_getdents,
};

static const struct dfs_filesystem_ops _skt_fs =
{
    "skt",
    DFS_FS_FLAG_DEFAULT,
    &_skt_fops,

    dfs_skt_mount,
    dfs_skt_unmount,
    NULL, /* mkfs */
    NULL, /* statfs */

    NULL, /* unlink */
    dfs_skt_stat,
    NULL, /* rename */
};

int dfs_skt_init(void)
{
    /* register rom file system */
    dfs_register(&_skt_fs);
    return 0;
}
INIT_COMPONENT_EXPORT(dfs_skt_init);
