/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2010 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

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
 * \file uffs_fileem_ecc_hw.c
 * \brief emulate uffs file system for hardware ECC.
 *
 *	 In this emulator, we call 'uffs_FlashMakeSpare()' to do the layout job
 *	 and call 'uffs_EccMake()' to calculate ECC.
 *
 * \author Ricky Zheng @ Oct, 2010
 */

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs_fileem.h"
#include "uffs/uffs_ecc.h"

#define PFX "femu: "
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

static int femu_hw_WritePageWithLayout(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *ecc, const uffs_TagStore *ts)
{
	int written;
	int abs_page;
	int full_page_size;
	uffs_FileEmu *emu;
	struct uffs_StorageAttrSt *attr = dev->attr;
	u8 spare[UFFS_MAX_SPARE_SIZE];
	u8 ecc_buf[UFFS_MAX_ECC_SIZE];
	int spare_len;


	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto err;
	}

	abs_page = attr->pages_per_block * block + page;
	full_page_size = attr->page_data_size + attr->spare_size;

	if (data && data_len > 0) {
		if (data_len > attr->page_data_size)
			goto err;

		emu->em_monitor_page[abs_page]++;
		if (emu->em_monitor_page[abs_page] > PAGE_DATA_WRITE_COUNT_LIMIT) {
			MSG("Warrning: block %d page %d exceed it's maximum write time!", block, page);
			goto err;
		}
		
		fseek(emu->fp, abs_page * full_page_size, SEEK_SET);

		written = fwrite(data, 1, data_len, emu->fp);
		
		if (written != data_len) {
			MSG("write page I/O error ?");
			goto err;
		}

		dev->st.page_write_count++;
		dev->st.io_write += written;

	}

	if (ts) {

		emu->em_monitor_spare[abs_page]++;
		if (emu->em_monitor_spare[abs_page] > PAGE_SPARE_WRITE_COUNT_LIMIT) {
			MSG("Warrning: block %d page %d (spare) exceed it's maximum write time!", block, page);
			goto err;
		}

		if (!uffs_Assert(data != NULL, "BUG: Write spare without data ?"))
			goto err;

		uffs_EccMake(data, data_len, ecc_buf);
		uffs_FlashMakeSpare(dev, ts, ecc_buf, spare);
		spare_len = dev->mem.spare_data_size;
		
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size, SEEK_SET);
		written = fwrite(spare, 1, spare_len, emu->fp);
		if (written != spare_len) {
			MSG("write spare I/O error ?");
			goto err;
		}

		dev->st.spare_write_count++;
		dev->st.io_write += written;
	}

	if (data == NULL && ts == NULL) {
		// mark bad block
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size + attr->block_status_offs, SEEK_SET);
		written = fwrite("\0", 1, 1, emu->fp);
		if (written != 1) {
			MSG("write bad block mark I/O error ?");
			goto err;
		}
		dev->st.io_write++;
	}

	fflush(emu->fp);
	return UFFS_FLASH_NO_ERR;
err:
	fflush(emu->fp);
	return UFFS_FLASH_IO_ERR;
}


static URET femu_hw_ReadPageWithLayout(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc,
									uffs_TagStore *ts, u8 *ecc_store)
{
	int nread;
	uffs_FileEmu *emu;
	int abs_page;
	int full_page_size;
	struct uffs_StorageAttrSt *attr = dev->attr;
	unsigned char status;
	u8 spare[UFFS_MAX_SPARE_SIZE];
	int spare_len;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto err;
	}

	abs_page = attr->pages_per_block * block + page;
	full_page_size = attr->page_data_size + attr->spare_size;

	if (data && data_len > 0) {
		if (data_len > attr->page_data_size)
			goto err;

		fseek(emu->fp, abs_page * full_page_size, SEEK_SET);
		nread = fread(data, 1, data_len, emu->fp);

		if (nread != data_len) {
			MSG("read page I/O error ?");
			goto err;
		}
		dev->st.io_read += nread;
		dev->st.page_read_count++;

		if (ecc) {
			// calculate ECC for data
			uffs_EccMake(data, data_len, ecc);
		}
	}

	if (ts) {

		spare_len = dev->mem.spare_data_size;
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size, SEEK_SET);
		nread = fread(spare, 1, spare_len, emu->fp);

		if (nread != spare_len) {
			MSG("read page spare I/O error ?");
			goto err;
		}

		// unload ts and ecc from spare
		uffs_FlashUnloadSpare(dev, spare, ts, ecc_store);

		dev->st.io_read += nread;
		dev->st.spare_read_count++;
	}

	if (data == NULL && ts == NULL) {
		// read bad block mark
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size + attr->block_status_offs, SEEK_SET);
		nread = fread(&status, 1, 1, emu->fp);

		if (nread != 1) {
			MSG("read badblock mark I/O error ?");
			goto err;
		}
		dev->st.io_read++;

		return status == 0xFF ? UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK;
	}

	return UFFS_FLASH_NO_ERR;
err:
	return UFFS_FLASH_IO_ERR;
}


uffs_FlashOps g_femu_ops_ecc_hw = {
	femu_InitFlash,				// InitFlash()
	femu_ReleaseFlash,			// ReleaseFlash()
	NULL,						// ReadPage()
	femu_hw_ReadPageWithLayout,	// ReadPageWithLayout()
	NULL,						// WritePage()
	femu_hw_WritePageWithLayout,// WritePageWithLayout()
	NULL,						// IsBadBlock(), let UFFS take care of it.
	NULL,						// MarkBadBlock(), let UFFS take care of it.
	femu_EraseBlock,			// EraseBlock()
};
