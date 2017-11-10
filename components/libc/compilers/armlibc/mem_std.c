/*
 * File     : mem_std.c
 * Brief    : implement standard memory routins.
 *
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * 2014-08-03     bernard      Add file header.
 */

#include "rtthread.h"

/* avoid the heap and heap-using library functions supplied by arm */
#pragma import(__use_no_heap)

void *malloc(int n)
{
    return rt_malloc(n);
}
RTM_EXPORT(malloc);

void *realloc(void *rmem, rt_size_t newsize)
{
    return rt_realloc(rmem, newsize);
}
RTM_EXPORT(realloc);

void *calloc(rt_size_t nelem, rt_size_t elsize)
{
    return rt_calloc(nelem, elsize);
}
RTM_EXPORT(calloc);

void free(void *rmem)
{
    rt_free(rmem);
}
RTM_EXPORT(free);
