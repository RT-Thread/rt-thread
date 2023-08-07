/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 * 2023/08/06     Meco Man     rename as stdio_init.h
 */

#ifndef __POSIX_STDIO_INIT_H__
#define __POSIX_STDIO_INIT_H__

#include <rtconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

int posix_stdio_init(void);
#ifdef RT_USING_POSIX_STDIO
int posix_stdio_get_console(void);
int posix_stdio_set_console(const char* device_name, int mode);
#endif /* RT_USING_POSIX_STDIO */

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_STDIO_INIT_H__ */
