/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "board.h"
#ifdef BSP_USING_I2C

static struct rt_i2c_bus_device prv_air105_i2c;
static rt_ssize_t air105_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num);
static rt_ssize_t air105_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num);
static rt_err_t air105_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                   int cmd,
                                   void *args);

static const struct rt_i2c_bus_device_ops air105_i2c_ops =
{
    .master_xfer        = air105_i2c_mst_xfer,
    .slave_xfer         = RT_NULL,
    .i2c_bus_control    = air105_i2c_bus_control
};


static rt_ssize_t air105_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    rt_size_t i;
    uint64_t tick;
    struct rt_i2c_msg *msg = msgs;
    RT_ASSERT(bus != RT_NULL);
    rt_uint32_t i2c_id = (rt_uint32_t)bus->priv;
    rt_int32_t Result;
    while(!I2C_WaitResult(i2c_id, &Result)) {;}
    for (i = 0; i < num; i++)
    {
        if (!(msg[i].flags & RT_I2C_NO_START))
        {
            if (msg[i].flags & RT_I2C_ADDR_10BIT)
            {
                I2C_Prepare(i2c_id, msg[i].addr, 2, NULL, NULL);
            }
            else
            {
                I2C_Prepare(i2c_id, msg[i].addr, 1, NULL, NULL);
            }
        }
        if (msg[i].flags & RT_I2C_RD)
        {
            tick = GetSysTick();
            I2C_MasterXfer(i2c_id, I2C_OP_READ, 0, msg[i].buf, msg[i].len, bus->timeout);
            while(!I2C_WaitResult(i2c_id, &Result) && !SysTickCheckTimeout(tick, bus->timeout * CORE_TICK_1MS)){;}
            if (!I2C_WaitResult(i2c_id, &Result))
            {
                I2C_ForceStop(i2c_id);
                return -RT_EIO;
            }
        }
        else
        {
            tick = GetSysTick();
            I2C_MasterXfer(i2c_id, I2C_OP_WRITE, 0, msg[i].buf, msg[i].len, bus->timeout);
            while(!I2C_WaitResult(i2c_id, &Result) && !SysTickCheckTimeout(tick, bus->timeout * CORE_TICK_1MS)){;}
            if (!I2C_WaitResult(i2c_id, &Result))
            {
                I2C_ForceStop(i2c_id);
                return -RT_EIO;
            }
        }
    }
    return i;
}
static rt_ssize_t air105_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    return -RT_ENOSYS;
}
static rt_err_t air105_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                   int cmd,
                                   void *args)
{

    RT_ASSERT(bus != RT_NULL);
    rt_uint32_t i2c_id = (rt_uint32_t)bus->priv;
    switch (cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        I2C_MasterSetup(i2c_id, *(rt_uint32_t *)args);
        break;
    default:
        return -RT_EIO;
    }

    return RT_EOK;
}

int air105_hw_i2c_init(void)
{
    I2C_GlobalInit();
    prv_air105_i2c.ops = &air105_i2c_ops;
    prv_air105_i2c.priv = 0;
    I2C_MasterSetup(0, 400000);
    GPIO_Iomux(GPIOE_06, 2);
    GPIO_Iomux(GPIOE_07, 2);
#ifdef I2C_BUS_NAME
    rt_i2c_bus_device_register(&prv_air105_i2c, I2C_BUS_NAME);
#else
    rt_i2c_bus_device_register(&prv_air105_i2c, "i2c");
#endif

    return 0;
}
INIT_DEVICE_EXPORT(air105_hw_i2c_init);

#endif /* BSP_USING_I2C */
