/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>
#include <rtthread.h>

extern int _ramfunc_end;
#define PIC32_SRAM_END (0xA0000000 + 1024UL*128) //795F512L 512K FLASH 128KB SRAM

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char* device);
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init((void*)&_ramfunc_end, (void*)PIC32_SRAM_END);
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
#ifdef RT_USING_DEVICE
    finsh_set_device("uart1");
#endif
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

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}

