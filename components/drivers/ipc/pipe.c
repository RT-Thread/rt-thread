/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 * 2017-11-08     JasonJiaJie  fix memory leak issue when close a pipe.
 */
#include <rthw.h>
#include <rtdevice.h>
#include <stdint.h>
#include <sys/errno.h>

#if defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_POSIX_PIPE)
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <dfs_file.h>

/**
 * @brief    This function will open a pipe.
 *
 * @param    fd is the file descriptor.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -1, it means the file descriptor is invalid.
 *           When the return value is -RT_ENOMEM, it means insufficient memory allocation failed.
 */
static int pipe_fops_open(struct dfs_fd *fd)
{
    int rc = 0;
    rt_device_t device;
    rt_pipe_t *pipe;

    pipe = (rt_pipe_t *)fd->data;
    if (!pipe) return -1;

    device = &(pipe->parent);
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    if (device->ref_count == 0)
    {
        pipe->fifo = rt_ringbuffer_create(pipe->bufsz);
        if (pipe->fifo == RT_NULL)
        {
            rc = -RT_ENOMEM;
            goto __exit;
        }
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

__exit:
    rt_mutex_release(&(pipe->lock));

    return rc;
}

/**
 * @brief    This function will close a pipe.
 *
 * @param    fd is the file descriptor.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -1, it means the file descriptor is invalid.
 */
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
        rt_wqueue_wakeup(&(pipe->reader_queue), (void *)(POLLIN | POLLERR | POLLHUP));
    }

    if (pipe->readers == 0)
    {
        rt_wqueue_wakeup(&(pipe->writer_queue), (void *)(POLLOUT | POLLERR | POLLHUP));
    }

    if (device->ref_count == 1)
    {
        if (pipe->fifo != RT_NULL)
            rt_ringbuffer_destroy(pipe->fifo);
        pipe->fifo = RT_NULL;
    }
    device->ref_count --;

    rt_mutex_release(&(pipe->lock));

    if (device->ref_count == 0 && pipe->is_named == RT_FALSE)
    {
        /* delete the unamed pipe */
        rt_pipe_delete(device->parent.name);
    }

    return 0;
}

/**
 * @brief    This function will get the pipe space size depends on the command.
 *
 * @param    fd is the file descriptor.
 *
 * @param    cmd is the command. It determines what data will get.
 *
 *               FIONREAD        The command to get the number of bytes in the pipe.
 *
 *               FIONWRITE       The command to get the number of bytes can be written to the pipe.
 *
 * @param    args is the pointer to the data to store the read data.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -EINVAL, it means the command is invalid.
 */
static int pipe_fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_pipe_t *pipe;
    int ret = 0;

    pipe = (rt_pipe_t *)fd->data;

    switch (cmd)
    {
    case FIONREAD:
        *((int *)args) = rt_ringbuffer_data_len(pipe->fifo);
        break;
    case FIONWRITE:
        *((int *)args) = rt_ringbuffer_space_len(pipe->fifo);
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

/**
 * @brief    This function will read data from pipe.
 *
 * @param    fd is the file descriptor.
 *
 * @param    buf is the buffer to store the read data.
 *
 * @param    count is the length of data to be read.
 *
 * @return   Return the length of data read.
 *           When the return value is 0, it means O_NONBLOCK is enabled and there is no thread that has the pipe open for writing.
 *           When the return value is -EAGAIN, it means there are no data to be read.
 */
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
            rt_wqueue_wakeup(&(pipe->writer_queue), (void *)POLLOUT);
            rt_wqueue_wait(&(pipe->reader_queue), 0, -1);
            rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);
        }
    }

    /* wakeup writer */
    rt_wqueue_wakeup(&(pipe->writer_queue), (void *)POLLOUT);

out:
    rt_mutex_release(&pipe->lock);
    return len;
}

/**
 * @brief    This function will write data to pipe.
 *
 * @param    fd is the file descriptor.
 *
 * @param    buf is a pointer to the data buffer to be written.
 *
 * @param    count is the length of data to be write.
 *
 * @return   Return the length of data written.
 *           When the return value is -EAGAIN, it means O_NONBLOCK is enabled and there are no space to be written.
 *           When the return value is -EPIPE, it means there is no thread that has the pipe open for reading.
 */
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

    pbuf = (uint8_t *)buf;
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
        rt_wqueue_wakeup(&(pipe->reader_queue), (void *)POLLIN);
        /* pipe full, waiting on suspended write list */
        rt_wqueue_wait(&(pipe->writer_queue), 0, -1);
        rt_mutex_take(&pipe->lock, -1);
    }
    rt_mutex_release(&pipe->lock);

    if (wakeup)
    {
        rt_wqueue_wakeup(&(pipe->reader_queue), (void *)POLLIN);
    }

