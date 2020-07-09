/*
 * File      : blink.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2017, RT-Thread Development Team
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
 * 2017-11-8      Tangyuxin    first version
 */

#include <rtthread.h>

#include <board.h>
#include <drv_gpio.h>

void blink_task(void* param)
{
    rt_uint8_t cnt = 0;
    
    while(1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND / 4);

        if(cnt & 0x01)
            gpio_set_value(BLINK_LED0_PORT,BLINK_LED0_PIN,0);
        else
            gpio_set_value(BLINK_LED0_PORT,BLINK_LED0_PIN,1);

        if(cnt & 0x02)
            gpio_set_value(BLINK_LED1_PORT,BLINK_LED1_PIN,0);
        else
            gpio_set_value(BLINK_LED1_PORT,BLINK_LED1_PIN,1);

        if(cnt & 0x04)
            gpio_set_value(BLINK_LED2_PORT,BLINK_LED2_PIN,0);
        else
            gpio_set_value(BLINK_LED2_PORT,BLINK_LED2_PIN,1);

        if(cnt & 0x08)
            gpio_set_value(BLINK_LED3_PORT,BLINK_LED3_PIN,0);
        else
            gpio_set_value(BLINK_LED3_PORT,BLINK_LED3_PIN,1);

        cnt ++;
    }
}

int blink_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("blink",
                           blink_task, RT_NULL,
                           512,
                           RT_THREAD_PRIORITY_MAX - 2,
                           10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}
INIT_APP_EXPORT(blink_init);
