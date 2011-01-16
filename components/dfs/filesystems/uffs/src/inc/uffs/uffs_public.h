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
 * \brief public data structures for uffs
 * \author Ricky Zheng
 */

#ifndef _UFFS_PUBLIC_H_
#define _UFFS_PUBLIC_H_

#include "uffs/uffs_types.h"
#include "uffs/uffs_config.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * \struct uffs_TagStoreSt
 * \brief uffs tag, 8 bytes, will be store in page spare area.
 */
struct uffs_TagStoreSt {
	u32 dirty:1;		//!< 0: dirty, 1: clear
	u32 valid:1;		//!< 0: valid, 1: invalid
	u32 type:2;			//!< block type: #UFFS_TYPE_DIR, #UFFS_TYPE_FILE, #UFFS_TYPE_DATA
	u32 block_ts:2;		//!< time stamp of block;
	u32 data_len:12;	//!< length of page data
	u32 serial:14;		//!< serial number

	u32 parent:10;		//!< parent's serial number
	u32 page_id:6;		//!< page id
	u32 reserved:4;		//!< reserved, for UFFS2
	u32 tag_ecc:12;		//!< tag ECC
};

#define TAG_ECC_DEFAULT (0xFFF)	//!< 12-bit '1'

/**
 * \struct uffs_TagStoreSt_8
 * \brief this data structure describes the page status, for 8 bytes page spare.
 * \note there is no tag ecc for this !
 */
struct uffs_TagStoreSt_8 {
	u32 dirty:1;			//!< 0: dirty, 1: clear
	u32 valid:1;			//!< 0: valid, 1: invalid
	u32 type:2;				//!< block type: #UFFS_TYPE_DIR, #UFFS_TYPE_FILE, #UFFS_TYPE_DATA
	u32 block_ts:2;			//!< time stamp of block;
	u32 page_id:5;			//!< page id
	u32 parent:7;			//!< parent's serial number
	u32 serial:8;			//!< serial number
	u32 data_len:8;			//!< length of page data
};

/** 
 * \struct uffs_TagsSt
 */
struct uffs_TagsSt {
	struct uffs_TagStoreSt s;		/* store must be the first member */

	/** data_sum for file or dir name */
	u16 data_sum;

	/**
	 * block_status is not covered by tag_ecc.
	 * it's loaded from flash but not directly write to flash.
	 */
	u8 block_status;

	/** internal used */
	u8 _dirty:1;			//!< raw data, before doing ecc correction
	u8 _valid:1;			//!< raw data, before doing ecc correction
};

/** 
 * \struct uffs_MiniHeaderSt
 * \brief the mini header resides on the head of page data
 */
struct uffs_MiniHeaderSt {
	u8 status;
	u8 reserved;
	u16 crc;
};


/** uffs_TagsSt.dirty */
#define TAG_VALID		0
#define TAG_INVALID		1

/** uffs_TagsSt.valid */
#define TAG_DIRTY		0
#define TAG_CLEAR		1

#define TAG_IS_DIRTY(tag) ((tag)->s.dirty == TAG_DIRTY)
#define TAG_IS_VALID(tag) ((tag)->s.valid == TAG_VALID)
#define TAG_SERIAL(tag) (tag)->s.serial
#define TAG_PARENT(tag) (tag)->s.parent
#define TAG_PAGE_ID(tag) (tag)->s.page_id
#define TAG_DATA_LEN(tag) (tag)->s.data_len
#define TAG_TYPE(tag) (tag)->s.type
#define TAG_BLOCK_TS(tag) (tag)->s.block_ts


int uffs_GetFirstBlockTimeStamp(void);
int uffs_GetNextBlockTimeStamp(int prev);
UBOOL uffs_IsSrcNewerThanObj(int src, int obj);


#include "uffs_device.h"



/********************************** debug & error *************************************/
#define UFFS_ERR_NOISY		-1
#define UFFS_ERR_NORMAL		0
#define UFFS_ERR_SERIOUS	1
#define UFFS_ERR_DEAD		2

#define TENDSTR "\n"

//#define UFFS_DBG_LEVEL	UFFS_ERR_NORMAL	
#define UFFS_DBG_LEVEL	UFFS_ERR_DEAD	

