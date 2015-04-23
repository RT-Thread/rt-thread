/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
 * 2011-01-13     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <at91sam926x.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif
extern void rt_application_init(void);

/**
 * @addtogroup at91sam9260
 */

/*@{*/
#if defined(__CC_ARM)
extern int Image$$ER_ZI$$ZI$$Limit;
#define HEAP_BEGIN  (&Image$$ER_ZI$$ZI$$Limit)
#elif (defined (__GNUC__))
extern unsigned char __bss_end__;
#define HEAP_BEGIN  (&__bss_end__)
#elif (defined (__ICCARM__))
#pragma section=".noinit"
#define HEAP_BEGIN  (__section_end(".noinit"))
#endif

#define HEAP_END    (0x24000000)

/**
 * This function will startup RT-Thread RTOS.
 */
static void rtthread_startup(void)
{
    /* initialize board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();
    /* initialize system timer*/
    rt_system_timer_init();
    /* initialize application */
    rt_application_init();

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
#ifdef RT_USING_DEVICE
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif
	
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

/*@}*/
