/**
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
#define DBG_TAG "dlib.syscall.mem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief   A macro for indicating that heap support is not enabled.
 */
#define _NO_HEAP_ERROR()                      \
    do                                        \
    {                                         \
        LOG_E("Please enable RT_USING_HEAP"); \
        RT_ASSERT(0);                         \
    } while (0)
#endif /* RT_USING_HEAP */

/**
 * @brief   Allocate memory from the heap.
 *
 * @param   n   is the number of bytes to allocate.
 *
 * @return  A pointer to the allocated memory, or RT_NULL if heap support is not enabled.
 */
void *malloc(size_t n)
{
#ifdef RT_USING_HEAP
    return rt_malloc(n);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

/**
 * @brief   Resize a previously allocated memory block.
 *
 * @param   rmem        is a pointer to the previously allocated memory block.
 * @param   newsize     is the new size in bytes to resize the block to.
 *
 * @return  A pointer to the resized memory block, or RT_NULL if heap support is not enabled.
 */
void *realloc(void *rmem, size_t newsize)
{
#ifdef RT_USING_HEAP
    return rt_realloc(rmem, newsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

/**
 * @brief   Allocate memory for an array with elements.
 *
 * @param   nelem   is the number of elements to allocate.
 * @param   elsize  is the size of each element in bytes.
 *
 * @return  A pointer to the allocated memory, or RT_NULL if heap support is not enabled.
 */
void *calloc(size_t nelem, size_t elsize)
{
#ifdef RT_USING_HEAP
    return rt_calloc(nelem, elsize);
#else
    _NO_HEAP_ERROR();
    return RT_NULL;
#endif
}

/**
 * @brief   Free previously allocated memory.
 *
 * @param   rmem    is a pointer to the memory block to free.
 */
void free(void *rmem)
{
#ifdef RT_USING_HEAP
    rt_free(rmem);
#else
    _NO_HEAP_ERROR();
#endif
}
