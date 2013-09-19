/*
 * File      : i2c-bit-ops.h
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
