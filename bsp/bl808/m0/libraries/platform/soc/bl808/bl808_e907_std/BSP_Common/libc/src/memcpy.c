/*
 * memcpy.c
 */

#include <string.h>
#include <stdint.h>

void *memcpy(void *dst, const void *src, size_t n)
{
	const char *p = (char *)src;
	char *q = (char *)dst;
	while (n--) {
		*q++ = *p++;
	}
	return dst;
}
