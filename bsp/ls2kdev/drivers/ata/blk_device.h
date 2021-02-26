/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     first version
 */

#ifndef __BLK_DEVICE_H__
#define __BLK_DEVICE_H__

#include <rtconfig.h>
#include <ext4_mbr.h>

#define DEV_TYPE_UNKNOWN 0xff  /* not connected */
#define DEV_TYPE_HARDDISK 0x00 /* harddisk */
#define DEV_TYPE_TAPE 0x01     /* Tape */
#define DEV_TYPE_CDROM 0x05    /* CD-ROM */
#define DEV_TYPE_OPDISK 0x07   /* optical disk */

struct blk_device
{
    struct rt_device parent;
    struct ahci_uc_priv *ahci_device;

    rt_uint8_t target;
    rt_uint8_t lun;
    rt_uint8_t type;

#ifdef RT_USING_DFS_LWEXT4
    struct ext4_mbr_bdevs ext4_partition;
#endif

    rt_bool_t lba48;
    rt_uint64_t lba;
    rt_uint64_t blksz;
    rt_int32_t log2blksz;

    char product[21];
    char revision[9];
    char vendor[41];
};

void blk_device_init(struct blk_device *blk_devices);

#endif
