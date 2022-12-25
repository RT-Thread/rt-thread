/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * strcmp.c
 */

#include <string.h>

#ifdef BFLB_IN_BENCHMARK
int bflb_strcmp(const char *s1, const char *s2)
#else
int strcmp(const char *s1, const char *s2)
#endif
{
	const unsigned char *c1 = (const unsigned char *)s1;
	const unsigned char *c2 = (const unsigned char *)s2;
	unsigned char ch;
	int d = 0;

	while (1) {
		d = (int)(ch = *c1++) - (int)*c2++;
		if (d || !ch)
			break;
	}

	return d;
}
