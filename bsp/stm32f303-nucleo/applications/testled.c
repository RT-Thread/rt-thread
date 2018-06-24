/*
 * File      : testled.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * Date           Author       Notes
 * 2018-06-24     BC           first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>

void led_thread(void *p)
{
    rt_pin_mode(46, 0);  /* green LED */
    rt_pin_mode(75, 0);  /* red LED */
    rt_pin_mode(137, 0); /* blue LED */

    while (1)
    {
        rt_pin_write(75, 1);
        rt_kprintf("Red LED is on!\n");
        rt_thread_delay(20);
        rt_pin_write(75, 0);
        rt_kprintf("Red LED is off!\n");
        rt_thread_delay(20);

        rt_pin_write(137, 1);
        rt_kprintf("Blue LED is on!\n");
        rt_thread_delay(20);
        rt_pin_write(137, 0);
        rt_kprintf("Blue LED is off!\n");
        rt_thread_delay(20);

        rt_pin_write(46, 1);
        rt_kprintf("Green LED is on!\n");
        rt_thread_delay(20);
        rt_pin_write(46, 0);
        rt_kprintf("Green LED is off!\n");
        rt_thread_delay(20);
    }
}

int led_test(void)
{
    rt_thread_t thread = RT_NULL;

    thread = rt_thread_create("led", led_thread, RT_NULL, 256, 20, 10);
    if (thread != RT_NULL)
        rt_thread_startup(thread);

    return RT_EOK;
}

INIT_APP_EXPORT(led_test);
