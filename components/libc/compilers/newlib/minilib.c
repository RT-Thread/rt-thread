/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-23     Meco Man     first version
 */

#include <reent.h>
#include <rtthread.h>

#ifdef RT_USING_HEAP /* Memory routine */
void *
_malloc_r (struct _reent *ptr, size_t size)
{
    void* result;

    result = (void*)rt_malloc (size);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
    void* result;

    result = (void*)rt_realloc (old, newlen);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
    void* result;

    result = (void*)rt_calloc (size, len);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void
_free_r (struct _reent *ptr, void *addr)
{
    rt_free (addr);
}

#else
void *
_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    return RT_NULL;
}
#endif /*RT_USING_HEAP*/
