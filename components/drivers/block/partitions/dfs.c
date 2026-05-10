/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 * 2023-02-25     GuEe-GUI      make blk interface
 */

#include "efi.h"

#define DBG_TAG "blk.part.dfs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t dfs_partition(struct rt_blk_disk *disk)
{
    rt_ssize_t res;
    struct dfs_partition part;
    rt_uint8_t *sector = rt_malloc(rt_blk_disk_get_logical_block_size(disk));

    if (!sector)
    {
        return -RT_ENOMEM;
    }

    res = disk->ops->read(disk, 0, sector, 1);

    if (res < 0)
    {
        rt_free(sector);
        return res;
    }

    /* check MBR signature at offset 0x1FE-0x1FF */
    if (sector[0x1FE] != 0x55 || sector[0x1FF] != 0xAA)
    {
        rt_free(sector);
        return -RT_ERROR;
    }

    /* get disk total capacity */
    rt_ssize_t disk_capacity = rt_blk_disk_get_capacity(disk);
    if (disk_capacity <= 0)
    {
        rt_free(sector);
        return disk_capacity < 0 ? disk_capacity : -RT_ERROR;
    }

    for (rt_size_t i = 0; i < disk->max_partitions; ++i)
    {
        res = dfs_filesystem_get_partition(&part, sector, i);

        if (res)
        {
            break;
        }

        /* check if partition start and size are within disk capacity */
        off_t part_start = part.offset;
        size_t part_size = part.size;
        off_t part_end = part_start + (off_t)part_size;

        if (part_start >= (off_t)disk_capacity)
        {
            LOG_W("Partition %d: start sector %ld >= disk capacity %ld, skipped",
                  i, part_start, disk_capacity);
            continue;
        }

        if (part_size == 0 || part_end > (off_t)disk_capacity)
        {
            LOG_W("Partition %d: size %lu or end sector %ld > disk capacity %ld, skipped",
                  i, part_size, part_end, disk_capacity);
            continue;
        }

        if (blk_put_partition(disk, "dfs", part.offset, part.size, i) == -RT_ENOMEM)
        {
            break;
        }
    }

    rt_free(sector);

    return RT_EOK;
}
