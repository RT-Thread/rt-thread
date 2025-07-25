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

#include "../block/blk_dev.h"

struct scsi_sd
{
    struct rt_blk_disk parent;
    struct rt_scsi_device *sdev;

    int sd_id;
    rt_bool_t use16;
    struct rt_device_blk_geometry geometry;
};

#define raw_to_scsi_sd(raw) rt_container_of(raw, struct scsi_sd, parent)

static struct rt_dm_ida sd_ida = RT_DM_IDA_INIT(CUSTOM);
static struct rt_dm_ida scsi_sd_ida = RT_DM_IDA_INIT(SCSI_SD);

static rt_ssize_t scsi_sd_read(struct rt_blk_disk *disk, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_err_t err;
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);
    struct rt_scsi_device *sdev = ssd->sdev;

    sector_count &= RT_UINT32_MAX;

    if (sector >> 32)
    {
        err = rt_scsi_read16(sdev, sector, buffer, sector_count);
    }
    else
    {
        err = rt_scsi_read10(sdev, sector, buffer, sector_count);
    }

    return !err ? sector_count : (rt_ssize_t)err;
}

static rt_ssize_t scsi_sd_write(struct rt_blk_disk *disk, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    rt_err_t err;
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);
    struct rt_scsi_device *sdev = ssd->sdev;

    sector_count &= RT_UINT32_MAX;

    if (sector >> 32)
    {
        err = rt_scsi_write16(sdev, sector, buffer, sector_count);
    }
    else
    {
        err = rt_scsi_write10(sdev, sector, buffer, sector_count);
    }

    return !err ? sector_count : (rt_ssize_t)err;
}

static rt_err_t scsi_sd_getgeome(struct rt_blk_disk *disk,
        struct rt_device_blk_geometry *geometry)
{
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);

    rt_memcpy(geometry, &ssd->geometry, sizeof(ssd->geometry));

    return RT_EOK;
}

static rt_err_t scsi_sd_sync(struct rt_blk_disk *disk)
{
    rt_err_t err;
    rt_size_t lba_count;
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);
    struct rt_scsi_device *sdev = ssd->sdev;

    lba_count = ssd->geometry.sector_count;

    if (ssd->use16)
    {
        err = rt_scsi_synchronize_cache16(sdev, 0, lba_count);
    }
    else
    {
        err = rt_scsi_synchronize_cache10(sdev, 0, lba_count);
    }

    return err;
}

static rt_err_t scsi_sd_erase(struct rt_blk_disk *disk)
{
    rt_err_t err;
    rt_size_t lba_count;
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);
    struct rt_scsi_device *sdev = ssd->sdev;

    lba_count = ssd->geometry.sector_count;

    if (ssd->use16)
    {
        err = rt_scsi_write_same16(sdev, 0, lba_count);
    }
    else
    {
        err = rt_scsi_write_same10(sdev, 0, lba_count);
    }

    return err;
}

static rt_err_t scsi_sd_autorefresh(struct rt_blk_disk *disk, rt_bool_t is_auto)
{
    rt_err_t err;
    int sp;
    rt_size_t size;
    rt_uint8_t buffer[64];
    rt_uint8_t *buffer_data;
    rt_bool_t use6 = RT_TRUE;
    struct scsi_sd *ssd = raw_to_scsi_sd(disk);
    struct rt_scsi_device *sdev = ssd->sdev;
    struct rt_scsi_mode_select_data data;

    err = rt_scsi_mode_sense6(sdev, 0x08, 8, 0, buffer, sizeof(buffer), &data);

    if (err && err != -RT_ENOMEM)
    {
        use6 = RT_FALSE;
        err = rt_scsi_mode_sense10(sdev, 0x08, 8, 0, buffer, sizeof(buffer), &data);
    }
    if (err)
    {
        return err;
    }

    size = rt_min_t(rt_size_t, sizeof(buffer),
            data.length - data.header_length - data.block_descriptor_length);
    buffer_data = buffer + data.header_length + data.block_descriptor_length;
    buffer_data[2] &= ~0x05;
    buffer_data[2] |= (!!is_auto) << 2 | (!!is_auto);
    sp = buffer_data[0] & 0x80 ? 1 : 0;
    buffer_data[0] &= ~0x80;
    data.device_specific = 0;

    if (use6)
    {
        err = rt_scsi_mode_select6(sdev, 1, sp, buffer_data, size, &data);
    }
    else
    {
        err = rt_scsi_mode_select10(sdev, 1, sp, buffer_data, size, &data);
    }

    return err;
}

static const struct rt_blk_disk_ops scsi_sd_ops =
{
    .read = scsi_sd_read,
    .write = scsi_sd_write,
    .getgeome = scsi_sd_getgeome,
    .sync = scsi_sd_sync,
    .erase = scsi_sd_erase,
    .autorefresh = scsi_sd_autorefresh,
};

rt_err_t scsi_sd_probe(struct rt_scsi_device *sdev)
{
    rt_err_t err;
    union
    {
        struct rt_scsi_read_capacity10_data capacity10;
        struct rt_scsi_read_capacity16_data capacity16;
    } data;
    struct scsi_sd *ssd = rt_calloc(1, sizeof(*ssd));

    if (!ssd)
    {
        return -RT_ENOMEM;
    }

    if ((ssd->sd_id = rt_dm_ida_alloc(&sd_ida)) < 0)
    {
        return -RT_EFULL;
    }

    sdev->priv = ssd;
    ssd->sdev = sdev;
    ssd->parent.ida = &scsi_sd_ida;
    ssd->parent.parallel_io = RT_FALSE;
    ssd->parent.ops = &scsi_sd_ops;
    ssd->parent.max_partitions = RT_BLK_PARTITION_MAX;

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
        ssd->use16 = RT_TRUE;
    }
    ssd->geometry.bytes_per_sector = sdev->block_size;
    ssd->geometry.block_size = sdev->block_size;
    ssd->geometry.sector_count = sdev->last_block + 1;

    rt_dm_dev_set_name(&ssd->parent.parent, "sd%c%c", letter_name(ssd->sd_id));

    if ((err = rt_hw_blk_disk_register(&ssd->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&sd_ida, ssd->sd_id);
    rt_free(ssd);

    return err;
}

rt_err_t scsi_sd_remove(struct rt_scsi_device *sdev)
{
    struct scsi_sd *ssd = sdev->priv;

    rt_dm_ida_free(&sd_ida, ssd->sd_id);

    return rt_hw_blk_disk_unregister(&ssd->parent);
}
