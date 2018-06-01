/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2018-03-01     flyingcys    add realtek ameba
 */

#include <rthw.h>
#include <rtthread.h>

/**
 * @addtogroup ameba
 */

/*@{*/

int main(void)
{
    rt_kprintf("Hello RT-Thread!\n");
    
#ifdef RT_USING_LWIP
    wifi_start();
#endif

    return 0;
}

/*@}*/
