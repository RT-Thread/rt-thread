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

extern rt_uint32_t PCLK, FCLK, HCLK, UCLK;

extern void rt_hw_clock_init(void);
extern void rt_hw_mmu_init(void);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);

#define UART0	((struct uartport *)&U0BASE)
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
	UART0,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;

#define UART2	((struct uartport *)&U2BASE)
struct serial_int_rx uart2_int_rx;
struct serial_device uart2 =
{
	UART2,
	&uart2_int_rx,
	RT_NULL
};
struct rt_device uart2_device;

/**
 * This function will handle rtos timer
 */
static void rt_timer_handler(int vector, void *param)
{
	rt_tick_increase();
}

/**
 * This function will handle serial
 */
static void rt_serial0_handler(int vector, void *param)
{
	INTSUBMSK |= (BIT_SUB_RXD0);

	rt_hw_serial_isr(&uart0_device);

	SUBSRCPND |= BIT_SUB_RXD0;

	/* Unmask sub interrupt (RXD0) */
	INTSUBMSK  &=~(BIT_SUB_RXD0);
}

/**
 * This function will handle serial
 */
static void rt_serial2_handler(int vector, void *param)
{
	INTSUBMSK |= (BIT_SUB_RXD2);

	rt_hw_serial_isr(&uart2_device);

	SUBSRCPND |= BIT_SUB_RXD2;

	/* Unmask sub interrupt (RXD0) */
	INTSUBMSK  &=~(BIT_SUB_RXD2);
}

/**
 * This function will handle init uart
 */
static void rt_hw_uart_init(void)
{
	int i;
	/* UART0 port configure */
	GPHCON |= 0xAA;
	/* PULLUP is disable */
	GPHUP |= 0xF;

	/* FIFO enable, Tx/Rx FIFO clear */
	uart0.uart_device->ufcon = 0x0;
	/* disable the flow control */
	uart0.uart_device->umcon = 0x0;
	/* Normal,No parity,1 stop,8 bit */
	uart0.uart_device->ulcon = 0x3;
	/*
	 * tx=level,rx=edge,disable timeout int.,enable rx error int.,
	 * normal,interrupt or polling
	 */
	uart0.uart_device->ucon = 0x245;
	/* Set uart0 bps */
	uart0.uart_device->ubrd = (rt_int32_t)(PCLK / (BPS * 16)) - 1;
	/* output PCLK to UART0/1, PWMTIMER */
	CLKCON |= 0x0D00;

	/* FIFO enable, Tx/Rx FIFO clear */
	uart2.uart_device->ufcon = 0x0;
	/* disable the flow control */
	uart2.uart_device->umcon = 0x0;
	/* Normal,No parity,1 stop,8 bit */
	uart2.uart_device->ulcon = 0x3;
	/*
	 * tx=level,rx=edge,disable timeout int.,enable rx error int.,
	 * normal,interrupt or polling
	 */
	uart2.uart_device->ucon = 0x245;
	/* Set uart0 bps */
	uart2.uart_device->ubrd = (rt_int32_t)(PCLK / (BPS * 16)) - 1;

	for (i = 0; i < 100; i++);

	/* install uart0 isr */
	INTSUBMSK &= ~(BIT_SUB_RXD0);

	/* install uart2 isr */
	INTSUBMSK &= ~(BIT_SUB_RXD2);

	rt_hw_interrupt_install(INTUART0, rt_serial0_handler, RT_NULL, "UART0");
	rt_hw_interrupt_umask(INTUART0);

	rt_hw_interrupt_install(INTUART2, rt_serial2_handler, RT_NULL, "UART2");
	rt_hw_interrupt_umask(INTUART2);
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
	/* initialize the system clock */
	rt_hw_clock_init();

	/* Get the clock */
	rt_hw_get_clock();

	/* initialize led port */
	rt_hw_led_init();

	/* initialize uart */
	rt_hw_uart_init();

	/* initialize mmu */
	rt_hw_mmu_init();

	/* initialize timer4 */
	rt_hw_timer_init();
}

/*@}*/
