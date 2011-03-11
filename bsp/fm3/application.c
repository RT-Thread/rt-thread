/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      the first version
 */

/**
 * @addtogroup FM3
 */
/*@{*/

#include <rtthread.h>
#include "board.h"
#include "led.h"

#ifdef RT_USING_RTGUI
#include "key.h"
#include "adc.h"
#include "lcd.h"
#include "cpuusage.h"
#include <rtgui/rtgui.h>
extern void rtgui_startup();
#endif

void rt_init_thread_entry(void *parameter)
{
	rt_hw_led_init();

#ifdef RT_USING_RTGUI
	rt_hw_key_init();
	rt_hw_adc_init();
	rt_hw_lcd_init();      
	rt_hw_cpu_init();
    
	/* re-init device driver */
	rt_device_init_all();

	/* startup rtgui */
	rtgui_startup();
#endif
}

int rt_application_init()
{
    rt_thread_t init_thread;

    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 1024, 21, 20);
    if(init_thread != RT_NULL)
        rt_thread_startup(init_thread);
    
    return 0;
}

/*@}*/
