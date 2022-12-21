/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 */
#ifndef  __LWP_MM_AREA_H__
#define  __LWP_MM_AREA_H__

#include <string.h>
#include <stdint.h>

#include <lwp_avl.h>

#ifdef ARCH_MM_MMU

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    MM_AREA_TYPE_PHY = 0,  /* mm_area physical address is IO register or reserved memory no cached*/
    MM_AREA_TYPE_PHY_CACHED,  /* mm_area physical address is IO register or reserved memory with cached */
    MM_AREA_TYPE_SHM,      /* mm_area physical address is shared memory */
    MM_AREA_TYPE_DATA,     /* mm_area physical address is alloced from page manager for data */
    MM_AREA_TYPE_TEXT,     /* mm_area physical address is alloced from page manager for text */
    MM_AREA_TYPE_UNKNOW,
};

struct rt_mm_area_struct
{
    size_t addr;
    size_t size;
    int type;
};

int lwp_map_area_insert(struct lwp_avl_struct **avl_tree, size_t addr, size_t size, int ma_type);
void lwp_map_area_remove(struct lwp_avl_struct **avl_tree, size_t addr);
struct lwp_avl_struct* lwp_map_find(struct lwp_avl_struct* ptree, size_t addr);
struct lwp_avl_struct* lwp_map_find_first(struct lwp_avl_struct* ptree);
size_t lwp_vmem_count(struct lwp_avl_struct *ptree);

#ifdef __cplusplus
}
#endif

#endif

#endif  /*__LWP_MM_AREA_H__*/
