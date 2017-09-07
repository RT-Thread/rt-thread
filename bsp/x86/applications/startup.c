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

#include "board.h"

extern void rt_hw_console_init(void);
extern void rt_hw_board_init(void);
extern int  rt_application_init(void);
//extern void rt_hw_interrupt_init(void);
//extern void rt_system_timer_init(void);
//extern void rt_system_scheduler_init(void);
//extern void rt_thread_idle_init(void);

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char *device);
#endif

extern unsigned char __bss_start[];
extern unsigned char __bss_end[];

/**
 * @addtogroup QEMU
 */

 /*@{*/

/* clear .bss */
void rt_hw_clear_bss(void)
{
    unsigned char *dst;
    dst = __bss_start;
    while (dst < __bss_end)
        *dst++ = 0;
}

/**
 * This function will startup RT-Thread RTOS
 */
void rtthread_startup(void)
{
    /* clear .bss */
    rt_hw_clear_bss();

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
    /* RAM 16M */
    rt_system_heap_init((void *)&__bss_end, (void *)(1024UL*1024*8));
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

/*@}*/
