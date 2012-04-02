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
 * \file uffs_find.h
 * \brief find objects under dir
 * \author Ricky Zheng
 */

#ifndef _UFFS_FIND_H_
#define _UFFS_FIND_H_

#include "uffs/uffs_fs.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct uffs_FindInfoSt {
	uffs_Device *dev;				//!< the device to be searched
	u16 serial;						//!< the dir serial number
	int step;						//!< step:	0 - working on dir entries,
									//			1 - working on file entries,
									//			2 - stoped.
	int hash;						//!< hash entry, internal used
	TreeNode *work;					//!< working node, internal used.
	int pos;						//!< current position
} uffs_FindInfo;


URET uffs_GetObjectInfo(uffs_Object *obj, uffs_ObjectInfo *info, int *err);
URET uffs_FindObjectOpen(uffs_FindInfo *find_handle, uffs_Object *dir);
URET uffs_FindObjectOpenEx(uffs_FindInfo *f, uffs_Device *dev, int dir);
URET uffs_FindObjectFirst(uffs_ObjectInfo *info, uffs_FindInfo *find_handle);
URET uffs_FindObjectNext(uffs_ObjectInfo *info, uffs_FindInfo *find_handle);
URET uffs_FindObjectRewind(uffs_FindInfo *find_handle);
URET uffs_FindObjectClose(uffs_FindInfo * find_handle);


#ifdef __cplusplus
}
#endif


#endif


