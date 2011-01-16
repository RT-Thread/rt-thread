/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/
/** 
 * \file uffs.h
 * \brief uffs basic defines
 * \author Ricky Zheng
 */

#ifndef _UFFS_H_
#define _UFFS_H_
#include <dfs_def.h>
#include "uffs/uffs_types.h"

#ifdef __cplusplus
extern "C"{
#endif

#define UO_RDONLY		DFS_O_RDONLY	/** read only */
#define UO_WRONLY		DFS_O_WRONLY	/** write only */
#define UO_RDWR			DFS_O_RDWR		/** read and write */
#define UO_APPEND		DFS_O_APPEND	/** append */

#define UO_BINARY		0x0000			/** no used in uffs */

#define UO_CREATE		DFS_O_CREAT		
#define UO_TRUNC		DFS_O_TRUNC		
#define UO_EXCL			DFS_O_EXCL

#define UO_DIR			DFS_O_DIRECTORY	/** open a directory */



#define UENOERR 		0	/** no error */
#define UEACCES			1	/** Tried to open read-only file
						 	for writing, or files sharing mode
						 	does not allow specified operations,
						 	or given path is directory */

#define UEEXIST			2	/** _O_CREAT and _O_EXCL flags specified,
							but filename already exists */
#define UEINVAL			3	/** Invalid oflag or pmode argument */
#define UEMFILE			4	/** No more file handles available
						  	(too many open files)  */
#define UENOENT			5	/** file or path not found */
#define UETIME			6	/** can't set file time */
#define UEBADF			9	/** invalid file handle */
#define UENOMEM			10	/** no enough memory */
#define UEIOERR			11	/** I/O error from lower level flash operation */
#define UENOTDIR 		12	/** Not a directory */
#define UEISDIR 		13	/** Is a directory */ 

#define UEUNKNOWN		100	/** unknown error */
	

#define _SEEK_CUR		0		/** seek from current position */
#define _SEEK_SET		1		/** seek from beginning of file */
#define _SEEK_END		2		/** seek from end of file */

#define USEEK_SET		DFS_SEEK_SET  	/*0* 从当前点寻找 */
#define USEEK_CUR		DFS_SEEK_CUR	/*1* 从文件的开始寻找 */
#define USEEK_END		DFS_SEEK_END	/*2* 从文件的结尾寻找 */




/** 
 * \def MAX_FILENAME_LENGTH 
 * \note Be careful: it's part of the physical format (see: uffs_FileInfoSt.name)
 *    !!DO NOT CHANGE IT AFTER FILE SYSTEM IS FORMATED!!
 */
#define MAX_FILENAME_LENGTH			32

/** \note 8-bits attr goes to uffs_dirent::d_type */
#define FILE_ATTR_DIR		(1 << 7)	//!< attribute for directory
#define FILE_ATTR_WRITE		(1 << 0)	//!< writable


/*
 * \structure uffs_FileInfoSt
 * \brief file/dir entry info in physical storage format
 */
struct uffs_FileInfoSt {
	u32 attr;				//!< file/dir attribute
	u32 create_time;
	u32 last_modify;
	u32 access;
	u32 reserved;
	u32 name_len;			//!< length of file/dir name
	char name[MAX_FILENAME_LENGTH];
};
typedef struct uffs_FileInfoSt uffs_FileInfo;

/**
 * \struct uffs_ObjectInfoSt
 * \brief object info
 */
typedef struct uffs_ObjectInfoSt {
	uffs_FileInfo info;
	u32 len;				//!< length of file
	u16 serial;				//!< object serial num
} uffs_ObjectInfo;


#ifdef __cplusplus
}
#endif


#endif

