/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


#ifndef __DRV_I2C_SOFT_H__
#define __DRV_I2C_SOFT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
struct hc32_soft_i2c_config
{
    rt_uint16_t scl_pin;
    rt_uint16_t sda_pin;
    const char  *bus_name;
};

struct hc32_soft_i2c
{
    struct rt_i2c_bit_ops    ops;
    struct rt_i2c_bus_device i2c_bus;
};

#ifdef BSP_USING_I2C1_SW
#define I2C1_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin  = BSP_I2C1_SCL_PIN,                       \
        .sda_pin  = BSP_I2C1_SDA_PIN,                       \
        .bus_name = "i2c1_sw",                              \
    }
#endif

#ifdef BSP_USING_I2C2_SW
#define I2C2_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin = BSP_I2C2_SCL_PIN,                        \
        .sda_pin = BSP_I2C2_SDA_PIN,                        \
        .bus_name = "i2c2_sw",                              \
    }
#endif

#ifdef BSP_USING_I2C3_SW
#define I2C3_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin = BSP_I2C3_SCL_PIN,                        \
        .sda_pin = BSP_I2C3_SDA_PIN,                        \
        .bus_name = "i2c3_sw",                              \
    }
#endif

#ifdef BSP_USING_I2C4_SW
#define I2C4_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin = BSP_I2C4_SCL_PIN,                        \
        .sda_pin = BSP_I2C4_SDA_PIN,                        \
        .bus_name = "i2c4_sw",                              \
    }
#endif

#ifdef BSP_USING_I2C5_SW
#define I2C5_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin = BSP_I2C5_SCL_PIN,                        \
        .sda_pin = BSP_I2C5_SDA_PIN,                        \
        .bus_name = "i2c5_sw",                              \
    }
#endif

#ifdef BSP_USING_I2C6_SW
#define I2C6_BUS_CONFIG                                     \
    {                                                       \
        .scl_pin = BSP_I2C6_SCL_PIN,                        \
        .sda_pin = BSP_I2C6_SDA_PIN,                        \
        .bus_name = "i2c6_sw",                              \
    }
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SOFT_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
