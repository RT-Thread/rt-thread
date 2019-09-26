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
 * \file uffs_buf.c
 * \brief uffs page buffers manipulations
 * \author Ricky Zheng
 * \note Created in 11th May, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_types.h"
#include "uffs/uffs_buf.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_pool.h"
#include "uffs/uffs_ecc.h"
#include "uffs/uffs_badblock.h"
#include <string.h>

#define PFX "pbuf: "


URET _BufFlush(struct uffs_DeviceSt *dev, UBOOL force_block_recover, int slot);


/**
 * \brief inspect (print) uffs page buffers.
 * \param[in] dev uffs device to be inspected.
 */
void uffs_BufInspect(uffs_Device *dev)
{
	struct uffs_PageBufDescSt *pb = &dev->buf;
	uffs_Buf *buf;

	uffs_PerrorRaw(UFFS_MSG_NORMAL,
					"------------- page buffer inspect ---------" TENDSTR);
	uffs_PerrorRaw(UFFS_MSG_NORMAL, "all buffers: " TENDSTR);
	for (buf = pb->head; buf; buf = buf->next) {
		if (buf->mark != 0) {
			uffs_PerrorRaw(UFFS_MSG_NORMAL,
				"\tF:%04x S:%04x P:%02d R:%02d D:%03d M:%c EM:%d" TENDSTR,
				buf->parent, buf->serial,
				buf->page_id, buf->ref_count,
				buf->data_len, buf->mark == UFFS_BUF_VALID ? 'V' : 'D',
				buf->ext_mark);
		}
	}
	uffs_PerrorRaw(UFFS_MSG_NORMAL,
					"--------------------------------------------"  TENDSTR);
}

/**
 * \brief initialize page buffers for device
 * in UFFS, each device has one buffer pool
 * \param[in] dev uffs device
 * \param[in] buf_max maximum buffer number, normally use #MAX_PAGE_BUFFERS
 * \param[in] dirty_buf_max maximum dirty buffer allowed,
 *				if the dirty buffer over this number,
 *				than need to be flush to flash
 */
URET uffs_BufInit(uffs_Device *dev, int buf_max, int dirty_buf_max)
{
	void *pool;
	u8 *data;
	uffs_Buf *buf;
	int size;
	int i, slot;

	if (!dev)
		return U_FAIL;

	//init device common parameters, which are needed by page buffers
	dev->com.pg_size = dev->attr->page_data_size;  // we use the whole page.
	dev->com.header_size = sizeof(struct uffs_MiniHeaderSt); // mini header
	dev->com.pg_data_size = dev->com.pg_size - dev->com.header_size;

	if (dev->buf.pool != NULL) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"buf.pool is not NULL, buf already inited ?");
		return U_FAIL;
	}
	
	size = (sizeof(uffs_Buf) + dev->com.pg_size) * buf_max;
	if (dev->mem.pagebuf_pool_size == 0) {
		if (dev->mem.malloc) {
			dev->mem.pagebuf_pool_buf = dev->mem.malloc(dev, size);
			if (dev->mem.pagebuf_pool_buf)
				dev->mem.pagebuf_pool_size = size;
		}
	}
	if (size > dev->mem.pagebuf_pool_size) {
		uffs_Perror(UFFS_MSG_DEAD,
					"page buffers require %d but only %d available.",
				size, dev->mem.pagebuf_pool_size);
		return U_FAIL;
	}
	pool = dev->mem.pagebuf_pool_buf;

	uffs_Perror(UFFS_MSG_NOISY, "alloc %d bytes.", size);
	dev->buf.pool = pool;

	for (i = 0; i < buf_max; i++) {
		buf = (uffs_Buf *)((u8 *)pool + (sizeof(uffs_Buf) * i));
		memset(buf, 0, sizeof(uffs_Buf));
		data = (u8 *)pool + (sizeof(uffs_Buf) * buf_max) + (dev->com.pg_size * i);
		buf->header = data;
		buf->data = data + dev->com.header_size;
		buf->mark = UFFS_BUF_EMPTY;
		memset(buf->header, 0, dev->com.pg_size);
		if (i == 0) {
			buf->prev = NULL;
			dev->buf.head = buf;
		}
		else {
			buf->prev = (uffs_Buf *)((u8 *)buf - sizeof(uffs_Buf));
		}

		if (i == (buf_max - 1)) {
			buf->next = NULL;
			dev->buf.tail = buf;
		}
		else {
			buf->next = (uffs_Buf *)((u8 *)buf + sizeof(uffs_Buf));
		}
	}

	dev->buf.buf_max = buf_max;
	dev->buf.dirty_buf_max = (dirty_buf_max > dev->attr->pages_per_block ?
								dev->attr->pages_per_block : dirty_buf_max);

	for (slot = 0; slot < dev->cfg.dirty_groups; slot++) {
		dev->buf.dirtyGroup[slot].dirty = NULL;
		dev->buf.dirtyGroup[slot].count = 0;
	}
	return U_SUCC;
}

/**
 * \brief flush all buffers
 */
URET uffs_BufFlushAll(struct uffs_DeviceSt *dev)
{
	int slot;
	for (slot = 0; slot < dev->cfg.dirty_groups; slot++) {
		if(_BufFlush(dev, FALSE, slot) != U_SUCC) {
			uffs_Perror(UFFS_MSG_NORMAL,
						"fail to flush buffer(slot %d)", slot);
			return U_FAIL;
		}
	}
	return U_SUCC;
}

/** 
 * \brief release all page buffer, this function should be called 
			when unmounting a uffs device
 * \param[in] dev uffs device
 * \note if there are page buffers in used, it may cause fail to release
 */
URET uffs_BufReleaseAll(uffs_Device *dev)
{
	uffs_Buf *p;

	if (!dev)
		return U_FAIL;

	//now release all buffer
	p = dev->buf.head;
	while (p) {
		if (p->ref_count != 0) {
			uffs_Perror(UFFS_MSG_NORMAL, PFX
						"can't release buffers, parent:%d, serial:%d, \
						page_id:%d still in used.\n",
						p->parent, p->serial, p->page_id);
			return U_FAIL;
		}
		p = p->next;
	}

	if (uffs_BufFlushAll(dev) != U_SUCC) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"can't release buf, fail to flush buffer");
		return U_FAIL;
	}

	if (dev->mem.free) {
		dev->mem.free(dev, dev->buf.pool);
		dev->mem.pagebuf_pool_size = 0;
	}

	dev->buf.pool = NULL;
	dev->buf.head = dev->buf.tail = NULL;

	return U_SUCC;
}


static void _BreakFromBufList(uffs_Device *dev, uffs_Buf *buf)
{
	if(buf->next)
		buf->next->prev = buf->prev;

	if(buf->prev)
		buf->prev->next = buf->next;

	if(dev->buf.head == buf)
		dev->buf.head = buf->next;

	if(dev->buf.tail == buf)
		dev->buf.tail = buf->prev;

}

