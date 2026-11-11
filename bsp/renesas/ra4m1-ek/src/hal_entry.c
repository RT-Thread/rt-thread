/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-27     hywing       first version
 *
 */

#include <rtthread.h>
#include "hal_data.h"
#ifdef RT_USING_NANO
#include <drv_gpio.h>
#else
#include <rtdevice.h>
#endif /* RT_USING_NANO */

#define LED_PIN    BSP_IO_PORT_01_PIN_06 /* Onboard LED pins */
#define USER_BUTTON_PIN    "P105"

void on_button_clicked(void *args)
{
    rt_kprintf("On Button Clicked\n");
}

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    rt_pin_attach_irq(rt_pin_get(USER_BUTTON_PIN), PIN_IRQ_MODE_RISING, on_button_clicked, RT_NULL);
    rt_pin_irq_enable(rt_pin_get(USER_BUTTON_PIN), PIN_IRQ_ENABLE);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
