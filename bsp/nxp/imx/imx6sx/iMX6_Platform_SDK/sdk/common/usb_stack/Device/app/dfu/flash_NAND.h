/********************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
 *
 * @file flash_NAND.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief flash driver header file
 *
 *****************************************************************************/

/*********************************** Includes ***********************************/

/*********************************** Macros ************************************/

/*********************************** Defines ***********************************/
/* Error code */
#ifndef _FLASH_NAND_H_
#define _FLASH_NAND_H_

#define FLASH_READY 1
#define FLASH_ERASE_SUSPENDED 2
#define FLASH_TIMEOUT 3
#define FLASH_BUSY 4
#define FLASH_ERROR 5
#define FLASH_UNSUPPORTED_BUS_SIZE 6
#define FLASH_WRITE_PROTECT 7

#define FLASH_RESET_CMD 0xF0

#define DQ0 0x01
#define DQ1 0x02
#define DQ2 0x04
#define DQ3 0x08
#define DQ4 0x10
#define DQ5 0x20
#define DQ6 0x40
#define DQ7 0x80

#define  UNLOCKED   0
#define  LOCKED     1

#define WS_BYTES_IN_WORD 2



/* Flash commands */
#define FLASHCMD_PROGRAM        	0x20
#define FLASHCMD_SECTORERASE    	0x80
#define FLASHCMD_WRITEPROTECTION    0xE0

/* Sector information */
#define S28WS128_BASE_ADDR		 0x00000000

#define S28WS128_START_ADD_SECTOR0		0x00000000
#define S28WS128_SIZE_SECTOR0			0x8000

#define S28WS128_START_ADD_SECTOR1		0x00008000
#define S28WS128_SIZE_SECTOR1			0x8000

#define S28WS128_START_ADD_SECTOR2		0x00010000
#define S28WS128_SIZE_SECTOR2			0x8000

/*********************************** Constant **********************************/

/*********************************** Variables *********************************/

/*********************************** Prototype *********************************/
extern void Flash_Init();
uint_8 Flash_SectorErase(uint_8 *FlashPtr);
uint_8 Flash_ByteProgram(uint_8 *to_ptr,uint_8 *from_ptr,int size);

#endif
