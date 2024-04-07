/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __I2C_DM_H__
#define __I2C_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/core/bus.h>

/* I2C Frequency Modes */
#define I2C_MAX_STANDARD_MODE_FREQ      100000
#define I2C_MAX_FAST_MODE_FREQ          400000
#define I2C_MAX_FAST_MODE_PLUS_FREQ     1000000
#define I2C_MAX_TURBO_MODE_FREQ         1400000
#define I2C_MAX_HIGH_SPEED_MODE_FREQ    3400000
#define I2C_MAX_ULTRA_FAST_MODE_FREQ    5000000

struct i2c_timings
{
    rt_uint32_t bus_freq_hz; /* the bus frequency in Hz */
    rt_uint32_t scl_rise_ns; /* time SCL signal takes to rise in ns; t(r) in the I2C specification */
    rt_uint32_t scl_fall_ns; /* time SCL signal takes to fall in ns; t(f) in the I2C specification */
    rt_uint32_t scl_int_delay_ns; /* time IP core additionally needs to setup SCL in ns */
    rt_uint32_t sda_fall_ns; /* time SDA signal takes to fall in ns; t(f) in the I2C specification */
    rt_uint32_t sda_hold_ns; /* time IP core additionally needs to hold SDA in ns */
    rt_uint32_t digital_filter_width_ns; /* width in ns of spikes on i2c lines that the IP core digital filter can filter out */
    rt_uint32_t analog_filter_cutoff_freq_hz; /* threshold frequency for the low pass IP core analog filter */
};

#ifdef RT_USING_OFW
rt_err_t i2c_timings_ofw_parse(struct rt_ofw_node *dev_np, struct i2c_timings *timings,
        rt_bool_t use_defaults);
#else
rt_inline rt_err_t i2c_timings_ofw_parse(struct rt_ofw_node *dev_np, struct i2c_timings *timings,
        rt_bool_t use_defaults)
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

void i2c_bus_scan_clients(struct rt_i2c_bus_device *bus);

#endif /* __I2C_DM_H__ */
