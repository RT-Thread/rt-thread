/*
 * File      : dfs_romfs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
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
