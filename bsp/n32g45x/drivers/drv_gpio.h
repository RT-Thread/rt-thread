/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date                    Notes
 * 2020-05-07              first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>
#include <rthw.h>
#include <rtdevice.h>

#define __N32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__N32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

#define __N32_PIN(index, gpio, gpio_index)                                \
    {                                                                      \
        index, GPIO##gpio, GPIO_PIN_##gpio_index,                         \
        GPIO##gpio##_PORT_SOURCE, GPIO_PIN_SOURCE##gpio_index             \
    }
//GPIOC_PORT_SOURCE
#define __N32_PIN_RESERVE                                                 \
    {                                                                      \
        -1, 0, 0, 0, 0                                                     \
    }

/* N32 GPIO driver */
struct pin_index
{
    int index;
    GPIO_Module *gpio;
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

