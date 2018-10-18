#ifndef __STMFLASH_H__
#define __STMFLASH_H__

#include "stm32f4xx_hal.h"

#define FLASH_SIZE(LENTH)	(LENTH/4+((LENTH%4)?1:0))

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define FLASH_WAITETIME  50000          //FLASH等待超时时间

//FLASH 扇区的起始地址
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//扇区6起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) 	//扇区7起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) 	//扇区8起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) 	//扇区9起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) 	//扇区10起始地址,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) 	//扇区11起始地址,128 Kbytes 

#define ADDR_FLASH_SECTOR_12	((uint32_t)0x08100000) 	//扇区12起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_13	((uint32_t)0x08104000) 	//扇区13起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_14    ((uint32_t)0x08108000) 	//扇区14起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_15	((uint32_t)0x0810C000) 	//扇区15起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_16    ((uint32_t)0x08110000) 	//扇区16起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_17	((uint32_t)0x08120000) 	//扇区17起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_18	((uint32_t)0x08140000) 	//扇区18起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_19	((uint32_t)0x08160000) 	//扇区19起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_20    ((uint32_t)0x08180000) 	//扇区20起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_21	((uint32_t)0x081A0000) 	//扇区21起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_22    ((uint32_t)0x081C0000) 	//扇区22起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_23    ((uint32_t)0x081E0000) 	//扇区23起始地址, 128 Kbytes   
 
uint32_t STMFLASH_ReadWord(uint32_t faddr);	//读出字  
void STMFLASH_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead);   		//从指定地址开始读出指定长度的数据

#endif
