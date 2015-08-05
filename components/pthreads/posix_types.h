/*
 * File      : posix_types.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2013-12-23     Bernard      Add the checking for ESHUTDOWN 
 */

#ifndef __POSIX_TYPES_H__
#define __POSIX_TYPES_H__

#include <rtthread.h>

#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#include <sys/types.h>
#include <sys/time.h>

/* errno for Keil MDK */
#if defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__)
#include <sys/errno.h>
#include <sys/unistd.h>
#else
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#endif

#endif

