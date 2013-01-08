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

#include "uffs_config.h"
#include "uffs/uffs_types.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_crc.h"

#include <string.h>

#define PFX "pub : "


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
		uffs_Perror(UFFS_MSG_SERIOUS,
					"the two block have the same time stamp ?");
		break;
	case 1:
	case -2:
		return U_TRUE;
	case -1:
	case 2:
		return U_FALSE;
	default:
		uffs_Perror(UFFS_MSG_SERIOUS,  "time stamp out of range !");
		break;
	}

	return U_FALSE;
}


/** 
 * \brief given a page, search the block to find
 *			a better page with the same page id
 *
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] page page number to be compared with
 *
 * \return the better page number, could be the same with the given page.
 *         if the given page does not have good tag, return UFFS_INVALID_PAGE.
 */
u16 uffs_FindBestPageInBlock(uffs_Device *dev, uffs_BlockInfo *bc, u16 page)
{
	int i;
	uffs_Tags *tag, *tag_old;

	if (!uffs_Assert(page != UFFS_INVALID_PAGE, "invalid param !"))
		return page;	// just in case ...

	uffs_BlockInfoLoad(dev, bc, page); // load old page
	tag_old = GET_TAG(bc, page);

	if (!uffs_Assert(TAG_IS_GOOD(tag_old), "try to find a invalid page ?"))
		return UFFS_INVALID_PAGE;

	if (page == dev->attr->pages_per_block - 1)	// already the last page ?
		return page;

	for (i = dev->attr->pages_per_block - 1; i > page; i--) {
		uffs_BlockInfoLoad(dev, bc, i);
		tag = GET_TAG(bc, i);
		if (TAG_IS_GOOD(tag) &&
			TAG_PAGE_ID(tag) == TAG_PAGE_ID(tag_old) &&
			TAG_PARENT(tag) == TAG_PARENT(tag_old) &&
			TAG_SERIAL(tag) == TAG_SERIAL(tag_old))
		{
			break;
		}
	}

	return i;
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
u16 uffs_FindPageInBlockWithPageId(uffs_Device *dev,
								   uffs_BlockInfo *bc, u16 page_id)
{
	u16 page;
	uffs_Tags *tag;

	//Indeed, the page which has page_id, should ahead of page_id ...
	for (page = page_id; page < dev->attr->pages_per_block; page++) {
		uffs_BlockInfoLoad(dev, bc, page);
		tag = &(bc->spares[page].tag);
		if (TAG_IS_GOOD(tag) && TAG_PAGE_ID(tag) == page_id)
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

	return TAG_IS_GOOD(tag) ? U_TRUE : U_FALSE;
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
u16 uffs_FindFirstFreePage(uffs_Device *dev,
						   uffs_BlockInfo *bc, u16 pageFrom)
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
 * calculate sum of data, 8bit version
 * \param[in] p data pointer
 * \param[in] len length of data
 * \return return sum of data, 8bit
 */
u8 uffs_MakeSum8(const void *p, int len)
{
	return uffs_crc16sum(p, len) & 0xFF;
}

/** 
 * calculate sum of datam, 16bit version
 * \param[in] p data pointer
 * \param[in] len length of data
 * \return return sum of data, 16bit
 */
u16 uffs_MakeSum16(const void *p, int len)
{
	return uffs_crc16sum(p, len);
}

/** 
 * create a new file on a free block
 * \param[in] dev uffs device
 * \param[in] parent parent dir serial num
 * \param[in] serial serial num of this new file
 * \param[in] bc block information
 * \param[in] fi file information
 * \note parent, serial, bc must be provided before,
 *		 and all information in fi should be filled well before.
 */
URET uffs_CreateNewFile(uffs_Device *dev,
						u16 parent, u16 serial,
						uffs_BlockInfo *bc, uffs_FileInfo *fi)
{
	uffs_Tags *tag;
	uffs_Buf *buf;

	uffs_BlockInfoLoad(dev, bc, 0);

	tag = GET_TAG(bc, 0);
	TAG_PARENT(tag) = parent;
	TAG_SERIAL(tag) = serial;
	TAG_DATA_LEN(tag) = sizeof(uffs_FileInfo);

	buf = uffs_BufGet(dev, parent, serial, 0);
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "get buf fail.");
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

	uffs_BlockInfoLoad(dev, bc, lastPage);
	tag = GET_TAG(bc, lastPage);

	if (TAG_IS_GOOD(tag)) {
		// First try the last page.
		// if it's the full loaded file/data block, then we have a quick path.
		if (type == UFFS_TYPE_FILE) {
			if (TAG_PAGE_ID(tag) == (lastPage - 1)) {
				size = dev->com.pg_data_size * (dev->attr->pages_per_block - 2) + TAG_DATA_LEN(tag);
				return size;
			}
		}
		if (type == UFFS_TYPE_DATA) {
			if (TAG_PAGE_ID(tag) == lastPage) {
				size = dev->com.pg_data_size * (dev->attr->pages_per_block - 1) + TAG_DATA_LEN(tag);
				return size;
			}
		}
	}

	// ok, it's not the full loaded file/data block,
	// need to read all spares....
	uffs_BlockInfoLoad(dev, bc, UFFS_ALL_PAGES);
	tag = GET_TAG(bc, 0);
	if (uffs_Assert(TAG_IS_GOOD(tag), "block %d page 0 does not have good tag ?", bc->block)) {
		if (TAG_TYPE(tag) == UFFS_TYPE_FILE) {
			page_id = 1;	//In file header block, file data page_id from 1
			i = 1;			//search from page 1
		}
		else {
			page_id = 0;	//in normal file data block, page_id from 0
			i = 0;			//in normal file data block, search from page 0
		}
		for (; i < dev->attr->pages_per_block; i++) {
			tag = GET_TAG(bc, i);
			if (TAG_IS_GOOD(tag)) {
				if (page_id == TAG_PAGE_ID(tag)) {
					page = uffs_FindBestPageInBlock(dev, bc, i);
					if (uffs_Assert(page != UFFS_INVALID_PAGE, "got an invalid page ?")) {
						size += TAG_DATA_LEN(GET_TAG(bc, page));
						page_id++;
					}
				}
			}
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

	// search from the last page ... to first page
	for (i = dev->attr->pages_per_block - 1; i >= 0; i--) {
		uffs_BlockInfoLoad(dev, bc, i);
		if (uffs_IsPageErased(dev, bc, (u16)i) == U_TRUE) {
			count++;
		}
		else {
			if (TAG_IS_GOOD(GET_TAG(bc, i)))  // it won't be any free page if we see a good tag.
				break;
		}
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

	if (!TAG_IS_SEALED(tag) &&
		!TAG_IS_DIRTY(tag) &&
		!TAG_IS_VALID(tag)) {
		return U_TRUE;
	}

	return U_FALSE;
}

/** 
 * get partition used (bytes)
 */
int uffs_GetDeviceUsed(uffs_Device *dev)
{
	return (dev->par.end - dev->par.start + 1 -
			dev->tree.bad_count	- dev->tree.erased_count
			) *
				dev->attr->page_data_size *
					dev->attr->pages_per_block;
}

/** 
 * get partition free (bytes)
 */
int uffs_GetDeviceFree(uffs_Device *dev)
{
	return dev->tree.erased_count *
			dev->attr->page_data_size *
				dev->attr->pages_per_block;
}

/** 
 * get partition total size (bytes)
 */
int uffs_GetDeviceTotal(uffs_Device *dev)
{
	return (dev->par.end - dev->par.start + 1) *
				dev->attr->page_data_size *
					dev->attr->pages_per_block;
}

/**
 * load mini hader from flash
 */
URET uffs_LoadMiniHeader(uffs_Device *dev,
						 int block, u16 page, struct uffs_MiniHeaderSt *header)
{
	int ret;
	struct uffs_FlashOpsSt *ops = dev->ops;

	if (ops->ReadPageWithLayout) {
		ret = ops->ReadPageWithLayout(dev, block, page, (u8 *)header, 
										sizeof(struct uffs_MiniHeaderSt), NULL, NULL, NULL);
	}
	else {
		ret = ops->ReadPage(dev, block, page, (u8 *)header, sizeof(struct uffs_MiniHeaderSt), NULL, NULL, 0);
	}

	dev->st.page_header_read_count++;

	return UFFS_FLASH_HAVE_ERR(ret) ? U_FAIL : U_SUCC;
}

