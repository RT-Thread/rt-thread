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
 * \file uffs_blockinfo.c
 * \brief block information cache system manipulations
 * \author Ricky Zheng, created 10th May, 2005
 */

#include "uffs_config.h"
#include "uffs/uffs_blockinfo.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_os.h"

#include <string.h>

#define PFX "bc  : "

#define UFFS_CLONE_BLOCK_INFO_NEXT ((uffs_BlockInfo *)(-2))

/**
 * \brief before block info cache is enable,
 *			this function should be called to initialize it
 *
 * \param[in] dev uffs device
 * \param[in] maxCachedBlocks maximum cache buffers to be allocated
 * \return result of initialization
 *		\retval U_SUCC successful
 *		\retval U_FAIL failed
 */
URET uffs_BlockInfoInitCache(uffs_Device *dev, int maxCachedBlocks)
{
	uffs_BlockInfo * blockInfos = NULL;
	uffs_PageSpare * pageSpares = NULL;
	void * buf = NULL;
	uffs_BlockInfo *work = NULL;
	int size, i, j;

	if (dev->bc.head != NULL) {
		uffs_Perror(UFFS_MSG_NOISY,
					"block info cache has been inited already, "
					"now release it first.");
		uffs_BlockInfoReleaseCache(dev);
	}

	size = ( 
			sizeof(uffs_BlockInfo) +
			sizeof(uffs_PageSpare) * dev->attr->pages_per_block
			) * maxCachedBlocks;

	if (dev->mem.blockinfo_pool_size == 0) {
		if (dev->mem.malloc) {
			dev->mem.blockinfo_pool_buf = dev->mem.malloc(dev, size);
			if (dev->mem.blockinfo_pool_buf)
				dev->mem.blockinfo_pool_size = size;
		}
	}
	if (size > dev->mem.blockinfo_pool_size) {
		uffs_Perror(UFFS_MSG_DEAD,
					"Block cache buffer require %d but only %d available.",
					size, dev->mem.blockinfo_pool_size);
		return U_FAIL;
	}

	uffs_Perror(UFFS_MSG_NOISY, "alloc info cache %d bytes.", size);

	buf = dev->mem.blockinfo_pool_buf;

	memset(buf, 0, size);

	dev->bc.mem_pool = buf;

	size = 0;
	blockInfos = (uffs_BlockInfo *)buf;
	size += sizeof(uffs_BlockInfo) * maxCachedBlocks;

	pageSpares = (uffs_PageSpare *)((char *)buf + size);

	//initialize block info
	work = &(blockInfos[0]);
	dev->bc.head = work;
	work->ref_count = 0;
	work->prev = NULL;
	work->next = &(blockInfos[1]);
	work->block = UFFS_INVALID_BLOCK;

	for (i = 0; i < maxCachedBlocks - 2; i++) {
		work = &(blockInfos[i+1]);
		work->prev = &(blockInfos[i]);
		work->next = &(blockInfos[i+2]);
		work->ref_count = 0;
		work->block = UFFS_INVALID_BLOCK;
	}
	//the last node
	work = &(blockInfos[i+1]);
	work->prev = &(blockInfos[i]);
	work->next = NULL;
	work->block = UFFS_INVALID_BLOCK;
	work->ref_count = 0;
	dev->bc.tail = work;

	//initialize spares
	work = dev->bc.head;
	for (i = 0; i < maxCachedBlocks; i++) {
		work->spares = &(pageSpares[i*dev->attr->pages_per_block]);
		for (j = 0; j < dev->attr->pages_per_block; j++) {
			work->spares[j].expired = 1;
		}
		work->expired_count = dev->attr->pages_per_block;
		work = work->next;
	}
	return U_SUCC;
}

/**
 * \brief release all allocated memory of block info cache, 
 *			this function should be called when unmount file system
 * \param[in] dev uffs device
 */
URET uffs_BlockInfoReleaseCache(uffs_Device *dev)
{
	uffs_BlockInfo *work;

	if (dev->bc.head) {
		for (work = dev->bc.head; work != NULL; work = work->next) {
			if (work->ref_count != 0) {
				uffs_Perror(UFFS_MSG_SERIOUS,
					"There have refed block info cache, release cache fail.");
				return U_FAIL;
			}
		}
		if (dev->mem.free) {
			dev->mem.free(dev, dev->bc.mem_pool);
			dev->mem.blockinfo_pool_size = 0;
		}
	}

	dev->bc.head = dev->bc.tail = NULL;
	dev->bc.mem_pool = NULL;

	return U_SUCC;
}

static void _BreakBcFromList(uffs_Device *dev, uffs_BlockInfo *bc)
{
	if (bc->prev)
		bc->prev->next = bc->next;

	if (bc->next)
		bc->next->prev = bc->prev;

	if (dev->bc.head == bc)
		dev->bc.head = bc->next;

	if (dev->bc.tail == bc)
		dev->bc.tail = bc->prev;
}

static void _InsertToBcListTail(uffs_Device *dev, uffs_BlockInfo *bc)
{
	bc->next = NULL;
	bc->prev = dev->bc.tail;
	bc->prev->next = bc;
	dev->bc.tail = bc;
}

static void _MoveBcToTail(uffs_Device *dev, uffs_BlockInfo *bc)
{
	_BreakBcFromList(dev, bc);
	_InsertToBcListTail(dev, bc);
}


/** 
 * \brief load page spare data to given block info structure
 *			with given page number
 * \param[in] dev uffs device
 * \param[in] work given block info to be filled with
 * \param[in] page given page number to be read from,
 *			  if #UFFS_ALL_PAGES is presented, it will read
 *			  all pages, otherwise it will read only one given page.
 * \return load result
 * \retval U_SUCC successful
 * \retval U_FAIL fail to load
 * \note work->block must be set before load block info
 */
