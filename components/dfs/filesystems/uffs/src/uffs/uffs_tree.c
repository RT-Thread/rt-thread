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
 * \file uffs_tree.c
 * \brief seting up uffs tree data structure
 * \author Ricky Zheng, created 13th May, 2005
 */

#include "uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_pool.h"
#include "uffs/uffs_flash.h"
#include "uffs/uffs_badblock.h"

#include <string.h>

#define TPOOL(dev) &(dev->mem.tree_pool)

#define PFX "tree: "

static void uffs_InsertToFileEntry(uffs_Device *dev, TreeNode *node);
static void uffs_InsertToDirEntry(uffs_Device *dev, TreeNode *node);
static void uffs_InsertToDataEntry(uffs_Device *dev, TreeNode *node);

static TreeNode * uffs_TreeGetErasedNodeNoCheck(uffs_Device *dev);


struct BlockTypeStatSt {
	int dir;
	int file;
	int data;
};

/** 
 * \brief initialize tree buffers
 * \param[in] dev uffs device
 */
URET uffs_TreeInit(uffs_Device *dev)
{
	int size;
	int num;
	uffs_Pool *pool;
	int i;

	size = sizeof(TreeNode);
	num = dev->par.end - dev->par.start + 1;
	
	pool = &(dev->mem.tree_pool);

	if (dev->mem.tree_nodes_pool_size == 0) {
		if (dev->mem.malloc) {
			dev->mem.tree_nodes_pool_buf = dev->mem.malloc(dev, size * num);
			if (dev->mem.tree_nodes_pool_buf)
				dev->mem.tree_nodes_pool_size = size * num;
		}
	}
	if (size * num > dev->mem.tree_nodes_pool_size) {
		uffs_Perror(UFFS_MSG_DEAD,
					"Tree buffer require %d but only %d available.",
					size * num, dev->mem.tree_nodes_pool_size);
		memset(pool, 0, sizeof(uffs_Pool));
		return U_FAIL;
	}
	uffs_Perror(UFFS_MSG_NOISY, "alloc tree nodes %d bytes.", size * num);
	
	uffs_PoolInit(pool, dev->mem.tree_nodes_pool_buf,
					dev->mem.tree_nodes_pool_size, size, num);

	dev->tree.erased = NULL;
	dev->tree.erased_tail = NULL;
	dev->tree.erased_count = 0;
	dev->tree.bad = NULL;
	dev->tree.bad_count = 0;

	for (i = 0; i < DIR_NODE_ENTRY_LEN; i++) {
		dev->tree.dir_entry[i] = EMPTY_NODE;
	}

	for (i = 0; i < FILE_NODE_ENTRY_LEN; i++) {
		dev->tree.file_entry[i] = EMPTY_NODE;
	}

	for (i = 0; i < DATA_NODE_ENTRY_LEN; i++) {
		dev->tree.data_entry[i] = EMPTY_NODE;
	}

	dev->tree.max_serial = ROOT_DIR_SERIAL;
	
	return U_SUCC;
}
/** 
 * \brief release tree buffers, call this function when unmount
 * \param[in] dev uffs device
 */
URET uffs_TreeRelease(uffs_Device *dev)
{
	uffs_Pool *pool;
	
	pool = &(dev->mem.tree_pool);
	if (pool->mem && dev->mem.free) {
		dev->mem.free(dev, pool->mem);
		pool->mem = NULL;
		dev->mem.tree_nodes_pool_size = 0;
	}
	uffs_PoolRelease(pool);
	memset(pool, 0, sizeof(uffs_Pool));

	return U_SUCC;
}

static u16 _GetBlockFromNode(u8 type, TreeNode *node)
{
	switch (type) {
	case UFFS_TYPE_DIR:
		return node->u.dir.block;
	case UFFS_TYPE_FILE:
		return node->u.file.block;
	case UFFS_TYPE_DATA:
		return node->u.data.block;
	}
	uffs_Perror(UFFS_MSG_SERIOUS, "unkown type, X-block");
	return UFFS_INVALID_BLOCK;
}

#if 0
static u16 _GetParentFromNode(u8 type, TreeNode *node)
{
	switch (type) {
	case UFFS_TYPE_DIR:
		return node->u.dir.parent;
	case UFFS_TYPE_FILE:
		return node->u.file.parent;
	case UFFS_TYPE_DATA:
		return node->u.data.parent;
	}
	uffs_Perror(UFFS_MSG_SERIOUS, "unkown type, X-parent");
	return INVALID_UFFS_SERIAL;
}


