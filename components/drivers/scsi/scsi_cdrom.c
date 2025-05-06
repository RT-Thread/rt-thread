/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "scsi.blk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scsi_cdrom
{
    struct rt_blk_disk parent;
    struct rt_scsi_device *sdev;

    int cdrom_id;
    struct rt_device_blk_geometry geometry;
};

#define raw_to_scsi_cdrom(raw) rt_container_of(raw, struct scsi_cdrom, parent)

static struct rt_dm_ida cdrom_ida = RT_DM_IDA_INIT(CUSTOM);
static struct rt_dm_ida scsi_cdrom_ida = RT_DM_IDA_INIT(SCSI_CDROM);

static rt_ssize_t scsi_cdrom_read(struct rt_blk_disk *disk, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_err_t err;
    struct scsi_cdrom *scdrom = raw_to_scsi_cdrom(disk);
    struct rt_scsi_device *sdev = scdrom->sdev;

    sector_count &= RT_UINT32_MAX;

    if (sector >> 32)
    {
        err = rt_scsi_read16(sdev, sector, buffer, sector_count);
    }
    else
    {
        err = rt_scsi_read12(sdev, sector, buffer, sector_count);
    }

    return !err ? sector_count : (rt_ssize_t)err;
}

static rt_err_t scsi_cdrom_getgeome(struct rt_blk_disk *disk,
        struct rt_device_blk_geometry *geometry)
{
    struct scsi_cdrom *scdrom = raw_to_scsi_cdrom(disk);

    rt_memcpy(geometry, &scdrom->geometry, sizeof(scdrom->geometry));

    return RT_EOK;
}

static const struct rt_blk_disk_ops scsi_cdrom_ops =
{
    .read = scsi_cdrom_read,
    .getgeome = scsi_cdrom_getgeome,
};

rt_err_t scsi_cdrom_probe(struct rt_scsi_device *sdev)
{
    rt_err_t err;
    union
    {
        struct rt_scsi_read_capacity10_data capacity10;
        struct rt_scsi_read_capacity16_data capacity16;
    } data;
    struct scsi_cdrom *scdrom = rt_calloc(1, sizeof(*scdrom));

    if (!scdrom)
    {
        return -RT_ENOMEM;
    }

    if ((scdrom->cdrom_id = rt_dm_ida_alloc(&cdrom_ida)) < 0)
    {
        return -RT_EFULL;
    }

    sdev->priv = scdrom;
    scdrom->sdev = sdev;
    scdrom->parent.ida = &scsi_cdrom_ida;
    scdrom->parent.read_only = RT_TRUE;
    scdrom->parent.parallel_io = RT_FALSE;
    scdrom->parent.ops = &scsi_cdrom_ops;
    scdrom->parent.max_partitions = RT_BLK_PARTITION_NONE;

    if ((err = rt_scsi_read_capacity10(sdev, &data.capacity10)))
    {
        goto _fail;
    }
    if (data.capacity10.last_block == 0xffffffff)
    {
        if ((err = rt_scsi_read_capacity16(sdev, &data.capacity16)))
        {
            goto _fail;
        }
    }
    scdrom->geometry.bytes_per_sector = sdev->block_size;
    scdrom->geometry.block_size = sdev->block_size;
    scdrom->geometry.sector_count = sdev->last_block + 1;

    rt_dm_dev_set_name(&scdrom->parent.parent, "cdrom%u", scdrom->cdrom_id);

    if ((err = rt_hw_blk_disk_register(&scdrom->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&cdrom_ida, scdrom->cdrom_id);
    rt_free(scdrom);

    return err;
}

rt_err_t scsi_cdrom_remove(struct rt_scsi_device *sdev)
{
    struct scsi_cdrom *scdrom = sdev->priv;

    rt_dm_ida_free(&cdrom_ida, scdrom->cdrom_id);

    return rt_hw_blk_disk_unregister(&scdrom->parent);
}
