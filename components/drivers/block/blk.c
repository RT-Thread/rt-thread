/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#define DBG_TAG "rtdm.blk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "blk_dev.h"
#include "blk_dfs.h"

static void blk_remove_all(struct rt_blk_disk *disk)
{
    struct rt_blk_device *blk, *blk_next;

    /* Remove all partitions */
    rt_list_for_each_entry_safe(blk, blk_next, &disk->part_nodes, list)
    {
        disk_remove_blk_dev(blk, RT_TRUE);
    }
}

static rt_err_t blk_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_blk_disk *disk = to_blk_disk(dev);

    if (disk->read_only && (oflag & RT_DEVICE_OFLAG_WRONLY))
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t blk_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t blk_read(rt_device_t dev, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    struct rt_blk_disk *disk = to_blk_disk(dev);

    rt_sem_take(&disk->usr_lock, RT_WAITING_FOREVER);

    res = disk->ops->read(disk, sector, buffer, sector_count);

    rt_sem_release(&disk->usr_lock);

    return res;
}

static rt_ssize_t blk_write(rt_device_t dev, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    struct rt_blk_disk *disk = to_blk_disk(dev);

    if (!disk->read_only)
    {
        rt_sem_take(&disk->usr_lock, RT_WAITING_FOREVER);

        res = disk->ops->write(disk, sector, buffer, sector_count);

        rt_sem_release(&disk->usr_lock);

        return res;
    }

    return -RT_ENOSYS;
}

static rt_ssize_t blk_parallel_read(rt_device_t dev, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    struct rt_blk_disk *disk = to_blk_disk(dev);

    return disk->ops->read(disk, sector, buffer, sector_count);
}

static rt_ssize_t blk_parallel_write(rt_device_t dev, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    struct rt_blk_disk *disk = to_blk_disk(dev);

    if (!disk->read_only)
    {
        return disk->ops->write(disk, sector, buffer, sector_count);
    }

    return -RT_ENOSYS;
}

