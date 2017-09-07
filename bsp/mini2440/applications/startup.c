/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-26     Bernard      first implementation
 * 2006-05-05     Bernard      add two test thread
 * 2006-08-10     Bernard      use rt_show_version to display version information
 * 2008-07-14     Bernard      modify the heap memory init parameter
 */

#include <rthw.h>
#include <rtthread.h>

#include <s3c24x0.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

extern void rt_hw_interrupt_init(void);
extern void rt_hw_board_init(void);
extern void rt_hw_rtc_init(void);
extern void rt_serial_init(void);
extern void rt_system_timer_init(void);
extern void rt_system_scheduler_init(void);
extern void rt_thread_idle_init(void);
extern void rt_hw_cpu_icache_enable(void);
extern void rt_show_version(void);
extern void rt_system_heap_init(void*, void*);
extern void rt_hw_finsh_init(void);
extern void rt_application_init(void);

extern struct serial_device uart0;
extern struct rt_device uart0_device;
extern struct serial_device uart2;
extern struct rt_device uart2_device;

/**
 * @addtogroup mini2440
 */

/*@{*/
#if defined(__CC_ARM)
	extern int Image$$ER_ZI$$ZI$$Base;
	extern int Image$$ER_ZI$$ZI$$Length;
	extern int Image$$ER_ZI$$ZI$$Limit;
#elif (defined (__GNUC__))
	rt_uint8_t _irq_stack_start[1024];
	rt_uint8_t _fiq_stack_start[1024];
	rt_uint8_t _undefined_stack_start[512];
	rt_uint8_t _abort_stack_start[512];
	rt_uint8_t _svc_stack_start[4096] SECTION(".nobss");
	extern unsigned char __bss_start;
	extern unsigned char __bss_end;
#endif

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* enable cpu cache */
	rt_hw_cpu_icache_enable();
	rt_hw_cpu_dcache_enable();

	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init tick */
	rt_system_tick_init();

	/* init kernel object */
	rt_system_object_init();

	/* init timer system */
	rt_system_timer_init();

	/* init heap memory system */
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$ER_ZI$$ZI$$Limit, (void*)0x33F00000);
#else
	rt_system_heap_init((void*)&__bss_end, (void*)0x33F00000);
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

	/* register uart2, used for RTI debug */
	rt_hw_serial_register(&uart2_device, "uart2",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart2);

#ifdef RT_USING_DFS
	rt_hw_sdcard_init();
#ifdef RT_USING_DFS_UFFS
	rt_hw_nand_init();
#endif
#endif

	/* rtc init */
	rt_hw_rtc_init();
#endif

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
#ifdef RT_USING_DEVICE
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

/*@}*/
