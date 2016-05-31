/*
 * File      : dfs_net.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015-2016, RT-Thread Development Team
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
 * 2015-02-17     Bernard      First version
 * 2016-05-07     Bernard      Rename dfs_lwip to dfs_net
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>

#include "dfs_net.h"

int dfs_net_getsocket(int fd)
{
    struct dfs_fd *_dfs_fd; 
    
    _dfs_fd = fd_get(fd);
    if (_dfs_fd == RT_NULL) return -1;

    if (_dfs_fd->type != FT_SOCKET) return -1;
    
    return (int)_dfs_fd->data;
}

int dfs_net_ioctl(struct dfs_fd* file, int cmd, void* args)
{
    return -DFS_STATUS_EIO;
}

int dfs_net_read(struct dfs_fd* file, void *buf, rt_size_t count)
{
    int sock;

    sock = (int)file->data;
    count = lwip_read(sock, buf, count);

    return count;
}

int dfs_net_write(struct dfs_fd *file, const void *buf, rt_size_t count)
{
    int sock;
    
    sock = (int)file->data;
    count = lwip_write(sock, buf, count);

    return count;
}

int dfs_net_close(struct dfs_fd* file)
{
    int sock;
    int result;
    
    sock = (int)file->data;
    result = lwip_close(sock);
    
    if (result == 0) return DFS_STATUS_OK;
    
    return -result;
}

static const struct dfs_filesystem_operation _net_fs_ops = 
{
    "net",
    DFS_FS_FLAG_DEFAULT,
    RT_NULL,    /* mount    */
    RT_NULL,    /* unmont   */
    RT_NULL,    /* mkfs     */
    RT_NULL,    /* statfs   */

    RT_NULL,    /* open     */
    dfs_net_close,
    dfs_net_ioctl,
    dfs_net_read,
    dfs_net_write,
    RT_NULL,
    RT_NULL,    /* lseek    */
    RT_NULL,    /* getdents */
    RT_NULL,    /* unlink   */
    RT_NULL,    /* stat     */
    RT_NULL,    /* rename   */
};

static struct dfs_filesystem _net_fs = 
{
    0,              /* dev_id */
    RT_NULL,        /* path */
    &_net_fs_ops,
    RT_NULL         /* data */
};

struct dfs_filesystem* dfs_net_get_fs(void)
{
    return &_net_fs;
}

/*
NOTE: Beause we don't need to mount lwIP file system, the filesystem_ops is not 
registered to the system. 

int dfs_net_system_init(void)
{
    dfs_register(&_net_fs_ops);
    
    return 0;
}
INIT_FS_EXPORT(dfs_net_system_init);
*/
