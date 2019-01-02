/*
 * File      : io.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef __ASM_ARCH_IO_H
#define __ASM_ARCH_IO_H

#define IO_SPACE_LIMIT		0xFFFFFFFF

#define readb(a)	(*(volatile unsigned char  *)(a))
#define readw(a)	(*(volatile unsigned short *)(a))
#define readl(a)	(*(volatile unsigned int   *)(a))

#define writeb(v,a)	(*(volatile unsigned char  *)(a) = (v))
#define writew(v,a)	(*(volatile unsigned short *)(a) = (v))
#define writel(v,a)	(*(volatile unsigned int   *)(a) = (v))

#endif

