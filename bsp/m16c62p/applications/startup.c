/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-04-09     fify         for M16C
 */

#include <rthw.h>
#include <rtthread.h>

#include "iom16c62p.h"
#include "board.h"
#include "bsp.h"

extern void rt_hw_interrupt_init(void);
extern int  rt_application_init(void);
#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char* device);
#endif

#ifdef RT_USING_HEAP
#if (defined (__ICCM16C__))
#pragma section="DATA16_HEAP"
#elif (defined (__GNUC__))
extern unsigned char user_ram_end;
#endif
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __ICCM16C__
    rt_system_heap_init(__segment_begin("DATA16_HEAP"), __segment_end("DATA16_HEAP"));
#elif (defined (__GNUC__))
    rt_system_heap_init((void*)&user_ram_end, (void*)M16C62P_SRAM_END);
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device("uart0");
#endif

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init system setting */
    system_init();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
