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

#define DBG_TAG "virtio.dev.rpmsg"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_config/virtio-rpmsg.h"

#define QUEUE_RX    _queue_rx
#define QUEUE_TX    _queue_tx

struct virtio_rpmsg_tx_buf
{
    rt_uint8_t data[VIRTIO_RPMSG_MAX_BUF_SIZE];
    rt_uint32_t idx;
};

struct virtio_rpmsg
{
    struct rt_rpmsg_device parent;
    struct rt_rpmsg_device *ns;
    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[2];
    struct rt_spinlock tx_lock;

    rt_bool_t supp_ns;

    rt_uint8_t *tx_buffer;
    struct rt_completion *tx_done;
};

#define raw_to_virtio_rpmsg(raw) (raw)->priv

static int _queue_rx, _queue_tx;

static rt_err_t virtio_rpmsg_create_endpoint(struct rt_rpmsg_device *rdev,
        struct rt_rpmsg_endpoint *ept, struct rt_rpmsg_endpoint_info *info)
{
    rt_err_t err = RT_EOK;
    rt_bool_t is_remote = info->src == RT_RPMSG_ADDR_ANY;
    struct rt_rpmsg_endpoint *target_ept;
    struct virtio_rpmsg *vrpmsg = raw_to_virtio_rpmsg(rdev);

    ept->sysdata = (void *)(rt_ubase_t)is_remote;

    if (is_remote)
    {
        target_ept = rt_rpmsg_find_endpoint(rdev, info);

        if (target_ept)
        {
            LOG_E("%s: endpoint (name: %s, src: %u, dst: %u) already exist",
                    rt_dm_dev_get_name(&vrpmsg->vdev->parent),
                    info->name, info->src, info->dst);

            return -RT_EINVAL;
        }
    }

    if (!is_remote && vrpmsg->supp_ns)
    {
        struct rt_rpmsg_ns_msg ns_msg;

        rt_memset(&ns_msg, 0, sizeof(ns_msg));

        if (info && info->name[0])
        {
            rt_strncpy(ns_msg.name, info->name, RT_RPMSG_NAME_SIZE);
        }
        else
        {
            rt_strncpy(ns_msg.name, rdev->id.name, RT_RPMSG_NAME_SIZE);
        }

        ns_msg.addr  = rt_cpu_to_le32(ept->info.src);
        ns_msg.flags = rt_cpu_to_le32(RT_RPMSG_NS_CREATE);

        err = rt_rpmsg_sendto(ept, RT_RPMSG_NS_ADDR, &ns_msg, sizeof(ns_msg));

        if (err)
        {
            LOG_E("%s: Notify remote error = %s",
                    rt_dm_dev_get_name(&vrpmsg->vdev->parent), rt_strerror(err));
        }
    }

    return err;
}

static rt_err_t virtio_rpmsg_destroy_endpoint(struct rt_rpmsg_device *rdev,
        struct rt_rpmsg_endpoint *ept)
{
    rt_err_t err = RT_EOK;
    rt_bool_t is_remote = !!ept->sysdata;
    struct virtio_rpmsg *vrpmsg = raw_to_virtio_rpmsg(rdev);

    if (!is_remote && vrpmsg->supp_ns)
    {
        struct rt_rpmsg_ns_msg ns_msg;

        rt_memset(&ns_msg, 0, sizeof(ns_msg));

        if (ept->info.name[0])
        {
            rt_strncpy(ns_msg.name, ept->info.name, RT_RPMSG_NAME_SIZE);
        }
        else
        {
            rt_strncpy(ns_msg.name, rdev->id.name, RT_RPMSG_NAME_SIZE);
        }

        ns_msg.addr = rt_cpu_to_le32(ept->info.src);
        ns_msg.flags = rt_cpu_to_le32(RT_RPMSG_NS_DESTROY);

        err = rt_rpmsg_sendto(ept, RT_RPMSG_NS_ADDR, &ns_msg, sizeof(ns_msg));

        if (err)
        {
            LOG_E("%s: Notify remote error = %s",
                    rt_dm_dev_get_name(&vrpmsg->vdev->parent), rt_strerror(err));
        }
    }

    return err;
}

