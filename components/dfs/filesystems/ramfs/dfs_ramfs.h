/*
 * File      : dfs_ramfs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
