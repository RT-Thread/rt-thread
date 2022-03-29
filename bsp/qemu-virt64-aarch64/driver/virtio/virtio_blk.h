/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     using virtio common interface
 */

#ifndef __VIRTIO_BLK_H__
#define __VIRTIO_BLK_H__

#include <rtdef.h>

#include <virtio.h>

#define VIRTIO_BLK_BUF_DATA_SIZE    512
#define VIRTIO_BLK_BYTES_PER_SECTOR 512
#define VIRTIO_BLK_BLOCK_SIZE       512
#define VIRTIO_BLK_QUEUE_RING_SIZE  4

#define VIRTIO_BLK_F_RO             5   /* Disk is read-only */
#define VIRTIO_BLK_F_SCSI           7   /* Supports scsi command passthru */
#define VIRTIO_BLK_F_CONFIG_WCE     11  /* Writeback mode available in config */
#define VIRTIO_BLK_F_MQ             12  /* Support more than one vq */

#define VIRTIO_BLK_T_IN             0   /* Read the blk */
#define VIRTIO_BLK_T_OUT            1   /* Write the blk */
#define VIRTIO_BLK_T_SCSI_CMD       2
#define VIRTIO_BLK_T_SCSI_CMD_OUT   3
#define VIRTIO_BLK_T_FLUSH          4
#define VIRTIO_BLK_T_FLUSH_OUT      5

struct virtio_blk_req
{
    rt_uint32_t type;
    rt_uint32_t ioprio;
    rt_uint64_t sector;
};

struct virtio_blk_device
{
    struct rt_device parent;

    struct virtio_device virtio_dev;

    struct
    {
        rt_bool_t valid;
        rt_uint8_t status;

        struct virtio_blk_req req;

    } info[VIRTIO_BLK_QUEUE_RING_SIZE];
};

rt_err_t rt_virtio_blk_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

#endif /* __VIRTIO_BLK_H__ */
