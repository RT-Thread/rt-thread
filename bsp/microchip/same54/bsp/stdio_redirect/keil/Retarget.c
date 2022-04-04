/**
 * \file
 *
 * \brief STDIO redirection
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <stdio.h>

#ifdef _UNIT_TEST_
#undef fputc
#undef fgetc
#undef ferror
#define fputc ut_fputc
#define fgetc ut_fgetc
#define ferror ut_ferror
#endif

#include <stdio_io.h>

/* Disable semihosting */
#if defined(__GNUC__) && (__ARMCOMPILER_VERSION > 6000000) /*  Keil MDK with ARM Compiler 6 */
__asm(".global __use_no_semihosting\n\t");
#else
#pragma import(__use_no_semihosting_swi)
#endif

#ifndef __GNUC__
struct __FILE {
	int handle;
};
#endif
FILE __stdout;
FILE __stdin;
FILE __stderr;

int fputc(int ch, FILE *f)
{
	if ((f == stdout) || (f == stderr)) {
		uint8_t tmp = (uint8_t)ch;
		if (stdio_io_write(&tmp, 1) < 0) {
			return EOF;
		}
		return ch;
	} else {
		return EOF;
	}
}

int fgetc(FILE *f)
{
	if (f == stdin) {
		uint8_t tmp = 0;
		if (stdio_io_read(&tmp, 1) < 0) {
			return EOF;
		}
		return tmp;
	} else {
		return EOF;
	}
}

void _ttywrch(int ch)
{
	uint8_t tmp = (uint8_t)ch;
	stdio_io_write(&tmp, 1);
}

int ferror(FILE *f)
{
	(void)f;
	/* Your implementation of ferror */
	return EOF;
}

void _sys_exit(int return_code)
{
	(void)return_code;
	while (1) {
	}; /* endless loop */
}
