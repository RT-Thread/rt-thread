/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 */

#ifndef VIRTIO_H__
#define VIRTIO_H__

#include <stdint.h>

#define PAGE_SIZE   4096
#define PAGE_SHIFT  12

#define VIRTIO_STAT_ACKNOWLEDGE     1
#define VIRTIO_STAT_DRIVER          2
#define VIRTIO_STAT_DRIVER_OK       4
#define VIRTIO_STAT_FEATURES_OK     8
#define VIRTIO_STAT_NEEDS_RESET     64
#define VIRTIO_STAT_FAILED          128

#define QUEUE_SIZE  8

struct virtq_desc
{
    uint64_t addr;
    uint32_t len;
    uint16_t flags;
    uint16_t next;
};

#define VRING_DESC_F_NEXT  1    // chained with another descriptor
#define VRING_DESC_F_WRITE 2    // device writes (vs read)

struct virtq_avail
{
    uint16_t flags;             // always zero
    uint16_t idx;               // driver will write ring[idx] next
    uint16_t ring[QUEUE_SIZE];  // descriptor numbers of chain heads
    uint16_t unused;
};

struct virtq_used_elem
{
    uint32_t id;   // index of start of completed descriptor chain
    uint32_t len;
};

struct virtq_used
{
    uint16_t flags;                         // always zero
    uint16_t idx;                           // device increments when it adds a ring[] entry
    struct virtq_used_elem ring[QUEUE_SIZE];
};

#endif /* VIRTIO_H__ */
