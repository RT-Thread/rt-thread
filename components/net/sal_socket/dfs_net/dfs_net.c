/*
 * File      : dfs_net.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-03-09     Bernard      Fix the last data issue in poll.
 * 2018-05-24     ChenYong     Add socket abstraction layer
 */

#include <rtthread.h>

#include <dfs.h>
#include <dfs_net.h>

#include <sys/socket.h>

int dfs_net_getsocket(int fd)
{
    int socket;
    struct dfs_fd *_dfs_fd; 

    _dfs_fd = fd_get(fd);
    if (_dfs_fd == NULL) return -1;

    if (_dfs_fd->type != FT_SOCKET) socket = -1;
    else socket = (int)_dfs_fd->data;

    fd_put(_dfs_fd); /* put this dfs fd */
    return socket;
}

static int dfs_net_ioctl(struct dfs_fd* file, int cmd, void* args)
{
    return -EIO;
}

static int dfs_net_read(struct dfs_fd* file, void *buf, size_t count)
{
    int socket = (int) file->data;

    return sal_recvfrom(socket, buf, count, 0, NULL, NULL);
}

static int dfs_net_write(struct dfs_fd *file, const void *buf, size_t count)
{
    int socket = (int) file->data;

    return sal_sendto(socket, buf, count, 0, NULL, 0);
}

static int dfs_net_close(struct dfs_fd* file)
{
    int socket = (int) file->data;

    return sal_closesocket(socket);
}

static int dfs_net_poll(struct dfs_fd *file, struct rt_pollreq *req)
{
    extern int sal_poll(struct dfs_fd *file, struct rt_pollreq *req);

    return sal_poll(file, req);
}

const struct dfs_file_ops _net_fops = 
{
    NULL,    /* open     */
    dfs_net_close,
    dfs_net_ioctl,
    dfs_net_read,
    dfs_net_write,
    NULL,
    NULL,    /* lseek    */
    NULL,    /* getdents */
    dfs_net_poll,
};

const struct dfs_file_ops *dfs_net_get_fops(void)
{
    return &_net_fops;
}
