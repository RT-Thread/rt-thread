/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 * 2022-11-14     WangXiaoyao  Optimize for generic use case
 *                             and performance
 */
#ifndef __UTIL_TREE_AVL_H__
#define __UTIL_TREE_AVL_H__

#include <rtdef.h>
#include <stdint.h>

struct util_avl_struct
{
    struct util_avl_struct *avl_left;
    struct util_avl_struct *avl_right;
    struct util_avl_struct *parent;
    size_t height;
};

#define AVL_ROOT ((struct util_avl_struct *)0)

struct util_avl_root
{
    struct util_avl_struct *root_node;
};

void util_avl_rebalance(struct util_avl_struct *node,
                        struct util_avl_root *root);

void util_avl_remove(struct util_avl_struct *node, struct util_avl_root *root);

static inline void util_avl_link(struct util_avl_struct *new_node,
                                 struct util_avl_struct *parent,
                                 struct util_avl_struct **nodeplace)
{
    new_node->avl_left = AVL_ROOT;
    new_node->avl_right = AVL_ROOT;
    new_node->parent = parent;
    new_node->height = 1;
    *nodeplace = new_node;
}

static inline struct util_avl_struct *util_avl_next(
    struct util_avl_struct *node)
{
    struct util_avl_struct *successor = 0;
    if (node)
    {
        if (node->avl_right)
        {
            node = node->avl_right;
            while (node->avl_left)
                node = node->avl_left;
            successor = node;
        }
        else
        {
            while ((successor = node->parent) && (node == successor->avl_right))
                node = successor;
        }
    }
    return successor;
}

static inline struct util_avl_struct *util_avl_prev(
    struct util_avl_struct *node)
{
    struct util_avl_struct *predecessor = 0;
    if (node)
    {
        if (node->avl_left)
        {
            node = node->avl_left;
            while (node->avl_right)
                node = node->avl_right;
            predecessor = node;
        }
        else
        {
            while ((predecessor = node->parent) &&
                   (node == predecessor->avl_left))
                node = predecessor;
        }
    }
    return predecessor;
}

static inline struct util_avl_struct *util_avl_first(struct util_avl_root *root)
{
    struct util_avl_struct *first = root->root_node;
    if (first)
    {
        while (first->avl_left)
            first = first->avl_left;
    }
    return first;
}

static inline struct util_avl_struct *util_avl_last(struct util_avl_root *root)
{
    struct util_avl_struct *last = root->root_node;
    if (last)
    {
        while (last->avl_right)
            last = last->avl_right;
    }
    return last;
}

#endif /* __UTIL_TREE_AVL_H__ */
