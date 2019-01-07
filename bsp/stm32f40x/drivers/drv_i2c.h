/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-12-30     ppxiasky     Change to F4 Standard Library for simulation i2c 
 * 2019-01-04     ppxiasky     add hardware i2c 
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "stm32f4xx.h"

int hw_i2c_init(void);

#endif
