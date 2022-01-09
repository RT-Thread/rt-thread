/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#ifdef RT_USING_LWIP
    #include <lwip/sys.h>
    #include <netif/ethernetif.h>
#endif

/**
 * @addtogroup LM3S
 */

extern void rt_hw_serial_init(void);

/*@{*/
#ifdef RT_USING_FINSH
    extern int finsh_system_init(void);
    extern void finsh_set_device(const char *device);
#endif

extern int rt_application_init(void);
extern void rt_hw_sdcard_init(void);
extern int rt_hw_luminaryif_init(void);

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
void assert_failed(u8 *file, u32 line)
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
    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __CC_ARM
    rt_system_heap_init((void *)&Image$$RW_IRAM1$$ZI$$Limit, (void *)LM3S_SRAM_END);
#elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void *)LM3S_SRAM_END);
#else
    /* init memory system */
    rt_system_heap_init((void *)&__bss_end, (void *)LM3S_SRAM_END);
#endif
#endif

#ifdef RT_USING_MODULE
    /* init module system */
    rt_system_module_init();
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

#ifdef RT_USING_LWIP
    eth_system_device_init();

    /* register ethernetif device */
    rt_hw_luminaryif_init();
#endif

    /* init hardware serial device */
    rt_hw_serial_init();
#ifdef RT_USING_DFS
    /* init sd card device */
    rt_hw_sdcard_init();
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

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();
    rtthread_startup();

    return 0;
}

/*@}*/
