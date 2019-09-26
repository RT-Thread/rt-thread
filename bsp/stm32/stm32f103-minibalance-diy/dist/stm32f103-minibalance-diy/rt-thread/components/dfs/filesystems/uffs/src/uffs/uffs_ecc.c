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
 * \file uffs_ecc.c
 * \brief ecc maker and correct
 * \author Ricky Zheng, created in 12th Jun, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_fs.h"
#include <string.h>

#define PFX "ecc : "

static const u8 bits_tbl[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

static const u8 line_parity_tbl[16] = {
	0x00, 0x02, 0x08, 0x0a, 0x20, 0x22, 0x28, 0x2a,
	0x80, 0x82, 0x88, 0x8a, 0xa0, 0xa2, 0xa8, 0xaa
};

static const u8 line_parity_prime_tbl[16] = {
	0x00, 0x01, 0x04, 0x05, 0x10, 0x11, 0x14, 0x15,
	0x40, 0x41, 0x44, 0x45, 0x50, 0x51, 0x54, 0x55
};

static const u8 column_parity_tbl[256] = {
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00, 
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95, 
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99, 
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c, 
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5, 
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30, 
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c, 
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9, 
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9, 
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c, 
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30, 
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5, 
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c, 
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99, 
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95, 
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00, 
};

/**
 * calculate 3 bytes ECC for 256 bytes data.
 *
 * \param[in] data input data
 * \param[out] ecc output ecc
 * \param[in] length of data in bytes
 */
static void uffs_EccMakeChunk256(const void *data, void *ecc, u16 len)
{
	u8 *pecc = (u8 *)ecc;
	const u8 *p = (const u8 *)data;
	u8 b, col_parity = 0, line_parity = 0, line_parity_prime = 0;
	u16 i;

	for (i = 0; i < len; i++) {
		b = column_parity_tbl[*p++];
		col_parity ^= b;
		if (b & 0x01) { // odd number of bits in the byte
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}
	}

	// ECC layout:
	// Byte[0]  P64   | P64'   | P32  | P32'  | P16  | P16'  | P8   | P8'
	// Byte[1]  P1024 | P1024' | P512 | P512' | P256 | P256' | P128 | P128'
	// Byte[2]  P4    | P4'    | P2   | P2'   | P1   | P1'   | 1    | 1
	pecc[0] = ~(line_parity_tbl[line_parity & 0xf] |
				line_parity_prime_tbl[line_parity_prime & 0xf]);
	pecc[1] = ~(line_parity_tbl[line_parity >> 4] |
				line_parity_prime_tbl[line_parity_prime >> 4]);
	pecc[2] = (~col_parity) | 0x03;

}


/**
 * calculate ECC. (3 bytes ECC per 256 data)
 *
 * \param[in] data input data
 * \param[in] data_len length of data in byte
 * \param[out] ecc output ecc
 *
 * \return length of ECC in byte. (3 bytes ECC per 256 data) 
 */
int uffs_EccMake(const void *data, int data_len, void *ecc)
{
	const u8 *p_data = (const u8 *)data;
	u8 *p_ecc = (u8 *)ecc;
	int len;

	if (data == NULL || ecc == NULL)
		return 0;

	while (data_len > 0) {
		len = data_len > 256 ? 256 : data_len;
		uffs_EccMakeChunk256(p_data, p_ecc, len);
		data_len -= len;
		p_data += len;
		p_ecc += 3;
	}

	return p_ecc - (u8 *)ecc;
}

/**
 * perform ECC error correct for 256 bytes data chunk.
 *
 * \param[in|out] data input data to be corrected
 * \param[in] read_ecc 3 bytes ECC read from storage
 * \param[in] test_ecc 3 bytes ECC calculated from data
 * \param[in] errtop top position of error
 *
 * \return:  0 -- no error
 *			-1 -- can not be corrected
 *			>0 -- how many bits corrected
 */
static int uffs_EccCorrectChunk256(void *data, void *read_ecc,
								   const void *test_ecc, int errtop)
{
	u8 d0, d1, d2;		/* deltas */
	u8 *p = (u8 *)data;
	u8 *pread_ecc = (u8 *)read_ecc, *ptest_ecc = (u8 *)test_ecc;

	d0 = pread_ecc[0] ^ ptest_ecc[0];
	d1 = pread_ecc[1] ^ ptest_ecc[1];
	d2 = pread_ecc[2] ^ ptest_ecc[2];
	
	if ((d0 | d1 | d2) == 0)
		return 0;
	
	if( ((d0 ^ (d0 >> 1)) & 0x55) == 0x55 &&
	    ((d1 ^ (d1 >> 1)) & 0x55) == 0x55 &&
	    ((d2 ^ (d2 >> 1)) & 0x54) == 0x54)
	{
		// Single bit (recoverable) error in data

		u8 b;
		u8 bit;
		
		bit = b = 0;		
		
		if(d1 & 0x80) b |= 0x80;
		if(d1 & 0x20) b |= 0x40;
		if(d1 & 0x08) b |= 0x20;
		if(d1 & 0x02) b |= 0x10;
		if(d0 & 0x80) b |= 0x08;
		if(d0 & 0x20) b |= 0x04;
		if(d0 & 0x08) b |= 0x02;
		if(d0 & 0x02) b |= 0x01;

		if(d2 & 0x80) bit |= 0x04;
		if(d2 & 0x20) bit |= 0x02;
		if(d2 & 0x08) bit |= 0x01;

		if (b >= errtop) return -1;

		p[b] ^= (1 << bit);
		
		return 1;
	}
	
	if ((bits_tbl[d0] + bits_tbl[d1] + bits_tbl[d2]) == 1) {
		// error in ecc, no action need		
		return 1;
	}
	
	// Unrecoverable error
	return -1;
}

/**
 * perform ECC error correct
 *
 * \param[in|out] data input data to be corrected
 * \param[in] data_len length of data in byte
 * \param[in] read_ecc ECC read from storage
 * \param[in] test_ecc ECC calculated from data
 *
 * \return:  0 -- no error
 *			-1 -- can not be corrected
 *			>0 -- how many bits corrected
 */

int uffs_EccCorrect(void *data, int data_len,
					void *read_ecc, const void *test_ecc)
{
	u8 *p_data = (u8 *)data;
	u8 *p_read_ecc = (u8 *)read_ecc;
	u8 *p_test_ecc = (u8 *)test_ecc;
	int total = 0, ret, len;

	if (data == NULL || read_ecc == NULL || test_ecc == NULL)
		return -1;

	while (data_len > 0) {
		len = (data_len > 256 ? 256 : data_len);
		ret = uffs_EccCorrectChunk256(p_data, p_read_ecc, p_test_ecc, len);
		if (ret < 0) {
			total = ret;
			break;
		}
		else
			total += ret;

		p_data += len;
		p_read_ecc += 3;
		p_test_ecc += 3;
		data_len -= len;
	}

	return total;

}

/** 
 * generate 12 bit ecc for 8 bytes data. 
 *	(use 0xFF padding if the data length is less then 8 bytes)
 *
 * \param[in] data input data
 * \param[in] data_len length of data in byte
 *
 * \return 12 bits ECC data (lower 12 bits).
 */
u16 uffs_EccMake8(void *data, int data_len)
{
	u8 *p = (u8 *)data;
	u8 b, col_parity = 0, line_parity = 0, line_parity_prime = 0;
	u8 i;
	u16 ecc = 0;


	data_len = (data_len > 8 ? 8 : data_len);

	for (i = 0; i < data_len; i++) {
		b = column_parity_tbl[*p++];
		col_parity ^= b;
		if (b & 0x01) { // odd number of bits in the byte
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}
	}

	// ECC layout:
	// row:         (1) | (1)  | P32 | P32' | P16 | P16' | P8  | P8'
	// column:      P4  | P4'  | P2  | P2'  | P1  | P1'  | (1) | (1)
	// 12-bit ecc:  P32 | P32' | P16 | P16' | P8  | P8'  | P4  | P4' | P2 | P2' | P1 | P1' |
	ecc = (~(
			line_parity_tbl[line_parity & 0xf] |
			line_parity_prime_tbl[line_parity_prime & 0xf]
			)) << 6;
	ecc |= (((~col_parity) >> 2) & 0x3f);

	return ecc & 0xfff;
}

/**
 * correct 8 bytes data from 12 bits ECC
 *
 * \param[in|out] data input data
 * \param[in] read_ecc ecc read from storage
 * \param[in] test_ecc ecc calculated from data
 * \param[in] errtop top position of error.
 *
 * \return:  0 -- no error
 *			-1 -- can not be corrected
 *			>0 -- how many bits corrected
 */
int uffs_EccCorrect8(void *data, u16 read_ecc, u16 test_ecc, int errtop)
{
	u8 d0, d1;			/* deltas */
	u8 *p = (u8 *)data;

	read_ecc &= 0xfff;
	test_ecc &= 0xfff;

	d0 = (read_ecc >> 6) ^ (test_ecc >> 6);
	d1 = (read_ecc & 0x3f) ^ (test_ecc & 0x3f);

	if ((d0 | d1) == 0)
		return 0;
	
	if( ((d0 ^ (d0 >> 1)) & 0x15) == 0x15 &&
	    ((d1 ^ (d1 >> 1)) & 0x15) == 0x15)
	{
		// Single bit (recoverable) error in data

		u8 b;
		u8 bit;
		
		bit = b = 0;		
		
		if(d0 & 0x20) b |= 0x04;
		if(d0 & 0x08) b |= 0x02;
		if(d0 & 0x02) b |= 0x01;

		if(d1 & 0x20) bit |= 0x04;
		if(d1 & 0x08) bit |= 0x02;
		if(d1 & 0x02) bit |= 0x01;

		if (b >= (u8)errtop) return -1;
		if (bit >= 8) return -1;

		p[b] ^= (1 << bit);
		
		return 1;
	}
	
	if ((bits_tbl[d0] + bits_tbl[d1]) == 1) {
		// error in ecc, no action need		
		return 1;
	}
	
	// Unrecoverable error
	return -1;
}

