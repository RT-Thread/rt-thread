/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-11     zmshahaha    move from <rtdef.h>
 */

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <rtdef.h>

/* block device commands*/
#define RT_DEVICE_CTRL_BLK_GETGEOME     (RT_DEVICE_CTRL_BASE(Block) + 1)            /**< get geometry information   */
#define RT_DEVICE_CTRL_BLK_SYNC         (RT_DEVICE_CTRL_BASE(Block) + 2)            /**< flush data to block device */
#define RT_DEVICE_CTRL_BLK_ERASE        (RT_DEVICE_CTRL_BASE(Block) + 3)            /**< erase block on block device */
#define RT_DEVICE_CTRL_BLK_AUTOREFRESH  (RT_DEVICE_CTRL_BASE(Block) + 4)            /**< block device : enter/exit auto refresh mode */
#define RT_DEVICE_CTRL_BLK_PARTITION    (RT_DEVICE_CTRL_BASE(Block) + 5)            /**< get block device partition */

/**
 * block device geometry structure
 */
struct rt_device_blk_geometry
{
    rt_uint64_t sector_count;                           /**< count of sectors */
    rt_uint32_t bytes_per_sector;                       /**< number of bytes per sector */
    rt_uint32_t block_size;                             /**< number of bytes to erase one block */
};

/**
 * sector arrange struct on block device
 */
struct rt_device_blk_sectors
{
    rt_uint64_t sector_begin;                           /**< begin sector */
    rt_uint64_t sector_end;                             /**< end sector   */
};

#endif /* __BLOCK_H__ */
