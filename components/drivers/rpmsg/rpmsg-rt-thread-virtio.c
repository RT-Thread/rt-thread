/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <mmu.h>

#define DBG_TAG "rpmsg.rt-thread.virtio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "../virtio/virtio_config/virtio-rpmsg.h"
#include "../virtio/virtio_internal.h"

/*
 * RPMsg virtio AMP device driver
 *
 * The AMP OS device(s) may be instantiated in one of three equivalent way:
 *
 * Device Tree node, eg.:
 *
 *      rpmsg_virtio_master {
 *          compatible = "rt-thread,virtio-rpmsg";
 *          shmem = <&soc_sram>;
 *          mboxes = <&soc_mailbox 0>;
 *          queue-max = <64>;
 *          master;
 *      }
 *
 *      rpmsg_virtio_slave {
 *          compatible = "rt-thread,virtio-rpmsg";
 *          shmem = <&soc_sram>;
 *          mboxes = <&soc_mailbox 1>;
 *          queue-max = <64>;
 *          slave;
 *      }
 *
 * The property "queue-max" must be equal.
 */

#define RPMSG_VIRTIO_REG_MASTER_QUEUE_DESC  0x00 /* <RW> Virtual queue's master TX descriptor Area offset from share memory */
#define RPMSG_VIRTIO_REG_MASTER_QUEUE_AVAIL 0x04 /* <RW> Virtual queue's master TX available Ring (Driver Area) offset from share memory */
#define RPMSG_VIRTIO_REG_MASTER_QUEUE_USED  0x08 /* <RW> Virtual queue's master TX used Ring (Device Area) offset from share memory */
#define RPMSG_VIRTIO_REG_SLAVE_QUEUE_DESC   0x0c /* <RW> ... slave TX ... */
#define RPMSG_VIRTIO_REG_SLAVE_QUEUE_AVAIL  0x10 /* <RW> ... slave TX ... */
#define RPMSG_VIRTIO_REG_SLAVE_QUEUE_USED   0x14 /* <RW> ... slave TX ... */

#define RPMSG_VIRTIO_EVENT_LINK             RT_BIT(0)
#define RPMSG_VIRTIO_EVENT_QUEUE            RT_BIT(1)

typedef rt_uint32_t rpmsg_dma_tag;

struct rpmsg_virtio
{
    struct rt_virtio_device parent;
    struct rt_mbox_client mbox_client;

    rt_bool_t is_master;
    rt_uint8_t status;
    rt_uint32_t queue_max;

    void *shmem;
    void *regs;
    struct rt_mbox_chan *chan;

    void *pool;
    rt_slab_t slab;

    rt_uint16_t next_idx;
    struct virtq rx_virtq, peer_tx_virtq;

    struct rt_spinlock spinlock;
};

#define raw_to_rpmsg_virtio(raw) rt_container_of(raw, struct rpmsg_virtio, parent)