out:
    return ret;
}

/**
 * @brief    This function will get the pipe status.
 *
 * @param    fd is the file descriptor.
 *
 * @param    req is the request type.
 *
 * @return   mask of the pipe status.
 *           POLLIN means there is data to be read.
 *           POLLHUP means there is no thread that occupied the pipe to open for writing.
 *           POLLOUT means there is space to be written.
 *           POLLERR means there is no thread that occupied the pipe to open for reading.
 */
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
#endif /* defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_POSIX_PIPE) */

/**
 * @brief    This function will open the pipe and actually creates the pipe buffer.
 *
 * @param    device is a pointer to the pipe device descriptor.
 *
 * @param    oflag is the open method, but it is not used yet.
 *
 * @return   Return the operation status.
 *           When the return value is RT_EOK, the operation is successful.
 *           When the return value is -RT_EINVAL, it means the device handle is empty.
 *           When the return value is -RT_ENOMEM, it means insufficient memory allocation failed.
 */
static rt_err_t rt_pipe_open(rt_device_t device, rt_uint16_t oflag)
{
    rt_pipe_t *pipe = (rt_pipe_t *)device;
    rt_err_t ret = RT_EOK;

    if (device == RT_NULL)
    {
        ret = -RT_EINVAL;
        goto __exit;
    }

    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    if (pipe->fifo == RT_NULL)
    {
        pipe->fifo = rt_ringbuffer_create(pipe->bufsz);
        if (pipe->fifo == RT_NULL)
        {
            ret = -RT_ENOMEM;
        }
    }

    rt_mutex_release(&(pipe->lock));

__exit:
    return ret;
}

/**
 * @brief    This function will close the pipe and release the pipe buffer.
 *
 * @param    device is a pointer to the pipe device descriptor.
 *
 * @return   Return the operation status.
 *           When the return value is RT_EOK, the operation is successful.
 *           When the return value is -RT_EINVAL, it means the device handle is empty.
 */
static rt_err_t rt_pipe_close(rt_device_t device)
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

/**
 * @brief    This function will read the specified length of data from the pipe.
 *
 * @param    device is a pointer to the pipe device descriptor.
 *
 * @param    pos is a parameter compatible with POSIX standard interface (currently meaningless, just pass in 0).
 *
 * @param    buffer is a pointer to the buffer to store the read data.
 *
 * @param    count is the length of data to be read.
 *
 * @return   Return the length of data read.
 *           When the return value is 0, it means the pipe device handle is empty or the count is 0.
 */
static rt_size_t rt_pipe_read(rt_device_t device, rt_off_t pos, void *buffer, rt_size_t count)
{
    uint8_t *pbuf;
    rt_size_t read_bytes = 0;
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return 0;
    }
    if (count == 0) return 0;

    pbuf = (uint8_t *)buffer;
    rt_mutex_take(&(pipe->lock), RT_WAITING_FOREVER);

    while (read_bytes < count)
    {
        int len = rt_ringbuffer_get(pipe->fifo, &pbuf[read_bytes], (rt_uint16_t)(count - read_bytes));
        if (len <= 0) break;

        read_bytes += len;
    }
    rt_mutex_release(&pipe->lock);

    return read_bytes;
}

/**
 * @brief    This function will write the specified length of data to the pipe.
 *
 * @param    device is a pointer to the pipe device descriptor.
 *
 * @param    pos is a parameter compatible with POSIX standard interface (currently meaningless, just pass in 0).
 *
 * @param    buffer is a pointer to the data buffer to be written.
 *
 * @param    count is the length of data to be written.
 *
 * @return   Return the length of data written.
 *           When the return value is 0, it means the pipe device handle is empty or the count is 0.
 */
