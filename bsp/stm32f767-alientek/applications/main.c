/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup.
 */

#include <rtthread.h>

void thread1(void* param)
{
    while(1);
}
    
void thread2(void* param)
{
    while(1);
}

int main(void)
{
    rt_thread_t tid; 
    /* put user application code here */
    tid = rt_thread_create("thread1", thread1, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    RT_ASSERT(tid != RT_NULL);
    rt_thread_startup(tid);
    tid = rt_thread_create("thread2", thread2, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    RT_ASSERT(tid != RT_NULL);
    rt_thread_startup(tid);
    while(1);
    return 0;
}

