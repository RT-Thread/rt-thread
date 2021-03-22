/*
 * File      : fal.h
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_H_
#define _FAL_H_

#include <rtconfig.h>
#include <fal_cfg.h>
#include "fal_def.h"

/**
 * FAL (Flash Abstraction Layer) initialization.
 * It will initialize all flash device and all flash partition.
 *
 * @return >= 0: partitions total number
 */
int fal_init(void);

/* =============== flash device operator API =============== */
/**
 * find flash device by name
 *
 * @param name flash device name
 *
 * @return != NULL: flash device
 *            NULL: not found
 */
const struct fal_flash_dev *fal_flash_device_find(const char *name);

/* =============== partition operator API =============== */
/**
 * find the partition by name
 *
 * @param name partition name
 *
 * @return != NULL: partition
 *            NULL: not found
 */
const struct fal_partition *fal_partition_find(const char *name);

/**
 * get the partition table
 *
 * @param len return the partition table length
 *
 * @return partition table
 */
const struct fal_partition *fal_get_partition_table(size_t *len);

/**
 * set partition table temporarily
 * This setting will modify the partition table temporarily, the setting will be lost after restart.
 *
 * @param table partition table
 * @param len partition table length
 */
void fal_set_partition_table_temp(struct fal_partition *table, size_t len);

/**
 * read data from partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf read buffer
 * @param size read size
 *
 * @return >= 0: successful read data size
 *           -1: error
 */
int fal_partition_read(const struct fal_partition *part, uint32_t addr, uint8_t *buf, size_t size);

/**
 * write data to partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf write buffer
 * @param size write size
 *
 * @return >= 0: successful write data size
 *           -1: error
 */
int fal_partition_write(const struct fal_partition *part, uint32_t addr, const uint8_t *buf, size_t size);

/**
 * erase partition data
 *
 * @param part partition
 * @param addr relative address for partition
 * @param size erase size
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
int fal_partition_erase(const struct fal_partition *part, uint32_t addr, size_t size);

/**
 * erase partition all data
 *
 * @param part partition
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
int fal_partition_erase_all(const struct fal_partition *part);

/**
 * print the partition table
 */
void fal_show_part_table(void);

/* =============== API provided to RT-Thread =============== */
/**
 * create RT-Thread block device by specified partition
 *
 * @param parition_name partition name
 *
 * @return != NULL: created block device
 *            NULL: created failed
 */
struct rt_device *fal_blk_device_create(const char *parition_name);

#if defined(RT_USING_MTD_NOR)
/**
 * create RT-Thread MTD NOR device by specified partition
 *
 * @param parition_name partition name
 *
 * @return != NULL: created MTD NOR device
 *            NULL: created failed
 */
struct rt_device *fal_mtd_nor_device_create(const char *parition_name);
#endif /* defined(RT_USING_MTD_NOR) */

/**
 * create RT-Thread char device by specified partition
 *
 * @param parition_name partition name
 *
 * @return != NULL: created char device
 *            NULL: created failed
 */
struct rt_device *fal_char_device_create(const char *parition_name);

#endif /* _FAL_H_ */
