/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>
#include <rtthread.h>

extern int _ramfunc_end;
#define PIC32_SRAM_END (0xA0000000+0x8000) //795F512L 512KB

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
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

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init((void*)&_ramfunc_end, (void*)PIC32_SRAM_END);
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

//#ifdef RT_USING_DEVICE
//	/* register uart0 */
//	rt_hw_serial_register(&uart0_device, "uart0",
//		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
//		&uart0);
//
//	/* register uart2, used for RTI debug */
//	rt_hw_serial_register(&uart2_device, "uart2",
//		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
//		&uart2);
//
//#ifdef RT_USING_DFS
//#ifdef RT_USING_DFS_UFFS
//	rt_hw_nand_init();
//#endif
//#endif
//
//	/*init all registed devices */
//	rt_device_init_all();
//#endif

	/* init application */
	rt_application_init();

//#ifdef RT_USING_FINSH
//	/* init finsh */
//	finsh_system_init();
//#ifdef RT_USING_DEVICE
//	finsh_set_device("uart2");
//#endif
//#endif

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