static void _LinkToBufListHead(uffs_Device *dev, uffs_Buf *buf)
{
	if (buf == dev->buf.head)
		return;

	buf->prev = NULL;
	buf->next = dev->buf.head;

	if (dev->buf.head)
		dev->buf.head->prev = buf;

	if (dev->buf.tail == NULL)
		dev->buf.tail = buf;

	dev->buf.head = buf;
}

static void _LinkToBufListTail(uffs_Device *dev, uffs_Buf *buf)
{
	if (dev->buf.tail == buf)
		return;

	buf->prev = dev->buf.tail;
	buf->next = NULL;

	if (dev->buf.tail)
		dev->buf.tail->next = buf;

	if (dev->buf.head == NULL)
		dev->buf.head = buf;

	dev->buf.tail = buf;
}

//move a node which linked in the list to the head of list
static void _MoveNodeToHead(uffs_Device *dev, uffs_Buf *p)
{
	if (p == dev->buf.head)
		return;

	//break from list
	_BreakFromBufList(dev, p);

	//link to head
	_LinkToBufListHead(dev, p);
}

// check if the buf is already in dirty list
static UBOOL _IsBufInInDirtyList(uffs_Device *dev, int slot, uffs_Buf *buf)
{
	uffs_Buf *work;
	work = dev->buf.dirtyGroup[slot].dirty;
	while (work) {
		if (work == buf) 
			return U_TRUE;
		work = work->next_dirty;
	}

	return U_FALSE;
}

static void _LinkToDirtyList(uffs_Device *dev, int slot, uffs_Buf *buf)
{

	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"Try to insert a NULL node into dirty list ?");
		return;
	}

	buf->mark = UFFS_BUF_DIRTY;
	buf->prev_dirty = NULL;
	buf->next_dirty = dev->buf.dirtyGroup[slot].dirty;

	if (dev->buf.dirtyGroup[slot].dirty) 
		dev->buf.dirtyGroup[slot].dirty->prev_dirty = buf;

	dev->buf.dirtyGroup[slot].dirty = buf;
	dev->buf.dirtyGroup[slot].count++;
}

static int CountFreeBuf(uffs_Device *dev)
{
	int count = 0;

	uffs_Buf *buf = dev->buf.head;

	while (buf) {

		if (buf->ref_count == 0 && 
			buf->mark != UFFS_BUF_DIRTY)
			count++;

		buf = buf->next;
	}

	return count;
}

static uffs_Buf * _FindFreeBufEx(uffs_Device *dev, int clone)
{
	uffs_Buf *buf;

	if (!clone && CountFreeBuf(dev) <= CLONE_BUFFERS_THRESHOLD)
		return NULL;

#if 0
	buf = dev->buf.head;
	while (buf) {

		if (buf->ref_count == 0 && 
			buf->mark != UFFS_BUF_DIRTY)
			return buf;

		buf = buf->next;
	}
#else
	buf = dev->buf.tail;
	while (buf) {

		if(buf->ref_count == 0 &&
			buf->mark != UFFS_BUF_DIRTY) 
			return buf;

		buf = buf->prev;
	}
#endif

	return buf;
}

static uffs_Buf * _FindFreeBuf(uffs_Device *dev)
{
	return _FindFreeBufEx(dev, 0);
}


/** 
 * load psychical page data into buf and do ecc check 
 * \param[in] dev uffs device
 * \param[in] buf buf to be load in
 * \param[in] block psychical block number
 * \param[in] page psychical page number
 * \return return U_SUCC if no error,
 *	 return U_FAIL if I/O error or ecc check fail
 */
URET uffs_BufLoadPhyData(uffs_Device *dev, uffs_Buf *buf, u32 block, u32 page)
{
	int ret;

	ret = uffs_FlashReadPage(dev, block, page, buf, U_FALSE);

	if (UFFS_FLASH_HAVE_ERR(ret)) {
		buf->mark = UFFS_BUF_EMPTY;
		return U_FAIL;
	}
	else {
		buf->mark = UFFS_BUF_VALID;
		return U_SUCC;
	}
}

/** 
 * \brief load psychical page data into buf and ignore ECC result
 *
 * \param[in] dev uffs device
 * \param[in] buf buf to be load in
 * \param[in] block psychical block number
 * \param[in] page psychical page number
 *
 * \return return U_SUCC if no error, return U_FAIL if I/O error
 * \note this function should be only used when doing bad block recover.
 */
URET uffs_LoadPhyDataToBufEccUnCare(uffs_Device *dev,
									uffs_Buf *buf, u32 block, u32 page)
{
	int ret;

	ret = uffs_FlashReadPage(dev, block, page, buf, U_TRUE);

	if (ret == UFFS_FLASH_IO_ERR) {
		buf->mark = UFFS_BUF_EMPTY;
		return U_FAIL;
	}
	else {
		buf->mark = UFFS_BUF_VALID;
		return U_SUCC;
	}
}

/** 
 * find a buffer in the pool
 * \param[in] dev uffs device
 * \param[in] start buf to search from
 * \param[in] parent parent serial num
 * \param[in] serial serial num
 * \param[in] page_id page_id (if page_id == UFFS_ALL_PAGES then any page would match)
 * \return return found buffer, return NULL if buffer not found
 */
uffs_Buf * uffs_BufFindFrom(uffs_Device *dev, uffs_Buf *start,
						u16 parent, u16 serial, u16 page_id)
{
	uffs_Buf *p = start;

	while (p) {
		if(	p->parent == parent &&
			p->serial == serial &&
			(page_id == UFFS_ALL_PAGES || p->page_id == page_id) &&
			p->mark != UFFS_BUF_EMPTY) 
		{
			//they have match one
			return p;
		}
		p = p->next;
	}

	return NULL; //buffer not found
}

/** 
 * find a buffer in the pool
 * \param[in] dev uffs device
 * \param[in] parent parent serial num
 * \param[in] serial serial num
 * \param[in] page_id page_id (if page_id == UFFS_ALL_PAGES then any page would match)
 * \return return found buffer, return NULL if buffer not found
 */
uffs_Buf * uffs_BufFind(uffs_Device *dev,
						u16 parent, u16 serial, u16 page_id)
{
	uffs_Buf *p = dev->buf.head;

	return uffs_BufFindFrom(dev, p, parent, serial, page_id);
}


static uffs_Buf * _FindBufInDirtyList(uffs_Buf *dirty, u16 page_id)
{
	while(dirty) {
		if (dirty->page_id == page_id) 
			return dirty;
		dirty = dirty->next_dirty;
	}
	return NULL;
}