#define rpmsg_virtio_readl(rv, name) \
    rt_le32_to_cpu(HWREG32((rv)->regs + RPMSG_VIRTIO_REG_##name))
#define rpmsg_virtio_writel(rv, name, value) \
    HWREG32((rv)->regs + RPMSG_VIRTIO_REG_##name) = rt_cpu_to_le32(value)

static void rpmsg_virtio_rx_callback(struct rt_mbox_client *client, void *data)
{
    rt_ubase_t level;
    rt_uint16_t idx_inc = 0;
    rt_uint32_t *event = data;
    struct rt_virtqueue *vq;
    struct rt_virtio_device *vdev;
    struct virtq *rx_virtq, *tx_virtq;
    struct rpmsg_virtio *rv = rt_container_of(client, struct rpmsg_virtio, mbox_client);

    if (*event & RPMSG_VIRTIO_EVENT_LINK)
    {
        rt_ubase_t desc, avail, used;

        if (rv->is_master)
        {
            desc = rpmsg_virtio_readl(rv, SLAVE_QUEUE_DESC);
            avail = rpmsg_virtio_readl(rv, SLAVE_QUEUE_AVAIL);
            used = rpmsg_virtio_readl(rv, SLAVE_QUEUE_USED);
        }
        else
        {
            desc = rpmsg_virtio_readl(rv, MASTER_QUEUE_DESC);
            avail = rpmsg_virtio_readl(rv, MASTER_QUEUE_AVAIL);
            used = rpmsg_virtio_readl(rv, MASTER_QUEUE_USED);
        }

        rv->peer_tx_virtq.desc = (void *)rv->shmem + desc;
        rv->peer_tx_virtq.avail = (void *)rv->shmem + avail;
        rv->peer_tx_virtq.used = (void *)rv->shmem + used;
        rv->next_idx = 0;
    }

    rx_virtq = &rv->rx_virtq;
    tx_virtq = &rv->peer_tx_virtq;
    vdev = &rv->parent;

    /* Process local RX queue */
    while (tx_virtq->avail && rv->next_idx != tx_virtq->avail->idx)
    {
        rt_uint16_t tx_idx, rx_idx, tx_used_idx, rx_used_idx;
        struct virtq_desc *tx_desc, *rx_desc;

        tx_idx = virtio16_to_cpu(vdev, tx_virtq->avail->ring[rv->next_idx % tx_virtq->num]);
        rx_idx = virtio16_to_cpu(vdev, rx_virtq->avail->ring[rv->next_idx % rx_virtq->num]);
        tx_used_idx = virtio16_to_cpu(vdev, tx_virtq->used->idx) % tx_virtq->num;
        rx_used_idx = virtio16_to_cpu(vdev, rx_virtq->used->idx) % rx_virtq->num;
        rt_hw_rmb();

        tx_desc = &tx_virtq->desc[tx_idx];
        rx_desc = &rx_virtq->desc[rx_idx];

        *(rpmsg_dma_tag *)(rv->shmem +
                virtio64_to_cpu(vdev, rx_desc->addr) +
                virtio32_to_cpu(vdev, rx_desc->len)) = virtio64_to_cpu(vdev, tx_desc->addr);

        tx_virtq->used->ring[tx_used_idx].id = tx_idx;
        tx_virtq->used->ring[tx_used_idx].len = cpu_to_virtio32(vdev, 0);
        rx_virtq->used->ring[rx_used_idx].id = rx_idx;
        rx_virtq->used->ring[rx_used_idx].len = rx_virtq->desc[rx_idx].len;

        ++rx_virtq->used->idx;
        ++rv->next_idx;
        ++idx_inc;
        rt_hw_wmb();
    }

    if (*event & RPMSG_VIRTIO_EVENT_QUEUE)
    {
        level = rt_spin_lock_irqsave(&rv->spinlock);

        rt_list_for_each_entry(vq, &rv->parent.vq_node, list)
        {
            rt_virtqueue_isr(vq->index, vq);
        }

        rt_spin_unlock_irqrestore(&rv->spinlock, level);
    }

    /* Process peer TX queue */
    if (idx_inc)
    {
        tx_virtq->used->idx += cpu_to_virtio16(vdev, idx_inc);
        rt_hw_wmb();
    }
}

static rt_bool_t rpmsg_virtio_notify(struct rt_virtqueue *vq)
{
    rt_uint32_t event;
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vq->vdev);

    event = RPMSG_VIRTIO_EVENT_QUEUE;
    rt_mbox_send(rv->chan, &event, RT_WAITING_FOREVER);

    return RT_TRUE;
}

static rt_err_t rpmsg_virtio_get_status(struct rt_virtio_device *vdev,
        rt_uint8_t *out_status)
{
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    *out_status = rv->status;

    return RT_EOK;
}

static rt_err_t rpmsg_virtio_set_status(struct rt_virtio_device *vdev,
        rt_uint8_t status)
{
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    rv->status = status;

    return RT_EOK;
}

static rt_err_t rpmsg_virtio_get_features(struct rt_virtio_device *vdev,
        rt_uint64_t *out_features)
{
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    *out_features = RT_BIT_ULL(VIRTIO_F_VERSION_1) | RT_BIT_ULL(VIRTIO_F_ANY_LAYOUT);

    if (rv->is_master)
    {
        *out_features |= RT_BIT_ULL(VIRTIO_RPMSG_F_NS);
    }

    return RT_EOK;
}

static rt_err_t rpmsg_virtio_set_features(struct rt_virtio_device *vdev)
{
    return RT_EOK;
}

static rt_err_t rpmsg_virtio_get_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, void *dst, int length)
{
    return -RT_ENOSYS;
}

static rt_err_t rpmsg_virtio_set_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, const void *src, int length)
{
    return -RT_ENOSYS;
}

