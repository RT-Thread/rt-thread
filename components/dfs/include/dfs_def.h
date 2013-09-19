/*
 * File      : dfs_def.h
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
 * 2004-10-01     Beranard     The first version.
 * 2004-10-14     Beranard     Clean up the code.
 * 2005-01-22     Beranard     Clean up the code, port to MinGW
 */
 
#ifndef __DFS_DEF_H__
#define __DFS_DEF_H__

#include <rtthread.h>

#ifndef __D_FS__
#define __D_FS__
#endif

#define DEVICE_GETGEOME          0
#define DEVICE_GETINFO           1
#define DEVICE_FORMAT            2
#define DEVICE_CLEAN_SECTOR      3

/* File flags */
#define DFS_F_OPEN               0x01000000
#define DFS_F_DIRECTORY          0x02000000
#define DFS_F_EOF                0x04000000
#define DFS_F_ERR                0x08000000

#ifndef DFS_PATH_MAX
#define DFS_PATH_MAX             256
#endif

#ifndef SECTOR_SIZE
#define SECTOR_SIZE              512
#endif

#ifndef DFS_FILESYSTEM_TYPES_MAX
#define DFS_FILESYSTEM_TYPES_MAX 4
#endif

#define DFS_DEBUG_INFO           0x01
#define DFS_DEBUG_WARNING        0x02
#define DFS_DEBUG_ERROR          0x04
#define DFS_DEBUG_LEVEL          (DFS_DEBUG_INFO | DFS_DEBUG_WARNING | DFS_DEBUG_ERROR)

/* #define DFS_DEBUG */
#ifdef DFS_DEBUG
#define dfs_log(level, x)        do { if (level & DFS_DEBUG_LEVEL)      \
    {rt_kprintf("DFS %s, %d:", __FUNCTION__, __LINE__); rt_kprintf x;   \
    rt_kprintf ("\n");}}while (0)
#else
#define dfs_log(level, x)
#endif

#if defined(RT_USING_NEWLIB) 
#include <string.h>
#include <sys/stat.h>            /* used for struct stat */
#include <sys/statfs.h>          /* used for struct statfs */
#include <sys/errno.h>           /* used for error number */
#include <sys/fcntl.h>           /* used for operation flags */
#include <sys/unistd.h>          /* used for SEEK_SET/CUR/END */
#include <dirent.h>              /* used for struct dirent */

/* Device error codes */
#define DFS_STATUS_OK            0           /* no error */
#define DFS_STATUS_ENOENT        ENOENT      /* No such file or directory */
#define DFS_STATUS_EIO           EIO         /* I/O error */
#define DFS_STATUS_ENXIO         ENXIO       /* No such device or address */
#define DFS_STATUS_EBADF         EBADF       /* Bad file number */
#define DFS_STATUS_EAGAIN        EAGAIN      /* Try again */
#define DFS_STATUS_ENOMEM        ENOMEM      /* no memory */
#define DFS_STATUS_EBUSY         EBUSY       /* Device or resource busy */
#define DFS_STATUS_EEXIST        EEXIST      /* File exists */
#define DFS_STATUS_EXDEV         EXDEV       /* Cross-device link */
#define DFS_STATUS_ENODEV        ENODEV      /* No such device */
#define DFS_STATUS_ENOTDIR       ENOTDIR     /* Not a directory */
#define DFS_STATUS_EISDIR        EISDIR      /* Is a directory */
#define DFS_STATUS_EINVAL        EINVAL      /* Invalid argument */
#define DFS_STATUS_ENOSPC        ENOSPC      /* No space left on device */
#define DFS_STATUS_EROFS         EROFS       /* Read-only file system */
#define DFS_STATUS_ENOSYS        ENOSYS      /* Function not implemented */
#define DFS_STATUS_ENOTEMPTY     ENOTEMPTY   /* Directory not empty */

/* Operation flags */
#define DFS_O_RDONLY             O_RDONLY
#define DFS_O_WRONLY             O_WRONLY
#define DFS_O_RDWR               O_RDWR
#define DFS_O_ACCMODE            O_ACCMODE
#define DFS_O_CREAT              O_CREAT
#define DFS_O_EXCL               O_EXCL
#define DFS_O_TRUNC              O_TRUNC
#define DFS_O_APPEND             O_APPEND
#define DFS_O_DIRECTORY          O_DIRECTORY

