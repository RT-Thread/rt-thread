/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-17     Flybreak     the first version
 */

#include <rtthread.h>

int pico_get_errno(void)
{
    return rt_get_errno();
}

#ifdef RT_USING_HEAP /* Memory routine */
void *malloc(size_t n)
{
    return rt_malloc(n);
}
RTM_EXPORT(malloc);

void *realloc(void *rmem, size_t newsize)
{
    return rt_realloc(rmem, newsize);
}
RTM_EXPORT(realloc);

void *calloc(size_t nelem, size_t elsize)
{
    return rt_calloc(nelem, elsize);
}
RTM_EXPORT(calloc);

void free(void *rmem)
{
    rt_free(rmem);
}
RTM_EXPORT(free);
#endif