static URET _BreakFromDirty(uffs_Device *dev, uffs_Buf *dirtyBuf)
{
	int slot = -1;

	if (dirtyBuf->mark != UFFS_BUF_DIRTY) {
		uffs_Perror(UFFS_MSG_NORMAL,
						"try to break a non-dirty buf from dirty list ?");
		return U_FAIL;
	}

	slot = uffs_BufFindGroupSlot(dev, dirtyBuf->parent, dirtyBuf->serial);
	if (slot < 0) {
		uffs_Perror(UFFS_MSG_NORMAL, "no dirty list exit ?");
		return U_FAIL;
	}

	// break from the link
	if (dirtyBuf->next_dirty) {
		dirtyBuf->next_dirty->prev_dirty = dirtyBuf->prev_dirty;
	}

	if (dirtyBuf->prev_dirty) {
		dirtyBuf->prev_dirty->next_dirty = dirtyBuf->next_dirty;
	}

	// check if it's the link head ...
	if (dev->buf.dirtyGroup[slot].dirty == dirtyBuf) {
		dev->buf.dirtyGroup[slot].dirty = dirtyBuf->next_dirty;
	}

	dirtyBuf->next_dirty = dirtyBuf->prev_dirty = NULL; // clear dirty link

	dev->buf.dirtyGroup[slot].count--;

	return U_SUCC;
}

static u16 _GetDirOrFileNameSum(uffs_Device *dev, uffs_Buf *buf)
{
	u16 data_sum = 0; //default: 0
	uffs_FileInfo *fi;
	
	dev = dev;
	//FIXME: We use the same schema for both dir and file.
	if (buf->type == UFFS_TYPE_FILE || buf->type == UFFS_TYPE_DIR) {
		if (buf->page_id == 0) {
			fi = (uffs_FileInfo *)(buf->data);
			data_sum = uffs_MakeSum16(fi->name, fi->name_len);
		}
	}

	return data_sum;
}


static URET _CheckDirtyList(uffs_Buf *dirty)
{
	u16 parent;
	u16 serial;

	if (dirty == NULL) {
		return U_SUCC;
	}

	parent = dirty->parent;
	serial = dirty->serial;
	dirty = dirty->next_dirty;

	while (dirty) {
		if (parent != dirty->parent ||
			serial != dirty->serial) {
			uffs_Perror(UFFS_MSG_SERIOUS,
					"parent or serial in dirty pages buffer are not the same ?");
			return U_FAIL;
		}
		if (dirty->mark != UFFS_BUF_DIRTY) {
			uffs_Perror(UFFS_MSG_SERIOUS,
					"non-dirty page buffer in dirty buffer list ?");
			return U_FAIL;
		}
		dirty = dirty->next_dirty;
	}
	return U_SUCC;
}

/** find a page in dirty list, which has minimum page_id */
uffs_Buf * _FindMinimunPageIdFromDirtyList(uffs_Buf *dirtyList)
{
	uffs_Buf * work = dirtyList;
	uffs_Buf * buf = dirtyList;

	if (buf) {
		work = work->next_dirty;
		while (work) {
			if (work->page_id < buf->page_id)
				buf = work;
			work = work->next_dirty;
		}

		uffs_Assert(buf->mark == UFFS_BUF_DIRTY, 
					"buf (serial = %d, parent = %d, page_id = %d, type = %d) in dirty list but mark is 0x%x ?",
					buf->serial, buf->parent, buf->page_id, buf->type, buf->mark);
	}

	return buf;
}


/** 
 * \brief flush buffer with block recover
 *
 * Scenario: 
 *	1. get a free (erased) block --> newNode <br>
 *	2. copy from old block ---> oldNode, or copy from dirty list, <br>
 *		sorted by page_id, to new block. Skips the invalid pages when copy pages.<br>
 *	3. erased old block. set new info to oldNode, set newNode->block = old block,<br>
 *		and put newNode to erased list.<br>
 *	\note IT'S IMPORTANT TO KEEP OLD NODE IN THE LIST,
 *		 so you don't need to update the obj->node :-)
 */
static URET uffs_BufFlush_Exist_With_BlockCover(
			uffs_Device *dev,
			int slot,			//!< dirty group slot
			TreeNode *node,		//!< old data node on tree
			uffs_BlockInfo *bc	//!< old data block info
			)
{
	u16 i;
	u8 type, timeStamp;
	u16 page, parent, serial;
	uffs_Buf *buf;
	TreeNode *newNode;
	uffs_BlockInfo *newBc;
	uffs_Tags *tag, *oldTag;
	int x;
	u16 newBlock;
	UBOOL succRecover;			//U_TRUE: recover successful, erase old block,
								//U_FALSE: fail to recover, erase new block
	UBOOL flash_op_err;
	u16 data_sum = 0xFFFF;

	UBOOL useCloneBuf;

	type = dev->buf.dirtyGroup[slot].dirty->type;
	parent = dev->buf.dirtyGroup[slot].dirty->parent;
	serial = dev->buf.dirtyGroup[slot].dirty->serial;

retry:
	uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);

	flash_op_err = UFFS_FLASH_NO_ERR;
	succRecover = U_FALSE;

	newNode = uffs_TreeGetErasedNode(dev);
	if (newNode == NULL) {
		uffs_Perror(UFFS_MSG_NOISY, "no enough erased block!");
		goto ext;
	}
	newBlock = newNode->u.list.block;
	newBc = uffs_BlockInfoGet(dev, newBlock);
	if (newBc == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "get block info fail!");
		uffs_InsertToErasedListHead(dev, newNode);  //put node back to erased list
											//because it doesn't use, so put to head
		goto ext;
	}

	//uffs_Perror(UFFS_MSG_NOISY, "flush buffer with block cover to %d", newBlock);

#if 0
	// this assert seems not necessary ...
	if (!uffs_Assert(newBc->expired_count == dev->attr->pages_per_block,
			"We have block cache for erased block ? expired_count = %d, block = %d\n",
			newBc->expired_count, newBc->block)) {
		uffs_BlockInfoExpire(dev, newBc, UFFS_ALL_PAGES);
	}
#endif

	uffs_BlockInfoLoad(dev, newBc, UFFS_ALL_PAGES);
	timeStamp = uffs_GetNextBlockTimeStamp(uffs_GetBlockTimeStamp(dev, bc));

