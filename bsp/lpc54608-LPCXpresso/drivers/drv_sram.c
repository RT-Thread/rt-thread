/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2013-05-19     Bernard      The first version for LPC40xx
*/

#include "board.h"
#include "drv_sram.h"

#include <rtthread.h>

#ifdef BSP_DRV_SDRAM
struct rt_memheap system_heap;

void sram_init(void)
{
    rt_kprintf("system ram: [0x%08x - 0x%08x]\n", HEAP_BEGIN, HEAP_END);
    /* initialize the built-in SRAM as a memory heap */
    rt_memheap_init(&system_heap,
                    "system",
                    (void *)HEAP_BEGIN,
                    (rt_uint32_t)HEAP_END - (rt_uint32_t)HEAP_BEGIN);
}

void *sram_malloc(unsigned long size)
{
    return rt_memheap_alloc(&system_heap, size);
}
RTM_EXPORT(sram_malloc);

void sram_free(void *ptr)
{
    rt_memheap_free(ptr);
}
RTM_EXPORT(sram_free);

void *sram_realloc(void *ptr, unsigned long size)
{
    return rt_memheap_realloc(&system_heap, ptr, size);
}
RTM_EXPORT(sram_realloc);

#endif
