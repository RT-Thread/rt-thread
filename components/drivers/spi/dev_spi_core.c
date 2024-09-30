/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-08     bernard      first version.
 * 2012-02-03     bernard      add const attribute to the ops.
 * 2012-05-15     dzzxzz       fixed the return value in attach_device.
 * 2012-05-18     bernard      Changed SPI message to message list.
 *                             Added take/release SPI device/bus interface.
 * 2012-09-28     aozima       fixed rt_spi_release_bus assert error.
 */

#include "drivers/dev_spi.h"

#define DBG_TAG    "spi.core"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

extern rt_err_t rt_spi_bus_device_init(struct rt_spi_bus *bus, const char *name);
extern rt_err_t rt_spidev_device_init(struct rt_spi_device *dev, const char *name);

rt_err_t rt_spi_bus_register(struct rt_spi_bus       *bus,
                             const char              *name,
                             const struct rt_spi_ops *ops)
{
    rt_err_t result;

    result = rt_spi_bus_device_init(bus, name);
    if (result != RT_EOK)
        return result;

    /* initialize mutex lock */
    rt_mutex_init(&(bus->lock), name, RT_IPC_FLAG_PRIO);
    /* set ops */
    bus->ops = ops;
    /* initialize owner */
    bus->owner = RT_NULL;
    /* set bus mode */
    bus->mode = RT_SPI_BUS_MODE_SPI;

    return RT_EOK;
}

rt_err_t rt_spi_bus_attach_device_cspin(struct rt_spi_device *device,
                                        const char           *name,
                                        const char           *bus_name,
                                        rt_base_t            cs_pin,
                                        void                 *user_data)
{
    rt_err_t result;
    rt_device_t bus;

    /* get physical spi bus */
    bus = rt_device_find(bus_name);
    if (bus != RT_NULL && bus->type == RT_Device_Class_SPIBUS)
    {
        device->bus = (struct rt_spi_bus *)bus;

        /* initialize spidev device */
        result = rt_spidev_device_init(device, name);
        if (result != RT_EOK)
            return result;

        if(cs_pin != PIN_NONE)
        {
            rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
        }

        rt_memset(&device->config, 0, sizeof(device->config));
        device->parent.user_data = user_data;
        device->cs_pin = cs_pin;
        return RT_EOK;
    }

    /* not found the host bus */
    return -RT_ERROR;
}

rt_err_t rt_spi_bus_attach_device(struct rt_spi_device *device,
                                  const char           *name,
                                  const char           *bus_name,
                                  void                 *user_data)
{
    return rt_spi_bus_attach_device_cspin(device, name, bus_name, PIN_NONE, user_data);
}

rt_err_t rt_spi_bus_configure(struct rt_spi_device *device)
{
    rt_err_t result = -RT_ERROR;

    if (device->bus != RT_NULL)
    {
        result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            if (device->bus->owner == device)
            {
                /* current device is using, re-configure SPI bus */
                result = device->bus->ops->configure(device, &device->config);
                if (result != RT_EOK)
                {
                    /* configure SPI bus failed */
                    LOG_E("SPI device %s configuration failed", device->parent.parent.name);
                }
            }

            /* release lock */
            rt_mutex_release(&(device->bus->lock));
        }
    }
    else
    {
        result = RT_EOK;
    }

    return result;
}

