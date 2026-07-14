/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-06-07     dirtwillfly    first version for NS800
 */
#ifndef __I2C_HARD_CONFIG_H__
#define __I2C_HARD_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* I2C1 default GPIO configuration */
/* GPIO_0 (SDA) -> GPIOA, GPIO_PIN_0 */
/* GPIO_1 (SCL) -> GPIOA, GPIO_PIN_1 */
#ifndef BSP_I2C1_SCL_PIN_NUM
#define BSP_I2C1_SCL_PIN_NUM     1U
#endif
#ifndef BSP_I2C1_SDA_PIN_NUM
#define BSP_I2C1_SDA_PIN_NUM     0U
#endif
#ifndef BSP_I2C1_SCL_PORT
#define BSP_I2C1_SCL_PORT        GPIOA
#endif
#ifndef BSP_I2C1_SDA_PORT
#define BSP_I2C1_SDA_PORT        GPIOA
#endif
#ifndef BSP_I2C1_SCL_PIN
#define BSP_I2C1_SCL_PIN         GPIO_PIN_1
#endif
#ifndef BSP_I2C1_SDA_PIN
#define BSP_I2C1_SDA_PIN         GPIO_PIN_0
#endif
#ifndef BSP_I2C1_SCL_ALT_FUNC
#define BSP_I2C1_SCL_ALT_FUNC    ALT6_FUNCTION
#endif
#ifndef BSP_I2C1_SDA_ALT_FUNC
#define BSP_I2C1_SDA_ALT_FUNC    ALT6_FUNCTION
#endif

/* I2C2 default GPIO configuration */
/* GPIO_34 (SDA) -> GPIOB, GPIO_PIN_2 */
/* GPIO_35 (SCL) -> GPIOB, GPIO_PIN_3 */
#ifndef BSP_I2C2_SCL_PIN_NUM
#define BSP_I2C2_SCL_PIN_NUM     35U
#endif
#ifndef BSP_I2C2_SDA_PIN_NUM
#define BSP_I2C2_SDA_PIN_NUM     34U
#endif
#ifndef BSP_I2C2_SCL_PORT
#define BSP_I2C2_SCL_PORT        GPIOB
#endif
#ifndef BSP_I2C2_SDA_PORT
#define BSP_I2C2_SDA_PORT        GPIOB
#endif
#ifndef BSP_I2C2_SCL_PIN
#define BSP_I2C2_SCL_PIN         GPIO_PIN_3
#endif
#ifndef BSP_I2C2_SDA_PIN
#define BSP_I2C2_SDA_PIN         GPIO_PIN_2
#endif
#ifndef BSP_I2C2_SCL_ALT_FUNC
#define BSP_I2C2_SCL_ALT_FUNC    ALT6_FUNCTION
#endif
#ifndef BSP_I2C2_SDA_ALT_FUNC
#define BSP_I2C2_SDA_ALT_FUNC    ALT6_FUNCTION
#endif

#ifdef BSP_USING_HARD_I2C1
#ifndef BSP_I2C1_BAUDRATE
#define BSP_I2C1_BAUDRATE    100000
#endif

#ifndef I2C1_BUS_CONFIG
#define I2C1_BUS_CONFIG                                 \
    {                                                   \
        .name = "hwi2c1",                               \
        .Instance = I2C1,                               \
        .baudrate = BSP_I2C1_BAUDRATE,                  \
        .timeout = 1000,                                \
        .irq_type = I2C1_MST_IRQn,                      \
        .scl_pin_num = BSP_I2C1_SCL_PIN_NUM,            \
        .sda_pin_num = BSP_I2C1_SDA_PIN_NUM,            \
        .scl_port = BSP_I2C1_SCL_PORT,                  \
        .sda_port = BSP_I2C1_SDA_PORT,                  \
        .scl_pin = BSP_I2C1_SCL_PIN,                    \
        .sda_pin = BSP_I2C1_SDA_PIN,                    \
        .scl_alt_func = BSP_I2C1_SCL_ALT_FUNC,          \
        .sda_alt_func = BSP_I2C1_SDA_ALT_FUNC,          \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C1 */

#ifdef BSP_USING_HARD_I2C2
#ifndef BSP_I2C2_BAUDRATE
#define BSP_I2C2_BAUDRATE    100000
#endif

#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG                                 \
    {                                                   \
        .name = "hwi2c2",                               \
        .Instance = I2C2,                               \
        .baudrate = BSP_I2C2_BAUDRATE,                  \
        .timeout = 1000,                                \
        .irq_type = I2C2_MST_IRQn,                      \
        .scl_pin_num = BSP_I2C2_SCL_PIN_NUM,            \
        .sda_pin_num = BSP_I2C2_SDA_PIN_NUM,            \
        .scl_port = BSP_I2C2_SCL_PORT,                  \
        .sda_port = BSP_I2C2_SDA_PORT,                  \
        .scl_pin = BSP_I2C2_SCL_PIN,                    \
        .sda_pin = BSP_I2C2_SDA_PIN,                    \
        .scl_alt_func = BSP_I2C2_SCL_ALT_FUNC,          \
        .sda_alt_func = BSP_I2C2_SDA_ALT_FUNC,          \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C2 */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_HARD_CONFIG_H__ */

