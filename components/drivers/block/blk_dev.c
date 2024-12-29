/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     first version
 */

#include "blk_dev.h"
#include "blk_dfs.h"

#define DBG_TAG "blk.dm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

static rt_err_t blk_dev_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_blk_device *blk = to_blk(dev);

    return rt_device_open(&blk->disk->parent, oflag);
}

static rt_err_t blk_dev_close(rt_device_t dev)
{
    struct rt_blk_device *blk = to_blk(dev);

    return rt_device_close(&blk->disk->parent);
}

static rt_ssize_t blk_dev_read(rt_device_t dev, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    struct rt_blk_device *blk = to_blk(dev);

    if (sector <= blk->sector_start + blk->sector_count &&
        sector_count <= blk->sector_count)
    {
        return rt_device_read(&blk->disk->parent,
                blk->sector_start + sector, buffer, sector_count);
    }

    return -RT_EINVAL;
}

static rt_ssize_t blk_dev_write(rt_device_t dev, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    struct rt_blk_device *blk = to_blk(dev);

    if (sector <= blk->sector_start + blk->sector_count &&
        sector_count <= blk->sector_count)
    {
        return rt_device_write(&blk->disk->parent,
                blk->sector_start + sector, buffer, sector_count);
    }

    return -RT_EINVAL;
}

static rt_err_t blk_dev_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_blk_device *blk = to_blk(dev);
    struct rt_blk_disk *disk = blk->disk;
    struct rt_device_blk_geometry disk_geometry, *geometry;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        if ((geometry = args))
        {
            if (!(err = disk->ops->getgeome(disk, &disk_geometry)))
            {
                geometry->bytes_per_sector = disk_geometry.bytes_per_sector;
                geometry->block_size = disk_geometry.block_size;
                geometry->sector_count = blk->sector_count;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }

        break;

    case RT_DEVICE_CTRL_BLK_SYNC:
        rt_device_control(&disk->parent, cmd, args);
        break;

    case RT_DEVICE_CTRL_BLK_ERASE:
    case RT_DEVICE_CTRL_BLK_AUTOREFRESH:
        if (disk->partitions <= 1)
        {
            rt_device_control(&disk->parent, cmd, args);
        }
        else
        {
            err = -RT_EIO;
        }
        break;

    case RT_DEVICE_CTRL_BLK_PARTITION:
        if (args)
        {
            rt_memcpy(args, &blk->partition, sizeof(blk->partition));
        }
        else
        {
            err = -RT_EINVAL;
        }

        break;

    case RT_DEVICE_CTRL_BLK_SSIZEGET:
        device_get_blk_ssize(dev, args);
        err = RT_EOK;
        break;

    case RT_DEVICE_CTRL_ALL_BLK_SSIZEGET:
        device_get_all_blk_ssize(dev, args);
        err = RT_EOK;
        break;

    default:
        if (disk->ops->control)
        {
            err = disk->ops->control(disk, blk, cmd, args);
        }
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops blk_dev_ops =
{
    .open = blk_dev_open,
    .close = blk_dev_close,
    .read = blk_dev_read,
    .write = blk_dev_write,
    .control = blk_dev_control,
};
#endif

rt_err_t blk_dev_initialize(struct rt_blk_device *blk)
{
    struct rt_device *dev;

    if (!blk)
    {
        return -RT_EINVAL;
    }

    dev = &blk->parent;
    dev->type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    dev->ops = &blk_dev_ops;
#else
    dev->open = blk_dev_open;
    dev->close = blk_dev_close;
    dev->read = blk_dev_read;
    dev->write = blk_dev_write;
    dev->control = blk_dev_control;
#endif

    return RT_EOK;
}

rt_err_t disk_add_blk_dev(struct rt_blk_disk *disk, struct rt_blk_device *blk)
{
    rt_err_t err;
#ifdef RT_USING_DM
    int device_id;
#endif
    const char *disk_name, *name_fmt;

    if (!disk || !blk)
    {
        return -RT_EINVAL;
    }

#ifdef RT_USING_DM
    if ((device_id = rt_dm_ida_alloc(disk->ida)) < 0)
    {
        return -RT_EFULL;
    }
#endif

    blk->disk = disk;
    rt_list_init(&blk->list);

    disk_name = to_disk_name(disk);

    /* End is [a-zA-Z] or [0-9] */
    if (disk_name[rt_strlen(disk_name) - 1] < 'a')
    {
        name_fmt = "%sp%d";
    }
    else
    {
        name_fmt = "%s%d";
    }

#ifdef RT_USING_DM
    rt_dm_dev_set_name(&blk->parent, name_fmt, disk_name, blk->partno);
    blk->parent.master_id = disk->ida->master_id;
    blk->parent.device_id = device_id;
#else
    rt_snprintf(blk->parent.parent.name, RT_NAME_MAX, name_fmt, disk_name, blk->partno);
#endif
    device_set_blk_fops(&blk->parent);

    err = rt_device_register(&blk->parent, to_blk_name(blk),
            disk->parent.flag & RT_DEVICE_FLAG_RDWR);

    if (err)
    {
    #ifdef RT_USING_DM
        rt_dm_ida_free(disk->ida, device_id);
    #endif
        return err;
    }

    spin_lock(&disk->lock);

    rt_list_insert_before(&disk->part_nodes, &blk->list);

    spin_unlock(&disk->lock);

    return RT_EOK;
}

rt_err_t disk_remove_blk_dev(struct rt_blk_device *blk, rt_bool_t lockless)
{
    struct rt_blk_disk *disk;

    if (!blk)
    {
        return -RT_EINVAL;
    }

    disk = blk->disk;

    if (!disk)
    {
        return -RT_EINVAL;
    }
    else
    {
    #ifdef RT_USING_DFS
        const char *mountpath;

        if ((mountpath = dfs_filesystem_get_mounted_path(&blk->parent)))
        {
            dfs_unmount(mountpath);
            LOG_D("%s: Unmount file system on %s",
                    to_blk_name(blk), mountpath);
        }
    #endif
    }

#ifdef RT_USING_DM
    rt_dm_ida_free(disk->ida, blk->parent.device_id);
#endif

    rt_device_unregister(&blk->parent);

    if (!lockless)
    {
        spin_lock(&disk->lock);
    }

    rt_list_remove(&blk->list);

    if (!lockless)
    {
        spin_unlock(&disk->lock);
    }

    --disk->partitions;

    return RT_EOK;
}

rt_uint32_t blk_request_ioprio(void)
{
    struct rt_thread *task = rt_thread_self();

    return task ? RT_SCHED_PRIV(task).current_priority : 0;
}
