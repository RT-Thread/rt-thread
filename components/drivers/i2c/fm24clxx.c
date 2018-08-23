/*
 * File      : fm24clxx.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-07-14     aubr.cool    1st version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "fm24clxx.h"

struct fm24clxx_device
{
    struct rt_device         parent;
    struct rt_i2c_bus_device *bus;
};

/* RT-Thread device interface */

static rt_err_t fm24clxx_init(rt_device_t dev)
{
    return RT_EOK;
}
static rt_err_t fm24clxx_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t fm24clxx_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t fm24clxx_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_size_t fm24clxx_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct fm24clxx_device *fm24clxx;
    const struct fm24clxx_config *cfg;
    struct rt_i2c_msg msg[2];
    rt_uint8_t mem_addr[2] = {0,};
    rt_size_t ret = 0;
    RT_ASSERT(dev != 0);

    fm24clxx = (struct fm24clxx_device *) dev;

    RT_ASSERT(fm24clxx->parent.user_data != 0);
    cfg = (const struct fm24clxx_config *) fm24clxx->parent.user_data;

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

    ret = rt_i2c_transfer(fm24clxx->bus, msg, 2);
    return (ret == 2) ? size : 0;
}

static rt_size_t fm24clxx_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct fm24clxx_device *fm24clxx;
    const struct fm24clxx_config *cfg;
    struct rt_i2c_msg msg[2];
    rt_uint8_t mem_addr[2] = {0,};
    rt_size_t ret = 0;
    RT_ASSERT(dev != 0);

    fm24clxx = (struct fm24clxx_device *) dev;

    RT_ASSERT(fm24clxx->parent.user_data != 0);
    cfg = (const struct fm24clxx_config *) fm24clxx->parent.user_data;

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

    ret = rt_i2c_transfer(fm24clxx->bus, msg, 2);
    return (ret == 2) ? size : 0;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device fm24clxx_ops =
{
    fm24clxx_init,
    fm24clxx_open,
    fm24clxx_close,
    fm24clxx_read,
    fm24clxx_write,
    fm24clxx_control
};
#endif

rt_err_t fm24clxx_register(const char *fm_device_name, const char *i2c_bus, void *user_data)
{
    static struct fm24clxx_device fm24clxx_drv;
    struct rt_i2c_bus_device *bus;

    bus = rt_i2c_bus_device_find(i2c_bus);
    if (bus == RT_NULL)
    {
        return RT_ENOSYS;
    }

    fm24clxx_drv.bus = bus;
    fm24clxx_drv.parent.type      = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    fm24clxx_drv.parent.ops       = &fm24clxx_ops;
#else
    fm24clxx_drv.parent.init      = fm24clxx_init;
    fm24clxx_drv.parent.open      = fm24clxx_open;
    fm24clxx_drv.parent.close     = fm24clxx_close;
    fm24clxx_drv.parent.read      = fm24clxx_read;
    fm24clxx_drv.parent.write     = fm24clxx_write;
    fm24clxx_drv.parent.control   = fm24clxx_control;
#endif

    fm24clxx_drv.parent.user_data = user_data;

    return rt_device_register(&fm24clxx_drv.parent, fm_device_name, RT_DEVICE_FLAG_RDWR);
}