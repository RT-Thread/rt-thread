/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 * 2011-08-08     lgnq         modified for Loongson LS1B
 */

#include <rtthread.h>
#include <ls1b.h>

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
extern void rt_hw_dc_init(void);
#endif

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_RTGUI
    {
        rt_device_t dc;

        /* init Display Controller */
        rt_hw_dc_init();

        /* find Display Controller device */
        dc = rt_device_find("dc");

        /* set Display Controller device as rtgui graphic driver */
        rtgui_graphic_set_device(dc);
    }
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
}

int main(void)
{
    rt_thread_t tid;

    /* create initialization thread */
    tid = rt_thread_create("init",
                            rt_init_thread_entry, RT_NULL,
                            4096, 8, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
