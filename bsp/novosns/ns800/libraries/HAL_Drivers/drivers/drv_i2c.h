/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-07     dirtwillfly    first version for NS800
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include "drv_config.h"
#include "board.h"
#include "rtdevice.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BSP_I2C_CTRL_SET_TIMING 0x40

struct ns800_i2c_config
{
    const char      *name;
    I2C_TypeDef     *Instance;
    uint32_t        baudrate;
    uint32_t        timeout;
    IRQn_Type       irq_type;
    uint32_t        scl_pin_num;     /* SCL pin number for get_pin_info */
    uint32_t        sda_pin_num;     /* SDA pin number for get_pin_info */
    GPIO_TypeDef    *scl_port;       /* SCL GPIO port */
    GPIO_TypeDef    *sda_port;       /* SDA GPIO port */
    GPIO_PinNum     scl_pin;         /* SCL pin in the port */
    GPIO_PinNum     sda_pin;         /* SDA pin in the port */
    GPIO_AltFunc    scl_alt_func;    /* SCL alternate function */
    GPIO_AltFunc    sda_alt_func;    /* SDA alternate function */
};

struct ns800_i2c
{
    struct ns800_i2c_config    *config;
    struct rt_i2c_bus_device    i2c_bus;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_I2C_H__ */

