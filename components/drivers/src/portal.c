/*
 * File      : portal.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
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
 * 2013-08-19     Grissiom     initial version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define PT_WRITE_DEV(pt)  (((struct rt_portal_device*)pt)->write_dev)
#define PT_READ_DEV(pt)   (((struct rt_portal_device*)pt)->read_dev)

static rt_err_t _portal_init(rt_device_t dev)
{
    rt_err_t err;
    struct rt_portal_device *portal;

    RT_ASSERT(dev);

    portal = (struct rt_portal_device*)dev;

    err = rt_device_init(portal->write_dev);
    if (err != RT_EOK)
        return err;

    err = rt_device_init(portal->read_dev);

    return err;
}

static rt_err_t _portal_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t err;
    struct rt_portal_device *portal;

    RT_ASSERT(dev);

    if (!oflag)
        return -RT_ERROR;

    portal = (struct rt_portal_device*)dev;

    if (oflag & RT_DEVICE_OFLAG_RDONLY)
    {
        err = rt_device_open(portal->read_dev, RT_DEVICE_OFLAG_RDONLY);
        if (err != RT_EOK)
            return err;
    }

    if (oflag & RT_DEVICE_OFLAG_WRONLY)
    {
        err = rt_device_open(portal->write_dev, RT_DEVICE_OFLAG_WRONLY);
        if (err != RT_EOK)
            return err;
    }

    return RT_EOK;
}

static rt_err_t _portal_close(rt_device_t dev)
{
    struct rt_portal_device *portal;

    RT_ASSERT(dev);

    portal = (struct rt_portal_device*)dev;

    rt_device_close(portal->write_dev);
    rt_device_close(portal->read_dev);

    return RT_EOK;
}

static rt_size_t _portal_read(rt_device_t dev,
                              rt_off_t pos,
                              void *buffer,
                              rt_size_t size)
{
    return rt_device_read(PT_READ_DEV(dev),
                          pos, buffer, size);
}

static rt_size_t _portal_write(rt_device_t dev,
                               rt_off_t pos,
                               const void *buffer,
                               rt_size_t size)
{
    return rt_device_write(PT_WRITE_DEV(dev),
                           pos, buffer, size);
}

static rt_err_t _portal_rx_indicate(rt_device_t dev, rt_size_t size)
{
    struct rt_pipe_device *pipe;

    RT_ASSERT(dev && dev->type == RT_Device_Class_Pipe);

    pipe = (struct rt_pipe_device*)dev;

    if (pipe->read_portal->parent.rx_indicate)
        return pipe->read_portal->parent.rx_indicate(
                (rt_device_t)pipe->read_portal, size);

    return -RT_ENOSYS;
}

static rt_err_t _portal_tx_complete(rt_device_t dev, void *buf)
{
    struct rt_pipe_device *pipe;

    RT_ASSERT(dev && dev->type == RT_Device_Class_Pipe);

    pipe = (struct rt_pipe_device*)dev;

    if (pipe->write_portal->parent.tx_complete)
        return pipe->write_portal->parent.tx_complete(
                (rt_device_t)pipe->write_portal, buf);

    return -RT_ENOSYS;
}

/**
 * This function will initialize a portal device and put it under control of
 * resource management.
 *
 * Portal is a device that connect devices
 *
 * Currently, you can only connect pipes in portal. Pipes are unidirectional.
 * But with portal, you can construct a bidirectional device with two pipes.
 * The inner connection is just like this:
 *
 *   portal0        portal1
 * read   ||        || write
 * <--<---||<---<---||<---<-- (pipe0)
 *        ||        ||
 * -->--->||--->--->||--->--> (pipe1)
 * write  ||        || read
 *
 * You will always construct two portals on two pipes, say, "portal0" and
 * "portal1". Data written into "portal0" can be retrieved in "portal1" and
 * vice versa. `rx_indicate` and `tx_complete` events are propagated
 * accordingly.
 *
 * @param portal the portal device
 * @param portal_name the name of the portal device
 * @param write_dev the name of the pipe device that this portal write into
 * @param read_dev the name of the pipe device that this portal read from
 *
 * @return the operation status, RT_EOK on successful. -RT_ENOSYS on one pipe
 * device could not be found.
 */
rt_err_t rt_portal_init(struct rt_portal_device *portal,
                        const char *portal_name,
                        const char *write_dev,
                        const char *read_dev)
{
    rt_device_t dev;

    RT_ASSERT(portal);

    portal->parent.type        = RT_Device_Class_Portal;
    portal->parent.init        = _portal_init;
    portal->parent.open        = _portal_open;
    portal->parent.close       = _portal_close;
    portal->parent.write       = _portal_write;
    portal->parent.read        = _portal_read;
    /* single control of the two devices makes no sense */
    portal->parent.control     = RT_NULL;

    dev = rt_device_find(write_dev);
    if (dev == RT_NULL)
        return -RT_ENOSYS;
    RT_ASSERT(dev->type == RT_Device_Class_Pipe);
    portal->write_dev = dev;
    rt_device_set_tx_complete(&portal->parent, dev->tx_complete);
    rt_device_set_tx_complete(dev, _portal_tx_complete);
    ((struct rt_pipe_device*)dev)->write_portal = portal;

    dev = rt_device_find(read_dev);
    if (dev == RT_NULL)
    {
        rt_device_set_tx_complete(dev, portal->parent.tx_complete);
        return -RT_ENOSYS;
    }
    RT_ASSERT(dev->type == RT_Device_Class_Pipe);
    portal->read_dev = dev;
    rt_device_set_rx_indicate(&portal->parent, dev->rx_indicate);
    rt_device_set_rx_indicate(dev, _portal_rx_indicate);
    ((struct rt_pipe_device*)dev)->read_portal = portal;

    return rt_device_register(&(portal->parent),
                              portal_name,
                              RT_DEVICE_FLAG_RDWR);
}
RTM_EXPORT(rt_portal_init);

/**
 * This function will detach a portal device from resource management
 *
 * @param portal the portal device
 *
 * @return the operation status, RT_EOK on successful
 */
rt_err_t rt_portal_detach(struct rt_portal_device *portal)
{
    return rt_device_unregister(&portal->parent);
}
RTM_EXPORT(rt_portal_detach);

#ifdef RT_USING_HEAP
rt_err_t rt_portal_create(const char *name,
                          const char *write_dev,
                          const char *read_dev)
{
    struct rt_portal_device *portal;

    portal = (struct rt_portal_device*)rt_calloc(1, sizeof(*portal));
    if (portal == RT_NULL)
        return -RT_ENOMEM;

    return rt_portal_init(portal, name, write_dev, read_dev);
}
RTM_EXPORT(rt_portal_create);

void rt_portal_destroy(struct rt_portal_device *portal)
{
    if (portal == RT_NULL)
        return;

    rt_portal_detach(portal);

    rt_free(portal);

    return;
}
RTM_EXPORT(rt_portal_destroy);
#endif /* RT_USING_HEAP */

