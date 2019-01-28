/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-14     aubr.cool    1st version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "mb85rcxx.h"

struct mb85rcxx_device
{
    struct rt_device         parent;
    struct rt_i2c_bus_device *bus;
};

/* RT-Thread device interface */

static rt_err_t mb85rcxx_init(rt_device_t dev)
{
    return RT_EOK;
}
static rt_err_t mb85rcxx_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t mb85rcxx_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t mb85rcxx_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_size_t mb85rcxx_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct mb85rcxx_device *mb85rcxx;
    const struct mb85rcxx_config *cfg;
    struct rt_i2c_msg msg[2];
    rt_uint8_t mem_addr[2] = {0,};
    rt_size_t ret = 0;
    RT_ASSERT(dev != 0);

    mb85rcxx = (struct mb85rcxx_device *) dev;

    RT_ASSERT(mb85rcxx->parent.user_data != 0);
    cfg = (const struct mb85rcxx_config *) mb85rcxx->parent.user_data;

    if(pos > cfg->size)
    {
         return 0;
    }

    if(pos + size > cfg->size)
    {
         size = cfg->size - pos;
    }

    msg[0].addr     = cfg->addr;
    msg[0].flags    = cfg->flags | RT_I2C_WR;
    mem_addr[0]     = (pos >> 8);
    mem_addr[1]     = (rt_uint8_t) pos;
    msg[0].buf      = (rt_uint8_t *) mem_addr;
    msg[0].len      =  2;

    msg[1].addr     = cfg->addr;
    msg[1].flags    = cfg->flags | RT_I2C_RD;
    msg[1].buf      = (rt_uint8_t *) buffer;
    msg[1].len      = size;

    ret = rt_i2c_transfer(mb85rcxx->bus, msg, 2);
    return (ret == 2) ? size : 0;
}

static rt_size_t mb85rcxx_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct mb85rcxx_device *mb85rcxx;
    const struct mb85rcxx_config *cfg;
    struct rt_i2c_msg msg[2];
    rt_uint8_t mem_addr[2] = {0,};
    rt_size_t ret = 0;
    RT_ASSERT(dev != 0);

    mb85rcxx = (struct mb85rcxx_device *) dev;

    RT_ASSERT(mb85rcxx->parent.user_data != 0);
    cfg = (const struct mb85rcxx_config *) mb85rcxx->parent.user_data;

    if(pos > cfg->size)
    {
         return 0;
    }

    if(pos + size > cfg->size)
    {
         size = cfg->size - pos;
    }

    msg[0].addr     = cfg->addr;
    msg[0].flags    = cfg->flags | RT_I2C_WR;
    mem_addr[0]     = (pos >> 8);
    mem_addr[1]     = (rt_uint8_t) pos;
    msg[0].buf      = (rt_uint8_t *) mem_addr;
    msg[0].len      =  2;

    msg[1].addr     = cfg->addr;
    msg[1].flags    = cfg->flags | RT_I2C_WR | RT_I2C_NO_START;
    msg[1].buf      = (rt_uint8_t *) buffer;
    msg[1].len      = size;

    ret = rt_i2c_transfer(mb85rcxx->bus, msg, 2);
    return (ret == 2) ? size : 0;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device mb85rcxx_ops =
{
    mb85rcxx_init,
    mb85rcxx_open,
    mb85rcxx_close,
    mb85rcxx_read,
    mb85rcxx_write,
    mb85rcxx_control
};
#endif

rt_err_t mb85rcxx_register(const char *fm_device_name, const char *i2c_bus, void *user_data)
{
    static struct mb85rcxx_device mb85rcxx_drv;
    struct rt_i2c_bus_device *bus;

    bus = rt_i2c_bus_device_find(i2c_bus);
    if (bus == RT_NULL)
    {
        return RT_ENOSYS;
    }

    mb85rcxx_drv.bus = bus;
    mb85rcxx_drv.parent.type      = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    mb85rcxx_drv.parent.ops       = &mb85rcxx_ops;
#else
    mb85rcxx_drv.parent.init      = mb85rcxx_init;
    mb85rcxx_drv.parent.open      = mb85rcxx_open;
    mb85rcxx_drv.parent.close     = mb85rcxx_close;
    mb85rcxx_drv.parent.read      = mb85rcxx_read;
    mb85rcxx_drv.parent.write     = mb85rcxx_write;
    mb85rcxx_drv.parent.control   = mb85rcxx_control;
#endif

    mb85rcxx_drv.parent.user_data = user_data;

    return rt_device_register(&mb85rcxx_drv.parent, fm_device_name, RT_DEVICE_FLAG_RDWR);
}