static u16 _GetSerialFromNode(u8 type, TreeNode *node)
{
	switch (type) {
	case UFFS_TYPE_DIR:
		return node->u.dir.serial;
	case UFFS_TYPE_FILE:
		return node->u.file.serial;
	case UFFS_TYPE_DATA:
		return node->u.data.serial;
	}
	uffs_Perror(UFFS_MSG_SERIOUS, "unkown type, X-serial");
	return INVALID_UFFS_SERIAL;
}
#endif

/** 
 * insert a TreeNode *node to tree
 * \param[in] dev uffs device
 * \param[in] type type of node
 * \param[in] node node to be insert to
 */
void uffs_InsertNodeToTree(uffs_Device *dev, u8 type, TreeNode *node)
{
	switch (type) {
	case UFFS_TYPE_DIR:
		uffs_InsertToDirEntry(dev, node);
		break;
	case UFFS_TYPE_FILE:
		uffs_InsertToFileEntry(dev, node);
		break;
	case UFFS_TYPE_DATA:
		uffs_InsertToDataEntry(dev, node);
		break;
	default:
		uffs_Perror(UFFS_MSG_SERIOUS,
					"unkown type, can't insert to tree");
		break;
	}
}

/** 
 * find a node from tree
 * \param[in] dev uffs device
 * \param[in] type type of node
 * \param[in] parent parent serial num
 * \param[in] serial serial num
 */
TreeNode * uffs_FindFromTree(uffs_Device *dev,
							 u8 type, u16 parent, u16 serial)
{
	switch (type) {
	case UFFS_TYPE_DIR:
		return uffs_TreeFindDirNode(dev, serial);
	case UFFS_TYPE_FILE:
		return uffs_TreeFindFileNode(dev, serial);
	case UFFS_TYPE_DATA:
		return uffs_TreeFindDataNode(dev, parent, serial);
	}
	uffs_Perror(UFFS_MSG_SERIOUS,
				"unkown type, can't find node");
	return NULL;
}



static URET _BuildValidTreeNode(uffs_Device *dev,
								TreeNode *node,		//!< empty node
								uffs_BlockInfo *bc,
								struct BlockTypeStatSt *st)
{
	uffs_Tags *tag;
	TreeNode *node_alt;
	u16 block, parent, serial, block_alt, block_save;
	uffs_BlockInfo *bc_alt;
	u8 type;
	int page;
	UBOOL needToInsertToTree = U_FALSE;
	uffs_Buf *buf = NULL;
	uffs_FileInfo *info;
	u16 data_sum = 0;

	// check the first page on the block ...
	uffs_BlockInfoLoad(dev, bc, 0);

	tag = GET_TAG(bc, 0);  //get first page's tag

	if (!TAG_IS_DIRTY(tag)) {
		// should never go here ... unless mark dirty page failed ?
		uffs_Perror(UFFS_MSG_NORMAL,
					"First page is clean in a non-erased block ?");
		return U_FAIL;
	}

	if (!TAG_IS_VALID(tag)) {
		//first page is invalid ? should be erased now!
		uffs_Perror(UFFS_MSG_NORMAL,
					"first page in block %d is invalid, will be erased now!",
					bc->block);
		goto process_invalid_block;		
	}

	block = bc->block;
	parent = TAG_PARENT(tag);
	serial = TAG_SERIAL(tag);
	type = TAG_TYPE(tag);

	// check if there is an 'alternative block' 
	// (node which has the same serial number) in tree ?
	node_alt = uffs_FindFromTree(dev, type, parent, serial); 

	if (node_alt != NULL) {
		//find a alternate node ! need to check the timestamp !

		block_alt = _GetBlockFromNode(type, node_alt);

		uffs_Perror(UFFS_MSG_NORMAL,
					"Process unclean block (%d vs %d)", block, block_alt);

		if (block_alt == INVALID_UFFS_SERIAL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "invalid block ?");
			return U_FAIL;
		}
		
