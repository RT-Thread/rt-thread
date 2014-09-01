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
 * 2012-11-20     Bernard    the first version
 */

#include <rtthread.h>
#include <components.h>

#include <pthread.h>

void *test_task(void *parameter)
{
    int count = 0;

    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);
        rt_kprintf("count = %d\n", count ++);
    }

    return RT_NULL;
}

int rt_application_init()
{
    // pthread_t tid;

    /* do component initialization */
    rt_components_init();
#ifdef RT_USING_NEWLIB
    libc_system_init(RT_CONSOLE_DEVICE_NAME);
#endif

    // pthread_create(&tid, RT_NULL, test_task, RT_NULL);

    return 0;
}

