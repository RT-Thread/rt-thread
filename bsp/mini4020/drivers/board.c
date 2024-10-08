/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-16     Bernard      first implementation
 * 2010-10-5      Wangmeng     sep4020 implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include <sep4020.h>
#include <drivers/dev_serial.h>

void rt_hw_serial_putc(const char c);

#define UART0   ((struct uartport *)UART0_BASE)
struct rt_device uart0_device;
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
    UART0,
    &uart0_int_rx,
    RT_NULL
};

/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector, void *param)
{
    rt_uint32_t clear_int;
    rt_tick_increase();

    /*Clear timer interrupt*/
    clear_int = *(RP)TIMER_T1ISCR;
    *(RP)TIMER_T1ISCR=clear_int;
}

/**
 * This function will handle serial
 */
void rt_serial_handler(int vector, void *param)
{
    //rt_kprintf("in rt_serial_handler\n");
    rt_int32_t stat = *(RP)UART0_IIR ;
    char c;

    RT_UNUSED(c);

    /*Received data*/
    if (((stat & 0x0E) >> 1) == 0x02)
    {
        rt_hw_serial_isr(&uart0_device);
    }
    else
    {
        /*clear the timeout interrupt*/
        while (uart0.uart_device->lsr & USTAT_RCV_READY)
            c = uart0.uart_device->dlbl_fifo.rxfifo;
    }
}

/**
 * This function will init led on the board
 */
static void rt_hw_board_led_init(void)
{
  /* PE3 PE4 PE5 for led */
  *(RP)GPIO_PORTE_SEL |=0x38; /* GPIO */

  *(RP)GPIO_PORTE_DIR &= ~0x38; /* output*/

  *(RP)GPIO_PORTE_DATA &= ~0x38;  /* low */
}

/**
 * This function will init timer4 for system ticks
 */
void rt_hw_timer_init(void)
{
    /*Set timer1*/
    *(RP)TIMER_T1LCR = 880000;
    *(RP)TIMER_T1CR = 0x06;

    rt_hw_interrupt_install(INTSRC_TIMER1, rt_timer_handler, RT_NULL, "tick");
    rt_hw_interrupt_umask(INTSRC_TIMER1);

    /*Enable timer1*/
    *(RP)TIMER_T1CR |= 0x01;
}

/**
 * This function will handle init uart
 */
void rt_hw_uart_init(void)
{
    const rt_int32_t sysclk = 72000000;

    /*Set data bit:8*/
    *(RP)(UART0_LCR) = 0x83;
    /*Set baud rate high*/
    *(RP)(UART0_DLBH) = (sysclk/16/115200) >> 8;
    /*Set baud rate low*/
    *(RP)(UART0_DLBL) = (sysclk/16/115200) & 0xff;

    *(RP)(UART0_LCR) = 0x83&(~(0x1 << 7));

    /*Set trigger level*/
    *(RP)(UART0_FCR) = 0x0;
    *(RP)(UART0_IER) = 0x0;

    /*Enable rx interrupt*/
    *(RP)(UART0_IER) |= 0x01;
    /*Disable tx interrupt*/
    *(RP)(UART0_IER) &= ~(0x1<<1);

    rt_hw_interrupt_install(INTSRC_UART0, rt_serial_handler, RT_NULL, "UART0");
    rt_hw_interrupt_umask(INTSRC_UART0);
    /* register uart0 */
    rt_hw_serial_register(&uart0_device, "uart0",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart0);
}

void rt_hw_board_init(void)
{
    /* initialize uart */
    rt_hw_uart_init();
//  rt_hw_board_led_init();
    rt_hw_timer_init();
}

/* write one character to serial, must not trigger interrupt */
void rt_hw_serial_putc(const char c)
{
    /*
        to be polite with serial console add a line feed
        to the carriage return character
    */
    if (c=='\n')
        rt_hw_serial_putc('\r');

    while (!((*(RP)UART0_LSR) & 0x40));

    *(RP)(UART0_BASE) = c;
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char *str)
{
    while (*str)
    {
        rt_hw_serial_putc(*str++);
    }
}