static rt_err_t rpmsg_virtio_install_vqs(struct rt_virtio_device *vdev, int vqs_nr,
        struct rt_virtqueue *vqs[], const char *names[], rt_virtqueue_callback cbs[])
{
    rt_uint32_t event;
    struct rt_virtqueue *vq;
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    if (vqs_nr != 2)
    {
        return -RT_EINVAL;
    }

    /* Master TX or slave RX */
    vq = rt_virtqueue_create(vdev, names[0], 0, rv->queue_max, ARCH_PAGE_SIZE,
            rpmsg_virtio_notify, cbs[0], RT_NULL);

    if (!vq)
    {
        goto _fail;
    }
    vqs[0] = vq;

    /* Master RX or slave TX */
    vq = rt_virtqueue_create(vdev, names[1], 1, rv->queue_max, ARCH_PAGE_SIZE,
            rpmsg_virtio_notify, cbs[1], RT_NULL);

    if (!vq)
    {
        goto _fail;
    }
    vqs[1] = vq;

    if (rv->is_master)
    {
        rv->rx_virtq.desc = (void *)rt_virtqueue_get_desc_addr(vqs[1]);
        rv->rx_virtq.avail = (void *)rt_virtqueue_get_avail_addr(vqs[1]);
        rv->rx_virtq.used = (void *)rt_virtqueue_get_used_addr(vqs[1]);

        rpmsg_virtio_writel(rv, MASTER_QUEUE_DESC,
                (rt_ubase_t)rt_virtqueue_get_desc_addr(vqs[0]) - (rt_ubase_t)rv->shmem);
        rpmsg_virtio_writel(rv, MASTER_QUEUE_AVAIL,
                (rt_ubase_t)rt_virtqueue_get_avail_addr(vqs[0]) - (rt_ubase_t)rv->shmem);
        rpmsg_virtio_writel(rv, MASTER_QUEUE_USED,
                (rt_ubase_t)rt_virtqueue_get_used_addr(vqs[0]) - (rt_ubase_t)rv->shmem);
    }
    else
    {
        rv->rx_virtq.desc = (void *)rt_virtqueue_get_desc_addr(vqs[0]);
        rv->rx_virtq.avail = (void *)rt_virtqueue_get_avail_addr(vqs[0]);
        rv->rx_virtq.used = (void *)rt_virtqueue_get_used_addr(vqs[0]);

        rpmsg_virtio_writel(rv, SLAVE_QUEUE_DESC,
                (rt_ubase_t)rt_virtqueue_get_desc_addr(vqs[1]) - (rt_ubase_t)rv->shmem);
        rpmsg_virtio_writel(rv, SLAVE_QUEUE_AVAIL,
                (rt_ubase_t)rt_virtqueue_get_avail_addr(vqs[1]) - (rt_ubase_t)rv->shmem);
        rpmsg_virtio_writel(rv, SLAVE_QUEUE_USED,
                (rt_ubase_t)rt_virtqueue_get_used_addr(vqs[1]) - (rt_ubase_t)rv->shmem);

        rv->peer_tx_virtq.desc = (void *)rv->shmem + rpmsg_virtio_readl(rv, MASTER_QUEUE_DESC);
        rv->peer_tx_virtq.avail = (void *)rv->shmem + rpmsg_virtio_readl(rv, MASTER_QUEUE_AVAIL);
        rv->peer_tx_virtq.used = (void *)rv->shmem + rpmsg_virtio_readl(rv, MASTER_QUEUE_USED);
    }
    rv->rx_virtq.num = rv->queue_max;
    rv->peer_tx_virtq.num = rv->queue_max;

