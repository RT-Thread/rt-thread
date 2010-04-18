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

/*
+------------------------------------------------------------------------------
| Device Manager options
+------------------------------------------------------------------------------
*/
/* Device Options parameters */
#define DEVICES_MAX		8
#define DEVICE_NAME_MAX	8

/*
+------------------------------------------------------------------------------
| Device Filesystem options
+------------------------------------------------------------------------------
*/
/* the max length of filesystem name */
#define DFS_FS_NAME_MAX				4
/* the max type of filesystem */
#define DFS_FILESYSTEM_TYPES_MAX	2

/* the max length of path name */
#define DFS_PATH_MAX		256
/* the max length of file name */
#define DFS_FILE_MAX		256

/* options for server task */
#define DFS_MBOX_NUMBER		32
#define DFS_SERVER_STACK	1024
#define DFS_SERVER_PRI		110
#define DFS_SERVER_SLICE	20

/*
+------------------------------------------------------------------------------
| FAT filesystem options
+------------------------------------------------------------------------------
*/
/* file name max length */
#define FAT_NAME_MAX	256
/* max number of FAT filesystem */
#define FATFS_MAX		2

/* the size of sector */
#define SECTOR_SIZE		512

/* FAT table sector cache options */
#define FAT_CACHE_SIZE          0x10        /* config parameter */
#define FAT_CACHE_MASK          (FAT_CACHE_SIZE-1)

#define GET16(x)    (*(x)) | (*((x)+1) << 8)
#define GET32(x)    (*(x)) | (*((x)+1) << 8) | (*((x)+2) << 16) | (*((x)+3) << 24)

#define SET16(x, v)             	\
    do                          	\
    {                           	\
        *(x)     = (v) & 0x00ff; 	\
        (*((x)+1)) = (v) >> 8;     	\
    } while ( 0 )

#define SET32(x, v)                         	\
    do                                      	\
    {                                       	\
        *(x)     = (v)  & 0x000000ff;        	\
        (*((x)+1)) = ((v) >> 8) & 0x000000ff;  	\
        (*((x)+2)) = ((v) >> 16) & 0x000000ff; 	\
        (*((x)+3)) = ((v) >> 24);              	\
    } while ( 0 )

#define DFS_DEBUG_INFO			0x01
#define DFS_DEBUG_WARNING		0x02
#define DFS_DEBUG_ERROR			0x04

#define DFS_DEBUG_LEVEL			(DFS_DEBUG_INFO | DFS_DEBUG_WARNING | DFS_DEBUG_ERROR)

/* #define DFS_DEBUG */
#ifdef DFS_DEBUG
#define dfs_log(level, x)		do { if (level & DFS_DEBUG_LEVEL) 	\
	{rt_kprintf("DFS %s, %d:", __FILE__, __LINE__); rt_kprintf x;	\
	rt_kprintf ("\n");}}while (0)
#else
#define dfs_log(level, x)
#endif

#endif
