/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __TYPES_H__
#define __TYPES_H__
#include <rtconfig.h>

typedef long        off_t;
typedef unsigned long size_t;
typedef signed long   ssize_t;      /* Used for a count of bytes or an error indication. */

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef unsigned long  u_long;

typedef int mode_t;

typedef unsigned long clockid_t;
typedef int pid_t;

typedef int gid_t;
typedef int uid_t;
typedef int dev_t;
typedef int ino_t;
typedef int mode_t;
typedef int caddr_t;

typedef unsigned int wint_t;
typedef unsigned long useconds_t;

typedef	unsigned long clock_t; /* clock() */

#ifndef NULL
#define NULL        (0)
#endif

#define __u_char_defined

#endif

