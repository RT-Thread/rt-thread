/*
 * File      : startup.c
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_sram.h"

extern int  rt_application_init(void);

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
#ifdef BSP_DRV_SDRAM
    rt_kprintf("      heap: [0x%08x - 0x%08x]\n", LPC_EXT_SDRAM_BEGIN, LPC_EXT_SDRAM_END);
    rt_system_heap_init((void *)LPC_EXT_SDRAM_BEGIN, (void *)LPC_EXT_SDRAM_END);
    sram_init();
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();
	
    /* initialize system timer*/
    rt_system_timer_init();
	
    /* initialize application */
    rt_application_init();

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