//	uffs_Perror(UFFS_MSG_NOISY, "Flush buffers with Block Recover, from %d to %d", 
//					bc->block, newBc->block);

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		tag = GET_TAG(newBc, i);
		TAG_DIRTY_BIT(tag) = TAG_DIRTY;
		TAG_VALID_BIT(tag) = TAG_VALID;
		TAG_BLOCK_TS(tag) = timeStamp;
		TAG_PARENT(tag) = parent;
		TAG_SERIAL(tag) = serial;
		TAG_TYPE(tag) = type;
		TAG_PAGE_ID(tag) = (u8)(i & 0xFF);	// now, page_id = page.
									// FIX ME!! if more than 256 pages in a block

		SEAL_TAG(tag);
		
		buf = _FindBufInDirtyList(dev->buf.dirtyGroup[slot].dirty, i);
		if (buf != NULL) {
			if (i == 0)
				data_sum = _GetDirOrFileNameSum(dev, buf);

			TAG_DATA_LEN(tag) = buf->data_len;

			if (buf->data_len == 0 || (buf->ext_mark & UFFS_BUF_EXT_MARK_TRUNC_TAIL)) { // this only happen when truncating a file

				// when truncating a file, the last dirty buf will be
				// set as UFFS_BUF_EXT_MARK_TAIL. so that we don't do page recovery
				// for the rest pages in the block. (file is ended at this page)

				if (!uffs_Assert((buf->ext_mark & UFFS_BUF_EXT_MARK_TRUNC_TAIL) != 0,
					"buf->data == 0 but not the last page of truncating ? block = %d, page_id = %d",
					bc->block, i)) {

					// We can't do more about it for now ...
				}

				if (buf->data_len > 0) {
					flash_op_err = uffs_FlashWritePageCombine(dev, newBlock, i, buf, tag);
				}
				else {
					// data_len == 0, no I/O needed.
					flash_op_err = UFFS_FLASH_NO_ERR;
				}
				succRecover = U_TRUE;
				break;
			}
			else
				flash_op_err = uffs_FlashWritePageCombine(dev, newBlock, i, buf, tag);

			if (flash_op_err != UFFS_FLASH_NO_ERR) {
				if (flash_op_err == UFFS_FLASH_BAD_BLK) {
					uffs_Perror(UFFS_MSG_NORMAL,
								"new bad block %d discovered.", newBlock);
					break;
				}
				else if (flash_op_err == UFFS_FLASH_IO_ERR) {
					uffs_Perror(UFFS_MSG_NORMAL,
								"writing to block %d page %d, I/O error ?", 
								(int)newBlock, (int)i);
					break;
				}
				else {
					uffs_Perror(UFFS_MSG_SERIOUS, "Unhandled flash op result: %d", flash_op_err);
					break;
				}
			}
		}
		else {
			page = uffs_FindPageInBlockWithPageId(dev, bc, i);
			if (page == UFFS_INVALID_PAGE) {
				succRecover = U_TRUE;
				break;  //end of last page, normal break
			}
			page = uffs_FindBestPageInBlock(dev, bc, page);

			if (!uffs_Assert(page != UFFS_INVALID_PAGE, "got an invalid page ?\n"))
				break;

			oldTag = GET_TAG(bc, page);

			// First, try to find existing cached buffer.
			// Note: do not call uffs_BufGetEx() as it may trigger buf flush and result in infinite loop
			buf = uffs_BufGet(dev, parent, serial, i);

			if (buf == NULL) {  // no cached page buffer, use clone buffer.
				useCloneBuf = U_TRUE;
				buf = uffs_BufClone(dev, NULL);
				if (buf == NULL) {
					uffs_Perror(UFFS_MSG_SERIOUS, "Can't clone a new buf!");
					break;
				}
				x = uffs_BufLoadPhyData(dev, buf, bc->block, page);
				if (x == U_FAIL) {
					if (HAVE_BADBLOCK(dev) && dev->bad.block == bc->block) {
						// the old block is a bad block, we'll process it later.
						uffs_Perror(UFFS_MSG_SERIOUS,
									"the old block %d is a bad block, \
									but ignore it for now.",
									bc->block);
					}
					else {
						uffs_Perror(UFFS_MSG_SERIOUS, "I/O error ?");
						uffs_BufFreeClone(dev, buf);
						flash_op_err = UFFS_FLASH_IO_ERR;
						break;
					}
				}

				buf->type = type;
				buf->parent = parent;
				buf->serial = serial;
				buf->page_id = TAG_PAGE_ID(oldTag);
				buf->data_len = TAG_DATA_LEN(oldTag);

			}
			else {
				useCloneBuf = U_FALSE;

				uffs_Assert(buf->page_id == TAG_PAGE_ID(oldTag), "buf->page_id = %d, tag page id: %d", buf->page_id, TAG_PAGE_ID(oldTag));
				uffs_Assert(buf->data_len == TAG_DATA_LEN(oldTag), "buf->data_len = %d, tag data len: %d", buf->data_len, TAG_DATA_LEN(oldTag));
			}

			if (buf->data_len > dev->com.pg_data_size) {
				uffs_Perror(UFFS_MSG_NOISY, "data length over flow, truncated !");
				buf->data_len = dev->com.pg_data_size;
			}

			if (!uffs_Assert(buf->data_len != 0, "data_len == 0 ? block %d, page %d, serial %d, parent %d",
				bc->block, page, buf->serial, buf->parent)) {
				// this could be some error on flash ? we can't do more about it for now ...
			}

			TAG_DATA_LEN(tag) = buf->data_len;

			if (i == 0)
				data_sum = _GetDirOrFileNameSum(dev, buf);

			flash_op_err = uffs_FlashWritePageCombine(dev, newBlock, i, buf, tag);

			if (buf) {
				if (useCloneBuf)
					uffs_BufFreeClone(dev, buf);
				else
					uffs_BufPut(dev, buf);
			}

			if (flash_op_err == UFFS_FLASH_BAD_BLK) {
				uffs_Perror(UFFS_MSG_NORMAL,
							"new bad block %d discovered.", newBlock);
				break;
			}
			else if (flash_op_err == UFFS_FLASH_IO_ERR) {
				uffs_Perror(UFFS_MSG_NORMAL, "I/O error ?", newBlock);
				break;
			}
		}
	} //end of for

	if (i == dev->attr->pages_per_block)
		succRecover = U_TRUE;
	else {
		// expire last page info cache in case the 'tag' is not written.
		uffs_BlockInfoExpire(dev, newBc, i);
	}

	if (flash_op_err == UFFS_FLASH_BAD_BLK) {
		uffs_BlockInfoExpire(dev, newBc, UFFS_ALL_PAGES);
		uffs_BlockInfoPut(dev, newBc);
		if (newNode->u.list.block == dev->bad.block) {
			// the recovered block is a BAD block (buy me a lotto, please :-), we need to 
			// deal with it immediately (mark it as 'bad' and put into bad block list).
			uffs_BadBlockProcess(dev, newNode);
		}

		uffs_Perror(UFFS_MSG_NORMAL, "Retry block cover ...");

		goto retry; // retry on a new erased block ...
	}

	if (succRecover == U_TRUE) {
		// now it's time to clean the dirty buffers
		for (i = 0; i < dev->attr->pages_per_block; i++) {
			buf = _FindBufInDirtyList(dev->buf.dirtyGroup[slot].dirty, i);
			if (buf) {
				if (_BreakFromDirty(dev, buf) == U_SUCC) {
					buf->mark = UFFS_BUF_VALID;
					buf->ext_mark &= ~UFFS_BUF_EXT_MARK_TRUNC_TAIL;
					_MoveNodeToHead(dev, buf);
				}
			}
		}

		// swap the old block node and new block node.
		// it's important that we 'swap' the block and keep the node unchanged
		// so that allowing someone hold the node pointer unawared.
		switch (type) {
		case UFFS_TYPE_DIR:
			node->u.dir.parent = parent;
			node->u.dir.serial = serial;
			node->u.dir.block = newBlock;
			node->u.dir.checksum = data_sum;
			break;
		case UFFS_TYPE_FILE:
			node->u.file.parent = parent;
			node->u.file.serial = serial;
			node->u.file.block = newBlock;
			node->u.file.checksum = data_sum;
			break;
		case UFFS_TYPE_DATA:
			node->u.data.parent = parent;
			node->u.data.serial = serial;
			node->u.data.block = newBlock;
			break;
		default:
			uffs_Perror(UFFS_MSG_SERIOUS, "UNKNOW TYPE");
			break;
		}

		newNode->u.list.block = bc->block;

		// if the recovered block is a bad block, it's time to process it.
		if (HAVE_BADBLOCK(dev) && dev->bad.block == newNode->u.list.block) {
			//uffs_Perror(UFFS_MSG_SERIOUS, "Still have bad block ?");
			uffs_BadBlockProcess(dev, newNode);
		}
		else {
			// erase recovered block, put it back to erased block list.
			if (uffs_IsThisBlockUsed(dev, bc)) {
				uffs_FlashEraseBlock(dev, bc->block);
			}
			if (HAVE_BADBLOCK(dev))
				uffs_BadBlockProcess(dev, newNode);
			else
				uffs_TreeInsertToErasedListTail(dev, newNode);
		}
	}
	else {

		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);  // FIXME: this might not be necessary ...

		uffs_FlashEraseBlock(dev, newBlock);
		newNode->u.list.block = newBlock;
		if (HAVE_BADBLOCK(dev))
			uffs_BadBlockProcess(dev, newNode);
		else
			uffs_TreeInsertToErasedListTail(dev, newNode);
	}

	if (dev->buf.dirtyGroup[slot].dirty != NULL ||
			dev->buf.dirtyGroup[slot].count != 0) {
		uffs_Perror(UFFS_MSG_NORMAL, "still have dirty buffer ?");
	}

	uffs_BlockInfoPut(dev, newBc);

