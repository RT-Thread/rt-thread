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
 * \file uffs_public.c
 * \brief public and miscellaneous functions
 * \author Ricky Zheng, created 10th May, 2005
 */

#include "uffs/uffs_types.h"
#include "uffs/uffs_config.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_os.h"

#include <string.h>

#define PFX "pub: "


int uffs_GetFirstBlockTimeStamp(void)
{
	return 0;
}

int uffs_GetNextBlockTimeStamp(int prev)
{
	return (prev + 1) % 3;
}

UBOOL uffs_IsSrcNewerThanObj(int src, int obj)
{
	switch (src - obj) {
	case 0:
		uffs_Perror(UFFS_ERR_SERIOUS,  "the two block have the same time stamp ?");
		break;
	case 1:
	case -2:
		return U_TRUE;
	case -1:
	case 2:
		return U_FALSE;
	default:
		uffs_Perror(UFFS_ERR_SERIOUS,  "time stamp out of range !");
		break;
	}

	return U_FALSE;
}


/** 
 * \brief given a page, search the block to find a better page with the same page id
 *
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] page page number to be compared with
 *
 * \return the better page number, could be the same with the given page
 */
u16 uffs_FindBestPageInBlock(uffs_Device *dev, uffs_BlockInfo *bc, u16 page)
{
	int i;
	int best;
	uffs_Tags *tag, *tag_old;

	if (page == dev->attr->pages_per_block - 1)
		return page;
	
	uffs_BlockInfoLoad(dev, bc, page); //load old page
	tag_old = GET_TAG(bc, page);

	for (i = dev->attr->pages_per_block - 1; i > page; i--) {
		uffs_BlockInfoLoad(dev, bc, i);
		tag = GET_TAG(bc, i);
		if (TAG_PAGE_ID(tag) == TAG_PAGE_ID(tag_old)) {
			if (TAG_PARENT(tag) == TAG_PARENT(tag_old) &&
				TAG_SERIAL(tag) == TAG_SERIAL(tag_old) &&
				TAG_IS_DIRTY(tag) &&		//0: dirty, 1:clear
				TAG_IS_VALID(tag_old)) {	//0: valid, 1:invalid
					break;
			}
		}
	}
	best = i;

#if 0
	if (TAG_PAGE_ID(tag_old) == page) {
		//well, try to speed up by probing the last page ....
		uffs_BlockInfoLoad(dev, bc, dev->attr->pages_per_block - 1);
		tag = GET_TAG(bc, dev->attr->pages_per_block - 1);
		if (TAG_IS_VALID(tag) &&
			TAG_IS_DIRTY(tag) &&
			TAG_PAGE_ID(tag) == dev->attr->pages_per_block - 1) {
			return page;
		}
	}

	uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);
	best = page;
	//the better page must be ahead of page, so ...i = page + 1; i < ...
	for (i = page + 1; i < dev->attr->pages_per_block; i++) {
		tag = GET_TAG(bc, i);
		if (TAG_PAGE_ID(tag) == TAG_PAGE_ID(tag_old)) {
			if (TAG_PARENT(tag) == TAG_PARENT(tag_old) &&
				TAG_SERIAL(tag) == TAG_SERIAL(tag_old) &&
				TAG_IS_DIRTY(tag) &&		//0: dirty, 1:clear
				TAG_IS_VALID(tag_old)) {	//0: valid, 1:invalid
				if (i > best) 
					best = i;
			}
		}
	}
#endif

	return best;
}

/** 
 * \brief find a valid page with given page_id
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] page_id page_id to be find
 * \return the valid page number which has given page_id
 * \retval >=0 page number
 * \retval UFFS_INVALID_PAGE page not found
 */
