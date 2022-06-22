/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-03-04     Magicoe      for LPC17xx
 */

#include <rthw.h>
#include <rtthread.h>

#include "LPC177x_8x.h"
#include "board.h"

extern int  rt_application_init(void);

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end;
#endif

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* initialize board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

#ifdef RT_USING_HEAP
    /* initialize memory system */
    #ifdef __CC_ARM
        rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)(0x10000000 + 1024*64));
    #elif __ICCARM__
        rt_system_heap_init(__segment_end("HEAP"), (void*)(0x10000000 + 1024*64));
    #else
        rt_system_heap_init((void*)&__bss_end, (void*)(0x10000000 + 1024*64));
    #endif
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    /* initialize application */
    rt_application_init();

    /* initialize timer */
    rt_system_timer_init();

    /* initialize timer thread */
    rt_system_timer_thread_init();

    /* initialize idle thread */
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
