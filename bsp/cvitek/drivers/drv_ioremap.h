/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/07/24     heyuanjie87     first version
 */

#ifndef __DRV_IOREMAP_H__
#define __DRV_IOREMAP_H__

#include <rtconfig.h>

#ifdef RT_USING_SMART
#include <ioremap.h>

#define DRV_IOREMAP(addr, size) rt_ioremap(addr, size)
#define DRV_IOUNMAP(addr) rt_iounmap(addr)
#else
#define DRV_IOREMAP(addr, size) (addr)
#define DRV_IOUNMAP(addr)
#endif

#endif
