/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */

#ifndef __MM_AVL_ADPT_H__
#define __MM_AVL_ADPT_H__

#include <avl.h>
#include <rtdef.h>
#include <rtthread.h>
#include <stdint.h>

#define VAREA_ENTRY(pnode)                                                     \
    (pnode)                                                                    \
        ? rt_container_of(rt_container_of(pnode, struct _aspace_node, node),   \
                          struct rt_varea, node)                               \
        : 0

#define ASPACE_VAREA_NEXT(pva) (VAREA_ENTRY(util_avl_next(&pva->node.node)))
#define ASPACE_VAREA_FIRST(aspace) (VAREA_ENTRY(util_avl_first(&aspace->tree.tree)))
#define ASPACE_VAREA_LAST(aspace) (VAREA_ENTRY(util_avl_last(&aspace->tree.tree)))
#define ASPACE_VAREA_PREV(pva) (VAREA_ENTRY(util_avl_prev(&pva->node.node)))

typedef struct _aspace_node
{
    struct util_avl_struct node;
} *_aspace_node_t;

typedef struct _aspace_tree
{
    struct util_avl_root tree;
} *_aspace_tree_t;

#endif /* __MM_AVL_ADPT_H__ */
