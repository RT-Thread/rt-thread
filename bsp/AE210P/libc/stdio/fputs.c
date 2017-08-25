#include "uart/uart.h"

#include <stdio.h>

__attribute__((used))
int fputc(int c, FILE *stream)
{
	if (c == '\n')
		drv_uart_put_char('\r');

	drv_uart_put_char(c);

	return c;
}

__attribute__((used))
int fputs(const char *s, FILE *stream)
{
	while (fputc(*s++, stream))
		;

	return 0;
}

__attribute__((used))
int putc(int c, FILE *stream)
{
	return fputc(c, stream);
}

__attribute__((used))
int putchar(int c)
{
	return fputc(c, (void*)0x10);
}

__attribute__((used))
int puts(const char *s)
{
	return fputs(s, (void*)0x10);
}
