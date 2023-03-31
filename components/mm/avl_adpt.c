/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */
#include <rtdef.h>

#include <avl.h>
#include "avl_adpt.h"
#include "mm_aspace.h"
#include "mm_private.h"

#define DBG_TAG "MM"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief Adapter Layer for lwp AVL BST
 */

rt_err_t _aspace_bst_init(struct rt_aspace *aspace)
{
    aspace->tree.tree.root_node = AVL_ROOT;
    return RT_EOK;
}

static int compare_overlap(void *as, void *ae, void *bs, void *be)
{
    LOG_D("as %lx, ae %lx, bs %lx, be %lx", as, ae, bs, be);
    int cmp;
    if (as > be)
    {
        cmp = 1;
    }
    else if (ae < bs)
    {
        cmp = -1;
    }
    else
    {
        cmp = 0;
    }
    LOG_D("ret %d", cmp);
    return cmp;
}

static int compare_exceed(void *as, void *ae, void *bs, void *be)
{
    LOG_D("as %lx, ae %lx, bs %lx, be %lx", as, ae, bs, be);
    int cmp;
    if (as > bs)
    {
        cmp = 1;
    }
    else if (as < bs)
    {
        cmp = -1;
    }
    else
    {
        cmp = 0;
    }
    LOG_D("ret %d", cmp);
    return cmp;
}

static struct rt_varea *search(struct util_avl_root *root,
                               struct _mm_range range,
                               int (*compare)(void *as, void *ae, void *bs,
                                              void *be))
{
    struct util_avl_struct *node = root->root_node;
    while (node)
    {
        rt_varea_t varea = VAREA_ENTRY(node);
        int cmp = compare(range.start, range.end, varea->start,
                          varea->start + varea->size - 1);

        if (cmp < 0)
        {
            node = node->avl_left;
        }
        else if (cmp > 0)
        {
            node = node->avl_right;
        }
        else
        {
            return varea;
        }
    }
    return NULL;
}

struct rt_varea *_aspace_bst_search(struct rt_aspace *aspace, void *key)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct _mm_range range = {key, key};
    return search(root, range, compare_overlap);
}

rt_varea_t _aspace_bst_search_exceed(struct rt_aspace *aspace, void *start)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct util_avl_struct *node = root->root_node;
    rt_varea_t closest = NULL;
    ptrdiff_t min_off = PTRDIFF_MAX;
    while (node)
    {
        rt_varea_t varea = VAREA_ENTRY(node);
        void *va_s = varea->start;
        int cmp = compare_exceed(start, start, va_s, va_s);

        if (cmp < 0)
        {
            /* varae exceed start */
            ptrdiff_t off = va_s - start;
            if (off < min_off)
            {
                min_off = off;
                closest = varea;
            }
            node = node->avl_left;
        }
        else if (cmp > 0)
        {
            /* find the next huger varea */
            node = node->avl_right;
        }
        else
        {
            return varea;
        }
    }
    return closest;
}

struct rt_varea *_aspace_bst_search_overlap(struct rt_aspace *aspace,
                                            struct _mm_range range)
{
    struct util_avl_root *root = &aspace->tree.tree;
    return search(root, range, compare_overlap);
}

void _aspace_bst_insert(struct rt_aspace *aspace, struct rt_varea *varea)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct util_avl_struct *current = NULL;
    struct util_avl_struct **next = &(root->root_node);
    rt_ubase_t key = (rt_ubase_t)varea->start;

    /* Figure out where to put new node */
    while (*next)
    {
        current = *next;
        struct rt_varea *data = VAREA_ENTRY(current);

        if (key < (rt_ubase_t)data->start)
            next = &(current->avl_left);
        else if (key > (rt_ubase_t)data->start)
            next = &(current->avl_right);
        else
            return;
    }

    /* Add new node and rebalance tree. */
    util_avl_link(&varea->node.node, current, next);
    util_avl_rebalance(current, root);
    return;
}

void _aspace_bst_remove(struct rt_aspace *aspace, struct rt_varea *varea)
{
    struct util_avl_struct *node = &varea->node.node;
    util_avl_remove(node, &aspace->tree.tree);
}
