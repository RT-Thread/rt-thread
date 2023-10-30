/**
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-17     Flybreak     the first version
 */

#include <rtthread.h>
#include <sys/types.h>

/* Global errno variable */
static volatile int __pico_errno;

/**
 * @brief   Get a pointer to the global errno variable.
 *
 * @return  A pointer to the global errno variable.
 */
int *pico_get_errno(void)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        /* It's in an interrupt context */
        return &__pico_errno;
    }

    tid = rt_thread_self();
    if (tid == RT_NULL)
    {
        return &__pico_errno;
    }

    return &tid->error;
}

#ifdef RT_USING_HEAP

/**
 * @brief   Allocate memory from the heap.
 *
 * @param   n   The number of bytes to allocate.
 *
 * @return  A pointer to the allocated memory.
 */
void *malloc(size_t n)
{
    return rt_malloc(n);
}
RTM_EXPORT(malloc);

/**
 * @brief   Resize a previously allocated memory block.
 *
 * @param   rmem        A pointer to the previously allocated memory block.
 * @param   newsize     The new size in bytes to resize the block to.
 *
 * @return  A pointer to the resized memory block.
 */
void *realloc(void *rmem, size_t newsize)
{
    return rt_realloc(rmem, newsize);
}
RTM_EXPORT(realloc);

/**
 * @brief   Allocate memory for an array with elements.
 *
 * @param   nelem   The number of elements to allocate.
 * @param   elsize  The size of each element in bytes.
 *
 * @return  A pointer to the allocated memory.
 */
void *calloc(size_t nelem, size_t elsize)
{
    return rt_calloc(nelem, elsize);
}
RTM_EXPORT(calloc);

/**
 * @brief   Free previously allocated memory.
 *
 * @param   rmem    A pointer to the memory block to free.
 */
void free(void *rmem)
{
    rt_free(rmem);
}
RTM_EXPORT(free);
#endif /* RT_USING_HEAP */
