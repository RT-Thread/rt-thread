#include <stdarg.h>	/* va_list, va_arg() */
#include <stdio.h>

#include "do_printf.h"

/*****************************************************************************
 * PRINTF You must write your own putchar()
 *****************************************************************************/
static int vprintf_help(unsigned c, void **ptr){

	ptr = ptr; /* to avoid unused varible warning */
	putchar(c);

	return 0;
}

static int vsprintf_help(unsigned int c, void **ptr){

	char *dst = *ptr;
	*dst++ = c;
	*ptr = dst;

	return 0 ;
}

__attribute__((used))
int vsprintf(char *buffer, const char *fmt, va_list args){

	int ret_val = do_printf(fmt, args, vsprintf_help, (void *)buffer);
	buffer[ret_val] = '\0';

	return ret_val;
}

__attribute__((used))
int sprintf(char *buffer, const char *fmt, ...){

	va_list args;
	int ret_val;

	va_start(args, fmt);
	ret_val = vsprintf(buffer, fmt, args);
	va_end(args);

	return ret_val;
}

__attribute__((used))
int vprintf(const char *fmt, va_list args){

	return do_printf(fmt, args, vprintf_help, (void *)0);
}

__attribute__((used))
int printf(const char *fmt, ...){

	va_list args;
	int ret_val;

	va_start(args, fmt);
	ret_val = vprintf(fmt, args);
	va_end(args);

	return ret_val;
}