ext:
	return (succRecover == U_TRUE ? U_SUCC : U_FAIL);

}



/** 
 * \brief flush buffer to a new block which is not registered in tree
 *
 * Scenario:
 *		1. get a new block
 *		2. write pages in dirty list to new block, sorted by page_id
 *		3. insert new block to tree
 */
static URET _BufFlush_NewBlock(uffs_Device *dev, int slot)
{
	u8 type;
	TreeNode *node;
	uffs_BlockInfo *bc;
	URET ret;

	ret = U_FAIL;

	node = uffs_TreeGetErasedNode(dev);
	if (node == NULL) {
		uffs_Perror(UFFS_MSG_NOISY, "no erased block!");
		goto ext;
	}
	bc = uffs_BlockInfoGet(dev, node->u.list.block);
	if (bc == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "get block info fail!");
		uffs_InsertToErasedListHead(dev, node); //put node back to erased list
		goto ext;
	}

	type = dev->buf.dirtyGroup[slot].dirty->type;
	
	ret = uffs_BufFlush_Exist_With_BlockCover(dev, slot, node, bc);

	if (ret == U_SUCC)
		uffs_InsertNodeToTree(dev, type, node);
	else {
		uffs_FlashEraseBlock(dev, bc->block);
		uffs_TreeInsertToErasedListTail(dev, node);
	}		

	uffs_BlockInfoPut(dev, bc);
ext:
	return ret;
}


/** 
 * \brief flush buffer to a block with enough free pages 
 *  
 *  pages in dirty list must be sorted by page_id to write to flash
 */
static
URET
 uffs_BufFlush_Exist_With_Enough_FreePage(
		uffs_Device *dev,
		int slot,			//!< dirty group slot
		TreeNode *node,		//!< tree node
		uffs_BlockInfo *bc	//!< block info (Source, also destination)
		)		
{
	u16 page;
	uffs_Buf *buf;
	uffs_Tags *tag;
	URET ret = U_FAIL;
	int x;

//	uffs_Perror(UFFS_MSG_NOISY,
//					"Flush buffers with Enough Free Page to block %d",
//					bc->block);

	for (page = 1;	// page 0 won't be a free page, so we start from 1.
			page < dev->attr->pages_per_block &&
			dev->buf.dirtyGroup[slot].count > 0;		//still has dirty pages?
			page++) {

		// locate to the free page (make sure the page is a erased page, so an unclean page won't sneak in)
		for (; page < dev->attr->pages_per_block; page++) {
			if (uffs_IsPageErased(dev, bc, page))
				break;
		}

		if (!uffs_Assert(page < dev->attr->pages_per_block, "no free page? buf flush not finished."))
			break;

		buf = _FindMinimunPageIdFromDirtyList(dev->buf.dirtyGroup[slot].dirty);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS,
						"count > 0, but no dirty pages in list ?");
			goto ext;
		}

		//write the dirty page (id: buf->page_id) to page (free page)
		tag = GET_TAG(bc, page);
		TAG_DIRTY_BIT(tag) = TAG_DIRTY;
		TAG_VALID_BIT(tag) = TAG_VALID;
		TAG_BLOCK_TS(tag) = uffs_GetBlockTimeStamp(dev, bc);
		TAG_DATA_LEN(tag) = buf->data_len;
		TAG_TYPE(tag) = buf->type;
		TAG_PARENT(tag) = buf->parent;
		TAG_SERIAL(tag) = buf->serial;
		TAG_PAGE_ID(tag) = (u8)(buf->page_id);

		SEAL_TAG(tag);

		x = uffs_FlashWritePageCombine(dev, bc->block, page, buf, tag);
		if (x == UFFS_FLASH_IO_ERR) {
			uffs_Perror(UFFS_MSG_NORMAL, "I/O error <1>?");
			goto ext;
		}
		else if (x == UFFS_FLASH_BAD_BLK) {
			uffs_Perror(UFFS_MSG_NORMAL, "Bad blcok found, start block cover ...");
			ret = uffs_BufFlush_Exist_With_BlockCover(dev, slot, node, bc);
			goto ext;
		}
		else {
			if(_BreakFromDirty(dev, buf) == U_SUCC) {
				buf->mark = UFFS_BUF_VALID;
				_MoveNodeToHead(dev, buf);
			}
		}
	} //end of for
	
	if (dev->buf.dirtyGroup[slot].dirty != NULL ||
			dev->buf.dirtyGroup[slot].count != 0) {
		uffs_Perror(UFFS_MSG_NORMAL, "still has dirty buffer ?");
	}
	else {
		ret = U_SUCC;
	}

ext:
	return ret;
}


