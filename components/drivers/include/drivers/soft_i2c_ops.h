/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-07-30     sp-cai        first version
 */

#ifndef __SOFT_I2C_OPS_H__
#define __SOFT_I2C_OPS_H__

#ifdef __cplusplus
extern "C" {
#endif

struct rt_soft_i2c_ops
{
    void(*set_scl)(const void *cfg, rt_uint8_t value);
    void(*set_sda)(const void *cfg, rt_uint8_t value);
    rt_int8_t(*get_scl)(const void *cfg);
    rt_int8_t(*get_sda)(const void *cfg);
    void (*delay)(rt_uint32_t t);
    rt_err_t(*control)(struct rt_i2c_bus_device *bus, int cmd, void *args);
};

struct rt_soft_i2c
{
    struct rt_i2c_bus_device        i2c_bus;
    const struct rt_soft_i2c_ops    *ops;
    const void                      *cfg;
    rt_uint32_t     timing_delay;       /* scl and sda line delay */
    rt_int32_t      timing_timeout;     /* in tick */
    #ifdef RT_I2C_DETAIL
    rt_ubase_t      state;              /* I2C communication state */
    rt_err_t        error;              /* I2C Error code */
    #endif  //RT_I2C_DETAIL
};
rt_err_t rt_soft_i2c_bus_device_register(struct rt_i2c_bus_device *bus,
        const char *bus_name);

#ifdef __cplusplus
}
#endif

#endif  //__SOFT_I2C_OPS_H__