rt_err_t rt_spi_configure(struct rt_spi_device        *device,
                          struct rt_spi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* reset the CS pin */
    if (device->cs_pin != PIN_NONE)
    {
        if (cfg->mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    /* If the configurations are the same, we don't need to set again. */
    if (device->config.data_width == cfg->data_width &&
        device->config.mode       == (cfg->mode & RT_SPI_MODE_MASK) &&
        device->config.max_hz     == cfg->max_hz)
    {
        return RT_EOK;
    }

    /* set configuration */
    device->config.data_width = cfg->data_width;
    device->config.mode       = cfg->mode & RT_SPI_MODE_MASK;
    device->config.max_hz     = cfg->max_hz;

    return rt_spi_bus_configure(device);
}

rt_err_t rt_spi_send_then_send(struct rt_spi_device *device,
                               const void           *send_buf1,
                               rt_size_t             send_length1,
                               const void           *send_buf2,
                               rt_size_t             send_length2)
{
    rt_err_t result;
    struct rt_spi_message message;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (device->bus->owner != device)
        {
            /* not the same owner as current, re-configure SPI bus */
            result = device->bus->ops->configure(device, &device->config);
            if (result == RT_EOK)
            {
                /* set SPI bus owner */
                device->bus->owner = device;
            }
            else
            {
                /* configure SPI bus failed */
                LOG_E("SPI device %s configuration failed", device->parent.parent.name);
                goto __exit;
            }
        }

        /* send data1 */
        message.send_buf   = send_buf1;
        message.recv_buf   = RT_NULL;
        message.length     = send_length1;
        message.cs_take    = 1;
        message.cs_release = 0;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result < 0)
        {
            LOG_E("SPI device %s transfer failed", device->parent.parent.name);
            goto __exit;
        }

        /* send data2 */
        message.send_buf   = send_buf2;
        message.recv_buf   = RT_NULL;
        message.length     = send_length2;
        message.cs_take    = 0;
        message.cs_release = 1;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result < 0)
        {
            LOG_E("SPI device %s transfer failed", device->parent.parent.name);
            goto __exit;
        }

        result = RT_EOK;
    }
    else
    {
        return -RT_EIO;
    }

__exit:
    rt_mutex_release(&(device->bus->lock));

    return result;
}

rt_err_t rt_spi_send_then_recv(struct rt_spi_device *device,
                               const void           *send_buf,
                               rt_size_t             send_length,
                               void                 *recv_buf,
                               rt_size_t             recv_length)
{
    rt_err_t result;
    struct rt_spi_message message;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (device->bus->owner != device)
        {
            /* not the same owner as current, re-configure SPI bus */
            result = device->bus->ops->configure(device, &device->config);
            if (result == RT_EOK)
            {
                /* set SPI bus owner */
                device->bus->owner = device;
            }
            else
            {
                /* configure SPI bus failed */
                LOG_E("SPI device %s configuration failed", device->parent.parent.name);
                goto __exit;
            }
        }

        /* send data */
        message.send_buf   = send_buf;
        message.recv_buf   = RT_NULL;
        message.length     = send_length;
        message.cs_take    = 1;
        message.cs_release = 0;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result < 0)
        {
            LOG_E("SPI device %s transfer failed", device->parent.parent.name);
            goto __exit;
        }

        /* recv data */
        message.send_buf   = RT_NULL;
        message.recv_buf   = recv_buf;
        message.length     = recv_length;
        message.cs_take    = 0;
        message.cs_release = 1;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result < 0)
        {
            LOG_E("SPI device %s transfer failed", device->parent.parent.name);
            goto __exit;
        }

        result = RT_EOK;
    }
    else
    {
        return -RT_EIO;
    }

__exit:
    rt_mutex_release(&(device->bus->lock));

    return result;
}

rt_ssize_t rt_spi_transfer(struct rt_spi_device *device,
                           const void           *send_buf,
                           void                 *recv_buf,
                           rt_size_t             length)
{
    rt_ssize_t result;
    struct rt_spi_message message;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (device->bus->owner != device)
        {
            /* not the same owner as current, re-configure SPI bus */
            result = device->bus->ops->configure(device, &device->config);
            if (result == RT_EOK)
            {
                /* set SPI bus owner */
                device->bus->owner = device;
            }
            else
            {
                /* configure SPI bus failed */
                LOG_E("SPI device %s configuration failed", device->parent.parent.name);
                goto __exit;
            }
        }

        /* initial message */
        message.send_buf   = send_buf;
        message.recv_buf   = recv_buf;
        message.length     = length;
        message.cs_take    = 1;
        message.cs_release = 1;
        message.next       = RT_NULL;

        /* transfer message */
        result = device->bus->ops->xfer(device, &message);
        if (result < 0)
        {
            LOG_E("SPI device %s transfer failed", device->parent.parent.name);
            goto __exit;
        }
    }
    else
    {
        return -RT_EIO;
    }

