/** File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *

* Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 */

/**
 * @addtogroup QEMU
 */

/*@{*/

#include <rtthread.h>

ALIGN(RT_ALIGN_SIZE)
static char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void *parameter)
{
    unsigned int count=0;

    while (1)
    {
        /* led1 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led1 on,count : %d\r\n",count);
#endif
        count ++;
        /* sleep 0.5 second and switch to other thread */
        rt_thread_delay(RT_TICK_PER_SECOND / 2);

        /* led1 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led1 off\r\n");
#endif
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}

ALIGN(RT_ALIGN_SIZE)
static char thread_led2_stack[1024];
struct rt_thread thread_led2;
void rt_thread_entry_led2(void *parameter)
{
    unsigned int count=0;

    while (1)
    {
        /* led2 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led2 on,count : %d\r\n",count);
#endif
        count ++;
        rt_thread_delay(RT_TICK_PER_SECOND);

        /* led2 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led2 off\r\n");
#endif
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

/**
 * This function will be invoked to initalize user application when system
 * startup.
 */

int rt_application_init(void)
{
    // init led1 thread
    rt_thread_init(&thread_led1,
                   "led1",
                   rt_thread_entry_led1,
                   RT_NULL,
                   &thread_led1_stack[0],
                   sizeof(thread_led1_stack),11,5);
    rt_thread_startup(&thread_led1);

    // init led2 thread
    rt_thread_init(&thread_led2,
                   "led2",
                   rt_thread_entry_led2,
                   RT_NULL,
                   &thread_led2_stack[0],
                   sizeof(thread_led2_stack),12,5);
    rt_thread_startup(&thread_led2);

    return 0;
}

/*@}*/
