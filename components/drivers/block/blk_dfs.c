/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-08     GuEe-GUI     first version
 */

#include "blk_dfs.h"

#include <dfs_file.h>
#include <drivers/classes/block.h>

#if defined(RT_USING_POSIX_DEVIO) && defined(RT_USING_DFS_V2)
struct blk_fops_data
{
    struct rt_device_blk_geometry geometry;
};

static int blk_fops_open(struct dfs_file *file)
{
    struct rt_device *dev = file->vnode->data;
    struct blk_fops_data *data = rt_malloc(sizeof(*data));

    if (!data)
    {
        return (int)-RT_ENOMEM;
    }

    dev->user_data = data;
    rt_device_control(dev, RT_DEVICE_CTRL_BLK_GETGEOME, &data->geometry);
    rt_device_control(dev, RT_DEVICE_CTRL_ALL_BLK_SSIZEGET, &file->vnode->size);

    return 0;
}

static int blk_fops_close(struct dfs_file *file)
{
    struct rt_device *dev = file->vnode->data;

    rt_free(dev->user_data);
    dev->user_data = RT_NULL;

    return 0;
}

static int blk_fops_ioctl(struct dfs_file *file, int cmd, void *arg)
{
    struct rt_device *dev = file->vnode->data;

    return (int)rt_device_control(dev, cmd, arg);
}

static ssize_t blk_fops_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    void *rbuf;
    rt_ssize_t res = 0;
    int bytes_per_sector, blk_pos, first_offs, rsize = 0;
    struct rt_device *dev = file->vnode->data;
    struct blk_fops_data *data = dev->user_data;

    bytes_per_sector = data->geometry.bytes_per_sector;
    blk_pos = *pos / bytes_per_sector;
    first_offs = *pos % bytes_per_sector;

    if ((rbuf = rt_malloc(bytes_per_sector)))
    {
        /*
        ** #1: read first unalign block size.
        */
        res = rt_device_read(dev, blk_pos, rbuf, 1);

        if (res == 1)
        {
            if (count > bytes_per_sector - first_offs)
            {
                rsize = bytes_per_sector - first_offs;
            }
            else
            {
                rsize = count;
            }
            rt_memcpy(buf, rbuf + first_offs, rsize);
            ++blk_pos;

            /*
            ** #2: read continuous block size.
            */
            while (rsize < count)
            {
                res = rt_device_read(dev, blk_pos++, rbuf, 1);

                if (res != 1)
                {
                    break;
                }

                if (count - rsize >= bytes_per_sector)
                {
                    rt_memcpy(buf + rsize, rbuf, bytes_per_sector);
                    rsize += bytes_per_sector;
                }
                else
                {
                    rt_memcpy(buf + rsize, rbuf, count - rsize);
                    rsize = count;
                }
            }

            *pos += rsize;
        }

        rt_free(rbuf);
    }

    return rsize;
}

static ssize_t blk_fops_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    void *rbuf;
    rt_ssize_t res = 0;
    int bytes_per_sector, blk_pos, first_offs, wsize = 0;
    struct rt_device *dev = file->vnode->data;
    struct blk_fops_data *data = dev->user_data;

    bytes_per_sector = data->geometry.bytes_per_sector;
    blk_pos = *pos / bytes_per_sector;
    first_offs = *pos % bytes_per_sector;

    /*
    ** #1: write first unalign block size.
    */
    if (first_offs != 0)
    {
        if (count > bytes_per_sector - first_offs)
        {
            wsize = bytes_per_sector - first_offs;
        }
        else
        {
            wsize = count;
        }

        if ((rbuf = rt_malloc(bytes_per_sector)))
        {
            res = rt_device_read(dev, blk_pos, rbuf, 1);

            if (res == 1)
            {
                rt_memcpy(rbuf + first_offs, buf, wsize);
                res = rt_device_write(dev, blk_pos, (const void *)rbuf, 1);

                if (res == 1)
                {
                    blk_pos += 1;
                    rt_free(rbuf);

                    goto _goon;
                }
            }

            rt_free(rbuf);
        }

        return 0;
    }

_goon:
    /*
    ** #2: write continuous block size.
    */
    if ((count - wsize) / bytes_per_sector != 0)
    {
        res = rt_device_write(dev, blk_pos, buf + wsize, (count - wsize) / bytes_per_sector);
        wsize += res * bytes_per_sector;
        blk_pos += res;

        if (res != (count - wsize) / bytes_per_sector)
        {
            *pos += wsize;
            return wsize;
        }
    }

    /*
    ** # 3: write last unalign block size.
    */
    if ((count - wsize) != 0)
    {
        if ((rbuf = rt_malloc(bytes_per_sector)))
        {
            res = rt_device_read(dev, blk_pos, rbuf, 1);

            if (res == 1)
            {
                rt_memcpy(rbuf, buf + wsize, count - wsize);
                res = rt_device_write(dev, blk_pos, (const void *)rbuf, 1);

                if (res == 1)
                {
                    wsize += count - wsize;
                }
            }

            rt_free(rbuf);
        }
    }

    *pos += wsize;
    return wsize;
}

static int blk_fops_flush(struct dfs_file *file)
{
    struct rt_device *dev = file->vnode->data;

    return (int)rt_device_control(dev, RT_DEVICE_CTRL_BLK_SYNC, RT_NULL);
}

static int blk_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;

    return mask;
}

const static struct dfs_file_ops blk_fops =
{
    .open = blk_fops_open,
    .close = blk_fops_close,
    .ioctl = blk_fops_ioctl,
    .read = blk_fops_read,
    .write = blk_fops_write,
    .flush = blk_fops_flush,
    .lseek = generic_dfs_lseek,
    .poll = blk_fops_poll
};

void device_set_blk_fops(struct rt_device *dev)
{
    dev->fops = &blk_fops;
}
#else
void device_set_blk_fops(struct rt_device *dev)
{
}
#endif /* RT_USING_POSIX_DEVIO && RT_USING_DFS_V2 */

void device_get_blk_ssize(struct rt_device *dev, void *args)
{
    rt_uint32_t bytes_per_sector;
    struct rt_device_blk_geometry geometry;

    rt_device_control(dev, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);
    bytes_per_sector = geometry.bytes_per_sector;

    RT_ASSERT(sizeof(bytes_per_sector) == sizeof(geometry.bytes_per_sector));

    rt_memcpy(args, &bytes_per_sector, sizeof(bytes_per_sector));
}

void device_get_all_blk_ssize(struct rt_device *dev, void *args)
{
    rt_uint64_t count_mul_per;
    struct rt_device_blk_geometry geometry;

    rt_device_control(dev, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);
    count_mul_per = geometry.bytes_per_sector * geometry.sector_count;

    rt_memcpy(args, &count_mul_per, sizeof(count_mul_per));
}
