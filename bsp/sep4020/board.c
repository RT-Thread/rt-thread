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
 * 2006-08-23     Bernard      first implementation
 */

#include <rtthread.h>
#include <rthw.h>

#include <sep4020.h>
#include "board.h"
#include "serial.h"

/**
 * @addtogroup sep4020
 */
/*@{*/

extern rt_uint32_t rt_hw_get_clock(void);

/* uart0 */
#define UART0	((struct uartport *)UART0BASE)
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
	UART0,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;
/**
 * This is the timer interrupt service routine.
 * @param vector the irq number for timer
 */
void rt_hw_timer_handler(int vector)
{
    /* clear interrupt */        
    TIMER_T1ISCR;
	/* increase a tick */
	rt_tick_increase();
}

/**
 * This is the uart0 interrupt service routine.
 * @param vector the irq number for uart0
 */
void rt_serial_handler(int vector)
{
	rt_hw_serial_isr(&uart0_device);
}

/**
 * This function will handle init uart.
 */
void rt_hw_uart_init(void)
{
    rt_uint32_t baud;
    rt_uint32_t sysclock;

    sysclock = rt_hw_get_clock();
    /* caculate baud rate register */
    baud = sysclock/16/BR;

	/* LCR  */
	uart0.uart_device->lcr = 0x83;
	/* DLBH, IER  */
	uart0.uart_device->dlbh_ier = (baud>>8)&0xff;;
	/* DLBL */
	uart0.uart_device->dlbl_rxfifo_txfifo = baud&0xff;
	/* LCR */
	uart0.uart_device->lcr = 0x03;
	/* IER */
	uart0.uart_device->dlbh_ier = 0x01;
	/* FCR */
	uart0.uart_device->iir_fcr = 0x00;

 	rt_hw_serial_register(&uart0_device, "uart0",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart0);
	/* install uart isr */
	INTC_IER  |= (1<<INT_UART0);

	rt_hw_interrupt_install(INT_UART0, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(INT_UART0);
}
/** 
 * This function will init led on the board
 */
static void rt_hw_board_led_init(void)
{
  /* PE3 PE4 PE5 for led */
  GPIO_PORTE_SEL |=0x38; /* GPIO */
  
  GPIO_PORTE_DIR &= ~0x38; /* output*/

  GPIO_PORTE_DATA &= ~0x38;  /* low */
}

/**
 * This function will init timer1 for system ticks
 */
 static void rt_hw_timer_init(void)
 {
	TIMER_T1CR = 0x06;	                    /* reload mode and interrupt enable   */
	TIMER_T1LCR = 0xAFC80;	                /* 10ms under 72MHz 0xAFC80=720000    */

    INTC_IER  |= (1<<INT_TIMER1);           /* interrupt enable                   */

    rt_hw_interrupt_install(INT_TIMER1, rt_hw_timer_handler, RT_NULL);
	rt_hw_interrupt_umask(INT_TIMER1);

    TIMER_T1CR |= 0x01;                     /* enable the timer 1                 */
 }

/**
 * This function will initial sam7x board.
 */
void rt_hw_board_init()
{
	
	/* init hardware uart */
	rt_hw_uart_init();
	rt_console_set_device("uart0");

	/* init led */
	rt_hw_board_led_init();

	/* init timer for tick */
    rt_hw_timer_init();
	
}
/*@}*/
