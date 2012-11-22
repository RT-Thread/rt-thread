
#include "rtthread.h"

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
