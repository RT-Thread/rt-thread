/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-27     BalanceTWK        first version
 */

#ifndef __DRV_GPIO__H__
#define __DRV_GPIO__H__

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

/* GD32VF GPIO driver */
struct pin_index
{
    int index;
    uint32_t gpio_periph;
    uint32_t pin;
};

#define __GD32VF_PIN(index, gpio, gpio_index)      \
    {                                              \
        index, GPIO##gpio, GPIO_PIN_##gpio_index   \
    }

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_gpio_init(void);

#endif /* __DRV_GPIO__H__ */

/******************* end of file *******************/
