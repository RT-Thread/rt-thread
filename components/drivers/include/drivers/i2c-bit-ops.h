/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 */

#ifndef __I2C_BIT_OPS_H__
#define __I2C_BIT_OPS_H__

#ifdef __cplusplus
extern "C" {
#endif

struct rt_i2c_bit_ops
{
    void *data;            /* private data for lowlevel routines */
    void (*set_sda)(void *data, rt_int32_t state);
    void (*set_scl)(void *data, rt_int32_t state);
    rt_int32_t (*get_sda)(void *data);
    rt_int32_t (*get_scl)(void *data);

    void (*udelay)(rt_uint32_t us);

    rt_uint32_t delay_us;  /* scl and sda line delay */
    rt_uint32_t timeout;   /* in tick */
};

rt_err_t rt_i2c_bit_add_bus(struct rt_i2c_bus_device *bus,
                            const char               *bus_name);

#ifdef __cplusplus
}
#endif

#endif
