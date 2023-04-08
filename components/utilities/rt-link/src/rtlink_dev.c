/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-15     Sherman      the first version
 */

#define DBG_TAG    "RTLINK_DEV"
#define DBG_LVL    DBG_LOG
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rtlink_dev.h>

#define RTLINK_SERV(dev)  (((struct rt_link_device*)dev)->service)

#ifdef RT_USING_POSIX_DEVIO
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <poll.h>

int rtlink_fops_open(struct dfs_file *fd)
{
    rt_uint16_t flags = 0;
    rt_device_t device;

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        LOG_D("fops open: O_RDONLY!");
        flags = RT_DEVICE_FLAG_RDONLY;
        break;
    case O_WRONLY:
        LOG_D("fops open: O_WRONLY!");
        flags = RT_DEVICE_FLAG_WRONLY;
        break;
    case O_RDWR:
        LOG_D("fops open: O_RDWR!");
        flags = RT_DEVICE_FLAG_RDWR;
        break;
    default:
        LOG_E("fops open: unknown mode - %d!", fd->flags & O_ACCMODE);
        break;
    }

    device = (rt_device_t)fd->vnode->data;
    if (fd->flags & O_NONBLOCK)
    {
        rt_device_control(device, RT_LINK_TX_NONBLOCKING | RT_LINK_RX_NONBLOCKING, RT_NULL);
    }

    return rt_device_open(device, flags);
}

int rtlink_fops_close(struct dfs_file *fd)
{
    rt_device_t device;
    device = (rt_device_t)fd->vnode->data;

    rt_device_set_rx_indicate(device, RT_NULL);
    return rt_device_close(device);
}

int rtlink_fops_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    rt_device_t device;
    device = (rt_device_t)fd->vnode->data;

    if (cmd == O_NONBLOCK)
    {
        return rt_device_control(device, RT_LINK_TX_NONBLOCKING | RT_LINK_RX_NONBLOCKING, RT_NULL);
    }
    else
    {
        return rt_device_control(device, cmd, args);
    }
}

int rtlink_fops_read(struct dfs_file *fd, void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;
    device = (rt_device_t)fd->vnode->data;

    size = rt_device_read(device, -1,  buf, count);
    if (size <= 0)
    {
        size = -EAGAIN;
    }
    return size;
}

int rtlink_fops_write(struct dfs_file *fd, const void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;
    device = (rt_device_t)fd->vnode->data;

    size = rt_device_write(device, -1, buf, count);
    if (size <= 0)
    {
        size = -EAGAIN;
    }
    return size;
}

int rtlink_fops_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    int mask = 0;
    int flags = 0;
    rt_device_t device;
    struct rt_link_device *rtlink_dev;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    rtlink_dev = (struct rt_link_device *)device;

    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_base_t level;
        rt_poll_add(&(device->wait_queue), req);

        level = rt_hw_interrupt_disable();
        if (RT_NULL != rt_slist_first(&rtlink_dev->recv_head))
            mask |= POLLIN;
        rt_hw_interrupt_enable(level);
    }
    mask |= POLLOUT;

    return mask;
}

const static struct dfs_file_ops _rtlink_fops =
{
    rtlink_fops_open,
    rtlink_fops_close,
    rtlink_fops_ioctl,
    rtlink_fops_read,
    rtlink_fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    rtlink_fops_poll,
};
#endif /* RT_USING_POSIX_DEVIO */

/* The event type for the service channel number,
 * which is used to wake up the service thread in blocking receive mode */
struct rt_event recv_event;

static rt_err_t rt_link_event_send(struct rt_link_service *serv)
{
    RT_ASSERT(serv != RT_NULL);
    RT_ASSERT(serv->service < RT_LINK_SERVICE_MAX);
    rt_uint32_t set = 0x01 << serv->service;
    return rt_event_send(&recv_event, set);
}

static rt_err_t rt_link_event_recv(struct rt_link_service *service)
{
    RT_ASSERT(service != RT_NULL);
    RT_ASSERT(service->service < RT_LINK_SERVICE_MAX);

    rt_uint32_t set = 0x01 << service->service;
    rt_uint32_t recved = 0;
    rt_err_t ret = rt_event_recv(&recv_event,
                                 set,
                                 RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                                 RT_WAITING_FOREVER,
                                 &recved);
    if (recved & set)
    {
        return ret;
    }
    return -RT_ERROR;
}

