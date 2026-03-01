/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.net"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_aspace.h>
#include <netif/ethernetif.h>

#include "virtio_config/virtio-net.h"

#define QUEUE_RX(n) (n)
#define QUEUE_TX(n) ((n) + 1)

rt_packed(struct net_packet
{
    struct virtio_net_hdr hdr;

    rt_uint8_t mss[VIRTIO_NET_MSS];
});

struct virtio_net
{
    struct eth_device parent;
    struct rt_virtio_device *vdev;

    rt_uint16_t status;

    int max_pairs;
    int request_num;
    void (*virtqueue_add_net_packet)(struct rt_virtqueue *, struct net_packet *, rt_size_t);
    struct rt_virtqueue *vqs[RT_CPUS_NR * 2];

    rt_list_t rx_vq_nodes;
    struct rt_spinlock rx_lock;

    struct net_packet *tx_packet;
    struct net_packet *rx_packet;
};

#define raw_to_virtio_net(raw) \
        rt_container_of(rt_container_of(raw, struct eth_device, parent), struct virtio_net, parent)

static void virtqueue_add_net_packet_split(struct rt_virtqueue *vq,
        struct net_packet *packet, rt_size_t len)
{
    rt_virtqueue_add_outbuf(vq, packet, sizeof(packet->hdr) + len);
}

static void virtqueue_add_net_packet_packed(struct rt_virtqueue *vq,
        struct net_packet *packet, rt_size_t len)
{
    rt_virtqueue_add_outbuf(vq, &packet->hdr, sizeof(packet->hdr));
    rt_virtqueue_add_outbuf(vq, &packet->mss, len);
}

static rt_err_t virtio_net_tx(rt_device_t dev, struct pbuf *p)
{
    struct rt_virtqueue *vq;
    struct net_packet *packet;
    struct virtio_net *vnet = raw_to_virtio_net(dev);

    vq = vnet->vqs[QUEUE_TX(rt_hw_cpu_id() % vnet->max_pairs)];
    rt_virtqueue_wait_prepare(vq, vnet->request_num);

    packet = &vnet->tx_packet[vq->index * rt_virtqueue_next_buf_index(vq)];
    packet->hdr.flags = 0;
    packet->hdr.gso_type = 0;
    packet->hdr.hdr_len = 0;
    packet->hdr.gso_size = 0;
    packet->hdr.csum_start = 0;
    packet->hdr.csum_offset = 0;
    packet->hdr.num_buffers = 0;

    RT_ASSERT(p->tot_len <= sizeof(packet->mss));

    pbuf_copy_partial(p, &packet->mss, p->tot_len, 0);

    vnet->virtqueue_add_net_packet(vq, packet, p->tot_len);

    rt_virtqueue_kick(vq);

    return RT_EOK;
}

static struct pbuf *virtio_net_rx(rt_device_t dev)
{
    rt_size_t size;
    rt_ubase_t level;
    struct pbuf *p = RT_NULL;
    struct net_packet *packet;
    struct rt_virtqueue *vq;
    struct virtio_net *vnet = raw_to_virtio_net(dev);

    level = rt_spin_lock_irqsave(&vnet->rx_lock);

    rt_list_for_each_entry(vq, &vnet->rx_vq_nodes, user_list)
    {
        packet = rt_virtqueue_read_buf(vq, &size);

        if (!packet)
        {
            rt_list_remove(&vq->user_list);
            break;
        }
        size -= sizeof(packet->hdr);

        rt_spin_unlock_irqrestore(&vnet->rx_lock, level);

        p = pbuf_alloc(PBUF_RAW, size, PBUF_RAM);

        if (!p)
        {
            return RT_NULL;
        }

        rt_memcpy(p->payload, &packet->mss, size);

        level = rt_spin_lock_irqsave(&vnet->rx_lock);

        if (!rt_virtqueue_poll(vq, packet - vnet->rx_packet))
        {
            rt_list_remove(&vq->user_list);
        }

        rt_virtqueue_add_inbuf(vq, packet, sizeof(*packet));

        rt_virtqueue_kick(vq);

        break;
    }