/* Seek flags */
#define DFS_SEEK_SET             SEEK_SET
#define DFS_SEEK_CUR             SEEK_CUR
#define DFS_SEEK_END             SEEK_END

/* Stat codes */
#define DFS_S_IFMT               S_IFMT
#define DFS_S_IFSOCK             S_IFSOCK
#define DFS_S_IFLNK              S_IFLNK
#define DFS_S_IFREG              S_IFREG
#define DFS_S_IFBLK              S_IFBLK
#define DFS_S_IFDIR              S_IFDIR
#define DFS_S_IFCHR              S_IFCHR
#define DFS_S_IFIFO              S_IFIFO
#define DFS_S_ISUID              S_ISUID
#define DFS_S_ISGID              S_ISGID
#define DFS_S_ISVTX              S_ISVTX

#define DFS_S_ISLNK(m)           S_ISLNK(m)
#define DFS_S_ISREG(m)           S_ISREG(m)
#define DFS_S_ISDIR(m)           S_ISDIR(m)
#define DFS_S_ISCHR(m)           S_ISCHR(m)
#define DFS_S_ISBLK(m)           S_ISBLK(m)
#define DFS_S_ISFIFO(m)          S_ISFIFO(m)
#define DFS_S_ISSOCK(m)          S_ISSOCK(m)

#define DFS_S_IRWXU              S_IRWXU
#define DFS_S_IRUSR              S_IRUSR
#define DFS_S_IWUSR              S_IWUSR
#define DFS_S_IXUSR              S_IXUSR

#define DFS_S_IRWXG              S_IRWXG
#define DFS_S_IRGRP              S_IRGRP
#define DFS_S_IWGRP              S_IWGRP
#define DFS_S_IXGRP              S_IXGRP

#define DFS_S_IRWXO              S_IRWXO
#define DFS_S_IROTH              S_IROTH
#define DFS_S_IWOTH              S_IWOTH
#define DFS_S_IXOTH              S_IXOTH

/* Dirent types */
#define DFS_DT_UNKNOWN           DT_UNKNOWN
#define DFS_DT_REG               DT_REG
#define DFS_DT_DIR               DT_DIR

#else
    #ifdef RT_USING_MINILIBC
        #include <string.h>
    #else
        typedef long off_t;
        typedef int mode_t;
    #endif

/* Device error codes */
#define DFS_STATUS_OK            0       /* no error */
#define DFS_STATUS_ENOENT        2       /* No such file or directory */
#define DFS_STATUS_EIO           5       /* I/O error */
#define DFS_STATUS_ENXIO         6       /* No such device or address */
#define DFS_STATUS_EBADF         9       /* Bad file number */
#define DFS_STATUS_EAGAIN        11      /* Try again */
#define DFS_STATUS_ENOMEM        12      /* no memory */
#define DFS_STATUS_EBUSY         16      /* Device or resource busy */
#define DFS_STATUS_EEXIST        17      /* File exists */
#define DFS_STATUS_EXDEV         18      /* Cross-device link */
#define DFS_STATUS_ENODEV        19      /* No such device */
#define DFS_STATUS_ENOTDIR       20      /* Not a directory */
#define DFS_STATUS_EISDIR        21      /* Is a directory */
#define DFS_STATUS_EINVAL        22      /* Invalid argument */
#define DFS_STATUS_ENOSPC        28      /* No space left on device */
#define DFS_STATUS_EROFS         30      /* Read-only file system */
#define DFS_STATUS_ENOSYS        38      /* Function not implemented */
#define DFS_STATUS_ENOTEMPTY     39      /* Directory not empty */

/* Operation flags */
#define DFS_O_RDONLY             0x0000000
#define DFS_O_WRONLY             0x0000001
#define DFS_O_RDWR               0x0000002
#define DFS_O_ACCMODE            0x0000003
#define DFS_O_CREAT              0x0000100
#define DFS_O_EXCL               0x0000200
#define DFS_O_TRUNC              0x0001000
#define DFS_O_APPEND             0x0002000
#define DFS_O_BINARY             0x0008000
#define DFS_O_DIRECTORY          0x0200000

/* File flags */
#define DFS_F_OPEN               0x01000000
#define DFS_F_DIRECTORY          0x02000000
#define DFS_F_EOF                0x04000000
#define DFS_F_ERR                0x08000000

