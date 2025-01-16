/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     first version
 */

#ifndef __BLK_H__
#define __BLK_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/classes/block.h>

struct rt_dm_ida;
struct rt_blk_device;
struct rt_blk_disk_ops;

struct rt_blk_disk
{
    struct rt_device parent;

    const struct rt_blk_disk_ops *ops;
#ifdef RT_USING_DM
    struct rt_dm_ida *ida;
#endif

    rt_uint32_t read_only:1;
    rt_uint32_t parallel_io:1;
    rt_uint32_t removable:1;
#define RT_BLK_DISK_MAGIC 0xbdaabdaa
    rt_uint32_t __magic;

    rt_uint32_t partitions;
#define RT_BLK_PARTITION_NONE (-1)
#define RT_BLK_PARTITION_MAX  (RT_UINT32_MAX >> 1)
    rt_int32_t max_partitions;
    rt_list_t part_nodes;

    struct rt_spinlock lock;
    struct rt_semaphore usr_lock;
};

struct rt_blk_disk_ops
{
    rt_ssize_t (*read)(struct rt_blk_disk *disk, rt_off_t sector, void *buffer,
            rt_size_t sector_count);
    rt_ssize_t (*write)(struct rt_blk_disk *disk, rt_off_t sector, const void *buffer,
            rt_size_t sector_count);
    rt_err_t (*getgeome)(struct rt_blk_disk *disk, struct rt_device_blk_geometry *geometry);
    rt_err_t (*sync)(struct rt_blk_disk *disk);
    rt_err_t (*erase)(struct rt_blk_disk *disk);
    rt_err_t (*autorefresh)(struct rt_blk_disk *disk, rt_bool_t is_auto);
    rt_err_t (*control)(struct rt_blk_disk *disk, struct rt_blk_device *blk, int cmd, void *args);
};

#ifndef __DFS_H__
#include <dfs_fs.h>

struct rt_blk_device
{
    struct rt_device parent;

    int partno;
    struct dfs_partition partition;

    rt_list_t list;
    struct rt_blk_disk *disk;

    rt_size_t sector_start;
    rt_size_t sector_count;
};
#else
struct rt_blk_device;
#endif /* __DFS_H__ */

rt_err_t rt_hw_blk_disk_register(struct rt_blk_disk *disk);
rt_err_t rt_hw_blk_disk_unregister(struct rt_blk_disk *disk);

rt_err_t rt_blk_disk_probe_partition(struct rt_blk_disk *disk);
rt_ssize_t rt_blk_disk_get_capacity(struct rt_blk_disk *disk);
rt_ssize_t rt_blk_disk_get_logical_block_size(struct rt_blk_disk *disk);

#endif /* __BLK_H__ */
