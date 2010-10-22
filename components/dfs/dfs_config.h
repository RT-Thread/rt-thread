/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_opts.h, the option definitions of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2005-01-22     ffxz         The first version.
+------------------------------------------------------------------------------
*/

#ifndef __DFS_CONFIG_H__
#define __DFS_CONFIG_H__

/* the max type of filesystem */
#define DFS_FILESYSTEM_TYPES_MAX	4

/* the max length of path name */
#define DFS_PATH_MAX				256

/* the size of sector */
#define SECTOR_SIZE					512

#define DFS_DEBUG_INFO				0x01
#define DFS_DEBUG_WARNING			0x02
#define DFS_DEBUG_ERROR				0x04
#define DFS_DEBUG_LEVEL				(DFS_DEBUG_INFO | DFS_DEBUG_WARNING | DFS_DEBUG_ERROR)

/* #define DFS_DEBUG */
#ifdef DFS_DEBUG
#define dfs_log(level, x)		do { if (level & DFS_DEBUG_LEVEL) 	\
	{rt_kprintf("DFS %s, %d:", __FUNCTION__, __LINE__); rt_kprintf x;	\
	rt_kprintf ("\n");}}while (0)
#else
#define dfs_log(level, x)
#endif

#endif

