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
 * \file uffs_device.c
 * \brief uffs device operation
 * \author Ricky Zheng, created 10th May, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_mtb.h"
#include <string.h>

#define PFX "dev : "


#ifdef CONFIG_USE_PER_DEVICE_LOCK
void uffs_DeviceInitLock(uffs_Device *dev)
{
	uffs_SemCreate(&dev->lock.sem);
	dev->lock.task_id = UFFS_TASK_ID_NOT_EXIST;
	dev->lock.counter = 0;
}

void uffs_DeviceReleaseLock(uffs_Device *dev)
{
	uffs_SemDelete(&dev->lock.sem);
}

void uffs_DeviceLock(uffs_Device *dev)
{
	uffs_SemWait(dev->lock.sem);
	
	if (dev->lock.counter != 0) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"Lock device, counter %d NOT zero?!", dev->lock.counter);
	}

	dev->lock.counter++;
}

void uffs_DeviceUnLock(uffs_Device *dev)
{
	dev->lock.counter--;

	if (dev->lock.counter != 0) {
		uffs_Perror(UFFS_MSG_NORMAL,
					"Unlock device, counter %d NOT zero?!", dev->lock.counter);
	}
	
	uffs_SemSignal(dev->lock.sem);
}

#else

/* dummy stubs */
void uffs_DeviceInitLock(uffs_Device *dev) {}
void uffs_DeviceReleaseLock(uffs_Device *dev) {}
void uffs_DeviceLock(uffs_Device *dev) {}
void uffs_DeviceUnLock(uffs_Device *dev) {}

#endif
