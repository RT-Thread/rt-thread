/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup LPC4330
 */

/*@{*/

#include <rtthread.h>

#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif

#include "board_ngx_xplorer_18304330.h"

static void rt_init_thread_entry(void *parameter)
{
    Board_LED_Init();

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    while (1)
    {
        Board_LED_Set(0, 1);
        rt_thread_delay(50);
        Board_LED_Set(0, 0);
        rt_thread_delay(50);
    }
}

void rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry,
                           RT_NULL,
                           2048,
                           RT_THREAD_PRIORITY_MAX / 3,
                           20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
}

/*@}*/
