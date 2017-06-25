/******************************************************************************
*
* @brief  FLASH 驱动头文件.  
*
******************************************************************************/
#ifndef FLASH_H_
#define FLASH_H_


#include "common.h"

#define ETMRH_FSTAT_MGSTAT0_MASK  (1)
#define ETMRH_FSTAT_MGSTAT1_MASK  (1<<1)

#define FLASH_SECTOR_SIZE	512		// in bytes

#define FLASH_ERR_BASE				0x3000
#define FLASH_ERR_SUCCESS			0
#define FLASH_ERR_INVALID_PARAM		(FLASH_ERR_BASE+1)	 
#define EEPROM_ERR_SINGLE_BIT_FAULT	(FLASH_ERR_BASE+2)	  
#define EEPROM_ERR_DOUBLE_BIT_FAULT	(FLASH_ERR_BASE+4)	  
#define FLASH_ERR_ACCESS			(FLASH_ERR_BASE+8)	  
#define FLASH_ERR_PROTECTION		(FLASH_ERR_BASE+0x10)	  
#define FLASH_ERR_MGSTAT0			(FLASH_ERR_BASE+0x11)	 
#define FLASH_ERR_MGSTAT1			(FLASH_ERR_BASE+0x12)	 
#define FLASH_ERR_INIT_CCIF			(FLASH_ERR_BASE+0x14)	  
#define FLASH_ERR_INIT_FDIV			(FLASH_ERR_BASE+0x18)	  

/*********************************/

#define FLASH_CMD_PROGRAM               0x20000000
#define FLASH_CMD_CLEAR                 0x00005000
#define FLASH_CMD_ERASE_ALL             0x41000000
#define FLASH_CMD_ERASE_SECTOR		0x40000000
#define FLASH_FACTORY_KEY               0x0065fe9a

#define EFM_DONE_MASK                   0x00006000
#define EFM_STATUS_DONE                 0x00006000
#define EFM_STATUS_READY                0x00002000

#define FLASH_ACCERR_MASK 0x10

#define M8(adr)  (*((volatile unsigned char  *) (adr)))
#define M16(adr) (*((volatile unsigned short *) (adr)))
#define M32(adr) (*((volatile unsigned long  *) (adr)))



/******************************************************************************
******************************************************************************/
typedef  uint16_t (*TFlash_Fun1)(uint32_t wNVMTargetAddress, uint8_t *pbData, uint8_t bByteCount);
typedef  uint16_t (*TFlash_Fun2)(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1);
typedef  uint16_t (*TFlash_Fun3)(uint32_t wNVMTargetAddress, uint32_t dwData);

/******************************************************************************
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
