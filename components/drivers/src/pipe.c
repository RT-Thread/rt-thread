/*
 * File      : pipe.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012-2017, RT-Thread Development Team
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
 * 2012-09-30     Bernard      first version.
 * 2017-11-08     JasonJiaJie  fix memory leak issue when close a pipe.
 */
#include <rthw.h>
#include <rtdevice.h>
#include <stdint.h>

#if defined(RT_USING_POSIX)
#include <dfs_file.h>
#include <dfs_posix.h>
#include <dfs_poll.h>

static int pipe_fops_open(struct dfs_fd *fd)
{
    rt_device_t device;
    rt_pipe_t *pipe;

    pipe = (rt_pipe_t *)fd->data;
    if (!pipe) return -1;

    device = &(pipe->parent);
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    if (device->ref_count == 0)
    {
        pipe->fifo = rt_ringbuffer_create(pipe->bufsz);
    }

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        pipe->readers ++;
        break;
    case O_WRONLY:
        pipe->writers ++;
        break;
    case O_RDWR:
        pipe->readers ++;
        pipe->writers ++;
        break;
    }
    device->ref_count ++;

    rt_mutex_release(&(pipe->lock));

    return 0;
}

static int pipe_fops_close(struct dfs_fd *fd)
{
    rt_device_t device;
    rt_pipe_t *pipe;

    pipe = (rt_pipe_t *)fd->data;
    if (!pipe) return -1;

    device = &(pipe->parent);
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        pipe->readers --;
        break;
    case O_WRONLY:
        pipe->writers --;
        break;
    case O_RDWR:
        pipe->readers --;
        pipe->writers --;
        break;
    }

    if (pipe->writers == 0)
    {
        rt_wqueue_wakeup(&(pipe->reader_queue), (void*)(POLLIN | POLLERR | POLLHUP));
    }

    if (pipe->readers == 0)
    {
        rt_wqueue_wakeup(&(pipe->writer_queue), (void*)(POLLOUT | POLLERR | POLLHUP));
    }

    if (device->ref_count == 1)
    {
        rt_ringbuffer_destroy(pipe->fifo);
        pipe->fifo = RT_NULL;
    }
    device->ref_count --;

    rt_mutex_release(&(pipe->lock));

    return 0;
}

static int pipe_fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_pipe_t *pipe;
    int ret = 0;

    pipe = (rt_pipe_t *)fd->data;

    switch (cmd)
    {
    case FIONREAD:
        *((int*)args) = rt_ringbuffer_data_len(pipe->fifo);
        break;
    case FIONWRITE:
        *((int*)args) = rt_ringbuffer_space_len(pipe->fifo);
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static int pipe_fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    int len = 0;
    rt_pipe_t *pipe;

    pipe = (rt_pipe_t *)fd->data;

    /* no process has the pipe open for writing, return end-of-file */
    if (pipe->writers == 0)
        return 0;

    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    while (1)
    {
        if (pipe->writers == 0)
        {
            goto out;
        }

        len = rt_ringbuffer_get(pipe->fifo, buf, count);

        if (len > 0)
        {
            break;
        }
        else
        {
            if (fd->flags & O_NONBLOCK)
            {
                len = -EAGAIN;
                goto out;
            }

            rt_mutex_release(&pipe->lock);
            rt_wqueue_wakeup(&(pipe->writer_queue), (void*)POLLOUT);
            rt_wqueue_wait(&(pipe->reader_queue), 0, -1);
            rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);
        }
    }

    /* wakeup writer */
    rt_wqueue_wakeup(&(pipe->writer_queue), (void*)POLLOUT);

out:
    rt_mutex_release(&pipe->lock);
    return len;
}

