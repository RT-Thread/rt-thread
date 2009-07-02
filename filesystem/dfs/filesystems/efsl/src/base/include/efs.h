/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : efs.c                                                            *
* Release  : 0.3 - devel                                                      *
* Description : This should become the wrapper around efs. It will contain    *
*               functions like efs_init etc.                                  *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 2                     *
* of the License.                                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2006 Lennart Yseboodt *
*                                                    (c)2006 Michael De Nil   *
\*****************************************************************************/

#ifndef __EFS_H__
#define __EFS_H__

/*****************************************************************************/
#include <dfs_fs.h>

#include "types.h"
#include "config.h"
#include "extract.h"
#include "partition.h"

/* WARNING !!!!
 * These includes DO NOT BELONG HERE,
 * remove them when the VFS layer is implemented !!!!
 */
#include "fs.h"
#include "file.h"
#include "tm.h"
#include "ui.h" 

/*****************************************************************************/
#define LINUX_FILE_CONFIG	0x00
#define AVR_SD_CONFIG		0x01
/*****************************************************************************/

#define efs_read_sectors(device, start, count, buf)  rt_device_read(device,  \
	(start) * SECTOR_SIZE, (buf), (count) * SECTOR_SIZE) / SECTOR_SIZE
#define efs_write_sectors(device, start, count, buf) rt_device_write(device, \
	(start) * SECTOR_SIZE, (buf), (count) * SECTOR_SIZE) / SECTOR_SIZE

struct _efsl_fs {
	Partition partition;
	FileSystem filesystem;
};
typedef struct _efsl_fs efsl_fs;

/* EFS filesystem file operations */
int efs_mount(struct dfs_filesystem* fs);
int efs_unmount(struct dfs_filesystem* fs);
int efs_open(struct dfs_fd* file);
int efs_close(struct dfs_fd* file);
int efs_ioctl(struct dfs_fd* file, int cmd, void* args);
int efs_read(struct dfs_fd* file, void* buf, rt_size_t len);
int efs_write(struct dfs_fd* file, const void* buf, rt_size_t len);
int efs_lseek(struct dfs_fd* file, rt_off_t offset);
int efs_getdents(struct dfs_fd* file, struct dfs_dirent* dirp, rt_uint32_t count);
int efs_unlink(struct dfs_filesystem* fs, const char* path);
int efs_stat(struct dfs_filesystem* fs, const char *path, struct dfs_stat *st);
int efs_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath);

/*****************************************************************************/
int efsl_init(void);

#endif

