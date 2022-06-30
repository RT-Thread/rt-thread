/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-07     Meco Man     first version
 */

#ifndef __POSIX_STDIO_H__
#define __POSIX_STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/types.h>

#ifdef DFS_USING_POSIX
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#endif /* DFS_USING_POSIX */

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_STDIO_H__ */