/* Seek flags */
#ifdef __CC_ARM
#include <stdio.h>
#define DFS_SEEK_SET             SEEK_SET
#define DFS_SEEK_CUR             SEEK_CUR
#define DFS_SEEK_END             SEEK_END
#elif defined(_MSC_VER)
#include <stdio.h>
#define DFS_SEEK_SET             SEEK_SET
#define DFS_SEEK_CUR             SEEK_CUR
#define DFS_SEEK_END             SEEK_END
#else
#define DFS_SEEK_SET             0
#define DFS_SEEK_CUR             1
#define DFS_SEEK_END             2
#endif

/* Stat codes */
#define DFS_S_IFMT               00170000
#define DFS_S_IFSOCK             0140000
#define DFS_S_IFLNK              0120000
#define DFS_S_IFREG              0100000
#define DFS_S_IFBLK              0060000
#define DFS_S_IFDIR              0040000
#define DFS_S_IFCHR              0020000
#define DFS_S_IFIFO              0010000
#define DFS_S_ISUID              0004000
#define DFS_S_ISGID              0002000
#define DFS_S_ISVTX              0001000

#define DFS_S_ISLNK(m)           (((m) & DFS_S_IFMT) == DFS_S_IFLNK)
#define DFS_S_ISREG(m)           (((m) & DFS_S_IFMT) == DFS_S_IFREG)
#define DFS_S_ISDIR(m)           (((m) & DFS_S_IFMT) == DFS_S_IFDIR)
#define DFS_S_ISCHR(m)           (((m) & DFS_S_IFMT) == DFS_S_IFCHR)
#define DFS_S_ISBLK(m)           (((m) & DFS_S_IFMT) == DFS_S_IFBLK)
#define DFS_S_ISFIFO(m)          (((m) & DFS_S_IFMT) == DFS_S_IFIFO)
#define DFS_S_ISSOCK(m)          (((m) & DFS_S_IFMT) == DFS_S_IFSOCK)

#define DFS_S_IRWXU              00700
#define DFS_S_IRUSR              00400
#define DFS_S_IWUSR              00200
#define DFS_S_IXUSR              00100

#define DFS_S_IRWXG              00070
#define DFS_S_IRGRP              00040
#define DFS_S_IWGRP              00020
#define DFS_S_IXGRP              00010

#define DFS_S_IRWXO              00007
#define DFS_S_IROTH              00004
#define DFS_S_IWOTH              00002
#define DFS_S_IXOTH              00001

struct stat
{
    rt_device_t st_dev;
    rt_uint16_t st_mode;
    rt_uint32_t st_size;
    rt_time_t   st_mtime;
    rt_uint32_t st_blksize;
};

struct statfs
{
    rt_size_t f_bsize;   /* block size */
    rt_size_t f_blocks;  /* total data blocks in file system */
    rt_size_t f_bfree;   /* free blocks in file system */
};

/* File types */
#define FT_REGULAR               0   /* regular file */
#define FT_SOCKET                1   /* socket file  */
#define FT_DIRECTORY             2   /* directory    */
#define FT_USER                  3   /* user defined */

/* Dirent types */
#define DFS_DT_UNKNOWN           0x00
#define DFS_DT_REG               0x01
#define DFS_DT_DIR               0x02

struct dirent
{
    rt_uint8_t d_type;           /* The type of the file */
    rt_uint8_t d_namlen;         /* The length of the not including the terminating null file name */
    rt_uint16_t d_reclen;        /* length of this record */
    char d_name[DFS_PATH_MAX];   /* The null-terminated file name */
};
#endif

/* file descriptor */
#define DFS_FD_MAGIC	 0xfdfd
struct dfs_fd
{
    rt_uint16_t magic;           /* file descriptor magic number */
    rt_uint16_t type;            /* Type (regular or socket) */
    char *path;                  /* Name (below mount point) */
    int ref_count;               /* Descriptor reference count */

    struct dfs_filesystem *fs;   /* Resident file system */

    rt_uint32_t flags;           /* Descriptor flags */
    rt_size_t   size;            /* Size in bytes */
    rt_off_t    pos;             /* Current file position */

    void *data;                  /* Specific file system data */
};

#endif

