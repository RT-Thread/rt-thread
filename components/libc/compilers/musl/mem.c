/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/10/7      bernard      the first version
 */
#include <rtthread.h>

void *malloc(size_t n)
{
    return rt_malloc(n);
}

void *calloc(size_t m, size_t n)
{
    return rt_calloc(m, n);
}

void *realloc(void *p, size_t n)
{
    return rt_realloc(p, n);
}

void free(void *p)
{
    rt_free(p);
}
