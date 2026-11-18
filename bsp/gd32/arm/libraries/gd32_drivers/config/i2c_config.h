/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_HARD_I2C0
#ifndef BSP_I2C0_SCL_PIN
#define BSP_I2C0_SCL_PIN    "PB8"
#define BSP_I2C0_SDA_PIN    "PB9"
#define BSP_I2C0_AFIO       "AF4"
#endif
#ifndef I2C0_CONFIG
#define I2C0_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C0,                                      \
        .per_clk = RCU_I2C0,                                     \
        .scl_pin_name = BSP_I2C0_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C0_SDA_PIN,                        \
        .alternate = BSP_I2C0_AFIO,                              \
        .i2c_bus = &i2c0,                                        \
        .device_name = "hwi2c0",                                \
    }
#endif
#endif

#ifdef BSP_USING_HARD_I2C1
#ifndef BSP_I2C1_SCL_PIN
#define BSP_I2C1_SCL_PIN    "PH4"
#define BSP_I2C1_SDA_PIN    "PB11"
#define BSP_I2C1_AFIO       "AF4"
#endif
#ifndef I2C1_CONFIG
#define I2C1_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C1,                                      \
        .per_clk = RCU_I2C1,                                     \
        .scl_pin_name = BSP_I2C1_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C1_SDA_PIN,                        \
        .alternate = BSP_I2C1_AFIO,                              \
        .i2c_bus = &i2c1,                                        \
        .device_name = "hwi2c1",                                \
    }
#endif
#endif

#ifdef BSP_USING_HARD_I2C2
#ifndef BSP_I2C2_SCL_PIN
#define BSP_I2C2_SCL_PIN    "PA8"
#define BSP_I2C2_SDA_PIN    "PC9"
#define BSP_I2C2_AFIO       "AF4"
#endif
#ifndef I2C2_CONFIG
#define I2C2_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C2,                                      \
        .per_clk = RCU_I2C2,                                     \
        .scl_pin_name = BSP_I2C2_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C2_SDA_PIN,                        \
        .alternate = BSP_I2C2_AFIO,                              \
        .i2c_bus = &i2c2,                                        \
        .device_name = "hwi2c2",                                \
    }
#endif
#endif

#ifdef BSP_USING_HARD_I2C3
#ifndef BSP_I2C3_SCL_PIN
#define BSP_I2C3_SCL_PIN    "PF14"
#define BSP_I2C3_SDA_PIN    "PF15"
#define BSP_I2C3_AFIO       "AF4"
#endif
#ifndef I2C3_CONFIG
#define I2C3_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C3,                                      \
        .per_clk = RCU_I2C3,                                     \
        .scl_pin_name = BSP_I2C3_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C3_SDA_PIN,                        \
        .alternate = BSP_I2C3_AFIO,                              \
        .i2c_bus = &i2c3,                                        \
        .device_name = "hwi2c3",                                \
    }
#endif
#endif

#ifdef BSP_USING_HARD_I2C4
#ifndef BSP_I2C4_SCL_PIN
#define BSP_I2C4_SCL_PIN    "PG7"
#define BSP_I2C4_SDA_PIN    "PG8"
#define BSP_I2C4_AFIO       "AF6"
#endif
#ifndef I2C4_CONFIG
#define I2C4_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C4,                                      \
        .per_clk = RCU_I2C4,                                     \
        .scl_pin_name = BSP_I2C4_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C4_SDA_PIN,                        \
        .alternate = BSP_I2C4_AFIO,                              \
        .i2c_bus = &i2c4,                                        \
        .device_name = "hwi2c4",                                \
    }
#endif
#endif

#ifdef BSP_USING_HARD_I2C5
#ifndef BSP_I2C5_SCL_PIN
#define BSP_I2C5_SCL_PIN    "PF11"
#define BSP_I2C5_SDA_PIN    "PF12"
#define BSP_I2C5_AFIO       "AF4"
#endif
#ifndef I2C5_CONFIG
#define I2C5_CONFIG                                               \
    {                                                             \
        .i2c_periph = I2C5,                                      \
        .per_clk = RCU_I2C5,                                     \
        .scl_pin_name = BSP_I2C5_SCL_PIN,                        \
        .sda_pin_name = BSP_I2C5_SDA_PIN,                        \
        .alternate = BSP_I2C5_AFIO,                              \
        .i2c_bus = &i2c5,                                        \
        .device_name = "hwi2c5",                                \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __I2C_CONFIG_H__ */
