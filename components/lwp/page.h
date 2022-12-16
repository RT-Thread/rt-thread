/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-01     Jesven      The first version
 */

#ifndef  __PAGE_H__
#define  __PAGE_H__

#ifdef ARCH_MM_MMU

typedef struct tag_region
{
    size_t start;
    size_t end;
} rt_region_t;

void rt_page_init(rt_region_t reg);

void *rt_pages_alloc(uint32_t size_bits);

void rt_page_ref_inc(void *addr, uint32_t size_bits);

int rt_page_ref_get(void *addr, uint32_t size_bits);

int rt_pages_free(void *addr, uint32_t size_bits);

void rt_pageinfo_dump(void);

size_t rt_page_bits(size_t size);

void rt_page_get_info(size_t *total_nr, size_t *free_nr);

#endif

#endif  /*__PAGE_H__*/
