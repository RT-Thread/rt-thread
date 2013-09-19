/*
 * File      : i2c_core.c
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

static struct rt_mutex i2c_core_lock;

rt_err_t rt_i2c_bus_device_register(struct rt_i2c_bus_device *bus,
                                    const char               *bus_name)
{
    rt_err_t res = RT_EOK;

    rt_mutex_init(&bus->lock, "i2c_bus_lock", RT_IPC_FLAG_FIFO);

    rt_mutex_take(&i2c_core_lock, RT_WAITING_FOREVER);

    if (bus->timeout == 0)
        bus->timeout = RT_TICK_PER_SECOND;

    res = rt_i2c_bus_device_device_init(bus, bus_name);

    i2c_dbg("I2C bus [%s] registered\n", bus_name);

    rt_mutex_release(&i2c_core_lock);

    return res;
}

struct rt_i2c_bus_device *rt_i2c_bus_device_find(const char *bus_name)
{
    struct rt_i2c_bus_device *bus;
    rt_device_t dev = rt_device_find(bus_name);
    if (dev == RT_NULL || dev->type != RT_Device_Class_I2CBUS)
    {
        i2c_dbg("I2C bus %s not exist\n", bus_name);

        return RT_NULL;
    }

    bus = (struct rt_i2c_bus_device *)dev->user_data;

    return bus;
}

rt_size_t rt_i2c_transfer(struct rt_i2c_bus_device *bus,
                          struct rt_i2c_msg         msgs[],
                          rt_uint32_t               num)
{
    rt_size_t ret;

    if (bus->ops->master_xfer)
    {
#ifdef RT_I2C_DEBUG
        for (ret = 0; ret < num; ret++)
        {
            i2c_dbg("msgs[%d] %c, addr=0x%02x, len=%d%s\n", ret,
                    (msgs[ret].flags & RT_I2C_RD) ? 'R' : 'W',
                    msgs[ret].addr, msgs[ret].len);
        }
#endif

        rt_mutex_take(&bus->lock, RT_WAITING_FOREVER);
        ret = bus->ops->master_xfer(bus, msgs, num);
        rt_mutex_release(&bus->lock);

        return ret;
    }
    else
    {
        i2c_dbg("I2C bus operation not supported\n");

        return 0;
    }
}

rt_size_t rt_i2c_master_send(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             const rt_uint8_t         *buf,
                             rt_uint32_t               count)
{
    rt_size_t ret;
    struct rt_i2c_msg msg;

    msg.addr  = addr;
    msg.flags = flags & RT_I2C_ADDR_10BIT;
    msg.len   = count;
    msg.buf   = (rt_uint8_t *)buf;

    ret = rt_i2c_transfer(bus, &msg, 1);

    return (ret > 0) ? count : ret;
}

rt_size_t rt_i2c_master_recv(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             rt_uint8_t               *buf,
                             rt_uint32_t               count)
{
    rt_size_t ret;
    struct rt_i2c_msg msg;
    RT_ASSERT(bus != RT_NULL);

    msg.addr   = addr;
    msg.flags  = flags & RT_I2C_ADDR_10BIT;
    msg.flags |= RT_I2C_RD;
    msg.len    = count;
    msg.buf    = buf;

    ret = rt_i2c_transfer(bus, &msg, 1);

    return (ret > 0) ? count : ret;
}

int rt_i2c_core_init(void)
{
    return rt_mutex_init(&i2c_core_lock, "i2c_core_lock", RT_IPC_FLAG_FIFO);
}
INIT_COMPONENT_EXPORT(rt_i2c_core_init);