URET _BufFlush(struct uffs_DeviceSt *dev,
			   UBOOL force_block_recover, int slot)
{
	uffs_Buf *dirty;
	TreeNode *node;
	uffs_BlockInfo *bc;
	u16 n;
	URET ret;
	u8 type;
	u16 parent;
	u16 serial;
	int block;
	
	if (dev->buf.dirtyGroup[slot].count == 0) {
		return U_SUCC;
	}

	dirty = dev->buf.dirtyGroup[slot].dirty;

	if (_CheckDirtyList(dirty) == U_FAIL)
		return U_FAIL;

	type = dirty->type;
	parent = dirty->parent;
	serial = dirty->serial;

	switch (type) {
	case UFFS_TYPE_DIR:
		node = uffs_TreeFindDirNode(dev, serial);
		break;
	case UFFS_TYPE_FILE:
		node = uffs_TreeFindFileNode(dev, serial);
		break;
	case UFFS_TYPE_DATA:
		node = uffs_TreeFindDataNode(dev, parent, serial);
		break;
	default:
		uffs_Perror(UFFS_MSG_SERIOUS, "unknown type");
		return U_FAIL;
	}

	if (node == NULL) {
		//not found in the tree, need to generate a new block
		ret = _BufFlush_NewBlock(dev, slot);
	}
	else {
		switch (type) {
		case UFFS_TYPE_DIR:
			block = node->u.dir.block;
			break;
		case UFFS_TYPE_FILE:
			block = node->u.file.block;
			break;
		case UFFS_TYPE_DATA:
			block = node->u.data.block;
			break;
		default:
			uffs_Perror(UFFS_MSG_SERIOUS, "unknown type.");
			return U_FAIL;
		}
		bc = uffs_BlockInfoGet(dev, block);
		if(bc == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "get block info fail.");
			return U_FAIL;
		}

		ret = uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);
		if (ret == U_SUCC) {

			n = uffs_GetFreePagesCount(dev, bc);

			if (n >= dev->buf.dirtyGroup[slot].count && !force_block_recover) {
				//The free pages are enough for the dirty pages
				ret = uffs_BufFlush_Exist_With_Enough_FreePage(dev,	slot, node, bc);
			}
			else {
				ret = uffs_BufFlush_Exist_With_BlockCover(dev, slot, node, bc);
			}
		}
		uffs_BlockInfoPut(dev, bc);
	}

	return ret;
}

static int _FindMostDirtyGroup(struct uffs_DeviceSt *dev)
{
	int i, slot = -1;
	int max_count = 0;

	for (i = 0; i < dev->cfg.dirty_groups; i++) {
		if (dev->buf.dirtyGroup[i].dirty &&
				dev->buf.dirtyGroup[i].lock == 0) {
			if (dev->buf.dirtyGroup[i].count > max_count) {
				max_count = dev->buf.dirtyGroup[i].count;
				slot = i;
			}
		}
	}

	return slot;
}

/** lock dirty group */
URET uffs_BufLockGroup(struct uffs_DeviceSt *dev, int slot)
{
	URET ret = U_FAIL;
	if (slot >= 0 && slot < dev->cfg.dirty_groups) {
		dev->buf.dirtyGroup[slot].lock++;
		ret = U_SUCC;
	}	
	return ret;
}

/** unlock dirty group */
URET uffs_BufUnLockGroup(struct uffs_DeviceSt *dev, int slot)
{
	URET ret = U_FAIL;

	if (slot >= 0 && slot < dev->cfg.dirty_groups) {
		if (dev->buf.dirtyGroup[slot].lock > 0)
			dev->buf.dirtyGroup[slot].lock--;
		else {
			uffs_Perror(UFFS_MSG_SERIOUS, "Try to unlock an unlocked group ?");
		}
		ret = U_SUCC;
	}	
	return ret;
}


/** 
 * flush buffers to flash.
 * this will flush all dirty groups.
 * \param[in] dev uffs device
 */
URET uffs_BufFlush(struct uffs_DeviceSt *dev)
{
	int slot;

	slot = uffs_BufFindFreeGroupSlot(dev);
	if (slot >= 0)
		return U_SUCC;	// do nothing if there is free slot
	else
		return uffs_BufFlushMostDirtyGroup(dev);
}

/** 
 * flush most dirty group
 * \param[in] dev uffs device
 */
URET uffs_BufFlushMostDirtyGroup(struct uffs_DeviceSt *dev)
{
	int slot;

	slot = _FindMostDirtyGroup(dev);
	if (slot >= 0) {
		return _BufFlush(dev, U_FALSE, slot);
	}
	return U_SUCC;
}

/** 
 * flush buffers to flash
 * this will pick up a most dirty group,
 * and flush it if there is no free dirty group slot.
 *
 * \param[in] dev uffs device
 * \param[in] force_block_recover #U_TRUE: force a block recover
 *				 even there are enough free pages
 */
URET uffs_BufFlushEx(struct uffs_DeviceSt *dev, UBOOL force_block_recover)
{
	int slot;

	slot = uffs_BufFindFreeGroupSlot(dev);
	if (slot >= 0) {
		return U_SUCC;  //there is free slot, do nothing.
	}
	else {
		slot = _FindMostDirtyGroup(dev);
		return _BufFlush(dev, force_block_recover, slot);
	}
}

/**
 * flush buffer group with given parent/serial num.
 *
 * \param[in] dev uffs device
 * \param[in] parent parent num of the group
 * \param[in] serial serial num of the group
 */
URET uffs_BufFlushGroup(struct uffs_DeviceSt *dev, u16 parent, u16 serial)
{
	int slot;

	slot = uffs_BufFindGroupSlot(dev, parent, serial);
	if (slot >= 0) {
		return _BufFlush(dev, U_FALSE, slot);
	}

	return U_SUCC;
}

/**
 * flush buffer group with given parent/serial num
 * and force_block_recover indicator.
 *
 * \param[in] dev uffs device
 * \param[in] parent parent num of the group
 * \param[in] serial serial num of group
 * \param[in] force_block_recover indicator
 */
URET uffs_BufFlushGroupEx(struct uffs_DeviceSt *dev,
						  u16 parent, u16 serial, UBOOL force_block_recover)
{
	int slot;

	slot = uffs_BufFindGroupSlot(dev, parent, serial);
	if (slot >= 0) {
		return _BufFlush(dev, force_block_recover, slot);
	}

	return U_SUCC;
}


/**
 * flush buffer group/groups which match given parent num.
 *
 * \param[in] dev uffs device
 * \param[in] parent parent num of the group
 * \param[in] serial serial num of group
 * \param[in] force_block_recover indicator
 */
URET uffs_BufFlushGroupMatchParent(struct uffs_DeviceSt *dev, u16 parent)
{
	int slot;
	uffs_Buf *buf;
	URET ret = U_SUCC;

	for (slot = 0; slot < dev->cfg.dirty_groups && ret == U_SUCC; slot++) {
		if (dev->buf.dirtyGroup[slot].dirty) {
			buf = dev->buf.dirtyGroup[slot].dirty;
			if (buf->parent == parent) {
				ret = _BufFlush(dev, U_FALSE, slot);
			}
		}
	}

	return ret;
}

/**
 * find a free dirty group slot
 *
 * \param[in] dev uffs device
 * \return slot index (0 to MAX_DIRTY_BUF_GROUPS - 1) if found one,
 *			 otherwise return -1.
 */
