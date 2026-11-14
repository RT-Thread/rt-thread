/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     first version
 */

#ifndef __BLK_DEV_H__
#define __BLK_DEV_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/blk.h>
#include <drivers/misc.h>

#define to_blk_disk(dev)    rt_container_of(dev, struct rt_blk_disk, parent)
#define to_blk(dev)         rt_container_of(dev, struct rt_blk_device, parent)

#ifdef RT_USING_DM
#define to_disk_name(disk)  rt_dm_dev_get_name(&(disk)->parent)
#define to_blk_name(blk)    rt_dm_dev_get_name(&(blk)->parent)
#else
#define to_disk_name(disk)  (disk)->parent.parent.name
#define to_blk_name(blk)    (blk)->parent.parent.name
#endif

/* %c%c name */
#define letter_name(n)      ('a' + (n) / ((n) >= 26 ? (26 * 2) : 1)), ((n) >= 26 ? 'a' + (n) % 26 : '\0')

rt_inline void spin_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

rt_inline void spin_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

rt_err_t blk_dev_initialize(struct rt_blk_device *blk);
rt_err_t disk_add_blk_dev(struct rt_blk_disk *disk, struct rt_blk_device *blk);
rt_err_t disk_remove_blk_dev(struct rt_blk_device *blk, rt_bool_t lockless);

rt_uint32_t blk_request_ioprio(void);

#ifdef RT_USING_LWP
#include <lwp_user_mm.h>

static inline rt_err_t blk_copy_to_user(void *dst, const void *src, size_t n)
{
    if (lwp_self() == RT_NULL)
    {
        rt_memcpy(dst, src, n);
        return RT_EOK;
    }

    if (!lwp_user_accessable(dst, n))
    {
        return -RT_EFAULT;
    }

    if (lwp_put_to_user(dst, (void *)src, n) == 0)
    {
        return -RT_EFAULT;
    }

    return RT_EOK;
}
#endif

static inline rt_err_t blk_get_geometry_k(struct rt_device *dev, struct rt_device_blk_geometry *geo)
{
    struct rt_blk_disk *disk;
    struct rt_blk_device *blk;
    struct rt_device_blk_geometry disk_geo;
    rt_err_t err;

    if (!geo)
    {
        return -RT_EINVAL;
    }

    disk = to_blk_disk(dev);
    if (disk && disk->__magic == RT_BLK_DISK_MAGIC)
    {
        err = disk->ops->getgeome(disk, &disk_geo);
        if (err != RT_EOK)
        {
            return err;
        }
        rt_memcpy(geo, &disk_geo, sizeof(*geo));
        return RT_EOK;
    }

    blk = to_blk(dev);
    if (blk && blk->disk)
    {
        disk = blk->disk;
        err = disk->ops->getgeome(disk, &disk_geo);
        if (err != RT_EOK)
        {
            return err;
        }
        geo->bytes_per_sector = disk_geo.bytes_per_sector;
        geo->block_size = disk_geo.block_size;
        geo->sector_count = blk->sector_count;
        return RT_EOK;
    }

    return -RT_EINVAL;
}

static inline rt_err_t blk_get_total_size_k(struct rt_device *dev, rt_uint64_t *total)
{
    struct rt_blk_disk *disk;
    struct rt_blk_device *blk;
    struct rt_device_blk_geometry disk_geo;
    rt_err_t err;

    if (!total)
    {
        return -RT_EINVAL;
    }

    disk = to_blk_disk(dev);
    if (disk && disk->__magic == RT_BLK_DISK_MAGIC)
    {
        err = disk->ops->getgeome(disk, &disk_geo);
        if (err != RT_EOK)
        {
            return err;
        }
        *total = (rt_uint64_t)disk_geo.bytes_per_sector * disk_geo.sector_count;
        return RT_EOK;
    }

    blk = to_blk(dev);
    if (blk && blk->disk)
    {
        disk = blk->disk;
        err = disk->ops->getgeome(disk, &disk_geo);
        if (err != RT_EOK)
        {
            return err;
        }
        *total = (rt_uint64_t)disk_geo.bytes_per_sector * blk->sector_count;
        return RT_EOK;
    }

    return -RT_EINVAL;
}
#endif /* __BLK_DEV_H__ */
