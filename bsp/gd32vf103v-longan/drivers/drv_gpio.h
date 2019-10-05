/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-05     wuhanstudio  first version
 */

#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#define __GD32_PIN(index, gpio, gpio_index)                                \
    {                                                                       \
        index, GPIO##gpio, GPIO_PIN_##gpio_index                            \
    }

/* GD32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t gpio;
    uint32_t pin;
};

int rt_hw_pin_init(void);

#endif
