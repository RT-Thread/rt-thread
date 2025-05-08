/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     flybreak     the first version
 */

#ifndef __DFS_TMPFS_H__
#define __DFS_TMPFS_H__

#include <rtthread.h>
#include <dfs_vfs.h>

#define TMPFS_NAME_MAX  32
#define TMPFS_MAGIC     0x0B0B0B0B

#define TMPFS_TYPE_FILE   0x00
#define TMPFS_TYPE_DIR    0x01

struct tmpfs_sb;

struct tmpfs_file
{
    rt_uint32_t      type;     /* file type */
    char name[TMPFS_NAME_MAX]; /* file name */
    struct dfs_vfs_node node;  /* file node in the tmpfs */
    struct tmpfs_sb *sb;       /* superblock ptr */
    rt_uint8_t      *data;     /* file date ptr */
    rt_size_t        size;     /* file size */
    rt_bool_t       fre_memory;/* Whether to release memory upon close */
};


struct tmpfs_sb
{
    rt_uint32_t       magic;       /* TMPFS_MAGIC */
    struct tmpfs_file root;        /* root dir */
    rt_size_t         df_size;     /* df size */
    rt_list_t         sibling;     /* sb sibling list */
    struct rt_spinlock lock;       /* tmpfs lock */
};

int dfs_tmpfs_init(void);

#endif

