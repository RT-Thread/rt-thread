/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2016-05-05     Bernard      rename dfs_lwip to dfs_net.
 */

#ifndef DFS_NET_H__
#define DFS_NET_H__

#include <dfs_file.h>

#ifdef __cplusplus
extern "C" {
#endif

const struct dfs_file_ops* dfs_net_get_fops(void);
int dfs_net_getsocket(int fd);

#ifdef __cplusplus
}
#endif

#endif

