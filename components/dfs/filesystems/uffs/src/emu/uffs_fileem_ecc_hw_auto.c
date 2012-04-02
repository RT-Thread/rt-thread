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
 * \file uffs_fileem_ecc_hw_auto.c
 *
 * \brief Emulate uffs file system for auto hardware ECC or RS error collection.
 *
 *    This emulator emulate LPC32x0 MLC NAND controller which generate 10 bytes
 *    Reed-Solomon error correction code (RS-ECC) for every 518 bytes data.
 *
 *    For small page MLC have 16 bytes spare area leves only 6 bytes for 'meta-data',
 *    no enough room for UFFS's 8 bytes tag and bad block mark. For this reason,
 *    we adjust page data/spare boundary to 508/20.
 *
 *    This emulator does not calculate real RS-ECC code, instead, we use software ECC
 *    to calculate 6 bytes ECC code, so this solution does not have the same error
 *    correcting cabability of RS-ECC.
 *
 *    Note: the MLC controller strictly require sequencial access to serial data buffer.
 *
 * \author Ricky Zheng @ Oct, 2010
 */

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_ecc.h"
#include "uffs_fileem.h"

#define PFX "femu: "
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

#define RS_ECC_SIZE			10
#define PAGE_DATA_SIZE		508
#define PAGE_SPARE_SIZE		20
#define PAGE_FULL_SIZE		(PAGE_DATA_SIZE + PAGE_SPARE_SIZE)
static u8 g_sdata_buf[PAGE_FULL_SIZE];	// emulating LPC32x0's 528-bytes serial data buffer

static int g_sdata_buf_pointer = 0;

static void start_sdata_access()
{
	g_sdata_buf_pointer = 0;
}

static void feed_sdata(const u8 *data, int len)
{
	if (!uffs_Assert(g_sdata_buf_pointer + len <= sizeof(g_sdata_buf), "BUG: Serial Data Buffer overflow !!"))
		return;

	if (data)
		memcpy(g_sdata_buf + g_sdata_buf_pointer, data, len);
	g_sdata_buf_pointer += len;
}

static void feed_sdata_constant(u8 val, int num)
{
	if (!uffs_Assert(g_sdata_buf_pointer + num <= sizeof(g_sdata_buf), "BUG: Serial Data Buffer overflow !!"))
		return;

	memset(g_sdata_buf + g_sdata_buf_pointer, val, num);
	g_sdata_buf_pointer += num;
}

static void drain_sdata(u8 *data, int len)
{
	if (!uffs_Assert( (int)sizeof(g_sdata_buf) - g_sdata_buf_pointer >= len, "BUG: Serial Data Buffer overdrain !!"))
		return;

	if (data)
		memcpy(data, g_sdata_buf + g_sdata_buf_pointer, len);
	g_sdata_buf_pointer += len;
}

static int load_sdata(uffs_Device *dev, int block, int page)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	int abs_page;
	struct uffs_StorageAttrSt *attr = dev->attr;
	int nread;
	int ret;
	u8 ecc_buf[RS_ECC_SIZE];
	u8 *ecc_store;

	abs_page = attr->pages_per_block * block + page;

	fseek(emu->fp, abs_page * PAGE_FULL_SIZE, SEEK_SET);
	nread = fread(g_sdata_buf, 1, PAGE_FULL_SIZE, emu->fp);
	g_sdata_buf_pointer = 0;

	ret = ((nread == PAGE_FULL_SIZE) ? UFFS_FLASH_NO_ERR : UFFS_FLASH_IO_ERR);

	if (ret == UFFS_FLASH_NO_ERR) {

		// Perform ECC check & correction
		// In the real world, this is done by MLC controller hardware
		memset(ecc_buf, 0xFF, RS_ECC_SIZE);
		uffs_EccMake(g_sdata_buf, attr->page_data_size, ecc_buf);

		ecc_store = g_sdata_buf + PAGE_FULL_SIZE - RS_ECC_SIZE;

		ret = uffs_EccCorrect(g_sdata_buf, attr->page_data_size, ecc_store, ecc_buf);

		ret = (ret < 0 ? UFFS_FLASH_ECC_FAIL :
				(ret > 0 ? UFFS_FLASH_ECC_OK : UFFS_FLASH_NO_ERR));
		
	}

	return ret;
}

static int program_sdata(uffs_Device *dev, int block, int page)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	int abs_page;
	struct uffs_StorageAttrSt *attr = dev->attr;
	u8 ecc_buf[RS_ECC_SIZE];
	int writtern = 0;

	// In the real world, MLC controller will generate RS-ECC code in serial data buffer
	// and might start auto programing NAND flash. Here, we use software ECC to emulate RS-ECC.
	memset(ecc_buf, 0xFF, sizeof(ecc_buf));
	uffs_EccMake(g_sdata_buf, attr->page_data_size, ecc_buf);
	feed_sdata(ecc_buf, RS_ECC_SIZE);

	if (!uffs_Assert(g_sdata_buf_pointer == PAGE_FULL_SIZE, "Serial Data Buffer is not fully filled !!"))
		goto ext;

	abs_page = attr->pages_per_block * block + page;

	fseek(emu->fp, abs_page * PAGE_FULL_SIZE, SEEK_SET);
	writtern = fwrite(g_sdata_buf, 1, PAGE_FULL_SIZE, emu->fp);
ext:
	return (writtern == PAGE_FULL_SIZE) ? UFFS_FLASH_NO_ERR : UFFS_FLASH_IO_ERR;
}


static int femu_hw_auto_InitFlash(uffs_Device *dev)
{
	struct uffs_StorageAttrSt *attr = dev->attr;

	// now this is a good chance to adjust page data/spare boundary
	if (attr->page_data_size + attr->spare_size != PAGE_FULL_SIZE) {
		MSGLN("This emulator emulates only for page size %d bytes !", PAGE_FULL_SIZE);
		return -1;
	}
	if (attr->spare_size < PAGE_SPARE_SIZE) {
		attr->page_data_size -= (PAGE_SPARE_SIZE - attr->spare_size);
		attr->spare_size = PAGE_SPARE_SIZE;
		MSGLN("Adjust page data/spare boundary to %d/%d", attr->page_data_size, attr->spare_size);
	}

	// and fix ECC size
	attr->ecc_size = RS_ECC_SIZE;
	MSGLN("Adjust ECC size to %d bytes", attr->ecc_size);
	
	return femu_InitFlash(dev);
}


static int femu_hw_auto_WritePageWithLayout(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *ecc, const uffs_TagStore *ts)
{
	int abs_page;
	uffs_FileEmu *emu;
	struct uffs_StorageAttrSt *attr = dev->attr;
	u8 spare[PAGE_SPARE_SIZE];
	int ret = UFFS_FLASH_IO_ERR;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto err;
	}

	abs_page = attr->pages_per_block * block + page;

	start_sdata_access();

	dev->st.page_write_count++;
	dev->st.spare_write_count++;
	dev->st.io_write += PAGE_FULL_SIZE;

	if (data || ts) {
		// normal page write
		if (data && data_len > 0) {
			if (data_len > attr->page_data_size)
				goto err;

			emu->em_monitor_page[abs_page]++;
			if (emu->em_monitor_page[abs_page] > PAGE_DATA_WRITE_COUNT_LIMIT) {
				MSGLN("Warrning: block %d page %d exceed it's maximum write time!", block, page);
				goto err;
			}
			
			// Copy data to serial data buffer
			feed_sdata(data, data_len);

			// Pad the rest data as 0xFF
			feed_sdata_constant(0xFF, attr->page_data_size - data_len);

		}
		else {
			// We still need to feed data to serial data buffer to make MLC controller happy
			// The current UFFS won't write ts only, so we'll never run to here.
			feed_sdata_constant(0xFF, attr->page_data_size);
		}

		if (ts) {

			emu->em_monitor_spare[abs_page]++;
			if (emu->em_monitor_spare[abs_page] > PAGE_SPARE_WRITE_COUNT_LIMIT) {
				MSGLN("Warrning: block %d page %d (spare) exceed it's maximum write time!", block, page);
				goto err;
			}

			memset(spare, 0xFF, sizeof(spare));
			uffs_FlashMakeSpare(dev, ts, NULL, spare);	// do not pack ECC, as MLC controller will
														// automatically write RS-ECC to the latest 10 bytes.

			// feed spare data to serial data buffer
			feed_sdata(spare, PAGE_SPARE_SIZE - RS_ECC_SIZE);			
		}
	}
	else {
		// mark bad block

		// feed data to serial data buffer to make MLC controller happy
		feed_sdata_constant(0xFF, attr->page_data_size);

		memset(spare, 0xFF, sizeof(spare));
		spare[attr->block_status_offs] = 0;

		// feed spare data to serial data buffer
		feed_sdata(spare, PAGE_SPARE_SIZE - RS_ECC_SIZE);

		dev->st.io_write++;
	}

	// now, program serial data buffer to NAND flash
	ret = program_sdata(dev, block, page);

	fflush(emu->fp);
	return ret;
err:
	fflush(emu->fp);
	return ret;
}


static URET femu_hw_auto_ReadPageWithLayout(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc,
									uffs_TagStore *ts, u8 *ecc_store)
{
	uffs_FileEmu *emu;
	int abs_page;
	struct uffs_StorageAttrSt *attr = dev->attr;
	unsigned char status;
	u8 spare[PAGE_SPARE_SIZE];
	int ret = UFFS_FLASH_IO_ERR;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (!emu || !(emu->fp)) {
		goto ext;
	}

	abs_page = attr->pages_per_block * block + page;

	// now load full page to serial data buffer
	ret = load_sdata(dev, block, page);
	if (ret != UFFS_FLASH_NO_ERR)
		goto ext;

	start_sdata_access();

	dev->st.io_read += PAGE_FULL_SIZE;
	dev->st.page_read_count++;
	dev->st.spare_read_count++;

	if (data || ts) {

		if (data && data_len > 0) {
			if (data_len > attr->page_data_size)
				goto ext;

			drain_sdata(data, data_len);
		}

		if (ts) {
			if (g_sdata_buf_pointer < attr->page_data_size)
				drain_sdata(NULL, attr->page_data_size - g_sdata_buf_pointer);

			drain_sdata(spare, PAGE_SPARE_SIZE - RS_ECC_SIZE);

			// unload ts from spare
			uffs_FlashUnloadSpare(dev, spare, ts, NULL);
		}
	}
	else {
		// read bad block mark
		drain_sdata(NULL, attr->page_data_size + attr->block_status_offs - 1);
		drain_sdata(&status, 1);

		ret = (status == 0xFF ? UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK);
	}

ext:
	return ret;
}


uffs_FlashOps g_femu_ops_ecc_hw_auto = {
	femu_hw_auto_InitFlash,				// InitFlash()
	femu_ReleaseFlash,					// ReleaseFlash()
	NULL,								// ReadPage()
	femu_hw_auto_ReadPageWithLayout,	// ReadPageWithLayout()
	NULL,								// WritePage()
	femu_hw_auto_WritePageWithLayout,	// WirtePageWithLayout()
	NULL,						// IsBadBlock(), let UFFS take care of it.
	NULL,						// MarkBadBlock(), let UFFS take care of it.
	femu_EraseBlock,			// EraseBlock()
};
