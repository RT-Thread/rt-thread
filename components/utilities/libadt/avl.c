/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 * 2022-11-14     WangXiaoyao  Optimize footprint and performance
 *                             Export as ADT for generic use case
 */
#include <stddef.h>
#include <stdint.h>

#include "avl.h"

#define HEIGHT_OF(node) ((node) ? (node)->height : 0)
#define IS_RCHILD(node) (!((node) - ((node)->parent->avl_right)))
#define IS_LCHILD(node) (!((node) - ((node)->parent->avl_left)))
#define NODE_PLACE(node)                                                       \
    IS_LCHILD(node) ? &(node)->parent->avl_left : &(node)->parent->avl_right

static inline void rotate_right(struct util_avl_struct *axis,
                                struct util_avl_struct *lchild,
                                struct util_avl_struct *lrchild,
                                struct util_avl_struct **nodeplace,
                                size_t lrheight)
{
    axis->avl_left = lrchild;
    lchild->avl_right = axis;

    axis->height = lrheight + 1;
    lchild->height = axis->height + 1;

    lchild->parent = axis->parent;
    axis->parent = lchild;

    *nodeplace = lchild;
    if (lrchild != NULL)
        lrchild->parent = axis;
}

static inline void midmount_right(struct util_avl_struct *axis,
                                  struct util_avl_struct *lchild,
                                  struct util_avl_struct *lrchild,
                                  struct util_avl_struct **nodeplace,
                                  size_t lrheight)
{
    lchild->avl_right = lrchild->avl_left;
    axis->avl_left = lrchild->avl_right;
    lrchild->avl_left = lchild;
    lrchild->avl_right = axis;

    lrchild->height = lchild->height;
    lchild->height = lrheight;
    axis->height = lrheight;

    lrchild->parent = axis->parent;
    lchild->parent = lrchild;
    axis->parent = lrchild;
    if (lchild->avl_right != NULL)
        lchild->avl_right->parent = lchild;
    if (axis->avl_left != NULL)
        axis->avl_left->parent = axis;
    *nodeplace = lrchild;
}

static inline void rotate_left(struct util_avl_struct *axis,
                               struct util_avl_struct *rchild,
                               struct util_avl_struct *rlchild,
                               struct util_avl_struct **nodeplace,
                               size_t rlheight)
{
    axis->avl_right = rlchild;
    rchild->avl_left = axis;

    axis->height = rlheight + 1;
    rchild->height = axis->height + 1;

    rchild->parent = axis->parent;
    axis->parent = rchild;

    *nodeplace = rchild;
    if (rlchild != NULL)
        rlchild->parent = axis;
}

static inline void midmount_left(struct util_avl_struct *axis,
                                 struct util_avl_struct *rchild,
                                 struct util_avl_struct *rlchild,
                                 struct util_avl_struct **nodeplace,
                                 size_t rlheight)
{
    rchild->avl_left = rlchild->avl_right;
    axis->avl_right = rlchild->avl_left;
    rlchild->avl_right = rchild;
    rlchild->avl_left = axis;

    rlchild->height = rchild->height;
    rchild->height = rlheight;
    axis->height = rlheight;

    rlchild->parent = axis->parent;
    rchild->parent = rlchild;
    axis->parent = rlchild;
    if (rchild->avl_left != NULL)
        rchild->avl_left->parent = rchild;
    if (axis->avl_right != NULL)
        axis->avl_right->parent = axis;

    *nodeplace = rlchild;
}

/**
 * @brief avl insertion & delete conceptually contain 2 stage
 * 1. insertion/delete of reference
 * 2. rebalance
 */

void util_avl_rebalance(struct util_avl_struct *node,
                        struct util_avl_root *root)
{
    if (!node)
        return;

    struct util_avl_struct *axis = node;
    struct util_avl_struct **nodeplace;
    do
    {
        struct util_avl_struct *lchild = axis->avl_left;
        struct util_avl_struct *rchild = axis->avl_right;
        nodeplace = axis->parent ? NODE_PLACE(axis) : &root->root_node;
        int lheight = HEIGHT_OF(lchild);
        int rheight = HEIGHT_OF(rchild);
        if (rheight + 1 < lheight)
        {
            struct util_avl_struct *lrchild = lchild->avl_right;
            size_t lrheight = HEIGHT_OF(lrchild);
            if (HEIGHT_OF(lchild->avl_left) >= lrheight)
            {
                rotate_right(axis, lchild, lrchild, nodeplace, lrheight);
                axis = lchild->parent;
            }
            else
            {
                midmount_right(axis, lchild, lrchild, nodeplace, lrheight);
                axis = lrchild->parent;
            }
        }
        else if (lheight + 1 < rheight)
        {
            struct util_avl_struct *rlchild = rchild->avl_left;
            size_t rlheight = HEIGHT_OF(rlchild);
            if (HEIGHT_OF(rchild->avl_right) >= rlheight)
            {
                rotate_left(axis, rchild, rlchild, nodeplace, rlheight);
                axis = rchild->parent;
            }
            else
            {
                midmount_left(axis, rchild, rlchild, nodeplace, rlheight);
                axis = rlchild->parent;
            }
        }
        else
        {
            int height = (lheight < rheight ? rheight : lheight) + 1;
            if (height == axis->height)
                break;
            axis->height = height;
            axis = axis->parent;
        }
    } while (axis);
}

void util_avl_remove(struct util_avl_struct *node, struct util_avl_root *root)
{
    struct util_avl_struct **nodeplace;

    if (root->root_node == NULL)
        return;

    if (node->parent != NULL)
    {
        nodeplace = NODE_PLACE(node);
    }
    else
    {
        nodeplace = &root->root_node;
    }

    /* deletion */
    if (node->avl_right == NULL)
    {
        *nodeplace = node->avl_left;
        if (node->avl_left != NULL)
            node->avl_left->parent = node->parent;
        node = node->parent;
    }
    else
    {
        struct util_avl_struct *rchild = node->avl_right;
        if (rchild->avl_left == NULL)
        {
            *nodeplace = rchild;
            rchild->avl_left = node->avl_left;
            if (rchild->avl_left != NULL)
                rchild->avl_left->parent = rchild;
            rchild->parent = node->parent;
            util_avl_rebalance(rchild, root);
            node = rchild->parent;
        }
        else
        {
            struct util_avl_struct *successor = rchild->avl_left;
            struct util_avl_struct *sparent = rchild;
            while (successor->avl_left != NULL)
            {
                sparent = successor;
                successor = successor->avl_left;
            }
            *nodeplace = successor;
            sparent->avl_left = successor->avl_right;
            successor->avl_left = node->avl_left;
            successor->avl_right = node->avl_right;

            if (successor->avl_left != NULL)
                successor->avl_left->parent = successor;
            successor->avl_right->parent = successor;

            if (sparent->avl_left != NULL)
                sparent->avl_left->parent = sparent;
            successor->parent = node->parent;
            util_avl_rebalance(sparent, root);
            node = successor;
        }
    }

    /* rebalance */
    util_avl_rebalance(node, root);
    return;
}
