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
 * \file uffs_fileem_wrap.c
 *
 * \brief file emulator wrapper functions for injecting bad blocks or ECC errors.
 *
 * \author Ricky Zheng, created Nov, 2010
 */

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs_fileem.h"

#define PFX "femu: "
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

// #define UFFS_FEMU_SHOW_FLASH_IO

#ifdef UFFS_FEMU_ENABLE_INJECTION

struct uffs_FileEmuBitFlip {
	int block;
	int page;
	int offset;
	u8 mask;
};

/* simulate bad blocks */
#define FILEEMU_STOCK_BAD_BLOCKS	{5, 180}	// bad block come from manufacture
#define FILEEMU_ERASE_BAD_BLOCKS	{100, 150}	// new bad block discovered when erasing

/* simulating bit flip */
#define FILEEMU_WRITE_BIT_FLIP \
	{ \
		{20, 2, 10, 1 << 4},	/* block 20, page 2, offset 10, bit 4 */	\
		{24, 4, -3, 1 << 2},	/* block 24, page 4, spare offset 3, bit 2*/ \
		{60, 1, 5, 1 << 3},		/* block 60, page 1, offset 5, bit 3 */ \
		{66, 1, 15, 1 << 7},	/* block 66, page 1, offset 300, bit 7 */ \
		{80, 2, 2, 1 << 1},		/* block 80, page 2, offset 2, bit 1 */ \
		{88, 2, 100, 1 << 5},	/* block 88, page 2, offset 100, bit 5 */ \
	}


static int femu_InitFlash_wrap(uffs_Device *dev);

static int femu_ReadPage_wrap(uffs_Device *dev, u32 block, u32 page, u8 *data, int data_len, u8 *ecc,
							u8 *spare, int spare_len);
static int femu_ReadPageWithLayout_wrap(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc,
									uffs_TagStore *ts, u8 *ecc_store);
static int femu_WritePage_wrap(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *spare, int spare_len);
static int femu_WritePageWithLayout_wrap(uffs_Device *dev, u32 block, u32 page, const u8* data, int data_len, const u8 *ecc,
									const uffs_TagStore *ts);
static int femu_EraseBlock_wrap(uffs_Device *dev, u32 blockNumber);


/////////////////////////////////////////////////////////////////////////////////

void femu_setup_wrapper_functions(uffs_Device *dev)
{
	uffs_FileEmu *emu;
	emu = (uffs_FileEmu *)(dev->attr->_private);

	// setup wrap functions, for inject ECC errors, etc.

	memcpy(&emu->ops_orig, dev->ops, sizeof(struct uffs_FlashOpsSt));

	if (dev->ops->InitFlash)
		dev->ops->InitFlash = femu_InitFlash_wrap;
	if (dev->ops->EraseBlock)
		dev->ops->EraseBlock = femu_EraseBlock_wrap;
	if (dev->ops->ReadPage)
		dev->ops->ReadPage = femu_ReadPage_wrap;
	if (dev->ops->ReadPageWithLayout)
		dev->ops->ReadPageWithLayout = femu_ReadPageWithLayout_wrap;
	if (dev->ops->WritePage)
		dev->ops->WritePage = femu_WritePage_wrap;
	if (dev->ops->WritePageWithLayout)
		dev->ops->WritePageWithLayout = femu_WritePageWithLayout_wrap;
}

static int femu_InitFlash_wrap(uffs_Device *dev)
{
	int ret;
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);

#ifdef FILEEMU_STOCK_BAD_BLOCKS
	u32 bad_blocks[] = FILEEMU_STOCK_BAD_BLOCKS;
	int j;
	u8 x = 0;
	struct uffs_StorageAttrSt *attr = dev->attr;
	int full_page_size = attr->page_data_size + attr->spare_size;
	int blk_size = full_page_size * attr->pages_per_block;
#endif

	if (emu->initCount == 0) {
		ret = emu->ops_orig.InitFlash(dev);
#ifdef FILEEMU_STOCK_BAD_BLOCKS
		if (ret >= 0) {
			for (j = 0; j < ARRAY_SIZE(bad_blocks); j++) {
				if (bad_blocks[j] < dev->attr->total_blocks) {
					printf(" --- manufacture bad block %d ---\n", bad_blocks[j]);
					fseek(emu->fp, bad_blocks[j] * blk_size + attr->page_data_size + dev->attr->block_status_offs, SEEK_SET);
					fwrite(&x, 1, 1, emu->fp);
				}
			}
		}
#endif
	}
	else {
		ret = emu->ops_orig.InitFlash(dev);
	}

	return ret;
}

static int femu_ReadPage_wrap(uffs_Device *dev, u32 block, u32 page, u8 *data, int data_len, u8 *ecc,
							u8 *spare, int spare_len)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);

