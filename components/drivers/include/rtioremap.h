/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-11     heyuanjie87  first version.
 */

#ifndef __RT_RTIOREMAP_H__
#define __RT_RTIOREMAP_H__

#include <rtconfig.h>

#if defined(ARCH_MM_MMU) && defined(MM_USING_IOREMAP)
#include <ioremap.h>
#else
#define rt_ioremap(addr, size) (addr)
#define rt_iounmap(addr)
#endif

#endif
