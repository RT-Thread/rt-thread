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
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#ifndef RT_USING_HEAP
/* if there is not enable heap, we should use static thread and stack. */
ALIGN(8)
static rt_uint8_t init_stack[512];
static struct rt_thread init_thread;
#endif

void rt_init_thread_entry(void* parameter)
{    
     /* initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
    
}
int rt_application_init()
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);
#else
    {
        
        rt_err_t result;

        tid = &init_thread;
        result = rt_thread_init(tid, "init", rt_init_thread_entry, RT_NULL,
                                init_stack, sizeof(init_stack), RT_THREAD_PRIORITY_MAX / 3, 20);
        RT_ASSERT(result == RT_EOK);
    }
#endif
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
