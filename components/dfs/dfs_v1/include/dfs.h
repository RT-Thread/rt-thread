/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 */

#ifndef __DFS_H__
#define __DFS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DFS_FILESYSTEMS_MAX
#define DFS_FILESYSTEMS_MAX     4
#endif

#ifndef DFS_FD_MAX
#define DFS_FD_MAX              16
#endif

/*
 * skip stdin/stdout/stderr normally
 */
#ifndef DFS_STDIO_OFFSET
#define DFS_STDIO_OFFSET           3
#endif

#ifndef DFS_PATH_MAX
#define DFS_PATH_MAX             DIRENT_NAME_MAX
#endif

#ifndef SECTOR_SIZE
#define SECTOR_SIZE              512
#endif

#ifndef DFS_FILESYSTEM_TYPES_MAX
#define DFS_FILESYSTEM_TYPES_MAX 2
#endif

#define DFS_FS_FLAG_DEFAULT     0x00    /* default flag */
#define DFS_FS_FLAG_FULLPATH    0x01    /* set full path to underlaying file system */

/* File types */
#define FT_REGULAR               0   /* regular file */
#define FT_SOCKET                1   /* socket file  */
#define FT_DIRECTORY             2   /* directory    */
#define FT_USER                  3   /* user defined */
#define FT_DEVICE                4   /* device */

/* File flags */
#define DFS_F_OPEN              0x01000000
#define DFS_F_DIRECTORY         0x02000000
#define DFS_F_EOF               0x04000000
#define DFS_F_ERR               0x08000000

#ifdef RT_USING_DFS_LARGE_FILE
typedef int64_t dfs_off_t;
#define DFS_OFF_MAX INT64_MAX
#else
typedef int32_t dfs_off_t;
#define DFS_OFF_MAX INT32_MAX
#endif

struct dfs_stat
{
    dev_t st_dev;
    uint16_t st_ino;
    uint16_t st_mode;
    uint16_t st_nlink;
    uint16_t st_uid;
    uint16_t st_gid;
    struct rt_device *st_rdev;
    dfs_off_t st_size;
    time_t atime;
    long st_spare1;
    time_t mtime;
    long st_spare2;
    time_t ctime;
    long st_spare3;
    uint32_t st_blksize;
    uint32_t st_blocks;
    long st_spare4[2];
};

void dfs_print_off_t(dfs_off_t value);

struct dfs_fdtable
{
    uint32_t maxfd;
    struct dfs_file **fds;
};

/* Initialization of dfs */
int dfs_init(void);

char *dfs_normalize_path(const char *directory, const char *filename);
const char *dfs_subdir(const char *directory, const char *filename);

void dfs_lock(void);
void dfs_unlock(void);

void dfs_file_lock(void);
void dfs_file_unlock(void);

void dfs_fm_lock(void);
void dfs_fm_unlock(void);

void fd_init(struct dfs_file *fd);

#ifdef DFS_USING_POSIX

/* FD APIs */
int fdt_fd_new(struct dfs_fdtable *fdt);
struct dfs_file *fdt_fd_get(struct dfs_fdtable* fdt, int fd);
void fdt_fd_release(struct dfs_fdtable* fdt, int fd);

int fd_new(void);
struct dfs_file *fd_get(int fd);
void fd_release(int fd);

int fd_is_open(const char *pathname);
int fd_associate(struct dfs_fdtable *fdt, int fd, struct dfs_file *file);
int fd_get_fd_index(struct dfs_file *file);

struct dfs_fdtable *dfs_fdtable_get(void);
struct dfs_fdtable *dfs_fdtable_get_global(void);
#endif /* DFS_USING_POSIX */

#ifdef __cplusplus
}
#endif

#endif
