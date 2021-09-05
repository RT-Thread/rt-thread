/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-04-15     Bernard      the first version.
 */
#include "platform.h"

#ifdef RT_USING_MEMHEAP
static struct rt_memheap _memheap;
#endif

void platform_init(void)
{
#ifdef RT_USING_MEMHEAP
    /* create memory heap object on 0x2007 C000 - 0x2008 4000*/
#ifdef RT_USING_LWIP
    rt_memheap_init(&_memheap, "system", (void*)0x2007C000, 16*1024);
#else
    rt_memheap_init(&_memheap, "system", (void*)0x2007C000, 32*1024);
#endif
#endif
}
