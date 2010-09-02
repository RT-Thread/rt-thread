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
 * \file uffs_utils.c
 * \brief utilities of uffs
 * \author Ricky Zheng, created 12th May, 2005
 */
#include "uffs/uffs_device.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_version.h"
#include "uffs/uffs_badblock.h"

#include <stdio.h>
#include <string.h>

#define PFX "util: "

#ifdef CONFIG_ENABLE_BAD_BLOCK_VERIFY
static void _ForceFormatAndCheckBlock(uffs_Device *dev, int block)
{
	u8 *pageBuf;
	int pageSize;
	int i, j;
	uffs_Buf *buf;
	UBOOL bad = U_TRUE;
	int ret;

	buf = uffs_BufClone(dev, NULL);
	if (buf == NULL) {
		uffs_Perror(UFFS_ERR_SERIOUS, "Alloc page buffer fail ! Format stoped.");
		goto ext;
	}

	pageSize = dev->com.pg_data_size;
	pageBuf = buf->data;


	//step 1: Erase, fully fill with 0x0, and check
	ret = dev->ops->EraseBlock(dev, block);
	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		goto bad_out;

	memset(pageBuf, 0, pageSize);
	for (i = 0; i < dev->attr->pages_per_block; i++) {
		ret = dev->ops->WritePageData(dev, block, i, pageBuf, pageSize, NULL);
		if (UFFS_FLASH_IS_BAD_BLOCK(ret))
			goto bad_out;
		ret = dev->ops->WritePageSpare(dev, block, i, pageBuf, 0, dev->attr->spare_size, U_TRUE);
		if (UFFS_FLASH_IS_BAD_BLOCK(ret))
			goto bad_out;
	}
	for (i = 0; i < dev->attr->pages_per_block; i++) {
		memset(pageBuf, 0xFF, pageSize);
		dev->ops->ReadPageData(dev, block, i, pageBuf, pageSize, NULL);
		for (j = 0; j < pageSize; j++) {
			if(pageBuf[j] != 0)
				goto bad_out;
		}
		memset(pageBuf, 0xFF, dev->attr->spare_size);
		dev->ops->ReadPageSpare(dev, block, i, pageBuf, 0, dev->attr->spare_size);
		for (j = 0; j < dev->attr->spare_size; j++) {
			if(pageBuf[j] != 0)
				goto bad_out;
		}
	}

	//step 2: Erase, and check
	ret = dev->ops->EraseBlock(dev, block);
	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		goto bad_out;

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		memset(pageBuf, 0, pageSize);
		dev->ops->ReadPageData(dev, block, i, pageBuf, pageSize, NULL);
		for (j = 0; j < pageSize; j++) {
			if(pageBuf[j] != 0xFF)
				goto bad_out;
		}
		memset(pageBuf, 0, dev->attr->spare_size);
		dev->ops->ReadPageSpare(dev, block, i, pageBuf, 0, dev->attr->spare_size);
		for (j = 0; j < dev->attr->spare_size; j++) {
			if(pageBuf[j] != 0xFF)
				goto bad_out;
		}
	}

	// format succ
	bad = U_FALSE;

bad_out:
	if (bad == U_TRUE)
		uffs_FlashMarkBadBlock(dev, block);
ext:
	if (buf) 
		uffs_BufFreeClone(dev, buf);

	return;
}
#endif



URET uffs_FormatDevice(uffs_Device *dev)
{
	u16 i, slot;
	
	if (dev == NULL)
		return U_FAIL;

	if (dev->ops == NULL) 
		return U_FAIL;


	if (uffs_BufIsAllFree(dev) == U_FALSE) {
		uffs_Perror(UFFS_ERR_NORMAL, "some page still in used!");
		return U_FAIL;
	}

	for (slot = 0; slot < MAX_DIRTY_BUF_GROUPS; slot++) {
		if (dev->buf.dirtyGroup[slot].count > 0) {
			uffs_Perror(UFFS_ERR_SERIOUS, "there still have dirty pages!");
			return U_FAIL;
		}
	}

	uffs_BufSetAllEmpty(dev);


	if (uffs_BlockInfoIsAllFree(dev) == U_FALSE) {
		uffs_Perror(UFFS_ERR_NORMAL, "there still have block info cache ? fail to format");
		return U_FAIL;
	}

	uffs_BlockInfoExpireAll(dev);

	for (i = dev->par.start; i <= dev->par.end; i++) {
		if (uffs_FlashIsBadBlock(dev, i) == U_FALSE) {
			uffs_FlashEraseBlock(dev, i);
			if (HAVE_BADBLOCK(dev))
				uffs_BadBlockProcess(dev, NULL);
		}
		else {
#ifdef CONFIG_ENABLE_BAD_BLOCK_VERIFY
			_ForceFormatAndCheckBlock(dev, i);
#endif
		}
	}

	if (uffs_TreeRelease(dev) == U_FAIL) {
		return U_FAIL;
	}

	if (uffs_TreeInit(dev) == U_FAIL) {
		return U_FAIL;
	}

	if (uffs_BuildTree(dev) == U_FAIL) {
		return U_FAIL;
	}
	
	return U_SUCC;
}

