 /*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/
/**
 * \file nand flash interface example
 * \brief example for using nand flash driver and multiple partitions, with system memory allocator.
 * \author Ricky Zheng, created at 27 Nov, 2007
 * \modify amsl, at 17 Jan, 2010 iamyhw@gmail.com 
 */

#include <rtthread.h>
#include <stdio.h>
#include <dfs_fs.h>
#include "uffs/uffs_device.h"
#include "uffs/uffs_flash.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_find.h"
#include "uffs/uffs_fd.h"
#include "uffs_ext.h"

#include "k9f2g08.h"

#define PFX "nand-drv:"

/*
 * Note: all=0,read manufacturer id and device id only.
 *       all=1,read all bytes,comprise additional ids.
 */
static void nand_read_chip_ids(u8* buf, UBOOL all)
{
	K9F2G08_ReadChipID(buf, all);
}

static int nand_write_page_data(uffs_Device *dev, u32 block, u32 page, const u8 *buffer, int len, u8 *ecc)
{
	K9F2G08_WritePage(block,page,buffer,len,ecc);
	
	dev->st.page_write_count++;
	return UFFS_FLASH_NO_ERR;
}


static int nand_write_page_spare(uffs_Device *dev, u32 block, u32 page, const u8 *spare, int ofs, int len, UBOOL eod)
{
	K9F2G08_WriteTags(block,page,spare,ofs,len);

	dev->st.spare_write_count++;  
	return UFFS_FLASH_NO_ERR;
}

static int nand_read_page_data(uffs_Device *dev, u32 block, u32 page, u8 *buffer, int len, u8 *ecc)
{
	K9F2G08_ReadPage(block,page,buffer,len,ecc);

	dev->st.page_read_count++;
	return UFFS_FLASH_NO_ERR;
}

static int nand_read_page_spare(uffs_Device *dev, u32 block, u32 page, u8 *spare, int ofs, int len)
{
	K9F2G08_ReadTags(block,page,spare,ofs,len);

	dev->st.spare_read_count++;		
	return UFFS_FLASH_NO_ERR;
}

static int nand_erase_block(uffs_Device *dev, u32 block)
{
	K9F2G08_EraseBlock(block);

	dev->st.block_erase_count++;
	return UFFS_FLASH_NO_ERR;
}

static int nand_mark_badblock(uffs_Device *dev,u32 block)
{
	return K9F2G08_Mark_badblk(block);
}

static int nand_is_badblock(uffs_Device *dev,u32 block)
{
	return K9F2G08_Check_badblk(block);
}

/* The only uffs v1.3.2-4 can used. */
static uffs_FlashOps nand_driver_ops = 
{
	nand_read_page_data,    /* ReadPageData	*/
	nand_read_page_spare,   /* ReadPageSpare */
	NULL,                	/* ReadPageSpareWithLayout */
	nand_write_page_data,   /* WritePageData */
	nand_write_page_spare,  /* WritePageSpare */
	NULL,					/* WriteFullPage */		
	nand_is_badblock,       /* IsBadBlock */
	nand_mark_badblock,     /* MarkBadBlock */
	nand_erase_block,       /* EraseBlock */
};

static struct uffs_StorageAttrSt flash_storage = {0};

static int initDevice(uffs_Device *dev)
{
	dev->ops = &nand_driver_ops;
	return U_SUCC;
}

static int releaseDevice(uffs_Device *dev)
{
	return U_SUCC;
}

#include <dfs_uffs.h>

static uffs_Device uffs_device = {0};

/* 
 * define mount table,UFFS FS private data
 * it is absolute accessing for uffs.
 * set struct data on the RT-Thread device 
 */
static uffs_MountTable uffs_mount_table = 
{
	&uffs_device, 
	0, 
	TOTAL_BLOCKS-1, 
	"/" ,
	NULL, 
};

#include "nand.h"
extern struct nand_flash_dev      nand_flash_ids[];
extern struct nand_manufacturers  nand_manuf_ids[];

struct nand_flash_dev* nand_init(u8* buf)
{
	struct nand_flash_dev* type=RT_NULL;
	int i, dev_id,maf_id;

	K9F2G08_Reset();
	rt_kprintf("nand: ");

	nand_read_chip_ids(buf,0);
	maf_id= buf[0];
	/* Try to identify manufacturer */
	for (i = 0; nand_manuf_ids[i].id != 0x0; i++) 
	{
		if (nand_manuf_ids[i].id == maf_id)
		{
			rt_kprintf("%s ",nand_manuf_ids[i].name);
			break;
		}
	}
	if(nand_manuf_ids[i].id == 0x0)
	{
		rt_kprintf("%s\n",nand_manuf_ids[i].name);
		return RT_NULL;	
	}

