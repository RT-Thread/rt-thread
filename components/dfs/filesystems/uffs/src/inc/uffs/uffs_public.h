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
#include "uffs/uffs_core.h"
#include "uffs/uffs.h"
#include "uffs/uffs_pool.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef ARRAY_SIZE
# define ARRAY_SIZE(ar) (sizeof(ar) / sizeof(ar[0]))
#endif

#ifndef offsetof
# define offsetof(T, x) ((size_t) &((T *)0)->x)
#endif
#ifndef container_of
#define container_of(p, T, x) ((T *)((char *)(p) - offsetof(T,x)))
#endif

/** 
 * \def MAX_FILENAME_LENGTH 
 * \note Be careful: it's part of the physical format (see: uffs_FileInfoSt.name)
 *    !!DO NOT CHANGE IT AFTER FILE SYSTEM IS FORMATED!!
 */
#define MAX_FILENAME_LENGTH         128

/** \note 8-bits attr goes to uffs_dirent::d_type */
#define FILE_ATTR_DIR       (1 << 7)    //!< attribute for directory
#define FILE_ATTR_WRITE     (1 << 0)    //!< writable


/**
 * \structure uffs_FileInfoSt
 * \brief file/dir entry info in physical storage format
 */
struct uffs_FileInfoSt {
    u32 attr;               //!< file/dir attribute
    u32 create_time;
    u32 last_modify;
    u32 access;
    u32 reserved;
    u32 name_len;           //!< length of file/dir name
    char name[MAX_FILENAME_LENGTH];
}; //6*4 + sizeof(name) = 24 + 128 = 152 Bytes
typedef struct uffs_FileInfoSt uffs_FileInfo;

/**
 * \struct uffs_ObjectInfoSt
 * \brief object info
 */
typedef struct uffs_ObjectInfoSt {
    uffs_FileInfo info;
    u32 len;                //!< length of file
    u16 serial;             //!< object serial num
} uffs_ObjectInfo;


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
 * \struct uffs_TagsSt
 */
struct uffs_TagsSt {
	struct uffs_TagStoreSt s;		/* store must be the first member */

	/** data_sum for file or dir name */
	u16 data_sum;

	/** internal used */
	u8 seal_byte;			//!< seal byte.
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

#define TAG_IS_DIRTY(tag) (*((u32 *) &((tag)->s)) != 0xFFFFFFFF)	// tag is dirty if first 4 bytes not all 0xFF
#define TAG_IS_VALID(tag) ((tag)->s.valid == TAG_VALID)
#define TAG_IS_SEALED(tag) ((tag)->seal_byte != 0xFF)

#define TAG_IS_GOOD(tag) (TAG_IS_SEALED(tag) && TAG_IS_VALID(tag))

#define TAG_VALID_BIT(tag) (tag)->s.valid
#define TAG_DIRTY_BIT(tag) (tag)->s.dirty
#define TAG_SERIAL(tag) (tag)->s.serial
#define TAG_PARENT(tag) (tag)->s.parent
#define TAG_PAGE_ID(tag) (tag)->s.page_id
#define TAG_DATA_LEN(tag) (tag)->s.data_len
#define TAG_TYPE(tag) (tag)->s.type
#define TAG_BLOCK_TS(tag) (tag)->s.block_ts
#define SEAL_TAG(tag) (tag)->seal_byte = 0

int uffs_GetFirstBlockTimeStamp(void);
int uffs_GetNextBlockTimeStamp(int prev);
UBOOL uffs_IsSrcNewerThanObj(int src, int obj);


#include "uffs_device.h"



/********************************** debug & error *************************************/
#define UFFS_MSG_NOISY		-1
#define UFFS_MSG_NORMAL		0
#define UFFS_MSG_SERIOUS	1
#define UFFS_MSG_DEAD		2
#define UFFS_MSG_NOMSG		100

#define TENDSTR "\n"

#if !defined(RT_THREAD)
struct uffs_DebugMsgOutputSt;
URET uffs_InitDebugMessageOutput(struct uffs_DebugMsgOutputSt *ops, int msg_level);
void uffs_DebugSetMessageLevel(int msg_level);

void uffs_DebugMessage(int level, const char *prefix, const char *suffix, const char *errFmt, ...);
void uffs_AssertCall(const char *file, int line, const char *msg, ...);
#else

#define UFFS_DBG_LEVEL  UFFS_MSG_NORMAL

#ifdef CONFIG_ENABLE_UFFS_DEBUG_MSG
#define uffs_DebugMessage(level, prefix, suffix, errFmt, ...) do { \
	if (level >= UFFS_DBG_LEVEL) \
		rt_kprintf(prefix errFmt suffix, ##__VA_ARGS__); \
} while(0)

#define uffs_AssertCall(file, line, msg, ...) \
	rt_kprintf("ASSERT %s:%d - :" msg "\n", (const char *)file, (int)line, ##__VA_ARGS__)
#else
#define uffs_DebugMessage(level, prefix, suffix, errFmt, ...)
#define uffs_AssertCall(file, line, msg, ...)
#endif //CONFIG_ENABLE_UFFS_DEBUG_MSG
#endif //RT_THREAD

#ifdef _COMPILER_DO_NOT_SUPPORT_MACRO_VALIST_REPLACE_
/* For those compilers do not support valist parameter replace in macro define */
void uffs_Perror(int level, const char *fmt, ...);
void uffs_PerrorRaw(int level, const char *fmt, ...);
UBOOL uffs_Assert(UBOOL expr, const char *fmt, ...);
#else

#if !defined(RT_THREAD)
#define uffs_Perror(level, fmt, ... ) \
	uffs_DebugMessage(level, PFX, TENDSTR, fmt, ## __VA_ARGS__)

#define uffs_PerrorRaw(level, fmt, ... ) \
	uffs_DebugMessage(level, NULL, NULL, fmt, ## __VA_ARGS__)

#else

#ifdef CONFIG_ENABLE_UFFS_DEBUG_MSG

#define uffs_Perror(level, fmt, ... ) do{\
	if (level >= UFFS_DBG_LEVEL) \
		rt_kprintf(PFX fmt TENDSTR, ##__VA_ARGS__); \
} while(0)

#define uffs_PerrorRaw(level, fmt, ... ) do{\
	if (level >= UFFS_DBG_LEVEL) \
		rt_kprintf(fmt, ##__VA_ARGS__); \
} while(0)
#else
#define uffs_Perror(level, fmt, ... )
#define uffs_PerrorRaw(level, fmt, ... )
#endif // CONFIG_ENABLE_UFFS_DEBUG_MSG
#endif // RT_THREAD

#define uffs_Assert(expr, msg, ...) \
	((expr) ? U_TRUE : (uffs_AssertCall(__FILE__, __LINE__, msg, ## __VA_ARGS__), U_FALSE))

#endif //_COMPILER_DO_NOT_SUPPORT_MACRO_VALIST_REPLACE_

#define uffs_Panic() \
	do { \
		uffs_AssertCall(__FILE__, __LINE__, "Bam !!\n"); \
		while(1); \
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

/** 
 * \def UFFS_INVALID_BLOCK
 * \brief macro for invalid block number
 */
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
u16 uffs_FindFirstFreePage(uffs_Device *dev, uffs_BlockInfo *bc, u16 pageFrom);
u16 uffs_FindPageInBlockWithPageId(uffs_Device *dev, uffs_BlockInfo *bc, u16 page_id);

u8 uffs_MakeSum8(const void *p, int len);
u16 uffs_MakeSum16(const void *p, int len);
URET uffs_CreateNewFile(uffs_Device *dev, u16 parent, u16 serial, uffs_BlockInfo *bc, uffs_FileInfo *fi);

int uffs_GetBlockFileDataLength(uffs_Device *dev, uffs_BlockInfo *bc, u8 type);
UBOOL uffs_IsPageErased(uffs_Device *dev, uffs_BlockInfo *bc, u16 page);
int uffs_GetFreePagesCount(uffs_Device *dev, uffs_BlockInfo *bc);
UBOOL uffs_IsDataBlockReguFull(uffs_Device *dev, uffs_BlockInfo *bc);
UBOOL uffs_IsThisBlockUsed(uffs_Device *dev, uffs_BlockInfo *bc);

int uffs_GetBlockTimeStamp(uffs_Device *dev, uffs_BlockInfo *bc);

int uffs_GetDeviceUsed(uffs_Device *dev);
int uffs_GetDeviceFree(uffs_Device *dev);
int uffs_GetDeviceTotal(uffs_Device *dev);

URET uffs_LoadMiniHeader(uffs_Device *dev, int block, u16 page, struct uffs_MiniHeaderSt *header);


/* some functions from uffs_fd.c */
void uffs_FdSignatureIncrease(void);
URET uffs_DirEntryBufInit(void);
URET uffs_DirEntryBufRelease(void);
uffs_Pool * uffs_DirEntryBufGetPool(void);
int uffs_DirEntryBufPutAll(uffs_Device *dev);


/************************************************************************/
/*  init functions                                                                     */
/************************************************************************/
URET uffs_InitDevice(uffs_Device *dev);
URET uffs_ReleaseDevice(uffs_Device *dev);

URET uffs_InitFileSystemObjects(void);
URET uffs_ReleaseFileSystemObjects(void);


#ifdef __cplusplus
}
#endif
#endif	// _UFFS_PUBLIC_H_

