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
  the GNU General Public License v2.my_application_main_entry
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/
/**
 * \file flash-interface-example.c
 * \brief example for using flash driver and multiple partitions, with static memory allocator.
 * \author Ricky Zheng, created at 27 Nov, 2007
 */
  
#include <string.h>

#include "uffs/uffs_device.h"
#include "uffs/uffs_flash.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fs.h"

#define PFX "nand-drv:"

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR == 0
int main()
{
	uffs_Perror(UFFS_ERR_NORMAL, "This example need CONFIG_USE_STATIC_MEMORY_ALLOCATOR = 1");
	return 0;
}
#else


#define USE_SINGLE_WRITE_FUN


#ifdef USE_SINGLE_WRITE_FUN
static int nand_write_full_page(uffs_Device *dev, u32 block, u32 pageNum, const u8 *page, int len, const u8 *tag, int tag_len, const u8 *ecc);
#else
static int nand_write_page_data(uffs_Device *dev, u32 block, u32 pageNum, const u8 *page, int len, u8 *ecc);
static int nand_write_page_spare(uffs_Device *dev, u32 block, u32 pageNum, const u8 *spare, int ofs, int len, UBOOL eod);
#endif

static int nand_read_page_data(uffs_Device *dev, u32 block, u32 pageNum, u8 *page, int len, u8 *ecc);
static int nand_read_page_spare(uffs_Device *dev, u32 block, u32 pageNum, u8 *spare, int ofs, int len);

static int nand_erase_block(uffs_Device *dev, u32 blockNumber);

static URET nand_init_device(uffs_Device *dev);


#ifdef USE_SINGLE_WRITE_FUN
// if you want to optimize nand flash driver, or use special nand hardware controller, 
// or use other NAND driver (for example, eCos NAND lib), you shoud do layout in nand driver.
static int nand_write_full_page(uffs_Device *dev, u32 block, u32 pageNum, const u8 *page, int len, const u8 *tag, int tag_len, const u8 *ecc)
{
#define SPOOL(dev) &((dev)->mem.spare_pool)

	u8 *spare_buf = NULL;
	
	spare_buf = (u8 *) uffs_PoolGet(SPOOL(dev));  // alloc a spare buffer
	
	// ... START WRITE COMMAND ...
	// ...
	
	if (page) {
		// WRITE page data
		// ....		
		if (dev->attr->ecc_opt == UFFS_ECC_HW) {
			// read ECC from hardware controller to ecc buf,
			// ...
		}
	}
	
	if (tag && tag_len > 0) {
		
		// now, you can use UFFS's layout function
			uffs_FlashMakeSpare(dev, (uffs_TagStore *)tag, ecc, spare_buf);
		// or, do your own layout
		//   ....
		
		// WRITE spare_buf to page spare ...
		// ...
	}
	
	// FINISH write command ...
	// ...
	// read program status ...
	// ...
  
	if (page)
		dev->st.page_write_count++;
	if (tag)
		dev->st.spare_write_count++;
	
	if (spare_buf)
		uffs_PoolPut(SPOOL(dev), spare_buf);  // release spare buffer
	
	return UFFS_FLASH_NO_ERR;
}

#else

static int nand_write_page_data(uffs_Device *dev, u32 block, u32 pageNum, const u8 *page, int len, u8 *ecc)
{
	// send WRITE command

	// ... transfer data ...
	
	dev->st.page_write_count++;
	return UFFS_FLASH_NO_ERR;
}


static int nand_write_page_spare(uffs_Device *dev, u32 block, u32 pageNum, const u8 *spare, int ofs, int len, UBOOL eod)
{
	if (eod == U_FALSE) {
		// send WRITE command
	}
	else {
		// do not need to send WRITE command if eod == U_FALSE because 'nand_write_page_data' is called before.
	}

	// ... transfer data ...

	// send COMMIT command

	// read STATUS

	dev->st.spare_write_count++;  
	return UFFS_FLASH_NO_ERR;
}

#endif


static int nand_read_page_data(uffs_Device *dev, u32 block, u32 pageNum, u8 *page, int len, u8 *ecc)
{
	// send READ command

	// ... transfer data ...

	// read STATUS

	dev->st.page_read_count++;
	return UFFS_FLASH_NO_ERR;
}

static int nand_read_page_spare(uffs_Device *dev, u32 block, u32 pageNum, u8 *spare, int ofs, int len)
{
	// send READ command

	// ... transfer data ...

	// read STATUS

	dev->st.spare_read_count++;		
	return UFFS_FLASH_NO_ERR;
}


static int nand_erase_block(uffs_Device *dev, u32 blockNumber)
{
	// insert your nand driver codes here ...

	dev->st.block_erase_count++;
	return UFFS_FLASH_NO_ERR;
}


