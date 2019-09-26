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
#include "uffs/uffs_core.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_fs.h"

#ifdef __cplusplus
extern "C"{
#endif


/** ECC options (uffs_StorageAttrSt.ecc_opt) */
#define UFFS_ECC_NONE		0	//!< do not use ECC
#define UFFS_ECC_SOFT		1	//!< UFFS calculate the ECC
#define UFFS_ECC_HW			2	//!< Flash driver(or by hardware) calculate the ECC
#define UFFS_ECC_HW_AUTO	3	//!< Hardware calculate the ECC and automatically write to spare.

#define UFFS_ECC_OPTION_STRING \
	{ "none", "soft", "hw", "auto" }	// index is the ecc option value.

/** spare layout options (uffs_StorageAttrSt.layout_opt) */
#define UFFS_LAYOUT_UFFS	0	//!< do layout by dev->attr information
#define UFFS_LAYOUT_FLASH	1	//!< flash driver do the layout

#define UFFS_SPARE_LAYOUT_SIZE	6	//!< maximum spare layout array size, 2 segments

/** flash operation return code */
#define UFFS_FLASH_NO_ERR		0		//!< no error
#define UFFS_FLASH_ECC_OK		1		//!< bit-flip found, but corrected by ECC
#define UFFS_FLASH_NOT_SEALED	2		//!< page spare area is not sealed properly (only for ReadPageWithLayout())
#define UFFS_FLASH_IO_ERR		-1		//!< I/O error
#define UFFS_FLASH_ECC_FAIL		-2		//!< ECC failed
#define UFFS_FLASH_BAD_BLK		-3		//!< bad block
#define UFFS_FLASH_CRC_ERR		-4		//!< CRC failed
#define UFFS_FLASH_UNKNOWN_ERR	-100	//!< unkown error?

#define UFFS_FLASH_HAVE_ERR(e)		((e) < 0)

#if defined(CONFIG_BAD_BLOCK_POLICY_STRICT)
# define UFFS_FLASH_IS_BAD_BLOCK(e)	\
	((e) == UFFS_FLASH_ECC_FAIL || (e) == UFFS_FLASH_ECC_OK || (e) == UFFS_FLASH_BAD_BLK || (e) == UFFS_FLASH_CRC_ERR)
#else
# define UFFS_FLASH_IS_BAD_BLOCK(e)	\
	((e) == UFFS_FLASH_ECC_FAIL || (e) == UFFS_FLASH_BAD_BLK || (e) == UFFS_FLASH_CRC_ERR)
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
	int ecc_size;			//!< ecc size in bytes
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
	 * Initilize flash driver, called once when UFFS initilize partition
	 *
	 * \return 0 if no error, return -1 when failed.
	 *
	 * \note This function is optional.
	 */
	int (*InitFlash)(uffs_Device *dev);

	/**
	 * Release flash driver, called once when UFFS unmount partition
	 *
	 * \return 0 if no error, return -1 when failed.
	 *
	 * \note This function is optional.
	 */
	int (*ReleaseFlash)(uffs_Device *dev);

	/**
	 * Read a full nand page, UFFS do the layout.
	 * 
	 * \param[out] ecc ecc of page data
	 *   if ecc_opt is UFFS_ECC_HW, flash driver must calculate and return ecc of data(if ecc != NULL).
	 *   if ecc_opt is UFFS_ECC_HW_AUTO, flash driver do ecc correction before return data and flash driver do not need to return ecc.
	 *   if ecc_opt is UFFS_ECC_NONE or UFFS_ECC_SOFT, flash driver do not need to calculate data ecc and return ecc.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success and/or has no flip bits.
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_ECC_FAIL: page data has flip bits and ecc correct failed (when ecc_opt == UFFS_ECC_HW_AUTO)
	 *			#UFFS_FLASH_ECC_OK: page data has flip bits and corrected by ecc (when ecc_opt == UFFS_ECC_HW_AUTO)
	 *          #UFFS_FLASH_BAD_BLK: if the block is a bad block (e.g., the bad block mark byte is not 0xFF).
	 *
	 * \note if data is NULL, do not return data; if spare is NULL, do not return spare; if both data and spare are all NULL,
	 *       then read bad block mark and return UFFS_FLASH_BAD_BLK if bad block mark is not 0xFF.
	 *
	 * \note pad 0xFF for calculating ECC if len < page_data_size
	 */
	int (*ReadPage)(uffs_Device *dev, u32 block, u32 page, u8 *data, int data_len, u8 *ecc,
						u8 *spare, int spare_len);

	/**
	 * Read a full nand page, driver do the layout.
	 *
	 * \param[out] ecc ecc of page data
	 *   if ecc_opt is UFFS_ECC_HW, flash driver must calculate and return ecc of data(if ecc != NULL).
	 *   if ecc_opt is UFFS_ECC_HW_AUTO, flash driver do ecc correction before return data and flash driver do not need to return ecc.
	 *   if ecc_opt is UFFS_ECC_NONE or UFFS_ECC_SOFT, flash driver do not need calculate data ecc and return ecc.
	 *
	 * \param[out] ecc_store ecc store on spare area
	 *   if ecc_opt is UFFS_ECC_NONE or UFFS_ECC_HW_AUTO, do not need to return ecc_store.
	 *
	 * \note flash driver must provide this function if layout_opt is UFFS_LAYOUT_FLASH.
	 *       UFFS will use this function (if exist) prio to 'ReadPageSpare()'
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_ECC_FAIL: page data has flip bits and ecc correct failed (when ecc_opt == UFFS_ECC_HW_AUTO)
	 *			#UFFS_FLASH_ECC_OK: page data has flip bits and corrected by ecc (when ecc_opt == UFFS_ECC_HW_AUTO)
	 *          #UFFS_FLASH_BAD_BLK: if the block is a bad block (e.g., the bad block mark byte is not 0xFF)
	 *			#UFFS_FLASH_NOT_SEALED: if the page spare is not sealed properly
	 *
	 * \note if data is NULL, do not return data; if ts is NULL, do not read tag; if both data and ts are NULL,
	 *       then read bad block mark and return UFFS_FLASH_BAD_BLK if bad block mark is not 0xFF.
	 *
	 * \note flash driver DO NOT need to do ecc correction for tag,
	 *		UFFS will take care of tag ecc.
	 */
	int (*ReadPageWithLayout)(uffs_Device *dev, u32 block, u32 page, u8* data, int data_len, u8 *ecc,
									uffs_TagStore *ts, u8 *ecc_store);

	/**
	 * Write a full page, UFFS do the layout for spare area.
	 *
	 * \note If you have ecc_opt UFFS_ECC_HW or UFFS_ECC_HW_AUTO, you MUST implement WritePageWithLayout().
	 *       Implement WritePage() function if you have ecc_opt UFFS_ECC_NONE or UFFS_ECC_SOFT and
	 *       WritePageWithLayout() is not implemented.
	 *
	 * \note If data == NULL && spare == NULL, driver should mark this block as a 'bad block'.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*WritePage)(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *spare, int spare_len);

	/**
	 * Write full page, flash driver do the layout for spare area.
	 *
	 * \note if layout_opt is UFFS_LAYOUT_FLASH or ecc_opt is UFFS_ECC_HW/UFFS_ECC_HW_AUTO, flash driver MUST implement
	 *       this function. UFFS will use this function (if provided) prio to 'WritePage()'
	 *
	 * \param[in] ecc ecc of data. if ecc_opt is UFFS_ECC_SOFT and this function is implemented,
	 *                UFFS will calculate page data ecc and pass it to WritePageWithLayout().
	 *            if ecc_opt is UFFS_ECC_NONE/UFFS_ECC_HW/UFFS_ECC_HW_AUTO, UFFS pass ecc = NULL.
	 *
	 * \note If data == NULL && ts == NULL, driver should mark this block as a 'bad block'.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*WritePageWithLayout)(uffs_Device *dev, u32 block, u32 page,
							const u8 *data, int data_len, const u8 *ecc, const uffs_TagStore *ts);

	/**
	 * Check block status.
	 *
	 * \note flash driver may maintain a bad block table to speed up bad block checking or
	 *		it will require one or two read spare I/O to check block status.
	 *
	 * \note if this function is not implented by driver, UFFS check the block_status byte in spare.
	 *
	 * \return 1 if it's a bad block, 0 if it's not.
	 */
	int (*IsBadBlock)(uffs_Device *dev, u32 block);

	/**
	 * Mark a new bad block.
	 *
	 * \note if this function is not implemented, UFFS mark bad block by call 'WritePage()/WritePageWithLayout()'
	 *       with: data == NULL && spare == NULL && ts == NULL.
	 *
	 * \return 0 if success, otherwise return -1.
	 */
	int (*MarkBadBlock)(uffs_Device *dev, u32 block);

	/**
	 * Erase a block, driver MUST implement this function.
	 *
	 * \return	#UFFS_FLASH_NO_ERR: success
	 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
	 *			#UFFS_FLASH_BAD_BLK: a bad block detected.
	 */
	int (*EraseBlock)(uffs_Device *dev, u32 block);
};

