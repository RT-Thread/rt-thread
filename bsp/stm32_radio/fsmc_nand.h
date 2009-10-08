/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : fsmc_nand.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Header for fsmc_nand.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_NAND_H
#define __FSMC_NAND_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u8 Maker_ID;
  u8 Device_ID;
  u8 Third_ID;
  u8 Fourth_ID;
}NAND_IDTypeDef;

typedef struct 
{
  u16 Zone;
  u16 Block;
  u16 Page;
} NAND_ADDRESS;

/* Exported constants --------------------------------------------------------*/
/* NAND Area definition  for STM3210E-EVAL Board RevD */
#define CMD_AREA                   (u32)(1<<16)  /* A16 = CLE  high */
#define ADDR_AREA                  (u32)(1<<17)  /* A17 = ALE high */

#define DATA_AREA                  ((u32)0x00000000) 

/* FSMC NAND memory command */
#define	NAND_CMD_AREA_A            ((u8)0x00)
#define	NAND_CMD_AREA_B            ((u8)0x01)
#define NAND_CMD_AREA_C            ((u8)0x50)
#define NAND_CMD_AREA_TRUE1        ((u8)0x30)

#define NAND_CMD_WRITE0            ((u8)0x80)
#define NAND_CMD_WRITE_TRUE1       ((u8)0x10)
	
#define NAND_CMD_ERASE0            ((u8)0x60)
#define NAND_CMD_ERASE1            ((u8)0xD0)  

#define NAND_CMD_READID            ((u8)0x90)	
#define NAND_CMD_STATUS            ((u8)0x70)
#define NAND_CMD_LOCK_STATUS       ((u8)0x7A)
#define NAND_CMD_RESET             ((u8)0xFF)

/* NAND memory status */
#define NAND_VALID_ADDRESS         ((u32)0x00000100)
#define NAND_INVALID_ADDRESS       ((u32)0x00000200)
#define NAND_TIMEOUT_ERROR         ((u32)0x00000400)
#define NAND_BUSY                  ((u32)0x00000000)
#define NAND_ERROR                 ((u32)0x00000001)
#define NAND_READY                 ((u32)0x00000040)

/* FSMC NAND memory parameters */
//#define NAND_PAGE_SIZE             ((u16)0x0200) /* 512 bytes per page w/o Spare Area */
//#define NAND_BLOCK_SIZE            ((u16)0x0020) /* 32x512 bytes pages per block */
//#define NAND_ZONE_SIZE             ((u16)0x0400) /* 1024 Block per zone */
//#define NAND_SPARE_AREA_SIZE       ((u16)0x0010) /* last 16 bytes as spare area */
//#define NAND_MAX_ZONE              ((u16)0x0004) /* 4 zones of 1024 block */

/* FSMC NAND memory parameters */
#define NAND_PAGE_SIZE             ((u16)0x0800) /* 2K bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((u16)0x0040) /* 64x2K bytes pages per block */
#define NAND_ZONE_SIZE             ((u16)0x0400) /* 1024 Block per zone */
#define NAND_SPARE_AREA_SIZE       ((u16)0x0040) /* last 64 bytes as spare area */
#define NAND_MAX_ZONE              ((u16)0x0002) /* 1 zones of 2048 block */

/* FSMC NAND memory address computation */
#define ADDR_1st_CYCLE(ADDR)       (u8)((ADDR)& 0xFF)               /* 1st addressing cycle */
#define ADDR_2nd_CYCLE(ADDR)       (u8)(((ADDR)& 0xFF00) >> 8)      /* 2nd addressing cycle */
#define ADDR_3rd_CYCLE(ADDR)       (u8)(((ADDR)& 0xFF0000) >> 16)   /* 3rd addressing cycle */
#define ADDR_4th_CYCLE(ADDR)       (u8)(((ADDR)& 0xFF000000) >> 24) /* 4th addressing cycle */
#define ADDR_5fh_CYCLE(ADDR)       (u8)(((ADDR)& 0xFF00000000) >> 32) /* 4th addressing cycle */
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FSMC_NAND_Init(void);
void FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID);
u32 FSMC_NAND_WriteSmallPage(u8 *pBuffer, NAND_ADDRESS Address, u32 NumPageToWrite);
u32 FSMC_NAND_ReadSmallPage (u8 *pBuffer, NAND_ADDRESS Address, u32 NumPageToRead);
u32 FSMC_NAND_WriteSpareArea(u8 *pBuffer, NAND_ADDRESS Address, u32 NumSpareAreaTowrite);
u32 FSMC_NAND_ReadSpareArea(u8 *pBuffer, NAND_ADDRESS Address, u32 NumSpareAreaToRead);
u32 FSMC_NAND_EraseBlock(NAND_ADDRESS Address);
u32 FSMC_NAND_Reset(void);
u32 FSMC_NAND_GetStatus(void);
u32 FSMC_NAND_ReadStatus(void);
u32 FSMC_NAND_AddressIncrement(NAND_ADDRESS* Address);

#endif /* __FSMC_NAND_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
