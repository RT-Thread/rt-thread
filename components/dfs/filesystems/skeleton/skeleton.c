/*
 * File      : skeleton.c
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>

#include "dfs_skt_fs.h"

int dfs_skt_mount(struct dfs_filesystem* fs, unsigned long rwflag, const void* data)
{
    return RT_EOK;
}

int dfs_skt_unmount(struct dfs_filesystem* fs)
{
    return RT_EOK;
}

int dfs_skt_ioctl(struct dfs_fd* file, int cmd, void* args)
{
    return -RT_EIO;
}

int dfs_skt_read(struct dfs_fd* file, void *buf, rt_size_t count)
{
    return count;
}

int dfs_skt_lseek(struct dfs_fd* file, rt_off_t offset)
{
    return -RT_EIO;
}

int dfs_skt_close(struct dfs_fd* file)
{
    return RT_EOK;
}

int dfs_skt_open(struct dfs_fd* file)
{
    return RT_EOK;
}

int dfs_skt_stat(struct dfs_filesystem* fs, const char *path, struct stat *st)
{
    return RT_EOK;
}

int dfs_skt_getdents(struct dfs_fd* file, struct dirent* dirp, rt_uint32_t count)
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

