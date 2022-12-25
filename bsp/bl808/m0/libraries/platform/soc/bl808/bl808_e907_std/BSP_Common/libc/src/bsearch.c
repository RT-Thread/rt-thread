/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * bsearch.c
 */

#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nmemb,
	      size_t size, int (*cmp) (const void *, const void *))
{
	while (nmemb) {
		size_t mididx = nmemb / 2;
		const void *midobj = (const unsigned char *) base +
				mididx * size;
		int diff = cmp(key, midobj);

		if (diff == 0)
			return (void *)midobj;

		if (diff > 0) {
			base = (const unsigned char *) midobj + size;
			nmemb -= mididx + 1;
		} else
			nmemb = mididx;
	}

	return NULL;
}
