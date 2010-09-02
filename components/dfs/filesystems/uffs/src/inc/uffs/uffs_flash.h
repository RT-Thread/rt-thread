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
 * \file uffs_public.h
 * \brief flash interface for UFFS
 * \author Ricky Zheng
 */

#ifndef _UFFS_FLASH_H_
#define _UFFS_FLASH_H_

#include "uffs/uffs_types.h"
#include "uffs/uffs_config.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_device.h"

#ifdef __cplusplus
extern "C"{
#endif


/** ECC options (uffs_StorageAttrSt.ecc_opt) */
#define UFFS_ECC_NONE		0	//!< do not use ECC
#define UFFS_ECC_SOFT		1	//!< UFFS calculate the ECC
#define UFFS_ECC_HW			2	//!< Flash driver(or by hardware) calculate the ECC
#define UFFS_ECC_HW_AUTO	3	//!< Hardware calculate the ECC and automatically write to spare.


/** spare layout options (uffs_StorageAttrSt.layout_opt) */
#define UFFS_LAYOUT_UFFS	0	//!< do layout by dev->attr information
#define UFFS_LAYOUT_FLASH	1	//!< flash driver do the layout

#define UFFS_SPARE_LAYOUT_SIZE	6	//!< maximum spare layout array size, 2 segments

/** flash operation return code */
#define UFFS_FLASH_NO_ERR		0		//!< no error
#define UFFS_FLASH_ECC_OK		1		//!< bit-flip found, but corrected by ECC
#define UFFS_FLASH_IO_ERR		-1		//!< I/O error
#define UFFS_FLASH_ECC_FAIL		-2		//!< ECC failed
#define UFFS_FLASH_BAD_BLK		-3		//!< bad block
#define UFFS_FLASH_UNKNOWN_ERR	-100	//!< unkown error?

#define UFFS_FLASH_HAVE_ERR(e)		((e) < 0)

#if defined(CONFIG_BAD_BLOCK_POLICY_STRICT)
# define UFFS_FLASH_IS_BAD_BLOCK(e)	((e) == UFFS_FLASH_ECC_FAIL || (e) == UFFS_FLASH_ECC_OK || (e) == UFFS_FLASH_BAD_BLK)
#else
# define UFFS_FLASH_IS_BAD_BLOCK(e)	((e) == UFFS_FLASH_ECC_FAIL || (e) == UFFS_FLASH_BAD_BLK)
#endif


/** defines for page info (data length and data sum) */
#define UFFS_PAGE_INFO_CLEAN	0xFFFFFFFF
#define UFFS_PAGE_INFO_IOERR	0xDEADFFFF
#define UFFS_PAGE_GET_LEN(info)	(info & 0xFFFF)
#define UFFS_PAGE_GET_DSUM(info) (info >> 16)
#define UFFS_PAGE_MAKE_INFO(d_len, d_sum) ((d_sum << 16) | d_len)

/** 
 * \struct uffs_StorageAttrSt
 * \brief uffs device storage attribute, provide by nand specific file
 */
struct uffs_StorageAttrSt {
	u32 total_blocks;		//!< total blocks in this chip
	u16 page_data_size;		//!< page data size (physical page data size, e.g. 512)
	u16 pages_per_block;	//!< pages per block
	u8 spare_size;			//!< page spare size (physical page spare size, e.g. 16)
	u8 block_status_offs;	//!< block status byte offset in spare
	int ecc_opt;			//!< ecc option ( #UFFS_ECC_[NONE|SOFT|HW|HW_AUTO] )
	int layout_opt;			//!< layout option (#UFFS_LAYOUT_UFFS or #UFFS_LAYOUT_FLASH)
	const u8 *ecc_layout;	//!< page data ECC layout: [ofs1, size1, ofs2, size2, ..., 0xFF, 0]
	const u8 *data_layout;	//!< spare data layout: [ofs1, size1, ofs2, size2, ..., 0xFF, 0]
	u8 _uffs_ecc_layout[UFFS_SPARE_LAYOUT_SIZE];	//!< uffs spare ecc layout
	u8 _uffs_data_layout[UFFS_SPARE_LAYOUT_SIZE];	//!< uffs spare data layout
	void *_private;			//!< private data for storage attribute
};


/**
 * \struct uffs_FlashOpsSt 
 * \brief low level flash operations, should be implement in flash driver
 */
struct uffs_FlashOpsSt {
	/**
	 * Read page data.
	 * 
	 * if ecc_opt is UFFS_ECC_HW, flash driver must calculate and return ecc (if ecc != NULL).
	 *
	 * if ecc_opt is UFFS_ECC_HW_AUTO, flash driver do ecc correction aganist ecc in spare area.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success and/or has no flip bits.
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_ECC_FAIL: page data has flip bits and ecc correct failed.
	 *			#UFFS_FLASH_ECC_OK: page data has flip bits and corrected by ecc.
	 *
	 * \note pad 0xFF for calculating ECC if len < page_data_size
	 */
	int (*ReadPageData)(uffs_Device *dev, u32 block, u32 page, u8 *data, int len, u8 *ecc);


	/**
	 * Read page spare [len] bytes from [ofs].
	 *
	 * \note flash driver must privide this function.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *
	 * \note flash driver DO NOT need to do ecc correction for spare data,
	 *		UFFS will take care of spare data ecc.
	 */
	int (*ReadPageSpare)(uffs_Device *dev, u32 block, u32 page, u8 *spare, int ofs, int len);

	/**
	 * Read page spare, unload to tag and ecc.
	 *
	 * \note flash driver must provide this function if layout_opt is UFFS_LAYOUT_FLASH.
	 *       UFFS will use this function (if exist) prio to 'ReadPageSpare()'
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *
	 * \note flash driver DO NOT need to do ecc correction for spare data,
	 *		UFFS will take care of spare data ecc.
	 */
	int (*ReadPageSpareWithLayout)(uffs_Device *dev, u32 block, u32 page, u8 *tag, int len, u8 *ecc);

	/**
	 * Write page data.
	 *
	 * if ecc_opt is UFFS_ECC_HW, flash driver must calculate and return the ecc.
	 * if ecc_opt is UFFS_ECC_HW_AUTO, do not need to return ecc.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 *
	 * \note pad 0xFF for calculating ECC if len < page_data_size
	 */
	int (*WritePageData)(uffs_Device *dev, u32 block, u32 page, const u8 *data, int len, u8 *ecc);


	/**
	 * Write [len] bytes to page spare from [ofs].
	 *
	 * \note flash driver must privide this function.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*WritePageSpare)(uffs_Device *dev, u32 block, u32 page, const u8 *spare, int ofs, int len, UBOOL eod);
	
	/**
	 * Write full page, include page data and spare.
	 *
	 * you need to pack spare within nand driver.
	 *
	 * \note if layout_opt is UFFS_LAYOUT_FLASH, flash driver must implement this function.
	 *       UFFS will use this function (if provided) prio to 'WritePageData() + WritePageSpare()'
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*WriteFullPage)(uffs_Device *dev, u32 block, u32 page, const u8* data, int len, const u8 *ts, int ts_len, const u8 *ecc);

	/**
	 * check block status.
	 *
	 * \note flash driver may maintain a bad block table to speed up bad block checking or
	 *		it will require one or two read spare I/O to check block status.
	 *
	 * \note if this function is not provided, UFFS check the block_status byte in spare.
	 *
	 * \return 1 if it's a bad block, 0 if it's not.
	 */
	int (*IsBadBlock)(uffs_Device *dev, u32 block);

	/**
	 * Mark a new bad block.
	 *
	 * \return 0 if success, otherwise return -1.
	 */
	int (*MarkBadBlock)(uffs_Device *dev, u32 block);

	/**
	 * Erase a block.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*EraseBlock)(uffs_Device *dev, u32 block);
};

/** make spare from tag store and ecc */
void uffs_FlashMakeSpare(uffs_Device *dev, uffs_TagStore *ts, const u8 *ecc, u8* spare);

/** read page spare, fill tag and ECC */
int uffs_FlashReadPageSpare(uffs_Device *dev, int block, int page, uffs_Tags *tag, u8 *ecc);

/** read page data to page buf and do ECC correct */
int uffs_FlashReadPage(uffs_Device *dev, int block, int page, uffs_Buf *buf);

/** write page data and spare */
int uffs_FlashWritePageCombine(uffs_Device *dev, int block, int page, uffs_Buf *buf, uffs_Tags *tag);

/** Mark this block as bad block */
int uffs_FlashMarkBadBlock(uffs_Device *dev, int block);

/** Is this block a bad block ? */
UBOOL uffs_FlashIsBadBlock(uffs_Device *dev, int block);

/** Erase flash block */
int uffs_FlashEraseBlock(uffs_Device *dev, int block);

/* mark a clean page as 'dirty' (and 'invalid') */
int uffs_FlashMarkDirtyPage(uffs_Device *dev, int block, int page);

/**
 * get page head info
 *
 * \return #UFFS_PAGE_INFO_IOERR if I/O error, otherwise return page info
 */
u32 uffs_FlashGetPageInfo(uffs_Device *dev, int block, int page);

/** load uffs_FileInfo from flash storage */
URET uffs_FlashReadFileinfoPhy(uffs_Device *dev, int block, int page, uffs_FileInfo *info);

/**
 * Initialize UFFS flash interface
 */
URET uffs_FlashInterfaceInit(uffs_Device *dev);

/**
 * Release UFFS flash interface
 */
URET uffs_FlashInterfaceRelease(uffs_Device *dev);

#ifdef __cplusplus
}
#endif
#endif
