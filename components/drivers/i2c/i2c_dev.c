/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 * 2014-08-03     bernard       fix some compiling warning
 * 2021-04-20     RiceChen      added support for bus clock control
 */

#include <rtdevice.h>

#define DBG_TAG               "I2C"
#ifdef RT_I2C_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#include <rtdbg.h>

static rt_ssize_t i2c_bus_device_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   count)
{
    rt_uint16_t addr;
    rt_uint16_t flags;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    LOG_D("I2C bus dev [%s] reading %u bytes.", dev->parent.name, count);

    addr = pos & 0xffff;
    flags = (pos >> 16) & 0xffff;

    return rt_i2c_master_recv(bus, addr, flags, (rt_uint8_t *)buffer, count);
}

static rt_ssize_t i2c_bus_device_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   count)
{
    rt_uint16_t addr;
    rt_uint16_t flags;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    LOG_D("I2C bus dev [%s] writing %u bytes.", dev->parent.name, count);

    addr = pos & 0xffff;
    flags = (pos >> 16) & 0xffff;

    return rt_i2c_master_send(bus, addr, flags, (const rt_uint8_t *)buffer, count);
}

static rt_err_t i2c_bus_device_control(rt_device_t dev,
                                       int         cmd,
                                       void       *args)
{
    rt_err_t ret;
    struct rt_i2c_priv_data *priv_data;
    struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data;
    rt_uint32_t bus_clock;

    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
    /* set 10-bit addr mode */
    case RT_I2C_DEV_CTRL_10BIT:
        bus->flags |= RT_I2C_ADDR_10BIT;
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
    case RT_I2C_DEV_CTRL_CLK:
        bus_clock = *(rt_uint32_t *)args;
        ret = rt_i2c_control(bus, cmd, bus_clock);
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

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops i2c_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    i2c_bus_device_read,
    i2c_bus_device_write,
    i2c_bus_device_control
};
#endif

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
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &i2c_ops;
#else
    device->init    = RT_NULL;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = i2c_bus_device_read;
    device->write   = i2c_bus_device_write;
    device->control = i2c_bus_device_control;
#endif

    /* register to device manager */
    rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
