/*
 * uffs/flash/nand.h
 *
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Info:
 *	Contains standard defines and IDs for NAND flash devices
 */
#ifndef __RTT_DFS_NAND_H__
#define __RTT_DFS_NAND_H__

/*
 * Standard NAND flash commands
 */ 
#define NAND_CMD_READ0				0		/* Read0 */
#define NAND_CMD_READ1				1		/* Read1 */
#define NAND_CMD_RNDOUT				5		/* Random data output */
#define NAND_CMD_PAGEPROG			0x10	/* Write phase 2 */
#define NAND_CMD_READOOB			0x50	/* Read oob	*/
#define NAND_CMD_ERASE1				0x60	/* Erase phase 1 */
#define NAND_CMD_STATUS				0x70	/* Status read */
#define NAND_CMD_STATUS_MULTI		0x71								 
#define NAND_CMD_SEQIN				0x80	/* Write phase 1 */
#define NAND_CMD_RNDIN				0x85	/* Random data input */
#define NAND_CMD_READID				0x90	/* ReadID,all-purpose command */
#define NAND_CMD_ERASE2				0xd0	/* Erase phase 2 */
#define NAND_CMD_RESET				0xff	/* Reset */

/* Extended commands for large page devices */
#define NAND_CMD_READSTART			0x30
#define NAND_CMD_RNDOUTSTART		0xE0
#define NAND_CMD_CACHEDPROG			0x15
#define NAND_CMD_READ_EDC			0x7b	

/* define low accessing value */
#define TOTAL_BLOCKS    	2048							/* total block of whole chip */
#define PAGE_DATA_SIZE  	2048							/* max size of page data */
#define PAGE_SPARE_SIZE 	64								/* max size of extended partition */
#define PAGES_PER_BLOCK 	64								/* max pages per block' */
#define PAGE_SIZE			(PAGE_DATA_SIZE+PAGE_SPARE_SIZE)/* max size per whole page */
#define BLOCK_DATA_SIZE 	(PAGE_DATA_SIZE*PAGES_PER_BLOCK)/* max size per block' */

/* bad flags offset in the oob area. */
#define NAND_SMALL_BADBLOCK_POS		5	/* small page FLASH	*/
#define NAND_LARGE_BADBLOCK_POS		0	/* large page FLASH	*/

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
	char 		  *name;	/* chip name */
	int 		  id;		/* chip ID */
	unsigned long pagesize;	/* max pages */
	unsigned long chipsize;	/* size of whole chip iMB */
	unsigned long blocksize;/* size of block */
	unsigned long options;	/* option */
};

struct nand_manufacturers 
{
	int id;
	char * name;
};

#endif /*__RTT_DFS_NAND_H__*/
