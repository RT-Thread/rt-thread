/*
 * File      : console.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>


#include "serial.h"

static unsigned addr_6845;
static rt_uint16_t *crt_buf;
static rt_int16_t  crt_pos;

extern void rt_serial_init(void);
extern char rt_keyboard_getc(void);

static void rt_console_putc(int c);

/**
 * @addtogroup QEMU
 */
/*@{*/

/**
 * This function initializes cga
 *
 */
void rt_cga_init(void)
{
	rt_uint16_t volatile *cp;
	rt_uint16_t was;
	rt_uint32_t pos;

	cp = (rt_uint16_t *) (CGA_BUF);
	was = *cp;
	*cp = (rt_uint16_t) 0xA55A;
	if (*cp != 0xA55A)
	{
		cp = (rt_uint16_t *) (MONO_BUF);
		addr_6845 = MONO_BASE;
	}
	else
	{
		*cp = was;
		addr_6845 = CGA_BASE;
	}

	/* Extract cursor location */
	outb(addr_6845, 14);
	pos = inb(addr_6845+1) << 8;
	outb(addr_6845, 15);
	pos |= inb(addr_6845+1);

	crt_buf = (rt_uint16_t *)cp;
	crt_pos = pos;
}

/**
 * This function will write a character to cga
 *
 * @param c the char to write
 */
static void rt_cga_putc(int c)
{
	/* if no attribute given, then use black on white */
	if (!(c & ~0xff)) c |= 0x0700;

	switch (c & 0xff)
	{
	case '\b':
		if (crt_pos > 0)
		{
			crt_pos--;
			crt_buf[crt_pos] = (c&~0xff) | ' ';
		}
		break;
	case '\n':
		crt_pos += CRT_COLS;
		/* cascade	*/
	case '\r':
		crt_pos -= (crt_pos % CRT_COLS);
		break;
	case '\t':
		rt_console_putc(' ');
		rt_console_putc(' ');
		rt_console_putc(' ');
		rt_console_putc(' ');
		rt_console_putc(' ');
		break;
	default:
		crt_buf[crt_pos++] = c;		/* write the character */
		break;
	}

	if (crt_pos >= CRT_SIZE)
	{
		rt_int32_t i;
		rt_memcpy(crt_buf, crt_buf + CRT_COLS, (CRT_SIZE - CRT_COLS) << 1);
		for (i = CRT_SIZE - CRT_COLS; i < CRT_SIZE; i++)
			crt_buf[i] = 0x0700 | ' ';
		crt_pos -= CRT_COLS;
	}

	outb(addr_6845, 14);
	outb(addr_6845+1, crt_pos >> 8);
	outb(addr_6845, 15);
	outb(addr_6845+1, crt_pos);
}

/**
 * This function will write a character to serial an cga
 *
 * @param c the char to write
 */
static void rt_console_putc(int c)
{
	rt_cga_putc(c);
	rt_serial_putc(c);
}

/**
 * This function initializes console
 *
 */
void rt_console_init(void)
{
	rt_cga_init();
	rt_serial_init();
}

/**
 * This function is used to display a string on console, normally, it's 
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 *
 * Modified:
 *	caoxl 2009-10-14
 *	the name is change to rt_hw_console_output in the v0.3.0
 *
 */

//void rt_console_puts(const char* str)
void rt_hw_console_output(const char* str)
{
	while (*str)
	{
		rt_console_putc (*str++);
	}
}

#define BY2CONS 512

static struct
{
	rt_uint8_t buf[BY2CONS];
	rt_uint32_t rpos;
	rt_uint32_t wpos;
}cons;

static void rt_console_intr(char (*proc)(void))
{
	int c;

	while ((c = (*proc)()) != -1)
	{
		if (c == 0)
			continue;
		cons.buf[cons.wpos++] = c;
		if (cons.wpos == BY2CONS)
			cons.wpos = 0;
	}
}

/**
 * return the next input character from the console,either from serial,
 * or keyboard
 *
 */
int rt_console_getc(void)
{
	int c;

	rt_console_intr(rt_serial_getc);
	rt_console_intr(rt_keyboard_getc);

	if (cons.rpos != cons.wpos)
	{
		c = cons.buf[cons.rpos++];
		if (cons.rpos == BY2CONS)
			cons.rpos = 0;
		return c;
	}
	return 0;
}

/*@}*/
