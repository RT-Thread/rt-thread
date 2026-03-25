/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     using virtio common interface
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.blk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "../block/blk_dev.h"
#include "virtio_internal.h"
#include "virtio_config/virtio-blk.h"

struct virtio_blk
{
    struct rt_blk_disk parent;
    struct rt_virtio_device *vdev;

    int vblk_id;
    rt_le32_t blk_size;

    int vqs_nr;
    struct rt_virtqueue *vqs[RT_CPUS_NR];
    struct rt_spinlock *lock;
    struct rt_completion *done;
};

#define raw_to_virtio_blk(raw) rt_container_of(raw, struct virtio_blk, parent)

static struct rt_dm_ida virtio_blk_ida = RT_DM_IDA_INIT(CUSTOM);
static struct rt_dm_ida vd_ida = RT_DM_IDA_INIT(VIRTUAL_BLOCK);

static rt_err_t virtio_blk_request(struct virtio_blk *vblk,
        rt_off_t sector, void *buffer, rt_size_t sector_count, int type)
{
    rt_base_t level;
    rt_uint8_t status;
    struct rt_virtqueue *vq;
    struct virtio_blk_req req;
    struct rt_virtio_device *vdev = vblk->vdev;

    vq = vblk->vqs[rt_hw_cpu_id() % vblk->vqs_nr];
    if (type == VIRTIO_BLK_T_OUT || type == VIRTIO_BLK_T_IN)
    {
        rt_virtqueue_wait_prepare(vq, 3);
    }
    else
    {
        rt_virtqueue_wait_prepare(vq, 2);
    }

    level = rt_spin_lock_irqsave(&vblk->lock[vq->index]);

    req.type = cpu_to_virtio32(vdev, type);
    req.ioprio = cpu_to_virtio32(vdev, blk_request_ioprio());
    req.sector = cpu_to_virtio64(vdev, sector * (vblk->blk_size / 512));
    rt_virtqueue_add_outbuf(vq, &req, sizeof(req));

    if (type == VIRTIO_BLK_T_OUT)
    {
        rt_virtqueue_add_outbuf(vq, buffer, sector_count * vblk->blk_size);
    }
    else if (type == VIRTIO_BLK_T_IN)
    {
        rt_virtqueue_add_inbuf(vq, buffer, sector_count * vblk->blk_size);
    }

    status = RT_UINT8_MAX;
    rt_virtqueue_add_inbuf(vq, &status, sizeof(status));

    rt_virtqueue_kick(vq);

    rt_spin_unlock_irqrestore(&vblk->lock[vq->index], level);

    rt_completion_wait(&vblk->done[vq->index], RT_WAITING_FOREVER);

    switch (status)
    {
    case VIRTIO_BLK_S_OK:
        return RT_EOK;

    case VIRTIO_BLK_S_UNSUPP:
        return -RT_ENOSYS;

    case VIRTIO_BLK_S_ZONE_OPEN_RESOURCE:
        return 1;

    case VIRTIO_BLK_S_ZONE_ACTIVE_RESOURCE:
        return 2;

    case VIRTIO_BLK_S_IOERR:
    case VIRTIO_BLK_S_ZONE_UNALIGNED_WP:
    default:
        return -RT_EIO;
    }
}

static rt_ssize_t virtio_blk_read(struct rt_blk_disk *disk, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    res = virtio_blk_request(vblk, sector, buffer, sector_count, VIRTIO_BLK_T_IN);

    return res >= 0 ? sector_count : res;
}

static rt_ssize_t virtio_blk_write(struct rt_blk_disk *disk, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    res = virtio_blk_request(vblk, sector, (void *)buffer, sector_count, VIRTIO_BLK_T_OUT);

    return res >= 0 ? sector_count : res;
}

static rt_err_t virtio_blk_getgeome(struct rt_blk_disk *disk,
        struct rt_device_blk_geometry *geometry)
{
    rt_le64_t capacity;
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    rt_virtio_read_config(vblk->vdev, struct virtio_blk_config, capacity, &capacity);

    geometry->bytes_per_sector = 512;
    geometry->block_size = vblk->blk_size;
    geometry->sector_count = rt_le64_to_cpu(capacity);

    return RT_EOK;
}

static rt_err_t virtio_blk_sync(struct rt_blk_disk *disk)
{
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    return virtio_blk_request(vblk, 0, RT_NULL, 0, VIRTIO_BLK_T_FLUSH);
}

static rt_err_t virtio_blk_erase(struct rt_blk_disk *disk)
{
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    return virtio_blk_request(vblk, 0, RT_NULL, 0, VIRTIO_BLK_T_SECURE_ERASE);
}

static rt_err_t virtio_blk_autorefresh(struct rt_blk_disk *disk, rt_bool_t is_auto)
{
    rt_uint8_t writeback = !is_auto;
    struct virtio_blk *vblk = raw_to_virtio_blk(disk);

    /*
     * 0: write through
     * 1: write back
     */
    rt_virtio_write_config(vblk->vdev, struct virtio_blk_config, writeback, writeback);

    return RT_EOK;
}

