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

#ifndef _UFFS_UTILS_H_
#define _UFFS_UTILS_H_

#include "uffs/uffs_types.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif


//get UFFS disk version, if fail, return 0
int uffs_GetUFFSVersion(struct uffs_DeviceSt *dev);

void uffs_InitGlobalFsLock(void);
void uffs_ReleaseGlobalFsLock(void);
void uffs_GlobalFsLockLock(void);
void uffs_GlobalFsLockUnlock(void);

URET uffs_FormatDevice(uffs_Device *dev, UBOOL force);

#ifdef __cplusplus
}
#endif

typedef void dump_msg_cb(struct uffs_DeviceSt *dev, const char *fmt, ...);

void uffs_DumpDevice(struct uffs_DeviceSt *dev, dump_msg_cb *dump);

#endif