    /* Ask peer to link */
    event = RPMSG_VIRTIO_EVENT_LINK;
    rt_mbox_send(rv->chan, &event, RT_WAITING_FOREVER);

    return RT_EOK;

_fail:
    rt_virtio_virtqueue_release(vdev);

    return -RT_ERROR;
}

static rt_err_t rpmsg_virtio_release_vqs(struct rt_virtio_device *vdev)
{
    struct rt_virtqueue *vq, *vq_next;
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    rt_list_for_each_entry_safe(vq, vq_next, &rv->parent.vq_node, list)
    {
        rt_virtqueue_delete(&rv->parent, vq);
    }

    return RT_EOK;
}

static rt_err_t rpmsg_virtio_control_vqs(struct rt_virtio_device *vdev,
        rt_uint32_t cfg, void *data)
{
    return -RT_ENOSYS;
}

static rt_err_t rpmsg_virtio_generation(struct rt_virtio_device *vdev,
        rt_uint32_t *out_counter)
{
    return RT_EOK;
}

static rt_err_t rpmsg_virtio_reset(struct rt_virtio_device *vdev)
{
    struct rpmsg_virtio *rv = raw_to_rpmsg_virtio(vdev);

    rv->status = 0;

    return RT_EOK;
}

static const struct rt_virtio_transport rpmsg_virtio_trans =
{
    .get_status = rpmsg_virtio_get_status,
    .set_status = rpmsg_virtio_set_status,
    .get_features = rpmsg_virtio_get_features,
    .set_features = rpmsg_virtio_set_features,
    .get_config = rpmsg_virtio_get_config,
    .set_config = rpmsg_virtio_set_config,
    .install_vqs = rpmsg_virtio_install_vqs,
    .release_vqs = rpmsg_virtio_release_vqs,
    .control_vqs = rpmsg_virtio_control_vqs,
    .generation = rpmsg_virtio_generation,
    .reset = rpmsg_virtio_reset,
};

static void *rpmsg_virtio_dma_alloc(struct rt_device *dev, rt_size_t size,
        rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    void *dma_buffer;
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);
    struct rpmsg_virtio *rv = rt_container_of(vdev, struct rpmsg_virtio, parent);

    /* Ignore flags */
    if (!(dma_buffer = rt_slab_alloc(rv->slab, size)))
    {
        return dma_buffer;
    }

    if (dma_handle)
    {
        *dma_handle = (rt_ubase_t)(dma_buffer - rv->shmem);
    }

    return dma_buffer;
}

static void rpmsg_virtio_dma_free(struct rt_device *dev, rt_size_t size,
        void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);
    struct rpmsg_virtio *rv = rt_container_of(vdev, struct rpmsg_virtio, parent);

    rt_slab_free(rv->slab, cpu_addr);
}

static rt_err_t rpmsg_virtio_dma_sync_out_data(struct rt_device *dev,
        void *data, rt_size_t size, rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    void *dma_buffer;

    dma_buffer = rpmsg_virtio_dma_alloc(dev, size + sizeof(rpmsg_dma_tag), dma_handle, flags);

    if (!dma_buffer)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(dma_buffer, data, size);

    return RT_EOK;
}

static rt_err_t rpmsg_virtio_dma_sync_in_data(struct rt_device *dev,
        void *out_data, rt_size_t size, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    void *dma_buffer;
    rpmsg_dma_tag dma_tag;
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);
    struct rpmsg_virtio *rv = rt_container_of(vdev, struct rpmsg_virtio, parent);

    dma_buffer = rv->shmem + dma_handle;
    dma_tag = *(rpmsg_dma_tag *)(dma_buffer + size);

    rt_memcpy(out_data, rv->shmem + dma_tag, size);

    size += sizeof(rpmsg_dma_tag);
    rpmsg_virtio_dma_free(dev, size, dma_buffer, dma_handle, flags);

    return RT_EOK;
}

static const struct rt_dma_map_ops rpmsg_virtio_dma_ops =
{
    .alloc = rpmsg_virtio_dma_alloc,
    .free = rpmsg_virtio_dma_free,
    .sync_out_data = rpmsg_virtio_dma_sync_out_data,
    .sync_in_data = rpmsg_virtio_dma_sync_in_data,
};

static rt_err_t rpmsg_virtio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t addr, size;
    struct rt_ofw_node *shmem_np;
    struct rt_virtio_device *vdev;
    struct rt_device *dev = &pdev->parent;
    struct rpmsg_virtio *rv = rt_calloc(1, sizeof(*rv));

    if (!rv)
    {
        return -RT_ENOMEM;
    }

    rv->mbox_client.dev = dev;
    rv->mbox_client.rx_callback = rpmsg_virtio_rx_callback;

    rv->chan = rt_mbox_request_by_index(&rv->mbox_client, 0);

    if (rt_is_err_or_null(rv->chan))
    {
        err = -RT_EINVAL;
        LOG_E("Request mailbox fail");

        goto _fail;
    }

    vdev = &rv->parent;

    if ((err = rt_dm_dev_prop_read_u32(dev, "queue-max", &rv->queue_max)))
    {
        goto _fail;
    }

    shmem_np = rt_ofw_parse_phandle(dev->ofw_node, "shmem", 0);
    rt_ofw_get_address(shmem_np, 0, &addr, &size);
    rt_ofw_node_put(shmem_np);

    rv->shmem = rt_ioremap_cached((void *)addr, size);

    if (!rv->shmem)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rv->is_master = rt_dm_dev_prop_read_bool(dev, "master");
    rv->regs = rv->shmem;
    rv->pool = rv->shmem + ARCH_PAGE_SIZE;

    size = (size - ARCH_PAGE_SIZE) >> 1;

    if (!rv->is_master)
    {
        rv->pool += size;
    }

    if (!(rv->slab = rt_slab_init(rt_dm_dev_get_name(dev), rv->pool, size)))
    {
        LOG_E("Create AMP dma pool fail");

        err = -RT_ENOMEM;
        goto _fail;
    }
    rt_dma_device_set_ops(&vdev->parent, &rpmsg_virtio_dma_ops);
    vdev->dma_dispatch = RT_TRUE;

    rt_spin_lock_init(&rv->spinlock);

    vdev->id.device = VIRTIO_DEVICE_ID_RPMSG;
    vdev->id.vendor = 0x534f5452; /* RTOS */
    vdev->trans = &rpmsg_virtio_trans;
    vdev->parent.ofw_node = dev->ofw_node;

    if ((err = rt_virtio_device_register(vdev)))
    {
        goto _fail;
    }

    dev->user_data = rv;

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(rv->chan))
    {
        rt_mbox_release(rv->chan);
    }
    if (rv->shmem)
    {
        rt_iounmap(rv->shmem);
    }
    rt_free(rv);

    return err;
}

static rt_err_t rpmsg_virtio_remove(struct rt_platform_device *pdev)
{
    struct rpmsg_virtio *rv = pdev->parent.user_data;

    rt_bus_remove_device(&rv->parent.parent);

    rt_slab_detach(rv->slab);
    rt_mbox_release(rv->chan);
    rt_iounmap(rv->shmem);
    rt_free(rv);

    return RT_EOK;
}

static const struct rt_ofw_node_id rpmsg_virtio_ofw_ids[] =
{
    { .compatible = "rt-thread,virtio-rpmsg" },
    { /* sentinel */ }
};

static struct rt_platform_driver rpmsg_virtio_driver =
{
    .name = "rt-thread-virtio-rpmsg",
    .ids = rpmsg_virtio_ofw_ids,

    .probe = rpmsg_virtio_probe,
    .remove = rpmsg_virtio_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpmsg_virtio_driver);