		bc_alt = uffs_BlockInfoGet(dev, block_alt);
		if (bc_alt == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "can't get block info ");
			return U_FAIL;
		}
		uffs_BlockInfoLoad(dev, bc_alt, 0);
		if (uffs_IsSrcNewerThanObj (
				TAG_BLOCK_TS(tag),
				TAG_BLOCK_TS(GET_TAG(bc_alt, 0))) == U_TRUE) {

			//the node is newer than node_alt, so keep node_alt, and erase node
			uffs_FlashEraseBlock(dev, block);
			node->u.list.block = block;
			if (HAVE_BADBLOCK(dev))
				uffs_BadBlockProcess(dev, node);
			else
				uffs_TreeInsertToErasedListTail(dev, node);

			uffs_BlockInfoPut(dev, bc_alt);  //put back bc_alt before we return.
			return U_SUCC;
		}
		else {
			//the node is older than node_alt, so keep node, and erase node_alt
			//we use node as erased node to insert to erased list

			block_save = _GetBlockFromNode(type, node_alt);
			uffs_FlashEraseBlock(dev, block_save);
			node->u.list.block = block_save;
			if (HAVE_BADBLOCK(dev))
				uffs_BadBlockProcess(dev, node);
			else
				uffs_TreeInsertToErasedListTail(dev, node);

			//put back bc_alt because we don't need it anymore.
			uffs_BlockInfoPut(dev, bc_alt);
			
			//use node_alt to store new informations in following
			node = node_alt;

			needToInsertToTree = U_FALSE;
		}
	}
	else {
		needToInsertToTree = U_TRUE;
	}

	if (type == UFFS_TYPE_DIR || type == UFFS_TYPE_FILE) {
		buf = uffs_BufClone(dev, NULL);
		if (buf == NULL)
			return U_FAIL;
		uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);
		page = uffs_FindPageInBlockWithPageId(dev, bc, 0);
		if (page == UFFS_INVALID_PAGE) {
			uffs_BufFreeClone(dev, buf);
			uffs_Perror(UFFS_MSG_SERIOUS,
				"Can't find any valid page for page_id=0 ? invalid block !"
				"this might be caused by the tag layout change.\n");
			goto process_invalid_block;
		}
		page = uffs_FindBestPageInBlock(dev, bc, page);
		uffs_FlashReadPage(dev, block, page, buf, U_FALSE);
		info = (uffs_FileInfo *) (buf->data);
		data_sum = uffs_MakeSum16(info->name, info->name_len);
		uffs_BufFreeClone(dev, buf);
	}

	switch (type) {
	case UFFS_TYPE_DIR:
		node->u.dir.block = bc->block;
		node->u.dir.checksum = data_sum;
		node->u.dir.parent = TAG_PARENT(tag);
		node->u.dir.serial = TAG_SERIAL(tag);
		st->dir++;
		break;
	case UFFS_TYPE_FILE:
		node->u.file.block = bc->block;
		node->u.file.checksum = data_sum;
		node->u.file.parent = TAG_PARENT(tag);
		node->u.file.serial = TAG_SERIAL(tag);
		node->u.file.len = uffs_GetBlockFileDataLength(dev, bc, UFFS_TYPE_FILE);  
		st->file++;
		break;
	case UFFS_TYPE_DATA:
		node->u.data.block = bc->block;
		node->u.data.parent = TAG_PARENT(tag);
		node->u.data.serial = TAG_SERIAL(tag);
		node->u.data.len = uffs_GetBlockFileDataLength(dev, bc, UFFS_TYPE_DATA); 
		st->data++;
		break;
	}

	if (needToInsertToTree == U_TRUE) {
		uffs_InsertNodeToTree(dev, type, node);
	}

	return U_SUCC;

process_invalid_block:
	/* erase the invalid block */
	uffs_FlashEraseBlock(dev, bc->block);

	node->u.list.block = bc->block;

	if (HAVE_BADBLOCK(dev))
		uffs_BadBlockProcess(dev, node);
	else
		uffs_TreeInsertToErasedListTail(dev, node);

	return U_SUCC;
}


static URET _ScanAndFixUnCleanPage(uffs_Device *dev, uffs_BlockInfo *bc)
{
	int page;
	uffs_Tags *tag;
	struct uffs_MiniHeaderSt header;

	/* in most case, the valid block contents fewer free page,
		so it's better scan from the last page ... to page 1.
		note: scanning page 0 is not necessary, will check it later.

		The worse case: read (pages_per_block - 1) * (mini header + spares) !
		most case: read one spare.
	*/
	for (page = dev->attr->pages_per_block - 1; page > 0; page--) {
		uffs_BlockInfoLoad(dev, bc, page);
		tag = GET_TAG(bc, page);

		if (TAG_IS_SEALED(tag))
			break;	// tag sealed, no unclean page in this block.

		if (TAG_IS_DIRTY(tag) || TAG_IS_VALID(tag)) {  // tag not sealed but dirty/valid ?
			uffs_Perror(UFFS_MSG_NORMAL,
					"unclean page found, block %d page %d",
					bc->block, page);

			// ok, an unclean page found.
			// This unclean page can be identified by tag.
			// We can leave it as it is, but performing a block recover would be good ?
			// There won't be another unclean page in this block ... stop here.
			break;
		}

		// now we have a clean tag (all 0xFF ?). Need to check mini header to see if it's an unclean page.
		if (uffs_LoadMiniHeader(dev, bc->block, page, &header) == U_FAIL)
			return U_FAIL;

		if (header.status != 0xFF) {
			// page data is dirty? this is an unclean page and we should explicitly mark tag as 'dirty and invalid'.
			// This writing does not violate "no partial program" claim, because we are writing to a clean page spare.
			uffs_Perror(UFFS_MSG_NORMAL,
						"unclean page found, block %d page %d, mark it.",
						bc->block, page);
			uffs_FlashMarkDirtyPage(dev, bc, page);
		}
	}

	return U_SUCC;
}