static int pipe_fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    int len;
    rt_pipe_t *pipe;
    int wakeup = 0;
    int ret = 0;
    uint8_t *pbuf;

    pipe = (rt_pipe_t *)fd->data;

    if (pipe->readers == 0)
    {
        ret = -EPIPE;
        goto out;
    }

    if (count == 0)
        return 0;

    pbuf = (uint8_t*)buf;
    rt_mutex_take(&pipe->lock, -1);

    while (1)
    {
        if (pipe->readers == 0)
        {
            if (ret == 0)
                ret = -EPIPE;
            break;
        }

        len = rt_ringbuffer_put(pipe->fifo, pbuf, count - ret);
        ret +=  len;
        pbuf += len;
        wakeup = 1;

        if (ret == count)
        {
            break;
        }
        else
        {
            if (fd->flags & O_NONBLOCK)
            {
                if (ret == 0)
                {
                    ret = -EAGAIN;
                }

                break;
            }
        }

        rt_mutex_release(&pipe->lock);
        rt_wqueue_wakeup(&(pipe->reader_queue), (void*)POLLIN);
        /* pipe full, waiting on suspended write list */
        rt_wqueue_wait(&(pipe->writer_queue), 0, -1);
        rt_mutex_take(&pipe->lock, -1);
    }
    rt_mutex_release(&pipe->lock);

    if (wakeup)
    {
        rt_wqueue_wakeup(&(pipe->reader_queue), (void*)POLLIN);
    }

out:
    return ret;
}

static int pipe_fops_poll(struct dfs_fd *fd, rt_pollreq_t *req)
{
    int mask = 0;
    rt_pipe_t *pipe;
    int mode = 0;
    pipe = (rt_pipe_t *)fd->data;

    rt_poll_add(&(pipe->reader_queue), req);
    rt_poll_add(&(pipe->writer_queue), req);

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        mode = 1;
        break;
    case O_WRONLY:
        mode = 2;
        break;
    case O_RDWR:
        mode = 3;
        break;
    }

    if (mode & 1)
    {
        if (rt_ringbuffer_data_len(pipe->fifo) != 0)
        {
            mask |= POLLIN;
        }
        if (pipe->writers == 0)
        {
            mask |= POLLHUP;
        }
    }

    if (mode & 2)
    {
        if (rt_ringbuffer_space_len(pipe->fifo) != 0)
        {
            mask |= POLLOUT;
        }
        if (pipe->readers == 0)
        {
            mask |= POLLERR;
        }
    }

    return mask;
}

static const struct dfs_file_ops pipe_fops =
{
    pipe_fops_open,
    pipe_fops_close,
    pipe_fops_ioctl,
    pipe_fops_read,
    pipe_fops_write,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    pipe_fops_poll,
};
#endif /* end of RT_USING_POSIX */

rt_err_t  rt_pipe_open (rt_device_t device, rt_uint16_t oflag)
{
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL) return -RT_EINVAL;
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    if (pipe->fifo == RT_NULL)
    {
        pipe->fifo = rt_ringbuffer_create(pipe->bufsz);
    }

    rt_mutex_release(&(pipe->lock));

    return RT_EOK;
}

rt_err_t  rt_pipe_close  (rt_device_t device)
{
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL) return -RT_EINVAL;
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    if (device->ref_count == 1)
    {
        rt_ringbuffer_destroy(pipe->fifo);
        pipe->fifo = RT_NULL;
    }

    rt_mutex_release(&(pipe->lock));

    return RT_EOK;
}

rt_size_t rt_pipe_read   (rt_device_t device, rt_off_t pos, void *buffer, rt_size_t count)
{
    uint8_t *pbuf;
    rt_size_t read_bytes = 0;
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL)
    {
        rt_set_errno(-EINVAL);
        return 0;
    }
    if (count == 0) return 0;

    pbuf = (uint8_t*)buffer;
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    while (read_bytes < count)
    {
        int len = rt_ringbuffer_get(pipe->fifo, &pbuf[read_bytes], count - read_bytes);
        if (len <= 0) break;

        read_bytes += len;
    }
    rt_mutex_release(&pipe->lock);

    return read_bytes;
}

