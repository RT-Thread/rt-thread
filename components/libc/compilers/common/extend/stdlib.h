/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-30     Meco Man     The first version.
 */

#ifndef __EXTEND_STDLIB_H__
#define __EXTEND_STDLIB_H__

#include <stdint.h>

char *itoa(int n, char *buffer, int radix);
char *lltoa(int64_t ll, char *buffer, int radix);
char *ltoa(long l, char *buffer, int radix);
char *ulltoa(uint64_t ll, char *buffer, int radix);
char *ultoa(unsigned long l, char *buffer, int radix);
char *utoa(unsigned int n, char *buffer, int radix);

#endif /* __EXTEND_STDLIB_H__ */
