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
 * \file uffs_init.c
 * \brief initialize uffs file system device
 * \author Ricky Zheng, created 12th May, 2005
 */

#include "uffs_config.h"
#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_tree.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_badblock.h"
#include "uffs/uffs_utils.h"
#include <string.h>

#define PFX "init: "

static URET uffs_InitDeviceConfig(uffs_Device *dev)
{
    if (dev->cfg.dirty_groups == 0)
        dev->cfg.dirty_groups = MAX_DIRTY_BUF_GROUPS;

	if (!uffs_Assert(dev->cfg.dirty_groups >= 1 && dev->cfg.dirty_groups <= MAX_DIRTY_BUF_GROUPS,
						"invalid config: dirty_groups = %d\n", dev->cfg.dirty_groups))
		return U_FAIL;

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
	dev->cfg.bc_caches = MAX_CACHED_BLOCK_INFO;
	dev->cfg.page_buffers = MAX_PAGE_BUFFERS;
	dev->cfg.dirty_pages = MAX_DIRTY_PAGES_IN_A_BLOCK;
	dev->cfg.reserved_free_blocks = MINIMUN_ERASED_BLOCK;
#else
	if (dev->cfg.bc_caches == 0)
		dev->cfg.bc_caches = MAX_CACHED_BLOCK_INFO;
	if (dev->cfg.page_buffers == 0)
		dev->cfg.page_buffers = MAX_PAGE_BUFFERS;
	if (dev->cfg.dirty_pages == 0)
		dev->cfg.dirty_pages = MAX_DIRTY_PAGES_IN_A_BLOCK;
	if (dev->cfg.reserved_free_blocks == 0)
		dev->cfg.reserved_free_blocks = MINIMUN_ERASED_BLOCK;

	if (!uffs_Assert(dev->cfg.page_buffers - CLONE_BUFFERS_THRESHOLD >= 3, "invalid config: page_buffers = %d\n", dev->cfg.page_buffers))
		return U_FAIL;

#endif
	return U_SUCC;
}

URET uffs_InitDevice(uffs_Device *dev)
{
	URET ret;

	ret = uffs_InitDeviceConfig(dev);
	if (ret != U_SUCC)
		return U_FAIL;

	if (dev->mem.init) {
		if (dev->mem.init(dev) != U_SUCC) {
			uffs_Perror(UFFS_MSG_SERIOUS, "Init memory allocator fail.");
			return U_FAIL;
		}
	}

	memset(&(dev->st), 0, sizeof(uffs_FlashStat));

	uffs_DeviceInitLock(dev);
	uffs_BadBlockInit(dev);


	if (uffs_FlashInterfaceInit(dev) != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't initialize flash interface !");
		goto fail;
	}

	uffs_Perror(UFFS_MSG_NOISY, "init page buf");
	ret = uffs_BufInit(dev, dev->cfg.page_buffers, dev->cfg.dirty_pages);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_DEAD, "Initialize page buffers fail");
		goto fail;
	}
	uffs_Perror(UFFS_MSG_NOISY, "init block info cache");
	ret = uffs_BlockInfoInitCache(dev, dev->cfg.bc_caches);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_DEAD, "Initialize block info fail");
		goto fail;
	}

	ret = uffs_TreeInit(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "fail to init tree buffers");
		goto fail;
	}

	ret = uffs_BuildTree(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "fail to build tree");
		goto fail;
	}

	return U_SUCC;

fail:
	uffs_DeviceReleaseLock(dev);

	return U_FAIL;
}

URET uffs_ReleaseDevice(uffs_Device *dev)
{
	URET ret;

	ret = uffs_BlockInfoReleaseCache(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS,  "fail to release block info.");
		goto ext;
	}

	ret = uffs_BufReleaseAll(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS,  "fail to release page buffers");
		goto ext;
	}

	ret = uffs_TreeRelease(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "fail to release tree buffers!");
		goto ext;
	}

	ret = uffs_FlashInterfaceRelease(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "fail to release tree buffers!");
		goto ext;
	}

	if (dev->mem.release)
		ret = dev->mem.release(dev);

	if (ret != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "fail to release memory allocator!");
	}

	uffs_DeviceReleaseLock(dev);

ext:
	return ret;

}

URET uffs_InitFileSystemObjects(void)
{
	if (uffs_InitObjectBuf() == U_SUCC) {
		if (uffs_DirEntryBufInit() == U_SUCC) {
			uffs_InitGlobalFsLock();
			return U_SUCC;
		}
	}

	return U_FAIL;
}

URET uffs_ReleaseFileSystemObjects(void)
{
	if (uffs_ReleaseObjectBuf() == U_SUCC) {
		if (uffs_DirEntryBufRelease() == U_SUCC) {
			uffs_ReleaseGlobalFsLock();
			return U_SUCC;
		}
	}

	return U_FAIL;
}
