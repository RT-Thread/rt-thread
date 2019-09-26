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
 * \file uffs_utils.c
 * \brief utilities of uffs
 * \author Ricky Zheng, created 12th May, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_version.h"
#include "uffs/uffs_badblock.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_fs.h"

#include <stdio.h>
#include <string.h>

#define PFX "util: "

#define SPOOL(dev) &((dev)->mem.spare_pool)

#ifdef CONFIG_USE_GLOBAL_FS_LOCK
static OSSEM _global_lock = OSSEM_NOT_INITED;

/* global file system lock */
void uffs_InitGlobalFsLock(void)
{
	uffs_SemCreate(&_global_lock);
}

void uffs_ReleaseGlobalFsLock(void)
{
	uffs_SemDelete(&_global_lock);
}

void uffs_GlobalFsLockLock(void)
{
	uffs_SemWait(_global_lock);
}

void uffs_GlobalFsLockUnlock(void)
{
	uffs_SemSignal(_global_lock);
}

#else

void uffs_InitGlobalFsLock(void) {}
void uffs_ReleaseGlobalFsLock(void) {}
void uffs_GlobalFsLockLock(void) {}
void uffs_GlobalFsLockUnlock(void) {}

#endif


#ifdef CONFIG_ENABLE_BAD_BLOCK_VERIFY
static void _ForceFormatAndCheckBlock(uffs_Device *dev, int block)
{
	int i, j;
	uffs_Buf *buf = NULL;
	UBOOL bad = U_TRUE;
	URET ret;
	struct uffs_FlashOpsSt *ops = dev->ops;
	struct uffs_TagStoreSt ts;
	u8 *spare = NULL;

	buf = uffs_BufClone(dev, NULL);
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"Alloc page buffer fail ! Format stoped.");
		goto ext;
	}

	spare = (u8 *)uffs_PoolGet(SPOOL(dev));
	if (spare == NULL)
		goto ext;

	//step 1: Erase, fully fill with 0x0, and check
	ret = uffs_FlashEraseBlock(dev, block);
	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		goto bad_out;

	memset(buf->header, 0, dev->com.pg_size);
	memset(&ts, 0, sizeof(ts));
	memset(spare, 0, dev->attr->spare_size);

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		if (ops->WritePageWithLayout)
			ret = ops->WritePageWithLayout(dev, block, i, buf->header, dev->com.pg_size, NULL, &ts);
		else
			ret = ops->WritePage(dev, block, i, buf->header, dev->com.pg_size, spare, dev->attr->spare_size);

		if (UFFS_FLASH_IS_BAD_BLOCK(ret))
			goto bad_out;
	}
	for (i = 0; i < dev->attr->pages_per_block; i++) {
		memset(buf->header, 0xFF, dev->com.pg_size);
		memset(&ts, 0xFF, sizeof(ts));
		memset(spare, 0xFF, dev->attr->spare_size);

		if (ops->ReadPageWithLayout) {
			ret = ops->ReadPageWithLayout(dev, block, i, buf->header, dev->com.pg_size, NULL, &ts, NULL);
			if (UFFS_FLASH_IS_BAD_BLOCK(ret))
				goto bad_out;
			for (j = 0; j < dev->com.pg_size; j++)
				if (buf->header[j] != 0)
					goto bad_out;
			for (j = 0; j < sizeof(ts); j++)
				if (((u8 *)&ts)[j] != 0)
					goto bad_out;
		}
		else {
			ret = ops->ReadPage(dev, block, i, buf->header, dev->com.pg_size, NULL, spare, dev->attr->spare_size);
			if (UFFS_FLASH_IS_BAD_BLOCK(ret))
				goto bad_out;
			for (j = 0; j < dev->com.pg_size; j++)
				if (buf->header[j] != 0)
					goto bad_out;
			for (j = 0; j < dev->attr->spare_size; j++)
				if (spare[j] != 0)
					goto bad_out;
		}
	}

	//step 2: Erase, and check
	ret = uffs_FlashEraseBlock(dev, block);
	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		goto bad_out;

	for (i = 0; i < dev->attr->pages_per_block; i++) {
		memset(buf->header, 0, dev->com.pg_size);
		memset(&ts, 0, sizeof(ts));
		memset(spare, 0, dev->attr->spare_size);

		if (ops->ReadPageWithLayout) {
			ret = ops->ReadPageWithLayout(dev, block, i, buf->header, dev->com.pg_size, NULL, &ts, NULL);
			if (UFFS_FLASH_IS_BAD_BLOCK(ret))
				goto bad_out;
			for (j = 0; j < dev->com.pg_size; j++)
				if (buf->header[j] != 0xFF)
					goto bad_out;
			for (j = 0; j < sizeof(ts); j++)
				if (((u8 *)&ts)[j] != 0xFF)
					goto bad_out;
		}
		else {
			ret = ops->ReadPage(dev, block, i, buf->header, dev->com.pg_size, NULL, spare, dev->attr->spare_size);
			if (UFFS_FLASH_IS_BAD_BLOCK(ret))
				goto bad_out;
			for (j = 0; j < dev->com.pg_size; j++)
				if (buf->header[j] != 0xFF)
					goto bad_out;
			for (j = 0; j < dev->attr->spare_size; j++)
				if (spare[j] != 0xFF)
					goto bad_out;
		}
	}

	// format succ
	bad = U_FALSE;