__exit:
    rt_mutex_release(&(device->bus->lock));

    return result;
}

rt_err_t rt_spi_sendrecv8(struct rt_spi_device *device,
                          rt_uint8_t            senddata,
                          rt_uint8_t           *recvdata)
{
    rt_ssize_t len = rt_spi_transfer(device, &senddata, recvdata, 1);
    if (len < 0)
    {
        return (rt_err_t)len;
    }
    else
    {
        return RT_EOK;
    }
}

rt_err_t rt_spi_sendrecv16(struct rt_spi_device *device,
                           rt_uint16_t           senddata,
                           rt_uint16_t          *recvdata)
{
    rt_ssize_t len;
    rt_uint16_t tmp;

    if (device->config.mode & RT_SPI_MSB)
    {
        tmp = ((senddata & 0xff00) >> 8) | ((senddata & 0x00ff) << 8);
        senddata = tmp;
    }

    len = rt_spi_transfer(device, &senddata, recvdata, 2);
    if(len < 0)
    {
        return (rt_err_t)len;
    }

    if (device->config.mode & RT_SPI_MSB)
    {
        tmp = ((*recvdata & 0xff00) >> 8) | ((*recvdata & 0x00ff) << 8);
        *recvdata = tmp;
    }

    return RT_EOK;
}

struct rt_spi_message *rt_spi_transfer_message(struct rt_spi_device  *device,
                                               struct rt_spi_message *message)
{
    rt_err_t result;
    struct rt_spi_message *index;

    RT_ASSERT(device != RT_NULL);

    /* get first message */
    index = message;
    if (index == RT_NULL)
        return index;

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return index;
    }

    /* configure SPI bus */
    if (device->bus->owner != device)
    {
        /* not the same owner as current, re-configure SPI bus */
        result = device->bus->ops->configure(device, &device->config);
        if (result == RT_EOK)
        {
            /* set SPI bus owner */
            device->bus->owner = device;
        }
        else
        {
            /* configure SPI bus failed */
            goto __exit;
        }
    }

    /* transmit each SPI message */
    while (index != RT_NULL)
    {
        /* transmit SPI message */
        result = device->bus->ops->xfer(device, index);
        if (result < 0)
        {
            break;
        }

        index = index->next;
    }

__exit:
    /* release bus lock */
    rt_mutex_release(&(device->bus->lock));

    return index;
}

rt_err_t rt_spi_take_bus(struct rt_spi_device *device)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return -RT_EBUSY;
    }

    /* configure SPI bus */
    if (device->bus->owner != device)
    {
        /* not the same owner as current, re-configure SPI bus */
        result = device->bus->ops->configure(device, &device->config);
        if (result == RT_EOK)
        {
            /* set SPI bus owner */
            device->bus->owner = device;
        }
        else
        {
            /* configure SPI bus failed */
            rt_mutex_release(&(device->bus->lock));

            return result;
        }
    }

    return result;
}

rt_err_t rt_spi_release_bus(struct rt_spi_device *device)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->owner == device);

    /* release lock */
    return rt_mutex_release(&(device->bus->lock));
}

rt_err_t rt_spi_take(struct rt_spi_device *device)
{
    rt_ssize_t result;
    struct rt_spi_message message;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    rt_memset(&message, 0, sizeof(message));
    message.cs_take = 1;

    result = device->bus->ops->xfer(device, &message);
    if(result < 0)
    {
        return (rt_err_t)result;
    }

    return RT_EOK;
}

rt_err_t rt_spi_release(struct rt_spi_device *device)
{
    rt_ssize_t result;
    struct rt_spi_message message;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    rt_memset(&message, 0, sizeof(message));
    message.cs_release = 1;

    result = device->bus->ops->xfer(device, &message);
    if(result < 0)
    {
        return (rt_err_t)result;
    }

    return RT_EOK;
}
