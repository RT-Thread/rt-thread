/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __PROC_FS_H__
#define __PROC_FS_H__

#include <dfs_file.h>

int dfs_procfs_init(void);

int proc_read_data(struct dfs_file *file, void *buf, size_t count, off_t *pos);

#endif
