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

#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_config.h"
#include "uffs/uffs_tree.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_badblock.h"
#include <string.h>

#define PFX "init: "

URET uffs_InitDevice(uffs_Device *dev)
{
	URET ret;

	if (dev->mem.init) {
		if (dev->mem.init(dev) != U_SUCC) {
			uffs_Perror(UFFS_ERR_SERIOUS, "Init memory allocator fail.");
			return U_FAIL;
		}
	}

	memset(&(dev->st), 0, sizeof(uffs_FlashStat));

	uffs_DeviceInitLock(dev);
	uffs_BadBlockInit(dev);

	if (uffs_FlashInterfaceInit(dev) != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "Can't initialize flash interface !");
		goto fail;
	}

	uffs_Perror(UFFS_ERR_NOISY, "init page buf");
	ret = uffs_BufInit(dev, MAX_PAGE_BUFFERS, MAX_DIRTY_PAGES_IN_A_BLOCK);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_DEAD, "Initialize page buffers fail");
		goto fail;
	}
	uffs_Perror(UFFS_ERR_NOISY, "init block info cache");
	ret = uffs_BlockInfoInitCache(dev, MAX_CACHED_BLOCK_INFO);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_DEAD, "Initialize block info fail");
		goto fail;
	}

	ret = uffs_TreeInit(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "fail to init tree buffers");
		goto fail;
	}

	ret = uffs_BuildTree(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "fail to build tree");
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
		uffs_Perror(UFFS_ERR_SERIOUS,  "fail to release block info.");
		goto ext;
	}

	ret = uffs_BufReleaseAll(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS,  "fail to release page buffers");
		goto ext;
	}

	ret = uffs_TreeRelease(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "fail to release tree buffers!");
		goto ext;
	}

	ret = uffs_FlashInterfaceRelease(dev);
	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "fail to release tree buffers!");
		goto ext;
	}

	if (dev->mem.release)
		ret = dev->mem.release(dev);

	if (ret != U_SUCC) {
		uffs_Perror(UFFS_ERR_SERIOUS, "fail to release memory allocator!");
	}

	uffs_DeviceReleaseLock(dev);

ext:
	return ret;

}

