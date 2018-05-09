/*
 * File     : libc.h
 * Brief    : armcc libc header file
 *
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017/10/15     bernard      the first version
 */
#ifndef __RTT_LIBC_H__
#define __RTT_LIBC_H__

#include <stddef.h>

int libc_system_init(void);

int libc_stdio_set_console(const char* device_name, int mode);
int libc_stdio_get_console(void);
int libc_stdio_read (void *buffer, size_t size);
int libc_stdio_write(const void *buffer, size_t size);

#endif
