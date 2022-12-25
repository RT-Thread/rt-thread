/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * mrand48.c
 */

#include <stdlib.h>
#include <stdint.h>

/* Common with lrand48.c, srand48.c */
extern unsigned short __rand48_seed[3];

long mrand48(void)
{
	return jrand48(__rand48_seed);
}
