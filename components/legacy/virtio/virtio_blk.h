/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

#define VIRTIO_BLK_QUEUE            0
#define VIRTIO_BLK_BYTES_PER_SECTOR 512
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

struct virtio_blk_config
{
    rt_uint64_t capacity;           /* The capacity (in 512-byte sectors). */
    rt_uint32_t size_max;           /* The maximum segment size (if VIRTIO_BLK_F_SIZE_MAX) */
    rt_uint32_t seg_max;            /* The maximum number of segments (if VIRTIO_BLK_F_SEG_MAX) */

    /* Geometry of the device (if VIRTIO_BLK_F_GEOMETRY) */
    struct virtio_blk_geometry
    {
        rt_uint16_t cylinders;
        rt_uint8_t heads;
        rt_uint8_t sectors;
    } geometry;

    rt_uint32_t blk_size;           /* Block size of device (if VIRTIO_BLK_F_BLK_SIZE) */

    struct virtio_blk_topology
    {
        /* # Of logical blocks per physical block (log2) */
        rt_uint8_t physical_block_exp;
        /* Offset of first aligned logical block */
        rt_uint8_t alignment_offset;
        /* Suggested minimum I/O size in blocks */
        rt_uint16_t min_io_size;
        /* Optimal (suggested maximum) I/O size in blocks */
        rt_uint32_t opt_io_size;
    } topology;

    rt_uint8_t writeback;
    rt_uint8_t unused0;
    rt_uint16_t num_queues;
    rt_uint32_t max_discard_sectors;
    rt_uint32_t max_discard_seg;
    rt_uint32_t discard_sector_alignment;
    rt_uint32_t max_write_zeroes_sectors;
    rt_uint32_t max_write_zeroes_seg;
    rt_uint8_t write_zeroes_may_unmap;
    rt_uint8_t unused1[3];
    rt_uint32_t max_secure_erase_sectors;
    rt_uint32_t max_secure_erase_seg;
    rt_uint32_t secure_erase_sector_alignment;
} __attribute__((packed));

struct virtio_blk_device
{
    struct rt_device parent;

    struct virtio_device virtio_dev;

    struct virtio_blk_config *config;

    struct
    {
        rt_bool_t valid;
        rt_uint8_t status;

        struct virtio_blk_req req;

    } info[VIRTIO_BLK_QUEUE_RING_SIZE];
};

rt_err_t rt_virtio_blk_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

#endif /* __VIRTIO_BLK_H__ */
