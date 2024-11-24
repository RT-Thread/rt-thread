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

    for (rt_size_t i = 0; i < disk->max_partitions; ++i)
    {
        res = dfs_filesystem_get_partition(&part, sector, i);

        if (res)
        {
            break;
        }

        if (blk_put_partition(disk, "dfs", part.offset, part.size, i) == -RT_ENOMEM)
        {
            break;
        }
    }

    return RT_EOK;
}
