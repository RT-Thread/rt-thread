/* See LICENSE of license details. */

#include <stddef.h>

void *_sbrk(ptrdiff_t incr) {
    extern char _end[];

    static char *curbrk = _end;

    if ((curbrk + incr < _end) )
        return (void *)-1;

    curbrk += incr;
    return curbrk - incr;
}
