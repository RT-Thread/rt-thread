/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

static unsigned int _seed=1;

/* Knuth's TAOCP section 3.6 */
#define	M	((1U<<31) -1)
#define	A	48271
#define	Q	44488		// M/A
#define	R	3399		// M%A; R < Q !!!

int rand_r(unsigned int* seed)
{   int32_t X;

    X = *seed;
    X = A*(X%Q) - R * (int32_t) (X/Q);
    if (X < 0)
	X += M;

    *seed = X;
    return X;
}

int rand(void) {
  return rand_r(&_seed);
}

void srand(unsigned int i)
{ 
	_seed=i;
}

int random(void) __attribute__((alias("rand")));
void srandom(unsigned int i) __attribute__((alias("srand")));
