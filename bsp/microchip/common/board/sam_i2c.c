/*
 * Copyright (c)
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-11  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <atmel_start.h>

#ifdef SAM_I2C_EXAMPLE

struct sam_i2c_bus
{
    struct rt_i2c_bus_device parent;
    struct i2c_m_sync_desc  *i2c_desc;
    char                    *device_name;
};

#define I2CBUS_NAME          "i2c0"

static struct sam_i2c_bus sam_i2c0 =
{
    .i2c_desc    = &I2C_0,
    .device_name = I2CBUS_NAME,
};

static rt_ssize_t sam_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num);
static rt_ssize_t sam_i2c_slave_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_err_t sam_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                    rt_uint32_t, rt_uint32_t);

static const struct rt_i2c_bus_device_ops sam_i2c_ops =
{
    .master_xfer     = sam_i2c_master_xfer,
    .slave_xfer      = sam_i2c_slave_xfer,
    .i2c_bus_control = sam_i2c_bus_control,
};

static inline void sam_i2c_update_control(struct rt_i2c_msg *src,
                                          struct _i2c_m_msg *dest)
{
    dest->len    = (int32_t)src->len;
    dest->addr   = src->addr;
    dest->buffer = src->buf;

    /* Get I2C message R/W attribute first */
    dest->flags = dest->flags & 0x0001;

    if (dest->flags & RT_I2C_ADDR_10BIT)
        dest->flags |= I2C_M_TEN;
    else
        dest->flags |= I2C_M_SEVEN;
}

static rt_ssize_t sam_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num)
{
    struct sam_i2c_bus *sam_i2c = (struct sam_i2c_bus *)bus;
    struct _i2c_m_msg   i2c_msg;
    rt_size_t i;

    RT_ASSERT(bus != RT_NULL);

    for (i = 0; i < num; i++)
    {
        sam_i2c_update_control(&msgs[i], &i2c_msg);
        if (i2c_m_sync_transfer(sam_i2c->i2c_desc, &i2c_msg) != 0)
            break;
    }

    return i;
}

static rt_ssize_t sam_i2c_slave_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    return 0;
}

static rt_err_t sam_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                    rt_uint32_t cmd,
                                    rt_uint32_t arg)
{
    return RT_ERROR;
    struct sam_i2c_bus *sam_i2c = (struct sam_i2c_bus *)bus;

    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        i2c_m_sync_set_baudrate(sam_i2c->i2c_desc, 0, arg);
        break;
    default:
        return -RT_EIO;
    }

    return RT_EOK;
}

int rt_hw_i2c_init(void)
{
    rt_i2c_bus_device_register(&sam_i2c0.parent, sam_i2c0.device_name);
    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_i2c_init);
#endif
#endif
/*@}*/
