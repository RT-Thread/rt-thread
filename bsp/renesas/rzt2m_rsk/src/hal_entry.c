/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-03-11    Wangyuqiang   first version
 */

#include <rtthread.h>
#include "hal_data.h"
#include <board.h>
#ifdef RT_USING_NANO
#include <drv_gpio.h>
#else
#include <rtdevice.h>
#endif /* RT_USING_NANO */

#define LED_PIN    BSP_IO_PORT_19_PIN_6 /* Onboard LED pins */

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");
    rt_kprintf("==================================================\n");
    rt_kprintf("This is a iar project which mode is xspi0 execution!\n");
    rt_kprintf("==================================================\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