static URET _BuildTreeStepOne(uffs_Device *dev)
{
	int block_lt;
	uffs_BlockInfo *bc = NULL;
	TreeNode *node;
	struct uffs_TreeSt *tree;
	uffs_Pool *pool;
	struct uffs_MiniHeaderSt header;
	URET ret = U_SUCC;
	struct BlockTypeStatSt st = {0, 0, 0};
	
	tree = &(dev->tree);
	pool = TPOOL(dev);

	tree->bad = NULL;
	tree->bad_count = 0;
	tree->erased = NULL;
	tree->erased_tail = NULL;
	tree->erased_count = 0;

	uffs_Perror(UFFS_MSG_NOISY, "build tree step one");

//	printf("s:%d e:%d\n", dev->par.start, dev->par.end);
	for (block_lt = dev->par.start; block_lt <= dev->par.end; block_lt++) {
		bc = uffs_BlockInfoGet(dev, block_lt);
		if (bc == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "step one:fail to get block info");
			ret = U_FAIL;
			break;
		}
		node = (TreeNode *)uffs_PoolGet(pool);
		if (node == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "insufficient tree node!");
			ret = U_FAIL;
			break;
		}

		// Need to check bad block at first !
		if (uffs_FlashIsBadBlock(dev, block_lt) == U_TRUE) {
			node->u.list.block = block_lt;
			uffs_TreeInsertToBadBlockList(dev, node);
			uffs_Perror(UFFS_MSG_NORMAL, "found bad block %d", block_lt);
		}
		else if (uffs_IsPageErased(dev, bc, 0) == U_TRUE) { //@ read one spare: 0
			// page 0 tag shows it's an erased block, we need to check the mini header status to make sure it is clean.
			if (uffs_LoadMiniHeader(dev, block_lt, 0, &header) == U_FAIL) {
				uffs_Perror(UFFS_MSG_SERIOUS,
							"I/O error when reading mini header !"
							"block %d page %d",
							block_lt, 0);
				ret = U_FAIL;
				break;
			}

			if (header.status != 0xFF) {
				// page 0 tag is clean but page data is dirty ???
				// this block should be erased immediately !
				uffs_FlashEraseBlock(dev, block_lt);
			}
			node->u.list.block = block_lt;
			if (HAVE_BADBLOCK(dev)) {
				uffs_Perror(UFFS_MSG_NORMAL,
							"New bad block (%d) discovered.", block_lt);
				uffs_BadBlockProcess(dev, node);
			}
			else {
				// page 0 is clean does not means all pages in this block are clean,
				// need to check this block later before use it.
				uffs_TreeInsertToErasedListTailEx(dev, node, 1);
			}
		}
		else {
			
			// this block have valid data page(s).

			ret = _ScanAndFixUnCleanPage(dev, bc);
			if (ret == U_FAIL)
				break;

			ret = _BuildValidTreeNode(dev, node, bc, &st);
			if (ret == U_FAIL)
				break;

		}
		uffs_BlockInfoPut(dev, bc);
	} //end of for

	if(ret == U_FAIL) 
		uffs_BlockInfoPut(dev, bc);

	uffs_Perror(UFFS_MSG_NORMAL,
				"DIR %d, FILE %d, DATA %d", st.dir, st.file, st.data);

	return ret;
}

static URET _BuildTreeStepTwo(uffs_Device *dev)
{
	//Randomise the start point of erased block to implement wear levelling
	u32 startCount = 0;
	u32 endPoint;
	TreeNode *node;

	uffs_Perror(UFFS_MSG_NOISY, "build tree step two");

	endPoint = uffs_GetCurDateTime() % (dev->tree.erased_count + 1);
	while (startCount < endPoint) {
		node = uffs_TreeGetErasedNodeNoCheck(dev);
		if (node == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "No erased block ?");
			return U_FAIL;
		}
		uffs_TreeInsertToErasedListTailEx(dev, node, -1);
		startCount++;
	}

	return U_SUCC;
}