    rt_spin_unlock_irqrestore(&vnet->rx_lock, level);

    return p;
}

static rt_err_t virtio_net_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    rt_uint8_t *mac;
    struct virtio_net *vnet = raw_to_virtio_net(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        mac = args;

        if (!mac)
        {
            err = -RT_EINVAL;
            break;
        }

        for (int i = 0; i < 6; ++i)
        {
            rt_virtio_read_config(vnet->vdev, struct virtio_net_config, mac[i], &mac[i]);
        }
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_net_ops =
{
    .control = virtio_net_control,
};
#endif

static void virtio_net_rx_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_net *vnet = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vnet->rx_lock);

    rt_list_insert_before(&vnet->rx_vq_nodes, &vq->user_list);

    rt_spin_unlock_irqrestore(&vnet->rx_lock, level);

    eth_device_ready(&vnet->parent);
}

static void virtio_net_tx_done(struct rt_virtqueue *vq)
{
    rt_virtqueue_read_buf(vq, RT_NULL);
}

static void virtio_net_config_changed(struct rt_virtio_device *vdev)
{
    rt_uint16_t status;
    rt_bool_t link_up;
    struct virtio_net *vnet = vdev->priv;

    if (!rt_virtio_has_feature(vdev, VIRTIO_NET_F_STATUS))
    {
        return;
    }

    rt_virtio_read_config(vdev, struct virtio_net_config, status, &status);

    /* Remove other status bit */
    status &= VIRTIO_NET_S_LINK_UP;

    if (vnet->status == status)
    {
        /* Status no change */
        return;
    }

    link_up = !!((vnet->status = status) & VIRTIO_NET_S_LINK_UP);

    LOG_D("%s linkchange to %s", rt_dm_dev_get_name(&vdev->parent), link_up ? "up" : "down");

    eth_device_linkchange(&vnet->parent, link_up);
}

static rt_err_t virtio_net_vq_init(struct virtio_net *vnet)
{
    rt_err_t err;
    rt_size_t vqs_nr = 2, qsize;
    const char *names[RT_ARRAY_SIZE(vnet->vqs)];
    rt_virtqueue_callback cbs[RT_ARRAY_SIZE(vnet->vqs)];
    struct rt_virtio_device *vdev = vnet->vdev;

    if (rt_virtio_has_feature(vdev, VIRTIO_NET_F_MQ) ||
        rt_virtio_has_feature(vdev, VIRTIO_NET_F_RSS))
    {
        rt_virtio_read_config(vdev, struct virtio_net_config, max_virtqueue_pairs, &vqs_nr);
        vqs_nr *= 2;
    }

    for (int i = 0; i < vqs_nr; i += 2)
    {
        int rx = QUEUE_RX(i), tx = QUEUE_TX(i);

        names[rx] = "rx";
        names[tx] = "tx";

        cbs[rx] = &virtio_net_rx_done;
        cbs[tx] = &virtio_net_tx_done;
    }

    vnet->max_pairs = vqs_nr / 2;
    err = rt_virtio_virtqueue_install(vdev, vqs_nr, vnet->vqs, names, cbs);

    if (err)
    {
        return err;
    }

    qsize = rt_virtqueue_get_virtq_size(vnet->vqs[QUEUE_TX(0)]);

    if (!(vnet->tx_packet = rt_malloc(sizeof(vnet->tx_packet[0]) * vqs_nr * qsize)))
    {
        return -RT_ENOMEM;
    }

    qsize = rt_virtqueue_get_virtq_size(vnet->vqs[QUEUE_RX(0)]);

    if (!(vnet->rx_packet = rt_malloc(sizeof(vnet->rx_packet[0]) * vqs_nr * qsize)))
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < vqs_nr; i += 2)
    {
        int rx = QUEUE_RX(i);
        struct net_packet *packet;
        struct rt_virtqueue *vq = vnet->vqs[rx];

        packet = &vnet->rx_packet[rx * qsize];

        for (int idx = 0; idx < qsize; ++idx, ++packet)
        {
            rt_virtqueue_add_inbuf(vq, packet, sizeof(*packet));

            rt_virtqueue_submit(vq);
        }

        rt_virtqueue_notify(vq);
    }

    return RT_EOK;
}

