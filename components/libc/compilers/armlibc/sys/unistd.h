/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H

#include <rtthread.h>

#ifdef RT_USING_DFS

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

#include <dfs_posix.h>
#else
#define _FREAD      0x0001  /* read enabled */
#define _FWRITE     0x0002  /* write enabled */
#define _FAPPEND    0x0008  /* append (writes guaranteed at the end) */
#define _FMARK      0x0010  /* internal; mark during gc() */
#define _FDEFER     0x0020  /* internal; defer for next gc pass */
#define _FASYNC     0x0040  /* signal pgrp when data ready */
#define _FSHLOCK    0x0080  /* BSD flock() shared lock present */
#define _FEXLOCK    0x0100  /* BSD flock() exclusive lock present */
#define _FCREAT     0x0200  /* open with file create */
#define _FTRUNC     0x0400  /* open with truncation */
#define _FEXCL      0x0800  /* error on open if file exists */
#define _FNBIO      0x1000  /* non blocking I/O (sys5 style) */
#define _FSYNC      0x2000  /* do all writes synchronously */
#define _FNONBLOCK  0x4000  /* non blocking I/O (POSIX style) */
#define _FNDELAY    _FNONBLOCK  /* non blocking I/O (4.2 style) */
#define _FNOCTTY    0x8000  /* don't assign a ctty on this open */


#ifndef O_RDONLY
#define O_RDONLY    0       /* +1 == FREAD */
#endif
#ifndef O_WRONLY
#define O_WRONLY    1       /* +1 == FWRITE */
#endif
#ifndef O_RDWR
#define O_RDWR      2       /* +1 == FREAD|FWRITE */
#endif
#ifndef O_APPEND
#define O_APPEND    _FAPPEND
#endif
#ifndef O_CREAT
#define O_CREAT     _FCREAT
#endif
#ifndef O_TRUNC
#define O_TRUNC     _FTRUNC
#endif
#ifndef O_EXCL
#define O_EXCL      _FEXCL
#endif
#ifndef O_SYNC
#define O_SYNC      _FSYNC
#endif

#endif


int     isatty      (int fd);
char *  ttyname     (int desc);

#endif /* _SYS_UNISTD_H */
