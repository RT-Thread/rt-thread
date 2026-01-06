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
#define DBG_TAG    "armlibc.syscall.mem"
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

/**
 * @brief Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block. The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param[in] n the size of the memory block, in bytes.
 *
 * @return On success, a pointer to the memory block allocated by the function.
 *         If the system is configured without heap (RT_USING_HEAP is not defined),
 *         the function will assert and return RT_NULL.
 *
 * @note The returned pointer is always suitably aligned for any built-in type.
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
 * @brief Reallocate memory block
 *
 * Changes the size of the memory block pointed to by rmem.
 * The function may move the memory block to a new location
 * (whose address is returned by the function).
 * The content of the memory block is preserved up to the
 * lesser of the new and old sizes, even if the block is
 * moved to a new location. If the new size is larger,
 * the value of the newly allocated portion is indeterminate.
 *
 * @param[in,out] rmem pointer to a memory block previously allocated with
 *             malloc, calloc or realloc to be reallocated.
 *             If this is RT_NULL, a new block is allocated and
 *             a pointer to it is returned by the function.
 * @param[in] newsize new size for the memory block, in bytes.
 *
 * @return A pointer to the reallocated memory block, which may be either
 *         the same as the rmem pointer or a new location.
 *         If the system is configured without heap (RT_USING_HEAP is not defined),
 *         the function will assert and return RT_NULL.
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
 * @brief Allocate and zero-initialize array
 *
 * Allocates a block of memory for an array of nelem elements, each of them
 * elsize bytes long, and initializes all its bits to zero.
 * The effective result is the allocation of a zero-initialized memory block
 * of (nelem*elsize) bytes.
 *
 * @param[in] nelem number of elements to allocate.
 * @param[in] elsize size of each element.
 *
 * @return On success, a pointer to the memory block allocated by the function.
 *         If the system is configured without heap (RT_USING_HEAP is not defined),
 *         the function will assert and return RT_NULL.
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
 * @brief Deallocate memory block
 *
 * A block of memory previously allocated by a call to malloc, calloc or realloc
 * is deallocated, making it available again for further allocations.
 *
 * @param[in] rmem pointer to a memory block previously allocated with malloc,
 *             calloc or realloc to be deallocated. If a null pointer is
 *             passed as argument, no action occurs.
 *
 * @note If the system is configured without heap (RT_USING_HEAP is not defined),
 *       the function will assert.
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
