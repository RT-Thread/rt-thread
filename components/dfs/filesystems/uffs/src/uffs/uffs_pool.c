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
 * \file uffs_pool.c
 * \brief Fast fixed size memory pool management.
 * \author Ricky Zheng, Simon Kallweit
 */

#include "uffs_config.h" 
#include "uffs/uffs_types.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_pool.h"

/*

	usage:

	#define BUF_SIZE	32
	#define NUM_BUFS	1024

	static int pool_mem[NUM_BUFS * BUF_SIZE / sizeof(int)];
	static uffs_Pool pool;

	uffs_PoolInit(&pool, pool_mem, sizeof(pool_mem), BUF_SIZE, NUM_BUFS);

	void * p;
	p = uffs_PoolGet(&pool);
	...
	uffs_PoolPut(p, &pool);

	notice:

	uffs_PoolInit will assert when NUM_BUFS is not at least 1, or BUF_SIZE is
	not	aligned to the platforms pointer size.

*/


/**
 * \brief Initializes the memory pool.
 * \param[in] pool memory pool
 * \param[in] mem pool memory
 * \param[in] mem_size size of pool memory
 * \param[in] buf_size size of a single buffer
 * \param[in] num_bufs number of buffers
 * \return Returns U_SUCC if successful.
 */
URET uffs_PoolInit(uffs_Pool *pool,
				   void *mem, u32 mem_size, u32 buf_size, u32 num_bufs)
{
	unsigned int i;
	uffs_PoolEntry *e1, *e2;

	if (!uffs_Assert(pool != NULL, "pool missing") ||
		!uffs_Assert(mem != NULL, "pool memory missing") ||
		!uffs_Assert(num_bufs > 0, "not enough buffers") ||
		!uffs_Assert(buf_size % sizeof(void *) == 0,
					"buffer size not aligned to pointer size") ||
		!uffs_Assert(mem_size == num_bufs * buf_size,
					"pool memory size is wrong"))
	{
		return U_FAIL;
	}

	pool->mem = (u8 *)mem;
	pool->buf_size = buf_size;
	pool->num_bufs = num_bufs;

	uffs_SemCreate(&pool->sem);	
	uffs_SemWait(pool->sem);

	// Initialize the free_list
	e1 = e2 = pool->free_list = (uffs_PoolEntry *) pool->mem;
	for (i = 1; i < pool->num_bufs; i++) {
		e2 = (uffs_PoolEntry *) (pool->mem + i * pool->buf_size);
		e1->next = e2;
		e1 = e2;
	}
	e2->next = NULL;
	
	uffs_SemSignal(pool->sem);

	return U_SUCC;
}

/**
 * \brief verify pointer validity aganist memory pool
 * \return U_TRUE if valid, U_FALSE if invalid.
 */
UBOOL uffs_PoolVerify(uffs_Pool *pool, void *p)
{
	return p &&
		(u8 *)p >= pool->mem &&
		(u8 *)p < pool->mem + (pool->buf_size * pool->num_bufs) &&
		(((u8 *)p - pool->mem) % pool->buf_size) == 0 ? U_TRUE : U_FALSE;
}

/**
 * \brief Releases the memory pool.
 * \param[in] pool memory pool
 * \return Returns U_SUCC if successful.
 */
URET uffs_PoolRelease(uffs_Pool *pool)
{
	if (!uffs_Assert(pool != NULL, "pool missing"))
		return U_FAIL;
	
	uffs_SemDelete(&pool->sem);

	return U_SUCC;
}

/**
 * \brief Get a buffer from the memory pool.
 * \param[in] pool memory pool
 * \return Returns a pointer to the buffer or NULL if none is available.
 */
void *uffs_PoolGet(uffs_Pool *pool)
{
	uffs_PoolEntry *e;

	if (!uffs_Assert(pool != NULL, "pool missing"))
		return NULL;

	e = pool->free_list;
	if (e)
		pool->free_list = e->next;

	return e;
}

/**
 * \brief Get a buffer from the memory pool.
 * This version is locked and should be used when multiple threads access the
 * same memory pool.
 * \param[in] pool memory pool
 * \return Returns a pointer to the buffer or NULL if none is available.
 */
void *uffs_PoolGetLocked(uffs_Pool *pool)
{
	uffs_PoolEntry *e;

	if (!uffs_Assert(pool != NULL, "pool missing"))
		return NULL;

	uffs_SemWait(pool->sem);
	e = pool->free_list;
	if (e)
		pool->free_list = e->next;
	uffs_SemSignal(pool->sem);

	return e;
}

/**
 * \brief Puts a buffer back to the memory pool.
 * \param[in] pool memory pool
 * \param[in] p buffer to put back
 * \return Returns 0 if successful.
 */
int uffs_PoolPut(uffs_Pool *pool, void *p)
{
	uffs_PoolEntry *e = (uffs_PoolEntry *)p;

	if (!uffs_Assert(pool != NULL, "pool missing"))
		return -1;

	if (e) {
		e->next = pool->free_list;
		pool->free_list = e;
		return 0;
	}

	return -1;
}

