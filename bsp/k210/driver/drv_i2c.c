/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-12     ZLW          first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_I2C
#include "drv_i2c.h"
#include <drv_io_config.h>
#include <i2c.h>
#include <dmac.h>
#include <sysctl.h>
#include <gpiohs.h>
#include <string.h>
#include "utils.h"

#define MAX_CLOCK  (400000)

struct  k210_i2c_bus
{
    struct rt_i2c_bus_device parent;
    i2c_device_number_t i2c_instance;
    rt_uint32_t slave_addr;
    rt_uint32_t addr_width;
    rt_uint32_t clk_freq;
    dmac_channel_number_t dma_channel;
};



static rt_size_t k210_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                                                          struct rt_i2c_msg msgs[],
                                                                                       rt_uint32_t num)
{
    return 0;
}

static rt_size_t k210_i2c_slave_xfer(struct rt_i2c_bus_device *bus,
                                                                     struct rt_i2c_msg msgs[],
                                                                                    rt_uint32_t num)
{
    return 0;
}

static rt_err_t k210_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                                                        rt_uint32_t cmd,
                                                                       rt_uint32_t arg)
{
    return RT_ERROR;
}

const static struct rt_i2c_bus_device_ops k210_i2c_ops =
{
    k210_i2c_master_xfer,
    k210_i2c_slave_xfer,
    k210_i2c_bus_control
};

int rt_hw_i2c_init(void)
{
    rt_err_t ret = RT_EOK;
    static struct k210_i2c_bus i2c_bus;
#ifdef BSP_USING_I2C0
    i2c_bus.i2c_instance = I2C_DEVICE_0;
    i2c_bus.slave_addr = I2C0_SLAVE_ADDR;
    i2c_bus.addr_width = I2C0_ADDR_WIDTH;
#if I2C0_CLK_FREQ > MAX_CLOCK
    i2c_bus.clk_freq = MAX_CLOCK;
#else
    i2c_bus.clk_freq = I2C0_CLK_FREQ;
#endif
    i2c_init(i2c_bus.i2c_instance,i2c_bus.slave_addr,i2c_bus.addr_width,i2c_bus.clk_freq);
    ret = rt_i2c_bus_device_register(&i2c_bus.parent,"i2c0");

#endif
    
#ifdef BSP_USING_I2C1
    if(ret != RT_EOK)
    {
        return ret;
    }

    i2c_bus.i2c_instance = I2C_DEVICE_1;
    i2c_bus.slave_addr = I2C1_SLAVE_ADDR;
    i2c_bus.addr_width = I2C1_ADDR_WIDTH;
#if I2C1_CLK_FREQ > MAX_CLOCK
    i2c_bus.clk_freq = MAX_CLOCK;
#else
    i2c_bus.clk_freq = I2C1_CLK_FREQ;
#endif
    i2c_init(i2c_bus.i2c_instance,i2c_bus.slave_addr,i2c_bus.addr_width,i2c_bus.clk_freq);
    ret = rt_i2c_bus_device_register(&i2c_bus.parent,"i2c1");
#endif

#ifdef BSP_USING_I2C2
     if(ret != RT_EOK)
    {
        return ret;
    }

    i2c_bus.i2c_instance = I2C_DEVICE_2;
    i2c_bus.slave_addr = I2C2_SLAVE_ADDR;
    i2c_bus.addr_width = I2C2_ADDR_WIDTH;
#if I2C2_CLK_FREQ > MAX_CLOCK
    i2c_bus.clk_freq = MAX_CLOCK;
#else
    i2c_bus.clk_freq = I2C2_CLK_FREQ;
#endif
    i2c_init(i2c_bus.i2c_instance,i2c_bus.slave_addr,i2c_bus.addr_width,i2c_bus.clk_freq);
    ret = rt_i2c_bus_device_register(&i2c_bus.parent,"i2c2");
#endif
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
#endif
