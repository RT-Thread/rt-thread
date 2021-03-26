/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-07     Bernard      Add O_DIRECTORY definition in NEWLIB mode.
 * 2018-02-09     Bernard      Add O_BINARY definition
 */

#ifndef LIBC_FCNTL_H__
#define LIBC_FCNTL_H__

#if defined(RT_USING_NEWLIB) || defined(_WIN32) || (defined( __GNUC__ ) && !defined(__ARMCC_VERSION))
#include <fcntl.h>

#ifndef O_NONBLOCK
#define O_NONBLOCK   0x4000
#endif

#if defined(_WIN32)
#define O_ACCMODE   (_O_RDONLY | _O_WRONLY | _O_RDWR)
#endif

#ifndef F_GETFL
#define F_GETFL  3
#endif
#ifndef F_SETFL
#define F_SETFL  4
#endif

#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#ifndef O_BINARY
#ifdef  _O_BINARY
#define O_BINARY _O_BINARY
#else
#define O_BINARY         0
#endif
#endif

#else
#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

#define O_CREAT        0100
#define O_EXCL         0200
#define O_NOCTTY       0400
#define O_TRUNC       01000
#define O_APPEND      02000
#define O_NONBLOCK    04000
#define O_DSYNC      010000
#define O_SYNC     04010000
#define O_RSYNC    04010000
#define O_BINARY    0100000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW  0400000
#define O_CLOEXEC  02000000

#define O_ASYNC      020000
#define O_DIRECT     040000
#define O_LARGEFILE 0100000
#define O_NOATIME  01000000
#define O_PATH    010000000
#define O_TMPFILE 020200000
#define O_NDELAY O_NONBLOCK

#define O_SEARCH  O_PATH
#define O_EXEC    O_PATH

#define O_ACCMODE (03|O_SEARCH)

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
#endif

#endif
