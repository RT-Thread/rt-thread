
#include "internal.h"
static uint32_t  next = 1;

static uint32_t seed;


/* Return next random integer */

int32_t rand()
{
	next = next * 1103515245L + 12345;
	return (uint32_t) (next / 65536L) % 32768L;
}

/* Set seed for random generator */

void srand(seed)
  uint32_t seed;
{
	next = seed;
}

void srandom(seed)
  uint32_t seed;
{
	srand(seed);
}

int32_t random()
{
    return rand();
}

