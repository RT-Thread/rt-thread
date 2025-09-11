/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2025-08-17     CYFS          first version
 */

#include <rtthread.h>
#include "hal_data.h"
#ifdef RT_USING_NANO
#include <drv_gpio.h>
#else
#include <rtdevice.h>
#endif /* RT_USING_NANO */

#define LED_PIN    BSP_IO_PORT_02_PIN_05 /* Onboard LED pins */

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");
    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
