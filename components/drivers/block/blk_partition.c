/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#define DBG_TAG "blk.part"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "blk_partition.h"

static rt_err_t (*partition_list[])(struct rt_blk_disk *) =
{
#ifdef RT_BLK_PARTITION_EFI
    efi_partition,
#endif
#ifdef RT_BLK_PARTITION_DFS
    dfs_partition,
#endif
};

rt_err_t blk_put_partition(struct rt_blk_disk *disk, const char *type,
        rt_size_t start, rt_size_t count, int partno)
{
    rt_err_t err;

    struct rt_blk_device *blk = rt_calloc(1, sizeof(*blk));

    if (type && rt_strcmp(type, "dfs"))
    {
        rt_uint32_t ssz = rt_blk_disk_get_logical_block_size(disk);

        rt_kprintf("found part[%u], begin: %lu, size: ", partno, start * ssz);

        if ((count >> 11) == 0)
        {
            rt_kprintf("%u%cB\n", count >> 1, 'K'); /* KB */
        }
        else
        {
            rt_uint32_t size_mb = count >> 11;      /* MB */

            if ((size_mb >> 10) == 0)
            {
                rt_kprintf("%u.%u%cB\n", size_mb, (count >> 1) & 0x3ff, 'M');
            }
            else
            {
                rt_kprintf("%u.%u%cB\n", size_mb >> 10, size_mb & 0x3ff, 'G');
            }
        }
    }

    if (!blk)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    err = blk_dev_initialize(blk);

    if (err)
    {
        goto _fail;
    }

    blk->partno = partno;
    blk->sector_start = start;
    blk->sector_count = count;

    blk->partition.offset = start;
    blk->partition.size = count;
    blk->partition.lock = &disk->usr_lock;

    err = disk_add_blk_dev(disk, blk);

    if (err)
    {
        goto _fail;
    }

    ++disk->partitions;

    return RT_EOK;

_fail:
    LOG_E("%s: Put partition.%s[%u] start = %lu count = %lu error = %s",
            to_disk_name(disk), type, partno, start, count, rt_strerror(err));

    if (blk)
    {
        rt_free(blk);
    }

    return err;
}

rt_err_t rt_blk_disk_probe_partition(struct rt_blk_disk *disk)
{
    rt_err_t err = RT_EOK;

    if (!disk)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s: Probing disk partitions", to_disk_name(disk));

    if (disk->partitions)
    {
        return err;
    }

    err = -RT_EEMPTY;

    if (disk->max_partitions == RT_BLK_PARTITION_NONE)
    {
        LOG_D("%s: Unsupported partitions", to_disk_name(disk));

        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(partition_list); ++i)
    {
        rt_err_t part_err = partition_list[i](disk);

        if (part_err == -RT_ENOMEM)
        {
            err = part_err;
            break;
        }

        if (!part_err)
        {
            err = RT_EOK;
            break;
        }
    }

    if ((err && err != -RT_ENOMEM) || disk->partitions == 0)
    {
        /* No partition found */
        rt_size_t total_sectors = rt_blk_disk_get_capacity(disk);

        err = blk_put_partition(disk, RT_NULL, 0, total_sectors, 0);
    }

    return err;
}
