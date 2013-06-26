/*
 * File      : dfs_romfs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
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
 */

#ifndef __DFS_ROMFS_H__
#define __DFS_ROMFS_H__

#include <rtthread.h>

#define ROMFS_DIRENT_FILE	0x00
#define ROMFS_DIRENT_DIR	0x01

struct romfs_dirent
{
	rt_uint32_t		 type;	/* dirent type */

	const char		 *name;	/* dirent name */
	const rt_uint8_t *data;	/* file date ptr */
	rt_size_t		 size;	/* file size */
};

int dfs_romfs_init(void);
extern const struct romfs_dirent romfs_root;

#endif
