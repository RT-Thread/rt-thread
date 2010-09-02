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

#ifndef UFFS_UTILS_H
#define UFFS_UTILS_H

#include "uffs/uffs_types.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif


//begin method
#define PARTITION_FOLLOW_PRIVATE	0
#define PARTITION_BEGIN_ABSOLUTE	1
	
//alloc method
#define ALLOC_BY_SIZE		0
#define ALLOC_BY_ABSOLUTE	1
#define ALLOC_USE_FREE		2

//struct uffs_PartitionMakeInfoSt {
//	u32 begin_method;
//	u32	alloc_method;
//	union{
//		u32 begin_block;
//		u32 begin_offset;
//	};
//	union{
//		u32 end_block;
//		u32 size;
//		u32 remain_size;
//	};
//	u32 access;
//};
//
//
//URET uffs_MakePartition(struct uffs_DeviceSt *dev, struct uffs_PartitionMakeInfoSt *pi, int nums);
//
//void uffs_ListPartition(struct uffs_DeviceSt *dev);

//get UFFS disk version, if fail, return 0
int uffs_GetUFFSVersion(struct uffs_DeviceSt *dev);

URET uffs_FormatDevice(uffs_Device *dev);

#ifdef __cplusplus
}
#endif


#endif

