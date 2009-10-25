/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_fs.h, the filesystem related defines of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-02-22     ffxz         The first version.
+------------------------------------------------------------------------------
*/
#ifndef __DFS_FS_H__
#define __DFS_FS_H__

#include <dfs_def.h>
#include <dfs_config.h>

/* Pre-declaration */
struct dfs_filesystem;
struct dfs_fd;
struct dfs_dirent;

/* File system operations struct */
struct dfs_filesystem_operation
{
	char name[DFS_FS_NAME_MAX + 1];

	int (*mount)	(struct dfs_filesystem* fs);
	int (*unmount)	(struct dfs_filesystem* fs);

	int (*open)	(struct dfs_fd* fd);
	int (*close)	(struct dfs_fd* fd);
	int (*ioctl)	(struct dfs_fd* fd, int cmd, void *args);
	int (*read)	(struct dfs_fd* fd, void* buf, rt_size_t count);
	int (*write)	(struct dfs_fd* fd, const void* buf, rt_size_t count);
	int (*lseek)	(struct dfs_fd* fd, rt_off_t offset);
	int (*getdents)	(struct dfs_fd* fd, struct dfs_dirent* dirp, rt_uint32_t count);

	int (*unlink)	(struct dfs_filesystem* fs, const char* pathname);
	int (*stat)		(struct dfs_filesystem* fs, const char* filename, struct dfs_stat* buf);
	int (*rename)	(struct dfs_filesystem* fs, const char* oldpath, const char* newpath);
};

/* Mounted file system */
struct dfs_filesystem
{
	rt_device_t dev_id;					/* Attached device */

	char path[DFS_PATH_MAX + 1];			/* File system mount point */
	struct dfs_filesystem_operation* ops;	/* Operations for file system type */
	rt_uint32_t block_id;					/* Current block_id on attached device */

	void *data;							/* Specific file system data */
};

/* file system partition table */
struct dfs_partition
{
	rt_uint8_t type;		/* file system type */
	rt_off_t  offset;		/* partition start offset */
	rt_size_t size;			/* partition size */
	rt_sem_t lock;	
};

int dfs_register(struct dfs_filesystem_operation* ops);
struct dfs_filesystem* dfs_filesystem_lookup(const char *path);
rt_err_t dfs_filesystem_get_partition(struct dfs_partition* part, rt_uint8_t* buf, rt_uint32_t pindex);

int dfs_mount(const char* device_name, const char* path,
       const char* filesystemtype, rt_uint32_t rwflag, const
       void* data);
int dfs_unmount(const char *specialfile);

/* extern variable */
extern struct dfs_filesystem_operation* filesystem_operation_table[];
extern struct dfs_filesystem filesystem_table[];

extern char working_directory[];

void dfs_lock(void);
void dfs_unlock(void);

#endif
