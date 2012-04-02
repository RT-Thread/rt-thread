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
 * \file uffs_fileem_share.c
 * \brief emulate uffs file system, shared functions
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

/****************************************************************/
/*           Shared flash driver functions:                     */
/*                                                              */
/*   femu_InitFlash(), femu_ReleaseFlash(), femu_EraseBlock()   */
/*                                                              */
/****************************************************************/

static u8 g_page_buf[UFFS_MAX_PAGE_SIZE + UFFS_MAX_SPARE_SIZE];

/*
 * Create emulator disk, initialise monitors, inject manufacture bad blocks, etc.
 *
 */
int femu_InitFlash(uffs_Device *dev)
{
	int i;
	int fSize;
	int written;
	u8 * p = g_page_buf;
	uffs_FileEmu *emu;

	struct uffs_StorageAttrSt *attr = dev->attr;

	int full_page_size = attr->page_data_size + attr->spare_size;
	int total_pages = attr->total_blocks * attr->pages_per_block;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	if (emu->initCount > 0) {
		emu->initCount++;
		return 0;
	}

	if (emu->emu_filename == NULL)
		emu->emu_filename = UFFS_FEMU_FILE_NAME;

	uffs_Perror(UFFS_MSG_NORMAL,  "femu device init.");

	emu->em_monitor_page = (u8 *) malloc(sizeof(emu->em_monitor_page[0]) * total_pages);
	if (!emu->em_monitor_page)
		return -1;
	emu->em_monitor_spare = (u8 *) malloc(sizeof(emu->em_monitor_spare[0]) * total_pages);
	if (!emu->em_monitor_spare)
		return -1;

	emu->em_monitor_block = (u32 *) malloc(sizeof(emu->em_monitor_block[0]) * attr->total_blocks);
	if (!emu->em_monitor_block)
		return -1;

	//clear monitor
	memset(emu->em_monitor_page, 0, sizeof(emu->em_monitor_page[0]) * total_pages);
	memset(emu->em_monitor_spare, 0, sizeof(emu->em_monitor_spare[0]) * total_pages);
	memset(emu->em_monitor_block, 0, sizeof(emu->em_monitor_block[0]) * attr->total_blocks);

	emu->fp = fopen(emu->emu_filename, "rb");
	if (emu->fp == NULL) {
		emu->fp = fopen(emu->emu_filename, "ab+");
		if (emu->fp == NULL) {
			printf(PFX"Failed to create uffs emulation file.");
			return -1;
		}

		fseek(emu->fp, 0, SEEK_END);
		fSize = ftell(emu->fp);
		
		if (fSize < total_pages * full_page_size)	{
			printf("Creating uffs emulation file\n");
			fseek(emu->fp, 0, SEEK_SET);
			memset(p, 0xff, full_page_size);
			for (i = 0; i < total_pages; i++)	{
				written = fwrite(p, 1, full_page_size, emu->fp);
				if (written != full_page_size)	{
					printf("Write failed\n");
					fclose(emu->fp);
					emu->fp = NULL;
					return -1;
				}
			}		
		}
	}

	fflush(emu->fp);	
	fclose(emu->fp);

	emu->fp = fopen(emu->emu_filename, "rb+");
	if (emu->fp == NULL) {
		printf(PFX"Can't open emulation file.\n");
		return -1;
	}

	emu->initCount++;

	return 0;
}

/*
 * Release resources
 */
int femu_ReleaseFlash(uffs_Device *dev)
{
	uffs_FileEmu *emu;

	emu = (uffs_FileEmu *)(dev->attr->_private);

	emu->initCount--;

	if (emu->initCount == 0) {

		uffs_Perror(UFFS_MSG_NORMAL,  "femu device release.");

		if (emu->fp) {
			fclose(emu->fp);
			emu->fp = NULL;
		}

		if (emu->em_monitor_page)
			free(emu->em_monitor_page);
		if (emu->em_monitor_spare) 
			free(emu->em_monitor_spare);
		if (emu->em_monitor_block)
			free(emu->em_monitor_block);
		emu->em_monitor_page = NULL;
		emu->em_monitor_spare = NULL;
		emu->em_monitor_block = NULL;
	}

	return 0;
}

int femu_EraseBlock(uffs_Device *dev, u32 blockNumber)
{

	int i;
	u8 * pg = g_page_buf;
	int pg_size, pgd_size, sp_size, blks, blk_pgs, blk_size;
	uffs_FileEmu *emu;
	emu = (uffs_FileEmu *)(dev->attr->_private);
	if (!emu || !(emu->fp))
		goto err;

	pg_size = dev->attr->page_data_size + dev->attr->spare_size;
	pgd_size = dev->attr->page_data_size;
	sp_size = dev->attr->spare_size;
	blk_pgs = dev->attr->pages_per_block;
	blks = dev->attr->total_blocks;
	blk_size = dev->attr->page_data_size * dev->attr->pages_per_block;
	
	printf("femu: erase block %d\n", blockNumber);

	if ((int)blockNumber >= blks) {
		printf("Attempt to erase non-existant block %d\n",blockNumber);
		goto err;
	}
	else {

		//clear this block monitors
		memset(emu->em_monitor_page + (blockNumber * blk_pgs), 
			0, 
			blk_pgs * sizeof(u8));
		memset(emu->em_monitor_spare + (blockNumber * blk_pgs),
			0,
			blk_pgs * sizeof(u8));

		emu->em_monitor_block[blockNumber]++;
		
		memset(pg, 0xff, (pgd_size + sp_size));
		
		fseek(emu->fp, blockNumber * blk_pgs * (pgd_size + sp_size), SEEK_SET);
		
		for (i = 0; i < blk_pgs; i++)	{
			fwrite(pg, 1, (pgd_size + sp_size), emu->fp);
		}

		fflush(emu->fp);
		dev->st.block_erase_count++;
	}

	return UFFS_FLASH_NO_ERR;
err:
	return UFFS_FLASH_IO_ERR;
	
}

