/*
 * File:    mem_std.c
 * Brief:   Replace memory management functions of arm standard c library
 *
 */

#include "rtthread.h"

/* avoid the heap and heap-using library functions supplied by arm */
#pragma import(__use_no_heap)

void * malloc(int n)
{
    return rt_malloc(n);
}

void * realloc(void *rmem, rt_size_t newsize)
{
    return rt_realloc(rmem, newsize);
}

void free(void *rmem)
{
    rt_free(rmem);
}
