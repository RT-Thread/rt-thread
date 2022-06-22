/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-11-06     balanceTWK        first version
 * 2020-04-15     hqfang            Modify for gd32vf103
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

#define __GD32_PORT(port)  GPIO##port

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__GD32_PORT(PORTx) - (rt_base_t)GPIOA)/(0x0400UL) )) + PIN)

#define __GD32_PIN(index, gpio, gpio_index)                                \
    {                                                                      \
        index, GPIO##gpio, GPIO_PIN_##gpio_index                           \
    }

#define __GD32_PIN_RESERVE                                                 \
    {                                                                      \
        -1, 0, 0                                                           \
    }

/* GD32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t gpio;
    uint32_t pin;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */

