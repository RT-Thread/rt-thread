/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-30     Meco Man     The first version.
 */

#ifndef __EXTEND_STDIO_H__
#define __EXTEND_STDIO_H__

#include <stdio.h>
#include <sys/types.h>

#if defined(__ICCARM__) && (_DLIB_FILE_DESCRIPTOR == 0)
typedef void FILE;
#endif

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif /* __EXTEND_STDIO_H__ */
