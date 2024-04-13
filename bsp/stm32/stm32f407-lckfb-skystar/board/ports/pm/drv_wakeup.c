/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-07     Tanek        first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stm32F4xx.h>
#include "board.h"
#include "drv_gpio.h"

#define USER_WAKEUP_PIN       GET_PIN(C, 5)
#define DRV_WKUP_PIN_IRQ_MODE PIN_IRQ_MODE_FALLING

static void (*_wakeup_hook)(void);

void bsp_register_wakeup(void (*hook)(void))
{
    RT_ASSERT(hook != RT_NULL);

    _wakeup_hook = hook;
}

static void _wakeup_callback(void *args)
{
    extern void pm_wk_up();
    pm_wk_up();   /* wakeup from deep sleep */
    if (_wakeup_hook)
        _wakeup_hook();
}

static int rt_hw_wakeup_init(void)
{
    rt_pin_mode(USER_WAKEUP_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(USER_WAKEUP_PIN, DRV_WKUP_PIN_IRQ_MODE, _wakeup_callback, RT_NULL);
    rt_pin_irq_enable(USER_WAKEUP_PIN, 1);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_wakeup_init);
