/*
 * File      : startup.c
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

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#define A_K0BASE		0x80000000

/**
 * @addtogroup Loongson LS1B
 */

/*@{*/

extern unsigned char __bss_end;

extern int rt_application_init(void);

extern void tlb_refill_exception(void);
extern void general_exception(void);
extern void irq_exception(void);

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init cache */
    rt_hw_cache_init();
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* copy vector */
    rt_memcpy((void *)A_K0BASE, tlb_refill_exception, 0x20);
    rt_memcpy((void *)(A_K0BASE + 0x180), general_exception, 0x20);
    rt_memcpy((void *)(A_K0BASE + 0x200), irq_exception, 0x20);

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)&__bss_end, (void*)RT_HW_HEAP_END);
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* initialize timer */
    rt_system_timer_init();

    /* initialize timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* init application */
    rt_application_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return;
}

/*@}*/