URET uffs_BlockInfoLoad(uffs_Device *dev, uffs_BlockInfo *work, int page)
{
	int i, ret;
	uffs_PageSpare *spare;

	if (page == UFFS_ALL_PAGES) {
		for (i = 0; i < dev->attr->pages_per_block; i++) {
			spare = &(work->spares[i]);
			if (spare->expired == 0)
				continue;
			
			ret = uffs_FlashReadPageTag(dev, work->block, i,
											&(spare->tag));
			if (UFFS_FLASH_HAVE_ERR(ret)) {
				uffs_Perror(UFFS_MSG_SERIOUS,
							"load block %d page %d spare fail.",
							work->block, i);
				return U_FAIL;
			}
			spare->expired = 0;
			work->expired_count--;
		}
	}
	else {
		if (page < 0 || page >= dev->attr->pages_per_block) {
			uffs_Perror(UFFS_MSG_SERIOUS, "page out of range !");
			return U_FAIL;
		}
		spare = &(work->spares[page]);
		if (spare->expired != 0) {
			ret = uffs_FlashReadPageTag(dev, work->block, page,
											&(spare->tag));
			if (UFFS_FLASH_HAVE_ERR(ret)) {
				uffs_Perror(UFFS_MSG_SERIOUS,
							"load block %d page %d spare fail.",
							work->block, page);
				return U_FAIL;
			}
			spare->expired = 0;
			work->expired_count--;
		}
	}
	return U_SUCC;
}


/** 
 * \brief find a block cache with given block number
 * \param[in] dev uffs device
 * \param[in] block block number
 * \return found block cache
 * \retval NULL cache not found
 * \retval non-NULL found cache pointer
 */
uffs_BlockInfo * uffs_BlockInfoFindInCache(uffs_Device *dev, int block)
{
	uffs_BlockInfo *work;
	
	//search cached block
	for (work = dev->bc.head; work != NULL; work = work->next) {
		if (work->block == block) {
			work->ref_count++;
			return work;
		}
	}
	return NULL;
}


/** 
 * \brief Find a cached block in cache pool,
 *			if the cached block exist then return the pointer,
 *			if the block does not cached already, find a non-used cache.
 *			if all of cached are used out, return NULL.
 * \param[in] dev uffs device
 * \param[in] block block number to be found
 * \return found block cache buffer
 * \retval NULL caches used out
 * \retval non-NULL buffer pointer of given block
 */
uffs_BlockInfo * uffs_BlockInfoGet(uffs_Device *dev, int block)
{
	uffs_BlockInfo *work;
	int i;

	//search cached block
	if ((work = uffs_BlockInfoFindInCache(dev, block)) != NULL) {
		_MoveBcToTail(dev, work);
		return work;
	}

	//can't find block from cache, need to find a free(unlocked) cache
	for (work = dev->bc.head; work != NULL; work = work->next) {
		if(work->ref_count == 0) break;
	}
	if (work == NULL) {
		//caches used out !
		uffs_Perror(UFFS_MSG_SERIOUS,  "insufficient block info cache");
		return NULL;
	}

	work->block = block;
	work->expired_count = dev->attr->pages_per_block;
	for (i = 0; i < dev->attr->pages_per_block; i++) {
		work->spares[i].expired = 1;

		// TODO: init tag
	}

	work->ref_count = 1;

	_MoveBcToTail(dev, work);

	return work;
}

/** 
 * \brief put block info buffer back to pool,
 *			 should be called with #uffs_BlockInfoGet in pairs.
 * \param[in] dev uffs device
 * \param[in] p pointer of block info buffer
 */
void uffs_BlockInfoPut(uffs_Device *dev, uffs_BlockInfo *p)
{
	dev = dev;
	if (p)
	{
		if (p->ref_count == 0) {
			uffs_Perror(UFFS_MSG_SERIOUS,
				"Put an unused block info cache back ?");
		}
		else {
			p->ref_count--;
		}
	}
}


/** 
 * \brief make the given pages expired in given block info buffer
 * \param[in] dev uffs device
 * \param[in] p pointer of block info buffer
 * \param[in] page given page number.
 *	if #UFFS_ALL_PAGES presented, all pages in the block should be made expired.
 */
void uffs_BlockInfoExpire(uffs_Device *dev, uffs_BlockInfo *p, int page)
{
	int i;
	uffs_PageSpare *spare;

	if (page == UFFS_ALL_PAGES) {
		for (i = 0; i < dev->attr->pages_per_block; i++) {
			spare = &(p->spares[i]);
			if (spare->expired == 0) {
				spare->expired = 1;
				p->expired_count++;
			}
		}
	}
	else {
		if (page >= 0 && page < dev->attr->pages_per_block) {
			spare = &(p->spares[page]);
			if (spare->expired == 0) {
				spare->expired = 1;
				p->expired_count++;
			}
		}
	}
}

/** 
 * Is all blcok info cache free (not referenced) ?
 */
UBOOL uffs_BlockInfoIsAllFree(uffs_Device *dev)
{
	uffs_BlockInfo *work;

	work = dev->bc.head;
	while (work) {
		if (work->ref_count != 0)
			return U_FALSE;
		work = work->next;
	}

	return U_TRUE;
}

void uffs_BlockInfoExpireAll(uffs_Device *dev)
{
	uffs_BlockInfo *bc;

	bc = dev->bc.head;
	while (bc) {
		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);
		bc = bc->next;
	}
	return;
}
