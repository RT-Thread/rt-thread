/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     support packed
 */

#ifndef __VIRTQ_H__
#define __VIRTQ_H__

#include <drivers/misc.h>
#include <drivers/byteorder.h>

#define VIRTQ_DESC_F_NEXT           RT_BIT(0) /* This marks a buffer as continuing via the next field. */
#define VIRTQ_DESC_F_WRITE          RT_BIT(1) /* This marks a buffer as write-only (otherwise read-only). */
#define VIRTQ_DESC_F_INDIRECT       RT_BIT(3) /* This means the buffer contains a list of buffer descriptors. */
#define VIRTQ_DESC_F_AVAIL          RT_BIT(7)
#define VIRTQ_DESC_F_USED           RT_BIT(15)

/*
 * The device uses this in used->flags to advise the driver: don't kick me
 * when you add a buffer.  It's unreliable, so it's simply an optimization.
 */
#define VIRTQ_USED_F_NO_NOTIFY      1

/*
 * The driver uses this in avail->flags to advise the device: don't
 * interrupt me when you consume a buffer.  It's unreliable, so it's
 * simply an optimization.
 */
#define VIRTQ_AVAIL_F_NO_INTERRUPT  1

/* Virtqueue descriptors: 16 bytes. These can chain together via "next". */
struct virtq_desc
{
    rt_uint64_t addr;   /* Address (guest-physical). */
    rt_uint32_t len;    /* Length. */
    rt_uint16_t flags;  /* The flags as indicated above. */
    rt_uint16_t next;   /* We chain unused descriptors via this, too */
};

struct virtq_avail
{
    rt_uint16_t flags;  /* Notifications */
    rt_uint16_t idx;    /* Where the driver would put the next descriptor entry in the ring (modulo the queue size) */
    rt_uint16_t ring[];

    /*
     * Only if VIRTIO_F_RING_EVENT_IDX
     * rt_uint16_t used_event;
     */
};

struct virtq_used_elem
{
    rt_uint32_t id;     /* Index of start of used descriptor chain. */
    rt_uint32_t len;    /* Total length of the descriptor chain which was written to. */
};

struct virtq_used
{
    rt_uint16_t flags;
    rt_uint16_t idx;
    struct virtq_used_elem ring[];

    /*
     * Only if VIRTIO_F_RING_EVENT_IDX
     * rt_uint16_t avail_event;
     */
};

/* Enable events in packed ring. */
#define VIRTQ_PACKED_EVENT_FLAG_ENABLE  0x0
/* Disable events in packed ring. */
#define VIRTQ_PACKED_EVENT_FLAG_DISABLE 0x1
/*
 * Enable events for a specific descriptor in packed ring.
 * (as specified by Descriptor Ring Change Event Offset/Wrap Counter).
 * Only valid if VIRTIO_F_RING_EVENT_IDX has been negotiated.
 */
#define VIRTQ_PACKED_EVENT_FLAG_DESC    0x2

/* Offset bit shift in event suppression structure of packed ring. */
#define VIRTQ_PACKED_EVENT_OFF          0
/* Wrap counter bit shift in event suppression structure of packed ring. */
#define VIRTQ_PACKED_EVENT_WRAP_CTR     15

struct virtq_packed_desc
{
    rt_le64_t addr;     /* Buffer Address. */
    rt_le32_t len;      /* Buffer Length. */
    rt_le16_t id;       /* Buffer ID (always at the last desc). */
    rt_le16_t flags;    /* The flags depending on descriptor type. */
    /*
     * For avail desc:
     *  When wrap counter is 1 =>  VIRTQ_DESC_F_AVAIL | ~VIRTQ_DESC_F_USED
     *  When wrap counter is 0 => ~VIRTQ_DESC_F_AVAIL |  VIRTQ_DESC_F_USED
     *
     * For used desc:
     *  When wrap counter is 1 =>  VIRTQ_DESC_F_AVAIL |  VIRTQ_DESC_F_USED
     *  When wrap counter is 0 => ~VIRTQ_DESC_F_AVAIL | ~VIRTQ_DESC_F_USED
     */
};

struct virtq_packed_desc_event
{
    rt_le16_t off_wrap; /* Descriptor ring change event offset/wrap counter. */
    rt_le16_t flags;    /* Descriptor ring change event flags. */
};

struct virtq
{
    rt_uint32_t num;
    rt_uint32_t align;

    union
    {
        struct virtq_desc *desc;
        struct virtq_packed_desc *desc_packed;
    };
    union
    {
        struct virtq_avail *avail;
        struct virtq_packed_desc_event *driver_event;
    };
    union
    {
        struct virtq_used *used;
        struct virtq_packed_desc_event *device_event;
    };
};

rt_inline void virtq_init(struct virtq *virtq, rt_uint32_t num,
        void *pages, rt_ubase_t align)
{
    /* Only split */
    virtq->num = num;
    virtq->align = align;

    virtq->desc = (struct virtq_desc *)pages;
    virtq->avail = (struct virtq_avail *)&virtq->desc[num];
    /* Keep sizeof(used_event) */
    virtq->used = (struct virtq_used *)RT_ALIGN((rt_ubase_t)&virtq->avail->ring[num] + sizeof(rt_uint16_t), align);
}

rt_inline rt_size_t virtq_size(struct virtq *virtq, rt_uint32_t try_num, rt_uint32_t try_align)
{
    /* Only split */
    rt_uint32_t align;
    rt_size_t size, num;

    if (virtq)
    {
        num = virtq->num;
        align = virtq->align;
    }
    else
    {
        num = try_num;
        align = try_align;
    }

    size = sizeof(struct virtq_desc) * num;
    size += sizeof(struct virtq_avail) + sizeof(rt_uint16_t) * num;
    /* Keep sizeof(used_event) */
    size += sizeof(rt_uint16_t);
    size = RT_ALIGN(size, align);
    size += sizeof(struct virtq_used) + sizeof(struct virtq_used_elem) * num;
    /* Keep sizeof(avail_event) */
    size += sizeof(rt_uint16_t);

    return size;
}

rt_inline rt_bool_t virtq_need_event(rt_uint16_t event_idx,
        rt_uint16_t new_idx, rt_uint16_t old_idx)
{
    return (rt_uint16_t)(new_idx - event_idx - 1) < (rt_uint16_t)(new_idx - old_idx);
}

/* Get location of event indices (only with VIRTIO_F_EVENT_IDX) */
rt_inline rt_uint16_t *virtq_used_event(struct virtq *virtq)
{
    /* For backwards compat, used event index is at *end* of avail ring. */
    return &virtq->avail->ring[virtq->num];
}

rt_inline rt_uint16_t *virtq_avail_event(struct virtq *virtq)
{
    /* For backwards compat, avail event index is at *end* of used ring. */
    return (rt_uint16_t *)&virtq->used->ring[virtq->num];
}

#endif /* __VIRTQ_H__ */
