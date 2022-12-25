/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * strpbrk
 */

#include <string.h>

#include "strxspn.h"

char *strpbrk(const char *s, const char *accept)
{
	const char *ss = s + __strxspn(s, accept, 1);

	return *ss ? (char *)ss : NULL;
}
