/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-28     Bernard      first version
 * 2021-11-13     Meco Man     implement no-heap warning
 */

#include <rtthread.h>
#include <stddef.h>

#ifndef RT_USING_HEAP
#define DBG_TAG    "dlib.syscall.mem"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#define _NO_HEAP_ERROR()  do{LOG_E("Please enable RT_USING_HEAP");\
                             RT_ASSERT(0);\
                            }while(0)
#endif /* RT_USING_HEAP */

void *malloc(size_t n)
{
#ifdef RT_USING_HEAP
    return rt_malloc(n);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

void *realloc(void *rmem, size_t newsize)
{
#ifdef RT_USING_HEAP
    return rt_realloc(rmem, newsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

void *calloc(size_t nelem, size_t elsize)
{
#ifdef RT_USING_HEAP
    return rt_calloc(nelem, elsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

void free(void *rmem)
{
#ifdef RT_USING_HEAP
    rt_free(rmem);
#else
    _NO_HEAP_ERROR();
#endif
}