TreeNode * uffs_TreeFindFileNode(uffs_Device *dev, u16 serial)
{
	int hash;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);

	hash = serial & FILE_NODE_HASH_MASK;
	x = tree->file_entry[hash];
	while (x != EMPTY_NODE) {
		node = FROM_IDX(x, TPOOL(dev));
		if (node->u.file.serial == serial) {
			return node;
		}
		else {
			x = node->hash_next;
		}
	}
	return NULL;
}

/** add a node into suspend list */
void uffs_TreeSuspendAdd(uffs_Device *dev, TreeNode *node)
{
	node->u.list.next = dev->tree.suspend;
	node->u.list.prev = NULL;

	if (dev->tree.suspend)
		dev->tree.suspend->u.list.prev = node;
	dev->tree.suspend = node;
}

/** search suspend list */
TreeNode * uffs_TreeFindSuspendNode(uffs_Device *dev, u16 serial)
{
	TreeNode *node = dev->tree.suspend;
	while (node) {
		if (node->u.list.u.serial == serial)
			break;
		
		node = node->u.list.next;
	}

	return node;
}

/** remove a node from suspend list */
void uffs_TreeRemoveSuspendNode(uffs_Device *dev, TreeNode *node)
{
	if (node->u.list.prev)
		node->u.list.prev->u.list.next = node->u.list.next;
	if (node->u.list.next)
		node->u.list.next->u.list.prev = node->u.list.prev;
	if (node == dev->tree.suspend)
		dev->tree.suspend = NULL;
}

TreeNode * uffs_TreeFindFileNodeWithParent(uffs_Device *dev, u16 parent)
{
	int hash;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);

	for (hash = 0; hash < FILE_NODE_ENTRY_LEN; hash++) {
		x = tree->file_entry[hash];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.file.parent == parent) {
				return node;
			}
			else {
				x = node->hash_next;
			}
		}
	}

	return NULL;
}

TreeNode * uffs_TreeFindDirNode(uffs_Device *dev, u16 serial)
{
	int hash;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);

	hash = serial & DIR_NODE_HASH_MASK;
	x = tree->dir_entry[hash];
	while (x != EMPTY_NODE) {
		node = FROM_IDX(x, TPOOL(dev));
		if (node->u.dir.serial == serial) {
			return node;
		}
		else {
			x = node->hash_next;
		}
	}
	return NULL;
}

TreeNode * uffs_TreeFindDirNodeWithParent(uffs_Device *dev, u16 parent)
{
	int hash;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);

	for (hash = 0; hash < DIR_NODE_ENTRY_LEN; hash++) {
		x = tree->dir_entry[hash];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.dir.parent == parent) {
				return node;
			}
			else {
				x = node->hash_next;
			}
		}
	}
	
	return NULL;
}

TreeNode * uffs_TreeFindFileNodeByName(uffs_Device *dev,
										const char *name,
										u32 len,
										u16 sum, u16 parent)
{
	int i;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	
	for (i = 0; i < FILE_NODE_ENTRY_LEN; i++) {
		x = tree->file_entry[i];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.file.checksum == sum && node->u.file.parent == parent) {
				//read file name from flash, and compare...
				if (uffs_TreeCompareFileName(dev, name, len, sum, 
												node, UFFS_TYPE_FILE) == U_TRUE) {
					//Got it!
					return node;
				}
			}
			x = node->hash_next;
		}
	}

	return NULL;
}

TreeNode * uffs_TreeFindDataNode(uffs_Device *dev, u16 parent, u16 serial)
{
	int hash;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	u16 x;

	hash = GET_DATA_HASH(parent, serial);
	x = tree->data_entry[hash];
	while(x != EMPTY_NODE) {
		node = FROM_IDX(x, TPOOL(dev));

		if(node->u.data.parent == parent &&
			node->u.data.serial == serial)
				return node;

		x = node->hash_next;
	}

	return NULL;
}

TreeNode * uffs_TreeFindDirNodeByBlock(uffs_Device *dev, u16 block)
{
	int hash;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	u16 x;

	for (hash = 0; hash < DIR_NODE_ENTRY_LEN; hash++) {
		x = tree->dir_entry[hash];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.dir.block == block)
				return node;
			x = node->hash_next;
		}
	}

	return NULL;
}

TreeNode * uffs_TreeFindErasedNodeByBlock(uffs_Device *dev, u16 block)
{
	TreeNode *node;
	node = dev->tree.erased;

	while (node) {
		if (node->u.list.block == block) 
			return node;
		node = node->u.list.next;
	}
		
	return NULL;
}