u16 uffs_FindPageInBlockWithPageId(uffs_Device *dev, uffs_BlockInfo *bc, u16 page_id)
{
	u16 page;
	uffs_Tags *tag;

	//Indeed, the page which has page_id, should ahead of page_id ...
	for (page = page_id; page < dev->attr->pages_per_block; page++) {
		uffs_BlockInfoLoad(dev, bc, page);
		tag = &(bc->spares[page].tag);
		if (TAG_PAGE_ID(tag) == page_id)
			return page;
	}

	return UFFS_INVALID_PAGE;
}

/** 
 * Are all the pages in the block used ?
 */
UBOOL uffs_IsBlockPagesFullUsed(uffs_Device *dev, uffs_BlockInfo *bc)
{
	uffs_Tags *tag;

	// if the last page is dirty, then the whole block is full
	uffs_BlockInfoLoad(dev, bc, dev->attr->pages_per_block - 1);
	tag = GET_TAG(bc, dev->attr->pages_per_block - 1);

	return TAG_IS_DIRTY(tag) ? U_TRUE : U_FALSE;
}

/** 
 * Is this block used ?
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \retval U_TRUE block is used
 * \retval U_FALSE block is free
 */
UBOOL uffs_IsThisBlockUsed(uffs_Device *dev, uffs_BlockInfo *bc)
{
	uffs_Tags *tag;

	// if the first page is dirty, then this block is used.
	uffs_BlockInfoLoad(dev, bc, 0);
	tag = GET_TAG(bc, 0);

	return TAG_IS_DIRTY(tag) ? U_TRUE : U_FALSE;
}

/** 
 * get block time stamp from a exist block
 * \param[in] dev uffs device
 * \param[in] bc block info
 */
int uffs_GetBlockTimeStamp(uffs_Device *dev, uffs_BlockInfo *bc)
{
	if(uffs_IsThisBlockUsed(dev, bc) == U_FALSE) 
		return uffs_GetFirstBlockTimeStamp();
	else{
		uffs_BlockInfoLoad(dev, bc, 0);
		return TAG_BLOCK_TS(GET_TAG(bc, 0));
	}

}

/** 
 * find first free page from 'pageFrom'
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] pageFrom search from this page
 * \return return first free page number from 'pageFrom'
 * \retval UFFS_INVALID_PAGE no free page found
 * \retval >=0 the first free page number
 */
u16 uffs_FindFirstFreePage(uffs_Device *dev, uffs_BlockInfo *bc, u16 pageFrom)
{
	u16 i;

	for (i = pageFrom; i < dev->attr->pages_per_block; i++) {
		uffs_BlockInfoLoad(dev, bc, i);
		if (uffs_IsPageErased(dev, bc, i) == U_TRUE)
			return i;
	}

	return UFFS_INVALID_PAGE; //free page not found
}


/** 
 * Find first valid page from a block, just used in mounting a partition
 */
u16 uffs_FindFirstValidPage(uffs_Device *dev, uffs_BlockInfo *bc)
{
	u16 i;

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		if (uffs_BlockInfoLoad(dev, bc, i) == U_SUCC)
			return i;
	}
	return UFFS_INVALID_PAGE;
}


/** 
 * calculate sum of data, 8bit version
 * \param[in] p data pointer
 * \param[in] len length of data
 * \return return sum of data, 8bit
 */
u8 uffs_MakeSum8(const void *p, int len)
{
	u8 ret = 0;
	const u8 *data = (const u8 *)p;

	if (!p)
		return 0;

	while (len > 0) {
		ret += *data++;
		len--;
	}

	return ret;
}

/** 
 * calculate sum of datam, 16bit version
 * \param[in] p data pointer
 * \param[in] len length of data
 * \return return sum of data, 16bit
 */
u16 uffs_MakeSum16(const void *p, int len)
{
	u8 ret_lo = 0;
	u8 ret_hi = 0;
	const u8 *data = (const u8 *)p;

	if (!p)
		return 0;

	while (len > 0) {
		ret_lo += *data;
		ret_hi ^= *data;
		data++;
		len--;
	}

	return (ret_hi << 8) | ret_lo;
}

