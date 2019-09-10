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
 * \file uffs_fileem_ecc_soft.c
 * \brief emulate uffs file system for software ECC
 * \author Ricky Zheng @ Oct, 2010
 */

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_flash.h"
#include "uffs_fileem.h"

#define PFX "femu: "
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

static int femu_WritePage(uffs_Device *dev, u32 block, u32 page_num,
							const u8 *data, int data_len, const u8 *spare, int spare_len)
{
	int written;
	int abs_page;
	int full_page_size;
	uffs_FileEmu *emu;
	struct uffs_StorageAttrSt *attr = dev->attr;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto err;
	}

	abs_page = attr->pages_per_block * block + page_num;
	full_page_size = attr->page_data_size + attr->spare_size;

	if (data && data_len > 0) {
		if (data_len > attr->page_data_size)
			goto err;

		emu->em_monitor_page[abs_page]++;
		if (emu->em_monitor_page[abs_page] > PAGE_DATA_WRITE_COUNT_LIMIT) {
			MSGLN("Warrning: block %d page %d exceed it's maximum write time!", block, page_num);
			goto err;
		}
		
		fseek(emu->fp, abs_page * full_page_size, SEEK_SET);

		written = fwrite(data, 1, data_len, emu->fp);
		
		if (written != data_len) {
			MSGLN("write page I/O error ?");
			goto err;
		}

		dev->st.page_write_count++;
		dev->st.io_write += written;
	}

	if (spare && spare_len > 0) {
		if (spare_len > attr->spare_size)
			goto err;

		emu->em_monitor_spare[abs_page]++;
		if (emu->em_monitor_spare[abs_page] > PAGE_SPARE_WRITE_COUNT_LIMIT) {
			MSGLN("Warrning: block %d page %d (spare) exceed it's maximum write time!", block, page_num);
			goto err;
		}
		
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size, SEEK_SET);
		written = fwrite(spare, 1, spare_len, emu->fp);
		if (written != spare_len) {
			MSGLN("write spare I/O error ?");
			goto err;
		}

		dev->st.spare_write_count++;
		dev->st.io_write += written;
	}

	if (data == NULL && spare == NULL) {
		// mark bad block
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size + attr->block_status_offs, SEEK_SET);
		written = fwrite("\0", 1, 1, emu->fp);
		if (written != 1) {
			MSGLN("write bad block mark I/O error ?");
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


static URET femu_ReadPage(uffs_Device *dev, u32 block, u32 page_num, u8 *data, int data_len, u8 *ecc,
							u8 *spare, int spare_len)
{
	int nread;
	uffs_FileEmu *emu;
	int abs_page;
	int full_page_size;
	struct uffs_StorageAttrSt *attr = dev->attr;
	unsigned char status;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto err;
	}

	abs_page = attr->pages_per_block * block + page_num;
	full_page_size = attr->page_data_size + attr->spare_size;

	if (data && data_len > 0) {
		if (data_len > attr->page_data_size)
			goto err;

		fseek(emu->fp, abs_page * full_page_size, SEEK_SET);
		nread = fread(data, 1, data_len, emu->fp);

		if (nread != data_len) {
			MSGLN("read page I/O error ?");
			goto err;
		}
		dev->st.io_read += nread;
		dev->st.page_read_count++;
	}

	if (spare && spare_len > 0) {
		if (spare_len > attr->spare_size)
			goto err;

		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size, SEEK_SET);
		nread = fread(spare, 1, spare_len, emu->fp);

		if (nread != spare_len) {
			MSGLN("read page spare I/O error ?");
			goto err;
		}
		dev->st.io_read += nread;
		dev->st.spare_read_count++;
	}

	if (data == NULL && spare == NULL) {
		// read bad block mark
		fseek(emu->fp, abs_page * full_page_size + attr->page_data_size + attr->block_status_offs, SEEK_SET);
		nread = fread(&status, 1, 1, emu->fp);

		if (nread != 1) {
			MSGLN("read badblock mark I/O error ?");
			goto err;
		}
		dev->st.io_read++;

		return status == 0xFF ? UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK;
	}

	return UFFS_FLASH_NO_ERR;
err:
	return UFFS_FLASH_IO_ERR;
}


uffs_FlashOps g_femu_ops_ecc_soft = {
	femu_InitFlash,		// InitFlash()
	femu_ReleaseFlash,	// ReleaseFlash()
	femu_ReadPage,		// ReadPage()
	NULL,				// ReadPageWithLayout
	femu_WritePage,		// WritePage()
	NULL,				// WirtePageWithLayout
	NULL,				// IsBadBlock(), let UFFS take care of it.
	NULL,				// MarkBadBlock(), let UFFS take care of it.
	femu_EraseBlock,	// EraseBlock()
};
