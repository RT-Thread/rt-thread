/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_raw.h, the raw APIs of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-01-26     ffxz		  The first version
+------------------------------------------------------------------------------
*/

#ifndef __DFS_RAW_H__
#define __DFS_RAW_H__

#include <dfs_def.h>
#include <dfs_fs.h>

int dfile_raw_open(struct dfs_fd* fd, const char *path, int flags);
int dfile_raw_close(struct dfs_fd* fd);
int dfile_raw_ioctl(struct dfs_fd* fd, int cmd, void *args);
int dfile_raw_read(struct dfs_fd* fd, void *buf, rt_size_t len);
int dfile_raw_getdents(struct dfs_fd* fd, struct dfs_dirent* dirp, rt_size_t nbytes);
int dfile_raw_unlink(const char *path);
int dfile_raw_write(struct dfs_fd* fd, const void *buf, rt_size_t len);
int dfile_raw_lseek(struct dfs_fd* fd, rt_off_t offset);
int dfile_raw_stat(const char *path, struct dfs_stat *buf);
int dfile_raw_rename(const char* oldpath, const char* newpath);

/* FD APIs */
int fd_new(void);
struct dfs_fd* fd_get(int fd);
void fd_put(struct dfs_fd* fd);

#endif
