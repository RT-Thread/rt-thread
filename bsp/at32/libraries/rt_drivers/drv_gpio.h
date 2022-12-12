/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-05-16     shelton           first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rthw.h>
#include <rtdevice.h>
#include "drv_common.h"

#define __AT32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__AT32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

#define __AT32_PIN(index, gpio, gpio_index)                                \
    {                                                                      \
        index, GPIO##gpio, GPIO_Pins_##gpio_index,                         \
        GPIO_PortSourceGPIO##gpio, GPIO_PinsSource##gpio_index             \
    }

#define __AT32_PIN_RESERVE                                                 \
    {                                                                      \
        -1, 0, 0, 0, 0                                                     \
    }

/* AT32 GPIO driver */
struct pin_index
{
    int index;
    gpio_type *gpio_x;
    rt_uint32_t pin;
    rt_uint32_t portsource;
    rt_uint32_t pinsource;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    rt_uint16_t lineno;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */

