/*
 * File      : userled.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * Date           Author        Notes
 * 2012-09-20     heyuanjie     first version
 * 2012-09-29     lgnq          re-fromat the coding style
 */

#include <rtthread.h>
#include "drv_led.h"

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
#include <finsh.h>
#endif

static rt_thread_t tid;

/**
 * This function is the entry of the led thread
 *
 * @param param parameter of the led thread
 */
static void rt_userled_thread_init(void *param)
{
    led_init();
	
    led_set(1);

    /* leds blink */
    while (1)
    {
        led_set(0);  		
        rt_thread_delay(RT_TICK_PER_SECOND / 100);
        led_clear(0);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

/**
 * This function will create and start a led thread
 */
void rt_hw_userled_init(void)
{
    tid = rt_thread_create("userled",
                           rt_userled_thread_init,
                           RT_NULL,
                           512,
                           8,
                           1);
    if (tid != RT_NULL)
        rt_thread_startup(tid); 
}

void rt_hw_userled_cleanup(void)
{
    rt_enter_critical();
    
    led_clear(0);
    
    if (tid != RT_NULL && tid->stat != RT_THREAD_CLOSE)
    {
        rt_kprintf("delete led thread success\n");
        rt_thread_delete(tid);
    }
    else
    {
        rt_kprintf("delete led thread faild\n");
        if (tid == RT_NULL)
            rt_kprintf("tid is null\n");
        else
            rt_kprintf("tid stat is %d\n", tid->stat);
    }
    
    rt_exit_critical();
}
#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
MSH_CMD_EXPORT_ALIAS(rt_hw_userled_cleanup, led_cleanup, delete led task);
#endif


void rt_hw_userled_input(void)
{
    led_deinit();
}
#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
MSH_CMD_EXPORT_ALIAS(rt_hw_userled_input, led_as_input, delete led task);
#endif
