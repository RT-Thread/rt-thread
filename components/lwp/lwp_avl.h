/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 */
#ifndef  LWP_AVL_H__
#define  LWP_AVL_H__

#include <rtthread.h>

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define avl_key_t       size_t
#define AVL_EMPTY       (struct lwp_avl_struct *)0
#define avl_maxheight   32
#define heightof(tree)  ((tree) == AVL_EMPTY ? 0 : (tree)->avl_height)

struct lwp_avl_struct
{
    struct lwp_avl_struct *avl_left;
    struct lwp_avl_struct *avl_right;
    int    avl_height;
    avl_key_t avl_key;
    void *data;
};

void lwp_avl_remove(struct lwp_avl_struct * node_to_delete, struct lwp_avl_struct ** ptree);
void lwp_avl_insert (struct lwp_avl_struct * new_node, struct lwp_avl_struct ** ptree);
struct lwp_avl_struct* lwp_avl_find(avl_key_t key, struct lwp_avl_struct* ptree);
int lwp_avl_traversal(struct lwp_avl_struct* ptree, int (*fun)(struct lwp_avl_struct*, void *), void *arg);
struct lwp_avl_struct* lwp_map_find_first(struct lwp_avl_struct* ptree);

#ifdef __cplusplus
}
#endif

#endif  /* LWP_AVL_H__ */
