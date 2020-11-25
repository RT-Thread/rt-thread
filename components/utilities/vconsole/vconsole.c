/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-20     tyx          first implementation
 */

#include <rtdevice.h>
#include <string.h>
#include <dfs_posix.h>
#include <vconsole.h>

#define PRINT   rt_kprintf

#define VC_EVENT_RECV (0x1 << 0)
#define VC_EVENT_EXIT (0x1 << 1)

int libc_stdio_set_console(const char* device_name, int mode);
int libc_stdio_get_console(void);
static rt_size_t _read(rt_device_t dev, rt_off_t pos, void *buffer,
                       rt_size_t size);
static rt_size_t _write(rt_device_t dev, rt_off_t pos, const void *buffer,
                        rt_size_t size);

#ifdef RT_USING_POSIX
#include <dfs_posix.h>
#include <dfs_poll.h>

static rt_err_t fops_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_wqueue_wakeup(&(dev->wait_queue), (void*)POLLIN);
    return RT_EOK;
}

/* fops for vc */
static int _fops_open(struct dfs_fd *fd)
{
    rt_err_t ret = 0;
    rt_uint16_t flags = 0;
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        flags = RT_DEVICE_FLAG_RDONLY;
        break;
    case O_WRONLY:
        flags = RT_DEVICE_FLAG_WRONLY;
        break;
    case O_RDWR:
        flags = RT_DEVICE_FLAG_RDWR;
        break;
    default:
        break;
    }

    if ((fd->flags & O_ACCMODE) != O_WRONLY)
        rt_device_set_rx_indicate(device, fops_rx_ind);
    ret = rt_device_open(device, flags);
    if (ret == RT_EOK) return 0;

    return ret;
}

static int _fops_close(struct dfs_fd *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;

    rt_device_set_rx_indicate(device, RT_NULL);
    rt_device_close(device);

    return 0;
}

static int _fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    switch (cmd)
    {
    case FIONREAD:
        break;
    case FIONWRITE:
        break;
    }

    return rt_device_control(device, cmd, args);
}

static int _fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;

    device = (rt_device_t)fd->data;

    do
    {
        size = rt_device_read(device, -1,  buf, count);
        if (size <= 0)
        {
            if (fd->flags & O_NONBLOCK)
            {
                size = -EAGAIN;
                break;
            }

            rt_wqueue_wait(&(device->wait_queue), 0, RT_WAITING_FOREVER);
        }
    }while (size <= 0);

    return size;
}

static int _fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    return rt_device_write(device, -1, buf, count);
}

static int _fops_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    int mask = 0;
    int flags = 0;
    rt_device_t device;
    vconsole_t vc;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    vc = (vconsole_t)device;

    /* only support POLLIN */
    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_poll_add(&(device->wait_queue), req);
        if (rt_ringbuffer_data_len(&vc->ring_buff) > 0)
            mask |= POLLIN;
    }

    return mask;
}

const static struct dfs_file_ops _vc_fops =
{
    _fops_open,
    _fops_close,
    _fops_ioctl,
    _fops_read,
    _fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    _fops_poll,
};
#endif

static rt_size_t _read(rt_device_t dev, rt_off_t pos, void *buffer,
                       rt_size_t size)
{
    vconsole_t vc = (vconsole_t)dev;
    rt_size_t len;

#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_take(&vc->mutex);
#else
    rt_enter_critical();
#endif
    len = rt_ringbuffer_get(&vc->ring_buff, buffer, size);
#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_release(&vc->mutex);
#else
    rt_exit_critical();
#endif
    return len;
}

static rt_size_t _write(rt_device_t dev, rt_off_t pos, const void *buffer,
                        rt_size_t size)
{
    vconsole_t vc = (vconsole_t)dev;
    rt_size_t len, w_len;
    rt_uint8_t *bstr;
    const rt_uint8_t *str = buffer;
    int index = 0;
    int i;

    w_len = 0;
    bstr = vc->cache;
    for (i = 0; i < size && index < vc->cache_size; i++)
    {
        if(str[i] == '\n')
        {
            bstr[index++] = '\r';
        }
        bstr[index++] = str[i];
        if (index >= vc->cache_size - 1)
        {
            len = vc->output(dev, vc->cache, vc->cache_size);
            index = 0;
            w_len += len;
        }
    }
    if (index > 0)
    {
        len = vc->output(dev, vc->cache, index);
        w_len += len;
    }

    return w_len;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _vc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _read,
    _write,
    RT_NULL
};
#endif