static rt_err_t virtio_rpmsg_send(struct rt_rpmsg_device *rdev,
        rt_uint32_t src, rt_uint32_t dst,
        const void *data, rt_size_t len, rt_int32_t timeout)
{
    rt_base_t level;
    int idx;
    struct rt_virtqueue *vq;
    struct virtio_rpmsg_hdr *msg;
    struct virtio_rpmsg_tx_buf *tx_buf;
    struct virtio_rpmsg *vrpmsg = raw_to_virtio_rpmsg(rdev);

    if (src == RT_RPMSG_ADDR_ANY || dst == RT_RPMSG_ADDR_ANY)
    {
        LOG_E("%s: Invalid addr(src: %u, dst: %u)",
                rt_dm_dev_get_name(&vrpmsg->vdev->parent), src, dst);

        return -RT_EINVAL;
    }

    if (len > VIRTIO_RPMSG_MAX_BUF_SIZE - sizeof(*msg))
    {
        LOG_E("%s: Data's len = %u > %u is too big",
                rt_dm_dev_get_name(&vrpmsg->vdev->parent),
                len, VIRTIO_RPMSG_MAX_BUF_SIZE - sizeof(*msg));

        return -RT_EFULL;
    }

    vq = vrpmsg->vqs[QUEUE_TX];
    rt_virtqueue_wait_prepare(vq, 1);

    level = rt_spin_lock_irqsave(&vrpmsg->tx_lock);

    idx = rt_virtqueue_next_buf_index(vq);
    tx_buf = (void *)vrpmsg->tx_buffer + idx * sizeof(struct virtio_rpmsg_tx_buf);
    tx_buf->idx = idx;
    msg = (void *)tx_buf->data;

    msg->src = rt_cpu_to_le32(src);
    msg->dst = rt_cpu_to_le32(dst);
    msg->reserved = 0;
    msg->len = rt_cpu_to_le16(len);
    msg->flags = 0;
    LOG_D("%s: %cX-HDR(src: %u, dst: %u, len: %u, flags: %u, reserved: %u)",
            rt_dm_dev_get_name(&vrpmsg->vdev->parent), 'T', src, dst, len, 0, 0);
    rt_memcpy(msg->data, data, len);

    rt_virtqueue_add_outbuf(vq, msg, sizeof(*msg) + len);

    rt_virtqueue_kick(vq);

    rt_spin_unlock_irqrestore(&vrpmsg->tx_lock, level);

    if (timeout)
    {
        rt_completion_wait(&vrpmsg->tx_done[idx], timeout);
    }

    return RT_EOK;
}

static const struct rt_rpmsg_ops virtio_rpmsg_ops =
{
    .create_endpoint = virtio_rpmsg_create_endpoint,
    .destroy_endpoint = virtio_rpmsg_destroy_endpoint,
    .send = virtio_rpmsg_send,
};

static void virtio_rpmsg_rx_done(struct rt_virtqueue *vq)
{
    rt_size_t len, msg_len;
    struct rt_rpmsg_device *rdev;
    struct rt_rpmsg_endpoint *ept;
    struct rt_rpmsg_endpoint_info info;
    struct virtio_rpmsg_hdr *msg;
    struct virtio_rpmsg *vrpmsg = vq->vdev->priv;

    rdev = &vrpmsg->parent;
    msg = rt_virtqueue_read_buf(vq, &len);

    if (!msg)
    {
        LOG_D("%s: not used buffer", rt_dm_dev_get_name(&vrpmsg->vdev->parent));
        return;
    }

    do {
        msg_len = rt_le16_to_cpu(msg->len);

        LOG_D("%s: %cX-HDR(src: %u, dst: %u, len: %u, flags: %u, reserved: %u)",
                rt_dm_dev_get_name(&vrpmsg->vdev->parent), 'R',
                rt_le32_to_cpu(msg->src),
                rt_le32_to_cpu(msg->dst),
                msg_len,
                rt_le16_to_cpu(msg->flags),
                rt_le32_to_cpu(msg->reserved));

        info.src = rt_le32_to_cpu(msg->dst);
        info.dst = RT_RPMSG_ADDR_ANY;
        info.name[0] = '\0';

        if (rt_le32_to_cpu(msg->dst) == RT_RPMSG_NS_ADDR && vrpmsg->ns)
        {
            ept = rt_rpmsg_find_endpoint(vrpmsg->ns, &info);
        }
        else
        {
            ept = rt_rpmsg_find_endpoint(rdev, &info);
        }

        if (ept && ept->rx_callback)
        {
            ept->rx_callback(rdev, rt_le32_to_cpu(msg->src), msg->data, msg_len);
        }

        rt_virtqueue_add_inbuf(vq, msg, VIRTIO_RPMSG_MAX_BUF_SIZE);

        rt_virtqueue_kick(vq);

        msg = rt_virtqueue_read_buf(vq, &len);
    } while (msg);
}

static void virtio_rpmsg_tx_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_rpmsg_tx_buf *tx_buf;
    struct virtio_rpmsg *vrpmsg = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vrpmsg->tx_lock);

    while ((tx_buf = rt_virtqueue_read_buf(vq, RT_NULL)))
    {
        rt_completion_done(&vrpmsg->tx_done[tx_buf->idx]);
    }

    rt_spin_unlock_irqrestore(&vrpmsg->tx_lock, level);
}

