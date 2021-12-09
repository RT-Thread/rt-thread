/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     bernard      Add file header
 * 2021-11-13     Meco Man     implement no-heap warning
 */

#include <rtthread.h>
#include <stddef.h>

#ifndef RT_USING_HEAP
#define DBG_TAG    "armlibc.mem"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define _NO_HEAP_ERROR()  do{LOG_E("Please enable RT_USING_HEAP");\
                             RT_ASSERT(0);\
                            }while(0)
#endif /* RT_USING_HEAP */

#ifdef __CC_ARM
/* avoid the heap and heap-using library functions supplied by arm */
#pragma import(__use_no_heap)
#endif /* __CC_ARM */

void *malloc(size_t n)
{
#ifdef RT_USING_HEAP
    return rt_malloc(n);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}
RTM_EXPORT(malloc);

void *realloc(void *rmem, size_t newsize)
{
#ifdef RT_USING_HEAP
    return rt_realloc(rmem, newsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}
RTM_EXPORT(realloc);

void *calloc(size_t nelem, size_t elsize)
{
#ifdef RT_USING_HEAP
    return rt_calloc(nelem, elsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}
RTM_EXPORT(calloc);

void free(void *rmem)
{
#ifdef RT_USING_HEAP
    rt_free(rmem);
#else
    _NO_HEAP_ERROR();
#endif
}
RTM_EXPORT(free);