/**
 * \brief Puts a buffer back to the memory pool.
 * This version is locked and should be used when multiple threads access the
 * same memory pool.
 * \param[in] pool memory pool
 * \param[in] p buffer to put back
 * \return Returns 0 if successful.
 */
int uffs_PoolPutLocked(uffs_Pool *pool, void *p)
{
	uffs_PoolEntry *e = (uffs_PoolEntry *)p;

	if (!uffs_Assert(pool != NULL, "pool missing"))
		return -1;

	if (e) {
		uffs_SemWait(pool->sem);
		e->next = pool->free_list;
		pool->free_list = e;
		uffs_SemSignal(pool->sem);
		return 0;
	}

	return -1;
}

/**
 * \brief Gets a buffer by index (offset).
 * This method returns a buffer from the memory pool by index.
 * \param[in] pool memory pool
 * \param[in] index index
 * \return Returns a pointer to the buffer.
 */
void *uffs_PoolGetBufByIndex(uffs_Pool *pool, u32 index)
{
	if (!uffs_Assert(pool != NULL, "pool missing") ||
		!uffs_Assert(index < pool->num_bufs,
				"index(%d) out of range(max %d)", index, pool->num_bufs))
	{
		return NULL;
	}

	return (u8 *) pool->mem + index * pool->buf_size;
}

/**
 * \brief Gets the index (offset) of a buffer.
 * This method returns the index of a buffer from the memory pool.
 * \param[in] pool memory pool
 * \param[in] p buffer to get index from
 * \return Returns the index of the buffer.
 */
u32 uffs_PoolGetIndex(uffs_Pool *pool, void *p)
{
	if (!uffs_Assert(pool != NULL, "pool missing") ||
		!uffs_Assert(p >= (void *) pool->mem &&
			p < (void *) (pool->mem + pool->num_bufs * pool->buf_size),
			"pointer out of range"))
	{
		uffs_Panic();
	}

	return ((u8 *) p - pool->mem) / pool->buf_size;
}

/**
 * \brief Check given buffer in free list
 * \return U_TRUE if it's in free list, U_FALSE if not.
 */
UBOOL uffs_PoolCheckFreeList(uffs_Pool *pool, void *p)
{
	uffs_PoolEntry *e;
	for (e = pool->free_list; e; e = e->next) {
		if ((void *)e == p)
			return U_TRUE;
	}
	return U_FALSE;
}

/**
 * \brief this is more efficient version for small nodes number memory pool (< 32)
 */
static void * FindNextAllocatedInSmallPool(uffs_Pool *pool, void *from)
{
	u32 map = 0;
	uffs_PoolEntry *e;
	u32 i;

	for (e = pool->free_list; e; e = e->next)
		map |= (1 << uffs_PoolGetIndex(pool, e));

	for (i = uffs_PoolGetIndex(pool, from);
			(map & (1 << i)) && i < 32 && i < pool->num_bufs;
				i++);

	return i < 32 && i < pool->num_bufs ?
			uffs_PoolGetBufByIndex(pool, i) : NULL;
}


/**
 * \brief Find next allocated memory block
 *
 * \param[in] pool memory pool
 * \param[in] from search start address, if NULL, from pool->mem
 *
 * \return next allocated memory block, NULL if not found.
 *
 * \note This is NOT efficient, don't do it on a pool with large free nodes !
 */
void * uffs_PoolFindNextAllocated(uffs_Pool *pool, void *from)
{
	uffs_PoolEntry *e = NULL;
	u8 *p = (u8 *)from;

	if (p == NULL)
		p = pool->mem;
	else
		p += pool->buf_size;

	if (pool->num_bufs < 32)
		return FindNextAllocatedInSmallPool(pool, p);

	// work through the free list, stop if not in free list,
	// otherwise move to next entry and search free list again.

	if (pool->free_list) {
		while (uffs_PoolVerify(pool, p)) {
			e = pool->free_list;
			while (e) {
				if (p == (u8 *)e) {
					p += pool->buf_size; // in free list, move to next entry
					break;
				}
				e = e->next;
			}
			if (e == NULL)	// not in free_list, gotcha
				break;
		}	
	}

	return uffs_PoolVerify(pool, p) ? p : NULL ;
}

/**
 * \brief get free memory block count
 */
int uffs_PoolGetFreeCount(uffs_Pool *pool)
{
	int count = 0;
	uffs_PoolEntry *e;

	e = pool->free_list;
	while (e) {
		count++;
		e = e->next;
	}

	return count;
}

/**
 * \brief put all memory block back, return how many memory blocks were put back
 */
int uffs_PoolPutAll(uffs_Pool *pool)
{
	void *p = NULL;
	int count = 0;

	do {
		p = uffs_PoolFindNextAllocated(pool, p);
		if (p) {
			uffs_PoolPut(pool, p);
			count++;
		}
	} while (p);

	return count;
}
