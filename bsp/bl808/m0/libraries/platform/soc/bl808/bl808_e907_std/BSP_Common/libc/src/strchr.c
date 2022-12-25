/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * strchr.c
 */

#include <string.h>
#include <compat_attribute.h>

__WEAK__
char *strchr(const char *s, int c)
{
	while (*s != (char)c) {
		if (!*s)
			return NULL;
		s++;
	}

	return (char *)s;
}
