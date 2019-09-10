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
 * \file uffs_buf.h
 * \brief page buffers
 * \author Ricky Zheng
 */

#ifndef UFFS_BUF_H
#define UFFS_BUF_H

#include "uffs/uffs_types.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_tree.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif
	
#define CLONE_BUF_MARK		0xffff		//!< set uffs_BufSt::ref_count to this for a 'cloned' buffer

/** for uffs_BufSt::mark */
#define UFFS_BUF_EMPTY		0			//!< buffer is empty
#define UFFS_BUF_VALID		1			//!< buffer is holding valid data
#define UFFS_BUF_DIRTY		2			//!< buffer data is modified

/** for uffs_BufSt::ext_mark */
#define UFFS_BUF_EXT_MARK_TRUNC_TAIL 1	//!< the last page of file (when truncating a file)

/** uffs page buffer */
struct uffs_BufSt{
	struct uffs_BufSt *next;			//!< link to next buffer
	struct uffs_BufSt *prev;			//!< link to previous buffer
	struct uffs_BufSt *next_dirty;		//!< link to next dirty buffer
	struct uffs_BufSt *prev_dirty;		//!< link to previous dirty buffer
	u8 type;							//!< #UFFS_TYPE_DIR or #UFFS_TYPE_FILE or #UFFS_TYPE_DATA
	u8 ext_mark;						//!< extension mark. 
	u16 parent;							//!< parent serial
	u16 serial;							//!< serial 
	u16 page_id;						//!< page id 
	u16 mark;							//!< #UFFS_BUF_EMPTY or #UFFS_BUF_VALID, or #UFFS_BUF_DIRTY ?
	u16 ref_count;						//!< reference counter, or #CLONE_BUF_MARK for a cloned buffer
	u16 data_len;						//!< length of data
	u16 check_sum;						//!< checksum field
	u8 * data;							//!< data buffer
	u8 * header;						//!< header
};

#define uffs_BufIsFree(buf) (buf->ref_count == 0 ? U_TRUE : U_FALSE)

/** initialize page buffers */
URET uffs_BufInit(struct uffs_DeviceSt *dev, int buf_max, int dirty_buf_max);

/** release page buffers */
URET uffs_BufReleaseAll(struct uffs_DeviceSt *dev);

/** find the page buffer, move to link list head if found */
uffs_Buf * uffs_BufGet(struct uffs_DeviceSt *dev, u16 parent, u16 serial, u16 page_id);
uffs_Buf *uffs_BufGetEx(struct uffs_DeviceSt *dev, u8 type, TreeNode *node, u16 page_id, int oflag);

/** alloc a new page buffer */
uffs_Buf *uffs_BufNew(struct uffs_DeviceSt *dev, u8 type, u16 parent, u16 serial, u16 page_id);

/** find the page buffer (not affect the reference counter) */
uffs_Buf * uffs_BufFind(uffs_Device *dev, u16 parent, u16 serial, u16 page_id);

/** find the page buffer from #start (not affect the reference counter) */
uffs_Buf * uffs_BufFindFrom(uffs_Device *dev, uffs_Buf *start,
						u16 parent, u16 serial, u16 page_id);

/** put page buffer back to pool, called in pair with #uffs_Get,#uffs_GetEx or #uffs_BufNew */
URET uffs_BufPut(uffs_Device *dev, uffs_Buf *buf);

/** increase buffer references */
void uffs_BufIncRef(uffs_Buf *buf);

/** decrease buffer references */
void uffs_BufDecRef(uffs_Buf *buf);

/** write data to a page buffer */
URET uffs_BufWrite(struct uffs_DeviceSt *dev, uffs_Buf *buf, void *data, u32 ofs, u32 len);

/** read data from a page buffer */
URET uffs_BufRead(struct uffs_DeviceSt *dev, uffs_Buf *buf, void *data, u32 ofs, u32 len);

/** mark buffer as #UFFS_BUF_EMPTY if ref_count == 0, and discard all data it holds */
void uffs_BufMarkEmpty(uffs_Device *dev, uffs_Buf *buf);

/** if there is no free dirty group slot, flush the most dirty group */
URET uffs_BufFlush(struct uffs_DeviceSt *dev);
URET uffs_BufFlushEx(struct uffs_DeviceSt *dev, UBOOL force_block_recover);

/** flush dirty group */
URET uffs_BufFlushGroup(struct uffs_DeviceSt *dev, u16 parent, u16 serial);
URET uffs_BufFlushGroupEx(struct uffs_DeviceSt *dev, u16 parent, u16 serial, UBOOL force_block_recover);

/** find free dirty group slot */
int uffs_BufFindFreeGroupSlot(struct uffs_DeviceSt *dev);

/** find the dirty group slot */
int uffs_BufFindGroupSlot(struct uffs_DeviceSt *dev, u16 parent, u16 serial);

/** lock dirty group */
URET uffs_BufLockGroup(struct uffs_DeviceSt *dev, int slot);

/** unlock dirty group */
URET uffs_BufUnLockGroup(struct uffs_DeviceSt *dev, int slot);

/** flush most dirty group */
URET uffs_BufFlushMostDirtyGroup(struct uffs_DeviceSt *dev);

/** flush all groups under the same parent number */
URET uffs_BufFlushGroupMatchParent(struct uffs_DeviceSt *dev, u16 parent);

/** flush all page buffers */
URET uffs_BufFlushAll(struct uffs_DeviceSt *dev);

/** no one holding any page buffer ? safe to release page buffers */
UBOOL uffs_BufIsAllFree(struct uffs_DeviceSt *dev);

/** are all page buffer marked with #UFFS_BUF_EMPTY ? */
UBOOL uffs_BufIsAllEmpty(struct uffs_DeviceSt *dev);

/** mark all page buffer as #UFFS_BUF_EMPTY */
URET uffs_BufSetAllEmpty(struct uffs_DeviceSt *dev);

/** clone a page buffer */
uffs_Buf * uffs_BufClone(struct uffs_DeviceSt *dev, uffs_Buf *buf);

/** release a cloned page buffer, call in pair with #uffs_BufClone */
URET uffs_BufFreeClone(uffs_Device *dev, uffs_Buf *buf);

/** load physical storage data to page buffer */
URET uffs_BufLoadPhyData(uffs_Device *dev, uffs_Buf *buf, u32 block, u32 page);

/** load physical storage data to page buffer withouth checking ECC */
URET uffs_LoadPhyDataToBufEccUnCare(uffs_Device *dev, uffs_Buf *buf, u32 block, u32 page);

/** showing page buffers info, for debug only */
void uffs_BufInspect(uffs_Device *dev);

#ifdef __cplusplus
}
#endif


#endif
