/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     cliffLL      first version.
 */

#include "drivers/dev_spi.h"

extern rt_err_t spi_bus_register(struct rt_spi_bus *bus,
                                 const char *name,
                                 const struct rt_spi_ops *ops);

rt_err_t rt_ospi_configure(struct rt_ospi_device *device, struct rt_ospi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* reset the CS pin */
    if (device->parent.cs_pin != PIN_NONE)
    {
        rt_err_t result = rt_mutex_take(&(device->parent.bus->lock), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            if (cfg->parent.mode & RT_SPI_CS_HIGH)
            {
                rt_pin_write(device->parent.cs_pin, PIN_LOW);
            }
            else
            {
                rt_pin_write(device->parent.cs_pin, PIN_HIGH);
            }
            rt_mutex_release(&(device->parent.bus->lock));
        }
        else
        {
            return result;
        }
    }

    /* copy configuration items */
    device->config.parent.mode = cfg->parent.mode;
    device->config.parent.max_hz = cfg->parent.max_hz;
    device->config.parent.data_width = cfg->parent.data_width;
#ifdef RT_USING_DM
    device->config.parent.data_width_tx = cfg->parent.data_width_tx;
    device->config.parent.data_width_rx = cfg->parent.data_width_rx;
#else
    device->config.parent.reserved = cfg->parent.reserved;
#endif
    device->config.medium_size = cfg->medium_size;
    device->config.dtr_mode = cfg->dtr_mode;

    return rt_spi_bus_configure(&device->parent);
}

rt_err_t rt_ospi_bus_register(struct rt_spi_bus *bus, const char *name, const struct rt_spi_ops *ops)
{
    /* set SPI bus to ospi modes */
    bus->mode = RT_SPI_BUS_MODE_OSPI;

    return spi_bus_register(bus, name, ops);
}

rt_ssize_t rt_ospi_transfer_message(struct rt_ospi_device *device, struct rt_ospi_message *message)
{
    rt_ssize_t result;

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

rt_ssize_t rt_ospi_send_then_recv(struct rt_ospi_device *device, const void *send_buf, rt_size_t send_length, void *recv_buf, rt_size_t recv_length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(recv_buf);
    RT_ASSERT(send_length != 0);

    struct rt_ospi_message message;
    unsigned char *ptr = (unsigned char *)send_buf;
    rt_size_t count = 0;
    rt_ssize_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.size = 8;
    message.instruction.ospi_lines = 1;
    message.instruction.dtrmode = 0;
    count++;

    /* get address */
    if (send_length > 1)
    {
        if ((send_length >= 5) && (message.instruction.content != 0x5A))
        {
            /* 4 Byte command, address size is 4 Byte */
            message.address.content = (ptr[1] << 24) | (ptr[2] << 16) | (ptr[3] << 8) | (ptr[4]);
            message.address.size = 32;
            message.address.ospi_lines = 1;
            message.address.dtrmode = 0;
            count += 4;
        }
        else if (send_length >= 4)
        {
            /*
             * JEDEC Read SFDP (0x5A) uses:
             *   1-byte instruction + 3-byte address + 1-byte dummy.
             *
             * The fifth byte in the SPI buffer is a dummy byte, not a fourth
             * address byte. Parse the address as 24-bit so that dummy_cycles
             * is calculated correctly.
             */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            message.address.ospi_lines = 1;
            message.address.dtrmode = 0;
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
        message.address.content = 0;
        message.address.ospi_lines = 0;
        message.address.size = 0;
        message.address.dtrmode = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.ospi_lines = 0;
    message.alternate_bytes.dtrmode = 0;

    /* if send_length is not equal to count, dummy cycles exit and should be set */
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

    message.ospi_data_lines = 1;
    message.ospi_data_dtrmode = 0;
    message.dqs_mode = 0;
    /* set next */
    /* Ensure correct OSPI message chaining by setting next pointer to NULL, preventing unintended data transmission issues.*/
    message.parent.next = RT_NULL;

    result = rt_ospi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else if (result > 0)
    {
        result = recv_length;
    }

    return result;
}

rt_ssize_t rt_ospi_send(struct rt_ospi_device *device, const void *send_buf, rt_size_t length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(length != 0);

    struct rt_ospi_message message;
    unsigned char *ptr = (unsigned char *)send_buf;
    rt_size_t count = 0;
    rt_ssize_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.size = 8;
    message.instruction.ospi_lines = 1;
    message.instruction.dtrmode = 0;
    count++;

    /* get address */
    if (length > 1)
    {
        if (length >= 5)
        {
            /* 4 Byte command, address size is 4 Byte */
            message.address.content = (ptr[1] << 24) | (ptr[2] << 16) | (ptr[3] << 8) | (ptr[4]);
            message.address.size = 32;
            message.address.ospi_lines = 1;
            message.address.dtrmode = 0;
            count += 4;
        }
        else if (length >= 4)
        {
            /* address size is 3 Byte */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            message.address.ospi_lines = 1;
            message.address.dtrmode = 0;
            count += 3;
        }
        else if (length >= 2)
        {
            /* no address but send data */
            message.address.content = 0;
            message.address.ospi_lines = 0;
            message.address.size = 0;
            message.address.dtrmode = 0;
        }
        else
        {
            return -RT_ERROR;
        }
    }
    else
    {
        /* no address stage */
        message.address.content = 0;
        message.address.ospi_lines = 0;
        message.address.size = 0;
        message.address.dtrmode = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.ospi_lines = 0;
    message.alternate_bytes.dtrmode = 0;

    message.dummy_cycles = 0;

    /* determine if there is data to send */
    if (length - count > 0)
    {
        message.ospi_data_lines = 1;
    }
    else
    {
        message.ospi_data_lines = 0;
    }

    /* set send buf and send size */
    message.parent.send_buf = ptr + count;
    message.parent.recv_buf = RT_NULL;
    message.parent.length = length - count;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;

    message.ospi_data_dtrmode = 0;
    message.dqs_mode = 0;
    /* set next */
    /* Ensure correct OSPI message chaining by setting next pointer to NULL, preventing unintended data transmission issues.*/
    message.parent.next = RT_NULL;

    result = rt_ospi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else if (result > 0)
    {
        result = length;
    }

    return result;
}
