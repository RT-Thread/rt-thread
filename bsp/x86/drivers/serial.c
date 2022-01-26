/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 * 2006-10-10     Bernard      use keyboard instead of serial
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

/**
 * @addtogroup QEMU
 */
/*@{*/

/**
 * This function initializes serial
 */
void rt_serial_init(void)
{
    outb(COM1+3,0x80);  /* set DLAB of line control reg */
    outb(COM1,0x0c);    /* LS of divisor (48 -> 2400 bps */
    outb(COM1+1,0x00);  /* MS of divisor */
    outb(COM1+3,0x03);  /* reset DLAB */
    outb(COM1+4,0x0b);  /* set DTR,RTS, OUT_2 */
    outb(COM1+1,0x0d);  /* enable all intrs but writes */
    inb(COM1);          /* read data port to reset things (?) */
}

/**
 * This function read a character from serial without interrupt enable mode
 *
 * @return the read char
 */
char rt_serial_getc(void)
{
    while(!(inb(COM1+COMSTATUS) & COMDATA));

    return inb(COM1+COMREAD);
}

/**
 * This function will write a character to serial without interrupt enable mode
 *
 * @param c the char to write
 */
void rt_serial_putc(const char c)
{
    int val;

    while(1)
    {
           if ((val = inb(COM1+COMSTATUS)) & THRE)
            break;
    }

    outb(COM1+COMWRITE, c&0xff);
}

/*@}*/
