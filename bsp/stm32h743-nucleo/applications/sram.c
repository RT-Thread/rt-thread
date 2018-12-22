/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
* Date           Author       Notes
* 2015-08-03     xiaonong     The first version for STM32F7
* 2017-08-25     LongfeiMa    transplantation for stm32h7xx
*/

#include "sram.h"
#include "board.h"

#include <rtthread.h>

#ifdef RT_USING_EXT_SDRAM
struct rt_memheap system_heap;

void sram_init(void)
{
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