/////////////////////////////////////////////////////////////////////////////////

static struct uffs_FlashOpsSt my_nand_driver_ops = {
	nand_read_page_data,    //ReadPageData
	nand_read_page_spare,   //ReadPageSpare
	NULL,                   //ReadPageSpareWithLayout
#ifdef USE_SINGLE_WRITE_FUN
	NULL,
	NULL,
	nand_write_full_page,   //WriteFullPages
#else
	nand_write_page_data,   //WritePageData
	nand_write_page_spare,  //WritePageSpare
	NULL,
#endif	
	NULL,                   //IsBadBlock
	NULL,                   //MarkBadBlock
	nand_erase_block,       //EraseBlock
};

// change these parameters to fit your nand flash specification
#define MAN_ID          MAN_ID_SAMSUNG  // simulate Samsung's NAND flash

#define TOTAL_BLOCKS    1024
#define PAGE_DATA_SIZE  512
#define PAGE_SPARE_SIZE 16
#define PAGES_PER_BLOCK 32
#define PAGE_SIZE		(PAGE_DATA_SIZE + PAGE_SPARE_SIZE)
#define BLOCK_DATA_SIZE (PAGE_DATA_SIZE * PAGES_PER_BLOCK)

#define NR_PARTITION	2								/* total partitions */
#define PAR_1_BLOCKS	100								/* partition 1 */
#define PAR_2_BLOCKS	(TOTAL_BLOCKS - PAR_1_BLOCKS)	/* partition 2 */

static struct uffs_StorageAttrSt flash_storage = {0};

/* static alloc the memory for each partition */

static int static_buffer_par1[UFFS_STATIC_BUFF_SIZE(PAGES_PER_BLOCK, PAGE_SIZE, PAR_1_BLOCKS) / sizeof(int)];
static int static_buffer_par2[UFFS_STATIC_BUFF_SIZE(PAGES_PER_BLOCK, PAGE_SIZE, PAR_2_BLOCKS) / sizeof(int)];;


static void setup_flash_storage(struct uffs_StorageAttrSt *attr)
{
	memset(attr, 0, sizeof(struct uffs_StorageAttrSt));
	
	attr->total_blocks = TOTAL_BLOCKS;			/* total blocks */
	attr->page_data_size = PAGE_DATA_SIZE;		/* page data size */
	attr->pages_per_block = PAGES_PER_BLOCK;	/* pages per block */
	attr->spare_size = PAGE_SPARE_SIZE;		  	/* page spare size */
	attr->block_status_offs = 4;				/* block status offset is 5th byte in spare */
	attr->ecc_opt = UFFS_ECC_SOFT;              /* ecc option */
	attr->layout_opt = UFFS_LAYOUT_UFFS;        /* let UFFS do the spare layout */    
}


static URET my_initDevice(uffs_Device *dev)
{
	dev->ops = &my_nand_driver_ops;
    
	return U_SUCC;
}

static URET my_releaseDevice(uffs_Device *dev)
{
	return U_SUCC;
}

/* define mount table */
static uffs_Device demo_device_1 = {0};
static uffs_Device demo_device_2 = {0};

static uffs_MountTable demo_mount_table[] = {
	{ &demo_device_1,  0, PAR_1_BLOCKS - 1, "/data/" },
	{ &demo_device_2,  PAR_1_BLOCKS, PAR_1_BLOCKS + PAR_2_BLOCKS - 1, "/" },
	{ NULL, 0, 0, NULL }
};

static int my_init_filesystem(void)
{
	uffs_MountTable *mtbl = &(demo_mount_table[0]);

	/* setup nand storage attributes */
	setup_flash_storage(&flash_storage);

	/* setup memory allocator */
	uffs_MemSetupStaticAllocator(&demo_device_1.mem, static_buffer_par1, sizeof(static_buffer_par1));
	uffs_MemSetupStaticAllocator(&demo_device_2.mem, static_buffer_par2, sizeof(static_buffer_par2));

	/* register mount table */
	while(mtbl->dev) {
		mtbl->dev->Init = my_initDevice;
		mtbl->dev->Release = my_releaseDevice;
		mtbl->dev->attr = &flash_storage;
		uffs_RegisterMountTable(mtbl);
		mtbl++;
	}
	
	return uffs_InitMountTable() == U_SUCC ? 0 : -1;
}

/* application entry */
int main()
{
	my_init_filesystem();

	// ... my application codes ....
	// read/write/create/delete files ...

	uffs_ReleaseMountTable();

	return 0;
}

#endif


/////////////////////////////////////////////////////////////////////////////////
