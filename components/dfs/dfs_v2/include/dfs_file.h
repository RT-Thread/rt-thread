/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-01-26     Bernard      The first version.
 * 2023-05-05     Bernard      Change to dfs v2.0
 */

#ifndef __DFS_FILE_H__
#define __DFS_FILE_H__

#include <dfs.h>
#include <dfs_fs.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define STDIN_FILENO  0     /* standard input file descriptor */
#define STDOUT_FILENO 1     /* standard output file descriptor */
#define STDERR_FILENO 2     /* standard error file descriptor */

struct dfs_file;
struct dfs_vnode;
struct dfs_dentry;
struct dfs_attr;

struct rt_pollreq;
struct dirent;
struct lwp_avl_struct;
struct file_lock;

struct dfs_file_ops
{
    int (*open)(struct dfs_file *file);
    int (*close)(struct dfs_file *file);
    int (*ioctl)(struct dfs_file *file, int cmd, void *arg);
    ssize_t (*read)(struct dfs_file *file, void *buf, size_t count, off_t *pos);
    ssize_t (*write)(struct dfs_file *file, const void *buf, size_t count, off_t *pos);
    int (*flush)(struct dfs_file *file);
    off_t (*lseek)(struct dfs_file *file, off_t offset, int wherece);
    int (*truncate)(struct dfs_file *file, off_t offset);
    int (*getdents)(struct dfs_file *file, struct dirent *dirp, uint32_t count);
    int (*poll)(struct dfs_file *file, struct rt_pollreq *req);

    int (*mmap)(struct dfs_file *file, struct lwp_avl_struct *mmap);
    int (*lock)(struct dfs_file *file, struct file_lock *flock);
    int (*flock)(struct dfs_file *file, int, struct file_lock *flock);
};

struct dfs_vnode
{
    uint32_t flags;
    uint32_t mode;
    int type;               /* node type */

    rt_atomic_t ref_count;  /* reference count */

    struct dfs_mnt *mnt;    /* which mounted file system does this vnode belong to */

    size_t size;
    uint32_t nlink;

    const struct dfs_file_ops *fops;

    unsigned int uid;
    unsigned int gid;
    struct timespec atime;
    struct timespec mtime;
    struct timespec ctime;

    void *data;             /* private data of this file system */
};

/* file descriptor */
#define DFS_FD_MAGIC 0xfdfd
struct dfs_file
{
    uint16_t magic;
    uint16_t mode;

    uint32_t flags;
    rt_atomic_t ref_count;

    off_t fpos;
    struct rt_mutex pos_lock;

    const struct dfs_file_ops *fops;
    struct dfs_dentry *dentry;  /* dentry of this file */
    struct dfs_vnode *vnode;    /* vnode of this file */

    void *data;
};

/* file is open for reading */
#define FMODE_READ 0x1
/* file is open for writing */
#define FMODE_WRITE 0x2
/* file is seekable */
#define FMODE_LSEEK 0x4
/* file can be accessed using pread */
#define FMODE_PREAD 0x8
/* file can be accessed using pwrite */
#define FMODE_PWRITE 0x10
/* File is opened for execution with sys_execve / sys_uselib */
#define FMODE_EXEC 0x20
/* File is opened with O_NDELAY (only set for block devices) */
#define FMODE_NDELAY 0x40
/* File is opened with O_EXCL (only set for block devices) */
#define FMODE_EXCL 0x80

/* dfs_vnode.c */
int dfs_vnode_init(struct dfs_vnode *vnode, int type, const struct dfs_file_ops *fops);
struct dfs_vnode *dfs_vnode_create(void);
int dfs_vnode_destroy(struct dfs_vnode* vnode);

struct dfs_vnode *dfs_vnode_ref(struct dfs_vnode *vnode);
void dfs_vnode_unref(struct dfs_vnode *vnode);

/*dfs_file.c*/

struct dfs_mmap2_args
{
    void *addr;
    size_t length;
    int prot;
    int flags;
    off_t pgoffset;

    void *ret;
};

void dfs_file_init(struct dfs_file *file);
void dfs_file_deinit(struct dfs_file *file);

int dfs_file_open(struct dfs_file *file, const char *path, int flags, mode_t mode);
int dfs_file_close(struct dfs_file *file);

off_t dfs_file_get_fpos(struct dfs_file *file);
void dfs_file_set_fpos(struct dfs_file *file, off_t fpos);
ssize_t dfs_file_read(struct dfs_file *file, void *buf, size_t len);
ssize_t dfs_file_write(struct dfs_file *file, const void *buf, size_t len);
off_t generic_dfs_lseek(struct dfs_file *file, off_t offset, int whence);
off_t dfs_file_lseek(struct dfs_file *file, off_t offset, int wherece);
int dfs_file_stat(const char *path, struct stat *buf);
int dfs_file_lstat(const char *path, struct stat *buf);
int dfs_file_setattr(const char *path, struct dfs_attr *attr);
int dfs_file_fstat(struct dfs_file *file, struct stat *buf);
int dfs_file_ioctl(struct dfs_file *file, int cmd, void *args);
int dfs_file_fcntl(int fd, int cmd, unsigned long arg);
int dfs_file_fsync(struct dfs_file *file);
int dfs_file_unlink(const char *path);
int dfs_file_link(const char *oldname, const char *newname);
int dfs_file_symlink(const char *oldname, const char *name);
int dfs_file_readlink(const char *path, char *buf, int bufsize);
int dfs_file_rename(const char *old_file, const char *new_file);
int dfs_file_ftruncate(struct dfs_file *file, off_t length);
int dfs_file_getdents(struct dfs_file *file, struct dirent *dirp, size_t nbytes);
int dfs_file_mkdir(const char *path, mode_t mode);
int dfs_file_rmdir(const char *pathname);
int dfs_file_isdir(const char *path);
int dfs_file_access(const char *path, mode_t mode);
int dfs_file_chdir(const char *path);
char *dfs_file_getcwd(char *buf, size_t size);
int dfs_file_mmap2(struct dfs_file *file, struct dfs_mmap2_args *mmap2);

/* 0x5254 is just a magic number to make these relatively unique ("RT") */
#define RT_FIOFTRUNCATE  0x52540000U
#define RT_FIOGETADDR    0x52540001U
#define RT_FIOMMAP2      0x52540002U

#ifdef __cplusplus
}
#endif

#endif
