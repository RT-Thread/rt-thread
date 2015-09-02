/*
* File      : sram.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
* Date           Author       Notes
* 2015-08-03     xiaonong     The first version for STM32F7
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
