/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-05     Bernard      the first version
 */
#ifndef GPIO_H__
#define GPIO_H__

#include <stdint.h>


struct stm32_hw_pin_userdata
{
    int pin;
    uint32_t mode;
};

#define PIN_USERDATA_END {-1,0}

extern struct stm32_hw_pin_userdata stm32_pins[];

int rt_hw_pin_init(void);

#endif