static void send_cb(struct rt_link_service *service, void *buffer)
{
    RT_ASSERT(service != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    struct rt_link_device *rtlink = (struct rt_link_device *)service->user_data;

    if (rtlink && rtlink->parent.tx_complete)
    {
        rtlink->parent.tx_complete(&rtlink->parent, buffer);
    }
}

static void recv_cb(struct rt_link_service *service, void *data, rt_size_t size)
{
    RT_ASSERT(service != RT_NULL);
    struct rt_link_device *rtlink = (struct rt_link_device *)service->user_data;

    if (rtlink)
    {
        struct rtlink_recv_list *node = rt_malloc(sizeof(struct rtlink_recv_list));
        node->data = data;
        node->size = size;
        node->index = 0;
        rt_slist_append(&rtlink->recv_head, &node->list);
        rt_link_event_send(service);

        if (rtlink->parent.rx_indicate)
        {
            rtlink->parent.rx_indicate(&rtlink->parent, size);
        }
    }
    else
    {
        rt_free(data);
    }
}

rt_err_t  rt_link_dev_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

    struct rt_link_device *rtlink = (struct rt_link_device *)dev;
    rtlink->service.service = RT_LINK_SERVICE_MAX;
    rtlink->service.recv_cb = RT_NULL;
    rtlink->service.send_cb = RT_NULL;
    rtlink->service.timeout_tx = RT_WAITING_NO;
    rtlink->service.user_data = (void *)dev;

    rt_slist_init(&rtlink->recv_head);
    return RT_EOK;
}

rt_err_t  rt_link_dev_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    struct rt_link_device *rtlink = (struct rt_link_device *)dev;

    rtlink->service.recv_cb = recv_cb;
    rtlink->service.send_cb = send_cb;

    dev->open_flag = oflag & RT_DEVICE_OFLAG_MASK;
    if (dev->open_flag == RT_DEVICE_OFLAG_RDONLY)
    {
        rtlink->service.send_cb = RT_NULL;
    }
    else if (dev->open_flag == RT_DEVICE_OFLAG_WRONLY)
    {
        rtlink->service.recv_cb = RT_NULL;
    }
    return rt_link_service_attach(&rtlink->service);
}

rt_err_t  rt_link_dev_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    struct rt_link_device *rtlink = (struct rt_link_device *)dev;
    return rt_link_service_detach(&rtlink->service);
}

rt_ssize_t rt_link_dev_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    struct rt_link_device *rtlink = (struct rt_link_device *)dev;
    struct rtlink_recv_list *node;
    rt_size_t read_len = 0;
    rt_size_t unread_len = 0;

    if (dev->rx_indicate == RT_NULL)
    {
        /* RT_LINK_RX_BLOCKING, wait service receive data event */
        rt_link_event_recv(&rtlink->service);
    }

    if (rt_slist_first(&rtlink->recv_head) != RT_NULL)
    {
        node = rt_container_of(rt_slist_next(&rtlink->recv_head), struct rtlink_recv_list, list);
        unread_len = (node->size) - (node->index);
        read_len = (size > unread_len) ? unread_len : size;
        rt_memcpy(buffer, (rt_uint8_t *)node->data + node->index, read_len);
        node->index += read_len;

        if (node->index >= node->size)
        {
            rt_slist_remove(&rtlink->recv_head, &node->list);
            node->index = 0;
            rt_free(node->data);
            rt_free(node);
        }
        if (rt_slist_first(&rtlink->recv_head) != RT_NULL)
        {
            rt_link_event_send(&rtlink->service);
        }
    }
    return read_len;
}

rt_ssize_t rt_link_dev_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    return rt_link_send(&RTLINK_SERV(dev), buffer, size);
}

rt_err_t  rt_link_dev_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd & RT_DEVICE_CTRL_CONFIG)
    {
        if (args == RT_NULL)
            return -RT_EINVAL;
        RTLINK_SERV(dev).service = ((struct rt_link_service *)args)->service;
        RTLINK_SERV(dev).timeout_tx = ((struct rt_link_service *)args)->timeout_tx;
        RTLINK_SERV(dev).flag = ((struct rt_link_service *)args)->flag;
    }

    if (cmd & RT_LINK_RX_BLOCKING)
    {
        dev->rx_indicate = RT_NULL;
    }
    if (cmd & RT_LINK_TX_BLOCKING)
    {
        RTLINK_SERV(dev).timeout_tx = RT_WAITING_FOREVER;
        dev->tx_complete = RT_NULL;
    }
    if (cmd & RT_LINK_TX_NONBLOCKING)
    {
        RTLINK_SERV(dev).timeout_tx = RT_WAITING_NO;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtlink_ops =
{
    rt_link_dev_init,
    rt_link_dev_open,
    rt_link_dev_close,
    rt_link_dev_read,
    rt_link_dev_write,
    rt_link_dev_control
};
#endif /* RT_USING_DEVICE_OPS */

/*
 * rtlink device register
 */
rt_err_t rt_link_dev_register(struct rt_link_device *rtlink,
                              const char              *name,
                              rt_uint32_t              flag,
                              void                    *data)
{
    rt_err_t ret;
    struct rt_device *device;
    RT_ASSERT(rtlink != RT_NULL);

    device = (struct rt_device *)rtlink;
    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtlink_ops;
#else
    device->init        = rt_link_dev_init;
    device->open        = rt_link_dev_open;
    device->close       = rt_link_dev_close;
    device->read        = rt_link_dev_read;
    device->write       = rt_link_dev_write;
    device->control     = rt_link_dev_control;
#endif
    device->user_data   = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

#ifdef RT_USING_POSIX_DEVIO
    /* set fops */
    device->fops        = &_rtlink_fops;
#endif

    rt_event_init(&recv_event, "rtlink_dev", RT_IPC_FLAG_FIFO);
    return ret;
}
