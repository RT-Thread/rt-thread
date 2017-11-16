/*
 * File      : userled.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-09-20     heyuanjie     first version
 * 2012-09-29     lgnq          re-fromat the coding style
 */

#include <rtthread.h>
#include "drv_led.h"

#if defined(RT_USING_PM) && defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
#include <finsh.h>
#endif

#include <drivers/pm.h>

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
        rt_thread_delay(100);
        led_clear(0);
        rt_thread_delay(900);
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
#if defined(RT_USING_PM) && defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
MSH_CMD_EXPORT_ALIAS(rt_hw_userled_cleanup, led_cleanup, delete led task);
#endif


void rt_hw_userled_input(void)
{
    led_deinit();
}
#if defined(RT_USING_PM) && defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
MSH_CMD_EXPORT_ALIAS(rt_hw_userled_input, led_as_input, delete led task);
#endif
