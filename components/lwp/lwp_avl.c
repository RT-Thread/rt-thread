/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 */
#include <rtthread.h>
#include <lwp_avl.h>

static void lwp_avl_rebalance(struct lwp_avl_struct ***nodeplaces_ptr, int count)
{
    for (; count > 0; count--)
    {
        struct lwp_avl_struct **nodeplace = *--nodeplaces_ptr;
        struct lwp_avl_struct *node = *nodeplace;
        struct lwp_avl_struct *nodeleft = node->avl_left;
        struct lwp_avl_struct *noderight = node->avl_right;
        int heightleft = heightof(nodeleft);
        int heightright = heightof(noderight);
        if (heightright + 1 < heightleft)
        {
            struct lwp_avl_struct *nodeleftleft = nodeleft->avl_left;
            struct lwp_avl_struct *nodeleftright = nodeleft->avl_right;
            int heightleftright = heightof(nodeleftright);
            if (heightof(nodeleftleft) >= heightleftright)
            {
                node->avl_left = nodeleftright;
                nodeleft->avl_right = node;
                nodeleft->avl_height = 1 + (node->avl_height = 1 + heightleftright);
                *nodeplace = nodeleft;
            }
            else
            {
                nodeleft->avl_right = nodeleftright->avl_left;
                node->avl_left = nodeleftright->avl_right;
                nodeleftright->avl_left = nodeleft;
                nodeleftright->avl_right = node;
                nodeleft->avl_height = node->avl_height = heightleftright;
                nodeleftright->avl_height = heightleft;
                *nodeplace = nodeleftright;
            }
        }
        else if (heightleft + 1 < heightright)
        {
            struct lwp_avl_struct *noderightright = noderight->avl_right;
            struct lwp_avl_struct *noderightleft = noderight->avl_left;
            int heightrightleft = heightof(noderightleft);
            if (heightof(noderightright) >= heightrightleft)
            {
                node->avl_right = noderightleft;
                noderight->avl_left = node;
                noderight->avl_height = 1 + (node->avl_height = 1 + heightrightleft);
                *nodeplace = noderight;
            }
            else
            {
                noderight->avl_left = noderightleft->avl_right;
                node->avl_right = noderightleft->avl_left;
                noderightleft->avl_right = noderight;
                noderightleft->avl_left = node;
                noderight->avl_height = node->avl_height = heightrightleft;
                noderightleft->avl_height = heightright;
                *nodeplace = noderightleft;
            }
        }
        else
        {
            int height = (heightleft < heightright ? heightright : heightleft) + 1;
            if (height == node->avl_height)
                break;
            node->avl_height = height;
        }
    }
}

void lwp_avl_remove(struct lwp_avl_struct *node_to_delete, struct lwp_avl_struct **ptree)
{
    avl_key_t key = node_to_delete->avl_key;
    struct lwp_avl_struct **nodeplace = ptree;
    struct lwp_avl_struct **stack[avl_maxheight];
    uint32_t stack_count = 0;
    struct lwp_avl_struct ***stack_ptr = &stack[0]; /* = &stack[stackcount] */
    struct lwp_avl_struct **nodeplace_to_delete;
    for (;;)
    {
        struct lwp_avl_struct *node = *nodeplace;
        if (node == AVL_EMPTY)
        {
            return;
        }

        *stack_ptr++ = nodeplace;
        stack_count++;
        if (key == node->avl_key)
            break;
        if (key < node->avl_key)
            nodeplace = &node->avl_left;
        else
            nodeplace = &node->avl_right;
    }
    nodeplace_to_delete = nodeplace;
    if (node_to_delete->avl_left == AVL_EMPTY)
    {
        *nodeplace_to_delete = node_to_delete->avl_right;
        stack_ptr--;
        stack_count--;
    }
    else
    {
        struct lwp_avl_struct ***stack_ptr_to_delete = stack_ptr;
        struct lwp_avl_struct **nodeplace = &node_to_delete->avl_left;
        struct lwp_avl_struct *node;
        for (;;)
        {
            node = *nodeplace;
            if (node->avl_right == AVL_EMPTY)
                break;
            *stack_ptr++ = nodeplace;
            stack_count++;
            nodeplace = &node->avl_right;
        }
        *nodeplace = node->avl_left;
        node->avl_left = node_to_delete->avl_left;
        node->avl_right = node_to_delete->avl_right;
        node->avl_height = node_to_delete->avl_height;
        *nodeplace_to_delete = node;
        *stack_ptr_to_delete = &node->avl_left;
    }
    lwp_avl_rebalance(stack_ptr, stack_count);
}

void lwp_avl_insert(struct lwp_avl_struct *new_node, struct lwp_avl_struct **ptree)
{
    avl_key_t key = new_node->avl_key;
    struct lwp_avl_struct **nodeplace = ptree;
    struct lwp_avl_struct **stack[avl_maxheight];
    int stack_count = 0;
    struct lwp_avl_struct ***stack_ptr = &stack[0]; /* = &stack[stackcount] */
    for (;;)
    {
        struct lwp_avl_struct *node = *nodeplace;
        if (node == AVL_EMPTY)
            break;
        *stack_ptr++ = nodeplace;
        stack_count++;
        if (key < node->avl_key)
            nodeplace = &node->avl_left;
        else
            nodeplace = &node->avl_right;
    }
    new_node->avl_left = AVL_EMPTY;
    new_node->avl_right = AVL_EMPTY;
    new_node->avl_height = 1;
    *nodeplace = new_node;
    lwp_avl_rebalance(stack_ptr, stack_count);
}

struct lwp_avl_struct *lwp_avl_find(avl_key_t key, struct lwp_avl_struct *ptree)
{
    for (;;)
    {
        if (ptree == AVL_EMPTY)
        {
            return (struct lwp_avl_struct *)0;
        }
        if (key == ptree->avl_key)
            break;
        if (key < ptree->avl_key)
            ptree = ptree->avl_left;
        else
            ptree = ptree->avl_right;
    }
    return ptree;
}

int lwp_avl_traversal(struct lwp_avl_struct *ptree, int (*fun)(struct lwp_avl_struct *, void *), void *arg)
{
    int ret;

    if (!ptree)
    {
        return 0;
    }
    if (ptree->avl_left)
    {
        ret = lwp_avl_traversal(ptree->avl_left, fun, arg);
        if (ret != 0)
        {
            return ret;
        }
    }
    ret = (*fun)(ptree, arg);
    if (ret != 0)
    {
        return ret;
    }
    if (ptree->avl_right)
    {
        ret = lwp_avl_traversal(ptree->avl_right, fun, arg);
        if (ret != 0)
        {
            return ret;
        }
    }
    return ret;
}

rt_weak struct lwp_avl_struct* lwp_map_find_first(struct lwp_avl_struct* ptree)
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

