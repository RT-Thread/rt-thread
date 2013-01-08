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
 * \file uffs_fileem.h
 * \brief Emulate NAND flash with host file.
 * \author Ricky Zheng
 */

#ifndef _UFFS_FILEEM_H_
#define _UFFS_FILEEM_H_

#include "uffs/uffs_device.h"

#define UFFS_FEMU_FILE_NAME		"uffsemfile.bin"

#define UFFS_FEMU_MAX_BLOCKS	(1024 * 16)		// maximum 16K blocks

#define UFFS_FEMU_ENABLE_INJECTION		// enable bad block & ecc error injection

extern struct uffs_FlashOpsSt g_femu_ops_ecc_soft;		// for software ECC or no ECC.
extern struct uffs_FlashOpsSt g_femu_ops_ecc_hw;		// for hardware ECC
extern struct uffs_FlashOpsSt g_femu_ops_ecc_hw_auto;	// for auto hardware ECC

#define PAGE_DATA_WRITE_COUNT_LIMIT		1
#define PAGE_SPARE_WRITE_COUNT_LIMIT	1

typedef struct uffs_FileEmuSt {
	int initCount;
	FILE *fp;
	FILE *dump_fp;
	u8 *em_monitor_page;		// page write monitor
	u8 * em_monitor_spare;		// spare write monitor
	u32 *em_monitor_block;		// block erease monitor
	const char *emu_filename;
#ifdef UFFS_FEMU_ENABLE_INJECTION
	struct uffs_FlashOpsSt ops_orig;
	UBOOL wrap_inited;
#endif
} uffs_FileEmu;

/* file emulator device init/release entry */
URET femu_InitDevice(uffs_Device *dev);
URET femu_ReleaseDevice(uffs_Device *dev);

struct uffs_StorageAttrSt * femu_GetStorage(void);
struct uffs_FileEmuSt * femu_GetPrivate(void);

#ifdef UFFS_FEMU_ENABLE_INJECTION
void femu_setup_wrapper_functions(uffs_Device *dev);
#endif

/* internal used functions, shared by all ecc option implementations */
int femu_InitFlash(uffs_Device *dev);
int femu_ReleaseFlash(uffs_Device *dev);
int femu_EraseBlock(uffs_Device *dev, u32 blockNumber);

#endif

