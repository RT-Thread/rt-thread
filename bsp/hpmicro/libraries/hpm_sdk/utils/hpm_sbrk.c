/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifdef __GNUC__
#include <stdio.h>
#include <errno.h>
#include "hpm_common.h"

void *_sbrk(int incr)
{
    extern char __heap_start__, __heap_end__;
    static char *heap_end;
    char *prev_heap_end;
    void *ret;

    if (heap_end == NULL)
    {
        heap_end = &__heap_start__;
    }

    prev_heap_end = heap_end;

    if ((unsigned int)heap_end + (unsigned int)incr > (unsigned int)(&__heap_end__))
    {
        errno = ENOMEM;

        ret = (void *)-1;
    }
    else
    {
        heap_end = (char *)((unsigned int)heap_end + (unsigned int)incr);

        ret = (void *)prev_heap_end;
    }

    return ret;
}
#endif
