/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
#include <string.h>

char *strtok_r(char *s, const char *delim, char **holder)
{
	if (s)
		*holder = s;

	do {
		s = strsep(holder, delim);
	} while (s && !*s);

	return s;
}