/** make spare from tag store and ecc */
void uffs_FlashMakeSpare(uffs_Device *dev, const uffs_TagStore *ts, const u8 *ecc, u8* spare);

/** unload tag and ecc from spare */
void uffs_FlashUnloadSpare(uffs_Device *dev, const u8 *spare, struct uffs_TagStoreSt *ts, u8 *ecc);

/** read page spare and fill to tag */
int uffs_FlashReadPageTag(uffs_Device *dev, int block, int page, uffs_Tags *tag);

/** read page data to page buf and do ECC correct */
int uffs_FlashReadPage(uffs_Device *dev, int block, int page, uffs_Buf *buf, UBOOL skip_ecc);

/** write page data and spare */
int uffs_FlashWritePageCombine(uffs_Device *dev, int block, int page, uffs_Buf *buf, uffs_Tags *tag);

/** Mark this block as bad block */
int uffs_FlashMarkBadBlock(uffs_Device *dev, int block);

/** Is this block a bad block ? */
UBOOL uffs_FlashIsBadBlock(uffs_Device *dev, int block);

/** Erase flash block */
int uffs_FlashEraseBlock(uffs_Device *dev, int block);

/* mark a clean page as 'dirty' (and 'invalid') */
int uffs_FlashMarkDirtyPage(uffs_Device *dev, uffs_BlockInfo *bc, int page);

/* check if the block pages are all clean */
URET uffs_FlashCheckErasedBlock(uffs_Device *dev, int block);
	
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
