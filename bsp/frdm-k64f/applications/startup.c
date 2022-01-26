/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>

/**
 * @addtogroup k64
 */

/*@{*/

extern int  rt_application_init(void);
#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char* device);
#endif

#ifdef __CC_ARM
extern int Image$$RW_IRAM2$$ZI$$Limit;
#define K64_SRAM_BEGIN    (&Image$$RW_IRAM2$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define K64_SRAM_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define K64_SRAM_BEGIN    (&__bss_end)
#endif

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(rt_uint8_t* file, rt_uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}

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

    rt_system_heap_init((void*)K64_SRAM_BEGIN, (void*)K64_SRAM_END);

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device(FINSH_DEVICE_NAME);
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

/*@}*/
