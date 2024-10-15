/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>

#include <sep4020.h>
#include <board.h>
#include <drivers/dev_serial.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <netif/ethernetif.h>
#endif

#define SDRAM_BASE  0x30000000

#ifdef __CC_ARM
extern int Image$$RW_RAM1$$ZI$$Limit;
#elif (defined (__GNUC__))
    extern unsigned char __bss_end;
#endif

extern void rt_application_init(void);
extern int finsh_system_init(void);
extern void sd_init(void);

void rtthread_startup()
{
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

    /* init heap memory system */
#ifdef __CC_ARM
    rt_system_heap_init((void*)&Image$$RW_RAM1$$ZI$$Limit, (void*)(SDRAM_BASE + 0x200000));
#else
    rt_system_heap_init(&__bss_end, (void*)0x34000000);
#endif


    /* init scheduler system */
    rt_system_scheduler_init();

#ifdef RT_USING_DEVICE

#ifdef RT_USING_DFS
    rt_hw_sdcard_init();
#endif

#ifdef RT_USING_LWIP
    eth_system_device_init();
    rt_hw_dm9161_init();
#endif
#endif

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device("uart0");
#endif
#endif

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;

}

int main()
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}