/** 
 * create a new file on a free block
 * \param[in] dev uffs device
 * \param[in] parent parent dir serial num
 * \param[in] serial serial num of this new file
 * \param[in] bc block information
 * \param[in] fi file information
 * \note parent, serial, bc must be provided before, and all information in fi should be filled well before.
 */
URET uffs_CreateNewFile(uffs_Device *dev, u16 parent, u16 serial, uffs_BlockInfo *bc, uffs_FileInfo *fi)
{
	uffs_Tags *tag;
	uffs_Buf *buf;

	uffs_BlockInfoLoad(dev, bc, 0);

	tag = GET_TAG(bc, 0);
	TAG_PARENT(tag) = parent;
	TAG_SERIAL(tag) = serial;
	TAG_DATA_LEN(tag) = sizeof(uffs_FileInfo);
	//tag->data_sum = uffs_MakeSum16(fi->name, fi->name_len);

	buf = uffs_BufGet(dev, parent, serial, 0);
	if (buf == NULL) {
		uffs_Perror(UFFS_ERR_SERIOUS, "get buf fail.");
		return U_FAIL;
	}

	memcpy(buf->data, fi, TAG_DATA_LEN(tag));
	buf->data_len = TAG_DATA_LEN(tag);

	return uffs_BufPut(dev, buf);
}


/** 
 * \brief calculate data length of a file block
 * \param[in] dev uffs device
 * \param[in] bc block info
 */
int uffs_GetBlockFileDataLength(uffs_Device *dev, uffs_BlockInfo *bc, u8 type)
{
	u16 page_id;
	u16 i;
	uffs_Tags *tag;
	int size = 0;
	u16 page;
	u16 lastPage = dev->attr->pages_per_block - 1;

	// TODO: Need to speed up this procedure!
	// First try the last page. will hit it if it's the full loaded file/data block.
	uffs_BlockInfoLoad(dev, bc, lastPage);
	tag = GET_TAG(bc, lastPage);

	if (type == UFFS_TYPE_FILE) {
		if(TAG_PAGE_ID(tag) == (lastPage - 1) &&
			TAG_DATA_LEN(tag) == dev->com.pg_data_size) {
			size = dev->com.pg_data_size * (dev->attr->pages_per_block - 1);
			return size;
		}
	}
	if (type == UFFS_TYPE_DATA) {
		if(TAG_PAGE_ID(tag) == lastPage &&
			TAG_DATA_LEN(tag) == dev->com.pg_data_size) {
			size = dev->com.pg_data_size * dev->attr->pages_per_block;
			return size;
		}
	}

	// ok, it's not the full loaded file/data block, need to read all spares....
	uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);
	tag = GET_TAG(bc, 0);
	if (TAG_TYPE(tag) == UFFS_TYPE_FILE) {
		page_id = 1; //In file header block, file data page_id from 1
		i = 1;		//search from page 1
	}
	else {
		page_id = 0;	//in normal file data block, page_id from 0
		i = 0;		//in normal file data block, search from page 0
	}
	for (; i < dev->attr->pages_per_block; i++) {
		tag = GET_TAG(bc, i);
		if (page_id == TAG_PAGE_ID(tag)) {
			page = uffs_FindBestPageInBlock(dev, bc, i);
			size += TAG_DATA_LEN(GET_TAG(bc, page));
			page_id++;
		}
	}

	return size;
}

/** 
 * get free pages number
 * \param[in] dev uffs device
 * \param[in] bc block info
 */
int uffs_GetFreePagesCount(uffs_Device *dev, uffs_BlockInfo *bc)
{
	int count = 0;
	int i;

	for (i = dev->attr->pages_per_block - 1; i >= 0; i--) {
		uffs_BlockInfoLoad(dev, bc, i);
		if (uffs_IsPageErased(dev, bc, (u16)i) == U_TRUE) {
			count++;
		}
		else break;
	}

	return count;
}
/** 
 * \brief Is the block erased ?
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] page page number to be check
 * \retval U_TRUE block is erased, ready to use
 * \retval U_FALSE block is dirty, maybe use by file
 */
