/**
 * @file    heap_override.c
 *
 * @brief   Heap memory allocation functions override for RT-Thread without dynamic memory heap.
 *
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     bernard      Add file header
 * 2021-11-13     Meco Man     Implement no-heap warning
 */

#include <rtthread.h>
#include <stddef.h>

#ifndef RT_USING_HEAP
#define DBG_TAG "armlibc.syscall.mem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief   Display a warning message indicating that dynamic memory heap is not enabled.
 *
 * @note    This function is called when attempting to use memory allocation functions without heap support.
 *          It logs an error message and asserts to indicate that RT_USING_HEAP should be enabled.
 */
#define _NO_HEAP_ERROR()                      \
    do                                        \
    {                                         \
        LOG_E("Please enable RT_USING_HEAP"); \
        RT_ASSERT(0);                         \
    } while (0)
#endif /* RT_USING_HEAP */

#ifdef __CC_ARM
/* Avoid the heap and heap-using library functions supplied by arm */
#pragma import(__use_no_heap)
#endif /* __CC_ARM */

/**
 * @brief   Allocate memory from the heap.
 *
 * @param   n     Number of bytes to allocate.
 *
 * @return  A pointer to the allocated memory, or RT_NULL if heap support is not enabled.
 *
 * @note    This function overrides the standard C library's 'malloc' function when RT_USING_HEAP is not defined.
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
RTM_EXPORT(malloc);

/**
 * @brief   Reallocate memory from the heap.
 *
 * @param   rmem     Pointer to the previously allocated memory.
 * @param   newsize  New size in bytes.
 *
 * @return  A pointer to the reallocated memory, or RT_NULL if heap support is not enabled.
 *
 * @note    This function overrides the standard C library's 'realloc' function when RT_USING_HEAP is not defined.
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
RTM_EXPORT(realloc);

/**
 * @brief   Allocate and zero-initialize memory from the heap.
 *
 * @param   nelem   Number of elements to allocate.
 * @param   elsize  Size of each element in bytes.
 *
 * @return  A pointer to the allocated and zero-initialized memory, or RT_NULL if heap support is not enabled.
 *
 * @note    This function overrides the standard C library's 'calloc' function when RT_USING_HEAP is not defined.
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
RTM_EXPORT(calloc);

/**
 * @brief   Free memory allocated from the heap.
 *
 * @param   rmem     Pointer to the memory to be freed.
 *
 * @note    This function overrides the standard C library's 'free' function when RT_USING_HEAP is not defined.
 */
void free(void *rmem)
{
#ifdef RT_USING_HEAP
    rt_free(rmem);
#else
    _NO_HEAP_ERROR();
#endif
}
RTM_EXPORT(free);
