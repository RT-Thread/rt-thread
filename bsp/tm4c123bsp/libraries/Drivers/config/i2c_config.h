/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-20     wirano       first version
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__


#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_I2C0_CLK_100)
#define I2C0_CLK 100000
#elif defined(BSP_I2C0_CLK_400)
#define I2C0_CLK 400000
#endif

#if defined(BSP_I2C1_CLK_100)
#define I2C1_CLK 100000
#elif defined(BSP_I2C1_CLK_400)
#define I2C1_CLK 400000
#endif

#if defined(BSP_I2C2_CLK_100)
#define I2C2_CLK 100000
#elif defined(BSP_I2C2_CLK_400)
#define I2C2_CLK 400000
#endif

#if defined(BSP_I2C3_CLK_100)
#define I2C3_CLK 100000
#elif defined(BSP_I2C3_CLK_400)
#define I2C3_CLK 400000
#endif

#ifdef BSP_USING_I2C0
#ifndef I2C0_BUS_CONFIG
#define I2C0_BUS_CONFIG                             \
    {                                               \
        .base = I2C0_BASE,                          \
        .bus_name = "i2c0",                         \
        .clk_freq = I2C0_CLK,                       \
    }
#endif /* I2C0_BUS_CONFIG */
#endif /* BSP_USING_I2C0 */

#ifdef BSP_USING_I2C1
#ifndef I2C1_BUS_CONFIG
#define I2C1_BUS_CONFIG                             \
    {                                               \
        .base = I2C1_BASE,                          \
        .bus_name = "i2c1",                         \
        .clk_freq = I2C1_CLK,                       \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_I2C1 */

#ifdef BSP_USING_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                             \
    {                                               \
        .base = I2C2_BASE,                          \
        .bus_name = "i2c2",                         \
        .clk_freq = I2C2_CLK,                       \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_I2C2 */

#ifdef BSP_USING_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG                             \
    {                                               \
        .base = I2C3_BASE,                          \
        .bus_name = "i2c3",                         \
        .clk_freq = I2C3_CLK,                       \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_I2C3 */

#ifdef __cplusplus
}
#endif

#endif //__I2C_CONFIG_H__
