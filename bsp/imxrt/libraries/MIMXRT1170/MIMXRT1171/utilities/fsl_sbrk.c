/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2022, 2024-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if defined(__GNUC__)
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#endif

#if defined(__GNUC__)
/*!
 * @brief Function to override ARMGCC default function _sbrk
 *
 * _sbrk is called by malloc. ARMGCC default _sbrk compares "SP" register and
 * heap end, if heap end is larger than "SP", then _sbrk returns error and
 * memory allocation failed. This function changes to compare __HeapLimit with
 * heap end.
 */
void * _sbrk(ptrdiff_t incr);
void * _sbrk(ptrdiff_t incr)
{
    extern char end __asm("end");
    extern char heap_limit __asm("__HeapLimit");
    static char *heap_end;
    char *prev_heap_end;
    void *ret;

    if (heap_end == NULL)
    {
        heap_end = &end;
    }

    prev_heap_end = heap_end;

    if ((&heap_limit) - heap_end < incr)
    {
        errno = ENOMEM;

        ret = (void *)-1;
    }
    else
    {
        heap_end = (char *)((uintptr_t)heap_end + (uintptr_t)incr);

        ret = (void *)prev_heap_end;
    }

    return ret;
}
#endif
