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
 * 2006-09-23     Bernard      first version
 * 2006-10-05     Bernard      add .nobbs attribute for _svc_stack_start
 */

#include <rtthread.h>
#include <rthw.h>

#include <s3c44b0.h>
#include <board.h>

extern void rt_hw_interrupt_init(void);
extern void rt_serial_init(void);
extern void rt_hw_cpu_icache_enable(void);

/**
 * @addtogroup wh44b0
 */
/*@{*/

#ifdef __CC_ARM
extern int Image$$RW_RAM1$$ZI$$Limit;
#else
extern int __bss_end;
#endif

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
#endif
extern int  rt_application_init(void);

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* enable cpu cache */
	rt_hw_cpu_icache_enable();

	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();

	/* init hardware serial */
	rt_serial_init();

	rt_show_version();

	/* init timer system */
	rt_system_timer_init();

	/* init memory system */
#ifdef RT_USING_HEAP
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$RW_RAM1$$ZI$$Limit, (void*)0xD000000);
#else
	rt_system_heap_init((void*)&__bss_end, (void*)0xD000000);
#endif
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

#ifdef RT_USING_HOOK
	/* set idle thread hook */
	rt_thread_idle_sethook(rt_hw_led_flash);
#endif

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init the finsh input */
	rt_hw_finsh_init();

	/* init finsh */
	finsh_system_init();
#endif

	/* init idle thread */
	rt_thread_idle_init();

	/* unmask interrupt */
	rt_hw_interrupt_umask(INT_GLOBAL);

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

int main(void)
{
	/* invoke rtthread startup */
	rtthread_startup();
}

/*@}*/