static rt_err_t virtio_rpmsg_vq_init(struct virtio_rpmsg *vrpmsg)
{
    rt_err_t err;
    rt_size_t vqs_nr = 2, qsize;
    void *rx_buffer;
    const char *names[RT_ARRAY_SIZE(vrpmsg->vqs)];
    rt_virtqueue_callback cbs[RT_ARRAY_SIZE(vrpmsg->vqs)];
    struct rt_virtio_device *vdev = vrpmsg->vdev;
    struct rt_virtqueue *vq;

    names[QUEUE_RX] = "rx";
    names[QUEUE_TX] = "tx";

    cbs[QUEUE_RX] = &virtio_rpmsg_rx_done;
    cbs[QUEUE_TX] = &virtio_rpmsg_tx_done;

    err = rt_virtio_virtqueue_install(vdev, vqs_nr, vrpmsg->vqs, names, cbs);

    if (err)
    {
        return err;
    }

    qsize = rt_virtqueue_get_virtq_size(vrpmsg->vqs[QUEUE_TX]);
    if (!(vrpmsg->tx_done = rt_malloc(sizeof(vrpmsg->tx_done[0]) * qsize)))
    {
        return -RT_ENOMEM;
    }

    for (int idx = 0; idx < qsize; ++idx)
    {
        rt_completion_init(&vrpmsg->tx_done[idx]);
    }

    vrpmsg->tx_buffer = rt_malloc(qsize * sizeof(struct virtio_rpmsg_tx_buf) +
            rt_virtqueue_get_virtq_size(vrpmsg->vqs[QUEUE_RX]) * VIRTIO_RPMSG_MAX_BUF_SIZE);

    if (!vrpmsg->tx_buffer)
    {
        return -RT_ENOMEM;
    }

    vq = vrpmsg->vqs[QUEUE_RX];
    rx_buffer = vrpmsg->tx_buffer + qsize * sizeof(struct virtio_rpmsg_tx_buf);

    for (int idx = 0; idx < qsize; ++idx, rx_buffer += VIRTIO_RPMSG_MAX_BUF_SIZE)
    {
        rt_virtqueue_add_inbuf(vq, rx_buffer, VIRTIO_RPMSG_MAX_BUF_SIZE);

        rt_virtqueue_submit(vq);
    }

    rt_virtqueue_notify(vq);

    return err;
}

static void virtio_rpmsg_vq_finit(struct virtio_rpmsg *vrpmsg)
{
    if (vrpmsg->vqs[0])
    {
        rt_virtio_virtqueue_release(vrpmsg->vdev);
    }
    if (vrpmsg->tx_done)
    {
        rt_free(vrpmsg->tx_done);
    }
    if (vrpmsg->tx_buffer)
    {
        rt_free(vrpmsg->tx_buffer);
    }
}

static rt_err_t virtio_rpmsg_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err = RT_EOK;
    struct virtio_rpmsg *vrpmsg;

    if (rt_rpmsg_mode() == RT_RPMSG_MODE_SLAVE)
    {
        _queue_rx = 0;
        _queue_tx = 1;
    }
    else
    {
        _queue_tx = 0;
        _queue_rx = 1;
    }

    vrpmsg = rt_calloc(1, sizeof(*vrpmsg));

    if (!vrpmsg)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vrpmsg;
    vrpmsg->vdev = vdev;
    vdev->parent.user_data = vrpmsg;

    if ((err = virtio_rpmsg_vq_init(vrpmsg)))
    {
        goto _fail;
    }

    rt_spin_lock_init(&vrpmsg->tx_lock);

    rt_strncpy(vrpmsg->parent.id.name, "rpmsg-char", sizeof(vrpmsg->parent.id.name));
    vrpmsg->parent.ops = &virtio_rpmsg_ops;
    vrpmsg->parent.priv = vrpmsg;

    if ((err = rt_rpmsg_device_register(&vrpmsg->parent)))
    {
        goto _fail;
    }

    /* Enable the name service */
    if ((vrpmsg->supp_ns = rt_virtio_has_feature(vdev, VIRTIO_RPMSG_F_NS)))
    {
        vrpmsg->ns = rt_calloc(1, sizeof(*vrpmsg->ns));

        if (!vrpmsg->ns)
        {
            goto _fail_ns;
        }

        rt_strncpy(vrpmsg->ns->id.name, "rpmsg-name-service", RT_RPMSG_NAME_SIZE);
        vrpmsg->ns->ops = &virtio_rpmsg_ops;
        vrpmsg->ns->priv = vrpmsg;

        if ((err = rt_rpmsg_device_register(vrpmsg->ns)))
        {
            goto _fail_ns;
        }
    }

    return RT_EOK;

_fail_ns:
    rt_bus_remove_device(&vrpmsg->parent.parent);

_fail:
    virtio_rpmsg_vq_finit(vrpmsg);
    rt_free(vrpmsg);

    return err;
}

static rt_err_t virtio_rpmsg_remove(struct rt_virtio_device *vdev)
{
    struct virtio_rpmsg *vrpmsg = vdev->parent.user_data;

    rt_bus_remove_device(&vrpmsg->parent.parent);

    if (vrpmsg->ns)
    {
        rt_bus_remove_device(&vrpmsg->ns->parent);
    }

    virtio_rpmsg_vq_finit(vrpmsg);
    rt_free(vrpmsg);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_rpmsg_ids[] =
{
    { VIRTIO_DEVICE_ID_RPMSG, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_rpmsg_driver =
{
    .ids = virtio_rpmsg_ids,
    .features =
        RT_BIT(VIRTIO_RPMSG_F_NS)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_rpmsg_probe,
    .remove = virtio_rpmsg_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_rpmsg_driver);
