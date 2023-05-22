/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef DFS_PRIVATE_H__
#define DFS_PRIVATE_H__

#include <dfs.h>

#define DBG_TAG    "DFS"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define NO_WORKING_DIR  "system does not support working directory\n"

/* extern variable */
extern const struct dfs_filesystem_ops *filesystem_operation_table[];
extern struct dfs_filesystem filesystem_table[];
extern const struct dfs_mount_tbl mount_table[];

extern char working_directory[];

#endif
