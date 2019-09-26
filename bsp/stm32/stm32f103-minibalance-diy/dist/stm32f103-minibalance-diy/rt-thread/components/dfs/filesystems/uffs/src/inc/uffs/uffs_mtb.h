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
 * \file uffs_mtb.h
 * \brief mount table related stuff
 * \author Ricky Zheng
 */

#ifndef _UFFS_MTB_H_
#define _UFFS_MTB_H_

#include "uffs/uffs_types.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef struct uffs_MountTableEntrySt {
	uffs_Device *dev;		// UFFS 'device' - core internal data structure for partition
	int start_block;		// partition start block
	int end_block;			// partition end block ( if < 0, reserve space form the end of storage)
	const char *mount;		// mount point
	struct uffs_MountTableEntrySt *prev;
	struct uffs_MountTableEntrySt *next;
} uffs_MountTable;

/** Register mount entry, will be put at 'unmounted' list */
int uffs_RegisterMountTable(uffs_MountTable *mtb);

/** Remove mount entry from the list */
int uffs_UnRegisterMountTable(uffs_MountTable *mtb);

/** mount partition */
int uffs_Mount(const char *mount);

/** unmount parttion */
int uffs_UnMount(const char *mount);

/** get mounted entry list */
uffs_MountTable * uffs_MtbGetMounted(void);

/** get unmounted entry list */
uffs_MountTable * uffs_MtbGetUnMounted(void);

/** get matched mount point from absolute path */
int uffs_GetMatchedMountPointSize(const char *path);			

/** get uffs device from mount point */
uffs_Device * uffs_GetDeviceFromMountPoint(const char *mount);	

/** get uffs device from mount point */
uffs_Device * uffs_GetDeviceFromMountPointEx(const char *mount, int len);	

/** get mount point name from uffs device */
const char * uffs_GetDeviceMountPoint(uffs_Device *dev);		

/** down crease uffs device references by uffs_GetDeviceXXX() */
void uffs_PutDevice(uffs_Device *dev);							

#ifdef __cplusplus
}
#endif
#endif
