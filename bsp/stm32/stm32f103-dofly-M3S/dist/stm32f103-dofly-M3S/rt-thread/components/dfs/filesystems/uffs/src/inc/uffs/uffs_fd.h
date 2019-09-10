/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file uffs_fd.h
 * \brief PISIX like file operations
 * \author Ricky Zheng, created 8th Jun, 2005
 */

#ifndef _UFFS_FD_H_
#define _UFFS_FD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "uffs/uffs.h"

/**
 * \brief definitions for uffs_stat::st_mode
 */
#define	US_IFMT		0xF000	/* file type make */
#define	US_IFREG	0x8000	/* regular */
#define	US_IFLNK	0xA000	/* symbolic link */
#define	US_IFDIR	0x4000	/* directory */
#define	US_IREAD	0000400	/* read permission */
#define	US_IWRITE	0000200	/* write permission */

#define	US_IRWXU	00700	/* RWX	owner */
#define	US_IRUSR	00400	/* R	owner */
#define	US_IWUSR	00200	/* W	owner */
#define	US_IXUSR	00100	/* X	owner */
#define	US_IRWXG	00070	/* RWX	group */
#define	US_IRGRP	00040	/* R	group */
#define	US_IWGRP	00020	/* W	group */
#define	US_IXGRP	00010	/* X	group */
#define	US_IRWXO	00007	/* RWX	other */
#define	US_IROTH	00004	/* R	other */
#define	US_IWOTH	00002	/* W	other */
#define	US_IXOTH	00001	/* X	other */

/**
 * \brief POSIX dirent
 */
struct uffs_dirent {
    int d_ino;							/* inode number (serial number of this object) */
    int d_off;							/* offset to this dirent */
    unsigned short int d_reclen;		/* length of this uffs_dirent */
    unsigned short int d_namelen;		/* length of this d_name */
    unsigned char d_type;				/* type of this record */
    char d_name[256];					/* name of this object */
};

struct uffs_dirSt;
typedef struct uffs_dirSt uffs_DIR;

/**
 * \brief POSIX stat
 */
struct uffs_stat {
    int			st_dev;     /* ID of device containing file */
    int			st_ino;     /* inode number */
    int			st_mode;    /* protection */
    int			st_nlink;   /* number of hard links */
    int			st_uid;     /* user ID of owner */
    int			st_gid;     /* group ID of owner */
    int			st_rdev;    /* device ID (if special file) */
    long		st_size;    /* total size, in bytes */
    int			st_blksize; /* blocksize for filesystem I/O */
    int			st_blocks;  /* number of blocks allocated */
    unsigned int	st_atime;   /* time of last access */
    unsigned int	st_mtime;   /* time of last modification */
    unsigned int	st_ctime;   /* time of last status change */
};

/* POSIX complaint file system APIs */

int uffs_open(const char *name, int oflag, ...);
int uffs_close(int fd);
int uffs_read(int fd, void *data, int len);
int uffs_write(int fd, const void *data, int len);
long uffs_seek(int fd, long offset, int origin);
long uffs_tell(int fd);
int uffs_eof(int fd);
int uffs_flush(int fd);
int uffs_rename(const char *old_name, const char *new_name);
int uffs_remove(const char *name);
int uffs_ftruncate(int fd, long remain);

int uffs_mkdir(const char *name, ...);
int uffs_rmdir(const char *name);

int uffs_stat(const char *name, struct uffs_stat *buf);
int uffs_lstat(const char *name, struct uffs_stat *buf);
int uffs_fstat(int fd, struct uffs_stat *buf);

int uffs_closedir(uffs_DIR *dirp);
uffs_DIR * uffs_opendir(const char *path);
struct uffs_dirent * uffs_readdir(uffs_DIR *dirp);

void uffs_rewinddir(uffs_DIR *dirp);


int uffs_get_error(void);
int uffs_set_error(int err);

int uffs_version(void);
int uffs_format(const char *mount_point);

long uffs_space_total(const char *mount_point);
long uffs_space_used(const char *mount_point);
long uffs_space_free(const char *mount_point);

void uffs_flush_all(const char *mount_point);

#ifdef __cplusplus
}
#endif
#endif



