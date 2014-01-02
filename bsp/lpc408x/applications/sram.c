/*
* File      : sram.c
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
*
* The license and distribution terms for this file may be
* found in the file LICENSE in this distribution or at
* http://www.rt-thread.org/license/LICENSE
*
* Change Logs:
* Date           Author       Notes
* 2013-05-19     Bernard      The first version for LPC40xx
*/

#include "sram.h"
#include "board.h"

#include <rtthread.h>

#ifdef LPC_EXT_SDRAM
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

void sram_free(void *ptr)
{
    rt_memheap_free(ptr);
}

void *sram_realloc(void *ptr, unsigned long size)
{
    return rt_memheap_realloc(&system_heap, ptr, size);
}

#endif
