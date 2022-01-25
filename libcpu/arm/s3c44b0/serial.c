/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-06     XuXinming    first version
 * 2006-09-20     Bernard      clean code according code style
 */

#include <rtthread.h>
#include <rthw.h>

#include "s3c44b0.h"

void rt_serial_init(void);
void rt_console_puts(const char* str);
void rt_serial_putc(const char c);

#define USTAT_RCV_READY     0x01    /* receive data ready */
#define USTAT_TXB_EMPTY     0x02    /* tx buffer empty */

rt_inline void serial_flush_input(void)
{
    volatile unsigned int tmp;

    /* keep on reading as long as the receiver is not empty */
    while(UTRSTAT0 & USTAT_RCV_READY) tmp = URXH0;
}

rt_inline void serial_flush_output(void)
{
    /* wait until the transmitter is no longer busy */
    while(!(UTRSTAT0 & USTAT_TXB_EMPTY)) ;
}

/**
 * @addtogroup S3C44B0
 */
/*@{*/

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 */
void rt_console_puts(const char* str)
{
    while (*str)
    {
        rt_serial_putc (*str++);
    }
}

/**
 * This function initializes serial
 */
void rt_serial_init()
{
    rt_uint32_t divisor = 0;

    divisor = 0x20;

    serial_flush_output();
    serial_flush_input();

    /* UART interrupt off */
    UCON0   = 0;
    /* FIFO disable */
    UFCON0  =0x0;
    UMCON0  =0x0;
    /* set baudrate */
    UBRDIV0 = divisor;

    /* word length=8bit, stop bit = 1, no parity, use external clock */
    ULCON0  = 0x03|0x00|0x00;

    UCON0   = 0x5;
}

/**
 * This function read a character from serial without interrupt enable mode
 *
 * @return the read char
 */
char rt_serial_getc()
{
    while ((UTRSTAT0 & USTAT_RCV_READY) == 0);

    return URXH0;
}

/**
 * This function will write a character to serial without interrupt enable mode
 *
 * @param c the char to write
 */
void rt_serial_putc(const char c)
{
    /*
        to be polite with serial console add a line feed
        to the carriage return character
    */
    if (c=='\n')rt_serial_putc('\r');

    /* wait for room in the transmit FIFO */
    while(!(UTRSTAT0 & USTAT_TXB_EMPTY));

    UTXH0 = (rt_uint8_t)c;
}

/*@}*/
