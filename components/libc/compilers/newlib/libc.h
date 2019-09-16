/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */
#ifndef __RTT_LIBC_H__
#define __RTT_LIBC_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#ifndef _EXFUN
#define _EXFUN(name, proto)		name proto
#endif

#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

#ifdef __cplusplus
extern "C" {
#endif
int libc_system_init(void);
int libc_stdio_set_console(const char* device_name, int mode);
int libc_stdio_get_console(void);

/* some time related function */
int libc_set_time(const struct timespec* time);
int libc_get_time(struct timespec* time);
int libc_time_to_tick(const struct timespec* time);
#ifdef __cplusplus
}
#endif

#endif
