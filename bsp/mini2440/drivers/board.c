/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-24     Bernard      first implementation
 * 2006-05-05     Bernard      add DATA_COUNT definition
 * 2006-10-05     Alsor.Z       for s3c2410x porting
 * 2007-11-20     Yi.Qiu	     add lcd,touch,console
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "led.h"

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
#endif

#if defined(__CC_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void*)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN      (((void*)&__bss_end) + 0x1000)
#endif

#define HEAP_END        (void*)(0x33F00000)


extern rt_uint32_t PCLK, FCLK, HCLK, UCLK;

extern void rt_hw_clock_init(void);
extern void rt_hw_mmu_init(void);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);

/**
 * This function will handle rtos timer
 */
static void rt_timer_handler(int vector, void *param)
{
	rt_tick_increase();
}

/**
 * This function will init timer4 for system ticks
 */
static  void rt_hw_timer_init(void)
 {
	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;
	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	TCNTB4 = (rt_int32_t)(PCLK / (4 *16* RT_TICK_PER_SECOND)) - 1;
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);
	/* install interrupt handler */
	rt_hw_interrupt_install(INTTIMER4, rt_timer_handler, RT_NULL, "tick");
	rt_hw_interrupt_umask(INTTIMER4);

    /* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
 }

/**
 * This function will init s3ceb2410 board
 */
void rt_hw_board_init(void)
{
	rt_hw_cpu_icache_enable();
	rt_hw_cpu_dcache_enable();

	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize the system clock */
	rt_hw_clock_init();

	/* Get the clock */
	rt_hw_get_clock();

	/* initialize led port */
	rt_hw_led_init();

	/* initialize mmu */
	rt_hw_mmu_init();

	/* initialize timer4 */
	rt_hw_timer_init();

	/* initialize system heap */
	rt_system_heap_init(HEAP_BEGIN, HEAP_END);

	rt_components_board_init();

#ifdef RT_USING_CONSOLE
	rt_console_set_device("uart0");
#endif

}
/*@}*/
