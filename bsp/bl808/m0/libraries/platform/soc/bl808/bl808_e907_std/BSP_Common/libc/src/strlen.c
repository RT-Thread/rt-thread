/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * strlen()
 */

#include <string.h>

size_t strlen(const char *s)
{
	const char *ss = s;
	while (*ss)
		ss++;
	return ss - s;
}
