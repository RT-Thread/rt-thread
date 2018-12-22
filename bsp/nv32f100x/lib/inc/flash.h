/******************************************************************************
******************************************************************************
*
* @file flash.h
*
* @brief application entry point which performs application specific tasks. 
*
*******************************************************************************
*
* provide a demo for how to initialize the NV32, output messages via SCI, 
* flash operations, etc.
* NOTE:
*	printf call may occupy a lot of memory (around 1924 bytes), so please
*	consider your code size before using printf.
******************************************************************************
*
* provide FLASH driver
*
******************************************************************************/



#ifndef FLASH_H_
#define FLASH_H_

/******************************************************************************
* Includes
******************************************************************************/
#include "common.h"
/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/
/* Uncomment the following line to support programming flash while running code from flash */
// #define FLASH_ENABLE_STALLING_FLASH_CONTROLLER

#define ETMRH_FSTAT_MGSTAT0_MASK  (1)
#define ETMRH_FSTAT_MGSTAT1_MASK  (1<<1)

#define FLASH_SECTOR_SIZE	512		// in bytes

/* Flash driver errors */
#define FLASH_ERR_BASE				0x3000
#define FLASH_ERR_SUCCESS			0
#define FLASH_ERR_INVALID_PARAM		(FLASH_ERR_BASE+1)	// invalid parameter error code
#define EEPROM_ERR_SINGLE_BIT_FAULT	(FLASH_ERR_BASE+2)	// EEPROM single bit fault error code
#define EEPROM_ERR_DOUBLE_BIT_FAULT	(FLASH_ERR_BASE+4)	// EEPROM double bits fault error code
#define FLASH_ERR_ACCESS			(FLASH_ERR_BASE+8)	// flash access error code
#define FLASH_ERR_PROTECTION		(FLASH_ERR_BASE+0x10)	// flash protection error code
#define FLASH_ERR_MGSTAT0			(FLASH_ERR_BASE+0x11)	// flash verification error code
#define FLASH_ERR_MGSTAT1			(FLASH_ERR_BASE+0x12)	// flash non-correctable error code
#define FLASH_ERR_INIT_CCIF			(FLASH_ERR_BASE+0x14)	// flash driver init error with CCIF = 1
#define FLASH_ERR_INIT_FDIV			(FLASH_ERR_BASE+0x18)	// flash driver init error with wrong FDIV 

/* Flash and EEPROM commands */


#define FLASH_CMD_PROGRAM			0x20000000
#define FLASH_CMD_CLEAR       0x00005000
#define FLASH_CMD_ERASE_ALL   0x41000000
#define FLASH_CMD_ERASE_SECTOR		0x40000000
#define FLASH_FACTORY_KEY 0x0065fe9a

#define EFM_DONE_MASK    0x00006000
#define EFM_STATUS_DONE  0x00006000
#define EFM_STATUS_READY 0x00002000

#define FLASH_ACCERR_MASK 0x10

#define M8(adr)  (*((volatile unsigned char  *) (adr)))
#define M16(adr) (*((volatile unsigned short *) (adr)))
#define M32(adr) (*((volatile unsigned long  *) (adr)))



/******************************************************************************
* Types
******************************************************************************/
typedef  uint16_t (*TFlash_Fun1)(uint32_t wNVMTargetAddress, uint8_t *pbData, uint8_t bByteCount);
typedef  uint16_t (*TFlash_Fun2)(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1);
typedef  uint16_t (*TFlash_Fun3)(uint32_t wNVMTargetAddress, uint32_t dwData);

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
uint16_t Flash_Program(uint32_t wNVMTargetAddress, uint8_t *pData, uint16_t sizeBytes);
uint16_t Flash_Program1LongWord(uint32_t wNVMTargetAddress, uint32_t dwData);
uint16_t Flash_Program2LongWords(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1);

uint16_t Flash_EraseSector(uint32_t wNVMTargetAddress);

uint16_t Flash_VerifyBackdoorKey(void);

uint16_t NVM_EraseAll(void);

uint16_t NVM_Unsecure(void);

uint16_t Flash_Init(void);

#ifdef IAR
void __ramfunc EFM_LaunchCMD(uint32_t EFM_CMD);
#else
void EFM_LaunchCMD(uint32_t EFM_CMD);
#endif


void	Flash_CopyInRAM(void);
void	Flash_CopyRouinte2RAM(char *func, uint16_t sizeFunc);
/********************************************************************/

#endif /* FLASH_H_ */