	dev_id = buf[1];
	/* Lookup the flash id */
	for(i = 0; nand_flash_ids[i].name != RT_NULL; i++) 
	{
		if(dev_id == nand_flash_ids[i].id) 
		{
			type =  &nand_flash_ids[i];
			rt_kprintf("%s\n",nand_flash_ids[i].name);
			return type;
		}
	}
	
	return RT_NULL;
}

/* 
 * RT-Thread Device Driver Interface
 * UFFS FileSystem NandFlash InterFace
 * we don't use entity, let uffs autarky 
 */

struct rt_device nand_device;

static rt_err_t rt_nand_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_nand_open(rt_device_t dev, u16 oflag)
{
	return RT_EOK;
}

static rt_err_t rt_nand_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_nand_control(rt_device_t dev, u8 cmd, void *args)
{
	return RT_EOK;
}

static rt_size_t rt_nand_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{	
	return RT_EOK;
}

static rt_size_t rt_nand_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	return RT_EOK;
}

void rt_hw_nand_init(void)
{
	struct nand_flash_dev *type = RT_NULL;
	u8 buf[5];
	if((type = nand_init(buf)) != RT_NULL)
	{
		uffs_MountTable *entry;
		struct uffs_StorageAttrSt *chip = &flash_storage;

		rt_device_t dev = &nand_device;
		/* fill in NandFlash device struct */
		dev->type      = RT_Device_Class_Block;					
		dev->init      = rt_nand_init;
		dev->open      = rt_nand_open;
		dev->close     = rt_nand_close;
		dev->read      = rt_nand_read;
		dev->write     = rt_nand_write;
		dev->control   = rt_nand_control;
		dev->user_data = &uffs_mount_table;
		/* register nandfalsh device */
		rt_device_register(&nand_device, "nand0",
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

		/* about uffs codes */
		entry = &uffs_mount_table;
		/* entry->lock = rt_sem_create("sem_nand0", 1, RT_IPC_FLAG_FIFO); */ /* it's lonely!how to do? */

		uffs_MemSetupSystemAllocator(&(entry->dev->mem));
		entry->dev->Init    = initDevice;
		entry->dev->Release = releaseDevice;
		entry->dev->attr    = chip;
		uffs_RegisterMountTable(entry);

		/* Newer devices have all the information in additional id bytes */
		if(!type->pagesize) 
		{
			int extid;
			nand_read_chip_ids(buf,1);//reread chip ids,the all and the one.

			/* The 3rd id byte holds MLC / multichip data,untapped */
			/* The 4th id byte is the important one */
			extid = buf[3];
			/* Calc pagesize */
			chip->page_data_size = 1024 << (extid & 0x3);
			extid >>= 2;
			/* Calc oobsize */
			chip->spare_size = (8<<(extid & 0x01))*(chip->page_data_size>>9);
			extid >>= 2;
			/* Calc blocksize. Blocksize is multiples of 64KiB */
			chip->pages_per_block = ((64*1024)<<(extid & 0x03))/(chip->page_data_size);
			/* The 5th id byte,it is no use */
			chip->total_blocks = (type->chipsize*1024*1024) / 
								 chip->page_data_size / chip->pages_per_block;
	
		} 
		else 
		{	/* Old devices have chip data hardcoded in the device id table */
			chip->page_data_size = type->pagesize;
			chip->pages_per_block = type->blocksize / type->pagesize;
			chip->spare_size = chip->page_data_size / 32;
			chip->total_blocks = (type->chipsize*1024*1024) / type->blocksize;
		}
		if(type->options & NAND_SAMSUNG_LP_OPTIONS)
			chip->block_status_offs = NAND_LARGE_BADBLOCK_POS;
		else
			chip->block_status_offs = NAND_SMALL_BADBLOCK_POS;
		chip->ecc_opt    = UFFS_ECC_SOFT;    		/* ecc option, do not use ECC,debug */
		chip->layout_opt = UFFS_LAYOUT_UFFS; 		/* let UFFS do the spare layout */
#if (0)	/* DEBUG trace facility */
		rt_kprintf("page_data_size  = %d\n",chip->page_data_size);		
		rt_kprintf("pages_per_block = %d\n",chip->pages_per_block);
		rt_kprintf("spare_size      = %d\n",chip->spare_size);
		rt_kprintf("total_blocks    = %d\n",chip->total_blocks);
		rt_kprintf("block_stat_offs = %d\n",chip->block_status_offs);
#endif
	}
}

/* end of file */																				 

