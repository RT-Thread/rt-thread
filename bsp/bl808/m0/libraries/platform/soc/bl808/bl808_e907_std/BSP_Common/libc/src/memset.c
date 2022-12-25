/*
 * memset.c
 */

#include <string.h>
#include <stdint.h>

void *memset(void *dst, int c, size_t n)
{
	char *q = (char *)dst;
	while (n--) {
		*q++ = c;
		__asm volatile ("":::"memory");
	}
	return dst;
}