rt_device_t vconsole_create(const char *name, vc_output_t out)
{
    vconsole_t vc;
    int ret;
    rt_device_t vc_dev;

    if (out == RT_NULL || out == RT_NULL)
    {
        return RT_NULL;
    }
    /* create virtual console device */
    vc = rt_calloc(1, sizeof(struct vconsole) +
                   VCONSOLE_CACHE_SIZE +
                   VCONSOLE_POOL_SIZE);
    if (vc == RT_NULL)
    {
        return RT_NULL;
    }

    vc->magic = VCONSOLE_MAGIC_NUM;
    vc->output = out;
    vc->cache_size = VCONSOLE_CACHE_SIZE;
    vc->ring_size = VCONSOLE_POOL_SIZE;
    rt_ringbuffer_init(&vc->ring_buff, vc->ring_pool, vc->ring_size);
#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_init(&vc->mutex, name, RT_IPC_FLAG_FIFO);
#endif

    /* init virtual console device */
    vc_dev = &vc->parent;
    vc_dev->type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    vc_dev->ops = &_vc_ops;
#else
    vc_dev->init = RT_NULL;
    vc_dev->open = RT_NULL;
    vc_dev->close = RT_NULL;
    vc_dev->read = _read;
    vc_dev->write = _write;
    vc_dev->control = RT_NULL;
#endif
    vc_dev->user_data = RT_NULL;

    /* register virtual console device */
    ret = rt_device_register(vc_dev, name,
                             RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    if (ret != RT_EOK)
    {
#ifdef VCONSOLE_USING_MUTEX
        rt_mutex_detach(&vc->mutex);
#endif
        rt_free(vc);
        return RT_NULL;
    }
#ifdef RT_USING_POSIX
    /* set fops */
    vc_dev->fops        = &_vc_fops;
#endif
    return vc_dev;
}

rt_device_t vconsole_switch(rt_device_t device)
{
    rt_device_t old_dev;

    if (device == RT_NULL)
        return RT_NULL;

    old_dev = rt_console_get_device();
    rt_console_set_device(device->parent.name);
#ifdef RT_USING_POSIX
    {
        int fd, flags;

        fd = libc_stdio_get_console();
        flags = ioctl(fd, F_GETFL, 0);
        ioctl(fd, F_SETFL, (void *)(flags | O_NONBLOCK));
        libc_stdio_set_console(device->parent.name, O_RDWR);
        rt_wqueue_wakeup(&(old_dev->wait_queue), (void*)POLLERR);
        rt_thread_mdelay(20);
    }
#else
    finsh_set_device(device->parent.name);
#endif
    return old_dev;
}

rt_err_t vconsole_delete(rt_device_t device)
{
    vconsole_t vc = (vconsole_t)device;

    if (vc == RT_NULL)
    {
        return -RT_EINVAL;
    }
    if (device == rt_console_get_device())
    {
        return -RT_EBUSY;
    }
    if (vc->magic != VCONSOLE_MAGIC_NUM)
    {
        return -RT_ERROR;
    }
    rt_device_unregister(device);
#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_detach(&vc->mutex);
#endif
    rt_free(vc);

    return RT_EOK;
}

rt_size_t vconsole_input(rt_device_t device, const rt_uint8_t *buff, rt_size_t size)
{
    rt_size_t len;
    vconsole_t vc = (vconsole_t)device;

    RT_ASSERT(vc != RT_NULL);
    RT_ASSERT(vc->magic == VCONSOLE_MAGIC_NUM);

#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_take(&vc->mutex);
#else
    rt_enter_critical();
#endif
    len = rt_ringbuffer_put(&vc->ring_buff, buff, size);
#ifdef VCONSOLE_USING_MUTEX
    rt_mutex_release(&vc->mutex);
#else
    rt_exit_critical();
#endif
    if (len > 0 && device->rx_indicate)
    {
        device->rx_indicate(device, len);
    }
    return len;
}