static const struct rt_blk_disk_ops virtio_blk_ops =
{
    .read = virtio_blk_read,
    .write = virtio_blk_write,
    .getgeome = virtio_blk_getgeome,
    .sync = virtio_blk_sync,
    .erase = virtio_blk_erase,
    .autorefresh = virtio_blk_autorefresh,
};

static void virtio_blk_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_blk *vblk = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vblk->lock[vq->index]);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vblk->done[vq->index]);

    rt_spin_unlock_irqrestore(&vblk->lock[vq->index], level);
}

static rt_err_t virtio_blk_vq_init(struct virtio_blk *vblk)
{
    rt_uint16_t vqs_nr = 1;
    const char *names[RT_ARRAY_SIZE(vblk->vqs)];
    rt_virtqueue_callback cbs[RT_ARRAY_SIZE(vblk->vqs)];
    struct rt_virtio_device *vdev = vblk->vdev;

    if (rt_virtio_has_feature(vdev, VIRTIO_BLK_F_MQ))
    {
        rt_virtio_read_config(vdev, struct virtio_blk_config, num_queues, &vqs_nr);
    }

    if (!(vblk->lock = rt_malloc(sizeof(vblk->lock[0]) * vqs_nr)))
    {
        return -RT_ENOMEM;
    }

    if (!(vblk->done = rt_malloc(sizeof(vblk->done[0]) * vqs_nr)))
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < vqs_nr; ++i)
    {
        names[i] = "req";
        cbs[i] = &virtio_blk_done;

        rt_spin_lock_init(&vblk->lock[i]);
        rt_completion_init(&vblk->done[i]);
    }

    vblk->vqs_nr = vqs_nr;
    return rt_virtio_virtqueue_install(vdev, vqs_nr, vblk->vqs, names, cbs);
}

static void virtio_blk_vq_finit(struct virtio_blk *vblk)
{
    if (vblk->vqs[0])
    {
        rt_virtio_virtqueue_release(vblk->vdev);
    }
    if (vblk->lock)
    {
        rt_free(vblk->lock);
    }
    if (vblk->done)
    {
        rt_free(vblk->done);
    }
}

static rt_err_t virtio_blk_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_blk *vblk = rt_calloc(1, sizeof(*vblk));

    if (!vblk)
    {
        return -RT_ENOMEM;
    }

    if ((vblk->vblk_id = rt_dm_ida_alloc(&virtio_blk_ida)) < 0)
    {
        return -RT_EFULL;
    }

    vdev->priv = vblk;
    vblk->vdev = vdev;
    vdev->parent.user_data = vblk;
    vblk->parent.ida = &vd_ida;
    vblk->parent.parallel_io = RT_TRUE;
    vblk->parent.ops = &virtio_blk_ops;
    vblk->parent.max_partitions = RT_BLK_PARTITION_MAX;

    if ((err = virtio_blk_vq_init(vblk)))
    {
        goto _fail;
    }

    rt_virtio_read_config(vdev, struct virtio_blk_config, blk_size, &vblk->blk_size);

    rt_dm_dev_set_name(&vblk->parent.parent, "vd%c%c", letter_name(vblk->vblk_id));

    if ((err = rt_hw_blk_disk_register(&vblk->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&virtio_blk_ida, vblk->vblk_id);
    virtio_blk_vq_finit(vblk);
    rt_free(vblk);

    return err;
}

static rt_err_t virtio_blk_remove(struct rt_virtio_device *vdev)
{
    struct virtio_blk *vblk = vdev->parent.user_data;

    rt_hw_blk_disk_unregister(&vblk->parent);
    rt_dm_ida_free(&virtio_blk_ida, vblk->vblk_id);

    virtio_blk_vq_finit(vblk);
    rt_free(vblk);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_blk_ids[] =
{
    { VIRTIO_DEVICE_ID_BLOCK, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_blk_driver =
{
    .ids = virtio_blk_ids,
    .features =
        RT_BIT(VIRTIO_BLK_F_SIZE_MAX)
      | RT_BIT(VIRTIO_BLK_F_GEOMETRY)
      | RT_BIT(VIRTIO_BLK_F_BLK_SIZE)
      | RT_BIT(VIRTIO_BLK_F_FLUSH)
      | RT_BIT(VIRTIO_BLK_F_TOPOLOGY)
      | RT_BIT(VIRTIO_BLK_F_CONFIG_WCE)
      | RT_BIT(VIRTIO_BLK_F_MQ)
      | RT_BIT(VIRTIO_BLK_F_DISCARD)
      | RT_BIT(VIRTIO_BLK_F_WRITE_ZEROES)
      | RT_BIT(VIRTIO_BLK_F_SECURE_ERASE),

    .probe = virtio_blk_probe,
    .remove = virtio_blk_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_blk_driver);
