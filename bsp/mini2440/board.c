/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-24     Bernard      first implementation
 * 2006-05-05     Bernard      add DATA_COUNT definition
 * 2006-10-05     Alsor.Z      for s3c2410x porting
 * 2007-11-20     Yi.Qiu	     add lcd,touch,console
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"

/**
 * @addtogroup s3ceb2410
 */
/*@{*/

extern rt_uint32_t PCLK, FCLK, HCLK, UCLK;
extern rt_uint8_t asc16_font[];
extern rt_uint16_t _rt_hw_framebuffer[];

extern void rt_hw_lcd_init(void);
extern void rt_hw_mmu_init(void);
extern void rt_hw_touch_init(void);

extern void rt_kbd_init(void);
extern void rt_console_init(rt_uint8_t*, rt_uint8_t*, rt_uint8_t);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);

static rt_uint32_t timer_load_val = 0;

#define UART0	((struct uartport *)U0BASE)	
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 = 
{
	UART0,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;

/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector)
{
	/* reset TDATA0 */
	TCNTB4 = timer_load_val;

	rt_tick_increase();
}

/**
 * This function will handle serial
 */
void rt_serial_handler(int vector)
{
	INTSUBMSK |= (BIT_SUB_RXD0);

	rt_hw_serial_isr(&uart0_device);

	SUBSRCPND |= BIT_SUB_RXD0;

	/* Unmask sub interrupt (RXD0) */
	INTSUBMSK  &=~(BIT_SUB_RXD0);
}

/**
 * This function will handle init uart
 */
void rt_hw_uart_init(void)
{
	int i;
	
	GPHCON |= 0xa0;
	/*PULLUP is enable */
	GPHUP  |= 0x0c;  
	
	/* FIFO enable, Tx/Rx FIFO clear */
	uart0.uart_device->ufcon = 0x1;
	/* disable the flow control */
	uart0.uart_device->umcon = 0x0;	
	/* Normal,No parity,1 stop,8 bit */
	uart0.uart_device->ulcon = 0x3;	
	/*
	 * tx=level,rx=edge,disable timeout int.,enable rx error int.,
	 * normal,interrupt or polling
	 */
	uart0.uart_device->ucon = 0x245;

	/* output PCLK to UART0/1, PWMTIMER */
	CLKCON |= 0x0D00;

	for (i = 0; i < 100; i++);	

	/* install uart isr */
	INTSUBMSK &= ~(BIT_SUB_RXD0);

	rt_hw_interrupt_install(INTUART0, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(INTUART0);		
}

/**
 * This function will init s3ceb2410 board
 */
void rt_hw_board_init()
{
	/* FCLK = 304.8M */
	#define MDIV		68
	#define PDIV		1
	#define SDIV		1

	//rt_hw_set_clock(SDIV, PDIV, MDIV);
	/* HCLK = PCLK = FCLK */
	//rt_hw_set_dividor(0, 0);

	/* use PWM Timer 4 because it has no output */
	/* prescaler for Timer 4 is 16 */
	TCFG0 = 0x0f00;

	/* all divider = 1/2 */
	TCFG1 = 0x0;

	rt_hw_get_clock();

	if (timer_load_val == 0)
	{
		/*
		 * for 10 ms clock period @ PCLK with 4 bit divider = 1/2
		 * (default) and prescaler = 16. Should be 10390
		 * @33.25MHz and 15625 @ 50 MHz
		 */
		timer_load_val = PCLK/(2 * 16 * 100);
	}
	/* load value for 10 ms timeout */
	TCNTB4 = timer_load_val;
	/* auto load, manual update of Timer 4 */
	TCON = (TCON & ~0x0700000) | 0x600000;
	/* auto load, start Timer 4 */
	TCON = (TCON & ~0x0700000) | 0x500000 | 0x3;
	/*Enable NAND, USBD, PWM TImer, UART0,1 and GPIO clock,*/
	CLKCON = 0xfffff0;

	/* initialize uart */
	rt_hw_uart_init();

	/* initialize mmu */
	rt_hw_mmu_init();

	/* initialize keypad */
	rt_kbd_init();

	/* initialize console */
	//rt_console_init(&_rt_hw_framebuffer[0], &asc16_font[0], 2);

#ifdef RT_USING_RTGUI
	rt_hw_touch_init();
#endif

	/* install interrupt handler */
	rt_hw_interrupt_install(INTTIMER4, rt_timer_handler, RT_NULL);
	rt_hw_interrupt_umask(INTTIMER4);

	/* stop timer 	*/
	/* TCON = 0x0;	*/
}

/*@}*/
