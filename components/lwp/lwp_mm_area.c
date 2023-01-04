/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 */
#include <rtthread.h>

#ifdef ARCH_MM_MMU
#include <lwp_mm_area.h>

int lwp_map_area_insert(struct lwp_avl_struct **avl_tree, size_t addr, size_t size, int ma_type)
{
    struct lwp_avl_struct *node = RT_NULL;
    struct rt_mm_area_struct *ma = RT_NULL;

    if (!size)
    {
        return -1;
    }
    ma = (struct rt_mm_area_struct *)rt_malloc(sizeof(struct rt_mm_area_struct));
    if (!ma)
    {
        return -1;
    }
    ma->addr = addr;
    ma->size = size;
    ma->type = ma_type;

    node = (struct lwp_avl_struct *)rt_malloc(sizeof(struct lwp_avl_struct));
    if (!node)
    {
        rt_free(ma);
        return -1;
    }
    memset(node, 0, sizeof(struct lwp_avl_struct));

    node->avl_key = ma->addr;
    node->data = (void *)ma;
    lwp_avl_insert(node, avl_tree);
    return 0;
}

void lwp_map_area_remove(struct lwp_avl_struct **avl_tree, size_t addr)
{
    struct lwp_avl_struct *node = RT_NULL;

    node = lwp_avl_find(addr, *avl_tree);
    if (!node)
    {
        return;
    }
    lwp_avl_remove(node, avl_tree);
    rt_free(node->data);
    rt_free(node);
}

struct lwp_avl_struct* lwp_map_find(struct lwp_avl_struct* ptree, size_t addr)
{
    struct lwp_avl_struct *node = ptree;

    while (1)
    {
        if (!node)
        {
            return node;
        }
        if ((size_t)node->avl_key <= addr)
        {
            struct rt_mm_area_struct *ma = (struct rt_mm_area_struct *)node->data;
            if ((ma->addr <= addr) && (addr < ma->addr + ma->size))
            {
                /* find area */
                break;
            }
            node = node->avl_right;
        }
        else
        {
            node = node->avl_left;
        }
    }
    return node;
}

struct lwp_avl_struct* lwp_map_find_first(struct lwp_avl_struct* ptree)
{
    if (ptree == AVL_EMPTY)
    {
        return (struct lwp_avl_struct *)0;
    }
    while (1)
    {
        if (!ptree->avl_left)
        {
            break;
        }
        ptree = ptree->avl_left;
    }
    return ptree;
}

int top_mem_fun(struct lwp_avl_struct* ptree, void *arg)
{
    size_t *vs = (size_t *)arg;
    struct rt_mm_area_struct *ma;

    ma = (struct rt_mm_area_struct *)ptree->data;
    *vs += ma->size;
    return 0;
}

size_t lwp_vmem_count(struct lwp_avl_struct *ptree)
{
    size_t vsize = 0;
    lwp_avl_traversal(ptree, top_mem_fun, &vsize);
    return vsize;
}
#endif
