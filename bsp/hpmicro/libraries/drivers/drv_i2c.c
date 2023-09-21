/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#ifdef BSP_USING_I2C
#include "drv_i2c.h"
#include "hpm_i2c_drv.h"
#include "board.h"

#ifdef RT_USING_I2C

struct hpm_i2c
{
    struct rt_i2c_bus_device bus;
    I2C_Type *base;
    clock_name_t clk_name;
    char *bus_name;
};

static struct hpm_i2c hpm_i2cs[] =
{
#if defined(BSP_USING_I2C0)
    {
        .base = HPM_I2C0,
        .bus_name = "i2c0",
        .clk_name = clock_i2c0,
    },
#endif
#if defined(BSP_USING_I2C1)
    {
        .base = HPM_I2C1,
        .bus_name = "i2c1",
        .clk_name = clock_i2c1,
    },
#endif
#if defined(BSP_USING_I2C2)
    {
        .base = HPM_I2C2,
        .bus_name = "i2c2",
        .clk_name = clock_i2c2,
    },
#endif
#if defined(BSP_USING_I2C3)
    {
        .base = HPM_I2C3,
        .bus_name = "i2c3",
        .clk_name = clock_i2c3,
    },
#endif
};

static rt_ssize_t hpm_i2c_master_transfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);


struct rt_i2c_bus_device_ops hpm_i2c_ops =
{
    hpm_i2c_master_transfer,
    RT_NULL,
    RT_NULL
};

static rt_ssize_t hpm_i2c_master_transfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    struct rt_i2c_msg *msg;
    struct hpm_i2c *i2c_info = (struct hpm_i2c *)bus;

    hpm_stat_t i2c_stat = status_success;
    rt_size_t ret = 0;
    rt_uint32_t i;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            i2c_enable_10bit_address_mode(i2c_info->base, true);
        }
        else
        {
            i2c_enable_10bit_address_mode(i2c_info->base, false);
        }

        if (msg->flags & RT_I2C_RD)
        {
            i2c_stat = i2c_master_read(i2c_info->base, msg->addr, msg->buf, msg->len);
        }
        else
        {
            i2c_stat = i2c_master_write(i2c_info->base, msg->addr, msg->buf, msg->len);
        }

        if (i2c_stat != status_success)
        {
            break;
        }
    }

    if (i2c_stat != status_success)
    {
        return ret;
    }

    ret = i;
    return ret;
}


int rt_hw_i2c_init(void)
{
    rt_err_t ret = RT_EOK;
    hpm_stat_t stat;
    i2c_config_t config;
    rt_uint32_t freq;

    for (uint32_t i = 0; i < sizeof(hpm_i2cs) / sizeof(hpm_i2cs[0]); i++) {
        init_i2c_pins(hpm_i2cs[i].base);
        clock_add_to_group(hpm_i2cs[i].clk_name, 0);
        clock_set_source_divider(hpm_i2cs[i].clk_name, clk_src_osc24m, 1U);

        config.i2c_mode = i2c_mode_normal;
        config.is_10bit_addressing = false;
        freq = clock_get_frequency(hpm_i2cs[i].clk_name);
        stat = i2c_init_master(hpm_i2cs[i].base, freq, &config);
        if (stat != status_success) {
            LOG_E("rt i2c device %s init failed", hpm_i2cs[i].bus_name);
        }

        hpm_i2cs[i].bus.ops = &hpm_i2c_ops;
        ret = rt_i2c_bus_device_register(&hpm_i2cs[i].bus, hpm_i2cs[i].bus_name);
        if (ret != RT_EOK) {
            LOG_E("rt i2c device %s register failed, status=%d\n", hpm_i2cs[i].bus_name, ret);
        }
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */

#endif /*BSP_USING_I2C*/