bad_out:
	if (bad == U_TRUE)
		uffs_FlashMarkBadBlock(dev, block);
ext:
	if (buf)
		uffs_BufFreeClone(dev, buf);

	if (spare)
		uffs_PoolPut(SPOOL(dev), spare);

	return;
}
#endif



URET uffs_FormatDevice(uffs_Device *dev, UBOOL force)
{
	u16 i, slot;
	URET ret = U_SUCC;
	
	if (dev == NULL)
		return U_FAIL;

	if (dev->ops == NULL) 
		return U_FAIL;

	uffs_GlobalFsLockLock();

	ret = uffs_BufFlushAll(dev);

	if (dev->ref_count > 1 && !force) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"can't format when dev->ref_count = %d",
					dev->ref_count);
		ret = U_FAIL;
	}

	if (ret == U_SUCC && force) {
		uffs_DirEntryBufPutAll(dev);
		uffs_PutAllObjectBuf(dev);
		uffs_FdSignatureIncrease();
	}

	if (ret == U_SUCC &&
		uffs_BufIsAllFree(dev) == U_FALSE &&
		!force)
	{
		uffs_Perror(UFFS_MSG_NORMAL, "some page still in used!");
		ret = U_FAIL;
	}

	if (!force) {
		for (slot = 0; ret == U_SUCC && slot < dev->cfg.dirty_groups; slot++) {
			if (dev->buf.dirtyGroup[slot].count > 0) {
				uffs_Perror(UFFS_MSG_SERIOUS, "there still have dirty pages!");
				ret = U_FAIL;
			}
		}
	}

	if (ret == U_SUCC)
		uffs_BufSetAllEmpty(dev);


	if (ret == U_SUCC && uffs_BlockInfoIsAllFree(dev) == U_FALSE && !force) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"there still have block info cache ? fail to format");
		ret = U_FAIL;
	}

	if (ret == U_SUCC)
		uffs_BlockInfoExpireAll(dev);

	for (i = dev->par.start; ret == U_SUCC && i <= dev->par.end; i++) {
		if (uffs_FlashIsBadBlock(dev, i) == U_FALSE) {
			uffs_FlashEraseBlock(dev, i);
			if (HAVE_BADBLOCK(dev))
				uffs_BadBlockProcess(dev, NULL);
		}
		else {
#ifdef CONFIG_ENABLE_BAD_BLOCK_VERIFY
			_ForceFormatAndCheckBlock(dev, i);
#endif
		}
	}

	if (ret == U_SUCC && uffs_TreeRelease(dev) == U_FAIL) {
		ret = U_FAIL;
	}

	if (ret == U_SUCC && uffs_TreeInit(dev) == U_FAIL) {
		ret = U_FAIL;
	}

	if (ret == U_SUCC && uffs_BuildTree(dev) == U_FAIL) {
		ret = U_FAIL;
	}

	uffs_GlobalFsLockUnlock();

	return ret;
}

