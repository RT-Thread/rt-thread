/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-20     wirano       first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__


#include <stdint.h>
#include <rtdevice.h>
#include <rthw.h>


struct tm4c123_i2c
{
    struct rt_i2c_bus_device bus;
    uint32_t base;
    char *bus_name;
    uint32_t clk_freq;
};

int rt_hw_i2c_init(void);

#endif /* __DRV_I2C_H__ */