TreeNode * uffs_TreeFindBadNodeByBlock(uffs_Device *dev, u16 block)
{
	TreeNode *node;
	node = dev->tree.bad;

	while (node) {
		if (node->u.list.block == block) 
			return node;
		node = node->u.list.next;
	}
		
	return NULL;
}

TreeNode * uffs_TreeFindFileNodeByBlock(uffs_Device *dev, u16 block)
{
	int hash;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	u16 x;

	for (hash = 0; hash < FILE_NODE_ENTRY_LEN; hash++) {
		x = tree->file_entry[hash];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.file.block == block)
				return node;
			x = node->hash_next;
		}
	}

	return NULL;
}

TreeNode * uffs_TreeFindDataNodeByBlock(uffs_Device *dev, u16 block)
{
	int hash;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	u16 x;

	for (hash = 0; hash < DATA_NODE_ENTRY_LEN; hash++) {
		x = tree->data_entry[hash];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.data.block == block)
				return node;
			x = node->hash_next;
		}
	}

	return NULL;
}

TreeNode * uffs_TreeFindNodeByBlock(uffs_Device *dev, u16 block, int *region)
{
	TreeNode *node = NULL;

	if (*region & SEARCH_REGION_DATA) {
		node = uffs_TreeFindDataNodeByBlock(dev, block);
		if (node) {
			*region &= SEARCH_REGION_DATA;
			return node;
		}
	}
	if (*region & SEARCH_REGION_FILE) {
		node = uffs_TreeFindFileNodeByBlock(dev, block);
		if (node) {
			*region &= SEARCH_REGION_FILE;
			return node;
		}
	}
	if (*region & SEARCH_REGION_DIR) {
		node = uffs_TreeFindDirNodeByBlock(dev, block);
		if (node) {
			*region &= SEARCH_REGION_DIR;
			return node;
		}
	}
	if (*region & SEARCH_REGION_ERASED) {
		node = uffs_TreeFindErasedNodeByBlock(dev, block);
		if (node) {
			*region &= SEARCH_REGION_ERASED;
			return node;
		}
	}
	if (*region & SEARCH_REGION_BAD) {
		node = uffs_TreeFindBadNodeByBlock(dev, block);
		if (node) {
			*region &= SEARCH_REGION_BAD;
			return node;
		}
	}

	return node;
}

TreeNode * uffs_TreeFindDirNodeByName(uffs_Device *dev,
									  const char *name, u32 len,
									  u16 sum, u16 parent)
{
	int i;
	u16 x;
	TreeNode *node;
	struct uffs_TreeSt *tree = &(dev->tree);
	
	for (i = 0; i < DIR_NODE_ENTRY_LEN; i++) {
		x = tree->dir_entry[i];
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.dir.checksum == sum &&
					node->u.dir.parent == parent) {
				//read file name from flash, and compare...
				if (uffs_TreeCompareFileName(dev, name, len, sum,
											node, UFFS_TYPE_DIR) == U_TRUE) {
					//Got it!
					return node;
				}
			}
			x = node->hash_next;
		}
	}

	return NULL;

}

UBOOL uffs_CompareFileName(const char *src, int src_len, const char *des)
{
	while (src_len-- > 0) {
		if(*src++ != *des++)
			return U_FALSE;
	}

	return U_TRUE;
}

/** compare [name] with tree [node] represented object name by loading
	uffs_FileInfo from storage */
UBOOL uffs_TreeCompareFileName(uffs_Device *dev,
							   const char *name, u32 len, u16 sum,
							   TreeNode *node, int type)
{
	UBOOL matched = U_FALSE;
	uffs_FileInfo *fi;
	uffs_Buf *buf;
	u16 data_sum;

	buf = uffs_BufGetEx(dev, type, node, 0, 0);
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "can't get buf !\n ");
		goto ext;
	}
	fi = (uffs_FileInfo *)(buf->data);
	data_sum = uffs_MakeSum16(fi->name, fi->name_len);

	if (data_sum != sum) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"the obj's sum in storage is different with given sum!");
		goto ext;
	}

	if (fi->name_len == len) {
		if(uffs_CompareFileName(fi->name, fi->name_len, name) == U_TRUE) {
			matched = U_TRUE;
		}
	}
ext:
	if (buf)
		uffs_BufPut(dev, buf);

	return matched;
}


