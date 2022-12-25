/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * memccpy.c
 *
 * memccpy()
 */

#include <stddef.h>
#include <string.h>

void *memccpy(void *dst, const void *src, int c, size_t n)
{
	char *q = (char *)dst;
	const char *p = (char *)src;
	char ch;

	while (n--) {
		*q++ = ch = *p++;
		if (ch == (char)c)
			return q;
	}

	return NULL;		/* No instance of "c" found */
}
