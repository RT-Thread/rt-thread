/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety      first version
 * 2015-04-27     ArdaFu     Port bsp from at91sam9260 to asm9260t
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_LED
#include "led.h"

void rt_led_thread_entry(void* parameter)
{
    rt_uint8_t cnt = 0;
    led_init();
    while(1)
    {
        /* light on leds for one second */
        rt_thread_delay(40);
        cnt++;
        if(cnt & 0x01)
            led_on(1);
        else
            led_off(1);
    }
}

static void start_led_thread(void)
{
    rt_thread_t led_thread;
    led_thread = rt_thread_create("led", rt_led_thread_entry, RT_NULL, 512,
                                  (RT_THREAD_PRIORITY_MAX / 8 * 5), 20);
    if(led_thread != RT_NULL)
        rt_thread_startup(led_thread);
}
#endif

int main()
{
#ifdef RT_USING_LED
    start_led_thread();
#endif
    return 0;
}