#ifdef UFFS_FEMU_SHOW_FLASH_IO
	if (data || spare) {
		MSG(PFX " Read block %d page %d", block, page);
		if (data)
			MSG(" DATA[%d]", data_len);
		if (spare)
			MSG(" SPARE[%d]", spare_len);
		MSG(TENDSTR);
	}
#endif
	return emu->ops_orig.ReadPage(dev, block, page, data, data_len, ecc, spare, spare_len);
}

static int femu_ReadPageWithLayout_wrap(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc,
									uffs_TagStore *ts, u8 *ecc_store)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);

#ifdef UFFS_FEMU_SHOW_FLASH_IO
	if (data || ts) {
		MSG(PFX " Read block %d page %d", block, page);
		if (data)
			MSG(" DATA[%d]", data_len);
		if (ts)
			MSG(" TS");
		MSG(TENDSTR);
	}
#endif
	return emu->ops_orig.ReadPageWithLayout(dev, block, page, data, data_len, ecc, ts, ecc_store);
}


////////////////////// wraper functions ///////////////////////////

static void InjectBitFlip(uffs_Device *dev, u32 block, u32 page)
{
#ifdef FILEEMU_WRITE_BIT_FLIP
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	struct uffs_FileEmuBitFlip flips[] = FILEEMU_WRITE_BIT_FLIP;
	struct uffs_FileEmuBitFlip *x;
	u8 buf[UFFS_MAX_PAGE_SIZE + UFFS_MAX_SPARE_SIZE];
	u8 *data = buf;
	u8 *spare = buf + dev->attr->page_data_size;
	int full_page_size = dev->attr->page_data_size + dev->attr->spare_size;
	int blk_size = full_page_size * dev->attr->pages_per_block;
	int page_offset = block * blk_size + full_page_size * page;

	int i;
	u8 *p;

	fseek(emu->fp, page_offset, SEEK_SET);
	fread(buf, 1, full_page_size, emu->fp);

	p = NULL;
	for (i = 0; i < ARRAY_SIZE(flips); i++) {
		x = &flips[i];
		if (x->block == block && x->page == page) {
			if (x->offset >= 0) {
				printf(" --- Inject data bit flip at block%d, page%d, offset%d, mask%d --- \n", block, page, x->offset, x->mask);
				p = (u8 *)(data + x->offset);
			}
			else {
				printf(" --- Inject spare bit flip at block%d, page%d, offset%d, mask%d --- \n", block, page, -x->offset, x->mask);
				p = (u8 *)(spare - x->offset);
			}
			*p = (*p & ~x->mask) | (~(*p & x->mask) & x->mask);
		}
	}

	if (p) {
		fseek(emu->fp, page_offset, SEEK_SET);
		fwrite(buf, 1, full_page_size, emu->fp);
	}
#endif	
}

static int femu_WritePage_wrap(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *spare, int spare_len)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	int ret;

#ifdef UFFS_FEMU_SHOW_FLASH_IO
	if (data || spare) {
		MSG(PFX " Write block %d page %d", block, page);
		if (data)
			MSG(" DATA[%d]", data_len);
		if (spare)
			MSG(" SPARE[%d]", spare_len);
		MSG(TENDSTR);
	}
#endif
	
	ret = emu->ops_orig.WritePage(dev, block, page, data, data_len, spare, spare_len);

	InjectBitFlip(dev, block, page);

	return ret;
}

static int femu_WritePageWithLayout_wrap(uffs_Device *dev, u32 block, u32 page, const u8* data, int data_len, const u8 *ecc,
									const uffs_TagStore *ts)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	int ret;
	
#ifdef UFFS_FEMU_SHOW_FLASH_IO
	if (data || ts) {
		MSG(PFX " Write block %d page %d", block, page);
		if (data)
			MSG(" DATA[%d]", data_len);
		if (ts)
			MSG(" TS");
		MSG(TENDSTR);
	}
#endif

	ret = emu->ops_orig.WritePageWithLayout(dev, block, page, data, data_len, ecc, ts);

	InjectBitFlip(dev, block, page);

	return ret;
}


static int femu_EraseBlock_wrap(uffs_Device *dev, u32 blockNumber)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);

#ifdef FILEEMU_ERASE_BAD_BLOCKS
	int blocks[] = FILEEMU_ERASE_BAD_BLOCKS;
	int i;
	URET ret;
	ret = emu->ops_orig.EraseBlock(dev, blockNumber);

	for (i = 0; i < ARRAY_SIZE(blocks); i++) {
		if (blockNumber == blocks[i]) {
			printf(" --- Inject bad block%d when erasing --- \n", blockNumber);
			ret = UFFS_FLASH_BAD_BLK;
		}
	}

	return ret;		

#else

	return emu->ops_orig.EraseBlock(dev, blockNumber);

#endif
}

#endif // UFFS_FEMU_ENABLE_INJECTION

/////////////////////////////////////////////////////////////////////////////////
