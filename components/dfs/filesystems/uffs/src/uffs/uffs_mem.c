/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file uffs_mem.c
 * \brief uffs native memory allocator
 * \author Ricky Zheng, created 23th Feb, 2007
 */

#include <rtthread.h>

#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_mem.h"

#define PFX "mem: "

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
#include <rtthread.h>

void* rt_malloc_link(struct uffs_DeviceSt *dev, unsigned int size)
{
	return rt_malloc(size);
}
URET rt_free_link(struct uffs_DeviceSt *dev, void *p)
{
	rt_free(p);
	return 0;
}

void uffs_MemSetupSystemAllocator(uffs_MemAllocator *allocator)
{
	allocator->malloc = rt_malloc_link;
	allocator->free = rt_free_link;
}
#endif



