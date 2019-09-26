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
 * \file uffs_ecc.h
 * \brief file handle operations
 * \author Ricky Zheng, created 8th Jun, 2005
 */

#ifndef _UFFS_ECC_H_
#define _UFFS_ECC_H_

#include <string.h>

#include "uffs/uffs_fs.h"
#include "uffs/uffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif



#define MAX_ECC_LENGTH	24	//!< 2K page ecc length is 24 bytes.

/**
 * calculate ECC
 * \return length of generated ECC. (3 bytes ECC per 256 data) 
 */
int uffs_EccMake(const void *data, int data_len, void *ecc);

/** 
 * correct data by ECC.
 *
 * return:   0 -- no error
 *			-1 -- can not be corrected
 *			>0 -- how many bits are corrected
 */
int uffs_EccCorrect(void *data, int data_len, void *read_ecc, const void *test_ecc);


/**
 * generate 12 bit ecc for maximum 8 bytes data
 */
u16 uffs_EccMake8(const void *data, int data_len);

/**
 * correct maximum 8 bytes data from 12 bits ECC
 *
 * return:   0 -- no error
 *			-1 -- can not be corrected
 *			>0 -- how many bits are corrected
 */
int uffs_EccCorrect8(void *data, u16 read_ecc, u16 test_ecc, int errtop);


#ifdef __cplusplus
}
#endif
#endif
