/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * strstr.c
 */

#include <string.h>
//#include <wmlibc.h>

char *strstr(const char *haystack, const char *needle)
{
	return (char *)memmem(haystack, strlen(haystack), needle,
			      strlen(needle));
}
