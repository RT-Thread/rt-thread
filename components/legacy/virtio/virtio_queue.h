/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_QUEUE_H__
#define __VIRTIO_QUEUE_H__

#include <rtdef.h>

#define VIRTQ_DESC_F_NEXT           1 /* This marks a buffer as continuing via the next field. */
#define VIRTQ_DESC_F_WRITE          2 /* This marks a buffer as write-only (otherwise read-only). */
#define VIRTQ_DESC_F_INDIRECT       4 /* This means the buffer contains a list of buffer descriptors. */

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

struct virtq
{
    rt_uint32_t num;

    struct virtq_desc *desc;
    struct virtq_avail *avail;
    struct virtq_used *used;

    /* Helper of driver */
    rt_uint16_t used_idx;
    rt_bool_t *free;
    rt_size_t free_count;
};

#define VIRTQ_DESC_TOTAL_SIZE(ring_size)    (sizeof(struct virtq_desc) * (ring_size))
/* flags, idx, used_event + ring * ring_size */
#define VIRTQ_AVAIL_TOTAL_SIZE(ring_size)   (sizeof(rt_uint16_t) * 3 + sizeof(rt_uint16_t) * (ring_size))
/* flags, idx, avail_event + ring * ring_size */
#define VIRTQ_USED_TOTAL_SIZE(ring_size)    (sizeof(rt_uint16_t) * 3 + sizeof(struct virtq_used_elem) * (ring_size))

#define VIRTQ_AVAIL_RES_SIZE    (sizeof(rt_uint16_t))   /* used_event */
#define VIRTQ_USED_RES_SIZE     (sizeof(rt_uint16_t))   /* avail_event */

#define VIRTQ_INVALID_DESC_ID   RT_UINT16_MAX

#endif /* __VIRTIO_QUEUE_H__ */