/* calculate file length, etc */
static URET _BuildTreeStepThree(uffs_Device *dev)
{
	int i;
	u16 x;
	TreeNode *work;
	TreeNode *node;
	struct uffs_TreeSt *tree;
	uffs_Pool *pool;
	u16 blockSave;

	TreeNode *cache = NULL;
	u16 cacheSerial = INVALID_UFFS_SERIAL;

	tree = &(dev->tree);
	pool = TPOOL(dev);

	uffs_Perror(UFFS_MSG_NOISY, "build tree step three");

	for (i = 0; i < DATA_NODE_ENTRY_LEN; i++) {
		x = tree->data_entry[i];
		while (x != EMPTY_NODE) {
			work = FROM_IDX(x, pool);
			if (work->u.data.parent == cacheSerial) {
				node = cache;
			}
			else {
				node = uffs_TreeFindFileNode(dev, work->u.data.parent);
				cache = node;
				cacheSerial = work->u.data.parent;
			}
			if (node == NULL) {
				x = work->hash_next;
				//this data block does not belong to any file ?
				//should be erased.
				uffs_Perror(UFFS_MSG_NORMAL,
					"find a orphan data block:%d, "
					"parent:%d, serial:%d, will be erased!",
					work->u.data.block,
					work->u.data.parent, work->u.data.serial);

				uffs_BreakFromEntry(dev, UFFS_TYPE_DATA, work);
				blockSave = work->u.data.block;
				work->u.list.block = blockSave;
				uffs_FlashEraseBlock(dev, blockSave);
				if (HAVE_BADBLOCK(dev))
					uffs_BadBlockProcess(dev, work);
				else
					uffs_TreeInsertToErasedListTail(dev, work);
			}
			else {
				node->u.file.len += work->u.data.len;
				x = work->hash_next;
			}
		}
	}

	return U_SUCC;
}

/** 
 * \brief build tree structure from flash
 * \param[in] dev uffs device
 */
URET uffs_BuildTree(uffs_Device *dev)
{
	URET ret;

	/***** step one: scan all page spares, classify DIR/FILE/DATA nodes,
		check bad blocks/uncompleted(conflicted) blocks as well *****/

	/* if the disk is big and full filled of data this step could be
		the most time consuming .... */

	ret = _BuildTreeStepOne(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "build tree step one fail!");
		return ret;
	}

	/***** step two: randomize the erased blocks, for ware-leveling purpose *****/
	/* this step is very fast :) */
	ret = _BuildTreeStepTwo(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "build tree step two fail!");
		return ret;
	}

	/***** step three: check DATA nodes, find orphan nodes and erase them *****/
	/* if there are a lot of files and disk is fully filled, this step 
		could be very time consuming ... */
	ret = _BuildTreeStepThree(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "build tree step three fail!");
		return ret;
	}
	
	return U_SUCC;
}

/** 
 * find a free file or dir serial NO
 * \param[in] dev uffs device
 * \return if no free serial found, return #INVALID_UFFS_SERIAL
 */
u16 uffs_FindFreeFsnSerial(uffs_Device *dev)
{
	u16 i;
	TreeNode *node;

	//TODO!! Do we need a faster serial number generating method?
	//		 it depends on how often creating files or directories

	for (i = ROOT_DIR_SERIAL + 1; i < MAX_UFFS_FSN; i++) {
		node = uffs_TreeFindDirNode(dev, i);
		if (node == NULL) {
			node = uffs_TreeFindFileNode(dev, i);
			if (node == NULL) {
				node = uffs_TreeFindSuspendNode(dev, i);
				if (node == NULL)
					return i;
			}
		}
	}

	return INVALID_UFFS_SERIAL;
}

static TreeNode * uffs_TreeGetErasedNodeNoCheck(uffs_Device *dev)
{
	TreeNode *node = NULL;
	if (dev->tree.erased) {
		node = dev->tree.erased;
		dev->tree.erased->u.list.prev = NULL;
		dev->tree.erased = dev->tree.erased->u.list.next;
		if(dev->tree.erased == NULL) 
			dev->tree.erased_tail = NULL;
		dev->tree.erased_count--;
	}
	
	return node;
}

TreeNode * uffs_TreeGetErasedNode(uffs_Device *dev)
{
	TreeNode *node = uffs_TreeGetErasedNodeNoCheck(dev);
	u16 block;
	
	if (node && node->u.list.u.need_check) {
		block = node->u.list.block;
		if (uffs_FlashCheckErasedBlock(dev, block) != U_SUCC) {
			// Hmm, this block is not fully erased ? erase it immediately.
			uffs_FlashEraseBlock(dev, block);
			node->u.list.u.need_check = 0;
		}
	}
	return node;
}

static void _InsertToEntry(uffs_Device *dev, u16 *entry,
						   int hash, TreeNode *node)
{
	node->hash_next = entry[hash];
	node->hash_prev = EMPTY_NODE;
	if (entry[hash] != EMPTY_NODE) {
		FROM_IDX(entry[hash], TPOOL(dev))->hash_prev = TO_IDX(node, TPOOL(dev));
	}
	entry[hash] = TO_IDX(node, TPOOL(dev));
}


