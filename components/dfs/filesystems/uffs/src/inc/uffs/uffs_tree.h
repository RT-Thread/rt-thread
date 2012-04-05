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

#ifndef _UFFS_TREE_H_
#define _UFFS_TREE_H_

#include "uffs/uffs_types.h"
#include "uffs/uffs_pool.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif

#define UFFS_TYPE_DIR		0
#define UFFS_TYPE_FILE		1
#define UFFS_TYPE_DATA		2
#define UFFS_TYPE_RESV		3
#define UFFS_TYPE_INVALID	0xFF

struct uffs_NodeTypeNameMapSt {
	int type;
	const char *name;
};

#define UFFS_TYPE_NAME_MAP { \
	{UFFS_TYPE_DIR, "DIR"}, \
	{UFFS_TYPE_FILE, "FILE"}, \
	{UFFS_TYPE_DATA, "DATA"}, \
	{UFFS_TYPE_RESV, "RESV"}, \
	{UFFS_TYPE_INVALID, "INVALID"} \
}

struct BlockListSt {	/* 12 bytes */
	struct uffs_TreeNodeSt * next;
	struct uffs_TreeNodeSt * prev;
	u16 block;
	union {
		u16 serial;    /* for suspended block list */
		u8 need_check; /* for erased block list */
	} u;
};

struct DirhSt {		/* 8 bytes */
	u16 checksum;	/* check sum of dir name */
	u16 block;
	u16 parent;
	u16 serial;
};


struct FilehSt {	/* 12 bytes */
	u16 block;
	u16 checksum;	/* check sum of file name */
	u16 parent;
	u16 serial;
	u32 len;		/* file length total */
};

struct FdataSt {	/* 10 bytes */
	u16 block;
	u16 parent;
	u32 len;		/* file data length on this block */
	u16 serial;
};

//UFFS TreeNode (14 or 16 bytes)
typedef struct uffs_TreeNodeSt {
	union {
		struct BlockListSt list;
		struct DirhSt dir;
		struct FilehSt file;
		struct FdataSt data;
	} u;
	u16 hash_next;		
	u16 hash_prev;			
} TreeNode;


//TODO: UFFS2 Tree structures
/*
struct FdataSt {
	u32 len;
};

struct filebSt {
	u16 bls;		//how many blocks this file contents ...
	u8 offs;		//the offset of this file header on FILE block
	u8 sum;			//short sum of file name
};

//Extra data structure for storing file length information
struct FilehSt {
	u32 len;
};

//UFFS2 TreeNode (12 bytes)
typedef struct uffs_TreeNodeSt {
	u16 nextIdx;
	u16 block;
	u16 parent;
	u16 serial;
	union {
		struct FilehSt h;
		struct filedSt file;
		struct data;
	} u;
} TreeNode;

*/


#define EMPTY_NODE 0xffff				//!< special index num of empty node.

#define ROOT_DIR_SERIAL	0				//!< serial num of root dir
#define MAX_UFFS_FSN			0x3ff	//!< maximum dir|file serial number (uffs_TagStore#parent: 10 bits)
#define MAX_UFFS_FDN			0x3fff	//!< maximum file data block serial numbers (uffs_TagStore#serial: 14 bits)
#define PARENT_OF_ROOT			0xfffd	//!< parent of ROOT ? kidding me ...
#define INVALID_UFFS_SERIAL		0xffff	//!< invalid serial num

#define DIR_NODE_HASH_MASK		0x1f
#define DIR_NODE_ENTRY_LEN		(DIR_NODE_HASH_MASK + 1)

#define FILE_NODE_HASH_MASK		0x3f
#define FILE_NODE_ENTRY_LEN		(FILE_NODE_HASH_MASK + 1)

#define DATA_NODE_HASH_MASK		0x1ff
#define DATA_NODE_ENTRY_LEN		(DATA_NODE_HASH_MASK + 1)
#define FROM_IDX(idx, pool)		((TreeNode *)uffs_PoolGetBufByIndex(pool, idx))
#define TO_IDX(p, pool)			((u16)uffs_PoolGetIndex(pool, (void *) p))


