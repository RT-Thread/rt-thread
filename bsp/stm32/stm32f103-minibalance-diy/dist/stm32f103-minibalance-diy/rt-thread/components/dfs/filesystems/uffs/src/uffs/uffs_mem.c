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
 * \file uffs_mem.c
 * \brief uffs static memory allocator
 * \author Ricky Zheng, created 23th Feb, 2007
 */

#include <string.h>
#include "uffs_config.h"
#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_mem.h"

#define PFX "mem : "

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
static void * static_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
	struct uffs_memAllocatorSt *mem = &dev->mem;
	void *p = NULL;

	size += (size % sizeof(long) ? sizeof(long) - (size % sizeof(long)) : 0);

	if (mem->buf_size - mem->pos < (int)size) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"Memory alloc failed! (alloc %d, free %d)",
					size, mem->buf_size - mem->pos);
	}
	else {
		p = mem->buf_start + mem->pos;
		mem->pos += size;
		uffs_Perror(UFFS_MSG_NOISY,
					"0x%p: Allocated %d, free %d",
					p, size, mem->buf_size - mem->pos);
	}

	return p;
}

void uffs_MemSetupStaticAllocator(uffs_MemAllocator *allocator,
								  void *pool, int size)
{
	allocator->buf_start = (char *)pool;
	allocator->buf_size = size;
	allocator->pos = 0;
	allocator->malloc = static_malloc;
	allocator->free = NULL;  //never free memory for static memory allocator

	uffs_Perror(UFFS_MSG_NOISY,
				"System static memory: %d bytes", allocator->buf_size);
	
}

#endif






