/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     first version
 */

#ifndef __BLK_PARTITION_H__
#define __BLK_PARTITION_H__

#include "blk_dev.h"

rt_err_t blk_put_partition(struct rt_blk_disk *disk, const char *type,
        rt_size_t start, rt_size_t count, int partno);

rt_err_t dfs_partition(struct rt_blk_disk *disk);
rt_err_t efi_partition(struct rt_blk_disk *disk);

#endif /* __BLK_PARTITION_H__ */
