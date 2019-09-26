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

#ifndef _UFFS_MEM_H_
#define _UFFS_MEM_H_

#include "uffs/uffs_device.h"

#ifdef __cplusplus
extern "C"{
#endif

/** uffs memory allocator */
typedef struct uffs_memAllocatorSt {
	URET (*init)(struct uffs_DeviceSt *dev);			//!< init memory allocator, setup buffer sizes
	URET (*release)(struct uffs_DeviceSt *dev);			//!< release memory allocator (for dynamic memory allocation)
	
	void * (*malloc)(struct uffs_DeviceSt *dev, unsigned int size); //!< allocate memory (for dynamic memory allocation)
	URET (*free)(struct uffs_DeviceSt *dev, void *p);   //!< free memory (for dynamic memory allocation)

	void * blockinfo_pool_buf;			//!< block info cache buffers
	void * pagebuf_pool_buf;			//!< page buffers
	void * tree_nodes_pool_buf;			//!< tree nodes buffer
	void * spare_pool_buf;				//!< spare buffers

	int blockinfo_pool_size;			//!< block info cache buffers size
	int pagebuf_pool_size;				//!< page buffers size
	int tree_nodes_pool_size;			//!< tree nodes buffer size
	int spare_pool_size;				//!< spare buffer pool size

	uffs_Pool tree_pool;
	uffs_Pool spare_pool;

	int spare_data_size;				//!< spare size consumed by UFFS, 
										//!< calculated by UFFS according to the layout information.

	/* for static memory allocator */
	char *buf_start;
	int buf_size;
	int pos;


} uffs_MemAllocator;

void uffs_MemSetupSystemAllocator(uffs_MemAllocator *allocator);
void uffs_MemSetupStaticAllocator(uffs_MemAllocator *allocator, void *pool, int size);

#ifdef __cplusplus
}
#endif


#endif

