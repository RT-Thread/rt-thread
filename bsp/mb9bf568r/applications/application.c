/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-24     Bernard      the first version
 */

/**
 * @addtogroup FM4
 */
/*@{*/

#include <rtthread.h>
#include "board.h"

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif


    //finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);


    /**< init led device */
    {
        extern void rt_led_hw_init(void);
        rt_led_hw_init();
    }

}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, 8, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

/*@}*/
