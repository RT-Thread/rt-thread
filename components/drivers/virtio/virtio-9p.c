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

#define DBG_TAG "virtio.dev.9p"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dfs_9pfs.h>
#include "virtio_config/virtio-9p.h"

struct virtio_9p
{
    struct p9_protocol parent;
    struct rt_virtio_device *vdev;

    char *tag;
    struct rt_virtqueue *vqs[1];
    struct rt_completion done;
    struct rt_spinlock lock;
};

static rt_err_t virtio_9p_transport(struct p9_protocol *p9p,
        rt_uint8_t *tx_data, rt_uint32_t tx_size,
        rt_uint8_t *rx_data, rt_uint32_t *ref_rx_size)
{
    rt_err_t err;
    rt_ubase_t level;
    struct rt_virtqueue *vq;
    struct virtio_9p *v9p = rt_container_of(p9p, struct virtio_9p, parent);

    vq = v9p->vqs[0];
    rt_virtqueue_wait_prepare(vq, 2);

    level = rt_spin_lock_irqsave(&v9p->lock);

    rt_virtqueue_add_outbuf(vq, tx_data, tx_size);
    rt_virtqueue_add_inbuf(vq, rx_data, *ref_rx_size);

    rt_virtqueue_kick(vq);

    rt_spin_unlock_irqrestore(&v9p->lock, level);

    if (!(err = rt_completion_wait(&v9p->done, rt_tick_from_millisecond(1000))))
    {
        *ref_rx_size = rt_min_t(rt_uint32_t,
                *ref_rx_size, rt_le32_to_cpu(*(rt_uint32_t*)(&rx_data[0])));
    }

    return err;
}

static void virtio_9p_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_9p *v9p = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&v9p->lock);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&v9p->done);

    rt_spin_unlock_irqrestore(&v9p->lock, level);
}

static rt_err_t virtio_9p_vq_init(struct virtio_9p *v9p)
{
    const char *names[] =
    {
        "req",
    };
    rt_virtqueue_callback cbs[] =
    {
        &virtio_9p_done,
    };

    return rt_virtio_virtqueue_install(v9p->vdev, RT_ARRAY_SIZE(v9p->vqs),
            v9p->vqs, names, cbs);
}

static void virtio_9p_vq_finit(struct virtio_9p *v9p)
{
    if (v9p->vqs[0])
    {
        rt_virtio_virtqueue_release(v9p->vdev);
    }
    if (v9p->tag)
    {
        rt_free(v9p->tag);
    }

    rt_free(v9p);
}

static rt_err_t virtio_9p_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    rt_uint16_t tag_len = 0;
    struct virtio_9p *v9p = rt_calloc(1, sizeof(*v9p));

    if (!v9p)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = v9p;
    v9p->vdev = vdev;
    vdev->parent.user_data = v9p;

    if ((err = virtio_9p_vq_init(v9p)))
    {
        goto _fail;
    }

    if (rt_virtio_has_feature(vdev, VIRTIO_9P_F_MOUNT_TAG))
    {
        rt_virtio_read_config(vdev, struct virtio_9p_config, tag_len, &tag_len);
    }

    v9p->tag = rt_malloc(tag_len + 1);

    if (!v9p->tag)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rt_virtio_read_bytes(vdev, rt_offsetof(struct virtio_9p_config, tag),
            v9p->tag, 1, tag_len);
    v9p->tag[tag_len] = '\0';

    rt_completion_init(&v9p->done);
    rt_spin_lock_init(&v9p->lock);

    v9p->parent.name = "virtio";
    v9p->parent.tag = v9p->tag;
    v9p->parent.transport = &virtio_9p_transport;
    if ((err = dfs_9pfs_add_tag(&v9p->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    virtio_9p_vq_finit(v9p);

    return err;
}

static rt_err_t virtio_9p_remove(struct rt_virtio_device *vdev)
{
    struct virtio_9p *v9p = vdev->parent.user_data;

    dfs_9pfs_del_tag(&v9p->parent);

    virtio_9p_vq_finit(v9p);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_9p_ids[] =
{
    { VIRTIO_DEVICE_ID_9P, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_9p_driver =
{
    .ids = virtio_9p_ids,
    .features =
        RT_BIT(VIRTIO_9P_F_MOUNT_TAG)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_9p_probe,
    .remove = virtio_9p_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_9p_driver);
