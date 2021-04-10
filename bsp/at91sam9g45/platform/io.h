/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef __ASM_ARCH_IO_H
#define __ASM_ARCH_IO_H

#define IO_SPACE_LIMIT      0xFFFFFFFF

#define readb(a)    (*(volatile unsigned char  *)(a))
#define readw(a)    (*(volatile unsigned short *)(a))
#define readl(a)    (*(volatile unsigned int   *)(a))

#define writeb(v,a) (*(volatile unsigned char  *)(a) = (v))
#define writew(v,a) (*(volatile unsigned short *)(a) = (v))
#define writel(v,a) (*(volatile unsigned int   *)(a) = (v))

#endif

