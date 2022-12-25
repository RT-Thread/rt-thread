/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * memcmp.c
 */

#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *c1 = (unsigned char *)s1, *c2 = (unsigned char *)s2;
	int d = 0;

	while (n--) {
		d = (int)*c1++ - (int)*c2++;
		if (d)
			break;
	}

	return d;
}
