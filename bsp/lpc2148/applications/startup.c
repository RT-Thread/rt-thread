/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-02-16     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "board.h"
#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
#include "dm9000.h"
#endif
#ifdef RT_USING_DFS
#include "sd.h"
#endif

/**
 * @addtogroup lpc2148
 */

/*@{*/

extern int  rt_application_init(void);
extern void rt_show_version(void);
#ifdef RT_USING_DEVICE
extern rt_err_t rt_hw_serial_init(void);
#endif

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#else
extern int __bss_end;
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

    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __CC_ARM
    rt_system_heap_init((void *)&Image$$RW_IRAM1$$ZI$$Limit, (void *)0x40008000);
#else
    /* init memory system */
    rt_system_heap_init((void *)&__bss_end, (void *)0x40008000);
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}

/*@}*/
