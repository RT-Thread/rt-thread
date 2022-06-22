/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-07     Meco Man     The first version
 */

#ifndef __POSIX_WCHAR_H__
#define __POSIX_WCHAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <wchar.h>

int wcwidth(wchar_t);
int wcswidth(const wchar_t*, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_WCHAR_H__ */
