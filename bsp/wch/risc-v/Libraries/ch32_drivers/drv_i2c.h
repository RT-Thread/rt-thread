/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-4-1       IceBear003   the first version
 */

#ifndef __DRV_I2C_H_
#define __DRV_I2C_H_

#include <rtthread.h>
#include <rtdevice.h>

struct i2c_bus_device
{
    struct rt_i2c_bus_device parent;
    I2C_TypeDef *periph;
};

struct i2c_config
{
    rt_uint32_t clock_speed;
    uint16_t duty_cycle;
    uint16_t own_address;
    uint8_t enable_ack;
    uint8_t is_7_bit_address;
};

struct i2c_config i2c_default_conf={5000, I2C_Mode_I2C, I2C_DutyCycle_2, 0, I2C_Ack_Disable, I2C_AcknowledgedAddress_7bit};

int rt_hw_i2c_init(struct i2c_config *config);

#endif