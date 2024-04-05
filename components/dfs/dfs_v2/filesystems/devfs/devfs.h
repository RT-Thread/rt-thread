/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DEVICE_FS_H__
#define __DEVICE_FS_H__

const struct dfs_file_ops *dfs_devfs_fops(void);
mode_t dfs_devfs_device_to_mode(struct rt_device *device);
void dfs_devfs_device_add(rt_device_t device);
int dfs_devfs_update(void);

#endif
