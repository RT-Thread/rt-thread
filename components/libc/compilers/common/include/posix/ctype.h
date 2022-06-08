/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-07     Meco Man     The first version.
 */

#ifndef __POSIX_CTYPE_H__
#define __POSIX_CTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>

#ifndef isascii /* some toolchain use macro to define it */
int isascii(int c);
#endif
#ifndef toascii
int toascii(int c);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_CTYPE_H__ */
