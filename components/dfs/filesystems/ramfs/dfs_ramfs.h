/*
 * File      : dfs_ramfs.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, Shanghai Real-Thread Technology Co., Ltd
 *
 * All rights reserved.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-04-15     Bernard      the first version
 * 2013-05-05     Bernard      remove CRC for ramfs persistence
 */

#ifndef __DFS_ROMFS_H__
#define __DFS_ROMFS_H__

#include <rtthread.h>
#include <rtservice.h>

#define RAMFS_NAME_MAX  32
#define RAMFS_MAGIC		0x0A0A0A0A

struct ramfs_dirent
{
    rt_list_t list;
    char name[RAMFS_NAME_MAX];	/* dirent name */
    rt_uint8_t* data;

    rt_size_t size;	/* file size */
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
