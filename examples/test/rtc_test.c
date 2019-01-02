/*
 * File      : rtc_test.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * Date           Author         Notes
 * 2018-01-15     Liu2guang      the first version.
 */
#include <rtthread.h> 
#include <rtdevice.h> 

int rtc_test(void)
{    
    uint8_t i;
    time_t now;

    rt_err_t ret = RT_EOK; 
    
    rt_kprintf("[RTC Test]RTC Test Start...\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("[RTC Test]Set RTC 2017-04-01 12:30:46\n\n"); 
    rt_thread_delay(RT_TICK_PER_SECOND);
    
    ret = set_date(2017, 4, 1); 
    if(ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Date failed\n"); 
        return RT_ERROR;
    }
    
    rt_thread_delay(RT_TICK_PER_SECOND);
    
    ret = set_time(12, 30, 46); 
    if(ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Time failed\n"); 
        return RT_ERROR;
    }
    
    rt_thread_delay(RT_TICK_PER_SECOND);
    
    for(i = 0; i < 10; i++)
    {
        rt_kprintf("[RTC Test]Read RTC Date and Time: "); 
        now = time(RT_NULL);
        rt_kprintf("%s", ctime(&now));
        
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
    
    rt_kprintf("\n");

    return RT_EOK;
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(rtc_test, rtc drive test. e.g: rtc_test());
MSH_CMD_EXPORT(rtc_test, rtc drive test. e.g: rtc_test()); 
#endif
