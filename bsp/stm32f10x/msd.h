/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : msd.h
* Author             : MCD Application Team
* Version            : V2.1
* Date               : 05/30/2008
* Description        : Header for msd.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MSD_H
#define __MSD_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

/* Private define ------------------------------------------------------------*/
/* Block Size */
#define BLOCK_SIZE    512

/* Dummy byte */
#define DUMMY   0xFF

/* Start Data tokens  */
/* Tokens (necessary because at nop/idle (and CS active) only 0xff is on the data/command line) */
#define MSD_START_DATA_SINGLE_BLOCK_READ 0xFE  /* Data token start byte, Start Single Block Read */
#define MSD_START_DATA_MULTIPLE_BLOCK_READ  0xFE  /* Data token start byte, Start Multiple Block Read */
#define MSD_START_DATA_SINGLE_BLOCK_WRITE 0xFE  /* Data token start byte, Start Single Block Write */
#define MSD_START_DATA_MULTIPLE_BLOCK_WRITE 0xFD  /* Data token start byte, Start Multiple Block Write */
#define MSD_STOP_DATA_MULTIPLE_BLOCK_WRITE 0xFD  /* Data toke stop byte, Stop Multiple Block Write */

/* MSD functions return */
#define MSD_SUCCESS       0x00
#define MSD_FAIL          0xFF

/* MSD reponses and error flags */
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

/* Data response error */
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF

/* Commands: CMDxx = CMD-number | 0x40 */
#define MSD_GO_IDLE_STATE          0   /* CMD0=0x40 */
#define MSD_SEND_OP_COND           1   /* CMD1=0x41 */
#define MSD_SEND_CSD               9   /* CMD9=0x49 */
#define MSD_SEND_CID               10  /* CMD10=0x4A */
#define MSD_STOP_TRANSMISSION      12  /* CMD12=0x4C */
#define MSD_SEND_STATUS            13  /* CMD13=0x4D */
#define MSD_SET_BLOCKLEN           16  /* CMD16=0x50 */
#define MSD_READ_SINGLE_BLOCK      17  /* CMD17=0x51 */
#define MSD_READ_MULTIPLE_BLOCK    18  /* CMD18=0x52 */
#define MSD_SET_BLOCK_COUNT        23  /* CMD23=0x57 */
#define MSD_WRITE_BLOCK            24  /* CMD24=0x58 */
#define MSD_WRITE_MULTIPLE_BLOCK   25  /* CMD25=0x59 */
#define MSD_PROGRAM_CSD            27  /* CMD27=0x5B */
#define MSD_SET_WRITE_PROT         28  /* CMD28=0x5C */
#define MSD_CLR_WRITE_PROT         29  /* CMD29=0x5D */
#define MSD_SEND_WRITE_PROT        30  /* CMD30=0x5E */
#define MSD_TAG_SECTOR_START       32  /* CMD32=0x60 */
#define MSD_TAG_SECTOR_END         33  /* CMD33=0x61 */
#define MSD_UNTAG_SECTOR           34  /* CMD34=0x62 */
#define MSD_TAG_ERASE_GROUP_START  35  /* CMD35=0x63 */
#define MSD_TAG_ERASE_GROUP_END    36  /* CMD36=0x64 */
#define MSD_UNTAG_ERASE_GROUP      37  /* CMD37=0x65 */
#define MSD_ERASE                  38  /* CMD38=0x66 */
#define MSD_READ_OCR               39  /* CMD39=0x67 */
#define MSD_CRC_ON_OFF             40  /* CMD40=0x68 */

/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct _MSD_CSD      /*Card Specific Data*/
{
  vu8  CSDStruct;            /* CSD structure */
  vu8  SysSpecVersion;       /* System specification version */
  vu8  Reserved1;            /* Reserved */
  vu8  TAAC;                 /* Data read access-time 1 */
  vu8  NSAC;                 /* Data read access-time 2 in CLK cycles */
  vu8  MaxBusClkFrec;        /* Max. bus clock frequency */
  vu16 CardComdClasses;      /* Card command classes */
  vu8  RdBlockLen;           /* Max. read data block length */
  vu8  PartBlockRead;        /* Partial blocks for read allowed */
  vu8  WrBlockMisalign;      /* Write block misalignment */
  vu8  RdBlockMisalign;      /* Read block misalignment */
  vu8  DSRImpl;              /* DSR implemented */
  vu8  Reserved2;            /* Reserved */
  vu16 DeviceSize;           /* Device Size */
  vu8  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
  vu8  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
  vu8  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
  vu8  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
  vu8  DeviceSizeMul;        /* Device size multiplier */
  vu8  EraseGrSize;          /* Erase group size */
  vu8  EraseGrMul;           /* Erase group size multiplier */
  vu8  WrProtectGrSize;      /* Write protect group size */
  vu8  WrProtectGrEnable;    /* Write protect group enable */
  vu8  ManDeflECC;           /* Manufacturer default ECC */
  vu8  WrSpeedFact;          /* Write speed factor */
  vu8  MaxWrBlockLen;        /* Max. write data block length */
  vu8  WriteBlockPaPartial;  /* Partial blocks for write allowed */
  vu8  Reserved3;            /* Reserded */
  vu8  ContentProtectAppli;  /* Content protection application */
  vu8  FileFormatGrouop;     /* File format group */
  vu8  CopyFlag;             /* Copy flag (OTP) */
  vu8  PermWrProtect;        /* Permanent write protection */
  vu8  TempWrProtect;        /* Temporary write protection */
  vu8  FileFormat;           /* File Format */
  vu8  ECC;                  /* ECC code */
  vu8  msd_CRC;                  /* CRC */
  vu8  Reserved4;            /* always 1*/
}
sMSD_CSD;

typedef struct _MSD_CID      /*Card Identification Data*/
{
  vu8  ManufacturerID;       /* ManufacturerID */
  vu16 OEM_AppliID;          /* OEM/Application ID */
  vu32 ProdName1;            /* Product Name part1 */
  vu8  ProdName2;            /* Product Name part2*/
  vu8  ProdRev;              /* Product Revision */
  vu32 ProdSN;               /* Product Serial Number */
  vu8  Reserved1;            /* Reserved1 */
  vu16 ManufactDate;         /* Manufacturing Date */
  vu8  msd_CRC;                  /* CRC */
  vu8  Reserved2;            /* always 1*/
}
sMSD_CID;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*----- High layer function -----*/
u8 MSD_Init(void);
u8 MSD_WriteBlock(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
u8 MSD_ReadBlock(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u8 MSD_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 NumByteToWrite);
u8 MSD_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 NumByteToRead);
u8 MSD_GetCSDRegister(sMSD_CSD* MSD_csd);
u8 MSD_GetCIDRegister(sMSD_CID* MSD_cid);

/*----- Medium layer function -----*/
void MSD_SendCmd(u8 Cmd, u32 Arg, u8 Crc);
u8 MSD_GetResponse(u8 Response);
u8 MSD_GetDataResponse(void);
u8 MSD_GoIdleState(void);
u16 MSD_GetStatus(void);

/*----- Low layer function -----*/
void MSD_WriteByte(u8 byte);
u8 MSD_ReadByte(void);

#endif /* __MSD_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
