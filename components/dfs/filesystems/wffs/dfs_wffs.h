/*
 * File      : dfs_wffs.h
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
 * 2013-12-15     Jone.Chen	   yuhua8688@tom.com
 */

#ifndef __DFS_WFFS_H__
#define __DFS_WFFS_H__

#include <rtthread.h>

#define wffs_DIRENT_FILE	0x00
#define wffs_DIRENT_DIR	0x01



int dfs_wffs_init(void);
extern const struct wffs_dirent wffs_root;

#endif
