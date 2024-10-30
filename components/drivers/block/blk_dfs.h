/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-08     GuEe-GUI     first version
 */

#ifndef __BLK_DFS_H__
#define __BLK_DFS_H__

#include <rtdef.h>

#define RT_DEVICE_CTRL_BLK_SSIZEGET      0x00001268     /**< get number of bytes per sector */
#define RT_DEVICE_CTRL_ALL_BLK_SSIZEGET  0x80081272     /**< get number of bytes per sector * sector counts */

void device_set_blk_fops(struct rt_device *dev);
void device_get_blk_ssize(struct rt_device *dev, void *args);
void device_get_all_blk_ssize(struct rt_device *dev, void *args);

#endif /* __BLK_DFS_H__ */
