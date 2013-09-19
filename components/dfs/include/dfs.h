/*
 * File      : dfs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
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
 * 2005-02-22     Bernard      The first version.
 */

#ifndef __DFS_H__
#define __DFS_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NO_WORKING_DIR  "system does not support working directory\n"

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
