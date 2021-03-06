/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 */

#ifndef __PAGE_H__
#define __PAGE_H__

typedef struct tag_region
{
    size_t start;
    size_t end;
}rt_region_t;

rt_size_t rt_page_bits(rt_size_t size);
void *rt_pages_alloc(rt_size_t size_bits);
void rt_pages_free(void *addr,rt_size_t size_bits);
void rt_pageinfo_dump();
void rt_page_get_info(size_t *total_nr, size_t *free_nr);
void rt_page_init(rt_region_t reg);

#endif