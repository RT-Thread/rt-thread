/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     first version
 */

#include <rtthread.h>
#include <rtdef.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <ext4.h>
#include <ext4_debug.h>
#include <blk_device.h>
#include <stdint.h>

static struct blk_device *blkdev;
static rt_uint32_t disk_sector_size;

static int blockdev_open(struct ext4_blockdev *bdev)
{
    int r;
    uint32_t size;
    rt_device_t device = (rt_device_t)blkdev;
    struct rt_device_blk_geometry geometry;

    RT_ASSERT(device);

    r = rt_device_open((rt_device_t)blkdev, RT_DEVICE_OFLAG_RDWR);

    if (r != RT_EOK)
    {
        return r;
    }

    r = rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

    if (RT_EOK == r)
    {
        bdev->part_offset = 0;
        bdev->part_size = geometry.sector_count * geometry.bytes_per_sector;
        disk_sector_size = geometry.bytes_per_sector;
        bdev->bdif->ph_bcnt = bdev->part_size / bdev->bdif->ph_bsize;
    }

    return r;
}

static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
                          uint32_t blk_cnt)
{
    int result;
    rt_device_t device = (rt_device_t)blkdev;
    struct blk_device *blk = (struct blk_device *)device;
    RT_ASSERT(device);

    result = rt_device_read(device, blk_id * (bdev->bdif->ph_bsize / disk_sector_size),
                            buf, blk_cnt * (bdev->bdif->ph_bsize / disk_sector_size));

    if ((blk_cnt * (bdev->bdif->ph_bsize / disk_sector_size)) == result)
    {
        result = 0;
    }
    else
    {
        result = -EIO;
    }

    return result;
}

static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
                           uint64_t blk_id, uint32_t blk_cnt)
{
    int result;
    rt_device_t device = (rt_device_t)blkdev;

    RT_ASSERT(device);

    result = rt_device_write(device, blk_id * (bdev->bdif->ph_bsize / disk_sector_size),
                             buf, blk_cnt * (bdev->bdif->ph_bsize / disk_sector_size));

    if ((blk_cnt * (bdev->bdif->ph_bsize / disk_sector_size)) == result)
    {
        result = 0;
    }
    else
    {
        result = -EIO;
    }

    return result;
}

static int blockdev_close(struct ext4_blockdev *bdev)
{
    return rt_device_close((rt_device_t)blkdev);
}

static int blockdev_lock(struct ext4_blockdev *bdev)
{
    return 0;
}

static int blockdev_unlock(struct ext4_blockdev *bdev)
{
    return 0;
}

EXT4_BLOCKDEV_STATIC_INSTANCE(bdev, 4096, 0, blockdev_open,
                              blockdev_bread, blockdev_bwrite, blockdev_close,
                              blockdev_lock, blockdev_unlock);

void blk_device_init(struct blk_device *blk_devices)
{
    blkdev = blk_devices;

    if (ext4_mbr_scan(&bdev, &(blkdev->ext4_partition)) != EOK)
    {
        rt_kprintf("MBR scan failed!\n");
        return;
    }
}
