/*
 * File      : keyboard.c
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

#define NO			0

#define SHIFT		(1 << 0)
#define CTL			(1 << 1)
#define ALT			(1 << 2)

#define CAPSLOCK	(1<<3)
#define NUMLOCK		(1<<4)
#define SCROLLOCK	(1<<5)

static int shiftcode[256] = 
{
	[29] CTL,
	[42] SHIFT,
	[54] SHIFT,
	[56] ALT,
};

static int togglecode[256] = 
{
	[58] CAPSLOCK,
	[69] NUMLOCK,
	[70] SCROLLOCK,
};

static char normalmap[256] =
{
	NO,    033,  '1',  '2',  '3',  '4',  '5',  '6',
	'7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
	'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
	'o',  'p',  '[',  ']',  '\n', NO,   'a',  's',
	'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',
	'\'', '`',  NO,   '\\', 'z',  'x',  'c',  'v',
	'b',  'n',  'm',  ',',  '.',  '/',  NO,   '*',
	NO,   ' ',   NO,   NO,   NO,   NO,   NO,   NO,
	NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',
	'8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
	'2',  '3',  '0',  '.',  
};

static char shiftmap[256] = 
{
	NO,   033,  '!',  '@',  '#',  '$',  '%',  '^',
	'&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
	'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
	'O',  'P',  '{',  '}',  '\n', NO,   'A',  'S',
	'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',
	'"',  '~',  NO,   '|',  'Z',  'X',  'C',  'V',
	'B',  'N',  'M',  '<',  '>',  '?',  NO,   '*',
	NO,   ' ',   NO,   NO,   NO,   NO,   NO,   NO,
	NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',
	'8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
	'2',  '3',  '0',  '.',  
};

#define C(x) (x-'@')

static char ctlmap[256] = 
{
	NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO, 
	NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO, 
	C('Q'),  C('W'),  C('E'),  C('R'),  C('T'),  C('Y'),  C('U'),  C('I'),
	C('O'),  C('P'),  NO,      NO,      '\r',    NO,      C('A'),  C('S'),
	C('D'),  C('F'),  C('G'),  C('H'),  C('J'),  C('K'),  C('L'),  NO, 
	NO,      NO,      NO,      C('\\'), C('Z'),  C('X'),  C('C'),  C('V'),
	C('B'),  C('N'),  C('M'),  NO,      NO,      C('/'),  NO,      NO, 
};

static char *charcode[4] = 
{
	normalmap,
	shiftmap,
	ctlmap,
	ctlmap,
};

/**
 * @addtogroup QEMU
 */
/*@{*/

/**
 * This function get a char from the keyboard
 */
char rt_keyboard_getc(void)
{
	int c;
	rt_uint8_t data;
	static rt_uint32_t shift;

	if ((inb(KBSTATP) & KBS_DIB) == 0)
		return -1;

	data = inb(KBDATAP);

	if (data & 0x80) 
	{
		/* key up */
		shift &= ~shiftcode[data&~0x80];
		return 0;
	}

	/* key down */
	shift |= shiftcode[data];
	shift ^= togglecode[data];
	c = charcode[shift&(CTL|SHIFT)][data];

	if (shift&CAPSLOCK) 
	{
		if ('a' <= c && c <= 'z')
			c += 'A' - 'a';
		else if ('A' <= c && c <= 'Z')
			c += 'a' - 'A';
	}
	
	return c;
}

/*@}*/
