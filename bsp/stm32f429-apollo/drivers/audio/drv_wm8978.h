/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-14     ZeroFree     first implementation
 */
#ifndef __DRV_WM8978_H__
#define __DRV_WM8978_H__

#include <rtthread.h>
#include <rtdevice.h>

int wm8978_init(struct rt_i2c_bus_device *dev);
int wm8978_set_volume(struct rt_i2c_bus_device *dev, int vol);

#endif
