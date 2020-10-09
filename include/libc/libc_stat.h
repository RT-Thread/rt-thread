/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBC_STAT_H__
#define LIBC_STAT_H__

#include <rtconfig.h>

#if defined(RT_USING_NEWLIB) || defined( __GNUC__ )
/* use header file of newlib */
#include <sys/stat.h>

#elif defined(_WIN32)
#include <sys/stat.h>

#define S_IRWXU              00700
#define S_IRUSR              00400
#define S_IWUSR              00200
#define S_IXUSR              00100

#define S_IRWXG              00070
#define S_IRGRP              00040
#define S_IWGRP              00020
#define S_IXGRP              00010

#define S_IRWXO              00007
#define S_IROTH              00004
#define S_IWOTH              00002
#define S_IXOTH              00001

#define S_IFSOCK             0140000
#define S_IFLNK              0120000
#define S_IFBLK              0060000
#define S_IFIFO              0010000
#define S_ISUID              0004000
#define S_ISGID              0002000
#define S_ISVTX              0001000

#define S_ISDIR(m)           (((m) & S_IFMT) == S_IFDIR)

#else
#define S_IFMT               00170000
#define S_IFSOCK             0140000
#define S_IFLNK              0120000
#define S_IFREG              0100000
#define S_IFBLK              0060000
#define S_IFDIR              0040000
#define S_IFCHR              0020000
#define S_IFIFO              0010000
#define S_ISUID              0004000
#define S_ISGID              0002000
#define S_ISVTX              0001000

#define S_ISLNK(m)           (((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)           (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)           (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)           (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)           (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m)          (((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m)          (((m) & S_IFMT) == S_IFSOCK)

#define S_IRWXU              00700
#define S_IRUSR              00400
#define S_IWUSR              00200
#define S_IXUSR              00100

#define S_IRWXG              00070
#define S_IRGRP              00040
#define S_IWGRP              00020
#define S_IXGRP              00010

#define S_IRWXO              00007
#define S_IROTH              00004
#define S_IWOTH              00002
#define S_IXOTH              00001

/* stat structure */
#include <stdint.h>
#include <time.h>

struct stat
{
    struct rt_device *st_dev;
    uint16_t  st_ino;
    uint16_t  st_mode;
    uint16_t  st_nlink;
    uint16_t  st_uid;
    uint16_t  st_gid;
    struct rt_device *st_rdev;
    uint32_t  st_size;
    time_t    st_atime;
    long      st_spare1;
    time_t    st_mtime;
    long      st_spare2;
    time_t    st_ctime;
    long      st_spare3;
    uint32_t  st_blksize;
    uint32_t  st_blocks;
    long      st_spare4[2];
};

#endif

#endif