void uffs_DebugMessage(int level, const char *prefix, const char *suffix, const char *errFmt, ...);

#define uffs_Perror(level, fmt, ... ) \
	uffs_DebugMessage(level, PFX, TENDSTR, fmt, ## __VA_ARGS__)

#define uffs_PerrorRaw(level, fmt, ... ) \
	uffs_DebugMessage(level, NULL, NULL, fmt, ## __VA_ARGS__)



void uffs_AssertCall(const char *file, int line, const char *msg);

#define uffs_Assert(expr, msg)												\
	do {																	\
		if (!(expr))														\
			uffs_AssertCall(__FILE__, __LINE__, msg);						\
	} while(0)

/********************************** NAND **********************************************/
//NAND flash specific file must implement these interface
URET uffs_LoadPageSpare(uffs_Device *dev, int block, int page, uffs_Tags *tag);
URET uffs_WritePageSpare(uffs_Device *dev, int block, int page, uffs_Tags *tag);
URET uffs_MakePageValid(uffs_Device *dev, int block, int page, uffs_Tags *tag);
UBOOL uffs_IsBlockBad(uffs_Device *dev, uffs_BlockInfo *bc);

/********************************** Public defines *****************************/
/**
 * \def UFFS_ALL_PAGES 
 * \brief UFFS_ALL_PAGES if this value presented, that means the objects are all pages in the block
 */
#define UFFS_ALL_PAGES (0xffff)

/** 
 * \def UFFS_INVALID_PAGE
 * \brief macro for invalid page number
 */
#define UFFS_INVALID_PAGE	(0xfffe)
#define UFFS_INVALID_BLOCK	(0xfffe)


URET uffs_NewBlock(uffs_Device *dev, u16 block, uffs_Tags *tag, uffs_Buf *buf);
URET uffs_BlockRecover(uffs_Device *dev, uffs_BlockInfo *old, u16 newBlock);
URET uffs_PageRecover(uffs_Device *dev, 
					  uffs_BlockInfo *bc, 
					  u16 oldPage, 
					  u16 newPage, 
					  uffs_Buf *buf);
int uffs_FindFreePageInBlock(uffs_Device *dev, uffs_BlockInfo *bc);
u16 uffs_FindBestPageInBlock(uffs_Device *dev, uffs_BlockInfo *bc, u16 page);
u16 uffs_FindFirstValidPage(uffs_Device *dev, uffs_BlockInfo *bc);
u16 uffs_FindFirstFreePage(uffs_Device *dev, uffs_BlockInfo *bc, u16 pageFrom);
u16 uffs_FindPageInBlockWithPageId(uffs_Device *dev, uffs_BlockInfo *bc, u16 page_id);

u8 uffs_MakeSum8(const void *p, int len);
u16 uffs_MakeSum16(const void *p, int len);
URET uffs_CreateNewFile(uffs_Device *dev, u16 parent, u16 serial, uffs_BlockInfo *bc, uffs_FileInfo *fi);

int uffs_GetBlockFileDataLength(uffs_Device *dev, uffs_BlockInfo *bc, u8 type);
UBOOL uffs_IsPageErased(uffs_Device *dev, uffs_BlockInfo *bc, u16 page);
int uffs_GetFreePagesCount(uffs_Device *dev, uffs_BlockInfo *bc);
UBOOL uffs_IsDataBlockReguFull(uffs_Device *dev, uffs_BlockInfo *bc);

int uffs_GetBlockTimeStamp(uffs_Device *dev, uffs_BlockInfo *bc);


int uffs_GetDeviceUsed(uffs_Device *dev);
int uffs_GetDeviceFree(uffs_Device *dev);
int uffs_GetDeviceTotal(uffs_Device *dev);

URET uffs_LoadMiniHeader(uffs_Device *dev, int block, u16 page, struct uffs_MiniHeaderSt *header);


/************************************************************************/
/*  init functions                                                                     */
/************************************************************************/
URET uffs_InitDevice(uffs_Device *dev);
URET uffs_ReleaseDevice(uffs_Device *dev);


URET uffs_InitFlashClass(uffs_Device *dev);



#ifdef __cplusplus
}
#endif
#endif	// _UFFS_PUBLIC_H_

