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
 * 2010-11-13     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <dm36x.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

extern void rt_hw_interrupt_init(void);
extern void rt_hw_board_init(void);
extern void rt_serial_init(void);
extern void rt_system_timer_init(void);
extern void rt_system_scheduler_init(void);
extern void rt_thread_idle_init(void);
extern void rt_hw_cpu_icache_enable(void);
extern void rt_show_version(void);
extern void rt_system_heap_init(void*, void*);
extern void rt_hw_finsh_init(void);
extern void rt_application_init(void);

/**
 * @addtogroup dm365
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
	rt_uint8_t _svc_stack_start[1024] SECTION(".nobss");
	extern unsigned char __bss_start;
	extern unsigned char __bss_end;
#endif

#ifdef RT_USING_FINSH
extern void finsh_system_init(void);
#endif

rt_inline void rt_swi(void)
{
	rt_kprintf("before swi\n");
	//asm ("swi 0x2");
	rt_kprintf("after swi\n");
}

#define	BREAKPOINT()			asm(".word 	0xe7ffdeff")
void breakpoint(void) 
{ 
	//#define BP 0xe7fddefe 
	//*(unsigned long *)breakinst = BP; 
	//__asm__ __volatile__(" 
	//.globl breakinst 
	//nop 
	//breakinst: nop 
	//nop 
	//nop 
	//"); 
	rt_kprintf("before breakpoint\n");
	BREAKPOINT();
	rt_kprintf("after breakpoint\n");
} 

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* enable cpu cache */
	//rt_hw_cpu_icache_enable();
	//rt_hw_cpu_dcache_enable();

	/* initialize hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();
	
	/* initialize tick */
	rt_system_tick_init();

	/* initialize kernel object */
	rt_system_object_init();

	/* initialize timer system */
	rt_system_timer_init();

	/* initialize heap memory system */
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$ER_ZI$$ZI$$Limit, (void*)0x88000000);
#else
	rt_system_heap_init((void*)&__bss_end, (void*)0x88000000);
#endif

#ifdef RT_USING_MODULE
	/* initialize module system*/
	rt_system_module_init();
#endif

	/* initialize scheduler system */
	rt_system_scheduler_init();

	/* initialize application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
#ifdef RT_USING_DEVICE
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif

	/* initialize system timer thread */
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
	rt_uint32_t UNUSED level;

	/* disable interrupt first */
	level = rt_hw_interrupt_disable();

	/* startup RT-Thread RTOS */
	rtthread_startup();

	return 0;
}

/*@}*/
