/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_HW_I2C_H__
#define __DRV_HW_I2C_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gd32_i2c_config
{
    rt_uint32_t i2c_periph;
    rcu_periph_enum periph_clk;

    rcu_periph_enum scl_clk;
    rt_uint32_t scl_port;
    rt_uint32_t scl_pin;
    rt_uint32_t scl_af;

    rcu_periph_enum sda_clk;
    rt_uint32_t sda_port;
    rt_uint32_t sda_pin;
    rt_uint32_t sda_af;

    rt_uint32_t i2c_clock_hz;  /* I2C clock frequency in Hz */
    const char *device_name;
};

struct gd32_i2c
{
    struct rt_i2c_bus_device parent;
    const struct gd32_i2c_config *config;
    rt_uint32_t i2c_clock_hz;
};

int rt_hw_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HW_I2C_H__ */

