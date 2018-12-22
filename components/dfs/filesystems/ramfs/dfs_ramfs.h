/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-04-15     Bernard      the first version
 * 2013-05-05     Bernard      remove CRC for ramfs persistence
 */

#ifndef __DFS_RAMFS_H__
#define __DFS_RAMFS_H__

#include <rtthread.h>
#include <rtservice.h>

#define RAMFS_NAME_MAX  32
#define RAMFS_MAGIC     0x0A0A0A0A

struct ramfs_dirent
{
    rt_list_t list;
    struct dfs_ramfs *fs;       /* file system ref */

    char name[RAMFS_NAME_MAX];  /* dirent name */
    rt_uint8_t* data;

    rt_size_t size;             /* file size */
};

/**
 * DFS ramfs object
 */
struct dfs_ramfs
{
    rt_uint32_t magic;

    struct rt_memheap memheap;
    struct ramfs_dirent root;
};

int dfs_ramfs_init(void);
struct dfs_ramfs* dfs_ramfs_create(rt_uint8_t* pool, rt_size_t size);

#endif

