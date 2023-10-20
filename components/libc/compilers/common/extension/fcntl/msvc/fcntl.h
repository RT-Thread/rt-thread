/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-02     Meco Man     First version
 */

#ifndef __FCNTL_H__
#define __FCNTL_H__

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* VS fcntl.h interent */
#define O_RDONLY        0x0000  /* open for reading only */
#define O_WRONLY        0x0001  /* open for writing only */
#define O_RDWR          0x0002  /* open for reading and writing */
#define O_APPEND        0x0008  /* writes done at eof */

#define O_CREAT         0x0100  /* create and open file */
#define O_TRUNC         0x0200  /* open and truncate */
#define O_EXCL          0x0400  /* open only if file doesn't already exist */

// O_TEXT files have <cr><lf> sequences translated to <lf> on read()'s and <lf>
// sequences translated to <cr><lf> on write()'s
#define O_TEXT          0x4000  /* file mode is text (translated) */

#define O_BINARY        0x8000  /* file mode is binary (untranslated) */
#define O_RAW           O_BINARY
#define O_TEMPORARY     0x0040  /* temporary file bit (file is deleted when last handle is closed) */
#define O_NOINHERIT     0x0080  /* child process doesn't inherit file */
#define O_SEQUENTIAL    0x0020  /* file access is primarily sequential */
#define O_RANDOM        0x0010  /* file access is primarily random */

/* extension */
#define O_ACCMODE       0x0003  /* mask for above modes, from 4.4BSD https://minnie.tuhs.org/cgi-bin/utree.pl?file=4.4BSD/usr/include/sys/fcntl.h */
#define O_NONBLOCK      0x0004  /* non blocking I/O, from BSD apple https://opensource.apple.com/source/xnu/xnu-1228.0.2/bsd/sys/fcntl.h */
#define O_DIRECTORY     0x200000 /* from Newlib */

#define F_DUPFD  0
#define F_GETFD  1
#define F_SETFD  2
#define F_GETFL  3
#define F_SETFL  4

#define F_SETOWN 8
#define F_GETOWN 9
#define F_SETSIG 10
#define F_GETSIG 11

#define F_GETLK 12
#define F_SETLK 13
#define F_SETLKW 14

#define F_SETOWN_EX 15
#define F_GETOWN_EX 16

#define F_GETOWNER_UIDS 17

int open(const char *file, int flags, ...);
int fcntl(int fildes, int cmd, ...);
int creat(const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif

#endif
