/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

/**
 * @addtogroup MIMXRT1052
 */
/*@{*/

#include <stdio.h>

#include "fsl_common.h"
#include <board.h>
#include <rtthread.h>

#include "led.h"

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
}



ALIGN(RT_ALIGN_SIZE)
static char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    uint32_t led_index = 0;
    rt_hw_led_init();

    while (1)
    {

        rt_hw_led_on(led_index);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        rt_hw_led_off(led_index);
        rt_thread_delay(RT_TICK_PER_SECOND/2);

        led_index++;

        if (led_index == LED_MAX)
        {
            led_index = 0;
        }
    }
}

int rt_application_init()
{
    rt_thread_t init_thread;
    rt_err_t result;

     //------- init led1 thread
    result = rt_thread_init(&thread_led1,
                   "led_demo",
                   rt_thread_entry_led1,
                   RT_NULL,
                   &thread_led1_stack[0],
                   sizeof(thread_led1_stack),11,5);
    if (RT_EOK == result)
    {
        rt_thread_startup(&thread_led1);
    }

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
    {    rt_thread_startup(init_thread);
    }



    return 0;
}

/*@}*/