static void virtio_net_vq_finit(struct virtio_net *vnet)
{
    if (vnet->vqs[0])
    {
        rt_virtio_virtqueue_release(vnet->vdev);
    }
    if (vnet->tx_packet)
    {
        rt_free(vnet->tx_packet);
    }
    if (vnet->rx_packet)
    {
        rt_free(vnet->rx_packet);
    }
}

static rt_err_t virtio_net_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err = RT_EOK;
    struct virtio_net *vnet = rt_calloc(1, sizeof(*vnet));

    if (!vnet)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vnet;
    vnet->vdev = vdev;
    vdev->parent.user_data = vnet;
#ifdef RT_USING_DEVICE_OPS
    vnet->parent.parent.ops = &virtio_net_ops;
#else
    vnet->parent.parent.control = virtio_net_control;
#endif
    vnet->parent.eth_tx = virtio_net_tx;
    vnet->parent.eth_rx = virtio_net_rx;

    if (rt_virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
    {
        vnet->request_num = 2;
        vnet->virtqueue_add_net_packet = &virtqueue_add_net_packet_packed;
    }
    else
    {
        vnet->request_num = 1;
        vnet->virtqueue_add_net_packet = &virtqueue_add_net_packet_split;
    }

    if ((err = virtio_net_vq_init(vnet)))
    {
        goto _fail;
    }

    rt_list_init(&vnet->rx_vq_nodes);
    rt_spin_lock_init(&vnet->rx_lock);

    if ((err = rt_dm_dev_set_name_auto(&vnet->parent.parent, "e")) < 0)
    {
        goto _fail;
    }

    if ((err = eth_device_init(&vnet->parent, rt_dm_dev_get_name(&vnet->parent.parent))))
    {
        goto _fail;
    }

    eth_device_linkchange(&vnet->parent, RT_TRUE);

    return RT_EOK;

_fail:
    virtio_net_vq_finit(vnet);
    rt_free(vnet);

    return err;
}

static rt_err_t virtio_net_remove(struct rt_virtio_device *vdev)
{
    struct virtio_net *vnet = vdev->parent.user_data;

    eth_device_linkchange(&vnet->parent, RT_FALSE);
    eth_device_deinit(&vnet->parent);

    virtio_net_vq_finit(vnet);
    rt_free(vnet);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_net_ids[] =
{
    { VIRTIO_DEVICE_ID_NET, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_net_driver =
{
    .ids = virtio_net_ids,
    .features =
        RT_BIT(VIRTIO_NET_F_MTU)
      | RT_BIT(VIRTIO_NET_F_MAC)
      | RT_BIT(VIRTIO_NET_F_MRG_RXBUF)
      | RT_BIT(VIRTIO_NET_F_STATUS)
      | RT_BIT(VIRTIO_NET_F_CTRL_RX)
      | RT_BIT(VIRTIO_NET_F_CTRL_VLAN)
      | RT_BIT(VIRTIO_NET_F_CTRL_RX_EXTRA)
      | RT_BIT(VIRTIO_NET_F_GUEST_ANNOUNCE)
      | RT_BIT(VIRTIO_NET_F_MQ)
      | RT_BIT(VIRTIO_NET_F_CTRL_MAC_ADDR)
      | RT_BIT(VIRTIO_NET_F_SPEED_DUPLEX)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_net_probe,
    .remove = virtio_net_remove,
    .config_changed = virtio_net_config_changed,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_net_driver);