int uffs_BufFindFreeGroupSlot(struct uffs_DeviceSt *dev)
{
	int i, slot = -1;

	for (i = 0; i < dev->cfg.dirty_groups; i++) {
		if (dev->buf.dirtyGroup[i].dirty == NULL) {
			slot = i;
			break;
		}
	}
	return slot;
}

/**
 * find a dirty group slot with given parent/serial num.
 *
 * \param[in] dev uffs device
 * \param[in] parent parent num of the group
 * \param[in] serial serial num of group
 * \return slot index (0 to MAX_DIRTY_BUF_GROUPS - 1) if found one,
 *			otherwise return -1.
 */
int uffs_BufFindGroupSlot(struct uffs_DeviceSt *dev, u16 parent, u16 serial)
{
	uffs_Buf *buf;
	int i, slot = -1;

	for (i = 0; i < dev->cfg.dirty_groups; i++) {
		if (dev->buf.dirtyGroup[i].dirty) {
			buf = dev->buf.dirtyGroup[i].dirty;
			if (buf->parent == parent && buf->serial == serial) {
				slot = i;
				break;
			}
		}
	}
	return slot;
}

/** 
 * \brief get a page buffer
 * \param[in] dev uffs device
 * \param[in] parent parent serial num
 * \param[in] serial serial num
 * \param[in] page_id page_id
 * \return return the buffer found in buffer list, if not found, return NULL.
 */
uffs_Buf * uffs_BufGet(struct uffs_DeviceSt *dev,
					   u16 parent, u16 serial, u16 page_id)
{
	uffs_Buf *p;

	//first, check whether the buffer exist in buf list ?
	p = uffs_BufFind(dev, parent, serial, page_id);

	if (p) {
		p->ref_count++;
		_MoveNodeToHead(dev, p);
	}

	return p;
}

/** 
 * New generate a buffer
 */
uffs_Buf *uffs_BufNew(struct uffs_DeviceSt *dev,
					  u8 type, u16 parent, u16 serial, u16 page_id)
{
	uffs_Buf *buf;

	buf = uffs_BufGet(dev, parent, serial, page_id);
	if (buf) {
		if (buf->ref_count > 1) {
			uffs_Perror(UFFS_MSG_SERIOUS, "When create new buf, \
						an exist buffer has ref count %d, possibly bug!",
						buf->ref_count);
		}
		else {
			buf->data_len = 0;
		}
		_MoveNodeToHead(dev, buf);
		return buf;
	}

	buf = _FindFreeBuf(dev);
	if (buf == NULL) {
		uffs_BufFlushMostDirtyGroup(dev);
		buf = _FindFreeBuf(dev);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "no free page buf!");
			return NULL;
		}
	}

	buf->mark = UFFS_BUF_EMPTY;
	buf->type = type;
	buf->parent = parent;
	buf->serial = serial;
	buf->page_id = page_id;
	buf->data_len = 0;
	buf->ref_count++;
	memset(buf->data, 0xff, dev->com.pg_data_size);

	_MoveNodeToHead(dev, buf);
	
	return buf;	
}



/** 
 * get a page buffer
 * \param[in] dev uffs device
 * \param[in] type dir, file or data ?
 * \param[in] node node on the tree
 * \param[in] page_id page_id
 * \param[in] oflag the open flag of current file/dir object
 * \return return the buffer if found in buffer list, if not found in 
 *		buffer list, it will get a free buffer, and load data from flash.
 *		return NULL if not free buffer.
 */
uffs_Buf *uffs_BufGetEx(struct uffs_DeviceSt *dev,
						u8 type, TreeNode *node, u16 page_id, int oflag)
{
	uffs_Buf *buf;
	u16 parent, serial, block, page;
	uffs_BlockInfo *bc;

	switch (type) {
	case UFFS_TYPE_DIR:
		parent = node->u.dir.parent;
		serial = node->u.dir.serial;
		block = node->u.dir.block;
		break;
	case UFFS_TYPE_FILE:
		parent = node->u.file.parent;
		serial = node->u.file.serial;
		block = node->u.file.block;
		break;
	case UFFS_TYPE_DATA:
		parent = node->u.data.parent;
		serial = node->u.data.serial;
		block = node->u.data.block;
		break;
	default:
		uffs_Perror(UFFS_MSG_SERIOUS, "unknown type");
		return NULL;
	}

	buf = uffs_BufFind(dev, parent, serial, page_id);
	if (buf) {
		buf->ref_count++;
		return buf;
	}

	buf = _FindFreeBuf(dev);
	if (buf == NULL) {
		uffs_BufFlushMostDirtyGroup(dev);
		buf = _FindFreeBuf(dev);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "no free page buf!");
			return NULL;
		}

		/* Note: if uffs_BufFlushMostDirtyGroup() flush the same block as we'll write to,
		 *	the block will be changed to a new one! (and the content of 'node' is changed).
		 *	So here we need to update block number from the new 'node'.
		 */
		switch (type) {
		case UFFS_TYPE_DIR:
			block = node->u.dir.block;
			break;
		case UFFS_TYPE_FILE:
			block = node->u.file.block;
			break;
		case UFFS_TYPE_DATA:
			block = node->u.data.block;
			break;
		default:
			uffs_Perror(UFFS_MSG_SERIOUS, "unknown type");
			return NULL;
		}
	}

	bc = uffs_BlockInfoGet(dev, block);
	if (bc == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't get block info!");
		return NULL;
	}
	
	page = uffs_FindPageInBlockWithPageId(dev, bc, page_id);
	if (page == UFFS_INVALID_PAGE) {
		uffs_BlockInfoPut(dev, bc);
		uffs_Perror(UFFS_MSG_SERIOUS, "can't find right page ? block %d page_id %d", bc->block, page_id);
		return NULL;
	}
	page = uffs_FindBestPageInBlock(dev, bc, page);
	if (!uffs_Assert(page != UFFS_INVALID_PAGE, "got an invalid page?\n"))
		return NULL;

	uffs_BlockInfoPut(dev, bc);

	buf->mark = UFFS_BUF_EMPTY;
	buf->type = type;
	buf->parent = parent;
	buf->serial = serial;
	buf->page_id = page_id;

	if (UFFS_FLASH_HAVE_ERR(uffs_FlashReadPage(dev, block, page, buf, oflag & UO_NOECC ? U_TRUE : U_FALSE))) {
		uffs_Perror(UFFS_MSG_SERIOUS, "can't load page from flash !");
		return NULL;
	}

	buf->data_len = TAG_DATA_LEN(GET_TAG(bc, page));
	buf->mark = UFFS_BUF_VALID;
	buf->ref_count++;

	_MoveNodeToHead(dev, buf);
	
	return buf;

}

/** 
 * \brief Put back a page buffer, make reference count decrease by one
 * \param[in] dev uffs device
 * \param[in] buf buffer to be put back
 */
