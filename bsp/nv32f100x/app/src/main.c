/*
 * File      : _main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
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
 * 2015-11-19     Urey         the first version
 * 2017-09-20     Quintin.Z    modify for nv32
 */
#include "rtthread.h"
#include "finsh.h"

extern void led_thread_entry(void* parameter);

int main(void)
{
    rt_thread_t thread;

#ifdef  RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Create led thread */
    thread = rt_thread_create("led",
                              led_thread_entry, RT_NULL,
                              256, 20, 20);
    if(thread != RT_NULL)
        rt_thread_startup(thread);

    return 0;
}
