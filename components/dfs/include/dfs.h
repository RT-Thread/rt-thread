/*
 * File      : dfs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 */

#ifndef __DFS_H__
#define __DFS_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

char *dfs_normalize_path(const char *directory, const char *filename);
const char *dfs_subdir(const char *directory, const char *filename);

/* FD APIs */
int fd_new(void);
struct dfs_fd *fd_get(int fd);
void fd_put(struct dfs_fd *fd);
int fd_is_open(const char *pathname);

#ifdef __cplusplus
}
#endif

#endif
