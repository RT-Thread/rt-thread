/* See LICENSE of license details. */

#include <stddef.h>

void *_sbrk(ptrdiff_t incr) {
    extern char _end[];

    static char *curbrk = _end;
#ifndef __ANDES__
    extern char _heap_end[];
    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
#else
	if ((curbrk + incr < _end) )
#endif
        return NULL - 1;

    curbrk += incr;
    return curbrk - incr;
}