URET uffs_BufPut(uffs_Device *dev, uffs_Buf *buf)
{
	URET ret = U_FAIL;

	dev = dev;
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_NORMAL,  "Can't put an NULL buffer!");
	}
	else if (buf->ref_count == 0) {
		uffs_Perror(UFFS_MSG_NORMAL,  "Putting an unused page buffer ? ");
	}
	else if (buf->ref_count == CLONE_BUF_MARK) {
		uffs_Perror(UFFS_MSG_NORMAL, "Putting an cloned page buffer ? ");
		ret = uffs_BufFreeClone(dev, buf);
	}
	else {
		buf->ref_count--;
		ret = U_SUCC;
	}

	return ret;
}


/** 
 * \brief clone from an exist buffer.
		allocate memory for new buffer, and copy data from original buffer if 
		original buffer is not NULL. 
 * \param[in] dev uffs device
 * \param[in] buf page buffer to be clone from.
 *				if NULL presented here, data copy will not be processed
 * \return return the cloned page buffer, all data copied from source
 * \note the cloned buffer is not linked in page buffer list in uffs device,
 *			so you should use #uffs_BufFreeClone instead of #uffs_BufPut
 *			when you put back or release buffer
 */
uffs_Buf * uffs_BufClone(uffs_Device *dev, uffs_Buf *buf)
{
	uffs_Buf *p;

	p = _FindFreeBufEx(dev, 1);
	if (p == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"no enough free pages for clone! " \
					"Please increase Clone Buffer Count threshold.");
	}
	else {
		_BreakFromBufList(dev, p);

		if (buf) {
			p->parent = buf->parent;
			p->type = buf->type;
			p->serial = buf->serial;
			p->page_id = buf->page_id;
			
			p->data_len = buf->data_len;
			//athough the valid data length is .data_len,
			//but we still need copy the whole buffer, include header
			memcpy(p->header, buf->header, dev->com.pg_size);
		}
		p->next = p->prev = NULL; // the cloned one is not linked to device buffer
		p->next_dirty = p->prev_dirty = NULL;
		p->ref_count = CLONE_BUF_MARK;	// CLONE_BUF_MARK indicates that
										// this is an cloned buffer
	}

	return p;
}

/** 
 * \brief release cloned buffer
 * \param[in] dev uffs device
 * \param[in] buf cloned buffer
 */
URET uffs_BufFreeClone(uffs_Device *dev, uffs_Buf *buf)
{
	dev = dev; //make compiler happy
	if (!buf)
		return U_FAIL;

	if (buf->ref_count != CLONE_BUF_MARK) {
		/* a cloned buffer must have a ref_count of CLONE_BUF_MARK */
		uffs_Perror(UFFS_MSG_SERIOUS,
					"Try to release a non-cloned page buffer ?");
		return U_FAIL;
	}

	buf->ref_count = 0;
	buf->mark = UFFS_BUF_EMPTY;
	_LinkToBufListTail(dev, buf);

	return U_SUCC;
}



UBOOL uffs_BufIsAllFree(struct uffs_DeviceSt *dev)
{
	uffs_Buf *buf = dev->buf.head;

	while (buf) {
		if(buf->ref_count != 0) return U_FALSE;
		buf = buf->next;
	}

	return U_TRUE;
}

UBOOL uffs_BufIsAllEmpty(struct uffs_DeviceSt *dev)
{
	uffs_Buf *buf = dev->buf.head;

	while (buf) {
		if(buf->mark != UFFS_BUF_EMPTY) return U_FALSE;
		buf = buf->next;
	}

	return U_TRUE;
}


URET uffs_BufSetAllEmpty(struct uffs_DeviceSt *dev)
{
	uffs_Buf *buf = dev->buf.head;

	while (buf) {
		buf->mark = UFFS_BUF_EMPTY;
		buf = buf->next;
	}
	return U_SUCC;
}


void uffs_BufIncRef(uffs_Buf *buf)
{
	buf->ref_count++;
}

void uffs_BufDecRef(uffs_Buf *buf)
{
	if (buf->ref_count > 0)
		buf->ref_count--;
}

/** mark buffer as #UFFS_BUF_EMPTY if ref_count == 0,
	and discard all data it holds */
void uffs_BufMarkEmpty(uffs_Device *dev, uffs_Buf *buf)
{
	if (buf->mark != UFFS_BUF_EMPTY) {
		if (buf->ref_count == 0) {
			if (buf->mark == UFFS_BUF_DIRTY)
				_BreakFromDirty(dev, buf);
			buf->mark = UFFS_BUF_EMPTY;
		}
	}
}

#if 0
static UBOOL _IsBufInDirtyList(struct uffs_DeviceSt *dev, uffs_Buf *buf)
{
	uffs_Buf *p = dev->buf.dirtyGroup[slot].dirty;

	while (p) {
		if(p == buf) return U_TRUE;
		p = p->next_dirty;
	}

	return U_FALSE;
}
#endif

URET uffs_BufWrite(struct uffs_DeviceSt *dev,
				   uffs_Buf *buf, void *data, u32 ofs, u32 len)
{
	int slot;

	if(ofs + len > dev->com.pg_data_size) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"data length out of range! %d+%d", ofs, len);
		return U_FAIL;
	}

	slot = uffs_BufFindGroupSlot(dev, buf->parent, buf->serial);

	if (slot < 0) {
		// need to take a free slot
		slot = uffs_BufFindFreeGroupSlot(dev);
		if (slot < 0) {
			// no free slot ? flush buffer
			if (uffs_BufFlushMostDirtyGroup(dev) != U_SUCC)
				return U_FAIL;

			slot = uffs_BufFindFreeGroupSlot(dev);
			if (slot < 0) {
				// still no free slot ??
				uffs_Perror(UFFS_MSG_SERIOUS, "no free slot ?");
				return U_FAIL;
			}
		}
	}

	if (data)
		memcpy(buf->data + ofs, data, len);
	else
		memset(buf->data + ofs, 0, len);	// if data == NULL, then fill all '\0'.

	if (ofs + len > buf->data_len) 
		buf->data_len = ofs + len;
	
	if (_IsBufInInDirtyList(dev, slot, buf) == U_FALSE) {
		_LinkToDirtyList(dev, slot, buf);
	}

	if (dev->buf.dirtyGroup[slot].count >= dev->buf.dirty_buf_max) {
		if (uffs_BufFlushGroup(dev, buf->parent, buf->serial) != U_SUCC) {
			return U_FAIL;
		}
	}

	return U_SUCC;
}

URET uffs_BufRead(struct uffs_DeviceSt *dev,
				  uffs_Buf *buf, void *data, u32 ofs, u32 len)
{
	u32 readSize;
	u32 pg_data_size = dev->com.pg_data_size;

	readSize = (ofs >= pg_data_size ? 
					0 : (ofs + len >= pg_data_size ? pg_data_size - ofs : len)
				);

	if (readSize > 0) 
		memcpy(data, buf->data + ofs, readSize);

	return U_SUCC;
}







