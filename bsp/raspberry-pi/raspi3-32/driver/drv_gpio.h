/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "interrupt.h"
#include "board.h"

#define GPIO_IRQ_NUM 3

#define IRQ_GPIO0               49
#define IRQ_GPIO1               50
#define IRQ_GPIO2               51
#define IRQ_GPIO3               52

struct gpio_irq_def
{
    void  *irq_arg[32];
    void (*irq_cb[32])(void *param);
    rt_uint8_t irq_type[32];
};

enum gpio_irq_clock
{
    GPIO_IRQ_LOSC_32KHZ = 0,
    GPIO_IRQ_HOSC_24MHZ
};

int rt_hw_gpio_init(void);

#endif /* __DRV_GPIO_H__ */
