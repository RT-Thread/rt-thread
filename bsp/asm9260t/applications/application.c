/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author		Notes
 * 2011-01-13     weety		 first version
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
