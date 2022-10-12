/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef RTCONFIG_PROJECT_H__
#define RTCONFIG_PROJECT_H__

#define RT_HEAP_SIZE   (1024*1024*8)

#ifdef _MSC_VER
/* disable some warning in MSC */
// #pragma warning(disable:4103)   /* structure packing changed by including file */
// #pragma warning(disable:4273)   /* to ignore: warning C4273: inconsistent dll linkage */
#endif /* _MSC_VER */

#endif /* RTCONFIG_PROJECT_H__ */
