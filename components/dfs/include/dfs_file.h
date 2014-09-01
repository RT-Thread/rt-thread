/*
 * File      : dfs_file.h
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
 * 2005-01-26     Bernard      The first version.
 */

#ifndef __DFS_FILE_H__
#define __DFS_FILE_H__

#include <dfs_def.h>
#include <dfs.h>
#include <dfs_fs.h>

int dfs_file_open(struct dfs_fd *fd, const char *path, int flags);
int dfs_file_close(struct dfs_fd *fd);
int dfs_file_ioctl(struct dfs_fd *fd, int cmd, void *args);
int dfs_file_read(struct dfs_fd *fd, void *buf, rt_size_t len);
int dfs_file_getdents(struct dfs_fd *fd, struct dirent *dirp, rt_size_t nbytes);
int dfs_file_unlink(const char *path);
int dfs_file_write(struct dfs_fd *fd, const void *buf, rt_size_t len);
int dfs_file_flush(struct dfs_fd *fd);
int dfs_file_lseek(struct dfs_fd *fd, rt_off_t offset);
int dfs_file_stat(const char *path, struct stat *buf);
int dfs_file_rename(const char *oldpath, const char *newpath);

#endif

