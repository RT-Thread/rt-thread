/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2012-02-13   mojingxian  first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "application.h"
#include "board.h"
#include "serial.h"
#include "finsh.h"

extern "asm" int rtt_heap_start;
extern "asm" int rtt_heap_end;
extern struct serial_device uart0;
extern struct rt_device uart0_device;

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
    rt_system_heap_init((void*)&rtt_heap_start, (void*)&rtt_heap_end);
#endif

#ifdef RT_USING_MODULE
    /* init module system*/
    rt_system_module_init();
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

#ifdef RT_USING_DEVICE
    /* register uart0 */
    rt_hw_serial_register(&uart0_device, "uart0",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart0);

    rt_console_set_device("uart0");
#endif

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    extern int finsh_system_init(void);
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device("uart0");
#endif
#endif

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

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