UBOOL uffs_IsPageErased(uffs_Device *dev, uffs_BlockInfo *bc, u16 page)
{
	uffs_Tags *tag;

	uffs_BlockInfoLoad(dev, bc, page);
	tag = GET_TAG(bc, page);

	if (!TAG_IS_DIRTY(tag) &&
		!TAG_IS_VALID(tag)) {
		return U_TRUE;
	}

	return U_FALSE;
}

/** 
 * \brief Is this block the last block of file ? (no free pages, and full filled with full page_id)
 */
UBOOL uffs_IsDataBlockReguFull(uffs_Device *dev, uffs_BlockInfo *bc)
{
	uffs_Tags *tag;
	uffs_BlockInfoLoad(dev, bc, dev->attr->pages_per_block - 1);

	tag = GET_TAG(bc, dev->attr->pages_per_block - 1);

	if (TAG_PAGE_ID(tag) == (dev->attr->pages_per_block - 1) &&
		TAG_DATA_LEN(tag) == dev->com.pg_data_size) {
		return U_TRUE;
	}
	return U_FALSE;
}

/** 
 * get partition used (bytes)
 */
int uffs_GetDeviceUsed(uffs_Device *dev)
{
	return (dev->par.end - dev->par.start + 1 - dev->tree.bad_count
				- dev->tree.erased_count) * dev->attr->page_data_size * dev->attr->pages_per_block;
}

/** 
 * get partition free (bytes)
 */
int uffs_GetDeviceFree(uffs_Device *dev)
{
	return dev->tree.erased_count * dev->attr->page_data_size * dev->attr->pages_per_block;
}

/** 
 * get partition total size (bytes)
 */
int uffs_GetDeviceTotal(uffs_Device *dev)
{
	return (dev->par.end - dev->par.start + 1) * dev->attr->page_data_size * dev->attr->pages_per_block;
}

/**
 * load mini hader from flash
 */
URET uffs_LoadMiniHeader(uffs_Device *dev, int block, u16 page, struct uffs_MiniHeaderSt *header)
{
	int ret = dev->ops->ReadPageData(dev, block, page, (u8 *)header, sizeof(struct uffs_MiniHeaderSt), NULL);

	dev->st.page_header_read_count++;

	return UFFS_FLASH_HAVE_ERR(ret) ? U_FAIL : U_SUCC;
}

#if 0
/** \brief transfer the standard uffs_Tags to uffs_Tags_8
 *  \param[in] tag standard uffs_Tags
 *  \param[out] tag_8 small tag to fit into 8 bytes spare space
 */
void uffs_TransferToTag8(uffs_Tags *tag, uffs_Tags_8 *tag_8)
{
	tag_8->dirty = tag->dirty;
	tag_8->valid = tag->valid;
	tag_8->type = tag->type;
	tag_8->block_ts = tag->block_ts;
	tag_8->page_id = tag->page_id;
	tag_8->parent = tag->parent & 0xFF;
	tag_8->serial = tag->serial & 0xFF;
	tag_8->data_len = tag->data_len & 0xFF;
	tag_8->data_sum = tag->data_sum;
	tag_8->block_status = tag->block_status;
}

/** \brief transfer the small uffs_Tags_8 to standard uffs_Tags
 *  \param[out] tag standard uffs_Tags
 *  \param[in] tag_8 small tag to fit into 8 bytes spare space
 */
void uffs_TransferFromTag8(uffs_Tags *tag, uffs_Tags_8 *tag_8)
{
	tag->dirty = tag_8->dirty;
	tag->valid = tag_8->valid;
	tag->type = tag_8->type;
	tag->block_ts = tag_8->block_ts;
	tag->page_id = tag_8->page_id;
	tag->parent = tag_8->parent;
	tag->serial = tag_8->serial;
	tag->data_len = tag_8->data_len;
	tag->data_sum = tag_8->data_sum;
	tag->block_status = tag_8->block_status;
}
#endif


