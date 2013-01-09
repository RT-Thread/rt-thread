/*
 * @brief	IO redirection support
 *
 * This file adds re-direction support to the library for various
 * projects. It can be configured in one of 3 ways - no redirection,
 * redirection via a UART, or redirection via semihosting. If DEBUG
 * is not defined, all printf statements will do nothing with the
 * output being throw away. If DEBUG is defined, then the choice of
 * output is selected by the DEBUG_SEMIHOSTING define. If the
 * DEBUG_SEMIHOSTING is not defined, then output is redirected via
 * the UART. If DEBUG_SEMIHOSTING is defined, then output will be
 * attempted to be redirected via semihosting. If the UART method
 * is used, then the Board_UARTPutChar and Board_UARTGetChar
 * functions must be defined to be used by this driver and the UART
 * must already be initialized to the correct settings.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "sys_config.h"
#include "board.h"

/* Keil (Realview) support */
#if defined(__CC_ARM)

#include <stdio.h>
#include <rt_misc.h>

#if defined(DEBUG)
#if defined(DEBUG_SEMIHOSTING)
#define ITM_Port8(n)    (*((volatile unsigned char *) (0xE0000000 + 4 * n)))
#define ITM_Port16(n)   (*((volatile unsigned short *) (0xE0000000 + 4 * n)))
#define ITM_Port32(n)   (*((volatile unsigned long *) (0xE0000000 + 4 * n)))

#define DEMCR           (*((volatile unsigned long *) (0xE000EDFC)))
#define TRCENA          0x01000000

/* Write to SWO */
void _ttywrch(int ch)
{
	if (DEMCR & TRCENA) {
		while (ITM_Port32(0) == 0) {}
		ITM_Port8(0) = ch;
	}
}

#else
static INLINE void BoardOutChar(char ch)
{
	Board_UARTPutChar(ch);
}

#endif /* defined(DEBUG_SEMIHOSTING) */
#endif /* defined(DEBUG) */

struct __FILE {
	int handle;
};

FILE __stdout;
FILE __stdin;
FILE __stderr;

void *_sys_open(const char *name, int openmode)
{
	return 0;
}

int fputc(int c, FILE *f)
{
#if defined(DEBUG)
#if defined(DEBUG_SEMIHOSTING)
	_ttywrch(c);
#else
	BoardOutChar((char) c);
#endif
#endif
	return 0;
}

int fgetc(FILE *f)
{
#if defined(DEBUG) && !defined(DEBUG_SEMIHOSTING)
	return Board_UARTGetChar();
#else
	return 0;
#endif
}

int ferror(FILE *f)
{
	return EOF;
}

void _sys_exit(int return_code)
{
label:  goto label;	/* endless loop */
}

#endif /* defined (__CC_ARM) */

/* IAR support */
#if defined(__ICCARM__)
/*******************
 *
 * Copyright 1998-2003 IAR Systems.  All rights reserved.
 *
 * $Revision: 30870 $
 *
 * This is a template implementation of the "__write" function used by
 * the standard library.  Replace it with a system-specific
 * implementation.
 *
 * The "__write" function should output "size" number of bytes from
 * "buffer" in some application-specific way.  It should return the
 * number of characters written, or _LLIO_ERROR on failure.
 *
 * If "buffer" is zero then __write should perform flushing of
 * internal buffers, if any.  In this case "handle" can be -1 to
 * indicate that all handles should be flushed.
 *
 * The template implementation below assumes that the application
 * provides the function "MyLowLevelPutchar".  It should return the
 * character written, or -1 on failure.
 *
 ********************/

#include <yfuns.h>

_STD_BEGIN

#pragma module_name = "?__write"

#if defined(DEBUG)
#if defined(DEBUG_SEMIHOSTING)
#error Semihosting support not yet working on IAR
#endif /* defined(DEBUG_SEMIHOSTING) */
#endif /* defined(DEBUG) */

/*
   If the __write implementation uses internal buffering, uncomment
   the following line to ensure that we are called with "buffer" as 0
   (i.e. flush) when the application terminates. */
size_t __write(int handle, const unsigned char *buffer, size_t size)
{
#if defined(DEBUG)
	size_t nChars = 0;

	if (buffer == 0) {
		/*
		   This means that we should flush internal buffers.  Since we
		   don't we just return.  (Remember, "handle" == -1 means that all
		   handles should be flushed.)
		 */
		return 0;
	}

	/* This template only writes to "standard out" and "standard err",
	   for all other file handles it returns failure. */
	if (( handle != _LLIO_STDOUT) && ( handle != _LLIO_STDERR) ) {
		return _LLIO_ERROR;
	}

	for ( /* Empty */; size != 0; --size) {
		Board_UARTPutChar(*buffer++);
		++nChars;
	}

	return nChars;
#else
	return size;
#endif /* defined(DEBUG) */
}

_STD_END

#endif /* defined (__ICCARM__) */

#if defined( __GNUC__ )
/* Include stdio.h to pull in __REDLIB_INTERFACE_VERSION__ */
#include <stdio.h>

#if (__REDLIB_INTERFACE_VERSION__ >= 20000)
/* We are using new Redlib_v2 semihosting interface */
	#define WRITEFUNC __sys_write
	#define READFUNC __sys_readc
#else
/* We are using original Redlib semihosting interface */
	#define WRITEFUNC __write
	#define READFUNC __readc
#endif

#if defined(DEBUG)
#if defined(DEBUG_SEMIHOSTING)
/* Do nothing, semihosting is enabled by default in LPCXpresso */
#endif /* defined(DEBUG_SEMIHOSTING) */
#endif /* defined(DEBUG) */

#if !defined(DEBUG_SEMIHOSTING)
int WRITEFUNC(int iFileHandle, char *pcBuffer, int iLength)
{
#if defined(DEBUG)
	unsigned int i;
	for (i = 0; i < iLength; i++) {
		Board_UARTPutChar(pcBuffer[i]);
	}
#endif

	return iLength;
}

/* Called by bottom level of scanf routine within RedLib C library to read
   a character. With the default semihosting stub, this would read the character
   from the debugger console window (which acts as stdin). But this version reads
   the character from the LPC1768/RDB1768 UART. */
int READFUNC(void)
{
#if defined(DEBUG)
	char c = Board_UARTGetChar();
	return (int) c;

#else
	return (int) -1;
#endif
}

#endif /* !defined(DEBUG_SEMIHOSTING) */
#endif /* defined ( __GNUC__ ) */
