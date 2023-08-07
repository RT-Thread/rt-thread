/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */

#ifndef __POSIX_STDIO_H__
#define __POSIX_STDIO_H__

#include <rtconfig.h>
#include <stdio.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int rt_posix_stdio_init(void);
int rt_posix_stdio_get_console(void);
int rt_posix_stdio_set_console(const char* device_name, int mode);
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_STDIO_H__ */
