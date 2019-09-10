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
 * \file uffs_fileem.c
 * \brief emulate uffs file system
 * \author Ricky Zheng, created 9th May, 2005
 */
  

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_device.h"
#include "uffs_fileem.h"

#define PFX "femu: "
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)


static struct uffs_StorageAttrSt g_femu_storage = {0};

static struct uffs_FileEmuSt g_femu_private = {0};


struct uffs_StorageAttrSt * femu_GetStorage()
{
	return &g_femu_storage;
}

struct uffs_FileEmuSt *femu_GetPrivate()
{
	return &g_femu_private;
}

URET femu_InitDevice(uffs_Device *dev)
{
	uffs_FileEmu *emu = femu_GetPrivate();

	// setup device storage attr and private data structure.
	// all femu partition share one storage attribute

	dev->attr = femu_GetStorage();
	dev->attr->_private = (void *) emu;

	// setup flash driver operations, according to the ecc option.
	switch(dev->attr->ecc_opt) {
		case UFFS_ECC_NONE:
		case UFFS_ECC_SOFT:
			dev->ops = &g_femu_ops_ecc_soft;
			break;
		case UFFS_ECC_HW:
			dev->ops = &g_femu_ops_ecc_hw;
			break;
		case UFFS_ECC_HW_AUTO:
			dev->ops = &g_femu_ops_ecc_hw_auto;
			break;
		default:
			break;
	}

#ifdef UFFS_FEMU_ENABLE_INJECTION
	// setup wrap functions, for inject ECC errors, etc.
	// check wrap_inited so that multiple devices can share the same driver
	if (!emu->wrap_inited) {
		femu_setup_wrapper_functions(dev);
		emu->wrap_inited = U_TRUE;
	}
#endif

	return U_SUCC;
}

/* Nothing to do here */
URET femu_ReleaseDevice(uffs_Device *dev)
{
	return U_SUCC;
}


/////////////////////////////////////////////////////////////////////////////////
