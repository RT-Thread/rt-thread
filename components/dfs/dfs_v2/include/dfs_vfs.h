/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DFS_VFS_H__
#define __DFS_VFS_H__

#include "dfs_file.h"
#include "dfs_fs.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct dfs_vfs_node
{
    rt_list_t     subnode;     /* file subnode list */
    rt_list_t     sibling;     /* file sibling list */
};

rt_inline void dfs_vfs_init_node(struct dfs_vfs_node *node)
{
    rt_list_init(&node->subnode);
    rt_list_init(&node->sibling);
}

rt_inline void dfs_vfs_append_node(struct dfs_vfs_node *dir, struct dfs_vfs_node *node)
{
    rt_list_insert_after(&(dir->subnode), &(node->sibling));
}

rt_inline void dfs_vfs_remove_node(struct dfs_vfs_node *node)
{
    rt_list_remove(&(node->sibling));
}

#define dfs_vfs_for_each_subnode(node, tmp, dir, member)                          \
    rt_list_for_each_entry_safe(node, tmp, &dir->member.subnode, member.sibling)

#ifdef __cplusplus
}
#endif

#endif /*__DFS_VFS_H__*/