static const char * GetTagName(struct uffs_TagStoreSt *s)
{
	const char *name = "UNKNOWN";
	struct uffs_NodeTypeNameMapSt maps[] = UFFS_TYPE_NAME_MAP;
	int i;

	for (i = 0; i < ARRAY_SIZE(maps); i++) {
		if (s->type == maps[i].type)
			name = maps[i].name;
	}

	return name;
}

static void DumpBufHex(struct uffs_DeviceSt *dev, const u8* buf, int len, dump_msg_cb *dump)
{
	int i;
	for (i = 0; i < len; i++)
		dump(dev, "%02X ", buf[i]);
}

// return -1 if do not need to read next tag
static int DumpTag(struct uffs_DeviceSt *dev, int block, int page, uffs_Tags *tag, dump_msg_cb *dump)
{
	struct uffs_TagStoreSt *s = &tag->s;
	struct uffs_MiniHeaderSt header;
	URET ret;

	if (!TAG_IS_DIRTY(tag)) {
		// is a clean page ?
		ret = uffs_LoadMiniHeader(dev, block, page, &header);
		if (ret == U_FAIL) {
			dump(dev, "Fail to load mini header from page 0\n");
		}
		else {
			if (header.status == 0xFF)
				dump(dev, "page %d CLEAN\n", page);
			else {
				dump(dev, "page %d NOT clean ! header: ", page);
				DumpBufHex(dev, (u8 *)&header, sizeof(header), dump);
				dump(dev, ", tag: ");
				DumpBufHex(dev, (u8 *)s, sizeof(struct uffs_TagStoreSt), dump);
				dump(dev, "\n");
			}
		}
		return -1;
	}
	
	dump(dev, " - page %2d/%2d %s %d/%d len%4d\n", page, s->page_id, GetTagName(s), s->serial, s->parent, s->data_len);
	
	return 0;
}

static void DumpBlock(struct uffs_DeviceSt *dev, int block, dump_msg_cb *dump)
{
	int i;
	struct uffs_StorageAttrSt *attr = dev->attr;
	uffs_Tags tag;
	URET ret;

	dump(dev, "--- Block %d ---\n", block);

	if (uffs_FlashIsBadBlock(dev, block)) {
		dump(dev, "Bad block\n\n");
		return;
	}

	for (i = 0; i < attr->pages_per_block; i++) {

		memset(&tag, 0xFF, sizeof(tag));
		ret = uffs_FlashReadPageTag(dev, block, i, &tag);

		if (ret == UFFS_FLASH_IO_ERR) {
			dump(dev, "page %d tag I/O error\n", i);
			continue;
		}
		else if (ret == UFFS_FLASH_ECC_FAIL) {
			dump(dev, "page %d tag ECC error\n", i);
			continue;
		}
		else if (ret == UFFS_FLASH_NO_ERR || ret == UFFS_FLASH_ECC_OK) {
			if (ret == UFFS_FLASH_ECC_OK)
				dump(dev, "page %d tag has bit flip, corrected by ECC\n", i);

			if (DumpTag(dev, block, i, &tag, dump) == 0)
				continue;
			else
				break;
		}
		else {
			dump(dev, "read page %d tag return unexpected: %d\n", i, ret);
			continue;
		}
	}
	dump(dev, "\n");
}

void uffs_DumpDevice(struct uffs_DeviceSt *dev, dump_msg_cb *dump)
{
	int i;
	for (i = dev->par.start; i <= dev->par.end; i++) {
		DumpBlock(dev, i, dump);
	}	
}
