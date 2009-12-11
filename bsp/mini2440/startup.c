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
 * 2006-02-26     Bernard      first implementation
 * 2006-05-05     Bernard      add two test thread
 * 2006-08-10     Bernard      use rt_show_version to display version information
 * 2008-07-14     Bernard      modify the heap memory init parameter
 */

#include <rtthread.h>
#include <rthw.h>

#include <s3c2410.h>

rt_uint8_t _irq_stack_start[1024];
rt_uint8_t _fiq_stack_start[1024];
rt_uint8_t _undefined_stack_start[512];
rt_uint8_t _abort_stack_start[512];
rt_uint8_t _svc_stack_start[1024] SECTION(".nobss");

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
extern int rtl8019_device_register(char*);

extern struct serial_device uart0;
extern struct rt_device uart0_device;

/**
 * @addtogroup s3ceb2410
 */

/*@{*/

#ifdef __CC_ARM
	extern rt_uint8_t* __bss_start;
	extern rt_uint8_t* __bss_end;
#else
	extern rt_uint8_t __bss_start;
	extern rt_uint8_t __bss_end;
#endif

/*
 * 4 LEDs on S3CEB2410 : GPF4~GPF7
 */
void led_set(rt_uint32_t led)
{
	GPFDAT = led;
}

/* led loop */
void led_flash(void)
{
	rt_uint32_t i;

	/* change the pin mux to enable the LED output */
	GPFCON = 0x5500;

	led_set(1 << 4);
	for ( i = 0; i < 2000000; i++);

	led_set(1 << 5);
	for ( i = 0; i < 2000000; i++);

	led_set(1 << 6);
	for ( i = 0; i < 2000000; i++);

	led_set(1 << 17);
	for ( i = 0; i < 2000000; i++);
}

#ifdef RT_USING_FINSH
extern void finsh_system_init(void);
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
	rt_system_heap_init((void*)__bss_end, (void*)0x34000000);
#else
	rt_system_heap_init(&__bss_end, (void*)0x34000000);
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

	/* set idle thread hook */
	rt_thread_idle_sethook(led_flash);

#ifdef RT_USING_DEVICE
	/* register uart1 */
	rt_hw_serial_register(&uart0_device, "uart0", 
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart0);		
	rt_hw_sdcard_init();
#ifdef RT_USING_LWIP
	/* init ethernet task */
	eth_system_device_init();

	/* init rtl8019 device */
	rt_rtl8019_device_register("e0");
#endif

	/*init all registed devices */
	rt_device_init_all();
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

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

/*@}*/
