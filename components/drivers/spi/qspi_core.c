/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-16     zylx      first version.
 */

#include <drivers/spi.h>

rt_err_t rt_qspi_configure(struct rt_qspi_device *device, struct rt_qspi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    struct rt_qspi_device *qspi_device = (struct rt_qspi_device *)device;
    rt_err_t result = RT_EOK;

    /* copy configuration items */
    qspi_device->config.parent.mode = cfg->parent.mode;
    qspi_device->config.parent.max_hz = cfg->parent.max_hz;
    qspi_device->config.parent.data_width = cfg->parent.data_width;
    qspi_device->config.parent.reserved = cfg->parent.reserved;
    qspi_device->config.medium_size = cfg->medium_size;
    qspi_device->config.ddr_mode = cfg->ddr_mode;
    qspi_device->config.qspi_dl_width = cfg->qspi_dl_width;

    result = rt_spi_configure(&device->parent, &cfg->parent);

    return result;
}

rt_err_t rt_qspi_bus_register(struct rt_spi_bus *bus, const char *name, const struct rt_spi_ops *ops)
{
    rt_err_t result = RT_EOK;

    result = rt_spi_bus_register(bus, name, ops);
    if(result == RT_EOK)
    {
        /* set SPI bus to qspi modes */
        bus->mode = RT_SPI_BUS_MODE_QSPI;
    }

    return result;
}

rt_size_t rt_qspi_transfer_message(struct rt_qspi_device  *device, struct rt_qspi_message *message)
{
    rt_err_t result;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    result = rt_mutex_take(&(device->parent.bus->lock), RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        rt_set_errno(-RT_EBUSY);

        return 0;
    }

    /* reset errno */
    rt_set_errno(RT_EOK);

    /* configure SPI bus */
    if (device->parent.bus->owner != &device->parent)
    {
        /* not the same owner as current, re-configure SPI bus */
        result = device->parent.bus->ops->configure(&device->parent, &device->parent.config);
        if (result == RT_EOK)
        {
            /* set SPI bus owner */
            device->parent.bus->owner = &device->parent;
        }
        else
        {
            /* configure SPI bus failed */
            rt_set_errno(-RT_EIO);
            goto __exit;
        }
    }

    /* transmit each SPI message */

    result = device->parent.bus->ops->xfer(&device->parent, &message->parent);
    if (result == 0)
    {
        rt_set_errno(-RT_EIO);
    }

__exit:
    /* release bus lock */
    rt_mutex_release(&(device->parent.bus->lock));

    return result;
}

rt_err_t rt_qspi_send_then_recv(struct rt_qspi_device *device, const void *send_buf, rt_size_t send_length, void *recv_buf, rt_size_t recv_length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(recv_buf);
    RT_ASSERT(send_length != 0);

    struct rt_qspi_message message;
    unsigned char *ptr = (unsigned char *)send_buf;
    rt_size_t count = 0;
    rt_err_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.qspi_lines = 1;
    count++;

    /* get address */
    if (send_length > 1)
    {
        if (device->config.medium_size > 0x1000000 && send_length >= 5)
        {
            /* medium size greater than 16Mb, address size is 4 Byte */
            message.address.content = (ptr[1] << 24) | (ptr[2] << 16) | (ptr[3] << 8) | (ptr[4]);
            message.address.size = 32;
            count += 4;
        }
        else if (send_length >= 4)
        {
            /* address size is 3 Byte */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            count += 3;
        }
        else
        {
            return -RT_ERROR;
        }
        message.address.qspi_lines = 1;
    }
    else
    {
        /* no address stage */
        message.address.content = 0 ;
        message.address.qspi_lines = 0;
        message.address.size = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.qspi_lines = 0;

    /* set dummy cycles */
    if (count != send_length)
    {
        message.dummy_cycles = (send_length - count) * 8;

    }
    else
    {
        message.dummy_cycles = 0;
    }

    /* set recv buf and recv size */
    message.parent.recv_buf = recv_buf;
    message.parent.send_buf = RT_NULL;
    message.parent.length = recv_length;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;

    message.qspi_data_lines = 1;

    result = rt_qspi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else
    {
        result = recv_length;
    }

    return result;
}

rt_err_t rt_qspi_send(struct rt_qspi_device *device, const void *send_buf, rt_size_t length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(length != 0);

    struct rt_qspi_message message;
    char *ptr = (char *)send_buf;
    rt_size_t  count = 0;
    rt_err_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.qspi_lines = 1;
    count++;

    /* get address */
    if (length > 1)
    {
        if (device->config.medium_size > 0x1000000 && length >= 5)
        {
            /* medium size greater than 16Mb, address size is 4 Byte */
            message.address.content = (ptr[1] << 24) | (ptr[2] << 16) | (ptr[3] << 8) | (ptr[4]);
            message.address.size = 32;
            message.address.qspi_lines = 1;
            count += 4;
        }
        else if (length >= 4)
        {
            /* address size is 3 Byte */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            message.address.qspi_lines = 1;
            count += 3;
        }
        else
        {
            return -RT_ERROR;
        }

    }
    else
    {
        /* no address stage */
        message.address.content = 0 ;
        message.address.qspi_lines = 0;
        message.address.size = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.qspi_lines = 0;

    message.dummy_cycles = 0;

    /* determine if there is data to send */
    if (length - count > 0)
    {
        message.qspi_data_lines = 1;
    }
    else
    {
        message.qspi_data_lines = 0;

    }

    /* set send buf and send size */
    message.parent.send_buf = ptr + count;
    message.parent.recv_buf = RT_NULL;
    message.parent.length = length - count;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;

    result = rt_qspi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else
    {
        result = length;
    }

    return result;
}
