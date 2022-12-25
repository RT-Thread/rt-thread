/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * srand48.c
 */

#include <stdlib.h>
#include <stdint.h>

/* Common with mrand48.c, lrand48.c */
extern unsigned short __rand48_seed[3];

void srand48(long seedval)
{
	__rand48_seed[0] = 0x330e;
	__rand48_seed[1] = (unsigned short)seedval;
	__rand48_seed[2] = (unsigned short)((uint32_t) seedval >> 16);
}

void srand(unsigned int __s)
{
	srand48(__s);
}

void srandom(unsigned int __s)
{
	srand48(__s);
}
