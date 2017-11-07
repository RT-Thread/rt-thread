/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.fayfayspace.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 * 2006-10-10     Bernard      update to 0.2.2 version
 */

#include <rtthread.h>
#include <rthw.h>

extern void rt_hw_console_init(void);
extern void rt_hw_board_init(void);
extern int  rt_application_init(void);
extern void rt_hw_timer_init(void);
#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char *device);
#endif
#ifdef RT_USING_HEAP
    static unsigned char ucHeap[16*1024*1024];
#endif
/**
 * This function will startup RT-Thread RTOS
 */
void rtthread_startup(void)
{
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init the console */
    rt_hw_console_init();
    rt_console_set_device("console");

    /* init board */
    rt_hw_board_init();

    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

    /* init memory system */
#ifdef RT_USING_HEAP
	rt_system_heap_init((void *)ucHeap, &ucHeap[sizeof(ucHeap)]);
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device("console");
#endif

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

void rt_low_level_init(void)
{
	/* copy ISR vector */
	memcpy((void*)0x0000, (void*)0x8000, 64);
}

void rt_hw_board_init(void)
{
	rt_hw_timer_init();
}
void machine_reset(void)
{
	/* TODO */
	while(1);
}

void machine_shutdown(void)
{
	/* TODO */
	while(1);
}

/*@}*/
