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

#ifdef RT_USING_USERSPACE

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    MM_AREA_TYPE_PHY = 0,
    MM_AREA_TYPE_SHM,
    MM_AREA_TYPE_AUTO,
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
