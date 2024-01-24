/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-07     Meco Man     The first version.
 */

#ifndef __POSIX_STDLIB_H__
#define __POSIX_STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

void __rt_libc_exit(int status);

char *itoa(int n, char *buffer, int radix);
char *lltoa(int64_t ll, char *buffer, int radix);
char *ltoa(long l, char *buffer, int radix);
char *ulltoa(uint64_t ll, char *buffer, int radix);
char *ultoa(unsigned long l, char *buffer, int radix);
char *utoa(unsigned int n, char *buffer, int radix);

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_STDLIB_H__ */
