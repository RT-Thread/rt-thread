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
 * \file uffs_badblock.c
 * \brief bad block checking and recovering
 * \author Ricky Zheng, created in 13th Jun, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_ecc.h"
#include "uffs/uffs_badblock.h"
#include <string.h>

#define PFX "bbl : "

void uffs_BadBlockInit(uffs_Device *dev)
{
	dev->bad.block = UFFS_INVALID_BLOCK;
}


/** 
 * \brief process bad block: erase bad block, mark it as 'bad'
 *			and put the node to bad block list.
 * \param[in] dev uffs device
 * \param[in] node bad block tree node
 *			(before the block turn 'bad', it must belong to something ...)
 */
void uffs_BadBlockProcess(uffs_Device *dev, TreeNode *node)
{
	if (HAVE_BADBLOCK(dev)) {
		// mark the bad block
		uffs_FlashMarkBadBlock(dev, dev->bad.block);

		// and put it into bad block list
		if (node != NULL)
			uffs_TreeInsertToBadBlockList(dev, node);

		//clear bad block mark.
		dev->bad.block = UFFS_INVALID_BLOCK;

	}
}

/** 
 * \brief process bad block and put the node in 'suspend' list.
 * \param[in] dev uffs device
 * \param[in] node bad block tree node
 */
void uffs_BadBlockProcessSuspend(uffs_Device *dev, TreeNode *node)
{
	if (HAVE_BADBLOCK(dev)) {
		// mark the bad block
		uffs_FlashMarkBadBlock(dev, dev->bad.block);

		// and put it into bad block list
		if (node != NULL)
			uffs_TreeSuspendAdd(dev, node);

		//clear bad block mark.
		dev->bad.block = UFFS_INVALID_BLOCK;
	}
}

/** 
 * \brief recover bad block
 * \param[in] dev uffs device
 */
void uffs_BadBlockRecover(uffs_Device *dev)
{
	TreeNode *good, *bad;
	uffs_Buf *buf;
	u16 i;
	u16 page;
	uffs_BlockInfo *bc = NULL;
	uffs_Tags *tag;
	uffs_Tags newTag;
	UBOOL succRecov;
	UBOOL goodBlockIsDirty = U_FALSE;
	int ret;
	int region;
	u8 type;
	
	if (dev->bad.block == UFFS_INVALID_BLOCK)
		return;

	// pick up an erased good block
	good = uffs_TreeGetErasedNode(dev);
	if (good == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "no free block to replace bad block!");
		return;
	}

	//recover block
	bc = uffs_BlockInfoGet(dev, dev->bad.block);
	
	if (bc == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "can't get bad block info");
		return;
	}

	succRecov = U_TRUE;
	for (i = 0; i < dev->attr->pages_per_block; i++) {
		page = uffs_FindPageInBlockWithPageId(dev, bc, i);
		if (page == UFFS_INVALID_PAGE) {
			break;  //end of last valid page, normal break
		}
		page = uffs_FindBestPageInBlock(dev, bc, page);
		if (page == UFFS_INVALID_PAGE) {
			// got an invalid page ? it's bad block anyway ...
			uffs_Perror(UFFS_MSG_SERIOUS, "bad block recover (block %d) not finished", bc->block);
			break;
		}
		tag = GET_TAG(bc, page);
		buf = uffs_BufClone(dev, NULL);
		if (buf == NULL) {	
			uffs_Perror(UFFS_MSG_SERIOUS, "Can't clone a new buf!");
			succRecov = U_FALSE;
			break;
		}
		//NOTE: since this is a bad block, we can't guarantee the data is ECC ok,
		//		so just load data even ECC is not OK.
		ret = uffs_LoadPhyDataToBufEccUnCare(dev, buf, bc->block, page);
		if (ret == U_FAIL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "I/O error ?");
			uffs_BufFreeClone(dev, buf);
			succRecov = U_FALSE;
			break;
		}
		buf->data_len = TAG_DATA_LEN(tag);
		if (buf->data_len > dev->com.pg_data_size) {
			uffs_Perror(UFFS_MSG_NOISY, "data length over flow!!!");
			buf->data_len = dev->com.pg_data_size;
		}

		buf->parent = TAG_PARENT(tag);
		buf->serial = TAG_SERIAL(tag);
		buf->type = TAG_TYPE(tag);
		buf->page_id = TAG_PAGE_ID(tag);
		
		// new tag copied from old tag, and increase time-stamp.
		newTag = *tag;
		TAG_BLOCK_TS(&newTag) = uffs_GetNextBlockTimeStamp(TAG_BLOCK_TS(tag));

		ret = uffs_FlashWritePageCombine(dev, good->u.list.block, i, buf, &newTag);

		goodBlockIsDirty = U_TRUE;
		uffs_BufFreeClone(dev, buf);

		if (ret == UFFS_FLASH_IO_ERR) {
			uffs_Perror(UFFS_MSG_NORMAL, "I/O error ?");
			succRecov = U_FALSE;
			break;
		}
	}


	if (succRecov == U_TRUE) {
		// successful recover bad block, so need to mark bad block,
		// and replace with good one

		region = SEARCH_REGION_DIR|SEARCH_REGION_FILE|SEARCH_REGION_DATA;
		bad = uffs_TreeFindNodeByBlock(dev, dev->bad.block, &region);
		if (bad != NULL) {
			switch (region) {
			case SEARCH_REGION_DIR:
				bad->u.dir.block = good->u.list.block;
				type = UFFS_TYPE_DIR;
				break;
			case SEARCH_REGION_FILE:
				bad->u.file.block = good->u.list.block;
				type = UFFS_TYPE_FILE;
				break;
			case SEARCH_REGION_DATA:
				bad->u.data.block = good->u.list.block;
				type = UFFS_TYPE_DATA;
			}
			
			//from now, the 'bad' is actually good block :)))
			uffs_Perror(UFFS_MSG_NOISY,
						"new bad block %d found, and replaced by %d, type %d!",
						dev->bad.block, good->u.list.block, type);
			uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);
			//we reuse the 'good' node as bad block node, and process the bad block.
			good->u.list.block = dev->bad.block;
			uffs_BadBlockProcess(dev, good);
		}
		else {
			uffs_Perror(UFFS_MSG_SERIOUS,
						"can't find the reported bad block(%d) in the tree???",
						dev->bad.block);
			if (goodBlockIsDirty == U_TRUE)
				dev->ops->EraseBlock(dev, good->u.list.block);
			uffs_TreeInsertToErasedListTail(dev, good);
		}
	}
	else {
		if (goodBlockIsDirty == U_TRUE)
			dev->ops->EraseBlock(dev, good->u.list.block);
		uffs_TreeInsertToErasedListTail(dev, good); //put back to erased list
	}

	uffs_BlockInfoPut(dev, bc);

}


/** put a new block to the bad block waiting list */
void uffs_BadBlockAdd(uffs_Device *dev, int block)
{
	if (dev->bad.block == block)
		return;

	if (dev->bad.block != UFFS_INVALID_BLOCK)
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't add more then one bad block !");
	else
		dev->bad.block = block;
}

