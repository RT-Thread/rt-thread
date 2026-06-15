/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     using virtio common interface
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#ifndef __VIRTIO_BLK_H__
#define __VIRTIO_BLK_H__

#include <drivers/core/dm.h>

#define VIRTIO_BLK_F_SIZE_MAX       1   /* Indicates maximum segment size */
#define VIRTIO_BLK_F_SEG_MAX        2   /* Indicates maximum # of segments */
#define VIRTIO_BLK_F_GEOMETRY       4   /* Legacy geometry available  */
#define VIRTIO_BLK_F_RO             5   /* Disk is read-only */
#define VIRTIO_BLK_F_BLK_SIZE       6   /* Block size of disk is available*/
#define VIRTIO_BLK_F_SCSI           7   /* Supports scsi command passthru */
#define VIRTIO_BLK_F_FLUSH          9   /* Flush command supported */
#define VIRTIO_BLK_F_TOPOLOGY       10  /* Topology information is available */
#define VIRTIO_BLK_F_CONFIG_WCE     11  /* Writeback mode available in config */
#define VIRTIO_BLK_F_MQ             12  /* Support more than one vq */
#define VIRTIO_BLK_F_DISCARD        13  /* DISCARD is supported */
#define VIRTIO_BLK_F_WRITE_ZEROES   14  /* WRITE ZEROES is supported */
#define VIRTIO_BLK_F_SECURE_ERASE   16  /* Secure Erase is supported */

#define VIRTIO_BLK_T_IN             0   /* Read the blk */
#define VIRTIO_BLK_T_OUT            1   /* Write the blk */
#define VIRTIO_BLK_T_SCSI_CMD       2
#define VIRTIO_BLK_T_SCSI_CMD_OUT   3
#define VIRTIO_BLK_T_FLUSH          4
#define VIRTIO_BLK_T_FLUSH_OUT      5
#define VIRTIO_BLK_T_GET_ID         8   /* Get device ID command */
#define VIRTIO_BLK_T_DISCARD        11  /* Discard command */
#define VIRTIO_BLK_T_WRITE_ZEROES   13  /* Write zeroes command */
#define VIRTIO_BLK_T_SECURE_ERASE   14  /* Secure erase command */
#define VIRTIO_BLK_T_ZONE_APPEND    15  /* Zone append command */
#define VIRTIO_BLK_T_ZONE_REPORT    16  /* Report zones command */
#define VIRTIO_BLK_T_ZONE_OPEN      18  /* Open zone command */
#define VIRTIO_BLK_T_ZONE_CLOSE     20  /* Close zone command */
#define VIRTIO_BLK_T_ZONE_FINISH    22  /* Finish zone command */
#define VIRTIO_BLK_T_ZONE_RESET     24  /* Reset zone command */
#define VIRTIO_BLK_T_ZONE_RESET_ALL 26  /* Reset All zones command */

struct virtio_blk_req
{
    rt_le32_t type;
    rt_le32_t ioprio;
    rt_le64_t sector;

#define VIRTIO_BLK_S_OK                     0
#define VIRTIO_BLK_S_IOERR                  1
#define VIRTIO_BLK_S_UNSUPP                 2
#define VIRTIO_BLK_S_ZONE_INVALID_CMD       3
#define VIRTIO_BLK_S_ZONE_UNALIGNED_WP      4
#define VIRTIO_BLK_S_ZONE_OPEN_RESOURCE     5
#define VIRTIO_BLK_S_ZONE_ACTIVE_RESOURCE   6
    /*
     * next:
     * rt_uint8_t data[];
     * rt_uint8_t status;
     */
};

struct virtio_blk_discard_write_zeroes
{
    rt_le64_t sector;
    rt_le32_t num_sectors;

    /*
     * unmap:1
     * reserved:31
     */
    rt_le32_t flags;
};

rt_packed(struct virtio_blk_config
{
    /* The capacity (in 512-byte sectors). */
    rt_le64_t capacity;
    /* The maximum segment size (if VIRTIO_BLK_F_SIZE_MAX) */
    rt_le32_t size_max;
    /* The maximum number of segments (if VIRTIO_BLK_F_SEG_MAX) */
    rt_le32_t seg_max;

    /* Geometry of the device (if VIRTIO_BLK_F_GEOMETRY) */
    struct virtio_blk_geometry
    {
        rt_le16_t cylinders;
        rt_uint8_t heads;
        rt_uint8_t sectors;
    } geometry;

    /* Block size of device (if VIRTIO_BLK_F_BLK_SIZE) */
    rt_le32_t blk_size;

    struct virtio_blk_topology
    {
        /* # Of logical blocks per physical block (log2) */
        rt_uint8_t physical_block_exp;
        /* Offset of first aligned logical block */
        rt_uint8_t alignment_offset;
        /* Suggested minimum I/O size in blocks */
        rt_le16_t min_io_size;
        /* Optimal (suggested maximum) I/O size in blocks */
        rt_le32_t opt_io_size;
    } topology;

    rt_uint8_t writeback;
    rt_uint8_t unused0;
    rt_uint16_t num_queues;
    rt_le32_t max_discard_sectors;
    rt_le32_t max_discard_seg;
    rt_le32_t discard_sector_alignment;
    rt_le32_t max_write_zeroes_sectors;
    rt_le32_t max_write_zeroes_seg;
    rt_uint8_t write_zeroes_may_unmap;
    rt_uint8_t unused1[3];
    rt_le32_t max_secure_erase_sectors;
    rt_le32_t max_secure_erase_seg;
    rt_le32_t secure_erase_sector_alignment;
});

#endif /* __VIRTIO_BLK_H__ */
