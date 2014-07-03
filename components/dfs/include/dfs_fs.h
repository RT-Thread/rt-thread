/*
 * File      : dfs_fs.h
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
 
#ifndef __DFS_FS_H__
#define __DFS_FS_H__

#include <dfs_def.h>

#define DFS_FS_FLAG_DEFAULT     0x00    /* default flag */
#define DFS_FS_FLAG_FULLPATH    0x01    /* set full path to underlaying file system */

/* Pre-declaration */
struct dfs_filesystem;
struct dfs_fd;

/* File system operations struct */
struct dfs_filesystem_operation
{
    char *name;
    rt_uint32_t flags;      /* flags for file system operations */

    /* mount and unmount file system */
    int (*mount)    (struct dfs_filesystem *fs, unsigned long rwflag, const void *data);
    int (*unmount)  (struct dfs_filesystem *fs);

    /* make a file system */
    int (*mkfs)     (rt_device_t devid);
    int (*statfs)   (struct dfs_filesystem *fs, struct statfs *buf);

    int (*open)     (struct dfs_fd *fd);
    int (*close)    (struct dfs_fd *fd);
    int (*ioctl)    (struct dfs_fd *fd, int cmd, void *args);
    int (*read)     (struct dfs_fd *fd, void *buf, rt_size_t count);
    int (*write)    (struct dfs_fd *fd, const void *buf, rt_size_t count);
    int (*flush)    (struct dfs_fd *fd);
    int (*lseek)    (struct dfs_fd *fd, rt_off_t offset);
    int (*getdents) (struct dfs_fd *fd, struct dirent *dirp, rt_uint32_t count);

    int (*unlink)   (struct dfs_filesystem *fs, const char *pathname);
    int (*stat)     (struct dfs_filesystem *fs, const char *filename, struct stat *buf);
    int (*rename)   (struct dfs_filesystem *fs, const char *oldpath, const char *newpath);
};

/* Mounted file system */
struct dfs_filesystem
{
    rt_device_t dev_id;     /* Attached device */

    char *path;             /* File system mount point */
    const struct dfs_filesystem_operation *ops; /* Operations for file system type */

    void *data;             /* Specific file system data */
};

/* file system partition table */
struct dfs_partition
{
    rt_uint8_t type;        /* file system type */
    rt_off_t  offset;       /* partition start offset */
    rt_size_t size;         /* partition size */
    rt_sem_t lock;  
};

/* mount table */
struct dfs_mount_tbl
{
	const char	 *device_name;
	const char   *path;
	const char   *filesystemtype;
	unsigned long rwflag;
	const void   *data;
};

int dfs_register(const struct dfs_filesystem_operation *ops);
struct dfs_filesystem *dfs_filesystem_lookup(const char *path);
const char* dfs_filesystem_get_mounted_path(struct rt_device* device);

rt_err_t dfs_filesystem_get_partition(struct dfs_partition *part,
                                      rt_uint8_t           *buf,
                                      rt_uint32_t           pindex);

int dfs_mount(const char *device_name,
              const char *path,
              const char *filesystemtype,
              rt_uint32_t rwflag,
              const void *data);
int dfs_unmount(const char *specialfile);

/* extern variable */
extern const struct dfs_filesystem_operation *filesystem_operation_table[];
extern struct dfs_filesystem filesystem_table[];
extern const struct dfs_mount_tbl mount_table[];

extern char working_directory[];

void dfs_lock(void);
void dfs_unlock(void);
int dfs_mkfs(const char *fs_name, const char *device_name);
int dfs_statfs(const char *path, struct statfs *buffer);

#endif
