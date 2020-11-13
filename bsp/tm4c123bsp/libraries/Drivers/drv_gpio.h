/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <stdint.h>
#include <rtthread.h>

#define _TM4C_PIN(index, gpioport, gpio_index)                           \
        {                                                                \
             index, GPIO_PORT##gpioport##_BASE, GPIO_PIN_##gpio_index    \
        }

#define _TM4C_PIN_RESERVE                                                \
        {                                                                \
             -1, 0, 0                                                    \
        }

/* TM4C123 GPIO driver*/
struct pin_index
{
    int index;
    uint32_t gpioBaseAddress;
    uint32_t pin;
};

extern int rt_hw_pin_init(void);

#endif  /*__DRV_GPIO_H__*/

/************************** end of file ******************/