static rt_size_t rt_pipe_write(rt_device_t device, rt_off_t pos, const void *buffer, rt_size_t count)
{
    uint8_t *pbuf;
    rt_size_t write_bytes = 0;
    rt_pipe_t *pipe = (rt_pipe_t *)device;

    if (device == RT_NULL)
    {
        rt_set_errno(EINVAL);
        return 0;
    }
    if (count == 0) return 0;

    pbuf = (uint8_t *)buffer;
    rt_mutex_take(&pipe->lock, -1);

    while (write_bytes < count)
    {
        int len = rt_ringbuffer_put(pipe->fifo, &pbuf[write_bytes], (rt_uint16_t)(count - write_bytes));
        if (len <= 0) break;

        write_bytes += len;
    }
    rt_mutex_release(&pipe->lock);

    return write_bytes;
}

/**
 * @brief    This function is not used yet.
 *
 * @param    dev is not used yet.
 *
 * @param    cmd is not used yet.
 *
 * @param    args is not used yet.
 *
 * @return   Always return RT_EOK.
 */
static rt_err_t rt_pipe_control(rt_device_t dev, int cmd, void *args)
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
#endif /* RT_USING_DEVICE_OPS */

/**
 * @brief    This function will initialize a pipe device.
 *           The system allocates a pipe handle from dynamic heap memory, initializes the pipe handle
 *           with the specified value, and registers the pipe device with the system.
 *
 * @param    name is the name of pipe device.
 *
 * @param    bufsz is the size of pipe buffer.
 *
 * @return   Return the pointer to the pipe device.
 *           When the return value is RT_NULL, it means the initialization failed.
 */
rt_pipe_t *rt_pipe_create(const char *name, int bufsz)
{
    rt_pipe_t *pipe;
    rt_device_t dev;

    pipe = (rt_pipe_t *)rt_malloc(sizeof(rt_pipe_t));
    if (pipe == RT_NULL) return RT_NULL;

    rt_memset(pipe, 0, sizeof(rt_pipe_t));
    pipe->is_named = RT_TRUE; /* initialize as a named pipe */
    rt_mutex_init(&(pipe->lock), name, RT_IPC_FLAG_PRIO);
    rt_wqueue_init(&(pipe->reader_queue));
    rt_wqueue_init(&(pipe->writer_queue));

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
#if defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_POSIX_PIPE)
    dev->fops = (void *)&pipe_fops;
#endif

    return pipe;
}

/**
 * @brief    This function will delete a pipe device.
 *           The system will release the pipe handle and unregister the pipe device from the system.
 *
 * @param    pipe is the pointer to the pipe device.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -RT_EINVAL, it means the pipe device is not found or the device isn't a pipe.
 *           When the return value is -RT_EBUSY, it means the pipe device is busy.
 */
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
            result = -RT_EINVAL;
        }
    }
    else
    {
        result = -RT_EINVAL;
    }

    return result;
}

#if defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_POSIX_PIPE)
/**
 * @brief    This function will creat a anonymous pipe.
 *
 * @param    fildes[0] is the read handle.
 *           fildes[1] is the write handle.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -1, it means the operation is failed.
 */
int pipe(int fildes[2])
{
    rt_pipe_t *pipe;
    char dname[RT_NAME_MAX];
    char dev_name[RT_NAME_MAX * 4];
    static int pipeno = 0;

    rt_snprintf(dname, sizeof(dname), "pipe%d", pipeno++);

    pipe = rt_pipe_create(dname, RT_USING_POSIX_PIPE_SIZE);
    if (pipe == RT_NULL)
    {
        return -1;
    }

    pipe->is_named = RT_FALSE; /* unamed pipe */
    rt_snprintf(dev_name, sizeof(dev_name), "/dev/%s", dname);
    fildes[0] = open(dev_name, O_RDONLY, 0);
    if (fildes[0] < 0)
    {
        return -1;
    }

    fildes[1] = open(dev_name, O_WRONLY, 0);
    if (fildes[1] < 0)
    {
        close(fildes[0]);
        return -1;
    }

    return 0;
}

/**
 * @brief    This function will create a named pipe.
 *
 * @param    path is the name of pipe device.
 *
 * @param    mode is not used yet.
 *
 * @return   Return the operation status.
 *           When the return value is 0, it means the operation is successful.
 *           When the return value is -1, it means the operation is failed.
 */
int mkfifo(const char *path, mode_t mode)
{
    rt_pipe_t *pipe;

    pipe = rt_pipe_create(path, RT_USING_POSIX_PIPE_SIZE);
    if (pipe == RT_NULL)
    {
        return -1;
    }

    return 0;
}
#endif /* defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_POSIX_PIPE) */
