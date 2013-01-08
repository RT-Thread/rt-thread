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
 * \file uffs_badblock.h
 * \brief bad block management
 * \author Ricky Zheng
 */

#ifndef _UFFS_BADBLOCK_H_
#define _UFFS_BADBLOCK_H_

#include "uffs/uffs_public.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif


#define HAVE_BADBLOCK(dev) (dev->bad.block != UFFS_INVALID_BLOCK)

/** initialize bad block management data structures for uffs device */
void uffs_BadBlockInit(uffs_Device *dev);

/** processing bad block: erase bad block,
	mark it as 'bad' and put it to bad block list */
void uffs_BadBlockProcess(uffs_Device *dev, TreeNode *node);

/** processing bad block: erase bad block,
	mark it as 'bad' and put it to suspend block list */
void uffs_BadBlockProcessSuspend(uffs_Device *dev, TreeNode *node);

/** try to recover data from a new discovered bad block */
void uffs_BadBlockRecover(uffs_Device *dev);

/** put a new block to the bad block waiting list */
void uffs_BadBlockAdd(uffs_Device *dev, int block);


#ifdef __cplusplus
}
#endif


#endif