rt_size_t rt_pipe_write  (rt_device_t device, rt_off_t pos, const void *buffer, rt_size_t count)
{
    uint8_t *pbuf;
    rt_size_t write_bytes = 0;
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL)
    {
        rt_set_errno(-EINVAL);
        return 0;
    }
    if (count == 0) return 0;

    pbuf = (uint8_t*)buffer;
    rt_mutex_take(&pipe->lock, -1);

    while (write_bytes < count)
    {
        int len = rt_ringbuffer_put(pipe->fifo, &pbuf[write_bytes], count - write_bytes);
        if (len <= 0) break;

        write_bytes += len;
    }
    rt_mutex_release(&pipe->lock);

    return write_bytes;
}

rt_err_t  rt_pipe_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pipe_ops = 
{
    RT_NULL,
    rt_pipe_open,
    rt_pipe_close,
    rt_pipe_read,
    rt_pipe_write,
    rt_pipe_control,
};
#endif

rt_pipe_t *rt_pipe_create(const char *name, int bufsz)
{
    rt_pipe_t *pipe;
    rt_device_t dev;

    pipe = rt_malloc(sizeof(rt_pipe_t));
    if (pipe == RT_NULL) return RT_NULL;

    rt_memset(pipe, 0, sizeof(rt_pipe_t));
    rt_mutex_init(&(pipe->lock), name, RT_IPC_FLAG_FIFO);
    rt_list_init(&(pipe->reader_queue));
    rt_list_init(&(pipe->writer_queue));

    RT_ASSERT(bufsz < 0xFFFF);
    pipe->bufsz = bufsz;

    dev = &(pipe->parent);
    dev->type = RT_Device_Class_Pipe;
#ifdef RT_USING_DEVICE_OPS
    dev->ops         = &pipe_ops;
#else
    dev->init        = RT_NULL;
    dev->open        = rt_pipe_open;
    dev->read        = rt_pipe_read;
    dev->write       = rt_pipe_write;
    dev->close       = rt_pipe_close;
    dev->control     = rt_pipe_control;
#endif

    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

    if (rt_device_register(&(pipe->parent), name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE) != 0)
    {
        rt_free(pipe);
        return RT_NULL;
    }
#ifdef RT_USING_POSIX
    dev->fops = (void*)&pipe_fops;
#endif

    return pipe;
}

int rt_pipe_delete(const char *name)
{
    int result = 0;
    rt_device_t device;

    device = rt_device_find(name);
    if (device)
    {
        if (device->type == RT_Device_Class_Pipe)
        {
            rt_pipe_t *pipe;

            if (device->ref_count != 0)
            {
                return -RT_EBUSY;
            }

            pipe = (rt_pipe_t *)device;

            rt_mutex_detach(&(pipe->lock));
            rt_device_unregister(device);

            /* close fifo ringbuffer */
            if (pipe->fifo) 
            {
                rt_ringbuffer_destroy(pipe->fifo);
                pipe->fifo = RT_NULL;
            }
            rt_free(pipe);
        }
        else
        {
            result = -ENODEV;
        }
    }
    else
    {
        result = -ENODEV;
    }

    return result;
}

#ifdef RT_USING_POSIX
int pipe(int fildes[2])
{
    rt_pipe_t *pipe;
    char dname[8];
    char dev_name[32];
    static int pipeno = 0;

    rt_snprintf(dname, sizeof(dname), "pipe%d", pipeno++);

    pipe = rt_pipe_create(dname, PIPE_BUFSZ);
    if (pipe == RT_NULL)
    {
        return -1;
    }

    rt_snprintf(dev_name, sizeof(dev_name), "/dev/%s", dname);
    fildes[0] = open(dev_name, O_RDONLY, 0);
    if (fildes[0] < 0)
    {
        return -1;
    }

    fildes[1] = open(dev_name, O_WRONLY, 0);
    if (fildes[1] < 0)
    {
        close(fildes[1]);
        return -1;
    }

    return 0;
}

int mkfifo(const char *path, mode_t mode)
{
    rt_pipe_t *pipe;
    
    pipe = rt_pipe_create(path, PIPE_BUFSZ);
    if (pipe == RT_NULL)
    {
        return -1;
    }

    return 0;
}
#endif