#define GET_FILE_HASH(serial)			(serial & FILE_NODE_HASH_MASK)
#define GET_DIR_HASH(serial)			(serial & DIR_NODE_HASH_MASK)
#define GET_DATA_HASH(parent, serial)	((parent + serial) & DATA_NODE_HASH_MASK)


struct uffs_TreeSt {
	TreeNode *erased;					//!< erased block list head
	TreeNode *erased_tail;				//!< erased block list tail
	TreeNode *suspend;					//!< suspended block list
	int erased_count;					//!< erased block counter
	TreeNode *bad;						//!< bad block list
	int bad_count;						//!< bad block count
	u16 dir_entry[DIR_NODE_ENTRY_LEN];
	u16 file_entry[FILE_NODE_ENTRY_LEN];
	u16 data_entry[DATA_NODE_ENTRY_LEN];
	u16 max_serial;
};


URET uffs_TreeInit(uffs_Device *dev);
URET uffs_TreeRelease(uffs_Device *dev);
URET uffs_BuildTree(uffs_Device *dev);
u16 uffs_FindFreeFsnSerial(uffs_Device *dev);
TreeNode * uffs_TreeFindFileNode(uffs_Device *dev, u16 serial);
TreeNode * uffs_TreeFindFileNodeWithParent(uffs_Device *dev, u16 parent);
TreeNode * uffs_TreeFindDirNode(uffs_Device *dev, u16 serial);
TreeNode * uffs_TreeFindDirNodeWithParent(uffs_Device *dev, u16 parent);
TreeNode * uffs_TreeFindFileNodeByName(uffs_Device *dev, const char *name, u32 len, u16 sum, u16 parent);
TreeNode * uffs_TreeFindDirNodeByName(uffs_Device *dev, const char *name, u32 len, u16 sum, u16 parent);
TreeNode * uffs_TreeFindDataNode(uffs_Device *dev, u16 parent, u16 serial);


TreeNode * uffs_TreeFindDirNodeByBlock(uffs_Device *dev, u16 block);
TreeNode * uffs_TreeFindFileNodeByBlock(uffs_Device *dev, u16 block);
TreeNode * uffs_TreeFindDataNodeByBlock(uffs_Device *dev, u16 block);
TreeNode * uffs_TreeFindErasedNodeByBlock(uffs_Device *dev, u16 block);
TreeNode * uffs_TreeFindBadNodeByBlock(uffs_Device *dev, u16 block);

void uffs_TreeSuspendAdd(uffs_Device *dev, TreeNode *node);
TreeNode * uffs_TreeFindSuspendNode(uffs_Device *dev, u16 serial);
void uffs_TreeRemoveSuspendNode(uffs_Device *dev, TreeNode *node);

#define SEARCH_REGION_DIR		1
#define SEARCH_REGION_FILE		2
#define SEARCH_REGION_DATA		4
#define SEARCH_REGION_BAD		8
#define SEARCH_REGION_ERASED	16
TreeNode * uffs_TreeFindNodeByBlock(uffs_Device *dev, u16 block, int *region);



UBOOL uffs_TreeCompareFileName(uffs_Device *dev, const char *name, u32 len, u16 sum, TreeNode *node, int type);

TreeNode * uffs_TreeGetErasedNode(uffs_Device *dev);

void uffs_InsertNodeToTree(uffs_Device *dev, u8 type, TreeNode *node);
void uffs_InsertToErasedListHead(uffs_Device *dev, TreeNode *node);
void uffs_TreeInsertToErasedListTail(uffs_Device *dev, TreeNode *node);
void uffs_TreeInsertToErasedListTailEx(uffs_Device *dev, TreeNode *node, int need_check);
void uffs_TreeInsertToBadBlockList(uffs_Device *dev, TreeNode *node);

void uffs_BreakFromEntry(uffs_Device *dev, u8 type, TreeNode *node);

void uffs_TreeSetNodeBlock(u8 type, TreeNode *node, u16 block);


#ifdef __cplusplus
}
#endif



#endif


