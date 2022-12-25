/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * memswap()
 *
 * Swaps the contents of two nonoverlapping memory areas.
 * This really could be done faster...
 */

#include <string.h>

void memswap(void *m1, void *m2, size_t n)
{
	char *p = (char *)m1;
	char *q = (char *)m2;
	char tmp;

	while (n--) {
		tmp = *p;
		*p = *q;
		*q = tmp;

		p++;
		q++;
	}
}
