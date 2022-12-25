/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * snprintf.c
 */

#include <stdio.h>
#include <stdarg.h>

int snprintf(char *buffer, size_t n, const char *format, ...)
{
	va_list ap;
	int rv;

	va_start(ap, format);
	rv = vsnprintf(buffer, n, format, ap);
	va_end(ap);
	return rv;
}
