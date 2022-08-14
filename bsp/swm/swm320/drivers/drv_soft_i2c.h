/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_SOFT_I2C_H__
#define __DRV_SOFT_I2C_H__

#include "board.h"

/* swm config class */
struct swm_soft_i2c_cfg
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *name;
};
/* swm i2c dirver class */
struct swm_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c2_bus;
};

#ifdef BSP_USING_I2C0
#define I2C0_BUS_CFG             \
    {                            \
        .scl = BSP_I2C0_SCL_PIN, \
        .sda = BSP_I2C0_SDA_PIN, \
        .name = "i2c0",          \
    }
#endif

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CFG             \
    {                            \
        .scl = BSP_I2C1_SCL_PIN, \
        .sda = BSP_I2C1_SDA_PIN, \
        .name = "i2c1",          \
    }
#endif

int rt_hw_i2c_init(void);

#endif /* __DRV_SOFT_I2C_H__ */
