/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-01     Jesven       The first version
 * 2022-12-13     WangXiaoyao  Hot-pluggable, extensible
 *                             page management algorithm
 */
#ifndef __MM_PAGE_H__
#define __MM_PAGE_H__

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#define GET_FLOOR(type) \
    (1ul << (8 * sizeof(rt_size_t) - __builtin_clzl(2 * sizeof(type) - 1) - 1))
#define DEF_PAGE_T(fields) \
    typedef struct rt_page {\
        union {struct {fields}; char _padding[GET_FLOOR(struct {fields})];};\
    } *rt_page_t

DEF_PAGE_T(
    struct rt_page *next;   /* same level next */
    struct rt_page *pre;    /* same level pre  */

    rt_uint32_t size_bits;     /* if is ARCH_ADDRESS_WIDTH_BITS, means not free */
    rt_uint32_t ref_cnt;       /* page group ref count */
);

#undef GET_FLOOR
#undef DEF_PAGE_T

typedef struct tag_region
{
    rt_size_t start;
    rt_size_t end;
} rt_region_t;

extern const rt_size_t rt_mpr_size;
extern void *rt_mpr_start;

void rt_page_init(rt_region_t reg);

void rt_page_cleanup(void);

void *rt_pages_alloc(rt_uint32_t size_bits);

void rt_page_ref_inc(void *addr, rt_uint32_t size_bits);

int rt_page_ref_get(void *addr, rt_uint32_t size_bits);

int rt_pages_free(void *addr, rt_uint32_t size_bits);

void rt_page_list(void);

rt_size_t rt_page_bits(rt_size_t size);

void rt_page_get_info(rt_size_t *total_nr, rt_size_t *free_nr);

void *rt_page_page2addr(struct rt_page *p);

struct rt_page *rt_page_addr2page(void *addr);

/**
 * @brief Install page frames at run-time
 * Region size must be aligned to 2^(RT_PAGE_MAX_ORDER + ARCH_PAGE_SHIFT - 1)
 * bytes currently (typically 2 MB).
 *
 * !WARNING this API will NOT check whether region is valid or not in list
 *
 * @param region region.start as first page frame(inclusive),
 *               region.end as first page frame after free region
 * @return int 0 on success
 */
int rt_page_install(rt_region_t region);

#endif /* __MM_PAGE_H__ */
