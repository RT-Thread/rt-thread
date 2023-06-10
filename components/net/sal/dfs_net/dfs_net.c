/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
    struct dfs_file *file;

    file = fd_get(fd);
    if (file == NULL) return -1;

    if (file->vnode->type != FT_SOCKET) socket = -1;
    else socket = (int)(size_t)file->vnode->data;

    return socket;
}

static int dfs_net_ioctl(struct dfs_file* file, int cmd, void* args)
{
    int ret;
    int socket = (int)(size_t)file->vnode->data;

    ret = sal_ioctlsocket(socket, cmd, args);
    if (ret < 0)
    {
        ret = rt_get_errno();
        return (ret > 0) ? (-ret) : ret;
    }
    return ret;
}

#ifdef RT_USING_DFS_V2
static int dfs_net_read(struct dfs_file* file, void *buf, size_t count, off_t *pos)
#else
static int dfs_net_read(struct dfs_file* file, void *buf, size_t count)
#endif
{
    int ret;
    int socket = (int)(size_t)file->vnode->data;

    ret = sal_recvfrom(socket, buf, count, 0, NULL, NULL);
    if (ret < 0)
    {
        ret = rt_get_errno();
        return (ret > 0) ? (-ret) : ret;
    }

    return ret;
}

#ifdef RT_USING_DFS_V2
static int dfs_net_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
#else
static int dfs_net_write(struct dfs_file *file, const void *buf, size_t count)
#endif
{
    int ret;
    int socket = (int)(size_t)file->vnode->data;

    ret = sal_sendto(socket, buf, count, 0, NULL, 0);
    if (ret < 0)
    {
        ret = rt_get_errno();
        return (ret > 0) ? (-ret) : ret;
    }

    return ret;
}

static int dfs_net_close(struct dfs_file* file)
{
    int socket;
    int ret = 0;

    if (file->vnode->ref_count == 1)
    {
        socket = (int)(size_t)file->vnode->data;
        ret = sal_closesocket(socket);
    }
    return ret;
}

static int dfs_net_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    extern int sal_poll(struct dfs_file *file, struct rt_pollreq *req);

    return sal_poll(file, req);
}

const struct dfs_file_ops _net_fops =
{
    .close = dfs_net_close,
    .ioctl = dfs_net_ioctl,
    .read  = dfs_net_read,
    .write = dfs_net_write,
    .poll  = dfs_net_poll,
};

const struct dfs_file_ops *dfs_net_get_fops(void)
{
    return &_net_fops;
}
