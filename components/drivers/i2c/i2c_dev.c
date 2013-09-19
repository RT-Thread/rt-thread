/*
 * File      : i2c_dev.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 */

#include <rtdevice.h>

static rt_err_t i2c_bus_device_init(rt_device_t dev)
{
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;
    RT_ASSERT(bus != RT_NULL);

    return RT_EOK;
}

static rt_size_t i2c_bus_device_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   count)
{
    rt_uint16_t addr;
    rt_uint16_t flags;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    i2c_dbg("I2C bus dev [%s] reading %u bytes.\n", dev->parent.name, count);

    addr = pos & 0xffff;
    flags = (pos >> 16) & 0xffff;

    return rt_i2c_master_recv(bus, addr, flags, buffer, count);
}

static rt_size_t i2c_bus_device_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   count)
{
    rt_uint16_t addr;
    rt_uint16_t flags;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    i2c_dbg("I2C bus dev writing %u bytes.\n", dev->parent.name, count);

    addr = pos & 0xffff;
    flags = (pos >> 16) & 0xffff;

    return rt_i2c_master_send(bus, addr, flags, buffer, count);
}

static rt_err_t i2c_bus_device_control(rt_device_t dev,
                                       rt_uint8_t  cmd,
                                       void       *args)
{
    rt_err_t ret;
    struct rt_i2c_priv_data *priv_data;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;

    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
    /* set 10-bit addr mode */
    case RT_I2C_DEV_CTRL_10BIT:
        bus->flags |= RT_I2C_ADDR_10BIT;
        break;
    case RT_I2C_DEV_CTRL_ADDR:
        bus->addr = *(rt_uint16_t *)args;
        break;
    case RT_I2C_DEV_CTRL_TIMEOUT:
        bus->timeout = *(rt_uint32_t *)args;
        break;
    case RT_I2C_DEV_CTRL_RW:
        priv_data = (struct rt_i2c_priv_data *)args;
        ret = rt_i2c_transfer(bus, priv_data->msgs, priv_data->number);
        if (ret < 0)
        {
            return -RT_EIO;
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}

rt_err_t rt_i2c_bus_device_device_init(struct rt_i2c_bus_device *bus,
                                       const char               *name)
{
    struct rt_device *device;
    RT_ASSERT(bus != RT_NULL);

    device = &bus->parent;

    device->user_data = bus;

    /* set device type */
    device->type    = RT_Device_Class_I2CBUS;
    /* initialize device interface */
    device->init    = i2c_bus_device_init;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = i2c_bus_device_read;
    device->write   = i2c_bus_device_write;
    device->control = i2c_bus_device_control;

    /* register to device manager */
    rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