/** 
 * break the node from entry
 */
void uffs_BreakFromEntry(uffs_Device *dev, u8 type, TreeNode *node)
{
	u16 *entry;
	int hash;
	TreeNode *work;

	switch (type) {
	case UFFS_TYPE_DIR:
		hash = GET_DIR_HASH(node->u.dir.serial);
		entry = &(dev->tree.dir_entry[hash]);
		break;
	case UFFS_TYPE_FILE:
		hash = GET_FILE_HASH(node->u.file.serial);
		entry = &(dev->tree.file_entry[hash]);
		break;
	case UFFS_TYPE_DATA:
		hash = GET_DATA_HASH(node->u.data.parent, node->u.data.serial);
		entry = &(dev->tree.data_entry[hash]);
		break;
	default:
		uffs_Perror(UFFS_MSG_SERIOUS, "unknown type when break...");
		return;
	}

	if (node->hash_prev != EMPTY_NODE) {
		work = FROM_IDX(node->hash_prev, &(dev->mem.tree_pool));
		work->hash_next = node->hash_next;
	}
	if (node->hash_next != EMPTY_NODE) {
		work = FROM_IDX(node->hash_next, &(dev->mem.tree_pool));
		work->hash_prev = node->hash_prev;
	}

	if (*entry == TO_IDX(node, &(dev->mem.tree_pool))) {
		*entry = node->hash_next;
	}
}

static void uffs_InsertToFileEntry(uffs_Device *dev, TreeNode *node)
{
	_InsertToEntry(dev, dev->tree.file_entry,
					GET_FILE_HASH(node->u.file.serial),
					node);
}

static void uffs_InsertToDirEntry(uffs_Device *dev, TreeNode *node)
{
	_InsertToEntry(dev, dev->tree.dir_entry,
					GET_DIR_HASH(node->u.dir.serial),
					node);
}

static void uffs_InsertToDataEntry(uffs_Device *dev, TreeNode *node)
{
	_InsertToEntry(dev, dev->tree.data_entry,
					GET_DATA_HASH(node->u.data.parent, node->u.data.serial),
					node);
}

void uffs_InsertToErasedListHead(uffs_Device *dev, TreeNode *node)
{
	struct uffs_TreeSt *tree;
	tree = &(dev->tree);

	node->u.list.next = tree->erased;
	node->u.list.prev = NULL;

	if (tree->erased) {
		tree->erased->u.list.prev = node;
	}

	tree->erased = node;
	if (node->u.list.next == tree->erased_tail) {
		tree->erased_tail = node;
	}
	tree->erased_count++;
}

/**
 * insert node to erased list.
 * \param need_check: 0 - no need to check later
 *                    1 - need to check later
 *                  < 0 - keep 'node->u.list.need_check' value
 */
void uffs_TreeInsertToErasedListTailEx(uffs_Device *dev, TreeNode *node, int need_check)
{
	struct uffs_TreeSt *tree;
	tree = &(dev->tree);
	
	if (need_check >= 0)
		node->u.list.u.need_check = need_check;
	
	node->u.list.next = NULL;
	node->u.list.prev = tree->erased_tail;
	if (tree->erased_tail) {
		tree->erased_tail->u.list.next = node;
	}

	tree->erased_tail = node;
	if(tree->erased == NULL) {
		tree->erased = node;
	}
	tree->erased_count++;
}

void uffs_TreeInsertToErasedListTail(uffs_Device *dev, TreeNode *node)
{
	// this function is called after the block is erased, so don't need to check.
	uffs_TreeInsertToErasedListTailEx(dev, node, 0);
}

void uffs_TreeInsertToBadBlockList(uffs_Device *dev, TreeNode *node)
{
	struct uffs_TreeSt *tree;

	tree = &(dev->tree);
	node->u.list.prev = NULL;
	node->u.list.next = tree->bad;

	if (tree->bad) {
		tree->bad->u.list.prev = node;
	}

	tree->bad = node;
	tree->bad_count++;
}

/** 
 * set tree node block value
 */
void uffs_TreeSetNodeBlock(u8 type, TreeNode *node, u16 block)
{
	switch (type) {
	case UFFS_TYPE_FILE:
		node->u.file.block = block;
		break;
	case UFFS_TYPE_DIR:
		node->u.dir.block = block;
		break;
	case UFFS_TYPE_DATA:
		node->u.data.block = block;
		break;
	}
}

