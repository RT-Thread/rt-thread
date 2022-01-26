/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 */

#ifndef DRV_VIRTIO_BLK_H__
#define DRV_VIRTIO_BLK_H__

#include <rthw.h>
#include <stdint.h>
#include "virtio.h"

#define VIRTIO_BLK_BUF_DATA_SIZE        512
#define VIRTIO_BLK_BYTES_PER_SECTOR     512
#define VIRTIO_BLK_BLOCK_SIZE           512
#define VIRTIO_BLK_SECTOR_COUNT         0x40000 /* 128MB */

#define VIRTIO_BLK_F_RO                 5   /* Disk is read-only */
#define VIRTIO_BLK_F_SCSI               7   /* Supports scsi command passthru */
#define VIRTIO_BLK_F_CONFIG_WCE         11  /* Writeback mode available in config */
#define VIRTIO_BLK_F_MQ                 12  /* Support more than one vq */

#define VIRTIO_BLK_T_IN                 0   /* Read the blk */
#define VIRTIO_BLK_T_OUT                1   /* Write the blk */

#define VIRTIO_F_ANY_LAYOUT             27
#define VIRTIO_RING_F_INDIRECT_DESC     28
#define VIRTIO_RING_F_EVENT_IDX         29

struct virtio_blk_buf
{
    int valid;
    uint32_t block_no;
    uint8_t *data;
};

struct virtio_blk_req
{
    uint32_t type;
    uint32_t reserved;
    uint64_t sector;
};

/*
 * virtio_blk must be a static variable because
 * pages must consist of two contiguous pages of
 * page-aligned physical memory
 */
struct virtio_blk
{
    char pages[2 * PAGE_SIZE];
    struct virtq_desc *desc;
    struct virtq_avail *avail;
    struct virtq_used *used;

    char free[QUEUE_SIZE];
    uint16_t used_idx;
    struct
    {
        struct virtio_blk_buf *buf;
        char status;
    } info[QUEUE_SIZE];

    struct virtio_blk_req ops[QUEUE_SIZE];
} __attribute__ ((aligned (PAGE_SIZE)));

struct virtio_blk_device
{
    struct rt_device parent;
    struct virtio_blk *blk;

    uint32_t *mmio_base;
#ifdef RT_USING_SMP
    struct rt_spinlock spinlock;
#endif
};

int rt_hw_virtio_blk_init(void);

#endif /* DRV_VIRTIO_BLK_H__ */
