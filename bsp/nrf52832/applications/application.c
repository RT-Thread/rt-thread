/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-03-01     Yangfs       the first version
 * 2015-03-27     Bernard      code cleanup.
 */

/**
 * @addtogroup NRF52832
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

void rt_init_thread_entry(void* parameter)
{
    extern rt_err_t ble_init(void);

    ble_init();
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 1024,
                            RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}


/*@}*/
