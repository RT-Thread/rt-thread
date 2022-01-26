/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2011-12-17     nl1031       for MicroBlaze
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
extern int finsh_system_init(void);
#endif

extern void rt_hw_led_flash(void);


/*@{*/
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#endif

#ifdef __GNUC__
extern unsigned char __bss_start;
extern unsigned char __bss_end;
#endif

extern void rt_hw_interrupt_init(void);
extern int  rt_application_init(void);
#ifdef RT_USING_DEVICE
extern rt_err_t rt_hw_serial_init(void);
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
    rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)0x204000);
#elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void*)0x204000);
#else
    rt_system_heap_init((void*)&__bss_end, (void*)(&__bss_end+0x4000));

#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

#ifdef RT_USING_HOOK /* if the hook is used */
    /* set idle thread hook */
    rt_thread_idle_sethook(rt_hw_led_flash);
#endif

#ifdef RT_USING_DEVICE
    /* init hardware serial device */
    rt_hw_serial_init();
#endif

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device("uart1");
#endif
#endif

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main (void)
{
    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}

/*@}*/