static rt_err_t blk_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err;
    struct rt_blk_disk *disk = to_blk_disk(dev);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        if (args)
        {
            err = disk->ops->getgeome(disk, args);
        }
        else
        {
            err = -RT_EINVAL;
        }

        break;

    case RT_DEVICE_CTRL_BLK_SYNC:
        if (disk->ops->sync)
        {
            rt_sem_take(&disk->usr_lock, RT_WAITING_FOREVER);

            spin_lock(&disk->lock);

            err = disk->ops->sync(disk);

            spin_unlock(&disk->lock);

            rt_sem_release(&disk->usr_lock);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case RT_DEVICE_CTRL_BLK_ERASE:
        if (disk->ops->erase)
        {
            rt_sem_take(&disk->usr_lock, RT_WAITING_FOREVER);

            spin_lock(&disk->lock);

            if (disk->parent.ref_count != 1)
            {
                err = -RT_EBUSY;
                goto _unlock;
            }

            blk_remove_all(disk);

            err = disk->ops->erase(disk);

        _unlock:
            spin_unlock(&disk->lock);

            rt_sem_release(&disk->usr_lock);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case RT_DEVICE_CTRL_BLK_AUTOREFRESH:
        if (disk->ops->autorefresh)
        {
            err = disk->ops->autorefresh(disk, !!args);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case RT_DEVICE_CTRL_BLK_PARTITION:
        err = -RT_EINVAL;
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
            err = disk->ops->control(disk, RT_NULL, cmd, args);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops blk_ops =
{
    .open = blk_open,
    .close = blk_close,
    .read = blk_read,
    .write = blk_write,
    .control = blk_control,
};

const static struct rt_device_ops blk_parallel_ops =
{
    .open = blk_open,
    .close = blk_close,
    .read = blk_parallel_read,
    .write = blk_parallel_write,
    .control = blk_control,
};
#endif /* RT_USING_DEVICE_OPS */

rt_err_t rt_hw_blk_disk_register(struct rt_blk_disk *disk)
{
    rt_err_t err;
#ifdef RT_USING_DM
    int device_id;
#endif
    const char *disk_name;
    rt_uint16_t flags = RT_DEVICE_FLAG_RDONLY;

    if (!disk || !disk->ops)
    {
        return -RT_EINVAL;
    }

#ifdef RT_USING_DM
    if (!disk->ida)
    {
        return -RT_EINVAL;
    }
#endif

#if RT_NAME_MAX > 0
    if (disk->parent.parent.name[0] == '\0')
#else
    if (disk->parent.parent.name)
#endif
    {
        return -RT_EINVAL;
    }

#ifdef RT_USING_DM
    if ((device_id = rt_dm_ida_alloc(disk->ida)) < 0)
    {
        return -RT_EFULL;
    }
#endif

    disk->__magic = RT_BLK_DISK_MAGIC;
    disk_name = to_disk_name(disk);

    err = rt_sem_init(&disk->usr_lock, disk_name, 1, RT_IPC_FLAG_PRIO);

    if (err)
    {
    #ifdef RT_USING_DM
        rt_dm_ida_free(disk->ida, device_id);
    #endif

        LOG_E("%s: Init user mutex error = %s", rt_strerror(err));

        return err;
    }

    rt_list_init(&disk->part_nodes);
    rt_spin_lock_init(&disk->lock);

    disk->parent.type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    if (disk->parallel_io)
    {
        disk->parent.ops = &blk_parallel_ops;
    }
    else
    {
        disk->parent.ops = &blk_ops;
    }
#else
    disk->parent.open = blk_open;
    disk->parent.close = blk_close;

    if (disk->parallel_io)
    {
        disk->parent.read = blk_parallel_read;
        disk->parent.write = blk_parallel_write;
    }
    else
    {
        disk->parent.read = blk_read;
        disk->parent.write = blk_write;
    }
    disk->parent.control = blk_control;
#endif

    if (!disk->ops->write)
    {
        disk->read_only = RT_TRUE;
    }

    if (!disk->read_only)
    {
        flags |= RT_DEVICE_FLAG_WRONLY;
    }

#ifdef RT_USING_DM
    disk->parent.master_id = disk->ida->master_id;
    disk->parent.device_id = device_id;
#endif
    device_set_blk_fops(&disk->parent);

    err = rt_device_register(&disk->parent, disk_name, flags);

    if (err)
    {
        rt_sem_detach(&disk->usr_lock);
    }

    /* Ignore partition scanning errors */
    rt_blk_disk_probe_partition(disk);

    return err;
}

rt_err_t rt_hw_blk_disk_unregister(struct rt_blk_disk *disk)
{
    rt_err_t err;

    if (!disk)
    {
        return -RT_EINVAL;
    }

    spin_lock(&disk->lock);

    if (disk->parent.ref_count > 0)
    {
        err = -RT_EBUSY;
        goto _unlock;
    }

    /* Flush all data */
    if (disk->ops->sync)
    {
        err = disk->ops->sync(disk);

        if (err)
        {
            LOG_E("%s: Sync error = %s", to_disk_name(disk), rt_strerror(err));

            goto _unlock;
        }
    }

    rt_sem_detach(&disk->usr_lock);

    blk_remove_all(disk);

#ifdef RT_USING_DM
    rt_dm_ida_free(disk->ida, disk->parent.device_id);
#endif

    err = rt_device_unregister(&disk->parent);

_unlock:
    spin_unlock(&disk->lock);

    return err;
}

rt_ssize_t rt_blk_disk_get_capacity(struct rt_blk_disk *disk)
{
    rt_ssize_t res;
    struct rt_device_blk_geometry geometry;

    if (!disk)
    {
        return -RT_EINVAL;
    }

    res = disk->ops->getgeome(disk, &geometry);

    if (!res)
    {
        return geometry.sector_count;
    }

    return res;
}

rt_ssize_t rt_blk_disk_get_logical_block_size(struct rt_blk_disk *disk)
{
    rt_ssize_t res;
    struct rt_device_blk_geometry geometry;

    if (!disk)
    {
        return -RT_EINVAL;
    }

    res = disk->ops->getgeome(disk, &geometry);

    if (!res)
    {
        return geometry.bytes_per_sector;
    }

    return res;
}

#ifdef RT_USING_DFS_MNTTABLE
static int blk_dfs_mnt_table(void)
{
    rt_ubase_t level;
    struct rt_object *obj;
    struct rt_device *dev;
    struct rt_blk_disk *disk;
    struct rt_blk_device *blk_dev;
    struct rt_object_information *info = rt_object_get_information(RT_Object_Class_Device);

    level = rt_hw_interrupt_disable();

    rt_list_for_each_entry(obj, &info->object_list, list)
    {
        dev = rt_container_of(obj, struct rt_device, parent);

        if (dev->type != RT_Device_Class_Block)
        {
            continue;
        }

        disk = to_blk_disk(dev);

        if (disk->__magic != RT_BLK_DISK_MAGIC)
        {
            continue;
        }

        if (disk->max_partitions == RT_BLK_PARTITION_NONE)
        {
            dfs_mount_device(&disk->parent);
            continue;
        }

        rt_list_for_each_entry(blk_dev, &disk->part_nodes, list)
        {
            dfs_mount_device(&blk_dev->parent);
        }
    }

    rt_hw_interrupt_enable(level);

    return 0;
}
INIT_ENV_EXPORT(blk_dfs_mnt_table);
#endif /* RT_USING_DFS_MNTTABLE */

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
const char *convert_size(struct rt_device_blk_geometry *geome,
        rt_size_t sector_count, rt_size_t *out_cap, rt_size_t *out_minor)
{
    rt_size_t cap, minor = 0;
    int size_index = 0;
    const char *size_name[] = { "B", "K", "M", "G", "T", "P", "E" };

    cap = geome->bytes_per_sector * sector_count;

    for (size_index = 0; size_index < RT_ARRAY_SIZE(size_name) - 1; ++size_index)
    {
        if (cap < 1024)
        {
            break;
        }

        /* Only one decimal point */
        minor = (cap % 1024) * 10 / 1024;
        cap = cap / 1024;
    }

    *out_cap = cap;
    *out_minor = minor;

    return size_name[size_index];
}

static int list_blk(int argc, char**argv)
{
    rt_ubase_t level;
    rt_size_t cap, minor;
    const char *size_name;
    struct rt_object *obj;
    struct rt_device *dev;
    struct rt_blk_disk *disk;
    struct rt_blk_device *blk_dev;
    struct rt_device_blk_geometry geome;
    struct rt_object_information *info = rt_object_get_information(RT_Object_Class_Device);

    level = rt_hw_interrupt_disable();

    rt_kprintf("%-*.s MAJ:MIN RM SIZE\tRO TYPE MOUNTPOINT\n", RT_NAME_MAX, "NAME");

    rt_list_for_each_entry(obj, &info->object_list, list)
    {
        dev = rt_container_of(obj, struct rt_device, parent);

        if (dev->type != RT_Device_Class_Block)
        {
            continue;
        }

        disk = to_blk_disk(dev);

        if (disk->__magic != RT_BLK_DISK_MAGIC)
        {
            continue;
        }

        if (disk->ops->getgeome(disk, &geome))
        {
            continue;
        }

        size_name = convert_size(&geome, geome.sector_count, &cap, &minor);

        rt_kprintf("%-*.s %3u.%-3u  %u %u.%u%s\t%u  disk %s\n",
                RT_NAME_MAX, to_disk_name(disk),
        #ifdef RT_USING_DM
                disk->parent.master_id, disk->parent.device_id,
        #else
                0, 0,
        #endif
                disk->removable, cap, minor, size_name, disk->read_only,
                disk->max_partitions != RT_BLK_PARTITION_NONE ? "\b" :
                    (dfs_filesystem_get_mounted_path(&disk->parent) ? : "\b"));

        rt_list_for_each_entry(blk_dev, &disk->part_nodes, list)
        {
            size_name = convert_size(&geome, blk_dev->sector_count, &cap, &minor);

            rt_kprintf("%c--%-*.s %3u.%-3u  %u %u.%u%s\t%u  part %s\n",
                    blk_dev->list.next != &disk->part_nodes ? '|' : '`',
                    RT_NAME_MAX - 3, to_blk_name(blk_dev),
            #ifdef RT_USING_DM
                    blk_dev->parent.master_id, blk_dev->parent.device_id,
            #else
                    0, 0,
            #endif
                    disk->removable, cap, minor, size_name, disk->read_only,
                    dfs_filesystem_get_mounted_path(&blk_dev->parent) ? : "");
        }
    }

    rt_hw_interrupt_enable(level);

    return 0;
}
MSH_CMD_EXPORT(list_blk, dump all of blks information);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
