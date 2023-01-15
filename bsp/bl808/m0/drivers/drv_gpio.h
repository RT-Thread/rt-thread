/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/01/5      chushicheng  first version
 *
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>
#include <rtdevice.h>
#include "drv_device.h"

#define GPIO_OUTPUT_MODE                         0
#define GPIO_OUTPUT_PP_MODE                      1
#define GPIO_OUTPUT_PD_MODE                      2
#define GPIO_INPUT_MODE                          3
#define GPIO_INPUT_PP_MODE                       4
#define GPIO_INPUT_PD_MODE                       5
#define GPIO_ASYNC_RISING_TRIGER_INT_MODE        6
#define GPIO_ASYNC_FALLING_TRIGER_INT_MODE       7
#define GPIO_ASYNC_HIGH_LEVEL_INT_MODE           8
#define GPIO_ASYNC_LOW_LEVEL_INT_MODE            9
#define GPIO_SYNC_RISING_TRIGER_INT_MODE         10
#define GPIO_SYNC_FALLING_TRIGER_INT_MODE        11
#define GPIO_SYNC_RISING_FALLING_TRIGER_INT_MODE 12
#define GPIO_SYNC_HIGH_LEVEL_INT_MODE            13
#define GPIO_SYNC_LOW_LEVEL_INT_MODE             14
#define GPIO_HZ_MODE                             15


int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */
