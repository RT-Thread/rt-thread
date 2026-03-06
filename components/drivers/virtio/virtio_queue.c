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

#define DBG_TAG "virtio.queue"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_aspace.h>

#include <drivers/dma.h>
#include <drivers/virtq.h>
#include <drivers/virtio.h>

#include "virtio_internal.h"

struct virtq_buffer_shadow
{
    rt_ubase_t dma_handle;
    void *dma_buf;

    rt_size_t size;
    rt_size_t chain_num;
};

struct virtqueue_split
{
    struct virtq virtq;
    rt_ubase_t virtq_dma;

    rt_uint16_t avail_idx_shadow;
    rt_uint16_t avail_flags_shadow;
    struct virtq_buffer_shadow buffer_shadow[0];
};

struct virtqueue_packed
{
    struct virtq virtq;
    rt_size_t virtq_size;
    rt_ubase_t virtq_dma;
    rt_ubase_t driver_event_dma;
    rt_ubase_t device_event_dma;

    rt_uint16_t last_used_idx;
    rt_uint16_t avail_used_flags;
    rt_uint16_t avail_wrap_counter;
    rt_uint16_t avail_flags_shadow;
    rt_uint16_t event_flags_shadow;
    struct virtq_buffer_shadow buffer_shadow[0];
};

static struct rt_virtqueue *vq_split_create(struct rt_virtio_device *vdev,
        const char *name, int index, int num, rt_uint32_t align,
        rt_virtqueue_notifier notify, rt_virtqueue_callback callback,
        struct rt_virtqueue_formula *formula)
{
    void *pages;
    rt_size_t size;
    struct virtqueue_split *vq_split;
    struct rt_virtqueue *vq = RT_NULL;
    struct virtq_buffer_shadow *buffer_shadow;

    /*
     * Layout:
     * +-----------------+
     * |   rt_virtqueue  |
     * +-----------------+
     * | virtqueue_split |
     * +-----------------+
     * |  buffer_shadow  |
     * +-----------------+
     */
    vq = rt_malloc(sizeof(*vq) +
            sizeof(struct virtqueue_split) +
            sizeof(struct virtq_buffer_shadow) * num);

    if (!vq)
    {
        return RT_NULL;
    }

    vq_split = (void *)vq + sizeof(*vq);
    buffer_shadow = (void *)vq_split + sizeof(*vq_split);
    rt_memset(buffer_shadow, 0, sizeof(*buffer_shadow) * num);

    /*
     *  +------------------+-----------+----------------------+
     *  | Virtqueue Part   | Alignment | Size                 |
     *  +------------------+-----------+----------------------+
     *  | Descriptor Table | 16        | 16 * (Queue Size)    |
     *  +------------------+-----------+----------------------+
     *  | Available Ring   | 2         | 6 + 2 * (Queue Size) |
     *  +------------------+-----------+----------------------+
     *  | Used Ring        | 4         | 6 + 8 * (Queue Size) |
     *  +------------------+-----------+----------------------+
     */
    size = virtq_size(RT_NULL, num, align);

    if (formula->page)
    {
        pages = formula->page;
    }
    else
    {
        pages = rt_dma_alloc(&vdev->parent, size, &vq_split->virtq_dma, RT_DMA_F_LINEAR);

        if (!pages)
        {
            rt_free(vq);

            return RT_NULL;
        }
    }

    rt_memset(pages, 0, size);
    virtq_init(&vq_split->virtq, num, pages, align);

    vq_split->avail_idx_shadow = 0;
    vq_split->avail_flags_shadow = 0;

    vq->name = name;
    vq->index = index;
    vq->num_free = num;

    vq->callback = callback;

    vq->vq_split = vq_split;
    vq->packed_ring = RT_FALSE;

    vq->notify = notify;
    vq->event = rt_virtio_has_feature(vdev, VIRTIO_F_RING_EVENT_IDX);
    vq->event_triggered = RT_FALSE;
    vq->free_head = 0;
    vq->num_added = 0;
    vq->last_used_idx = 0;

    vq->vdev = vdev;

    if (!vq->callback)
    {
        vq_split->avail_flags_shadow |= VIRTQ_AVAIL_F_NO_INTERRUPT;

        if (!vq->event)
        {
            vq_split->virtq.avail->flags = cpu_to_virtio16(vdev,
                    vq_split->avail_flags_shadow);
        }
    }

    rt_memcpy(&vq->formula, formula, sizeof(*formula));

    return vq;
}

static rt_err_t vq_split_delete(struct rt_virtqueue *vq)
{
    rt_err_t err = RT_EOK;
    struct virtq *virtq;
    struct virtqueue_split *vq_split = vq->vq_split;
    struct rt_virtqueue_formula *formula = &vq->formula;

    if (!formula->page)
    {
        virtq = &vq_split->virtq;
        rt_dma_free(&vq->vdev->parent, virtq_size(virtq, 0, 0),
                (void *)virtq->desc, vq_split->virtq_dma, RT_DMA_F_LINEAR);
    }

    rt_free(vq);

    return err;
}

static rt_err_t vq_split_add_buf(struct rt_virtqueue *vq,
        void *dma_buf, rt_size_t size, rt_bool_t is_out)
{
    rt_err_t err;
    rt_uint16_t buf_id;
    rt_ubase_t dma_addr;
    rt_size_t virtq_num;
    int head, next, flags;
    struct virtq *virtq;
    struct virtq_desc *desc;
    struct virtqueue_split *vq_split;
    struct virtq_buffer_shadow *buffer_shadow;
    struct rt_virtio_device *vdev = vq->vdev;

    if (!vq->num_free)
    {
        LOG_D("%s.virtqueue[%s(%d)] add buffer.len = %d fail",
                rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, size);

        /* Recvice buffer NOW! */
        if (is_out)
        {
            vq->notify(vq);
        }

        return -RT_EFULL;
    }

    err = rt_dma_sync_out_data(&vdev->parent, dma_buf, size, &dma_addr, RT_DMA_F_LINEAR);

    if (err)
    {
        return err;
    }

    vq_split = vq->vq_split;
    virtq = &vq_split->virtq;
    virtq_num = virtq->num;

    head = vq->free_head++ & (virtq_num - 1);
    rt_hw_dsb();

    next = vq->free_head & (virtq_num - 1);
    desc = &virtq->desc[head];
    buffer_shadow = &vq_split->buffer_shadow[head];

    buffer_shadow->dma_handle = dma_addr;
    buffer_shadow->dma_buf = dma_buf;
    buffer_shadow->size = size;

    buf_id = (head - vq->num_added) & (virtq_num - 1);
    vq_split->buffer_shadow[buf_id].chain_num = vq->num_added + 1;

    flags = VIRTQ_DESC_F_NEXT;
    if (!is_out)
    {
        flags |= VIRTQ_DESC_F_WRITE;
    }

    desc->addr = cpu_to_virtio64(vdev, dma_addr);
    desc->len = cpu_to_virtio32(vdev, size);
    desc->flags = cpu_to_virtio16(vdev, flags);
    desc->next = cpu_to_virtio16(vdev, next);

    /* Update index  */
    ++vq->num_added;
    --vq->num_free;

    LOG_D("%s.virtqueue[%s(%d)] add buffer(%p, size = %d) head = %d",
            rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, dma_buf, size, head);

    return RT_EOK;
}

static rt_bool_t vq_split_submit(struct rt_virtqueue *vq)
{
    int head, prev;
    rt_uint16_t avail, num_added;
    struct rt_virtio_device *vdev = vq->vdev;
    struct virtqueue_split *vq_split = vq->vq_split;
    struct virtq *virtq = &vq_split->virtq;
    rt_size_t virtq_num = virtq->num;

    num_added = vq->num_added;
    head = vq->free_head;
    prev = (head - 1) & (virtq_num - 1);
    head = head - num_added;

    LOG_D("%s.virtqueue[%s(%d)] submit head = %d, num_added = %d, idx = %d",
            rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index,
            head & (virtq_num - 1), num_added, virtq->avail->idx);

    /* Reset list info */
    vq->num_added = 0;

    /* Clear last "next" flags */
    virtq->desc[prev].flags &= ~cpu_to_virtio16(vdev, VIRTQ_DESC_F_NEXT);
    virtq->desc[prev].next = 0;

    /* Tell the device the first index in our chain of descriptors */
    avail = vq_split->avail_idx_shadow & (virtq_num - 1);
    virtq->avail->ring[avail] = cpu_to_virtio32(vdev, head & (virtq_num - 1));

    /* Tell the device another avail ring entry is available */
    rt_hw_wmb();
    ++vq_split->avail_idx_shadow;
    virtq->avail->idx = cpu_to_virtio16(vdev, vq_split->avail_idx_shadow);

    if (vq->event)
    {
        rt_uint16_t old = vq_split->avail_idx_shadow - num_added;
        rt_uint16_t new = vq_split->avail_idx_shadow;

        return virtq_need_event(virtio16_to_cpu(vdev,
                *virtq_avail_event(virtq)), new, old);
    }

    return !(virtq->used->flags & cpu_to_virtio16(vdev, VIRTQ_USED_F_NO_NOTIFY));
}

static rt_bool_t vq_split_poll(struct rt_virtqueue *vq, rt_uint32_t last_used_idx)
{
    return (rt_uint16_t)last_used_idx != virtio16_to_cpu(vq->vdev, vq->vq_split->virtq.used->idx);
}

rt_inline rt_bool_t vq_split_pending(struct rt_virtqueue *vq)
{
    return vq->last_used_idx != virtio16_to_cpu(vq->vdev, vq->vq_split->virtq.used->idx);
}

static void vq_split_disable_callback(struct rt_virtqueue *vq)
{
    struct virtqueue_split *vq_split = vq->vq_split;
    struct virtq *virtq = &vq_split->virtq;

    if (!(vq_split->avail_flags_shadow & VIRTQ_AVAIL_F_NO_INTERRUPT))
    {
        vq_split->avail_flags_shadow |= VIRTQ_AVAIL_F_NO_INTERRUPT;

        if (vq->event)
        {
            *virtq_used_event(virtq) = 0;
        }
        else
        {
            virtq->avail->flags = cpu_to_virtio16(vq->vdev, vq_split->avail_flags_shadow);
        }
    }
}

static rt_uint32_t vq_split_enable_callback(struct rt_virtqueue *vq)
{
    struct virtqueue_split *vq_split = vq->vq_split;
    struct virtq *virtq = &vq_split->virtq;
    rt_uint16_t last_used_idx = vq->last_used_idx;

    if (vq_split->avail_flags_shadow & VIRTQ_AVAIL_F_NO_INTERRUPT)
    {
        vq_split->avail_flags_shadow &= ~VIRTQ_AVAIL_F_NO_INTERRUPT;

        if (!vq->event)
        {
            virtq->avail->flags = cpu_to_virtio16(vq->vdev, vq_split->avail_flags_shadow);
        }
    }

    *virtq_used_event(virtq) = cpu_to_virtio16(vq->vdev, last_used_idx);

    return last_used_idx;
}

static void *vq_split_read_buf(struct rt_virtqueue *vq, rt_size_t *out_len)
{
    void *buf;
    rt_err_t err;
    rt_uint32_t idx;
    rt_uint16_t last_used, next;
    rt_size_t chain_num;
    struct virtq *virtq;
    struct virtqueue_split *vq_split;
    struct virtq_buffer_shadow *buffer_shadow;
    struct rt_virtio_device *vdev = vq->vdev;

    if (!vq_split_pending(vq))
    {
        LOG_D("%s.virtqueue[%s(%d)] read buffer empty",
                rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index);

        return RT_NULL;
    }

    vq_split = vq->vq_split;
    virtq = &vq_split->virtq;

    last_used = vq->last_used_idx & (virtq->num - 1);
    next = idx = virtio32_to_cpu(vdev, virtq->used->ring[last_used].id);
    *out_len = virtio32_to_cpu(vdev, virtq->used->ring[last_used].len);
    rt_hw_dsb();

    buffer_shadow = &vq_split->buffer_shadow[idx];
    buf = buffer_shadow->dma_buf;
    chain_num = buffer_shadow->chain_num;

    LOG_D("%s.virtqueue[%s(%d)] read head = %d, buffer(%p, size = %d)",
            rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, idx, buf, *out_len);

    for (int i = 0; i < chain_num; ++i)
    {
        idx = next;
        next = virtq->desc[idx].next;

        if (virtq->desc[idx].flags & VIRTQ_DESC_F_WRITE ||
            vdev->dma_dispatch)
        {
            buffer_shadow = &vq_split->buffer_shadow[idx];
            err = rt_dma_sync_in_data(&vdev->parent,
                    buffer_shadow->dma_buf,
                    buffer_shadow->size,
                    buffer_shadow->dma_handle, RT_DMA_F_LINEAR);

            if (err)
            {
                LOG_E("%s.virtqueue[%s(%d)] read head = %d sync error = %s",
                        rt_dm_dev_get_name(&vdev->parent),
                        vq->name, vq->index, idx, rt_strerror(err));
            }
        }
    }

    vq->num_free += chain_num;
    ++vq->last_used_idx;

    if (!(vq_split->avail_flags_shadow & VIRTQ_AVAIL_F_NO_INTERRUPT))
    {
        HWREG16(virtq_used_event(virtq)) = cpu_to_virtio16(vq->vdev, vq->last_used_idx);
        rt_hw_dmb();
    }

    rt_hw_dsb();

    return buf;
}

static struct rt_virtqueue *vq_packed_create(struct rt_virtio_device *vdev,
        const char *name, int index, int num, int align,
        rt_virtqueue_notifier notify, rt_virtqueue_callback callback,
        struct rt_virtqueue_formula *formula)
{
    rt_size_t size, event_size;
    struct virtq *virtq;
    struct virtqueue_packed *vq_packed;
    struct rt_virtqueue *vq = RT_NULL;
    struct virtq_buffer_shadow *buffer_shadow;

    /*
     * Layout:
     * +------------------------+
     * |      rt_virtqueue      |
     * +------------------------+
     * |    virtqueue_packed    |
     * +------------------------+
     * |     buffer_shadow      |
     * +------------------------+
     */
    vq = rt_malloc(sizeof(*vq) +
            sizeof(struct virtqueue_packed) +
            sizeof(struct virtq_buffer_shadow) * num);

    if (!vq)
    {
        return RT_NULL;
    }

    vq_packed = (void *)vq + sizeof(*vq);
    buffer_shadow = (void *)vq_packed + sizeof(*vq_packed);
    rt_memset(buffer_shadow, 0, sizeof(*buffer_shadow) * num);

    /*
     *  +--------------------------+-----------+-------------------+
     *  | Virtqueue Part           | Alignment | Size              |
     *  +--------------------------+-----------+-------------------+
     *  | Descriptor Ring          | 16        | 16 * (Queue Size) |
     *  +--------------------------+-----------+-------------------+
     *  | Device Event Suppression | 4         | 4                 |
     *  +--------------------------+-----------+-------------------+
     *  | Driver Event Suppression | 4         | 4                 |
     *  +--------------------------+-----------+-------------------+
     */
    virtq = &vq_packed->virtq;

    size = num * sizeof(struct virtq_packed_desc);
    size = RT_ALIGN(size, 4);
    event_size = sizeof(struct virtq_packed_desc_event);
    vq_packed->virtq_size = size + event_size * 2;

    if (formula->page)
    {
        virtq->desc_packed = formula->page;
    }
    else
    {
        virtq->desc_packed = rt_dma_alloc(&vdev->parent,
                vq_packed->virtq_size, &vq_packed->virtq_dma, RT_DMA_F_LINEAR);

        if (!virtq->desc_packed)
        {
            rt_free(vq);

            return RT_NULL;
        }
    }

    virtq->driver_event = (void *)virtq->desc_packed + size;
    vq_packed->driver_event_dma = vq_packed->virtq_dma + size;

    virtq->device_event = (void *)virtq->driver_event + event_size;
    vq_packed->device_event_dma = vq_packed->driver_event_dma + event_size;

    rt_memset(virtq->desc_packed, 0, size);
    rt_memset(virtq->driver_event, 0, event_size);
    rt_memset(virtq->device_event, 0, event_size);
    virtq->num = num;
    virtq->align = align;

    vq_packed->avail_wrap_counter = 1;
    vq_packed->event_flags_shadow = 0;
    vq_packed->avail_used_flags = VIRTQ_DESC_F_AVAIL;

    vq->name = name;
    vq->index = index;
    vq->num_free = num;

    vq->callback = callback;

    vq->vq_packed = vq_packed;
    vq->packed_ring = RT_TRUE;

    vq->notify = notify;
    vq->event = rt_virtio_has_feature(vdev, VIRTIO_F_RING_EVENT_IDX);
    vq->event_triggered = RT_FALSE;
    vq->free_head = 0;
    vq->num_added = 0;
    vq->last_used_idx = 0 | RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR);

    vq->vdev = vdev;

    if (!vq->callback)
    {
        vq_packed->avail_flags_shadow = VIRTQ_PACKED_EVENT_FLAG_DISABLE;
        vq_packed->virtq.avail->flags = rt_cpu_to_le16(vq_packed->avail_flags_shadow);
    }

    rt_memcpy(&vq->formula, formula, sizeof(*formula));

    return vq;
}

static rt_err_t vq_packed_delete(struct rt_virtqueue *vq)
{
    rt_err_t err = RT_EOK;
    struct virtq *virtq;
    struct virtqueue_packed *vq_packed = vq->vq_packed;
    struct rt_virtqueue_formula *formula = &vq->formula;

    virtq = &vq_packed->virtq;

    if (virtq->desc_packed && !formula->page)
    {
        rt_dma_free(&vq->vdev->parent, vq_packed->virtq_size,
                (void *)virtq->desc_packed, vq_packed->virtq_dma, RT_DMA_F_LINEAR);
    }

    rt_free(vq);

    return err;
}

static rt_err_t vq_packed_add_buf(struct rt_virtqueue *vq,
        void *dma_buf, rt_size_t size, rt_bool_t is_out)
{
    rt_err_t err;
    rt_uint16_t buf_id;
    rt_ubase_t dma_addr;
    rt_size_t virtq_num;
    int head, flags;
    struct virtq *virtq;
    struct virtqueue_packed *vq_packed;
    struct virtq_packed_desc *desc_packed;
    struct virtq_buffer_shadow *buffer_shadow;
    struct rt_virtio_device *vdev = vq->vdev;

    if (!vq->num_free)
    {
        LOG_D("%s.virtqueue[%s(%d)] add buffer.len = %d fail",
                rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, size);

        /* Recvice buffer NOW! */
        if (is_out)
        {
            vq->notify(vq);
        }

        return -RT_EFULL;
    }

    err = rt_dma_sync_out_data(&vdev->parent, dma_buf, size, &dma_addr, RT_DMA_F_LINEAR);

    if (err)
    {
        return err;
    }

    vq_packed = vq->vq_packed;
    virtq = &vq_packed->virtq;
    virtq_num = virtq->num;

    head = vq->free_head++ & (virtq_num - 1);
    rt_hw_dsb();

    desc_packed = &virtq->desc_packed[head];
    buffer_shadow = &vq_packed->buffer_shadow[head];

    buffer_shadow->dma_handle = dma_addr;
    buffer_shadow->dma_buf = dma_buf;
    buffer_shadow->size = size;

    buf_id = (head - vq->num_added) & (virtq_num - 1);
    vq_packed->buffer_shadow[buf_id].chain_num = vq->num_added + 1;

    flags = VIRTQ_DESC_F_NEXT;
    if (!is_out)
    {
        flags |= VIRTQ_DESC_F_WRITE;
    }

    desc_packed->addr = rt_cpu_to_le64(dma_addr);
    desc_packed->len = rt_cpu_to_le32(size);
    desc_packed->id = rt_cpu_to_le16(buf_id);
    desc_packed->flags = rt_cpu_to_le16(vq_packed->avail_used_flags | flags);

    /* Ready fot next */
    if (head + 1 >= virtq->num)
    {
        vq_packed->avail_used_flags ^= VIRTQ_DESC_F_AVAIL | VIRTQ_DESC_F_USED;
        /* Toggle the wrap counter */
        vq_packed->avail_wrap_counter ^= 1;
    }

    rt_hw_wmb();

    /* Update index  */
    ++vq->num_added;
    --vq->num_free;

    LOG_D("%s.virtqueue[%s(%d)] add buffer(%p, size = %d) head = %d",
            rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, dma_buf, size, head);

    return RT_EOK;
}

static rt_bool_t vq_packed_submit(struct rt_virtqueue *vq)
{
    int head, prev;
    rt_uint16_t off_wrap, flags, wrap_counter, event_idx;
    struct virtq_packed_desc_event device_event;
    struct virtqueue_packed *vq_packed = vq->vq_packed;
    struct virtq *virtq = &vq_packed->virtq;
    rt_size_t virtq_num = virtq->num;

    rt_hw_dmb();
    rt_memcpy(&device_event, virtq->device_event, sizeof(device_event));

    head = vq->free_head;
    prev = (head - 1) & (virtq_num - 1);
    head = head - vq->num_added;

    LOG_D("%s.virtqueue[%s(%d)] submit head = %d, num_added = %d, idx = %d",
            rt_dm_dev_get_name(&vq->vdev->parent), vq->name, vq->index,
            head & (virtq_num - 1), vq->num_added, rt_le16_to_cpu(device_event.off_wrap) &
                    ~RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR));

    /* Reset list info */
    vq->num_added = 0;

    /* Clear last "next" flags */
    virtq->desc_packed[prev].flags &= ~rt_cpu_to_le16(VIRTQ_DESC_F_NEXT);

    flags = rt_le16_to_cpu(device_event.flags);

    if (flags != VIRTQ_PACKED_EVENT_FLAG_DESC)
    {
        return (flags != VIRTQ_PACKED_EVENT_FLAG_DISABLE);
    }

    off_wrap = rt_le16_to_cpu(device_event.off_wrap);

    wrap_counter = off_wrap >> VIRTQ_PACKED_EVENT_WRAP_CTR;
    event_idx = off_wrap & ~RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR);
    if (wrap_counter != vq_packed->avail_wrap_counter)
    {
        event_idx -= virtq->num;
    }

    return virtq_need_event(event_idx, prev, head);
}

rt_inline rt_bool_t is_used_desc_packed(const struct virtq *virtq,
        rt_uint16_t idx, rt_bool_t used_wrap_counter)
{
    rt_uint16_t flags;
    rt_bool_t avail, used;

    flags = rt_le16_to_cpu(virtq->desc_packed[idx].flags);
    avail = !!(flags & VIRTQ_DESC_F_AVAIL);
    used = !!(flags & VIRTQ_DESC_F_USED);

    return avail == used && used == used_wrap_counter;
}

static rt_bool_t packed_used_wrap_counter(rt_uint16_t last_used_idx)
{
    return !!(last_used_idx & RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR));
}

static rt_uint16_t packed_last_used(rt_uint16_t last_used_idx)
{
    return last_used_idx & ~(-RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR));
}

static rt_bool_t vq_packed_poll(struct rt_virtqueue *vq, rt_uint32_t last_used_idx)
{
    rt_bool_t wrap_counter;
    rt_uint16_t off_wrap = last_used_idx, used_idx;

    wrap_counter = off_wrap >> VIRTQ_PACKED_EVENT_WRAP_CTR;
    used_idx = off_wrap & ~RT_BIT(VIRTQ_PACKED_EVENT_WRAP_CTR);

    return is_used_desc_packed(&vq->vq_packed->virtq, used_idx, wrap_counter);
}

rt_inline rt_bool_t vq_packed_pending(struct rt_virtqueue *vq)
{
    rt_bool_t wrap_counter;
    rt_uint16_t last_used, last_used_idx;

    last_used_idx = HWREG16(&vq->last_used_idx);
    last_used = packed_last_used(last_used_idx);
    wrap_counter = packed_used_wrap_counter(last_used_idx);
    return is_used_desc_packed(&vq->vq_packed->virtq, last_used, wrap_counter);
}

static void vq_packed_disable_callback(struct rt_virtqueue *vq)
{
    struct virtqueue_packed *vq_packed = vq->vq_packed;

    if (vq_packed->event_flags_shadow != VIRTQ_PACKED_EVENT_FLAG_DISABLE)
    {
        vq_packed->event_flags_shadow = VIRTQ_PACKED_EVENT_FLAG_DISABLE;

        /*
         * If device triggered an event already it won't trigger one again:
         * no need to disable.
         */
        if (vq->event_triggered)
        {
            return;
        }

        vq_packed->virtq.driver_event->flags = rt_cpu_to_le16(vq_packed->event_flags_shadow);
    }
}

static rt_uint32_t vq_packed_enable_callback(struct rt_virtqueue *vq)
{
    struct virtqueue_packed *vq_packed = vq->vq_packed;

    if (vq->event)
    {
        vq_packed->virtq.driver_event->off_wrap = rt_cpu_to_le16(vq->last_used_idx);

        /* Update event offset and event wrap counter first before updating event flags. */
        rt_hw_wmb();
    }

    if (vq_packed->event_flags_shadow == VIRTQ_PACKED_EVENT_FLAG_DISABLE)
    {
        vq_packed->event_flags_shadow = vq->event ?
                VIRTQ_PACKED_EVENT_FLAG_DESC : VIRTQ_PACKED_EVENT_FLAG_ENABLE;
        vq_packed->virtq.driver_event->flags =
                rt_cpu_to_le16(vq_packed->event_flags_shadow);
    }

    return vq->last_used_idx;
}

static void *vq_packed_read_buf(struct rt_virtqueue *vq, rt_size_t *out_len)
{
    void *buf;
    rt_err_t err;
    rt_bool_t wrap_counter;
    rt_uint16_t last_used, last_used_idx, id;
    rt_size_t chain_num;
    struct virtq *virtq;
    struct virtqueue_packed *vq_packed;
    struct virtq_buffer_shadow *buffer_shadow;
    struct rt_virtio_device *vdev = vq->vdev;

    if (!vq_packed_pending(vq))
    {
        LOG_D("%s.virtqueue[%s(%d)] read buffer empty",
                rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index);

        return RT_NULL;
    }

    vq_packed = vq->vq_packed;
    virtq = &vq_packed->virtq;

    rt_hw_rmb();

    last_used_idx = HWREG16(&vq->last_used_idx);
    wrap_counter = packed_used_wrap_counter(last_used_idx);
    last_used = packed_last_used(last_used_idx);
    id = rt_le16_to_cpu(virtq->desc_packed[last_used].id);
    *out_len = rt_le32_to_cpu(virtq->desc_packed[last_used].len);

    buffer_shadow = &vq->vq_packed->buffer_shadow[id];
    buf = buffer_shadow->dma_buf;
    chain_num = buffer_shadow->chain_num;

    LOG_D("%s.virtqueue[%s(%d)] read head = %d, buffer(%p, size = %d)",
            rt_dm_dev_get_name(&vdev->parent), vq->name, vq->index, id, buf, *out_len);

    for (int i = 0; i < chain_num; ++i)
    {
        if (virtq->desc_packed[id].flags & VIRTQ_DESC_F_WRITE ||
            vdev->dma_dispatch)
        {
            buffer_shadow = &vq->vq_packed->buffer_shadow[id];
            err = rt_dma_sync_in_data(&vdev->parent,
                    buffer_shadow->dma_buf,
                    buffer_shadow->size,
                    buffer_shadow->dma_handle, RT_DMA_F_LINEAR);

            if (err)
            {
                LOG_E("%s.virtqueue[%s(%d)] read head = %d sync error = %s",
                        rt_dm_dev_get_name(&vdev->parent),
                        vq->name, vq->index, id, rt_strerror(err));
            }
        }

        ++id;
    }

    vq->num_free += chain_num;
    last_used += chain_num;

    if (last_used >= virtq->num)
    {
        last_used -= virtq->num;
        wrap_counter ^= 1;
    }

    last_used |= (wrap_counter << VIRTQ_PACKED_EVENT_WRAP_CTR);
    HWREG16(&vq->last_used_idx) = last_used;

    if (vq_packed->event_flags_shadow == VIRTQ_PACKED_EVENT_FLAG_DESC)
    {
        HWREG16(&virtq->driver_event->off_wrap) = rt_cpu_to_le16(vq->last_used_idx);
        rt_hw_dmb();
    }

    return buf;
}

rt_inline rt_bool_t virtqueue_pending(struct rt_virtqueue *vq)
{
    rt_bool_t res = RT_FALSE;

    if (vq->packed_ring)
    {
        res = vq_packed_pending(vq);
    }
    else
    {
        res = vq_split_pending(vq);
    }

    return res;
}

struct rt_virtqueue *rt_virtqueue_create(struct rt_virtio_device *vdev,
        const char *name, int index, int num, rt_uint32_t align,
        rt_virtqueue_notifier notify, rt_virtqueue_callback callback,
        struct rt_virtqueue_formula *formula)
{
    struct rt_virtqueue *vq = RT_NULL;
    struct rt_virtqueue_formula default_formula = {};

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(num != 0);
    RT_ASSERT((num & (num - 1)) == 0);
    RT_ASSERT(notify != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    formula = formula ? : &default_formula;

    if (rt_virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
    {
        vq = vq_packed_create(vdev, name, index, num, align, notify, callback, formula);
    }
    else
    {
        vq = vq_split_create(vdev, name, index, num, align, notify, callback, formula);
    }

    if (vq)
    {
        if (!callback)
        {
            rt_virtqueue_disable_callback(vq);
        }

        rt_base_t level = rt_spin_lock_irqsave(&vdev->vq_lock);

        rt_list_init(&vq->list);
        rt_list_init(&vq->user_list);
        rt_list_insert_before(&vdev->vq_node, &vq->list);

        rt_spin_unlock_irqrestore(&vdev->vq_lock, level);
    }

    return vq;
}

rt_err_t rt_virtqueue_delete(struct rt_virtio_device *vdev, struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    rt_err_t err = RT_EOK;

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vq != RT_NULL);

    level = rt_spin_lock_irqsave(&vdev->vq_lock);

    while (virtqueue_pending(vq))
    {
        rt_spin_unlock_irqrestore(&vdev->vq_lock, level);

        rt_thread_yield();

        level = rt_spin_lock_irqsave(&vdev->vq_lock);
    }

    rt_list_remove(&vq->list);

    rt_spin_unlock_irqrestore(&vdev->vq_lock, level);

    if (vq->packed_ring)
    {
        vq_packed_delete(vq);
    }
    else
    {
        vq_split_delete(vq);
    }

    return err;
}

rt_err_t rt_virtqueue_add_outbuf(struct rt_virtqueue *vq, void *dma_buf, rt_size_t size)
{
    rt_err_t err = -RT_ENOSYS;

    RT_ASSERT(vq != RT_NULL);
    RT_ASSERT(dma_buf != RT_NULL);
    RT_ASSERT(size != 0);

    if (vq->packed_ring)
    {
        err = vq_packed_add_buf(vq, dma_buf, size, RT_TRUE);
    }
    else
    {
        err = vq_split_add_buf(vq, dma_buf, size, RT_TRUE);
    }

    return err;
}

rt_err_t rt_virtqueue_add_inbuf(struct rt_virtqueue *vq, void *dma_buf, rt_size_t size)
{
    rt_err_t err = -RT_ENOSYS;

    RT_ASSERT(vq != RT_NULL);
    RT_ASSERT(dma_buf != RT_NULL);
    RT_ASSERT(size != 0);

    if (vq->packed_ring)
    {
        err = vq_packed_add_buf(vq, dma_buf, size, RT_FALSE);
    }
    else
    {
        err = vq_split_add_buf(vq, dma_buf, size, RT_FALSE);
    }

    return err;
}

rt_bool_t rt_virtqueue_prepare(struct rt_virtqueue *vq, rt_uint32_t nr)
{
    return vq->num_free >= nr;
}

void rt_virtqueue_wait_prepare(struct rt_virtqueue *vq, rt_uint32_t nr)
{
    while (!rt_virtqueue_prepare(vq, nr))
    {
        rt_thread_yield();
        rt_hw_cpu_relax();
    }
}

rt_uint32_t rt_virtqueue_next_buf_index(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    return vq->free_head % (vq->packed_ring ?
            vq->vq_packed->virtq.num : vq->vq_split->virtq.num);
}

rt_bool_t rt_virtqueue_submit(struct rt_virtqueue *vq)
{
    rt_bool_t res = RT_FALSE;

    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        res = vq_packed_submit(vq);
    }
    else
    {
        res = vq_split_submit(vq);
    }

    return res;
}

rt_bool_t rt_virtqueue_notify(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (!vq->notify(vq))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

rt_bool_t rt_virtqueue_kick(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (rt_virtqueue_submit(vq))
    {
        return rt_virtqueue_notify(vq);
    }

    return RT_TRUE;
}

void rt_virtqueue_isr(int irq, struct rt_virtqueue *vq)
{
    if (!virtqueue_pending(vq))
    {
        LOG_D("%s.virtqueue[%s(%d)] no buffer pending in %s",
                rt_dm_dev_get_name(&vq->vdev->parent), vq->name, vq->index, "isr");

        return;
    }

    if (vq->event)
    {
        vq->event_triggered = RT_TRUE;
    }

    if (vq->callback)
    {
        vq->callback(vq);
    }
}

rt_bool_t rt_virtqueue_poll(struct rt_virtqueue *vq, rt_uint32_t last_used_idx)
{
    rt_bool_t res = RT_FALSE;

    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        res = vq_packed_poll(vq, last_used_idx);
    }
    else
    {
        res = vq_split_poll(vq, last_used_idx);
    }

    return res;
}

void rt_virtqueue_disable_callback(struct rt_virtqueue *vq)
{
    if (vq->event_triggered)
    {
        return;
    }

    if (vq->packed_ring)
    {
        vq_packed_disable_callback(vq);
    }
    else
    {
        vq_split_disable_callback(vq);
    }
}

rt_bool_t rt_virtqueue_enable_callback(struct rt_virtqueue *vq,
        rt_uint32_t *out_last_used_idx)
{
    rt_uint32_t last_used_idx;

    if (vq->event_triggered)
    {
        vq->event_triggered = RT_FALSE;
    }

    if (vq->packed_ring)
    {
        last_used_idx = vq_packed_enable_callback(vq);
    }
    else
    {
        last_used_idx = vq_split_enable_callback(vq);
    }

    if (out_last_used_idx)
    {
        *out_last_used_idx = last_used_idx;
    }

    return !rt_virtqueue_poll(vq, last_used_idx);
}

void *rt_virtqueue_read_buf(struct rt_virtqueue *vq, rt_size_t *out_len)
{
    void *buf = RT_NULL;
    rt_size_t len = 0;

    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        buf = vq_packed_read_buf(vq, &len);
    }
    else
    {
        buf = vq_split_read_buf(vq, &len);
    }

    if (len && out_len)
    {
        *out_len = len;
    }

    return buf;
}

rt_size_t rt_virtqueue_get_virtq_size(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        return (rt_ubase_t)vq->vq_packed->virtq.num;
    }
    else
    {
        return (rt_ubase_t)vq->vq_split->virtq.num;
    }
}

rt_ubase_t rt_virtqueue_get_desc_addr(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        return (rt_ubase_t)vq->vq_packed->virtq.desc;
    }
    else
    {
        return (rt_ubase_t)vq->vq_split->virtq.desc;
    }
}

rt_ubase_t rt_virtqueue_get_avail_addr(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        return (rt_ubase_t)vq->vq_packed->virtq.driver_event;
    }
    else
    {
        return (rt_ubase_t)vq->vq_split->virtq.avail;
    }
}

rt_ubase_t rt_virtqueue_get_used_addr(struct rt_virtqueue *vq)
{
    RT_ASSERT(vq != RT_NULL);

    if (vq->packed_ring)
    {
        return (rt_ubase_t)vq->vq_packed->virtq.device_event;
    }
    else
    {
        return (rt_ubase_t)vq->vq_split->virtq.used;
    }
}
