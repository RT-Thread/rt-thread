/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-04     Yangxin      first implementation
 */


#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


int main()
{
    rt_kprintf("This is main thread!!\n");

    while(1)
    {
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
