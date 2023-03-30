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

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include "bflb_gpio.h"

#define GPIO_MAX            (GPIO_PIN_45 + 1)
int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */
