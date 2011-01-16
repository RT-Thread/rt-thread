//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
--*/
#ifndef __NAND_H__
#define __NAND_H__

#include <s3c24x0.h>
#include <uffs/uffs_types.h>

/* define low accessing value */
#define TOTAL_BLOCKS    	2048							/* total block of whole chip */
#define PAGE_DATA_SIZE  	2048							/* max size of page data */
#define PAGE_SPARE_SIZE 	64								/* max size of extended partition */
#define PAGES_PER_BLOCK 	64								/* max pages per block' */
#define PAGE_SIZE			(PAGE_DATA_SIZE+PAGE_SPARE_SIZE)/* max size per whole page */
#define BLOCK_DATA_SIZE 	(PAGE_DATA_SIZE*PAGES_PER_BLOCK)/* max size per block' */

//bad flags offset in the oob area. 
#define NAND_SMALL_BADBLOCK_POS		5	//small page FLASH
#define NAND_LARGE_BADBLOCK_POS		0	//large page FLASH

/* Option constants for bizarre disfunctionality and real
*  features
*/
/* Chip can not auto increment pages */
#define NAND_NO_AUTOINCR	0x00000001
/* Buswitdh is 16 bit */
#define NAND_BUSWIDTH_16	0x00000002
/* Device supports partial programming without padding */
#define NAND_NO_PADDING		0x00000004
/* Chip has cache program function */
#define NAND_CACHEPRG		0x00000008
/* Chip has copy back function */
#define NAND_COPYBACK		0x00000010
/* AND Chip which has 4 banks and a confusing page / block
 * assignment. See Renesas datasheet for further information */
#define NAND_IS_AND			0x00000020
/* Chip has a array of 4 pages which can be read without
 * additional ready /busy waits */
#define NAND_4PAGE_ARRAY	0x00000040

/* Options valid for Samsung large page devices */
#define NAND_SAMSUNG_LP_OPTIONS \
	(NAND_NO_PADDING | NAND_CACHEPRG | NAND_COPYBACK)


struct nand_flash_dev 

{
	char 		  *name;	//chip name
	int 		  id;		//chip ID
	unsigned long pagesize;	//max pages
	unsigned long chipsize;	//size of whole chip iMB
	unsigned long blocksize;//size of block 
	unsigned long options;	//option
};

struct nand_manufacturers 
{
	int id;
	char * name;
};

#endif /*__NAND_H__*/
