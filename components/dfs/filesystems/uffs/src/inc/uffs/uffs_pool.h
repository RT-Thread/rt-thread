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
 * \file uffs_pool.h
 * \brief Fast fixed size memory pool management.
 * \author Ricky Zheng, Simon Kallweit
 */

#ifndef _UFFS_POOL_H_
#define _UFFS_POOL_H_


#include "uffs/uffs_types.h"
#include "uffs/uffs_os.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * \struct uffs_PoolEntrySt
 * \brief Helper type for free buffer entries.
 */
typedef struct uffs_PoolEntrySt {
    struct uffs_PoolEntrySt *next;
} uffs_PoolEntry;

/**
 * \struct uffs_PoolSt
 * \brief Memory pool.
 */
typedef struct uffs_PoolSt {
	u8 *mem;					//!< memory pool
	u32 buf_size;				//!< size of a buffer
	u32 num_bufs;				//!< number of buffers in the pool
	uffs_PoolEntry *free_list;	//!< linked list of free buffers
	OSSEM sem;					//!< buffer lock
} uffs_Pool;

URET uffs_PoolInit(uffs_Pool *pool, void *mem, u32 mem_size, u32 buf_size, u32 num_bufs);
URET uffs_PoolRelease(uffs_Pool *pool);

UBOOL uffs_PoolVerify(uffs_Pool *pool, void *p);

void *uffs_PoolGet(uffs_Pool *pool);
void *uffs_PoolGetLocked(uffs_Pool *pool);

int uffs_PoolPut(uffs_Pool *pool, void *p);
int uffs_PoolPutLocked(uffs_Pool *pool, void *p);

void *uffs_PoolGetBufByIndex(uffs_Pool *pool, u32 index);
u32 uffs_PoolGetIndex(uffs_Pool *pool, void *p);
UBOOL uffs_PoolCheckFreeList(uffs_Pool *pool, void *p);

void * uffs_PoolFindNextAllocated(uffs_Pool *pool, void *from);

int uffs_PoolGetFreeCount(uffs_Pool *pool);
int uffs_PoolPutAll(uffs_Pool *pool);

#ifdef __cplusplus
}
#endif

#endif // _UFFS_POOL_H_
